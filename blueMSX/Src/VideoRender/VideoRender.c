/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoRender/VideoRender.c,v $
**
** $Revision: 1.18 $
**
** $Date: 2005-02-09 20:52:57 $
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
#include "hq2x.h"
#include "hq3x.h"
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
static void copySharpPAL_2x2_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt16* rgbTable, UInt32 rnd)
{
    static UInt32 rndVal = 51;
    UInt16* pDst1       = (UInt16*)pDestination;
    UInt16* pDst2       = pDst1 + dstPitch / (int)sizeof(UInt16);
    UInt16* pDst3       = pDst2;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    rndVal *= 13;
    rnd    *= rndVal;

    dstPitch /= (int)sizeof(UInt16);

    if (frame->interlace == INTERLACE_ODD) {
        pDst1 += dstPitch;
        pDst2 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev1 = colCur;
        int dstIndex = 0;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth * 2;
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
                colRgb1  = rgbTable[colTmp];

                colPrev1  = colCur;
                colCur    = colNext1;

                colNext1 = pSrc[w++];
                colTmp  = ((colNext1   + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                colRgb2 = rgbTable[colTmp];

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
            int width = srcWidth;
            int w;
            for (w = 0; w < width; w++) {
                UInt32 colNext;
                UInt16 colRgb1;
                UInt16 colRgb2;
                UInt32 colTmp;
                UInt16 noise;

                colNext = pSrc[w];
                colTmp  = ((colNext + colCur) >> 1) & YCBCR_MASK;
                colRgb1 = rgbTable[((colTmp + colCur) >> 1) & YCBCR_MASK];
                colRgb2 = rgbTable[((colTmp + colNext) >> 1) & YCBCR_MASK];

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

static void copySharpPAL_2x2_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32* rgbTable, UInt32 rnd)
{
    static UInt32 rndVal = 51;
    UInt32* pDst1       = (UInt32*)pDestination;
    UInt32* pDst2       = pDst1 + dstPitch / (int)sizeof(UInt32);
    UInt32* pDst3       = pDst2;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    rndVal *= 13;
    rnd    *= rndVal;

    dstPitch /= (int)sizeof(UInt32);

    if (frame->interlace == INTERLACE_ODD) {
        pDst1 += dstPitch;
        pDst2 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev1 = colCur;
        int dstIndex = 0;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth * 2;
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
                colRgb1  = rgbTable[colTmp];

                colPrev1  = colCur;
                colCur    = colNext1;

                colNext1 = pSrc[w++];
                colTmp  = ((colNext1   + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                colRgb2 = rgbTable[colTmp];

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
            int width = srcWidth;
            int w;
            for (w = 0; w < width; w++) {
                UInt32 colNext;
                UInt32 colRgb1;
                UInt32 colRgb2;
                UInt32 colTmp;
                UInt32 noise;

                colNext = pSrc[w];
                colTmp  = ((colNext + colCur) >> 1) & YCBCR_MASK;
                colRgb1 = rgbTable[((colTmp + colCur) >> 1) & YCBCR_MASK];
                colRgb2 = rgbTable[((colTmp + colNext) >> 1) & YCBCR_MASK];

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

static void copySharpPAL_2x1_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt16* rgbTable, UInt32 rnd)
{
    static UInt32 rndVal = 51;
    UInt16* pDst1       = (UInt16*)pDestination;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    rndVal *= 13;
    rnd    *= rndVal;

    dstPitch /= (int)sizeof(UInt16);

    if (frame->interlace == INTERLACE_ODD) {
        pDst1 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev1 = colCur;
        int dstIndex = 0;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth * 2;
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
                colRgb1  = rgbTable[colTmp];

                colPrev1  = colCur;
                colCur    = colNext1;

                colNext1 = pSrc[w++];
                colTmp  = ((colNext1   + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                colRgb2 = rgbTable[colTmp];

                colPrev1 = colCur;
                colCur   = colNext1;

                noise = (UInt16)((rnd >> 31) * 0x821);
                pDst1[dstIndex++] = colRgb1 + noise;
                pDst1[dstIndex++] = colRgb2 + noise;

                rnd *= 23;
            }
        }
        else {
            int width = srcWidth;
            int w;
            for (w = 0; w < width; w++) {
                UInt32 colNext;
                UInt16 colRgb1;
                UInt16 colRgb2;
                UInt32 colTmp;
                UInt16 noise;

                colNext = pSrc[w];
                colTmp  = ((colNext + colCur) >> 1) & YCBCR_MASK;
                colRgb1 = rgbTable[((colTmp + colCur) >> 1) & YCBCR_MASK];
                colRgb2 = rgbTable[((colTmp + colNext) >> 1) & YCBCR_MASK];

                noise = (UInt16)((rnd >> 31) * 0x821);
                pDst1[dstIndex++] = colRgb1 + noise;
                pDst1[dstIndex++] = colRgb2 + noise;

                rnd *= 23;
                colCur = colNext;
            }
        }

        pDst1 += dstPitch;
    }
}


static void copySharpPAL_2x1_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32* rgbTable, UInt32 rnd)
{
    static UInt32 rndVal = 51;
    UInt32* pDst1       = (UInt32*)pDestination;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    rndVal *= 13;
    rnd    *= rndVal;

    dstPitch /= (int)sizeof(UInt32);

    if (frame->interlace == INTERLACE_ODD) {
        pDst1 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev1 = colCur;
        int dstIndex = 0;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth * 2;
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
                colRgb1  = rgbTable[colTmp];

                colPrev1  = colCur;
                colCur    = colNext1;

                colNext1 = pSrc[w++];
                colTmp  = ((colNext1   + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                colRgb2 = rgbTable[colTmp];

                colPrev1 = colCur;
                colCur   = colNext1;

                noise = (rnd >> 29) * 0x10101;
                pDst1[dstIndex++] = colRgb1 + noise;
                pDst1[dstIndex++] = colRgb2 + noise;

                rnd *= 23;
            }
        }
        else {
            int width = srcWidth;
            int w;
            for (w = 0; w < width; w++) {
                UInt32 colNext;
                UInt32 colRgb1;
                UInt32 colRgb2;
                UInt32 colTmp;
                UInt32 noise;

                colNext = pSrc[w];
                colTmp  = ((colNext + colCur) >> 1) & YCBCR_MASK;
                colRgb1 = rgbTable[((colTmp + colCur) >> 1) & YCBCR_MASK];
                colRgb2 = rgbTable[((colTmp + colNext) >> 1) & YCBCR_MASK];

                noise = (rnd >> 29) * 0x10101;
                pDst1[dstIndex++] = colRgb1 + noise;
                pDst1[dstIndex++] = colRgb2 + noise;

                rnd *= 23;
                colCur = colNext;
            }
        }

        pDst1 += dstPitch;
    }
}

static void copyMonitorPAL_2x2_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt16* rgbTable, UInt32 rnd)
{
    static UInt32 rndVal = 51;
    UInt16* pDst1       = (UInt16*)pDestination;
    UInt16* pDst2       = pDst1 + dstPitch / (int)sizeof(UInt16);
    UInt16* pDst3       = pDst2;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    rndVal *= 13;
    rnd    *= rndVal;

    dstPitch /= (int)sizeof(UInt16);

    if (frame->interlace == INTERLACE_ODD) {
        pDst1 += dstPitch;
        pDst2 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev1 = colCur;
        int dstIndex = 0;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth * 2;
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
                colRgb1  = rgbTable[colTmp];

                colPrev1  = colCur;
                colCur    = colNext1;

                colNext1 = pSrc[w++];
                colTmp  = ((colNext1   + colCur) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                colRgb2 = rgbTable[colTmp];

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
            int width = srcWidth;
            int w;
            for (w = 0; w < width; w++) {
                UInt32 colNext;
                UInt16 colRgb1;
                UInt16 colRgb2;
                UInt32 colTmp;
                UInt16 noise;

                colNext = pSrc[w];
                colTmp  = ((colNext + colCur) >> 1) & YCBCR_MASK;
                colRgb1 = rgbTable[((colTmp + colCur) >> 1) & YCBCR_MASK];
                colRgb2 = rgbTable[colNext];

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

static void copyMonitorPAL_2x2_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32* rgbTable, UInt32 rnd)
{
    static UInt32 rndVal = 51;
    UInt32* pDst1       = (UInt32*)pDestination;
    UInt32* pDst2       = pDst1 + dstPitch / (int)sizeof(UInt32);
    UInt32* pDst3       = pDst2;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    rndVal *= 13;
    rnd    *= rndVal;

    dstPitch /= (int)sizeof(UInt32);

    if (frame->interlace == INTERLACE_ODD) {
        pDst1 += dstPitch;
        pDst2 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev1 = colCur;
        int dstIndex = 0;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth * 2;
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
                colRgb1  = rgbTable[colTmp];

                colPrev1  = colCur;
                colCur    = colNext1;

                colNext1 = pSrc[w++];
                colTmp  = ((colNext1   + colCur) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                colRgb2 = rgbTable[colTmp];

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
            int width = srcWidth;
            int w;
            for (w = 0; w < width; w++) {
                UInt32 colNext;
                UInt32 colRgb1;
                UInt32 colRgb2;
                UInt32 colTmp;
                UInt32 noise;

                colNext = pSrc[w];
                colTmp  = ((colNext + colCur) >> 1) & YCBCR_MASK;
                colRgb1 = rgbTable[((colTmp + colCur) >> 1) & YCBCR_MASK];
                colRgb2 = rgbTable[colNext];

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

static void copyMonitorPAL_2x1_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt16* rgbTable, UInt32 rnd)
{
    static UInt32 rndVal = 51;
    UInt16* pDst1       = (UInt16*)pDestination;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    rndVal *= 13;
    rnd    *= rndVal;

    dstPitch /= (int)sizeof(UInt16);

    if (frame->interlace == INTERLACE_ODD) {
        pDst1 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev1 = colCur;
        int dstIndex = 0;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth * 2;
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
                colRgb1  = rgbTable[colTmp];

                colPrev1  = colCur;
                colCur    = colNext1;

                colNext1 = pSrc[w++];
                colTmp  = ((colNext1   + colCur) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                colRgb2 = rgbTable[colTmp];

                colPrev1 = colCur;
                colCur   = colNext1;

                noise = (UInt16)(rnd >> 31) * 0x0821;
                pDst1[dstIndex++] = colRgb1 + noise;
                pDst1[dstIndex++] = colRgb2 + noise;

                rnd *= 23;
            }
        }
        else {
            int width = srcWidth;
            int w;
            for (w = 0; w < width; w++) {
                UInt32 colNext;
                UInt16 colRgb1;
                UInt16 colRgb2;
                UInt32 colTmp;
                UInt16 noise;

                colNext = pSrc[w];
                colTmp  = ((colNext + colCur) >> 1) & YCBCR_MASK;
                colRgb1 = rgbTable[((colTmp + colCur) >> 1) & YCBCR_MASK];
                colRgb2 = rgbTable[colNext];

                noise = (UInt16)(rnd >> 31) * 0x0821;
                pDst1[dstIndex++] = colRgb1 + noise;
                pDst1[dstIndex++] = colRgb2 + noise;
                rnd *= 23;
                colCur = colNext;
            }
        }

        pDst1 += dstPitch;
    }
}

static void copyMonitorPAL_2x1_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32* rgbTable, UInt32 rnd)
{
    static UInt32 rndVal = 51;
    UInt32* pDst1       = (UInt32*)pDestination;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    rndVal *= 13;
    rnd    *= rndVal;

    dstPitch /= (int)sizeof(UInt32);

    if (frame->interlace == INTERLACE_ODD) {
        pDst1 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev1 = colCur;
        int dstIndex = 0;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth * 2;
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
                colRgb1  = rgbTable[colTmp];

                colPrev1  = colCur;
                colCur    = colNext1;

                colNext1 = pSrc[w++];
                colTmp  = ((colNext1   + colCur) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                colRgb2 = rgbTable[colTmp];

                colPrev1 = colCur;
                colCur   = colNext1;

                noise = (rnd >> 30) * 0x10101;

                pDst1[dstIndex++] = colRgb1 + noise;
                pDst1[dstIndex++] = colRgb2 + noise;

                rnd *= 23;
            }
        }
        else {
            int width = srcWidth;
            int w;
            for (w = 0; w < width; w++) {
                UInt32 colNext;
                UInt32 colRgb1;
                UInt32 colRgb2;
                UInt32 colTmp;
                UInt32 noise;

                colNext = pSrc[w];
                colTmp  = ((colNext + colCur) >> 1) & YCBCR_MASK;
                colRgb1 = rgbTable[((colTmp + colCur) >> 1) & YCBCR_MASK];
                colRgb2 = rgbTable[colNext];

                noise = (rnd >> 30) * 0x10101;
                pDst1[dstIndex++] = colRgb1 + noise;
                pDst1[dstIndex++] = colRgb2 + noise;
                rnd *= 23;
                colCur = colNext;
            }
        }

        pDst1 += dstPitch;
    }
}



static void copyPAL_2x2_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt16* rgbTable, UInt32 rnd)
{
    static UInt32 rndVal = 51;
    UInt16* pDst1       = (UInt16*)pDestination;
    UInt16* pDst2       = pDst1 + dstPitch / (int)sizeof(UInt16);
    UInt16* pDst3       = pDst2;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    rndVal *= 13;
    rnd    *= rndVal;

    dstPitch /= (int)sizeof(UInt16);

    if (frame->interlace == INTERLACE_ODD) {
        pDst1 += dstPitch;
        pDst2 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev2 = colCur;
        UInt32 colPrev1 = colCur;
        UInt32 colNext1 = colCur;
        int dstIndex = 0;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth * 2;
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
                colRgb1 = rgbTable[colTmp];

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
                colRgb2 = rgbTable[colTmp];

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
            int width = srcWidth;
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
                colRgb1 = rgbTable[colTmp];

                colTmp  = ((colNext + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colLgt) >> 1) & YCBCR_MASK;
                colRgb2 = rgbTable[colTmp];

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

static void copyPAL_2x2_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32* rgbTable, UInt32 rnd)
{
    static UInt32 rndVal = 51;
    UInt32* pDst1       = (UInt32*)pDestination;
    UInt32* pDst2       = pDst1 + dstPitch / (int)sizeof(UInt32);
    UInt32* pDst3       = pDst2;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    rndVal *= 13;
    rnd    *= rndVal;

    dstPitch /= (int)sizeof(UInt32);

    if (frame->interlace == INTERLACE_ODD) {
        pDst1 += dstPitch;
        pDst2 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev2 = colCur;
        UInt32 colPrev1 = colCur;
        UInt32 colNext1 = colCur;
        int dstIndex = 0;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth * 2;
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
                colRgb1 = rgbTable[colTmp];

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
                colRgb2 = rgbTable[colTmp];

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
            int width = srcWidth;
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
                colRgb1 = rgbTable[colTmp];

                colTmp  = ((colNext + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colLgt) >> 1) & YCBCR_MASK;
                colRgb2 = rgbTable[colTmp];

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

static void copyPAL_2x1_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt16* rgbTable, UInt32 rnd)
{
    static UInt32 rndVal = 51;
    UInt16* pDst1       = (UInt16*)pDestination;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    rndVal *= 13;
    rnd    *= rndVal;

    dstPitch /= (int)sizeof(UInt16);

    if (frame->interlace == INTERLACE_ODD) {
        pDst1 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev2 = colCur;
        UInt32 colPrev1 = colCur;
        UInt32 colNext1 = colCur;
        int dstIndex = 0;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth * 2;
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
                colRgb1 = rgbTable[colTmp];

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
                colRgb2 = rgbTable[colTmp];

                colPrev2 = colPrev1;
                colPrev1 = colCur;
                colCur   = colNext1;
                colNext1 = colNext2;

                noise = (UInt16)((rnd >> 31) * 0x821);
                pDst1[dstIndex++] = colRgb1 + noise;
                pDst1[dstIndex++] = colRgb2 + noise;

                rnd *= 23;
            }
        }
        else {
            int width = srcWidth;
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
                colRgb1 = rgbTable[colTmp];

                colTmp  = ((colNext + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colLgt) >> 1) & YCBCR_MASK;
                colRgb2 = rgbTable[colTmp];

                noise = (UInt16)((rnd >> 31) * 0x821);
                pDst1[dstIndex++] = colRgb1 + noise;
                pDst1[dstIndex++] = colRgb2 + noise;


                rnd *= 23;
                colPrev1 = colCur;
                colCur = colNext;
            }
        }
        pDst1 += dstPitch;
    }
}

static void copyPAL_2x1_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32* rgbTable, UInt32 rnd)
{
    static UInt32 rndVal = 51;
    UInt32* pDst1       = (UInt32*)pDestination;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    rndVal *= 13;
    rnd    *= rndVal;

    dstPitch /= (int)sizeof(UInt32);

    if (frame->interlace == INTERLACE_ODD) {
        pDst1 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev2 = colCur;
        UInt32 colPrev1 = colCur;
        UInt32 colNext1 = colCur;
        int dstIndex = 0;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth * 2;
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
                colRgb1 = rgbTable[colTmp];

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
                colRgb2 = rgbTable[colTmp];

                colPrev2 = colPrev1;
                colPrev1 = colCur;
                colCur   = colNext1;
                colNext1 = colNext2;

                noise = (rnd >> 29) * 0x10101;
                pDst1[dstIndex++] = colRgb1 + noise;
                pDst1[dstIndex++] = colRgb2 + noise;

                rnd *= 23;
            }
        }
        else {
            int width = srcWidth;
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
                colRgb1 = rgbTable[colTmp];

                colTmp  = ((colNext + colPrev1) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colLgt) >> 1) & YCBCR_MASK;
                colRgb2 = rgbTable[colTmp];

                noise = (rnd >> 29) * 0x10101;
                pDst1[dstIndex++] = colRgb1 + noise;
                pDst1[dstIndex++] = colRgb2 + noise;


                rnd *= 23;
                colPrev1 = colCur;
                colCur = colNext;
            }
        }
        pDst1 += dstPitch;
    }
}

static void copyPAL_1x1_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt16* rgbTable, UInt32 rnd)
{
    static UInt32 rndVal = 51;
    UInt16* pDst        = (UInt16*)pDestination;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    rndVal *= 13;
    rnd    *= rndVal;
    
    dstPitch /= (int)sizeof(UInt16);

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev = colCur;
        int w;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth * 2;
            for (w = 0; w < width; w++) {
                UInt32 colNext = ((pSrc[2 * w] + pSrc[2 * w + 1]) >> 1) & YCBCR_MASK;
                UInt32 colTmp;

                colTmp  = ((colPrev + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colCur) >> 1) & YCBCR_MASK;

                pDst[w] = rgbTable[colTmp] + (UInt16)(rnd >> 31)  * 0x0821;

                rnd *= 23;
                colPrev = colCur;
                colCur = colNext;
            }
        }
        else {
            int width = srcWidth;
            for (w = 0; w < width; w++) {
                UInt32 colNext = pSrc[w];
                UInt32 colTmp;

                colTmp  = ((colPrev + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colCur) >> 1) & YCBCR_MASK;

                pDst[w] = rgbTable[colTmp] + (UInt16)(rnd >> 31)  * 0x0821;

                rnd *= 23;
                colPrev = colCur;
                colCur = colNext;
            }
        }
        pDst += dstPitch;
    }
}


