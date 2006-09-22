/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/AmdFlash.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2006-09-22 06:18:42 $
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
#include "AmdFlash.h"
#include "SaveState.h"
#include "sramLoader.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


// Minimal AMD flash emulation to support the obsonet flash

typedef struct {
    UInt32 address;
    UInt8  value;
} AmdCmd;

struct AmdFlash
{
    UInt8* romData;
    int    flashSize;
    int    sectorSize;
    AmdCmd cmd[8];
    int    cmdIdx;
    char   sramFilename[512];
};


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

    memset(rm->romData + (rm->cmd[5].address & ~(rm->sectorSize - 1) & (rm->flashSize - 1)), 0xff, rm->sectorSize);
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

    memset(rm->romData, 0xff, rm->flashSize);
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

    rm->romData[rm->cmd[3].address & (rm->flashSize - 1)] &= rm->cmd[3].value;
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

void amdFlashSaveState(AmdFlash* rm)
{
    SaveState* state = saveStateOpenForWrite("amdFlash");
    int i;

    for (i = 0; i < 8; i++) {
        char buf[32];
        sprintf(buf, "cmd_%d_address", i);
        saveStateSet(state, buf,   rm->cmd[i].address);
        sprintf(buf, "cmd_%d_value", i);
        saveStateSet(state, buf,   rm->cmd[i].value);
    }

    saveStateSet(state, "cmdIdx",   rm->cmdIdx);

    saveStateClose(state);
}

void amdFlashLoadState(AmdFlash* rm)
{
    SaveState* state = saveStateOpenForRead("amdFlash");
    int i;

    for (i = 0; i < 8; i++) {
        char buf[32];
        sprintf(buf, "cmd_%d_address", i);
        rm->cmd[i].address = saveStateGet(state, buf,   0);
        sprintf(buf, "cmd_%d_value", i);
        rm->cmd[i].value = (UInt8)saveStateGet(state, buf,   0);
    }

    rm->cmdIdx = saveStateGet(state, "cmdIdx", 0);

    saveStateClose(state);
}

AmdFlash* amdFlashCreate(int flashSize, int sectorSize, void* romData, int size, char* sramFilename)
{
    AmdFlash* rm = (AmdFlash*)calloc(1, sizeof(AmdFlash));
    
    if (sramFilename != NULL) {
        strcpy(rm->sramFilename, sramFilename);
    }

    rm->flashSize = flashSize;
    rm->sectorSize = sectorSize;

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
        sramSave(rm->sramFilename, rm->romData, rm->flashSize, NULL, 0);
    }
    free(rm);
}
