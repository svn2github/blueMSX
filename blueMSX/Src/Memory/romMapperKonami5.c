/*****************************************************************************
** File:        romMapperKonami5.c
**
** Author:      Daniel Vik
**
** Description: Rom mapper for Konami5 cartridges
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
#include "romMapperKonami5.h"
#include "romMapper.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>


typedef struct {
    int deviceHandle;
    UInt8* romData;
    int slot;
    int sslot;
    int startPage;
    int size;
    int romMapper[4];
    int sccEnable;
    SCC* scc;
} RomMapperKonami5;

static void saveState(RomMapperKonami5* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperKonami5");
    char tag[16];
    int i;

    for (i = 0; i < 4; i++) {
        sprintf(tag, "romMapper%d", i);
        saveStateSet(state, tag, rm->romMapper[i]);
    }

    saveStateSet(state, "sccEnable", rm->sccEnable);

    saveStateClose(state);
}

static void loadState(RomMapperKonami5* rm)
{
    SaveState* state = saveStateOpenForRead("mapperKonami5");
    char tag[16];
    int i;

    for (i = 0; i < 4; i++) {
        sprintf(tag, "romMapper%d", i);
        rm->romMapper[i] = saveStateGet(state, tag, 0);
    }
    
    rm->sccEnable = saveStateGet(state, "sccEnable", 0);

    saveStateClose(state);

    for (i = 0; i < 4; i++) {   
        slotMapPage(rm->slot, rm->sslot, rm->startPage + i, rm->romData + rm->romMapper[i] * 0x2000, 1, 0);
    }
    
    if (rm->sccEnable) {
        slotMapPage(rm->slot, rm->sslot, rm->startPage + 2, rm->romData + rm->romMapper[2] * 0x2000, 0, 0);
    }
    else {
        slotMapPage(rm->slot, rm->sslot, rm->startPage + 2, rm->romData + rm->romMapper[2] * 0x2000, 1, 0);
    }
}

static void destroy(RomMapperKonami5* rm)
{
    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm->romData);
    free(rm);
}

static UInt8 read(RomMapperKonami5* rm, UInt16 address) 
{
    address += 0x4000;

    if (address >= 0x9800 && address < 0xa000 && rm->sccEnable) {
        return sccRead(rm->scc, (UInt8)(address & 0xff));
    }

    return rm->romData[rm->romMapper[2] * 0x2000 + (address & 0x1fff)];
}

static void write(RomMapperKonami5* rm, UInt16 address, UInt8 value) 
{
    int change = 0;
    int bank;

    address += 0x4000;

    if (address >= 0x9800 && address < 0xa000 && rm->sccEnable) {
        sccWrite(rm->scc, address & 0xff, value);
        return;
    }
    
    if ((address < 0x5000) || (address >= 0xb800) || ((address & 0x1fff) != 0x1000)) {
        return;
    }

    bank = (address - 0x5000) >> 13;

    if (bank == 2) {
        int newEnable = (value & 0x3F) == 0x3F;
        change = rm->sccEnable != newEnable;
        rm->sccEnable = newEnable;
    }

    value &= (rm->size / 8192 - 1);
    if (rm->romMapper[bank] != value || change) {
        UInt8* bankData = rm->romData + ((int)value << 13);

        rm->romMapper[bank] = value;
        
        if (bank == 2 && rm->sccEnable) {
            slotMapPage(rm->slot, rm->sslot, rm->startPage + 2, rm->romData + rm->romMapper[2] * 0x2000, 0, 0);
        }
        else {
            slotMapPage(rm->slot, rm->sslot, rm->startPage + bank, bankData, 1, 0);
        }
    }
}

int romMapperKonami5Create(char* filename, UInt8* romData, 
                           int size, int slot, int sslot, int startPage, SCC* scc) 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    RomMapperKonami5* rm;
    int i;

    if (size < 0x8000) {
        return 1;
    }

    rm = malloc(sizeof(RomMapperKonami5));

    rm->deviceHandle = deviceManagerRegister(ROM_KONAMI5, &callbacks, rm);
    slotRegister(slot, sslot, startPage, 4, read, write, destroy, rm);

    rm->romData = malloc(size);
    memcpy(rm->romData, romData, size);
    rm->size = size;
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;
    rm->scc   = scc;
    rm->sccEnable = 0;

    rm->romMapper[0] = 0;
    rm->romMapper[1] = 1;
    rm->romMapper[2] = 2;
    rm->romMapper[3] = 3;

    for (i = 0; i < 4; i++) {   
        slotMapPage(rm->slot, rm->sslot, rm->startPage + i, rm->romData + rm->romMapper[i] * 0x2000, 1, 0);
    }

    return 1;
}

