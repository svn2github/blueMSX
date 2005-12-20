/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperGIDE.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-12-20 21:24:29 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2005 Daniel Vik, Tomas Karlsson
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
#include "romMapperGIDE.h"
#include "HarddiskIDE.h"
#include "MediaDb.h"
#include "DeviceManager.h"
#include "DebugDeviceManager.h"
#include "SaveState.h"
#include "IoPort.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    int deviceHandle;
    int debugHandle;
    HarddiskIde* hdide;
    UInt8 intEnable;
    UInt8 drvSelect;
    UInt8 altStatus;
} RomMapperGIde;

static void saveState(RomMapperGIde* rm)
{
    SaveState* state = saveStateOpenForWrite("RomMapperGIde");

    saveStateSet(state, "intEnable",  rm->intEnable);
    saveStateSet(state, "drvSelect",  rm->drvSelect);
    saveStateSet(state, "altStatus",  rm->altStatus);
    
    saveStateClose(state);

    harddiskIdeSaveState(rm->hdide);
}

static void loadState(RomMapperGIde* rm)
{
    SaveState* state = saveStateOpenForRead("RomMapperGIde");

    rm->intEnable  = (UInt8)saveStateGet(state, "intEnable",  0);
    rm->drvSelect  = (UInt8)saveStateGet(state, "drvSelect",  0);
    rm->altStatus  = (UInt8)saveStateGet(state, "altStatus",  0);

    saveStateClose(state);

    harddiskIdeLoadState(rm->hdide);
}

static void destroy(RomMapperGIde* rm)
{
    ioPortUnregister(0x44);
    ioPortUnregister(0x45);
    ioPortUnregister(0x46);
    ioPortUnregister(0x47);
    ioPortUnregister(0x48);
    ioPortUnregister(0x49);
    ioPortUnregister(0x4a);
    ioPortUnregister(0x4b);
    ioPortUnregister(0x4c);
    ioPortUnregister(0x4d);
    ioPortUnregister(0x4e);
    ioPortUnregister(0x4f);

    deviceManagerUnregister(rm->deviceHandle);
    debugDeviceUnregister(rm->debugHandle);

    harddiskIdeDestroy(rm->hdide);

    free(rm);
}

static UInt8 peekIo(RomMapperGIde* rm, UInt16 ioPort) 
{
    return 0xff;
}


static UInt8 readIo(RomMapperGIde* rm, UInt16 ioPort) 
{
	switch (ioPort)
	{
	case 0x44:			/* Reserved for expansion board */
		return 0xff;
	case 0x45:			/* RTC 72421 */
		return 0xff;
	case 0x46:			/* GIDE alternate status */
		return rm->altStatus;
	case 0x47:			/* GIDE drive address register */
		return rm->drvSelect;
	case 0x48:			/* IDE data register */
		return harddiskIdeReadRegister(rm->hdide, 0);
	case 0x49:			/* IDE error register */
		return harddiskIdeReadRegister(rm->hdide, 1);
	case 0x4a:			/* IDE sector count register */
		return harddiskIdeReadRegister(rm->hdide, 2);
	case 0x4b:			/* IDE sector number register */
		return harddiskIdeReadRegister(rm->hdide, 3);
	case 0x4c:			/* IDE cylinder low register */
		return harddiskIdeReadRegister(rm->hdide, 4);
	case 0x4d:			/* IDE cylinder high register */
		return harddiskIdeReadRegister(rm->hdide, 5);
	case 0x4e:			/* IDE drive/head register */
		return harddiskIdeReadRegister(rm->hdide, 6);
	case 0x4f:			/* IDE status register */
		rm->altStatus = harddiskIdeReadRegister(rm->hdide, 7);
		return rm->altStatus;

	}
	return 0xff;
}

static void writeIo(RomMapperGIde* rm, UInt16 ioPort, UInt8 value) 
{
	switch (ioPort)
	{
	case 0x44:			/* Reserved for expansion board */
		break; 
	case 0x45:			/* RTC 72421 */
		break; 
	case 0x46:			/* GIDE digital output register */
		rm->intEnable = value & 0x01?1:0;
		if (value & 0x02)
			harddiskIdeReset(rm->hdide);
		break; 
	case 0x47:			/* GIDE drive address register */
		break; 
	case 0x48:			/* IDE data register */
		harddiskIdeWriteRegister(rm->hdide, 0, value);
		break; 
	case 0x49:			/* IDE write precomp register */
		harddiskIdeWriteRegister(rm->hdide, 1, value);
		break; 
	case 0x4a:			/* IDE sector count register */
		harddiskIdeWriteRegister(rm->hdide, 2, value);
		break; 
	case 0x4b:			/* IDE sector number register */
		harddiskIdeWriteRegister(rm->hdide, 3, value);
		break; 
	case 0x4c:			/* IDE cylinder low register */
		harddiskIdeWriteRegister(rm->hdide, 4, value);
		break; 
	case 0x4d:			/* IDE cylinder high register */
		harddiskIdeWriteRegister(rm->hdide, 5, value);
		break; 
	case 0x4e:			/* IDE drive/head register */
		rm->drvSelect = value;
		harddiskIdeWriteRegister(rm->hdide, 6, value);
		break; 
	case 0x4f:			/* IDE command register */
		harddiskIdeWriteRegister(rm->hdide, 7, value);
		break; 
	}
}

static void reset(RomMapperGIde* rm)
{
    harddiskIdeReset(rm->hdide);
}

static void getDebugInfo(RomMapperGIde* rm, DbgDevice* dbgDevice)
{
    DbgIoPorts* ioPorts;
    int i;

    ioPorts = dbgDeviceAddIoPorts(dbgDevice, "GIDE", 12);
    for (i = 0; i < 12; i++) {
        dbgIoPortsAddPort(ioPorts, i, 0x44 + i, DBG_IO_READWRITE, peekIo(rm, 0x44 + i));
    }
}

int romMapperGIdeCreate(const char* fileName) 
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    DebugCallbacks dbgCallbacks = { getDebugInfo, NULL, NULL, NULL };
    RomMapperGIde* rm;

    rm = malloc(sizeof(RomMapperGIde));
    
//    rm->deviceHandle = deviceManagerRegister(ROM_GIDE, &callbacks, rm);
    rm->debugHandle = debugDeviceRegister(DBGTYPE_PORT, "GIDE", &dbgCallbacks, rm);

    ioPortRegister(0x44, readIo, writeIo, rm);
    ioPortRegister(0x45, readIo, writeIo, rm);
    ioPortRegister(0x46, readIo, writeIo, rm);
    ioPortRegister(0x47, readIo, writeIo, rm);
    ioPortRegister(0x48, readIo, writeIo, rm);
    ioPortRegister(0x49, readIo, writeIo, rm);
    ioPortRegister(0x4a, readIo, writeIo, rm);
    ioPortRegister(0x4b, readIo, writeIo, rm);
    ioPortRegister(0x4c, readIo, writeIo, rm);
    ioPortRegister(0x4d, readIo, writeIo, rm);
    ioPortRegister(0x4e, readIo, writeIo, rm);
    ioPortRegister(0x4f, readIo, writeIo, rm);

    rm->hdide = harddiskIdeCreate(fileName);

    reset(rm);

    return 1;
}

