/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Input/ColecoSteeringWheel.c,v $
**
** $Revision: 1.4 $
**
** $Date: 2008-03-30 18:38:40 $
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
#include "ColecoSteeringWheel.h"
#include "InputEvent.h"
#include "ArchInput.h"

#include <stdlib.h>

struct ColecoSteeringWheel {
    ColecoJoystickDevice joyDevice;
    int controller;
    UInt32 pos;
};

static UInt16 read(ColecoSteeringWheel* joystick) {
    UInt16 state = 0;
    UInt16 modPos;
    int dx;
    int dy;

    archMouseGetState(&dx, &dy);

    joystick->pos += dx;

    modPos = (joystick->pos >> 6) & 3;
    modPos ^= (modPos >> 1) & 1;

    state = (archMouseGetButtonState(0) << 4) |
            (modPos << 8);

    return ~state;
}

static void reset(ColecoSteeringWheel* joystick) {
    joystick->pos = 0;
}

static void destroy(ColecoSteeringWheel* joystick) {
    archMouseSetForceLock(1);
}

ColecoJoystickDevice* colecoSteeringWheelCreate(int controller)
{
    ColecoSteeringWheel* joystick = (ColecoSteeringWheel*)calloc(1, sizeof(ColecoSteeringWheel));
    joystick->joyDevice.read    = read;
    joystick->joyDevice.reset   = reset;
    joystick->joyDevice.destroy = destroy;
    joystick->controller        = controller;

    archMouseSetForceLock(1);
   
    return (ColecoJoystickDevice*)joystick;
}