/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Theme/ThemeTriggers.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-01-15 23:55:33 $
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
#include "ThemeTriggers.h"
#include "MsxTypes.h"
#include <stdlib.h>
#include <string.h>

#include "Properties.h"
#include "Emulator.h"
#include "Board.h"
#include "Keyboard.h"
#include "Led.h"
#include "Casette.h"
#include "AudioMixer.h"
#include "FileHistory.h"
#include "build_number.h"
#include "version.h"
#include "ArchNotifications.h"

static void createAboutInfo(char* buffer, int length, unsigned int clk)
{
    static char text[4096];
    static int  len = 0;

    if (len == 0) {
        sprintf(text, 
                "                                 "
                "Special thanks to: "
                "Ricardo Bittencourt,  "
                "Rudolf Lechleitner,  "
                "MkII,  "
                "Shimanuki Koshi,  "
                "Roger Filipe,  "
                "Kobayashi Michiko,  "
                "Ulver,  "
                "Nicolas Beyaert,  "
                "SLotman,  "
                "Laurent Halter,  "
                "Fabio Albergaria Dias,  "
                "Glafouk,  "
                "Martijn van Tienen,  "
                "V�ctor Fern�ndez S�nchez,  "
                "William Ouwehand,  "
                "Miikka \"MP83\" Poikela,  "
                "Davide Platania a.k.a. Kruznak,  "
                "Wouter Vermaelen,  "
                "Manuel Bilderbeek,  "
                "Maarten ter Huurne,  "
                "Jussi Pitk�nen,  "
                "Tobias Keizer,  "
                "Hondarer,  "
                "Atarulum,  "
                "Sandy Pleyte,  "
                "Amer Dugmag,  "
                "Alex Wulms,  "
                "BouKiCHi,  "
                "Marat Fayzullin,  "
                "Jarek Burczynski,  "
                "R. Belmont,  "
                "O. Galibert,  "
                "Tatsuyuki Satoh,  "
                "Gilles Vollant"
                "......          ......"
                "and YOU !!!!"
                "                                     ");

        len = strlen(text);
    }

    {
#define SHOW_VERSION_TIME 100
        int pos = clk % (len + SHOW_VERSION_TIME - length);
        if (pos < SHOW_VERSION_TIME) {
            sprintf(buffer, "version %s  build %d", BLUE_MSX_VERSION, BUILD_NUMBER);
        }
        else {
            strncpy(buffer, text + pos - SHOW_VERSION_TIME, length);
        }
    }
    buffer[length] = 0;
}



int themeTriggerEmuStopped() {
    return emulatorGetState() == EMU_STOPPED;
}

int themeTriggerEmuPaused() {
    return emulatorGetState() != EMU_RUNNING && emulatorGetState() != EMU_STOPPED;
}

int themeTriggerEmuRunning() {
    return emulatorGetState() == EMU_RUNNING;
}

int themeTriggerFdcTiming() {
    return boardGetFdcTimingEnable();
}

int themeTriggerCpuTraceEnable() {
    return boardTraceGetEnable();
}

int themeTriggerLedDiskA() {
    return ledGetFdd1(); 
}

int themeTriggerLedDiskB() {
    return ledGetFdd2();
}

int themeTriggerLedCas() {
    return tapeIsBusy();
}

int themeTriggerLedAudioSwitch() {
    return propGetGlobalProperties()->emulation.audioSwitch ? 1 : 0;
}

int themeTriggerLedFrontSwitch() {
    return propGetGlobalProperties()->emulation.frontSwitch ? 1 : 0;
}

int themeTriggerLedPauseSwitch() {
    return propGetGlobalProperties()->emulation.pauseSwitch ? 1 : 0;
}

int themeTriggerLedCaps() {
    return ledGetCapslock();
}

int themeTriggerLedKana() {
    return ledGetKana();
}

int themeTriggerLedTurboR() {
    return ledGetTurboR();
}

int themeTriggerLedPause() {
    return ledGetPause();
}

int themeTriggerLedRecord() {
    return mixerIsLogging(mixerGetGlobalMixer()) ? 1 : 0;
}

int themeTriggerLedRensha() {
    return ledGetRensha();
}

int themeTriggerAudioStereo() {
    return propGetGlobalProperties()->sound.stereo ? 1 : 0;
}

int themeTriggerAudioMaster() {
    return propGetGlobalProperties()->sound.masterEnable ? 1 : 0;
}

int themeTriggerAudioKbd(){
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].enable ? 1 : 0;
}

