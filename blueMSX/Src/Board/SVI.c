/*****************************************************************************
** File:        SVI.c
**
** Author:      Daniel Vik, Tomas Karlsson
**
** More info:   www.bluemsx.com
**
** Description: Spectravideo SVI-328 and SVI-318 emulation
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include "SVI.h"
#include "R800.h"
#include "R800Dasm.h"
#include "R800SaveState.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include "Led.h"
#include "Switches.h"
#include "JoystickIO.h"
#include "AY8910.h"
#include "KeyClick.h"
#include "Casette.h"
#include "Disk.h"
#include "IoPort.h"
#include "RomLoader.h"
#include "svi328Fdc.h"

/* Hardware */
static Machine*        sviMachine;
static DeviceInfo*     sviDevInfo;
static AY8910*         ay8910;
static AudioKeyClick*  keyClick;
static R800*           r800;
static JoystickIO*     joyIO;
static UInt32          nextSyncTime;
static UInt32          loopTime;
static int             syncCount;
static int             SyncPeriod;
static UInt8           KeyMap[16];
static UInt32          SviFrequency;
static int             pendingInt;
static UInt32          sviRamSize;
static UInt32          sviVramSize;
static int             useRom;
static int             traceEnabled;

typedef enum { BANK_02=0, BANK_12=1, BANK_22=2, BANK_32=3 } sviBanksHigh;
typedef enum { BANK_01=0, BANK_11=1, BANK_21=2, BANK_31=3 } sviBanksLow;

static UInt8 sviMemoryLow[4][0x8000];
static UInt8 sviMemoryHigh[4][0x8000];
static UInt8 sviBankLow;
static UInt8 sviBankHigh;
static UInt8 sviLowReadOnly;
static UInt8 psgAYReg15;

void sviLoadState();
void sviSaveState();

extern int  WaitForSync(void);
extern void Keyboard(UInt8* keybardMap);
extern void PatchZ80(void* ref, CpuRegs* cpu);

static void sviMemReset()
{
    memset(sviMemoryHigh, 0xff, 0x20000);
    memset(sviMemoryLow, 0xff, 0x20000); 
}

static void sviMemSetBank(UInt8 AYReg15)
{
    sviBankLow = (AYReg15&1)?(AYReg15&2)?(AYReg15&8)?BANK_01:BANK_31:BANK_21:BANK_11;
    sviBankHigh = (AYReg15&4)?(AYReg15&16)?BANK_02:BANK_32:BANK_22;
    sviLowReadOnly = ((sviBankLow==BANK_01)||(sviBankLow==BANK_11))?1:0;

    psgAYReg15 = AYReg15;
}

void sviMemWrite(void* ref, UInt16 address, UInt8 value)
{
    if (address & 0x8000)
        sviMemoryHigh[sviBankHigh][address & 0x7FFF] = value;
    else
        if(!sviLowReadOnly)
            sviMemoryLow[sviBankLow][address] = value;
}

UInt8 sviMemRead(void* ref, UInt16 address)
{
    if (address & 0x8000)
        return sviMemoryHigh[sviBankHigh][address & 0x7FFF];
    else
        return sviMemoryLow[sviBankLow][address];
}

static void sviSaveMemory()
{
    SaveState* state = saveStateOpenForWrite("sviMemory");

    saveStateSetBuffer(state, "sviMemoryLow", sviMemoryLow, sizeof(sviMemoryLow));
    saveStateSetBuffer(state, "sviMemoryHigh", sviMemoryHigh, sizeof(sviMemoryHigh));

    saveStateSet(state, "sviBankLow",     sviBankLow);
    saveStateSet(state, "sviBankHigh",    sviBankHigh);
    saveStateSet(state, "sviLowReadOnly", sviLowReadOnly);
    saveStateSet(state, "psgAYReg15",     psgAYReg15);

    saveStateClose(state);
}

