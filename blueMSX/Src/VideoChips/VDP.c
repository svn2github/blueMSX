/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoChips/VDP.c,v $
**
** $Revision: 1.19 $
**
** $Date: 2005-02-05 01:17:26 $
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
#include "VDP.h"
#include "V9938.h"
#include "Board.h"
#include "Board.h"
#include "IoPort.h"
#include "SaveState.h"
#include "DeviceManager.h"
#include "VideoManager.h"
#include "FrameBuffer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Global configuration (not device specific)

static int spritesEnable = 1;
static int displayEnable = 1;
static int refreshRate   = 0;

void vdpSetSpritesEnable(int enable) {
    spritesEnable = enable ? 1 : 0;
}

int vdpGetSpritesEnable() {
    return spritesEnable;
}

void vdpSetDisplayEnable(int enable) {
    displayEnable = enable ? 1 : 0;
}

int vdpGetDisplayEnable() {
    return displayEnable;
}

int vdpGetRefreshRate() 
{
    return refreshRate;
}

// ....

extern UInt32  emuPalette0;
extern UInt32  emuPalette[300];


#define HPERIOD      1368

#define INT_IE0     0x01
#define INT_IE1     0x02

#define VRAM_SIZE (128 * 1024)

static int vramAddr;
#define MAP_VRAM(vdp, addr) ((vdp)->vram + ((vramAddr = addr, (vdp)->screenMode >= 7 && (vdp)->screenMode <= 12 ? (vramAddr >> 1 | ((vramAddr & 1) << 16)) : vramAddr) & (vdp)->vramMask))

#define vdpIsSpritesBig(regs)        (regs[1]  & 0x01)
#define vdpIsSprites16x16(regs)      (regs[1]  & 0x02)
#define vdpIsSpritesOff(regs)        (regs[8]  & 0x02)
#define vdpIsColor0Solid(regs)       (regs[8]  & 0x20)
#define vdpIsVideoPal(vdp)          (((vdp)->vdpRegs[9]  & (vdp)->palMask & 0x02) | (vdp)->palValue)
#define vdpIsOddPage(vdp)           (((~(vdp)->vdpStatus[2] & 0x02) << 7) & (((vdp)->vdpRegs[9]  & 0x04) << 6))
#define vdpIsInterlaceOn(regs)       (regs[9]  & 0x08)
#define vdpIsScanLines212(regs)      (regs[9]  & 0x80)
#define vdpIsEdgeMasked(regs)        (regs[25] & 0x02)
#define vdpIsModeYJK(regs)           (regs[25] & 0x08)
#define vdpIsModeYAE(regs)           (regs[25] & 0x10)
#define vdpVScroll(vdp)              ((vdp)->vdpRegs[23])
#define vdpHScroll(vdp)       ((((int)((vdp)->vdpRegs[26]&0x3F)<<3)-(int)((vdp)->vdpRegs[27]&0x07))&~(~(int)vdpHScroll512(vdp)<<8))
#define vdpHScroll512(vdp)    ((vdp)->vdpRegs[25]&((vdp)->vdpRegs[2]>>5)&0x1)


static const UInt8 registerValueMaskMSX1[8] = {
	0x03, 0xfb, 0x0f, 0xff, 0x07, 0x7f, 0x07, 0xff
};

