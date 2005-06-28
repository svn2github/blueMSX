/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/MSXMidi.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2005-06-28 05:18:26 $
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
#include "Board.h"
#include "IoPort.h"
#include "I8251.h"
#include "I8254.h"
#include <stdlib.h>

int archMidiCreate(void);
void archMidiDestroy(void);
int archMidiTransmit(UInt8 value);
void archMidiSetDataBits(int value);
void archMidiSetStopBits(int value);
void archMidiSetParity(int value);


typedef struct {
    int deviceHandle;
    I8251* i8251;
    I8254* i8254;
    
	int timerIRQlatch;
	int timerIRQenabled;
	int rxrdyIRQlatch;
	int rxrdyIRQenabled;

    int ready;
} MSXMidi;

#define INT_TMR   0x100
#define INT_RXRDY 0x200



/*****************************************
** Device Manager callbacks
******************************************
*/
static void saveState(MSXMidi* msxMidi)
{
    SaveState* state = saveStateOpenForWrite("MSXMidi");
    
    saveStateClose(state);

    i8251SaveState(msxMidi->i8251);
    i8254SaveState(msxMidi->i8254);
}

static void loadState(MSXMidi* msxMidi)
{
    SaveState* state = saveStateOpenForRead("MSXMidi");

    saveStateClose(state);
    
    i8251LoadState(msxMidi->i8251);
    i8254LoadState(msxMidi->i8254);
}

static void destroy(MSXMidi* msxMidi)
{
    ioPortUnregister(0xe8);
    ioPortUnregister(0xe9);
    ioPortUnregister(0xea);
    ioPortUnregister(0xeb);
    ioPortUnregister(0xec);
    ioPortUnregister(0xed);
    ioPortUnregister(0xee);
    ioPortUnregister(0xef);
    
    i8251Destroy(msxMidi->i8251);
    i8254Destroy(msxMidi->i8254);

    deviceManagerUnregister(msxMidi->deviceHandle);
    free(msxMidi);
}

static void reset(MSXMidi* msxMidi) 
{
    boardClearInt(INT_TMR);
    boardClearInt(INT_RXRDY);

	msxMidi->timerIRQlatch   = 0;
	msxMidi->timerIRQenabled = 0;
	msxMidi->rxrdyIRQlatch   = 0;
	msxMidi->rxrdyIRQenabled = 0;

    i8251Reset(msxMidi->i8251);
    i8254Reset(msxMidi->i8254);
}


static void setTimerIRQ(MSXMidi* msxMidi, int status)
{
	if (msxMidi->timerIRQlatch != status) {
		msxMidi->timerIRQlatch = status;
		if (msxMidi->timerIRQenabled) {
			if (msxMidi->timerIRQlatch) {
                boardSetInt(INT_TMR);
			} 
            else {
                boardClearInt(INT_TMR);
			}
		}

        i8254SetGate(msxMidi->i8254, 2, msxMidi->timerIRQenabled && !msxMidi->timerIRQlatch);
	}
}

static void enableTimerIRQ(MSXMidi* msxMidi, int enabled)
{
	if (msxMidi->timerIRQenabled != enabled) {
		msxMidi->timerIRQenabled = enabled;
		if (msxMidi->timerIRQlatch) {
			if (msxMidi->timerIRQenabled) {
                boardSetInt(INT_TMR);
			} 
            else {
                boardClearInt(INT_TMR);
			}
		}
        i8254SetGate(msxMidi->i8254, 2, msxMidi->timerIRQenabled && !msxMidi->timerIRQlatch);
	}
}

static void setRxRDYIRQ(MSXMidi* msxMidi, int status)
{
	if (msxMidi->rxrdyIRQlatch != status) {
		msxMidi->rxrdyIRQlatch = status;
		if (msxMidi->rxrdyIRQenabled) {
			if (msxMidi->rxrdyIRQlatch) {
                boardSetInt(INT_RXRDY);
			}
            else {
                boardClearInt(INT_RXRDY);
			}
		}
	}
}