static void sviLoadMemory()
{
    SaveState* state = saveStateOpenForRead("sviMemory");


    saveStateGetBuffer(state, "sviMemoryLow", sviMemoryLow, sizeof(sviMemoryLow));
    saveStateGetBuffer(state, "sviMemoryHigh", sviMemoryHigh, sizeof(sviMemoryHigh));

    sviBankLow     = (UInt8)saveStateGet(state, "sviBankLow",     0);
    sviBankHigh    = (UInt8)saveStateGet(state, "sviBankHigh",    0);
    sviLowReadOnly = (UInt8)saveStateGet(state, "sviLowReadOnly", 0);
    psgAYReg15     = (UInt8)saveStateGet(state, "psgAYReg15",     0);

    saveStateClose(state);
}

//static UInt16 patchAddress[] = {0x0069,0x006C,0x006F,0x0072,0x0075,0x0078,0x210A,0x21A9,0};
static UInt16 patchAddress[] = {0x006C,0x006F,0x0072,0x0075,0x0078,0x210A,0x21A9,0};

static void sviPatchROM(void)
{
    int i;

    /* Patch SVI-328 BIOS and BASIC for cassette handling */
    for (i = 0; patchAddress[i]; i++) {
        sviMemoryLow[BANK_01][patchAddress[i]] = 0xED;
        sviMemoryLow[BANK_01][patchAddress[i]+1] = 0xFE;
        sviMemoryLow[BANK_01][patchAddress[i]+2] = 0xC9;
    }

    sviMemoryLow[BANK_01][0x2073]=0x01;   // Skip delay loop after save
    sviMemoryLow[BANK_01][0x20D0]=0x10;   // Write $55 only $10 times, instead
    sviMemoryLow[BANK_01][0x20D1]=0x00;   //   of $190
    sviMemoryLow[BANK_01][0x20E3]=0x00;   // Cancel instruction
    sviMemoryLow[BANK_01][0x20E4]=0x00;
    sviMemoryLow[BANK_01][0x20E5]=0x00;
    sviMemoryLow[BANK_01][0x20E6]=0xED;
    sviMemoryLow[BANK_01][0x20E7]=0xFE;
}

/*
PSG Port A Input
Bit Name   Description
 1  FWD1   Joystick 1, Forward
 2  BACK1  Joystick 1, Back
 3  LEFT1  Joystick 1, Left
 4  RIGHT1 Joystick 1, Right
 5  FWD2   Joystick 2, Forward
 6  BACK2  Joystick 2, Back
 7  LEFT2  Joystick 2, Left
 8  RIGHT2 Joystick 2, Right

PSG Port B Output
Bit Name    Description
1   /CART   Memory bank 11, ROM 0000-7FFF (Cartridge /CCS1, /CCS2)
2   /BK21   Memory bank 21, RAM 0000-7FFF
3   /BK22   Memory bank 22, RAM 8000-FFFF
4   /BK31   Memory bank 31, RAM 0000-7FFF
5   /BK32   Memory bank 32, RAM 8000-7FFF
6   CAPS    Caps-Lock diod
7   /ROMEN0 Memory bank 12, ROM 8000-BFFF* (Cartridge /CCS3)
8   /ROMEN1 Memory bank 12, ROM C000-FFFF* (Cartridge /CCS4)

* The /CART signal must be active for any effect,
  then all banks of RAM are disabled. */

UInt8 sviPsgReadHandler(void* arg, UInt16 address) 
{
    UInt8 value = 0xff;

    switch (address) {
        case 0:
            value = joystickReadSVI(joyIO);
            break;
        case 1:
            value = psgAYReg15;
            break;
    }
    return value;
}

static void sviPsgWriteHandler(void* arg, UInt16 address, UInt8 value) 
{
    switch (address) {
    case 0:
        break;
    case 1:
        ledSetCapslock(value & 0x20 ? 1 : 0);
        if ((psgAYReg15 & 0xDF) != (value & 0xDF))
            sviMemSetBank(value);
        break;
    }
}

