/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperMsxAudio.c,v $
**
** $Revision: 1.5 $
**
** $Date: 2005-02-11 04:38:28 $
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
#include "romMapperMsxAudio.h"
#include "MediaDb.h"
#include "Switches.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "IoPort.h"
#include "Board.h"
#include "Y8950.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    int deviceHandle;
    Y8950* y8950;
    int ioBase;
    UInt8* romData;
    UInt8 ram[0x1000];
    int bankSelect; 
    int sizeMask;
    int slot;
    int sslot;
    int startPage;
} RomMapperMsxAudio;

static int deviceCount = 0;

static void saveState(RomMapperMsxAudio* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperMsxAudio");

    saveStateSet(state, "bankSelect", rm->bankSelect);
    saveStateSetBuffer(state, "ram", rm->ram, sizeof(rm->ram));
    
    saveStateClose(state);

    if (rm->y8950 != NULL) {
        y8950SaveState(rm->y8950);
    }
}

static void loadState(RomMapperMsxAudio* rm)
{
    SaveState* state = saveStateOpenForRead("mapperMsxAudio");

    rm->bankSelect = saveStateGet(state, "bankSelect", 0);
    saveStateGetBuffer(state, "ram", rm->ram, sizeof(rm->ram));

    saveStateClose(state);
    
    if (rm->y8950 != NULL) {
        y8950LoadState(rm->y8950);
    }
}

static void destroy(RomMapperMsxAudio* rm)
{
    ioPortUnregister(rm->ioBase + 0);
    ioPortUnregister(rm->ioBase + 1);

    deviceCount--;

    if (rm->y8950 != NULL) {
        y8950Destroy(rm->y8950);
    }

    if (rm->sizeMask != -1) {
        slotUnregister(rm->slot, rm->sslot, rm->startPage);
    }

    deviceManagerUnregister(rm->deviceHandle);

    if (rm->romData != NULL) {
        free(rm->romData);
    }
    free(rm);
}

static UInt8 read(RomMapperMsxAudio* rm, UInt16 address) 
{
	if (rm->bankSelect == 0 && (address & 0x3fff) >= 0x3000) {
		return rm->ram[(address & 0x3fff) - 0x3000];
    }

	return rm->romData[(0x8000 * rm->bankSelect + (address & 0x7fff)) & rm->sizeMask];
}

static void reset(RomMapperMsxAudio* rm) 
{
    if (rm->y8950 != NULL) {
        y8950Reset(rm->y8950);
    }
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
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    RomMapperMsxAudio* rm;
    int i;

    rm = malloc(sizeof(RomMapperMsxAudio));

    rm->deviceHandle = deviceManagerRegister(ROM_MSXAUDIO, &callbacks, rm);

    rm->ioBase = 0xc0 + deviceCount++ * 2;

    rm->romData = NULL;

    if (size > 0) {
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
    }

    rm->y8950 = NULL;

    if (boardGetY8950Enable()) {
        rm->y8950 = y8950Create(boardGetMixer());
        ioPortRegister(rm->ioBase + 0, y8950Read, y8950Write, rm->y8950);
        ioPortRegister(rm->ioBase + 1, y8950Read, y8950Write, rm->y8950);
    }

    reset(rm);

    return 1;
}

