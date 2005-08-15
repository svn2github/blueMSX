/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Emulator/Emulator.c,v $
**
** $Revision: 1.30 $
**
** $Date: 2005-08-15 05:37:52 $
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
#include "Emulator.h"
#include "MsxTypes.h"
#include "Debugger.h"
#include "Board.h"
#include "FileHistory.h"
#include "Switches.h"
#include "Led.h"
#include "Machine.h"
#include "JoystickIO.h"

#include "ArchThread.h"
#include "ArchEvent.h"
#include "ArchTimer.h"
#include "ArchSound.h"
#include "ArchMidi.h"
#include "ArchControls.h"
#include "ArchNotifications.h"
#include "Keyboard.h"

#include <math.h>

UInt32  emuFixedPalette[256];
UInt32  emuFixedSpritePalette[16];
UInt32  emuPalette0;
UInt32  emuPalette[16];
UInt32* emuFrameBuffer;
int*    emuLineWidth;

static int WaitForSync(int maxSpeed, int breakpointHit);

static void*  emuThread;
static void*  emuSyncEvent;
static void*  emuStartEvent;
static void*  emuTimer;
static int    emuExitFlag;
static UInt32 emuSysTime = 0;
static UInt32 emuFrequency = 3579545;
int           emuMaxSpeed = 0;
int           emuMaxEmuSpeed = 0; // Max speed issued by emulation
static char   emuStateName[512];
static volatile int      emuSuspendFlag;
static volatile EmuState emuState = EMU_STOPPED;
static volatile int      emuSingleStep = 0;
static Properties* properties;
static Mixer* mixer;
static DeviceInfo deviceInfo;
static Machine* machine;
static int lastScreenMode;

static int emuFrameskipCounter = 0;

static UInt32 emuTimeIdle       = 0;
static UInt32 emuTimeTotal      = 1;
static UInt32 emuTimeOverflow   = 0;
static UInt32 emuUsageCurrent   = 0;
static UInt32 emuCpuSpeed       = 0;
static UInt32 emuCpuUsage       = 0;
static int    enableSynchronousUpdate = 1;

static void emuCalcCpuUsage() {
    static UInt32 oldSysTime = 0;
    static UInt32 oldAverage = 0;
    static UInt32 cnt = 0;
    UInt32 newSysTime;
    UInt32 emuTimeAverage;

    if (emuTimeTotal < 10) {
        return;
    }
    newSysTime = archGetSystemUpTime(1000);
    emuTimeAverage = 100 * (emuTimeTotal - emuTimeIdle) / (emuTimeTotal / 10);
    
    emuTimeOverflow = emuTimeAverage > 940;

    if ((cnt++ & 0x1f) == 0) {
        UInt32 usageAverage = emuUsageCurrent * 100 / (newSysTime - oldSysTime) * emuFrequency / 3579545;
        if (usageAverage > 98 && usageAverage < 102) {
            usageAverage = 100;
        }

        if (usageAverage >= 10000) {
            usageAverage = 0;
        }

        emuCpuSpeed = usageAverage;
        emuCpuUsage = emuTimeAverage;
    }

    oldSysTime      = newSysTime;
    emuUsageCurrent = 0;
    emuTimeIdle     = 0;
    emuTimeTotal    = 1;
}

static int emuUseSynchronousUpdate()
{
    if (properties->emulation.speed == 50 &&
        enableSynchronousUpdate &&
        emulatorGetMaxSpeed() == 0)
    {
        return properties->emulation.syncMethod;
    }
    return P_EMU_SYNCAUTO;
}

UInt32 emulatorGetCpuSpeed() {
    return emuCpuSpeed;
}

UInt32 emulatorGetCpuUsage() {
    return emuCpuUsage;
}

void emuEnableSynchronousUpdate(int enable)
{
    enableSynchronousUpdate = enable;
}

void emulatorInit(Properties* theProperties, Mixer* theMixer)
{
    properties = theProperties;
    mixer      = theMixer;
}