/*
PPI Port A Input (Address 98H)
Bit Name     Description
 1  TA       Joystick 1, /SENSE
 2  TB       Joystick 1, EOC
 3  TC       Joystick 2, /SENSE
 4  TD       Joystick 2, EOC
 5  TRIGGER1 Joystick 1, Trigger
 6  TRIGGER2 Joystick 2, Trigger
 7  /READY   Cassette, Ready
 8  CASR     Cassette, Read data

PPI Port B Input (Address 99H)
Bit Name Description
 1  IN0  Keyboard, Column status of selected line
 2  IN1  Keyboard, Column status of selected line
 3  IN2  Keyboard, Column status of selected line
 4  IN3  Keyboard, Column status of selected line
 5  IN4  Keyboard, Column status of selected line
 6  IN5  Keyboard, Column status of selected line
 7  IN6  Keyboard, Column status of selected line
 8  IN7  Keyboard, Column status of selected line

PPI Port C Output (Address 97H)
Bit Name   Description
 1  KB0    Keyboard, Line select 0
 2  KB1    Keyboard, Line select 1
 3  KB2    Keyboard, Line select 2
 4  KB3    Keyboard, Line select 3
 5  CASON  Cassette, Motor relay control (0=on, 1=off)
 6  CASW   Cassette, Write data
 7  CASAUD Cassette, Audio out (pulse)
 8  SOUND  Keyboard, Click sound bit (pulse)
*/
typedef struct {
    UInt8          reg[4];
    UInt8          outReg[3]; 
    UInt8          inReg[3];
    UInt8          oldOutReg[3];
    UInt8          mode;
    UInt8*         keymap;
    AudioKeyClick* keyClick;
} I8255;

static I8255 i8255;

static UInt8 i8255read(void* ref, UInt16 ioPort)
{
    if (ioPort == 0x9A)
        return i8255.mode;

    ioPort &= 3;

    /* Read joystick triggers and cassette status*/
    i8255.inReg[0] = joystickReadTriggerSVI(joyIO);
    i8255.inReg[0] |= (sviDevInfo->cassette.inserted) ? 0:0x40; 

    /* Read keyboard input */
    i8255.inReg[1] = i8255.keymap[i8255.outReg[2] & 0x0f];

    switch(ioPort) {
    case 0: 
        return i8255.reg[3] & 0x10 ? i8255.inReg[0] : i8255.reg[0];
    case 1: 
        return i8255.reg[3] & 0x02? i8255.inReg[1] : i8255.reg[1];
    case 2: 
        return ((i8255.reg[3] & 0x01 ? i8255.inReg[2] : i8255.reg[2]) & 0x0f)|
               ((i8255.reg[3] & 0x08 ? i8255.inReg[2] : i8255.reg[2]) & 0xf0);
    case 3: 
        return i8255.reg[3];
    }
    return 0xff;
}

static void i8255write(void* ref, UInt16 ioPort, UInt8 value)
{
    if (ioPort == 0x97)
        i8255.mode = value;

    ioPort &= 3;

    /*  Update registers and ports */
    switch(ioPort) {
    case 0:
    case 1:
    case 2:
        /* Data registers */
        i8255.reg[ioPort] = value;
        break;
    case 3:
        /* Control register */
        if (value & 0x80) {
            i8255.reg[ioPort] = value;
        }
        else {
            ioPort = 1 << ((value & 0x0e) >> 1);
            if (value&0x01) {
                i8255.reg[2] |= ioPort; 
            }
            else {
                i8255.reg[2] &= ~ioPort;
            }
        }
        break;
    }

    /* Set output ports */
    value = i8255.reg[3];
    i8255.outReg[0] = value & 0x10 ? 0x00 : i8255.reg[0];
    i8255.outReg[1] = value & 0x02 ? 0x00 : i8255.reg[1];
    i8255.outReg[2] = ((value & 0x01 ? 0x00 : i8255.reg[2]) & 0x0f) | 
                    ((value & 0x08 ? 0x00 : i8255.reg[2]) & 0xf0);

    // Do post processing
    if (i8255.outReg[2] != i8255.oldOutReg[2]) { 
            audioKeyClick(i8255.keyClick, (i8255.outReg[2] >> 7));

        i8255.oldOutReg[2] = i8255.outReg[2]; 
    }

    if (i8255.outReg[0] != i8255.oldOutReg[0]) {
        i8255.oldOutReg[0] = i8255.outReg[0];
        value  = i8255.outReg[0];
    }
}