int themeTriggerAudioMoonsound() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].enable ? 1 : 0;
}

int themeTriggerAudioMsxAudio() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].enable ? 1 : 0;
}

int themeTriggerAudioMsxMusic() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].enable ? 1 : 0;
}

int themeTriggerAudioPsg() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_PSG].enable ? 1 : 0;
}

int themeTriggerAudioScc() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_SCC].enable ? 1 : 0;          
}

int themeTriggerAudioPcm() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_PCM].enable ? 1 : 0;
}

int themeTriggerVolKbdLeft() {
    return mixerGetChannelTypeVolume(mixerGetGlobalMixer(), MIXER_CHANNEL_KEYBOARD, MIXER_CHANNEL_LEFT);
}

int themeTriggerVolKbdRight() {
    return mixerGetChannelTypeVolume(mixerGetGlobalMixer(), MIXER_CHANNEL_KEYBOARD, MIXER_CHANNEL_RIGHT);
}

int themeTriggerVolMoonsoundLeft() {
    return mixerGetChannelTypeVolume(mixerGetGlobalMixer(), MIXER_CHANNEL_MOONSOUND, MIXER_CHANNEL_LEFT);
}

int themeTriggerVolMoonsoundRight() {
    return mixerGetChannelTypeVolume(mixerGetGlobalMixer(), MIXER_CHANNEL_MOONSOUND, MIXER_CHANNEL_RIGHT);
}

int themeTriggerVolMsxAudioLeft() {
    return mixerGetChannelTypeVolume(mixerGetGlobalMixer(), MIXER_CHANNEL_MSXAUDIO, MIXER_CHANNEL_LEFT);
}

int themeTriggerVolMsxAudioRight() {
    return mixerGetChannelTypeVolume(mixerGetGlobalMixer(), MIXER_CHANNEL_MSXAUDIO, MIXER_CHANNEL_RIGHT);
}

int themeTriggerVolMsxMusicLeft() {
    return mixerGetChannelTypeVolume(mixerGetGlobalMixer(), MIXER_CHANNEL_MSXMUSIC, MIXER_CHANNEL_LEFT);
}

int themeTriggerVolMsxMusicRight() {
    return mixerGetChannelTypeVolume(mixerGetGlobalMixer(), MIXER_CHANNEL_MSXMUSIC, MIXER_CHANNEL_RIGHT);
}

int themeTriggerVolPsgLeft() {
    return mixerGetChannelTypeVolume(mixerGetGlobalMixer(), MIXER_CHANNEL_PSG, MIXER_CHANNEL_LEFT);
}

int themeTriggerVolPsgRight() {
    return mixerGetChannelTypeVolume(mixerGetGlobalMixer(), MIXER_CHANNEL_PSG, MIXER_CHANNEL_RIGHT);
}

int themeTriggerVolSccLeft() {
    return mixerGetChannelTypeVolume(mixerGetGlobalMixer(), MIXER_CHANNEL_SCC, MIXER_CHANNEL_LEFT);
}

int themeTriggerVolSccRight() {
    return mixerGetChannelTypeVolume(mixerGetGlobalMixer(), MIXER_CHANNEL_SCC, MIXER_CHANNEL_RIGHT);
}

int themeTriggerVolPcmLeft() {
    return mixerGetChannelTypeVolume(mixerGetGlobalMixer(), MIXER_CHANNEL_PCM, MIXER_CHANNEL_LEFT);
}

int themeTriggerVolPcmRight() {
    return mixerGetChannelTypeVolume(mixerGetGlobalMixer(), MIXER_CHANNEL_PCM, MIXER_CHANNEL_RIGHT);
}

int themeTriggerVolMasterLeft() {
    return mixerGetMasterVolume(mixerGetGlobalMixer(), MIXER_CHANNEL_LEFT);
}

int themeTriggerVolMasterRight() {
    return mixerGetMasterVolume(mixerGetGlobalMixer(), MIXER_CHANNEL_RIGHT);
}

int themeTriggerLevelMaster() {
    return propGetGlobalProperties()->sound.masterVolume;
}

int themeTriggerLevelPsg() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_PSG].volume;
}

int themeTriggerLevelPcm() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_PCM].volume;
}

int themeTriggerLevelScc() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_SCC].volume;
}

int themeTriggerLevelKeyboard() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].volume;
}

int themeTriggerLevelMsxMusic() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].volume;
}

int themeTriggerLevelMsxAudio() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].volume;
}

int themeTriggerLevelMoonsound() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].volume;
}

int themeTriggerPanPsg() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_PSG].pan;
}

