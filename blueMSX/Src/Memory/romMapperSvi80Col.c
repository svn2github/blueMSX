/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperSvi80Col.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-01-25 16:57:26 $
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
#include "romMapperSvi80Col.h"
#include "RomMapper.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "IoPort.h"
#include "CRTC6845.h"
#include <stdlib.h>

typedef struct {
    int connector;
    int deviceHandle;
    CRTC6845* crtc6845;
} RomMapperSvi80Col;

static UInt8 memBankCtrl;

static void saveState(RomMapperSvi80Col* svi80col)
{
    SaveState* state = saveStateOpenForWrite("Svi80Col");

    saveStateSet(state, "connector",  svi80col->connector);
    saveStateSet(state, "memBankCtrl",  memBankCtrl);
    
    saveStateClose(state);
}

static void loadState(RomMapperSvi80Col* svi80col)
{
    SaveState* state = saveStateOpenForRead("Svi80Col");

    svi80col->connector  = (UInt8)saveStateGet(state, "connector",  0);
    memBankCtrl  = (UInt8)saveStateGet(state, "memBankCtrl",  0);

    saveStateClose(state);
}

static void destroy(RomMapperSvi80Col* svi80col)
{
    switch (svi80col->connector) {
    case SVI80COL_MSX:
        ioPortUnregister(0x78);
        ioPortUnregister(0x79);
//      ioPortUnregister(0x79); // FIX ME
        break;

    case SVI80COL_SVI:
        ioPortUnregister(0x50);
        ioPortUnregister(0x51);
        ioPortUnregister(0x58);
        break;
    }

    deviceManagerUnregister(svi80col->deviceHandle);

    free(svi80col);
}

static UInt8 readIo(RomMapperSvi80Col* svi80col, UInt16 ioPort) 
{
    return crtcRead(svi80col->crtc6845, ioPort);
}

static void writeIo(RomMapperSvi80Col* svi80col, UInt16 ioPort, UInt8 value) 
{
    crtcWrite(svi80col->crtc6845, ioPort, value);
}  

static void writeIoLatch(RomMapperSvi80Col* svi80col, UInt16 ioPort, UInt8 value) 
{
    crtcWriteLatch(svi80col->crtc6845, ioPort, value);
}  

static void writeIoMemBankCtrl(RomMapperSvi80Col* svi80col, UInt16 ioPort, UInt8 value)
{
    memBankCtrl = value & 1;
}

int svi80colMemBankCtrlStatus(void)
{
   return (memBankCtrl);
}

void svi80colMemWrite(UInt16 address, UInt8 value)
{
    crtcMemWrite(address, value);
}

UInt8 svi80colMemRead(UInt16 address)
{
    return crtcMemRead(address);
}

static void reset(RomMapperSvi80Col* svi80col)
{
    memBankCtrl = 0;
}

int romMapperSvi80ColCreate(Svi80ColConnector connector, int frameRate, UInt8* romData, int size)
{
    DeviceCallbacks callbacks = {destroy, reset, saveState, loadState};
    RomMapperSvi80Col* svi80col;

    if (size != 0x1000)
    	return 0;

    svi80col = malloc(sizeof(RomMapperSvi80Col));
    svi80col->connector  = connector;
    svi80col->deviceHandle = deviceManagerRegister(ROM_SVI80COL, &callbacks, svi80col);

    svi80col->crtc6845 = NULL;
    svi80col->crtc6845 = crtc6845Create(frameRate, romData, size);

    switch (svi80col->connector) {
    case SVI80COL_MSX:
        ioPortRegister(0x78, NULL,   writeIoLatch,       svi80col);
        ioPortRegister(0x79, readIo, writeIo,            svi80col);
//      ioPortRegister(0x79, NULL,   writeIoMemBankCtrl, svi80col); // FIX ME
        break;

    case SVI80COL_SVI:
        ioPortRegister(0x50, NULL,   writeIoLatch,       svi80col);
        ioPortRegister(0x51, readIo, writeIo,            svi80col);
        ioPortRegister(0x58, NULL,   writeIoMemBankCtrl, svi80col);
        break;

    default:
        return 0;
    }

    reset(svi80col);

    return 1;
}
