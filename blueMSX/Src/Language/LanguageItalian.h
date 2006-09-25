/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageItalian.h,v $
**
** $Revision: 1.50 $
**
** $Date: 2006-09-25 19:19:09 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2006 Daniel Vik
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
******************************************************************************
*/
#ifndef LANGUAGE_ITALIAN_H
#define LANGUAGE_ITALIAN_H

#include "LanguageStrings.h"
 
void langInitItalian(LanguageStrings* ls) 
{
    //----------------------
    // Language lines
    //----------------------

    ls->langChineseSimplified   = "Cinese Semplificato";
    ls->langChineseTraditional  = "Cinese Tradizionale";
    ls->langDutch               = "Olandese";
    ls->langEnglish             = "Inglese";
    ls->langFinnish             = "Finlandese";
    ls->langFrench              = "Francese";
    ls->langGerman              = "Tedesco";
    ls->langItalian             = "Italiano";
    ls->langJapanese            = "Giapponese";
    ls->langKorean              = "Coreano";
    ls->langPolish              = "Polacco";
    ls->langPortuguese          = "Portoghese";
    ls->langSpanish             = "Spagnolo";
    ls->langSwedish             = "Svedese";


    //----------------------
    // Generic lines
    //----------------------

    ls->textDevice              = "Periferica:"; 
    ls->textFilename            = "Nome del file:"; 
    ls->textFile                = "File"; 
    ls->textNone                = "Nessuno(a)"; 
    ls->textUnknown             = "Sconosciuto";                            


    //----------------------
    // Warning and Error lines
    //----------------------

    ls->warningTitle            = "blueMSX - Attenzione";
    ls->warningDiscardChanges   = "Vuoi annullare i cambiamenti apportati a questa configurazione?"; 
    ls->warningOverwriteFile    = "Vuoi sovrascrivere il file:"; 
    ls->errorTitle              = "blueMSX - Errore";
    ls->errorEnterFullscreen    = "Non riesco ad attivare la visualizzazione a schermo intero.           \n";
    ls->errorDirectXFailed      = "Non riesco a creare gli oggetti DirectX.          \nUtilizza le GDI.\nControlla le propriet� Video.";
    ls->errorNoRomInZip         = "Nessun file .rom trovato nel file compresso.";
    ls->errorNoDskInZip         = "Nessun file .dsk trovato nel file compresso.";
    ls->errorNoCasInZip         = "Nessun file .cas trovato nel file compresso.";
    ls->errorNoHelp             = "Non trovo il file di Guida in linea di blueMSX.";
    ls->errorStartEmu           = "Avvio dell'emulatore MSX fallito.";
    ls->errorPortableReadonly   = "Il dispositivo portatile � a sola lettura";        


    //----------------------
    // File related lines
    //----------------------

    ls->fileRom                 = "Immagine ROM"; 
    ls->fileAll                 = "Tutti i file"; 
    ls->fileCpuState            = "Stato della CPU"; 
    ls->fileVideoCapture        = "Cattura Video";    // New in 2.6
    ls->fileDisk                = "Immagine Disco"; 
    ls->fileCas                 = "Immagine Cassetta"; 
    ls->fileAvi                 = "Clip Video";       // New in 2.6


    //----------------------
    // Menu related lines
    //----------------------

    ls->menuNoRecentFiles       = "- nessun file recente -";
    ls->menuInsert              = "Inserisci";
    ls->menuEject               = "Rimuovi";

    ls->menuCartGameReader      = "Game Reader";                        
    ls->menuCartIde             = "IDE";                                
    ls->menuCartBeerIde         = "Beer";                               
    ls->menuCartGIde            = "GIDE";                               
    ls->menuCartSunriseIde      = "Sunrise";                            
    ls->menuCartSCC             = "Cartuccia SCC";
    ls->menuCartSCCPlus         = "Cartuccia SCC+";
    ls->menuCartFMPac           = "Cartuccia FM-PAC";
    ls->menuCartPac             = "Cartuccia PAC";
    ls->menuCartHBI55           = "Cartuccia Sony HBI-55"; 
    ls->menuCartInsertSpecial   = "Inserisci Speciale";                     
    ls->menuCartMegaRam         = "MegaRAM";                            
    ls->menuCartExternalRam     = "RAM esterno"; 

    ls->menuDiskInsertNew       = "Inserisci un nuovo disco";              
    ls->menuDiskDirInsert       = "Inserisci una cartella"; 
    ls->menuDiskAutoStart       = "Riavvia dopo l'inserimento";
    ls->menuCartAutoReset       = "Riavvia dopo aver inserito/rimosso";

    ls->menuCasRewindAfterInsert= "Riavvolgi dopo l'inserimento";
    ls->menuCasUseReadOnly      = "Usa un'immagine nastro a sola lettura";
    ls->lmenuCasSaveAs          = "Salva l'immagine nastro con nome";
    ls->menuCasSetPosition      = "Imposta la posizione";
    ls->menuCasRewind           = "Riavvolgi";

    ls->menuVideoLoad           = "Apri...";                           // New in 2.6
    ls->menuVideoPlay           = "Esegui l'ultimo video acquisito";   // New in 2.6
    ls->menuVideoRecord         = "Registra";                          // New in 2.6
    ls->menuVideoRecording      = "Salvataggio in corso";              // New in 2.6
    ls->menuVideoRecAppend      = "Registra (accoda)";                 // New in 2.6
    ls->menuVideoStop           = "Ferma";                             // New in 2.6
    ls->menuVideoRender         = "Crea una clip video";               // New in 2.6

    ls->menuPrnFormfeed         = "Pagina seguente"; 

    ls->menuZoomNormal          = "Dimensione ridotta";
    ls->menuZoomDouble          = "Dimensione normale";
    ls->menuZoomFullscreen      = "Schermo intero";
    
    ls->menuPropsEmulation      = "Emulazione";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Audio";
    ls->menuPropsControls       = "Controlli";
    ls->menuPropsPerformance    = "Prestazioni";
    ls->menuPropsSettings       = "Impostazioni";
    ls->menuPropsFile           = "File";
    ls->menuPropsLanguage       = "Lingua";
    ls->menuPropsPorts          = "Porte";
    
    ls->menuVideoSource         = "Uscita Video";                   
    ls->menuVideoSourceDefault  = "Nessuna uscita video connessa";      
    ls->menuVideoChipAutodetect = "Selezione automatica del chip video";     
    ls->menuVideoInSource       = "Ingresso Video";                    
    ls->menuVideoInBitmap       = "Ingresso da file Bitmap";                        
    
    ls->menuEthInterface        = "Interfaccia Ethernet";               // New in 2.6

    ls->menuHelpHelp            = "Guida in linea";
    ls->menuHelpAbout           = "Informazioni su blueMSX";

    ls->menuFileCart            = "Cartuccia Slot";
    ls->menuFileDisk            = "Disco floppy";
    ls->menuFileCas             = "Cassetta";
    ls->menuFilePrn             = "Stampante"; 
    ls->menuFileLoadState       = "Carica lo stato della CPU";
    ls->menuFileSaveState       = "Salva lo stato della CPU";
    ls->menuFileQLoadState      = "Carica rapidamente lo stato";
    ls->menuFileQSaveState      = "Salva rapidamente lo stato";
    ls->menuFileCaptureAudio    = "Cattura Audio";
    ls->menuFileCaptureVideo    = "Cattura Video";                      // New in 2.6
    ls->menuFileScreenShot      = "Salva uno screenshot";
    ls->menuFileExit            = "Esci";

    ls->menuFileHarddisk        = "Disco rigido";                          
    ls->menuFileHarddiskNoPesent= "Controller non presenti";             

    ls->menuRunRun              = "Esegui";
    ls->menuRunPause            = "Pausa";
    ls->menuRunStop             = "Ferma";
    ls->menuRunSoftReset        = "Riavvio software";
    ls->menuRunHardReset        = "Riavvio hardware";
    ls->menuRunCleanReset       = "Riavvio completo";

    ls->menuToolsMachine        = "Editor della macchina";
    ls->menuToolsShortcuts      = "Editor dei tasti rapidi";
    ls->menuToolsCtrlEditor     = "Editor dei controlli/tastiera";     // New in 2.6
    ls->menuToolsMixer          = "Mixer"; 
    ls->menuToolsDebugger       = "Debugger";               
    ls->menuToolsTrainer        = "Trainer";                
    ls->menuToolsTraceLogger    = "Trace Logger";           

    ls->menuFile                = "File";
    ls->menuRun                 = "Emulazione";
    ls->menuWindow              = "Finestra";
    ls->menuOptions             = "Opzioni";
    ls->menuTools               = "Strumenti";
    ls->menuHelp                = "Aiuto";


    //----------------------
    // Dialog related lines
    //----------------------

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Apri";
    ls->dlgCancel               = "Annulla";
    ls->dlgSave                 = "Salva";
    ls->dlgSaveAs               = "Salva con...";
    ls->dlgRun                  = "Esegui";
    ls->dlgClose                = "Chiudi";

    ls->dlgLoadRom              = "blueMSX - Seleziona un'immagine .rom da caricare";
    ls->dlgLoadDsk              = "blueMSX - Seleziona un'immagine dsk da caricare";
    ls->dlgLoadCas              = "blueMSX - Seleziona un'immagine cas da caricare";
    ls->dlgLoadRomDskCas        = "blueMSX - Seleziona un file .rom, .dsk, o .cas da caricare";
    ls->dlgLoadRomDesc          = "Scegli un'immagine .rom da caricare:";
    ls->dlgLoadDskDesc          = "Scegli un'immagine floppy da caricare:";
    ls->dlgLoadCasDesc          = "Scegli un'immagine cassetta da caricare:";
    ls->dlgLoadRomDskCasDesc    = "Scegli l'immagine di una rom, di un floppy, o di un nastro da caricare:";
    ls->dlgLoadState            = "Carica lo stato della CPU";
    ls->dlgLoadVideoCapture     = "Carica un video acquisito";         // New in 2.6
    ls->dlgSaveState            = "Salva lo stato della CPU";
    ls->dlgSaveCassette         = "blueMSX - Salva l'immagine nastro";
    ls->dlgSaveVideoClipAs      = "Salva una clip video con...";      // New in 2.6
    ls->dlgAmountCompleted      = "Salvataggio in corso:";        // New in 2.6
    ls->dlgInsertRom1           = "Inserisci una cartuccia ROM nello slot 1";
    ls->dlgInsertRom2           = "Inserisci una cartuccia ROM nello slot 2";
    ls->dlgInsertDiskA          = "Inserisci un'immagine floppy nell'unit� A";
    ls->dlgInsertDiskB          = "Inserisci un'immagine floppy nell'unit� B";
    ls->dlgInsertHarddisk       = "Inserisci uno disco rigido";                   
    ls->dlgInsertCas            = "Inserisci un'immagine cassetta";
    ls->dlgRomType              = "Tipo rom:"; 
    ls->dlgDiskSize             = "Formato del disco:";           // New in 2.6

    ls->dlgTapeTitle            = "blueMSX - Posizione del nastro";
    ls->dlgTapeFrameText        = "Posizione del nastro";
    ls->dlgTapeCurrentPos       = "Posizione attuale";
    ls->dlgTapeTotalTime        = "Durata totale";
    ls->dlgTapeCustom           = "Mostra i file personalizzati";
    ls->dlgTapeSetPosText       = "Posizione del nastro:";
    ls->dlgTabPosition          = "Posizione";
    ls->dlgTabType              = "Tipo";
    ls->dlgTabFilename          = "Nome del file";
    ls->dlgZipReset             = "Riavvia dopo l'inserimento";

    ls->dlgAboutTitle           = "blueMSX - Informazioni";

    ls->dlgLangLangText         = "Scegli la lingua per l'interfaccia di blueMSX";
    ls->dlgLangLangTitle        = "blueMSX - Lingua";

    ls->dlgAboutAbout           = "INFORMAZIONI\r\n==========";
    ls->dlgAboutVersion         = "Versione:";
    ls->dlgAboutBuildNumber     = "Compilazione:";
    ls->dlgAboutBuildDate       = "Data:";
    ls->dlgAboutCreat           = "Creato da Daniel Vik";
    ls->dlgAboutDevel           = "SVILUPPATORI\r\n=========";
    ls->dlgAboutThanks          = "RINGRAZIAMENTI SPECIALI A\r\n===================";
    ls->dlgAboutLisence         = "LICENZA\r\n"
                                  "======\r\n\r\n"
                                  "Questo programma � fornito \"cos� com'�\", senza alcuna esplicita o implicita "
                                  "garanzia. In nessun caso l'autore potr� essere ritenuto responsabile per qualunque "
                                  "danno derivante dall'uso di questo programma.\r\n\r\n"
                                  "Visita www.bluemsx.com per maggiori dettagli.";

    ls->dlgSavePreview          = "Mostra anteprima"; 
    ls->dlgSaveDate             = "Data:"; 

    ls->dlgRenderVideoCapture   = "blueMSX - Crea una clip video ...";  // New in 2.6


    //----------------------
    // Properties related lines
    //----------------------

    ls->propTitle               = "blueMSX - Propriet�";
    ls->propEmulation           = "Emulazione";
    ls->propVideo               = "Video";
    ls->propSound               = "Audio";
    ls->propControls            = "Controlli";
    ls->propPerformance         = "Prestazioni";
    ls->propSettings            = "Impostazioni";
    ls->propFile                = "File"; 
    ls->propPorts               = "Porte";
    
    ls->propEmuGeneralGB        = "Generale ";
    ls->propEmuFamilyText       = "Modello MSX:";
    ls->propEmuMemoryGB         = "Memoria ";
    ls->propEmuRamSizeText      = "Dimensioni della RAM:";
    ls->propEmuVramSizeText     = "Dimensioni della VRAM:";
    ls->propEmuSpeedGB          = "Velocit� di emulazione ";
    ls->propEmuSpeedText        = "Velocit� di emulazione:";
    ls->propEmuFrontSwitchGB    = "Interruttori Panasonic "; 
    ls->propEmuFrontSwitch      = " Interruttore frontale"; 
    ls->propEmuFdcTiming        = "Non sincronizzare il floppy disk"; 
    ls->propEmuPauseSwitch      = " Tasto pausa"; 
    ls->propEmuAudioSwitch      = " Cartuccia MSX-AUDIO"; 
    ls->propVideoFreqText       = "Frequenza Video:"; 
    ls->propVideoFreqAuto       = "Auto"; 
    ls->propSndOversampleText   = "Oversample:";
    ls->propSndYkInGB           = "YK-01/YK-10/YK-20 In ";                
    ls->propSndMidiInGB         = "MIDI In "; 
    ls->propSndMidiOutGB        = "MIDI Out "; 
    ls->propSndMidiChannel      = "Canale MIDI:";                      
    ls->propSndMidiAll          = "Tutti";                                

    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Tipo monitor:";
    ls->propMonEmuText          = "Emulazione monitor:";
    ls->propVideoTypeText       = "Tipo di video:";
    ls->propWindowSizeText      = "Dimensioni della finestra:";
    ls->propMonHorizStretch     = " Allungamento Orizzontale";
    ls->propMonVertStretch      = " Allungamento Verticale";
    ls->propMonDeInterlace      = " De-interlaccia"; 
    ls->propBlendFrames         = " Fusione fotogrammi consecutivi";           
    ls->propMonBrightness       = "Luminosit�:";
    ls->propMonContrast         = "Contrasto:";
    ls->propMonSaturation       = "Saturazione:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = " Linee di scansione:";
    ls->propMonColorGhosting    = " Modulatore RF"; 
    ls->propMonEffectsGB        = "Effetti "; 

    ls->propPerfVideoDrvGB      = "Driver video ";
    ls->propPerfVideoDispDrvText= "Driver per il video:";
    ls->propPerfFrameSkipText   = "Salto fotogrammi:";
    ls->propPerfAudioDrvGB      = "Driver audio ";
    ls->propPerfAudioDrvText    = "Driver per l'audio:";
    ls->propPerfAudioBufSzText  = "Dimensioni del buffer audio:";
    ls->propPerfEmuGB           = "Emulazione ";
    ls->propPerfSyncModeText    = "Tipo di sincronismo:";
    ls->propFullscreenResText   = "Risoluzione a schermo intero:"; 

    ls->propSndChipEmuGB        = "Emulazione del chip audio ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";
    ls->propSndMoonsound        = " Moonsound";
    ls->propSndMt32ToGm         = " Accordare strumenti MT-32 come General MIDI"; 

    ls->propPortsLptGB          = "Porta parallela ";
    ls->propPortsComGB          = "Porta seriale";
    ls->propPortsLptText        = "Porta:";
    ls->propPortsCom1Text       = "Porta 1:";
    ls->propPortsNone           = "Nessuna";
    ls->propPortsSimplCovox     = "SiMPL / Covox DAC"; 
    ls->propPortsFile           = "Stampa su file"; 
    ls->propPortsComFile        = "Invia su file"; 
    ls->propPortsOpenLogFile    = "Apri un file di rapporto"; 
    ls->propPortsEmulateMsxPrn  = "Emulazione:"; 

    ls->propSetFileHistoryGB    = "File Recenti ";
    ls->propSetFileHistorySize  = "Numero di voci nei File Recenti:";
    ls->propSetFileHistoryClear = "Cancella la lista";
    ls->propFileTypes           = " Associa a blueMSX alcuni tipi di file (.rom, .dsk, .cas, .sta)"; 
    ls->propWindowsEnvGB        = "Ambiente Windows";
    ls->propSetScreenSaver      = " Disabilita il salvaschermo durante l'esecuzione di blueMSX";
    ls->propDisableWinKeys      = " Associa automaticamente le funzionalit� MSX ai tasti Windows"; 
    ls->propPriorityBoost       = " Utilizza blueMSX con priorit� elevata";
    ls->propScreenshotPng       = " Utilizza il formato PNG per il salvataggio degli screenshot";  
    ls->propClearHistory        = "Desiderate realmente cancellare la lista?";
    ls->propOpenRomGB           = "Dialogo di apertura file rom "; 
    ls->propDefaultRomType      = "Tipo rom di default:"; 
    ls->propGuessRomType        = "Individua il tipo"; 

    ls->propSettDefSlotGB       = "Drag and Drop "; 
    ls->propSettDefSlots        = "Inserisci cartuccia in:"; 
    ls->propSettDefSlot         = " Slot"; 
    ls->propSettDefDrives       = "Inserisci disco in:"; 
    ls->propSettDefDrive        = " Floppy"; 

    ls->propThemeGB             = "Tema ";
    ls->propTheme               = "Tema:";


    //----------------------
    // Dropdown related lines
    //----------------------

    ls->enumVideoMonColor       = "Colore";
    ls->enumVideoMonGrey        = "Bianco e nero";
    ls->enumVideoMonGreen       = "Verde";
    ls->enumVideoMonAmber       = "Ambra";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Nessuna";
    ls->enumVideoEmuYc          = "Cavo Y/C (nitido)";
    ls->enumVideoEmuMonitor     = "Monitor"; 
    ls->enumVideoEmuYcBlur      = "Cavo Y/C rumoroso (nitido)";
    ls->enumVideoEmuComp        = "Composito (sfocato)";
    ls->enumVideoEmuCompBlur    = "Composito rumoroso (sfocato)";
    ls->enumVideoEmuScale2x     = "Dimensioni raddoppiate";
    ls->enumVideoEmuHq2x        = "Hq2x"; 

    ls->enumVideoSize1x         = "Normale - 320x200";
    ls->enumVideoSize2x         = "Doppia - 640x400";
    ls->enumVideoSizeFullscreen = "Schermo intero";

    ls->enumVideoDrvDirectDrawHW= "DirectDraw HW accelerato";
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

    ls->enumEmuSync1ms          = "Sincronizzato su MSX refresh"; 
    ls->enumEmuSyncAuto         = "Automatico (veloce)"; 
    ls->enumEmuSyncNone         = "Nessuno"; 
    ls->enumEmuSyncVblank       = "Sincronizzato su PC Vblank"; 
    ls->enumEmuAsyncVblank      = "PC Vblank asincrono";             

    ls->enumControlsJoyNone            = "Nessuno";
    ls->enumControlsJoyMouse           = "Mouse";
    ls->enumControlsJoyTetris2Dongle   = "Tetris 2 Dongle"; 
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey Dongle";             
    ls->enumControlsJoy2Button         = "2-button Joystick";                   
    ls->enumControlsJoyGunstick        = "Gun Stick";                         
    ls->enumControlsJoyAsciiLaser      = "ASCII Plus-X Terminator Laser";      
    ls->enumControlsJoyColeco          = "ColecoVision Joystick";                

    ls->enumDiskMsx35Dbl9Sect    = "MSX 3.5\" doppia faccia, 9 settori";     
    ls->enumDiskMsx35Dbl8Sect    = "MSX 3.5\" doppia faccia, 8 settori";     
    ls->enumDiskMsx35Sgl9Sect    = "MSX 3.5\" singola faccia, 9 settori";     
    ls->enumDiskMsx35Sgl8Sect    = "MSX 3.5\" singola faccia, 8 settori";     
    ls->enumDiskSvi525Dbl        = "SVI-328 5.25\" doppia faccia";           
    ls->enumDiskSvi525Sgl        = "SVI-328 5.25\" singola faccia";           
    ls->enumDiskSf3Sgl           = "Sega SF-7000 3\" singola faccia";  // New in 2.6


    //----------------------
    // Configuration related lines
    //----------------------

    ls->confTitle               = "blueMSX - Editor di configurazione della macchina";
    ls->confConfigText          = "Configurazione";
    ls->confSlotLayout          = "Disposizione degli slot";
    ls->confMemory              = "Memoria";
    ls->confChipEmulation       = "Emulazione del chip";
    ls->confChipExtras          = "Extra"; 

    ls->confOpenRom             = "Apri un immagine ROM"; 
    ls->confSaveTitle           = "blueMSX - Salva la configurazione";
    ls->confSaveText            = "Vuoi sovrascrivere la configurazione della macchina";
    ls->confSaveAsTitle         = "Salva con..."; 
    ls->confSaveAsMachineName   = "Nome della macchina:";
    ls->confDiscardTitle        = "blueMSX - Configurazione";
    ls->confExitSaveTitle       = "blueMSX - Esci dall'editor di configurazione";
    ls->confExitSaveText        = "Vuoi annullare i cambiamenti apportati alla configurazione attuale?";

    ls->confSlotLayoutGB        = "Disposizione degli slot ";
    ls->confSlotExtSlotGB       = "Slot esterni ";
    ls->confBoardGB             = "Sistema "; 
    ls->confBoardText           = "Sistema tipo:"; 
    ls->confSlotPrimary         = "Primario";
    ls->confSlotExpanded        = "Espanso (4 subslot)";

    ls->confSlotCart            = "Cartuccia 1:";
    ls->confSlot                = "Slot"; 
    ls->confSubslot             = "Subslot"; 

    ls->confMemAdd              = "Aggiungi...";
    ls->confMemEdit             = "Modifica...";
    ls->confMemRemove           = "Rimuovi";
    ls->confMemSlot             = "Slot";
    ls->confMemAddresss         = "Indirizzo";
    ls->confMemType             = "Tipo";
    ls->confMemRomImage         = "Immagine .ROM";
    
    ls->confChipVideoGB         = "Video ";
    ls->confChipVideoChip       = "Chip video:";
    ls->confChipVideoRam        = "RAM video:";
    ls->confChipSoundGB         = "Audio ";

    ls->confCmosGB              = "CMOS ";
    ls->confCmosEnable          = "Abilita CMOS";
    ls->confCmosBattery         = "Batteria carica";

    ls->confCpuFreqGB           = "Frequenza CPU "; 
    ls->confZ80FreqText         = "Frequenza Z80:"; 
    ls->confR800FreqText        = "Frequenza R800:"; 
    ls->confFdcGB               = "Controller Floppy Disk "; 
    ls->confCFdcNumDrivesText   = "Numero di unit�:"; 

    ls->confEditMemTitle        = "blueMSX - Modifica il Mapper";
    ls->confEditMemGB           = "Dettagli del Mapper ";
    ls->confEditMemType         = "Tipo:";
    ls->confEditMemFile         = "File:";
    ls->confEditMemAddress      = "Indirizzo";
    ls->confEditMemSize         = "Dimensioni";
    ls->confEditMemSlot         = "Slot";


    //----------------------
    // Shortcut lines
    //----------------------

    ls->shortcutKey             = "Azioni"; 
    ls->shortcutDescription     = "Tasti rapidi"; 

    ls->shortcutSaveConfig      = "blueMSX - Salva la configurazione";
    ls->shortcutOverwriteConfig = "Vuoi sovrascrivere la configurazione della macchina ?";
    ls->shortcutExitConfig      = "blueMSX - Esci dall'editor tasti rapidi ";
    ls->shortcutDiscardConfig   = "Vuoi annullare i cambiamenti apportati alla configurazione attuale?";
    ls->shortcutSaveConfigAs    = "blueMSX - Salva la configurazione con nome ";
    ls->shortcutConfigName      = "Nome della configurazione";
    ls->shortcutNewProfile      = "< Nuovo Profilo >";
    ls->shortcutConfigTitle     = "blueMSX - Editor tasti rapidi";
    ls->shortcutAssign          = "Assegna";
    ls->shortcutPressText       = "Combinazione tasti rapidi:";
    ls->shortcutScheme          = "Profilo:";
    ls->shortcutCartInsert1     = "Inserimento cartuccia nello slot 1";
    ls->shortcutCartRemove1     = "Rimozione cartuccia dallo slot 1 ";
    ls->shortcutCartInsert2     = "Inserimento cartuccia nello slot 2";
    ls->shortcutCartRemove2     = "Rimozione cartuccia dallo slot 2";
    ls->shortcutSpecialMenu1    = "Mostra menu speciale per la cartuccia dello slot 1";
    ls->shortcutSpecialMenu2    = "Mostra menu speciale per la cartuccia dello slot 2";
    ls->shortcutCartAutoReset   = "Riavvio emulatore dopo l'inserimento cartuccia";
    ls->shortcutDiskInsertA     = "Inserimento floppy nell'unit� A";
    ls->shortcutDiskDirInsertA  = "Inserisci una cartella come disco A"; 
    ls->shortcutDiskRemoveA     = "Rimozione floppy nell'unit� A";
    ls->shortcutDiskChangeA     = "Cambio rapido del floppy nell'unit� A";
    ls->shortcutDiskAutoResetA  = "Riavvio emulatore dopo inserimento floppy nell'unit� A";
    ls->shortcutDiskInsertB     = "Inserimento floppy nell'unit� B";
    ls->shortcutDiskDirInsertB  = "Inserisci una directory come disco B"; 
    ls->shortcutDiskRemoveB     = "Rimozione floppy nell'unit� B";
    ls->shortcutCasInsert       = "Inserimento immagine cassetta";
    ls->shortcutCasEject        = "Rimozione immagine cassetta";
    ls->shortcutCasAutorewind   = "Riavvolgimento automatico o meno della cassetta";
    ls->shortcutCasReadOnly     = "Cassetta nel modo a sola lettura o meno";
    ls->shortcutCasSetPosition  = "Impostazione della posizione del nastro";
    ls->shortcutCasRewind       = "Riavvolgimento cassetta";
    ls->shortcutCasSave         = "Salvataggio immagine nastro con nome";
    ls->shortcutPrnFormFeed     = "Passaggio alla pagina seguente"; 
    ls->shortcutCpuStateLoad    = "Caricamento dello stato della CPU";
    ls->shortcutCpuStateSave    = "Salvataggio dello stato della CPU";
    ls->shortcutCpuStateQload   = "Caricamento rapido dello stato della CPU";
    ls->shortcutCpuStateQsave   = "Salvataggio rapido dello stato della CPU";
    ls->shortcutAudioCapture    = "Avvia/Ferma la cattura audio ";
    ls->shortcutScreenshotOrig  = "Salvataggio di uno screenshot";
    ls->shortcutScreenshotSmall = "Salvataggio breve di uno screenshot senza filtro";
    ls->shortcutScreenshotLarge = "Salvataggio completo di uno screenshot senza filtro";
    ls->shortcutQuit            = "Uscita da blueMSX";
    ls->shortcutRunPause        = "Start/Pausa Emulatore";
    ls->shortcutStop            = "Stop Emulatore";
    ls->shortcutResetHard       = "Riavvio hardware";
    ls->shortcutResetSoft       = "Riavvio software";
    ls->shortcutResetClean      = "Riavvio completo";
    ls->shortcutSizeSmall       = "Passare in modalit� finestra piccola";
    ls->shortcutSizeNormal      = "Passare in modalit� finestra normale";
    ls->shortcutSizeFullscreen  = "Passare in modalit� schermo intero";
    ls->shortcutSizeMinimized   = "Minimizzi la finestra"; 
    ls->shortcutToggleFullscren = "Bilanciamento modalit� finestra/schermo intero";
    ls->shortcutVolumeIncrease  = "Aumentare il volume del suono";
    ls->shortcutVolumeDecrease  = "Diminuire il volume del suono";
    ls->shortcutVolumeMute      = "Stabilire il suono";
    ls->shortcutVolumeStereo    = "Bilanciamento mono/stereo";
    ls->shortcutSwitchMsxAudio  = "Attivare l'MSX-AUDIO Panasonic";
    ls->shortcutSwitchFront     = "Attivare l'interruttore frontale Panasonic";
    ls->shortcutSwitchPause     = "Attivare il tasto pausa Panasonic"; 
    ls->shortcutToggleMouseLock = "Attivare/disattivare il blocco del mouse";
    ls->shortcutEmuSpeedMax     = "Velocit� massima dell'emulazione";
    ls->shortcutEmuSpeedToggle  = "Bilancia la velocit� massima dell'emulazione"; 
    ls->shortcutEmuSpeedNormal  = "Velocit� normale dell'emulazione";
    ls->shortcutEmuSpeedInc     = "Aumentare la velocit� dell'emulazione";
    ls->shortcutEmuSpeedDec     = "Diminuire la velocit� dell'emulazione";
    ls->shortcutThemeSwitch     = "Cambia il tema";
    ls->shortcutShowEmuProp     = "Mostra propriet� dell'emulazione";
    ls->shortcutShowVideoProp   = "Mostra propriet� Video";
    ls->shortcutShowAudioProp   = "Mostra propriet� Audio";
    ls->shortcutShowCtrlProp    = "Mostra propriet� Controlli";
    ls->shortcutShowPerfProp    = "Mostra propriet� Prestazioni";
    ls->shortcutShowSettProp    = "Mostra propriet� Impostazioni";
    ls->shortcutShowPorts       = "Mostra propriet� delle Porte";
    ls->shortcutShowLanguage    = "Mostra dialogo per la scelta del linguaggio";
    ls->shortcutShowMachines    = "Mostra editor della macchina";
    ls->shortcutShowShortcuts   = "Mostra editor dei tasti rapidi";
    ls->shortcutShowKeyboard    = "Mostra editor dei controlli/tastiera"; 
    ls->shortcutShowDebugger    = "Mostra Debugger"; 
    ls->shortcutShowTrainer     = "Mostra Trainer"; 
    ls->shortcutShowMixer       = "Mostra Mixer"; 
    ls->shortcutShowHelp        = "Accedere agli argomenti dell'aiuto";
    ls->shortcutShowAbout       = "Vedere informazioni su blueMSX";
    ls->shortcutShowFiles       = "Mostra propriet� File";
    ls->shortcutToggleSpriteEnable = "Mostra/Disattiva gli Sprite";
    ls->shortcutToggleFdcTiming = "Sincronizzare o no disco floppy"; 
    ls->shortcutToggleCpuTrace  = "Convalidare/invalidare la traccia della CPU"; 
    ls->shortcutVideoLoad       = "Apri un video acquisito";              // New in 2.6
    ls->shortcutVideoPlay       = "Esegui l'ultimo video acquisito";      // New in 2.6
    ls->shortcutVideoRecord     = "Registra il video";         // New in 2.6
    ls->shortcutVideoStop       = "Ferma la registrazione video";         // New in 2.6
    ls->shortcutVideoRender     = "Crea una clip video";                  // New in 2.6


    //----------------------
    // Keyboard config lines
    //----------------------

    ls->keyconfigSelectedKey    = "Tasto scelto:"; 
    ls->keyconfigMappedTo       = "Assegnato a:"; 
    ls->keyconfigMappingScheme  = "Configurazione dei Tasti:"; 

    
    //----------------------
    // Rom type lines
    //----------------------

    ls->romTypeStandard         = "Standard";
    ls->romTypeZenima80         = "Zemina 80 in 1";
    ls->romTypeZenima90         = "Zemina 90 in 1";
    ls->romTypeZenima126        = "Zemina 126 in 1";
    ls->romTypeSccMirrored      = "SCC mirrored";
    ls->romTypeSccExtended      = "SCC extended";
    ls->romTypeKonamiGeneric    = "Konami Generic";
    ls->romTypeMirrored         = "Mirrored ROM";
    ls->romTypeNormal           = "Normal ROM";
    ls->romTypeDiskPatch        = "Normal + Disk Patch";
    ls->romTypeCasPatch         = "Normal + Cassette Patch";
    ls->romTypeTc8566afFdc      = "TC8566AF Disk Controller";
    ls->romTypeMicrosolFdc      = "Microsol Disk Controller";
    ls->romTypeNationalFdc      = "National Disk Controller";
    ls->romTypePhilipsFdc       = "Philips Disk Controller";
    ls->romTypeSvi738Fdc        = "SVI-738 Disk Controller";
    ls->romTypeMappedRam        = "Mapped RAM";
    ls->romTypeMirroredRam1k    = "1kB Mirrored RAM";
    ls->romTypeMirroredRam2k    = "2kB Mirrored RAM";
    ls->romTypeNormalRam        = "Normal RAM";
    ls->romTypeTurborPause      = "Turbo-R Pause";
    ls->romTypeF4deviceNormal   = "F4 Device Normal";
    ls->romTypeF4deviceInvert   = "F4 Device Inverted";
    ls->romTypeTurborTimer      = "Turbo-R Timer";
    ls->romTypeNormal4000       = "Normal 4000h";
    ls->romTypeNormalC000       = "Normal C000h";
    ls->romTypeExtRam           = "External RAM";
    ls->romTypeExtRam512        = "512kB External RAM";
    ls->romTypeExtRam1mb        = "1MB External RAM";
    ls->romTypeExtRam2mb        = "2MB External RAM";
    ls->romTypeExtRam4mb        = "4MB External RAM";
    ls->romTypeSvi328Cart       = "SVI-328 Cartridge";
    ls->romTypeSvi328Fdc        = "SVI-328 Disk Controller";
    ls->romTypeSvi328Prn        = "SVI-328 Printer";
    ls->romTypeSvi328Uart       = "SVI-328 Serial Port";
    ls->romTypeSvi328col80      = "SVI-328 80 Column Card";
    ls->romTypeSvi727col80      = "SVI-727 80 Column Card";
    ls->romTypeColecoCart       = "Coleco Cartridge";
    ls->romTypeSg1000Cart       = "SG-1000 Cartridge";
    ls->romTypeSc3000Cart       = "SC-3000 Cartridge";
    ls->romTypeMsxPrinter       = "MSX Printer";
    ls->romTypeTurborPcm        = "Turbo-R PCM Chip";
    ls->romTypeNms8280Digitiz   = "Philips NMS-8280 Digitizer";
    ls->romTypeHbiV1Digitiz     = "Sony HBI-V1 Digitizer";
    
    
    //----------------------
    // Debug type lines
    // Note: Only needs translation if debugger is translated
    //----------------------

    ls->dbgMemVisible           = "Visible Memory";
    ls->dbgMemRamNormal         = "Normal";
    ls->dbgMemRamMapped         = "Mapped";
    ls->dbgMemYmf278            = "YMF278 Sample RAM";
    ls->dbgMemAy8950            = "AY8950 Sample RAM";
    ls->dbgMemScc               = "Memory";

    ls->dbgCallstack            = "Callstack";

    ls->dbgRegs                 = "Registers";
    ls->dbgRegsCpu              = "CPU Registers";
    ls->dbgRegsYmf262           = "YMF262 Registers";
    ls->dbgRegsYmf278           = "YMF278 Registers";
    ls->dbgRegsAy8950           = "AY8950 Registers";
    ls->dbgRegsYm2413           = "YM2413 Registers";

    ls->dbgDevRamMapper         = "RAM Mapper";
    ls->dbgDevRam               = "RAM";
    ls->dbgDevF4Device          = "F4 Device";
    ls->dbgDevKorean80          = "Korean 80";
    ls->dbgDevKorean90          = "Korean 90";
    ls->dbgDevKorean128         = "Korean 128";
    ls->dbgDevFdcMicrosol       = "Microsol FDC";
    ls->dbgDevPrinter           = "Printer";
    ls->dbgDevSviFdc            = "SVI FDC";
    ls->dbgDevSviPrn            = "SVI Printer";
    ls->dbgDevSvi80Col          = "SVI 80 Column";
    ls->dbgDevRtc               = "RTC";
    ls->dbgDevTrPause           = "TR Pause";


    //----------------------
    // Debug type lines
    // Note: Can only be translated to european languages
    //----------------------

    ls->aboutScrollThanksTo     = "Un ringraziamento speciale a:";
    ls->aboutScrollAndYou       = "e TU !!!!";
};

#endif