static void enableRxRDYIRQ(MSXMidi* msxMidi, int enabled)
{
	if (msxMidi->rxrdyIRQenabled != enabled) {
		msxMidi->rxrdyIRQenabled = enabled;
		if (!msxMidi->rxrdyIRQenabled && msxMidi->rxrdyIRQlatch) {
            boardClearInt(INT_RXRDY);
		}
	}
}

/*****************************************
** IO Port callbacks
******************************************
*/
static UInt8 readIo(MSXMidi* msxMidi, UInt16 ioPort) 
{
	switch (ioPort & 7) {
		case 0: // UART data register
		case 1: // UART status register
			return i8251Read(msxMidi->i8251, ioPort & 3);
			break;
		case 2: // timer interrupt flag off
		case 3: // no function
			return 0xff;
		case 4: // counter 0 data port
		case 5: // counter 1 data port
		case 6: // counter 2 data port
		case 7: // timer command register
			return i8254Read(msxMidi->i8254, ioPort & 3);
	}
	return 0xff;
}

static void writeIo(MSXMidi* msxMidi, UInt16 ioPort, UInt8 value) 
{
	switch (ioPort & 7) {
		case 0: // UART data register
		case 1: // UART command register
            i8251Write(msxMidi->i8251, ioPort & 3, value);
			break;
		case 2: // timer interrupt flag off
			setTimerIRQ(msxMidi, 0);
			break;
		case 3: // no function
			break;
		case 4: // counter 0 data port
		case 5: // counter 1 data port
		case 6: // counter 2 data port
		case 7: // timer command register
            i8254Write(msxMidi->i8254, ioPort & 3, value);
			break;
	}
}


/*****************************************
** I8251 callbacks
******************************************
*/
static int transmit(MSXMidi* msxMidi, UInt8 value) 
{
    if (msxMidi->ready) {
        return archMidiTransmit(value);
    }
    return 1;
}

static int signal(MSXMidi* msxMidi)
{
    return 0;
}

static void setDataBits(MSXMidi* msxMidi, int value) 
{
    if (msxMidi->ready) {
        archMidiSetDataBits(value);
    }
}

static void setStopBits(MSXMidi* msxMidi, int value) 
{
    if (msxMidi->ready) {
        archMidiSetStopBits(value);
    }
}

static void setParity(MSXMidi* msxMidi, int value) 
{
    if (msxMidi->ready) {
        archMidiSetParity(value);
    }
}

static void setRxReady(MSXMidi* msxMidi, int status)
{
    setRxRDYIRQ(msxMidi, status);
}

static void setDtr(MSXMidi* msxMidi, int status) 
{
    enableTimerIRQ(msxMidi, status);
}

static void setRts(MSXMidi* msxMidi, int status)
{
    enableRxRDYIRQ(msxMidi, status);
}

static int getDtr(MSXMidi* msxMidi)
{
    return boardGetInt(INT_TMR) ? 1 : 0;
}

static int getRts(MSXMidi* msxMidi)
{
    return 1;
}




/*****************************************
** I8254 callbacks
******************************************
*/
static void pitOut0(MSXMidi* msxMidi, int state) 
{
}

static void pitOut1(MSXMidi* msxMidi, int state) 
{
}

static void pitOut2(MSXMidi* msxMidi, int state) 
{
    setTimerIRQ(msxMidi, 1);
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

    msxMidi->i8254 = i8254Create(4000000, pitOut0, pitOut1, pitOut2, msxMidi);
    msxMidi->i8251 = i8251Create(transmit, signal, setDataBits, setStopBits, setParity, 
                                 setRxReady, setDtr, setRts, getDtr, getRts, msxMidi);

    ioPortRegister(0xe8, readIo, writeIo, msxMidi);
    ioPortRegister(0xe9, readIo, writeIo, msxMidi);
    ioPortRegister(0xea, readIo, writeIo, msxMidi);
    ioPortRegister(0xeb, readIo, writeIo, msxMidi);
    ioPortRegister(0xec, readIo, writeIo, msxMidi);
    ioPortRegister(0xed, readIo, writeIo, msxMidi);
    ioPortRegister(0xee, readIo, writeIo, msxMidi);
    ioPortRegister(0xef, readIo, writeIo, msxMidi);

    msxMidi->ready = archMidiCreate();

    reset(msxMidi);

    return 1;
}
