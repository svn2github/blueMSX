/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/I8251.c,v $
**
** $Revision: 1.7 $
**
** $Date: 2005-07-04 01:54:37 $
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

#include "I8251.h"
#include "SaveState.h"
#include "Board.h"
#include <stdlib.h>

static int transmitDummy(void* ref, UInt8 value) {
    return 0;
}

static int signalDummy(void* ref) {
    return 0;
}
static void setDataBitsDummy(void* ref, int value) {
}
static void setStopBitsDummy(void* ref, int value) {
}
static void setParityDummy(void* ref, int value) {
}

static void setRxReadyDummy(void* ref, int status) {
}

static void setDtrDummy(void* ref, int status) {
}

static void setRtsDummy(void* ref, int status) {
}

static int getDtrDummy(void* ref) {
    return 0;
}

static int getRtsDummy(void* ref) {
    return 0;
}


#define STAT_TXRDY          0x01
#define STAT_RXRDY          0x02
#define STAT_TXEMPTY        0x04
#define STAT_PE             0x08
#define STAT_OE             0x10
#define STAT_FE             0x20
#define STAT_SYNBRK         0x40
#define STAT_DSR            0x80

#define MODE_BAUDRATE       0x03
#define MODE_SYNCHRONOUS    0x00
#define MODE_RATE1          0x01
#define MODE_RATE16         0x02
#define MODE_RATE64         0x03
#define MODE_WORDLENGTH     0x0c
#define MODE_5BIT           0x00
#define MODE_6BIT           0x04
#define MODE_7BIT           0x08
#define MODE_8BIT           0x0c
#define MODE_PARITYEN       0x10
#define MODE_PARITODD       0x00
#define MODE_PARITEVEN      0x20
#define MODE_STOP_BITS      0xc0
#define MODE_STOP_INV       0x00
#define MODE_STOP_1         0x40
#define MODE_STOP_15        0x80
#define MODE_STOP_2         0xc0
#define MODE_SINGLESYNC     0x80

#define CMD_TXEN            0x01
#define CMD_DTR             0x02
#define CMD_RXE             0x04
#define CMD_SBRK            0x08
#define CMD_RSTERR          0x10
#define CMD_RTS             0x20
#define CMD_RESET           0x40
#define CMD_HUNT            0x80

#define PHASE_MODE          0
#define PHASE_SYNC1         1
#define PHASE_SYNC2         2
#define PHASE_CMD           3


struct I8251
{
    I8251Transmit transmit;
    I8251Signal   signal;
    I8251Set      setDataBits;
    I8251Set      setStopBits;
    I8251Set      setParity;
    I8251Set      setRxReady;
    I8251Set      setDtr;
    I8251Set      setRts;
    I8251Get      getDtr;
    I8251Get      getRts;
    void*         ref;
    
    BoardTimer* timerRecv;
    BoardTimer* timerTrans;
    
    UInt32 timeRecv;
    UInt32 timeTrans;

	UInt8 status;
	UInt8 command;
	UInt8 mode;
	UInt8 sync1;
    UInt8 sync2;
	int   charLength;
    int   cmdFaze;

    int   dataBits;
    int   stopBits;
    int   parityEnabled;
    int   parity;
    UInt8 recvBuf;
    int   recvReady;
    UInt8 sendByte;
    UInt8 sendBuffer;
    int   sendBuffered;
};

static void setMode(I8251* i8251, UInt8 value)
{
	int baudrate     = 1;
    int stopBits     = 0;
    int dataBits     = 8;
    int parityEnable = 1;

	i8251->mode = value;
    
	switch (value & MODE_WORDLENGTH) {
	case MODE_5BIT:
        dataBits = 5;
		break;
	case MODE_6BIT:
        dataBits = 6;
		break;
	case MODE_7BIT:
        dataBits = 7;
		break;
	case MODE_8BIT:
        dataBits = 8;
		break;
	}

    i8251->setDataBits(i8251->ref, dataBits);

	switch(value & MODE_STOP_BITS) {
	case MODE_STOP_INV:
        stopBits = 0;
 		break;
	case MODE_STOP_1:
        stopBits = 2;
 		break;
	case MODE_STOP_15:
        stopBits = 3;
 		break;
	case MODE_STOP_2:
        stopBits = 4;
		break;
	}

    i8251->setStopBits(i8251->ref, stopBits);

	switch(value & (MODE_PARITYEN | MODE_PARITEVEN)) {
    case MODE_PARITYEN | MODE_PARITEVEN:
        i8251->setParity(i8251->ref, I8251_PARITY_EVEN);
        break;
    case MODE_PARITYEN:
        i8251->setParity(i8251->ref, I8251_PARITY_ODD);
        break;
    default:
        i8251->setParity(i8251->ref, I8251_PARITY_NONE);
    }

	switch (value & MODE_BAUDRATE) {
	case MODE_SYNCHRONOUS:
		baudrate = 1;
		break;
	case MODE_RATE1:
		baudrate = 1;
		break;
	case MODE_RATE16:
		baudrate = 16;
		break;
	case MODE_RATE64:
		baudrate = 64;
		break;
	}
    
    parityEnable = (value & MODE_PARITYEN) ? 1 : 0;
	i8251->charLength = (((2 * (1 + dataBits + parityEnable)) + stopBits) * baudrate) / 2;
}

