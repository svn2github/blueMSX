/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/SVI.c,v $
**
** $Revision: 1.32 $
**
** $Date: 2005-02-15 05:03:49 $
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
#include "Keyboard.h"
#include "Keyboard.h"
#include "Casette.h"
#include "Disk.h"
#include "IoPort.h"
#include "MegaromCartridge.h"
#include "DebugDeviceManager.h"
#include "VideoManager.h"
#include "SlotManager.h"
#include "ramNormal.h"
#include "RomLoader.h"
#include "romMapperNormal.h"
#include "romMapperCasette.h"
#include "romMapperPlain.h"
#include "romMapperSvi328Prn.h"
#include "romMapperSvi80Col.h"
#include "romMapperSvi328Rs232.h"
#include "romMapperSvi328Fdc.h"

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
static int             pendingInt;
static UInt32          sviRamSize;
static UInt32          sviVramSize;
static int             useRom;
static int             traceEnabled;
static UInt8*          sviRam;
static UInt8           psgAYReg15;
static int             svi80ColEnabled;
static int             debugHandle;

typedef enum { BANK_02=0x00, BANK_12=0x00, BANK_22=0xa0, BANK_32=0xf0 } sviBanksHigh;
typedef enum { BANK_01=0x00, BANK_11=0x05, BANK_21=0x0a, BANK_31=0x0f } sviBanksLow;

extern void PatchZ80(void* ref, CpuRegs* cpu);

void sviLoadState();
void sviSaveState();

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

void sviMemWrite(void* ref, UInt16 address, UInt8 value)
{
    if ((svi80ColEnabled && svi80colMemBankCtrlStatus()) && (address & 0xf800) == 0xf000)
    {
        svi80colMemWrite(address & 0xfff, value);
    }
    else
        slotWrite(&ref, address, value);
}

UInt8 sviMemRead(void* ref, UInt16 address)
{
    if ((svi80ColEnabled && svi80colMemBankCtrlStatus()) && (address & 0xf800) == 0xf000) 
        return svi80colMemRead(address & 0xfff);
    else
        return slotRead(&ref, address);
}

static void sviMemReset()
{
    slotManagerReset();
}

