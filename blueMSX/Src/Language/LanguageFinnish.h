/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageFinnish.h,v $
**
** $Revision: 1.19 $
**
** $Date: 2006-06-09 20:30:02 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vik
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
    ls->textNone                = "Ei käytössä";
    ls->textUnknown             = "Tuntematon";


    //----------------------
    // Warning and Error lines
    //----------------------

    ls->warningTitle            = "blueMSX - Varoitus";
    ls->warningDiscardChanges   = "Haluatko perua tekemäsi muutokset?";
    ls->warningOverwriteFile    = "Haluatko ylikirjoittaa tiedoston:";
    ls->errorTitle              = "blueMSX - Virhe";
    ls->errorEnterFullscreen    = "Siirtyminen kokoruututilaan epäonnistui.  \n";
    ls->errorDirectXFailed      = "DirectX objektien luonti epäonnistui.       \nDirectX on korvattu GDI:llä.\nTarkista video asetukset.";
    ls->errorNoRomInZip         = "Zip paketista ei löytynyt .ROM tiedostoa.";
    ls->errorNoDskInZip         = "Zip paketista ei löytynyt .DSK tiedostoa.";
    ls->errorNoCasInZip         = "Zip paketista ei löytynyt .CAS tiedostoa.";
    ls->errorNoHelp             = "blueMSX:n ohje tiedostoa ei löytynyt.";
    ls->errorStartEmu           = "MSX emulaattorin käynnistys epäonnistui.";
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
    ls->menuDiskAutoStart       = "Käynnistä uudelleen asettamisen jälkeen";
    ls->menuCartAutoReset       = "Käynnistä uudelleen muutettaessa";

    ls->menuCasRewindAfterInsert = "Kelaa alkuun asetettaessa";
    ls->menuCasUseReadOnly       = "Kirjoitussuojaa kasetti";
    ls->lmenuCasSaveAs           = "Tallenna kasetti nimellä";
    ls->menuCasSetPosition      = "Valitse kohta";
    ls->menuCasRewind           = "Kelaa alkuun";

    ls->menuPrnFormfeed         = "Paperin vaihto";

    ls->menuZoomNormal          = "Pieni koko";
    ls->menuZoomDouble          = "Normaali koko";
    ls->menuZoomFullscreen      = "Kokoruututila";

    ls->menuPropsEmulation      = "Emulaatio";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Ääni";
    ls->menuPropsControls       = "Kontrollit";
    ls->menuPropsPerformance    = "Suorituskyky";
    ls->menuPropsSettings       = "Asetukset";
    ls->menuPropsFile           = "Tiedostot";
    ls->menuPropsLanguage       = "Kieli";
    ls->menuPropsPorts          = "Liitännät";
    
    ls->menuVideoSource         = "Video Ulostulo";
    ls->menuVideoSourceDefault  = "Video Ulostuloa ei ole kytketty.";
    ls->menuVideoChipAutodetect = "Tunnista videopiiri automaattisesti";
    ls->menuVideoInSource       = "Video Sisääntulo";
    ls->menuVideoInBitmap       = "Bittikartta tiedosto";

    ls->menuHelpHelp            = "Ohjeen aiheet";
    ls->menuHelpAbout           = "Tietoja blueMSX:stä";

    ls->menuFileCart            = "Moduliportti";
    ls->menuFileDisk            = "Levyasema";
    ls->menuFileCas             = "Kasetti";
    ls->menuFilePrn             = "Tulostin";
    ls->menuFileLoadState       = "Lataa tila...";
    ls->menuFileSaveState       = "Tallenna tila nimellä";
    ls->menuFileQLoadState      = "Tilan pikalataus";
    ls->menuFileQSaveState      = "Tilan pikatallennus";
    ls->menuFileCaptureAudio    = "Tallenna äänet";
    ls->menuFileScreenShot      = "Tallenna kuvaruutukaappaus";
    ls->menuFileExit            = "Poistu";
    ls->menuFileHarddisk        = "Kovalevy";
    ls->menuFileHarddiskNoPesent= "Ohjaimia ei ole kytketty";

    ls->menuRunRun              = "Käynnistä";
    ls->menuRunPause            = "Keskeytä";
    ls->menuRunStop             = "Pysäytä";
    ls->menuRunSoftReset        = "Lämminkäynnistys";
    ls->menuRunHardReset        = "Kylmäkäynnistys";
    ls->menuRunCleanReset       = "Täydellinen uudelleenkäynnistys";

    ls->menuToolsMachine        = "Tietokone muokkain";
    ls->menuToolsShortcuts      = "Pikanäppäin valinnat";
    ls->menuToolsKeyboard       = "Peliohjaimet / Näppäimistökartta";
    ls->menuToolsMixer          = "Mikseri";

    ls->menuFile                = "Tiedosto";
    ls->menuRun                 = "Emulaatio";
    ls->menuWindow              = "Ikkuna";
    ls->menuOptions             = "Asetukset";
    ls->menuTools                = "Työkalut";
    ls->menuHelp                = "Ohjeet";


    //----------------------
    // Dialog related lines
    //----------------------

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Avaa";
    ls->dlgCancel               = "Peruuta";
    ls->dlgSave                 = "Tallenna";
    ls->dlgSaveAs               = "Tallenna nimellä";
    ls->dlgRun                  = "Käynnistä";
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
    ls->dlgSaveState            = "Tallenna tila nimellä";
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
    ls->dlgTapeCurrentPos       = "Tämänhetkinen kohta";
    ls->dlgTapeTotalTime        = "Kokonaispituus";
    ls->dlgTapeSetPosText       = "Kasetin kohta:";
    ls->dlgTapeCustom           = "Näytä erilliset tiedostojen osat";
    ls->dlgTabPosition          = "Kohta";
    ls->dlgTabType              = "Tyyppi";
    ls->dlgTabFilename          = "Tiedostonimi";
    ls->dlgZipReset             = "Uudelleenkäynnistys asettamisen jälkeen";

    ls->dlgAboutTitle           = "Tietoja blueMSX:stä";

    ls->dlgLangLangText         = "Valitse käytettävä kieli";
    ls->dlgLangLangTitle        = "blueMSX - Kielivalinta";

    ls->dlgAboutAbout           = "TIEDOT\r\n====";
    ls->dlgAboutVersion         = "Versio:";
    ls->dlgAboutBuildNumber     = "Kooste:";
    ls->dlgAboutBuildDate       = "Päiväys:";
    ls->dlgAboutCreat           = "Tekijä: Daniel Vik";
    ls->dlgAboutDevel           = "KEHITTÄJÄT\r\n=======";
    ls->dlgAboutThanks          = "ERITYIS KIITOKSET\r\n===========";
    ls->dlgAboutLisence         = "LISENSSI\r\n"
                                  "=====\r\n\r\n"
                                  "Tämä ohjelmisto toimitetaan sellaisenaan ilman minkäänlaista takuuta. "
                                  "Kehittäjät eivät ota mitään vastuuta ohjelman kaytössä tai käytöstä "
		          "aiheutuneista mahdollisista ongelmista tai vahingoista.\r\n\r\n"
		          "Lisätietoja löydät osoitteesta www.bluemsx.com.";

    ls->dlgSavePreview          = "Näytä Esikatselu";
    ls->dlgSaveDate             = "Tallennettu:";


    //----------------------
    // Properties related lines
    //----------------------

    ls->propTitle               = "blueMSX - Ominaisuudet";
    ls->propEmulation           = "Emulaatio";
    ls->propVideo               = "Video";
    ls->propSound               = "Ääni";
    ls->propControls            = "Kontrollit";
    ls->propPerformance         = "Suorituskyky";
    ls->propSettings            = "Asetukset";
    ls->propFile                = "Tiedostot";
    ls->propPorts               = "Liitännät";

    ls->propEmuGeneralGB        = "Yleistä ";
    ls->propEmuFamilyText       = "MSX malli:";
    ls->propEmuMemoryGB         = "Muisti ";
    ls->propEmuRamSizeText      = "RAM koko:";
    ls->propEmuVramSizeText     = "VRAM koko:";
    ls->propEmuSpeedGB          = "Emulaatio Nopeus ";
    ls->propEmuSpeedText        = "Emulaatio Nopeus:";
    ls->propEmuFrontSwitchGB     = "Panasonicin Kytkimet ";
    ls->propEmuFrontSwitch       = " Aplikaatio kytkin";
    ls->propEmuFdcTiming        = " Poista käytöstä levyaseman ajoitus";
    ls->propEmuPauseSwitch      = " PAUSE-näppäin";
    ls->propEmuAudioSwitch       = " MSX-AUDIO modulin kytkin";
    ls->propVideoFreqText       = "Video Taajuus:";
    ls->propVideoFreqAuto       = "Automaattinen";
    ls->propSndOversampleText   = "Ylinäytteistys:";
    ls->propSndYkInGB           = "YK-01/YK-10/YK-20 Sisään ";                // New in 2.5
    ls->propSndMidiInGB         = "MIDI Sisään ";
    ls->propSndMidiOutGB        = "MIDI Ulos ";
    ls->propSndMidiChannel      = "MIDI Channel:";                      // New in 2.5
    ls->propSndMidiAll          = "All";                                // New in 2.5

    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Monitorin tyyppi:";
    ls->propMonEmuText          = "Monitorin emulointi:";
    ls->propVideoTypeText       = "Video tyyppi:";
    ls->propWindowSizeText      = "Ikkunan koko:";
    ls->propMonHorizStretch     = " Vaaka Venytys";
    ls->propMonVertStretch      = " Pysty Venytys";
    ls->propMonDeInterlace      = " Lomituksen purku";
    ls->propMonBrightness       = "Kirkkaus:";
    ls->propMonContrast         = "Kontrasti:";
    ls->propMonSaturation       = "Saturaatio:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = " Juovat:";
    ls->propMonColorGhosting    = " Antenni muunnos:";
    ls->propMonEffectsGB        = "Tehosteet ";

    ls->propPerfVideoDrvGB      = "Video Ajuri ";
    ls->propPerfVideoDispDrvText= "Näyttö ajuri:";
    ls->propPerfFrameSkipText   = "Ruudunpäivitysten ohitus:";
    ls->propPerfAudioDrvGB      = "Ääni ajuri ";
    ls->propPerfAudioDrvText    = "Ääni ajuri:";
    ls->propPerfAudioBufSzText  = "Ääni puskurin koko:";
    ls->propPerfEmuGB           = "Emulaatio ";
    ls->propPerfSyncModeText    = "Tahdistus tapa:";
    ls->propFullscreenResText   = "Resoluutio kokoruututilassa:";

    ls->propSndChipEmuGB        = "Äänipiirien emulointi ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";
    ls->propSndMoonsound        = " Moonsound";
    ls->propSndMt32ToGm         = " Muunna MT-32 soittimet General MIDI soittimiksi";

    ls->propPortsLptGB          = "Rinnakkaisportti ";
    ls->propPortsComGB          = "Sarjaportit ";
    ls->propPortsLptText        = "Portti:";
    ls->propPortsCom1Text       = "Portti 1:";
    ls->propPortsNone           = "Ei mitään";
    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "Tulosta tiedostoon";
    ls->propPortsComFile        = "Lähetys tiedostoon";
    ls->propPortsOpenLogFile    = "Avaa lokitiedosto";
    ls->propPortsEmulateMsxPrn  = "Emulaatio:";

    ls->propSetFileHistoryGB    = "Tiedostohistoria ";
    ls->propSetFileHistorySize  = "Tiedostojen lukumäärä Tiedostohistoriassa:";
    ls->propSetFileHistoryClear = "Tyhjennä historia";
    ls->propFileTypes           = " Rekisteröi tiedostotyypit blueMSX:ään (.rom, .dsk, .cas, .sta)";
    ls->propWindowsEnvGB        = "Windows Ympäristö ";
    ls->propSetScreenSaver      = " Poista ruudunsäästäjä käytöstä, kun blueMSX on käynnissä";
    ls->propDisableWinKeys      = " Ota Windows-näppäimet MSX käyttöön";
    ls->propPriorityBoost       = " Nosta blueMSX:n prioriteettia";
    ls->propScreenshotPng       = " Tallenna kuvaruutukaappaukset PNG-muodossa";
    ls->propClearHistory        = "Oletko varma, että haluat poistaa kaikki tiedostohistorian tiedot ?";
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

    ls->enumVideoMonColor       = "Värillinen";
    ls->enumVideoMonGrey        = "Mustavalko";
    ls->enumVideoMonGreen       = "Vihermusta";
    ls->enumVideoMonAmber       = "Amber";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Ei käytössä";
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

    ls->enumVideoFrameskip0     = "Ei käytössä";
    ls->enumVideoFrameskip1     = "1 päivitys";
    ls->enumVideoFrameskip2     = "2 päivitystä";
    ls->enumVideoFrameskip3     = "3 päivitystä";
    ls->enumVideoFrameskip4     = "4 päivitystä";
    ls->enumVideoFrameskip5     = "5 päivitystä";

    ls->enumSoundDrvNone        = "Ei ääntä";
    ls->enumSoundDrvWMM         = "WMM ajuri";
    ls->enumSoundDrvDirectX     = "DirectX ajuri";

    ls->enumEmuSync1ms          = "Tahdistus MSX:n ruudunpäivitykseen";
    ls->enumEmuSyncAuto         = "Automaattinen (nopea)";
    ls->enumEmuSyncNone         = "Ei käytössä";
    ls->enumEmuSyncVblank       = "Tahdistus PC:n ruudunpäivitykseen";
    ls->enumEmuAsyncVblank      = "Asynchronous PC Vblank";             // New in 2.5

    ls->enumControlsJoyNone     = "Tyhjä";
    ls->enumControlsJoyMouse    = "Hiiri";
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle";
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey Dongle";
    ls->enumControlsJoy2Button = "2-button Joystick";                   // New in 2.5
    ls->enumControlsJoyLightGun = "Light Gun";                          // New in 2.5
    ls->enumControlsJoyColeco = "ColecoVision Joystick";                // New in 2.5


    //----------------------
    // Configuration related lines
    //----------------------

    ls->confTitle               = "blueMSX - Tietokone muokkain";
    ls->confConfigText          = "Tietokone profiili:";
    ls->confSlotLayout          = "Slotti järjestys";
    ls->confMemory              = "Muisti";
    ls->confChipEmulation       = "Piirien Emulointi";
    ls->confChipExtras          = "Muuta";

    ls->confOpenRom             = "Valitse ROM tiedosto";
    ls->confSaveTitle           = "blueMSX - Tallenna Tietokone profiili";
    ls->confSaveText            = "Haluatko ylikirjoittaa Tietokone profiilin:";
    ls->confSaveAsTitle         = "Tallenna tietokone profiili nimellä...";
    ls->confSaveAsMachineName   = "Tietokone profiili:";
    ls->confDiscardTitle        = "blueMSX - Tietokone muokkain";
    ls->confExitSaveTitle       = "blueMSX - Poistu tietokone muokkaimesta";
    ls->confExitSaveText        = "Haluatko hylätä tekemäsi muutokset nykyiseen tietokone profiiliin?";

    ls->confSlotLayoutGB        = "Slotti jako ";
    ls->confSlotExtSlotGB       = "Ulkoiset Slotit ";
    ls->confBoardGB             = "Emolevy ";
    ls->confBoardText           = "Emolevy tyyppi:";
    ls->confSlotPrimary         = "Jakamaton";
    ls->confSlotExpanded        = "Jaettu (4 alislottia)";

    ls->confSlotCart            = "Moduliportti";
    ls->confSlot                = "Slotti";
    ls->confSubslot             = "-";

    ls->confMemAdd              = "Lisää...";
    ls->confMemEdit             = "Muuta...";
    ls->confMemRemove           = "Poista";
    ls->confMemSlot             = "Slotti";
    ls->confMemAddresss         = "Muistialue";
    ls->confMemType             = "Tyyppi";
    ls->confMemRomImage         = "ROM tiedosto";

    ls->confChipVideoGB          = "Video ";
    ls->confChipVideoChip        = "Videopiiri:";
    ls->confChipVideoRam         = "Videomuisti:";
    ls->confChipSoundGB          = "Ääni ";

    ls->confCmosGB               = "Kellopiiri ";
    ls->confCmosEnable           = " Ota kellopiiri käyttöön";
    ls->confCmosBattery          = " Käytä ladattua paristoa";

    ls->confCpuFreqGB            = "Prosessori kellotaajuudet ";
    ls->confZ80FreqText          = "Z80 Kellotaajuus:";
    ls->confR800FreqText         = "R800 Kellotaajuus:";
    ls->confFdcGB                = "Levyasemaohjain ";
    ls->confCFdcNumDrivesText    = "Levyasemien lukumäärä:";

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
    ls->shortcutDescription     = "Pikanäppäin";

    ls->shortcutSaveConfig      = "blueMSX - Tallenna Asetukset";
    ls->shortcutOverwriteConfig = "Haluatko ylikirjoittaa pikanäppäin asetukset:";
    ls->shortcutExitConfig      = "blueMSX - Poistu pikanäppäin valinnoista";
    ls->shortcutDiscardConfig   = "Haluatko hylätä tekemäsi muutokset pikanäppäin asetuksiin?";
    ls->shortcutSaveConfigAs    = "blueMSX - Tallenna pikanäppäin asetukset";
    ls->shortcutConfigName      = "Asetusten nimi:";
    ls->shortcutNewProfile      = "< Uusi profiili >";
    ls->shortcutConfigTitle     = "blueMSX - Pikanäppäinten muokkaus";
    ls->shortcutAssign          = "Käytä";
    ls->shortcutPressText       = "Pikanäppäin (paina):";
    ls->shortcutScheme          = "Pikanäppäin profiili:";
    ls->shortcutCartInsert1     = "Aseta moduli 1";
    ls->shortcutCartRemove1     = "Poista moduli 1";
    ls->shortcutCartInsert2     = "Aseta moduli 2";
    ls->shortcutCartRemove2     = "Poista moduli 2";
    ls->shortcutSpecialMenu1    = "Näytä erikois moduli valikko moduliportille 1";
    ls->shortcutSpecialMenu2    = "Näytä erikois moduli valikko moduliportille 2";
    ls->shortcutCartAutoReset   = "Käynnistä kone uudeleen modulin asettamisen jälkeen";
    ls->shortcutDiskInsertA     = "Aseta levytiedosto asemaan A";
    ls->shortcutDiskDirInsertA  = "Aseta hakemisto levyasemaksi A";
    ls->shortcutDiskRemoveA     = "Poista levy levyasemasta A";
    ls->shortcutDiskChangeA     = "Pika vaihda levy A";
    ls->shortcutDiskAutoResetA  = "Käynnistä kone uudelleen levyn lisäämisen jälkeen asemaan A";
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
    ls->shortcutCpuStateSave    = "Tallenna tila nimellä";
    ls->shortcutCpuStateQload   = "Tilan pikalataus";
    ls->shortcutCpuStateQsave   = "Tilan pikatallennus";
    ls->shortcutAudioCapture    = "Käynnistä/Pysäytä äänen kaappaus";
    ls->shortcutScreenshotOrig  = "Ota ruudunkaappaus";
    ls->shortcutScreenshotSmall = "Pieni filtteröimätön ruudunkaappaus";
    ls->shortcutScreenshotLarge = "Suuri filtteröimätön ruudunkaappaus";
    ls->shortcutQuit            = "Poistu blueMSX:stä";
    ls->shortcutRunPause        = "Käynnistä/Keskeytä emulaatio";
    ls->shortcutStop            = "Pysäytä emulatio";
    ls->shortcutResetHard       = "Kylmäkäynnistys";
    ls->shortcutResetSoft       = "Lämminkäynnistys";
    ls->shortcutResetClean      = "Uudelleenkäynnistys virtanapista";
    ls->shortcutSizeSmall       = "Aseta pieni ikkunan koko";
    ls->shortcutSizeNormal      = "Aseta normaali ikkunan koko";
    ls->shortcutSizeFullscreen  = "Aseta kokoruututila";
    ls->shortcutSizeMinimized   = "Pienennä ikkuna";
    ls->shortcutToggleFullscren = "Vaihda kokoruututilaa";
    ls->shortcutVolumeIncrease  = "Nosta äänenvoimakkuutta";
    ls->shortcutVolumeDecrease  = "Laske äänenvoimakkuutta";
    ls->shortcutVolumeMute      = "Hiljennä äänet";
    ls->shortcutVolumeStereo    = "Muuta mono/stereo";
    ls->shortcutSwitchMsxAudio  = "Muuta MSX-AUDIO kytkimen tila";
    ls->shortcutSwitchFront     = "Muuta Panasonic aplikaatiokytkimen tila";
    ls->shortcutSwitchPause     = "Muuta Pause-näppäimen tilaa";
    ls->shortcutToggleMouseLock = "Muuta hiiren kaappauksen tilaa";
    ls->shortcutEmuSpeedMax     = "Maksimi emulointinopeus";
    ls->shortcutEmuSpeedToggle  = "Vaihda maksimi emulointinopeus";
    ls->shortcutEmuSpeedNormal  = "Normaali emulointinopeus";
    ls->shortcutEmuSpeedInc     = "Nopeuta emulointia";
    ls->shortcutEmuSpeedDec     = "Hidasta emulointia";
    ls->shortcutThemeSwitch     = "Vaihda teemaa";
    ls->shortcutShowEmuProp     = "Näytä emulaatio asetukset";
    ls->shortcutShowVideoProp   = "Näytä video asetukset";
    ls->shortcutShowAudioProp   = "Näytä ääni asetukset";
    ls->shortcutShowCtrlProp    = "Näytä kontrolli asetukset";
    ls->shortcutShowPerfProp    = "Näytä suorituskyky asetukset";
    ls->shortcutShowSettProp    = "Näytä yleisasetukset";
    ls->shortcutShowPorts       = "Näytä liitäntä asetukset";
    ls->shortcutShowLanguage    = "Näytä kielivalinnat";
    ls->shortcutShowMachines    = "Näytä tietokone muokkain";
    ls->shortcutShowShortcuts   = "Näytä pikanäppäin valinnat";
    ls->shortcutShowKeyboard    = "Näytä Peliohjain / Näppäimistö asetukset";
    ls->shortcutShowMixer       = "Näytä Mixeri";
    ls->shortcutShowDebugger    = "Näytä Debuggeri";
    ls->shortcutShowTrainer     = "Näytä Traineri";
    ls->shortcutShowHelp        = "Näytä ohjeet";
    ls->shortcutShowAbout       = "Näytä Tietoja blueMSX:stä";
    ls->shortcutShowFiles       = "Näytä tiedosto asetukset";
    ls->shortcutToggleSpriteEnable = "Näytä/Piilota Spritet";
    ls->shortcutToggleFdcTiming = "Ota käyttöön/Poista käytöstä levyaseman ajoitus";
    ls->shortcutToggleCpuTrace  = "Ota käyttöön/Poista käytöstä Prosessorin jäljitystoiminto";


    //----------------------
    // Keyboard config lines
    //----------------------

    ls->keyconfigSelectedKey    = "kohde näppäin:";
    ls->keyconfigMappedTo       = "PC näppäin:";
    ls->keyconfigMappingScheme  = "Näppäinkartta profiili:";
};

#endif

