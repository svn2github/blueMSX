/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Window.h,v $
**
** $Revision: 1.2 $
**
** $Date: 2005-01-16 03:23:21 $
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
#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H

#include <windows.h>
#include "Theme.h"

void* archWindowCreate(Theme* theme, int childWindow);
void* archObjectCreate(char* id, void* window, int x, int y, 
                       int width, int height, int arg1, int arg2);
void archObjectDestroy(char* id, void* object);
#endif