static void writeCommand(I8251* i8251, UInt8 value)
{
	UInt8 oldCommand = i8251->command;
	i8251->command = value;

    i8251->setRts(i8251->ref, value & CMD_RTS);
    i8251->setDtr(i8251->ref, value & CMD_DTR);
	
	if (!(value & CMD_TXEN)) {
        boardTimerRemove(i8251->timerTrans);
		i8251->status |= STAT_TXRDY | STAT_TXEMPTY;
	}
	if (value & CMD_RSTERR) {
		i8251->status &= ~(STAT_PE | STAT_OE | STAT_FE);
	}

	if ((value ^ oldCommand) & CMD_RXE) {
		if (value & CMD_RXE) {
			i8251->status &= ~(STAT_PE | STAT_OE | STAT_FE);
			i8251->recvReady = 1;
		} 
        else {
            boardTimerRemove(i8251->timerRecv);
			i8251->status &= ~(STAT_PE | STAT_OE | STAT_FE);
			i8251->status &= ~STAT_RXRDY;
		}
        i8251->signal(i8251->ref);
	}
}

static UInt8 readStatus(I8251* i8251)
{
	UInt8 result = i8251->status;
	if (i8251->getDtr(i8251->ref)) {
		result |= STAT_DSR;
	}
	return result;
}

static UInt8 readTrans(I8251* i8251)
{
	i8251->status &= ~STAT_RXRDY;
    i8251->setRxReady(i8251->ref, 0);
	return i8251->recvBuf;
}

static void writeTrans(I8251* i8251, UInt8 value)
{
	if (!(i8251->command & CMD_TXEN)) {
		return;
	}
	if (i8251->status & STAT_TXEMPTY) {
	    i8251->status &= ~STAT_TXEMPTY;
	    i8251->sendByte = value;

        i8251->timeTrans = (UInt32)(boardSystemTime() + (UInt64)i8251->charLength * boardFrequency() / 4000000);
        boardTimerAdd(i8251->timerTrans, i8251->timeTrans);
	} 
    else {
		i8251->sendBuffer = value;
		i8251->status &= ~STAT_TXRDY;
	}
}

static void onRecv(I8251* i8251, UInt32 time)
{
    i8251->timeRecv  = 0;
	i8251->recvReady = 1;
	i8251->signal(i8251->ref);
}

static void onTrans(I8251* i8251, UInt32 time)
{
    i8251->timeTrans  = 0;

	i8251->transmit(i8251->ref, i8251->sendByte);
	if (i8251->status & STAT_TXRDY) {
		i8251->status |= STAT_TXEMPTY;
	} 
    else {
		i8251->status |= STAT_TXRDY;
	    i8251->status &= ~STAT_TXEMPTY;
	    i8251->sendByte = i8251->sendBuffer;

        i8251->timeTrans = (UInt32)(boardSystemTime() + (UInt64)i8251->charLength * boardFrequency() / 4000000);
        boardTimerAdd(i8251->timerTrans, i8251->timeTrans);
	}
}

UInt8 i8251Read(I8251* i8251, UInt16 port)
{
	switch (port & 1) {
	case 0:
		return readTrans(i8251);
	case 1:
		return readStatus(i8251);
    }
    return 0xff;
}

