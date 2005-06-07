/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguagePolish.h,v $
**
** $Revision: 1.1 $ 
**
** $Date: 2005-06-07 02:41:45 $
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
#ifndef LANGUAGE_POLISH_H
#define LANGUAGE_POLISH_H

#include "LanguageStrings.h"
 
void langInitPolish(LanguageStrings* ls) 
{
    ls->statusBarStopped        = "  Zatrzymany";
    ls->statusBarPaused         = "  Pauza";
    ls->statusBarRunning        = "  Uruchomiony";
    
    ls->menuHardReset           = "Twardy Reset";
    ls->menuSoftReset           = "Miêkki Reset";
    
    ls->menuCartInsert          = "W³ó¿";
    ls->menuCartRemove          = "Usuñ";
    ls->menuCartAutoReset       = "Resetuj po zmianie";
    ls->menuCartNoRecentFiles   = "- brak ostatnich plików -";
    ls->menuCartFMPac           = "Kartrid¿ FM-PAC";
    ls->menuCartPac             = "Kartrid¿ PAC";
    ls->menuCartSpecial         = "Specialne";

    ls->menuDiskInsert          = "W³ó¿";
    ls->menuDiskEject           = "Wysuñ";
    ls->menuDiskAutoStart       = "Resetuj po zmianie";
    ls->menuDiskNoRecentFiles   = "- brak ostatnich plików -";
    
    ls->menuCasInsert           = "W³ó¿";
    ls->menuCasEject            = "Wyjmij";
    ls->menuCasSetPosition      = "Set Position";
    ls->menuCasRewind           = "Rewind";
    ls->menuCasNoRecentFiles    = "- no recent files -";

    ls->menuZoomNormal          = "Standardowe";
    ls->menuZoomDouble          = "Podwójne";
    ls->menuZoomFullscreen      = "Pe³ny ekran";
    
    ls->menuPropsEmulation      = "Emulacja";
    ls->menuPropsVideo          = "Obraz";
    ls->menuPropsSound          = "DŸwiêk";
    ls->menuPropsControls       = "Sterowanie";
    ls->menuPropsPerformance    = "Osi¹gi";
    ls->menuPropsLanguage       = "Jêzyk";
    
    ls->menuHelpHelp            = "Tematy pomocy";
    ls->menuHelpAbout           = "O blueMSX...";

    ls->menuFileCart1           = "Cartridge Slot 1";
    ls->menuFileCart2           = "Cartridge Slot 2";
    ls->menuFileDiskA           = "Stacja dyskietek A";
    ls->menuFileDiskB           = "Stacja dyskietek B";
    ls->menuFileCas             = "Kaseta";
    ls->menuFileLoadState       = "Wczytaj stan CPU";
    ls->menuFileSaveState       = "Zapisz stan CPU";
    ls->menuFileQLoadState      = "Szybki odczyt stanu";
    ls->menuFileQSaveState      = "Szybki zapis stanu";
    ls->menuFileCaptureAudio    = "Przechwyæ dŸwiêk";
    ls->menuFileScreenShot      = "Zapisz ekran";
    ls->menuFileExit            = "Wyjœcie";

    ls->menuRunRun              = "Uruchom";
    ls->menuRunPause            = "Spauzuj (???)";
    ls->menuRunStop             = "Zatrzymaj";
    ls->menuRunSoftReset        = "Miêkki reset";
    ls->menuRunHardReset        = "Twardy reset";
    ls->menuRunCleanReset       = "Ogólny reset";

    ls->menuFile                = "Plik";
    ls->menuRun                 = "Uruchamianie";
    ls->menuWindow              = "Okno";
    ls->menuOptions             = "Opcje";
    ls->menuHelp                = "Pomoc";
    
    ls->errorTitle              = "blueMSX - b³¹d";
    ls->errorEnterFullscreen    = "Nie mogê prze³¹czyæ na pe³ny ekran.           \n";
    ls->errorDirectXFailed      = "Nie mogê stworzyæ obiektów DirectX.           \nPrze³¹czam w tryb GDI.\nSprawdŸ w³aœciwoœci wideo.";
    ls->errorNoRomInZip         = "Nie znaleziono pliku .rom w archiwum zip.";
    ls->errorNoDskInZip         = "Nie znaleziono pliku .dsk w archiwum zip.";
    ls->errorNoCasInZip         = "Nie znaleziono pliku .cas w archiwum zip.";
    ls->errorNoHelp             = "Nie znaleziono pliku pomocy blueMSX.";
    ls->errorStartEmu           = "Nie uda³o siê uruchomiæ emulatora MSX.";

    ls->tooltipReset            = "Resetuje MSX";
    ls->tooltipCart1            = "Umieszcza kartrid¿ w 1-wszym slocie";
    ls->tooltipCart2            = "Umieszcza kartrid¿ w 2-gim slocie";
    ls->tooltipDiskA            = "Umieszcza dyskietkê w stacji A";
    ls->tooltipDiskB            = "Umieszcza dyskietkê w stacji B";
    ls->tooltipCas              = "Umieszcza kasetê w magnetofonie";
    ls->tooltipStart            = "Uruchamia emulacjê";
    ls->tooltipResume           = "Wznawia emulacjê";
    ls->tooltipPause            = "Przerywa emulacjê";
    ls->tooltipWindowSize       = "Ustawia rozmiar okna";
    ls->tooltipProperties       = "Otwiera okno w³aœciwoœci";
    ls->tooltipHelp             = "Otwiera okno pomocy";

    ls->dlgMainWindow           = "  blueMSX";
    ls->dlgLoadRom              = "blueMSX - Wybierz plik rom do wczytania";
    ls->dlgLoadDsk              = "blueMSX - Wybierz plik dsk do wczytania";
    ls->dlgLoadCas              = "blueMSX - Wybierz plik cas do wczytania";
    ls->dlgLoadRomDskCas        = "blueMSX - Wybierz plik rom, dsk lub cas do wczytania";
    ls->dlgLoadRomDesc          = "Wybierz rom do wczytania:";
    ls->dlgLoadDskDesc          = "Wybierz dyskietkê do wczytania:";
    ls->dlgLoadCasDesc          = "Wybierz taœmê do wczytania:";
    ls->dlgLoadRomDskCasDesc    = "Wybierz rom, dyskietkê lub taœmê do wczytania:";
    ls->dlgLoadState            = "Wczytaj stan CPU";
    ls->dlgSaveState            = "Zapisz stan CPU";
    ls->dlgInsertRom1           = "Wybierz kartrid¿ ROM dla 1-go slotu";
    ls->dlgInsertRom2           = "Wybierz kartrid¿ ROM dla 2-go slotu";
    ls->dlgInsertDiskA          = "Wybierz dyskietkê dla stacji A";
    ls->dlgInsertDiskB          = "Wybierz dyskietkê dla stacji B";
    ls->dlgInsertCas            = "Wybierz kasetê";

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Otwórz";
    ls->dlgCancel               = "Anuluj";

    ls->dlgTapeTitle            = "blueMSX - Pozycja taœmy";
    ls->dlgTapeFrameText        = "Pozycja taœmy";
    ls->dlgTapeCurrentPos       = "Obecna pozycja";
    ls->dlgTapeTotalTime        = "Czas ca³kowity";

    ls->dlgZipReset             = "Resettuj po zmianie";

    ls->dlgAboutTitle           = "blueMSX - O programie";

    ls->dlgJoyTitle1            = "blueMSX - Joystick zestaw klawiszy A";
    ls->dlgJoyTitle2            = "blueMSX - Joystick zestaw klawiszy B";
    ls->dlgJoyUpText            = "Góra";
    ls->dlgJoyDownText          = "Dó³";
    ls->dlgJoyLeftText          = "Lewo";
    ls->dlgJoyRightText         = "Prawo";
    ls->dlgJoyButton1Text       = "Przycisk 1";
    ls->dlgJoyButton2Text       = "Przycisk 2";
    ls->dlgJoyGB                = "Konfiguracja klawiszy (???)";

    ls->dlgLangLangText         = "Wybierz jêzyk dla blueMSX";
    ls->dlgLangLangTitle        = "blueMSX - Jêzyk";

    ls->propTitle               = "blueMSX - W³aœciwoœci";
    ls->propEmulation           = "Emulacja";
    ls->propVideo               = "Obraz";
    ls->propSound               = "DŸwiêk";
    ls->propControls            = "Kontrola (???)";
    ls->propPerformance         = "Osi¹gi (???)";
    
    ls->propEmuGeneralGB        = "Ogólne ";
    ls->propEmuFamilyText       = "Typ MSX:";
    ls->propEmuMemoryGB         = "Pamiêæ ";
    ls->propEmuRamSizeText      = "Rozmiar RAMu:";
    ls->propEmuVramSizeText     = "Rozmiar VRAMu:";
    ls->propEmuSpeedGB          = "Szybkoœæ emulacji ";
    ls->propEmuSpeedText        = "Szybkoœæ emulacji:";

    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Typ monitora:";
    ls->propMonEmuText          = "Emulacja monitora:";
    ls->propVideoYypeText       = "Video type (typ obrazu???):";
    ls->propWindowSizeText      = "Rozmiar okna:";

    ls->propPerfVideoDrvGB      = "Ustawienia Video";
    ls->propPerfVideoDispDrvText= "Sterownik obrazu:";
    ls->propPerfFrameSkipText   = "Przeskakiwanie klatek:";
    ls->propPerfAudioDrvGB      = "Ustawienia Audio";
    ls->propPerfAudioDrvText    = "Sterownik dŸwiêku:";
    ls->propPerfAudioBufSzText  = "Rozmiar bufora dŸwiêku:";
    ls->propPerfEmuGB           = "Emulacja ";
    ls->propPerfSyncModeText    = "Tryb synchronizacji:";

    ls->propSndChipEmuGB        = "Emulacja dŸwiêku";
    ls->propSndMixerGB          = "Mikser dŸwiêku";
    ls->propSndMonoText         = "mono";
    ls->propSndStereoText       = "stereo";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "MASTER";

    ls->propJoyPort1GB          = "Port #1 ";
    ls->propJoyPort2GB          = "Port #2 ";
    ls->propJoyAutofireText     = "Autofire:";
    ls->propJoyKeysetGB         = "Zestaw klawiszy dla Joysticka ";
    ls->propJoyKeyest1          = "Konfiguruj zestaw klawiszy A";
    ls->propJoyKeyest2          = "Konfiguruj zestaw klawiszy B";

    ls->enumVideoMonColor       = "Kolorowy";
    ls->enumVideoMonGrey        = "Czarno-bia³y";
    ls->enumVideoMonGreen       = "Zielony";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "None";
    ls->enumVideoEmuYc          = "Kabel Y/C (ostry)";
    ls->enumVideoEmuYcBlur      = "Zaszumiony kabel Y/C (ostry)";
    ls->enumVideoEmuComp        = "Kompozytowe (rozmyte)";
    ls->enumVideoEmuCompBlur    = "Zaszumione kompozytowe (rozmyte)";
    ls->enumVideoEmuScale2x     = "Skaluj 2x";

    ls->enumVideoSize1x         = "Normalna (???) - 320x200";
    ls->enumVideoSize2x         = "Podwójna (???) - 640x400";
    ls->enumVideoSizeFullscreen = "Pe³ny ekran";

    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "Brak";
    ls->enumVideoFrameskip1     = "1 klatka";
    ls->enumVideoFrameskip2     = "2 klatki";
    ls->enumVideoFrameskip3     = "3 klatki";
    ls->enumVideoFrameskip4     = "4 klatki";
    ls->enumVideoFrameskip5     = "5 klatek";

    ls->enumSoundDrvNone        = "Brak dŸwiêku";
    ls->enumSoundDrvWMM         = "Driver WMM";
    ls->enumSoundDrvDirectX     = "Driver DirectX";

    ls->enumEmuSync1ms          = "1ms (najlepszy)";
    ls->enumEmuSyncAuto         = "Auto (szybki)";

    ls->enumControlsJoyNone     = "Brak";
    ls->enumControlsJoyNumpad   = "Numpad";
    ls->enumControlsJoyKeysetA  = "Zestaw klawiszy A";
    ls->enumControlsJoyKeysetB  = "Zestaw klawiszy B";
    ls->enumControlsJoyPCjoy1   = "Joystick PC #1";
    ls->enumControlsJoyPCjoy2   = "Joystick PC #2";
    ls->enumControlsJoyMouse    = "Mysz";

    ls->enumControlsAfOff       = "Wy³. (Wy³¹czone???)";
    ls->enumControlsAfSlow      = "Wolny (-e???)";
    ls->enumControlsAfMedium    = "Œredni";
    ls->enumControlsAfFast      = "Szybki";

    ls->dlgAboutAbout           = "O programie\r\n====";
    ls->dlgAboutVersion         = "Wersja:";
    ls->dlgAboutBuildNumber     = "Kompilacja:";
    ls->dlgAboutBuildDate       = "Data:";
    ls->dlgAboutCreat           = "Stworzony przez Daniela Vika";
    ls->dlgAboutDevel           = "PROGRAMIŒCI\r\n========";
    ls->dlgAboutThanks          = "SPECJALNE PODZIÊKOWANIA DLA\r\n============";
    ls->dlgAboutLisence         = "LICENSE\r\n"
                                  "======\r\n\r\n"
                                  "This software is provided 'as-is', without any express or implied "
                                  "warranty. In no event will the author(s) be held liable for any damages "
                                  "arising from the use of this software.\r\n\r\n"
                                  "Visit www.bluemsx.com for more details.";

    // New entries
    ls->menuTools                = "Narzêdzia";
    ls->menuToolsMachine         = "Edytor komputerów";
    ls->menuPropsSettings        = "Ustawienia";
    ls->menuCasRewindAfterInsert = "Najpierw przewiñ do pocz¹tku";
    ls->menuCasUseReadOnly       = "U¿ywaj kaset 'tylko do odczytu'";
    ls->lmenuCasSaveAs           = "Zapisz kasetê jako...";

    ls->dlgSaveCassette          = "blueMSX - Zapisz obraz kasety";
    ls->dlgTapeCustom            = "Poka¿ pliki -custom(???)-";
    ls->dlgTapeSetPosText        = "Pozycja taœmy:";
    ls->dlgTabPosition           = "Pozycja";
    ls->dlgTabType               = "Type";
    ls->dlgTabFilename           = "Nazwa pliku";

    ls->propSettings             = "Ustawienia";
    
    ls->propSetFileHistoryGB     = "Historia plików (ostatnie pliki???) ";
    ls->propSetFileHistorySize   = "Iloœc elementów w historii plików:";
    ls->propSetFileHistoryClear  = "Wyczyœæ historiê";
    ls->propSetScreenSaverGB     = "Wygaszacz ekranu ";
    ls->propSetScreenSaver       = " Wy³¹cz wygaszacz podczas pracy blueMSX";

    ls->confTitle                = "blueMSX - Edytor Konfiguracji Komputerów";
    ls->confSave                 = "Zapisz";
    ls->confSaveAs               = "Zapisz jako...";
    ls->confRun                  = "Uruchom";
    ls->confClose                = "Zamknij";
    ls->confConfigText           = "Konfiguracja";
    ls->confSlotLayout           = "Uk³ad slotów";
    ls->confMemory               = "Pamiêæ";
    ls->confChipEmulation        = "Emulation Chip (-a/-ów/czip-???)";

    ls->confSlotLayoutGB         = "Uk³ad slotów ";
    ls->confSlotExtSlotGB        = "Zewnêtrzne sloty ";
    ls->confSlotSlot0            = "Slot 0";
    ls->confSlotSlot1            = "Slot 1";
    ls->confSlotSlot2            = "Slot 2";
    ls->confSlotSlot3            = "Slot 3";
    ls->confSlotCart1            = "Kartrid¿ 1:";
    ls->confSlotCart2            = "Kartrid¿ 2:";
    ls->confSlotPrimary          = "G³ówny";
    ls->confSlotExpanded         = "Dodatkowe (cztery pod-sloty)";

    ls->confMemAdd               = "Dodaj...";
    ls->confMemEdit              = "Edytuj...";
    ls->confMemRemove            = "Usuñ";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Adres";
    ls->confMemType              = "Typ";
    ls->confMemRomImage          = "Obraz rom";
    
    ls->confSaveTitle            = "blueMSX - Zapis(sz???) konfiguracjê";
    ls->confSaveText             = "Czy chcesz nadpisaæ konfiguracjê:";

    ls->confChipVideoGB          = "Obraz ";
    ls->confChipVideoChip        = "Koœæ video:";
    ls->confChipVideoRam         = "Pamiêæ video RAM:";
    ls->confChipSoundGB          = "DŸwiêk ";

    ls->slotEditMemTitle         = "blueMSX - Edytuj mapper (bueee???)";
    ls->slotEditMemGB            = "Konfiguracja mappera";
    ls->slotEditMemType          = "Typ:";
    ls->slotEditMemFile          = "Plik:";
    ls->slotEditMemAddress       = "Adres";
    ls->slotEditMemSize          = "Rozmiar";
    ls->slotEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Konfiguracja";
    ls->confExitSaveTitle        = "blueMSX - WyjdŸ z Edytora Konfiguracj";
    ls->confExitSaveText         = "Czy chcesz zignorowaæ zmiany w bierz¹cej konfiguracji?";

    ls->confSaveAsMachineTitle   = "blueMSX - Zapisz konfiguracjê komputera jako...";
    ls->confSaveAsMachineName    = "Nazwa komputera:";

    ls->confEditMemInternalRoms  = "blueMSX - Wewnêtrzne (???) romy";
    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypesGB          = "Typy plików ";
    ls->propFileTypes            = " SkojaŸ pliki z blueMSX (.rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " Automatic MSX function for Windows menu keys (???)"; 
    ls->propWindowsEnvGB         = "Otoczenie Windows (???)"; 
    ls->enumVideoDrvDirectDrawHW = "DirectDraw (sprzêtowe)"; 
    ls->enumVideoDrvDirectDrawHWSys = "DirectDraw mix."; 
    ls->propMonHorizStretch      = " Horizontal Stretch (???)";
    ls->propMonVertStretch       = " Vertical Stretch (???)";
    ls->propClearHistory         = "Na pewno wyczyœciæ historiê plików?";

    ls->propEmuFrontSwitchGB     = "Prze³¹czniki Panasonic ";
    ls->propEmuFrontSwitch       = " Prze³¹cznik g³ówny(???)";
    ls->propEmuAudioSwitch       = " MSX-AUDIO cartridge switch(???)";


    ls->dlgCmosGB                = "CMOS ";
    ls->dlgCmosEnable            = " Enable CMOS";
    ls->dlgCmosBattery           = " Use Charged Battery";

    ls->menuCartSnatcher        = "The Snatcher Cartridge";
    ls->menuCartSdSnatcher      = "SD-Snatcher Cartridge";
    ls->menuCartSCCMirrored     = "SCC Mirrored Cartridge";
    ls->menuCartSCCExpanded     = "SCC Expanded Cartridge";
    ls->menuCartSCCPlus         = "SCC+ Cartridge";
    ls->menuCartSCC             = "SCC Cartridge";
    
    ls->warningTitle             = "blueMSX - Uwaga";
    ls->tooltipStop             = "Zatrzymaj emulacjê";

    // New entries in 1.5.1
    ls->enumControlsJoyKeyset   = "Zestaw klawiszy";    
    ls->propJoyConfigKeyset     = "konfiguruj zestaw klawiszy";
    ls->propJoyControlText      = "Control:(???)";
    ls->propJoyButtonText       = "Przycisk";
    ls->propJoyButtonAText      = "Przycisk A:";
    ls->propJoyButtonBText      = "Przycisk B:";

    ls->menuToolsShortcuts      = "Edytor skrótów klawiaturowych";

    ls->shortcutSaveConfig      = "blueMSX - Zapisz konfiguracjê";
    ls->shortcutOverwriteConfig = "Chcesz nadpisaæ konfiguracjê skrótów?:";
    ls->shortcutExitConfig      = "blueMSX - WyjdŸ z edytora skrótów";
    ls->shortcutDiscardConfig   = "Czy chcesz zignorowaæ zmiany w bierz¹cej konfiguracji?";
    ls->shortcutSaveConfigAs    = "blueMSX - Zapisz konfiguracjê skrótów jako...";
    ls->shortcutConfigName      = "Nazwa konfiguracji:";
    ls->shortcutNewProfile      = "< Nowy profil >";
    ls->shortcutConfigTitle     = "blueMSX - Edytor Mapowania Skrótów";
    ls->shortcutAssign          = "Przypisz";
    ls->shortcutPressText       = "Naciœnij przycisk(i) skrótu:";
    ls->shortcutScheme          = "Schemat mapowania:";

    ls->shortcutCartInsert1     = "W³ó¿ kartrid¿ 1";
    ls->shortcutCartRemove1     = "Wyjmij kartrid¿ 1";
    ls->shortcutCartInsert2     = "W³ó¿ kartrid¿ 2";
    ls->shortcutCartRemove2     = "Wyjmij kartrid¿ 2";
    ls->shortcutCartAutoReset   = "Resetuj emulator przy wk³adaniu kartrid¿a";
    ls->shortcutDiskInsertA     = "W³ó¿ dyskietkê A";
    ls->shortcutDiskRemoveA     = "Wyjmij dyskietkê A";
    ls->shortcutDiskChangeA     = "Szybka zmiana dyskietki A";
    ls->shortcutDiskAutoResetA  = "Resetuj emulator przy wk³adaniu dyskietki A";
    ls->shortcutDiskInsertB     = "W³ó¿ dyskietkê B";
    ls->shortcutDiskRemoveB     = "Wyjmij dyskietkê B";
    ls->shortcutCasInsert       = "W³ó¿ kasetê";
    ls->shortcutCasEject        = "Wyjmij kasetê";
    ls->shortcutCasAutorewind   = "Prze³¹cz auto-przewijanie kasety";
    ls->shortcutCasReadOnly     = "Prze³¹cz kasetê na 'tylko do odczytu'";
    ls->shortcutCasSetPosition  = "Ustaw pozycjê kasety";
    ls->shortcutCasRewind       = "Przewiñ kasetê";
    ls->shortcutCasSave         = "Zapisz obraz kasety";
    ls->shortcutCpuStateLoad    = "Wczytaj stan CPU";
    ls->shortcutCpuStateSave    = "Zapisz stan CPU";
    ls->shortcutCpuStateQload   = "Szybkie wczytanie stanu CPU";
    ls->shortcutCpuStateQsave   = "Szybki zapis stanu CPU";
    ls->shortcutAudioCapture    = "Uruchom/zatrzymaj zapis dŸwiêku";
    ls->shortcutScreenshotOrig  = "Zapisanie zrzutu ekranu";
    ls->shortcutScreenshotSmall = "Ma³y, niefiltrowany zrzut ekranu";
    ls->shortcutScreenshotLarge = "Du¿y, niefiltrowany zrzut ekranu";
    ls->shortcutQuit            = "Wyjœcie z blueMSX";
    ls->shortcutRunPause        = "Uruchom/zpauzuj emulacjê";
    ls->shortcutStop            = "Zatrzymaj emulacje";
    ls->shortcutResetHard       = "Twardy Reset";
    ls->shortcutResetSoft       = "Miêkki Reset";
    ls->shortcutResetClean      = "Ogólny Reset";
    ls->shortcutSizeSmall       = "Ustaw ma³y rozmiar okna";
    ls->shortcutSizeNormal      = "Ustaw normalny rozmiar okna";
    ls->shortcutSizeFullscreen  = "Ustaw pe³ny ekran";
    ls->shortcutToggleFullscren = "Prze³¹czaj pe³ny ekran";
    ls->shortcutVolumeIncrease  = "Podg³oœnij dŸwiêk";
    ls->shortcutVolumeDecrease  = "Œcisz dŸwiêk";
    ls->shortcutVolumeMute      = "Wy³¹cz dŸwiêk";
    ls->shortcutSwitchMsxAudio  = "Pstryknij (???) prze³¹cznik MSX-AUDIO";
    ls->shortcutSwitchFront     = "Pstryknij g³ówny (???) prze³¹cznik Panasonic";
    ls->shortcutToggleMouseLock = "Prze³¹cznik przechwytywania myszy (chyba???)";
    ls->shortcutEmuSpeedMax     = "Maksymalna prêdkoœæ emulacji";
    ls->shortcutEmuSpeedToggle  = "Prze³¹czaj pomiêdzy maksymaln¹ prêdkoœci¹ emulacji";
    ls->shortcutEmuSpeedNormal  = "Normalna prêdkoœæ emulacji";
    ls->shortcutEmuSpeedInc     = "Zwiêksz prêdkoœæ emulacji";
    ls->shortcutEmuSpeedDec     = "Zmniejsz prêdkoœæ emulacji";
    ls->shortcutShowEmuProp     = "Wyœwiertl okno w³aœciwoœci";
    ls->shortcutShowVideoProp   = "Wyœwiertl ustawienia obrazu";
    ls->shortcutShowAudioProp   = "Wyœwiertl ustawienia dŸwiêku";
    ls->shortcutShowCtrlProp    = "Wyœwiertl ustawienia kontroli(???)";
    ls->shortcutShowPerfProp    = "Wyœwiertl ustawienia szybkoœci(???)";
    ls->shortcutShowSettProp    = "Wyœwiertl ustawienia";
    ls->shortcutShowLanguage    = "Wyœwiertl ustawienia jêzyka";
    ls->shortcutShowMachines    = "Wyœwiertl Edytor Komputerów";
    ls->shortcutShowShortcuts   = "Wyœwiertl Edytor Skrótów";
    ls->shortcutShowHelp        = "Wyœwiertl Pomoc";
    ls->shortcutShowAbout       = "Wyœwiertl informacje O programie";
    
    ls->shortcutSpecialMenu1    = "Wyœwiertl specjalne menu 1-go kartrid¿a";
    ls->shortcutSpecialMenu2    = "Wyœwiertl specjalne menu 2-go kartrid¿a";
    ls->shortcutVolumeStereo    = "Prze³¹cz mono/stereo";
    ls->shortcutThemeSwitch     = "Zmieñ temat :)";
    ls->shortcutToggleSpriteEnable = "Poka¿/ukryj sprite'y";
    
    ls->shortcutShowApearProp   = "Wyœwietl w³aœciwoœci wygl¹du";
    ls->menuPropsApearance      = "Wygl¹d";
    ls->propApearance           = "Wygl¹d";
    ls->propThemeGB             = "Temat ";
    ls->propTheme               = "Temat:";
    ls->propThemeClassic        = "Klasyczny";
    ls->propThemeBlue           = "DIGIDIGIblue";

    ls->propMonBrightness       = "Jasnoœæ:";
    ls->propMonContrast         = "Kontrast:";
    ls->propMonSaturation       = "Nasycenie:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanlines(???):";

    ls->dlgRomType              = "Typ romu:";
    ls->propOpenRomGB           = "Otwórz okno romu(???) ";
    ls->propDefaultRomType      = "Domyœlny typ romu:";
    ls->propGuessRomType        = "Odgadnij typ romu";

    ls->propFile                = "Pliki";
    ls->propSettDefSlotGB       = "Przeci¹gnij-i-upuœæ ";
    ls->propSettDefSlots        = "W³ó¿ rom do:";
    ls->propSettDefSlot1        = " Slot 1";
    ls->propSettDefSlot2        = " Slot 2";
    ls->propSettDefDrives       = "W³ó¿ dyskietkê do:";
    ls->propSettDefDriveA       = " stacji A";
    ls->propSettDefDriveB       = " stacji B";
    ls->menuPropsFile           = "Pliki";
    ls->shortcutShowFiles       = "Poka¿ w³aœciwoœci pliku";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "Pod³¹cz folder";
    ls->shortcutDiskDirInsertA  = "Pod³¹cz folder jako dyskietkê A";
    ls->shortcutDiskDirInsertB  = "Pod³¹cz folder jako dyskietkê B";
    ls->propMonDeInterlace      = " Usuwaj przeplot";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "Pauza (???)";
    ls->shortcutSizeMinimized   = "Minimalizuj okno";
    ls->shortcutEmuSpeedToggle  = "Prze³¹cz maksymaln¹ prêdkoœæ emulacji";
    ls->shortcutToggleCpuTrace  = "W³./wy³. œledzenie CPU";

    ls->enumVideoEmuMonitor     = "Monitor";

    ls->propEmuPauseSwitch      = " Prze³¹cznik pauzy";
    ls->propVideoFreqText       = "Czêstotliwoœæ obrazu:";
    ls->propVideoFreqAuto       = "Auto";
    ls->propSndOversampleText   = "Oversample:";

    ls->confChipExtras          = "Extras";
    ls->confBoardGB             = "Board ";
    ls->confBoardText           = "Board Type:";
    ls->dlgCpuFreqGB            = "CPU Frequency ";
    ls->dlgZ80FreqText          = "Z80 Frequency:";
    ls->dlgR800FreqText         = "R800 Frequency:";
    ls->dlgFdcGB                = "Floppy Disk Controller ";
    ls->dlgCFdcNumDrivesText    = "Number of Drives:";

    ls->propPriorityBoost       = " Podnieœ priorytet blueMSX";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "Wy³¹cz timing stacji dyskietek";
    ls->shortcutToggleFdcTiming = "W³./wy³. timing stacji dyskietek";
    ls->propUseRegistry         = "Zapisuj konfiguracjê w rejestrze";

    // New entries in 2.2
    ls->menuCartHBI55           = "Sony HBI-55 Cartridge";
    ls->propSndPcm              = " Turbo-R PCM";
    ls->propSndAY8910           = " AY8910 PSG";
    ls->propSndSN76489          = " SN76489 PSG";
    ls->enumVideoEmuHq2x        = "Hq2x";
    ls->propMonColorGhosting    = "RF-Modulator";

    ls->keyconfigSelectedKey    = "Wybrany klawisz:";
    ls->keyconfigMappedTo       = "Zmapowany na:";
    ls->keyconfigMappingScheme  = "Schemat mapowania:";

    ls->discardChanges          = "Czy chcesz zniszczyæ zmiany?";
    ls->overwriteConfig         = "Czy chcesz nadpisac bierz¹ca konfiguracjê?";

    ls->confSaveAsTitle         = "Zapisz konfiguracjê jako...";
    ls->confSaveAsName          = "Nzawa:";

    ls->menuToolsKeyboard       = "Edytor klawiatury";
    ls->shortcutShowKeyboard    = "Poka¿ edytor klawiatury";

    ls->menuVideoSource         = "ród³o obrazu";
    ls->menuVideoSourceDefault  = "Nie pod³¹czono Ÿród³a obrazu";
    ls->menuVideoChipAutodetect = "Autodetekcja koœci obrazu";
    ls->propFullscreenResText   = "Rozdzielczoœæ dla pe³nego ekranu:";
    ls->dlgSavePreview          = "Poka¿ podgl¹d";
    ls->dlgSaveDate             = "Czas zapisu (zapisany???):";
    
    ls->enumVideoMonAmber       = "Miodowy (???)";

    ls->menuPropsPorts          = "Porty";
    ls->propPortsLptGB          = "Port równoleg³y ";
    ls->propPortsComGB          = "Port szeregowy ";
    ls->propPortsLptText        = "Port:";
    ls->propPortsCom1Text       = "Port 1:";

    ls->shortcutShowDebugger    = "Poka¿ Debugger";
    ls->shortcutShowTrainer     = "Wyœwietl Trainer (???)";
    ls->shortcutShowPorts       = "Wyœwietl w³aœciwoœci portów";
    
    ls->propPorts               = "Ports";
    ls->propPortsNone           = "Brak";

    // New entries in 2.3
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle";

    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "Drukuj do pliku";
    ls->propPortsOpenLogFile    = "Otwórz plik logu";
    ls->propPortsFilenameText   = "Nazwa pliku:";
    ls->propPortsEmulateMsxPrn  = "Emulacja:";

    ls->shortcutPrnFormFeed     = "Wysuñ kartkê z drukarki";

    ls->menuPrnFormfeed         = "Wysuñ papier";
    ls->menuFilePrn             = "Drukarka";

};


#endif


