/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageFinnish.h,v $
**
** $Revision: 1.4 $
**
** $Date: 2004-12-28 22:48:36 $
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
    ls->statusBarStopped        = "  Pys�ytetty";
    ls->statusBarPaused         = "  Keskeytetty";
    ls->statusBarRunning        = "  K�ynniss�";
    
    ls->menuHardReset           = "Hardware resetointi";
    ls->menuSoftReset           = "Software resetointi";
    
    ls->menuCartInsert          = "Lis��...";
    ls->menuCartRemove          = "Poista";
    ls->menuCartAutoReset       = "Resetoi lis��misen/poistamisen j�lkeen";
    ls->menuCartNoRecentFiles   = "- ei viimeaikaisia tiedostoja -";
    ls->menuCartFMPac           = "FM-PAC Cartridge";
    ls->menuCartPac             = "PAC Cartridge";
    ls->menuCartSpecial         = "Special";

    ls->menuDiskInsert          = "Lis��...";
    ls->menuDiskEject           = "Poista";
    ls->menuDiskAutoStart       = "Resetoi lis��misen j�lkeen";
    ls->menuDiskNoRecentFiles   = "- ei viimeaikaisia tiedostoja -";
    
    ls->menuCasInsert           = "Lis��...";
    ls->menuCasEject            = "Poista";
    ls->menuCasSetPosition      = "Aseta sijainti";
    ls->menuCasRewind           = "Kelaa taaksenp�in";
    ls->menuCasNoRecentFiles    = "- ei viimeaikaisia tiedostoja -";

    ls->menuZoomNormal          = "Normaali koko";
    ls->menuZoomDouble          = "Tupla koko";
    ls->menuZoomFullscreen      = "Koko n�ytt�";
    
    ls->menuPropsEmulation      = "Emulointi";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "��ni";
    ls->menuPropsControls       = "Kontrollit";
    ls->menuPropsPerformance    = "Suorituskyky";
    ls->menuPropsLanguage       = "Kieli";
    
    ls->menuHelpHelp            = "Ohjeen aiheet";
    ls->menuHelpAbout           = "Tietoja blueMSX:st�";

    ls->menuFileCart1           = "Cartridge Slot 1";
    ls->menuFileCart2           = "Cartridge Slot 2";
    ls->menuFileDiskA           = "Levykeasema A";
    ls->menuFileDiskB           = "Levykeasema B";
    ls->menuFileCas             = "Kasettiasema";
    ls->menuFileLoadState       = "Lataa CPU-tila";
    ls->menuFileSaveState       = "Tallenna CPU-tila";
    ls->menuFileQLoadState      = "Pikalataa CPU-tila";
    ls->menuFileQSaveState      = "Pikatallenna CPU-tila";
    ls->menuFileCaptureAudio    = "Kaappaa Audio";
    ls->menuFileScreenShot      = "Kaappaa ScreenShot";
    ls->menuFileExit            = "Lopeta";

    ls->menuRunRun              = "Suorita";
    ls->menuRunPause            = "Keskeyt�";
    ls->menuRunStop             = "Pys�yt�";
    ls->menuRunSoftReset        = "Hardware resetointi";
    ls->menuRunHardReset        = "Software resetointi";
    ls->menuRunCleanReset       = "Puhdas resetointi";

    ls->menuFile                = "Tiedosto";
    ls->menuRun                 = "Ajo";
    ls->menuWindow              = "Ikkuna";
    ls->menuOptions             = "Asetukset";
    ls->menuHelp                = "Ohje";
    
    ls->errorTitle              = "blueMSX - Virhe";
    ls->errorEnterFullscreen    = "Ep�onnistuminen koko n�ytt��n siirtymisess�.           \n";
    ls->errorDirectXFailed      = "Ep�onnistuminen DirectX objektien luonnissa.           \nK�ytet��n GDI:t� oletuksena.\nTarkista Videon ominaisuudet.";
    ls->errorNoRomInZip         = "Zip arkistossa ei havaintoa .rom tiedostosta.";
    ls->errorNoDskInZip         = "Zip arkistossa ei havaintoa .dsk tiedostosta.";
    ls->errorNoCasInZip         = "Zip arkistossa ei havaintoa .cas tiedostosta.";
    ls->errorNoHelp             = "Ei pystytty paikantamaan blueMSX:n ohjeita.";
    ls->errorStartEmu           = "Ep�onnistuminen MSX-emulaattorin k�ynnistyksess�.";

    ls->tooltipReset            = "Resetoi MSX";
    ls->tooltipCart1            = "Lis�� cartridge slottiin 1";
    ls->tooltipCart2            = "Lis�� cartridge slottiin 2";
    ls->tooltipDiskA            = "Lis�� levyke levykeasemaan A";
    ls->tooltipDiskB            = "Lis�� levyke levykeasemaan B";
    ls->tooltipCas              = "Lis�� kasettinauha kasettiasemaan";
    ls->tooltipStart            = "K�ynnist� emulointi";
    ls->tooltipResume           = "Palauta emulointi";
    ls->tooltipPause            = "Keskeyt� emulointi";
    ls->tooltipWindowSize       = "Aseta ikkunan koko";
    ls->tooltipProperties       = "Avaa Ominaisuudet";
    ls->tooltipHelp             = "Avaa Ohjeikkuna";

    ls->dlgMainWindow           = "  blueMSX";
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
    ls->dlgInsertRom1           = "Lis�� cartridge slottiin 1";
    ls->dlgInsertRom2           = "Lis�� cartridge slottiin 2";
    ls->dlgInsertDiskA          = "Lis�� levyke levykeasemaan A";
    ls->dlgInsertDiskB          = "Lis�� levyke levykeasemaan B";
    ls->dlgInsertCas            = "Lis�� kasettinauha";

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Avaa";
    ls->dlgCancel               = "Peruuta";

    ls->dlgTapeTitle            = "blueMSX - Kasettinauhan sijainti";
    ls->dlgTapeFrameText        = "Kasettinauhan sijainti";
    ls->dlgTapeCurrentPos       = "Nykyinen sijainti";
    ls->dlgTapeTotalTime        = "Kokonaispituus";

    ls->dlgZipReset             = "Resetoi lis��misen j�lkeen";

    ls->dlgAboutTitle           = "blueMSX - Tiedot";

    ls->dlgJoyTitle1            = "blueMSX - Ohjaussauvan n�pp�insetti A";
    ls->dlgJoyTitle2            = "blueMSX - Ohjaussauvan n�pp�insetti B";
    ls->dlgJoyUpText            = "Yl�s";
    ls->dlgJoyDownText          = "Alas";
    ls->dlgJoyLeftText          = "Vasen";
    ls->dlgJoyRightText         = "Oikea";
    ls->dlgJoyButton1Text       = "Nappi 1";
    ls->dlgJoyButton2Text       = "Nappi 2";
    ls->dlgJoyGB                = "N�pp�insetin asetukset ";

    ls->dlgLangLangText         = "Valitse blueMSX:��n haluamasi kieli";
    ls->dlgLangLangTitle        = "blueMSX - Kieli";

    ls->propTitle               = "blueMSX - Ominaisuudet";
    ls->propEmulation           = "Emulointi";
    ls->propVideo               = "Video";
    ls->propSound               = "��ni";
    ls->propControls            = "Kontrollit";
    ls->propPerformance         = "Suorituskyky";
    
    ls->propEmuGeneralGB        = "Yleiset ";
    ls->propEmuFamilyText       = "MSX laite:";
    ls->propEmuMemoryGB         = "Muisti ";
    ls->propEmuRamSizeText      = "RAM koko:";
    ls->propEmuVramSizeText     = "VRAM koko:";
    ls->propEmuSpeedGB          = "Emuloinnin nopeus ";
    ls->propEmuSpeedText        = "Emuloinnin nopeus:";

    ls->propMonMonGB            = "N�ytt� ";
    ls->propMonTypeText         = "N�ytt�tyyppi:";
    ls->propMonEmuText          = "N�yt�n emulointi:";
    ls->propVideoYypeText       = "N�yt�n koko:";
    ls->propWindowSizeText      = "Ikkunan koko:";

    ls->propPerfVideoDrvGB      = "Video ";
    ls->propPerfVideoDispDrvText= "N�yt�nohjain:";
    ls->propPerfFrameSkipText   = "Frame skippaus:";
    ls->propPerfAudioDrvGB      = "Audio ";
    ls->propPerfAudioDrvText    = "��nenohjain:";
    ls->propPerfAudioBufSzText  = "��nipuskurin koko:";
    ls->propPerfEmuGB           = "Emulointi ";
    ls->propPerfSyncModeText    = "Synkronointi:";

    ls->propSndChipEmuGB        = "��nipiirin emulointi ";
    ls->propSndMixerGB          = "Audiomikseri ";
    ls->propSndMonoText         = "mono";
    ls->propSndStereoText       = "stereo";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "MASTER";

    ls->propJoyPort1GB          = "Portti #1 ";
    ls->propJoyPort2GB          = "Portti #2 ";
    ls->propJoyAutofireText     = "Autotulitus:";
    ls->propJoyKeysetGB         = "Ohjaussauvan n�pp�insetti ";
    ls->propJoyKeyest1          = "M��rit� n�pp�insetti A";
    ls->propJoyKeyest2          = "M��rit� n�pp�insetti B";

    ls->enumVideoMonColor       = "V�rillinen";
    ls->enumVideoMonGrey        = "Mustavalkoinen";
    ls->enumVideoMonGreen       = "Vihert�v�";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Ei k�yt�ss�";
    ls->enumVideoEmuYc          = "Y/C kaapeli (ter�v�)";



    ls->enumVideoEmuYcBlur      = "Kohiseva Y/C kaapeli";
    ls->enumVideoEmuComp        = "Komposiittikaapeli (sumea)";
    ls->enumVideoEmuCompBlur    = "Kohiseva komposiittikaapeli";
    ls->enumVideoEmuScale2x     = "2x skaalaus";

    ls->enumVideoSize1x         = "Normaali - 320x200";
    ls->enumVideoSize2x         = "Tupla - 640x400";
    ls->enumVideoSizeFullscreen = "Koko n�ytt�";

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

    ls->enumControlsJoyNone     = "Ei mit��n";
    ls->enumControlsJoyNumpad   = "Nump�di";
    ls->enumControlsJoyKeysetA  = "N�pp�insetti A";
    ls->enumControlsJoyKeysetB  = "N�pp�insetti B";
    ls->enumControlsJoyPCjoy1   = "PC ohjaussauva #1";
    ls->enumControlsJoyPCjoy2   = "PC ohjaussauva #2";
    ls->enumControlsJoyMouse    = "Hiiri";

    ls->enumControlsAfOff       = "Poissa";
    ls->enumControlsAfSlow      = "Hidas";
    ls->enumControlsAfMedium    = "Keski-";
    ls->enumControlsAfFast      = "Nopea";

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

    // New entries
    ls->menuTools                = "Ty�kalut";
    ls->menuToolsMachine         = "Laitekokoonpano editori";
    ls->menuPropsSettings        = "Asetukset";
    ls->menuCasRewindAfterInsert = "Kelaa taaksenp�in lis��misen j�lkeen";
    ls->menuCasUseReadOnly       = "K�yt� Vain luku -kasettinauhoja";
    ls->lmenuCasSaveAs           = "Tallenna kasettinauha nimell�...";

    ls->dlgSaveCassette          = "blueMSX - Tallenna kasettinauha";
    ls->dlgTapeCustom            = "N�yt� muokatut tiedostot";
    ls->dlgTapeSetPosText        = "Kasettinauhan sijainti:";
    ls->dlgTabPosition           = "Sijainti";
    ls->dlgTabType               = "Tyyppi";
    ls->dlgTabFilename           = "Tiedoston nimi";

    ls->propSettings             = "Asetukset";
    
    ls->propSetFileHistoryGB     = "Tiedostohistoria ";
    ls->propSetFileHistorySize   = "Tiedostojen m��r� tiedostohistoriassa:";
    ls->propSetFileHistoryClear  = "Tyhjenn� historia";
    ls->propSetScreenSaverGB     = "N�yt�ns��st�j� ";
    ls->propSetScreenSaver       = " Poista n�yt�ns��st�j� k�yt�st� kun blueMSX on k�ynniss�";

    ls->confTitle                = "blueMSX - Laitekokoonpano editori";
    ls->confSave                 = "Tallenna";
    ls->confSaveAs               = "Tallenna nimell�...";
    ls->confRun                  = "Suorita";
    ls->confClose                = "Sulje";
    ls->confConfigText           = "Kokoonpano";
    ls->confSlotLayout           = "Slot sommite";
    ls->confMemory               = "Muisti";
    ls->confChipEmulation        = "Piirin emulointi";

    ls->confSlotLayoutGB         = "Slot sommite ";
    ls->confSlotExtSlotGB        = "Ulkoiset slotit ";
    ls->confSlotSlot0            = "Slot 0";
    ls->confSlotSlot1            = "Slot 1";
    ls->confSlotSlot2            = "Slot 2";
    ls->confSlotSlot3            = "Slot 3";
    ls->confSlotCart1            = "Cartridge 1:";
    ls->confSlotCart2            = "Cartridge 2:";
    ls->confSlotPrimary          = "Ensisijainen";
    ls->confSlotExpanded         = "Laajennettu (nelj� lis�paikkaa)";

    ls->confMemAdd               = "Lis��...";
    ls->confMemEdit              = "Muokkaa...";
    ls->confMemRemove            = "Poista";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Osoite";
    ls->confMemType              = "Tyyppi";
    ls->confMemRomImage          = "Rom tiedosto";
    
    ls->confSaveTitle            = "blueMSX - Tallenna kokoonpano";
    ls->confSaveText             = "Haluatko korvata nykyisen laitekokoonpanon:";

    ls->confChipVideoGB          = "Video ";
    ls->confChipVideoChip        = "Videopiiri:";
    ls->confChipVideoRam         = "Video RAM:";
    ls->confChipSoundGB          = "��ni ";

    ls->slotEditMemTitle         = "blueMSX - Editoi kartoittaja";
    ls->slotEditMemGB            = "Kartoittajan yksityiskohdat ";
    ls->slotEditMemType          = "Tyyppi:";
    ls->slotEditMemFile          = "Tiedosto:";
    ls->slotEditMemAddress       = "Osoite";
    ls->slotEditMemSize          = "Koko";
    ls->slotEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Kokoonpano";
    ls->confExitSaveTitle        = "blueMSX - Poistu kokoonpano editorista";
    ls->confExitSaveText         = "Haluatko hyl�t� muutokset nykyiseen kokoonpanoon?";

    ls->confSaveAsTitle          = "blueMSX - Tallenna laitekokoonpano nimell�...";
    ls->confSaveAsMachineName    = "Laitekokoonpano:";

    ls->confEditMemInternalRoms  = "blueMSX - Sis�iset rommit";
    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypesGB          = "Tiedostotyypit ";
    ls->propFileTypes            = " Rekister�i tiedostotyypit blueMSX:lle (.rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " Automaattinen MSX toiminto Windowsin menu-n�pp�imille"; 
    ls->propWindowsEnvGB         = "Windowsin elinymp�rist� "; 
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW kiihdytys"; 
    ls->enumVideoDrvDirectDrawHWSys = "DirectDraw mix."; 
    ls->propMonHorizStretch      = " Vaakasuora venytys";
    ls->propMonVertStretch       = " Pystysuora venytys";
    ls->propClearHistory         = "Haluatko varmasti tyhjent�� tiedostohistorian ?";

    ls->propEmuFrontSwitchGB     = "Panasonic kytkimet ";
    ls->propEmuFrontSwitch       = " Etukytkin";
    ls->propEmuAudioSwitch       = " MSX-AUDIO cartridge kytkin";


    ls->dlgCmosGB                = "CMOS ";
    ls->dlgCmosEnable            = " Mahdollista CMOS";
    ls->dlgCmosBattery           = " K�yt� ladattuja pattereita";

    ls->menuCartSnatcher        = "The Snatcher Cartridge";
    ls->menuCartSdSnatcher      = "SD-Snatcher Cartridge";
    ls->menuCartSCCMirrored     = "SCC Mirrored Cartridge";
    ls->menuCartSCCExpanded     = "SCC Expanded Cartridge";
    ls->menuCartSCCPlus         = "SCC+ Cartridge";
    ls->menuCartSCC             = "SCC Cartridge";
    
    ls->warningTitle             = "blueMSX - Warning";
    ls->tooltipStop              = "Pys�yt� emulointi";


    // New entries in 1.5.1
    ls->enumControlsJoyKeyset   = "N�pp�insetti";
    ls->propJoyConfigKeyset     = "Muokkaa n�pp�insetti";
    ls->propJoyControlText      = "Ohjaus:";
    ls->propJoyButtonText       = "Nappi";
    ls->propJoyButtonAText      = "Nappi A:";
    ls->propJoyButtonBText      = "Nappi B:";

    ls->menuToolsShortcuts      = "Pikan�pp�in editori";

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
    ls->propThemeGB             = "Teema ";
    ls->propTheme               = "Teema";
    ls->propThemeClassic        = "Classic";
    ls->propThemeBlue           = "DIGIblue";

    ls->propMonBrightness       = "Kirkkaus:";
    ls->propMonContrast         = "Kontrasti:";
    ls->propMonSaturation       = "Kyll�isyys:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanline:";

    ls->dlgRomType              = "Rom-tyyppi:";
    ls->propOpenRomGB           = "Avaa rom-dialogi ";
    ls->propDefaultRomType      = "Perus rom-tyyppi:";
    ls->propGuessRomType        = "Arvaa rom-tyyppi";

    ls->propFile                = "Tiedostot";
    ls->propSettDefSlotGB       = "Ved� ja pudota ";
    ls->propSettDefSlots        = "Lis�� rom:";
    ls->propSettDefSlot1        = " Slot 1";
    ls->propSettDefSlot2        = " Slot 2";
    ls->propSettDefDrives       = "Lis�� levyke:";
    ls->propSettDefDriveA       = " Levykeasema A";
    ls->propSettDefDriveB       = " Levykeasema B";
    ls->menuPropsFile           = "File";
    ls->shortcutShowFiles       = "Show Files Dialog";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "Lis�� hakemisto";
    ls->shortcutDiskDirInsertA  = "Lis�� hakemisto levykkeeksi A";
    ls->shortcutDiskDirInsertB  = "Lis�� hakemisto levykkeeksi B";
    ls->propMonDeInterlace      = " De-interlace";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "Paina pause-nappia";
    ls->shortcutSizeMinimized   = "Pienenn� ikkuna";
    ls->shortcutEmuSpeedToggle  = "Aseta maksimaalinen emulaationopeus";
    ls->shortcutToggleCpuTrace  = "Enabloi/Disabloi prosessorin seuraus";

    ls->enumVideoEmuMonitor     = "N�ytt�";

    ls->propEmuPauseSwitch      = " Pause-nappi";
    ls->propVideoFreqText       = "Video Kellotaajuus:";
    ls->propVideoFreqAuto       = "Auto";
    ls->propSndOversampleText   = "Oversample:";

    ls->confChipExtras          = "Ekstrat";
    ls->confBoardGB             = "Board ";
    ls->confBoardText           = "Board Tyyppi:";
    ls->dlgCpuFreqGB            = "CPU Kellotaajuus ";
    ls->dlgZ80FreqText          = "Z80 Kellotaajuus:";
    ls->dlgR800FreqText         = "R800 Kellotaajuus:";
    ls->dlgFdcGB                = "Levykeasemaohjain ";
    ls->dlgCFdcNumDrivesText    = "Levykeasemien lukum��r�:";

    ls->propPriorityBoost        = " Nosta blueMSX:n prioriteetti�";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "Disabloi levykeaseman ajoitus";
    ls->shortcutToggleFdcTiming = "Enabloi/Disabloi levykeaseman ajoitus";
    ls->propUseRegistry         = "Tallenna konfiguraatio rekisteriin";

    // New entries in 2.2
    ls->menuCartHBI55           = "Sony HBI-55 Cartridge";
};

#endif

