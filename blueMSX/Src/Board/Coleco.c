/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/Coleco.c,v $
**
** $Revision: 1.13 $
**
** $Date: 2005-02-06 19:33:50 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vik, Tomas Karlsson, Maarten ter Huurne
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
#include "Coleco.h"
#include "SN76489.h"
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
#include "IoPort.h"
#include "RomLoader.h"
#include "ArchControls.h"
#include "Keyboard.h"


/* Hardware */
static Machine*        colecoMachine;
static DeviceInfo*     colecoDevInfo;
static SN76489*        sn76489;
static R800*           r800;
static JoystickIO*     joyIO;
static UInt32          nextSyncTime;
static UInt32          loopTime;
static int             syncCount;
static int             SyncPeriod;
static UInt32          colecoFrequency;
static int             pendingInt;
static UInt32          colecoRamSize;
static UInt32          colecoVramSize;
static int             useRom;
static int             traceEnabled;

static UInt8 colecoMemory[0x10000];

void colecoLoadState();
void colecoSaveState();

static int joyMode = 0;

void colecoSN76489Write(void* dummy, UInt16 ioPort, UInt8 value) 
{
    sn76489WriteData(sn76489, ioPort, value);
}

static void colecoJoyIoWrite(void* dummy, UInt16 ioPort, UInt8 value)
{
	joyMode = (ioPort >> 6) & 1;
}

static UInt8 colecorJoyIoRead(void* dummy, UInt16 ioPort)
{
    UInt8 joyState = joystickReadColeco(joyIO, ioPort >> 1);
    UInt8* keyMap = keyboardGetState();
    UInt8 value;

    if (joyMode != 0) {
        return ((joyState & 0x01) ? 0x01 : 0) |
               ((joyState & 0x08) ? 0x02 : 0) |
               ((joyState & 0x02) ? 0x04 : 0) |
               ((joyState & 0x04) ? 0x08 : 0) |
               ((joyState & 0x10) ? 0x40 : 0) |
               0x30;
    }

    value = 0x30 | ((joyState & 0x20) ? 0x40 : 0);

	if (ioPort & 2) {
		if      (~keyMap[ 9] & 0x08) value |= 0x0A; // 0
		else if (~keyMap[ 9] & 0x10) value |= 0x0D; // 1
		else if (~keyMap[ 9] & 0x20) value |= 0x07; // 2
		else if (~keyMap[ 9] & 0x40) value |= 0x0C; // 3
		else if (~keyMap[ 9] & 0x80) value |= 0x02; // 4
		else if (~keyMap[10] & 0x01) value |= 0x03; // 5
		else if (~keyMap[10] & 0x02) value |= 0x0E; // 6
		else if (~keyMap[10] & 0x04) value |= 0x05; // 7
		else if (~keyMap[10] & 0x08) value |= 0x01; // 8
		else if (~keyMap[10] & 0x10) value |= 0x0B; // 9
		else if (~keyMap[ 9] & 0x01) value |= 0x09; // *
		else if (~keyMap[ 9] & 0x04) value |= 0x06; // / to #
    }
    else {
		if      (~keyMap[0] & 0x01) value |= 0x0A; // 0
		else if (~keyMap[0] & 0x02) value |= 0x0D; // 1
		else if (~keyMap[0] & 0x04) value |= 0x07; // 2
		else if (~keyMap[0] & 0x08) value |= 0x0C; // 3
		else if (~keyMap[0] & 0x10) value |= 0x02; // 4
		else if (~keyMap[0] & 0x20) value |= 0x03; // 5
		else if (~keyMap[0] & 0x40) value |= 0x0E; // 6
		else if (~keyMap[0] & 0x80) value |= 0x05; // 7
		else if (~keyMap[1] & 0x01) value |= 0x01; // 8
		else if (~keyMap[1] & 0x02) value |= 0x0B; // 9
		else if (~keyMap[1] & 0x04) value |= 0x09; // - to *
		else if (~keyMap[1] & 0x08) value |= 0x06; // = to #
	}

    return value;
}

static void colecoJoyIoCreate()
{
    int i;
    for (i = 0xe0; i <= 0xff; i++) {
        ioPortRegister(i, colecorJoyIoRead, colecoSN76489Write, NULL);
    }
    for (i = 0x80; i <= 0x9f; i++) {
        ioPortRegister(i, NULL, colecoJoyIoWrite, NULL);
    }
    for (i = 0xc0; i <= 0xdf; i++) {
        ioPortRegister(i, NULL, colecoJoyIoWrite, NULL);
    }
}

static void colecoJoyIoDestroy()
{
    int i;
    for (i = 0xe0; i <= 0xff; i++) {
        ioPortUnregister(i);
    }
}

