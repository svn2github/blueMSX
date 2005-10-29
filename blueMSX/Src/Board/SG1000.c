/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/SG1000.c,v $
**
** $Revision: 1.8 $
**
** $Date: 2005-10-29 22:53:10 $
**
** More info: http://www.bluemsx.com
**
** Author: Ricardo Bittencourt
** Copyright (C) 2003-2005 Daniel Vik, Ricardo Bittencourt
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SG1000.h"

#include "R800.h"
#include "R800Dasm.h"
#include "R800SaveState.h"
#include "R800Debug.h"

#include "SN76489.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "SlotManager.h"
#include "Led.h"
#include "Switches.h"
#include "JoystickIO.h"
#include "IoPort.h"
#include "MegaromCartridge.h"


/* Hardware */
static SN76489*    sn76489;
static R800*       r800;
static JoystickIO* joyIO;
static UInt32      sg1000RamSize;
static UInt8*      sg1000Ram;
static int         joyMode = 0;

static void sg1000Sn76489Write(void* dummy, UInt16 ioPort, UInt8 value) 
{
    sn76489WriteData(sn76489, ioPort, value);
}

static UInt8 sg1000JoyIoRead(void* dummy, UInt16 ioPort)
{
    UInt8 joyState = joystickReadSG1000(joyIO, 0);

    return (joyState & 0x3F) | 0xC0;
}

static void sg1000JoyIoCreate()
{
	int i;

	for (i=0x40; i<0x80; i++)
		ioPortRegister(i, NULL, sg1000Sn76489Write, NULL);

	for (i=0xC0; i<0x100; i+=2)
		ioPortRegister(i, sg1000JoyIoRead, NULL, NULL);
}

static void sg1000JoyIoDestroy()
{
	int i;

	for (i=0x40; i<0x80; i++)
		ioPortUnregister(i);

	for (i=0xC0; i<0x100; i+=2)
		ioPortUnregister(i);
}

static void reset()
{
    UInt32 systemTime = boardSystemTime();

    slotManagerReset();

    if (r800 != NULL) {
        r800Reset(r800, systemTime);
    }

    if (sn76489 != NULL) {
        sn76489Reset(sn76489);
    }
    
    ledSetCapslock(0);

    deviceManagerReset();
}

static void destroy() 
{    
    boardRemoveExternalDevices();
    joystickIoDestroySG1000(joyIO);

    sg1000JoyIoDestroy();
    sn76489Destroy(sn76489);
    r800DebugDestroy();
    slotManagerDestroy();
    deviceManagerDestroy();
    r800Destroy(r800);
}

static int getRefreshRate()
{
    return vdpGetRefreshRate();
}

static void saveState()
{    
    r800SaveState(r800);
    deviceManagerSaveState();
    slotSaveState();
    joystickIoSaveState(joyIO);
    sn76489SaveState(sn76489);
}

static void loadState()
{
    r800LoadState(r800);
    boardInit(&r800->systemTime);
    deviceManagerLoadState();
    slotLoadState();
    joystickIoLoadState(joyIO);
    sn76489LoadState(sn76489);
}

int sg1000Create(Machine* machine, 
                 VdpSyncMode vdpSyncMode,
                 BoardInfo* boardInfo)
{
    int success;
    int i;

    r800 = r800Create(slotRead, slotWrite, ioPortRead, ioPortWrite, NULL, boardTimerCheckTimeout, NULL, NULL, NULL);

    boardInfo->cartridgeCount   = 1;
    boardInfo->diskdriveCount   = 0;
    boardInfo->casetteCount     = 0;
    boardInfo->cpuRef           = r800;

    boardInfo->destroy          = destroy;
    boardInfo->softReset        = reset;
    boardInfo->loadState        = loadState;
    boardInfo->saveState        = saveState;
    boardInfo->getRefreshRate   = getRefreshRate;
    boardInfo->getRamPage       = NULL;

    boardInfo->run              = r800Execute;
    boardInfo->stop             = r800StopExecution;
    boardInfo->setInt           = r800SetInt;
    boardInfo->clearInt         = r800ClearInt;
    boardInfo->setCpuTimeout    = r800SetTimeoutAt;
    boardInfo->setBreakpoint    = r800SetBreakpoint;
    boardInfo->clearBreakpoint  = r800ClearBreakpoint;

    deviceManagerCreate();
    
    boardInit(&r800->systemTime);
    ioPortReset();

    r800Reset(r800, 0);
    mixerReset(boardGetMixer());

    r800DebugCreate(r800);

    sn76489 = sn76489Create(boardGetMixer());

    slotManagerCreate();

    if (vdpSyncMode == VDP_SYNC_AUTO) {
        vdpSyncMode = VDP_SYNC_60HZ;
    }
    vdpCreate(VDP_SG1000, machine->video.vdpVersion, vdpSyncMode, machine->video.vramSize / 0x4000);

    sg1000JoyIoCreate();

	ledSetCapslock(0);

    for (i = 0; i < 4; i++) {
        slotSetSubslotted(i, 0);
    }
    for (i = 0; i < 2; i++) {
        cartridgeSetSlotInfo(i, machine->cart[i].slot, 0);
    }

    success = machineInitialize(machine, NULL, NULL);

    for (i = 0; i < 8; i++) {
        slotMapRamPage(0, 0, i);
    }

    joyIO = joystickIoCreateSG1000();

    if (success) {
        success = boardInsertExternalDevices();
    }

    r800SetFrequency(r800, CPU_Z80,  machine->cpu.freqZ80);
    r800SetFrequency(r800, CPU_R800, machine->cpu.freqR800);

    if (!success) {
        destroy();
    }

    return success;
}
