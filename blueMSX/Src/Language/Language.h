/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/Language.h,v $
**
** $Revision: 1.16 $
**
** $Date: 2005-01-29 00:28:49 $
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
#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <windows.h>
#include <tchar.h>

typedef enum { 
    EMU_LANG_ENGLISH    = 0, 
    EMU_LANG_SWEDISH    = 1, 
    EMU_LANG_JAPANESE   = 2, 
    EMU_LANG_PORTUGUESE = 3, 
    EMU_LANG_FRENCH     = 4, 
    EMU_LANG_DUTCH      = 5,
    EMU_LANG_SPANISH    = 6,
    EMU_LANG_ITALIAN    = 7,
    EMU_LANG_FINNISH    = 8,
    EMU_LANG_KOREAN     = 9,
    EMU_LANG_COUNT      = 10,
    EMU_LANG_UNKNOWN    = -1 
} EmuLanguageType;

void langInit();

int langSetLanguage(EmuLanguageType languageType);
int langShowDlg(HWND hwnd, int oldLanguage);
EmuLanguageType langFromName(_TCHAR* name);

_TCHAR* langStatusBarStopped();
_TCHAR* langStatusBarPaused();
_TCHAR* langStatusBarRunning();

_TCHAR* langMenuHardReset();
_TCHAR* langMenuSoftReset();

_TCHAR* langMenuCartInsert();
_TCHAR* langMenuCartRemove();
_TCHAR* langMenuCartAutoReset();
_TCHAR* langMenuCartNoRecentFiles();
_TCHAR* langMenuCartSnatcher();
_TCHAR* langMenuCartSdSnatcher();
_TCHAR* langMenuCartSCCMirrored();
_TCHAR* langMenuCartSCCExpanded();
_TCHAR* langMenuCartSCC();
_TCHAR* langMenuCartSCCPlus();
_TCHAR* langMenuCartFMPac();
_TCHAR* langMenuCartPac();
_TCHAR* langMenuCartHBI55();
_TCHAR* langMenuCartSpecial();

_TCHAR* langMenuDiskInsert();
_TCHAR* langMenuDiskDirInsert();
_TCHAR* langMenuDiskEject();
_TCHAR* langMenuDiskAutoStart();
_TCHAR* langMenuDiskNoRecentFiles();

_TCHAR* langMenuCasInsert();
_TCHAR* langMenuCasEject();
_TCHAR* langMenuCasRewindAfterInsert();
_TCHAR* langMenuCasUseReadOnly();
_TCHAR* langMenuCasSaveAs();
_TCHAR* langMenuCasSetPosition();
_TCHAR* langMenuCasRewind();
_TCHAR* langMenuCasNoRecentFiles();

_TCHAR* langMenuZoomNormal();
_TCHAR* langMenuZoomDouble();
_TCHAR* langMenuZoomFullscreen();

_TCHAR* langMenuPropsEmulation();
_TCHAR* langMenuPropsVideo();
_TCHAR* langMenuPropsSound();
_TCHAR* langMenuPropsControls();
_TCHAR* langMenuPropsPerformance();
_TCHAR* langMenuPropsSettings();
_TCHAR* langMenuPropsFile();
_TCHAR* langMenuPropsApearance();
_TCHAR* langMenuPropsLanguage();
_TCHAR* langMenuPropsPorts();

_TCHAR* langMenuVideoSource();
_TCHAR* langMenuVideoSourceDefault();

_TCHAR* langMenuHelpHelp();
_TCHAR* langMenuHelpAbout();

_TCHAR* langMenuFileCart1();
_TCHAR* langMenuFileCart2();
_TCHAR* langMenuFileDiskA();
_TCHAR* langMenuFileDiskB();
_TCHAR* langMenuFileCas();
_TCHAR* langMenuFileLoadState();
_TCHAR* langMenuFileSaveState();
_TCHAR* langMenuFileQLoadState();
_TCHAR* langMenuFileQSaveState();
_TCHAR* langMenuFileCaptureAudio();
_TCHAR* langMenuFileScreenShot();
_TCHAR* langMenuFileExit();

_TCHAR* langMenuRunRun();
_TCHAR* langMenuRunPause();
_TCHAR* langMenuRunStop();
_TCHAR* langMenuRunSoftReset();
_TCHAR* langMenuRunHardReset();
_TCHAR* langMenuRunCleanReset();

_TCHAR* langMenuToolsMachine();
_TCHAR* langMenuToolsShortcuts();
_TCHAR* langMenuToolsKeyboard();

