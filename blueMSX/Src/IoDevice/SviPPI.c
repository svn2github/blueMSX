/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/SviPPI.c,v $
**
** $Revision: 1.8 $
**
** $Date: 2005-11-02 06:58:20 $
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
#include "MediaDb.h"
#include "DeviceManager.h"
#include "DebugDeviceManager.h"
#include "SlotManager.h"
#include "IoPort.h"
#include "I8255.h"
#include "Board.h"
#include "SaveState.h"
#include "KeyClick.h"
#include "ArchInput.h"
#include "Switches.h"
#include "Led.h"
#include "InputEvent.h"
#include <stdlib.h>


static UInt8 getKeyState(int row);

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
    int    debugHandle;
    I8255* i8255;

    SviJoyIo* joyIO;
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
    debugDeviceUnregister(ppi->debugHandle);

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

static UInt8 peek(SviPPI* ppi, UInt16 ioPort)
{
    if (ioPort == 0x9A) {
        return ppi->mode;
    }

    return i8255Peek(ppi->i8255, ioPort);
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
    return sviJoyIoReadTrigger(ppi->joyIO) | 
           (boardGetCassetteInserted() ? 0:0x40);
}

static UInt8 readB(SviPPI* ppi)
{
    return getKeyState(ppi->row);
}

static void getDebugInfo(SviPPI* ppi, DbgDevice* dbgDevice)
{
    DbgIoPorts* ioPorts;

    ioPorts = dbgDeviceAddIoPorts(dbgDevice, "I8255 PPI", 5);
    dbgIoPortsAddPort(ioPorts, 0, 0x98, DBG_IO_READWRITE, peek(ppi, 0x98));
    dbgIoPortsAddPort(ioPorts, 1, 0x99, DBG_IO_READWRITE, peek(ppi, 0x99));
    dbgIoPortsAddPort(ioPorts, 2, 0x96, DBG_IO_READWRITE, peek(ppi, 0x96));
    dbgIoPortsAddPort(ioPorts, 3, 0x97, DBG_IO_READWRITE, peek(ppi, 0x97));
    dbgIoPortsAddPort(ioPorts, 4, 0x9A, DBG_IO_READ,      peek(ppi, 0x9A));
}

void sviPPICreate(SviJoyIo* joyIO)
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    DebugCallbacks dbgCallbacks = { getDebugInfo, NULL, NULL, NULL };
    SviPPI* ppi = malloc(sizeof(SviPPI));

    ppi->deviceHandle = deviceManagerRegister(RAM_MAPPER, &callbacks, ppi);
    ppi->debugHandle = debugDeviceRegister(DBGTYPE_BIOS, "I8255 PPI", &dbgCallbacks, ppi);

    ppi->joyIO = joyIO;
    ppi->i8255 = i8255Create(readA, readA, NULL,
                             readB, readB, NULL,
                             NULL,  NULL,  writeCLo,
                             NULL,  NULL,  writeCHi,
                             ppi);

    ppi->keyClick = audioKeyClickCreate(boardGetMixer());

    ioPortRegister(0x98, read, write, ppi); // PPI Port A
    ioPortRegister(0x99, read, write, ppi); // PPI Port B
    ioPortRegister(0x96, read, write, ppi); // PPI Port C
    ioPortRegister(0x97, read, write, ppi); // PPI Mode
    ioPortRegister(0x9A, read, NULL,  ppi); // PPI Return Mode

    reset(ppi);
}


