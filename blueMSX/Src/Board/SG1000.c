/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/SG1000.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2005-09-01 18:48:27 $
**
** More info: http://www.bluemsx.com
**
** Author: Ricardo Bittencourt
** Copyright (C) 2003-2005 Daniel Vik, Ricardo Bittencourt
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
#include "SG1000.h"
#include "SN76489.h"
#include "R800.h"
#include "R800Dasm.h"
#include "R800SaveState.h"
#include "DeviceManager.h"
#include "DebugDeviceManager.h"
#include "AudioMixer.h"
#include "SaveState.h"
#include "Led.h"
#include "Switches.h"
#include "JoystickIO.h"
#include "AY8910.h"
#include "KeyClick.h"
#include "IoPort.h"
#include "RomLoader.h"
#include "ArchControls.h"
#include "Keyboard.h"


/* Hardware */
static Machine*        sg1000Machine;
static DeviceInfo*     sg1000DevInfo;
static SN76489*        sn76489;
static R800*           r800;
static JoystickIO*     joyIO;
static UInt32          nextSyncTime;
static UInt32          loopTime;
static int             syncCount;
static int             SyncPeriod;
static int             pendingInt;
static UInt32          sg1000RamSize;
static UInt32          sg1000VramSize;
static int             useRom;
static int             traceEnabled;
static int             debugHandle;

static UInt8 sg1000Memory[0x10000];

void sg1000LoadState();
void sg1000SaveState();

static int joyMode = 0;

void sg1000SN76489Write(void* dummy, UInt16 ioPort, UInt8 value) 
{
    sn76489WriteData(sn76489, ioPort, value);
}

/*static void sg1000JoyIoWrite(void* dummy, UInt16 ioPort, UInt8 value)
{
	joyMode = (ioPort >> 6) & 1;
}*/

static UInt8 sg1000JoyIoRead(void* dummy, UInt16 ioPort)
{
    UInt8 joyState = joystickReadSG1000(joyIO, 0);

        return (joyState & 0x3F) | 0xC0;
}

static void sg1000JoyIoCreate()
{
  ioPortRegister(0x7E, NULL , sg1000SN76489Write, NULL);
  ioPortRegister(0x7F, NULL , sg1000SN76489Write, NULL);

  ioPortRegister(0xDC, sg1000JoyIoRead, NULL, NULL);
  ioPortRegister(0xC0, sg1000JoyIoRead, NULL, NULL);
}

static void sg1000JoyIoDestroy()
{
  ioPortUnregister(0x7E);
  ioPortUnregister(0x7F);
  ioPortUnregister(0xDC);
  ioPortUnregister(0xC0);
}

static void sg1000MemReset()
{
    memset(sg1000Memory, 0xff, 0x10000);
}

void sg1000MemWrite(void* ref, UInt16 address, UInt8 value)
{
    UInt8* memPtr;

    if (address < 0xA000) {
        return;
    }

    memPtr = sg1000Memory + 0xA000 + (address & 0x1fff);

    memPtr[0] = value;
    memPtr[0x2000] = value;
}

UInt8 sg1000MemRead(void* ref, UInt16 address)
{
    return sg1000Memory[address];
}

static void sg1000SaveMemory()
{
    SaveState* state = saveStateOpenForWrite("sg1000Memory");

    saveStateSetBuffer(state, "sg1000Memory", sg1000Memory, sizeof(sg1000Memory));

    saveStateClose(state);
}

static void sg1000LoadMemory()
{
    SaveState* state = saveStateOpenForRead("sg1000Memory");


    saveStateGetBuffer(state, "sg1000Memory", sg1000Memory, sizeof(sg1000Memory));

    saveStateClose(state);
}

void sg1000TraceEnable(const char* fileName) {
    traceEnabled = r800OpenTrace(fileName);
}

void sg1000TraceDisable() {
    r800CloseTrace();
    traceEnabled = 0;
}

int sg1000TraceGetEnable() {
    return traceEnabled;
}

void sg1000SetBreakpoint(UInt16 address) {
    if (r800) {
        r800SetBreakpoint(r800, address);
    }
}
void sg1000ClearBreakpoint(UInt16 address) {
    if (r800) {
        r800ClearBreakpoint(r800, address);
    }
}

UInt32 sg1000GetRamSize()
{ 
    return sg1000RamSize / 1024;
}

UInt32 sg1000GetVramSize()
{
    return sg1000VramSize / 1024;
}

