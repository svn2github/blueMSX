/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoChips/VDP.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2004-12-06 07:48:48 $
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
#include <string.h>
#include <stdio.h>


extern UInt32  emuPalette0;
extern UInt32  emuPalette[300];


#define HPERIOD      1368

#define INT_IE0     0x01
#define INT_IE1     0x02

#define VRAM_SIZE (128 * 1024)

static int vramAddr;
#define MAP_VRAM(addr) (VRAM + ((vramAddr = addr, screenMode >= 7 && screenMode <= 12 ? (vramAddr >> 1 | ((vramAddr & 1) << 16)) : vramAddr) & vramMask))

#define vdpIsSpritesBig(regs)        (regs[1]  & 0x01)
#define vdpIsSprites16x16(regs)      (regs[1]  & 0x02)
#define vdpIsSpritesOff(regs)        (regs[8]  & 0x02)
#define vdpIsColor0Solid(regs)       (regs[8]  & 0x20)
#define vdpIsVideoPal(regs)          ((regs[9]  & palMask & 0x02) | palValue)
#define vdpIsOddPage(regs)           (((~VDPStatus[2] & 0x02) << 7) & ((regs[9]  & 0x04) << 6))
#define vdpIsInterlaceOn(regs)       (regs[9]  & 0x08)
#define vdpIsScanLines212(regs)      (regs[9]  & 0x80)
#define vdpIsEdgeMasked(regs)        (regs[25] & 0x02)
#define vdpIsModeYJK(regs)           (regs[25] & 0x08)
#define vdpIsModeYAE(regs)           (regs[25] & 0x10)
#define VScroll       VDP[23]
#define HScroll       ((((int)(VDP[26]&0x3F)<<3)-(int)(VDP[27]&0x07))&~(~(int)HScroll512<<8))
#define HScroll512    (VDP[25]&(VDP[2]>>5)&0x1)


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


static void RefreshLineTx80(int, int);
static void RefreshLine0(int, int);
static void RefreshLine1(int, int);
static void RefreshLine2(int, int);
static void RefreshLine3(int, int);
static void RefreshLine4(int, int);
static void RefreshLine5(int, int);
static void RefreshLine6(int, int);
static void RefreshLine7(int, int);
static void RefreshLine8(int, int);
static void RefreshLine10(int, int);
static void RefreshLine12(int, int);

static void vdpSync(void);

static void (*RefreshLine)(int, int);

static int    vdpConnector;
static int    vdpVersion;

static const UInt8* registerValueMask;
static UInt8  registerMask;

static UInt8  palMask;
static UInt8  palValue;
static int    scr0splitLine;
static int    vramPage;
static int    sprGenBase;
static int    sprTabBase;
static int    colTabBase;
static int    chrTabBase;
static int    chrGenBase;
static UInt8  FGColor;
static UInt8  BGColor;
static UInt8  XFGColor;
static UInt8  XBGColor;
static int    scanLine;
static int    drawAreaStart;
static int    blinkFlag;
static int    blinkCnt;
static int    drawArea;
static int    palette[16];
static int    VRAMPages;
static int    VRAM128;
static int    vramMask;
static int    scanLines;
static int    lineOffset;
static UInt32 lineStartTime;
static UInt32 intStartTime;
static UInt32 leftBorderTime;
static int    firstLine;
static int    lastLine;
static int    intLine;
static int    firstLineOffset;
static int    leftBorder;
static UInt32 hRefresh;
static int    updateScreenMode;

static int    screenOn;
static int    VAdjust;
static int    HAdjust;

static int lineTime;
static int phase;
static int screenMode;
static UInt8  VDP[64];
static UInt8  VDPStatus[16];

static int    palKey;
static int    vdpKey;
static UInt8  vdpData;
static UInt8  vdpDataLatch;
static UInt16 vramAddress;

static int spritesEnable = 1;
static int displayEnable = 1;

static UInt8  VRAM[VRAM_SIZE];

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