static void i8255SaveState()
{
    SaveState* state = saveStateOpenForWrite("i8255");
    
    saveStateSet(state, "reg00",       i8255.reg[0]);
    saveStateSet(state, "reg01",       i8255.reg[1]);
    saveStateSet(state, "reg02",       i8255.reg[2]);
    saveStateSet(state, "reg03",       i8255.reg[3]);
    saveStateSet(state, "inReg00",     i8255.inReg[0]);
    saveStateSet(state, "inReg01",     i8255.inReg[1]);
    saveStateSet(state, "inReg02",     i8255.inReg[2]);
    saveStateSet(state, "outReg00",    i8255.outReg[0]);
    saveStateSet(state, "outReg01",    i8255.outReg[1]);
    saveStateSet(state, "outReg02",    i8255.outReg[2]);
    saveStateSet(state, "oldOutReg00", i8255.oldOutReg[0]);
    saveStateSet(state, "oldOutReg01", i8255.oldOutReg[1]);
    saveStateSet(state, "oldOutReg02", i8255.oldOutReg[2]);
    saveStateSet(state, "mode",        i8255.mode);

    saveStateClose(state);
}

static void i8255LoadState()
{
    SaveState* state = saveStateOpenForRead("i8255");

    i8255.reg[0]       = (UInt8)saveStateGet(state, "reg00",       0);
    i8255.reg[1]       = (UInt8)saveStateGet(state, "reg01",       0);
    i8255.reg[2]       = (UInt8)saveStateGet(state, "reg02",       0);
    i8255.reg[3]       = (UInt8)saveStateGet(state, "reg03",       0);
    i8255.inReg[0]     = (UInt8)saveStateGet(state, "inReg00",     0);
    i8255.inReg[1]     = (UInt8)saveStateGet(state, "inReg01",     0);
    i8255.inReg[2]     = (UInt8)saveStateGet(state, "inReg02",     0);
    i8255.outReg[0]    = (UInt8)saveStateGet(state, "outReg00",    0);
    i8255.outReg[1]    = (UInt8)saveStateGet(state, "outReg01",    0);
    i8255.outReg[2]    = (UInt8)saveStateGet(state, "outReg02",    0);
    i8255.oldOutReg[0] = (UInt8)saveStateGet(state, "oldOutReg00", 0);
    i8255.oldOutReg[1] = (UInt8)saveStateGet(state, "oldOutReg01", 0);
    i8255.oldOutReg[2] = (UInt8)saveStateGet(state, "oldOutReg02", 0);
    i8255.mode         = (UInt8)saveStateGet(state, "mode",        0);

    saveStateClose(state);
}

void ppiCreate(UInt8* keymap, AudioKeyClick* keyClick)
{
    memset(&i8255, 0, sizeof(i8255));

    i8255.keymap   = keymap;
    i8255.keyClick = keyClick;
    i8255.reg[3]   = 0x9b;

    ioPortRegister(0x98, i8255read, i8255write, NULL); // PPI Port A
    ioPortRegister(0x99, i8255read, i8255write, NULL); // PPI Port B
    ioPortRegister(0x96, i8255read, i8255write, NULL); // PPI Port C
    ioPortRegister(0x97, i8255read, i8255write, NULL); // PPI Mode
    ioPortRegister(0x9A, i8255read, NULL,       NULL); // PPI Return Mode
}

