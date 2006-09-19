/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Input/JoystickPort.c,v $
**
** $Revision: 1.7 $
**
** $Date: 2006-09-19 06:00:19 $
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
#include "JoystickPort.h"
#include "ArchInput.h"
#include "Language.h"
#include <stdlib.h>


static JoystickPortUpdateHandler updateHandler = NULL;
static void* updateHandlerRef;
static JoystickPortType inputType[JOYSTICK_MAX_PORTS];


void joystickPortSetType(int port, JoystickPortType type) 
{
    AmEnableMode mode;
    if (updateHandler != NULL && inputType[port] != type) {
        updateHandler(updateHandlerRef, port, type);
    }

    inputType[port] = type;

    mode = AM_DISABLE;

    if (inputType[0] == JOYSTICK_PORT_MOUSE || 
        inputType[1] == JOYSTICK_PORT_MOUSE)
    {
        mode = AM_ENABLE_MOUSE;
    }

    if (inputType[0] == JOYSTICK_PORT_GUNSTICK || 
        inputType[0] == JOYSTICK_PORT_ASCIILASER || 
        inputType[1] == JOYSTICK_PORT_GUNSTICK || 
        inputType[1] == JOYSTICK_PORT_ASCIILASER)
    {
        mode = AM_ENABLE_LASER;
    }

    archMouseEmuEnable(mode);
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

char* joystickPortTypeToName(int port, JoystickPortType type, int translate)
{
    if (translate) {
        switch(inputType[port]) {
        default:
        case JOYSTICK_PORT_NONE:            return langEnumControlsJoyNone();
        case JOYSTICK_PORT_JOYSTICK:        return langEnumControlsJoy2Button();
        case JOYSTICK_PORT_MOUSE:           return langEnumControlsJoyMouse();
        case JOYSTICK_PORT_TETRIS2DONGLE:   return langEnumControlsJoyTetrisDongle();
        case JOYSTICK_PORT_GUNSTICK:        return langEnumControlsJoyGunStick();
        case JOYSTICK_PORT_COLECOJOYSTICK:  return langEnumControlsJoyColeco();
        case JOYSTICK_PORT_MAGICKEYDONGLE:  return langEnumControlsJoyMagicKeyDongle();
        case JOYSTICK_PORT_ASCIILASER:      return langEnumControlsJoyAsciiLaser();
        }

        return langTextUnknown();
    }

    switch(inputType[port]) {
    default:
    case JOYSTICK_PORT_NONE:            return "none";
    case JOYSTICK_PORT_JOYSTICK:        return "joystick";
    case JOYSTICK_PORT_MOUSE:           return "mouse";
    case JOYSTICK_PORT_TETRIS2DONGLE:   return "tetris2 dongle";
    case JOYSTICK_PORT_GUNSTICK:        return "gunstick";
    case JOYSTICK_PORT_COLECOJOYSTICK:  return "coleco joystick";
    case JOYSTICK_PORT_MAGICKEYDONGLE:  return "magic key dongle";
    case JOYSTICK_PORT_ASCIILASER:      return "ascii laser";
    }

    return "unknown";
}

JoystickPortType joystickPortNameToType(int port, char* name, int translate)
{
    if (translate) {
        if (0 == strcmp(name, langEnumControlsJoy2Button())) return JOYSTICK_PORT_JOYSTICK;
        if (0 == strcmp(name, langEnumControlsJoyMouse())) return JOYSTICK_PORT_MOUSE;
        if (0 == strcmp(name, langEnumControlsJoyTetrisDongle())) return JOYSTICK_PORT_TETRIS2DONGLE;
        if (0 == strcmp(name, langEnumControlsJoyGunStick())) return JOYSTICK_PORT_GUNSTICK;
        if (0 == strcmp(name, langEnumControlsJoyColeco())) return JOYSTICK_PORT_COLECOJOYSTICK;
        if (0 == strcmp(name, langEnumControlsJoyMagicKeyDongle())) return JOYSTICK_PORT_MAGICKEYDONGLE;
        if (0 == strcmp(name, langEnumControlsJoyAsciiLaser())) return JOYSTICK_PORT_ASCIILASER;

        return JOYSTICK_PORT_NONE;
    }

    if (0 == strcmp(name, "joystick")) return JOYSTICK_PORT_JOYSTICK;
    if (0 == strcmp(name, "mouse")) return JOYSTICK_PORT_MOUSE;
    if (0 == strcmp(name, "tetris2 dongle")) return JOYSTICK_PORT_TETRIS2DONGLE;
    if (0 == strcmp(name, "gunstick")) return JOYSTICK_PORT_GUNSTICK;
    if (0 == strcmp(name, "coleco joystick")) return JOYSTICK_PORT_COLECOJOYSTICK;
    if (0 == strcmp(name, "magic key dongle")) return JOYSTICK_PORT_MAGICKEYDONGLE;
    if (0 == strcmp(name, "ascii laser")) return JOYSTICK_PORT_ASCIILASER;

    return JOYSTICK_PORT_NONE;
}
