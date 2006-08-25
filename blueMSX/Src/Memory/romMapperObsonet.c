/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperObsonet.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2006-08-25 06:27:07 $
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
#include "sramLoader.h"
#include <stdlib.h>
#include <string.h>


// Minimal AMD flash emulation to support the obsonet flash
// TODO: Use correct block size, currently its 16kB

typedef struct {
    UInt32 address;
    UInt8  value;
} AmdCmd;

typedef struct
{
    UInt8* romData;
    int    length;
    AmdCmd cmd[8];
    int    cmdIdx;
    char   sramFilename[512];
} AmdFlash;


static void checkCommandEraseSector(AmdFlash* rm) 
{
    if (rm->cmdIdx != 6) {
        return;
    }
    if ((rm->cmd[0].address & 0xfff) != 0xaaa || rm->cmd[0].value != 0xaa) return;
    if ((rm->cmd[1].address & 0xfff) != 0x555 || rm->cmd[1].value != 0x55) return;
    if ((rm->cmd[2].address & 0xfff) != 0xaaa || rm->cmd[2].value != 0x80) return;
    if ((rm->cmd[3].address & 0xfff) != 0xaaa || rm->cmd[3].value != 0xaa) return;
    if ((rm->cmd[4].address & 0xfff) != 0x555 || rm->cmd[4].value != 0x55) return;
    if (                                         rm->cmd[5].value != 0x30) return;

    memset(rm->romData + (rm->cmd[5].address & ~0x3fff & (rm->length - 1)), 0xff, 0x4000);
    rm->cmdIdx = 0;
}

static void checkCommandEraseChip(AmdFlash* rm) 
{
    if (rm->cmdIdx != 6) {
        return;
    }
    if ((rm->cmd[0].address & 0xfff) != 0xaaa || rm->cmd[0].value != 0xaa) return;
    if ((rm->cmd[1].address & 0xfff) != 0x555 || rm->cmd[1].value != 0x55) return;
    if ((rm->cmd[2].address & 0xfff) != 0xaaa || rm->cmd[2].value != 0x80) return;
    if ((rm->cmd[3].address & 0xfff) != 0xaaa || rm->cmd[3].value != 0xaa) return;
    if ((rm->cmd[4].address & 0xfff) != 0x555 || rm->cmd[4].value != 0x55) return;
    if (                                         rm->cmd[5].value != 0x10) return;

    memset(rm->romData, 0xff, rm->length);
    rm->cmdIdx = 0;
}

static void checkCommandProgram(AmdFlash* rm) 
{
    if (rm->cmdIdx != 4) {
        return;
    }

    if ((rm->cmd[0].address & 0xfff) != 0xaaa || rm->cmd[0].value != 0xaa) return;
    if ((rm->cmd[1].address & 0xfff) != 0x555 || rm->cmd[1].value != 0x55) return;
    if ((rm->cmd[2].address & 0xfff) != 0xaaa || rm->cmd[2].value != 0xa0) return;

    rm->romData[rm->cmd[3].address & (rm->length - 1)] &= rm->cmd[3].value;
    rm->cmdIdx = 0;
}

void amdFlashWrite(AmdFlash* rm, UInt32 address, UInt8 value)
{
    if (rm->cmdIdx < sizeof(rm->cmd) / sizeof(rm->cmd[0])) {
        rm->cmd[rm->cmdIdx].address = address;
        rm->cmd[rm->cmdIdx].value   = value;
        rm->cmdIdx++;
        checkCommandEraseSector(rm);
        checkCommandProgram(rm);
        checkCommandEraseChip(rm);
    }
}

UInt8* amdFlashGetPage(AmdFlash* rm, UInt32 address)
{
    return rm->romData + address;
}

void amdFlashReset(AmdFlash* rm)
{
    rm->cmdIdx = 0;
}

static void amdFlashSaveState(AmdFlash* rm)
{
    SaveState* state = saveStateOpenForWrite("amdFlash");

    saveStateClose(state);
}

static void amdFlashLoadState(AmdFlash* rm)
{
    SaveState* state = saveStateOpenForRead("amdFlash");

    saveStateClose(state);
}

