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
    ls->menuSoftReset           = "Mi�kki Reset";
    
    ls->menuCartInsert          = "W��";
    ls->menuCartRemove          = "Usu�";
    ls->menuCartAutoReset       = "Resetuj po zmianie";
    ls->menuCartNoRecentFiles   = "- brak ostatnich plik�w -";
    ls->menuCartFMPac           = "Kartrid� FM-PAC";
    ls->menuCartPac             = "Kartrid� PAC";
    ls->menuCartSpecial         = "Specialne";

    ls->menuDiskInsert          = "W��";
    ls->menuDiskEject           = "Wysu�";
    ls->menuDiskAutoStart       = "Resetuj po zmianie";
    ls->menuDiskNoRecentFiles   = "- brak ostatnich plik�w -";
    
    ls->menuCasInsert           = "W��";
    ls->menuCasEject            = "Wyjmij";
    ls->menuCasSetPosition      = "Set Position";
    ls->menuCasRewind           = "Rewind";
    ls->menuCasNoRecentFiles    = "- no recent files -";

    ls->menuZoomNormal          = "Standardowe";
    ls->menuZoomDouble          = "Podw�jne";
    ls->menuZoomFullscreen      = "Pe�ny ekran";
    
    ls->menuPropsEmulation      = "Emulacja";
    ls->menuPropsVideo          = "Obraz";
    ls->menuPropsSound          = "D�wi�k";
    ls->menuPropsControls       = "Sterowanie";
    ls->menuPropsPerformance    = "Osi�gi";
    ls->menuPropsLanguage       = "J�zyk";
    
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
    ls->menuFileCaptureAudio    = "Przechwy� d�wi�k";
    ls->menuFileScreenShot      = "Zapisz ekran";
    ls->menuFileExit            = "Wyj�cie";

    ls->menuRunRun              = "Uruchom";
    ls->menuRunPause            = "Spauzuj (???)";
    ls->menuRunStop             = "Zatrzymaj";
    ls->menuRunSoftReset        = "Mi�kki reset";
    ls->menuRunHardReset        = "Twardy reset";
    ls->menuRunCleanReset       = "Og�lny reset";

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

    ls->tooltipReset            = "Resetuje MSX";
    ls->tooltipCart1            = "Umieszcza kartrid� w 1-wszym slocie";
    ls->tooltipCart2            = "Umieszcza kartrid� w 2-gim slocie";
    ls->tooltipDiskA            = "Umieszcza dyskietk� w stacji A";
    ls->tooltipDiskB            = "Umieszcza dyskietk� w stacji B";
    ls->tooltipCas              = "Umieszcza kaset� w magnetofonie";
    ls->tooltipStart            = "Uruchamia emulacj�";
    ls->tooltipResume           = "Wznawia emulacj�";
    ls->tooltipPause            = "Przerywa emulacj�";
    ls->tooltipWindowSize       = "Ustawia rozmiar okna";
    ls->tooltipProperties       = "Otwiera okno w�a�ciwo�ci";
    ls->tooltipHelp             = "Otwiera okno pomocy";

    ls->dlgMainWindow           = "  blueMSX";
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
    ls->dlgInsertRom1           = "Wybierz kartrid� ROM dla 1-go slotu";
    ls->dlgInsertRom2           = "Wybierz kartrid� ROM dla 2-go slotu";
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

    ls->dlgJoyTitle1            = "blueMSX - Joystick zestaw klawiszy A";
    ls->dlgJoyTitle2            = "blueMSX - Joystick zestaw klawiszy B";
    ls->dlgJoyUpText            = "G�ra";
    ls->dlgJoyDownText          = "D�";
    ls->dlgJoyLeftText          = "Lewo";
    ls->dlgJoyRightText         = "Prawo";
    ls->dlgJoyButton1Text       = "Przycisk 1";
    ls->dlgJoyButton2Text       = "Przycisk 2";
    ls->dlgJoyGB                = "Konfiguracja klawiszy (???)";

    ls->dlgLangLangText         = "Wybierz j�zyk dla blueMSX";
    ls->dlgLangLangTitle        = "blueMSX - J�zyk";

    ls->propTitle               = "blueMSX - W�a�ciwo�ci";
    ls->propEmulation           = "Emulacja";
    ls->propVideo               = "Obraz";
    ls->propSound               = "D�wi�k";
    ls->propControls            = "Kontrola (???)";
    ls->propPerformance         = "Osi�gi (???)";
    
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
    ls->propVideoYypeText       = "Video type (typ obrazu???):";
    ls->propWindowSizeText      = "Rozmiar okna:";

    ls->propPerfVideoDrvGB      = "Ustawienia Video";
    ls->propPerfVideoDispDrvText= "Sterownik obrazu:";
    ls->propPerfFrameSkipText   = "Przeskakiwanie klatek:";
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

    ls->propJoyPort1GB          = "Port #1 ";
    ls->propJoyPort2GB          = "Port #2 ";
    ls->propJoyAutofireText     = "Autofire:";
    ls->propJoyKeysetGB         = "Zestaw klawiszy dla Joysticka ";
    ls->propJoyKeyest1          = "Konfiguruj zestaw klawiszy A";
    ls->propJoyKeyest2          = "Konfiguruj zestaw klawiszy B";

    ls->enumVideoMonColor       = "Kolorowy";
    ls->enumVideoMonGrey        = "Czarno-bia�y";
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
    ls->enumVideoSize2x         = "Podw�jna (???) - 640x400";
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
    ls->enumControlsJoyNumpad   = "Numpad";
    ls->enumControlsJoyKeysetA  = "Zestaw klawiszy A";
    ls->enumControlsJoyKeysetB  = "Zestaw klawiszy B";
    ls->enumControlsJoyPCjoy1   = "Joystick PC #1";
    ls->enumControlsJoyPCjoy2   = "Joystick PC #2";
    ls->enumControlsJoyMouse    = "Mysz";

    ls->enumControlsAfOff       = "Wy�. (Wy��czone???)";
    ls->enumControlsAfSlow      = "Wolny (-e???)";
    ls->enumControlsAfMedium    = "�redni";
    ls->enumControlsAfFast      = "Szybki";

    ls->dlgAboutAbout           = "O programie\r\n====";
    ls->dlgAboutVersion         = "Wersja:";
    ls->dlgAboutBuildNumber     = "Kompilacja:";
    ls->dlgAboutBuildDate       = "Data:";
    ls->dlgAboutCreat           = "Stworzony przez Daniela Vika";
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
    ls->dlgTapeCustom            = "Poka� pliki -custom(???)-";
    ls->dlgTapeSetPosText        = "Pozycja ta�my:";
    ls->dlgTabPosition           = "Pozycja";
    ls->dlgTabType               = "Type";
    ls->dlgTabFilename           = "Nazwa pliku";

    ls->propSettings             = "Ustawienia";
    
    ls->propSetFileHistoryGB     = "Historia plik�w (ostatnie pliki???) ";
    ls->propSetFileHistorySize   = "Ilo�c element�w w historii plik�w:";
    ls->propSetFileHistoryClear  = "Wyczy�� histori�";
    ls->propSetScreenSaverGB     = "Wygaszacz ekranu ";
    ls->propSetScreenSaver       = " Wy��cz wygaszacz podczas pracy blueMSX";

    ls->confTitle                = "blueMSX - Edytor Konfiguracji Komputer�w";
    ls->confSave                 = "Zapisz";
    ls->confSaveAs               = "Zapisz jako...";
    ls->confRun                  = "Uruchom";
    ls->confClose                = "Zamknij";
    ls->confConfigText           = "Konfiguracja";
    ls->confSlotLayout           = "Uk�ad slot�w";
    ls->confMemory               = "Pami��";
    ls->confChipEmulation        = "Emulation Chip (-a/-�w/czip-???)";

    ls->confSlotLayoutGB         = "Uk�ad slot�w ";
    ls->confSlotExtSlotGB        = "Zewn�trzne sloty ";
    ls->confSlotSlot0            = "Slot 0";
    ls->confSlotSlot1            = "Slot 1";
    ls->confSlotSlot2            = "Slot 2";
    ls->confSlotSlot3            = "Slot 3";
    ls->confSlotCart1            = "Kartrid� 1:";
    ls->confSlotCart2            = "Kartrid� 2:";
    ls->confSlotPrimary          = "G��wny";
    ls->confSlotExpanded         = "Dodatkowe (cztery pod-sloty)";

    ls->confMemAdd               = "Dodaj...";
    ls->confMemEdit              = "Edytuj...";
    ls->confMemRemove            = "Usu�";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Adres";
    ls->confMemType              = "Typ";
    ls->confMemRomImage          = "Obraz rom";
    
    ls->confSaveTitle            = "blueMSX - Zapis(sz???) konfiguracj�";
    ls->confSaveText             = "Czy chcesz nadpisa� konfiguracj�:";

    ls->confChipVideoGB          = "Obraz ";
    ls->confChipVideoChip        = "Ko�� video:";
    ls->confChipVideoRam         = "Pami�� video RAM:";
    ls->confChipSoundGB          = "D�wi�k ";

    ls->slotEditMemTitle         = "blueMSX - Edytuj mapper (bueee???)";
    ls->slotEditMemGB            = "Konfiguracja mappera";
    ls->slotEditMemType          = "Typ:";
    ls->slotEditMemFile          = "Plik:";
    ls->slotEditMemAddress       = "Adres";
    ls->slotEditMemSize          = "Rozmiar";
    ls->slotEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Konfiguracja";
    ls->confExitSaveTitle        = "blueMSX - Wyjd� z Edytora Konfiguracj";
    ls->confExitSaveText         = "Czy chcesz zignorowa� zmiany w bierz�cej konfiguracji?";

    ls->confSaveAsMachineTitle   = "blueMSX - Zapisz konfiguracj� komputera jako...";
    ls->confSaveAsMachineName    = "Nazwa komputera:";

    ls->confEditMemInternalRoms  = "blueMSX - Wewn�trzne (???) romy";
    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypesGB          = "Typy plik�w ";
    ls->propFileTypes            = " Skoja� pliki z blueMSX (.rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " Automatic MSX function for Windows menu keys (???)"; 
    ls->propWindowsEnvGB         = "Otoczenie Windows (???)"; 
    ls->enumVideoDrvDirectDrawHW = "DirectDraw (sprz�towe)"; 
    ls->enumVideoDrvDirectDrawHWSys = "DirectDraw mix."; 
    ls->propMonHorizStretch      = " Horizontal Stretch (???)";
    ls->propMonVertStretch       = " Vertical Stretch (???)";
    ls->propClearHistory         = "Na pewno wyczy�ci� histori� plik�w?";

    ls->propEmuFrontSwitchGB     = "Prze��czniki Panasonic ";
    ls->propEmuFrontSwitch       = " Prze��cznik g��wny(???)";
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
    ls->tooltipStop             = "Zatrzymaj emulacj�";

    // New entries in 1.5.1
    ls->enumControlsJoyKeyset   = "Zestaw klawiszy";    
    ls->propJoyConfigKeyset     = "konfiguruj zestaw klawiszy";
    ls->propJoyControlText      = "Control:(???)";
    ls->propJoyButtonText       = "Przycisk";
    ls->propJoyButtonAText      = "Przycisk A:";
    ls->propJoyButtonBText      = "Przycisk B:";

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
    ls->shortcutSwitchMsxAudio  = "Pstryknij (???) prze��cznik MSX-AUDIO";
    ls->shortcutSwitchFront     = "Pstryknij g��wny (???) prze��cznik Panasonic";
    ls->shortcutToggleMouseLock = "Prze��cznik przechwytywania myszy (chyba???)";
    ls->shortcutEmuSpeedMax     = "Maksymalna pr�dko�� emulacji";
    ls->shortcutEmuSpeedToggle  = "Prze��czaj pomi�dzy maksymaln� pr�dko�ci� emulacji";
    ls->shortcutEmuSpeedNormal  = "Normalna pr�dko�� emulacji";
    ls->shortcutEmuSpeedInc     = "Zwi�ksz pr�dko�� emulacji";
    ls->shortcutEmuSpeedDec     = "Zmniejsz pr�dko�� emulacji";
    ls->shortcutShowEmuProp     = "Wy�wiertl okno w�a�ciwo�ci";
    ls->shortcutShowVideoProp   = "Wy�wiertl ustawienia obrazu";
    ls->shortcutShowAudioProp   = "Wy�wiertl ustawienia d�wi�ku";
    ls->shortcutShowCtrlProp    = "Wy�wiertl ustawienia kontroli(???)";
    ls->shortcutShowPerfProp    = "Wy�wiertl ustawienia szybko�ci(???)";
    ls->shortcutShowSettProp    = "Wy�wiertl ustawienia";
    ls->shortcutShowLanguage    = "Wy�wiertl ustawienia j�zyka";
    ls->shortcutShowMachines    = "Wy�wiertl Edytor Komputer�w";
    ls->shortcutShowShortcuts   = "Wy�wiertl Edytor Skr�t�w";
    ls->shortcutShowHelp        = "Wy�wiertl Pomoc";
    ls->shortcutShowAbout       = "Wy�wiertl informacje O programie";
    
    ls->shortcutSpecialMenu1    = "Wy�wiertl specjalne menu 1-go kartrid�a";
    ls->shortcutSpecialMenu2    = "Wy�wiertl specjalne menu 2-go kartrid�a";
    ls->shortcutVolumeStereo    = "Prze��cz mono/stereo";
    ls->shortcutThemeSwitch     = "Zmie� temat :)";
    ls->shortcutToggleSpriteEnable = "Poka�/ukryj sprite'y";
    
    ls->shortcutShowApearProp   = "Wy�wietl w�a�ciwo�ci wygl�du";
    ls->menuPropsApearance      = "Wygl�d";
    ls->propApearance           = "Wygl�d";
    ls->propThemeGB             = "Temat ";
    ls->propTheme               = "Temat:";
    ls->propThemeClassic        = "Klasyczny";
    ls->propThemeBlue           = "DIGIDIGIblue";

    ls->propMonBrightness       = "Jasno��:";
    ls->propMonContrast         = "Kontrast:";
    ls->propMonSaturation       = "Nasycenie:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanlines(???):";

    ls->dlgRomType              = "Typ romu:";
    ls->propOpenRomGB           = "Otw�rz okno romu(???) ";
    ls->propDefaultRomType      = "Domy�lny typ romu:";
    ls->propGuessRomType        = "Odgadnij typ romu";

    ls->propFile                = "Pliki";
    ls->propSettDefSlotGB       = "Przeci�gnij-i-upu�� ";
    ls->propSettDefSlots        = "W�� rom do:";
    ls->propSettDefSlot1        = " Slot 1";
    ls->propSettDefSlot2        = " Slot 2";
    ls->propSettDefDrives       = "W�� dyskietk� do:";
    ls->propSettDefDriveA       = " stacji A";
    ls->propSettDefDriveB       = " stacji B";
    ls->menuPropsFile           = "Pliki";
    ls->shortcutShowFiles       = "Poka� w�a�ciwo�ci pliku";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "Pod��cz folder";
    ls->shortcutDiskDirInsertA  = "Pod��cz folder jako dyskietk� A";
    ls->shortcutDiskDirInsertB  = "Pod��cz folder jako dyskietk� B";
    ls->propMonDeInterlace      = " Usuwaj przeplot";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "Pauza (???)";
    ls->shortcutSizeMinimized   = "Minimalizuj okno";
    ls->shortcutEmuSpeedToggle  = "Prze��cz maksymaln� pr�dko�� emulacji";
    ls->shortcutToggleCpuTrace  = "W�./wy�. �ledzenie CPU";

    ls->enumVideoEmuMonitor     = "Monitor";

    ls->propEmuPauseSwitch      = " Prze��cznik pauzy";
    ls->propVideoFreqText       = "Cz�stotliwo�� obrazu:";
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

    ls->propPriorityBoost       = " Podnie� priorytet blueMSX";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "Wy��cz timing stacji dyskietek";
    ls->shortcutToggleFdcTiming = "W�./wy�. timing stacji dyskietek";
    ls->propUseRegistry         = "Zapisuj konfiguracj� w rejestrze";

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

    ls->discardChanges          = "Czy chcesz zniszczy� zmiany?";
    ls->overwriteConfig         = "Czy chcesz nadpisac bierz�ca konfiguracj�?";

    ls->confSaveAsTitle         = "Zapisz konfiguracj� jako...";
    ls->confSaveAsName          = "Nzawa:";

    ls->menuToolsKeyboard       = "Edytor klawiatury";
    ls->shortcutShowKeyboard    = "Poka� edytor klawiatury";

    ls->menuVideoSource         = "�r�d�o obrazu";
    ls->menuVideoSourceDefault  = "Nie pod��czono �r�d�a obrazu";
    ls->menuVideoChipAutodetect = "Autodetekcja ko�ci obrazu";
    ls->propFullscreenResText   = "Rozdzielczo�� dla pe�nego ekranu:";
    ls->dlgSavePreview          = "Poka� podgl�d";
    ls->dlgSaveDate             = "Czas zapisu (zapisany???):";
    
    ls->enumVideoMonAmber       = "Miodowy (???)";

    ls->menuPropsPorts          = "Porty";
    ls->propPortsLptGB          = "Port r�wnoleg�y ";
    ls->propPortsComGB          = "Port szeregowy ";
    ls->propPortsLptText        = "Port:";
    ls->propPortsCom1Text       = "Port 1:";

    ls->shortcutShowDebugger    = "Poka� Debugger";
    ls->shortcutShowTrainer     = "Wy�wietl Trainer (???)";
    ls->shortcutShowPorts       = "Wy�wietl w�a�ciwo�ci port�w";
    
    ls->propPorts               = "Ports";
    ls->propPortsNone           = "Brak";

    // New entries in 2.3
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle";

    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "Drukuj do pliku";
    ls->propPortsOpenLogFile    = "Otw�rz plik logu";
    ls->propPortsFilenameText   = "Nazwa pliku:";
    ls->propPortsEmulateMsxPrn  = "Emulacja:";

    ls->shortcutPrnFormFeed     = "Wysu� kartk� z drukarki";

    ls->menuPrnFormfeed         = "Wysu� papier";
    ls->menuFilePrn             = "Drukarka";

};


#endif


