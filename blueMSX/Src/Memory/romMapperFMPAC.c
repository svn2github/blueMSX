/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperFMPAC.c,v $
**
** $Revision: 1.4 $
**
** $Date: 2005-01-02 08:22:11 $
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
#include "romMapperFMPAC.h"
#include "romMapper.h"
#include "ioPort.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "YM2413.h"
#include "Board.h"
#include "SaveState.h"
#include "sramLoader.h"
#include <stdlib.h>
#include <string.h>


static char pacHeader[] = "PAC2 BACKUP DATA";

typedef struct {
    int deviceHandle;
    YM_2413* ym2413;
    UInt8 romData[0x10000];
    UInt8 sram[0x2000];
    char sramFilename[512];
    int bankSelect;
    int slot;
    int sslot;
    int startPage;
    int sramEnabled;
} RomMapperFMPAC;

static void saveState(RomMapperFMPAC* rm)
{
    SaveState* state = saveStateOpenForWrite("mapperFMPAC");

    saveStateSet(state, "bankSelect",  rm->bankSelect);
    saveStateSet(state, "sramEnabled", rm->sramEnabled);
    saveStateSet(state, "reg1ffe",     rm->romData[0x1ffe]);
    saveStateSet(state, "reg1fff",     rm->romData[0x1fff]);
    saveStateSet(state, "reg3ff6",     rm->romData[0x3ff6]);
    saveStateSet(state, "reg3ff7",     rm->romData[0x3ff7]);

    saveStateClose(state);
}

static void loadState(RomMapperFMPAC* rm)
{
    UInt8  reg1ffe;
    UInt8  reg1fff;
    UInt8  reg3ff6;
    UInt8  reg3ff7;

    SaveState* state = saveStateOpenForRead("mapperFMPAC");
    
    rm->bankSelect  =        saveStateGet(state, "bankSelect", 0);
    rm->sramEnabled =        saveStateGet(state, "sramEnabled", 0);
    reg1ffe         = (UInt8)saveStateGet(state, "reg1ffe", 0);
    reg1fff         = (UInt8)saveStateGet(state, "reg1fff", 0);
    reg3ff6         = (UInt8)saveStateGet(state, "reg3ff6", 0);
    reg3ff7         = (UInt8)saveStateGet(state, "reg3ff7", 0);

    saveStateClose(state);

    rm->romData[0x1FFE] = reg1ffe;
    rm->romData[0x5FFE] = reg1ffe;
    rm->romData[0x9FFE] = reg1ffe;
    rm->romData[0xDFFE] = reg1ffe;
    rm->romData[0x1FFF] = reg1fff;
    rm->romData[0x5FFF] = reg1fff;
    rm->romData[0x9FFF] = reg1fff;
    rm->romData[0xDFFF] = reg1fff;
    rm->romData[0x3FF6] = reg3ff6;
    rm->romData[0x7FF6] = reg3ff6;
    rm->romData[0xBFF6] = reg3ff6;
    rm->romData[0xFFF6] = reg3ff6;
    rm->romData[0x3FF7] = reg3ff7;
    rm->romData[0x7FF7] = reg3ff7;
    rm->romData[0xBFF7] = reg3ff7;
    rm->romData[0xFFF7] = reg3ff7;

    if (rm->sramEnabled) {
        slotMapPage(rm->slot, rm->sslot, rm->startPage,     rm->sram, 1, 0);
        slotUnmapPage(rm->slot, rm->sslot, rm->startPage + 1);
    }
    else {
        UInt8* pageData = rm->romData + (rm->bankSelect << 14);

        slotMapPage(rm->slot, rm->sslot, rm->startPage,     pageData, 1, 0);
        slotMapPage(rm->slot, rm->sslot, rm->startPage + 1, pageData + 0x2000, 1, 0);
    }
}

static void destroy(RomMapperFMPAC* rm)
{
    sramSave(rm->sramFilename, rm->sram, 0x1ffe, pacHeader, strlen(pacHeader));

    ioPortUnregister(0x7c);
    ioPortUnregister(0x7d);
    
    ym2413Destroy(rm->ym2413);

    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm);
}

static void reset(RomMapperFMPAC* rm) 
{
    ym2413Reset(rm->ym2413);
}