_TCHAR* langMenuFile();
_TCHAR* langMenuRun();
_TCHAR* langMenuWindow();
_TCHAR* langMenuOptions();
_TCHAR* langMenuTools();
_TCHAR* langMenuHelp();

_TCHAR* langErrorTitle();
_TCHAR* langWarningTitle();
_TCHAR* langErrorEnterFullscreen();
_TCHAR* langErrorDirectXFailed();
_TCHAR* langErrorNoRomInZip();
_TCHAR* langErrorNoDskInZip();
_TCHAR* langErrorNoCasInZip();
_TCHAR* langErrorNoHelp();
_TCHAR* langErrorStartEmu();
_TCHAR* langDiscardChanges();
_TCHAR* langOverwriteConfig();

_TCHAR* langTooltipReset();
_TCHAR* langTooltipCart1();
_TCHAR* langTooltipCart2();
_TCHAR* langTooltipDiskA();
_TCHAR* langTooltipDiskB();
_TCHAR* langTooltipCas();
_TCHAR* langTooltipStart();
_TCHAR* langTooltipResume();
_TCHAR* langTooltipPause();
_TCHAR* langTooltipStop();
_TCHAR* langTooltipWindowSize();
_TCHAR* langTooltipProperties();
_TCHAR* langTooltipHelp();

_TCHAR* langDlgMainWindow();
_TCHAR* langDlgLoadRom();
_TCHAR* langDlgLoadDsk();
_TCHAR* langDlgLoadCas();
_TCHAR* langDlgLoadRomDskCas();
_TCHAR* langDlgLoadRomDesc();
_TCHAR* langDlgLoadDskDesc();
_TCHAR* langDlgLoadCasDesc();
_TCHAR* langDlgLoadRomDskCasDesc();
_TCHAR* langDlgLoadState();
_TCHAR* langDlgSaveState();
_TCHAR* langDlgSaveCassette();
_TCHAR* langDlgInsertRom1();
_TCHAR* langDlgInsertRom2();
_TCHAR* langDlgInsertDiskA();
_TCHAR* langDlgInsertDiskB();
_TCHAR* langDlgInsertCas();
_TCHAR* langDlgRomType();

_TCHAR* langDlgOK();
_TCHAR* langDlgOpen();
_TCHAR* langDlgCancel();

_TCHAR* langDlgTapeTitle();
_TCHAR* langDlgTapeFrameText();
_TCHAR* langDlgTapeCurrentPos();
_TCHAR* langDlgTapeSetPosText();
_TCHAR* langDlgTapeCustom();
_TCHAR* langDlgTabPosition();
_TCHAR* langDlgTabType();
_TCHAR* langDlgTabFilename();
_TCHAR* langDlgTapeTotalTime();
_TCHAR* langDlgZipReset();

_TCHAR* langDlgAboutTitle();

_TCHAR* langDlgJoyTitle1();
_TCHAR* langDlgJoyTitle2();
_TCHAR* langDlgJoyUpText();
_TCHAR* langDlgJoyDownText();
_TCHAR* langDlgJoyLeftText();
_TCHAR* langDlgJoyRightText();
_TCHAR* langDlgJoyButton1Text();
_TCHAR* langDlgJoyButton2Text();
_TCHAR* langDlgJoyGB();

_TCHAR* langDlgLangLangText();
_TCHAR* langDlgLangTitle();

_TCHAR* langPropTitle();
_TCHAR* langPropEmulation();
_TCHAR* langPropVideo();
_TCHAR* langPropSound();
_TCHAR* langPropControls();
_TCHAR* langPropPerformance();
_TCHAR* langPropSettings();
_TCHAR* langPropApearance();
_TCHAR* langPropFile();
_TCHAR* langPropPorts();

_TCHAR* langPropEmuGeneralGB();
_TCHAR* langPropEmuFamilyText();
_TCHAR* langPropEmuMemoryGB();
_TCHAR* langPropEmuRamSizeText();
_TCHAR* langPropEmuVramSizeText();
_TCHAR* langPropEmuSpeedGB();
_TCHAR* langPropEmuSpeedText();
_TCHAR* langPropEmuFrontSwitchGB();
_TCHAR* langPropEmuFrontSwitch();
_TCHAR* langPropEmuFdcTiming();
_TCHAR* langPropEmuPauseSwitch();
_TCHAR* langPropEmuAudioSwitch();
_TCHAR* langPropVideoFreqText();
_TCHAR* langPropVideoFreqAuto();
_TCHAR* langPropSndOversampleText();

