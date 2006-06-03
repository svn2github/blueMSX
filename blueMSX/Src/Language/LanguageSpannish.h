/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageSpannish.h,v $
**
** $Revision: 1.15 $
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
#ifndef LANGUAGE_SPANISH_H
#define LANGUAGE_SPANISH_H

#include "LanguageStrings.h"

void langInitSpanish(LanguageStrings* ls)
{
    ls->menuNoRecentFiles       = "- No hay archivos recientes -";
    ls->menuInsert              = "Insertar";
    ls->menuEject               = "Sacar";

    ls->menuCartAutoReset       = "Reinicio Tras Insertar/Sacar";
    ls->menuCartFMPac           = "Cartucho FM-PAC";
    ls->menuCartPac             = "Cartucho PAC";

    ls->menuDiskAutoStart       = "Reinicio Tras Insertar";

    ls->menuCasSetPosition      = "Posicionar";
    ls->menuCasRewind           = "Rebovinar";

    ls->menuZoomNormal          = "Tamaño Normal";
    ls->menuZoomDouble          = "Tamaño Doble";
    ls->menuZoomFullscreen      = "Pantalla Completa";

    ls->menuPropsEmulation      = "Emulación";
    ls->menuPropsVideo          = "Vídeo";
    ls->menuPropsSound          = "Sonido";
    ls->menuPropsControls       = "Controles";
    ls->menuPropsPerformance    = "Rendimiento";
    ls->menuPropsLanguage       = "Idioma";

    ls->menuHelpHelp            = "Ayuda";
    ls->menuHelpAbout           = "Acerca De blueMSX";

    ls->menuFileCart            = "Cartucho Slot";
    ls->menuFileDisk            = "Unidad Disco";
    ls->menuFileCas             = "Cassette";
    ls->menuFileLoadState       = "Estado Carga CPU";
    ls->menuFileSaveState       = "Grabar Estado CPU";
    ls->menuFileQLoadState      = "Carga rápida Estado";
    ls->menuFileQSaveState      = "Grabación Rápida Estado";
    ls->menuFileCaptureAudio    = "Captura Audio";
    ls->menuFileScreenShot      = "Grabar Pantalla";
    ls->menuFileExit            = "Salir";

    ls->menuRunRun              = "Ejecutar";
    ls->menuRunPause            = "Pausar";
    ls->menuRunStop             = "Parada";
    ls->menuRunSoftReset        = "Reinicio Software";
    ls->menuRunHardReset        = "Reinicio Hardware";
    ls->menuRunCleanReset       = "Reinicio General";

    ls->menuFile                = "Archivo";
    ls->menuRun                 = "Ejecutar";
    ls->menuWindow              = "Ventana";
    ls->menuOptions             = "Opciones";
    ls->menuHelp                = "Ayuda";

    ls->errorTitle              = "blueMSX - Error";
    ls->errorEnterFullscreen    = "Error al intentar Modo Pantalla Completa             \n";
    ls->errorDirectXFailed      = "Error al crear objetos DirectX.           \n.\nComprueba configuración de Vídeo.";
    ls->errorNoRomInZip         = "No hay archivo .rom en el archivo zip.";
    ls->errorNoDskInZip         = "No hay archivo .dsk en el archivo zip.";
    ls->errorNoCasInZip         = "No hay archivo .cas en el archivo zip.";
    ls->errorNoHelp             = "Imposible encontrar archivo de ayuda de BlueMSX.";
    ls->errorStartEmu           = "Error al iniciar MSX emulator.";


    ls->dlgLoadRom              = "blueMSX - Seleccionar imagen Rom a cargar";
    ls->dlgLoadDsk              = "blueMSX - Seleccionar imagen Dsk a cargar";
    ls->dlgLoadCas              = "blueMSX - Seleccionar imagen Cas a cargar";
    ls->dlgLoadRomDskCas        = "blueMSX - Seleccionar un archivo Rom, Dsk, or Cas a cargar";
    ls->dlgLoadRomDesc          = "Seleccionar imagen Rom a cargar:";
    ls->dlgLoadDskDesc          = "Seleccionar imagen de disco a cargar:";
    ls->dlgLoadCasDesc          = "Seleccionar imagen de cinta a cargar:";
    ls->dlgLoadRomDskCasDesc    = "Seleccionar imagen Rom, Disco, o Cinta a cargar:";
    ls->dlgLoadState            = "Cargar Estado CPU";
    ls->dlgSaveState            = "Salvar Estado CPU";
    ls->dlgInsertRom1           = "Insertar Cartucho ROM en slot 1";
    ls->dlgInsertRom2           = "Insertar Cartucho ROM en slot 2";
    ls->dlgInsertDiskA          = "Insertar imagen de Disco en Unidad A";
    ls->dlgInsertDiskB          = "Insertar imagen de Disco en Unidad B";
    ls->dlgInsertCas            = "Insertar Cinsta de cassette";

    ls->dlgOK                   = "OK";
    ls->dlgCancel               = "Cancelar";

    ls->dlgTapeTitle            = "blueMSX - Posición de la Cinta";
    ls->dlgTapeFrameText        = "Posición de la Cinta";
    ls->dlgTapeCurrentPos       = "Posición Actual";
    ls->dlgTapeTotalTime        = "Tiempo Total";

    ls->dlgZipReset             = "Reiniciar Tras Insertar";

    ls->dlgAboutTitle           = "blueMSX - Acerca de";

    ls->dlgLangLangText         = "Seleccionar Idioma";
    ls->dlgLangLangTitle        = "blueMSX - Idioma";

    ls->propTitle               = "blueMSX - Propiedades";
    ls->propEmulation           = "Emulación";
    ls->propVideo               = "Video";
    ls->propSound               = "Sonido";
    ls->propControls            = "Controles";
    ls->propPerformance         = "Rendimiento";

    ls->propEmuGeneralGB        = "General ";
    ls->propEmuFamilyText       = "Familia MSX:";
    ls->propEmuMemoryGB         = "Memoria ";
    ls->propEmuRamSizeText      = "Tamaño RAM:";
    ls->propEmuVramSizeText     = "Tamaño VRAM:";
    ls->propEmuSpeedGB          = "Velocidad de la Emulación ";
    ls->propEmuSpeedText        = "Velocidad de la Emulación:";

    ls->propMonMonGB            = "Monitor ";
    ls->propMonTypeText         = "Tipo de Monitor:";
    ls->propMonEmuText          = "Emulación del Monitor:";
    ls->propVideoYypeText       = "Tipo de Video:";
    ls->propWindowSizeText      = "Tamaño de Ventana:";

    ls->propPerfVideoDrvGB      = "Controlador de Video ";
    ls->propPerfVideoDispDrvText= "Controlador de Pantalla:";
    ls->propPerfFrameSkipText   = "Omisión de Frames:";
    ls->propPerfAudioDrvGB      = "Controlador de Audio ";
    ls->propPerfAudioDrvText    = "Controlador de Sonido:";
    ls->propPerfAudioBufSzText  = "Tamaño del Buffer de sonido:";
    ls->propPerfEmuGB           = "Emulación ";
    ls->propPerfSyncModeText    = "Modo SYNC:";

    ls->propSndChipEmuGB        = "Emulación Chip de Sonido ";
    ls->propSndMixerGB          = "Mezclador de Audio ";
    ls->propSndMonoText         = "mono";
    ls->propSndStereoText       = "stereo";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "MASTER";

    ls->enumVideoMonColor       = "Color";
    ls->enumVideoMonGrey        = "Blanco y Negro";
    ls->enumVideoMonGreen       = "Verde";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "Ninguno";
    ls->enumVideoEmuYc          = "Cable Y/C";
    ls->enumVideoEmuYcBlur      = "Cable Y/C ruidoso";
    ls->enumVideoEmuComp        = "Compuesto";
    ls->enumVideoEmuCompBlur    = "Compuesto Ruidoso";
    ls->enumVideoEmuScale2x     = "Escala 2x";

    ls->enumVideoSize1x         = "Normal - 320x200";
    ls->enumVideoSize2x         = "Doble - 640x400";
    ls->enumVideoSizeFullscreen = "Pantalla Completa";

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

    ls->enumEmuSync1ms          = "1ms (Lo Mejor)";
    ls->enumEmuSyncAuto         = "Auto (Rápido)";

    ls->enumControlsJoyNone     = "Ninguno";
    ls->enumControlsJoyMouse    = "Ratón";

    ls->dlgAboutAbout           = "Acerca de\r\n====";
    ls->dlgAboutVersion         = "Versión:";
    ls->dlgAboutBuildNumber     = "Compilación:";
    ls->dlgAboutBuildDate       = "Fecha:";
    ls->dlgAboutCreat           = "Desarrollado por Daniel Vik";
    ls->dlgAboutLisence         = "LICENCIA\r\n"
                                  "======\r\n\r\n"
                                  "Este software se proporciona tal y como es, sin ninguna garantía."
                                  "En ningún caso el/los autores serán responsablesny de posibles daños "
                                  "producidos por el uso de este software.\r\n\r\n"
                                  "Para más detalles, visita la web www.bluemsx.com.";


    ls->dlgAboutDevel           = "PROGRAMADORES\r\n========";
    ls->dlgAboutThanks          = "MUCHAS GRACIAS A\r\n============";

    // New entries
    ls->menuTools                = "Herramientas";
    ls->menuToolsMachine         = "Editor de Máquina";
    ls->menuPropsSettings        = "Configuraciones";
    ls->menuCasRewindAfterInsert = "Rebovinar tras Insertar";
    ls->menuCasUseReadOnly       = "Usar Imagen de Cassette Sólo Lectura";
    ls->lmenuCasSaveAs           = "Salvar Imagen de Cassette Como...";

    ls->dlgSaveCassette          = "blueMSX - Salvar Imagen de Cinta";
    ls->dlgTapeCustom            = "Mostrar Archivos Personalizados";
    ls->dlgTapeSetPosText        = "Posición de la Cinta:";
    ls->dlgTabPosition           = "Posición";
    ls->dlgTabType               = "Tipo";
    ls->dlgTabFilename           = "Nombre Archivo";

    ls->propSettings             = "Configuraciones";

    ls->propSetFileHistoryGB     = "Histórico de Archivos ";
    ls->propSetFileHistorySize   = "Número de items en Histórico de Archivos:";
    ls->propSetFileHistoryClear  = "Borrar Hostórico";
    ls->propSetScreenSaver       = " Deshabilitar Salvapantallas mientras blueMSX esté en ejecución";

    ls->confTitle                = "blueMSX - Editor de Configuración de Máquina";
    ls->confSave                 = "Guardar";
    ls->confSaveAs               = "Guardar Como...";
    ls->confRun                  = "Ejecutar";
    ls->confClose                = "Cerrar";
    ls->confConfigText           = "Configuración";
    ls->confSlotLayout           = "Esquema del Slot";
    ls->confMemory               = "Memoria";
    ls->confChipEmulation        = "Emulación de Chip";

    ls->confSlotLayoutGB         = "Esquema del Slot ";
    ls->confSlotExtSlotGB        = "Slots Externos ";
    ls->confSlotCart             = "Cartucho";
    ls->confSlotPrimary          = "Primario";
    ls->confSlotExpanded         = "Expandido (cuator subslots)";

    ls->confMemAdd               = "Añadir...";
    ls->confMemEdit              = "Editar...";
    ls->confMemRemove            = "Borrar";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Dirección";
    ls->confMemType              = "Tipo";
    ls->confMemRomImage          = "Imagen Rom";
    
    ls->confSaveTitle            = "blueMSX - Guardar Configuración";
    ls->confSaveText             = "Usted desea sobreescribir la configuración de máquina?:";

    ls->confChipVideoGB          = "Video ";
    ls->confChipVideoChip        = "Chip Video:";
    ls->confChipVideoRam         = "RAM Video:";
    ls->confChipSoundGB          = "Sonido ";

    ls->confEditMemTitle         = "blueMSX - Editar Mapa";
    ls->confEditMemGB            = "Detalles Mapa ";
    ls->confEditMemType          = "Tipo:";
    ls->confEditMemFile          = "Archivo:";
    ls->confEditMemAddress       = "Dirección";
    ls->confEditMemSize          = "Tamaño";
    ls->confEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Configuración ";
    ls->confExitSaveTitle        = "blueMSX - Salir del Editor de Configuración";
    ls->confExitSaveText         = "Quieres descartar cambios de la configuración actual?";

    ls->confSaveAsMachineTitle   = "blueMSX - Guardar Configuración de Máquina como...";
    ls->confSaveAsMachineName    = "Nombre de Máquina:";

    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypes            = " Asociar algunos tipos de archivo con blueMSX";
    ls->propDisableWinKeys       = " Función MSX automática para las teclas Windows"; 
    ls->propWindowsEnvGB         = "Ambiente Windows";
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW acel.";
    ls->propMonHorizStretch      = " Estiramiento Horizontal";
    ls->propClearHistory         = "¿Desean realmente borrar hostórico ?";
    ls->propEmuFrontSwitchGB     = "Botones Panasonic "; 
    ls->propEmuFrontSwitch       = " Botón Frontal"; 
    ls->propEmuAudioSwitch       = " Botón cartucho MSX-AUDIO"; 
    ls->propMonVertStretch       = " Estiramiento Vertical";
    
    ls->confCmosGB               = "CMOS "; 
    ls->confCmosEnable           = " Activar el CMOS"; 
    ls->confCmosBattery          = " Utilizar una Batería Cargada";

    ls->menuCartSCCPlus         = "Cartucho SCC+";
    ls->menuCartSCC             = "Cartucho SCC";
    
    ls->warningTitle             = "blueMSX - Advertencia";


    // New entries in 1.5.1
    ls->menuToolsShortcuts      = "Editor de Atajos";

    ls->shortcutSaveConfig      = "blueMSX -  - Guardar Configuración";
    ls->shortcutOverwriteConfig = "Usted desea sobreescribir la configuración del atajo?:";
    ls->shortcutExitConfig      = "blueMSX - Salir del Editor de Atajos";
    ls->shortcutDiscardConfig   = "Quieres descartar cambios de la configuración actual?";
    ls->shortcutSaveConfigAs    = "blueMSX - Guardar Configuración de Atajos como...";
    ls->shortcutConfigName      = "Nombre de la configuración:";
    ls->shortcutNewProfile      = "< Nuevo Perfil >";
    ls->shortcutConfigTitle     = "blueMSX - Editor de la tarjeta de los atajos";
    ls->shortcutAssign          = "Asigne";
    ls->shortcutPressText       = "Apoyar en la(s) tecla(s) del atajo";
    ls->shortcutScheme          = "Disposición:";

    ls->shortcutCartInsert1     = "Insertar Cartucho ROM en slot 1";
    ls->shortcutCartRemove1     = "Sacar Cartucho ROM en slot 1";
    ls->shortcutCartInsert2     = "Insertar Cartucho ROM en slot 2";
    ls->shortcutCartRemove2     = "Sacar Cartucho ROM en slot 2";
    ls->shortcutCartAutoReset   = "Reiniciar Tras Insertar Cartucho ROM";
    ls->shortcutDiskInsertA     = "Insertar imagen de Disco en Unidad A";
    ls->shortcutDiskRemoveA     = "Sacar imagen de Disco en Unidad A";
    ls->shortcutDiskChangeA     = "Cambiar rápidamente de Disco en Unidad A";
    ls->shortcutDiskAutoResetA  = "Reiniciar Tras Insertar Disco en Unidad A";
    ls->shortcutDiskInsertB     = "Insertar imagen de Disco en Unidad B";
    ls->shortcutDiskRemoveB     = "Sacar imagen de Disco en Unidad B";
    ls->shortcutCasInsert       = "Insertar Cinsta de cassette";
    ls->shortcutCasEject        = "Sacar Cinsta de cassette";
    ls->shortcutCasAutorewind   = "Rebobinado Automático o no de Cassette";
    ls->shortcutCasReadOnly     = "Cassette en método sólo Lectura o no";
    ls->shortcutCasSetPosition  = "Posicionar Cassette";
    ls->shortcutCasRewind       = "Rebovinar Cassette";
    ls->shortcutCasSave         = "Salvar Imagen de Cassette";
    ls->shortcutCpuStateLoad    = "Cargar Estado CPU";
    ls->shortcutCpuStateSave    = "Grabar Estado CPU";
    ls->shortcutCpuStateQload   = "Cargar rápida Estado CPU";
    ls->shortcutCpuStateQsave   = "Grabar rápida Estado CPU";
    ls->shortcutAudioCapture    = "Iniciar/Pausar captura audio";
    ls->shortcutScreenshotOrig  = "Grabar Pantalla";
    ls->shortcutScreenshotSmall = "Pequeña captura de la pantalla sin filtro";
    ls->shortcutScreenshotLarge = "Gran captura de la pantalla sin filtro";
    ls->shortcutQuit            = "Salir blueMSX";
    ls->shortcutRunPause        = "Ejecutar/Pausar emulación";
    ls->shortcutStop            = "Parada emulación";
    ls->shortcutResetHard       = "Reinicio Hardware";
    ls->shortcutResetSoft       = "Reinicio Software";
    ls->shortcutResetClean      = "Reinicio General";
    ls->shortcutSizeSmall       = "Pasar en método ventana tamaño normal";
    ls->shortcutSizeNormal      = "Pasar en método ventana tamaño doble";
    ls->shortcutSizeFullscreen  = "Pasar en método pantalla completa";
    ls->shortcutToggleFullscren = "Balanza método ventana/método pantalla completa";
    ls->shortcutVolumeIncrease  = "Aumentar el volumen sonoro";
    ls->shortcutVolumeDecrease  = "Disminuir el volumen sonoro";
    ls->shortcutVolumeMute      = "Parada el sonido";
    ls->shortcutSwitchMsxAudio  = "Impulsar el botón cartucho MSX-AUDIO";
    ls->shortcutSwitchFront     = "Impulsar el botón frontal Panasonic";
    ls->shortcutToggleMouseLock = "Activar/desactivar el bloqueo del ratón";
    ls->shortcutEmuSpeedMax     = "Velocidad máxima de la emulación";
    ls->shortcutEmuSpeedNormal  = "Velocidad normal de la emulación";
    ls->shortcutEmuSpeedInc     = "Aumentar la velocidad de la emulación";
    ls->shortcutEmuSpeedDec     = "Disminuir la velocidad de la emulación";
    ls->shortcutShowEmuProp     = "Mostrar las propiedades de la emulación";
    ls->shortcutShowVideoProp   = "Mostraz las propiedades video";
    ls->shortcutShowAudioProp   = "Mostrar las propiedades de sonido";
    ls->shortcutShowCtrlProp    = "Mostrar las propiedades de los controles";
    ls->shortcutShowPerfProp    = "Mostrar las propiedades de redimiento";
    ls->shortcutShowSettProp    = "Mostrar las propiedades de los ajustes";
    ls->shortcutShowLanguage    = "Mostrar diálogo de la idioma";
    ls->shortcutShowMachines    = "Mostrar editor de la máquina";
    ls->shortcutShowShortcuts   = "Mostrar editor de atajos";
    ls->shortcutShowHelp        = "Ver la ayuda";
    ls->shortcutShowAbout       = "Ver la rúbrica acerca de blueMSX";

    ls->shortcutSpecialMenu1    = "Mostrar el menú especial para cartucho 1 ROM en slot 1";
    ls->shortcutSpecialMenu2    = "Mostrar el menú especial para cartucho 1 ROM en slot 2";
    ls->shortcutVolumeStereo    = "Balanza mono/stereo";
    ls->shortcutThemeSwitch     = "Cambiar de tema";
    ls->shortcutToggleSpriteEnable = "Mostrar/ocultar los sprites";
    
    ls->shortcutShowApearProp   = "Show Appearance Properties";
    ls->menuPropsApearance      = "Appearance";
    ls->propApearance           = "Appearance";
    ls->propThemeGB             = "Tema ";
    ls->propTheme               = "Tema";

    ls->propMonBrightness       = "Brillo:";
    ls->propMonContrast         = "Contraste:";
    ls->propMonSaturation       = "Saturación:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanlines:";

    ls->dlgRomType              = "Tipo rom:"; 
    ls->propOpenRomGB           = "Abrir archivo rom"; 
    ls->propDefaultRomType      = "Tipo por defecto:"; 
    ls->propGuessRomType        = "Conjeturar tipo"; 

    ls->propFile                = "Archivo"; 
    ls->propSettDefSlotGB       = "Deslizar e depositar "; 
    ls->propSettDefSlots        = "Insertar cartucho en:"; 
    ls->propSettDefSlot         = " Slot"; 
    ls->propSettDefDrives       = "Insertar disco en:"; 
    ls->propSettDefDrive        = " Unidad"; 
    ls->menuPropsFile           = "Archivo";
    ls->shortcutShowFiles       = "Mostrar las propiedades de los archivos";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "Insertar directorio"; 
    ls->shortcutDiskDirInsertA  = "Insertar un directorio como disco A"; 
    ls->shortcutDiskDirInsertB  = "Insertar un directorio como disco B";
    ls->propMonDeInterlace      = " De-entrelace";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "Impulsar el botón Pause"; 
    ls->shortcutSizeMinimized   = "Reducir la ventana"; 
    ls->shortcutEmuSpeedToggle  = "Balanza velocitad máxima de la emulación"; 
    ls->shortcutToggleCpuTrace  = "Activar/Desactivar Rastro de la CPU"; 

    ls->enumVideoEmuMonitor     = "Monitor"; 

    ls->propEmuPauseSwitch      = " Botón Pause"; 
    ls->propVideoFreqText       = "Frecuencia video:"; 
    ls->propVideoFreqAuto       = "Auto"; 
    ls->propSndOversampleText   = "Oversample:"; 

    ls->confChipExtras          = "Extras"; 
    ls->confBoardGB             = "Sistema "; 
    ls->confBoardText           = "Sistema tipo:"; 
    ls->confCpuFreqGB            = "Frecuencia CPU "; 
    ls->confZ80FreqText          = "Frecuencia Z80:"; 
    ls->confR800FreqText         = "Frecuencia R800:"; 
    ls->confFdcGB                = "Regulador De Diskette "; 
    ls->confCFdcNumDrivesText    = "Número de unidades:"; 

    ls->propPriorityBoost       = " Dar a blueMSX una elevada prioridad";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "No sincronizar unidade disco"; 
    ls->shortcutToggleFdcTiming = "Sincronizar o no unidade disco"; 

    // New entries in 2.2
    ls->menuCartHBI55           = "Cartucho Sony HBI-55"; 
    ls->propSndPcm              = " Turbo-R PCM"; 
    ls->propSndAY8910           = " AY8910 PSG"; 
    ls->propSndSN76489          = " SN76489 PSG"; 
    ls->enumVideoEmuHq2x        = "Hq2x"; 
    ls->propMonColorGhosting    = "Modulador RF"; 

    ls->keyconfigSelectedKey    = "Tecla MSX seleccionada:"; 
    ls->keyconfigMappedTo       = "Asignada a la tecla PC :"; 
    ls->keyconfigMappingScheme  = "Configuración del teclado:"; 

    ls->warningDiscardChanges   = "Quieres descartar cambios de la configuración actual?"; 

    ls->confSaveAsTitle         = "Guardar Como..."; 
    ls->confSaveAsName          = "Nombre:"; 

    ls->menuToolsKeyboard       = "Editor de teclado"; 
    ls->shortcutShowKeyboard    = "Mostrar editor de teclado"; 

    ls->menuVideoSource         = "Fuente Vídeo"; 
    ls->menuVideoSourceDefault  = "Ninguna fuente vídeo"; 
    ls->menuVideoChipAutodetect = "Detección automática"; 
    ls->propFullscreenResText   = "Resolución pantalla completa:"; 
    ls->dlgSavePreview          = "Imaginar"; 
    ls->dlgSaveDate             = "Fecha:"; 

    ls->enumVideoMonAmber       = "Ambar"; 

    ls->menuPropsPorts          = "Puertos"; 
    ls->propPortsLptGB          = "Puerto paralelo "; 
    ls->propPortsComGB          = "Puertos seriales "; 
    ls->propPortsLptText        = "Puerto:"; 
    ls->propPortsCom1Text       = "Puerto 1:"; 

    ls->shortcutShowDebugger    = "Mostrar Debugger"; 
    ls->shortcutShowTrainer     = "Mostrar Trainer"; 
    ls->shortcutShowPorts       = "Mostrar las propriedades de los puertos";
    
    ls->propPorts               = "Puertos";
    ls->propPortsNone           = "Ninguno";

    // New entries in 2.3 
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle"; 

    ls->propPortsSimplCovox     = "SiMPL / Covox DAC"; 
    ls->propPortsFile           = "Imprimir en archivo"; 
    ls->propPortsOpenLogFile    = "Abrir un archivo de datos"; 
    ls->propPortsEmulateMsxPrn  = "Emulación:"; 

    ls->shortcutPrnFormFeed     = "Paso a la página siguiente"; 

    ls->menuPrnFormfeed         = "Página siguiente"; 
    ls->menuFilePrn             = "Impresora"; 
    ls->propPortsComFile        = "Enviar hacia archivo";

    // New entries in 2.4 
    ls->shortcutShowMixer       = "Mostrar Mezclador de Audio"; 
    ls->menuToolsMixer          = "Mezclador de Audio"; 
    
    ls->propSndMidiInGB         = "MIDI In "; 
    ls->propSndMidiOutGB        = "MIDI Out "; 
    ls->propSndMt32ToGmText     = " Mapa instrumentos MT-32 a General MIDI"; 

    ls->textDevice              = "Tipo:"; 
    ls->textFilename            = "Nombre:"; 
    ls->textFile                = "Archivo"; 
    ls->textNone                = "Ninguno"; 

    ls->enumEmuSyncNone         = "Ninguno"; 
    ls->enumEmuSyncAuto         = "Auto (rápido)"; 
    ls->enumEmuSync1ms          = "Sinc sobre MSX refresh"; 
    ls->enumEmuSyncVblank       = "Sinc sobre PC Vertical Blank"; 

    ls->propMonEffectsGB        = "Efectos  "; 
    
    ls->confSlot                = "Slot"; 
    ls->confSubslot             = "Subslot"; 

    ls->shortcutDescription     = "Atajo"; 
    ls->shortcutKey             = "Tecla rápida"; 
    ls->fileRom                 = "ROM image"; 
    ls->confOpenRom             = "Abrirse ROM image"; 
    ls->fileAll                 = "Todos los archivos"; 
    ls->fileCpuState            = "Carga CPU"; 
    ls->fileDisk                = "Disk Image"; 
    ls->fileCas                 = "Tape Image"; 

    ls->menuCartExternalRam     = "RAM externo"; 
};

#endif
