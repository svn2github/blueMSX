/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Emulator/Properties.c,v $
**
** $Revision: 1.6 $
**
** $Date: 2004-12-24 08:32:29 $
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
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ArchKeyStorage.h"

#include "Properties.h"
#include "Machine.h"
#include "Board.h"


/* Alternative property default settings */
#ifdef PROPERTIES_DEFAULTS_ALT_1

void propInitDefaults(Properties* pProperties) 
{
    int i;
    pProperties->language = EMU_LANG_ENGLISH;
    
    pProperties->settings.disableScreensaver   = 0;
    strcpy(pProperties->settings.themeName, "Classic");

    memset(pProperties->settings.windowPos, 0, sizeof(pProperties->settings.windowPos));

    pProperties->emulation.statsDefDir[0]     = 0;
    pProperties->emulation.shortcutProfile[0] = 0;
    strcpy(pProperties->emulation.machineName, "MSX2 - Brazilian");
    pProperties->emulation.speed             = 50;
    pProperties->emulation.syncMethod        = P_EMU_SYNC1MS;
    pProperties->emulation.vdpSyncMode       = P_VDP_SYNCAUTO;
    pProperties->emulation.enableFdcTiming   = 1;
    pProperties->emulation.frontSwitch       = 0;
    pProperties->emulation.pauseSwitch       = 0;
    pProperties->emulation.audioSwitch       = 0;
    pProperties->emulation.registerFileTypes = 0;
    pProperties->emulation.disableWinKeys    = 0;
    pProperties->emulation.priorityBoost     = 0;
    
    pProperties->video.monType            = P_VIDEO_COLOR;
    pProperties->video.palEmu             = P_VIDEO_PALNONE;
    pProperties->video.size               = P_VIDEO_SIZEX2;
    pProperties->video.driver             = P_VIDEO_DRVDIRECTX_VIDEO;
    pProperties->video.frameSkip          = P_VIDEO_FSKIP0;
    pProperties->video.fullRes            = P_VIDEO_FRES640X480_32;
    pProperties->video.deInterlace        = 1;
    pProperties->video.horizontalStretch  = 0;
    pProperties->video.verticalStretch    = 0;
    pProperties->video.contrast           = 100;
    pProperties->video.brightness         = 100;
    pProperties->video.saturation         = 100;
    pProperties->video.gamma              = 100;
    pProperties->video.scanlinesEnable    = 0;
    pProperties->video.scanlinesPct       = 80;

    pProperties->sound.driver             = P_SOUND_DRVDIRECTX;
    pProperties->sound.frequency          = P_SOUND_FREQ44;
    pProperties->sound.bufSize            = 150;
    pProperties->sound.syncMethod         = P_SOUND_SYNCQADJUST;

    pProperties->sound.stereo = 1;
    pProperties->sound.masterVolume = 100;
    pProperties->sound.masterEnable = 1;
    pProperties->sound.chip.enableYM2413 = 1;
    pProperties->sound.chip.enableY8950 = 1;
    pProperties->sound.chip.enableMoonsound = 1;
    pProperties->sound.chip.moonsoundSRAM = 640;

    pProperties->sound.chip.ym2413Oversampling = 1;
    pProperties->sound.chip.y8950Oversampling = 1;
    pProperties->sound.chip.moonsoundOversampling = 1;

    pProperties->sound.mixerChannel[MIXER_CHANNEL_PSG].enable = 1;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_PSG].pan = 50;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_PSG].volume = 100;

    pProperties->sound.mixerChannel[MIXER_CHANNEL_SCC].enable = 1;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_SCC].pan = 50;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_SCC].volume = 100;

    pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].enable = 1;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].pan = 50;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].volume = 100;

    pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].enable = 1;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].pan = 50;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].volume = 100;

    pProperties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].enable = 1;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].pan = 50;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].volume = 100;

    pProperties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].enable = 1;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].pan = 50;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].volume = 100;

    pProperties->sound.mixerChannel[MIXER_CHANNEL_PCM].enable = 1;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_PCM].pan = 50;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_PCM].volume = 100;
    
    pProperties->joy1.type              = P_JOY_NUMPAD;
    pProperties->joy1.autofire          = P_JOY_AFOFF;
    pProperties->joy1.keyUp             = 0xff;
    pProperties->joy1.keyDown           = 0xff;
    pProperties->joy1.keyLeft           = 0xff;
    pProperties->joy1.keyRight          = 0xff;
    pProperties->joy1.button1           = 0xff;
    pProperties->joy1.button2           = 0xff;
    pProperties->joy1.hwType            = 0;
    pProperties->joy1.hwName[0]         = 0;
    pProperties->joy1.hwIndex           = 0;
    pProperties->joy1.hwButtonA         = 0;
    pProperties->joy1.hwButtonB         = 1;
    
    pProperties->joy2.type              = P_JOY_NONE;
    pProperties->joy2.autofire          = P_JOY_AFOFF;
    pProperties->joy2.keyUp             = 0xff;
    pProperties->joy2.keyDown           = 0xff;
    pProperties->joy2.keyLeft           = 0xff;
    pProperties->joy2.keyRight          = 0xff;
    pProperties->joy2.button1           = 0xff;
    pProperties->joy2.button2           = 0xff;
    pProperties->joy2.hwType            = 0;
    pProperties->joy2.hwName[0]         = 0;
    pProperties->joy2.hwIndex           = 0;
    pProperties->joy2.hwButtonA         = 0;
    pProperties->joy2.hwButtonB         = 1;
    
    pProperties->keyboard.keySet        = P_CHAR_EUROPEAN;
    
    pProperties->cartridge.defaultType  = ROM_UNKNOWN;
    pProperties->cartridge.defDir[0]    = 0;
    pProperties->cartridge.slotA[0]     = 0;
    pProperties->cartridge.slotAType    = ROM_UNKNOWN;
    pProperties->cartridge.slotB[0]     = 0;
    pProperties->cartridge.slotBType    = ROM_UNKNOWN;
    pProperties->cartridge.slotAZip[0]  = 0;
    pProperties->cartridge.slotBZip[0]  = 0;
    pProperties->cartridge.slotAFilter  = 1;
    pProperties->cartridge.slotBFilter  = 1;
    pProperties->cartridge.autoReset    = 1;
    pProperties->cartridge.quickStartDrive = 0;

    pProperties->diskdrive.defDir[0]    = 0;
    pProperties->diskdrive.slotA[0]     = 0;
    pProperties->diskdrive.slotB[0]     = 0;
    pProperties->diskdrive.slotAZip[0]  = 0;
    pProperties->diskdrive.slotBZip[0]  = 0;
    pProperties->diskdrive.slotADir[0]  = 0;
    pProperties->diskdrive.slotBDir[0]  = 0;
    pProperties->diskdrive.slotAFilter  = 1;
    pProperties->diskdrive.slotBFilter  = 1;
    pProperties->diskdrive.autostartA   = 0;
    pProperties->diskdrive.quickStartDrive = 0;
    
    pProperties->cassette.defDir[0]       = 0;
    pProperties->cassette.tape[0]         = 0;
    pProperties->cassette.tapeZip[0]      = 0;
    pProperties->cassette.filter          = 1;
    pProperties->cassette.showCustomFiles = 1;
    pProperties->cassette.readOnly        = 1;
    pProperties->cassette.autoRewind      = 0;

    for (i = 0; i < MAX_HISTORY; i++) {
        pProperties->filehistory.cartridgeA[i][0] = 0;
        pProperties->filehistory.cartridgeTypeA[i] = ROM_UNKNOWN;
        pProperties->filehistory.cartridgeB[i][0] = 0;
        pProperties->filehistory.cartridgeTypeB[i] = ROM_UNKNOWN;
        pProperties->filehistory.diskdriveA[i][0] = 0;
        pProperties->filehistory.diskdriveB[i][0] = 0;
        pProperties->filehistory.cassette[i][0] = 0;
    }

    pProperties->filehistory.quicksave[0] = 0;
    pProperties->filehistory.count        = 10;
}

