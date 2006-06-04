/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/Language.h,v $
**
** $Revision: 1.56 $
**
** $Date: 2006-06-04 19:23:17 $
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
    EMU_LANG_ENGLISH     = 0, 
    EMU_LANG_SWEDISH     = 1, 
    EMU_LANG_JAPANESE    = 2, 
    EMU_LANG_PORTUGUESE  = 3, 
    EMU_LANG_FRENCH      = 4, 
    EMU_LANG_DUTCH       = 5,
    EMU_LANG_SPANISH     = 6,
    EMU_LANG_ITALIAN     = 7,
    EMU_LANG_FINNISH     = 8,
    EMU_LANG_KOREAN      = 9,
    EMU_LANG_GERMAN      = 10,
    EMU_LANG_POLISH      = 11,
    EMU_LANG_CHINESESIMP = 12,
    EMU_LANG_CHINESETRAD = 13,
    EMU_LANG_COUNT       = 14,
    EMU_LANG_UNKNOWN     = -1 
} EmuLanguageType;

void langInit();

int langSetLanguage(EmuLanguageType languageType);
int langShowDlg(HWND hwnd, int oldLanguage);
EmuLanguageType langFromName(_TCHAR* name);


//----------------------
// Generic lines
//----------------------

_TCHAR* langTextDevice();
_TCHAR* langTextFilename();
_TCHAR* langTextFile();
_TCHAR* langTextNone();
_TCHAR* langTextUnknown();


//----------------------
// Warning and Error lines
//----------------------

_TCHAR* langWarningTitle();
_TCHAR* langWarningDiscardChanges();
_TCHAR* langWarningOverwriteFile();
_TCHAR* langErrorTitle();
_TCHAR* langErrorEnterFullscreen();
_TCHAR* langErrorDirectXFailed();
_TCHAR* langErrorNoRomInZip();
_TCHAR* langErrorNoDskInZip();
_TCHAR* langErrorNoCasInZip();
_TCHAR* langErrorNoHelp();
_TCHAR* langErrorStartEmu();
_TCHAR* langErrorPortableReadonly();


//----------------------
// File related lines
//----------------------

_TCHAR* langFileRom();
_TCHAR* langFileAll();
_TCHAR* langFileCpuState();
_TCHAR* langFileDisk();
_TCHAR* langFileCas();


//----------------------
// Menu related lines
//----------------------

_TCHAR* langMenuNoRecentFiles();
_TCHAR* langMenuInsert();
_TCHAR* langMenuEject();

_TCHAR* langMenuCartGameReader();
_TCHAR* langMenuCartIde();
_TCHAR* langMenuCartBeerIde();
_TCHAR* langMenuCartGIde();
_TCHAR* langMenuCartSunriseIde();
_TCHAR* langMenuCartSCC();
_TCHAR* langMenuCartSCCPlus();
_TCHAR* langMenuCartFMPac();
_TCHAR* langMenuCartPac();
_TCHAR* langMenuCartHBI55();
_TCHAR* langMenuCartInsertSpecial();
_TCHAR* langMenuCartExternalRam();
_TCHAR* langMenuCartMegaRam();

_TCHAR* langMenuDiskDirInsert();
_TCHAR* langMenuDiskInsertNew();
_TCHAR* langMenuDiskAutoStart();
_TCHAR* langMenuCartAutoReset();

_TCHAR* langMenuCasRewindAfterInsert();
_TCHAR* langMenuCasUseReadOnly();
_TCHAR* langMenuCasSaveAs();
_TCHAR* langMenuCasSetPosition();
_TCHAR* langMenuCasRewind();

_TCHAR* langMenuPrnFormfeed();

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
_TCHAR* langMenuPropsLanguage();
_TCHAR* langMenuPropsPorts();

_TCHAR* langMenuVideoSource();
_TCHAR* langMenuVideoSourceDefault();
_TCHAR* langMenuVideoChipAutodetect();
_TCHAR* langMenuVideoInSource();
_TCHAR* langMenuVideoInBitmap();

_TCHAR* langMenuHelpHelp();
_TCHAR* langMenuHelpAbout();

