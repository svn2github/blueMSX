/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoRender/VideoRender.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2004-12-06 21:13:39 $
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
#include "scalebit.h"
#include <stdlib.h>
#include <math.h>
#include <memory.h>
 
#define YCBCR_MASK 0x1F7DF
#define MAX_YCBCR_VALUE (1 << 17)

static UInt32 pRgbTableColor32[MAX_YCBCR_VALUE];
static UInt32 pRgbTableGreen32[MAX_YCBCR_VALUE];
static UInt32 pRgbTableWhite32[MAX_YCBCR_VALUE];
static UInt16 pRgbTableColor16[MAX_YCBCR_VALUE];
static UInt16 pRgbTableGreen16[MAX_YCBCR_VALUE];
static UInt16 pRgbTableWhite16[MAX_YCBCR_VALUE];

#define USE_RGB

UInt32 YJKtoYCbCrTable[32][64][64];

#ifndef USE_RGB
static UInt32 history[480][640];
#endif
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
#ifdef USE_RGB
			    int r = 255 * (y + j) / 31;
			    int g = 255 * (y + k) / 31;
			    int b = 255 * ((5 * y - 2 * j - k) / 4) / 31;

                r = MIN(255, MAX(0, r));
                g = MIN(255, MAX(0, g));
                b = MIN(255, MAX(0, b));
                YJKtoYCbCrTable[y][J][K] = videoGetColor(r, g, b);
#else
			    double r = 8.22 * (y + j);
			    double g = 8.22 * (y + k);
			    double b = 2.06 * (5 * y - 2 * j - k);
                int Y  = (int)(0.2989 * r + 0.5866 * g + 0.1145 * b);
                int Cb = (int)(b - Y);
                int Cr = (int)(r - Y);

                Y = MIN(255, MAX(0, Y));
                Cb = MIN(255, MAX(-256, Cb));
                Cr = MIN(255, MAX(-256, Cr));

                YJKtoYCbCrTable[y][J][K] = (Y / 8) | ((16 + (Cb / 16)) << 6) | ((16 + (Cr / 16)) << 12);
#endif
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
#ifndef USE_RGB
        int Y  = 8 * (YCbCr & 0x01f);
        int Cb = (int)((16 * (((YCbCr >> 6) & 0x1f) - 16)) * pVideo->saturation);
        int Cr = (int)((16 * (((YCbCr >> 12) & 0x1f) - 16)) * pVideo->saturation);

        int R = videoGamma(Cr + Y);
        int G = videoGamma((int)(Y - (0.1145/0.5866)*Cb - (0.2989/0.5866)*Cr));
        int B = videoGamma(Cb + Y);
        int L = videoGamma(Y);
#else
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
#endif
        pRgbTableColor32[YCbCr] = (R << 16) | (G << 8) | (B << 0);
        pRgbTableColor16[YCbCr] = ((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3);

        pRgbTableGreen32[YCbCr] = 0x100010 | (L << 8);
        pRgbTableGreen16[YCbCr] = 0x0801 | (UInt16)((L >> 2) << 5);

        pRgbTableWhite32[YCbCr] = (L << 16) | (L << 8) | (L << 0);
        pRgbTableWhite16[YCbCr] = (UInt16)(((L >> 3) << 11) | ((L >> 2) << 5) | (L >> 3));
    }
}


/*****************************************************************************
**
** PAL emulation rendering routines
**
******************************************************************************
*/
static void copySharpPAL_2x2_16(void* pSource, int srcWidth, int srcHeight, int* srcDoubleWidth, void* pDestination, 
                                int srcPitch, int dstPitch, UInt32 rnd, void* pRgbTable, int evenOddPage, int interlace)
{
    UInt16* pRgbTable16 = (UInt16*)pRgbTable;
    UInt32* pSrc        = (UInt32*)pSource;
    UInt16* pDst1       = (UInt16*)pDestination;
    UInt16* pDst2       = pDst1 + dstPitch / sizeof(UInt16);
    UInt16* pDst3       = pDst2;
    int w;
    int h;

    srcPitch *= 2;

    if (deInterlace && interlace) {
        // Draw even page
        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev1 = colCur;
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
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
                    pDst1[dstIndex++] = colRgb1 + noise;
                    pDst1[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                }
            }
            else {
                for (w = 0; w < srcWidth; w++) {
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
                    pDst1[dstIndex++] = colRgb1 + noise;
                    pDst1[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                    colCur = colNext;
                }
            }

            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst1 = (UInt16*)((UInt8*)pDst1 + dstPitch * 2);
        }

        // Draw odd page
        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev1 = colCur;
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
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
                    pDst2[dstIndex++] = colRgb1 + noise;
                    pDst2[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                }
            }
            else {
                for (w = 0; w < srcWidth; w++) {
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
                    pDst2[dstIndex++] = colRgb1 + noise;
                    pDst2[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                    colCur = colNext;
                }
            }

            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst2 = (UInt16*)((UInt8*)pDst2 + dstPitch * 2);
        }
    }
    else {
        if (evenOddPage) pSrc += 2 * srcWidth * srcHeight;

        if (interlace && evenOddPage) {
            pDst1 = (UInt16*)((UInt8*)pDst1 + dstPitch);
            pDst2 = (UInt16*)((UInt8*)pDst2 + dstPitch);
            srcHeight--;
        }

        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev1 = colCur;
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
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
                for (w = 0; w < srcWidth; w++) {
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
            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst1 = (UInt16*)((UInt8*)pDst1 + dstPitch * 2);
            pDst2 = (UInt16*)((UInt8*)pDst2 + dstPitch * 2);
        }
    }
}

static void copySharpPAL_2x2_32(void* pSource, int srcWidth, int srcHeight, int* srcDoubleWidth, void* pDestination, 
                                int srcPitch, int dstPitch, UInt32 rnd, void* pRgbTable, int evenOddPage, int interlace)
{
    UInt32* pRgbTable32 = (UInt32*)pRgbTable;
    UInt32* pSrc        = (UInt32*)pSource;
    UInt32* pDst1       = (UInt32*)pDestination;
    UInt32* pDst2       = pDst1 + dstPitch / sizeof(UInt32);
    UInt32* pDst3       = pDst2;
    int w;
    int h;

    srcPitch *= 2;

    if (deInterlace && interlace) {
        // Draw even page
        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev1 = colCur;
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
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
                    pDst1[dstIndex++] = colRgb1 + noise;
                    pDst1[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                }
            }
            else {
                for (w = 0; w < srcWidth; w++) {
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
                    pDst1[dstIndex++] = colRgb1 + noise;
                    pDst1[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                    colCur = colNext;
                }
            }

            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst1 = (UInt32*)((UInt8*)pDst1 + dstPitch * 2);
        }

        // Draw odd page
        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev1 = colCur;
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
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
                    pDst2[dstIndex++] = colRgb1 + noise;
                    pDst2[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                }
            }
            else {
                for (w = 0; w < srcWidth; w++) {
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
                    pDst2[dstIndex++] = colRgb1 + noise;
                    pDst2[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                    colCur = colNext;
                }
            }

            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst2 = (UInt32*)((UInt8*)pDst2 + dstPitch * 2);
        }
    }
    else {
        if (evenOddPage) pSrc += 2 * srcWidth * srcHeight;

        if (interlace && evenOddPage) {
            pDst1 = (UInt32*)((UInt8*)pDst1 + dstPitch);
            pDst2 = (UInt32*)((UInt8*)pDst2 + dstPitch);
            srcHeight--;
        }

        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev1 = colCur;
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
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
                for (w = 0; w < srcWidth; w++) {
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
            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst1 = (UInt32*)((UInt8*)pDst1 + dstPitch * 2);
            pDst2 = (UInt32*)((UInt8*)pDst2 + dstPitch * 2);
        }
    }
}

