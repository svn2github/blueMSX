/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageSwedish.h,v $
**
** $Revision: 1.23 $
**
** $Date: 2006-06-09 20:30:02 $
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

    ls->textDevice              = "Device:";
    ls->textFilename            = "Filenamn:";
    ls->textFile                = "Fil";
    ls->textNone                = "Ingen";
    ls->textUnknown             = "Ok�nd";


    //----------------------
    // Warning and Error lines
    //----------------------

    ls->warningTitle            = "blueMSX - Varning";
    ls->warningDiscardChanges   = "Vill du st�nga verktyget utan att spara dina �ndringar?";
    ls->warningOverwriteFile    = "Vill du skriva �ver filen:";
    ls->errorTitle              = "blueMSX - Fel";
    ls->errorEnterFullscreen    = "Misslyckades att byta till fullsk�rm.           \n";
    ls->errorDirectXFailed      = "Misslyckades att skapa DirectX objekt.          \nAnv�nder GDI ist�llet.\nKontrollera video inst�llningarna.";
    ls->errorNoRomInZip         = "Kunde inte hitta en .rom fil i zip arkivet.";
    ls->errorNoDskInZip         = "Kunde inte hitta en .dsk fil i zip arkivet.";
    ls->errorNoCasInZip         = "Kunde inte hitta en .cas fil i zip arkivet.";
    ls->errorNoHelp             = "Kunde inte hitta hj�lpfilen.";
    ls->errorStartEmu           = "Misslyckades att starta emulatorn.";
    ls->errorPortableReadonly   = "Flyttbar enhet �r inte skrivbar";


    //----------------------
    // File related lines
    //----------------------

    ls->fileRom                 = "Rom fil";
    ls->fileAll                 = "Alla Filer";
    ls->fileCpuState            = "CPU-tillstand";
    ls->fileDisk                = "Diskettfil";
    ls->fileCas                 = "Kasettfil";


    //----------------------
    // Menu related lines
    //----------------------

    ls->menuNoRecentFiles       = "- ingen filhistoria -";
    ls->menuInsert              = "S�tt in";
    ls->menuEject               = "Ta ur";

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
    ls->menuCartExternalRam     = "Externt RAM";

    ls->menuDiskInsertNew       = "S�tt in ny diskett fil";
    ls->menuDiskDirInsert       = "S�tt in mapp";
    ls->menuDiskAutoStart       = "Starta om efter ins�ttning/urdagning";
    ls->menuCartAutoReset       = "Starta om efter ins�ttning/urdagning";

    ls->menuCasRewindAfterInsert= "Spola tillbaka vid ins�ttning";
    ls->menuCasUseReadOnly      = "Till�t endast l�sning av kasett";
    ls->lmenuCasSaveAs          = "Spara kasett som...";
    ls->menuCasSetPosition      = "S�tt position";
    ls->menuCasRewind           = "Spola tillbaka";

    ls->menuPrnFormfeed         = "Form Feed";

    ls->menuZoomNormal          = "Normal storlek";
    ls->menuZoomDouble          = "Dubbel storlek";
    ls->menuZoomFullscreen      = "Helsk�rm";
    
    ls->menuPropsEmulation      = "Emulering";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Ljud";
    ls->menuPropsControls       = "Kontroller";
    ls->menuPropsPerformance    = "Prestanda";
    ls->menuPropsSettings       = "Inst�llningar";
    ls->menuPropsFile           = "Filer";
    ls->menuPropsLanguage       = "Spr�k";
    ls->menuPropsPorts          = "Portar";
    
    ls->menuVideoSource         = "Video ut k�lla";
    ls->menuVideoSourceDefault  = "Ingen videok�lla inkopplad";
    ls->menuVideoChipAutodetect = "Automatisk detektering av video chip";    
    ls->menuVideoInSource       = "Video ut k�lla";
    ls->menuVideoInBitmap       = "Bitmap fil";

    ls->menuHelpHelp            = "Hj�lp";
    ls->menuHelpAbout           = "Om blueMSX";

    ls->menuFileCart            = "Cartridge slot";
    ls->menuFileDisk            = "Diskettstaion";
    ls->menuFileCas             = "Kasett";
    ls->menuFilePrn             = "Skrivare";
    ls->menuFileLoadState       = "L�s in CPU-tillstand";
    ls->menuFileSaveState       = "Spara CPU-tillstand";
    ls->menuFileQLoadState      = "Snabbladda CPU-tillstand";
    ls->menuFileQSaveState      = "Snabbspara CPU-tillstand";
    ls->menuFileCaptureAudio    = "Spara ljud";
    ls->menuFileScreenShot      = "Spara sk�rmdump";
    ls->menuFileExit            = "Avsluta";

    ls->menuFileHarddisk        = "H�rddisk";
    ls->menuFileHarddiskNoPesent= "Inga enheter tillg�ngliga";

    ls->menuRunRun              = "K�r";
    ls->menuRunPause            = "Paus";
    ls->menuRunStop             = "Stanna";
    ls->menuRunSoftReset        = "Mjuk Omstart";
    ls->menuRunHardReset        = "H�rd Omstart";
    ls->menuRunCleanReset       = "Full Omstart";

    ls->menuToolsMachine        = "Konfigureringsverktyg";
    ls->menuToolsShortcuts      = "Kortkommando Verktyg";
    ls->menuToolsKeyboard       = "Tangentbordseditor";
    ls->menuToolsMixer          = "Mixer";

    ls->menuFile                = "Arkiv";
    ls->menuRun                 = "Emulering";
    ls->menuWindow              = "F�nster";
    ls->menuOptions             = "Egenskaper";
    ls->menuTools               = "Verktyg";
    ls->menuHelp                = "Hj�lp";
    

    //----------------------
    // Dialog related lines
    //----------------------

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "�ppna";
    ls->dlgCancel               = "Avbryt";
    ls->dlgSave                 = "Spara";
    ls->dlgSaveAs               = "Spara Som...";
    ls->dlgRun                  = "K�r";
    ls->dlgClose                = "St�ng";

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
    ls->dlgSaveCassette         = "blueMSX - Spara Kasett";
    ls->dlgInsertRom1           = "S�tt in ROM cartridge i slot 1";
    ls->dlgInsertRom2           = "S�tt in ROM cartridge i slot 2";
    ls->dlgInsertDiskA          = "S�tt in diskett i diskettstation A";
    ls->dlgInsertDiskB          = "S�tt in diskett i diskettstation B";
    ls->dlgInsertHarddisk       = "S�tt in h�rddisk";
    ls->dlgInsertCas            = "S�tt in kassettband";
    ls->dlgRomType              = "Rom Typ:";

    ls->dlgTapeTitle            = "blueMSX - Kassettposition";
    ls->dlgTapeFrameText        = "Kassettposition";
    ls->dlgTapeCurrentPos       = "Aktuell position";
    ls->dlgTapeTotalTime        = "Total l�ngd";
    ls->dlgTapeSetPosText       = "Kasettposition:";
    ls->dlgTapeCustom           = "Visa Specialfiler";
    ls->dlgTabPosition          = "Position";
    ls->dlgTabType              = "Typ";
    ls->dlgTabFilename          = "Filnamn";
    ls->dlgZipReset             = "Starta om efter ins�ttning";
    
    ls->dlgAboutTitle           = "blueMSX - Information";

    ls->dlgLangLangText         = "V�lj spr�k som blueMSX ska anv�nda";
    ls->dlgLangLangTitle        = "blueMSX - Spr�k";

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

    ls->dlgSavePreview          = "F�rvisning";
    ls->dlgSaveDate             = "Tid Sparad:";


    //----------------------
    // Properties related lines
    //----------------------

    ls->propTitle               = "blueMSX - Egenskaper";
    ls->propEmulation           = "Emulering";
    ls->propVideo               = "Video";
    ls->propSound               = "Ljud";
    ls->propControls            = "Kontroller";
    ls->propPerformance         = "Prestanda";
    ls->propSettings            = "Inst�llningar";
    ls->propFile                = "Filer";
    ls->propPorts               = "Portar";

    ls->propEmuGeneralGB        = "Allm�nt ";
    ls->propEmuFamilyText       = "MSX familj:";
    ls->propEmuMemoryGB         = "Minne ";
    ls->propEmuRamSizeText      = "RAM storlek:";
    ls->propEmuVramSizeText     = "VRAM storlek:";
    ls->propEmuSpeedGB          = "Emuleringshastighet ";
    ls->propEmuSpeedText        = "Emuleringshastighet:";
    ls->propEmuFrontSwitchGB    = "Panasonic Switchar ";
    ls->propEmuFrontSwitch      = " Front switch";
    ls->propEmuFdcTiming        = "Sl� Av Diskettstationstiming";
    ls->propEmuPauseSwitch      = " Paus switch";
    ls->propEmuAudioSwitch      = " MSX-AUDIO cartridge switch";
    ls->propVideoFreqText       = "Videofrekvens:";
    ls->propVideoFreqAuto       = "Automatisk";
    ls->propSndOversampleText   = "�versampling:";
    ls->propSndYkInGB           = "YK-01/YK-10/YK-20 In ";              // New in 2.5
    ls->propSndMidiInGB         = "MIDI In ";
    ls->propSndMidiOutGB        = "MIDI Ut ";
    ls->propSndMidiChannel      = "MIDI Channel:";                      // New in 2.5
    ls->propSndMidiAll          = "All";                                // New in 2.5

    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Monitor typ:";
    ls->propMonEmuText          = "Monitoremulering ";
    ls->propVideoTypeText       = "Videotyp:";
    ls->propWindowSizeText      = "F�nsterstorlek:";
    ls->propMonHorizStretch     = " Korrekt horizontell vidd";
    ls->propMonVertStretch      = " Vertikal stretch";
    ls->propMonDeInterlace      = " De-interlace";
    ls->propMonBrightness       = "Ljusstyrka:";
    ls->propMonContrast         = "Kontrast:";
    ls->propMonSaturation       = "F�rgm�ttnad:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanlinjer:";
    ls->propMonColorGhosting    = "RF-modulering";
    ls->propMonEffectsGB        = "Effekter ";

    ls->propPerfVideoDrvGB      = "Videodriver ";
    ls->propPerfVideoDispDrvText= "Sk�rmdriver:";
    ls->propPerfFrameSkipText   = "Frame skipping:";
    ls->propPerfAudioDrvGB      = "Lkuddriver ";
    ls->propPerfAudioDrvText    = "Ljuddriver:";
    ls->propPerfAudioBufSzText  = "Storlek p� ljudbuffer:";
    ls->propPerfEmuGB           = "Emulering ";
    ls->propPerfSyncModeText    = "Synkronisering:";
    ls->propFullscreenResText   = "Fullsk�rmsuppl�sning:";

    ls->propSndChipEmuGB        = "Emulering av ljudchip ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";
    ls->propSndMoonsound        = " Moonsound";
    ls->propSndMt32ToGm         = " Konvertera MT-32 instrument till General MIDI";

    ls->propPortsLptGB          = "Parallellport ";
    ls->propPortsComGB          = "Serieportar ";
    ls->propPortsLptText        = "Port:";
    ls->propPortsCom1Text       = "Port 1:";
    ls->propPortsNone           = "Ingen";
    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "Skriv till Fil";
    ls->propPortsComFile        = "Skicka till Fil";
    ls->propPortsOpenLogFile    = "�ppna Logfil";
    ls->propPortsEmulateMsxPrn  = "Emulering:";

    ls->propSetFileHistoryGB    = "Filhistoria ";
    ls->propSetFileHistorySize  = "Antal element i filhistorian:";
    ls->propSetFileHistoryClear = "Rensa historia";
    ls->propFileTypes           = " Registrera filtyper med blueMSX (.rom, .dsk, .cas, .sta)";
    ls->propWindowsEnvGB        = "Windows Milj� ";
    ls->propSetScreenSaver      = " Deaktivera sk�rmsl�ckare n�r blueMSX k�r";
    ls->propDisableWinKeys      = " Avaktivera WIndows menyer n�r emulatorn k�r";
    ls->propPriorityBoost       = " H�j prioriteten p� blueMSX";
    ls->propScreenshotPng       = " Anv�nd Portable Network Graphics (.png) sk�rmdump";
    ls->propClearHistory        = "Vill du verkligen radera filhistorien ?";
    ls->propOpenRomGB           = "�ppna Rom Dialog ";
    ls->propDefaultRomType      = "Default Rom Typ:";
    ls->propGuessRomType        = "Gissa Rom Typ";

    ls->propSettDefSlotGB       = "Dra och Sl�pp ";
    ls->propSettDefSlots        = "S�tt in Rom i:";
    ls->propSettDefSlot         = " Slot";
    ls->propSettDefDrives       = "S�tt in Diskett i:";
    ls->propSettDefDrive        = " Drive";

    ls->propThemeGB             = "Tema ";
    ls->propTheme               = "Tema";


    //----------------------
    // Dropdown related lines
    //----------------------

    ls->enumVideoMonColor       = "F�rg";
    ls->enumVideoMonGrey        = "Svartvit";
    ls->enumVideoMonGreen       = "Gr�n";
    ls->enumVideoMonAmber       = "Orange";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Ingen";
    ls->enumVideoEmuYc          = "Y/C kabel (skarp)";
    ls->enumVideoEmuMonitor     = "Monitor";
    ls->enumVideoEmuYcBlur      = "Brusig Y/C kabel (skarp)";
    ls->enumVideoEmuComp        = "Kompositkabel (suddig)";
    ls->enumVideoEmuCompBlur    = "Brusig komposit (suddig)";
    ls->enumVideoEmuScale2x     = "Scale 2x";
    ls->enumVideoEmuHq2x        = "Hq2x";

    ls->enumVideoSize1x         = "Normal - 320x200";
    ls->enumVideoSize2x         = "Dubbel - 640x400";
    ls->enumVideoSizeFullscreen = "Helsk�rm";

    ls->enumVideoDrvDirectDrawHW= "DirectDraw HW accel.";
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

    ls->enumEmuSync1ms          = "Synkronisera till MSX refresh";
    ls->enumEmuSyncVblank       = "Synkronisera till PC Vertikal Blank";
    ls->enumEmuAsyncVblank      = "Asynchronous PC Vblank";             // New in 2.5
    ls->enumEmuSyncNone         = "Ingen";
    ls->enumEmuSyncAuto         = "Automatisk (snabb)";

    ls->enumControlsJoyNone     = "Ingen";
    ls->enumControlsJoyMouse    = "Mus";
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 dosa";
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey dosa";
    ls->enumControlsJoy2Button = "2-button Joystick";                   // New in 2.5
    ls->enumControlsJoyLightGun = "Light Gun";                          // New in 2.5
    ls->enumControlsJoyColeco = "ColecoVision Joystick";                // New in 2.5


    //----------------------
    // Configuration related lines
    //----------------------

    ls->confTitle               = "blueMSX - Konfigureringsverktyg";
    ls->confConfigText          = "Konfigurering:";
    ls->confSlotLayout          = "Slot mappning";
    ls->confMemory              = "Minne";
    ls->confChipEmulation       = "Chipemulering";
    ls->confChipExtras          = "Extra";

    ls->confOpenRom             = "�ppna Rom fil";
    ls->confSaveTitle           = "blueMSX - Spara Konfigurering";
    ls->confSaveText            = "Vill du skriva �ver maskinkonfigureringen? :";
    ls->confSaveAsTitle         = "Spara Konfigurering Som...";
    ls->confSaveAsMachineName   = "Maskinnamn:";
    ls->confDiscardTitle        = "blueMSX - Konfigurering";
    ls->confExitSaveTitle       = "blueMSX - Avsluta Konfigureringsverktyg";
    ls->confExitSaveText        = "Vill du stanga konfigureringsverktyget utan att spara dina �ndringar?";

    ls->confSlotLayoutGB        = "Slot Layout ";
    ls->confSlotExtSlotGB       = "Externa slots ";
    ls->confBoardGB             = "Board ";
    ls->confBoardText           = "Board Typ:";
    ls->confSlotPrimary         = "Prim�r";
    ls->confSlotExpanded        = "Expanderad (4 subslottar)";

    ls->confSlotCart            = "Cartridge:";
    ls->confSlot                = "Slot";
    ls->confSubslot             = "Subslot";

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

    ls->confCmosGB               = "CMOS ";
    ls->confCmosEnable           = " Anv�nd CMOS";
    ls->confCmosBattery          = " Anv�nd Laddat Batteri";

    ls->confCpuFreqGB            = "CPU Frekvens ";
    ls->confZ80FreqText          = "Z80 Frekvens:";
    ls->confR800FreqText         = "R800 Frekvens:";
    ls->confFdcGB                = "Kontroller f�r Diskettenhet ";
    ls->confCFdcNumDrivesText    = "Antal Diskettenheter:";

    ls->confEditMemTitle         = "blueMSX - �ndra Minnesmap";
    ls->confEditMemGB            = "Detailjer ";
    ls->confEditMemType          = "Typ:";
    ls->confEditMemFile          = "Fil:";
    ls->confEditMemAddress       = "Adress";
    ls->confEditMemSize          = "Storlek";
    ls->confEditMemSlot          = "Slot";


    //----------------------
    // Shortcut lines
    //----------------------

    ls->shortcutKey             = "Tangentkombination";
    ls->shortcutDescription     = "Kortkommando";

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
    ls->shortcutSpecialMenu1    = "Visa Specialrom meny f�r Cartridge 1";
    ls->shortcutSpecialMenu2    = "Visa Specialrom meny f�r Cartridge 2";
    ls->shortcutCartAutoReset   = "Starta om efter Ins�ttning av Cartridge";
    ls->shortcutDiskInsertA     = "S�tt in Diskett A";
    ls->shortcutDiskDirInsertA  = "S�tt in Directory som Diskett A";
    ls->shortcutDiskRemoveA     = "Ta ur Diskett A";
    ls->shortcutDiskChangeA     = "Snabbbyt Diskett A";
    ls->shortcutDiskAutoResetA  = "Starta om efter Ins�ttning av Diskett";
    ls->shortcutDiskInsertB     = "S�tt in Diskett B";
    ls->shortcutDiskDirInsertB  = "S�tt in Directory som Diskett B";
    ls->shortcutDiskRemoveB     = "Ta ur Diskett B";
    ls->shortcutCasInsert       = "S�tt in Kasett";
    ls->shortcutCasEject        = "Ta ur Kasett";
    ls->shortcutCasAutorewind   = "Sl� Av/P� Automatisk Tillbakaspolning";
    ls->shortcutCasReadOnly     = "Sl� Av/P� Skrivskydd p� Kasettfiler";
    ls->shortcutCasSetPosition  = "S�tt Kasettposition";
    ls->shortcutCasRewind       = "Spola Tillabaka Kasett";
    ls->shortcutCasSave         = "Spara Kasett till fil";
    ls->shortcutPrnFormFeed     = "Form Feed p� Skrivare";
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
    ls->shortcutSizeMinimized   = "Minimera f�nster";
    ls->shortcutToggleFullscren = "V�xla till/fr�n Fullsk�rm";
    ls->shortcutVolumeIncrease  = "�ka Volymen";
    ls->shortcutVolumeDecrease  = "Minska Volymen";
    ls->shortcutVolumeMute      = "St�ng av Volymen";
    ls->shortcutVolumeStereo    = "V�xla mellan mono/stereo";
    ls->shortcutSwitchMsxAudio  = "Sl� om MSX-AUDIO Switch";
    ls->shortcutSwitchFront     = "Sl� om Panasonic Front Switch";
    ls->shortcutSwitchPause     = "Sl� om Pause Switch";
    ls->shortcutToggleMouseLock = "Sl� om Musl�s";
    ls->shortcutEmuSpeedMax     = "Maximal Emuleringshastighet";
    ls->shortcutEmuSpeedToggle  = "V�xla Mellan Normal och Max Emuleringshastighet";
    ls->shortcutEmuSpeedNormal  = "Minska Emuleringhastigheten";
    ls->shortcutEmuSpeedInc     = "�ka Emuleringhastigheten";
    ls->shortcutEmuSpeedDec     = "Minska Emuleringhastigheten";
    ls->shortcutThemeSwitch     = "V�xla f�nstretema";
    ls->shortcutShowEmuProp     = "�ppna Emuleringsf�nstret";
    ls->shortcutShowVideoProp   = "�ppna Videof�nstret";
    ls->shortcutShowAudioProp   = "�ppna Audiof�nstret";
    ls->shortcutShowCtrlProp    = "�ppna Kontrollf�nstret";
    ls->shortcutShowPerfProp    = "�ppna Prestandaf�nstret";
    ls->shortcutShowSettProp    = "�ppna Inst�llningsf�nstret";
    ls->shortcutShowPorts       = "Visa Portegenskaper";
    ls->shortcutShowLanguage    = "�ppna Spr�kf�nstret";
    ls->shortcutShowMachines    = "�ppna Konfigureringsverktyget";
    ls->shortcutShowShortcuts   = "�ppna Kortkommandoverktyget";
    ls->shortcutShowKeyboard    = "Visa Tangentbordseditor";
    ls->shortcutShowDebugger    = "Visa Debugger";
    ls->shortcutShowTrainer     = "Visa Trainer";
    ls->shortcutShowMixer       = "Visa Mixer";
    ls->shortcutShowHelp        = "�ppna Hj�lpf�nstret";
    ls->shortcutShowAbout       = "�ppna \"Om blueMSX\"-f�nstret";
    ls->shortcutShowFiles       = "�ppna Filerf�nstret";
    ls->shortcutToggleSpriteEnable = "Visa/D�lj Sprites";
    ls->shortcutToggleFdcTiming = "Sl� p�/av Diskettstationstiming";
    ls->shortcutToggleCpuTrace  = "Sl� p�/av CPU trace";


    //----------------------
    // Keyboard config lines
    //----------------------

    ls->keyconfigSelectedKey    = "V�lj tangent:";
    ls->keyconfigMappedTo       = "Mappad till:";
    ls->keyconfigMappingScheme  = "Mapschema:";
};

#endif
