/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageKorean.h,v $
**
** $Revision: 1.8 $ + additions 2005/03/03
**
** $Date: 2005-03-12 00:40:32 $
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
#ifndef LANGUAGE_KOREAN_H
#define LANGUAGE_KOREAN_H

#include "LanguageStrings.h"
 
void langInitKorean(LanguageStrings* ls)
{
    ls->statusBarStopped        = "  ����";
    ls->statusBarPaused         = "  �Ͻ� ����";
    ls->statusBarRunning        = "  ������";
    
    ls->menuHardReset           = "�ϵ� ����";
    ls->menuSoftReset           = "����Ʈ ����";
    
    ls->menuCartInsert          = "����";
    ls->menuCartRemove          = "����";
    ls->menuCartAutoReset       = "����/���� �Ŀ� �����";
    ls->menuCartNoRecentFiles   = "- ��� ���� ���� -";
    ls->menuCartFMPac           = "FM-PAC īƮ����";
    ls->menuCartPac             = "PAC īƮ����";
    ls->menuCartSpecial         = "����� ���� īƮ����";

    ls->menuDiskInsert          = "����";
    ls->menuDiskEject           = "������";
    ls->menuDiskAutoStart       = "�����Ŀ� �����";
    ls->menuDiskNoRecentFiles   = "- ��� ���� ���� -";
    
    ls->menuCasInsert           = "����";
    ls->menuCasEject            = "������";
    ls->menuCasSetPosition      = "��ġ ����";
    ls->menuCasRewind           = "�ǰ���";
    ls->menuCasNoRecentFiles    = "- ��� ���� ���� -";

    ls->menuZoomNormal          = "���� ũ��";
    ls->menuZoomDouble          = "�ι� ũ��";
    ls->menuZoomFullscreen      = "��ü ȭ��";
    
    ls->menuPropsEmulation      = "���ķ��̼�";
    ls->menuPropsVideo          = "����";
    ls->menuPropsSound          = "����";
    ls->menuPropsControls       = "��Ʈ��";
    ls->menuPropsPerformance    = "����";
    ls->menuPropsLanguage       = "���";
    
    ls->menuHelpHelp            = "���� �׸�";
    ls->menuHelpAbout           = "blueMSX�� ���Ͽ�";

    ls->menuFileCart1           = "īƮ���� ���� 1";
    ls->menuFileCart2           = "īƮ���� ���� 2";
    ls->menuFileDiskA           = "��ũ ����̺� A";
    ls->menuFileDiskB           = "��ũ ����̺� B";
    ls->menuFileCas             = "ī��Ʈ";
    ls->menuFileLoadState       = "CPU ���� �ҷ�����";
    ls->menuFileSaveState       = "CPU ���� ����";
    ls->menuFileQLoadState      = "���� �ٷ� �ҷ�����";
    ls->menuFileQSaveState      = "���� �ٷ� ����";
    ls->menuFileCaptureAudio    = "�Ҹ� ����";
    ls->menuFileScreenShot      = "ȭ�� ����";
    ls->menuFileExit            = "������";

    ls->menuRunRun              = "����";
    ls->menuRunPause            = "�Ͻ� ����";
    ls->menuRunStop             = "����";
    ls->menuRunSoftReset        = "����Ʈ ����";
    ls->menuRunHardReset        = "�ϵ� ����";
    ls->menuRunCleanReset       = "��ü ����";

    ls->menuFile                = "����";
    ls->menuRun                 = "����";
    ls->menuWindow              = "������";
    ls->menuOptions             = "�ɼ�";
    ls->menuHelp                = "����";
    
    ls->errorTitle              = "blueMSX - ����";
    ls->errorEnterFullscreen    = "��ü ȭ���� ���� ����.           \n";
    ls->errorDirectXFailed      = "DirectX ������Ʈ ����� ����.           \nGDI�� ��ü�ؼ� ����մϴ�.\n�׷���ī�� ��������� Ȯ���ϼ���.";
    ls->errorNoRomInZip         = "zip���� �ȿ� .rom�� ã�� �� �����ϴ�.";
    ls->errorNoDskInZip         = "zip���� �ȿ� .dsk�� ã�� �� �����ϴ�.";
    ls->errorNoCasInZip         = "zip���� �ȿ� .cas�� ã�� �� �����ϴ�.";
    ls->errorNoHelp             = "blueMSX ������ ã�� �� �����ϴ�.";
    ls->errorStartEmu           = "MSX ���ķ����͸� ������ �� �����ϴ�.";

    ls->tooltipReset            = "MSX ����";
    ls->tooltipCart1            = "���� 1�� īƮ���� ����";
    ls->tooltipCart2            = "���� 2�� īƮ���� ����";
    ls->tooltipDiskA            = "����̺� A�� ��ũ ����";
    ls->tooltipDiskB            = "����̺� B�� ��ũ ����";
    ls->tooltipCas              = "ī��Ʈ �÷��̾ ���� ����";
    ls->tooltipStart            = "���ķ��̼� ����";
    ls->tooltipResume           = "���ķ��̼� �ٽ� ����";
    ls->tooltipPause            = "���ķ��̼� �Ͻ� ����";
    ls->tooltipWindowSize       = "������ ũ�� ����";
    ls->tooltipProperties       = "�ɼ� ����";
    ls->tooltipHelp             = "���� ����";

    ls->dlgMainWindow           = "  blueMSX";
    ls->dlgLoadRom              = "blueMSX - īƮ������ ������ rom �̹��� ����";
    ls->dlgLoadDsk              = "blueMSX - ����̺꿡 ������ dsk �̹��� ����";
    ls->dlgLoadCas              = "blueMSX - ī��Ʈ �÷��̾ ���� cas �̹��� ����";
    ls->dlgLoadRomDskCas        = "blueMSX - �о� ���� rom, dsk, cas �̹��� ����";
    ls->dlgLoadRomDesc          = "īƮ������ ������ �� �̹����� ������ �ּ���:";
    ls->dlgLoadDskDesc          = "����̺꿡 ������ ù��° �� ��ũ �Ǵ� ��ũ �̹����� ������ �ּ���(��ȯ�� ALT+F9. ���ϸ�� ���ڰ� �����ؾ� �˴ϴ�):";
    ls->dlgLoadCasDesc          = "ī��Ʈ �÷��̾ ���� ���� �̹����� ������ �ּ���:";
    ls->dlgLoadRomDskCasDesc    = "�о� ���� ��,��ũ,�Ǵ� ���� �̹����� ������ �ּ���:";
    ls->dlgLoadState            = "CPU ���� �ҷ�����";
    ls->dlgSaveState            = "CPU ���� ����";
    ls->dlgInsertRom1           = "���� 1�� ROM īƮ���� ����";
    ls->dlgInsertRom2           = "���� 2�� ROM īƮ���� ����";
    ls->dlgInsertDiskA          = "����̺� A�� ��ũ ����";
    ls->dlgInsertDiskB          = "����̺� B�� ��ũ ����";
    ls->dlgInsertCas            = "ī��Ʈ ���� ����";

    ls->dlgOK                   = "Ȯ��";
    ls->dlgOpen                 = "����";
    ls->dlgCancel               = "���";

    ls->dlgTapeTitle            = "blueMSX - ���� ��ġ";
    ls->dlgTapeFrameText        = "���� ��ġ";
    ls->dlgTapeCurrentPos       = "���� ��ġ";
    ls->dlgTapeTotalTime        = "�� �ð�";

    ls->dlgZipReset             = "������ �����";

    ls->dlgAboutTitle           = "blueMSX�� ���Ͽ�";

    ls->dlgJoyTitle1            = "blueMSX - ���̽�ƽA Ű����";
    ls->dlgJoyTitle2            = "blueMSX - ���̽�ƽB Ű����";
    ls->dlgJoyUpText            = "��";
    ls->dlgJoyDownText          = "�Ʒ�";
    ls->dlgJoyLeftText          = "����";
    ls->dlgJoyRightText         = "������";
    ls->dlgJoyButton1Text       = "��ư 1";
    ls->dlgJoyButton2Text       = "��ư 2";
    ls->dlgJoyGB                = "Ű���� ";

    ls->dlgLangLangText         = "blueMSX�� ����� ��� ����";
    ls->dlgLangLangTitle        = "blueMSX - ���";

    ls->propTitle               = "blueMSX - �Ӽ�";
    ls->propEmulation           = "���ķ��̼�";
    ls->propVideo               = "����";
    ls->propSound               = "����";
    ls->propControls            = "��Ʈ��";
    ls->propPerformance         = "����";
    
    ls->propEmuGeneralGB        = "�Ϲ� ";
    ls->propEmuFamilyText       = "MSX �ӽ�:";
    ls->propEmuMemoryGB         = "�޸� ";
    ls->propEmuRamSizeText      = "�� ũ��:";
    ls->propEmuVramSizeText     = "������ ũ��:";
    ls->propEmuSpeedGB          = "���ķ��̼� �ӵ� ";
    ls->propEmuSpeedText        = "���ķ��̼� �ӵ�:";

    ls->propMonMonGB            = "����� ";
    ls->propMonTypeText         = "����� ����:";
    ls->propMonEmuText          = "����� ���ķ��̼�:";
    ls->propVideoYypeText       = "���� ����:";
    ls->propWindowSizeText      = "������ ũ��:";

    ls->propPerfVideoDrvGB      = "���� ����̹� ";
    ls->propPerfVideoDispDrvText= "ȭ�� ����̹�:";
    ls->propPerfFrameSkipText   = "������ �ǳʶ��:";
    ls->propPerfAudioDrvGB      = "����� ����̹� ";
    ls->propPerfAudioDrvText    = "���� ����̹�:";
    ls->propPerfAudioBufSzText  = "���� ���� ������:";
    ls->propPerfEmuGB           = "Ŭ�� ���ķ��̼� ";
    ls->propPerfSyncModeText    = "����ȭ ���:";

    ls->propSndChipEmuGB        = "���� Ĩ ���ķ��̼� ";
    ls->propSndMixerGB          = "����� �ͼ� ";
    ls->propSndMonoText         = "���";
    ls->propSndStereoText       = "���׷���";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "������";

    ls->propJoyPort1GB          = "��Ʈ #1 ";
    ls->propJoyPort2GB          = "��Ʈ #2 ";
    ls->propJoyAutofireText     = "�ڵ��߻�:";
    ls->propJoyKeysetGB         = "���̽�ƽ Ű���� ";
    ls->propJoyKeyest1          = "A Ű����";
    ls->propJoyKeyest2          = "B Ű����";

    ls->enumVideoMonColor       = "�÷�";
    ls->enumVideoMonGrey        = "������ ���";
    ls->enumVideoMonGreen       = "���";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "����";
    ls->enumVideoEmuYc          = "Y/C ���̺� (����)";
    ls->enumVideoEmuYcBlur      = "�����ִ� Y/C ���̺� (����)";
    ls->enumVideoEmuComp        = "������Ʈ (�帴)";
    ls->enumVideoEmuCompBlur    = "�����ִ� ������Ʈ (�帴)";
    ls->enumVideoEmuScale2x     = "2x ������";

    ls->enumVideoSize1x         = "���� - 320x200";
    ls->enumVideoSize2x         = "�ι� - 640x400";
    ls->enumVideoSizeFullscreen = "��ü ȭ��";

    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "����";
    ls->enumVideoFrameskip1     = "1 ������";
    ls->enumVideoFrameskip2     = "2 ������";
    ls->enumVideoFrameskip3     = "3 ������";
    ls->enumVideoFrameskip4     = "4 ������";
    ls->enumVideoFrameskip5     = "5 ������";

    ls->enumSoundDrvNone        = "�Ҹ�����";
    ls->enumSoundDrvWMM         = "WMM ����̹�";
    ls->enumSoundDrvDirectX     = "DirectX ����̹�";

    ls->enumEmuSync1ms          = "1ms (��������)";
    ls->enumEmuSyncAuto         = "�ڵ� (����)";

    ls->enumControlsJoyNone     = "����";
    ls->enumControlsJoyNumpad   = "����Ű";
    ls->enumControlsJoyKeysetA  = "Ű A";
    ls->enumControlsJoyKeysetB  = "Ű B";
    ls->enumControlsJoyPCjoy1   = "PC ���̽�ƽ #1";
    ls->enumControlsJoyPCjoy2   = "PC ���̽�ƽ #2";
    ls->enumControlsJoyMouse    = "���콺";

    ls->enumControlsAfOff       = "��";
    ls->enumControlsAfSlow      = "������";
    ls->enumControlsAfMedium    = "�߰�";
    ls->enumControlsAfFast      = "������";

    ls->dlgAboutAbout           = "���Ͽ�\r\n=====";
    ls->dlgAboutVersion         = "����:";
    ls->dlgAboutBuildNumber     = "����:";
    ls->dlgAboutBuildDate       = "��¥:";
    ls->dlgAboutCreat           = "������: Daniel Vik";
    ls->dlgAboutDevel           = "������ �е�\r\n========";
    ls->dlgAboutThanks          = "������ �ֽ� �е�\r\n===========";
    ls->dlgAboutLisence         = "���̼���\r\n"
                                  "======\r\n\r\n"
				  "�� ����Ʈ����� ���� �״�� �����Ǿ�� �ϸ�, ������̰� �������̰� "
				  "� ������ ������ ���� �ʽ��ϴ�.\r\n�� ����Ʈ������ ������� �Ͼ�� "
				  "��� �������� �����ڿ��Դ� å���� �����ϴ�.\r\n\r\n"
                                  "�� �ڼ��� ���� www.bluemsx.com�� �湮�� �ּ���.";

    // New entries
    ls->menuTools                = "����";
    ls->menuToolsMachine         = "�ӽ� ������";
    ls->menuPropsSettings        = "�ܺ� ����";
    ls->menuCasRewindAfterInsert = "�����Ŀ� �ǰ���";
    ls->menuCasUseReadOnly       = "�б�����";
    ls->lmenuCasSaveAs           = "�ٸ� �̸����� ����...";

    ls->dlgSaveCassette          = "blueMSX - ���� �̹��� ����";
    ls->dlgTapeCustom            = "����� ���� ���� ����";
    ls->dlgTapeSetPosText        = "���� ��ġ:";
    ls->dlgTabPosition           = "��ġ";
    ls->dlgTabType               = "����";
    ls->dlgTabFilename           = "���� �̸�";

    ls->propSettings             = "�ܺ� ����";
    
    ls->propSetFileHistoryGB     = "��� ���� ��� ";
    ls->propSetFileHistorySize   = "���� ���� ũ��:";
    ls->propSetFileHistoryClear  = "��� �����";
    ls->propSetScreenSaverGB     = "ȭ�� ��ȣ�� ";
    ls->propSetScreenSaver       = " blueMSX �����߿��� ȭ�� ��ȣ�� ��� ����";

    ls->confTitle                = "blueMSX - �ӽ� ���� ������";
    ls->confSave                 = "����";
    ls->confSaveAs               = "�ٸ� �̸�����...";
    ls->confRun                  = "����";
    ls->confClose                = "�ݱ�";
    ls->confConfigText           = "�ӽ� ����";
    ls->confSlotLayout           = "���� ��ġ";
    ls->confMemory               = "�޸�";
    ls->confChipEmulation        = "Ĩ ���ķ��̼�";

    ls->confSlotLayoutGB         = "���� ��ġ ";
    ls->confSlotExtSlotGB        = "�ܺ� ���� ";
    ls->confSlotSlot0            = "���� 0";
    ls->confSlotSlot1            = "���� 1";
    ls->confSlotSlot2            = "���� 2";
    ls->confSlotSlot3            = "���� 3";
    ls->confSlotCart1            = "īƮ���� 1:";
    ls->confSlotCart2            = "īƮ���� 2:";
    ls->confSlotPrimary          = "�⺻";
    ls->confSlotExpanded         = "Ȯ�� (4���� ���꽽��)";

    ls->confMemAdd               = "�߰�...";
    ls->confMemEdit              = "����...";
    ls->confMemRemove            = "����";
    ls->confMemSlot              = "����";
    ls->confMemAddresss          = "�ּ�";
    ls->confMemType              = "����";
    ls->confMemRomImage          = "�� �̹���";
    
    ls->confSaveTitle            = "blueMSX - ���� ����";
    ls->confSaveText             = "�̹� ������ �ֽ��ϴ�. ���� ������ �� ���Ϸ� �ٲٽðڽ��ϱ�?";

    ls->confChipVideoGB          = "���� ";
    ls->confChipVideoChip        = "���� Ĩ:";
    ls->confChipVideoRam         = "���� ��:";
    ls->confChipSoundGB          = "���� ";

    ls->slotEditMemTitle         = "blueMSX - ���� ����";
    ls->slotEditMemGB            = "���� �׸� ";
    ls->slotEditMemType          = "����:";
    ls->slotEditMemFile          = "����:";
    ls->slotEditMemAddress       = "�ּ�";
    ls->slotEditMemSize          = "ũ��";
    ls->slotEditMemSlot          = "����";
    ls->confDiscardTitle         = "blueMSX - ����";
    ls->confExitSaveTitle        = "blueMSX - �ӽ� ���� ������ ������";
    ls->confExitSaveText         = "������ ������ ����Ǳ� ���ؼ� ������ �ϼž� �մϴٸ� ���� �������� �ƹ��� ���⵵ �����ʰ� �׳� �����ڽ��ϱ�?";

    ls->confSaveAsMachineTitle   = "blueMSX - �ٸ� �̸����� �ӽ� ���� ����...";
    ls->confSaveAsMachineName    = "�ӽ� �̸�:";

    ls->confEditMemInternalRoms  = "blueMSX - ���� ROM";
    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypesGB          = "���� ���� ";
    ls->propFileTypes            = " blueMSX�� ��������(.rom .dsk .cas .sta) ����";
    ls->propDisableWinKeys       = " blueMSX �����߿��� ��/������ ������ Ű ��� ����"; 
    ls->propWindowsEnvGB         = "�������� ȯ�� "; 
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW accel."; 
    ls->enumVideoDrvDirectDrawHWSys = "DirectDraw mix."; 
    ls->propMonHorizStretch      = " ���� ��ũ��ġ";
    ls->propMonVertStretch       = " ���� ��ũ��ġ";
    ls->propClearHistory         = "��� ���� ����� ������?";
    ls->propEmuFrontSwitchGB     = "�ĳ��Ҵ� ����ġ ";
    ls->propEmuFrontSwitch       = " ����Ʈ ����ġ";
    ls->propEmuAudioSwitch       = " MSX-AUDIO īƮ���� ����ġ";


    ls->dlgCmosGB                = "CMOS ";
    ls->dlgCmosEnable            = " CMOS ���";
    ls->dlgCmosBattery           = " ������ ���";

    ls->menuCartSnatcher        = "The Snatcher īƮ����";
    ls->menuCartSdSnatcher      = "SD-Snatcher īƮ����";
    ls->menuCartSCCMirrored     = "SCC Mirrored īƮ����";
    ls->menuCartSCCExpanded     = "SCC Expanded īƮ����";
    ls->warningTitle             = "blueMSX - ���";
    ls->tooltipStop             = "���ķ��̼� ";


        // New entries in 1.5.1
    ls->enumControlsJoyKeyset   = "Ű����";    
    ls->propJoyConfigKeyset     = "Ű����";
    ls->propJoyControlText      = "��Ʈ��:";
    ls->propJoyButtonText       = "��ư";
    ls->propJoyButtonAText      = "��ư A:";
    ls->propJoyButtonBText      = "��ư B:";

    ls->menuToolsShortcuts      = "����Ű ������";

    ls->shortcutSaveConfig      = "blueMSX - ���� ����";
    ls->shortcutOverwriteConfig = "�̹� ������ �ֽ��ϴ�. ���� ������ �� ���Ϸ� �ٲٽðڽ��ϱ�?";
    ls->shortcutExitConfig      = "blueMSX - ����Ű ������ ������";
    ls->shortcutDiscardConfig   = "������ ������ ����Ǳ� ���ؼ� ������ �ϼž� �մϴٸ� ���� �������� �ƹ��� ���⵵ �����ʰ� �׳� �����ڽ��ϱ�?";
    ls->shortcutSaveConfigAs    = "blueMSX - �ٸ��̸����� ����Ű ���� ����...";
    ls->shortcutConfigName      = "���� �̸�:";
    ls->shortcutNewProfile      = "< ���ο� ������ >";
    ls->shortcutConfigTitle     = "blueMSX - ����Ű ���� ������";
    ls->shortcutAssign          = "����";
    ls->shortcutPressText       = "����Ű ���� ����:";
    ls->shortcutScheme          = "����Ű ��Ÿ��:";

    ls->shortcutCartInsert1     = "īƮ���� 1 ����";
    ls->shortcutCartRemove1     = "īƮ���� 1 ����";
    ls->shortcutCartInsert2     = "īƮ���� 2 ����";
    ls->shortcutCartRemove2     = "īƮ���� 2 ����";
    ls->shortcutCartAutoReset   = "īƮ���� ������ ���ķ����� �����";
    ls->shortcutDiskInsertA     = "���� A ����";
    ls->shortcutDiskRemoveA     = "���� A ������";
    ls->shortcutDiskChangeA     = "���� A ���� ��ȯ(zip���� ����)";
    ls->shortcutDiskAutoResetA  = "���� A ������ ���ķ����� �����";
    ls->shortcutDiskInsertB     = "���� B ����";
    ls->shortcutDiskRemoveB     = "���� B ������";
    ls->shortcutCasInsert       = "ī��Ʈ ����";
    ls->shortcutCasEject        = "ī��Ʈ ������";
    ls->shortcutCasAutorewind   = "ī��Ʈ �ڵ� �ǰ��� ��� ��ȯ";
    ls->shortcutCasReadOnly     = "ī��Ʈ �б����� ��ȯ";
    ls->shortcutCasSetPosition  = "���� ��ġ ����";
    ls->shortcutCasRewind       = "ī��Ʈ �ǰ���";
    ls->shortcutCasSave         = "ī��Ʈ �̹��� ����";
    ls->shortcutCpuStateLoad    = "CPU ���� �ҷ�����";
    ls->shortcutCpuStateSave    = "CPU ���� ����";
    ls->shortcutCpuStateQload   = "���� �ٷ� �ҷ�����";
    ls->shortcutCpuStateQsave   = "���� �ٷ� ����";
    ls->shortcutAudioCapture    = "�Ҹ� ���� ����/����";
    ls->shortcutScreenshotOrig  = "ȭ�� ����";
    ls->shortcutScreenshotSmall = "���� ũ��� ȭ�� ����(����)";
    ls->shortcutScreenshotLarge = "ū ũ��� ȭ�� ����(����)";
    ls->shortcutQuit            = "blueMSX ������";
    ls->shortcutRunPause        = "���ķ��̼� ����/�Ͻ� ����";
    ls->shortcutStop            = "���ķ��̼� ����";
    ls->shortcutResetHard       = "�ϵ� ����";
    ls->shortcutResetSoft       = "����Ʈ ����";
    ls->shortcutResetClean      = "��ü ����";
    ls->shortcutSizeSmall       = "���� ������ ũ��� ����";
    ls->shortcutSizeNormal      = "���� ������ ũ��� ����";
    ls->shortcutSizeFullscreen  = "��ü ȭ������ ����";
    ls->shortcutToggleFullscren = "��ü ȭ�� ��ȯ";
    ls->shortcutVolumeIncrease  = "���� ����";
    ls->shortcutVolumeDecrease  = "���� ����";
    ls->shortcutVolumeMute      = "���Ұ�";
    ls->shortcutSwitchMsxAudio  = "MSX-AUDIO ����ġ ��ȯ";
    ls->shortcutSwitchFront     = "�ĳ��Ҵ� ����Ʈ ����ġ ��ȯ";
    ls->shortcutToggleMouseLock = "���콺 ���� ��ȯ";
    ls->shortcutEmuSpeedMax     = "�ִ� ���ķ��̼� �ӵ�";
    ls->shortcutEmuSpeedNormal  = "���� ���ķ��̼� �ӵ�";
    ls->shortcutEmuSpeedInc     = "���ķ��̼� �ӵ� ����";
    ls->shortcutEmuSpeedDec     = "���ķ��̼� �ӵ� ����";
    ls->shortcutShowEmuProp     = "���ķ��̼� �Ӽ� ����";
    ls->shortcutShowVideoProp   = "���� �Ӽ� ����";
    ls->shortcutShowAudioProp   = "����� �Ӽ� ����";
    ls->shortcutShowCtrlProp    = "��Ʈ�� �Ӽ� ����";
    ls->shortcutShowPerfProp    = "���� �Ӽ� ����";
    ls->shortcutShowSettProp    = "�ܺ� ���� �Ӽ� ����";
    ls->shortcutShowLanguage    = "��� ����";
    ls->shortcutShowMachines    = "�ӽ� ������ ����";
    ls->shortcutShowShortcuts   = "����Ű ������ ����";
    ls->shortcutShowHelp        = "���� ����";
    ls->shortcutShowAbout       = "blueMSX�� ���Ͽ� ����";
    
    ls->shortcutSpecialMenu1    = "īƮ���� 1 - ����� ���� īƮ����";
    ls->shortcutSpecialMenu2    = "īƮ���� 2 - ����� ���� īƮ����";
    ls->shortcutVolumeStereo    = "���/���׷��� ��ȯ";
    ls->shortcutThemeSwitch     = "�׸� ��ȯ";
    ls->shortcutToggleSpriteEnable = "��������Ʈ ���̱�/����� ��ȯ";
    
    ls->shortcutShowApearProp   = "�ܺ� �Ӽ� ����";
    ls->menuPropsApearance      = "�ܺ�";
    ls->propApearance           = "�ܺ�";
    ls->propThemeGB             = "�׸� ";
    ls->propTheme               = "�⺻ �׸�:";
    ls->propThemeClassic        = "����";
    ls->propThemeBlue           = "DIGIDIGI�Ķ�";

    ls->propMonBrightness       = "���:";
    ls->propMonContrast         = "����:";
    ls->propMonSaturation       = "ä��:";
    ls->propMonGamma            = "����:";
    ls->propMonScanlines        = " ��ĵ����:";

    ls->dlgRomType              = "�� ����:";
    ls->propOpenRomGB           = "���� �׻� ���� ���� ��� ";
    ls->propDefaultRomType      = "�⺻ �� ����:";
    ls->propGuessRomType        = "�ڵ� �Ǵ�";

    ls->propFile                = "����";
    ls->propSettDefSlotGB       = "���콺�� ��� ������ ";
    ls->propSettDefSlots        = "���� ���Կ� �� ����:";
    ls->propSettDefSlot1        = " ���� 1";
    ls->propSettDefSlot2        = " ���� 2";
    ls->propSettDefDrives       = "���� ����̺꿡 ���� ����:";
    ls->propSettDefDriveA       = " ����̺� A";
    ls->propSettDefDriveB       = " ����̺� B";
    ls->menuPropsFile           = "����";
    ls->shortcutShowFiles       = "���� �Ӽ� ����";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "���丮 ����";
    ls->shortcutDiskDirInsertA  = "���� A�� ���丮 ����";
    ls->shortcutDiskDirInsertB  = "���� B�� ���丮 ����";

    ls->propMonDeInterlace      = " �����ͷ��̽�";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "�Ͻ� ���� ����ġ";
    ls->shortcutSizeMinimized   = "������ �ּ�ȭ";
    ls->shortcutEmuSpeedToggle  = "���ķ��̼� �ӵ� �ִ�ȭ ��ȯ";
    ls->shortcutToggleCpuTrace  = "CPU Ʈ���̽� ��ȯ";

    ls->enumVideoEmuMonitor     = "�����";

    ls->propEmuPauseSwitch      = " �Ͻ� ���� ����ġ";
    ls->propVideoFreqText       = "���� ���ļ�:";
    ls->propVideoFreqAuto       = "�ڵ�";
    ls->propSndOversampleText   = "��������:";

    ls->confChipExtras          = "��Ÿ";
    ls->confBoardGB             = "�ý��� ";
    ls->confBoardText           = "�ý��� ����:";
    ls->dlgCpuFreqGB            = "CPU ���ļ� ";
    ls->dlgZ80FreqText          = "Z80 ���ļ�:";
    ls->dlgR800FreqText         = "R800 ���ļ�:";
    ls->dlgFdcGB                = "�÷��� ��ũ ��Ʈ�ѷ� ";
    ls->dlgCFdcNumDrivesText    = "����̺��� ����:";

    ls->propPriorityBoost        = " blueMSX�� �۾� �켱�� �ֱ�";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "�÷��� ����̺� Ÿ�̹� ��� ����";
    ls->shortcutToggleFdcTiming = "�÷��� ����̺� Ÿ�̹� ���/���� ��ȯ";
    ls->propUseRegistry         = "������Ʈ���� ���� ����";

    // New entries in 2.2
    ls->menuCartHBI55           = "Sony HBI-55 īƮ����";
    ls->propSndPcm              = " Turbo-R PCM";
    ls->propSndAY8910           = " AY8910 PSG";
    ls->propSndSN76489          = " SN76489 PSG";
    ls->enumVideoEmuHq2x        = "Hq2x";
    ls->propMonColorGhosting    = "RF-��ⷹ����";

    ls->keyconfigSelectedKey    = "���õ� Ű:";
    ls->keyconfigMappedTo       = "������ Ű:";
    ls->keyconfigMappingScheme  = "���� ��Ÿ��:";

    ls->discardChanges          = "������ ������ ����Ǳ� ���ؼ� ������ �ϼž� �մϴٸ� ���� �������� �ƹ��� ���⵵ �����ʰ� �׳� �����ڽ��ϱ�?";
    ls->overwriteConfig         = "�̹� ������ �ֽ��ϴ�. ���� ������ �� ���Ϸ� �ٲٽðڽ��ϱ�?";

    ls->confSaveAsTitle         = "�ٸ� �̸����� ���� ����...";
    ls->confSaveAsName          = "�̸�:";

    ls->menuToolsKeyboard       = "Ű���� ������";
    ls->shortcutShowKeyboard    = "Ű���� ������ ����";

    ls->menuVideoSource         = "���� �ҽ�";
    ls->menuVideoSourceDefault  = "���� �ҽ� ���� �ʵ�";
    ls->menuVideoChipAutodetect = "���� Ĩ �ڵ�����";
    ls->propFullscreenResText   = "��ü ȭ�� �ػ�:";
    ls->dlgSavePreview          = "�̸� ����";
    ls->dlgSaveDate             = "�ð� �����:";

    ls->enumVideoMonAmber       = "ȣ�ڻ�"; 

    ls->menuPropsPorts          = "��Ʈ"; 
    ls->propPortsLptGB          = "�з��� ��Ʈ "; 
    ls->propPortsComGB          = "�ø��� ��Ʈ "; 
    ls->propPortsLptText        = "��Ʈ:"; 
    ls->propPortsCom1Text       = "��Ʈ 1:";

    ls->shortcutShowDebugger    = "����� ����"; 
    ls->shortcutShowTrainer     = "Ʈ���̳� ����"; 
    ls->shortcutShowPorts       = "��Ʈ �Ӽ� ����";
};

#endif
