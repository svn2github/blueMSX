/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoChips/CRTC6845.c,v $
**
** $Revision: 1.22 $
**
** $Date: 2005-01-25 16:58:48 $
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
#include "IoPort.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include <stdlib.h>
#include <memory.h>

/*
   AR Address Register
   R0 Horizontal Total (Character)                       SVI Default: 107
   R1 Horizontal Displayed (Character)                   SVI Default: 80
   R2 Horizontal Sync Position (Character)               SVI Default: 88
   R3 Sync Width (Vertical-Raster, Horizontal-Character) SVI Default:  8
   R4 Vertical Total (Line)                              SVI Default: 38
   R5 Vertical Total Adjust (Raster)                     SVI Default: 5
   R6 Vertical Displayed (Line)                          SVI Default: 24
   R7 Vertical Sync Position (Line)                      SVI Default: 30
   R8 Interlace and Skew                                 SVI Default: 0
   R9 Maximum Raster Address (Raster)                    SVI Default: 7
   R10 Cursor Start Raster (Raster)
   R11 Cursor End Raster (Raster)
   R12 Start Address (H)
   R13 Start Address (L)
   R14 Cursor (H)
   R15 Cursor (L)
   R16 Light Pen (H)
   R17 Light Pen (L)
*/

#define CHAR_WIDTH           7
#define MAX_CHARS_PER_LINE  84
#define DISPLAY_WIDTH       ((CHAR_WIDTH * MAX_CHARS_PER_LINE) / 2) // NOTE: DISPLAY_WIDTH should *never* exceed 320 !!
#define DISPLAY_HEIGHT      240

extern UInt32 videoGetColor(int R, int G, int B); // FIXME: Do something nicer

typedef enum { CURSOR_DISABLED, CURSOR_BLINK, CURSOR_NOBLINK} crtcCursorModes;
typedef enum { CRTC_R0=0,   CRTC_R1=1,   CRTC_R2=2,   CRTC_R3=3,   CRTC_R4=4,   CRTC_R5=5,
               CRTC_R6=6,   CRTC_R7=7,   CRTC_R8=8,   CRTC_R9=9,   CRTC_R10=10, CRTC_R11=11,
               CRTC_R12=12, CRTC_R13=13, CRTC_R14=14, CRTC_R15=15, CRTC_R16=16, CRTC_R17=17 } crtcRegisters;

static const UInt8 crtcRegisterValueMask[18] = {
    0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f,
    0x7f, 0x7f, 0xf3, 0x1f, 0x7f, 0x1f,
    0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff 
};

//static TYP_CRTC crtc;
static UInt8 crtcROM[0x1000];
static UInt8 crtcMemory[0x800];

// Frame refresh timer info
#define REFRESH_PERIOD (boardFrequency() /  50)

static void crtcRenderVideoBuffer(CRTC6845* crtc)
{
    UInt32 color[2];
    int x, y;
    int charWidth, charHeight;
    int Nr  = crtc->registers.reg[CRTC_R9] + 1; // Number of rasters per character
    FrameBuffer* crtcFrameBuffer = frameBufferFlipDrawFrame(); // Call once per frame

    crtc->frameCounter++;

    charWidth = crtc->registers.reg[CRTC_R1];
    if (charWidth >= crtc->registers.reg[CRTC_R0])
        charWidth = crtc->registers.reg[CRTC_R0] - 1;
    if (charWidth > 80)
        charWidth = 80;

    charHeight = crtc->registers.reg[CRTC_R6];
    if (charHeight >= crtc->registers.reg[CRTC_R4])
        charHeight = crtc->registers.reg[CRTC_R4] - 1;
    if (charHeight > 25)
        charHeight = 25;

    color[0] = videoGetColor(0, 0, 0);       // Cen be calculated once. The interface
    color[1] = videoGetColor(255, 255, 255); // must be updated (also for the VDP)

    crtcFrameBuffer->interlaceOdd = 0; // These fields could be set once only but 

    for (y = 0; y < DISPLAY_HEIGHT; y++) {
        UInt32* linePtr = crtcFrameBuffer->line[y].buffer;
        int charRaster = y % Nr;
        int vadjust = 3; // Fix vertical adjust from regs (the value 4)
        int hadjust = 2; // Fix horizontal adjust from regs (the value 1)
        int charLine   = y / Nr - vadjust;                
        int charAddress = charLine * charWidth - hadjust; 

        if (charLine < 0 || charLine >= charHeight) {
            for (x = 0; x < DISPLAY_WIDTH; x++) {
                linePtr[x] = color[0];
            }
            continue;
        }

        for (x = 0; x < MAX_CHARS_PER_LINE; x++) {
            UInt8 pattern = 0;

            if (x >= hadjust && x < charWidth + hadjust) {
                pattern = crtcROM[16*crtcMemory[charAddress]+charRaster];

                if (charAddress == crtc->cursor.addressStart) {
                    if (((crtc->frameCounter - crtc->cursor.blinkstart) & crtc->cursor.blinkrate) || (crtc->cursor.mode==CURSOR_NOBLINK)) {
                        pattern ^= charRaster >= crtc->cursor.rasterStart && charRaster <= crtc->cursor.rasterEnd ? 0xff : 0;
                    }
                }
            }
            linePtr[0] = color[(pattern >> 7) & 1];
            linePtr[1] = color[(pattern >> 6) & 1];
            linePtr[2] = color[(pattern >> 5) & 1];
            linePtr[3] = color[(pattern >> 4) & 1];
            linePtr[4] = color[(pattern >> 3) & 1];
            linePtr[5] = color[(pattern >> 2) & 1];
            linePtr[6] = color[(pattern >> 1) & 1];
            linePtr += 7;
            charAddress++;
        }
    }
}

