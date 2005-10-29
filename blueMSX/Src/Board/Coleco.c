/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/Coleco.c,v $
**
** $Revision: 1.33 $
**
** $Date: 2005-10-29 22:53:10 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vik, Tomas Karlsson, Maarten ter Huurne
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

#include "Coleco.h"

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
#include "Keyboard.h"
#include "MegaromCartridge.h"


/* Hardware */
static SN76489*    sn76489;
static R800*       r800;
static JoystickIO* joyIO;
static int         joyMode = 0;

static void colecoSN76489Write(void* dummy, UInt16 ioPort, UInt8 value) 
{
    sn76489WriteData(sn76489, ioPort, value);
}

static void colecoJoyIoWrite(void* dummy, UInt16 ioPort, UInt8 value)
{
	joyMode = (ioPort >> 6) & 1;
}

static UInt8 colecorJoyIoRead(void* dummy, UInt16 ioPort)
{
    UInt8 joyState = joystickReadColeco(joyIO, ioPort >> 1);
    UInt8* keyMap = keyboardGetState();
    UInt8 value;

    if (joyMode != 0) {
        return ((joyState & 0x01) ? 0x01 : 0) |
               ((joyState & 0x08) ? 0x02 : 0) |
               ((joyState & 0x02) ? 0x04 : 0) |
               ((joyState & 0x04) ? 0x08 : 0) |
               ((joyState & 0x10) ? 0x40 : 0) |
               0x30;
    }

    value = 0x30 | ((joyState & 0x20) ? 0x40 : 0);

	if (ioPort & 2) {
		if      (~keyMap[ 9] & 0x08) value |= 0x0A; // 0
		else if (~keyMap[ 9] & 0x10) value |= 0x0D; // 1
		else if (~keyMap[ 9] & 0x20) value |= 0x07; // 2
		else if (~keyMap[ 9] & 0x40) value |= 0x0C; // 3
		else if (~keyMap[ 9] & 0x80) value |= 0x02; // 4
		else if (~keyMap[10] & 0x01) value |= 0x03; // 5
		else if (~keyMap[10] & 0x02) value |= 0x0E; // 6
		else if (~keyMap[10] & 0x04) value |= 0x05; // 7
		else if (~keyMap[10] & 0x08) value |= 0x01; // 8
		else if (~keyMap[10] & 0x10) value |= 0x0B; // 9
		else if (~keyMap[ 9] & 0x01) value |= 0x09; // *
		else if (~keyMap[ 9] & 0x04) value |= 0x06; // / to #
    }
    else {
		if      (~keyMap[0] & 0x01) value |= 0x0A; // 0
		else if (~keyMap[0] & 0x02) value |= 0x0D; // 1
		else if (~keyMap[0] & 0x04) value |= 0x07; // 2
		else if (~keyMap[0] & 0x08) value |= 0x0C; // 3
		else if (~keyMap[0] & 0x10) value |= 0x02; // 4
		else if (~keyMap[0] & 0x20) value |= 0x03; // 5
		else if (~keyMap[0] & 0x40) value |= 0x0E; // 6
		else if (~keyMap[0] & 0x80) value |= 0x05; // 7
		else if (~keyMap[1] & 0x01) value |= 0x01; // 8
		else if (~keyMap[1] & 0x02) value |= 0x0B; // 9
		else if (~keyMap[1] & 0x04) value |= 0x09; // - to *
		else if (~keyMap[1] & 0x08) value |= 0x06; // = to #
	}

    return value;
}

static void colecoJoyIoCreate()
{
    int i;
    for (i = 0xe0; i <= 0xff; i++) {
        ioPortRegister(i, colecorJoyIoRead, colecoSN76489Write, NULL);
    }
    for (i = 0x80; i <= 0x9f; i++) {
        ioPortRegister(i, NULL, colecoJoyIoWrite, NULL);
    }
    for (i = 0xc0; i <= 0xdf; i++) {
        ioPortRegister(i, NULL, colecoJoyIoWrite, NULL);
    }
}

static void colecoJoyIoDestroy()
{
    int i;
    for (i = 0xe0; i <= 0xff; i++) {
        ioPortUnregister(i);
    }
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
    joystickIoDestroyColeco(joyIO);

    colecoJoyIoDestroy();
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
    joystickIoSaveState(joyIO);
    r800SaveState(r800);
    sn76489SaveState(sn76489);
    deviceManagerSaveState();
    slotSaveState();
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

int colecoCreate(Machine* machine, 
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
    vdpCreate(VDP_COLECO, machine->video.vdpVersion, vdpSyncMode, machine->video.vramSize / 0x4000);

    colecoJoyIoCreate();

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

    joyIO = joystickIoCreateColeco();

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