static void vdpUpdateScreenMode(void)
{
    switch (((VDP[0] & 0x0e) >> 1) | (VDP[1] & 0x18)) {
    case 0x10: screenMode = 0; break;
    case 0x00: screenMode = 1; break;
    case 0x01: screenMode = 2; break;
    case 0x08: screenMode = 3; break;
    case 0x02: screenMode = 4; break;
    case 0x03: screenMode = 5; break;
    case 0x04: screenMode = 6; break;
    case 0x05: screenMode = 7; break;
    case 0x07: screenMode = 8; break;
    case 0x12: screenMode = 13; break;
    }

    scr0splitLine = (scanLine - firstLine) & ~7;

    chrTabBase = (((int)VDP[2] << 10) | ~(-1 << 10)) & vramMask;
    chrGenBase = (((int)VDP[4] << 11) | ~(-1 << 11)) & vramMask;
    colTabBase = (((int)VDP[10] << 14) | ((int)VDP[3] << 6) | ~(-1 << 6)) & vramMask;

    sprTabBase = (((int)VDP[11] << 15) | ((int)VDP[5] << 7) | ~(-1 << 7)) & vramMask;
    sprGenBase = (((int)VDP[6] << 11) | ~(-1 << 11)) & vramMask;

    screenOn = VDP[1] & 0x40;
    
    vdpSetScreenMode(screenMode, VDP[25] & 0x40);

    switch (screenMode) {
    case 0: RefreshLine = RefreshLine0; break;
    case 1: RefreshLine = RefreshLine1; break;
    case 2: RefreshLine = RefreshLine2; break;
    case 3: RefreshLine = RefreshLine3; break;
    case 4: RefreshLine = RefreshLine4; break;
    case 5: RefreshLine = RefreshLine5; break;
    case 6: RefreshLine = RefreshLine6; break;
    case 7: 
        if(!vdpIsModeYJK(VDP)) {
            RefreshLine = RefreshLine7; 
            break;
        }
    case 8: 
        if(screenMode == 8 && !vdpIsModeYJK(VDP)) {
            RefreshLine = RefreshLine8; 
        }
        else if (vdpIsModeYAE(VDP)) {
            RefreshLine = RefreshLine10; 
            screenMode = 10;
        }
        else {
            RefreshLine = RefreshLine12; 
            screenMode = 12;
        }
        break;
    default:
        RefreshLine = RefreshLineTx80; break;
        screenMode = 13;
        break;
    }
    
    if (screenMode == 0 || screenMode == 13) {
        hRefresh = 960;
        leftBorder = 102 + 92;
    }
    else {
        hRefresh = 1024;
        leftBorder = 102 + 56;
    }
}

static void vdpUpdateRegisters(UInt8 reg, UInt8 value)
{ 
    reg   &= registerMask;
    value &= registerValueMask[reg];

    if (reg >= 0x20) {   
        vdpCmdWrite(reg - 0x20, value, boardSystemTime());
        return;
    }

    switch (reg) {
    case 0: 
        if (!(value & 0x10)) {
            boardClearInt(INT_IE1);
        }

        updateScreenMode |= (VDP[0] ^ value) & 0x0e;
        
        break;

    case 1: 
        if (VDPStatus[0] & 0x80) {
			if (value & 0x20) {
				boardSetInt(INT_IE0);
			}
			else {
				boardClearInt(INT_IE0);
			}
        }

        updateScreenMode |= (VDP[1] ^ value) & 0x58;
        
        vdpSetTimingMode(((value >> 6) & drawArea) | (VDP[8] & 2));
        break;

    case 2: 
        chrTabBase = (((int)value << 10) | ~(-1 << 10)) & vramMask;
        break;

    case 3: 
        colTabBase = (((int)VDP[10] << 14) | ((int)value << 6) | ~(-1 << 6)) & vramMask;
        break;

    case 4: 
        chrGenBase = (((int)value << 11) | ~(-1 << 11)) & vramMask;
        break;

    case 5: 
        sprTabBase = ((VDP[11] << 15) | (value << 7) | ~(-1 << 7)) & ((VRAMPages << 14) - 1);
        break;

    case 6: 
    	sprGenBase = ((value << 11) | ~(-1 << 11)) & ((VRAMPages << 14) - 1);
        break;

    case 7: 
        FGColor = value >> 4;
        BGColor = value & 0x0F;
        emuPalette[0] = (!BGColor || (VDP[8] & 0x20)) ? emuPalette0 : emuPalette[BGColor];
        break;

    case 8:
        vdpSetTimingMode(((VDP[1] >> 6) & drawArea) | (value & 2));
        emuPalette[0] = (!BGColor || (value & 0x20)) ? emuPalette0 : emuPalette[BGColor];
        break;

    case 9:
        value = (value & palMask) | palValue;
        scanLines = (value & 0x80) ? 212 : 192;
        break;

    case 10: 
        colTabBase = (((int)value << 14) | ((int)VDP[3] << 6) | ~(-1 << 6)) & vramMask;
        break;

    case 11: 
        sprTabBase = ((value << 15) | (VDP[5] << 7) | ~(-1 << 7)) & ((VRAMPages << 14) - 1);
        break;

    case 14: 
        value &= VRAMPages - 1;
        vramPage = (int)value << 14;
        break;

    case 16: 
        palKey = 0;
        break;

    case 19:
        boardClearInt(INT_IE1);
        intLine = (firstLine + ((value - VDP[23]) & 0xff)) % lastLine;
        break;

    case 23:
        intLine = (firstLine + ((VDP[19] - value) & 0xff)) % lastLine;
        if (!(VDP[0] & 0x10)) {
            boardClearInt(INT_IE1);
        }
        break;

    case 25: 
        updateScreenMode = 1;
        break;

    default:
        break;
    }

    VDP[reg] = value;
} 