static UInt8 getKeyState(int row)
{
    UInt8 keyState = 0;
    switch (row) {
    case 0:
        keyState = (inputEventGetState(EC_0      ) << 0) |
                   (inputEventGetState(EC_1      ) << 1) |
                   (inputEventGetState(EC_2      ) << 2) |
                   (inputEventGetState(EC_3      ) << 3) |
                   (inputEventGetState(EC_4      ) << 4) |
                   (inputEventGetState(EC_5      ) << 5) |
                   (inputEventGetState(EC_6      ) << 6) |
                   (inputEventGetState(EC_7      ) << 7);
        break;
        
    case 1:
        keyState = (inputEventGetState(EC_8      ) << 0) |
                   (inputEventGetState(EC_9      ) << 1) |
                   (inputEventGetState(EC_SEMICOL) << 2) |
                   (inputEventGetState(EC_COLON  ) << 3) |
                   (inputEventGetState(EC_COMMA  ) << 4) |
                   (inputEventGetState(EC_CIRCFLX) << 5) |
                   (inputEventGetState(EC_PERIOD ) << 6) |
                   (inputEventGetState(EC_DIV    ) << 7);
        break;
        
    case 2:
        keyState = (inputEventGetState(EC_NEG    ) << 0) |
                   (inputEventGetState(EC_A      ) << 1) |
                   (inputEventGetState(EC_B      ) << 2) |
                   (inputEventGetState(EC_C      ) << 3) |
                   (inputEventGetState(EC_D      ) << 4) |
                   (inputEventGetState(EC_E      ) << 5) |
                   (inputEventGetState(EC_F      ) << 6) |
                   (inputEventGetState(EC_G      ) << 7);
        break;
        
    case 3:
        keyState = (inputEventGetState(EC_H      ) << 0) |
                   (inputEventGetState(EC_I      ) << 1) |
                   (inputEventGetState(EC_J      ) << 2) |
                   (inputEventGetState(EC_K      ) << 3) |
                   (inputEventGetState(EC_L      ) << 4) |
                   (inputEventGetState(EC_M      ) << 5) |
                   (inputEventGetState(EC_N      ) << 6) |
                   (inputEventGetState(EC_O      ) << 7);
        break;
        
    case 4:
        keyState = (inputEventGetState(EC_P      ) << 0) |
                   (inputEventGetState(EC_Q      ) << 1) |
                   (inputEventGetState(EC_R      ) << 2) |
                   (inputEventGetState(EC_S      ) << 3) |
                   (inputEventGetState(EC_T      ) << 4) |
                   (inputEventGetState(EC_U      ) << 5) |
                   (inputEventGetState(EC_V      ) << 6) |
                   (inputEventGetState(EC_W      ) << 7);
        break;
        
    case 5:
        keyState = (inputEventGetState(EC_X      ) << 0) |
                   (inputEventGetState(EC_Y      ) << 1) |
                   (inputEventGetState(EC_Z      ) << 2) |
                   (inputEventGetState(EC_AT     ) << 3) |
                   (inputEventGetState(EC_BKSLASH) << 4) |
                   (inputEventGetState(EC_LBRACK ) << 5) |
                   (inputEventGetState(EC_BKSPACE) << 6) |
                   (inputEventGetState(EC_UP     ) << 7);
        break;
        
    case 6:
        keyState = (inputEventGetState(EC_LSHIFT ) << 0) |
                   (inputEventGetState(EC_RSHIFT ) << 0) |
                   (inputEventGetState(EC_CTRL   ) << 1) |
                   (inputEventGetState(EC_GRAPH  ) << 2) |
                   (inputEventGetState(EC_CODE   ) << 3) |
                   (inputEventGetState(EC_ESC    ) << 4) |
                   (inputEventGetState(EC_STOP   ) << 5) |
                   (inputEventGetState(EC_RETURN ) << 6) |
                   (inputEventGetState(EC_LEFT   ) << 6);
        break;
        
    case 7:
        keyState = (inputEventGetState(EC_F1      ) << 0) |
                   (inputEventGetState(EC_F2      ) << 1) |
                   (inputEventGetState(EC_F3      ) << 2) |
                   (inputEventGetState(EC_F4      ) << 3) |
                   (inputEventGetState(EC_F5      ) << 4) |
                   (inputEventGetState(EC_CLS     ) << 5) |
                   (inputEventGetState(EC_INS     ) << 6) |
                   (inputEventGetState(EC_DOWN    ) << 7);
        break;
        
    case 8:
        keyState = (inputEventGetState(EC_SPACE  ) << 0) |
                   (inputEventGetState(EC_TAB    ) << 1) |
                   (inputEventGetState(EC_DEL    ) << 2) |
                   (inputEventGetState(EC_CAPS   ) << 3) |
                   (inputEventGetState(EC_SELECT ) << 4) |
                   (inputEventGetState(EC_PRINT  ) << 5) |
                   (inputEventGetState(EC_RIGHT  ) << 7);
        break;
        
    case 9:
        keyState = (inputEventGetState(EC_NUM0   ) << 0) |
                   (inputEventGetState(EC_NUM1   ) << 1) |
                   (inputEventGetState(EC_NUM2   ) << 2) |
                   (inputEventGetState(EC_NUM3   ) << 3) |
                   (inputEventGetState(EC_NUM4   ) << 4) |
                   (inputEventGetState(EC_NUM5   ) << 5) |
                   (inputEventGetState(EC_NUM6   ) << 6) |
                   (inputEventGetState(EC_NUM7   ) << 7);
        break;
        
    case 10:
        keyState = (inputEventGetState(EC_NUM8   ) << 0) |
                   (inputEventGetState(EC_NUM9   ) << 1) |
                   (inputEventGetState(EC_NUMADD ) << 2) |
                   (inputEventGetState(EC_NUMSUB ) << 3) |
                   (inputEventGetState(EC_NUMMUL ) << 4) |
                   (inputEventGetState(EC_NUMDIV ) << 5) |
                   (inputEventGetState(EC_NUMPER ) << 6) |
                   (inputEventGetState(EC_NUMCOM ) << 7);
        break;
    }

    return ~keyState;
}
