/*****************************************************************************
** File:
**      Win32directx.h
**
** Author:
**      Daniel Vik, Laurent Halter
**
** Description:
**      Direct X draw support
**
** More info:   www.bluemsx.com
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
#ifndef WIN32_DIRECTX_H
#define WIN32_DIRECTX_H

#include <windows.h>
#include "VideoRender.h"

typedef enum { 
    DXE_OK                    =  0,
    DXE_DIRECTDRAWCREATE      = -1,
    DXE_SETCOOPERATIVELEVEL   = -2,
    DXE_SETDISPLAYMODE        = -3,
    DXE_CREATESURFACE         = -4,
    DXE_CREATEATTACHEDSURFACE = -5,
    DXE_CREATECLIPPER         = -6, 
    DXE_SETHWND               = -7,
    DXE_SETCLIPPER            = -8,
    DXE_CREATEFROMWINDOW      = -9
} DirectXError;

void DirectXUpdateSurface(Video* pVideo, void* srcBits, 
                          int srcWidth, int srcHeight, 
                          int* srcDoubleWidth, int noFlip, 
                          int dstPitchY, int dstOffset, int zoom, 
                          int horizontalStretch, int verticalStretch,
                          int evenOddPage, int interlace);
void DirectXExitFullscreenMode();
int DirectXEnterFullscreenMode(HWND hwnd, int width, int height, int depth, 
                               int useVideoBackBuffer, int useSysMemBuffering);
int DirectXEnterWindowedMode(HWND hwnd, int width, int height, 
                             int useVideoBackBuffer, int useSysMemBuffering);
int DirectXUpdateWindowedMode(HWND hwnd, int width, int height, 
                              int useVideoBackBuffer, int useSysMemBuffering);
void DirectXSetGDISurface();

#endif