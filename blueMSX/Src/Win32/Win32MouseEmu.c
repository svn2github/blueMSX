/*****************************************************************************
** File:
**      Win32MouseEmu.h
**
** Author:
**      Daniel Vik
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
#include "Win32MouseEmu.h"
 
static HWND mouseHwnd;
static int mouseIsRunning = 0;
static int mouseTimerId;
static RECT mouseCapRect;
static int mouseActive;
static int mouseEnable;
static int mouseDX;
static int mouseDY;
static int mouseLockDX;
static int mouseLockDY;
static int hasMouseLock;
static int mouseForceLock;

static void CALLBACK mouseEmuTimerCallback(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
    POINT pt;

    if (!mouseIsRunning || !mouseActive) {
        if (hasMouseLock) {
            hasMouseLock = 0;
            ShowCursor(TRUE);
            ReleaseCapture();
        }
        return;
    }

    GetCursorPos(&pt);

    ScreenToClient(mouseHwnd, &pt);
    
    if (!mouseForceLock && !PtInRect(&mouseCapRect, pt)) {
        if (hasMouseLock) {
            hasMouseLock = 0;
            ShowCursor(TRUE);
            ReleaseCapture();
        }
        return;
    }

    if (!hasMouseLock) {
        mouseLockDX = 0;
        mouseLockDY = 0;
        mouseDX = 0;
        mouseDY = 0;
        hasMouseLock = 1;
        ShowCursor(FALSE);
        SetCapture(mouseHwnd);
        if (mouseEnable) {
            pt.x = 100;
            pt.y = 100;
            ClientToScreen(mouseHwnd, &pt);
            SetCursorPos(pt.x, pt.y);
        }
    }
    else if (mouseEnable) {
        int DX = 100 - pt.x;
        int DY = 100 - pt.y;

        mouseDX += DX;
        mouseDY += DY;
        mouseLockDX -= DX;
        mouseLockDY -= DY;
    
        pt.x = 100;
        pt.y = 100;

        if (!mouseForceLock) {
            pt.x = mouseLockDX < -600 ? mouseCapRect.left   - 7  : mouseLockDX >  600 ? mouseCapRect.right  + 7  : pt.x;
            pt.y = mouseLockDY < -600 ? mouseCapRect.top    - 7  : mouseLockDY >  600 ? mouseCapRect.bottom + 7  : pt.y;

            if (mouseLockDX < -600 || mouseLockDX > 600 || mouseLockDY < -600 || mouseLockDY > 600) {
                hasMouseLock = 0;
                ShowCursor(TRUE);
                ReleaseCapture();
            }
        }

        ClientToScreen(mouseHwnd, &pt);
        SetCursorPos(pt.x, pt.y);
    }
}

void archMouseSetForceLock(int lock) {
    if (mouseForceLock == lock) {
        return;
    }

    if (lock) {
        if (!hasMouseLock) {
            POINT pt = { 100, 100 };
            ClientToScreen(mouseHwnd, &pt);
            SetCursorPos(pt.x, pt.y);
        }
    }
    else {
        if (hasMouseLock) {
            POINT pt = { 30, -3 };
            ClientToScreen(mouseHwnd, &pt);
            SetCursorPos(pt.x, pt.y);
        }
    }

    mouseForceLock = lock;
}

void mouseEmuInit(HWND hwnd, int timerId) {
    mouseHwnd = hwnd;
    mouseTimerId = timerId;
    SetTimer(mouseHwnd, mouseTimerId, 10, mouseEmuTimerCallback);
}

void mouseEmuSetCaptureInfo(RECT* captureRect) {
    if (captureRect != NULL) {
        memcpy(&mouseCapRect, captureRect, sizeof(RECT));
    }
    else {
        mouseActive = 0;
        memset(&mouseCapRect, 0, sizeof(RECT));
    }
}

void mouseEmuSetRunState(int isRunning) {
    mouseIsRunning = isRunning;
}

void mouseEmuEnable(int enable) {
    mouseEnable = enable;
}

void mouseEmuActivate(int activate) {
    mouseActive = activate;
}

void mouseEmuGetState(int* dx, int* dy) {
    *dx = 0;
    *dy = 0;

    if (hasMouseLock) {
        *dx = mouseDX;
        *dy = mouseDY;

        mouseDX = 0;
        mouseDY = 0;
    }
}

int  mouseEmuGetButtonState(int checkAlways) {
    int buttons = 0;

    if (hasMouseLock || checkAlways) {
        if (GetAsyncKeyState(VK_LBUTTON) > 1UL) {
            buttons |= 1;
        }

        if (GetAsyncKeyState(VK_MBUTTON) > 1UL || GetAsyncKeyState(VK_RBUTTON) > 1UL) {
            buttons |= 2;
        }
    }

    return buttons;
}


