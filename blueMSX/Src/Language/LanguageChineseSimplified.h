/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageChineseSimplified.h,v $
**
** $Revision: 1.6 $
**
** $Date: 2006-06-03 17:55:54 $
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
#ifndef LANGUAGE_CHINESE_SIMPLIFIED_H
#define LANGUAGE_CHINESE_SIMPLIFIED_H

#include "LanguageStrings.h"
 
void langInitChineseSimplified(LanguageStrings* ls) 
{
    ls->noRecentFiles           = "- ��������ļ� -";
    ls->insert                  = "����";
    ls->eject                   = "����";
    
    ls->menuCartAutoReset       = "����/�Ƴ�������";
    ls->menuCartFMPac           = "FM-PAC ����";
    ls->menuCartPac             = "PAC ����";

    ls->menuDiskAutoStart       = "���������";
    
    ls->menuCasSetPosition      = "�Ŵ�λ������";
    ls->menuCasRewind           = "����";

    ls->menuZoomNormal          = "��׼�ߴ�";
    ls->menuZoomDouble          = "�����ߴ�";
    ls->menuZoomFullscreen      = "ȫ��Ļ";
    
    ls->menuPropsEmulation      = "ģ��";
    ls->menuPropsVideo          = "��Ƶ";
    ls->menuPropsSound          = "����";
    ls->menuPropsControls       = "������";
    ls->menuPropsPerformance    = "����";
    ls->menuPropsLanguage       = "����";
    
    ls->menuHelpHelp            = "��������";
    ls->menuHelpAbout           = "���� blueMSX";

    ls->menuFileCart            = "�������";
    ls->menuFileDisk            = "����������";
    ls->menuFileCas             = "�Ŵ���";
    ls->menuFileLoadState       = "��ȡ CPU ״̬";
    ls->menuFileSaveState       = "���� CPU ״̬";
    ls->menuFileQLoadState      = "���ٶ�ȡ";
    ls->menuFileQSaveState      = "���ٱ���";
    ls->menuFileCaptureAudio    = "¼��";
    ls->menuFileScreenShot      = "��ͼ";
    ls->menuFileExit            = "�˳�";

    ls->menuRunRun              = "����";
    ls->menuRunPause            = "��ͣ";
    ls->menuRunStop             = "ֹͣ";
    ls->menuRunSoftReset        = "�������";
    ls->menuRunHardReset        = "Ӳ������";
    ls->menuRunCleanReset       = "��������";

    ls->menuFile                = "�ļ�";
    ls->menuRun                 = "����";
    ls->menuWindow              = "����";
    ls->menuOptions             = "ѡ��";
    ls->menuHelp                = "����";
    
    ls->errorTitle              = "blueMSX - ����";
    ls->errorEnterFullscreen    = "�޷�����ȫ��ģʽ��           \n";
    ls->errorDirectXFailed      = "�޷����� DirectX ����           \n��Ϊʹ��GDI��\n�����Կ����á�";
    ls->errorNoRomInZip         = "�޷��� zip ѹ�������ҵ� .rom �ļ���";
    ls->errorNoDskInZip         = "�޷��� zip ѹ�������ҵ� .dsk �ļ���";
    ls->errorNoCasInZip         = "�޷��� zip ѹ�������ҵ� .cas �ļ���";
    ls->errorNoHelp             = "�޷��ҵ� blueMSX �����ļ���";
    ls->errorStartEmu           = "�޷����� MSX ģ������";

    ls->dlgLoadRom              = "blueMSX - ��ѡ�񿨴�ӳ��";
    ls->dlgLoadDsk              = "blueMSX - ��ѡ������ӳ��";
    ls->dlgLoadCas              = "blueMSX - ��ѡ��Ŵ�ӳ��";
    ls->dlgLoadRomDskCas        = "blueMSX - ��ѡ�񿨴������̻�Ŵ�ӳ��";
    ls->dlgLoadRomDesc          = "��ѡ��Ҫ��ȡ�Ŀ���ӳ��:";
    ls->dlgLoadDskDesc          = "��ѡ��Ҫ��ȡ������ӳ��:";
    ls->dlgLoadCasDesc          = "��ѡ��Ҫ��ȡ�ĴŴ�ӳ��:";
    ls->dlgLoadRomDskCasDesc    = "��ѡ��Ҫ��ȡ�Ŀ��������̻�Ŵ�ӳ��:";
    ls->dlgLoadState            = "��ȡ CPU ״̬";
    ls->dlgSaveState            = "���� CPU ״̬";
    ls->dlgInsertRom1           = "���ڲ�� 1 ���� ROM ����";
    ls->dlgInsertRom2           = "���ڲ�� 2 ���� ROM ����";
    ls->dlgInsertDiskA          = "���������� A ��������ӳ��";
    ls->dlgInsertDiskB          = "���������� B ��������ӳ��";
    ls->dlgInsertCas            = "�����Ŵ�";

    ls->dlgOK                   = "ȷ��";
    ls->dlgOpen                 = "��";
    ls->dlgCancel               = "ȡ��";

    ls->dlgTapeTitle            = "blueMSX - �Ŵ�";
    ls->dlgTapeFrameText        = "�Ŵ�λ��";
    ls->dlgTapeCurrentPos       = "��ǰλ��";
    ls->dlgTapeTotalTime        = "��ʱ��";

    ls->dlgZipReset             = "���������";

    ls->dlgAboutTitle           = "blueMSX - ����";

    ls->dlgLangLangText         = "��ѡ�� blueMSX ��ʹ������";
    ls->dlgLangLangTitle        = "blueMSX - ����";

    ls->propTitle               = "blueMSX - ����";
    ls->propEmulation           = "ģ��";
    ls->propVideo               = "��Ƶ";
    ls->propSound               = "����";
    ls->propControls            = "������";
    ls->propPerformance         = "����";
    
    ls->propEmuGeneralGB        = "���� ";
    ls->propEmuFamilyText       = "MSX ����:";
    ls->propEmuMemoryGB         = "�ڴ� ";
    ls->propEmuRamSizeText      = "���ڴ�:";
    ls->propEmuVramSizeText     = "�Դ�:";
    ls->propEmuSpeedGB          = "ģ���ٶ� ";
    ls->propEmuSpeedText        = "ģ���ٶ�:";

    ls->propMonMonGB            = "��ʾ�� ";
    ls->propMonTypeText         = "��ʾ������:";
    ls->propMonEmuText          = "��ʾ��ģ��:";
    ls->propVideoYypeText       = "��Ƶ����:";
    ls->propWindowSizeText      = "���ڴ�С:";

    ls->propPerfVideoDrvGB      = "��Ƶ���� ";
    ls->propPerfVideoDispDrvText= "��ʾ����:";
    ls->propPerfFrameSkipText   = "��֡:";
    ls->propPerfAudioDrvGB      = "��Ƶ���� ";
    ls->propPerfAudioDrvText    = "��������:";
    ls->propPerfAudioBufSzText  = "��������:";
    ls->propPerfEmuGB           = "ģ�� ";
    ls->propPerfSyncModeText    = "ͬ��ģʽ:";

    ls->propSndChipEmuGB        = "����оƬģ�� ";
    ls->propSndMixerGB          = "��Ƶ��Ƶ�� ";
    ls->propSndMonoText         = "������";
    ls->propSndStereoText       = "������";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "��Ҫ";

    ls->enumVideoMonColor       = "��ɫ";
    ls->enumVideoMonGrey        = "�ڰ�";
    ls->enumVideoMonGreen       = "��ɫ";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "��";
    ls->enumVideoEmuYc          = "Y/C �����· (����)";
    ls->enumVideoEmuYcBlur      = "���� Y/C �����· (����)";
    ls->enumVideoEmuComp        = "���� (ģ��)";
    ls->enumVideoEmuCompBlur    = "���븴�� (ģ��)";
    ls->enumVideoEmuScale2x     = "2 ���ữ";

    ls->enumVideoSize1x         = "��׼ - 320x200";
    ls->enumVideoSize2x         = "���� - 640x400";
    ls->enumVideoSizeFullscreen = "ȫ��Ļ";

    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "��";
    ls->enumVideoFrameskip1     = "1��֡";
    ls->enumVideoFrameskip2     = "2��֡";
    ls->enumVideoFrameskip3     = "3��֡";
    ls->enumVideoFrameskip4     = "4��֡";
    ls->enumVideoFrameskip5     = "5��֡";

    ls->enumSoundDrvNone        = "����";
    ls->enumSoundDrvWMM         = "WMM ����";
    ls->enumSoundDrvDirectX     = "DirectX ����";

    ls->enumControlsJoyNone     = "��";
    ls->enumControlsJoyMouse    = "���";

    ls->dlgAboutAbout           = "����\r\n====";
    ls->dlgAboutVersion         = "�汾:";
    ls->dlgAboutBuildNumber     = "����:";
    ls->dlgAboutBuildDate       = "����:";
    ls->dlgAboutCreat           = "����:	Daniel Vik";
    ls->dlgAboutDevel           = "��λЭ���Ŀ�������\r\n========";
    ls->dlgAboutThanks          = "�ر���л\r\n============";
    ls->dlgAboutLisence         = "��Ȩ\r\n"
                                  "======\r\n\r\n"
                                  "������Ǹ���Ŀǰ״���������ģ�û���κ���ȷ��Ĭ�����Ȩ�� "
                                  "���κ�����£�ʹ�ñ��������ɵĺ�������û��Լ��е��� "
                                  "���߽����е��κ����Ρ�\r\n\r\n"
                                  "�����������½: www.bluemsx.com ";

    // New entries
    ls->menuTools                = "����";
    ls->menuToolsMachine         = "�������ϱ༭";
    ls->menuPropsSettings        = "�趨";
    ls->menuCasRewindAfterInsert = "����󵹴�";
    ls->menuCasUseReadOnly       = "ʹ�ôŴ�ʱֻ��";
    ls->lmenuCasSaveAs           = "���Ϊ...";

    ls->dlgSaveCassette          = "blueMSX - ����Ŵ�ӳ��";
    ls->dlgTapeCustom            = "��ʾ�Զ����ļ�";
    ls->dlgTapeSetPosText        = "�Ŵ�λ��:";
    ls->dlgTabPosition           = "λ��";
    ls->dlgTabType               = "����";
    ls->dlgTabFilename           = "�ļ���";

    ls->propSettings             = "����";
    
    ls->propSetFileHistoryGB     = "��ʷ�ļ� ";
    ls->propSetFileHistorySize   = "��ʷ�ļ�������:";
    ls->propSetFileHistoryClear  = "�����ʷ�ļ�";
    ls->propSetScreenSaver       = " blueMSX ����ʱ�ر���Ļ����";

    ls->confTitle                = "blueMSX - �������ϱ༭����";
    ls->confSave                 = "����";
    ls->confSaveAs               = "���Ϊ...";
    ls->confRun                  = "����";
    ls->confClose                = "�ر�";
    ls->confConfigText           = "����";
    ls->confSlotLayout           = "�������";
    ls->confMemory               = "�ڴ�";
    ls->confChipEmulation        = "оƬģ��";

    ls->confSlotLayoutGB         = "������� ";
    ls->confSlotExtSlotGB        = "��չ��� ";
    ls->confSlotCart             = "����";
    ls->confSlotPrimary          = "��Ҫ";
    ls->confSlotExpanded         = "��չ ���ĸ��Ӳ�ۣ�";

    ls->confMemAdd               = "���...";
    ls->confMemEdit              = "�༭...";
    ls->confMemRemove            = "ɾ��";
    ls->confMemSlot              = "���";
    ls->confMemAddresss          = "��ַ";
    ls->confMemType              = "����";
    ls->confMemRomImage          = "Rom ӳ��";
    
    ls->confSaveTitle            = "blueMSX - ��������";
    ls->confSaveText             = "Ҫ����ԭ�еĻ���������:";

    ls->confChipVideoGB          = "��Ƶ ";
    ls->confChipVideoChip        = "��ʾоƬ:";
    ls->confChipVideoRam         = "��ʾ�ڴ�:";
    ls->confChipSoundGB          = "���� ";

    ls->slotEditMemTitle         = "blueMSX - �༭ Mapper";
    ls->slotEditMemGB            = "Mapper ��ϸ";
    ls->slotEditMemType          = "����:";
    ls->slotEditMemFile          = "�ļ�:";
    ls->slotEditMemAddress       = "��ַ";
    ls->slotEditMemSize          = "��С";
    ls->slotEditMemSlot          = "���";

    ls->confDiscardTitle         = "blueMSX - ����";
    ls->confExitSaveTitle        = "blueMSX - �˳��༭����";
    ls->confExitSaveText         = "Ҫ�����Ե�ǰ�ļ����޸���";

    ls->confSaveAsMachineTitle   = "blueMSX - �����������Ϊ...";
    ls->confSaveAsMachineName    = "��������:";

    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypes            = " �� blueMSX �����ļ� ( .rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " MSX ʹ������Χ�� Windows ������Ч"; 
    ls->propWindowsEnvGB         = "Windows �����趨 "; 
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW ����"; 
    ls->propMonHorizStretch      = " ˮƽ����";
    ls->propMonVertStretch       = " ��ֱ����";
    ls->propClearHistory         = "ȷ��Ҫ�����ʷ�ļ���";

    ls->propEmuFrontSwitchGB     = "Panasonic ���� ";
    ls->propEmuFrontSwitch       = " ǰ�˿���";
    ls->propEmuAudioSwitch       = " MSX-AUDIO ������";


    ls->dlgCmosGB                = "CMOS ";
    ls->dlgCmosEnable            = " ���� CMOS";
    ls->dlgCmosBattery           = " �������õ��";

    ls->menuCartSCCPlus         = "SCC+ ����";
    ls->menuCartSCC             = "SCC ����";
    
    ls->warningTitle             = "blueMSX - ����";

    // New entries in 1.5.1
    ls->menuToolsShortcuts      = "��ݼ��༭����";

    ls->shortcutSaveConfig      = "blueMSX - ��������";
    ls->shortcutOverwriteConfig = "Ҫ����ԭ�еĿ�ݼ�������:";
    ls->shortcutExitConfig      = "blueMSX - �˳���ݼ��༭����";
    ls->shortcutDiscardConfig   = "Ҫ�����Ե�ǰ�ļ����޸���";
    ls->shortcutSaveConfigAs    = "blueMSX - ��ݼ����Ϊ...";
    ls->shortcutConfigName      = "��������:";
    ls->shortcutNewProfile      = "< �½����� >";
    ls->shortcutConfigTitle     = "blueMSX - ��ݼ������༭����";
    ls->shortcutAssign          = "����";
    ls->shortcutPressText       = "�������ݼ�:";
    ls->shortcutScheme          = "ӳ�䷽��:";

    ls->shortcutCartInsert1     = "���뿨�� 1";
    ls->shortcutCartRemove1     = "�Ƴ����� 1";
    ls->shortcutCartInsert2     = "���뿨�� 2";
    ls->shortcutCartRemove2     = "�Ƴ����� 2";
    ls->shortcutCartAutoReset   = "�������������ģ����";
    ls->shortcutDiskInsertA     = "�������� A";
    ls->shortcutDiskRemoveA     = "�������� A";
    ls->shortcutDiskChangeA     = "�����л����� A";
    ls->shortcutDiskAutoResetA  = "���� A ���������ģ����";
    ls->shortcutDiskInsertB     = "�������� B";
    ls->shortcutDiskRemoveB     = "�������� B";
    ls->shortcutCasInsert       = "����Ŵ�";
    ls->shortcutCasEject        = "�����Ŵ�";
    ls->shortcutCasAutorewind   = "�����Ŵ��Զ�����";
    ls->shortcutCasReadOnly     = "�����Ŵ�ֻ��";
    ls->shortcutCasSetPosition  = "�趨�Ŵ�λ��";
    ls->shortcutCasRewind       = "����";
    ls->shortcutCasSave         = "����Ŵ�ӳ��";
    ls->shortcutCpuStateLoad    = "��ȡ CPU ״̬";
    ls->shortcutCpuStateSave    = "���� CPU ״̬";
    ls->shortcutCpuStateQload   = "���ٶ�ȡ CPU ״̬";
    ls->shortcutCpuStateQsave   = "���ٱ��� CPU ״̬";
    ls->shortcutAudioCapture    = "��ʼ/ֹͣ¼��";
    ls->shortcutScreenshotOrig  = "��Ļ��ͼ ��ԭʼ��";
    ls->shortcutScreenshotSmall = "��Ļ��ͼ ����׼��δ���ˣ�";
    ls->shortcutScreenshotLarge = "��Ļ��ͼ ��������δ���ˣ�";
    ls->shortcutQuit            = "�˳� blueMSX";
    ls->shortcutRunPause        = "����/��ͣģ��";
    ls->shortcutStop            = "ֹͣģ��";
    ls->shortcutResetHard       = "Ӳ������";
    ls->shortcutResetSoft       = "�������";
    ls->shortcutResetClean      = "��������";
    ls->shortcutSizeSmall       = "��Ϊ��׼����";
    ls->shortcutSizeNormal      = "��Ϊ��������";
    ls->shortcutSizeFullscreen  = "��Ϊȫ��Ļ";
    ls->shortcutToggleFullscren = "�л�ȫ��Ļ";
    ls->shortcutVolumeIncrease  = "��������";
    ls->shortcutVolumeDecrease  = "��С����";
    ls->shortcutVolumeMute      = "����";
    ls->shortcutSwitchMsxAudio  = "�л� MSX-AUDIO ������";
    ls->shortcutSwitchFront     = "�л� Panasonic ǰ�˿���";
    ls->shortcutToggleMouseLock = "�л��������";
    ls->shortcutEmuSpeedMax     = "�����ģ��";
    ls->shortcutEmuSpeedToggle  = "���������ģ��";
    ls->shortcutEmuSpeedNormal  = "����ģ���ٶ�";
    ls->shortcutEmuSpeedInc     = "�ӿ�ģ���ٶ�";
    ls->shortcutEmuSpeedDec     = "����ģ���ٶ�";
    ls->shortcutShowEmuProp     = "��ʾģ������";
    ls->shortcutShowVideoProp   = "��ʾ��Ƶ����";
    ls->shortcutShowAudioProp   = "��ʾ��Ƶ����";
    ls->shortcutShowCtrlProp    = "��ʾ��������";
    ls->shortcutShowPerfProp    = "��ʾ��������";
    ls->shortcutShowSettProp    = "��ʾ��������";
    ls->shortcutShowLanguage    = "��ʾ���ԶԻ���";
    ls->shortcutShowMachines    = "��ʾ�������ϱ༭����";
    ls->shortcutShowShortcuts   = "��ʾ��ݼ��༭����";
    ls->shortcutShowHelp        = "��ʾ�����Ի���";
    ls->shortcutShowAbout       = "��ʾ���ڶԻ���";
    
    ls->shortcutSpecialMenu1    = "Ϊ���� 1 ��ʾ�ر� Rom �˵�";
    ls->shortcutSpecialMenu2    = "Ϊ���� 2 ��ʾ�ر� Rom �˵�";
    ls->shortcutVolumeStereo    = "�л�������/������";
    ls->shortcutThemeSwitch     = "�л���������";
    ls->shortcutToggleSpriteEnable = "��ʾ/���ػ��";
    
    ls->shortcutShowApearProp   = "��ʾ�������";
    ls->menuPropsApearance      = "���";
    ls->propApearance           = "���";
    ls->propThemeGB             = "�������� ";
    ls->propTheme               = "��������:";

    ls->propMonBrightness       = "����:";
    ls->propMonContrast         = "�Աȶ�:";
    ls->propMonSaturation       = "���Ͷ�:";
    ls->propMonGamma            = "٤��ֵ:";
    ls->propMonScanlines        = " ɨ����:";

    ls->dlgRomType              = "Rom ����:";
    ls->propOpenRomGB           = "�� Rom �Ի��� ";
    ls->propDefaultRomType      = "Ĭ�� Rom ����:";
    ls->propGuessRomType        = "�²� Rom ����";

    ls->propFile                = "�ļ�";
    ls->propSettDefSlotGB       = "�Ϸ� ";
    ls->propSettDefSlots        = "���� Rom ��:";
    ls->propSettDefSlot         = " ���";
    ls->propSettDefDrives       = "�������̵�:";
    ls->propSettDefDrive        = " ������";
    ls->menuPropsFile           = "�ļ�";
    ls->shortcutShowFiles       = "��ʾ�ļ��趨";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "����Ŀ¼";
    ls->shortcutDiskDirInsertA  = "����Ŀ¼��Ϊ����A";
    ls->shortcutDiskDirInsertB  = "����Ŀ¼��Ϊ����B";
    ls->propMonDeInterlace      = " �߻��ʳ�������";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "�л���ͣ����";
    ls->shortcutSizeMinimized   = "��С������";
    ls->shortcutEmuSpeedToggle  = "���������ģ��";
    ls->shortcutToggleCpuTrace  = "����/���� CPU ����";

    ls->enumVideoEmuMonitor     = "��ʾ��";

    ls->propEmuPauseSwitch      = " ��ͣ����";
    ls->propVideoFreqText       = "��ƵƵ��:";
    ls->propVideoFreqAuto       = "�Զ�";
    ls->propSndOversampleText   = "������:";

    ls->confChipExtras          = "����";
    ls->confBoardGB             = "���� ";
    ls->confBoardText           = "��������:";
    ls->dlgCpuFreqGB            = "CPU Ƶ�� ";
    ls->dlgZ80FreqText          = "Z80 Ƶ��:";
    ls->dlgR800FreqText         = "R800 Ƶ��:";
    ls->dlgFdcGB                = "���̿����� ";
    ls->dlgCFdcNumDrivesText    = "����������:";

    ls->propPriorityBoost       = " ���� blueMSX �����ȼ�";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "����������������ʱ";
    ls->shortcutToggleFdcTiming = "����/����������������ʱ";

    // New entries in 2.2
    ls->menuCartHBI55           = "Sony HBI-55 ����";
    ls->propSndPcm              = " Turbo-R PCM ��Ƶ";
    ls->propSndAY8910           = " AY8910 PSG ��Ƶ";
    ls->propSndSN76489          = " SN76489 PSG ��Ƶ";
    ls->enumVideoEmuHq2x        = "Hq2x";
    ls->propMonColorGhosting    = " RF-������";

    ls->keyconfigSelectedKey    = "ѡ�м�:";
    ls->keyconfigMappedTo       = "ӳ�䵽:";
    ls->keyconfigMappingScheme  = "ӳ�䷽��:";

    ls->discardChanges          = "Ҫ�����޸���";
    ls->overwriteConfig         = "Ҫ���ǵ�ǰ��������";

    ls->confSaveAsTitle         = "�������Ϊ...";
    ls->confSaveAsName          = "����:";

    ls->menuToolsKeyboard       = "���̱༭����";
    ls->shortcutShowKeyboard    = "��ʾ���̱༭����";

    ls->menuVideoSource         = "��Ƶ��Դ";
    ls->menuVideoSourceDefault  = "δ������Ƶ��Դ";
    ls->menuVideoChipAutodetect = "�Զ������ʾоƬ";
    ls->propFullscreenResText   = "ȫ��Ļ�ֱ���:";
    ls->dlgSavePreview          = "��ʾԤ��";
    ls->dlgSaveDate             = "����ʱ��:";
    
    ls->enumVideoMonAmber       = "��ɫ";

    ls->menuPropsPorts          = "�˿�";
    ls->propPortsLptGB          = "���ж˿� ";
    ls->propPortsComGB          = "���ж˿� ";
    ls->propPortsLptText        = "�˿�:";
    ls->propPortsCom1Text       = "�˿� 1:";

    ls->shortcutShowDebugger    = "��ʾ���Թ���";
    ls->shortcutShowTrainer     = "��ʾ�޸Ĺ���";
    ls->shortcutShowPorts       = "��ʾ�˿��趨";
    
    ls->propPorts               = "�˿�";
    ls->propPortsNone           = "��";

    // New entries in 2.3
    ls->enumControlsJoyTetris2Dongle = "����˹���� 2 ����ģ��";

    ls->propPortsSimplCovox     = "SiMPL/Covox ��ģת����";
    ls->propPortsFile           = "��ӡ���ļ�";
    ls->propPortsOpenLogFile    = "�򿪼�¼�ļ�";
    ls->propPortsFilenameText   = "�ļ���:";
    ls->propPortsEmulateMsxPrn  = "ģ��:";

    ls->shortcutPrnFormFeed     = "��ӡ����ҳ";

    ls->menuPrnFormfeed         = "��ҳ";
    ls->menuFilePrn             = "��ӡ��";
    ls->propPortsComFile        = "���͵��ļ�";

    // New entries in 2.4
    ls->shortcutShowMixer       = "��ʾ������";
    ls->menuToolsMixer          = "������";
    
    ls->propSndMidiInGB         = "MIDI ���� ";
    ls->propSndMidiOutGB        = "MIDI ��� ";
    ls->propSndMt32ToGmText     = " ӳ�� MT-32 ����Ϊһ�� MIDI �豸";

    ls->textDevice              = "�豸:";
    ls->textFilename            = "�ļ���:";
    ls->textFile                = "�ļ�";
    ls->textNone                = "��";

    ls->enumEmuSyncNone         = "��";
    ls->enumEmuSyncAuto         = "�Զ� (����)";
    ls->enumEmuSync1ms          = "ͬ���� MSX ��ˢ��";
    ls->enumEmuSyncVblank       = "ͬ���� PC �Ĵ�ֱ�հ�";

    ls->propMonEffectsGB        = "��Ч";

    ls->confSlot                = "���";
    ls->confSubslot             = "�Ӳ��";

    ls->shortcut                = "��ݼ�";
    ls->hotkey                  = "�ȼ�";
    ls->unknown                 = "δ֪";
    ls->romImage                = "ROM ӳ��";
    ls->romImageOpen            = "�� ROM ӳ��";
    ls->romCartridge            = "ROM ����";
    ls->allFiles                = "�����ļ�";
    ls->cpuState                = "CPU ״̬";
    ls->diskImage               = "����ӳ��";
    ls->casImage                = "�Ŵ�ӳ��";

    ls->menuCartExternalRam     = "��չ�ڴ�";
};


#endif

