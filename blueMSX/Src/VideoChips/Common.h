/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoChips/Common.h,v $
**
** $Revision: 1.5 $
**
** $Date: 2005-01-17 05:52:32 $
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
#include "SpriteLine.h"

#define WIDTH  320
#define HEIGHT 240

extern UInt32* emuFrameBuffer;
extern int*    emuLineWidth;
extern UInt32  emuFixedPalette[256];
extern UInt32  emuFixedSpritePalette[16];

static UInt8 emptylineBuf[512];

extern UInt32 YJKtoYCbCrTable[32][64][64];

#define YJKColor(Y, J, K) YJKtoYCbCrTable[(Y)][J][K]

UInt32 *RefreshBorder(VDP* vdp, int Y, UInt32 bgColor, int line512, int borderExtra)
{
    int lineSize = line512 ? 2 : 1;
    UInt32 *dstBitmap;
    int offset;

    if (!displayEnable) {
        return NULL;
    }

    Y -= vdpIsVideoPal(vdp) ? 27 : 0;

    if (Y < 0 || Y >= HEIGHT) {
        return NULL;
    }

    dstBitmap = emuFrameBuffer + (vdp->vdpStatus[2] & 0x02) * WIDTH * HEIGHT +  2 * WIDTH * Y;

    emuLineWidth[Y] = line512;

    if (Y > 0) {
        for (offset = lineSize * ((WIDTH - 256) / 2 + vdp->HAdjust + borderExtra) - 1; offset >= 0; offset--) {
            dstBitmap[offset] = bgColor;
        }
    }

    if (!(vdp->screenOn && vdp->drawArea)) {
        for(offset = lineSize * WIDTH - 1; offset >= 0; offset--) {
            dstBitmap[offset] = bgColor;
        }

        return NULL;
    }

    /* Return pointer to the scanline in emuFrameBuffer */
    return dstBitmap + lineSize * ((WIDTH - 256) / 2 + vdp->HAdjust + borderExtra);
}

static void RefreshRightBorder(VDP* vdp, int Y, UInt32 bgColor, int line512, int borderExtra) {
    int lineSize = line512 ? 2 : 1;
    UInt32 *dstBitmap;
    int offset;

    Y -= vdpIsVideoPal(vdp) ? 27 : 0;


    if (Y < 0 || Y >= HEIGHT || !displayEnable) {
        return;
    }
    
    dstBitmap = emuFrameBuffer + (vdp->vdpStatus[2] & 0x02) * WIDTH * HEIGHT +  2 * WIDTH * Y;
    for(offset = lineSize * ((WIDTH - 256) / 2 - vdp->HAdjust + borderExtra); offset >= lineSize; offset--) {
        dstBitmap[lineSize * WIDTH - offset] = bgColor;
    }
}

static void RefreshLine0(VDP* vdp, int Y, int X, int X2)
{
    UInt32* dstBitmap;
    UInt8*  charTable;
    int     patternBase;
    UInt32  color[2];

    if (X2 >= 32) {
        RefreshRightBorder(vdp, Y, emuPalette[vdp->BGColor], 0, 7);
    }

    if (X != 0) {
        return;
    }

    dstBitmap = RefreshBorder(vdp, Y, emuPalette[vdp->BGColor], 0, 9);
    Y -= vdp->firstLine;
    if (dstBitmap == NULL) {
        return;
    }

    Y = Y + vdpVScroll(vdp) - vdp->scr0splitLine;
    charTable = vdp->vram + (vdp->chrTabBase & ((-1 << 12) | (0xc00 + 40 * (Y / 8))));
    patternBase = vdp->chrGenBase & ((-1 << 11) | (Y & 7));
    color[0] = emuPalette[vdp->BGColor];
    color[1] = emuPalette[vdp->FGColor];

    for (X = 0; X < 40; X++) {
        int pattern = vdp->vram[patternBase | ((int)*charTable * 8)];
        dstBitmap[0] = color[(pattern >> 7) & 1];
        dstBitmap[1] = color[(pattern >> 6) & 1];
        dstBitmap[2] = color[(pattern >> 5) & 1];
        dstBitmap[3] = color[(pattern >> 4) & 1];
        dstBitmap[4] = color[(pattern >> 3) & 1];
        dstBitmap[5] = color[(pattern >> 2) & 1];
        charTable++;
        dstBitmap += 6;
    }
}


static void RefreshLineTx80(VDP* vdp, int Y, int X, int X2)
{
    UInt32* dstBitmap;
    UInt8   colPattern;
    UInt8*  charTable;
    int     patternBase;
    UInt8*  colTable;
    UInt32  colors[4];

    if (X2 >= 32) {
        RefreshRightBorder(vdp, Y, emuPalette[vdp->BGColor], 1, 7);
    }

    if (X != 0) {
        return;
    }
    
    dstBitmap = RefreshBorder(vdp, Y, emuPalette[vdp->BGColor], 1, 9);
    Y -= vdp->firstLine;
    if (dstBitmap == NULL) {
        return;
    }

    Y = Y + vdpVScroll(vdp) - vdp->scr0splitLine;

    charTable   = vdp->vram + (vdp->chrTabBase & ((-1 << 12) | (80 * (Y / 8))));
    patternBase = vdp->chrGenBase & ((-1 << 11) | (Y & 7));
    colTable    = vdp->vram + (vdp->colTabBase & ((-1 << 9) | (10 * (Y / 8))));
    colors[0]   = emuPalette[vdp->BGColor];
    colors[1]   = emuPalette[vdp->FGColor];
    colors[2]   = emuPalette[vdp->XBGColor];
    colors[3]   = emuPalette[vdp->XFGColor];

    for(X = 0; X < 80; X++) {
        int charPattern = vdp->vram[patternBase | ((int)*charTable * 8)];
        UInt32* color;
        if ((X & 0x07) == 0) {
            colPattern = *colTable++;
        }
        color = colors + ((colPattern >> 6) & 2);
        colPattern <<= 1;

        dstBitmap[0] = color[(charPattern >> 7) & 1];
        dstBitmap[1] = color[(charPattern >> 6) & 1];
        dstBitmap[2] = color[(charPattern >> 5) & 1];
        dstBitmap[3] = color[(charPattern >> 4) & 1];
        dstBitmap[4] = color[(charPattern >> 3) & 1];
        dstBitmap[5] = color[(charPattern >> 2) & 1];
        charTable++;
        dstBitmap += 6;
    }
}

