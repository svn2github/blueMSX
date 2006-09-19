/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperDisk.c,v $
**
** $Revision: 1.5 $
**
** $Date: 2006-09-19 06:00:28 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2006 Daniel Vik
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
#include "romMapperDisk.h"
#include "MediaDb.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


static UInt16 patchAddress[] = { 0x4010, 0x4013, 0x4016, 0x401c, 0x401f, 0 };

typedef struct {
    int deviceHandle;
    UInt8* romData;
    int slot;
    int sslot;
    int startPage;
} RomMapperDisk;

static void destroy(RomMapperDisk* rm)
{
    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm->romData);
    free(rm);
}

int romMapperDiskCreate(char* filename, UInt8* romData, 
                        int size, int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, NULL, NULL, NULL };
    RomMapperDisk* rm;
    int pages = size / 0x2000;
    int i;

    if (pages == 0 || (startPage + pages) > 8) {
        return 0;
    }

    rm = malloc(sizeof(RomMapperDisk));

    rm->deviceHandle = deviceManagerRegister(ROM_DISKPATCH, &callbacks, rm);
    slotRegister(slot, sslot, startPage, pages, NULL, NULL, NULL, destroy, rm);

    rm->romData = malloc(size);
    memcpy(rm->romData, romData, size);
    
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;

    // Patch the disk rom
    for (i = 0; patchAddress[i]; i++) {
        UInt8* ptr = rm->romData + patchAddress[i] - 0x4000;
        ptr[0] = 0xed;
        ptr[1] = 0xfe;
        ptr[2] = 0xc9;
    }

    for (i = 0; i < pages; i++) {
        slotMapPage(slot, sslot, i + startPage, rm->romData + 0x2000 * i, 1, 0);
    }

    return 1;
}