static void copyPAL_2x2_16(void* pSource, int srcWidth, int srcHeight, int* srcDoubleWidth, void* pDestination, 
                           int srcPitch, int dstPitch, UInt32 rnd, void* pRgbTable, UInt32 decay, int evenOddPage, int interlace)
{
    UInt16* pRgbTable16 = (UInt16*)pRgbTable;
    UInt32* pSrc        = (UInt32*)pSource;
    UInt16* pDst1       = (UInt16*)pDestination;
    UInt16* pDst2       = pDst1 + dstPitch / sizeof(UInt16);
    UInt16* pDst3       = pDst2;
    int w;
    int h;

    srcPitch *= 2;

    if (deInterlace && interlace) {
        // Draw even page
        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev1 = colCur;
            UInt32 colPrev2 = colCur;
            UInt32 colNext1 = colCur;
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
                    UInt32 colNext2;
                    UInt16 colRgb1;
                    UInt16 colRgb2;
                    UInt32 colTmp;
                    UInt16 noise;

                    colNext2 = pSrc[w++];
                    colTmp   = ((colNext2 + colPrev2) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colNext1) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colPrev1) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                    colRgb1  = pRgbTable16[colTmp];

                    colPrev2  = colPrev1;
                    colPrev1  = colCur;
                    colCur    = colNext1;
                    colNext1  = colNext2;

                    colNext2 = pSrc[w++];
                    colTmp   = ((colNext2 + colPrev2) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colPrev1) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colNext1) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                    colRgb2  = pRgbTable16[colTmp];

                    colPrev2  = colPrev1;
                    colPrev1 = colCur;
                    colCur   = colNext1;
                    colNext1  = colNext2;

                    noise = (UInt16)(rnd >> 31) * 0x0821;

                    pDst1[dstIndex++] = colRgb1 + noise;
                    pDst1[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                }
            }
            else {
                for (w = 0; w < srcWidth; w++) {
                    UInt32 colNext;
                    UInt16 colRgb1;
                    UInt16 colRgb2;
                    UInt32 colTmp;
                    UInt32 colLgt;
                    UInt16 noise;

                    colNext = pSrc[w];
#ifndef USE_RGB
                    colLgt  = colCur & 0x1f;
                    colTmp = history[h][w] - colLgt;
                    colLgt += ((-colTmp >> 24) & (decay * colTmp / 5)) - ((colTmp >> 24) & (decay * -colTmp / 16));
                    history[h][w] = colLgt;
                    colLgt += colCur & 0xffffffe0;
#else
                    colLgt = colCur;
#endif
                    colTmp  = ((colPrev1 + colNext) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colPrev1) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colLgt) >> 1) & YCBCR_MASK;
                    colRgb1 = pRgbTable16[colTmp];

                    colTmp  = ((colNext + colPrev1) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colNext) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colLgt) >> 1) & YCBCR_MASK;
                    colRgb2 = pRgbTable16[colTmp];

                    noise = (UInt16)(rnd >> 31) * 0x0821;

                    pDst1[dstIndex++] = colRgb1 + noise;
                    pDst1[dstIndex++] = colRgb2 + noise;

                    rnd *= 23;
                    colPrev1 = colCur;
                    colCur = colNext;
                }
            }

            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst1 = (UInt16*)((UInt8*)pDst1 + dstPitch * 2);
        }

        // Draw odd page
        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev1 = colCur;
            UInt32 colPrev2 = colCur;
            UInt32 colNext1 = colCur;
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
                    UInt32 colNext2;
                    UInt16 colRgb1;
                    UInt16 colRgb2;
                    UInt32 colTmp;
                    UInt16 noise;

                    colNext2 = pSrc[w++];
                    colTmp   = ((colNext2 + colPrev2) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colNext1) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colPrev1) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                    colRgb1  = pRgbTable16[colTmp];

                    colPrev2  = colPrev1;
                    colPrev1  = colCur;
                    colCur    = colNext1;
                    colNext1  = colNext2;

                    colNext2 = pSrc[w++];
                    colTmp   = ((colNext2 + colPrev2) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colPrev1) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colNext1) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                    colRgb2  = pRgbTable16[colTmp];

                    colPrev2  = colPrev1;
                    colPrev1 = colCur;
                    colCur   = colNext1;
                    colNext1  = colNext2;

                    noise = (UInt16)(rnd >> 31) * 0x0821;
                    pDst2[dstIndex++] = colRgb1 + noise;
                    pDst2[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                }
            }
            else {
                for (w = 0; w < srcWidth; w++) {
                    UInt32 colNext;
                    UInt16 colRgb1;
                    UInt16 colRgb2;
                    UInt32 colTmp;
                    UInt32 colLgt;
                    UInt16 noise;

                    colNext = pSrc[w];

#ifndef USE_RGB
                    colLgt  = colCur & 0x1f;
                    colTmp = history[h][w] - colLgt;
                    colLgt += ((-colTmp >> 24) & (decay * colTmp / 5)) - ((colTmp >> 24) & (decay * -colTmp / 16));
                    history[h][w] = colLgt;
                    colLgt += colCur & 0xffffffe0;
#else
                    colLgt = colCur;
#endif
                    colTmp  = ((colPrev1 + colNext) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colPrev1) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colLgt) >> 1) & YCBCR_MASK;
                    colRgb1 = pRgbTable16[colTmp];

                    colTmp  = ((colNext + colPrev1) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colNext) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colLgt) >> 1) & YCBCR_MASK;
                    colRgb2 = pRgbTable16[colTmp];

                    noise = (UInt16)(rnd >> 31) * 0x0821;
                    pDst2[dstIndex++] = colRgb1 + noise;
                    pDst2[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                    colPrev1 = colCur;
                    colCur = colNext;
                }
            }

            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst2 = (UInt16*)((UInt8*)pDst2 + dstPitch * 2);
        }
    }
    else {
        if (evenOddPage) pSrc += 2 * srcWidth * srcHeight;

        if (interlace && evenOddPage) {
            pDst1 = (UInt16*)((UInt8*)pDst1 + dstPitch);
            pDst2 = (UInt16*)((UInt8*)pDst2 + dstPitch);
            srcHeight--;
        }

        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev1 = colCur;
            UInt32 colPrev2 = colCur;
            UInt32 colNext1 = colCur;
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
                    UInt32 colNext2;
                    UInt16 colRgb1;
                    UInt16 colRgb2;
                    UInt32 colTmp;
                    UInt16 noise;

                    colNext2 = pSrc[w++];
                    colTmp   = ((colNext2 + colPrev2) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colNext1) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colPrev1) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                    colRgb1  = pRgbTable16[colTmp];

                    colPrev2  = colPrev1;
                    colPrev1  = colCur;
                    colCur    = colNext1;
                    colNext1  = colNext2;

                    colNext2 = pSrc[w++];
                    colTmp   = ((colNext2 + colPrev2) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colPrev1) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colNext1) >> 1) & YCBCR_MASK;
                    colTmp   = ((colTmp   + colCur) >> 1) & YCBCR_MASK;
                    colRgb2  = pRgbTable16[colTmp];

                    colPrev2  = colPrev1;
                    colPrev1 = colCur;
                    colCur   = colNext1;
                    colNext1  = colNext2;

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
                for (w = 0; w < srcWidth; w++) {
                    UInt32 colNext;
                    UInt16 colRgb1;
                    UInt16 colRgb2;
                    UInt32 colTmp;
                    UInt32 colLgt;
                    UInt16 noise;

                    colNext = pSrc[w];

#ifndef USE_RGB
                    colLgt  = colCur & 0x1f;
                    colTmp = history[h][w] - colLgt;
                    colLgt += ((-colTmp >> 24) & (decay * colTmp / 5)) - ((colTmp >> 24) & (decay * -colTmp / 16));
                    history[h][w] = colLgt;
                    colLgt += colCur & 0xffffffe0;
#else
                    colLgt = colCur;
#endif
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
            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst1 = (UInt16*)((UInt8*)pDst1 + dstPitch * 2);
            pDst2 = (UInt16*)((UInt8*)pDst2 + dstPitch * 2);
        }
    }
}

