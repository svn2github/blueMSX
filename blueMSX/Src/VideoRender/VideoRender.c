/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoRender/VideoRender.c,v $
**
** $Revision: 1.10 $
**
** $Date: 2005-01-22 03:20:02 $
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
#include "videoRender.h"
#include "FrameBuffer.h"
#include "Emulator.h"
#include "scalebit.h"
#include "Hq2x.h"
#include <stdlib.h>
#include <math.h>
#include <memory.h>
 
#define YCBCR_MASK 0x1F7DF
#define MAX_YCBCR_VALUE (1 << 17)

static UInt32 pRgbTableColor32[MAX_YCBCR_VALUE];
static UInt32 pRgbTableGreen32[MAX_YCBCR_VALUE];
static UInt32 pRgbTableWhite32[MAX_YCBCR_VALUE];
static UInt32 pRgbTableAmber32[MAX_YCBCR_VALUE];
static UInt16 pRgbTableColor16[MAX_YCBCR_VALUE];
static UInt16 pRgbTableGreen16[MAX_YCBCR_VALUE];
static UInt16 pRgbTableWhite16[MAX_YCBCR_VALUE];
static UInt16 pRgbTableAmber16[MAX_YCBCR_VALUE];

UInt32 YJKtoYCbCrTable[32][64][64];

static int initialized = 0;

#define ABS(a) ((a) < 0 ? -1 * (a) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

static void initYJKtoYCbCrTable() {
    int y;
    int J;
    int K;

    for (y = 0; y < 32; y++) {
        for (J = 0; J < 64; J++) {
            for (K = 0; K < 64; K++) {
		        int j = (J & 0x1f) - (J & 0x20);
		        int k = (K & 0x1f) - (K & 0x20);
			    int r = 255 * (y + j) / 31;
			    int g = 255 * (y + k) / 31;
			    int b = 255 * ((5 * y - 2 * j - k) / 4) / 31;

                r = MIN(255, MAX(0, r));
                g = MIN(255, MAX(0, g));
                b = MIN(255, MAX(0, b));
                YJKtoYCbCrTable[y][J][K] = videoGetColor(r, g, b);
            }
        }
    }
}

static int gammaTable[3 * 256];
static int deInterlace = 0;
static void generateGammaTable(Video* pVideo)
{
    int i;
    for (i = 0; i < 3 * 256; i++) {
        double value = (i - 256 + pVideo->brightness) * pVideo->contrast;
        gammaTable[i] = 6;
        if (value > 0) {
            double factor = pow(255., pVideo->gamma - 1.);
            value = (double)(factor * pow(value, pVideo->gamma));
            if (value > 0) {
                int gamma = (int)value;
                gammaTable[i] = MAX(6, MIN(247, gamma));
            }
        }
    }
}

#define videoGamma(index) gammaTable[index + 256]

