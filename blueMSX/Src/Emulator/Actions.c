/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Emulator/Actions.c,v $
**
** $Revision: 1.55 $
**
** $Date: 2005-12-20 00:39:39 $
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
#include "Debugger.h"
#include "FileHistory.h"
#include "LaunchFile.h"
#include "Emulator.h"
#include "InputEvent.h"
#include "VideoManager.h"
#include "VDP.h"

#include "ArchMenu.h"
#include "ArchDialog.h"
#include "ArchFile.h"
#include "ArchNotifications.h"
#include "ArchPrinter.h"
#include "ArchMidi.h"
#include "ArchInput.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


static struct {
    Properties* properties;
    Mixer* mixer;
    int mouseLock;
} state;

static char audioDir[PROP_MAXPATH]  = "";
static char audioPrefix[64]     = "";
static char stateDir[PROP_MAXPATH]  = "";
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


void actionToggleHorizontalStretch() {
    state.properties->video.horizontalStretch = !state.properties->video.horizontalStretch;
    archUpdateEmuDisplayConfig();
}

void actionToggleVerticalStretch() {
    state.properties->video.verticalStretch = !state.properties->video.verticalStretch;
    archUpdateEmuDisplayConfig();
}

void actionToggleScanlinesEnable() {
    state.properties->video.scanlinesEnable = !state.properties->video.scanlinesEnable;
    archUpdateEmuDisplayConfig();
}

void actionToggleDeinterlaceEnable() {
    state.properties->video.deInterlace = !state.properties->video.deInterlace;
    archUpdateEmuDisplayConfig();
}

void actionToggleRfModulatorEnable() {
    state.properties->video.colorSaturationEnable = !state.properties->video.colorSaturationEnable;
    archUpdateEmuDisplayConfig();
}


void actionQuit() {
    archQuit();
}

void actionToggleWaveCapture() {
    if (mixerIsLogging(state.mixer)) {
        mixerStopLog(state.mixer);
    }
    else {
        mixerStartLog(state.mixer, generateSaveFilename(state.properties, audioDir, audioPrefix, ".wav", 2));
    }
    archUpdateMenu(0);
}


void actionLoadState() {
    char* filename;

    emulatorSuspend();
    filename = archFilenameGetOpenState(state.properties);
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
        filename = archFilenameGetSaveState(state.properties);
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
        strcpy(state.properties->filehistory.quicksave, generateSaveFilename(state.properties, stateDir, statePrefix, ".sta", 2));
        boardSaveState(state.properties->filehistory.quicksave);
        emulatorResume();
    }
}