int themeTriggerPanPcm() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_PCM].pan;
}

int themeTriggerPanScc() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_SCC].pan;
}

int themeTriggerPanKeyboard() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].pan;
}

int themeTriggerPanMsxMusic() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].pan;
}

int themeTriggerPanMsxAudio() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].pan;
}

int themeTriggerPanMoonsound() {
    return propGetGlobalProperties()->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].pan;
}

int themeTriggerLevelRensha() {
    return 100 * propGetGlobalProperties()->joy1.autofire / 11;
}

int themeTriggerLevelEmuSpeed() {
    return propGetGlobalProperties()->emulation.speed;
}

int themeTriggerPort1None() {
    return propGetGlobalProperties()->joy1.type == P_JOY_NONE ? 1 : 0;
}

int themeTriggerPort1Mouse() {
    return propGetGlobalProperties()->joy1.type == P_JOY_MOUSE ? 1 : 0;
}

int themeTriggerPort1Num() {
    return propGetGlobalProperties()->joy1.type == P_JOY_NUMPAD ? 1 : 0;
}

int themeTriggerPort1Kbd() {
    return propGetGlobalProperties()->joy1.type == P_JOY_KEYSET ? 1 : 0;
}

int themeTriggerPort1Joy() {
    return propGetGlobalProperties()->joy1.type == P_JOY_HW ? 1 : 0;
}

int themeTriggerPort2None() {
    return propGetGlobalProperties()->joy2.type == P_JOY_NONE ? 1 : 0;
}

int themeTriggerPort2Mouse() {
    return propGetGlobalProperties()->joy2.type == P_JOY_MOUSE ? 1 : 0;
}

int themeTriggerPort2Num() {
    return propGetGlobalProperties()->joy2.type == P_JOY_NUMPAD ? 1 : 0;
}

int themeTriggerPort2Kbd() {
    return propGetGlobalProperties()->joy2.type == P_JOY_KEYSET ? 1 : 0;
}

int themeTriggerPort2Joy() {
    return propGetGlobalProperties()->joy2.type == P_JOY_HW ? 1 : 0;
}

int themeTriggerMachineMoonsound() {
    return mixerIsChannelTypeActive(mixerGetGlobalMixer(), MIXER_CHANNEL_MOONSOUND, 0);
}

int themeTriggerMachineMsxAudio() {
    return mixerIsChannelTypeActive(mixerGetGlobalMixer(), MIXER_CHANNEL_MSXAUDIO, 0);
}

int themeTriggerMachineMsxMusic() {
    return mixerIsChannelTypeActive(mixerGetGlobalMixer(), MIXER_CHANNEL_MSXMUSIC, 0);
}

int themeTriggerMachineScc() {
    return mixerIsChannelTypeActive(mixerGetGlobalMixer(), MIXER_CHANNEL_SCC, 0);
}

int themeTriggerMachineRom() {
    return boardUseRom();
}

int themeTriggerMachineMegaRom() {
    return boardUseMegaRom();
}

int themeTriggerMachineMegaRam() {
    return boardUseMegaRam();
}

int themeTriggerMachineFmPac() {
    return boardUseFmPac();
}

int themeTriggerConfDiskRI() {
    return propGetGlobalProperties()->diskdrive.autostartA;
}

int themeTriggerConfCartRI() {
    return propGetGlobalProperties()->cartridge.autoReset;
}

int themeTriggerConfCasRO() {
    return propGetGlobalProperties()->cassette.readOnly;
}

int themeTriggerVideoScanlines() {
    return propGetGlobalProperties()->video.scanlinesEnable;
}

int themeTriggerVideoHstretch() {
    return propGetGlobalProperties()->video.horizontalStretch;
}

int themeTriggerVideoVstretch() {
    return propGetGlobalProperties()->video.verticalStretch;
}

char* themeTriggerVideoScanlinePct() {
    static char buffer[16];
    sprintf(buffer, (propGetGlobalProperties()->video.scanlinesEnable ? "%d%%" : ""), 100 - propGetGlobalProperties()->video.scanlinesPct);
    return buffer;
}

char* themeTriggerScreenMode() {
    static char* txtScreenMode[14] = {
        "SCREEN 0",  "SCREEN 1", "SCREEN 2",  "SCREEN 3",
        "SCREEN 4",  "SCREEN 5", "SCREEN 6",  "SCREEN 7",
        "SCREEN 8",  "SCREEN 9", "SCREEN 10", "SCREEN 11",
        "SCREEN 12", "TEXT80"
    };
    if (emulatorGetState() == EMU_STOPPED) {
        return "";
    }
    return txtScreenMode[emulatorGetCurrentScreenMode()];
}

