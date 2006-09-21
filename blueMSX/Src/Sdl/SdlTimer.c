/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Sdl/SdlTimer.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2006-09-21 04:28:08 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2006 Daniel Vik
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
******************************************************************************
*/
#include "ArchTimer.h"
#include <stdlib.h>
#include "SDL/SDL.h"

static void (*timerCb)(void*) = NULL;
static UInt32 timerFreq;
static UInt32 lastTimeout;

Uint32 timerCalback(Uint32 interval)
{
    if (timerCb) {
        UInt32 currentTime = archGetSystemUpTime(timerFreq);

        while (lastTimeout != currentTime) {
            lastTimeout = currentTime;
            timerCb(timerCb);
        }
    }
    return interval;
}

void* archCreateTimer(int period, void (*timerCallback)(void*)) 
{ 
    timerFreq = 1000 / period;
    lastTimeout = archGetSystemUpTime(timerFreq);
    timerCb  = timerCallback;

    SDL_SetTimer(period, timerCalback);

    return timerCallback;
}

void archTimerDestroy(void* timer) 
{
    if (timerCb != timer) {
        return;
    }

    SDL_SetTimer(0, NULL);
    timerCb = NULL;
}

UInt32 archGetSystemUpTime(UInt32 frequency) 
{
    return SDL_GetTicks() / (1000 / frequency);
}

UInt32 archGetHiresTimer() {
    return SDL_GetTicks();
}

#if 0
#ifdef WINDOWS_HOST

UInt32 archGetHiresTimer() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return li.LowPart;
}

#else

#include <sys/time.h>

UInt32 archGetHiresTimer() 
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);

    return tv.tv_sec * 1000000 + tv.tv_usec;
}

#endif
#endif