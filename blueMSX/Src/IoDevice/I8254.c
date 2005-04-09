/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/I8254.c,v $
**
** $Revision: 1.6 $
**
** $Date: 2005-04-09 06:35:37 $
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

#include "I8254.h"
#include "SaveState.h"
#include "Board.h"
#include <stdlib.h>


typedef struct Counter
{
    UInt16 countingElement;
    UInt16 outputLatch;
    UInt16 countRegister;
    UInt8  controlWord;
    UInt8  statusLatch;

    int outputLatched;
    int statusLatched;
    int readPhase;
    int writePhase;
    int mode;
    int gate;

    int counterLatched;

    int outputState;

    int outPhase;
    int endOutPhase1;
    int endOutPhase2;

    volatile int insideTimerLoop;

    UInt32 frequency;
    
    I8254Out out;
    void* ref;

    BoardTimer* timer; 

    UInt32 refTime;
    UInt32 refFrag;
} Counter;


#define PHASE_NONE 0
#define PHASE_LOW  1
#define PHASE_HI   2

static void counterSetOutput(Counter* counter, int state)
{
    if (state != counter->outputState) {
        counter->out(counter->ref, state);
    }
    counter->outputState = state;
}

static UInt16 counterGetElapsedTime(Counter* counter)
{
    UInt64 elapsed;
    UInt32 elapsedTime;
    UInt32 systemTime = boardSystemTime();

    elapsed          = counter->frequency * (UInt64)(systemTime - counter->refTime) + counter->refFrag;
    counter->refTime = systemTime;
    counter->refFrag = (UInt32)(elapsed % boardFrequency());
    elapsedTime      = (UInt32)(elapsed / boardFrequency());

    return (UInt16)elapsedTime;
}

static void counterSetTimeout(Counter* counter)
{
    int nextTimeout = 0;
    int mode = counter->mode;

    // If counter is disabled, just return
    if (mode != 1 && mode != 5 && counter->gate == 0) {
        return;
    }

    if (counter->outPhase == 1) {
        nextTimeout = counter->countingElement - counter->endOutPhase1;
    }
    else if (counter->outPhase == 2) {
        nextTimeout = counter->countingElement - counter->endOutPhase2;
    }
    
    if (nextTimeout != 0) {
        boardTimerAdd(counter->timer, boardSystemTime() + 
                      (UInt64)boardFrequency() * nextTimeout / counter->frequency);
    }
}

static void counterSync(Counter* counter)
{
    UInt16 elapsedTime;
    int mode;

    // If sync is called recursively, return
    if (counter->insideTimerLoop) {
        return;
    }

    elapsedTime = counterGetElapsedTime(counter);
    mode = counter->mode;

    // If timer is disabled, return 
    if (mode != 1 && mode != 5 && counter->gate == 0) {
        return;
    }

    counter->insideTimerLoop = 1;

    while (counter->insideTimerLoop) {
        if (counter->outPhase == 0) {
            counter->countingElement -= elapsedTime;
            break;
        }

        if (counter->outPhase == 1) {
            if (elapsedTime < counter->countingElement - counter->endOutPhase1) {
                counter->countingElement -= elapsedTime;
                counterSetTimeout(counter);
                break;
            }

            if (mode == 0 || mode == 1) {
                counter->outPhase = 0;
                counter->countingElement -= elapsedTime;
                counterSetOutput(counter, 1);
                break;
            }

            elapsedTime -= counter->countingElement - counter->endOutPhase1;
            counter->countingElement = counter->endOutPhase1;
            counter->outPhase = 2;
            counterSetOutput(counter, 0);
            continue;
        }

        if (counter->outPhase == 2) {
            if (elapsedTime < counter->countingElement - counter->endOutPhase2) {
                counter->countingElement -= elapsedTime;
                counterSetTimeout(counter);
                break;
            }
            
            if (mode == 4 || mode == 5) {
                counter->outPhase = 0;
                counter->countingElement -= elapsedTime;
                counterSetOutput(counter, 1);
                break;
            }
            
            elapsedTime -= counter->countingElement - counter->endOutPhase2;
            counter->countingElement = counter->endOutPhase2;
            counter->outPhase = 1;
            counterSetOutput(counter, 1);
            counter->countingElement = counter->countRegister;
            if (mode == 3) {
                counter->endOutPhase1 = (counter->countRegister + 1) / 2;
            }
            continue;
        }
    }

    counter->insideTimerLoop = 0;
}

static void counterOnTimer(Counter* counter, UInt32 time)
{
    counterSync(counter);
}

static void counterLoad(Counter* counter)
{
    counter->countingElement = counter->countRegister;

    counter->outPhase = 1;

    switch (counter->mode) {
    case 0:
    case 1:
        counter->endOutPhase1 = 0;
        break;
    case 2:
        counter->endOutPhase1 = 2;
        counter->endOutPhase2 = 1;
        break;
    case 3:
        counter->endOutPhase1 = 1 + (counter->countRegister + 1) / 2;
        counter->endOutPhase2 = 1;
        break;
    case 4:
    case 5:
        counter->endOutPhase1 = 1;
        counter->endOutPhase2 = 0;
        break;
    }

    // Force exit from timer loop
    counter->insideTimerLoop = 0;

    counterSetTimeout(counter);
}

