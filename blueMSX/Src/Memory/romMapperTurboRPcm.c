/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperTurboRPcm.c,v $
**
** $Revision: 1.4 $
**
** $Date: 2004-12-12 22:18:27 $
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
#include "romMapperTurboRPcm.h"
#include "romMapper.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "Board.h"
#include "IoPort.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    DAC*   dac;
    int    deviceHandle;
    UInt8  sample;
    UInt8  status;
    UInt32 time;
} RomMapperTurboRPcm;

static void saveState(RomMapperTurboRPcm* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperTurboRPcm");

    saveStateSet(state, "sample", rm->sample);
    saveStateSet(state, "status", rm->status);
    saveStateSet(state, "time",   rm->time);
    
    saveStateClose(state);
}

static void loadState(RomMapperTurboRPcm* rm)
{
    SaveState* state = saveStateOpenForRead("mapperTurboRPcm");

    rm->sample = (UInt8)saveStateGet(state, "sample", 0);
    rm->status = (UInt8)saveStateGet(state, "status", 0);
    rm->time   =        saveStateGet(state, "time",   boardSystemTime());

    saveStateClose(state);
}

static void destroy(RomMapperTurboRPcm* rm)
{
    deviceManagerUnregister(rm->deviceHandle);

    ioPortUnregister(0xa4);
    ioPortUnregister(0xa5);

    free(rm);
}

static UInt8 read(RomMapperTurboRPcm* rm, UInt16 ioPort)
{
    switch (ioPort & 0x01) {
	case 0: 
		return (UInt8)(21000 * (UInt64)(boardSystemTime() - rm->time) / boardFrequency()) & 0x03;
	case 1:
		return (~rm->sample & 0x80) | rm->status;
    }
    return 0xff;
}

static void write(RomMapperTurboRPcm* rm, UInt16 ioPort, UInt8 value)
{
	switch (ioPort & 0x01) {
	case 0:
		rm->time   = boardSystemTime();// - boardFrequency() / 15750 / 4;
		rm->sample = value;
		if (rm->status & 0x02) {
            dacWrite(rm->dac, rm->sample);
		}
		break;

    case 1:
        if ((value & 0x03) == 0x03 && (~rm->status & 0x01)) {
            dacWrite(rm->dac, rm->sample);
		}
		rm->status = value & 0x1f;
        break;
    }
}

int romMapperTurboRPcmCreate(DAC* dac) 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    RomMapperTurboRPcm* rm = malloc(sizeof(RomMapperTurboRPcm));

    rm->deviceHandle = deviceManagerRegister(ROM_TURBORPCM, &callbacks, rm);

    rm->dac    = dac;
	rm->status = 0;
    rm->time   = boardSystemTime();

    ioPortRegister(0xa4, read, write, rm);
    ioPortRegister(0xa5, read, write, rm);

    return 1;
}