_TCHAR* langPropMonMonGB();
_TCHAR* langPropMonTypeText();
_TCHAR* langPropMonEmuText();
_TCHAR* langPropVideoYypeText();
_TCHAR* langPropWindowSizeText();
_TCHAR* langPropMonHorizStretch();
_TCHAR* langPropMonVertStretch();
_TCHAR* langPropMonDeInterlace();
_TCHAR* langPropMonBrightness();
_TCHAR* langPropMonContrast();
_TCHAR* langPropMonSaturation();
_TCHAR* langPropMonGamma();
_TCHAR* langPropMonScanlines();
_TCHAR* langPropMonColorGhosting();

_TCHAR* langPropPerfVideoDrvGB();
_TCHAR* langPropPerfVideoDispDrvText();
_TCHAR* langPropPerfFrameSkipText();
_TCHAR* langPropPerfAudioDrvGB();
_TCHAR* langPropPerfAudioDrvText();
_TCHAR* langPropPerfAudioBufSzText();
_TCHAR* langPropPerfEmuGB();
_TCHAR* langPropPerfSyncModeText();
_TCHAR* langPropFullscreenResText();

_TCHAR* langPropSndChipEmuGB();
_TCHAR* langPropSndMixerGB();
_TCHAR* langPropSndMonoText();
_TCHAR* langPropSndStereoText();
_TCHAR* langPropSndMsxMusicText();
_TCHAR* langPropSndMsxAudioText();
_TCHAR* langPropSndMoonsound();
_TCHAR* langPropSndPcm();
_TCHAR* langPropSndMasterText();

_TCHAR* langPropJoyPort1GB();
_TCHAR* langPropJoyPort2GB();
_TCHAR* langPropJoyAutofireText();
_TCHAR* langPropJoyConfigKeyset();
_TCHAR* langPropJoyControlText();
_TCHAR* langPropJoyButtonAText();
_TCHAR* langPropJoyButtonBText();
_TCHAR* langPropJoyButtonText();

_TCHAR* langPropJoyKeysetGB();
_TCHAR* langPropJoyKeyest1();
_TCHAR* langPropJoyKeyest2();

_TCHAR* langPropPortsLptGB();
_TCHAR* langPropPortsComGB();
_TCHAR* langPropPortsLptText();
_TCHAR* langPropPortsCom1Text();

_TCHAR* langPropSetFileHistoryGB();
_TCHAR* langPropSetFileHistorySize();
_TCHAR* langPropSetFileHistoryClear();
_TCHAR* langPropWindowsEnvGB();
_TCHAR* langPropScreenSaverGB();
_TCHAR* langPropScreenSaver();
_TCHAR* langPropFileTypesGB();
_TCHAR* langPropFileTypes();
_TCHAR* langPropDisableWinKeys();
_TCHAR* langPropPriorityBoost();
_TCHAR* langPropUseRegistry();
_TCHAR* langPropClearFileHistory();
_TCHAR* langPropOpenRomGB();
_TCHAR* langPropDefaultRomType();
_TCHAR* langPropGuessRomType();

_TCHAR* langPropSettDefSlotGB();
_TCHAR* langPropSettDefSlots();
_TCHAR* langPropSettDefSlot1();
_TCHAR* langPropSettDefSlot2();
_TCHAR* langPropSettDefDrives();
_TCHAR* langPropSettDefDriveA();
_TCHAR* langPropSettDefDriveB();

_TCHAR* langPropThemeGB();
_TCHAR* langPropTheme();
_TCHAR* langPropThemeClassic();
_TCHAR* langPropThemeBlue();

_TCHAR* langEnumVideoMonColor();
_TCHAR* langEnumVideoMonGrey();
_TCHAR* langEnumVideoMonGreen();
_TCHAR* langEnumVideoMonAmber();

_TCHAR* langEnumVideoTypePAL();
_TCHAR* langEnumVideoTypeNTSC();

_TCHAR* langEnumVideoEmuNone();
_TCHAR* langEnumVideoEmuYc();
_TCHAR* langEnumVideoEmuMonitor();
_TCHAR* langEnumVideoEmuYcBlur();
_TCHAR* langEnumVideoEmuComp();
_TCHAR* langEnumVideoEmuCompBlur();
_TCHAR* langEnumVideoEmuScale2x();
_TCHAR* langEnumVideoEmuHq2x();
_TCHAR* langEnumVideoEmuStreched();

_TCHAR* langEnumVideoSize1x();
_TCHAR* langEnumVideoSize2x();
_TCHAR* langEnumVideoSizeFullscreen();

_TCHAR* langEnumVideoDrvDirectDrawHW();
_TCHAR* langEnumVideoDrvDirectDrawHWSys();
_TCHAR* langEnumVideoDrvDirectDraw();
_TCHAR* langEnumVideoDrvGDI();

