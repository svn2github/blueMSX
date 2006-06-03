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
    ls->noRecentFiles           = "- 无最近的文件 -";
    ls->insert                  = "插入";
    ls->eject                   = "弹出";
    
    ls->menuCartAutoReset       = "插入/移除后重置";
    ls->menuCartFMPac           = "FM-PAC 卡带";
    ls->menuCartPac             = "PAC 卡带";

    ls->menuDiskAutoStart       = "插入后重置";
    
    ls->menuCasSetPosition      = "磁带位置设置";
    ls->menuCasRewind           = "倒带";

    ls->menuZoomNormal          = "标准尺寸";
    ls->menuZoomDouble          = "两倍尺寸";
    ls->menuZoomFullscreen      = "全屏幕";
    
    ls->menuPropsEmulation      = "模拟";
    ls->menuPropsVideo          = "视频";
    ls->menuPropsSound          = "声音";
    ls->menuPropsControls       = "控制器";
    ls->menuPropsPerformance    = "性能";
    ls->menuPropsLanguage       = "语言";
    
    ls->menuHelpHelp            = "帮助主题";
    ls->menuHelpAbout           = "关于 blueMSX";

    ls->menuFileCart            = "卡带插槽";
    ls->menuFileDisk            = "软盘驱动器";
    ls->menuFileCas             = "磁带机";
    ls->menuFileLoadState       = "读取 CPU 状态";
    ls->menuFileSaveState       = "保存 CPU 状态";
    ls->menuFileQLoadState      = "快速读取";
    ls->menuFileQSaveState      = "快速保存";
    ls->menuFileCaptureAudio    = "录音";
    ls->menuFileScreenShot      = "截图";
    ls->menuFileExit            = "退出";

    ls->menuRunRun              = "运行";
    ls->menuRunPause            = "暂停";
    ls->menuRunStop             = "停止";
    ls->menuRunSoftReset        = "软件重置";
    ls->menuRunHardReset        = "硬件重置";
    ls->menuRunCleanReset       = "常规重置";

    ls->menuFile                = "文件";
    ls->menuRun                 = "运行";
    ls->menuWindow              = "窗口";
    ls->menuOptions             = "选项";
    ls->menuHelp                = "帮助";
    
    ls->errorTitle              = "blueMSX - 错误";
    ls->errorEnterFullscreen    = "无法进入全屏模式。           \n";
    ls->errorDirectXFailed      = "无法创建 DirectX 对象。           \n改为使用GDI。\n请检查显卡设置。";
    ls->errorNoRomInZip         = "无法在 zip 压缩包内找到 .rom 文件。";
    ls->errorNoDskInZip         = "无法在 zip 压缩包内找到 .dsk 文件。";
    ls->errorNoCasInZip         = "无法在 zip 压缩包内找到 .cas 文件。";
    ls->errorNoHelp             = "无法找到 blueMSX 帮助文件。";
    ls->errorStartEmu           = "无法启动 MSX 模拟器。";

    ls->dlgLoadRom              = "blueMSX - 请选择卡带映像";
    ls->dlgLoadDsk              = "blueMSX - 请选择软盘映像";
    ls->dlgLoadCas              = "blueMSX - 请选择磁带映像";
    ls->dlgLoadRomDskCas        = "blueMSX - 请选择卡带、软盘或磁带映像";
    ls->dlgLoadRomDesc          = "请选择要读取的卡带映像:";
    ls->dlgLoadDskDesc          = "请选择要读取的软盘映像:";
    ls->dlgLoadCasDesc          = "请选择要读取的磁带映像:";
    ls->dlgLoadRomDskCasDesc    = "请选择要读取的卡带、软盘或磁带映像:";
    ls->dlgLoadState            = "读取 CPU 状态";
    ls->dlgSaveState            = "保存 CPU 状态";
    ls->dlgInsertRom1           = "请在插槽 1 插入 ROM 卡带";
    ls->dlgInsertRom2           = "请在插槽 2 插入 ROM 卡带";
    ls->dlgInsertDiskA          = "请在驱动器 A 插入软盘映像";
    ls->dlgInsertDiskB          = "请在驱动器 B 插入软盘映像";
    ls->dlgInsertCas            = "请插入磁带";

    ls->dlgOK                   = "确定";
    ls->dlgOpen                 = "打开";
    ls->dlgCancel               = "取消";

    ls->dlgTapeTitle            = "blueMSX - 磁带";
    ls->dlgTapeFrameText        = "磁带位置";
    ls->dlgTapeCurrentPos       = "当前位置";
    ls->dlgTapeTotalTime        = "总时间";

    ls->dlgZipReset             = "插入后重置";

    ls->dlgAboutTitle           = "blueMSX - 关于";

    ls->dlgLangLangText         = "请选择 blueMSX 所使用语言";
    ls->dlgLangLangTitle        = "blueMSX - 语言";

    ls->propTitle               = "blueMSX - 属性";
    ls->propEmulation           = "模拟";
    ls->propVideo               = "视频";
    ls->propSound               = "声音";
    ls->propControls            = "控制器";
    ls->propPerformance         = "性能";
    
    ls->propEmuGeneralGB        = "常规 ";
    ls->propEmuFamilyText       = "MSX 机型:";
    ls->propEmuMemoryGB         = "内存 ";
    ls->propEmuRamSizeText      = "主内存:";
    ls->propEmuVramSizeText     = "显存:";
    ls->propEmuSpeedGB          = "模拟速度 ";
    ls->propEmuSpeedText        = "模拟速度:";

    ls->propMonMonGB            = "显示器 ";
    ls->propMonTypeText         = "显示器类型:";
    ls->propMonEmuText          = "显示器模拟:";
    ls->propVideoYypeText       = "视频类型:";
    ls->propWindowSizeText      = "窗口大小:";

    ls->propPerfVideoDrvGB      = "视频驱动 ";
    ls->propPerfVideoDispDrvText= "显示驱动:";
    ls->propPerfFrameSkipText   = "跳帧:";
    ls->propPerfAudioDrvGB      = "音频驱动 ";
    ls->propPerfAudioDrvText    = "声音驱动:";
    ls->propPerfAudioBufSzText  = "声音缓冲:";
    ls->propPerfEmuGB           = "模拟 ";
    ls->propPerfSyncModeText    = "同步模式:";

    ls->propSndChipEmuGB        = "声音芯片模拟 ";
    ls->propSndMixerGB          = "音频混频器 ";
    ls->propSndMonoText         = "单声道";
    ls->propSndStereoText       = "立体声";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "主要";

    ls->enumVideoMonColor       = "彩色";
    ls->enumVideoMonGrey        = "黑白";
    ls->enumVideoMonGreen       = "绿色";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "无";
    ls->enumVideoEmuYc          = "Y/C 分离回路 (锐利)";
    ls->enumVideoEmuYcBlur      = "降噪 Y/C 分离回路 (锐利)";
    ls->enumVideoEmuComp        = "复合 (模糊)";
    ls->enumVideoEmuCompBlur    = "降噪复合 (模糊)";
    ls->enumVideoEmuScale2x     = "2 倍柔化";

    ls->enumVideoSize1x         = "标准 - 320x200";
    ls->enumVideoSize2x         = "两倍 - 640x400";
    ls->enumVideoSizeFullscreen = "全屏幕";

    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "无";
    ls->enumVideoFrameskip1     = "1个帧";
    ls->enumVideoFrameskip2     = "2个帧";
    ls->enumVideoFrameskip3     = "3个帧";
    ls->enumVideoFrameskip4     = "4个帧";
    ls->enumVideoFrameskip5     = "5个帧";

    ls->enumSoundDrvNone        = "无声";
    ls->enumSoundDrvWMM         = "WMM 驱动";
    ls->enumSoundDrvDirectX     = "DirectX 驱动";

    ls->enumControlsJoyNone     = "无";
    ls->enumControlsJoyMouse    = "鼠标";

    ls->dlgAboutAbout           = "关于\r\n====";
    ls->dlgAboutVersion         = "版本:";
    ls->dlgAboutBuildNumber     = "创建:";
    ls->dlgAboutBuildDate       = "日期:";
    ls->dlgAboutCreat           = "制作:	Daniel Vik";
    ls->dlgAboutDevel           = "各位协力的开发者们\r\n========";
    ls->dlgAboutThanks          = "特别鸣谢\r\n============";
    ls->dlgAboutLisence         = "授权\r\n"
                                  "======\r\n\r\n"
                                  "本软件是根据目前状况而发布的，没有任何明确或默许的授权。 "
                                  "在任何情况下，使用本软件所造成的后果需由用户自己承担， "
                                  "作者将不承担任何责任。\r\n\r\n"
                                  "更多详情请登陆: www.bluemsx.com ";

    // New entries
    ls->menuTools                = "工具";
    ls->menuToolsMachine         = "机型资料编辑";
    ls->menuPropsSettings        = "设定";
    ls->menuCasRewindAfterInsert = "插入后倒带";
    ls->menuCasUseReadOnly       = "使用磁带时只读";
    ls->lmenuCasSaveAs           = "另存为...";

    ls->dlgSaveCassette          = "blueMSX - 保存磁带映像";
    ls->dlgTapeCustom            = "显示自定义文件";
    ls->dlgTapeSetPosText        = "磁带位置:";
    ls->dlgTabPosition           = "位置";
    ls->dlgTabType               = "类型";
    ls->dlgTabFilename           = "文件名";

    ls->propSettings             = "其他";
    
    ls->propSetFileHistoryGB     = "历史文件 ";
    ls->propSetFileHistorySize   = "历史文件的数量:";
    ls->propSetFileHistoryClear  = "清除历史文件";
    ls->propSetScreenSaver       = " blueMSX 运行时关闭屏幕保护";

    ls->confTitle                = "blueMSX - 机型资料编辑工具";
    ls->confSave                 = "保存";
    ls->confSaveAs               = "另存为...";
    ls->confRun                  = "运行";
    ls->confClose                = "关闭";
    ls->confConfigText           = "设置";
    ls->confSlotLayout           = "插槽配线";
    ls->confMemory               = "内存";
    ls->confChipEmulation        = "芯片模拟";

    ls->confSlotLayoutGB         = "插槽配线 ";
    ls->confSlotExtSlotGB        = "扩展插槽 ";
    ls->confSlotCart             = "卡带";
    ls->confSlotPrimary          = "主要";
    ls->confSlotExpanded         = "扩展 （四个子插槽）";

    ls->confMemAdd               = "添加...";
    ls->confMemEdit              = "编辑...";
    ls->confMemRemove            = "删除";
    ls->confMemSlot              = "插槽";
    ls->confMemAddresss          = "地址";
    ls->confMemType              = "类型";
    ls->confMemRomImage          = "Rom 映像";
    
    ls->confSaveTitle            = "blueMSX - 保存设置";
    ls->confSaveText             = "要覆盖原有的机型资料吗:";

    ls->confChipVideoGB          = "视频 ";
    ls->confChipVideoChip        = "显示芯片:";
    ls->confChipVideoRam         = "显示内存:";
    ls->confChipSoundGB          = "声音 ";

    ls->slotEditMemTitle         = "blueMSX - 编辑 Mapper";
    ls->slotEditMemGB            = "Mapper 详细";
    ls->slotEditMemType          = "类型:";
    ls->slotEditMemFile          = "文件:";
    ls->slotEditMemAddress       = "地址";
    ls->slotEditMemSize          = "大小";
    ls->slotEditMemSlot          = "插槽";

    ls->confDiscardTitle         = "blueMSX - 设置";
    ls->confExitSaveTitle        = "blueMSX - 退出编辑工具";
    ls->confExitSaveText         = "要放弃对当前文件的修改吗？";

    ls->confSaveAsMachineTitle   = "blueMSX - 机型资料另存为...";
    ls->confSaveAsMachineName    = "机型类型:";

    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypes            = " 用 blueMSX 关联文件 ( .rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " MSX 使用中周围的 Windows 按键无效"; 
    ls->propWindowsEnvGB         = "Windows 环境设定 "; 
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW 加速"; 
    ls->propMonHorizStretch      = " 水平拉伸";
    ls->propMonVertStretch       = " 垂直拉伸";
    ls->propClearHistory         = "确认要清除历史文件？";

    ls->propEmuFrontSwitchGB     = "Panasonic 开关 ";
    ls->propEmuFrontSwitch       = " 前端开关";
    ls->propEmuAudioSwitch       = " MSX-AUDIO 卡开关";


    ls->dlgCmosGB                = "CMOS ";
    ls->dlgCmosEnable            = " 启用 CMOS";
    ls->dlgCmosBattery           = " 启用内置电池";

    ls->menuCartSCCPlus         = "SCC+ 卡带";
    ls->menuCartSCC             = "SCC 卡带";
    
    ls->warningTitle             = "blueMSX - 警告";

    // New entries in 1.5.1
    ls->menuToolsShortcuts      = "快捷键编辑工具";

    ls->shortcutSaveConfig      = "blueMSX - 保存设置";
    ls->shortcutOverwriteConfig = "要覆盖原有的快捷键设置吗:";
    ls->shortcutExitConfig      = "blueMSX - 退出快捷键编辑工具";
    ls->shortcutDiscardConfig   = "要放弃对当前文件的修改吗？";
    ls->shortcutSaveConfigAs    = "blueMSX - 快捷键另存为...";
    ls->shortcutConfigName      = "设置名称:";
    ls->shortcutNewProfile      = "< 新建档案 >";
    ls->shortcutConfigTitle     = "blueMSX - 快捷键方案编辑工具";
    ls->shortcutAssign          = "分配";
    ls->shortcutPressText       = "请输入快捷键:";
    ls->shortcutScheme          = "映射方案:";

    ls->shortcutCartInsert1     = "插入卡带 1";
    ls->shortcutCartRemove1     = "移除卡带 1";
    ls->shortcutCartInsert2     = "插入卡带 2";
    ls->shortcutCartRemove2     = "移除卡带 2";
    ls->shortcutCartAutoReset   = "卡带插入后重置模拟器";
    ls->shortcutDiskInsertA     = "插入软盘 A";
    ls->shortcutDiskRemoveA     = "弹出软盘 A";
    ls->shortcutDiskChangeA     = "快速切换软盘 A";
    ls->shortcutDiskAutoResetA  = "软盘 A 插入后重置模拟器";
    ls->shortcutDiskInsertB     = "插入软盘 B";
    ls->shortcutDiskRemoveB     = "弹出软盘 B";
    ls->shortcutCasInsert       = "插入磁带";
    ls->shortcutCasEject        = "弹出磁带";
    ls->shortcutCasAutorewind   = "锁定磁带自动倒带";
    ls->shortcutCasReadOnly     = "锁定磁带只读";
    ls->shortcutCasSetPosition  = "设定磁带位置";
    ls->shortcutCasRewind       = "倒带";
    ls->shortcutCasSave         = "保存磁带映像";
    ls->shortcutCpuStateLoad    = "读取 CPU 状态";
    ls->shortcutCpuStateSave    = "保存 CPU 状态";
    ls->shortcutCpuStateQload   = "快速读取 CPU 状态";
    ls->shortcutCpuStateQsave   = "快速保存 CPU 状态";
    ls->shortcutAudioCapture    = "开始/停止录音";
    ls->shortcutScreenshotOrig  = "屏幕截图 （原始）";
    ls->shortcutScreenshotSmall = "屏幕截图 （标准，未过滤）";
    ls->shortcutScreenshotLarge = "屏幕截图 （两倍，未过滤）";
    ls->shortcutQuit            = "退出 blueMSX";
    ls->shortcutRunPause        = "运行/暂停模拟";
    ls->shortcutStop            = "停止模拟";
    ls->shortcutResetHard       = "硬件重置";
    ls->shortcutResetSoft       = "软件重置";
    ls->shortcutResetClean      = "常规重置";
    ls->shortcutSizeSmall       = "设为标准窗口";
    ls->shortcutSizeNormal      = "设为两倍窗口";
    ls->shortcutSizeFullscreen  = "设为全屏幕";
    ls->shortcutToggleFullscren = "切换全屏幕";
    ls->shortcutVolumeIncrease  = "增大音量";
    ls->shortcutVolumeDecrease  = "减小音量";
    ls->shortcutVolumeMute      = "静音";
    ls->shortcutSwitchMsxAudio  = "切换 MSX-AUDIO 卡开关";
    ls->shortcutSwitchFront     = "切换 Panasonic 前端开关";
    ls->shortcutToggleMouseLock = "切换鼠标锁定";
    ls->shortcutEmuSpeedMax     = "最高速模拟";
    ls->shortcutEmuSpeedToggle  = "锁定最高速模拟";
    ls->shortcutEmuSpeedNormal  = "正常模拟速度";
    ls->shortcutEmuSpeedInc     = "加快模拟速度";
    ls->shortcutEmuSpeedDec     = "降低模拟速度";
    ls->shortcutShowEmuProp     = "显示模拟属性";
    ls->shortcutShowVideoProp   = "显示视频属性";
    ls->shortcutShowAudioProp   = "显示音频属性";
    ls->shortcutShowCtrlProp    = "显示控制属性";
    ls->shortcutShowPerfProp    = "显示性能属性";
    ls->shortcutShowSettProp    = "显示其他属性";
    ls->shortcutShowLanguage    = "显示语言对话框";
    ls->shortcutShowMachines    = "显示机型资料编辑工具";
    ls->shortcutShowShortcuts   = "显示快捷键编辑工具";
    ls->shortcutShowHelp        = "显示帮助对话框";
    ls->shortcutShowAbout       = "显示关于对话框";
    
    ls->shortcutSpecialMenu1    = "为卡带 1 显示特别 Rom 菜单";
    ls->shortcutSpecialMenu2    = "为卡带 2 显示特别 Rom 菜单";
    ls->shortcutVolumeStereo    = "切换单声道/立体声";
    ls->shortcutThemeSwitch     = "切换布景主题";
    ls->shortcutToggleSpriteEnable = "显示/隐藏活动块";
    
    ls->shortcutShowApearProp   = "显示外观属性";
    ls->menuPropsApearance      = "外观";
    ls->propApearance           = "外观";
    ls->propThemeGB             = "布景主题 ";
    ls->propTheme               = "布景主题:";

    ls->propMonBrightness       = "亮度:";
    ls->propMonContrast         = "对比度:";
    ls->propMonSaturation       = "饱和度:";
    ls->propMonGamma            = "伽玛值:";
    ls->propMonScanlines        = " 扫描线:";

    ls->dlgRomType              = "Rom 类型:";
    ls->propOpenRomGB           = "打开 Rom 对话框 ";
    ls->propDefaultRomType      = "默认 Rom 类型:";
    ls->propGuessRomType        = "猜测 Rom 类型";

    ls->propFile                = "文件";
    ls->propSettDefSlotGB       = "拖放 ";
    ls->propSettDefSlots        = "插入 Rom 到:";
    ls->propSettDefSlot         = " 插槽";
    ls->propSettDefDrives       = "插入软盘到:";
    ls->propSettDefDrive        = " 驱动器";
    ls->menuPropsFile           = "文件";
    ls->shortcutShowFiles       = "显示文件设定";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "插入目录";
    ls->shortcutDiskDirInsertA  = "插入目录作为软盘A";
    ls->shortcutDiskDirInsertB  = "插入目录作为软盘B";
    ls->propMonDeInterlace      = " 高画质除网格技术";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "切换暂停开关";
    ls->shortcutSizeMinimized   = "最小化窗口";
    ls->shortcutEmuSpeedToggle  = "锁定最高速模拟";
    ls->shortcutToggleCpuTrace  = "启用/禁用 CPU 跟踪";

    ls->enumVideoEmuMonitor     = "显示器";

    ls->propEmuPauseSwitch      = " 暂停开关";
    ls->propVideoFreqText       = "视频频率:";
    ls->propVideoFreqAuto       = "自动";
    ls->propSndOversampleText   = "过采样:";

    ls->confChipExtras          = "附加";
    ls->confBoardGB             = "主版 ";
    ls->confBoardText           = "主版类型:";
    ls->dlgCpuFreqGB            = "CPU 频率 ";
    ls->dlgZ80FreqText          = "Z80 频率:";
    ls->dlgR800FreqText         = "R800 频率:";
    ls->dlgFdcGB                = "软盘控制器 ";
    ls->dlgCFdcNumDrivesText    = "驱动器数量:";

    ls->propPriorityBoost       = " 提升 blueMSX 的优先级";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "禁用软盘驱动器计时";
    ls->shortcutToggleFdcTiming = "启用/禁用软盘驱动器计时";

    // New entries in 2.2
    ls->menuCartHBI55           = "Sony HBI-55 卡带";
    ls->propSndPcm              = " Turbo-R PCM 音频";
    ls->propSndAY8910           = " AY8910 PSG 音频";
    ls->propSndSN76489          = " SN76489 PSG 音频";
    ls->enumVideoEmuHq2x        = "Hq2x";
    ls->propMonColorGhosting    = " RF-调制器";

    ls->keyconfigSelectedKey    = "选中键:";
    ls->keyconfigMappedTo       = "映射到:";
    ls->keyconfigMappingScheme  = "映射方案:";

    ls->discardChanges          = "要放弃修改吗？";
    ls->overwriteConfig         = "要覆盖当前的设置吗？";

    ls->confSaveAsTitle         = "配置另存为...";
    ls->confSaveAsName          = "名称:";

    ls->menuToolsKeyboard       = "键盘编辑工具";
    ls->shortcutShowKeyboard    = "显示键盘编辑工具";

    ls->menuVideoSource         = "视频来源";
    ls->menuVideoSourceDefault  = "未连接视频来源";
    ls->menuVideoChipAutodetect = "自动检测显示芯片";
    ls->propFullscreenResText   = "全屏幕分辨率:";
    ls->dlgSavePreview          = "显示预览";
    ls->dlgSaveDate             = "保存时间:";
    
    ls->enumVideoMonAmber       = "黄色";

    ls->menuPropsPorts          = "端口";
    ls->propPortsLptGB          = "并行端口 ";
    ls->propPortsComGB          = "串行端口 ";
    ls->propPortsLptText        = "端口:";
    ls->propPortsCom1Text       = "端口 1:";

    ls->shortcutShowDebugger    = "显示调试工具";
    ls->shortcutShowTrainer     = "显示修改工具";
    ls->shortcutShowPorts       = "显示端口设定";
    
    ls->propPorts               = "端口";
    ls->propPortsNone           = "无";

    // New entries in 2.3
    ls->enumControlsJoyTetris2Dongle = "俄罗斯方块 2 界面模组";

    ls->propPortsSimplCovox     = "SiMPL/Covox 数模转化器";
    ls->propPortsFile           = "打印到文件";
    ls->propPortsOpenLogFile    = "打开纪录文件";
    ls->propPortsFilenameText   = "文件名:";
    ls->propPortsEmulateMsxPrn  = "模拟:";

    ls->shortcutPrnFormFeed     = "打印机换页";

    ls->menuPrnFormfeed         = "换页";
    ls->menuFilePrn             = "打印机";
    ls->propPortsComFile        = "发送到文件";

    // New entries in 2.4
    ls->shortcutShowMixer       = "显示混音器";
    ls->menuToolsMixer          = "混音器";
    
    ls->propSndMidiInGB         = "MIDI 输入 ";
    ls->propSndMidiOutGB        = "MIDI 输出 ";
    ls->propSndMt32ToGmText     = " 映射 MT-32 乐器为一般 MIDI 设备";

    ls->textDevice              = "设备:";
    ls->textFilename            = "文件名:";
    ls->textFile                = "文件";
    ls->textNone                = "无";

    ls->enumEmuSyncNone         = "无";
    ls->enumEmuSyncAuto         = "自动 (快速)";
    ls->enumEmuSync1ms          = "同步于 MSX 的刷新";
    ls->enumEmuSyncVblank       = "同步于 PC 的垂直空白";

    ls->propMonEffectsGB        = "特效";

    ls->confSlot                = "插槽";
    ls->confSubslot             = "子插槽";

    ls->shortcut                = "快捷键";
    ls->hotkey                  = "热键";
    ls->unknown                 = "未知";
    ls->romImage                = "ROM 映像";
    ls->romImageOpen            = "打开 ROM 映像";
    ls->romCartridge            = "ROM 卡带";
    ls->allFiles                = "所有文件";
    ls->cpuState                = "CPU 状态";
    ls->diskImage               = "软盘映像";
    ls->casImage                = "磁带映像";

    ls->menuCartExternalRam     = "扩展内存";
};


#endif