void actionCartInsert1() {
    RomType romType;
    char* filename;

    emulatorSuspend();
    filename = archFilenameGetOpenRom(state.properties, 1, &romType);
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
    filename = archFilenameGetOpenRom(state.properties, 2, &romType);
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

void actionEmuStep() {
    if (emulatorGetState() == EMU_PAUSED) {
        emulatorSetState(EMU_STEP);
    }
}

void actionEmuTogglePause() {
    if (emulatorGetState() == EMU_STOPPED) {
        emulatorStart(NULL);
    }
    else if (emulatorGetState() == EMU_PAUSED) {
        emulatorSetState(EMU_RUNNING);
        debuggerNotifyEmulatorResume();
    }
    else {  
        emulatorSetState(EMU_PAUSED);
        debuggerNotifyEmulatorPause();
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
    filename = archDirnameGetOpenDisk(state.properties, 1);
    if (filename != NULL) {        
        strcpy(state.properties->media.disks[0].directory, filename);
        insertDiskette(state.properties, 0, filename, NULL, 0);
    }
    emulatorResume();
    archUpdateMenu(0);
}

void actionDiskDirInsertB() {
    char* filename;

    emulatorSuspend();
    filename = archDirnameGetOpenDisk(state.properties, 1);
    if (filename != NULL) {        
        strcpy(state.properties->media.disks[1].directory, filename);
        insertDiskette(state.properties, 1, filename, NULL, 0);
    }
    emulatorResume();
    archUpdateMenu(0);
}

void actionDiskInsertA() {
    char* filename;

    emulatorSuspend();
    filename = archFilenameGetOpenDisk(state.properties, 1);
    if (filename != NULL) {        
        insertDiskette(state.properties, 0, filename, NULL, 0);
    }
    emulatorResume();
    archUpdateMenu(0);
}

void actionDiskInsertB() {
    char* filename;

    emulatorSuspend();
    filename = archFilenameGetOpenDisk(state.properties, 2);
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
    if (*state.properties->media.disks[0].fileName) {
        if (*state.properties->media.disks[0].fileNameInZip) {
            strcpy(state.properties->media.disks[0].fileNameInZip, fileGetNext(state.properties->media.disks[0].fileNameInZip, state.properties->media.disks[0].fileName));
            boardChangeDiskette(0, state.properties->media.disks[0].fileName, state.properties->media.disks[0].fileNameInZip);
            updateExtendedDiskName(0, state.properties->media.disks[0].fileName, state.properties->media.disks[0].fileNameInZip);
        }
        else {
            strcpy(state.properties->media.disks[0].fileName, fileGetNext(state.properties->media.disks[0].fileName, NULL));
            boardChangeDiskette(0, state.properties->media.disks[0].fileName, NULL);
            updateExtendedDiskName(0, state.properties->media.disks[0].fileName, state.properties->media.disks[0].fileNameInZip);
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
    archMinimizeMainWindow();
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
    filename = archFilenameGetOpenCas(state.properties);
    if (filename != NULL) {        
        insertCassette(state.properties, 0, filename, NULL, 0);
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
            boardChangeCassette(0, strlen(state.properties->media.tapes[0].fileName) ? state.properties->media.tapes[0].fileName : NULL, 
                                strlen(state.properties->media.tapes[0].fileNameInZip) ? state.properties->media.tapes[0].fileNameInZip : NULL);
        }
        tapeSetCurrentPos(0);
    if (emulatorGetState() != EMU_STOPPED) {
        emulatorResume();
    }
    else {
        boardChangeCassette(0, NULL, NULL);
        tapeSetReadOnly(state.properties->cassette.readOnly);
    }
    archUpdateMenu(0);
}

void actionCasSetPosition() {
    archShowCassettePosDialog();
}

void actionEmuResetSoft() {
    archUpdateMenu(0);
    if (emulatorGetState() == EMU_RUNNING) {
        emulatorSuspend();
        boardReset();
        debuggerNotifyEmulatorReset();
        emulatorResume();
    }
    else {
        emulatorStart(NULL);
    }
    archUpdateMenu(0);
}

void actionEmuResetHard() {
    archUpdateMenu(0);
    emulatorStop();
    emulatorStart(NULL);
    archUpdateMenu(0);
}

void actionEmuResetClean() {
    int i;

    emulatorStop();

    for (i = 0; i < PROP_MAX_CARTS; i++) {
        state.properties->media.carts[i].fileName[0] = 0;
        state.properties->media.carts[i].fileNameInZip[0] = 0;
        state.properties->media.carts[i].type = ROM_UNKNOWN;
        updateExtendedRomName(i, state.properties->media.carts[i].fileName, state.properties->media.carts[i].fileNameInZip);
    }
    
    for (i = 0; i < PROP_MAX_DISKS; i++) {
        state.properties->media.disks[i].fileName[0] = 0;
        state.properties->media.disks[i].fileNameInZip[0] = 0;
        updateExtendedDiskName(i, state.properties->media.disks[i].fileName, state.properties->media.disks[i].fileNameInZip);
    }

    for (i = 0; i < PROP_MAX_TAPES; i++) {
        state.properties->media.tapes[i].fileName[0] = 0;
        state.properties->media.tapes[i].fileNameInZip[0] = 0;
        updateExtendedCasName(i, state.properties->media.tapes[i].fileName, state.properties->media.tapes[i].fileNameInZip);
    }

    emulatorStart(NULL);
    archUpdateMenu(0);
}

void actionScreenCapture() {
    archScreenCapture(SC_NORMAL, NULL);
}

void actionScreenCaptureUnfilteredSmall() {
    archScreenCapture(SC_SMALL, NULL);
}

void actionScreenCaptureUnfilteredLarge() {
    archScreenCapture(SC_LARGE, NULL);
}

void actionTapeRemove(int i) {
    state.properties->media.tapes[i].fileName[0] = 0;
    state.properties->media.tapes[i].fileNameInZip[0] = 0;
    if (emulatorGetState() != EMU_STOPPED) {
        emulatorSuspend();
        boardChangeCassette(i, NULL, NULL);
        emulatorResume();
    }
    updateExtendedCasName(0, state.properties->media.tapes[0].fileName, state.properties->media.tapes[0].fileNameInZip);
    archUpdateMenu(0);
}

static void actionCartRemove(int i) {
    state.properties->media.carts[i].fileName[0] = 0;
    state.properties->media.carts[i].fileNameInZip[0] = 0;
    state.properties->media.carts[i].type = ROM_UNKNOWN;
    updateExtendedRomName(i, state.properties->media.carts[i].fileName, state.properties->media.carts[i].fileNameInZip);
    if (emulatorGetState() != EMU_STOPPED) {
        if (state.properties->cartridge.autoReset) {
            emulatorStop();
            emulatorStart(NULL);
        }
        else {
            emulatorSuspend();
            boardChangeCartridge(i, ROM_UNKNOWN, NULL, NULL);
            emulatorResume();
        }
    }
    archUpdateMenu(0);
}

static void actionDiskRemove(int i) {
    state.properties->media.disks[i].fileName[0] = 0;
    state.properties->media.disks[i].fileNameInZip[0] = 0;
    updateExtendedDiskName(i, state.properties->media.disks[i].fileName, state.properties->media.disks[i].fileNameInZip);
    if (emulatorGetState() != EMU_STOPPED) {
        emulatorSuspend();
        boardChangeDiskette(i, NULL, NULL);
        emulatorResume();
    }
    archUpdateMenu(0);
}

void actionCasRemove() {
    actionTapeRemove(0);
}

void actionDiskRemoveA() {
    actionDiskRemove(0);
}

void actionDiskRemoveB() {
    actionDiskRemove(1);
}

void actionCartRemove1() {
    actionCartRemove(0);
}

void actionCartRemove2() {
    actionCartRemove(1);
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

    if (*state.properties->media.tapes[0].fileName) {
        int type;

        if (emulatorGetState() == EMU_STOPPED) {
            tapeSetReadOnly(1);
            boardChangeCassette(0, strlen(state.properties->media.tapes[0].fileName) ? state.properties->media.tapes[0].fileName : NULL, 
                                strlen(state.properties->media.tapes[0].fileNameInZip) ? state.properties->media.tapes[0].fileNameInZip : NULL);
        }
        else {
            emulatorSuspend();
        }
        
        type = tapeGetFormat();

        filename = archFilenameGetSaveCas(state.properties, &type);

        if (filename != NULL && strlen(filename) != 0) {
            if (type == 1 || type == 2 || type == 3) {
                tapeSave(filename, type);
            }
        }

        if (emulatorGetState() == EMU_STOPPED) {
            boardChangeCassette(0, NULL, NULL);
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

void actionPropShowPerformance() {
    archShowPropertiesDialog(PROP_PERFORMANCE);
}

void actionPropShowSettings() {
    archShowPropertiesDialog(PROP_SETTINGS);
}

void actionPropShowPorts() {
    archShowPropertiesDialog(PROP_PORTS);
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

void actionToolsShowKeyboardEditor() {
    archShowKeyboardEditor();
}

void actionToolsShowMixer() {
    archShowMixer();
}

void actionToolsShowDebugger() {
    archShowDebugger();
}

void actionToolsShowTrainer() {
    archShowTrainer();
}

void actionHelpShowHelp() {
    archShowHelpDialog();
}

void actionHelpShowAbout() {
    archShowAboutDialog();
}

void actionMaximizeWindow() {
    archMaximizeWindow();
}

void actionMinimizeWindow() {
    archMinimizeWindow();
}

void actionCloseWindow() {
    archCloseWindow();
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
    mixerEnableChannelType(state.mixer, channel, newEnable);
}

void actionMuteTogglePcm() {
    int channel = MIXER_CHANNEL_PCM;
    int newEnable = !state.properties->sound.mixerChannel[channel].enable;
    state.properties->sound.mixerChannel[channel].enable = newEnable;
    mixerEnableChannelType(state.mixer, channel, newEnable);
}

void actionMuteToggleIo() {
    int channel = MIXER_CHANNEL_IO;
    int newEnable = !state.properties->sound.mixerChannel[channel].enable;
    state.properties->sound.mixerChannel[channel].enable = newEnable;
    mixerEnableChannelType(state.mixer, channel, newEnable);
}

void actionMuteToggleScc() {
    int channel = MIXER_CHANNEL_SCC;
    int newEnable = !state.properties->sound.mixerChannel[channel].enable;
    state.properties->sound.mixerChannel[channel].enable = newEnable;
    mixerEnableChannelType(state.mixer, channel, newEnable);
}

void actionMuteToggleKeyboard() {
    int channel = MIXER_CHANNEL_KEYBOARD;
    int newEnable = !state.properties->sound.mixerChannel[channel].enable;
    state.properties->sound.mixerChannel[channel].enable = newEnable;
    mixerEnableChannelType(state.mixer, channel, newEnable);
}

void actionMuteToggleMsxMusic() {
    int channel = MIXER_CHANNEL_MSXMUSIC;
    int newEnable = !state.properties->sound.mixerChannel[channel].enable;
    state.properties->sound.mixerChannel[channel].enable = newEnable;
    mixerEnableChannelType(state.mixer, channel, newEnable);
}

void actionMuteToggleMsxAudio() {
    int channel = MIXER_CHANNEL_MSXAUDIO;
    int newEnable = !state.properties->sound.mixerChannel[channel].enable;
    state.properties->sound.mixerChannel[channel].enable = newEnable;
    mixerEnableChannelType(state.mixer, channel, newEnable);
}

void actionMuteToggleMoonsound() {
    int channel = MIXER_CHANNEL_MOONSOUND;
    int newEnable = !state.properties->sound.mixerChannel[channel].enable;
    state.properties->sound.mixerChannel[channel].enable = newEnable;
    mixerEnableChannelType(state.mixer, channel, newEnable);
}

void actionMuteToggleMidi() {
    int channel = MIXER_CHANNEL_MIDI;
    int newEnable = !state.properties->sound.mixerChannel[channel].enable;
    state.properties->sound.mixerChannel[channel].enable = newEnable;
    mixerEnableChannelType(state.mixer, channel, newEnable);
}

void actionPrinterForceFormFeed()
{
    emulatorSuspend();
    archForceFormFeed();
    emulatorResume();
}

void actionVolumeToggleStereo() {
    state.properties->sound.stereo = !state.properties->sound.stereo;

    emulatorRestartSound();
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

void actionMenuPrinter(int x, int y) {
    archShowMenuPrinter(x, y);
}

void actionMenuJoyPort1(int x, int y) {
    archShowMenuJoyPort1(x, y);
}

void actionMenuJoyPort2(int x, int y) {
    archShowMenuJoyPort2(x, y);
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

void actionVideoEnableMon1(int value) {
    videoManagerSetActive(videoManagerGetActive() != 0 ? 0 : -1);
    archUpdateMenu(0);
}

void actionVideoEnableMon2(int value) {
    videoManagerSetActive(videoManagerGetActive() != 1 ? 1 : -1);
    archUpdateMenu(0);
}

void actionVideoEnableMon3(int value) {
    videoManagerSetActive(videoManagerGetActive() != 2 ? 2 : -1);
    archUpdateMenu(0);
}

// Actions controlled by value 0 - 100

void actionVideoSetGamma(int value) {
    state.properties->video.gamma = 50 + value;
    archUpdateEmuDisplayConfig();
}

void actionVideoSetBrightness(int value) {
    state.properties->video.brightness = 50 + value;
    archUpdateEmuDisplayConfig();
}

void actionVideoSetContrast(int value) {
    state.properties->video.contrast = 50 + value;
    archUpdateEmuDisplayConfig();
}

void actionVideoSetSaturation(int value) {
    state.properties->video.saturation = 50 + value;
    archUpdateEmuDisplayConfig();
}

void actionVideoSetScanlines(int value) {
    state.properties->video.scanlinesPct = 100 - value;
    archUpdateEmuDisplayConfig();
}

void actionVideoSetRfModulation(int value) {
    state.properties->video.colorSaturationWidth = (int)ceil((5 - 1) * value / 100.0);
    archUpdateEmuDisplayConfig();
}

void actionVideoSetColorMode(int value) {
    state.properties->video.monType = (int)ceil((P_VIDEO_MONCOUNT - 1) * value / 100.0);
    archUpdateEmuDisplayConfig();
}

void actionVideoSetFilter(int value) {
    state.properties->video.palEmu = (int)ceil((P_VIDEO_PALCOUNT - 1) * value / 100.0);
    archUpdateEmuDisplayConfig();
}

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
    mixerSetChannelTypeVolume(state.mixer, MIXER_CHANNEL_PSG, value);
}

void actionVolumeSetPcm(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_PCM].volume = value;
    mixerSetChannelTypeVolume(state.mixer, MIXER_CHANNEL_PCM, value);
}

void actionVolumeSetIo(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_IO].volume = value;
    mixerSetChannelTypeVolume(state.mixer, MIXER_CHANNEL_IO, value);
}

void actionVolumeSetScc(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_SCC].volume = value;
    mixerSetChannelTypeVolume(state.mixer, MIXER_CHANNEL_SCC, value);
}

void actionVolumeSetMsxMusic(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].volume = value;
    mixerSetChannelTypeVolume(state.mixer, MIXER_CHANNEL_MSXMUSIC, value);
}

void actionVolumeSetMsxAudio(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].volume = value;
    mixerSetChannelTypeVolume(state.mixer, MIXER_CHANNEL_MSXAUDIO, value);
}

void actionVolumeSetMoonsound(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].volume = value;
    mixerSetChannelTypeVolume(state.mixer, MIXER_CHANNEL_MOONSOUND, value);
}

void actionVolumeSetKeyboard(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].volume = value;
    mixerSetChannelTypeVolume(state.mixer, MIXER_CHANNEL_KEYBOARD, value);
}

void actionVolumeSetMidi(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_MIDI].volume = value;
    mixerSetChannelTypeVolume(state.mixer, MIXER_CHANNEL_MIDI, value);
}

void actionPanSetPsg(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_PSG].pan = value;
    mixerSetChannelTypePan(state.mixer, MIXER_CHANNEL_PSG, value);
}