static void copyPAL_1x1_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32* rgbTable, UInt32 rnd)
{
    static UInt32 rndVal = 51;
    UInt32* pDst        = (UInt32*)pDestination;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    rndVal *= 13;
    rnd    *= rndVal;

    dstPitch /= (int)sizeof(UInt32);

    for (h = 0; h < height; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        UInt32 colCur = pSrc[0];
        UInt32 colPrev = colCur;
        int w;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth * 2;
            for (w = 0; w < width; w++) {
                UInt32 colNext = ((pSrc[2 * w] + pSrc[2 * w + 1]) >> 1) & YCBCR_MASK;
                UInt32 colTmp;

                colTmp  = ((colPrev + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colCur) >> 1) & YCBCR_MASK;

                pDst[w] = rgbTable[colTmp] + (rnd >> 31)  * 0x10101;

                rnd *= 23;
                colPrev = colCur;
                colCur = colNext;
            }
        }
        else {
            int width = srcWidth;
            for (w = 0; w < width; w++) {
                UInt32 colNext = pSrc[w];
                UInt32 colTmp;

                colTmp  = ((colPrev + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colCur) >> 1) & YCBCR_MASK;

                pDst[w] = rgbTable[colTmp] + (rnd >> 31)  * 0x10101;

                rnd *= 23;
                colPrev = colCur;
                colCur = colNext;
            }
        }
        pDst += dstPitch;
    }
}

