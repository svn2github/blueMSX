/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoRender/VideoRender.h,v $
**
** $Revision: 1.8 $
**
** $Date: 2005-01-29 01:32:17 $
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
#ifndef VIDEO_RENDER_H
#define VIDEO_RENDER_H

#include "msxTypes.h"
#include "FrameBuffer.h"

typedef enum { 
    VIDEO_GREEN, 
    VIDEO_COLOR, 
    VIDEO_BLACKWHITE,
    VIDEO_AMBER
} VideoColorMode;

typedef enum { 
    VIDEO_PAL_FAST,
    VIDEO_PAL_MONITOR,
    VIDEO_PAL_SHARP,
    VIDEO_PAL_SHARP_NOISE,  
    VIDEO_PAL_BLUR, 
    VIDEO_PAL_BLUR_NOISE,
	VIDEO_PAL_SCALE2X,
    VIDEO_PAL_HQ2X,
} VideoPalMode;

typedef struct Video Video;

struct Video {
    UInt16* pRgbTable16;
    UInt32* pRgbTable32;
    VideoPalMode palMode;
    int scanLinesEnable;
    int scanLinesPct;
    int colorSaturationEnable;
    int colorSaturationWidth;
    double gamma;
    double saturation;
    double brightness;
    double contrast;
    int deInterlace;
};

Video* videoCreate();

void videoDestroy(Video* pVideo);

void videoSetFrameSkip(Video* pVideo, UInt32 skipCount);

void videoSetDeInterlace(Video* pVideo, int deInterlace);

void videoSetColorMode(Video* pVideo, VideoColorMode colorMode);

void videoSetPalMode(Video* pVideo, VideoPalMode palMode);

void videoRender(Video* pVideo, FrameBuffer* frameBuffer, int bitDepth, int zoom, void* pDst, int dstPitch);

void videoSetColors(Video* pVideo, int saturation, int brightness, int contrast, int gamma);

UInt32 videoGetColor(int R, int G, int B);

void videoSetScanLines(Video* pVideo, int enable, int scanLinesPct);
void videoSetColorSaturation(Video* pVideo, int enable, int width);

#endif
