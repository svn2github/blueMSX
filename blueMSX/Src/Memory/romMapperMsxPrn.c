/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperMsxPrn.c,v $
**
** $Revision: 1.4 $
**
** $Date: 2005-02-11 04:30:25 $
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
#include "romMapperMsxPrn.h"
#include "MediaDb.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "IoPort.h"
#include "PrinterIO.h"
#include <stdlib.h>

typedef struct {
    int deviceHandle;
    UInt8 prnData;
    UInt8 prnStrobe;
    int prnReady;
} RomMapperMsxPrn;

static void saveState(RomMapperMsxPrn* prn)
{
    SaveState* state = saveStateOpenForWrite("MsxPrn");

    saveStateSet(state, "prnData",  prn->prnData);
    saveStateSet(state, "prnStrobe",  prn->prnStrobe);
    
    saveStateClose(state);
}

static void loadState(RomMapperMsxPrn* prn)
{
    SaveState* state = saveStateOpenForRead("MsxPrn");

    prn->prnData  = (UInt8)saveStateGet(state, "prnData",  0);
    prn->prnStrobe  = (UInt8)saveStateGet(state, "prnStrobe",  0);

    saveStateClose(state);
}

static void destroy(RomMapperMsxPrn* prn)
{
    deviceManagerUnregister(prn->deviceHandle);

    ioPortUnregister(0x90);
    ioPortUnregister(0x91);

    printerIODestroy();

    free(prn);
}

static UInt8 readIo(RomMapperMsxPrn* prn, UInt16 ioPort) 
{
    if (prn->prnReady)
        return 0xfd;
	    
    return 0xff;
}

static void writeIo(RomMapperMsxPrn* prn, UInt16 ioPort, UInt8 value) 
{
    switch (ioPort) {
        case 0x90:
            if ((prn->prnStrobe & 2) && !(value & 2))
                printerIOWrite(prn->prnData);

            prn->prnStrobe = value;
            break;
        case 0x91:
            prn->prnData = value;
            break;
    }
}  

static void reset(RomMapperMsxPrn* prn)
{
    prn->prnStrobe = 0;
    prn->prnData = 0;
}

int romMapperMsxPrnCreate(void) 
{
    DeviceCallbacks callbacks = {destroy, reset, saveState, loadState};
    RomMapperMsxPrn* prn;

    prn = malloc(sizeof(RomMapperMsxPrn));

    prn->prnReady = printerIOCreate();

    prn->deviceHandle = deviceManagerRegister(ROM_MSXPRN, &callbacks, prn);

    ioPortRegister(0x90, readIo, writeIo, prn);
    ioPortRegister(0x91, readIo, writeIo, prn);

    reset(prn);

    return 1;
}
