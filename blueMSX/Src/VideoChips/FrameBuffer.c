/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoChips/FrameBuffer.c,v $
**
** $Revision: 1.11 $
**
** $Date: 2005-07-09 12:11:29 $
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
#include "FrameBuffer.h"
#include "ArchEvent.h"
#include <stdlib.h>

#define FRAMES_PER_FRAMEBUFFER 4

struct FrameBufferData {
    int viewFrame;
    int drawFrame;
    int currentAge;
    FrameBuffer frame[FRAMES_PER_FRAMEBUFFER];
};

static void* semaphore = NULL;
static FrameBuffer* deintBuffer = NULL;

static FrameBuffer* mixFrame(FrameBuffer* a, FrameBuffer* b, int pct);
extern int getScreenCompletePercent();

static void waitSem() {
    if (semaphore == NULL) {
        semaphore = archSemaphoreCreate(1);
    }
    archSemaphoreWait(semaphore, -1);
}

static void signalSem() {
    archSemaphoreSignal(semaphore);
}



static FrameBufferData* currentBuffer = NULL;


FrameBuffer* frameBufferGetViewFrame()
{
    return currentBuffer ? currentBuffer->frame + currentBuffer->viewFrame : NULL;
}

#if FRAMES_PER_FRAMEBUFFER == 4
FrameBuffer* frameBufferFlipViewFrame(int mixFrames) 
{
    int i1,i2;

    if (currentBuffer == NULL) {
        return NULL;
    }
    waitSem();
    switch (currentBuffer->viewFrame) {
    case 0: 
        switch (currentBuffer->drawFrame) {
        case 1: i1 = 2; i2 = 3; break;
        case 2: i1 = 3; i2 = 1; break;
        case 3: i1 = 1; i2 = 2; break;
        }
        break;
    case 1: 
        switch (currentBuffer->drawFrame) {
        case 0: i1 = 2; i2 = 3; break;
        case 2: i1 = 3; i2 = 0; break;
        case 3: i1 = 0; i2 = 2; break;
        }
        break;
    case 2:
        switch (currentBuffer->drawFrame) {
        case 0: i1 = 1; i2 = 3; break;
        case 1: i1 = 3; i2 = 0; break;
        case 3: i1 = 0; i2 = 1; break;
        }
        break;
    case 3: 
        switch (currentBuffer->drawFrame) {
        case 0: i1 = 1; i2 = 2; break;
        case 1: i1 = 2; i2 = 0; break;
        case 2: i1 = 0; i2 = 1; break;
        }
        break;
    }
    if (mixFrames) {
        int i3 = currentBuffer->viewFrame;
        
        if (currentBuffer->frame[i3].age > currentBuffer->frame[i2].age) {
            int tmp = i3; i3 = i2; i2 = tmp;
        }
        if (currentBuffer->frame[i2].age > currentBuffer->frame[i1].age) {
            int tmp = i2; i2 = i1; i1 = tmp;
        }
        if (currentBuffer->frame[i3].age > currentBuffer->frame[i2].age) {
            int tmp = i3; i3 = i2; i2 = tmp;
        }

        currentBuffer->viewFrame = i1;

        signalSem();

        return mixFrame(currentBuffer->frame + i1, currentBuffer->frame + i2, getScreenCompletePercent());
    }

    i1 = currentBuffer->frame[i1].age > currentBuffer->frame[i2].age ? i1 : i2;
    if (currentBuffer->frame[i1].age > currentBuffer->frame[currentBuffer->viewFrame].age) {
        currentBuffer->viewFrame = i1;
    }
    signalSem();
    return currentBuffer->frame + currentBuffer->viewFrame;
}
#else
FrameBuffer* frameBufferFlipViewFrame(int mixFrames) 
{
    int index;

    if (currentBuffer == NULL) {
        return NULL;
    }
    waitSem();
    switch (currentBuffer->viewFrame) {
    case 0: index = currentBuffer->drawFrame == 1 ? 2 : 1; break;
    case 1: index = currentBuffer->drawFrame == 2 ? 0 : 2; break;
    case 2: index = currentBuffer->drawFrame == 0 ? 1 : 0; break;
    }
    if (currentBuffer->frame[index].age > currentBuffer->frame[currentBuffer->viewFrame].age) {
        currentBuffer->viewFrame = index;
    }
    signalSem();
    return currentBuffer->frame + currentBuffer->viewFrame;
}

#endif


FrameBuffer* frameBufferGetDrawFrame()
{
    return currentBuffer ? currentBuffer->frame + currentBuffer->drawFrame : NULL;
}

