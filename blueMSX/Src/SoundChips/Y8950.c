/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/SoundChips/Y8950.c,v $
**
** $Revision: 1.5 $
**
** $Date: 2004-12-30 22:53:28 $
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

#define MAX_DEVICES 2

static int overSampling = 1;
static Y8950* theY8950[MAX_DEVICES];

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

static void destroy(Y8950* y8950) 
{
    int i;
    for (i = 0; i < MAX_DEVICES; i++) {
        if (y8950 == theY8950[i]) {
            theY8950[i] = NULL;
        }
    }

    deviceManagerUnregister(y8950->deviceHandle);

    ioPortUnregister(0xc0);
    ioPortUnregister(0xc1);

    mixerUnregisterChannel(y8950->mixer, y8950->handle);
    OPLDestroy(y8950->opl);
}

static void reset(Y8950* y8950)
{
    int i;
    for (i = 0; i < MAX_DEVICES; i++) {
        Y8950* y8950 = theY8950[i];
        if (y8950 != NULL) {
            y8950->counter1 = -1;
            y8950->counter2 = -1;
            OPLResetChip(y8950->opl);
        }
    }
}

int y8950Create(Mixer* mixer)
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    Y8950* y8950;
    int i;
    
    for (i = 0; i < MAX_DEVICES && theY8950[i] != NULL; i++);

    if (i == MAX_DEVICES) {
        return 0;
    }

    y8950 = (Y8950*)calloc(1, sizeof(Y8950));
    y8950->deviceHandle = deviceManagerRegister(AUDIO_Y8950, &callbacks, y8950);

    y8950->mixer = mixer;
    y8950->counter1 = -1;
    y8950->counter2 = -1;

    y8950->handle = mixerRegisterChannel(mixer, MIXER_CHANNEL_MSXAUDIO, 0, y8950Sync, y8950);

    y8950->opl = OPLCreate(OPL_TYPE_Y8950, FREQUENCY, SAMPLERATE, 256, y8950);
    OPLSetOversampling(y8950->opl, overSampling);
    OPLResetChip(y8950->opl);

    for (i = 0; i < MAX_DEVICES; i++) {
        if (theY8950[i] != NULL) {
            theY8950[i] = y8950;
            break;
        }
    }

    ioPortRegister(0xc0, y8950ReadAddress, y8950WriteAddress, y8950);
    ioPortRegister(0xc1, y8950ReadData,    y8950WriteData,    y8950);

    return 1;
}

void y8950TimerSet(void* ref, int timer, int count)
{
    Y8950* y8950 = (Y8950*)ref;

    if (timer == 0) {
        y8950->timer1 = count;
    }
    else {
        y8950->timer2 = count;
    }
}

void y8950TimerStart(void* ptr, int timer, int start, UInt8 ref)
{
    Y8950* y8950 = (Y8950*)ptr;

    if (timer == 0) {
        if ((start != 0) == (y8950->counter1 == -1)) {
            y8950->counter1  = start ? y8950->timer1 : -1;
        }
    }
    else {
        if ((start != 0) == (y8950->counter2 == -1)) {
            y8950->counter2  = start ? y8950->timer2 : -1;
        }
    }
}

void y8950Tick(UInt32 elapsedTime) 
{
    int i;

    for (i = 0; i < MAX_DEVICES; i++) {
        Y8950* y8950 = theY8950[i];
        if (y8950 != NULL) {
            while (elapsedTime--) {
                if (y8950->counter1 != -1) {
                    if (y8950->counter1-- == 0) {
                        if (OPLTimerOver(y8950->opl, 0)) {
                            y8950->counter1 = y8950->timer1;
                        }
                    }
                }

                if (y8950->counter2 != -1) {
                    if (y8950->counter2-- == 0) {
                        if (OPLTimerOver(y8950->opl, 1)) {
                            y8950->counter2 = y8950->timer2;
                        }
                    }
                }
            }
        }
    }
}

void y8950SetOversampling(int oversampling)
{
    int i;

    if (oversampling > 0) {
        overSampling = oversampling;
    }

    for (i = 0; i < MAX_DEVICES; i++) {
        Y8950* y8950 = theY8950[i];
        if (y8950 != NULL) {  
            OPLSetOversampling(y8950->opl, overSampling);
        }
    }
}

