/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperKonamiSynth.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2004-12-06 07:47:11 $
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
#include "romMapperKonamiSynth.h"
#include "romMapper.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
    int deviceHandle;
    UInt8* romData;
	DAC* dac;
    int slot;
    int sslot;
    int startPage;
} RomMapperKonamiSynth;

static void destroy(RomMapperKonamiSynth* rm)
{
    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm->romData);
    free(rm);
}

static void write(RomMapperKonamiSynth* rm, UInt16 address, UInt8 value) 
{
	address += 0x4000;

	if ((address & 0xc010) == 0x4000) {
        dacWrite(rm->dac, value);
	}
}

int romMapperKonamiSynthCreate(char* filename, UInt8* romData, 
                               int size, int slot, int sslot, int startPage, DAC* dac) 
{
    DeviceCallbacks callbacks = { destroy, NULL, NULL, NULL };
    RomMapperKonamiSynth* rm;
    int i;

    if (size != 0x8000) {
        return 0;
    }

    rm = malloc(sizeof(RomMapperKonamiSynth));

    rm->deviceHandle = deviceManagerRegister(ROM_KONAMISYNTH, &callbacks, rm);
    slotRegister(slot, sslot, startPage, 4, NULL, write, destroy, rm);

    rm->romData = malloc(size);
    memcpy(rm->romData, romData, size);
    rm->dac   = dac;
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;

    for (i = 0; i < 4; i++) {   
        slotMapPage(rm->slot, rm->sslot, rm->startPage + i, rm->romData + i * 0x2000, 1, 0);
    }

    return 1;
}

