/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/I8250.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-01-21 12:42:09 $
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
#include "I8250.h"
#include "SaveState.h"
#include <stdlib.h>

#define LCR_DIVISOR_LATCH_ACCESS_BIT 0x80
#define LSR_DATA_READY 0x01
#define LSR_TRANSMITTER_HOLDING_REGISTER_EMPTY 0x20
#define MCR_LOOPBACK_TEST 0x10

typedef enum { I8250PORT_RBR_THR_DLL, I8250PORT_IER_DLM, I8250PORT_IIR, I8250PORT_LCR,
               I8250PORT_MCR, I8250PORT_LSR, I8250PORT_MSR, I8250PORT_SCR } i8250Ports;

typedef enum { I8250REG_RBR, I8250REG_THR, I8250REG_DLL, I8250REG_IER, I8250REG_DLM, I8250REG_IIR,
               I8250REG_LCR, I8250REG_MCR, I8250REG_LSR, I8250REG_MSR, I8250REG_SCR } i8250Registers;

struct I8250
{
    I8250Read readRBR_DLL;   // Receiver Buffer Register (read only), Divisor Latch LSB (DLAB)
    I8250Write writeTHR_DLL; // Transmitter Holding Register (write only), Divisor Latch LSB (DLAB)
    I8250Read readIER_DLM;   // Interrupt Enable Register, Divisor Latch MSB (DLAB)
    I8250Write writeIER_DLM;
    I8250Read readIIR;       // Interrupt Identification register (read only)
    I8250Read readLCR;       // Line Control Register
    I8250Write writeLCR;
    I8250Read readMCR;       // Modem Control register
    I8250Write writeMCR;
    I8250Read readLSR;       // Line Status Register (read only)
    I8250Read readMSR;       // Modem Status Register (read only)
    I8250Read readSCR;       // Scratch Register
    I8250Write writeSCR;
    void* ref;

    UInt8 reg[11];
};

static UInt8 readDummy(void* ref)
{
    return 0xff;
}

static void writeDummy(void* ref, UInt8 value)
{
}

I8250* i8250Create(I8250Read readRBR_DLL, I8250Write writeTHR_DLL,
                   I8250Read readIER_DLM, I8250Write writeIER_DLM,
                   I8250Read readIIR,
                   I8250Read readLCR, I8250Write writeLCR,
                   I8250Read readMCR, I8250Write writeMCR,
                   I8250Read readLSR,
                   I8250Read readMSR,
                   I8250Read readSCR, I8250Write writeSCR,
                   void* ref)
{
    I8250* i8250 = calloc(1, sizeof(I8250));

    i8250->readRBR_DLL  = readRBR_DLL  ? readRBR_DLL  : readDummy;
    i8250->writeTHR_DLL = writeTHR_DLL ? writeTHR_DLL : writeDummy;
    i8250->readIER_DLM  = readIER_DLM  ? readIER_DLM  : readDummy;
    i8250->writeIER_DLM = writeIER_DLM ? writeIER_DLM : writeDummy;
    i8250->readIIR      = readIIR      ? readIIR      : readDummy;
    i8250->readLCR      = readLCR      ? readLCR      : readDummy;
    i8250->writeLCR     = writeLCR     ? writeLCR     : writeDummy;
    i8250->readMCR      = readMCR      ? readMCR      : readDummy;
    i8250->writeMCR     = writeMCR     ? writeMCR     : writeDummy;
    i8250->readLSR      = readLSR      ? readLSR      : readDummy;
    i8250->readMSR      = readMSR      ? readMSR      : readDummy;
    i8250->readSCR      = readSCR      ? readSCR      : readDummy;
    i8250->writeSCR     = writeSCR     ? writeSCR     : writeDummy;
    i8250->ref      = ref;

    return i8250;
}

void i8250Reset(I8250* i8250)
{
    i8250->reg[I8250REG_IER] = 0;
    i8250->reg[I8250REG_IIR] = 1;
    i8250->reg[I8250REG_LCR] = 0;
    i8250->reg[I8250REG_MCR] = 0;
    i8250->reg[I8250REG_LSR] = 0x60;
}

void i8250Destroy(I8250* i8250) 
{
    free(i8250);
}

void i8250LoadState(I8250* i8250)
{
}

void i8250SaveState(I8250* i8250)
{
}

UInt8 i8250Read(I8250* i8250, UInt16 port)
{
    UInt8 value = 0xff;

    port &= 0x7;

    switch (port) {
    case I8250PORT_RBR_THR_DLL:
        if (i8250->reg[I8250REG_LCR] & LCR_DIVISOR_LATCH_ACCESS_BIT)
            value = i8250->reg[I8250REG_DLL];
        else {
            value = i8250->reg[I8250REG_RBR];
            if(i8250->reg[I8250REG_LSR] & LSR_DATA_READY)
                i8250->reg[I8250REG_LSR] &= ~LSR_DATA_READY;
//          i8250ClearInt(n, COM_INT_PENDING_RECEIVED_DATA_AVAILABLE);
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
//      i8250ClearInt(n, COM_INT_PENDING_TRANSMITTER_HOLDING_REGISTER_EMPTY);
        break;

    case I8250PORT_LCR:
        value = i8250->reg[I8250REG_LCR];
        break;

    case I8250PORT_MCR:
        value = i8250->reg[I8250REG_MCR];
        break;

    case I8250PORT_LSR:
        i8250->reg[I8250REG_LSR] |= LSR_TRANSMITTER_HOLDING_REGISTER_EMPTY;
        value = i8250->reg[I8250REG_LSR];
        if(i8250->reg[I8250REG_LSR] & 0x1f)
            i8250->reg[I8250REG_LSR] &= 0xe1; // Clear FE, PE and OE and BREAK bits
//      i8250ClearInt(n, COM_INT_PENDING_RECEIVER_LINE_STATUS);
        break;

    case I8250PORT_MSR:
        if (i8250->reg[I8250REG_MCR] & MCR_LOOPBACK_TEST) {
	    value = i8250->reg[I8250REG_MCR] << 4;
	    i8250->reg[I8250REG_MSR] = (i8250->reg[I8250REG_MSR] ^ value) >> 4;
	    i8250->reg[I8250REG_MSR] |= value;
        }
        value = i8250->reg[I8250REG_MSR];
        i8250->reg[I8250REG_MSR] &= 0xf0; // Reset delta values
//      i8250ClearInt(n, COM_INT_PENDING_MODEM_STATUS_REGISTER);
        break;

    case I8250PORT_SCR:
        value = i8250->reg[I8250REG_SCR];
        break;
    }

    return value;
}

void i8250Write(I8250* i8250, UInt16 port, UInt8 value)
{
    port &= 0x7;

    switch (port) {
    case I8250PORT_RBR_THR_DLL:
        if (i8250->reg[I8250REG_LCR] & LCR_DIVISOR_LATCH_ACCESS_BIT)
            i8250->reg[I8250REG_DLL] = value;
        else {
            i8250->reg[I8250REG_THR] = value;
//          i8250ClearInt(n, COM_INT_PENDING_TRANSMITTER_HOLDING_REGISTER_EMPTY);
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
