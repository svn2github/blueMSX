/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageSwedish.h,v $
**
** $Revision: 1.4 $
**
** $Date: 2004-12-17 18:14:22 $
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
    ls->statusBarStopped        = "  Stannad";
    ls->statusBarPaused         = "  Pausad";
    ls->statusBarRunning        = "  Startad";
    
    ls->menuHardReset           = "H�rd Omstart";
    ls->menuSoftReset           = "Mjuk Omstart";
    
    ls->menuCartInsert          = "S�tt in";
    ls->menuCartRemove          = "Ta ur";
    ls->menuCartAutoReset       = "Starta om efter ins�ttning/urdagning";
    ls->menuCartNoRecentFiles   = "- ingen filhistoria -";
    ls->menuCartFMPac           = "FM-PAC Cartridge";
    ls->menuCartPac             = "PAC Cartridge";
    ls->menuCartSpecial         = "Special";

    ls->menuDiskInsert          = "S�tt in";
    ls->menuDiskEject           = "Ta ur";
    ls->menuDiskAutoStart       = "Starta om efter ins�ttning/urdagning";
    ls->menuDiskNoRecentFiles   = "- ingen filhistoria -";
    
    ls->menuCasInsert           = "S�tt in";
    ls->menuCasEject            = "Ta ur";
    ls->menuCasSetPosition      = "S�tt position";
    ls->menuCasRewind           = "Spola tillbaka";
    ls->menuCasNoRecentFiles    = "- ingen filhistoria -";

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

    ls->menuFileCart1           = "Cartridge slot 1";
    ls->menuFileCart2           = "Cartridge slot 2";
    ls->menuFileDiskA           = "Diskettstaion A";
    ls->menuFileDiskB           = "Diskettstaion B";
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

    ls->tooltipReset            = "Starta om emulatorn";
    ls->tooltipCart1            = "S�tt in Cartridge i Slot 1";
    ls->tooltipCart2            = "S�tt in Cartridge i Slot 2";
    ls->tooltipDiskA            = "S�tt in diskett i diskettstation A";
    ls->tooltipDiskB            = "S�tt in diskett i diskettstation B";
    ls->tooltipCas              = "S�tt in kassettband";
    ls->tooltipStart            = "Starta emuleringen";
    ls->tooltipResume           = "Forts�tt emuleringen";
    ls->tooltipPause            = "Pausa emuleringen";
    ls->tooltipWindowSize       = "S�tt f�nsterstorlek";
    ls->tooltipProperties       = "�ppna Egenskaper";
    ls->tooltipHelp             = "�ppna Hjalp fonstret";

    ls->dlgMainWindow           = "  blueMSX";
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

    ls->dlgJoyTitle1            = "blueMSX - Styrspak tangentgrupp A";
    ls->dlgJoyTitle2            = "blueMSX - Styrspak tangentgrupp B";
    ls->dlgJoyUpText            = "Upp";
    ls->dlgJoyDownText          = "Ner";
    ls->dlgJoyLeftText          = "V�nster";
    ls->dlgJoyRightText         = "H�ger";
    ls->dlgJoyButton1Text       = "Knapp 1";
    ls->dlgJoyButton2Text       = "Knapp 2";
    ls->dlgJoyGB                = "Konfigurering av tangentgrupp ";

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
    ls->propVideoYypeText       = "Video typ:";
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
    ls->propSndMixerGB          = "Ljudmixer ";
    ls->propSndMonoText         = "mono";
    ls->propSndStereoText       = "stereo";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "MASTER";

    ls->propJoyPort1GB          = "Port #1 ";
    ls->propJoyPort2GB          = "Port #2 ";
    ls->propJoyAutofireText     = "Auto eld:";
    ls->propJoyKeysetGB         = "Tangentgrupper for styrspak ";
    ls->propJoyKeyest1          = "Konfigurera grupp A";
    ls->propJoyKeyest2          = "Konfigurera grupp B";

    ls->enumVideoMonColor       = "F�rg";
    ls->enumVideoMonGrey        = "Svartvit";
    ls->enumVideoMonGreen       = "Gr�n";

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
    ls->enumControlsJoyNumpad   = "Numeriska tangenter";
    ls->enumControlsJoyKeysetA  = "Tangentgrupp A";
    ls->enumControlsJoyKeysetB  = "Tangentgrupp B";
    ls->enumControlsJoyPCjoy1   = "PC styrspak #1";
    ls->enumControlsJoyPCjoy2   = "PC styrspak #2";
    ls->enumControlsJoyMouse    = "Mus";

    ls->enumControlsAfOff       = "Av";
    ls->enumControlsAfSlow      = "L�ngsam";
    ls->enumControlsAfMedium    = "Medel";
    ls->enumControlsAfFast      = "Snabb";

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
    ls->propSetScreenSaverGB     = "Sk�rmsl�ckare ";
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
    ls->confSlotSlot0            = "Slot 0";
    ls->confSlotSlot1            = "Slot 1";
    ls->confSlotSlot2            = "Slot 2";
    ls->confSlotSlot3            = "Slot 3";
    ls->confSlotCart1            = "Cartridge 1:";
    ls->confSlotCart2            = "Cartridge 2:";
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

    ls->slotEditMemTitle         = "blueMSX - �ndra Minnesmap";
    ls->slotEditMemGB            = "Detailjer ";
    ls->slotEditMemType          = "Typ:";
    ls->slotEditMemFile          = "Fil:";
    ls->slotEditMemAddress       = "Adress";
    ls->slotEditMemSize          = "Storlek";
    ls->slotEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Konfigurering";
    ls->confExitSaveTitle        = "blueMSX - Avsluta Konfigureringsverktyg";
    ls->confExitSaveText         = "Vill du stanga konfigureringsverktyget utan att spara dina �ndringar?";

    ls->confSaveAsTitle          = "blueMSX - Spara Maskinkonfigurering Som...";
    ls->confSaveAsMachineName    = "Maskinnamn:";

    ls->confEditMemInternalRoms  = "blueMSX - Interna Rom Filer";


    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypesGB          = "Filtyper ";
    ls->propFileTypes            = " Registrera filtyper med blueMSX (.rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " Avaktivera WIndows menyer n�r emulatorn k�r";
    ls->propWindowsEnvGB         = "Windows Milj� ";
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW accel.";
    ls->enumVideoDrvDirectDrawHWSys = "DirectDraw mix."; 
    ls->propClearHistory         = "Vill du verkligen radera filhistorien ?";

    ls->propMonHorizStretch      = " Korrekt horizontell vidd";
    ls->propMonVertStretch       = " Vertikal stretch";
    ls->propEmuFrontSwitchGB     = "Panasonic Switches ";
    ls->propEmuFrontSwitch       = " Front Switch";
    ls->propEmuAudioSwitch       = " MSX-AUDIO cartridge switch";


    ls->dlgCmosGB                = "CMOS ";
    ls->dlgCmosEnable            = " Anv�nd CMOS";
    ls->dlgCmosBattery           = " Anv�nd Laddat Batteri";

    ls->menuCartSnatcher         = "The Snatcher Cartridge";
    ls->menuCartSdSnatcher       = "SD-Snatcher Cartridge";
    ls->menuCartSCCMirrored      = "SCC Speglad Cartridge";
    ls->menuCartSCCExpanded      = "SCC Expanderad Cartridge";
    ls->menuCartSCCPlus          = "SCC+ Cartridge";
    ls->menuCartSCC              = "SCC Cartridge";
    
    ls->warningTitle             = "blueMSX - Varning";
    ls->tooltipStop              = "Stanna emuleringen";

    // New entries in 1.5.1
    ls->enumControlsJoyKeyset   = "Keyset";    
    ls->propJoyConfigKeyset     = "Config Keyset";
    ls->propJoyControlText      = "Control:";
    ls->propJoyButtonText       = "Button";
    ls->propJoyButtonAText      = "Button A:";
    ls->propJoyButtonBText      = "Button B:";

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
    ls->propApearance           = "Utseende";
    ls->propThemeGB             = "Tema ";
    ls->propTheme               = "Tema";
    ls->propThemeClassic        = "Klassisk";
    ls->propThemeBlue           = "DIGIblue";

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
    ls->propSettDefSlot1        = " Slot 1";
    ls->propSettDefSlot2        = " Slot 2";
    ls->propSettDefDrives       = "S�tt in Diskett i:";
    ls->propSettDefDriveA       = " Drive A";
    ls->propSettDefDriveB       = " Drive B";
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
    ls->dlgCpuFreqGB            = "CPU Frekvens ";
    ls->dlgZ80FreqText          = "Z80 Frekvens:";
    ls->dlgR800FreqText         = "R800 Frekvens:";
    ls->dlgFdcGB                = "Kontroller f�r Diskettenhet ";
    ls->dlgCFdcNumDrivesText    = "Antal Diskettenheter:";

    ls->propPriorityBoost        = " H�j prioriteten p� blueMSX";
    
    // New entries in 2.0.1
    ls->propEmuFdcTiming        = "Sl� Av Diskettstationstiming";
    ls->shortcutToggleFdcTiming = "Sl� p�/av Diskettstationstiming";
    ls->propUseRegistry         = "Spara konnfigurering i Windows Registry";
};

#endif

