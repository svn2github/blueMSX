/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Emulator/Actions.h,v $
**
** $Revision: 1.18 $
**
** $Date: 2005-07-03 09:17:40 $
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
#ifndef ACTIONS_H
#define ACTIONS_H

#include "Properties.h"
#include "AudioMixer.h"

void actionInit(Properties* properties, Mixer* mixer);
void actionSetAudioCaptureSetDirectory(char* dir, char* prefix);
void actionSetQuickSaveSetDirectory(char* dir, char* prefix);

void actionQuit();
void actionLoadState();
void actionSaveState();
void actionQuickLoadState();
void actionQuickSaveState();
void actionCartInsert1();
void actionCartInsert2();
void actionEmuTogglePause();
void actionEmuStep();
void actionEmuStop();
void actionDiskInsertA();
void actionDiskInsertB();
void actionDiskDirInsertA();
void actionDiskDirInsertB();
void actionMaxSpeedSet();
void actionMaxSpeedRelease();
void actionDiskQuickChange();
void actionWindowSizeSmall();
void actionWindowSizeNormal();
void actionWindowSizeMinimized();
void actionWindowSizeFullscreen();
void actionEmuSpeedNormal();
void actionEmuSpeedDecrease();
void actionEmuSpeedIncrease();
void actionCasInsert();
void actionCasRewind();
void actionCasSetPosition(); 
void actionEmuResetSoft();
void actionEmuResetHard();
void actionEmuResetClean();
void actionScreenCapture();
void actionScreenCaptureUnfilteredSmall();
void actionScreenCaptureUnfilteredLarge();
void actionNextTheme();
void actionCasRemove();
void actionDiskRemoveA();
void actionDiskRemoveB();
void actionCartRemove1();
void actionCartRemove2();
void actionCasSave();
void actionPropShowEmulation();
void actionPropShowVideo();
void actionPropShowAudio();
void actionPropShowControls();
void actionPropShowPerformance();
void actionPropShowSettings();
void actionPropShowApearance();
void actionPropShowPorts();
void actionOptionsShowLanguage();
void actionToolsShowMachineEditor();
void actionToolsShowShorcutEditor();
void actionToolsShowKeyboardEditor();
void actionToolsShowMixer();
void actionToolsShowDebugger();
void actionToolsShowTrainer();
void actionHelpShowHelp();
void actionHelpShowAbout();
void actionVolumeIncrease();
void actionVolumeDecrease();
void actionPort1SetNone();
void actionPort1SetMouse();
void actionPort1SetNumpad();
void actionPort1SetKeyset();
void actionPort1SetTetrisDongle();
void actionPort1SetJoystick();
void actionPort2SetNone();
void actionPort2SetMouse();
void actionPort2SetNumpad();
void actionPort2SetKeyset();
void actionPort2SetTetrisDongle();
void actionPort2SetJoystick();

void actionMenuSpecialCart1(int x, int y);
void actionMenuSpecialCart2(int x, int y);
void actionMenuReset(int x, int y);
void actionMenuRun(int x, int y);
void actionMenuFile(int x, int y);
void actionMenuCart1(int x, int y);
void actionMenuCart2(int x, int y);
void actionMenuDiskA(int x, int y);
void actionMenuDiskB(int x, int y);
void actionMenuCassette(int x, int y);
void actionMenuPrinter(int x, int y);
void actionMenuControlsPort1(int x, int y);
void actionMenuControlsPort2(int x, int y);
void actionMenuZoom(int x, int y);
void actionMenuOptions(int x, int y);
void actionMenuHelp(int x, int y);
void actionMenuTools(int x, int y);

void actionToggleCartAutoReset();
void actionToggleDiskAutoResetA();
void actionToggleCasAutoRewind();
void actionToggleSpriteEnable();
void actionToggleFdcTiming();
void actionToggleMsxAudioSwitch();
void actionToggleFrontSwitch();
void actionTogglePauseSwitch();
void actionToggleWaveCapture();
void actionToggleMouseCapture();
void actionMaxSpeedToggle();
void actionFullscreenToggle();
void actionCasToggleReadonly();
void actionVolumeToggleStereo();
void actionCpuTraceToggle();

void actionToggleHorizontalStretch();
void actionToggleVerticalStretch();
void actionToggleScanlinesEnable();
void actionToggleDeinterlaceEnable();
void actionToggleRfModulatorEnable();

void actionMuteToggleMaster();
void actionMuteTogglePsg();
void actionMuteTogglePcm();
void actionMuteToggleIo();
void actionMuteToggleScc();
void actionMuteToggleKeyboard();
void actionMuteToggleMsxMusic();
void actionMuteToggleMsxAudio();
void actionMuteToggleMoonsound();
void actionMuteToggleMidi();

void actionPrinterForceFormFeed();

void actionSetCartAutoReset(int value);
void actionSetDiskAutoResetA(int value);
void actionSetCasAutoRewind(int value);
void actionSetSpriteEnable(int value);
void actionSetMsxAudioSwitch(int value);
void actionSetFdcTiming(int value);
void actionSetFrontSwitch(int value);
void actionSetPauseSwitch(int value);
void actionSetWaveCapture(int value);
void actionSetMouseCapture(int value);
void actionSetFullscreen(int value);
void actionSetCasReadonly(int value);
void actionSetVolumeMute(int value);
void actionSetVolumeStereo(int value);

void actionVideoSetGamma(int value);
void actionVideoSetBrightness(int value);
void actionVideoSetContrast(int value);
void actionVideoSetSaturation(int value);
void actionVideoSetScanlines(int value);
void actionVideoSetRfModulation(int value);
void actionVideoSetColorMode(int value);
void actionVideoSetFilter(int value);
void actionVideoEnableMon1(int value);
void actionVideoEnableMon2(int value);
void actionVideoEnableMon3(int value);

void actionVolumeSetMaster(int value);
void actionVolumeSetPsg(int value);
void actionVolumeSetPcm(int value);
void actionVolumeSetIo(int value);
void actionVolumeSetIo(int value);
void actionVolumeSetScc(int value);
void actionVolumeSetKeyboard(int value);
void actionVolumeSetMsxMusic(int value);
void actionVolumeSetMsxAudio(int value);
void actionVolumeSetMoonsound(int value);
void actionVolumeSetMidi(int value);
void actionPanSetPsg(int value);
void actionPanSetPcm(int value);
void actionPanSetIo(int value);
void actionPanSetScc(int value);
void actionPanSetKeyboard(int value);
void actionPanSetMsxMusic(int value);
void actionPanSetMsxAudio(int value);
void actionPanSetMoonsound(int value);
void actionPanSetMidi(int value);

void actionRenshaSetLevel(int value);
void actionEmuSpeedSet(int value);

void actionKeyPress(int keyCode, int pressed);

#endif