static void copyPAL_1x05_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt16* rgbTable, UInt32 rnd)
{
    static UInt32 rndVal = 51;
    UInt16* pDst        = (UInt16*)pDestination;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    rndVal *= 13;
    rnd    *= rndVal;

    dstPitch /= (int)sizeof(UInt16);

    for (h = 0; h < height; h += 2) {
        UInt32* pSrc1 = frame->line[h + 0].buffer;
        UInt32* pSrc2 = frame->line[h + 1].buffer;
        UInt32 colCur = pSrc1[0];
        UInt32 colPrev = colCur;
        int w;

        if (frame->line[h].doubleWidth) {
            for (w = 0; w < srcWidth; w++) {
                UInt32 colNext1 = ((pSrc1[2 * w] + pSrc1[2 * w + 1]) >> 1) & YCBCR_MASK;
                UInt32 colNext2 = ((pSrc2[2 * w] + pSrc2[2 * w + 1]) >> 1) & YCBCR_MASK;
                UInt32 colNext  = ((colNext1 + colNext2) >> 1) & YCBCR_MASK;
                UInt32 colTmp;

                colTmp  = ((colPrev + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colCur) >> 1) & YCBCR_MASK;

                pDst[w] = rgbTable[colTmp] + (UInt16)(rnd >> 31) * 0x0821;

                rnd *= 23;
                colPrev = colCur;
                colCur = colNext;
            }
        }
        else {
            for (w = 0; w < srcWidth; w++) {
                UInt32 colNext = ((pSrc1[w] + pSrc2[w]) >> 1) & YCBCR_MASK;
                UInt32 colTmp;

                colTmp  = ((colPrev + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colCur) >> 1) & YCBCR_MASK;

                pDst[w] = rgbTable[colTmp] + (UInt16)(rnd >> 31) * 0x0821;

                rnd *= 23;
                colPrev = colCur;
                colCur = colNext;
            }
        }
        pDst += dstPitch;
    }
}


