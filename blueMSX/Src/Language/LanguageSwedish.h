/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageSwedish.h,v $
**
** $Revision: 1.19 $
**
** $Date: 2006-06-04 00:43:35 $
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
#ifndef LANGUAGE_SWEDISH_H
#define LANGUAGE_SWEDISH_H

#include "LanguageStrings.h"

void langInitSwedish(LanguageStrings* ls) 
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

    ls->menuNoRecentFiles       = "- ingen filhistoria -";
    ls->menuInsert              = "S�tt in";
    ls->menuEject               = "Ta ur";

    ls->menuCartAutoReset       = "Starta om efter ins�ttning/urdagning";
    ls->menuCartFMPac           = "FM-PAC Cartridge";
    ls->menuCartPac             = "PAC Cartridge";

    ls->menuDiskAutoStart       = "Starta om efter ins�ttning/urdagning";
    
    ls->menuCasSetPosition      = "S�tt position";
    ls->menuCasRewind           = "Spola tillbaka";

    ls->menuZoomNormal          = "Normal storlek";
    ls->menuZoomDouble          = "Dubbel storlek";
    ls->menuZoomFullscreen      = "Helsk�rm";
    
    ls->menuPropsEmulation      = "Emulering";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Ljud";
    ls->menuPropsControls       = "Kontroller";
    ls->menuPropsPerformance    = "Prestanda";
    ls->menuPropsLanguage       = "Spr�k";
    
    ls->menuHelpHelp            = "Hj�lp";
    ls->menuHelpAbout           = "Om blueMSX";

    ls->menuFileCart            = "Cartridge slot";
    ls->menuFileDisk            = "Diskettstaion";
    ls->menuFileCas             = "Kasett";
    ls->menuFileLoadState       = "L�s in CPU-tillstand";
    ls->menuFileSaveState       = "Spara CPU-tillstand";
    ls->menuFileQLoadState      = "Snabbladda CPU-tillstand";
    ls->menuFileQSaveState      = "Snabbspara CPU-tillstand";
    ls->menuFileCaptureAudio    = "Spara ljud";
    ls->menuFileScreenShot      = "Spara sk�rmdump";
    ls->menuFileExit            = "Avsluta";

    ls->menuRunRun              = "K�r";
    ls->menuRunPause            = "Paus";
    ls->menuRunStop             = "Stanna";
    ls->menuRunSoftReset        = "Mjuk Omstart";
    ls->menuRunHardReset        = "H�rd Omstart";
    ls->menuRunCleanReset       = "Full Omstart";

    ls->menuFile                = "Arkiv";
    ls->menuRun                 = "K�r";
    ls->menuWindow              = "F�nster";
    ls->menuOptions             = "Egenskaper";
    ls->menuHelp                = "Hj�lp";
    
    ls->errorTitle              = "blueMSX - Fel";
    ls->errorEnterFullscreen    = "Misslyckades att byta till fullsk�rm.           \n";
    ls->errorDirectXFailed      = "Misslyckades att skapa DirectX objekt.          \nAnv�nder GDI ist�llet.\nKontrollera video inst�llningarna.";
    ls->errorNoRomInZip         = "Kunde inte hitta en .rom fil i zip arkivet.";
    ls->errorNoDskInZip         = "Kunde inte hitta en .dsk fil i zip arkivet.";
    ls->errorNoCasInZip         = "Kunde inte hitta en .cas fil i zip arkivet.";
    ls->errorNoHelp             = "Kunde inte hitta hj�lpfilen.";
    ls->errorStartEmu           = "Misslyckades att starta emulatorn.";


    ls->dlgLoadRom              = "blueMSX - Ladda en rom fil";
    ls->dlgLoadDsk              = "blueMSX - Ladda en dsk fil";
    ls->dlgLoadCas              = "blueMSX - Ladda en cas fil";
    ls->dlgLoadRomDskCas        = "blueMSX - Ladda en rom, dsk eller cas fil";
    ls->dlgLoadRomDesc          = "V�lj en cartridge fil:";
    ls->dlgLoadDskDesc          = "V�lj en diskett fil:";
    ls->dlgLoadCasDesc          = "V�lj en kassett fil:";
    ls->dlgLoadRomDskCasDesc    = "V�lj en fil:";
    ls->dlgLoadState            = "Ladda CPU-tillstand";
    ls->dlgSaveState            = "Spara CPU-tillstand";
    ls->dlgInsertRom1           = "S�tt in ROM cartridge i slot 1";
    ls->dlgInsertRom2           = "S�tt in ROM cartridge i slot 2";
    ls->dlgInsertDiskA          = "S�tt in diskett i diskettstation A";
    ls->dlgInsertDiskB          = "S�tt in diskett i diskettstation B";
    ls->dlgInsertCas            = "S�tt in kassettband";

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "�ppna";
    ls->dlgCancel               = "Avbryt";

    ls->dlgTapeTitle            = "blueMSX - Kassettposition";
    ls->dlgTapeFrameText        = "Kassettposition";
    ls->dlgTapeCurrentPos       = "Aktuell position";
    ls->dlgTapeTotalTime        = "Total l�ngd";
    
    ls->dlgZipReset             = "Starta om efter ins�ttning";

    ls->dlgAboutTitle           = "blueMSX - Information";

    ls->dlgLangLangText         = "V�lj spr�k som blueMSX ska anv�nda";
    ls->dlgLangLangTitle        = "blueMSX - Spr�k";

    ls->propTitle               = "blueMSX - Egenskaper";
    ls->propEmulation           = "Emulering";
    ls->propVideo               = "Video";
    ls->propSound               = "Ljud";
    ls->propControls            = "Kontroller";
    ls->propPerformance         = "Prestanda";
    
    ls->propEmuGeneralGB        = "Allm�nt ";
    ls->propEmuFamilyText       = "MSX familj:";
    ls->propEmuMemoryGB         = "Minne ";
    ls->propEmuRamSizeText      = "RAM storlek:";
    ls->propEmuVramSizeText     = "VRAM storlek:";
    ls->propEmuSpeedGB          = "Emuleringshastighet ";
    ls->propEmuSpeedText        = "Emuleringshastighet:";

    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Monitor typ:";
    ls->propMonEmuText          = "Monitor emulering ";
    ls->propVideoTypeText       = "Video typ:";
    ls->propWindowSizeText      = "F�nsterstorlek:";

    ls->propPerfVideoDrvGB      = "Video Driver ";
    ls->propPerfVideoDispDrvText= "Display driver:";
    ls->propPerfFrameSkipText   = "Frame skipping:";
    ls->propPerfAudioDrvGB      = "Audiodriver ";
    ls->propPerfAudioDrvText    = "Ljuddriver:";
    ls->propPerfAudioBufSzText  = "Storlek p� ljudbuffer:";
    ls->propPerfEmuGB           = "Emulering ";
    ls->propPerfSyncModeText    = "Synkronisering:";

    ls->propSndChipEmuGB        = "Emulering av ljudchip ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";

    ls->enumVideoMonColor       = "F�rg";
    ls->enumVideoMonGrey        = "Svartvit";
    ls->enumVideoMonGreen       = "Gr�n";
    ls->enumVideoMonAmber       = "Orange";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Ingen";
    ls->enumVideoEmuYc          = "Y/C kabel (skarp)";
    ls->enumVideoEmuYcBlur      = "Brusig Y/C kabel (skarp)";
    ls->enumVideoEmuComp        = "Kompositkabel (suddig)";
    ls->enumVideoEmuCompBlur    = "Brusig komposit (suddig)";
    ls->enumVideoEmuScale2x     = "Scale 2x";

    ls->enumVideoSize1x         = "Normal - 320x200";
    ls->enumVideoSize2x         = "Dubbel - 640x400";
    ls->enumVideoSizeFullscreen = "Helsk�rm";

    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "Ingen";
    ls->enumVideoFrameskip1     = "1 bild";
    ls->enumVideoFrameskip2     = "2 bilder";
    ls->enumVideoFrameskip3     = "3 bilder";
    ls->enumVideoFrameskip4     = "4 bilder";
    ls->enumVideoFrameskip5     = "5 bilder";

    ls->enumSoundDrvNone        = "Inget ljud";
    ls->enumSoundDrvWMM         = "WMM driver";
    ls->enumSoundDrvDirectX     = "DirectX driver";

    ls->enumEmuSync1ms          = "1ms (bast)";
    ls->enumEmuSyncAuto         = "Automatisk (snabbast)";

    ls->enumControlsJoyNone     = "Ingen";
    ls->enumControlsJoyMouse    = "Mus";

    ls->dlgAboutAbout           = "INFORMATION\r\n========";
    ls->dlgAboutVersion         = "Version:";
    ls->dlgAboutBuildNumber     = "Bygge:";
    ls->dlgAboutBuildDate       = "Datum:";
    ls->dlgAboutCreat           = "Skapat av Daniel Vik";
    ls->dlgAboutDevel           = "UTVECKLARE\r\n========";
    ls->dlgAboutThanks          = "TACK TILL\r\n=======";
    ls->dlgAboutLisence         = "LICENS\r\n"
                                  "=====\r\n\r\n"
                                  "Denna programvara �r erbjuden 'som den �r', utan n�gon explicit eller "
                                  "implicit garanti. Inte av n�gon h�ndelse kommer f�rfattaren/na att h�llas "
                                  "ansvariga f�r n�gra skador orsakade av detta program.\r\n\r\n"
                                  "Bes�k www.bluemsx.com for mer information.";

    ls->menuTools                = "Verktyg";
    ls->menuToolsMachine         = "Konfigureringsverktyg";
    ls->menuPropsSettings        = "Inst�llningar";
    ls->menuCasRewindAfterInsert = "Spola tillbaka vid ins�ttning";
    ls->menuCasUseReadOnly       = "Till�t endast l�sning av kasett";
    ls->lmenuCasSaveAs           = "Spara kasett som...";
    
    ls->dlgSaveCassette          = "blueMSX - Spara Kasett";
    ls->dlgTapeCustom            = "Visa Specialfiler";
    ls->dlgTapeSetPosText        = "Kasettposition:";
    ls->dlgTabPosition           = "Position";
    ls->dlgTabType               = "Typ";
    ls->dlgTabFilename           = "Filnamn";

    ls->propSettings             = "Inst�llningar";
    
    ls->propSetFileHistoryGB     = "Filhistoria ";
    ls->propSetFileHistorySize   = "Antal element i filhistorian:";
    ls->propSetFileHistoryClear  = "Rensa historia";
    ls->propSetScreenSaver       = " Deaktivera sk�rmsl�ckare n�r blueMSX k�r";

    ls->confTitle                = "blueMSX - Konfigureringsverktyg";
    ls->confSave                 = "Spara";
    ls->confSaveAs               = "Spara Som...";
    ls->confRun                  = "K�r";
    ls->confClose                = "St�ng";
    ls->confConfigText           = "Konfigurering:";
    ls->confSlotLayout           = "Slot mappning";
    ls->confMemory               = "Minne";
    ls->confChipEmulation        = "Chipemulering";

    ls->confSlotLayoutGB         = "Slot Layout ";
    ls->confSlotExtSlotGB        = "Externa slots ";
    ls->confSlotCart             = "Cartridge:";
    ls->confSlotPrimary          = "Prim�r";
    ls->confSlotExpanded         = "Expanderad (4 subslottar)";

    ls->confMemAdd               = "Ny...";
    ls->confMemEdit              = "�ndra...";
    ls->confMemRemove            = "Ta Bort";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Adress";
    ls->confMemType              = "Typ";
    ls->confMemRomImage          = "Rom Fil";
    
    ls->confChipVideoGB          = "Video ";
    ls->confChipVideoChip        = "Video Chip:";
    ls->confChipVideoRam         = "Video RAM:";
    ls->confChipSoundGB          = "Audio ";

    ls->confSaveTitle            = "blueMSX - Spara Konfigurering";
    ls->confSaveText             = "Vill du skriva �ver maskinkonfigureringen? :";

    ls->confEditMemTitle         = "blueMSX - �ndra Minnesmap";
    ls->confEditMemGB            = "Detailjer ";
    ls->confEditMemType          = "Typ:";
    ls->confEditMemFile          = "Fil:";
    ls->confEditMemAddress       = "Adress";
    ls->confEditMemSize          = "Storlek";
    ls->confEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Konfigurering";
    ls->confExitSaveTitle        = "blueMSX - Avsluta Konfigureringsverktyg";
    ls->confExitSaveText         = "Vill du stanga konfigureringsverktyget utan att spara dina �ndringar?";

    ls->confSaveAsMachineTitle   = "blueMSX - Spara Maskinkonfigurering Som...";
    ls->confSaveAsMachineName    = "Maskinnamn:";

    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypes            = " Registrera filtyper med blueMSX (.rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " Avaktivera WIndows menyer n�r emulatorn k�r";
    ls->propWindowsEnvGB         = "Windows Milj� ";
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW accel.";
    ls->propClearHistory         = "Vill du verkligen radera filhistorien ?";

    ls->propMonHorizStretch      = " Korrekt horizontell vidd";
    ls->propMonVertStretch       = " Vertikal stretch";
    ls->propEmuFrontSwitchGB     = "Panasonic Switches ";
    ls->propEmuFrontSwitch       = " Front Switch";
    ls->propEmuAudioSwitch       = " MSX-AUDIO cartridge switch";


    ls->confCmosGB                = "CMOS ";
    ls->confCmosEnable            = " Anv�nd CMOS";
    ls->confCmosBattery           = " Anv�nd Laddat Batteri";

    ls->menuCartSCCPlus          = "SCC+ Cartridge";
    ls->menuCartSCC              = "SCC Cartridge";
    
    ls->warningTitle             = "blueMSX - Varning";

    // New entries in 1.5.1
    ls->menuToolsShortcuts      = "Kortkommando Verktyg";

    ls->shortcutSaveConfig      = "blueMSX - Spara Konfigurering";
    ls->shortcutOverwriteConfig = "Vill du skriva �ver kortkommando konfigureringen:";
    ls->shortcutExitConfig      = "blueMSX - Avsluta Kortkommandoverktyget";
    ls->shortcutDiscardConfig   = "Vill du stanga konfigureringsverktyget utan att spara dina �ndringar?";
    ls->shortcutSaveConfigAs    = "blueMSX - Spara Kortkommando Konfigurering Som...";
    ls->shortcutConfigName      = "Konfigurering:";
    ls->shortcutNewProfile      = "< Ny Profil >";
    ls->shortcutConfigTitle     = "blueMSX - Konfigurering av Kortkommandon";
    ls->shortcutAssign          = "Tilldela";
    ls->shortcutPressText       = "Tryck kortkommando:";
    ls->shortcutScheme          = "Kommandoschema:";

    ls->shortcutCartInsert1     = "S�tt in Cartridge 1";
    ls->shortcutCartRemove1     = "Ta ur Cartridge 1";
    ls->shortcutCartInsert2     = "S�tt in Cartridge 2";
    ls->shortcutCartRemove2     = "Ta ur Cartridge 2";
    ls->shortcutCartAutoReset   = "Starta om efter Ins�ttning av Cartridge";
    ls->shortcutDiskInsertA     = "S�tt in Diskett A";
    ls->shortcutDiskRemoveA     = "Ta ur Diskett A";
    ls->shortcutDiskChangeA     = "Snabbbyt Diskett A";
    ls->shortcutDiskAutoResetA  = "Starta om efter Ins�ttning av Diskett";
    ls->shortcutDiskInsertB     = "S�tt in Diskett B";
    ls->shortcutDiskRemoveB     = "Ta ur Diskett B";
    ls->shortcutCasInsert       = "S�tt in Kasett";
    ls->shortcutCasEject        = "Ta ur Kasett";
    ls->shortcutCasAutorewind   = "Sl� Av/P� Automatisk Tillbakaspolning";
    ls->shortcutCasReadOnly     = "Sl� Av/P� Skrivskydd p� Kasettfiler";
    ls->shortcutCasSetPosition  = "S�tt Kasettposition";
    ls->shortcutCasRewind       = "Spola Tillabaka Kasett";
    ls->shortcutCasSave         = "Spara Kasett till fil";
    ls->shortcutCpuStateLoad    = "Ladda CPU-tillst�nd";
    ls->shortcutCpuStateSave    = "Spara CPU-tillst�nd";
    ls->shortcutCpuStateQload   = "Snabbladda CPU-tillst�nd";
    ls->shortcutCpuStateQsave   = "Snabbspara CPU-tillst�nd";
    ls->shortcutAudioCapture    = "Starta/Stanna Audioinspelning";
    ls->shortcutScreenshotOrig  = "Spar Sk�rmdump";
    ls->shortcutScreenshotSmall = "Spar Liten Ofiltrerad Sk�rmdump";
    ls->shortcutScreenshotLarge = "Spar Stor Ofiltrerad Sk�rmdump";
    ls->shortcutQuit            = "Avsluta blueMSX";
    ls->shortcutRunPause        = "K�r/Pause Emuleringen";
    ls->shortcutStop            = "Stanna Emuleringen";
    ls->shortcutResetHard       = "H�rd Omstart";
    ls->shortcutResetSoft       = "Mjuk Omstart";
    ls->shortcutResetClean      = "Full Omstart";
    ls->shortcutSizeSmall       = "V�xla till Liten F�nsterstorlek";
    ls->shortcutSizeNormal      = "V�xla till Normal F�nsterstorlek";
    ls->shortcutSizeFullscreen  = "V�xla till Fullsk�rm";
    ls->shortcutToggleFullscren = "V�xla till/fr�n Fullsk�rm";
    ls->shortcutVolumeIncrease  = "�ka Volymen";
    ls->shortcutVolumeDecrease  = "Minska Volymen";
    ls->shortcutVolumeMute      = "St�ng av Volymen";
    ls->shortcutSwitchMsxAudio  = "Sl� om MSX-AUDIO Switch";
    ls->shortcutSwitchFront     = "Sl� om Panasonic Front Switch";
    ls->shortcutToggleMouseLock = "Sl� om Musl�s";
    ls->shortcutEmuSpeedMax     = "Maximal Emuleringshastighet";
    ls->shortcutEmuSpeedNormal  = "Minska Emuleringhastigheten";
    ls->shortcutEmuSpeedInc     = "�ka Emuleringhastigheten";
    ls->shortcutEmuSpeedDec     = "Minska Emuleringhastigheten";
    ls->shortcutShowEmuProp     = "�ppna Emuleringsf�nstret";
    ls->shortcutShowVideoProp   = "�ppna Videof�nstret";
    ls->shortcutShowAudioProp   = "�ppna Audiof�nstret";
    ls->shortcutShowCtrlProp    = "�ppna Kontrollf�nstret";
    ls->shortcutShowPerfProp    = "�ppna Prestandaf�nstret";
    ls->shortcutShowSettProp    = "�ppna Inst�llningsf�nstret";
    ls->shortcutShowLanguage    = "�ppna Spr�kf�nstret";
    ls->shortcutShowMachines    = "�ppna Konfigureringsverktyget";
    ls->shortcutShowShortcuts   = "�ppna Kortkommandoverktyget";
    ls->shortcutShowHelp        = "�ppna Hj�lpf�nstret";
    ls->shortcutShowAbout       = "�ppna \"Om blueMSX\"-f�nstret";

    ls->shortcutSpecialMenu1    = "Visa Specialrom meny f�r Cartridge 1";
    ls->shortcutSpecialMenu2    = "Visa Specialrom meny f�r Cartridge 2";
    ls->shortcutVolumeStereo    = "V�xla mellan mono/stereo";
    ls->shortcutThemeSwitch     = "V�xla f�nstretema";
    ls->shortcutToggleSpriteEnable = "Visa/D�lj Sprites";
    
    ls->shortcutShowApearProp   = "�ppna Utseenedef�nstret";
    ls->menuPropsApearance      = "Utseende";
    ls->propThemeGB             = "Tema ";
    ls->propTheme               = "Tema";

    ls->propMonBrightness       = "Ljusstyrka:";
    ls->propMonContrast         = "Kontrast:";
    ls->propMonSaturation       = "F�rgm�ttnad:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanlinjer:";

    ls->dlgRomType              = "Rom Typ:";
    ls->propOpenRomGB           = "�ppna Rom Dialog ";
    ls->propDefaultRomType      = "Default Rom Typ:";
    ls->propGuessRomType        = "Gissa Rom Typ";

    ls->propFile                = "Filer";
    ls->propSettDefSlotGB       = "Dra och Sl�pp ";
    ls->propSettDefSlots        = "S�tt in Rom i:";
    ls->propSettDefSlot         = " Slot";
    ls->propSettDefDrives       = "S�tt in Diskett i:";
    ls->propSettDefDrive        = " Drive";
    ls->menuPropsFile           = "Filer";
    ls->shortcutShowFiles       = "�ppna Filerf�nstret";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "S�tt in Directory";
    ls->shortcutDiskDirInsertA  = "S�tt in Directory som Diskett A";
    ls->shortcutDiskDirInsertB  = "S�tt in Directory som Diskett B";
    ls->propMonDeInterlace      = " De-interlace";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "Sl� om Pause Switch";
    ls->shortcutSizeMinimized   = "Minimera f�nster";
    ls->shortcutEmuSpeedToggle  = "V�xla Mellan Normal och Max Emuleringshastighet";
    ls->shortcutToggleCpuTrace  = "Sl� p�/av CPU trace";
  
    ls->enumVideoEmuMonitor     = "Monitor";

    ls->propEmuPauseSwitch      = " Pause Switch";
    ls->propVideoFreqText       = "Video Frekvens:";
    ls->propVideoFreqAuto       = "Automatisk";
    ls->propSndOversampleText   = "�versampling:";

    ls->confChipExtras          = "Extra";
    ls->confBoardGB             = "Board ";
    ls->confBoardText           = "Board Typ:";
    ls->confCpuFreqGB            = "CPU Frekvens ";
    ls->confZ80FreqText          = "Z80 Frekvens:";
    ls->confR800FreqText         = "R800 Frekvens:";
    ls->confFdcGB                = "Kontroller f�r Diskettenhet ";
    ls->confCFdcNumDrivesText    = "Antal Diskettenheter:";

    ls->propPriorityBoost        = " H�j prioriteten p� blueMSX";
    
    // New entries in 2.1
    ls->propEmuFdcTiming        = "Sl� Av Diskettstationstiming";
    ls->shortcutToggleFdcTiming = "Sl� p�/av Diskettstationstiming";

    // New entries in 2.2
    ls->menuCartHBI55           = "Sony HBI-55 Cartridge";
    ls->enumVideoEmuHq2x        = "Hq2x";
    ls->propMonColorGhosting    = "RF-Modulering";

    ls->keyconfigSelectedKey    = "V�lj tangent:";
    ls->keyconfigMappedTo       = "Mappad till:";
    ls->keyconfigMappingScheme  = "Mapschema:";

    ls->warningDiscardChanges   = "Vill du st�nga verktyget utan att spara dina �ndringar?";

    ls->confSaveAsTitle         = "Spara Konfigurering Som...";

    ls->menuToolsKeyboard       = "Tangentbordseditor";
    ls->shortcutShowKeyboard    = "Visa Tangentbordseditor";

    ls->menuVideoSource         = "Videok�lla";
    ls->menuVideoSourceDefault  = "Ingen videok�lla inkopplad";
    ls->menuVideoChipAutodetect = "Automatisk detektering av video chip";
    ls->propFullscreenResText   = "Fullsk�rmsuppl�sning:";
    ls->dlgSavePreview          = "F�rvisning";
    ls->dlgSaveDate             = "Tid Sparad:";
    
    ls->enumVideoMonAmber       = "Amber";

    ls->menuPropsPorts          = "Portar";
    ls->propPortsLptGB          = "Parallellport ";
    ls->propPortsComGB          = "Serieportar ";
    ls->propPortsLptText        = "Port:";
    ls->propPortsCom1Text       = "Port 1:";

    ls->shortcutShowDebugger    = "Visa Debugger";
    ls->shortcutShowTrainer     = "Visa Trainer";
    ls->shortcutShowPorts       = "Visa Portegenskaper";
    
    ls->propPorts               = "Portar";
    ls->propPortsNone           = "Ingen";

    // New entries in 2.3
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle";

    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "Skriv till Fil";
    ls->propPortsOpenLogFile    = "�ppna Logfil";
    ls->propPortsEmulateMsxPrn  = "Emulering:";

    ls->shortcutPrnFormFeed     = "Form Feed p� Skrivare";

    ls->menuPrnFormfeed         = "Form Feed";
    ls->menuFilePrn             = "Skrivare";
    ls->propPortsComFile        = "Skicka till Fil";

    // New entries in 2.4
    ls->shortcutShowMixer       = "Show Mixer";
    ls->menuToolsMixer          = "Mixer";
    
    ls->propSndMidiInGB         = "MIDI In ";
    ls->propSndMidiOutGB        = "MIDI Ut ";
    ls->propSndMt32ToGm         = " Konvertera MT-32 instrument till General MIDI";

    ls->textDevice              = "Device:";
    ls->textFilename            = "Filenamn:";
    ls->textFile                = "Fil";
    ls->textNone                = "Ingen";

    ls->enumEmuSyncNone         = "Ingen";
    ls->enumEmuSyncAuto         = "Automatisk (snabb)";
    ls->enumEmuSync1ms          = "Synkronisera till MSX refresh";
    ls->enumEmuSyncVblank       = "Synkronisera till PC Vertikal Blank";

    ls->propMonEffectsGB        = "Effekter ";
    
    ls->confSlot                = "Slot";
    ls->confSubslot             = "Subslot";

    ls->shortcutDescription     = "Kortkommando";
    ls->shortcutKey             = "Hotkey";
    ls->fileRom                 = "Rom fil";
    ls->confOpenRom             = "�ppna Rom fil";
    ls->fileAll                 = "Alla Filer";
    ls->fileCpuState            = "CPU-tillstand";
    ls->fileDisk                = "Diskettfil";
    ls->fileCas                 = "Kasettfil";

    ls->menuCartExternalRam     = "Externt RAM";

};

#endif

