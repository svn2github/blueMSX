/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguagePolish.h,v $
**
** $Revision: 1.13 $
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
#ifndef LANGUAGE_POLISH_H
#define LANGUAGE_POLISH_H

#include "LanguageStrings.h"
 
void langInitPolish(LanguageStrings* ls) 
{
    //----------------------
    // Generic lines
    //----------------------

    ls->textDevice              = "Urz�dzenie:";
    ls->textFilename            = "Nazwa pliku:";
    ls->textFile                = "Plik";
    ls->textNone                = "Brak";
    ls->textUnknown             = "Unknown";                            // New in 2.5


    //----------------------
    // Warning and Error lines
    //----------------------

    ls->warningTitle             = "blueMSX - Uwaga";
    ls->warningDiscardChanges   = "Czy chcesz zniszczy� zmiany?";
    ls->warningOverwriteFile    = "Do you want to overwrite the file:"; // New in 2.5
    ls->errorTitle              = "blueMSX - b��d";
    ls->errorEnterFullscreen    = "Nie mog� prze��czy� na pe�ny ekran.           \n";
    ls->errorDirectXFailed      = "Nie mog� stworzy� obiekt�w DirectX.           \nPrze��czam w tryb GDI.\nSprawd� w�a�ciwo�ci wideo.";
    ls->errorNoRomInZip         = "Nie znaleziono pliku .rom w archiwum zip.";
    ls->errorNoDskInZip         = "Nie znaleziono pliku .dsk w archiwum zip.";
    ls->errorNoCasInZip         = "Nie znaleziono pliku .cas w archiwum zip.";
    ls->errorNoHelp             = "Nie znaleziono pliku pomocy blueMSX.";
    ls->errorStartEmu           = "Nie uda�o si� uruchomi� emulatora MSX.";
    ls->errorPortableReadonly   = "Portable device is readonly";        // New in 2.5


    //----------------------
    // File related lines
    //----------------------

    ls->fileRom                 = "ROM image";
    ls->fileAll                 = "Wszystkie pliki";
    ls->fileCpuState            = "Stan CPU";
    ls->fileDisk                = "Obraz dysku";
    ls->fileCas                 = "Obraz ta�my";


    //----------------------
    // Menu related lines
    //----------------------

    ls->menuNoRecentFiles       = "- brak ostatnich plik�w -";
    ls->menuInsert              = "Wybierz";
    ls->menuEject               = "Wysu�";

    ls->menuCartGameReader      = "Game Reader";                        // New in 2.5
    ls->menuCartIde             = "IDE";                                // New in 2.5
    ls->menuCartBeerIde         = "Beer";                               // New in 2.5
    ls->menuCartGIde            = "GIDE";                               // New in 2.5
    ls->menuCartSunriseIde      = "Sunrise";                            // New in 2.5
    ls->menuCartSCC             = "SCC Cartridge";
    ls->menuCartSCCPlus         = "SCC+ Cartridge";
    ls->menuCartFMPac           = "Kartrid� FM-PAC";
    ls->menuCartPac             = "Kartrid� PAC";
    ls->menuCartHBI55           = "Sony HBI-55 Cartridge";
    ls->menuCartInsertSpecial   = "Insert Special";                     // New in 2.5
    ls->menuCartMegaRam         = "MegaRAM";                            // New in 2.5
    ls->menuCartExternalRam     = "Zewn�trzny RAM";

    ls->menuDiskInsertNew       = "Insert New Disk Image";              // New in 2.5
    ls->menuDiskDirInsert       = "Podepnij folder";
    ls->menuDiskAutoStart       = "Resetuj po zmianie";
    ls->menuCartAutoReset       = "Resetuj po zmianie";
    
    ls->menuCasRewindAfterInsert = "Najpierw przewi� do pocz�tku";
    ls->menuCasUseReadOnly       = "U�ywaj kaset 'tylko do odczytu'";
    ls->lmenuCasSaveAs           = "Zapisz kaset� jako...";
    ls->menuCasSetPosition      = "Ustaw pozycj�";
    ls->menuCasRewind           = "Przewi� do pocz�tku";

    ls->menuPrnFormfeed         = "Wysu� papier";

    ls->menuZoomNormal          = "Standardowe";
    ls->menuZoomDouble          = "Podw�jne";
    ls->menuZoomFullscreen      = "Pe�ny ekran";
    
    ls->menuPropsEmulation      = "Emulacja";
    ls->menuPropsVideo          = "Obraz";
    ls->menuPropsSound          = "D�wi�k";
    ls->menuPropsControls       = "Sterowanie";
    ls->menuPropsPerformance    = "Wydajno��";
    ls->menuPropsSettings        = "Ustawienia";
    ls->menuPropsFile           = "Pliki";
    ls->menuPropsLanguage       = "J�zyk";
    ls->menuPropsPorts          = "Porty";
    
    ls->menuVideoSource         = "Video Out Source";                   // New in 2.5
    ls->menuVideoSourceDefault  = "No Video Out Source Connected";      // New in 2.5
    ls->menuVideoChipAutodetect = "Autodetekcja ko�ci obrazu";    
    ls->menuVideoInSource       = "Video In Source";                    // New in 2.5
    ls->menuVideoInBitmap       = "Bitmap File";                        // New in 2.5

    ls->menuHelpHelp            = "Tematy pomocy";
    ls->menuHelpAbout           = "O blueMSX...";

    ls->menuFileCart            = "Kartrid�";
    ls->menuFileDisk            = "Stacja dyskietek";
    ls->menuFileCas             = "Kaseta";
    ls->menuFilePrn             = "Drukarka";
    ls->menuFileLoadState       = "Wczytaj stan CPU";
    ls->menuFileSaveState       = "Zapisz stan CPU";
    ls->menuFileQLoadState      = "Szybki odczyt stanu";
    ls->menuFileQSaveState      = "Szybki zapis stanu";
    ls->menuFileCaptureAudio    = "Przechwy� d�wi�k";
    ls->menuFileScreenShot      = "Zapisz ekran";
    ls->menuFileExit            = "Wyj�cie";

    ls->menuFileHarddisk        = "Hard Disk";                          // New in 2.5
    ls->menuFileHarddiskNoPesent= "No Controllers Present";             // New in 2.5

    ls->menuRunRun              = "Uruchom";
    ls->menuRunPause            = "Pauza";
    ls->menuRunStop             = "Zatrzymaj";
    ls->menuRunSoftReset        = "Mi�kki reset";
    ls->menuRunHardReset        = "Twardy reset";
    ls->menuRunCleanReset       = "Pe�ny reset";

    ls->menuToolsMachine         = "Edytor komputer�w";
    ls->menuToolsShortcuts      = "Edytor skr�t�w klawiaturowych";
    ls->menuToolsKeyboard       = "Edytor klawiatury";
    ls->menuToolsMixer          = "Mikser";

    ls->menuFile                = "Plik";
    ls->menuRun                 = "Uruchamianie";
    ls->menuWindow              = "Okno";
    ls->menuOptions             = "Opcje";
    ls->menuTools                = "Narz�dzia";
    ls->menuHelp                = "Pomoc";
    

    //----------------------
    // Dialog related lines
    //----------------------

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Otw�rz";
    ls->dlgCancel               = "Anuluj";
    ls->dlgSave                 = "Zapisz";
    ls->dlgSaveAs               = "Zapisz jako...";
    ls->dlgRun                  = "Uruchom";
    ls->dlgClose                = "Zamknij";

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
    ls->dlgSaveCassette          = "blueMSX - Zapisz obraz kasety";
    ls->dlgInsertRom1           = "Wybierz kartrid� ROM dla slotu 1";
    ls->dlgInsertRom2           = "Wybierz kartrid� ROM dla slotu 2";
    ls->dlgInsertDiskA          = "Wybierz dyskietk� dla stacji A";
    ls->dlgInsertDiskB          = "Wybierz dyskietk� dla stacji B";
    ls->dlgInsertHarddisk       = "Insert Hard Disk";                   // New in 2.5
    ls->dlgInsertCas            = "Wybierz kaset�";
    ls->dlgRomType              = "Typ romu:";

    ls->dlgTapeTitle            = "blueMSX - Pozycja ta�my";
    ls->dlgTapeFrameText        = "Pozycja ta�my";
    ls->dlgTapeCurrentPos       = "Obecna pozycja";
    ls->dlgTapeTotalTime        = "Czas ca�kowity";
    ls->dlgTapeSetPosText        = "Pozycja ta�my:";
    ls->dlgTapeCustom            = "Poka� dowolne pliki";
    ls->dlgTabPosition           = "Pozycja";
    ls->dlgTabType               = "Typ";
    ls->dlgTabFilename           = "Nazwa pliku";
    ls->dlgZipReset             = "Resettuj po zmianie";

    ls->dlgAboutTitle           = "blueMSX - O programie";

    ls->dlgLangLangText         = "Wybierz j�zyk dla blueMSX";
    ls->dlgLangLangTitle        = "blueMSX - J�zyk";

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

    ls->dlgSavePreview          = "Poka� podgl�d";
    ls->dlgSaveDate             = "Czas zapisu:";


    //----------------------
    // Properties related lines
    //----------------------

    ls->propTitle               = "blueMSX - W�a�ciwo�ci";
    ls->propEmulation           = "Emulacja";
    ls->propVideo               = "Obraz";
    ls->propSound               = "D�wi�k";
    ls->propControls            = "Sterowanie";
    ls->propPerformance         = "Wydajno��";
    ls->propSettings             = "Ustawienia";
    ls->propFile                = "Pliki";
    ls->propPorts               = "Porty";
    
    ls->propEmuGeneralGB        = "Og�lne ";
    ls->propEmuFamilyText       = "Typ MSX:";
    ls->propEmuMemoryGB         = "Pami�� ";
    ls->propEmuRamSizeText      = "Rozmiar RAMu:";
    ls->propEmuVramSizeText     = "Rozmiar VRAMu:";
    ls->propEmuSpeedGB          = "Szybko�� emulacji ";
    ls->propEmuSpeedText        = "Szybko�� emulacji:";
    ls->propEmuFrontSwitchGB     = "Prze��czniki Panasonic ";
    ls->propEmuFrontSwitch       = " Prze��cznik g��wny";
    ls->propEmuFdcTiming        = "Wy��cz timing stacji dyskietek";
    ls->propEmuPauseSwitch      = " Prze��cznik pauzy";
    ls->propEmuAudioSwitch       = " Prze��cznik kartrid�a MSX-AUDIO";
    ls->propVideoFreqText       = "Cz�stotliwo�� obrazu:";
    ls->propVideoFreqAuto       = "Auto";
    ls->propSndOversampleText   = "Oversampling:";
    ls->propSndYkInGB           = "YK-01/YK-10/YK-20 In ";                // New in 2.5
    ls->propSndMidiInGB         = "MIDI In ";
    ls->propSndMidiOutGB        = "MIDI Out ";
    ls->propSndMidiChannel      = "MIDI Channel:";                      // New in 2.5
    ls->propSndMidiAll          = "All";                                // New in 2.5

    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Typ monitora:";
    ls->propMonEmuText          = "Emulacja monitora:";
    ls->propVideoTypeText       = "Typ obrazu:";
    ls->propWindowSizeText      = "Rozmiar okna:";
    ls->propMonHorizStretch      = " Rozci�gaj w poziomie";
    ls->propMonVertStretch       = " Rozci�gaj w pionie";
    ls->propMonDeInterlace      = " Usuwaj przeplot";
    ls->propMonBrightness       = "Jasno��:";
    ls->propMonColorGhosting    = "Modulator RF";
    ls->propMonContrast         = "Kontrast:";
    ls->propMonSaturation       = "Nasycenie:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Przeplot:";
    ls->propMonEffectsGB        = "Efekty ";

    ls->propPerfVideoDrvGB      = "Ustawienia Video";
    ls->propPerfVideoDispDrvText= "Sterownik obrazu:";
    ls->propPerfFrameSkipText   = "Gubienie klatek:";
    ls->propPerfAudioDrvGB      = "Ustawienia Audio";
    ls->propPerfAudioDrvText    = "Sterownik d�wi�ku:";
    ls->propPerfAudioBufSzText  = "Rozmiar bufora d�wi�ku:";
    ls->propPerfEmuGB           = "Emulacja ";
    ls->propPerfSyncModeText    = "Tryb synchronizacji:";
    ls->propFullscreenResText   = "Pe�ny ekran:";

    ls->propSndChipEmuGB        = "Emulacja d�wi�ku";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";
    ls->propSndMoonsound         = " Moonsound";
    ls->propSndMt32ToGm         = " Mapuj instrumenty MT-32 na General MIDI";

    ls->propPortsLptGB          = "Port r�wnoleg�y ";
    ls->propPortsComGB          = "Port szeregowy ";
    ls->propPortsLptText        = "Port:";
    ls->propPortsCom1Text       = "Port 1:";
    ls->propPortsNone           = "Brak";
    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "Drukuj do pliku";
    ls->propPortsComFile        = "Send to File";
    ls->propPortsOpenLogFile    = "Otw�rz plik logu";
    ls->propPortsEmulateMsxPrn  = "Emulacja:";

    ls->propSetFileHistoryGB     = "Historia plik�w ";
    ls->propSetFileHistorySize   = "Ilo�c element�w w historii plik�w:";
    ls->propSetFileHistoryClear  = "Wyczy�� histori�";
    ls->propFileTypes            = " Skoja� pliki z blueMSX (.rom, .dsk, .cas, .sta)";
    ls->propWindowsEnvGB         = "Otoczenie Windows "; 
    ls->propSetScreenSaver       = " Wy��cz wygaszacz podczas pracy blueMSX";
    ls->propDisableWinKeys       = " Automatyczna konfiguracja klawiszy Windows w MSX"; 
    ls->propPriorityBoost       = " Podnie� priorytet blueMSX";
    ls->propScreenshotPng       = " Use Portable Network Graphics (.png) screenshots";  // New in 2.5
    ls->propClearHistory         = "Na pewno wyczy�ci� histori� plik�w?";
    ls->propOpenRomGB           = "Okno wyboru romu ";
    ls->propDefaultRomType      = "Domy�lny typ romu:";
    ls->propGuessRomType        = "Odgadnij typ romu";

    ls->propSettDefSlotGB       = "Przeci�gnij-i-upu�� ";
    ls->propSettDefSlots        = "W�� rom do:";
    ls->propSettDefSlot         = " Slot";
    ls->propSettDefDrives       = "W�� dyskietk� do:";
    ls->propSettDefDrive        = " Stacji";

    ls->propThemeGB             = "Temat ";
    ls->propTheme               = "Temat:";


    //----------------------
    // Dropdown related lines
    //----------------------

    ls->enumVideoMonColor       = "Kolorowy";
    ls->enumVideoMonGrey        = "Czarno-bia�y";
    ls->enumVideoMonGreen       = "Zielony";
    ls->enumVideoMonAmber       = "Miodowy";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Brak";
    ls->enumVideoEmuYc          = "Kabel Y/C (ostry)";
    ls->enumVideoEmuMonitor     = "Monitor";
    ls->enumVideoEmuYcBlur      = "Zaszumiony kabel Y/C (ostry)";
    ls->enumVideoEmuComp        = "Kompozytowe (rozmyte)";
    ls->enumVideoEmuCompBlur    = "Zaszumione kompozytowe (rozmyte)";
    ls->enumVideoEmuScale2x     = "Skalowanie 2x";
    ls->enumVideoEmuHq2x        = "Hq2x";

    ls->enumVideoSize1x         = "Pojedyncza - 320x200";
    ls->enumVideoSize2x         = "Podw�jna - 640x400";
    ls->enumVideoSizeFullscreen = "Pe�ny ekran";

    ls->enumVideoDrvDirectDrawHW = "DirectDraw (sprz�towy)"; 
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

    ls->enumEmuSync1ms          = "Synchronizuj z od�wie�aniem MSX";
    ls->enumEmuSyncAuto         = "Auto (szybkie)";
    ls->enumEmuSyncNone         = "None";
    ls->enumEmuSyncVblank       = "Synchronizuj z synchronizacj� pionow� PC";
    ls->enumEmuAsyncVblank      = "Asynchronous PC Vblank";             // New in 2.5

    ls->enumControlsJoyNone     = "Brak";
    ls->enumControlsJoyMouse    = "Mysz";
    ls->enumControlsJoyTetris2Dongle = "Dongle Tetris 2";
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey Dongle";             // New in 2.5
    ls->enumControlsJoy2Button = "2-button Joystick";                   // New in 2.5
    ls->enumControlsJoyLightGun = "Light Gun";                          // New in 2.5
    ls->enumControlsJoyColeco = "ColecoVision Joystick";                // New in 2.5


    //----------------------
    // Configuration related lines
    //----------------------

    ls->confTitle                = "blueMSX - Edytor Konfiguracji Komputer�w";
    ls->confConfigText           = "Konfiguracja";
    ls->confSlotLayout           = "Uk�ad slot�w";
    ls->confMemory               = "Pami��";
    ls->confChipEmulation        = "Uk�ad obrazu";
    ls->confChipExtras          = "Extras";

    ls->confOpenRom             = "Otw�rz ROM";
    ls->confSaveTitle            = "blueMSX - Zapis konfiguracji";
    ls->confSaveText             = "Czy chcesz nadpisa� konfiguracj�:";
    ls->confSaveAsTitle         = "Zapisz konfiguracj� jako...";
    ls->confSaveAsMachineName    = "Nazwa komputera:";
    ls->confDiscardTitle         = "blueMSX - Konfiguracja";
    ls->confExitSaveTitle        = "blueMSX - Wyjd� z Edytora Konfiguracj";
    ls->confExitSaveText         = "Czy chcesz zignorowa� zmiany w bierz�cej konfiguracji?";

    ls->confSlotLayoutGB         = "Uk�ad slot�w ";
    ls->confSlotExtSlotGB        = "Zewn�trzne sloty ";
    ls->confBoardGB             = "Board ";
    ls->confBoardText           = "Board Type:";
    ls->confSlotPrimary          = "Podstawowy";
    ls->confSlotExpanded         = "Rozszerzone (cztery sub-sloty)";

    ls->confSlotCart             = "Kartrid�";
    ls->confSlot                = "Slot";
    ls->confSubslot             = "Podslot";

    ls->confMemAdd               = "Dodaj...";
    ls->confMemEdit              = "Edytuj...";
    ls->confMemRemove            = "Usu�";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Adres";
    ls->confMemType              = "Typ";
    ls->confMemRomImage          = "Obraz rom";
    
    ls->confChipVideoGB          = "Obraz ";
    ls->confChipVideoChip        = "Ko�� obrazu:";
    ls->confChipVideoRam         = "Pami�� RAM obrazu:";
    ls->confChipSoundGB          = "D�wi�k ";

    ls->confCmosGB                = "CMOS ";
    ls->confCmosEnable            = " Enable CMOS";
    ls->confCmosBattery           = " Use Charged Battery";

    ls->confCpuFreqGB            = "CPU Frequency ";
    ls->confZ80FreqText          = "Z80 Frequency:";
    ls->confR800FreqText         = "R800 Frequency:";
    ls->confFdcGB                = "Floppy Disk Controller ";
    ls->confCFdcNumDrivesText    = "Number of Drives:";

    ls->confEditMemTitle         = "blueMSX - Edytuj Mapper";
    ls->confEditMemGB            = "Konfiguracja Mappera";
    ls->confEditMemType          = "Typ:";
    ls->confEditMemFile          = "Plik:";
    ls->confEditMemAddress       = "Adres";
    ls->confEditMemSize          = "Rozmiar";
    ls->confEditMemSlot          = "Slot";


    //----------------------
    // Shortcut lines
    //----------------------

    ls->shortcutKey             = "Hotkey";
    ls->shortcutDescription     = "Skr�t";

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
    ls->shortcutSpecialMenu1    = "Wy�wietl specjalne menu 1-go kartrid�a";
    ls->shortcutSpecialMenu2    = "Wy�wietl specjalne menu 2-go kartrid�a";
    ls->shortcutCartAutoReset   = "Resetuj emulator przy wk�adaniu kartrid�a";
    ls->shortcutDiskInsertA     = "W�� dyskietk� A";
    ls->shortcutDiskDirInsertA  = "Pod��cz folder jako dyskietk� A";
    ls->shortcutDiskRemoveA     = "Wyjmij dyskietk� A";
    ls->shortcutDiskChangeA     = "Szybka zmiana dyskietki A";
    ls->shortcutDiskAutoResetA  = "Resetuj emulator przy wk�adaniu dyskietki A";
    ls->shortcutDiskInsertB     = "W�� dyskietk� B";
    ls->shortcutDiskDirInsertB  = "Pod��cz folder jako dyskietk� B";
    ls->shortcutDiskRemoveB     = "Wyjmij dyskietk� B";
    ls->shortcutCasInsert       = "W�� kaset�";
    ls->shortcutCasEject        = "Wyjmij kaset�";
    ls->shortcutCasAutorewind   = "Prze��cz auto-przewijanie kasety";
    ls->shortcutCasReadOnly     = "Prze��cz kaset� na 'tylko do odczytu'";
    ls->shortcutCasSetPosition  = "Ustaw pozycj� kasety";
    ls->shortcutCasRewind       = "Przewi� kaset�";
    ls->shortcutCasSave         = "Zapisz obraz kasety";
    ls->shortcutPrnFormFeed     = "Wysu� kartk� z drukarki";
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
    ls->shortcutSizeMinimized   = "Minimalizuj okno";
    ls->shortcutToggleFullscren = "Prze��czaj pe�ny ekran";
    ls->shortcutVolumeIncrease  = "Podg�o�nij d�wi�k";
    ls->shortcutVolumeDecrease  = "�cisz d�wi�k";
    ls->shortcutVolumeMute      = "Wy��cz d�wi�k";
    ls->shortcutVolumeStereo    = "Prze��cz mono/stereo";
    ls->shortcutSwitchMsxAudio  = "Prze��cznik MSX-AUDIO";
    ls->shortcutSwitchFront     = "Prze��cznik g��wny Panasonic";
    ls->shortcutSwitchPause     = "Pauza";
    ls->shortcutToggleMouseLock = "Przechwytywanie myszy";
    ls->shortcutEmuSpeedMax     = "Maksymalna pr�dko�� emulacji";
    ls->shortcutEmuSpeedToggle  = "Prze��cz maksymaln� pr�dko�� emulacji";
    ls->shortcutEmuSpeedNormal  = "Normalna pr�dko�� emulacji";
    ls->shortcutEmuSpeedInc     = "Zwi�ksz pr�dko�� emulacji";
    ls->shortcutEmuSpeedDec     = "Zmniejsz pr�dko�� emulacji";
    ls->shortcutThemeSwitch     = "Zmie� temat :)";
    ls->shortcutShowEmuProp     = "Wy�wietl okno w�a�ciwo�ci";
    ls->shortcutShowVideoProp   = "Wy�wietl ustawienia obrazu";
    ls->shortcutShowAudioProp   = "Wy�wietl ustawienia d�wi�ku";
    ls->shortcutShowCtrlProp    = "Wy�wietl ustawienia sterowania";
    ls->shortcutShowPerfProp    = "Wy�wietl ustawienia wydajno�ci";
    ls->shortcutShowSettProp    = "Wy�wietl ustawienia";
    ls->shortcutShowPorts       = "Wy�wietl w�a�ciwo�ci port�w";
    ls->shortcutShowLanguage    = "Wy�wietl ustawienia j�zyka";
    ls->shortcutShowMachines    = "Wy�wietl Edytor Komputer�w";
    ls->shortcutShowShortcuts   = "Wy�wietl Edytor Skr�t�w";
    ls->shortcutShowKeyboard    = "Poka� edytor klawiatury";
    ls->shortcutShowMixer       = "Poka� mikser";
    ls->shortcutShowDebugger    = "Poka� Debugger";
    ls->shortcutShowTrainer     = "Wy�wietl Trainer";
    ls->shortcutShowHelp        = "Wy�wietl Pomoc";
    ls->shortcutShowAbout       = "Wy�wietl informacje O programie";
    ls->shortcutShowFiles       = "Poka� w�a�ciwo�ci pliku";
    ls->shortcutToggleSpriteEnable = "Poka�/ukryj sprite'y";
    ls->shortcutToggleFdcTiming = "W�./wy�. timing stacji dyskietek";
    ls->shortcutToggleCpuTrace  = "W�./wy�. �ledzenie CPU";


    //----------------------
    // Keyboard config lines
    //----------------------

    ls->keyconfigSelectedKey    = "Wybrany klawisz:";
    ls->keyconfigMappedTo       = "Zmapowany na:";
    ls->keyconfigMappingScheme  = "Schemat mapowania:";
};

#endif
