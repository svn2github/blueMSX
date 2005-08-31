/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperKonamiKeyboardMaster.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-08-31 06:51:52 $
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
#include "romMapperKonamiKeyboardMaster.h"
#include "MediaDb.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "VLM5030.h"
#include "Board.h"
#include "SaveState.h"
#include "IoPort.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
    int deviceHandle;
    UInt8* romData;
	VLM5030* vlm5030;
    int slot;
    int sslot;
    int startPage;
} RomMapperKonamiKeyboardMaster;

static void destroy(RomMapperKonamiKeyboardMaster* rm)
{
    ioPortUnregister(0x00);
    ioPortUnregister(0x20);

    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);
    vlm5030Destroy(rm->vlm5030);

    free(rm->romData);
    free(rm);
}

static UInt8 read(RomMapperKonamiKeyboardMaster* rm, UInt16 ioPort)
{
    switch (ioPort) {
    case 0x00:
        return vlm5030Read(rm->vlm5030, 0);
    case 0x20:
        return vlm5030Read(rm->vlm5030, 1);
        break;
    }
    return 0xff;
}

static void write(RomMapperKonamiKeyboardMaster* rm, UInt16 ioPort, UInt8 value)
{	
    switch (ioPort) {
    case 0x00:
        vlm5030Write(rm->vlm5030, 0, value);
        break;
    case 0x20:
        vlm5030Write(rm->vlm5030, 1, value);
        break;
    }
}

int romMapperKonamiKeyboardMasterCreate(char* filename, UInt8* romData, 
                                        int size, int slot, int sslot, 
                                        int startPage) 
{
    DeviceCallbacks callbacks = { destroy, NULL, NULL, NULL };
    RomMapperKonamiKeyboardMaster* rm;
    int i;

    if (size != 0x4000) {
        return 0;
    }

    rm = malloc(sizeof(RomMapperKonamiKeyboardMaster));

    rm->deviceHandle = deviceManagerRegister(ROM_KONAMKBDMAS, &callbacks, rm);
    slotRegister(slot, sslot, startPage, 4, NULL, NULL, NULL, destroy, rm);

    rm->romData = malloc(size);
    memcpy(rm->romData, romData, size);
    rm->vlm5030 = vlm5030Create(boardGetMixer());
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;

    for (i = 0; i < 2; i++) {   
        slotMapPage(rm->slot, rm->sslot, rm->startPage + i, rm->romData + i * 0x2000, 1, 0);
    }

    ioPortRegister(0x00, read, write, rm);
    ioPortRegister(0x20, read, write, rm);

    return 1;
}

