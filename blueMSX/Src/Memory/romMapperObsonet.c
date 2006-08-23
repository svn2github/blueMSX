/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperObsonet.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2006-08-23 21:11:36 $
**
** More info: http://www.bluemsx.com
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
#include "romMapperObsonet.h"
#include "MediaDb.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "Board.h"
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
    UInt8 romMapper;
    UInt8 regBank;
} RomMapperObsonet;

static void saveState(RomMapperObsonet* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperObsonet");

    saveStateSet(state, "romMapper", rm->romMapper);
    saveStateSet(state, "regBank", rm->regBank);

    saveStateClose(state);
}

static void loadState(RomMapperObsonet* rm)
{
    SaveState* state = saveStateOpenForRead("mapperObsonet");

    rm->romMapper = (UInt8)saveStateGet(state, "romMapper", 0);
    rm->regBank = (UInt8)saveStateGet(state, "regBank", 0);

    saveStateClose(state);
    
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 0, rm->romData + rm->romMapper * 0x4000, 1, 0);
}

static void destroy(RomMapperObsonet* rm)
{
    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm->romData);
    free(rm);
}

static void reset(RomMapperObsonet* rm)
{
    rm->regBank   = 0;
    rm->romMapper = 0;
}

static UInt8 read(RomMapperObsonet* rm, UInt16 address) 
{
    if (address < 0x4000) {
        return rm->romData[rm->romMapper * 0x4000 + address];
    }
    return 0xff;
}

static UInt8 peek(RomMapperObsonet* rm, UInt16 address) 
{
    if ((address & 0x3fe0) == 0x3fe0) {
        // The register reads should return the values from the ethernet controller.
        // This is just test code.
        switch (address & 0x1f) {
        case 0:
            return rm->regBank << 6;
        case 2:
            if (rm->regBank == 3) {
                return rm->romMapper;
            }
        }
        return 0xff;
    }

    if (address < 0x4000) {
        // This is reads to 0x6000-0x7FDF, rest are directly mapped
        return rm->romData[rm->romMapper * 0x4000 + address];
    }

    return 0xff;
}

static void write(RomMapperObsonet* rm, UInt16 address, UInt8 value) 
{
    if ((address & 0x3fe0) == 0x3fe0) {
        switch (address & 0x1f) {
        case 0:
            rm->regBank = value >> 6;
            break;
        case 2:
            if (rm->regBank == 3) {
                rm->romMapper = value & 0x1f;
                slotMapPage(rm->slot, rm->sslot, rm->startPage + 0, rm->romData + rm->romMapper * 0x4000, 1, 0);
            }
        }
    }
}

int romMapperObsonetCreate(char* filename, UInt8* romData, 
                           int size, int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    RomMapperObsonet* rm;

    rm = malloc(sizeof(RomMapperObsonet));

    rm->deviceHandle = deviceManagerRegister(ROM_OBSONET, &callbacks, rm);
    slotRegister(slot, sslot, startPage, 4, read, peek, write, destroy, rm);

    rm->romData = malloc(0x80000);
    if (size >= 0x80000) {
        size = 0x80000;
    }
    memcpy(rm->romData, romData, size);
    memset(rm->romData + size, 0xff, 0x80000 - size);
    rm->size = size;
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;

    slotMapPage(rm->slot, rm->sslot, rm->startPage + 0, rm->romData, 1, 0);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 1, NULL, 0, 0);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 2, NULL, 0, 0);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 3, NULL, 0, 0);

    reset(rm);

    return 1;
}