static void colecoMemReset()
{
    memset(colecoMemory, 0xff, 0x10000);
}

void colecoMemWrite(void* ref, UInt16 address, UInt8 value)
{
    UInt8* memPtr;

    if (address < 0x6000 || address >= 0x8000) {
        return;
    }

    memPtr = colecoMemory + (address & 0x63ff);

    memPtr[0x0000] = value;
    memPtr[0x0400] = value;
    memPtr[0x0800] = value;
    memPtr[0x0c00] = value;
    memPtr[0x1000] = value;
    memPtr[0x1400] = value;
    memPtr[0x1800] = value;
    memPtr[0x1c00] = value;
}

UInt8 colecoMemRead(void* ref, UInt16 address)
{
    return colecoMemory[address];
}

static void colecoSaveMemory()
{
    SaveState* state = saveStateOpenForWrite("colecoMemory");

    saveStateSetBuffer(state, "colecoMemory", colecoMemory, sizeof(colecoMemory));

    saveStateClose(state);
}

static void colecoLoadMemory()
{
    SaveState* state = saveStateOpenForRead("colecoMemory");


    saveStateGetBuffer(state, "colecoMemory", colecoMemory, sizeof(colecoMemory));

    saveStateClose(state);
}

void colecoTraceEnable(const char* fileName) {
    traceEnabled = r800OpenTrace(fileName);
}

void colecoTraceDisable() {
    r800CloseTrace();
    traceEnabled = 0;
}

int colecoTraceGetEnable() {
    return traceEnabled;
}

UInt32 colecoGetRamSize()
{ 
    return colecoRamSize / 1024;
}

UInt32 colecoGetVramSize()
{
    return colecoVramSize / 1024;
}

int colecoUseRom()
{
    return useRom;
}

int colecoUseMegaRom()
{
    return 0;
}

int colecoUseMegaRam()
{
    return 0;
}

int colecoUseFmPac()
{
    return 0;
}

UInt32 colecoSystemTime() 
{
    if (r800) {
        return r800GetSystemTime(r800);
    }
    return 0;
}

UInt8* colecoGetRamPage(int page)
{
    static UInt8 emptyRam[0x2000];

    return emptyRam;
}

void colecoSetInt(UInt32 irq)
{
    pendingInt |= irq;
    r800SetNmi(r800);
}

UInt32 colecoGetInt()
{
    return pendingInt;
}

void colecoClearInt(UInt32 irq)
{
    pendingInt &= ~irq;
    if (pendingInt == 0)
        r800ClearNmi(r800);
}

void colecoInitStatistics(Machine* machine)
{
    int i;

    colecoVramSize = machine->video.vramSize;
    for (i = 0; i < machine->slotInfoCount; i++) {        if (machine->slotInfo[i].romType == RAM_NORMAL) {            colecoRamSize = 0x2000 * machine->slotInfo[i].pageCount;        }    }
}

static int colecoInitMachine(Machine* machine, 
                          VdpSyncMode vdpSyncMode)
{
    UInt8* buf;
    int success = 1;
    int size;

    /* Initialize VDP */
    colecoVramSize = machine->video.vramSize;
    if (vdpSyncMode == VDP_SYNC_AUTO) {
        vdpSyncMode = VDP_SYNC_60HZ;
    }
    vdpCreate(VDP_COLECO, machine->video.vdpVersion, vdpSyncMode, machine->video.vramSize / 0x4000);

    colecoJoyIoCreate();

    /* Initialize memory */
    colecoMemReset();
    /* Load system rom */
    buf = romLoad(machine->slotInfo[0].name, machine->slotInfo[0].inZipName, &size);
    if (buf != NULL) {
        if (size == 0x2000)
            memcpy(colecoMemory, buf, size);
        else
            success = 0;
        free(buf);
    }
    else
        success = 0;

    ledSetCapslock(0);

    return success;
}

void colecoReset()
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

void colecoSetCpuTimeout(UInt32 time)
{
    r800SetTimeoutAt(r800, time);
}

static void cpuTimeout(void* ref)
{
    boardTimerCheckTimeout();
}

void colecoRun() {
    r800Execute(r800);
}

void colecoStop() {
    r800StopExecution(r800);
}

