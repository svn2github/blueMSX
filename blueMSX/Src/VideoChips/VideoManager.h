/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/VideoChips/VideoManager.h,v $
**
** $Revision: 1.3 $
**
** $Date: 2005-02-01 04:43:33 $
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
#ifndef VIDEO_MANAGER_H
#define VIDEO_MANAGER_H

#include "MSXTypes.h"
#include "FrameBuffer.h"

typedef struct {
    void (*enable)(void*);
    void (*disable)(void*);
} VideoCallbacks;

int videoManagerGetCount();
int videoManagerGetActive();
void videoManagerSetActive(int index);
int videoManagerIsActive(int index);
char* videoManagerGetName(int index);

void videoManagerReset();

void videoManagerLoadState();
void videoManagerSaveState();

int videoManagerRegister(char* name, FrameBufferData* frameBuffer, 
                        VideoCallbacks* callbacks, void* ref);
void videoManagerUnregister(int handle);

#endif