static void copyPAL_1x05_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32* rgbTable, UInt32 rnd)
{
    static UInt32 rndVal = 51;
    UInt32* pDst        = (UInt32*)pDestination;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    rndVal *= 13;
    rnd    *= rndVal;

    dstPitch /= (int)sizeof(UInt32);

    for (h = 0; h < height; h += 2) {
        UInt32* pSrc1 = frame->line[h + 0].buffer;
        UInt32* pSrc2 = frame->line[h + 1].buffer;
        UInt32 colCur = pSrc1[0];
        UInt32 colPrev = colCur;
        int w;

        if (frame->line[h].doubleWidth) {
            for (w = 0; w < srcWidth; w++) {
                UInt32 colNext1 = ((pSrc1[2 * w] + pSrc1[2 * w + 1]) >> 1) & YCBCR_MASK;
                UInt32 colNext2 = ((pSrc2[2 * w] + pSrc2[2 * w + 1]) >> 1) & YCBCR_MASK;
                UInt32 colNext  = ((colNext1 + colNext2) >> 1) & YCBCR_MASK;
                UInt32 colTmp;

                colTmp  = ((colPrev + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colCur) >> 1) & YCBCR_MASK;

                pDst[w] = rgbTable[colTmp] + (rnd >> 31)  * 0x10101;

                rnd *= 23;
                colPrev = colCur;
                colCur = colNext;
            }
        }
        else {
            for (w = 0; w < srcWidth; w++) {
                UInt32 colNext = ((pSrc1[w] + pSrc2[w]) >> 1) & YCBCR_MASK;
                UInt32 colTmp;

                colTmp  = ((colPrev + colNext) >> 1) & YCBCR_MASK;
                colTmp  = ((colTmp + colCur) >> 1) & YCBCR_MASK;

                pDst[w] = rgbTable[colTmp] + (rnd >> 31)  * 0x10101;

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
static void copy_1x1_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt16* rgbTable)
{
    UInt16* pDst        = (UInt16*)pDestination;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    dstPitch /= (int)sizeof(UInt16);

    for (h = 0; h < height; h++) {
        UInt16* pOldDst = pDst;
        UInt32* pSrc = frame->line[h].buffer;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth / 4;
            while (width--) {
                pDst[0] = rgbTable[((pSrc[0] + pSrc[1]) >> 1) & YCBCR_MASK];
                pDst[1] = rgbTable[((pSrc[2] + pSrc[3]) >> 1) & YCBCR_MASK];
                pDst[2] = rgbTable[((pSrc[4] + pSrc[5]) >> 1) & YCBCR_MASK];
                pDst[3] = rgbTable[((pSrc[6] + pSrc[7]) >> 1) & YCBCR_MASK];
                pSrc += 8;
                pDst += 4;
            }
        }
        else {
            int width = srcWidth / 4;
            while (width--) {
                pDst[0] = rgbTable[pSrc[0]];
                pDst[1] = rgbTable[pSrc[1]];
                pDst[2] = rgbTable[pSrc[2]];
                pDst[3] = rgbTable[pSrc[3]];
                pSrc += 4;
                pDst += 4;
            }
        }
        pDst = pOldDst + dstPitch; 
    }
}


static void copy_1x1_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32* rgbTable)
{
    UInt32* pDst        = (UInt32*)pDestination;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    dstPitch /= (int)sizeof(UInt32);

    for (h = 0; h < height; h++) {
        UInt32* pOldDst = pDst;
        UInt32* pSrc = frame->line[h].buffer;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth / 4;
            while (width--) {
                pDst[0] = rgbTable[((pSrc[0] + pSrc[1]) >> 1) & YCBCR_MASK];
                pDst[1] = rgbTable[((pSrc[2] + pSrc[3]) >> 1) & YCBCR_MASK];
                pDst[2] = rgbTable[((pSrc[4] + pSrc[5]) >> 1) & YCBCR_MASK];
                pDst[3] = rgbTable[((pSrc[6] + pSrc[7]) >> 1) & YCBCR_MASK];
                pSrc += 8;
                pDst += 4;
            }
        }
        else {
            int width = srcWidth / 4;
            while (width--) {
                pDst[0] = rgbTable[pSrc[0]];
                pDst[1] = rgbTable[pSrc[1]];
                pDst[2] = rgbTable[pSrc[2]];
                pDst[3] = rgbTable[pSrc[3]];
                pSrc += 4;
                pDst += 4;
            }
        }
        pDst = pOldDst + dstPitch; 
    }
}