void actionPanSetPcm(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_PCM].pan = value;
    mixerSetChannelTypePan(state.mixer, MIXER_CHANNEL_PCM, value);
}

void actionPanSetIo(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_IO].pan = value;
    mixerSetChannelTypePan(state.mixer, MIXER_CHANNEL_IO, value);
}

void actionPanSetScc(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_SCC].pan = value;
    mixerSetChannelTypePan(state.mixer, MIXER_CHANNEL_SCC, value);
}

void actionPanSetMsxMusic(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_MSXMUSIC].pan = value;
    mixerSetChannelTypePan(state.mixer, MIXER_CHANNEL_MSXMUSIC, value);
}

void actionPanSetMsxAudio(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_MSXAUDIO].pan = value;
    mixerSetChannelTypePan(state.mixer, MIXER_CHANNEL_MSXAUDIO, value);
}

void actionPanSetMoonsound(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_MOONSOUND].pan = value;
    mixerSetChannelTypePan(state.mixer, MIXER_CHANNEL_MOONSOUND, value);
}

void actionPanSetKeyboard(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_KEYBOARD].pan = value;
    mixerSetChannelTypePan(state.mixer, MIXER_CHANNEL_KEYBOARD, value);
}

void actionPanSetMidi(int value) {
    state.properties->sound.mixerChannel[MIXER_CHANNEL_MIDI].pan = value;
    mixerSetChannelTypePan(state.mixer, MIXER_CHANNEL_MIDI, value);
}

void actionRenshaSetLevel(int value) {
    state.properties->joy1.autofire = (int)ceil((11 - 1) * value / 100.0);
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
                                                        audioPrefix, ".wav", 2));
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

void actionKeyPress(int keyCode, int pressed)
{
    if (pressed) {
        inputEventSet(keyCode);
        archKeyboardSetSelectedKey(keyCode);
    }
    else {
        inputEventUnset(keyCode);
    }
}

