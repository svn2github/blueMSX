/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperKanji.c,v $
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
#include "romMapperKanji.h"
#include "romMapper.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "IoPort.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
    UInt8* romData;
    int deviceHandle;
    int size;
    UInt32 address[2];
} RomMapperKanji;

static void saveState(RomMapperKanji* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperKanji");

    saveStateSet(state, "address0", rm->address[0]);
    saveStateSet(state, "address1", rm->address[1]);
    
    saveStateClose(state);
}

static void loadState(RomMapperKanji* rm)
{
    SaveState* state = saveStateOpenForRead("mapperKanji");

    rm->address[0] = saveStateGet(state, "address0", 0);
    rm->address[1] = saveStateGet(state, "address1", 0);

    saveStateClose(state);
}

static void destroy(RomMapperKanji* rm)
{
    deviceManagerUnregister(rm->deviceHandle);

    ioPortUnregister(0xd9);
    ioPortUnregister(0xd8);
    ioPortUnregister(0xda);
    ioPortUnregister(0xdb);

    free(rm->romData);
    free(rm);
}

static UInt8 read(RomMapperKanji* rm, UInt16 ioPort)
{
    UInt32* reg = &rm->address[(ioPort & 2) >> 1];
    UInt8 value;

	if (reg == &rm->address[1] && rm->size != 0x40000) {
        return 0xff;
    }

    value = rm->romData[*reg];

    *reg = (*reg & ~0x1f) | ((*reg + 1) & 0x1f);

    return value;
}

static void write(RomMapperKanji* rm, UInt16 ioPort, UInt8 value)
{	
    switch (ioPort & 0x03) {
	case 0:
		rm->address[0] = (rm->address[0] & 0x1f800) | ((value & 0x3f) << 5);
		break;
	case 1:
		rm->address[0] = (rm->address[0] & 0x007e0) | ((value & 0x3f) << 11);
		break;
	case 2:
		rm->address[1] = (rm->address[1] & 0x3f800) | ((value & 0x3f) << 5);
		break;
	case 3:
		rm->address[1] = (rm->address[1] & 0x207e0) | ((value & 0x3f) << 11);
		break;
	}
}

int romMapperKanjiCreate(UInt8* romData, int size) 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    RomMapperKanji* rm;

	if (size != 0x20000 && size != 0x40000) {
        return 0;
    }

    rm = malloc(sizeof(RomMapperKanji));

    rm->size = size;
    rm->address[0] = 0;
    rm->address[1] = 0x20000;

    rm->deviceHandle = deviceManagerRegister(ROM_KANJI, &callbacks, rm);

    rm->romData = malloc(size);
    memcpy(rm->romData, romData, size);
    
    ioPortRegister(0xd8, NULL, write, rm);
    ioPortRegister(0xd9, read, write, rm);
    ioPortRegister(0xda, NULL, write, rm);
    ioPortRegister(0xdb, read, write, rm);

    return 1;
}