void i8251Write(I8251* i8251, UInt16 port, UInt8 value)
{
	switch (port & 1) {
	case 0:
		writeTrans(i8251, value);
		break;
	case 1:
		switch (i8251->cmdFaze) {
		case PHASE_MODE:
			setMode(i8251, value);
			if ((i8251->mode & MODE_BAUDRATE) == MODE_SYNCHRONOUS) {
				i8251->cmdFaze = PHASE_SYNC1;
			} 
            else {
				i8251->cmdFaze = PHASE_CMD;
			}
			break;
		case PHASE_SYNC1:
			i8251->sync1 = value;
			if (i8251->mode & MODE_SINGLESYNC) {
				i8251->cmdFaze = PHASE_CMD;
			} 
            else {
				i8251->cmdFaze = PHASE_SYNC2;
			}
			break;
		case PHASE_SYNC2:
			i8251->sync2 = value;
			i8251->cmdFaze = PHASE_CMD;
			break;
		case PHASE_CMD:
			if (value & CMD_RESET) {
				i8251->cmdFaze = PHASE_MODE;
			} 
            else {
				writeCommand(i8251, value);
			}
			break;
		}
		break;
    }
}

void i8251LoadState(I8251* i8251)
{
    SaveState* state = saveStateOpenForRead("i8251");
    
    i8251->timeRecv      = saveStateGet(state, "timeRecv",        0);
    i8251->timeTrans     = saveStateGet(state, "timeTrans",       0);
    i8251->status        = saveStateGet(state, "status",          0);
    i8251->command       = saveStateGet(state, "command",         0);
    i8251->mode          = saveStateGet(state, "mode",            0);
    i8251->sync1         = saveStateGet(state, "sync1",           0);
    i8251->sync2         = saveStateGet(state, "sync2",           0);
    i8251->charLength    = saveStateGet(state, "charLength",      0);
    i8251->cmdFaze       = saveStateGet(state, "cmdFaze",         0);
    i8251->dataBits      = saveStateGet(state, "dataBits",        0);
    i8251->stopBits      = saveStateGet(state, "stopBits",        0);
    i8251->parityEnabled = saveStateGet(state, "parityEnabled",   0);
    i8251->parity        = saveStateGet(state, "parity",          0);
    i8251->recvBuf       = saveStateGet(state, "recvBuf",         0);
    i8251->recvReady     = saveStateGet(state, "recvReady",       0);
    i8251->sendByte      = saveStateGet(state, "sendByte",        0);
    i8251->sendBuffer    = saveStateGet(state, "sendBuffer",      0);
    i8251->sendBuffered  = saveStateGet(state, "sendBuffered",    0);

    if (i8251->timeRecv != 0) {
        boardTimerAdd(i8251->timerRecv, i8251->timeRecv);
    }
    if (i8251->timeTrans != 0) {
        boardTimerAdd(i8251->timerTrans, i8251->timeTrans);
    }
    saveStateClose(state);
}

void i8251SaveState(I8251* i8251)
{
    SaveState* state = saveStateOpenForWrite("i8251");

    saveStateSet(state, "timeRecv",        i8251->timeRecv);
    saveStateSet(state, "timeTrans",       i8251->timeTrans);
    saveStateSet(state, "status",          i8251->status);
    saveStateSet(state, "command",         i8251->command);
    saveStateSet(state, "mode",            i8251->mode);
    saveStateSet(state, "sync1",           i8251->sync1);
    saveStateSet(state, "sync2",           i8251->sync2);
    saveStateSet(state, "charLength",      i8251->charLength);
    saveStateSet(state, "cmdFaze",         i8251->cmdFaze);
    saveStateSet(state, "dataBits",        i8251->dataBits);
    saveStateSet(state, "stopBits",        i8251->stopBits);
    saveStateSet(state, "parityEnabled",   i8251->parityEnabled);
    saveStateSet(state, "parity",          i8251->parity);
    saveStateSet(state, "recvBuf",         i8251->recvBuf);
    saveStateSet(state, "recvReady",       i8251->recvReady);
    saveStateSet(state, "sendByte",        i8251->sendByte);
    saveStateSet(state, "sendBuffer",      i8251->sendBuffer);
    saveStateSet(state, "sendBuffered",    i8251->sendBuffered);

    saveStateClose(state);
}

void i8251Reset(I8251* i8251)
{	
    i8251->status = STAT_TXRDY | STAT_TXEMPTY;
	i8251->command = 0xff;
	writeCommand(i8251, 0);
	i8251->cmdFaze = PHASE_MODE;
}

void i8251RxData(I8251* i8251, UInt8 value)
{
	if (i8251->status & STAT_RXRDY) {
		i8251->status |= STAT_OE;
	} 
    else {
		i8251->recvBuf = value;
		i8251->status |= STAT_RXRDY;
		i8251->setRxReady(i8251->ref, 1);
	}
	i8251->recvReady = 0;

    i8251->timeRecv = (UInt32)(boardSystemTime() + (UInt64)i8251->charLength * boardFrequency() / 4000000);
    boardTimerAdd(i8251->timerRecv, i8251->timeRecv);
}