UInt8 vdpRead(void* dummy, UInt16 ioPort) 
{
    UInt8 value;

    vdpSync();

	value = vdpData;
	vdpData = *MAP_VRAM((VDP[14] << 14) | vramAddress);
	vramAddress = (vramAddress + 1) & 0x3fff;
    if (vramAddress == 0 && screenMode > 3) {
        VDP[14] = (VDP[14] + 1) & (VRAMPages - 1);
    }
	vdpKey = 0;

    return value;
}

UInt8 vdpReadStatus(void* dummy, UInt16 ioPort)
{
    UInt8 vdpStatus;

    vdpSync();

    if (vdpVersion == VDP_TMS9929A || vdpVersion == VDP_TMS99x8A) {
        vdpStatus = VDPStatus[0];
        VDPStatus[0] &= 0x1f;
        boardClearInt(INT_IE0);
        return vdpStatus;
    }
    
    vdpStatus = VDPStatus[VDP[15]];
    
    vdpKey = 0;

    switch(VDP[15]) {
    case 0: 
        VDPStatus[0] &= 0x1f;
        boardClearInt(INT_IE0);
        break;

    case 1: 
        if (VDP[0] & 0x10) {
            if (boardGetInt(INT_IE1)) {
                boardClearInt(INT_IE1);
                vdpStatus |=  0x01;
            }
        }
        else {
            if (boardSystemTime() - intStartTime < HPERIOD - hRefresh) {
                vdpStatus |= 0x01;
            }
        }
        break;

    case 2:
        vdpStatus |= 0x20 | vdpGetStatus();
        if (boardSystemTime() - (lineStartTime + leftBorderTime) < (UInt32)hRefresh + 57 + 26) {
            vdpStatus &= ~0x20;
        }
        break;

    case 7: 
        vdpStatus = vdpGetColor();
        break;

    case 8: 
        vdpStatus = (UInt8)vdpGetBorderX();
        break;

    case 9: 
        vdpStatus = (UInt8)(vdpGetBorderX() >> 8);
        break;
    }

    return vdpStatus;
}

void vdpWrite(void* dummy, UInt16 ioPort, UInt8 value)
{
    vdpSync();

    *MAP_VRAM(((VDP[14] << 14) | vramAddress) & vramMask) = value;
	vdpData = value;
	vdpKey = 0;
    vramAddress = (vramAddress + 1) & 0x3fff;
    if (vramAddress == 0 && screenMode > 3) {
        VDP[14] = (VDP[14] + 1 )& (VRAMPages - 1);
    }

    return;
}

void vdpWriteLatch(void* dummy, UInt16 ioPort, UInt8 value)
{
    vdpSync();

    if (vdpKey) {
		if (value & 0x80) {
			if (!(value & 0x40)) {
                vdpUpdateRegisters(value, vdpDataLatch);
			}
		} 
        else {
			vramAddress = ((UInt16)value << 8 | vdpDataLatch) & 0x3fff;
			if (!(value & 0x40)) {
				vdpRead(dummy, ioPort);
			}
		}
		vdpKey = 0;
	} else {
		vdpDataLatch = value;
		vdpKey = 1;
	}
}

