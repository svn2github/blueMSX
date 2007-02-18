/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoChips/Common.h,v $
**
** $Revision: 1.34 $
**
** $Date: 2007-02-18 23:59:15 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2006 Daniel Vik
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
******************************************************************************
*/
#include "SpriteLine.h"

#define BORDER_WIDTH   8
#define DISPLAY_WIDTH  256
#define SCREEN_WIDTH   (2 * BORDER_WIDTH + DISPLAY_WIDTH)
#define SCREEN_HEIGHT  240



#define UPDATE_TABLE_5() if ((++scroll & 0x7f) == 0) charTable += jump[page ^= 1];
#define UPDATE_TABLE_6() if ((++scroll & 0xff) == 0) charTable += jump[page ^= 1];
#define UPDATE_TABLE_7() if ((++scroll & 0xff) == 0) charTable += jump[page ^= 1];
#define UPDATE_TABLE_8() if ((++scroll & 0xff) == 0) charTable += jump[page ^= 1];
#define UPDATE_TABLE_10() if ((++scroll & 0xff) == 0) charTable += jump[page ^= 1];
#define UPDATE_TABLE_12() if ((++scroll & 0xff) == 0) charTable += jump[page ^= 1];


static int jumpTable[] = { -128, -128, -0x8080, 0x7f80 };

static UInt16* linePtr0 = NULL;
static UInt16* linePtr0p = NULL;
static UInt16* linePtr0w = NULL;
static UInt16* linePtr1 = NULL;
static UInt16* linePtr2 = NULL;
static UInt16* linePtr3 = NULL;
static UInt16* linePtr4 = NULL;
static UInt16* linePtr5 = NULL;
static UInt16* linePtr6 = NULL;
static UInt16* linePtr7 = NULL;
static UInt16* linePtr8 = NULL;
static UInt16* linePtr10 = NULL;
static UInt16* linePtr12 = NULL;

void RefreshLineReset()
{
    linePtr0 = NULL;
    linePtr0p = NULL;
    linePtr0w = NULL;
    linePtr1 = NULL;
    linePtr2 = NULL;
    linePtr3 = NULL;
    linePtr4 = NULL;
    linePtr5 = NULL;
    linePtr6 = NULL;
    linePtr7 = NULL;
    linePtr8 = NULL;
    linePtr10 = NULL;
    linePtr12 = NULL;
}

UInt16 *RefreshBorder(VDP* vdp, int Y, UInt16 bgColor, int line512, int borderExtra)
{
    FrameBuffer* frameBuffer = frameBufferGetDrawFrame();
    int lineSize = line512 ? 2 : 1;
    UInt16 *linePtr;
    int offset;

    if (frameBuffer == NULL) {
        return NULL;
    }

    Y -= vdp->displayOffest;

    frameBufferSetScanline(Y);

    linePtr = frameBuffer->line[Y].buffer;

    if (frameBuffer->line[Y].doubleWidth != line512 && line512 == 0) {
        for(offset = 256 + 16; offset < 512 + 16; offset++) {
            linePtr[offset] = 0;
        }
    }

    frameBuffer->line[Y].doubleWidth = line512;

    for (offset = lineSize * (BORDER_WIDTH + vdp->HAdjust + borderExtra) - 1; offset >= 0; offset--) {
        *linePtr++ = bgColor;
    }

    return linePtr;
}


UInt16 *RefreshBorder6(VDP* vdp, int Y, UInt16 bgColor1, UInt16 bgColor2, int line512, int borderExtra)
{
    FrameBuffer* frameBuffer = frameBufferGetDrawFrame();
    int lineSize = line512 ? 2 : 1;
    UInt16 *linePtr;
    int offset;

    if (frameBuffer == NULL) {
        return NULL;
    }

    Y -= vdp->displayOffest;

    frameBufferSetScanline(Y);

    linePtr = frameBuffer->line[Y].buffer;

    if (frameBuffer->line[Y].doubleWidth != line512 && line512 == 0) {
        for(offset = 256 + 16; offset < 512 + 16; offset++) {
            linePtr[offset] = 0;
        }
    }

    frameBuffer->line[Y].doubleWidth = line512;

    for (offset = lineSize * (BORDER_WIDTH + vdp->HAdjust + borderExtra) - 1; offset >= 0; offset -= 2) {
        *linePtr++ = bgColor1;
        *linePtr++ = bgColor2;
    }

    return linePtr;
}

static void RefreshRightBorder(VDP* vdp, int Y, UInt16 bgColor, int line512, int borderExtra) {
    FrameBuffer* frameBuffer = frameBufferGetDrawFrame();
    int lineSize = line512 ? 2 : 1;
    UInt16 *linePtr;
    int offset;

    if (frameBuffer == NULL) {
        return;
    }

    Y -= vdp->displayOffest;

    if (!displayEnable) {
        return;
    }
    
    linePtr = frameBuffer->line[Y].buffer;

    for(offset = lineSize * (BORDER_WIDTH - vdp->HAdjust + borderExtra + 1) - 1; offset > 0; offset--) {
        linePtr[lineSize * SCREEN_WIDTH - offset] = bgColor;
    }
}

static void RefreshRightBorder6(VDP* vdp, int Y, UInt16 bgColor1, UInt16 bgColor2, int line512, int borderExtra) {
    FrameBuffer* frameBuffer = frameBufferGetDrawFrame();
    int lineSize = line512 ? 2 : 1;
    UInt16 *linePtr;
    int offset;

    if (frameBuffer == NULL) {
        return;
    }

    Y -= vdp->displayOffest;

    if (!displayEnable) {
        return;
    }
    
    linePtr = frameBuffer->line[Y].buffer;

    for(offset = lineSize * (BORDER_WIDTH - vdp->HAdjust + borderExtra + 1) - 1; offset > 0; offset-= 2) {
        linePtr[lineSize * SCREEN_WIDTH - offset - 1] = bgColor1;
        linePtr[lineSize * SCREEN_WIDTH - offset] = bgColor2;
    }
}