EmuState emulatorGetState() {
    return emuState;
}

void emulatorSetState(EmuState state) {
    if (state == EMU_RUNNING) {
        archSoundResume();
        archMidiEnable(1);
    }
    else {
        archSoundSuspend();
        archMidiEnable(0);
    }
    if (state == EMU_STEP) {
        state = EMU_RUNNING;
        emuSingleStep = 1;
    }
    emuState = state;
}

void emulatorRunOne() {
    archEventSet(emuSyncEvent);
}

int emulatorGetSyncPeriod() {
    return properties->emulation.syncMethod == P_EMU_SYNCAUTO ||
           properties->emulation.syncMethod == P_EMU_SYNCNONE ? 2 : 1;
}

void timerCallback(void* timer) {
    static UInt32 frameCount = 0;
    static UInt32 emuCount = 0;
    static UInt32 kbdCount = 0;
    static UInt32 oldSysTime = 0;
    static UInt32 refreshRate = 50;
    UInt32 framePeriod = (properties->video.frameSkip + 1) * 1000;
    UInt32 syncPeriod = emulatorGetSyncPeriod();
    UInt32 sysTime = archGetSystemUpTime(1000);
    UInt32 diffTime = sysTime - oldSysTime;

    if (diffTime == 0) {
        return;
    }

    oldSysTime = sysTime;

    // Update display
    frameCount += refreshRate * diffTime;
    if (frameCount >= framePeriod) {
        frameCount %= framePeriod;
        if (emuState == EMU_RUNNING) {
            int syncMethod = emuUseSynchronousUpdate();
            refreshRate = boardGetRefreshRate();

            if (syncMethod == P_EMU_SYNCAUTO || syncMethod == P_EMU_SYNCNONE) {
                archUpdateEmuDisplay(0);
            }
        }
    }

    // Update emulation
    emulatorRunOne();
}

static void getDeviceInfo(DeviceInfo* deviceInfo) 
{
    strcpy(properties->cartridge.slotA,    deviceInfo->cartridge[0].name);
    strcpy(properties->cartridge.slotAZip, deviceInfo->cartridge[0].inZipName);
    properties->cartridge.slotAType = deviceInfo->cartridge[0].type;

    strcpy(properties->cartridge.slotB,    deviceInfo->cartridge[1].name);
    strcpy(properties->cartridge.slotBZip, deviceInfo->cartridge[1].inZipName);
    properties->cartridge.slotBType = deviceInfo->cartridge[1].type;

    strcpy(properties->diskdrive.slotA,    deviceInfo->diskette[0].name);
    strcpy(properties->diskdrive.slotAZip, deviceInfo->diskette[0].inZipName);

    strcpy(properties->diskdrive.slotB,    deviceInfo->diskette[1].name);
    strcpy(properties->diskdrive.slotBZip, deviceInfo->diskette[1].inZipName);

    strcpy(properties->cassette.tape,      deviceInfo->cassette.name);
    strcpy(properties->cassette.tapeZip,   deviceInfo->cassette.inZipName);
    
    properties->emulation.vdpSyncMode      = deviceInfo->video.vdpSyncMode;

    updateExtendedRomName(0, properties->cartridge.slotA, properties->cartridge.slotAZip);
    updateExtendedRomName(1, properties->cartridge.slotB, properties->cartridge.slotBZip);
    updateExtendedDiskName(0, properties->diskdrive.slotA, properties->diskdrive.slotAZip);
    updateExtendedDiskName(1, properties->diskdrive.slotB, properties->diskdrive.slotBZip);
    updateExtendedCasName(properties->cassette.tape, properties->cassette.tapeZip);
}

