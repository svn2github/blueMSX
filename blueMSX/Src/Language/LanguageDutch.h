/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageDutch.h,v $
**
** $Revision: 1.2 $
**
** $Date: 2004-12-06 07:59:12 $
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
    ls->statusBarStopped        = "  Gestopt";
    ls->statusBarPaused         = "  Gepauzeerd";
    ls->statusBarRunning        = "  Bezig";

    ls->menuHardReset           = "Harde Herstart";
    ls->menuSoftReset           = "Zachte Herstart";

    ls->menuCartInsert          = "Toevoegen";
    ls->menuCartRemove          = "Verwijderen";
    ls->menuCartAutoReset       = "Herstart na toevoegen/verwijderen";
    ls->menuCartNoRecentFiles   = "- geen recente bestanden -";
    ls->menuCartFMPac           = "FM-PAC Cartridge";
    ls->menuCartPac             = "PAC Cartridge";
    ls->menuCartSpecial         = "Speciaal";

    ls->menuDiskInsert          = "Toevoegen";
    ls->menuDiskEject           = "Eruit halen";
    ls->menuDiskAutoStart       = "Herstart na toevoegen";
    ls->menuDiskNoRecentFiles   = "- geen recente bestanden -";

    ls->menuCasInsert           = "Toevoegen";
    ls->menuCasEject            = "Verwijderen";
    ls->menuCasSetPosition      = "Bepaal positie";
    ls->menuCasRewind           = "Spoel terug";
    ls->menuCasNoRecentFiles    = "- geen recente bestanden -";

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

    ls->menuFileCart1           = "Cartridge slot 1";
    ls->menuFileCart2           = "Cartridge slot 2";
    ls->menuFileDiskA           = "Diskette drive A";
    ls->menuFileDiskB           = "Diskette drive B";
    ls->menuFileCas             = "Cassette";
    ls->menuFileLoadState       = "Laad CPU status";
    ls->menuFileSaveState       = "Opslaan CPU status";
    ls->menuFileQLoadState      = "Snel laden status";
    ls->menuFileQSaveState      = "Snel opslaan status";
    ls->menuFileCaptureAudio    = "Opslaan Geluid";
    ls->menuFileScreenShot      = "Opslaan Screenshot";
    ls->menuFileExit            = "Exit";

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
    ls->errorEnterFullscreen    = "Gefaald om naar Volledig Scherm stand te gaan.          \n";
    ls->errorDirectXFailed      = "Gefaald om de DirectX objecten te creeren.           \nUsing GDI instead.\nCheck Video properties.";
    ls->errorNoRomInZip         = "Er zijn geen .rom bestanden te vinden in het zip bestand.";
    ls->errorNoDskInZip         = "Er zijn geen .dsk bestanden te vinden in het zip bestand.";
    ls->errorNoCasInZip         = "Er zijn geen .cas bestanden te vinden in het zip bestand.";
    ls->errorNoHelp             = "Het blueMSX help bestand is niet te vinden.";
    ls->errorStartEmu           = "Gefaald om de MSX emulator te starten.";

    ls->tooltipReset            = "Herstart MSX";
    ls->tooltipCart1            = "Stop Cartridge in Slot 1";
    ls->tooltipCart2            = "Stop Cartridge in Slot 2";
    ls->tooltipDiskA            = "Stop Diskette in Drive A";
    ls->tooltipDiskB            = "Stop Diskette in Drive B";
    ls->tooltipCas              = "Stop Tape in Cassette speler";
    ls->tooltipStart            = "Start emulatie";
    ls->tooltipResume           = "Ga verder met emulatie";
    ls->tooltipPause            = "Pauseer emulatie";
    ls->tooltipWindowSize       = "Bepaal Window Grootte";
    ls->tooltipProperties       = "Open Eigenschappen van Dialog";
    ls->tooltipHelp             = "Open Help Scherm";

    ls->dlgMainWindow           = "  blueMSX";
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
    ls->dlgInsertCas            = "Stop cassette in tape";

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Openen";
    ls->dlgCancel               = "Annuleren";

    ls->dlgTapeTitle            = "blueMSX - Tape positie";
    ls->dlgTapeFrameText        = "Tape Positie";
    ls->dlgTapeCurrentPos       = "Huidige positie";
    ls->dlgTapeTotalTime        = "Totale tijd";

    ls->dlgZipReset             = "Herstart na toevoegen";

    ls->dlgAboutTitle           = "blueMSX - Info";

    ls->dlgJoyTitle1            = "blueMSX - Joystick toetsenkeuze A";
    ls->dlgJoyTitle2            = "blueMSX - Joystick toetsenkeuze B";
    ls->dlgJoyUpText            = "Boven";
    ls->dlgJoyDownText          = "Beneden";
    ls->dlgJoyLeftText          = "Links";
    ls->dlgJoyRightText         = "Rechts";
    ls->dlgJoyButton1Text       = "Knop 1";
    ls->dlgJoyButton2Text       = "Knop 2";
    ls->dlgJoyGB                = "Toetsenkeuze configuratie ";

    ls->dlgLangLangText         = "Kies de taal die blueMSX moet gebruiken";
    ls->dlgLangLangTitle        = "blueMSX - Taal";

    ls->propTitle               = "blueMSX - Eigenschappen";
    ls->propEmulation           = "Emulatie";
    ls->propVideo               = "Beeld";
    ls->propSound               = "Geluid";
    ls->propControls            = "Besturing";
    ls->propPerformance         = "Prestatie";

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

    ls->propPerfVideoDrvGB      = "Beeld (Video) Driver ";
    ls->propPerfVideoDispDrvText= "Beeld (Display) driver:";
    ls->propPerfFrameSkipText   = "Overslaan van frames:";
    ls->propPerfAudioDrvGB      = "Audio Driver ";
    ls->propPerfAudioDrvText    = "Geluid driver:";
    ls->propPerfAudioBufSzText  = "Geluid buffer grootte:";
    ls->propPerfEmuGB           = "Emulatie ";
    ls->propPerfSyncModeText    = "SYNC Modus:";

    ls->propSndChipEmuGB        = "Geluid Chip Emulatie ";
    ls->propSndMixerGB          = "Audio Mixer ";
    ls->propSndMonoText         = "mono";
    ls->propSndStereoText       = "stereo";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "MASTER";

    ls->propJoyPort1GB          = "Port #1 ";
    ls->propJoyPort2GB          = "Port #2 ";
    ls->propJoyAutofireText     = "Auto-vuren:";
    ls->propJoyKeysetGB         = "Joystick toetsenkeuze ";
    ls->propJoyKeyest1          = "Bepaal toetsenkeuze A";
    ls->propJoyKeyest2          = "Bepaal toetsenkeuze B";

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
    ls->enumSoundDrvWMM         = "WMM driver";
    ls->enumSoundDrvDirectX     = "DirectX driver";

    ls->enumEmuSync1ms          = "1ms (beste)";
    ls->enumEmuSyncAuto         = "Automatisch (snel)";

    ls->enumControlsJoyNone     = "geen";
    ls->enumControlsJoyNumpad   = "Numpad";
    ls->enumControlsJoyKeysetA  = "Toetsenkeuze A";
    ls->enumControlsJoyKeysetB  = "Toetsenkeuze B";
    ls->enumControlsJoyPCjoy1   = "PC joystick #1";
    ls->enumControlsJoyPCjoy2   = "PC joystick #2";
    ls->enumControlsJoyMouse    = "Muis";

    ls->enumControlsAfOff       = "Uit";
    ls->enumControlsAfSlow      = "Langzaam";
    ls->enumControlsAfMedium    = "Gemiddeld";
    ls->enumControlsAfFast      = "Snel";

    ls->dlgAboutAbout           = "Info\r\n====";
    ls->dlgAboutVersion         = "Versie:";
    ls->dlgAboutBuildNumber     = "Gemaakt:";
    ls->dlgAboutBuildDate       = "Datum:";
    ls->dlgAboutCreat           = "Gemaakt door Daniel Vik";
    ls->dlgAboutLisence         = "LICENTIE\r\n"
                                  "======\r\n\r\n"
                                  "Deze software wordt gegeven 'as-is', zonder enige vorm van garantie. "
                                  " De auteur is niet verantwoordelijk voor elke vorm van schade "
                                  "die onstaat door het gebruik van deze software.\r\n\r\n"
                                  "Bezoek www.bluemsx.com voor meer details.";


    ls->dlgAboutDevel           = "GEMAAKT DOOR\r\n========";
    ls->dlgAboutThanks          = "MET DANK AAN\r\n============";

    // New entries
    ls->menuTools                = "Gereedschap";
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
    ls->propSetFileHistorySize   = "Aantal Bestanden Geschiedenis:";
    ls->propSetFileHistoryClear  = "Leegmaken Geschiedenis";
    ls->propSetScreenSaverGB     = "Scherm beveiliging";
    ls->propSetScreenSaver       = "Uitschakelen Scherm Beveiliging wanneer blueMSX draait";
    ls->confTitle                = "blueMSX - Aanpassen Machine Configuratie";
    ls->confSave                 = "Opslaan";
    ls->confSaveAs               = "Opslaan als...";
    ls->confRun                  = "Start";
    ls->confClose                = "Afsluiten";
    ls->confConfigText           = "Configuratie";
    ls->confSlotLayout           = "Slot Uiterlijk";
    ls->confMemory               = "Geheugen";
    ls->confChipEmulation        = "Chip Emulatie";

    ls->confSlotLayoutGB         = "Slot Uiterlijk ";
    ls->confSlotExtSlotGB        = "Externe Slots ";
    ls->confSlotSlot0            = "Slot 0";
    ls->confSlotSlot1            = "Slot 1";
    ls->confSlotSlot2            = "Slot 2";
    ls->confSlotSlot3            = "Slot 3";
    ls->confSlotCart1            = "Cartridge 1:";
    ls->confSlotCart2            = "Cartridge 2:";
    ls->confSlotPrimary          = "Primair";
    ls->confSlotExpanded         = "Uitgebreid (vier sub-slots)";

    ls->confMemAdd               = "Toevoegen...";
    ls->confMemEdit              = "Aanpassen...";
    ls->confMemRemove            = "Verwijderen";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Address";
    ls->confMemType              = "Type";
    ls->confMemRomImage          = "Rom Beeld";

    ls->confChipVideoGB          = "Beeld ";
    ls->confChipVideoChip        = "Beeld Chip:";
    ls->confChipVideoRam         = "Beeld RAM:";
    ls->confChipSoundGB          = "Geluid ";

    ls->confSaveTitle            = "blueMSX - Sla Machine Configuratie op";
    ls->confSaveText             = "Deze machine configuratie vervangen? :";

    ls->slotEditMemTitle         = "blueMSX - Aanpassen Mapper";
    ls->slotEditMemGB            = "Mapper Details ";
    ls->slotEditMemType          = "Type:";
    ls->slotEditMemFile          = "Bestand:";
    ls->slotEditMemAddress       = "Address";
    ls->slotEditMemSize          = "Grootte";
    ls->slotEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Configuratie";
    ls->confExitSaveTitle        = "blueMSX - Afsluiten Aanpassen Machine Configuratie";
    ls->confExitSaveText         = "De gemaakte wijzigingen in de huidige configuratie niet toepassen?";

    ls->confSaveAsTitle          = "blueMSX - Sla Machine Configuratie op als...";
    ls->confSaveAsMachineName    = "Machine Naam:";

    ls->confEditMemInternalRoms  = "blueMSX - Interne roms";


    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypesGB          = "Bestand types ";
    ls->propFileTypes            = " Verbinden sommige bestand types met blueMSX";
    ls->propDisableWinKeys       = " Automatische MSX functie voor Windows toetsen";
    ls->propWindowsEnvGB         = "Windows Omgeving";
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW accel.";
    ls->enumVideoDrvDirectDrawHWSys = "DirectDraw mix.";
    ls->propMonHorizStretch      = " Horizontale Uitrekking";
    ls->propClearHistory         = "Bestand geschiedenis werkelijk leegmaken ?";
    ls->propEmuFrontSwitchGB     = "Panasonic Switches ";
    ls->propEmuFrontSwitch       = " Front Switch";
    ls->propEmuAudioSwitch       = " MSX-AUDIO cartridge switch";
    ls->propMonVertStretch       = " Verticale Uitrekking";

    ls->dlgCmosGB                = "CMOS ";
    ls->dlgCmosEnable            = " Aanzetten CMOS";
    ls->dlgCmosBattery           = " Gebruiken Geladen Batterij";

    ls->menuCartSnatcher        = "The Snatcher Cartridge";
    ls->menuCartSdSnatcher      = "SD-Snatcher Cartridge";
    ls->menuCartSCCMirrored     = "SCC Gespiegelde Cartridge";
    ls->menuCartSCCExpanded     = "SCC Uitgebreide Cartridge";
    ls->menuCartSCCPlus         = "SCC+ Cartridge";

    ls->warningTitle             = "blueMSX - Waarschuwing";
    ls->tooltipStop              = "Stop emulatie";


    // New entries in 1.5.1
    ls->enumControlsJoyKeyset   = "Toetsenkeuze";
    ls->propJoyConfigKeyset     = "Configuratie Toetsenkeuze";
    ls->propJoyControlText      = "Besturing:";
    ls->propJoyButtonText       = "Knop";
    ls->propJoyButtonAText      = "Knop A:";
    ls->propJoyButtonBText      = "Knop B:";

    ls->menuToolsShortcuts      = "Maken Snelkoppeling";

    ls->shortcutSaveConfig      = "blueMSX -  Sla Configuratie op";
    ls->shortcutOverwriteConfig = "Huidige configuratie overschrijven?:";
    ls->shortcutExitConfig      = "blueMSX -  Afsluiten Snelkoppeling Configuratie";
    ls->shortcutDiscardConfig   = "De gemaakte wijzigingen in de huidige configuratie niet toepassen?";
    ls->shortcutSaveConfigAs    = "blueMSX - Sla Configuratie op als...";
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
    ls->shortcutEmuSpeedMax     = "Maximum snelheid van de emulatie";
    ls->shortcutEmuSpeedNormal  = "Normale snelheid van de emulatie";
    ls->shortcutEmuSpeedInc     = "Verhoog snelheid van de emulatie";
    ls->shortcutEmuSpeedDec     = "Verlaag snelheid van de emulatie";
    ls->shortcutShowEmuProp     = "Openenen venster: Eigenschappen van de emulatie";
    ls->shortcutShowVideoProp   = "Openenen venster: Beeld";
    ls->shortcutShowAudioProp   = "Openenen venster: Geluid";
    ls->shortcutShowCtrlProp    = "Openenen venster: Besturing";
    ls->shortcutShowPerfProp    = "Openenen venster: Prestatie";
    ls->shortcutShowSettProp    = "Openenen venster: Instellingen";
    ls->shortcutShowLanguage    = "Openenen venster: Taaldialoog";
    ls->shortcutShowMachines    = "Openenen venster: Machine menu";
    ls->shortcutShowShortcuts   = "Openenen venster: Snelkoppelingen menu";
    ls->shortcutShowHelp        = "Openenen venster: Hulpdialoog";
    ls->shortcutShowAbout       = "Openenen venster: Info blueMSX";

    ls->shortcutSpecialMenu1    = "Openenen venster: Speciale menu voor ROM cartridge in slot 1";
    ls->shortcutSpecialMenu2    = "Openenen venster: Speciale menu voor ROM cartridge in slot 2";
    ls->shortcutVolumeStereo    = "Kiezen mono of stereo mode";
    ls->shortcutThemeSwitch     = "Kiezen ander thema";
    ls->shortcutToggleSpriteEnable = "Tonen/Verbergen sprites";

    ls->shortcutShowApearProp   = "Show Uiterlijk eigenschappen";
    ls->menuPropsApearance      = "Uiterlijk";
    ls->propApearance           = "Uiterlijk";
    ls->propThemeGB             = "Thema ";
    ls->propTheme               = "Thema";
    ls->propThemeClassic        = "Klassiek";
    ls->propThemeBlue           = "DIGIblauw";

    ls->propMonBrightness       = "Helderheid:";
    ls->propMonContrast         = "Contrast:";
    ls->propMonSaturation       = "Verzadiging:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanlines:";

    ls->dlgRomType              = "Rom type :";
    ls->propOpenRomGB           = "Openen Rom bestand";
    ls->propDefaultRomType      = "Standaard type:";
    ls->propGuessRomType        = "Raden type";

    ls->propFile                = "Bestand";
    ls->propSettDefSlotGB       = "Slepen en neerzetten ";
    ls->propSettDefSlots        = "Toevoegen cartridge in:";
    ls->propSettDefSlot1        = " Slot 1";
    ls->propSettDefSlot2        = " Slot 2";
    ls->propSettDefDrives       = "Toevoegen diskette in:";
    ls->propSettDefDriveA       = " Drive A";
    ls->propSettDefDriveB       = " Drive B";
    ls->menuPropsFile           = "Bestand";
    ls->shortcutShowFiles       = "Tonen van bestand eigenschappen";

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
    ls->dlgCpuFreqGB            = "CPU frequentie "; 
    ls->dlgZ80FreqText          = "Z80 frequentie:"; 
    ls->dlgR800FreqText         = "R800 Frequentie:"; 
    ls->dlgFdcGB                = "Floppy Disk Controller "; 
    ls->dlgCFdcNumDrivesText    = "Aantal drives:"; 

    ls->propPriorityBoost       = " Aan blueMSX een hoge prioriteit geven";

};

#endif
