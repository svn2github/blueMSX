/*****************************************************************************
** File:        romMapperMsxAudio.c
**
** Author:      Daniel Vik
**
** Description: Rom mapper for MSX audio cartridges with 1kB 4kB RAM
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
#include "romMapperMsxAudio.h"
#include "romMapper.h"
#include "Switches.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    int deviceHandle;
    UInt8* romData;
    UInt8 ram[0x1000];
    int bankSelect; 
    int sizeMask;
    int slot;
    int sslot;
    int startPage;
} RomMapperMsxAudio;

static void saveState(RomMapperMsxAudio* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperMsxAudio");

    saveStateSet(state, "bankSelect", rm->bankSelect);
    saveStateSetBuffer(state, "ram", rm->ram, sizeof(rm->ram));
    
    saveStateClose(state);
}

static void loadState(RomMapperMsxAudio* rm)
{
    SaveState* state = saveStateOpenForRead("mapperMsxAudio");

    rm->bankSelect = saveStateGet(state, "bankSelect", 0);
    saveStateGetBuffer(state, "ram", rm->ram, sizeof(rm->ram));

    saveStateClose(state);
}

static void destroy(RomMapperMsxAudio* rm)
{
    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm->romData);
    free(rm);
}

static UInt8 read(RomMapperMsxAudio* rm, UInt16 address) 
{
	if (rm->bankSelect == 0 && (address & 0x3fff) >= 0x3000) {
		return rm->ram[(address & 0x3fff) - 0x3000];
    }

	return rm->romData[(0x8000 * rm->bankSelect + (address & 0x7fff)) & rm->sizeMask];
}

static void write(RomMapperMsxAudio* rm, UInt16 address, UInt8 value) 
{
	address &= 0x7fff;
	if (address == 0x7ffe) {
		rm->bankSelect = value & 3;
	}
	address &= 0x3fff;
	if (rm->bankSelect == 0 && address >= 0x3000) {
		rm->ram[address - 0x3000] = value;
	}
}

int romMapperMsxAudioCreate(char* filename, UInt8* romData, 
                            int size, int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    RomMapperMsxAudio* rm;
    int i;

    if (size < 0x8000 || startPage != 0) {
        return 0;
    }

    rm = malloc(sizeof(RomMapperMsxAudio));

    rm->deviceHandle = deviceManagerRegister(ROM_MSXAUDIO, &callbacks, rm);
    slotRegister(slot, sslot, startPage, 8, read, write, destroy, rm);

    rm->romData = malloc(size);
    memcpy(rm->romData, romData, size);
    memset(rm->ram, 0, 0x1000);
    rm->bankSelect = 0;
    rm->sizeMask = size - 1;
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;

    if (!switchGetAudio()) {
        rm->romData[0x408e] = 0;
    }

    for (i = 0; i < 8; i++) {   
        slotMapPage(rm->slot, rm->sslot, rm->startPage + i, NULL, 0, 0);
    }

    return 1;
}

