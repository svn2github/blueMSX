/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/SoundChips/Y8950.c,v $
**
** $Revision: 1.4 $
**
** $Date: 2004-12-26 10:09:55 $
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
#include "Y8950.h"
#include "fmopl.h"
#include "Board.h"
#include "SaveState.h"
#include "IoPort.h"
#include "romMapper.h"
#include "DeviceManager.h"
#include <stdlib.h>
#include <string.h>

#define FREQUENCY        3579545
#define SAMPLERATE       44100
#define BUFFER_SIZE      10000


struct Y8950 {
    Mixer* mixer;
    Int32  handle;

    FM_OPL* opl;
    int    oversampling;
    int    deviceHandle;
    UInt8  address;
    UInt32 timer1;
    UInt32 counter1;
    UInt32 timer2;
    UInt32 counter2;
    Int32  buffer[BUFFER_SIZE];
};

extern INT32 outd;
extern INT32 ams;
extern INT32 vib;
extern INT32 feedback2;

static Y8950* theY8950 = NULL;
static volatile int initialized = 0;

static UInt8 y8950ReadAddress(Y8950* y8950, UInt16 ioPort)
{
    return (UInt8)OPLRead(y8950->opl, 0);
}

static UInt8 y8950ReadData(Y8950* y8950, UInt16 ioPort)
{
    if (y8950->opl->address == 0x14) {
        mixerSync(y8950->mixer);
    }
    return (UInt8)OPLRead(y8950->opl, 1);
}

static void y8950WriteAddress(Y8950* y8950, UInt16 ioPort, UInt8 address)
{
    OPLWrite(y8950->opl, 0, address);
}

static void y8950WriteData(Y8950* y8950, UInt16 ioPort, UInt8 data)
{
    mixerSync(y8950->mixer);

    OPLWrite(y8950->opl, 1, data);
}

static Int32* y8950Sync(void* ref, UInt32 count) 
{
    Y8950* y8950 = (Y8950*)ref;
    UInt32 i;

    for (i = 0; i < count; i++) {
        y8950->buffer[i] = Y8950UpdateOne(y8950->opl);
    }

    return y8950->buffer;
}


static void saveState(Y8950* y8950)
{
    SaveState* state = saveStateOpenForWrite("msxaudio1");

    saveStateSet(state, "address",   y8950->address);
    saveStateSet(state, "timer1",    y8950->timer1);
    saveStateSet(state, "counter1",  y8950->counter1);
    saveStateSet(state, "timer2",    y8950->timer2);
    saveStateSet(state, "counter2",  y8950->counter2);
    saveStateSet(state, "outd",      outd);
    saveStateSet(state, "ams",       ams);
    saveStateSet(state, "vib",       vib);
    saveStateSet(state, "feedback2", feedback2);

    saveStateClose(state);

    Y8950SaveState(y8950->opl);
    YM_DELTAT_ADPCM_SaveState(y8950->opl->deltat);
}

static void loadState(Y8950* y8950)
{
    SaveState* state = saveStateOpenForRead("msxaudio1");

    y8950->address   = (UInt8)saveStateGet(state, "address",   0);
    y8950->timer1    =        saveStateGet(state, "timer1",    0);
    y8950->counter1  =        saveStateGet(state, "counter1",  0);
    y8950->timer2    =        saveStateGet(state, "timer2",    0);
    y8950->counter2  =        saveStateGet(state, "counter2",  0);

    outd      = saveStateGet(state, "outd",      0);
    ams       = saveStateGet(state, "ams",       0);
    vib       = saveStateGet(state, "vib",       0);
    feedback2 = saveStateGet(state, "feedback2", 0);

    saveStateClose(state);

    Y8950LoadState(y8950->opl);
    YM_DELTAT_ADPCM_LoadState(y8950->opl->deltat);
}

static void destroy(Y8950* y8950) {
    initialized = 0;

    deviceManagerUnregister(y8950->deviceHandle);

    ioPortUnregister(0xc0);
    ioPortUnregister(0xc1);

    mixerUnregisterChannel(y8950->mixer, y8950->handle);
    OPLDestroy(y8950->opl);

    theY8950 = NULL;
}

static void reset(Y8950* y8950)
{
    if (theY8950 != NULL) {
        theY8950->counter1 = -1;
        theY8950->counter2 = -1;
        OPLResetChip(theY8950->opl);
    }
}

void y8950SetOversampling(int oversampling)
{
    if (initialized) {
        theY8950->oversampling = oversampling;
        
        OPLSetOversampling(theY8950->opl, theY8950->oversampling);
    }
}

int y8950Create(Mixer* mixer)
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    Y8950* y8950 = (Y8950*)calloc(1, sizeof(Y8950));

    theY8950 = y8950;

    y8950->deviceHandle = deviceManagerRegister(AUDIO_Y8950, &callbacks, y8950);

    y8950->mixer = mixer;
    y8950->counter1 = -1;
    y8950->counter2 = -1;
    y8950->oversampling = 1;

    y8950->handle = mixerRegisterChannel(mixer, MIXER_CHANNEL_MSXAUDIO, 0, y8950Sync, y8950);

    y8950->opl = OPLCreate(OPL_TYPE_Y8950, FREQUENCY, SAMPLERATE, 256);
    OPLSetOversampling(y8950->opl, y8950->oversampling);
    OPLResetChip(y8950->opl);

    initialized = 1;

    ioPortRegister(0xc0, y8950ReadAddress, y8950WriteAddress, y8950);
    ioPortRegister(0xc1, y8950ReadData,    y8950WriteData,    y8950);

    return 1;
}

void y8950TimerSet(int timer, int count)
{
    if (timer == 0) {
        theY8950->timer1 = count;
    }
    else {
        theY8950->timer2 = count;
    }
}

void y8950TimerStart(int timer, int start, UInt8 ref)
{
    if (timer == 0) {
        if ((start != 0) == (theY8950->counter1 == -1)) {
            theY8950->counter1  = start ? theY8950->timer1 : -1;
        }
    }
    else {
        if ((start != 0) == (theY8950->counter2 == -1)) {
            theY8950->counter2  = start ? theY8950->timer2 : -1;
        }
    }
}

void y8950Tick(UInt32 elapsedTime) 
{
    if (theY8950 != NULL) {
        while (elapsedTime--) {
            if (theY8950->counter1 != -1) {
                if (theY8950->counter1-- == 0) {
                    if (OPLTimerOver(theY8950->opl, 0)) {
                        theY8950->counter1 = theY8950->timer1;
                    }
                }
            }

            if (theY8950->counter2 != -1) {
                if (theY8950->counter2-- == 0) {
                    if (OPLTimerOver(theY8950->opl, 1)) {
                        theY8950->counter2 = theY8950->timer2;
                    }
                }
            }
        }
    }
}
