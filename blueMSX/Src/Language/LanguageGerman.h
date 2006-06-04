/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageGerman.h,v $
**
** $Revision: 1.12 $ 
**
** $Date: 2006-06-04 01:18:57 $
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
#ifndef LANGUAGE_GERMAN_H
#define LANGUAGE_GERMAN_H

#include "LanguageStrings.h"
 
void langInitGerman(LanguageStrings* ls) 
{
    //----------------------
    // Generic lines
    //----------------------

    //----------------------
    // Warning and Error lines
    //----------------------

    //----------------------
    // File related lines
    //----------------------

    //----------------------
    // Menu related lines
    //----------------------

    //----------------------
    // Dialog related lines
    //----------------------

    //----------------------
    // Properties related lines
    //----------------------

    //----------------------
    // Dropdown related lines
    //----------------------

    //----------------------
    // Configuration related lines
    //----------------------

    //----------------------
    // Shortcut lines
    //----------------------

    //----------------------
    // Keyboard config lines
    //----------------------

    ls->menuNoRecentFiles       = "- keine neuen Files -";
    ls->menuInsert              = "Einf�gen";
    ls->menuEject               = "Auswurf";

    ls->menuCartAutoReset       = "Reset nach Einf�gen/Entfernen";
    ls->menuCartFMPac           = "FM-PAC-Cartridge";
    ls->menuCartPac             = "PAC-Cartridge";

    ls->menuDiskAutoStart       = "Reset nach Einf�gen";
    
    ls->menuCasSetPosition      = "Positionieren";
    ls->menuCasRewind           = "Zur�ck";

    ls->menuZoomNormal          = "Normale Gr��e";
    ls->menuZoomDouble          = "Doppelte Gr��e";
    ls->menuZoomFullscreen      = "Ganzer Bildschirm";
    
    ls->menuPropsEmulation      = "Emulation";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Sound";
    ls->menuPropsControls       = "Controls";
    ls->menuPropsPerformance    = "Performance";
    ls->menuPropsLanguage       = "Sprache";
    ls->menuPropsPorts          = "Ports";
    
    ls->menuHelpHelp            = "Hilfethemen";
    ls->menuHelpAbout           = "�ber blueMSX";

    ls->menuFileCart            = "Cartridge Slot";
    ls->menuFileDisk            = "Disk Drive";
    ls->menuFileCas             = "Cassette";
    ls->menuFileLoadState       = "Lade CPU-Status";
    ls->menuFileSaveState       = "Speichere CPU-Status";
    ls->menuFileQLoadState      = "Quick Load State";
    ls->menuFileQSaveState      = "Quick Save State";
    ls->menuFileCaptureAudio    = "Capture Audio";
    ls->menuFileScreenShot      = "Speichere Screenshot";
    ls->menuFileExit            = "Exit";

    ls->menuRunRun              = "Start";
    ls->menuRunPause            = "Pause";
    ls->menuRunStop             = "Stopp";
    ls->menuRunSoftReset        = "Soft Reset";
    ls->menuRunHardReset        = "Hard Reset";
    ls->menuRunCleanReset       = "Allgemeiner Reset";

    ls->menuFile                = "File";
    ls->menuRun                 = "Run";
    ls->menuWindow              = "Window";
    ls->menuOptions             = "Options";
    ls->menuHelp                = "Help";
    
    ls->errorTitle              = "blueMSX - Fehler";
    ls->errorEnterFullscreen    = "Konnte nicht in den Fullscreen-Modus gehen.           \n";
    ls->errorDirectXFailed      = "DirectX objects konnten nicht erzeugt werden.\nBenutze stattdessen GDI.\n�berpr�fe die Video-Eigenschaften.";
    ls->errorNoRomInZip         = "Konnte kein .rom-File im Zip-Archiv finden.";
    ls->errorNoDskInZip         = "Konnte kein .dsk-File im Zip-Archiv finden.";
    ls->errorNoCasInZip         = "Konnte kein .cas-File im Zip-Archiv finden.";
    ls->errorNoHelp             = "Konnte kein blueMSX-Hilfe-File finden.";
    ls->errorStartEmu           = "Der MSX-Emulator konnte nicht gestartet werde.";


    ls->dlgLoadRom              = "blueMSX - W�hle ein ROM-Image aus";
    ls->dlgLoadDsk              = "blueMSX - W�hle ein DSK-Image aus";
    ls->dlgLoadCas              = "blueMSX - W�hle ein CAS-Image aus";
    ls->dlgLoadRomDskCas        = "blueMSX - W�hle ein ROM-, DSK- oder CAS- File zum Laden aus";
    ls->dlgLoadRomDesc          = "W�hle ein ROM-Image aus:";
    ls->dlgLoadDskDesc          = "W�hle ein DISK-Image aus:";
    ls->dlgLoadCasDesc          = "W�hle ein CASSETTEN-Image aus:";
    ls->dlgLoadRomDskCasDesc    = "W�hle ein ROM-, DSK- oder CAS- File zum Laden aus:";
    ls->dlgLoadState            = "Lade CPU-Status";
    ls->dlgSaveState            = "Speichere CPU-Status";
    ls->dlgInsertRom1           = "ROM-Cartridge in Slot 1 einf�gen";
    ls->dlgInsertRom2           = "ROM-Cartridge in Slot 2 einf�gen";
    ls->dlgInsertDiskA          = "Disketten-Image in Laufwerk A einf�gen";
    ls->dlgInsertDiskB          = "Disketten-Image in Laufwerk B einf�gen";
    ls->dlgInsertCas            = "Cassette einf�gen";

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "�ffnen";
    ls->dlgCancel               = "Abbrechen";

    ls->dlgTapeTitle            = "blueMSX - Bandposition";
    ls->dlgTapeFrameText        = "Bandposition";
    ls->dlgTapeCurrentPos       = "Aktuelle Position";
    ls->dlgTapeTotalTime        = "Gesamtzeit";

    ls->dlgZipReset             = "Reset nach Einf�gen";

    ls->dlgAboutTitle           = "�ber blueMSX";

    ls->dlgLangLangText         = "W�hle die Sprache aus, die blueMSX benutzen soll.";
    ls->dlgLangLangTitle        = "blueMSX - Sprache";

    ls->propTitle               = "blueMSX - Eigenschaften";
    ls->propEmulation           = "Emulation";
    ls->propVideo               = "Video";
    ls->propSound               = "Sound";
    ls->propControls            = "Controls";
    ls->propPerformance         = "Performance";
    ls->propPorts               = "Ports";
    
    ls->propEmuGeneralGB        = "Allgemeines ";
    ls->propEmuFamilyText       = "MSX-Maschine:";
    ls->propEmuMemoryGB         = "Memory ";
    ls->propEmuRamSizeText      = "RAM size:";
    ls->propEmuVramSizeText     = "VRAM size:";
    ls->propEmuSpeedGB          = "Emulationsgeschwindigkeit ";
    ls->propEmuSpeedText        = "Emulationsgeschwindigkeit:";

    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Typ des Monitors:";
    ls->propMonEmuText          = "Monitoremulation:";
    ls->propVideoTypeText       = "Videotyp:";
    ls->propWindowSizeText      = "Fenstergr��e:";

    ls->propPerfVideoDrvGB      = "Video-Treiber ";
    ls->propPerfVideoDispDrvText= "Display-Treiber:";
    ls->propPerfFrameSkipText   = "Frame skipping:";
    ls->propPerfAudioDrvGB      = "Audio-Treiber ";
    ls->propPerfAudioDrvText    = "Sound-Treiber:";
    ls->propPerfAudioBufSzText  = "Gr��e des Sound-Buffers:";
    ls->propPerfEmuGB           = "Emulation ";
    ls->propPerfSyncModeText    = "SYNC-Mode:";

    ls->propSndChipEmuGB        = "Emulation des Sound-Chips ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";

    ls->propPortsLptGB          = "Paralleler Port ";
    ls->propPortsComGB          = "Serielle Ports ";
    ls->propPortsLptText        = "Port:";
    ls->propPortsCom1Text       = "Port 1:";

    ls->enumVideoMonColor       = "Farbe";
    ls->enumVideoMonGrey        = "Schwarzwei�";
    ls->enumVideoMonGreen       = "Gr�n";
    ls->enumVideoMonAmber       = "Amber";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Nichts";
    ls->enumVideoEmuYc          = "Y/C-Kabel (scharf)";
    ls->enumVideoEmuYcBlur      = "Verrauschtes Y/C-Kabel (scharf)";
    ls->enumVideoEmuComp        = "Composit-Signal (verwaschen)";
    ls->enumVideoEmuCompBlur    = "Verrauschtes Composit-Signal (verwaschen)";
    ls->enumVideoEmuScale2x     = "Scale 2x";

    ls->enumVideoSize1x         = "Normal - 320x200";
    ls->enumVideoSize2x         = "Double - 640x400";
    ls->enumVideoSizeFullscreen = "Fullscreen";

    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "Nichts";
    ls->enumVideoFrameskip1     = "1 Frame";
    ls->enumVideoFrameskip2     = "2 Frames";
    ls->enumVideoFrameskip3     = "3 Frames";
    ls->enumVideoFrameskip4     = "4 Frames";
    ls->enumVideoFrameskip5     = "5 Frames";

    ls->enumSoundDrvNone        = "Kein Sound";
    ls->enumSoundDrvWMM         = "WMM-Treiber";
    ls->enumSoundDrvDirectX     = "DirectX-Treiber";

    ls->enumEmuSync1ms          = "1ms (am besten)";
    ls->enumEmuSyncAuto         = "Auto (schnell)";

    ls->enumControlsJoyNone     = "Nichts";
    ls->enumControlsJoyMouse    = "Maus";

    ls->dlgAboutAbout           = "�BER\r\n====";
    ls->dlgAboutVersion         = "Version:";
    ls->dlgAboutBuildNumber     = "Hergestellt:";
    ls->dlgAboutBuildDate       = "Datum:";
    ls->dlgAboutCreat           = "von Daniel Vik";
    ls->dlgAboutDevel           = "ENTWICKLER\r\n========";
    ls->dlgAboutThanks          = "BESONDEREN DANK AN\r\n============";
    ls->dlgAboutLisence         = "LIZENZ\r\n"
                                  "======\r\n\r\n"
                                  "Diese Software wird ''wie sie ist'' zur Verf�gung gestellt, ohne jegliche Garantie."
                                  "In keinem Fall wird der Autor/werden die Autoren haftpflichtig f�r irgendwelche Sch�den,"
                                  "die aus dem Gebrauch dieser Software entstehen k�nnten.\r\n\r\n"
                                  "Besuchen Sie www.bluemsx.com, um n�here Details zu erfahren.";

    // New entries
    ls->menuTools                = "Tools";
    ls->menuToolsMachine         = "Maschineneditor";
    ls->menuPropsSettings        = "Einstellungen";
    ls->menuCasRewindAfterInsert = "Zur�ck nach Einf�gen";
    ls->menuCasUseReadOnly       = "Cassetten-Image nur lesend benutzen";
    ls->lmenuCasSaveAs           = "Speichere Cassetten-Image als ...";

    ls->dlgSaveCassette          = "blueMSX - Speichere Tape-Image";
    ls->dlgTapeCustom            = "Zeige anwenderspezifische Files";
    ls->dlgTapeSetPosText        = "Bandposition:";
    ls->dlgTabPosition           = "Position";
    ls->dlgTabType               = "Typ";
    ls->dlgTabFilename           = "Filename";

    ls->propSettings             = "Einstellungen";
    
    ls->propSetFileHistoryGB     = "File History ";
    ls->propSetFileHistorySize   = "Anzahl der Elemente in der File-History:";
    ls->propSetFileHistoryClear  = "L�sche History";
    ls->propSetScreenSaver       = " Schalte den Bildschirmschoner ab, wenn blueMSX l�uft";

    ls->confTitle                = "blueMSX - Editor f�r die Maschinenkonfiguration";
    ls->confSave                 = "Speichern";
    ls->confSaveAs               = "Speichern als ...";
    ls->confRun                  = "Start";
    ls->confClose                = "Schlie�en";
    ls->confConfigText           = "Konfiguration";
    ls->confSlotLayout           = "Slot-Layout";
    ls->confMemory               = "Memory";
    ls->confChipEmulation        = "Chip-Emulation";

    ls->confSlotLayoutGB         = "Slot-Layout ";
    ls->confSlotExtSlotGB        = "Externe Slots ";
    ls->confSlotCart             = "Cartridge";
    ls->confSlotPrimary          = "Primary";
    ls->confSlotExpanded         = "Expanded (vier Subslots)";

    ls->confMemAdd               = "Hinzuf�gen ...";
    ls->confMemEdit              = "Editieren ...";
    ls->confMemRemove            = "Entfernen";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Addresse";
    ls->confMemType              = "Typ";
    ls->confMemRomImage          = "ROM-Image";
    
    ls->confSaveTitle            = "blueMSX - Speichere Konfiguration";
    ls->confSaveText             = "M�chten Sie die Maschinenkonfiguration �berschreiben?";

    ls->confChipVideoGB          = "Video ";
    ls->confChipVideoChip        = "Video-Chip:";
    ls->confChipVideoRam         = "Video-RAM:";
    ls->confChipSoundGB          = "Sound ";

    ls->confEditMemTitle         = "blueMSX - Edit Mapper";
    ls->confEditMemGB            = "Mapper Details ";
    ls->confEditMemType          = "Typ:";
    ls->confEditMemFile          = "File:";
    ls->confEditMemAddress       = "Addresse";
    ls->confEditMemSize          = "Gr��e";
    ls->confEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Konfiguration";
    ls->confExitSaveTitle        = "blueMSX - Konfigurationseditor verlassen";
    ls->confExitSaveText         = "M�chten Sie die aktuellen �nderungen der Konfiguration verwerfen?";

    ls->confSaveAsMachineName    = "Name der Maschine:";

    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypes            = " Registriere Filetypen mit blueMSX (.rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " Automatische MSX-Function f�r Windows-Men�tasten"; 
    ls->propWindowsEnvGB         = "Windows-Environment "; 
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW accel."; 
    ls->propMonHorizStretch      = " Horizontal Stretch";
    ls->propMonVertStretch       = " Vertical Stretch";
    ls->propClearHistory         = "Sind Sie sicher, da� Sie die File-History l�schen wollen?";

    ls->propEmuFrontSwitchGB     = "Panasonic Switches ";
    ls->propEmuFrontSwitch       = " Front Switch";
    ls->propEmuAudioSwitch       = " MSX-AUDIO cartridge switch";

    ls->confCmosGB                = "CMOS ";
    ls->confCmosEnable            = " CMOS einschalten";
    ls->confCmosBattery           = " Verwende geladene Batterie";

    ls->menuCartSCCPlus         = "SCC+ Cartridge";
    ls->menuCartSCC             = "SCC Cartridge";
    
    ls->warningTitle             = "blueMSX - Warnung";

    // New entries in 1.5.1
    ls->menuToolsShortcuts      = "Shortcuts-Editor";

    ls->shortcutSaveConfig      = "blueMSX - Speichere Konfiguration";
    ls->shortcutOverwriteConfig = "M�chten Sie die Shortcut-Konfiguration �berschreiben:";
    ls->shortcutExitConfig      = "blueMSX - Exit Shortcut Editor";
    ls->shortcutDiscardConfig   = "M�chten Sie die �nderungen an der aktuellen Konfiguration verwerfen?";
    ls->shortcutSaveConfigAs    = "blueMSX - Speichere Shortcut-Konfiguration als ...";
    ls->shortcutConfigName      = "Konfigurationsname:";
    ls->shortcutNewProfile      = "< Neues Profil >";
    ls->shortcutConfigTitle     = "blueMSX - Shortcut Mapping Editor";
    ls->shortcutAssign          = "Zuweisen";
    ls->shortcutPressText       = "Dr�cke Shortcut-Taste(n):";
    ls->shortcutScheme          = "Mapping Scheme:";

    ls->shortcutCartInsert1     = "Cartridge 1 einf�gen";
    ls->shortcutCartRemove1     = "Cartridge 1 entfernen";
    ls->shortcutCartInsert2     = "Cartridge 2 einf�gen";
    ls->shortcutCartRemove2     = "Cartridge 2 entfernen";
    ls->shortcutCartAutoReset   = "Emulator zur�cksetzen, wenn Cartridge eingef�gt wird";
    ls->shortcutDiskInsertA     = "Diskette A einf�gen";
    ls->shortcutDiskRemoveA     = "Diskette A auswerfen";
    ls->shortcutDiskChangeA     = "Schneller Austausch von Diskette A";
    ls->shortcutDiskAutoResetA  = "Emulator zur�cksetzen, wenn Diskette A eingef�gt wird";
    ls->shortcutDiskInsertB     = "Diskette B einf�gen";
    ls->shortcutDiskRemoveB     = "Diskette B auswerfen";
    ls->shortcutCasInsert       = "Cassette einf�gen";
    ls->shortcutCasEject        = "Cassette auswerfen";
    ls->shortcutCasAutorewind   = "Toggle Auto-rewind on Cassette";
    ls->shortcutCasReadOnly     = "Toggle Read-only Cassette";
    ls->shortcutCasSetPosition  = "Bandposition festlegen";
    ls->shortcutCasRewind       = "Cassette zur�ckspulen";
    ls->shortcutCasSave         = "Cassetten-Image speichern";
    ls->shortcutCpuStateLoad    = "CPU-Status laden";
    ls->shortcutCpuStateSave    = "CPU-Status speichern";
    ls->shortcutCpuStateQload   = "Schnelladen des CPU-Status";
    ls->shortcutCpuStateQsave   = "Schnellspeichern des CPU-Status";
    ls->shortcutAudioCapture    = "Start/stop audio capture";
    ls->shortcutScreenshotOrig  = "Screenshot capture";
    ls->shortcutScreenshotSmall = "Small unfiltered screenshot capture";
    ls->shortcutScreenshotLarge = "Large unfiltered screenshot capture";
    ls->shortcutQuit            = "blueMSX verlassen";
    ls->shortcutRunPause        = "Start/Unterbrechung der Emulation";
    ls->shortcutStop            = "Emulation stoppen";
    ls->shortcutResetHard       = "Hard-Reset";
    ls->shortcutResetSoft       = "Soft-Reset";
    ls->shortcutResetClean      = "Allgemeiner Reset";
    ls->shortcutSizeSmall       = "Kleine Fenstergr��e einstellen";
    ls->shortcutSizeNormal      = "Normale Fenstergr��e einstellen";
    ls->shortcutSizeFullscreen  = "Volle Bildschirmgr��e einstellen";
    ls->shortcutToggleFullscren = "Bildschirmgr��e umschalten";
    ls->shortcutVolumeIncrease  = "Lautst�rke erh�hen";
    ls->shortcutVolumeDecrease  = "Lautst�rke vermindern";
    ls->shortcutVolumeMute      = "Ton abschalten";
    ls->shortcutSwitchMsxAudio  = "Toggle MSX-AUDIO switch";
    ls->shortcutSwitchFront     = "Toggle Panasonic front switch";
    ls->shortcutToggleMouseLock = "Maussperre umschalten";
    ls->shortcutEmuSpeedMax     = "Max. Emulationsgeschwindigkeit";
    ls->shortcutEmuSpeedToggle  = "Max. Emulationsgeschwindigkeit umschalten";
    ls->shortcutEmuSpeedNormal  = "Normale Emulationsgeschwindigkeit";
    ls->shortcutEmuSpeedInc     = "Emulationsgeschwindigkeit erh�hen";
    ls->shortcutEmuSpeedDec     = "Emulationsgeschwindigkeit vermindern";
    ls->shortcutShowEmuProp     = "Zeige Emulationseigenschaften";
    ls->shortcutShowVideoProp   = "Zeige Video-Eigenschaften";
    ls->shortcutShowAudioProp   = "Zeige Audio-Eigenschaften";
    ls->shortcutShowCtrlProp    = "Zeige Control-Eigenschaften";
    ls->shortcutShowPerfProp    = "Zeige Leistungseigenschaften";
    ls->shortcutShowSettProp    = "Zeige Einstellungseigenschaften";
    ls->shortcutShowLanguage    = "Zeige Sprachdialog";
    ls->shortcutShowMachines    = "Zeige Maschineneditor";
    ls->shortcutShowShortcuts   = "Zeige Shortcuts-Editor";
    ls->shortcutShowHelp        = "Zeige Hilfe-Dialog";
    ls->shortcutShowAbout       = "Zeige ''About''-Dialog";
    
    ls->shortcutSpecialMenu1    = "Zeige spezielles ROM-Men� f�r Cartridge 1";
    ls->shortcutSpecialMenu2    = "Zeige spezielles ROM-Men� f�r Cartridge 2";
    ls->shortcutVolumeStereo    = "Mono/Stereo umschalten";
    ls->shortcutThemeSwitch     = "Switch theme";
    ls->shortcutToggleSpriteEnable = "Sprites zeigen/verdecken";
    
    ls->shortcutShowApearProp   = "Zeige Appearance-Eigenschaften";
    ls->menuPropsApearance      = "Appearance";
    ls->propThemeGB             = "Theme ";
    ls->propTheme               = "Theme:";

    ls->propMonBrightness       = "Helligkeit:";
    ls->propMonContrast         = "Kontrast:";
    ls->propMonSaturation       = "S�ttigung:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanlines:";

    ls->dlgRomType              = "Typ des ROMs:";
    ls->propOpenRomGB           = "�ffne ROM-Dialog ";
    ls->propDefaultRomType      = "Voreingestellter ROM-Typ:";
    ls->propGuessRomType        = "ROM-Typ erraten";

    ls->propFile                = "Files";
    ls->propSettDefSlotGB       = "Drag and Drop ";
    ls->propSettDefSlots        = "ROM einf�gen in:";
    ls->propSettDefSlot         = " Slot";
    ls->propSettDefDrives       = "Disketten einf�gen in:";
    ls->propSettDefDrive        = " Drive";
    ls->menuPropsFile           = "Files";
    ls->shortcutShowFiles       = "Zeige Fileeigenschaften";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "Directory einf�gen";
    ls->shortcutDiskDirInsertA  = "Directory als Diskette A einf�gen";
    ls->shortcutDiskDirInsertB  = "Directory als Diskette B einf�gen";
    ls->propMonDeInterlace      = " De-interlace";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "Unterbrechungstaste umschalten";
    ls->shortcutSizeMinimized   = "Fenster minimieren";
    ls->shortcutEmuSpeedToggle  = "Max. Emulationsgeschwindigkeit umschalten";
    ls->shortcutToggleCpuTrace  = "Enable/Disable CPU Trace";

    ls->enumVideoEmuMonitor     = "Monitor";

    ls->propEmuPauseSwitch      = " Unterbrechungstaste";
    ls->propVideoFreqText       = "Video-Frequenz:";
    ls->propVideoFreqAuto       = "Auto";
    ls->propSndOversampleText   = "Oversample:";

    ls->confChipExtras          = "Extras";
    ls->confBoardGB             = "Board ";
    ls->confBoardText           = "Board-Typ:";
    ls->confCpuFreqGB            = "CPU-Frequenz ";
    ls->confZ80FreqText          = "Z80-Frequenz:";
    ls->confR800FreqText         = "R800-Frequenz:";
    ls->confFdcGB                = "Floppy-Disk-Controller ";
    ls->confCFdcNumDrivesText    = "Anzahl der Laufwerke:";

    ls->propPriorityBoost       = " Die Priorit�t von blueMSX erh�hen";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "Floppy-Drive-Timing sperren";
    ls->shortcutToggleFdcTiming = "Freigabe/Sperren des Floppy-Drive-Timings";

    // New entries in 2.2
    ls->menuCartHBI55           = "Sony HBI-55 Cartridge";
    ls->enumVideoEmuHq2x        = "Hq2x";
    ls->propMonColorGhosting    = "RF-Modulator";

    ls->keyconfigSelectedKey    = "Selected Key:";
    ls->keyconfigMappedTo       = "Mapped To:";
    ls->keyconfigMappingScheme  = "Mapping Scheme:";

    ls->warningDiscardChanges   = "M�chten Sie die �nderungen verwerfen?";

    ls->confSaveAsTitle         = "Speichere Konfiguration als ...";

    ls->menuToolsKeyboard       = "Keyboard-Editor";
    ls->shortcutShowKeyboard    = "Zeige Keyboard-Editor";

    ls->menuVideoSource         = "Video-Quelle";
    ls->menuVideoSourceDefault  = "Keine Video-Quelle angeschlossen";
    ls->menuVideoChipAutodetect = "Autodetect Video-Chip";
    ls->propFullscreenResText   = "Bildschirmaufl�sung:";
    ls->dlgSavePreview          = "Zeige Preview";
    ls->dlgSaveDate             = "Eingesparte Zeit:";

    ls->enumVideoMonAmber       = "Amber"; 

    ls->menuPropsPorts          = "Ports"; 
    ls->propPortsLptGB          = "Paralleler Port "; 
    ls->propPortsComGB          = "Serielle Ports "; 
    ls->propPortsLptText        = "Port:"; 
    ls->propPortsCom1Text       = "Port 1:";

    ls->shortcutShowDebugger    = "Zeige Debugger";
    ls->shortcutShowTrainer     = "Zeige Trainer";
    ls->shortcutShowPorts       = "Zeige Ports-Eigenschaften";

    ls->propPorts               = "Ports";
    ls->propPortsNone           = "Nichts";

    // New entries in 2.3
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle";

    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "In Datei schreiben";
    ls->propPortsOpenLogFile    = "�ffne Log-Datei";
    ls->propPortsEmulateMsxPrn  = "Emulation:";

    ls->shortcutPrnFormFeed     = "Seitenvorschub des Druckers";

    ls->menuPrnFormfeed         = "Seitenvorschub";
    ls->menuFilePrn             = "Drucker";
    ls->propPortsComFile        = "Zu Datei senden";

    // New entries in 2.4
    ls->shortcutShowMixer       = "Zeige Audio-Mixer";
    ls->menuToolsMixer          = "Audio-Mixer";
    
    ls->propSndMidiInGB         = "MIDI In ";
    ls->propSndMidiOutGB        = "MIDI Out ";
    ls->propSndMt32ToGm         = " Map MT-32 instruments to General MIDI";

    ls->textDevice              = "Typ:";
    ls->textFilename            = "Filename:";
    ls->textFile                = "File";
    ls->textNone                = "Nichts";    

    ls->enumEmuSyncNone         = "Nichts";
    ls->enumEmuSyncAuto         = "Automatisch (schnell)";
    ls->enumEmuSync1ms          = "Sync am MSX refresh";
    ls->enumEmuSyncVblank       = "Sync am PC Vertical Blank";

    ls->propMonEffectsGB        = "Effects ";
    
    ls->confSlot                = "Slot";
    ls->confSubslot             = "Subslot";

    ls->shortcutDescription     = "Shortcut";
    ls->shortcutKey             = "Kontrollsequenz";

    ls->fileRom                 = "ROM-Image";
    ls->confOpenRom             = "�ffnen ROM-Image";
    ls->fileAll                 = "All Files";
    ls->fileCpuState            = "CPU-Status";
    ls->fileDisk                = "Diskette-Image";
    ls->fileCas                 = "Cassette-Image";

    ls->menuCartExternalRam     = "Externes RAM";
};



#endif