static const UInt8 registerValueMaskMSX2[64] = {
	0x7e, 0x7b, 0x7f, 0xff, 0x3f, 0xff, 0x3f, 0xff,
	0xfb, 0xbf, 0x07, 0x03, 0xff, 0xff, 0x07, 0x0f,
	0x0f, 0xbf, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0xff,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

static const UInt8 registerValueMaskMSX2p[64] = {
	0x7e, 0x7b, 0x7f, 0xff, 0x3f, 0xff, 0x3f, 0xff,
	0xfb, 0xbf, 0x07, 0x03, 0xff, 0xff, 0x07, 0x0f,
	0x0f, 0xbf, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0xff,
    0x00, 0x7f, 0x3f, 0x07, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

static UInt32 msx1Palette[16] = {
    0x000000, 0x000000, 0x21c842, 0x5edc78, 0x5455ed, 0x7d76fc, 0xd4524d, 0x42ebf5,
    0xfc5554, 0xff7978, 0xd4c154, 0xe6ce80, 0x21b03b, 0xc95bba, 0xcccccc, 0xffffff
};

static UInt32 defaultPalette[16] = {
    0x000000, 0x000000, 0x24da24, 0x68ff68, 0x2424ff, 0x4868ff, 0xb62424, 0x48daff,
    0xff2424, 0xff6868, 0xdada24, 0xdada91, 0x249124, 0xda48b6, 0xb6b6b6, 0xffffff
};

typedef struct VDP VDP;

static void RefreshLineTx80(VDP*, int, int, int);
static void RefreshLine0(VDP*, int, int, int);
static void RefreshLine1(VDP*, int, int, int);
static void RefreshLine2(VDP*, int, int, int);
static void RefreshLine3(VDP*, int, int, int);
static void RefreshLine4(VDP*, int, int, int);
static void RefreshLine5(VDP*, int, int, int);
static void RefreshLine6(VDP*, int, int, int);
static void RefreshLine7(VDP*, int, int, int);
static void RefreshLine8(VDP*, int, int, int);
static void RefreshLine10(VDP*, int, int, int);
static void RefreshLine12(VDP*, int, int, int);

static void sync(VDP*, UInt32);

struct VDP {
    VdpCmdState* cmdEngine;
    void (*RefreshLine)(VDP*, int, int, int);
    int    vdpConnector;
    int    vdpVersion;

    const UInt8* registerValueMask;
    UInt8  registerMask;

    UInt8  palMask;
    UInt8  palValue;
    int    scr0splitLine;
    int    vramPage;
    int    sprGenBase;
    int    sprTabBase;
    int    colTabBase;
    int    chrTabBase;
    int    chrGenBase;
    UInt8  FGColor;
    UInt8  BGColor;
    UInt8  XFGColor;
    UInt8  XBGColor;
    int    blinkFlag;
    int    blinkCnt;
    int    drawArea;
    int    palette[16];
    int    vramPages;
    int    vram128;
    int    vramMask;
    int    lineOffset;
    UInt32 intStartTime;
    int    firstLine;
    int    lastLine;
    int    leftBorder;
    UInt32 hRefresh;

    int    curLine;

    int    screenOn;
    int    VAdjust;
    int    HAdjust;

    int screenMode;
    UInt8  vdpRegs[64];
    UInt8  vdpStatus[16];

    int    palKey;
    int    vdpKey;
    UInt8  vdpData;
    UInt8  vdpDataLatch;
    UInt16 vramAddress;

    BoardTimer* timerDisplay;
    BoardTimer* timerDrawAreaStart;
    BoardTimer* timerVStart;
    BoardTimer* timerScrModeChange;
    BoardTimer* timerHint;
    BoardTimer* timerHint2;
    BoardTimer* timerVint;

    UInt32 frameStartTime;
    UInt32 timeScrMode;
    UInt32 timeHint;
    UInt32 timeVint;
    UInt32 timeDrawAreaStart;
    UInt32 timeVStart;
    UInt32 timeDisplay;

    UInt8  vram[VRAM_SIZE];
    
    int deviceHandle;
    int videoHandle;
    int videoEnabled;

    FrameBufferData* frameBuffer;
};

static void vdpBlink(VDP* vdp)
{
    if(vdp->blinkCnt) {
        vdp->blinkCnt--;
    }
    else {
        vdp->blinkFlag = !vdp->blinkFlag;
        if (!vdp->vdpRegs[13]) { 
            vdp->XFGColor = vdp->FGColor;
            vdp->XBGColor = vdp->BGColor; 
        }
        else {
            vdp->blinkCnt = (vdp->blinkFlag ? vdp->vdpRegs[13] & 0x0f : vdp->vdpRegs[13] >> 4) * 10;
            if(vdp->blinkCnt) {
                if (vdp->blinkFlag) { 
                    vdp->XFGColor = vdp->FGColor;
                    vdp->XBGColor = vdp->BGColor; 
                }
                else { 
                    vdp->XFGColor = vdp->vdpRegs[12] >> 4; 
                    vdp->XBGColor = vdp->vdpRegs[12] & 0x0f; 
                }
            }
        }
    }
}

static void scheduleScrModeChange(VDP* vdp)
{
    vdp->timeScrMode = vdp->frameStartTime + HPERIOD * (1 + (boardSystemTime() - vdp->frameStartTime) / HPERIOD);
    boardTimerAdd(vdp->timerScrModeChange, vdp->timeScrMode);
}

static void scheduleHint(VDP* vdp)
{
    vdp->timeHint = vdp->frameStartTime + (vdp->firstLine + ((vdp->vdpRegs[19] - vdp->vdpRegs[23]) & 0xff)) * HPERIOD + vdp->leftBorder + vdp->hRefresh;
    boardTimerAdd(vdp->timerHint, vdp->timeHint);
    boardTimerAdd(vdp->timerHint2, vdp->timeHint + 130);
}

static void scheduleVint(VDP* vdp)
{
    vdp->timeVint = vdp->frameStartTime + (vdp->firstLine + ((vdp->vdpRegs[9] & 0x80) ? 212 : 192)) * HPERIOD + vdp->leftBorder - 10;
    boardTimerAdd(vdp->timerVint, vdp->timeVint);
}

static void scheduleDrawAreaStart(VDP* vdp)
{
    vdp->timeDrawAreaStart = vdp->frameStartTime + ((vdp->drawArea ? 3 + 13 : vdp->firstLine) - 1) * HPERIOD + vdp->leftBorder + vdp->hRefresh;
    boardTimerAdd(vdp->timerDrawAreaStart, vdp->timeDrawAreaStart);

    vdp->timeVStart = vdp->frameStartTime + (vdp->firstLine - 1) * HPERIOD + vdp->leftBorder - 10;
    boardTimerAdd(vdp->timerVStart, vdp->timeVStart);
}

static void onHint(VDP* vdp, UInt32 time)
{
    sync(vdp, time);
    vdp->intStartTime = time;
}

static void onHint2(VDP* vdp, UInt32 time)
{
    sync(vdp, time);

    if (vdp->vdpRegs[0] & 0x10) {
        boardSetInt(INT_IE1);
    }
}

static void onVint(VDP* vdp, UInt32 time)
{
    sync(vdp, time);

    vdp->lineOffset = 0;
    vdp->vdpStatus[0] |= 0x80;
    vdp->vdpStatus[2] |= 0x40;
    if (vdp->vdpRegs[1] & 0x20) {
        boardSetInt(INT_IE0);
    }
    vdp->drawArea = 0;
    vdpSetTimingMode(vdp->cmdEngine, vdp->vdpRegs[8] & 2);
}

static void onVStart(VDP* vdp, UInt32 time)
{
    sync(vdp, time);
    vdp->lineOffset = 0;
    vdp->vdpStatus[2] &= ~0x40;
}

static void onDrawAreaStart(VDP* vdp, UInt32 time)
{
    sync(vdp, time);

    vdp->drawArea = 1;
    vdp->vdpStatus[2] &= ~0x40;
    vdpSetTimingMode(vdp->cmdEngine, ((vdp->vdpRegs[1] >> 6) & vdp->drawArea) | (vdp->vdpRegs[8] & 2));
}

static void onDisplay(VDP* vdp, UInt32 time)
{
    int isPal = vdpIsVideoPal(vdp); 

    if (vdp->videoEnabled) {
        FrameBuffer* frameBuffer;
        frameBuffer = frameBufferFlipDrawFrame();
        frameBuffer->lines = 240;
        if (vdpIsInterlaceOn(vdp->vdpRegs)) {
            frameBuffer->interlace = 
                (vdp->vdpStatus[2] & 0x02) && (vdp->vdpRegs[9]  & 0x04) && vdp->vram128 ? INTERLACE_EVEN : INTERLACE_ODD;
        }
        else {
            frameBuffer->interlace = INTERLACE_NONE;
        }
    }

    refreshRate = isPal ? 50 : 60; // Update global refresh rate

    sync(vdp, time);

    vdp->scr0splitLine = 0;
    vdp->curLine = 0;

    vdp->lastLine = isPal ? 313 : 262;
    vdp->firstLine = (isPal ? 27 : 0) + (vdpIsScanLines212(vdp->vdpRegs) ? 14 : 24) + vdp->VAdjust;
    if (!(vdp->vdpRegs[0] & 0x10)) {
        boardClearInt(INT_IE1);
    }
    vdp->vdpStatus[2] ^= 0x02;
    RefreshScreen(vdp->screenMode);

    vdpBlink(vdp);

    vdp->frameStartTime = vdp->timeDisplay;
    vdp->timeDisplay += HPERIOD * vdp->lastLine;
    boardTimerAdd(vdp->timerDisplay, vdp->timeDisplay);

    scheduleDrawAreaStart(vdp);
    scheduleHint(vdp);
    scheduleVint(vdp);
}

static void onScrModeChange(VDP* vdp, UInt32 time)
{
    int scanLine = (boardSystemTime() - vdp->frameStartTime) / HPERIOD;

    sync(vdp, time);

    switch (((vdp->vdpRegs[0] & 0x0e) >> 1) | (vdp->vdpRegs[1] & 0x18)) {
    case 0x10: vdp->screenMode = 0; break;
    case 0x00: vdp->screenMode = 1; break;
    case 0x01: vdp->screenMode = 2; break;
    case 0x08: vdp->screenMode = 3; break;
    case 0x02: vdp->screenMode = 4; break;
    case 0x03: vdp->screenMode = 5; break;
    case 0x04: vdp->screenMode = 6; break;
    case 0x05: vdp->screenMode = 7; break;
    case 0x07: vdp->screenMode = 8; break;
    case 0x12: vdp->screenMode = 13; break;
    }

    vdp->scr0splitLine = (scanLine - vdp->firstLine) & ~7;

    vdp->chrTabBase = (((int)vdp->vdpRegs[2] << 10) | ~(-1 << 10)) & vdp->vramMask;
    vdp->chrGenBase = (((int)vdp->vdpRegs[4] << 11) | ~(-1 << 11)) & vdp->vramMask;
    vdp->colTabBase = (((int)vdp->vdpRegs[10] << 14) | ((int)vdp->vdpRegs[3] << 6) | ~(-1 << 6)) & vdp->vramMask;

    vdp->sprTabBase = (((int)vdp->vdpRegs[11] << 15) | ((int)vdp->vdpRegs[5] << 7) | ~(-1 << 7)) & vdp->vramMask;
    vdp->sprGenBase = (((int)vdp->vdpRegs[6] << 11) | ~(-1 << 11)) & vdp->vramMask;

    vdp->screenOn = vdp->vdpRegs[1] & 0x40;
    
    vdpSetScreenMode(vdp->cmdEngine, vdp->screenMode, vdp->vdpRegs[25] & 0x40);

    switch (vdp->screenMode) {
    case 0: vdp->RefreshLine = RefreshLine0; break;
    case 1: vdp->RefreshLine = RefreshLine1; break;
    case 2: vdp->RefreshLine = RefreshLine2; break;
    case 3: vdp->RefreshLine = RefreshLine3; break;
    case 4: vdp->RefreshLine = RefreshLine4; break;
    case 5: vdp->RefreshLine = RefreshLine5; break;
    case 6: vdp->RefreshLine = RefreshLine6; break;
    case 7: 
        if(!vdpIsModeYJK(vdp->vdpRegs)) {
            vdp->RefreshLine = RefreshLine7; 
            break;
        }
    case 8: 
        if(vdp->screenMode == 8 && !vdpIsModeYJK(vdp->vdpRegs)) {
            vdp->RefreshLine = RefreshLine8; 
        }
        else if (vdpIsModeYAE(vdp->vdpRegs)) {
            vdp->RefreshLine = RefreshLine10; 
            vdp->screenMode = 10;
        }
        else {
            vdp->RefreshLine = RefreshLine12; 
            vdp->screenMode = 12;
        }
        break;
    default:
        vdp->RefreshLine = RefreshLineTx80; break;
        vdp->screenMode = 13;
        break;
    }
    
    if (vdp->screenMode == 0 || vdp->screenMode == 13) {
        vdp->hRefresh = 960;
        vdp->leftBorder = 102 + 92;
    }
    else {
        vdp->hRefresh = 1024;
        vdp->leftBorder = 102 + 56;
    }

    vdp->VAdjust = (-((Int8)(vdp->vdpRegs[18]) >> 4));
    vdp->HAdjust = (-((Int8)(vdp->vdpRegs[18] << 4) >> 4));
}

static void vdpUpdateRegisters(VDP* vdp, UInt8 reg, UInt8 value)
{ 
    UInt8 change;

    reg   &= vdp->registerMask;
    value &= vdp->registerValueMask[reg];
    sync(vdp, boardSystemTime());
    
    if (reg >= 0x20) {   
        vdpCmdWrite(vdp->cmdEngine, reg - 0x20, value, boardSystemTime());
        return;
    }

    change = vdp->vdpRegs[reg] ^ value;
    vdp->vdpRegs[reg] = value;

    switch (reg) {
    case 0: 
        if (!(value & 0x10)) {
            boardClearInt(INT_IE1);
        }

        if (change & 0x0e) {
            scheduleScrModeChange(vdp);
        }

        break;

    case 1: 
        if (vdp->vdpStatus[0] & 0x80) {
			if (value & 0x20) {
				boardSetInt(INT_IE0);
			}
			else {
				boardClearInt(INT_IE0);
			}
        }

        if (change & 0x58) {
            scheduleScrModeChange(vdp);
        }
        
        vdpSetTimingMode(vdp->cmdEngine, ((value >> 6) & vdp->drawArea) | (vdp->vdpRegs[8] & 2));
        break;

    case 2: 
        vdp->chrTabBase = (((int)value << 10) | ~(-1 << 10)) & vdp->vramMask;
        break;

    case 3: 
        vdp->colTabBase = (((int)vdp->vdpRegs[10] << 14) | ((int)value << 6) | ~(-1 << 6)) & vdp->vramMask;
        break;

    case 4: 
        vdp->chrGenBase = (((int)value << 11) | ~(-1 << 11)) & vdp->vramMask;
        break;

    case 5: 
        vdp->sprTabBase = ((vdp->vdpRegs[11] << 15) | (value << 7) | ~(-1 << 7)) & ((vdp->vramPages << 14) - 1);
        break;

    case 6: 
    	vdp->sprGenBase = ((value << 11) | ~(-1 << 11)) & ((vdp->vramPages << 14) - 1);
        break;

    case 7: 
        vdp->FGColor = value >> 4;
        vdp->BGColor = value & 0x0F;
        emuPalette[0] = (!vdp->BGColor || (vdp->vdpRegs[8] & 0x20)) ? emuPalette0 : emuPalette[vdp->BGColor];
        break;

    case 8:
        vdpSetTimingMode(vdp->cmdEngine, ((vdp->vdpRegs[1] >> 6) & vdp->drawArea) | (value & 2));
        emuPalette[0] = (!vdp->BGColor || (value & 0x20)) ? emuPalette0 : emuPalette[vdp->BGColor];
        break;

    case 9:
        value = (value & vdp->palMask) | vdp->palValue;
        if (change & 0x80) {
            scheduleVint(vdp);
        }
        break;

    case 10: 
        vdp->colTabBase = (((int)value << 14) | ((int)vdp->vdpRegs[3] << 6) | ~(-1 << 6)) & vdp->vramMask;
        break;

    case 11: 
        vdp->sprTabBase = ((value << 15) | (vdp->vdpRegs[5] << 7) | ~(-1 << 7)) & ((vdp->vramPages << 14) - 1);
        break;

    case 14: 
        value &= vdp->vramPages - 1;
        vdp->vramPage = (int)value << 14;
        break;

    case 16: 
        vdp->palKey = 0;
        break;

    case 18:
        if (change) {
            scheduleScrModeChange(vdp);
        }
        break;

    case 19:
        boardClearInt(INT_IE1);
        if (change) {
            scheduleHint(vdp);
        }
        break;

    case 23:
        if (change) {
            scheduleHint(vdp);
        }
        if (!(vdp->vdpRegs[0] & 0x10)) {
            boardClearInt(INT_IE1);
        }
        break;

    case 25: 
        if (change) {
            scheduleScrModeChange(vdp);
        }
        break;

    default:
        break;
    }
} 

static UInt8 read(VDP* vdp, UInt16 ioPort) 
{
    UInt8 value;

    if (vdp->vdpVersion == VDP_V9938 || vdp->vdpVersion == VDP_V9958) {
        vdpCmdExecute(vdp->cmdEngine, boardSystemTime());
    }

	value = vdp->vdpData;
	vdp->vdpData = *MAP_VRAM(vdp, (vdp->vdpRegs[14] << 14) | vdp->vramAddress);
	vdp->vramAddress = (vdp->vramAddress + 1) & 0x3fff;
    if (vdp->vramAddress == 0 && vdp->screenMode > 3) {
        vdp->vdpRegs[14] = (vdp->vdpRegs[14] + 1) & (vdp->vramPages - 1);
    }
	vdp->vdpKey = 0;

    return value;
}

static UInt8 readStatus(VDP* vdp, UInt16 ioPort)
{
    UInt8 vdpStatus;

    sync(vdp, boardSystemTime());

    if (vdp->vdpVersion == VDP_TMS9929A || vdp->vdpVersion == VDP_TMS99x8A) {
        vdpStatus = vdp->vdpStatus[0];
        vdp->vdpStatus[0] &= 0x1f;
        boardClearInt(INT_IE0);
        return vdpStatus;
    }
    
    vdpStatus = vdp->vdpStatus[vdp->vdpRegs[15]];
    
    vdp->vdpKey = 0;

    switch(vdp->vdpRegs[15]) {
    case 0: 
        vdp->vdpStatus[0] &= 0x1f;
        boardClearInt(INT_IE0);
        break;

    case 1: 
        if (vdp->vdpRegs[0] & 0x10) {
            if (boardGetInt(INT_IE1)) {
                boardClearInt(INT_IE1);
                vdpStatus |=  0x01;
            }
        }
        else {
            if (boardSystemTime() - vdp->timeHint < HPERIOD - vdp->hRefresh) {
                vdpStatus |= 0x01;
            }
        }
        break;

    case 2:
        {
            UInt32 frameTime = boardSystemTime() - vdp->frameStartTime;
            vdpStatus |= 0x40 | 0x20 | vdpGetStatus(vdp->cmdEngine);
            if (vdp->drawArea || (frameTime - ((vdp->firstLine - 1) * HPERIOD + vdp->leftBorder - 10) < 4 * HPERIOD)) {
                vdpStatus &= ~0x40;
            }
            if (frameTime % HPERIOD - vdp->leftBorder < (UInt32)vdp->hRefresh + 57 + 26) {
                vdpStatus &= ~0x20;
            }
        }
        break;

    case 7: 
        vdpStatus = vdpGetColor(vdp->cmdEngine);
        break;

    case 8: 
        vdpStatus = (UInt8)vdpGetBorderX(vdp->cmdEngine);
        break;

    case 9: 
        vdpStatus = (UInt8)(vdpGetBorderX(vdp->cmdEngine) >> 8);
        break;
    }

    return vdpStatus;
}

static void write(VDP* vdp, UInt16 ioPort, UInt8 value)
{
    sync(vdp, boardSystemTime());

    *MAP_VRAM(vdp, ((vdp->vdpRegs[14] << 14) | vdp->vramAddress) & vdp->vramMask) = value;
	vdp->vdpData = value;
	vdp->vdpKey = 0;
    vdp->vramAddress = (vdp->vramAddress + 1) & 0x3fff;
    if (vdp->vramAddress == 0 && vdp->screenMode > 3) {
        vdp->vdpRegs[14] = (vdp->vdpRegs[14] + 1 )& (vdp->vramPages - 1);
    }
}

static void writeLatch(VDP* vdp, UInt16 ioPort, UInt8 value)
{
    if (vdp->vdpKey) {
		if (value & 0x80) {
			if (!(value & 0x40)) {
                vdpUpdateRegisters(vdp, value, vdp->vdpDataLatch);
			}
		} 
        else {
			vdp->vramAddress = ((UInt16)value << 8 | vdp->vdpDataLatch) & 0x3fff;
			if (!(value & 0x40)) {
				read(vdp, ioPort);
			}
		}
		vdp->vdpKey = 0;
	} else {
		vdp->vdpDataLatch = value;
		vdp->vdpKey = 1;
	}
}

static void writePaletteLatch(VDP* vdp, UInt16 ioPort, UInt8 value)
{
    if (vdp->palKey) {
		int palEntry = vdp->vdpRegs[16];
        sync(vdp, boardSystemTime());
        vdp->palette[palEntry] = (((UInt32)(vdp->vdpDataLatch & 0x70) * 255 / 112) << 16) |
                            (((UInt32)(value & 0x07) * 255 / 7) << 8) |
                            ((UInt32)(vdp->vdpDataLatch & 0x07) * 255 / 7);
        SetColor(palEntry, vdp->palette[palEntry]);
        emuPalette[0] = (!vdp->BGColor || (vdp->vdpRegs[8] & 0x20)) ? emuPalette0 : emuPalette[vdp->BGColor];

        vdp->vdpRegs[16] = (palEntry + 1) & 0x0f;
		vdp->palKey = 0;
	} 
    else {
		vdp->vdpDataLatch = value;
		vdp->palKey = 1;
	}
}

static void writeRegister(VDP* vdp, UInt16 ioPort, UInt8 value)
{
    int reg;

	vdp->vdpDataLatch = value;
    reg = vdp->vdpRegs[17];
    if((reg & 0x3f) != 17) {
        vdpUpdateRegisters(vdp, reg, value);
    }
    if(~reg & 0x80) {
        vdp->vdpRegs[17] = (reg + 1) & 0x3f;
    }
}

static void sync(VDP* vdp, UInt32 systemTime) 
{
    int frameTime = systemTime - vdp->frameStartTime;
    int scanLine = frameTime / HPERIOD;
    int lineTime = frameTime % HPERIOD - vdp->leftBorder + 20;
    int curLineOffset;

    if (vdp->vdpVersion == VDP_V9938 || vdp->vdpVersion == VDP_V9958) {
        vdpCmdExecute(vdp->cmdEngine, boardSystemTime());
    }

    if (!vdp->videoEnabled) {
        return;
    }

    if (vdp->curLine < scanLine) {
        if (vdp->lineOffset <= 32) {
            vdp->RefreshLine(vdp, vdp->curLine, vdp->lineOffset, 33);
        }
        vdp->lineOffset = 0;
        vdp->curLine++;
        while (vdp->curLine < scanLine) {
            vdp->RefreshLine(vdp, vdp->curLine, 0, 33);
            vdp->curLine++;
        }
    }

    if (vdp->lineOffset > 32 || lineTime < 0) {
        return;
    }

    curLineOffset = lineTime / 32;
    if (curLineOffset > 33) {
        curLineOffset = 33;
    }

    if (vdp->lineOffset < curLineOffset) {
        vdp->RefreshLine(vdp, vdp->curLine, vdp->lineOffset, curLineOffset);
        vdp->lineOffset = curLineOffset;
    }
}

static void saveState(VDP* vdp)
{
    SaveState* state = saveStateOpenForWrite("vdp");
    char tag[32];
    int index;

    saveStateGet(state, "frameStartTime",    vdp->frameStartTime);
    saveStateGet(state, "timeScrMode",       vdp->timeScrMode);
    saveStateGet(state, "timeHint",          vdp->timeHint);
    saveStateGet(state, "timeVint",          vdp->timeVint);
    saveStateGet(state, "timeDrawAreaStart", vdp->timeDrawAreaStart);
    saveStateGet(state, "timeVStart",        vdp->timeVStart);
    saveStateGet(state, "timeDisplay",       vdp->timeDisplay);

    saveStateSet(state, "palKey",          vdp->palKey);
    saveStateSet(state, "vdpKey",          vdp->vdpKey);
    saveStateSet(state, "vramAddress",     vdp->vramAddress);
    saveStateSet(state, "vdpData",         vdp->vdpData);
    saveStateSet(state, "vdpDataLatch",    vdp->vdpDataLatch);
    saveStateSet(state, "xfgColor",        vdp->XFGColor);
    saveStateSet(state, "xbgColor",        vdp->XBGColor);
    saveStateSet(state, "intStartTime",    vdp->intStartTime);
    saveStateSet(state, "firstLine",       vdp->firstLine);
    saveStateSet(state, "blinkFlag",       vdp->blinkFlag);
    saveStateSet(state, "blinkCnt",        vdp->blinkCnt);
    saveStateSet(state, "drawArea",        vdp->drawArea);
    saveStateSet(state, "vramPages",       vdp->vramPages);
    saveStateSet(state, "vdpConnector",    vdp->vdpConnector);
    saveStateSet(state, "vdpVersion",      vdp->vdpVersion);
    saveStateGet(state, "leftBorder",      vdp->leftBorder);
    saveStateGet(state, "hRefresh",        vdp->hRefresh);

    saveStateSetBuffer(state, "regs", vdp->vdpRegs, sizeof(vdp->vdpRegs));
    saveStateSetBuffer(state, "status", vdp->vdpStatus, sizeof(vdp->vdpStatus));

    for (index = 0; index < sizeof(vdp->palette) / sizeof(vdp->palette[0]); index++) {
        sprintf(tag, "palette%d", index);
        saveStateSet(state, tag, vdp->palette[index]);
    }
    
    saveStateSetBuffer(state, "vram", vdp->vram, 0x4000 * vdp->vramPages);

    saveStateClose(state);

    vdpCmdSaveState(vdp->cmdEngine);
}

static void loadState(VDP* vdp)
{
    SaveState* state = saveStateOpenForRead("vdp");
    UInt32 systemTime = boardSystemTime() + 100;
    char tag[32];
    int index;

    vdp->frameStartTime    =      saveStateGet(state, "frameStartTime",    systemTime);
    vdp->timeScrMode       =      saveStateGet(state, "timeScrMode",       systemTime);
    vdp->timeHint          =      saveStateGet(state, "timeHint",          systemTime);
    vdp->timeVint          =      saveStateGet(state, "timeVint",          systemTime);
    vdp->timeDrawAreaStart =      saveStateGet(state, "timeDrawAreaStart", systemTime);
    vdp->timeVStart        =      saveStateGet(state, "timeVStart",        systemTime);
    vdp->timeDisplay       =      saveStateGet(state, "timeDisplay",       systemTime);

    vdp->palKey         =         saveStateGet(state, "palKey",          0);
    vdp->vdpKey         =         saveStateGet(state, "vdpKey",          0);
    vdp->vramAddress    = (UInt16)saveStateGet(state, "vramAddress",     0);
    vdp->vdpData        = (UInt8) saveStateGet(state, "vdpData",         0);
    vdp->vdpDataLatch   = (UInt8) saveStateGet(state, "vdpDataLatch",    0);
    vdp->XFGColor       = (UInt8) saveStateGet(state, "xfgColor",        0);
    vdp->XBGColor       = (UInt8) saveStateGet(state, "xbgColor",        0);
    vdp->intStartTime   =         saveStateGet(state, "intStartTime",    0);
    vdp->firstLine      =         saveStateGet(state, "firstLine",       1);
    vdp->blinkFlag      =         saveStateGet(state, "blinkFlag",       0);
    vdp->blinkCnt       =         saveStateGet(state, "blinkCnt",        0);
    vdp->drawArea       =         saveStateGet(state, "drawArea",        0);
    vdp->vramPages      =         saveStateGet(state, "vramPages",       8);
    vdp->vdpConnector   =         saveStateGet(state, "vdpConnector",    VDP_MSX);
    vdp->vdpVersion     =         saveStateGet(state, "vdpVersion",      0);
    vdp->leftBorder     =         saveStateGet(state, "leftBorder",      200);
    vdp->hRefresh       =         saveStateGet(state, "hRefresh",        1024);

    saveStateGetBuffer(state, "regs", vdp->vdpRegs, sizeof(vdp->vdpRegs));
    saveStateGetBuffer(state, "status", vdp->vdpStatus, sizeof(vdp->vdpStatus));

    for (index = 0; index < sizeof(vdp->palette) / sizeof(vdp->palette[0]); index++) {
        sprintf(tag, "palette%d", index);
        vdp->palette[index] = saveStateGet(state, tag, 0);
    }

    saveStateGetBuffer(state, "vram", vdp->vram, 0x4000 * vdp->vramPages);

    saveStateClose(state);

    vdp->vramMask        = (vdp->vramPages << 14) - 1;
    vdp->vram128         = vdp->vramPages >= 8 ? 0x10000 : 0;
    vdp->vramPage        = ((int)vdp->vdpRegs[14] << 14) & (vdp->vramPages - 1);
    vdp->lastLine        = vdpIsVideoPal(vdp) ? 313 : 262;    
    vdp->FGColor         = vdp->vdpRegs[7] >> 4;
    vdp->BGColor         = vdp->vdpRegs[7] & 0x0F;
    vdp->lineOffset      = 0;

    switch (vdp->vdpVersion) {
    case VDP_TMS9929A:
    case VDP_TMS99x8A:
        vdp->registerValueMask = registerValueMaskMSX1;
        vdp->registerMask      = 0x07;
        break;
    case VDP_V9938:
        vdp->registerValueMask = registerValueMaskMSX2;
        vdp->registerMask      = 0x3f;
        break;
    case VDP_V9958:
        vdp->registerValueMask = registerValueMaskMSX2p;
        vdp->registerMask      = 0x3f;
        break;
    }

    vdpCmdLoadState(vdp->cmdEngine);

    /* Set vdp->palette */
    for (index = 0; index < 16; index++) {
        SetColor(index, vdp->palette[index]);
    }
    emuPalette[0] = (!vdp->BGColor || (vdp->vdpRegs[8] & 0x20)) ? emuPalette0 : emuPalette[vdp->BGColor];

    onScrModeChange(vdp, boardSystemTime());

    boardTimerAdd(vdp->timerScrModeChange, vdp->timeScrMode);
    boardTimerAdd(vdp->timerHint, vdp->timeHint);
    boardTimerAdd(vdp->timerHint2, vdp->timeHint);
    boardTimerAdd(vdp->timerVint, vdp->timeVint);
    boardTimerAdd(vdp->timerDrawAreaStart, vdp->timeDrawAreaStart);
    boardTimerAdd(vdp->timerVStart, vdp->timeVStart);
    boardTimerAdd(vdp->timerDisplay, vdp->timeDisplay);
}

static void reset(VDP* vdp)
{
    int i;

    vdp->frameStartTime  = boardSystemTime();
    vdp->timeDisplay     = boardSystemTime();
    vdp->scr0splitLine   = 0;
    vdp->vramPage        = 0;
    vdp->sprGenBase      = 0;
    vdp->sprTabBase      = 0;
    vdp->colTabBase      = 0;
    vdp->chrTabBase      = 0;
    vdp->chrGenBase      = 0;
    vdp->palKey          = 0;
    vdp->vdpKey          = 0;
	vdp->vramAddress     = 0;
	vdp->vdpData         = 0;
	vdp->vdpDataLatch    = 0;
    vdp->FGColor         = 0;
    vdp->BGColor         = 0;
    vdp->XFGColor        = 0;
    vdp->XBGColor        = 0;
    vdp->blinkFlag       = 0;
    vdp->blinkCnt        = 0;
    vdp->drawArea        = 0;
    vdp->intStartTime    = 0;
    vdp->lastLine        = 0;
    vdp->screenOn        = 0;
    vdp->VAdjust         = 0;
    vdp->HAdjust         = 0;
    vdp->hRefresh        = 0;

    vdp->leftBorder      = 200;
    vdp->screenMode      = 1;
    vdp->lineOffset      = 256;
    vdp->firstLine       = 1;
    vdp->lastLine        = -1;

    memset(vdp->palette, 0, sizeof(vdp->palette));
    memset(vdp->vram, 0, VRAM_SIZE);
    memset(vdp->vdpStatus, 0, sizeof(vdp->vdpStatus));
    memset(vdp->vdpRegs, 0, sizeof(vdp->vdpRegs));

    vdp->cmdEngine = vdpCmdCreate(vdp->vramPages << 14, vdp->vram, boardSystemTime());

    vdp->vdpStatus[0] = 0x9f;
    vdp->vdpStatus[1] = vdp->vdpVersion == VDP_V9958 ? 0x04 : 0;
    vdp->vdpStatus[2] = 0x6c;
        
    vdp->vdpRegs[1] = 0x10;
    vdp->vdpRegs[2] = 0xff;
    vdp->vdpRegs[3] = 0xff;
    vdp->vdpRegs[4] = 0xff;
    vdp->vdpRegs[5] = 0xff;
    vdp->vdpRegs[9] = (0x02 & vdp->palMask) | vdp->palValue;

    if (vdp->vdpVersion == VDP_TMS9929A || vdp->vdpVersion == VDP_TMS99x8A) {
        memcpy(vdp->palette, msx1Palette, sizeof(vdp->palette));
    }
    else {
        memcpy(vdp->palette, defaultPalette, sizeof(vdp->palette));
    }

    for (i = 0; i < 16; i++) {
        SetColor(i, vdp->palette[i]);
    }
    emuPalette[0] = (!vdp->BGColor || (vdp->vdpRegs[8] & 0x20)) ? emuPalette0 : emuPalette[vdp->BGColor];

    onScrModeChange(vdp, boardSystemTime());

    onDisplay(vdp, boardSystemTime());
}

static void destroy(VDP* vdp) 
{
    int i;

    deviceManagerUnregister(vdp->deviceHandle);
    videoManagerUnregister(vdp->videoHandle);

    switch (vdp->vdpConnector) {
    case VDP_MSX:
        ioPortUnregister(0x98);
        ioPortUnregister(0x99);
        ioPortUnregister(0x9a);
        ioPortUnregister(0x9b);
        break;

    case VDP_SVI:
        ioPortUnregister(0x80);
        ioPortUnregister(0x81);
        ioPortUnregister(0x84);
        ioPortUnregister(0x85);
        break;

    case VDP_COLECO:
        for (i = 0xa0; i < 0xc0; i++) {
            ioPortUnregister(i);
        }
        break;
    }

    boardTimerDestroy(vdp->timerDisplay);
    boardTimerDestroy(vdp->timerDrawAreaStart);
    boardTimerDestroy(vdp->timerVStart);
    boardTimerDestroy(vdp->timerScrModeChange);
    boardTimerDestroy(vdp->timerHint);
    boardTimerDestroy(vdp->timerHint2);
    boardTimerDestroy(vdp->timerVint);

    vdpCmdDestroy(vdp->cmdEngine);

    frameBufferDataDestroy(vdp->frameBuffer);

    free(vdp);
}

static void videoEnable(VDP* vdp)
{
    vdp->videoEnabled = 1;
}

static void videoDisable(VDP* vdp)
{
    vdp->videoEnabled = 0;
}

void vdpCreate(VdpConnector connector, VdpVersion version, VdpSyncMode sync, int vramPages)
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    VideoCallbacks videoCallbacks = { videoEnable, videoDisable };
    int i;

    VDP* vdp = (VDP*)calloc(1, sizeof(VDP));

    vdp->deviceHandle = deviceManagerRegister(ROM_V9958, &callbacks, vdp);

    vdp->timerDisplay       = boardTimerCreate(onDisplay, vdp);
    vdp->timerDrawAreaStart = boardTimerCreate(onDrawAreaStart, vdp);
    vdp->timerVStart        = boardTimerCreate(onVStart, vdp);
    vdp->timerScrModeChange = boardTimerCreate(onScrModeChange, vdp);
    vdp->timerHint          = boardTimerCreate(onHint, vdp);
    vdp->timerHint2         = boardTimerCreate(onHint2, vdp);
    vdp->timerVint          = boardTimerCreate(onVint, vdp);

    vdp->vramPages     = vramPages;
    vdp->vram128       = vramPages >= 8 ? 0x10000 : 0;
    vdp->vramMask      = (vramPages << 14) - 1;
    vdp->vdpVersion    = version;
    vdp->vdpConnector  = connector;

    vdp->frameBuffer   = frameBufferDataCreate(8 + 256 + 8, 240, 1);
    vdp->videoHandle   = videoManagerRegister(VdpNames[version], vdp->frameBuffer, &videoCallbacks, vdp);

    if (sync == VDP_SYNC_AUTO) {
        vdp->palMask  = ~0;
        vdp->palValue = 0;
    }
    else if (sync == VDP_SYNC_50HZ) {
        vdp->palMask  = ~0x02;
        vdp->palValue = 0x02;
    }
    else if (sync == VDP_SYNC_60HZ) {
        vdp->palMask  = ~0x02;
        vdp->palValue = 0x00;
    }

    reset(vdp);

    switch (vdp->vdpVersion) {
    case VDP_TMS9929A:
        vdp->registerValueMask = registerValueMaskMSX1;
        vdp->registerMask      = 0x07;
        break;
    case VDP_TMS99x8A:
        vdp->registerValueMask = registerValueMaskMSX1;
        vdp->registerMask      = 0x07;
        vdp->vdpRegs[9]          &= ~0x02;
        break;
    case VDP_V9938:
        vdp->registerValueMask = registerValueMaskMSX2;
        vdp->registerMask      = 0x3f;
        break;
    case VDP_V9958:
        vdp->registerValueMask = registerValueMaskMSX2p;
        vdp->registerMask      = 0x3f;
        break;
    }
    
    switch (vdp->vdpConnector) {
    case VDP_MSX:
        ioPortRegister(0x98, read,       write,      vdp);
        ioPortRegister(0x99, readStatus, writeLatch, vdp);
        if (vdp->vdpVersion == VDP_V9938 || vdp->vdpVersion == VDP_V9958) {
            ioPortRegister(0x9a, NULL, writePaletteLatch, vdp);
            ioPortRegister(0x9b, NULL, writeRegister,     vdp);
        }
        break;

    case VDP_SVI:
        ioPortRegister(0x80, NULL,          write,      vdp); // vdp->vdpRegs vdp->vram Write
        ioPortRegister(0x81, NULL,          writeLatch, vdp); // vdp->vdpRegs Address Latch
        ioPortRegister(0x84, read,       NULL,          vdp); // vdp->vdpRegs vdp->vram Read
        ioPortRegister(0x85, readStatus, NULL,          vdp); // vdp->vdpRegs Status Read
        break;

    case VDP_COLECO:
        for (i = 0xa0; i < 0xc0; i += 2) {
            ioPortRegister(i,     read,       write,      vdp);
            ioPortRegister(i + 1, readStatus, writeLatch, vdp);
        }
        break;
    }
}

#include "common.h"

