/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperSunriseIDE.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-12-19 07:11:56 $
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
#include "romMapperSunriseIde.h"
#include "MediaDb.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "SunriseIde.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
    int deviceHandle;
    UInt8* romData;
    int slot;
    int sslot;
    int startPage;
    UInt32 romMask;

    SunriseIde* ide;
    int    ideEnabled;
    UInt8  readLatch;
    UInt8  writeLatch;
    int    romMapper;
} RomMapperSunriseIde;


static UInt8 reverse(UInt8 a)
{
	a = ((a & 0xF0) >> 4) | ((a & 0x0F) << 4);
	a = ((a & 0xCC) >> 2) | ((a & 0x33) << 2);
	a = ((a & 0xAA) >> 1) | ((a & 0x55) << 1);
	return a;
}


static void saveState(RomMapperSunriseIde* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperSunriseIde");

    saveStateSet(state, "ideEnabled", rm->ideEnabled);
    saveStateSet(state, "readLatch", rm->readLatch);
    saveStateSet(state, "writeLatch", rm->writeLatch);
    saveStateSet(state, "romMapper", rm->romMapper);

    saveStateClose(state);

    sunriseIdeSaveState(rm->ide);
}

static void loadState(RomMapperSunriseIde* rm)
{
    SaveState* state = saveStateOpenForRead("mapperSunriseIde");

    rm->ideEnabled = saveStateGet(state, "ideEnabled", 0);
    rm->readLatch = (UInt8)saveStateGet(state, "readLatch", 0);
    rm->writeLatch = (UInt8)saveStateGet(state, "writeLatch", 0);
    rm->romMapper = saveStateGet(state, "romMapper", 0);

    saveStateClose(state);
    
    sunriseIdeLoadState(rm->ide);
}

static void destroy(RomMapperSunriseIde* rm)
{
    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    sunriseIdeDestroy(rm->ide);

    free(rm->romData);
    free(rm);
}

static UInt8 read(RomMapperSunriseIde* rm, UInt16 address) 
{
	if (rm->ideEnabled && (address & 0x3e00) == 0x3c00) {
		if ((address & 1) == 0) {
	        UInt16 value = sunriseIdeRead(rm->ide);
	        rm->readLatch = value >> 8;
	        return value & 0xff;
        }
		return rm->readLatch;
	}

	if (rm->ideEnabled && (address & 0x3f00) == 0x3e00) {
        return sunriseIdeReadRegister(rm->ide, address & 0x0f);
	}
	if (address < 0x4000) {
		return rm->romData[address + rm->romMapper];
	}

    return 0xff;
}

static void write(RomMapperSunriseIde* rm, UInt16 address, UInt8 value) 
{
	if ((address & 0xBF04) == 0x0104) {
        rm->ideEnabled = value & 1;
        rm->romMapper = 0x4000 * (reverse(value & 0xf8) & rm->romMask);
		return;
	}

	if (rm->ideEnabled && (address & 0x3e00) == 0x3c00) {
		if ((address & 1) == 0) {
            rm->writeLatch = value;
		} 
        else {
            sunriseIdeWrite(rm->ide, (value << 8) | rm->writeLatch);
		}
		return;
	}
	if (rm->ideEnabled && ((address & 0x3f00) == 0x3e00)) {
		sunriseIdeWriteRegister(rm->ide, address & 0x0f, value);
		return;
	}
}

static void reset(RomMapperSunriseIde* rm) 
{
    rm->ideEnabled = 1;
    rm->romMapper = rm->romMask * 0x4000;
    rm->readLatch = 0;
    rm->writeLatch = 0;

    sunriseIdeReset(rm->ide);
}


int romMapperSunriseIdeCreate(char* filename, UInt8* romData, 
                          int size, int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    RomMapperSunriseIde* rm;
    int i;

    int origSize = size;
    
    size = 0x8000;
    while (size < origSize) {
        size *= 2;
    }

    rm = malloc(sizeof(RomMapperSunriseIde));

    rm->deviceHandle = deviceManagerRegister(ROM_SUNRISEIDE, &callbacks, rm);
    slotRegister(slot, sslot, startPage, 4, NULL, NULL, write, destroy, rm);

    rm->ide = sunriseIdeCreate();

    rm->romData = calloc(1, size);
    memcpy(rm->romData, romData, origSize);
    rm->romMask = size / 0x4000 - 1;
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;

    rm->romMapper = 0;

    for (i = 0; i < 4; i++) {   
        slotMapPage(rm->slot, rm->sslot, rm->startPage + i, NULL, 0, 0);
    }

    reset(rm);

    return 1;
}