static UInt8 counterRead(Counter* counter)
{
    UInt16 outputLatch;

    counterSync(counter);
    
    if (!counter->outputLatched) {
        counter->outputLatch = counter->countingElement;
    }

    if (counter->statusLatched) {
        counter->statusLatched = 0;
        return counter->statusLatch;
    }

    // Modify output latch if mode = 3.
    outputLatch = counter->outputLatch;
    if (counter->mode == 3) {
        if (outputLatch > counter->countRegister / 2) {
            outputLatch = outputLatch - counter->countRegister / 2;
        }
        outputLatch *= 2;
    }

    switch ((counter->controlWord & 0x30) >> 4) {
    case 0:
        return 0xff;

    case 1:
        counter->outputLatched = 0;
        return outputLatch & 0xff;
    case 2:
        counter->outputLatched = 0;
        return outputLatch >> 8;
    case 3:
        if (counter->readPhase == PHASE_LOW) {
            counter->readPhase = PHASE_HI;
            return outputLatch & 0xff;
        }
        counter->outputLatched = 0;
        counter->readPhase = PHASE_LOW;
        return outputLatch >> 8;
    }

    return 0xff;
}

static void counterWrite(Counter* counter, UInt8 value)
{
    counterSync(counter);

    switch ((counter->controlWord & 0x30) >> 4) {
    case 0:
        return;
    case 1:
        counter->countRegister = (counter->countRegister & 0xff00) | value;
        break;
    case 2:
        counter->countRegister = (counter->countRegister & 0x00ff) | (value << 8);
        break;
    case 3:
        if (counter->writePhase == PHASE_LOW) {
            counter->countRegister = (counter->countRegister & 0xff00) | value;
            counter->writePhase = PHASE_HI;
            if (counter->mode == 0) {
                counter->outPhase = 0;
            }
            return;
        }
        else {
            counter->countRegister = (counter->countRegister & 0x00ff) | (value << 8);
            counter->writePhase = PHASE_LOW;
        }
        break;
    }

    if (counter->mode != 1 && counter->mode != 5) {
        counterLoad(counter);
    }
}

static void counterSetGate(Counter* counter, int state)
{
    counterSync(counter);

    if (counter->gate == state) {
        return;
    }

    counter->gate = state;

    if (counter->mode & 0x02) {
        if (state) {
            counterLoad(counter);
        }
        else {
            counterSetOutput(counter, 1);
        }
    }
    else if (counter->mode & 0x01) {
        if (state) {
            counterLoad(counter);
        }
        if (counter->mode == 1) {
            counterSetOutput(counter, 0);
        }
    }

    if ((counter->mode & 1) == 0 && counter->gate == 1) {
        counter->insideTimerLoop = 0;
        counterSetTimeout(counter);
    }
}

static void counterLatchOutput(Counter* counter)
{
    counterSync(counter);

    counter->readPhase = PHASE_LOW;
    counter->outputLatch = counter->countingElement;
    counter->outputLatched = 1;
}

static void counterLatchStatus(Counter* counter)
{
    counterSync(counter);
    counter->statusLatch = counter->controlWord | (counter->outputState ? 0x80 : 0);
    counter->statusLatched = 1;

}

static void counterSetControl(Counter* counter, UInt8 value)
{
    counterSync(counter);

    counter->controlWord = value;

    if ((value & 0x30) == 0x00) {
        counterLatchOutput(counter);
    }
    else {
        counter->writePhase = PHASE_LOW;
        counter->mode = (value & (value & 0x04 ? 0x06 : 0x0e)) >> 1;
        counterSetOutput(counter, counter->mode == 0 ? 0 : 1);
    }
}

static void counterReset(Counter* counter)
{
    counter->readPhase     = PHASE_LOW;
    counter->writePhase    = PHASE_LOW;
    counter->outputLatched = 0;
    counter->statusLatched = 0;
    counter->controlWord   = 0x30;
}

static Counter* counterCreate(I8254Out out, void* ref, UInt32 frequency) 
{
    Counter* counter = calloc(1, sizeof(Counter));

    counter->frequency = frequency;
    counter->out = out;
    counter->ref = ref;

    counter->timer = boardTimerCreate(counterOnTimer, counter);

    counterReset(counter);

    return counter;
}

static void counterDestroy(Counter* counter)
{
    boardTimerDestroy(counter->timer);
    free(counter);
}

struct I8254
{
    Counter* counter1;
    Counter* counter2;
    Counter* counter3;
};

UInt8 i8254Read(I8254* i8254, UInt16 port)
{
	switch (port & 3) {
	case 0:
		return counterRead(i8254->counter1);
	case 1:
		return counterRead(i8254->counter2);
	case 2:
		return counterRead(i8254->counter3);
	}
    return 0xff;
}

