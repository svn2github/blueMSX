/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageChineseTraditional.h,v $
**
** $Revision: 1.37 $
**
** $Date: 2006-08-31 22:32:06 $
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
    // Language lines
    //----------------------

    ls->langChineseSimplified   = "���� (²��)";
    ls->langChineseTraditional  = "���� (�c��)";
    ls->langDutch               = "������";
    ls->langEnglish             = "�^��";
    ls->langFinnish             = "������";
    ls->langFrench              = "�k��";
    ls->langGerman              = "�w��";
    ls->langItalian             = "�q�j�Q��";
    ls->langJapanese            = "���";
    ls->langKorean              = "����";
    ls->langPolish              = "�i����";
    ls->langPortuguese          = "�������";
    ls->langSpanish             = "��Z����";
    ls->langSwedish             = "����";


    //----------------------
    // Generic lines
    //----------------------

    ls->textDevice              = "�˸m:";
    ls->textFilename            = "�ɮצW��:";
    ls->textFile                = "�ɮ�";
    ls->textNone                = "�L";
    ls->textUnknown             = "������";                            


    //----------------------
    // Warning and Error lines
    //----------------------

    ls->warningTitle            = "blueMSX - ĵ�i";
    ls->warningDiscardChanges   = "�z�T�w�n����ܧ�ܡH";
    ls->warningOverwriteFile    = "�z�T�w�n�мg�ɮ�:"; 
    ls->errorTitle              = "blueMSX - ���~";
    ls->errorEnterFullscreen    = "�L�k�i�J���ù��Ҧ��C           \n";
    ls->errorDirectXFailed      = "�L�k�إ� DirectX ����C           \n���N���ϥ� GDI�C\n���ˬd���T���e�C";
    ls->errorNoRomInZip         = "�L�k�b zip ���Y�ɮפ���X .rom �ɮסC";
    ls->errorNoDskInZip         = "�L�k�b zip ���Y�ɮפ���X .dsk �ɮסC";
    ls->errorNoCasInZip         = "�L�k�b zip ���Y�ɮפ���X .cas �ɮסC";
    ls->errorNoHelp             = "�L�k��� blueMSX �����ɮסC";
    ls->errorStartEmu           = "�L�k�Ұ� MSX �������C";
    ls->errorPortableReadonly   = "�i�⦡�˸m����Ū�ݩ�";        


    //----------------------
    // File related lines
    //----------------------

    ls->fileRom                 = "ROM �M����";
    ls->fileAll                 = "�Ҧ��ɮ�";
    ls->fileCpuState            = "CPU ���A";
    ls->fileVideoCapture        = "�^�����T"; // New in 2.6
    ls->fileDisk                = "�ϺЬM����";
    ls->fileCas                 = "�ϱa�M����";
    ls->fileAvi                 = "���ŵ��T";    // New in 2.6


    //----------------------
    // Menu related lines
    //----------------------

    ls->menuNoRecentFiles       = "- �S���̪��ɮ� -";
    ls->menuInsert              = "���J";
    ls->menuEject               = "�h�X";

    ls->menuCartGameReader      = "�C��Ū����";                        
    ls->menuCartIde             = "IDE";                                
    ls->menuCartBeerIde         = "Beer";                               
    ls->menuCartGIde            = "GIDE";                               
    ls->menuCartSunriseIde      = "Sunrise";                            
    ls->menuCartSCCPlus         = "SCC + �d�X";
    ls->menuCartSCC             = "SCC �d�X";
    ls->menuCartFMPac           = "FM-PAC �d�X";
    ls->menuCartPac             = "PAC �d�X";
    ls->menuCartHBI55           = "SONY HBI-55 �d�X";
    ls->menuCartInsertSpecial   = "���J�S���ɮ�";                     
    ls->menuCartMegaRam         = "MegaRAM";                            
    ls->menuCartExternalRam     = "�~�� RAM";

    ls->menuDiskInsertNew       = "���J�s���ϺЬM����";              
    ls->menuDiskDirInsert       = "���J�ؿ�";
    ls->menuDiskAutoStart       = "���J���᭫�m";
    ls->menuCartAutoReset       = "���J/�������᭫�m";
    
    ls->menuCasRewindAfterInsert = "���J����j�a";
    ls->menuCasUseReadOnly       = "�ϥκϱa�M���ɰ�Ū";
    ls->lmenuCasSaveAs           = "�t�s�ϱa�M���ɬ�...";
    ls->menuCasSetPosition      = "�]�w��m";
    ls->menuCasRewind           = "�j�a";

    ls->menuVideoLoad           = "���J...";             // New in 2.6
    ls->menuVideoPlay           = "����W�����^��";   // New in 2.6
    ls->menuVideoRecord         = "���s";              // New in 2.6
    ls->menuVideoRecording      = "���b���s";           // New in 2.6
    ls->menuVideoRecAppend      = "���s (���[)";     // New in 2.6
    ls->menuVideoStop           = "����";                // New in 2.6
    ls->menuVideoRender         = "��V���T�ɮ�";   // New in 2.6

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
    
    ls->menuVideoSource         = "���T��X�ӷ�";                   
    ls->menuVideoSourceDefault  = "�S�����T��X�ӷ��s�u";      
    ls->menuVideoChipAutodetect = "�۰ʰ������T����";
    ls->menuVideoInSource       = "���T��J�ӷ�";                    
    ls->menuVideoInBitmap       = "�I�}����";                        
    
    ls->menuEthInterface        = "Ethernet Interface"; // New in 2.6

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
    ls->menuFileCaptureVideo    = "�^�����T"; // New in 2.6
    ls->menuFileScreenShot      = "�x�s�ù����";
    ls->menuFileExit            = "����";

    ls->menuFileHarddisk        = "�w�о�";                          
    ls->menuFileHarddiskNoPesent= "�S���w�о����";             

    ls->menuRunRun              = "����";
    ls->menuRunPause            = "�Ȱ�";
    ls->menuRunStop             = "����";
    ls->menuRunSoftReset        = "�n�魫�m";
    ls->menuRunHardReset        = "�w�魫�m";
    ls->menuRunCleanReset       = "�@�뭫�m";

    ls->menuToolsMachine        = "���ؽs�边";
    ls->menuToolsShortcuts      = "�ֳt��s�边";
    ls->menuToolsCtrlEditor     = "��� / ��L�s�边"; // New in 2.6
    ls->menuToolsMixer          = "�V�X��";
    ls->menuToolsDebugger       = "�����u��";               
    ls->menuToolsTrainer        = "�V�m��";                
    ls->menuToolsTraceLogger    = "�l�ܰO����";           

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
    ls->dlgLoadVideoCapture     = "���J�^�����T";      // New in 2.6
    ls->dlgSaveState            = "�x�s CPU ���A";
    ls->dlgSaveCassette          = "blueMSX - �x�s�ϱa�M����";
    ls->dlgSaveVideoClipAs      = "�x�s���T���Ŭ�...";      // New in 2.6
    ls->dlgAmountCompleted      = "���ͧ���:";          // New in 2.6
    ls->dlgInsertRom1           = "�Цb���� 1 ���J ROM �d�X";
    ls->dlgInsertRom2           = "�Цb���� 2 ���J ROM �d�X";
    ls->dlgInsertDiskA          = "�Цb�Ϻо� A ���J�ϺЬM����";
    ls->dlgInsertDiskB          = "�Цb�Ϻо� B ���J�ϺЬM����";
    ls->dlgInsertHarddisk       = "���J�w�о�";                   
    ls->dlgInsertCas            = "�д��J�ϱa���ϱa";
    ls->dlgRomType              = "ROM ����:";
    ls->dlgDiskSize             = "�ϺФj�p:";             // New in 2.6

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

    ls->dlgRenderVideoCapture   = "blueMSX - ���b��V�^�����T...";  // New in 2.6


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
    ls->propSndYkInGB           = "YK-01/YK-10/YK-20 ��J ";                
    ls->propSndMidiInGB         = "MIDI ��J ";
    ls->propSndMidiOutGB        = "MIDI ��X ";
    ls->propSndMidiChannel      = "MIDI �n�D:";                      
    ls->propSndMidiAll          = "����";                                

    ls->propMonMonGB            = "�ʵ��� ";
    ls->propMonTypeText         = "�ʵ�������:";
    ls->propMonEmuText          = "�ʵ�������:";
    ls->propVideoTypeText       = "���T����:";
    ls->propWindowSizeText      = "�����j�p:";
    ls->propMonHorizStretch      = " �����Ԧ�";
    ls->propMonDeInterlace      = " �h�������e��\\��";
    ls->propBlendFrames         = " �V�X�s�򪺵e��";           
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
    ls->propPriorityBoost        = " ���� blueMSX ���u���v";
    ls->propScreenshotPng        = " �ϥΥi�⦡�����ϧ� (.png) �ù����";  
    ls->propClearHistory         = "�z�O�_�T�w�n�M���ɮװO���H";
    ls->propOpenRomGB            = "�}�� ROM ��ܤ�� ";
    ls->propDefaultRomType       = "�w�] ROM ����:";
    ls->propGuessRomType         = "���� ROM ����";

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

    ls->enumVideoDrvDirectDrawHW = "DirectDraw �w��[�t"; 
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
    ls->enumEmuAsyncVblank      = "�D�P�B PC �ť�";             

    ls->enumControlsJoyNone     = "�L";
    ls->enumControlsJoyMouse    = "�ƹ�";
    ls->enumControlsJoyTetris2Dongle = "�Xù����� 2 �����Ҳ�";
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey Dongle";             
    ls->enumControlsJoy2Button = "2 ���s�n��";                   
    ls->enumControlsJoyGunstick  = "Gun Stick ���u�j";                         
    ls->enumControlsJoyAsciiLaser="ASCII Plus-X �׵��̹p�g���u�j";      
    ls->enumControlsJoyColeco = "ColecoVision �n��";                

    ls->enumDiskMsx35Dbl9Sect    = "MSX 3.5\" ����, 9 �Ӻϰ�";     
    ls->enumDiskMsx35Dbl8Sect    = "MSX 3.5\" ����, 8 �Ӻϰ�";     
    ls->enumDiskMsx35Sgl9Sect    = "MSX 3.5\" �歱, 9 �Ӻϰ�";     
    ls->enumDiskMsx35Sgl8Sect    = "MSX 3.5\" �歱, 8 �Ӻϰ�";     
    ls->enumDiskSvi525Dbl        = "SVI-328 5.25\" ����";           
    ls->enumDiskSvi525Sgl        = "SVI-328 5.25\" �歱"; 
    ls->enumDiskSf3Sgl           = "Sega SF-7000 3\"  �歱";  // New in 2.6             


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
    ls->shortcutVideoLoad       = "���J...";             // New in 2.6
    ls->shortcutVideoPlay       = "����W�����^��";   // New in 2.6
    ls->shortcutVideoRecord     = "���s";              // New in 2.6
    ls->shortcutVideoStop       = "����";                // New in 2.6
    ls->shortcutVideoRender     = "��V���T�ɮ�";   // New in 2.6


    //----------------------
    // Keyboard config lines
    //----------------------

    ls->keyconfigSelectedKey    = "���������:";
    ls->keyconfigMappedTo       = "������:";
    ls->keyconfigMappingScheme  = "�����t�m:";

    
    //----------------------
    // Rom type lines
    //----------------------

    ls->romTypeStandard         = "Standard";
    ls->romTypeMsxdos2          = "MSXDOS 2";
    ls->romTypeKonamiScc        = "Konami SCC";
    ls->romTypeKonami           = "Konami";
    ls->romTypeAscii8           = "ASCII 8";
    ls->romTypeAscii16          = "ASCII 16";
    ls->romTypeGameMaster2      = "Game Master 2 (SRAM)";
    ls->romTypeAscii8Sram       = "ASCII 8 (SRAM)";
    ls->romTypeAscii16Sram      = "ASCII 16 (SRAM)";
    ls->romTypeRtype            = "R-Type";
    ls->romTypeCrossblaim       = "Cross Blaim";
    ls->romTypeHarryFox         = "Harry Fox";
    ls->romTypeMajutsushi       = "Konami Majutsushi";
    ls->romTypeZenima80         = "Zemina 80 in 1";
    ls->romTypeZenima90         = "Zemina 90 in 1";
    ls->romTypeZenima126        = "Zemina 126 in 1";
    ls->romTypeScc              = "SCC";
    ls->romTypeSccPlus          = "SCC+";
    ls->romTypeSnatcher         = "The Snatcher";
    ls->romTypeSdSnatcher       = "SD Snatcher";
    ls->romTypeSccMirrored      = "SCC mirrored";
    ls->romTypeSccExtended      = "SCC extended";
    ls->romTypeFmpac            = "FMPAC (SRAM)";
    ls->romTypeFmpak            = "FMPAK";
    ls->romTypeKonamiGeneric    = "Konami Generic";
    ls->romTypeSuperPierrot     = "Super Pierrot";
    ls->romTypeMirrored         = "Mirrored ROM";
    ls->romTypeNormal           = "Normal ROM";
    ls->romTypeDiskPatch        = "Normal + Disk Patch";
    ls->romTypeCasPatch         = "Normal + Cassette Patch";
    ls->romTypeTc8566afFdc      = "TC8566AF Disk Controller";
    ls->romTypeMicrosolFdc      = "Microsol Disk Controller";
    ls->romTypeNationalFdc      = "National Disk Controller";
    ls->romTypePhilipsFdc       = "Philips Disk Controller";
    ls->romTypeSvi738Fdc        = "SVI-738 Disk Controller";
    ls->romTypeMappedRam        = "Mapped RAM";
    ls->romTypeMirroredRam1k    = "1kB Mirrored RAM";
    ls->romTypeMirroredRam2k    = "2kB Mirrored RAM";
    ls->romTypeNormalRam        = "Normal RAM";
    ls->romTypeKanji            = "Kanji";
    ls->romTypeHolyQuran        = "Holy Quran";
    ls->romTypeMatsushitaSram   = "Matsushita SRAM";
    ls->romTypePanasonic16      = "Panasonic 16kB SRAM";
    ls->romTypePanasonic32      = "Panasonic 32kB SRAM";
    ls->romTypeBunsetsu         = "Bunsetsu";
    ls->romTypeJisyo            = "Jisyo";
    ls->romTypeKanji12          = "Kanji12";
    ls->romTypeNationalSram     = "National (SRAM)";
    ls->romTypeS1985            = "S1985";
    ls->romTypeS1990            = "S1990";
    ls->romTypeTurborPause      = "Turbo-R Pause";
    ls->romTypeF4deviceNormal   = "F4 Device Normal";
    ls->romTypeF4deviceInvert   = "F4 Device Inverted";
    ls->romTypeMsxMidi          = "MSX-MIDI";
    ls->romTypeTurborTimer      = "Turbo-R Timer";
    ls->romTypeKoei             = "Koei (SRAM)";
    ls->romTypeBasic            = "Basic ROM";
    ls->romTypeHalnote          = "Halnote";
    ls->romTypeLodeRunner       = "Lode Runner";
    ls->romTypeNormal4000       = "Normal 4000h";
    ls->romTypeNormalC000       = "Normal C000h";
    ls->romTypeKonamiSynth      = "Konami Synthesizer";
    ls->romTypeKonamiKbdMast    = "Konami Keyboard Master";
    ls->romTypeKonamiWordPro    = "Konami Word Pro";
    ls->romTypePac              = "PAC (SRAM)";
    ls->romTypeMegaRam          = "MegaRAM";
    ls->romTypeMegaRam128       = "128kB MegaRAM";
    ls->romTypeMegaRam256       = "256kB MegaRAM";
    ls->romTypeMegaRam512       = "512kB MegaRAM";
    ls->romTypeMegaRam768       = "768kB MegaRAM";
    ls->romTypeMegaRam2mb       = "2MB MegaRAM";
    ls->romTypeExtRam           = "External RAM";
    ls->romTypeExtRam512        = "512kB External RAM";
    ls->romTypeExtRam1mb        = "1MB External RAM";
    ls->romTypeExtRam2mb        = "2MB External RAM";
    ls->romTypeExtRam4mb        = "4MB External RAM";
    ls->romTypeMsxMusic         = "MSX Music";
    ls->romTypeMsxAudio         = "MSX Audio";
    ls->romTypeY8950            = "Y8950";
    ls->romTypeMoonsound        = "Moonsound";
    ls->romTypeSvi328Cart       = "SVI-328 Cartridge";
    ls->romTypeSvi328Fdc        = "SVI-328 Disk Controller";
    ls->romTypeSvi328Prn        = "SVI-328 Printer";
    ls->romTypeSvi328Uart       = "SVI-328 Serial Port";
    ls->romTypeSvi328col80      = "SVI-328 80 Column Card";
    ls->romTypeSvi727col80      = "SVI-727 80 Column Card";
    ls->romTypeColecoCart       = "Coleco Cartridge";
    ls->romTypeSg1000Cart       = "SG-1000 Cartridge";
    ls->romTypeSc3000Cart       = "SC-3000 Cartridge";
    ls->romTypeTheCastle        = "The Castle";
    ls->romTypeSonyHbi55        = "Sony HBI-55";
    ls->romTypeMsxPrinter       = "MSX Printer";
    ls->romTypeTurborPcm        = "Turbo-R PCM Chip";
    ls->romTypeGameReader       = "Sunrise GameReader";
    ls->romTypeSunriseIde       = "Sunrise IDE";
    ls->romTypeBeerIde          = "Beer IDE";
    ls->romTypeGide             = "GIDE";
    ls->romTypeVmx80            = "Microsol VMX-80";
    ls->romTypeNms8280Digitiz   = "Philips NMS-8280 Digitizer";
    ls->romTypeHbiV1Digitiz     = "Sony HBI-V1 Digitizer";
    ls->romTypeFmdas            = "F&M Direct Assembler System";
    ls->romTypeSfg01            = "Yamaha SFG-01";
    ls->romTypeSfg05            = "Yamaha SFG-05";
    ls->romTypePlayBall         = "Sony Playball";  // New in 2.6
    ls->romTypeObsonet          = "Obsonet";  // New in 2.6
    ls->romTypeSegaBasic        = "Sega Basic";  // New in 2.6
    
    
    //----------------------
    // Debug type lines
    // Note: Only needs translation if debugger is translated
    //----------------------

    ls->dbgMemVisible           = "�i���O����";
    ls->dbgMemRamNormal         = "�з�";
    ls->dbgMemRamMapped         = "����";
    ls->dbgMemVram              = "VRAM";
    ls->dbgMemYmf278            = "YMF278 ���� RAM";
    ls->dbgMemAy8950            = "AY8950 ���� RAM";
    ls->dbgMemScc               = "�O����";

    ls->dbgCallstack            = "�I�s���|";

    ls->dbgRegs                 = "�Ȧs��";
    ls->dbgRegsCpu              = "CPU �Ȧs��";
    ls->dbgRegsYmf262           = "YMF262 �Ȧs��";
    ls->dbgRegsYmf278           = "YMF278 �Ȧs��";
    ls->dbgRegsAy8950           = "AY8950 �Ȧs��";
    ls->dbgRegsYm2413           = "YM2413 �Ȧs��";

    ls->dbgDevRamMapper         = "RAM ������";
    ls->dbgDevRam               = "RAM";
    ls->dbgDevIdeBeer           = "Beer IDE";
    ls->dbgDevIdeGide           = "GIDE";
    ls->dbgDevF4Device          = "F4 �˸m";
    ls->dbgDevFmpac             = "FMPAC";
    ls->dbgDevFmpak             = "FMPAK";
    ls->dbgDevKanji             = "Kanji";
    ls->dbgDevKanji12           = "Kanji 12";
    ls->dbgDevKonamiKbd         = "Konami Keyboard Master";
    ls->dbgDevKorean80          = "Korean 80";
    ls->dbgDevKorean90          = "Korean 90";
    ls->dbgDevKorean128         = "Korean 128";
    ls->dbgDevMegaRam           = "Mega RAM";
    ls->dbgDevFdcMicrosol       = "Microsol FDC";
    ls->dbgDevMoonsound         = "Moonsound";
    ls->dbgDevMsxAudio          = "MSX ����";
    ls->dbgDevMsxAudioMidi      = "MSX ���� MIDI";
    ls->dbgDevMsxMusic          = "MSX ����";
    ls->dbgDevPrinter           = "�L���";
    ls->dbgDevRs232             = "RS232";
    ls->dbgDevS1990             = "S1990";
    ls->dbgDevSfg05             = "Yamaha SFG-05";
    ls->dbgDevHbi55             = "Sony HBI-55";
    ls->dbgDevSviFdc            = "SVI FDC";
    ls->dbgDevSviPrn            = "SVI �L���";
    ls->dbgDevSvi80Col          = "SVI 80 �����";
    ls->dbgDevPcm               = "PCM";
    ls->dbgDevMatsushita        = "Matsushita";
    ls->dbgDevS1985             = "S1985";
    ls->dbgDevCrtc6845          = "CRTC6845";
    ls->dbgDevTms9929A          = "TMS9929A";
    ls->dbgDevTms99x8A          = "TMS99x8A";
    ls->dbgDevV9938             = "V9938";
    ls->dbgDevV9958             = "V9958";
    ls->dbgDevZ80               = "Z80";
    ls->dbgDevMsxMidi           = "MSX MIDI";
    ls->dbgDevPpi               = "PPI";
    ls->dbgDevRtc               = "RTC";
    ls->dbgDevTrPause           = "TR �Ȱ�";
    ls->dbgDevAy8910            = "AY8910 PSG";
    ls->dbgDevScc               = "SCC";


    //----------------------
    // Debug type lines
    // Note: Can only be translated to european languages
    //----------------------

    ls->aboutScrollThanksTo     = "Special thanks to: ";
    ls->aboutScrollAndYou       = "and YOU !!!!";
};

#endif