static void setDeviceInfo(DeviceInfo* deviceInfo) 
{
    /* Set cart A */
    deviceInfo->cartridge[0].inserted =  strlen(properties->cartridge.slotA);
    deviceInfo->cartridge[0].type = properties->cartridge.slotAType;
    strcpy(deviceInfo->cartridge[0].name,      properties->cartridge.slotA);
    strcpy(deviceInfo->cartridge[0].inZipName, properties->cartridge.slotAZip);

    /* Set cart B */
    deviceInfo->cartridge[1].inserted =  strlen(properties->cartridge.slotB);
    deviceInfo->cartridge[1].type = properties->cartridge.slotBType;
    strcpy(deviceInfo->cartridge[1].name,      properties->cartridge.slotB);
    strcpy(deviceInfo->cartridge[1].inZipName, properties->cartridge.slotBZip);

    /* Set disk A */
    deviceInfo->diskette[0].inserted =  strlen(properties->diskdrive.slotA);
    strcpy(deviceInfo->diskette[0].name,      properties->diskdrive.slotA);
    strcpy(deviceInfo->diskette[0].inZipName, properties->diskdrive.slotAZip);

    /* Set disk B */
    deviceInfo->diskette[1].inserted =  strlen(properties->diskdrive.slotB);
    strcpy(deviceInfo->diskette[1].name,      properties->diskdrive.slotB);
    strcpy(deviceInfo->diskette[1].inZipName, properties->diskdrive.slotBZip);

    /* Set tape */
    deviceInfo->cassette.inserted =  strlen(properties->cassette.tape);
    strcpy(deviceInfo->cassette.name,      properties->cassette.tape);
    strcpy(deviceInfo->cassette.inZipName, properties->cassette.tapeZip);
    
    /* Set video config */
    deviceInfo->video.vdpSyncMode     = properties->emulation.vdpSyncMode;
}

static int emulationStartFailure = 0;

static void emulatorThread() {
    int frequency;
    int success = 0;

    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);

    emulatorSetFrequency(properties->emulation.speed, &frequency);

    switchSetFront(properties->emulation.frontSwitch);
    switchSetPause(properties->emulation.pauseSwitch);
    switchSetAudio(properties->emulation.audioSwitch);

    success = boardRun(machine,
                       &deviceInfo,
                       mixer,
                       *emuStateName ? emuStateName : NULL,
                       frequency, WaitForSync);

    ledSetAll(0);
    emuState = EMU_STOPPED;

    archTimerDestroy(emuTimer);

    if (!success) {
        emulationStartFailure = 1;
    }
    
    archEventSet(emuStartEvent);
}

