/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/romMapperMsxRs232.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-04-11 18:31:50 $
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
#include "DeviceManager.h"
#include "SaveState.h"
#include "IoPort.h"
#include "I8251.h"
#include "I8254.h"
#include <stdlib.h>


typedef struct {
    int deviceHandle;
    I8251* i8251;
    I8254* i8254;
} MSXRs232;



/*****************************************
** Device Manager callbacks
******************************************
*/
static void saveState(MSXRs232* msxRs232)
{
    SaveState* state = saveStateOpenForWrite("MSXRs232");
    
    saveStateClose(state);

    i8251SaveState(msxRs232->i8251);
    i8254SaveState(msxRs232->i8254);
}

static void loadState(MSXRs232* msxRs232)
{
    SaveState* state = saveStateOpenForRead("MSXRs232");

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

    deviceManagerUnregister(msxRs232->deviceHandle);
    free(msxRs232);
}

static void reset(MSXRs232* msxRs232) 
{
    i8251Reset(msxRs232->i8251);
    i8254Reset(msxRs232->i8254);
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
        value = i8251Read(msxRs232->i8251, ioPort);
        break;
    case 0x82:
        // Status sense port for CTS, Timer/Counter 2, RI and CD
        break;
    case 0x84:
    case 0x85:
    case 0x86:
	value = i8254Read(msxRs232->i8254, ioPort);
        break;
    }

    return value;
}

static void writeIo(MSXRs232* msxRs232, UInt16 ioPort, UInt8 value) 
{
    switch (ioPort) {
    case 0x80:
    case 0x81:
        i8251Write(msxRs232->i8251, ioPort, value);
        break;
    case 0x82:
        // Interrupt mask register
        break;
    case 0x84:
    case 0x85:
    case 0x86:
    case 0x87:
        i8254Write(msxRs232->i8254, ioPort, value);
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

static void setRxReady(MSXRs232* msxRs232, int status) {
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
static void pitOut1(MSXRs232* msxRs232, int state) 
{
}
static void pitOut2(MSXRs232* msxRs232, int state) 
{
}
static void pitOut3(MSXRs232* msxRs232, int state) 
{
}

/*****************************************
** MSX RS-232 Create Method
******************************************
*/
int romMapperMsxRs232Create()
{
    DeviceCallbacks callbacks = {destroy, reset, saveState, loadState};
    MSXRs232* msxRs232;

    msxRs232 = malloc(sizeof(MSXRs232));
    
    msxRs232->deviceHandle = deviceManagerRegister(ROM_MSXRS232, &callbacks, msxRs232);

    msxRs232->i8251 = i8251Create(transmit, signal, setDataBits, setStopBits, setParity, 
                                 setRxReady, setDtr, setRts, getDtr, getRts, msxRs232);

    msxRs232->i8254 = i8254Create(1843200, pitOut1, pitOut2, pitOut3, msxRs232);

    ioPortRegister(0x80, readIo, writeIo, msxRs232);
    ioPortRegister(0x81, readIo, writeIo, msxRs232);
    ioPortRegister(0x82, readIo, writeIo, msxRs232);
    ioPortRegister(0x84, readIo, writeIo, msxRs232);
    ioPortRegister(0x85, readIo, writeIo, msxRs232);
    ioPortRegister(0x86, readIo, writeIo, msxRs232);
    ioPortRegister(0x87, NULL, writeIo, msxRs232);
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
    reset(msxRs232);

    return 1;
}
