/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/SoundChips/Moonsound.cpp,v $
**
** $Revision: 1.2 $
**
** $Date: 2004-12-06 08:00:54 $
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
#include "Moonsound.h"
#include <string.h>
#include "OpenMsxYMF262.h"
#include "OpenMsxYMF278.h"
extern "C" {
#include "Board.h"
#include "SaveState.h"
#include "IoPort.h"
#include "romMapper.h"
#include "DeviceManager.h"
}

#define FREQUENCY        3579545
#define SAMPLERATE       44100
#define BUFFER_SIZE      2 * 10000
 
struct Moonsound {
    Moonsound() : opl3latch(0), opl4latch(0),
        timer1(0), timer2(0), timerRef1(0xff), timerRef2(0xff) {
        memset(defaultBuffer, 0, sizeof(defaultBuffer));
    }

    Mixer* mixer;
    Int32  Oversampling;
    Int32  deviceHandle;
    YMF278* ymf278;
    YMF262* ymf262;
    Int32  buffer[BUFFER_SIZE];
    Int32  defaultBuffer[BUFFER_SIZE];
    UInt32 timer1;
    UInt32 counter1;
    UInt8  timerRef1;
    UInt32 timer2;
    UInt32 counter2;
    UInt8  timerRef2;
    int opl3latch;
    UInt8 opl4latch;
};

Moonsound* theMoonsound = NULL;

extern "C" static void destroy(void* rm) {
    Moonsound* moonsound = (Moonsound*)rm;
    deviceManagerUnregister(moonsound->deviceHandle);

    ioPortUnregister(0x7e);
    ioPortUnregister(0x7f);
    ioPortUnregister(0xc4);
    ioPortUnregister(0xc5);
    ioPortUnregister(0xc6);
    ioPortUnregister(0xc7);

    mixerUnregisterChannel(moonsound->mixer, MIXER_CHANNEL_MOONSOUND);

    delete moonsound->ymf262;
    delete moonsound->ymf278;

    theMoonsound = NULL;
}

extern "C" static void saveState(void* rm)
{
    Moonsound* moonsound = (Moonsound*)rm;

    SaveState* state = saveStateOpenForWrite("moonsound");

    saveStateSet(state, "timer1",    moonsound->timer1);
    saveStateSet(state, "counter1",  moonsound->counter1);
    saveStateSet(state, "timerRef1", moonsound->timerRef1);
    saveStateSet(state, "timer2",    moonsound->timer2);
    saveStateSet(state, "counter2",  moonsound->counter2);
    saveStateSet(state, "timerRef2", moonsound->timerRef2);
    saveStateSet(state, "opl3latch", moonsound->opl3latch);
    saveStateSet(state, "opl4latch", moonsound->opl4latch);

    saveStateClose(state);

    moonsound->ymf262->saveState();
    moonsound->ymf278->saveState();
}

extern "C" static void loadState(void* rm)
{
    Moonsound* moonsound = (Moonsound*)rm;

    SaveState* state = saveStateOpenForRead("moonsound");

    moonsound->timer1    =        saveStateGet(state, "timer1",    0);
    moonsound->counter1  =        saveStateGet(state, "counter1",  0);
    moonsound->timerRef1 = (UInt8)saveStateGet(state, "timerRef1", 0);
    moonsound->timer2    =        saveStateGet(state, "timer2",    0);
    moonsound->counter2  =        saveStateGet(state, "counter2",  0);
    moonsound->timerRef2 = (UInt8)saveStateGet(state, "timerRef2", 0);
    moonsound->opl3latch =        saveStateGet(state, "opl3latch", 0);
    moonsound->opl4latch = (UInt8)saveStateGet(state, "opl4latch", 0);

    saveStateClose(state);

    moonsound->ymf262->loadState();
    moonsound->ymf278->loadState();
}

extern "C" static void reset(void* rm)
{
    Moonsound* moonsound = (Moonsound*)rm;

    UInt32 systemTime = boardSystemTime();

    moonsound->counter1 = (UInt32)-1;
    moonsound->counter2 = (UInt32)-1;
    moonsound->ymf262->reset(systemTime);
    moonsound->ymf278->reset(systemTime);
}

extern "C" static Int32* sync(void* ref, UInt32 count) 
{
    Moonsound* moonsound = (Moonsound*)ref;
    int* genBuf1 = NULL;
    int* genBuf2 = NULL;
    UInt32 i;

    genBuf1 = moonsound->ymf262->updateBuffer(count);
    if (genBuf1 == NULL) {
        genBuf1 = (int*)moonsound->defaultBuffer;
    }

    genBuf2 = moonsound->ymf278->updateBuffer(count);
    if (genBuf2 == NULL) {
        genBuf2 = (int*)moonsound->defaultBuffer;
    }

    for (i = 0; i < 2 * count; i++) {
        moonsound->buffer[i] = genBuf1[i] + genBuf2[i];
    }

    return moonsound->buffer;
}

void moonsoundTimerSet(int timer, int count)
{
    if (timer == 1) {
        if (theMoonsound->counter1 != -1) {
            theMoonsound->counter1 = count;
        }
        theMoonsound->timer1 = count;
    }
    else {
        if (theMoonsound->counter2 != -1) {
            theMoonsound->counter2 = count;
        }
        theMoonsound->timer2 = count;
    }
}

