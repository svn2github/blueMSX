/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Emulator/Actions.c,v $
**
** $Revision: 1.4 $
**
** $Date: 2004-12-13 02:04:47 $
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
#include "Actions.h"
#include "MsxTypes.h"
#include "Switches.h"
#include "AudioMixer.h"
#include "Board.h"
#include "Casette.h"
#include "FileHistory.h"
#include "LaunchFile.h"
#include "Emulator.h"
#include "VDP.h"

#include "ArchMenu.h"
#include "ArchDialog.h"
#include "ArchControls.h"
#include "ArchNotifications.h"

#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <math.h>


static struct {
    Properties* properties;
    Mixer* mixer;
    int mouseLock;
} state;

static char audioDir[MAX_PATH]  = "";
static char audioPrefix[64]     = "";
static char stateDir[MAX_PATH]  = "";
static char statePrefix[64]     = "";

void actionSetAudioCaptureSetDirectory(char* dir, char* prefix)
{
    strcpy(audioDir, dir);
    strcpy(audioPrefix, prefix);
}

void actionSetQuickSaveSetDirectory(char* dir, char* prefix)
{
    strcpy(stateDir, dir);
    strcpy(statePrefix, prefix);
}

void actionInit(Properties* properties, Mixer* mixer)
{
    memset(&state, 0, sizeof(state));

    state.properties = properties;
    state.mixer      = mixer;
}

void actionToggleSpriteEnable() {
    vdpSetSpritesEnable(!vdpGetSpritesEnable());
}

void actionToggleMsxAudioSwitch() {
    state.properties->emulation.audioSwitch = !state.properties->emulation.audioSwitch;
    switchSetAudio(state.properties->emulation.audioSwitch);
}

void actionToggleFrontSwitch() {
    state.properties->emulation.frontSwitch = !state.properties->emulation.frontSwitch;
    switchSetFront(state.properties->emulation.frontSwitch);
}

void actionTogglePauseSwitch() {
    state.properties->emulation.pauseSwitch = !state.properties->emulation.pauseSwitch;
    switchSetPause(state.properties->emulation.pauseSwitch);
}

void actionToggleFdcTiming() {
    state.properties->emulation.enableFdcTiming = !state.properties->emulation.enableFdcTiming;
    boardSetFdcTimingEnable(state.properties->emulation.enableFdcTiming);
}

void actionQuit() {
    archQuit();
}

void actionToggleWaveCapture() {
    if (mixerIsLogging(state.mixer)) {
        mixerStopLog(state.mixer);
    }
    else {
        mixerStartLog(state.mixer, generateSaveFilename(state.properties, audioDir, audioPrefix, ".wav"));
    }
    archUpdateMenu(0);
}


void actionLoadState() {
    char* filename;

    emulatorSuspend();
    filename = archFileOpen(langDlgLoadState(), "CPU state   (*.sta)\0*.sta\0", 
                            state.properties->emulation.statsDefDir, ".sta\0", NULL, NULL, -1);
    if (filename != NULL) {
        emulatorStop();
        emulatorStart(filename);
    }
    else {
        emulatorResume();
    }
    archUpdateMenu(0);
}

void actionSaveState() {
    char* filename;

    if (emulatorGetState() != EMU_STOPPED) {
        emulatorSuspend();
        filename = archFileSave(langDlgSaveState(), "CPU state   (*.sta)\0*.sta\0", 
                                state.properties->emulation.statsDefDir, ".sta\0", NULL);
        if (filename != NULL && strlen(filename) != 0) {
            char *ptr = filename + strlen(filename) - 1;
            while(*ptr != '.' && ptr > filename) {
                ptr--;
            }
            if (ptr == filename) {
                ptr = filename + strlen(filename);
            }

            strcpy(ptr, ".sta");
            boardSaveState(filename);
        }
        emulatorResume();
    }
}

void actionQuickLoadState() {
    if (fileExist(state.properties->filehistory.quicksave, NULL)) {
        emulatorStop();
        emulatorStart(state.properties->filehistory.quicksave);
    }
    archUpdateMenu(0);
}

