/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoChips/CRTC6845.c,v $
**
** $Revision: 1.6 $
**
** $Date: 2005-01-18 00:41:55 $
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

#include "CRTC6845.h"
#include "Board.h"
#include "IoPort.h"
#include <memory.h>

/*
     AR Address Register

     R0 Horizontal Total (Character)
     R1 Horizontal Displayed (Character)
     R2 Horizontal Sync Position (Character)
     R3 Sync Width (Vertical-Raster, Horizontal-Character)
     R4 Vertical Total (Line)
     R5 Vertical Total Adjust (Raster)
     R6 Vertical Displayed (Line)
     R7 Vertical Sync Position (Line)
     R8 Interlace and Skew
     R9 Maximum Raster Address (Raster)
     R10 Cursor Start Raster (Raster)
     R11 Cursor End Raster (Raster)
     R12 Start Address (H)
     R13 Start Address (L)
     R14 Cursor (H)
     R15 Cursor (L)
     R16 Light Pen (H)
     R17 Light Pen (L)
*/

static const UInt8 crtcRegisterValueMask[18] = {
    0xff,  // R0
    0xff,  // R1
    0xff,  // R2
    0xff,  // R3
    0x7f,  // R4
    0x1f,  // R5
    0x7f,  // R6
    0x7f,  // R7
    0xf3,  // R8
    0x1f,  // R9
    0x7f,  // R10
    0x1f,  // R11
    0x3f,  // R12
    0xff,  // R13
    0x3f,  // R14
    0xff,  // R15
    0x3f,  // R16
    0xff   // R17
};

static UInt8 crtcRegister[18];
static UInt8 crtcAddressReg; // AR

typedef enum { CURSOR_NOBLINK, CURSOR_DISABLED, CURSOR_BLINK16, CURSOR_BLINK32} crtcCursorStates;

/* Encoded registers */
typedef struct
{
    UInt8    mode;
    UInt8    rasterStart;
    UInt8    rasterEnd;
    UInt16   addressStart;
} TYP_CRTC_CURSOR;

typedef struct
{
    TYP_CRTC_CURSOR    cursor;
} TYP_CRTC;

static TYP_CRTC crtc;

static UInt8 crtcROM[0x1000];
static UInt8 crtcMemory[0x800];
static UInt8 crtcMemoryBankControl = 0;

// 80 x 25 characters (8x8 pixels/char, no colors)
static UInt8 crtcScreenBuffer[0x3e80];

static int crtcConnector;

static void crtcScreenWrite(UInt16 address, UInt8 value)
{
    if (address < 80 * 25)
        memcpy(&crtcScreenBuffer[address*8], &crtcROM[value], 8);
}

void crtcScreenRefresh(void)
{
/*
    - Blit crtcScreenBuffer to display
    - Reorganize buffer for VideoRender interface?
    - Draw cursor
    - Timer for blinking cursor
*/
}

UInt8 crtcRead(void* dummy, UInt16 ioPort)
{
    if (crtcAddressReg < 18)
        return crtcRegister[crtcAddressReg];
    else
        return 0xff;
}

void crtcWrite(void* dummy, UInt16 ioPort, UInt8 value)
{
    if (crtcAddressReg < 18) {
        value &= crtcRegisterValueMask[crtcAddressReg];
        crtcRegister[crtcAddressReg] = value;
        switch (crtcAddressReg ) {
        case 10:
            crtc.cursor.rasterStart = value & 0x1f;
            value &= 0x60;
            crtc.cursor.mode = (value&32)?(value&64)?(value&96)?CURSOR_DISABLED:CURSOR_BLINK16:CURSOR_BLINK32:CURSOR_NOBLINK;
            break;
        case 11:
            crtc.cursor.rasterEnd = value;
            break;
        case 12:
            crtc.cursor.addressStart &= 0xff;
            crtc.cursor.addressStart |= value << 8;
            break;
        case 13:
            crtc.cursor.addressStart &= 0xff00;
            crtc.cursor.addressStart |= value;
            break;
        }
    }
}

void crtcWriteLatch(void* dummy, UInt16 ioPort, UInt8 value)
{
    crtcAddressReg = value & 0x1f;
}

void crtcMemEnable(void* dummy, UInt16 ioPort, UInt8 value)
{
/*
   The SVI-806 column card for the SVI-328 disables all the Z80
   memory access from 0xF000 and above when then CRTC memory
   bank is enabled. The VRAM is 2KB.
*/
   crtcMemoryBankControl = value & 1;
}

int crtcMemBankStatus(void)
{
   return (crtcMemoryBankControl);
}

void crtcMemWrite(UInt16 address, UInt8 value)
{
    if (address < 0x800) {
        crtcMemory[address] = value;
        crtcScreenWrite(address, value);
    }
}

UInt8 crtcMemRead(UInt16 address)
{
    if (address < 0x800)
        return crtcMemory[address];
    else
        return 0xff;
}

void crtcReset(void)
{
    crtcAddressReg = 0;
    crtcMemoryBankControl = 0;
    memset(crtcRegister, 0, sizeof(crtcRegister));
    memset(crtcMemory, 0xff, sizeof(crtcMemory));
    memset(crtcScreenBuffer, 0, sizeof(crtcScreenBuffer));
}

int crtcInit(CrtcConnector connector, char* filename, UInt8* romData, int size)
{
    crtcConnector  = connector;

    if (size != 0x1000) {
    	return 0;
    }

    crtcReset();

    memset(crtcROM, 0xff, sizeof(crtcROM));
    memcpy(&crtcROM[0], romData, size);

    switch (crtcConnector) {
    case CRTC_MSX:
        ioPortRegister(0x78, NULL,     crtcWriteLatch, NULL); // CRTC Address latch
        ioPortRegister(0x79, crtcRead, crtcWrite,      NULL); // CRTC Controller register 
//        ioPortRegister(0x79, NULL,     crtcMemEnable,  NULL); // VRAM enable/disable
        break;

    case CRTC_SVI:
        ioPortRegister(0x50, NULL,     crtcWriteLatch, NULL); // CRTC Address latch
        ioPortRegister(0x51, crtcRead, crtcWrite,      NULL); // CRTC Controller register 
        ioPortRegister(0x58, NULL,     crtcMemEnable,  NULL); // VRAM enable/disable
        break;

    default:        return 0;
    }

    return 1;
}

void crtcDestroy() 
{
    switch (crtcConnector) {
    case CRTC_MSX:
        ioPortUnregister(0x78);
        ioPortUnregister(0x79);
//        ioPortUnregister(0x79);
        break;

    case CRTC_SVI:
        ioPortUnregister(0x50);
        ioPortUnregister(0x51);
        ioPortUnregister(0x58);
        break;
    }
}
