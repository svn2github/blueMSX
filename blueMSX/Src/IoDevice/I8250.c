/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/I8250.c,v $
**
** $Revision: 1.4 $
**
** $Date: 2005-04-06 20:47:01 $
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
// TODO:
// - Interrupt handling
// - Handshaking, Flow control
// - Dynamic config of baud rate, data bits, etc.
// - Receive buffers
#include "I8250.h"
#include "SaveState.h"
#include <stdlib.h>

#define LCR_DIVISOR_LATCH_ACCESS_BIT 0x80
#define LSR_DATA_READY 0x01
#define LSR_OVERRUN_ERROR 0x02
#define LSR_TRANSMITTER_HOLDING_REGISTER_EMPTY 0x20
#define LSR_TRANSMITTER_EMPTY 0x40
#define MCR_LOOPBACK_TEST 0x10

typedef enum
{
    I8250PORT_RBR_THR_DLL,  // Receiver Buffer Register (read only), Divisor Latch LSB (DLAB)
                            // Transmitter Holding Register (write only), Divisor Latch LSB (DLAB)
    I8250PORT_IER_DLM,      // Interrupt Enable Register, Divisor Latch MSB (DLAB)
    I8250PORT_IIR,          // Interrupt Identification register (read only)
    I8250PORT_LCR,          // Line Control Register
    I8250PORT_MCR,          // Modem Control register
    I8250PORT_LSR,          // Line Status Register (read only)
    I8250PORT_MSR,          // Modem Status Register (read only)
    I8250PORT_SCR           // Scratch Register
} i8250Ports;

typedef enum { I8250REG_RBR, I8250REG_THR, I8250REG_DLL, I8250REG_IER, I8250REG_DLM, I8250REG_IIR,
               I8250REG_LCR, I8250REG_MCR, I8250REG_LSR, I8250REG_MSR, I8250REG_SCR } i8250Registers;


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

struct I8250
{
    I8250Transmit transmit;
    I8250Signal   signal;
    I8250Set      setDataBits;
    I8250Set      setStopBits;
    I8250Set      setParity;
    I8250Set      setRxReady;
    I8250Set      setDtr;
    I8250Set      setRts;
    I8250Get      getDtr;
    I8250Get      getRts;
    void* ref;

    UInt8 reg[11];
};

void i8250Receive(I8250* i8250, UInt8 value)
{
    i8250->reg[I8250REG_RBR] = value;
    if(i8250->reg[I8250REG_LSR] & LSR_DATA_READY)
        i8250->reg[I8250REG_LSR] |= LSR_OVERRUN_ERROR;
    i8250->reg[I8250REG_LSR] |= LSR_DATA_READY;
}

static void i8250Transmit(I8250* i8250, UInt8 value)
{
    if (i8250->transmit(i8250->ref, value))
        i8250->reg[I8250REG_LSR] &= ~LSR_TRANSMITTER_EMPTY;
}

UInt8 i8250Read(I8250* i8250, UInt16 port)
{
    UInt8 value = 0xff;

    switch (port) {
    case I8250PORT_RBR_THR_DLL:
        if (i8250->reg[I8250REG_LCR] & LCR_DIVISOR_LATCH_ACCESS_BIT)
            value = i8250->reg[I8250REG_DLL];
        else {
            value = i8250->reg[I8250REG_RBR];
            if(i8250->reg[I8250REG_LSR] & LSR_DATA_READY)
                i8250->reg[I8250REG_LSR] &= ~LSR_DATA_READY;
        }
        break;

    case I8250PORT_IER_DLM:
        if (i8250->reg[I8250REG_LCR] & LCR_DIVISOR_LATCH_ACCESS_BIT)
            value = i8250->reg[I8250REG_DLM];
        else
            value = i8250->reg[I8250REG_IER];
        break;

    case I8250PORT_IIR:
        value = i8250->reg[I8250REG_IIR];
        break;

    case I8250PORT_LCR:
        value = i8250->reg[I8250REG_LCR];
        break;

    case I8250PORT_MCR:
        value = i8250->reg[I8250REG_MCR];
        break;

    case I8250PORT_LSR:
//        i8250Receive(i8250);
        i8250->reg[I8250REG_LSR] |= LSR_TRANSMITTER_HOLDING_REGISTER_EMPTY;
        value = i8250->reg[I8250REG_LSR];
        if(i8250->reg[I8250REG_LSR] & 0x1f)
            i8250->reg[I8250REG_LSR] &= 0xe1; // Clear FE, PE and OE and BREAK bits
        break;

    case I8250PORT_MSR:
        if (i8250->reg[I8250REG_MCR] & MCR_LOOPBACK_TEST) {
	    value = i8250->reg[I8250REG_MCR] << 4;
	    i8250->reg[I8250REG_MSR] = (i8250->reg[I8250REG_MSR] ^ value) >> 4;
	    i8250->reg[I8250REG_MSR] |= value;
        }
        value = i8250->reg[I8250REG_MSR];
        i8250->reg[I8250REG_MSR] &= 0xf0; // Reset delta values
        break;

    case I8250PORT_SCR:
        value = i8250->reg[I8250REG_SCR];
        break;
    }

    return value;
}

