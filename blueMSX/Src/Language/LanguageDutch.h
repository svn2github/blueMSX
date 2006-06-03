/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageDutch.h,v $
**
** $Revision: 1.16 $
**
** $Date: 2006-06-03 20:38:43 $
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
#ifndef LANGUAGE_DUTCH_H
#define LANGUAGE_DUTCH_H

#include "LanguageStrings.h"

void langInitDutch(LanguageStrings* ls)
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

    ls->menuNoRecentFiles       = "- geen recente bestanden -";
    ls->menuInsert              = "Toevoegen";
    ls->menuEject               = "Eruit halen";

    ls->menuCartAutoReset       = "Herstart na toevoegen/verwijderen";
    ls->menuCartFMPac           = "FM-PAC Cartridge";
    ls->menuCartPac             = "PAC Cartridge";
    
    ls->menuDiskAutoStart       = "Herstart na toevoegen";

    ls->menuCasSetPosition      = "Bepaal positie";
    ls->menuCasRewind           = "Spoel terug";

    ls->menuZoomNormal          = "Normale grootte";
    ls->menuZoomDouble          = "Dubbele grootte";
    ls->menuZoomFullscreen      = "Volledig scherm";

    ls->menuPropsEmulation      = "Emulatie";
    ls->menuPropsVideo          = "Beeld";
    ls->menuPropsSound          = "Geluid";
    ls->menuPropsControls       = "Besturing";
    ls->menuPropsPerformance    = "Prestatie";
    ls->menuPropsLanguage       = "Taal";

    ls->menuHelpHelp            = "Help";
    ls->menuHelpAbout           = "Info blueMSX";

    ls->menuFileCart            = "Cartridge slot";
    ls->menuFileDisk            = "Diskette station";
    ls->menuFileCas             = "Cassette";
    ls->menuFileLoadState       = "Laad CPU status";
    ls->menuFileSaveState       = "Opslaan CPU status";
    ls->menuFileQLoadState      = "Snel laden status";
    ls->menuFileQSaveState      = "Snel opslaan status";
    ls->menuFileCaptureAudio    = "Opslaan Geluid";
    ls->menuFileScreenShot      = "Schermafdruk maken";
    ls->menuFileExit            = "Afsluiten";

    ls->menuRunRun              = "Start";
    ls->menuRunPause            = "Pauze";
    ls->menuRunStop             = "Stop";
    ls->menuRunSoftReset        = "Zachte Herstart";
    ls->menuRunHardReset        = "Harde Herstart";
    ls->menuRunCleanReset       = "Algemene Herstart";

    ls->menuFile                = "Bestand";
    ls->menuRun                 = "Start";
    ls->menuWindow              = "Scherm";
    ls->menuOptions             = "Opties";
    ls->menuHelp                = "Help";

    ls->errorTitle              = "blueMSX - Fout";
    ls->errorEnterFullscreen    = "Het is niet gelukt om over te schakelen naar de volledige schermmodus.          \n";
    ls->errorDirectXFailed      = "Het is niet gelukt om DirectX te initializeren. \nDe GDI wordt nu gebruikt.\nKijk de video instellingen na..";
    

    ls->errorNoRomInZip         = "Er zijn geen .rom bestanden gevonden in het zip bestand.";
    ls->errorNoDskInZip         = "Er zijn geen .dsk bestanden gevonden in het zip bestand.";
    ls->errorNoCasInZip         = "Er zijn geen .cas bestanden gevonden in het zip bestand.";
    ls->errorNoHelp             = "Het blueMSX help bestand is niet gevonden.";
    ls->errorStartEmu           = "Het is niet gelukt om de MSX emulator te starten.";


    ls->dlgLoadRom              = "blueMSX - Selecteer een rom om te laden";
    ls->dlgLoadDsk              = "blueMSX - Selecteer een dsk om te laden";
    ls->dlgLoadCas              = "blueMSX - Selecteer een cas om te laden";
    ls->dlgLoadRomDskCas        = "blueMSX - Selecteer een rom, dsk, of cas bestand om te laden";
    ls->dlgLoadRomDesc          = "Selecteer een rom om te laden:";
    ls->dlgLoadDskDesc          = "Selecteer een diskette om te laden:";
    ls->dlgLoadCasDesc          = "Selecteer een tape om te laden:";
    ls->dlgLoadRomDskCasDesc    = "Selecteer een rom, diskette, of tape om te laden:";
    ls->dlgLoadState            = "Laad CPU status";
    ls->dlgSaveState            = "Opslaan CPU status";
    ls->dlgInsertRom1           = "Stop ROM cartridge in slot 1";
    ls->dlgInsertRom2           = "Stop ROM cartridge in slot 2";
    ls->dlgInsertDiskA          = "Stop diskette image in drive A";
    ls->dlgInsertDiskB          = "Stop diskette image in drive B";
    ls->dlgInsertCas            = "Stop tape in casette speler";

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Openen";
    ls->dlgCancel               = "Annuleren";

    ls->dlgTapeTitle            = "blueMSX - Tape positie";
    ls->dlgTapeFrameText        = "Tape Positie";
    ls->dlgTapeCurrentPos       = "Huidige positie";
    ls->dlgTapeTotalTime        = "Totale tijd";

    ls->dlgZipReset             = "Herstart na toevoegen";

    ls->dlgAboutTitle           = "blueMSX - Info";

    ls->dlgLangLangText         = "Kies de taal die blueMSX moet gebruiken";
    ls->dlgLangLangTitle        = "blueMSX - Taal";

    ls->propTitle               = "blueMSX - Eigenschappen";
    ls->propEmulation           = "Emulatie";
    ls->propVideo               = "Beeld";
    ls->propSound               = "Geluid";
    ls->propControls            = "Besturing";
    ls->propPerformance         = "Prestaties";

    ls->propEmuGeneralGB        = "Algemeen ";
    ls->propEmuFamilyText       = "MSX familie:";
    ls->propEmuMemoryGB         = "Geheugen ";
    ls->propEmuRamSizeText      = "RAM grootte:";
    ls->propEmuVramSizeText     = "VRAM grootte:";
    ls->propEmuSpeedGB          = "Emulatie Snelheid ";
    ls->propEmuSpeedText        = "Emulatie Snelheid:";

    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Monitor type:";
    ls->propMonEmuText          = "Monitor emulatie:";
    ls->propVideoYypeText       = "Beeld type:";
    ls->propWindowSizeText      = "Scherm grootte:";

    ls->propPerfVideoDrvGB      = "Beeld instellingen ";
    ls->propPerfVideoDispDrvText= "Beeld stuurprogramma:";
    ls->propPerfFrameSkipText   = "Frames overslaan:";
    ls->propPerfAudioDrvGB      = "Geluid instellingen ";
    ls->propPerfAudioDrvText    = "Geluid stuurprogramma:";
    ls->propPerfAudioBufSzText  = "Geluid buffer grootte:";
    ls->propPerfEmuGB           = "Emulatie ";
    ls->propPerfSyncModeText    = "Synchronisatie mode";

    ls->propSndChipEmuGB        = "Geluid Chip Emulatie ";
    ls->propSndMixerGB          = "Audio Mixer ";
    ls->propSndMonoText         = "mono";
    ls->propSndStereoText       = "stereo";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "MASTER";

    ls->enumVideoMonColor       = "Kleur";
    ls->enumVideoMonGrey        = "Zwart-Wit";
    ls->enumVideoMonGreen       = "Groen";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Geen";
    ls->enumVideoEmuYc          = "Y/C kabel (Scherp)";
    ls->enumVideoEmuYcBlur      = "Ruis Y/C kabel (Scherp)";
    ls->enumVideoEmuComp        = "Compositie (Wazig)";
    ls->enumVideoEmuCompBlur    = "Ruis Compositie (Wazig)";
    ls->enumVideoEmuScale2x     = "Schaal 2x";

    ls->enumVideoSize1x         = "Normaal - 320x200";
    ls->enumVideoSize2x         = "Dubbel - 640x400";
    ls->enumVideoSizeFullscreen = "Volledig Scherm";

    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "geen";
    ls->enumVideoFrameskip1     = "1 frame";
    ls->enumVideoFrameskip2     = "2 frames";
    ls->enumVideoFrameskip3     = "3 frames";
    ls->enumVideoFrameskip4     = "4 frames";
    ls->enumVideoFrameskip5     = "5 frames";

    ls->enumSoundDrvNone        = "Geen Geluid";
    ls->enumSoundDrvWMM         = "WMM stuurprogramma";
    ls->enumSoundDrvDirectX     = "DirectX stuurprogramma";

    ls->enumEmuSync1ms          = "1ms (beste)";
    ls->enumEmuSyncAuto         = "Automatisch (snel)";

    ls->enumControlsJoyNone     = "geen";
    ls->enumControlsJoyMouse    = "Muis";

    ls->dlgAboutAbout           = "Info\r\n====";
    ls->dlgAboutVersion         = "Versie:";
    ls->dlgAboutBuildNumber     = "Gemaakt:";
    ls->dlgAboutBuildDate       = "Datum:";
    ls->dlgAboutCreat           = "Gemaakt door Daniel Vik";
    ls->dlgAboutLisence         = "LICENTIE\r\n"
                                  "======\r\n\r\n"
                                  "Deze software wordt gegeven 'as-is', zonder enige vorm van garantie. "
                                  "De auteur(s) is/zijn niet verantwoordelijk voor elke vorm van schade "
                                  "die onstaat door het gebruik van deze software.\r\n\r\n"
                                  "Bezoek www.bluemsx.com voor meer details.";


    ls->dlgAboutDevel           = "GEMAAKT DOOR\r\n========";
    ls->dlgAboutThanks          = "MET DANK AAN\r\n============";

    // New entries
    ls->menuTools                = "Extra";
    ls->menuToolsMachine         = "Aanpassen Machine";
    ls->menuPropsSettings        = "Instellingen";
    ls->menuCasRewindAfterInsert = "Terugspoelen na inname";
    ls->menuCasUseReadOnly       = "Gebruik Cassette Beeld als Alleen Lezen";
    ls->lmenuCasSaveAs           = "Sla Cassette Beeld op als...";

    ls->dlgSaveCassette          = "blueMSX - Sla Tape Beeld op";
    ls->dlgTapeCustom            = "Laat Speciale Bestanden zien";
    ls->dlgTapeSetPosText        = "Tape Positie:";
    ls->dlgTabPosition           = "Positie";
    ls->dlgTabType               = "Type";
    ls->dlgTabFilename           = "Bestandsnaam";

    ls->propSettings             = "Instellingen";

    ls->propSetFileHistoryGB     = "Bestand Geschiedenis ";
    ls->propSetFileHistorySize   = "Aantal bestanden in geschiedenis:";
    ls->propSetFileHistoryClear  = "Leegmaken Geschiedenis";
    ls->propSetScreenSaver       = "Scherm Beveiliging uitschakelen als blueMSX draait";
    ls->confTitle                = "blueMSX - Machine configuratie aanpassen";
    ls->confSave                 = "Opslaan";
    ls->confSaveAs               = "Opslaan als...";
    ls->confRun                  = "Start";
    ls->confClose                = "Afsluiten";
    ls->confConfigText           = "Configuratie";
    ls->confSlotLayout           = "Slot instellingen";
    ls->confMemory               = "Geheugen";
    ls->confChipEmulation        = "Chip Emulatie";

    ls->confSlotLayoutGB         = "Slot instellingen ";
    ls->confSlotExtSlotGB        = "Externe Slots ";
    ls->confSlotCart             = "Cartridge";
    ls->confSlotPrimary          = "Primair";
    ls->confSlotExpanded         = "Uitgebreid (vier sub-slots)";

    ls->confMemAdd               = "Toevoegen...";
    ls->confMemEdit              = "Aanpassen...";
    ls->confMemRemove            = "Verwijderen";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Adres";
    ls->confMemType              = "Type";
    ls->confMemRomImage          = "Rom Beeld";

    ls->confChipVideoGB          = "Beeld ";
    ls->confChipVideoChip        = "Beeld Chip:";
    ls->confChipVideoRam         = "Beeld RAM:";
    ls->confChipSoundGB          = "Geluid ";

    ls->confSaveTitle            = "blueMSX - Machine configuratie opslaan";
    ls->confSaveText             = "Deze machine configuratie vervangen? :";

    ls->confEditMemTitle         = "blueMSX - Aanpassen Mapper";
    ls->confEditMemGB            = "Mapper Details ";
    ls->confEditMemType          = "Type:";
    ls->confEditMemFile          = "Bestand:";
    ls->confEditMemAddress       = "Address";
    ls->confEditMemSize          = "Grootte";
    ls->confEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Configuratie";
    ls->confExitSaveTitle        = "blueMSX - Machine configuratie afsluiten";
    ls->confExitSaveText         = "De gemaakte wijzigingen in de huidige configuratie worden niet opgeslagen. Wilt u doorgaan?";

    ls->confSaveAsMachineTitle   = "blueMSX - Machine configuratie opslaan als...";
    ls->confSaveAsMachineName    = "Machine Naam:";

    ls->propSndMoonsound         = " Moonsound";

    ls->propWindowsEnvGB         = "Windows Omgeving";

    ls->propFileTypes            = " Bestanden registreren bij blueMSX (.rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " Automatische MSX functie voor Windows menu toetsen";


    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW accel.";
    ls->propMonHorizStretch      = " Horizontaal uitrekken";

    ls->propClearHistory         = "Weet u zeker dat u de bestandsgeschiedenis wilt wissen?";

    ls->propEmuFrontSwitchGB     = "Panasonic Switches ";
    ls->propEmuFrontSwitch       = " Front Switch";
    ls->propEmuAudioSwitch       = " MSX-AUDIO cartridge switch";
    ls->propMonVertStretch       = " Verticaal uitrekken";

    ls->confCmosGB                = "CMOS ";
    ls->confCmosEnable            = " Aanzetten CMOS";
    ls->confCmosBattery           = " Gebruiken Geladen Batterij";

    ls->menuCartSCCPlus          = "SCC+ Cartridge";
    ls->menuCartSCC              = "SCC Cartridge";
    
    ls->warningTitle             = "blueMSX - Waarschuwing";


    // New entries in 1.5.1
    ls->menuToolsShortcuts      = "Maken Snelkoppeling";

    ls->shortcutSaveConfig      = "blueMSX -  Configuratie opslaan";
    ls->shortcutOverwriteConfig = "Huidige configuratie overschrijven?:";
    ls->shortcutExitConfig      = "blueMSX -  Snelkoppeling configuratie afsluiten";

    ls->shortcutDiscardConfig   = "Weet u zeker dat u de gemaakte wijzigingen in de huidige configuratie niet wilt toepassen?";

    ls->shortcutSaveConfigAs    = "blueMSX - Configuratie opslaan als...";
    ls->shortcutConfigName      = "Configuratie Naam:";
    ls->shortcutNewProfile      = "< Nieuw Profiel >";
    ls->shortcutConfigTitle     = "blueMSX - Snelkoppeling Toewijzingen";
    ls->shortcutAssign          = "Toewijzen";
    ls->shortcutPressText       = "Druk op Snelkoppeling toets(en):";
    ls->shortcutScheme          = "Schema:";

    ls->shortcutCartInsert1     = "Toevoegen Cartridge in Slot 1";
    ls->shortcutCartRemove1     = "Verwijder Cartridge uit Slot 1";
    ls->shortcutCartInsert2     = "Toevoegen Cartridge in Slot 2";
    ls->shortcutCartRemove2     = "Verwijder Cartridge uit Slot 2";

    ls->shortcutCartAutoReset   = "Herstart na toevoegen cartridge";
    ls->shortcutDiskInsertA     = "Toevoegen Diskette in Drive A";
    ls->shortcutDiskRemoveA     = "Verwijder Diskette uit drive A";
    ls->shortcutDiskChangeA     = "Snel veranderen van diskette in drive A";
    ls->shortcutDiskAutoResetA  = "Herstart na toevoegen diskette in drive A";
    ls->shortcutDiskInsertB     = "Toevoegen Diskette in Drive B";
    ls->shortcutDiskRemoveB     = "Verwijder Diskette uit Drive B";
    ls->shortcutCasInsert       = "Toevoegen Cassette";
    ls->shortcutCasEject        = "Verwijder Cassette";
    ls->shortcutCasAutorewind   = "Automatisch cassette terugspoelen ja/nee";
    ls->shortcutCasReadOnly     = "Aleen lezen cassette beeld ja/nee";
    ls->shortcutCasSetPosition  = "Bepalen Cassette Positie";
    ls->shortcutCasRewind       = "Terugspoelen Cassette";
    ls->shortcutCasSave         = "Opslaan Cassette Beeld";
    ls->shortcutCpuStateLoad    = "Laden CPU status";
    ls->shortcutCpuStateSave    = "Opslaan CPU status";
    ls->shortcutCpuStateQload   = "Snel laden CPU status";
    ls->shortcutCpuStateQsave   = "Snel opslaan CPU status";
    ls->shortcutAudioCapture    = "Start/stop het audio opslaan";
    ls->shortcutScreenshotOrig  = "Opslaan screenshot";
    ls->shortcutScreenshotSmall = "Opslaan klein ongefilterde screenshot";
    ls->shortcutScreenshotLarge = "Opslaan groot ongefilterde screenshot";
    ls->shortcutQuit            = "Exit blueMSX";
    ls->shortcutRunPause        = "Starten/Pauseren emulatie";
    ls->shortcutStop            = "Stoppen emulatie";
    ls->shortcutResetHard       = "Harde Herstart";
    ls->shortcutResetSoft       = "Zachte Herstart";
    ls->shortcutResetClean      = "Algemene Herstart";
    ls->shortcutSizeSmall       = "Kiezen normale grootte voor het scherm";
    ls->shortcutSizeNormal      = "Kiezen dubbele grootte voor het scherm";
    ls->shortcutSizeFullscreen  = "Kiezen volledig scherm";
    ls->shortcutToggleFullscren = "Kiezen volledig scherm of onvolledig scherm";
    ls->shortcutVolumeIncrease  = "Geluidsterkte verhogen";
    ls->shortcutVolumeDecrease  = "Geluidsterkte verminderen";
    ls->shortcutVolumeMute      = "Geluid uitzetten";
    ls->shortcutSwitchMsxAudio  = "MSX-AUDIO switch aan/uit";
    ls->shortcutSwitchFront     = "Panasonic front switch aan/uit";
    ls->shortcutToggleMouseLock = "Muis vastzetten aan/uit";
    ls->shortcutEmuSpeedMax     = "Maximale emulatie snelheid";
    ls->shortcutEmuSpeedNormal  = "Normale emulatie snelheid";
    ls->shortcutEmuSpeedInc     = "Verhoog emulatie snelheid";
    ls->shortcutEmuSpeedDec     = "Verlaag emulatie snelheid";
    ls->shortcutShowEmuProp     = "Dialoog: Emulatie eigenschappen";
    ls->shortcutShowVideoProp   = "Dialoog: Beeld";
    ls->shortcutShowAudioProp   = "Dialoog: Geluid";
    ls->shortcutShowCtrlProp    = "Dialoog: Besturing";
    ls->shortcutShowPerfProp    = "Dialoog: Prestatie";
    ls->shortcutShowSettProp    = "Dialoog: Instellingen";
    ls->shortcutShowLanguage    = "Dialoog: Taaldialoog";
    ls->shortcutShowMachines    = "Dialoog: Machine menu";
    ls->shortcutShowShortcuts   = "Dialoog: Snelkoppelingen menu";
    ls->shortcutShowHelp        = "Dialoog: Hulpdialoog";
    ls->shortcutShowAbout       = "Dialoog: Info blueMSX";

    ls->shortcutSpecialMenu1    = "Dialoog: Speciaal menu voor ROM cartridge in slot 1";
    ls->shortcutSpecialMenu2    = "Dialoog: Speciaal menu voor ROM cartridge in slot 2";
    ls->shortcutVolumeStereo    = "Wisselen mono of stereo mode";
    ls->shortcutThemeSwitch     = "Ander thema kiezen";

    ls->shortcutToggleSpriteEnable = "Tonen/Verbergen sprites";

    ls->shortcutShowApearProp   = "Uiterlijke eigenschappen weergeven";
    ls->menuPropsApearance      = "Uiterlijk";
    ls->propApearance           = "Uiterlijk";
    ls->propThemeGB             = "Thema ";
    ls->propTheme               = "Thema";

    ls->propMonBrightness       = "Helderheid:";
    ls->propMonContrast         = "Contrast:";
    ls->propMonSaturation       = "Verzadiging:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Beeldlijnen:";

    ls->dlgRomType              = "Rom type :";
    ls->propOpenRomGB           = "Openen Rom bestand";
    ls->propDefaultRomType      = "Standaard type:";
    ls->propGuessRomType        = "Raden type";

    ls->propFile                = "Bestand";
    ls->propSettDefSlotGB       = "Slepen en neerzetten ";
    ls->propSettDefSlots        = "Toevoegen cartridge in:";
    ls->propSettDefSlot         = " Slot";
    ls->propSettDefDrives       = "Toevoegen diskette in:";
    ls->propSettDefDrive        = " Drive";
    ls->menuPropsFile           = "Bestand";
    ls->shortcutShowFiles       = "Tonen van bestandseigenschappen";

    // New entries in 1.6.1
    
    ls->menuDiskDirInsert       = "Insert Directory";
    
    ls->shortcutDiskDirInsertA  = "Insert Directory as Diskette A";
    ls->shortcutDiskDirInsertB  = "Insert Directory as Diskette B";
    ls->propMonDeInterlace      = " De-interlace";
    
    // New entries in 2.0
    ls->shortcutSwitchPause     = "Pause switch aan/uit"; 
    ls->shortcutSizeMinimized   = "Minimaliseer scherm"; 
    ls->shortcutEmuSpeedToggle  = "Maximum snelheid van de emulatie aan/uit"; 
    ls->shortcutToggleCpuTrace  = "Toelaten/niet toelaten CPU spoor"; 

    ls->enumVideoEmuMonitor     = "Monitor"; 

    ls->propEmuPauseSwitch      = " Pause Switch"; 
    ls->propVideoFreqText       = "Video frequentie:"; 
    ls->propVideoFreqAuto       = "Auto"; 
    ls->propSndOversampleText   = "Oversample:"; 

    ls->confChipExtras          = "Extras"; 
    ls->confBoardGB             = "Systeem "; 
    ls->confBoardText           = "Systeem Type:"; 
    ls->confCpuFreqGB            = "CPU frequentie "; 
    ls->confZ80FreqText          = "Z80 frequentie:"; 
    ls->confR800FreqText         = "R800 Frequentie:"; 
    ls->confFdcGB                = "Floppy Disk Controller "; 
    ls->confCFdcNumDrivesText    = "Aantal drives:"; 

    ls->propPriorityBoost       = " blueMSX een hogere prioriteit geven";

    // New entries in 2.1
    
    ls->propEmuFdcTiming        = "Diskette station niet synchroniseren"; 

    ls->shortcutToggleFdcTiming = "Synchroniseren/Niet synchroniseren"; 
    
    // New entries in 2.2
    ls->menuCartHBI55           = "Sony HBI-55 Cartridge"; 
    ls->propSndPcm              = " Turbo-R PCM"; 
    ls->propSndAY8910           = " AY8910 PSG"; 
    ls->propSndSN76489          = " SN76489 PSG"; 
    ls->enumVideoEmuHq2x        = "Hq2x"; 
    ls->propMonColorGhosting    = "RF-Modulator"; 

    ls->keyconfigSelectedKey    = "Geselecteerde toets:"; 
    ls->keyconfigMappedTo       = "Gekoppeld aan:"; 
    ls->keyconfigMappingScheme  = "Koppel Schema:"; 

    ls->warningDiscardChanges   = "Wilt u de wijzigingen ongedaan maken?"; 

    ls->confSaveAsTitle         = "Configuratie opslaan als..."; 
    ls->confSaveAsName          = "Naam:"; 

    ls->menuToolsKeyboard       = "Toetsenbord Editor"; 
    ls->shortcutShowKeyboard    = "Toetsenbord editor weergeven"; 

    ls->menuVideoSource         = "Video bron"; 
    ls->menuVideoSourceDefault  = "Geen Video bron geselecteerd"; 
    ls->menuVideoChipAutodetect = "Automatisch detecteren van Video Chip"; 
    ls->propFullscreenResText   = "Resolutie voor volledige schermmodus:"; 
    ls->dlgSavePreview          = "Voorbeeld weergeven"; 
    ls->dlgSaveDate             = "Opgeslagen op:"; 

    ls->enumVideoMonAmber       = "Amber"; 

    ls->menuPropsPorts          = "Poorten"; 
    ls->propPortsLptGB          = "Parallele poort "; 
    ls->propPortsComGB          = "Seriele poorten "; 
    ls->propPortsLptText        = "Poort:"; 
    ls->propPortsCom1Text       = "Poort 1:";

    ls->shortcutShowDebugger    = "Debugger weergeven"; 
    ls->shortcutShowTrainer     = "Trainer weergeven"; 
    ls->shortcutShowPorts       = "Eigenschappen van poorten weergeven";
    
    ls->propPorts               = "Poorten";
    ls->propPortsNone           = "Geen";

    // New entries in 2.3 
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle"; 

    ls->propPortsSimplCovox = "SiMPL / Covox DAC"; 
    ls->propPortsFile = "Afdrukken naar bestand"; 
    ls->propPortsOpenLogFile = "Log bestand openen"; 
    ls->propPortsEmulateMsxPrn = "Emulatie:"; 

    ls->shortcutPrnFormFeed = "Printer pagina doorvoer"; 

    ls->menuPrnFormfeed = "Pagina doorvoer"; 
    ls->menuFilePrn = "Printer"; 
    ls->propPortsComFile = "Stuur naar bestand"; 
};

#endif
