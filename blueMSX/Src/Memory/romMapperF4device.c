/*****************************************************************************
** File:        romMapperF4device.c
**
** Author:      Daniel Vik
**
** Description: Rom mapper for Kanji cartridges
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
#include "romMapperF4device.h"
#include "romMapper.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "IoPort.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    int deviceHandle;
    int inverted;
    int status;
} RomMapperF4device;

static void saveState(RomMapperF4device* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperF4device");

    saveStateSet(state, "status", rm->status);

    saveStateClose(state);
}

static void loadState(RomMapperF4device* rm)
{
    SaveState* state = saveStateOpenForRead("mapperF4device");
    
    rm->status = saveStateGet(state, "status", 0);

    saveStateClose(state);
}

static void destroy(RomMapperF4device* rm)
{
    deviceManagerUnregister(rm->deviceHandle);

    ioPortUnregister(0xf4);

    free(rm);
}

static UInt8 read(RomMapperF4device* rm, UInt16 ioPort)
{
    return rm->status;
}

static void write(RomMapperF4device* rm, UInt16 ioPort, UInt8 value)
{	
	if (rm->inverted) {
		rm->status = value | 0x7f;
	} 
    else {
		rm->status = (rm->status & 0x20) | (value & 0x20);
	}
}

int romMapperF4deviceCreate(int inverted) 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    RomMapperF4device* rm = malloc(sizeof(RomMapperF4device));

    rm->status = inverted ? 0xff : 0;

    rm->inverted   = inverted;
    rm->deviceHandle = deviceManagerRegister(inverted ? ROM_F4INVERTED : ROM_F4DEVICE, &callbacks, rm);

    ioPortRegister(0xf4, read, write, rm);

    return 1;
}

