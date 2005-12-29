/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperGIDE.c,v $
**
** $Revision: 1.7 $
**
** $Date: 2005-12-29 06:54:11 $
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
#include "Board.h"
#include "Disk.h"
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
    int portBase;

    if (boardGetType() == BOARD_SVI)
        portBase = 0x40;
    else
        portBase = 0x60;

    ioPortUnregister(portBase + 0x04);
    ioPortUnregister(portBase + 0x05);
    ioPortUnregister(portBase + 0x06);
    ioPortUnregister(portBase + 0x07);
    ioPortUnregister(portBase + 0x08);
    ioPortUnregister(portBase + 0x09);
    ioPortUnregister(portBase + 0x0a);
    ioPortUnregister(portBase + 0x0b);
    ioPortUnregister(portBase + 0x0c);
    ioPortUnregister(portBase + 0x0d);
    ioPortUnregister(portBase + 0x0e);
    ioPortUnregister(portBase + 0x0f);

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
    switch (ioPort & 0x0f)
    {
    case 0x04:        /* Reserved for expansion board */
        return 0xff;
    case 0x05:        /* RTC 72421 */
        return 0xff;
    case 0x06:        /* GIDE alternate status */
        return rm->altStatus;
    case 0x07:        /* GIDE drive address register */
        return rm->drvSelect;
    case 0x08:        /* IDE data register */
        return (UInt8)harddiskIdeRead(rm->hdide);
    case 0x09:        /* IDE error register */
        return harddiskIdeReadRegister(rm->hdide, 1);
    case 0x0a:        /* IDE sector count register */
        return harddiskIdeReadRegister(rm->hdide, 2);
    case 0x0b:        /* IDE sector number register */
        return harddiskIdeReadRegister(rm->hdide, 3);
    case 0x0c:        /* IDE cylinder low register */
        return harddiskIdeReadRegister(rm->hdide, 4);
    case 0x0d:        /* IDE cylinder high register */
        return harddiskIdeReadRegister(rm->hdide, 5);
    case 0x0e:        /* IDE drive/head register */
        return harddiskIdeReadRegister(rm->hdide, 6);
    case 0x0f:        /* IDE status register */
        rm->altStatus = harddiskIdeReadRegister(rm->hdide, 7);
        return rm->altStatus;

    }
    return 0xff;
}

static void writeIo(RomMapperGIde* rm, UInt16 ioPort, UInt8 value) 
{
    switch (ioPort & 0x0f)
    {
    case 0x04:        /* Reserved for expansion board */
        break; 
    case 0x05:        /* RTC 72421 */
        break; 
    case 0x06:        /* GIDE digital output register */
        rm->intEnable = value & 0x01?1:0;
        if (value & 0x02)
            harddiskIdeReset(rm->hdide);
        break; 
    case 0x07:        /* GIDE drive address register */
        break; 
    case 0x08:        /* IDE data register */
        harddiskIdeWrite(rm->hdide, value);
        break; 
    case 0x09:        /* IDE write precomp register */
        harddiskIdeWriteRegister(rm->hdide, 1, value);
        break; 
    case 0x0a:        /* IDE sector count register */
        harddiskIdeWriteRegister(rm->hdide, 2, value);
        break; 
    case 0x0b:        /* IDE sector number register */
        harddiskIdeWriteRegister(rm->hdide, 3, value);
        break; 
    case 0x0c:        /* IDE cylinder low register */
        harddiskIdeWriteRegister(rm->hdide, 4, value);
        break; 
    case 0x0d:        /* IDE cylinder high register */
        harddiskIdeWriteRegister(rm->hdide, 5, value);
        break; 
    case 0x0e:        /* IDE drive/head register */
        rm->drvSelect = value;
        harddiskIdeWriteRegister(rm->hdide, 6, value);
        break; 
    case 0x0f:        /* IDE command register */
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

int romMapperGIdeCreate(int hdId) 
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    DebugCallbacks dbgCallbacks = { getDebugInfo, NULL, NULL, NULL };
    RomMapperGIde* rm;
    int portBase;

    rm = malloc(sizeof(RomMapperGIde));
    
    rm->deviceHandle = deviceManagerRegister(ROM_GIDE, &callbacks, rm);
    rm->debugHandle = debugDeviceRegister(DBGTYPE_PORT, "GIDE", &dbgCallbacks, rm);

    if (boardGetType() == BOARD_SVI)
        portBase = 0x40;
    else
        portBase = 0x60;

    ioPortRegister(portBase + 0x04, readIo, writeIo, rm);
    ioPortRegister(portBase + 0x05, readIo, writeIo, rm);
    ioPortRegister(portBase + 0x06, readIo, writeIo, rm);
    ioPortRegister(portBase + 0x07, readIo, writeIo, rm);
    ioPortRegister(portBase + 0x08, readIo, writeIo, rm);
    ioPortRegister(portBase + 0x09, readIo, writeIo, rm);
    ioPortRegister(portBase + 0x0a, readIo, writeIo, rm);
    ioPortRegister(portBase + 0x0b, readIo, writeIo, rm);
    ioPortRegister(portBase + 0x0c, readIo, writeIo, rm);
    ioPortRegister(portBase + 0x0d, readIo, writeIo, rm);
    ioPortRegister(portBase + 0x0e, readIo, writeIo, rm);
    ioPortRegister(portBase + 0x0f, readIo, writeIo, rm);

    rm->hdide = harddiskIdeCreate(diskGetHdDriveId(hdId, 0));

    reset(rm);

    return 1;
}