AmdFlash* amdFlashCreate(int flashSize, void* romData, int size, char* sramFilename)
{
    AmdFlash* rm = (AmdFlash*)calloc(1, sizeof(AmdFlash));
    
    if (sramFilename != NULL) {
        strcpy(rm->sramFilename, sramFilename);
    }

    rm->length = flashSize;

    rm->romData = malloc(flashSize);
    if (size >= flashSize) {
        size = flashSize;
    }
    memcpy(rm->romData, romData, size);
    memset(rm->romData + size, 0xff, flashSize - size);

    return rm;
}

void amdFlashDestroy(AmdFlash* rm)
{
    if (rm->sramFilename[0]) {
        sramSave(rm->sramFilename, rm->romData, rm->length, NULL, 0);
    }
}

//////////////////////////////////////////////////////////


typedef struct {
    int deviceHandle;
    AmdFlash* amdFlash;
    int slot;
    int sslot;
    int startPage;
    UInt8 romMapper;
    UInt8 regBank;
    UInt8* flashPage;
} RomMapperObsonet;



static void saveState(RomMapperObsonet* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperObsonet");

    saveStateSet(state, "romMapper", rm->romMapper);
    saveStateSet(state, "regBank", rm->regBank);

    saveStateClose(state);

    amdFlashSaveState(rm->amdFlash);
}

static void loadState(RomMapperObsonet* rm)
{
    SaveState* state = saveStateOpenForRead("mapperObsonet");

    rm->romMapper = (UInt8)saveStateGet(state, "romMapper", 0);
    rm->regBank = (UInt8)saveStateGet(state, "regBank", 0);

    saveStateClose(state);

    amdFlashLoadState(rm->amdFlash);

    rm->flashPage = amdFlashGetPage(rm->amdFlash, rm->romMapper * 0x4000);

    slotMapPage(rm->slot, rm->sslot, rm->startPage + 0, rm->flashPage, 1, 0);
}

static void destroy(RomMapperObsonet* rm)
{
    amdFlashDestroy(rm->amdFlash);
    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm);
}

static void reset(RomMapperObsonet* rm)
{
    rm->regBank   = 0;
    rm->romMapper = 0;
    amdFlashReset(rm->amdFlash);
}

static UInt8 read(RomMapperObsonet* rm, UInt16 address) 
{
    if ((address & 0x3fe0) == 0x3fe0) {
        printf("R %d: %.4x\n", rm->regBank, address & 0x1f);
        // The register reads should return the values from the ethernet controller.
        // This is just test code.
        switch (address & 0x1f) {
        case 0:
            return rm->regBank << 6;
        case 2:
            if (rm->regBank == 3) {
                return rm->romMapper;
            }
            break;
        case 10:
            if (rm->regBank == 0) {
                return 0x50;
            }
            break;
        case 11:
            if (rm->regBank == 0) {
                return 0x70;
            }
            break;
        }
        return 0xff;
    }

    if (address < 0x4000) {
        // This is reads to 0x6000-0x7FDF, rest are directly mapped
        return rm->flashPage[address];
    }

    return 0xff;
}

static UInt8 peek(RomMapperObsonet* rm, UInt16 address) 
{
    
    if ((address & 0x3fe0) == 0x3fe0) return 0xff;
    return read(rm, address);
}

static void write(RomMapperObsonet* rm, UInt16 address, UInt8 value) 
{
    if ((address & 0x3fe0) == 0x3fe0) {
        printf("W %d: %.4x  %.2x\n", rm->regBank, address & 0x1f, value);
        switch (address & 0x1f) {
        case 0:
            rm->regBank = value >> 6;
            break;
        case 2:
            if (rm->regBank == 3) {
                rm->romMapper = value & 0x1f;
                rm->flashPage = amdFlashGetPage(rm->amdFlash, rm->romMapper * 0x4000);
                slotMapPage(rm->slot, rm->sslot, rm->startPage + 0, rm->flashPage, 1, 0);
            }
        }
    }
    else if (address < 0x4000) {
        amdFlashWrite(rm->amdFlash, address + 0x4000 * rm->romMapper, value);
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

    rm->amdFlash = amdFlashCreate(0x80000, romData, size, sramCreateFilenameWithSuffix("obsonet.rom", "", ".rom"));
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;

    rm->flashPage = amdFlashGetPage(rm->amdFlash, 0);

    slotMapPage(rm->slot, rm->sslot, rm->startPage + 0, rm->flashPage, 1, 0);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 1, NULL, 0, 0);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 2, NULL, 0, 0);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 3, NULL, 0, 0);

    reset(rm);

    return 1;
}

