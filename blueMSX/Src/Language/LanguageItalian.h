/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageItalian.h,v $
**
** $Revision: 1.9 $
**
** $Date: 2005-03-10 01:34:55 $
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
    ls->statusBarStopped        = "  Fermato";
    ls->statusBarPaused         = "  In pausa";
    ls->statusBarRunning        = "  In esecuzione";
    
    ls->menuHardReset           = "Riavvio hardware";
    ls->menuSoftReset           = "Riavvio software";
    
    ls->menuCartInsert          = "Inserisci";
    ls->menuCartRemove          = "Rimuovi";
    ls->menuCartAutoReset       = "Riavvia dopo aver inserito/rimosso";
    ls->menuCartNoRecentFiles   = "- nessun file recente -";
    ls->menuCartFMPac           = "Cartuccia FM-PAC";
    ls->menuCartPac             = "Cartuccia PAC";
    ls->menuCartSpecial         = "Speciale";

    ls->menuDiskInsert          = "Inserisci";
    ls->menuDiskEject           = "Espelli";
    ls->menuDiskAutoStart       = "Riavvia dopo l'inserimento";
    ls->menuDiskNoRecentFiles   = "- nessun file recente -";
    
    ls->menuCasInsert           = "Inserisci";
    ls->menuCasEject            = "Espelli";
    ls->menuCasSetPosition      = "Imposta la posizione";
    ls->menuCasRewind           = "Riavvolgi";
    ls->menuCasNoRecentFiles    = "- nessun file recente -";

    ls->menuZoomNormal          = "Dimensione normale";
    ls->menuZoomDouble          = "Dimensione doppia";
    ls->menuZoomFullscreen      = "Schermo intero";
    
    ls->menuPropsEmulation      = "Emulazione";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Sonoro";
    ls->menuPropsControls       = "Controlli";
    ls->menuPropsPerformance    = "Prestazioni";
    ls->menuPropsLanguage       = "Lingua";
    
    ls->menuHelpHelp            = "Argomenti";
    ls->menuHelpAbout           = "Informazioni su blueMSX";

    ls->menuFileCart1           = "Cartuccia Slot 1";
    ls->menuFileCart2           = "Cartuccia Slot 2";
    ls->menuFileDiskA           = "Disco floppy A";
    ls->menuFileDiskB           = "Disco floppy B";
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

    ls->tooltipReset            = "Riavvia l'MSX";
    ls->tooltipCart1            = "Inserisce una cartuccia nello Slot 1";
    ls->tooltipCart2            = "Inserisce una cartuccia nello Slot 2";
    ls->tooltipDiskA            = "Inserisce un dischetto nell'unità A";
    ls->tooltipDiskB            = "Inserisce un dischetto nell'unità B";
    ls->tooltipCas              = "Inserisce un nastro nel riproduttore";
    ls->tooltipStart            = "Avvia l'emulazione";
    ls->tooltipResume           = "Riprende l'emulazione";
    ls->tooltipPause            = "Mette in pausa l'emulatore";
    ls->tooltipWindowSize       = "Imposta le dimensioni della finestra";
    ls->tooltipProperties       = "Apre il pannello delle proprietà";
    ls->tooltipHelp             = "Apre la finestra di aiuto";

    ls->dlgMainWindow           = "  blueMSX";
    ls->dlgLoadRom              = "blueMSX - Seleziona un'immagine rom da caricare";
    ls->dlgLoadDsk              = "blueMSX - Seleziona un'immagine dsk da caricare";
    ls->dlgLoadCas              = "blueMSX - Seleziona un'immagine cas da caricare";
    ls->dlgLoadRomDskCas        = "blueMSX - Seleziona un file rom, dsk, o cas da caricare";
    ls->dlgLoadRomDesc          = "Scegli un'immagine rom da caricare:";
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

    ls->dlgJoyTitle1            = "blueMSX - Configurazione del joystick A";
    ls->dlgJoyTitle2            = "blueMSX - Configurazione del joystick B";
    ls->dlgJoyUpText            = "Sù";
    ls->dlgJoyDownText          = "Giù";
    ls->dlgJoyLeftText          = "Sinistra";
    ls->dlgJoyRightText         = "Destra";
    ls->dlgJoyButton1Text       = "Pulsante 1";
    ls->dlgJoyButton2Text       = "Pulsante 2";
    ls->dlgJoyGB                = "Configurazione dei tasti ";

    ls->dlgLangLangText         = "Scegli la lingua per l'interfaccia di blueMSX";
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
    ls->propVideoYypeText       = "Tipo di video:";
    ls->propWindowSizeText      = "Dimensioni della finestra:";

    ls->propPerfVideoDrvGB      = "Driver video ";
    ls->propPerfVideoDispDrvText= "Mostra il driver:";
    ls->propPerfFrameSkipText   = "Salta fotogrammi:";
    ls->propPerfAudioDrvGB      = "Driver audio ";
    ls->propPerfAudioDrvText    = "Driver del suono:";
    ls->propPerfAudioBufSzText  = "Dimensioni del buffer audio:";
    ls->propPerfEmuGB           = "Emulazione ";
    ls->propPerfSyncModeText    = "SYNC Modo sincronizzato:";

    ls->propSndChipEmuGB        = "Emulazione del chip audio ";
    ls->propSndMixerGB          = "Mixer audio ";
    ls->propSndMonoText         = "mono";
    ls->propSndStereoText       = "stereo";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "MASTER";

    ls->propJoyPort1GB          = "Porta #1 ";
    ls->propJoyPort2GB          = "Porta #2 ";
    ls->propJoyAutofireText     = "Sparo auto:";
    ls->propJoyKeysetGB         = "Configurazione joysticks ";
    ls->propJoyKeyest1          = "Configura il joystick A";
    ls->propJoyKeyest2          = "Configura il joystick B";

    ls->enumVideoMonColor       = "Colore";
    ls->enumVideoMonGrey        = "Bianco e nero";
    ls->enumVideoMonGreen       = "Verde";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Nessuna";
    ls->enumVideoEmuYc          = "Cavo Y/C (Sharp)";
    ls->enumVideoEmuYcBlur      = "Cavo Y/C rumoroso (Sharp)";
    ls->enumVideoEmuComp        = "Composito (Blurry)";
    ls->enumVideoEmuCompBlur    = "Composito rumoroso (Blurry)";
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
    ls->enumControlsJoyNumpad   = "Tastierino numerico";
    ls->enumControlsJoyKeysetA  = "Controlli per A";
    ls->enumControlsJoyKeysetB  = "Controlli per B";
    ls->enumControlsJoyPCjoy1   = "PC joystick #1";
    ls->enumControlsJoyPCjoy2   = "PC joystick #2";
    ls->enumControlsJoyMouse    = "Mouse";

    ls->enumControlsAfOff       = "Disattivato";
    ls->enumControlsAfSlow      = "Lento";
    ls->enumControlsAfMedium    = "Medio";
    ls->enumControlsAfFast      = "Rapido";

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
    ls->propSetScreenSaverGB     = "Salvaschermo ";
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
    ls->confSlotSlot0            = "Slot 0";
    ls->confSlotSlot1            = "Slot 1";
    ls->confSlotSlot2            = "Slot 2";
    ls->confSlotSlot3            = "Slot 3";
    ls->confSlotCart1            = "Cartuccia 1:";
    ls->confSlotCart2            = "Cartuccia 2:";
    ls->confSlotPrimary          = "Primario";
    ls->confSlotExpanded         = "Espanso (4 subslots)";

    ls->confMemAdd               = "Aggiungi...";
    ls->confMemEdit              = "Modifica...";
    ls->confMemRemove            = "Rimuovi";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Indirizzo";
    ls->confMemType              = "Tipo";
    ls->confMemRomImage          = "Immagine ROM";
    
    ls->confSaveTitle            = "blueMSX - Salva la configurazione";
    ls->confSaveText             = "Vuoi sovrascrivere la configurazione della macchina?";

    ls->confChipVideoGB          = "Video ";
    ls->confChipVideoChip        = "Chip video:";
    ls->confChipVideoRam         = "RAM video:";
    ls->confChipSoundGB          = "Audio ";

    ls->slotEditMemTitle         = "blueMSX - Modifica il Mapper";
    ls->slotEditMemGB            = "Dettagli del Mapper ";
    ls->slotEditMemType          = "Tipo:";
    ls->slotEditMemFile          = "File:";
    ls->slotEditMemAddress       = "Indirizzo";
    ls->slotEditMemSize          = "Dimensioni";
    ls->slotEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Configurazione";
    ls->confExitSaveTitle        = "blueMSX - Esci dall'editor di configurazione";
    ls->confExitSaveText         = "Vuoi annullare i cambiamenti apportati alla configurazione attuale?";

    ls->confSaveAsMachineTitle   = "blueMSX - Salva la configurazione con nome";
    ls->confSaveAsMachineName    = "Nome della macchina:";
    
    ls->confEditMemInternalRoms  = "blueMSX - Roms interne"; 


    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypesGB          = "Tipi di file ";
    ls->propFileTypes            = " Associare alcuni tipi di file con blueMSX"; 
    ls->propDisableWinKeys       = " Funzione MSX automatica per le chiavi Windows"; 
    ls->propWindowsEnvGB         = "Ambiente Windows";

    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW accel.";
    ls->enumVideoDrvDirectDrawHWSys = "DirectDraw mix."; 
    ls->propMonHorizStretch      = " Allungamento Orizzontale";
    ls->propClearHistory         = "Desiderate realmente cancellare la lista ?";
    ls->propEmuFrontSwitchGB     = "Panasonic Switches "; 
    ls->propEmuFrontSwitch       = " Front Switch"; 
    ls->propEmuAudioSwitch       = " MSX-AUDIO cartridge switch"; 
    ls->propMonVertStretch       = " Allungamento Verticale";

    ls->dlgCmosGB                = "CMOS ";
    ls->dlgCmosEnable            = "Enable CMOS";
    ls->dlgCmosBattery           = "Battery charged";

    ls->menuCartSnatcher        = "Cartuccia The Snatcher";
    ls->menuCartSdSnatcher      = "Cartuccia SD-Snatcher";
    ls->menuCartSCCMirrored     = "Cartuccia SCC Mirrored";
    ls->menuCartSCCExpanded     = "Cartuccia SCC Expanded";
    ls->menuCartSCCPlus         = "Cartuccia SCC+";
    ls->menuCartSCC             = "Cartuccia SCC";
    
    ls->warningTitle             = "blueMSX - Avvertimento";
    ls->tooltipStop              = "Ferma l'emulazione";



    // New entries in 1.5.1
    ls->enumControlsJoyKeyset   = "Keyset";    
    ls->propJoyConfigKeyset     = "Config Keyset";
    ls->propJoyControlText      = "Controllo:";
    ls->propJoyButtonText       = "Tasto";
    ls->propJoyButtonAText      = "Tasto A:";
    ls->propJoyButtonBText      = "Tasto B:";

    ls->menuToolsShortcuts      = "Editore di scorciatoie";

    ls->shortcutSaveConfig      = "blueMSX - Salva la configurazione";
    ls->shortcutOverwriteConfig = "Vuoi sovrascrivere la configurazione della macchina?";
    ls->shortcutExitConfig      = "blueMSX - Esci dall'editor di scorciatoie ";
    ls->shortcutDiscardConfig   = "Vuoi annullare i cambiamenti apportati alla configurazione attuale?";
    ls->shortcutSaveConfigAs    = "blueMSX - Salva la configurazione con nome ";
    ls->shortcutConfigName      = "Nome della configurazione";
    ls->shortcutNewProfile      = "< Nuovo Profilo >";
    ls->shortcutConfigTitle     = "blueMSX - Editore della carta delle scorciatoie";
    ls->shortcutAssign          = "Assegni";
    ls->shortcutPressText       = "Premi tasto(i) della scorciatoia :";
    ls->shortcutScheme          = "Schema:";

    ls->shortcutCartInsert1     = "Inserisce una cartuccia nello slot 1";
    ls->shortcutCartRemove1     = "Rimuovi cartuccia nello slot 1 ";
    ls->shortcutCartInsert2     = "Inserisce una cartuccia nello slot 2";
    ls->shortcutCartRemove2     = "Rimuovi cartuccia nello slot 2";
    ls->shortcutCartAutoReset   = "Riavvia dopo aver inserito cartuccia";
    ls->shortcutDiskInsertA     = "Inserisce un dischetto nell'unità A";
    ls->shortcutDiskRemoveA     = "Espelli dischetto nell'unità A ";
    ls->shortcutDiskChangeA     = "Cambiare rapidamente dischetto nell'unità A";
    ls->shortcutDiskAutoResetA  = "Riavvia dopo l'inserimento nell'unità A";
    ls->shortcutDiskInsertB     = "Inserisce un dischetto nell'unità B";
    ls->shortcutDiskRemoveB     = "Espelli dischetto nell'unità B";
    ls->shortcutCasInsert       = "Inserisci un'immagine cassetta";
    ls->shortcutCasEject        = "Espelli immagine cassetta";
    ls->shortcutCasAutorewind   = "Riavvolgi automatico o no della cassetta";
    ls->shortcutCasReadOnly     = "Cassetta in modo lettura sola o no";
    ls->shortcutCasSetPosition  = "Imposta la posizione";
    ls->shortcutCasRewind       = "Riavvolgi cassetta";
    ls->shortcutCasSave         = "Salva l'immagine nastro con nome";
    ls->shortcutCpuStateLoad    = "Carica lo stato della CPU";
    ls->shortcutCpuStateSave    = "Salva lo stato della CPU";
    ls->shortcutCpuStateQload   = "Carica rapidamente lo stato della CPU";
    ls->shortcutCpuStateQsave   = "Salva rapidamente lo stato della CPU";
    ls->shortcutAudioCapture    = "Inizi/ferma la capture audio ";
    ls->shortcutScreenshotOrig  = "Salva la schermata";
    ls->shortcutScreenshotSmall = "Piccola cattura della schermata senza filtro";
    ls->shortcutScreenshotLarge = "Grande cattura della schermata senza filtro";
    ls->shortcutQuit            = "Esci blueMSX";
    ls->shortcutRunPause        = "Execui/Pausa  l'emulazione";
    ls->shortcutStop            = "Ferma l'emulazione";
    ls->shortcutResetHard       = "Riavvio hardware";
    ls->shortcutResetSoft       = "Riavvio software";
    ls->shortcutResetClean      = "Riavvio generale";
    ls->shortcutSizeSmall       = "Passare in modo finestra normale";
    ls->shortcutSizeNormal      = "Passare in modo doppio della finestra";
    ls->shortcutSizeFullscreen  = "Passare in modo schermo intero";
    ls->shortcutToggleFullscren = "Bilancia modo finestra/modo schermo intero";
    ls->shortcutVolumeIncrease  = "Aumentare il volume sonoro";
    ls->shortcutVolumeDecrease  = "Diminuire il volume sonoro";
    ls->shortcutVolumeMute      = "Stabilire il suono";
    ls->shortcutSwitchMsxAudio  = "Attivare il MSX-AUDIO switch";
    ls->shortcutSwitchFront     = "Attivare il Panasonic front switch";
    ls->shortcutToggleMouseLock = "Attivare/disattivare il blocco del topo";
    ls->shortcutEmuSpeedMax     = "Velocità massima dell'emulazione";
    ls->shortcutEmuSpeedNormal  = "Velocità normale dell'emulazione";
    ls->shortcutEmuSpeedInc     = "Aumentare la velocità dell'emulazione";
    ls->shortcutEmuSpeedDec     = "Diminuire la velocità dell'emulazione";
    ls->shortcutShowEmuProp     = "Mostri proprietà  dell'emulazione";
    ls->shortcutShowVideoProp   = "Mostri proprietà Video";
    ls->shortcutShowAudioProp   = "Mostri proprietà Audio";
    ls->shortcutShowCtrlProp    = "Mostri proprietà di Controlli";
    ls->shortcutShowPerfProp    = "Mostri proprietà di Prestazioni";
    ls->shortcutShowSettProp    = "Mostri proprietà di Impostazioni";
    ls->shortcutShowLanguage    = "Mostri dialogo di lingua";
    ls->shortcutShowMachines    = "Mostri editore della macchina";
    ls->shortcutShowShortcuts   = "Mostri editore Delle scorciatoie";
    ls->shortcutShowHelp        = "Accedere alle argomenti dell'aiuto";
    ls->shortcutShowAbout       = "Vedere informazioni su blueMSX";
    
    ls->shortcutSpecialMenu1    = "Mostri il menu speciale per la cartuccia nello slot 1";
    ls->shortcutSpecialMenu2    = "Mostri il menu speciale per la cartuccia nello slot 2";
    ls->shortcutVolumeStereo    = "Bilancia mono/stereo";
    ls->shortcutThemeSwitch     = "Commuti il tema";
    ls->shortcutToggleSpriteEnable = "Mostri/Pellame Sprites";
    
    ls->shortcutShowApearProp   = "Show Appearance Properties";
    ls->menuPropsApearance      = "Appearance";
    ls->propApearance           = "Appearance";
    ls->propThemeGB             = "Terna ";
    ls->propTheme               = "Terna";
    ls->propThemeClassic        = "Classico";
    ls->propThemeBlue           = "DIGIblue";

    ls->propMonBrightness       = "Luminosità:";
    ls->propMonContrast         = "Contrasto:";
    ls->propMonSaturation       = "Saturazione:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanlines:";

    ls->dlgRomType              = "Tipo rom:"; 
    ls->propOpenRomGB           = "Aprire rom file"; 
    ls->propDefaultRomType      = "Tipo per difetto:"; 
    ls->propGuessRomType        = "Indovina tipo"; 

    ls->propFile                = "File"; 
    ls->propSettDefSlotGB       = "Scivola e deposita "; 
    ls->propSettDefSlots        = "Inserisci cartuccia in:"; 
    ls->propSettDefSlot1        = " Slot 1"; 
    ls->propSettDefSlot2        = " Slot 2"; 
    ls->propSettDefDrives       = "Inerisci disco in:"; 
    ls->propSettDefDriveA       = " Floppy A"; 
    ls->propSettDefDriveB       = " Floppy B"; 
    ls->menuPropsFile           = "File";
    ls->shortcutShowFiles       = "Mostri proprietà Files";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "Inserisci repertorio"; 
    ls->shortcutDiskDirInsertA  = "Inserisci un repertorio come disco A"; 
    ls->shortcutDiskDirInsertB  = "Inserisci un repertorio come disco B"; 
    ls->propMonDeInterlace      = " De-intrecci"; 

    // New entries in 2.0
    ls->shortcutSwitchPause     = "Attivare il Pause switch"; 
    ls->shortcutSizeMinimized   = "Minimizzi la finestra"; 
    ls->shortcutEmuSpeedToggle  = "Bilencia velocità massima dell'emulazione"; 
    ls->shortcutToggleCpuTrace  = "Convalidare/invalidare la traccia della CPU"; 

    ls->enumVideoEmuMonitor     = "Monitor"; 

    ls->propEmuPauseSwitch      = " Pause Switch"; 
    ls->propVideoFreqText       = "Video frequenza:"; 
    ls->propVideoFreqAuto       = "Auto"; 
    ls->propSndOversampleText   = "Oversample:";

    ls->confChipExtras          = "Extras"; 
    ls->confBoardGB             = "Sistema "; 
    ls->confBoardText           = "Sistema tipo:"; 
    ls->dlgCpuFreqGB            = "CPU frequenza "; 
    ls->dlgZ80FreqText          = "Z80 frequenza:"; 
    ls->dlgR800FreqText         = "R800 frequenza:"; 
    ls->dlgFdcGB                = "Dispositivo di controllo di lettore di disci "; 
    ls->dlgCFdcNumDrivesText    = "Numero di lettore:"; 

    ls->propPriorityBoost       = " Dare a blueMSX una precedenza elevata";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "Non sincronizzare disco floppy"; 
    ls->shortcutToggleFdcTiming = "Sincronizzare o no disco floppy"; 
    ls->propUseRegistry         = "Salva la configurazione nel Registro";

    // New entries in 2.2
    ls->menuCartHBI55           = "Cartuccia Sony HBI-55"; 
    ls->propSndPcm              = " Turbo-R PCM"; 
    ls->propSndAY8910           = " AY8910 PSG"; 
    ls->propSndSN76489          = " SN76489 PSG"; 
    ls->enumVideoEmuHq2x        = "Hq2x"; 
    ls->propMonColorGhosting    = "Modulatore RF"; 

    ls->keyconfigSelectedKey    = "Chiave MSX scelta:"; 
    ls->keyconfigMappedTo       = "Assegnata alla chiave PC:"; 
    ls->keyconfigMappingScheme  = "Configurazione della tastiera:"; 

    ls->discardChanges          = "Vuoi annullare i cambiamenti apportati a questa configurazione ?"; 
    ls->overwriteConfig         = "Vuoi sovrascrivere questa configurazione ?"; 

    ls->confSaveAsTitle         = "Salva con..."; 
    ls->confSaveAsName          = "Nome:"; 

    ls->menuToolsKeyboard       = "Editore di tastiera"; 
    ls->shortcutShowKeyboard    = "Mostri editore di tastiera"; 

    ls->menuVideoSource         = "Fonte Video"; 
    ls->menuVideoSourceDefault  = "Nessuna fonte video"; 
    ls->menuVideoChipAutodetect = "Individuazione automatica"; 
    ls->propFullscreenResText   = "Risoluzione schermo intero:"; 
    ls->dlgSavePreview          = "Mostri sommario"; 
    ls->dlgSaveDate             = "Data:"; 

    ls->enumVideoMonAmber       = "Ambra";

    ls->menuPropsPorts          = "Porti";
    ls->propPortsLptGB          = "Porto parallelo ";
    ls->propPortsComGB          = "Porti serie";
    ls->propPortsLptText        = "Porto:";
    ls->propPortsCom1Text       = "Porto 1:";

    ls->shortcutShowDebugger    = "Mostri Debugger"; 
    ls->shortcutShowTrainer     = "Mostri Trainer"; 
    ls->shortcutShowPorts       = "Mostri proprietà di Porti";
};

#endif