void ppiDestroy(void) 
{
    ioPortUnregister(0x98);
    ioPortUnregister(0x99);
    ioPortUnregister(0x96);
    ioPortUnregister(0x97);
    ioPortUnregister(0x9A);
}


void sviTraceEnable(const char* fileName) {
    traceEnabled = r800OpenTrace(fileName);
}

void sviTraceDisable() {
    r800CloseTrace();
    traceEnabled = 0;
}

int sviTraceGetEnable() {
    return traceEnabled;
}

UInt32 sviGetRamSize()
{ 
    return sviRamSize / 1024;
}

UInt32 sviGetVramSize()
{
    return sviVramSize / 1024;
}

int sviUseRom()
{
    return useRom;
}

int sviUseMegaRom()
{
    return 0;
}

int sviUseMegaRam()
{
    return 0;
}

int sviUseFmPac()
{
    return 0;
}

UInt32 sviSystemTime() 
{
    if (r800) {
        return r800GetSystemTime(r800);
    }
    return 0;
}

UInt8* sviGetRamPage(int page)
{
    static UInt8 emptyRam[0x2000];

    return emptyRam;
}

void sviSetInt(UInt32 irq)
{
    pendingInt |= irq;
    r800SetInt(r800);
}

UInt32 sviGetInt()
{
    return pendingInt;
}

void sviClearInt(UInt32 irq)
{
    pendingInt &= ~irq;
    if (pendingInt == 0)
        r800ClearInt(r800);
}

void sviInitStatistics(Machine* machine)
{
    sviVramSize = machine->video.vramSize;
    sviRamSize = 0x28000;
}

static int sviInitMachine(Machine* machine, 
                          Mixer* mixer,
                          VdpSyncMode vdpSyncMode)
{
    UInt8* buf;
    int success = 1;
    int size;

    /* Initialize VDP */
    sviVramSize = machine->video.vramSize;
    vdpInit(VDP_SVI, machine->video.vdpVersion, vdpSyncMode, machine->video.vramSize / 0x4000);

    /* Initialize memory */
    sviMemReset();
    sviMemSetBank(0xDF);

    buf = romLoad(machine->slotInfo[0].name, machine->slotInfo[0].inZipName, &size);
    if (buf != NULL) {
        if (size < 0x8001)
            memcpy(&sviMemoryLow[BANK_01][0], buf, size);
        else
            success = 0;
        free(buf);
    }
    else
        success = 0;

    ledSetCapslock(0);

    /* Patch BASIC ROM for cassette usage */
    sviPatchROM();

    /* Initialize FDC */
    svi328FdcCreate();

    return success;
}

void sviReset()
{
    UInt32 systemTime = boardSystemTime();
    if (r800 != NULL) {
        r800Reset(r800, systemTime);
    }
    if (ay8910 != NULL) {
        ay8910Reset(ay8910);
    }

    vdpReset();
    
    sviMemSetBank(0xDF);

    ledSetCapslock(0);

    deviceManagerReset();
}