int sg1000UseRom()
{
    return useRom;
}

int sg1000UseMegaRom()
{
    return 0;
}

int sg1000UseMegaRam()
{
    return 0;
}

int sg1000UseFmPac()
{
    return 0;
}

UInt32 sg1000SystemTime() 
{
    if (r800) {
        return r800GetSystemTime(r800);
    }
    return 0;
}

UInt8* sg1000GetRamPage(int page)
{
    static UInt8 emptyRam[0x2000];

    return emptyRam;
}

void sg1000SetInt(UInt32 irq)
{
    pendingInt |= irq;
    r800SetInt(r800);
}

UInt32 sg1000GetInt()
{
    return pendingInt;
}

void sg1000ClearInt(UInt32 irq)
{
    pendingInt &= ~irq;
	if (pendingInt == 0) {
        r800ClearInt(r800);
	}

}

void sg1000InitStatistics(Machine* machine)
{
    int i;

    sg1000VramSize = machine->video.vramSize;
    for (i = 0; i < machine->slotInfoCount; i++) {        if (machine->slotInfo[i].romType == RAM_NORMAL) {            sg1000RamSize = 0x2000 * machine->slotInfo[i].pageCount;        }    }
}

static int sg1000InitMachine(Machine* machine, 
                          VdpSyncMode vdpSyncMode)
{
    int success = 1;
 
    /* Initialize VDP */
    sg1000VramSize = machine->video.vramSize;
    if (vdpSyncMode == VDP_SYNC_AUTO) {
        vdpSyncMode = VDP_SYNC_60HZ;
    }
    vdpCreate(VDP_SG1000, machine->video.vdpVersion, vdpSyncMode, machine->video.vramSize / 0x4000);

    sg1000JoyIoCreate();

    /* Initialize memory */
    sg1000MemReset();
    /* Load system rom */
    /*buf = romLoad(machine->slotInfo[0].name, machine->slotInfo[0].inZipName, &size);
    if (buf != NULL) {
        if (size == 0x2000)
            memcpy(sg1000Memory, buf, size);
        else
            success = 0;
        free(buf);
    }
    else
        success = 0;*/

    ledSetCapslock(0);

    return success;
}

void sg1000Reset()
{
    UInt32 systemTime = boardSystemTime();
    if (r800 != NULL) {
        r800Reset(r800, systemTime);
    }

    if (sn76489 != NULL) {
        sn76489Reset(sn76489);
    }
    
    ledSetCapslock(0);

    deviceManagerReset();
}

void sg1000SetCpuTimeout(UInt32 time)
{
    r800SetTimeoutAt(r800, time);
}

static void cpuTimeout(void* ref)
{
    boardTimerCheckTimeout();
}

static void breakpointCb(void* ref, UInt16 pc)
{
    boardOnBreakpoint(pc);
}


extern void debuggerTrace(const char* str);
static void debugCb(void* ref, int command, const char* data) 
{
    int slot, page, addr, rv;
    switch (command) {
    case ASDBG_TRACE:
        debuggerTrace(data);
        break;
    case ASDBG_SETBP:
        rv = sscanf(data, "%x %x %x", &slot, &page, &addr);
        if (rv == 3) {
            debuggerSetBreakpoint((UInt16)slot, (UInt16)page, (UInt16)addr);
        }
        break;
    }
}

void sg1000Run() {
    r800Execute(r800);
}

void sg1000Stop() {
    r800StopExecution(r800);
}

static void getDebugInfo(void* dummy, DbgDevice* dbgDevice)
{
    DbgRegisterBank* regBank;

    dbgDeviceAddMemoryBlock(dbgDevice, "Visible Memory", 1, 0, 0x10000, sg1000Memory);

    if (r800->callstackSize > 255) {
        static UInt16 callstack[0x100];
        int beginning = r800->callstackSize & 0xff;
        int reminder = 256 - beginning;
        memcpy(callstack, r800->callstack + beginning, reminder * sizeof(UInt16));
        memcpy(callstack + reminder, r800->callstack, beginning * sizeof(UInt16));
        dbgDeviceAddCallstack(dbgDevice, "Callstack", callstack, 256);
    }
    else {
        dbgDeviceAddCallstack(dbgDevice, "Callstack", r800->callstack, r800->callstackSize);
    }

    regBank = dbgDeviceAddRegisterBank(dbgDevice, "CPU Registers", 17);

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
    dbgRegisterBankAddRegister(regBank, 14, "IM",  8,  r800->regs.im);
    dbgRegisterBankAddRegister(regBank, 15, "IFF1",8,  r800->regs.iff1);
    dbgRegisterBankAddRegister(regBank, 16, "IFF2",8,  r800->regs.iff2);
}

