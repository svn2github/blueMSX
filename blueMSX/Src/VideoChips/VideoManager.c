/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoChips/VideoManager.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-01-17 08:01:20 $
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
#include "VideoManager.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_DEVICES 64

typedef struct {
    int handle;
    VideoCallbacks callbacks;
    void* ref;
    char  name[32];
} VideoInfo;

typedef struct {
    VideoInfo di[MAX_DEVICES];
    int count;
    int lastHandle;
} VideoManager;

static VideoManager videoManager;

void videoManagerCreate() {
    videoManager.count = 0;
    videoManager.lastHandle = 0;
}

void videoManagerDestroy()
{
}

int videoManagerRegister(char* name, VideoCallbacks* callbacks, void* ref)
{
    if (videoManager.count >= MAX_DEVICES) {
        return 0;
    }

    videoManager.di[videoManager.count].handle    = ++videoManager.lastHandle;
    videoManager.di[videoManager.count].callbacks = *callbacks;
    videoManager.di[videoManager.count].ref       = ref;

    strcpy(videoManager.di[videoManager.count].name, name);

    videoManager.count++;

    return videoManager.lastHandle;
}

void videoManagerUnregister(int handle)
{
    int i;

    if (videoManager.count == 0) {
        return;
    }

    for (i = 0; i < videoManager.count; i++) {
        if (videoManager.di[i].handle == handle) {
            break;
        }
    }

    if (i == videoManager.count) {
        return;
    }

    videoManager.count--;
    while (i < videoManager.count) {
        videoManager.di[i] = videoManager.di[i + 1];
        i++;
    }
}