void vdpWritePaletteLatch(void* dummy, UInt16 ioPort, UInt8 value)
{
    vdpSync();

    if (palKey) {
		int palEntry = VDP[16];
        palette[palEntry] = (((UInt32)(vdpDataLatch & 0x70) * 255 / 112) << 16) |
                            (((UInt32)(value & 0x07) * 255 / 7) << 8) |
                            ((UInt32)(vdpDataLatch & 0x07) * 255 / 7);
        SetColor(palEntry, palette[palEntry]);
        emuPalette[0] = (!BGColor || (VDP[8] & 0x20)) ? emuPalette0 : emuPalette[BGColor];

        VDP[16] = (palEntry + 1) & 0x0f;
		palKey = 0;
	} 
    else {
		vdpDataLatch = value;
		palKey = 1;
	}
}

void vdpWriteRegister(void* dummy, UInt16 ioPort, UInt8 value)
{
    int reg;

    vdpSync();

	vdpDataLatch = value;
    reg = VDP[17];
    if((reg & 0x3f) != 17) {
        vdpUpdateRegisters(reg, value);
    }
    if(~reg & 0x80) {
        VDP[17] = (reg + 1) & 0x3f;
    }

    return;
}

static void vdpBlink()
{
    if(blinkCnt) {
        blinkCnt--;
    }
    else {
        blinkFlag = !blinkFlag;
        if (!VDP[13]) { 
            XFGColor = FGColor;
            XBGColor = BGColor; 
        }
        else {
            blinkCnt = (blinkFlag ? VDP[13] & 0x0f : VDP[13] >> 4) * 10;
            if(blinkCnt) {
                if (blinkFlag) { 
                    XFGColor = FGColor;
                    XBGColor = BGColor; 
                }
                else { 
                    XFGColor = VDP[12] >> 4; 
                    XBGColor = VDP[12] & 0x0f; 
                }
            }
        }
    }
}

int vdpRefreshLine(UInt32 systemTime) 
{
    vdpSync();

    if (phase == 0) {
        scanLine++;
        if (scanLine >= lastLine) {
            int isPal = vdpIsVideoPal(VDP); 
            scr0splitLine = 0;
            scanLine = 0;

            firstLineOffset = isPal ? 27 : 0;
            lastLine = isPal ? 313 : 262;
            firstLine = firstLineOffset + (vdpIsScanLines212(VDP) ? 14 : 24) + VAdjust;
            intLine = firstLine + ((VDP[19] - VDP[23]) & 0xff);
            if (!(VDP[0] & 0x10)) {
                boardClearInt(INT_IE1);
            }
            drawAreaStart = (drawArea ? 3 + 13 : firstLine) - 1;
            VDPStatus[2] ^= 0x02;
            RefreshScreen(screenMode, (~VDPStatus[2] & 0x02) >> 1, vdpIsInterlaceOn(VDP) && ((VDP[9]  & 0x04) && VRAM128));


            vdpBlink();
        }
        
        if (updateScreenMode) {
            vdpUpdateScreenMode();
            updateScreenMode = 0;
        }

        VAdjust = (-((Int8)(VDP[18]) >> 4));
        HAdjust = (-((Int8)(VDP[18] << 4) >> 4));
        leftBorderTime = leftBorder + HPERIOD * HAdjust / 256;
        lineStartTime = systemTime;
        lineTime = leftBorderTime - 10;
    }
    else if (phase == 1) {
        lineTime = hRefresh + 10;
        lineOffset = 0;

        if (scanLine == firstLine - 1) {
            VDPStatus[2] &= ~0x40;
        }

        if (scanLine == firstLine + scanLines) {
            VDPStatus[0] |= 0x80;
            VDPStatus[2] |= 0x40;
            if (VDP[1] & 0x20) {
                boardSetInt(INT_IE0);
            }
            drawArea = 0;
            vdpSetTimingMode(VDP[8] & 2);
        }
    }
    else {
        if (scanLine == intLine) {
            intStartTime = systemTime;
            if (VDP[0] & 0x10) {
                boardSetInt(INT_IE1);
            }
        }

        if (scanLine == drawAreaStart) {
            drawArea = 1;
            vdpSetTimingMode(((VDP[1] >> 6) & drawArea) | (VDP[8] & 2));
        }
        
        lineTime = HPERIOD - hRefresh - leftBorderTime;
    }
    
    phase = (phase + 1) % 3;

    return lineTime;
}