_TCHAR* langMenuFileCart();
_TCHAR* langMenuFileDisk();
_TCHAR* langMenuFileCas();
_TCHAR* langMenuFilePrn();
_TCHAR* langMenuFileLoadState();
_TCHAR* langMenuFileSaveState();
_TCHAR* langMenuFileQLoadState();
_TCHAR* langMenuFileQSaveState();
_TCHAR* langMenuFileCaptureAudio();
_TCHAR* langMenuFileScreenShot();
_TCHAR* langMenuFileExit();
_TCHAR* langMenuFileHarddisk();
_TCHAR* langMenuFileHarddiskNoPresent();

_TCHAR* langMenuRunRun();
_TCHAR* langMenuRunPause();
_TCHAR* langMenuRunStop();
_TCHAR* langMenuRunSoftReset();
_TCHAR* langMenuRunHardReset();
_TCHAR* langMenuRunCleanReset();

_TCHAR* langMenuToolsMachine();
_TCHAR* langMenuToolsShortcuts();
_TCHAR* langMenuToolsKeyboard();
_TCHAR* langMenuToolsMixer();

_TCHAR* langMenuFile();
_TCHAR* langMenuRun();
_TCHAR* langMenuWindow();
_TCHAR* langMenuOptions();
_TCHAR* langMenuTools();
_TCHAR* langMenuHelp();


//----------------------
// Dialog related lines
//----------------------

_TCHAR* langDlgOK();
_TCHAR* langDlgOpen();
_TCHAR* langDlgCancel();
_TCHAR* langDlgSave();
_TCHAR* langDlgSaveAs();
_TCHAR* langDlgRun();
_TCHAR* langDlgClose();

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
_TCHAR* langDlgInsertHarddisk();
_TCHAR* langDlgInsertCas();
_TCHAR* langDlgRomType();

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

_TCHAR* langDlgLangLangText();
_TCHAR* langDlgLangTitle();

_TCHAR* langDlgAboutAbout();
_TCHAR* langDlgAboutVersion();
_TCHAR* langDlgAboutBuildNumber();
_TCHAR* langDlgAboutBuildDate();
_TCHAR* langDlgAboutCreat();
_TCHAR* langDlgAboutDevel();
_TCHAR* langDlgAboutThanks();
_TCHAR* langDlgAboutLisence();

_TCHAR* langDlgSavePreview();
_TCHAR* langDlgSaveDate();


//----------------------
// Properties related lines
//----------------------

_TCHAR* langPropTitle();
_TCHAR* langPropEmulation();
_TCHAR* langPropVideo();
_TCHAR* langPropSound();
_TCHAR* langPropControls();
_TCHAR* langPropPerformance();
_TCHAR* langPropSettings();
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
_TCHAR* langPropSndMidiInGB();
_TCHAR* langPropSndMidiOutGB();

_TCHAR* langPropMonMonGB();
_TCHAR* langPropMonTypeText();
_TCHAR* langPropMonEmuText();
_TCHAR* langPropVideoTypeText();
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
_TCHAR* langPropMonEffectsGB();

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
_TCHAR* langPropSndMsxMusic();
_TCHAR* langPropSndMsxAudio();
_TCHAR* langPropSndMoonsound();
_TCHAR* langPropSndMt32ToGm();

_TCHAR* langPropPortsLptGB();
_TCHAR* langPropPortsComGB();
_TCHAR* langPropPortsLptText();
_TCHAR* langPropPortsCom1Text();
_TCHAR* langPropPortsNone();
_TCHAR* langPropPortsSimplCovox();
_TCHAR* langPropPortsFile();
_TCHAR* langPropPortsComFile();
_TCHAR* langPropPortsOpenLogFile();
_TCHAR* langPropPortsEmulateMsxPrn();

_TCHAR* langPropSetFileHistoryGB();
_TCHAR* langPropSetFileHistorySize();
_TCHAR* langPropSetFileHistoryClear();
_TCHAR* langPropWindowsEnvGB();
_TCHAR* langPropScreenSaver();
_TCHAR* langPropFileTypes();
_TCHAR* langPropDisableWinKeys();
_TCHAR* langPropPriorityBoost();
_TCHAR* langPropScreenshotPng();
_TCHAR* langPropClearFileHistory();
_TCHAR* langPropOpenRomGB();
_TCHAR* langPropDefaultRomType();
_TCHAR* langPropGuessRomType();

