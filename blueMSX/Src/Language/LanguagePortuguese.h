/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguagePortuguese.h,v $
**
** $Revision: 1.14 $
**
** $Date: 2005-09-04 04:25:24 $
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
    
    ls->menuCartInsert          = "Inserir Cartucho";
    ls->menuCartRemove          = "Remover Cartucho";
    ls->menuCartAutoReset       = "Reset ap�s inserir/remover";
    ls->menuCartNoRecentFiles   = "- Sem Arquivos Recentes -";
    ls->menuCartFMPac           = "Cartucho FM-PAC";
    ls->menuCartPac             = "Cartucho PAC";
    ls->menuCartSpecial         = "Especial";

    ls->menuDiskInsert          = "Inserir";
    ls->menuDiskEject           = "Ejetar";
    ls->menuDiskAutoStart       = "Reset ap�s inserir";
    ls->menuDiskNoRecentFiles   = "- Sem Arquivos Recentes -";
    
    ls->menuCasInsert           = "Inserir";
    ls->menuCasEject            = "Ejetar";
    ls->menuCasSetPosition      = "Ajustar Posi��o";
    ls->menuCasRewind           = "Rebobinar";
    ls->menuCasNoRecentFiles    = "- Sem Arquivos Recentes -";

    ls->menuZoomNormal          = "Tamanho Normal";
    ls->menuZoomDouble          = "Tamanho Duplo";
    ls->menuZoomFullscreen      = "Tela Cheia";
    
    ls->menuPropsEmulation      = "Emula��o";
    ls->menuPropsVideo          = "Video";
    ls->menuPropsSound          = "Som";
    ls->menuPropsControls       = "Controles";
    ls->menuPropsPerformance    = "Performance";
    ls->menuPropsLanguage       = "Linguagem";
    
    ls->menuHelpHelp            = "T�picos Ajuda";
    ls->menuHelpAbout           = "Sobre blueMSX";

    ls->menuFileCart1           = "Cartucho Slot 1";
    ls->menuFileCart2           = "Cartucho Slot 2";
    ls->menuFileDiskA           = "Disco drive A";
    ls->menuFileDiskB           = "Disco drive B";
    ls->menuFileCas             = "Cassette";
    ls->menuFileLoadState       = "Carregar Status da CPU";
    ls->menuFileSaveState       = "Salvar Status da CPU";
    ls->menuFileQLoadState      = "Carregar r�pido Status";
    ls->menuFileQSaveState      = "Salvar r�pido Status";
    ls->menuFileCaptureAudio    = "Capturar �udio";
    ls->menuFileScreenShot      = "Salvar Tela";
    ls->menuFileExit            = "Sair";

    ls->menuRunRun              = "Executar";
    ls->menuRunPause            = "Pausa";
    ls->menuRunStop             = "Parar";
    ls->menuRunSoftReset        = "Reset Completo";
    ls->menuRunHardReset        = "Reset Leve";
    ls->menuRunCleanReset       = "Reset Geral";

    ls->menuFile                = "Arquivo";
    ls->menuRun                 = "Execu��o";
    ls->menuWindow              = "Janela";
    ls->menuOptions             = "Op��es";
    ls->menuHelp                = "Ajuda";
    
    ls->errorTitle              = "blueMSX - Erro";
    ls->errorEnterFullscreen    = "Falha ao entrar em Tela Cheia.             \n";
    ls->errorDirectXFailed      = "Falha ao Criar Objetos DirectX.             \nUsando GDI ao inv�s.\nCheque as propriedades Video.";
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
    ls->tooltipCas              = "Insira Tape no Cassette Player";
    ls->tooltipStart            = "Iniciar emula��o";
    ls->tooltipResume           = "Continuar emula��o";
    ls->tooltipPause            = "Pausar emula��o";
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

    ls->dlgTapeTitle            = "blueMSX - Posi��o do Tape";
    ls->dlgTapeFrameText        = "Posi��o do Tape";
    ls->dlgTapeCurrentPos       = "Posi��o Atual";
    ls->dlgTapeTotalTime        = "Tempo Total";

    ls->dlgZipReset             = "Reset ap�s inserir";

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

    ls->dlgLangLangText         = "Escolha uma linguagem que blueMSX ir� usar";
    ls->dlgLangLangTitle        = "blueMSX - Linguagem";

    ls->propTitle               = "blueMSX - Propriedades";
    ls->propEmulation           = "Emula��o";
    ls->propVideo               = "Video";
    ls->propSound               = "Som";
    ls->propControls            = "Controles";
    ls->propPerformance         = "Performance";
    
    ls->propEmuGeneralGB        = "Geral ";
    ls->propEmuFamilyText       = "MSX :";
    ls->propEmuMemoryGB         = "Mem�ria ";
    ls->propEmuRamSizeText      = "Tamanho RAM :";
    ls->propEmuVramSizeText     = "Tamanho VRAM :";
    ls->propEmuSpeedGB          = "Velocidade da Emula��o ";
    ls->propEmuSpeedText        = "Velocidade da Emula��o:";

    ls->propMonMonGB            = "Monitor:";
    ls->propMonTypeText         = "Tipo de Monitor:";
    ls->propMonEmuText          = "Emulac�o de Monitor:";
    ls->propVideoYypeText       = "Tipo de Video:";
    ls->propWindowSizeText      = "Tamanho Janela:";

    ls->propPerfVideoDrvGB      = "Driver de Video:";
    ls->propPerfVideoDispDrvText= "Driver do Display:";
    ls->propPerfFrameSkipText   = "Frame skipping:";
    ls->propPerfAudioDrvGB      = "Driver de Audio:";
    ls->propPerfAudioDrvText    = "Driver de Som:";
    ls->propPerfAudioBufSzText  = "Tamanho buffer Som:";
    ls->propPerfEmuGB           = "Emula��o:";
    ls->propPerfSyncModeText    = "Modo Sincronismo:";

    ls->propSndChipEmuGB        = "Emula��o do Chip de Som";
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
    ls->enumEmuSyncAuto         = "Auto (R�pido)";

    ls->enumControlsJoyNone     = "Nenhum";
    ls->enumControlsJoyNumpad   = "Teclado Num�rico";
    ls->enumControlsJoyKeysetA  = "Teclas A";
    ls->enumControlsJoyKeysetB  = "Teclas B";
    ls->enumControlsJoyPCjoy1   = "PC joystick #1";
    ls->enumControlsJoyPCjoy2   = "PC joystick #2";
    ls->enumControlsJoyMouse    = "Mouse";

    ls->enumControlsAfOff       = "Desligado";
    ls->enumControlsAfSlow      = "Lento";
    ls->enumControlsAfMedium    = "Medio";
    ls->enumControlsAfFast      = "R�pido";

    ls->dlgAboutAbout           = "Sobre\r\n====";
    ls->dlgAboutVersion         = "Vers�o:";
    ls->dlgAboutBuildNumber     = "Compila��o:";
    ls->dlgAboutBuildDate       = "Data:";
    ls->dlgAboutDevel           = "Desenvolvido por Daniel Vik";
    ls->dlgAboutThanks          = "MUITO OBRIGADO PARA\r\n============";
    ls->dlgAboutLisence         = "LICEN�A\r\n"
                                  "======\r\n\r\n"
                                  "Este software � provido 'como-est�', sem Garantia expressa ou implicada."
                                  "Em Nenhuma circunstancia os autores ser�o responsaveis por qualquer "
                                  "Problema ou DANO proveniente do uso deste software.\r\n\r\n"
                                  "Visite www.bluemsx.com para mais detalhes.";


    
    ls->dlgAboutCreat           = "Criado Por Daniel Vik";
    ls->dlgAboutDevel           = "DESENVOLVEDORES\r\n========";

    // New entries
    ls->menuTools                = "Ferramentas";
    ls->menuToolsMachine         = "Configura��o da M�quina";
    ls->menuPropsSettings        = "Ajustes";
    ls->menuCasRewindAfterInsert = "Rebobinar Apos Inserir";
    ls->menuCasUseReadOnly       = "Usar Cassete Como Somente Leitura";
    ls->lmenuCasSaveAs           = "Salvar Imagem do Cassete Como...";

    ls->dlgSaveCassette          = "blueMSX - Salvar Imagem Tape";
    ls->dlgTapeCustom            = "Mostrar Arquivos Personalizados";
    ls->dlgTapeSetPosText        = "Posi��o do Cassete:";
    ls->dlgTabPosition           = "Posi��o";
    ls->dlgTabType               = "Tipo";
    ls->dlgTabFilename           = "Nome do Arquivo";

    ls->propSettings             = "Ajustes";
    
    ls->propSetFileHistoryGB     = "Hist�rico ";
    ls->propSetFileHistorySize   = "Numero de itens no Hist�rico:";
    ls->propSetFileHistoryClear  = "Limpar Hist�rico";
    ls->propSetScreenSaverGB     = "Prote��o de Tela";
    ls->propSetScreenSaver       = " Desabilitar Prote��o de Tela Quando blueMSX estiver ativo";

    ls->confTitle                = "blueMSX - Editor de Configura��o da Maquina";
    ls->confSave                 = "Salvar";
    ls->confSaveAs               = "Salvar Como";
    ls->confRun                  = "Executar";
    ls->confClose                = "Fechar";
    ls->confConfigText           = "Configura��o";
    ls->confSlotLayout           = "Slot Layout";
    ls->confMemory               = "Mem�ria";
    ls->confChipEmulation        = "Emula��o do Chip";

    ls->confSlotLayoutGB         = "Layout do Slot ";
    ls->confSlotExtSlotGB        = "Slots Externos";
    ls->confSlotSlot0            = "Slot 0";
    ls->confSlotSlot1            = "Slot 1";
    ls->confSlotSlot2            = "Slot 2";
    ls->confSlotSlot3            = "Slot 3";
    ls->confSlotCart1            = "Cartucho 1:";
    ls->confSlotCart2            = "Cartucho 2:";
    ls->confSlotPrimary          = "Prim�rio";
    ls->confSlotExpanded         = "Expandido (Quatro sub-slots)";

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

    ls->confSaveTitle            = "blueMSX - Salvar Configura��o";
    ls->confSaveText             = "Voc� quer substituir esta configura��o da m�quina? :";

    ls->slotEditMemTitle         = "blueMSX - Editar Mapper";
    ls->slotEditMemGB            = "Detalhes do Mapper ";
    ls->slotEditMemType          = "Tipo:";
    ls->slotEditMemFile          = "Arquivo:";
    ls->slotEditMemAddress       = "Endere�o";
    ls->slotEditMemSize          = "Tamanho";
    ls->slotEditMemSlot          = "Slot";

    ls->confDiscardTitle         = "blueMSX - Configura��o";
    ls->confExitSaveTitle        = "blueMSX - Sair do Editor de Configura��o";
    ls->confExitSaveText         = "Voce quer desfazer as altera��es da Configura��o atual ?";

    ls->confSaveAsMachineTitle   = "blueMSX - Salvar Configura��o da Maquina Como...";
    ls->confSaveAsMachineName    = "Nome da Maquina:";

    ls->confEditMemInternalRoms  = "blueMSX - Roms interno"; 


    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypesGB          = "Tipos de arquivo ";
    ls->propFileTypes            = " Associar certos tipos de arquivo com blueMSX";
    ls->propDisableWinKeys       = " Fun��o MSX autom�tica para as teclas Windows"; 
    ls->propWindowsEnvGB         = "Ambiente Windows";

    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW acel.";
    ls->enumVideoDrvDirectDrawHWSys = "DirectDraw mix."; 
    ls->propMonHorizStretch      = " Estiramento Horizontal"; 
    ls->propClearHistory         = "Deseja realmente limpar hist�rico ?";
    ls->propEmuFrontSwitchGB     = "Bot�o Panasonic "; 
    ls->propEmuFrontSwitch       = " Bot�o Frontal"; 
    ls->propEmuAudioSwitch       = " Bot�o Cartucho MSX-AUDIO"; 
    ls->propMonVertStretch       = " Estiramento Vertical"; 

    ls->dlgCmosGB                = "CMOS "; 
    ls->dlgCmosEnable            = " Ativar CMOS"; 
    ls->dlgCmosBattery           = " Utilizar uma Bateria Carregada";

    ls->menuCartSnatcher        = "Cartucho The Snatcher";
    ls->menuCartSdSnatcher      = "Cartucho SD-Snatcher";
    ls->menuCartSCCMirrored     = "Cartucho SCC Mirrored";
    ls->menuCartSCCExpanded     = "Cartucho SCC Expanded";
    ls->menuCartSCCPlus         = "Cartucho SCC+";
    ls->menuCartSCC             = "Cartucho SCC";
    
    ls->warningTitle             = "blueMSX - Advert�ncia";
    ls->tooltipStop              = "Parar emula��o";


    // New entries in 1.5.1
    ls->enumControlsJoyKeyset   = "Keyset";    
    ls->propJoyConfigKeyset     = "Configurar Keyset";
    ls->propJoyControlText      = "Controle:";
    ls->propJoyButtonText       = "Bot�o";
    ls->propJoyButtonAText      = "Bot�o A:";
    ls->propJoyButtonBText      = "Bot�o B:";

    ls->menuToolsShortcuts      = "Configura��o de Atalhos";

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
    ls->shortcutCartAutoReset   = "Reset ap�s inserir cartucho";
    ls->shortcutDiskInsertA     = "Inserir Disco no Drive A";
    ls->shortcutDiskRemoveA     = "Ejetar  Disco no Drive A ";
    ls->shortcutDiskChangeA     = "Alterar rapidamente Disco no Drive A";
    ls->shortcutDiskAutoResetA  = "Reset ap�s inserir Disco no Drive A ";
    ls->shortcutDiskInsertB     = "Insira Disco no Drive B";
    ls->shortcutDiskRemoveB     = "Ejetar Disco no Drive B";
    ls->shortcutCasInsert       = "Inserir Cassette";
    ls->shortcutCasEject        = "Ejetar Cassette";
    ls->shortcutCasAutorewind   = "Rebobina��o autom�tica ou n�o do cassete";
    ls->shortcutCasReadOnly     = "Cassete em modo leitura somente ou n�o";
    ls->shortcutCasSetPosition  = "Ajustar Posi��o";
    ls->shortcutCasRewind       = "Rebobinar Cassette";
    ls->shortcutCasSave         = "Salvar Imagem do Cassette Como...";
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
    ls->shortcutToggleFullscren = "Troca de modo Janela/Tela Cheia";
    ls->shortcutVolumeIncrease  = "Aumentar Volume sonoro";
    ls->shortcutVolumeDecrease  = "Diminuir Volume sonoro";
    ls->shortcutVolumeMute      = "Parar Som";
    ls->shortcutSwitchMsxAudio  = "Impulsionar Bot�o cartucho MSX-AUDIO";
    ls->shortcutSwitchFront     = "Impulsionar Bot�o frontal Panasonic";
    ls->shortcutToggleMouseLock = "Ativar/Desativar Bloqueio do Mouse";
    ls->shortcutEmuSpeedMax     = "Velocidade M�xima da Emula��o";
    ls->shortcutEmuSpeedNormal  = "Velocidade Normal da Emula��o";
    ls->shortcutEmuSpeedInc     = "Aumentar Velocidade da Emula��o";
    ls->shortcutEmuSpeedDec     = "Diminuir Velocidade da Emula��o";
    ls->shortcutShowEmuProp     = "Mostrar Propriedades da Emula��o";
    ls->shortcutShowVideoProp   = "Mostrar Propriedades Video";
    ls->shortcutShowAudioProp   = "Mostrar Propriedades de Som";
    ls->shortcutShowCtrlProp    = "Mostrar Propriedades dos Controles";
    ls->shortcutShowPerfProp    = "Mostrar Propriedades Performance";
    ls->shortcutShowSettProp    = "Mostrar Propriedades dos Ajustes";
    ls->shortcutShowLanguage    = "Mostrar Di�logo da L�ngua";
    ls->shortcutShowMachines    = "Mostrar Configura��o da M�quina";
    ls->shortcutShowShortcuts   = "Mostrar Configura��o de Atalhos";
    ls->shortcutShowHelp        = "Ver Rubricas da Ajuda";
    ls->shortcutShowAbout       = "Ver Rubrica Sobre blueMSX";

    ls->shortcutSpecialMenu1    = "Mostrar Menu Especial para Cartucho no Slot 1";
    ls->shortcutSpecialMenu2    = "Mostrar Menu Especial para Cartucho no Slot 2";
    ls->shortcutVolumeStereo    = "Troca Mono/Estereo";
    ls->shortcutThemeSwitch     = "Troque o tema";
    ls->shortcutToggleSpriteEnable = "Mostrar/esconder os sprites";
    
    ls->shortcutShowApearProp   = "Mostrar Propriedades";
    ls->menuPropsApearance      = "Apar�ncia";
    ls->propApearance           = "Apar�ncia";
    ls->propThemeGB             = "Tema ";
    ls->propTheme               = "Tema";
    ls->propThemeClassic        = "Cl�ssico";
    ls->propThemeBlue           = "DIGIblue";

    ls->propMonBrightness       = "Brilho:";
    ls->propMonContrast         = "Contraste:";
    ls->propMonSaturation       = "Satura��o:";
    ls->propMonGamma            = "Gama:";
    ls->propMonScanlines        = " Scanlines:";

    ls->dlgRomType              = "Tipo rom:"; 
    ls->propOpenRomGB           = "Abrir arquivo rom"; 
    ls->propDefaultRomType      = "Tipo de ROM Padr�o:"; 
    ls->propGuessRomType        = "Adivinhar tipo"; 

    ls->propFile                = "Arquivo"; 
    ls->propSettDefSlotGB       = "Deslizar e depositar "; 
    ls->propSettDefSlots        = "Inserir cartucho no:"; 
    ls->propSettDefSlot1        = " Slot 1"; 
    ls->propSettDefSlot2        = " Slot 2"; 
    ls->propSettDefDrives       = "Inserir disco no:"; 
    ls->propSettDefDriveA       = " Drive A"; 
    ls->propSettDefDriveB       = " Drive B"; 
    ls->menuPropsFile           = "Arquivo"; 
    ls->shortcutShowFiles       = "Mostrar Propriedades de Arquivos";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "Inserir diret�rio"; 
    ls->shortcutDiskDirInsertA  = "Inserir um diret�rio como disco A"; 
    ls->shortcutDiskDirInsertB  = "Inserir um diret�rio como disco B"; 
    ls->propMonDeInterlace      = " De-entrela�ar";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "Impulsionar Botao Pause"; 
    ls->shortcutSizeMinimized   = "Reduzir a Janela"; 
    ls->shortcutEmuSpeedToggle  = "Troca de Velocidade M�xima da Emula��o"; 
    ls->shortcutToggleCpuTrace  = "Ativar/Desativar Tra�o da CPU"; 

    ls->enumVideoEmuMonitor     = "Monitor"; 

    ls->propEmuPauseSwitch      = " Bot�o Pause "; 
    ls->propVideoFreqText       = "Freq��ncia video:"; 
    ls->propVideoFreqAuto       = "Auto"; 
    ls->propSndOversampleText   = "Oversample:"; 

    ls->confChipExtras          = "Extras"; 
    ls->confBoardGB             = "Sistema "; 
    ls->confBoardText           = "Sistema tipo:"; 
    ls->dlgCpuFreqGB            = "Freq��ncia CPU "; 
    ls->dlgZ80FreqText          = "Freq��ncia Z80:"; 
    ls->dlgR800FreqText         = "Freq��ncia R800:"; 
    ls->dlgFdcGB                = "Controlador do Drive "; 
    ls->dlgCFdcNumDrivesText    = "N�mero das Drives:"; 

    ls->propPriorityBoost       = " Dar ao blueMSX uma prioridade elevada";

    // New entries in 2.1
    ls->propEmuFdcTiming        = " N�o sincronizar disco do drive"; 
    ls->shortcutToggleFdcTiming = "sincronizar ou n�o disco drive"; 
    ls->propUseRegistry         = " Salvar a configura��o no Registro";

    // New entries in 2.2
    ls->menuCartHBI55           = "Cartucho Sony HBI-55"; 
    ls->propSndPcm              = " Turbo-R PCM"; 
    ls->propSndAY8910           = " AY8910 PSG"; 
    ls->propSndSN76489          = " SN76489 PSG"; 
    ls->enumVideoEmuHq2x        = "Hq2x"; 
    ls->propMonColorGhosting    = " Modulador RF"; 

    ls->keyconfigSelectedKey    = "Tecla MSX seleccionada:"; 
    ls->keyconfigMappedTo       = "Atribu�da � tecla PC :"; 
    ls->keyconfigMappingScheme  = "Configura��o do teclado:"; 

    ls->discardChanges          = "Voc� quer desfazer as altera��es da configura��o atual?"; 
    ls->overwriteConfig         = "Voc� quer substituir esta configura��o do teclado ?"; 

    ls->confSaveAsTitle         = "Salvar Como"; 
    ls->confSaveAsName          = "Nome:"; 

    ls->menuToolsKeyboard       = "Configura��o do Teclado"; 
    ls->shortcutShowKeyboard    = "Mostrar Configura��o do Teclado"; 

    ls->menuVideoSource         = "Fonte V�deo"; 
    ls->menuVideoSourceDefault  = "Nenhuma fonte v�deo"; 
    ls->menuVideoChipAutodetect = "Detec��o autom�tica"; 
    ls->propFullscreenResText   = "Resolu��o tela cheia:"; 
    ls->dlgSavePreview          = "Visualizar"; 
    ls->dlgSaveDate             = "Data:"; 

    ls->enumVideoMonAmber       = "�mbar"; 

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
    ls->propPortsFilenameText   = "Nome:"; 
    ls->propPortsEmulateMsxPrn  = "Emula��o:"; 

    ls->shortcutPrnFormFeed     = "Passagem para a p�gina seguinte"; 

    ls->menuPrnFormfeed         = "P�gina seguinte"; 
    ls->menuFilePrn             = "Impressora"; 
    ls->propPortsComFile        = "Enviar para arquivo";
};

#endif


