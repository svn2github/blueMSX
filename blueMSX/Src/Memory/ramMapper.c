/*****************************************************************************
** File:        ramMapper.c
**
** Author:      Daniel Vik
**
** Description: Ram mapper
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
#include "ramMapper.h"
#include "ramMapperIo.h"
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
    int handle;
    int slot;
    int sslot;
    int mask;
} RamMapper;

static void saveState(RamMapper* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperRam");
    
    saveStateSet(state, "mask", rm->mask);
    
    saveStateSetBuffer(state, "ramData", rm->ramData, 0x4000 * (rm->mask + 1));

    saveStateClose(state);
}

static void loadState(RamMapper* rm)
{
    SaveState* state = saveStateOpenForRead("mapperRam");
    int i;
    
    rm->mask = saveStateGet(state, "mask", 0);
    
    saveStateGetBuffer(state, "ramData", rm->ramData, 0x4000 * (rm->mask + 1));

    saveStateClose(state);

    for (i = 0; i < 4; i++) {
        slotMapPage(rm->slot, rm->sslot, 2 * i, rm->ramData + 0x4000 * (ramMapperIoGetPortValue(i) & rm->mask), 1, 1);
        slotMapPage(rm->slot, rm->sslot, 2 * i + 1, rm->ramData + 0x4000 * (ramMapperIoGetPortValue(i) & rm->mask) + 0x2000, 1, 1);
    }
}

static void write(RamMapper* rm, UInt16 page, UInt8 value)
{
    value &= rm->mask;

    slotMapPage(rm->slot, rm->sslot, 2 * page,     rm->ramData + 0x4000 * value, 1, 1);
    slotMapPage(rm->slot, rm->sslot, 2 * page + 1, rm->ramData + 0x4000 * value + 0x2000, 1, 1);
}

static void destroy(RamMapper* rm)
{
    ramMapperIoRemove(rm->handle);
    slotUnregister(rm->slot, rm->sslot, 0);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm);
}

int ramMapperCreate(int size, int slot, int sslot, int startPage, UInt8** ramPtr, UInt32* ramSize) 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    RamMapper* rm;
    int pages = size / 0x4000;
    int i;

    // Check that memory is a power of 2 and at least 64kB
    for (i = 4; i < pages; i <<= 1);

    if (i != pages) {
        return 0;
    }

    size = pages * 0x4000;

    // Start page must be zero (only full slot allowed)
    if (startPage != 0) {
        return 0;
    }

    rm = malloc(sizeof(RamMapper));

    rm->ramData = malloc(size);
    rm->slot    = slot;
    rm->sslot   = sslot;
    rm->mask    = pages - 1;

    memset(rm->ramData, 0xff, size);

    rm->handle  = ramMapperIoAdd(pages * 0x4000, write, rm);
    
    rm->deviceHandle = deviceManagerRegister(RAM_MAPPER, &callbacks, rm);
    slotRegister(slot, sslot, 0, 8, NULL, NULL, destroy, rm);

    for (i = 0; i < 4; i++) {
        slotMapPage(slot, sslot, 2 * i, rm->ramData + 0x4000 * (ramMapperIoGetPortValue(i) & rm->mask), 1, 1);
        slotMapPage(slot, sslot, 2 * i + 1, rm->ramData + 0x4000 * (ramMapperIoGetPortValue(i) & rm->mask) + 0x2000, 1, 1);
    }

    if (ramPtr != NULL) {
        *ramPtr = rm->ramData;
    }
    if (ramSize != NULL) {
        *ramSize = size;
    }

    return 1;
}
