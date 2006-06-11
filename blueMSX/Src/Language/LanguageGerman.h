/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageGerman.h,v $
**
** $Revision: 1.16 $ 
**
** $Date: 2006-06-11 19:02:48 $
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

    ls->textDevice              = "Typ:";
    ls->textFilename            = "Filename:";
    ls->textFile                = "File";
    ls->textNone                = "Nichts";    
    ls->textUnknown             = "Unknown";                            // New in 2.5


    //----------------------
    // Warning and Error lines
    //----------------------

    ls->warningTitle             = "blueMSX - Warnung";
    ls->warningDiscardChanges   = "M�chten Sie die �nderungen verwerfen?";
    ls->warningOverwriteFile    = "Do you want to overwrite the file:"; // New in 2.5
    ls->errorTitle              = "blueMSX - Fehler";
    ls->errorEnterFullscreen    = "Konnte nicht in den Fullscreen-Modus gehen.           \n";
    ls->errorDirectXFailed      = "DirectX objects konnten nicht erzeugt werden.\nBenutze stattdessen GDI.\n�berpr�fe die Video-Eigenschaften.";
    ls->errorNoRomInZip         = "Konnte kein .rom-File im Zip-Archiv finden.";
    ls->errorNoDskInZip         = "Konnte kein .dsk-File im Zip-Archiv finden.";
    ls->errorNoCasInZip         = "Konnte kein .cas-File im Zip-Archiv finden.";
    ls->errorNoHelp             = "Konnte kein blueMSX-Hilfe-File finden.";
    ls->errorStartEmu           = "Der MSX-Emulator konnte nicht gestartet werde.";
    ls->errorPortableReadonly   = "Portable device is readonly";        // New in 2.5


    //----------------------
    // File related lines
    //----------------------

    ls->fileRom                 = "ROM-Image";
    ls->fileAll                 = "All Files";
    ls->fileCpuState            = "CPU-Status";
    ls->fileDisk                = "Diskette-Image";
    ls->fileCas                 = "Cassette-Image";


    //----------------------
    // Menu related lines
    //----------------------

    ls->menuNoRecentFiles       = "- keine neuen Files -";
    ls->menuInsert              = "Einf�gen";
    ls->menuEject               = "Auswurf";

    ls->menuCartGameReader      = "Game Reader";                        // New in 2.5
    ls->menuCartIde             = "IDE";                                // New in 2.5
    ls->menuCartBeerIde         = "Beer";                               // New in 2.5
    ls->menuCartGIde            = "GIDE";                               // New in 2.5
    ls->menuCartSunriseIde      = "Sunrise";                            // New in 2.5
    ls->menuCartSCC             = "SCC Cartridge";
    ls->menuCartSCCPlus         = "SCC+ Cartridge";
    ls->menuCartFMPac           = "FM-PAC-Cartridge";
    ls->menuCartPac             = "PAC-Cartridge";
    ls->menuCartHBI55           = "Sony HBI-55 Cartridge";
    ls->menuCartInsertSpecial   = "Insert Special";                     // New in 2.5
    ls->menuCartMegaRam         = "MegaRAM";                            // New in 2.5
    ls->menuCartExternalRam     = "Externes RAM";

    ls->menuCasRewindAfterInsert = "Zur�ck nach Einf�gen";
    ls->menuCasUseReadOnly       = "Cassetten-Image nur lesend benutzen";
    ls->lmenuCasSaveAs           = "Speichere Cassetten-Image als ...";
    ls->menuCasSetPosition      = "Positionieren";
    ls->menuCasRewind           = "Zur�ck";

    ls->menuDiskInsertNew       = "Insert New Disk Image";              // New in 2.5
    ls->menuDiskDirInsert       = "Directory einf�gen";
    ls->menuDiskAutoStart       = "Reset nach Einf�gen";
    ls->menuCartAutoReset       = "Reset nach Einf�gen/Entfernen";

    ls->menuPrnFormfeed         = "Seitenvorschub";

    ls->menuZoomNormal          = "Normale Gr��e";
    ls->menuZoomDouble          = "Doppelte Gr��e";
    ls->menuZoomFullscreen      = "Ganzer Bildschirm";
    
    ls->menuPropsEmulation      = "Emulation";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Sound";
    ls->menuPropsControls       = "Controls";
    ls->menuPropsPerformance    = "Performance";
    ls->menuPropsSettings        = "Einstellungen";
    ls->menuPropsFile           = "Files";
    ls->menuPropsLanguage       = "Sprache";
    ls->menuPropsPorts          = "Ports";
    
    ls->menuVideoSource         = "Video Out Source";                   // New in 2.5
    ls->menuVideoSourceDefault  = "No Video Out Source Connected";      // New in 2.5
    ls->menuVideoChipAutodetect = "Autodetect Video-Chip";    
    ls->menuVideoInSource       = "Video In Source";                    // New in 2.5
    ls->menuVideoInBitmap       = "Bitmap File";                        // New in 2.5

    ls->menuHelpHelp            = "Hilfethemen";
    ls->menuHelpAbout           = "�ber blueMSX";

    ls->menuFileCart            = "Cartridge Slot";
    ls->menuFileDisk            = "Disk Drive";
    ls->menuFileCas             = "Cassette";
    ls->menuFilePrn             = "Drucker";
    ls->menuFileLoadState       = "Lade CPU-Status";
    ls->menuFileSaveState       = "Speichere CPU-Status";
    ls->menuFileQLoadState      = "Quick Load State";
    ls->menuFileQSaveState      = "Quick Save State";
    ls->menuFileCaptureAudio    = "Capture Audio";
    ls->menuFileScreenShot      = "Speichere Screenshot";
    ls->menuFileExit            = "Exit";

    ls->menuFileHarddisk        = "Hard Disk";                          // New in 2.5
    ls->menuFileHarddiskNoPesent= "No Controllers Present";             // New in 2.5

    ls->menuRunRun              = "Start";
    ls->menuRunPause            = "Pause";
    ls->menuRunStop             = "Stopp";
    ls->menuRunSoftReset        = "Soft Reset";
    ls->menuRunHardReset        = "Hard Reset";
    ls->menuRunCleanReset       = "Allgemeiner Reset";

    ls->menuToolsMachine         = "Maschineneditor";
    ls->menuToolsShortcuts      = "Shortcuts-Editor";
    ls->menuToolsKeyboard       = "Keyboard-Editor";
    ls->menuToolsMixer          = "Audio-Mixer";
    ls->menuToolsDebugger       = "Debugger";               // New in 2.5
    ls->menuToolsTrainer        = "Trainer";                // New in 2.5
    ls->menuToolsTraceLogger    = "Trace Logger";           // New in 2.5

    ls->menuFile                = "File";
    ls->menuRun                 = "Run";
    ls->menuWindow              = "Window";
    ls->menuOptions             = "Options";
    ls->menuTools                = "Tools";
    ls->menuHelp                = "Help";


    //----------------------
    // Dialog related lines
    //----------------------

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "�ffnen";
    ls->dlgCancel               = "Abbrechen";
    ls->dlgSave                 = "Speichern";
    ls->dlgSaveAs               = "Speichern als ...";
    ls->dlgRun                  = "Start";
    ls->dlgClose                = "Schlie�en";

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
    ls->dlgSaveCassette          = "blueMSX - Speichere Tape-Image";
    ls->dlgInsertRom1           = "ROM-Cartridge in Slot 1 einf�gen";
    ls->dlgInsertRom2           = "ROM-Cartridge in Slot 2 einf�gen";
    ls->dlgInsertDiskA          = "Disketten-Image in Laufwerk A einf�gen";
    ls->dlgInsertDiskB          = "Disketten-Image in Laufwerk B einf�gen";
    ls->dlgInsertCas            = "Cassette einf�gen";
    ls->dlgInsertHarddisk       = "Insert Hard Disk";                   // New in 2.5
    ls->dlgRomType              = "Typ des ROMs:";

    ls->dlgTapeTitle            = "blueMSX - Bandposition";
    ls->dlgTapeFrameText        = "Bandposition";
    ls->dlgTapeCurrentPos       = "Aktuelle Position";
    ls->dlgTapeTotalTime        = "Gesamtzeit";
    ls->dlgTapeSetPosText        = "Bandposition:";
    ls->dlgTapeCustom            = "Zeige anwenderspezifische Files";
    ls->dlgTabPosition           = "Position";
    ls->dlgTabType               = "Typ";
    ls->dlgTabFilename           = "Filename";
    ls->dlgZipReset             = "Reset nach Einf�gen";

    ls->dlgAboutTitle           = "�ber blueMSX";

    ls->dlgLangLangText         = "W�hle die Sprache aus, die blueMSX benutzen soll.";
    ls->dlgLangLangTitle        = "blueMSX - Sprache";

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

    ls->dlgSavePreview          = "Zeige Preview";
    ls->dlgSaveDate             = "Eingesparte Zeit:";


    //----------------------
    // Properties related lines
    //----------------------

    ls->propTitle               = "blueMSX - Eigenschaften";
    ls->propEmulation           = "Emulation";
    ls->propVideo               = "Video";
    ls->propSound               = "Sound";
    ls->propControls            = "Controls";
    ls->propPerformance         = "Performance";
    ls->propSettings             = "Einstellungen";
    ls->propFile                = "Files";
    ls->propPorts               = "Ports";
    
    ls->propEmuGeneralGB        = "Allgemeines ";
    ls->propEmuFamilyText       = "MSX-Maschine:";
    ls->propEmuMemoryGB         = "Memory ";
    ls->propEmuRamSizeText      = "RAM size:";
    ls->propEmuVramSizeText     = "VRAM size:";
    ls->propEmuSpeedGB          = "Emulationsgeschwindigkeit ";
    ls->propEmuSpeedText        = "Emulationsgeschwindigkeit:";
    ls->propEmuFrontSwitchGB     = "Panasonic Switches ";
    ls->propEmuFrontSwitch       = " Front Switch";
    ls->propEmuFdcTiming        = "Floppy-Drive-Timing sperren";
    ls->propEmuPauseSwitch      = " Unterbrechungstaste";
    ls->propEmuAudioSwitch       = " MSX-AUDIO cartridge switch";
    ls->propVideoFreqText       = "Video-Frequenz:";
    ls->propVideoFreqAuto       = "Auto";
    ls->propSndOversampleText   = "Oversample:";
    ls->propSndYkInGB           = "YK-01/YK-10/YK-20 In ";                // New in 2.5
    ls->propSndMidiInGB         = "MIDI In ";
    ls->propSndMidiOutGB        = "MIDI Out ";
    ls->propSndMidiChannel      = "MIDI Channel:";                      // New in 2.5
    ls->propSndMidiAll          = "All";                                // New in 2.5

    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Typ des Monitors:";
    ls->propMonEmuText          = "Monitoremulation:";
    ls->propVideoTypeText       = "Videotyp:";
    ls->propWindowSizeText      = "Fenstergr��e:";
    ls->propMonHorizStretch      = " Horizontal Stretch";
    ls->propMonVertStretch       = " Vertical Stretch";
    ls->propMonDeInterlace      = " De-interlace";
    ls->propMonBrightness       = "Helligkeit:";
    ls->propMonContrast         = "Kontrast:";
    ls->propMonSaturation       = "S�ttigung:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanlines:";
    ls->propMonColorGhosting    = "RF-Modulator";
    ls->propMonEffectsGB        = "Effects ";

    ls->propPerfVideoDrvGB      = "Video-Treiber ";
    ls->propPerfVideoDispDrvText= "Display-Treiber:";
    ls->propPerfFrameSkipText   = "Frame skipping:";
    ls->propPerfAudioDrvGB      = "Audio-Treiber ";
    ls->propPerfAudioDrvText    = "Sound-Treiber:";
    ls->propPerfAudioBufSzText  = "Gr��e des Sound-Buffers:";
    ls->propPerfEmuGB           = "Emulation ";
    ls->propPerfSyncModeText    = "SYNC-Mode:";
    ls->propFullscreenResText   = "Bildschirmaufl�sung:";

    ls->propSndChipEmuGB        = "Emulation des Sound-Chips ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";
    ls->propSndMoonsound         = " Moonsound";
    ls->propSndMt32ToGm         = " Map MT-32 instruments to General MIDI";

    ls->propPortsLptGB          = "Paralleler Port ";
    ls->propPortsComGB          = "Serielle Ports ";
    ls->propPortsLptText        = "Port:";
    ls->propPortsCom1Text       = "Port 1:";
    ls->propPortsNone           = "Nichts";
    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "In Datei schreiben";
    ls->propPortsComFile        = "Zu Datei senden";
    ls->propPortsOpenLogFile    = "�ffne Log-Datei";
    ls->propPortsEmulateMsxPrn  = "Emulation:";

    ls->propSetFileHistoryGB     = "File History ";
    ls->propSetFileHistorySize   = "Anzahl der Elemente in der File-History:";
    ls->propSetFileHistoryClear  = "L�sche History";
    ls->propFileTypes            = " Registriere Filetypen mit blueMSX (.rom, .dsk, .cas, .sta)";
    ls->propWindowsEnvGB         = "Windows-Environment "; 
    ls->propSetScreenSaver       = " Schalte den Bildschirmschoner ab, wenn blueMSX l�uft";
    ls->propDisableWinKeys       = " Automatische MSX-Function f�r Windows-Men�tasten"; 
    ls->propPriorityBoost       = " Die Priorit�t von blueMSX erh�hen";
    ls->propScreenshotPng       = " Use Portable Network Graphics (.png) screenshots";  // New in 2.5
    ls->propClearHistory         = "Sind Sie sicher, da� Sie die File-History l�schen wollen?";
    ls->propOpenRomGB           = "�ffne ROM-Dialog ";
    ls->propDefaultRomType      = "Voreingestellter ROM-Typ:";
    ls->propGuessRomType        = "ROM-Typ erraten";

    ls->propSettDefSlotGB       = "Drag and Drop ";
    ls->propSettDefSlots        = "ROM einf�gen in:";
    ls->propSettDefSlot         = " Slot";
    ls->propSettDefDrives       = "Disketten einf�gen in:";
    ls->propSettDefDrive        = " Drive";

    ls->propThemeGB             = "Theme ";
    ls->propTheme               = "Theme:";


    //----------------------
    // Dropdown related lines
    //----------------------

    ls->enumVideoMonColor       = "Farbe";
    ls->enumVideoMonGrey        = "Schwarzwei�";
    ls->enumVideoMonGreen       = "Gr�n";
    ls->enumVideoMonAmber       = "Amber";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Nichts";
    ls->enumVideoEmuYc          = "Y/C-Kabel (scharf)";
    ls->enumVideoEmuMonitor     = "Monitor";
    ls->enumVideoEmuYcBlur      = "Verrauschtes Y/C-Kabel (scharf)";
    ls->enumVideoEmuComp        = "Composit-Signal (verwaschen)";
    ls->enumVideoEmuCompBlur    = "Verrauschtes Composit-Signal (verwaschen)";
    ls->enumVideoEmuScale2x     = "Scale 2x";
    ls->enumVideoEmuHq2x        = "Hq2x";

    ls->enumVideoSize1x         = "Normal - 320x200";
    ls->enumVideoSize2x         = "Double - 640x400";
    ls->enumVideoSizeFullscreen = "Fullscreen";

    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW accel."; 
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

    ls->enumEmuSync1ms          = "Sync am MSX refresh";
    ls->enumEmuSyncAuto         = "Automatisch (schnell)";
    ls->enumEmuSyncNone         = "Nichts";
    ls->enumEmuSyncVblank       = "Sync am PC Vertical Blank";
    ls->enumEmuAsyncVblank      = "Asynchronous PC Vblank";             // New in 2.5

    ls->enumControlsJoyNone     = "Nichts";
    ls->enumControlsJoyMouse    = "Maus";
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle";
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey Dongle";             // New in 2.5
    ls->enumControlsJoy2Button = "2-button Joystick";                   // New in 2.5
    ls->enumControlsJoyGunstick  = "Gun Stick";                         // New in 2.5
    ls->enumControlsJoyAsciiLaser="ASCII Plus-X Terminator Laser";      // New in 2.5
    ls->enumControlsJoyColeco = "ColecoVision Joystick";                // New in 2.5


    //----------------------
    // Configuration related lines
    //----------------------

    ls->confTitle                = "blueMSX - Editor f�r die Maschinenkonfiguration";
    ls->confConfigText           = "Konfiguration";
    ls->confSlotLayout           = "Slot-Layout";
    ls->confMemory               = "Memory";
    ls->confChipEmulation        = "Chip-Emulation";
    ls->confChipExtras          = "Extras";

    ls->confOpenRom             = "�ffnen ROM-Image";
    ls->confSaveTitle            = "blueMSX - Speichere Konfiguration";
    ls->confSaveText             = "M�chten Sie die Maschinenkonfiguration �berschreiben?";
    ls->confSaveAsTitle         = "Speichere Konfiguration als ...";
    ls->confSaveAsMachineName    = "Name der Maschine:";
    ls->confDiscardTitle         = "blueMSX - Konfiguration";
    ls->confExitSaveTitle        = "blueMSX - Konfigurationseditor verlassen";
    ls->confExitSaveText         = "M�chten Sie die aktuellen �nderungen der Konfiguration verwerfen?";

    ls->confSlotLayoutGB         = "Slot-Layout ";
    ls->confSlotExtSlotGB        = "Externe Slots ";
    ls->confBoardGB             = "Board ";
    ls->confBoardText           = "Board-Typ:";
    ls->confSlotPrimary          = "Primary";
    ls->confSlotExpanded         = "Expanded (vier Subslots)";

    ls->confSlotCart             = "Cartridge";
    ls->confSlot                = "Slot";
    ls->confSubslot             = "Subslot";

    ls->confMemAdd               = "Hinzuf�gen ...";
    ls->confMemEdit              = "Editieren ...";
    ls->confMemRemove            = "Entfernen";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Addresse";
    ls->confMemType              = "Typ";
    ls->confMemRomImage          = "ROM-Image";
    
    ls->confChipVideoGB          = "Video ";
    ls->confChipVideoChip        = "Video-Chip:";
    ls->confChipVideoRam         = "Video-RAM:";
    ls->confChipSoundGB          = "Sound ";

    ls->confCmosGB                = "CMOS ";
    ls->confCmosEnable            = " CMOS einschalten";
    ls->confCmosBattery           = " Verwende geladene Batterie";

    ls->confCpuFreqGB            = "CPU-Frequenz ";
    ls->confZ80FreqText          = "Z80-Frequenz:";
    ls->confR800FreqText         = "R800-Frequenz:";
    ls->confFdcGB                = "Floppy-Disk-Controller ";
    ls->confCFdcNumDrivesText    = "Anzahl der Laufwerke:";

    ls->confEditMemTitle         = "blueMSX - Edit Mapper";
    ls->confEditMemGB            = "Mapper Details ";
    ls->confEditMemType          = "Typ:";
    ls->confEditMemFile          = "File:";
    ls->confEditMemAddress       = "Addresse";
    ls->confEditMemSize          = "Gr��e";
    ls->confEditMemSlot          = "Slot";


    //----------------------
    // Shortcut lines
    //----------------------

    ls->shortcutKey             = "Kontrollsequenz";
    ls->shortcutDescription     = "Shortcut";

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
    ls->shortcutSpecialMenu1    = "Zeige spezielles ROM-Men� f�r Cartridge 1";
    ls->shortcutSpecialMenu2    = "Zeige spezielles ROM-Men� f�r Cartridge 2";
    ls->shortcutCartAutoReset   = "Emulator zur�cksetzen, wenn Cartridge eingef�gt wird";
    ls->shortcutDiskInsertA     = "Diskette A einf�gen";
    ls->shortcutDiskDirInsertA  = "Directory als Diskette A einf�gen";
    ls->shortcutDiskRemoveA     = "Diskette A auswerfen";
    ls->shortcutDiskChangeA     = "Schneller Austausch von Diskette A";
    ls->shortcutDiskAutoResetA  = "Emulator zur�cksetzen, wenn Diskette A eingef�gt wird";
    ls->shortcutDiskInsertB     = "Diskette B einf�gen";
    ls->shortcutDiskDirInsertB  = "Directory als Diskette B einf�gen";
    ls->shortcutDiskRemoveB     = "Diskette B auswerfen";
    ls->shortcutCasInsert       = "Cassette einf�gen";
    ls->shortcutCasEject        = "Cassette auswerfen";
    ls->shortcutCasAutorewind   = "Toggle Auto-rewind on Cassette";
    ls->shortcutCasReadOnly     = "Toggle Read-only Cassette";
    ls->shortcutCasSetPosition  = "Bandposition festlegen";
    ls->shortcutCasRewind       = "Cassette zur�ckspulen";
    ls->shortcutCasSave         = "Cassetten-Image speichern";
    ls->shortcutPrnFormFeed     = "Seitenvorschub des Druckers";
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
    ls->shortcutSizeMinimized   = "Fenster minimieren";
    ls->shortcutVolumeIncrease  = "Lautst�rke erh�hen";
    ls->shortcutVolumeDecrease  = "Lautst�rke vermindern";
    ls->shortcutVolumeMute      = "Ton abschalten";
    ls->shortcutVolumeStereo    = "Mono/Stereo umschalten";
    ls->shortcutSwitchMsxAudio  = "Toggle MSX-AUDIO switch";
    ls->shortcutSwitchFront     = "Toggle Panasonic front switch";
    ls->shortcutSwitchPause     = "Unterbrechungstaste umschalten";
    ls->shortcutToggleMouseLock = "Maussperre umschalten";
    ls->shortcutEmuSpeedMax     = "Max. Emulationsgeschwindigkeit";
    ls->shortcutEmuSpeedToggle  = "Max. Emulationsgeschwindigkeit umschalten";
    ls->shortcutEmuSpeedNormal  = "Normale Emulationsgeschwindigkeit";
    ls->shortcutEmuSpeedInc     = "Emulationsgeschwindigkeit erh�hen";
    ls->shortcutEmuSpeedDec     = "Emulationsgeschwindigkeit vermindern";
    ls->shortcutThemeSwitch     = "Switch theme";
    ls->shortcutShowEmuProp     = "Zeige Emulationseigenschaften";
    ls->shortcutShowVideoProp   = "Zeige Video-Eigenschaften";
    ls->shortcutShowAudioProp   = "Zeige Audio-Eigenschaften";
    ls->shortcutShowCtrlProp    = "Zeige Control-Eigenschaften";
    ls->shortcutShowPerfProp    = "Zeige Leistungseigenschaften";
    ls->shortcutShowSettProp    = "Zeige Einstellungseigenschaften";
    ls->shortcutShowPorts       = "Zeige Ports-Eigenschaften";
    ls->shortcutShowLanguage    = "Zeige Sprachdialog";
    ls->shortcutShowMachines    = "Zeige Maschineneditor";
    ls->shortcutShowShortcuts   = "Zeige Shortcuts-Editor";
    ls->shortcutShowKeyboard    = "Zeige Keyboard-Editor";
    ls->shortcutShowMixer       = "Zeige Audio-Mixer";
    ls->shortcutShowDebugger    = "Zeige Debugger";
    ls->shortcutShowTrainer     = "Zeige Trainer";
    ls->shortcutShowHelp        = "Zeige Hilfe-Dialog";
    ls->shortcutShowAbout       = "Zeige ''About''-Dialog";
    ls->shortcutShowFiles       = "Zeige Fileeigenschaften";
    ls->shortcutToggleSpriteEnable = "Sprites zeigen/verdecken";
    ls->shortcutToggleFdcTiming = "Freigabe/Sperren des Floppy-Drive-Timings";
    ls->shortcutToggleCpuTrace  = "Enable/Disable CPU Trace";


    //----------------------
    // Keyboard config lines
    //----------------------

    ls->keyconfigSelectedKey    = "Selected Key:";
    ls->keyconfigMappedTo       = "Mapped To:";
    ls->keyconfigMappingScheme  = "Mapping Scheme:";
};

#endif