void actionQuickSaveState() {
    if (emulatorGetState() != EMU_STOPPED) {
        emulatorSuspend();
        strcpy(state.properties->filehistory.quicksave, generateSaveFilename(state.properties, stateDir, statePrefix, ".sta"));
        boardSaveState(state.properties->filehistory.quicksave);
        emulatorResume();
    }
}

void actionCartInsert1() {
    RomType romType;
    char* filename;

    emulatorSuspend();
    filename = archFileRomOpen(langDlgInsertRom1(), 
                               "ROM cartridge   (*.rom, *.mx1, *.mx2, *.zip)\0*.rom; *.mx1; *.mx2; *.zip\0All Files   (*.*)\0*.*\0", 
                               state.properties->cartridge.defDir, ".rom\0.mx1\0.mx2\0.zip\0.*\0",
                               &state.properties->cartridge.slotAFilter, ".rom", &romType);
    if (filename != NULL) {        
        insertCartridge(state.properties, 0, filename, NULL, romType, 0);
    }
    else {
        emulatorResume();
    }
    archUpdateMenu(0);
}

void actionCartInsert2() {
    RomType romType;
    char* filename;

    emulatorSuspend();
    filename = archFileRomOpen(langDlgInsertRom2(), 
                               "ROM cartridge   (*.rom, *.mx1, *.mx2, *.zip)\0*.rom; *.mx1; *.mx2; *.zip\0All Files   (*.*)\0*.*\0", 
                               state.properties->cartridge.defDir, ".rom\0.mx1\0.mx2\0.zip\0.*\0",
                               &state.properties->cartridge.slotBFilter, ".rom", &romType);
    if (filename != NULL) {        
        insertCartridge(state.properties, 1, filename, NULL, romType, 0);
    }
    else {
        emulatorResume();
    }
    archUpdateMenu(0);
}

void actionToggleMouseCapture() {
    state.mouseLock ^= 1;
    archMouseSetForceLock(state.mouseLock);
}

void actionPort1SetNone() {
	state.properties->joy1.type = P_JOY_NONE;
}

void actionPort1SetMouse() {
	state.properties->joy1.type = P_JOY_MOUSE;
}

void actionPort1SetNumpad() {
	state.properties->joy1.type = P_JOY_NUMPAD;
}

void actionPort1SetKeyset() {
	state.properties->joy1.type = P_JOY_KEYSET;
}

void actionPort1SetJoystick() {
	if (archJoystickGetCount()) {
		state.properties->joy1.type = P_JOY_HW;
	}
}

void actionPort2SetNone() {
	state.properties->joy2.type = P_JOY_NONE;
}

void actionPort2SetMouse() {
	state.properties->joy2.type = P_JOY_MOUSE;
}

void actionPort2SetNumpad() {
	state.properties->joy2.type = P_JOY_NUMPAD;
}

void actionPort2SetKeyset() {
	state.properties->joy2.type = P_JOY_KEYSET;
}

void actionPort2SetJoystick() {
	if (archJoystickGetCount()) {
    	state.properties->joy2.type = P_JOY_HW;
    }
}

void actionEmuTogglePause() {
    if (emulatorGetState() == EMU_STOPPED) {
        emulatorStart(NULL);
    }
    else if (emulatorGetState() == EMU_PAUSED) {
        emulatorSetState(EMU_RUNNING);
    }
    else {
        emulatorSetState(EMU_PAUSED);
    }
    archUpdateMenu(0);
}

void actionEmuStop() {
    if (emulatorGetState() != EMU_STOPPED) {
        emulatorStop();
    }
    archUpdateMenu(0);
}

void actionDiskDirInsertA() {
    char* filename;

    emulatorSuspend();
    filename = archDirOpen(langDlgInsertDiskA(), state.properties->diskdrive.slotADir);
    if (filename != NULL) {        
        strcpy(state.properties->diskdrive.slotADir, filename);
        insertDiskette(state.properties, 0, filename, NULL, 0);
    }
    emulatorResume();
    archUpdateMenu(0);
}