static void copyMonitorPAL_2x2_32(void* pSource, int srcWidth, int srcHeight, int* srcDoubleWidth, void* pDestination, 
                                  int srcPitch, int dstPitch, UInt32 rnd, void* pRgbTable, int evenOddPage, int interlace)
{
    UInt32* pRgbTable32 = (UInt32*)pRgbTable;
    UInt32* pSrc        = (UInt32*)pSource;
    UInt32* pDst1       = (UInt32*)pDestination;
    UInt32* pDst2       = pDst1 + dstPitch / sizeof(UInt32);
    UInt32* pDst3       = pDst2;
    int w;
    int h;

    srcPitch *= 2;

    if (deInterlace && interlace) {
        // Draw even page
        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev1 = colCur;
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
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
                    pDst1[dstIndex++] = colRgb1 + noise;
                    pDst1[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                }
            }
            else {
                for (w = 0; w < srcWidth; w++) {
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
                    pDst1[dstIndex++] = colRgb1 + noise;
                    pDst1[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                    colCur = colNext;
                }
            }

            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst1 = (UInt32*)((UInt8*)pDst1 + dstPitch * 2);
        }

        // Draw odd page
        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev1 = colCur;
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
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
                    pDst2[dstIndex++] = colRgb1 + noise;
                    pDst2[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                }
            }
            else {
                for (w = 0; w < srcWidth; w++) {
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
                    pDst2[dstIndex++] = colRgb1 + noise;
                    pDst2[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                    colCur = colNext;
                }
            }

            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst2 = (UInt32*)((UInt8*)pDst2 + dstPitch * 2);
        }
    }
    else {
        if (evenOddPage) pSrc += 2 * srcWidth * srcHeight;

        if (interlace && evenOddPage) {
            pDst1 = (UInt32*)((UInt8*)pDst1 + dstPitch);
            pDst2 = (UInt32*)((UInt8*)pDst2 + dstPitch);
            srcHeight--;
        }

        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev1 = colCur;
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
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
                for (w = 0; w < srcWidth; w++) {
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

            pDst3 = pDst2;
            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst1 = (UInt32*)((UInt8*)pDst1 + dstPitch * 2);
            pDst2 = (UInt32*)((UInt8*)pDst2 + dstPitch * 2);
        }
    }
}

static void copyPAL_2x2_32(void* pSource, int srcWidth, int srcHeight, int* srcDoubleWidth, void* pDestination, 
                           int srcPitch, int dstPitch, UInt32 rnd, void* pRgbTable, UInt32 decay, int evenOddPage, int interlace)
{
    UInt32* pRgbTable32 = (UInt32*)pRgbTable;
    UInt32* pSrc        = (UInt32*)pSource;
    UInt32* pDst1       = (UInt32*)pDestination;
    UInt32* pDst2       = pDst1 + dstPitch / sizeof(UInt32);
    UInt32* pDst3       = pDst2;
    int w;
    int h;

    srcPitch *= 2;

    if (deInterlace && interlace) {
        // Draw even page
        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev2 = colCur;
            UInt32 colPrev1 = colCur;
            UInt32 colNext1 = colCur;
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
                    UInt32 colNext2;
                    UInt32 colRgb1;
                    UInt32 colRgb2;
                    UInt32 colTmp;
                    UInt32 colLgt;
                    UInt32 noise;

                    colNext2 = pSrc[w];

#ifndef USE_RGB
                    colLgt  = colCur & 0x1f;
                    noise = history[h][w] - colLgt;
                    colLgt += ((-noise >> 24) & (decay * noise / 5)) - ((noise >> 24) & (decay * -noise / 16));
                    history[h][w] = colLgt;
                    colLgt += colCur & 0xffffffe0;
#else
                    colLgt = colCur;
#endif
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

#ifndef USE_RGB
                    colLgt  = colCur & 0x1f;
                    noise = history[h][w] - colLgt;
                    colLgt += ((-noise >> 24) & (decay * noise / 5)) - ((noise >> 24) & (decay * -noise / 16));
                    history[h][w] = colLgt;
                    colLgt += colCur & 0xffffffe0;
#else
                    colLgt = colCur;
#endif
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

                    pDst1[dstIndex++] = colRgb1 + noise;
                    pDst1[dstIndex++] = colRgb2 + noise;

                    rnd *= 23;
                }
            }
            else {
                for (w = 0; w < srcWidth; w++) {
                    UInt32 colNext;
                    UInt32 colRgb1;
                    UInt32 colRgb2;
                    UInt32 colTmp;
                    UInt32 colLgt;
                    UInt32 noise;

                    colNext = pSrc[w];

#ifndef USE_RGB
                    colLgt  = colCur & 0x1f;
                    noise = history[h][w] - colLgt;
                    colLgt += ((-noise >> 24) & (decay * noise / 5)) - ((noise >> 24) & (decay * -noise / 16));
                    history[h][w] = colLgt;
                    colLgt += colCur & 0xffffffe0;
#else
                    colLgt = colCur;
#endif
                    colTmp  = ((colPrev1 + colNext) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colPrev1) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colLgt) >> 1) & YCBCR_MASK;
                    colRgb1 = pRgbTable32[colTmp];

                    colTmp  = ((colNext + colPrev1) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colNext) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colLgt) >> 1) & YCBCR_MASK;
                    colRgb2 = pRgbTable32[colTmp];

                    noise = (rnd >> 29) * 0x10101;
                    pDst1[dstIndex++] = colRgb1 + noise;
                    pDst1[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                    colPrev1 = colCur;
                    colCur = colNext;
                }
            }

            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst1 = (UInt32*)((UInt8*)pDst1 + dstPitch * 2);
        }

        // Draw odd page
        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev2 = colCur;
            UInt32 colPrev1 = colCur;
            UInt32 colNext1 = colCur;
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
                    UInt32 colNext2;
                    UInt32 colRgb1;
                    UInt32 colRgb2;
                    UInt32 colTmp;
                    UInt32 colLgt;
                    UInt32 noise;

                    colNext2 = pSrc[w];

#ifndef USE_RGB
                    colLgt  = colCur & 0x1f;
                    noise = history[h][w] - colLgt;
                    colLgt += ((-noise >> 24) & (decay * noise / 5)) - ((noise >> 24) & (decay * -noise / 16));
                    history[h][w] = colLgt;
                    colLgt += colCur & 0xffffffe0;
#else
                    colLgt = colCur;
#endif
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

#ifndef USE_RGB
                    colLgt  = colCur & 0x1f;
                    noise = history[h][w] - colLgt;
                    colLgt += ((-noise >> 24) & (decay * noise / 5)) - ((noise >> 24) & (decay * -noise / 16));
                    history[h][w] = colLgt;
                    colLgt += colCur & 0xffffffe0;
#else
                    colLgt = colCur;
