/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageChineseSimplified.h,v $
**
** $Revision: 1.13 $
**
** $Date: 2006-06-06 04:58:43 $
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
    //----------------------
    // Generic lines
    //----------------------

    ls->textDevice              = "�豸:";
    ls->textFilename            = "�ļ���:";
    ls->textFile                = "�ļ�";
    ls->textNone                = "��";
    ls->textUnknown             = "Unknown";                            // New in 2.5


    //----------------------
    // Warning and Error lines
    //----------------------

    ls->warningTitle             = "blueMSX - ����";
    ls->warningDiscardChanges   = "Ҫ�����޸���";
    ls->warningOverwriteFile    = "Do you want to overwrite the file:"; // New in 2.5
    ls->errorTitle              = "blueMSX - ����";
    ls->errorEnterFullscreen    = "�޷�����ȫ��ģʽ��           \n";
    ls->errorDirectXFailed      = "�޷����� DirectX ����           \n��Ϊʹ��GDI��\n�����Կ����á�";
    ls->errorNoRomInZip         = "�޷��� zip ѹ�������ҵ� .rom �ļ���";
    ls->errorNoDskInZip         = "�޷��� zip ѹ�������ҵ� .dsk �ļ���";
    ls->errorNoCasInZip         = "�޷��� zip ѹ�������ҵ� .cas �ļ���";
    ls->errorNoHelp             = "�޷��ҵ� blueMSX �����ļ���";
    ls->errorStartEmu           = "�޷����� MSX ģ������";
    ls->errorPortableReadonly   = "Portable device is readonly";        // New in 2.5


    //----------------------
    // File related lines
    //----------------------

    ls->fileRom                 = "ROM ӳ��";
    ls->fileAll                 = "�����ļ�";
    ls->fileCpuState            = "CPU ״̬";
    ls->fileDisk                = "����ӳ��";
    ls->fileCas                 = "�Ŵ�ӳ��";


    //----------------------
    // Menu related lines
    //----------------------

    ls->menuNoRecentFiles       = "- ��������ļ� -";
    ls->menuInsert              = "����";
    ls->menuEject               = "����";
    
    ls->menuCartGameReader      = "Game Reader";                        // New in 2.5
    ls->menuCartIde             = "IDE";                                // New in 2.5
    ls->menuCartBeerIde         = "Beer";                               // New in 2.5
    ls->menuCartGIde            = "GIDE";                               // New in 2.5
    ls->menuCartSunriseIde      = "Sunrise";                            // New in 2.5
    ls->menuCartSCCPlus         = "SCC+ ����";
    ls->menuCartSCC             = "SCC ����";
    ls->menuCartFMPac           = "FM-PAC ����";
    ls->menuCartPac             = "PAC ����";
    ls->menuCartHBI55           = "Sony HBI-55 ����";
    ls->menuCartInsertSpecial   = "Insert Special";                     // New in 2.5
    ls->menuCartMegaRam         = "MegaRAM";                            // New in 2.5
    ls->menuCartExternalRam     = "��չ�ڴ�";

    ls->menuDiskInsertNew       = "Insert New Disk Image";              // New in 2.5
    ls->menuDiskDirInsert       = "����Ŀ¼";
    ls->menuDiskAutoStart       = "���������";
    ls->menuCartAutoReset       = "����/�Ƴ�������";

    ls->menuCasRewindAfterInsert = "����󵹴�";
    ls->menuCasUseReadOnly       = "ʹ�ôŴ�ʱֻ��";
    ls->lmenuCasSaveAs           = "���Ϊ...";
    ls->menuCasSetPosition      = "�Ŵ�λ������";
    ls->menuCasRewind           = "����";

    ls->menuZoomNormal          = "��׼�ߴ�";
    ls->menuZoomDouble          = "�����ߴ�";
    ls->menuZoomFullscreen      = "ȫ��Ļ";
    
    ls->menuPrnFormfeed         = "��ҳ";
    
    ls->menuPropsEmulation      = "ģ��";
    ls->menuPropsVideo          = "��Ƶ";
    ls->menuPropsSound          = "����";
    ls->menuPropsControls       = "������";
    ls->menuPropsPerformance    = "����";
    ls->menuPropsSettings        = "�趨";
    ls->menuPropsFile           = "�ļ�";
    ls->menuPropsLanguage       = "����";
    ls->menuPropsPorts          = "�˿�";
    
    ls->menuVideoSource         = "Video Out Source";                   // New in 2.5
    ls->menuVideoSourceDefault  = "No Video Out Source Connected";      // New in 2.5
    ls->menuVideoChipAutodetect = "�Զ������ʾоƬ";
    ls->menuVideoInSource       = "Video In Source";                    // New in 2.5
    ls->menuVideoInBitmap       = "Bitmap File";                        // New in 2.5

    ls->menuHelpHelp            = "��������";
    ls->menuHelpAbout           = "���� blueMSX";

    ls->menuFileCart            = "�������";
    ls->menuFileDisk            = "����������";
    ls->menuFileCas             = "�Ŵ���";
    ls->menuFilePrn             = "��ӡ��";
    ls->menuFileLoadState       = "��ȡ CPU ״̬";
    ls->menuFileSaveState       = "���� CPU ״̬";
    ls->menuFileQLoadState      = "���ٶ�ȡ";
    ls->menuFileQSaveState      = "���ٱ���";
    ls->menuFileCaptureAudio    = "¼��";
    ls->menuFileScreenShot      = "��ͼ";
    ls->menuFileExit            = "�˳�";

    ls->menuFileHarddisk        = "Hard Disk";                          // New in 2.5
    ls->menuFileHarddiskNoPesent= "No Controllers Present";             // New in 2.5

    ls->menuRunRun              = "����";
    ls->menuRunPause            = "��ͣ";
    ls->menuRunStop             = "ֹͣ";
    ls->menuRunSoftReset        = "�������";
    ls->menuRunHardReset        = "Ӳ������";
    ls->menuRunCleanReset       = "��������";

    ls->menuToolsMachine         = "�������ϱ༭";
    ls->menuToolsShortcuts      = "��ݼ��༭����";
    ls->menuToolsKeyboard       = "���̱༭����";
    ls->menuToolsMixer          = "������";

    ls->menuFile                = "�ļ�";
    ls->menuRun                 = "����";
    ls->menuWindow              = "����";
    ls->menuOptions             = "ѡ��";
    ls->menuTools                = "����";
    ls->menuHelp                = "����";


    //----------------------
    // Dialog related lines
    //----------------------

    ls->dlgOK                   = "ȷ��";
    ls->dlgOpen                 = "��";
    ls->dlgCancel               = "ȡ��";
    ls->dlgSave                 = "����";
    ls->dlgSaveAs               = "���Ϊ...";
    ls->dlgRun                  = "����";
    ls->dlgClose                = "�ر�";

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
    ls->dlgSaveCassette          = "blueMSX - ����Ŵ�ӳ��";
    ls->dlgInsertRom1           = "���ڲ�� 1 ���� ROM ����";
    ls->dlgInsertRom2           = "���ڲ�� 2 ���� ROM ����";
    ls->dlgInsertDiskA          = "���������� A ��������ӳ��";
    ls->dlgInsertDiskB          = "���������� B ��������ӳ��";
    ls->dlgInsertHarddisk       = "Insert Hard Disk";                   // New in 2.5
    ls->dlgInsertCas            = "�����Ŵ�";
    ls->dlgRomType              = "Rom ����:";

    ls->dlgTapeTitle            = "blueMSX - �Ŵ�";
    ls->dlgTapeFrameText        = "�Ŵ�λ��";
    ls->dlgTapeCurrentPos       = "��ǰλ��";
    ls->dlgTapeTotalTime        = "��ʱ��";
    ls->dlgTapeCustom            = "��ʾ�Զ����ļ�";
    ls->dlgTapeSetPosText        = "�Ŵ�λ��:";
    ls->dlgTabPosition           = "λ��";
    ls->dlgTabType               = "����";
    ls->dlgTabFilename           = "�ļ���";
    ls->dlgZipReset             = "���������";

    ls->dlgAboutTitle           = "blueMSX - ����";

    ls->dlgLangLangText         = "��ѡ�� blueMSX ��ʹ������";
    ls->dlgLangLangTitle        = "blueMSX - ����";

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

    ls->dlgSavePreview          = "��ʾԤ��";
    ls->dlgSaveDate             = "����ʱ��:";


    //----------------------
    // Properties related lines
    //----------------------

    ls->propTitle               = "blueMSX - ����";
    ls->propEmulation           = "ģ��";
    ls->propVideo               = "��Ƶ";
    ls->propSound               = "����";
    ls->propControls            = "������";
    ls->propPerformance         = "����";
    ls->propSettings             = "����";
    ls->propFile                = "�ļ�";
    ls->propPorts               = "�˿�";
    
    ls->propEmuGeneralGB        = "���� ";
    ls->propEmuFamilyText       = "MSX ����:";
    ls->propEmuMemoryGB         = "�ڴ� ";
    ls->propEmuRamSizeText      = "���ڴ�:";
    ls->propEmuVramSizeText     = "�Դ�:";
    ls->propEmuSpeedGB          = "ģ���ٶ� ";
    ls->propEmuSpeedText        = "ģ���ٶ�:";
    ls->propEmuFrontSwitchGB     = "Panasonic ���� ";
    ls->propEmuFrontSwitch       = " ǰ�˿���";
    ls->propEmuFdcTiming        = "����������������ʱ";
    ls->propEmuPauseSwitch      = " ��ͣ����";
    ls->propEmuAudioSwitch       = " MSX-AUDIO ������";
    ls->propVideoFreqText       = "��ƵƵ��:";
    ls->propVideoFreqAuto       = "�Զ�";
    ls->propSndOversampleText   = "������:";
    ls->propSndMidiInGB         = "MIDI ���� ";
    ls->propSndMidiOutGB        = "MIDI ��� ";

    ls->propMonMonGB            = "��ʾ�� ";
    ls->propMonTypeText         = "��ʾ������:";
    ls->propMonEmuText          = "��ʾ��ģ��:";
    ls->propVideoTypeText       = "��Ƶ����:";
    ls->propWindowSizeText      = "���ڴ�С:";
    ls->propMonHorizStretch      = " ˮƽ����";
    ls->propMonVertStretch       = " ��ֱ����";
    ls->propMonDeInterlace      = " �߻��ʳ�������";
    ls->propMonBrightness       = "����:";
    ls->propMonContrast         = "�Աȶ�:";
    ls->propMonSaturation       = "���Ͷ�:";
    ls->propMonGamma            = "٤��ֵ:";
    ls->propMonScanlines        = " ɨ����:";
    ls->propMonColorGhosting    = " RF-������";
    ls->propMonEffectsGB        = "��Ч";

    ls->propPerfVideoDrvGB      = "��Ƶ���� ";
    ls->propPerfVideoDispDrvText= "��ʾ����:";
    ls->propPerfFrameSkipText   = "��֡:";
    ls->propPerfAudioDrvGB      = "��Ƶ���� ";
    ls->propPerfAudioDrvText    = "��������:";
    ls->propPerfAudioBufSzText  = "��������:";
    ls->propPerfEmuGB           = "ģ�� ";
    ls->propPerfSyncModeText    = "ͬ��ģʽ:";
    ls->propFullscreenResText   = "ȫ��Ļ�ֱ���:";

    ls->propSndChipEmuGB        = "����оƬģ�� ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";
    ls->propSndMoonsound         = " Moonsound";
    ls->propSndMt32ToGm         = " ӳ�� MT-32 ����Ϊһ�� MIDI �豸";

    ls->propPortsLptGB          = "���ж˿� ";
    ls->propPortsComGB          = "���ж˿� ";
    ls->propPortsLptText        = "�˿�:";
    ls->propPortsCom1Text       = "�˿� 1:";
    ls->propPortsNone           = "��";
    ls->propPortsSimplCovox     = "SiMPL/Covox ��ģת����";
    ls->propPortsFile           = "��ӡ���ļ�";
    ls->propPortsComFile        = "���͵��ļ�";
    ls->propPortsOpenLogFile    = "�򿪼�¼�ļ�";
    ls->propPortsEmulateMsxPrn  = "ģ��:";

    ls->propSetFileHistoryGB     = "��ʷ�ļ� ";
    ls->propSetFileHistorySize   = "��ʷ�ļ�������:";
    ls->propSetFileHistoryClear  = "�����ʷ�ļ�";
    ls->propFileTypes            = " �� blueMSX �����ļ� ( .rom, .dsk, .cas, .sta)";
    ls->propWindowsEnvGB         = "Windows �����趨 "; 
    ls->propSetScreenSaver       = " blueMSX ����ʱ�ر���Ļ����";
    ls->propDisableWinKeys       = " MSX ʹ������Χ�� Windows ������Ч"; 
    ls->propPriorityBoost       = " ���� blueMSX �����ȼ�";
    ls->propScreenshotPng       = " Use Portable Network Graphics (.png) screenshots";  // New in 2.5
    ls->propClearHistory         = "ȷ��Ҫ�����ʷ�ļ���";
    ls->propOpenRomGB           = "�� Rom �Ի��� ";
    ls->propDefaultRomType      = "Ĭ�� Rom ����:";
    ls->propGuessRomType        = "�²� Rom ����";

    ls->propSettDefSlotGB       = "�Ϸ� ";
    ls->propSettDefSlots        = "���� Rom ��:";
    ls->propSettDefSlot         = " ���";
    ls->propSettDefDrives       = "�������̵�:";
    ls->propSettDefDrive        = " ������";

    ls->propThemeGB             = "�������� ";
    ls->propTheme               = "��������:";


    //----------------------
    // Dropdown related lines
    //----------------------

    ls->enumVideoMonColor       = "��ɫ";
    ls->enumVideoMonGrey        = "�ڰ�";
    ls->enumVideoMonGreen       = "��ɫ";
    ls->enumVideoMonAmber       = "��ɫ";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "��";
    ls->enumVideoEmuYc          = "Y/C �����· (����)";
    ls->enumVideoEmuMonitor     = "��ʾ��";
    ls->enumVideoEmuYcBlur      = "���� Y/C �����· (����)";
    ls->enumVideoEmuComp        = "���� (ģ��)";
    ls->enumVideoEmuCompBlur    = "���븴�� (ģ��)";
    ls->enumVideoEmuScale2x     = "2 ���ữ";
    ls->enumVideoEmuHq2x        = "Hq2x";

    ls->enumVideoSize1x         = "��׼ - 320x200";
    ls->enumVideoSize2x         = "���� - 640x400";
    ls->enumVideoSizeFullscreen = "ȫ��Ļ";

    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW ����"; 
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

    ls->enumEmuSync1ms          = "ͬ���� MSX ��ˢ��";
    ls->enumEmuSyncAuto         = "�Զ� (����)";
    ls->enumEmuSyncNone         = "��";
    ls->enumEmuSyncVblank       = "ͬ���� PC �Ĵ�ֱ�հ�";

    ls->enumControlsJoyNone     = "��";
    ls->enumControlsJoyMouse    = "���";
    ls->enumControlsJoyTetris2Dongle = "����˹���� 2 ����ģ��";
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey Dongle";             // New in 2.5


    //----------------------
    // Configuration related lines
    //----------------------

    ls->confTitle                = "blueMSX - �������ϱ༭����";
    ls->confConfigText           = "����";
    ls->confSlotLayout           = "�������";
    ls->confMemory               = "�ڴ�";
    ls->confChipEmulation        = "оƬģ��";
    ls->confChipExtras          = "����";

    ls->confOpenRom             = "�� ROM ӳ��";
    ls->confSaveTitle            = "blueMSX - ��������";
    ls->confSaveText             = "Ҫ����ԭ�еĻ���������:";
    ls->confSaveAsTitle         = "�������Ϊ...";
    ls->confSaveAsMachineName    = "��������:";
    ls->confDiscardTitle         = "blueMSX - ����";
    ls->confExitSaveTitle        = "blueMSX - �˳��༭����";
    ls->confExitSaveText         = "Ҫ�����Ե�ǰ�ļ����޸���";

    ls->confSlotLayoutGB         = "������� ";
    ls->confSlotExtSlotGB        = "��չ��� ";
    ls->confBoardGB             = "���� ";
    ls->confBoardText           = "��������:";
    ls->confSlotPrimary          = "��Ҫ";
    ls->confSlotExpanded         = "��չ ���ĸ��Ӳ�ۣ�";

    ls->confSlotCart             = "����";
    ls->confSlot                = "���";
    ls->confSubslot             = "�Ӳ��";

    ls->confMemAdd               = "���...";
    ls->confMemEdit              = "�༭...";
    ls->confMemRemove            = "ɾ��";
    ls->confMemSlot              = "���";
    ls->confMemAddresss          = "��ַ";
    ls->confMemType              = "����";
    ls->confMemRomImage          = "Rom ӳ��";
    
    ls->confChipVideoGB          = "��Ƶ ";
    ls->confChipVideoChip        = "��ʾоƬ:";
    ls->confChipVideoRam         = "��ʾ�ڴ�:";
    ls->confChipSoundGB          = "���� ";

    ls->confCmosGB                = "CMOS ";
    ls->confCmosEnable            = " ���� CMOS";
    ls->confCmosBattery           = " �������õ��";

    ls->confCpuFreqGB            = "CPU Ƶ�� ";
    ls->confZ80FreqText          = "Z80 Ƶ��:";
    ls->confR800FreqText         = "R800 Ƶ��:";
    ls->confFdcGB                = "���̿����� ";
    ls->confCFdcNumDrivesText    = "����������:";

    ls->confEditMemTitle         = "blueMSX - �༭ Mapper";
    ls->confEditMemGB            = "Mapper ��ϸ";
    ls->confEditMemType          = "����:";
    ls->confEditMemFile          = "�ļ�:";
    ls->confEditMemAddress       = "��ַ";
    ls->confEditMemSize          = "��С";
    ls->confEditMemSlot          = "���";


    //----------------------
    // Shortcut lines
    //----------------------

    ls->shortcutKey             = "�ȼ�";
    ls->shortcutDescription     = "��ݼ�";

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
    ls->shortcutSpecialMenu1    = "Ϊ���� 1 ��ʾ�ر� Rom �˵�";
    ls->shortcutSpecialMenu2    = "Ϊ���� 2 ��ʾ�ر� Rom �˵�";
    ls->shortcutCartAutoReset   = "�������������ģ����";
    ls->shortcutDiskInsertA     = "�������� A";
    ls->shortcutDiskDirInsertA  = "����Ŀ¼��Ϊ����A";
    ls->shortcutDiskRemoveA     = "�������� A";
    ls->shortcutDiskChangeA     = "�����л����� A";
    ls->shortcutDiskAutoResetA  = "���� A ���������ģ����";
    ls->shortcutDiskInsertB     = "�������� B";
    ls->shortcutDiskDirInsertB  = "����Ŀ¼��Ϊ����B";
    ls->shortcutDiskRemoveB     = "�������� B";
    ls->shortcutCasInsert       = "����Ŵ�";
    ls->shortcutCasEject        = "�����Ŵ�";
    ls->shortcutCasAutorewind   = "�����Ŵ��Զ�����";
    ls->shortcutCasReadOnly     = "�����Ŵ�ֻ��";
    ls->shortcutCasSetPosition  = "�趨�Ŵ�λ��";
    ls->shortcutCasRewind       = "����";
    ls->shortcutCasSave         = "����Ŵ�ӳ��";
    ls->shortcutPrnFormFeed     = "��ӡ����ҳ";
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
    ls->shortcutSizeMinimized   = "��С������";
    ls->shortcutToggleFullscren = "�л�ȫ��Ļ";
    ls->shortcutVolumeIncrease  = "��������";
    ls->shortcutVolumeDecrease  = "��С����";
    ls->shortcutVolumeMute      = "����";
    ls->shortcutVolumeStereo    = "�л�������/������";
    ls->shortcutSwitchMsxAudio  = "�л� MSX-AUDIO ������";
    ls->shortcutSwitchFront     = "�л� Panasonic ǰ�˿���";
    ls->shortcutSwitchPause     = "�л���ͣ����";
    ls->shortcutToggleMouseLock = "�л��������";
    ls->shortcutEmuSpeedMax     = "�����ģ��";
    ls->shortcutEmuSpeedToggle  = "���������ģ��";
    ls->shortcutEmuSpeedNormal  = "����ģ���ٶ�";
    ls->shortcutEmuSpeedInc     = "�ӿ�ģ���ٶ�";
    ls->shortcutEmuSpeedDec     = "����ģ���ٶ�";
    ls->shortcutThemeSwitch     = "�л���������";
    ls->shortcutShowEmuProp     = "��ʾģ������";
    ls->shortcutShowVideoProp   = "��ʾ��Ƶ����";
    ls->shortcutShowAudioProp   = "��ʾ��Ƶ����";
    ls->shortcutShowCtrlProp    = "��ʾ��������";
    ls->shortcutShowPerfProp    = "��ʾ��������";
    ls->shortcutShowSettProp    = "��ʾ��������";
    ls->shortcutShowPorts       = "��ʾ�˿��趨";
    ls->shortcutShowLanguage    = "��ʾ���ԶԻ���";
    ls->shortcutShowMachines    = "��ʾ�������ϱ༭����";
    ls->shortcutShowShortcuts   = "��ʾ��ݼ��༭����";
    ls->shortcutShowKeyboard    = "��ʾ���̱༭����";
    ls->shortcutShowDebugger    = "��ʾ���Թ���";
    ls->shortcutShowTrainer     = "��ʾ�޸Ĺ���";
    ls->shortcutShowMixer       = "��ʾ������";
    ls->shortcutShowHelp        = "��ʾ�����Ի���";
    ls->shortcutShowAbout       = "��ʾ���ڶԻ���";
    ls->shortcutShowFiles       = "��ʾ�ļ��趨";
    ls->shortcutToggleSpriteEnable = "��ʾ/���ػ��";
    ls->shortcutToggleFdcTiming = "����/����������������ʱ";
    ls->shortcutToggleCpuTrace  = "����/���� CPU ����";


    //----------------------
    // Keyboard config lines
    //----------------------
    
    ls->keyconfigSelectedKey    = "ѡ�м�:";
    ls->keyconfigMappedTo       = "ӳ�䵽:";
    ls->keyconfigMappingScheme  = "ӳ�䷽��:";
};

#endif
