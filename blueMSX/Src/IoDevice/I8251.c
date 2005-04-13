/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/I8251.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2005-04-13 19:15:46 $
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
    I8251PORT_DATA,     // Data port
    I8251PORT_CMD_STAT  // Command and Status port
} i8251Ports;

typedef enum
{
    I8251_STATE_IDLE,    // Idle
    I8251_STATE_DATARX,  // Data Receive
    I8251_STATE_DATATX   // Data Transmit
} i8251States;

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
    I8251Get      getRts;    UInt8         mode;    UInt8         command;    UInt8         status;    UInt8         data;    int           state;
    void* ref;
};

UInt8 i8251Read(I8251* usart, UInt16 port)
{
    UInt8 value = 0xff;

    switch (port) {
    case I8251PORT_DATA:
        value = usart->data;
        break;
    case I8251PORT_CMD_STAT:
        value = usart->status;
        break;
    }
    return value;
}

void i8251Write(I8251* usart, UInt16 port, UInt8 value)
{
    switch (port) {
    case I8251PORT_DATA:
        usart->data = value;
        break;
    case I8251PORT_CMD_STAT:
        usart->command = value;
        break;
    }
}

void i8251SaveState(I8251* usart)
{
    SaveState* state = saveStateOpenForWrite("i8251");

    saveStateClose(state);
}

void i8251LoadState(I8251* usart)
{
    SaveState* state = saveStateOpenForRead("i8251");

    saveStateClose(state);
}

void i8251Reset(I8251* usart)
{
    usart->status = ST_TXRDY|ST_TXEMPTY;
    usart->state = I8251_STATE_IDLE;
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

    return i8251;
}