static void copy_1x05_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt16* rgbTable)
{
    UInt16* pDst        = (UInt16*)pDestination;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    dstPitch /= (int)sizeof(UInt16);

    for (h = 0; h < height; h += 2) {
        UInt16* pOldDst = pDst;
        UInt32* pSrc1 = frame->line[h + 0].buffer;
        UInt32* pSrc2 = frame->line[h + 1].buffer;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth;
            while (width--) {
                UInt32 col0 = ((pSrc1[0] + pSrc1[1]) >> 1) & YCBCR_MASK;
                UInt32 col1 = ((pSrc2[0] + pSrc2[1]) >> 1) & YCBCR_MASK;
                
                *pDst++ = rgbTable[((col0 + col1) >> 1) & YCBCR_MASK];
                pSrc1 += 2;
                pSrc2 += 2;
            }
        }
        else {
            int width = srcWidth;
            while (width--) {
                *pDst++ = rgbTable[((*pSrc1++ + *pSrc2++) >> 1) & YCBCR_MASK];
            }
        }
        pDst = pOldDst + dstPitch; 
    }
}


static void copy_1x05_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32* rgbTable)
{
    UInt32* pDst        = (UInt32*)pDestination;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    dstPitch /= (int)sizeof(UInt32);

    for (h = 0; h < height; h += 2) {
        UInt32* pOldDst = pDst;
        UInt32* pSrc1 = frame->line[h + 0].buffer;
        UInt32* pSrc2 = frame->line[h + 1].buffer;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth;
            while (width--) {
                UInt32 col0 = ((pSrc1[0] + pSrc1[1]) >> 1) & YCBCR_MASK;
                UInt32 col1 = ((pSrc2[0] + pSrc2[1]) >> 1) & YCBCR_MASK;
                
                *pDst++ = rgbTable[((col0 + col1) >> 1) & YCBCR_MASK];
                pSrc1 += 2;
                pSrc2 += 2;
            }
        }
        else {
            int width = srcWidth;
            while (width--) {
                *pDst++ = rgbTable[((*pSrc1++ + *pSrc2++) >> 1) & YCBCR_MASK];
            }
        }
        pDst = pOldDst + dstPitch; 
    }
}