void actionDiskDirInsertB() {
    char* filename;

    emulatorSuspend();
    filename = archDirOpen(langDlgInsertDiskB(), state.properties->diskdrive.slotBDir);
    if (filename != NULL) {        
        strcpy(state.properties->diskdrive.slotBDir, filename);
        insertDiskette(state.properties, 1, filename, NULL, 0);
    }
    emulatorResume();
    archUpdateMenu(0);
}

void actionDiskInsertA() {
    char* filename;

    emulatorSuspend();
    filename = archFileOpen(langDlgInsertDiskA(), 
                            "Disk image   (*.dsk, *.di1, *.di2, *.zip)\0*.dsk; *.di1; *.di2; *.zip\0All Files   (*.*)\0*.*\0",
                            state.properties->diskdrive.defDir, ".dsk\0.di1\0.di2\0.zip\0", 
                            &state.properties->diskdrive.slotAFilter, ".dsk", 720 * 1024);
    if (filename != NULL) {        
        insertDiskette(state.properties, 0, filename, NULL, 0);
    }
    emulatorResume();
    archUpdateMenu(0);
}

void actionDiskInsertB() {
    char* filename;

    emulatorSuspend();
    filename = archFileOpen(langDlgInsertDiskB(), 
                            "Disk image   (*.dsk, *.di1, *.di2, *.zip)\0*.dsk; *.di1; *.di2; *.zip\0All Files   (*.*)\0*.*\0",
                            state.properties->diskdrive.defDir, ".dsk\0.di1\0.di2\0.zip\0", 
                            &state.properties->diskdrive.slotBFilter, ".dsk", 720 * 1024);
    if (filename != NULL) {
        
        insertDiskette(state.properties, 1, filename, NULL, 0);
    }
    emulatorResume();
    archUpdateMenu(0);
}

void actionMaxSpeedSet() {
    emulatorSetMaxSpeed(1);
}

void actionMaxSpeedRelease() {
    emulatorSetMaxSpeed(0);
}

void actionDiskQuickChange() {
    if (*state.properties->diskdrive.slotA) {
        if (*state.properties->diskdrive.slotAZip) {
            strcpy(state.properties->diskdrive.slotAZip, fileGetNext(state.properties->diskdrive.slotAZip, state.properties->diskdrive.slotA));
            boardChangeDiskette(0, state.properties->diskdrive.slotA, state.properties->diskdrive.slotAZip);
            updateExtendedDiskName(0, state.properties->diskdrive.slotA, state.properties->diskdrive.slotAZip);
        }
        else {
            strcpy(state.properties->diskdrive.slotA, fileGetNext(state.properties->diskdrive.slotA, NULL));
            boardChangeDiskette(0, state.properties->diskdrive.slotA, NULL);
            updateExtendedDiskName(0, state.properties->diskdrive.slotA, state.properties->diskdrive.slotAZip);
        }
        archDiskQuickChangeNotify();
    }
    archUpdateMenu(0);
}

void actionWindowSizeSmall() {
    if (state.properties->video.size != P_VIDEO_SIZEX1) {
        state.properties->video.size = P_VIDEO_SIZEX1;
        archUpdateWindow();
    }
}

void actionWindowSizeNormal() {
    if (state.properties->video.size != P_VIDEO_SIZEX2) {
        state.properties->video.size = P_VIDEO_SIZEX2;
        archUpdateWindow();
    }
}

void actionWindowSizeFullscreen() {
    if (state.properties->video.size != P_VIDEO_SIZEFULLSCREEN) {
        state.properties->video.size = P_VIDEO_SIZEFULLSCREEN;
        archUpdateWindow();
    }
}

void actionWindowSizeMinimized() {
    archMinimizeWindow();
}

void actionMaxSpeedToggle() {
    emulatorSetMaxSpeed(emulatorGetMaxSpeed() ? 0 : 1);
}

void actionFullscreenToggle() {
    if (state.properties->video.size == P_VIDEO_SIZEFULLSCREEN) {
        if (archGetWindowedSize() == P_VIDEO_SIZEX2) {
            actionWindowSizeNormal();
        }
        else {
            actionWindowSizeSmall();
        }
    }
    else {
        actionWindowSizeFullscreen();
    }
    archUpdateMenu(0);
}