int vdpGetRefreshRate() {
    return vdpIsVideoPal(VDP) ? 50 : 60;
}

static void vdpSync(void) {
    UInt32 systemTime = boardSystemTime();
    int curLine;
    int curLineOffset;

    if (vdpVersion == VDP_V9938 || vdpVersion == VDP_V9958) {
        vdpCmdExecute(systemTime);
    }

    curLine = scanLine - firstLineOffset;
    if (curLine & ~0xff) {
        return;
    }

    curLineOffset = systemTime - (lineStartTime + leftBorderTime) - 24;
    if (curLineOffset < 0) {
        return;
    }

    curLineOffset /= 32;

    if (curLineOffset > 33) curLineOffset = 33;

    while (lineOffset < curLineOffset) RefreshLine(curLine, lineOffset++);
}

void vdpSaveState()
{
    SaveState* state = saveStateOpenForWrite("vdp");
    char tag[32];
    int index;

    saveStateSet(state, "palKey",          palKey);
    saveStateSet(state, "vdpKey",          vdpKey);
    saveStateSet(state, "vramAddress",     vramAddress);
    saveStateSet(state, "vdpData",         vdpData);
    saveStateSet(state, "vdpDataLatch",    vdpDataLatch);
    saveStateSet(state, "drawAreaStart",   drawAreaStart);
    saveStateSet(state, "xfgColor",        XFGColor);
    saveStateSet(state, "xbgColor",        XBGColor);
    saveStateSet(state, "scanLine",        scanLine);
    saveStateSet(state, "lineTime",        lineTime);
    saveStateSet(state, "phase",           phase);
    saveStateSet(state, "lineStartTime",   lineStartTime);
    saveStateSet(state, "leftBorderTime",  leftBorderTime);
    saveStateSet(state, "intStartTime",    intStartTime);
    saveStateSet(state, "scanLines",       scanLines);
    saveStateSet(state, "firstLine",       firstLine);
    saveStateSet(state, "blinkFlag",       blinkFlag);
    saveStateSet(state, "blinkCnt",        blinkCnt);
    saveStateSet(state, "drawArea",        drawArea);
    saveStateSet(state, "lineOffset",      lineOffset);
    saveStateSet(state, "vramPages",       VRAMPages);
    saveStateSet(state, "vdpConnector",    vdpConnector);
    saveStateSet(state, "vdpVersion",      vdpVersion);
    saveStateGet(state, "leftBorder",      leftBorder);
    saveStateGet(state, "updateScrMode",   updateScreenMode);
    saveStateGet(state, "hRefresh",        hRefresh);

    saveStateSetBuffer(state, "regs", VDP, sizeof(VDP));
    saveStateSetBuffer(state, "status", VDPStatus, sizeof(VDPStatus));

    for (index = 0; index < sizeof(palette) / sizeof(palette[0]); index++) {
        sprintf(tag, "palette%d", index);
        saveStateSet(state, tag, palette[index]);
    }
    
    saveStateSetBuffer(state, "vram", VRAM, 0x4000 * VRAMPages);

    saveStateClose(state);

    vdpCmdSaveState();
}

