/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageSpannish.h,v $
**
** $Revision: 1.6 $
**
** $Date: 2005-01-03 23:12:41 $
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
    ls->statusBarStopped        = "  Parado";
    ls->statusBarPaused         = "  En Pausa";
    ls->statusBarRunning        = "  En Ejecución";

    ls->menuHardReset           = "Reinicio Hardware";
    ls->menuSoftReset           = "Reinicio Software";

    ls->menuCartInsert          = "Insertar";
    ls->menuCartRemove          = "Sacar";
    ls->menuCartAutoReset       = "Reinicio Tras Insertar/Sacar";
    ls->menuCartNoRecentFiles   = "- No hay archivos recientes -";
    ls->menuCartFMPac           = "Cartucho FM-PAC";
    ls->menuCartPac             = "Cartucho PAC";
    ls->menuCartSpecial         = "Especial";

    ls->menuDiskInsert          = "Insertar";
    ls->menuDiskEject           = "Sacar";
    ls->menuDiskAutoStart       = "Reinicio Tras Insertar";
    ls->menuDiskNoRecentFiles   = "- No hay archivos recientes -";

    ls->menuCasInsert           = "Insertar";
    ls->menuCasEject            = "Sacar";
    ls->menuCasSetPosition      = "Posicionar";
    ls->menuCasRewind           = "Rebovinar";
    ls->menuCasNoRecentFiles    = "- No hay archivos recientes -";

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

    ls->menuFileCart1           = "Cartucho Slot 1";
    ls->menuFileCart2           = "Cartucho Slot 2";
    ls->menuFileDiskA           = "Unidad Disco A";
    ls->menuFileDiskB           = "Unidad Disco B";
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

    ls->tooltipReset            = "Reinicio MSX";
    ls->tooltipCart1            = "Inserta Cartucho en Slot 1";
    ls->tooltipCart2            = "Inserta Cartucho en Slot 2";
    ls->tooltipDiskA            = "Inserta Disco en Unidad A";
    ls->tooltipDiskB            = "Inserta Disco en Unidad B";
    ls->tooltipCas              = "Inserta Cinta en Reproductor";
    ls->tooltipStart            = "Iniciar Emulación";
    ls->tooltipResume           = "Seguir Emulación";
    ls->tooltipPause            = "Pausar Emulación";
    ls->tooltipWindowSize       = "Configurar Tamaño Ventana";
    ls->tooltipProperties       = "Abrir Propiedades Dialogo";
    ls->tooltipHelp             = "Abrir Ventana Ayuda";

    ls->dlgMainWindow           = "  blueMSX";
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

    ls->dlgJoyTitle1            = "blueMSX - Controles Joystick A";
    ls->dlgJoyTitle2            = "blueMSX - Controles Joystick B";
    ls->dlgJoyUpText            = "Arriba";
    ls->dlgJoyDownText          = "Abajo";
    ls->dlgJoyLeftText          = "Izquierda";
    ls->dlgJoyRightText         = "Derecha";
    ls->dlgJoyButton1Text       = "Botón 1";
    ls->dlgJoyButton2Text       = "Botón 2";
    ls->dlgJoyGB                = "Configuración de Controles";

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

    ls->propJoyPort1GB          = "Puerto #1 ";
    ls->propJoyPort2GB          = "Puerto #2 ";
    ls->propJoyAutofireText     = "Auto-Disparo:";
    ls->propJoyKeysetGB         = "Controles Joystick ";
    ls->propJoyKeyest1          = "Configurar controles A";
    ls->propJoyKeyest2          = "Configurar controles B";

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
    ls->enumControlsJoyNumpad   = "Pad Numérico";
    ls->enumControlsJoyKeysetA  = "Controles A";
    ls->enumControlsJoyKeysetB  = "Controles B";
    ls->enumControlsJoyPCjoy1   = "Joystick PC #1";
    ls->enumControlsJoyPCjoy2   = "Joystick PC #2";
    ls->enumControlsJoyMouse    = "Ratón";

    ls->enumControlsAfOff       = "Desactivado";
    ls->enumControlsAfSlow      = "Lento";
    ls->enumControlsAfMedium    = "Medio";
    ls->enumControlsAfFast      = "Rápido";

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
    ls->propSetScreenSaverGB     = "Salvapantallas ";
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
    ls->confSlotSlot0            = "Slot 0";
    ls->confSlotSlot1            = "Slot 1";
    ls->confSlotSlot2            = "Slot 2";
    ls->confSlotSlot3            = "Slot 3";
    ls->confSlotCart1            = "Cartucho 1:";
    ls->confSlotCart2            = "Cartucho 2:";
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

    ls->slotEditMemTitle         = "blueMSX - Editar Mapa";
    ls->slotEditMemGB            = "Detalles Mapa ";
    ls->slotEditMemType          = "Tipo:";
    ls->slotEditMemFile          = "Archivo:";
    ls->slotEditMemAddress       = "Dirección";
    ls->slotEditMemSize          = "Tamaño";
    ls->slotEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Configuración ";
    ls->confExitSaveTitle        = "blueMSX - Salir del Editor de Configuración";
    ls->confExitSaveText         = "Quieres descartar cambios de la configuración actual?";

    ls->confSaveAsTitle          = "blueMSX - Guardar Configuración de Máquina como...";
    ls->confSaveAsMachineName    = "Nombre de Máquina:";

    ls->confEditMemInternalRoms  = "blueMSX - Roms internos";


    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypesGB          = "Tipos de archivo ";
    ls->propFileTypes            = " Asociar algunos tipos de archivo con blueMSX";
    ls->propDisableWinKeys       = " Función MSX automática para las teclas Windows"; 
    ls->propWindowsEnvGB         = "Ambiente Windows";
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW acel.";
    ls->enumVideoDrvDirectDrawHWSys = "DirectDraw mix."; 
    ls->propMonHorizStretch      = " Estiramiento Horizontal";
    ls->propClearHistory         = "¿Desean realmente borrar hostórico ?";
    ls->propEmuFrontSwitchGB     = "Botones Panasonic "; 
    ls->propEmuFrontSwitch       = " Botón Frontal"; 
    ls->propEmuAudioSwitch       = " Botón cartucho MSX-AUDIO"; 
    ls->propMonVertStretch       = " Estiramiento Vertical";
    
    ls->dlgCmosGB                = "CMOS "; 
    ls->dlgCmosEnable            = " Activar el CMOS"; 
    ls->dlgCmosBattery           = " Utilizar una Batería Cargada";

    ls->menuCartSnatcher        = "Cartucho The Snatcher";
    ls->menuCartSdSnatcher      = "Cartucho SD-Snatcher";
    ls->menuCartSCCMirrored     = "Cartucho SCC Mirrored";
    ls->menuCartSCCExpanded     = "Cartucho SCC Expanded";
    ls->menuCartSCCPlus         = "Cartucho SCC+";
    ls->menuCartSCC             = "Cartucho SCC";
    
    ls->warningTitle             = "blueMSX - Advertencia";
    ls->tooltipStop              = "Parada Emulación";


    // New entries in 1.5.1
    ls->enumControlsJoyKeyset   = "Keyset";    
    ls->propJoyConfigKeyset     = "Config Keyset";
    ls->propJoyControlText      = "Control:";
    ls->propJoyButtonText       = "Botón";
    ls->propJoyButtonAText      = "Botón A:";
    ls->propJoyButtonBText      = "Botón B:";

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
    ls->propThemeClassic        = "Clásico";
    ls->propThemeBlue           = "DIGIblue";

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
    ls->propSettDefSlot1        = " Slot 1"; 
    ls->propSettDefSlot2        = " Slot 2"; 
    ls->propSettDefDrives       = "Insertar disco en:"; 
    ls->propSettDefDriveA       = " Unidad A"; 
    ls->propSettDefDriveB       = " Unidad B"; 
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
    ls->dlgCpuFreqGB            = "Frecuencia CPU "; 
    ls->dlgZ80FreqText          = "Frecuencia Z80:"; 
    ls->dlgR800FreqText         = "Frecuencia R800:"; 
    ls->dlgFdcGB                = "Regulador De Diskette "; 
    ls->dlgCFdcNumDrivesText    = "Número de unidades:"; 

    ls->propPriorityBoost       = " Dar a blueMSX una elevada prioridad";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "No sincronizar unidade disco"; 
    ls->shortcutToggleFdcTiming = "Sincronizar o no unidade disco"; 
    ls->propUseRegistry         = "Grabar la configuración en el Registro";

    // New entries in 2.2
    ls->menuCartHBI55           = "Cartucho Sony HBI-55";
    ls->propSndPcm              = " Turbo-R PCM";
    ls->propSndAY8910           = " AY8910 PSG";
    ls->propSndSN76489          = " SN76489 PSG";
    ls->enumVideoEmuHq2x        = "Hq2x";
};

#endif