void i8251Destroy(I8251* i8251) 
{
    boardTimerDestroy(i8251->timerRecv);
    boardTimerDestroy(i8251->timerTrans);

    free(i8251);
}

I8251* i8251Create(I8251Transmit transmit,    I8251Signal   signal,
                   I8251Set      setDataBits, I8251Set      setStopBits,
                   I8251Set      setParity,   I8251Set      setRxReady,
                   I8251Set      setDtr,      I8251Set      setRts,
                   I8251Get      getDtr,      I8251Get      getRts,
                   void* ref)
{
    I8251* i8251 = calloc(1, sizeof(I8251));
    
    i8251->transmit    = transmit    ? transmit    : transmitDummy;
    i8251->signal      = signal      ? signal      : signalDummy;
    i8251->setDataBits = setDataBits ? setDataBits : setDataBitsDummy;
    i8251->setStopBits = setStopBits ? setStopBits : setStopBitsDummy;
    i8251->setParity   = setParity   ? setParity   : setParityDummy;
    i8251->setRxReady  = setRxReady  ? setRxReady  : setRxReadyDummy;
    i8251->setDtr      = setDtr      ? setDtr      : setDtrDummy;
    i8251->setRts      = setRts      ? setRts      : setRtsDummy;
    i8251->getDtr      = getDtr      ? getDtr      : getDtrDummy;
    i8251->getRts      = getRts      ? getRts      : getRtsDummy;
    
    i8251->ref = ref;

    i8251->timerRecv  = boardTimerCreate(onRecv, i8251);
    i8251->timerTrans = boardTimerCreate(onTrans, i8251);

    i8251Reset(i8251);

    return i8251;
}


#if 0

/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/I8251.c,v $
**
** $Revision: 1.7 $
**
** $Date: 2005-07-04 01:54:37 $
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

#include "I8251.h"
#include "SaveState.h"
#include <stdlib.h>

static int transmitDummy(void* ref, UInt8 value) {
    return 0;
}

static int signalDummy(void* ref) {
    return 0;
}
static void setDataBitsDummy(void* ref, int value) {
}
static void setStopBitsDummy(void* ref, int value) {
}
static void setParityDummy(void* ref, int value) {
}

static void setRxReadyDummy(void* ref, int status) {
}

static void setDtrDummy(void* ref, int status) {
}

static void setRtsDummy(void* ref, int status) {
}

static int getDtrDummy(void* ref) {
    return 0;
}

static int getRtsDummy(void* ref) {
    return 0;
}

#define CMD_TXEN   0x01
#define CMD_DTR    0x02
#define CMD_RXE    0x04
#define CMD_SBRK   0x08
#define CMD_RSTERR 0x10
#define CMD_RTS    0x20
#define CMD_RESET  0x40
#define CMD_HUNT   0x80

#define ST_TXRDY   0x01
#define ST_RXRDY   0x02
#define ST_TXEMPTY 0x04
#define ST_PE      0x08
#define ST_OE      0x10
#define ST_FE      0x20
#define ST_SYNBRK  0x40
#define ST_DSR     0x80

typedef enum
{
    I8251_PORT_DATA,
    I8251_PORT_CMD_STAT
} i8251Ports;

typedef enum
{
    I8251_MODE_CONFIG_WAIT,
    I8251_MODE_CONFIG_SYNC1,
    I8251_MODE_CONFIG_SYNC2,
    I8251_MODE_CONFIG_DONE
} i8251MStates;

struct I8251
{
    I8251Transmit transmit;
    I8251Signal   signal;
    I8251Set      setDataBits;
    I8251Set      setStopBits;
    I8251Set      setParity;
    I8251Set      setRxReady;
    I8251Set      setDtr;
    I8251Set      setRts;
    I8251Get      getDtr;
    I8251Get      getRts;

    UInt8         modeConfig;
    UInt8         mode;
    UInt8         command;
    UInt8         status;
    UInt8         data;
    void* ref;
};

UInt8 i8251Read(I8251* usart, UInt16 port)
{
    UInt8 value = 0xff;

    switch (port) {
    case I8251_PORT_DATA:
        value = usart->data;
        usart->status &= ~ST_RXRDY;
        usart->setRxReady(usart, 0);
        break;
    case I8251_PORT_CMD_STAT:
        value = usart->status;
        break;
    }
    return value;
}

