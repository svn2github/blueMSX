/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageDutch.h,v $
**
** $Revision: 1.51 $
**
** $Date: 2008-02-10 17:25:03 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2006 Daniel Vik
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
******************************************************************************
*/
#ifndef LANGUAGE_DUTCH_H
#define LANGUAGE_DUTCH_H

#include "LanguageStrings.h"

void langInitDutch(LanguageStrings* ls)
{
    //----------------------
    // Language lines
    //----------------------

    ls->langCatalan             = "Catalan";
    ls->langChineseSimplified   = "Chinees Simpel";
    ls->langChineseTraditional  = "Chinees Traditioneel";
    ls->langDutch               = "Nederlands";
    ls->langEnglish             = "Engels";
    ls->langFinnish             = "Fins";
    ls->langFrench              = "Frans";
    ls->langGerman              = "Duits";
    ls->langItalian             = "Italiaans";
    ls->langJapanese            = "Japans";
    ls->langKorean              = "Koreaans";
    ls->langPolish              = "Pools";
    ls->langPortuguese          = "Portugees";
    ls->langRussian             = "Russian";            // v2.8
    ls->langSpanish             = "Spaans";
    ls->langSwedish             = "Zweeds";


    //----------------------
    // Generic lines
    //----------------------

    ls->textDevice              = "Apparaat:";
    ls->textFilename            = "Bestandsnaam:";
    ls->textFile                = "Bestand";
    ls->textNone                = "Geen";
    ls->textUnknown             = "Onbekend";


    //----------------------
    // Warning and Error lines
    //----------------------

    ls->warningTitle            = "blueMSX - Waarschuwing";
    ls->warningDiscardChanges   = "Wilt u de wijzigingen ongedaan maken?";
    ls->warningOverwriteFile    = "Wilt u het volgende bestand overschrijven?";
    ls->errorTitle              = "blueMSX - Foutmelding";
    ls->errorEnterFullscreen    = "Het is niet gelukt om over te schakelen naar de volledige schermmodus.          \n";
    ls->errorDirectXFailed      = "Het is niet gelukt om DirectX te initialiseren. \nDe GDI wordt nu gebruikt.\nKijk de videoinstellingen na...";
    ls->errorNoRomInZip         = "Er zijn geen .rom-bestanden gevonden in het zip-bestand.";
    ls->errorNoDskInZip         = "Er zijn geen .dsk-bestanden gevonden in het zip-bestand.";
    ls->errorNoCasInZip         = "Er zijn geen .cas-bestanden gevonden in het zip-bestand.";
    ls->errorNoHelp             = "Het blueMSX-helpbestand is niet gevonden.";
    ls->errorStartEmu           = "Het is niet gelukt om de MSX-emulator te starten.";
    ls->errorPortableReadonly   = "Het draagbare apparaat is Alleen Lezen";


    //----------------------
    // File related lines
    //----------------------

    ls->fileRom                 = "Rom-beeld";
    ls->fileAll                 = "Alle bestanden";
    ls->fileCpuState            = "CPU-status";
    ls->fileVideoCapture        = "Videoopname";
    ls->fileDisk                = "Disk-beeld";
    ls->fileCas                 = "Cassette-beeld";
    ls->fileAvi                 = "Videobestand";


    //----------------------
    // Menu related lines
    //----------------------

    ls->menuNoRecentFiles       = "- Geen recente bestanden -";
    ls->menuInsert              = "Toevoegen";
    ls->menuEject               = "Verwijderen";

    ls->menuCartGameReader      = "Game Reader";
    ls->menuCartIde             = "IDE";
    ls->menuCartBeerIde         = "Beer";
    ls->menuCartGIde            = "GIDE";
    ls->menuCartSunriseIde      = "Sunrise";  
    ls->menuCartScsi            = "SCSI";                // New in 2.7
    ls->menuCartMegaSCSI        = "MEGA-SCSI";           // New in 2.7
    ls->menuCartWaveSCSI        = "WAVE-SCSI";           // New in 2.7
    ls->menuCartGoudaSCSI       = "Gouda SCSI";          // New in 2.7
    ls->menuCartSCC             = "SCC Cartridge";
    ls->menuCartSCCPlus         = "SCC+ Cartridge";
    ls->menuCartFMPac           = "FM-PAC Cartridge";
    ls->menuCartPac             = "PAC Cartridge";
    ls->menuCartHBI55           = "Sony HBI-55 Cartridge";
    ls->menuCartInsertSpecial   = "Toevoegen Speciale Cartridge";
    ls->menuCartMegaRam         = "MegaRAM";
    ls->menuCartExternalRam     = "Extern RAM-geheugen";
    ls->menuCartEseRam          = "Ese-RAM";             // New in 2.7
    ls->menuCartEseSCC          = "Ese-SCC";             // New in 2.7
    ls->menuCartMegaFlashRom    = "Mega Flash ROM";      // New in 2.7

    ls->menuDiskInsertNew       = "Toevoegen Nieuw Diskette-beeld";
    ls->menuDiskInsertCdrom     = "Insert CD-Rom";       // New in 2.7
    ls->menuDiskDirInsert       = "Toevoegen Map";
    ls->menuDiskAutoStart       = "Herstart na toevoegen";
    ls->menuCartAutoReset       = "Herstart na toevoegen/verwijderen";

    ls->menuCasRewindAfterInsert= "Terugspoelen na inname";
    ls->menuCasUseReadOnly      = "Gebruik Cassette-beeld als Alleen Lezen";
    ls->lmenuCasSaveAs          = "Cassette-beeld opslaan als...";
    ls->menuCasSetPosition      = "Bepaal positie";
    ls->menuCasRewind           = "Terugspoelen cassette";

    ls->menuVideoLoad           = "Laden...";
    ls->menuVideoPlay           = "Laatste opname afspelen";
    ls->menuVideoRecord         = "Opnemen";
    ls->menuVideoRecording      = "Bezig met openemen";
    ls->menuVideoRecAppend      = "Opnemen (toevoegen)";
    ls->menuVideoStop           = "Stoppen";
    ls->menuVideoRender         = "Maak Videobestand";

    ls->menuPrnFormfeed         = "Paginadoorvoer";

    ls->menuZoomNormal          = "Normale grootte";
    ls->menuZoomDouble          = "Dubbele grootte";
    ls->menuZoomFullscreen      = "Volledig scherm";

    ls->menuPropsEmulation      = "Emulatie";
    ls->menuPropsVideo          = "Beeld";
    ls->menuPropsSound          = "Geluid";
    ls->menuPropsControls       = "Besturing";
    ls->menuPropsPerformance    = "Prestatie";
    ls->menuPropsSettings       = "Instellingen";
    ls->menuPropsFile           = "Bestand";
    ls->menuPropsDisk           = "Disks";               // New in 2.7
    ls->menuPropsLanguage       = "Taal";
    ls->menuPropsPorts          = "Poorten";

    ls->menuVideoSource         = "Video Uit-bron";
    ls->menuVideoSourceDefault  = "Geen Video Uit-bron verbonden";
    ls->menuVideoChipAutodetect = "Automatische detectie Videochip";
    ls->menuVideoInSource       = "Video In-bron";
    ls->menuVideoInBitmap       = "Afbeedingsbestand";

    ls->menuEthInterface        = "Ethernet koppeling";

    ls->menuHelpHelp            = "Help";
    ls->menuHelpAbout           = "Info blueMSX";

    ls->menuFileCart            = "Cartridgeslot";
    ls->menuFileDisk            = "Diskettestation";
    ls->menuFileCas             = "Cassette";
    ls->menuFilePrn             = "Printer";
    ls->menuFileLoadState       = "Laad CPU-status";
    ls->menuFileSaveState       = "Opslaan CPU-status";
    ls->menuFileQLoadState      = "Snel laden CPU-status";
    ls->menuFileQSaveState      = "Snel opslaan CPU-status";
    ls->menuFileCaptureAudio    = "Opslaan Geluid";
    ls->menuFileCaptureVideo    = "Opslaan Video";
    ls->menuFileScreenShot      = "Schermafdruk maken";
    ls->menuFileExit            = "Afsluiten";

    ls->menuFileHarddisk        = "Vaste schijf";
    ls->menuFileHarddiskNoPesent= "Geen vaste schijfcontrollers aanwezig";
    ls->menuFileHarddiskRemoveAll= "Eject All Harddisk";    // New in 2.7

    ls->menuRunRun              = "Start";
    ls->menuRunPause            = "Pauze";
    ls->menuRunStop             = "Stop";
    ls->menuRunSoftReset        = "Zachte Herstart";
    ls->menuRunHardReset        = "Harde Herstart";
    ls->menuRunCleanReset       = "Algemene Herstart";

    ls->menuToolsMachine        = "Aanpassen Machine";
    ls->menuToolsShortcuts      = "Maken Snelkoppeling";
    ls->menuToolsCtrlEditor     = "Besturingseditors";
    ls->menuToolsMixer          = "Mixer";
    ls->menuToolsDebugger       = "Debugger";
    ls->menuToolsTrainer        = "Trainer";
    ls->menuToolsTraceLogger    = "Trace Logger";

    ls->menuFile                = "Bestand";
    ls->menuRun                 = "Start";
    ls->menuWindow              = "Scherm";
    ls->menuOptions             = "Opties";
    ls->menuTools               = "Extra";
    ls->menuHelp                = "Help";


    //----------------------
    // Dialog related lines
    //----------------------

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Openen";
    ls->dlgCancel               = "Annuleren";
    ls->dlgSave                 = "Opslaan";
    ls->dlgSaveAs               = "Opslaan als...";
    ls->dlgRun                  = "Start";
    ls->dlgClose                = "Afsluiten";

    ls->dlgLoadRom              = "blueMSX - Selecteer een rom om te laden";
    ls->dlgLoadDsk              = "blueMSX - Selecteer een dsk om te laden";
    ls->dlgLoadCas              = "blueMSX - Selecteer een cas om te laden";
    ls->dlgLoadRomDskCas        = "blueMSX - Selecteer een rom, dsk, of cas-bestand om te laden";
    ls->dlgLoadRomDesc          = "Selecteer een rom om te laden:";
    ls->dlgLoadDskDesc          = "Selecteer een diskette om te laden:";
    ls->dlgLoadCasDesc          = "Selecteer een cassette om te laden:";
    ls->dlgLoadRomDskCasDesc    = "Selecteer een cartridge, diskette of cassette om te laden:";
    ls->dlgLoadState            = "Laad CPU-status";
    ls->dlgLoadVideoCapture     = "Laad Video-opname";
    ls->dlgSaveState            = "Opslaan CPU-status";
    ls->dlgSaveCassette         = "blueMSX - Opslaan Cassette-beeld";
    ls->dlgSaveVideoClipAs      = "Videoclip opslaan als...";
    ls->dlgAmountCompleted      = "Aantal gereed:";
    ls->dlgInsertRom1           = "Toevoegen Rom-cartridge in slot 1";
    ls->dlgInsertRom2           = "Toevoegen Rom-cartridge in slot 2";
    ls->dlgInsertDiskA          = "Toevoegen diskette-beeld in station A";
    ls->dlgInsertDiskB          = "Toevoegen diskette-beeld in station B";
    ls->dlgInsertHarddisk       = "Toevoegen Vaste schijf";
    ls->dlgInsertCas            = "Toevoegen cassette-beeld in casettespeler";
    ls->dlgRomType              = "Romtype :";
    ls->dlgDiskSize             = "Diskomvang:";

    ls->dlgTapeTitle            = "blueMSX - Tapepositie";
    ls->dlgTapeFrameText        = "Tapepositie";
    ls->dlgTapeCurrentPos       = "Huidige positie";
    ls->dlgTapeTotalTime        = "Totale tijd";
    ls->dlgTapeCustom            = "Laat Speciale Bestanden zien";
    ls->dlgTapeSetPosText        = "Tape Positie:";
    ls->dlgTabPosition           = "Positie";
    ls->dlgTabType               = "Type";
    ls->dlgTabFilename           = "Bestandsnaam";
    ls->dlgZipReset             = "Herstart na toevoegen";

    ls->dlgAboutTitle           = "blueMSX - Info";

    ls->dlgLangLangText         = "Kies de taal die blueMSX moet gebruiken";
    ls->dlgLangLangTitle        = "blueMSX - Taal";

    ls->dlgAboutAbout           = "Info\r\n====";
    ls->dlgAboutVersion         = "Versie:";
    ls->dlgAboutBuildNumber     = "Gemaakt:";
    ls->dlgAboutBuildDate       = "Datum:";
    ls->dlgAboutCreat           = "Gemaakt door Daniel Vik";
    ls->dlgAboutDevel           = "GEMAAKT DOOR\r\n========";
    ls->dlgAboutThanks          = "MET DANK AAN\r\n============";       // New in 2.7 (retranslate, see english)
    ls->dlgAboutLisence         = "LICENTIE\r\n"
                                  "======\r\n\r\n"
                                  "Deze software wordt gegeven 'as-is', zonder enige vorm van garantie. "
                                  "De auteur(s) is/zijn niet verantwoordelijk voor elke vorm van schade "
                                  "die onstaat door het gebruik van deze software.\r\n\r\n"
                                  "Bezoek www.bluemsx.com voor meer details.";

    ls->dlgSavePreview          = "Voorbeeld weergeven";
    ls->dlgSaveDate             = "Opgeslagen op:";

    ls->dlgRenderVideoCapture   = "blueMSX - Videoclip wordt gemaakt...";


    //----------------------
    // Properties related lines
    //----------------------

    ls->propTitle               = "blueMSX - Eigenschappen";
    ls->propEmulation           = "Emulatie";
    ls->propVideo               = "Beeld";
    ls->propSound               = "Geluid";
    ls->propControls            = "Besturing";
    ls->propPerformance         = "Prestaties";
    ls->propSettings            = "Instellingen";
    ls->propFile                = "Bestand";
    ls->propDisk                = "Disks";              // New in 2.7
    ls->propPorts               = "Poorten";

    ls->propEmuGeneralGB        = "Algemeen ";
    ls->propEmuFamilyText       = "MSX-familie:";
    ls->propEmuMemoryGB         = "Geheugen ";
    ls->propEmuRamSizeText      = "RAM-grootte:";
    ls->propEmuVramSizeText     = "VRAM-grootte:";
    ls->propEmuSpeedGB          = "Emulatiesnelheid ";
    ls->propEmuSpeedText        = "Emulatiesnelheid:";
    ls->propEmuFrontSwitchGB    = "Panasonic schakelaars ";
    ls->propEmuFrontSwitch      = " Front Switch";
    ls->propEmuFdcTiming        = " Diskettestation niet synchroniseren";
    ls->propEmuPauseSwitch      = " Pause Switch";
    ls->propEmuAudioSwitch      = " MSX-AUDIO cartridge switch";
    ls->propVideoFreqText       = "Videofrequentie:";
    ls->propVideoFreqAuto       = "Automatisch";
    ls->propSndOversampleText   = "Oversample:";
    ls->propSndYkInGB           = "YK-01/YK-10/YK-20 In ";
    ls->propSndMidiInGB         = "MIDI In ";
    ls->propSndMidiOutGB        = "MIDI Out ";
    ls->propSndMidiChannel      = "MIDI-kanaal:";
    ls->propSndMidiAll          = "Alle";

    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Monitortype:";
    ls->propMonEmuText          = "Monitoremulatie:";
    ls->propVideoTypeText       = "Beeldtype:";
    ls->propWindowSizeText      = "Schermgrootte:";
    ls->propMonHorizStretch     = " Horizontaal uitrekken";
    ls->propMonVertStretch      = " Verticaal uitrekken";
    ls->propMonDeInterlace      = " Deïnterlace";
    ls->propBlendFrames         = " Opeenvolgende frames mengen";
    ls->propMonBrightness       = "Helderheid:";
    ls->propMonContrast         = "Contrast:";
    ls->propMonSaturation       = "Verzadiging:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = " Beeldlijnen";
    ls->propMonColorGhosting    = " RF-modulator";
    ls->propMonEffectsGB        = " Effecten ";

    ls->propPerfVideoDrvGB      = "Beeldinstellingen ";
    ls->propPerfVideoDispDrvText= "Stuurprogramma:";
    ls->propPerfFrameSkipText   = "Frames overslaan:";
    ls->propPerfAudioDrvGB      = "Geluidsinstellingen ";
    ls->propPerfAudioDrvText    = "Stuurprogramma:";
    ls->propPerfAudioBufSzText  = "Buffergrootte:";
    ls->propPerfEmuGB           = "Emulatie ";
    ls->propPerfSyncModeText    = "Synchronisatiemodus";
    ls->propFullscreenResText   = "Resolutie vol. schermmodus:";

    ls->propSndChipEmuGB        = "Emulatie geluidschip ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";
    ls->propSndMoonsound        = " Moonsound";
    ls->propSndMt32ToGm         = " Map MT-32-instrumenten naar General MIDI-indeling";

    ls->propPortsLptGB          = "Parallele poort ";
    ls->propPortsComGB          = "Seriele poorten ";
    ls->propPortsLptText        = "Poort:";
    ls->propPortsCom1Text       = "Poort 1:";
    ls->propPortsNone           = "Geen";
    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "Afdrukken naar bestand";
    ls->propPortsComFile        = "Stuur naar bestand";
    ls->propPortsOpenLogFile    = "Logbestand openen";
    ls->propPortsEmulateMsxPrn  = "Emulatie:";

    ls->propSetFileHistoryGB     = "Bestandsgeschiedenis ";
    ls->propSetFileHistorySize   = "Aantal bestanden in geschiedenis:";
    ls->propSetFileHistoryClear  = "Leegmaken Geschiedenis";
    ls->propFileTypes            = " Bestanden registreren bij blueMSX (.rom, .dsk, .cas, .sta)";
    ls->propWindowsEnvGB         = "Windows Omgeving";
    ls->propSetScreenSaver       = "Schermbeveiliging uitschakelen als blueMSX draait";
    ls->propDisableWinKeys       = " Automatische MSX-functie voor menutoetsen Windows";
    ls->propPriorityBoost       = " blueMSX een hogere prioriteit geven";
    ls->propScreenshotPng       = " Gebruik Portable Network Graphics (.png) voor afbeeldingen";
    ls->propClearHistory         = "Weet u zeker dat u de bestandsgeschiedenis wilt wissen?";
    ls->propOpenRomGB           = "Openen Rombestand";
    ls->propDefaultRomType      = "Standaardtype:";
    ls->propGuessRomType        = "Raden type";

    ls->propSettDefSlotGB       = "Slepen en neerzetten ";
    ls->propSettDefSlots        = "Toevoegen cartridge in:";
    ls->propSettDefSlot         = " Slot";
    ls->propSettDefDrives       = "Toevoegen diskette in:";
    ls->propSettDefDrive        = " Station";

    ls->propThemeGB             = "Thema ";
    ls->propTheme               = "Thema";

    ls->propCdromGB             = "CD-ROM";          // New in 2.7
    ls->propCdromMethod         = "Access Method:";  // New in 2.7
    ls->propCdromMethodNone     = "None";            // New in 2.7
    ls->propCdromMethodIoctl    = "IOCTL";           // New in 2.7
    ls->propCdromMethodAspi     = "ASPI";            // New in 2.7
    ls->propCdromDrive          = "Drive:";          // New in 2.7


    //----------------------
    // Dropdown related lines
    //----------------------

    ls->enumVideoMonColor       = "Kleur";
    ls->enumVideoMonGrey        = "Zwart-Wit";
    ls->enumVideoMonGreen       = "Groen";
    ls->enumVideoMonAmber       = "Amber";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Geen";
    ls->enumVideoEmuYc          = "Y/C-kabel (Scherp)";
    ls->enumVideoEmuMonitor     = "Monitor";
    ls->enumVideoEmuYcBlur      = "Ruis Y/C-kabel (Scherp)";
    ls->enumVideoEmuComp        = "Compositie (Wazig)";
    ls->enumVideoEmuCompBlur    = "Ruis Compositie (Wazig)";
    ls->enumVideoEmuScale2x     = "Schaal 2x";
    ls->enumVideoEmuHq2x        = "Hq2x";

    ls->enumVideoSize1x         = "Normaal - 320x200";
    ls->enumVideoSize2x         = "Dubbel - 640x400";
    ls->enumVideoSizeFullscreen = "Volledig Scherm";

    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW accel.";
    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "Geen";
    ls->enumVideoFrameskip1     = "1 frame";
    ls->enumVideoFrameskip2     = "2 frames";
    ls->enumVideoFrameskip3     = "3 frames";
    ls->enumVideoFrameskip4     = "4 frames";
    ls->enumVideoFrameskip5     = "5 frames";

    ls->enumSoundDrvNone        = "Geen Geluid";
    ls->enumSoundDrvWMM         = "WMM-stuurprogramma";
    ls->enumSoundDrvDirectX     = "DirectX-stuurprogramma";

    ls->enumEmuSync1ms          = "Synchroniseren tijdens MSX refresh";
    ls->enumEmuSyncAuto         = "Automatisch (snel)";
    ls->enumEmuSyncNone         = "Geen";
    ls->enumEmuSyncVblank       = "Synchroon met PC Vertical Blank";
    ls->enumEmuAsyncVblank      = "Asynchroon met PC Vblank";

    ls->enumControlsJoyNone     = "Geen";
    ls->enumControlsJoyMouse    = "Muis";
    ls->enumControlsJoyTetris2Dongle = "Tetris 2-dongle";
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey-dongle";
    ls->enumControlsJoy2Button = "2-knopsjoystick";
    ls->enumControlsJoyGunstick  = "Gun Stick";
    ls->enumControlsJoyAsciiLaser="ASCII Plus-X Terminator Laser";
    ls->enumControlsArkanoidPad  ="Arkanoid Pad";                   // New in 2.7.1
    ls->enumControlsJoyColeco = "ColecoVision Joystick";

    ls->enumDiskMsx35Dbl9Sect    = "MSX 3.5\" Double Sided, 9 Sectoren";
    ls->enumDiskMsx35Dbl8Sect    = "MSX 3.5\" Double Sided, 8 Sectoren";
    ls->enumDiskMsx35Sgl9Sect    = "MSX 3.5\" Single Sided, 9 Sectoren";
    ls->enumDiskMsx35Sgl8Sect    = "MSX 3.5\" Single Sided, 8 Sectoren";
    ls->enumDiskSvi525Dbl        = "SVI-328 5.25\" Double Sided";
    ls->enumDiskSvi525Sgl        = "SVI-328 5.25\" Single Sided";
    ls->enumDiskSf3Sgl           = "Sega SF-7000 3\" Single Sided";


    //----------------------
    // Configuration related lines
    //----------------------

    ls->confTitle               = "blueMSX - Machineconfiguratie aanpassen";
    ls->confConfigText          = "Configuratie:";
    ls->confSlotLayout          = "Slotinstellingen";
    ls->confMemory              = "Geheugen";
    ls->confChipEmulation       = "Chipemulatie";
    ls->confChipExtras          = "Extras";

    ls->confOpenRom             = "Open Rom-beeld";
    ls->confSaveTitle           = "blueMSX - Machineconfiguratie opslaan";
    ls->confSaveText            = "Deze machine configuratie vervangen? :";
    ls->confSaveAsTitle         = "Configuratie opslaan als...";
    ls->confSaveAsMachineName   = "Configuratienaam:";
    ls->confDiscardTitle        = "blueMSX - Configuratie";
    ls->confExitSaveTitle       = "blueMSX - Machineconfiguratie afsluiten";
    ls->confExitSaveText        = "De gemaakte wijzigingen in de huidige configuratie worden niet opgeslagen. Wilt u doorgaan?";

    ls->confSlotLayoutGB        = "Slotinstellingen ";
    ls->confSlotExtSlotGB       = "Externe Slots ";
    ls->confBoardGB             = "Systeem ";
    ls->confBoardText           = "Systeemtype:";
    ls->confSlotPrimary         = "Primair";
    ls->confSlotExpanded        = "Uitgebreid (vier sub-slots)";

    ls->confSlotCart            = "Cartridge";
    ls->confSlot                = "Slot";
    ls->confSubslot             = "Subslot";

    ls->confMemAdd              = "Toevoegen...";
    ls->confMemEdit             = "Aanpassen...";
    ls->confMemRemove           = "Verwijderen";
    ls->confMemSlot             = "Slot";
    ls->confMemAddresss         = "Adres";
    ls->confMemType             = "Type";
    ls->confMemRomImage         = "Rom-beeld";

    ls->confChipVideoGB         = "Weergave ";
    ls->confChipVideoChip       = "Videochip:";
    ls->confChipVideoRam        = "VideoRAM:";
    ls->confChipSoundGB         = "Geluid ";

    ls->confCmosGB                = "CMOS ";
    ls->confCmosEnable            = " Aanzetten CMOS";
    ls->confCmosBattery           = " Geladen batterij gebruiken";

    ls->confCpuFreqGB            = "CPU-frequentie ";
    ls->confZ80FreqText          = "Z80-frequentie:";
    ls->confR800FreqText         = "R800-frequentie:";
    ls->confFdcGB                = "Diskettecontroller ";
    ls->confCFdcNumDrivesText    = "Aantal stations:";

    ls->confEditMemTitle        = "blueMSX - Aanpassen Mapper";
    ls->confEditMemGB           = "Mapperdetails ";
    ls->confEditMemType         = "Type:";
    ls->confEditMemFile         = "Bestand:";
    ls->confEditMemAddress      = "Addres:";
    ls->confEditMemSize         = "Grootte:";
    ls->confEditMemSlot         = "Slot:";


    //----------------------
    // Shortcut lines
    //----------------------

    ls->shortcutKey             = "Sneltoets";
    ls->shortcutDescription     = "Snelkoppeling";

    ls->shortcutSaveConfig      = "blueMSX -  Configuratie opslaan";
    ls->shortcutOverwriteConfig = "Huidige configuratie overschrijven?:";
    ls->shortcutExitConfig      = "blueMSX -  Snelkoppelingconfiguratie afsluiten";
    ls->shortcutDiscardConfig   = "Weet u zeker dat u de gemaakte wijzigingen in de huidige configuratie niet wilt toepassen?";
    ls->shortcutSaveConfigAs    = "blueMSX - Configuratie opslaan als...";
    ls->shortcutConfigName      = "Snelkoppelingsnaam:";
    ls->shortcutNewProfile      = "< Nieuw Profiel >";
    ls->shortcutConfigTitle     = "blueMSX - Toewijzingen Snelkoppelingen";
    ls->shortcutAssign          = "Toewijzen";
    ls->shortcutPressText       = "Snelkoppelingstoets(en):";
    ls->shortcutScheme          = "Schema:";
    ls->shortcutCartInsert1     = "Toevoegen Cartridge in Slot 1";
    ls->shortcutCartRemove1     = "Verwijder Cartridge uit Slot 1";
    ls->shortcutCartInsert2     = "Toevoegen Cartridge in Slot 2";
    ls->shortcutCartRemove2     = "Verwijder Cartridge uit Slot 2";
    ls->shortcutSpecialMenu1    = "Dialoog: Speciaal menu voor Romcartridge in slot 1";
    ls->shortcutSpecialMenu2    = "Dialoog: Speciaal menu voor Romcartridge in slot 2";
    ls->shortcutCartAutoReset   = "Herstart na toevoegen cartridge";
    ls->shortcutDiskInsertA     = "Toevoegen Diskette in station A";
    ls->shortcutDiskDirInsertA  = "Toevoegen Map als Diskette A";
    ls->shortcutDiskRemoveA     = "Verwijder Diskette uit station A";
    ls->shortcutDiskChangeA     = "Snel veranderen van diskette in station A";
    ls->shortcutDiskAutoResetA  = "Herstart na toevoegen diskette in station A";
    ls->shortcutDiskInsertB     = "Toevoegen Diskette in station B";
    ls->shortcutDiskDirInsertB  = "Toevoegen Map als Diskette B";
    ls->shortcutDiskRemoveB     = "Verwijder Diskette uit station B";
    ls->shortcutCasInsert       = "Toevoegen Cassette";
    ls->shortcutCasEject        = "Verwijder Cassette";
    ls->shortcutCasAutorewind   = "Automatisch cassette terugspoelen ja/nee";
    ls->shortcutCasReadOnly     = "Aleen lezen cassette-beeld ja/nee";
    ls->shortcutCasSetPosition  = "Bepalen Cassettepositie";
    ls->shortcutCasRewind       = "Terugspoelen Cassette";
    ls->shortcutCasSave         = "Opslaan Cassette-beeld";
    ls->shortcutPrnFormFeed     = "Printer paginadoorvoer";
    ls->shortcutCpuStateLoad    = "Laden CPU-status";
    ls->shortcutCpuStateSave    = "Opslaan CPU-status";
    ls->shortcutCpuStateQload   = "Snel laden CPU-status";
    ls->shortcutCpuStateQsave   = "Snel opslaan CPU-status";
    ls->shortcutAudioCapture    = "Start/stop het audio opslaan";
    ls->shortcutScreenshotOrig  = "Opslaan schermafdruk";
    ls->shortcutScreenshotSmall = "Opslaan klein ongefilterde schermafdruk";
    ls->shortcutScreenshotLarge = "Opslaan groot ongefilterde schermafdruk";
    ls->shortcutQuit            = "Afsluiten blueMSX";
    ls->shortcutRunPause        = "Starten/Pauseren emulatie";
    ls->shortcutStop            = "Stoppen emulatie";
    ls->shortcutResetHard       = "Harde Herstart";
    ls->shortcutResetSoft       = "Zachte Herstart";
    ls->shortcutResetClean      = "Algemene Herstart";
    ls->shortcutSizeSmall       = "Kiezen normale grootte voor het scherm";
    ls->shortcutSizeNormal      = "Kiezen dubbele grootte voor het scherm";
    ls->shortcutSizeFullscreen  = "Kiezen volledig scherm";
    ls->shortcutSizeMinimized   = "Minimaliseer scherm";
    ls->shortcutToggleFullscren = "Kiezen volledig scherm of onvolledig scherm";
    ls->shortcutVolumeIncrease  = "Geluidsterkte verhogen";
    ls->shortcutVolumeDecrease  = "Geluidsterkte verminderen";
    ls->shortcutVolumeMute      = "Geluid uitzetten";
    ls->shortcutVolumeStereo    = "Wisselen mono of stereo mode";
    ls->shortcutSwitchMsxAudio  = "MSX-AUDIO switch aan/uit";
    ls->shortcutSwitchFront     = "Panasonic front switch aan/uit";
    ls->shortcutSwitchPause     = "Pause switch aan/uit";
    ls->shortcutToggleMouseLock = "Muis vastzetten aan/uit";
    ls->shortcutEmuSpeedMax     = "Maximale emulatie snelheid";
    ls->shortcutEmuSpeedToggle  = "Maximum snelheid van de emulatie aan/uit";
    ls->shortcutEmuSpeedNormal  = "Normale emulatie snelheid";
    ls->shortcutEmuSpeedInc     = "Verhoog emulatie snelheid";
    ls->shortcutEmuSpeedDec     = "Verlaag emulatie snelheid";
    ls->shortcutThemeSwitch     = "Ander thema kiezen";
    ls->shortcutShowEmuProp     = "Dialoog: Emulatie eigenschappen";
    ls->shortcutShowVideoProp   = "Dialoog: Beeld";
    ls->shortcutShowAudioProp   = "Dialoog: Geluid";
    ls->shortcutShowCtrlProp    = "Dialoog: Besturing";
    ls->shortcutShowPerfProp    = "Dialoog: Prestatie";
    ls->shortcutShowSettProp    = "Dialoog: Instellingen";
    ls->shortcutShowPorts       = "Eigenschappen van poorten weergeven";
    ls->shortcutShowLanguage    = "Dialoog: Taaldialoog";
    ls->shortcutShowMachines    = "Dialoog: Machine menu";
    ls->shortcutShowShortcuts   = "Dialoog: Snelkoppelingenmenu";
    ls->shortcutShowKeyboard    = "Toetsenbord editor weergeven";
    ls->shortcutShowMixer       = "Show Mixer";
    ls->shortcutShowDebugger    = "Debugger weergeven";
    ls->shortcutShowTrainer     = "Trainer weergeven";
    ls->shortcutShowHelp        = "Dialoog: Hulpdialoog";
    ls->shortcutShowAbout       = "Dialoog: Info blueMSX";
    ls->shortcutShowFiles       = "Tonen van bestandseigenschappen";
    ls->shortcutToggleSpriteEnable = "Tonen/Verbergen sprites";
    ls->shortcutToggleFdcTiming = "Synchroniseren/Niet synchroniseren";
    ls->shortcutToggleCpuTrace  = "Toelaten/niet toelaten CPU-spoor";
    ls->shortcutVideoLoad       = "Laden...";
    ls->shortcutVideoPlay       = "Laatste opname afspelen";
    ls->shortcutVideoRecord     = "Opnemen";
    ls->shortcutVideoStop       = "Stoppen";
    ls->shortcutVideoRender     = "Maak Videobestand";


    //----------------------
    // Keyboard config lines
    //----------------------

    ls->keyconfigSelectedKey    = "Geselecteerde toets:";
    ls->keyconfigMappedTo       = "Gekoppeld aan:";
    ls->keyconfigMappingScheme  = "Koppelschema:";


    //----------------------
    // Rom type lines
    //----------------------

    ls->romTypeStandard         = "Standaard";
    ls->romTypeZenima80         = "Zemina 80 in 1";
    ls->romTypeZenima90         = "Zemina 90 in 1";
    ls->romTypeZenima126        = "Zemina 126 in 1";
    ls->romTypeSccMirrored      = "SCC mirrored";
    ls->romTypeSccExtended      = "SCC extended";
    ls->romTypeKonamiGeneric    = "Konami Generic";
    ls->romTypeMirrored         = "Mirrored ROM";
    ls->romTypeNormal           = "Normal ROM";
    ls->romTypeDiskPatch        = "Normal + Disk Patch";
    ls->romTypeCasPatch         = "Normal + Cassette Patch";
    ls->romTypeTc8566afFdc      = "TC8566AF Disk Controller";
    ls->romTypeTc8566afTrFdc    = "TC8566AF Turbo-R Disk Controller";
    ls->romTypeMicrosolFdc      = "Microsol Disk Controller";
    ls->romTypeNationalFdc      = "National Disk Controller";
    ls->romTypePhilipsFdc       = "Philips Disk Controller";
    ls->romTypeSvi738Fdc        = "SVI-738 Disk Controller";
    ls->romTypeMappedRam        = "Mapped RAM";
    ls->romTypeMirroredRam1k    = "1kB Mirrored RAM";
    ls->romTypeMirroredRam2k    = "2kB Mirrored RAM";
    ls->romTypeNormalRam        = "Normal RAM";
    ls->romTypeTurborPause      = "Turbo-R Pause";
    ls->romTypeF4deviceNormal   = "F4 Device Normal";
    ls->romTypeF4deviceInvert   = "F4 Device Inverted";
    ls->romTypeTurborTimer      = "Turbo-R Timer";
    ls->romTypeNormal4000       = "Normal 4000h";
    ls->romTypeNormalC000       = "Normal C000h";
    ls->romTypeExtRam           = "External RAM";
    ls->romTypeExtRam512        = "512kB External RAM";
    ls->romTypeExtRam1mb        = "1MB External RAM";
    ls->romTypeExtRam2mb        = "2MB External RAM";
    ls->romTypeExtRam4mb        = "4MB External RAM";
    ls->romTypeSvi328Cart       = "SVI-328 Cartridge";
    ls->romTypeSvi328Fdc        = "SVI-328 Disk Controller";
    ls->romTypeSvi328Prn        = "SVI-328 Printer";
    ls->romTypeSvi328Uart       = "SVI-328 Serial Port";
    ls->romTypeSvi328col80      = "SVI-328 80 Column Card";
    ls->romTypeSvi727col80      = "SVI-727 80 Column Card";
    ls->romTypeColecoCart       = "Coleco Cartridge";
    ls->romTypeSg1000Cart       = "SG-1000 Cartridge";
    ls->romTypeSc3000Cart       = "SC-3000 Cartridge";
    ls->romTypeMsxPrinter       = "MSX Printer";
    ls->romTypeTurborPcm        = "Turbo-R PCM Chip";
    ls->romTypeNms8280Digitiz   = "Philips NMS-8280 Digitizer";
    ls->romTypeHbiV1Digitiz     = "Sony HBI-V1 Digitizer";


    //----------------------
    // Debug type lines
    // Note: Only needs translation if debugger is translated
    //----------------------

    ls->dbgMemVisible           = "Zichtbaar geheugen";
    ls->dbgMemRamNormal         = "Normaal";
    ls->dbgMemRamMapped         = "Mapped";
    ls->dbgMemYmf278            = "YMF278 Sample RAM";
    ls->dbgMemAy8950            = "AY8950 Sample RAM";
    ls->dbgMemScc               = "Geheugen";

    ls->dbgCallstack            = "Callstack";

    ls->dbgRegs                 = "Registers";
    ls->dbgRegsCpu              = "CPU Registers";
    ls->dbgRegsYmf262           = "YMF262 Registers";
    ls->dbgRegsYmf278           = "YMF278 Registers";
    ls->dbgRegsAy8950           = "AY8950 Registers";
    ls->dbgRegsYm2413           = "YM2413 Registers";

    ls->dbgDevRamMapper         = "RAM Mapper";
    ls->dbgDevRam               = "RAM";
    ls->dbgDevF4Device          = "F4 Device";
    ls->dbgDevKorean80          = "Korean 80";
    ls->dbgDevKorean90          = "Korean 90";
    ls->dbgDevKorean128         = "Korean 128";
    ls->dbgDevFdcMicrosol       = "Microsol FDC";
    ls->dbgDevPrinter           = "Printer";
    ls->dbgDevSviFdc            = "SVI FDC";
    ls->dbgDevSviPrn            = "SVI Printer";
    ls->dbgDevSvi80Col          = "SVI 80 Column";
    ls->dbgDevRtc               = "RTC";
    ls->dbgDevTrPause           = "TR Pause";


    //----------------------
    // Debug type lines
    // Note: Can only be translated to european languages
    //----------------------
    ls->aboutScrollThanksTo     = "Speciale dank aan: ";
    ls->aboutScrollAndYou       = "en U!!!!";
};

#endif
