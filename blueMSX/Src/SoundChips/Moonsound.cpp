/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/SoundChips/Moonsound.cpp,v $
**
** $Revision: 1.6 $
**
** $Date: 2005-01-02 08:22:12 $
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
    Int32 handle;

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

void moonsoundTimerSet(void* ref, int timer, int count)
{
    Moonsound* moonsound = (Moonsound*)ref;

    if (timer == 1) {
        if (moonsound->counter1 != -1) {
            moonsound->counter1 = count;
        }
        moonsound->timer1 = count;
    }
    else {
        if (moonsound->counter2 != -1) {
            moonsound->counter2 = count;
        }
        moonsound->timer2 = count;
    }
}

void moonsoundTimerStart(void* ref, int timer, int start, UInt8 timerRef)
{
    Moonsound* moonsound = (Moonsound*)ref;

    if (timer == 1) {
        moonsound->timerRef1 = timerRef;
        moonsound->counter1  = start ? moonsound->timer1 : (UInt32)-1;
    }
    else {
        moonsound->timerRef2 = timerRef;
        moonsound->counter2  = start ? moonsound->timer2 : (UInt32)-1;
    }
}

extern "C" {

void moonsoundDestroy(Moonsound* moonsound) 
{
    mixerUnregisterChannel(moonsound->mixer, moonsound->handle);

    delete moonsound->ymf262;
    delete moonsound->ymf278;

    theMoonsound = NULL;
}

void moonsoundSaveState(Moonsound* moonsound)
{
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

void moonsoundLoadState(Moonsound* moonsound)
{
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

void moonsoundReset(Moonsound* moonsound)
{
    UInt32 systemTime = boardSystemTime();

    moonsound->counter1 = (UInt32)-1;
    moonsound->counter2 = (UInt32)-1;
    moonsound->ymf262->reset(systemTime);
    moonsound->ymf278->reset(systemTime);
}

static Int32* sync(void* ref, UInt32 count) 
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

void moonsoundTick(UInt32 elapsedTime) 
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

UInt8 moonsoundRead(Moonsound* moonsound, UInt16 ioPort)
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

void moonsoundWrite(Moonsound* moonsound, UInt16 ioPort, UInt8 value)
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

Moonsound* moonsoundCreate(Mixer* mixer, void* romData, int romSize, int sramSize)
{
    Moonsound* moonsound = new Moonsound;
    UInt32 systemTime = boardSystemTime();

    moonsound->mixer = mixer;
    moonsound->counter1 = (UInt32)-1;
    moonsound->counter2 = (UInt32)-1;

    moonsound->handle = mixerRegisterChannel(mixer, MIXER_CHANNEL_MOONSOUND, 1, sync, moonsound);

    moonsound->ymf262 = new YMF262(0, systemTime, moonsound);
    moonsound->ymf262->setSampleRate(SAMPLERATE, boardGetMoonsoundOversampling());
	moonsound->ymf262->setVolume(32767);

    moonsound->ymf278 = new YMF278(0, sramSize, romData, romSize, systemTime);
    moonsound->ymf278->setSampleRate(SAMPLERATE, boardGetMoonsoundOversampling());
    moonsound->ymf278->setVolume(32767);
    
    theMoonsound = moonsound;

    return moonsound;
}

}



