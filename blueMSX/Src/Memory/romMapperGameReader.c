/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperGameReader.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-10-30 01:49:54 $
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
#include "romMapperGameReader.h"
#include "MediaDb.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "IoPort.h"
#include "GameReader.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define HISTORY_LENGTH 0x40

#define CACHE_LINE_BITS 10
#define CACHE_LINES     (0x10000 >> CACHE_LINE_BITS)
#define CACHE_LINE_SIZE (1 << CACHE_LINE_BITS)

typedef struct {
    int deviceHandle;
    GrHandle* gameReader;
    int slot;
    int sslot;
    int cartSlot;
    int cacheLineEnabled[CACHE_LINES];
    UInt8 cacheLineData[CACHE_LINES][1 << CACHE_LINE_BITS];
} RomMapperGameReader;

static void saveState(RomMapperGameReader* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperGameReader");
    saveStateClose(state);
}

static void loadState(RomMapperGameReader* rm)
{
    SaveState* state = saveStateOpenForRead("mapperGameReader");
    saveStateClose(state);
}


static void destroy(RomMapperGameReader* rm)
{
    if (rm->gameReader != NULL) {
        gameReaderDestroy(rm->gameReader);
        ioPortUnregisterUnused(rm->cartSlot);
        slotUnregister(rm->slot, rm->sslot, 0);
    }
    deviceManagerUnregister(rm->deviceHandle);

    free(rm);
}

static UInt8 readIo(RomMapperGameReader* rm, UInt16 port)
{
    UInt8 value = 0xff;

    if ((port & 0xf8) == 0xb8 ||
        (port & 0xf8) == 0xd8 ||
        (port & 0xfc) == 0x80 ||
        (port & 0xf0) == 0xf0)
    {
        return 0xff;
    }

    if (!gameReaderReadIo(rm->gameReader, port, &value)) {
        return 0xff;
    }

    return value;
}

static void writeIo(RomMapperGameReader* rm, UInt16 port, UInt8 value)
{
    if ((port & 0xf8) == 0xb8 ||
        (port & 0xf8) == 0xd8 ||
        (port & 0xfc) == 0x80 ||
        (port & 0xf0) == 0xf0)
    {
        return;
    }
    gameReaderWriteIo(rm->gameReader, port, value);
}

static UInt8 read(RomMapperGameReader* rm, UInt16 address) 
{
    int bank = address >> CACHE_LINE_BITS;
    if (!rm->cacheLineEnabled[bank]) {
        if (!gameReaderRead(rm->gameReader, bank << CACHE_LINE_BITS, rm->cacheLineData[bank], CACHE_LINE_SIZE)) {
            memset(rm->cacheLineData[bank], 0xff, CACHE_LINE_SIZE);
        }
        rm->cacheLineEnabled[bank] = 1;
    }

    return rm->cacheLineData[bank][address & (CACHE_LINE_SIZE - 1)];
}


static void write(RomMapperGameReader* rm, UInt16 address, UInt8 value) 
{
    int bank = address >> 13;
    int i;

    for (i = 0; i < CACHE_LINES; i++) {
        rm->cacheLineEnabled[i] = 0;
    }
    
    gameReaderWrite(rm->gameReader, address, &value, 1);
}

int romMapperGameReaderCreate(int cartSlot, int slot, int sslot) 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    RomMapperGameReader* rm;
    int i;

    rm = malloc(sizeof(RomMapperGameReader));

    rm->deviceHandle = deviceManagerRegister(ROM_KONAMI4, &callbacks, rm);

    rm->slot     = slot;
    rm->sslot    = sslot;
    rm->cartSlot = cartSlot;

    rm->gameReader = gameReaderCreate(cartSlot);

    for (i = 0; i < CACHE_LINES; i++) {
        rm->cacheLineEnabled[i] = 0;
    }

    if (rm->gameReader != NULL) {
        ioPortRegisterUnused(cartSlot, readIo, writeIo, rm);
        slotRegister(slot, sslot, 0, 8, read, read, write, destroy, rm);
        for (i = 0; i < 8; i++) {   
            slotMapPage(rm->slot, rm->sslot, i, NULL, 0, 0);
        }
    }

    return 1;
}

