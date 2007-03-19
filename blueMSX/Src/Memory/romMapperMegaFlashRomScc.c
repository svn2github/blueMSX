/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperMegaFlashRomScc.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2007-03-19 19:30:19 $
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
#include "romMapperMegaFlashRomScc.h"
#include "AmdFlash.h"
#include "MediaDb.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "sramLoader.h"
#include "SCC.h"
#include "Board.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>


typedef struct {
    int deviceHandle;
    UInt8* romData;
    AmdFlash* flash;
    int slot;
    int sslot;
    int startPage;
    int size;
    int flashStart;
    int romMapper[4];
    int flashPage[4];
    int sccEnable;
    SCC* scc;
} RomMapperMegaFlashRomScc;

static void mapPage(RomMapperMegaFlashRomScc* rm, int bank, int page)
{
    int flashPageStart  = rm->flashStart / 0x2000;
    int readEnable;
    UInt8* bankData;

    rm->romMapper[bank] = page & (rm->size / 0x2000 - 1);
    rm->flashPage[bank] = page - flashPageStart;

    if (rm->flashPage[bank] < 0) {
        bankData = rm->romData + page * 0x2000;
    }
    else {
        bankData = amdFlashGetPage(rm->flash, rm->flashPage[bank] * 0x2000);
    }

    readEnable = (bank == 2 && rm->sccEnable) || rm->flashPage[bank] >= 0 ? 0 : 1;

    slotMapPage(rm->slot, rm->sslot, rm->startPage + bank, bankData, readEnable, 0);
}

static void saveState(RomMapperMegaFlashRomScc* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperMegaFlashRomScc");
    char tag[16];
    int i;

    for (i = 0; i < 4; i++) {
        sprintf(tag, "romMapper%d", i);
        saveStateSet(state, tag, rm->romMapper[i]);
    }

    saveStateSet(state, "sccEnable", rm->sccEnable);

    saveStateClose(state);

    sccSaveState(rm->scc);
    amdFlashSaveState(rm->flash);
}

static void loadState(RomMapperMegaFlashRomScc* rm)
{
    SaveState* state = saveStateOpenForRead("mapperMegaFlashRomScc");
    char tag[16];
    int i;

    for (i = 0; i < 4; i++) {
        sprintf(tag, "romMapper%d", i);
        rm->romMapper[i] = saveStateGet(state, tag, 0);
    }
    
    rm->sccEnable = saveStateGet(state, "sccEnable", 0);

    saveStateClose(state);

    sccLoadState(rm->scc);    
    amdFlashLoadState(rm->flash);

    for (i = 0; i < 4; i++) {   
        mapPage(rm, i, rm->romMapper[i]);
    }    
}

static void destroy(RomMapperMegaFlashRomScc* rm)
{
    amdFlashDestroy(rm->flash);
    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);
    sccDestroy(rm->scc);

    free(rm->romData);
    free(rm);
}

static void reset(RomMapperMegaFlashRomScc* rm)
{
    amdFlashReset(rm->flash);
    sccReset(rm->scc);
}

static UInt8 read(RomMapperMegaFlashRomScc* rm, UInt16 address) 
{
    int bank = address / 0x2000;

    address += 0x4000;

    if (address >= 0x9800 && address < 0xa000 && rm->sccEnable) {
        return sccRead(rm->scc, (UInt8)(address & 0xff));
    }

    if (rm->flashPage[bank] >= 0) {
        return amdFlashRead(rm->flash, (address & 0x1fff) + 0x2000 * rm->flashPage[bank]);
    }

    return rm->romData[rm->romMapper[2] * 0x2000 + (address & 0x1fff)];
}

static UInt8 peek(RomMapperMegaFlashRomScc* rm, UInt16 address) 
{
    int bank = address / 0x2000;

    address += 0x4000;

    if (address >= 0x9800 && address < 0xa000 && rm->sccEnable) {
        return sccPeek(rm->scc, (UInt8)(address & 0xff));
    }

    if (rm->flashPage[bank] >= 0) {
        return amdFlashRead(rm->flash, (address & 0x1fff) + 0x2000 * rm->flashPage[bank]);
    }

    return rm->romData[rm->romMapper[2] * 0x2000 + (address & 0x1fff)];
}

static void write(RomMapperMegaFlashRomScc* rm, UInt16 address, UInt8 value) 
{
    int change = 0;
    int bank;

    address += 0x4000;
    if (address >= 0x9800 && address < 0xa000 && rm->sccEnable) {
        sccWrite(rm->scc, address & 0xff, value);
        return;
    }
    address -= 0x4000;

    bank = address >> 13;

    if (rm->flashPage[bank] >= 0) {
        amdFlashWrite(rm->flash, (address & 0x1fff) + 0x2000 * rm->flashPage[bank], value);
    }

    if ((address - 0x1000) & 0x1800) {
        return;
    }

    if (bank == 2) {
        int newEnable = (value & 0x3F) == 0x3F;
        change = rm->sccEnable != newEnable;
        rm->sccEnable = newEnable;
    }

    if (rm->romMapper[bank] != value || change) {
        mapPage(rm, bank, value);
    }
}

int romMapperMegaFlashRomSccCreate(char* filename, UInt8* romData, 
                                   int size, int slot, int sslot, int startPage, int flashSize) 
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    RomMapperMegaFlashRomScc* rm;
    int i;

    rm = calloc(1, sizeof(RomMapperMegaFlashRomScc));

    rm->deviceHandle = deviceManagerRegister(ROM_MEGAFLSHSCC, &callbacks, rm);
    slotRegister(slot, sslot, startPage, 4, read, peek, write, destroy, rm);

    if (size >= 0x80000) {
        size = 0x80000;
    }

    rm->flashStart = flashSize < 0 ? 0 : 0x80000 - flashSize;
    rm->romData = malloc(0x80000);
    memset(rm->romData, 0xff, 0x80000);
    memcpy(rm->romData, romData, size);
    rm->size = 0x80000;
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;
    rm->scc = sccCreate(boardGetMixer());
    sccSetMode(rm->scc, SCC_REAL);
    rm->sccEnable = 0;

    if (size > rm->flashStart) {
        rm->flash = amdFlashCreate(AMD_TYPE_2, 0x80000 - rm->flashStart, 0x10000, romData + rm->flashStart, size - rm->flashStart, sramCreateFilenameWithSuffix(filename, "", ".sram"));
    }
    else {
        rm->flash = amdFlashCreate(AMD_TYPE_2, 0x80000 - rm->flashStart, 0x10000, NULL, 0, sramCreateFilenameWithSuffix(filename, "", ".sram"));
    }

    for (i = 0; i < 4; i++) {   
        mapPage(rm, i, i);
    }

    return 1;
}
