/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageChineseTraditional.h,v $
**
** $Revision: 1.8 $
**
** $Date: 2006-06-03 20:22:18 $
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
    ls->menuNoRecentFiles       = "- 沒有最近的檔案 -";
    ls->menuInsert              = "插入";
    ls->menuEject               = "退出";

    ls->menuCartAutoReset       = "插入/移除之後重置";
    ls->menuCartFMPac           = "FM-PAC 卡匣";
    ls->menuCartPac             = "PAC 卡匣";

    ls->menuDiskAutoStart       = "插入之後重置";
    
    ls->menuCasSetPosition      = "設定位置";
    ls->menuCasRewind           = "迴帶";

    ls->menuZoomNormal          = "一般大小";
    ls->menuZoomDouble          = "兩倍大小";
    ls->menuZoomFullscreen      = "全螢幕";
    
    ls->menuPropsEmulation      = "模擬";
    ls->menuPropsVideo          = "視訊";
    ls->menuPropsSound          = "音效";
    ls->menuPropsControls       = "控制器";
    ls->menuPropsPerformance    = "效能";
    ls->menuPropsLanguage       = "語言";
    
    ls->menuHelpHelp            = "說明主題";
    ls->menuHelpAbout           = "關於 blueMSX";

    ls->menuFileCart            = "卡匣插槽";
    ls->menuFileDisk            = "磁碟機";
    ls->menuFileCas             = "磁帶機";
    ls->menuFileLoadState       = "載入 CPU 狀態";
    ls->menuFileSaveState       = "儲存 CPU 狀態";
    ls->menuFileQLoadState      = "快速載入狀態";
    ls->menuFileQSaveState      = "快速儲存狀態";
    ls->menuFileCaptureAudio    = "擷取音訊";
    ls->menuFileScreenShot      = "儲存螢幕抓圖";
    ls->menuFileExit            = "結束";

    ls->menuRunRun              = "執行";
    ls->menuRunPause            = "暫停";
    ls->menuRunStop             = "停止";
    ls->menuRunSoftReset        = "軟體重置";
    ls->menuRunHardReset        = "硬體重置";
    ls->menuRunCleanReset       = "一般重置";

    ls->menuFile                = "檔案";
    ls->menuRun                 = "執行";
    ls->menuWindow              = "視窗";
    ls->menuOptions             = "選項";
    ls->menuHelp                = "說明";
    
    ls->errorTitle              = "blueMSX - 錯誤";
    ls->errorEnterFullscreen    = "無法進入全螢幕模式。           \n";
    ls->errorDirectXFailed      = "無法建立 DirectX 物件。           \n替代為使用 GDI。\n請檢查視訊內容。";
    ls->errorNoRomInZip         = "無法在 zip 壓縮檔案中找出 .rom 檔案。";
    ls->errorNoDskInZip         = "無法在 zip 壓縮檔案中找出 .dsk 檔案。";
    ls->errorNoCasInZip         = "無法在 zip 壓縮檔案中找出 .cas 檔案。";
    ls->errorNoHelp             = "無法找到 blueMSX 說明檔案。";
    ls->errorStartEmu           = "無法啟動 MSX 模擬器。";


    ls->dlgLoadRom              = "blueMSX - 選擇卡匣映像檔載入";
    ls->dlgLoadDsk              = "blueMSX - 選擇磁碟映像檔載入";
    ls->dlgLoadCas              = "blueMSX - 選擇磁帶映像檔載入";
    ls->dlgLoadRomDskCas        = "blueMSX - 選擇卡匣、磁碟或磁帶映像檔載入";
    ls->dlgLoadRomDesc          = "請選擇要載入的卡匣映像檔:";
    ls->dlgLoadDskDesc          = "請選擇要載入的磁碟映像檔:";
    ls->dlgLoadCasDesc          = "請選擇要載入的磁帶映像檔:";
    ls->dlgLoadRomDskCasDesc    = "請選擇要載入的卡匣、磁碟或磁帶映像檔:";
    ls->dlgLoadState            = "載入 CPU 狀態";
    ls->dlgSaveState            = "儲存 CPU 狀態";
    ls->dlgInsertRom1           = "請在插槽 1 插入 ROM 卡匣";
    ls->dlgInsertRom2           = "請在插槽 2 插入 ROM 卡匣";
    ls->dlgInsertDiskA          = "請在磁碟機 A 插入磁碟映像檔";
    ls->dlgInsertDiskB          = "請在磁碟機 B 插入磁碟映像檔";
    ls->dlgInsertCas            = "請插入磁帶機磁帶";

    ls->dlgOK                   = "確定";
    ls->dlgOpen                 = "開啟";
    ls->dlgCancel               = "取消";

    ls->dlgTapeTitle            = "blueMSX - 磁帶位置";
    ls->dlgTapeFrameText        = "磁帶位置";
    ls->dlgTapeCurrentPos       = "目前的位置";
    ls->dlgTapeTotalTime        = "總時間";

    ls->dlgZipReset             = "插入之後重置";

    ls->dlgAboutTitle           = "blueMSX - 關於";

    ls->dlgLangLangText         = "請選擇 blueMSX 要使用的語言";
    ls->dlgLangLangTitle        = "blueMSX - 語言";

    ls->propTitle               = "blueMSX - 內容";
    ls->propEmulation           = "模擬";
    ls->propVideo               = "視訊";
    ls->propSound               = "音效";
    ls->propControls            = "控制器";
    ls->propPerformance         = "效能";
    
    ls->propEmuGeneralGB        = "一般 ";
    ls->propEmuFamilyText       = "MSX 機種:";
    ls->propEmuMemoryGB         = "記憶體 ";
    ls->propEmuRamSizeText      = "RAM 大小:";
    ls->propEmuVramSizeText     = "VRAM 大小:";
    ls->propEmuSpeedGB          = "模擬速度 ";
    ls->propEmuSpeedText        = "模擬速度:";

    ls->propMonMonGB            = "監視器 ";
    ls->propMonTypeText         = "監視器類型:";
    ls->propMonEmuText          = "監視器模擬:";
    ls->propVideoYypeText       = "視訊類型:";
    ls->propWindowSizeText      = "視窗大小:";

    ls->propPerfVideoDrvGB      = "視訊驅動程式 ";
    ls->propPerfVideoDispDrvText= "顯示驅動程式:";
    ls->propPerfFrameSkipText   = "畫格略過:";
    ls->propPerfAudioDrvGB      = "音訊驅動程式 ";
    ls->propPerfAudioDrvText    = "音效驅動程式:";
    ls->propPerfAudioBufSzText  = "音效緩衝區大小:";
    ls->propPerfEmuGB           = "模擬 ";
    ls->propPerfSyncModeText    = "同步模式:";

    ls->propSndChipEmuGB        = "音效晶片模擬 ";
    ls->propSndMixerGB          = "音效混合器 ";
    ls->propSndMonoText         = "單音";
    ls->propSndStereoText       = "立體聲";
    ls->propSndMsxMusicText     = " MSX 音樂";
    ls->propSndMsxAudioText     = " MSX 音效";
    ls->propSndMsxMasterText    = "主要";

    ls->enumVideoMonColor       = "彩色";
    ls->enumVideoMonGrey        = "黑白";
    ls->enumVideoMonGreen       = "綠色";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "無";
    ls->enumVideoEmuYc          = "Y/C 分離回路 (銳利)";
    ls->enumVideoEmuYcBlur      = "雜訊 Y/C 分離回路 (銳利)";
    ls->enumVideoEmuComp        = "複合 (模糊)";
    ls->enumVideoEmuCompBlur    = "雜訊複合 (模糊)";
    ls->enumVideoEmuScale2x     = "兩倍縮放";

    ls->enumVideoSize1x         = "標準 - 320x200";
    ls->enumVideoSize2x         = "兩倍 - 640x400";
    ls->enumVideoSizeFullscreen = "全螢幕";

    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "無";
    ls->enumVideoFrameskip1     = "1 畫格";
    ls->enumVideoFrameskip2     = "2 個畫格";
    ls->enumVideoFrameskip3     = "3 個畫格";
    ls->enumVideoFrameskip4     = "4 個畫格";
    ls->enumVideoFrameskip5     = "5 個畫格";

    ls->enumSoundDrvNone        = "沒有音效";
    ls->enumSoundDrvWMM         = "WMM 驅動程式";
    ls->enumSoundDrvDirectX     = "DirectX 驅動程式";

    ls->enumControlsJoyNone     = "無";
    ls->enumControlsJoyMouse    = "滑鼠";

    ls->dlgAboutAbout           = "關於\r\n====";
    ls->dlgAboutVersion         = "版本:";
    ls->dlgAboutBuildNumber     = "組建:";
    ls->dlgAboutBuildDate       = "日期:";
    ls->dlgAboutCreat           = "由 Daniel Vik 創作";
    ls->dlgAboutDevel           = "開發成員\r\n========";
    ls->dlgAboutThanks          = "特別感謝\r\n============";
    ls->dlgAboutLisence         = "授權協議\r\n"
                                  "======\r\n\r\n"
                                  "這個軟體依據目前的狀態來提供，沒有任何明確的或暗示的擔保。 "
                                  "在任何情況下，使用這個軟體所造成的損害需要使用者自己承擔， "
                                  "作者不承擔任何的責任。\r\n\r\n"
                                  "請訪問 www.bluemsx.com 取得更多細節。";

    // New entries
    ls->menuTools                = "工具";
    ls->menuToolsMachine         = "機種編輯器";
    ls->menuPropsSettings        = "設定";
    ls->menuCasRewindAfterInsert = "插入之後迴帶";
    ls->menuCasUseReadOnly       = "使用磁帶映像檔唯讀";
    ls->lmenuCasSaveAs           = "另存磁帶映像檔為...";

    ls->dlgSaveCassette          = "blueMSX - 儲存磁帶映像檔";
    ls->dlgTapeCustom            = "顯示自訂檔案";
    ls->dlgTapeSetPosText        = "磁帶位置:";
    ls->dlgTabPosition           = "位置";
    ls->dlgTabType               = "類型";
    ls->dlgTabFilename           = "檔案名稱";

    ls->propSettings             = "設定";
    
    ls->propSetFileHistoryGB     = "檔案記錄 ";
    ls->propSetFileHistorySize   = "檔案記錄的項目數:";
    ls->propSetFileHistoryClear  = "清除記錄";
    ls->propSetScreenSaver       = " 當 blueMSX 執行時停用螢幕保護";

    ls->confTitle                = "blueMSX - 機種組態編輯器";
    ls->confSave                 = "儲存";
    ls->confSaveAs               = "另存新檔...";
    ls->confRun                  = "執行";
    ls->confClose                = "關閉";
    ls->confConfigText           = "設定";
    ls->confSlotLayout           = "插槽配置";
    ls->confMemory               = "記憶體";
    ls->confChipEmulation        = "晶片模擬";

    ls->confSlotLayoutGB         = "插槽布局 ";
    ls->confSlotExtSlotGB        = "外部插槽 ";
    ls->confSlotCart             = "卡匣";
    ls->confSlotPrimary          = "主要";
    ls->confSlotExpanded         = "已擴展 (四個子插槽)";

    ls->confMemAdd               = "加入...";
    ls->confMemEdit              = "編輯...";
    ls->confMemRemove            = "移除";
    ls->confMemSlot              = "插槽";
    ls->confMemAddresss          = "位址";
    ls->confMemType              = "類型";
    ls->confMemRomImage          = "ROM 映像檔";
    
    ls->confSaveTitle            = "blueMSX - 儲存設定";
    ls->confSaveText             = "您確定要覆寫機種設定嗎:";

    ls->confChipVideoGB          = "視訊 ";
    ls->confChipVideoChip        = "視訊晶片:";
    ls->confChipVideoRam         = "視訊 RAM:";
    ls->confChipSoundGB          = "音效 ";

    ls->confEditMemTitle         = "blueMSX - 編輯對應器";
    ls->confEditMemGB            = "對應器細節 ";
    ls->confEditMemType          = "類型:";
    ls->confEditMemFile          = "檔案:";
    ls->confEditMemAddress       = "位址";
    ls->confEditMemSize          = "大小";
    ls->confEditMemSlot          = "插槽";

    ls->confDiscardTitle         = "blueMSX - 設定";
    ls->confExitSaveTitle        = "blueMSX - 離開設定編輯器";
    ls->confExitSaveText         = "您確定要放棄目前的設定及變更嗎？";

    ls->confSaveAsMachineTitle   = "blueMSX - 另存機種設定為...";
    ls->confSaveAsMachineName    = "機種名稱:";

    ls->propSndMoonsound         = " MoonSound";

    ls->propFileTypes            = " 註冊 blueMSX 關聯的檔案類型 (.rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " 使用 MSX 時自動停用 Windows 的左、右鍵功\能表"; 
    ls->propWindowsEnvGB         = "Windows 環境 "; 
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW 加速"; 
    ls->propMonHorizStretch      = " 水平拉伸";
    ls->propMonVertStretch       = " 垂直拉伸";
    ls->propClearHistory         = "您是否確定要清除檔案記錄？";

    ls->propEmuFrontSwitchGB     = "Panasonic 開關 ";
    ls->propEmuFrontSwitch       = " 前端開關";
    ls->propEmuAudioSwitch       = " MSX 音效卡開關";


    ls->confCmosGB                = "CMOS ";
    ls->confCmosEnable            = " 啟用 CMOS";
    ls->confCmosBattery           = " 使用充電電池";

    ls->menuCartSCCPlus         = "SCC + 卡匣";
    ls->menuCartSCC             = "SCC 卡匣";
    
    ls->warningTitle             = "blueMSX - 警告";

    // New entries in 1.5.1
    ls->menuToolsShortcuts      = "快速鍵編輯器";

    ls->shortcutSaveConfig      = "blueMSX - 儲存設定";
    ls->shortcutOverwriteConfig = "您確定要覆寫快速鍵設定嗎:";
    ls->shortcutExitConfig      = "blueMSX - 離開快速鍵編輯器";
    ls->shortcutDiscardConfig   = "您確定要放棄目前的設定及變更嗎？";
    ls->shortcutSaveConfigAs    = "blueMSX - 另存快速鍵設定為...";
    ls->shortcutConfigName      = "設定名稱:";
    ls->shortcutNewProfile      = "< 新的設定檔 >";
    ls->shortcutConfigTitle     = "blueMSX - 快速鍵對應編輯器";
    ls->shortcutAssign          = "指派";
    ls->shortcutPressText       = "請按下快速鍵按鍵:";
    ls->shortcutScheme          = "對應配置:";

    ls->shortcutCartInsert1     = "插入卡匣 1";
    ls->shortcutCartRemove1     = "移除卡匣 1";
    ls->shortcutCartInsert2     = "插入卡匣 2";
    ls->shortcutCartRemove2     = "移除卡匣 2";
    ls->shortcutCartAutoReset   = "當卡匣插入後重置模擬器";
    ls->shortcutDiskInsertA     = "插入磁片 A";
    ls->shortcutDiskRemoveA     = "退出磁片 A";
    ls->shortcutDiskChangeA     = "快速變更磁片 A";
    ls->shortcutDiskAutoResetA  = "當磁片 A 插入後重置模擬器";
    ls->shortcutDiskInsertB     = "插入磁片 B";
    ls->shortcutDiskRemoveB     = "退出磁片 B";
    ls->shortcutCasInsert       = "插入磁帶";
    ls->shortcutCasEject        = "退出磁帶";
    ls->shortcutCasAutorewind   = "將磁帶切換為自動迴帶狀態";
    ls->shortcutCasReadOnly     = "將磁帶切換為唯讀狀態";
    ls->shortcutCasSetPosition  = "設定磁帶位置";
    ls->shortcutCasRewind       = "磁帶迴帶";
    ls->shortcutCasSave         = "儲存磁帶映像檔";
    ls->shortcutCpuStateLoad    = "載入 CPU 狀態";
    ls->shortcutCpuStateSave    = "儲存 CPU 狀態";
    ls->shortcutCpuStateQload   = "快速載入 CPU 狀態";
    ls->shortcutCpuStateQsave   = "快速儲存 CPU 狀態";
    ls->shortcutAudioCapture    = "開始/停止音訊擷取";
    ls->shortcutScreenshotOrig  = "螢幕抓圖 (原始)";
    ls->shortcutScreenshotSmall = "未過濾的螢幕抓圖 (較小)";
    ls->shortcutScreenshotLarge = "未過濾的螢幕抓圖 (較大)";
    ls->shortcutQuit            = "結束 blueMSX";
    ls->shortcutRunPause        = "執行/暫停模擬";
    ls->shortcutStop            = "停止模擬";
    ls->shortcutResetHard       = "硬體重置";
    ls->shortcutResetSoft       = "軟體重置";
    ls->shortcutResetClean      = "一般重置";
    ls->shortcutSizeSmall       = "設定小視窗大小";
    ls->shortcutSizeNormal      = "設定標準視窗大小";
    ls->shortcutSizeFullscreen  = "設定全螢幕";
    ls->shortcutToggleFullscren = "切換全螢幕";
    ls->shortcutVolumeIncrease  = "增大音量";
    ls->shortcutVolumeDecrease  = "減小音量";
    ls->shortcutVolumeMute      = "靜音音量";
    ls->shortcutSwitchMsxAudio  = "切換 MSX 音效開關";
    ls->shortcutSwitchFront     = "切換 Panasonic 前端開關";
    ls->shortcutToggleMouseLock = "切換滑鼠鎖定";
    ls->shortcutEmuSpeedMax     = "最高模擬速度";
    ls->shortcutEmuSpeedToggle  = "切換最高模擬速度";
    ls->shortcutEmuSpeedNormal  = "標準模擬速度";
    ls->shortcutEmuSpeedInc     = "增加模擬速度";
    ls->shortcutEmuSpeedDec     = "減低模擬速度";
    ls->shortcutShowEmuProp     = "顯示模擬內容";
    ls->shortcutShowVideoProp   = "顯示視訊內容";
    ls->shortcutShowAudioProp   = "顯示音訊內容";
    ls->shortcutShowCtrlProp    = "顯示控制內容";
    ls->shortcutShowPerfProp    = "顯示效能內容";
    ls->shortcutShowSettProp    = "顯示設定內容";
    ls->shortcutShowLanguage    = "顯示語言對話方塊";
    ls->shortcutShowMachines    = "顯示機種編輯器";
    ls->shortcutShowShortcuts   = "顯示快速鍵編輯器";
    ls->shortcutShowHelp        = "顯示說明對話方塊";
    ls->shortcutShowAbout       = "顯示關於對話方塊";
    
    ls->shortcutSpecialMenu1    = "顯示卡匣 1 的額外 ROM 選單";
    ls->shortcutSpecialMenu2    = "顯示卡匣 2 的額外 ROM 選單";
    ls->shortcutVolumeStereo    = "切換單音/立體聲";
    ls->shortcutThemeSwitch     = "切換佈景主題";
    ls->shortcutToggleSpriteEnable = "顯示/隱藏前景圖層";
    
    ls->shortcutShowApearProp   = "顯示外觀內容";
    ls->menuPropsApearance      = "外觀";
    ls->propApearance           = "外觀";
    ls->propThemeGB             = "佈景主題 ";
    ls->propTheme               = "佈景主題:";

    ls->propMonBrightness       = "亮度:";
    ls->propMonContrast         = "對比度:";
    ls->propMonSaturation       = "飽合度:";
    ls->propMonGamma            = "珈瑪值:";
    ls->propMonScanlines        = "掃瞄線:";

    ls->dlgRomType              = "ROM 類型:";
    ls->propOpenRomGB           = "開啟 ROM 對話方塊 ";
    ls->propDefaultRomType      = "預設 ROM 類型:";
    ls->propGuessRomType        = "推測 ROM 類型";

    ls->propFile                = "檔案";
    ls->propSettDefSlotGB       = "拖曳 ";
    ls->propSettDefSlots        = "插入 ROM 到:";
    ls->propSettDefSlot         = " 插槽";
    ls->propSettDefDrives       = "插入磁片到:";
    ls->propSettDefDrive        = " 磁碟機";
    ls->menuPropsFile           = "檔案";
    ls->shortcutShowFiles       = "顯示檔案內容";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "插入目錄";
    ls->shortcutDiskDirInsertA  = "插入目錄作為磁片 A";
    ls->shortcutDiskDirInsertB  = "插入目錄作為磁片 B";
    ls->propMonDeInterlace      = " 去雜紋高畫質功\能";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "切換暫停開關";
    ls->shortcutSizeMinimized   = "最小化視窗";
    ls->shortcutEmuSpeedToggle  = "切換最高模擬速度";
    ls->shortcutToggleCpuTrace  = "啟用/停用 CPU 追蹤";

    ls->enumVideoEmuMonitor     = "監視器";

    ls->propEmuPauseSwitch      = " 暫停開關";
    ls->propVideoFreqText       = "視訊頻率:";
    ls->propVideoFreqAuto       = "自動";
    ls->propSndOversampleText   = "超取樣:";

    ls->confChipExtras          = "額外";
    ls->confBoardGB             = "主機板 ";
    ls->confBoardText           = "主機板類型:";
    ls->confCpuFreqGB            = "CPU 頻率 ";
    ls->confZ80FreqText          = "Z80 頻率:";
    ls->confR800FreqText         = "R800 頻率:";
    ls->confFdcGB                = "軟式磁碟控制器 ";
    ls->confCFdcNumDrivesText    = "磁碟機代號:";

    ls->propPriorityBoost       = " 提高 blueMSX 的優先權";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "停用軟式磁碟機計時";
    ls->shortcutToggleFdcTiming = "啟用/停用軟式磁碟機計時";

    // New entries in 2.2
    ls->menuCartHBI55           = "SONY HBI-55 卡匣";
    ls->propSndPcm              = " Turbo-R PCM 音訊";
    ls->propSndAY8910           = " AY8910 PSG 音訊";
    ls->propSndSN76489          = " SN76489 PSG 音訊";
    ls->enumVideoEmuHq2x        = "兩倍高品質";
    ls->propMonColorGhosting    = "RF 調變器";

    ls->keyconfigSelectedKey    = "選取的按鍵:";
    ls->keyconfigMappedTo       = "對應到:";
    ls->keyconfigMappingScheme  = "對應配置:";

    ls->warningDiscardChanges   = "您確定要放棄變更嗎？";

    ls->confSaveAsTitle         = "另存設定為...";
    ls->confSaveAsName          = "名稱:";

    ls->menuToolsKeyboard       = "鍵盤編輯器";
    ls->shortcutShowKeyboard    = "顯示鍵盤編輯器";

    ls->menuVideoSource         = "視訊來源";
    ls->menuVideoSourceDefault  = "未連線的視訊來源";
    ls->menuVideoChipAutodetect = "自動偵測視訊晶片";
    ls->propFullscreenResText   = "全螢幕解析度:";
    ls->dlgSavePreview          = "顯示預覽";
    ls->dlgSaveDate             = "儲存時間:";
    
    ls->enumVideoMonAmber       = "黃色";

    ls->menuPropsPorts          = "連接埠";
    ls->propPortsLptGB          = "並列連接埠 ";
    ls->propPortsComGB          = "序列連接埠 ";
    ls->propPortsLptText        = "連接埠:";
    ls->propPortsCom1Text       = "連接埠 1:";

    ls->shortcutShowDebugger    = "顯示偵錯工具";
    ls->shortcutShowTrainer     = "顯示修改器";
    ls->shortcutShowPorts       = "顯示連接埠內容";
    
    ls->propPorts               = "連接埠";
    ls->propPortsNone           = "無";

    // New entries in 2.3
    ls->enumControlsJoyTetris2Dongle = "俄羅斯方塊 2 介面模組";

    ls->propPortsSimplCovox     = "SiMPL / Covox 數位類比轉換器";
    ls->propPortsFile           = "列印到檔案";
    ls->propPortsOpenLogFile    = "開啟記錄檔";
    ls->propPortsEmulateMsxPrn  = "模擬:";

    ls->shortcutPrnFormFeed     = "印表機換頁";

    ls->menuPrnFormfeed         = "換頁";
    ls->menuFilePrn             = "印表機";
    ls->propPortsComFile        = "傳送到檔案";

    // New entries in 2.4
    ls->shortcutShowMixer       = "顯示混合器";
    ls->menuToolsMixer          = "混合器";
    
    ls->propSndMidiInGB         = "MIDI 輸入 ";
    ls->propSndMidiOutGB        = "MIDI 輸出 ";
    ls->propSndMt32ToGmText     = " 對應 MT-32 樂器到一般 MIDI 裝置";

    ls->textDevice              = "裝置:";
    ls->textFilename            = "檔案名稱:";
    ls->textFile                = "檔案";
    ls->textNone                = "無";

    ls->enumEmuSyncNone         = "無";
    ls->enumEmuSyncAuto         = "自動 (快速)";
    ls->enumEmuSync1ms          = "同步於 MSX 重新整理";
    ls->enumEmuSyncVblank       = "同步到 PC 垂直空白";

    ls->propMonEffectsGB        = "效果";

    ls->confSlot                = "插槽";
    ls->confSubslot             = "子插槽";

    ls->shortcutDescription     = "捷徑";
    ls->shortcutKey             = "快速鍵";
    ls->fileRom                 = "ROM 映像檔";
    ls->confOpenRom             = "開啟 ROM 映像檔";
    ls->fileAll                 = "所有檔案";
    ls->fileCpuState            = "CPU 狀態";
    ls->fileDisk                = "磁碟映像檔";
    ls->fileCas                 = "磁帶映像檔";
    ls->menuCartExternalRam     = "外部 RAM";
};


#endif

