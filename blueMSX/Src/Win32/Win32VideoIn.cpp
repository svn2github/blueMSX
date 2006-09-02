/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32VideoIn.cpp,v $
**
** $Revision: 1.7 $
**
** $Date: 2006-09-02 20:17:55 $
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
extern "C" {
#include "Win32VideoIn.h"
#include "ArchVideoIn.h"
#include "Language.h"
}

#include "Win32DirectShow.h"

typedef struct {
    UInt16* buffer;
    int     width;
    int     height;

    int inputIndex;
    int inputCount;
    int disabled;

    CVideoGrabber* grabber;
    
    CVideoGrabber::DeviceNameList devList;
} VideoIn;

static VideoIn videoIn;


int archVideoInIsVideoConnected()
{
    return videoIn.inputIndex > 0;
}

UInt16* archVideoInBufferGet(int width, int height)
{
    if (videoIn.inputIndex == 0) {
        return NULL;
    }

    // Allocate new video buffer if size has changed
    if (width != videoIn.width || height != videoIn.height) {
        if (videoIn.buffer != NULL) {
            free(videoIn.buffer);
        }
        videoIn.buffer = (UInt16*)calloc(1, sizeof(UInt16) * width * height);
        videoIn.width  = width;
        videoIn.height = height;
    }

    videoIn.grabber->GrabFrame(videoIn.buffer, width, height);

    return videoIn.buffer;
}

void videoInInitialize(Properties* properties)
{
    videoIn.inputCount = 1;
    videoIn.inputIndex = 0;

    videoIn.disabled = properties->videoIn.disabled;

    if (videoIn.disabled) {
        return;
    }

    videoIn.grabber = new CVideoGrabber;
    
    videoIn.devList = videoIn.grabber->GetDeviceNames();

    videoIn.inputCount += videoIn.devList.size();

    videoIn.inputIndex = properties->videoIn.inputIndex;

    videoInSetActive(videoIn.inputIndex);
}

void videoInCleanup(Properties* properties)
{
    if (videoIn.disabled) {
        return;
    }

    videoIn.grabber->ShutdownGrabber();
    delete videoIn.grabber;

    properties->videoIn.inputIndex = videoIn.inputIndex;
}

int  videoInGetCount()
{
    return videoIn.inputCount;
}

int videoInIsActive(int index)
{
    return index == videoIn.inputIndex;
}

int videoInGetActive()
{
    return videoIn.inputIndex;
}

const char* videoInGetName(int index)
{
    if (index == 0) {
        return langTextNone();
    }
    
    if (index < videoIn.inputCount) {
        return videoIn.devList[index - 1].c_str();
    }

    return langTextUnknown();
}

void videoInSetActive(int index)
{
    bool showdialog;

    if (videoIn.disabled) {
        return;
    }

    videoIn.grabber->ShutdownGrabber();

    showdialog = (videoIn.inputIndex != index);
    videoIn.inputIndex = index;

    if (videoIn.inputIndex > videoIn.inputCount) {
        videoIn.inputIndex = 0;
    }

    if (videoIn.inputIndex > 0) {
        if (showdialog) {
            videoIn.grabber->ShowProperties(NULL, videoIn.devList[videoIn.inputIndex - 1]);
        }

        if (!videoIn.grabber->SetupGrabber(videoIn.devList[videoIn.inputIndex - 1])) {
            videoIn.inputIndex = 0;
        }
    }
}
