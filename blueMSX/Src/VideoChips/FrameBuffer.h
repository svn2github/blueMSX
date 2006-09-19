/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoChips/FrameBuffer.h,v $
**
** $Revision: 1.22 $
**
** $Date: 2006-09-19 06:00:36 $
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
#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "MsxTypes.h"

#define FB_MAX_LINE_WIDTH 640
#define FB_MAX_LINES      480

typedef struct {
    int doubleWidth; // 1 when normal, 2 when 2 src pixels per dest pixel
    UInt16 buffer[FB_MAX_LINE_WIDTH];
} LineBuffer;

typedef enum { INTERLACE_NONE, INTERLACE_ODD, INTERLACE_EVEN } InterlaceMode;
typedef struct {
    int age;           // Internal use
    InterlaceMode interlace; 
    int maxWidth;
    int lines;         // Number of lines in frame buffer
    LineBuffer line[FB_MAX_LINES];
} FrameBuffer;

typedef struct FrameBufferData FrameBufferData;

typedef enum {
    MIXMODE_INTERNAL = 1,
    MIXMODE_BOTH     = 2,
    MIXMODE_EXTERNAL = 4,
    MIXMODE_NONE     = 8
} FrameBufferMixMode;

void frameBufferSetFrameCount(int frameCount);

FrameBuffer* frameBufferGetViewFrame();
FrameBuffer* frameBufferGetDrawFrame();
FrameBuffer* frameBufferFlipViewFrame(int mixFrames);
FrameBuffer* frameBufferFlipDrawFrame();

void frameBufferSetScanline(int scanline);
int frameBufferGetScanline();

FrameBuffer* frameBufferGetWhiteNoiseFrame();
FrameBuffer* frameBufferDeinterlace(FrameBuffer* frameBuffer);
void frameBufferClearDeinterlace();

FrameBufferData* frameBufferDataCreate(int maxWidth, int maxHeight, int defaultHorizZoom);
void frameBufferDataDestroy(FrameBufferData* frameData);

void frameBufferSetActive(FrameBufferData* frameData);
void frameBufferSetMixMode(FrameBufferMixMode mode, FrameBufferMixMode mask);

FrameBufferData* frameBufferGetActive();

void frameBufferSetBlendFrames(int blendFrames);

#define videoGetTransparentColor() 0x8000

static UInt16 videoGetColor(int R, int G, int B)
{
    return ((R >> 3) << 10) | ((G >> 3) << 5) | (B >> 3);
}

#endif
