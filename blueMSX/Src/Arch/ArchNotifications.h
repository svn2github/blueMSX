/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Arch/ArchNotifications.h,v $
**
** $Revision: 1.6 $
**
** $Date: 2005-01-15 03:06:46 $
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
#ifndef ARCH_NOTIFICATIONS_H
#define ARCH_NOTIFICATIONS_H

typedef enum { SC_NORMAL, SC_SMALL, SC_LARGE } ScreenCaptureType;

void archScreenCapture(ScreenCaptureType type);

void archQuit();
void archUpdateMenu(int show);
void archUpdateWindow();
PropVideoSize archGetWindowedSize();
void archMinimizeWindow();
void archThemeSetNext();
void archThemeUpdate(struct Theme* theme);
void archKeyboardSetSelectedKey(int keyCode);

typedef enum { WH_NORMAL, WH_KBDCONFIG, WH_PROPERTIES } WindowHandler;
void* archWindowCreate(struct Theme* theme, WindowHandler handler);

void archUpdateEmuDisplay(int synchronous, int screenMode, int evenOdd, int interlace);

void archDiskQuickChangeNotify();
void archEmulationStartNotification();
void archEmulationStopNotification();

#endif
