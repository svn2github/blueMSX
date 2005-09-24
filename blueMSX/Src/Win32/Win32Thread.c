/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Thread.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2005-09-24 00:09:50 $
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
#include "ArchThread.h"
#include <windows.h>

void* archThreadCreate(void (*entryPoint)())
{
    DWORD id;
    return CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)entryPoint, NULL, 0, &id);
}

void archThreadDestroy(void* thread)
{
    TerminateThread(thread, 0);
    CloseHandle(thread);
}

void archThreadJoin(void* thread, int timeout)
{
    if (timeout < 0) {
        timeout = INFINITE;
    }

    WaitForSingleObject(thread, timeout);
}


void  archThreadBoostPriority()
{
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
}


void archThreadSleep(int milliseconds) 
{
    Sleep(milliseconds);
}