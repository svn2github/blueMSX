/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperMsxAudio.c,v $
**
** $Revision: 1.11 $
**
** $Date: 2006-09-19 06:00:30 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2006 Daniel Vik
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
#include "romMapperMsxAudio.h"
#include "MediaDb.h"
#include "Switches.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "DebugDeviceManager.h"
#include "IoPort.h"
#include "Board.h"
#include "Y8950.h"
#include "SaveState.h"
#include "Language.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    int deviceHandle;
    int debugHandle;
    Y8950* y8950;
    int ioBase;
    UInt8* romData;
    UInt8 ram[0x1000];
    int bankSelect; 
    int sizeMask;
    int slot;
    int sslot;
    int startPage;
} RomMapperMsxAudio;

static int deviceCount = 0;

static void saveState(RomMapperMsxAudio* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperMsxAudio");

    saveStateSet(state, "bankSelect", rm->bankSelect);
    saveStateSetBuffer(state, "ram", rm->ram, sizeof(rm->ram));
    
    saveStateClose(state);

    if (rm->y8950 != NULL) {
        y8950SaveState(rm->y8950);
    }
}

static void loadState(RomMapperMsxAudio* rm)
{
    SaveState* state = saveStateOpenForRead("mapperMsxAudio");

    rm->bankSelect = saveStateGet(state, "bankSelect", 0);
    saveStateGetBuffer(state, "ram", rm->ram, sizeof(rm->ram));

    saveStateClose(state);
    
    if (rm->y8950 != NULL) {
        y8950LoadState(rm->y8950);
    }
}

static void destroy(RomMapperMsxAudio* rm)
{
    ioPortUnregister(0x00);
    ioPortUnregister(0x01);
    ioPortUnregister(0x04);
    ioPortUnregister(0x05);

    ioPortUnregister(rm->ioBase + 0);
    ioPortUnregister(rm->ioBase + 1);

    deviceCount--;

    if (rm->y8950 != NULL) {
        y8950Destroy(rm->y8950);
    }

    if (rm->sizeMask != -1) {
        slotUnregister(rm->slot, rm->sslot, rm->startPage);
    }

    debugDeviceUnregister(rm->debugHandle);
    deviceManagerUnregister(rm->deviceHandle);

    if (rm->romData != NULL) {
        free(rm->romData);
    }
    free(rm);
}

static UInt8 read(RomMapperMsxAudio* rm, UInt16 address) 
{
	if (rm->bankSelect == 0 && (address & 0x3fff) >= 0x3000) {
		return rm->ram[(address & 0x3fff) - 0x3000];
    }

	return rm->romData[(0x8000 * rm->bankSelect + (address & 0x7fff)) & rm->sizeMask];
}

static void reset(RomMapperMsxAudio* rm) 
{
    if (rm->y8950 != NULL) {
        y8950Reset(rm->y8950);
    }
}

static void write(RomMapperMsxAudio* rm, UInt16 address, UInt8 value) 
{
	address &= 0x7fff;
	if (address == 0x7ffe) {
		rm->bankSelect = value & 3;
	}
	address &= 0x3fff;
	if (rm->bankSelect == 0 && address >= 0x3000) {
		rm->ram[address - 0x3000] = value;
	}
}


static void midiWrite(RomMapperMsxAudio* rm, UInt16 ioPort, UInt8 value)
{
}

static UInt8 midiRead(RomMapperMsxAudio* rm, UInt16 ioPort)
{
    switch (ioPort & 1) {
    case 0x00: 
        return 2;

    case 0x01: 
        return 0;
    }

    return 0xff;
}

static void getDebugInfo(RomMapperMsxAudio* rm, DbgDevice* dbgDevice)
{
    DbgIoPorts* ioPorts;

    if (rm->y8950 == NULL) {
        return;
    }

    ioPorts = dbgDeviceAddIoPorts(dbgDevice, langDbgDevMsxAudio(), 2);
    dbgIoPortsAddPort(ioPorts, 0, rm->ioBase + 0, DBG_IO_READWRITE, y8950Peek(rm->y8950, 0));
    dbgIoPortsAddPort(ioPorts, 1, rm->ioBase + 1, DBG_IO_READWRITE, y8950Peek(rm->y8950, 1));
    
    ioPorts = dbgDeviceAddIoPorts(dbgDevice, langDbgDevMsxAudioMidi(), 4);
    dbgIoPortsAddPort(ioPorts, 0, 0x00, DBG_IO_WRITE, 0);
    dbgIoPortsAddPort(ioPorts, 1, 0x01, DBG_IO_WRITE, 0);
    dbgIoPortsAddPort(ioPorts, 2, 0x04, DBG_IO_READ, midiRead(rm, 0x04));
    dbgIoPortsAddPort(ioPorts, 3, 0x05, DBG_IO_READ, midiRead(rm, 0x05));

    y8950GetDebugInfo(rm->y8950, dbgDevice);
}

int romMapperMsxAudioCreate(char* filename, UInt8* romData, 
                            int size, int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    DebugCallbacks dbgCallbacks = { getDebugInfo, NULL, NULL, NULL };
    RomMapperMsxAudio* rm;
    int i;

    rm = malloc(sizeof(RomMapperMsxAudio));

    rm->deviceHandle = deviceManagerRegister(ROM_MSXAUDIO, &callbacks, rm);
    rm->debugHandle = debugDeviceRegister(DBGTYPE_AUDIO, langDbgDevMsxAudio(), &dbgCallbacks, rm);

    rm->ioBase = 0xc0 + deviceCount++ * 2;

    rm->romData = NULL;

    if (size > 0) {
        slotRegister(slot, sslot, startPage, 8, read, read, write, destroy, rm);

        rm->romData = malloc(size);
        memcpy(rm->romData, romData, size);
        memset(rm->ram, 0, 0x1000);
        rm->bankSelect = 0;
        rm->sizeMask = size - 1;
        rm->slot  = slot;
        rm->sslot = sslot;
        rm->startPage  = startPage;

        if (!switchGetAudio()) {
            rm->romData[0x408e] = 0;
        }

        for (i = 0; i < 8; i++) {
            slotMapPage(rm->slot, rm->sslot, rm->startPage + i, NULL, 0, 0);
        }
    }

    rm->y8950 = NULL;

    if (boardGetY8950Enable()) {
        rm->y8950 = y8950Create(boardGetMixer());
        ioPortRegister(rm->ioBase + 0, y8950Read, y8950Write, rm->y8950);
        ioPortRegister(rm->ioBase + 1, y8950Read, y8950Write, rm->y8950);

        ioPortRegister(0x00, NULL, midiWrite, rm);
        ioPortRegister(0x01, NULL, midiWrite, rm);
        ioPortRegister(0x04, midiRead, NULL, rm);
        ioPortRegister(0x05, midiRead, NULL, rm);
    }

    reset(rm);

    return 1;
}

