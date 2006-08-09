/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/Sf7000PPI.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2006-08-09 14:09:48 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vik, Tomas Karlsson
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
#include "Sf7000PPI.h"
#include "DeviceManager.h"
#include "DebugDeviceManager.h"
#include "SlotManager.h"
#include "IoPort.h"
#include "I8255.h"
#include "NEC765.h"
#include "Board.h"
#include "SaveState.h"
#include "Language.h"
#include <stdlib.h>


typedef struct {
    int    deviceHandle;
    int    debugHandle;
    I8255* i8255;
    NEC765* nec765;
} Sf7000PPI;


static void destroy(Sf7000PPI* ppi)
{
    ioPortUnregister(0xe4);
    ioPortUnregister(0xe5);
    ioPortUnregister(0xe6);
    ioPortUnregister(0xe7);

    deviceManagerUnregister(ppi->deviceHandle);
    debugDeviceUnregister(ppi->debugHandle);

    nec765Destroy(ppi->nec765);
    i8255Destroy(ppi->i8255);

    free(ppi);
}

static void reset(Sf7000PPI* ppi) 
{
    i8255Reset(ppi->i8255);
}

static void loadState(Sf7000PPI* ppi)
{
    SaveState* state = saveStateOpenForRead("Sf7000PPI");

    saveStateClose(state);
    
    i8255LoadState(ppi->i8255);
}

static void saveState(Sf7000PPI* ppi)
{
    SaveState* state = saveStateOpenForWrite("Sf7000PPI");
    
    saveStateClose(state);

    i8255SaveState(ppi->i8255);
}

static void writeCLo(Sf7000PPI* ppi, UInt8 value)
{
    if (value & 0x08) {
        nec765Reset(ppi->nec765);
        // set int ????
    }
}

static UInt8 readA(Sf7000PPI* ppi)
{
    UInt8 value = 0;

    if (nec765GetInt(ppi->nec765)) {
        value |= 0x01;
    }

    if (!nec765GetIndex(ppi->nec765)) {
        value |= 0x04;
    }

    return value;
}

static void writeCHi(Sf7000PPI* ppi, UInt8 value)
{
    slotSetRamSlot(0, (value >> 2) & 0x01);
}

static UInt8 read(Sf7000PPI* ppi, UInt16 port)
{
    return i8255Read(ppi->i8255, port);
}

static void write(Sf7000PPI* ppi, UInt16 port, UInt8 value)
{
    i8255Write(ppi->i8255, port, value);
}

static void getDebugInfo(Sf7000PPI* ppi, DbgDevice* dbgDevice)
{
    DbgIoPorts* ioPorts;

    ioPorts = dbgDeviceAddIoPorts(dbgDevice, langDbgDevPpi(), 5);
    dbgIoPortsAddPort(ioPorts, 0, 0xdc, DBG_IO_WRITE, i8255Read(ppi->i8255, 0xe4));
    dbgIoPortsAddPort(ioPorts, 1, 0xdd, DBG_IO_WRITE, i8255Read(ppi->i8255, 0xe5));
    dbgIoPortsAddPort(ioPorts, 2, 0xde, DBG_IO_WRITE, i8255Read(ppi->i8255, 0xe6));
    dbgIoPortsAddPort(ioPorts, 3, 0xdf, DBG_IO_WRITE, i8255Read(ppi->i8255, 0xe7));
}

static UInt8 fdcRead(Sf7000PPI* ppi, UInt16 port)
{
    UInt8 value = 0xff;

    switch (port & 1) {
    case 0: value = nec765ReadStatus(ppi->nec765); break;
    case 1: value = nec765Read(ppi->nec765); break;
    }

//    i8255WriteLatchA(ppi->i8255, nec765GetInt(ppi->nec765));

    return value;
}

static void fdcWrite(Sf7000PPI* ppi, UInt16 port, UInt8 value)
{
    switch (port & 1) {
    case 1: 
        nec765Write(ppi->nec765, value); break;
    }
    
//    i8255WriteLatchA(ppi->i8255, nec765GetInt(ppi->nec765));
}

void sf7000PPICreate()
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    DebugCallbacks dbgCallbacks = { getDebugInfo, NULL, NULL, NULL };
    Sf7000PPI* ppi = malloc(sizeof(Sf7000PPI));

    ppi->deviceHandle = deviceManagerRegister(RAM_MAPPER, &callbacks, ppi);
    ppi->debugHandle = debugDeviceRegister(DBGTYPE_BIOS, langDbgDevPpi(), &dbgCallbacks, ppi);
    
    ppi->nec765 = nec765Create();

    ppi->i8255 = i8255Create(NULL,  readA,  NULL,
                             NULL,  NULL,  NULL,
                             NULL,  NULL,  writeCLo,
                             NULL,  NULL,  writeCHi,
                             ppi);

	ioPortRegister(0xe0, fdcRead, NULL, ppi);
	ioPortRegister(0xe1, fdcRead, fdcWrite, ppi);

    ioPortRegister(0xe4, read, write, ppi); // PPI Port A
    ioPortRegister(0xe5, read, write, ppi); // PPI Port B
    ioPortRegister(0xe6, read, write, ppi); // PPI Port C
    ioPortRegister(0xe7, read, write, ppi); // PPI Mode

    reset(ppi);
}


