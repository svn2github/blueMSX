/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoChips/FrameBuffer.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-01-18 10:17:18 $
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


struct FrameBufferData {
    int viewFrame;
    int drawFrame;
    FrameBuffer frame[3];
};

static void* semaphore = NULL;

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

FrameBuffer* frameBufferFlipViewFrame() 
{
    if (currentBuffer == NULL) {
        return NULL;
    }
    waitSem();
    switch (currentBuffer->viewFrame) {
    case 0: currentBuffer->viewFrame = currentBuffer->drawFrame == 1 ? 2 : 1; break;
    case 1: currentBuffer->viewFrame = currentBuffer->drawFrame == 2 ? 0 : 2; break;
    case 2: currentBuffer->viewFrame = currentBuffer->drawFrame == 0 ? 1 : 0; break;
    }
    signalSem();
    return currentBuffer->frame + currentBuffer->viewFrame;
}

FrameBuffer* frameBufferGetDrawFrame()
{
    return currentBuffer ? currentBuffer->frame + currentBuffer->drawFrame : NULL;
}

FrameBuffer* frameBufferFlipDrawFrame()
{
    if (currentBuffer == NULL) {
        return NULL;
    }
    waitSem();
    switch (currentBuffer->drawFrame) {
    case 0: currentBuffer->drawFrame = currentBuffer->viewFrame == 1 ? 2 : 1; break;
    case 1: currentBuffer->drawFrame = currentBuffer->viewFrame == 2 ? 0 : 2; break;
    case 2: currentBuffer->drawFrame = currentBuffer->viewFrame == 0 ? 1 : 0; break;
    }
    signalSem();
    return currentBuffer->frame + currentBuffer->drawFrame;
}

FrameBufferData* frameBufferDataCreate()
{
    FrameBufferData* frameData = calloc(1, sizeof(FrameBufferData));
    frameData->drawFrame = 1;

    if (currentBuffer == NULL) {
        currentBuffer = frameData;
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


