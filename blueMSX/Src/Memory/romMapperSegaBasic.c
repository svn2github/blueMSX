/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperSegaBasic.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2006-08-31 22:32:06 $
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
#include "romMapperSegaBasic.h"
#include "MediaDb.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "DebugDeviceManager.h"
#include "Language.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
    int deviceHandle;
    int debugHandle;
    UInt8* romData;
    UInt8 ram[0x8000];
    int slot;
    int sslot;
    int startPage;
} RomMapperSegaBasic;

static void saveState(RomMapperSegaBasic* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperSegaBasic");

    saveStateSetBuffer(state, "ram", rm->ram, 0x8000);

    saveStateClose(state);
}

static void loadState(RomMapperSegaBasic* rm)
{
    SaveState* state = saveStateOpenForRead("mapperSegaBasic");

    saveStateGetBuffer(state, "ram", rm->ram, 0x8000);

    saveStateClose(state);
}

static void destroy(RomMapperSegaBasic* rm)
{
    debugDeviceUnregister(rm->debugHandle);

    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm->romData);
    free(rm);
}

static void getDebugInfo(RomMapperSegaBasic* rm, DbgDevice* dbgDevice)
{
    dbgDeviceAddMemoryBlock(dbgDevice, langDbgMemRamNormal(), 0, 0, 0x8000, rm->ram);
}

static int dbgWriteMemory(RomMapperSegaBasic* rm, char* name, void* data, int start, int size)
{
    if (strcmp(name, "Normal") || start + size >= 0x8000) {
        return 0;
    }

    memcpy(rm->ram+ start, data, size);

    return 1;
}

int romMapperSegaBasicCreate(char* filename, UInt8* romData, 
                          int size, int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    DebugCallbacks dbgCallbacks = { getDebugInfo, dbgWriteMemory, NULL, NULL };
    RomMapperSegaBasic* rm;
    int pages = size / 0x2000 + ((size & 0x1fff) ? 1 : 0);
    int i;

    if (size != 0x8000 || startPage != 0) {
        return 0;
    }

    rm = malloc(sizeof(RomMapperSegaBasic));

    rm->deviceHandle = deviceManagerRegister(ROM_SEGABASIC, &callbacks, rm);
    
    rm->debugHandle = debugDeviceRegister(DBGTYPE_RAM, langDbgDevRam(), &dbgCallbacks, rm);

    slotRegister(slot, sslot, startPage, pages, NULL, NULL, NULL, destroy, rm);

    rm->romData = malloc(pages * 0x2000);
    memcpy(rm->romData, romData, size);
    memset(rm->ram, 0xff, 0x2000);

    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;
    
    for (i = 0; i < pages; i++) {
        if (i + startPage >= 2) slot = 0;
        slotMapPage(slot, sslot, i + startPage, rm->romData + 0x2000 * i, 1, 0);
        
    }
    
    for (; i < 8; i++) {
        slotMapPage(0, 0, i, rm->ram + 0x2000 * (i - 4), 1, 1);
    }

    return 1;
}

