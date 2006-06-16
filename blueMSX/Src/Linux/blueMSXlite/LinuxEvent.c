/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Linux/blueMSXlite/LinuxEvent.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2006-06-16 19:40:54 $
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
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    pthread_mutex_t mutex;
    pthread_mutex_t event;
    int   state;
} Event;

void* archEventCreate(int initState) 
{ 
    Event* e = calloc(1, sizeof(Event));
    e->state = initState ? 1 : 0;
    pthread_mutex_init(&e->mutex, NULL);
    pthread_mutex_init(&e->event, NULL);
    if (e->state == 0) {
        pthread_mutex_lock(&e->event);
    }
    return e; 
}

void archEventDestroy(void* event) 
{
    Event* e = (Event*)event;
    pthread_mutex_destroy(&e->mutex);
    pthread_mutex_destroy(&e->event);
    free(e);
}

void archEventSet(void* event) 
{
    Event* e = (Event*)event;

    pthread_mutex_lock(&e->mutex);
    if (e->state == 0) {
        e->state = 1;
        pthread_mutex_unlock(&e->event);
    }
    pthread_mutex_unlock(&e->mutex);
}

void archEventWait(void* event, int timeout) 
{
    Event* e = (Event*)event;
    
    pthread_mutex_lock(&e->event);
    e->state = 0;
}

typedef struct {
    pthread_mutex_t mutex;
    pthread_mutex_t event;
    int   value;
} Semaphore;

void* archSemaphoreCreate(int initCount) 
{ 
    Semaphore* s = calloc(1, sizeof(Event));
    s->value = initCount;
    pthread_mutex_init(&s->mutex, NULL);
    pthread_mutex_init(&s->event, NULL);
    pthread_mutex_lock(&s->event);

    return s; 
}

void archSemaphoreDestroy(void* semaphore) 
{
    Semaphore* s = (Semaphore*)semaphore;

    pthread_mutex_destroy(&s->mutex);
    pthread_mutex_destroy(&s->event);
    free(s);
}

void archSemaphoreSignal(void* semaphore) 
{
    Semaphore* s = (Semaphore*)semaphore;

    pthread_mutex_lock(&s->mutex);
    s->value++;
    if (s->value == 0) {
        pthread_mutex_unlock(&s->event);
    }
    pthread_mutex_unlock(&s->mutex);
}

void archSemaphoreWait(void* semaphore, int timeout) 
{
    Semaphore* s = (Semaphore*)semaphore;
    int value;

    pthread_mutex_lock(&s->mutex);
    value = --s->value;
    pthread_mutex_unlock(&s->mutex);
    if (value < 0) {
        pthread_mutex_lock(&s->event);
    }
}
