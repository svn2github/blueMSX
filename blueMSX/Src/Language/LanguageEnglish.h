/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageEnglish.h,v $
**
** $Revision: 1.60 $
**
** $Date: 2006-06-04 21:33:21 $
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
#ifndef LANGUAGE_ENGLISH_H
#define LANGUAGE_ENGLISH_H

#include "LanguageStrings.h"
 
void langInitEnglish(LanguageStrings* ls) 
{
    //----------------------
    // Generic lines
    //----------------------

    ls->textDevice              = "Device:";
    ls->textFilename            = "Filename:";
    ls->textFile                = "File";
    ls->textNone                = "None";
    ls->textUnknown             = "Unknown";


    //----------------------
    // Warning and Error lines
    //----------------------

    ls->warningTitle            = "blueMSX - Warning";
    ls->warningDiscardChanges   = "Do you want to discard changes?";
    ls->warningOverwriteFile    = "Do you want to overwrite the file:";
    ls->errorTitle              = "blueMSX - Error";
    ls->errorEnterFullscreen    = "Failed to enter fullscreen mode.           \n";
    ls->errorDirectXFailed      = "Failed to create DirectX objects.           \nUsing GDI instead.\nCheck Video properties.";
    ls->errorNoRomInZip         = "Could not locate a .rom file in the zip archive.";
    ls->errorNoDskInZip         = "Could not locate a .dsk file in the zip archive.";
    ls->errorNoCasInZip         = "Could not locate a .cas file in the zip archive.";
    ls->errorNoHelp             = "Could not locate the blueMSX help file.";
    ls->errorStartEmu           = "Failed to Start MSX emulator.";
    ls->errorPortableReadonly   = "Portable device is readonly";


    //----------------------
    // File related lines
    //----------------------

    ls->fileRom                 = "ROM image";
    ls->fileAll                 = "All Files";
    ls->fileCpuState            = "CPU state";
    ls->fileDisk                = "Disk Image";
    ls->fileCas                 = "Tape Image";


    //----------------------
    // Menu related lines
    //----------------------

    ls->menuNoRecentFiles       = "- no recent files -";
    ls->menuInsert              = "Insert";
    ls->menuEject               = "Eject";

    ls->menuCartGameReader      = "Game Reader";
    ls->menuCartIde             = "IDE";
    ls->menuCartBeerIde         = "Beer";
    ls->menuCartGIde            = "GIDE";
    ls->menuCartSunriseIde      = "Sunrise";
    ls->menuCartSCC             = "SCC Cartridge";
    ls->menuCartSCCPlus         = "SCC+ Cartridge";
    ls->menuCartFMPac           = "FM-PAC Cartridge";
    ls->menuCartPac             = "PAC Cartridge";
    ls->menuCartHBI55           = "Sony HBI-55 Cartridge";
    ls->menuCartInsertSpecial   = "Insert Special";
    ls->menuCartMegaRam         = "MegaRAM";
    ls->menuCartExternalRam     = "External RAM";

    ls->menuDiskInsertNew       = "Insert New Disk Image";
    ls->menuDiskDirInsert       = "Insert Directory";
    ls->menuDiskAutoStart       = "Reset After Insert";
    ls->menuCartAutoReset       = "Reset After Insert/Remove";

    ls->menuCasRewindAfterInsert= "Rewind After Insert";
    ls->menuCasUseReadOnly      = "Use Cassette Image Read Only";
    ls->lmenuCasSaveAs          = "Save Cassette Image As...";
    ls->menuCasSetPosition      = "Set Position";
    ls->menuCasRewind           = "Rewind";

    ls->menuPrnFormfeed         = "Form Feed";

    ls->menuZoomNormal          = "Normal Size";
    ls->menuZoomDouble          = "Double Size";
    ls->menuZoomFullscreen      = "Fullscreen";
    
    ls->menuPropsEmulation      = "Emulation";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Sound";
    ls->menuPropsControls       = "Controls";
    ls->menuPropsPerformance    = "Performance";
    ls->menuPropsSettings       = "Settings";
    ls->menuPropsFile           = "Files";
    ls->menuPropsLanguage       = "Language";
    ls->menuPropsPorts          = "Ports";
    
    ls->menuVideoSource         = "Video Out Source";
    ls->menuVideoSourceDefault  = "No Video Out Source Connected";
    ls->menuVideoChipAutodetect = "Autodetect Video Chip";
    ls->menuVideoInSource       = "Video In Source";
    ls->menuVideoInBitmap       = "Bitmap File";

    ls->menuHelpHelp            = "Help Topics";
    ls->menuHelpAbout           = "About blueMSX";

    ls->menuFileCart            = "Cartridge Slot";
    ls->menuFileDisk            = "Disk Drive";
    ls->menuFileCas             = "Cassette";
    ls->menuFilePrn             = "Printer";
    ls->menuFileLoadState       = "Load CPU State";
    ls->menuFileSaveState       = "Save CPU State";
    ls->menuFileQLoadState      = "Quick Load State";
    ls->menuFileQSaveState      = "Quick Save State";
    ls->menuFileCaptureAudio    = "Capture Audio";
    ls->menuFileScreenShot      = "Save Screenshot";
    ls->menuFileExit            = "Exit";

    ls->menuFileHarddisk        = "Hard Disk";
    ls->menuFileHarddiskNoPesent= "No Controllers Present";

    ls->menuRunRun              = "Run";
    ls->menuRunPause            = "Pause";
    ls->menuRunStop             = "Stop";
    ls->menuRunSoftReset        = "Soft Reset";
    ls->menuRunHardReset        = "Hard Reset";
    ls->menuRunCleanReset       = "Complete Reset";

    ls->menuToolsMachine        = "Machine Editor";
    ls->menuToolsShortcuts      = "Shortcuts Editor";
    ls->menuToolsKeyboard       = "Controllers / Keyboard Editor";
    ls->menuToolsMixer          = "Mixer";

    ls->menuFile                = "File";
    ls->menuRun                 = "Emulation";
    ls->menuWindow              = "Window";
    ls->menuOptions             = "Options";
    ls->menuTools               = "Tools";
    ls->menuHelp                = "Help";
    

    //----------------------
    // Dialog related lines
    //----------------------

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Open";
    ls->dlgCancel               = "Cancel";
    ls->dlgSave                 = "Save";
    ls->dlgSaveAs               = "Save As...";
    ls->dlgRun                  = "Run";
    ls->dlgClose                = "Close";

    ls->dlgLoadRom              = "blueMSX - Select a rom image to load";
    ls->dlgLoadDsk              = "blueMSX - Select a dsk image to load";
    ls->dlgLoadCas              = "blueMSX - Select a cas image to load";
    ls->dlgLoadRomDskCas        = "blueMSX - Select a rom, dsk, or cas file to load";
    ls->dlgLoadRomDesc          = "Choose a rom image to load:";
    ls->dlgLoadDskDesc          = "Choose a disk image to load:";
    ls->dlgLoadCasDesc          = "Choose a tape image to load:";
    ls->dlgLoadRomDskCasDesc    = "Choose a rom, disk, or tape image to load:";
    ls->dlgLoadState            = "Load state";
    ls->dlgSaveState            = "Save state as...";
    ls->dlgSaveCassette         = "blueMSX - Save Tape Image";
    ls->dlgInsertRom1           = "Insert ROM cartridge into slot 1";
    ls->dlgInsertRom2           = "Insert ROM cartridge into slot 2";
    ls->dlgInsertDiskA          = "Insert disk image into drive A";
    ls->dlgInsertDiskB          = "Insert disk image into drive B";
    ls->dlgInsertHarddisk       = "Insert Hard Disk";
    ls->dlgInsertCas            = "Insert cassette tape";
    ls->dlgRomType              = "Rom Type:";

    ls->dlgTapeTitle            = "blueMSX - Tape Position";
    ls->dlgTapeFrameText        = "Tape Position";
    ls->dlgTapeCurrentPos       = "Current Position";
    ls->dlgTapeTotalTime        = "Total Time";
    ls->dlgTapeSetPosText       = "Tape Position:";
    ls->dlgTapeCustom           = "Show Custom Files";
    ls->dlgTabPosition          = "Position";
    ls->dlgTabType              = "Type";
    ls->dlgTabFilename          = "Filename";
    ls->dlgZipReset             = "Reset after insert";

    ls->dlgAboutTitle           = "blueMSX - About";

    ls->dlgLangLangText         = "Choose the language that blueMSX will use";
    ls->dlgLangLangTitle        = "blueMSX - Language";

    ls->dlgAboutAbout           = "ABOUT\r\n====";
    ls->dlgAboutVersion         = "Version:";
    ls->dlgAboutBuildNumber     = "Build:";
    ls->dlgAboutBuildDate       = "Date:";
    ls->dlgAboutCreat           = "Created by Daniel Vik";
    ls->dlgAboutDevel           = "DEVELOPERS\r\n========";
    ls->dlgAboutThanks          = "SPECIAL THANKS TO\r\n============";
    ls->dlgAboutLisence         = "LICENSE\r\n"
                                  "======\r\n\r\n"
                                  "This software is provided 'as-is', without any express or implied "
                                  "warranty. In no event will the author(s) be held liable for any damages "
                                  "arising from the use of this software.\r\n\r\n"
                                  "Visit www.bluemsx.com for more details.";

    ls->dlgSavePreview          = "Show Preview";
    ls->dlgSaveDate             = "Time Saved:";


    //----------------------
    // Properties related lines
    //----------------------

    ls->propTitle               = "blueMSX - Properties";
    ls->propEmulation           = "Emulation";
    ls->propVideo               = "Video";
    ls->propSound               = "Sound";
    ls->propControls            = "Controls";
    ls->propPerformance         = "Performance";
    ls->propSettings            = "Settings";
    ls->propFile                = "Files";
    ls->propPorts               = "Ports";
    
    ls->propEmuGeneralGB        = "General ";
    ls->propEmuFamilyText       = "MSX machine:";
    ls->propEmuMemoryGB         = "Memory ";
    ls->propEmuRamSizeText      = "RAM size:";
    ls->propEmuVramSizeText     = "VRAM size:";
    ls->propEmuSpeedGB          = "Emulation Speed ";
    ls->propEmuSpeedText        = "Emulation Speed:";
    ls->propEmuFrontSwitchGB    = "Panasonic Switches ";
    ls->propEmuFrontSwitch      = " Front Switch";
    ls->propEmuFdcTiming        = "Disable Floppy Drive Timing";
    ls->propEmuPauseSwitch      = " Pause Switch";
    ls->propEmuAudioSwitch      = " MSX-AUDIO cartridge switch";
    ls->propVideoFreqText       = "Video Frequency:";
    ls->propVideoFreqAuto       = "Auto";
    ls->propSndOversampleText   = "Oversample:";
    ls->propSndMidiInGB         = "MIDI In ";
    ls->propSndMidiOutGB        = "MIDI Out ";

    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Monitor type:";
    ls->propMonEmuText          = "Monitor emulation:";
    ls->propVideoTypeText       = "Video type:";
    ls->propWindowSizeText      = "Window size:";
    ls->propMonHorizStretch     = " Horizontal Stretch";
    ls->propMonVertStretch      = " Vertical Stretch";
    ls->propMonDeInterlace      = " De-interlace";
    ls->propMonBrightness       = "Brightness:";
    ls->propMonContrast         = "Contrast:";
    ls->propMonSaturation       = "Saturation:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanlines:";
    ls->propMonColorGhosting    = "RF-Modulator";
    ls->propMonEffectsGB        = "Effects ";

    ls->propPerfVideoDrvGB      = "Video Driver ";
    ls->propPerfVideoDispDrvText= "Display driver:";
    ls->propPerfFrameSkipText   = "Frame skipping:";
    ls->propPerfAudioDrvGB      = "Audio Driver ";
    ls->propPerfAudioDrvText    = "Sound driver:";
    ls->propPerfAudioBufSzText  = "Sound buffer size:";
    ls->propPerfEmuGB           = "Emulation ";
    ls->propPerfSyncModeText    = "SYNC Mode:";
    ls->propFullscreenResText   = "Fullscreen Resolution:";

    ls->propSndChipEmuGB        = "Sound Chip Emulation ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";
    ls->propSndMoonsound        = " Moonsound";
    ls->propSndMt32ToGm         = " Map MT-32 instruments to General MIDI";

    ls->propPortsLptGB          = "Parallel port ";
    ls->propPortsComGB          = "Serial ports ";
    ls->propPortsLptText        = "Port:";
    ls->propPortsCom1Text       = "Port 1:";
    ls->propPortsNone           = "None";
    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "Print to File";
    ls->propPortsComFile        = "Send to File";
    ls->propPortsOpenLogFile    = "Open Log File";
    ls->propPortsEmulateMsxPrn  = "Emulation:";

    ls->propSetFileHistoryGB    = "File History ";
    ls->propSetFileHistorySize  = "Number of items in File History:";
    ls->propSetFileHistoryClear = "Clear History";
    ls->propFileTypes           = " Register file types with blueMSX (.rom, .dsk, .cas, .sta)";
    ls->propWindowsEnvGB        = "Windows Environment "; 
    ls->propSetScreenSaver      = " Disable screen saver when blueMSX is running";
    ls->propDisableWinKeys      = " Automatic MSX function for Windows menu keys"; 
    ls->propPriorityBoost       = " Boost the priority of blueMSX";
    ls->propScreenshotPng       = " Use Portable Network Graphics (.png) screenshots";
    ls->propClearHistory        = "Are you sure you want to clear the file history ?";
    ls->propOpenRomGB           = "Open Rom Dialog ";
    ls->propDefaultRomType      = "Default Rom Type:";
    ls->propGuessRomType        = "Guess Rom Type";

    ls->propSettDefSlotGB       = "Drag and Drop ";
    ls->propSettDefSlots        = "Insert Rom Into:";
    ls->propSettDefSlot         = " Slot";
    ls->propSettDefDrives       = "Insert Diskette Into:";
    ls->propSettDefDrive        = " Drive";

    ls->propThemeGB             = "Theme ";
    ls->propTheme               = "Theme:";


    //----------------------
    // Dropdown related lines
    //----------------------

    ls->enumVideoMonColor       = "Color";
    ls->enumVideoMonGrey        = "Black and white";
    ls->enumVideoMonGreen       = "Green";
    ls->enumVideoMonAmber       = "Amber";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "None";
    ls->enumVideoEmuYc          = "Y/C cable (sharp)";
    ls->enumVideoEmuMonitor     = "Monitor";
    ls->enumVideoEmuYcBlur      = "Noisy Y/C cable (sharp)";
    ls->enumVideoEmuComp        = "Composite (blurry)";
    ls->enumVideoEmuCompBlur    = "Noisy Composite (blurry)";
    ls->enumVideoEmuScale2x     = "Scale 2x";
    ls->enumVideoEmuHq2x        = "Hq2x";

    ls->enumVideoSize1x         = "Normal - 320x200";
    ls->enumVideoSize2x         = "Double - 640x400";
    ls->enumVideoSizeFullscreen = "Fullscreen";

    ls->enumVideoDrvDirectDrawHW= "DirectDraw HW accel."; 
    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "None";
    ls->enumVideoFrameskip1     = "1 frame";
    ls->enumVideoFrameskip2     = "2 frames";
    ls->enumVideoFrameskip3     = "3 frames";
    ls->enumVideoFrameskip4     = "4 frames";
    ls->enumVideoFrameskip5     = "5 frames";

    ls->enumSoundDrvNone        = "No Sound";
    ls->enumSoundDrvWMM         = "WMM driver";
    ls->enumSoundDrvDirectX     = "DirectX driver";

    ls->enumEmuSync1ms          = "Sync on MSX refresh";
    ls->enumEmuSyncAuto         = "Auto (fast)";
    ls->enumEmuSyncNone         = "None";
    ls->enumEmuSyncVblank       = "Sync to PC Vertical Blank";

    ls->enumControlsJoyNone     = "None";
    ls->enumControlsJoyMouse    = "Mouse";
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle";
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey Dongle";


    //----------------------
    // Configuration related lines
    //----------------------

    ls->confTitle               = "blueMSX - Machine Configuration Editor";
    ls->confConfigText          = "Configuration";
    ls->confSlotLayout          = "Slot Layout";
    ls->confMemory              = "Memory";
    ls->confChipEmulation       = "Chip Emulation";
    ls->confChipExtras          = "Extras";

    ls->confOpenRom             = "Open ROM image";
    ls->confSaveTitle           = "blueMSX - Save Configuration";
    ls->confSaveText            = "Do you want to overwrite the machine configuration:";
    ls->confSaveAsTitle         = "Save Configuration As...";
    ls->confSaveAsMachineName   = "Machine Name:";
    ls->confDiscardTitle        = "blueMSX - Configuration";
    ls->confExitSaveTitle       = "blueMSX - Exit Configuration Editor";
    ls->confExitSaveText        = "Do you want to discard changes to the current configuration?";

    ls->confSlotLayoutGB        = "Slot Layout ";
    ls->confSlotExtSlotGB       = "External Slots ";
    ls->confBoardGB             = "Board ";
    ls->confBoardText           = "Board Type:";
    ls->confSlotPrimary         = "Primary";
    ls->confSlotExpanded        = "Expanded (four subslots)";

    ls->confSlotCart            = "Cartridge";
    ls->confSlot                = "Slot";
    ls->confSubslot             = "Subslot";

    ls->confMemAdd              = "Add...";
    ls->confMemEdit             = "Edit...";
    ls->confMemRemove           = "Remove";
    ls->confMemSlot             = "Slot";
    ls->confMemAddresss         = "Address";
    ls->confMemType             = "Type";
    ls->confMemRomImage         = "Rom Image";

    ls->confChipVideoGB          = "Video ";
    ls->confChipVideoChip        = "Video Chip:";
    ls->confChipVideoRam         = "Video RAM:";
    ls->confChipSoundGB          = "Sound ";

    ls->confCmosGB               = "CMOS ";
    ls->confCmosEnable           = " Enable CMOS";
    ls->confCmosBattery          = " Use Charged Battery";

    ls->confCpuFreqGB            = "CPU Frequency ";
    ls->confZ80FreqText          = "Z80 Frequency:";
    ls->confR800FreqText         = "R800 Frequency:";
    ls->confFdcGB                = "Floppy Disk Controller ";
    ls->confCFdcNumDrivesText    = "Number of Drives:";

    ls->confEditMemTitle         = "blueMSX - Edit Mapper";
    ls->confEditMemGB            = "Mapper Details ";
    ls->confEditMemType          = "Type:";
    ls->confEditMemFile          = "File:";
    ls->confEditMemAddress       = "Address";
    ls->confEditMemSize          = "Size";
    ls->confEditMemSlot          = "Slot";


    //----------------------
    // Shortcut lines
    //----------------------

    ls->shortcutKey             = "Hotkey";
    ls->shortcutDescription     = "Shortcut";

    ls->shortcutSaveConfig      = "blueMSX - Save Configuration";
    ls->shortcutOverwriteConfig = "Do you want to overwrite the shortcut configuration:";
    ls->shortcutExitConfig      = "blueMSX - Exit Shortcut Editor";
    ls->shortcutDiscardConfig   = "Do you want to discard changes to the current configuration?";
    ls->shortcutSaveConfigAs    = "blueMSX - Save Shortcut Configuration As...";
    ls->shortcutConfigName      = "Config Name:";
    ls->shortcutNewProfile      = "< New Profile >";
    ls->shortcutConfigTitle     = "blueMSX - Shortcut Mapping Editor";
    ls->shortcutAssign          = "Assign";
    ls->shortcutPressText       = "Press shortcut key(s):";
    ls->shortcutScheme          = "Mapping Scheme:";
    ls->shortcutCartInsert1     = "Insert Cartridge 1";
    ls->shortcutCartRemove1     = "Remove Cartridge 1";
    ls->shortcutCartInsert2     = "Insert Cartridge 2";
    ls->shortcutCartRemove2     = "Remove Cartridge 2";
    ls->shortcutSpecialMenu1    = "Show Special Rom Menu for Cartridge 1";
    ls->shortcutSpecialMenu2    = "Show Special Rom Menu for Cartridge 2";
    ls->shortcutCartAutoReset   = "Reset Emulator when Cartridge is Inserted";
    ls->shortcutDiskInsertA     = "Insert Diskette A";
    ls->shortcutDiskDirInsertA  = "Insert Directory as Diskette A";
    ls->shortcutDiskRemoveA     = "Eject Diskette A";
    ls->shortcutDiskChangeA     = "Quick change Diskette A";
    ls->shortcutDiskAutoResetA  = "Reset Emulator when Diskette A is Inserted";
    ls->shortcutDiskInsertB     = "Insert Diskette B";
    ls->shortcutDiskDirInsertB  = "Insert Directory as Diskette B";
    ls->shortcutDiskRemoveB     = "Eject Diskette B";
    ls->shortcutCasInsert       = "Insert Cassette";
    ls->shortcutCasEject        = "Eject Cassette";
    ls->shortcutCasAutorewind   = "Toggle Auto-rewind on Cassette";
    ls->shortcutCasReadOnly     = "Toggle Read-only Cassette";
    ls->shortcutCasSetPosition  = "Set Tape position";
    ls->shortcutCasRewind       = "Rewind Cassette";
    ls->shortcutCasSave         = "Save Cassette Image";
    ls->shortcutPrnFormFeed     = "Printer Form Feed";
    ls->shortcutCpuStateLoad    = "Load CPU state";
    ls->shortcutCpuStateSave    = "Save CPU state";
    ls->shortcutCpuStateQload   = "Quick load CPU state";
    ls->shortcutCpuStateQsave   = "Quick save CPU state";
    ls->shortcutAudioCapture    = "Start/stop audio capture";
    ls->shortcutScreenshotOrig  = "Screenshot capture";
    ls->shortcutScreenshotSmall = "Small unfiltered screenshot capture";
    ls->shortcutScreenshotLarge = "Large unfiltered screenshot capture";
    ls->shortcutQuit            = "Quit blueMSX";
    ls->shortcutRunPause        = "Run/Pause emulation";
    ls->shortcutStop            = "Stop emulation";
    ls->shortcutResetHard       = "Hard Reset";
    ls->shortcutResetSoft       = "Soft Reset";
    ls->shortcutResetClean      = "Complete Reset";
    ls->shortcutSizeSmall       = "Set small window size";
    ls->shortcutSizeNormal      = "Set normal window size";
    ls->shortcutSizeFullscreen  = "Set fullscreen";
    ls->shortcutSizeMinimized   = "Minimize window";
    ls->shortcutToggleFullscren = "Toggle fullscreen";
    ls->shortcutVolumeIncrease  = "Increase Volume";
    ls->shortcutVolumeDecrease  = "Decrease Volume";
    ls->shortcutVolumeMute      = "Mute Volume";
    ls->shortcutVolumeStereo    = "Toggle mono/stereo";
    ls->shortcutSwitchMsxAudio  = "Toggle MSX-AUDIO switch";
    ls->shortcutSwitchFront     = "Toggle Panasonic front switch";
    ls->shortcutSwitchPause     = "Toggle pause switch";
    ls->shortcutToggleMouseLock = "Toggle mouse lock";
    ls->shortcutEmuSpeedMax     = "Max emulation speed";
    ls->shortcutEmuSpeedToggle  = "Toggle max emulation speed";
    ls->shortcutEmuSpeedNormal  = "Normal emulation speed";
    ls->shortcutEmuSpeedInc     = "Increase emulation speed";
    ls->shortcutEmuSpeedDec     = "Decrease emulation speed";
    ls->shortcutThemeSwitch     = "Switch theme";
    ls->shortcutShowEmuProp     = "Show Emulation Properties";
    ls->shortcutShowVideoProp   = "Show Video Properties";
    ls->shortcutShowAudioProp   = "Show Audio Properties";
    ls->shortcutShowCtrlProp    = "Show Controls Properties";
    ls->shortcutShowPerfProp    = "Show Performance Properties";
    ls->shortcutShowSettProp    = "Show Settings Properties";
    ls->shortcutShowPorts       = "Show Ports Properties";
    ls->shortcutShowLanguage    = "Show Language Dialog";
    ls->shortcutShowMachines    = "Show Machine Editor";
    ls->shortcutShowShortcuts   = "Show Shortcuts Editor";
    ls->shortcutShowKeyboard    = "Show Controllers / Keyboard Editor";
    ls->shortcutShowMixer       = "Show Mixer";
    ls->shortcutShowDebugger    = "Show Debugger";
    ls->shortcutShowTrainer     = "Show Trainer";
    ls->shortcutShowHelp        = "Show Help Dialog";
    ls->shortcutShowAbout       = "Show About Dialog";    
    ls->shortcutShowFiles       = "Show Files Properties";
    ls->shortcutToggleSpriteEnable = "Show/Hide Sprites";
    ls->shortcutToggleFdcTiming = "Enable/Disable Floppy Drive Timing";
    ls->shortcutToggleCpuTrace  = "Enable/Disable CPU Trace";


    //----------------------
    // Keyboard config lines
    //----------------------    
 
    ls->keyconfigSelectedKey    = "Selected Key:";
    ls->keyconfigMappedTo       = "Mapped To:";
    ls->keyconfigMappingScheme  = "Mapping Scheme:";
};

#endif
