/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperOpcodeSaveRam.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2008-11-23 20:26:12 $
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
#include "romMapperOpcodeSaveRam.h"
#include "MediaDb.h"
#include "DeviceManager.h"
#include "DebugDeviceManager.h"
#include "SlotManager.h"
#include "SaveState.h"
#include "AY8910.h"
#include "Board.h"
#include "IoPort.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    int     slot;
    int     sslot;
    int     startPage;

    int    deviceHandle;
    int    debugHandle;

    UInt8   saveRam[0x8000];
} RomMapperOpcodeSaveRam;


static void saveState(RomMapperOpcodeSaveRam* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperOpcodeSaveRam");

    
    saveStateSetBuffer(state, "saveRam", rm->saveRam, 0x8000);
    
    saveStateClose(state);
}

static void loadState(RomMapperOpcodeSaveRam* rm)
{
    SaveState* state = saveStateOpenForRead("mapperOpcodeSaveRam");
    
    saveStateGetBuffer(state, "saveRam", rm->saveRam, 0x8000);

    saveStateClose(state);
}

static void destroy(RomMapperOpcodeSaveRam* rm)
{
    deviceManagerUnregister(rm->deviceHandle);
    debugDeviceUnregister(rm->debugHandle);

    free(rm);
}

static UInt8 peek(RomMapperOpcodeSaveRam* rm, UInt16 ioPort)
{
    return 0xff;
}

static UInt8 read(RomMapperOpcodeSaveRam* rm, UInt16 ioPort)
{
    return 0xff;
}

static void write(RomMapperOpcodeSaveRam* rm, UInt16 ioPort, UInt8 value)
{
}

static void reset(RomMapperOpcodeSaveRam* rm)
{
}

static void getDebugInfo(RomMapperOpcodeSaveRam* rm, DbgDevice* dbgDevice)
{
    dbgDeviceAddMemoryBlock(dbgDevice, "Save Ram", 0, 0, sizeof(rm->saveRam), rm->saveRam);
}

int romMapperOpcodeSaveRamCreate(int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    DebugCallbacks dbgCallbacks = { getDebugInfo, NULL, NULL, NULL };
    
    RomMapperOpcodeSaveRam* rm = malloc(sizeof(RomMapperOpcodeSaveRam));
    
    rm->slot      = slot;
    rm->sslot     = sslot;
    rm->startPage = startPage;
    
    memset(rm->saveRam, 0xff, sizeof(rm->saveRam));

    rm->deviceHandle = deviceManagerRegister(ROM_OPCODESAVE, &callbacks, rm);
    rm->debugHandle = debugDeviceRegister(DBGTYPE_RAM, "SAVERAM", &dbgCallbacks, rm);

    slotMapPage(rm->slot, rm->sslot, rm->startPage + 0, rm->saveRam + 0x0000, 1, 1);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 1, rm->saveRam + 0x2000, 1, 1);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 2, rm->saveRam + 0x4000, 1, 1);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 3, rm->saveRam + 0x6000, 1, 1);

    reset(rm);

    return 1;
}