#endif
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
                    pDst2[dstIndex++] = colRgb1 + noise;
                    pDst2[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                }
            }
            else {
                for (w = 0; w < srcWidth; w++) {
                    UInt32 colNext;
                    UInt32 colRgb1;
                    UInt32 colRgb2;
                    UInt32 colTmp;
                    UInt32 colLgt;
                    UInt32 noise;

                    colNext = pSrc[w];

#ifndef USE_RGB
                    colLgt  = colCur & 0x1f;
                    noise = history[h][w] - colLgt;
                    colLgt += ((-noise >> 24) & (decay * noise / 5)) - ((noise >> 24) & (decay * -noise / 16));
                    history[h][w] = colLgt;
                    colLgt += colCur & 0xffffffe0;
#else
                    colLgt = colCur;
#endif
                    colTmp  = ((colPrev1 + colNext) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colPrev1) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colLgt) >> 1) & YCBCR_MASK;
                    colRgb1 = pRgbTable32[colTmp];

                    colTmp  = ((colNext + colPrev1) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colNext) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colLgt) >> 1) & YCBCR_MASK;
                    colRgb2 = pRgbTable32[colTmp];

                    noise = (rnd >> 29) * 0x10101;
                    pDst2[dstIndex++] = colRgb1 + noise;
                    pDst2[dstIndex++] = colRgb2 + noise;
                    rnd *= 23;
                    colPrev1 = colCur;
                    colCur = colNext;
                }
            }

            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst2 = (UInt32*)((UInt8*)pDst2 + dstPitch * 2);
        }
    }
    else {
        if (evenOddPage) pSrc += 2 * srcWidth * srcHeight;

        if (interlace && evenOddPage) {
            pDst1 = (UInt32*)((UInt8*)pDst1 + dstPitch);
            pDst2 = (UInt32*)((UInt8*)pDst2 + dstPitch);
            srcHeight--;
        }

        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev2 = colCur;
            UInt32 colPrev1 = colCur;
            UInt32 colNext1 = colCur;
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
                    UInt32 colNext2;
                    UInt32 colRgb1;
                    UInt32 colRgb2;
                    UInt32 colTmp;
                    UInt32 colLgt;
                    UInt32 noise;

                    colNext2 = pSrc[w];

#ifndef USE_RGB
                    colLgt  = colCur & 0x1f;
                    noise = history[h][w] - colLgt;
                    colLgt += ((-noise >> 24) & (decay * noise / 5)) - ((noise >> 24) & (decay * -noise / 16));
                    history[h][w] = colLgt;
                    colLgt += colCur & 0xffffffe0;
#else
                    colLgt = colCur;
#endif
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

#ifndef USE_RGB
                    colLgt  = colCur & 0x1f;
                    noise = history[h][w] - colLgt;
                    colLgt += ((-noise >> 24) & (decay * noise / 5)) - ((noise >> 24) & (decay * -noise / 16));
                    history[h][w] = colLgt;
                    colLgt += colCur & 0xffffffe0;
#else
                    colLgt = colCur;
#endif
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
                for (w = 0; w < srcWidth; w++) {
                    UInt32 colNext;
                    UInt32 colRgb1;
                    UInt32 colRgb2;
                    UInt32 colTmp;
                    UInt32 colLgt;
                    UInt32 noise;

                    colNext = pSrc[w];

#ifndef USE_RGB
                    colLgt  = colCur & 0x1f;
                    noise = history[h][w] - colLgt;
                    colLgt += ((-noise >> 24) & (decay * noise / 5)) - ((noise >> 24) & (decay * -noise / 16));
                    history[h][w] = colLgt;
                    colLgt += colCur & 0xffffffe0;
#else
                    colLgt = colCur;
#endif

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
            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst1 = (UInt32*)((UInt8*)pDst1 + dstPitch * 2);
            pDst2 = (UInt32*)((UInt8*)pDst2 + dstPitch * 2);
        }
    }
}

static void copyPAL_1x1_16(void* pSource, int srcWidth, int srcHeight, int* srcDoubleWidth, void* pDestination, 
                           int srcPitch, int dstPitch, UInt32 rnd, void* pRgbTable, int evenOddPage, int interlace)
{
    UInt16* pRgbTable16 = (UInt16*)pRgbTable;
    UInt32* pSrc        = (UInt32*)pSource;
    UInt32 *pSrc2       = pSrc + 2 * srcWidth * srcHeight;
    UInt16* pDst        = (UInt16*)pDestination;
    int w;
    int h;

    srcPitch *= 2;

    if (interlace) {
        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev = colCur;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < srcWidth; w++) {
                    UInt32 colNext = (((((pSrc[2 * w] + pSrc[2 * w + 1]) >> 1) & YCBCR_MASK) >> 1) + ((((pSrc2[2 * w] + pSrc2[2 * w + 1]) >> 1) & YCBCR_MASK) >> 1)) & YCBCR_MASK;
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
                for (w = 0; w < srcWidth; w++) {
                    UInt32 colNext = ((pSrc[w] + pSrc2[w]) >> 1) & YCBCR_MASK;
                    UInt32 colTmp;

                    colTmp  = ((colPrev + colNext) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colCur) >> 1) & YCBCR_MASK;

                    pDst[w] = pRgbTable16[colTmp] + (UInt16)(rnd >> 31)  * 0x0821;

                    rnd *= 23;
                    colPrev = colCur;
                    colCur = colNext;
                }
            }

            pSrc = (UInt32*)((UInt8*)pSrc + srcPitch);
            pSrc2 = (UInt32*)((UInt8*)pSrc2 + srcPitch);
            pDst = (UInt16*) ((UInt8*)pDst + dstPitch);
        }
    }
    else {
        if (evenOddPage) pSrc += 2 * srcWidth * srcHeight;
        
        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev = colCur;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < srcWidth; w++) {
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
                for (w = 0; w < srcWidth; w++) {
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

            pSrc = (UInt32*)((UInt8*)pSrc + srcPitch);
            pDst = (UInt16*) ((UInt8*)pDst + dstPitch);
        }
    }
}

static void copyPAL_1x1_32(void* pSource, int srcWidth, int srcHeight, int* srcDoubleWidth, void* pDestination, 
                           int srcPitch, int dstPitch, UInt32 rnd, void* pRgbTable, int evenOddPage, int interlace)
{
    UInt32* pRgbTable32 = (UInt32*)pRgbTable;
    UInt32* pSrc        = (UInt32*)pSource;
    UInt32 *pSrc2       = pSrc + 2 * srcWidth * srcHeight;
    UInt32* pDst        = (UInt32*)pDestination;
    int w;
    int h;

    srcPitch *= 2;

    if (interlace) {
        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev = colCur;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < srcWidth; w++) {
                    UInt32 colNext = (((((pSrc[2 * w] + pSrc[2 * w + 1]) >> 1) & YCBCR_MASK) >> 1) + ((((pSrc2[2 * w] + pSrc2[2 * w + 1]) >> 1) & YCBCR_MASK) >> 1)) & YCBCR_MASK;
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
                for (w = 0; w < srcWidth; w++) {
                    UInt32 colNext = ((pSrc[w] + pSrc2[w]) >> 1) & YCBCR_MASK;
                    UInt32 colTmp;

                    colTmp  = ((colPrev + colNext) >> 1) & YCBCR_MASK;
                    colTmp  = ((colTmp + colCur) >> 1) & YCBCR_MASK;

                    pDst[w] = pRgbTable32[colTmp] + (rnd >> 31)  * 0x10101;

                    rnd *= 23;
                    colPrev = colCur;
                    colCur = colNext;
                }
            }

            pSrc = (UInt32*)((UInt8*)pSrc + srcPitch);
            pSrc2 = (UInt32*)((UInt8*)pSrc2 + srcPitch);
            pDst = (UInt32*)((UInt8*)pDst + dstPitch);
        }
    }
    else {
        if (evenOddPage) pSrc += 2 * srcWidth * srcHeight;

        for (h = 0; h < srcHeight; h++) {
            UInt32 colCur = pSrc[0];
            UInt32 colPrev = colCur;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < srcWidth; w++) {
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
                for (w = 0; w < srcWidth; w++) {
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

            pSrc = (UInt32*)((UInt8*)pSrc + srcPitch);
            pDst = (UInt32*)((UInt8*)pDst + dstPitch);
        }
    }
}


