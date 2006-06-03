/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguagePolish.h,v $
**
** $Revision: 1.7 $
**
** $Date: 2006-06-03 20:22:18 $
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
    ls->menuNoRecentFiles       = "- brak ostatnich plik�w -";
    ls->menuInsert              = "Wybierz";
    ls->menuEject               = "Wysu�";

    ls->menuCartAutoReset       = "Resetuj po zmianie";
    ls->menuCartFMPac           = "Kartrid� FM-PAC";
    ls->menuCartPac             = "Kartrid� PAC";

    ls->menuDiskAutoStart       = "Resetuj po zmianie";
    
    ls->menuCasSetPosition      = "Ustaw pozycj�";
    ls->menuCasRewind           = "Przewi� do pocz�tku";

    ls->menuZoomNormal          = "Standardowe";
    ls->menuZoomDouble          = "Podw�jne";
    ls->menuZoomFullscreen      = "Pe�ny ekran";
    
    ls->menuPropsEmulation      = "Emulacja";
    ls->menuPropsVideo          = "Obraz";
    ls->menuPropsSound          = "D�wi�k";
    ls->menuPropsControls       = "Sterowanie";
    ls->menuPropsPerformance    = "Wydajno��";
    ls->menuPropsLanguage       = "J�zyk";
    
    ls->menuHelpHelp            = "Tematy pomocy";
    ls->menuHelpAbout           = "O blueMSX...";

    ls->menuFileCart            = "Kartrid�";
    ls->menuFileDisk            = "Stacja dyskietek";
    ls->menuFileCas             = "Kaseta";
    ls->menuFileLoadState       = "Wczytaj stan CPU";
    ls->menuFileSaveState       = "Zapisz stan CPU";
    ls->menuFileQLoadState      = "Szybki odczyt stanu";
    ls->menuFileQSaveState      = "Szybki zapis stanu";
    ls->menuFileCaptureAudio    = "Przechwy� d�wi�k";
    ls->menuFileScreenShot      = "Zapisz ekran";
    ls->menuFileExit            = "Wyj�cie";

    ls->menuRunRun              = "Uruchom";
    ls->menuRunPause            = "Pauza";
    ls->menuRunStop             = "Zatrzymaj";
    ls->menuRunSoftReset        = "Mi�kki reset";
    ls->menuRunHardReset        = "Twardy reset";
    ls->menuRunCleanReset       = "Pe�ny reset";

    ls->menuFile                = "Plik";
    ls->menuRun                 = "Uruchamianie";
    ls->menuWindow              = "Okno";
    ls->menuOptions             = "Opcje";
    ls->menuHelp                = "Pomoc";
    
    ls->errorTitle              = "blueMSX - b��d";
    ls->errorEnterFullscreen    = "Nie mog� prze��czy� na pe�ny ekran.           \n";
    ls->errorDirectXFailed      = "Nie mog� stworzy� obiekt�w DirectX.           \nPrze��czam w tryb GDI.\nSprawd� w�a�ciwo�ci wideo.";
    ls->errorNoRomInZip         = "Nie znaleziono pliku .rom w archiwum zip.";
    ls->errorNoDskInZip         = "Nie znaleziono pliku .dsk w archiwum zip.";
    ls->errorNoCasInZip         = "Nie znaleziono pliku .cas w archiwum zip.";
    ls->errorNoHelp             = "Nie znaleziono pliku pomocy blueMSX.";
    ls->errorStartEmu           = "Nie uda�o si� uruchomi� emulatora MSX.";

    ls->dlgLoadRom              = "blueMSX - Wybierz plik rom do wczytania";
    ls->dlgLoadDsk              = "blueMSX - Wybierz plik dsk do wczytania";
    ls->dlgLoadCas              = "blueMSX - Wybierz plik cas do wczytania";
    ls->dlgLoadRomDskCas        = "blueMSX - Wybierz plik rom, dsk lub cas do wczytania";
    ls->dlgLoadRomDesc          = "Wybierz rom do wczytania:";
    ls->dlgLoadDskDesc          = "Wybierz dyskietk� do wczytania:";
    ls->dlgLoadCasDesc          = "Wybierz ta�m� do wczytania:";
    ls->dlgLoadRomDskCasDesc    = "Wybierz rom, dyskietk� lub ta�m� do wczytania:";
    ls->dlgLoadState            = "Wczytaj stan CPU";
    ls->dlgSaveState            = "Zapisz stan CPU";
    ls->dlgInsertRom1           = "Wybierz kartrid� ROM dla slotu 1";
    ls->dlgInsertRom2           = "Wybierz kartrid� ROM dla slotu 2";
    ls->dlgInsertDiskA          = "Wybierz dyskietk� dla stacji A";
    ls->dlgInsertDiskB          = "Wybierz dyskietk� dla stacji B";
    ls->dlgInsertCas            = "Wybierz kaset�";

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Otw�rz";
    ls->dlgCancel               = "Anuluj";

    ls->dlgTapeTitle            = "blueMSX - Pozycja ta�my";
    ls->dlgTapeFrameText        = "Pozycja ta�my";
    ls->dlgTapeCurrentPos       = "Obecna pozycja";
    ls->dlgTapeTotalTime        = "Czas ca�kowity";

    ls->dlgZipReset             = "Resettuj po zmianie";

    ls->dlgAboutTitle           = "blueMSX - O programie";

    ls->dlgLangLangText         = "Wybierz j�zyk dla blueMSX";
    ls->dlgLangLangTitle        = "blueMSX - J�zyk";

    ls->propTitle               = "blueMSX - W�a�ciwo�ci";
    ls->propEmulation           = "Emulacja";
    ls->propVideo               = "Obraz";
    ls->propSound               = "D�wi�k";
    ls->propControls            = "Sterowanie";
    ls->propPerformance         = "Wydajno��";
    
    ls->propEmuGeneralGB        = "Og�lne ";
    ls->propEmuFamilyText       = "Typ MSX:";
    ls->propEmuMemoryGB         = "Pami�� ";
    ls->propEmuRamSizeText      = "Rozmiar RAMu:";
    ls->propEmuVramSizeText     = "Rozmiar VRAMu:";
    ls->propEmuSpeedGB          = "Szybko�� emulacji ";
    ls->propEmuSpeedText        = "Szybko�� emulacji:";

    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Typ monitora:";
    ls->propMonEmuText          = "Emulacja monitora:";
    ls->propVideoYypeText       = "Typ obrazu:";
    ls->propWindowSizeText      = "Rozmiar okna:";

    ls->propPerfVideoDrvGB      = "Ustawienia Video";
    ls->propPerfVideoDispDrvText= "Sterownik obrazu:";
    ls->propPerfFrameSkipText   = "Gubienie klatek:";
    ls->propPerfAudioDrvGB      = "Ustawienia Audio";
    ls->propPerfAudioDrvText    = "Sterownik d�wi�ku:";
    ls->propPerfAudioBufSzText  = "Rozmiar bufora d�wi�ku:";
    ls->propPerfEmuGB           = "Emulacja ";
    ls->propPerfSyncModeText    = "Tryb synchronizacji:";

    ls->propSndChipEmuGB        = "Emulacja d�wi�ku";
    ls->propSndMixerGB          = "Mikser d�wi�ku";
    ls->propSndMonoText         = "mono";
    ls->propSndStereoText       = "stereo";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "MASTER";

    ls->enumVideoMonColor       = "Kolorowy";
    ls->enumVideoMonGrey        = "Czarno-bia�y";
    ls->enumVideoMonGreen       = "Zielony";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Brak";
    ls->enumVideoEmuYc          = "Kabel Y/C (ostry)";
    ls->enumVideoEmuYcBlur      = "Zaszumiony kabel Y/C (ostry)";
    ls->enumVideoEmuComp        = "Kompozytowe (rozmyte)";
    ls->enumVideoEmuCompBlur    = "Zaszumione kompozytowe (rozmyte)";
    ls->enumVideoEmuScale2x     = "Skalowanie 2x";

    ls->enumVideoSize1x         = "Pojedyncza - 320x200";
    ls->enumVideoSize2x         = "Podw�jna - 640x400";
    ls->enumVideoSizeFullscreen = "Pe�ny ekran";

    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "Brak";
    ls->enumVideoFrameskip1     = "1 klatka";
    ls->enumVideoFrameskip2     = "2 klatki";
    ls->enumVideoFrameskip3     = "3 klatki";
    ls->enumVideoFrameskip4     = "4 klatki";
    ls->enumVideoFrameskip5     = "5 klatek";

    ls->enumSoundDrvNone        = "Brak d�wi�ku";
    ls->enumSoundDrvWMM         = "Driver WMM";
    ls->enumSoundDrvDirectX     = "Driver DirectX";

    ls->enumEmuSync1ms          = "1ms (najlepszy)";
    ls->enumEmuSyncAuto         = "Auto (szybki)";

    ls->enumControlsJoyNone     = "Brak";
    ls->enumControlsJoyMouse    = "Mysz";

    ls->dlgAboutAbout           = "O programie\r\n====";
    ls->dlgAboutVersion         = "Wersja:";
    ls->dlgAboutBuildNumber     = "Kompilacja:";
    ls->dlgAboutBuildDate       = "Data:";
    ls->dlgAboutCreat           = "Program Daniela Vika";
    ls->dlgAboutDevel           = "PROGRAMI�CI\r\n========";
    ls->dlgAboutThanks          = "SPECJALNE PODZI�KOWANIA DLA\r\n============";
    ls->dlgAboutLisence         = "LICENSE\r\n"
                                  "======\r\n\r\n"
                                  "This software is provided 'as-is', without any express or implied "
                                  "warranty. In no event will the author(s) be held liable for any damages "
                                  "arising from the use of this software.\r\n\r\n"
                                  "Visit www.bluemsx.com for more details.";

    // New entries
    ls->menuTools                = "Narz�dzia";
    ls->menuToolsMachine         = "Edytor komputer�w";
    ls->menuPropsSettings        = "Ustawienia";
    ls->menuCasRewindAfterInsert = "Najpierw przewi� do pocz�tku";
    ls->menuCasUseReadOnly       = "U�ywaj kaset 'tylko do odczytu'";
    ls->lmenuCasSaveAs           = "Zapisz kaset� jako...";

    ls->dlgSaveCassette          = "blueMSX - Zapisz obraz kasety";
    ls->dlgTapeCustom            = "Poka� dowolne pliki";
    ls->dlgTapeSetPosText        = "Pozycja ta�my:";
    ls->dlgTabPosition           = "Pozycja";
    ls->dlgTabType               = "Typ";
    ls->dlgTabFilename           = "Nazwa pliku";

    ls->propSettings             = "Ustawienia";
    
    ls->propSetFileHistoryGB     = "Historia plik�w ";
    ls->propSetFileHistorySize   = "Ilo�c element�w w historii plik�w:";
    ls->propSetFileHistoryClear  = "Wyczy�� histori�";
    ls->propSetScreenSaver       = " Wy��cz wygaszacz podczas pracy blueMSX";

    ls->confTitle                = "blueMSX - Edytor Konfiguracji Komputer�w";
    ls->confSave                 = "Zapisz";
    ls->confSaveAs               = "Zapisz jako...";
    ls->confRun                  = "Uruchom";
    ls->confClose                = "Zamknij";
    ls->confConfigText           = "Konfiguracja";
    ls->confSlotLayout           = "Uk�ad slot�w";
    ls->confMemory               = "Pami��";
    ls->confChipEmulation        = "Uk�ad obrazu";

    ls->confSlotLayoutGB         = "Uk�ad slot�w ";
    ls->confSlotExtSlotGB        = "Zewn�trzne sloty ";
    ls->confSlotCart             = "Kartrid�";
    ls->confSlotPrimary          = "Podstawowy";
    ls->confSlotExpanded         = "Rozszerzone (cztery sub-sloty)";

    ls->confMemAdd               = "Dodaj...";
    ls->confMemEdit              = "Edytuj...";
    ls->confMemRemove            = "Usu�";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Adres";
    ls->confMemType              = "Typ";
    ls->confMemRomImage          = "Obraz rom";
    
    ls->confSaveTitle            = "blueMSX - Zapis konfiguracji";
    ls->confSaveText             = "Czy chcesz nadpisa� konfiguracj�:";

    ls->confChipVideoGB          = "Obraz ";
    ls->confChipVideoChip        = "Ko�� obrazu:";
    ls->confChipVideoRam         = "Pami�� RAM obrazu:";
    ls->confChipSoundGB          = "D�wi�k ";

    ls->confEditMemTitle         = "blueMSX - Edytuj Mapper";
    ls->confEditMemGB            = "Konfiguracja Mappera";
    ls->confEditMemType          = "Typ:";
    ls->confEditMemFile          = "Plik:";
    ls->confEditMemAddress       = "Adres";
    ls->confEditMemSize          = "Rozmiar";
    ls->confEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Konfiguracja";
    ls->confExitSaveTitle        = "blueMSX - Wyjd� z Edytora Konfiguracj";
    ls->confExitSaveText         = "Czy chcesz zignorowa� zmiany w bierz�cej konfiguracji?";

    ls->confSaveAsMachineTitle   = "blueMSX - Zapisz konfiguracj� komputera jako...";
    ls->confSaveAsMachineName    = "Nazwa komputera:";

    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypes            = " Skoja� pliki z blueMSX (.rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " Automatyczna konfiguracja klawiszy Windows w MSX"; 
    ls->propWindowsEnvGB         = "Otoczenie Windows "; 
    ls->enumVideoDrvDirectDrawHW = "DirectDraw (sprz�towy)"; 
    ls->propMonHorizStretch      = " Rozci�gaj w poziomie";
    ls->propMonVertStretch       = " Rozci�gaj w pionie";
    ls->propClearHistory         = "Na pewno wyczy�ci� histori� plik�w?";

    ls->propEmuFrontSwitchGB     = "Prze��czniki Panasonic ";
    ls->propEmuFrontSwitch       = " Prze��cznik g��wny";
    ls->propEmuAudioSwitch       = " Prze��cznik kartrid�a MSX-AUDIO";


    ls->confCmosGB                = "CMOS ";
    ls->confCmosEnable            = " Enable CMOS";
    ls->confCmosBattery           = " Use Charged Battery";

    ls->menuCartSCCPlus         = "SCC+ Cartridge";
    ls->menuCartSCC             = "SCC Cartridge";
    
    ls->warningTitle             = "blueMSX - Uwaga";

    // New entries in 1.5.1
    ls->menuToolsShortcuts      = "Edytor skr�t�w klawiaturowych";

    ls->shortcutSaveConfig      = "blueMSX - Zapisz konfiguracj�";
    ls->shortcutOverwriteConfig = "Chcesz nadpisa� konfiguracj� skr�t�w?:";
    ls->shortcutExitConfig      = "blueMSX - Wyjd� z edytora skr�t�w";
    ls->shortcutDiscardConfig   = "Czy chcesz zignorowa� zmiany w bierz�cej konfiguracji?";
    ls->shortcutSaveConfigAs    = "blueMSX - Zapisz konfiguracj� skr�t�w jako...";
    ls->shortcutConfigName      = "Nazwa konfiguracji:";
    ls->shortcutNewProfile      = "< Nowy profil >";
    ls->shortcutConfigTitle     = "blueMSX - Edytor Mapowania Skr�t�w";
    ls->shortcutAssign          = "Przypisz";
    ls->shortcutPressText       = "Naci�nij przycisk(i) skr�tu:";
    ls->shortcutScheme          = "Schemat mapowania:";

    ls->shortcutCartInsert1     = "W�� kartrid� 1";
    ls->shortcutCartRemove1     = "Wyjmij kartrid� 1";
    ls->shortcutCartInsert2     = "W�� kartrid� 2";
    ls->shortcutCartRemove2     = "Wyjmij kartrid� 2";
    ls->shortcutCartAutoReset   = "Resetuj emulator przy wk�adaniu kartrid�a";
    ls->shortcutDiskInsertA     = "W�� dyskietk� A";
    ls->shortcutDiskRemoveA     = "Wyjmij dyskietk� A";
    ls->shortcutDiskChangeA     = "Szybka zmiana dyskietki A";
    ls->shortcutDiskAutoResetA  = "Resetuj emulator przy wk�adaniu dyskietki A";
    ls->shortcutDiskInsertB     = "W�� dyskietk� B";
    ls->shortcutDiskRemoveB     = "Wyjmij dyskietk� B";
    ls->shortcutCasInsert       = "W�� kaset�";
    ls->shortcutCasEject        = "Wyjmij kaset�";
    ls->shortcutCasAutorewind   = "Prze��cz auto-przewijanie kasety";
    ls->shortcutCasReadOnly     = "Prze��cz kaset� na 'tylko do odczytu'";
    ls->shortcutCasSetPosition  = "Ustaw pozycj� kasety";
    ls->shortcutCasRewind       = "Przewi� kaset�";
    ls->shortcutCasSave         = "Zapisz obraz kasety";
    ls->shortcutCpuStateLoad    = "Wczytaj stan CPU";
    ls->shortcutCpuStateSave    = "Zapisz stan CPU";
    ls->shortcutCpuStateQload   = "Szybkie wczytanie stanu CPU";
    ls->shortcutCpuStateQsave   = "Szybki zapis stanu CPU";
    ls->shortcutAudioCapture    = "Uruchom/zatrzymaj zapis d�wi�ku";
    ls->shortcutScreenshotOrig  = "Zapisanie zrzutu ekranu";
    ls->shortcutScreenshotSmall = "Ma�y, niefiltrowany zrzut ekranu";
    ls->shortcutScreenshotLarge = "Du�y, niefiltrowany zrzut ekranu";
    ls->shortcutQuit            = "Wyj�cie z blueMSX";
    ls->shortcutRunPause        = "Uruchom/zpauzuj emulacj�";
    ls->shortcutStop            = "Zatrzymaj emulacje";
    ls->shortcutResetHard       = "Twardy Reset";
    ls->shortcutResetSoft       = "Mi�kki Reset";
    ls->shortcutResetClean      = "Og�lny Reset";
    ls->shortcutSizeSmall       = "Ustaw ma�y rozmiar okna";
    ls->shortcutSizeNormal      = "Ustaw normalny rozmiar okna";
    ls->shortcutSizeFullscreen  = "Ustaw pe�ny ekran";
    ls->shortcutToggleFullscren = "Prze��czaj pe�ny ekran";
    ls->shortcutVolumeIncrease  = "Podg�o�nij d�wi�k";
    ls->shortcutVolumeDecrease  = "�cisz d�wi�k";
    ls->shortcutVolumeMute      = "Wy��cz d�wi�k";
    ls->shortcutSwitchMsxAudio  = "Prze��cznik MSX-AUDIO";
    ls->shortcutSwitchFront     = "Prze��cznik g��wny Panasonic";
    ls->shortcutToggleMouseLock = "Przechwytywanie myszy";
    ls->shortcutEmuSpeedMax     = "Maksymalna pr�dko�� emulacji";
    ls->shortcutEmuSpeedToggle  = "Prze��czaj pomi�dzy maksymaln� pr�dko�ci� emulacji";
    ls->shortcutEmuSpeedNormal  = "Normalna pr�dko�� emulacji";
    ls->shortcutEmuSpeedInc     = "Zwi�ksz pr�dko�� emulacji";
    ls->shortcutEmuSpeedDec     = "Zmniejsz pr�dko�� emulacji";
    ls->shortcutShowEmuProp     = "Wy�wietl okno w�a�ciwo�ci";
    ls->shortcutShowVideoProp   = "Wy�wietl ustawienia obrazu";
    ls->shortcutShowAudioProp   = "Wy�wietl ustawienia d�wi�ku";
    ls->shortcutShowCtrlProp    = "Wy�wietl ustawienia sterowania";
    ls->shortcutShowPerfProp    = "Wy�wietl ustawienia wydajno�ci";
    ls->shortcutShowSettProp    = "Wy�wietl ustawienia";
    ls->shortcutShowLanguage    = "Wy�wietl ustawienia j�zyka";
    ls->shortcutShowMachines    = "Wy�wietl Edytor Komputer�w";
    ls->shortcutShowShortcuts   = "Wy�wietl Edytor Skr�t�w";
    ls->shortcutShowHelp        = "Wy�wietl Pomoc";
    ls->shortcutShowAbout       = "Wy�wietl informacje O programie";
    
    ls->shortcutSpecialMenu1    = "Wy�wietl specjalne menu 1-go kartrid�a";
    ls->shortcutSpecialMenu2    = "Wy�wietl specjalne menu 2-go kartrid�a";
    ls->shortcutVolumeStereo    = "Prze��cz mono/stereo";
    ls->shortcutThemeSwitch     = "Zmie� temat :)";
    ls->shortcutToggleSpriteEnable = "Poka�/ukryj sprite'y";
    
    ls->shortcutShowApearProp   = "Wy�wietl w�a�ciwo�ci wygl�du";
    ls->menuPropsApearance      = "Wygl�d";
    ls->propApearance           = "Wygl�d";
    ls->propThemeGB             = "Temat ";
    ls->propTheme               = "Temat:";

    ls->propMonBrightness       = "Jasno��:";
    ls->propMonContrast         = "Kontrast:";
    ls->propMonSaturation       = "Nasycenie:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Przeplot:";

    ls->dlgRomType              = "Typ romu:";
    ls->propOpenRomGB           = "Okno wyboru romu ";
    ls->propDefaultRomType      = "Domy�lny typ romu:";
    ls->propGuessRomType        = "Odgadnij typ romu";

    ls->propFile                = "Pliki";
    ls->propSettDefSlotGB       = "Przeci�gnij-i-upu�� ";
    ls->propSettDefSlots        = "W�� rom do:";
    ls->propSettDefSlot         = " Slot";
    ls->propSettDefDrives       = "W�� dyskietk� do:";
    ls->propSettDefDrive        = " Stacji";
    ls->menuPropsFile           = "Pliki";
    ls->shortcutShowFiles       = "Poka� w�a�ciwo�ci pliku";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "Podepnij folder";
    ls->shortcutDiskDirInsertA  = "Pod��cz folder jako dyskietk� A";
    ls->shortcutDiskDirInsertB  = "Pod��cz folder jako dyskietk� B";
    ls->propMonDeInterlace      = " Usuwaj przeplot";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "Pauza";
    ls->shortcutSizeMinimized   = "Minimalizuj okno";
    ls->shortcutEmuSpeedToggle  = "Prze��cz maksymaln� pr�dko�� emulacji";
    ls->shortcutToggleCpuTrace  = "W�./wy�. �ledzenie CPU";

    ls->enumVideoEmuMonitor     = "Monitor";

    ls->propEmuPauseSwitch      = " Prze��cznik pauzy";
    ls->propVideoFreqText       = "Cz�stotliwo�� obrazu:";
    ls->propVideoFreqAuto       = "Auto";
    ls->propSndOversampleText   = "Oversampling:";

    ls->confChipExtras          = "Extras";
    ls->confBoardGB             = "Board ";
    ls->confBoardText           = "Board Type:";
    ls->confCpuFreqGB            = "CPU Frequency ";
    ls->confZ80FreqText          = "Z80 Frequency:";
    ls->confR800FreqText         = "R800 Frequency:";
    ls->confFdcGB                = "Floppy Disk Controller ";
    ls->confCFdcNumDrivesText    = "Number of Drives:";

    ls->propPriorityBoost       = " Podnie� priorytet blueMSX";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "Wy��cz timing stacji dyskietek";
    ls->shortcutToggleFdcTiming = "W�./wy�. timing stacji dyskietek";

    // New entries in 2.2
    ls->menuCartHBI55           = "Sony HBI-55 Cartridge";
    ls->propSndPcm              = " Turbo-R PCM";
    ls->propSndAY8910           = " AY8910 PSG";
    ls->propSndSN76489          = " SN76489 PSG";
    ls->enumVideoEmuHq2x        = "Hq2x";
    ls->propMonColorGhosting    = "Modulator RF";

    ls->keyconfigSelectedKey    = "Wybrany klawisz:";
    ls->keyconfigMappedTo       = "Zmapowany na:";
    ls->keyconfigMappingScheme  = "Schemat mapowania:";

    ls->warningDiscardChanges   = "Czy chcesz zniszczy� zmiany?";

    ls->confSaveAsTitle         = "Zapisz konfiguracj� jako...";
    ls->confSaveAsName          = "Nazwa:";

    ls->menuToolsKeyboard       = "Edytor klawiatury";
    ls->shortcutShowKeyboard    = "Poka� edytor klawiatury";

    ls->menuVideoSource         = "�r�d�o obrazu";
    ls->menuVideoSourceDefault  = "Nie pod��czono �r�d�a obrazu";
    ls->menuVideoChipAutodetect = "Autodetekcja ko�ci obrazu";
    ls->propFullscreenResText   = "Pe�ny ekran:";
    ls->dlgSavePreview          = "Poka� podgl�d";
    ls->dlgSaveDate             = "Czas zapisu:";
    
    ls->enumVideoMonAmber       = "Miodowy";

    ls->menuPropsPorts          = "Porty";
    ls->propPortsLptGB          = "Port r�wnoleg�y ";
    ls->propPortsComGB          = "Port szeregowy ";
    ls->propPortsLptText        = "Port:";
    ls->propPortsCom1Text       = "Port 1:";

    ls->shortcutShowDebugger    = "Poka� Debugger";
    ls->shortcutShowTrainer     = "Wy�wietl Trainer";
    ls->shortcutShowPorts       = "Wy�wietl w�a�ciwo�ci port�w";
    
    ls->propPorts               = "Porty";
    ls->propPortsNone           = "Brak";

    // New entries in 2.3
    ls->enumControlsJoyTetris2Dongle = "Dongle Tetris 2";

    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "Drukuj do pliku";
    ls->propPortsOpenLogFile    = "Otw�rz plik logu";
    ls->propPortsEmulateMsxPrn  = "Emulacja:";

    ls->shortcutPrnFormFeed     = "Wysu� kartk� z drukarki";

    ls->menuPrnFormfeed         = "Wysu� papier";
    ls->menuFilePrn             = "Drukarka";

    // New entries in 2.4
    ls->shortcutShowMixer       = "Poka� mikser";
    ls->menuToolsMixer          = "Mikser";
    
    ls->propSndMidiInGB         = "MIDI In ";
    ls->propSndMidiOutGB        = "MIDI Out ";
    ls->propSndMt32ToGmText     = " Mapuj instrumenty MT-32 na General MIDI";

    ls->textDevice              = "Urz�dzenie:";
    ls->textFilename            = "Nazwa pliku:";
    ls->textFile                = "Plik";
    ls->textNone                = "Brak";

    ls->enumEmuSyncAuto         = "Auto (szybkie)";
    ls->enumEmuSync1ms          = "Synchronizuj z od�wie�aniem MSX";
    ls->enumEmuSyncVblank       = "Synchronizuj z synchronizacj� pionow� PC";

    ls->propMonEffectsGB        = "Efekty ";
    
    ls->confSlot                = "Slot";
    ls->confSubslot             = "Podslot";

    ls->shortcutDescription     = "Skr�t";
    ls->shortcutKey             = "Hotkey";
    ls->fileRom                 = "ROM image";
    ls->confOpenRom             = "Otw�rz ROM";
    ls->fileAll                 = "Wszystkie pliki";
    ls->fileCpuState            = "Stan CPU";
    ls->fileDisk                = "Obraz dysku";
    ls->fileCas                 = "Obraz ta�my";

    ls->menuCartExternalRam     = "Zewn�trzny RAM";
};


#endif


