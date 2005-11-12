/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/ram1kBMirrored.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2005-11-12 02:51:47 $
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
#include "ram1kBMirrored.h"
#include "MediaDb.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "DebugDeviceManager.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
    int deviceHandle;
    int debugHandle;
    int slot;
    int sslot;
    int startPage;
    int pages;
    UInt8 ramData[0x10000];
} Ram1kBMirrored;

static void saveState(Ram1kBMirrored* rm)
{
    SaveState* state = saveStateOpenForWrite("mapper1kBMirroredRam");

    saveStateSet(state, "pages", rm->pages);
    saveStateSetBuffer(state, "ramData", rm->ramData, 0x10000);

    saveStateClose(state);
}

static void loadState(Ram1kBMirrored* rm)
{
    SaveState* state = saveStateOpenForRead("mapper1kBMirroredRam");
    int i;

    rm->pages = saveStateGet(state, "pages", 0);
    saveStateGetBuffer(state, "ramData", rm->ramData, 0x10000);

    saveStateClose(state);
    
    for (i = 0; i < rm->pages; i++) {
        slotMapPage(rm->slot, rm->sslot, i + rm->startPage, rm->ramData + 0x2000 * i, 1, 1);
    }
}

static void destroy(Ram1kBMirrored* rm)
{
    debugDeviceUnregister(rm->debugHandle);

    slotUnregister(rm->slot, rm->sslot, 0);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm);
}

static void getDebugInfo(Ram1kBMirrored* rm, DbgDevice* dbgDevice)
{
    dbgDeviceAddMemoryBlock(dbgDevice, "Normal", 0, 0, 0x0400, rm->ramData);
}

static int dbgWriteMemory(Ram1kBMirrored* rm, char* name, void* data, int start, int size)
{
    if (strcmp(name, "Normal") || start + size > 0x400) {
        return 0;
    }

    memcpy(rm->ramData + start, data, size);

    return 1;
}

static void write(Ram1kBMirrored* rm, UInt16 address, UInt8 value) 
{
    address &= 0x3ff;

    rm->ramData[address + 0x0000] = value;
    rm->ramData[address + 0x0400] = value;
    rm->ramData[address + 0x0800] = value;
    rm->ramData[address + 0x0c00] = value;
    rm->ramData[address + 0x1000] = value;
    rm->ramData[address + 0x1400] = value;
    rm->ramData[address + 0x1800] = value;
    rm->ramData[address + 0x1c00] = value;
}

int ram1kBMirroredCreate(int size, int slot, int sslot, int startPage, UInt8** ramPtr, UInt32* ramSize) 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    DebugCallbacks dbgCallbacks = { getDebugInfo, dbgWriteMemory, NULL, NULL };
    Ram1kBMirrored* rm;
    int pages = size / 0x2000;
    int i;

    if (size > 0x10000 || (size & 0x1fff)) {
        return 0;
    }

    // Start page must be zero (only full slot allowed)
    if (startPage + pages > 8) {
        return 0;
    }

    rm = malloc(sizeof(Ram1kBMirrored));

    rm->slot      = slot;
    rm->sslot     = sslot;
    rm->startPage = startPage;
    rm->pages     = pages;

    memset(rm->ramData, 0xff, sizeof(rm->ramData));

    rm->debugHandle = debugDeviceRegister(DBGTYPE_RAM, "RAM", &dbgCallbacks, rm);

    for (i = 0; i < pages; i++) {
        slotMapPage(slot, sslot, i + startPage, rm->ramData + 0x2000 * i, 1, 0);
    }

    rm->deviceHandle = deviceManagerRegister(RAM_1KB_MIRRORED, &callbacks, rm);
    slotRegister(slot, sslot, startPage, pages, NULL, NULL, write, destroy, rm);

    if (ramPtr != NULL) {
        *ramPtr = rm->ramData;
    }

    if (ramSize != NULL) {
        *ramSize = 0x400;
    }

    return 1;
}

