/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/SviPPI.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2004-12-28 05:09:07 $
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
#include "SviPPI.h"
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
#include <stdlib.h>


/*
PPI Port A Input (Address 98H)
Bit Name     Description
 1  TA       Joystick 1, /SENSE
 2  TB       Joystick 1, EOC
 3  TC       Joystick 2, /SENSE
 4  TD       Joystick 2, EOC
 5  TRIGGER1 Joystick 1, Trigger
 6  TRIGGER2 Joystick 2, Trigger
 7  /READY   Cassette, Ready
 8  CASR     Cassette, Read data

PPI Port B Input (Address 99H)
Bit Name Description
 1  IN0  Keyboard, Column status of selected line
 2  IN1  Keyboard, Column status of selected line
 3  IN2  Keyboard, Column status of selected line
 4  IN3  Keyboard, Column status of selected line
 5  IN4  Keyboard, Column status of selected line
 6  IN5  Keyboard, Column status of selected line
 7  IN6  Keyboard, Column status of selected line
 8  IN7  Keyboard, Column status of selected line

PPI Port C Output (Address 97H)
Bit Name   Description
 1  KB0    Keyboard, Line select 0
 2  KB1    Keyboard, Line select 1
 3  KB2    Keyboard, Line select 2
 4  KB3    Keyboard, Line select 3
 5  CASON  Cassette, Motor relay control (0=on, 1=off)
 6  CASW   Cassette, Write data
 7  CASAUD Cassette, Audio out (pulse)
 8  SOUND  Keyboard, Click sound bit (pulse)
*/

typedef struct {
    int    deviceHandle;
    I8255* i8255;

    JoystickIO* joyIO;
    AudioKeyClick* keyClick;

    UInt8 row;
    Int32 regCHi;
    UInt8 mode;
} SviPPI;

static void destroy(SviPPI* ppi)
{
    ioPortUnregister(0x98);
    ioPortUnregister(0x99);
    ioPortUnregister(0x96);
    ioPortUnregister(0x97);
    ioPortUnregister(0x9A);

    audioKeyClickDestroy(ppi->keyClick);
    deviceManagerUnregister(ppi->deviceHandle);

    i8255Destroy(ppi->i8255);

    free(ppi);
}

static void reset(SviPPI* ppi) 
{
    ppi->row    = 0;
    ppi->regCHi = -1;
    ppi->mode   = 0;

    i8255Reset(ppi->i8255);
}

static void loadState(SviPPI* ppi)
{
    SaveState* state = saveStateOpenForRead("SviPPI");

    ppi->row    = (UInt8)saveStateGet(state, "row", 0);
    ppi->mode   = (UInt8)saveStateGet(state, "mode", 0);
    ppi->regCHi =        saveStateGet(state, "regCHi", -1);

    saveStateClose(state);
    
    i8255LoadState(ppi->i8255);
}

static void saveState(SviPPI* ppi)
{
    SaveState* state = saveStateOpenForWrite("SviPPI");
    
    saveStateSet(state, "row", ppi->row);
    saveStateSet(state, "mode", ppi->mode);
    saveStateSet(state, "regCHi", ppi->regCHi);

    saveStateClose(state);

    i8255SaveState(ppi->i8255);
}

static UInt8 read(SviPPI* ppi, UInt16 ioPort)
{
    if (ioPort == 0x9A) {
        return ppi->mode;
    }

    return i8255Read(ppi->i8255, ioPort);
}

static void write(SviPPI* ppi, UInt16 ioPort, UInt8 value)
{
    if (ioPort == 0x97) {
        ppi->mode = value;
    }

    i8255Write(ppi->i8255, ioPort, value);
}

static void writeCLo(SviPPI* ppi, UInt8 value)
{
    ppi->row = value;
}

static void writeCHi(SviPPI* ppi, UInt8 value)
{
    if (value != ppi->regCHi) {
        ppi->regCHi = value;

        audioKeyClick(ppi->keyClick, value & 0x08);
    }
}

static UInt8 readA(SviPPI* ppi)
{
    return joystickReadTriggerSVI(ppi->joyIO) | 
           (boardGetCassetteInserted() ? 0:0x40);
}

static UInt8 readB(SviPPI* ppi)
{
    UInt8* keymap = archKeyboardGetState();
    return keymap[ppi->row];
}

void sviPPICreate(JoystickIO* joyIO)
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    SviPPI* ppi = malloc(sizeof(SviPPI));

    ppi->deviceHandle = deviceManagerRegister(RAM_MAPPER, &callbacks, ppi);

    ppi->joyIO = joyIO;
    ppi->i8255 = i8255Create(readA, NULL,
                             readB, NULL,
                             NULL,  writeCLo,
                             NULL,  writeCHi,
                             ppi);

    ppi->keyClick = audioKeyClickCreate(boardGetMixer());

    ioPortRegister(0x98, read, write, ppi); // PPI Port A
    ioPortRegister(0x99, read, write, ppi); // PPI Port B
    ioPortRegister(0x96, read, write, ppi); // PPI Port C
    ioPortRegister(0x97, read, write, ppi); // PPI Mode
    ioPortRegister(0x9A, read, NULL,  ppi); // PPI Return Mode

    reset(ppi);
}