void vdpLoadState()
{
    SaveState* state = saveStateOpenForRead("vdp");
    char tag[32];
    int index;

    palKey         =         saveStateGet(state, "palKey",          0);
    vdpKey         =         saveStateGet(state, "vdpKey",          0);
    vramAddress    = (UInt16)saveStateGet(state, "vramAddress",     0);
    vdpData        = (UInt8) saveStateGet(state, "vdpData",         0);
    vdpDataLatch   = (UInt8) saveStateGet(state, "vdpDataLatch",    0);
    drawAreaStart  =         saveStateGet(state, "drawAreaStart",   0);
    XFGColor       = (UInt8) saveStateGet(state, "xfgColor",        0);
    XBGColor       = (UInt8) saveStateGet(state, "xbgColor",        0);
    scanLine       =         saveStateGet(state, "scanLine",        10000);
    lineTime       =         saveStateGet(state, "lineTime",        0);
    phase          =         saveStateGet(state, "phase",           0);
    lineStartTime  =         saveStateGet(state, "lineStartTime",   0);
    leftBorderTime =         saveStateGet(state, "leftBorderTime",  0);
    intStartTime   =         saveStateGet(state, "intStartTime",    0);
    scanLines      =         saveStateGet(state, "scanLines",       0);
    firstLine      =         saveStateGet(state, "firstLine",       1);
    blinkFlag      =         saveStateGet(state, "blinkFlag",       0);
    blinkCnt       =         saveStateGet(state, "blinkCnt",        0);
    drawArea       =         saveStateGet(state, "drawArea",        0);
    lineOffset     =         saveStateGet(state, "lineOffset",      256);
    VRAMPages      =         saveStateGet(state, "vramPages",       8);
    vdpConnector   =         saveStateGet(state, "vdpConnector",    VDP_MSX);
    vdpVersion     =         saveStateGet(state, "vdpVersion",      0);
    leftBorder     =         saveStateGet(state, "leftBorder",      200);
    updateScreenMode=         saveStateGet(state, "updateScrMode",  0);
    hRefresh       =         saveStateGet(state, "hRefresh",        1024);

    saveStateGetBuffer(state, "regs", VDP, sizeof(VDP));
    saveStateGetBuffer(state, "status", VDPStatus, sizeof(VDPStatus));

    for (index = 0; index < sizeof(palette) / sizeof(palette[0]); index++) {
        sprintf(tag, "palette%d", index);
        palette[index] = saveStateGet(state, tag, 0);
    }

    saveStateGetBuffer(state, "vram", VRAM, 0x4000 * VRAMPages);

    saveStateClose(state);

    vramMask        = (VRAMPages << 14) - 1;
    VRAM128         = VRAMPages >= 8 ? 0x10000 : 0;
    vramPage        = ((int)VDP[14] << 14) & (VRAMPages - 1);
    firstLineOffset = vdpIsVideoPal(VDP) ? 27 : 0;
    lastLine        = vdpIsVideoPal(VDP) ? 313 : 262;    
    FGColor         = VDP[7] >> 4;
    BGColor         = VDP[7] & 0x0F;

    switch (vdpVersion) {
    case VDP_TMS9929A:
    case VDP_TMS99x8A:
        registerValueMask = registerValueMaskMSX1;
        registerMask      = 0x07;
        break;
    case VDP_V9938:
        registerValueMask = registerValueMaskMSX2;
        registerMask      = 0x3f;
        break;
    case VDP_V9958:
        registerValueMask = registerValueMaskMSX2p;
        registerMask      = 0x3f;
        break;
    }

    vdpCmdLoadState();


    /* Set palette */
    for (index = 0; index < 16; index++) {
        SetColor(index, palette[index]);
    }
    emuPalette[0] = (!BGColor || (VDP[8] & 0x20)) ? emuPalette0 : emuPalette[BGColor];

    vdpUpdateScreenMode();

    intLine = firstLine + ((VDP[19] - VDP[23]) & 0xff);
}

