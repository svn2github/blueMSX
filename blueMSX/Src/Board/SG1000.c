/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/SG1000.c,v $
**
** $Revision: 1.15 $
**
** $Date: 2006-08-09 14:09:47 $
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
#include "IoPort.h"
#include "Disk.h"
#include "MegaromCartridge.h"
#include "Sg1000JoyIo.h"
#include "Sc3000PPI.h"
#include "Sf7000PPI.h"


/* Hardware */
static Sg1000JoyIo* joyIo;
static SN76489*     sn76489;
static R800*        r800;
static UInt8*       sfRam;
static UInt32       sfRamSize;


// ---------------------------------------------
// SG-1000 Joystick and PSG handler


static void sg1000Sn76489Write(void* dummy, UInt16 ioPort, UInt8 value) 
{
    sn76489WriteData(sn76489, ioPort, value);
}

static UInt8 joyIoRead(void* dummy, UInt16 ioPort)
{
    switch (ioPort & 1) {
    case 0:
        return (UInt8)(sg1000JoyIoRead(joyIo) & 0xff);
    case 1:
        return (UInt8)(sg1000JoyIoRead(joyIo) >> 8);
    }

    return 0xff;
}

static void sg1000IoPortDestroy(void* dummy)
{
	int i;

	for (i=0x40; i<0x80; i++)
		ioPortUnregister(i);

	for (i=0xC0; i<0x100; i+=2)
		ioPortUnregister(i);

	ioPortUnregister(0xc1);
	ioPortUnregister(0xdd);
}

static void sg1000IoPortCreate()
{
    DeviceCallbacks callbacks = { sg1000IoPortDestroy, NULL, NULL, NULL };
	int i;
   
	for (i=0x40; i<0x80; i++)
		ioPortRegister(i, NULL, sg1000Sn76489Write, NULL);

	for (i=0xC0; i<0x100; i+=2)
		ioPortRegister(i, joyIoRead, NULL, NULL);
    
	ioPortRegister(0xc1, joyIoRead, NULL, NULL);
	ioPortRegister(0xdd, joyIoRead, NULL, NULL);
}

// -----------------------------------------------------

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
    sn76489SaveState(sn76489);
}

static void loadState()
{
    r800LoadState(r800);
    boardInit(&r800->systemTime);
    deviceManagerLoadState();
    slotLoadState();
    sn76489LoadState(sn76489);
}

static UInt8* getRamPage(int page) {
    static UInt8 emptyRam[0x2000];

    if (sfRam == NULL) {
        return emptyRam;
    }

	return sfRam + ((page * 0x2000) & (sfRamSize - 1));
}

int sg1000Create(Machine* machine, 
                 VdpSyncMode vdpSyncMode,
                 BoardInfo* boardInfo)
{
    int success;
    int i;

    sfRam = NULL;

    r800 = r800Create(0, slotRead, slotWrite, ioPortRead, ioPortWrite, NULL, boardTimerCheckTimeout, NULL, NULL, NULL);

    boardInfo->cartridgeCount   = 1;
    boardInfo->diskdriveCount   = 0;
    boardInfo->casetteCount     = 0;
    boardInfo->cpuRef           = r800;

    boardInfo->destroy          = destroy;
    boardInfo->softReset        = reset;
    boardInfo->loadState        = loadState;
    boardInfo->saveState        = saveState;
    boardInfo->getRefreshRate   = getRefreshRate;
    boardInfo->getRamPage       = getRamPage;

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

    joyIo = sg1000JoyIoCreate();
    if (machine->board.type == BOARD_SF7000) {
        sc3000PPICreate(joyIo);
        
        sf7000PPICreate();
            
        diskEnable(0, machine->fdc.count > 0);
        diskEnable(1, machine->fdc.count > 1);

    }
    sg1000IoPortCreate();

	ledSetCapslock(0);

    for (i = 0; i < 4; i++) {
        slotSetSubslotted(i, 0);
    }
    for (i = 0; i < 2; i++) {
        cartridgeSetSlotInfo(i, machine->cart[i].slot, 0);
    }

    success = machineInitialize(machine, &sfRam, &sfRamSize);

    for (i = 0; i < 8; i++) {
        slotMapRamPage(0, 0, i);
    }

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