char* themeTriggerScreenModeShort() {
    static char* txtScreenModeShort[14] = {
        "SCR 0",  "SCR 1", "SCR 2",  "SCR 3",
        "SCR 4",  "SCR 5", "SCR 6",  "SCR 7",
        "SCR 8",  "SCR 9", "SCR 10", "SCR 11",
        "SCR 12", "TXT 80"
    };
    if (emulatorGetState() == EMU_STOPPED) {
        return "";
    }
    return txtScreenModeShort[emulatorGetCurrentScreenMode()];
}

char* themeTriggerMemoryRam() {
    static char buffer[16];
    if (boardGetRamSize() >= 1024) {
        sprintf(buffer, "%dMB", boardGetRamSize() / 1024);
    }
    else {
        sprintf(buffer, "%dkB", boardGetRamSize());
    }
    return buffer;
}

char* themeTriggerMemoryVram() {
    static char buffer[16];
    sprintf(buffer, "%dkB", boardGetVramSize());
    return buffer;
}

char* themeTriggerEmuFrequency() {
    static char buffer[16];
    if (emulatorGetState() == EMU_STOPPED) {
        return "";
    }
    sprintf(buffer, "%d%%", emulatorGetCpuSpeed());
    return buffer;
}

char* themeTriggerFpsString() {
    static char buffer[16];
    int fps;
    
    if (emulatorGetState() == EMU_STOPPED) {
        return "";
    }
    fps = archGetFramesPerSecond();
    if (fps == 59 || fps == 61) fps = 60;
    if (fps == 49 || fps == 51) fps = 50;
    sprintf(buffer, "%2d", fps);
    return buffer;
}

char* themeTriggerCpuString() {
    static char buffer[16];
    if (emulatorGetState() == EMU_STOPPED) {
        return "";
    }
    sprintf(buffer, "%2d.%d%%", emulatorGetCpuUsage() / 10, 
            emulatorGetCpuUsage() % 10);
    return buffer;
}

char* themeTriggerRomMapper1() {
    return propGetGlobalProperties()->cartridge.slotA[0] ? romTypeToString(propGetGlobalProperties()->cartridge.slotAType) : "";
}

char* themeTriggerRomMapper2() {
    return propGetGlobalProperties()->cartridge.slotB[0] ? romTypeToString(propGetGlobalProperties()->cartridge.slotBType) : ""; 
}

char* themeTriggerRomMapper1Short() {
    return propGetGlobalProperties()->cartridge.slotA[0] ? romTypeToShortString(propGetGlobalProperties()->cartridge.slotAType) : "";
}

char* themeTriggerRomMapper2Short() {
    return propGetGlobalProperties()->cartridge.slotB[0] ? romTypeToShortString(propGetGlobalProperties()->cartridge.slotBType) : "";
}

char* themeTriggerMachineName() {
    return propGetGlobalProperties()->emulation.machineName;
}

char* themeTriggerRunningName() {
    return createSaveFileBaseName(propGetGlobalProperties(), 1);
}

char* themeTriggerBuildNumber() {
    static char buffer[16];
    sprintf(buffer, "%d", BUILD_NUMBER);
    return buffer;
}

char* themeTriggerVersion() {
    return BLUE_MSX_VERSION;
}

char* themeTriggerBuildAndVersion() {
    static int aboutCnt = 0;
    static char buffer[128];
    if (emulatorGetState() != EMU_STOPPED) {
        aboutCnt = 0;
    }
    createAboutInfo(buffer, 30, aboutCnt++ / 2);
    return buffer;
}

int themeTriggerKeyPressed(int keyCode) {
    return keyboardGetKeyState(keyCode) || themeTriggerKeyEdit(keyCode);
}

int themeTriggerKeyEdit(int keyCode) {
    return archKeyboardIsKeySelected(keyCode);
}

int themeTriggerKeyConfigured(int keyCode) {
    return !archKeyboardIsKeyConfigured(keyCode);
}

char* themeTriggerLangKbdSelKey() {
    return langKeyconfigSelectedKey();
}

char* themeTriggerLangKbdMappedTo() {
    return langKeyconfigMappedTo();
}

char* themeTriggerLangKbdMapSCheme() {
    return langKeyconfigMappingScheme();
}

char* themeTriggerSelectedKey() {
    return archGetSelectedKey();
}

char* themeTriggerMappedKey() {
    return archGetMappedKey();
}