void actionEmuSpeedNormal() {
    state.properties->emulation.speed = 50;
    emulatorSetFrequency(state.properties->emulation.speed, NULL);
}

void actionEmuSpeedDecrease() {
    if (state.properties->emulation.speed > 0) {
        state.properties->emulation.speed--;
        emulatorSetFrequency(state.properties->emulation.speed, NULL);
    }
}

void actionEmuSpeedIncrease() {
    if (state.properties->emulation.speed < 100) {
        state.properties->emulation.speed++;
        emulatorSetFrequency(state.properties->emulation.speed, NULL);
    }
}

void actionCasInsert() {
    char* filename;

    emulatorSuspend();
    filename = archFileOpen(langDlgInsertCas(),
                            "Tape image   (*.cas, *.zip)\0*.cas; *.zip\0All Files   (*.*)\0*.*\0", 
                            state.properties->cassette.defDir, ".cas\0.zip\0.*\0", 
                            &state.properties->cassette.filter, ".cas", 0);
    if (filename != NULL) {        
        insertCassette(state.properties, filename, NULL, 0);
        if (state.properties->cassette.autoRewind) {
            tapeSetCurrentPos(0);
        }
    }
    emulatorResume();
    archUpdateMenu(0);
}

void actionCasRewind() {
    if (emulatorGetState() != EMU_STOPPED) {
            emulatorSuspend();
        }
        else {
            tapeSetReadOnly(1);
            boardChangeCassette(strlen(state.properties->cassette.tape) ? state.properties->cassette.tape : NULL, 
                                strlen(state.properties->cassette.tapeZip) ? state.properties->cassette.tapeZip : NULL);
        }
        tapeSetCurrentPos(0);
    if (emulatorGetState() != EMU_STOPPED) {
        emulatorResume();
    }
    else {
        boardChangeCassette(NULL, NULL);
        tapeSetReadOnly(state.properties->cassette.readOnly);
    }
    archUpdateMenu(0);
}

void actionCasSetPosition() {
    archShowCassettePosDialog();
}

void actionEmuResetSoft() {
    if (emulatorGetState() == EMU_RUNNING) {
        emulatorSuspend();
        boardReset();
        emulatorResume();
    }
    else {
        emulatorStart(NULL);
    }
    archUpdateMenu(0);
}

void actionEmuResetHard() {
    emulatorStop();
    emulatorStart(NULL);
    archUpdateMenu(0);
}

void actionEmuResetClean() {
    emulatorStop();
    state.properties->diskdrive.slotA[0] = 0;
    state.properties->diskdrive.slotAZip[0] = 0;
    state.properties->diskdrive.slotB[0] = 0;
    state.properties->diskdrive.slotBZip[0] = 0;
    updateExtendedDiskName(0, state.properties->diskdrive.slotA, state.properties->diskdrive.slotAZip);
    updateExtendedDiskName(1, state.properties->diskdrive.slotB, state.properties->diskdrive.slotBZip);

    state.properties->cartridge.slotA[0] = 0;
    state.properties->cartridge.slotAZip[0] = 0;
    state.properties->cartridge.slotB[0] = 0;
    state.properties->cartridge.slotBZip[0] = 0;
    state.properties->cartridge.slotAType = ROM_UNKNOWN;
    state.properties->cartridge.slotBType = ROM_UNKNOWN;

    updateExtendedRomName(0, state.properties->cartridge.slotA, state.properties->cartridge.slotAZip);
    updateExtendedRomName(1, state.properties->cartridge.slotB, state.properties->cartridge.slotBZip);

    updateExtendedCasName(state.properties->cassette.tape, state.properties->cassette.tapeZip);

    emulatorStart(NULL);
    archUpdateMenu(0);
}

void actionScreenCapture() {
    archScreenCapture(SC_NORMAL);
}

void actionScreenCaptureUnfilteredSmall() {
    archScreenCapture(SC_SMALL);
}

