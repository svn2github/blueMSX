/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperBeerIDE.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2005-12-21 03:34:58 $
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
#include "romMapperBeerIDE.h"
#include "HarddiskIDE.h"
#include "MediaDb.h"
#include "DeviceManager.h"
#include "DebugDeviceManager.h"
#include "SaveState.h"
#include "IoPort.h"
#include "I8255.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
PPI    NAME   IDE PIN
---    ----   -------
PA0    HD0    17 Host Data 0
PA1    HD1    15 Host Data 1
PA2    HD2    13 Host Data 2
PA3    HD3    11 Host Data 3
PA4    HD4     9 Host Data 4
PA5    HD5     7 Host Data 5
PA6    HD6     5 Host Data 6
PA7    HD7     3 Host Data 7

PB0    HD8     4 Host Data 8
PB1    HD9     6 Host Data 9
PB2    HD10    8 Host Data 10
PB3    HD11   10 Host Data 11
PB4    HD12   12 Host Data 12
PB5    HD13   14 Host Data 13
PB6    HD14   16 Host Data 14
PB7    HD15   18 Host Data 15

PC0    HA0    35 Addr 0
PC1    HA1    33 Addr 1
PC2    HA2    36 Addr 2
PC3    N/A
PC4    N/A
PC5    HCS    37 /CS0
PC6    HWR    23 /IO Write
PC7    HRD    25 /IO Read
*/

typedef struct {
    int deviceHandle;
    int debugHandle;
    UInt8* romData;
    int slot;
    int sslot;
    int startPage;
    HarddiskIde* hdide;
    I8255* i8255;
} RomMapperBeerIde;

static void saveState(RomMapperBeerIde* rm)
{
    SaveState* state = saveStateOpenForWrite("RomMapperBeerIde");

    saveStateClose(state);

    harddiskIdeSaveState(rm->hdide);
    i8255SaveState(rm->i8255);
}

static void loadState(RomMapperBeerIde* rm)
{
    SaveState* state = saveStateOpenForRead("RomMapperBeerIde");

    saveStateClose(state);

    harddiskIdeLoadState(rm->hdide);
    i8255LoadState(rm->i8255);
}

static void destroy(RomMapperBeerIde* rm)
{
    ioPortUnregister(0x30);
    ioPortUnregister(0x31);
    ioPortUnregister(0x32);
    ioPortUnregister(0x33);

    deviceManagerUnregister(rm->deviceHandle);
    debugDeviceUnregister(rm->debugHandle);

    harddiskIdeDestroy(rm->hdide);
    
    i8255Destroy(rm->i8255);

    free(rm);
}

static UInt8 peekIo(RomMapperBeerIde* rm, UInt16 ioPort) 
{
    return 0xff;
}

static UInt8 readA(RomMapperBeerIde* rm)
{
    return 0xff;
}

static UInt8 readB(RomMapperBeerIde* rm)
{
    return 0xff;
}

static void writeA(RomMapperBeerIde* rm, UInt8 value)
{
}

static void writeB(RomMapperBeerIde* rm, UInt8 value)
{
}

static void writeCLo(RomMapperBeerIde* rm, UInt8 value)
{
}

static void writeCHi(RomMapperBeerIde* rm, UInt8 value)
{
}

static UInt8 read(RomMapperBeerIde* rm, UInt16 address) 
{
    return 0xff;
}

static void write(RomMapperBeerIde* rm, UInt16 address, UInt8 value) 
{
}

static void reset(RomMapperBeerIde* rm)
{
    harddiskIdeReset(rm->hdide);

    i8255Reset(rm->i8255);
}

static void getDebugInfo(RomMapperBeerIde* rm, DbgDevice* dbgDevice)
{
    DbgIoPorts* ioPorts;
    int i;

    ioPorts = dbgDeviceAddIoPorts(dbgDevice, "Beer IDE", 12);
    for (i = 0; i < 12; i++) {
        dbgIoPortsAddPort(ioPorts, i, 0x44 + i, DBG_IO_READWRITE, peekIo(rm, 0x44 + i));
    }
}

int romMapperBeerIdeCreate(const char* diskFileName, char* fileName, UInt8* romData, 
                              int size, int slot, int sslot, int startPage)
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    DebugCallbacks dbgCallbacks = { getDebugInfo, NULL, NULL, NULL };
    RomMapperBeerIde* rm;

    rm = malloc(sizeof(RomMapperBeerIde));
    
    rm->deviceHandle = deviceManagerRegister(ROM_BEERIDE, &callbacks, rm);
    rm->debugHandle = debugDeviceRegister(DBGTYPE_PORT, "Beer IDE", &dbgCallbacks, rm);
    rm->i8255 = i8255Create( NULL, readA, writeA,
                             NULL, readB, writeB,
                             NULL,  NULL,  writeCLo,
                             NULL,  NULL,  writeCHi,
                             rm);

    ioPortRegister(0x30, i8255Read, i8255Write, rm->i8255); // PPI Port A
    ioPortRegister(0x31, i8255Read, i8255Write, rm->i8255); // PPI Port B
    ioPortRegister(0x32, i8255Read, i8255Write, rm->i8255); // PPI Port C
    ioPortRegister(0x33, i8255Read, i8255Write, rm->i8255); // PPI Mode

    rm->hdide = harddiskIdeCreate(diskFileName);

    reset(rm);

    return 1;
}