int sviRun(Machine* machine, 
           DeviceInfo* devInfo,
           Mixer* mixer,
           int loadState,
           int frequency)
{
    int success;
    int i;

    sviMachine   = machine;
    sviDevInfo   = devInfo;

    SyncPeriod   = 0;
    SviFrequency = frequency;

    nextSyncTime  = 0;
    loopTime      = 0;
    syncCount     = 0;
    pendingInt    = 0;

    // If we're running from a state file, use its machine
    // and user configuration
    if (loadState) {
        sviLoadState();
        machineLoadState(sviMachine);
    }

    deviceManagerCreate();
    ioPortReset();

    r800 = r800Create(sviMemRead, sviMemWrite, ioPortRead, ioPortWrite, PatchZ80, NULL);
    r800Reset(r800, 0);
    mixerReset(mixer);

    ay8910 = ay8910Create(mixer, AY8910_SVI);
    ay8910SetIoPort(ay8910, sviPsgReadHandler, sviPsgWriteHandler, NULL);

    keyClick  = audioKeyClickCreate(mixer);
    ppiCreate(KeyMap, keyClick);

    success = sviInitMachine(machine, mixer, devInfo->video.vdpSyncMode);

    joyIO = joystickIoCreateSVI();

    if (devInfo->cartridge[0].inserted) {
        sviChangeCartridge(0, devInfo->cartridge[0].type, 
                              devInfo->cartridge[0].name,
                              devInfo->cartridge[0].inZipName);
    }

    for (i = 0; i < 2; i++) {
        if (devInfo->diskette[i].inserted) {
            sviChangeDiskette(i, devInfo->diskette[i].name,
                                 devInfo->diskette[i].inZipName);
        }
    }

    if (devInfo->cassette.inserted) {
        sviChangeCassette(devInfo->cassette.name,
                          devInfo->cassette.inZipName);
    }

    memset(KeyMap, 0xff, 16);

    r800SetFrequency(r800, CPU_Z80,  machine->cpu.freqZ80);
    r800SetFrequency(r800, CPU_R800, machine->cpu.freqR800);

    diskEnable(0, machine->fdc.count > 0);
    diskEnable(1, machine->fdc.count > 1);

    if (loadState) {
        sviLoadMemory();
        deviceManagerLoadState();
        joystickIoLoadState(joyIO);
        machineLoadState(sviMachine);
        i8255LoadState();
        ay8910LoadState(ay8910);
        r800LoadState(r800);
        vdpLoadState();
        tapeLoadState();
    }

    if (success) {
        /* Start execution of the code */
        for (;;) {
            if (syncCount >= SyncPeriod) {
                int execTime = WaitForSync();
                int renshaSpeed;

                if (execTime == -1) {
                    break;
                }
                syncCount -= SyncPeriod;
                SyncPeriod = execTime * SviFrequency * 6; // FIXME
                mixerSync(mixer);

                Keyboard(KeyMap);

                renshaSpeed = switchGetRensha();
                if (renshaSpeed) {
                    UInt8 renshaOn = (UInt8)((UInt64)renshaSpeed * nextSyncTime / boardFrequency());
                    ledSetRensha(renshaSpeed > 14 ? 1 : renshaOn & 2);
                    KeyMap[8] |= (renshaOn & 1);
                }
                else {
                    ledSetRensha(0);
                }
            }

            syncCount += 1000 * loopTime;
            nextSyncTime += loopTime;

            if (traceEnabled) {
                r800ExecuteTrace(r800, nextSyncTime);
            }
            else {
                r800Execute(r800, nextSyncTime);
            }

            loopTime = vdpRefreshLine(nextSyncTime);
        }
    }

    sviTraceDisable();

    joystickIoDestroySVI(joyIO);

    ay8910SetIoPort(ay8910, NULL, NULL, NULL);
    ay8910Destroy(ay8910);
    audioKeyClickDestroy(keyClick);

    sviChangeDiskette(0, NULL, NULL);
    sviChangeDiskette(1, NULL, NULL);

    sviChangeCassette(0, 0);

    vdpDestroy();

    deviceManagerDestroy();

    sviMachine = NULL;
    sviDevInfo = NULL;

    useRom     = 0;

    return success;
}

void sviSetFrequency(UInt32 frequency)
{
    SviFrequency = frequency;
}

int sviGetRefreshRate()
{
    return vdpGetRefreshRate();
}

