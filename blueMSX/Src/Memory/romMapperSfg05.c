/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperSfg05.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2006-06-01 07:02:43 $
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
#include "romMapperSfg05.h"
#include "MediaDb.h"
#include "Switches.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "DebugDeviceManager.h"
#include "IoPort.h"
#include "Board.h"
#include "YM2151.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    int deviceHandle;
    int debugHandle;
    YM2151* ym2151;
    UInt8* romData; 
    int slot;
    int sslot;
    int startPage;
} RomMapperSfg05;

static int deviceCount = 0;

static void saveState(RomMapperSfg05* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperSfg05");
    
    saveStateClose(state);

    ym2151SaveState(rm->ym2151);
}

static void loadState(RomMapperSfg05* rm)
{
    SaveState* state = saveStateOpenForRead("mapperSfg05");

    saveStateClose(state);
    
    ym2151LoadState(rm->ym2151);
}

static void destroy(RomMapperSfg05* rm)
{
    deviceCount--;

    if (rm->ym2151 != NULL) {
        ym2151Destroy(rm->ym2151);
    }

    slotUnregister(rm->slot, rm->sslot, rm->startPage);

    debugDeviceUnregister(rm->debugHandle);
    deviceManagerUnregister(rm->deviceHandle);

    if (rm->romData != NULL) {
        free(rm->romData);
    }
    free(rm);
}

static UInt8 read(RomMapperSfg05* rm, UInt16 address) 
{
    if (address < 0x3ff0 || address >= 0x3ff8) {
    	return rm->romData[address & 0x7fff];
    }

//    printf("R %.2x\n", address);
    switch (address & 0x3fff) {
    case 0x3ff0:
        return ym2151Read(rm->ym2151, 0);
    case 0x3ff1:
        return ym2151Read(rm->ym2151, 1);
    }

    return 0xff;
}

static void reset(RomMapperSfg05* rm) 
{
    ym2151Reset(rm->ym2151);
}

static void write(RomMapperSfg05* rm, UInt16 address, UInt8 value) 
{
//    printf("W %.2x: %.2x\n", address, value);
    if (address < 0x3ff0 || address >= 0x3ff8) {
    	return;
    }

//    printf("W %.2x: %.2x\n", address, value);
    switch (address & 0x3fff) {
    case 0x3ff0:
        ym2151Write(rm->ym2151, 0, value);
        break;
    case 0x3ff1:
        ym2151Write(rm->ym2151, 1, value);
        break;
    }
}


static void getDebugInfo(RomMapperSfg05* rm, DbgDevice* dbgDevice)
{
    ym2151GetDebugInfo(rm->ym2151, dbgDevice);
}

int romMapperSfg05Create(char* filename, UInt8* romData, 
                            int size, int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    DebugCallbacks dbgCallbacks = { getDebugInfo, NULL, NULL, NULL };
    RomMapperSfg05* rm;
    int i;

    rm = malloc(sizeof(RomMapperSfg05));

    rm->deviceHandle = deviceManagerRegister(ROM_YAMAHASFG05, &callbacks, rm);
    rm->debugHandle = debugDeviceRegister(DBGTYPE_AUDIO, "Yamaha SFG-05", &dbgCallbacks, rm);

    slotRegister(slot, sslot, startPage, 4, read, read, write, destroy, rm);

    rm->romData = malloc(size);
    memcpy(rm->romData, romData, size);
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;

    for (i = 0; i < 4; i++) {
        slotMapPage(rm->slot, rm->sslot, rm->startPage + i, NULL, 0, 0);
    }

    rm->ym2151 = ym2151Create(boardGetMixer());

    reset(rm);

    return 1;
}
