/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Timer.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2004-12-06 07:32:02 $
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
#include "ArchTimer.h"
#include "Win32Common.h"
#include <windows.h>

typedef struct {
    MMRESULT timerId;
} Win32Timer;

static void (*timerCb)(void*) = NULL;
static void* timerId = NULL;

static void syncCallback() {
    if (timerCb) {
        timerCb(timerId);
    }
}

UInt32 archGetSystemUpTime(UInt32 frequency)
{
    static LONGLONG hfFrequency = 0;
    LARGE_INTEGER li;

    if (!hfFrequency) {
        if (QueryPerformanceFrequency(&li)) {
            hfFrequency = li.QuadPart;
        }
        else {
            return 0;
        }
    }

    QueryPerformanceCounter(&li);

    return (DWORD)(li.QuadPart * frequency / hfFrequency);
}

static void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
    syncCallback();
}

static void CALLBACK timerCallback(unsigned int unused1,
                                   unsigned int unused2,
                                   unsigned long unused3,
                                   unsigned long unused4,
                                   unsigned long unused5)
{
    syncCallback();
}

void* archCreateTimer(int period, void (*callback)(void*)) {
    Win32Timer* win32Timer = (Win32Timer*)malloc(sizeof(Win32Timer));

    win32Timer->timerId = 0;
    
    win32Timer->timerId = timeSetEvent(period, period, timerCallback, 0, TIME_PERIODIC);

    if (win32Timer->timerId == 0) {
        SetTimer(getMainHwnd(), 0, period, TimerProc);
    }

    timerCb = callback;
    timerId = win32Timer;

    return win32Timer;
}

void archTimerDestroy(void* timer) 
{
    Win32Timer* win32Timer = (Win32Timer*)timer;

    if (win32Timer == NULL) {
        return;
    }

    if (win32Timer->timerId != 0) {
        timeKillEvent(win32Timer->timerId);
    }
    else {
        KillTimer(getMainHwnd(), 0);
    }

    free(win32Timer);
}


