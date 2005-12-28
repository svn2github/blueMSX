/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/SunriseIDE.c,v $
**
** $Revision: 1.4 $
**
** $Date: 2005-12-28 06:50:18 $
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
#include "HarddiskIde.h"
#include "Board.h"
#include "SaveState.h"
#include "Disk.h"
#include <stdlib.h>
#include <string.h>

    

struct SunriseIde {
    int softReset;
    int currentDevice;
    HarddiskIde* hdide[2];
};


SunriseIde* sunriseIdeCreate(int hdId)
{
    SunriseIde* ide = malloc(sizeof(SunriseIde));

    ide->hdide[0] = harddiskIdeCreate(diskGetHdDriveId(hdId, 0));
    ide->hdide[1] = harddiskIdeCreate(diskGetHdDriveId(hdId, 1));

    sunriseIdeReset(ide);

    return ide;
}

void sunriseIdeDestroy(SunriseIde* ide)
{
    harddiskIdeDestroy(ide->hdide[0]);
    harddiskIdeDestroy(ide->hdide[1]);
    free(ide);
}

void sunriseIdeReset(SunriseIde* ide)
{
    ide->currentDevice = 0;
    ide->softReset = 0;
    harddiskIdeReset(ide->hdide[0]);
    harddiskIdeReset(ide->hdide[1]);
}

UInt16 sunriseIdeRead(SunriseIde* ide)
{
    return harddiskIdeRead(ide->hdide[ide->currentDevice]);
}

void sunriseIdeWrite(SunriseIde* ide, UInt16 value)
{
    harddiskIdeWrite(ide->hdide[ide->currentDevice], value);
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

    value = harddiskIdeReadRegister(ide->hdide[ide->currentDevice], reg);
    if (reg == 6) {
        value = (value & ~0x10) | (ide->currentDevice << 4);
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
        harddiskIdeReset(ide->hdide[0]);
        harddiskIdeReset(ide->hdide[1]);
        return;
    }

    if (reg == 6) {
        ide->currentDevice = (value >> 4) & 1;
    }
    harddiskIdeWriteRegister(ide->hdide[ide->currentDevice], reg, value);
}

void sunriseIdeLoadState(SunriseIde* ide)
{
    SaveState* state = saveStateOpenForRead("sunriseIde");

    saveStateClose(state);

    harddiskIdeLoadState(ide->hdide[0]);
    harddiskIdeLoadState(ide->hdide[1]);
}

void sunriseIdeSaveState(SunriseIde* ide)
{
    SaveState* state = saveStateOpenForWrite("sunriseIde");

    saveStateClose(state);
    
    harddiskIdeSaveState(ide->hdide[0]);
    harddiskIdeSaveState(ide->hdide[1]);
}
