/*****************************************************************************
** File:        I8255.c
**
** Author:      Daniel Vik
**
** Description: I8255 emulation
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
#include "I8255.h"
#include "SlotManager.h"
#include "SaveState.h"
#include "Led.h"
#include "IoPort.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    UInt8          reg[4];
    UInt8          outReg[3]; 
    UInt8          inReg[3];
    UInt8          oldOutReg[3];
    UInt8*         keymap;
    AudioKeyClick* keyClick;
} I8255;

static I8255 i8255;

static UInt8 i8255read(void* ref, UInt16 ioPort)
{
    ioPort &= 3;

    // Read keyboard input
    i8255.inReg[1] = i8255.keymap[i8255.outReg[2] & 0x0f];

    switch(ioPort) {
    case 0: 
        return i8255.reg[3] & 0x10 ? i8255.inReg[0] : i8255.reg[0];
    case 1: 
        return i8255.reg[3] & 0x02? i8255.inReg[1] : i8255.reg[1];
    case 2: 
        return ((i8255.reg[3] & 0x01 ? i8255.inReg[2] : i8255.reg[2]) & 0x0f)|
               ((i8255.reg[3] & 0x08 ? i8255.inReg[2] : i8255.reg[2]) & 0xf0);
    case 3: 
        return i8255.reg[3];
    }

    return 0xff;
}

static void i8255write(void* ref, UInt16 ioPort, UInt8 value)
{
    int i;

    ioPort &= 3;

    // Update registers and ports
    switch(ioPort) {
    case 0:
    case 1:
    case 2:
        /* Data registers */
        i8255.reg[ioPort] = value;
        break;
    case 3:
        /* Control register */
        if (value & 0x80) {
            i8255.reg[ioPort] = value;
        }
        else {
            ioPort = 1 << ((value & 0x0e) >> 1);
            if (value&0x01) {
                i8255.reg[2] |= ioPort; 
            }
            else {
                i8255.reg[2] &= ~ioPort;
            }
        }
        break;
    }

    /* Set output ports */
    value = i8255.reg[3];
    i8255.outReg[0] = value & 0x10 ? 0x00 : i8255.reg[0];
    i8255.outReg[1] = value & 0x02 ? 0x00 : i8255.reg[1];
    i8255.outReg[2] = ((value & 0x01 ? 0x00 : i8255.reg[2]) & 0x0f) | 
                      ((value & 0x08 ? 0x00 : i8255.reg[2]) & 0xf0);

    // Do post processing
    if (i8255.outReg[2] != i8255.oldOutReg[2]) { 
        audioKeyClick(i8255.keyClick, (i8255.outReg[2] >> 7));

        ledSetCapslock(0 == (i8255.outReg[2] & 0x40));

        i8255.oldOutReg[2] = i8255.outReg[2]; 
    }

    if (i8255.outReg[0] != i8255.oldOutReg[0]) {
        i8255.oldOutReg[0] = i8255.outReg[0];
        value  = i8255.outReg[0];

        for (i = 0; i < 4; i++) {
            slotSetRamSlot(i, value & 3);
            value >>= 2;
        }
    }
}

void i8255Create(UInt8* keymap, AudioKeyClick* keyClick)
{
    memset(&i8255, 0, sizeof(i8255));
    
    i8255.keymap   = keymap;
    i8255.keyClick = keyClick;
    i8255.reg[3]   = 0x9b;

    ioPortRegister(0xa8, i8255read, i8255write, NULL);
    ioPortRegister(0xa9, i8255read, i8255write, NULL);
    ioPortRegister(0xaa, i8255read, i8255write, NULL);
    ioPortRegister(0xab, i8255read, i8255write, NULL);

    ledSetCapslock(0);
}

void i8255Destroy() 
{
    ioPortUnregister(0xa8);
    ioPortUnregister(0xa9);
    ioPortUnregister(0xaa);
    ioPortUnregister(0xab);
}

void i8255Reset()
{
    memset(i8255.reg,       0, sizeof(i8255.reg));
    memset(i8255.outReg,    0, sizeof(i8255.outReg));
    memset(i8255.inReg,     0, sizeof(i8255.inReg));
    memset(i8255.oldOutReg, 0, sizeof(i8255.oldOutReg));
    i8255.reg[3] = 0x9b;

    ledSetCapslock(0);
}

void i8255SaveState()
{
    SaveState* state = saveStateOpenForWrite("i8255");
    
    saveStateSet(state, "reg00",       i8255.reg[0]);
    saveStateSet(state, "reg01",       i8255.reg[1]);
    saveStateSet(state, "reg02",       i8255.reg[2]);
    saveStateSet(state, "reg03",       i8255.reg[3]);
    saveStateSet(state, "inReg00",     i8255.inReg[0]);
    saveStateSet(state, "inReg01",     i8255.inReg[1]);
    saveStateSet(state, "inReg02",     i8255.inReg[2]);
    saveStateSet(state, "outReg00",    i8255.outReg[0]);
    saveStateSet(state, "outReg01",    i8255.outReg[1]);
    saveStateSet(state, "outReg02",    i8255.outReg[2]);
    saveStateSet(state, "oldOutReg00", i8255.oldOutReg[0]);
    saveStateSet(state, "oldOutReg01", i8255.oldOutReg[1]);
    saveStateSet(state, "oldOutReg02", i8255.oldOutReg[2]);

    saveStateClose(state);
}

void i8255LoadState()
{
    SaveState* state = saveStateOpenForRead("i8255");

    i8255.reg[0]       = (UInt8)saveStateGet(state, "reg00",       0);
    i8255.reg[1]       = (UInt8)saveStateGet(state, "reg01",       0);
    i8255.reg[2]       = (UInt8)saveStateGet(state, "reg02",       0);
    i8255.reg[3]       = (UInt8)saveStateGet(state, "reg03",       0);
    i8255.inReg[0]     = (UInt8)saveStateGet(state, "inReg00",     0);
    i8255.inReg[1]     = (UInt8)saveStateGet(state, "inReg01",     0);
    i8255.inReg[2]     = (UInt8)saveStateGet(state, "inReg02",     0);
    i8255.outReg[0]    = (UInt8)saveStateGet(state, "outReg00",    0);
    i8255.outReg[1]    = (UInt8)saveStateGet(state, "outReg01",    0);
    i8255.outReg[2]    = (UInt8)saveStateGet(state, "outReg02",    0);
    i8255.oldOutReg[0] = (UInt8)saveStateGet(state, "oldOutReg00", 0);
    i8255.oldOutReg[1] = (UInt8)saveStateGet(state, "oldOutReg01", 0);
    i8255.oldOutReg[2] = (UInt8)saveStateGet(state, "oldOutReg02", 0);

    saveStateClose(state);
}
