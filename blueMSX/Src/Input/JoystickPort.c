/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Input/JoystickPort.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-11-01 21:19:31 $
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
#include "JoystickPort.h"
#include <stdlib.h>


static JoystickPortUpdateHandler updateHandler = NULL;
static void* updateHandlerRef;
static JoystickPortType inputType[JOYSTICK_MAX_PORTS];


void joystickPortSetType(int port, JoystickPortType type) 
{
    if (updateHandler != NULL && inputType[port] != type) {
        updateHandler(updateHandlerRef, port, type);
    }

    inputType[port] = type;
}

JoystickPortType joystickPortGetType(int port)
{
    return inputType[port];
}

void joystickPortUpdateHandlerRegister(JoystickPortUpdateHandler fn, void* ref)
{
    int port;
    updateHandler = fn;
    updateHandlerRef = ref;

    for (port = 0; port < JOYSTICK_MAX_PORTS; port++) {
        updateHandler(updateHandlerRef, port, inputType[port]);
    }
}

void joystickPortUpdateHandlerUnregister()
{
    updateHandler = NULL;
}