void emulatorStart(char* stateName) {
    UInt32 color = videoGetColor(0, 0, 0);
    int i;

    dbgEnable();

    archEmulationStartNotification();

    emulatorResume();

    emuExitFlag = 0;

    for (i = 0; i < 256; i++) {
        emuFixedPalette[i] = videoGetColor(255 * ((i >> 2) & 7) / 7, 
                                           255 * ((i >> 5) & 7) / 7, 
                                           255 * ((i & 3) == 3 ? 7 : 2 * (i & 3)) / 7);
    }

    emuFixedSpritePalette[0]  = videoGetColor(0 * 255 / 7, 0 * 255 / 7, 0 * 255 / 7);
    emuFixedSpritePalette[1]  = videoGetColor(0 * 255 / 7, 0 * 255 / 7, 2 * 255 / 7);
    emuFixedSpritePalette[2]  = videoGetColor(3 * 255 / 7, 0 * 255 / 7, 0 * 255 / 7);
    emuFixedSpritePalette[3]  = videoGetColor(3 * 255 / 7, 0 * 255 / 7, 2 * 255 / 7);
    emuFixedSpritePalette[4]  = videoGetColor(0 * 255 / 7, 3 * 255 / 7, 0 * 255 / 7);
    emuFixedSpritePalette[5]  = videoGetColor(0 * 255 / 7, 3 * 255 / 7, 2 * 255 / 7);
    emuFixedSpritePalette[6]  = videoGetColor(3 * 255 / 7, 3 * 255 / 7, 0 * 255 / 7);
    emuFixedSpritePalette[7]  = videoGetColor(3 * 255 / 7, 3 * 255 / 7, 2 * 255 / 7);
    emuFixedSpritePalette[8]  = videoGetColor(7 * 255 / 7, 4 * 255 / 7, 2 * 255 / 7);
    emuFixedSpritePalette[9]  = videoGetColor(0 * 255 / 7, 0 * 255 / 7, 7 * 255 / 7);
    emuFixedSpritePalette[10] = videoGetColor(7 * 255 / 7, 0 * 255 / 7, 0 * 255 / 7);
    emuFixedSpritePalette[11] = videoGetColor(7 * 255 / 7, 0 * 255 / 7, 7 * 255 / 7);
    emuFixedSpritePalette[12] = videoGetColor(0 * 255 / 7, 7 * 255 / 7, 0 * 255 / 7);
    emuFixedSpritePalette[13] = videoGetColor(0 * 255 / 7, 7 * 255 / 7, 7 * 255 / 7);
    emuFixedSpritePalette[14] = videoGetColor(7 * 255 / 7, 7 * 255 / 7, 0 * 255 / 7);
    emuFixedSpritePalette[15] = videoGetColor(7 * 255 / 7, 7 * 255 / 7, 7 * 255 / 7);

    mixerIsChannelTypeActive(mixer, MIXER_CHANNEL_MOONSOUND, 1);
    mixerIsChannelTypeActive(mixer, MIXER_CHANNEL_MSXAUDIO, 1);
    mixerIsChannelTypeActive(mixer, MIXER_CHANNEL_MSXMUSIC, 1);
    mixerIsChannelTypeActive(mixer, MIXER_CHANNEL_SCC, 1);
    
    properties->emulation.pauseSwitch = 0;
    switchSetPause(properties->emulation.pauseSwitch);

    machine = machineCreate(properties->emulation.machineName);

    if (machine == NULL) {  
        MessageBox(NULL, langErrorStartEmu(), langErrorTitle(), MB_ICONHAND | MB_OK);
        archEmulationStopNotification();
        emuState = EMU_STOPPED;
        archEmulationStartFailure();
        return;
    }

    boardSetMachine(machine);

    emuSyncEvent  = CreateEvent(NULL, 0, 0, NULL);
    emuStartEvent = CreateEvent(NULL, 0, 0, NULL);
    emuTimer      = 0;

    if (properties->emulation.syncMethod == P_EMU_SYNCTOVBLANK ||
        properties->emulation.syncMethod == P_EMU_SYNCAUTO ||
        properties->emulation.syncMethod == P_EMU_SYNCNONE ||
        properties->emulation.syncMethod == P_EMU_SYNCFRAMES)
    {
        emuTimer = archCreateTimer(emulatorGetSyncPeriod(), timerCallback);
    }

    setDeviceInfo(&deviceInfo);

    switch (machine->board.type) {
    default:
    case BOARD_MSX:
        keyboardSetKeymap(KEYMAP_MSX);
        break;
    case BOARD_SVI:
        keyboardSetKeymap(KEYMAP_SVI);
        break;
    case BOARD_COLECO:
        keyboardSetKeymap(KEYMAP_COLECO);
        break;
    }

    archSoundResume();
    archMidiEnable(1);

    emuState = EMU_PAUSED;
    emulationStartFailure = 0;
    strcpy(emuStateName, stateName ? stateName : "");

    emuThread = archThreadCreate(emulatorThread);
    
    archEventWait(emuStartEvent, 3000);
    
    if (emulationStartFailure) {
        archEmulationStopNotification();
        emuState = EMU_STOPPED;
        archEmulationStartFailure();
    }
    if (emuState != EMU_STOPPED) {
        getDeviceInfo(&deviceInfo);

        joystickIoGetType(0, (int*)&properties->joy1.type);
        joystickIoGetType(1, (int*)&properties->joy2.type);

        boardSetYm2413Oversampling(properties->sound.chip.ym2413Oversampling);
        boardSetY8950Oversampling(properties->sound.chip.y8950Oversampling);
        boardSetMoonsoundOversampling(properties->sound.chip.moonsoundOversampling);

        strcpy(properties->emulation.machineName, machine->name);

        debuggerNotifyEmulatorStart();
        
        emuState = EMU_RUNNING;
    }
} 

