/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/SunriseIDE.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-12-19 07:11:55 $
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
#include "SunriseIde.h"
#include "Board.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>

    

struct SunriseIde {
    int softReset;
    int currentDevice;
};


SunriseIde* sunriseIdeCreate()
{
    SunriseIde* ide = malloc(sizeof(SunriseIde));

    sunriseIdeReset(ide);

    return ide;
}

void sunriseIdeDestroy(SunriseIde* ide)
{
    free(ide);
}

void sunriseIdeReset(SunriseIde* ide)
{
    ide->currentDevice = 0;
    ide->softReset = 0;
//  device[0]->reset(time);
//  device[1]->reset(time);
}

UInt16 sunriseIdeRead(SunriseIde* ide)
{
//  return device[ide->currentDevice]->readData();
}

void sunriseIdeWrite(SunriseIde* ide, UInt16 value)
{
//  device[ide->currentDevice]->writeData(value);
}

UInt8 sunriseIdeReadRegister(SunriseIde* ide, UInt8 reg)
{
    UInt8 value;

    if (reg == 14) {
        reg = 7;
    }

    if (ide->softReset) {
        return 0x7f | (reg == 7 ? 0x80 : 0);
    }

    if (reg == 0) {
        return sunriseIdeRead(ide) & 0xFF;
    } 

//    value = device[ide->currentDevice]->readReg(reg, time);
    if (reg == 6) {
        value = value & ~0x10 | (ide->currentDevice << 4);
    }
    return value;
}

void sunriseIdeWriteRegister(SunriseIde* ide, UInt8 reg, UInt8 value)
{
    if (ide->softReset) {
        if ((reg == 14) && !(value & 0x04)) {
            ide->softReset = 0;
        }
        return;
    }

    if (reg == 0) {
        sunriseIdeWrite(ide, (value << 8) | value);
        return;
    }

    if ((reg == 14) && (value & 0x04)) {
        ide->softReset = 1;
//        device[0]->reset();
//        device[1]->reset();
        return;
    }

    if (reg == 6) {
        ide->currentDevice = (value & 0x10) >> 4;
    }
//    device[ide->currentDevice]->writeReg(reg, value);
}

void sunriseIdeLoadState(SunriseIde* ide)
{
    SaveState* state = saveStateOpenForRead("sunriseIde");

    saveStateClose(state);
}

void sunriseIdeSaveState(SunriseIde* ide)
{
    SaveState* state = saveStateOpenForWrite("sunriseIde");

    saveStateClose(state);
}
