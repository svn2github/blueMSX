/*****************************************************************************
** File:
**      Actions.h
**
** Author:
**      Daniel Vik
**
** Description:
**      Emulator actions
**
** More info:   
**      www.bluemsx.com
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
void actionOptionsShowLanguage();
void actionToolsShowMachineEditor();
void actionToolsShowShorcutEditor();
void actionHelpShowHelp();
void actionHelpShowAbout();
void actionVolumeIncrease();
void actionVolumeDecrease();
void actionPort1SetNone();
void actionPort1SetMouse();
void actionPort1SetNumpad();
void actionPort1SetKeyset();
void actionPort1SetJoystick();
void actionPort2SetNone();
void actionPort2SetMouse();
void actionPort2SetNumpad();
void actionPort2SetKeyset();
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
void actionMenuZoom(int x, int y);
void actionMenuOptions(int x, int y);
void actionMenuHelp(int x, int y);
void actionMenuTools(int x, int y);

void actionToggleCartAutoReset();
void actionToggleDiskAutoResetA();
void actionToggleCasAutoRewind();
void actionToggleSpriteEnable();
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

void actionMuteToggleMaster();
void actionMuteTogglePsg();
void actionMuteTogglePcm();
void actionMuteToggleScc();
void actionMuteToggleKeyboard();
void actionMuteToggleMsxMusic();
void actionMuteToggleMsxAudio();
void actionMuteToggleMoonsound();

void actionSetCartAutoReset(int value);
void actionSetDiskAutoResetA(int value);
void actionSetCasAutoRewind(int value);
void actionSetSpriteEnable(int value);
void actionSetMsxAudioSwitch(int value);
void actionSetFrontSwitch(int value);
void actionSetPauseSwitch(int value);
void actionSetWaveCapture(int value);
void actionSetMouseCapture(int value);
void actionSetFullscreen(int value);
void actionSetCasReadonly(int value);
void actionSetVolumeMute(int value);
void actionSetVolumeStereo(int value);

void actionVolumeSetMaster(int value);
void actionVolumeSetPsg(int value);
void actionVolumeSetPcm(int value);
void actionVolumeSetScc(int value);
void actionVolumeSetKeyboard(int value);
void actionVolumeSetMsxMusic(int value);
void actionVolumeSetMsxAudio(int value);
void actionVolumeSetMoonsound(int value);
void actionPanSetPsg(int value);
void actionPanSetPcm(int value);
void actionPanSetScc(int value);
void actionPanSetKeyboard(int value);
void actionPanSetMsxMusic(int value);
void actionPanSetMsxAudio(int value);
void actionPanSetMoonsound(int value);

void actionRenshaSetLevel(int value);
void actionEmuSpeedSet(int value);

#endif