void emulatorStop() {
    if (emuState == EMU_STOPPED) {
        return;
    }

    debuggerNotifyEmulatorStop();

    emuState = EMU_STOPPED;

    do {
        Sleep(10);
    } while (!emuSuspendFlag);

    emuExitFlag = 1;
    archEventSet(emuSyncEvent);
    archThreadJoin(emuThread, 400);
    archSoundSuspend();
    archMidiEnable(0);
    machineDestroy(machine);
    archThreadDestroy(emuThread);
    archEventDestroy(emuSyncEvent);
    archEventDestroy(emuStartEvent);
    
    // Reset active indicators in mixer
    mixerIsChannelTypeActive(mixer, MIXER_CHANNEL_MOONSOUND, 1);
    mixerIsChannelTypeActive(mixer, MIXER_CHANNEL_MSXAUDIO, 1);
    mixerIsChannelTypeActive(mixer, MIXER_CHANNEL_MSXMUSIC, 1);
    mixerIsChannelTypeActive(mixer, MIXER_CHANNEL_SCC, 1);

    archMidiUpdateDriver();

    archEmulationStopNotification();
    
    dbgDisable();
    dbgPrint();
}

void emulatorSetFrequency(int logFrequency, int* frequency) {
    emuFrequency = (int)(3579545 * pow(2.0, (logFrequency - 50) / 15.0515));

    if (frequency != NULL) {
        *frequency  = emuFrequency;
    }

    boardSetFrequency(emuFrequency);
}

void emulatorSuspend() {
    if (emuState == EMU_RUNNING) {
        emuState = EMU_SUSPENDED;
        do {
            Sleep(10);
        } while (!emuSuspendFlag);
        archSoundSuspend();
        archMidiEnable(0);
    }
}


void emulatorResume() {
    emuSysTime = 0;

    if (emuState == EMU_SUSPENDED) {
        archSoundResume();
        archMidiEnable(1);
        emuState = EMU_RUNNING;
        archUpdateEmuDisplay(0);
    }
}


int emulatorGetCurrentScreenMode()
{
    return lastScreenMode;
}

void emulatorRestart() {
    Machine* machine = machineCreate(properties->emulation.machineName);

    emulatorStop();
    if (machine != NULL) {
        boardSetMachine(machine);
        machineDestroy(machine);
    }
}

void emulatorRestartSound() {
    emulatorSuspend();
    archSoundDestroy();
    archSoundCreate(mixer, 44100, properties->sound.bufSize, properties->sound.stereo ? 2 : 1);
    emulatorResume();
}

void SetColor(int palEntry, UInt32 rgbColor) {
    UInt32 color = videoGetColor(((rgbColor >> 16) & 0xff), ((rgbColor >> 8) & 0xff), rgbColor & 0xff);
    if (palEntry == 0) {
        emuPalette0 = color;
    }
    else {
        emuPalette[palEntry] = color;
    }
    if (emuState == EMU_PAUSED) {
        archUpdateEmuDisplay(0);
    }
}

int emulatorGetCpuOverflow() {
    int overflow = emuTimeOverflow;
    emuTimeOverflow = 0;
    return overflow;
}

void emulatorSetMaxSpeed(int enable) {
    emuMaxSpeed = enable;
}

int  emulatorGetMaxSpeed() {
    return emuMaxSpeed;
}