/*****************************************************************************
**
** Fast rendering routines
**
******************************************************************************
*/
static void copy_1x1_16(void* pSource, int srcWidth, int srcHeight, int* srcDoubleWidth, void* pDestination, 
                        int srcPitch, int dstPitch, UInt32 rnd, void* pRgbTable, int evenOddPage, int interlace)
{
    UInt16* pRgbTable16 = (UInt16*)pRgbTable;
    UInt32* pSrc        = (UInt32*)pSource;
    UInt32 *pSrc2       = pSrc + 2 * srcWidth * srcHeight;
    UInt16* pDst        = (UInt16*)pDestination;
    int w;
    int h;

    srcWidth /= 8;
    srcPitch *= 2;

    if (interlace) {
        for (h = 0; h < srcHeight; h++) {
            if (srcDoubleWidth[h]) {
                for (w = 0; w < srcWidth; w++) {
                    pDst[0] = pRgbTable16[(((((pSrc[0] + pSrc[1]) >> 1) & YCBCR_MASK) + (((pSrc2[0] + pSrc2[1]) >> 1) & YCBCR_MASK)) >> 1) & YCBCR_MASK];
                    pDst[1] = pRgbTable16[(((((pSrc[2] + pSrc[3]) >> 1) & YCBCR_MASK) + (((pSrc2[2] + pSrc2[3]) >> 1) & YCBCR_MASK)) >> 1) & YCBCR_MASK];
                    pDst[2] = pRgbTable16[(((((pSrc[4] + pSrc[5]) >> 1) & YCBCR_MASK) + (((pSrc2[4] + pSrc2[5]) >> 1) & YCBCR_MASK)) >> 1) & YCBCR_MASK];
                    pDst[3] = pRgbTable16[(((((pSrc[6] + pSrc[7]) >> 1) & YCBCR_MASK) + (((pSrc2[6] + pSrc2[7]) >> 1) & YCBCR_MASK)) >> 1) & YCBCR_MASK];
                    pDst[4] = pRgbTable16[(((((pSrc[8] + pSrc[9]) >> 1) & YCBCR_MASK) + (((pSrc2[8] + pSrc2[9]) >> 1) & YCBCR_MASK)) >> 1) & YCBCR_MASK];
                    pDst[5] = pRgbTable16[(((((pSrc[10] + pSrc[11]) >> 1) & YCBCR_MASK) + (((pSrc2[10] + pSrc2[11]) >> 1) & YCBCR_MASK)) >> 1) & YCBCR_MASK];
                    pDst[6] = pRgbTable16[(((((pSrc[12] + pSrc[13]) >> 1) & YCBCR_MASK) + (((pSrc2[12] + pSrc2[13]) >> 1) & YCBCR_MASK)) >> 1) & YCBCR_MASK];
                    pDst[7] = pRgbTable16[(((((pSrc[14] + pSrc[15]) >> 1) & YCBCR_MASK) + (((pSrc2[14] + pSrc2[15]) >> 1) & YCBCR_MASK)) >> 1) & YCBCR_MASK];
                    
                    pSrc += 16;
                    pSrc2 += 16;
                    pDst += 8;
                }

                pSrc -= 16 * srcWidth;
                pSrc2 -= 16 * srcWidth;
                pDst -= 8 * srcWidth;
            }
            else {
                for (w = 0; w < srcWidth; w ++) {
                    pDst[0] = pRgbTable16[((pSrc[0] + pSrc2[0]) >> 1) & YCBCR_MASK];
                    pDst[1] = pRgbTable16[((pSrc[1] + pSrc2[1]) >> 1) & YCBCR_MASK];
                    pDst[2] = pRgbTable16[((pSrc[2] + pSrc2[2]) >> 1) & YCBCR_MASK];
                    pDst[3] = pRgbTable16[((pSrc[3] + pSrc2[3]) >> 1) & YCBCR_MASK];
                    pDst[4] = pRgbTable16[((pSrc[4] + pSrc2[4]) >> 1) & YCBCR_MASK];
                    pDst[5] = pRgbTable16[((pSrc[5] + pSrc2[5]) >> 1) & YCBCR_MASK];
                    pDst[6] = pRgbTable16[((pSrc[6] + pSrc2[6]) >> 1) & YCBCR_MASK];
                    pDst[7] = pRgbTable16[((pSrc[7] + pSrc2[7]) >> 1) & YCBCR_MASK];
                    
                    pSrc += 8;
                    pSrc2 += 8;
                    pDst += 8;
                }

                pSrc -= 8 * srcWidth;
                pSrc2 -= 8 * srcWidth;
                pDst -= 8 * srcWidth;
            }

            pSrc = (UInt32*)((UInt8*)pSrc + srcPitch);
            pSrc2 = (UInt32*)((UInt8*)pSrc2 + srcPitch);
            pDst = (UInt16*)((UInt8*)pDst + dstPitch);
        }
    }
    else {
        if (evenOddPage) pSrc += 2 * 8 * srcWidth * srcHeight;
        for (h = 0; h < srcHeight; h++) {
            if (srcDoubleWidth[h]) {
                for (w = 0; w < srcWidth; w++) {
                    pDst[0] = pRgbTable16[((pSrc[0] + pSrc[1]) >> 1) & YCBCR_MASK];
                    pDst[1] = pRgbTable16[((pSrc[2] + pSrc[3]) >> 1) & YCBCR_MASK];
                    pDst[2] = pRgbTable16[((pSrc[4] + pSrc[5]) >> 1) & YCBCR_MASK];
                    pDst[3] = pRgbTable16[((pSrc[6] + pSrc[7]) >> 1) & YCBCR_MASK];
                    pDst[4] = pRgbTable16[((pSrc[8] + pSrc[9]) >> 1) & YCBCR_MASK];
                    pDst[5] = pRgbTable16[((pSrc[10] + pSrc[11]) >> 1) & YCBCR_MASK];
                    pDst[6] = pRgbTable16[((pSrc[12] + pSrc[13]) >> 1) & YCBCR_MASK];
                    pDst[7] = pRgbTable16[((pSrc[14] + pSrc[15]) >> 1) & YCBCR_MASK];
                    
                    pSrc += 16;
                    pDst += 8;
                }

                pSrc -= 16 * srcWidth;
                pDst -= 8 * srcWidth;
            }
            else {
                for (w = 0; w < srcWidth; w ++) {
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

                pSrc -= 8 * srcWidth;
                pDst -= 8 * srcWidth;
            }

            pSrc = (UInt32*)((UInt8*)pSrc + srcPitch);
            pDst = (UInt16*)((UInt8*)pDst + dstPitch);
        }
    }
}

static void copy_1x1_32(void* pSource, int srcWidth, int srcHeight, int* srcDoubleWidth, void* pDestination, 
                        int srcPitch, int dstPitch, UInt32 rnd, void* pRgbTable, int evenOddPage, int interlace)
{
    UInt32* pRgbTable32 = (UInt32*)pRgbTable;
    UInt32* pSrc        = (UInt32*)pSource;
    UInt32 *pSrc2       = pSrc + 2 * srcWidth * srcHeight;
    UInt32* pDst        = (UInt32*)pDestination;
    int w;
    int h;

    srcWidth /= 8;

    srcPitch *= 2;

    if (interlace) {
        for (h = 0; h < srcHeight; h++) {
            if (srcDoubleWidth[h]) {
                for (w = 0; w < srcWidth; w++) {
                    pDst[0] = pRgbTable32[(((((pSrc[0] + pSrc[1]) >> 1) & YCBCR_MASK) + (((pSrc2[0] + pSrc2[1]) >> 1) & YCBCR_MASK)) >> 1) & YCBCR_MASK];
                    pDst[1] = pRgbTable32[(((((pSrc[2] + pSrc[3]) >> 1) & YCBCR_MASK) + (((pSrc2[2] + pSrc2[3]) >> 1) & YCBCR_MASK)) >> 1) & YCBCR_MASK];
                    pDst[2] = pRgbTable32[(((((pSrc[4] + pSrc[5]) >> 1) & YCBCR_MASK) + (((pSrc2[4] + pSrc2[5]) >> 1) & YCBCR_MASK)) >> 1) & YCBCR_MASK];
                    pDst[3] = pRgbTable32[(((((pSrc[6] + pSrc[7]) >> 1) & YCBCR_MASK) + (((pSrc2[6] + pSrc2[7]) >> 1) & YCBCR_MASK)) >> 1) & YCBCR_MASK];
                    pDst[4] = pRgbTable32[(((((pSrc[8] + pSrc[9]) >> 1) & YCBCR_MASK) + (((pSrc2[8] + pSrc2[9]) >> 1) & YCBCR_MASK)) >> 1) & YCBCR_MASK];
                    pDst[5] = pRgbTable32[(((((pSrc[10] + pSrc[11]) >> 1) & YCBCR_MASK) + (((pSrc2[10] + pSrc2[11]) >> 1) & YCBCR_MASK)) >> 1) & YCBCR_MASK];
                    pDst[6] = pRgbTable32[(((((pSrc[12] + pSrc[13]) >> 1) & YCBCR_MASK) + (((pSrc2[12] + pSrc2[13]) >> 1) & YCBCR_MASK)) >> 1) & YCBCR_MASK];
                    pDst[7] = pRgbTable32[(((((pSrc[14] + pSrc[15]) >> 1) & YCBCR_MASK) + (((pSrc2[14] + pSrc2[15]) >> 1) & YCBCR_MASK)) >> 1) & YCBCR_MASK];
                    
                    pSrc += 16;
                    pSrc2 += 16;
                    pDst += 8;
                }
                pSrc -= 16 * srcWidth;
                pSrc2 -= 16 * srcWidth;
                pDst -= 8 * srcWidth;
            }
            else {
                for (w = 0; w < srcWidth; w++) {
                    pDst[0] = pRgbTable32[((pSrc[0] + pSrc2[0]) >> 1) & YCBCR_MASK];
                    pDst[1] = pRgbTable32[((pSrc[1] + pSrc2[1]) >> 1) & YCBCR_MASK];
                    pDst[2] = pRgbTable32[((pSrc[2] + pSrc2[2]) >> 1) & YCBCR_MASK];
                    pDst[3] = pRgbTable32[((pSrc[3] + pSrc2[3]) >> 1) & YCBCR_MASK];
                    pDst[4] = pRgbTable32[((pSrc[4] + pSrc2[4]) >> 1) & YCBCR_MASK];
                    pDst[5] = pRgbTable32[((pSrc[5] + pSrc2[5]) >> 1) & YCBCR_MASK];
                    pDst[6] = pRgbTable32[((pSrc[6] + pSrc2[6]) >> 1) & YCBCR_MASK];
                    pDst[7] = pRgbTable32[((pSrc[7] + pSrc2[7]) >> 1) & YCBCR_MASK];
                    
                    pSrc += 8;
                    pSrc2 += 8;
                    pDst += 8;
                }
                pSrc -= 8 * srcWidth;
                pSrc2 -= 8 * srcWidth;
                pDst -= 8 * srcWidth;
            }        
            pSrc = (UInt32*)((UInt8*)pSrc + srcPitch);
            pSrc2 = (UInt32*)((UInt8*)pSrc2 + srcPitch);
            pDst = (UInt32*)((UInt8*)pDst + dstPitch);
        }
    }
    else {
        if (evenOddPage) pSrc += 2 * 8 * srcWidth * srcHeight;
        for (h = 0; h < srcHeight; h++) {
            if (srcDoubleWidth[h]) {
                for (w = 0; w < srcWidth; w++) {
                    pDst[0] = pRgbTable32[((pSrc[0] + pSrc[1]) >> 1) & YCBCR_MASK];
                    pDst[1] = pRgbTable32[((pSrc[2] + pSrc[3]) >> 1) & YCBCR_MASK];
                    pDst[2] = pRgbTable32[((pSrc[4] + pSrc[5]) >> 1) & YCBCR_MASK];
                    pDst[3] = pRgbTable32[((pSrc[6] + pSrc[7]) >> 1) & YCBCR_MASK];
                    pDst[4] = pRgbTable32[((pSrc[8] + pSrc[9]) >> 1) & YCBCR_MASK];
                    pDst[5] = pRgbTable32[((pSrc[10] + pSrc[11]) >> 1) & YCBCR_MASK];
                    pDst[6] = pRgbTable32[((pSrc[12] + pSrc[13]) >> 1) & YCBCR_MASK];
                    pDst[7] = pRgbTable32[((pSrc[14] + pSrc[15]) >> 1) & YCBCR_MASK];
                    
                    pSrc += 16;
                    pDst += 8;
                }
                pSrc -= 16 * srcWidth;
                pDst -= 8 * srcWidth;
            }
            else {
                for (w = 0; w < srcWidth; w++) {
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
                pSrc -= 8 * srcWidth;
                pDst -= 8 * srcWidth;
            }        
            pSrc = (UInt32*)((UInt8*)pSrc + srcPitch);
            pDst = (UInt32*)((UInt8*)pDst + dstPitch);
        }
    }
}

static void copy_2x2_16(void* pSource, int srcWidth, int srcHeight, int* srcDoubleWidth, void* pDestination, 
                        int srcPitch, int dstPitch, UInt32 rnd, void* pRgbTable, int evenOddPage, int interlace)
{
    UInt16* pRgbTable16 = (UInt16*)pRgbTable;
    UInt32* pSrc        = (UInt32*)pSource;
    UInt16* pDst1       = (UInt16*)pDestination;
    UInt16* pDst2       = pDst1 + dstPitch / sizeof(UInt16);
    int w;
    int h;    

    srcPitch *= 2;

    if (deInterlace && interlace) {
        UInt32 *pSrc2 = pSrc + 2 * srcWidth * srcHeight;

        for (h = 0; h < srcHeight; h++) {
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
                    pDst1[dstIndex]   = pRgbTable16[pSrc[w]];
                    pDst2[dstIndex++] = pRgbTable16[pSrc2[w++]];
                    
                    pDst1[dstIndex]   = pRgbTable16[pSrc[w]];
                    pDst2[dstIndex++] = pRgbTable16[pSrc2[w++]];
                    
                    pDst1[dstIndex]   = pRgbTable16[pSrc[w]];
                    pDst2[dstIndex++] = pRgbTable16[pSrc2[w++]];
                    
                    pDst1[dstIndex]   = pRgbTable16[pSrc[w]];
                    pDst2[dstIndex++] = pRgbTable16[pSrc2[w++]];
                }
            }
            else {
                for (w = 0; w < srcWidth;) {
                    UInt16 col1 = pRgbTable16[pSrc[w]];
                    UInt16 col2 = pRgbTable16[pSrc2[w++]];
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col2;
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col2;

                    col1 = pRgbTable16[pSrc[w]];
                    col2 = pRgbTable16[pSrc2[w++]];
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col2;
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col2;

                    col1 = pRgbTable16[pSrc[w]];
                    col2 = pRgbTable16[pSrc2[w++]];
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col2;
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col2;

                    col1 = pRgbTable16[pSrc[w]];
                    col2 = pRgbTable16[pSrc2[w++]];
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col2;
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col2;
                }
            }

            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pSrc2 = (UInt32*)((UInt8*)pSrc2 + srcPitch);
            pDst1 = (UInt16*)((UInt8*)pDst1 + dstPitch * 2);
            pDst2 = (UInt16*)((UInt8*)pDst2 + dstPitch * 2);
        }
    }
    else {
        if (evenOddPage) pSrc += 2 * srcWidth * srcHeight;

        if (interlace && evenOddPage) {
            pDst1 = (UInt16*)((UInt8*)pDst1 + dstPitch);
            pDst2 = (UInt16*)((UInt8*)pDst2 + dstPitch);
            srcHeight--;
        }

        for (h = 0; h < srcHeight; h++) {
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
                    UInt16 col1 = pRgbTable16[pSrc[w++]];
                    UInt16 col2 = pRgbTable16[pSrc[w++]];
                    UInt16 col3 = pRgbTable16[pSrc[w++]];
                    UInt16 col4 = pRgbTable16[pSrc[w++]];

                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col1;
                    
                    pDst1[dstIndex]   = col2;
                    pDst2[dstIndex++] = col2;
                    
                    pDst1[dstIndex]   = col3;
                    pDst2[dstIndex++] = col3;
                    
                    pDst1[dstIndex]   = col4;
                    pDst2[dstIndex++] = col4;
                }
            }
            else {
                for (w = 0; w < srcWidth;) {
                    UInt16 col1 = pRgbTable16[pSrc[w++]];
                    UInt16 col2 = pRgbTable16[pSrc[w++]];
                    UInt16 col3 = pRgbTable16[pSrc[w++]];
                    UInt16 col4 = pRgbTable16[pSrc[w++]];

                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col1;
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col1;
                    
                    pDst1[dstIndex]   = col2;
                    pDst2[dstIndex++] = col2;
                    pDst1[dstIndex]   = col2;
                    pDst2[dstIndex++] = col2;
                    
                    pDst1[dstIndex]   = col3;
                    pDst2[dstIndex++] = col3;
                    pDst1[dstIndex]   = col3;
                    pDst2[dstIndex++] = col3;
                    
                    pDst1[dstIndex]   = col4;
                    pDst2[dstIndex++] = col4;
                    pDst1[dstIndex]   = col4;
                    pDst2[dstIndex++] = col4;
                }
            }

            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst1 = (UInt16*)((UInt8*)pDst1 + dstPitch * 2);
            pDst2 = (UInt16*)((UInt8*)pDst2 + dstPitch * 2);
        }
    }
}

