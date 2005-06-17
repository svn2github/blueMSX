/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageGerman.h,v $
**
** $Revision: 1.3 $ 
**
** $Date: 2005-06-17 19:29:32 $
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
    ls->statusBarStopped        = "  Gestoppt";
    ls->statusBarPaused         = "  Unterbrochen";
    ls->statusBarRunning        = "  L�uft";

    ls->menuHardReset           = "Hard Reset";
    ls->menuSoftReset           = "Soft Reset";
    
    ls->menuCartInsert          = "Einf�gen";
    ls->menuCartRemove          = "Entfernen";
    ls->menuCartAutoReset       = "Reset nach Einf�gen/Entfernen";
    ls->menuCartNoRecentFiles   = "- keine neuen Files -";
    ls->menuCartFMPac           = "FM-PAC-Cartridge";
    ls->menuCartPac             = "PAC-Cartridge";
    ls->menuCartSpecial         = "Spezial";

    ls->menuDiskInsert          = "Einf�gen";
    ls->menuDiskEject           = "Auswurf";
    ls->menuDiskAutoStart       = "Reset nach Einf�gen";
    ls->menuDiskNoRecentFiles   = "- keine neuen Files -";
    
    ls->menuCasInsert           = "Einf�gen";
    ls->menuCasEject            = "Auswurf";
    ls->menuCasSetPosition      = "Positionieren";
    ls->menuCasRewind           = "Zur�ck";
    ls->menuCasNoRecentFiles    = "- keine neuen Files -";

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

    ls->menuFileCart1           = "Cartridge Slot 1";
    ls->menuFileCart2           = "Cartridge Slot 2";
    ls->menuFileDiskA           = "Disk Drive A";
    ls->menuFileDiskB           = "Disk Drive B";
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

    ls->tooltipReset            = "Reset MSX";
    ls->tooltipCart1            = "Cartridge in Slot 1 einf�gen";
    ls->tooltipCart2            = "Cartridge in Slot 2 einf�gen";
    ls->tooltipDiskA            = "Diskette in Laufwerk A einf�gen";
    ls->tooltipDiskB            = "Diskette in Laufwerk B einf�gen";
    ls->tooltipCas              = "Cassette in den Cassettenrecorder einlegen";
    ls->tooltipStart            = "Starte Emulation";
    ls->tooltipResume           = "Emulation fortsetzen";
    ls->tooltipPause            = "Emulation unterbrechen";
    ls->tooltipWindowSize       = "Fenstergr��e einstellen";
    ls->tooltipProperties       = "�ffne den Eigenschaften-Dialog";
    ls->tooltipHelp             = "�ffne das Hilfe-Fenster";

    ls->dlgMainWindow           = "  blueMSX";
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

    ls->dlgJoyTitle1            = "blueMSX - Joystick-Keyset A";
    ls->dlgJoyTitle2            = "blueMSX - Joystick-Keyset B";
    ls->dlgJoyUpText            = "hoch";
    ls->dlgJoyDownText          = "runter";
    ls->dlgJoyLeftText          = "links";
    ls->dlgJoyRightText         = "rechts";
    ls->dlgJoyButton1Text       = "Button 1";
    ls->dlgJoyButton2Text       = "Button 2";
    ls->dlgJoyGB                = "Keyset Configuration ";

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
    ls->propVideoYypeText       = "Videotyp:";
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
    ls->propSndMixerGB          = "Audio-Mixer ";
    ls->propSndMonoText         = "mono";
    ls->propSndStereoText       = "stereo";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "MASTER";

    ls->propJoyPort1GB          = "Port #1 ";
    ls->propJoyPort2GB          = "Port #2 ";
    ls->propJoyAutofireText     = "Autofire:";
    ls->propJoyKeysetGB         = "Joystick-Keysets ";
    ls->propJoyKeyest1          = "Konfiguriere Keyset A";
    ls->propJoyKeyest2          = "Konfiguriere Keyset B";

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
    ls->enumControlsJoyNumpad   = "Zehnerblock";
    ls->enumControlsJoyKeysetA  = "Keyset A";
    ls->enumControlsJoyKeysetB  = "Keyset B";
    ls->enumControlsJoyPCjoy1   = "PC-Joystick #1";
    ls->enumControlsJoyPCjoy2   = "PC-Joystick #2";
    ls->enumControlsJoyMouse    = "Maus";

    ls->enumControlsAfOff       = "Aus";
    ls->enumControlsAfSlow      = "Langsam";
    ls->enumControlsAfMedium    = "Mittel";
    ls->enumControlsAfFast      = "Schnell";

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
    ls->propSetScreenSaverGB     = "Bildschirmschoner ";
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
    ls->confSlotSlot0            = "Slot 0";
    ls->confSlotSlot1            = "Slot 1";
    ls->confSlotSlot2            = "Slot 2";
    ls->confSlotSlot3            = "Slot 3";
    ls->confSlotCart1            = "Cartridge 1:";
    ls->confSlotCart2            = "Cartridge 2:";
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

    ls->slotEditMemTitle         = "blueMSX - Edit Mapper";
    ls->slotEditMemGB            = "Mapper Details ";
    ls->slotEditMemType          = "Typ:";
    ls->slotEditMemFile          = "File:";
    ls->slotEditMemAddress       = "Addresse";
    ls->slotEditMemSize          = "Gr��e";
    ls->slotEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Konfiguration";
    ls->confExitSaveTitle        = "blueMSX - Konfigurationseditor verlassen";
    ls->confExitSaveText         = "M�chten Sie die aktuellen �nderungen der Konfiguration verwerfen?";

    ls->confSaveAsMachineTitle   = "blueMSX - Speichere Maschinenkonfiguration als ...";
    ls->confSaveAsMachineName    = "Name der Maschine:";

    ls->confEditMemInternalRoms  = "blueMSX - Interne ROMs";
    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypesGB          = "Filetypen ";
    ls->propFileTypes            = " Registriere Filetypen mit blueMSX (.rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " Automatische MSX-Function f�r Windows-Men�tasten"; 
    ls->propWindowsEnvGB         = "Windows-Environment "; 
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW accel."; 
    ls->enumVideoDrvDirectDrawHWSys = "DirectDraw mix."; 
    ls->propMonHorizStretch      = " Horizontal Stretch";
    ls->propMonVertStretch       = " Vertical Stretch";
    ls->propClearHistory         = "Sind Sie sicher, da� Sie die File-History l�schen wollen?";

    ls->propEmuFrontSwitchGB     = "Panasonic Switches ";
    ls->propEmuFrontSwitch       = " Front Switch";
    ls->propEmuAudioSwitch       = " MSX-AUDIO cartridge switch";

    ls->dlgCmosGB                = "CMOS ";
    ls->dlgCmosEnable            = " CMOS einschalten";
    ls->dlgCmosBattery           = " Verwende geladene Batterie";

    ls->menuCartSnatcher        = "The Snatcher Cartridge";
    ls->menuCartSdSnatcher      = "SD-Snatcher Cartridge";
    ls->menuCartSCCMirrored     = "SCC Mirrored Cartridge";
    ls->menuCartSCCExpanded     = "SCC Expanded Cartridge";
    ls->menuCartSCCPlus         = "SCC+ Cartridge";
    ls->menuCartSCC             = "SCC Cartridge";
    
    ls->warningTitle             = "blueMSX - Warnung";
    ls->tooltipStop             = "Stoppe Emulation";

    // New entries in 1.5.1
    ls->enumControlsJoyKeyset   = "Keyset";    
    ls->propJoyConfigKeyset     = "Konfiguriere Keyset";
    ls->propJoyControlText      = "Control:";
    ls->propJoyButtonText       = "Button";
    ls->propJoyButtonAText      = "Button A:";
    ls->propJoyButtonBText      = "Button B:";

    ls->menuToolsShortcuts      = "Shortcuts-Editor";

    ls->shortcutSaveConfig      = "blueMSX - Speichere Konfiguration";
    ls->shortcutOverwriteConfig = "M�chten Sie die Shortcut-Konfiguration �berschreiben:";
    ls->shortcutExitConfig      = "blueMSX - Exit Shortcut Editor";
    ls->shortcutDiscardConfig   = "M�chten Sie die �nderungen an der aktuellen Konfiguration verwerfen?";
    ls->shortcutSaveConfigAs    = "blueMSX - Speichere Shortcut-Konfiguration als ...";
    ls->shortcutConfigName      = "Konfigurationsname:";
    ls->shortcutNewProfile      = "< Neues Profile >";
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
    ls->propApearance           = "Appearance";
    ls->propThemeGB             = "Theme ";
    ls->propTheme               = "Theme:";
    ls->propThemeClassic        = "Classic";
    ls->propThemeBlue           = "DIGIDIGIblue";

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
    ls->propSettDefSlot1        = " Slot 1";
    ls->propSettDefSlot2        = " Slot 2";
    ls->propSettDefDrives       = "Disketten einf�gen in:";
    ls->propSettDefDriveA       = " Drive A";
    ls->propSettDefDriveB       = " Drive B";
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
    ls->dlgCpuFreqGB            = "CPU-Frequenz ";
    ls->dlgZ80FreqText          = "Z80-Frequenz:";
    ls->dlgR800FreqText         = "R800-Frequenz:";
    ls->dlgFdcGB                = "Floppy-Disk-Controller ";
    ls->dlgCFdcNumDrivesText    = "Anzahl der Laufwerke:";

    ls->propPriorityBoost       = " Die Priorit�t von blueMSX erh�hen";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "Floppy-Drive-Timing sperren";
    ls->shortcutToggleFdcTiming = "Freigabe/Sperren des Floppy-Drive-Timings";
    ls->propUseRegistry         = "Konfiguration in der Registry speichern";

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

    ls->discardChanges          = "M�chten Sie die �nderungen verwerfen?";
    ls->overwriteConfig         = "M�chten Sie die aktuelle Konfiguration �berschreiben?";

    ls->confSaveAsTitle         = "Speichere Konfiguration als ...";
    ls->confSaveAsName          = "Name:";

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

    // New entries in 2.3
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle";

    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "In Datei schreiben";
    ls->propPortsOpenLogFile    = "�ffne Log-Datei";
    ls->propPortsFilenameText   = "Dateiname:";
    ls->propPortsEmulateMsxPrn  = "Emulation:";

    ls->shortcutPrnFormFeed     = "Seitenvorschub des Druckers";

    ls->menuPrnFormfeed         = "Seitenvorschub";
    ls->menuFilePrn             = "Drucker";
    ls->propPortsComFile        = "Zu Datei senden";
};



#endif