void actionScreenCaptureUnfilteredLarge() {
    archScreenCapture(SC_LARGE);
}

void actionCasRemove() {
    state.properties->cassette.tape[0] = 0;
    state.properties->cassette.tapeZip[0] = 0;
    if (emulatorGetState() != EMU_STOPPED) {
        emulatorSuspend();
        boardChangeCassette(NULL, NULL);
        emulatorResume();
    }
    updateExtendedCasName(state.properties->cassette.tape, state.properties->cassette.tapeZip);
    archUpdateMenu(0);
}

void actionDiskRemoveA() {
    state.properties->diskdrive.slotA[0] = 0;
    state.properties->diskdrive.slotAZip[0] = 0;
    updateExtendedDiskName(0, state.properties->diskdrive.slotA, state.properties->diskdrive.slotAZip);
    if (emulatorGetState() != EMU_STOPPED) {
        emulatorSuspend();
        boardChangeDiskette(0, NULL, NULL);
        emulatorResume();
    }
    archUpdateMenu(0);
}

void actionDiskRemoveB() {
    state.properties->diskdrive.slotB[0] = 0;
    state.properties->diskdrive.slotBZip[0] = 0;
    updateExtendedDiskName(1, state.properties->diskdrive.slotB, state.properties->diskdrive.slotBZip);
    if (emulatorGetState() != EMU_STOPPED) {
        emulatorSuspend();
        boardChangeDiskette(1, NULL, NULL);
        emulatorResume();
    }
    archUpdateMenu(0);
}

void actionCartRemove1() {
    state.properties->cartridge.slotA[0] = 0;
    state.properties->cartridge.slotAZip[0] = 0;
    state.properties->cartridge.slotAType = ROM_UNKNOWN;
    updateExtendedRomName(0, state.properties->cartridge.slotA, state.properties->cartridge.slotAZip);
    if (emulatorGetState() != EMU_STOPPED) {
        if (state.properties->cartridge.autoReset) {
            emulatorStop();
            emulatorStart(NULL);
        }
        else {
            emulatorSuspend();
            boardChangeCartridge(0, ROM_UNKNOWN, NULL, NULL);
            emulatorResume();
        }
    }
    archUpdateMenu(0);
}

void actionCartRemove2() {
    state.properties->cartridge.slotB[0] = 0;
    state.properties->cartridge.slotBZip[0] = 0;
    updateExtendedRomName(1, state.properties->cartridge.slotB, state.properties->cartridge.slotBZip);
    if (emulatorGetState() != EMU_STOPPED) {
        if (state.properties->cartridge.autoReset) {
            emulatorStop();
            emulatorStart(NULL);
        }
        else {
            emulatorSuspend();
            boardChangeCartridge(1, ROM_UNKNOWN, NULL, NULL);
            emulatorResume();
        }
    }
    archUpdateMenu(0);
}

void actionToggleCartAutoReset() {
    state.properties->cartridge.autoReset ^= 1;
    archUpdateMenu(0);
}

void actionToggleDiskAutoResetA() {
    state.properties->diskdrive.autostartA ^= 1;
    archUpdateMenu(0);
}

void actionCasToggleReadonly() {
    state.properties->cassette.readOnly ^= 1;
    archUpdateMenu(0);
}

void actionToggleCasAutoRewind() {
    state.properties->cassette.autoRewind ^= 1;
    archUpdateMenu(0);
}

void actionCasSave() {
    char* filename;

    if (*state.properties->cassette.tape) {
        int type;

        if (emulatorGetState() == EMU_STOPPED) {
            tapeSetReadOnly(1);
            boardChangeCassette(strlen(state.properties->cassette.tape) ? state.properties->cassette.tape : NULL, 
                                strlen(state.properties->cassette.tapeZip) ? state.properties->cassette.tapeZip : NULL);
        }
        else {
            emulatorSuspend();
        }
        
        type = tapeGetFormat();

        filename = archFileSave(langDlgSaveCassette(), 
                                "Tape Image - fMSX-DOS     (*.cas)\0*.cas\0Tape Image - fMSX98/AT   (*.cas)\0*.cas\0Tape Image - SVI-328         (*.cas)\0*.cas\0", 
                                state.properties->cassette.defDir, ".cas\0", &type);
        if (filename != NULL && strlen(filename) != 0) {
            if (type == 1 || type == 2 || type == 3) {
                tapeSave(filename, type);
            }
        }

        if (emulatorGetState() == EMU_STOPPED) {
            boardChangeCassette(NULL, NULL);
            tapeSetReadOnly(state.properties->cassette.readOnly);
        }
        else {
            emulatorResume();
        }
    }
    archUpdateMenu(0);
}