void copy_2x2_32(void* pSource, int srcWidth, int srcHeight, int* srcDoubleWidth, void* pDestination, 
                 int srcPitch, int dstPitch, UInt32 rnd, void* pRgbTable, int evenOddPage, int interlace)
{
    UInt32* pRgbTable32 = (UInt32*)pRgbTable;
    UInt32* pSrc        = (UInt32*)pSource;
    UInt32* pDst1       = (UInt32*)pDestination;
    UInt32* pDst2       = pDst1 + dstPitch / sizeof(UInt32);
    int w;
    int h;

    srcPitch *= 2;

    if (deInterlace && interlace) {
        UInt32 *pSrc2 = pSrc + 2 * srcWidth * srcHeight;

        for (h = 0; h < srcHeight; h++) {
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
                    pDst1[dstIndex]   = pRgbTable32[pSrc[w]];
                    pDst2[dstIndex++] = pRgbTable32[pSrc2[w++]];
                    
                    pDst1[dstIndex]   = pRgbTable32[pSrc[w]];
                    pDst2[dstIndex++] = pRgbTable32[pSrc2[w++]];
                    
                    pDst1[dstIndex]   = pRgbTable32[pSrc[w]];
                    pDst2[dstIndex++] = pRgbTable32[pSrc2[w++]];
                    
                    pDst1[dstIndex]   = pRgbTable32[pSrc[w]];
                    pDst2[dstIndex++] = pRgbTable32[pSrc2[w++]];
                }
            }
            else {
                for (w = 0; w < srcWidth;) {
                    UInt32 col1 = pRgbTable32[pSrc[w]];
                    UInt32 col2 = pRgbTable32[pSrc2[w++]];
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col2;
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col2;

                    col1 = pRgbTable32[pSrc[w]];
                    col2 = pRgbTable32[pSrc2[w++]];
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col2;
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col2;

                    col1 = pRgbTable32[pSrc[w]];
                    col2 = pRgbTable32[pSrc2[w++]];
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col2;
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col2;

                    col1 = pRgbTable32[pSrc[w]];
                    col2 = pRgbTable32[pSrc2[w++]];
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col2;
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col2;
                }
            }

            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pSrc2 = (UInt32*)((UInt8*)pSrc2 + srcPitch);
            pDst1 = (UInt32*)((UInt8*)pDst1 + dstPitch * 2);
            pDst2 = (UInt32*)((UInt8*)pDst2 + dstPitch * 2);
        }
    }
    else {
        if (evenOddPage) pSrc += 2 * srcWidth * srcHeight;

        if (interlace && evenOddPage) {
            pDst1 = (UInt32*)((UInt8*)pDst1 + dstPitch);
            pDst2 = (UInt32*)((UInt8*)pDst2 + dstPitch);
            srcHeight--;
        }
        for (h = 0; h < srcHeight; h++) {
            int dstIndex = 0;

            if (srcDoubleWidth[h]) {
                for (w = 0; w < 2 * srcWidth;) {
                    UInt32 col1 = pRgbTable32[pSrc[w++]];
                    UInt32 col2 = pRgbTable32[pSrc[w++]];
                    UInt32 col3 = pRgbTable32[pSrc[w++]];
                    UInt32 col4 = pRgbTable32[pSrc[w++]];

                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col1;
                    
                    pDst1[dstIndex]   = col2;
                    pDst2[dstIndex++] = col2;
                    
                    pDst1[dstIndex]   = col3;
                    pDst2[dstIndex++] = col3;
                    
                    pDst1[dstIndex]   = col4;
                    pDst2[dstIndex++] = col4;
                }
            }
            else {
                for (w = 0; w < srcWidth;) {
                    UInt32 col1 = pRgbTable32[pSrc[w++]];
                    UInt32 col2 = pRgbTable32[pSrc[w++]];
                    UInt32 col3 = pRgbTable32[pSrc[w++]];
                    UInt32 col4 = pRgbTable32[pSrc[w++]];

                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col1;
                    pDst1[dstIndex]   = col1;
                    pDst2[dstIndex++] = col1;
                    
                    pDst1[dstIndex]   = col2;
                    pDst2[dstIndex++] = col2;
                    pDst1[dstIndex]   = col2;
                    pDst2[dstIndex++] = col2;
                    
                    pDst1[dstIndex]   = col3;
                    pDst2[dstIndex++] = col3;
                    pDst1[dstIndex]   = col3;
                    pDst2[dstIndex++] = col3;
                    
                    pDst1[dstIndex]   = col4;
                    pDst2[dstIndex++] = col4;
                    pDst1[dstIndex]   = col4;
                    pDst2[dstIndex++] = col4;
                }
            }

            pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
            pDst1 = (UInt32*)((UInt8*)pDst1 + dstPitch * 2);
            pDst2 = (UInt32*)((UInt8*)pDst2 + dstPitch * 2);
        }
    }
}