void sviChangeCartridge(int cartNo, RomType romType, char* cart, char* cartZip)
{
    UInt8* buf;
    int size;

    if (cart && strlen(cart) == 0)
        cart = NULL;

    if (cartZip && strlen(cartZip) == 0)
        cartZip = NULL;

    if (sviDevInfo != NULL) {
        sviDevInfo->cartridge[cartNo].inserted = cart != NULL;
        sviDevInfo->cartridge[cartNo].type = romType;
        strcpy(sviDevInfo->cartridge[cartNo].name, cart ? cart : "");
        strcpy(sviDevInfo->cartridge[cartNo].inZipName, cartZip ? cartZip : "");
    }

    if (cartNo == 0) {
        memset(&sviMemoryLow[BANK_11][0], 0xff, 0x8000);
        buf = romLoad(cart, cartZip, &size);
        if (buf != NULL && size < 0x8001) {
            memcpy(&sviMemoryLow[BANK_11][0], buf, size);
            useRom = 1;
        }
        else
            useRom = 0;
            free(buf);
    }
}

void sviChangeDiskette(int driveId, char* fileName, const char* fileInZipFile)
{
    if (fileName && strlen(fileName) == 0)
        fileName = NULL;

    if (fileInZipFile && strlen(fileInZipFile) == 0)
        fileInZipFile = NULL;

    if (sviDevInfo != NULL) {
        sviDevInfo->diskette[driveId].inserted = fileName != NULL;
        strcpy(sviDevInfo->diskette[driveId].name, fileName ? fileName : "");
        strcpy(sviDevInfo->diskette[driveId].inZipName, fileInZipFile ? fileInZipFile : "");
    }

    diskChange(driveId, fileName, fileInZipFile);
}

void sviChangeCassette(char *name, const char *fileInZipFile)
{
    if (name && strlen(name) == 0)
        name = NULL;

    if (fileInZipFile && strlen(fileInZipFile) == 0)
        fileInZipFile = NULL;

    if (sviDevInfo != NULL) {
        sviDevInfo->cassette.inserted = name != NULL;

        strcpy(sviDevInfo->cassette.name, name ? name : "");
        strcpy(sviDevInfo->cassette.inZipName, fileInZipFile ? fileInZipFile : "");
    }

    tapeInsert(name, fileInZipFile);
}

void sviSaveState()
{    
    SaveState* state = saveStateOpenForWrite("svi");
    DeviceInfo* di = sviDevInfo;

    saveStateSet(state, "nextSyncTime",    nextSyncTime);
    saveStateSet(state, "loopTime",        loopTime);
    saveStateSet(state, "syncCount",       syncCount);
    saveStateSet(state, "SyncPeriod",      SyncPeriod);
    saveStateSet(state, "pendingInt",      pendingInt);
    saveStateSet(state, "SviFrequency",    SviFrequency);
    
    saveStateSet(state, "cartInserted00", di->cartridge[0].inserted);
    saveStateSet(state, "cartType00",     di->cartridge[0].type);
    saveStateSetBuffer(state, "cartName00",  di->cartridge[0].name, strlen(di->cartridge[0].name) + 1);
    saveStateSetBuffer(state, "cartInZip00", di->cartridge[0].inZipName, strlen(di->cartridge[0].inZipName) + 1);
    saveStateSet(state, "cartInserted01", di->cartridge[1].inserted);
    saveStateSet(state, "cartType01",     di->cartridge[1].type);
    saveStateSetBuffer(state, "cartName01",  di->cartridge[1].name, strlen(di->cartridge[1].name) + 1);
    saveStateSetBuffer(state, "cartInZip01", di->cartridge[1].inZipName, strlen(di->cartridge[1].inZipName) + 1);

    saveStateSet(state, "diskInserted00", di->diskette[0].inserted);
    saveStateSetBuffer(state, "diskName00",  di->diskette[0].name, strlen(di->diskette[0].name) + 1);
    saveStateSetBuffer(state, "diskInZip00", di->diskette[0].inZipName, strlen(di->diskette[0].inZipName) + 1);
    saveStateSet(state, "diskInserted01", di->diskette[1].inserted);
    saveStateSetBuffer(state, "diskName01",  di->diskette[1].name, strlen(di->diskette[1].name) + 1);
    saveStateSetBuffer(state, "diskInZip01", di->diskette[1].inZipName, strlen(di->diskette[1].inZipName) + 1);

    saveStateSet(state, "casInserted", di->cassette.inserted);
    saveStateSetBuffer(state, "casName",  di->cassette.name, strlen(di->cassette.name) + 1);
    saveStateSetBuffer(state, "casInZip", di->cassette.inZipName, strlen(di->cassette.inZipName) + 1);
    saveStateSetBuffer(state, "keyMap",   KeyMap, sizeof(KeyMap));

    saveStateSet(state, "enableYM2413",    di->audio.enableYM2413);
    saveStateSet(state, "enableY8950",     di->audio.enableY8950);
    saveStateSet(state, "enableMoonsound", di->audio.enableMoonsound);
    saveStateSet(state, "moonsoundSRAM",   di->audio.moonsoundSRAM);

    saveStateSet(state, "vdpSyncMode",   di->video.vdpSyncMode);

    saveStateClose(state);

    sviSaveMemory();
    joystickIoSaveState(joyIO);
    machineSaveState(sviMachine);
    r800SaveState(r800);
    deviceManagerSaveState();
    ay8910SaveState(ay8910);
    vdpSaveState();
    tapeSaveState();
    i8255SaveState();
}