static void write(RomMapperFMPAC* rm, UInt16 address, UInt8 value) 
{
    int update = 0;

    address &= 0x3fff;

    switch (address) {
    case 0x1ffe:
        rm->sram[0x1ffe] = value;
        rm->romData[0x1ffe] = value;
        rm->romData[0x5ffe] = value;
        rm->romData[0x9ffe] = value;
        rm->romData[0xdffe] = value;
        rm->sramEnabled = rm->romData[0x1ffe] == 0x4d && rm->romData[0x1fff] == 0x69;
        update = 1;
        break;
    case 0x1fff:
        rm->sram[0x1fff] = value;
        rm->romData[0x1fff] = value;
        rm->romData[0x5fff] = value;
        rm->romData[0x9fff] = value;
        rm->romData[0xdfff] = value;
        rm->sramEnabled = rm->romData[0x1ffe] == 0x4d && rm->romData[0x1fff] == 0x69;
        update = 1;
        break;
	case 0x3ff4:
        ioPortWrite(NULL, 0x7c, value);
		break;
	case 0x3ff5:
        ioPortWrite(NULL, 0x7d, value);
		break;
	case 0x3ff6:
        rm->romData[0x3ff6] = value & 0x11;
        rm->romData[0x7ff6] = value & 0x11;
        rm->romData[0xbff6] = value & 0x11;
        rm->romData[0xfff6] = value & 0x11;
		break;
	case 0x3ff7:
        if ((value & 3) != rm->bankSelect) {
            rm->bankSelect = value & 3;
            rm->romData[0x3ff7] = value;
            rm->romData[0x7ff7] = value;
            rm->romData[0xbff7] = value;
            rm->romData[0xfff7] = value;
            update = 1;
        }
		break;
	default:
		if (rm->sramEnabled && address < 0x1ffe) {
            rm->sram[address] = value;
		}
        break;
    }

    if (update) {
        if (rm->sramEnabled) {
            slotMapPage(rm->slot, rm->sslot, rm->startPage,     rm->sram, 1, 0);
            slotUnmapPage(rm->slot, rm->sslot, rm->startPage + 1);
        }
        else {
            UInt8* pageData = rm->romData + (rm->bankSelect << 14);

            slotMapPage(rm->slot, rm->sslot, rm->startPage,     pageData, 1, 0);
            slotMapPage(rm->slot, rm->sslot, rm->startPage + 1, pageData + 0x2000, 1, 0);
        }
    }
}

static void writeIo(RomMapperFMPAC* rm, UInt16 port, UInt8 data)
{
    if (rm->romData[0x3ff6] & 1) {
        switch (port & 1) {
        case 0:
            ym2413WriteAddress(rm->ym2413, data);
            break;
        case 1:
            ym2413WriteData(rm->ym2413, data);
            break;
        }
    }
}

int romMapperFMPACCreate(char* filename, UInt8* romData, 
                         int size, int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    RomMapperFMPAC* rm;

    if (size != 0x10000) {
        return 0;
    }

    rm = malloc(sizeof(RomMapperFMPAC));

    rm->deviceHandle = deviceManagerRegister(ROM_FMPAC, &callbacks, rm);
    slotRegister(slot, sslot, startPage, 2, NULL, write, destroy, rm);

    rm->ym2413 = ym2413Create(boardGetMixer());

    if (boardGetYm2413Enable()) {
        ioPortRegister(0x7c, NULL, writeIo, rm);
        ioPortRegister(0x7d, NULL, writeIo, rm);
    }

    memcpy(rm->romData, romData, 0x10000);
    memset(rm->sram, 0xff, 0x2000);
    rm->bankSelect = 0;
    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;
    rm->sramEnabled = 0;
    strcpy(rm->sramFilename, sramCreateFilename(filename));

    sramLoad(rm->sramFilename, rm->sram, 0x1ffe, pacHeader, strlen(pacHeader));

    slotMapPage(rm->slot, rm->sslot, rm->startPage,     rm->romData, 1, 0);
    slotMapPage(rm->slot, rm->sslot, rm->startPage + 1, rm->romData + 0x2000, 1, 0);

    rm->romData[0x1ffe] = 0xff;
    rm->romData[0x5ffe] = 0xff;
    rm->romData[0x9ffe] = 0xff;
    rm->romData[0xdffe] = 0xff;
    rm->romData[0x1fff] = 0xff;
    rm->romData[0x5fff] = 0xff;
    rm->romData[0x9fff] = 0xff;
    rm->romData[0xdfff] = 0xff;
    rm->romData[0x3ff6] = 0;
    rm->romData[0x7ff6] = 0;
    rm->romData[0xbff6] = 0;
    rm->romData[0xfff6] = 0;
    rm->romData[0x3ff7] = 0;
    rm->romData[0x7ff7] = 0;
    rm->romData[0xbff7] = 0;
    rm->romData[0xfff7] = 0;

    return 1;
}