static void sviMemSetBank(UInt8 AYReg15)
{
    UInt8 pages;
    int i;

    psgAYReg15 = AYReg15;

    /* Map the SVI-328 bank to pages */
    pages = (AYReg15&1)?(AYReg15&2)?(AYReg15&8)?BANK_01:BANK_31:BANK_21:BANK_11;
    pages |= (AYReg15&4)?(AYReg15&16)?BANK_02:BANK_32:BANK_22;

    for (i = 0; i < 4; i++) {
        slotSetRamSlot(i, pages & 3);
        pages >>= 2;
    }
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

void sviInitStatistics(Machine* machine)
{
    int i;

    sviVramSize = machine->video.vramSize;

    for (i = 0; i < machine->slotInfoCount; i++) {

        if (machine->slotInfo[i].romType == RAM_NORMAL) {

            sviRamSize = 0x2000 * machine->slotInfo[i].pageCount;

        }

    }
}

static int sviInitMachine(Machine* machine, 
                          VdpSyncMode vdpSyncMode)
{
    UInt8* buf;
    int success = 1;
    int size;
    int i;

    sviRam = NULL;
    svi80ColEnabled = 0;

    /* Initialize VDP */
    sviVramSize = machine->video.vramSize;
    vdpCreate(VDP_SVI, machine->video.vdpVersion, vdpSyncMode, machine->video.vramSize / 0x4000);

    /* Initialize memory */
    for (i = 0; i < 4; i++) {
        slotSetSubslotted(i, 0);
    }
    for (i = 0; i < 2; i++) {
        cartridgeSetSlotInfo(i, machine->cart[i].slot, 0);
    }

    /* Initialize RAM */
    for (i = 0; i < machine->slotInfoCount; i++) {
        int slot;
        int subslot;
        int startPage;
        char* romName;
        
        // Don't map slots with error
        if (machine->slotInfo[i].error) {
            continue;
        }

        romName   = strlen(machine->slotInfo[i].inZipName) ? machine->slotInfo[i].inZipName : machine->slotInfo[i].name;
        slot      = machine->slotInfo[i].slot;
        subslot   = machine->slotInfo[i].subslot;
        startPage = machine->slotInfo[i].startPage;
        size      = 0x2000 * machine->slotInfo[i].pageCount;

        if (machine->slotInfo[i].romType == RAM_NORMAL) {
            success &= ramNormalCreate(size, slot, subslot, startPage, &sviRam, &sviRamSize);
            continue;
        }
    }

    if (sviRam == NULL) {
        return 0;
    }

    for (i = 0; i < machine->slotInfoCount; i++) {
        int slot;
        int subslot;
        int startPage;
        char* romName;
        
        // Don't map slots with error
        if (machine->slotInfo[i].error) {
            continue;
        }

        romName   = strlen(machine->slotInfo[i].inZipName) ? machine->slotInfo[i].inZipName : machine->slotInfo[i].name;
        slot      = machine->slotInfo[i].slot;
        subslot   = machine->slotInfo[i].subslot;
        startPage = machine->slotInfo[i].startPage;
        size      = 0x2000 * machine->slotInfo[i].pageCount;
        
        if (machine->slotInfo[i].romType == RAM_NORMAL) {
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_SVI328FDC) {
            success &= svi328FdcCreate();
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_SVI328PRN) {
            success &= romMapperSvi328PrnCreate();
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_SVI328RS232) {
            success &= romMapperSvi328Rs232Create(SVI328_RS232);
            continue;
        }

        buf = romLoad(machine->slotInfo[i].name, machine->slotInfo[i].inZipName, &size);

        if (buf == NULL) {
            success = 0;
            continue;
        }

        switch (machine->slotInfo[i].romType) {
        case ROM_PLAIN:
            success &= romMapperPlainCreate(romName, buf, size, slot, subslot, startPage);
            break;
        case ROM_NORMAL:
            success &= romMapperNormalCreate(romName, buf, size, slot, subslot, startPage);
            break;
        case ROM_CASPATCH:
            success &= romMapperCasetteCreate(romName, buf, size, slot, subslot, startPage);
            break;
        case ROM_SVI80COL: {
                int frameRate = (vdpSyncMode == VDP_SYNC_60HZ) ? 60 : 50;
                svi80ColEnabled = romMapperSvi80ColCreate(SVI80COL_SVI, frameRate, buf, size);
                success &= svi80ColEnabled;
            }
            break;
        }
        free(buf);
    }

    for (i = 0; i < 8; i++) {
        slotMapRamPage(0, 0, i);
    }

    sviMemSetBank(0xDF);
    ledSetCapslock(0);

    return success;
}

void sviReset()
{
    UInt32 systemTime = boardSystemTime();

    slotManagerReset();

    if (r800 != NULL) {
        r800Reset(r800, systemTime);
    }
    if (ay8910 != NULL) {
        ay8910Reset(ay8910);
    }

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

void sviRun() {
    r800Execute(r800);
}

void sviStop() {
    r800StopExecution(r800);
}

static void setDebugInfo(void* dummy, DbgDevice* dbgDevice)
{
    static UInt8 mappedRAM[0x10000];
    DbgRegisterBank* regBank;
    int i;

    for (i = 0; i < 0x10000; i++) {
        slotPeek(NULL, i);
    }

    dbgDeviceAddMemoryBlock(dbgDevice, "Mapped Memory", 0, 0x10000, mappedRAM);

    regBank = dbgDeviceAddRegisterBank(dbgDevice, "CPU Registers", 14);

    dbgRegisterBankAddRegister(regBank,  0, "AF",  16, r800->regs.AF.W);
    dbgRegisterBankAddRegister(regBank,  1, "BC",  16, r800->regs.BC.W);
    dbgRegisterBankAddRegister(regBank,  2, "DE",  16, r800->regs.DE.W);
    dbgRegisterBankAddRegister(regBank,  3, "HL",  16, r800->regs.HL.W);
    dbgRegisterBankAddRegister(regBank,  4, "AF1", 16, r800->regs.AF1.W);
    dbgRegisterBankAddRegister(regBank,  5, "BC1", 16, r800->regs.BC1.W);
    dbgRegisterBankAddRegister(regBank,  6, "DE1", 16, r800->regs.DE1.W);
    dbgRegisterBankAddRegister(regBank,  7, "HL1", 16, r800->regs.HL1.W);
    dbgRegisterBankAddRegister(regBank,  8, "IX",  16, r800->regs.IX.W);
    dbgRegisterBankAddRegister(regBank,  9, "IY",  16, r800->regs.IY.W);
    dbgRegisterBankAddRegister(regBank, 10, "SP",  16, r800->regs.SP.W);
    dbgRegisterBankAddRegister(regBank, 11, "PC",  16, r800->regs.PC.W);
    dbgRegisterBankAddRegister(regBank, 12, "I",   8,  r800->regs.I);
    dbgRegisterBankAddRegister(regBank, 13, "R",   8,  r800->regs.R);
    dbgRegisterBankAddRegister(regBank, 14, "IFF", 8,  (r800->regs.iff1 != 0 ? 1 : 0)  + 2 * (r800->regs.iff2 != 0 ? 1 : 0));
}

int sviCreate(Machine* machine, 
              DeviceInfo* devInfo,
              int loadState)
{
    int success;
    int i;

    sviMachine   = machine;
    sviDevInfo   = devInfo;

    SyncPeriod   = 0;

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

//    r800 = r800Create(slotRead, slotWrite, ioPortRead, ioPortWrite, PatchZ80, cpuTimeout, NULL);
    r800 = r800Create(sviMemRead, sviMemWrite, ioPortRead, ioPortWrite, PatchZ80, cpuTimeout, NULL);

    boardInit(&r800->systemTime);
    ioPortReset();

    r800Reset(r800, 0);
    mixerReset(boardGetMixer());
    
    debugHandle = debugDeviceRegister(DBGTYPE_CPU, "Z80", setDebugInfo, NULL);

    ay8910 = ay8910Create(boardGetMixer(), AY8910_SVI);
    ay8910SetIoPort(ay8910, sviPsgReadHandler, sviPsgWriteHandler, NULL);

    keyClick  = audioKeyClickCreate(boardGetMixer());

    joyIO = joystickIoCreateSVI();
    
    sviPPICreate(joyIO);
    slotManagerCreate();

    success = sviInitMachine(machine, devInfo->video.vdpSyncMode);

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
        boardInit(&r800->systemTime);
        deviceManagerLoadState();
        joystickIoLoadState(joyIO);
        machineLoadState(sviMachine);
        ay8910LoadState(ay8910);
        tapeLoadState();
        videoManagerLoadState();
        keyboardLoadState();
    }

    if (!success) {
        sviDestroy();
    }

    return success;
}

void sviDestroy() {    
    sviTraceDisable();

    joystickIoDestroySVI(joyIO);

    ay8910SetIoPort(ay8910, NULL, NULL, NULL);
    ay8910Destroy(ay8910);
    ay8910 = NULL;
    audioKeyClickDestroy(keyClick);

    debugDeviceUnregister(debugHandle);

    sviChangeDiskette(0, NULL, NULL);
    sviChangeDiskette(1, NULL, NULL);

    sviChangeCassette(0, 0);

    slotManagerDestroy();

    deviceManagerDestroy();

    r800Destroy(r800);

    sviMachine = NULL;
    sviDevInfo = NULL;

    useRom     = 0;
}

int sviGetRefreshRate()
{
    return vdpGetRefreshRate();
}

UInt8* sviGetRamPage(int page)
{
    static UInt8 emptyRam[0x2000];

    if (sviRam == NULL) {
        return emptyRam;
    }

    return sviRam + ((page * 0x2000) & (sviRamSize - 1));
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

void sviChangeCartridge(int cartNo, RomType romType, char* cart, char* cartZip)
{
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
        cartridgeInsert(cartNo, ROM_PLAIN, cart, cartZip); 
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

    diskChangeSVI(driveId, fileName, fileInZipFile);
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
    saveStateSet(state, "svi80ColEnabled", svi80ColEnabled);
    
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

    saveStateSet(state, "psgAYReg15",     psgAYReg15);

    saveStateClose(state);

    joystickIoSaveState(joyIO);
    machineSaveState(sviMachine);
    r800SaveState(r800);
    deviceManagerSaveState();
    ay8910SaveState(ay8910);
    tapeSaveState();
    videoManagerSaveState();
    keyboardSaveState();
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
    svi80ColEnabled     = saveStateGet(state, "svi80ColEnabled", 0);

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

    psgAYReg15     = (UInt8)saveStateGet(state, "psgAYReg15",     0);

    saveStateClose(state);
}