static void copy_2x2_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt16* rgbTable)
{
    UInt16* pDst1       = (UInt16*)pDestination;
    UInt16* pDst2       = pDst1 + dstPitch / (int)sizeof(UInt16);
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    dstPitch /= (int)sizeof(UInt16);

    if (frame->interlace == INTERLACE_ODD) {
        pDst1 += dstPitch;
        pDst2 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt16* pDst1old = pDst1;
        UInt16* pDst2old = pDst2;
        UInt32* pSrc = frame->line[h].buffer;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth / 4 * 2;
            while (width--) {
                UInt16 col1 = rgbTable[pSrc[0]];
                UInt16 col2 = rgbTable[pSrc[1]];
                UInt16 col3 = rgbTable[pSrc[2]];
                UInt16 col4 = rgbTable[pSrc[3]];
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
            int width = srcWidth / 4;
            while (width--) {
                UInt16 col1 = rgbTable[pSrc[0]];
                UInt16 col2 = rgbTable[pSrc[1]];
                UInt16 col3 = rgbTable[pSrc[2]];
                UInt16 col4 = rgbTable[pSrc[3]];
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

static void copy_2x2_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32* rgbTable)
{
    UInt32* pDst1       = (UInt32*)pDestination;
    UInt32* pDst2       = pDst1 + dstPitch / (int)sizeof(UInt32);
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    dstPitch /= (int)sizeof(UInt32);

    if (frame->interlace == INTERLACE_ODD) {
        pDst1 += dstPitch;
        pDst2 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pDst1old = pDst1;
        UInt32* pDst2old = pDst2;
        UInt32* pSrc = frame->line[h].buffer;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth / 4 * 2;
            while (width--) {
                UInt32 col1 = rgbTable[pSrc[0]];
                UInt32 col2 = rgbTable[pSrc[1]];
                UInt32 col3 = rgbTable[pSrc[2]];
                UInt32 col4 = rgbTable[pSrc[3]];
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
            int width = srcWidth / 4;
            while (width--) {
                UInt32 col1 = rgbTable[pSrc[0]];
                UInt32 col2 = rgbTable[pSrc[1]];
                UInt32 col3 = rgbTable[pSrc[2]];
                UInt32 col4 = rgbTable[pSrc[3]];
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

static void copy_2x1_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt16* rgbTable)
{
    UInt16* pDst1       = (UInt16*)pDestination;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    dstPitch /= (int)sizeof(UInt16);

    if (frame->interlace == INTERLACE_ODD) {
        pDst1 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt16* pDst1old = pDst1;
        UInt32* pSrc = frame->line[h].buffer;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth / 4 * 2;
            while (width--) {
                pDst1[0] = rgbTable[pSrc[0]];
                pDst1[1] = rgbTable[pSrc[1]];
                pDst1[2] = rgbTable[pSrc[2]];
                pDst1[3] = rgbTable[pSrc[3]];
                pDst1 += 4;
                pSrc  += 4;
            }
        }
        else {
            int width = srcWidth / 4;
            while (width--) {
                UInt16 col1 = rgbTable[pSrc[0]];
                UInt16 col2 = rgbTable[pSrc[1]];
                UInt16 col3 = rgbTable[pSrc[2]];
                UInt16 col4 = rgbTable[pSrc[3]];
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
            }
        }

        pDst1 = pDst1old + dstPitch;
    }
}

static void copy_2x1_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32* rgbTable)
{
    UInt32* pDst1       = (UInt32*)pDestination;
    int height          = frame->lines;
    int srcWidth        = frame->maxWidth;
    int h;

    dstPitch /= (int)sizeof(UInt32);

    if (frame->interlace == INTERLACE_ODD) {
        pDst1 += dstPitch;
        height--;
    }

    for (h = 0; h < height; h++) {
        UInt32* pDst1old = pDst1;
        UInt32* pSrc = frame->line[h].buffer;

        if (frame->line[h].doubleWidth) {
            int width = srcWidth / 4 * 2;
            while (width--) {
                pDst1[0] = rgbTable[pSrc[0]];
                pDst1[1] = rgbTable[pSrc[1]];
                pDst1[2] = rgbTable[pSrc[2]];
                pDst1[3] = rgbTable[pSrc[3]];
                pDst1 += 4;
                pSrc  += 4;
            }
        }
        else {
            int width = srcWidth / 4;
            while (width--) {
                UInt32 col1 = rgbTable[pSrc[0]];
                UInt32 col2 = rgbTable[pSrc[1]];
                UInt32 col3 = rgbTable[pSrc[2]];
                UInt32 col4 = rgbTable[pSrc[3]];
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
            }
        }

        pDst1 = pDst1old + dstPitch;
    }
}



static void hq2x_2x2_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt16* rgbTable)
{
	UInt16  ImgSrc[320 * 240];
    UInt16* pDst        = (UInt16*)ImgSrc;
    int srcHeight       = frame->lines;
    int srcWidth        = frame->maxWidth;
	int h;

    if (srcWidth == 0) {
        return;
    }  

    for (h = 0; h < srcHeight; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        int width = srcWidth / 8;
        while (width--) {
            pDst[0] = rgbTable[pSrc[0]];
            pDst[1] = rgbTable[pSrc[1]];
            pDst[2] = rgbTable[pSrc[2]];
            pDst[3] = rgbTable[pSrc[3]];
            pDst[4] = rgbTable[pSrc[4]];
            pDst[5] = rgbTable[pSrc[5]];
            pDst[6] = rgbTable[pSrc[6]];
            pDst[7] = rgbTable[pSrc[7]];
            pSrc += 8;
            pDst += 8;
        }
    }

    hq2x_32(ImgSrc, pDestination, srcWidth, srcHeight, dstPitch);
}

static void hq3x_2x2_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt16* rgbTable)
{
	UInt16  ImgSrc[320 * 240];
    UInt16* pDst        = (UInt16*)ImgSrc;
    int srcHeight       = frame->lines;
    int srcWidth        = frame->maxWidth;
	int h;

    if (srcWidth == 0) {
        return;
    }  

    for (h = 0; h < srcHeight; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        int width = srcWidth / 8;
        while (width--) {
            pDst[0] = rgbTable[pSrc[0]];
            pDst[1] = rgbTable[pSrc[1]];
            pDst[2] = rgbTable[pSrc[2]];
            pDst[3] = rgbTable[pSrc[3]];
            pDst[4] = rgbTable[pSrc[4]];
            pDst[5] = rgbTable[pSrc[5]];
            pDst[6] = rgbTable[pSrc[6]];
            pDst[7] = rgbTable[pSrc[7]];
            pSrc += 8;
            pDst += 8;
        }
    }

    hq3x_32(ImgSrc, pDestination, srcWidth, srcHeight, dstPitch);
}

static void scale2x_2x2_32(FrameBuffer* frame, void* pDestination, int dstPitch, UInt32* rgbTable)
{
	UInt32  ImgSrc[320 * 240];
    UInt32* pDst        = (UInt32*)ImgSrc;
    int srcHeight       = frame->lines;
    int srcWidth        = frame->maxWidth;
	int h;

    if (srcWidth == 0) {
        return;
    }

    for (h = 0; h < srcHeight; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        int width = srcWidth / 8;
        while (width--) {
            pDst[0] = rgbTable[pSrc[0]];
            pDst[1] = rgbTable[pSrc[1]];
            pDst[2] = rgbTable[pSrc[2]];
            pDst[3] = rgbTable[pSrc[3]];
            pDst[4] = rgbTable[pSrc[4]];
            pDst[5] = rgbTable[pSrc[5]];
            pDst[6] = rgbTable[pSrc[6]];
            pDst[7] = rgbTable[pSrc[7]];
            pSrc += 8;
            pDst += 8;
        }
    }

    scale(2, pDestination, dstPitch, ImgSrc, srcWidth * sizeof(UInt32), sizeof(UInt32), srcWidth, srcHeight);
}

static void scale2x_2x2_16(FrameBuffer* frame, void* pDestination, int dstPitch, UInt16* rgbTable)
{
	UInt16  ImgSrc[320 * 240];
    UInt16* pDst        = (UInt16*)ImgSrc;
    int srcHeight       = frame->lines;
    int srcWidth        = frame->maxWidth;
	int h;

    if (srcWidth == 0) {
        return;
    }

    for (h = 0; h < srcHeight; h++) {
        UInt32* pSrc = frame->line[h].buffer;
        int width = srcWidth / 8;
        while (width--) {
            pDst[0] = rgbTable[pSrc[0]];
            pDst[1] = rgbTable[pSrc[1]];
            pDst[2] = rgbTable[pSrc[2]];
            pDst[3] = rgbTable[pSrc[3]];
            pDst[4] = rgbTable[pSrc[4]];
            pDst[5] = rgbTable[pSrc[5]];
            pDst[6] = rgbTable[pSrc[6]];
            pDst[7] = rgbTable[pSrc[7]];
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
    Video* pVideo = (Video*)calloc(1, sizeof(Video));
    initYJKtoYCbCrTable();

    pVideo->gamma       = 1;
    pVideo->saturation  = 1;
    pVideo->brightness  = 0;
    pVideo->contrast    = 1;
    pVideo->deInterlace = 0;

    initRGBTable(pVideo);

    hq2x_init();
    hq3x_init();

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

void videoSetDeInterlace(Video* pVideo, int deInterlace)
{
    pVideo->deInterlace = deInterlace;
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

    pitch  /= (int)sizeof(UInt16);

    switch (blur) {
    case 0:
        break;

    case 1:
        for (h = 0; h < height; h++) {
            UInt16 p0 = pBuf[0] & 0xf7de;
            for (w = 1; w < width; w++) {
                UInt16 p1 = pBuf[w] & 0xf7de;
                pBuf[w] = (UInt16)((p0 & 0x07e0) | (((p0 + p1) / 2) & 0x001f) | (p1 & 0xf800));
                p0 = p1;
            }
            pBuf += pitch;
        }
        break;

    case 2:
        for (h = 0; h < height; h++) {
            UInt16 p0 = pBuf[0];
            UInt16 p1 = pBuf[1];
            for (w = 2; w < width; w++) {
                UInt16 p2 = pBuf[w];
                pBuf[w] = (UInt16)((p0 & 0x07e0) | (p1 & 0x001f) | (((p1 + p2) / 2) & 0xf800));
                p0 = p1;
                p1 = p2;
            }
            pBuf += pitch;
        }
        break;

    case 3:
        for (h = 0; h < height; h++) {
            UInt16 p0 = pBuf[0];
            UInt16 p1 = pBuf[1];
            for (w = 2; w < width; w++) {
                UInt16 p2 = pBuf[w];
                pBuf[w] = (UInt16)((p0 & 0x07e0) | (p1 & 0x001f) | (p2 & 0xf800));
                p0 = p1;
                p1 = p2;
            }
            pBuf += pitch;
        }
        break;

    case 4:
        for (h = 0; h < height; h++) {
            UInt16 p0 = pBuf[0] & 0xf7de;
            UInt16 p1 = pBuf[1] & 0xf7de;
            UInt16 p2 = pBuf[2] & 0xf7de;
            for (w = 3; w < width; w++) {
                UInt16 p3 = pBuf[w] & 0xf7de;;
                pBuf[w] = (UInt16)((((p0 + p1) / 2) & 0x07e0) | (p2 & 0x001f) | (p3 & 0xf800));
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

static int videoRender240(Video* pVideo, FrameBuffer* frame, int bitDepth, int zoom, 
                          void* pDst, int dstOffset, int dstPitch, int canChangeZoom)
{
    pDst = (char*)pDst + zoom * dstOffset;

    switch (bitDepth) {
    case 16:
        switch (pVideo->palMode) {
        case VIDEO_PAL_FAST:
            if (zoom == 2) {
                if (pVideo->scanLinesEnable || pVideo->colorSaturationEnable || canChangeZoom == 0) {
                    copy_2x2_16(frame, pDst, dstPitch, pVideo->pRgbTable16);
                }
                else {
                    int h = frame->lines;
                    while (--h >= 0 && !frame->line[h].doubleWidth);
                    if (h) copy_2x2_16(frame, pDst, dstPitch, pVideo->pRgbTable16);
                    else {
                        copy_1x1_16(frame, pDst, dstPitch, pVideo->pRgbTable16);
                        zoom = 1;
                    }
                }
            }
            else copy_1x1_16(frame, pDst, dstPitch, pVideo->pRgbTable16);
            break;
        case VIDEO_PAL_MONITOR:
            if (zoom == 2) copyMonitorPAL_2x2_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 1);
            else           copyPAL_1x1_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 0);
            break;
        case VIDEO_PAL_SHARP:
            if (zoom == 2) copySharpPAL_2x2_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 0);
            else           copyPAL_1x1_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 0);
            break;
        case VIDEO_PAL_SHARP_NOISE:
            if (zoom == 2) copySharpPAL_2x2_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 1);
            else           copyPAL_1x1_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 1);
            break;
        case VIDEO_PAL_BLUR:
            if (zoom == 2) copyPAL_2x2_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 0);
            else           copyPAL_1x1_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 0);
            break;
        case VIDEO_PAL_BLUR_NOISE:
            if (zoom == 2) copyPAL_2x2_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 1);
            else           copyPAL_1x1_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 1);
            break;
		case VIDEO_PAL_HQ2X: // Can't do 16bit hq2x so just use scale2x instead
		case VIDEO_PAL_SCALE2X:
            if (zoom==2) {
                if (frame->line[0].doubleWidth == 0 && frame->interlace == INTERLACE_NONE) {
                    scale2x_2x2_16(frame, pDst, dstPitch, pVideo->pRgbTable16);
                }
                else {
                    copy_2x2_16(frame, pDst, dstPitch, pVideo->pRgbTable16);
                }
            }
            else {
                copy_1x1_16(frame, pDst, dstPitch, pVideo->pRgbTable16);
            }
            break;
        }
        break;
    case 32:
        switch (pVideo->palMode) {
        case VIDEO_PAL_FAST:
            if (zoom == 2) {
                if (pVideo->scanLinesEnable || pVideo->colorSaturationEnable || canChangeZoom == 0) {
                    copy_2x2_32(frame, pDst, dstPitch, pVideo->pRgbTable32);
                }
                else {
                    int h = frame->lines;
                    while (--h >= 0 && !frame->line[h].doubleWidth);
                    if (h) copy_2x2_32(frame, pDst, dstPitch, pVideo->pRgbTable32);
                    else {
                        copy_1x1_32(frame, pDst, dstPitch, pVideo->pRgbTable32);
                        zoom = 1;
                    }
                }
            }
            else           copy_1x1_32(frame, pDst, dstPitch, pVideo->pRgbTable32);
            break;
        case VIDEO_PAL_MONITOR:
            if (zoom == 2) copyMonitorPAL_2x2_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 1);
            else           copyPAL_1x1_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 0);
            break;
        case VIDEO_PAL_SHARP:
            if (zoom == 2) copySharpPAL_2x2_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 0);
            else           copy_1x1_32(frame, pDst, dstPitch, pVideo->pRgbTable32);
            break;
        case VIDEO_PAL_SHARP_NOISE:
            if (zoom == 2) copySharpPAL_2x2_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 1);
            else           copyPAL_1x1_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 1);
            break;
        case VIDEO_PAL_BLUR:
            if (zoom == 2) copyPAL_2x2_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 0);
            else           copyPAL_1x1_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 0);
            break;
        case VIDEO_PAL_BLUR_NOISE:
            if (zoom == 2) copyPAL_2x2_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 1);
            else           copyPAL_1x1_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 1);
            break;
		case VIDEO_PAL_SCALE2X:
            if (zoom==2) {
                if (frame->line[0].doubleWidth == 0 && frame->interlace == INTERLACE_NONE) {
                    scale2x_2x2_32(frame, pDst, dstPitch, pVideo->pRgbTable32);
                }
                else {
                    copy_2x2_32(frame, pDst, dstPitch, pVideo->pRgbTable32);
                }
            }
            else {
                copy_1x1_32(frame, pDst, dstPitch, pVideo->pRgbTable32);
            }
            break;
		case VIDEO_PAL_HQ2X:
            if (zoom==2) {
                if (frame->line[0].doubleWidth == 0 && frame->interlace == INTERLACE_NONE) {
                    if (canChangeZoom > 0) {
                        pDst = (char*)pDst + dstOffset;
                        hq3x_2x2_32(frame, pDst, dstPitch, pVideo->pRgbTable16);
                        zoom =3;
                    }
                    else {
                        hq2x_2x2_32(frame, pDst, dstPitch, pVideo->pRgbTable16);
                    }
                }
                else {
                    copy_2x2_32(frame, pDst, dstPitch, pVideo->pRgbTable32);
                }
            }
            else {
                copy_1x1_32(frame, pDst, dstPitch, pVideo->pRgbTable32);
            }
            break;
        }
        break;
    }
    return zoom;
}

