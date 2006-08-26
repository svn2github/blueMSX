/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/rtl8019.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2006-08-26 01:03:35 $
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
#include "RTL8019.h"
#include "Board.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>


#define MEM_SIZE  0x8000
#define MEM_START 0x4000
#define MEM_END   (MEM_START + MEM_SIZE)


typedef struct RTL8019
{
    UInt8  regCr;
    UInt8  regPstart;
    UInt8  regPstop;
    UInt8  regBnry;
    UInt8  regTpsr;
    UInt16 regTbcr;
    UInt8  regIsr;
    UInt16 regRsar;
    UInt16 regRbcr;
    UInt8  regRcr;
    UInt8  regTcr;
    UInt8  regDcr;
    UInt8  regImr;
    UInt8  regCurr;
    UInt16 regClda;
    UInt8  regRppr;
    UInt8  regLppr;
    UInt8  regAcnt;
    UInt8  regTsr;
    UInt8  regNcr;
    UInt8  regFifo;
    UInt16 regCrda;
    UInt8  regRsr;
    UInt8  regCntr0;
    UInt8  regCntr1;
    UInt8  regCntr2;

    UInt8  regPar[6];
    UInt8  regMar[8];
    UInt8  macaddr[32];
    
    UInt8 memory[MEM_SIZE];
};


#define CR_STP          0x01    // Stop command
#define CR_STA          0x02    // Nothing
#define CR_TXP          0x04    // Transmit
#define CR_RD           0x38    // DMA command mode
#define CR_PS           0xc0    // Page select

#define CR_PAGE0        0x00
#define CR_PAGE1        0x40
#define CR_PAGE2        0x80
#define CR_PAGE3        0xc0

#define CR_RD_DMA       0x20    // DMA complete
#define CR_RD_NA        0x00    // Not allowed
#define CR_RD_READ      0x08    // Read
#define CR_RD_WRIE      0x10    // Write
#define CR_RD_SEND      0x18    // Send


#define ISR_PRX         0x01    // Packet receive
#define ISR_PTX         0x02    // Packet transmit
#define ISR_RXE         0x04    // Receive error
#define ISR_TXE         0x08    // Transmit error
#define ISR_OVW         0x10    // Receive buffer overflow
#define ISR_CNT         0x20    // Tally overflow
#define ISR_RDC         0x40    // DMA transfer complete
#define ISR_RST         0x80    // Reset

#define IMR_PRX         0x01    // Packet receive
#define IMR_PTX         0x02    // Packet transmit
#define IMR_RXE         0x04    // Receive error
#define IMR_TXE         0x08    // Transmit error
#define IMR_OVW         0x10    // Receive buffer overflow
#define IMR_CNT         0x20    // Tally overflow
#define IMR_RDC         0x40    // DMA transfer complete
#define IMR_RST         0x80    // Reset


#define RCR_SEP         0x01    // Accept/reject errors
#define RCR_AR          0x02    // Accept/reject packets < 64 bytes
#define RCR_AB          0x04    // Accept/reject broadcast
#define RCR_AM          0x08    // Accept/reject multicast
#define RCR_PRO         0x10    // Accept/reject all physical packets
#define RCR_MON         0x20    // Monitor mode

#define RSR_PRX         0x01    // Receive no error
#define RSR_CRC         0x02    // CRC error
#define RSR_FAE         0x04    // Frame alignment error
#define RSR_BIT3        0x08    // 
#define RSR_MPA         0x10    // Missed packet
#define RSR_PHY         0x20    // Multicast or broadcast packet
#define RSR_DIS         0x40    // Receiver disabled
#define RSR_DFR         0x80    // Carrier or collision detected

#define TCR_CRC         0x01    // CRC logic
#define TCR_LB0         0x02    // Loopback mode
#define TCR_LB1         0x03    // Loopback mode
#define TCR_ATD         0x04    // Auto transmit disable
#define TCR_OFST        0x05    // Collision offset enable
#define TCR_LB_MASK     0x06
#define TCR_LB_NORMAL   0x00
#define TCR_LB_INT      0x02
#define TCR_LB_EXT1     0x04
#define TCR_LB_EXT2     0x06

#define TSR_PTX         0x01    // Transmission complete, no errors
#define TSR_BIT1        0x02
#define TSR_COL         0x04    // Transmission collision
#define TSR_ABT         0x08    // Aborted transmission
#define TSR_CRS         0x10    // Carrier sense lost
#define TSR_BIT5        0x20
#define TSR_CDH         0x40    // CD Heartbeat signal
#define TSR_OWC         0x80    // Out of window collision

