/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperMsxRs232.c,v $
**
** $Revision: 1.4 $
**
** $Date: 2005-04-28 18:33:09 $
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
#include "romMapperMsxRs232.h"
#include "MediaDb.h"
#include "IoPort.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "Board.h"
#include "I8251.h"
#include "I8254.h"
#include <stdlib.h>
#include <memory.h>

/*
  80H  R/W  8251 data port
  81H  R/W  8251 command/status port
  82H   R   Status sense port for CTS, Timer/Counter 2, RI and CD
  82H   W   Interrupt mask register
  84H  R/W  8253 counter 0
  85H  R/W  8253 counter 1
  86H  R/W  8253 counter 2
  87H   W   8253 mode register
*/

#define STATUS_CD   0x01
#define STATUS_RI   0x02
#define STATUS_OUT2 0x40
#define STATUS_CTS  0x80

#define INTMASK_RXREADY 0x01
#define INTMASK_TXREADY 0x02
#define INTMASK_SBRK    0x04
#define INTMASK_OUT2    0x08

#define CMD_RSTERR 0x10
#define CMD_RTS    0x20
#define CMD_RESET  0x40
#define CMD_HUNT   0x80

typedef struct {
    int deviceHandle;
    int slot;
    int sslot;
    int startPage;
    int serialLink;
    UInt8* romData;
    I8251* i8251;
    I8254* i8254;
    UInt8 status;   // Status for CTS, PIT Timer/Counter 2, RI and CD
    UInt8 intmask;  // Interrupt mask
} MSXRs232;

static MSXRs232* msxRs232;

/*****************************************
** Device Manager callbacks
******************************************
*/
static void saveState(MSXRs232* msxRs232)
{
    SaveState* state = saveStateOpenForWrite("MSXRs232");

    saveStateSet(state, "status",  msxRs232->status);
    saveStateSet(state, "intmask",  msxRs232->intmask);

    saveStateClose(state);

    i8251SaveState(msxRs232->i8251);
    i8254SaveState(msxRs232->i8254);
}

static void loadState(MSXRs232* msxRs232)
{
    SaveState* state = saveStateOpenForRead("MSXRs232");

    msxRs232->status  = (UInt8)saveStateGet(state, "status",  0);
    msxRs232->intmask  = (UInt8)saveStateGet(state, "intmask",  0);

    saveStateClose(state);
    
    i8251LoadState(msxRs232->i8251);
    i8254LoadState(msxRs232->i8254);
}

static void destroy(MSXRs232* msxRs232)
{
    ioPortUnregister(0x80);
    ioPortUnregister(0x81);
    ioPortUnregister(0x82);
    ioPortUnregister(0x84);
    ioPortUnregister(0x85);
    ioPortUnregister(0x86);
    ioPortUnregister(0x87);
       
    i8251Destroy(msxRs232->i8251);
    i8254Destroy(msxRs232->i8254);

    slotUnregister(msxRs232->slot, msxRs232->sslot, msxRs232->startPage);
    deviceManagerUnregister(msxRs232->deviceHandle);

    free(msxRs232->romData);
    free(msxRs232);
}

static void reset(MSXRs232* msxRs232) 
{
    i8251Reset(msxRs232->i8251);
    i8254Reset(msxRs232->i8254);
    msxRs232->status = 0;
    msxRs232->intmask = 0;
}

/*****************************************
** Slot callbacks
******************************************
*/
static UInt8 read(MSXRs232* msxRs232, UInt16 address) 
{
    return address < 0x4000 ? msxRs232->romData[address] : 0xff;
}

static UInt8 peek(MSXRs232* msxRs232, UInt16 address) 
{
    return address < 0x4000 ? msxRs232->romData[address] : 0xff;
}

static void write(MSXRs232* msxRs232, UInt16 address, UInt8 value)
{
}

/*****************************************
** IO Port callbacks
******************************************
*/
static UInt8 readIo(MSXRs232* msxRs232, UInt16 ioPort) 
{
    UInt8 value = 0xff;

    switch (ioPort) {
    case 0x80:
    case 0x81:
        ioPort &= 0x01;
        value = i8251Read(msxRs232->i8251, ioPort);
        break;
    case 0x82:
        value = msxRs232->status;
        break;
    case 0x84:
    case 0x85:
    case 0x86:
        ioPort &= 0x03;
	    value = i8254Read(msxRs232->i8254, ioPort);
        break;
    }

    return value;
}