int colecoCreate(Machine* machine, 
                 DeviceInfo* devInfo,
                 int loadState,
                 int frequency)
{
    int success;

    colecoMachine   = machine;
    colecoDevInfo   = devInfo;

    SyncPeriod   = 0;
    colecoFrequency = frequency;

    nextSyncTime  = 0;
    loopTime      = 0;
    syncCount     = 0;
    pendingInt    = 0;

    // If we're running from a state file, use its machine
    // and user configuration
    if (loadState) {
        colecoLoadState();
        machineLoadState(colecoMachine);
    }

    deviceManagerCreate();
    
    r800 = r800Create(colecoMemRead, colecoMemWrite, ioPortRead, ioPortWrite, NULL, cpuTimeout, NULL);

    boardInit(&r800->systemTime);
    ioPortReset();

    r800Reset(r800, 0);
    mixerReset(boardGetMixer());

    sn76489 = sn76489Create(boardGetMixer());
    success = colecoInitMachine(machine, devInfo->video.vdpSyncMode);

    joyIO = joystickIoCreateColeco();

    if (devInfo->cartridge[0].inserted) {
        colecoChangeCartridge(0, devInfo->cartridge[0].type, 
                              devInfo->cartridge[0].name,
                              devInfo->cartridge[0].inZipName);
    }

    r800SetFrequency(r800, CPU_Z80,  machine->cpu.freqZ80);
    r800SetFrequency(r800, CPU_R800, machine->cpu.freqR800);

    if (loadState) {
        r800LoadState(r800);
        boardInit(&r800->systemTime);
        colecoLoadMemory();
        deviceManagerLoadState();
        joystickIoLoadState(joyIO);
        machineLoadState(colecoMachine);
        sn76489LoadState(sn76489);
        keyboardLoadState();
    }

    if (!success) {
        colecoDestroy();
    }

    return success;
}

void colecoDestroy() {    
    colecoTraceDisable();

    joystickIoDestroyColeco(joyIO);

    colecoJoyIoDestroy();
    sn76489Destroy(sn76489);

    deviceManagerDestroy();
    
    r800Destroy(r800);

    colecoMachine = NULL;
    colecoDevInfo = NULL;

    useRom     = 0;
}

void colecoSetFrequency(UInt32 frequency)
{
    colecoFrequency = frequency;
}

int colecoGetRefreshRate()
{
    return vdpGetRefreshRate();
}

void colecoChangeCartridge(int cartNo, RomType romType, char* cart, char* cartZip)
{
    UInt8* buf;
    int size;

    if (cart && strlen(cart) == 0)
        cart = NULL;

    if (cartZip && strlen(cartZip) == 0)
        cartZip = NULL;

    if (colecoDevInfo != NULL) {
        colecoDevInfo->cartridge[cartNo].inserted = cart != NULL;
        colecoDevInfo->cartridge[cartNo].type = romType;
        strcpy(colecoDevInfo->cartridge[cartNo].name, cart ? cart : "");
        strcpy(colecoDevInfo->cartridge[cartNo].inZipName, cartZip ? cartZip : "");
    }

    if (cartNo == 0) {
        memset(&colecoMemory[0x8000], 0xff, 0x8000);
        buf = romLoad(cart, cartZip, &size);
        useRom = 0;
        if (buf != NULL) {
            if (size <= 0x8000) {
                memcpy(&colecoMemory[0x8000], buf, size);
                useRom = 1;
            }
            free(buf);
        }
    }
}

void colecoChangeDiskette(int driveId, char* fileName, const char* fileInZipFile)
{
}

int colecoChangeCassette(char *name, const char *fileInZipFile)
{
    return 0;
}

void colecoSaveState()
{    
    SaveState* state = saveStateOpenForWrite("coleco");
    DeviceInfo* di = colecoDevInfo;

    saveStateSet(state, "nextSyncTime",    nextSyncTime);
    saveStateSet(state, "loopTime",        loopTime);
    saveStateSet(state, "syncCount",       syncCount);
    saveStateSet(state, "SyncPeriod",      SyncPeriod);
    saveStateSet(state, "pendingInt",      pendingInt);
    saveStateSet(state, "colecoFrequency", colecoFrequency);
    
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

    colecoSaveMemory();
    joystickIoSaveState(joyIO);
    machineSaveState(colecoMachine);
    r800SaveState(r800);
    sn76489SaveState(sn76489);
    deviceManagerSaveState();
    keyboardSaveState();
}

void colecoLoadState()
{
    SaveState* state = saveStateOpenForRead("coleco");
    DeviceInfo* di = colecoDevInfo;

    nextSyncTime        = saveStateGet(state, "nextSyncTime",    0);
    loopTime            = saveStateGet(state, "loopTime",        0);
    syncCount           = saveStateGet(state, "syncCount",       0);
    SyncPeriod          = saveStateGet(state, "SyncPeriod",      0);
    pendingInt          = saveStateGet(state, "pendingInt",      0);
    colecoFrequency        = saveStateGet(state, "colecoFrequency",    0);

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