void actionPropShowEmulation() {
    archShowPropertiesDialog(PROP_EMULATION);
}

void actionPropShowVideo() {
    archShowPropertiesDialog(PROP_VIDEO);
}

void actionPropShowAudio() {
    archShowPropertiesDialog(PROP_SOUND);
}

void actionPropShowControls() {
    archShowPropertiesDialog(PROP_CONTROLS);
}

void actionPropShowPerformance() {
    archShowPropertiesDialog(PROP_PERFORMANCE);
}

void actionPropShowSettings() {
    archShowPropertiesDialog(PROP_SETTINGS);
}

void actionPropShowApearance() {
    archShowPropertiesDialog(PROP_APEARANCE);
}

void actionOptionsShowLanguage() {
    archShowLanguageDialog();
}

void actionToolsShowMachineEditor() {
    archShowMachineEditor();
}

void actionToolsShowShorcutEditor() {
    archShowShortcutsEditor();
}

void actionHelpShowHelp() {
    archShowHelpDialog();
}

void actionHelpShowAbout() {
    archShowAboutDialog();
}

void actionVolumeIncrease() {
    state.properties->sound.masterVolume += 5;
    if (state.properties->sound.masterVolume > 100) {
        state.properties->sound.masterVolume = 100;
    }
    mixerSetMasterVolume(state.mixer, state.properties->sound.masterVolume);
}

void actionVolumeDecrease() {
    state.properties->sound.masterVolume -= 5;
    if (state.properties->sound.masterVolume < 0) {
        state.properties->sound.masterVolume = 0;
    }
    mixerSetMasterVolume(state.mixer, state.properties->sound.masterVolume);
}
 
void actionMuteToggleMaster() {
    state.properties->sound.masterEnable = !state.properties->sound.masterEnable;
    mixerEnableMaster(state.mixer, state.properties->sound.masterEnable);
}

void actionMuteTogglePsg() {
    int channel = MIXER_CHANNEL_PSG;
    int newEnable = !state.properties->sound.mixerChannel[channel].enable;
    state.properties->sound.mixerChannel[channel].enable = newEnable;
    mixerEnableChannel(state.mixer, channel, newEnable);
}

void actionMuteTogglePcm() {
    int channel = MIXER_CHANNEL_PCM;
    int newEnable = !state.properties->sound.mixerChannel[channel].enable;
    state.properties->sound.mixerChannel[channel].enable = newEnable;
    mixerEnableChannel(state.mixer, channel, newEnable);
}

void actionMuteToggleScc() {
    int channel = MIXER_CHANNEL_SCC;
    int newEnable = !state.properties->sound.mixerChannel[channel].enable;
    state.properties->sound.mixerChannel[channel].enable = newEnable;
    mixerEnableChannel(state.mixer, channel, newEnable);
}

void actionMuteToggleKeyboard() {
    int channel = MIXER_CHANNEL_KEYBOARD;
    int newEnable = !state.properties->sound.mixerChannel[channel].enable;
    state.properties->sound.mixerChannel[channel].enable = newEnable;
    mixerEnableChannel(state.mixer, channel, newEnable);
}

void actionMuteToggleMsxMusic() {
    int channel = MIXER_CHANNEL_MSXMUSIC;
    int newEnable = !state.properties->sound.mixerChannel[channel].enable;
    state.properties->sound.mixerChannel[channel].enable = newEnable;
    mixerEnableChannel(state.mixer, channel, newEnable);
}