static void writeIo(MSXRs232* msxRs232, UInt16 ioPort, UInt8 value) 
{
    UInt16 baseAdr;

    switch (ioPort) {
    case 0x80:
    case 0x81:
        baseAdr = ioPort - 0x80;
        i8251Write(msxRs232->i8251, baseAdr, value);
        break;
    case 0x82:
        msxRs232->intmask = value & 0x0f;
        break;
    case 0x84:
    case 0x85:
    case 0x86:
    case 0x87:
        baseAdr = ioPort - 0x84;
        i8254Write(msxRs232->i8254, baseAdr, value);
        break;
    }
}

/*****************************************
** I8251 callbacks
******************************************
*/
static int transmit(MSXRs232* msxRs232, UInt8 value) {
    return 0;
}

static int signal(MSXRs232* msxRs232) {
    return 0;
}

static void setDataBits(MSXRs232* msxRs232, int value) {
}

static void setStopBits(MSXRs232* msxRs232, int value) {
}

static void setParity(MSXRs232* msxRs232, int value) {
}

static void setRxReady(MSXRs232* msxRs232, int status)
{
    if (~msxRs232->intmask & INTMASK_RXREADY) {
        if (status)
            boardSetInt(1);
        else
            boardClearInt(1);
    }
}

static void setDtr(MSXRs232* msxRs232, int status) {
}

static void setRts(MSXRs232* msxRs232, int status) {
}

static int getDtr(MSXRs232* msxRs232) {
    return 0;
}

static int getRts(MSXRs232* msxRs232) {
    return 0;
}

/*****************************************
** I8254 callbacks
******************************************
*/
static void pitOut0(MSXRs232* msxRs232, int state) 
{
    //msxRs232->i8251->rxClk(msxRs232, state);
}
static void pitOut1(MSXRs232* msxRs232, int state) 
{
    //msxRs232->i8251->txClk(msxRs232, state);
}

static void pitOut2 (MSXRs232* msxRs232, int state) 
{
    msxRs232->status = (state) ? msxRs232->status|STATUS_OUT2 : msxRs232->status&~STATUS_OUT2;
}

/*****************************************
** ARCH UART callbacks
******************************************
*/
static void romMapperMsxRs232ReceiveCallback(UInt8 value)
{
    i8251RxData(msxRs232->i8251, value);
}

/*****************************************
** MSX RS-232 Create Method
******************************************
*/
int romMapperMsxRs232Create(char* filename, UInt8* romData, int size, int slot, int sslot, int startPage)
{
    DeviceCallbacks callbacks = {destroy, reset, saveState, loadState};
    int pages = 4;
    int i;

    if ((startPage + pages) > 8) {
        return 0;
    }

    msxRs232 = malloc(sizeof(MSXRs232));
    
    msxRs232->deviceHandle = deviceManagerRegister(ROM_MSXRS232, &callbacks, msxRs232);

    slotRegister(slot, sslot, startPage, pages, read, peek, write, destroy, msxRs232);

    msxRs232->romData = malloc(size);
    memcpy(msxRs232->romData, romData, size);
    
    msxRs232->slot  = slot;
    msxRs232->sslot = sslot;
    msxRs232->startPage  = startPage;

    for (i = 0; i < pages; i++) {
        slotMapPage(slot, sslot, i + startPage, NULL, 0, 0);
    }

    msxRs232->i8251 = i8251Create(transmit, signal, setDataBits, setStopBits, setParity, 
                                 setRxReady, setDtr, setRts, getDtr, getRts, msxRs232);

    msxRs232->i8254 = i8254Create(1843200, pitOut0, pitOut1, pitOut2, msxRs232);

    msxRs232->serialLink = archUartCreate(romMapperMsxRs232ReceiveCallback);

    ioPortRegister(0x80, readIo, writeIo, msxRs232);
    ioPortRegister(0x81, readIo, writeIo, msxRs232);
    ioPortRegister(0x82, readIo, writeIo, msxRs232);
    ioPortRegister(0x84, readIo, writeIo, msxRs232);
    ioPortRegister(0x85, readIo, writeIo, msxRs232);
    ioPortRegister(0x86, readIo, writeIo, msxRs232);
    ioPortRegister(0x87, NULL, writeIo, msxRs232);

    reset(msxRs232);

    return 1;
}
