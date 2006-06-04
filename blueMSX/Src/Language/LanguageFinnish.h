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
    ls->errorEnterFullscreen    = "Ep�onnistuminen koko n�ytt��n siirtymisess�.           \n";
    ls->errorDirectXFailed      = "Ep�onnistuminen DirectX objektien luonnissa.           \nK�ytet��n GDI:t� oletuksena.\nTarkista Videon ominaisuudet.";
    ls->errorNoRomInZip         = "Zip arkistossa ei havaintoa .rom tiedostosta.";
    ls->errorNoDskInZip         = "Zip arkistossa ei havaintoa .dsk tiedostosta.";
    ls->errorNoCasInZip         = "Zip arkistossa ei havaintoa .cas tiedostosta.";
    ls->errorNoHelp             = "Ei pystytty paikantamaan blueMSX:n ohjeita.";
    ls->errorStartEmu           = "Ep�onnistuminen MSX-emulaattorin k�ynnistyksess�.";
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
    ls->menuInsert              = "Lis��...";
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
    ls->menuDiskDirInsert       = "Lis�� hakemisto";
    ls->menuDiskAutoStart       = "Resetoi lis��misen j�lkeen";
    ls->menuCartAutoReset       = "Resetoi lis��misen/poistamisen j�lkeen";

    ls->menuCasRewindAfterInsert = "Kelaa taaksenp�in lis��misen j�lkeen";
    ls->menuCasUseReadOnly       = "K�yt� Vain luku -kasettinauhoja";
    ls->lmenuCasSaveAs           = "Tallenna kasettinauha nimell�...";
    ls->menuCasSetPosition      = "Aseta sijainti";
    ls->menuCasRewind           = "Kelaa taaksenp�in";

    ls->menuPrnFormfeed         = "Form Feed";

    ls->menuZoomNormal          = "Normaali koko";
    ls->menuZoomDouble          = "Tupla koko";
    ls->menuZoomFullscreen      = "Koko n�ytt�";

    ls->menuPropsEmulation      = "Emulointi";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "��ni";
    ls->menuPropsControls       = "Kontrollit";
    ls->menuPropsPerformance    = "Suorituskyky";
    ls->menuPropsSettings        = "Asetukset";
    ls->menuPropsFile           = "File";
    ls->menuPropsLanguage       = "Kieli";
    ls->menuPropsPorts          = "Ports";

    ls->menuVideoSource         = "Videol�hde";
    ls->menuVideoSourceDefault  = "Videol�hdett� ei ole kytketty";
    ls->menuVideoChipAutodetect = "Tunnista videol�hde automaattisesti";
    ls->menuVideoInSource       = "Video In Source";
    ls->menuVideoInBitmap       = "Bitmap File";

    ls->menuHelpHelp            = "Ohjeen aiheet";
    ls->menuHelpAbout           = "Tietoja blueMSX:st�";

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
    ls->menuRunPause            = "Keskeyt�";
    ls->menuRunStop             = "Pys�yt�";
    ls->menuRunSoftReset        = "Hardware resetointi";
    ls->menuRunHardReset        = "Software resetointi";
    ls->menuRunCleanReset       = "Puhdas resetointi";

    ls->menuToolsMachine         = "Laitekokoonpano editori";
    ls->menuToolsShortcuts      = "Pikan�pp�in editori";
    ls->menuToolsKeyboard       = "N�pp�imist�editori";
    ls->menuToolsMixer          = "Mixer";

    ls->menuFile                = "Tiedosto";
    ls->menuRun                 = "Ajo";
    ls->menuWindow              = "Ikkuna";
    ls->menuOptions             = "Asetukset";
    ls->menuTools                = "Ty�kalut";
    ls->menuHelp                = "Ohje";


    //----------------------
    // Dialog related lines
    //----------------------

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Avaa";
    ls->dlgCancel               = "Peruuta";
    ls->dlgSave                 = "Tallenna";
    ls->dlgSaveAs               = "Tallenna nimell�...";
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
    ls->dlgInsertRom1           = "Lis�� cartridge slottiin 1";
    ls->dlgInsertRom2           = "Lis�� cartridge slottiin 2";
    ls->dlgInsertDiskA          = "Lis�� levyke levykeasemaan A";
    ls->dlgInsertDiskB          = "Lis�� levyke levykeasemaan B";
    ls->dlgInsertHarddisk       = "Insert Hard Disk";
    ls->dlgInsertCas            = "Lis�� kasettinauha";
    ls->dlgRomType              = "Rom-tyyppi:";

    ls->dlgTapeTitle            = "blueMSX - Kasettinauhan sijainti";
    ls->dlgTapeFrameText        = "Kasettinauhan sijainti";
    ls->dlgTapeCurrentPos       = "Nykyinen sijainti";
    ls->dlgTapeTotalTime        = "Kokonaispituus";
    ls->dlgTapeSetPosText        = "Kasettinauhan sijainti:";
    ls->dlgTapeCustom            = "N�yt� muokatut tiedostot";
    ls->dlgTabPosition           = "Sijainti";
    ls->dlgTabType               = "Tyyppi";
    ls->dlgTabFilename           = "Tiedoston nimi";
    ls->dlgZipReset             = "Resetoi lis��misen j�lkeen";

    ls->dlgAboutTitle           = "blueMSX - Tiedot";

    ls->dlgLangLangText         = "Valitse blueMSX:��n haluamasi kieli";
    ls->dlgLangLangTitle        = "blueMSX - Kieli";

    ls->dlgAboutAbout           = "TIEDOT\r\n=====";
    ls->dlgAboutVersion         = "Versio:";
    ls->dlgAboutBuildNumber     = "Kooste:";
    ls->dlgAboutBuildDate       = "P�iv�ys:";
    ls->dlgAboutCreat           = "Luonnut Daniel Vik";
    ls->dlgAboutDevel           = "KEHITT�J�T\r\n========";
    ls->dlgAboutThanks          = "ERIKOISKIITOKSET\r\n============";
    ls->dlgAboutLisence         = "LISENSSI\r\n"
                                  "======\r\n\r\n"
                                  "T�m� ohjelmisto toimitetaan 'sellaisena kuin se on', ilman mink��nlaista "
                                  "takuuta. Tekij�(t) eiv�t siten ota mit��n vastuuta mahdollisista vahingoista "
                                  "joita sinulle voi ilmet� t�m�n ohjelmiston k�yt�n yhteydess�.\r\n\r\n"
                                  "Lis�tietoja l�yd�t osoitteesta www.bluemsx.com.";

    ls->dlgSavePreview          = "Esikatsele";
    ls->dlgSaveDate             = "Aika talletettu:";


    //----------------------
    // Properties related lines
    //----------------------

    ls->propTitle               = "blueMSX - Ominaisuudet";
    ls->propEmulation           = "Emulointi";
    ls->propVideo               = "Video";
    ls->propSound               = "��ni";
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

    ls->propMonMonGB            = "N�ytt� ";
    ls->propMonTypeText         = "N�ytt�tyyppi:";
    ls->propMonEmuText          = "N�yt�n emulointi:";
    ls->propVideoTypeText       = "N�yt�n koko:";
    ls->propWindowSizeText      = "Ikkunan koko:";
    ls->propMonHorizStretch      = " Vaakasuora venytys";
    ls->propMonVertStretch       = " Pystysuora venytys";
    ls->propMonDeInterlace      = " De-interlace";
    ls->propMonBrightness       = "Kirkkaus:";
    ls->propMonContrast         = "Kontrasti:";
    ls->propMonSaturation       = "Kyll�isyys:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanline:";
    ls->propMonColorGhosting    = "RF-modulaattori";
    ls->propMonEffectsGB        = "Effects ";

    ls->propPerfVideoDrvGB      = "Video ";
    ls->propPerfVideoDispDrvText= "N�yt�nohjain:";
    ls->propPerfFrameSkipText   = "Frame skippaus:";
    ls->propPerfAudioDrvGB      = "Audio ";
    ls->propPerfAudioDrvText    = "��nenohjain:";
    ls->propPerfAudioBufSzText  = "��nipuskurin koko:";
    ls->propPerfEmuGB           = "Emulointi ";
    ls->propPerfSyncModeText    = "Synkronointi:";
    ls->propFullscreenResText   = "T�ysruudun resoluutio:";

    ls->propSndChipEmuGB        = "��nipiirin emulointi ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";
    ls->propSndMoonsound         = " Moonsound";
    ls->propSndMt32ToGm         = " Map MT-32 instruments to General MIDI";

    ls->propPortsLptGB          = "Parallel port ";
    ls->propPortsComGB          = "Serial ports ";
    ls->propPortsLptText        = "Port:";
    ls->propPortsCom1Text       = "Port 1:";
    ls->propPortsNone           = "Ei k�yt�ss�";
    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "Print to File";
    ls->propPortsComFile        = "Send to File";
    ls->propPortsOpenLogFile    = "Open Log File";
    ls->propPortsEmulateMsxPrn  = "Emulation:";

    ls->propSetFileHistoryGB     = "Tiedostohistoria ";
    ls->propSetFileHistorySize   = "Tiedostojen m��r� tiedostohistoriassa:";
    ls->propSetFileHistoryClear  = "Tyhjenn� historia";
    ls->propFileTypes            = " Rekister�i tiedostotyypit blueMSX:lle (.rom, .dsk, .cas, .sta)";
    ls->propWindowsEnvGB         = "Windowsin elinymp�rist� "; 
    ls->propSetScreenSaver       = " Poista n�yt�ns��st�j� k�yt�st� kun blueMSX on k�ynniss�";
    ls->propDisableWinKeys       = " Automaattinen MSX toiminto Windowsin menu-n�pp�imille"; 
    ls->propPriorityBoost        = " Nosta blueMSX:n prioriteetti�";
    ls->propScreenshotPng       = " Use Portable Network Graphics (.png) screenshots";
    ls->propClearHistory         = "Haluatko varmasti tyhjent�� tiedostohistorian ?";
    ls->propOpenRomGB           = "Avaa rom-dialogi ";
    ls->propDefaultRomType      = "Perus rom-tyyppi:";
    ls->propGuessRomType        = "Arvaa rom-tyyppi";

    ls->propSettDefSlotGB       = "Ved� ja pudota ";
    ls->propSettDefSlots        = "Lis�� rom:";
    ls->propSettDefSlot         = " Slot";
    ls->propSettDefDrives       = "Lis�� levyke:";
    ls->propSettDefDrive        = " Levykeasema";

    ls->propThemeGB             = "Teema ";
    ls->propTheme               = "Teema";


    //----------------------
    // Dropdown related lines
    //----------------------

    ls->enumVideoMonColor       = "V�rillinen";
    ls->enumVideoMonGrey        = "Mustavalkoinen";
    ls->enumVideoMonGreen       = "Vihert�v�";
    ls->enumVideoMonAmber       = "Amber";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Ei k�yt�ss�";
    ls->enumVideoEmuYc          = "Y/C kaapeli (ter�v�)";
    ls->enumVideoEmuMonitor     = "N�ytt�";
    ls->enumVideoEmuYcBlur      = "Kohiseva Y/C kaapeli";
    ls->enumVideoEmuComp        = "Komposiittikaapeli (sumea)";
    ls->enumVideoEmuCompBlur    = "Kohiseva komposiittikaapeli";
    ls->enumVideoEmuScale2x     = "2x skaalaus";
    ls->enumVideoEmuHq2x        = "Hq2x";

    ls->enumVideoSize1x         = "Normaali - 320x200";
    ls->enumVideoSize2x         = "Tupla - 640x400";
    ls->enumVideoSizeFullscreen = "Koko n�ytt�";

    ls->enumVideoDrvDirectDrawHW= "DirectDraw HW kiihdytys"; 
    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "Ei yht��n";
    ls->enumVideoFrameskip1     = "1 kuva";
    ls->enumVideoFrameskip2     = "2 kuvaa";
    ls->enumVideoFrameskip3     = "3 kuvaa";
    ls->enumVideoFrameskip4     = "4 kuvaa";
    ls->enumVideoFrameskip5     = "5 kuvaa";

    ls->enumSoundDrvNone        = "Ei ��nt�";
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
    ls->confSaveAsTitle         = "Tallenna konfiguraatio nimell�...";
    ls->confSaveAsMachineName   = "Laitekokoonpano:";
    ls->confDiscardTitle        = "blueMSX - Kokoonpano";
    ls->confExitSaveTitle       = "blueMSX - Poistu kokoonpano editorista";
    ls->confExitSaveText        = "Haluatko hyl�t� muutokset nykyiseen kokoonpanoon?";

    ls->confSlotLayoutGB        = "Slot sommite ";
    ls->confSlotExtSlotGB       = "Ulkoiset slotit ";
    ls->confBoardGB             = "Board ";
    ls->confBoardText           = "Board Tyyppi:";
    ls->confSlotPrimary         = "Ensisijainen";
    ls->confSlotExpanded        = "Laajennettu (nelj� lis�paikkaa)";

    ls->confSlotCart            = "Cartridge";
    ls->confSlot                = "Slot";
    ls->confSubslot             = "Subslot";

    ls->confMemAdd              = "Lis��...";
    ls->confMemEdit             = "Muokkaa...";
    ls->confMemRemove           = "Poista";
    ls->confMemSlot             = "Slot";
    ls->confMemAddresss         = "Osoite";
    ls->confMemType             = "Tyyppi";
    ls->confMemRomImage         = "Rom tiedosto";
    
    ls->confChipVideoGB         = "Video ";
    ls->confChipVideoChip       = "Videopiiri:";
    ls->confChipVideoRam        = "Video RAM:";
    ls->confChipSoundGB         = "��ni ";

    ls->confCmosGB                = "CMOS ";
    ls->confCmosEnable            = " Mahdollista CMOS";
    ls->confCmosBattery           = " K�yt� ladattuja pattereita";

    ls->confCpuFreqGB            = "CPU Kellotaajuus ";
    ls->confZ80FreqText          = "Z80 Kellotaajuus:";
    ls->confR800FreqText         = "R800 Kellotaajuus:";
    ls->confFdcGB                = "Levykeasemaohjain ";
    ls->confCFdcNumDrivesText    = "Levykeasemien lukum��r�:";

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
    ls->shortcutDiskDirInsertA  = "Lis�� hakemisto levykkeeksi A";
    ls->shortcutDiskRemoveA     = "Eject Diskette A";
    ls->shortcutDiskChangeA     = "Quick change Diskette A";
    ls->shortcutDiskAutoResetA  = "Reset Emulator when Diskette A is Inserted";
    ls->shortcutDiskInsertB     = "Insert Diskette B";
    ls->shortcutDiskDirInsertB  = "Lis�� hakemisto levykkeeksi B";
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
    ls->shortcutSizeMinimized   = "Pienenn� ikkuna";
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
    ls->shortcutShowKeyboard    = "N�yt� n�pp�imist�editori";
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

    ls->keyconfigSelectedKey    = "Valittu n�pp�in:";
    ls->keyconfigMappedTo       = "Mapattu n�pp�imeen:";
    ls->keyconfigMappingScheme  = "N�pp�imist�kartta:";
};

#endif
