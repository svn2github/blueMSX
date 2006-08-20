/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageSpannish.h,v $
**
** $Revision: 1.38 $
**
** $Date: 2006-08-20 05:04:09 $
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
#ifndef LANGUAGE_SPANISH_H
#define LANGUAGE_SPANISH_H

#include "LanguageStrings.h"

void langInitSpanish(LanguageStrings* ls)
{
    //----------------------
    // Language lines
    //----------------------

    ls->langChineseSimplified   = "Chino simplificado";
    ls->langChineseTraditional  = "Chino tradicional";
    ls->langDutch               = "Holand�s";
    ls->langEnglish             = "Ingl�s";
    ls->langFinnish             = "Finland�s";
    ls->langFrench              = "Franc�s";
    ls->langGerman              = "Alem�n";
    ls->langItalian             = "Italiano";
    ls->langJapanese            = "Japon�s";
    ls->langKorean              = "Coreano";
    ls->langPolish              = "Polaco";
    ls->langPortuguese          = "Portugu�s";
    ls->langSpanish             = "Espa�ol";
    ls->langSwedish             = "Sueco";


    //----------------------
    // Generic lines
    //----------------------

    ls->textDevice              = "Tipo:"; 
    ls->textFilename            = "Nombre:"; 
    ls->textFile                = "Archivo"; 
    ls->textNone                = "Ninguno"; 
    ls->textUnknown             = "Desconocido";                            


    //----------------------
    // Warning and Error lines
    //----------------------

    ls->warningTitle             = "blueMSX - Advertencia";
    ls->warningDiscardChanges   = "Quieres descartar cambios de la configuraci�n actual?"; 
    ls->warningOverwriteFile    = "Usted desea sobreescribir este archivo?:"; 
    ls->errorTitle              = "blueMSX - Error";
    ls->errorEnterFullscreen    = "Error al intentar Modo Pantalla Completa             \n";
    ls->errorDirectXFailed      = "Error al crear objetos DirectX.           \n.\nComprueba configuraci�n de V�deo.";
    ls->errorNoRomInZip         = "No hay archivo .rom en el archivo zip.";
    ls->errorNoDskInZip         = "No hay archivo .dsk en el archivo zip.";
    ls->errorNoCasInZip         = "No hay archivo .cas en el archivo zip.";
    ls->errorNoHelp             = "Imposible encontrar archivo de ayuda de BlueMSX.";
    ls->errorStartEmu           = "Error al iniciar MSX emulator.";
    ls->errorPortableReadonly   = "El dispositivo portable es s�lo lectura";        


    //----------------------
    // File related lines
    //----------------------

    ls->fileRom                 = "ROM image"; 
    ls->fileAll                 = "Todos los archivos"; 
    ls->fileCpuState            = "Carga CPU"; 
    ls->fileVideoCapture        = "Video Capture"; // New in 2.6
    ls->fileDisk                = "Disk Image"; 
    ls->fileCas                 = "Tape Image"; 
    ls->fileAvi                 = "Video Clip";    // New in 2.6


    //----------------------
    // Menu related lines
    //----------------------

    ls->menuNoRecentFiles       = "- No hay archivos recientes -";
    ls->menuInsert              = "Insertar";
    ls->menuEject               = "Sacar";

    ls->menuCartGameReader      = "Game Reader";                        
    ls->menuCartIde             = "IDE";                                
    ls->menuCartBeerIde         = "Beer";                               
    ls->menuCartGIde            = "GIDE";                               
    ls->menuCartSunriseIde      = "Sunrise";                            
    ls->menuCartSCCPlus         = "Cartucho SCC+";
    ls->menuCartSCC             = "Cartucho SCC";
    ls->menuCartFMPac           = "Cartucho FM-PAC";
    ls->menuCartPac             = "Cartucho PAC";
    ls->menuCartHBI55           = "Cartucho Sony HBI-55"; 
    ls->menuCartInsertSpecial   = "Insertar Especial";                     
    ls->menuCartMegaRam         = "MegaRAM";                            
    ls->menuCartExternalRam     = "RAM externo"; 

    ls->menuDiskInsertNew       = "Insertar nueva imagen de Disco";              
    ls->menuDiskDirInsert       = "Insertar directorio"; 
    ls->menuDiskAutoStart       = "Reinicio Tras Insertar";
    ls->menuCartAutoReset       = "Reinicio Tras Insertar/Sacar";

    ls->menuCasRewindAfterInsert = "Rebovinar tras Insertar";
    ls->menuCasUseReadOnly       = "Usar Imagen de Cassette S�lo Lectura";
    ls->lmenuCasSaveAs           = "Salvar Imagen de Cassette Como...";
    ls->menuCasSetPosition      = "Posicionar";
    ls->menuCasRewind           = "Rebovinar";

    ls->menuVideoLoad           = "Load...";             // New in 2.6
    ls->menuVideoPlay           = "Play Last Capture";   // New in 2.6
    ls->menuVideoRecord         = "Record";              // New in 2.6
    ls->menuVideoRecording      = "Recording";           // New in 2.6
    ls->menuVideoRecAppend      = "Record (append)";     // New in 2.6
    ls->menuVideoStop           = "Stop";                // New in 2.6
    ls->menuVideoRender         = "Render Video File";   // New in 2.6

    ls->menuPrnFormfeed         = "P�gina siguiente"; 

    ls->menuZoomNormal          = "Tama�o Peque�a";
    ls->menuZoomDouble          = "Tama�o Normal";
    ls->menuZoomFullscreen      = "Pantalla Completa";

    ls->menuPropsEmulation      = "Emulaci�n";
    ls->menuPropsVideo          = "V�deo";
    ls->menuPropsSound          = "Sonido";
    ls->menuPropsControls       = "Controles";
    ls->menuPropsPerformance    = "Rendimiento";
    ls->menuPropsSettings        = "Configuraciones";
    ls->menuPropsFile           = "Archivo";
    ls->menuPropsLanguage       = "Idioma";
    ls->menuPropsPorts          = "Puertos"; 

    ls->menuVideoSource         = "Salida V�deo";                   
    ls->menuVideoSourceDefault  = "Salida V�deo no conectada";      
    ls->menuVideoChipAutodetect = "Detecci�n autom�tica";     
    ls->menuVideoInSource       = "Entrada v�deo";                    
    ls->menuVideoInBitmap       = "Archivo Bitmap";                        

    ls->menuHelpHelp            = "Ayuda";
    ls->menuHelpAbout           = "Acerca De blueMSX";

    ls->menuFileCart            = "Cartucho Slot";
    ls->menuFileDisk            = "Unidad Disco";
    ls->menuFileCas             = "Cassette";
    ls->menuFilePrn             = "Impresora"; 
    ls->menuFileLoadState       = "Estado Carga CPU";
    ls->menuFileSaveState       = "Grabar Estado CPU";
    ls->menuFileQLoadState      = "Carga r�pida Estado";
    ls->menuFileQSaveState      = "Grabaci�n R�pida Estado";
    ls->menuFileCaptureAudio    = "Captura Audio";
    ls->menuFileCaptureVideo    = "Video Capture"; // New in 2.6
    ls->menuFileScreenShot      = "Grabar Pantalla";
    ls->menuFileExit            = "Salir";

    ls->menuFileHarddisk        = "Disco duro";                          
    ls->menuFileHarddiskNoPesent= "No hay controladores";             

    ls->menuRunRun              = "Ejecutar";
    ls->menuRunPause            = "Pausar";
    ls->menuRunStop             = "Parada";
    ls->menuRunSoftReset        = "Reinicio Software";
    ls->menuRunHardReset        = "Reinicio Hardware";
    ls->menuRunCleanReset       = "Reinicio Completo";

    ls->menuToolsMachine        = "Editor de M�quina";
    ls->menuToolsShortcuts      = "Editor de Atajos";
    ls->menuToolsCtrlEditor     = "Editor de controladores/teclado";  // New in 2.6
    ls->menuToolsMixer          = "Mezclador de Audio"; 
    ls->menuToolsDebugger       = "Debugger";               
    ls->menuToolsTrainer        = "Trainer";                
    ls->menuToolsTraceLogger    = "Trace Logger";           

    ls->menuFile                = "Archivo";
    ls->menuRun                 = "Emulaci�n";
    ls->menuWindow              = "Ventana";
    ls->menuOptions             = "Opciones";
    ls->menuTools                = "Herramientas";
    ls->menuHelp                = "Ayuda";


    //----------------------
    // Dialog related lines
    //----------------------

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Open";
    ls->dlgCancel               = "Cancelar";
    ls->dlgSave                 = "Guardar";
    ls->dlgSaveAs               = "Guardar Como...";
    ls->dlgRun                  = "Ejecutar";
    ls->dlgClose                = "Cerrar";

    ls->dlgLoadRom              = "blueMSX - Seleccionar imagen Rom a cargar";
    ls->dlgLoadDsk              = "blueMSX - Seleccionar imagen Dsk a cargar";
    ls->dlgLoadCas              = "blueMSX - Seleccionar imagen Cas a cargar";
    ls->dlgLoadRomDskCas        = "blueMSX - Seleccionar un archivo Rom, Dsk, or Cas a cargar";
    ls->dlgLoadRomDesc          = "Seleccionar imagen Rom a cargar:";
    ls->dlgLoadDskDesc          = "Seleccionar imagen de disco a cargar:";
    ls->dlgLoadCasDesc          = "Seleccionar imagen de cinta a cargar:";
    ls->dlgLoadRomDskCasDesc    = "Seleccionar imagen Rom, Disco, o Cinta a cargar:";
    ls->dlgLoadState            = "Cargar Estado CPU";
    ls->dlgLoadVideoCapture     = "Load video capture";      // New in 2.6
    ls->dlgSaveState            = "Salvar Estado CPU";
    ls->dlgSaveCassette          = "blueMSX - Salvar Imagen de Cinta";
    ls->dlgSaveVideoClipAs      = "Save video clip as...";      // New in 2.6
    ls->dlgAmountCompleted      = "Amount completed:";          // New in 2.6
    ls->dlgInsertRom1           = "Insertar Cartucho ROM en slot 1";
    ls->dlgInsertRom2           = "Insertar Cartucho ROM en slot 2";
    ls->dlgInsertDiskA          = "Insertar imagen de Disco en Unidad A";
    ls->dlgInsertDiskB          = "Insertar imagen de Disco en Unidad B";
    ls->dlgInsertHarddisk       = "Insertar disco duro";                   
    ls->dlgInsertCas            = "Insertar Cinsta de cassette";
    ls->dlgRomType              = "Tipo rom:"; 
    ls->dlgDiskSize             = "Disk Size:";             // New in 2.6

    ls->dlgTapeTitle            = "blueMSX - Posici�n de la Cinta";
    ls->dlgTapeFrameText        = "Posici�n de la Cinta";
    ls->dlgTapeCurrentPos       = "Posici�n Actual";
    ls->dlgTapeTotalTime        = "Tiempo Total";
    ls->dlgTapeSetPosText        = "Posici�n de la Cinta:";
    ls->dlgTapeCustom            = "Mostrar Archivos Personalizados";
    ls->dlgTabPosition           = "Posici�n";
    ls->dlgTabType               = "Tipo";
    ls->dlgTabFilename           = "Nombre Archivo";
    ls->dlgZipReset             = "Reiniciar Tras Insertar";

    ls->dlgAboutTitle           = "blueMSX - Acerca de";

    ls->dlgLangLangText         = "Seleccionar Idioma";
    ls->dlgLangLangTitle        = "blueMSX - Idioma";

    ls->dlgAboutAbout           = "Acerca de\r\n====";
    ls->dlgAboutVersion         = "Versi�n:";
    ls->dlgAboutBuildNumber     = "Compilaci�n:";
    ls->dlgAboutBuildDate       = "Fecha:";
    ls->dlgAboutCreat           = "Desarrollado por Daniel Vik";
    ls->dlgAboutDevel           = "PROGRAMADORES\r\n========";
    ls->dlgAboutThanks          = "MUCHAS GRACIAS A\r\n============";
    ls->dlgAboutLisence         = "LICENCIA\r\n"
                                  "======\r\n\r\n"
                                  "Este software se proporciona tal y como es, sin ninguna garant�a."
                                  "En ning�n caso el/los autores ser�n responsablesny de posibles da�os "
                                  "producidos por el uso de este software.\r\n\r\n"
                                  "Para m�s detalles, visita la web www.bluemsx.com.";

    ls->dlgSavePreview          = "Imaginar"; 
    ls->dlgSaveDate             = "Fecha:"; 

    ls->dlgRenderVideoCapture   = "blueMSX - Rendering Video Capture...";  // New in 2.6


    //----------------------
    // Properties related lines
    //----------------------

    ls->propTitle               = "blueMSX - Propiedades";
    ls->propEmulation           = "Emulaci�n";
    ls->propVideo               = "Video";
    ls->propSound               = "Sonido";
    ls->propControls            = "Controles";
    ls->propPerformance         = "Rendimiento";
    ls->propSettings             = "Configuraciones";
    ls->propFile                = "Archivo"; 
    ls->propPorts               = "Puertos";

    ls->propEmuGeneralGB        = "General ";
    ls->propEmuFamilyText       = "Familia MSX:";
    ls->propEmuMemoryGB         = "Memoria ";
    ls->propEmuRamSizeText      = "Tama�o RAM:";
    ls->propEmuVramSizeText     = "Tama�o VRAM:";
    ls->propEmuSpeedGB          = "Velocidad de la Emulaci�n ";
    ls->propEmuSpeedText        = "Velocidad de la Emulaci�n:";
    ls->propEmuFrontSwitchGB     = "Botones Panasonic "; 
    ls->propEmuFrontSwitch       = " Bot�n Frontal"; 
    ls->propEmuFdcTiming        = "No sincronizar unidade disco"; 
    ls->propEmuPauseSwitch      = " Bot�n Pause"; 
    ls->propEmuAudioSwitch       = " Bot�n cartucho MSX-AUDIO"; 
    ls->propVideoFreqText       = "Frecuencia video:"; 
    ls->propVideoFreqAuto       = "Auto"; 
    ls->propSndOversampleText   = "Oversample:"; 
    ls->propSndYkInGB           = "YK-01/YK-10/YK-20 In ";                
    ls->propSndMidiInGB         = "MIDI In "; 
    ls->propSndMidiOutGB        = "MIDI Out "; 
    ls->propSndMidiChannel      = "Canal MIDI:";                      
    ls->propSndMidiAll          = "Todos";                                

    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Tipo de Monitor:";
    ls->propMonEmuText          = "Emulaci�n del Monitor:";
    ls->propVideoTypeText       = "Tipo de Video:";
    ls->propWindowSizeText      = "Tama�o de Ventana:";
    ls->propMonHorizStretch      = " Estiramiento Horizontal";
    ls->propMonVertStretch       = " Estiramiento Vertical";
    ls->propMonDeInterlace      = " De-entrelace";
    ls->propBlendFrames         = " Mezclar frames consecutivas";           
    ls->propMonBrightness       = "Brillo:";
    ls->propMonContrast         = "Contraste:";
    ls->propMonSaturation       = "Saturaci�n:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanlines:";
    ls->propMonColorGhosting    = "Modulador RF"; 
    ls->propMonEffectsGB        = "Efectos  "; 

    ls->propPerfVideoDrvGB      = "Controlador de Video ";
    ls->propPerfVideoDispDrvText= "Controlador de Pantalla:";
    ls->propPerfFrameSkipText   = "Omisi�n de Frames:";
    ls->propPerfAudioDrvGB      = "Controlador de Audio ";
    ls->propPerfAudioDrvText    = "Controlador de Sonido:";
    ls->propPerfAudioBufSzText  = "Tama�o del Buffer de sonido:";
    ls->propPerfEmuGB           = "Emulaci�n ";
    ls->propPerfSyncModeText    = "Modo SYNC:";
    ls->propFullscreenResText   = "Resoluci�n pantalla completa:"; 

    ls->propSndChipEmuGB        = "Emulaci�n Chip de Sonido ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";
    ls->propSndMoonsound         = " Moonsound";
    ls->propSndMt32ToGm         = " Mapa instrumentos MT-32 a General MIDI"; 

    ls->propPortsLptGB          = "Puerto paralelo "; 
    ls->propPortsComGB          = "Puertos seriales "; 
    ls->propPortsLptText        = "Puerto:"; 
    ls->propPortsCom1Text       = "Puerto 1:"; 
    ls->propPortsNone           = "Ninguno";
    ls->propPortsSimplCovox     = "SiMPL / Covox DAC"; 
    ls->propPortsFile           = "Imprimir en archivo"; 
    ls->propPortsComFile        = "Enviar hacia archivo";
    ls->propPortsOpenLogFile    = "Abrir un archivo de datos"; 
    ls->propPortsEmulateMsxPrn  = "Emulaci�n:"; 

    ls->propSetFileHistoryGB     = "Hist�rico de Archivos ";
    ls->propSetFileHistorySize   = "N�mero de items en Hist�rico de Archivos:";
    ls->propSetFileHistoryClear  = "Borrar Host�rico";
    ls->propFileTypes            = " Asociar algunos tipos de archivo con blueMSX";
    ls->propWindowsEnvGB         = "Ambiente Windows";
    ls->propSetScreenSaver       = " Deshabilitar Salvapantallas mientras blueMSX est� en ejecuci�n";
    ls->propDisableWinKeys       = " Funci�n MSX autom�tica para las teclas Windows"; 
    ls->propPriorityBoost       = " Dar a blueMSX una elevada prioridad";
    ls->propScreenshotPng       = " Utilizar el formato PNG para las capturas de pantalla";  
    ls->propClearHistory         = "�Desean realmente borrar host�rico ?";
    ls->propOpenRomGB           = "Abrir archivo rom"; 
    ls->propDefaultRomType      = "Tipo por defecto:"; 
    ls->propGuessRomType        = "Conjeturar tipo"; 

    ls->propSettDefSlotGB       = "Deslizar e depositar "; 
    ls->propSettDefSlots        = "Insertar cartucho en:"; 
    ls->propSettDefSlot         = " Slot"; 
    ls->propSettDefDrives       = "Insertar disco en:"; 
    ls->propSettDefDrive        = " Unidad"; 

    ls->propThemeGB             = "Tema ";
    ls->propTheme               = "Tema";


    //----------------------
    // Dropdown related lines
    //----------------------

    ls->enumVideoMonColor       = "Color";
    ls->enumVideoMonGrey        = "Blanco y Negro";
    ls->enumVideoMonGreen       = "Verde";
    ls->enumVideoMonAmber       = "Ambar"; 

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Ninguno";
    ls->enumVideoEmuYc          = "Cable Y/C";
    ls->enumVideoEmuMonitor     = "Monitor"; 
    ls->enumVideoEmuYcBlur      = "Cable Y/C ruidoso";
    ls->enumVideoEmuComp        = "Compuesto";
    ls->enumVideoEmuCompBlur    = "Compuesto Ruidoso";
    ls->enumVideoEmuScale2x     = "Escala 2x";
    ls->enumVideoEmuHq2x        = "Hq2x"; 

    ls->enumVideoSize1x         = "Normal - 320x200";
    ls->enumVideoSize2x         = "Doble - 640x400";
    ls->enumVideoSizeFullscreen = "Pantalla Completa";

    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW acel.";
    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "Ninguno";
    ls->enumVideoFrameskip1     = "1 frame";
    ls->enumVideoFrameskip2     = "2 frames";
    ls->enumVideoFrameskip3     = "3 frames";
    ls->enumVideoFrameskip4     = "4 frames";
    ls->enumVideoFrameskip5     = "5 frames";

    ls->enumSoundDrvNone        = "Sin Sonido";
    ls->enumSoundDrvWMM         = "Controlador WMM";
    ls->enumSoundDrvDirectX     = "Controlador DirectX";

    ls->enumEmuSync1ms          = "Sinc sobre MSX refresh"; 
    ls->enumEmuSyncAuto         = "Auto (r�pido)"; 
    ls->enumEmuSyncNone         = "Ninguno"; 
    ls->enumEmuSyncVblank       = "Sinc sobre PC Vertical Blank"; 
    ls->enumEmuAsyncVblank      = "Asincr�nico PC Vblank";             

    ls->enumControlsJoyNone     = "Ninguno";
    ls->enumControlsJoyMouse    = "Rat�n";
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle"; 
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey Dongle";             
    ls->enumControlsJoy2Button = "2-button Joystick";                   
    ls->enumControlsJoyGunstick  = "Gun Stick";                         
    ls->enumControlsJoyAsciiLaser="ASCII Plus-X Terminator Laser";      
    ls->enumControlsJoyColeco = "ColecoVision Joystick";                

    ls->enumDiskMsx35Dbl9Sect    = "MSX 3.5\" doble cara, 9 sectores";     
    ls->enumDiskMsx35Dbl8Sect    = "MSX 3.5\" doble cara, 8 sectores";     
    ls->enumDiskMsx35Sgl9Sect    = "MSX 3.5\" simple cara, 9 sectores";     
    ls->enumDiskMsx35Sgl8Sect    = "MSX 3.5\" simple cara, 8 sectores";     
    ls->enumDiskSvi525Dbl        = "SVI-328 5.25\" doble cara";           
    ls->enumDiskSvi525Sgl        = "SVI-328 5.25\" simple cara";  
    ls->enumDiskSf3Sgl           = "Sega SF-7000 3\" simple cara";  // New in 2.6         


    //----------------------
    // Configuration related lines
    //----------------------

    ls->confTitle                = "blueMSX - Editor de Configuraci�n de M�quina";
    ls->confConfigText           = "Configuraci�n";
    ls->confSlotLayout           = "Esquema del Slot";
    ls->confMemory               = "Memoria";
    ls->confChipEmulation        = "Emulaci�n de Chip";
    ls->confChipExtras          = "Extras"; 

    ls->confOpenRom             = "Abrirse ROM image"; 
    ls->confSaveTitle            = "blueMSX - Guardar Configuraci�n";
    ls->confSaveText             = "Usted desea sobreescribir la configuraci�n de m�quina?:";
    ls->confSaveAsTitle         = "Guardar Como..."; 
    ls->confSaveAsMachineName    = "Nombre de M�quina:";
    ls->confDiscardTitle         = "blueMSX - Configuraci�n ";
    ls->confExitSaveTitle        = "blueMSX - Salir del Editor de Configuraci�n";
    ls->confExitSaveText         = "Quieres descartar cambios de la configuraci�n actual?";

    ls->confSlotLayoutGB         = "Esquema del Slot ";
    ls->confSlotExtSlotGB        = "Slots Externos ";
    ls->confBoardGB             = "Sistema "; 
    ls->confBoardText           = "Sistema tipo:"; 
    ls->confSlotPrimary          = "Primario";
    ls->confSlotExpanded         = "Expandido (cuator subslots)";

    ls->confSlotCart             = "Cartucho";
    ls->confSlot                = "Slot"; 
    ls->confSubslot             = "Subslot"; 

    ls->confMemAdd               = "A�adir...";
    ls->confMemEdit              = "Editar...";
    ls->confMemRemove            = "Borrar";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Direcci�n";
    ls->confMemType              = "Tipo";
    ls->confMemRomImage          = "Imagen Rom";
    
    ls->confChipVideoGB          = "Video ";
    ls->confChipVideoChip        = "Chip Video:";
    ls->confChipVideoRam         = "RAM Video:";
    ls->confChipSoundGB          = "Sonido ";

    ls->confCmosGB               = "CMOS "; 
    ls->confCmosEnable           = " Activar el CMOS"; 
    ls->confCmosBattery          = " Utilizar una Bater�a Cargada";

    ls->confCpuFreqGB            = "Frecuencia CPU "; 
    ls->confZ80FreqText          = "Frecuencia Z80:"; 
    ls->confR800FreqText         = "Frecuencia R800:"; 
    ls->confFdcGB                = "Regulador De Diskette "; 
    ls->confCFdcNumDrivesText    = "N�mero de unidades:"; 

    ls->confEditMemTitle         = "blueMSX - Editar Mapa";
    ls->confEditMemGB            = "Detalles Mapa ";
    ls->confEditMemType          = "Tipo:";
    ls->confEditMemFile          = "Archivo:";
    ls->confEditMemAddress       = "Direcci�n";
    ls->confEditMemSize          = "Tama�o";
    ls->confEditMemSlot          = "Slot";


    //----------------------
    // Shortcut lines
    //----------------------

    ls->shortcutKey             = "Tecla r�pida"; 
    ls->shortcutDescription     = "Atajo"; 

    ls->shortcutSaveConfig      = "blueMSX -  - Guardar Configuraci�n";
    ls->shortcutOverwriteConfig = "Usted desea sobreescribir la configuraci�n del atajo?:";
    ls->shortcutExitConfig      = "blueMSX - Salir del Editor de Atajos";
    ls->shortcutDiscardConfig   = "Quieres descartar cambios de la configuraci�n actual?";
    ls->shortcutSaveConfigAs    = "blueMSX - Guardar Configuraci�n de Atajos como...";
    ls->shortcutConfigName      = "Nombre de la configuraci�n:";
    ls->shortcutNewProfile      = "< Nuevo Perfil >";
    ls->shortcutConfigTitle     = "blueMSX - Editor de la tarjeta de los atajos";
    ls->shortcutAssign          = "Asigne";
    ls->shortcutPressText       = "Apoyar en la(s) tecla(s) del atajo";
    ls->shortcutScheme          = "Disposici�n:";
    ls->shortcutCartInsert1     = "Insertar Cartucho ROM en slot 1";
    ls->shortcutCartRemove1     = "Sacar Cartucho ROM en slot 1";
    ls->shortcutCartInsert2     = "Insertar Cartucho ROM en slot 2";
    ls->shortcutCartRemove2     = "Sacar Cartucho ROM en slot 2";
    ls->shortcutSpecialMenu1    = "Mostrar el men� especial para cartucho 1 ROM en slot 1";
    ls->shortcutSpecialMenu2    = "Mostrar el men� especial para cartucho 1 ROM en slot 2";
    ls->shortcutCartAutoReset   = "Reiniciar Tras Insertar Cartucho ROM";
    ls->shortcutDiskInsertA     = "Insertar imagen de Disco en Unidad A";
    ls->shortcutDiskDirInsertA  = "Insertar un directorio como disco A"; 
    ls->shortcutDiskRemoveA     = "Sacar imagen de Disco en Unidad A";
    ls->shortcutDiskChangeA     = "Cambiar r�pidamente de Disco en Unidad A";
    ls->shortcutDiskAutoResetA  = "Reiniciar Tras Insertar Disco en Unidad A";
    ls->shortcutDiskInsertB     = "Insertar imagen de Disco en Unidad B";
    ls->shortcutDiskDirInsertB  = "Insertar un directorio como disco B";
    ls->shortcutDiskRemoveB     = "Sacar imagen de Disco en Unidad B";
    ls->shortcutCasInsert       = "Insertar Cinsta de cassette";
    ls->shortcutCasEject        = "Sacar Cinsta de cassette";
    ls->shortcutCasAutorewind   = "Rebobinado Autom�tico o no de Cassette";
    ls->shortcutCasReadOnly     = "Cassette en m�todo s�lo Lectura o no";
    ls->shortcutCasSetPosition  = "Posicionar Cassette";
    ls->shortcutCasRewind       = "Rebovinar Cassette";
    ls->shortcutCasSave         = "Salvar Imagen de Cassette";
    ls->shortcutPrnFormFeed     = "Paso a la p�gina siguiente"; 
    ls->shortcutCpuStateLoad    = "Cargar Estado CPU";
    ls->shortcutCpuStateSave    = "Grabar Estado CPU";
    ls->shortcutCpuStateQload   = "Cargar r�pida Estado CPU";
    ls->shortcutCpuStateQsave   = "Grabar r�pida Estado CPU";
    ls->shortcutAudioCapture    = "Iniciar/Pausar captura audio";
    ls->shortcutScreenshotOrig  = "Grabar Pantalla";
    ls->shortcutScreenshotSmall = "Peque�a captura de la pantalla sin filtro";
    ls->shortcutScreenshotLarge = "Gran captura de la pantalla sin filtro";
    ls->shortcutQuit            = "Salir blueMSX";
    ls->shortcutRunPause        = "Ejecutar/Pausar emulaci�n";
    ls->shortcutStop            = "Parada emulaci�n";
    ls->shortcutResetHard       = "Reinicio Hardware";
    ls->shortcutResetSoft       = "Reinicio Software";
    ls->shortcutResetClean      = "Reinicio Completo";
    ls->shortcutSizeSmall       = "Pasar en m�todo ventana tama�o peque�a";
    ls->shortcutSizeNormal      = "Pasar en m�todo ventana tama�o normal";
    ls->shortcutSizeFullscreen  = "Pasar en m�todo pantalla completa";
    ls->shortcutSizeMinimized   = "Reducir la ventana"; 
    ls->shortcutToggleFullscren = "Balanza m�todo ventana/m�todo pantalla completa";
    ls->shortcutVolumeIncrease  = "Aumentar el volumen sonoro";
    ls->shortcutVolumeDecrease  = "Disminuir el volumen sonoro";
    ls->shortcutVolumeMute      = "Parada el sonido";
    ls->shortcutVolumeStereo    = "Balanza mono/stereo";
    ls->shortcutSwitchMsxAudio  = "Impulsar el bot�n cartucho MSX-AUDIO";
    ls->shortcutSwitchFront     = "Impulsar el bot�n frontal Panasonic";
    ls->shortcutSwitchPause     = "Impulsar el bot�n Pause"; 
    ls->shortcutToggleMouseLock = "Activar/desactivar el bloqueo del rat�n";
    ls->shortcutEmuSpeedMax     = "Velocidad m�xima de la emulaci�n";
    ls->shortcutEmuSpeedToggle  = "Balanza velocitad m�xima de la emulaci�n"; 
    ls->shortcutEmuSpeedNormal  = "Velocidad normal de la emulaci�n";
    ls->shortcutEmuSpeedInc     = "Aumentar la velocidad de la emulaci�n";
    ls->shortcutEmuSpeedDec     = "Disminuir la velocidad de la emulaci�n";
    ls->shortcutThemeSwitch     = "Cambiar de tema";
    ls->shortcutShowEmuProp     = "Mostrar las propiedades de la emulaci�n";
    ls->shortcutShowVideoProp   = "Mostraz las propiedades video";
    ls->shortcutShowAudioProp   = "Mostrar las propiedades de sonido";
    ls->shortcutShowCtrlProp    = "Mostrar las propiedades de los controles";
    ls->shortcutShowPerfProp    = "Mostrar las propiedades de redimiento";
    ls->shortcutShowSettProp    = "Mostrar las propiedades de los ajustes";
    ls->shortcutShowPorts       = "Mostrar las propriedades de los puertos";
    ls->shortcutShowLanguage    = "Mostrar di�logo de la idioma";
    ls->shortcutShowMachines    = "Mostrar editor de la m�quina";
    ls->shortcutShowShortcuts   = "Mostrar editor de atajos";
    ls->shortcutShowKeyboard    = "Mostrar editor de controladores/teclado"; 
    ls->shortcutShowMixer       = "Mostrar Mezclador de Audio"; 
    ls->shortcutShowDebugger    = "Mostrar Debugger"; 
    ls->shortcutShowTrainer     = "Mostrar Trainer"; 
    ls->shortcutShowHelp        = "Ver la ayuda";
    ls->shortcutShowAbout       = "Ver la r�brica acerca de blueMSX";
    ls->shortcutShowFiles       = "Mostrar las propiedades de los archivos";
    ls->shortcutToggleSpriteEnable = "Mostrar/ocultar los sprites";
    ls->shortcutToggleFdcTiming = "Sincronizar o no unidade disco"; 
    ls->shortcutToggleCpuTrace  = "Activar/Desactivar Rastro de la CPU"; 


    //----------------------
    // Keyboard config lines
    //----------------------

    ls->keyconfigSelectedKey    = "Tecla MSX:"; 
    ls->keyconfigMappedTo       = "Tecla PC :"; 
    ls->keyconfigMappingScheme  = "Configuraci�n del teclado:"; 

    
    //----------------------
    // Rom type lines
    //----------------------

    ls->romTypeStandard         = "Standard";
    ls->romTypeMsxdos2          = "MSXDOS 2";
    ls->romTypeKonamiScc        = "Konami SCC";
    ls->romTypeKonami           = "Konami";
    ls->romTypeAscii8           = "ASCII 8";
    ls->romTypeAscii16          = "ASCII 16";
    ls->romTypeGameMaster2      = "Game Master 2 (SRAM)";
    ls->romTypeAscii8Sram       = "ASCII 8 (SRAM)";
    ls->romTypeAscii16Sram      = "ASCII 16 (SRAM)";
    ls->romTypeRtype            = "R-Type";
    ls->romTypeCrossblaim       = "Cross Blaim";
    ls->romTypeHarryFox         = "Harry Fox";
    ls->romTypeMajutsushi       = "Konami Majutsushi";
    ls->romTypeZenima80         = "Zemina 80 in 1";
    ls->romTypeZenima90         = "Zemina 90 in 1";
    ls->romTypeZenima126        = "Zemina 126 in 1";
    ls->romTypeScc              = "SCC";
    ls->romTypeSccPlus          = "SCC+";
    ls->romTypeSnatcher         = "The Snatcher";
    ls->romTypeSdSnatcher       = "SD Snatcher";
    ls->romTypeSccMirrored      = "SCC mirrored";
    ls->romTypeSccExtended      = "SCC extended";
    ls->romTypeFmpac            = "FMPAC (SRAM)";
    ls->romTypeFmpak            = "FMPAK";
    ls->romTypeKonamiGeneric    = "Konami Generic";
    ls->romTypeSuperPierrot     = "Super Pierrot";
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
    ls->romTypeNormalRam        = "Normal RAM";
    ls->romTypeKanji            = "Kanji";
    ls->romTypeHolyQuran        = "Holy Quran";
    ls->romTypeMatsushitaSram   = "Matsushita SRAM";
    ls->romTypePanasonic16      = "Panasonic 16kB SRAM";
    ls->romTypePanasonic32      = "Panasonic 32kB SRAM";
    ls->romTypeBunsetsu         = "Bunsetsu";
    ls->romTypeJisyo            = "Jisyo";
    ls->romTypeKanji12          = "Kanji12";
    ls->romTypeNationalSram     = "National (SRAM)";
    ls->romTypeS1985            = "S1985";
    ls->romTypeS1990            = "S1990";
    ls->romTypeTurborPause      = "Turbo-R Pause";
    ls->romTypeF4deviceNormal   = "F4 Device Normal";
    ls->romTypeF4deviceInvert   = "F4 Device Inverted";
    ls->romTypeMsxMidi          = "MSX-MIDI";
    ls->romTypeTurborTimer      = "Turbo-R Timer";
    ls->romTypeKoei             = "Koei (SRAM)";
    ls->romTypeBasic            = "Basic ROM";
    ls->romTypeHalnote          = "Halnote";
    ls->romTypeLodeRunner       = "Lode Runner";
    ls->romTypeNormal4000       = "Normal 4000h";
    ls->romTypeNormalC000       = "Normal C000h";
    ls->romTypeKonamiSynth      = "Konami Synthesizer";
    ls->romTypeKonamiKbdMast    = "Konami Keyboard Master";
    ls->romTypeKonamiWordPro    = "Konami Word Pro";
    ls->romTypePac              = "PAC (SRAM)";
    ls->romTypeMegaRam          = "MegaRAM";
    ls->romTypeMegaRam128       = "128kB MegaRAM";
    ls->romTypeMegaRam256       = "256kB MegaRAM";
    ls->romTypeMegaRam512       = "512kB MegaRAM";
    ls->romTypeMegaRam768       = "768kB MegaRAM";
    ls->romTypeMegaRam2mb       = "2MB MegaRAM";
    ls->romTypeExtRam           = "External RAM";
    ls->romTypeExtRam512        = "512kB External RAM";
    ls->romTypeExtRam1mb        = "1MB External RAM";
    ls->romTypeExtRam2mb        = "2MB External RAM";
    ls->romTypeExtRam4mb        = "4MB External RAM";
    ls->romTypeMsxMusic         = "MSX Music";
    ls->romTypeMsxAudio         = "MSX Audio";
    ls->romTypeY8950            = "Y8950";
    ls->romTypeMoonsound        = "Moonsound";
    ls->romTypeSvi328Cart       = "SVI-328 Cartridge";
    ls->romTypeSvi328Fdc        = "SVI-328 Disk Controller";
    ls->romTypeSvi328Prn        = "SVI-328 Printer";
    ls->romTypeSvi328Uart       = "SVI-328 Serial Port";
    ls->romTypeSvi328col80      = "SVI-328 80 Column Card";
    ls->romTypeSvi727col80      = "SVI-727 80 Column Card";
    ls->romTypeColecoCart       = "Coleco Cartridge";
    ls->romTypeSg1000Cart       = "SG-1000 Cartridge";
    ls->romTypeSc3000Cart       = "SC-3000 Cartridge";
    ls->romTypeTheCastle        = "The Castle";
    ls->romTypeSonyHbi55        = "Sony HBI-55";
    ls->romTypeMsxPrinter       = "MSX Printer";
    ls->romTypeTurborPcm        = "Turbo-R PCM Chip";
    ls->romTypeGameReader       = "Sunrise GameReader";
    ls->romTypeSunriseIde       = "Sunrise IDE";
    ls->romTypeBeerIde          = "Beer IDE";
    ls->romTypeGide             = "GIDE";
    ls->romTypeVmx80            = "Microsol VMX-80";
    ls->romTypeNms8280Digitiz   = "Philips NMS-8280 Digitizer";
    ls->romTypeHbiV1Digitiz     = "Sony HBI-V1 Digitizer";
    ls->romTypeFmdas            = "F&M Direct Assembler System";
    ls->romTypeSfg01            = "Yamaha SFG-01";
    ls->romTypeSfg05            = "Yamaha SFG-05";
    
    
    //----------------------
    // Debug type lines
    // Note: Only needs translation if debugger is translated
    //----------------------

    ls->dbgMemVisible           = "Visible Memory";
    ls->dbgMemRamNormal         = "Normal";
    ls->dbgMemRamMapped         = "Mapped";
    ls->dbgMemVram              = "VRAM";
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
    ls->dbgDevIdeBeer           = "Beer IDE";
    ls->dbgDevIdeGide           = "GIDE";
    ls->dbgDevF4Device          = "F4 Device";
    ls->dbgDevFmpac             = "FMPAC";
    ls->dbgDevFmpak             = "FMPAK";
    ls->dbgDevKanji             = "Kanji";
    ls->dbgDevKanji12           = "Kanji 12";
    ls->dbgDevKonamiKbd         = "Konami Keyboard Master";
    ls->dbgDevKorean80          = "Korean 80";
    ls->dbgDevKorean90          = "Korean 90";
    ls->dbgDevKorean128         = "Korean 128";
    ls->dbgDevMegaRam           = "Mega RAM";
    ls->dbgDevFdcMicrosol       = "Microsol FDC";
    ls->dbgDevMoonsound         = "Moonsound";
    ls->dbgDevMsxAudio          = "MSX Audio";
    ls->dbgDevMsxAudioMidi      = "MSX Audio MIDI";
    ls->dbgDevMsxMusic          = "MSX Music";
    ls->dbgDevPrinter           = "Printer";
    ls->dbgDevRs232             = "RS232";
    ls->dbgDevS1990             = "S1990";
    ls->dbgDevSfg05             = "Yamaha SFG-05";
    ls->dbgDevHbi55             = "Sony HBI-55";
    ls->dbgDevSviFdc            = "SVI FDC";
    ls->dbgDevSviPrn            = "SVI Printer";
    ls->dbgDevSvi80Col          = "SVI 80 Column";
    ls->dbgDevPcm               = "PCM";
    ls->dbgDevMatsushita        = "Matsushita";
    ls->dbgDevS1985             = "S1985";
    ls->dbgDevCrtc6845          = "CRTC6845";
    ls->dbgDevTms9929A          = "TMS9929A";
    ls->dbgDevTms99x8A          = "TMS99x8A";
    ls->dbgDevV9938             = "V9938";
    ls->dbgDevV9958             = "V9958";
    ls->dbgDevZ80               = "Z80";
    ls->dbgDevMsxMidi           = "MSX MIDI";
    ls->dbgDevPpi               = "PPI";
    ls->dbgDevRtc               = "RTC";
    ls->dbgDevTrPause           = "TR Pause";
    ls->dbgDevAy8910            = "AY8910 PSG";
    ls->dbgDevScc               = "SCC";


    //----------------------
    // Debug type lines
    // Note: Can only be translated to european languages
    //----------------------

    ls->aboutScrollThanksTo     = "Gracias especiales a: ";
    ls->aboutScrollAndYou       = "y USTED !!!!";
};

#endif
