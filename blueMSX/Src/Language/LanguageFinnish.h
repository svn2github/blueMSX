/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageFinnish.h,v $
**
** $Revision: 1.29 $
**
** $Date: 2006-06-23 19:09:49 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2006 Daniel Vik, NYYRIKKI
**
** Translated By : NYYRIKKI 2006
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

    ls->textDevice              = "Laite:";
    ls->textFilename            = "Tiedostonimi:";
    ls->textFile                = "Tiedosto";
    ls->textNone                = "Ei k�yt�ss�";
    ls->textUnknown             = "Tuntematon";


    //----------------------
    // Warning and Error lines
    //----------------------

    ls->warningTitle            = "blueMSX - Varoitus";
    ls->warningDiscardChanges   = "Haluatko perua tekem�si muutokset?";
    ls->warningOverwriteFile    = "Haluatko korvata tiedoston:";
    ls->errorTitle              = "blueMSX - Virhe";
    ls->errorEnterFullscreen    = "Siirtyminen kokoruututilaan ep�onnistui.  \n";
    ls->errorDirectXFailed      = "DirectX objektien luonti ep�onnistui.      \nDirectX on korvattu GDI:ll�.\nTarkista video asetukset.";
    ls->errorNoRomInZip         = "Zip paketista ei l�ytynyt .ROM tiedostoa.";
    ls->errorNoDskInZip         = "Zip paketista ei l�ytynyt .DSK tiedostoa.";
    ls->errorNoCasInZip         = "Zip paketista ei l�ytynyt .CAS tiedostoa.";
    ls->errorNoHelp             = "blueMSX:n ohje tiedostoa ei l�ytynyt.";
    ls->errorStartEmu           = "MSX emulaattorin k�ynnistys ep�onnistui.";
    ls->errorPortableReadonly   = "Kannettava laite tukee vain lukemista.";


    //----------------------
    // File related lines
    //----------------------

    ls->fileRom                 = "ROM tiedosto";
    ls->fileAll                 = "Kaikki tiedostot";
    ls->fileCpuState            = "Tilanne tallenne";
    ls->fileDisk                = "Levy tiedosto";
    ls->fileCas                 = "Kasetti tiedosto";


    //----------------------
    // Menu related lines
    //----------------------

    ls->menuNoRecentFiles       = "- ei viimeaikaisia tiedostoja -";
    ls->menuInsert              = "Aseta...";
    ls->menuEject               = "Poista";

    ls->menuCartGameReader      = "Game Reader";
    ls->menuCartIde             = "IDE";
    ls->menuCartBeerIde         = "Beer";
    ls->menuCartGIde            = "GIDE";
    ls->menuCartSunriseIde      = "Sunrise";
    ls->menuCartSCC             = "SCC Moduli";
    ls->menuCartSCCPlus         = "SCC+ Moduli";
    ls->menuCartFMPac           = "FM-PAC Moduli";
    ls->menuCartPac             = "PAC Moduli";
    ls->menuCartHBI55           = "Sony HBI-55 Moduli";
    ls->menuCartInsertSpecial   = "Erikois moduli";
    ls->menuCartMegaRam         = "MegaRAM";
    ls->menuCartExternalRam     = "Ulkoinen muisti";

    ls->menuDiskInsertNew       = "Uusi levytiedosto";
    ls->menuDiskDirInsert       = "Aseta hakemisto";
    ls->menuDiskAutoStart       = "K�ynnist� uudelleen asettamisen j�lkeen";
    ls->menuCartAutoReset       = "K�ynnist� uudelleen muutettaessa";

    ls->menuCasRewindAfterInsert = "Kelaa alkuun asetettaessa";
    ls->menuCasUseReadOnly       = "Kirjoitussuojaa kasetti";
    ls->lmenuCasSaveAs           = "Tallenna kasetti nimell�";
    ls->menuCasSetPosition      = "Valitse kohta";
    ls->menuCasRewind           = "Kelaa alkuun";

    ls->menuPrnFormfeed         = "Paperin vaihto";

    ls->menuZoomNormal          = "Pieni koko";
    ls->menuZoomDouble          = "Normaali koko";
    ls->menuZoomFullscreen      = "Kokoruututila";

    ls->menuPropsEmulation      = "Emulaatio";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "��ni";
    ls->menuPropsControls       = "Kontrollit";
    ls->menuPropsPerformance    = "Suorituskyky";
    ls->menuPropsSettings       = "Asetukset";
    ls->menuPropsFile           = "Tiedostot";
    ls->menuPropsLanguage       = "Kieli";
    ls->menuPropsPorts          = "Liit�nn�t";
    
    ls->menuVideoSource         = "Video Ulostulo";
    ls->menuVideoSourceDefault  = "Video Ulostuloa ei ole kytketty.";
    ls->menuVideoChipAutodetect = "Tunnista videopiiri automaattisesti";
    ls->menuVideoInSource       = "Video Sis��ntulo";
    ls->menuVideoInBitmap       = "Bittikartta tiedosto";

    ls->menuHelpHelp            = "Ohjeen aiheet";
    ls->menuHelpAbout           = "Tietoja blueMSX:st�";

    ls->menuFileCart            = "Moduliportti";
    ls->menuFileDisk            = "Levyasema";
    ls->menuFileCas             = "Kasetti";
    ls->menuFilePrn             = "Tulostin";
    ls->menuFileLoadState       = "Lataa tila...";
    ls->menuFileSaveState       = "Tallenna tila nimell�";
    ls->menuFileQLoadState      = "Tilan pikalataus";
    ls->menuFileQSaveState      = "Tilan pikatallennus";
    ls->menuFileCaptureAudio    = "Tallenna ��net";
    ls->menuFileScreenShot      = "Tallenna kuvaruutukaappaus";
    ls->menuFileExit            = "Poistu";
    ls->menuFileHarddisk        = "Kovalevy";
    ls->menuFileHarddiskNoPesent= "Ohjaimia ei ole kytketty";

    ls->menuRunRun              = "K�ynnist�";
    ls->menuRunPause            = "Keskeyt�";
    ls->menuRunStop             = "Pys�yt�";
    ls->menuRunSoftReset        = "L�mmink�ynnistys";
    ls->menuRunHardReset        = "Kylm�k�ynnistys";
    ls->menuRunCleanReset       = "T�ydellinen uudelleenk�ynnistys";

    ls->menuToolsMachine        = "Tietokone muokkain";
    ls->menuToolsShortcuts      = "Pikan�pp�in asetukset";
    ls->menuToolsKeyboard       = "Peliohjaimet / N�pp�imist�kartta";
    ls->menuToolsMixer          = "Mikseri";
    ls->menuToolsDebugger       = "Debugger";               // New in 2.5
    ls->menuToolsTrainer        = "Trainer";                // New in 2.5
    ls->menuToolsTraceLogger    = "Seurantalogi";         // New in 2.5

    ls->menuFile                = "Tiedosto";
    ls->menuRun                 = "Emulaatio";
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
    ls->dlgSaveAs               = "Tallenna nimell�";
    ls->dlgRun                  = "K�ynnist�";
    ls->dlgClose                = "Sulje";

    ls->dlgLoadRom              = "blueMSX - Lataa rom tiedosto";
    ls->dlgLoadDsk              = "blueMSX - Lataa dsk tiedosto";
    ls->dlgLoadCas              = "blueMSX - Lataa cas tiedosto";
    ls->dlgLoadRomDskCas        = "blueMSX - Valitse ladatava rom, dsk tai cas tiedosto";
    ls->dlgLoadRomDesc          = "Valitse ladattava ROM-tiedosto:";
    ls->dlgLoadDskDesc          = "Valitse ladattava levytiedosto:";
    ls->dlgLoadCasDesc          = "Valitse ladattava kasettitiedosto:";
    ls->dlgLoadRomDskCasDesc    = "Valitse ladattava ROM-, kasetti- tai levytiedosto:";
    ls->dlgLoadState            = "Lataa tila";
    ls->dlgSaveState            = "Tallenna tila nimell�";
    ls->dlgSaveCassette         = "blueMSX - Tallenna kasetti";
    ls->dlgInsertRom1           = "Aseta moduli porttiin 1";
    ls->dlgInsertRom2           = "Aseta moduli porttiin 2";
    ls->dlgInsertDiskA          = "Aseta levy asemaan A";
    ls->dlgInsertDiskB          = "Aseta levy asemaan B";
    ls->dlgInsertHarddisk       = "Aseta kovalevy";
    ls->dlgInsertCas            = "Aseta kasetti";
    ls->dlgRomType              = "ROM-malli:";

    ls->dlgTapeTitle            = "blueMSX - Kasetin kohta";
    ls->dlgTapeFrameText        = "Kasetin kohta";
    ls->dlgTapeCurrentPos       = "T�m�nhetkinen kohta";
    ls->dlgTapeTotalTime        = "Kokonaispituus";
    ls->dlgTapeSetPosText       = "Kasetin kohta:";
    ls->dlgTapeCustom           = "N�yt� erilliset tiedostojen osat";
    ls->dlgTabPosition          = "Kohta";
    ls->dlgTabType              = "Tyyppi";
    ls->dlgTabFilename          = "Tiedostonimi";
    ls->dlgZipReset             = "Uudelleenk�ynnistys asettamisen j�lkeen";

    ls->dlgAboutTitle           = "Tietoja blueMSX:st�";

    ls->dlgLangLangText         = "Valitse k�ytett�v� kieli";
    ls->dlgLangLangTitle        = "blueMSX - Kielivalinta";

    ls->dlgAboutAbout           = "TIEDOT\r\n====";
    ls->dlgAboutVersion         = "Versio:";
    ls->dlgAboutBuildNumber     = "K��nn�s:";
    ls->dlgAboutBuildDate       = "P�iv�ys:";
    ls->dlgAboutCreat           = "Tekij�: Daniel Vik";
    ls->dlgAboutDevel           = "KEHITT�J�T\r\n=======";
    ls->dlgAboutThanks          = "ERITYIS KIITOKSET\r\n===========";
    ls->dlgAboutLisence         = "LISENSSI\r\n"
                                  "=====\r\n\r\n"
                                  "T�m� ohjelmisto toimitetaan sellaisenaan ilman mink��nlaista takuuta. "
                                  "Kehitt�j�t eiv�t ota mit��n vastuuta ohjelman kayt�ss� tai k�yt�st� "
                                  "aiheutuneista mahdollisista ongelmista tai vahingoista.\r\n\r\n"
                                  "Lis�tietoja l�yd�t osoitteesta www.bluemsx.com.";

    ls->dlgSavePreview          = "N�yt� Esikatselu";
    ls->dlgSaveDate             = "Tallennettu:";


    //----------------------
    // Properties related lines
    //----------------------

    ls->propTitle               = "blueMSX - Ominaisuudet";
    ls->propEmulation           = "Emulaatio";
    ls->propVideo               = "Video";
    ls->propSound               = "��ni";
    ls->propControls            = "Kontrollit";
    ls->propPerformance         = "Suorituskyky";
    ls->propSettings            = "Asetukset";
    ls->propFile                = "Tiedostot";
    ls->propPorts               = "Liit�nn�t";

    ls->propEmuGeneralGB        = "Yleist� ";
    ls->propEmuFamilyText       = "MSX malli:";
    ls->propEmuMemoryGB         = "Muisti ";
    ls->propEmuRamSizeText      = "RAM koko:";
    ls->propEmuVramSizeText     = "VRAM koko:";
    ls->propEmuSpeedGB          = "Emulaatio Nopeus ";
    ls->propEmuSpeedText        = "Emulaatio Nopeus:";
    ls->propEmuFrontSwitchGB     = "Panasonicin Kytkimet ";
    ls->propEmuFrontSwitch       = " Aplikaatio kytkin";
    ls->propEmuFdcTiming        = " Poista k�yt�st� levyaseman ajoitus";
    ls->propEmuPauseSwitch      = " PAUSE-n�pp�in";
    ls->propEmuAudioSwitch       = " MSX-AUDIO modulin kytkin";
    ls->propVideoFreqText       = "Video Taajuus:";
    ls->propVideoFreqAuto       = "Automaattinen";
    ls->propSndOversampleText   = "Ylin�ytteistys:";
    ls->propSndYkInGB           = "YK-01/YK-10/YK-20 Sis��n ";                // New in 2.5
    ls->propSndMidiInGB         = "MIDI Sis��n ";
    ls->propSndMidiOutGB        = "MIDI Ulos ";
    ls->propSndMidiChannel      = "MIDI Kanava:";                      // New in 2.5
    ls->propSndMidiAll          = "Kaikki";                                // New in 2.5

    ls->propMonMonGB            = "Monitori ";
    ls->propMonTypeText         = "Monitorin tyyppi:";
    ls->propMonEmuText          = "Monitorin emulointi:";
    ls->propVideoTypeText       = "Video tyyppi:";
    ls->propWindowSizeText      = "Ikkunan koko:";
    ls->propMonHorizStretch     = " Vaaka Venytys";
    ls->propMonVertStretch      = " Pysty Venytys";
    ls->propMonDeInterlace      = " Lomituksen purku";
    ls->propBlendFrames         = " Yhdist� per�kk�iset kuvat";
    ls->propMonBrightness       = "Kirkkaus:";
    ls->propMonContrast         = "Kontrasti:";
    ls->propMonSaturation       = "Saturaatio:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = " Juovat:";
    ls->propMonColorGhosting    = " Antenni muunnos:";
    ls->propMonEffectsGB        = "Tehosteet ";

    ls->propPerfVideoDrvGB      = "Video Ajuri ";
    ls->propPerfVideoDispDrvText= "N�ytt� ajuri:";
    ls->propPerfFrameSkipText   = "Ruudunp�ivitysten ohitus:";
    ls->propPerfAudioDrvGB      = "��ni ajuri ";
    ls->propPerfAudioDrvText    = "��ni ajuri:";
    ls->propPerfAudioBufSzText  = "��nipuskurin koko:";
    ls->propPerfEmuGB           = "Emulaatio ";
    ls->propPerfSyncModeText    = "Tahdistus tapa:";
    ls->propFullscreenResText   = "Resoluutio kokoruututilassa:";

    ls->propSndChipEmuGB        = "��nipiirien emulointi ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";
    ls->propSndMoonsound        = " Moonsound";
    ls->propSndMt32ToGm         = " Muunna MT-32 soittimet General MIDI soittimiksi";

    ls->propPortsLptGB          = "Rinnakkaisportti ";
    ls->propPortsComGB          = "Sarjaportit ";
    ls->propPortsLptText        = "Portti:";
    ls->propPortsCom1Text       = "Portti 1:";
    ls->propPortsNone           = "Ei mit��n";
    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "Tulosta tiedostoon";
    ls->propPortsComFile        = "L�hetys tiedostoon";
    ls->propPortsOpenLogFile    = "Avaa lokitiedosto";
    ls->propPortsEmulateMsxPrn  = "Emulaatio:";

    ls->propSetFileHistoryGB    = "Tiedostohistoria ";
    ls->propSetFileHistorySize  = "Tiedostojen lukum��r�:";
    ls->propSetFileHistoryClear = "Tyhjenn� historia";
    ls->propFileTypes           = " Rekister�i tiedostotyypit blueMSX:��n (.rom, .dsk, .cas, .sta)";
    ls->propWindowsEnvGB        = "Windows Ymp�rist� ";
    ls->propSetScreenSaver      = " Poista ruuduns��st�j� k�yt�st�, kun blueMSX on k�ynniss�";
    ls->propDisableWinKeys      = " Ota Windows-n�pp�imet MSX k�ytt��n";
    ls->propPriorityBoost       = " Nosta blueMSX:n prioriteettia";
    ls->propScreenshotPng       = " Tallenna kuvaruutukaappaukset PNG-muodossa";
    ls->propClearHistory        = "Oletko varma, ett� haluat poistaa kaikki tiedostohistorian tiedot ?";
    ls->propOpenRomGB           = "ROM-tiedostojen avaus ";
    ls->propDefaultRomType      = "Oletus ROM tyyppi:";
    ls->propGuessRomType        = "Arvaa ROM tyyppi";

    ls->propSettDefSlotGB       = "Tiedostojen raahaaminen emulaattoriin ";
    ls->propSettDefSlots        = "Aseta ROM Moduliporttiin:";
    ls->propSettDefSlot         = " Moduliportti";
    ls->propSettDefDrives       = "Aseta levy asemaan:";
    ls->propSettDefDrive        = " Levysema";

    ls->propThemeGB             = "Teemat ";
    ls->propTheme               = "Teema:";


    //----------------------
    // Dropdown related lines
    //----------------------

    ls->enumVideoMonColor       = "V�rillinen";
    ls->enumVideoMonGrey        = "Mustavalko";
    ls->enumVideoMonGreen       = "Vihermusta";
    ls->enumVideoMonAmber       = "Amber";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Ei k�yt�ss�";
    ls->enumVideoEmuYc          = "Y/C kaapeli (tarkka)";
    ls->enumVideoEmuMonitor     = "Monitori";
    ls->enumVideoEmuYcBlur      = "Kohiseva Y/C kaapeli (tarkka)";
    ls->enumVideoEmuComp        = "Komposiitti (samea)";
    ls->enumVideoEmuCompBlur    = "Kohiseva Komposiitti (samea)";
    ls->enumVideoEmuScale2x     = "Scale 2x";
    ls->enumVideoEmuHq2x        = "Hq2x";

    ls->enumVideoSize1x         = "Pieni - 320x200";
    ls->enumVideoSize2x         = "Normaali - 640x400";
    ls->enumVideoSizeFullscreen = "Kokoruututila";

    ls->enumVideoDrvDirectDrawHW= "Kiihdytetty DirectDraw";
    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "Ei k�yt�ss�";
    ls->enumVideoFrameskip1     = "1 p�ivitys";
    ls->enumVideoFrameskip2     = "2 p�ivityst�";
    ls->enumVideoFrameskip3     = "3 p�ivityst�";
    ls->enumVideoFrameskip4     = "4 p�ivityst�";
    ls->enumVideoFrameskip5     = "5 p�ivityst�";

    ls->enumSoundDrvNone        = "Ei ��nt�";
    ls->enumSoundDrvWMM         = "WMM ajuri";
    ls->enumSoundDrvDirectX     = "DirectX ajuri";

    ls->enumEmuSync1ms          = "Tahdistus MSX:n ruudunp�ivitykseen";
    ls->enumEmuSyncAuto         = "Automaattinen (nopea)";
    ls->enumEmuSyncNone         = "Ei k�yt�ss�";
    ls->enumEmuSyncVblank       = "Tahdistus PC:n ruudunp�ivitykseen";
    ls->enumEmuAsyncVblank      = "Tahdistamaton PC:n ruudunp�ivitys";           // New in 2.5

    ls->enumControlsJoyNone     = "Tyhj�";
    ls->enumControlsJoyMouse    = "Hiiri";
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle";
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey Dongle";
    ls->enumControlsJoy2Button = "2-n�pp�iminen Joystick";                   // New in 2.5
    ls->enumControlsJoyGunstick  = "Gun Stick-valopistooli";                      // New in 2.5
    ls->enumControlsJoyAsciiLaser="ASCII Plus-X Terminator Laser";      // New in 2.5
    ls->enumControlsJoyColeco = "ColecoVision Joystick";                // New in 2.5


    //----------------------
    // Configuration related lines
    //----------------------

    ls->confTitle               = "blueMSX - Tietokone muokkain";
    ls->confConfigText          = "Tietokone profiili:";
    ls->confSlotLayout          = "Slotti j�rjestys";
    ls->confMemory              = "Muisti";
    ls->confChipEmulation       = "Piirien Emulointi";
    ls->confChipExtras          = "Muuta";

    ls->confOpenRom             = "Valitse ROM tiedosto";
    ls->confSaveTitle           = "blueMSX - Tallenna Tietokone profiili";
    ls->confSaveText            = "Haluatko korvata Tietokone profiilin:";
    ls->confSaveAsTitle         = "Tallenna tietokone profiili nimell�...";
    ls->confSaveAsMachineName   = "Tietokone profiili:";
    ls->confDiscardTitle        = "blueMSX - Tietokone muokkain";
    ls->confExitSaveTitle       = "blueMSX - Poistu tietokone muokkaimesta";
    ls->confExitSaveText        = "Haluatko hyl�t� tekem�si muutokset nykyiseen tietokone profiiliin?";

    ls->confSlotLayoutGB        = "Slotti jako ";
    ls->confSlotExtSlotGB       = "Ulkoiset Slotit ";
    ls->confBoardGB             = "Emolevy ";
    ls->confBoardText           = "Emolevy tyyppi:";
    ls->confSlotPrimary         = "Jakamaton";
    ls->confSlotExpanded        = "Jaettu (4 alislottia)";

    ls->confSlotCart            = "Moduliportti";
    ls->confSlot                = "Slotti";
    ls->confSubslot             = "-";

    ls->confMemAdd              = "Lis��...";
    ls->confMemEdit             = "Muuta...";
    ls->confMemRemove           = "Poista";
    ls->confMemSlot             = "Slotti";
    ls->confMemAddresss         = "Muistialue";
    ls->confMemType             = "Tyyppi";
    ls->confMemRomImage         = "ROM tiedosto";

    ls->confChipVideoGB          = "Video ";
    ls->confChipVideoChip        = "Videopiiri:";
    ls->confChipVideoRam         = "Videomuisti:";
    ls->confChipSoundGB          = "��ni ";

    ls->confCmosGB               = "Kellopiiri ";
    ls->confCmosEnable           = " Ota kellopiiri k�ytt��n";
    ls->confCmosBattery          = " K�yt� ladattua paristoa";

    ls->confCpuFreqGB            = "Prosessori kellotaajuudet ";
    ls->confZ80FreqText          = "Z80 Kellotaajuus:";
    ls->confR800FreqText         = "R800 Kellotaajuus:";
    ls->confFdcGB                = "Levyasemaohjain ";
    ls->confCFdcNumDrivesText    = "Levyasemien lukum��r�:";

    ls->confEditMemTitle         = "blueMSX - Muistin hallinta";
    ls->confEditMemGB            = "Muistin tiedot ";
    ls->confEditMemType          = "Tyyppi:";
    ls->confEditMemFile          = "Tiedosto:";
    ls->confEditMemAddress       = "Muistialue";
    ls->confEditMemSize          = "Koko";
    ls->confEditMemSlot          = "Slotti";


    //----------------------
    // Shortcut lines
    //----------------------

    ls->shortcutKey             = "Tapahtuma";
    ls->shortcutDescription     = "Pikan�pp�in";

    ls->shortcutSaveConfig      = "blueMSX - Tallenna Asetukset";
    ls->shortcutOverwriteConfig = "Haluatko korvata pikan�pp�in asetukset:";
    ls->shortcutExitConfig      = "blueMSX - Poistu pikan�pp�in asetuksista";
    ls->shortcutDiscardConfig   = "Haluatko hyl�t� tekem�si muutokset pikan�pp�in asetuksiin?";
    ls->shortcutSaveConfigAs    = "blueMSX - Tallenna pikan�pp�in asetukset";
    ls->shortcutConfigName      = "Asetusten nimi:";
    ls->shortcutNewProfile      = "< Uusi profiili >";
    ls->shortcutConfigTitle     = "blueMSX - Pikan�pp�in asetukset";
    ls->shortcutAssign          = "K�yt�";
    ls->shortcutPressText       = "Pikan�pp�in (paina):";
    ls->shortcutScheme          = "Pikan�pp�in profiili:";
    ls->shortcutCartInsert1     = "Aseta moduli 1";
    ls->shortcutCartRemove1     = "Poista moduli 1";
    ls->shortcutCartInsert2     = "Aseta moduli 2";
    ls->shortcutCartRemove2     = "Poista moduli 2";
    ls->shortcutSpecialMenu1    = "N�yt� erikois moduli valikko moduliportille 1";
    ls->shortcutSpecialMenu2    = "N�yt� erikois moduli valikko moduliportille 2";
    ls->shortcutCartAutoReset   = "K�ynnist� kone uudeleen modulin asettamisen j�lkeen";
    ls->shortcutDiskInsertA     = "Aseta levytiedosto asemaan A";
    ls->shortcutDiskDirInsertA  = "Aseta hakemisto levyasemaksi A";
    ls->shortcutDiskRemoveA     = "Poista levy levyasemasta A";
    ls->shortcutDiskChangeA     = "Pika vaihda levy A";
    ls->shortcutDiskAutoResetA  = "K�ynnist� kone uudelleen levyn lis��misen j�lkeen asemaan A";
    ls->shortcutDiskInsertB     = "Aseta levytiedosto asemaan B";
    ls->shortcutDiskDirInsertB  = "Aseta hakemisto levyasemaksi B";
    ls->shortcutDiskRemoveB     = "Poista levy levyasemasta B";
    ls->shortcutCasInsert       = "Aseta kasetti";
    ls->shortcutCasEject        = "Poista kasetti";
    ls->shortcutCasAutorewind   = "Muuta kasetin automaattista alkuunkelaus toimintoa";
    ls->shortcutCasReadOnly     = "Muuta kasetin kirjoitussuojausta";
    ls->shortcutCasSetPosition  = "Aseta kasetin kohta";
    ls->shortcutCasRewind       = "Kelaa kasetti alkuun";
    ls->shortcutCasSave         = "Tallenna kasetti image";
    ls->shortcutPrnFormFeed     = "Vaihda tulostimessa sivua";
    ls->shortcutCpuStateLoad    = "Lataa tila";
    ls->shortcutCpuStateSave    = "Tallenna tila nimell�";
    ls->shortcutCpuStateQload   = "Tilan pikalataus";
    ls->shortcutCpuStateQsave   = "Tilan pikatallennus";
    ls->shortcutAudioCapture    = "K�ynnist�/Pys�yt� ��nen kaappaus";
    ls->shortcutScreenshotOrig  = "Ota ruudunkaappaus";
    ls->shortcutScreenshotSmall = "Pieni filtter�im�t�n ruudunkaappaus";
    ls->shortcutScreenshotLarge = "Suuri filtter�im�t�n ruudunkaappaus";
    ls->shortcutQuit            = "Poistu blueMSX:st�";
    ls->shortcutRunPause        = "K�ynnist�/Keskeyt� emulaatio";
    ls->shortcutStop            = "Pys�yt� emulatio";
    ls->shortcutResetHard       = "Kylm�k�ynnistys";
    ls->shortcutResetSoft       = "L�mmink�ynnistys";
    ls->shortcutResetClean      = "T�ydellinen uudelleenk�ynnistys";
    ls->shortcutSizeSmall       = "Aseta pieni ikkunan koko";
    ls->shortcutSizeNormal      = "Aseta normaali ikkunan koko";
    ls->shortcutSizeFullscreen  = "Aseta kokoruututila";
    ls->shortcutSizeMinimized   = "Pienenn� ikkuna";
    ls->shortcutToggleFullscren = "Vaihda kokoruututilaa";
    ls->shortcutVolumeIncrease  = "Nosta ��nenvoimakkuutta";
    ls->shortcutVolumeDecrease  = "Laske ��nenvoimakkuutta";
    ls->shortcutVolumeMute      = "Hiljenn� ��net";
    ls->shortcutVolumeStereo    = "Muuta mono/stereo";
    ls->shortcutSwitchMsxAudio  = "Muuta MSX-AUDIO kytkimen tila";
    ls->shortcutSwitchFront     = "Muuta Panasonic aplikaatiokytkimen tila";
    ls->shortcutSwitchPause     = "Muuta Pause-n�pp�imen tilaa";
    ls->shortcutToggleMouseLock = "Muuta hiiren kaappauksen tilaa";
    ls->shortcutEmuSpeedMax     = "Maksimi emulointinopeus";
    ls->shortcutEmuSpeedToggle  = "Vaihda maksimi emulointinopeus";
    ls->shortcutEmuSpeedNormal  = "Normaali emulointinopeus";
    ls->shortcutEmuSpeedInc     = "Nopeuta emulointia";
    ls->shortcutEmuSpeedDec     = "Hidasta emulointia";
    ls->shortcutThemeSwitch     = "Vaihda teemaa";
    ls->shortcutShowEmuProp     = "N�yt� emulaatio asetukset";
    ls->shortcutShowVideoProp   = "N�yt� video asetukset";
    ls->shortcutShowAudioProp   = "N�yt� ��ni asetukset";
    ls->shortcutShowCtrlProp    = "N�yt� kontrolli asetukset";
    ls->shortcutShowPerfProp    = "N�yt� suorituskyky asetukset";
    ls->shortcutShowSettProp    = "N�yt� yleisasetukset";
    ls->shortcutShowPorts       = "N�yt� liit�nt� asetukset";
    ls->shortcutShowLanguage    = "N�yt� kielivalinnat";
    ls->shortcutShowMachines    = "N�yt� tietokone muokkain";
    ls->shortcutShowShortcuts   = "N�yt� pikan�pp�in valinnat";
    ls->shortcutShowKeyboard    = "N�yt� Peliohjain / N�pp�imist� asetukset";
    ls->shortcutShowMixer       = "N�yt� Mixeri";
    ls->shortcutShowDebugger    = "N�yt� Debugger";
    ls->shortcutShowTrainer     = "N�yt� Trainer";
    ls->shortcutShowHelp        = "N�yt� ohjeet";
    ls->shortcutShowAbout       = "N�yt� Tietoja blueMSX:st�";
    ls->shortcutShowFiles       = "N�yt� tiedosto asetukset";
    ls->shortcutToggleSpriteEnable = "N�yt�/Piilota Spritet";
    ls->shortcutToggleFdcTiming = "Ota k�ytt��n/Poista k�yt�st� levyaseman ajoitus";
    ls->shortcutToggleCpuTrace  = "Ota k�ytt��n/Poista k�yt�st� Prosessorin j�ljitystoiminto";


    //----------------------
    // Keyboard config lines
    //----------------------

    ls->keyconfigSelectedKey    = "kohde n�pp�in:";
    ls->keyconfigMappedTo       = "PC n�pp�in:";
    ls->keyconfigMappingScheme  = "N�pp�inkartta profiili:";

    
    //----------------------
    // Rom type lines
    //----------------------

    ls->romTypeStandard         = "Standardi";
    ls->romTypeMsxdos2          = "MSX-DOS 2";
    ls->romTypeKonamiScc        = "Konami SCC";
    ls->romTypeKonami           = "Konami";
    ls->romTypeAscii8           = "ASCII 8";
    ls->romTypeAscii16          = "ASCII 16";
    ls->romTypeGameMaster2      = "Game Master 2 (SRAM)";
    ls->romTypeAscii8Sram       = "ASCII 8 (SRAM)";
    ls->romTypeAscii16Sram      = "ASCII 16 (SRAM)";
    ls->romTypeRtype            = "R-Type";
    ls->romTypeCrossblaim       = "Cross Blaim";
    ls->romTypeHarryFox         = "Harry Fox";
    ls->romTypeMajutsushi       = "Konami Majutsushi";
    ls->romTypeZenima80         = "Zemina 80 in 1";
    ls->romTypeZenima90         = "Zemina 90 in 1";
    ls->romTypeZenima126        = "Zemina 126 in 1";
    ls->romTypeScc              = "SCC";
    ls->romTypeSccPlus          = "SCC+";
    ls->romTypeSnatcher         = "The Snatcher";
    ls->romTypeSdSnatcher       = "SD Snatcher";
    ls->romTypeSccMirrored      = "SCC peilattu";
    ls->romTypeSccExtended      = "SCC laajennettu";
    ls->romTypeFmpac            = "FM-PAC (SRAM)";
    ls->romTypeFmpak            = "FM-PAK";
    ls->romTypeKonamiGeneric    = "Konami Yleinen";
    ls->romTypeSuperPierrot     = "Super Pierrot";
    ls->romTypeMirrored         = "Peilattu ROM";
    ls->romTypeNormal           = "Tavallinen ROM";
    ls->romTypeDiskPatch        = "Tavallinen + korjaus levylt�";
    ls->romTypeCasPatch         = "Tavallinen + korjaus kasetilta";
    ls->romTypeTc8566afFdc      = "TC8566AF Diskettiasemaohjain";
    ls->romTypeMicrosolFdc      = "Microsol Diskettiasemaohjain";
    ls->romTypeNationalFdc      = "National Diskettiasemaohjain";
    ls->romTypePhilipsFdc       = "Philips Diskettiasemaohjain";
    ls->romTypeSvi738Fdc        = "SVI-738 Diskettiasemaohjain";
    ls->romTypeMappedRam        = "Mapper RAM";
    ls->romTypeMirroredRam1k    = "1kB peilattu RAM";
    ls->romTypeNormalRam        = "Tavallinen RAM";
    ls->romTypeKanji            = "Kanji";
    ls->romTypeHolyQuran        = "Holy Quran";
    ls->romTypeMatsushitaSram   = "Matsushita SRAM";
    ls->romTypePanasonic16      = "Panasonic 16kB SRAM";
    ls->romTypePanasonic32      = "Panasonic 32kB SRAM";
    ls->romTypeBunsetsu         = "Bunsetsu";
    ls->romTypeJisyo            = "Jisyo";
    ls->romTypeKanji12          = "Kanji12";
    ls->romTypeNationalSram     = "National (SRAM)";
    ls->romTypeS1985            = "S1985";
    ls->romTypeS1990            = "S1990";
    ls->romTypeTurborPause      = "Turbo-R Pause";
    ls->romTypeF4deviceNormal   = "Tavallinen F4 portti";
    ls->romTypeF4deviceInvert   = "K��nnetty F4 portti";
    ls->romTypeMsxMidi          = "MSX-MIDI";
    ls->romTypeTurborTimer      = "Turbo-R Ajastin";
    ls->romTypeKoei             = "Koei (SRAM)";
    ls->romTypeBasic            = "Basic ROM";
    ls->romTypeHalnote          = "Halnote";
    ls->romTypeLodeRunner       = "Lode Runner";
    ls->romTypeNormal4000       = "Tavallinen #4000";
    ls->romTypeNormalC000       = "Tavallinen #C000";
    ls->romTypeKonamiSynth      = "Konami Synthesizer";
    ls->romTypeKonamiKbdMast    = "Konami Keyboard Master";
    ls->romTypeKonamiWordPro    = "Konami Word Pro";
    ls->romTypePac              = "PAC (SRAM)";
    ls->romTypeMegaRam          = "MegaRAM";
    ls->romTypeMegaRam128       = "128kB MegaRAM";
    ls->romTypeMegaRam256       = "256kB MegaRAM";
    ls->romTypeMegaRam512       = "512kB MegaRAM";
    ls->romTypeMegaRam768       = "768kB MegaRAM";
    ls->romTypeMegaRam2mb       = "2MB MegaRAM";
    ls->romTypeExtRam           = "Ulkoinen RAM";
    ls->romTypeExtRam512        = "512kB Ulkoinen RAM";
    ls->romTypeExtRam1mb        = "1MB Ulkoinen RAM";
    ls->romTypeExtRam2mb        = "2MB Ulkoinen RAM";
    ls->romTypeExtRam4mb        = "4MB Ulkoinen RAM";
    ls->romTypeMsxMusic         = "MSX-Music";
    ls->romTypeMsxAudio         = "MSX-Audio";
    ls->romTypeY8950            = "Y8950";
    ls->romTypeMoonsound        = "Moonsound";
    ls->romTypeSvi328Cart       = "SVI-328 Moduli";
    ls->romTypeSvi328Fdc        = "SVI-328 Levyasemaohjain";
    ls->romTypeSvi328Prn        = "SVI-328 Tulostin";
    ls->romTypeSvi328Uart       = "SVI-328 Sarjaportti";
    ls->romTypeSvi328col80      = "SVI-328 80-merkin kortti";
    ls->romTypeSvi727col80      = "SVI-727 80-merkin kortti";
    ls->romTypeColecoCart       = "Coleco Moduli";
    ls->romTypeSg1000Cart       = "SG-1000 Moduli";
    ls->romTypeTheCastle        = "The Castle";
    ls->romTypeSonyHbi55        = "Sony HBI-55";
    ls->romTypeMsxPrinter       = "MSX Tulostin";
    ls->romTypeTurborPcm        = "Turbo-R PCM piiri";
    ls->romTypeGameReader       = "Sunrise GameReader";
    ls->romTypeSunriseIde       = "Sunrise IDE";
    ls->romTypeBeerIde          = "Beer IDE";
    ls->romTypeGide             = "GIDE";
    ls->romTypeVmx80            = "Microsol VMX-80";
    ls->romTypeNms8280Digitiz   = "Philips NMS-8280 Digitoija";
    ls->romTypeHbiV1Digitiz     = "Sony HBI-V1 Digitoija";
    ls->romTypeFmdas            = "F&M Direct Assembler System";
    ls->romTypeSfg05            = "Yamaha SFG-05";
    
    
    //----------------------
    // Debug type lines
    // Note: Only needs translation if debugger is translated
    //----------------------

    ls->dbgMemVisible           = "N�kyv� muisti";
    ls->dbgMemRamNormal         = "Normaali";
    ls->dbgMemRamMapped         = "Sivutettu";
    ls->dbgMemVram              = "VRAM";
    ls->dbgMemYmf278            = "YMF278 Sample RAM";
    ls->dbgMemAy8950            = "AY8950 Sample RAM";
    ls->dbgMemScc               = "Muisti";

    ls->dbgCallstack            = "Kutsupino";

    ls->dbgRegs                 = "Rekisterit";
    ls->dbgRegsCpu              = "CPU Rekisterit";
    ls->dbgRegsYmf262           = "YMF262 Rekisterit";
    ls->dbgRegsYmf278           = "YMF278 Rekisterit";
    ls->dbgRegsAy8950           = "AY8950 Rekisterit";
    ls->dbgRegsYm2413           = "YM2413 Rekisterit";

    ls->dbgDevRamMapper         = "RAM Mapper";
    ls->dbgDevRam               = "RAM";
    ls->dbgDevIdeBeer           = "Beer IDE";
    ls->dbgDevIdeGide           = "GIDE";
    ls->dbgDevF4Device          = "F4 Portti";
    ls->dbgDevFmpac             = "FM-PAC";
    ls->dbgDevFmpak             = "FM-PAK";
    ls->dbgDevKanji             = "Kanji";
    ls->dbgDevKanji12           = "Kanji 12";
    ls->dbgDevKonamiKbd         = "Konami Keyboard Master";
    ls->dbgDevKorean80          = "Korea 80";
    ls->dbgDevKorean90          = "Korea 90";
    ls->dbgDevKorean128         = "Korea 128";
    ls->dbgDevMegaRam           = "MegaRAM";
    ls->dbgDevFdcMicrosol       = "Microsol levyohjain";
    ls->dbgDevMoonsound         = "Moonsound";
    ls->dbgDevMsxAudio          = "MSX-Audio";
    ls->dbgDevMsxAudioMidi      = "MSX-Audio MIDI";
    ls->dbgDevMsxMusic          = "MSX-Music";
    ls->dbgDevPrinter           = "Tulostin";
    ls->dbgDevRs232             = "RS-232";
    ls->dbgDevS1990             = "S1990";
    ls->dbgDevSfg05             = "Yamaha SFG-05";
    ls->dbgDevHbi55             = "Sony HBI-55";
    ls->dbgDevSviFdc            = "SVI levyohjain";
    ls->dbgDevSviPrn            = "SVI Tulostin";
    ls->dbgDevSvi80Col          = "SVI 80-merkki�";
    ls->dbgDevPcm               = "PCM";
    ls->dbgDevMatsushita        = "Matsushita";
    ls->dbgDevS1985             = "S1985";
    ls->dbgDevCrtc6845          = "CRTC6845";
    ls->dbgDevTms9929A          = "TMS9929A";
    ls->dbgDevTms99x8A          = "TMS99x8A";
    ls->dbgDevV9938             = "V9938";
    ls->dbgDevV9958             = "V9958";
    ls->dbgDevZ80               = "Z80";
    ls->dbgDevMsxMidi           = "MSX MIDI";
    ls->dbgDevPpi               = "PPI";
    ls->dbgDevRtc               = "Kellopiiri";
    ls->dbgDevTrPause           = "tR Pause";
    ls->dbgDevAy8910            = "AY8910 PSG";
    ls->dbgDevScc               = "SCC";


    //----------------------
    // Debug type lines
    // Note: Can only be translated to european languages
    //----------------------
   ls->aboutScrollThanksTo      = "Kiitoksen ansaitsevat : ";
   ls->aboutScrollAndYou        = "sek� SIN� !!!!";
};

#endif