#else

/* Default property settings */
void propInitDefaults(Properties* pProperties) 
{
    int i;
    pProperties->language                 = EMU_LANG_ENGLISH;

    pProperties->settings.disableScreensaver   = 0;
    if (GetSystemMetrics(SM_CYSCREEN) > 600) {
        strcpy(pProperties->settings.themeName, "DIGIblue V2.1");
    }
    else {
        strcpy(pProperties->settings.themeName, "Classic");
    }
    memset(pProperties->settings.windowPos, 0, sizeof(pProperties->settings.windowPos));

    pProperties->emulation.statsDefDir[0]     = 0;
    pProperties->emulation.shortcutProfile[0] = 0;
    strcpy(pProperties->emulation.machineName, "MSX2");
    pProperties->emulation.speed             = 50;
    pProperties->emulation.syncMethod        = P_EMU_SYNCAUTO;
    pProperties->emulation.vdpSyncMode       = P_VDP_SYNCAUTO;
    pProperties->emulation.enableFdcTiming   = 1;
    pProperties->emulation.frontSwitch       = 0;
    pProperties->emulation.pauseSwitch       = 0;
    pProperties->emulation.audioSwitch       = 0;
    pProperties->emulation.registerFileTypes = 0;
    pProperties->emulation.disableWinKeys    = 0;
    pProperties->emulation.priorityBoost     = 0;

    pProperties->video.monType            = P_VIDEO_COLOR;
    pProperties->video.palEmu             = P_VIDEO_PALNYC;
    pProperties->video.size               = P_VIDEO_SIZEX2;
    pProperties->video.driver             = P_VIDEO_DRVDIRECTX_VIDEO;
    pProperties->video.frameSkip          = P_VIDEO_FSKIP0;
    pProperties->video.fullRes            = P_VIDEO_FRES640X480_32;
    pProperties->video.deInterlace        = 1;
    pProperties->video.horizontalStretch  = 1;
    pProperties->video.verticalStretch    = 0;
    pProperties->video.contrast           = 100;
    pProperties->video.brightness         = 100;
    pProperties->video.saturation         = 100;
    pProperties->video.gamma              = 100;
    pProperties->video.scanlinesEnable    = 0;
    pProperties->video.scanlinesPct       = 80;

    pProperties->sound.driver           = P_SOUND_DRVDIRECTX;
    pProperties->sound.frequency        = P_SOUND_FREQ44;
    pProperties->sound.bufSize          = 100;
    pProperties->sound.syncMethod       = P_SOUND_SYNCQADJUST;

    pProperties->sound.stereo = 1;
    pProperties->sound.masterVolume = 75;
    pProperties->sound.masterEnable = 1;
    pProperties->sound.chip.enableYM2413 = 1;
    pProperties->sound.chip.enableY8950 = 1;
    pProperties->sound.chip.enableMoonsound = 1;
    pProperties->sound.chip.moonsoundSRAM = 640;
    
    pProperties->sound.chip.ym2413Oversampling = 1;
    pProperties->sound.chip.y8950Oversampling = 1;
    pProperties->sound.chip.moonsoundOversampling = 1;

    pProperties->sound.mixerChannel[MIXER_CHANNEL_PSG].enable = 1;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_PSG].pan = 42;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_PSG].volume = 100;

    pProperties->sound.mixerChannel[MIXER_CHANNEL_SCC].enable = 1;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_SCC].pan = 58;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_SCC].volume = 100;

    pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].enable = 1;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].pan = 58;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].volume = 95;

    pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].enable = 1;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].pan = 50;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].volume = 95;

    pProperties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].enable = 1;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].pan = 50;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].volume = 95;

    pProperties->sound.mixerChannel[MIXER_CHANNEL_PCM].enable = 1;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_PCM].pan = 48;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_PCM].volume = 95;

    pProperties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].enable = 1;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].pan = 54;
    pProperties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].volume = 65;
    
    pProperties->joy1.type              = P_JOY_NONE;
    pProperties->joy1.autofire          = P_JOY_AFOFF;
    pProperties->joy1.keyUp             = 0xff;
    pProperties->joy1.keyDown           = 0xff;
    pProperties->joy1.keyLeft           = 0xff;
    pProperties->joy1.keyRight          = 0xff;
    pProperties->joy1.button1           = 0xff;
    pProperties->joy1.button2           = 0xff;
    pProperties->joy1.hwType            = 0;
    pProperties->joy1.hwName[0]         = 0;
    pProperties->joy1.hwIndex           = 0;
    pProperties->joy1.hwButtonA         = 0;
    pProperties->joy1.hwButtonB         = 1;
    
    pProperties->joy2.type              = P_JOY_NONE;
    pProperties->joy2.autofire          = P_JOY_AFOFF;
    pProperties->joy2.keyUp             = 0xff;
    pProperties->joy2.keyDown           = 0xff;
    pProperties->joy2.keyLeft           = 0xff;
    pProperties->joy2.keyRight          = 0xff;
    pProperties->joy2.button1           = 0xff;
    pProperties->joy2.button2           = 0xff;
    pProperties->joy2.hwType            = 0;
    pProperties->joy2.hwName[0]         = 0;
    pProperties->joy2.hwIndex           = 0;
    pProperties->joy2.hwButtonA         = 0;
    pProperties->joy2.hwButtonB         = 1;
    
    pProperties->keyboard.keySet        = P_CHAR_EUROPEAN;
    
    pProperties->cartridge.defaultType  = ROM_UNKNOWN;
    pProperties->cartridge.defDir[0]    = 0;
    pProperties->cartridge.slotA[0]     = 0;
    pProperties->cartridge.slotAType    = ROM_UNKNOWN;
    pProperties->cartridge.slotB[0]     = 0;
    pProperties->cartridge.slotBType    = ROM_UNKNOWN;
    pProperties->cartridge.slotAZip[0]  = 0;
    pProperties->cartridge.slotBZip[0]  = 0;
    pProperties->cartridge.autoReset    = 1;
    pProperties->cartridge.quickStartDrive = 0;

    
    pProperties->diskdrive.defDir[0]    = 0;
    pProperties->diskdrive.slotA[0]     = 0;
    pProperties->diskdrive.slotB[0]     = 0;
    pProperties->diskdrive.slotAZip[0]  = 0;
    pProperties->diskdrive.slotBZip[0]  = 0;
    pProperties->diskdrive.slotADir[0]  = 0;
    pProperties->diskdrive.slotBDir[0]  = 0;
    pProperties->diskdrive.autostartA   = 0;
    pProperties->diskdrive.quickStartDrive = 0;


    pProperties->cassette.defDir[0]       = 0;
    pProperties->cassette.tape[0]         = 0;
    pProperties->cassette.tapeZip[0]      = 0;
    pProperties->cassette.showCustomFiles = 1;
    pProperties->cassette.readOnly        = 1;
    pProperties->cassette.autoRewind      = 0;

    for (i = 0; i < MAX_HISTORY; i++) {
        pProperties->filehistory.cartridgeA[i][0] = 0;
        pProperties->filehistory.cartridgeTypeA[i] = ROM_UNKNOWN;
        pProperties->filehistory.cartridgeB[i][0] = 0;
        pProperties->filehistory.cartridgeTypeB[i] = ROM_UNKNOWN;
        pProperties->filehistory.diskdriveA[i][0] = 0;
        pProperties->filehistory.diskdriveB[i][0] = 0;
        pProperties->filehistory.cassette[i][0] = 0;
    }

    pProperties->filehistory.quicksave[0] = 0;
    pProperties->filehistory.count        = 10;
}

