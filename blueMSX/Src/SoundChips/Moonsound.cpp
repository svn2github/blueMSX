/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/SoundChips/Moonsound.cpp,v $
**
** $Revision: 1.10 $
**
** $Date: 2005-02-06 23:38:59 $
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
        timerValue1(0), timerValue2(0), timerRef1(0xff), timerRef2(0xff) {
        memset(defaultBuffer, 0, sizeof(defaultBuffer));
    }

    Mixer* mixer;
    Int32 handle;

    YMF278* ymf278;
    YMF262* ymf262;
    Int32  buffer[BUFFER_SIZE];
    Int32  defaultBuffer[BUFFER_SIZE];
    BoardTimer* timer1;
    BoardTimer* timer2;
    UInt32 timeout1;
    UInt32 timeout2;
    UInt32 timerValue1;
    UInt32 timerValue2;
    UInt32 timerStarted1;
    UInt32 timerStarted2;
    UInt8  timerRef1;
    UInt8  timerRef2;
    int opl3latch;
    UInt8 opl4latch;
};


void moonsoundTimerStart(void* ref, int timer, int start, UInt8 timerRef);

static void onTimeout1(void* ref, UInt32 time)
{
    Moonsound* moonsound = (Moonsound*)ref;

    moonsoundTimerStart(moonsound, 1, 1, moonsound->timerRef1);
    moonsound->ymf262->callback(moonsound->timerRef1);
}

static void onTimeout2(void* ref, UInt32 time)
{
    Moonsound* moonsound = (Moonsound*)ref;

    moonsoundTimerStart(moonsound, 4, 1, moonsound->timerRef1);
    moonsound->ymf262->callback(moonsound->timerRef1);
}

void moonsoundTimerSet(void* ref, int timer, int count)
{
    Moonsound* moonsound = (Moonsound*)ref;

    if (timer == 1) {
        moonsound->timerValue1 = count;
        if (moonsound->timerStarted1) {
            moonsoundTimerStart(moonsound, timer, 1, moonsound->timerRef1);
        }
    }
    else {
        moonsound->timerValue2 = count;
        if (moonsound->timerStarted2) {
            moonsoundTimerStart(moonsound, timer, 1, moonsound->timerRef2);
        }
    }
}

void moonsoundTimerStart(void* ref, int timer, int start, UInt8 timerRef)
{
    Moonsound* moonsound = (Moonsound*)ref;

    if (timer == 1) {
        moonsound->timerRef1 = timerRef;
        moonsound->timerStarted1 = start;
        if (start) {
            moonsound->timeout1 = boardCalcRelativeTimeout(12380, moonsound->timerValue1);
            boardTimerAdd(moonsound->timer1, moonsound->timeout1);
        }
        else {
            boardTimerRemove(moonsound->timer1);
        }
    }
    else {
        moonsound->timerRef2 = timerRef;
        moonsound->timerStarted2 = start;
        if (start) {
            moonsound->timeout2 = boardCalcRelativeTimeout(12380, moonsound->timerValue2);
            boardTimerAdd(moonsound->timer2, moonsound->timeout2);
        }
        else {
            boardTimerRemove(moonsound->timer2);
        }
    }
}

extern "C" {

void moonsoundDestroy(Moonsound* moonsound) 
{
    mixerUnregisterChannel(moonsound->mixer, moonsound->handle);

    delete moonsound->ymf262;
    delete moonsound->ymf278;
    
    boardTimerDestroy(moonsound->timer1);
    boardTimerDestroy(moonsound->timer2);
}

void moonsoundSaveState(Moonsound* moonsound)
{
    SaveState* state = saveStateOpenForWrite("moonsound");

    saveStateSet(state, "timerValue1",    moonsound->timerValue1);
    saveStateSet(state, "timeout1",       moonsound->timeout1);
    saveStateSet(state, "timerStarted1",  moonsound->timerStarted1);
    saveStateSet(state, "timerRef1",      moonsound->timerRef1);
    saveStateSet(state, "timerValue2",    moonsound->timerValue2);
    saveStateSet(state, "timeout2",       moonsound->timeout2);
    saveStateSet(state, "timerStarted2",  moonsound->timerStarted2);
    saveStateSet(state, "timerRef2",      moonsound->timerRef2);
    saveStateSet(state, "opl3latch", moonsound->opl3latch);
    saveStateSet(state, "opl4latch", moonsound->opl4latch);

    saveStateClose(state);

    moonsound->ymf262->saveState();
    moonsound->ymf278->saveState();
}

void moonsoundLoadState(Moonsound* moonsound)
{
    SaveState* state = saveStateOpenForRead("moonsound");

    moonsound->timerValue1    =        saveStateGet(state, "timerValue1",    0);
    moonsound->timeout1       =        saveStateGet(state, "timeout1",       0);
    moonsound->timerStarted1  =        saveStateGet(state, "timerStarted1",  0);
    moonsound->timerRef1      = (UInt8)saveStateGet(state, "timerRef1",      0);
    moonsound->timerValue2    =        saveStateGet(state, "timerValue2",    0);
    moonsound->timeout2       =        saveStateGet(state, "timeout2",       0);
    moonsound->timerStarted2  =        saveStateGet(state, "timerStarted2",  0);
    moonsound->timerRef2      = (UInt8)saveStateGet(state, "timerRef2",      0);
    moonsound->opl3latch =        saveStateGet(state, "opl3latch", 0);
    moonsound->opl4latch = (UInt8)saveStateGet(state, "opl4latch", 0);

    saveStateClose(state);

    moonsound->ymf262->loadState();
    moonsound->ymf278->loadState();
    
    if (moonsound->timerStarted1) {
        boardTimerAdd(moonsound->timer1, moonsound->timeout1);
    }

    if (moonsound->timerStarted2) {
        boardTimerAdd(moonsound->timer2, moonsound->timeout2);
    }
}

void moonsoundReset(Moonsound* moonsound)
{
    UInt32 systemTime = boardSystemTime();

    moonsound->timerStarted1 = (UInt32)-1;
    moonsound->timerStarted2 = (UInt32)-1;
    moonsound->ymf262->reset(systemTime);
    moonsound->ymf278->reset(systemTime);

    moonsoundTimerStart(moonsound, 1, 0, moonsound->timerRef1);
    moonsoundTimerStart(moonsound, 4, 0, moonsound->timerRef2);
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
    moonsound->timerStarted1 = 0;
    moonsound->timerStarted2 = 0;

    moonsound->timer1 = boardTimerCreate(onTimeout1, moonsound);
    moonsound->timer2 = boardTimerCreate(onTimeout2, moonsound);

    moonsound->handle = mixerRegisterChannel(mixer, MIXER_CHANNEL_MOONSOUND, 1, sync, moonsound);

    moonsound->ymf262 = new YMF262(0, systemTime, moonsound);
    moonsound->ymf262->setSampleRate(SAMPLERATE, boardGetMoonsoundOversampling());
	moonsound->ymf262->setVolume(32767);

    moonsound->ymf278 = new YMF278(0, sramSize, romData, romSize, systemTime);
    moonsound->ymf278->setSampleRate(SAMPLERATE, boardGetMoonsoundOversampling());
    moonsound->ymf278->setVolume(32767);

    return moonsound;
}

}



