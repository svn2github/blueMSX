/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoChips/CRTC6845.c,v $
**
** $Revision: 1.9 $
**
** $Date: 2005-01-18 23:48:26 $
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

typedef enum { CURSOR_DISABLED, CURSOR_BLINK, CURSOR_NOBLINK} crtcCursorModes;

typedef enum { CRTC_SCREEN_NOREFRESH, CRTC_SCREEN_REFRESH } crtcScreenRefreshs;

typedef enum { CRTC_R0=0,   CRTC_R1=1,   CRTC_R2=2,   CRTC_R3=3,   CRTC_R4=4,   CRTC_R5=5,
               CRTC_R6=6,   CRTC_R7=7,   CRTC_R8=8,   CRTC_R9=9,   CRTC_R10=10, CRTC_R11=11,
               CRTC_R12=12, CRTC_R13=13, CRTC_R14=14, CRTC_R15=15, CRTC_R16=16, CRTC_R17=17 } crtcRegisters;

static const UInt8 crtcRegisterValueMask[18] = {
    0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f,
    0x7f, 0x7f, 0xf3, 0x1f, 0x7f, 0x1f,
    0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff 
};

typedef struct
{
    int      mode;
    UInt8    rasterStart;
    UInt8    rasterEnd;
    UInt16   addressStart;
    float    blinkrate;
} TYP_CURSOR;

typedef struct
{
    UInt8    address;  // AR
    UInt8    reg[18];  // R0-R17
} TYP_REGISTER;

typedef struct
{
    TYP_CURSOR   cursor;
    TYP_REGISTER registers;
    int          screen;
} TYP_CRTC;

static TYP_CRTC crtc;

static UInt8 crtcROM[0x1000];
static UInt8 crtcMemory[0x800];
static UInt8 crtcMemoryBankControl = 0;

static int crtcConnector;

// 80 x 25 characters (8x8 pixels/char, no colors)
static UInt8 crtcScreenBuffer[0x3e80];

/*
    - Blit crtcScreenBuffer to display
    - Reorganize buffer for VideoRender interface?
    - Draw cursor
    - Timer for blinking cursor
*/

void crtcScreenDrawCursor(void)
{
    UInt8 cursorBmp[8];
    int i;

    memset(&cursorBmp[8], 0, sizeof(cursorBmp));

    for (i = crtc.cursor.rasterStart; i < crtc.cursor.rasterEnd; i++) {
        cursorBmp[i] = 0xff;
    }

    memcpy(&crtcScreenBuffer[crtc.cursor.addressStart], &cursorBmp[0], sizeof(cursorBmp));
}

void crtcScreenRefresh(void)
{
    int x, y, Nhd, Nvd;
    UInt16 addressVram, addressScreen;

    addressVram = 0;
    addressScreen = 0;
    memset(crtcScreenBuffer, 0, sizeof(crtcScreenBuffer));

    Nhd = crtc.registers.reg[CRTC_R1];
    if (Nhd >= crtc.registers.reg[CRTC_R0])
        Nhd = crtc.registers.reg[CRTC_R0] - 1;
    if (Nhd > 80)
        Nhd = 80;

    Nvd = crtc.registers.reg[CRTC_R6];
    if (Nvd >= crtc.registers.reg[CRTC_R4])
        Nvd = crtc.registers.reg[CRTC_R4] - 1;
    if (Nvd > 25)
        Nvd = 25;

    for (y = 0; y < Nvd; y++) {

        for (x = 0; x < Nhd; x++) {
            memcpy(&crtcScreenBuffer[addressScreen+x*8], &crtcROM[crtcMemory[addressVram]], 8);
            addressVram++;
        }
        addressScreen += 640;
    }
}

static void crtcScreenWrite(UInt16 address, UInt8 value)
{
    if (address < 80 * 25)
        memcpy(&crtcScreenBuffer[address*8], &crtcROM[value], 8);
}

static void crtcCursorUpdate(void)
{
    switch (crtc.registers.reg[CRTC_R10] & 0x60 ) {
    case 32:
        crtc.cursor.mode = CURSOR_DISABLED;
        crtc.cursor.blinkrate = 0;
        break;
    case 64:
        crtc.cursor.mode = CURSOR_BLINK;
        crtc.cursor.blinkrate = (float)50 / 16;    // Get Hz from emu
        break;
    case 96:
        crtc.cursor.mode = CURSOR_BLINK;
        crtc.cursor.blinkrate = (float)50 / 32;    // Get Hz from emu
        break;
    default:
        crtc.cursor.mode = CURSOR_NOBLINK;
        crtc.cursor.blinkrate = 0;
    }
    
    crtc.cursor.rasterStart = crtc.registers.reg[CRTC_R10] & 0x1f;
    crtc.cursor.rasterEnd = crtc.registers.reg[CRTC_R11];

    crtc.cursor.addressStart = crtc.registers.reg[CRTC_R14];
    crtc.cursor.addressStart <<= 8;
    crtc.cursor.addressStart |= crtc.registers.reg[CRTC_R15];
}

UInt8 crtcRead(void* dummy, UInt16 ioPort)
{
    if (crtc.registers.address < 18)
        return crtc.registers.reg[crtc.registers.address];
    else
        return 0xff;
}

void crtcWrite(void* dummy, UInt16 ioPort, UInt8 value)
{
    if (crtc.registers.address < 18) {

        value &= crtcRegisterValueMask[crtc.registers.address];
        crtc.registers.reg[crtc.registers.address] = value;

        switch (crtc.registers.address) {
        case CRTC_R0:
        case CRTC_R1:
        case CRTC_R4:
        case CRTC_R6:
            crtc.screen = CRTC_SCREEN_REFRESH;
            break;
        case CRTC_R10:
        case CRTC_R11:
        case CRTC_R14:
        case CRTC_R15:
            crtcCursorUpdate();
            break;
        }
    }
}

void crtcWriteLatch(void* dummy, UInt16 ioPort, UInt8 value)
{
    crtc.registers.address = value & 0x1f;
}

void crtcMemEnable(void* dummy, UInt16 ioPort, UInt8 value)
{
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
    crtcMemoryBankControl = 0;
    memset(&crtc, 0, sizeof(crtc));
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