#if 1
static void RefreshLine0(VDP* vdp, int Y, int X, int X2)
{
    static int     border;
    static UInt8*  sprLine;
    static int     patternBase;
    static int     pattern;
    static int     x;
    static int     y;
    static int     shift;
    int    rightBorder;

    if (X == -1) {
        X++;
        linePtr0 = RefreshBorder(vdp, Y, vdp->palette[vdp->BGColor], 0, 1);
        border = !vdp->screenOn || !vdp->drawArea;

        if (!border) {
            y = Y - vdp->firstLine + vdpVScroll(vdp) - vdp->scr0splitLine;
            x = 0;
            patternBase = vdp->chrGenBase & ((-1 << 11) | (y & 7));
            shift = 0;
        }
    }

    if (linePtr0 == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    if (border) {
        UInt16 bgColor = vdp->palette[vdp->BGColor];
        while (X < X2) {
            linePtr0[0] = bgColor;
            linePtr0[1] = bgColor;
            linePtr0[2] = bgColor;
            linePtr0[3] = bgColor;
            linePtr0[4] = bgColor;
            linePtr0[5] = bgColor;
            linePtr0[6] = bgColor;
            linePtr0[7] = bgColor;
            linePtr0 += 8; 
            X++;
        }
    }
    else {
        UInt16 color[2] = { vdp->palette[vdp->BGColor], vdp->palette[vdp->FGColor] };

        while (X < X2) {
            if (X == 0 || X == 31) {
                linePtr0[0] = color[0];
                linePtr0[1] = color[0];
                linePtr0[2] = color[0];
                linePtr0[3] = color[0];
                linePtr0[4] = color[0];
                linePtr0[5] = color[0];
                linePtr0[6] = color[0];
                linePtr0[7] = color[0];
                linePtr0 += 8; 
                X++;
            }
            else {
                int j;
                for (j = 0; j < 4; j++) {
                    if (shift <= 2) { 
                        int charIdx = 0xc00 + 40 * (y / 8) + x++;
                        UInt8* charTable = vdp->vram + (vdp->chrTabBase & ((-1 << 12) | charIdx));
                        pattern = vdp->vram[patternBase | ((int)*charTable * 8)];
                        shift = 8; 
                    }

                    linePtr0[0] = color[(pattern >> --shift) & 1];
                    linePtr0[1] = color[(pattern >> --shift) & 1];
                    linePtr0 += 2; 
                }
                X++;
            }
        }
    }
    if (rightBorder) {
        RefreshRightBorder(vdp, Y, vdp->palette[vdp->BGColor], 0, 0);
    }
}


static void RefreshLine0Plus(VDP* vdp, int Y, int X, int X2)
{
    static int     border;
    static UInt8*  sprLine;
    static int     patternBase;
    static int     pattern;
    static int     x;
    static int     y;
    static int     shift;
    int    rightBorder;

    if (X == -1) {
        X++;
        linePtr0p = RefreshBorder(vdp, Y, vdp->palette[vdp->BGColor], 0, 1);
        border = !vdp->screenOn || !vdp->drawArea;

        if (!border) {
            y = Y - vdp->firstLine + vdpVScroll(vdp) - vdp->scr0splitLine;
            x = 0;
            patternBase =  (-1 << 13) | ((y & 0xc0) << 5) | (y & 7);
            shift = 0;
        }
    }

    if (linePtr0p == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    if (border) {
        UInt16 bgColor = vdp->palette[vdp->BGColor];
        while (X < X2) {
            linePtr0p[0] = bgColor;
            linePtr0p[1] = bgColor;
            linePtr0p[2] = bgColor;
            linePtr0p[3] = bgColor;
            linePtr0p[4] = bgColor;
            linePtr0p[5] = bgColor;
            linePtr0p[6] = bgColor;
            linePtr0p[7] = bgColor;
            linePtr0p += 8; 
            X++;
        }
    }
    else {
        UInt16 color[2] = { vdp->palette[vdp->BGColor], vdp->palette[vdp->FGColor] };

        while (X < X2) {
            if (X == 0 || X == 31) {
                linePtr0p[0] = color[0];
                linePtr0p[1] = color[0];
                linePtr0p[2] = color[0];
                linePtr0p[3] = color[0];
                linePtr0p[4] = color[0];
                linePtr0p[5] = color[0];
                linePtr0p[6] = color[0];
                linePtr0p[7] = color[0];
                linePtr0p += 8; 
                X++;
            }
            else {
                int j;
                for (j = 0; j < 4; j++) {
                    if (shift <= 2) { 
                        int charIdx = 0xc00 + 40 * (y / 8) + x++;
                        UInt8* charTable = vdp->vram + (vdp->chrTabBase & ((-1 << 12) | charIdx));
                        pattern = vdp->vram[vdp->chrGenBase & (patternBase | ((int)*charTable * 8))];
                        shift = 8; 
                    }

                    linePtr0p[0] = color[(pattern >> --shift) & 1];
                    linePtr0p[1] = color[(pattern >> --shift) & 1];
                    linePtr0p += 2; 
                }
                X++;
            }
        }
    }
    if (rightBorder) {
        RefreshRightBorder(vdp, Y, vdp->palette[vdp->BGColor], 0, 0);
    }
}

static void RefreshLineTx80(VDP* vdp, int Y, int X, int X2)
{
    static int     border;
    static UInt8*  sprLine;
    static int     patternBase;
    static UInt8   colPattern;
    static int     pattern;
    static UInt16* col;
    static int     x;
    static int     y;
    static int     shift;
    int    rightBorder;

    if (X == -1) {
        X++;
        linePtr0p = RefreshBorder(vdp, Y, vdp->palette[vdp->BGColor], 1, 1);
        border = !vdp->screenOn || !vdp->drawArea;

        if (!border) {
            y = Y - vdp->firstLine + vdpVScroll(vdp) - vdp->scr0splitLine;
            x = 0;
            patternBase = vdp->chrGenBase & ((-1 << 11) | (y & 7));
            shift = 0;
        }
    }

    if (linePtr0p == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    if (border) {
        UInt16 bgColor = vdp->palette[vdp->BGColor];
        while (X < X2) {
            int j;
            for (j = 0; j < 2; j++) {
                linePtr0p[0] = bgColor;
                linePtr0p[1] = bgColor;
                linePtr0p[2] = bgColor;
                linePtr0p[3] = bgColor;
                linePtr0p[4] = bgColor;
                linePtr0p[5] = bgColor;
                linePtr0p[6] = bgColor;
                linePtr0p[7] = bgColor;
                linePtr0p += 8; 
            }
            X++;
        }
    }
    else {
        UInt16 color[4] = { 
            vdp->palette[vdp->BGColor],  vdp->palette[vdp->FGColor],
            vdp->palette[vdp->XBGColor], vdp->palette[vdp->XFGColor]
        };

        while (X < X2) {
            if (X == 0 || X == 31) {
                int j;
                for (j = 0; j < 2; j++) {
                    linePtr0p[0] = color[0];
                    linePtr0p[1] = color[0];
                    linePtr0p[2] = color[0];
                    linePtr0p[3] = color[0];
                    linePtr0p[4] = color[0];
                    linePtr0p[5] = color[0];
                    linePtr0p[6] = color[0];
                    linePtr0p[7] = color[0];
                    linePtr0p += 8; 
                }
                X++;
            }
            else {
                int j;
                for (j = 0; j < 8; j++) {
                    if (shift <= 2) { 
                        int charIdx = 80 * (y / 8) + x;
                        UInt8*  charTable   = vdp->vram + (vdp->chrTabBase & ((-1 << 12) | charIdx));
                        pattern = vdp->vram[patternBase | ((int)*charTable * 8)];
                        shift = 8; 

                        if ((x & 0x07) == 0) {
                            UInt8*  colTable = vdp->vram + (vdp->colTabBase & ((-1 << 9) | (charIdx / 8)));
                            colPattern = *colTable++;
                        }
                        col = color + ((colPattern >> 6) & 2);
                        colPattern <<= 1;

                        x++;
                    }

                    linePtr0p[0] = col[(pattern >> --shift) & 1];
                    linePtr0p[1] = col[(pattern >> --shift) & 1];
                    linePtr0p += 2; 
                }
                X++;
            }
        }
    }
    if (rightBorder) {
        RefreshRightBorder(vdp, Y, vdp->palette[vdp->BGColor], 1, 0);
    }
}

#else
static void RefreshLine0(VDP* vdp, int Y, int X, int X2)
{
    int     patternBase;
    UInt16  color[2];

    if (X2 >= 32) {
        RefreshRightBorder(vdp, Y, vdp->palette[vdp->BGColor], 0, 7);
    }

    if (X > 6 || X2 <= 6) {
        return;
    }

    linePtr0 = RefreshBorder(vdp, Y, vdp->palette[vdp->BGColor], 0, 9);

    if (linePtr0 == NULL) {
        return;
    }

    if (!vdp->screenOn || !vdp->drawArea) {
        UInt16 bgColor = vdp->palette[vdp->BGColor];
        for (X = 0; X < 40; X++) {
            linePtr0[0] = bgColor;
            linePtr0[1] = bgColor;
            linePtr0[2] = bgColor;
            linePtr0[3] = bgColor;
            linePtr0[4] = bgColor;
            linePtr0[5] = bgColor;
            linePtr0 += 6; 
        }
    }
    else {
        Y -= vdp->firstLine;
        Y = Y + vdpVScroll(vdp) - vdp->scr0splitLine;
        patternBase = vdp->chrGenBase & ((-1 << 11) | (Y & 7));
        color[0] = vdp->palette[vdp->BGColor];
        color[1] = vdp->palette[vdp->FGColor];

        for (X = 0; X < 40; X++) {
            int charIdx = 0xc00 + 40 * (Y / 8) + X;
            UInt8* charTable = vdp->vram + (vdp->chrTabBase & ((-1 << 12) | charIdx));
            int pattern = vdp->vram[patternBase | ((int)*charTable * 8)];
            linePtr0[0] = color[(pattern >> 7) & 1];
            linePtr0[1] = color[(pattern >> 6) & 1];
            linePtr0[2] = color[(pattern >> 5) & 1];
            linePtr0[3] = color[(pattern >> 4) & 1];
            linePtr0[4] = color[(pattern >> 3) & 1];
            linePtr0[5] = color[(pattern >> 2) & 1];
            charTable++;
            linePtr0 += 6;
        }
    }
}

static void RefreshLine0Plus(VDP* vdp, int Y, int X, int X2)
{
    int     patternBase;
    UInt16  color[2];

    if (X2 >= 32) {
        RefreshRightBorder(vdp, Y, vdp->palette[vdp->BGColor], 0, 7);
    }

    if (X > 6 || X2 <= 6) {
        return;
    }

    linePtr0p = RefreshBorder(vdp, Y, vdp->palette[vdp->BGColor], 0, 9);

    if (linePtr0p == NULL) {
        return;
    }

    if (!vdp->screenOn || !vdp->drawArea) {
        UInt16 bgColor = vdp->palette[vdp->BGColor];
        for (X = 0; X < 40; X++) {
            linePtr0p[0] = bgColor;
            linePtr0p[1] = bgColor;
            linePtr0p[2] = bgColor;
            linePtr0p[3] = bgColor;
            linePtr0p[4] = bgColor;
            linePtr0p[5] = bgColor;
            linePtr0p += 6; 
        }
    }
    else {
        Y -= vdp->firstLine;
        Y = Y + vdpVScroll(vdp) - vdp->scr0splitLine;
        patternBase =  (-1 << 13) | ((Y & 0xc0) << 5) | (Y & 7);
        color[0] = vdp->palette[vdp->BGColor];
        color[1] = vdp->palette[vdp->FGColor];

        for (X = 0; X < 40; X++) {
            int charIdx = 0xc00 + 40 * (Y / 8) + X;
            UInt8* charTable = vdp->vram + (vdp->chrTabBase & ((-1 << 12) | charIdx));
            int pattern = vdp->vram[vdp->chrGenBase & (patternBase | ((int)*charTable * 8))];
            linePtr0p[0] = color[(pattern >> 7) & 1];
            linePtr0p[1] = color[(pattern >> 6) & 1];
            linePtr0p[2] = color[(pattern >> 5) & 1];
            linePtr0p[3] = color[(pattern >> 4) & 1];
            linePtr0p[4] = color[(pattern >> 3) & 1];
            linePtr0p[5] = color[(pattern >> 2) & 1];
            charTable++;
            linePtr0p += 6;
        }
    }
}

static void RefreshLineTx80(VDP* vdp, int Y, int X, int X2)
{
    UInt8   colPattern;
    UInt16  colors[4];

    if (X2 >= 32) {
        RefreshRightBorder(vdp, Y, vdp->palette[vdp->BGColor], 1, 7);
    }

    if (X > 6 || X2 <= 6) {
        return;
    }

    linePtr0w = RefreshBorder(vdp, Y, vdp->palette[vdp->BGColor], 1, 9);
    
    if (linePtr0w == NULL) {
        return;
    }

    if (!vdp->screenOn || !vdp->drawArea) {
        UInt16 bgColor = vdp->palette[vdp->BGColor];
        for (X = 0; X < 80; X++) {
            linePtr0w[0] = bgColor;
            linePtr0w[1] = bgColor;
            linePtr0w[2] = bgColor;
            linePtr0w[3] = bgColor;
            linePtr0w[4] = bgColor;
            linePtr0w[5] = bgColor;
            linePtr0w += 6; 
        }
    }
    else {
        int patternBase;

        Y -= vdp->firstLine;
        Y = Y + vdpVScroll(vdp) - vdp->scr0splitLine;
        
        patternBase = vdp->chrGenBase & ((-1 << 11) | (Y & 7));

        colors[0]   = vdp->palette[vdp->BGColor];
        colors[1]   = vdp->palette[vdp->FGColor];
        colors[2]   = vdp->palette[vdp->XBGColor];
        colors[3]   = vdp->palette[vdp->XFGColor];

        for(X = 0; X < 80; X++) {
            int charIdx = 80 * (Y / 8) + X;
            UInt8*  charTable   = vdp->vram + (vdp->chrTabBase & ((-1 << 12) | charIdx));
            int charPattern     = vdp->vram[patternBase | ((int)*charTable * 8)];

            UInt16* color;
            if ((X & 0x07) == 0) {
                UInt8*  colTable    = vdp->vram + (vdp->colTabBase & ((-1 << 9) | (charIdx / 8)));
                colPattern = *colTable++;
            }
            color = colors + ((colPattern >> 6) & 2);
            colPattern <<= 1;

            linePtr0w[0] = color[(charPattern >> 7) & 1];
            linePtr0w[1] = color[(charPattern >> 6) & 1];
            linePtr0w[2] = color[(charPattern >> 5) & 1];
            linePtr0w[3] = color[(charPattern >> 4) & 1];
            linePtr0w[4] = color[(charPattern >> 3) & 1];
            linePtr0w[5] = color[(charPattern >> 2) & 1];
            linePtr0w += 6;
        }
    }
}

#endif

static void RefreshLine1(VDP* vdp, int Y, int X, int X2)
{
    static int     border;
    static UInt8*  sprLine;
    static UInt8*  charTable;
    static int     patternBase;
    UInt8  charPattern;
    UInt8  colPattern;
    UInt8  col;
    UInt16 color[2];
    int    y;
    int    rightBorder;

    if (X == -1) {
        X++;
        linePtr1 = RefreshBorder(vdp, Y, vdp->palette[vdp->BGColor], 0, 0);
        border = !vdp->screenOn || !vdp->drawArea;
        sprLine = spritesLine(vdp, Y);

        if (!border) {
            y = Y - vdp->firstLine + vdpVScroll(vdp);
            charTable   = vdp->vram + (vdp->chrTabBase & ((-1 << 10) | (32 * (y / 8))));
            patternBase = vdp->chrGenBase & ((-1 << 11) | (y & 7));
        }
    }

    if (linePtr1 == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    if (border) {
        UInt16 bgColor = vdp->palette[vdp->BGColor];
        while (X < X2) {
            linePtr1[0] = bgColor;
            linePtr1[1] = bgColor;
            linePtr1[2] = bgColor;
            linePtr1[3] = bgColor;
            linePtr1[4] = bgColor;
            linePtr1[5] = bgColor;
            linePtr1[6] = bgColor;
            linePtr1[7] = bgColor;
            linePtr1 += 8; 
            X++;
        }
    }
    else {
        while (X < X2) {
            colPattern = vdp->vram[vdp->colTabBase & ((*charTable / 8) | (-1 << 6))];
            color[0] = vdp->palette[colPattern & 0x0f];
            color[1] = vdp->palette[colPattern >> 4];
            charPattern = vdp->vram[patternBase | ((int)*charTable * 8)];

            col = sprLine[0]; linePtr1[0] = col ? vdp->palette[col] : color[(charPattern >> 7) & 1]; 
            col = sprLine[1]; linePtr1[1] = col ? vdp->palette[col] : color[(charPattern >> 6) & 1];
            col = sprLine[2]; linePtr1[2] = col ? vdp->palette[col] : color[(charPattern >> 5) & 1]; 
            col = sprLine[3]; linePtr1[3] = col ? vdp->palette[col] : color[(charPattern >> 4) & 1];
            col = sprLine[4]; linePtr1[4] = col ? vdp->palette[col] : color[(charPattern >> 3) & 1]; 
            col = sprLine[5]; linePtr1[5] = col ? vdp->palette[col] : color[(charPattern >> 2) & 1];
            col = sprLine[6]; linePtr1[6] = col ? vdp->palette[col] : color[(charPattern >> 1) & 1]; 
            col = sprLine[7]; linePtr1[7] = col ? vdp->palette[col] : color[(charPattern >> 0) & 1];
            sprLine += 8;
            charTable++; 
            linePtr1 += 8; 
            X++;
        }
    }
    if (rightBorder) {
        RefreshRightBorder(vdp, Y, vdp->palette[vdp->BGColor], 0, 0);
    }
}


static void RefreshLine2(VDP* vdp, int Y, int X, int X2)
{
    static int     border;
    static UInt8*  sprLine;
    static UInt8*  charTable;
    static int     patternBase;
    static int     base;
    UInt8  charPattern;
    UInt8  colPattern;
    UInt8  col;
    UInt16 color[2];
    int    index;
    int    y;
    int    rightBorder;

    if (X == -1) {
        X++;
        linePtr2 = RefreshBorder(vdp, Y,  vdp->palette[vdp->BGColor], 0, 0);
        border = !vdp->screenOn || !vdp->drawArea;
        sprLine = spritesLine(vdp, Y);
        
        if (!border) {
            y = Y - vdp->firstLine + vdpVScroll(vdp);
            charTable   = vdp->vram + (vdp->chrTabBase & ((-1 << 10) | (32 * (y / 8))));
            base        = (-1 << 13) | ((y & 0xc0) << 5) | (y & 7);
        }
    }

    if (linePtr2 == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    if (border) {
        UInt16 bgColor = vdp->palette[vdp->BGColor];
        while (X < X2) {
            linePtr2[0] = bgColor;
            linePtr2[1] = bgColor;
            linePtr2[2] = bgColor;
            linePtr2[3] = bgColor;
            linePtr2[4] = bgColor;
            linePtr2[5] = bgColor;
            linePtr2[6] = bgColor;
            linePtr2[7] = bgColor;
            linePtr2 += 8; 
            X++;
        }
    }
    else {
        while (X < X2) {
            index      = base | ((int)*charTable * 8);
            colPattern = vdp->vram[vdp->colTabBase & index];
            color[0]   = vdp->palette[colPattern & 0x0f];
            color[1]   = vdp->palette[colPattern >> 4];
            charPattern = vdp->vram[vdp->chrGenBase & index];

            col = sprLine[0]; linePtr2[0] = col ? vdp->palette[col] : color[(charPattern >> 7) & 1]; 
            col = sprLine[1]; linePtr2[1] = col ? vdp->palette[col] : color[(charPattern >> 6) & 1];
            col = sprLine[2]; linePtr2[2] = col ? vdp->palette[col] : color[(charPattern >> 5) & 1];
            col = sprLine[3]; linePtr2[3] = col ? vdp->palette[col] : color[(charPattern >> 4) & 1];
            col = sprLine[4]; linePtr2[4] = col ? vdp->palette[col] : color[(charPattern >> 3) & 1];
            col = sprLine[5]; linePtr2[5] = col ? vdp->palette[col] : color[(charPattern >> 2) & 1];
            col = sprLine[6]; linePtr2[6] = col ? vdp->palette[col] : color[(charPattern >> 1) & 1];
            col = sprLine[7]; linePtr2[7] = col ? vdp->palette[col] : color[(charPattern >> 0) & 1];
            sprLine += 8;
            charTable++;
            linePtr2 += 8; 
            X++;
        }
    }

    if (rightBorder) {
        RefreshRightBorder(vdp, Y, vdp->palette[vdp->BGColor], 0, 0);
    }
}

static void RefreshLine3(VDP* vdp, int Y, int X, int X2)
{
    static int     border;
    static UInt8*  sprLine;
    static UInt8*  charTable;
    static int     patternBase;
    UInt8  colPattern;
    UInt16 fc;
    UInt16 bc;
    UInt8 col;
    int   y;
    int    rightBorder;

    if (X == -1) {
        X++;
        linePtr3 = RefreshBorder(vdp, Y, vdp->palette[vdp->BGColor], 0, 0);
        border = !vdp->screenOn || !vdp->drawArea;
        sprLine = spritesLine(vdp, Y);

        if (!border) {
            y = Y - vdp->firstLine + vdpVScroll(vdp);
            charTable   = vdp->vram + (vdp->chrTabBase & ((-1 << 10) | (32 * (y / 8))));
            patternBase = vdp->chrGenBase & ((-1 << 11) | ((y >> 2) & 7));
        }
    }

    if (linePtr3 == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }


    if (border) {
        UInt16 bgColor = vdp->palette[vdp->BGColor];
        while (X < X2) {
            linePtr3[0] = bgColor;
            linePtr3[1] = bgColor;
            linePtr3[2] = bgColor;
            linePtr3[3] = bgColor;
            linePtr3[4] = bgColor;
            linePtr3[5] = bgColor;
            linePtr3[6] = bgColor;
            linePtr3[7] = bgColor;
            linePtr3 += 8; 
            X++;
        }
    }
    else {
        while (X < X2) {
            colPattern = vdp->vram[patternBase | ((int)*charTable * 8)];
            fc = vdp->palette[colPattern >> 4];
            bc = vdp->palette[colPattern & 0x0f];

            col = sprLine[0]; linePtr3[0] = col ? vdp->palette[col] : fc; 
            col = sprLine[1]; linePtr3[1] = col ? vdp->palette[col] : fc;
            col = sprLine[2]; linePtr3[2] = col ? vdp->palette[col] : fc; 
            col = sprLine[3]; linePtr3[3] = col ? vdp->palette[col] : fc;
            col = sprLine[4]; linePtr3[4] = col ? vdp->palette[col] : bc; 
            col = sprLine[5]; linePtr3[5] = col ? vdp->palette[col] : bc;
            col = sprLine[6]; linePtr3[6] = col ? vdp->palette[col] : bc; 
            col = sprLine[7]; linePtr3[7] = col ? vdp->palette[col] : bc;
            sprLine += 8;
            charTable++; 
            linePtr3 += 8; 
            X++;
        }
    }
    if (rightBorder) {
        RefreshRightBorder(vdp, Y, vdp->palette[vdp->BGColor], 0, 0);
    }
}


static void RefreshLine4(VDP* vdp, int Y, int X, int X2)
{
    static int     border;
    static UInt8*  sprLine;
    static UInt8*  charTable;
    static int     base;
    static int     hScroll;
    static int     hScroll512;
    static int*    jump;
    static int     page;
    static int     scroll;
    UInt8  charPattern;
    UInt8  colPattern;
    UInt8  col;
    UInt16 color[2];
    int    index;
    int    rightBorder;

    if (X == -1) {
        int y;

        X++;
        linePtr4 = RefreshBorder(vdp, Y, vdp->palette[vdp->BGColor], 0, 0);
        border = !vdp->screenOn || !vdp->drawArea;
        sprLine = colorSpritesLine(vdp, Y, 0);

        if (linePtr4 == NULL) {
            return;
        }

        if (!border) {
            hScroll    =  ((((int)(vdp->vdpRegs[26] & 0x3F & ~(~vdpHScroll512(vdp) << 5))) << 3) - (int)(vdp->vdpRegs[27] & 0x07) & 0xffffffff);
            hScroll512 = vdpHScroll512(vdp);
            jump       = jumpTable + hScroll512 * 2;
            page       = (vdp->chrTabBase / 0x8000) & 1;
            scroll     = hScroll >> 3;

            y = Y - vdp->firstLine + vdpVScroll(vdp);
            charTable   = vdp->vram + (vdp->chrTabBase & ((-1 << 10) | (32 * (y / 8)))) + scroll;
            base        = (-1 << 13) | ((y & 0xc0) << 5) | (y & 7);

            if (vdpIsEdgeMasked(vdp->vdpRegs)) {
                UInt16 bgColor = vdp->palette[vdp->BGColor];
                linePtr4[0] = bgColor;
                linePtr4[1] = bgColor;
                linePtr4[2] = bgColor;
                linePtr4[3] = bgColor;
                linePtr4[4] = bgColor;
                linePtr4[5] = bgColor;
                linePtr4[6] = bgColor;
                linePtr4[7] = bgColor;
                charTable++; 
                X++;
                sprLine += sprLine != NULL ? 8 : 0;
                linePtr4 += 8;
            }

            if (hScroll512) {
                if (scroll & 0x20) {
                    charTable -= 32;
                }
            }

            index       = base | ((int)*charTable * 8);
            colPattern = vdp->vram[vdp->colTabBase & index];
            color[0]   = vdp->palette[colPattern & 0x0f];
            color[1]   = vdp->palette[colPattern >> 4];
            charPattern = vdp->vram[vdp->chrGenBase & index];

            switch (hScroll & 7) {
            case 1: col = *sprLine++; *linePtr4++ = col ? vdp->palette[col >> 1] : color[(charPattern >> 6) & 1]; 
            case 2: col = *sprLine++; *linePtr4++ = col ? vdp->palette[col >> 1] : color[(charPattern >> 5) & 1]; 
            case 3: col = *sprLine++; *linePtr4++ = col ? vdp->palette[col >> 1] : color[(charPattern >> 4) & 1]; 
            case 4: col = *sprLine++; *linePtr4++ = col ? vdp->palette[col >> 1] : color[(charPattern >> 3) & 1]; 
            case 5: col = *sprLine++; *linePtr4++ = col ? vdp->palette[col >> 1] : color[(charPattern >> 2) & 1]; 
            case 6: col = *sprLine++; *linePtr4++ = col ? vdp->palette[col >> 1] : color[(charPattern >> 1) & 1]; 
            case 7: col = *sprLine++; *linePtr4++ = col ? vdp->palette[col >> 1] : color[(charPattern >> 0) & 1]; charTable++;
            }
        }
    }

    if (linePtr4 == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    if (border) {
        UInt16 bgColor = vdp->palette[vdp->BGColor];
        while (X < X2) {
            linePtr4[0] = bgColor;
            linePtr4[1] = bgColor;
            linePtr4[2] = bgColor;
            linePtr4[3] = bgColor;
            linePtr4[4] = bgColor;
            linePtr4[5] = bgColor;
            linePtr4[6] = bgColor;
            linePtr4[7] = bgColor;
            linePtr4 += 8; 
            X++;
        }
    }
    else {
        while (X < X2) {
            index       = base | ((int)*charTable * 8);
            colPattern = vdp->vram[vdp->colTabBase & index];
            color[0]   = vdp->palette[colPattern & 0x0f];
            color[1]   = vdp->palette[colPattern >> 4];
            charPattern = vdp->vram[vdp->chrGenBase & index];

            linePtr4[0] = (col = sprLine[0]) ? vdp->palette[col >> 1] : color[(charPattern >> 7) & 1]; 
            linePtr4[1] = (col = sprLine[1]) ? vdp->palette[col >> 1] : color[(charPattern >> 6) & 1];
            linePtr4[2] = (col = sprLine[2]) ? vdp->palette[col >> 1] : color[(charPattern >> 5) & 1];
            linePtr4[3] = (col = sprLine[3]) ? vdp->palette[col >> 1] : color[(charPattern >> 4) & 1];
            linePtr4[4] = (col = sprLine[4]) ? vdp->palette[col >> 1] : color[(charPattern >> 3) & 1];
            linePtr4[5] = (col = sprLine[5]) ? vdp->palette[col >> 1] : color[(charPattern >> 2) & 1];
            linePtr4[6] = (col = sprLine[6]) ? vdp->palette[col >> 1] : color[(charPattern >> 1) & 1];
            linePtr4[7] = (col = sprLine[7]) ? vdp->palette[col >> 1] : color[(charPattern >> 0) & 1];
            sprLine += 8;
            charTable++;
            linePtr4 += 8; 
            X++;
        }
    }
    if (rightBorder) {
        RefreshRightBorder(vdp, Y, vdp->palette[vdp->BGColor], 0, 0);
    }
}

static void RefreshLine5(VDP* vdp, int Y, int X, int X2)
{
    static int     border;
    static UInt8*  charTable;
    static UInt8*  sprLine;
    static int     addrSwitch;
    static int     hScroll512;
    static int*    jump;
    static int     page;
    static int     scroll;
    static int     hScroll;
    static int     vscroll;
    static int     chrTabO;
    int col;
    int rightBorder;

    if (X == -1) {
        X++;
        linePtr5 = RefreshBorder(vdp, Y,  vdp->palette[vdp->BGColor], 0, 0);
        border = !vdp->screenOn || !vdp->drawArea;
        sprLine   = colorSpritesLine(vdp, Y, 0);

        if (linePtr5 == NULL) {
            return;
        }

        if (!border) {
            hScroll512 = vdpHScroll512(vdp);
            jump       = jumpTable + hScroll512 * 2;
            page       = (vdp->chrTabBase / 0x8000) & 1;
            hScroll    = vdpHScroll(vdp);
            vscroll    = vdpVScroll(vdp);
            chrTabO    = vdp->chrTabBase;
            scroll     = hScroll / 2;

            charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll;

            if (hScroll512) {
                if (scroll & 0x80) charTable += jump[page ^= 1];
                if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
            }

            if (vdpIsEdgeMasked(vdp->vdpRegs)) {
                UInt16 bgColor = vdp->palette[vdp->BGColor];
                linePtr5[0] = bgColor;
                linePtr5[1] = bgColor;
                linePtr5[2] = bgColor;
                linePtr5[3] = bgColor;
                linePtr5[4] = bgColor;
                linePtr5[5] = bgColor;
                linePtr5[6] = bgColor;
                linePtr5[7] = bgColor;

                UPDATE_TABLE_5(); UPDATE_TABLE_5(); UPDATE_TABLE_5(); UPDATE_TABLE_5();
                sprLine   += sprLine != NULL ? 8 : 0;
                linePtr5 += 8;
                charTable += 4;
                X++;
            }
        }
    }

    if (linePtr5 == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    if (border) {
        UInt16 bgColor = vdp->palette[vdp->BGColor];
        while (X < X2) {
            linePtr5[0] = bgColor;
            linePtr5[1] = bgColor;
            linePtr5[2] = bgColor;
            linePtr5[3] = bgColor;
            linePtr5[4] = bgColor;
            linePtr5[5] = bgColor;
            linePtr5[6] = bgColor;
            linePtr5[7] = bgColor;
            linePtr5 += 8; 
            X++;
        }
    }
    else {
        // Update vscroll if needed
        if (vscroll != vdpVScroll(vdp) || chrTabO != vdp->chrTabBase) {
            jump       = jumpTable + hScroll512 * 2;
            page       = (vdp->chrTabBase / 0x8000) & 1;
            hScroll    = vdpHScroll(vdp) + X * 8;
            scroll     = hScroll / 2;
            vscroll    = vdpVScroll(vdp);
            chrTabO    = vdp->chrTabBase;

            charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll;

            if (hScroll512) {
                if (scroll & 0x80) charTable += jump[page ^= 1];
                if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
            }
        }
        while (X < X2) {
            if (hScroll & 1) {
                linePtr5[0] = vdp->palette[(col = sprLine[0]) ? col >> 1 : charTable[0] & 0x0f]; UPDATE_TABLE_5();
                linePtr5[1] = vdp->palette[(col = sprLine[1]) ? col >> 1 : charTable[1] >> 4];
                linePtr5[2] = vdp->palette[(col = sprLine[2]) ? col >> 1 : charTable[1] & 0x0f]; UPDATE_TABLE_5();
                linePtr5[3] = vdp->palette[(col = sprLine[3]) ? col >> 1 : charTable[2] >> 4];
                linePtr5[4] = vdp->palette[(col = sprLine[4]) ? col >> 1 : charTable[2] & 0x0f]; UPDATE_TABLE_5();
                linePtr5[5] = vdp->palette[(col = sprLine[5]) ? col >> 1 : charTable[3] >> 4];
                linePtr5[6] = vdp->palette[(col = sprLine[6]) ? col >> 1 : charTable[3] & 0x0f]; UPDATE_TABLE_5();
                linePtr5[7] = vdp->palette[(col = sprLine[7]) ? col >> 1 : charTable[4] >> 4];
            }
            else {     
                linePtr5[0] = vdp->palette[(col = sprLine[0]) ? col >> 1 : charTable[0] >> 4];
                linePtr5[1] = vdp->palette[(col = sprLine[1]) ? col >> 1 : charTable[0] & 0x0f]; UPDATE_TABLE_5();
                linePtr5[2] = vdp->palette[(col = sprLine[2]) ? col >> 1 : charTable[1] >> 4];
                linePtr5[3] = vdp->palette[(col = sprLine[3]) ? col >> 1 : charTable[1] & 0x0f]; UPDATE_TABLE_5();
                linePtr5[4] = vdp->palette[(col = sprLine[4]) ? col >> 1 : charTable[2] >> 4];
                linePtr5[5] = vdp->palette[(col = sprLine[5]) ? col >> 1 : charTable[2] & 0x0f]; UPDATE_TABLE_5();
                linePtr5[6] = vdp->palette[(col = sprLine[6]) ? col >> 1 : charTable[3] >> 4];
                linePtr5[7] = vdp->palette[(col = sprLine[7]) ? col >> 1 : charTable[3] & 0x0f]; UPDATE_TABLE_5();
            }
            sprLine += 8;

            linePtr5 += 8; 
            charTable += 4;
            X++;
        }
    }

    if (rightBorder) {
        RefreshRightBorder(vdp, Y, vdp->palette[vdp->BGColor], 0, 0);
    }
}

static void RefreshLine6(VDP* vdp, int Y, int X, int X2)
{
    static int     border;
    static int*    jump;
    static int     hScroll512;
    static int     scroll;
    static int     page;
    static UInt8*  charTable;
    static UInt8*  sprLine;
    int col;
    int rightBorder;

    if (X == -1) {
        X++;
        linePtr6 = RefreshBorder6(vdp, Y, vdp->palette[(vdp->BGColor >> 2) & 0x03], vdp->palette[vdp->BGColor & 0x03], 1, 0);
        border = !vdp->screenOn || !vdp->drawArea;
        sprLine   = colorSpritesLine(vdp, Y, 1);

        if (linePtr6 == NULL) {
            return;
        }

        if (!border) {
            hScroll512 = vdpHScroll512(vdp);
            scroll     = vdpHScroll(vdp);
            jump       = jumpTable + hScroll512 * 2;
            page    = (vdp->chrTabBase / 0x8000) & 1;

            charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll / 2;

            if (hScroll512) {
                if (scroll & 0x100) charTable += jump[page ^= 1];
                if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
            }

            if (vdpIsEdgeMasked(vdp->vdpRegs)) {
                UInt16 bgColor = vdp->palette[vdp->BGColor & 0x03];
                linePtr6[0]  = linePtr6[1]  = bgColor; 
                linePtr6[2]  = linePtr6[3]  = bgColor; 
                linePtr6[4]  = linePtr6[5]  = bgColor; 
                linePtr6[6]  = linePtr6[7]  = bgColor; 
                linePtr6[8]  = linePtr6[9]  = bgColor; 
                linePtr6[10] = linePtr6[11] = bgColor; 
                linePtr6[12] = linePtr6[13] = bgColor; 
                linePtr6[14] = linePtr6[15] = bgColor; 
                UPDATE_TABLE_6(); UPDATE_TABLE_6(); UPDATE_TABLE_6(); UPDATE_TABLE_6();
                UPDATE_TABLE_6(); UPDATE_TABLE_6(); UPDATE_TABLE_6(); UPDATE_TABLE_6();
                sprLine += sprLine != NULL ? 8 : 0; 
                linePtr6 += 16; 
                charTable += 4;
                X++;
            }
        }
    }

    if (linePtr6 == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    if (border) {
        UInt16 bgColor1 = vdp->palette[(vdp->BGColor >> 2) & 0x03];
        UInt16 bgColor2 = vdp->palette[vdp->BGColor & 0x03];
        while (X < X2) {
            linePtr6[ 0] = bgColor1;
            linePtr6[ 1] = bgColor2;
            linePtr6[ 2] = bgColor1;
            linePtr6[ 3] = bgColor2;
            linePtr6[ 4] = bgColor1;
            linePtr6[ 5] = bgColor2;
            linePtr6[ 6] = bgColor1;
            linePtr6[ 7] = bgColor2;
            linePtr6[ 8] = bgColor1;
            linePtr6[ 9] = bgColor2;
            linePtr6[10] = bgColor1;
            linePtr6[11] = bgColor2;
            linePtr6[12] = bgColor1;
            linePtr6[13] = bgColor2;
            linePtr6[14] = bgColor1;
            linePtr6[15] = bgColor2;
            linePtr6 += 16; 
            X++;
        }
    }
    else {

        linePtr6[ 0] = vdp->palette[(col = sprLine[0] >> 3) ? (col >> 1) & 3 : (charTable[0] >> 2) & 3];

        while (X < X2) {
            if (scroll & 1) {
                linePtr6[ 0] = vdp->palette[(col = sprLine[0] >> 3) ? (col >> 1) & 3 : (charTable[0] >> 2) & 3];
                linePtr6[ 1] = vdp->palette[(col = sprLine[0]  & 7) ? (col >> 1) & 3 : (charTable[0] >> 0) & 3]; UPDATE_TABLE_6();
                linePtr6[ 2] = vdp->palette[(col = sprLine[1] >> 3) ? (col >> 1) & 3 : (charTable[1] >> 6) & 3];
                linePtr6[ 3] = vdp->palette[(col = sprLine[1]  & 7) ? (col >> 1) & 3 : (charTable[1] >> 4) & 3]; UPDATE_TABLE_6();
                linePtr6[ 4] = vdp->palette[(col = sprLine[2] >> 3) ? (col >> 1) & 3 : (charTable[1] >> 2) & 3];
                linePtr6[ 5] = vdp->palette[(col = sprLine[2]  & 7) ? (col >> 1) & 3 : (charTable[1] >> 0) & 3]; UPDATE_TABLE_6();
                linePtr6[ 6] = vdp->palette[(col = sprLine[3] >> 3) ? (col >> 1) & 3 : (charTable[2] >> 6) & 3];
                linePtr6[ 7] = vdp->palette[(col = sprLine[3]  & 7) ? (col >> 1) & 3 : (charTable[2] >> 4) & 3]; UPDATE_TABLE_6();
                linePtr6[ 8] = vdp->palette[(col = sprLine[4] >> 3) ? (col >> 1) & 3 : (charTable[2] >> 2) & 3];
                linePtr6[ 9] = vdp->palette[(col = sprLine[4]  & 7) ? (col >> 1) & 3 : (charTable[2] >> 0) & 3]; UPDATE_TABLE_6();
                linePtr6[10] = vdp->palette[(col = sprLine[5] >> 3) ? (col >> 1) & 3 : (charTable[3] >> 6) & 3];
                linePtr6[11] = vdp->palette[(col = sprLine[5]  & 7) ? (col >> 1) & 3 : (charTable[3] >> 4) & 3]; UPDATE_TABLE_6();
                linePtr6[12] = vdp->palette[(col = sprLine[6] >> 3) ? (col >> 1) & 3 : (charTable[3] >> 2) & 3];
                linePtr6[13] = vdp->palette[(col = sprLine[6]  & 7) ? (col >> 1) & 3 : (charTable[3] >> 0) & 3]; UPDATE_TABLE_6();
                linePtr6[14] = vdp->palette[(col = sprLine[7] >> 3) ? (col >> 1) & 3 : (charTable[4] >> 6) & 3];
                linePtr6[15] = vdp->palette[(col = sprLine[7]  & 7) ? (col >> 1) & 3 : (charTable[4] >> 4) & 3]; UPDATE_TABLE_6();
            }
            else {
                linePtr6[ 0] = vdp->palette[(col = sprLine[0] >> 3) ? (col >> 1) & 3 : (charTable[0] >> 6) & 3];
                linePtr6[ 1] = vdp->palette[(col = sprLine[0]  & 7) ? (col >> 1) & 3 : (charTable[0] >> 4) & 3]; UPDATE_TABLE_6();
                linePtr6[ 2] = vdp->palette[(col = sprLine[1] >> 3) ? (col >> 1) & 3 : (charTable[0] >> 2) & 3];
                linePtr6[ 3] = vdp->palette[(col = sprLine[1]  & 7) ? (col >> 1) & 3 : (charTable[0] >> 0) & 3]; UPDATE_TABLE_6();
                linePtr6[ 4] = vdp->palette[(col = sprLine[2] >> 3) ? (col >> 1) & 3 : (charTable[1] >> 6) & 3];
                linePtr6[ 5] = vdp->palette[(col = sprLine[2]  & 7) ? (col >> 1) & 3 : (charTable[1] >> 4) & 3]; UPDATE_TABLE_6();
                linePtr6[ 6] = vdp->palette[(col = sprLine[3] >> 3) ? (col >> 1) & 3 : (charTable[1] >> 2) & 3];
                linePtr6[ 7] = vdp->palette[(col = sprLine[3]  & 7) ? (col >> 1) & 3 : (charTable[1] >> 0) & 3]; UPDATE_TABLE_6();
                linePtr6[ 8] = vdp->palette[(col = sprLine[4] >> 3) ? (col >> 1) & 3 : (charTable[2] >> 6) & 3];
                linePtr6[ 9] = vdp->palette[(col = sprLine[4]  & 7) ? (col >> 1) & 3 : (charTable[2] >> 4) & 3]; UPDATE_TABLE_6();
                linePtr6[10] = vdp->palette[(col = sprLine[5] >> 3) ? (col >> 1) & 3 : (charTable[2] >> 2) & 3];
                linePtr6[11] = vdp->palette[(col = sprLine[5]  & 7) ? (col >> 1) & 3 : (charTable[2] >> 0) & 3]; UPDATE_TABLE_6();
                linePtr6[12] = vdp->palette[(col = sprLine[6] >> 3) ? (col >> 1) & 3 : (charTable[3] >> 6) & 3];
                linePtr6[13] = vdp->palette[(col = sprLine[6]  & 7) ? (col >> 1) & 3 : (charTable[3] >> 4) & 3]; UPDATE_TABLE_6();
                linePtr6[14] = vdp->palette[(col = sprLine[7] >> 3) ? (col >> 1) & 3 : (charTable[3] >> 2) & 3];
                linePtr6[15] = vdp->palette[(col = sprLine[7]  & 7) ? (col >> 1) & 3 : (charTable[3] >> 0) & 3]; UPDATE_TABLE_6();
            }
            sprLine += 8; 

            linePtr6 += 16; 
            charTable += 4;
            X++;
        }
    }
    if (rightBorder) {
        RefreshRightBorder6(vdp, Y, vdp->palette[(vdp->BGColor >> 2) & 0x03], vdp->palette[vdp->BGColor & 0x03], 1, 0);
    }
}

static void RefreshLine7(VDP* vdp, int Y, int X, int X2)
{
    static int     border;
    static UInt8*  charTable;
    static UInt8*  sprLine;
    static int     hScroll512;
    static int     page;
    static int*    jump;
    static int     scroll;
    static int     vscroll;
    static int     chrTabO;
    int col;
    int rightBorder;

    if (X == -1) {
        X++;
        linePtr7 = RefreshBorder(vdp, Y, vdp->palette[vdp->BGColor], 1, 0);
        border = !vdp->screenOn || !vdp->drawArea;
        sprLine = colorSpritesLine(vdp, Y, 0);
    
        if (linePtr7 == NULL) {
            return;
        }

        if (!border) {
            hScroll512 = vdpHScroll512(vdp);
            jump       = jumpTable + hScroll512 * 2;
            page    = (vdp->chrTabBase / 0x8000) & 1;
            scroll     = vdpHScroll(vdp);
            vscroll    = vdpVScroll(vdp);
            chrTabO    = vdp->chrTabBase;

            charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll / 2;


            if (hScroll512) {
                if (scroll & 0x100) charTable += jump[page ^= 1];
                if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
            }

            if (vdpIsEdgeMasked(vdp->vdpRegs)) {
                UInt16 bgColor = vdp->palette[vdp->BGColor];
                linePtr7[0]  = linePtr7[1]  = bgColor; 
                linePtr7[2]  = linePtr7[3]  = bgColor; 
                linePtr7[4]  = linePtr7[5]  = bgColor; 
                linePtr7[6]  = linePtr7[7]  = bgColor; 
                linePtr7[8]  = linePtr7[9]  = bgColor; 
                linePtr7[10] = linePtr7[11] = bgColor; 
                linePtr7[12] = linePtr7[13] = bgColor; 
                linePtr7[14] = linePtr7[15] = bgColor; 
                UPDATE_TABLE_7(); UPDATE_TABLE_7(); UPDATE_TABLE_7(); UPDATE_TABLE_7();
                UPDATE_TABLE_7(); UPDATE_TABLE_7(); UPDATE_TABLE_7(); UPDATE_TABLE_7();
                sprLine   += sprLine != NULL ? 8 : 0;
                linePtr7 += 16; 
                charTable += 4;
                X++; 
            }
        }
    }

    if (linePtr7 == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    if (border) {
        UInt16 bgColor = vdp->palette[vdp->BGColor];
        while (X < X2) {
            linePtr7[0] = bgColor;
            linePtr7[1] = bgColor;
            linePtr7[2] = bgColor;
            linePtr7[3] = bgColor;
            linePtr7[4] = bgColor;
            linePtr7[5] = bgColor;
            linePtr7[6] = bgColor;
            linePtr7[7] = bgColor;
            linePtr7[8] = bgColor;
            linePtr7[9] = bgColor;
            linePtr7[10] = bgColor;
            linePtr7[11] = bgColor;
            linePtr7[12] = bgColor;
            linePtr7[13] = bgColor;
            linePtr7[14] = bgColor;
            linePtr7[15] = bgColor;
            linePtr7 += 16; 
            X++;
        }
    }
    else {
        // Update vscroll if needed
        if (vscroll != vdpVScroll(vdp) || chrTabO != vdp->chrTabBase) {
            scroll  = vdpHScroll(vdp) + X * 8;
            page = (vdp->chrTabBase / 0x8000) & 1;
            jump    = jumpTable + hScroll512 * 2;
            vscroll = vdpVScroll(vdp);
            chrTabO  = vdp->chrTabBase;

            charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll / 2;

            if (hScroll512) {
                if (scroll & 0x100) charTable += jump[page ^= 1];
                if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
            }
        }

        while (X < X2) {
            if (scroll & 1) {
                (col = sprLine[0]) ? linePtr7[0]  = linePtr7[1]  = vdp->palette[col >> 1] : 
                (col = charTable[vdp->vram128], 
                linePtr7[0]  = vdp->palette[col >> 4],
                linePtr7[1]  = vdp->palette[col & 0xf]);
                UPDATE_TABLE_7();
                (col = sprLine[1]) ? linePtr7[2]  = linePtr7[3]  = vdp->palette[col >> 1] :
                (col = charTable[1],  
                linePtr7[2]  = vdp->palette[col >> 4],
                linePtr7[3]  = vdp->palette[col & 0xf]); 
                UPDATE_TABLE_7();
                (col = sprLine[2]) ? linePtr7[4]  = linePtr7[5]  = vdp->palette[col >> 1] : 
                (col = charTable[vdp->vram128|1],
                linePtr7[4]  = vdp->palette[col >> 4],
                linePtr7[5]  = vdp->palette[col & 0xf]);
                UPDATE_TABLE_7();
                (col = sprLine[3]) ? linePtr7[6]  = linePtr7[7]  = vdp->palette[col >> 1] : 
                (col = charTable[2],   
                linePtr7[6]  = vdp->palette[col >> 4],
                linePtr7[7]  = vdp->palette[col & 0xf]); 
                UPDATE_TABLE_7();
                (col = sprLine[4]) ? linePtr7[8]  = linePtr7[9]  = vdp->palette[col >> 1] :
                (col = charTable[vdp->vram128|2], 
                linePtr7[8]  = vdp->palette[col >> 4], 
                linePtr7[9]  = vdp->palette[col & 0xf]);
                UPDATE_TABLE_7();
                (col = sprLine[5]) ? linePtr7[10] = linePtr7[11] = vdp->palette[col >> 1] : 
                (col = charTable[3],      
                linePtr7[10] = vdp->palette[col >> 4],
                linePtr7[11] = vdp->palette[col & 0xf]); 
                UPDATE_TABLE_7();
                (col = sprLine[6]) ? linePtr7[12] = linePtr7[13] = vdp->palette[col >> 1] : 
                (col = charTable[vdp->vram128|3], 
                linePtr7[12] = vdp->palette[col >> 4], 
                linePtr7[13] = vdp->palette[col & 0xf]);
                UPDATE_TABLE_7();
                (col = sprLine[7]) ? linePtr7[14] = linePtr7[15] = vdp->palette[col >> 1] : 
                (col = charTable[4],  
                linePtr7[14] = vdp->palette[col >> 4], 
                linePtr7[15] = vdp->palette[col & 0xf]); 
                UPDATE_TABLE_7();
            }
            else {
                (col = sprLine[0]) ? linePtr7[0]  = linePtr7[1]  = vdp->palette[col >> 1] : 
                (col = charTable[0],      
                linePtr7[0]  = vdp->palette[col >> 4],
                linePtr7[1]  = vdp->palette[col & 0xf]);
                UPDATE_TABLE_7();
                (col = sprLine[1]) ? linePtr7[2]  = linePtr7[3]  = vdp->palette[col >> 1] : 
                (col = charTable[vdp->vram128], 
                linePtr7[2]  = vdp->palette[col >> 4],
                linePtr7[3]  = vdp->palette[col & 0xf]);
                UPDATE_TABLE_7();
                (col = sprLine[2]) ? linePtr7[4]  = linePtr7[5]  = vdp->palette[col >> 1] :
                (col = charTable[1],    
                linePtr7[4]  = vdp->palette[col >> 4], 
                linePtr7[5]  = vdp->palette[col & 0xf]);
                UPDATE_TABLE_7();
                (col = sprLine[3]) ? linePtr7[6]  = linePtr7[7]  = vdp->palette[col >> 1] :
                (col = charTable[vdp->vram128|1],
                linePtr7[6]  = vdp->palette[col >> 4], 
                linePtr7[7]  = vdp->palette[col & 0xf]);
                UPDATE_TABLE_7();
                (col = sprLine[4]) ? linePtr7[8]  = linePtr7[9]  = vdp->palette[col >> 1] : 
                (col = charTable[2],      
                linePtr7[8]  = vdp->palette[col >> 4], 
                linePtr7[9]  = vdp->palette[col & 0xf]); 
                UPDATE_TABLE_7();
                (col = sprLine[5]) ? linePtr7[10] = linePtr7[11] = vdp->palette[col >> 1] :
                (col = charTable[vdp->vram128|2], 
                linePtr7[10] = vdp->palette[col >> 4], 
                linePtr7[11] = vdp->palette[col & 0xf]); 
                UPDATE_TABLE_7();
                (col = sprLine[6]) ? linePtr7[12] = linePtr7[13] = vdp->palette[col >> 1] : 
                (col = charTable[3],   
                linePtr7[12] = vdp->palette[col >> 4], 
                linePtr7[13] = vdp->palette[col & 0xf]); 
                UPDATE_TABLE_7();
                (col = sprLine[7]) ? linePtr7[14] = linePtr7[15] = vdp->palette[col >> 1] : 
                (col = charTable[vdp->vram128|3], 
                linePtr7[14] = vdp->palette[col >> 4], 
                linePtr7[15] = vdp->palette[col & 0xf]); 
                UPDATE_TABLE_7();
            }
            sprLine += 8; 

            linePtr7 += 16; 
            charTable += 4;
            X++;
        }
    }    
    if (rightBorder) {
        RefreshRightBorder(vdp, Y, vdp->palette[vdp->BGColor], 1, 0);
    }
}

static void RefreshLine8(VDP* vdp, int Y, int X, int X2)
{
    static UInt8   SprToScr[16] = { 
        0x00, 0x02, 0x10, 0x12, 0x80, 0x82, 0x90, 0x92, 
        0x49, 0x4B, 0x59, 0x5B, 0xC9, 0xCB, 0xD9, 0xDB 
    };
    static int     border;
    static UInt8*  charTable;
    static UInt8*  sprLine;
    static int     hScroll;
    static int     hScroll512;
    static int*    jump;
    static int     page;
    static int     scroll;
    static int     vscroll;
    static int     chrTabO;
    int col;
    int rightBorder;

    if (X == -1) {
        X++;
        linePtr8 = RefreshBorder(vdp, Y, vdp->paletteFixed[vdp->vdpRegs[7]], 0, 0);
        border = !vdp->screenOn || !vdp->drawArea;
        sprLine = colorSpritesLine(vdp, Y, 0);

        if (linePtr8 == NULL) {
            return;
        }

        if (!border) {        
            hScroll    = vdpHScroll(vdp);
            hScroll512 = vdpHScroll512(vdp);
            jump       = jumpTable + hScroll512 * 2;
            page    = (vdp->chrTabBase / 0x8000) & 1;
            scroll     = hScroll;
            vscroll    = vdpVScroll(vdp);
            chrTabO    = vdp->chrTabBase;

            charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll / 2;

            if (hScroll512) {
                if (scroll & 0x100) charTable += jump[page ^= 1];
                if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
            }

            if (vdpIsEdgeMasked(vdp->vdpRegs)) {
                UInt16 bgColor = vdp->paletteFixed[vdp->vdpRegs[7]];
                linePtr8[0] = bgColor;
                linePtr8[1] = bgColor;
                linePtr8[2] = bgColor;
                linePtr8[3] = bgColor;
                linePtr8[4] = bgColor;
                linePtr8[5] = bgColor;
                linePtr8[6] = bgColor;
                linePtr8[7] = bgColor;
                UPDATE_TABLE_8(); UPDATE_TABLE_8(); UPDATE_TABLE_8(); UPDATE_TABLE_8();
                UPDATE_TABLE_8(); UPDATE_TABLE_8(); UPDATE_TABLE_8(); UPDATE_TABLE_8();
                sprLine   += sprLine != NULL ? 8 : 0; 
                charTable += 4;
                linePtr8 += 8; 
                X++; 
            }
        }
    }

    if (linePtr8 == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    if (border) {
        UInt16 bgColor = vdp->paletteFixed[vdp->vdpRegs[7]];
        while (X < X2) {
            linePtr8[0] = bgColor;
            linePtr8[1] = bgColor;
            linePtr8[2] = bgColor;
            linePtr8[3] = bgColor;
            linePtr8[4] = bgColor;
            linePtr8[5] = bgColor;
            linePtr8[6] = bgColor;
            linePtr8[7] = bgColor;
            linePtr8 += 8; 
            X++;
        }
    }
    else {
        // Update vscroll if needed
        if (vscroll != vdpVScroll(vdp) || chrTabO != vdp->chrTabBase) {
            scroll = vdpHScroll(vdp) + X * 8;
            jump   = jumpTable + hScroll512 * 2;
            vscroll = vdpVScroll(vdp);
            chrTabO = vdp->chrTabBase;

            charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll / 2;

            if (hScroll512) {
                if (scroll & 0x100) charTable += jump[page ^= 1];
                if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
            }
        }

        while (X < X2) {
            if (scroll & 1) {
                col = sprLine[0]; linePtr8[0] = col ? vdp->paletteSprite8[col >> 1] : 
                vdp->paletteFixed[charTable[vdp->vram128]]; UPDATE_TABLE_8();
                col = sprLine[1]; linePtr8[1] = col ? vdp->paletteSprite8[col >> 1] : 
                vdp->paletteFixed[charTable[1]]; UPDATE_TABLE_8();
                col = sprLine[2]; linePtr8[2] = col ? vdp->paletteSprite8[col >> 1] : 
                vdp->paletteFixed[charTable[vdp->vram128|1]]; UPDATE_TABLE_8();
                col = sprLine[3]; linePtr8[3] = col ? vdp->paletteSprite8[col >> 1] : 
                vdp->paletteFixed[charTable[2]]; UPDATE_TABLE_8();
                col = sprLine[4]; linePtr8[4] = col ? vdp->paletteSprite8[col >> 1] : 
                vdp->paletteFixed[charTable[vdp->vram128|2]]; UPDATE_TABLE_8();
                col = sprLine[5]; linePtr8[5] = col ? vdp->paletteSprite8[col >> 1] : 
                vdp->paletteFixed[charTable[3]]; UPDATE_TABLE_8();
                col = sprLine[6]; linePtr8[6] = col ? vdp->paletteSprite8[col >> 1] : 
                vdp->paletteFixed[charTable[vdp->vram128|3]]; UPDATE_TABLE_8();
                col = sprLine[7]; linePtr8[7] = col ? vdp->paletteSprite8[col >> 1] : 
                vdp->paletteFixed[charTable[4]]; UPDATE_TABLE_8();
            }
            else {
                col = sprLine[0]; linePtr8[0] = col ? vdp->paletteSprite8[col >> 1] : 
                vdp->paletteFixed[charTable[0]]; UPDATE_TABLE_8();
                col = sprLine[1]; linePtr8[1] = col ? vdp->paletteSprite8[col >> 1] : 
                vdp->paletteFixed[charTable[vdp->vram128]]; UPDATE_TABLE_8();
                col = sprLine[2]; linePtr8[2] = col ? vdp->paletteSprite8[col >> 1] : 
                vdp->paletteFixed[charTable[1]]; UPDATE_TABLE_8();
                col = sprLine[3]; linePtr8[3] = col ? vdp->paletteSprite8[col >> 1] : 
                vdp->paletteFixed[charTable[vdp->vram128|1]]; UPDATE_TABLE_8();
                col = sprLine[4]; linePtr8[4] = col ? vdp->paletteSprite8[col >> 1] : 
                vdp->paletteFixed[charTable[2]]; UPDATE_TABLE_8();
                col = sprLine[5]; linePtr8[5] = col ? vdp->paletteSprite8[col >> 1] : 
                vdp->paletteFixed[charTable[vdp->vram128|2]]; UPDATE_TABLE_8();
                col = sprLine[6]; linePtr8[6] = col ? vdp->paletteSprite8[col >> 1] : 
                vdp->paletteFixed[charTable[3]]; UPDATE_TABLE_8();
                col = sprLine[7]; linePtr8[7] = col ? vdp->paletteSprite8[col >> 1] : 
                vdp->paletteFixed[charTable[vdp->vram128|3]]; UPDATE_TABLE_8();
            }
            sprLine += 8; 

            charTable += 4; linePtr8 += 8; X++;
        }
    }

    if (rightBorder) {
        RefreshRightBorder(vdp, Y, vdp->paletteFixed[vdp->vdpRegs[7]], 0, 0);
    }
}

static void RefreshLine10(VDP* vdp, int Y, int X, int X2)
{
    static int     border;
    static UInt8* charTable;
    static UInt8* sprLine;
    static int hScroll512;
    static int* jump;
    static int page;
    static int scroll;
    static int vscroll;
    static int hscroll;
    static int chrTabO;
    int col;
    UInt8 t0, t1, t2, t3;
    int y, J, K;
    int rightBorder;

    if (X == -1) {
        X++;
        linePtr10 = RefreshBorder(vdp, Y, vdp->paletteFixed[vdp->vdpRegs[7]], 0, 0);
        border = !vdp->screenOn || !vdp->drawArea;
        sprLine = colorSpritesLine(vdp, Y, 0);

        if (linePtr10 == NULL) {
            return;
        }

        if (!border) {
            hScroll512 = vdpHScroll512(vdp);
            jump       = jumpTable + hScroll512 * 2;
            page    = (vdp->chrTabBase / 0x8000) & 1;
            hscroll    = vdpHScroll(vdp);
            scroll     = hscroll & ~3;
            vscroll    = vdpVScroll(vdp);
            chrTabO    = vdp->chrTabBase;

            charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll / 2;

            if (hScroll512) {
                if (scroll & 0x100) charTable += jump[page ^= 1];
                if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
            }

            if (vdpIsEdgeMasked(vdp->vdpRegs)) {
                UInt16 bgColor = vdp->paletteFixed[vdp->vdpRegs[7]];
                linePtr10[0] = bgColor;
                linePtr10[1] = bgColor;
                linePtr10[2] = bgColor;
                linePtr10[3] = bgColor;
                linePtr10[4] = bgColor;
                linePtr10[5] = bgColor;
                linePtr10[6] = bgColor;
                linePtr10[7] = bgColor;
                UPDATE_TABLE_10(); UPDATE_TABLE_10(); UPDATE_TABLE_10(); UPDATE_TABLE_10();
                UPDATE_TABLE_10(); UPDATE_TABLE_10(); UPDATE_TABLE_10(); UPDATE_TABLE_10();
                sprLine   += sprLine != NULL ? 8 : 0; 
                charTable += 4; 
                linePtr10 += 8;
                X++; 
            }

            t0 = charTable[0];              UPDATE_TABLE_10();
            t1 = charTable[vdp->vram128];   UPDATE_TABLE_10();
            t2 = charTable[1];              UPDATE_TABLE_10();
            t3 = charTable[vdp->vram128|1]; UPDATE_TABLE_10();


            K=(t0 & 0x07) | ((t1 & 0x07) << 3);
            J=(t2 & 0x07) | ((t3 & 0x07) << 3);

            switch (hscroll & 3) {
            case 0:
                col = sprLine[0]; y = t0 >> 3; *linePtr10++ = col ? vdp->palette[col >> 1] : y & 1 ? vdp->palette[y >> 1] : vdp->yjkColor[y][J][K];
            case 1:
                col = sprLine[1]; y = t1 >> 3; *linePtr10++ = col ? vdp->palette[col >> 1] : y & 1 ? vdp->palette[y >> 1] : vdp->yjkColor[y][J][K];
            case 2:
                col = sprLine[2]; y = t2 >> 3; *linePtr10++ = col ? vdp->palette[col >> 1] : y & 1 ? vdp->palette[y >> 1] : vdp->yjkColor[y][J][K];
            case 3:
                col = sprLine[3]; y = t3 >> 3; *linePtr10++ = col ? vdp->palette[col >> 1] : y & 1 ? vdp->palette[y >> 1] : vdp->yjkColor[y][J][K];
            }
            sprLine += 4;
            charTable += 2;
        }
    }

    if (linePtr10 == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    if (border) {
        UInt16 bgColor = vdp->paletteFixed[vdp->vdpRegs[7]];
        while (X < X2) {
            linePtr10[0] = bgColor;
            linePtr10[1] = bgColor;
            linePtr10[2] = bgColor;
            linePtr10[3] = bgColor;
            linePtr10[4] = bgColor;
            linePtr10[5] = bgColor;
            linePtr10[6] = bgColor;
            linePtr10[7] = bgColor;
            linePtr10 += 8; 
            X++;
        }
    }
    else {
        // Update vscroll if needed
        if (vscroll != vdpVScroll(vdp) || chrTabO != vdp->chrTabBase) {
            hscroll = vdpHScroll(vdp);
            scroll = (hscroll & ~3) + X * 8;
            jump   = jumpTable + hScroll512 * 2;
            vscroll = vdpVScroll(vdp);
            chrTabO  = vdp->chrTabBase;

            charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll / 2;
            charTable += 2; 

            if (hScroll512) {
                if (scroll & 0x100) charTable += jump[page ^= 1];
                if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
            }
        }

        while (X < X2) {
            t0 = charTable[0];              UPDATE_TABLE_10();
            t1 = charTable[vdp->vram128];   UPDATE_TABLE_10();
            t2 = charTable[1];              UPDATE_TABLE_10();
            t3 = charTable[vdp->vram128|1]; UPDATE_TABLE_10();

            K=(t0 & 0x07) | ((t1 & 0x07) << 3);
            J=(t2 & 0x07) | ((t3 & 0x07) << 3);

            col = sprLine[0]; y = t0 >> 3; linePtr10[0] = col ? vdp->palette[col >> 1] : y & 1 ? vdp->palette[y >> 1] : vdp->yjkColor[y][J][K];
            col = sprLine[1]; y = t1 >> 3; linePtr10[1] = col ? vdp->palette[col >> 1] : y & 1 ? vdp->palette[y >> 1] : vdp->yjkColor[y][J][K];
            col = sprLine[2]; y = t2 >> 3; linePtr10[2] = col ? vdp->palette[col >> 1] : y & 1 ? vdp->palette[y >> 1] : vdp->yjkColor[y][J][K];
            col = sprLine[3]; y = t3 >> 3; linePtr10[3] = col ? vdp->palette[col >> 1] : y & 1 ? vdp->palette[y >> 1] : vdp->yjkColor[y][J][K];

            t0 = charTable[2];        UPDATE_TABLE_10();
            t1 = charTable[vdp->vram128|2];  UPDATE_TABLE_10();
            t2 = charTable[3];        UPDATE_TABLE_10();
            t3 = charTable[vdp->vram128|3];  UPDATE_TABLE_10();

            K=(t0 & 0x07) | ((t1 & 0x07) << 3);
            J=(t2 & 0x07) | ((t3 & 0x07) << 3);

            if (X == 31) {
                switch (hscroll & 3) {
                case 1:
                    y = t2 >> 3; col = sprLine[6]; linePtr10[6] = col ? vdp->palette[col >> 1] : y & 1 ? vdp->palette[y >> 1] : vdp->yjkColor[y][J][K];
                case 2:
                    y = t1 >> 3; col = sprLine[5]; linePtr10[5] = col ? vdp->palette[col >> 1] : y & 1 ? vdp->palette[y >> 1] : vdp->yjkColor[y][J][K];
                case 3:
                    y = t0 >> 3; col = sprLine[4]; linePtr10[4] = col ? vdp->palette[col >> 1] : y & 1 ? vdp->palette[y >> 1] : vdp->yjkColor[y][J][K];
                }
            }
            else {
                col = sprLine[4]; y = t0 >> 3; linePtr10[4] = col ? vdp->palette[col >> 1] : y & 1 ? vdp->palette[y >> 1] : vdp->yjkColor[y][J][K];
                col = sprLine[5]; y = t1 >> 3; linePtr10[5] = col ? vdp->palette[col >> 1] : y & 1 ? vdp->palette[y >> 1] : vdp->yjkColor[y][J][K];
                col = sprLine[6]; y = t2 >> 3; linePtr10[6] = col ? vdp->palette[col >> 1] : y & 1 ? vdp->palette[y >> 1] : vdp->yjkColor[y][J][K];
                col = sprLine[7]; y = t3 >> 3; linePtr10[7] = col ? vdp->palette[col >> 1] : y & 1 ? vdp->palette[y >> 1] : vdp->yjkColor[y][J][K];
                sprLine += 8; 
            }

            charTable += 4; linePtr10 += 8;
            X++;
        }
    }

    if (rightBorder) {
        RefreshRightBorder(vdp, Y, vdp->paletteFixed[vdp->vdpRegs[7]], 0, 0);
    }
}

static void RefreshLine12(VDP* vdp, int Y, int X, int X2)
{
    static int     border;
    static UInt8* charTable;
    static UInt8* sprLine;
    static int hScroll512;
    static int* jump;
    static int page;
    static int scroll;
    static int vscroll;
    static int hscroll;
    static int chrTabO;
    int col;
    UInt8 t0, t1, t2, t3;
    int J, K;
    int rightBorder;

    if (X == -1) {
        X++;
        linePtr12 = RefreshBorder(vdp, Y, vdp->paletteFixed[vdp->vdpRegs[7]], 0, 0);
        border = !vdp->screenOn || !vdp->drawArea;
        sprLine = colorSpritesLine(vdp, Y, 0);

        if (linePtr12 == NULL) {
            return;
        }

        if (!border) {
            hScroll512 = vdpHScroll512(vdp);
            jump       = jumpTable + hScroll512 * 2;
            page    = (vdp->chrTabBase / 0x8000) & 1;
            hscroll    = vdpHScroll(vdp);
            scroll     = hscroll & ~3;
            vscroll    = vdpVScroll(vdp);
            chrTabO    = vdp->chrTabBase;

            charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll / 2;

            if (hScroll512) {
                if (scroll & 0x100) charTable += jump[page ^= 1];
                if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
            }

            if (vdpIsEdgeMasked(vdp->vdpRegs)) {
                UInt16 bgColor = vdp->paletteFixed[vdp->vdpRegs[7]];
                linePtr12[0] = bgColor;
                linePtr12[1] = bgColor;
                linePtr12[2] = bgColor;
                linePtr12[3] = bgColor;
                linePtr12[4] = bgColor;
                linePtr12[5] = bgColor;
                linePtr12[6] = bgColor;
                linePtr12[7] = bgColor;
                UPDATE_TABLE_12(); UPDATE_TABLE_12(); UPDATE_TABLE_12(); UPDATE_TABLE_12();
                UPDATE_TABLE_12(); UPDATE_TABLE_12(); UPDATE_TABLE_12(); UPDATE_TABLE_12();
                sprLine   += sprLine != NULL ? 8 : 0; 
                charTable += 4; 
                linePtr12 += 8;
                X++; 
            }

            t0 = charTable[0];              UPDATE_TABLE_12();
            t1 = charTable[vdp->vram128];   UPDATE_TABLE_12();
            t2 = charTable[1];              UPDATE_TABLE_12();
            t3 = charTable[vdp->vram128|1]; UPDATE_TABLE_12();

            K=(t0 & 0x07) | ((t1 & 0x07) << 3);
            J=(t2 & 0x07) | ((t3 & 0x07) << 3);

            switch (hscroll & 3) {
            case 0:
                col = sprLine[0]; *linePtr12++ = col ? vdp->palette[col >> 1] : vdp->yjkColor[t0 >> 3][J][K];
            case 1:
                col = sprLine[1]; *linePtr12++ = col ? vdp->palette[col >> 1] : vdp->yjkColor[t1 >> 3][J][K];
            case 2:
                col = sprLine[2]; *linePtr12++ = col ? vdp->palette[col >> 1] : vdp->yjkColor[t2 >> 3][J][K];
            case 3:
                col = sprLine[3]; *linePtr12++ = col ? vdp->palette[col >> 1] : vdp->yjkColor[t3 >> 3][J][K];
            }
            sprLine += 4;
            charTable += 2;
        }
    }

    if (linePtr12 == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    if (border) {
        UInt16 bgColor = vdp->paletteFixed[vdp->vdpRegs[7]];
        while (X < X2) {
            linePtr12[0] = bgColor;
            linePtr12[1] = bgColor;
            linePtr12[2] = bgColor;
            linePtr12[3] = bgColor;
            linePtr12[4] = bgColor;
            linePtr12[5] = bgColor;
            linePtr12[6] = bgColor;
            linePtr12[7] = bgColor;
            linePtr12 += 8; 
            X++;
        }
    }
    else {
        // Update vscroll if needed
        if (vscroll != vdpVScroll(vdp) || chrTabO != vdp->chrTabBase) {
            hscroll = vdpHScroll(vdp);
            scroll = (hscroll & ~3) + X * 8;
            jump   = jumpTable + hScroll512 * 2;
            vscroll = vdpVScroll(vdp);
            chrTabO  = vdp->chrTabBase;

            charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll / 2;
            charTable += 2; 

            if (hScroll512) {
                if (scroll & 0x100) charTable += jump[page ^= 1];
                if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
            }
        }

        while (X < X2) {
            t0 = charTable[0];         UPDATE_TABLE_12();
            t1 = charTable[vdp->vram128];   UPDATE_TABLE_12();
            t2 = charTable[1];         UPDATE_TABLE_12();
            t3 = charTable[vdp->vram128|1]; UPDATE_TABLE_12();

            K=(t0 & 0x07) | ((t1 & 0x07) << 3);
            J=(t2 & 0x07) | ((t3 & 0x07) << 3);

            col = sprLine[0]; linePtr12[0] = col ? vdp->palette[col >> 1] : vdp->yjkColor[t0 >> 3][J][K];
            col = sprLine[1]; linePtr12[1] = col ? vdp->palette[col >> 1] : vdp->yjkColor[t1 >> 3][J][K];
            col = sprLine[2]; linePtr12[2] = col ? vdp->palette[col >> 1] : vdp->yjkColor[t2 >> 3][J][K];
            col = sprLine[3]; linePtr12[3] = col ? vdp->palette[col >> 1] : vdp->yjkColor[t3 >> 3][J][K];

            t0 = charTable[2];        UPDATE_TABLE_12();
            t1 = charTable[vdp->vram128|2];  UPDATE_TABLE_12();
            t2 = charTable[3];        UPDATE_TABLE_12();
            t3 = charTable[vdp->vram128|3];  UPDATE_TABLE_12();

            K=(t0 & 0x07) | ((t1 & 0x07) << 3);
            J=(t2 & 0x07) | ((t3 & 0x07) << 3);

            if (X == 31) {
                switch (hscroll & 3) {
                case 1:
                    col = sprLine[6]; linePtr12[6] = col ? vdp->palette[col >> 1] : vdp->yjkColor[t2 >> 3][J][K];
                case 2:
                    col = sprLine[5]; linePtr12[5] = col ? vdp->palette[col >> 1] : vdp->yjkColor[t1 >> 3][J][K];
                case 3:
                    col = sprLine[4]; linePtr12[4] = col ? vdp->palette[col >> 1] : vdp->yjkColor[t0 >> 3][J][K];
                }
            }
            else {
                col = sprLine[4]; linePtr12[4] = col ? vdp->palette[col >> 1] : vdp->yjkColor[t0 >> 3][J][K];
                col = sprLine[5]; linePtr12[5] = col ? vdp->palette[col >> 1] : vdp->yjkColor[t1 >> 3][J][K];
                col = sprLine[6]; linePtr12[6] = col ? vdp->palette[col >> 1] : vdp->yjkColor[t2 >> 3][J][K];
                col = sprLine[7]; linePtr12[7] = col ? vdp->palette[col >> 1] : vdp->yjkColor[t3 >> 3][J][K];
                sprLine += 8; 
            }

            charTable += 4; linePtr12 += 8;
            X++;
        }
    }

    if (rightBorder) {
        RefreshRightBorder(vdp, Y, vdp->paletteFixed[vdp->vdpRegs[7]], 0, 0);
    }
}
