/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguagePortuguese.h,v $
**
** $Revision: 1.8 $
**
** $Date: 2005-03-03 16:38:38 $
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
    ls->statusBarStopped        = "  Parado ";
    ls->statusBarPaused         = "  Pausa ";
    ls->statusBarRunning        = "  Executando";
    
    ls->menuHardReset           = "Reset Completo";
    ls->menuSoftReset           = "Reset Leve";
    
    ls->menuCartInsert          = "Inserir";
    ls->menuCartRemove          = "Remover";
    ls->menuCartAutoReset       = "Reset apos inserir/remover";
    ls->menuCartNoRecentFiles   = "- Sem Arquivos Recentes -";
    ls->menuCartFMPac           = "Cartucho FM-PAC";
    ls->menuCartPac           = "Cartucho PAC";
    ls->menuCartSpecial         = "Especial";

    ls->menuDiskInsert          = "Inserir";
    ls->menuDiskEject           = "Ejetar";
    ls->menuDiskAutoStart       = "Reset apos inserir";
    ls->menuDiskNoRecentFiles   = "- Sem Arquivos Recentes -";
    
    ls->menuCasInsert           = "Inserir";
    ls->menuCasEject            = "Ejetar";
    ls->menuCasSetPosition      = "Ajustar Posição";
    ls->menuCasRewind           = "Rebobinar";
    ls->menuCasNoRecentFiles    = "- Sem Arquivos Recentes -";

    ls->menuZoomNormal          = "Tamanho Normal";
    ls->menuZoomDouble          = "Tamanho Duplo";
    ls->menuZoomFullscreen      = "Tela Cheia";
    
    ls->menuPropsEmulation      = "Emulação";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Som";
    ls->menuPropsControls       = "Controles";
    ls->menuPropsPerformance    = "Performance";
    ls->menuPropsLanguage       = "Linguagem";
    
    ls->menuHelpHelp            = "Topicos Ajuda";
    ls->menuHelpAbout           = "Sobre blueMSX";

    ls->menuFileCart1           = "Cartucho slot 1";
    ls->menuFileCart2           = "Cartucho slot 2";
    ls->menuFileDiskA           = "Disco drive A";
    ls->menuFileDiskB           = "Disco drive B";
    ls->menuFileCas             = "Cassette";
    ls->menuFileLoadState       = "Carregar Status da CPU";
    ls->menuFileSaveState       = "Salvar Status da CPU";
    ls->menuFileQLoadState      = "Carregar rapido Status";
    ls->menuFileQSaveState      = "Salvar rapido Status";
    ls->menuFileCaptureAudio    = "Capturar audio";
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
    ls->errorDirectXFailed      = "Falha ao Criar Objetos DirectX.             \nUsando GDI ao inves.\nCheque as propriedades Video.";
    ls->errorNoRomInZip         = "Nao foi localizado arquivo .ROM dentro do arquivo zip.";
    ls->errorNoDskInZip         = "Nao foi localizado arquivo .DSK dentro do arquivo zip.";
    ls->errorNoCasInZip         = "Nao foi localizado arquivo .CAS dentro do arquivo zip.";
    ls->errorNoHelp             = "Nao foi localizado arquivo ajuda do blueMSX";
    ls->errorStartEmu           = "Falha ao Iniciar o emulador MSX.";

    ls->tooltipReset            = "Reset MSX";
    ls->tooltipCart1            = "Insira Cartucho no Slot 1";
    ls->tooltipCart2            = "Insira Cartucho no Slot 2";
    ls->tooltipDiskA            = "Insira Disco no Drive A";
    ls->tooltipDiskB            = "Insira Disco no Drive B";
    ls->tooltipCas              = "Insira Tape no Cassette player";
    ls->tooltipStart            = "Iniciar emulação";
    ls->tooltipResume           = "Continuar emulação";
    ls->tooltipPause            = "Pausar emulação";
    ls->tooltipWindowSize       = "Ajustar tamanho Janela";
    ls->tooltipProperties       = "Abrir Propriedades";
    ls->tooltipHelp             = "Abrir Ajuda";

    ls->dlgMainWindow           = "  blueMSX";
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

    ls->dlgZipReset             = "Reset apos inserir";

    ls->dlgAboutTitle           = "blueMSX - Sobre";

    ls->dlgJoyTitle1            = "blueMSX - Ajuste Joystick A";
    ls->dlgJoyTitle2            = "blueMSX - Ajuste Joystick B";
    ls->dlgJoyUpText            = "Acima";
    ls->dlgJoyDownText          = "Abaixo";
    ls->dlgJoyLeftText          = "Esquerda";
    ls->dlgJoyRightText         = "Direita";
    ls->dlgJoyButton1Text       = "Botao 1";
    ls->dlgJoyButton2Text       = "Botao 2";
    ls->dlgJoyGB                = "Ajuste das Teclas ";

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
    ls->propEmuMemoryGB         = "Memoria ";
    ls->propEmuRamSizeText      = "Tamanho RAM :";
    ls->propEmuVramSizeText     = "Tamanho VRAM :";
    ls->propEmuSpeedGB          = "Velocidade da Emulação ";
    ls->propEmuSpeedText        = "Velocidade da Emulação:";

    ls->propMonMonGB            = "Monitor:";
    ls->propMonTypeText         = "Tipo de Monitor:";
    ls->propMonEmuText          = "Emulacão de Monitor:";
    ls->propVideoYypeText       = "Tipo de Video:";
    ls->propWindowSizeText      = "Tamanho Janela:";

    ls->propPerfVideoDrvGB      = "Driver de Video";
    ls->propPerfVideoDispDrvText= "Driver do Display:";
    ls->propPerfFrameSkipText   = "Frame skipping:";
    ls->propPerfAudioDrvGB      = "Driver de Audio:";
    ls->propPerfAudioDrvText    = "Driver de Som:";
    ls->propPerfAudioBufSzText  = "Tamanho buffer Som:";
    ls->propPerfEmuGB           = "Emulação ";
    ls->propPerfSyncModeText    = "Modo Sincronismo:";

    ls->propSndChipEmuGB        = "Emulação do Chip de Som";
    ls->propSndMixerGB          = "Mixer de Audio";
    ls->propSndMonoText         = "Mono";
    ls->propSndStereoText       = "Estereo";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "MASTER";

    ls->propJoyPort1GB          = "Porta #1";
    ls->propJoyPort2GB          = "Porta #2";
    ls->propJoyAutofireText     = "Auto-Tiro";
    ls->propJoyKeysetGB         = "Ajuste de Joystick";
    ls->propJoyKeyest1          = "Ajuste Joystick A";
    ls->propJoyKeyest2          = "Ajuste Joystick B";

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
    ls->enumEmuSyncAuto         = "Auto (Rapido)";

    ls->enumControlsJoyNone     = "Nenhum";
    ls->enumControlsJoyNumpad   = "Teclado Numerico";
    ls->enumControlsJoyKeysetA  = "Teclas A";
    ls->enumControlsJoyKeysetB  = "Teclas B";
    ls->enumControlsJoyPCjoy1   = "PC joystick #1";
    ls->enumControlsJoyPCjoy2   = "PC joystick #2";
    ls->enumControlsJoyMouse    = "Mouse";

    ls->enumControlsAfOff       = "Desligado";
    ls->enumControlsAfSlow      = "Lento";
    ls->enumControlsAfMedium    = "Medio";
    ls->enumControlsAfFast      = "Rapido";

    ls->dlgAboutAbout           = "Sobre\r\n====";
    ls->dlgAboutVersion         = "Versão:";
    ls->dlgAboutBuildNumber     = "Compilação:";
    ls->dlgAboutBuildDate       = "Data:";
    ls->dlgAboutDevel           = "Desenvolvido por Daniel Vik";
    ls->dlgAboutThanks          = "MOITO OBRIGADO PARA\r\n============";
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
    ls->menuToolsMachine         = "Configuração da Maquina";
    ls->menuPropsSettings        = "Ajustes";
    ls->menuCasRewindAfterInsert = "Rebobinar Apos Inserir";
    ls->menuCasUseReadOnly       = "Usar Cassette Como Somente Leitura";
    ls->lmenuCasSaveAs           = "Salvar Imagem do Cassette Como...";

    ls->dlgSaveCassette          = "blueMSX - Salvar Imagem Tape";
    ls->dlgTapeCustom            = "Mostrar Arquivos Personalizados";
    ls->dlgTapeSetPosText        = "Posição do Tape:";
    ls->dlgTabPosition           = "Posição";
    ls->dlgTabType               = "Tipo";
    ls->dlgTabFilename           = "Nome do Arquivo";

    ls->propSettings             = "Ajustes";
    
    ls->propSetFileHistoryGB     = "Histórico ";
    ls->propSetFileHistorySize   = "Numero de items no Histórico:";
    ls->propSetFileHistoryClear  = "Limpar Historico";
    ls->propSetScreenSaverGB     = "Proteção de Tela";
    ls->propSetScreenSaver       = "Desabilitar Proteção de Tela Quando blueMSX estiver ativo";

    ls->confTitle                = "blueMSX - Editor de Configuração da Maquina";
    ls->confSave                 = "Salvar";
    ls->confSaveAs               = "Salvar Como";
    ls->confRun                  = "Executar";
    ls->confClose                = "Fechar";
    ls->confConfigText           = "Configuração";
    ls->confSlotLayout           = "Slot Layout";
    ls->confMemory               = "Memoria";
    ls->confChipEmulation        = "Emulação do Chip";

    ls->confSlotLayoutGB         = "Layout do Slot ";
    ls->confSlotExtSlotGB        = "Slots Externos";
    ls->confSlotSlot0            = "Slot 0";
    ls->confSlotSlot1            = "Slot 1";
    ls->confSlotSlot2            = "Slot 2";
    ls->confSlotSlot3            = "Slot 3";
    ls->confSlotCart1            = "Cartucho 1:";
    ls->confSlotCart2            = "Cartucho 2:";
    ls->confSlotPrimary          = "Primario";
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
    ls->confSaveText             = "Você quer  substituir esta configuração da máquina? :";

    ls->slotEditMemTitle         = "blueMSX - Editar Mapper";
    ls->slotEditMemGB            = "Detalhes do Mapper ";
    ls->slotEditMemType          = "Tipo:";
    ls->slotEditMemFile          = "Arquivo:";
    ls->slotEditMemAddress       = "Endereço";
    ls->slotEditMemSize          = "Tamanho";
    ls->slotEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Configuração";
    ls->confExitSaveTitle        = "blueMSX - Sair do Editor de Configuração";
    ls->confExitSaveText         = "Voce quer desfazer as alterações da Configuração atual ?";

    ls->confSaveAsMachineTitle   = "blueMSX - Salvar Configuração da Maquina Como...";
    ls->confSaveAsMachineName    = "Nome da Maquina:";

    ls->confEditMemInternalRoms  = "blueMSX - Roms interno"; 


    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypesGB          = "Tipos de arquivo ";
    ls->propFileTypes            = " Associar certos tipos de arquivo com blueMSX";
    ls->propDisableWinKeys       = " Função MSX automática para as teclas Windows"; 
    ls->propWindowsEnvGB         = "Ambiente Windows";

    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW acel.";
    ls->enumVideoDrvDirectDrawHWSys = "DirectDraw mix."; 
    ls->propMonHorizStretch      = " Estiramento Horizontal"; 
    ls->propClearHistory         = "Désirez realmente limpar historico ?";
    ls->propEmuFrontSwitchGB     = "Botaoes Panasonic "; 
    ls->propEmuFrontSwitch       = " Botao Frontal"; 
    ls->propEmuAudioSwitch       = " Botao cartucho MSX-AUDIO"; 
    ls->propMonVertStretch       = " Estiramento Vertical"; 

    ls->dlgCmosGB                = "CMOS "; 
    ls->dlgCmosEnable            = " Activar CMOS"; 
    ls->dlgCmosBattery           = " Utilizar uma Bateria Carregada";

    ls->menuCartSnatcher        = "Cartucho The Snatcher";
    ls->menuCartSdSnatcher      = "Cartucho SD-Snatcher";
    ls->menuCartSCCMirrored     = "Cartucho SCC Mirrored";
    ls->menuCartSCCExpanded     = "Cartucho SCC Expanded";
    ls->menuCartSCCPlus         = "Cartucho SCC+";
    ls->menuCartSCC             = "Cartucho SCC";
    
    ls->warningTitle             = "blueMSX - Advertência";
    ls->tooltipStop              = "Parar emulação";


    // New entries in 1.5.1
    ls->enumControlsJoyKeyset   = "Keyset";    
    ls->propJoyConfigKeyset     = "Config Keyset";
    ls->propJoyControlText      = "Controlo:";
    ls->propJoyButtonText       = "Botao";
    ls->propJoyButtonAText      = "Botao A:";
    ls->propJoyButtonBText      = "Botao B:";

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
    ls->shortcutCartAutoReset   = "Reset apos inserir cartucho";
    ls->shortcutDiskInsertA     = "Inserir Disco no Drive A";
    ls->shortcutDiskRemoveA     = "Ejetar  Disco no Drive A ";
    ls->shortcutDiskChangeA     = "Alterar rapidamente Disco no Drive A";
    ls->shortcutDiskAutoResetA  = "Reset apos inserir Disco no Drive A ";
    ls->shortcutDiskInsertB     = "Insira Disco no Drive B";
    ls->shortcutDiskRemoveB     = "Ejetar Disco no Drive B";
    ls->shortcutCasInsert       = "Inserir Cassette";
    ls->shortcutCasEject        = "Ejetar Cassette";
    ls->shortcutCasAutorewind   = "Rebobinação automático ou não da cassete";
    ls->shortcutCasReadOnly     = "Cassete em modo leitura somente ou não";
    ls->shortcutCasSetPosition  = "Ajustar Posição";
    ls->shortcutCasRewind       = "Rebobinar Cassette";
    ls->shortcutCasSave         = "Salvar Imagem do Cassette Como...";
    ls->shortcutCpuStateLoad    = "Carregar Status da CPU";
    ls->shortcutCpuStateSave    = "Salvar Status da CPU";
    ls->shortcutCpuStateQload   = "Carregar rapido Status da CPU";
    ls->shortcutCpuStateQsave   = "Salvar rapido Status da CPU";
    ls->shortcutAudioCapture    = "Começar/parar a captura audio";
    ls->shortcutScreenshotOrig  = "Salvar Tela";
    ls->shortcutScreenshotSmall = "Pequena captura do tela sem filtro";
    ls->shortcutScreenshotLarge = "Grande captura do tela sem filtro";
    ls->shortcutQuit            = "Sair blueMSX";
    ls->shortcutRunPause        = "Executar/Pausa Emulação ";
    ls->shortcutStop            = "Parar Emulação";
    ls->shortcutResetHard       = "Reset Completo";
    ls->shortcutResetSoft       = "Reset Leve";
    ls->shortcutResetClean      = "Reset Geral";
    ls->shortcutSizeSmall       = "Passar em modo Janela Tamanho Normal";
    ls->shortcutSizeNormal      = "Passar em modo Janela Tamanho Duplo";
    ls->shortcutSizeFullscreen  = "Passar em modo Tela Cheia";
    ls->shortcutToggleFullscren = "Balança modo Janela/modo Tela Cheia";
    ls->shortcutVolumeIncrease  = "Aumentar Volume sonoro";
    ls->shortcutVolumeDecrease  = "Diminuir Volume sonoro";
    ls->shortcutVolumeMute      = "Parar Som";
    ls->shortcutSwitchMsxAudio  = "Impulsionar Botao cartucho MSX-AUDIO";
    ls->shortcutSwitchFront     = "Impulsionar Botao frontal Panasonic";
    ls->shortcutToggleMouseLock = "Activar/Desativar Bloqueio do Rato";
    ls->shortcutEmuSpeedMax     = "Velocidade Máxima da Emulação";
    ls->shortcutEmuSpeedNormal  = "Velocidade Normal da Emulação";
    ls->shortcutEmuSpeedInc     = "Aumentar Velocidade da Emulação";
    ls->shortcutEmuSpeedDec     = "Diminuir Velocidade da Emulação";
    ls->shortcutShowEmuProp     = "Mostre Propriedades da Emulation";
    ls->shortcutShowVideoProp   = "Mostre Propriedades Video";
    ls->shortcutShowAudioProp   = "Mostre Propriedades de Som";
    ls->shortcutShowCtrlProp    = "Mostre Propriedades dos Controles";
    ls->shortcutShowPerfProp    = "Mostre Propriedades Performance";
    ls->shortcutShowSettProp    = "Mostre Propriedades dos Ajustes";
    ls->shortcutShowLanguage    = "Mostre Diálogo da Língua";
    ls->shortcutShowMachines    = "Mostre Configuração da Máquina";
    ls->shortcutShowShortcuts   = "Mostre Configuração de Atalhos";
    ls->shortcutShowHelp        = "Ver Rubricas da Ajuda";
    ls->shortcutShowAbout       = "Ver Rubrica Sobre blueMSX";

    ls->shortcutSpecialMenu1    = "Mostre Menu Especial para Cartucho no Slot 1";
    ls->shortcutSpecialMenu2    = "Mostre Menu Especial para Cartucho no Slot 2";
    ls->shortcutVolumeStereo    = "Balança mono/estereo";
    ls->shortcutThemeSwitch     = "Comute o tema";
    ls->shortcutToggleSpriteEnable = "Mostrar/esconder os sprites";
    
    ls->shortcutShowApearProp   = "Show Appearance Properties";
    ls->menuPropsApearance      = "Appearance";
    ls->propApearance           = "Appearance";
    ls->propThemeGB             = "Tema ";
    ls->propTheme               = "Tema";
    ls->propThemeClassic        = "Clássico";
    ls->propThemeBlue           = "DIGIblue";

    ls->propMonBrightness       = "Brilho:";
    ls->propMonContrast         = "Contraste:";
    ls->propMonSaturation       = "Saturação:";
    ls->propMonGamma            = "Gamma:";
    ls->propMonScanlines        = "Scanlines:";

    ls->dlgRomType              = "Tipo rom:"; 
    ls->propOpenRomGB           = "Abrir arquivo rom"; 
    ls->propDefaultRomType      = "Tipo por defeito:"; 
    ls->propGuessRomType        = "Adivinhar tipo"; 

    ls->propFile                = "Arquivo"; 
    ls->propSettDefSlotGB       = "Deslizar e depositar "; 
    ls->propSettDefSlots        = "Inserir cartucho em:"; 
    ls->propSettDefSlot1        = " Slot 1"; 
    ls->propSettDefSlot2        = " Slot 2"; 
    ls->propSettDefDrives       = "Inserir disco em:"; 
    ls->propSettDefDriveA       = " Drive A"; 
    ls->propSettDefDriveB       = " Drive B"; 
    ls->menuPropsFile           = "Arquivo"; 
    ls->shortcutShowFiles       = "Mostre Propriedades de Arquivos";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "Inserir directório"; 
    ls->shortcutDiskDirInsertA  = "Inserir um directório como disco A"; 
    ls->shortcutDiskDirInsertB  = "Inserir um directório como disco B"; 
    ls->propMonDeInterlace      = " De-entrelace";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "Impulsionar Botao Pause"; 
    ls->shortcutSizeMinimized   = "Reduzir a Janela"; 
    ls->shortcutEmuSpeedToggle  = "Balança Velocidade Máxima da Emulação"; 
    ls->shortcutToggleCpuTrace  = "Activar/Desativar Traço da CPU"; 

    ls->enumVideoEmuMonitor     = "Monitor"; 

    ls->propEmuPauseSwitch      = " Botao Pause "; 
    ls->propVideoFreqText       = "Freqüência video:"; 
    ls->propVideoFreqAuto       = "Auto"; 
    ls->propSndOversampleText   = "Oversample:"; 

    ls->confChipExtras          = "Extras"; 
    ls->confBoardGB             = "Sistema "; 
    ls->confBoardText           = "Sistema tipo:"; 
    ls->dlgCpuFreqGB            = "Freqüência CPU "; 
    ls->dlgZ80FreqText          = "Freqüência Z80:"; 
    ls->dlgR800FreqText         = "Freqüência R800:"; 
    ls->dlgFdcGB                = "Controlador da Drive "; 
    ls->dlgCFdcNumDrivesText    = "Número das Drives:"; 

    ls->propPriorityBoost       = " Dar à blueMSX uma prioridade elevada";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "Não synchroniser disco drive"; 
    ls->shortcutToggleFdcTiming = "Synchroniser ou não disco drive"; 
    ls->propUseRegistry         = "Salvar a configuração no Registo";

    // New entries in 2.2
    ls->menuCartHBI55           = "Cartucho Sony HBI-55"; 
    ls->propSndPcm              = " Turbo-R PCM"; 
    ls->propSndAY8910           = " AY8910 PSG"; 
    ls->propSndSN76489          = " SN76489 PSG"; 
    ls->enumVideoEmuHq2x        = "Hq2x"; 
    ls->propMonColorGhosting    = "Modulador RF"; 

    ls->keyconfigSelectedKey    = "Tecla MSX seleccionada:"; 
    ls->keyconfigMappedTo       = "Atribuída à tecla PC :"; 
    ls->keyconfigMappingScheme  = "Configuração do teclado:"; 

    ls->discardChanges          = "Você quer desfazer as alterações da configuração atual?"; 
    ls->overwriteConfig         = "Você quer substituir esta configuração do teclado ?"; 

    ls->confSaveAsTitle         = "Salvar Como"; 
    ls->confSaveAsName          = "Nome:"; 

    ls->menuToolsKeyboard       = "Configuração do Teclado"; 
    ls->shortcutShowKeyboard    = "Mostre Configuração do Teclado"; 

    ls->menuVideoSource         = "Fonte Vídeo"; 
    ls->menuVideoSourceDefault  = "Nenhuma fonte vídeo"; 
    ls->menuVideoChipAutodetect = "Detecção automática"; 
    ls->propFullscreenResText   = "Resolução tela cheia:"; 
    ls->dlgSavePreview          = "Visualizar"; 
    ls->dlgSaveDate             = "Data:"; 

    ls->enumVideoMonAmber       = "Ambarino"; 

    ls->menuPropsPorts          = "Portas"; 
    ls->propPortsLptGB          = "Porta paralela "; 
    ls->propPortsComGB          = "Portas de série "; 
    ls->propPortsLptText        = "Porta:"; 
    ls->propPortsCom1Text       = "Porta 1:"; 
};

#endif