#endif

// propLoadDefault loads registry settings that can not be reset
static void propLoadDefault(Properties* pProperties) 
{
    getIntValue("DisableScreensaver", (long*)&pProperties->settings.disableScreensaver);
    getIntValue("RegisterTypes", (long*)&pProperties->emulation.registerFileTypes);
    getIntValue("DisableWinKeys", (long*)&pProperties->emulation.disableWinKeys);
}

static void propLoad(Properties* pProperties) 
{
    int i;
    getIntValue("EmuLanguage", (long*)&pProperties->language);

    getIntValue("DisableScreensaver", (long*)&pProperties->settings.disableScreensaver);
    getStrValue("ThemeName20", (char*)pProperties->settings.themeName);

    getStrValue("StateDefDir", (char*)pProperties->emulation.statsDefDir);
    getStrValue("MachineName", (char*)pProperties->emulation.machineName);
    getStrValue("ShortcutProfile", (char*)pProperties->emulation.shortcutProfile);
    getIntValue("EmulationSpeed", (long*)&pProperties->emulation.speed);
    getIntValue("EmulationSyncMethod", (long*)&pProperties->emulation.syncMethod);
    getIntValue("VdpSyncMode", (long*)&pProperties->emulation.vdpSyncMode);
    
    getIntValue("EnableFdcTiming", (long*)&pProperties->emulation.enableFdcTiming);
    getIntValue("FrontSwitch", (long*)&pProperties->emulation.frontSwitch);
    getIntValue("PauseSwitch", (long*)&pProperties->emulation.pauseSwitch);
    getIntValue("AudioSwitch", (long*)&pProperties->emulation.audioSwitch);
    getIntValue("RegisterTypes", (long*)&pProperties->emulation.registerFileTypes);
    getIntValue("DisableWinKeys", (long*)&pProperties->emulation.disableWinKeys);
    getIntValue("PriorityBoost", (long*)&pProperties->emulation.priorityBoost);
    
    getIntValue("Monitor", (long*)&pProperties->video.monType);
    getIntValue("VideoEmu", (long*)&pProperties->video.palEmu);
    getIntValue("VideoSize", (long*)&pProperties->video.size);
    getIntValue("Video Drvr", (long*)&pProperties->video.driver);
    getIntValue("FrameSkip", (long*)&pProperties->video.frameSkip);
    getIntValue("FullRes", (long*)&pProperties->video.fullRes);
    getIntValue("DeInterlace", (long*)&pProperties->video.deInterlace);
    getIntValue("HorizontalStretch", (long*)&pProperties->video.horizontalStretch);
    getIntValue("VerticalStretch", (long*)&pProperties->video.verticalStretch);
    getIntValue("VideoContrast", (long*)&pProperties->video.contrast);
    getIntValue("VideoBrightness", (long*)&pProperties->video.brightness);
    getIntValue("VideoSaturation", (long*)&pProperties->video.saturation);
    getIntValue("VideoGamma", (long*)&pProperties->video.gamma);
    getIntValue("ScanlinesEnable", (long*)&pProperties->video.scanlinesEnable);
    getIntValue("ScanlinesPct", (long*)&pProperties->video.scanlinesPct);

    getIntValue("Sound-Out", (long*)&pProperties->sound.driver);
    getIntValue("Frequency", (long*)&pProperties->sound.frequency);
    getIntValue("SoundBufferSize", (long*)&pProperties->sound.bufSize);
    getIntValue("SyncMethod", (long*)&pProperties->sound.syncMethod);

    getIntValue("StereoMono", (long*)&pProperties->sound.stereo);
    getIntValue("MasterVolume", (long*)&pProperties->sound.masterVolume);
    getIntValue("MasterEnable", (long*)&pProperties->sound.masterEnable);
    getIntValue("EnableMSXMusic", (long*)&pProperties->sound.chip.enableYM2413);
    getIntValue("EnableMSXAudio", (long*)&pProperties->sound.chip.enableY8950);
    getIntValue("EnableMoonsound", (long*)&pProperties->sound.chip.enableMoonsound);
    getIntValue("MoonsoundSRAMsize", (long*)&pProperties->sound.chip.moonsoundSRAM);
    getIntValue("YM2413Oversampling", (long*)&pProperties->sound.chip.ym2413Oversampling);
    getIntValue("Y8950Oversampling", (long*)&pProperties->sound.chip.y8950Oversampling);
    getIntValue("MoonsoundOversampling", (long*)&pProperties->sound.chip.moonsoundOversampling);
    
    getIntValue("PSGEnable", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_PSG].enable);
    getIntValue("PSGPAN", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_PSG].pan);
    getIntValue("PSGVOL", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_PSG].volume);
    getIntValue("SCCEnable", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_SCC].enable);
    getIntValue("SCCPAN", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_SCC].pan);
    getIntValue("SCCVOL", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_SCC].volume);
    getIntValue("MSXMUSICEnable", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].enable);
    getIntValue("MSXMUSICPAN", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].pan);
    getIntValue("MSXMUSICVOL", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].volume);
    getIntValue("MSXAUDIOEnable", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].enable);
    getIntValue("MSXAUDIOPAN", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].pan);
    getIntValue("MSXAUDIOVOL", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].volume);
    getIntValue("KEYBOARDEnable", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].enable);
    getIntValue("KEYBOARDPAN", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].pan);
    getIntValue("KEYBOARDVOL", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].volume);
    getIntValue("MOONSOUNDEnable", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].enable);
    getIntValue("MOONSOUNDPAN", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].pan);
    getIntValue("MOONSOUNDVOL", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].volume);
    getIntValue("PCMEnable", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_PCM].enable);
    getIntValue("PCMPAN", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_PCM].pan);
    getIntValue("PCMVOL", (long*)&pProperties->sound.mixerChannel[MIXER_CHANNEL_PCM].volume);
    
    getIntValue("Joy1Control", (long*)&pProperties->joy1.type);
    getIntValue("JoyAutoFire", (long*)&pProperties->joy1.autofire);
    getIntValue("JoyKeyUp", (long*)&pProperties->joy1.keyUp);
    getIntValue("JoyKeyDown", (long*)&pProperties->joy1.keyDown);
    getIntValue("JoyKeyLeft", (long*)&pProperties->joy1.keyLeft);
    getIntValue("JoyKeyRight", (long*)&pProperties->joy1.keyRight);
    getIntValue("JoyButton1", (long*)&pProperties->joy1.button1);
    getIntValue("JoyButton2", (long*)&pProperties->joy1.button2);
    getIntValue("JoyHwType", (long*)&pProperties->joy1.hwType);
    getStrValue("JoyHwName", (char*)pProperties->joy1.hwName);
    getIntValue("JoyHwIndex", (long*)&pProperties->joy1.hwIndex);
    getIntValue("JoyHwButton1", (long*)&pProperties->joy1.hwButtonA);
    getIntValue("JoyHwButton2", (long*)&pProperties->joy1.hwButtonB);
    
    getIntValue("Joy2Control", (long*)&pProperties->joy2.type);
    getIntValue("Joy2AutoFire", (long*)&pProperties->joy2.autofire);
    getIntValue("Joy2KeyUp", (long*)&pProperties->joy2.keyUp);
    getIntValue("Joy2KeyDown", (long*)&pProperties->joy2.keyDown);
    getIntValue("Joy2KeyLeft", (long*)&pProperties->joy2.keyLeft);
    getIntValue("Joy2KeyRight", (long*)&pProperties->joy2.keyRight);
    getIntValue("Joy2Button1", (long*)&pProperties->joy2.button1);
    getIntValue("Joy2Button2", (long*)&pProperties->joy2.button2);
    getIntValue("Joy2HwType", (long*)&pProperties->joy2.hwType);
    getStrValue("Joy2HwName", (char*)pProperties->joy2.hwName);
    getIntValue("Joy2HwIndex", (long*)&pProperties->joy2.hwIndex);
    getIntValue("Joy2HwButton1", (long*)&pProperties->joy2.hwButtonA);
    getIntValue("Joy2HwButton2", (long*)&pProperties->joy2.hwButtonB);
    
    getIntValue("KeyBoardKeySet", (long*)&pProperties->keyboard.keySet);
    
    getIntValue("CartDefaultType", (long*)&pProperties->cartridge.defaultType);
    getStrValue("CartDefDir", (char*)pProperties->cartridge.defDir);
    getStrValue("CartSlotA", (char*)pProperties->cartridge.slotA);
    getIntValue("CartSlotAType", (long*)&pProperties->cartridge.slotAType);
    getStrValue("CartSlotB", (char*)pProperties->cartridge.slotB);
    getIntValue("CartSlotBType", (long*)&pProperties->cartridge.slotBType);
    getStrValue("CartSlotA-ZIP", (char*)pProperties->cartridge.slotAZip);
    getStrValue("CartSlotB-ZIP", (char*)pProperties->cartridge.slotBZip);
    getIntValue("CartSlotA-Filter", (long*)&pProperties->cartridge.slotAFilter);
    getIntValue("CartSlotB-Filter", (long*)&pProperties->cartridge.slotBFilter);
    getIntValue("CartAutoReset", (long*)&pProperties->cartridge.autoReset);
    getIntValue("CartQuickStartUnit", (long*)&pProperties->cartridge.quickStartDrive);

    getStrValue("DriveDefDir", (char*)pProperties->diskdrive.defDir);
    getStrValue("DriveSlotA", (char*)pProperties->diskdrive.slotA);
    getStrValue("DriveSlotB", (char*)pProperties->diskdrive.slotB);
    getStrValue("DriveSlotA-ZIP", (char*)pProperties->diskdrive.slotAZip);
    getStrValue("DriveSlotB-ZIP", (char*)pProperties->diskdrive.slotBZip);
    getStrValue("DriveSlotA-Dir", (char*)pProperties->diskdrive.slotADir);
    getStrValue("DriveSlotB-Dir", (char*)pProperties->diskdrive.slotBDir);
    getIntValue("DriveSlotA-Filter", (long*)&pProperties->diskdrive.slotAFilter);
    getIntValue("DriveSlotB-Filter", (long*)&pProperties->diskdrive.slotBFilter);
    getIntValue("DriveAutoStart", (long*)&pProperties->diskdrive.autostartA);
    getIntValue("DriveQuickStartUnit", (long*)&pProperties->diskdrive.quickStartDrive);

    getStrValue("CasseteDefDir", (char*)pProperties->cassette.defDir);
    getStrValue("Cassete", (char*)pProperties->cassette.tape);
    getStrValue("Cassete-ZIP", (char*)pProperties->cassette.tapeZip);
    getIntValue("Cassete-Filter", (long*)&pProperties->cassette.filter);
    getIntValue("CasseteShowCustom", (long*)&pProperties->cassette.showCustomFiles);
    getIntValue("CasseteShowCustom", (long*)&pProperties->cassette.readOnly);
    getIntValue("CasseteAutoRewind", (long*)&pProperties->cassette.autoRewind);
    
    for (i = 0; i < MAX_HISTORY; i++) {
        char str[32];
        sprintf(str, "CartA-History%x",i);
        getStrValue(str, (char*)pProperties->filehistory.cartridgeA[i]);
        sprintf(str, "CartTypeA-History%x",i);
        getIntValue(str, (long*)&pProperties->filehistory.cartridgeTypeA[i]);
        sprintf(str, "CartB-History%x",i);
        getStrValue(str, (char*)pProperties->filehistory.cartridgeB[i]);
        sprintf(str, "CartTypeB-History%x",i);
        getIntValue(str, (long*)&pProperties->filehistory.cartridgeTypeB[i]);
        sprintf(str, "DiskDriveA-History%x",i);
        getStrValue(str, (char*)pProperties->filehistory.diskdriveA[i]);
        sprintf(str, "DiskDriveB-History%x",i);
        getStrValue(str, (char*)pProperties->filehistory.diskdriveB[i]);
        sprintf(str, "Cassete-History%x",i);
        getStrValue(str, (char*)pProperties->filehistory.cassette[i]);
    }

    getStrValue("QuickSave-History", (char*)pProperties->filehistory.quicksave);

    getIntValue("History-Count", (long*)&pProperties->filehistory.count);

    for (i = 0; i < DLG_MAX_ID; i++) {
        char str[32];
        sprintf(str, "WindowPosLeft%x",i);
        getIntValue(str, (long*)&pProperties->settings.windowPos[i].left);
        sprintf(str, "WindowPosTop%x",i);
        getIntValue(str, (long*)&pProperties->settings.windowPos[i].top);
        sprintf(str, "WindowPosRight%x",i);
        getIntValue(str, (long*)&pProperties->settings.windowPos[i].right);
        sprintf(str, "WindowPosBottom%x",i);
        getIntValue(str, (long*)&pProperties->settings.windowPos[i].bottom);
    }
}

