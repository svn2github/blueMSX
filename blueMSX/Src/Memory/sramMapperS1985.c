/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/sramMapperS1985.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2004-12-06 07:47:12 $
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
#include "sramMapperMatsuchita.h"
#include "romMapper.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "IoPort.h"
#include "sramLoader.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern int frontSwitchEnabled();

typedef struct {
    int    deviceHandle;
    UInt8  sram[0x10];
    UInt32 address;
	UInt8  color1;
    UInt8  color2;
	UInt8  pattern;
} SramMapperS1985;

static void saveState(SramMapperS1985* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperS1985");

    saveStateSet(state, "address", rm->address);
    saveStateSet(state, "color1",  rm->color1);
    saveStateSet(state, "color2",  rm->color2);
    saveStateSet(state, "pattern", rm->pattern);
    
    saveStateClose(state);
}

static void loadState(SramMapperS1985* rm)
{
    SaveState* state = saveStateOpenForRead("mapperS1985");

    rm->address =        saveStateGet(state, "address", 0);
    rm->color1  = (UInt8)saveStateGet(state, "color1",  0);
    rm->color2  = (UInt8)saveStateGet(state, "color2",  0);
    rm->pattern = (UInt8)saveStateGet(state, "pattern", 0);

    saveStateClose(state);
}

static void destroy(SramMapperS1985* rm)
{
    sramSave(sramCreateFilename("Matsushita.SRAM"), rm->sram, 0x10, NULL, 0);

    deviceManagerUnregister(rm->deviceHandle);

    ioPortUnregisterSub(0x08);

    free(rm);
}

static UInt8 read(SramMapperS1985* rm, UInt16 ioPort)
{
	UInt8 result;
	switch (ioPort & 0x0f) {
	case 0:
		result = ~0xfe;
		break;
	case 2:
		result = rm->sram[rm->address];
		break;
	case 7:
		result = (rm->pattern & 0x80) ? rm->color2 : rm->color1;
		rm->pattern = (rm->pattern << 1) | (rm->pattern >> 7);
		break;
	default:
		result = 0xff;
	}

	return result;
}

static void write(SramMapperS1985* rm, UInt16 ioPort, UInt8 value)
{
	switch (ioPort & 0x0f) {
	case 1:
		rm->address = value & 0x0f;
		break;
	case 2:
		rm->sram[rm->address] = value;
		break;
	case 6:
		rm->color2 = rm->color1;
		rm->color1 = value;
		break;
	case 7:
		rm->pattern = value;
		break;
	}
}

int sramMapperS1985Create() 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    SramMapperS1985* rm;

    rm = malloc(sizeof(SramMapperS1985));

    rm->deviceHandle = deviceManagerRegister(SRAM_S1985, &callbacks, rm);
    memset(rm->sram, 0xff, 0x10);
    rm->address = 0;

    sramLoad(sramCreateFilename("Matsushita.SRAM"), rm->sram, 0x10, NULL, 0);

    ioPortRegisterSub(0xfe, read, write, rm);

    return 1;
}