void i8254Write(I8254* i8254, UInt16 port, UInt8 value)
{
	switch (port & 3) {
	case 0:
		counterWrite(i8254->counter1, value);
        break;
	case 1:
		counterWrite(i8254->counter2, value);
        break;
	case 2:
		counterWrite(i8254->counter3, value);
        break;
    case 3:
        if ((value & 0xc0) == 0xc0) {
            if (value & 0x02) {
                if (~value & 0x10) counterLatchOutput(i8254->counter1);
                if (~value & 0x20) counterLatchStatus(i8254->counter1);
            }
            if (value & 0x04) {
                if (~value & 0x10) counterLatchOutput(i8254->counter2);
                if (~value & 0x20) counterLatchStatus(i8254->counter2);
            }
            if (value & 0x08) {
                if (~value & 0x10) counterLatchOutput(i8254->counter3);
                if (~value & 0x20) counterLatchStatus(i8254->counter3);
            }
        }
        else {
            switch (value >> 6) {
            case 0:
    		    counterSetControl(i8254->counter1, value & 0x3f);
                break;
            case 1:
    		    counterSetControl(i8254->counter2, value & 0x3f);
                break;
            case 2:
    		    counterSetControl(i8254->counter3, value & 0x3f);
                break;
            }

        }
        break;
	}
}

void i8254SaveState(I8254* i8254)
{
    SaveState* state = saveStateOpenForWrite("i8254");

    saveStateClose(state);
}

void i8254LoadState(I8254* i8254)
{
    SaveState* state = saveStateOpenForRead("i8254");

    saveStateClose(state);
}

void i8254Reset(I8254* i8254)
{
    counterReset(i8254->counter1);
    counterReset(i8254->counter2);
    counterReset(i8254->counter3);
}

void i8254Destroy(I8254* i8254) 
{
    free(i8254);
}

void i8254SetGate(I8254* i8254, I8254Counter counter, int state)
{
	switch (counter) {
	case I8254_COUNTER_1:
		counterSetGate(i8254->counter1, state);
        break;
	case I8254_COUNTER_2:
		counterSetGate(i8254->counter2, state);
        break;
	case I8254_COUNTER_3:
		counterSetGate(i8254->counter3, state);
        break;
	}
}

static void outDummy(void* ref, int state) 
{
}

I8254* i8254Create(UInt32 frequency, I8254Out out1, I8254Out out2, I8254Out out3, void* ref)
{
    I8254* i8254 = calloc(1, sizeof(I8254));
    
    i8254->counter1 = counterCreate(out1 ? out1 : outDummy, ref, frequency);
    i8254->counter2 = counterCreate(out2 ? out2 : outDummy, ref, frequency);
    i8254->counter3 = counterCreate(out3 ? out3 : outDummy, ref, frequency);

    return i8254;
}

///////////////////////

I8254* i8254;


static void i8254out1(void* ref, int state) {
    UInt16 cnt;

    i8254Write(i8254, 3, 0xe2);

    cnt = i8254Read(i8254, 0) | (i8254Read(i8254, 0) << 8);

    printf("Counter 1 = %d  %.4x\n", state, cnt);

    if (state == 0) {
        i8254SetGate(i8254, I8254_COUNTER_3, 1);
        i8254Write(i8254, 3, 0xB0);
        i8254Write(i8254, 2, 0x20);
        i8254Write(i8254, 2, 0x00);
    }
}

static void i8254out2(void* ref, int state) 
{
    UInt16 cnt;

    i8254Write(i8254, 3, 0xe4);

    cnt = i8254Read(i8254, 1) | (i8254Read(i8254, 1) << 8);

    printf("Counter 2 = %d  %.4x\n", state, cnt);
}

static void i8254out3(void* ref, int state) 
{
    UInt16 cnt1, cnt2, cnt3;

    i8254Write(i8254, 3, 0xee);

    cnt1 = i8254Read(i8254, 0) | (i8254Read(i8254, 0) << 8);
    cnt2 = i8254Read(i8254, 1) | (i8254Read(i8254, 1) << 8);
    cnt3 = i8254Read(i8254, 2) | (i8254Read(i8254, 2) << 8);

    printf("Counter 3: %d  %.4x  %.4x  %.4x\n", state, cnt1, cnt2, cnt3);
}


void testI8254() {
    i8254 = i8254Create(4000000, i8254out1, i8254out2, i8254out3, 0);

    i8254SetGate(i8254, I8254_COUNTER_1, 1);
    i8254Write(i8254, 3, 0x34);
    i8254Write(i8254, 0, 0x80);
    i8254Write(i8254, 0, 0x02);

    i8254SetGate(i8254, I8254_COUNTER_2, 1);
    i8254Write(i8254, 3, 0x76);
    i8254Write(i8254, 1, 0x80);
    i8254Write(i8254, 1, 0x01);
}

