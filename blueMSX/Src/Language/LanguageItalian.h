/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageItalian.h,v $
**
** $Revision: 1.20 $
**
** $Date: 2006-06-04 01:18:57 $
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
#ifndef LANGUAGE_ITALIAN_H
#define LANGUAGE_ITALIAN_H

#include "LanguageStrings.h"
 
void langInitItalian(LanguageStrings* ls) 
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

    ls->menuNoRecentFiles       = "- nessun file recente -";
    ls->menuInsert              = "Inserisci";
    ls->menuEject               = "Rimuovi";

    ls->menuCartAutoReset       = "Riavvia dopo aver inserito/rimosso";
    ls->menuCartFMPac           = "Cartuccia FM-PAC";
    ls->menuCartPac             = "Cartuccia PAC";

    ls->menuDiskAutoStart       = "Riavvia dopo l'inserimento";
    
    ls->menuCasSetPosition      = "Imposta la posizione";
    ls->menuCasRewind           = "Riavvolgi";

    ls->menuZoomNormal          = "Dimensione normale";
    ls->menuZoomDouble          = "Dimensione doppia";
    ls->menuZoomFullscreen      = "Schermo intero";
    
    ls->menuPropsEmulation      = "Emulazione";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Audio";
    ls->menuPropsControls       = "Controlli";
    ls->menuPropsPerformance    = "Prestazioni";
    ls->menuPropsLanguage       = "Linguaggi";
    
    ls->menuHelpHelp            = "Argomenti";
    ls->menuHelpAbout           = "Informazioni su blueMSX";

    ls->menuFileCart            = "Cartuccia Slot";
    ls->menuFileDisk            = "Disco floppy";
    ls->menuFileCas             = "Cassetta";
    ls->menuFileLoadState       = "Carica lo stato della CPU";
    ls->menuFileSaveState       = "Salva lo stato della CPU";
    ls->menuFileQLoadState      = "Carica rapidamente lo stato";
    ls->menuFileQSaveState      = "Salva rapidamente lo stato";
    ls->menuFileCaptureAudio    = "Cattura l'audio";
    ls->menuFileScreenShot      = "Salva la schermata";
    ls->menuFileExit            = "Esci";

    ls->menuRunRun              = "Esegui";
    ls->menuRunPause            = "Pausa";
    ls->menuRunStop             = "Ferma";
    ls->menuRunSoftReset        = "Riavvio software";
    ls->menuRunHardReset        = "Riavvio hardware";
    ls->menuRunCleanReset       = "Riavvio generale";

    ls->menuFile                = "File";
    ls->menuRun                 = "Esecuzione";
    ls->menuWindow              = "Finestra";
    ls->menuOptions             = "Opzioni";
    ls->menuHelp                = "Aiuto";
    
    ls->errorTitle              = "blueMSX - Errore";
    ls->errorEnterFullscreen    = "Non riesco ad attivare la visualizzazione a schermo intero.           \n";
    ls->errorDirectXFailed      = "Non riesco a creare gli oggetti DirectX.          \nUtilizzo GDI.\nControllo le proprietà Video.";
    ls->errorNoRomInZip         = "Nessun file .rom trovato nell'archivio zip.";
    ls->errorNoDskInZip         = "Nessun file .dsk trovato nell'archivio zip.";
    ls->errorNoCasInZip         = "Nessun file .cas trovato nell'archivio zip.";
    ls->errorNoHelp             = "Non trovo il file di Aiuto di blueMSX.";
    ls->errorStartEmu           = "Avvio dell'emulatore MSX fallito.";


    ls->dlgLoadRom              = "blueMSX - Seleziona un'immagine .rom da caricare";
    ls->dlgLoadDsk              = "blueMSX - Seleziona un'immagine dsk da caricare";
    ls->dlgLoadCas              = "blueMSX - Seleziona un'immagine cas da caricare";
    ls->dlgLoadRomDskCas        = "blueMSX - Seleziona un file .rom, .dsk, o .cas da caricare";
    ls->dlgLoadRomDesc          = "Scegli un'immagine .rom da caricare:";
    ls->dlgLoadDskDesc          = "Scegli un'immagine dischetto da caricare:";
    ls->dlgLoadCasDesc          = "Scegli un'immagine cassetta da caricare:";
    ls->dlgLoadRomDskCasDesc    = "Scegli l'immagine di una rom, di un dischetto, o di un nastro da caricare:";
    ls->dlgLoadState            = "Carica lo stato della CPU";
    ls->dlgSaveState            = "Salva lo stato della CPU";
    ls->dlgInsertRom1           = "Inserisci una cartuccia ROM nello slot 1";
    ls->dlgInsertRom2           = "Inserisci una cartuccia ROM nello slot 2";
    ls->dlgInsertDiskA          = "Inserisci un'immagine dischetto nell'unità A";
    ls->dlgInsertDiskB          = "Inserisci un'immagine dischetto nell'unità B";
    ls->dlgInsertCas            = "Inserisci un'immagine cassetta";

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Aprire";
    ls->dlgCancel               = "Annulla";

    ls->dlgTapeTitle            = "blueMSX - Posizione del nastro";
    ls->dlgTapeFrameText        = "Posizione del nastro";
    ls->dlgTapeCurrentPos       = "Posizione attuale";
    ls->dlgTapeTotalTime        = "Durata totale";

    ls->dlgZipReset             = "Riavvia dopo l'inserimento";

    ls->dlgAboutTitle           = "blueMSX - Informazioni";

    ls->dlgLangLangText         = "Scegli il linguaggio per l'interfaccia di blueMSX";
    ls->dlgLangLangTitle        = "blueMSX - Lingua";

    ls->propTitle               = "blueMSX - Proprietà";
    ls->propEmulation           = "Emulazione";
    ls->propVideo               = "Video";
    ls->propSound               = "Audio";
    ls->propControls            = "Controlli";
    ls->propPerformance         = "Prestazioni";
    
    ls->propEmuGeneralGB        = "Generale ";
    ls->propEmuFamilyText       = "Modello MSX:";
    ls->propEmuMemoryGB         = "Memoria ";
    ls->propEmuRamSizeText      = "Dimensioni della RAM:";
    ls->propEmuVramSizeText     = "Dimensioni della VRAM:";
    ls->propEmuSpeedGB          = "Velocità di emulazione ";
    ls->propEmuSpeedText        = "Velocità di emulazione:";

    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Tipo monitor:";
    ls->propMonEmuText          = "Emulazione monitor:";
    ls->propVideoTypeText       = "Tipo di video:";
    ls->propWindowSizeText      = "Dimensioni della finestra:";

    ls->propPerfVideoDrvGB      = "Driver video ";
    ls->propPerfVideoDispDrvText= "Driver per il video:";
    ls->propPerfFrameSkipText   = "Salto fotogrammi:";
    ls->propPerfAudioDrvGB      = "Driver audio ";
    ls->propPerfAudioDrvText    = "Driver per l'audio:";
    ls->propPerfAudioBufSzText  = "Dimensioni del buffer audio:";
    ls->propPerfEmuGB           = "Emulazione ";
    ls->propPerfSyncModeText    = "SYNC Modo sincronizzato:";

    ls->propSndChipEmuGB        = "Emulazione del chip audio ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";

    ls->enumVideoMonColor       = "Colore";
    ls->enumVideoMonGrey        = "Bianco e nero";
    ls->enumVideoMonGreen       = "Verde";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Nessuna";
    ls->enumVideoEmuYc          = "Cavo Y/C (Sharp)";
    ls->enumVideoEmuYcBlur      = "Cavo Y/C rumoroso (Sharp)";
    ls->enumVideoEmuComp        = "Composito (Sfocato)";
    ls->enumVideoEmuCompBlur    = "Composito rumoroso (Sfocato)";
    ls->enumVideoEmuScale2x     = "Dimensioni doppie";

    ls->enumVideoSize1x         = "Normale - 320x200";
    ls->enumVideoSize2x         = "Doppia - 640x400";
    ls->enumVideoSizeFullscreen = "Schermo intero";

    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "Nessuno";
    ls->enumVideoFrameskip1     = "1 fotogramma";
    ls->enumVideoFrameskip2     = "2 fotogrammi";
    ls->enumVideoFrameskip3     = "3 fotogrammi";
    ls->enumVideoFrameskip4     = "4 fotogrammi";
    ls->enumVideoFrameskip5     = "5 fotogrammi";

    ls->enumSoundDrvNone        = "Nessun suono";
    ls->enumSoundDrvWMM         = "Driver WMM";
    ls->enumSoundDrvDirectX     = "Driver DirectX";

    ls->enumEmuSync1ms          = "1ms (migliore)";
    ls->enumEmuSyncAuto         = "Automatico (veloce)";

    ls->enumControlsJoyNone     = "Nessuno";
    ls->enumControlsJoyMouse    = "Mouse";

    ls->dlgAboutAbout           = "INFORMAZIONI\r\n====";
    ls->dlgAboutVersion         = "Versione:";
    ls->dlgAboutBuildNumber     = "Compilazione:";
    ls->dlgAboutBuildDate       = "Data:";
    ls->dlgAboutCreat           = "Creato da Daniel Vik";
    ls->dlgAboutDevel           = "SVILUPPATORI\r\n========";
    ls->dlgAboutThanks          = "RINGRAZIAMENTI SPECIALI A\r\n============";
    ls->dlgAboutLisence         = "LICENZA\r\n"
                                  "======\r\n\r\n"
                                  "Questo programma è fornito \"così com'è\", senza alcuna esplicita o implicita "
                                  "garanzia. In nessun caso l'autore potrà essere ritenuto responsabile per "
                                  "qualunque danno derivante dall'uso di questo programma.\r\n\r\n"
                                  "Visita www.bluemsx.com per maggiori dettagli.";

    // New entries
    ls->menuTools                = "Strumenti";
    ls->menuToolsMachine         = "Editor della macchina";
    ls->menuPropsSettings        = "Impostazioni";
    ls->menuCasRewindAfterInsert = "Riavvolgi dopo l'inserimento";
    ls->menuCasUseReadOnly       = "Usa un'immagine nastro a sola lettura";
    ls->lmenuCasSaveAs           = "Salva l'immagine nastro con nome";

    ls->dlgSaveCassette          = "blueMSX - Salva l'immagine nastro";
    ls->dlgTapeCustom            = "Mostra i files personalizzati";
    ls->dlgTapeSetPosText        = "Posizione del nastro:";
    ls->dlgTabPosition           = "Posizione";
    ls->dlgTabType               = "Tipo";
    ls->dlgTabFilename           = "Nome del file";

    ls->propSettings             = "Impostazioni";
    
    ls->propSetFileHistoryGB     = "Files recenti ";
    ls->propSetFileHistorySize   = "Numero di voci in Files recenti:";
    ls->propSetFileHistoryClear  = "Cancella la lista";
    ls->propSetScreenSaver       = " Disabilita il salvaschermo durante l'esecuzione di blueMSX";

    ls->confTitle                = "blueMSX - Editor di configurazione della macchina";
    ls->confSave                 = "Salva";
    ls->confSaveAs               = "Salva con...";
    ls->confRun                  = "Esegui";
    ls->confClose                = "Chiudi";
    ls->confConfigText           = "Configurazione";
    ls->confSlotLayout           = "Disposizione degli slots";
    ls->confMemory               = "Memoria";
    ls->confChipEmulation        = "Emulazione del chip";

    ls->confSlotLayoutGB         = "Disposizione degli slots ";
    ls->confSlotExtSlotGB        = "Slots esterni ";
    ls->confSlotCart             = "Cartuccia 1:";
    ls->confSlotPrimary          = "Primario";
    ls->confSlotExpanded         = "Espanso (4 subslots)";

    ls->confMemAdd               = "Aggiungi...";
    ls->confMemEdit              = "Modifica...";
    ls->confMemRemove            = "Rimuovi";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Indirizzo";
    ls->confMemType              = "Tipo";
    ls->confMemRomImage          = "Immagine .ROM";
    
    ls->confSaveTitle            = "blueMSX - Salva la configurazione";
    ls->confSaveText             = "Vuoi sovrascrivere la configurazione della macchina?";

    ls->confChipVideoGB          = "Video ";
    ls->confChipVideoChip        = "Chip video:";
    ls->confChipVideoRam         = "RAM video:";
    ls->confChipSoundGB          = "Audio ";

    ls->confEditMemTitle         = "blueMSX - Modifica il Mapper";
    ls->confEditMemGB            = "Dettagli del Mapper ";
    ls->confEditMemType          = "Tipo:";
    ls->confEditMemFile          = "File:";
    ls->confEditMemAddress       = "Indirizzo";
    ls->confEditMemSize          = "Dimensioni";
    ls->confEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Configurazione";
    ls->confExitSaveTitle        = "blueMSX - Esci dall'editor di configurazione";
    ls->confExitSaveText         = "Vuoi annullare i cambiamenti apportati alla configurazione attuale?";

    ls->confSaveAsMachineName    = "Nome della macchina:";
    
    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypes            = " Associa tipi file a blueMSX (.rom, .dsk, .cas, .sta)"; 
    ls->propDisableWinKeys       = " Funzioni MSX automatiche con il menu tasti di Windows"; 
    ls->propWindowsEnvGB         = "Ambiente Windows";

    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW accel.";
    ls->propMonHorizStretch      = " Allungamento Orizzontale";
    ls->propClearHistory         = "Desiderate realmente cancellare la lista ?";
    ls->propEmuFrontSwitchGB     = "Switches Panasonic "; 
    ls->propEmuFrontSwitch       = " Front Switch"; 
    ls->propEmuAudioSwitch       = " MSX-AUDIO cartridge switch"; 
    ls->propMonVertStretch       = " Allungamento Verticale";

    ls->confCmosGB                = "CMOS ";
    ls->confCmosEnable            = "Abilita CMOS";
    ls->confCmosBattery           = "Battery charged";

    ls->menuCartSCCPlus         = "Cartuccia SCC+";
    ls->menuCartSCC             = "Cartuccia SCC";
    
    ls->warningTitle             = "blueMSX - Avvertimento";



    // New entries in 1.5.1
    ls->menuToolsShortcuts      = "Editor degli shortcut";

    ls->shortcutSaveConfig      = "blueMSX - Salva la configurazione";
    ls->shortcutOverwriteConfig = "Vuoi sovrascrivere la configurazione della macchina?";
    ls->shortcutExitConfig      = "blueMSX - Esci dall'editor di scorciatoie ";
    ls->shortcutDiscardConfig   = "Vuoi annullare i cambiamenti apportati alla configurazione attuale?";
    ls->shortcutSaveConfigAs    = "blueMSX - Salva la configurazione con nome ";
    ls->shortcutConfigName      = "Nome della configurazione";
    ls->shortcutNewProfile      = "< Nuovo Profilo >";
    ls->shortcutConfigTitle     = "blueMSX - Editor degli shortcut";
    ls->shortcutAssign          = "Assegna";
    ls->shortcutPressText       = "Premi tasto(i) della scorciatoia :";
    ls->shortcutScheme          = "Schema:";

    ls->shortcutCartInsert1     = "Inserimento cartuccia nello slot 1";
    ls->shortcutCartRemove1     = "Rimozione cartuccia dallo slot 1 ";
    ls->shortcutCartInsert2     = "Inserimento cartuccia nello slot 2";
    ls->shortcutCartRemove2     = "Rimozione cartuccia dallo slot 2";
    ls->shortcutCartAutoReset   = "Riavvio emulatore dopo inserimento cartuccia";
    ls->shortcutDiskInsertA     = "Inserimento dischetto nell'unità A";
    ls->shortcutDiskRemoveA     = "Rimozione dischetto nell'unità A";
    ls->shortcutDiskChangeA     = "Cambio rapido del dischetto nell'unità A";
    ls->shortcutDiskAutoResetA  = "Riavvio emulatore dopo inserimento floppy nell'unità A";
    ls->shortcutDiskInsertB     = "Inserimento dischetto nell'unità B";
    ls->shortcutDiskRemoveB     = "Rimozione dischetto nell'unità B";
    ls->shortcutCasInsert       = "Inserimento immagine cassetta";
    ls->shortcutCasEject        = "Rimozione immagine cassetta";
    ls->shortcutCasAutorewind   = "Riavvolgimento automatico o meno della cassetta";
    ls->shortcutCasReadOnly     = "Cassetta in modo solo lettura o meno";
    ls->shortcutCasSetPosition  = "Impostazione della posizione del nastro";
    ls->shortcutCasRewind       = "Riavvolgimento cassetta";
    ls->shortcutCasSave         = "Salvataggio immagine nastro con nome";
    ls->shortcutCpuStateLoad    = "Caricamento dello stato della CPU";
    ls->shortcutCpuStateSave    = "Salvataggio dello stato della CPU";
    ls->shortcutCpuStateQload   = "Caricamento rapido dello stato della CPU";
    ls->shortcutCpuStateQsave   = "Salvataggio rapido dello stato della CPU";
    ls->shortcutAudioCapture    = "Start/Stop audio capture ";
    ls->shortcutScreenshotOrig  = "Salvataggio della schermata";
    ls->shortcutScreenshotSmall = "Salvataggio breve della schermata senza filtro";
    ls->shortcutScreenshotLarge = "Salvataggio completo della schermata senza filtro";
    ls->shortcutQuit            = "Uscita da blueMSX";
    ls->shortcutRunPause        = "Start/Pausa Emulatore";
    ls->shortcutStop            = "Stop Emulatore";
    ls->shortcutResetHard       = "Riavvio hardware";
    ls->shortcutResetSoft       = "Riavvio software";
    ls->shortcutResetClean      = "Riavvio generale";
    ls->shortcutSizeSmall       = "Passare in modalità finestra normale";
    ls->shortcutSizeNormal      = "Passare in modalità finestra doppia";
    ls->shortcutSizeFullscreen  = "Passare in modalità schermo intero";
    ls->shortcutToggleFullscren = "Bilanciamento modalità finestra/schermo intero";
    ls->shortcutVolumeIncrease  = "Aumentare il volume del suono";
    ls->shortcutVolumeDecrease  = "Diminuire il volume del suono";
    ls->shortcutVolumeMute      = "Stabilire il suono";
    ls->shortcutSwitchMsxAudio  = "Attivare l' MSX-AUDIO switch";
    ls->shortcutSwitchFront     = "Attivare il Panasonic front switch";
    ls->shortcutToggleMouseLock = "Attivare/disattivare il blocco del mouse";
    ls->shortcutEmuSpeedMax     = "Velocità massima dell'emulazione";
    ls->shortcutEmuSpeedNormal  = "Velocità normale dell'emulazione";
    ls->shortcutEmuSpeedInc     = "Aumentare la velocità dell'emulazione";
    ls->shortcutEmuSpeedDec     = "Diminuire la velocità dell'emulazione";
    ls->shortcutShowEmuProp     = "Mostra proprietà  dell'emulazione";
    ls->shortcutShowVideoProp   = "Mostra proprietà Video";
    ls->shortcutShowAudioProp   = "Mostra proprietà Audio";
    ls->shortcutShowCtrlProp    = "Mostra proprietà Controlli";
    ls->shortcutShowPerfProp    = "Mostra proprietà Prestazioni";
    ls->shortcutShowSettProp    = "Mostra proprietà Impostazioni";
    ls->shortcutShowLanguage    = "Mostra dialogo per la scelta del linguaggio";
    ls->shortcutShowMachines    = "Mostra editor della macchina";
    ls->shortcutShowShortcuts   = "Mostra editor degli shortcut";
    ls->shortcutShowHelp        = "Accedere agli argomenti dell'aiuto";
    ls->shortcutShowAbout       = "Vedere informazioni su blueMSX";
    
    ls->shortcutSpecialMenu1    = "Mostra menu Speciale per la cartuccia dello slot 1";
    ls->shortcutSpecialMenu2    = "Mostra menu speciale per la cartuccia dello slot 2";
    ls->shortcutVolumeStereo    = "Bilanciamento mono/stereo";
    ls->shortcutThemeSwitch     = "Cambia il tema";
    ls->shortcutToggleSpriteEnable = "Mostra/Disattiva Sprites";
    
    ls->shortcutShowApearProp   = "Mostra proprietà dell'aspetto";
    ls->menuPropsApearance      = "Aspetto";
    ls->propThemeGB             = "Tema ";
    ls->propTheme               = "Tema";

    ls->propMonBrightness       = "Luminosità:";
    ls->propMonContrast         = "Contrasto:";
    ls->propMonSaturation       = "Saturazione:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanlines:";

    ls->dlgRomType              = "Tipo rom:"; 
    ls->propOpenRomGB           = "Dialogo di apertura file rom "; 
    ls->propDefaultRomType      = "Tipo rom di default:"; 
    ls->propGuessRomType        = "Individua il tipo"; 

    ls->propFile                = "File"; 
    ls->propSettDefSlotGB       = "Drag and Drop "; 
    ls->propSettDefSlots        = "Inserisci cartuccia in:"; 
    ls->propSettDefSlot         = " Slot"; 
    ls->propSettDefDrives       = "Inerisci disco in:"; 
    ls->propSettDefDrive        = " Floppy"; 
    ls->menuPropsFile           = "File";
    ls->shortcutShowFiles       = "Mostri proprietà Files";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "Inserisci Directory"; 
    ls->shortcutDiskDirInsertA  = "Inserisci una directory come disco A"; 
    ls->shortcutDiskDirInsertB  = "Inserisci una directory come disco B"; 
    ls->propMonDeInterlace      = " De-interlace"; 

    // New entries in 2.0
    ls->shortcutSwitchPause     = "Attivare il Pause switch"; 
    ls->shortcutSizeMinimized   = "Minimizzi la finestra"; 
    ls->shortcutEmuSpeedToggle  = "Bilencia velocità massima dell'emulazione"; 
    ls->shortcutToggleCpuTrace  = "Convalidare/invalidare la traccia della CPU"; 

    ls->enumVideoEmuMonitor     = "Monitor"; 

    ls->propEmuPauseSwitch      = " Pause Switch"; 
    ls->propVideoFreqText       = "Frequenza Video:"; 
    ls->propVideoFreqAuto       = "Auto"; 
    ls->propSndOversampleText   = "Oversample:";

    ls->confChipExtras          = "Extra"; 
    ls->confBoardGB             = "Sistema "; 
    ls->confBoardText           = "Sistema tipo:"; 
    ls->confCpuFreqGB            = "Frequenza CPU "; 
    ls->confZ80FreqText          = "Frequenza Z80:"; 
    ls->confR800FreqText         = "Frequenza R800:"; 
    ls->confFdcGB                = "Controller Floppy Disk "; 
    ls->confCFdcNumDrivesText    = "Numero di unità:"; 

    ls->propPriorityBoost       = " Dare a blueMSX una precedenza elevata";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "Non sincronizzare floppy disk"; 
    ls->shortcutToggleFdcTiming = "Sincronizzare o no disco floppy"; 

    // New entries in 2.2
    ls->menuCartHBI55           = "Cartuccia Sony HBI-55"; 
    ls->enumVideoEmuHq2x        = "Hq2x"; 
    ls->propMonColorGhosting    = "Modulatore RF"; 

    ls->keyconfigSelectedKey    = "Tasto scelto:"; 
    ls->keyconfigMappedTo       = "Assegnato a:"; 
    ls->keyconfigMappingScheme  = "Configurazione dei Tasti:"; 

    ls->warningDiscardChanges   = "Vuoi annullare i cambiamenti apportati a questa configurazione ?"; 

    ls->confSaveAsTitle         = "Salva con..."; 

    ls->menuToolsKeyboard       = "Editor della tastiera"; 
    ls->shortcutShowKeyboard    = "Mostri editor della tastiera"; 

    ls->menuVideoSource         = "Sorgente Video"; 
    ls->menuVideoSourceDefault  = "Nessuna sorgente video"; 
    ls->menuVideoChipAutodetect = "Individuazione automatica"; 
    ls->propFullscreenResText   = "Risoluzione schermo intero:"; 
    ls->dlgSavePreview          = "Mostra anteprima"; 
    ls->dlgSaveDate             = "Data:"; 

    ls->enumVideoMonAmber       = "Ambra";

    ls->menuPropsPorts          = "Porte";
    ls->propPortsLptGB          = "Porta parallela ";
    ls->propPortsComGB          = "Porta seriale";
    ls->propPortsLptText        = "Porta:";
    ls->propPortsCom1Text       = "Porta 1:";

    ls->shortcutShowDebugger    = "Mostri Debugger"; 
    ls->shortcutShowTrainer     = "Mostri Trainer"; 
    ls->shortcutShowPorts       = "Mostri proprietà delle Porte";
    
    ls->propPorts               = "Porte";
    ls->propPortsNone           = "Nessuna";
    
      // New entries in 2.3 
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle"; 

    ls->propPortsSimplCovox     = "SiMPL / Covox DAC"; 
    ls->propPortsFile           = "Stampare in archivio"; 
    ls->propPortsOpenLogFile    = "Aprire un archivio di dati"; 
    ls->propPortsEmulateMsxPrn  = "Emulazione:"; 

    ls->shortcutPrnFormFeed     = "Passaggio alla pagina seguente"; 

    ls->menuPrnFormfeed         = "Pagina seguente"; 
    ls->menuFilePrn             = "Stampante"; 
    ls->propPortsComFile        = "Inviare verso archivio"; 

    // New entries in 2.4 
    ls->shortcutShowMixer       = "Mostri Mixer"; 
    ls->menuToolsMixer          = "Mixer"; 
    
    ls->propSndMidiInGB         = "MIDI In "; 
    ls->propSndMidiOutGB        = "MIDI Out "; 
    ls->propSndMt32ToGm         = " Accordare strumenti MT-32 a General MIDI"; 

    ls->textDevice              = "Tipo:"; 
    ls->textFilename            = "Nome:"; 
    ls->textFile                = "File"; 
    ls->textNone                = "Nessuno"; 

    ls->enumEmuSyncNone         = "Nessuno"; 
    ls->enumEmuSyncAuto         = "Automatico (veloce)"; 
    ls->enumEmuSync1ms          = "Sinc su MSX refresh"; 
    ls->enumEmuSyncVblank       = "Sinc su PC Vertical Blank"; 

    ls->propMonEffectsGB        = "Effeti "; 
    
    ls->confSlot                = "Slot"; 
    ls->confSubslot             = "Subslot"; 

    ls->shortcutDescription     = "Shortcut"; 
    ls->shortcutKey             = "Hotkey"; 
    ls->fileRom                 = "ROM image"; 
    ls->confOpenRom             = "Aprire ROM image"; 
    ls->fileAll                 = "Tutti gli archivi"; 
    ls->fileCpuState             = "Stato della CPU"; 
    ls->fileDisk                = "Disk Image"; 
    ls->fileCas                 = "Tape Image"; 

    ls->menuCartExternalRam     = "RAM esterno"; 
};

#endif


