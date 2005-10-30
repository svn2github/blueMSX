/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoChips/FrameBuffer.c,v $
**
** $Revision: 1.15 $
**
** $Date: 2005-10-30 01:49:54 $
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

#define MAX_FRAMES_PER_FRAMEBUFFER 4

struct FrameBufferData {
    int viewFrame;
    int drawFrame;
    int currentAge;
    FrameBuffer frame[MAX_FRAMES_PER_FRAMEBUFFER];
};

static void* semaphore = NULL;
static FrameBuffer* deintBuffer = NULL;

static FrameBuffer* mixFrame(FrameBuffer* a, FrameBuffer* b, int pct);
static FrameBuffer* mixFrameInterlace(FrameBuffer* a, FrameBuffer* b, int pct);
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
static int frameBufferCount = MAX_FRAMES_PER_FRAMEBUFFER;


static FrameBuffer* frameBufferFlipViewFrame1(int mixFrames) 
{
    if (currentBuffer == NULL) {
        return NULL;
    }
    currentBuffer->frame->age = ++currentBuffer->currentAge;
    return currentBuffer->frame;
}

static FrameBuffer* frameBufferFlipViewFrame3(int mixFrames) 
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

static FrameBuffer* frameBufferFlipViewFrame4(int mixFrames) 
{
    int i1,i2;

    if (currentBuffer == NULL) {
        return NULL;
    }
    waitSem();
#if 0
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
#else
    {
        int secondFrame = 0;
        int viewAge;
        int i;
        for (i = 0; i < 4; i++) {
            if (i == currentBuffer->drawFrame) continue;
            if (currentBuffer->frame[i].age > currentBuffer->frame[currentBuffer->viewFrame].age) {
                currentBuffer->viewFrame = i;
            }
        }
        viewAge = 0;
        for (i = 0; i < 4; i++) {
            if (i == currentBuffer->drawFrame) continue;
            if (i == currentBuffer->viewFrame) continue;
            if (currentBuffer->frame[i].age > viewAge) {
                viewAge = currentBuffer->frame[i].age;
                secondFrame = i;
            }
        }
        signalSem();

        return mixFrame(currentBuffer->frame + currentBuffer->viewFrame, currentBuffer->frame + secondFrame, getScreenCompletePercent());
    }
#endif

    i1 = currentBuffer->frame[i1].age > currentBuffer->frame[i2].age ? i1 : i2;
    if (currentBuffer->frame[i1].age > currentBuffer->frame[currentBuffer->viewFrame].age) {
        currentBuffer->viewFrame = i1;
    }
    signalSem();
    return currentBuffer->frame + currentBuffer->viewFrame;
}


static FrameBuffer* frameBufferFlipDrawFrame1()
{
    if (currentBuffer == NULL) {
        return NULL;
    }
    return currentBuffer->frame; 
}

static FrameBuffer* frameBufferFlipDrawFrame3()
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

static FrameBuffer* frameBufferFlipDrawFrame4()
{
    FrameBuffer* frame;
    int i1,i2;

    if (currentBuffer == NULL) {
        return NULL;
    }
    waitSem();
#if 0
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
#else
    {
        int drawFrame = currentBuffer->drawFrame;
        int drawAge = 0x7fffffff;
        int i;
        for (i = 0; i < 4; i++) {
            if (i == drawFrame) continue;
            if (currentBuffer->frame[i].age < drawAge) {
                drawAge = currentBuffer->frame[i].age;
                currentBuffer->drawFrame = i;
            }
        }
    }
#endif
    signalSem();
    frame = currentBuffer->frame + currentBuffer->drawFrame;
    frame->age = ++currentBuffer->currentAge;
    return frame;
}



FrameBuffer* frameBufferGetViewFrame()
{
    return currentBuffer ? currentBuffer->frame + currentBuffer->viewFrame : NULL;
}

FrameBuffer* frameBufferGetDrawFrame()
{
    return currentBuffer ? currentBuffer->frame + currentBuffer->drawFrame : NULL;
}

void frameBufferSetFrameCount(int frameCount)
{
    waitSem();
    frameBufferCount = frameCount;
    if (currentBuffer != NULL) {
        int i;
        currentBuffer->viewFrame = 0;
        currentBuffer->drawFrame = 0;

        for (i = 0; i < MAX_FRAMES_PER_FRAMEBUFFER; i++) {
            currentBuffer->frame[i].age = 0;
        }
    }
    signalSem();
}

FrameBuffer* frameBufferFlipViewFrame(int mixFrames) 
{
    switch (frameBufferCount) {
    case 3:
        return frameBufferFlipViewFrame3(mixFrames);
    case 4:
        return frameBufferFlipViewFrame4(mixFrames);
    }
    return frameBufferFlipViewFrame1(mixFrames);
}

FrameBuffer* frameBufferFlipDrawFrame() {
    switch (frameBufferCount) {
    case 3:
        return frameBufferFlipDrawFrame3();
    case 4:
        return frameBufferFlipDrawFrame4();
    }
    return frameBufferFlipDrawFrame1();
}

FrameBufferData* frameBufferDataCreate(int maxWidth, int maxHeight, int defaultHorizZoom)
{
    int i;
    FrameBufferData* frameData = calloc(1, sizeof(FrameBufferData));
    frameData->drawFrame = frameBufferCount > 1 ? 1 : 0;

    for (i = 0; i < MAX_FRAMES_PER_FRAMEBUFFER; i++) {
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

    if (a->interlace != INTERLACE_NONE) {
        return mixFrameInterlace(a, b, pct);
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
        }
    }

    return d;
}


static FrameBuffer* mixFrameInterlace(FrameBuffer* a, FrameBuffer* b, int pct)
{
    static FrameBuffer* d = NULL;
    int p = 0x40 * pct / 100;
    int n = 0x40 - p;
    int x;
    int y;
    UInt32* dp;
    int     width;
    UInt32* ap;
    UInt32* bp;

    if (d == NULL) {
        d = (FrameBuffer*)malloc(sizeof(FrameBuffer)); 
    }

    d->lines     = a->lines * 2;
    d->interlace = INTERLACE_NONE;
    d->maxWidth  = a->maxWidth;

    if (p == 0x40) { p = 0x39; n = 1; }
    if (n == 0x40) { n = 0x39; p = 1; }

    if (a->interlace == INTERLACE_ODD) {
        FrameBuffer* t;
        int t2;

        t = a;
        a = b;
        b = t;

        t2 = n;
        n = p;
        p = t2;
    }

    for (y = 0; y < a->lines * 2; y++) {
        width = a->line[y / 2].doubleWidth ? a->maxWidth * 2: a->maxWidth;
        if (y & 1) {
            ap = a->line[y / 2].buffer;
            bp = b->line[y / 2].buffer;
        }
        else {
            ap = a->line[y / 2].buffer;
            if (y == 0) {
                bp = b->line[a->lines - 1].buffer;
            }
            else {
                bp = b->line[y / 2 - 1].buffer;
            }
        }
        dp = d->line[y].buffer;
        d->line[y].doubleWidth = a->line[y / 2].doubleWidth;

        for (x = 0; x < width; x++) {
            UInt32 av = ap[x];
            UInt32 bv = bp[x];
            dp[x] = ((((av & M1) * p + (bv & M1) * n) >> 6) & M1) |
                    ((((av & M2) * p + (bv & M2) * n) >> 6) & M2);
        }
    }

    return d;
}
