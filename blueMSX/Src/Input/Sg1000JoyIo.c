/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Input/Sg1000JoyIo.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2006-07-18 21:09:33 $
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
#include "Sg1000JoyIo.h"
#include "Sg1000Joystick.h"
#include "Sg1000JoystickDevice.h"
#include "JoystickPort.h"
#include "InputEvent.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "MediaDb.h"

#include "SviJoystick.h"

#include <stdlib.h>

struct Sg1000JoyIo {
    Sg1000JoystickDevice* joyDevice[2];
    int joyDeviceHandle;
    int deviceHandle;
};

static void joyIoHandler(Sg1000JoyIo* joyIo, int port, JoystickPortType type)
{
    if (port >= 2) {
        return;
    }

    if (joyIo->joyDevice[port] != NULL && joyIo->joyDevice[port]->destroy != NULL) {
        joyIo->joyDevice[port]->destroy(joyIo->joyDevice[port]);
    }
    
    switch (type) {
    default:
    case JOYSTICK_PORT_NONE:
        joyIo->joyDevice[port] = NULL;
        break;
    case JOYSTICK_PORT_JOYSTICK:
        joyIo->joyDevice[port] = sg1000JoystickCreate(port);
        break;
    }
}

static void loadState(Sg1000JoyIo* joyIo)
{
    int i;
    for (i = 0; i < 2; i++) {
        if (joyIo->joyDevice[i] != NULL && joyIo->joyDevice[i]->loadState != NULL) {
            joyIo->joyDevice[i]->loadState(joyIo->joyDevice[i]);
        }
    }
}

static void saveState(Sg1000JoyIo* joyIo)
{
    int i;
    for (i = 0; i < 2; i++) {
        if (joyIo->joyDevice[i] != NULL && joyIo->joyDevice[i]->saveState != NULL) {
            joyIo->joyDevice[i]->saveState(joyIo->joyDevice[i]);
        }
    }
}

static void reset(Sg1000JoyIo* joyIo)
{
    int i;
    for (i = 0; i < 2; i++) {
        if (joyIo->joyDevice[i] != NULL && joyIo->joyDevice[i]->reset != NULL) {
            joyIo->joyDevice[i]->reset(joyIo->joyDevice[i]);
        }
    }
}

static void destroy(Sg1000JoyIo* joyIo)
{
    int i;
    for (i = 0; i < 2; i++) {
        if (joyIo->joyDevice[i] != NULL && joyIo->joyDevice[i]->destroy != NULL) {
            joyIo->joyDevice[i]->destroy(joyIo->joyDevice[i]);
        }
    }

    joystickPortUpdateHandlerUnregister();

    deviceManagerUnregister(joyIo->deviceHandle);
}

UInt16 sg1000JoyIoRead(Sg1000JoyIo* joyIo) 
{
    UInt16 state = 0xf000;
    if (joyIo->joyDevice[0] != NULL && joyIo->joyDevice[0]->read != NULL) {
        state |= joyIo->joyDevice[0]->read(joyIo->joyDevice[0]) << 0;
    }
    if (joyIo->joyDevice[1] != NULL && joyIo->joyDevice[1]->read != NULL) {
        state |= (UInt16)joyIo->joyDevice[1]->read(joyIo->joyDevice[1]) << 6;
    }
    return state;
}

Sg1000JoyIo* sg1000JoyIoCreate() 
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    Sg1000JoyIo* sg1000JoyIo = (Sg1000JoyIo*)calloc(1, sizeof(Sg1000JoyIo));

    joystickPortUpdateHandlerRegister(joyIoHandler, sg1000JoyIo);

    sg1000JoyIo->deviceHandle = deviceManagerRegister(ROM_UNKNOWN, &callbacks, sg1000JoyIo);

    return sg1000JoyIo;
}

