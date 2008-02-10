/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageCatalan.h,v $
**
** $Revision: 1.1 $
**
** $Date: 2008-02-10 17:25:03 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2008 Daniel Vik
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
#ifndef LANGUAGE_CATALAN_H
#define LANGUAGE_CATALAN_H

#include "LanguageStrings.h"
 
void langInitCatalan(LanguageStrings* ls) 
{
    //----------------------
    // Language lines
    //----------------------


    ls->langCatalan             = "Catalan";
    ls->langChineseSimplified   = "Xinès simplificat";
    ls->langChineseTraditional  = "Xinès tradicional";
    ls->langDutch               = "Neerlandès";
    ls->langEnglish             = "Anglès";
    ls->langFinnish             = "Finlandès";
    ls->langFrench              = "Francès";
    ls->langGerman              = "Alemany";
    ls->langItalian             = "Italià";
    ls->langJapanese            = "Japonès";
    ls->langKorean              = "Koreà";
    ls->langPolish              = "Polonès";
    ls->langPortuguese          = "Portuguès";
    ls->langSpanish             = "Espanyol";
    ls->langSwedish             = "Suec";


    //----------------------
    // Generic lines
    //----------------------


    ls->textDevice              = "Dispositiu:";
    ls->textFilename            = "Nom del fitxer:";
    ls->textFile                = "Fitxer";
    ls->textNone                = "Cap";
    ls->textUnknown             = "Desconegut";


    //----------------------
    // Warning and Error lines
    //----------------------


    ls->warningTitle            = "blueMSX - Avís";
    ls->warningDiscardChanges   = "Voleu descartar els canvis?";
    ls->warningOverwriteFile    = "Voleu sobreescriure el fitxer?:";
    ls->errorTitle              = "blueMSX - Error";
    ls->errorEnterFullscreen    = "No s'ha pogut entrar en el mode pantalla completa.           \n";
    ls->errorDirectXFailed      = "No s'ha pogut crear els objectes DirectX.           \nFent servir GDI.\nComprobeu les propietat del vídeo.";
    ls->errorNoRomInZip         = "No s'ha pogut trobar un fitxer .rom dins de l'arxiu zip.";
    ls->errorNoDskInZip         = "No s'ha pogut trobar un fitxer .dsk dins de l'arxiu zip.";
    ls->errorNoCasInZip         = "No s'ha pogut trobar un fitxer .cas dins de l'arxiu zip.";
    ls->errorNoHelp             = "No s'ha pogut trobar el fitxer d'ajuda de blueMSX.";
    ls->errorStartEmu           = "No s'ha pogut iniciar l'emulador MSX.";
    ls->errorPortableReadonly   = "El dispositiu portàtil és de només lectura";


    //----------------------
    // File related lines
    //----------------------


    ls->fileRom                 = "Imatge ROM";
    ls->fileAll                 = "Tots els fitxers";
    ls->fileCpuState            = "Estat de la CPU";
    ls->fileDisk                = "Imatge de disc";
    ls->fileCas                 = "Imatge de cinta";


    //----------------------
    // Menu related lines
    //----------------------


    ls->menuNoRecentFiles       = "- no hi ha fitxers recents -";
    ls->menuInsert              = "Insereix";
    ls->menuEject               = "Expulsa";


    ls->menuCartGameReader      = "Lector de jocs";
    ls->menuCartIde             = "IDE";
    ls->menuCartBeerIde         = "Beer";
    ls->menuCartGIde            = "GIDE";
    ls->menuCartSunriseIde      = "Sunrise";
    ls->menuCartSCC             = "Cartutx SCC";
    ls->menuCartSCCPlus         = "Cartutx SCC+";
    ls->menuCartFMPac           = "Cartutx FM-PAC";
    ls->menuCartPac             = "Cartutx PAC";
    ls->menuCartHBI55           = "Cartutx Sony HBI-55";
    ls->menuCartInsertSpecial   = "Insereix Especial";
    ls->menuCartMegaRam         = "MegaRAM";
    ls->menuCartExternalRam     = "RAM externa";


    ls->menuDiskInsertNew       = "Insereix una nova imatge de disc";
    ls->menuDiskDirInsert       = "Insereix directori";
    ls->menuDiskAutoStart       = "Reinicia després de la inserció";
    ls->menuCartAutoReset       = "Reinicia després de la inserció/expulsió";


    ls->menuCasRewindAfterInsert= "Rebobina després de la inserció";
    ls->menuCasUseReadOnly      = "Utilitza una imatge de casset només lectura";
    ls->lmenuCasSaveAs          = "Anomena i desa la imatge de casset...";
    ls->menuCasSetPosition      = "Estableix la posició";
    ls->menuCasRewind           = "Rebobina";


    ls->menuPrnFormfeed         = "Pàgina següent";


    ls->menuZoomNormal          = "Finestra petita";
    ls->menuZoomDouble          = "Finestra normal";
    ls->menuZoomFullscreen      = "Pantalla completa";
    

    ls->menuPropsEmulation      = "Emulació";
    ls->menuPropsVideo          = "Vídeo";
    ls->menuPropsSound          = "So";
    ls->menuPropsControls       = "Controls";
    ls->menuPropsPerformance    = "Rendiment";
    ls->menuPropsSettings       = "Paràmetres";
    ls->menuPropsFile           = "Fitxers";
    ls->menuPropsLanguage       = "Idioma";
    ls->menuPropsPorts          = "Ports";
    

    ls->menuVideoSource         = "Font de la sortida de vídeo";
    ls->menuVideoSourceDefault  = "No hi ha conectada cap font de sortida de vídeo";
    ls->menuVideoChipAutodetect = "Detecció automàtica del xip de vídeo";
    ls->menuVideoInSource       = "Font de la entrada de vídeo";
    ls->menuVideoInBitmap       = "Fitxer de mapa de bits";


    ls->menuHelpHelp            = "Temes d'ajuda";
    ls->menuHelpAbout           = "Al voltant de blueMSX";


    ls->menuFileCart            = "Ranura de cartutx";
    ls->menuFileDisk            = "Unitat de disc";
    ls->menuFileCas             = "Casset";
    ls->menuFilePrn             = "Impressora";
    ls->menuFileLoadState       = "Carrega l'estat de la CPU";
    ls->menuFileSaveState       = "Desa l'estat de la CPU";
    ls->menuFileQLoadState      = "Estat de càrrega ràpida";
    ls->menuFileQSaveState      = "Estat de desat ràpid";
    ls->menuFileCaptureAudio    = "Captura àudio";
    ls->menuFileScreenShot      = "Desa la captura de pantalla";
    ls->menuFileExit            = "Surt";


    ls->menuFileHarddisk        = "Disc dur";
    ls->menuFileHarddiskNoPesent= "No hi ha controladors";


    ls->menuRunRun              = "Executa";
    ls->menuRunPause            = "Posa en pausa";
    ls->menuRunStop             = "Atura";
    ls->menuRunSoftReset        = "Reinicialització suau";
    ls->menuRunHardReset        = "Reinicialització dura";
    ls->menuRunCleanReset       = "Reinicialització completa";


    ls->menuToolsMachine        = "Editor màquina";
    ls->menuToolsShortcuts      = "Editor de drecera";
    ls->menuToolsKeyboard       = "Controladors / editor de teclat";
    ls->menuToolsMixer          = "Mesclador";
    ls->menuToolsDebugger       = "Depurador";               // New in 2.5
    ls->menuToolsTrainer        = "Trainer";                // New in 2.5
    ls->menuToolsTraceLogger    = "Trace Logger";           // New in 2.5


    ls->menuFile                = "Fitxer";
    ls->menuRun                 = "Emulació";
    ls->menuWindow              = "Finestra";
    ls->menuOptions             = "Opcions";
    ls->menuTools               = "Eines";
    ls->menuHelp                = "Ajuda";
    

    //----------------------
    // Dialog related lines
    //----------------------


    ls->dlgOK                   = "D'acord";
    ls->dlgOpen                 = "Obri";
    ls->dlgCancel               = "Cancel·la";
    ls->dlgSave                 = "Desa";
    ls->dlgSaveAs               = "Anomena i desa...";
    ls->dlgRun                  = "Executa";
    ls->dlgClose                = "Tanca";


    ls->dlgLoadRom              = "blueMSX - Selecciona i carrega una imatge rom";
    ls->dlgLoadDsk              = "blueMSX - Selecciona i carrega una imatge dsk";
    ls->dlgLoadCas              = "blueMSX - Selecciona i carrega una imatge cas";
    ls->dlgLoadRomDskCas        = "blueMSX - Selecciona i carrega una imatge rom, dsk, o cas";
    ls->dlgLoadRomDesc          = "Tria i carrega una imatge rom:";
    ls->dlgLoadDskDesc          = "Tria i carrega una imatge de disc:";
    ls->dlgLoadCasDesc          = "Tria i carrega una imatge de cinta:";
    ls->dlgLoadRomDskCasDesc    = "Tria i carrega una imatge rom, de disc o de cinta:";
    ls->dlgLoadState            = "Carrega l'estat";
    ls->dlgSaveState            = "Anomena i desa l'estat...";
    ls->dlgSaveCassette         = "blueMSX - Desa la imatge de cinta";
    ls->dlgInsertRom1           = "Insereix el cartutx ROM en la ranura 1";
    ls->dlgInsertRom2           = "Insereix el cartutx ROM en la ranura 2";
    ls->dlgInsertDiskA          = "Insereix la imatge de disc en la unitat A";
    ls->dlgInsertDiskB          = "Insereix la imatge de disc en la unitat B";
    ls->dlgInsertHarddisk       = "Insereix el disc dur";
    ls->dlgInsertCas            = "Insereix una cinta de casset";
    ls->dlgRomType              = "Tipus de Rom:";


    ls->dlgTapeTitle            = "blueMSX - Posició de la cinta";
    ls->dlgTapeFrameText        = "Posició de la cinta";
    ls->dlgTapeCurrentPos       = "Posció actual";
    ls->dlgTapeTotalTime        = "Temps total";
    ls->dlgTapeSetPosText       = "Posició de la cinta:";
    ls->dlgTapeCustom           = "Mostra els fitxers personalitzats";
    ls->dlgTabPosition          = "Posició";	
    ls->dlgTabType              = "Tipus";
    ls->dlgTabFilename          = "Nom del fitxer:";
    ls->dlgZipReset             = "Reinicia després de la inserció";


    ls->dlgAboutTitle           = "blueMSX - Al voltant de";


    ls->dlgLangLangText         = "Tria el idioma que blueMSX emprarà";
    ls->dlgLangLangTitle        = "blueMSX - Idioma";


    ls->dlgAboutAbout           = "AL VOLTANT DE\r\n====";
    ls->dlgAboutVersion         = "Versió:";
    ls->dlgAboutBuildNumber     = "Muntatge:";
    ls->dlgAboutBuildDate       = "Data:";
    ls->dlgAboutCreat           = "Creat per Daniel Vik";
    ls->dlgAboutDevel           = "DESENVOLUPADORS\r\n========";
    ls->dlgAboutThanks          = "AGRAÏMENTS ESPECIALS A\r\n============";
    ls->dlgAboutLisence         = "LLICÈNSIA\r\n"
                                  "======\r\n\r\n"
                                  "This software is provided 'as-is', without any express or implied "
                                  "warranty. In no event will the author(s) be held liable for any damages "
                                  "arising from the use of this software.\r\n\r\n"
                                  "Visit www.bluemsx.com for more details.";


    ls->dlgSavePreview          = "Mostra previsualització";
    ls->dlgSaveDate             = "Temps desat:";


    //----------------------
    // Properties related lines
    //----------------------


    ls->propTitle               = "blueMSX - Propietats";
    ls->propEmulation           = "Emulació";
    ls->propVideo               = "Vídeo";
    ls->propSound               = "So";
    ls->propControls            = "Controls";
    ls->propPerformance         = "Rendiment";
    ls->propSettings            = "Paràmetres";
    ls->propFile                = "Fitxers";
    ls->propPorts               = "Ports";
    

    ls->propEmuGeneralGB        = "General ";
    ls->propEmuFamilyText       = "Màquina MSX:";
    ls->propEmuMemoryGB         = "Memòria ";
    ls->propEmuRamSizeText      = "Mida de la RAM:";
    ls->propEmuVramSizeText     = "Mida de la VRAM:";
    ls->propEmuSpeedGB          = "Velocitat d'emulació ";
    ls->propEmuSpeedText        = "Velocitat d'emulació ";
    ls->propEmuFrontSwitchGB    = "Commutadors Panasonic ";
    ls->propEmuFrontSwitch      = " Commutador frontal";
    ls->propEmuFdcTiming        = "Desactiva la sincronització de la unitat de disc";
    ls->propEmuPauseSwitch      = " Commutador de pausa";
    ls->propEmuAudioSwitch      = " Commutador del cartutx MSX-AUDIO";
    ls->propVideoFreqText       = "Freqüència de vídeo:";
    ls->propVideoFreqAuto       = "Auto";
    ls->propSndOversampleText   = "Sobremostra:";
    ls->propSndYkInGB           = "YK-01/YK-10/YK-20 In ";
    ls->propSndMidiInGB         = "MIDI In ";
    ls->propSndMidiOutGB        = "MIDI Out ";
    ls->propSndMidiChannel      = "Canal MIDI:";
    ls->propSndMidiAll          = "Tot";


    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Tipus de monitor:";
    ls->propMonEmuText          = "Emulació del monitor:";
    ls->propVideoTypeText       = "Tipus de vídeo:";
    ls->propWindowSizeText      = "Mida de la finestra:";
    ls->propMonHorizStretch     = " Ampliació horitzontal";
    ls->propMonVertStretch      = " Ampliació vertical";
    ls->propMonDeInterlace      = " Desentrellaçat";
    ls->propBlendFrames         = " Barreja els marcs consecutius";
    ls->propMonBrightness       = "Lluminositat:";
    ls->propMonContrast         = "Contrast:";
    ls->propMonSaturation       = "Saturació:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Línies d'exploració:";
    ls->propMonColorGhosting    = "Modulador RF";
    ls->propMonEffectsGB        = "Efectes ";


    ls->propPerfVideoDrvGB      = "Controlador de vídeo ";
    ls->propPerfVideoDispDrvText= "Controlador de visualització:";
    ls->propPerfFrameSkipText   = "Omissió de marcs:";
    ls->propPerfAudioDrvGB      = "Controlador d'àudio ";
    ls->propPerfAudioDrvText    = "Controlador de so:";
    ls->propPerfAudioBufSzText  = "Mida de la memòria intermèdia de so:";
    ls->propPerfEmuGB           = "Emulació ";
    ls->propPerfSyncModeText    = "Mode SYNC:";
    ls->propFullscreenResText   = "Resolució a pantalla completa:";


    ls->propSndChipEmuGB        = "Emulació del xip de so ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";
    ls->propSndMoonsound        = " Moonsound";
    ls->propSndMt32ToGm         = " Mapeja MT-32 instruments a General MIDI";


    ls->propPortsLptGB          = "Port paral·lel ";
    ls->propPortsComGB          = "Ports sèrie ";
    ls->propPortsLptText        = "Port:";
    ls->propPortsCom1Text       = "Port 1:";
    ls->propPortsNone           = "Cap";
    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "Imprimeix a un fitxer";
    ls->propPortsComFile        = "Envia a un fitxer";
    ls->propPortsOpenLogFile    = "Obri el fitxer de registre";
    ls->propPortsEmulateMsxPrn  = "Emulació";


    ls->propSetFileHistoryGB    = "Historial del fitxer ";
    ls->propSetFileHistorySize  = "Nombre d'elements en el historial del fitxer:";
    ls->propSetFileHistoryClear = "Neteja l'historial";
    ls->propFileTypes           = " Registra els tipus de fitxer amb blueMSX (.rom, .dsk, .cas, .sta)";
    ls->propWindowsEnvGB        = "Entorn Windows "; 
    ls->propSetScreenSaver      = " Desactiva l'estalvi de pantalla quan s'execute blueMSX";
    ls->propDisableWinKeys      = " Funció automàtica MSX per les tecles de menú de Windows";  
    ls->propPriorityBoost       = " Augmenta la prioritat de blueMSX";
    ls->propScreenshotPng       = " Empra captures de pantalla Portable Network Graphics (.png)";
    ls->propClearHistory        = "Esteu segur que voleu buidar l'historial del fitxer ?";
    ls->propOpenRomGB           = "Obri el diàlog Rom ";
    ls->propDefaultRomType      = "Tipus predeterminat de Rom:";
    ls->propGuessRomType        = "Endevina el tipus de Rrom";


    ls->propSettDefSlotGB       = "Arrossega i deixa anar ";
    ls->propSettDefSlots        = "Insereix el Rom en:";
    ls->propSettDefSlot         = " Ranura";
    ls->propSettDefDrives       = "Insereix el disquet en:";
    ls->propSettDefDrive        = " Unitat";


    ls->propThemeGB             = "Tema ";
    ls->propTheme               = "Tema ";


    //----------------------
    // Dropdown related lines
    //----------------------


    ls->enumVideoMonColor       = "Color";
    ls->enumVideoMonGrey        = "Blanc i negre";
    ls->enumVideoMonGreen       = "Verd";
    ls->enumVideoMonAmber       = "Ambre";


    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";


    ls->enumVideoEmuNone        = "Cap";
    ls->enumVideoEmuYc          = "Cable Y/C (nítid)";
    ls->enumVideoEmuMonitor     = "Monitor";
    ls->enumVideoEmuYcBlur      = "Cable Y/C sorollós (nítid)";
    ls->enumVideoEmuComp        = "Compost (borrós)";
    ls->enumVideoEmuCompBlur    = "Compost sorollós (borrós)";
    ls->enumVideoEmuScale2x     = "Escala 2x";
    ls->enumVideoEmuHq2x        = "Hq2x";


    ls->enumVideoSize1x         = "Normal - 320x200";
    ls->enumVideoSize2x         = "Doble - 640x400";
    ls->enumVideoSizeFullscreen = "Pantalla completa";


    ls->enumVideoDrvDirectDrawHW= "Acceleració DirectDraw de maquinari";  
    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";


    ls->enumVideoFrameskip0     = "Cap";
    ls->enumVideoFrameskip1     = "1 marc";
    ls->enumVideoFrameskip2     = "2 marcs";
    ls->enumVideoFrameskip3     = "3 marcs";
    ls->enumVideoFrameskip4     = "4 marcs";
    ls->enumVideoFrameskip5     = "5 marcs";


    ls->enumSoundDrvNone        = "Sense so";
    ls->enumSoundDrvWMM         = "Controlador WMM";
    ls->enumSoundDrvDirectX     = "Controlador DirectX";


    ls->enumEmuSync1ms          = "Sincronitza al refresc de MSX";
    ls->enumEmuSyncAuto         = "Auto (ràpid)";
    ls->enumEmuSyncNone         = "Cap";
    ls->enumEmuSyncVblank       = "Sincronització sobre PC Vertical Blank";
    ls->enumEmuAsyncVblank      = "Desincronització PC Vblank";             // New in 2.5


    ls->enumControlsJoyNone     = "Cap";
    ls->enumControlsJoyMouse    = "Ratolí";
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle";
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey Dongle";
    ls->enumControlsJoy2Button = "Palanca de control de 2 botons";                   // New in 2.5
    ls->enumControlsJoyGunstick  = "Gun Stick";                         // New in 2.5
    ls->enumControlsJoyAsciiLaser="ASCII Plus-X Terminator Laser";      // New in 2.5
    ls->enumControlsJoyColeco = "Palanca de control ColecoVision";                // New in 2.5


    ls->enumDiskMsx35Dbl9Sect    = "MSX 3.5 dues cares, 9 sectors";     // New in 2.5
    ls->enumDiskMsx35Dbl8Sect    = "MSX 3.5 dues cares, 8 sectors";     // New in 2.5
    ls->enumDiskMsx35Sgl9Sect    = "MSX 3.5 una cara, 9 sectors";     // New in 2.5
    ls->enumDiskMsx35Sgl8Sect    = "MSX 3.5 una cara, 8 sectors";     // New in 2.5
    ls->enumDiskSvi525Dbl        = "SVI-328 5.25 dues cares";           // New in 2.5
    ls->enumDiskSvi525Sgl        = "SVI-328 5.25 una cara";           // New in 2.5


    //----------------------
    // Configuration related lines
    //----------------------


    ls->confTitle               = "blueMSX - Editor de configuració de la màquina";
    ls->confConfigText          = "Nom del perfil";
    ls->confSlotLayout          = "Format de la ranura";
    ls->confMemory              = "Memòria";
    ls->confChipEmulation       = "Emulació del xip";
    ls->confChipExtras          = "Extras";


    ls->confOpenRom             = "Obri la imatge ROM";
    ls->confSaveTitle           = "blueMSX - Desa la configuració";
    ls->confSaveText            = "Voleu sobreescriure la configuració de la màquina? :";
    ls->confSaveAsTitle         = "Anomena i desa la configuració...";
    ls->confSaveAsMachineName   = "Nom de la màquina:";
    ls->confDiscardTitle        = "blueMSX - Configuració";
    ls->confExitSaveTitle       = "blueMSX - Surt de l'editor de configuració";
    ls->confExitSaveText        = "Voleu descartar els canvis de la configuració actual?";


    ls->confSlotLayoutGB        = "Format de la ranura";
    ls->confSlotExtSlotGB       = "Ranures externes ";
    ls->confBoardGB             = "Taula ";
    ls->confBoardText           = "Tipus de taula:";
    ls->confSlotPrimary         = "Primària";
    ls->confSlotExpanded        = "Expandida (quatre subranures)";


    ls->confSlotCart            = "Cartutx";
    ls->confSlot                = "Ranura";
    ls->confSubslot             = "Subranura";


    ls->confMemAdd              = "Afegeix...";
    ls->confMemEdit             = "Edita...";
    ls->confMemRemove           = "Elimina";
    ls->confMemSlot             = "Ranura";
    ls->confMemAddresss         = "Adreça";
    ls->confMemType             = "Tipus";
    ls->confMemRomImage         = "Imatge rom";


    ls->confChipVideoGB          = "Vídeo";
    ls->confChipVideoChip        = "Xip de vídeo:";
    ls->confChipVideoRam         = "RAM de vídeo:";
    ls->confChipSoundGB          = "So";


    ls->confCmosGB               = "Xip del rellotge ";
    ls->confCmosEnable           = " Activa el xip del rellotge";
    ls->confCmosBattery          = " Utilitza la bateria carregada";


    ls->confCpuFreqGB            = "Freqüència de la CPU ";
    ls->confZ80FreqText          = "Freqüència del Z80:";
    ls->confR800FreqText         = "Freqüència del R800:";
    ls->confFdcGB                = "Controlador del disquet ";
    ls->confCFdcNumDrivesText    = "Nombre d'unitats:";


    ls->confEditMemTitle         = "blueMSX - Edita el mapejador";
    ls->confEditMemGB            = "Detalls del mapejador ";
    ls->confEditMemType          = "Tipus:";
    ls->confEditMemFile          = "Fitxer:";
    ls->confEditMemAddress       = "Adreça";
    ls->confEditMemSize          = "Mida";
    ls->confEditMemSlot          = "Ranura";


    //----------------------
    // Shortcut lines
    //----------------------


    ls->shortcutKey             = "Acció";
    ls->shortcutDescription     = "Drecera";


    ls->shortcutSaveConfig      = "blueMSX - Desa la configuració";
    ls->shortcutOverwriteConfig = "Voleu sobreescriure la configuració de drecera? :";
    ls->shortcutExitConfig      = "blueMSX - Surt de l'editor de drecera";
    ls->shortcutDiscardConfig   = "Voleu descartar els canvis de la configuració actual?";
    ls->shortcutSaveConfigAs    = "blueMSX - Anomena i desa la configuració de drecera...";
    ls->shortcutConfigName      = "Nom de la configuració:";
    ls->shortcutNewProfile      = "< Nou perfil >";
    ls->shortcutConfigTitle     = "blueMSX - Editor de mapatge de drecera";
    ls->shortcutAssign          = "Assigna";
    ls->shortcutPressText       = "Prem la tecla(es) de drecera:";
    ls->shortcutScheme          = "Esquema de mapatge:";
    ls->shortcutCartInsert1     = "Inserta el cartutx 1";
    ls->shortcutCartRemove1     = "Trau el cartutx 1";
    ls->shortcutCartInsert2     = "Inserta el cartutx 2";
    ls->shortcutCartRemove2     = "Trau el cartutx 2";
    ls->shortcutSpecialMenu1    = "Mostra el menú especial per al cartutx 1";
    ls->shortcutSpecialMenu2    = "Mostra el menú especial per al cartutx 2";
    ls->shortcutCartAutoReset   = "Reinicia l'emulador quan s'inserisca el cartutx";
    ls->shortcutDiskInsertA     = "Inseriu el disquet A";
    ls->shortcutDiskDirInsertA  = "Inseriu el directori com a disquet A";
    ls->shortcutDiskRemoveA     = "Expulsa el disquet A";
    ls->shortcutDiskChangeA     = "Expulsa ràpid el disquet A";
    ls->shortcutDiskAutoResetA  = "Reinicia l'emulador quan s'inserisca el disquet";
    ls->shortcutDiskInsertB     = "Inseriu el disquet B";
    ls->shortcutDiskDirInsertB  = "Inseriu el directori com a disquet B";
    ls->shortcutDiskRemoveB     = "Expulsa el disquet B";
    ls->shortcutCasInsert       = "Inseriu el casset";
    ls->shortcutCasEject        = "Expulsa el casset";
    ls->shortcutCasAutorewind   = "Commuta el rebobinat automàtic en el casset";
    ls->shortcutCasReadOnly     = "Commuta el casset només de lectura";
    ls->shortcutCasSetPosition  = "Estableix la posició de la cinta";
    ls->shortcutCasRewind       = "Rebobina el casset";
    ls->shortcutCasSave         = "Desa la imatge del casset";
    ls->shortcutPrnFormFeed     = "Pas a la pàgina següent";
    ls->shortcutCpuStateLoad    = "Carrega l'estat de la CPU";
    ls->shortcutCpuStateSave    = "Desa l'estat de la CPU";
    ls->shortcutCpuStateQload   = "Carrega ràpid l'estat de la CPU";
    ls->shortcutCpuStateQsave   = "Desa ràpid l'estat de la CPU";
    ls->shortcutAudioCapture    = "Inicia/atura la captura d'àudio";
    ls->shortcutScreenshotOrig  = "Fes una captura de pantalla";
    ls->shortcutScreenshotSmall = "Captura de pantalla petita no filtrada";
    ls->shortcutScreenshotLarge = "Captura de pantalla gran no filtrada";
    ls->shortcutQuit            = "Surt de blueMSX";
    ls->shortcutRunPause        = "Executa/posa en pausa l'emulació";
    ls->shortcutStop            = "Atura l'emulació";
    ls->shortcutResetHard       = "Reinicialització dura";
    ls->shortcutResetSoft       = "Reinicialització suau";
    ls->shortcutResetClean      = "Reinicialització completa";
    ls->shortcutSizeSmall       = "Fixa la dimensió de finestra petita";
    ls->shortcutSizeNormal      = "Fixa la dimensió de finestra normal";
    ls->shortcutSizeFullscreen  = "Fixa la pantalla completa";
    ls->shortcutSizeMinimized   = "Minimitza la finestra";
    ls->shortcutToggleFullscren = "Commuta la pantalla completa";
    ls->shortcutVolumeIncrease  = "Augmenta el volum";
    ls->shortcutVolumeDecrease  = "Redueix el volum";
    ls->shortcutVolumeMute      = "Silencia el so";
    ls->shortcutVolumeStereo    = "Commuta mono/estèreo";
    ls->shortcutSwitchMsxAudio  = "Commuta el commutador MSX-AUDIO";
    ls->shortcutSwitchFront     = "Commuta el commutador frontal Panasonic";
    ls->shortcutSwitchPause     = "Commuta el commutador de pausa";
    ls->shortcutToggleMouseLock = "Commuta el blocatge del ratolí";
    ls->shortcutEmuSpeedMax     = "Velocitat d'emulació màxima";
    ls->shortcutEmuSpeedToggle  = "Commuta la velocitat d'emulació màxima";
    ls->shortcutEmuSpeedNormal  = "Velocitat d'emulació normal";
    ls->shortcutEmuSpeedInc     = "Augmenta la velocitat d'emulació";
    ls->shortcutEmuSpeedDec     = "Redueix la velocitat d'emulació";
    ls->shortcutThemeSwitch     = "Commuta el tema";
    ls->shortcutShowEmuProp     = "Mostra les propietats d'emulació";
    ls->shortcutShowVideoProp   = "Mostra les propietats de vídeo";
    ls->shortcutShowAudioProp   = "Mostra les propietats d'àudio";
    ls->shortcutShowCtrlProp    = "Mostra les propietats dels controls";
    ls->shortcutShowPerfProp    = "Mostra les propietats del rendiment";
    ls->shortcutShowSettProp    = "Mostra les propietats dels paràmetres";
    ls->shortcutShowPorts       = "Mostra les propietats dels ports";
    ls->shortcutShowLanguage    = "Mostra el diàlog de l'idioma";
    ls->shortcutShowMachines    = "Mostra l'editor de la màquina";
    ls->shortcutShowShortcuts   = "Mostra l'editor de drecera";
    ls->shortcutShowKeyboard    = "Mostra l'editor de controladors / teclat";
    ls->shortcutShowMixer       = "Mostra el mesclador";
    ls->shortcutShowDebugger    = "Mostra el depurador";
    ls->shortcutShowTrainer     = "Mostrar Trainer";
    ls->shortcutShowHelp        = "Mostra el diàlog d'ajuda";
    ls->shortcutShowAbout       = "Mostra el diàlog 'Quant a'";    
    ls->shortcutShowFiles       = "Mostra les propietats dels fitxers";
    ls->shortcutToggleSpriteEnable = "Mostra/Amaga els Sprites";
    ls->shortcutToggleFdcTiming = "Activa/Desactiva la sincronització de la unitat de disc";
    ls->shortcutToggleCpuTrace  = "Activa/Desactiva el rastre de la CPU";


    //----------------------
    // Keyboard config lines
    //----------------------    
 

    ls->keyconfigSelectedKey    = "Tecla seleccionada:";
    ls->keyconfigMappedTo       = "Mapejat a:";
    ls->keyconfigMappingScheme  = "Esquema de mapatge:";

    
    //----------------------
    // Rom type lines
    //----------------------


    ls->romTypeStandard         = "Estàndard";
    ls->romTypeZenima80         = "Zemina 80 in 1";
    ls->romTypeZenima90         = "Zemina 90 in 1";
    ls->romTypeZenima126        = "Zemina 126 in 1";
    ls->romTypeKonamiGeneric    = "Konami Generic";
    ls->romTypeMirrored         = "ROM replicat";
    ls->romTypeNormal           = "ROM normal";
    ls->romTypeDiskPatch        = "Normal + pedaç de disc";
    ls->romTypeCasPatch         = "Normal + pedaç de casset";
    ls->romTypeTc8566afFdc      = "Controladora de disc TC8566AF";
    ls->romTypeMicrosolFdc      = "Controladora de disc Microsol";
    ls->romTypeNationalFdc      = "Controladora de disc National";
    ls->romTypePhilipsFdc       = "Controladora de disc Philips";
    ls->romTypeSvi738Fdc        = "Controladora de disc SVI-738";
    ls->romTypeMappedRam        = "RAM mapejada";
    ls->romTypeMirroredRam1k    = "1kB de RAM replicada";
    ls->romTypeNormalRam        = "RAM normal";
    ls->romTypeTurborPause      = "Pausa del Turbo-R";
    ls->romTypeF4deviceNormal   = "Dispositiu F4 normal";
    ls->romTypeF4deviceInvert   = "Dispositiu F4 invertit";
    ls->romTypeTurborTimer      = "Temporitzador del Turbo-R";
    ls->romTypeNormal4000       = "Normal 4000h";
    ls->romTypeNormalC000       = "Normal C000h";
    ls->romTypeExtRam           = "RAM externa";
    ls->romTypeExtRam512        = "RAM externa de 512kB";
    ls->romTypeExtRam1mb        = "RAM externa de 1MB";
    ls->romTypeExtRam2mb        = "RAM externa de 2MB";
    ls->romTypeExtRam4mb        = "RAM externa de 4MB";
    ls->romTypeSvi328Cart       = "Cartutx del SVI-328";
    ls->romTypeSvi328Fdc        = "Controladora de disc del SVI-328";
    ls->romTypeSvi328Prn        = "Impressora del SVI-328";
    ls->romTypeSvi328Uart       = "Port sèrie del SVI-328";
    ls->romTypeSvi328col80      = "Tarja de 80 columnes del SVI-328 80";
    ls->romTypeSvi727col80      = "Tarja de 80 columnes del SVI-727";
    ls->romTypeColecoCart       = "Cartutx Coleco";
    ls->romTypeSg1000Cart       = "Cartutx SG-1000";
    ls->romTypeMsxPrinter       = "Impressora MSX";
    ls->romTypeTurborPcm        = "Xip PCM del Turbo-R";
    ls->romTypeNms8280Digitiz   = "Digitalitzador del Philips NMS-8280";
    ls->romTypeHbiV1Digitiz     = "Digitalitzador del Sony HBI-V1";
        
    //----------------------
    // Debug type lines
    // Note: Only needs translation if debugger is translated
    //----------------------

    ls->dbgMemRamNormal         = "Normal";
    ls->dbgMemRamMapped         = "Mapejat";
    ls->dbgMemYmf278            = "RAM de mostra del YMF278";
    ls->dbgMemAy8950            = "RAM de mosstra del AY8950";
    ls->dbgMemScc               = "Memòria";


    ls->dbgCallstack            = "Callstack";


    ls->dbgRegs                 = "Registres";
    ls->dbgRegsCpu              = "Registres de la CPU";
    ls->dbgRegsYmf262           = "Registres del YMF262";
    ls->dbgRegsYmf278           = "Registres del YMF278";
    ls->dbgRegsAy8950           = "Registres del AY8950";
    ls->dbgRegsYm2413           = "Registres del YM2413";


    ls->dbgDevRamMapper         = "Mapejador de RAM";
    ls->dbgDevRam               = "RAM";
    ls->dbgDevF4Device          = "Dispositiu F4";
    ls->dbgDevKorean80          = "Korean 80";
    ls->dbgDevKorean90          = "Korean 90";
    ls->dbgDevKorean128         = "Korean 128";
    ls->dbgDevFdcMicrosol       = "Microsol FDC";
    ls->dbgDevPrinter           = "Impressora";
    ls->dbgDevSviFdc            = "SVI FDC";
    ls->dbgDevSviPrn            = "Impressora del SVI";
    ls->dbgDevSvi80Col          = "80 columnes del SVI";
    ls->dbgDevRtc               = "RTC";
    ls->dbgDevTrPause           = "Pausa del TR";


    //----------------------
    // Debug type lines
    // Note: Can only be translated to european languages
    //----------------------


    ls->aboutScrollThanksTo     = "Agraïments especials a: ";
    ls->aboutScrollAndYou       = "i a TU !!!!";
};

#endif