static void scale2x_2x2_32(void* pSource, int srcWidth, int srcHeight, void* pDestination, 
                           int srcPitch, int dstPitch, UInt32 rnd, void* pRgbTable, int evenOddPage)
{
	UInt32  ImgSrc[80000];
	UInt32* pRgbTable32 = (UInt32*)pRgbTable;
    UInt32* pSrc        = (UInt32*)pSource;
    UInt32* pDst1       = (UInt32*)pDestination;
	int w, h;    

    if (evenOddPage) pSrc += 2 * srcWidth * srcHeight;

	srcPitch/=2;

    for (h=0; h<srcHeight; h++) 
	{
        for (w=0; w<srcWidth; w++) 
		{
			ImgSrc[w+h*srcWidth]=pRgbTable32[pSrc[w]];
        }
		pSrc+=srcPitch;
    }
    scale(2, &pDst1[0], srcWidth*8, &ImgSrc[0], srcWidth*4, 4, srcWidth, srcHeight);
}

static void scale2x_2x2_16(void* pSource, int srcWidth, int srcHeight, void* pDestination, 
                           int srcPitch, int dstPitch, UInt32 rnd, void* pRgbTable, int evenOddPage)
{

    UInt16* pRgbTable16 = (UInt16*)pRgbTable;
    UInt32* pSrc        = (UInt32*)pSource;
    UInt16* pDst1       = (UInt16*)pDestination;
	UInt16  ImgSrc[320*250];
	int w, h,index;    

    if (evenOddPage) pSrc += 2 * srcWidth * srcHeight;
    srcPitch *= 2;
    index=0;
    for (h=0; h<srcHeight; h++) 
	{
        for (w=0; w<srcWidth; w++) 
		{
			ImgSrc[index]=pRgbTable16[pSrc[w]];
			index++;
        }
        pSrc  = (UInt32*)((UInt8*)pSrc  + srcPitch);
    }
    scale(2, &pDst1[0], srcWidth*4, &ImgSrc[0], srcWidth*2, 2, srcWidth, srcHeight);
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
    pVideo->decay = 3 - skipCount;
}

