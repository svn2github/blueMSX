/*****************************************************************************
** File:        romMapperMegaRAM.c
**
** Author:      Daniel Vik
**
** Description: Rom mapper for MegaRAM cartridges
**
** More info:   www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vik
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
#include "romMapperMegaRAM.h"
#include "romMapper.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "IoPort.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
    int deviceHandle;
    UInt8* ramData;
    int slot;
    int sslot;
    int startPage;
    int size;
    int writeEnabled;
    int romMapper[4];
} RomMapperMegaRAM;

static void saveState(RomMapperMegaRAM* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperMegaRAM");
    char tag[16];
    int i;

    for (i = 0; i < 4; i++) {
        sprintf(tag, "romMapper%d", i);
        saveStateSet(state, tag, rm->romMapper[i]);
    }
    
    saveStateSet(state, "writeEnabled", rm->writeEnabled);
    saveStateSet(state, "size",         rm->size);
    
    saveStateSetBuffer(state, "ramData", rm->ramData, rm->size);

    saveStateClose(state);
}

static void loadState(RomMapperMegaRAM* rm)
{
    SaveState* state = saveStateOpenForRead("mapperMegaRAM");
    char tag[16];
    int i;

    for (i = 0; i < 4; i++) {
        sprintf(tag, "romMapper%d", i);
        rm->romMapper[i] = saveStateGet(state, tag, 0);
    }
    
    rm->writeEnabled = saveStateGet(state, "writeEnabled", 0);
    rm->size         = saveStateGet(state, "size",         0);
    
    saveStateGetBuffer(state, "ramData", rm->ramData, rm->size);

    saveStateClose(state);

    for (i = 0; i < 4; i++) {   
        slotMapPage(rm->slot, rm->sslot, rm->startPage + i, rm->ramData + rm->romMapper[i] * 0x2000, 1, rm->writeEnabled);
        slotMapPage(rm->slot, rm->sslot, rm->startPage + i + 4, rm->ramData + rm->romMapper[i] * 0x2000, 1, rm->writeEnabled);
    }
}

static void destroy(RomMapperMegaRAM* rm)
{
    ioPortUnregister(0x8e);
    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm->ramData);
    free(rm);
}

static void write(RomMapperMegaRAM* rm, UInt16 address, UInt8 value) 
{
    int bank;

    address &= 0x7fff;

	bank = address >> 13;
    value %= rm->size >> 13;

    if (rm->romMapper[bank] != value) {
        UInt8* bankData = rm->ramData + ((int)value << 13);

        rm->romMapper[bank] = value;
        
        slotMapPage(rm->slot, rm->sslot, rm->startPage + bank, bankData, 1, 0);
        slotMapPage(rm->slot, rm->sslot, rm->startPage + bank  + 4, bankData, 1, 0);
    }
}

static void writeIo(RomMapperMegaRAM* rm, UInt16 ioPort, UInt8 value)
{
    if (rm->writeEnabled) {
        int i;
        for (i = 0; i < 4; i++) {
            slotMapPage(rm->slot, rm->sslot, rm->startPage + i, rm->ramData + rm->romMapper[i] * 0x2000, 1, 0);
            slotMapPage(rm->slot, rm->sslot, rm->startPage + i + 4, rm->ramData + rm->romMapper[i] * 0x2000, 1, 0);
        }
    }
    rm->writeEnabled = 0;
}

static UInt8 readIo(RomMapperMegaRAM* rm, UInt16 ioPort)
{
    if (!rm->writeEnabled) {
        int i;
        for (i = 0; i < 4; i++) {
            slotMapPage(rm->slot, rm->sslot, rm->startPage + i, rm->ramData + rm->romMapper[i] * 0x2000, 1, 1);
            slotMapPage(rm->slot, rm->sslot, rm->startPage + i + 4, rm->ramData + rm->romMapper[i] * 0x2000, 1, 1);
        }
    }
    rm->writeEnabled = 1;

    return 0xff;
}

int romMapperMegaRAMCreate(int size, int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    RomMapperMegaRAM* rm;
    int i;

    if (startPage != 0) {
        return 0;
    }

    rm = malloc(sizeof(RomMapperMegaRAM));

    rm->deviceHandle = deviceManagerRegister(ROM_MEGARAM, &callbacks, rm);
    slotRegister(slot, sslot, startPage, 8, NULL, write, destroy, rm);

    rm->ramData = malloc(size);
    memset(rm->ramData, 0xff, size);
    rm->size = size;
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->writeEnabled = 0;
    rm->startPage  = startPage;

    rm->romMapper[0] = 0;
    rm->romMapper[1] = 0;
    rm->romMapper[2] = 0;
    rm->romMapper[3] = 0;

    for (i = 0; i < 4; i++) {   
        slotMapPage(rm->slot, rm->sslot, rm->startPage + i, rm->ramData + rm->romMapper[i] * 0x2000, 1, 0);
        slotMapPage(rm->slot, rm->sslot, rm->startPage + i + 4, rm->ramData + rm->romMapper[i] * 0x2000, 1, 0);
    }
    
    ioPortRegister(0x8e, readIo, writeIo, rm);

    return 1;
}