static int videoRender480(Video* pVideo, FrameBuffer* frame, int bitDepth, int zoom, 
                          void* pDst, int dstOffset, int dstPitch, int canChangeZoom)
{
    pDst = (char*)pDst + zoom * dstOffset;

    switch (bitDepth) {
    case 16:
        switch (pVideo->palMode) {
        default:
        case VIDEO_PAL_FAST:
		case VIDEO_PAL_SCALE2X:
		case VIDEO_PAL_HQ2X:
            if (zoom == 2) copy_2x1_16(frame, pDst, dstPitch, pVideo->pRgbTable16);
            else           copy_1x05_16(frame, pDst, dstPitch, pVideo->pRgbTable16);
            break;
        case VIDEO_PAL_MONITOR:
            if (zoom == 2) copyMonitorPAL_2x1_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 1);
            else           copyPAL_1x05_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 0);
            break;
        case VIDEO_PAL_SHARP:
            if (zoom == 2) copySharpPAL_2x1_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 0);
            else           copy_1x05_16(frame, pDst, dstPitch, pVideo->pRgbTable16);
            break;
        case VIDEO_PAL_SHARP_NOISE:
            if (zoom == 2) copySharpPAL_2x1_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 1);
            else           copyPAL_1x05_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 1);
            break;
        case VIDEO_PAL_BLUR:
            if (zoom == 2) copyPAL_2x1_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 0);
            else           copyPAL_1x05_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 0);
            break;
        case VIDEO_PAL_BLUR_NOISE:
            if (zoom == 2) copyPAL_2x1_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 1);
            else           copyPAL_1x05_16(frame, pDst, dstPitch, pVideo->pRgbTable16, 1);
            break;
        }
        break;
    case 32:
        switch (pVideo->palMode) {
        default:
        case VIDEO_PAL_FAST:
		case VIDEO_PAL_SCALE2X:
		case VIDEO_PAL_HQ2X:
            if (zoom == 2) copy_2x1_32(frame, pDst, dstPitch, pVideo->pRgbTable32);
            else           copy_1x05_32(frame, pDst, dstPitch, pVideo->pRgbTable32);
            break;
        case VIDEO_PAL_MONITOR:
            if (zoom == 2) copyMonitorPAL_2x1_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 1);
            else           copyPAL_1x05_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 0);
            break;
        case VIDEO_PAL_SHARP:
            if (zoom == 2) copySharpPAL_2x1_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 0);
            else           copy_1x05_32(frame, pDst, dstPitch, pVideo->pRgbTable32);
            break;
        case VIDEO_PAL_SHARP_NOISE:
            if (zoom == 2) copySharpPAL_2x1_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 1);
            else           copyPAL_1x05_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 1);
            break;
        case VIDEO_PAL_BLUR:
            if (zoom == 2) copyPAL_2x1_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 0);
            else           copyPAL_1x05_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 0);
            break;
        case VIDEO_PAL_BLUR_NOISE:
            if (zoom == 2) copyPAL_2x1_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 1);
            else           copyPAL_1x05_32(frame, pDst, dstPitch, pVideo->pRgbTable32, 1);
            break;
        }
        break;
    }
    return zoom;
}