#define DCR_WTS         0x01    // 16 bit word transfer
#define DCR_BOS         0x02    // Byte order select
#define DCR_LAS         0x04    // DMA mode (?)
#define DCR_LS          0x08    // Loopback select
#define DCR_ARM         0x10    // Auto initialize remote
#define DCR_FT0         0x20    // Fifo treshold select
#define DCR_FT1         0x40    // Fifo treshold select


static void setIrq(int enable);

static void writeRemoteDma(RTL8019* rtl, UInt8 address, UInt8 value);
static void writeResetDma(RTL8019* rtl, UInt8 address, UInt8 value);
static void writePage0(RTL8019* rtl, UInt8 address, UInt8 value);
static void writePage1(RTL8019* rtl, UInt8 address, UInt8 value);
static void writePage2(RTL8019* rtl, UInt8 address, UInt8 value);
static void writePage3(RTL8019* rtl, UInt8 address, UInt8 value);
static void writeCr(RTL8019* rtl, UInt8 value);

static UInt8 readRemoteDma(RTL8019* rtl, UInt8 address);
static UInt8 readResetDma(RTL8019* rtl, UInt8 address);
static UInt8 readPage0(RTL8019* rtl, UInt8 address);
static UInt8 readPage1(RTL8019* rtl, UInt8 address);
static UInt8 readPage2(RTL8019* rtl, UInt8 address);
static UInt8 readPage3(RTL8019* rtl, UInt8 address);


void rtl8019SaveState(RTL8019* rtl)
{
}

void rtl8019LoadState(RTL8019* rtl)
{
}

RTL8019* rtl8019Create()
{
    RTL8019* rtl = malloc(sizeof(RTL8019));

    rtl8019Reset(rtl);

    return rtl;
}

void rtl8019Destroy(RTL8019* rtl)
{
    free(rtl);
}

void rtl8019Reset(RTL8019* rtl)
{
    rtl->regCr      = CR_RD_DMA | CR_STP;
    rtl->regPstart  = 0;
    rtl->regPstop   = 0;
    rtl->regBnry    = 0;
    rtl->regTpsr    = 0;
    rtl->regTbcr    = 0;
    rtl->regIsr     = ISR_RST;
    rtl->regRsar    = 0;
    rtl->regRbcr    = 0;
    rtl->regRcr     = 0;
    rtl->regTcr     = 0;
    rtl->regDcr     = 0;
    rtl->regImr     = 0;
    rtl->regCurr    = 0;
    rtl->regClda    = 0;
    rtl->regRppr    = 0;
    rtl->regLppr    = 0;
    rtl->regAcnt    = 0;
    rtl->regTsr     = TSR_BIT1 | TSR_BIT5;
    rtl->regNcr     = 0;
    rtl->regFifo    = 0;
    rtl->regCrda    = 0;
    rtl->regRsr     = RSR_BIT3;
    rtl->regCntr0   = 0;
    rtl->regCntr1   = 0;
    rtl->regCntr2   = 0;
    
    memset(rtl->regPar, 0, sizeof(rtl->regPar));
    memset(rtl->regMar, 0, sizeof(rtl->regMar));
    memset(rtl->memory, 0, sizeof(rtl->memory));

    setIrq(0);
}

UInt8 rtl8019Read(RTL8019* rtl, UInt8 address)
{
    if (address == 0x10 || address == 0x11) {
        return readRemoteDma(rtl, address);
    }
    else if (address == 0x1f) {
        return readResetDma(rtl, address);
    }
    else if (address < 0x10) {
        switch (rtl->regCr & CR_PS) {
        case CR_PAGE0:
            return readPage0(rtl, address);
        case CR_PAGE1:
            return readPage1(rtl, address);
        case CR_PAGE2:
            return readPage2(rtl, address);
        case CR_PAGE3:
            return readPage3(rtl, address);
        }
    }
    return 0;
}

void rtl8019Write(RTL8019* rtl, UInt8 address, UInt8 value)
{
    if (address == 0x10 || address == 0x11) {
        writeRemoteDma(rtl, address, value);
    }
    else if (address == 0x1f) {
        writeResetDma(rtl, address, value);
    }
    else if (address < 0x10) {
        switch (rtl->regCr & CR_PS) {
        case CR_PAGE0:
            writePage0(rtl, address, value);
            break;
        case CR_PAGE1:
            writePage1(rtl, address, value);
            break;
        case CR_PAGE2:
            writePage2(rtl, address, value);
            break;
        case CR_PAGE3:
            writePage3(rtl, address, value);
            break;
        }
    }
}


