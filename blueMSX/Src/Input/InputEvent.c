/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Input/InputEvent.c,v $
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
#include "InputEvent.h"
#include "ArchInput.h"

int inputEventGetState(int eventCode)
{
    switch (eventCode) {
    case EK_JOY1_UP:        return (archJoystickGetState(0) & 0x01) ? 1 : 0;
    case EK_JOY1_DOWN:      return (archJoystickGetState(0) & 0x02) ? 1 : 0;
    case EK_JOY1_LEFT:      return (archJoystickGetState(0) & 0x04) ? 1 : 0;
    case EK_JOY1_RIGHT:     return (archJoystickGetState(0) & 0x08) ? 1 : 0;
    case EK_JOY1_BUTTON1:   return (archJoystickGetState(0) & 0x10) ? 1 : 0;
    case EK_JOY1_BUTTON2:   return (archJoystickGetState(0) & 0x20) ? 1 : 0;
    case EK_JOY2_UP:        return (archJoystickGetState(1) & 0x01) ? 1 : 0;
    case EK_JOY2_DOWN:      return (archJoystickGetState(1) & 0x02) ? 1 : 0;
    case EK_JOY2_LEFT:      return (archJoystickGetState(1) & 0x04) ? 1 : 0;
    case EK_JOY2_RIGHT:     return (archJoystickGetState(1) & 0x08) ? 1 : 0;
    case EK_JOY2_BUTTON1:   return (archJoystickGetState(1) & 0x10) ? 1 : 0;
    case EK_JOY2_BUTTON2:   return (archJoystickGetState(1) & 0x20) ? 1 : 0;

    case EK_JOY1_BUTTON3:
    case EK_JOY1_BUTTON4:
    case EK_JOY1_BUTTON5:
    case EK_JOY1_BUTTON6:
    case EK_JOY2_BUTTON3:
    case EK_JOY2_BUTTON4:
    case EK_JOY2_BUTTON5:
    case EK_JOY2_BUTTON6:
        return 0;
    default:
        return keyboardGetKeyState(eventCode);
    }
}