_TCHAR* langPropSettDefSlotGB();
_TCHAR* langPropSettDefSlots();
_TCHAR* langPropSettDefSlot();
_TCHAR* langPropSettDefDrives();
_TCHAR* langPropSettDefDrive();

_TCHAR* langPropThemeGB();
_TCHAR* langPropTheme();


//----------------------
// Dropdown related lines
//----------------------

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
_TCHAR* langEnumEmuSyncNone();
_TCHAR* langEnumEmuSyncVblank();

_TCHAR* langEnumControlsJoyNone();
_TCHAR* langEnumControlsJoyTetrisDongle();
_TCHAR* langEnumControlsJoyMagicKeyDongle();
_TCHAR* langEnumControlsJoyMouse();


//----------------------
// Configuration related lines
//----------------------

_TCHAR* langConfTitle();
_TCHAR* langConfConfigText();
_TCHAR* langConfSlotLayout();
_TCHAR* langConfMemory();
_TCHAR* langConfChipEmulation();
_TCHAR* langConfChipExtras();

_TCHAR* langConfOpenRom();
_TCHAR* langConfSaveTitle();
_TCHAR* langConfSaveAsTitle();
_TCHAR* langConfSaveText();
_TCHAR* langConfSaveAsMachineName();
_TCHAR* langConfDiscardTitle();
_TCHAR* langConfExitSaveTitle();
_TCHAR* langConfExitSaveText();

_TCHAR* langConfSlotLayoutGB();
_TCHAR* langConfSlotExtSlotGB();
_TCHAR* langConfBoardGB();
_TCHAR* langConfBoardText();
_TCHAR* langConfSlotPrimary();
_TCHAR* langConfSlotExpanded();

_TCHAR* langConfCartridge();
_TCHAR* langConfSlot();
_TCHAR* langConfSubslot();

_TCHAR* langConfMemAdd();
_TCHAR* langConfMemEdit();
_TCHAR* langConfMemRemove();
_TCHAR* langConfMemSlot();
_TCHAR* langConfMemAddress();
_TCHAR* langConfMemType();
_TCHAR* langConfMemRomImage();

_TCHAR* langConfChipVideoGB();
_TCHAR* langConfChipVideoChip();
_TCHAR* langConfChipVideoRam();
_TCHAR* langConfChipSoundGB();

_TCHAR* langConfCmosGB();
_TCHAR* langConfCmosEnableText();
_TCHAR* langConfCmosBatteryText();

_TCHAR* langConfChipCpuFreqGB();
_TCHAR* langConfChipZ80FreqText();
_TCHAR* langConfChipR800FreqText();
_TCHAR* langConfChipFdcGB();
_TCHAR* langConfChipFdcNumDrivesText();

_TCHAR* langConfEditMemTitle();
_TCHAR* langConfEditMemGB();
_TCHAR* langConfEditMemType();
_TCHAR* langConfEditMemFile();
_TCHAR* langConfEditMemAddress();
_TCHAR* langConfEditMemSize();
_TCHAR* langConfEditMemSlot();


//----------------------
// Shortcut lines
//----------------------

_TCHAR* langShortcutKey();
_TCHAR* langShortcutDescription();

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
_TCHAR* langShortcutPrnFormFeed();
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
_TCHAR* langShortcutShowPorts();
_TCHAR* langShortcutShowLanguage();
_TCHAR* langShortcutShowMachines();
_TCHAR* langShortcutShowShortcuts();
_TCHAR* langShortcutShowKeyboard();
_TCHAR* langShortcutShowMixer();
_TCHAR* langShortcutShowDebugger();
_TCHAR* langShortcutShowTrainer();
_TCHAR* langShortcutShowHelp();
_TCHAR* langShortcutShowAbout();
_TCHAR* langShortcutShowFiles();
_TCHAR* langShortcutToggleSpriteEnable();
_TCHAR* langShortcutToggleFdcTiming();
_TCHAR* langShortcutToggleCpuTrace();


//----------------------
// Keyboard config lines
//----------------------

_TCHAR* langKeyconfigSelectedKey();
_TCHAR* langKeyconfigMappedTo();
_TCHAR* langKeyconfigMappingScheme();


#endif

