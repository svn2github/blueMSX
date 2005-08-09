/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageChineseTraditional.h,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-08-09 08:37:20 $
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
#ifndef LANGUAGE_CHINESE_TRADITIONAL_H
#define LANGUAGE_CHINESE_TRADITIONAL_H

#include "LanguageStrings.h"
 
void langInitChineseTraditional(LanguageStrings* ls) 
{
    ls->statusBarStopped        = "  �w����";
    ls->statusBarPaused         = "  �Ȱ�";
    ls->statusBarRunning        = "  ���椤";
    
    ls->menuHardReset           = "�w�魫�m";
    ls->menuSoftReset           = "�n�魫�m";
    
    ls->menuCartInsert          = "���J";
    ls->menuCartRemove          = "����";
    ls->menuCartAutoReset       = "���J/�������᭫�m";
    ls->menuCartNoRecentFiles   = "- �S���̪��ɮ� -";
    ls->menuCartFMPac           = "FM-PAC �d�X";
    ls->menuCartPac             = "PAC �d�X";
    ls->menuCartSpecial         = "�S��";

    ls->menuDiskInsert          = "���J";
    ls->menuDiskEject           = "�h�X";
    ls->menuDiskAutoStart       = "���J���᭫�m";
    ls->menuDiskNoRecentFiles   = "- �S���̪��ɮ� -";
    
    ls->menuCasInsert           = "���J";
    ls->menuCasEject            = "�h�X";
    ls->menuCasSetPosition      = "�]�w��m";
    ls->menuCasRewind           = "�j�a";
    ls->menuCasNoRecentFiles    = "- �S���̪��ɮ� -";

    ls->menuZoomNormal          = "�@��j�p";
    ls->menuZoomDouble          = "�⭿�j�p";
    ls->menuZoomFullscreen      = "���ù�";
    
    ls->menuPropsEmulation      = "����";
    ls->menuPropsVideo          = "���T";
    ls->menuPropsSound          = "����";
    ls->menuPropsControls       = "���";
    ls->menuPropsPerformance    = "�į�";
    ls->menuPropsLanguage       = "�y��";
    
    ls->menuHelpHelp            = "�����D�D";
    ls->menuHelpAbout           = "���� blueMSX";

    ls->menuFileCart1           = "�d�X���� 1";
    ls->menuFileCart2           = "�d�X���� 2";
    ls->menuFileDiskA           = "�Ϻо� A";
    ls->menuFileDiskB           = "�Ϻо� B";
    ls->menuFileCas             = "�ϱa��";
    ls->menuFileLoadState       = "���J CPU ���A";
    ls->menuFileSaveState       = "�x�s CPU ���A";
    ls->menuFileQLoadState      = "�ֳt���J���A";
    ls->menuFileQSaveState      = "�ֳt�x�s���A";
    ls->menuFileCaptureAudio    = "�^�����T";
    ls->menuFileScreenShot      = "�x�s�ù����";
    ls->menuFileExit            = "����";

    ls->menuRunRun              = "����";
    ls->menuRunPause            = "�Ȱ�";
    ls->menuRunStop             = "����";
    ls->menuRunSoftReset        = "�n�魫�m";
    ls->menuRunHardReset        = "�w�魫�m";
    ls->menuRunCleanReset       = "�@�뭫�m";

    ls->menuFile                = "�ɮ�";
    ls->menuRun                 = "����";
    ls->menuWindow              = "����";
    ls->menuOptions             = "�ﶵ";
    ls->menuHelp                = "����";
    
    ls->errorTitle              = "blueMSX - ���~";
    ls->errorEnterFullscreen    = "�L�k�i�J���ù��Ҧ��C           \n";
    ls->errorDirectXFailed      = "�L�k�إ� DirectX ����C           \n���N���ϥ� GDI�C\n���ˬd���T���e�C";
    ls->errorNoRomInZip         = "�L�k�b zip ���Y�ɮפ���X .rom �ɮסC";
    ls->errorNoDskInZip         = "�L�k�b zip ���Y�ɮפ���X .dsk �ɮסC";
    ls->errorNoCasInZip         = "�L�k�b zip ���Y�ɮפ���X .cas �ɮסC";
    ls->errorNoHelp             = "�L�k��� blueMSX �����ɮסC";
    ls->errorStartEmu           = "�L�k�Ұ� MSX �������C";

    ls->tooltipReset            = "���m MSX";
    ls->tooltipCart1            = "�Цb���� 1 ���J�d�X";
    ls->tooltipCart2            = "�Цb���� 2 ���J�d�X";
    ls->tooltipDiskA            = "�Цb�Ϻо� A ���J�Ϻ�";
    ls->tooltipDiskB            = "�Цb�Ϻо� B ���J�Ϻ�";
    ls->tooltipCas              = "�Цb�ϱa�����J�ϱa";
    ls->tooltipStart            = "�}�l����";
    ls->tooltipResume           = "�~�����";
    ls->tooltipPause            = "�Ȱ�����";
    ls->tooltipWindowSize       = "�]�w�����j�p";
    ls->tooltipProperties       = "�}�Ҥ��e��ܤ��";
    ls->tooltipHelp             = "�}�һ�������";

    ls->dlgMainWindow           = "  blueMSX";
    ls->dlgLoadRom              = "blueMSX - ��ܥd�X�M���ɸ��J";
    ls->dlgLoadDsk              = "blueMSX - ��ܺϺЬM���ɸ��J";
    ls->dlgLoadCas              = "blueMSX - ��ܺϱa�M���ɸ��J";
    ls->dlgLoadRomDskCas        = "blueMSX - ��ܥd�X�B�ϺЩκϱa�M���ɸ��J";
    ls->dlgLoadRomDesc          = "�п�ܭn���J���d�X�M����:";
    ls->dlgLoadDskDesc          = "�п�ܭn���J���ϺЬM����:";
    ls->dlgLoadCasDesc          = "�п�ܭn���J���ϱa�M����:";
    ls->dlgLoadRomDskCasDesc    = "�п�ܭn���J���d�X�B�ϺЩκϱa�M����:";
    ls->dlgLoadState            = "���J CPU ���A";
    ls->dlgSaveState            = "�x�s CPU ���A";
    ls->dlgInsertRom1           = "�Цb���� 1 ���J ROM �d�X";
    ls->dlgInsertRom2           = "�Цb���� 2 ���J ROM �d�X";
    ls->dlgInsertDiskA          = "�Цb�Ϻо� A ���J�ϺЬM����";
    ls->dlgInsertDiskB          = "�Цb�Ϻо� B ���J�ϺЬM����";
    ls->dlgInsertCas            = "�д��J�ϱa���ϱa";

    ls->dlgOK                   = "�T�w";
    ls->dlgOpen                 = "�}��";
    ls->dlgCancel               = "����";

    ls->dlgTapeTitle            = "blueMSX - �ϱa��m";
    ls->dlgTapeFrameText        = "�ϱa��m";
    ls->dlgTapeCurrentPos       = "�ثe����m";
    ls->dlgTapeTotalTime        = "�`�ɶ�";

    ls->dlgZipReset             = "���J���᭫�m";

    ls->dlgAboutTitle           = "blueMSX - ����";

    ls->dlgJoyTitle1            = "blueMSX - �n�� A ����]�w";
    ls->dlgJoyTitle2            = "blueMSX - �n�� B ����]�w";
    ls->dlgJoyUpText            = "�W";
    ls->dlgJoyDownText          = "�U";
    ls->dlgJoyLeftText          = "��";
    ls->dlgJoyRightText         = "�k";
    ls->dlgJoyButton1Text       = "���s 1";
    ls->dlgJoyButton2Text       = "���s 2";
    ls->dlgJoyGB                = "����]�w ";

    ls->dlgLangLangText         = "�п�� blueMSX �n�ϥΪ��y��";
    ls->dlgLangLangTitle        = "blueMSX - �y��";

    ls->propTitle               = "blueMSX - ���e";
    ls->propEmulation           = "����";
    ls->propVideo               = "���T";
    ls->propSound               = "����";
    ls->propControls            = "���";
    ls->propPerformance         = "�į�";
    
    ls->propEmuGeneralGB        = "�@�� ";
    ls->propEmuFamilyText       = "MSX ����:";
    ls->propEmuMemoryGB         = "�O���� ";
    ls->propEmuRamSizeText      = "RAM �j�p:";
    ls->propEmuVramSizeText     = "VRAM �j�p:";
    ls->propEmuSpeedGB          = "�����t�� ";
    ls->propEmuSpeedText        = "�����t��:";

    ls->propMonMonGB            = "�ʵ��� ";
    ls->propMonTypeText         = "�ʵ�������:";
    ls->propMonEmuText          = "�ʵ�������:";
    ls->propVideoYypeText       = "���T����:";
    ls->propWindowSizeText      = "�����j�p:";

    ls->propPerfVideoDrvGB      = "���T�X�ʵ{�� ";
    ls->propPerfVideoDispDrvText= "����X�ʵ{��:";
    ls->propPerfFrameSkipText   = "�e�沤�L:";
    ls->propPerfAudioDrvGB      = "���T�X�ʵ{�� ";
    ls->propPerfAudioDrvText    = "�����X�ʵ{��:";
    ls->propPerfAudioBufSzText  = "���Ľw�İϤj�p:";
    ls->propPerfEmuGB           = "���� ";
    ls->propPerfSyncModeText    = "�P�B�Ҧ�:";

    ls->propSndChipEmuGB        = "���Ĵ������� ";
    ls->propSndMixerGB          = "���ĲV�X�� ";
    ls->propSndMonoText         = "�歵";
    ls->propSndStereoText       = "�����n";
    ls->propSndMsxMusicText     = " MSX ����";
    ls->propSndMsxAudioText     = " MSX ����";
    ls->propSndMsxMasterText    = "�D�n";

    ls->propJoyPort1GB          = "�s���� #1 ";
    ls->propJoyPort2GB          = "�s���� #2 ";
    ls->propJoyAutofireText     = "�s�o:";
    ls->propJoyKeysetGB         = "�n�����]�w ";
    ls->propJoyKeyest1          = "�]�w�n�� A ������";
    ls->propJoyKeyest2          = "�]�w�n�� B ������";

    ls->enumVideoMonColor       = "�m��";
    ls->enumVideoMonGrey        = "�¥�";
    ls->enumVideoMonGreen       = "���";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "�L";
    ls->enumVideoEmuYc          = "Y/C �����^�� (�U�Q)";
    ls->enumVideoEmuYcBlur      = "���T Y/C �����^�� (�U�Q)";
    ls->enumVideoEmuComp        = "�ƦX (�ҽk)";
    ls->enumVideoEmuCompBlur    = "���T�ƦX (�ҽk)";
    ls->enumVideoEmuScale2x     = "�⭿�Y��";

    ls->enumVideoSize1x         = "�з� - 320x200";
    ls->enumVideoSize2x         = "�⭿ - 640x400";
    ls->enumVideoSizeFullscreen = "���ù�";

    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "�L";
    ls->enumVideoFrameskip1     = "1 �e��";
    ls->enumVideoFrameskip2     = "2 �ӵe��";
    ls->enumVideoFrameskip3     = "3 �ӵe��";
    ls->enumVideoFrameskip4     = "4 �ӵe��";
    ls->enumVideoFrameskip5     = "5 �ӵe��";

    ls->enumSoundDrvNone        = "�S������";
    ls->enumSoundDrvWMM         = "WMM �X�ʵ{��";
    ls->enumSoundDrvDirectX     = "DirectX �X�ʵ{��";

    ls->enumControlsJoyNone     = "�L";
    ls->enumControlsJoyNumpad   = "�Ʀr��x";
    ls->enumControlsJoyKeysetA  = "����]�w A";
    ls->enumControlsJoyKeysetB  = "����]�w B";
    ls->enumControlsJoyPCjoy1   = "PC �n�� #1";
    ls->enumControlsJoyPCjoy2   = "PC �n�� #2";
    ls->enumControlsJoyMouse    = "�ƹ�";

    ls->enumControlsAfOff       = "��";
    ls->enumControlsAfSlow      = "�C";
    ls->enumControlsAfMedium    = "��";
    ls->enumControlsAfFast      = "��";

    ls->dlgAboutAbout           = "����\r\n====";
    ls->dlgAboutVersion         = "����:";
    ls->dlgAboutBuildNumber     = "�ի�:";
    ls->dlgAboutBuildDate       = "���:";
    ls->dlgAboutCreat           = "�� Daniel Vik �Ч@";
    ls->dlgAboutDevel           = "�}�o����\r\n========";
    ls->dlgAboutThanks          = "�S�O�P��\r\n============";
    ls->dlgAboutLisence         = "���v��ĳ\r\n"
                                  "======\r\n\r\n"
                                  "�o�ӳn��̾ڥثe�����A�Ӵ��ѡA�S��������T���ηt�ܪ���O�C "
                                  "�b���󱡪p�U�A�ϥγo�ӳn��ҳy�����l�`�ݭn�ϥΪ̦ۤv�Ӿ�A "
                                  "�@�̤��Ӿ���󪺳d���C\r\n\r\n"
                                  "�гX�� www.bluemsx.com ���o��h�Ӹ`�C";

    // New entries
    ls->menuTools                = "�u��";
    ls->menuToolsMachine         = "���ؽs�边";
    ls->menuPropsSettings        = "�]�w";
    ls->menuCasRewindAfterInsert = "���J����j�a";
    ls->menuCasUseReadOnly       = "�ϥκϱa�M���ɰ�Ū";
    ls->lmenuCasSaveAs           = "�t�s�ϱa�M���ɬ�...";

    ls->dlgSaveCassette          = "blueMSX - �x�s�ϱa�M����";
    ls->dlgTapeCustom            = "��ܦۭq�ɮ�";
    ls->dlgTapeSetPosText        = "�ϱa��m:";
    ls->dlgTabPosition           = "��m";
    ls->dlgTabType               = "����";
    ls->dlgTabFilename           = "�ɮצW��";

    ls->propSettings             = "�]�w";
    
    ls->propSetFileHistoryGB     = "�ɮװO�� ";
    ls->propSetFileHistorySize   = "�ɮװO�������ؼ�:";
    ls->propSetFileHistoryClear  = "�M���O��";
    ls->propSetScreenSaverGB     = "�ù��O�@ ";
    ls->propSetScreenSaver       = " �� blueMSX ����ɰ��οù��O�@";

    ls->confTitle                = "blueMSX - ���زպA�s�边";
    ls->confSave                 = "�x�s";
    ls->confSaveAs               = "�t�s�s��...";
    ls->confRun                  = "����";
    ls->confClose                = "����";
    ls->confConfigText           = "�]�w";
    ls->confSlotLayout           = "���Ѱt�m";
    ls->confMemory               = "�O����";
    ls->confChipEmulation        = "��������";

    ls->confSlotLayoutGB         = "���ѥ��� ";
    ls->confSlotExtSlotGB        = "�~������ ";
    ls->confSlotSlot0            = "���� 0";
    ls->confSlotSlot1            = "���� 1";
    ls->confSlotSlot2            = "���� 2";
    ls->confSlotSlot3            = "���� 3";
    ls->confSlotCart1            = "�d�X 1:";
    ls->confSlotCart2            = "�d�X 2:";
    ls->confSlotPrimary          = "�D�n";
    ls->confSlotExpanded         = "�w�X�i (�|�Ӥl����)";

    ls->confMemAdd               = "�[�J...";
    ls->confMemEdit              = "�s��...";
    ls->confMemRemove            = "����";
    ls->confMemSlot              = "����";
    ls->confMemAddresss          = "��}";
    ls->confMemType              = "����";
    ls->confMemRomImage          = "ROM �M����";
    
    ls->confSaveTitle            = "blueMSX - �x�s�]�w";
    ls->confSaveText             = "�z�T�w�n�мg���س]�w��:";

    ls->confChipVideoGB          = "���T ";
    ls->confChipVideoChip        = "���T����:";
    ls->confChipVideoRam         = "���T RAM:";
    ls->confChipSoundGB          = "���� ";

    ls->slotEditMemTitle         = "blueMSX - �s�������";
    ls->slotEditMemGB            = "�������Ӹ` ";
    ls->slotEditMemType          = "����:";
    ls->slotEditMemFile          = "�ɮ�:";
    ls->slotEditMemAddress       = "��}";
    ls->slotEditMemSize          = "�j�p";
    ls->slotEditMemSlot          = "����";

    ls->confDiscardTitle         = "blueMSX - �]�w";
    ls->confExitSaveTitle        = "blueMSX - ���}�]�w�s�边";
    ls->confExitSaveText         = "�z�T�w�n���ثe���]�w���ܧ�ܡH";

    ls->confSaveAsMachineTitle   = "blueMSX - �t�s���س]�w��...";
    ls->confSaveAsMachineName    = "���ئW��:";

    ls->confEditMemInternalRoms  = "blueMSX - ���� ROM";
    ls->propSndMoonsound         = " MoonSound";

    ls->propFileTypesGB          = "�ɮ����� ";
    ls->propFileTypes            = " ���U blueMSX ���p���ɮ����� (.rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " �ϥ� MSX �ɦ۰ʰ��� Windows �����B�k��\\���"; 
    ls->propWindowsEnvGB         = "Windows ���� "; 
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW �[�t"; 
    ls->enumVideoDrvDirectDrawHWSys = "DirectDraw �V�X"; 
    ls->propMonHorizStretch      = " �����Ԧ�";
    ls->propMonVertStretch       = " �����Ԧ�";
    ls->propClearHistory         = "�z�O�_�T�w�n�M���ɮװO���H";

    ls->propEmuFrontSwitchGB     = "Panasonic �}�� ";
    ls->propEmuFrontSwitch       = " �e�ݶ}��";
    ls->propEmuAudioSwitch       = " MSX ���ĥd�}��";


    ls->dlgCmosGB                = "CMOS ";
    ls->dlgCmosEnable            = " �ҥ� CMOS";
    ls->dlgCmosBattery           = " �ϥΥR�q�q��";

    ls->menuCartSnatcher        = "Snatcher �d�X";
    ls->menuCartSdSnatcher      = "SD-Snatcher �d�X";
    ls->menuCartSCCMirrored     = "SCC �蹳�d�X";
    ls->menuCartSCCExpanded     = "SCC �X�i�d�X";
    ls->menuCartSCCPlus         = "SCC + �d�X";
    ls->menuCartSCC             = "SCC �d�X";
    
    ls->warningTitle             = "blueMSX - ĵ�i";
    ls->tooltipStop             = "�������";

    // New entries in 1.5.1
    ls->enumControlsJoyKeyset   = "����]�w";    
    ls->propJoyConfigKeyset     = "�]�w����";
    ls->propJoyControlText      = "���:";
    ls->propJoyButtonText       = "���s";
    ls->propJoyButtonAText      = "���s A:";
    ls->propJoyButtonBText      = "���s B:";

    ls->menuToolsShortcuts      = "�ֳt��s�边";

    ls->shortcutSaveConfig      = "blueMSX - �x�s�]�w";
    ls->shortcutOverwriteConfig = "�z�T�w�n�мg�ֳt��]�w��:";
    ls->shortcutExitConfig      = "blueMSX - ���}�ֳt��s�边";
    ls->shortcutDiscardConfig   = "�z�T�w�n���ثe���]�w���ܧ�ܡH";
    ls->shortcutSaveConfigAs    = "blueMSX - �t�s�ֳt��]�w��...";
    ls->shortcutConfigName      = "�]�w�W��:";
    ls->shortcutNewProfile      = "< �s���]�w�� >";
    ls->shortcutConfigTitle     = "blueMSX - �ֳt������s�边";
    ls->shortcutAssign          = "����";
    ls->shortcutPressText       = "�Ы��U�ֳt�����:";
    ls->shortcutScheme          = "�����t�m:";

    ls->shortcutCartInsert1     = "���J�d�X 1";
    ls->shortcutCartRemove1     = "�����d�X 1";
    ls->shortcutCartInsert2     = "���J�d�X 2";
    ls->shortcutCartRemove2     = "�����d�X 2";
    ls->shortcutCartAutoReset   = "��d�X���J�᭫�m������";
    ls->shortcutDiskInsertA     = "���J�Ϥ� A";
    ls->shortcutDiskRemoveA     = "�h�X�Ϥ� A";
    ls->shortcutDiskChangeA     = "�ֳt�ܧ�Ϥ� A";
    ls->shortcutDiskAutoResetA  = "��Ϥ� A ���J�᭫�m������";
    ls->shortcutDiskInsertB     = "���J�Ϥ� B";
    ls->shortcutDiskRemoveB     = "�h�X�Ϥ� B";
    ls->shortcutCasInsert       = "���J�ϱa";
    ls->shortcutCasEject        = "�h�X�ϱa";
    ls->shortcutCasAutorewind   = "�N�ϱa�������۰ʰj�a���A";
    ls->shortcutCasReadOnly     = "�N�ϱa��������Ū���A";
    ls->shortcutCasSetPosition  = "�]�w�ϱa��m";
    ls->shortcutCasRewind       = "�ϱa�j�a";
    ls->shortcutCasSave         = "�x�s�ϱa�M����";
    ls->shortcutCpuStateLoad    = "���J CPU ���A";
    ls->shortcutCpuStateSave    = "�x�s CPU ���A";
    ls->shortcutCpuStateQload   = "�ֳt���J CPU ���A";
    ls->shortcutCpuStateQsave   = "�ֳt�x�s CPU ���A";
    ls->shortcutAudioCapture    = "�}�l/����T�^��";
    ls->shortcutScreenshotOrig  = "�ù���� (��l)";
    ls->shortcutScreenshotSmall = "���L�o���ù���� (���p)";
    ls->shortcutScreenshotLarge = "���L�o���ù���� (���j)";
    ls->shortcutQuit            = "���� blueMSX";
    ls->shortcutRunPause        = "����/�Ȱ�����";
    ls->shortcutStop            = "�������";
    ls->shortcutResetHard       = "�w�魫�m";
    ls->shortcutResetSoft       = "�n�魫�m";
    ls->shortcutResetClean      = "�@�뭫�m";
    ls->shortcutSizeSmall       = "�]�w�p�����j�p";
    ls->shortcutSizeNormal      = "�]�w�зǵ����j�p";
    ls->shortcutSizeFullscreen  = "�]�w���ù�";
    ls->shortcutToggleFullscren = "�������ù�";
    ls->shortcutVolumeIncrease  = "�W�j���q";
    ls->shortcutVolumeDecrease  = "��p���q";
    ls->shortcutVolumeMute      = "�R�����q";
    ls->shortcutSwitchMsxAudio  = "���� MSX ���Ķ}��";
    ls->shortcutSwitchFront     = "���� Panasonic �e�ݶ}��";
    ls->shortcutToggleMouseLock = "�����ƹ���w";
    ls->shortcutEmuSpeedMax     = "�̰������t��";
    ls->shortcutEmuSpeedToggle  = "�����̰������t��";
    ls->shortcutEmuSpeedNormal  = "�зǼ����t��";
    ls->shortcutEmuSpeedInc     = "�W�[�����t��";
    ls->shortcutEmuSpeedDec     = "��C�����t��";
    ls->shortcutShowEmuProp     = "��ܼ������e";
    ls->shortcutShowVideoProp   = "��ܵ��T���e";
    ls->shortcutShowAudioProp   = "��ܭ��T���e";
    ls->shortcutShowCtrlProp    = "��ܱ���e";
    ls->shortcutShowPerfProp    = "��ܮįऺ�e";
    ls->shortcutShowSettProp    = "��ܳ]�w���e";
    ls->shortcutShowLanguage    = "��ܻy����ܤ��";
    ls->shortcutShowMachines    = "��ܾ��ؽs�边";
    ls->shortcutShowShortcuts   = "��ܧֳt��s�边";
    ls->shortcutShowHelp        = "��ܻ�����ܤ��";
    ls->shortcutShowAbout       = "��������ܤ��";
    
    ls->shortcutSpecialMenu1    = "��ܥd�X 1 ���B�~ ROM ���";
    ls->shortcutSpecialMenu2    = "��ܥd�X 2 ���B�~ ROM ���";
    ls->shortcutVolumeStereo    = "�����歵/�����n";
    ls->shortcutThemeSwitch     = "�����G���D�D";
    ls->shortcutToggleSpriteEnable = "���/���ëe���ϼh";
    
    ls->shortcutShowApearProp   = "��ܥ~�[���e";
    ls->menuPropsApearance      = "�~�[";
    ls->propApearance           = "�~�[";
    ls->propThemeGB             = "�G���D�D ";
    ls->propTheme               = "�G���D�D:";
    ls->propThemeClassic        = "�嫬";
    ls->propThemeBlue           = "DIGIDIGIblue";

    ls->propMonBrightness       = "�G��:";
    ls->propMonContrast         = "����:";
    ls->propMonSaturation       = "���X��:";
    ls->propMonGamma            = "�ɺ���:";
    ls->propMonScanlines        = "���˽u:";

    ls->dlgRomType              = "ROM ����:";
    ls->propOpenRomGB           = "�}�� ROM ��ܤ�� ";
    ls->propDefaultRomType      = "�w�] ROM ����:";
    ls->propGuessRomType        = "���� ROM ����";

    ls->propFile                = "�ɮ�";
    ls->propSettDefSlotGB       = "�즲 ";
    ls->propSettDefSlots        = "���J ROM ��:";
    ls->propSettDefSlot1        = " ���� 1";
    ls->propSettDefSlot2        = " ���� 2";
    ls->propSettDefDrives       = "���J�Ϥ���:";
    ls->propSettDefDriveA       = " �Ϻо� A";
    ls->propSettDefDriveB       = " �Ϻо� B";
    ls->menuPropsFile           = "�ɮ�";
    ls->shortcutShowFiles       = "����ɮפ��e";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "���J�ؿ�";
    ls->shortcutDiskDirInsertA  = "���J�ؿ��@���Ϥ� A";
    ls->shortcutDiskDirInsertB  = "���J�ؿ��@���Ϥ� B";
    ls->propMonDeInterlace      = " �h�������e��\\��";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "�����Ȱ��}��";
    ls->shortcutSizeMinimized   = "�̤p�Ƶ���";
    ls->shortcutEmuSpeedToggle  = "�����̰������t��";
    ls->shortcutToggleCpuTrace  = "�ҥ�/���� CPU �l��";

    ls->enumVideoEmuMonitor     = "�ʵ���";

    ls->propEmuPauseSwitch      = " �Ȱ��}��";
    ls->propVideoFreqText       = "���T�W�v:";
    ls->propVideoFreqAuto       = "�۰�";
    ls->propSndOversampleText   = "�W����:";

    ls->confChipExtras          = "�B�~";
    ls->confBoardGB             = "�D���O ";
    ls->confBoardText           = "�D���O����:";
    ls->dlgCpuFreqGB            = "CPU �W�v ";
    ls->dlgZ80FreqText          = "Z80 �W�v:";
    ls->dlgR800FreqText         = "R800 �W�v:";
    ls->dlgFdcGB                = "�n���Ϻб�� ";
    ls->dlgCFdcNumDrivesText    = "�Ϻо��N��:";

    ls->propPriorityBoost       = " ���� blueMSX ���u���v";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "���γn���Ϻо��p��";
    ls->shortcutToggleFdcTiming = "�ҥ�/���γn���Ϻо��p��";
    ls->propUseRegistry         = "�b���U���x�s�]�w";

    // New entries in 2.2
    ls->menuCartHBI55           = "SONY HBI-55 �d�X";
    ls->propSndPcm              = " Turbo-R PCM ���T";
    ls->propSndAY8910           = " AY8910 PSG ���T";
    ls->propSndSN76489          = " SN76489 PSG ���T";
    ls->enumVideoEmuHq2x        = "�⭿���~��";
    ls->propMonColorGhosting    = "RF ���ܾ�";

    ls->keyconfigSelectedKey    = "���������:";
    ls->keyconfigMappedTo       = "������:";
    ls->keyconfigMappingScheme  = "�����t�m:";

    ls->discardChanges          = "�z�T�w�n����ܧ�ܡH";
    ls->overwriteConfig         = "�z�T�w�n�мg�ثe���]�w�ܡH";

    ls->confSaveAsTitle         = "�t�s�]�w��...";
    ls->confSaveAsName          = "�W��:";

    ls->menuToolsKeyboard       = "��L�s�边";
    ls->shortcutShowKeyboard    = "�����L�s�边";

    ls->menuVideoSource         = "���T�ӷ�";
    ls->menuVideoSourceDefault  = "���s�u�����T�ӷ�";
    ls->menuVideoChipAutodetect = "�۰ʰ������T����";
    ls->propFullscreenResText   = "���ù��ѪR��:";
    ls->dlgSavePreview          = "��ܹw��";
    ls->dlgSaveDate             = "�x�s�ɶ�:";
    
    ls->enumVideoMonAmber       = "����";

    ls->menuPropsPorts          = "�s����";
    ls->propPortsLptGB          = "�æC�s���� ";
    ls->propPortsComGB          = "�ǦC�s���� ";
    ls->propPortsLptText        = "�s����:";
    ls->propPortsCom1Text       = "�s���� 1:";

    ls->shortcutShowDebugger    = "��ܰ����u��";
    ls->shortcutShowTrainer     = "��ܭקﾹ";
    ls->shortcutShowPorts       = "��ܳs���𤺮e";
    
    ls->propPorts               = "�s����";
    ls->propPortsNone           = "�L";

    // New entries in 2.3
    ls->enumControlsJoyTetris2Dongle = "�Xù����� 2 �����Ҳ�";

    ls->propPortsSimplCovox     = "SiMPL / Covox �Ʀ������ഫ��";
    ls->propPortsFile           = "�C�L���ɮ�";
    ls->propPortsOpenLogFile    = "�}�ҰO����";
    ls->propPortsFilenameText   = "�ɮצW��:";
    ls->propPortsEmulateMsxPrn  = "����:";

    ls->shortcutPrnFormFeed     = "�L�������";

    ls->menuPrnFormfeed         = "����";
    ls->menuFilePrn             = "�L���";
    ls->propPortsComFile        = "�ǰe���ɮ�";

    // New entries in 2.4
    ls->shortcutShowMixer       = "��ܲV�X��";
    ls->menuToolsMixer          = "�V�X��";
    
    ls->propSndMidiInGB         = "MIDI ��J ";
    ls->propSndMidiOutGB        = "MIDI ��X ";
    ls->propSndMt32ToGmText     = " ���� MT-32 �־���@�� MIDI �˸m";

    ls->textDevice              = "�˸m:";
    ls->textFilename            = "�ɮצW��:";
    ls->textFile                = "�ɮ�";
    ls->textNone                = "�L";

    ls->enumEmuSyncAuto         = "�۰� (�ֳt)";
    ls->enumEmuSync1ms          = "�P�B�� MSX ���s��z";
    ls->enumEmuSyncVblank       = "�P�B�� PC �����ť�";
};


#endif

