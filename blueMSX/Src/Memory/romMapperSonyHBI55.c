/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperSonyHBI55.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2004-12-29 00:10:48 $
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
#include "romMapperSonyHBI55.h"
#include "romMapper.h"
#include "DeviceManager.h"
#include "SlotManager.h"
#include "sramLoader.h"
#include "IoPort.h"
#include "I8255.h"
#include "Board.h"
#include "SaveState.h"
#include "KeyClick.h"
#include "ArchControls.h"
#include "Switches.h"
#include "Led.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    int    deviceHandle;
    I8255* i8255;

    UInt8  sram[0x1000];
    UInt16 address;
    int    mode;
} SonyHBI55;

static void destroy(SonyHBI55* rm)
{
    ioPortUnregister(0xb0);
    ioPortUnregister(0xb1);
    ioPortUnregister(0xb2);
    ioPortUnregister(0xb3);
    
    sramSave(sramCreateFilename("HBI-55.SRAM"), rm->sram, 0x1000, NULL, 0);

    deviceManagerUnregister(rm->deviceHandle);

    i8255Destroy(rm->i8255);

    free(rm);
}

static void reset(SonyHBI55* rm) 
{
    i8255Reset(rm->i8255);
}

static void loadState(SonyHBI55* rm)
{
    SaveState* state = saveStateOpenForRead("SonyHBI55");

    rm->mode    =         saveStateGet(state, "mode",    0);
    rm->address = (UInt16)saveStateGet(state, "address", 0);

    saveStateClose(state);
    
    i8255LoadState(rm->i8255);
}

static void saveState(SonyHBI55* rm)
{
    SaveState* state = saveStateOpenForWrite("SonyHBI55");
    
    saveStateSet(state, "mode",    rm->mode);
    saveStateSet(state, "address", rm->address);

    saveStateClose(state);

    i8255SaveState(rm->i8255);
}

static void writeA(SonyHBI55* rm, UInt8 value)
{
	rm->address = (rm->address & 0xff00) | value; 
}

static void writeB(SonyHBI55* rm, UInt8 value)
{
	rm->address = (rm->address & 0x00ff) | ((value & 0x0f) << 8); 
	rm->mode    = value >> 6;
}

static void writeCLo(SonyHBI55* rm, UInt8 value)
{
    if (rm->mode == 1) {
        if (rm->address > 0) {
            rm->sram[rm->address] &= 0xf0;
            rm->sram[rm->address] |= value;
        }
    }
}

static void writeCHi(SonyHBI55* rm, UInt8 value)
{
    if (rm->mode == 1) {
        if (rm->address > 0) {
            rm->sram[rm->address] &= 0x0f;
            rm->sram[rm->address] |= value << 4;
        }
    }
}

static UInt8 readCLo(SonyHBI55* rm)
{
    if (rm->mode == 3) {
        return rm->sram[rm->address] & 0x0f;
    }
    return 0x0f;
}


static UInt8 readCHi(SonyHBI55* rm)
{
    if (rm->mode == 3) {
        return rm->sram[rm->address] >> 4;
    }
    return 0x0f;
}

int romMapperSonyHBI55Create()
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    SonyHBI55* rm = malloc(sizeof(SonyHBI55));

    rm->deviceHandle = deviceManagerRegister(ROM_SONYHBI55, &callbacks, rm);

    memset(rm->sram, 0xff, sizeof(rm->sram));
    sramLoad(sramCreateFilename("HBI-55.SRAM"), rm->sram, 0x1000, NULL, 0);

    rm->sram[0] = 0x53;

    rm->i8255 = i8255Create(NULL,    writeA,
                            NULL,    writeB,
                            readCLo, writeCLo,
                            readCHi, writeCHi,
                            rm);

    ioPortRegister(0xb0, i8255Read, i8255Write, rm->i8255);
    ioPortRegister(0xb1, i8255Read, i8255Write, rm->i8255);
    ioPortRegister(0xb2, i8255Read, i8255Write, rm->i8255);
    ioPortRegister(0xb3, i8255Read, i8255Write, rm->i8255);

    reset(rm);

    return 1;
}