static void crtcCursorUpdate(CRTC6845* crtc)
{
    switch (crtc->registers.reg[CRTC_R10] & 0x60 ) {
    case 32:
        crtc->cursor.mode = CURSOR_DISABLED;
        crtc->cursor.blinkrate = 0;
        break;
    case 64:
        crtc->cursor.mode = CURSOR_BLINK;
        crtc->cursor.blinkrate = 16;
        break;
    case 96:
        crtc->cursor.mode = CURSOR_BLINK;
        crtc->cursor.blinkrate = 32;
        break;
    default:
        crtc->cursor.mode = CURSOR_NOBLINK;
        crtc->cursor.blinkrate = 0;
    }
    crtc->cursor.blinkstart = crtc->frameCounter - crtc->cursor.blinkrate;
    crtc->cursor.rasterStart = crtc->registers.reg[CRTC_R10] & 0x1f;
}

// Timer callback that is called once every frame
static void crtcOnDisplay(CRTC6845* crtc, UInt32 time)
{
    // Render VRAM if video is connected
    if (crtc->videoEnabled)
        crtcRenderVideoBuffer(crtc);

    boardTimerAdd(crtc->timerDisplay, time + REFRESH_PERIOD);
}

// Callback called when video connector is enabled
static void crtcVideoEnable(CRTC6845* crtc)
{
    crtc->videoEnabled = 1;
}

// Callback called when video connector is disabled
static void crtcVideoDisable(CRTC6845* crtc)
{
    crtc->videoEnabled = 0;
}

static void saveState(CRTC6845* crtc)
{
    SaveState* state = saveStateOpenForWrite("crtc6845");

    saveStateClose(state);
}

static void loadState(CRTC6845* crtc)
{
    SaveState* state = saveStateOpenForRead("vdp");

    saveStateClose(state);
}
UInt8 crtcRead(CRTC6845* crtc, UInt16 ioPort)
{
    if (crtc->registers.address < 18)
        return crtc->registers.reg[crtc->registers.address];

    return 0xff;
}

void crtcWrite(CRTC6845* crtc, UInt16 ioPort, UInt8 value)
{
    if (crtc->registers.address < 16) {
        value &= crtcRegisterValueMask[crtc->registers.address];
        crtc->registers.reg[crtc->registers.address] = value;
        switch (crtc->registers.address) {
        case CRTC_R10:
            crtcCursorUpdate(crtc);
            break;
        case CRTC_R11:
            crtc->cursor.rasterEnd = crtc->registers.reg[CRTC_R11];
            break;
        case CRTC_R14:
        case CRTC_R15:
            crtc->cursor.addressStart = (crtc->registers.reg[CRTC_R14] << 8) | crtc->registers.reg[CRTC_R15];
            crtc->cursor.blinkstart = crtc->frameCounter - crtc->cursor.blinkrate;
            break;
        }
    }
}

void crtcWriteLatch(CRTC6845* crtc, UInt16 ioPort, UInt8 value)
{
    crtc->registers.address = value & 0x1f;
}

void crtcMemWrite(UInt16 address, UInt8 value)
{
    if (address < 0x800)
        crtcMemory[address] = value;
}

UInt8 crtcMemRead(UInt16 address)
{
    if (address < 0x800)
        return crtcMemory[address];
    else
        return 0xff;
}

static void crtc6845Reset(CRTC6845* crtc)
{
    memset(&crtc->registers, 0, sizeof(&crtc->registers));
    memset(&crtc->cursor, 0, sizeof(&crtc->cursor));
    memset(crtcMemory, 0xff, sizeof(crtcMemory));
    crtc->frameCounter = 0;
}

static void crtc6845Destroy(CRTC6845* crtc)
{
    deviceManagerUnregister(crtc->deviceHandle);
    videoManagerUnregister(crtc->videoHandle);
    boardTimerDestroy(crtc->timerDisplay);

    free(crtc);    
}

CRTC6845* crtc6845Create(int frameRate, UInt8* romData, int size)
{
    CRTC6845* crtc;

    if (size != 0x1000)
    	return NULL;

    memset(crtcROM, 0xff, sizeof(crtcROM));
    memcpy(&crtcROM[0], romData, size);

    crtc = malloc(sizeof(CRTC6845));
    crtc6845Reset(crtc);
    crtc->frameRate = frameRate;

    // Create and start frame refresh timer
    crtc->timerDisplay = boardTimerCreate(crtcOnDisplay, crtc);
    boardTimerAdd(crtc->timerDisplay, boardSystemTime() + REFRESH_PERIOD);

    // Initialize device
    {
        DeviceCallbacks callbacks = { crtc6845Destroy, crtc6845Reset, saveState, loadState };
        crtc->deviceHandle = deviceManagerRegister(ROM_SVI80COL, &callbacks, crtc);
    }

    // Initialize video frame buffer
    {
        VideoCallbacks videoCallbacks = { crtcVideoEnable, crtcVideoDisable };
        crtc->frameBufferData = frameBufferDataCreate(DISPLAY_WIDTH, DISPLAY_HEIGHT, 2);
        crtc->videoHandle = videoManagerRegister("CRTC6845", crtc->frameBufferData, &videoCallbacks, crtc);
    }

    return crtc;
}
