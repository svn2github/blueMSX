/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/MSXMidi.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-04-06 20:47:01 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2005 Daniel Vik, Tomas Karlsson, Johan van Leur
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
#include "MSXMidi.h"
#include "MediaDb.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "IoPort.h"
#include "I8250.h"
#include <stdlib.h>


typedef struct {
    int deviceHandle;
    I8250* i8250;
} MSXMidi;



/*****************************************
** Device Manager callbacks
******************************************
*/
static void saveState(MSXMidi* msxMidi)
{
    SaveState* state = saveStateOpenForWrite("MSXMidi");
    
    saveStateClose(state);

    i8250SaveState(msxMidi->i8250);
}

static void loadState(MSXMidi* msxMidi)
{
    SaveState* state = saveStateOpenForRead("MSXMidi");

    saveStateClose(state);
    
    i8250LoadState(msxMidi->i8250);
}

static void destroy(MSXMidi* msxMidi)
{
    ioPortUnregister(0xe8);
    
    i8250Destroy(msxMidi->i8250);

    deviceManagerUnregister(msxMidi->deviceHandle);
    free(msxMidi);
}

static void reset(MSXMidi* msxMidi) {
}


/*****************************************
** IO Port callbacks
******************************************
*/
static UInt8 readIo(MSXMidi* msxMidi, UInt16 ioPort) 
{
    return 0;
}

static void writeIo(MSXMidi* msxMidi, UInt16 ioPort, UInt8 value) 
{
}


/*****************************************
** I8250 callbacks
******************************************
*/
static int transmit(MSXMidi* msxMidi, UInt8 value) {
    return 0;
}

static int signal(MSXMidi* msxMidi) {
    return 0;
}

static void setDataBits(MSXMidi* msxMidi, int value) {
}

static void setStopBits(MSXMidi* msxMidi, int value) {
}

static void setParity(MSXMidi* msxMidi, int value) {
}

static void setRxReady(MSXMidi* msxMidi, int status) {
}

static void setDtr(MSXMidi* msxMidi, int status) {
}

static void setRts(MSXMidi* msxMidi, int status) {
}

static int getDtr(MSXMidi* msxMidi) {
    return 0;
}

static int getRts(MSXMidi* msxMidi) {
    return 0;
}




/*****************************************
** MSX MIDI Create Method
******************************************
*/
int MSXMidiCreate()
{
    DeviceCallbacks callbacks = {destroy, reset, saveState, loadState};
    MSXMidi* msxMidi;

    msxMidi = malloc(sizeof(MSXMidi));
    
    msxMidi->deviceHandle = deviceManagerRegister(ROM_MSXMIDI, &callbacks, msxMidi);

    msxMidi->i8250 = i8250Create(transmit, signal, setDataBits, setStopBits, setParity, 
                                 setRxReady, setDtr, setRts, getDtr, getRts, msxMidi);

    ioPortRegister(0xe8, readIo, writeIo, msxMidi);

    reset(msxMidi);

    return 1;
}