_TCHAR* langEnumVideoFrameskip0();
_TCHAR* langEnumVideoFrameskip1();
_TCHAR* langEnumVideoFrameskip2();
_TCHAR* langEnumVideoFrameskip3();
_TCHAR* langEnumVideoFrameskip4();
_TCHAR* langEnumVideoFrameskip5();

_TCHAR* langEnumSoundDrvNone();
_TCHAR* langEnumSoundDrvWMM();
_TCHAR* langEnumSoundDrvDirectX();

_TCHAR* langEnumEmuSync1ms();
_TCHAR* langEnumEmuSyncAuto();

_TCHAR* langEnumControlsJoyNone();
_TCHAR* langEnumControlsJoyNumpad();
_TCHAR* langEnumControlsJoyKeyset();
_TCHAR* langEnumControlsJoyKeysetA();
_TCHAR* langEnumControlsJoyKeysetB();
_TCHAR* langEnumControlsJoyPCjoy1();
_TCHAR* langEnumControlsJoyPCjoy2();
_TCHAR* langEnumControlsJoyMouse();

_TCHAR* langEnumControlsAfOff();
_TCHAR* langEnumControlsAfSlow();
_TCHAR* langEnumControlsAfMedium();
_TCHAR* langEnumControlsAfFast();

_TCHAR* langDlgAboutAbout();
_TCHAR* langDlgAboutVersion();
_TCHAR* langDlgAboutBuildNumber();
_TCHAR* langDlgAboutBuildDate();
_TCHAR* langDlgAboutCreat();
_TCHAR* langDlgAboutDevel();
_TCHAR* langDlgAboutThanks();
_TCHAR* langDlgAboutLisence();

_TCHAR* langDlgConfTitle();
_TCHAR* langDlgSave();
_TCHAR* langDlgSaveAs();
_TCHAR* langDlgRun();
_TCHAR* langDlgClose();
_TCHAR* langDlgConfConfigText();
_TCHAR* langDlgConfSlotLayout();
_TCHAR* langDlgConfMemory();
_TCHAR* langDlgConfChipEmulation();
_TCHAR* langDlgConfChipExtras();

_TCHAR* langDlgSlotLayoutGB();
_TCHAR* langDlgSlotExtSlotGB();
_TCHAR* langDlgBoardGB();
_TCHAR* langDlgBoardText();
_TCHAR* langDlgSlotSlot0();
_TCHAR* langDlgSlotSlot1();
_TCHAR* langDlgSlotSlot2();
_TCHAR* langDlgSlotSlot3();
_TCHAR* langDlgSlotCart1();
_TCHAR* langDlgSlotCart2();
_TCHAR* langDlgSlotPrimary();
_TCHAR* langDlgSlotExpanded();

_TCHAR* langDlgConfSaveTitle();
_TCHAR* langDlgConfSaveText();

_TCHAR* langDlgMemAdd();
_TCHAR* langDlgMemEdit();
_TCHAR* langDlgMemRemove();
_TCHAR* langDlgMemSlot();
_TCHAR* langDlgMemAddress();
_TCHAR* langDlgMemType();
_TCHAR* langDlgMemRomImage();

_TCHAR* langDlgChipVideoGB();
_TCHAR* langDlgChipVideoChip();
_TCHAR* langDlgChipVideoRam();
_TCHAR* langDlgChipSoundGB();

_TCHAR* langDlgCmosGB();
_TCHAR* langDlgCmosEnableText();
_TCHAR* langDlgCmosBatteryText();

_TCHAR* langDlgChipCpuFreqGB();
_TCHAR* langDlgChipZ80FreqText();
_TCHAR* langDlgChipR800FreqText();
_TCHAR* langDlgChipFdcGB();
_TCHAR* langDlgChipFdcNumDrivesText();

_TCHAR* langSlotEditMemTitle();
_TCHAR* langSlotEditMemGB();
_TCHAR* langSlotEditMemType();
_TCHAR* langSlotEditMemFile();
_TCHAR* langSlotEditMemAddress();
_TCHAR* langSlotEditMemSize();
_TCHAR* langSlotEditMemSlot();

_TCHAR* langConfDiscardTitle();
_TCHAR* langConfExitSaveTitle();
_TCHAR* langConfExitSaveText();
_TCHAR* langConfSaveTitle();
_TCHAR* langConfSaveText();

_TCHAR* langDlgConfSaveAsTitle();
_TCHAR* langDlgConfSaveAsMachineName();

_TCHAR* langSlotEditMemInternalRoms();

