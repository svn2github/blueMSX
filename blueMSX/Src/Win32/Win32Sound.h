/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Sound.h,v $
**
** $Revision: 1.2 $
**
** $Date: 2004-12-06 07:31:42 $
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
#ifndef WIN32_SOUND_H
#define WIN32_SOUND_H

#include <windows.h>
#include "audioMixer.h"

typedef enum {
    SOUND_DRV_NONE,
    SOUND_DRV_WMM,
    SOUND_DRV_DIRECTX
} SoundDriver;

void soundDriverConfig(HWND hwnd, SoundDriver driver);
void archSoundCreate(Mixer* mixer, UInt32 sampleRate, UInt32 bufferSize, Int16 channels);
void archSoundDestroy(void);
void archSoundResume(void); 
void archSoundSuspend(void);

#endif
