/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/SVI.c,v $
**
** $Revision: 1.7 $
**
** $Date: 2005-01-03 23:12:31 $
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include "SVI.h"
#include "SviPPI.h"
#include "R800.h"
#include "R800Dasm.h"
#include "R800SaveState.h"
#include "DeviceManager.h"
#include "AudioMixer.h"
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
static Mixer*          sviMixer;
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

void sviSetCpuTimeout(UInt32 time)
{
    r800SetTimeoutAt(r800, time);
}

static void cpuTimeout(void* ref)
{
    boardTimerCheckTimeout();
}

static void onSync(void* ref, UInt32 time)
{
    BoardTimer* timer = (BoardTimer*)ref;
    int execTime = 0;

    while (execTime == 0) {
        execTime = WaitForSync();

        if (execTime < 0) {
            r800StopExecution(r800);
            return;
        }
    }

    mixerSync(sviMixer);

    boardTimerAdd(timer, boardSystemTime() + (UInt32)((UInt64)execTime * boardFrequency() / 1000));
}

int sviRun(Machine* machine, 
           DeviceInfo* devInfo,
           Mixer* mixer,
           int loadState,
           int frequency)
{
    int success;
    int i;

    sviMixer     = mixer;
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
    boardInit(0);
    ioPortReset();

    r800 = r800Create(sviMemRead, sviMemWrite, ioPortRead, ioPortWrite, PatchZ80, cpuTimeout, NULL);
    r800Reset(r800, 0);
    mixerReset(mixer);

    ay8910 = ay8910Create(mixer, AY8910_SVI);
    ay8910SetIoPort(ay8910, sviPsgReadHandler, sviPsgWriteHandler, NULL);

    keyClick  = audioKeyClickCreate(mixer);

    joyIO = joystickIoCreateSVI();
    
    sviPPICreate(joyIO);

    success = sviInitMachine(machine, mixer, devInfo->video.vdpSyncMode);

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
        r800LoadState(r800);
        boardInit(boardSystemTime());
        sviLoadMemory();
        deviceManagerLoadState();
        joystickIoLoadState(joyIO);
        machineLoadState(sviMachine);
        ay8910LoadState(ay8910);
        vdpLoadState();
        tapeLoadState();
    }

    if (success) {
        BoardTimer* timer = boardTimerCreate(onSync, NULL);
        
        boardTimerAdd(timer, boardSystemTime() + 1);

        r800Execute(r800);
    }

    sviTraceDisable();

    joystickIoDestroySVI(joyIO);

    ay8910SetIoPort(ay8910, NULL, NULL, NULL);
    ay8910Destroy(ay8910);
    ay8910 = NULL;
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

int sviChangeCassette(char *name, const char *fileInZipFile)
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

    return sviDevInfo ? sviDevInfo->cassette.inserted : 0;
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

