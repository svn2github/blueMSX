/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Properties.h,v $
**
** $Revision: 1.3 $
**
** $Date: 2004-12-16 08:02:36 $
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
#ifndef WIN32_PROPERTIES_H
#define WIN32_PROPERTIES_H

#include <windows.h>
#include "Properties.h"
#include "audioMixer.h"
#include "VideoRender.h"
#include "Language.h"
#include "RomMapper.h"
#include "Win32Common.h"

int showProperties(Properties* pProperties, HWND hwndOwner, PropPage startPage, Mixer* mixer, Video* video);

void propertiesInit(char* iniFile);
void propUpdateJoyinfo(Properties* pProperties);

#endif
