/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperSvi328Rs232.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-01-27 01:08:11 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vik, Tomas Karlsson
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
#include "romMapperSvi328Rs232.h"
#include "RomMapper.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "IoPort.h"
#include "I8250.h"
#include <stdlib.h>

typedef struct {
    int connector;
    int deviceHandle;
    I8250* i8250;
} RomMapperSvi328Rs232;

static void saveState(RomMapperSvi328Rs232* rs232)
{
    SaveState* state = saveStateOpenForWrite("Svi328Rs232");

    saveStateSet(state, "connector",  rs232->connector);
    saveStateSet(state, "deviceHandle",  rs232->deviceHandle);
    
    saveStateClose(state);
}

static void loadState(RomMapperSvi328Rs232* rs232)
{
    SaveState* state = saveStateOpenForRead("Svi328Rs232");

    rs232->connector   =        saveStateGet(state, "connector",  0);
    rs232->deviceHandle = (UInt8)saveStateGet(state, "deviceHandle",  0);

    saveStateClose(state);
}

static void destroy(RomMapperSvi328Rs232* rs232)
{
    ioPortUnregister(0x28);
    ioPortUnregister(0x29);
    ioPortUnregister(0x2A);
    ioPortUnregister(0x2B);
    ioPortUnregister(0x2C);
    ioPortUnregister(0x2A);
    ioPortUnregister(0x2D);
    ioPortUnregister(0x2E);

    deviceManagerUnregister(rs232->deviceHandle);

    free(rs232);
}

static UInt8 readIo(RomMapperSvi328Rs232* rs232, UInt16 ioPort) 
{
    return i8250Read(rs232->i8250, ioPort - 0x28);
}

static void writeIo(RomMapperSvi328Rs232* rs232, UInt16 ioPort, UInt8 value) 
{
    i8250Write(rs232->i8250, ioPort - 0x28, value);
}  

int romMapperSvi328Rs232Create(void)
{
    DeviceCallbacks callbacks = {destroy, NULL, saveState, loadState};
    RomMapperSvi328Rs232* rs232;

    rs232 = malloc(sizeof(RomMapperSvi328Rs232));

    rs232->deviceHandle = deviceManagerRegister(ROM_SVI328RS232, &callbacks, rs232);

    rs232->i8250 = NULL;
    rs232->i8250 = i8250Create(readIo, writeIo ,
                              readIo, writeIo ,
                              readIo,
                              readIo, writeIo ,
                              readIo, writeIo ,
                              readIo,
                              readIo,
                              readIo, writeIo ,
                              rs232);

    ioPortRegister(0x28, readIo, writeIo, rs232);
    ioPortRegister(0x29, readIo, writeIo, rs232);
    ioPortRegister(0x2A, readIo, NULL,    rs232);
    ioPortRegister(0x2B, readIo, writeIo, rs232);
    ioPortRegister(0x2C, readIo, writeIo, rs232);
    ioPortRegister(0x2D, readIo, NULL,    rs232);
    ioPortRegister(0x2E, readIo, NULL,    rs232);

    return 1;
}