void actionMuteToggleMsxAudio() {
    int channel = MIXER_CHANNEL_MSXAUDIO;
    int newEnable = !state.properties->sound.mixerChannel[channel].enable;
    state.properties->sound.mixerChannel[channel].enable = newEnable;
    mixerEnableChannel(state.mixer, channel, newEnable);
}
void actionMuteToggleMoonsound() {
    int channel = MIXER_CHANNEL_MOONSOUND;
    int newEnable = !state.properties->sound.mixerChannel[channel].enable;
    state.properties->sound.mixerChannel[channel].enable = newEnable;
    mixerEnableChannel(state.mixer, channel, newEnable);
}

void actionVolumeToggleStereo() {
    state.properties->sound.stereo = !state.properties->sound.stereo;

    emulatorRestartSound();
}

void actionCpuTraceToggle() {
    if (boardTraceGetEnable()) {
        boardTraceDisable();
    }
    else {
        boardTraceEnable("CpuTrace.txt");
    }
}

void actionNextTheme() {
    archThemeSetNext();
}

void actionMenuSpecialCart1(int x, int y) {
    archShowMenuSpecialCart1(x, y);
}

void actionMenuSpecialCart2(int x, int y) {
    archShowMenuSpecialCart2(x, y);
}

void actionMenuReset(int x, int y) {
    archShowMenuReset(x, y);
}

void actionMenuHelp(int x, int y) {
    archShowMenuHelp(x, y);
}

void actionMenuRun(int x, int y) {
    archShowMenuRun(x, y);
}

void actionMenuFile(int x, int y) {
    archShowMenuFile(x, y);
}

void actionMenuCart1(int x, int y) {
    archShowMenuCart1(x, y);
}

void actionMenuCart2(int x, int y) {
    archShowMenuCart2(x, y);
}

void actionMenuDiskA(int x, int y) {
    archShowMenuDiskA(x, y);
}

void actionMenuDiskB(int x, int y) {
    archShowMenuDiskB(x, y);
}

void actionMenuCassette(int x, int y) {
    archShowMenuCassette(x, y);
}

void actionMenuZoom(int x, int y) {
    archShowMenuZoom(x, y);
}

void actionMenuOptions(int x, int y) {
    archShowMenuOptions(x, y);
}

void actionMenuTools(int x, int y) {
    archShowMenuTools(x, y);
}

// Actions controlled by value 0 - 100



void actionEmuSpeedSet(int value) {
    state.properties->emulation.speed = value;
    emulatorSetFrequency(state.properties->emulation.speed, NULL);
}

void actionVolumeSetMaster(int value) {
    state.properties->sound.masterVolume = value;
    mixerSetMasterVolume(state.mixer, value);
}

void actionVolumeSetPsg(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_PSG].volume = value;
    mixerSetChannelVolume(state.mixer, MIXER_CHANNEL_PSG, value);
}

void actionVolumeSetPcm(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_PCM].volume = value;
    mixerSetChannelVolume(state.mixer, MIXER_CHANNEL_PCM, value);
}

void actionVolumeSetScc(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_SCC].volume = value;
    mixerSetChannelVolume(state.mixer, MIXER_CHANNEL_SCC, value);
}

void actionVolumeSetMsxMusic(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].volume = value;
    mixerSetChannelVolume(state.mixer, MIXER_CHANNEL_MSXMUSIC, value);
}

void actionVolumeSetMsxAudio(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].volume = value;
    mixerSetChannelVolume(state.mixer, MIXER_CHANNEL_MSXAUDIO, value);
}

void actionVolumeSetMoonsound(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].volume = value;
    mixerSetChannelVolume(state.mixer, MIXER_CHANNEL_MOONSOUND, value);
}

void actionVolumeSetKeyboard(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].volume = value;
    mixerSetChannelVolume(state.mixer, MIXER_CHANNEL_KEYBOARD, value);
}

void actionPanSetPsg(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_PSG].pan = value;
    mixerSetChannelPan(state.mixer, MIXER_CHANNEL_PSG, value);
}

