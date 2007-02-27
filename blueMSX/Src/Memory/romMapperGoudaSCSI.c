/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperGoudaSCSI.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2007-02-26 19:20:12 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2007 Daniel Vik, white cat
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
******************************************************************************
*/
#include "romMapperGoudaSCSI.h"
#include "wd33c93.h"
#include "MediaDb.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "DebugDeviceManager.h"
#include "SaveState.h"
#include "IoPort.h"
#include "Language.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PORT_BASE   0x34

typedef struct {
    int deviceHandle;
    int debugHandle;
    UInt8* romData;
    int slot;
    int sslot;
    int startPage;
    WD33C93* wd33c93;
} RomMapperGoudaSCSI;

static void saveState(RomMapperGoudaSCSI* rm)
{
    wd33c93SaveState(rm->wd33c93);
}

static void loadState(RomMapperGoudaSCSI* rm)
{
    wd33c93LoadState(rm->wd33c93);
}

// experimental for HSH ROM
static UInt8 dummy(RomMapperGoudaSCSI* rm, UInt16 ioPort)
{
    return 0xb0;
    //bit 4: 1 = Halt on SCSI parity error
}

static void icReset(RomMapperGoudaSCSI* rm, UInt16 ioPort, UInt8 value)
{
    wd33c93Reset(rm->wd33c93, 1);
}

static void getDebugInfo(RomMapperGoudaSCSI* rm, DbgDevice* dbgDevice)
{
    DbgIoPorts* ioPorts;

    ioPorts = dbgDeviceAddIoPorts(dbgDevice, langDbgDevScsiGouda(), 3);
    dbgIoPortsAddPort(ioPorts, 0, PORT_BASE + 0, DBG_IO_READWRITE, wd33c93Peek(rm->wd33c93, 0));
    dbgIoPortsAddPort(ioPorts, 1, PORT_BASE + 1, DBG_IO_READWRITE, wd33c93Peek(rm->wd33c93, 1));
    dbgIoPortsAddPort(ioPorts, 2, PORT_BASE + 2, DBG_IO_READWRITE, 0xb0);
}

static void reset(RomMapperGoudaSCSI* rm)
{
    wd33c93Reset(rm->wd33c93, 1);
}

static void destroy(RomMapperGoudaSCSI* rm)
{
    ioPortUnregister(PORT_BASE + 0);
    ioPortUnregister(PORT_BASE + 1);
    ioPortUnregister(PORT_BASE + 2);

    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    wd33c93Destroy(rm->wd33c93);
    free(rm->romData);
    free(rm);
}

int romMapperGoudaSCSICreate(int hdId, char* filename, UInt8* romData,
                          int size, int slot, int sslot, int startPage)
{
    DeviceCallbacks callbacks = {
        (void*)destroy, (void*)reset, (void*)saveState, (void*)loadState };
    DebugCallbacks dbgCallbacks = { (void*)getDebugInfo, NULL, NULL, NULL };
    RomMapperGoudaSCSI* rm;
    int i;
    UInt8* pBuf;

    if (romData == NULL) {
        size = 0x4000;
    } else {
        if (size != 0x4000) {
            return 0;
        }
    }

    rm = malloc(sizeof(RomMapperGoudaSCSI));

    rm->deviceHandle = deviceManagerRegister(ROM_GOUDASCSI, &callbacks, rm);
    slotRegister(slot, sslot, startPage, 2, NULL, NULL, NULL, (SlotEject)destroy, rm);
    rm->debugHandle = debugDeviceRegister(DBGTYPE_PORT, langDbgDevScsiGouda(), &dbgCallbacks, rm);

    rm->romData = malloc(0x4000);
    if (romData != NULL) {
        memcpy(rm->romData, romData, 0x4000);
        // NOVAXIS bug patch (a setting menu comes to function)
        i = 0x3ffd;
        pBuf = rm->romData;
        do {
            if (*pBuf == 0xcd && *(pBuf+1) == 0x65 && *(pBuf+2) == 0xf3) {
                *pBuf++ = 0xdb; // in a,(0a8h)
                *pBuf++ = 0xa8;
                *pBuf   = 0x00;
                i -= 2;
            }
            i--;
            pBuf++;
        } while (i > 0);
    }
    else {
        memset(rm->romData, 0xff, 0x4000);
    }

    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;
    rm->wd33c93 = wd33c93Create(hdId);

    slotMapPage(slot, sslot, startPage    , rm->romData         , 1, 0);
    slotMapPage(slot, sslot, startPage + 1, rm->romData + 0x2000, 1, 0);

    ioPortRegister(PORT_BASE + 0, (IoPortRead)wd33c93Read, (IoPortWrite)wd33c93Write, rm->wd33c93);
    ioPortRegister(PORT_BASE + 1, (IoPortRead)wd33c93Read, (IoPortWrite)wd33c93Write, rm->wd33c93);
    ioPortRegister(PORT_BASE + 2, (IoPortRead)dummy,       (IoPortWrite)icReset,      rm);

    return 1;
}
