/*****************************************************************************
** File:        ramNormal.c
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
#include "ramNormal.h"
#include "romMapper.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
    int deviceHandle;
    int slot;
    int sslot;
    int startPage;
    int pages;
    UInt8 ramData[0x10000];
} RamNormal;

static void saveState(RamNormal* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperNormalRam");

    saveStateSet(state, "pages", rm->pages);
    saveStateSetBuffer(state, "ramData", rm->ramData, rm->pages * 0x2000);

    saveStateClose(state);
}

static void loadState(RamNormal* rm)
{
    SaveState* state = saveStateOpenForRead("mapperNormalRam");
    int i;

    rm->pages = saveStateGet(state, "pages", 0);
    
    saveStateGetBuffer(state, "ramData", rm->ramData, rm->pages * 0x2000);

    saveStateClose(state);

    for (i = 0; i < rm->pages; i++) {
        slotMapPage(rm->slot, rm->sslot, i + rm->startPage, rm->ramData + 0x2000 * i, 1, 1);
    }
}

static void destroy(void* ref)
{
    RamNormal* rm = (RamNormal*)ref;

    slotUnregister(rm->slot, rm->sslot, 0);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm);
}

int ramNormalCreate(int size, int slot, int sslot, int startPage, UInt8** ramPtr, UInt32* ramSize) 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    RamNormal* rm;
    int pages = size / 0x2000;
    int i;

    if (size > 0x10000 || (size & 0x1fff)) {
        return 0;
    }

    // Start page must be zero (only full slot allowed)
    if (startPage + pages > 8) {
        return 0;
    }

    rm = malloc(sizeof(RamNormal));

    rm->slot      = slot;
    rm->sslot     = sslot;
    rm->startPage = startPage;
    rm->pages     = pages;

    memset(rm->ramData, 0xff, sizeof(rm->ramData));

    for (i = 0; i < pages; i++) {
        slotMapPage(slot, sslot, i + startPage, rm->ramData + 0x2000 * i, 1, 1);
    }

    rm->deviceHandle = deviceManagerRegister(RAM_NORMAL, &callbacks, rm);
    slotRegister(slot, sslot, startPage, pages, NULL, NULL, destroy, rm);

    if (ramPtr != NULL) {
        *ramPtr = rm->ramData;
    }

    if (ramSize != NULL) {
        *ramSize = pages * 0x2000;
    }

    return 1;
}