void actionPanSetPcm(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_PCM].pan = value;
    mixerSetChannelPan(state.mixer, MIXER_CHANNEL_PCM, value);
}

void actionPanSetScc(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_SCC].pan = value;
    mixerSetChannelPan(state.mixer, MIXER_CHANNEL_SCC, value);
}

void actionPanSetMsxMusic(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].pan = value;
    mixerSetChannelPan(state.mixer, MIXER_CHANNEL_MSXMUSIC, value);
}

void actionPanSetMsxAudio(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].pan = value;
    mixerSetChannelPan(state.mixer, MIXER_CHANNEL_MSXAUDIO, value);
}

void actionPanSetMoonsound(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].pan = value;
    mixerSetChannelPan(state.mixer, MIXER_CHANNEL_MOONSOUND, value);
}

void actionPanSetKeyboard(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].pan = value;
    mixerSetChannelPan(state.mixer, MIXER_CHANNEL_KEYBOARD, value);
}

void actionRenshaSetLevel(int value) {
    state.properties->joy1.autofire = 11 * value / 100;
    switchSetRensha(state.properties->joy1.autofire);
}

void actionSetSpriteEnable(int value) {
    vdpSetSpritesEnable(value);
}

void actionSetMsxAudioSwitch(int value) {
    state.properties->emulation.audioSwitch = value ? 1 : 0;
    switchSetAudio(state.properties->emulation.audioSwitch);
}

void actionSetFrontSwitch(int value) {
    state.properties->emulation.frontSwitch = value ? 1 : 0;
    switchSetFront(state.properties->emulation.frontSwitch);
}

void actionSetPauseSwitch(int value) {
    state.properties->emulation.pauseSwitch = value ? 1 : 0;
    switchSetPause(state.properties->emulation.pauseSwitch);
}

void actionSetFdcTiming(int value) {
    state.properties->emulation.enableFdcTiming = value ? 1 : 0;
    boardSetFdcTimingEnable(state.properties->emulation.enableFdcTiming);
}

void actionSetWaveCapture(int value) {
    if (value == 0) {
        mixerStopLog(state.mixer);
    }
    else {
        mixerStartLog(state.mixer, generateSaveFilename(state.properties, 
                                                        audioDir, 
                                                        audioPrefix, ".wav"));
    }
    archUpdateMenu(0);
}

void actionSetMouseCapture(int value) {
    state.mouseLock = value ? 1 : 0;
    archMouseSetForceLock(state.mouseLock);
}

void actionSetFullscreen(int value) {
    if (value == 0 && state.properties->video.size == P_VIDEO_SIZEFULLSCREEN) {
        if (archGetWindowedSize() == P_VIDEO_SIZEX2) {
            actionWindowSizeNormal();
        }
        else {
            actionWindowSizeSmall();
        }
    }
    else if (state.properties->video.size != P_VIDEO_SIZEFULLSCREEN) {
        actionWindowSizeFullscreen();
    }
}

void actionSetCartAutoReset(int value) {
    state.properties->cartridge.autoReset = value ? 1 : 0;
    archUpdateMenu(0);
}

void actionSetDiskAutoResetA(int value) {
    state.properties->diskdrive.autostartA = value ? 1 : 0;
    archUpdateMenu(0);
}

void actionSetCasReadonly(int value) {
    state.properties->cassette.readOnly = value ? 1 : 0;
    archUpdateMenu(0);
}

void actionSetCasAutoRewind(int value) {
    state.properties->cassette.autoRewind = value ? 1 : 0;
    archUpdateMenu(0);
}

void actionSetVolumeMute(int value) {
    int oldEnable = state.properties->sound.masterEnable;
    state.properties->sound.masterEnable = value ? 1 : 0;
    if (oldEnable != state.properties->sound.masterEnable) {
        mixerEnableMaster(state.mixer, state.properties->sound.masterEnable);
    }
}

void actionSetVolumeStereo(int value) {
    int oldStereo = state.properties->sound.stereo;
    state.properties->sound.stereo = value ? 1 : 0;
    if (oldStereo != state.properties->sound.stereo) {
        emulatorRestartSound();
    }
}