void i8251Write(I8251* usart, UInt16 port, UInt8 value)
{
    switch (port) {
    case I8251_PORT_DATA:
        if (usart->modeConfig != I8251_MODE_CONFIG_DONE) {
            switch (usart->modeConfig) {
            case I8251_MODE_CONFIG_WAIT:
                usart->mode = value;
                usart->modeConfig = (value & 0x03) ? I8251_MODE_CONFIG_DONE : I8251_MODE_CONFIG_SYNC1;
                break;
            case I8251_MODE_CONFIG_SYNC1:
                usart->modeConfig = (value & 0x80) ? I8251_MODE_CONFIG_DONE : I8251_MODE_CONFIG_SYNC2;
                break;
            case I8251_MODE_CONFIG_SYNC2:
                usart->modeConfig = I8251_MODE_CONFIG_DONE;
                break;
            }
        }
        else {
            usart->data = value;
            usart->status &= ~ST_TXRDY;
            usart->transmit(usart->ref, value);
        }
        break;
    case I8251_PORT_CMD_STAT:
        usart->command = value;
        break;
    }
}

#define I8251_RX_BUFFER_SIZE 256
#define I8251_RX_BUFFER_MASK (I8251_RX_BUFFER_SIZE - 1)

static UInt8 i8251RxBuffer[I8251_RX_BUFFER_SIZE];
static UInt16 i8251RxBufferHead;
static UInt16 i8251RxBufferTail;
static short int i8251RxBufferDataAvailable;

void i8251RxData(I8251* usart, UInt8 value)
{
    UInt16 unTempRxHead = 0;

    unTempRxHead = (i8251RxBufferHead + 1) & I8251_RX_BUFFER_MASK;

    if(unTempRxHead != i8251RxBufferTail) {
    	i8251RxBuffer[unTempRxHead] = value;
    	i8251RxBufferHead = unTempRxHead;
    	i8251RxBufferDataAvailable = 1;
    }
    else {
    	i8251RxBufferDataAvailable = -1;
    }
}

static short int i8251RxBufferGetByte(UInt8* value)
{
    UInt16 unTempRxTail = 0;

    if(i8251RxBufferHead == i8251RxBufferTail)
        return 0;

    unTempRxTail = (i8251RxBufferTail + 1) & I8251_RX_BUFFER_MASK;
    *value = i8251RxBuffer[unTempRxTail];
    i8251RxBufferTail = unTempRxTail;

    return 1;
}

static UInt16 i8251RxBufferGetLength(void)
{
    return ((i8251RxBufferHead - i8251RxBufferTail) & I8251_RX_BUFFER_MASK);
}

static void i8251RxBufferClear(void)
{
    i8251RxBufferHead = 0;
    i8251RxBufferTail = 0;
    i8251RxBufferDataAvailable = 0;
}

void i8251LoadState(I8251* usart)
{
    SaveState* state = saveStateOpenForRead("i8251");

    saveStateClose(state);
}

void i8251SaveState(I8251* usart)
{
    SaveState* state = saveStateOpenForWrite("i8251");

    saveStateClose(state);
}

void i8251Reset(I8251* usart)
{
    usart->status = ST_TXRDY|ST_TXEMPTY;
    usart->mode = 0;
    usart->modeConfig = I8251_MODE_CONFIG_WAIT;
}

void i8251Destroy(I8251* usart) 
{
    free(usart);
}

I8251* i8251Create(I8251Transmit transmit,    I8251Signal   signal,
                   I8251Set      setDataBits, I8251Set      setStopBits,
                   I8251Set      setParity,   I8251Set      setRxReady,
                   I8251Set      setDtr,      I8251Set      setRts,
                   I8251Get      getDtr,      I8251Get      getRts,
                   void* ref)
{
    I8251* i8251 = calloc(1, sizeof(I8251));
    
    i8251->transmit    = transmit    ? transmit    : transmitDummy;
    i8251->signal      = signal      ? signal      : signalDummy;
    i8251->setDataBits = setDataBits ? setDataBits : setDataBitsDummy;
    i8251->setStopBits = setStopBits ? setStopBits : setStopBitsDummy;
    i8251->setParity   = setParity   ? setParity   : setParityDummy;
    i8251->setRxReady  = setRxReady  ? setRxReady  : setRxReadyDummy;
    i8251->setDtr      = setDtr      ? setDtr      : setDtrDummy;
    i8251->setRts      = setRts      ? setRts      : setRtsDummy;
    i8251->getDtr      = getDtr      ? getDtr      : getDtrDummy;
    i8251->getRts      = getRts      ? getRts      : getRtsDummy;
    
    i8251->ref = ref;

    i8251Reset(i8251);

    return i8251;
}

#endif