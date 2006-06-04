/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguagePortuguese.h,v $
**
** $Revision: 1.20 $
**
** $Date: 2006-06-04 00:43:35 $
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

    ls->menuNoRecentFiles       = "- Sem Arquivos Recentes -";
    ls->menuInsert              = "Inserir";
    ls->menuEject               = "Ejetar";

    ls->menuCartAutoReset       = "Reset após inserir/remover";
    ls->menuCartFMPac           = "Cartucho FM-PAC";
    ls->menuCartPac             = "Cartucho PAC";

    ls->menuDiskAutoStart       = "Reset após inserir";
    
    ls->menuCasSetPosition      = "Ajustar Posição";
    ls->menuCasRewind           = "Rebobinar";

    ls->menuZoomNormal          = "Tamanho Normal";
    ls->menuZoomDouble          = "Tamanho Duplo";
    ls->menuZoomFullscreen      = "Tela Cheia";
    
    ls->menuPropsEmulation      = "Emulação";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Som";
    ls->menuPropsControls       = "Controles";
    ls->menuPropsPerformance    = "Performance";
    ls->menuPropsLanguage       = "Linguagem";
    
    ls->menuHelpHelp            = "Tópicos Ajuda";
    ls->menuHelpAbout           = "Sobre blueMSX";

    ls->menuFileCart            = "Cartucho Slot";
    ls->menuFileDisk            = "Disco drive";
    ls->menuFileCas             = "Cassette";
    ls->menuFileLoadState       = "Carregar Status da CPU";
    ls->menuFileSaveState       = "Salvar Status da CPU";
    ls->menuFileQLoadState      = "Carregar rápido Status";
    ls->menuFileQSaveState      = "Salvar rápido Status";
    ls->menuFileCaptureAudio    = "Capturar áudio";
    ls->menuFileScreenShot      = "Salvar Tela";
    ls->menuFileExit            = "Sair";

    ls->menuRunRun              = "Executar";
    ls->menuRunPause            = "Pausa";
    ls->menuRunStop             = "Parar";
    ls->menuRunSoftReset        = "Reset Completo";
    ls->menuRunHardReset        = "Reset Leve";
    ls->menuRunCleanReset       = "Reset Geral";

    ls->menuFile                = "Arquivo";
    ls->menuRun                 = "Execução";
    ls->menuWindow              = "Janela";
    ls->menuOptions             = "Opções";
    ls->menuHelp                = "Ajuda";
    
    ls->errorTitle              = "blueMSX - Erro";
    ls->errorEnterFullscreen    = "Falha ao entrar em Tela Cheia.             \n";
    ls->errorDirectXFailed      = "Falha ao Criar Objetos DirectX.             \nUsando GDI ao invés.\nCheque as propriedades Video.";
    ls->errorNoRomInZip         = "Nao foi localizado arquivo .ROM dentro do arquivo zip.";
    ls->errorNoDskInZip         = "Nao foi localizado arquivo .DSK dentro do arquivo zip.";
    ls->errorNoCasInZip         = "Nao foi localizado arquivo .CAS dentro do arquivo zip.";
    ls->errorNoHelp             = "Nao foi localizado arquivo ajuda do blueMSX";
    ls->errorStartEmu           = "Falha ao Iniciar o emulador MSX.";


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
    ls->dlgInsertRom1           = "Insira cartucho ROM no slot 1";
    ls->dlgInsertRom2           = "Insira cartucho ROM no slot 2";
    ls->dlgInsertDiskA          = "Insira disco no drive A";
    ls->dlgInsertDiskB          = "Insira disco no drive B";
    ls->dlgInsertCas            = "Insira cassette tape";

    ls->dlgOK                   = "OK";
    ls->dlgOpen                 = "Abrir";
    ls->dlgCancel               = "Cancelar";

    ls->dlgTapeTitle            = "blueMSX - Posição do Tape";
    ls->dlgTapeFrameText        = "Posição do Tape";
    ls->dlgTapeCurrentPos       = "Posição Atual";
    ls->dlgTapeTotalTime        = "Tempo Total";

    ls->dlgZipReset             = "Reset após inserir";

    ls->dlgAboutTitle           = "blueMSX - Sobre";

    ls->dlgLangLangText         = "Escolha uma linguagem que blueMSX irá usar";
    ls->dlgLangLangTitle        = "blueMSX - Linguagem";

    ls->propTitle               = "blueMSX - Propriedades";
    ls->propEmulation           = "Emulação";
    ls->propVideo               = "Video";
    ls->propSound               = "Som";
    ls->propControls            = "Controles";
    ls->propPerformance         = "Performance";
    
    ls->propEmuGeneralGB        = "Geral ";
    ls->propEmuFamilyText       = "MSX :";
    ls->propEmuMemoryGB         = "Memória ";
    ls->propEmuRamSizeText      = "Tamanho RAM :";
    ls->propEmuVramSizeText     = "Tamanho VRAM :";
    ls->propEmuSpeedGB          = "Velocidade da Emulação ";
    ls->propEmuSpeedText        = "Velocidade da Emulação:";

    ls->propMonMonGB            = "Monitor:";
    ls->propMonTypeText         = "Tipo de Monitor:";
    ls->propMonEmuText          = "Emulacão de Monitor:";
    ls->propVideoTypeText       = "Tipo de Video:";
    ls->propWindowSizeText      = "Tamanho Janela:";

    ls->propPerfVideoDrvGB      = "Driver de Video:";
    ls->propPerfVideoDispDrvText= "Driver do Display:";
    ls->propPerfFrameSkipText   = "Frame skipping:";
    ls->propPerfAudioDrvGB      = "Driver de Audio:";
    ls->propPerfAudioDrvText    = "Driver de Som:";
    ls->propPerfAudioBufSzText  = "Tamanho buffer Som:";
    ls->propPerfEmuGB           = "Emulação:";
    ls->propPerfSyncModeText    = "Modo Sincronismo:";

    ls->propSndChipEmuGB        = "Emulação do Chip de Som";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";

    ls->enumVideoMonColor       = "Cor";
    ls->enumVideoMonGrey        = "Branco e Preto";
    ls->enumVideoMonGreen       = "Verde";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC e PAL-M";

    ls->enumVideoEmuNone        = "Nenhum";
    ls->enumVideoEmuYc          = "Y/C cable (sharp)";
    ls->enumVideoEmuYcBlur      = "Noisy Y/C cable (sharp)";
    ls->enumVideoEmuComp        = "Composite (blurry)";
    ls->enumVideoEmuCompBlur    = "Noisy Composite (blurry)";
    ls->enumVideoEmuScale2x     = "Escala 2x";

    ls->enumVideoSize1x         = "Normal - 320x200";
    ls->enumVideoSize2x         = "Duplo  - 640x400";
    ls->enumVideoSizeFullscreen = "Tela Cheia";

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

    ls->enumEmuSync1ms          = "1ms (Melhor)";
    ls->enumEmuSyncAuto         = "Auto (Rápido)";

    ls->enumControlsJoyNone     = "Nenhum";
    ls->enumControlsJoyMouse    = "Mouse";

    ls->dlgAboutAbout           = "Sobre\r\n====";
    ls->dlgAboutVersion         = "Versão:";
    ls->dlgAboutBuildNumber     = "Compilação:";
    ls->dlgAboutBuildDate       = "Data:";
    ls->dlgAboutDevel           = "Desenvolvido por Daniel Vik";
    ls->dlgAboutThanks          = "MUITO OBRIGADO PARA\r\n============";
    ls->dlgAboutLisence         = "LICENÇA\r\n"
                                  "======\r\n\r\n"
                                  "Este software é provido 'como-está', sem Garantia expressa ou implicada."
                                  "Em Nenhuma circunstancia os autores serão responsaveis por qualquer "
                                  "Problema ou DANO proveniente do uso deste software.\r\n\r\n"
                                  "Visite www.bluemsx.com para mais detalhes.";


    
    ls->dlgAboutCreat           = "Criado Por Daniel Vik";
    ls->dlgAboutDevel           = "DESENVOLVEDORES\r\n========";

    // New entries
    ls->menuTools                = "Ferramentas";
    ls->menuToolsMachine         = "Configuração da Máquina";
    ls->menuPropsSettings        = "Ajustes";
    ls->menuCasRewindAfterInsert = "Rebobinar Apos Inserir";
    ls->menuCasUseReadOnly       = "Usar Cassete Como Somente Leitura";
    ls->lmenuCasSaveAs           = "Salvar Imagem do Cassete Como...";

    ls->dlgSaveCassette          = "blueMSX - Salvar Imagem Tape";
    ls->dlgTapeCustom            = "Mostrar Arquivos Personalizados";
    ls->dlgTapeSetPosText        = "Posição do Cassete:";
    ls->dlgTabPosition           = "Posição";
    ls->dlgTabType               = "Tipo";
    ls->dlgTabFilename           = "Nome do Arquivo";

    ls->propSettings             = "Ajustes";
    
    ls->propSetFileHistoryGB     = "Histórico ";
    ls->propSetFileHistorySize   = "Numero de itens no Histórico:";
    ls->propSetFileHistoryClear  = "Limpar Histórico";
    ls->propSetScreenSaver       = " Desabilitar Proteção de Tela Quando blueMSX estiver ativo";

    ls->confTitle                = "blueMSX - Editor de Configuração da Maquina";
    ls->confSave                 = "Salvar";
    ls->confSaveAs               = "Salvar Como";
    ls->confRun                  = "Executar";
    ls->confClose                = "Fechar";
    ls->confConfigText           = "Configuração";
    ls->confSlotLayout           = "Slot Layout";
    ls->confMemory               = "Memória";
    ls->confChipEmulation        = "Emulação do Chip";

    ls->confSlotLayoutGB         = "Layout do Slot ";
    ls->confSlotExtSlotGB        = "Slots Externos";
    ls->confSlotCart             = "Cartucho";
    ls->confSlotPrimary          = "Primário";
    ls->confSlotExpanded         = "Expandido (Quatro sub-slots)";

    ls->confMemAdd               = "Adicionar...";
    ls->confMemEdit              = "Editar...";
    ls->confMemRemove            = "Remover";
    ls->confMemSlot              = "Slot";
    ls->confMemAddresss          = "Endereço";
    ls->confMemType              = "Tipo";
    ls->confMemRomImage          = "Imagem Rom ";
    
    ls->confChipVideoGB          = "Video ";
    ls->confChipVideoChip        = "Video Chip:";
    ls->confChipVideoRam         = "Video RAM:";
    ls->confChipSoundGB          = "Som ";

    ls->confSaveTitle            = "blueMSX - Salvar Configuração";
    ls->confSaveText             = "Você quer substituir esta configuração da máquina? :";

    ls->confEditMemTitle         = "blueMSX - Editar Mapper";
    ls->confEditMemGB            = "Detalhes do Mapper ";
    ls->confEditMemType          = "Tipo:";
    ls->confEditMemFile          = "Arquivo:";
    ls->confEditMemAddress       = "Endereço";
    ls->confEditMemSize          = "Tamanho";
    ls->confEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Configuração";
    ls->confExitSaveTitle        = "blueMSX - Sair do Editor de Configuração";
    ls->confExitSaveText         = "Voce quer desfazer as alterações da Configuração atual ?";

    ls->confSaveAsMachineTitle   = "blueMSX - Salvar Configuração da Maquina Como...";
    ls->confSaveAsMachineName    = "Nome da Maquina:";

    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypes            = " Associar certos tipos de arquivo com blueMSX";
    ls->propDisableWinKeys       = " Função MSX automática para as teclas Windows"; 
    ls->propWindowsEnvGB         = "Ambiente Windows";

    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW acel.";
    ls->propMonHorizStretch      = " Estiramento Horizontal"; 
    ls->propClearHistory         = "Deseja realmente limpar histórico ?";
    ls->propEmuFrontSwitchGB     = "Botão Panasonic "; 
    ls->propEmuFrontSwitch       = " Botão Frontal"; 
    ls->propEmuAudioSwitch       = " Botão Cartucho MSX-AUDIO"; 
    ls->propMonVertStretch       = " Estiramento Vertical"; 

    ls->confCmosGB                = "CMOS "; 
    ls->confCmosEnable            = " Ativar CMOS"; 
    ls->confCmosBattery           = " Utilizar uma Bateria Carregada";

    ls->menuCartSCCPlus         = "Cartucho SCC+";
    ls->menuCartSCC             = "Cartucho SCC";
    
    ls->warningTitle             = "blueMSX - Advertência";


    // New entries in 1.5.1
    ls->menuToolsShortcuts      = "Configuração de Atalhos";

    ls->shortcutSaveConfig      = "blueMSX - Salvar Configuração";
    ls->shortcutOverwriteConfig = "Você quer  substituir esta configuração da máquina?:";
    ls->shortcutExitConfig      = "blueMSX - Sair do Editor de Atalhos";
    ls->shortcutDiscardConfig   = "Voce quer desfazer as alterações da Configuração atual ?";
    ls->shortcutSaveConfigAs    = "blueMSX - Salvar Configuração de Atalhos Como...";
    ls->shortcutConfigName      = "Nome da Configuração:";
    ls->shortcutNewProfile      = "< Novo Perfil >";
    ls->shortcutConfigTitle     = "blueMSX - Editor do Mapa dos Atalhos";
    ls->shortcutAssign          = "Atribuir";
    ls->shortcutPressText       = "Apoiar sobre Tecla(s) :";
    ls->shortcutScheme          = "Disposição:";

    ls->shortcutCartInsert1     = "Inserir Cartucho no Slot 1";
    ls->shortcutCartRemove1     = "Remover Cartucho no Slot 1";
    ls->shortcutCartInsert2     = "Inserir Cartucho no Slot 2";
    ls->shortcutCartRemove2     = "Remover Cartucho no Slot 2";
    ls->shortcutCartAutoReset   = "Reset após inserir cartucho";
    ls->shortcutDiskInsertA     = "Inserir Disco no Drive A";
    ls->shortcutDiskRemoveA     = "Ejetar  Disco no Drive A ";
    ls->shortcutDiskChangeA     = "Alterar rapidamente Disco no Drive A";
    ls->shortcutDiskAutoResetA  = "Reset após inserir Disco no Drive A ";
    ls->shortcutDiskInsertB     = "Insira Disco no Drive B";
    ls->shortcutDiskRemoveB     = "Ejetar Disco no Drive B";
    ls->shortcutCasInsert       = "Inserir Cassette";
    ls->shortcutCasEject        = "Ejetar Cassette";
    ls->shortcutCasAutorewind   = "Rebobinação automática ou não do cassete";
    ls->shortcutCasReadOnly     = "Cassete em modo leitura somente ou não";
    ls->shortcutCasSetPosition  = "Ajustar Posição";
    ls->shortcutCasRewind       = "Rebobinar Cassette";
    ls->shortcutCasSave         = "Salvar Imagem do Cassette Como...";
    ls->shortcutCpuStateLoad    = "Carregar Status da CPU";
    ls->shortcutCpuStateSave    = "Salvar Status da CPU";
    ls->shortcutCpuStateQload   = "Carregar rapido Status da CPU";
    ls->shortcutCpuStateQsave   = "Salvar rapido Status da CPU";
    ls->shortcutAudioCapture    = "Começar/parar a captura áudio";
    ls->shortcutScreenshotOrig  = "Salvar Tela";
    ls->shortcutScreenshotSmall = "Pequena captura da tela sem filtro";
    ls->shortcutScreenshotLarge = "Grande captura da tela sem filtro";
    ls->shortcutQuit            = "Sair blueMSX";
    ls->shortcutRunPause        = "Executar/Pausa Emulação ";
    ls->shortcutStop            = "Parar Emulação";
    ls->shortcutResetHard       = "Reset Completo";
    ls->shortcutResetSoft       = "Reset Leve";
    ls->shortcutResetClean      = "Reset Geral";
    ls->shortcutSizeSmall       = "Passar em modo Janela Tamanho Normal";
    ls->shortcutSizeNormal      = "Passar em modo Janela Tamanho Duplo";
    ls->shortcutSizeFullscreen  = "Passar em modo Tela Cheia";
    ls->shortcutToggleFullscren = "Troca de modo Janela/Tela Cheia";
    ls->shortcutVolumeIncrease  = "Aumentar Volume sonoro";
    ls->shortcutVolumeDecrease  = "Diminuir Volume sonoro";
    ls->shortcutVolumeMute      = "Parar Som";
    ls->shortcutSwitchMsxAudio  = "Impulsionar Botão cartucho MSX-AUDIO";
    ls->shortcutSwitchFront     = "Impulsionar Botão frontal Panasonic";
    ls->shortcutToggleMouseLock = "Ativar/Desativar Bloqueio do Mouse";
    ls->shortcutEmuSpeedMax     = "Velocidade Máxima da Emulação";
    ls->shortcutEmuSpeedNormal  = "Velocidade Normal da Emulação";
    ls->shortcutEmuSpeedInc     = "Aumentar Velocidade da Emulação";
    ls->shortcutEmuSpeedDec     = "Diminuir Velocidade da Emulação";
    ls->shortcutShowEmuProp     = "Mostrar Propriedades da Emulação";
    ls->shortcutShowVideoProp   = "Mostrar Propriedades Video";
    ls->shortcutShowAudioProp   = "Mostrar Propriedades de Som";
    ls->shortcutShowCtrlProp    = "Mostrar Propriedades dos Controles";
    ls->shortcutShowPerfProp    = "Mostrar Propriedades Performance";
    ls->shortcutShowSettProp    = "Mostrar Propriedades dos Ajustes";
    ls->shortcutShowLanguage    = "Mostrar Diálogo da Língua";
    ls->shortcutShowMachines    = "Mostrar Configuração da Máquina";
    ls->shortcutShowShortcuts   = "Mostrar Configuração de Atalhos";
    ls->shortcutShowHelp        = "Ver Rubricas da Ajuda";
    ls->shortcutShowAbout       = "Ver Rubrica Sobre blueMSX";

    ls->shortcutSpecialMenu1    = "Mostrar Menu Especial para Cartucho no Slot 1";
    ls->shortcutSpecialMenu2    = "Mostrar Menu Especial para Cartucho no Slot 2";
    ls->shortcutVolumeStereo    = "Troca Mono/Estereo";
    ls->shortcutThemeSwitch     = "Troque o tema";
    ls->shortcutToggleSpriteEnable = "Mostrar/esconder os sprites";
    
    ls->shortcutShowApearProp   = "Mostrar Propriedades";
    ls->menuPropsApearance      = "Aparência";
    ls->propThemeGB             = "Tema ";
    ls->propTheme               = "Tema";

    ls->propMonBrightness       = "Brilho:";
    ls->propMonContrast         = "Contraste:";
    ls->propMonSaturation       = "Saturação:";
    ls->propMonGamma            = "Gama:";
    ls->propMonScanlines        = " Scanlines:";

    ls->dlgRomType              = "Tipo rom:"; 
    ls->propOpenRomGB           = "Abrir arquivo rom"; 
    ls->propDefaultRomType      = "Tipo de ROM Padrão:"; 
    ls->propGuessRomType        = "Adivinhar tipo"; 

    ls->propFile                = "Arquivo"; 
    ls->propSettDefSlotGB       = "Deslizar e depositar "; 
    ls->propSettDefSlots        = "Inserir cartucho no:"; 
    ls->propSettDefSlot         = " Slot"; 
    ls->propSettDefDrives       = "Inserir disco no:"; 
    ls->propSettDefDrive       = " Drive"; 
    ls->menuPropsFile           = "Arquivo"; 
    ls->shortcutShowFiles       = "Mostrar Propriedades de Arquivos";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "Inserir diretório"; 
    ls->shortcutDiskDirInsertA  = "Inserir um diretório como disco A"; 
    ls->shortcutDiskDirInsertB  = "Inserir um diretório como disco B"; 
    ls->propMonDeInterlace      = " De-entrelaçar";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "Impulsionar Botao Pause"; 
    ls->shortcutSizeMinimized   = "Reduzir a Janela"; 
    ls->shortcutEmuSpeedToggle  = "Troca de Velocidade Máxima da Emulação"; 
    ls->shortcutToggleCpuTrace  = "Ativar/Desativar Traço da CPU"; 

    ls->enumVideoEmuMonitor     = "Monitor"; 

    ls->propEmuPauseSwitch      = " Botão Pause "; 
    ls->propVideoFreqText       = "Freqüência video:"; 
    ls->propVideoFreqAuto       = "Auto"; 
    ls->propSndOversampleText   = "Oversample:"; 

    ls->confChipExtras          = "Extras"; 
    ls->confBoardGB             = "Sistema "; 
    ls->confBoardText           = "Sistema tipo:"; 
    ls->confCpuFreqGB            = "Freqüência CPU "; 
    ls->confZ80FreqText          = "Freqüência Z80:"; 
    ls->confR800FreqText         = "Freqüência R800:"; 
    ls->confFdcGB                = "Controlador do Drive "; 
    ls->confCFdcNumDrivesText    = "Número das Drives:"; 

    ls->propPriorityBoost       = " Dar ao blueMSX uma prioridade elevada";

    // New entries in 2.1
    ls->propEmuFdcTiming        = " Não sincronizar disco do drive"; 
    ls->shortcutToggleFdcTiming = "sincronizar ou não disco drive"; 

    // New entries in 2.2
    ls->menuCartHBI55           = "Cartucho Sony HBI-55"; 
    ls->enumVideoEmuHq2x        = "Hq2x"; 
    ls->propMonColorGhosting    = " Modulador RF"; 

    ls->keyconfigSelectedKey    = "Tecla MSX seleccionada:"; 
    ls->keyconfigMappedTo       = "Atribuída à tecla PC :"; 
    ls->keyconfigMappingScheme  = "Configuração do teclado:"; 

    ls->warningDiscardChanges   = "Você quer desfazer as alterações da configuração atual?"; 

    ls->confSaveAsTitle         = "Salvar Como"; 

    ls->menuToolsKeyboard       = "Configuração do Teclado"; 
    ls->shortcutShowKeyboard    = "Mostrar Configuração do Teclado"; 

    ls->menuVideoSource         = "Fonte Vídeo"; 
    ls->menuVideoSourceDefault  = "Nenhuma fonte vídeo"; 
    ls->menuVideoChipAutodetect = "Detecção automática"; 
    ls->propFullscreenResText   = "Resolução tela cheia:"; 
    ls->dlgSavePreview          = "Visualizar"; 
    ls->dlgSaveDate             = "Data:"; 

    ls->enumVideoMonAmber       = "Âmbar"; 

    ls->menuPropsPorts          = "Portas"; 
    ls->propPortsLptGB          = "Porta paralela "; 
    ls->propPortsComGB          = "Portas seriais "; 
    ls->propPortsLptText        = "Porta:"; 
    ls->propPortsCom1Text       = "Porta 1:"; 

    ls->shortcutShowDebugger    = "Mostrar Debugger"; 
    ls->shortcutShowTrainer     = "Mostrar Trainer"; 
    ls->shortcutShowPorts       = "Mostrar Propriedades das Portas";
    
    ls->propPorts               = "Portas";
    ls->propPortsNone           = "Nenhum";

    // New entries in 2.3 
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle"; 

    ls->propPortsSimplCovox     = "SiMPL / Covox DAC"; 
    ls->propPortsFile           = "Imprimir em arquivo"; 
    ls->propPortsOpenLogFile    = "Abrir um arquivo de dados"; 
    ls->propPortsEmulateMsxPrn  = "Emulação:"; 

    ls->shortcutPrnFormFeed     = "Passagem para a página seguinte"; 

    ls->menuPrnFormfeed         = "Página seguinte"; 
    ls->menuFilePrn             = "Impressora"; 
    ls->propPortsComFile        = "Enviar para arquivo";

    // New entries in 2.4 
    ls->shortcutShowMixer       = "Mostre Mixer de Audio"; 
    ls->menuToolsMixer          = "Mixer de Audio"; 
    
    ls->propSndMidiInGB         = "MIDI In "; 
    ls->propSndMidiOutGB        = "MIDI Out "; 
    ls->propSndMt32ToGm         = " Mapa instrumentos MT-32 a General MIDI"; 

    ls->textDevice              = "Tipo:"; 
    ls->textFilename            = "Nome:"; 
    ls->textFile                = "Arquivo"; 
    ls->textNone                = "Nenhum"; 

    ls->enumEmuSyncNone         = "Nenhum"; 
    ls->enumEmuSyncAuto         = "Auto (rapido)"; 
    ls->enumEmuSync1ms          = "Sinc sobre MSX refresh"; 
    ls->enumEmuSyncVblank       = "Sinc sobre PC Vertical Blank"; 

    ls->propMonEffectsGB        = "Efeitos "; 
    
    ls->confSlot                = "Slot"; 
    ls->confSubslot             = "Sub-slot"; 

    ls->shortcutDescription     = "Shortcut"; 
    ls->shortcutKey             = "Hotkey"; 
    ls->fileRom                 = "ROM image"; 
    ls->confOpenRom             = "Abrir ROM image"; 
    ls->fileAll                 = "Todos os arquivos"; 
    ls->fileCpuState            = "Status da CPU"; 
    ls->fileDisk                = "Disk Image"; 
    ls->fileCas                 = "Tape Image"; 

    ls->menuCartExternalRam     = "RAM esterno";
};

#endif