void emulatorResetMixer() {
    // Reset active indicators in mixer
    mixerIsChannelTypeActive(mixer, MIXER_CHANNEL_MOONSOUND, 1);
    mixerIsChannelTypeActive(mixer, MIXER_CHANNEL_MSXAUDIO, 1);
    mixerIsChannelTypeActive(mixer, MIXER_CHANNEL_MSXMUSIC, 1);
    mixerIsChannelTypeActive(mixer, MIXER_CHANNEL_SCC, 1);
    mixerIsChannelTypeActive(mixer, MIXER_CHANNEL_PCM, 1);
    mixerIsChannelTypeActive(mixer, MIXER_CHANNEL_IO, 1);
}

int emulatorSyncScreen()
{
    int rv = 0;
    emuFrameskipCounter--;
    if (emuFrameskipCounter < 0) {
        rv = archUpdateEmuDisplay(properties->emulation.syncMethod);
        if (rv) {
            emuFrameskipCounter = properties->video.frameSkip;
        }
    }
    return rv;
}

void RefreshScreen(int screenMode) {

    lastScreenMode = screenMode;

    if (emuUseSynchronousUpdate() == P_EMU_SYNCFRAMES) {
        emulatorSyncScreen();
    }
}

static int WaitForSync(int maxSpeed, int breakpointHit) {
    LARGE_INTEGER li1;
    LARGE_INTEGER li2;
    static UInt32 tmp = 0;
    static UInt32 cnt = 0;
    UInt32 sysTime;
    UInt32 diffTime;
    UInt32 syncPeriod;
    static int overflowCount = 0;
    static UInt32 kbdPollCnt = 0;

    emuMaxEmuSpeed = maxSpeed;

    syncPeriod = emulatorGetSyncPeriod();
    QueryPerformanceCounter(&li1);

    emuSuspendFlag = 1;
        
    if (emuSingleStep) {
        debuggerNotifyEmulatorPause();
        emuSingleStep = 0;
        emuState = EMU_PAUSED;
    }

    if (breakpointHit) {
        debuggerNotifyEmulatorPause();
        emuState = EMU_PAUSED;
    }
    
    if (emuState != EMU_RUNNING) {
        archEventSet(emuStartEvent);
        emuSysTime = 0;
    }

    if (((++kbdPollCnt & 0x03) >> syncPeriod) == 0) {
        archPollInput();
    }

    if (emuUseSynchronousUpdate() == P_EMU_SYNCTOVBLANK) {
        overflowCount += emulatorSyncScreen() ? 0 : 1;
        while ((!emuExitFlag && emuState != EMU_RUNNING) || overflowCount > 0) {
            WaitForSingleObject(emuSyncEvent, INFINITE);
            overflowCount--;
        }
    }
    else {
        do {
            WaitForSingleObject(emuSyncEvent, INFINITE);
            if (((emuMaxSpeed || emuMaxEmuSpeed) && !emuExitFlag) || overflowCount > 0) {
                WaitForSingleObject(emuSyncEvent, INFINITE);
            }
            overflowCount = 0;
        } while (!emuExitFlag && emuState != EMU_RUNNING);
    }

    emuSuspendFlag = 0;
    QueryPerformanceCounter(&li2);

    emuTimeIdle  += li2.LowPart - li1.LowPart;
    emuTimeTotal += li2.LowPart - tmp;
    tmp = li2.LowPart;
    
    sysTime = archGetSystemUpTime(1000);
    diffTime = sysTime - emuSysTime;
    emuSysTime = sysTime;
    
    if (emuSingleStep) {
        diffTime = 0;
    }

    if ((++cnt & 0x0f) == 0) {
        emuCalcCpuUsage(NULL);
    }

    overflowCount = emulatorGetCpuOverflow() ? 1 : 0;
    if (diffTime > 50U) {
        overflowCount = 1;
        diffTime = 0;
    }

    if (emuMaxSpeed || emuMaxEmuSpeed) {
        diffTime *= 10;
        if (diffTime > 20 * syncPeriod) {
            diffTime =  20 * syncPeriod;
        }
    }

    emuUsageCurrent += diffTime;

    return emuExitFlag ? -1 : diffTime;
}