void propSave(Properties* pProperties) 
{
    int i;
    setIntValue("EmuLanguage", pProperties->language);

    setIntValue("DisableScreensaver",   pProperties->settings.disableScreensaver);
    setStrValue("ThemeName20", (char*)pProperties->settings.themeName);

    setStrValue("StateDefDir", (char*)pProperties->emulation.statsDefDir);
    setStrValue("MachineName", (char*)pProperties->emulation.machineName);
    setStrValue("ShortcutProfile", (char*)pProperties->emulation.shortcutProfile);
    setIntValue("EmulationSpeed", pProperties->emulation.speed);
    setIntValue("EmulationSyncMethod", pProperties->emulation.syncMethod);
    setIntValue("VdpSyncMode", pProperties->emulation.vdpSyncMode);
    setIntValue("EnableFdcTiming", pProperties->emulation.enableFdcTiming);
    setIntValue("FrontSwitch", pProperties->emulation.frontSwitch);
    setIntValue("PauseSwitch", pProperties->emulation.pauseSwitch);
    setIntValue("AudioSwitch", pProperties->emulation.audioSwitch);
    setIntValue("RegisterTypes", pProperties->emulation.registerFileTypes);
    setIntValue("DisableWinKeys", pProperties->emulation.disableWinKeys);
    setIntValue("PriorityBoost", pProperties->emulation.priorityBoost);

    setIntValue("Monitor", pProperties->video.monType);
    setIntValue("VideoEmu", pProperties->video.palEmu);
    setIntValue("VideoSize", pProperties->video.size);
    setIntValue("Video Drvr", pProperties->video.driver);
    setIntValue("FrameSkip", pProperties->video.frameSkip);
    setIntValue("FullRes", pProperties->video.fullRes);
    setIntValue("DeInterlace", pProperties->video.deInterlace);
    setIntValue("HorizontalStretch", pProperties->video.horizontalStretch);
    setIntValue("VerticalStretch", pProperties->video.verticalStretch);
    setIntValue("VideoContrast", pProperties->video.contrast);
    setIntValue("VideoBrightness", pProperties->video.brightness);
    setIntValue("VideoSaturation", pProperties->video.saturation);
    setIntValue("VideoGamma", pProperties->video.gamma);
    setIntValue("ScanlinesEnable", pProperties->video.scanlinesEnable);
    setIntValue("ScanlinesPct", pProperties->video.scanlinesPct);

    setIntValue("Sound-Out", pProperties->sound.driver);
    setIntValue("Frequency", pProperties->sound.frequency);
    setIntValue("SoundBufferSize", pProperties->sound.bufSize);
    setIntValue("SyncMethod", pProperties->sound.syncMethod);

    setIntValue("StereoMono", pProperties->sound.stereo);
    setIntValue("MasterVolume", pProperties->sound.masterVolume);
    setIntValue("MasterEnable", pProperties->sound.masterEnable);
    setIntValue("EnableMSXAudio", pProperties->sound.chip.enableY8950);
    setIntValue("EnableMSXMusic", pProperties->sound.chip.enableYM2413);
    setIntValue("EnableMoonsound", pProperties->sound.chip.enableMoonsound);
    setIntValue("MoonsoundSRAMsize", pProperties->sound.chip.moonsoundSRAM);
    setIntValue("YM2413Oversampling", pProperties->sound.chip.ym2413Oversampling);
    setIntValue("Y8950Oversampling", pProperties->sound.chip.y8950Oversampling);
    setIntValue("MoonsoundOversampling", pProperties->sound.chip.moonsoundOversampling);
    
    setIntValue("PSGEnable", pProperties->sound.mixerChannel[MIXER_CHANNEL_PSG].enable);
    setIntValue("PSGPAN", pProperties->sound.mixerChannel[MIXER_CHANNEL_PSG].pan);
    setIntValue("PSGVOL", pProperties->sound.mixerChannel[MIXER_CHANNEL_PSG].volume);
    setIntValue("SCCEnable", pProperties->sound.mixerChannel[MIXER_CHANNEL_SCC].enable);
    setIntValue("SCCPAN", pProperties->sound.mixerChannel[MIXER_CHANNEL_SCC].pan);
    setIntValue("SCCVOL", pProperties->sound.mixerChannel[MIXER_CHANNEL_SCC].volume);
    setIntValue("MSXMUSICEnable", pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].enable);
    setIntValue("MSXMUSICPAN", pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].pan);
    setIntValue("MSXMUSICVOL", pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].volume);
    setIntValue("MSXAUDIOEnable", pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].enable);
    setIntValue("MSXAUDIOPAN", pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].pan);
    setIntValue("MSXAUDIOVOL", pProperties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].volume);
    setIntValue("KEYBOARDEnable", pProperties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].enable);
    setIntValue("KEYBOARDPAN", pProperties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].pan);
    setIntValue("KEYBOARDVOL", pProperties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].volume);
    setIntValue("MOONSOUNDEnable", pProperties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].enable);
    setIntValue("MOONSOUNDPAN", pProperties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].pan);
    setIntValue("MOONSOUNDVOL", pProperties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].volume);
    setIntValue("PCMEnable", pProperties->sound.mixerChannel[MIXER_CHANNEL_PCM].enable);
    setIntValue("PCMPAN", pProperties->sound.mixerChannel[MIXER_CHANNEL_PCM].pan);
    setIntValue("PCMVOL", pProperties->sound.mixerChannel[MIXER_CHANNEL_PCM].volume);

    setIntValue("Joy1Control", pProperties->joy1.type);
    setIntValue("JoyAutoFire", pProperties->joy1.autofire);
    setIntValue("JoyKeyUp", pProperties->joy1.keyUp);
    setIntValue("JoyKeyDown", pProperties->joy1.keyDown);
    setIntValue("JoyKeyLeft", pProperties->joy1.keyLeft);
    setIntValue("JoyKeyRight", pProperties->joy1.keyRight);
    setIntValue("JoyButton1", pProperties->joy1.button1);
    setIntValue("JoyButton2", pProperties->joy1.button2);
    setIntValue("JoyHwType", pProperties->joy1.hwType);
    setStrValue("JoyHwName", (char*)pProperties->joy1.hwName);
    setIntValue("JoyHwIndex", pProperties->joy1.hwIndex);
    setIntValue("JoyHwButton1", pProperties->joy1.hwButtonA);
    setIntValue("JoyHwButton2", pProperties->joy1.hwButtonB);

    setIntValue("Joy2Control", pProperties->joy2.type);
    setIntValue("Joy2AutoFire", pProperties->joy2.autofire);
    setIntValue("Joy2KeyUp", pProperties->joy2.keyUp);
    setIntValue("Joy2KeyDown", pProperties->joy2.keyDown);
    setIntValue("Joy2KeyLeft", pProperties->joy2.keyLeft);
    setIntValue("Joy2KeyRight", pProperties->joy2.keyRight);
    setIntValue("Joy2Button1", pProperties->joy2.button1);
    setIntValue("Joy2Button2", pProperties->joy2.button2);
    setIntValue("Joy2HwType", pProperties->joy2.hwType);
    setStrValue("Joy2HwName", (char*)pProperties->joy2.hwName);
    setIntValue("Joy2HwIndex", pProperties->joy2.hwIndex);
    setIntValue("Joy2HwButton1", pProperties->joy2.hwButtonA);
    setIntValue("Joy2HwButton2", pProperties->joy2.hwButtonB);
    
    setIntValue("KeyBoardKeySet", pProperties->keyboard.keySet);
    
    setIntValue("CartDefaultType", pProperties->cartridge.defaultType);
    setStrValue("CartDefDir", (char*)pProperties->cartridge.defDir);
    setStrValue("CartSlotA", (char*)pProperties->cartridge.slotA);
    setIntValue("CartSlotAType", pProperties->cartridge.slotAType);
    setStrValue("CartSlotB", (char*)pProperties->cartridge.slotB);
    setIntValue("CartSlotBType", pProperties->cartridge.slotBType);
    setStrValue("CartSlotA-ZIP", (char*)pProperties->cartridge.slotAZip);
    setStrValue("CartSlotB-ZIP", (char*)pProperties->cartridge.slotBZip);
    setIntValue("CartSlotA-Filter", pProperties->cartridge.slotAFilter);
    setIntValue("CartSlotB-Filter", pProperties->cartridge.slotBFilter);
    setIntValue("CartAutoReset", pProperties->cartridge.autoReset);
    setIntValue("CartQuickStartUnit", pProperties->cartridge.quickStartDrive);

    setStrValue("DriveDefDir", (char*)pProperties->diskdrive.defDir);
    setStrValue("DriveSlotA", (char*)pProperties->diskdrive.slotA);
    setStrValue("DriveSlotB", (char*)pProperties->diskdrive.slotB);
    setStrValue("DriveSlotA-ZIP", (char*)pProperties->diskdrive.slotAZip);
    setStrValue("DriveSlotB-ZIP", (char*)pProperties->diskdrive.slotBZip);
    setStrValue("DriveSlotA-Dir", (char*)pProperties->diskdrive.slotADir);
    setStrValue("DriveSlotB-Dir", (char*)pProperties->diskdrive.slotBDir);
    setIntValue("DriveSlotA-Filter", pProperties->diskdrive.slotAFilter);
    setIntValue("DriveSlotB-Filter", pProperties->diskdrive.slotBFilter);
    setIntValue("DriveAutoStart", pProperties->diskdrive.autostartA);
    setIntValue("DriveQuickStartUnit", pProperties->diskdrive.quickStartDrive);

    setStrValue("CasseteDefDir", (char*)pProperties->cassette.defDir);
    setStrValue("Cassete", (char*)pProperties->cassette.tape);
    setStrValue("Cassete-ZIP", (char*)pProperties->cassette.tapeZip);
    setIntValue("Cassete-Filter", pProperties->cassette.filter);
    setIntValue("CasseteShowCustom", pProperties->cassette.showCustomFiles);
    setIntValue("CasseteShowCustom", pProperties->cassette.readOnly);
    setIntValue("CasseteAutoRewind", pProperties->cassette.autoRewind);

    for (i = 0; i < MAX_HISTORY; i++) {
        char str[32];
        sprintf(str, "CartA-History%x",i);
        setStrValue(str, (char*)pProperties->filehistory.cartridgeA[i]);
        sprintf(str, "CartTypeA-History%x",i);
        setIntValue(str, pProperties->filehistory.cartridgeTypeA[i]);
        sprintf(str, "CartB-History%x",i);
        setStrValue(str, (char*)pProperties->filehistory.cartridgeB[i]);
        sprintf(str, "CartTypeB-History%x",i);
        setIntValue(str, pProperties->filehistory.cartridgeTypeB[i]);
        sprintf(str, "DiskDriveA-History%x",i);
        setStrValue(str, (char*)pProperties->filehistory.diskdriveA[i]);
        sprintf(str, "DiskDriveB-History%x",i);
        setStrValue(str, (char*)pProperties->filehistory.diskdriveB[i]);
        sprintf(str, "Cassete-History%x",i);
        setStrValue(str, (char*)pProperties->filehistory.cassette[i]);
    }

    setStrValue("QuickSave-History", (char*)pProperties->filehistory.quicksave);
    
    setIntValue("History-Count", pProperties->filehistory.count);

    for (i = 0; i < DLG_MAX_ID; i++) {
        char str[32];
        sprintf(str, "WindowPosLeft%x",i);
        setIntValue(str, pProperties->settings.windowPos[i].left);
        sprintf(str, "WindowPosTop%x",i);
        setIntValue(str, pProperties->settings.windowPos[i].top);
        sprintf(str, "WindowPosRight%x",i);
        setIntValue(str, pProperties->settings.windowPos[i].right);
        sprintf(str, "WindowPosBottom%x",i);
        setIntValue(str, pProperties->settings.windowPos[i].bottom);
    }
}