static void setIrq(int enable)
{
    // FIXME
}


static void writeCr(RTL8019* rtl, UInt8 value)
{
}

static void writeRemoteDma(RTL8019* rtl, UInt8 address, UInt8 value)
{
    // If 8 bit mode, don't allow writes to second DMA port
    if ((address & 1) && !(rtl->regDcr & DCR_WTS)) {
        return;
    }

    if (rtl->regRbcr == 0) {
        // No data to write
        return;
    }

    if (rtl->regCrda >= MEM_START && rtl->regCrda < MEM_END) {
        rtl->memory[rtl->regCrda - MEM_START] = value;
    }
    rtl->regCrda++;
    if (rtl->regCrda == rtl->regPstop << 8) {
        rtl->regCrda = rtl->regPstart << 8;
    }

    rtl->regRbcr--;
    if (rtl->regRbcr == 0) {
        rtl->regIsr |= ISR_RDC;
        setIrq(rtl->regImr & IMR_RDC);
    }
}

static void writeResetDma(RTL8019* rtl, UInt8 address, UInt8 value)
{
}

static void writePage0(RTL8019* rtl, UInt8 address, UInt8 value)
{
    switch (address) {
    case 0x00:
        writeCr(rtl, value);
        break;
    case 0x01:
        rtl->regPstart = value;
        break;
    case 0x02:
        rtl->regPstop = value;
        break;
    case 0x03:
        rtl->regBnry = value;
        break;
    case 0x04:
        rtl->regTpsr = value;
        break;
    case 0x05:
        rtl->regTbcr = (rtl->regTbcr & 0xff00) | value;
        break;
    case 0x06:
        rtl->regTbcr = (rtl->regTbcr & 0x00ff) | ((UInt16)value << 8);
        break;
    case 0x07:
        rtl->regIsr = (rtl->regIsr & ISR_RST) | (rtl->regIsr & ~(value & 0x7f));
        if ((rtl->regIsr & rtl->regImr) == 0) {
            setIrq(0);
        }
        break;
    case 0x08:
        rtl->regRsar = (rtl->regRsar & 0xff00) | value;
        rtl->regCrda = rtl->regRsar;
        break;
    case 0x09:
        rtl->regRsar = (rtl->regRsar & 0x00ff) | ((UInt16)value << 8);
        rtl->regCrda = rtl->regRsar;
        break;
    case 0x0a:
        rtl->regRbcr = (rtl->regRbcr & 0xff00) | value;
        break;
    case 0x0b:
        rtl->regRbcr = (rtl->regRbcr & 0x00ff) | ((UInt16)value << 8);
        break;
    case 0x0c:
        rtl->regRcr = value & 0x3f;
        break;
    case 0x0d:
        rtl->regTcr = value & 0x1f;
        break;
    case 0x0e:
        rtl->regDcr = value & 0x3f;
        break;
    case 0x0f:
        rtl->regImr = value & 0x7f;
        setIrq(rtl->regIsr & rtl->regImr);
        break;
    }
}

static void writePage1(RTL8019* rtl, UInt8 address, UInt8 value)
{
    switch (address) {
    case 0x00:
        writeCr(rtl, value);
        break;
    case 0x01:
    case 0x02:
    case 0x03:
    case 0x04:
    case 0x05:
    case 0x06:
        rtl->regPar[address - 1] = value;
        break;
    case 0x07:
        rtl->regCurr = value;
        break;
    case 0x08:
    case 0x09:
    case 0x0a:
    case 0x0b:
    case 0x0c:
    case 0x0d:
    case 0x0e:
    case 0x0f:
        rtl->regMar[address - 8] = value;
        break;
    }
}

static void writePage2(RTL8019* rtl, UInt8 address, UInt8 value)
{
    switch (address) {
    case 0x00:
        writeCr(rtl, value);
        break;
    case 0x01:
        rtl->regClda = (rtl->regClda & 0xff00) | value;
        break;
    case 0x02:
        rtl->regClda = (rtl->regClda & 0x00ff) | ((UInt16)value << 8);
        break;
    case 0x03:
        rtl->regRppr = value;
        break;
    case 0x05:
        rtl->regLppr = value;
        break;
    case 0x06:
        rtl->regAcnt = (rtl->regAcnt & 0x00ff) | ((UInt16)value << 8);
        break;
    case 0x07:
        rtl->regAcnt = (rtl->regAcnt & 0xff00) | value;
        break;
    }
}

