/*****************************************************************************
** File:
**      DeviceManager.h
**
** Author:
**      Daniel Vik
**
** Description:
**      Device handling methods
**
** More info:   
**      www.bluemsx.com
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
#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "MSXTypes.h"

typedef struct {
    void  (*destroy)(void*);
    void  (*reset)(void*);
    void  (*saveState)(void*);
    void  (*loadState)(void*);
} DeviceCallbacks;

void deviceManagerCreate();
void deviceManagerDestroy();

void deviceManagerReset();

void deviceManagerLoadState();
void deviceManagerSaveState();

int deviceManagerRegister(int type, DeviceCallbacks* callbacks, void* ref);
void deviceManagerUnregister(int handle);

#endif