#if FRAMES_PER_FRAMEBUFFER == 4
FrameBuffer* frameBufferFlipDrawFrame()
{
    FrameBuffer* frame;
    int i1,i2;

    if (currentBuffer == NULL) {
        return NULL;
    }
    waitSem();
    switch (currentBuffer->drawFrame) {
    case 0: 
        switch (currentBuffer->viewFrame) {
        case 1: i1 = 2; i2 = 3; break;
        case 2: i1 = 3; i2 = 1; break;
        case 3: i1 = 1; i2 = 2; break;
        }
        break;
    case 1: 
        switch (currentBuffer->viewFrame) {
        case 0: i1 = 2; i2 = 3; break;
        case 2: i1 = 3; i2 = 0; break;
        case 3: i1 = 0; i2 = 2; break;
        }
        break;
    case 2:
        switch (currentBuffer->viewFrame) {
        case 0: i1 = 1; i2 = 3; break;
        case 1: i1 = 3; i2 = 0; break;
        case 3: i1 = 0; i2 = 1; break;
        }
        break;
    case 3: 
        switch (currentBuffer->viewFrame) {
        case 0: i1 = 1; i2 = 2; break;
        case 1: i1 = 2; i2 = 0; break;
        case 2: i1 = 0; i2 = 1; break;
        }
        break;
    }
    currentBuffer->drawFrame = currentBuffer->frame[i1].age < currentBuffer->frame[i2].age ? i1 : i2;
    signalSem();
    frame = currentBuffer->frame + currentBuffer->drawFrame;
    frame->age = ++currentBuffer->currentAge;
    return frame;
}
#else
FrameBuffer* frameBufferFlipDrawFrame()
{
    FrameBuffer* frame;

    if (currentBuffer == NULL) {
        return NULL;
    }
    waitSem();
    switch (currentBuffer->drawFrame) {
    case 0: currentBuffer->drawFrame = currentBuffer->viewFrame == 1 ? 2 : 1; break;
    case 1: currentBuffer->drawFrame = currentBuffer->viewFrame == 2 ? 0 : 2; break;
    case 2: currentBuffer->drawFrame = currentBuffer->viewFrame == 0 ? 1 : 0; break;
    }
    frame = currentBuffer->frame + currentBuffer->drawFrame;
    frame->age = ++currentBuffer->currentAge;
    signalSem();
    return frame;
}
#endif

FrameBufferData* frameBufferDataCreate(int maxWidth, int maxHeight, int defaultHorizZoom)
{
    int i;
    FrameBufferData* frameData = calloc(1, sizeof(FrameBufferData));
    frameData->drawFrame = 1;

    for (i = 0; i < FRAMES_PER_FRAMEBUFFER; i++) {
        int j;

        frameData->frame[i].maxWidth = maxWidth;
        frameData->frame[i].lines = maxHeight;
        for (j = 0; j < FB_MAX_LINES; j++) {
            frameData->frame[i].line[j].doubleWidth = defaultHorizZoom - 1;
        }
    }

    return frameData;
}

void frameBufferDataDestroy(FrameBufferData* frameData)
{
    if (frameData == currentBuffer) {
        currentBuffer = NULL;
    }
    free(frameData);
}

void frameBufferSetActive(FrameBufferData* frameData)
{
    currentBuffer = frameData;
}

FrameBufferData* frameBufferGetActive() 
{
    return currentBuffer;
}

extern UInt32 videoGetColor(int R, int G, int B);

FrameBuffer* frameBufferGetWhiteNoiseFrame() 
{
    static FrameBuffer* frameBuffer = NULL;
    UInt32 colors[32];
    static UInt32 r = 13;
    int y;

    for (y = 0; y < 32; y++) {
        colors[y] = videoGetColor(y << 3, y << 3, y << 3);
    }

    if (frameBuffer == NULL) {
        frameBuffer = calloc(1, sizeof(FrameBuffer));
        frameBuffer->lines = 240;
        frameBuffer->maxWidth = 320;
    }

    for (y = 0; y < 240; y++) {
        int x;
        UInt32* buffer = frameBuffer->line[y].buffer;
        frameBuffer->line[y].doubleWidth = 0;
        for (x = 0; x < 320; x++) {
            buffer[x] = colors[r >> 27];
            r *= 7;
        }
    }

    return frameBuffer;
}

void frameBufferClearDeinterlace()
{
    if (deintBuffer != NULL) {
        void* buf = deintBuffer;
        deintBuffer = NULL;
        free(buf);
    }
}

FrameBuffer* frameBufferDeinterlace(FrameBuffer* frameBuffer)
{
    int y;

    if (deintBuffer == NULL) {
        deintBuffer = calloc(1, sizeof(FrameBuffer));
    }
    deintBuffer->lines = frameBuffer->lines < FB_MAX_LINES / 2 ? 2 * frameBuffer->lines : FB_MAX_LINES;
    deintBuffer->maxWidth = frameBuffer->maxWidth;

    for (y = frameBuffer->interlace == INTERLACE_ODD ? 1 : 0; y < FB_MAX_LINES; y += 2) {
        deintBuffer->line[y] = frameBuffer->line[y / 2];
    }
    return deintBuffer;
}


#define M1 0x1F01F
#define M2 0x007C0

static FrameBuffer* mixFrame(FrameBuffer* a, FrameBuffer* b, int pct)
{
    static FrameBuffer* d = NULL;
    int p = 0x40 * pct / 100;
    int n = 0x40 - p;
    int x;
    int y;

    if (d == NULL) {
        d = (FrameBuffer*)malloc(sizeof(FrameBuffer)); 
    }

    if (p == 0x40) {
        return a;
    }
    if (n == 0x40) {
        return b;
    }

    d->lines = a->lines;
    d->interlace = a->interlace;
    d->maxWidth = a->maxWidth;

    for (y = 0; y < a->lines; y++) {
        int width = a->line[y].doubleWidth ? a->maxWidth * 2: a->maxWidth;
        UInt32* ap = a->line[y].buffer;
        UInt32* bp = b->line[y].buffer;
        UInt32* dp = d->line[y].buffer;

        d->line[y].doubleWidth = a->line[y].doubleWidth;
        for (x = 0; x < width; x++) {
            UInt32 av = ap[x];
            UInt32 bv = bp[x];
            dp[x] = ((((av & M1) * p + (bv & M1) * n) >> 6) & M1) |
                    ((((av & M2) * p + (bv & M2) * n) >> 6) & M2);

            if (dp[x] & ~0x1F7DF) {
                exit(0);
            }
        }
    }

    return d;
}
