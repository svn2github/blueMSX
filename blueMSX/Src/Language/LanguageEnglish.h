/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageEnglish.h,v $
**
** $Revision: 1.53 $
**
** $Date: 2006-06-03 17:55:54 $
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
    ls->noRecentFiles           = "- no recent files -";
    ls->insert                  = "Insert";
    ls->eject                   = "Eject";

    ls->menuCartAutoReset       = "Reset After Insert/Remove";
    ls->menuCartFMPac           = "FM-PAC Cartridge";
    ls->menuCartPac             = "PAC Cartridge";

    ls->menuDiskAutoStart       = "Reset After Insert";
    
    ls->menuCasSetPosition      = "Set Position";
    ls->menuCasRewind           = "Rewind";

    ls->menuZoomNormal          = "Normal Size";
    ls->menuZoomDouble          = "Double Size";
    ls->menuZoomFullscreen      = "Fullscreen";
    
    ls->menuPropsEmulation      = "Emulation";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Sound";
    ls->menuPropsControls       = "Controls";
    ls->menuPropsPerformance    = "Performance";
    ls->menuPropsLanguage       = "Language";
    
    ls->menuHelpHelp            = "Help Topics";
    ls->menuHelpAbout           = "About blueMSX";

    ls->menuFileCart           = "Cartridge Slot";
    ls->menuFileDisk           = "Disk Drive";
    ls->menuFileCas             = "Cassette";
    ls->menuFileLoadState       = "Load CPU State";
    ls->menuFileSaveState       = "Save CPU State";
    ls->menuFileQLoadState      = "Quick Load State";
    ls->menuFileQSaveState      = "Quick Save State";
    ls->menuFileCaptureAudio    = "Capture Audio";
    ls->menuFileScreenShot      = "Save Screenshot";
    ls->menuFileExit            = "Exit";

    ls->menuRunRun              = "Run";
    ls->menuRunPause            = "Pause";
    ls->menuRunStop             = "Stop";
    ls->menuRunSoftReset        = "Soft Reset";
    ls->menuRunHardReset        = "Hard Reset";
    ls->menuRunCleanReset       = "General Reset";

    ls->menuFile                = "File";
    ls->menuRun                 = "Run";
    ls->menuWindow              = "Window";
    ls->menuOptions             = "Options";
    ls->menuHelp                = "Help";
    
    ls->errorTitle              = "blueMSX - Error";
    ls->errorEnterFullscreen    = "Failed to enter fullscreen mode.           \n";
    ls->errorDirectXFailed      = "Failed to create DirectX objects.           \nUsing GDI instead.\nCheck Video properties.";
    ls->errorNoRomInZip         = "Could not locate a .rom file in the zip archive.";
    ls->errorNoDskInZip         = "Could not locate a .dsk file in the zip archive.";
    ls->errorNoCasInZip         = "Could not locate a .cas file in the zip archive.";
    ls->errorNoHelp             = "Could not locate the blueMSX help file.";
    ls->errorStartEmu           = "Failed to Start MSX emulator.";


    ls->dlgLoadRom              = "blueMSX - Select a rom image to load";
    ls->dlgLoadDsk              = "blueMSX - Select a dsk image to load";
    ls->dlgLoadCas              = "blueMSX - Select a cas image to load";
    ls->dlgLoadRomDskCas        = "blueMSX - Select a rom, dsk, or cas file to load";
    ls->dlgLoadRomDesc          = "Choose a rom image to load:";
    ls->dlgLoadDskDesc          = "Choose a disk image to load:";
    ls->dlgLoadCasDesc          = "Choose a tape image to load:";
    ls->dlgLoadRomDskCasDesc    = "Choose a rom, disk, or tape image to load:";
    ls->dlgLoadState            = "Load CPU state";
    ls->dlgSaveState            = "Save CPU state";
    ls->dlgInsertRom1           = "Insert ROM cartridge into slot 1";
    ls->dlgInsertRom2           = "Insert ROM cartridge into slot 2";
    ls->dlgInsertDiskA          = "Insert disk image into drive A";
    ls->dlgInsertDiskB          = "Insert disk image into drive B";
    ls->dlgInsertCas            = "Insert cassette tape";

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Open";
    ls->dlgCancel               = "Cancel";

    ls->dlgTapeTitle            = "blueMSX - Tape Position";
    ls->dlgTapeFrameText        = "Tape Position";
    ls->dlgTapeCurrentPos       = "Current Position";
    ls->dlgTapeTotalTime        = "Total Time";

    ls->dlgZipReset             = "Reset after insert";

    ls->dlgAboutTitle           = "blueMSX - About";

    ls->dlgLangLangText         = "Choose the language that blueMSX will use";
    ls->dlgLangLangTitle        = "blueMSX - Language";

    ls->propTitle               = "blueMSX - Properties";
    ls->propEmulation           = "Emulation";
    ls->propVideo               = "Video";
    ls->propSound               = "Sound";
    ls->propControls            = "Controls";
    ls->propPerformance         = "Performance";
    
    ls->propEmuGeneralGB        = "General ";
    ls->propEmuFamilyText       = "MSX machine:";
    ls->propEmuMemoryGB         = "Memory ";
    ls->propEmuRamSizeText      = "RAM size:";
    ls->propEmuVramSizeText     = "VRAM size:";
    ls->propEmuSpeedGB          = "Emulation Speed ";
    ls->propEmuSpeedText        = "Emulation Speed:";

    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Monitor type:";
    ls->propMonEmuText          = "Monitor emulation:";
    ls->propVideoYypeText       = "Video type:";
    ls->propWindowSizeText      = "Window size:";

    ls->propPerfVideoDrvGB      = "Video Driver ";
    ls->propPerfVideoDispDrvText= "Display driver:";
    ls->propPerfFrameSkipText   = "Frame skipping:";
    ls->propPerfAudioDrvGB      = "Audio Driver ";
    ls->propPerfAudioDrvText    = "Sound driver:";
    ls->propPerfAudioBufSzText  = "Sound buffer size:";
    ls->propPerfEmuGB           = "Emulation ";
    ls->propPerfSyncModeText    = "SYNC Mode:";

    ls->propSndChipEmuGB        = "Sound Chip Emulation ";
    ls->propSndMixerGB          = "Audio Mixer ";
    ls->propSndMonoText         = "mono";
    ls->propSndStereoText       = "stereo";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "MASTER";

    ls->enumVideoMonColor       = "Color";
    ls->enumVideoMonGrey        = "Black and white";
    ls->enumVideoMonGreen       = "Green";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "None";
    ls->enumVideoEmuYc          = "Y/C cable (sharp)";
    ls->enumVideoEmuYcBlur      = "Noisy Y/C cable (sharp)";
    ls->enumVideoEmuComp        = "Composite (blurry)";
    ls->enumVideoEmuCompBlur    = "Noisy Composite (blurry)";
    ls->enumVideoEmuScale2x     = "Scale 2x";

    ls->enumVideoSize1x         = "Normal - 320x200";
    ls->enumVideoSize2x         = "Double - 640x400";
    ls->enumVideoSizeFullscreen = "Fullscreen";

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

    ls->enumControlsJoyNone     = "None";
    ls->enumControlsJoyMouse    = "Mouse";

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

    // New entries
    ls->menuTools                = "Tools";
    ls->menuToolsMachine         = "Machine Editor";
    ls->menuPropsSettings        = "Settings";
    ls->menuCasRewindAfterInsert = "Rewind After Insert";
    ls->menuCasUseReadOnly       = "Use Cassette Image Read Only";
    ls->lmenuCasSaveAs           = "Save Cassette Image As...";

    ls->dlgSaveCassette          = "blueMSX - Save Tape Image";
    ls->dlgTapeCustom            = "Show Custom Files";
    ls->dlgTapeSetPosText        = "Tape Position:";
    ls->dlgTabPosition           = "Position";
    ls->dlgTabType               = "Type";
    ls->dlgTabFilename           = "Filename";

    ls->propSettings             = "Settings";
    
    ls->propSetFileHistoryGB     = "File History ";
    ls->propSetFileHistorySize   = "Number of items in File History:";
    ls->propSetFileHistoryClear  = "Clear History";
    ls->propSetScreenSaver       = " Disable screen saver when blueMSX is running";

    ls->confTitle                = "blueMSX - Machine Configuration Editor";
    ls->confSave                 = "Save";
    ls->confSaveAs               = "Save As...";
    ls->confRun                  = "Run";
    ls->confClose                = "Close";
    ls->confConfigText           = "Configuration";
    ls->confSlotLayout           = "Slot Layout";
    ls->confMemory               = "Memory";
    ls->confChipEmulation        = "Chip Emulation";

    ls->confSlotLayoutGB         = "Slot Layout ";
    ls->confSlotExtSlotGB        = "External Slots ";
    ls->confSlotCart             = "Cartridge";
    ls->confSlotPrimary          = "Primary";
    ls->confSlotExpanded         = "Expanded (four subslots)";

    ls->confMemAdd               = "Add...";
    ls->confMemEdit              = "Edit...";
    ls->confMemRemove            = "Remove";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Address";
    ls->confMemType              = "Type";
    ls->confMemRomImage          = "Rom Image";
    
    ls->confSaveTitle            = "blueMSX - Save Configuration";
    ls->confSaveText             = "Do you want to overwrite the machine configuration:";

    ls->confChipVideoGB          = "Video ";
    ls->confChipVideoChip        = "Video Chip:";
    ls->confChipVideoRam         = "Video RAM:";
    ls->confChipSoundGB          = "Sound ";

    ls->slotEditMemTitle         = "blueMSX - Edit Mapper";
    ls->slotEditMemGB            = "Mapper Details ";
    ls->slotEditMemType          = "Type:";
    ls->slotEditMemFile          = "File:";
    ls->slotEditMemAddress       = "Address";
    ls->slotEditMemSize          = "Size";
    ls->slotEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Configuration";
    ls->confExitSaveTitle        = "blueMSX - Exit Configuration Editor";
    ls->confExitSaveText         = "Do you want to discard changes to the current configuration?";

    ls->confSaveAsMachineTitle   = "blueMSX - Save Machine Configuration As...";
    ls->confSaveAsMachineName    = "Machine Name:";

    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypes            = " Register file types with blueMSX (.rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " Automatic MSX function for Windows menu keys"; 
    ls->propWindowsEnvGB         = "Windows Environment "; 
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW accel."; 
    ls->propMonHorizStretch      = " Horizontal Stretch";
    ls->propMonVertStretch       = " Vertical Stretch";
    ls->propClearHistory         = "Are you sure you want to clear the file history ?";

    ls->propEmuFrontSwitchGB     = "Panasonic Switches ";
    ls->propEmuFrontSwitch       = " Front Switch";
    ls->propEmuAudioSwitch       = " MSX-AUDIO cartridge switch";


    ls->dlgCmosGB                = "CMOS ";
    ls->dlgCmosEnable            = " Enable CMOS";
    ls->dlgCmosBattery           = " Use Charged Battery";

    ls->menuCartSCCPlus         = "SCC+ Cartridge";
    ls->menuCartSCC             = "SCC Cartridge";
    
    ls->warningTitle             = "blueMSX - Warning";

    // New entries in 1.5.1
    ls->menuToolsShortcuts      = "Shortcuts Editor";

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
    ls->shortcutCartAutoReset   = "Reset Emulator when Cartridge is Inserted";
    ls->shortcutDiskInsertA     = "Insert Diskette A";
    ls->shortcutDiskRemoveA     = "Eject Diskette A";
    ls->shortcutDiskChangeA     = "Quick change Diskette A";
    ls->shortcutDiskAutoResetA  = "Reset Emulator when Diskette A is Inserted";
    ls->shortcutDiskInsertB     = "Insert Diskette B";
    ls->shortcutDiskRemoveB     = "Eject Diskette B";
    ls->shortcutCasInsert       = "Insert Cassette";
    ls->shortcutCasEject        = "Eject Cassette";
    ls->shortcutCasAutorewind   = "Toggle Auto-rewind on Cassette";
    ls->shortcutCasReadOnly     = "Toggle Read-only Cassette";
    ls->shortcutCasSetPosition  = "Set Tape position";
    ls->shortcutCasRewind       = "Rewind Cassette";
    ls->shortcutCasSave         = "Save Cassette Image";
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
    ls->shortcutResetClean      = "General Reset";
    ls->shortcutSizeSmall       = "Set small window size";
    ls->shortcutSizeNormal      = "Set normal window size";
    ls->shortcutSizeFullscreen  = "Set fullscreen";
    ls->shortcutToggleFullscren = "Toggle fullscreen";
    ls->shortcutVolumeIncrease  = "Increase Volume";
    ls->shortcutVolumeDecrease  = "Decrease Volume";
    ls->shortcutVolumeMute      = "Mute Volume";
    ls->shortcutSwitchMsxAudio  = "Toggle MSX-AUDIO switch";
    ls->shortcutSwitchFront     = "Toggle Panasonic front switch";
    ls->shortcutToggleMouseLock = "Toggle mouse lock";
    ls->shortcutEmuSpeedMax     = "Max emulation speed";
    ls->shortcutEmuSpeedToggle  = "Toggle max emulation speed";
    ls->shortcutEmuSpeedNormal  = "Normal emulation speed";
    ls->shortcutEmuSpeedInc     = "Increase emulation speed";
    ls->shortcutEmuSpeedDec     = "Decrease emulation speed";
    ls->shortcutShowEmuProp     = "Show Emulation Properties";
    ls->shortcutShowVideoProp   = "Show Video Properties";
    ls->shortcutShowAudioProp   = "Show Audio Properties";
    ls->shortcutShowCtrlProp    = "Show Controls Properties";
    ls->shortcutShowPerfProp    = "Show Performance Properties";
    ls->shortcutShowSettProp    = "Show Settings Properties";
    ls->shortcutShowLanguage    = "Show Language Dialog";
    ls->shortcutShowMachines    = "Show Machine Editor";
    ls->shortcutShowShortcuts   = "Show Shortcuts Editor";
    ls->shortcutShowHelp        = "Show Help Dialog";
    ls->shortcutShowAbout       = "Show About Dialog";
    
    ls->shortcutSpecialMenu1    = "Show Special Rom Menu for Cartridge 1";
    ls->shortcutSpecialMenu2    = "Show Special Rom Menu for Cartridge 2";
    ls->shortcutVolumeStereo    = "Toggle mono/stereo";
    ls->shortcutThemeSwitch     = "Switch theme";
    ls->shortcutToggleSpriteEnable = "Show/Hide Sprites";
    
    ls->shortcutShowApearProp   = "Show Appearance Properties";
    ls->menuPropsApearance      = "Appearance";
    ls->propApearance           = "Appearance";
    ls->propThemeGB             = "Theme ";
    ls->propTheme               = "Theme:";

    ls->propMonBrightness       = "Brightness:";
    ls->propMonContrast         = "Contrast:";
    ls->propMonSaturation       = "Saturation:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanlines:";

    ls->dlgRomType              = "Rom Type:";
    ls->propOpenRomGB           = "Open Rom Dialog ";
    ls->propDefaultRomType      = "Default Rom Type:";
    ls->propGuessRomType        = "Guess Rom Type";

    ls->propFile                = "Files";
    ls->propSettDefSlotGB       = "Drag and Drop ";
    ls->propSettDefSlots        = "Insert Rom Into:";
    ls->propSettDefSlot         = " Slot";
    ls->propSettDefDrives       = "Insert Diskette Into:";
    ls->propSettDefDrive        = " Drive";
    ls->menuPropsFile           = "Files";
    ls->shortcutShowFiles       = "Show Files Properties";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "Insert Directory";
    ls->shortcutDiskDirInsertA  = "Insert Directory as Diskette A";
    ls->shortcutDiskDirInsertB  = "Insert Directory as Diskette B";
    ls->propMonDeInterlace      = " De-interlace";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "Toggle pause switch";
    ls->shortcutSizeMinimized   = "Minimize window";
    ls->shortcutEmuSpeedToggle  = "Toggle max emulation speed";
    ls->shortcutToggleCpuTrace  = "Enable/Disable CPU Trace";

    ls->enumVideoEmuMonitor     = "Monitor";

    ls->propEmuPauseSwitch      = " Pause Switch";
    ls->propVideoFreqText       = "Video Frequency:";
    ls->propVideoFreqAuto       = "Auto";
    ls->propSndOversampleText   = "Oversample:";

    ls->confChipExtras          = "Extras";
    ls->confBoardGB             = "Board ";
    ls->confBoardText           = "Board Type:";
    ls->dlgCpuFreqGB            = "CPU Frequency ";
    ls->dlgZ80FreqText          = "Z80 Frequency:";
    ls->dlgR800FreqText         = "R800 Frequency:";
    ls->dlgFdcGB                = "Floppy Disk Controller ";
    ls->dlgCFdcNumDrivesText    = "Number of Drives:";

    ls->propPriorityBoost       = " Boost the priority of blueMSX";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "Disable Floppy Drive Timing";
    ls->shortcutToggleFdcTiming = "Enable/Disable Floppy Drive Timing";

    // New entries in 2.2
    ls->menuCartHBI55           = "Sony HBI-55 Cartridge";
    ls->propSndPcm              = " Turbo-R PCM";
    ls->propSndAY8910           = " AY8910 PSG";
    ls->propSndSN76489          = " SN76489 PSG";
    ls->enumVideoEmuHq2x        = "Hq2x";
    ls->propMonColorGhosting    = "RF-Modulator";

    ls->keyconfigSelectedKey    = "Selected Key:";
    ls->keyconfigMappedTo       = "Mapped To:";
    ls->keyconfigMappingScheme  = "Mapping Scheme:";

    ls->discardChanges          = "Do you want to discard changes?";
    ls->overwriteConfig         = "Do you want to overwrite the current configuration?";

    ls->confSaveAsTitle         = "Save Configuration As...";
    ls->confSaveAsName          = "Name:";

    ls->menuToolsKeyboard       = "Keyboard Editor";
    ls->shortcutShowKeyboard    = "Show Keyboard Editor";

    ls->menuVideoChipAutodetect = "Autodetect Video Chip";
    ls->propFullscreenResText   = "Fullscreen Resolution:";
    ls->dlgSavePreview          = "Show Preview";
    ls->dlgSaveDate             = "Time Saved:";
    
    ls->enumVideoMonAmber       = "Amber";

    ls->menuPropsPorts          = "Ports";
    ls->propPortsLptGB          = "Parallel port ";
    ls->propPortsComGB          = "Serial ports ";
    ls->propPortsLptText        = "Port:";
    ls->propPortsCom1Text       = "Port 1:";

    ls->shortcutShowDebugger    = "Show Debugger";
    ls->shortcutShowTrainer     = "Show Trainer";
    ls->shortcutShowPorts       = "Show Ports Properties";
    
    ls->propPorts               = "Ports";
    ls->propPortsNone           = "None";

    // New entries in 2.3
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle";

    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "Print to File";
    ls->propPortsOpenLogFile    = "Open Log File";
    ls->propPortsFilenameText   = "Filename:";
    ls->propPortsEmulateMsxPrn  = "Emulation:";

    ls->shortcutPrnFormFeed     = "Printer Form Feed";

    ls->menuPrnFormfeed         = "Form Feed";
    ls->menuFilePrn             = "Printer";
    ls->propPortsComFile        = "Send to File";

    // New entries in 2.4
    ls->shortcutShowMixer       = "Show Mixer";
    ls->menuToolsMixer          = "Mixer";
    
    ls->propSndMidiInGB         = "MIDI In ";
    ls->propSndMidiOutGB        = "MIDI Out ";
    ls->propSndMt32ToGmText     = " Map MT-32 instruments to General MIDI";

    ls->textDevice              = "Device:";
    ls->textFilename            = "Filename:";
    ls->textFile                = "File";
    ls->textNone                = "None";

    ls->enumEmuSyncNone         = "None";
    ls->enumEmuSyncAuto         = "Auto (fast)";
    ls->enumEmuSync1ms          = "Sync on MSX refresh";
    ls->enumEmuSyncVblank       = "Sync to PC Vertical Blank";

    ls->propMonEffectsGB        = "Effects ";
    
    ls->confSlot                = "Slot";
    ls->confSubslot             = "Subslot";

    ls->shortcut                = "Shortcut";
    ls->hotkey                  = "Hotkey";
    ls->unknown                 = "Unknown";
    ls->romImage                = "ROM image";
    ls->romImageOpen            = "Open ROM image";
    ls->romCartridge            = "ROM cartridge";
    ls->allFiles                = "All Files";
    ls->cpuState                = "CPU state";
    ls->diskImage               = "Disk Image";
    ls->casImage                = "Tape Image";

    ls->menuCartExternalRam     = "External RAM";

    // New entries in 2.5
    ls->menuCartGameReader      = "Game Reader";
    ls->menuDiskInsertNew       = "Insert New...";
    ls->menuCartIde             = "IDE";
    ls->menuCartSunriseIde      = "Sunrise";
    ls->menuCartBeerIde         = "Beer";
    ls->menuCartGIde            = "GIDE";
    ls->menuCartInsertSpecial   = "Insert Special";
    ls->menuCartMegaRam         = "MegaRAM";
    ls->menuFileHarddisk        = "Hard Disk";
    ls->menuFileHarddiskNoPesent= "No Controllers Present";
    ls->dlgInsertHarddisk       = "Insert Hard Disk";

    ls->menuVideoSource         = "Video Out Source";
    ls->menuVideoSourceDefault  = "No Video Out Source Connected";
    
    ls->menuVideoInSource       = "Video In Source";
    ls->menuVideoInBitmap       = "Bitmap File";

    ls->textUnknown             = "Unknown";

    ls->overwriteFile           = "Do you want to overwrite the file:";

    ls->portableReadonly        = "Portable device is readonly";
    
    ls->propScreenshotPng       = " Use Portable Network Graphics (.png) screenshots";

    ls->enumControlsJoyTMagicKeyDongle = "MagicKey Dongle";
};


#endif

