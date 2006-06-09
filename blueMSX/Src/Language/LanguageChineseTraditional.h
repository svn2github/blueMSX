/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageChineseTraditional.h,v $
**
** $Revision: 1.14 $
**
** $Date: 2006-06-09 20:30:02 $
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
    //----------------------
    // Generic lines
    //----------------------

    ls->textDevice              = "�˸m:";
    ls->textFilename            = "�ɮצW��:";
    ls->textFile                = "�ɮ�";
    ls->textNone                = "�L";
    ls->textUnknown             = "Unknown";                            // New in 2.5


    //----------------------
    // Warning and Error lines
    //----------------------

    ls->warningTitle             = "blueMSX - ĵ�i";
    ls->warningDiscardChanges   = "�z�T�w�n����ܧ�ܡH";
    ls->warningOverwriteFile    = "Do you want to overwrite the file:"; // New in 2.5
    ls->errorTitle              = "blueMSX - ���~";
    ls->errorEnterFullscreen    = "�L�k�i�J���ù��Ҧ��C           \n";
    ls->errorDirectXFailed      = "�L�k�إ� DirectX ����C           \n���N���ϥ� GDI�C\n���ˬd���T���e�C";
    ls->errorNoRomInZip         = "�L�k�b zip ���Y�ɮפ���X .rom �ɮסC";
    ls->errorNoDskInZip         = "�L�k�b zip ���Y�ɮפ���X .dsk �ɮסC";
    ls->errorNoCasInZip         = "�L�k�b zip ���Y�ɮפ���X .cas �ɮסC";
    ls->errorNoHelp             = "�L�k��� blueMSX �����ɮסC";
    ls->errorStartEmu           = "�L�k�Ұ� MSX �������C";
    ls->errorPortableReadonly   = "Portable device is readonly";        // New in 2.5


    //----------------------
    // File related lines
    //----------------------

    ls->fileRom                 = "ROM �M����";
    ls->fileAll                 = "�Ҧ��ɮ�";
    ls->fileCpuState            = "CPU ���A";
    ls->fileDisk                = "�ϺЬM����";
    ls->fileCas                 = "�ϱa�M����";


    //----------------------
    // Menu related lines
    //----------------------

    ls->menuNoRecentFiles       = "- �S���̪��ɮ� -";
    ls->menuInsert              = "���J";
    ls->menuEject               = "�h�X";

    ls->menuCartGameReader      = "Game Reader";                        // New in 2.5
    ls->menuCartIde             = "IDE";                                // New in 2.5
    ls->menuCartBeerIde         = "Beer";                               // New in 2.5
    ls->menuCartGIde            = "GIDE";                               // New in 2.5
    ls->menuCartSunriseIde      = "Sunrise";                            // New in 2.5
    ls->menuCartSCCPlus         = "SCC + �d�X";
    ls->menuCartSCC             = "SCC �d�X";
    ls->menuCartFMPac           = "FM-PAC �d�X";
    ls->menuCartPac             = "PAC �d�X";
    ls->menuCartHBI55           = "SONY HBI-55 �d�X";
    ls->menuCartInsertSpecial   = "Insert Special";                     // New in 2.5
    ls->menuCartMegaRam         = "MegaRAM";                            // New in 2.5
    ls->menuCartExternalRam     = "�~�� RAM";

    ls->menuDiskInsertNew       = "Insert New Disk Image";              // New in 2.5
    ls->menuDiskDirInsert       = "���J�ؿ�";
    ls->menuDiskAutoStart       = "���J���᭫�m";
    ls->menuCartAutoReset       = "���J/�������᭫�m";
    
    ls->menuCasRewindAfterInsert = "���J����j�a";
    ls->menuCasUseReadOnly       = "�ϥκϱa�M���ɰ�Ū";
    ls->lmenuCasSaveAs           = "�t�s�ϱa�M���ɬ�...";
    ls->menuCasSetPosition      = "�]�w��m";
    ls->menuCasRewind           = "�j�a";

    ls->menuPrnFormfeed         = "����";

    ls->menuZoomNormal          = "�@��j�p";
    ls->menuZoomDouble          = "�⭿�j�p";
    ls->menuZoomFullscreen      = "���ù�";
    
    ls->menuPropsEmulation      = "����";
    ls->menuPropsVideo          = "���T";
    ls->menuPropsSound          = "����";
    ls->menuPropsControls       = "���";
    ls->menuPropsPerformance    = "�į�";
    ls->menuPropsSettings        = "�]�w";
    ls->menuPropsFile           = "�ɮ�";
    ls->menuPropsLanguage       = "�y��";
    ls->menuPropsPorts          = "�s����";
    
    ls->menuVideoSource         = "Video Out Source";                   // New in 2.5
    ls->menuVideoSourceDefault  = "No Video Out Source Connected";      // New in 2.5
    ls->menuVideoChipAutodetect = "�۰ʰ������T����";
    ls->menuVideoInSource       = "Video In Source";                    // New in 2.5
    ls->menuVideoInBitmap       = "Bitmap File";                        // New in 2.5

    ls->menuHelpHelp            = "�����D�D";
    ls->menuHelpAbout           = "���� blueMSX";

    ls->menuFileCart            = "�d�X����";
    ls->menuFileDisk            = "�Ϻо�";
    ls->menuFileCas             = "�ϱa��";
    ls->menuFilePrn             = "�L���";
    ls->menuFileLoadState       = "���J CPU ���A";
    ls->menuFileSaveState       = "�x�s CPU ���A";
    ls->menuFileQLoadState      = "�ֳt���J���A";
    ls->menuFileQSaveState      = "�ֳt�x�s���A";
    ls->menuFileCaptureAudio    = "�^�����T";
    ls->menuFileScreenShot      = "�x�s�ù����";
    ls->menuFileExit            = "����";

    ls->menuFileHarddisk        = "Hard Disk";                          // New in 2.5
    ls->menuFileHarddiskNoPesent= "No Controllers Present";             // New in 2.5

    ls->menuRunRun              = "����";
    ls->menuRunPause            = "�Ȱ�";
    ls->menuRunStop             = "����";
    ls->menuRunSoftReset        = "�n�魫�m";
    ls->menuRunHardReset        = "�w�魫�m";
    ls->menuRunCleanReset       = "�@�뭫�m";

    ls->menuToolsMachine        = "���ؽs�边";
    ls->menuToolsShortcuts      = "�ֳt��s�边";
    ls->menuToolsKeyboard       = "��L�s�边";
    ls->menuToolsMixer          = "�V�X��";

    ls->menuFile                = "�ɮ�";
    ls->menuRun                 = "����";
    ls->menuWindow              = "����";
    ls->menuOptions             = "�ﶵ";
    ls->menuTools               = "�u��";
    ls->menuHelp                = "����";


    //----------------------
    // Dialog related lines
    //----------------------

    ls->dlgOK                   = "�T�w";
    ls->dlgOpen                 = "�}��";
    ls->dlgCancel               = "����";
    ls->dlgSave                 = "�x�s";
    ls->dlgSaveAs               = "�t�s�s��...";
    ls->dlgRun                  = "����";
    ls->dlgClose                = "����";
    
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
    ls->dlgSaveCassette          = "blueMSX - �x�s�ϱa�M����";
    ls->dlgInsertRom1           = "�Цb���� 1 ���J ROM �d�X";
    ls->dlgInsertRom2           = "�Цb���� 2 ���J ROM �d�X";
    ls->dlgInsertDiskA          = "�Цb�Ϻо� A ���J�ϺЬM����";
    ls->dlgInsertDiskB          = "�Цb�Ϻо� B ���J�ϺЬM����";
    ls->dlgInsertHarddisk       = "Insert Hard Disk";                   // New in 2.5
    ls->dlgInsertCas            = "�д��J�ϱa���ϱa";
    ls->dlgRomType              = "ROM ����:";

    ls->dlgTapeTitle            = "blueMSX - �ϱa��m";
    ls->dlgTapeFrameText        = "�ϱa��m";
    ls->dlgTapeCurrentPos       = "�ثe����m";
    ls->dlgTapeTotalTime        = "�`�ɶ�";
    ls->dlgTapeSetPosText        = "�ϱa��m:";
    ls->dlgTapeCustom            = "��ܦۭq�ɮ�";
    ls->dlgTabPosition           = "��m";
    ls->dlgTabType               = "����";
    ls->dlgTabFilename           = "�ɮצW��";
    ls->dlgZipReset             = "���J���᭫�m";

    ls->dlgAboutTitle           = "blueMSX - ����";

    ls->dlgLangLangText         = "�п�� blueMSX �n�ϥΪ��y��";
    ls->dlgLangLangTitle        = "blueMSX - �y��";

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

    ls->dlgSavePreview          = "��ܹw��";
    ls->dlgSaveDate             = "�x�s�ɶ�:";


    //----------------------
    // Properties related lines
    //----------------------

    ls->propTitle               = "blueMSX - ���e";
    ls->propEmulation           = "����";
    ls->propVideo               = "���T";
    ls->propSound               = "����";
    ls->propControls            = "���";
    ls->propPerformance         = "�į�";
    ls->propSettings             = "�]�w";
    ls->propFile                = "�ɮ�";
    ls->propPorts               = "�s����";
    
    ls->propEmuGeneralGB        = "�@�� ";
    ls->propEmuFamilyText       = "MSX ����:";
    ls->propEmuMemoryGB         = "�O���� ";
    ls->propEmuRamSizeText      = "RAM �j�p:";
    ls->propEmuVramSizeText     = "VRAM �j�p:";
    ls->propEmuSpeedGB          = "�����t�� ";
    ls->propEmuSpeedText        = "�����t��:";
    ls->propEmuFrontSwitchGB     = "Panasonic �}�� ";
    ls->propEmuFrontSwitch       = " �e�ݶ}��";
    ls->propEmuFdcTiming        = "���γn���Ϻо��p��";
    ls->propEmuPauseSwitch      = " �Ȱ��}��";
    ls->propEmuAudioSwitch       = " MSX ���ĥd�}��";
    ls->propVideoFreqText       = "���T�W�v:";
    ls->propVideoFreqAuto       = "�۰�";
    ls->propSndOversampleText   = "�W����:";
    ls->propSndYkInGB           = "YK-01/YK-10/YK-20 In ";                // New in 2.5
    ls->propSndMidiInGB         = "MIDI ��J ";
    ls->propSndMidiOutGB        = "MIDI ��X ";
    ls->propSndMidiChannel      = "MIDI Channel:";                      // New in 2.5
    ls->propSndMidiAll          = "All";                                // New in 2.5

    ls->propMonMonGB            = "�ʵ��� ";
    ls->propMonTypeText         = "�ʵ�������:";
    ls->propMonEmuText          = "�ʵ�������:";
    ls->propVideoTypeText       = "���T����:";
    ls->propWindowSizeText      = "�����j�p:";
    ls->propMonHorizStretch      = " �����Ԧ�";
    ls->propMonDeInterlace      = " �h�������e��\\��";
    ls->propMonColorGhosting    = "RF ���ܾ�";
    ls->propMonVertStretch       = " �����Ԧ�";
    ls->propMonBrightness       = "�G��:";
    ls->propMonContrast         = "����:";
    ls->propMonSaturation       = "���X��:";
    ls->propMonGamma            = "�ɺ���:";
    ls->propMonScanlines        = "���˽u:";
    ls->propMonEffectsGB        = "�ĪG";

    ls->propPerfVideoDrvGB      = "���T�X�ʵ{�� ";
    ls->propPerfVideoDispDrvText= "����X�ʵ{��:";
    ls->propPerfFrameSkipText   = "�e�沤�L:";
    ls->propPerfAudioDrvGB      = "���T�X�ʵ{�� ";
    ls->propPerfAudioDrvText    = "�����X�ʵ{��:";
    ls->propPerfAudioBufSzText  = "���Ľw�İϤj�p:";
    ls->propPerfEmuGB           = "���� ";
    ls->propPerfSyncModeText    = "�P�B�Ҧ�:";
    ls->propFullscreenResText   = "���ù��ѪR��:";

    ls->propSndChipEmuGB        = "���Ĵ������� ";
    ls->propSndMsxMusic         = " MSX ����";
    ls->propSndMsxAudio         = " MSX ����";
    ls->propSndMoonsound        = " MoonSound";
    ls->propSndMt32ToGm         = " ���� MT-32 �־���@�� MIDI �˸m";

    ls->propPortsLptGB          = "�æC�s���� ";
    ls->propPortsComGB          = "�ǦC�s���� ";
    ls->propPortsLptText        = "�s����:";
    ls->propPortsCom1Text       = "�s���� 1:";
    ls->propPortsNone           = "�L";
    ls->propPortsSimplCovox     = "SiMPL / Covox �Ʀ������ഫ��";
    ls->propPortsFile           = "�C�L���ɮ�";
    ls->propPortsComFile        = "�ǰe���ɮ�";
    ls->propPortsOpenLogFile    = "�}�ҰO����";
    ls->propPortsEmulateMsxPrn  = "����:";

    ls->propSetFileHistoryGB     = "�ɮװO�� ";
    ls->propSetFileHistorySize   = "�ɮװO�������ؼ�:";
    ls->propSetFileHistoryClear  = "�M���O��";
    ls->propFileTypes            = " ���U blueMSX ���p���ɮ����� (.rom, .dsk, .cas, .sta)";
    ls->propWindowsEnvGB         = "Windows ���� "; 
    ls->propSetScreenSaver       = " �� blueMSX ����ɰ��οù��O�@";
    ls->propDisableWinKeys       = " �ϥ� MSX �ɦ۰ʰ��� Windows �����B�k��\\���"; 
    ls->propPriorityBoost       = " ���� blueMSX ���u���v";
    ls->propScreenshotPng       = " Use Portable Network Graphics (.png) screenshots";  // New in 2.5
    ls->propClearHistory         = "�z�O�_�T�w�n�M���ɮװO���H";
    ls->propOpenRomGB           = "�}�� ROM ��ܤ�� ";
    ls->propDefaultRomType      = "�w�] ROM ����:";
    ls->propGuessRomType        = "���� ROM ����";

    ls->propSettDefSlotGB       = "�즲 ";
    ls->propSettDefSlots        = "���J ROM ��:";
    ls->propSettDefSlot         = " ����";
    ls->propSettDefDrives       = "���J�Ϥ���:";
    ls->propSettDefDrive        = " �Ϻо�";

    ls->propThemeGB             = "�G���D�D ";
    ls->propTheme               = "�G���D�D:";


    //----------------------
    // Dropdown related lines
    //----------------------

    ls->enumVideoMonColor       = "�m��";
    ls->enumVideoMonGrey        = "�¥�";
    ls->enumVideoMonGreen       = "���";
    ls->enumVideoMonAmber       = "����";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "�L";
    ls->enumVideoEmuYc          = "Y/C �����^�� (�U�Q)";
    ls->enumVideoEmuMonitor     = "�ʵ���";
    ls->enumVideoEmuYcBlur      = "���T Y/C �����^�� (�U�Q)";
    ls->enumVideoEmuComp        = "�ƦX (�ҽk)";
    ls->enumVideoEmuCompBlur    = "���T�ƦX (�ҽk)";
    ls->enumVideoEmuScale2x     = "�⭿�Y��";
    ls->enumVideoEmuHq2x        = "�⭿���~��";

    ls->enumVideoSize1x         = "�з� - 320x200";
    ls->enumVideoSize2x         = "�⭿ - 640x400";
    ls->enumVideoSizeFullscreen = "���ù�";

    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW �[�t"; 
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

    ls->enumEmuSync1ms          = "�P�B�� MSX ���s��z";
    ls->enumEmuSyncAuto         = "�۰� (�ֳt)";
    ls->enumEmuSyncNone         = "�L";
    ls->enumEmuSyncVblank       = "�P�B�� PC �����ť�";

    ls->enumControlsJoyNone     = "�L";
    ls->enumControlsJoyMouse    = "�ƹ�";
    ls->enumControlsJoyTetris2Dongle = "�Xù����� 2 �����Ҳ�";
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey Dongle";             // New in 2.5
    ls->enumControlsJoy2Button = "2-button Joystick";                   // New in 2.5
    ls->enumControlsJoyLightGun = "Light Gun";                          // New in 2.5
    ls->enumControlsJoyColeco = "ColecoVision Joystick";                // New in 2.5


    //----------------------
    // Configuration related lines
    //----------------------

    ls->confTitle                = "blueMSX - ���زպA�s�边";
    ls->confConfigText           = "�]�w";
    ls->confSlotLayout           = "���Ѱt�m";
    ls->confMemory               = "�O����";
    ls->confChipEmulation        = "��������";
    ls->confChipExtras          = "�B�~";

    ls->confOpenRom             = "�}�� ROM �M����";
    ls->confSaveTitle            = "blueMSX - �x�s�]�w";
    ls->confSaveText             = "�z�T�w�n�мg���س]�w��:";
    ls->confSaveAsTitle         = "�t�s�]�w��...";
    ls->confSaveAsMachineName    = "���ئW��:";
    ls->confDiscardTitle         = "blueMSX - �]�w";
    ls->confExitSaveTitle        = "blueMSX - ���}�]�w�s�边";
    ls->confExitSaveText         = "�z�T�w�n���ثe���]�w���ܧ�ܡH";

    ls->confSlotLayoutGB         = "���ѥ��� ";
    ls->confSlotExtSlotGB        = "�~������ ";
    ls->confBoardGB             = "�D���O ";
    ls->confBoardText           = "�D���O����:";
    ls->confSlotPrimary          = "�D�n";
    ls->confSlotExpanded         = "�w�X�i (�|�Ӥl����)";

    ls->confSlotCart             = "�d�X";
    ls->confSlot                = "����";
    ls->confSubslot             = "�l����";

    ls->confMemAdd               = "�[�J...";
    ls->confMemEdit              = "�s��...";
    ls->confMemRemove            = "����";
    ls->confMemSlot              = "����";
    ls->confMemAddresss          = "��}";
    ls->confMemType              = "����";
    ls->confMemRomImage          = "ROM �M����";
    
    ls->confChipVideoGB          = "���T ";
    ls->confChipVideoChip        = "���T����:";
    ls->confChipVideoRam         = "���T RAM:";
    ls->confChipSoundGB          = "���� ";

    ls->confCmosGB                = "CMOS ";
    ls->confCmosEnable            = " �ҥ� CMOS";
    ls->confCmosBattery           = " �ϥΥR�q�q��";

    ls->confCpuFreqGB            = "CPU �W�v ";
    ls->confZ80FreqText          = "Z80 �W�v:";
    ls->confR800FreqText         = "R800 �W�v:";
    ls->confFdcGB                = "�n���Ϻб�� ";
    ls->confCFdcNumDrivesText    = "�Ϻо��N��:";

    ls->confEditMemTitle         = "blueMSX - �s�������";
    ls->confEditMemGB            = "�������Ӹ` ";
    ls->confEditMemType          = "����:";
    ls->confEditMemFile          = "�ɮ�:";
    ls->confEditMemAddress       = "��}";
    ls->confEditMemSize          = "�j�p";
    ls->confEditMemSlot          = "����";


    //----------------------
    // Shortcut lines
    //----------------------

    ls->shortcutKey             = "�ֳt��";
    ls->shortcutDescription     = "���|";

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
    ls->shortcutSpecialMenu1    = "��ܥd�X 1 ���B�~ ROM ���";
    ls->shortcutSpecialMenu2    = "��ܥd�X 2 ���B�~ ROM ���";
    ls->shortcutCartAutoReset   = "��d�X���J�᭫�m������";
    ls->shortcutDiskInsertA     = "���J�Ϥ� A";
    ls->shortcutDiskDirInsertA  = "���J�ؿ��@���Ϥ� A";
    ls->shortcutDiskRemoveA     = "�h�X�Ϥ� A";
    ls->shortcutDiskChangeA     = "�ֳt�ܧ�Ϥ� A";
    ls->shortcutDiskAutoResetA  = "��Ϥ� A ���J�᭫�m������";
    ls->shortcutDiskInsertB     = "���J�Ϥ� B";
    ls->shortcutDiskDirInsertB  = "���J�ؿ��@���Ϥ� B";
    ls->shortcutDiskRemoveB     = "�h�X�Ϥ� B";
    ls->shortcutCasInsert       = "���J�ϱa";
    ls->shortcutCasEject        = "�h�X�ϱa";
    ls->shortcutCasAutorewind   = "�N�ϱa�������۰ʰj�a���A";
    ls->shortcutCasReadOnly     = "�N�ϱa��������Ū���A";
    ls->shortcutCasSetPosition  = "�]�w�ϱa��m";
    ls->shortcutCasRewind       = "�ϱa�j�a";
    ls->shortcutCasSave         = "�x�s�ϱa�M����";
    ls->shortcutPrnFormFeed     = "�L�������";
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
    ls->shortcutSizeMinimized   = "�̤p�Ƶ���";
    ls->shortcutToggleFullscren = "�������ù�";
    ls->shortcutVolumeIncrease  = "�W�j���q";
    ls->shortcutVolumeDecrease  = "��p���q";
    ls->shortcutVolumeMute      = "�R�����q";
    ls->shortcutVolumeStereo    = "�����歵/�����n";
    ls->shortcutSwitchMsxAudio  = "���� MSX ���Ķ}��";
    ls->shortcutSwitchFront     = "���� Panasonic �e�ݶ}��";
    ls->shortcutSwitchPause     = "�����Ȱ��}��";
    ls->shortcutToggleMouseLock = "�����ƹ���w";
    ls->shortcutEmuSpeedMax     = "�̰������t��";
    ls->shortcutEmuSpeedToggle  = "�����̰������t��";
    ls->shortcutEmuSpeedNormal  = "�зǼ����t��";
    ls->shortcutEmuSpeedInc     = "�W�[�����t��";
    ls->shortcutEmuSpeedDec     = "��C�����t��";
    ls->shortcutThemeSwitch     = "�����G���D�D";
    ls->shortcutShowEmuProp     = "��ܼ������e";
    ls->shortcutShowVideoProp   = "��ܵ��T���e";
    ls->shortcutShowAudioProp   = "��ܭ��T���e";
    ls->shortcutShowCtrlProp    = "��ܱ���e";
    ls->shortcutShowPerfProp    = "��ܮįऺ�e";
    ls->shortcutShowSettProp    = "��ܳ]�w���e";
    ls->shortcutShowPorts       = "��ܳs���𤺮e";
    ls->shortcutShowLanguage    = "��ܻy����ܤ��";
    ls->shortcutShowMachines    = "��ܾ��ؽs�边";
    ls->shortcutShowShortcuts   = "��ܧֳt��s�边";
    ls->shortcutShowKeyboard    = "�����L�s�边";
    ls->shortcutShowMixer       = "��ܲV�X��";
    ls->shortcutShowDebugger    = "��ܰ����u��";
    ls->shortcutShowTrainer     = "��ܭקﾹ";
    ls->shortcutShowHelp        = "��ܻ�����ܤ��";
    ls->shortcutShowAbout       = "��������ܤ��";
    ls->shortcutShowFiles       = "����ɮפ��e";
    ls->shortcutToggleSpriteEnable = "���/���ëe���ϼh";
    ls->shortcutToggleFdcTiming = "�ҥ�/���γn���Ϻо��p��";
    ls->shortcutToggleCpuTrace  = "�ҥ�/���� CPU �l��";


    //----------------------
    // Keyboard config lines
    //----------------------

    ls->keyconfigSelectedKey    = "���������:";
    ls->keyconfigMappedTo       = "������:";
    ls->keyconfigMappingScheme  = "�����t�m:";
};

#endif
