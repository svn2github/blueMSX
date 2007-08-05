/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/Coleco.c,v $
**
** $Revision: 1.47 $
**
** $Date: 2007-08-05 21:51:44 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2006 Daniel Vik, Tomas Karlsson, Maarten ter Huurne
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
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

#include "InputEvent.h"
#include "SN76489.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "SlotManager.h"
#include "Led.h"
#include "Switches.h"
#include "IoPort.h"
#include "MegaromCartridge.h"
#include "JoystickPort.h"
#include "ColecoJoystick.h"


/* Hardware */
static SN76489*    sn76489;
static R800*       r800;


// ---------------------------------------------
// SG-1000 Joystick and PSG handler

static ColecoJoystickDevice* joyDevice[2];
static int joyDeviceHandle;
static int joyMode;

static void colecoSN76489Write(void* dummy, UInt16 ioPort, UInt8 value) 
{
    sn76489WriteData(sn76489, ioPort, value);
}

static void colecoJoyIoWrite(void* dummy, UInt16 ioPort, UInt8 value)
{
	joyMode = (ioPort >> 6) & 1;
}

static UInt8 colecoJoyIoRead(void* dummy, UInt16 ioPort)
{
    ColecoJoystickDevice* device = joyDevice[(ioPort >> 1) & 1];
    UInt8 joyState = 0x3f;
    UInt8 value;

    if (device != NULL && device->read != NULL) {
        joyState = device->read(device);
    }

    if (joyMode != 0) {
        return boardCaptureUInt8(ioPort & 2, ((joyState & 0x01) ? 0x01 : 0) |
                                             ((joyState & 0x08) ? 0x02 : 0) |
                                             ((joyState & 0x02) ? 0x04 : 0) |
                                             ((joyState & 0x04) ? 0x08 : 0) |
                                             ((joyState & 0x10) ? 0x40 : 0) |
                                             0x30);
    }

    value = 0x30 | ((joyState & 0x20) ? 0x40 : 0);

	if (ioPort & 2) {
		if      (inputEventGetState(EC_COLECO2_0))    value |= 0x0A;
		else if (inputEventGetState(EC_COLECO2_1))    value |= 0x0D;
		else if (inputEventGetState(EC_COLECO2_2))    value |= 0x07;
		else if (inputEventGetState(EC_COLECO2_3))    value |= 0x0C;
		else if (inputEventGetState(EC_COLECO2_4))    value |= 0x02;
		else if (inputEventGetState(EC_COLECO2_5))    value |= 0x03;
		else if (inputEventGetState(EC_COLECO2_6))    value |= 0x0E;
		else if (inputEventGetState(EC_COLECO2_7))    value |= 0x05;
		else if (inputEventGetState(EC_COLECO2_8))    value |= 0x01;
		else if (inputEventGetState(EC_COLECO2_9))    value |= 0x0B;
		else if (inputEventGetState(EC_COLECO2_STAR)) value |= 0x09;
		else if (inputEventGetState(EC_COLECO2_HASH)) value |= 0x06;
    }
    else {
		if      (inputEventGetState(EC_COLECO1_0))    value |= 0x0A;
		else if (inputEventGetState(EC_COLECO1_1))    value |= 0x0D;
		else if (inputEventGetState(EC_COLECO1_2))    value |= 0x07;
		else if (inputEventGetState(EC_COLECO1_3))    value |= 0x0C;
		else if (inputEventGetState(EC_COLECO1_4))    value |= 0x02;
		else if (inputEventGetState(EC_COLECO1_5))    value |= 0x03;
		else if (inputEventGetState(EC_COLECO1_6))    value |= 0x0E;
		else if (inputEventGetState(EC_COLECO1_7))    value |= 0x05;
		else if (inputEventGetState(EC_COLECO1_8))    value |= 0x01;
		else if (inputEventGetState(EC_COLECO1_9))    value |= 0x0B;
		else if (inputEventGetState(EC_COLECO1_STAR)) value |= 0x09;
		else if (inputEventGetState(EC_COLECO1_HASH)) value |= 0x06;
	}

    return boardCaptureUInt8(4 + (ioPort & 2), value);
}