void vdpReset()
{
    int i;

    scr0splitLine   = 0;
    vramPage        = 0;
    sprGenBase      = 0;
    sprTabBase      = 0;
    colTabBase      = 0;
    chrTabBase      = 0;
    chrGenBase      = 0;
    palKey          = 0;
    vdpKey          = 0;
	vramAddress     = 0;
	vdpData         = 0;
	vdpDataLatch    = 0;
    FGColor         = 0;
    BGColor         = 0;
    XFGColor        = 0;
    XBGColor        = 0;
    drawAreaStart   = 0;
    blinkFlag       = 0;
    blinkCnt        = 0;
    drawArea        = 0;
    lineStartTime   = 0;
    intStartTime    = 0;
    lastLine        = 0;
    firstLineOffset = 0;
    screenOn        = 0;
    VAdjust         = 0;
    HAdjust         = 0;
    lineTime        = 0;
    hRefresh        = 0;
    phase           = 0;
    updateScreenMode= 0;

    leftBorder      = 200;
    screenMode      = 1;
    lineOffset      = 256;
    firstLine       = 1;
    lastLine        = -1;
    scanLine        = 10000;
    scanLines       = 192;
    
    memset(palette, 0, sizeof(palette));
    memset(VRAM, 0, VRAM_SIZE);
    memset(VDPStatus, 0, sizeof(VDPStatus));
    memset(VDP, 0, sizeof(VDP));

    vdpCmdInit(VRAMPages << 14, VRAM, boardSystemTime());

    VDPStatus[0] = 0x9f;
    VDPStatus[1] = vdpVersion == VDP_V9958 ? 0x04 : 0;
    VDPStatus[2] = 0x6c;
        
    VDP[1] = 0x10;
    VDP[2] = 0xff;
    VDP[3] = 0xff;
    VDP[4] = 0xff;
    VDP[5] = 0xff;
    VDP[9] = (0x02 & palMask) | palValue;

    if (vdpVersion == VDP_TMS9929A || vdpVersion == VDP_TMS99x8A) {
        memcpy(palette, msx1Palette, sizeof(palette));
    }
    else {
        memcpy(palette, defaultPalette, sizeof(palette));
    }

    for (i = 0; i < 16; i++) {
        SetColor(i, palette[i]);
    }
    emuPalette[0] = (!BGColor || (VDP[8] & 0x20)) ? emuPalette0 : emuPalette[BGColor];

    vdpUpdateScreenMode();
}

void vdpInit(VdpConnector connector, VdpVersion version, VdpSyncMode sync, int vramPages)
{
    int i;

    VRAMPages     = vramPages;
    VRAM128       = vramPages >= 8 ? 0x10000 : 0;
    vramMask      = (vramPages << 14) - 1;
    vdpVersion    = version;
    vdpConnector  = connector;

    if (sync == VDP_SYNC_AUTO) {
        palMask  = ~0;
        palValue = 0;
    }
    else if (sync == VDP_SYNC_50HZ) {
        palMask  = ~0x02;
        palValue = 0x02;
    }
    else if (sync == VDP_SYNC_60HZ) {
        palMask  = ~0x02;
        palValue = 0x00;
    }

    vdpReset();

    switch (vdpVersion) {
    case VDP_TMS9929A:
        registerValueMask = registerValueMaskMSX1;
        registerMask      = 0x07;
        break;
    case VDP_TMS99x8A:
        registerValueMask = registerValueMaskMSX1;
        registerMask      = 0x07;
        VDP[9]          &= ~0x02;
        break;
    case VDP_V9938:
        registerValueMask = registerValueMaskMSX2;
        registerMask      = 0x3f;
        break;
    case VDP_V9958:
        registerValueMask = registerValueMaskMSX2p;
        registerMask      = 0x3f;
        break;
    }
    
    switch (vdpConnector) {
    case VDP_MSX:
        ioPortRegister(0x98, vdpRead,       vdpWrite,      NULL);
        ioPortRegister(0x99, vdpReadStatus, vdpWriteLatch, NULL);
        if (vdpVersion == VDP_V9938 || vdpVersion == VDP_V9958) {
            ioPortRegister(0x9a, NULL, vdpWritePaletteLatch, NULL);
            ioPortRegister(0x9b, NULL, vdpWriteRegister,     NULL);
        }
        break;

    case VDP_SVI:
        ioPortRegister(0x80, NULL,          vdpWrite,      NULL); // VDP VRAM Write
        ioPortRegister(0x81, NULL,          vdpWriteLatch, NULL); // VDP Address Latch
        ioPortRegister(0x84, vdpRead,       NULL,          NULL); // VDP VRAM Read
        ioPortRegister(0x85, vdpReadStatus, NULL,          NULL); // VDP Status Read
        break;

    case VDP_COLECO:
        for (i = 0xa0; i < 0xc0; i += 2) {
            ioPortRegister(i,     vdpRead,       vdpWrite,      NULL);
            ioPortRegister(i + 1, vdpReadStatus, vdpWriteLatch, NULL);
        }
        break;
    }
}

void vdpDestroy() 
{
    int i;

    switch (vdpConnector) {
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
}


#include "common.h"
