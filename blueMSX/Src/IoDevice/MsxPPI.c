/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/MsxPPI.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2005-01-04 07:14:16 $
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
#include "MsxPPI.h"
#include "romMapper.h"
#include "DeviceManager.h"
#include "SlotManager.h"
#include "IoPort.h"
#include "I8255.h"
#include "Board.h"
#include "SaveState.h"
#include "KeyClick.h"
#include "ArchControls.h"
#include "Switches.h"
#include "Led.h"
#include "Keyboard.h"
#include <stdlib.h>

typedef struct {
    int    deviceHandle;
    I8255* i8255;

    AudioKeyClick* keyClick;

    UInt8 row;
    Int32 regA;
    Int32 regCHi;
} MsxPPI;

static void destroy(MsxPPI* ppi)
{
    ioPortUnregister(0xa8);
    ioPortUnregister(0xa9);
    ioPortUnregister(0xaa);
    ioPortUnregister(0xab);

    audioKeyClickDestroy(ppi->keyClick);
    deviceManagerUnregister(ppi->deviceHandle);

    i8255Destroy(ppi->i8255);

    free(ppi);
}

static void reset(MsxPPI* ppi) 
{
    ppi->row       = 0;
    ppi->regA   = -1;
    ppi->regCHi = -1;

    i8255Reset(ppi->i8255);
}

static void loadState(MsxPPI* ppi)
{
    SaveState* state = saveStateOpenForRead("MsxPPI");

    ppi->row    = (UInt8)saveStateGet(state, "row", 0);
    ppi->regA   =        saveStateGet(state, "regA", -1);
    ppi->regCHi =        saveStateGet(state, "regCHi", -1);

    saveStateClose(state);
    
    i8255LoadState(ppi->i8255);
}

static void saveState(MsxPPI* ppi)
{
    SaveState* state = saveStateOpenForWrite("MsxPPI");
    
    saveStateSet(state, "row", ppi->row);
    saveStateSet(state, "regA", ppi->regA);
    saveStateSet(state, "regCHi", ppi->regCHi);

    saveStateClose(state);

    i8255SaveState(ppi->i8255);
}

static void writeA(MsxPPI* ppi, UInt8 value)
{
    if (value != ppi->regA) {
        int i;

        ppi->regA = value;

        for (i = 0; i < 4; i++) {
            slotSetRamSlot(i, value & 3);
            value >>= 2;
        }
    }
}

static void writeCLo(MsxPPI* ppi, UInt8 value)
{
    ppi->row = value;
}

static void writeCHi(MsxPPI* ppi, UInt8 value)
{
    if (value != ppi->regCHi) {
        ppi->regCHi = value;

        audioKeyClick(ppi->keyClick, value & 0x08);
        ledSetCapslock(!(value & 0x04));
    }
}

static UInt8 readB(MsxPPI* ppi)
{
    UInt8* keymap = keyboardGetState();
    UInt8 value = keymap[ppi->row];

    if (ppi->row == 8) {
        int renshaSpeed = switchGetRensha();
        if (renshaSpeed) {
            UInt8 renshaOn = (UInt8)((UInt64)renshaSpeed * boardSystemTime() / boardFrequency());
            ledSetRensha(renshaSpeed > 14 ? 1 : renshaOn & 2);
            value |= (renshaOn & 1);
        }
        else {
            ledSetRensha(0);
        }
    }

    return value;
}

void msxPPICreate()
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    MsxPPI* ppi = malloc(sizeof(MsxPPI));

    ppi->deviceHandle = deviceManagerRegister(RAM_MAPPER, &callbacks, ppi);

    ppi->i8255 = i8255Create(NULL,  writeA,
                             readB, NULL,
                             NULL,  writeCLo,
                             NULL,  writeCHi,
                             ppi);

    ppi->keyClick = audioKeyClickCreate(boardGetMixer());

    ioPortRegister(0xa8, i8255Read, i8255Write, ppi->i8255);
    ioPortRegister(0xa9, i8255Read, i8255Write, ppi->i8255);
    ioPortRegister(0xaa, i8255Read, i8255Write, ppi->i8255);
    ioPortRegister(0xab, i8255Read, i8255Write, ppi->i8255);

    reset(ppi);
}