void videoSetDeInterlace(Video* pVideo, int doDeInterlace)
{
    deInterlace = doDeInterlace;
}

UInt32 videoGetColor(int R, int G, int B)
{
    int Y  = (int)(0.2989*R + 0.5866*G + 0.1145*B);
    int Cb = B - Y;
    int Cr = R - Y;

#ifdef USE_RGB
    return ((R >> 3) << 12) | ((G >> 3) << 6) | (B >> 3);
#endif
    Y  = MAX(0,   MIN(31, Y / 8));
    Cb = 16 + MAX(-16, MIN(15, Cb / 16));
    Cr = 16 + MAX(-16, MIN(15, Cr / 16));

    return Y | (Cb << 6) | (Cr << 12);
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

void scanLines_16(void* pBuffer, int width, int height, int pitch, int interlace, int evenOddPage, int scanLinesPct)
{
    UInt32* pBuf = (UInt32*)pBuffer;
    int w, h;

    if (scanLinesPct == 100) {
        return;
    }

    pitch = pitch * 2 / sizeof(UInt32);
    scanLinesPct = scanLinesPct * 32 / 100;
    height /= 2;
    width /= 2;

#if 0    
    if (interlace && !deInterlace && evenOddPage) {
        pBuf += pitch / 2;
    }
#endif
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

void scanLines_32(void* pBuffer, int width, int height, int pitch, int interlace, int evenOddPage, int scanLinesPct)
{
    UInt32* pBuf = (UInt32*)pBuffer;
    int w, h;

    if (scanLinesPct == 100) {
        return;
    }

    pitch = pitch * 2 / sizeof(UInt32);
    scanLinesPct = scanLinesPct * 255 / 100;
    height /= 2;
#if 0    
    if (interlace && !deInterlace && evenOddPage) {
        pBuf += pitch / 2;
    }
#endif
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

void videoRender(Video* pVideo, int bitDepth, int zoom, int evenOddPage, int interlace,
                 void* pSrc, int srcWidth, int srcHeight, int* srcDoubleWidth, void* pDst, int srcPitch, int dstPitch)
{
    static UInt32 rnd = 51;

    // Update simple rand generator
    rnd *= 13;

    switch (bitDepth) {
    case 16:
        switch (pVideo->palMode) {
        case VIDEO_PAL_FAST:
            if (zoom == 2) copy_2x2_16(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable16, evenOddPage, interlace);
            else           copy_1x1_16(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable16, evenOddPage, interlace);
            break;
        case VIDEO_PAL_SHARP:
            if (zoom == 2) copySharpPAL_2x2_16(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable16, evenOddPage, interlace);
            else           copyPAL_1x1_16(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable16, evenOddPage, interlace);
            break;
        case VIDEO_PAL_SHARP_NOISE:
            if (zoom == 2) copySharpPAL_2x2_16(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, rnd, pVideo->pRgbTable16, evenOddPage, interlace);
            else           copyPAL_1x1_16(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, rnd, pVideo->pRgbTable16, evenOddPage, interlace);
            break;
        case VIDEO_PAL_BLUR:
            if (zoom == 2) copyPAL_2x2_16(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable16, pVideo->decay, evenOddPage, interlace);
            else           copyPAL_1x1_16(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable16, evenOddPage, interlace);
            break;
        case VIDEO_PAL_BLUR_NOISE:
            if (zoom == 2) copyPAL_2x2_16(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, rnd, pVideo->pRgbTable16, pVideo->decay, evenOddPage, interlace);
            else           copyPAL_1x1_16(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, rnd, pVideo->pRgbTable16, evenOddPage, interlace);
            break;
		case VIDEO_PAL_SCALE2X:
            if (zoom==2) {
                if (!*srcDoubleWidth && !interlace) {
                    scale2x_2x2_16(pSrc, srcWidth, srcHeight, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable16, evenOddPage);
                }
                else {
                    copy_2x2_16(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable16, evenOddPage, interlace);
                }
            }
            else {
                copy_1x1_16(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable16, evenOddPage, interlace);
            }
            break;
        case VIDEO_PAL_STRETCHED :
            if (zoom == 2 && (*srcDoubleWidth) || interlace) {
                copy_2x2_16(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable16, evenOddPage, interlace);
            }
            else {
                copy_1x1_16(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable16, evenOddPage, interlace);
            }
            break;

        }

        if (pVideo->scanLinesEnable) {
            scanLines_16(pDst, 320 * zoom, 240 * zoom, dstPitch, interlace, evenOddPage, pVideo->scanLinesPct);
        }
        break;
    case 32:
        switch (pVideo->palMode) {
        case VIDEO_PAL_FAST:
            if (zoom == 2) copy_2x2_32(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable32, evenOddPage, interlace);
            else           copy_1x1_32(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable32, evenOddPage, interlace);
            break;
        case VIDEO_PAL_MONITOR:
            if (zoom == 2) copyMonitorPAL_2x2_32(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, rnd, pVideo->pRgbTable32, evenOddPage, interlace);
            else           copyPAL_1x1_32(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable32, evenOddPage, interlace);
            break;
        case VIDEO_PAL_SHARP:
            if (zoom == 2) copySharpPAL_2x2_32(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable32, evenOddPage, interlace);
            else           copy_1x1_32(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable32, evenOddPage, interlace);
            break;
        case VIDEO_PAL_SHARP_NOISE:
            if (zoom == 2) copySharpPAL_2x2_32(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, rnd, pVideo->pRgbTable32, evenOddPage, interlace);
            else           copyPAL_1x1_32(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, rnd, pVideo->pRgbTable32, evenOddPage, interlace);
            break;
        case VIDEO_PAL_BLUR:
            if (zoom == 2) copyPAL_2x2_32(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable32, pVideo->decay, evenOddPage, interlace);
            else           copyPAL_1x1_32(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable32, evenOddPage, interlace);
            break;
        case VIDEO_PAL_BLUR_NOISE:
            if (zoom == 2) copyPAL_2x2_32(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, rnd, pVideo->pRgbTable32, pVideo->decay, evenOddPage, interlace);
            else           copyPAL_1x1_32(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, rnd, pVideo->pRgbTable32, evenOddPage, interlace);
            break;
		case VIDEO_PAL_SCALE2X:
            if (zoom==2) {
                if (!*srcDoubleWidth && !interlace) {
                    scale2x_2x2_32(pSrc, srcWidth, srcHeight, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable32, evenOddPage);
                }
                else {
                    copy_2x2_32(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable32, evenOddPage, interlace);
                }
            }
            else {
                copy_1x1_32(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable32, evenOddPage, interlace);
            }
            break;
        case VIDEO_PAL_STRETCHED :
            if (zoom == 2 && (*srcDoubleWidth) || interlace) {
                copy_2x2_32(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable32, evenOddPage, interlace);
            }
            else {
                copy_1x1_32(pSrc, srcWidth, srcHeight, srcDoubleWidth, pDst, srcPitch, dstPitch, 0, pVideo->pRgbTable32, evenOddPage, interlace);
            }
            break;
        }

        if (pVideo->scanLinesEnable) {
            scanLines_32(pDst, 320 * zoom, 240 * zoom, dstPitch, interlace, evenOddPage, pVideo->scanLinesPct);
        }
        break;
    }
}
