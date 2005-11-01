/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Input/ColecoJoystick.c,v $
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
#include "ColecoJoystick.h"
#include "InputEvent.h"

#include <stdlib.h>

struct ColecoJoystick {
    ColecoJoystickDevice joyDevice;
    int controller;
};

static UInt8 read(ColecoJoystick* joystick) {
    UInt8 state;

    if (joystick->controller == 0) {
        state = (inputEventGetState(EK_JOY1_UP)      << 0) |
                (inputEventGetState(EK_JOY1_DOWN)    << 1) |
                (inputEventGetState(EK_JOY1_LEFT)    << 2) |
                (inputEventGetState(EK_JOY1_RIGHT)   << 3) |
                (inputEventGetState(EK_JOY1_BUTTON1) << 4) |
                (inputEventGetState(EK_JOY1_BUTTON2) << 5);
    }
    else {
        state = (inputEventGetState(EK_JOY2_UP)      << 0) |
                (inputEventGetState(EK_JOY2_DOWN)    << 1) |
                (inputEventGetState(EK_JOY2_LEFT)    << 2) |
                (inputEventGetState(EK_JOY2_RIGHT)   << 3) |
                (inputEventGetState(EK_JOY2_BUTTON1) << 4) |
                (inputEventGetState(EK_JOY2_BUTTON2) << 5);
    }

    return ~state & 0x3f;
}

ColecoJoystickDevice* colecoJoystickCreate(int controller)
{
    ColecoJoystick* joystick = (ColecoJoystick*)calloc(1, sizeof(ColecoJoystick));
    joystick->joyDevice.read   = read;
    joystick->controller       = controller;
    
    return (ColecoJoystickDevice*)joystick;
}