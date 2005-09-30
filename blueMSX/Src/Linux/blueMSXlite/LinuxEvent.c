/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Linux/blueMSXlite/LinuxEvent.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2005-09-30 05:50:27 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vikl, Tomas Karlsson
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
#include "ArchEvent.h"
#include <semaphore.h>
#include <stdlib.h>

typedef struct {
    void* eventSem;
    void* lockSem;
    int   state;
} Event;

void* archEventCreate(int initState) 
{ 
    Event* e = calloc(1, sizeof(Event));
    e->state = initState ? 1 : 0;
    e->lockSem  = archSemaphoreCreate(1);
    e->eventSem  = archSemaphoreCreate(e->state);
    return e; 
}

void archEventDestroy(void* event) 
{
    Event* e = (Event*)event;
    archSemaphoreDestroy(e->lockSem);
    archSemaphoreDestroy(e->eventSem);
    free(e);
}

void archEventSet(void* event) 
{
    Event* e = (Event*)event;
    archSemaphoreWait(e->lockSem, -1);
    if (e->state == 0) {
        e->state = 1;
        archSemaphoreSignal(e->eventSem);
    }
    archSemaphoreSignal(e->lockSem);
}

void archEventWait(void* event, int timeout) 
{
    Event* e = (Event*)event;
    archSemaphoreWait(e->eventSem, timeout);
    e->state = 0;
}

void* archSemaphoreCreate(int initCount) 
{ 
    void* semaphore = malloc(sizeof(sem_t));

    sem_init((sem_t*)semaphore, 0, initCount);

    return semaphore;
}

void archSemaphoreDestroy(void* semaphore) 
{
    sem_destroy((sem_t*)semaphore);
    free(semaphore);
}

void archSemaphoreSignal(void* semaphore) 
{
    sem_post((sem_t*)semaphore);
}

void archSemaphoreWait(void* semaphore, int timeout) 
{
    sem_wait((sem_t*)semaphore);
}