static void RefreshLine1(VDP* vdp, int Y, int X, int X2)
{
    static UInt32* dstBitmap = NULL;
    static UInt8*  sprLine = emptylineBuf;
    static UInt8*  charTable;
    static int     patternBase;
    UInt8  charPattern;
    UInt8  colPattern;
    UInt8  col;
    UInt32 color[2];
    int    y;
    int    rightBorder;

    if (X == 0) {
        dstBitmap = RefreshBorder(vdp, Y, emuPalette[vdp->BGColor], 0, 0);
        sprLine = spritesLine(vdp, Y);
        if (dstBitmap == NULL) {
            return;
        }

        y = Y - vdp->firstLine + vdpVScroll(vdp);
        charTable   = vdp->vram + (vdp->chrTabBase & ((-1 << 10) | (32 * (y / 8))));
        patternBase = vdp->chrGenBase & ((-1 << 11) | (y & 7));
    }

    if (dstBitmap == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    while (X < X2) {
        colPattern = vdp->vram[vdp->colTabBase & ((*charTable / 8) | (-1 << 6))];
        color[0] = emuPalette[colPattern & 0x0f];
        color[1] = emuPalette[colPattern >> 4];
        charPattern = vdp->vram[patternBase | ((int)*charTable * 8)];

        if (sprLine != NULL) {
            col = sprLine[0]; dstBitmap[0] = col ? emuPalette[col] : color[(charPattern >> 7) & 1]; 
            col = sprLine[1]; dstBitmap[1] = col ? emuPalette[col] : color[(charPattern >> 6) & 1];
            col = sprLine[2]; dstBitmap[2] = col ? emuPalette[col] : color[(charPattern >> 5) & 1]; 
            col = sprLine[3]; dstBitmap[3] = col ? emuPalette[col] : color[(charPattern >> 4) & 1];
            col = sprLine[4]; dstBitmap[4] = col ? emuPalette[col] : color[(charPattern >> 3) & 1]; 
            col = sprLine[5]; dstBitmap[5] = col ? emuPalette[col] : color[(charPattern >> 2) & 1];
            col = sprLine[6]; dstBitmap[6] = col ? emuPalette[col] : color[(charPattern >> 1) & 1]; 
            col = sprLine[7]; dstBitmap[7] = col ? emuPalette[col] : color[(charPattern >> 0) & 1];
            sprLine += 8;
        }
        else {
            dstBitmap[0] = color[(charPattern >> 7) & 1];
            dstBitmap[1] = color[(charPattern >> 6) & 1];
            dstBitmap[2] = color[(charPattern >> 5) & 1];
            dstBitmap[3] = color[(charPattern >> 4) & 1];
            dstBitmap[4] = color[(charPattern >> 3) & 1];
            dstBitmap[5] = color[(charPattern >> 2) & 1];
            dstBitmap[6] = color[(charPattern >> 1) & 1];
            dstBitmap[7] = color[(charPattern >> 0) & 1];
        }
        charTable++; 
        dstBitmap += 8; 
        X++;
    }

    if (rightBorder) {
        RefreshRightBorder(vdp, Y, emuPalette[vdp->BGColor], 0, 0);
    }
}

static void RefreshLine2(VDP* vdp, int Y, int X, int X2)
{
    static UInt32* dstBitmap = NULL;
    static UInt8*  sprLine = emptylineBuf;
    static UInt8*  charTable;
    static int     patternBase;
    static int     colorBase;
    UInt8  charPattern;
    UInt8  colPattern;
    UInt8  col;
    UInt32 color[2];
    int    index;
    int    y;
    int    rightBorder;

    if (X == 0) {
        int mask;

        dstBitmap = RefreshBorder(vdp, Y,  emuPalette[vdp->BGColor], 0, 0);
        sprLine = spritesLine(vdp, Y);
        if (dstBitmap == NULL) {
            return;
        }
 
        y = Y - vdp->firstLine + vdpVScroll(vdp);
        charTable   = vdp->vram + (vdp->chrTabBase & ((-1 << 10) | (32 * (y / 8))));
        mask        = (-1 << 13) | ((y & 0xc0) << 5) | (y & 7);
        patternBase = vdp->chrGenBase & mask;
        colorBase   = vdp->colTabBase & mask;
    }

    if (dstBitmap == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    while (X < X2) {
        index      = ((int)*charTable * 8);
        colPattern = vdp->vram[colorBase | index];
        color[0]   = emuPalette[colPattern & 0x0f];
        color[1]   = emuPalette[colPattern >> 4];
        charPattern = vdp->vram[patternBase | index];

        if (sprLine != NULL) {
            col = sprLine[0]; dstBitmap[0] = col ? emuPalette[col] : color[(charPattern >> 7) & 1]; 
            col = sprLine[1]; dstBitmap[1] = col ? emuPalette[col] : color[(charPattern >> 6) & 1];
            col = sprLine[2]; dstBitmap[2] = col ? emuPalette[col] : color[(charPattern >> 5) & 1];
            col = sprLine[3]; dstBitmap[3] = col ? emuPalette[col] : color[(charPattern >> 4) & 1];
            col = sprLine[4]; dstBitmap[4] = col ? emuPalette[col] : color[(charPattern >> 3) & 1];
            col = sprLine[5]; dstBitmap[5] = col ? emuPalette[col] : color[(charPattern >> 2) & 1];
            col = sprLine[6]; dstBitmap[6] = col ? emuPalette[col] : color[(charPattern >> 1) & 1];
            col = sprLine[7]; dstBitmap[7] = col ? emuPalette[col] : color[(charPattern >> 0) & 1];
            sprLine += 8;
        }
        else {
            dstBitmap[0] = color[(charPattern >> 7) & 1];
            dstBitmap[1] = color[(charPattern >> 6) & 1];
            dstBitmap[2] = color[(charPattern >> 5) & 1];
            dstBitmap[3] = color[(charPattern >> 4) & 1];
            dstBitmap[4] = color[(charPattern >> 3) & 1];
            dstBitmap[5] = color[(charPattern >> 2) & 1];
            dstBitmap[6] = color[(charPattern >> 1) & 1];
            dstBitmap[7] = color[(charPattern >> 0) & 1];
        }

        charTable++;
        dstBitmap += 8; 
        X++;
    }

    if (rightBorder) {
        RefreshRightBorder(vdp, Y, emuPalette[vdp->BGColor], 0, 0);
    }
}

static void RefreshLine3(VDP* vdp, int Y, int X, int X2)
{
    static UInt32* dstBitmap = NULL;
    static UInt8*  sprLine = emptylineBuf;
    static UInt8*  charTable;
    static int     patternBase;
    UInt8  colPattern;
    UInt32 fc;
    UInt32 bc;
    UInt8 col;
    int   y;
    int    rightBorder;

    if (X == 0) {
        dstBitmap = RefreshBorder(vdp, Y, emuPalette[vdp->BGColor], 0, 0);
        sprLine = spritesLine(vdp, Y);
        if (dstBitmap == NULL) {
            return;
        }

        y = Y - vdp->firstLine + vdpVScroll(vdp);
        charTable   = vdp->vram + (vdp->chrTabBase & ((-1 << 10) | (32 * (y / 8))));
        patternBase = vdp->chrGenBase & ((-1 << 11) | ((y >> 2) & 7));
    }

    if (dstBitmap == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    while (X < X2) {
        colPattern = vdp->vram[patternBase | ((int)*charTable * 8)];
        fc = emuPalette[colPattern >> 4];
        bc = emuPalette[colPattern & 0x0f];

        if (sprLine != NULL) {
            col = sprLine[0]; dstBitmap[0] = col ? emuPalette[col] : fc; 
            col = sprLine[1]; dstBitmap[1] = col ? emuPalette[col] : fc;
            col = sprLine[2]; dstBitmap[2] = col ? emuPalette[col] : fc; 
            col = sprLine[3]; dstBitmap[3] = col ? emuPalette[col] : fc;
            col = sprLine[4]; dstBitmap[4] = col ? emuPalette[col] : bc; 
            col = sprLine[5]; dstBitmap[5] = col ? emuPalette[col] : bc;
            col = sprLine[6]; dstBitmap[6] = col ? emuPalette[col] : bc; 
            col = sprLine[7]; dstBitmap[7] = col ? emuPalette[col] : bc;
            sprLine += 8;
        }
        else {
            dstBitmap[0] = fc; 
            dstBitmap[1] = fc;
            dstBitmap[2] = fc; 
            dstBitmap[3] = fc;
            dstBitmap[4] = bc; 
            dstBitmap[5] = bc;
            dstBitmap[6] = bc; 
            dstBitmap[7] = bc;
        }

        charTable++; 
        dstBitmap += 8; 
        X++;
    }

    if (rightBorder) {
        RefreshRightBorder(vdp, Y, emuPalette[vdp->BGColor], 0, 0);
    }
}


static void RefreshLine4(VDP* vdp, int Y, int X, int X2)
{
    static int jumpTable[] = { -128, -128, -0x8080, 0x7f80 };
    static UInt32* dstBitmap = NULL;
    static UInt8*  sprLine = emptylineBuf;
    static UInt8*  charTable;
    static int     patternBase;
    static int     colorBase;
    static int     hScroll;
    static int     hScroll512;
    static int*    jump;
    static int     page;
    static int     scroll;
    UInt8  charPattern;
    UInt8  colPattern;
    UInt8  col;
    UInt32 color[2];
    int    index;
    int    rightBorder;

    if (X == 0) {
        int mask;
        int y;

        dstBitmap = RefreshBorder(vdp, Y, emuPalette[vdp->BGColor], 0, 0);
        sprLine = colorSpritesLine(vdp, Y);
        if (dstBitmap == NULL) {
            return;
        }
        hScroll    =  ((((int)(vdp->vdpRegs[26] & 0x3F & ~(~vdpHScroll512(vdp) << 5))) << 3) - (int)(vdp->vdpRegs[27] & 0x07) & 0xffffffff);
        hScroll512 = vdpHScroll512(vdp);
        jump       = jumpTable + hScroll512 * 2;
        page       = (vdp->chrTabBase / 0x8000) & 1;
        scroll     = hScroll >> 3;

        y = Y - vdp->firstLine + vdpVScroll(vdp);
        charTable   = vdp->vram + (vdp->chrTabBase & ((-1 << 10) | (32 * (y / 8)))) + scroll;
        mask        = (-1 << 13) | ((y & 0xc0) << 5) | (y & 7);
        patternBase = vdp->chrGenBase & mask;
        colorBase   = vdp->colTabBase & mask;

        if (vdpIsEdgeMasked(vdp->vdpRegs)) {
            UInt32 bgColor = emuPalette[vdp->BGColor];
            dstBitmap[0] = bgColor;
            dstBitmap[1] = bgColor;
            dstBitmap[2] = bgColor;
            dstBitmap[3] = bgColor;
            dstBitmap[4] = bgColor;
            dstBitmap[5] = bgColor;
            dstBitmap[6] = bgColor;
            dstBitmap[7] = bgColor;
            charTable++; 
            X++;
            sprLine += sprLine != NULL ? 8 : 0;
            dstBitmap += 8;
        }

        if (hScroll512) {
            if (scroll & 0x20) {
                charTable -= 32;
            }
        }

        index       = ((int)*charTable * 8);
        colPattern  = vdp->vram[colorBase | index];
        color[0]    = emuPalette[colPattern & 0x0f];
        color[1]    = emuPalette[colPattern >> 4];
        charPattern = vdp->vram[patternBase | index];

        if (sprLine != NULL) {
            switch (hScroll & 7) {
                case 1: col = *sprLine++; *dstBitmap++ = col ? emuPalette[col >> 1] : color[(charPattern >> 6) & 1]; 
                case 2: col = *sprLine++; *dstBitmap++ = col ? emuPalette[col >> 1] : color[(charPattern >> 5) & 1]; 
                case 3: col = *sprLine++; *dstBitmap++ = col ? emuPalette[col >> 1] : color[(charPattern >> 4) & 1]; 
                case 4: col = *sprLine++; *dstBitmap++ = col ? emuPalette[col >> 1] : color[(charPattern >> 3) & 1]; 
                case 5: col = *sprLine++; *dstBitmap++ = col ? emuPalette[col >> 1] : color[(charPattern >> 2) & 1]; 
                case 6: col = *sprLine++; *dstBitmap++ = col ? emuPalette[col >> 1] : color[(charPattern >> 1) & 1]; 
                case 7: col = *sprLine++; *dstBitmap++ = col ? emuPalette[col >> 1] : color[(charPattern >> 0) & 1]; charTable++;
            }
        }
        else {
            switch (hScroll & 7) {
                case 1: *dstBitmap++ = color[(charPattern >> 6) & 1]; 
                case 2: *dstBitmap++ = color[(charPattern >> 5) & 1]; 
                case 3: *dstBitmap++ = color[(charPattern >> 4) & 1]; 
                case 4: *dstBitmap++ = color[(charPattern >> 3) & 1]; 
                case 5: *dstBitmap++ = color[(charPattern >> 2) & 1]; 
                case 6: *dstBitmap++ = color[(charPattern >> 1) & 1]; 
                case 7: *dstBitmap++ = color[(charPattern >> 0) & 1];  charTable++;
            }
        }
    }

    if (dstBitmap == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    while (X < X2) {
        index       = ((int)*charTable * 8);
        colPattern  = vdp->vram[colorBase | index];
        color[0]    = emuPalette[colPattern & 0x0f];
        color[1]    = emuPalette[colPattern >> 4];
        charPattern = vdp->vram[patternBase | index];

        if (sprLine != NULL) {
            col = sprLine[0]; dstBitmap[0] = col ? emuPalette[col >> 1] : color[(charPattern >> 7) & 1]; 
            col = sprLine[1]; dstBitmap[1] = col ? emuPalette[col >> 1] : color[(charPattern >> 6) & 1];
            col = sprLine[2]; dstBitmap[2] = col ? emuPalette[col >> 1] : color[(charPattern >> 5) & 1];
            col = sprLine[3]; dstBitmap[3] = col ? emuPalette[col >> 1] : color[(charPattern >> 4) & 1];
            col = sprLine[4]; dstBitmap[4] = col ? emuPalette[col >> 1] : color[(charPattern >> 3) & 1];
            col = sprLine[5]; dstBitmap[5] = col ? emuPalette[col >> 1] : color[(charPattern >> 2) & 1];
            col = sprLine[6]; dstBitmap[6] = col ? emuPalette[col >> 1] : color[(charPattern >> 1) & 1];
            col = sprLine[7]; dstBitmap[7] = col ? emuPalette[col >> 1] : color[(charPattern >> 0) & 1];
            sprLine += 8;
        }
        else {
            dstBitmap[0] = color[(charPattern >> 7) & 1];
            dstBitmap[1] = color[(charPattern >> 6) & 1];
            dstBitmap[2] = color[(charPattern >> 5) & 1];
            dstBitmap[3] = color[(charPattern >> 4) & 1];
            dstBitmap[4] = color[(charPattern >> 3) & 1];
            dstBitmap[5] = color[(charPattern >> 2) & 1];
            dstBitmap[6] = color[(charPattern >> 1) & 1];
            dstBitmap[7] = color[(charPattern >> 0) & 1];
        }

        charTable++;
        dstBitmap += 8; 
        X++;
    }

    if (rightBorder) {
        RefreshRightBorder(vdp, Y, emuPalette[vdp->BGColor], 0, 0);
    }
}

static void RefreshLine5(VDP* vdp, int Y, int X, int X2)
{
    static int     jumpTable[] = { -128, -128, -0x8080, 0x7f80 };
    static UInt32* dstBitmap = NULL;
    static UInt8*  charTable;
    static UInt8*  sprLine = emptylineBuf;
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

    if (X == 0) {
        dstBitmap = RefreshBorder(vdp, Y,  emuPalette[vdp->BGColor], 0, 0);
        sprLine   = colorSpritesLine(vdp, Y);
        if (dstBitmap == NULL) {
            return;
        }

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

#define UPDATE_T() if ((++scroll & 0x7f) == 0) charTable += jump[page ^= 1];

        if (vdpIsEdgeMasked(vdp->vdpRegs)) {
            UInt32 bgColor = emuPalette[vdp->BGColor];
            dstBitmap[0] = bgColor;
            dstBitmap[1] = bgColor;
            dstBitmap[2] = bgColor;
            dstBitmap[3] = bgColor;
            dstBitmap[4] = bgColor;
            dstBitmap[5] = bgColor;
            dstBitmap[6] = bgColor;
            dstBitmap[7] = bgColor;

            UPDATE_T(); UPDATE_T(); UPDATE_T(); UPDATE_T();
            sprLine   += sprLine != NULL ? 8 : 0;
            dstBitmap += 8;
            charTable += 4;
            X++;
        }
    }

    if (dstBitmap == NULL) {
        return;
    }

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

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    while (X < X2) {
        if (sprLine != NULL) {
            if (hScroll & 1) {
                col = sprLine[0]; dstBitmap[0] = emuPalette[col? col >> 1 : charTable[0] & 0x0f]; UPDATE_T();
                col = sprLine[1]; dstBitmap[1] = emuPalette[col? col >> 1 : charTable[1] >> 4];
                col = sprLine[2]; dstBitmap[2] = emuPalette[col? col >> 1 : charTable[1] & 0x0f]; UPDATE_T();
                col = sprLine[3]; dstBitmap[3] = emuPalette[col? col >> 1 : charTable[2] >> 4];
                col = sprLine[4]; dstBitmap[4] = emuPalette[col? col >> 1 : charTable[2] & 0x0f]; UPDATE_T();
                col = sprLine[5]; dstBitmap[5] = emuPalette[col? col >> 1 : charTable[3] >> 4];
                col = sprLine[6]; dstBitmap[6] = emuPalette[col? col >> 1 : charTable[3] & 0x0f]; UPDATE_T();
                col = sprLine[7]; dstBitmap[7] = emuPalette[col? col >> 1 : charTable[4] >> 4];
            }
            else {     
                col = sprLine[0]; dstBitmap[0] = emuPalette[col? col >> 1 : charTable[0] >> 4];
                col = sprLine[1]; dstBitmap[1] = emuPalette[col? col >> 1 : charTable[0] & 0x0f]; UPDATE_T();
                col = sprLine[2]; dstBitmap[2] = emuPalette[col? col >> 1 : charTable[1] >> 4];
                col = sprLine[3]; dstBitmap[3] = emuPalette[col? col >> 1 : charTable[1] & 0x0f]; UPDATE_T();
                col = sprLine[4]; dstBitmap[4] = emuPalette[col? col >> 1 : charTable[2] >> 4];
                col = sprLine[5]; dstBitmap[5] = emuPalette[col? col >> 1 : charTable[2] & 0x0f]; UPDATE_T();
                col = sprLine[6]; dstBitmap[6] = emuPalette[col? col >> 1 : charTable[3] >> 4];
                col = sprLine[7]; dstBitmap[7] = emuPalette[col? col >> 1 : charTable[3] & 0x0f]; UPDATE_T();
            }
            sprLine += 8;
        }
        else {
            if (hScroll & 1) {
                dstBitmap[0] = emuPalette[charTable[0] & 0x0f]; UPDATE_T();
                dstBitmap[1] = emuPalette[charTable[1] >> 4];
                dstBitmap[2] = emuPalette[charTable[1] & 0x0f]; UPDATE_T();
                dstBitmap[3] = emuPalette[charTable[2] >> 4];
                dstBitmap[4] = emuPalette[charTable[2] & 0x0f]; UPDATE_T();
                dstBitmap[5] = emuPalette[charTable[3] >> 4];
                dstBitmap[6] = emuPalette[charTable[3] & 0x0f]; UPDATE_T();
                dstBitmap[7] = emuPalette[charTable[4] >> 4];
            }
            else {     
                dstBitmap[0] = emuPalette[charTable[0] >> 4];
                dstBitmap[1] = emuPalette[charTable[0] & 0x0f]; UPDATE_T();
                dstBitmap[2] = emuPalette[charTable[1] >> 4];
                dstBitmap[3] = emuPalette[charTable[1] & 0x0f]; UPDATE_T();
                dstBitmap[4] = emuPalette[charTable[2] >> 4];
                dstBitmap[5] = emuPalette[charTable[2] & 0x0f]; UPDATE_T();
                dstBitmap[6] = emuPalette[charTable[3] >> 4];
                dstBitmap[7] = emuPalette[charTable[3] & 0x0f]; UPDATE_T();
            }
        }
    #undef UPDATE_T

        dstBitmap += 8; 
        charTable += 4;
        X++;
     }

    if (rightBorder) {
        RefreshRightBorder(vdp, Y, emuPalette[vdp->BGColor], 0, 0);
    }
}

static void RefreshLine6(VDP* vdp, int Y, int X, int X2)
{
    static int     jumpTable[] = { -128, -128, -0x8080, 0x7f80 };
    static int*    jump;
    static int     hScroll512;
    static int     scroll;
    static int     page;
    static UInt32* dstBitmap = NULL;
    static UInt8*  charTable;
    static UInt8*  sprLine = emptylineBuf;
    int col;
    int rightBorder;

    if (X == 0) {
        dstBitmap = RefreshBorder(vdp, Y, emuPalette[vdp->BGColor & 0x03], 1, 0);
        sprLine   = colorSpritesLine(vdp, Y);
        if (dstBitmap == NULL) {
            return;
        }
        
        hScroll512 = vdpHScroll512(vdp);
        scroll     = vdpHScroll(vdp);
        jump       = jumpTable + hScroll512 * 2;
        page    = (vdp->chrTabBase / 0x8000) & 1;

        charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll / 2;

        if (hScroll512) {
            if (scroll & 0x100) charTable += jump[page ^= 1];
            if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
        }

#define UPDATE_T() if ((++scroll & 0xff) == 0) charTable += jump[page ^= 1];

        if (vdpIsEdgeMasked(vdp->vdpRegs)) {
            UInt32 bgColor = emuPalette[vdp->BGColor & 0x03];
            dstBitmap[0]  = dstBitmap[1]  = bgColor; 
            dstBitmap[2]  = dstBitmap[3]  = bgColor; 
            dstBitmap[4]  = dstBitmap[5]  = bgColor; 
            dstBitmap[6]  = dstBitmap[7]  = bgColor; 
            dstBitmap[8]  = dstBitmap[9]  = bgColor; 
            dstBitmap[10] = dstBitmap[11] = bgColor; 
            dstBitmap[12] = dstBitmap[13] = bgColor; 
            dstBitmap[14] = dstBitmap[15] = bgColor; 
            UPDATE_T(); UPDATE_T(); UPDATE_T(); UPDATE_T();
            UPDATE_T(); UPDATE_T(); UPDATE_T(); UPDATE_T();
            sprLine += sprLine != NULL ? 8 : 0; 
            dstBitmap += 16; 
            charTable += 4;
            X++;
        }
    }

    if (dstBitmap == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    while (X < X2) {
        if (sprLine != NULL) {
            if (scroll & 1) {
                (col = sprLine[0]) ? dstBitmap[0]  = dstBitmap[1]  = emuPalette[(col >> 1) & 3] : 
                    (col = charTable[0],
                    dstBitmap[0]  = emuPalette[(col >> 2) & 3],
                    dstBitmap[1]  = emuPalette[(col >> 0) & 3]);
                UPDATE_T();
                (col = sprLine[1]) ? dstBitmap[2]  = dstBitmap[3]  = emuPalette[(col >> 1) & 3] : 
                    (col = charTable[1],
                    dstBitmap[2]  = emuPalette[(col >> 6) & 3], 
                    dstBitmap[3]  = emuPalette[(col >> 4) & 3]);
                UPDATE_T();
                (col = sprLine[2]) ? dstBitmap[4]  = dstBitmap[5]  = emuPalette[(col >> 1) & 3] : 
                    (col = charTable[1], 
                    dstBitmap[4]  = emuPalette[(col >> 2) & 3], 
                    dstBitmap[5]  = emuPalette[(col >> 0) & 3]);
                UPDATE_T();
                (col = sprLine[3]) ? dstBitmap[6]  = dstBitmap[7]  = emuPalette[(col >> 1) & 3] : 
                    (col = charTable[2],
                    dstBitmap[6]  = emuPalette[(col >> 6) & 3],
                    dstBitmap[7]  = emuPalette[(col >> 4) & 3]);
                UPDATE_T();
                (col = sprLine[4]) ? dstBitmap[8]  = dstBitmap[9]  = emuPalette[(col >> 1) & 3] : 
                    (col = charTable[2],
                    dstBitmap[8]  = emuPalette[(col >> 2) & 3],
                    dstBitmap[9]  = emuPalette[(col >> 0) & 3]);
                UPDATE_T();
                (col = sprLine[5]) ? dstBitmap[10] = dstBitmap[11] = emuPalette[(col >> 1) & 3] : 
                    (col = charTable[3], 
                    dstBitmap[10] = emuPalette[(col >> 6) & 3], 
                    dstBitmap[11] = emuPalette[(col >> 4) & 3]); 
                UPDATE_T();
                (col = sprLine[6]) ? dstBitmap[12] = dstBitmap[13] = emuPalette[(col >> 1) & 3] : 
                    (col = charTable[3],
                    dstBitmap[12] = emuPalette[(col >> 2) & 3], 
                    dstBitmap[13] = emuPalette[(col >> 0) & 3]); 
                UPDATE_T();
                (col = sprLine[7]) ? dstBitmap[14] = dstBitmap[15] = emuPalette[(col >> 1) & 3] : 
                    (col = charTable[4],
                    dstBitmap[14] = emuPalette[(col >> 6) & 3],
                    dstBitmap[15] = emuPalette[(col >> 4) & 3]);
                UPDATE_T();
            }
            else {
                (col = sprLine[0]) ? dstBitmap[0]  = dstBitmap[1]  = emuPalette[(col >> 1) & 3] : 
                    (col = charTable[0], 
                    dstBitmap[0]  = emuPalette[(col >> 6) & 3], 
                    dstBitmap[1]  = emuPalette[(col >> 4) & 3]);
                UPDATE_T();
                (col = sprLine[1]) ? dstBitmap[2]  = dstBitmap[3]  = emuPalette[(col >> 1) & 3] : 
                    (col = charTable[0], 
                    dstBitmap[2]  = emuPalette[(col >> 2) & 3],
                    dstBitmap[3]  = emuPalette[(col >> 0) & 3]); 
                UPDATE_T();
                (col = sprLine[2]) ? dstBitmap[4]  = dstBitmap[5]  = emuPalette[(col >> 1) & 3] : 
                    (col = charTable[1], 
                    dstBitmap[4]  = emuPalette[(col >> 6) & 3], 
                    dstBitmap[5]  = emuPalette[(col >> 4) & 3]);
                UPDATE_T();
                (col = sprLine[3]) ? dstBitmap[6]  = dstBitmap[7]  = emuPalette[(col >> 1) & 3] : 
                    (col = charTable[1],
                    dstBitmap[6]  = emuPalette[(col >> 2) & 3], 
                    dstBitmap[7]  = emuPalette[(col >> 0) & 3]);
                UPDATE_T();
                (col = sprLine[4]) ? dstBitmap[8]  = dstBitmap[9]  = emuPalette[(col >> 1) & 3] : 
                    (col = charTable[2], 
                    dstBitmap[8]  = emuPalette[(col >> 6) & 3],
                    dstBitmap[9]  = emuPalette[(col >> 4) & 3]);
                UPDATE_T();
                (col = sprLine[5]) ? dstBitmap[10] = dstBitmap[11] = emuPalette[(col >> 1) & 3] : 
                    (col = charTable[2], 
                    dstBitmap[10] = emuPalette[(col >> 2) & 3],
                    dstBitmap[11] = emuPalette[(col >> 0) & 3]); 
                UPDATE_T();
                (col = sprLine[6]) ? dstBitmap[12] = dstBitmap[13] = emuPalette[(col >> 1) & 3] : 
                    (col = charTable[3],
                    dstBitmap[12] = emuPalette[(col >> 6) & 3], 
                    dstBitmap[13] = emuPalette[(col >> 4) & 3]); 
                UPDATE_T();
                (col = sprLine[7]) ? dstBitmap[14] = dstBitmap[15] = emuPalette[(col >> 1) & 3] :
                    (col = charTable[3],
                    dstBitmap[14] = emuPalette[(col >> 2) & 3], 
                    dstBitmap[15] = emuPalette[(col >> 0) & 3]);
                UPDATE_T();
            }
            sprLine += 8; 
        }
        else {
            if (scroll & 1) {
                col = charTable[0]; 
                dstBitmap[0]  = emuPalette[(col >> 2) & 3]; 
                dstBitmap[1]  = emuPalette[(col >> 0) & 3]; 
                UPDATE_T();
                col = charTable[1]; 
                dstBitmap[2]  = emuPalette[(col >> 6) & 3]; 
                dstBitmap[3]  = emuPalette[(col >> 4) & 3];
                UPDATE_T();
                col = charTable[1]; 
                dstBitmap[4]  = emuPalette[(col >> 2) & 3];
                dstBitmap[5]  = emuPalette[(col >> 0) & 3];
                UPDATE_T();
                col = charTable[2]; 
                dstBitmap[6]  = emuPalette[(col >> 6) & 3]; 
                dstBitmap[7]  = emuPalette[(col >> 4) & 3];
                UPDATE_T();
                col = charTable[2]; 
                dstBitmap[8]  = emuPalette[(col >> 2) & 3]; 
                dstBitmap[9]  = emuPalette[(col >> 0) & 3];
                UPDATE_T();
                col = charTable[3]; 
                dstBitmap[10] = emuPalette[(col >> 6) & 3]; 
                dstBitmap[11] = emuPalette[(col >> 4) & 3]; 
                UPDATE_T();
                col = charTable[3]; 
                dstBitmap[12] = emuPalette[(col >> 2) & 3]; 
                dstBitmap[13] = emuPalette[(col >> 0) & 3];
                UPDATE_T();
                col = charTable[4]; 
                dstBitmap[14] = emuPalette[(col >> 6) & 3]; 
                dstBitmap[15] = emuPalette[(col >> 4) & 3]; 
                UPDATE_T();
            }
            else {
                col = charTable[0];
                dstBitmap[0]  = emuPalette[(col >> 6) & 3];
                dstBitmap[1]  = emuPalette[(col >> 4) & 3];
                UPDATE_T();
                col = charTable[0];
                dstBitmap[2]  = emuPalette[(col >> 2) & 3]; 
                dstBitmap[3]  = emuPalette[(col >> 0) & 3]; 
                UPDATE_T();
                col = charTable[1];
                dstBitmap[4]  = emuPalette[(col >> 6) & 3]; 
                dstBitmap[5]  = emuPalette[(col >> 4) & 3]; 
                UPDATE_T();
                col = charTable[1]; 
                dstBitmap[6]  = emuPalette[(col >> 2) & 3];
                dstBitmap[7]  = emuPalette[(col >> 0) & 3]; 
                UPDATE_T();
                col = charTable[2]; 
                dstBitmap[8]  = emuPalette[(col >> 6) & 3];
                dstBitmap[9]  = emuPalette[(col >> 4) & 3]; 
                UPDATE_T();
                col = charTable[2]; 
                dstBitmap[10] = emuPalette[(col >> 2) & 3];
                dstBitmap[11] = emuPalette[(col >> 0) & 3]; 
                UPDATE_T();
                col = charTable[3]; 
                dstBitmap[12] = emuPalette[(col >> 6) & 3]; 
                dstBitmap[13] = emuPalette[(col >> 4) & 3]; 
                UPDATE_T();
                col = charTable[3]; 
                dstBitmap[14] = emuPalette[(col >> 2) & 3];
                dstBitmap[15] = emuPalette[(col >> 0) & 3]; 
                UPDATE_T();
            }
        }
    #undef UPDATE_T

        dstBitmap += 16; 
        charTable += 4;
        X++;
    }

    if (rightBorder) {
        RefreshRightBorder(vdp, Y, emuPalette[vdp->BGColor & 0x03], 1, 0);
    }
}

static void RefreshLine7(VDP* vdp, int Y, int X, int X2)
{
    static int     jumpTable[] = { -128, -128, -0x8080, 0x7f80 };
    static UInt32* dstBitmap = NULL;
    static UInt8*  charTable;
    static UInt8*  sprLine = emptylineBuf;
    static int     hScroll512;
    static int     page;
    static int*    jump;
    static int     scroll;
    static int     vscroll;
    static int     chrTabO;
    int col;
    int rightBorder;

    if (X == 0) {
        dstBitmap = RefreshBorder(vdp, Y, emuPalette[vdp->BGColor], 1, 0);
        sprLine = colorSpritesLine(vdp, Y);
        if (dstBitmap == NULL) {
            return;
        }
        
        hScroll512 = vdpHScroll512(vdp);
        jump       = jumpTable + hScroll512 * 2;
        page    = (vdp->chrTabBase / 0x8000) & 1;
        scroll     = vdpHScroll(vdp);
        vscroll    = vdpVScroll(vdp);
        chrTabO    = vdp->chrTabBase;

        charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll / 2;

#define UPDATE_T() if ((++scroll & 0xff) == 0) charTable += jump[page ^= 1];

        if (hScroll512) {
            if (scroll & 0x100) charTable += jump[page ^= 1];
            if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
        }

        if (vdpIsEdgeMasked(vdp->vdpRegs)) {
            UInt32 bgColor = emuPalette[vdp->BGColor];
            dstBitmap[0]  = dstBitmap[1]  = bgColor; 
            dstBitmap[2]  = dstBitmap[3]  = bgColor; 
            dstBitmap[4]  = dstBitmap[5]  = bgColor; 
            dstBitmap[6]  = dstBitmap[7]  = bgColor; 
            dstBitmap[8]  = dstBitmap[9]  = bgColor; 
            dstBitmap[10] = dstBitmap[11] = bgColor; 
            dstBitmap[12] = dstBitmap[13] = bgColor; 
            dstBitmap[14] = dstBitmap[15] = bgColor; 
            UPDATE_T(); UPDATE_T(); UPDATE_T(); UPDATE_T();
            UPDATE_T(); UPDATE_T(); UPDATE_T(); UPDATE_T();
            sprLine   += sprLine != NULL ? 8 : 0;
            dstBitmap += 16; 
            charTable += 4;
            X++; 
        }
    }

    if (dstBitmap == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

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

        if (sprLine != NULL) {
            if (scroll & 1) {
                (col = sprLine[0]) ? dstBitmap[0]  = dstBitmap[1]  = emuPalette[col >> 1] : 
                (col = charTable[vdp->vram128], 
                dstBitmap[0]  = emuPalette[col >> 4],
                dstBitmap[1]  = emuPalette[col & 0xf]);
                UPDATE_T();
                (col = sprLine[1]) ? dstBitmap[2]  = dstBitmap[3]  = emuPalette[col >> 1] :
                (col = charTable[1],  
                dstBitmap[2]  = emuPalette[col >> 4],
                dstBitmap[3]  = emuPalette[col & 0xf]); 
                UPDATE_T();
                (col = sprLine[2]) ? dstBitmap[4]  = dstBitmap[5]  = emuPalette[col >> 1] : 
                (col = charTable[vdp->vram128|1],
                dstBitmap[4]  = emuPalette[col >> 4],
                dstBitmap[5]  = emuPalette[col & 0xf]);
                UPDATE_T();
                (col = sprLine[3]) ? dstBitmap[6]  = dstBitmap[7]  = emuPalette[col >> 1] : 
                (col = charTable[2],   
                dstBitmap[6]  = emuPalette[col >> 4],
                dstBitmap[7]  = emuPalette[col & 0xf]); 
                UPDATE_T();
                (col = sprLine[4]) ? dstBitmap[8]  = dstBitmap[9]  = emuPalette[col >> 1] :
                (col = charTable[vdp->vram128|2], 
                dstBitmap[8]  = emuPalette[col >> 4], 
                dstBitmap[9]  = emuPalette[col & 0xf]);
                UPDATE_T();
                (col = sprLine[5]) ? dstBitmap[10] = dstBitmap[11] = emuPalette[col >> 1] : 
                (col = charTable[3],      
                dstBitmap[10] = emuPalette[col >> 4],
                dstBitmap[11] = emuPalette[col & 0xf]); 
                UPDATE_T();
                (col = sprLine[6]) ? dstBitmap[12] = dstBitmap[13] = emuPalette[col >> 1] : 
                (col = charTable[vdp->vram128|3], 
                dstBitmap[12] = emuPalette[col >> 4], 
                dstBitmap[13] = emuPalette[col & 0xf]);
                UPDATE_T();
                (col = sprLine[7]) ? dstBitmap[14] = dstBitmap[15] = emuPalette[col >> 1] : 
                (col = charTable[4],  
                dstBitmap[14] = emuPalette[col >> 4], 
                dstBitmap[15] = emuPalette[col & 0xf]); 
                UPDATE_T();
            }
            else {
                (col = sprLine[0]) ? dstBitmap[0]  = dstBitmap[1]  = emuPalette[col >> 1] : 
                (col = charTable[0],      
                dstBitmap[0]  = emuPalette[col >> 4],
                dstBitmap[1]  = emuPalette[col & 0xf]);
                UPDATE_T();
                (col = sprLine[1]) ? dstBitmap[2]  = dstBitmap[3]  = emuPalette[col >> 1] : 
                (col = charTable[vdp->vram128], 
                dstBitmap[2]  = emuPalette[col >> 4],
                dstBitmap[3]  = emuPalette[col & 0xf]);
                UPDATE_T();
                (col = sprLine[2]) ? dstBitmap[4]  = dstBitmap[5]  = emuPalette[col >> 1] :
                (col = charTable[1],    
                dstBitmap[4]  = emuPalette[col >> 4], 
                dstBitmap[5]  = emuPalette[col & 0xf]);
                UPDATE_T();
                (col = sprLine[3]) ? dstBitmap[6]  = dstBitmap[7]  = emuPalette[col >> 1] :
                (col = charTable[vdp->vram128|1],
                dstBitmap[6]  = emuPalette[col >> 4], 
                dstBitmap[7]  = emuPalette[col & 0xf]);
                UPDATE_T();
                (col = sprLine[4]) ? dstBitmap[8]  = dstBitmap[9]  = emuPalette[col >> 1] : 
                (col = charTable[2],      
                dstBitmap[8]  = emuPalette[col >> 4], 
                dstBitmap[9]  = emuPalette[col & 0xf]); 
                UPDATE_T();
                (col = sprLine[5]) ? dstBitmap[10] = dstBitmap[11] = emuPalette[col >> 1] :
                (col = charTable[vdp->vram128|2], 
                dstBitmap[10] = emuPalette[col >> 4], 
                dstBitmap[11] = emuPalette[col & 0xf]); 
                UPDATE_T();
                (col = sprLine[6]) ? dstBitmap[12] = dstBitmap[13] = emuPalette[col >> 1] : 
                (col = charTable[3],   
                dstBitmap[12] = emuPalette[col >> 4], 
                dstBitmap[13] = emuPalette[col & 0xf]); 
                UPDATE_T();
                (col = sprLine[7]) ? dstBitmap[14] = dstBitmap[15] = emuPalette[col >> 1] : 
                (col = charTable[vdp->vram128|3], 
                dstBitmap[14] = emuPalette[col >> 4], 
                dstBitmap[15] = emuPalette[col & 0xf]); 
                UPDATE_T();
            }
            sprLine += 8; 
        }
        else {
            if (scroll & 1) {
                col = charTable[vdp->vram128];  
                dstBitmap[0]  = emuPalette[col >> 4]; 
                dstBitmap[1]  = emuPalette[col & 0xf];
                UPDATE_T();
                col = charTable[1];
                dstBitmap[2]  = emuPalette[col >> 4]; 
                dstBitmap[3]  = emuPalette[col & 0xf];
                UPDATE_T();
                col = charTable[vdp->vram128|1];
                dstBitmap[4]  = emuPalette[col >> 4];
                dstBitmap[5]  = emuPalette[col & 0xf];
                UPDATE_T();
                col = charTable[2];
                dstBitmap[6]  = emuPalette[col >> 4];
                dstBitmap[7]  = emuPalette[col & 0xf]; 
                UPDATE_T();
                col = charTable[vdp->vram128|2];
                dstBitmap[8]  = emuPalette[col >> 4]; 
                dstBitmap[9]  = emuPalette[col & 0xf]; 
                UPDATE_T();
                col = charTable[3];
                dstBitmap[10] = emuPalette[col >> 4]; 
                dstBitmap[11] = emuPalette[col & 0xf];
                UPDATE_T();
                col = charTable[vdp->vram128|3];
                dstBitmap[12] = emuPalette[col >> 4]; 
                dstBitmap[13] = emuPalette[col & 0xf];
                UPDATE_T();
                col = charTable[4];
                dstBitmap[14] = emuPalette[col >> 4]; 
                dstBitmap[15] = emuPalette[col & 0xf];
                UPDATE_T();
            }
            else {
                col = charTable[0];
                dstBitmap[0]  = emuPalette[col >> 4];
                dstBitmap[1]  = emuPalette[col & 0xf];
                UPDATE_T();
                col = charTable[vdp->vram128];
                dstBitmap[2]  = emuPalette[col >> 4];
                dstBitmap[3]  = emuPalette[col & 0xf];
                UPDATE_T();
                col = charTable[1];
                dstBitmap[4]  = emuPalette[col >> 4];
                dstBitmap[5]  = emuPalette[col & 0xf];
                UPDATE_T();
                col = charTable[vdp->vram128|1];
                dstBitmap[6]  = emuPalette[col >> 4];
                dstBitmap[7]  = emuPalette[col & 0xf];
                UPDATE_T();
                col = charTable[2];
                dstBitmap[8]  = emuPalette[col >> 4];
                dstBitmap[9]  = emuPalette[col & 0xf]; 
                UPDATE_T();
                col = charTable[vdp->vram128|2];
                dstBitmap[10] = emuPalette[col >> 4];
                dstBitmap[11] = emuPalette[col & 0xf]; 
                UPDATE_T();
                col = charTable[3];
                dstBitmap[12] = emuPalette[col >> 4];
                dstBitmap[13] = emuPalette[col & 0xf];
                UPDATE_T();
                col = charTable[vdp->vram128|3];
                dstBitmap[14] = emuPalette[col >> 4];
                dstBitmap[15] = emuPalette[col & 0xf];
                UPDATE_T();
            }
        }
    #undef UPDATE_T

        dstBitmap += 16; 
        charTable += 4;
        X++;
    }
    
    if (rightBorder) {
        RefreshRightBorder(vdp, Y, emuPalette[vdp->BGColor], 1, 0);
    }
}

static void RefreshLine8(VDP* vdp, int Y, int X, int X2)
{
    static UInt8   SprToScr[16] = { 
        0x00, 0x02, 0x10, 0x12, 0x80, 0x82, 0x90, 0x92, 
        0x49, 0x4B, 0x59, 0x5B, 0xC9, 0xCB, 0xD9, 0xDB 
    };
    static int     jumpTable[] = { -128, -128, -0x8080, 0x7f80 };
    static UInt32* dstBitmap = NULL;
    static UInt8*  charTable;
    static UInt8*  sprLine = emptylineBuf;
    static int     hScroll;
    static int     hScroll512;
    static int*    jump;
    static int     page;
    static int     scroll;
    static int     vscroll;
    static int     chrTabO;
    int col;
    int rightBorder;

    if (X == 0) {
        dstBitmap = RefreshBorder(vdp, Y, emuFixedPalette[vdp->vdpRegs[7]], 0, 0);
        sprLine = colorSpritesLine(vdp, Y);
        if (dstBitmap == NULL) {
            return;
        }
        
        hScroll    = vdpHScroll(vdp);
        hScroll512 = vdpHScroll512(vdp);
        jump       = jumpTable + hScroll512 * 2;
        page    = (vdp->chrTabBase / 0x8000) & 1;
        scroll     = hScroll;
        vscroll    = vdpVScroll(vdp);
        chrTabO    = vdp->chrTabBase;

        charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll / 2;

#define UPDATE_T() if ((++scroll & 0xff) == 0) charTable += jump[page ^= 1];

        if (hScroll512) {
            if (scroll & 0x100) charTable += jump[page ^= 1];
            if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
        }

        if (vdpIsEdgeMasked(vdp->vdpRegs)) {
            UInt32 bgColor = emuFixedPalette[vdp->BGColor];
            dstBitmap[0] = bgColor;
            dstBitmap[1] = bgColor;
            dstBitmap[2] = bgColor;
            dstBitmap[3] = bgColor;
            dstBitmap[4] = bgColor;
            dstBitmap[5] = bgColor;
            dstBitmap[6] = bgColor;
            dstBitmap[7] = bgColor;
            UPDATE_T(); UPDATE_T(); UPDATE_T(); UPDATE_T();
            UPDATE_T(); UPDATE_T(); UPDATE_T(); UPDATE_T();
            sprLine   += sprLine != NULL ? 8 : 0; 
            charTable += 4;
            dstBitmap += 8; 
            X++; 
        }
    }

    if (dstBitmap == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

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
        if (sprLine != NULL) {
            if (scroll & 1) {
                col = sprLine[0]; dstBitmap[0] = col ? emuFixedSpritePalette[col >> 1] : 
            emuFixedPalette[charTable[vdp->vram128]]; UPDATE_T();
                col = sprLine[1]; dstBitmap[1] = col ? emuFixedSpritePalette[col >> 1] : 
                emuFixedPalette[charTable[1]]; UPDATE_T();
                col = sprLine[2]; dstBitmap[2] = col ? emuFixedSpritePalette[col >> 1] : 
                emuFixedPalette[charTable[vdp->vram128|1]]; UPDATE_T();
                col = sprLine[3]; dstBitmap[3] = col ? emuFixedSpritePalette[col >> 1] : 
                emuFixedPalette[charTable[2]]; UPDATE_T();
                col = sprLine[4]; dstBitmap[4] = col ? emuFixedSpritePalette[col >> 1] : 
                emuFixedPalette[charTable[vdp->vram128|2]]; UPDATE_T();
                col = sprLine[5]; dstBitmap[5] = col ? emuFixedSpritePalette[col >> 1] : 
                emuFixedPalette[charTable[3]]; UPDATE_T();
                col = sprLine[6]; dstBitmap[6] = col ? emuFixedSpritePalette[col >> 1] : 
                emuFixedPalette[charTable[vdp->vram128|3]]; UPDATE_T();
                col = sprLine[7]; dstBitmap[7] = col ? emuFixedSpritePalette[col >> 1] : 
                emuFixedPalette[charTable[4]]; UPDATE_T();
            }
            else {
                col = sprLine[0]; dstBitmap[0] = col ? emuFixedSpritePalette[col >> 1] : 
            emuFixedPalette[charTable[0]]; UPDATE_T();
                col = sprLine[1]; dstBitmap[1] = col ? emuFixedSpritePalette[col >> 1] : 
                emuFixedPalette[charTable[vdp->vram128]]; UPDATE_T();
                col = sprLine[2]; dstBitmap[2] = col ? emuFixedSpritePalette[col >> 1] : 
                emuFixedPalette[charTable[1]]; UPDATE_T();
                col = sprLine[3]; dstBitmap[3] = col ? emuFixedSpritePalette[col >> 1] : 
                emuFixedPalette[charTable[vdp->vram128|1]]; UPDATE_T();
                col = sprLine[4]; dstBitmap[4] = col ? emuFixedSpritePalette[col >> 1] : 
                emuFixedPalette[charTable[2]]; UPDATE_T();
                col = sprLine[5]; dstBitmap[5] = col ? emuFixedSpritePalette[col >> 1] : 
                emuFixedPalette[charTable[vdp->vram128|2]]; UPDATE_T();
                col = sprLine[6]; dstBitmap[6] = col ? emuFixedSpritePalette[col >> 1] : 
                emuFixedPalette[charTable[3]]; UPDATE_T();
                col = sprLine[7]; dstBitmap[7] = col ? emuFixedSpritePalette[col >> 1] : 
                emuFixedPalette[charTable[vdp->vram128|3]]; UPDATE_T();
            }
            sprLine += 8; 
        }
        else {
            if (scroll & 1) {
                dstBitmap[0] = emuFixedPalette[charTable[vdp->vram128]];   UPDATE_T();
                dstBitmap[1] = emuFixedPalette[charTable[1]];         UPDATE_T();
                dstBitmap[2] = emuFixedPalette[charTable[vdp->vram128|1]]; UPDATE_T();
                dstBitmap[3] = emuFixedPalette[charTable[2]];         UPDATE_T();
                dstBitmap[4] = emuFixedPalette[charTable[vdp->vram128|2]]; UPDATE_T();
                dstBitmap[5] = emuFixedPalette[charTable[3]];         UPDATE_T();
                dstBitmap[6] = emuFixedPalette[charTable[vdp->vram128|3]]; UPDATE_T();
                dstBitmap[7] = emuFixedPalette[charTable[4]];         UPDATE_T();
            }
            else {
                dstBitmap[0] = emuFixedPalette[charTable[0]];         UPDATE_T();
                dstBitmap[1] = emuFixedPalette[charTable[vdp->vram128]];   UPDATE_T();
                dstBitmap[2] = emuFixedPalette[charTable[1]];         UPDATE_T();
                dstBitmap[3] = emuFixedPalette[charTable[vdp->vram128|1]]; UPDATE_T();
                dstBitmap[4] = emuFixedPalette[charTable[2]];         UPDATE_T();
                dstBitmap[5] = emuFixedPalette[charTable[vdp->vram128|2]]; UPDATE_T();
                dstBitmap[6] = emuFixedPalette[charTable[3]];         UPDATE_T();
                dstBitmap[7] = emuFixedPalette[charTable[vdp->vram128|3]]; UPDATE_T();
            }
        }
    #undef UPDATE_T

        charTable += 4; dstBitmap += 8; X++;
    }

    if (rightBorder) {
        RefreshRightBorder(vdp, Y, emuFixedPalette[vdp->vdpRegs[7]], 0, 0);
    }
}

static void RefreshLine10(VDP* vdp, int Y, int X, int X2)
{
    static int jumpTable[] = { -128, -128, -0x8080, 0x7f80 };
    static UInt32* dstBitmap = NULL;
    static UInt8* charTable;
    static UInt8* sprLine = emptylineBuf;
    static int hScroll512;
    static int* jump;
    static int page;
    static int scroll;
    static int vscroll;
    static int chrTabO;
    UInt8 t0, t1, t2, t3;
    int y, J,K;
    int col;
    int rightBorder;

    if (X == 0) {
        dstBitmap = RefreshBorder(vdp, Y,  emuFixedPalette[vdp->vdpRegs[7]], 0, 0);
        sprLine = colorSpritesLine(vdp, Y);
        if (dstBitmap == NULL) {
            return;
        }
        
        hScroll512 = vdpHScroll512(vdp);
        jump       = jumpTable + hScroll512 * 2;
        page    = (vdp->chrTabBase / 0x8000) & 1;
        scroll     = vdpHScroll(vdp) & ~3;
        vscroll    = vdpVScroll(vdp);
        chrTabO    = vdp->chrTabBase;

        charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll / 2;

#define UPDATE_T() if ((++scroll & 0xff) == 0) charTable += jump[page ^= 1];

        if (hScroll512) {
            if (scroll & 0x100) charTable += jump[page ^= 1];
            if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
        }

        if (vdpIsEdgeMasked(vdp->vdpRegs)) {
            UInt32 bgColor = emuFixedPalette[vdp->vdpRegs[7]];
            dstBitmap[0] = bgColor;
            dstBitmap[1] = bgColor;
            dstBitmap[2] = bgColor;
            dstBitmap[3] = bgColor;
            dstBitmap[4] = bgColor;
            dstBitmap[5] = bgColor;
            dstBitmap[6] = bgColor;
            dstBitmap[7] = bgColor;
            UPDATE_T(); UPDATE_T(); UPDATE_T(); UPDATE_T();
            UPDATE_T(); UPDATE_T(); UPDATE_T(); UPDATE_T();
            sprLine += sprLine != NULL ? 8 : 0; 
            charTable += 4; 
            dstBitmap += 8;
            X++; 
        }

        if (X > 0) {
            return;
        }

        t0 = charTable[0];        UPDATE_T();
        t1 = charTable[vdp->vram128];  UPDATE_T();
        t2 = charTable[1];        UPDATE_T();
        t3 = charTable[vdp->vram128|1];  UPDATE_T();

        K = (t0 & 0x07) | ((t1 & 0x07) << 3);
        J = (t2 & 0x07) | ((t3 & 0x07) << 3);

        if (sprLine != NULL) {
            switch (vdpHScroll(vdp) & 3) {
            case 0:
                col = sprLine[0]; y = t0 >> 3; *dstBitmap++ = col ? emuPalette[col >> 1] : 
                y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
            case 1:
                col = sprLine[1]; y = t1 >> 3; *dstBitmap++ = col ? emuPalette[col >> 1] : 
                y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
            case 2:
                col = sprLine[2]; y = t2 >> 3; *dstBitmap++ = col ? emuPalette[col >> 1] : 
                y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
            case 3:
                col = sprLine[3]; y = t3 >> 3; *dstBitmap++ = col ? emuPalette[col >> 1] : 
                y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
            }
            sprLine += 4;
        }
        else {
            switch (vdpHScroll(vdp) & 3) {
            case 0:
                y = t0 >> 3; *dstBitmap++ = y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
            case 1:
                y = t1 >> 3; *dstBitmap++ = y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
            case 2:
                y = t2 >> 3; *dstBitmap++ = y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
            case 3:
                y = t3 >> 3; *dstBitmap++ = y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
            }
        }
        charTable += 2; 
    }

    if (dstBitmap == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

    // Update vscroll if needed
    if (vscroll != vdpVScroll(vdp) || chrTabO != vdp->chrTabBase) {
        scroll = vdpHScroll(vdp) + X * 8;
        jump   = jumpTable + hScroll512 * 2;
        vscroll = vdpVScroll(vdp);
        chrTabO  = vdp->chrTabBase;

        charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll / 2;
        charTable += 2; 

        if (vdpIsOddPage(vdp)) charTable += jump[2 | (page ^= 1)] + 128;

        if (hScroll512) {
            if (scroll & 0x100) charTable += jump[page ^= 1];
            if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
        }
    }

    while (X < X2) {
        t0 = charTable[0];         UPDATE_T();
        t1 = charTable[vdp->vram128];   UPDATE_T();
        t2 = charTable[1];         UPDATE_T();
        t3 = charTable[vdp->vram128|1]; UPDATE_T();

        K = (t0 & 0x07) | ((t1 & 0x07) << 3);
        J = (t2 & 0x07) | ((t3 & 0x07) << 3);

        if (sprLine != NULL) {
            col = sprLine[0]; y = t0 >> 3; dstBitmap[0] = col ? emuPalette[col >> 1] : 
        y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
            col = sprLine[1]; y = t1 >> 3; dstBitmap[1] = col ? emuPalette[col >> 1] : 
        y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
            col = sprLine[2]; y = t2 >> 3; dstBitmap[2] = col ? emuPalette[col >> 1] : 
        y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
            col = sprLine[3]; y = t3 >> 3; dstBitmap[3] = col ? emuPalette[col >> 1] : 
        y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
        }
        else {
            y = t0 >> 3; dstBitmap[0] = y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
            y = t1 >> 3; dstBitmap[1] = y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
            y = t2 >> 3; dstBitmap[2] = y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
            y = t3 >> 3; dstBitmap[3] = y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
        }

        t0 = charTable[2];         UPDATE_T();
        t1 = charTable[vdp->vram128|2]; UPDATE_T();
        t2 = charTable[3];         UPDATE_T();
        t3 = charTable[vdp->vram128|3]; UPDATE_T();

        K = (t0 & 0x07) | ((t1 & 0x07) << 3);
        J = (t2 & 0x07) | ((t3 & 0x07) << 3);

        if (X == 31) {
            if (sprLine != NULL) {
                switch (vdpHScroll(vdp) & 3) {
                case 1:
                    col = sprLine[6]; y = t2 >> 3; dstBitmap[6] = col ? emuPalette[col >> 1] : 
                    y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
                case 2:
                    col = sprLine[5]; y = t1 >> 3; dstBitmap[5] = col ? emuPalette[col >> 1] : 
                    y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
                case 3:
                    col = sprLine[4]; y = t0 >> 3; dstBitmap[4] = col ? emuPalette[col >> 1] : 
                    y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
                }
            }
            else {
                switch (vdpHScroll(vdp) & 3) {
                case 1:
                    y = t2 >> 3; dstBitmap[6] = y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
                case 2:
                    y = t1 >> 3; dstBitmap[5] = y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
                case 3:
                    y = t0 >> 3; dstBitmap[4] = y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
                }
            }
        }
        else {
            if (sprLine != NULL) {
                col = sprLine[4]; y = t0 >> 3; dstBitmap[4] = col ? 
                    emuPalette[col >> 1] : y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
                col = sprLine[5]; y = t1 >> 3; dstBitmap[5] = col ? 
                    emuPalette[col >> 1] : y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
                col = sprLine[6]; y = t2 >> 3; dstBitmap[6] = col ? 
                    emuPalette[col >> 1] : y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
                col = sprLine[7]; y = t3 >> 3; dstBitmap[7] = col ? 
                    emuPalette[col >> 1] : y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
                sprLine += 8; 
            }
            else {
                y = t0 >> 3; dstBitmap[4] = y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
                y = t1 >> 3; dstBitmap[5] = y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
                y = t2 >> 3; dstBitmap[6] = y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
                y = t3 >> 3; dstBitmap[7] = y & 1 ? emuPalette[y >> 1] : YJKColor(y, J, K);
            }
        }
    #undef UPDATE_T

        charTable += 4; dstBitmap += 8; X++;
    }

    if (rightBorder) {
        RefreshRightBorder(vdp, Y, emuFixedPalette[vdp->vdpRegs[7]], 0, 0);
    }
}

static void RefreshLine12(VDP* vdp, int Y, int X, int X2)
{
    static int jumpTable[] = { -128, -128, -0x8080, 0x7f80 };
    static UInt32* dstBitmap = NULL;
    static UInt8* charTable;
    static UInt8* sprLine = emptylineBuf;
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

    if (X == 0) {
        dstBitmap = RefreshBorder(vdp, Y, emuFixedPalette[vdp->vdpRegs[7]], 0, 0);
        sprLine = colorSpritesLine(vdp, Y);
        if (dstBitmap == NULL) {
            return;
        }
        
        hScroll512 = vdpHScroll512(vdp);
        jump       = jumpTable + hScroll512 * 2;
        page    = (vdp->chrTabBase / 0x8000) & 1;
        hscroll    = vdpHScroll(vdp);
        scroll     = hscroll & ~3;
        vscroll    = vdpVScroll(vdp);
        chrTabO    = vdp->chrTabBase;

        charTable = vdp->vram + (vdp->chrTabBase & (~vdpIsOddPage(vdp) << 7) & ((-1 << 15) | ((Y - vdp->firstLine + vdpVScroll(vdp)) << 7))) + scroll / 2;

#define UPDATE_T() if ((++scroll & 0xff) == 0) charTable += jump[page ^= 1];

        if (hScroll512) {
            if (scroll & 0x100) charTable += jump[page ^= 1];
            if (vdp->chrTabBase & (1 << 15)) charTable += jump[page ^= 1] + 128;
        }

        if (vdpIsEdgeMasked(vdp->vdpRegs)) {
            UInt32 bgColor = emuFixedPalette[vdp->vdpRegs[7]];
            dstBitmap[0] = bgColor;
            dstBitmap[1] = bgColor;
            dstBitmap[2] = bgColor;
            dstBitmap[3] = bgColor;
            dstBitmap[4] = bgColor;
            dstBitmap[5] = bgColor;
            dstBitmap[6] = bgColor;
            dstBitmap[7] = bgColor;
            UPDATE_T(); UPDATE_T(); UPDATE_T(); UPDATE_T();
            UPDATE_T(); UPDATE_T(); UPDATE_T(); UPDATE_T();
            sprLine   += sprLine != NULL ? 8 : 0; 
            charTable += 4; 
            dstBitmap += 8;
            X++; 
        }

        t0 = charTable[0];        UPDATE_T();
        t1 = charTable[vdp->vram128];  UPDATE_T();
        t2 = charTable[1];        UPDATE_T();
        t3 = charTable[vdp->vram128|1];  UPDATE_T();

        K=(t0 & 0x07) | ((t1 & 0x07) << 3);
        J=(t2 & 0x07) | ((t3 & 0x07) << 3);

        if (sprLine != NULL) {
            switch (hscroll & 3) {
            case 0:
                col = sprLine[0]; *dstBitmap++ = col ? emuPalette[col >> 1] : YJKColor(t0 >> 3, J, K);
            case 1:
                col = sprLine[1]; *dstBitmap++ = col ? emuPalette[col >> 1] : YJKColor(t1 >> 3, J, K);
            case 2:
                col = sprLine[2]; *dstBitmap++ = col ? emuPalette[col >> 1] : YJKColor(t2 >> 3, J, K);
            case 3:
                col = sprLine[3]; *dstBitmap++ = col ? emuPalette[col >> 1] : YJKColor(t3 >> 3, J, K);
            }
            sprLine += 4;
        }
        else {
            switch (hscroll & 3) {
            case 0:
                *dstBitmap++ = YJKColor(t0 >> 3, J, K);
            case 1:
                *dstBitmap++ = YJKColor(t1 >> 3, J, K);
            case 2:
                *dstBitmap++ = YJKColor(t2 >> 3, J, K);
            case 3:
                *dstBitmap++ = YJKColor(t3 >> 3, J, K);
            }
        }
        charTable += 2;
    }

    if (dstBitmap == NULL) {
        return;
    }

    rightBorder = X2 == 33;
    if (rightBorder) {
        X2--;
    }

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
        t0 = charTable[0];         UPDATE_T();
        t1 = charTable[vdp->vram128];   UPDATE_T();
        t2 = charTable[1];         UPDATE_T();
        t3 = charTable[vdp->vram128|1]; UPDATE_T();

        K=(t0 & 0x07) | ((t1 & 0x07) << 3);
        J=(t2 & 0x07) | ((t3 & 0x07) << 3);

        if (sprLine != NULL) {
            col = sprLine[0]; dstBitmap[0] = col ? emuPalette[col >> 1] : YJKColor(t0 >> 3, J, K);
            col = sprLine[1]; dstBitmap[1] = col ? emuPalette[col >> 1] : YJKColor(t1 >> 3, J, K);
            col = sprLine[2]; dstBitmap[2] = col ? emuPalette[col >> 1] : YJKColor(t2 >> 3, J, K);
            col = sprLine[3]; dstBitmap[3] = col ? emuPalette[col >> 1] : YJKColor(t3 >> 3, J, K);
        }
        else {
            dstBitmap[0] = YJKColor(t0 >> 3, J, K);
            dstBitmap[1] = YJKColor(t1 >> 3, J, K);
            dstBitmap[2] = YJKColor(t2 >> 3, J, K);
            dstBitmap[3] = YJKColor(t3 >> 3, J, K);
        }

        t0 = charTable[2];        UPDATE_T();
        t1 = charTable[vdp->vram128|2];  UPDATE_T();
        t2 = charTable[3];        UPDATE_T();
        t3 = charTable[vdp->vram128|3];  UPDATE_T();

        K=(t0 & 0x07) | ((t1 & 0x07) << 3);
        J=(t2 & 0x07) | ((t3 & 0x07) << 3);

        if (X == 31) {
            if (sprLine != NULL) {
                switch (hscroll & 3) {
                case 1:
                    col = sprLine[6]; dstBitmap[6] = col ? emuPalette[col >> 1] : YJKColor(t2 >> 3, J, K);
                case 2:
                    col = sprLine[5]; dstBitmap[5] = col ? emuPalette[col >> 1] : YJKColor(t1 >> 3, J, K);
                case 3:
                    col = sprLine[4]; dstBitmap[4] = col ? emuPalette[col >> 1] : YJKColor(t0 >> 3, J, K);
                }
            }
            else {
                switch (hscroll & 3) {
                case 1:
                    dstBitmap[6] = YJKColor(t2 >> 3, J, K);
                case 2:
                    dstBitmap[5] = YJKColor(t1 >> 3, J, K);
                case 3:
                    dstBitmap[4] = YJKColor(t0 >> 3, J, K);
                }
            }
        }
        else {
            if (sprLine != NULL) {
                col = sprLine[4]; dstBitmap[4] = col ? emuPalette[col >> 1] : YJKColor(t0 >> 3, J, K);
                col = sprLine[5]; dstBitmap[5] = col ? emuPalette[col >> 1] : YJKColor(t1 >> 3, J, K);
                col = sprLine[6]; dstBitmap[6] = col ? emuPalette[col >> 1] : YJKColor(t2 >> 3, J, K);
                col = sprLine[7]; dstBitmap[7] = col ? emuPalette[col >> 1] : YJKColor(t3 >> 3, J, K);
                sprLine += 8; 
            }
            else {
                dstBitmap[4] = YJKColor(t0 >> 3, J, K);
                dstBitmap[5] = YJKColor(t1 >> 3, J, K);
                dstBitmap[6] = YJKColor(t2 >> 3, J, K);
                dstBitmap[7] = YJKColor(t3 >> 3, J, K);
            }
        }
    #undef UPDATE_T

        charTable += 4; dstBitmap += 8;
        X++;
    }

    if (rightBorder) {
        RefreshRightBorder(vdp, Y, emuFixedPalette[vdp->vdpRegs[7]], 0, 0);
    }
}