Properties* propCreate(int useDefault) 
{
    Properties* pProperties;

    pProperties = malloc(sizeof(Properties));
    pProperties->joy1.id = 1;
    pProperties->joy2.id = 2;
    propInitDefaults(pProperties);

    if (!useDefault) {
        propLoad(pProperties);
    }
    else {
        propLoadDefault(pProperties);
    }

    // Verify machine name
    {
        char** machineNames = machineGetAvailable(1);
        
        while (*machineNames != NULL) {
            if (0 == strcmp(*machineNames, pProperties->emulation.machineName)) {
                break;
            }
            machineNames++;
        }

        if (*machineNames == NULL) {
            char** machineNames = machineGetAvailable(1);
            int foundMSX2 = 0;

            if (*machineNames != NULL) {
                strcpy(pProperties->emulation.machineName, *machineNames);
            }

            while (*machineNames != NULL) {
                if (0 == strcmp(*machineNames, "MSX2")) {
                    strcpy(pProperties->emulation.machineName, *machineNames);
                    foundMSX2 = 1;
                }
                if (!foundMSX2 && 0 == strncmp(*machineNames, "MSX2", 4)) {
                    strcpy(pProperties->emulation.machineName, *machineNames);
                    foundMSX2 = 1;
                }
                machineNames++;
            }
        }
    }

    return pProperties;
}


void propDestroy(Properties* pProperties) {
    propSave(pProperties);

    free(pProperties);
}

 
