/*****************************************************************************
** File:        romMapperCasette.c
**
** Author:      Daniel Vik
**
** Description: Rom mapper for Patched Casette controller
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
#include "romMapperCasette.h"
#include "romMapper.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


static UInt16 patchAddress[] = { 0x00e1, 0x00e4, 0x00e7, 0x00ea, 0x00ed, 0x00f0, 0x00f3, 0 };

typedef struct {
    int deviceHandle;
    UInt8* romData;
    int slot;
    int sslot;
    int startPage;
} RomMapperCasette;

static void destroy(RomMapperCasette* rm)
{
    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm->romData);
    free(rm);
}

int romMapperCasetteCreate(char* filename, UInt8* romData, 
                        int size, int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, NULL, NULL, NULL };
    RomMapperCasette* rm;
    int pages = size / 0x2000;
    int i;

    if (pages == 0 || (startPage + pages) > 8) {
        return 0;
    }

    rm = malloc(sizeof(RomMapperCasette));

    rm->deviceHandle = deviceManagerRegister(ROM_CASPATCH, &callbacks, rm);
    slotRegister(slot, sslot, startPage, pages, NULL, NULL, destroy, rm);

    rm->romData = malloc(size);
    memcpy(rm->romData, romData, size);
    
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;

    // Patch the disk rom
    for (i = 0; patchAddress[i]; i++) {
        UInt8* ptr = rm->romData + patchAddress[i];
        ptr[0] = 0xed;
        ptr[1] = 0xfe;
        ptr[2] = 0xc9;
    }

    for (i = 0; i < pages; i++) {
        slotMapPage(slot, sslot, i + startPage, rm->romData + 0x2000 * i, 1, 0);
    }

    return 1;
}
