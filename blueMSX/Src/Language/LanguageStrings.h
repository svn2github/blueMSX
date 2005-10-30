/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageStrings.h,v $
**
** $Revision: 1.38 $
**
** $Date: 2005-10-30 01:49:54 $
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
#ifndef LANGUAGE_STRINGS_H
#define LANGUAGE_STRINGS_H

#ifdef WIN32
#include <windows.h>
#include <tchar.h>
#else
typedef char _TCHAR;
#endif

typedef struct {
    _TCHAR* statusBarStopped;
    _TCHAR* statusBarPaused;
    _TCHAR* statusBarRunning;

    _TCHAR* menuHardReset;
    _TCHAR* menuSoftReset;

    _TCHAR* menuCartInsert;
    _TCHAR* menuCartRemove;
    _TCHAR* menuCartAutoReset;
    _TCHAR* menuCartNoRecentFiles;
    _TCHAR* menuCartSnatcher;
    _TCHAR* menuCartSdSnatcher;
    _TCHAR* menuCartGameReader;
    _TCHAR* menuCartSCCMirrored;
    _TCHAR* menuCartSCCExpanded;
    _TCHAR* menuCartSCCPlus;
    _TCHAR* menuCartSCC;
    _TCHAR* menuCartFMPac;
    _TCHAR* menuCartPac;
    _TCHAR* menuCartHBI55;
    _TCHAR* menuCartSpecial;
    _TCHAR* menuCartExternalRam;
    
    _TCHAR* menuDiskInsert;
    _TCHAR* menuDiskDirInsert;
    _TCHAR* menuDiskEject;
    _TCHAR* menuDiskAutoStart;
    _TCHAR* menuDiskNoRecentFiles;

    _TCHAR* menuCasInsert;
    _TCHAR* menuCasEject;
    _TCHAR* menuCasRewindAfterInsert;
    _TCHAR* menuCasUseReadOnly;
    _TCHAR* lmenuCasSaveAs;
    _TCHAR* menuCasSetPosition;
    _TCHAR* menuCasRewind;
    _TCHAR* menuCasNoRecentFiles;

    _TCHAR* menuPrnFormfeed;

    _TCHAR* menuZoomNormal;
    _TCHAR* menuZoomDouble;
    _TCHAR* menuZoomFullscreen;

    _TCHAR* menuPropsEmulation;
    _TCHAR* menuPropsVideo;
    _TCHAR* menuPropsSound;
    _TCHAR* menuPropsControls;
    _TCHAR* menuPropsPerformance;
    _TCHAR* menuPropsPorts;
    _TCHAR* menuPropsSettings;
    _TCHAR* menuPropsFile;
    _TCHAR* menuPropsApearance;
    _TCHAR* menuTools;
    _TCHAR* menuPropsLanguage;

    _TCHAR* menuVideoSource;
    _TCHAR* menuVideoSourceDefault;
    _TCHAR* menuVideoChipAutodetect;

    _TCHAR* menuToolsMachine;
    _TCHAR* menuToolsShortcuts;
    _TCHAR* menuToolsKeyboard;
    _TCHAR* menuToolsMixer;

    _TCHAR* menuHelpHelp;
    _TCHAR* menuHelpAbout;
    
    _TCHAR* menuFileCart1;
    _TCHAR* menuFileCart2;
    _TCHAR* menuFileDiskA;
    _TCHAR* menuFileDiskB;
    _TCHAR* menuFileCas;
    _TCHAR* menuFilePrn;
    _TCHAR* menuFileLoadState;
    _TCHAR* menuFileSaveState;
    _TCHAR* menuFileQLoadState;
    _TCHAR* menuFileQSaveState;
    _TCHAR* menuFileCaptureAudio;
    _TCHAR* menuFileScreenShot;
    _TCHAR* menuFileExit;

    _TCHAR* menuRunRun;
    _TCHAR* menuRunPause;
    _TCHAR* menuRunStop;
    _TCHAR* menuRunSoftReset;
    _TCHAR* menuRunHardReset;
    _TCHAR* menuRunCleanReset;
    
    _TCHAR* menuFile;
    _TCHAR* menuRun;
    _TCHAR* menuWindow;
    _TCHAR* menuOptions;
    _TCHAR* menuHelp;

    _TCHAR* errorTitle;
    _TCHAR* warningTitle;
    _TCHAR* errorEnterFullscreen;
    _TCHAR* errorDirectXFailed;
    _TCHAR* errorNoRomInZip;
    _TCHAR* errorNoDskInZip;
    _TCHAR* errorNoCasInZip;
    _TCHAR* errorNoHelp;
    _TCHAR* errorStartEmu;
    _TCHAR* discardChanges;
    _TCHAR* overwriteConfig;

    _TCHAR* tooltipReset;
    _TCHAR* tooltipCart1;
    _TCHAR* tooltipCart2;
    _TCHAR* tooltipDiskA;
    _TCHAR* tooltipDiskB;
    _TCHAR* tooltipCas;
    _TCHAR* tooltipStart;
    _TCHAR* tooltipResume;
    _TCHAR* tooltipPause;
    _TCHAR* tooltipStop;
    _TCHAR* tooltipWindowSize;
    _TCHAR* tooltipProperties;
    _TCHAR* tooltipHelp;
    
    _TCHAR* dlgMainWindow;
    _TCHAR* dlgLoadRom;
    _TCHAR* dlgLoadDsk;
    _TCHAR* dlgLoadCas;
    _TCHAR* dlgLoadRomDskCas;
    _TCHAR* dlgLoadRomDesc;
    _TCHAR* dlgLoadDskDesc;
    _TCHAR* dlgLoadCasDesc;
    _TCHAR* dlgLoadRomDskCasDesc;
    _TCHAR* dlgLoadState;
    _TCHAR* dlgSaveState;
    _TCHAR* dlgInsertRom1;
    _TCHAR* dlgInsertRom2;
    _TCHAR* dlgInsertDiskA;
    _TCHAR* dlgInsertDiskB;
    _TCHAR* dlgInsertCas;
    _TCHAR* dlgRomType;

    _TCHAR* dlgOK;
    _TCHAR* dlgOpen;
    _TCHAR* dlgCancel;
    _TCHAR* dlgTapeTitle;
    _TCHAR* dlgTapeFrameText;
    _TCHAR* dlgTapeCurrentPos;
    _TCHAR* dlgTapeTotalTime;
    _TCHAR* dlgTapeCustom;
    _TCHAR* dlgTapeSetPosText;
    _TCHAR* dlgTabPosition;
    _TCHAR* dlgTabType;
    _TCHAR* dlgTabFilename;

    _TCHAR* dlgSaveCassette;

    _TCHAR* dlgZipReset;

    _TCHAR* dlgAboutTitle;

    _TCHAR* dlgJoyTitle1;
    _TCHAR* dlgJoyTitle2;
    _TCHAR* dlgJoyUpText;
    _TCHAR* dlgJoyDownText;
    _TCHAR* dlgJoyLeftText;
    _TCHAR* dlgJoyRightText;
    _TCHAR* dlgJoyButton1Text;
    _TCHAR* dlgJoyButton2Text;
    _TCHAR* dlgJoyGB;

    _TCHAR* dlgLangLangText;
    _TCHAR* dlgLangLangTitle;

    _TCHAR* propTitle;
    _TCHAR* propEmulation;
    _TCHAR* propVideo;
    _TCHAR* propSound;
    _TCHAR* propControls;
    _TCHAR* propPerformance;
    _TCHAR* propPorts;
    _TCHAR* propSettings;

    _TCHAR* propEmuGeneralGB;
    _TCHAR* propEmuFamilyText;
    _TCHAR* propEmuMemoryGB;
    _TCHAR* propEmuRamSizeText;
    _TCHAR* propEmuVramSizeText;
    _TCHAR* propEmuSpeedGB;
    _TCHAR* propEmuSpeedText;
    _TCHAR* propEmuFrontSwitchGB;
    _TCHAR* propEmuFrontSwitch;
    _TCHAR* propEmuFdcTiming;
    _TCHAR* propEmuPauseSwitch;
    _TCHAR* propEmuAudioSwitch;
    _TCHAR* propVideoFreqText;
    _TCHAR* propVideoFreqAuto;
    _TCHAR* propSndOversampleText;

    _TCHAR* propSndMidiInGB;
    _TCHAR* propSndMidiOutGB;

    _TCHAR* textDevice;
    _TCHAR* textFilename;
    _TCHAR* textFile;
    _TCHAR* textNone;

    _TCHAR* propMonMonGB;
    _TCHAR* propMonTypeText;
    _TCHAR* propMonEmuText;
    _TCHAR* propVideoYypeText;
    _TCHAR* propWindowSizeText;
    _TCHAR* propMonHorizStretch;
    _TCHAR* propMonVertStretch;
    _TCHAR* propMonDeInterlace;
    _TCHAR* propMonBrightness;
    _TCHAR* propMonContrast;
    _TCHAR* propMonSaturation;
    _TCHAR* propMonGamma;
    _TCHAR* propMonScanlines;
    _TCHAR* propMonColorGhosting;
    _TCHAR* propMonEffectsGB;

    _TCHAR* propPerfVideoDrvGB;
    _TCHAR* propPerfVideoDispDrvText;
    _TCHAR* propPerfFrameSkipText;
    _TCHAR* propPerfAudioDrvGB;
    _TCHAR* propPerfAudioDrvText;
    _TCHAR* propPerfAudioBufSzText;
    _TCHAR* propPerfEmuGB;
    _TCHAR* propPerfSyncModeText;
    _TCHAR* propFullscreenResText;

    _TCHAR* propSndChipEmuGB;
    _TCHAR* propSndMixerGB;
    _TCHAR* propSndMonoText;
    _TCHAR* propSndStereoText;
    _TCHAR* propSndMsxMusicText;
    _TCHAR* propSndMsxAudioText;
    _TCHAR* propSndMoonsound;
    _TCHAR* propSndPcm;
    _TCHAR* propSndAY8910;
    _TCHAR* propSndSN76489;
    _TCHAR* propSndMsxMasterText;
    _TCHAR* propSndMt32ToGmText;

    _TCHAR* propJoyPort1GB;
    _TCHAR* propJoyPort2GB;
    _TCHAR* propJoyAutofireText;
    _TCHAR* propJoyKeyset;
    _TCHAR* propJoyConfigKeyset;
    _TCHAR* propJoyControlText;
    _TCHAR* propJoyButtonText;
    _TCHAR* propJoyButtonAText;
    _TCHAR* propJoyButtonBText;

    _TCHAR* propJoyKeysetGB;
    _TCHAR* propJoyKeyest1;
    _TCHAR* propJoyKeyest2;

    _TCHAR* propPortsLptGB;
    _TCHAR* propPortsComGB;
    _TCHAR* propPortsLptText;
    _TCHAR* propPortsCom1Text;
    _TCHAR* propPortsNone;
    _TCHAR* propPortsSimplCovox;
    _TCHAR* propPortsFile;
    _TCHAR* propPortsComFile;
    _TCHAR* propPortsOpenLogFile;
    _TCHAR* propPortsFilenameText;
    _TCHAR* propPortsEmulateMsxPrn;

    _TCHAR* propSetFileHistoryGB;
    _TCHAR* propSetFileHistorySize;
    _TCHAR* propSetFileHistoryClear;
    _TCHAR* propSetScreenSaverGB;
    _TCHAR* propFileTypesGB;
    _TCHAR* propWindowsEnvGB;
    _TCHAR* propSetScreenSaver;
    _TCHAR* propFileTypes;
    _TCHAR* propDisableWinKeys;
    _TCHAR* propPriorityBoost;
    _TCHAR* propUseRegistry;
    _TCHAR* propClearHistory;
    _TCHAR* propSettDefSlotGB;
    _TCHAR* propSettDefSlots;
    _TCHAR* propSettDefSlot1;
    _TCHAR* propSettDefSlot2;
    _TCHAR* propSettDefDrives;
    _TCHAR* propSettDefDriveA;
    _TCHAR* propSettDefDriveB;
    
    _TCHAR* propApearance;
    _TCHAR* propFile;
    _TCHAR* propThemeGB;
    _TCHAR* propTheme;
    _TCHAR* propThemeClassic;
    _TCHAR* propThemeBlue;

    _TCHAR* propOpenRomGB;
    _TCHAR* propDefaultRomType;
    _TCHAR* propGuessRomType;

    _TCHAR* enumVideoMonColor;
    _TCHAR* enumVideoMonGrey;
    _TCHAR* enumVideoMonGreen;
    _TCHAR* enumVideoMonAmber;

    _TCHAR* enumVideoTypePAL;
    _TCHAR* enumVideoTypeNTSC;

    _TCHAR* enumVideoEmuNone;
    _TCHAR* enumVideoEmuYc;
    _TCHAR* enumVideoEmuMonitor;
    _TCHAR* enumVideoEmuYcBlur;
    _TCHAR* enumVideoEmuComp;
    _TCHAR* enumVideoEmuCompBlur;
    _TCHAR* enumVideoEmuScale2x;
    _TCHAR* enumVideoEmuHq2x;

    _TCHAR* enumVideoSize1x;
    _TCHAR* enumVideoSize2x;
    _TCHAR* enumVideoSizeFullscreen;

    _TCHAR* enumVideoDrvDirectDrawHW;
    _TCHAR* enumVideoDrvDirectDrawHWSys;
    _TCHAR* enumVideoDrvDirectDraw;
    _TCHAR* enumVideoDrvGDI;

    _TCHAR* enumVideoFrameskip0;
    _TCHAR* enumVideoFrameskip1;
    _TCHAR* enumVideoFrameskip2;
    _TCHAR* enumVideoFrameskip3;
    _TCHAR* enumVideoFrameskip4;
    _TCHAR* enumVideoFrameskip5;

    _TCHAR* enumSoundDrvNone;
    _TCHAR* enumSoundDrvWMM;
    _TCHAR* enumSoundDrvDirectX;

    _TCHAR* enumEmuSync1ms;
    _TCHAR* enumEmuSyncAuto;
    _TCHAR* enumEmuSyncNone;
    _TCHAR* enumEmuSyncVblank;

    _TCHAR* enumControlsJoyNone;
    _TCHAR* enumControlsJoyNumpad;
    _TCHAR* enumControlsJoyKeyset;
    _TCHAR* enumControlsJoyTetris2Dongle;
    _TCHAR* enumControlsJoyKeysetA;
    _TCHAR* enumControlsJoyKeysetB;
    _TCHAR* enumControlsJoyPCjoy1;
    _TCHAR* enumControlsJoyPCjoy2;
    _TCHAR* enumControlsJoyMouse;

    _TCHAR* enumControlsAfOff;
    _TCHAR* enumControlsAfSlow;
    _TCHAR* enumControlsAfMedium;
    _TCHAR* enumControlsAfFast;

    _TCHAR* dlgAboutAbout;
    _TCHAR* dlgAboutVersion;
    _TCHAR* dlgAboutBuildNumber;
    _TCHAR* dlgAboutBuildDate;
    _TCHAR* dlgAboutCreat;
    _TCHAR* dlgAboutDevel;
    _TCHAR* dlgAboutThanks;
    _TCHAR* dlgAboutLisence;
    _TCHAR* dlgSavePreview;
    _TCHAR* dlgSaveDate;
    
    _TCHAR* confTitle;
    _TCHAR* confSave;
    _TCHAR* confSaveAs;
    _TCHAR* confRun;
    _TCHAR* confClose;
    _TCHAR* confConfigText;
    _TCHAR* confSlotLayout;
    _TCHAR* confMemory;
    _TCHAR* confChipEmulation;
    _TCHAR* confChipExtras;
        
    _TCHAR* confChipVideoGB;
    _TCHAR* confChipVideoChip;
    _TCHAR* confChipVideoRam;
    _TCHAR* confChipSoundGB;

    _TCHAR* dlgCmosGB;
    _TCHAR* dlgCmosEnable;
    _TCHAR* dlgCmosBattery;
        
    _TCHAR* dlgCpuFreqGB;
    _TCHAR* dlgZ80FreqText;
    _TCHAR* dlgR800FreqText;
    _TCHAR* dlgFdcGB;
    _TCHAR* dlgCFdcNumDrivesText;

    _TCHAR* confSlotLayoutGB;
    _TCHAR* confSlotExtSlotGB;
    _TCHAR* confBoardGB;
    _TCHAR* confBoardText;
    _TCHAR* confSlotSlot0;
    _TCHAR* confSlotSlot1;
    _TCHAR* confSlotSlot2;
    _TCHAR* confSlotSlot3;
    _TCHAR* confSlotCart1;
    _TCHAR* confSlotCart2;
    _TCHAR* confSlotPrimary;
    _TCHAR* confSlotExpanded;

    _TCHAR* confSlot;
    _TCHAR* confSubslot;

    _TCHAR* shortcut;
    _TCHAR* hotkey;
    _TCHAR* unknown;
    _TCHAR* romImage;
    _TCHAR* romImageOpen;
    _TCHAR* romCartridge;
    _TCHAR* allFiles;
    _TCHAR* cpuState;
    _TCHAR* diskImage;
    _TCHAR* casImage;

    _TCHAR* confMemAdd;
    _TCHAR* confMemEdit;
    _TCHAR* confMemRemove;
    _TCHAR* confMemSlot;
    _TCHAR* confMemAddresss;
    _TCHAR* confMemType;
    _TCHAR* confMemRomImage;
    
    _TCHAR* confMemSaveTitle;
    _TCHAR* confMemSaveText;
        
    _TCHAR* slotEditMemTitle;
    _TCHAR* slotEditMemGB;
    _TCHAR* slotEditMemType;
    _TCHAR* slotEditMemFile;
    _TCHAR* slotEditMemAddress;
    _TCHAR* slotEditMemSize;
    _TCHAR* slotEditMemSlot;

    _TCHAR* confSaveTitle;
    _TCHAR* confSaveText;

    _TCHAR* confDiscardTitle;
    _TCHAR* confExitSaveTitle;
    _TCHAR* confExitSaveText;

    _TCHAR* confSaveAsMachineTitle;
    _TCHAR* confSaveAsMachineName;

    _TCHAR* confEditMemInternalRoms;

    _TCHAR* confSaveAsTitle;
    _TCHAR* confSaveAsName;

    _TCHAR* shortcutSaveConfig;
    _TCHAR* shortcutOverwriteConfig;
    _TCHAR* shortcutExitConfig;
    _TCHAR* shortcutDiscardConfig;
    _TCHAR* shortcutSaveConfigAs;
    _TCHAR* shortcutConfigName;
    _TCHAR* shortcutNewProfile;
    _TCHAR* shortcutConfigTitle;
    _TCHAR* shortcutAssign;
    _TCHAR* shortcutPressText;
    _TCHAR* shortcutScheme;

    _TCHAR* shortcutCartInsert1;
    _TCHAR* shortcutCartRemove1;
    _TCHAR* shortcutCartInsert2;
    _TCHAR* shortcutCartRemove2;
    _TCHAR* shortcutSpecialMenu1;
    _TCHAR* shortcutSpecialMenu2;
    _TCHAR* shortcutCartAutoReset;
    _TCHAR* shortcutDiskInsertA;
    _TCHAR* shortcutDiskDirInsertA;
    _TCHAR* shortcutDiskRemoveA;
    _TCHAR* shortcutDiskChangeA;
    _TCHAR* shortcutDiskAutoResetA;
    _TCHAR* shortcutDiskInsertB;
    _TCHAR* shortcutDiskDirInsertB;
    _TCHAR* shortcutDiskRemoveB;
    _TCHAR* shortcutCasInsert;
    _TCHAR* shortcutCasEject;
    _TCHAR* shortcutCasAutorewind;
    _TCHAR* shortcutCasReadOnly;
    _TCHAR* shortcutCasSetPosition;
    _TCHAR* shortcutCasRewind;
    _TCHAR* shortcutCasSave;
    _TCHAR* shortcutPrnFormFeed;
    _TCHAR* shortcutCpuStateLoad;
    _TCHAR* shortcutCpuStateSave;
    _TCHAR* shortcutCpuStateQload;
    _TCHAR* shortcutCpuStateQsave;
    _TCHAR* shortcutAudioCapture;
    _TCHAR* shortcutScreenshotOrig;
    _TCHAR* shortcutScreenshotSmall;
    _TCHAR* shortcutScreenshotLarge;
    _TCHAR* shortcutQuit;
    _TCHAR* shortcutRunPause;
    _TCHAR* shortcutStop;
    _TCHAR* shortcutResetHard;
    _TCHAR* shortcutResetSoft;
    _TCHAR* shortcutResetClean;
    _TCHAR* shortcutSizeSmall;
    _TCHAR* shortcutSizeNormal;
    _TCHAR* shortcutSizeFullscreen;
    _TCHAR* shortcutSizeMinimized;
    _TCHAR* shortcutToggleFullscren;
    _TCHAR* shortcutVolumeIncrease;
    _TCHAR* shortcutVolumeDecrease;
    _TCHAR* shortcutVolumeMute;
    _TCHAR* shortcutVolumeStereo;
    _TCHAR* shortcutSwitchMsxAudio;
    _TCHAR* shortcutSwitchFront;
    _TCHAR* shortcutSwitchPause;
    _TCHAR* shortcutToggleMouseLock;
    _TCHAR* shortcutEmuSpeedMax;
    _TCHAR* shortcutEmuSpeedToggle;
    _TCHAR* shortcutEmuSpeedNormal;
    _TCHAR* shortcutEmuSpeedInc;
    _TCHAR* shortcutEmuSpeedDec;
    _TCHAR* shortcutThemeSwitch;
    _TCHAR* shortcutShowEmuProp;
    _TCHAR* shortcutShowVideoProp;
    _TCHAR* shortcutShowAudioProp;
    _TCHAR* shortcutShowCtrlProp;
    _TCHAR* shortcutShowPerfProp;
    _TCHAR* shortcutShowSettProp;
    _TCHAR* shortcutShowPorts;
    _TCHAR* shortcutShowApearProp;
    _TCHAR* shortcutShowLanguage;
    _TCHAR* shortcutShowMachines;
    _TCHAR* shortcutShowShortcuts;
    _TCHAR* shortcutShowKeyboard;
    _TCHAR* shortcutShowMixer;
    _TCHAR* shortcutShowDebugger;
    _TCHAR* shortcutShowTrainer;
    _TCHAR* shortcutShowHelp;
    _TCHAR* shortcutShowAbout;
    _TCHAR* shortcutShowFiles;
    _TCHAR* shortcutToggleSpriteEnable;
    _TCHAR* shortcutToggleFdcTiming;
    _TCHAR* shortcutToggleCpuTrace;

    _TCHAR* keyconfigSelectedKey;
    _TCHAR* keyconfigMappedTo;
    _TCHAR* keyconfigMappingScheme;

} LanguageStrings;

#endif

