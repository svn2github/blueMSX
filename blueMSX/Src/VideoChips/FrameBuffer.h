/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoChips/FrameBuffer.h,v $
**
** $Revision: 1.3 $
**
** $Date: 2005-01-19 05:26:35 $
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
#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "MSXTypes.h"

#define MAX_LINE_WIDTH 640

typedef struct {
    int width;    // Width of line in frame buffer
    UInt32 buffer[MAX_LINE_WIDTH];
} LineBuffer;

typedef struct {
    int age;          // Internal use
    int interlaceOdd; // 0 in most cases, 1 if odd interlaced frame
    int lines;        // Number of lines in frame buffer
    LineBuffer line[480];
} FrameBuffer;

typedef struct FrameBufferData FrameBufferData;


FrameBuffer* frameBufferGetViewFrame();
FrameBuffer* frameBufferFlipViewFrame();
FrameBuffer* frameBufferGetDrawFrame();
FrameBuffer* frameBufferFlipDrawFrame();

FrameBufferData* frameBufferDataCreate();
void frameBufferDataDestroy(FrameBufferData* frameData);

void frameBufferSetActive(FrameBufferData* frameData);
FrameBufferData* frameBufferGetActive();

#endif