static void colecoJoyIoHandler(void* dummy, int port, JoystickPortType type)
{
    if (port >= 2) {
        return;
    }

    if (joyDevice[port] != NULL && joyDevice[port]->destroy != NULL) {
        joyDevice[port]->destroy(joyDevice[port]);
    }
    
    switch (type) {
    default:
    case JOYSTICK_PORT_NONE:
        joyDevice[port] = NULL;
        break;
    case JOYSTICK_PORT_COLECOJOYSTICK:
        joyDevice[port] = colecoJoystickCreate(port);
        break;
    }
}

static void colecoJoyIoLoadState(void* dummy)
{
    if (joyDevice[0] != NULL && joyDevice[0]->loadState != NULL) {
        joyDevice[0]->loadState(joyDevice[0]);
    }
    if (joyDevice[1] != NULL && joyDevice[1]->loadState != NULL) {
        joyDevice[1]->loadState(joyDevice[1]);
    }
}

static void colecoJoyIoSaveState(void* dummy)
{
    if (joyDevice[0] != NULL && joyDevice[0]->saveState != NULL) {
        joyDevice[0]->saveState(joyDevice[0]);
    }
    if (joyDevice[1] != NULL && joyDevice[1]->saveState != NULL) {
        joyDevice[1]->saveState(joyDevice[1]);
    }
}

static void colecoJoyIoReset(void* dummy)
{
    if (joyDevice[0] != NULL && joyDevice[0]->reset != NULL) {
        joyDevice[0]->reset(joyDevice[0]);
    }
    if (joyDevice[1] != NULL && joyDevice[1]->reset != NULL) {
        joyDevice[1]->reset(joyDevice[1]);
    }
}

static void colecoJoyIoDestroy(void* dummy)
{
    int i;
    for (i = 0xe0; i <= 0xff; i++) {
        ioPortUnregister(i);
    }
    
    if (joyDevice[0] != NULL && joyDevice[0]->destroy != NULL) {
        joyDevice[0]->destroy(joyDevice[0]);
    }
    if (joyDevice[1] != NULL && joyDevice[1]->destroy != NULL) {
        joyDevice[1]->destroy(joyDevice[1]);
    }
    
    joystickPortUpdateHandlerUnregister();

    deviceManagerUnregister(joyDeviceHandle);
}

static void colecoJoyIoCreate()
{
    DeviceCallbacks callbacks = { colecoJoyIoDestroy,   colecoJoyIoReset, 
                                  colecoJoyIoSaveState, colecoJoyIoLoadState };

    int i;
    
    // Initialize joyMode
    joyMode = 1;

    for (i = 0xe0; i <= 0xff; i++) {
        ioPortRegister(i, colecoJoyIoRead, colecoSN76489Write, NULL);
    }
    for (i = 0x80; i <= 0x9f; i++) {
        ioPortRegister(i, NULL, colecoJoyIoWrite, NULL);
    }
    for (i = 0xc0; i <= 0xdf; i++) {
        ioPortRegister(i, NULL, colecoJoyIoWrite, NULL);
    }
    
    joystickPortUpdateHandlerRegister(colecoJoyIoHandler, NULL);
    joyDeviceHandle = deviceManagerRegister(ROM_UNKNOWN, &callbacks, NULL);
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
    sn76489LoadState(sn76489);
}

int colecoCreate(Machine* machine, 
                 VdpSyncMode vdpSyncMode,
                 BoardInfo* boardInfo)
{
    int success;
    int i;

    r800 = r800Create(CPU_ENABLE_M1, slotRead, slotWrite, ioPortRead, ioPortWrite, NULL, boardTimerCheckTimeout, NULL, NULL, NULL);

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
    boardInfo->setInt           = r800SetNmi;
    boardInfo->clearInt         = r800ClearNmi;
    boardInfo->setCpuTimeout    = r800SetTimeoutAt;
    boardInfo->setBreakpoint    = r800SetBreakpoint;
    boardInfo->clearBreakpoint  = r800ClearBreakpoint;
    boardInfo->setDataBus       = r800SetDataBus;

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

    success = machineInitialize(machine, NULL, NULL, NULL);

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