void moonsoundTimerStart(int timer, int start, UInt8 ref)
{
    if (timer == 1) {
        theMoonsound->timerRef1 = ref;
        theMoonsound->counter1  = start ? theMoonsound->timer1 : (UInt32)-1;
    }
    else {
        theMoonsound->timerRef2 = ref;
        theMoonsound->counter2  = start ? theMoonsound->timer2 : (UInt32)-1;
    }
}

extern "C" void moonsoundTick(UInt32 elapsedTime) 
{
    if (theMoonsound != NULL) {
        while (elapsedTime--) {
            if (theMoonsound->counter1 != -1) {
                if (theMoonsound->counter1-- == 0) {
                    theMoonsound->counter1 = theMoonsound->timer1;
                    theMoonsound->ymf262->callback(theMoonsound->timerRef1);
                }
            }

            if (theMoonsound->counter2 != -1) {
                if (theMoonsound->counter2-- == 0) {
                    theMoonsound->counter2 = theMoonsound->timer2;
                    theMoonsound->ymf262->callback(theMoonsound->timerRef2);
                }
            }
        }
    }
}

extern "C" UInt8 moonsoundRead(Moonsound* moonsound, UInt16 ioPort)
{
	UInt8 result = 0xff;
    UInt32 systemTime = boardSystemTime();

	if (ioPort < 0xC0) {
		switch (ioPort & 0x01) {
		case 1: // read wave register
			result = moonsound->ymf278->readRegOPL4(moonsound->opl4latch, systemTime);
			break;
		}
	} else {
		switch (ioPort & 0x03) {
		case 0: // read status
		case 2:
			result = moonsound->ymf262->readStatus() | 
                     moonsound->ymf278->readStatus(systemTime);
			break;
		case 1:
		case 3: // read fm register
			result = moonsound->ymf262->readReg(moonsound->opl3latch);
			break;
		}
	}

    return result;
}
extern "C" void moonsoundWrite(Moonsound* moonsound, UInt16 ioPort, UInt8 value)
{
    UInt32 systemTime = boardSystemTime();
	if (ioPort < 0xC0) {
		switch (ioPort & 0x01) {
		case 0: // select register
			moonsound->opl4latch = value;
			break;
		case 1:
  			moonsound->ymf278->writeRegOPL4(moonsound->opl4latch, value, systemTime);
			break;
		}
	} else {
		switch (ioPort & 0x03) {
		case 0:
			moonsound->opl3latch = value;
			break;
		case 2: // select register bank 1
			moonsound->opl3latch = value | 0x100;
			break;
		case 1:
		case 3: // write fm register
			moonsound->ymf262->writeReg(moonsound->opl3latch, value, systemTime);
			break;
		}
	}
}

extern "C" void moonsoundSetOversampling(int Oversampling)
{
    if (theMoonsound) {
        theMoonsound->Oversampling = Oversampling;
        
        theMoonsound->ymf262->setSampleRate(SAMPLERATE, theMoonsound->Oversampling);
        theMoonsound->ymf278->setSampleRate(SAMPLERATE, theMoonsound->Oversampling);
    }
}

extern "C" int moonsoundCreate(Mixer* mixer, void* romData, int romSize, int sramSize)
{
    DeviceCallbacks callbacks = { destroy, reset, saveState, loadState };
    Moonsound* moonsound = new Moonsound;
    UInt32 systemTime = boardSystemTime();

    theMoonsound = moonsound;

    moonsound->mixer = mixer;
    moonsound->counter1 = (UInt32)-1;
    moonsound->counter2 = (UInt32)-1;
    moonsound->Oversampling = 1;

    mixerRegisterChannel(mixer, MIXER_CHANNEL_MOONSOUND, 1, sync, moonsound);

    moonsound->deviceHandle = deviceManagerRegister(AUDIO_MOONSOUND, &callbacks, moonsound);

    moonsound->ymf262 = new YMF262(0, systemTime);
    moonsound->ymf262->setSampleRate(SAMPLERATE, moonsound->Oversampling);
	moonsound->ymf262->setVolume(32767);

    moonsound->ymf278 = new YMF278(0, sramSize, romData, romSize, systemTime);
    moonsound->ymf278->setSampleRate(SAMPLERATE, moonsound->Oversampling);
    moonsound->ymf278->setVolume(32767);

    ioPortRegister(0x7e, (IoPortRead)moonsoundRead, (IoPortWrite)moonsoundWrite, moonsound);
    ioPortRegister(0x7f, (IoPortRead)moonsoundRead, (IoPortWrite)moonsoundWrite, moonsound);
    ioPortRegister(0xc4, (IoPortRead)moonsoundRead, (IoPortWrite)moonsoundWrite, moonsound);
    ioPortRegister(0xc5, (IoPortRead)moonsoundRead, (IoPortWrite)moonsoundWrite, moonsound);
    ioPortRegister(0xc6, (IoPortRead)moonsoundRead, (IoPortWrite)moonsoundWrite, moonsound);
    ioPortRegister(0xc7, (IoPortRead)moonsoundRead, (IoPortWrite)moonsoundWrite, moonsound);

    return 1;
}


