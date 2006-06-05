/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguagePortuguese.h,v $
**
** $Revision: 1.23 $
**
** $Date: 2006-06-05 03:41:12 $
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
#ifndef LANGUAGE_PORTUGUESE_H
#define LANGUAGE_PORTUGUESE_H

#include "LanguageStrings.h"

void langInitPortuguese(LanguageStrings* ls) 
{
    //----------------------
    // Generic lines
    //----------------------

    ls->textDevice              = "Tipo:"; 
    ls->textFilename            = "Nome:"; 
    ls->textFile                = "Arquivo"; 
    ls->textNone                = "Nenhum"; 
    ls->textUnknown             = "Unknown";                            // New in 2.5


    //----------------------
    // Warning and Error lines
    //----------------------

    ls->warningTitle             = "blueMSX - Advert�ncia";
    ls->warningDiscardChanges   = "Voc� quer desfazer as altera��es da configura��o atual?"; 
    ls->warningOverwriteFile    = "Do you want to overwrite the file:"; // New in 2.5
    ls->errorTitle              = "blueMSX - Erro";
    ls->errorEnterFullscreen    = "Falha ao entrar em Tela Cheia.             \n";
    ls->errorDirectXFailed      = "Falha ao Criar Objetos DirectX.             \nUsando GDI ao inv�s.\nCheque as propriedades Video.";
    ls->errorNoRomInZip         = "Nao foi localizado arquivo .ROM dentro do arquivo zip.";
    ls->errorNoDskInZip         = "Nao foi localizado arquivo .DSK dentro do arquivo zip.";
    ls->errorNoCasInZip         = "Nao foi localizado arquivo .CAS dentro do arquivo zip.";
    ls->errorNoHelp             = "Nao foi localizado arquivo ajuda do blueMSX";
    ls->errorStartEmu           = "Falha ao Iniciar o emulador MSX.";
    ls->errorPortableReadonly   = "Portable device is readonly";        // New in 2.5


    //----------------------
    // File related lines
    //----------------------

    ls->fileRom                 = "ROM image"; 
    ls->fileAll                 = "Todos os arquivos"; 
    ls->fileCpuState            = "Status da CPU"; 
    ls->fileDisk                = "Disk Image"; 
    ls->fileCas                 = "Tape Image"; 


    //----------------------
    // Menu related lines
    //----------------------

    ls->menuNoRecentFiles       = "- Sem Arquivos Recentes -";
    ls->menuInsert              = "Inserir";
    ls->menuEject               = "Ejetar";

    ls->menuCartGameReader      = "Game Reader";                        // New in 2.5
    ls->menuCartIde             = "IDE";                                // New in 2.5
    ls->menuCartBeerIde         = "Beer";                               // New in 2.5
    ls->menuCartGIde            = "GIDE";                               // New in 2.5
    ls->menuCartSunriseIde      = "Sunrise";                            // New in 2.5
    ls->menuCartSCC             = "Cartucho SCC";
    ls->menuCartSCCPlus         = "Cartucho SCC+";
    ls->menuCartFMPac           = "Cartucho FM-PAC";
    ls->menuCartPac             = "Cartucho PAC";
    ls->menuCartHBI55           = "Cartucho Sony HBI-55"; 
    ls->menuCartInsertSpecial   = "Insert Special";                     // New in 2.5
    ls->menuCartMegaRam         = "MegaRAM";                            // New in 2.5
    ls->menuCartExternalRam     = "RAM esterno";

    ls->menuDiskInsertNew       = "Insert New Disk Image";              // New in 2.5
    ls->menuDiskDirInsert       = "Inserir diret�rio"; 
    ls->menuDiskAutoStart       = "Reset ap�s inserir";
    ls->menuCartAutoReset       = "Reset ap�s inserir/remover";
    
    ls->menuCasRewindAfterInsert = "Rebobinar Apos Inserir";
    ls->menuCasUseReadOnly       = "Usar Cassete Como Somente Leitura";
    ls->lmenuCasSaveAs           = "Salvar Imagem do Cassete Como...";
    ls->menuCasSetPosition      = "Ajustar Posi��o";
    ls->menuCasRewind           = "Rebobinar";

    ls->menuPrnFormfeed         = "P�gina seguinte"; 

    ls->menuZoomNormal          = "Tamanho Normal";
    ls->menuZoomDouble          = "Tamanho Duplo";
    ls->menuZoomFullscreen      = "Tela Cheia";
    
    ls->menuPropsEmulation      = "Emula��o";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Som";
    ls->menuPropsControls       = "Controles";
    ls->menuPropsPerformance    = "Performance";
    ls->menuPropsSettings       = "Ajustes";
    ls->menuPropsFile           = "Arquivo"; 
    ls->menuPropsLanguage       = "Linguagem";
    ls->menuPropsPorts          = "Portas"; 
    
    ls->menuVideoSource         = "Video Out Source";                   // New in 2.5
    ls->menuVideoSourceDefault  = "No Video Out Source Connected";      // New in 2.5
    ls->menuVideoInSource       = "Video In Source";                    // New in 2.5
    ls->menuVideoInBitmap       = "Bitmap File";                        // New in 2.5
    ls->menuVideoChipAutodetect = "Detec��o autom�tica"; 

    ls->menuHelpHelp            = "T�picos Ajuda";
    ls->menuHelpAbout           = "Sobre blueMSX";

    ls->menuFileCart            = "Cartucho Slot";
    ls->menuFileDisk            = "Disco drive";
    ls->menuFileCas             = "Cassette";
    ls->menuFilePrn             = "Impressora"; 
    ls->menuFileLoadState       = "Carregar Status da CPU";
    ls->menuFileSaveState       = "Salvar Status da CPU";
    ls->menuFileQLoadState      = "Carregar r�pido Status";
    ls->menuFileQSaveState      = "Salvar r�pido Status";
    ls->menuFileCaptureAudio    = "Capturar �udio";
    ls->menuFileScreenShot      = "Salvar Tela";
    ls->menuFileExit            = "Sair";

    ls->menuFileHarddisk        = "Hard Disk";                          // New in 2.5
    ls->menuFileHarddiskNoPesent= "No Controllers Present";             // New in 2.5

    ls->menuRunRun              = "Executar";
    ls->menuRunPause            = "Pausa";
    ls->menuRunStop             = "Parar";
    ls->menuRunSoftReset        = "Reset Completo";
    ls->menuRunHardReset        = "Reset Leve";
    ls->menuRunCleanReset       = "Reset Geral";

    ls->menuToolsMachine         = "Configura��o da M�quina";
    ls->menuToolsShortcuts      = "Configura��o de Atalhos";
    ls->menuToolsKeyboard       = "Configura��o do Teclado"; 
    ls->menuToolsMixer          = "Mixer de Audio"; 

    ls->menuFile                = "Arquivo";
    ls->menuRun                 = "Execu��o";
    ls->menuWindow              = "Janela";
    ls->menuOptions             = "Op��es";
    ls->menuTools                = "Ferramentas";
    ls->menuHelp                = "Ajuda";


    //----------------------
    // Dialog related lines
    //----------------------

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Abrir";
    ls->dlgCancel               = "Cancelar";
    ls->dlgSave                 = "Salvar";
    ls->dlgSaveAs               = "Salvar Como";
    ls->dlgRun                  = "Executar";
    ls->dlgClose                = "Fechar";

    ls->dlgLoadRom              = "blueMSX - Selecione uma ROM para carregar";
    ls->dlgLoadDsk              = "blueMSX - Selecione uma DSK para carregar";
    ls->dlgLoadCas              = "blueMSX - Selecione uma CAS para carregar";
    ls->dlgLoadRomDskCas        = "blueMSX - Selecione uma ROM, DSK, ou CAS para carregar";
    ls->dlgLoadRomDesc          = "Escolha uma ROM para carregar:";
    ls->dlgLoadDskDesc          = "Escolha um disco para carregar:";
    ls->dlgLoadCasDesc          = "Escolha um tape para carregar:";
    ls->dlgLoadRomDskCasDesc    = "Escolha uma ROM, disco, ou tape para carregar:";
    ls->dlgLoadState            = "Carregar Status da CPU";
    ls->dlgSaveState            = "Salvar Status da CPU";
    ls->dlgSaveCassette          = "blueMSX - Salvar Imagem Tape";
    ls->dlgInsertRom1           = "Insira cartucho ROM no slot 1";
    ls->dlgInsertRom2           = "Insira cartucho ROM no slot 2";
    ls->dlgInsertDiskA          = "Insira disco no drive A";
    ls->dlgInsertDiskB          = "Insira disco no drive B";
    ls->dlgInsertCas            = "Insira cassette tape";
    ls->dlgInsertHarddisk       = "Insert Hard Disk";                   // New in 2.5
    ls->dlgRomType              = "Tipo rom:"; 

    ls->dlgTapeTitle            = "blueMSX - Posi��o do Tape";
    ls->dlgTapeFrameText        = "Posi��o do Tape";
    ls->dlgTapeCurrentPos       = "Posi��o Atual";
    ls->dlgTapeTotalTime        = "Tempo Total";
    ls->dlgTapeCustom            = "Mostrar Arquivos Personalizados";
    ls->dlgTapeSetPosText        = "Posi��o do Cassete:";
    ls->dlgTabPosition           = "Posi��o";
    ls->dlgTabType               = "Tipo";
    ls->dlgTabFilename           = "Nome do Arquivo";
    ls->dlgZipReset             = "Reset ap�s inserir";

    ls->dlgAboutTitle           = "blueMSX - Sobre";

    ls->dlgLangLangText         = "Escolha uma linguagem que blueMSX ir� usar";
    ls->dlgLangLangTitle        = "blueMSX - Linguagem";

    ls->dlgAboutAbout           = "Sobre\r\n====";
    ls->dlgAboutVersion         = "Vers�o:";
    ls->dlgAboutBuildNumber     = "Compila��o:";
    ls->dlgAboutBuildDate       = "Data:";
    ls->dlgAboutCreat           = "Criado Por Daniel Vik";
    ls->dlgAboutDevel           = "DESENVOLVEDORES\r\n========";
    ls->dlgAboutThanks          = "MUITO OBRIGADO PARA\r\n============";
    ls->dlgAboutLisence         = "LICEN�A\r\n"
                                  "======\r\n\r\n"
                                  "Este software � provido 'como-est�', sem Garantia expressa ou implicada."
                                  "Em Nenhuma circunstancia os autores ser�o responsaveis por qualquer "
                                  "Problema ou DANO proveniente do uso deste software.\r\n\r\n"
                                  "Visite www.bluemsx.com para mais detalhes.";

    ls->dlgSavePreview          = "Visualizar"; 
    ls->dlgSaveDate             = "Data:"; 


    //----------------------
    // Properties related lines
    //----------------------

    ls->propTitle               = "blueMSX - Propriedades";
    ls->propEmulation           = "Emula��o";
    ls->propVideo               = "Video";
    ls->propSound               = "Som";
    ls->propControls            = "Controles";
    ls->propPerformance         = "Performance";
    ls->propSettings             = "Ajustes";
    ls->propFile                = "Arquivo"; 
    ls->propPorts               = "Portas";
    
    ls->propEmuGeneralGB        = "Geral ";
    ls->propEmuFamilyText       = "MSX :";
    ls->propEmuMemoryGB         = "Mem�ria ";
    ls->propEmuRamSizeText      = "Tamanho RAM :";
    ls->propEmuVramSizeText     = "Tamanho VRAM :";
    ls->propEmuSpeedGB          = "Velocidade da Emula��o ";
    ls->propEmuSpeedText        = "Velocidade da Emula��o:";
    ls->propEmuFrontSwitchGB    = "Bot�o Panasonic "; 
    ls->propEmuFrontSwitch      = " Bot�o Frontal"; 
    ls->propEmuFdcTiming        = " N�o sincronizar disco do drive"; 
    ls->propEmuPauseSwitch      = " Bot�o Pause "; 
    ls->propEmuAudioSwitch      = " Bot�o Cartucho MSX-AUDIO"; 
    ls->propVideoFreqText       = "Freq��ncia video:"; 
    ls->propVideoFreqAuto       = "Auto"; 
    ls->propSndOversampleText   = "Oversample:"; 
    ls->propSndMidiInGB         = "MIDI In "; 
    ls->propSndMidiOutGB        = "MIDI Out "; 

    ls->propMonMonGB            = "Monitor:";
    ls->propMonTypeText         = "Tipo de Monitor:";
    ls->propMonEmuText          = "Emulac�o de Monitor:";
    ls->propVideoTypeText       = "Tipo de Video:";
    ls->propWindowSizeText      = "Tamanho Janela:";
    ls->propMonHorizStretch     = " Estiramento Horizontal"; 
    ls->propMonVertStretch      = " Estiramento Vertical"; 
    ls->propMonDeInterlace      = " De-entrela�ar";
    ls->propMonBrightness       = "Brilho:";
    ls->propMonContrast         = "Contraste:";
    ls->propMonSaturation       = "Satura��o:";
    ls->propMonGamma            = "Gama:";
    ls->propMonScanlines        = " Scanlines:";
    ls->propMonColorGhosting    = " Modulador RF"; 
    ls->propMonEffectsGB        = "Efeitos "; 

    ls->propPerfVideoDrvGB      = "Driver de Video:";
    ls->propPerfVideoDispDrvText= "Driver do Display:";
    ls->propPerfFrameSkipText   = "Frame skipping:";
    ls->propPerfAudioDrvGB      = "Driver de Audio:";
    ls->propPerfAudioDrvText    = "Driver de Som:";
    ls->propPerfAudioBufSzText  = "Tamanho buffer Som:";
    ls->propPerfEmuGB           = "Emula��o:";
    ls->propPerfSyncModeText    = "Modo Sincronismo:";
    ls->propFullscreenResText   = "Resolu��o tela cheia:"; 

    ls->propSndChipEmuGB        = "Emula��o do Chip de Som";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";
    ls->propSndMoonsound         = " Moonsound";
    ls->propSndMt32ToGm         = " Mapa instrumentos MT-32 a General MIDI"; 

    ls->propPortsLptGB          = "Porta paralela "; 
    ls->propPortsComGB          = "Portas seriais "; 
    ls->propPortsLptText        = "Porta:"; 
    ls->propPortsCom1Text       = "Porta 1:"; 
    ls->propPortsNone           = "Nenhum";
    ls->propPortsSimplCovox     = "SiMPL / Covox DAC"; 
    ls->propPortsFile           = "Imprimir em arquivo"; 
    ls->propPortsComFile        = "Enviar para arquivo";
    ls->propPortsOpenLogFile    = "Abrir um arquivo de dados"; 
    ls->propPortsEmulateMsxPrn  = "Emula��o:"; 

    ls->propSetFileHistoryGB    = "Hist�rico ";
    ls->propSetFileHistorySize  = "Numero de itens no Hist�rico:";
    ls->propSetFileHistoryClear = "Limpar Hist�rico";
    ls->propFileTypes           = " Associar certos tipos de arquivo com blueMSX";
    ls->propWindowsEnvGB        = "Ambiente Windows";
    ls->propSetScreenSaver      = " Desabilitar Prote��o de Tela Quando blueMSX estiver ativo";
    ls->propDisableWinKeys      = " Fun��o MSX autom�tica para as teclas Windows"; 
    ls->propPriorityBoost       = " Dar ao blueMSX uma prioridade elevada";
    ls->propScreenshotPng       = " Use Portable Network Graphics (.png) screenshots";  // New in 2.5
    ls->propClearHistory        = "Deseja realmente limpar hist�rico ?";
    ls->propOpenRomGB           = "Abrir arquivo rom"; 
    ls->propDefaultRomType      = "Tipo de ROM Padr�o:"; 
    ls->propGuessRomType        = "Adivinhar tipo"; 

    ls->propSettDefSlotGB       = "Deslizar e depositar "; 
    ls->propSettDefSlots        = "Inserir cartucho no:"; 
    ls->propSettDefSlot         = " Slot"; 
    ls->propSettDefDrives       = "Inserir disco no:"; 
    ls->propSettDefDrive        = " Drive"; 

    ls->propThemeGB             = "Tema ";
    ls->propTheme               = "Tema";


    //----------------------
    // Dropdown related lines
    //----------------------

    ls->enumVideoMonColor       = "Cor";
    ls->enumVideoMonGrey        = "Branco e Preto";
    ls->enumVideoMonGreen       = "Verde";
    ls->enumVideoMonAmber       = "�mbar"; 

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC e PAL-M";

    ls->enumVideoEmuNone        = "Nenhum";
    ls->enumVideoEmuYc          = "Y/C cable (sharp)";
    ls->enumVideoEmuMonitor     = "Monitor"; 
    ls->enumVideoEmuYcBlur      = "Noisy Y/C cable (sharp)";
    ls->enumVideoEmuComp        = "Composite (blurry)";
    ls->enumVideoEmuCompBlur    = "Noisy Composite (blurry)";
    ls->enumVideoEmuScale2x     = "Escala 2x";
    ls->enumVideoEmuHq2x        = "Hq2x"; 

    ls->enumVideoSize1x         = "Normal - 320x200";
    ls->enumVideoSize2x         = "Duplo  - 640x400";
    ls->enumVideoSizeFullscreen = "Tela Cheia";

    ls->enumVideoDrvDirectDrawHW= "DirectDraw HW acel.";
    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "Nenhum";
    ls->enumVideoFrameskip1     = "1 frame";
    ls->enumVideoFrameskip2     = "2 frames";
    ls->enumVideoFrameskip3     = "3 frames";
    ls->enumVideoFrameskip4     = "4 frames";
    ls->enumVideoFrameskip5     = "5 frames";

    ls->enumSoundDrvNone        = "Sem Som";
    ls->enumSoundDrvWMM         = "Driver WMM";
    ls->enumSoundDrvDirectX     = "Driver DirectX";

    ls->enumEmuSync1ms          = "Sinc sobre MSX refresh"; 
    ls->enumEmuSyncAuto         = "Auto (rapido)"; 
    ls->enumEmuSyncNone         = "Nenhum"; 
    ls->enumEmuSyncVblank       = "Sinc sobre PC Vertical Blank"; 

    ls->enumControlsJoyNone     = "Nenhum";
    ls->enumControlsJoyMouse    = "Mouse";
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle"; 
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey Dongle";             // New in 2.5


    //----------------------
    // Configuration related lines
    //----------------------

    ls->confTitle               = "blueMSX - Editor de Configura��o da Maquina";
    ls->confConfigText          = "Configura��o";
    ls->confSlotLayout          = "Slot Layout";
    ls->confMemory              = "Mem�ria";
    ls->confChipEmulation       = "Emula��o do Chip";
    ls->confChipExtras          = "Extras"; 

    ls->confOpenRom             = "Abrir ROM image"; 
    ls->confSaveTitle           = "blueMSX - Salvar Configura��o";
    ls->confSaveText            = "Voc� quer substituir esta configura��o da m�quina? :";
    ls->confSaveAsTitle         = "Salvar Como"; 
    ls->confSaveAsMachineName   = "Nome da Maquina:";
    ls->confDiscardTitle        = "blueMSX - Configura��o";
    ls->confExitSaveTitle       = "blueMSX - Sair do Editor de Configura��o";
    ls->confExitSaveText        = "Voce quer desfazer as altera��es da Configura��o atual ?";

    ls->confSlotLayoutGB        = "Layout do Slot ";
    ls->confSlotExtSlotGB       = "Slots Externos";
    ls->confBoardGB             = "Sistema "; 
    ls->confBoardText           = "Sistema tipo:"; 
    ls->confSlotPrimary         = "Prim�rio";
    ls->confSlotExpanded        = "Expandido (Quatro sub-slots)";

    ls->confSlotCart            = "Cartucho";
    ls->confSlot                = "Slot"; 
    ls->confSubslot             = "Sub-slot"; 

    ls->confMemAdd               = "Adicionar...";
    ls->confMemEdit              = "Editar...";
    ls->confMemRemove            = "Remover";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Endere�o";
    ls->confMemType              = "Tipo";
    ls->confMemRomImage          = "Imagem Rom ";
    
    ls->confChipVideoGB          = "Video ";
    ls->confChipVideoChip        = "Video Chip:";
    ls->confChipVideoRam         = "Video RAM:";
    ls->confChipSoundGB          = "Som ";

    ls->confCmosGB                = "CMOS "; 
    ls->confCmosEnable            = " Ativar CMOS"; 
    ls->confCmosBattery           = " Utilizar uma Bateria Carregada";

    ls->confCpuFreqGB            = "Freq��ncia CPU "; 
    ls->confZ80FreqText          = "Freq��ncia Z80:"; 
    ls->confR800FreqText         = "Freq��ncia R800:"; 
    ls->confFdcGB                = "Controlador do Drive "; 
    ls->confCFdcNumDrivesText    = "N�mero das Drives:"; 

    ls->confEditMemTitle         = "blueMSX - Editar Mapper";
    ls->confEditMemGB            = "Detalhes do Mapper ";
    ls->confEditMemType          = "Tipo:";
    ls->confEditMemFile          = "Arquivo:";
    ls->confEditMemAddress       = "Endere�o";
    ls->confEditMemSize          = "Tamanho";
    ls->confEditMemSlot          = "Slot";


    //----------------------
    // Shortcut lines
    //----------------------

    ls->shortcutKey             = "Hotkey"; 
    ls->shortcutDescription     = "Shortcut"; 

    ls->shortcutSaveConfig      = "blueMSX - Salvar Configura��o";
    ls->shortcutOverwriteConfig = "Voc� quer  substituir esta configura��o da m�quina?:";
    ls->shortcutExitConfig      = "blueMSX - Sair do Editor de Atalhos";
    ls->shortcutDiscardConfig   = "Voce quer desfazer as altera��es da Configura��o atual ?";
    ls->shortcutSaveConfigAs    = "blueMSX - Salvar Configura��o de Atalhos Como...";
    ls->shortcutConfigName      = "Nome da Configura��o:";
    ls->shortcutNewProfile      = "< Novo Perfil >";
    ls->shortcutConfigTitle     = "blueMSX - Editor do Mapa dos Atalhos";
    ls->shortcutAssign          = "Atribuir";
    ls->shortcutPressText       = "Apoiar sobre Tecla(s) :";
    ls->shortcutScheme          = "Disposi��o:";
    ls->shortcutCartInsert1     = "Inserir Cartucho no Slot 1";
    ls->shortcutCartRemove1     = "Remover Cartucho no Slot 1";
    ls->shortcutCartInsert2     = "Inserir Cartucho no Slot 2";
    ls->shortcutCartRemove2     = "Remover Cartucho no Slot 2";
    ls->shortcutSpecialMenu1    = "Mostrar Menu Especial para Cartucho no Slot 1";
    ls->shortcutSpecialMenu2    = "Mostrar Menu Especial para Cartucho no Slot 2";
    ls->shortcutCartAutoReset   = "Reset ap�s inserir cartucho";
    ls->shortcutDiskInsertA     = "Inserir Disco no Drive A";
    ls->shortcutDiskDirInsertA  = "Inserir um diret�rio como disco A"; 
    ls->shortcutDiskRemoveA     = "Ejetar  Disco no Drive A ";
    ls->shortcutDiskChangeA     = "Alterar rapidamente Disco no Drive A";
    ls->shortcutDiskAutoResetA  = "Reset ap�s inserir Disco no Drive A ";
    ls->shortcutDiskInsertB     = "Insira Disco no Drive B";
    ls->shortcutDiskDirInsertB  = "Inserir um diret�rio como disco B"; 
    ls->shortcutDiskRemoveB     = "Ejetar Disco no Drive B";
    ls->shortcutCasInsert       = "Inserir Cassette";
    ls->shortcutCasEject        = "Ejetar Cassette";
    ls->shortcutCasAutorewind   = "Rebobina��o autom�tica ou n�o do cassete";
    ls->shortcutCasReadOnly     = "Cassete em modo leitura somente ou n�o";
    ls->shortcutCasSetPosition  = "Ajustar Posi��o";
    ls->shortcutCasRewind       = "Rebobinar Cassette";
    ls->shortcutCasSave         = "Salvar Imagem do Cassette Como...";
    ls->shortcutPrnFormFeed     = "Passagem para a p�gina seguinte"; 
    ls->shortcutCpuStateLoad    = "Carregar Status da CPU";
    ls->shortcutCpuStateSave    = "Salvar Status da CPU";
    ls->shortcutCpuStateQload   = "Carregar rapido Status da CPU";
    ls->shortcutCpuStateQsave   = "Salvar rapido Status da CPU";
    ls->shortcutAudioCapture    = "Come�ar/parar a captura �udio";
    ls->shortcutScreenshotOrig  = "Salvar Tela";
    ls->shortcutScreenshotSmall = "Pequena captura da tela sem filtro";
    ls->shortcutScreenshotLarge = "Grande captura da tela sem filtro";
    ls->shortcutQuit            = "Sair blueMSX";
    ls->shortcutRunPause        = "Executar/Pausa Emula��o ";
    ls->shortcutStop            = "Parar Emula��o";
    ls->shortcutResetHard       = "Reset Completo";
    ls->shortcutResetSoft       = "Reset Leve";
    ls->shortcutResetClean      = "Reset Geral";
    ls->shortcutSizeSmall       = "Passar em modo Janela Tamanho Normal";
    ls->shortcutSizeNormal      = "Passar em modo Janela Tamanho Duplo";
    ls->shortcutSizeFullscreen  = "Passar em modo Tela Cheia";
    ls->shortcutSizeMinimized   = "Reduzir a Janela"; 
    ls->shortcutToggleFullscren = "Troca de modo Janela/Tela Cheia";
    ls->shortcutVolumeIncrease  = "Aumentar Volume sonoro";
    ls->shortcutVolumeDecrease  = "Diminuir Volume sonoro";
    ls->shortcutVolumeMute      = "Parar Som";
    ls->shortcutVolumeStereo    = "Troca Mono/Estereo";
    ls->shortcutSwitchMsxAudio  = "Impulsionar Bot�o cartucho MSX-AUDIO";
    ls->shortcutSwitchFront     = "Impulsionar Bot�o frontal Panasonic";
    ls->shortcutSwitchPause     = "Impulsionar Botao Pause"; 
    ls->shortcutToggleMouseLock = "Ativar/Desativar Bloqueio do Mouse";
    ls->shortcutEmuSpeedMax     = "Velocidade M�xima da Emula��o";
    ls->shortcutEmuSpeedToggle  = "Troca de Velocidade M�xima da Emula��o"; 
    ls->shortcutEmuSpeedNormal  = "Velocidade Normal da Emula��o";
    ls->shortcutEmuSpeedInc     = "Aumentar Velocidade da Emula��o";
    ls->shortcutEmuSpeedDec     = "Diminuir Velocidade da Emula��o";
    ls->shortcutThemeSwitch     = "Troque o tema";
    ls->shortcutShowEmuProp     = "Mostrar Propriedades da Emula��o";
    ls->shortcutShowVideoProp   = "Mostrar Propriedades Video";
    ls->shortcutShowAudioProp   = "Mostrar Propriedades de Som";
    ls->shortcutShowCtrlProp    = "Mostrar Propriedades dos Controles";
    ls->shortcutShowPerfProp    = "Mostrar Propriedades Performance";
    ls->shortcutShowSettProp    = "Mostrar Propriedades dos Ajustes";
    ls->shortcutShowPorts       = "Mostrar Propriedades das Portas";
    ls->shortcutShowLanguage    = "Mostrar Di�logo da L�ngua";
    ls->shortcutShowMachines    = "Mostrar Configura��o da M�quina";
    ls->shortcutShowShortcuts   = "Mostrar Configura��o de Atalhos";
    ls->shortcutShowKeyboard    = "Mostrar Configura��o do Teclado"; 
    ls->shortcutShowMixer       = "Mostre Mixer de Audio"; 
    ls->shortcutShowDebugger    = "Mostrar Debugger"; 
    ls->shortcutShowTrainer     = "Mostrar Trainer"; 
    ls->shortcutShowHelp        = "Ver Rubricas da Ajuda";
    ls->shortcutShowAbout       = "Ver Rubrica Sobre blueMSX";
    ls->shortcutShowFiles       = "Mostrar Propriedades de Arquivos";
    ls->shortcutToggleSpriteEnable = "Mostrar/esconder os sprites";
    ls->shortcutToggleFdcTiming = "sincronizar ou n�o disco drive"; 
    ls->shortcutToggleCpuTrace  = "Ativar/Desativar Tra�o da CPU"; 


    //----------------------
    // Keyboard config lines
    //----------------------

    ls->keyconfigSelectedKey    = "Tecla MSX seleccionada:"; 
    ls->keyconfigMappedTo       = "Atribu�da � tecla PC :"; 
    ls->keyconfigMappingScheme  = "Configura��o do teclado:"; 
};

#endif