static int dbgWriteRegister(void* dummy, char* name, int regIndex, UInt32 value)
{
    switch (regIndex) {
    case  0: r800->regs.AF.W = (UInt16)value; break;
    case  1: r800->regs.BC.W = (UInt16)value; break;
    case  2: r800->regs.DE.W = (UInt16)value; break;
    case  3: r800->regs.HL.W = (UInt16)value; break;
    case  4: r800->regs.AF1.W = (UInt16)value; break;
    case  5: r800->regs.BC1.W = (UInt16)value; break;
    case  6: r800->regs.DE1.W = (UInt16)value; break;
    case  7: r800->regs.HL1.W = (UInt16)value; break;
    case  8: r800->regs.IX.W = (UInt16)value; break;
    case  9: r800->regs.IY.W = (UInt16)value; break;
    case 10: r800->regs.SP.W = (UInt16)value; break;
    case 11: r800->regs.PC.W = (UInt16)value; break;
    case 12: r800->regs.I = (UInt8)value; break;
    case 13: r800->regs.R = (UInt8)value; break;
    case 14: r800->regs.im = value > 2 ? 2 : (UInt8)value; break;
    case 15: r800->regs.iff1 = value > 2 ? 2 : (UInt8)value; break; 
    case 16: r800->regs.iff2 = value > 2 ? 2 : (UInt8)value; break; 
    }

    return 1;
}

int sg1000Create(Machine* machine, 
                 DeviceInfo* devInfo,
                 int loadState)
{
    DebugCallbacks dbgCallbacks = { getDebugInfo, NULL, dbgWriteRegister, NULL };
    int success;

    sg1000Machine   = machine;
    sg1000DevInfo   = devInfo;

    SyncPeriod   = 0;

    nextSyncTime  = 0;
    loopTime      = 0;
    syncCount     = 0;
    pendingInt    = 0;

    // If we're running from a state file, use its machine
    // and user configuration
    if (loadState) {
        sg1000LoadState();
        machineLoadState(sg1000Machine);
    }

    deviceManagerCreate();
    
    r800 = r800Create(sg1000MemRead, sg1000MemWrite, ioPortRead, ioPortWrite, NULL, cpuTimeout, breakpointCb, debugCb, NULL);

    boardInit(&r800->systemTime);
    ioPortReset();

    r800Reset(r800, 0);
    mixerReset(boardGetMixer());
    
    debugHandle = debugDeviceRegister(DBGTYPE_CPU, "Z80", &dbgCallbacks, NULL);

    sn76489 = sn76489Create(boardGetMixer());
    success = sg1000InitMachine(machine, devInfo->video.vdpSyncMode);

    joyIO = joystickIoCreateSG1000();

    if (devInfo->cartridge[0].inserted) {
        sg1000ChangeCartridge(0, devInfo->cartridge[0].type, 
                              devInfo->cartridge[0].name,
                              devInfo->cartridge[0].inZipName);
    }

    r800SetFrequency(r800, CPU_Z80,  machine->cpu.freqZ80);
    r800SetFrequency(r800, CPU_R800, machine->cpu.freqR800);

    if (loadState) {
        r800LoadState(r800);
        boardInit(&r800->systemTime);
        sg1000LoadMemory();
        deviceManagerLoadState();
        joystickIoLoadState(joyIO);
        machineLoadState(sg1000Machine);
        sn76489LoadState(sn76489);
        keyboardLoadState();
    }

    if (!success) {
        sg1000Destroy();
    }

    return success;
}

void sg1000Destroy() {    
    sg1000TraceDisable();

    joystickIoDestroySG1000(joyIO);

    sg1000JoyIoDestroy();
    sn76489Destroy(sn76489);

    debugDeviceUnregister(debugHandle);

    deviceManagerDestroy();
    
    r800Destroy(r800);

    sg1000Machine = NULL;
    sg1000DevInfo = NULL;

    useRom     = 0;
}

int sg1000GetRefreshRate()
{
    return vdpGetRefreshRate();
}

