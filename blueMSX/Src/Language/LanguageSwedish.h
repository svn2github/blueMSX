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
    ls->menuInsert              = "Sätt in";
    ls->menuEject               = "Ta ur";

    ls->menuCartAutoReset       = "Starta om efter insättning/urdagning";
    ls->menuCartFMPac           = "FM-PAC Cartridge";
    ls->menuCartPac             = "PAC Cartridge";

    ls->menuDiskAutoStart       = "Starta om efter insättning/urdagning";
    
    ls->menuCasSetPosition      = "Sätt position";
    ls->menuCasRewind           = "Spola tillbaka";

    ls->menuZoomNormal          = "Normal storlek";
    ls->menuZoomDouble          = "Dubbel storlek";
    ls->menuZoomFullscreen      = "Helskärm";
    
    ls->menuPropsEmulation      = "Emulering";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Ljud";
    ls->menuPropsControls       = "Kontroller";
    ls->menuPropsPerformance    = "Prestanda";
    ls->menuPropsLanguage       = "Språk";
    
    ls->menuHelpHelp            = "Hjälp";
    ls->menuHelpAbout           = "Om blueMSX";

    ls->menuFileCart            = "Cartridge slot";
    ls->menuFileDisk            = "Diskettstaion";
    ls->menuFileCas             = "Kasett";
    ls->menuFileLoadState       = "Läs in CPU-tillstand";
    ls->menuFileSaveState       = "Spara CPU-tillstand";
    ls->menuFileQLoadState      = "Snabbladda CPU-tillstand";
    ls->menuFileQSaveState      = "Snabbspara CPU-tillstand";
    ls->menuFileCaptureAudio    = "Spara ljud";
    ls->menuFileScreenShot      = "Spara skärmdump";
    ls->menuFileExit            = "Avsluta";

    ls->menuRunRun              = "Kör";
    ls->menuRunPause            = "Paus";
    ls->menuRunStop             = "Stanna";
    ls->menuRunSoftReset        = "Mjuk Omstart";
    ls->menuRunHardReset        = "Hård Omstart";
    ls->menuRunCleanReset       = "Full Omstart";

    ls->menuFile                = "Arkiv";
    ls->menuRun                 = "Kör";
    ls->menuWindow              = "Fönster";
    ls->menuOptions             = "Egenskaper";
    ls->menuHelp                = "Hjälp";
    
    ls->errorTitle              = "blueMSX - Fel";
    ls->errorEnterFullscreen    = "Misslyckades att byta till fullskärm.           \n";
    ls->errorDirectXFailed      = "Misslyckades att skapa DirectX objekt.          \nAnvänder GDI istället.\nKontrollera video inställningarna.";
    ls->errorNoRomInZip         = "Kunde inte hitta en .rom fil i zip arkivet.";
    ls->errorNoDskInZip         = "Kunde inte hitta en .dsk fil i zip arkivet.";
    ls->errorNoCasInZip         = "Kunde inte hitta en .cas fil i zip arkivet.";
    ls->errorNoHelp             = "Kunde inte hitta hjälpfilen.";
    ls->errorStartEmu           = "Misslyckades att starta emulatorn.";


    ls->dlgLoadRom              = "blueMSX - Ladda en rom fil";
    ls->dlgLoadDsk              = "blueMSX - Ladda en dsk fil";
    ls->dlgLoadCas              = "blueMSX - Ladda en cas fil";
    ls->dlgLoadRomDskCas        = "blueMSX - Ladda en rom, dsk eller cas fil";
    ls->dlgLoadRomDesc          = "Välj en cartridge fil:";
    ls->dlgLoadDskDesc          = "Välj en diskett fil:";
    ls->dlgLoadCasDesc          = "Välj en kassett fil:";
    ls->dlgLoadRomDskCasDesc    = "Välj en fil:";
    ls->dlgLoadState            = "Ladda CPU-tillstand";
    ls->dlgSaveState            = "Spara CPU-tillstand";
    ls->dlgInsertRom1           = "Sätt in ROM cartridge i slot 1";
    ls->dlgInsertRom2           = "Sätt in ROM cartridge i slot 2";
    ls->dlgInsertDiskA          = "Sätt in diskett i diskettstation A";
    ls->dlgInsertDiskB          = "Sätt in diskett i diskettstation B";
    ls->dlgInsertCas            = "Sätt in kassettband";

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Öppna";
    ls->dlgCancel               = "Avbryt";

    ls->dlgTapeTitle            = "blueMSX - Kassettposition";
    ls->dlgTapeFrameText        = "Kassettposition";
    ls->dlgTapeCurrentPos       = "Aktuell position";
    ls->dlgTapeTotalTime        = "Total längd";
    
    ls->dlgZipReset             = "Starta om efter insättning";

    ls->dlgAboutTitle           = "blueMSX - Information";

    ls->dlgLangLangText         = "Välj språk som blueMSX ska använda";
    ls->dlgLangLangTitle        = "blueMSX - Språk";

    ls->propTitle               = "blueMSX - Egenskaper";
    ls->propEmulation           = "Emulering";
    ls->propVideo               = "Video";
    ls->propSound               = "Ljud";
    ls->propControls            = "Kontroller";
    ls->propPerformance         = "Prestanda";
    
    ls->propEmuGeneralGB        = "Allmänt ";
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
    ls->propWindowSizeText      = "Fönsterstorlek:";

    ls->propPerfVideoDrvGB      = "Video Driver ";
    ls->propPerfVideoDispDrvText= "Display driver:";
    ls->propPerfFrameSkipText   = "Frame skipping:";
    ls->propPerfAudioDrvGB      = "Audiodriver ";
    ls->propPerfAudioDrvText    = "Ljuddriver:";
    ls->propPerfAudioBufSzText  = "Storlek på ljudbuffer:";
    ls->propPerfEmuGB           = "Emulering ";
    ls->propPerfSyncModeText    = "Synkronisering:";

    ls->propSndChipEmuGB        = "Emulering av ljudchip ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";

    ls->enumVideoMonColor       = "Färg";
    ls->enumVideoMonGrey        = "Svartvit";
    ls->enumVideoMonGreen       = "Grön";
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
    ls->enumVideoSizeFullscreen = "Helskärm";

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
                                  "Denna programvara är erbjuden 'som den är', utan någon explicit eller "
                                  "implicit garanti. Inte av någon händelse kommer författaren/na att hållas "
                                  "ansvariga för några skador orsakade av detta program.\r\n\r\n"
                                  "Besök www.bluemsx.com for mer information.";

    ls->menuTools                = "Verktyg";
    ls->menuToolsMachine         = "Konfigureringsverktyg";
    ls->menuPropsSettings        = "Inställningar";
    ls->menuCasRewindAfterInsert = "Spola tillbaka vid insättning";
    ls->menuCasUseReadOnly       = "Tillåt endast läsning av kasett";
    ls->lmenuCasSaveAs           = "Spara kasett som...";
    
    ls->dlgSaveCassette          = "blueMSX - Spara Kasett";
    ls->dlgTapeCustom            = "Visa Specialfiler";
    ls->dlgTapeSetPosText        = "Kasettposition:";
    ls->dlgTabPosition           = "Position";
    ls->dlgTabType               = "Typ";
    ls->dlgTabFilename           = "Filnamn";

    ls->propSettings             = "Inställningar";
    
    ls->propSetFileHistoryGB     = "Filhistoria ";
    ls->propSetFileHistorySize   = "Antal element i filhistorian:";
    ls->propSetFileHistoryClear  = "Rensa historia";
    ls->propSetScreenSaver       = " Deaktivera skärmsläckare när blueMSX kör";

    ls->confTitle                = "blueMSX - Konfigureringsverktyg";
    ls->confSave                 = "Spara";
    ls->confSaveAs               = "Spara Som...";
    ls->confRun                  = "Kör";
    ls->confClose                = "Stäng";
    ls->confConfigText           = "Konfigurering:";
    ls->confSlotLayout           = "Slot mappning";
    ls->confMemory               = "Minne";
    ls->confChipEmulation        = "Chipemulering";

    ls->confSlotLayoutGB         = "Slot Layout ";
    ls->confSlotExtSlotGB        = "Externa slots ";
    ls->confSlotCart             = "Cartridge:";
    ls->confSlotPrimary          = "Primär";
    ls->confSlotExpanded         = "Expanderad (4 subslottar)";

    ls->confMemAdd               = "Ny...";
    ls->confMemEdit              = "Ändra...";
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
    ls->confSaveText             = "Vill du skriva över maskinkonfigureringen? :";

    ls->confEditMemTitle         = "blueMSX - Ändra Minnesmap";
    ls->confEditMemGB            = "Detailjer ";
    ls->confEditMemType          = "Typ:";
    ls->confEditMemFile          = "Fil:";
    ls->confEditMemAddress       = "Adress";
    ls->confEditMemSize          = "Storlek";
    ls->confEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Konfigurering";
    ls->confExitSaveTitle        = "blueMSX - Avsluta Konfigureringsverktyg";
    ls->confExitSaveText         = "Vill du stanga konfigureringsverktyget utan att spara dina ändringar?";

    ls->confSaveAsMachineTitle   = "blueMSX - Spara Maskinkonfigurering Som...";
    ls->confSaveAsMachineName    = "Maskinnamn:";

    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypes            = " Registrera filtyper med blueMSX (.rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " Avaktivera WIndows menyer när emulatorn kör";
    ls->propWindowsEnvGB         = "Windows Miljö ";
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW accel.";
    ls->propClearHistory         = "Vill du verkligen radera filhistorien ?";

    ls->propMonHorizStretch      = " Korrekt horizontell vidd";
    ls->propMonVertStretch       = " Vertikal stretch";
    ls->propEmuFrontSwitchGB     = "Panasonic Switches ";
    ls->propEmuFrontSwitch       = " Front Switch";
    ls->propEmuAudioSwitch       = " MSX-AUDIO cartridge switch";


    ls->confCmosGB                = "CMOS ";
    ls->confCmosEnable            = " Använd CMOS";
    ls->confCmosBattery           = " Använd Laddat Batteri";

    ls->menuCartSCCPlus          = "SCC+ Cartridge";
    ls->menuCartSCC              = "SCC Cartridge";
    
    ls->warningTitle             = "blueMSX - Varning";

    // New entries in 1.5.1
    ls->menuToolsShortcuts      = "Kortkommando Verktyg";

    ls->shortcutSaveConfig      = "blueMSX - Spara Konfigurering";
    ls->shortcutOverwriteConfig = "Vill du skriva över kortkommando konfigureringen:";
    ls->shortcutExitConfig      = "blueMSX - Avsluta Kortkommandoverktyget";
    ls->shortcutDiscardConfig   = "Vill du stanga konfigureringsverktyget utan att spara dina ändringar?";
    ls->shortcutSaveConfigAs    = "blueMSX - Spara Kortkommando Konfigurering Som...";
    ls->shortcutConfigName      = "Konfigurering:";
    ls->shortcutNewProfile      = "< Ny Profil >";
    ls->shortcutConfigTitle     = "blueMSX - Konfigurering av Kortkommandon";
    ls->shortcutAssign          = "Tilldela";
    ls->shortcutPressText       = "Tryck kortkommando:";
    ls->shortcutScheme          = "Kommandoschema:";

    ls->shortcutCartInsert1     = "Sätt in Cartridge 1";
    ls->shortcutCartRemove1     = "Ta ur Cartridge 1";
    ls->shortcutCartInsert2     = "Sätt in Cartridge 2";
    ls->shortcutCartRemove2     = "Ta ur Cartridge 2";
    ls->shortcutCartAutoReset   = "Starta om efter Insättning av Cartridge";
    ls->shortcutDiskInsertA     = "Sätt in Diskett A";
    ls->shortcutDiskRemoveA     = "Ta ur Diskett A";
    ls->shortcutDiskChangeA     = "Snabbbyt Diskett A";
    ls->shortcutDiskAutoResetA  = "Starta om efter Insättning av Diskett";
    ls->shortcutDiskInsertB     = "Sätt in Diskett B";
    ls->shortcutDiskRemoveB     = "Ta ur Diskett B";
    ls->shortcutCasInsert       = "Sätt in Kasett";
    ls->shortcutCasEject        = "Ta ur Kasett";
    ls->shortcutCasAutorewind   = "Slå Av/På Automatisk Tillbakaspolning";
    ls->shortcutCasReadOnly     = "Slå Av/På Skrivskydd på Kasettfiler";
    ls->shortcutCasSetPosition  = "Sätt Kasettposition";
    ls->shortcutCasRewind       = "Spola Tillabaka Kasett";
    ls->shortcutCasSave         = "Spara Kasett till fil";
    ls->shortcutCpuStateLoad    = "Ladda CPU-tillstånd";
    ls->shortcutCpuStateSave    = "Spara CPU-tillstånd";
    ls->shortcutCpuStateQload   = "Snabbladda CPU-tillstånd";
    ls->shortcutCpuStateQsave   = "Snabbspara CPU-tillstånd";
    ls->shortcutAudioCapture    = "Starta/Stanna Audioinspelning";
    ls->shortcutScreenshotOrig  = "Spar Skärmdump";
    ls->shortcutScreenshotSmall = "Spar Liten Ofiltrerad Skärmdump";
    ls->shortcutScreenshotLarge = "Spar Stor Ofiltrerad Skärmdump";
    ls->shortcutQuit            = "Avsluta blueMSX";
    ls->shortcutRunPause        = "Kör/Pause Emuleringen";
    ls->shortcutStop            = "Stanna Emuleringen";
    ls->shortcutResetHard       = "Hård Omstart";
    ls->shortcutResetSoft       = "Mjuk Omstart";
    ls->shortcutResetClean      = "Full Omstart";
    ls->shortcutSizeSmall       = "Växla till Liten Fönsterstorlek";
    ls->shortcutSizeNormal      = "Växla till Normal Fönsterstorlek";
    ls->shortcutSizeFullscreen  = "Växla till Fullskärm";
    ls->shortcutToggleFullscren = "Växla till/från Fullskärm";
    ls->shortcutVolumeIncrease  = "Öka Volymen";
    ls->shortcutVolumeDecrease  = "Minska Volymen";
    ls->shortcutVolumeMute      = "Stäng av Volymen";
    ls->shortcutSwitchMsxAudio  = "Slå om MSX-AUDIO Switch";
    ls->shortcutSwitchFront     = "Slå om Panasonic Front Switch";
    ls->shortcutToggleMouseLock = "Slå om Muslås";
    ls->shortcutEmuSpeedMax     = "Maximal Emuleringshastighet";
    ls->shortcutEmuSpeedNormal  = "Minska Emuleringhastigheten";
    ls->shortcutEmuSpeedInc     = "Öka Emuleringhastigheten";
    ls->shortcutEmuSpeedDec     = "Minska Emuleringhastigheten";
    ls->shortcutShowEmuProp     = "Öppna Emuleringsfönstret";
    ls->shortcutShowVideoProp   = "Öppna Videofönstret";
    ls->shortcutShowAudioProp   = "Öppna Audiofönstret";
    ls->shortcutShowCtrlProp    = "Öppna Kontrollfönstret";
    ls->shortcutShowPerfProp    = "Öppna Prestandafönstret";
    ls->shortcutShowSettProp    = "Öppna Inställningsfönstret";
    ls->shortcutShowLanguage    = "Öppna Språkfönstret";
    ls->shortcutShowMachines    = "Öppna Konfigureringsverktyget";
    ls->shortcutShowShortcuts   = "Öppna Kortkommandoverktyget";
    ls->shortcutShowHelp        = "Öppna Hjälpfönstret";
    ls->shortcutShowAbout       = "Öppna \"Om blueMSX\"-fönstret";

    ls->shortcutSpecialMenu1    = "Visa Specialrom meny för Cartridge 1";
    ls->shortcutSpecialMenu2    = "Visa Specialrom meny för Cartridge 2";
    ls->shortcutVolumeStereo    = "Växla mellan mono/stereo";
    ls->shortcutThemeSwitch     = "Växla fönstretema";
    ls->shortcutToggleSpriteEnable = "Visa/Dölj Sprites";
    
    ls->shortcutShowApearProp   = "Öppna Utseenedefönstret";
    ls->menuPropsApearance      = "Utseende";
    ls->propThemeGB             = "Tema ";
    ls->propTheme               = "Tema";

    ls->propMonBrightness       = "Ljusstyrka:";
    ls->propMonContrast         = "Kontrast:";
    ls->propMonSaturation       = "Färgmättnad:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanlinjer:";

    ls->dlgRomType              = "Rom Typ:";
    ls->propOpenRomGB           = "Öppna Rom Dialog ";
    ls->propDefaultRomType      = "Default Rom Typ:";
    ls->propGuessRomType        = "Gissa Rom Typ";

    ls->propFile                = "Filer";
    ls->propSettDefSlotGB       = "Dra och Släpp ";
    ls->propSettDefSlots        = "Sätt in Rom i:";
    ls->propSettDefSlot         = " Slot";
    ls->propSettDefDrives       = "Sätt in Diskett i:";
    ls->propSettDefDrive        = " Drive";
    ls->menuPropsFile           = "Filer";
    ls->shortcutShowFiles       = "Öppna Filerfönstret";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "Sätt in Directory";
    ls->shortcutDiskDirInsertA  = "Sätt in Directory som Diskett A";
    ls->shortcutDiskDirInsertB  = "Sätt in Directory som Diskett B";
    ls->propMonDeInterlace      = " De-interlace";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "Slå om Pause Switch";
    ls->shortcutSizeMinimized   = "Minimera fönster";
    ls->shortcutEmuSpeedToggle  = "Växla Mellan Normal och Max Emuleringshastighet";
    ls->shortcutToggleCpuTrace  = "Slå på/av CPU trace";
  
    ls->enumVideoEmuMonitor     = "Monitor";

    ls->propEmuPauseSwitch      = " Pause Switch";
    ls->propVideoFreqText       = "Video Frekvens:";
    ls->propVideoFreqAuto       = "Automatisk";
    ls->propSndOversampleText   = "Översampling:";

    ls->confChipExtras          = "Extra";
    ls->confBoardGB             = "Board ";
    ls->confBoardText           = "Board Typ:";
    ls->confCpuFreqGB            = "CPU Frekvens ";
    ls->confZ80FreqText          = "Z80 Frekvens:";
    ls->confR800FreqText         = "R800 Frekvens:";
    ls->confFdcGB                = "Kontroller för Diskettenhet ";
    ls->confCFdcNumDrivesText    = "Antal Diskettenheter:";

    ls->propPriorityBoost        = " Höj prioriteten på blueMSX";
    
    // New entries in 2.1
    ls->propEmuFdcTiming        = "Slå Av Diskettstationstiming";
    ls->shortcutToggleFdcTiming = "Slå på/av Diskettstationstiming";

    // New entries in 2.2
    ls->menuCartHBI55           = "Sony HBI-55 Cartridge";
    ls->enumVideoEmuHq2x        = "Hq2x";
    ls->propMonColorGhosting    = "RF-Modulering";

    ls->keyconfigSelectedKey    = "Välj tangent:";
    ls->keyconfigMappedTo       = "Mappad till:";
    ls->keyconfigMappingScheme  = "Mapschema:";

    ls->warningDiscardChanges   = "Vill du stänga verktyget utan att spara dina ändringar?";

    ls->confSaveAsTitle         = "Spara Konfigurering Som...";

    ls->menuToolsKeyboard       = "Tangentbordseditor";
    ls->shortcutShowKeyboard    = "Visa Tangentbordseditor";

    ls->menuVideoSource         = "Videokälla";
    ls->menuVideoSourceDefault  = "Ingen videokälla inkopplad";
    ls->menuVideoChipAutodetect = "Automatisk detektering av video chip";
    ls->propFullscreenResText   = "Fullskärmsupplösning:";
    ls->dlgSavePreview          = "Förvisning";
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
    ls->propPortsOpenLogFile    = "Öppna Logfil";
    ls->propPortsEmulateMsxPrn  = "Emulering:";

    ls->shortcutPrnFormFeed     = "Form Feed på Skrivare";

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
    ls->confOpenRom             = "Öppna Rom fil";
    ls->fileAll                 = "Alla Filer";
    ls->fileCpuState            = "CPU-tillstand";
    ls->fileDisk                = "Diskettfil";
    ls->fileCas                 = "Kasettfil";

    ls->menuCartExternalRam     = "Externt RAM";

};

#endif

