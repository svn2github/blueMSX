/*****************************************************************************

** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageJapanese.h,v $
**
** $Revision: 1.25 $
**
** $Date: 2006-06-04 19:23:17 $
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
#ifndef LANGUAGE_JAPANESE_H
#define LANGUAGE_JAPANESE_H

#include "LanguageStrings.h"

void langInitJapanese(LanguageStrings* ls) 
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

    ls->menuNoRecentFiles       = "- �g�p�t�@�C���Ȃ� -";
    ls->menuInsert              = "�}��";
    ls->menuEject               = "���o��";

    ls->menuCartAutoReset       = "�}��/���o���ナ�Z�b�g";
    ls->menuCartFMPac           = "FMPAC+�J�[�g���b�W";
    ls->menuCartPac             = "PAC+�J�[�g���b�W";
    
    ls->menuDiskAutoStart       = "�}��/���o���ナ�Z�b�g";
    
    ls->menuCasSetPosition      = "�e�[�v�ʒu�Z�b�g";
    ls->menuCasRewind           = "�����߂�";
    
    ls->menuZoomNormal          = "�W���T�C�Y";
    ls->menuZoomDouble          = "2�{�T�C�Y";
    ls->menuZoomFullscreen      = "�t���X�N���[��";
    

    ls->menuPropsEmulation      = "�G�~�����[�V����";
    ls->menuPropsVideo          = "�r�f�I";
    ls->menuPropsSound          = "�T�E���h";
    ls->menuPropsControls       = "�R���g���[��";
    ls->menuPropsPerformance    = "�p�t�H�[�}���X";
    ls->menuPropsLanguage       = "����";
    
    ls->menuHelpHelp            = "�w���v�ڎ�";
    ls->menuHelpAbout           = "blueMSX�ɂ���";

    ls->menuFileCart            = "ROM�X���b�g";
    ls->menuFileDisk            = "�f�B�X�N�h���C�u";
    ls->menuFileCas             = "�J�Z�b�g�e�[�v";
    ls->menuFileLoadState       = "CPU�X�e�[�g �ǂݍ���";
    ls->menuFileSaveState       = "CPU�X�e�[�g �ۑ�";
    ls->menuFileQLoadState      = "�N�C�b�N���[�h";
    ls->menuFileQSaveState      = "�N�C�b�N�Z�[�u";
    ls->menuFileCaptureAudio    = "�^��";
    ls->menuFileScreenShot      = "�X�N���[���V���b�g";
    ls->menuFileExit            = "�I��";

    ls->menuRunRun              = "���s";
    ls->menuRunPause            = "�ꎞ��~";
    ls->menuRunStop             = "��~";
    ls->menuRunSoftReset        = "�\\�t�g���Z�b�g";
    ls->menuRunHardReset        = "�n�[�h���Z�b�g";
    ls->menuRunCleanReset       = "�N���[�����Z�b�g";

    ls->menuFile                = "�t�@�C��";
    ls->menuRun                 = "���s";
    ls->menuWindow              = "�E�B���h�E";
    ls->menuOptions             = "�I�v�V����";

    ls->menuHelp                = "�w���v";
    

    ls->errorTitle              = "blueMSX �G���[";
    ls->errorEnterFullscreen    = "�t���X�N���[�����[�h�ɂł��܂���.           \n";
    ls->errorDirectXFailed      = "DirectX �I�u�W�F�N�g���쐬�ł��܂���.           \nGDI�����Ɏg�p���܂�.\n�O���t�B�b�N�J�[�h�̐ݒ���m�F���Ă�������.";

    ls->errorNoRomInZip         = "zip�t�@�C���̒���.rom�t�@�C����������܂���.";
    ls->errorNoDskInZip         = "zip�t�@�C���̒���.dsk�t�@�C����������܂���.";
    ls->errorNoCasInZip         = "zip�t�@�C���̒���.cas�t�@�C����������܂���.";

    ls->errorNoHelp             = "blueMSX�̃w���v�t�@�C����������܂���.";
    ls->errorStartEmu           = "MSX�G�~�����[�^�̊J�n�Ɏ��s���܂���.";


    ls->dlgLoadRom              = "blueMSX - rom�C���[�W��I��";
    ls->dlgLoadDsk              = "blueMSX - dsk�C���[�W��I��";
    ls->dlgLoadCas              = "blueMSX - cas�C���[�W��I��";
    ls->dlgLoadRomDskCas        = "blueMSX - rom, dsk, �܂���cas�C���[�W��I��";
    ls->dlgLoadRomDesc          = "�ǂݍ���rom�C���[�W:";
    ls->dlgLoadDskDesc          = "�ǂݍ���dsk�C���[�W:";
    ls->dlgLoadCasDesc          = "�ǂݍ���cas�C���[�W:";
    ls->dlgLoadRomDskCasDesc    = "�ǂݍ���rom, dsk, cas�C���[�W:";
    ls->dlgLoadState            = "CPU�X�e�[�g �ǂݍ���";
    ls->dlgSaveState            = "CPU�X�e�[�g �ۑ�";
    ls->dlgInsertRom1           = "ROM�J�[�g���b�W���X���b�g1�ɑ}��";
    ls->dlgInsertRom2           = "ROM�J�[�g���b�W���X���b�g2�ɑ}��";
    ls->dlgInsertDiskA          = "�f�B�X�N�C���[�W���h���C�uA�ɑ}��";
    ls->dlgInsertDiskB          = "�f�B�X�N�C���[�W���h���C�uB�ɑ}��";
    ls->dlgInsertCas            = "�J�Z�b�g�e�[�v��}��";

    ls->dlgOK                   = "OK";
    ls->dlgCancel               = "�L�����Z��";

    ls->dlgTapeTitle            = "blueMSX - �J�Z�b�g�e�[�v";
    ls->dlgTapeFrameText        = "�e�[�v�ʒu";
    ls->dlgTapeCurrentPos       = "���݈ʒu";
    ls->dlgTapeTotalTime        = "�g�[�^���^�C��";

    ls->dlgZipReset             = "�}���ナ�Z�b�g";

    ls->dlgAboutTitle           = "blueMSX�ɂ���";

    ls->dlgLangLangText         = "blueMSX�Ŏg�p���錾���I�����Ă�������";
    ls->dlgLangLangTitle        = "blueMSX - ����";

    ls->propTitle               = "blueMSX - �ݒ�";
    ls->propEmulation           = "�G�~�����[�V����";
    ls->propVideo               = "�r�f�I";
    ls->propSound               = "�T�E���h";
    ls->propControls            = "�R���g���[��";
    ls->propPerformance         = "�p�t�H�[�}���X";
    

    ls->propEmuGeneralGB        = "��� ";
    ls->propEmuFamilyText       = "MSX�̎��:";
    ls->propEmuMemoryGB         = "������ ";
    ls->propEmuRamSizeText      = "���C��RAM:";
    ls->propEmuVramSizeText     = "VRAM:";
    ls->propEmuSpeedGB          = "�X�s�[�h ";
    ls->propEmuSpeedText        = "�X�s�[�h:";

    ls->propMonMonGB            = "���j�^�[ ";
    ls->propMonTypeText         = "���j�^�[�̎��:";
    ls->propMonEmuText          = "���j�^�[�G�~�����[�V����:";
    ls->propVideoTypeText       = "�f������:";
    ls->propWindowSizeText      = "�E�B���h�E�T�C�Y:";

    ls->propPerfVideoDrvGB      = "�r�f�I�h���C�o ";
    ls->propPerfVideoDispDrvText= "�f�B�X�v���C�h���C�o:";
    ls->propPerfFrameSkipText   = "�t���[���X�L�b�v:";
    ls->propPerfAudioDrvGB      = "�T�E���h�h���C�o ";
    ls->propPerfAudioDrvText    = "�T�E���h�h���C�o:";
    ls->propPerfAudioBufSzText  = "�T�E���h�o�b�t�@:";
    ls->propPerfEmuGB           = "�G�~�����[�V���� ";
    ls->propPerfSyncModeText    = "SYNC���[�h:";

    ls->propSndChipEmuGB        = "�T�E���h�̃G�~�����[�V���� ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";

    ls->enumVideoMonColor       = "�J���[";
    ls->enumVideoMonGrey        = "���m�N��";
    ls->enumVideoMonGreen       = "�O���[��";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "�Ȃ�";
    ls->enumVideoEmuYc          = "Y/C�P�[�u�� (�N��)";
    ls->enumVideoEmuYcBlur      = "Y/C�P�[�u���{�m�C�Y (�N��)";
    ls->enumVideoEmuComp        = "�R���|�W�b�g (�s�N��)";
    ls->enumVideoEmuCompBlur    = "�R���|�W�b�g�{�m�C�Y (�s�N��)";
    ls->enumVideoEmuScale2x     = "Scale 2x";

    ls->enumVideoSize1x         = "�W���T�C�Y - 320x200";
    ls->enumVideoSize2x         = "2�{�T�C�Y - 640x400";
    ls->enumVideoSizeFullscreen = "�t���X�N���[��";

    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "�Ȃ�";
    ls->enumVideoFrameskip1     = "1�t���[��";
    ls->enumVideoFrameskip2     = "2�t���[��";
    ls->enumVideoFrameskip3     = "3�t���[��";
    ls->enumVideoFrameskip4     = "4�t���[��";
    ls->enumVideoFrameskip5     = "5�t���[��";

    ls->enumSoundDrvNone        = "�T�E���h�Ȃ�";
    ls->enumSoundDrvWMM         = "WMM�h���C�o";
    ls->enumSoundDrvDirectX     = "DirectX�h���C�o";

    ls->enumEmuSync1ms          = "1ms (���m)";
    ls->enumEmuSyncAuto         = "���� (����)";

    ls->enumControlsJoyNone     = "�Ȃ�";
    ls->enumControlsJoyMouse    = "�}�E�X";

    ls->dlgAboutAbout           = "���̃\\�t�g�ɂ���\r\n==========";
    ls->dlgAboutVersion         = "�o�[�W����:";
    ls->dlgAboutBuildNumber     = "�r���h:";
    ls->dlgAboutBuildDate       = "���t:";
    ls->dlgAboutCreat           = "���� Daniel Vik";
    ls->dlgAboutThanks          = "�����͂������������X\r\n============";
    ls->dlgAboutLisence         = "======\r\n\r\n"
                                  "���̃\\�t�g�E�F�A�͌�������̂܂܂̏�ԂŔz�z������̂ł���, �����I�܂���"
                                  "�َ��I���킸��؂̕ۏ؂͂���܂���. �܂����̃\\�t�g�E�F�A�̎g�p�̌��ʐ�����"
                                  "�����Ȃ鑹�Q�ɂ��Ă�, ��҂͐ӔC�𕉂��܂���.\r\n\r\n"
                                  "�ڂ��������ɂ��Ă�, www.bluemsx.com ��������������. ";
    
    ls->dlgAboutDevel           = "�J����\r\n========";

    // New entries
    ls->menuTools                = "�c�[��";
    ls->menuToolsMachine         = "�}�V���\\���ҏW";
    ls->menuPropsSettings        = "���̑�";
    ls->menuCasRewindAfterInsert = "�}���㊪���߂�";
    ls->menuCasUseReadOnly       = "�e�[�v��ǂݍ��ݐ�p�ɂ���";
    ls->lmenuCasSaveAs           = "�e�[�v��ʖ��ŕۑ�...";

    ls->dlgSaveCassette          = "blueMSX - �e�[�v��ۑ�";
    ls->dlgTapeCustom            = "�J�X�^���t�@�C����\\��";
    ls->dlgTapeSetPosText        = "�e�[�v�ʒu:";
    ls->dlgTabPosition           = "�ʒu";
    ls->dlgTabType               = "�^�C�v";
    ls->dlgTabFilename           = "�t�@�C����";

    ls->propSettings             = "���̑�";
    
    ls->propSetFileHistoryGB     = "�t�@�C���q�X�g�� ";
    ls->propSetFileHistorySize   = "�t�@�C���q�X�g���̌�:";
    ls->propSetFileHistoryClear  = "�q�X�g���̏���";
    ls->propSetScreenSaver       = " blueMSX�̓��쒆�̓X�N���[���Z�[�o�𖳌��ɂ���";

    ls->confTitle                = "blueMSX - �}�V���\\���ҏW";
    ls->dlgSave                 = "�ۑ�";
    ls->dlgSaveAs               = "�ʖ��ۑ�...";
    ls->dlgRun                  = "�N��";
    ls->dlgClose                = "����";
    ls->confConfigText           = "�}�V���\\��";
    ls->confSlotLayout           = "�X���b�g�\\��";
    ls->confMemory               = "������";
    ls->confChipEmulation        = "�`�b�v";

    ls->confSlotLayoutGB         = "�X���b�g�\\�� ";
    ls->confSlotExtSlotGB        = "�g���X���b�g ";
    ls->confSlotCart             = "�J�[�g���b�W";
    ls->confSlotPrimary          = "��{";
    ls->confSlotExpanded         = "�g�� (4�̕��X���b�g)";

    ls->confMemAdd               = "�ǉ�...";
    ls->confMemEdit              = "�ҏW...";
    ls->confMemRemove            = "�폜";
    ls->confMemSlot              = "�X���b�g";
    ls->confMemAddresss          = "�A�h���X";
    ls->confMemType              = "�^�C�v";
    ls->confMemRomImage          = "����";
    
    ls->confChipVideoGB          = "�r�f�I ";
    ls->confChipVideoChip        = "�r�f�I�`�b�v:";
    ls->confChipVideoRam         = "�r�f�IRAM:";
    ls->confChipSoundGB          = "�T�E���h ";

    ls->confEditMemTitle         = "blueMSX - �}�b�p�̕ҏW";
    ls->confEditMemGB            = "�}�b�p�̏ڍ� ";
    ls->confEditMemType          = "�^�C�v:";
    ls->confEditMemFile          = "�t�@�C��:";
    ls->confEditMemAddress       = "�A�h���X:";
    ls->confEditMemSize          = "�T�C�Y:";
    ls->confEditMemSlot          = "�X���b�g:";

    ls->confSaveAsTitle          = "blueMSX - �}�V���\\����ʖ��ŕۑ�...";
    ls->confSaveAsMachineName    = "�\\����:";

    ls->confSaveTitle            = "blueMSX - �}�V���\\���̕ۑ�";
    ls->confSaveText             = "�}�V���\\�����㏑�����Ă�낵���ł���?";

    ls->dlgOpen                  = "�J��";

    ls->confSaveTitle            = "blueMSX - �}�V���\\���ҏW�̏I��";
    ls->confSaveText             = "���݂̍\\���������܂����A��낵���ł���?";
    
    ls->confExitSaveTitle        = "blueMSX - �}�V���\\���ҏW�̏I��";
    ls->confExitSaveText         = "���݂̍\\���������܂����A��낵���ł���?";

    ls->confDiscardTitle         = "blueMSX - �}�V���\\���ҏW";
    
    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypes            = " blueMSX�Ɋ֘A�t����t�@�C����� (.rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " blueMSX���g�p���ɍ��E��Windows�L�[�𖳌�������"; 
    ls->propWindowsEnvGB         = "�E�B���h�E�Y�� ";
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW accel."; 
    ls->propMonHorizStretch      = " ���� �X�g���b�`";  
    ls->propClearHistory         = "�q�X�g���̏��������s���āA��낵���ł���?"; 

    ls->propEmuFrontSwitchGB     = "�p�i�\\�j�b�N�X�C�b�` "; 
    ls->propEmuFrontSwitch       = " �O�ʃX�C�b�`"; 
    ls->propEmuAudioSwitch       = " MSX-AUDIO �J�[�g���b�W �X�C�b�`"; 
    ls->propMonVertStretch       = " ���� �X�g���b�`";

    ls->confCmosGB                = "CMOS "; 
    ls->confCmosEnable            = " CMOS��L��"; 
    ls->confCmosBattery           = " �����o�b�e���[��L����";
     
    ls->menuCartSCCPlus          = "SCC+  �J�[�g���b�W";
    ls->menuCartSCC              = "SCC  �J�[�g���b�W";
    
    ls->warningTitle             = "blueMSX - Warning";

    // New entries in 1.5.1
    ls->menuToolsShortcuts      = "�V���[�g�J�b�g�\\���ҏW";

    ls->shortcutSaveConfig      = "blueMSX - �\\���̕ۑ�";
    ls->shortcutOverwriteConfig = "�V���[�g�J�b�g�\\�����㏑�����Ă�낵���ł���?:";
    ls->shortcutExitConfig      = "blueMSX - �V���[�g�J�b�g�\\���ҏW�̏I��";
    ls->shortcutDiscardConfig   = "���݂̍\\���������܂����A��낵���ł���?";
    ls->shortcutSaveConfigAs    = "blueMSX - �V���[�g�J�b�g�\\����ʖ��ŕۑ�...";
    ls->shortcutConfigName      = "�\\����:";
    ls->shortcutNewProfile      = "< �V�K �v���t�@�C�� >";
    ls->shortcutConfigTitle     = "blueMSX - �V���[�g�J�b�g �\\���ҏW";
    ls->shortcutAssign          = "���蓖��";
    ls->shortcutPressText       = "�V���[�g�J�b�g�L�[���͗�:";
    ls->shortcutScheme          = "�}�b�s���O�X�L�[��:";

    ls->shortcutCartInsert1     = "�J�[�g���b�W1 �}��";
    ls->shortcutCartRemove1     = "�J�[�g���b�W1 ���o��";
    ls->shortcutCartInsert2     = "�J�[�g���b�W2 �}��";
    ls->shortcutCartRemove2     = "�J�[�g���b�W2 ���o��";
    ls->shortcutCartAutoReset   = "�J�[�g���b�W �}��/���o���ナ�Z�b�g";
    ls->shortcutDiskInsertA     = "�f�B�X�NA �}��";
    ls->shortcutDiskRemoveA     = "�f�B�X�NA ���o��";
    ls->shortcutDiskChangeA     = "�f�B�X�NA ����ւ�(v-DRIVE)";
    ls->shortcutDiskAutoResetA  = "�f�B�X�NA �}��/���o���ナ�Z�b�g";
    ls->shortcutDiskInsertB     = "�f�B�X�NB �}��";
    ls->shortcutDiskRemoveB     = "�f�B�X�NB ���o��";
    ls->shortcutCasInsert       = "�e�[�v �}��";
    ls->shortcutCasEject        = "�e�[�v ���o��";
    ls->shortcutCasAutorewind   = "�e�[�v �}���㊪���߂�";
    ls->shortcutCasReadOnly     = "�e�[�v��ǂݍ��ݐ�p�ɂ���";
    ls->shortcutCasSetPosition  = "�e�[�v�ʒu�Z�b�g";
    ls->shortcutCasRewind       = "�e�[�v�����߂�";
    ls->shortcutCasSave         = "�e�[�v�C���[�W �ۑ�";
    ls->shortcutCpuStateLoad    = "CPU�X�e�[�g�ǂݍ���";
    ls->shortcutCpuStateSave    = "CPU�X�e�[�g�ۑ�";
    ls->shortcutCpuStateQload   = "�N�C�b�N���[�h";
    ls->shortcutCpuStateQsave   = "�N���b�N�Z�[�u";
    ls->shortcutAudioCapture    = "�T�E���h�^���̎��s/��~";
    ls->shortcutScreenshotOrig  = "�X�N���[���V���b�g";
    ls->shortcutScreenshotSmall = "���t�B���^�[�W���T�C�Y �X�N���[���V���b�g";
    ls->shortcutScreenshotLarge = "���t�B���^�[2�{�T�C�Y �X�N���[���V���b�g";
    ls->shortcutQuit            = "blueMSX���I������";
    ls->shortcutRunPause        = "�G�~�����[�V�����̎��s/�|�[�Y";
    ls->shortcutStop            = "��~";
    ls->shortcutResetHard       = "�n�[�h���Z�b�g";
    ls->shortcutResetSoft       = "�\\�t�g���Z�b�g";
    ls->shortcutResetClean      = "�N���[�����Z�b�g";
    ls->shortcutSizeSmall       = "�W���T�C�Y";
    ls->shortcutSizeNormal      = "2�{�T�C�Y";
    ls->shortcutSizeFullscreen  = "�t���X�N���[��";
    ls->shortcutToggleFullscren = "�t���X�N���[����";
    ls->shortcutVolumeIncrease  = "�{�����[�����グ��";
    ls->shortcutVolumeDecrease  = "�{�����[����������";
    ls->shortcutVolumeMute      = "�~���[�g";
    ls->shortcutSwitchMsxAudio  = "MSX-AUDIO�J�[�g���b�W�X�C�b�`";
    ls->shortcutSwitchFront     = "�O�ʃX�C�b�`";
    ls->shortcutToggleMouseLock = "�}�E�X���b�N";
    ls->shortcutEmuSpeedMax     = "�G�~�����[�V�������s���x���ő���";
    ls->shortcutEmuSpeedNormal  = "�G�~�����[�V�������s���x��W����";
    ls->shortcutEmuSpeedInc     = "�G�~�����[�V�������x������";
    ls->shortcutEmuSpeedDec     = "�G�~�����[�V�������x�̌���";
    ls->shortcutShowEmuProp     = "�G�~�����[�V�����ݒ��ʂ̕\\��";
    ls->shortcutShowVideoProp   = "�r�f�I�ݒ��ʂ̕\\��";
    ls->shortcutShowAudioProp   = "�T�E���h�ݒ��ʂ̕\\��";
    ls->shortcutShowCtrlProp    = "�R���g���[���ݒ��ʂ̕\\��";
    ls->shortcutShowPerfProp    = "�p�t�H�[�}���X�ݒ��ʂ̕\\��";
    ls->shortcutShowSettProp    = "���̑��ݒ��ʂ̕\\��";
    ls->shortcutShowLanguage    = "����_�C�A���O�̕\\��";
    ls->shortcutShowMachines    = "�}�V���\\���ҏW�̕\\��";
    ls->shortcutShowShortcuts   = "�V���[�g�J�b�g�G�f�B�^�[�̕\\��";
    ls->shortcutShowHelp        = "�w���v�_�C�A���O�̕\\��";
    ls->shortcutShowAbout       = "blueMSX�ɂ��Ă̕\\��";

    ls->shortcutSpecialMenu1    = "�J�[�g���b�W1�̂��̑����j���[�̕\\��";
    ls->shortcutSpecialMenu2    = "�J�[�g���b�W2�̂��̑����j���[�̕\\��";
    ls->shortcutVolumeStereo    = "���m/�X�e���I�̐؂�ւ�";
    ls->shortcutThemeSwitch     = "�e�[�}�̐؂�ւ�";
    ls->shortcutToggleSpriteEnable = "�X�v���C�g�̕\\��/����";

    ls->propThemeGB             = "�e�[�} ";
    ls->propTheme               = "�e�[�}";

    ls->propMonBrightness       = "���邳:";
    ls->propMonContrast         = "�R���g���X�g:";
    ls->propMonSaturation       = "�ʓx:";
    ls->propMonGamma            = "�K���}:";
    ls->propMonScanlines        = "�X�L�������C��:";
    ls->dlgRomType              = "�������:"; 
    ls->propOpenRomGB           = "�����_�C�A���O���J��"; 
    ls->propDefaultRomType      = "�W�������^�C�v:"; 
    ls->propGuessRomType        = "������ނ𐄑�";

    ls->propFile                = "�t�@�C��"; 
    ls->propSettDefSlotGB       = "�h���b�O���h���b�v "; 
    ls->propSettDefSlots        = "������}������X���b�g:"; 
    ls->propSettDefSlot         = " �X���b�g"; 
    ls->propSettDefDrives       = "�f�B�X�N��}������h���C�u:"; 
    ls->propSettDefDrive        = " �h���C�u"; 
    ls->menuPropsFile           = "�t�@�C��";
    ls->shortcutShowFiles       = "�t�@�C���_�C�A���O��\\��";

    // New entries in 1.6.1 
    ls->menuDiskDirInsert       = "�f�B���N�g���}��"; 
    ls->shortcutDiskDirInsertA  = "�f�B���N�g�����f�B�X�NA�Ƃ��đ}��"; 
    ls->shortcutDiskDirInsertB  = "�f�B���N�g�����f�B�X�NB�Ƃ��đ}��";
    ls->propMonDeInterlace      = " �f�C���^�[���[�X";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "�p�i�\\�j�b�N�n �|�[�Y�X�C�b�`";
    ls->shortcutSizeMinimized   = "�E�B���h�E �ŏ���";
    ls->shortcutEmuSpeedToggle  = "�ő�����̗L��";
    ls->shortcutToggleCpuTrace  = "CPU�g���[�X�̗L��";

    ls->enumVideoEmuMonitor     = "���j�^�[";

    ls->propEmuPauseSwitch      = " �|�[�Y �X�C�b�`";
    ls->propVideoFreqText       = "�r�f�I ���g��:";
    ls->propVideoFreqAuto       = "����";
    ls->propSndOversampleText   = "�T���v�����O:";

    ls->confChipExtras          = "�G�L�X�g��";
    ls->confBoardGB             = "��� ";
    ls->confBoardText           = "��� �^�C�v:";
    ls->confCpuFreqGB            = "CPU ���g�� ";
    ls->confZ80FreqText          = "Z80 ���g��:";
    ls->confR800FreqText         = "R800 ���g��:";
    ls->confFdcGB                = "�t���b�s�[�f�B�X�N�R���g���[���[ ";
    ls->confCFdcNumDrivesText    = "�h���C�u�̐�:";

    ls->propPriorityBoost        = " blueMSX�Ɋ����Ă�v���C�I���e�B�[�̃u�[�X�g";

    // New entries in 2.0.1
    ls->propEmuFdcTiming        = "FDD�h���C�u�̃^�C�~���O�𖳌���";
    ls->shortcutToggleFdcTiming = "FDD�h���C�u�̃^�C�~���O �L��";

    // New entries in 2.2
    ls->menuCartHBI55           = "Sony HBI-55 �J�[�g���b�W";
    ls->enumVideoEmuHq2x        = "Hq2x";
    ls->propMonColorGhosting    = "RF���W�����[�^";

    ls->keyconfigSelectedKey    = "�I���L�[:";
    ls->keyconfigMappedTo       = "�ΏۃL�[:";
    ls->keyconfigMappingScheme  = "�}�b�s���O�X�L�[��:";

    ls->warningDiscardChanges   = "�\\���������܂����A��낵���ł���?";

    ls->confSaveAsTitle         = "�ʖ��ŕۑ�...";

    ls->menuToolsKeyboard       = "�L�[�{�[�h�\\���ҏW";
    ls->shortcutShowKeyboard    = "�L�[�{�[�h�\\���ҏW�̕\\��";

    ls->menuVideoSource         = "�r�f�I�\\�[�X";
    ls->menuVideoSourceDefault  = "�r�f�I�\\�[�X�̐ڑ�������܂���";
    ls->menuVideoChipAutodetect = "�q�f�I�`�b�v�̎����F��";
    ls->propFullscreenResText   = "�t���X�N���[���̉𑜓x:";
    ls->dlgSavePreview          = "�v���r���[�\\��";
    ls->dlgSaveDate             = "�Z�[�u����:";
    
    ls->enumVideoMonAmber       = "�A���o�[";

    ls->menuPropsPorts          = "�|�[�g";
    ls->propPortsLptGB          = "�p�������|�[�g ";
    ls->propPortsComGB          = "�V���A���|�[�g ";
    ls->propPortsLptText        = "�|�[�g:";
    ls->propPortsCom1Text       = "�|�[�g 1:";

	ls->shortcutShowDebugger    = "�f�o�b�K�[�\\��";
    ls->shortcutShowTrainer     = "�g���[�i�[�\\��";
    ls->shortcutShowPorts       = "�|�[�g�\\���ݒ�̕\\��";
    
    ls->propPorts               = "�|�[�g";
    ls->propPortsNone           = "�Ȃ�";

    // New entries in 2.3
    ls->enumControlsJoyTetris2Dongle = "Tetris 2 Dongle";

    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "Print to File";
    ls->propPortsOpenLogFile    = "Open Log File";
    ls->propPortsEmulateMsxPrn  = "Emulation:";

    ls->shortcutPrnFormFeed     = "Printer Form Feed";

    ls->menuPrnFormfeed         = "Form Feed";
    ls->menuFilePrn             = "Printer";
    ls->propPortsComFile        = "Send to File";

    // New entries in 2.3 
    ls->enumControlsJoyTetris2Dongle = "�e�g���X 2 �h���O��"; 

    ls->propPortsSimplCovox     = "SiMPL / Covox DAC"; 
    ls->propPortsFile           = "�t�@�C���փv�����g"; 
    ls->propPortsOpenLogFile    = "���O�t�@�C�����J��"; 
    ls->propPortsEmulateMsxPrn  = "�G�~�����[�V����:"; 

    ls->shortcutPrnFormFeed     = "�t�H�[���t�B�[�h"; 

    ls->menuPrnFormfeed         = "�t�H�[���t�B�[�h"; 
    ls->menuFilePrn             = "�v�����^�["; 
    ls->propPortsComFile        = "�t�@�C���֑���"; 


        // New entries in 2.4 
    ls->shortcutShowMixer       = "�~�L�T�[�̕\\��"; 
    ls->menuToolsMixer          = "�~�L�T�["; 
    
    ls->propSndMidiInGB         = "MIDI �C�� "; 
    ls->propSndMidiOutGB        = "MIDI �A�E�g "; 
    ls->propSndMt32ToGm         = " MT-32 �y����W�F�l����MIDI�Ƀ}�b�s���O"; 

    ls->textDevice              = "�f�o�C�X:"; 
    ls->textFilename            = "�t�@�C����:"; 
    ls->textFile                = "�t�@�C��"; 
    ls->textNone                = "����"; 

    ls->enumEmuSyncNone         = "����"; 
    ls->enumEmuSyncAuto         = "�I�[�g (����)"; 
    ls->enumEmuSync1ms          = "MSX�̑��x�ɓ���"; 
    ls->enumEmuSyncVblank       = "PC�̏������ɓ���"; 

    ls->propMonEffectsGB        = "�G�t�F�N�g "; 
    
    ls->confSlot                = "�X���b�g"; 
    ls->confSubslot             = "�T�u�X���b�g"; 

    ls->shortcutDescription     = "�V���[�g�J�b�g"; 
    ls->shortcutKey             = "�z�b�g�L�["; 
    ls->fileRom                 = "���� �C���[�W"; 
    ls->confOpenRom             = "���� �C���[�W���J��"; 
    ls->fileAll                 = "�S�Ẵt�@�C��"; 
    ls->fileCpuState            = "CPU �X�e�[�g"; 
    ls->fileDisk                = "�f�B�X�N �C���[�W"; 
    ls->fileCas                 = "�e�[�v �C���[�W"; 

    ls->menuCartExternalRam     = "�O�� ����"; 

};


#endif

