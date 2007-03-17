/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperNoWind.c,v $
**
** $Revision: 1.6 $
**
** $Date: 2007-03-17 01:04:35 $
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
#include "romMapperNoWind.h"
#include "AmdFlash.h"
#include "MediaDb.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "Board.h"
#include "SaveState.h"
#include "sramLoader.h"
#include "ft245.h"
#include <stdlib.h>
#include <string.h>


typedef struct {
    int deviceHandle;
    AmdFlash* amdFlash;
    FT245*  ft245;
    int slot;
    int sslot;
    int startPage;
    UInt8 romMapper;
    UInt8* flashPage;
} RomMapperNoWind;




static void updateMapper(RomMapperNoWind* rm, UInt8 page)
{
    rm->romMapper = page & 0x1f;
    rm->flashPage = amdFlashGetPage(rm->amdFlash, rm->romMapper * 0x4000);

    slotMapPage(rm->slot, rm->sslot, rm->startPage + 0, NULL, 0, 0);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 1, NULL, 0, 0);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 2, rm->flashPage, 1, 0);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 3, rm->flashPage + 0x2000, 1, 0);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 4, NULL,          0, 0);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 5, rm->flashPage + 0x2000, 1, 0);
}


static void saveState(RomMapperNoWind* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperDumas");

    saveStateSet(state, "romMapper", rm->romMapper);

    saveStateClose(state);

    amdFlashSaveState(rm->amdFlash);
    ft245SaveState(rm->ft245);
}

static void loadState(RomMapperNoWind* rm)
{
    SaveState* state = saveStateOpenForRead("mapperDumas");

    rm->romMapper = (UInt8)saveStateGet(state, "romMapper", 0);

    saveStateClose(state);

    amdFlashLoadState(rm->amdFlash);

    ft245LoadState(rm->ft245);

    updateMapper(rm, rm->romMapper);
}

static void destroy(RomMapperNoWind* rm)
{
    amdFlashDestroy(rm->amdFlash);
    ft245Destroy(rm->ft245);
    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm);
}

static void reset(RomMapperNoWind* rm)
{
    amdFlashReset(rm->amdFlash);
    ft245Reset(rm->ft245);

    updateMapper(rm, 0);
}

static UInt8 read(RomMapperNoWind* rm, UInt16 address) 
{
    if (address >= 0x2000 && address < 0x4000) {
        return ft245Read(rm->ft245);
    }
    if (address >= 0x8000 && address < 0xa000) {
        return ft245Read(rm->ft245);
    }

    return 0xff;
}

static UInt8 peek(RomMapperNoWind* rm, UInt16 address) 
{
    if (address >= 0x2000 && address < 0x4000) {
        return ft245Peek(rm->ft245);
    }
    if (address >= 0x8000 && address < 0xa000) {
        return ft245Peek(rm->ft245);
    }

    return 0xff;
}

static void write(RomMapperNoWind* rm, UInt16 address, UInt8 value) 
{   
    if (address < 0x4000) {
        amdFlashWrite(rm->amdFlash, address + 0x4000 * rm->romMapper, value);
        return;
    }

    if ((address >= 0x4000 && address < 0x6000) || 
        (address >= 0x8000 && address < 0xa000)) 
    {
        ft245Write(rm->ft245, value);
        return;
    }

    if ((address >= 0x6000 && address < 0x8000) || 
        (address >= 0xa000 && address < 0xc000)) 
    {
        // FIXME: Is the page selected based on address or data lines?
        updateMapper(rm, value & 0x1f);
    }
}

int romMapperNoWindCreate(char* filename, UInt8* romData, 
                         int size, int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    RomMapperNoWind* rm;

    rm = malloc(sizeof(RomMapperNoWind));

    rm->deviceHandle = deviceManagerRegister(ROM_NOWIND, &callbacks, rm);
    slotRegister(slot, sslot, startPage, 6, read, peek, write, destroy, rm);

    rm->amdFlash = amdFlashCreate(AMD_TYPE_1, 0x80000, 0x10000, romData, size, sramCreateFilenameWithSuffix("nowind.rom", "", ".rom"));
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;

    rm->ft245 = ft245Create();

    reset(rm);

    return 1;
}