static void initRGBTable(Video* pVideo) 
{
    int YCbCr;

    generateGammaTable(pVideo);

    for (YCbCr = 0; YCbCr < MAX_YCBCR_VALUE; YCbCr++) {
        int R = 8 * ((YCbCr >> 12) & 0x01f);
        int G = 8 * ((YCbCr >> 6) & 0x01f);
        int B = 8 * ((YCbCr >> 0) & 0x01f);
        int L = 0;

        int Y  = (int)(0.2989*R + 0.5866*G + 0.1145*B);
        int Cb = B - Y;
        int Cr = R - Y;

        if (pVideo->saturation < 0.999 || pVideo->saturation > 1.001) {
            Cb = (int)(Cb * pVideo->saturation);
            Cr = (int)(Cr * pVideo->saturation);
            Y  = MAX(0, MIN(255, Y));
            Cb = MAX(-256, MIN(255, Cb));
            Cr = MAX(-256, MIN(255, Cr));
            R = Cr + Y;
            G = (int)(Y - (0.1145/0.5866)*Cb - (0.2989/0.5866)*Cr);
            B = Cb + Y;
            R = MIN(255, MAX(0, R));
            G = MIN(255, MAX(0, G));
            B = MIN(255, MAX(0, B));
        }

        R = videoGamma(R);
        G = videoGamma(G);
        B = videoGamma(B);
        L = videoGamma(Y);

        pRgbTableColor32[YCbCr] = (R << 16) | (G << 8) | (B << 0);
        pRgbTableColor16[YCbCr] = ((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3);

        pRgbTableGreen32[YCbCr] = 0x100010 | (L << 8);
        pRgbTableGreen16[YCbCr] = 0x0801 | (UInt16)((L >> 2) << 5);

        pRgbTableWhite32[YCbCr] = (L << 16) | (L << 8) | (L << 0);
        pRgbTableWhite16[YCbCr] = (UInt16)(((L >> 3) << 11) | ((L >> 2) << 5) | (L >> 3));

        pRgbTableAmber32[YCbCr] = (L << 16) | ((L * 176 / 255) << 8);
        pRgbTableAmber16[YCbCr] = ((L >> 3) << 11) | (((L * 176 / 255) >> 2) << 5);
    }
}


/*****************************************************************************
**
** PAL emulation rendering routines
**
******************************************************************************
*/
static void copySharpPAL_2x2_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32 rnd, void* pRgbTable)
{
    UInt16* pRgbTable16 = (UInt16*)pRgbTable;
    UInt16* pDst1       = (UInt16*)pDestination;
    UInt16* pDst2       = pDst1 + dstPitch / (int)sizeof(UInt16);
    UInt16* pDst3       = pDst2;
    int height          = frame->lines;
    int h;

    dstPitch /= (int)sizeof(UInt16);

    if (frame->interlaceOdd) {
        pDst1 += dstPitch;
        pDst2 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        int width = frame->line[h].width;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev1 = colCur;
        int dstIndex = 0;

        if (width > 320) {
            int w;
            for (w = 0; w < width;) {
                UInt32 colNext1;
                UInt16 colRgb1;
                UInt16 colRgb2;
                UInt32 colTmp;
                UInt16 noise;

                colNext1 = pSrc[w++];
                colTmp   = ((colNext1   + colPrev1) >> 1) & YCBCR_MASK;
                colTmp   = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                colRgb1  = pRgbTable16[colTmp];

                colPrev1  = colCur;
                colCur    = colNext1;

                colNext1 = pSrc[w++];
                colTmp  = ((colNext1   + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                colRgb2 = pRgbTable16[colTmp];

                colPrev1 = colCur;
                colCur   = colNext1;

                noise = (UInt16)(rnd >> 31) * 0x0821;
                pDst2[dstIndex] = colRgb1 + noise;
                pDst1[dstIndex] = (((pDst3[dstIndex] >> 1) & 0x7bef) + ((colRgb1 >> 1) & 0x7bef));
                dstIndex++;
                pDst2[dstIndex] = colRgb2 + noise;
                pDst1[dstIndex] = (((pDst3[dstIndex] >> 3) & 0x7bef) + ((colRgb2 >> 1) & 0x7bef));
                dstIndex++;

                rnd *= 23;
            }
        }
        else {
            int w;
            for (w = 0; w < width; w++) {
                UInt32 colNext;
                UInt16 colRgb1;
                UInt16 colRgb2;
                UInt32 colTmp;
                UInt16 noise;

                colNext = pSrc[w];
                colTmp  = ((colNext + colCur) >> 1) & YCBCR_MASK;
                colRgb1 = pRgbTable16[((colTmp + colCur) >> 1) & YCBCR_MASK];
                colRgb2 = pRgbTable16[((colTmp + colNext) >> 1) & YCBCR_MASK];

                noise = (UInt16)(rnd >> 31) * 0x0821;
                pDst2[dstIndex] = colRgb1 + noise;
                pDst1[dstIndex] = (((pDst3[dstIndex] >> 1) & 0x7bef) + ((colRgb1 >> 1) & 0x7bef));
                dstIndex++;
                pDst2[dstIndex] = colRgb2 + noise;
                pDst1[dstIndex] = (((pDst3[dstIndex] >> 1) & 0x7bef) + ((colRgb2 >> 1) & 0x7bef));
                dstIndex++;

                rnd *= 23;
                colCur = colNext;
            }
        }

        pDst3 = pDst2;
        pDst1 += dstPitch * 2;
        pDst2 += dstPitch * 2;
    }
}

static void copySharpPAL_2x2_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32 rnd, void* pRgbTable)
{
    UInt32* pRgbTable32 = (UInt32*)pRgbTable;
    UInt32* pDst1       = (UInt32*)pDestination;
    UInt32* pDst2       = pDst1 + dstPitch / (int)sizeof(UInt32);
    UInt32* pDst3       = pDst2;
    int height          = frame->lines;
    int h;

    dstPitch /= (int)sizeof(UInt32);

    if (frame->interlaceOdd) {
        pDst1 += dstPitch;
        pDst2 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        int width = frame->line[h].width;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev1 = colCur;
        int dstIndex = 0;

        if (width > 320) {
            int w;
            for (w = 0; w < width;) {
                UInt32 colNext1;
                UInt32 colRgb1;
                UInt32 colRgb2;
                UInt32 colTmp;
                UInt32 noise;

                colNext1 = pSrc[w++];
                colTmp   = ((colNext1   + colPrev1) >> 1) & YCBCR_MASK;
                colTmp   = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                colRgb1  = pRgbTable32[colTmp];

                colPrev1  = colCur;
                colCur    = colNext1;

                colNext1 = pSrc[w++];
                colTmp  = ((colNext1   + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                colRgb2 = pRgbTable32[colTmp];

                colPrev1 = colCur;
                colCur   = colNext1;

                noise = (rnd >> 29) * 0x10101;
                pDst2[dstIndex] = colRgb1 + noise;
                pDst1[dstIndex] = ((pDst3[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb1 >> 1) & 0x7f7f7f);
                dstIndex++;
                pDst2[dstIndex] = colRgb2 + noise;
                pDst1[dstIndex] = ((pDst3[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb2 >> 1) & 0x7f7f7f);
                dstIndex++;

                rnd *= 23;
            }
        }
        else {
            int w;
            for (w = 0; w < width; w++) {
                UInt32 colNext;
                UInt32 colRgb1;
                UInt32 colRgb2;
                UInt32 colTmp;
                UInt32 noise;

                colNext = pSrc[w];
                colTmp  = ((colNext + colCur) >> 1) & YCBCR_MASK;
                colRgb1 = pRgbTable32[((colTmp + colCur) >> 1) & YCBCR_MASK];
                colRgb2 = pRgbTable32[((colTmp + colNext) >> 1) & YCBCR_MASK];

                noise = (rnd >> 29) * 0x10101;
                pDst2[dstIndex] = colRgb1 + noise;
                pDst1[dstIndex] = ((pDst3[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb1 >> 1) & 0x7f7f7f);
                dstIndex++;
                pDst2[dstIndex] = colRgb2 + noise;
                pDst1[dstIndex] = ((pDst3[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb2 >> 1) & 0x7f7f7f);
                dstIndex++;

                rnd *= 23;
                colCur = colNext;
            }
        }

        pDst3 = pDst2;
        pDst1 += dstPitch * 2;
        pDst2 += dstPitch * 2;
    }
}

static void copyMonitorPAL_2x2_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32 rnd, void* pRgbTable)
{
    UInt16* pRgbTable16 = (UInt16*)pRgbTable;
    UInt16* pDst1       = (UInt16*)pDestination;
    UInt16* pDst2       = pDst1 + dstPitch / (int)sizeof(UInt16);
    UInt16* pDst3       = pDst2;
    int height          = frame->lines;
    int h;

    dstPitch /= (int)sizeof(UInt16);

    if (frame->interlaceOdd) {
        pDst1 += dstPitch;
        pDst2 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        int width = frame->line[h].width;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev1 = colCur;
        int dstIndex = 0;

        if (width > 320) {
            int w;
            for (w = 0; w < width;) {
                UInt32 colNext1;
                UInt16 colRgb1;
                UInt16 colRgb2;
                UInt32 colTmp;
                UInt16 noise;

                colNext1 = pSrc[w++];
                colTmp   = ((colNext1   + colCur) >> 1) & YCBCR_MASK;
                colTmp   = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                colRgb1  = pRgbTable16[colTmp];

                colPrev1  = colCur;
                colCur    = colNext1;

                colNext1 = pSrc[w++];
                colTmp  = ((colNext1   + colCur) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                colRgb2 = pRgbTable16[colTmp];

                colPrev1 = colCur;
                colCur   = colNext1;

                noise = (UInt16)(rnd >> 31) * 0x0821;
                pDst2[dstIndex] = colRgb1 + noise;
                pDst1[dstIndex] = ((pDst3[dstIndex] >> 1) & 0x7bef) + ((colRgb1 >> 1) & 0x7bef);
                pDst1[dstIndex] = ((pDst1[dstIndex] >> 1) & 0x7bef) + ((colRgb1 >> 1) & 0x7bef);
                dstIndex++;
                pDst2[dstIndex] = colRgb2 + noise;
                pDst1[dstIndex] = ((pDst3[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb2 >> 1) & 0x7f7f7f);
                pDst1[dstIndex] = ((pDst1[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb2 >> 1) & 0x7f7f7f);
                dstIndex++;

                rnd *= 23;
            }
        }
        else {
            int w;
            for (w = 0; w < width; w++) {
                UInt32 colNext;
                UInt16 colRgb1;
                UInt16 colRgb2;
                UInt32 colTmp;
                UInt16 noise;

                colNext = pSrc[w];
                colTmp  = ((colNext + colCur) >> 1) & YCBCR_MASK;
                colRgb1 = pRgbTable16[((colTmp + colCur) >> 1) & YCBCR_MASK];
                colRgb2 = pRgbTable16[colNext];

                noise = (UInt16)(rnd >> 31) * 0x0821;
                pDst2[dstIndex] = colRgb1 + noise;
                pDst1[dstIndex] = ((pDst3[dstIndex] >> 1) & 0x7bef) + ((colRgb1 >> 1) & 0x7bef);
                pDst1[dstIndex] = ((pDst1[dstIndex] >> 1) & 0x7bef) + ((colRgb1 >> 1) & 0x7bef);
                dstIndex++;
                pDst2[dstIndex] = colRgb2 + noise;
                pDst1[dstIndex] = ((pDst3[dstIndex] >> 1) & 0x7bef) + ((colRgb2 >> 1) & 0x7bef);
                pDst1[dstIndex] = ((pDst1[dstIndex] >> 1) & 0x7bef) + ((colRgb2 >> 1) & 0x7bef);
                dstIndex++;

                rnd *= 23;
                colCur = colNext;
            }
        }

        pDst3  = pDst2;
        pDst1 += dstPitch * 2;
        pDst2 += dstPitch * 2;
    }
}

static void copyMonitorPAL_2x2_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32 rnd, void* pRgbTable)
{
    UInt32* pRgbTable32 = (UInt32*)pRgbTable;
    UInt32* pDst1       = (UInt32*)pDestination;
    UInt32* pDst2       = pDst1 + dstPitch / (int)sizeof(UInt32);
    UInt32* pDst3       = pDst2;
    int height          = frame->lines;
    int h;

    dstPitch /= (int)sizeof(UInt32);

    if (frame->interlaceOdd) {
        pDst1 += dstPitch;
        pDst2 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        int width = frame->line[h].width;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev1 = colCur;
        int dstIndex = 0;

        if (width > 320) {
            int w;
            for (w = 0; w < width;) {
                UInt32 colNext1;
                UInt32 colRgb1;
                UInt32 colRgb2;
                UInt32 colTmp;
                UInt32 noise;

                colNext1 = pSrc[w++];
                colTmp   = ((colNext1   + colCur) >> 1) & YCBCR_MASK;
                colTmp   = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                colRgb1  = pRgbTable32[colTmp];

                colPrev1  = colCur;
                colCur    = colNext1;

                colNext1 = pSrc[w++];
                colTmp  = ((colNext1   + colCur) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                colRgb2 = pRgbTable32[colTmp];

                colPrev1 = colCur;
                colCur   = colNext1;

                noise = (rnd >> 30) * 0x10101;
                pDst2[dstIndex] = colRgb1 + noise;
                pDst1[dstIndex] = ((pDst3[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb1 >> 1) & 0x7f7f7f);
                pDst1[dstIndex] = ((pDst1[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb1 >> 1) & 0x7f7f7f);
                dstIndex++;
                pDst2[dstIndex] = colRgb2 + noise;
                pDst1[dstIndex] = ((pDst3[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb2 >> 1) & 0x7f7f7f);
                pDst1[dstIndex] = ((pDst1[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb2 >> 1) & 0x7f7f7f);
                dstIndex++;

                rnd *= 23;
            }
        }
        else {
            int w;
            for (w = 0; w < width; w++) {
                UInt32 colNext;
                UInt32 colRgb1;
                UInt32 colRgb2;
                UInt32 colTmp;
                UInt32 noise;

                colNext = pSrc[w];
                colTmp  = ((colNext + colCur) >> 1) & YCBCR_MASK;
                colRgb1 = pRgbTable32[((colTmp + colCur) >> 1) & YCBCR_MASK];
                colRgb2 = pRgbTable32[colNext];

                noise = (rnd >> 30) * 0x10101;
                pDst2[dstIndex] = colRgb1 + noise;
                pDst1[dstIndex] = ((pDst3[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb1 >> 1) & 0x7f7f7f);
                pDst1[dstIndex] = ((pDst1[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb1 >> 1) & 0x7f7f7f);
                dstIndex++;
                pDst2[dstIndex] = colRgb2 + noise;
                pDst1[dstIndex] = ((pDst3[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb2 >> 1) & 0x7f7f7f);
                pDst1[dstIndex] = ((pDst1[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb2 >> 1) & 0x7f7f7f);
                dstIndex++;

                rnd *= 23;
                colCur = colNext;
            }
        }

        pDst3  = pDst2;
        pDst1 += dstPitch * 2;
        pDst2 += dstPitch * 2;
    }
}



static void copyPAL_2x2_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32 rnd, void* pRgbTable)
{
    UInt16* pRgbTable16 = (UInt16*)pRgbTable;
    UInt16* pDst1       = (UInt16*)pDestination;
    UInt16* pDst2       = pDst1 + dstPitch / (int)sizeof(UInt16);
    UInt16* pDst3       = pDst2;
    int height          = frame->lines;
    int h;

    dstPitch /= (int)sizeof(UInt16);

    if (frame->interlaceOdd) {
        pDst1 += dstPitch;
        pDst2 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        int width = frame->line[h].width;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev2 = colCur;
        UInt32 colPrev1 = colCur;
        UInt32 colNext1 = colCur;
        int dstIndex = 0;

        if (width > 320) {
            int w;
            for (w = 0; w < width;) {
                UInt32 colNext2;
                UInt16 colRgb1;
                UInt16 colRgb2;
                UInt32 colTmp;
                UInt32 colLgt;
                UInt16 noise;

                colNext2 = pSrc[w];

                colLgt = colCur;
                w++;

                colTmp  = ((colPrev2 + colNext2) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colNext1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colLgt) >> 1) & YCBCR_MASK;
                colRgb1 = pRgbTable16[colTmp];

                colPrev2 = colPrev1;
                colPrev1 = colCur;
                colCur   = colNext1;
                colNext1 = colNext2;
                colNext2 = pSrc[w];

                colLgt = colCur;
                w++;

                colTmp  = ((colPrev2 + colNext2) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colNext1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colLgt) >> 1) & YCBCR_MASK;
                colRgb2 = pRgbTable16[colTmp];

                colPrev2 = colPrev1;
                colPrev1 = colCur;
                colCur   = colNext1;
                colNext1 = colNext2;

                noise = (UInt16)(rnd >> 31) * 0x0821;
                pDst2[dstIndex] = colRgb1 + noise;
                pDst1[dstIndex] = (((pDst3[dstIndex] >> 1) & 0x7bef) + ((colRgb1 >> 1) & 0x7bef));
                dstIndex++;
                pDst2[dstIndex] = colRgb2 + noise;
                pDst1[dstIndex] = (((pDst3[dstIndex] >> 1) & 0x7bef) + ((colRgb2 >> 1) & 0x7bef));
                dstIndex++;

                rnd *= 23;
            }
        }
        else {
            int w;
            for (w = 0; w < width; w++) {
                UInt32 colNext;
                UInt16 colRgb1;
                UInt16 colRgb2;
                UInt32 colTmp;
                UInt32 colLgt;
                UInt16 noise;

                colNext = pSrc[w];

                colLgt = colCur;

                colTmp  = ((colPrev1 + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colLgt) >> 1) & YCBCR_MASK;
                colRgb1 = pRgbTable16[colTmp];

                colTmp  = ((colNext + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colLgt) >> 1) & YCBCR_MASK;
                colRgb2 = pRgbTable16[colTmp];

                noise = (UInt16)(rnd >> 31) * 0x0821;
                pDst2[dstIndex] = colRgb1 + noise;
                pDst1[dstIndex] = (((pDst3[dstIndex] >> 1) & 0x7bef) + ((colRgb1 >> 1) & 0x7bef));
                dstIndex++;
                pDst2[dstIndex] = colRgb2 + noise;
                pDst1[dstIndex] = (((pDst3[dstIndex] >> 1) & 0x7bef) + ((colRgb2 >> 1) & 0x7bef));
                dstIndex++;

                rnd *= 23;
                colPrev1 = colCur;
                colCur = colNext;
            }
        }
        pDst3 = pDst2;
        pDst1 += dstPitch * 2;
        pDst2 += dstPitch * 2;
    }
}

static void copyPAL_2x2_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32 rnd, void* pRgbTable)
{
    UInt32* pRgbTable32 = (UInt32*)pRgbTable;
    UInt32* pDst1       = (UInt32*)pDestination;
    UInt32* pDst2       = pDst1 + dstPitch / (int)sizeof(UInt32);
    UInt32* pDst3       = pDst2;
    int height          = frame->lines;
    int h;

    dstPitch /= (int)sizeof(UInt32);

    if (frame->interlaceOdd) {
        pDst1 += dstPitch;
        pDst2 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        int width = frame->line[h].width;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev2 = colCur;
        UInt32 colPrev1 = colCur;
        UInt32 colNext1 = colCur;
        int dstIndex = 0;

        if (width > 320) {
            int w;
            for (w = 0; w < width;) {
                UInt32 colNext2;
                UInt32 colRgb1;
                UInt32 colRgb2;
                UInt32 colTmp;
                UInt32 colLgt;
                UInt32 noise;

                colNext2 = pSrc[w];

                colLgt = colCur;
                w++;

                colTmp  = ((colPrev2 + colNext2) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colNext1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colLgt) >> 1) & YCBCR_MASK;
                colRgb1 = pRgbTable32[colTmp];

                colPrev2 = colPrev1;
                colPrev1 = colCur;
                colCur   = colNext1;
                colNext1 = colNext2;
                colNext2 = pSrc[w];

                colLgt = colCur;
                w++;

                colTmp  = ((colPrev2 + colNext2) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colNext1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colLgt) >> 1) & YCBCR_MASK;
                colRgb2 = pRgbTable32[colTmp];

                colPrev2 = colPrev1;
                colPrev1 = colCur;
                colCur   = colNext1;
                colNext1 = colNext2;

                noise = (rnd >> 29) * 0x10101;
                pDst2[dstIndex] = colRgb1 + noise;
                pDst1[dstIndex] = (((pDst3[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb1 >> 1) & 0x7f7f7f));
                dstIndex++;
                pDst2[dstIndex] = colRgb2 + noise;
                pDst1[dstIndex] = (((pDst3[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb2 >> 1) & 0x7f7f7f));
                dstIndex++;

                rnd *= 23;
            }
        }
        else {
            int w;
            for (w = 0; w < width; w++) {
                UInt32 colNext;
                UInt32 colRgb1;
                UInt32 colRgb2;
                UInt32 colTmp;
                UInt32 colLgt;
                UInt32 noise;

                colNext = pSrc[w];

                colLgt = colCur;

                colTmp  = ((colPrev1 + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colLgt) >> 1) & YCBCR_MASK;
                colRgb1 = pRgbTable32[colTmp];

                colTmp  = ((colNext + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colLgt) >> 1) & YCBCR_MASK;
                colRgb2 = pRgbTable32[colTmp];

                noise = (rnd >> 29) * 0x10101;
                pDst2[dstIndex] = colRgb1 + noise;
                pDst1[dstIndex] = (((pDst3[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb1 >> 1) & 0x7f7f7f));
                dstIndex++;
                pDst2[dstIndex] = colRgb2 + noise;
                pDst1[dstIndex] = (((pDst3[dstIndex] >> 1) & 0x7f7f7f) + ((colRgb2 >> 1) & 0x7f7f7f));
                dstIndex++;

                rnd *= 23;
                colPrev1 = colCur;
                colCur = colNext;
            }
        }
        pDst3 = pDst2;
        pDst1 += dstPitch * 2;
        pDst2 += dstPitch * 2;
    }
}

static void copyPAL_1x1_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32 rnd, void* pRgbTable)
{
    UInt16* pRgbTable16 = (UInt16*)pRgbTable;
    UInt16* pDst        = (UInt16*)pDestination;
    int height          = frame->lines;
    int h;
    
    dstPitch /= (int)sizeof(UInt16);

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev = colCur;
        int width = frame->line[h].width;
        int w;

        if (width > 320) {
            for (w = 0; w < width; w++) {
                UInt32 colNext = ((pSrc[2 * w] + pSrc[2 * w + 1]) >> 1) & YCBCR_MASK;
                UInt32 colTmp;

                colTmp  = ((colPrev + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colCur) >> 1) & YCBCR_MASK;

                pDst[w] = pRgbTable16[colTmp] + (UInt16)(rnd >> 31)  * 0x0821;

                rnd *= 23;
                colPrev = colCur;
                colCur = colNext;
            }
        }
        else {
            for (w = 0; w < width; w++) {
                UInt32 colNext = pSrc[w];
                UInt32 colTmp;

                colTmp  = ((colPrev + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colCur) >> 1) & YCBCR_MASK;

                pDst[w] = pRgbTable16[colTmp] + (UInt16)(rnd >> 31)  * 0x0821;

                rnd *= 23;
                colPrev = colCur;
                colCur = colNext;
            }
        }
        pDst += dstPitch;
    }
}


static void copyPAL_1x1_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32 rnd, void* pRgbTable)
{
    UInt32* pRgbTable32 = (UInt32*)pRgbTable;
    UInt32* pDst        = (UInt32*)pDestination;
    int height          = frame->lines;
    int h;

    dstPitch /= (int)sizeof(UInt32);

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev = colCur;
        int width = frame->line[h].width;
        int w;

        if (width > 320) {
            for (w = 0; w < width; w++) {
                UInt32 colNext = ((pSrc[2 * w] + pSrc[2 * w + 1]) >> 1) & YCBCR_MASK;
                UInt32 colTmp;

                colTmp  = ((colPrev + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colCur) >> 1) & YCBCR_MASK;

                pDst[w] = pRgbTable32[colTmp] + (rnd >> 31)  * 0x10101;

                rnd *= 23;
                colPrev = colCur;
                colCur = colNext;
            }
        }
        else {
            for (w = 0; w < width; w++) {
                UInt32 colNext = pSrc[w];
                UInt32 colTmp;

                colTmp  = ((colPrev + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colCur) >> 1) & YCBCR_MASK;

                pDst[w] = pRgbTable32[colTmp] + (rnd >> 31)  * 0x10101;

                rnd *= 23;
                colPrev = colCur;
                colCur = colNext;
            }
        }
        pDst += dstPitch;
    }
}


/*****************************************************************************
**
** Fast rendering routines
**
******************************************************************************
*/
static void copy_1x1_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32 rnd, void* pRgbTable)
{
    UInt16* pRgbTable16 = (UInt16*)pRgbTable;
    UInt16* pDst        = (UInt16*)pDestination;
    int height          = frame->lines;
    int h;

    dstPitch /= (int)sizeof(UInt16);

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        int width = frame->line[h].width / 4;

        if (width > 320 / 4) {
            while (width--) {
                pDst[0] = pRgbTable16[((pSrc[0] + pSrc[1]) >> 1) & YCBCR_MASK];
                pDst[1] = pRgbTable16[((pSrc[2] + pSrc[3]) >> 1) & YCBCR_MASK];
                pDst[2] = pRgbTable16[((pSrc[4] + pSrc[5]) >> 1) & YCBCR_MASK];
                pDst[3] = pRgbTable16[((pSrc[6] + pSrc[7]) >> 1) & YCBCR_MASK];
                pSrc += 8;
                pDst += 4;
            }
        }
        else {
            while (width--) {
                pDst[0] = pRgbTable16[pSrc[0]];
                pDst[1] = pRgbTable16[pSrc[1]];
                pDst[2] = pRgbTable16[pSrc[2]];
                pDst[3] = pRgbTable16[pSrc[3]];
                pSrc += 4;
                pDst += 4;
            }
        }
        pDst += dstPitch;
    }
}


static void copy_1x1_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32 rnd, void* pRgbTable)
{
    UInt32* pRgbTable32 = (UInt32*)pRgbTable;
    UInt32* pDst        = (UInt32*)pDestination;
    int height          = frame->lines;
    int h;

    dstPitch /= (int)sizeof(UInt16);

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        int width = frame->line[h].width / 4;

        if (width > 320 / 4) {
            while (width--) {
                pDst[0] = pRgbTable32[((pSrc[0] + pSrc[1]) >> 1) & YCBCR_MASK];
                pDst[1] = pRgbTable32[((pSrc[2] + pSrc[3]) >> 1) & YCBCR_MASK];
                pDst[2] = pRgbTable32[((pSrc[4] + pSrc[5]) >> 1) & YCBCR_MASK];
                pDst[3] = pRgbTable32[((pSrc[6] + pSrc[7]) >> 1) & YCBCR_MASK];
                pSrc += 8;
                pDst += 4;
            }
        }
        else {
            while (width--) {
                pDst[0] = pRgbTable32[pSrc[0]];
                pDst[1] = pRgbTable32[pSrc[1]];
                pDst[2] = pRgbTable32[pSrc[2]];
                pDst[3] = pRgbTable32[pSrc[3]];
                pSrc += 4;
                pDst += 4;
            }
        }
        pDst += dstPitch;
    }
}


static void copy_2x2_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32 rnd, void* pRgbTable)
{
    UInt16* pRgbTable16 = (UInt16*)pRgbTable;
    UInt16* pDst1       = (UInt16*)pDestination;
    UInt16* pDst2       = pDst1 + dstPitch / (int)sizeof(UInt16);
    int height          = frame->lines;
    int h;

    dstPitch /= (int)sizeof(UInt16);

    if (frame->interlaceOdd) {
        pDst1 += dstPitch;
        pDst2 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt16* pDst1old = pDst1;
        UInt16* pDst2old = pDst2;
        UInt32* pSrc = frame->line[h].buffer;
        int width = frame->line[h].width / 4;

        if (width > 320 / 4) {
            while (width--) {
                UInt16 col1 = pRgbTable16[pSrc[0]];
                UInt16 col2 = pRgbTable16[pSrc[1]];
                UInt16 col3 = pRgbTable16[pSrc[2]];
                UInt16 col4 = pRgbTable16[pSrc[3]];
                pSrc  += 4;

                pDst1[0] = col1;
                pDst1[1] = col2;
                pDst1[2] = col3;
                pDst1[3] = col4;
                pDst1 += 4;

                pDst2[0] = col1;
                pDst2[1] = col2;
                pDst2[2] = col3;
                pDst2[3] = col4;
                pDst2 += 4;
            }
        }
        else {
            while (width--) {
                UInt16 col1 = pRgbTable16[pSrc[0]];
                UInt16 col2 = pRgbTable16[pSrc[1]];
                UInt16 col3 = pRgbTable16[pSrc[2]];
                UInt16 col4 = pRgbTable16[pSrc[3]];
                pSrc  += 4;

                pDst1[0] = col1;
                pDst1[1] = col1;
                pDst1[2] = col2;
                pDst1[3] = col2;
                pDst1[4] = col3;
                pDst1[5] = col3;
                pDst1[6] = col4;
                pDst1[7] = col4;
                pDst1 += 8;

                pDst2[0] = col1;
                pDst2[1] = col1;
                pDst2[2] = col2;
                pDst2[3] = col2;
                pDst2[4] = col3;
                pDst2[5] = col3;
                pDst2[6] = col4;
                pDst2[7] = col4;
                pDst2 += 8;
            }
        }

        pDst1 = pDst1old + dstPitch * 2;
        pDst2 = pDst2old +  dstPitch * 2;
    }
}

static void copy_2x2_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32 rnd, void* pRgbTable)
{
    UInt32* pRgbTable32 = (UInt32*)pRgbTable;
    UInt32* pDst1       = (UInt32*)pDestination;
    UInt32* pDst2       = pDst1 + dstPitch / (int)sizeof(UInt32);
    int height          = frame->lines;
    int h;

    dstPitch /= (int)sizeof(UInt32);

    if (frame->interlaceOdd) {
        pDst1 += dstPitch;
        pDst2 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pDst1old = pDst1;
        UInt32* pDst2old = pDst2;
        UInt32* pSrc = frame->line[h].buffer;
        int width = frame->line[h].width / 4;

        if (width > 320 / 4) {
            while (width--) {
                UInt32 col1 = pRgbTable32[pSrc[0]];
                UInt32 col2 = pRgbTable32[pSrc[1]];
                UInt32 col3 = pRgbTable32[pSrc[2]];
                UInt32 col4 = pRgbTable32[pSrc[3]];
                pSrc  += 4;

                pDst1[0] = col1;
                pDst1[1] = col2;
                pDst1[2] = col3;
                pDst1[3] = col4;
                pDst1 += 4;

                pDst2[0] = col1;
                pDst2[1] = col2;
                pDst2[2] = col3;
                pDst2[3] = col4;
                pDst2 += 4;
            }
        }
        else {
            while (width--) {
                UInt32 col1 = pRgbTable32[pSrc[0]];
                UInt32 col2 = pRgbTable32[pSrc[1]];
                UInt32 col3 = pRgbTable32[pSrc[2]];
                UInt32 col4 = pRgbTable32[pSrc[3]];
                pSrc  += 4;

                pDst1[0] = col1;
                pDst1[1] = col1;
                pDst1[2] = col2;
                pDst1[3] = col2;
                pDst1[4] = col3;
                pDst1[5] = col3;
                pDst1[6] = col4;
                pDst1[7] = col4;
                pDst1 += 8;

                pDst2[0] = col1;
                pDst2[1] = col1;
                pDst2[2] = col2;
                pDst2[3] = col2;
                pDst2[4] = col3;
                pDst2[5] = col3;
                pDst2[6] = col4;
                pDst2[7] = col4;
                pDst2 += 8;
            }
        }

        pDst1 = pDst1old + dstPitch * 2;
        pDst2 = pDst2old +  dstPitch * 2;
    }
}


static void hq2x_2x2_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32 rnd, void* pRgbTable)
{
	UInt16  ImgSrc[320 * 240];
    UInt16* pRgbTable16 = (UInt16*)pRgbTable;
    UInt16* pDst        = (UInt16*)ImgSrc;
    int srcHeight       = frame->lines;
    int srcWidth        = frame->line[0].width;
	int h;

    if (srcWidth == 0) {
        return;
    }  

    for (h = 0; h < srcHeight; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        int width = srcWidth / 8;
        while (width--) {
            pDst[0] = pRgbTable16[pSrc[0]];
            pDst[1] = pRgbTable16[pSrc[1]];
            pDst[2] = pRgbTable16[pSrc[2]];
            pDst[3] = pRgbTable16[pSrc[3]];
            pDst[4] = pRgbTable16[pSrc[4]];
            pDst[5] = pRgbTable16[pSrc[5]];
            pDst[6] = pRgbTable16[pSrc[6]];
            pDst[7] = pRgbTable16[pSrc[7]];
            pSrc += 8;
            pDst += 8;
        }
    }

    hq2x_32(ImgSrc, pDestination, srcWidth, srcHeight, dstPitch);
}

static void scale2x_2x2_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32 rnd, void* pRgbTable)
{
	UInt32  ImgSrc[320 * 240];
	UInt32* pRgbTable32 = (UInt32*)pRgbTable;
    UInt32* pDst        = (UInt32*)ImgSrc;
    int srcHeight       = frame->lines;
    int srcWidth        = frame->line[0].width;
	int h;

    if (srcWidth == 0) {
        return;
    }

    for (h = 0; h < srcHeight; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        int width = srcWidth / 8;
        while (width--) {
            pDst[0] = pRgbTable32[pSrc[0]];
            pDst[1] = pRgbTable32[pSrc[1]];
            pDst[2] = pRgbTable32[pSrc[2]];
            pDst[3] = pRgbTable32[pSrc[3]];
            pDst[4] = pRgbTable32[pSrc[4]];
            pDst[5] = pRgbTable32[pSrc[5]];
            pDst[6] = pRgbTable32[pSrc[6]];
            pDst[7] = pRgbTable32[pSrc[7]];
            pSrc += 8;
            pDst += 8;
        }
    }

    scale(2, pDestination, dstPitch, ImgSrc, srcWidth * sizeof(UInt32), sizeof(UInt32), srcWidth, srcHeight);
}

static void scale2x_2x2_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32 rnd, void* pRgbTable)
{
	UInt16  ImgSrc[320 * 240];
	UInt16* pRgbTable16 = (UInt16*)pRgbTable;
    UInt16* pDst        = (UInt16*)ImgSrc;
    int srcHeight       = frame->lines;
    int srcWidth        = frame->line[0].width;
	int h;

    if (srcWidth == 0) {
        return;
    }

    for (h = 0; h < srcHeight; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        int width = srcWidth / 8;
        while (width--) {
            pDst[0] = pRgbTable16[pSrc[0]];
            pDst[1] = pRgbTable16[pSrc[1]];
            pDst[2] = pRgbTable16[pSrc[2]];
            pDst[3] = pRgbTable16[pSrc[3]];
            pDst[4] = pRgbTable16[pSrc[4]];
            pDst[5] = pRgbTable16[pSrc[5]];
            pDst[6] = pRgbTable16[pSrc[6]];
            pDst[7] = pRgbTable16[pSrc[7]];
            pSrc += 8;
            pDst += 8;
        }
    }

    scale(2, pDestination, dstPitch, ImgSrc, srcWidth * sizeof(UInt16), sizeof(UInt16), srcWidth, srcHeight);
}

/*****************************************************************************
**
** Public interface methods
**
******************************************************************************
*/
Video* videoCreate() 
{
    Video* pVideo = (Video*)calloc(sizeof(Video), 1);
    initYJKtoYCbCrTable();

    pVideo->gamma      = 1;
    pVideo->saturation = 1;
    pVideo->brightness = 0;
    pVideo->contrast   = 1;
    deInterlace        = 1;

    initRGBTable(pVideo);

    InitLUTs();

    pVideo->palMode = VIDEO_PAL_FAST;
    pVideo->pRgbTable16 = pRgbTableColor16;
    pVideo->pRgbTable32 = pRgbTableColor32;

    return pVideo;
}

void videoDestroy(Video* pVideo) 
{
    free(pVideo);
}

void videoSetFrameSkip(Video* pVideo, UInt32 skipCount)
{
    if (skipCount > 3) skipCount = 3;
}

void videoSetDeInterlace(Video* pVideo, int doDeInterlace)
{
    deInterlace = doDeInterlace;
}

UInt32 videoGetColor(int R, int G, int B)
{
    return ((R >> 3) << 12) | ((G >> 3) << 6) | (B >> 3);
}

void videoSetColors(Video* pVideo, int saturation, int brightness, int contrast, int gamma)
{
    pVideo->gamma      = 1 + (MAX(0, MIN(200, gamma)) - 100) / 500.;
    pVideo->saturation = MAX(0, MIN(200, saturation)) / 100.;
    pVideo->brightness = MAX(0, MIN(200, brightness)) - 100.;
    pVideo->contrast   = MAX(0, MIN(200, contrast)) / 100.;

    if (!initialized) {
        initYJKtoYCbCrTable();
        initialized = 1;
    }

    initRGBTable(pVideo);
}

void videoSetColorMode(Video* pVideo, VideoColorMode colorMode) 
{
    if (!initialized) {
        videoSetColors(pVideo, (int)pVideo->gamma, (int)pVideo->saturation, (int)pVideo->brightness, (int)pVideo->contrast);
    }

    switch (colorMode) {
    case VIDEO_GREEN:
        pVideo->pRgbTable16 = pRgbTableGreen16;
        pVideo->pRgbTable32 = pRgbTableGreen32;
        break;
    case VIDEO_BLACKWHITE:
        pVideo->pRgbTable16 = pRgbTableWhite16;
        pVideo->pRgbTable32 = pRgbTableWhite32;
        break;
    case VIDEO_AMBER:
        pVideo->pRgbTable16 = pRgbTableAmber16;
        pVideo->pRgbTable32 = pRgbTableAmber32;
        break;
    case VIDEO_COLOR:
    default:
        pVideo->pRgbTable16 = pRgbTableColor16;
        pVideo->pRgbTable32 = pRgbTableColor32;
        break;
    }
}

void videoSetPalMode(Video* pVideo, VideoPalMode palMode)
{
    pVideo->palMode = palMode;
}

void videoSetScanLines(Video* pVideo, int enable, int scanLinesPct)
{
    pVideo->scanLinesEnable = enable;
    pVideo->scanLinesPct    = scanLinesPct;
}

void videoSetColorSaturation(Video* pVideo, int enable, int width)
{
    pVideo->colorSaturationEnable = enable;
    pVideo->colorSaturationWidth  = width;
}

void colorSaturation_16(void* pBuffer, int width, int height, int pitch, int blur)
{
    // This can be made more efficient by using 32 bit arithmetic and calculate
    // two pixels at the time....
    UInt16* pBuf = (UInt16*)pBuffer;
    int w, h;

    pitch  /= (int)sizeof(UInt32);

    switch (blur) {
    case 0:
        break;

    case 1:
        for (h = 0; h < height; h++) {
            UInt32 p0 = pBuf[0] & 0xfefefe;
            for (w = 1; w < width; w++) {
                UInt32 p1 = pBuf[w] & 0xfefefe;
                pBuf[w] = (UInt16)((p0 & 0x00ff00) | (((p0 + p1) / 2) & 0x0000ff) | (p1 & 0xff0000));
                p0 = p1;
            }
            pBuf += pitch;
        }
        break;

    case 2:
        for (h = 0; h < height; h++) {
            UInt32 p0 = pBuf[0];
            UInt32 p1 = pBuf[1];
            for (w = 2; w < width; w++) {
                UInt32 p2 = pBuf[w];
                pBuf[w] = (UInt16)((p0 & 0x00ff00) | (p1 & 0x0000ff) | (((p1 + p2) / 2) & 0xff0000));
                p0 = p1;
                p1 = p2;
            }
            pBuf += pitch;
        }
        break;

    case 3:
        for (h = 0; h < height; h++) {
            UInt32 p0 = pBuf[0];
            UInt32 p1 = pBuf[1];
            for (w = 2; w < width; w++) {
                UInt32 p2 = pBuf[w];
                pBuf[w] = (UInt16)((p0 & 0x00ff00) | (p1 & 0x0000ff) | (p2 & 0xff0000));
                p0 = p1;
                p1 = p2;
            }
            pBuf += pitch;
        }
        break;

    case 4:
        for (h = 0; h < height; h++) {
            UInt32 p0 = pBuf[0] & 0xfefefe;
            UInt32 p1 = pBuf[1] & 0xfefefe;
            UInt32 p2 = pBuf[2] & 0xfefefe;
            for (w = 3; w < width; w++) {
                UInt32 p3 = pBuf[w] & 0xfefefe;;
                pBuf[w] = (UInt16)((((p0 + p1) / 2) & 0x00ff00) | (p2 & 0x0000ff) | (p3 & 0xff0000));
                p0 = p1;
                p1 = p2;
                p2 = p3;
            }
            pBuf += pitch;
        }
        break;
    }
}

void colorSaturation_32(void* pBuffer, int width, int height, int pitch, int blur)
{
    UInt32* pBuf = (UInt32*)pBuffer;
    int w, h;

    pitch  /= (int)sizeof(UInt32);

    switch (blur) {
    case 0:
        break;

    case 1:
        for (h = 0; h < height; h++) {
            UInt32 p0 = pBuf[0] & 0xfefefe;
            for (w = 1; w < width; w++) {
                UInt32 p1 = pBuf[w] & 0xfefefe;
                pBuf[w] = (p0 & 0x00ff00) | (((p0 + p1) / 2) & 0x0000ff) | (p1 & 0xff0000);
                p0 = p1;
            }
            pBuf += pitch;
        }
        break;

    case 2:
        for (h = 0; h < height; h++) {
            UInt32 p0 = pBuf[0];
            UInt32 p1 = pBuf[1];
            for (w = 2; w < width; w++) {
                UInt32 p2 = pBuf[w];
                pBuf[w] = (p0 & 0x00ff00) | (p1 & 0x0000ff) | (((p1 + p2) / 2) & 0xff0000);
                p0 = p1;
                p1 = p2;
            }
            pBuf += pitch;
        }
        break;

    case 3:
        for (h = 0; h < height; h++) {
            UInt32 p0 = pBuf[0];
            UInt32 p1 = pBuf[1];
            for (w = 2; w < width; w++) {
                UInt32 p2 = pBuf[w];
                pBuf[w] = (p0 & 0x00ff00) | (p1 & 0x0000ff) | (p2 & 0xff0000);
                p0 = p1;
                p1 = p2;
            }
            pBuf += pitch;
        }
        break;

    case 4:
        for (h = 0; h < height; h++) {
            UInt32 p0 = pBuf[0] & 0xfefefe;
            UInt32 p1 = pBuf[1] & 0xfefefe;
            UInt32 p2 = pBuf[2] & 0xfefefe;
            for (w = 3; w < width; w++) {
                UInt32 p3 = pBuf[w] & 0xfefefe;;
                pBuf[w] = (((p0 + p1) / 2) & 0x00ff00) | (p2 & 0x0000ff) | (p3 & 0xff0000);
                p0 = p1;
                p1 = p2;
                p2 = p3;
            }
            pBuf += pitch;
        }
        break;
    }
}

void scanLines_16(void* pBuffer, int width, int height, int pitch, int scanLinesPct)
{
    UInt32* pBuf = (UInt32*)pBuffer;
    int w, h;

    if (scanLinesPct == 100) {
        return;
    }

    pitch = pitch * 2 / (int)sizeof(UInt32);
    scanLinesPct = scanLinesPct * 32 / 100;
    height /= 2;
    width /= 2;

    if (scanLinesPct == 0) {
        for (h = 0; h < height; h++) {
            memset(pBuf, 0, width * sizeof(UInt32));
            pBuf += pitch;
        }
        return;
    }

    for (h = 0; h < height; h++) {
        for (w = 0; w < width; w++) {
            UInt32 pixel = pBuf[w];
            UInt32 a = (((pixel & 0x07e0f81f) * scanLinesPct) & 0xfc1f03e0) >> 5;
            UInt32 b = (((pixel >> 5) & 0x07c0f83f) * scanLinesPct) & 0xf81f07e0;
            pBuf[w] = a | b;
        }
        pBuf += pitch;
    }
}

void scanLines_32(void* pBuffer, int width, int height, int pitch, int scanLinesPct)
{
    UInt32* pBuf = (UInt32*)pBuffer;
    int w, h;

    if (scanLinesPct == 100) {
        return;
    }

    pitch = pitch * 2 / (int)sizeof(UInt32);
    scanLinesPct = scanLinesPct * 255 / 100;
    height /= 2;

    if (scanLinesPct == 0) {
        for (h = 0; h < height; h++) {
            memset(pBuf, 0, width * sizeof(UInt32));
            pBuf += pitch;
        }
        return;
    }

    for (h = 0; h < height; h++) {
        for (w = 0; w < width; w++) {
            UInt32 pixel = pBuf[w];
            UInt32 a = (((pixel & 0xff00ff) * scanLinesPct) & 0xff00ff00) >> 8;
            UInt32 b  = (((pixel >> 8)& 0xff00ff) * scanLinesPct) & 0xff00ff00;
            pBuf[w] = a | b;
        }
        pBuf += pitch;
    }
}

void videoRender(Video* pVideo, int bitDepth, int zoom, void* pDst, int dstPitch)
{
    static UInt32 rnd = 51;
    FrameBuffer* frame = frameBufferGetViewFrame();
    
    if (frame == NULL) {
        return;
    }

    // Update simple rand generator
    rnd *= 13;

    switch (bitDepth) {
    case 16:
        switch (pVideo->palMode) {
        case VIDEO_PAL_FAST:
            if (zoom == 2) copy_2x2_16(frame, pDst, dstPitch, 0, pVideo->pRgbTable16);
            else           copy_1x1_16(frame, pDst, dstPitch, 0, pVideo->pRgbTable16);
            break;
        case VIDEO_PAL_MONITOR:
            if (zoom == 2) copyMonitorPAL_2x2_16(frame, pDst, dstPitch, rnd, pVideo->pRgbTable16);
            else           copyPAL_1x1_16(frame, pDst, dstPitch, 0, pVideo->pRgbTable16);
            break;
        case VIDEO_PAL_SHARP:
            if (zoom == 2) copySharpPAL_2x2_16(frame, pDst, dstPitch, 0, pVideo->pRgbTable16);
            else           copyPAL_1x1_16(frame, pDst, dstPitch, 0, pVideo->pRgbTable16);
            break;
        case VIDEO_PAL_SHARP_NOISE:
            if (zoom == 2) copySharpPAL_2x2_16(frame, pDst, dstPitch, rnd, pVideo->pRgbTable16);
            else           copyPAL_1x1_16(frame, pDst, dstPitch, rnd, pVideo->pRgbTable16);
            break;
        case VIDEO_PAL_BLUR:
            if (zoom == 2) copyPAL_2x2_16(frame, pDst, dstPitch, 0, pVideo->pRgbTable16);
            else           copyPAL_1x1_16(frame, pDst, dstPitch, 0, pVideo->pRgbTable16);
            break;
        case VIDEO_PAL_BLUR_NOISE:
            if (zoom == 2) copyPAL_2x2_16(frame, pDst, dstPitch, rnd, pVideo->pRgbTable16);
            else           copyPAL_1x1_16(frame, pDst, dstPitch, rnd, pVideo->pRgbTable16);
            break;
		case VIDEO_PAL_HQ2X: // Can't do 16bit hq2x so just use scale2x instead
		case VIDEO_PAL_SCALE2X:
            if (zoom==2) {
                if (frame->line[0].width <= 320 && !frame->interlaceOdd) {
                    scale2x_2x2_16(frame, pDst, dstPitch, 0, pVideo->pRgbTable16);
                }
                else {
                    copy_2x2_16(frame, pDst, dstPitch, 0, pVideo->pRgbTable16);
                }
            }
            else {
                copy_1x1_16(frame, pDst, dstPitch, 0, pVideo->pRgbTable16);
            }
            break;
        }

        if (pVideo->colorSaturationEnable) {
            colorSaturation_16(pDst, 320 * zoom, 240 * zoom, dstPitch, pVideo->colorSaturationWidth);
        }

        if (pVideo->scanLinesEnable) {
            scanLines_16(pDst, 320 * zoom, 240 * zoom, dstPitch, pVideo->scanLinesPct);
        }

        break;
    case 32:
        switch (pVideo->palMode) {
        case VIDEO_PAL_FAST:
            if (zoom == 2) copy_2x2_32(frame, pDst, dstPitch, 0, pVideo->pRgbTable32);
            else           copy_1x1_32(frame, pDst, dstPitch, 0, pVideo->pRgbTable32);
            break;
        case VIDEO_PAL_MONITOR:
            if (zoom == 2) copyMonitorPAL_2x2_32(frame, pDst, dstPitch, rnd, pVideo->pRgbTable32);
            else           copyPAL_1x1_32(frame, pDst, dstPitch, 0, pVideo->pRgbTable32);
            break;
        case VIDEO_PAL_SHARP:
            if (zoom == 2) copySharpPAL_2x2_32(frame, pDst, dstPitch, 0, pVideo->pRgbTable32);
            else           copy_1x1_32(frame, pDst, dstPitch, 0, pVideo->pRgbTable32);
            break;
        case VIDEO_PAL_SHARP_NOISE:
            if (zoom == 2) copySharpPAL_2x2_32(frame, pDst, dstPitch, rnd, pVideo->pRgbTable32);
            else           copyPAL_1x1_32(frame, pDst, dstPitch, rnd, pVideo->pRgbTable32);
            break;
        case VIDEO_PAL_BLUR:
            if (zoom == 2) copyPAL_2x2_32(frame, pDst, dstPitch, 0, pVideo->pRgbTable32);
            else           copyPAL_1x1_32(frame, pDst, dstPitch, 0, pVideo->pRgbTable32);
            break;
        case VIDEO_PAL_BLUR_NOISE:
            if (zoom == 2) copyPAL_2x2_32(frame, pDst, dstPitch, rnd, pVideo->pRgbTable32);
            else           copyPAL_1x1_32(frame, pDst, dstPitch, rnd, pVideo->pRgbTable32);
            break;
		case VIDEO_PAL_SCALE2X:
            if (zoom==2) {
                if (frame->line[0].width <= 320 && !frame->interlaceOdd) {
                    scale2x_2x2_32(frame, pDst, dstPitch, 0, pVideo->pRgbTable32);
                }
                else {
                    copy_2x2_32(frame, pDst, dstPitch, 0, pVideo->pRgbTable32);
                }
            }
            else {
                copy_1x1_32(frame, pDst, dstPitch, 0, pVideo->pRgbTable32);
            }
            break;
		case VIDEO_PAL_HQ2X:
            if (zoom==2) {
                if (frame->line[0].width <= 320 && !frame->interlaceOdd) {
                    hq2x_2x2_32(frame, pDst, dstPitch, 0, pVideo->pRgbTable16);
                }
                else {
                    copy_2x2_32(frame, pDst, dstPitch, 0, pVideo->pRgbTable32);
                }
            }
            else {
                copy_1x1_32(frame, pDst, dstPitch, 0, pVideo->pRgbTable32);
            }
            break;
        }

        if (pVideo->colorSaturationEnable) {
            colorSaturation_32(pDst, 320 * zoom, 240 * zoom, dstPitch, pVideo->colorSaturationWidth);
        }

        if (pVideo->scanLinesEnable) {
            scanLines_32(pDst, 320 * zoom, 240 * zoom, dstPitch, pVideo->scanLinesPct);
        }
        break;
    }
}