_TCHAR* langConfSaveAsTitle();
_TCHAR* langConfSaveAsName();

_TCHAR* langShortcutSaveConfig();
_TCHAR* langShortcutOverwriteConfig();
_TCHAR* langShortcutExitConfig();
_TCHAR* langShortcutDiscardConfig();
_TCHAR* langShortcutSaveConfigAs();
_TCHAR* langShortcutConfigName();
_TCHAR* langShortcutNewProfile();
_TCHAR* langShortcutConfigTitle();
_TCHAR* langShortcutAssign();
_TCHAR* langShortcutPressText();
_TCHAR* langShortcutScheme();

_TCHAR* langShortcutCartInsert1();
_TCHAR* langShortcutCartRemove1();
_TCHAR* langShortcutCartInsert2();
_TCHAR* langShortcutCartRemove2();
_TCHAR* langShortcutCartSpecialMenu1();
_TCHAR* langShortcutCartSpecialMenu2();
_TCHAR* langShortcutCartAutoReset();
_TCHAR* langShortcutDiskInsertA();
_TCHAR* langShortcutDiskDirInsertA();
_TCHAR* langShortcutDiskRemoveA();
_TCHAR* langShortcutDiskChangeA();
_TCHAR* langShortcutDiskAutoResetA();
_TCHAR* langShortcutDiskInsertB();
_TCHAR* langShortcutDiskDirInsertB();
_TCHAR* langShortcutDiskRemoveB();
_TCHAR* langShortcutCasInsert();
_TCHAR* langShortcutCasEject();
_TCHAR* langShortcutCasAutorewind();
_TCHAR* langShortcutCasReadOnly();
_TCHAR* langShortcutCasSetPosition();
_TCHAR* langShortcutCasRewind();
_TCHAR* langShortcutCasSave();
_TCHAR* langShortcutCpuStateLoad();
_TCHAR* langShortcutCpuStateSave();
_TCHAR* langShortcutCpuStateQload();
_TCHAR* langShortcutCpuStateQsave();
_TCHAR* langShortcutAudioCapture();
_TCHAR* langShortcutScreenshotOrig();
_TCHAR* langShortcutScreenshotSmall();
_TCHAR* langShortcutScreenshotLarge();
_TCHAR* langShortcutQuit();
_TCHAR* langShortcutRunPause();
_TCHAR* langShortcutStop();
_TCHAR* langShortcutResetHard();
_TCHAR* langShortcutResetSoft();
_TCHAR* langShortcutResetClean();
_TCHAR* langShortcutSizeSmall();
_TCHAR* langShortcutSizeNormal();
_TCHAR* langShortcutSizeMinimized();
_TCHAR* langShortcutSizeFullscreen();
_TCHAR* langShortcutToggleFullscren();
_TCHAR* langShortcutVolumeIncrease();
_TCHAR* langShortcutVolumeDecrease();
_TCHAR* langShortcutVolumeMute();
_TCHAR* langShortcutVolumeStereo();
_TCHAR* langShortcutSwitchMsxAudio();
_TCHAR* langShortcutSwitchFront();
_TCHAR* langShortcutSwitchPause();
_TCHAR* langShortcutToggleMouseLock();
_TCHAR* langShortcutEmuSpeedMax();
_TCHAR* langShortcutEmuSpeedMaxToggle();
_TCHAR* langShortcutEmuSpeedNormal();
_TCHAR* langShortcutEmuSpeedInc();
_TCHAR* langShortcutEmuSpeedDec();
_TCHAR* langShortcutThemeSwitch();
_TCHAR* langShortcutShowEmuProp();
_TCHAR* langShortcutShowVideoProp();
_TCHAR* langShortcutShowAudioProp();
_TCHAR* langShortcutShowCtrlProp();
_TCHAR* langShortcutShowPerfProp();
_TCHAR* langShortcutShowSettProp();
_TCHAR* langShortcutShowApearProp();
_TCHAR* langShortcutShowLanguage();
_TCHAR* langShortcutShowMachines();
_TCHAR* langShortcutShowShortcuts();
_TCHAR* langShortcutShowKeyboard();
_TCHAR* langShortcutShowHelp();
_TCHAR* langShortcutShowAbout();
_TCHAR* langShortcutShowFiles();
_TCHAR* langShortcutToggleSpriteEnable();
_TCHAR* langShortcutToggleFdcTiming();
_TCHAR* langShortcutToggleCpuTrace();

_TCHAR* langKeyconfigSelectedKey();
_TCHAR* langKeyconfigMappedTo();
_TCHAR* langKeyconfigMappingScheme();


#endif

