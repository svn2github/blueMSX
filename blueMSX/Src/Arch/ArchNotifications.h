/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Arch/ArchNotifications.h,v $
**
** $Revision: 1.20 $
**
** $Date: 2005-09-24 00:09:49 $
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

void* archScreenCapture(ScreenCaptureType type, int* bitmapSize);

void archQuit();
void archUpdateJoystick();
void archUpdateMenu(int show);
void archVideoOutputChange();
void archUpdateWindow();
int  archGetWindowedSize();
void archMinimizeMainWindow();
void archThemeSetNext();
void archThemeUpdate(struct Theme* theme);
void archPollInput();
void archKeyboardSetSelectedKey(int keyCode);
char* archGetSelectedKey();
char* archGetMappedKey();
int archKeyboardIsKeyConfigured(int msxKeyCode);
int archKeyboardIsKeySelected(int msxKeyCode);

int archGetFramesPerSecond();


char* archKeyconfigSelectedKeyTitle();
char* archKeyconfigMappedToTitle();
char* archKeyconfigMappingSchemeTitle();


void* archWindowCreate(struct Theme* theme, int childWindow);
void archWindowStartMove();
void archWindowMove();
void archWindowEndMove();

void archUpdateEmuDisplayConfig();
int  archUpdateEmuDisplay(int synchronous);

void archDiskQuickChangeNotify();
void archEmulationStartNotification();
void archEmulationStopNotification();
void archEmulationStartFailure();

int archFileExists(const char* fileName);
#endif
