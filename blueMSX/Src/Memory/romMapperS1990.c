/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperS1990.c,v $
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
#include "romMapper.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "Switches.h"
#include "IoPort.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern void msxSetCpu(int mode);

typedef struct {
    int   deviceHandle;
	UInt8 registerSelect;
	UInt8 cpuStatus;
} RomMapperS1990;

static void saveState(RomMapperS1990* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperS1990");

    saveStateSet(state, "registerSelect",  rm->registerSelect);
    saveStateSet(state, "cpuStatus",       rm->cpuStatus);
    
    saveStateClose(state);
}

static void loadState(RomMapperS1990* rm)
{
    SaveState* state = saveStateOpenForRead("mapperS1990");

    rm->registerSelect = (UInt8)saveStateGet(state, "registerSelect",  0);
    rm->cpuStatus      = (UInt8)saveStateGet(state, "cpuStatus",       0);

    saveStateClose(state);
}

static void destroy(RomMapperS1990* rm)
{
    deviceManagerUnregister(rm->deviceHandle);

    ioPortUnregister(0xe4);
    ioPortUnregister(0xe5);

    free(rm);
}

static void updateStatus(RomMapperS1990* rm, UInt8 value)
{
	rm->cpuStatus = value & 0x60;
    msxSetCpu((rm->cpuStatus & 0x20) ? 0 : 1);
}

static UInt8 read(RomMapperS1990* rm, UInt16 ioPort)
{
	switch (ioPort & 0x01) {
	case 0:
		return rm->registerSelect;
	case 1:
		switch (rm->registerSelect) {
		case 5:
			return switchGetFront() ? 0x40 : 0x00;
		case 6:
			return rm->cpuStatus;
		case 13:
			return 0x03;	//TODO
		case 14:
			return 0x2F;	//TODO
		case 15:
			return 0x8B;	//TODO
		default:
			return 0xFF;
		}
	}

    return 0;
}

static void write(RomMapperS1990* rm, UInt16 ioPort, UInt8 value)
{
	switch (ioPort & 0x01) {
	case 0:
		rm->registerSelect = value;
		break;
	case 1:
		switch (rm->registerSelect) {
		case 6:
			updateStatus(rm, value);
			break;
		}
		break;
    }
}

static void reset(RomMapperS1990* rm)
{
    rm->registerSelect = 0;
    updateStatus(rm, 96);
}

int romMapperS1990Create() 
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    RomMapperS1990* rm;

    rm = malloc(sizeof(RomMapperS1990));

    rm->deviceHandle = deviceManagerRegister(ROM_S1990, &callbacks, rm);

    ioPortRegister(0xe4, read, write, rm);
    ioPortRegister(0xe5, read, write, rm);

    reset(rm);

    return 1;
}

