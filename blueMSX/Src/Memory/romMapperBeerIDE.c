/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperBeerIDE.c,v $
**
** $Revision: 1.4 $
**
** $Date: 2005-12-22 09:10:32 $
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
PA0    HD0    17 D0
PA1    HD1    15 D1
PA2    HD2    13 D2
PA3    HD3    11 D3
PA4    HD4     9 D4
PA5    HD5     7 D5
PA6    HD6     5 D6
PA7    HD7     3 D7

PB0    HD8     4 D8
PB1    HD9     6 D9
PB2    HD10    8 D10
PB3    HD11   10 D11
PB4    HD12   12 D12
PB5    HD13   14 D13
PB6    HD14   16 D14
PB7    HD15   18 D15

PC0    HA0    35 A0
PC1    HA1    33 A1
PC2    HA2    36 A2
PC3    N/A
PC4    N/A
PC5    HCS    37 /CS0
PC6    HWR    23 /IOWR
PC7    HRD    25 /IORD
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
    UInt8 ideAddress;
    UInt8 ideIoRead;
    UInt8 ideIoWrite;
    UInt16 ideData;
} RomMapperBeerIde;

static void saveState(RomMapperBeerIde* rm)
{
    SaveState* state = saveStateOpenForWrite("RomMapperBeerIde");

    saveStateSet(state, "ideAddress", rm->ideAddress);
    saveStateSet(state, "ideIoRead", rm->ideIoRead);
    saveStateSet(state, "ideIoWrite", rm->ideIoWrite);
    saveStateSet(state, "ideData", rm->ideData);

    saveStateClose(state);

    harddiskIdeSaveState(rm->hdide);
    i8255SaveState(rm->i8255);
}

static void loadState(RomMapperBeerIde* rm)
{
    SaveState* state = saveStateOpenForRead("RomMapperBeerIde");

    rm->ideAddress = (UInt8)saveStateGet(state, "ideAddress", 0);
    rm->ideIoRead = (UInt8)saveStateGet(state, "ideIoRead", 0);
    rm->ideIoWrite = (UInt8)saveStateGet(state, "ideIoWrite", 0);
    rm->ideData = (UInt8)saveStateGet(state, "ideData", 0);

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
    return (UInt8)rm->ideData;
}

static UInt8 readB(RomMapperBeerIde* rm)
{
	return (UInt8)rm->ideData >>8;
}

static void writeA(RomMapperBeerIde* rm, UInt8 value)
{
    rm->ideData &= 0xff00;
    rm->ideData |= value;
}

static void writeB(RomMapperBeerIde* rm, UInt8 value)
{
    rm->ideData &= 0x00ff;
    rm->ideData |= value<<8;
}

static void writeCLo(RomMapperBeerIde* rm, UInt8 value)
{
	rm->ideAddress = value & 0x07;
}

static void writeCHi(RomMapperBeerIde* rm, UInt8 value)
{
	rm->ideIoRead = value & 0x08 ? 0:1;
	rm->ideIoWrite = value & 0x04 ? 0:1;

	if (rm->ideIoRead)
	{
		switch (rm->ideAddress)
		{
		case 0:
			rm->ideData = harddiskIdeRead(rm->hdide);
			break;
		default:
			rm->ideData = harddiskIdeReadRegister(rm->hdide, rm->ideAddress);
			break;
		}
	}

    if (rm->ideIoWrite)
	{
		switch (rm->ideAddress)
		{
		case 0:
            harddiskIdeWrite(rm->hdide, rm->ideData);
			break;
		default:
		    harddiskIdeWriteRegister(rm->hdide, rm->ideAddress, (UInt8)rm->ideData);
			break;
		}
	}
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

int romMapperBeerIdeCreate(char* fileName, UInt8* romData, 
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
                             NULL, NULL,  writeCLo,
                             NULL, NULL,  writeCHi,
                             rm);

    ioPortRegister(0x30, i8255Read, i8255Write, rm->i8255); // PPI Port A
    ioPortRegister(0x31, i8255Read, i8255Write, rm->i8255); // PPI Port B
    ioPortRegister(0x32, i8255Read, i8255Write, rm->i8255); // PPI Port C
    ioPortRegister(0x33, i8255Read, i8255Write, rm->i8255); // PPI Mode

    rm->hdide = harddiskIdeCreate(2);

    reset(rm);

    return 1;
}