int videoRender(Video* pVideo, FrameBuffer* frame, int bitDepth, int zoom, 
                void* pDst, int dstOffset, int dstPitch, int canChangeZoom)
{
    if (frame == NULL) {
        return zoom;
    }

    if (frame->interlace != INTERLACE_NONE && pVideo->deInterlace) {
        frame = frameBufferDeinterlace(frame);
    }

    if (frame->lines <= 240) {
        zoom = videoRender240(pVideo, frame, bitDepth, zoom, pDst, dstOffset, dstPitch, canChangeZoom);
    }
    else {
        zoom = videoRender480(pVideo, frame, bitDepth, zoom, pDst, dstOffset, dstPitch, canChangeZoom);
    }

    switch (bitDepth) {
    case 16:
        if (pVideo->colorSaturationEnable) {
            colorSaturation_16(pDst, 320 * zoom, 240 * zoom, dstPitch, pVideo->colorSaturationWidth);
        }

        if (pVideo->scanLinesEnable) {
            scanLines_16(pDst, 320 * zoom, 240 * zoom, dstPitch, pVideo->scanLinesPct);
        }

        break;
    case 32:
        if (pVideo->colorSaturationEnable) {
            colorSaturation_32(pDst, 320 * zoom, 240 * zoom, dstPitch, pVideo->colorSaturationWidth);
        }

        if (pVideo->scanLinesEnable) {
            scanLines_32(pDst, 320 * zoom, 240 * zoom, dstPitch, pVideo->scanLinesPct);
        }
        break;
    }

    return zoom;
}