void i8250Write(I8250* i8250, UInt16 port, UInt8 value)
{
    switch (port) {
    case I8250PORT_RBR_THR_DLL:
        if (i8250->reg[I8250REG_LCR] & LCR_DIVISOR_LATCH_ACCESS_BIT)
            i8250->reg[I8250REG_DLL] = value;
        else {
            i8250->reg[I8250REG_THR] = value;
            i8250Transmit(i8250, value);
        }
        break;

    case I8250PORT_IER_DLM:
        if (i8250->reg[I8250REG_LCR] & LCR_DIVISOR_LATCH_ACCESS_BIT)
            i8250->reg[I8250REG_DLM] = value;
        else
            i8250->reg[I8250REG_IER] = value;
        break;

    case I8250PORT_LCR:
        i8250->reg[I8250REG_LCR] = value;
        break;

    case I8250PORT_MCR:
        i8250->reg[I8250REG_MCR] = value;
        break;

    case I8250PORT_SCR:
        i8250->reg[I8250REG_SCR] = value;
        break;
    }
}

void i8250SaveState(I8250* uart)
{
    SaveState* state = saveStateOpenForWrite("i8250");

    saveStateClose(state);
}

void i8250LoadState(I8250* uart)
{
    SaveState* state = saveStateOpenForRead("i8250");

    saveStateClose(state);
}

void i8250Reset(I8250* i8250)
{
    i8250->reg[I8250REG_IER] = 0;
    i8250->reg[I8250REG_IIR] = 1;
    i8250->reg[I8250REG_LCR] = 0;
    i8250->reg[I8250REG_MCR] = 0;
    i8250->reg[I8250REG_LSR] = 0x60;
}

void i8250Destroy(I8250* uart) 
{
    free(uart);
}

I8250* i8250Create(I8250Transmit transmit,    I8250Signal   signal,
                   I8250Set      setDataBits, I8250Set      setStopBits,
                   I8250Set      setParity,   I8250Set      setRxReady,
                   I8250Set      setDtr,      I8250Set      setRts,
                   I8250Get      getDtr,      I8250Get      getRts,
                   void* ref)
{
    I8250* i8250 = calloc(1, sizeof(I8250));
    
    i8250->transmit    = transmit    ? transmit    : transmitDummy;
    i8250->signal      = signal      ? signal      : signalDummy;
    i8250->setDataBits = setDataBits ? setDataBits : setDataBitsDummy;
    i8250->setStopBits = setStopBits ? setStopBits : setStopBitsDummy;
    i8250->setParity   = setParity   ? setParity   : setParityDummy;
    i8250->setRxReady  = setRxReady  ? setRxReady  : setRxReadyDummy;
    i8250->setDtr      = setDtr      ? setDtr      : setDtrDummy;
    i8250->setRts      = setRts      ? setRts      : setRtsDummy;
    i8250->getDtr      = getDtr      ? getDtr      : getDtrDummy;
    i8250->getRts      = getRts      ? getRts      : getRtsDummy;

    return i8250;
}
