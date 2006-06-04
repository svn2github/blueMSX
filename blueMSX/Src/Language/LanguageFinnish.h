/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageFinnish.h,v $
**
** $Revision: 1.17 $
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
#ifndef LANGUAGE_FINNISH_H
#define LANGUAGE_FINNISH_H

#include "LanguageStrings.h"
 
void langInitFinnish(LanguageStrings* ls) 
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
    ls->warningDiscardChanges   = "Haluatko kumota muutokset?";
    ls->warningOverwriteFile    = "Do you want to overwrite the file:";
    ls->errorTitle              = "blueMSX - Virhe";
    ls->errorEnterFullscreen    = "Epäonnistuminen koko näyttöön siirtymisessä.           \n";
    ls->errorDirectXFailed      = "Epäonnistuminen DirectX objektien luonnissa.           \nKäytetään GDI:tä oletuksena.\nTarkista Videon ominaisuudet.";
    ls->errorNoRomInZip         = "Zip arkistossa ei havaintoa .rom tiedostosta.";
    ls->errorNoDskInZip         = "Zip arkistossa ei havaintoa .dsk tiedostosta.";
    ls->errorNoCasInZip         = "Zip arkistossa ei havaintoa .cas tiedostosta.";
    ls->errorNoHelp             = "Ei pystytty paikantamaan blueMSX:n ohjeita.";
    ls->errorStartEmu           = "Epäonnistuminen MSX-emulaattorin käynnistyksessä.";
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

    ls->menuNoRecentFiles       = "- ei viimeaikaisia tiedostoja -";
    ls->menuInsert              = "Lisää...";
    ls->menuEject               = "Poista";

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
    ls->menuDiskDirInsert       = "Lisää hakemisto";
    ls->menuDiskAutoStart       = "Resetoi lisäämisen jälkeen";
    ls->menuCartAutoReset       = "Resetoi lisäämisen/poistamisen jälkeen";

    ls->menuCasRewindAfterInsert = "Kelaa taaksenpäin lisäämisen jälkeen";
    ls->menuCasUseReadOnly       = "Käytä Vain luku -kasettinauhoja";
    ls->lmenuCasSaveAs           = "Tallenna kasettinauha nimellä...";
    ls->menuCasSetPosition      = "Aseta sijainti";
    ls->menuCasRewind           = "Kelaa taaksenpäin";

    ls->menuPrnFormfeed         = "Form Feed";

    ls->menuZoomNormal          = "Normaali koko";
    ls->menuZoomDouble          = "Tupla koko";
    ls->menuZoomFullscreen      = "Koko näyttö";

    ls->menuPropsEmulation      = "Emulointi";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Ääni";
    ls->menuPropsControls       = "Kontrollit";
    ls->menuPropsPerformance    = "Suorituskyky";
    ls->menuPropsSettings        = "Asetukset";
    ls->menuPropsFile           = "File";
    ls->menuPropsLanguage       = "Kieli";
    ls->menuPropsPorts          = "Ports";

    ls->menuVideoSource         = "Videolähde";
    ls->menuVideoSourceDefault  = "Videolähdettä ei ole kytketty";
    ls->menuVideoChipAutodetect = "Tunnista videolähde automaattisesti";
    ls->menuVideoInSource       = "Video In Source";
    ls->menuVideoInBitmap       = "Bitmap File";

    ls->menuHelpHelp            = "Ohjeen aiheet";
    ls->menuHelpAbout           = "Tietoja blueMSX:stä";

    ls->menuFileCart            = "Cartridge Slot";
    ls->menuFileDisk            = "Levykeasema";
    ls->menuFileCas             = "Kasettiasema";
    ls->menuFilePrn             = "Printer";
    ls->menuFileLoadState       = "Lataa CPU-tila";
    ls->menuFileSaveState       = "Tallenna CPU-tila";
    ls->menuFileQLoadState      = "Pikalataa CPU-tila";
    ls->menuFileQSaveState      = "Pikatallenna CPU-tila";
    ls->menuFileCaptureAudio    = "Kaappaa Audio";
    ls->menuFileScreenShot      = "Kaappaa ScreenShot";
    ls->menuFileExit            = "Lopeta";
    ls->menuFileHarddisk        = "Hard Disk";
    ls->menuFileHarddiskNoPesent= "No Controllers Present";

    ls->menuRunRun              = "Suorita";
    ls->menuRunPause            = "Keskeytä";
    ls->menuRunStop             = "Pysäytä";
    ls->menuRunSoftReset        = "Hardware resetointi";
    ls->menuRunHardReset        = "Software resetointi";
    ls->menuRunCleanReset       = "Puhdas resetointi";

    ls->menuToolsMachine         = "Laitekokoonpano editori";
    ls->menuToolsShortcuts      = "Pikanäppäin editori";
    ls->menuToolsKeyboard       = "Näppäimistöeditori";
    ls->menuToolsMixer          = "Mixer";

    ls->menuFile                = "Tiedosto";
    ls->menuRun                 = "Ajo";
    ls->menuWindow              = "Ikkuna";
    ls->menuOptions             = "Asetukset";
    ls->menuTools                = "Työkalut";
    ls->menuHelp                = "Ohje";


    //----------------------
    // Dialog related lines
    //----------------------

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Avaa";
    ls->dlgCancel               = "Peruuta";
    ls->dlgSave                 = "Tallenna";
    ls->dlgSaveAs               = "Tallenna nimellä...";
    ls->dlgRun                  = "Suorita";
    ls->dlgClose                = "Sulje";

    ls->dlgLoadRom              = "blueMSX - Lataa rom tiedosto";
    ls->dlgLoadDsk              = "blueMSX - Lataa dsk tiedosto";
    ls->dlgLoadCas              = "blueMSX - Lataa cas tiedosto";
    ls->dlgLoadRomDskCas        = "blueMSX - Valitse rom, dsk tai cas tiedosto ladattavaksi";
    ls->dlgLoadRomDesc          = "Valitse cartridge-kasetti ladattavaksi:";
    ls->dlgLoadDskDesc          = "Valitse levyke ladattavaksi:";
    ls->dlgLoadCasDesc          = "Valitse kasettinauha ladattavaksi:";
    ls->dlgLoadRomDskCasDesc    = "Valitse tiedosto ladattavaksi:";
    ls->dlgLoadState            = "Lataa CPU-tila";
    ls->dlgSaveState            = "Tallenna CPU-tila";
    ls->dlgSaveCassette          = "blueMSX - Tallenna kasettinauha";
    ls->dlgInsertRom1           = "Lisää cartridge slottiin 1";
    ls->dlgInsertRom2           = "Lisää cartridge slottiin 2";
    ls->dlgInsertDiskA          = "Lisää levyke levykeasemaan A";
    ls->dlgInsertDiskB          = "Lisää levyke levykeasemaan B";
    ls->dlgInsertHarddisk       = "Insert Hard Disk";
    ls->dlgInsertCas            = "Lisää kasettinauha";
    ls->dlgRomType              = "Rom-tyyppi:";

    ls->dlgTapeTitle            = "blueMSX - Kasettinauhan sijainti";
    ls->dlgTapeFrameText        = "Kasettinauhan sijainti";
    ls->dlgTapeCurrentPos       = "Nykyinen sijainti";
    ls->dlgTapeTotalTime        = "Kokonaispituus";
    ls->dlgTapeSetPosText        = "Kasettinauhan sijainti:";
    ls->dlgTapeCustom            = "Näytä muokatut tiedostot";
    ls->dlgTabPosition           = "Sijainti";
    ls->dlgTabType               = "Tyyppi";
    ls->dlgTabFilename           = "Tiedoston nimi";
    ls->dlgZipReset             = "Resetoi lisäämisen jälkeen";

    ls->dlgAboutTitle           = "blueMSX - Tiedot";

    ls->dlgLangLangText         = "Valitse blueMSX:ään haluamasi kieli";
    ls->dlgLangLangTitle        = "blueMSX - Kieli";

    ls->dlgAboutAbout           = "TIEDOT\r\n=====";
    ls->dlgAboutVersion         = "Versio:";
    ls->dlgAboutBuildNumber     = "Kooste:";
    ls->dlgAboutBuildDate       = "Päiväys:";
    ls->dlgAboutCreat           = "Luonnut Daniel Vik";
    ls->dlgAboutDevel           = "KEHITTÄJÄT\r\n========";
    ls->dlgAboutThanks          = "ERIKOISKIITOKSET\r\n============";
    ls->dlgAboutLisence         = "LISENSSI\r\n"
                                  "======\r\n\r\n"
                                  "Tämä ohjelmisto toimitetaan 'sellaisena kuin se on', ilman minkäänlaista "
                                  "takuuta. Tekijä(t) eivät siten ota mitään vastuuta mahdollisista vahingoista "
                                  "joita sinulle voi ilmetä tämän ohjelmiston käytön yhteydessä.\r\n\r\n"
                                  "Lisätietoja löydät osoitteesta www.bluemsx.com.";

    ls->dlgSavePreview          = "Esikatsele";
    ls->dlgSaveDate             = "Aika talletettu:";


    //----------------------
    // Properties related lines
    //----------------------

    ls->propTitle               = "blueMSX - Ominaisuudet";
    ls->propEmulation           = "Emulointi";
    ls->propVideo               = "Video";
    ls->propSound               = "Ääni";
    ls->propControls            = "Kontrollit";
    ls->propPerformance         = "Suorituskyky";
    ls->propSettings             = "Asetukset";
    ls->propFile                = "Tiedostot";
    ls->propPorts               = "Ports";
    
    ls->propEmuGeneralGB        = "Yleiset ";
    ls->propEmuFamilyText       = "MSX laite:";
    ls->propEmuMemoryGB         = "Muisti ";
    ls->propEmuRamSizeText      = "RAM koko:";
    ls->propEmuVramSizeText     = "VRAM koko:";
    ls->propEmuSpeedGB          = "Emuloinnin nopeus ";
    ls->propEmuSpeedText        = "Emuloinnin nopeus:";
    ls->propEmuFrontSwitchGB     = "Panasonic kytkimet ";
    ls->propEmuFrontSwitch       = " Etukytkin";
    ls->propEmuFdcTiming        = "Disabloi levykeaseman ajoitus";
    ls->propEmuPauseSwitch      = " Pause-nappi";
    ls->propEmuAudioSwitch       = " MSX-AUDIO cartridge kytkin";
    ls->propVideoFreqText       = "Video Kellotaajuus:";
    ls->propVideoFreqAuto       = "Auto";
    ls->propSndOversampleText   = "Oversample:";
    ls->propSndMidiInGB         = "MIDI In ";
    ls->propSndMidiOutGB        = "MIDI Out ";

    ls->propMonMonGB            = "Näyttö ";
    ls->propMonTypeText         = "Näyttötyyppi:";
    ls->propMonEmuText          = "Näytön emulointi:";
    ls->propVideoTypeText       = "Näytön koko:";
    ls->propWindowSizeText      = "Ikkunan koko:";
    ls->propMonHorizStretch      = " Vaakasuora venytys";
    ls->propMonVertStretch       = " Pystysuora venytys";
    ls->propMonDeInterlace      = " De-interlace";
    ls->propMonBrightness       = "Kirkkaus:";
    ls->propMonContrast         = "Kontrasti:";
    ls->propMonSaturation       = "Kylläisyys:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanline:";
    ls->propMonColorGhosting    = "RF-modulaattori";
    ls->propMonEffectsGB        = "Effects ";

    ls->propPerfVideoDrvGB      = "Video ";
    ls->propPerfVideoDispDrvText= "Näytönohjain:";
    ls->propPerfFrameSkipText   = "Frame skippaus:";
    ls->propPerfAudioDrvGB      = "Audio ";
    ls->propPerfAudioDrvText    = "Äänenohjain:";
    ls->propPerfAudioBufSzText  = "Äänipuskurin koko:";
    ls->propPerfEmuGB           = "Emulointi ";
    ls->propPerfSyncModeText    = "Synkronointi:";
    ls->propFullscreenResText   = "Täysruudun resoluutio:";

    ls->propSndChipEmuGB        = "Äänipiirin emulointi ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";
    ls->propSndMoonsound         = " Moonsound";
    ls->propSndMt32ToGm         = " Map MT-32 instruments to General MIDI";

    ls->propPortsLptGB          = "Parallel port ";
    ls->propPortsComGB          = "Serial ports ";
    ls->propPortsLptText        = "Port:";
    ls->propPortsCom1Text       = "Port 1:";
    ls->propPortsNone           = "Ei käytössä";
    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "Print to File";
    ls->propPortsComFile        = "Send to File";
    ls->propPortsOpenLogFile    = "Open Log File";
    ls->propPortsEmulateMsxPrn  = "Emulation:";

    ls->propSetFileHistoryGB     = "Tiedostohistoria ";
    ls->propSetFileHistorySize   = "Tiedostojen määrä tiedostohistoriassa:";
    ls->propSetFileHistoryClear  = "Tyhjennä historia";
    ls->propFileTypes            = " Rekisteröi tiedostotyypit blueMSX:lle (.rom, .dsk, .cas, .sta)";
    ls->propWindowsEnvGB         = "Windowsin elinympäristö "; 
    ls->propSetScreenSaver       = " Poista näytönsäästäjä käytöstä kun blueMSX on käynnissä";
    ls->propDisableWinKeys       = " Automaattinen MSX toiminto Windowsin menu-näppäimille"; 
    ls->propPriorityBoost        = " Nosta blueMSX:n prioriteettiä";
    ls->propScreenshotPng       = " Use Portable Network Graphics (.png) screenshots";
    ls->propClearHistory         = "Haluatko varmasti tyhjentää tiedostohistorian ?";
    ls->propOpenRomGB           = "Avaa rom-dialogi ";
    ls->propDefaultRomType      = "Perus rom-tyyppi:";
    ls->propGuessRomType        = "Arvaa rom-tyyppi";

    ls->propSettDefSlotGB       = "Vedä ja pudota ";
    ls->propSettDefSlots        = "Lisää rom:";
    ls->propSettDefSlot         = " Slot";
    ls->propSettDefDrives       = "Lisää levyke:";
    ls->propSettDefDrive        = " Levykeasema";

    ls->propThemeGB             = "Teema ";
    ls->propTheme               = "Teema";


    //----------------------
    // Dropdown related lines
    //----------------------

    ls->enumVideoMonColor       = "Värillinen";
    ls->enumVideoMonGrey        = "Mustavalkoinen";
    ls->enumVideoMonGreen       = "Vihertävä";
    ls->enumVideoMonAmber       = "Amber";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Ei käytössä";
    ls->enumVideoEmuYc          = "Y/C kaapeli (terävä)";
    ls->enumVideoEmuMonitor     = "Näyttö";
    ls->enumVideoEmuYcBlur      = "Kohiseva Y/C kaapeli";
    ls->enumVideoEmuComp        = "Komposiittikaapeli (sumea)";
    ls->enumVideoEmuCompBlur    = "Kohiseva komposiittikaapeli";
    ls->enumVideoEmuScale2x     = "2x skaalaus";
    ls->enumVideoEmuHq2x        = "Hq2x";

    ls->enumVideoSize1x         = "Normaali - 320x200";
    ls->enumVideoSize2x         = "Tupla - 640x400";
    ls->enumVideoSizeFullscreen = "Koko näyttö";

    ls->enumVideoDrvDirectDrawHW= "DirectDraw HW kiihdytys"; 
    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "Ei yhtään";
    ls->enumVideoFrameskip1     = "1 kuva";
    ls->enumVideoFrameskip2     = "2 kuvaa";
    ls->enumVideoFrameskip3     = "3 kuvaa";
    ls->enumVideoFrameskip4     = "4 kuvaa";
    ls->enumVideoFrameskip5     = "5 kuvaa";

    ls->enumSoundDrvNone        = "Ei ääntä";
    ls->enumSoundDrvWMM         = "WMM ohjain";
    ls->enumSoundDrvDirectX     = "DirectX ohjain";

    ls->enumEmuSync1ms          = "1ms (paras)";
    ls->enumEmuSyncAuto         = "Auto (nopea)";
    ls->enumEmuSyncNone         = "None";
    ls->enumEmuSyncVblank       = "Sync to PC Vertical Blank";

    ls->enumControlsJoyNone     = "None";
    ls->enumControlsJoyMouse    = "Mouse";
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle";
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey Dongle";


    //----------------------
    // Configuration related lines
    //----------------------

    ls->confTitle               = "blueMSX - Laitekokoonpano editori";
    ls->confConfigText          = "Kokoonpano";
    ls->confSlotLayout          = "Slot sommite";
    ls->confMemory              = "Muisti";
    ls->confChipEmulation       = "Piirin emulointi";
    ls->confChipExtras          = "Ekstrat";

    ls->confOpenRom             = "Open ROM image";
    ls->confSaveTitle           = "blueMSX - Tallenna kokoonpano";
    ls->confSaveText            = "Haluatko korvata nykyisen laitekokoonpanon:";
    ls->confSaveAsTitle         = "Tallenna konfiguraatio nimellä...";
    ls->confSaveAsMachineName   = "Laitekokoonpano:";
    ls->confDiscardTitle        = "blueMSX - Kokoonpano";
    ls->confExitSaveTitle       = "blueMSX - Poistu kokoonpano editorista";
    ls->confExitSaveText        = "Haluatko hylätä muutokset nykyiseen kokoonpanoon?";

    ls->confSlotLayoutGB        = "Slot sommite ";
    ls->confSlotExtSlotGB       = "Ulkoiset slotit ";
    ls->confBoardGB             = "Board ";
    ls->confBoardText           = "Board Tyyppi:";
    ls->confSlotPrimary         = "Ensisijainen";
    ls->confSlotExpanded        = "Laajennettu (neljä lisäpaikkaa)";

    ls->confSlotCart            = "Cartridge";
    ls->confSlot                = "Slot";
    ls->confSubslot             = "Subslot";

    ls->confMemAdd              = "Lisää...";
    ls->confMemEdit             = "Muokkaa...";
    ls->confMemRemove           = "Poista";
    ls->confMemSlot             = "Slot";
    ls->confMemAddresss         = "Osoite";
    ls->confMemType             = "Tyyppi";
    ls->confMemRomImage         = "Rom tiedosto";
    
    ls->confChipVideoGB         = "Video ";
    ls->confChipVideoChip       = "Videopiiri:";
    ls->confChipVideoRam        = "Video RAM:";
    ls->confChipSoundGB         = "Ääni ";

    ls->confCmosGB                = "CMOS ";
    ls->confCmosEnable            = " Mahdollista CMOS";
    ls->confCmosBattery           = " Käytä ladattuja pattereita";

    ls->confCpuFreqGB            = "CPU Kellotaajuus ";
    ls->confZ80FreqText          = "Z80 Kellotaajuus:";
    ls->confR800FreqText         = "R800 Kellotaajuus:";
    ls->confFdcGB                = "Levykeasemaohjain ";
    ls->confCFdcNumDrivesText    = "Levykeasemien lukumäärä:";

    ls->confEditMemTitle        = "blueMSX - Editoi kartoittaja";
    ls->confEditMemGB           = "Kartoittajan yksityiskohdat ";
    ls->confEditMemType         = "Tyyppi:";
    ls->confEditMemFile         = "Tiedosto:";
    ls->confEditMemAddress      = "Osoite";
    ls->confEditMemSize         = "Koko";
    ls->confEditMemSlot         = "Slot";


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
    ls->shortcutDiskDirInsertA  = "Lisää hakemisto levykkeeksi A";
    ls->shortcutDiskRemoveA     = "Eject Diskette A";
    ls->shortcutDiskChangeA     = "Quick change Diskette A";
    ls->shortcutDiskAutoResetA  = "Reset Emulator when Diskette A is Inserted";
    ls->shortcutDiskInsertB     = "Insert Diskette B";
    ls->shortcutDiskDirInsertB  = "Lisää hakemisto levykkeeksi B";
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
    ls->shortcutResetClean      = "General Reset";
    ls->shortcutSizeSmall       = "Set small window size";
    ls->shortcutSizeNormal      = "Set normal window size";
    ls->shortcutSizeFullscreen  = "Set fullscreen";
    ls->shortcutSizeMinimized   = "Pienennä ikkuna";
    ls->shortcutToggleFullscren = "Toggle fullscreen";
    ls->shortcutVolumeIncrease  = "Increase Volume";
    ls->shortcutVolumeDecrease  = "Decrease Volume";
    ls->shortcutVolumeMute      = "Mute Volume";
    ls->shortcutVolumeStereo    = "Toggle mono/stereo";
    ls->shortcutSwitchMsxAudio  = "Toggle MSX-AUDIO switch";
    ls->shortcutSwitchFront     = "Toggle Panasonic front switch";
    ls->shortcutSwitchPause     = "Paina pause-nappia";
    ls->shortcutToggleMouseLock = "Toggle mouse lock";
    ls->shortcutEmuSpeedMax     = "Max emulation speed";
    ls->shortcutEmuSpeedToggle  = "Aseta maksimaalinen emulaationopeus";
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
    ls->shortcutShowKeyboard    = "Näytä näppäimistöeditori";
    ls->shortcutShowMixer       = "Show Mixer";
    ls->shortcutShowDebugger    = "Show Debugger";
    ls->shortcutShowTrainer     = "Show Trainer";
    ls->shortcutShowHelp        = "Show Help Dialog";
    ls->shortcutShowAbout       = "Show About Dialog";
    ls->shortcutShowFiles       = "Show Files Dialog";
    ls->shortcutToggleSpriteEnable = "Show/Hide Sprites";
    ls->shortcutToggleFdcTiming = "Enabloi/Disabloi levykeaseman ajoitus";
    ls->shortcutToggleCpuTrace  = "Enabloi/Disabloi prosessorin seuraus";
    
 
    //----------------------
    // Keyboard config lines
    //----------------------

    ls->keyconfigSelectedKey    = "Valittu näppäin:";
    ls->keyconfigMappedTo       = "Mapattu näppäimeen:";
    ls->keyconfigMappingScheme  = "Näppäimistökartta:";
};

#endif