void sviLoadState()
{
    SaveState* state = saveStateOpenForRead("svi");
    DeviceInfo* di = sviDevInfo;

    nextSyncTime        = saveStateGet(state, "nextSyncTime",    0);
    loopTime            = saveStateGet(state, "loopTime",        0);
    syncCount           = saveStateGet(state, "syncCount",       0);
    SyncPeriod          = saveStateGet(state, "SyncPeriod",      0);
    pendingInt          = saveStateGet(state, "pendingInt",      0);
    SviFrequency        = saveStateGet(state, "SviFrequency",    0);

    di->cartridge[0].inserted = saveStateGet(state, "cartInserted00", 0);
    di->cartridge[0].type = saveStateGet(state, "cartType00",     0);
    saveStateGetBuffer(state, "cartName00",  di->cartridge[0].name, sizeof(di->cartridge[0].name));
    saveStateGetBuffer(state, "cartInZip00", di->cartridge[0].inZipName, sizeof(di->cartridge[0].inZipName));
    di->cartridge[1].inserted = saveStateGet(state, "cartInserted01", 0);
    di->cartridge[1].type = saveStateGet(state, "cartType01",     0);
    saveStateGetBuffer(state, "cartName01",  di->cartridge[1].name, sizeof(di->cartridge[1].name));
    saveStateGetBuffer(state, "cartInZip01", di->cartridge[1].inZipName, sizeof(di->cartridge[1].inZipName));

    di->diskette[0].inserted = saveStateGet(state, "diskInserted00", 0);
    saveStateGetBuffer(state, "diskName00",  di->diskette[0].name, sizeof(di->diskette[0].name));
    saveStateGetBuffer(state, "diskInZip00", di->diskette[0].inZipName, sizeof(di->diskette[0].inZipName));
    di->diskette[1].inserted = saveStateGet(state, "diskInserted01", 0);
    saveStateGetBuffer(state, "diskName01",  di->diskette[1].name, sizeof(di->diskette[1].name));
    saveStateGetBuffer(state, "diskInZip01", di->diskette[1].inZipName, sizeof(di->diskette[1].inZipName));

    di->cassette.inserted = saveStateGet(state, "casInserted", 0);
    saveStateGetBuffer(state, "casName",  di->cassette.name, sizeof(di->cassette.name));
    saveStateGetBuffer(state, "casInZip", di->cassette.inZipName, sizeof(di->cassette.inZipName));
    saveStateGetBuffer(state, "keyMap",   KeyMap, sizeof(KeyMap));

    di->video.vdpSyncMode = saveStateGet(state, "vdpSyncMode", 0);

    saveStateClose(state);
}