void sg1000ChangeCartridge(int cartNo, RomType romType, char* cart, char* cartZip)
{
    UInt8* buf;
    int size;

    if (cart && strlen(cart) == 0)
        cart = NULL;

    if (cartZip && strlen(cartZip) == 0)
        cartZip = NULL;

    if (sg1000DevInfo != NULL) {
        sg1000DevInfo->cartridge[cartNo].inserted = cart != NULL;
        sg1000DevInfo->cartridge[cartNo].type = romType;
        strcpy(sg1000DevInfo->cartridge[cartNo].name, cart ? cart : "");
        strcpy(sg1000DevInfo->cartridge[cartNo].inZipName, cartZip ? cartZip : "");
    }

    if (cartNo == 0) {
        memset(sg1000Memory, 0xff, 0xA000);
        buf = romLoad(cart, cartZip, &size);
        useRom = 0;
        if (buf != NULL) {
            if (size <= 0xA000) {
                memcpy(sg1000Memory, buf, size);
                useRom = 1;
            }
            free(buf);
        }
    }
}

void sg1000ChangeDiskette(int driveId, char* fileName, const char* fileInZipFile)
{
}

int sg1000ChangeCassette(char *name, const char *fileInZipFile)
{
    return 0;
}

void sg1000SaveState()
{    
    SaveState* state = saveStateOpenForWrite("sg1000");
    DeviceInfo* di = sg1000DevInfo;

    saveStateSet(state, "nextSyncTime",    nextSyncTime);
    saveStateSet(state, "loopTime",        loopTime);
    saveStateSet(state, "syncCount",       syncCount);
    saveStateSet(state, "SyncPeriod",      SyncPeriod);
    saveStateSet(state, "pendingInt",      pendingInt);
    
    saveStateSet(state, "cartInserted00", di->cartridge[0].inserted);
    saveStateSet(state, "cartType00",     di->cartridge[0].type);
    saveStateSetBuffer(state, "cartName00",  di->cartridge[0].name, strlen(di->cartridge[0].name) + 1);
    saveStateSetBuffer(state, "cartInZip00", di->cartridge[0].inZipName, strlen(di->cartridge[0].inZipName) + 1);
    saveStateSet(state, "cartInserted01", di->cartridge[1].inserted);
    saveStateSet(state, "cartType01",     di->cartridge[1].type);
    saveStateSetBuffer(state, "cartName01",  di->cartridge[1].name, strlen(di->cartridge[1].name) + 1);
    saveStateSetBuffer(state, "cartInZip01", di->cartridge[1].inZipName, strlen(di->cartridge[1].inZipName) + 1);

    saveStateSet(state, "vdpSyncMode",   di->video.vdpSyncMode);

    saveStateClose(state);

    sg1000SaveMemory();
    joystickIoSaveState(joyIO);
    machineSaveState(sg1000Machine);
    r800SaveState(r800);
    sn76489SaveState(sn76489);
    deviceManagerSaveState();
    keyboardSaveState();
}

void sg1000LoadState()
{
    SaveState* state = saveStateOpenForRead("sg1000");
    DeviceInfo* di = sg1000DevInfo;

    nextSyncTime        = saveStateGet(state, "nextSyncTime",    0);
    loopTime            = saveStateGet(state, "loopTime",        0);
    syncCount           = saveStateGet(state, "syncCount",       0);
    SyncPeriod          = saveStateGet(state, "SyncPeriod",      0);
    pendingInt          = saveStateGet(state, "pendingInt",      0);

    di->cartridge[0].inserted = saveStateGet(state, "cartInserted00", 0);
    di->cartridge[0].type = saveStateGet(state, "cartType00",     0);
    saveStateGetBuffer(state, "cartName00",  di->cartridge[0].name, sizeof(di->cartridge[0].name));
    saveStateGetBuffer(state, "cartInZip00", di->cartridge[0].inZipName, sizeof(di->cartridge[0].inZipName));
    di->cartridge[1].inserted = saveStateGet(state, "cartInserted01", 0);
    di->cartridge[1].type = saveStateGet(state, "cartType01",     0);
    saveStateGetBuffer(state, "cartName01",  di->cartridge[1].name, sizeof(di->cartridge[1].name));
    saveStateGetBuffer(state, "cartInZip01", di->cartridge[1].inZipName, sizeof(di->cartridge[1].inZipName));

    di->video.vdpSyncMode = saveStateGet(state, "vdpSyncMode", 0);

    saveStateClose(state);
}