static void writePage3(RTL8019* rtl, UInt8 address, UInt8 value)
{
    switch (address) {
    case 0x00:
        writeCr(rtl, value);
        break;
    }
}

static UInt8 readRemoteDma(RTL8019* rtl, UInt8 address)
{
    UInt8 value = 0;

    if (rtl->regRbcr == 0) {
        // No data to read
        return value;
    }

    // If 8 bit mode, don't allow writes to second DMA port
    if ((address & 1) && !(rtl->regDcr & DCR_WTS)) {
        return value;
    }

    if (rtl->regCrda < 32) {
        value = rtl->macaddr[rtl->regCrda];
    }

    if (rtl->regCrda >= MEM_START && rtl->regCrda < MEM_END) {
        value = rtl->memory[rtl->regCrda - MEM_START];
    }

    rtl->regCrda++;
    if (rtl->regCrda == rtl->regPstop << 8) {
        rtl->regCrda = rtl->regPstart << 8;
    }

    rtl->regRbcr--;
    if (rtl->regRbcr == 0) {
        rtl->regIsr |= ISR_RDC;
        setIrq(rtl->regImr & IMR_RDC);
    }

    return value;
}

static UInt8 readResetDma(RTL8019* rtl, UInt8 address)
{
    rtl8019Reset(rtl);
    return 0;
}

static UInt8 readPage0(RTL8019* rtl, UInt8 address)
{
    switch (address) {
    case 0x00:
        return rtl->regCr;
    case 0x01:
        return (UInt8)(rtl->regClda & 0xff);
    case 0x02:
        return (UInt8)(rtl->regClda >> 8);
    case 0x03:
        return rtl->regBnry;
    case 0x04:
        return rtl->regTsr | 0x22;
    case 0x05:
        return rtl->regNcr;
    case 0x06:
        return rtl->regFifo;
    case 0x07:
        return rtl->regIsr;
    case 0x08:
        return (UInt8)(rtl->regCrda & 0xff);
    case 0x09:
        return (UInt8)(rtl->regCrda >> 8);
    case 0x0a:
        return 0x50;
    case 0x0b:
        return 0x70;
    case 0x0c:
        return rtl->regRsr;
    case 0x0d:
        return rtl->regCntr0;
    case 0x0e:
        return rtl->regCntr1;
    case 0x0f:
        return rtl->regCntr2;
    }

    return 0xff;
}

static UInt8 readPage1(RTL8019* rtl, UInt8 address)
{
    switch (address) {
    case 0x00:
        return rtl->regCr;
    case 0x01:
    case 0x02:
    case 0x03:
    case 0x04:
    case 0x05:
    case 0x06:
        return rtl->regPar[address - 1];
    case 0x07:
        return rtl->regCurr;
    case 0x08:
    case 0x09:
    case 0x0a:
    case 0x0b:
    case 0x0c:
    case 0x0d:
    case 0x0e:
    case 0x0f:
        return rtl->regMar[address - 8];
    }

    return 0xff;
}

static UInt8 readPage2(RTL8019* rtl, UInt8 address)
{
    switch (address) {
    case 0x00:
        return rtl->regCr;
    case 0x01:
        return rtl->regPstart;
    case 0x02:
        return rtl->regPstop;
    case 0x03:
        return rtl->regRppr;
    case 0x04:
        return rtl->regTpsr;
    case 0x05:
        return rtl->regLppr;
    case 0x06:
        return (UInt8)(rtl->regAcnt >> 8);
    case 0x07:
        return (UInt8)(rtl->regAcnt & 0xff);
    case 0x0c:
        return rtl->regRcr;
    case 0x0d:
        return rtl->regTcr;
    case 0x0e:
        return rtl->regDcr;
    case 0x0f:
        return rtl->regImr;
    }

    return 0xff;
}

static UInt8 readPage3(RTL8019* rtl, UInt8 address)
{
    switch (address) {
    case 0x00:
        return rtl->regCr;
    case 0x05:
    case 0x06:
        return 0x40;
    }

    return 0;
}

