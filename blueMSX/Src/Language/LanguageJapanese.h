/*****************************************************************************

** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageJapanese.h,v $
**
** $Revision: 1.15 $
**
** $Date: 2005-03-13 05:27:58 $
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
    ls->statusBarStopped        = " 停止";
    ls->statusBarPaused         = " 中断";
    ls->statusBarRunning        = " 実行中";
    
    ls->menuHardReset           = "ハードリセット";
    ls->menuSoftReset           = "ソ\フトリセット";
    
    ls->menuCartInsert          = "挿入";
    ls->menuCartRemove          = "取り出し";
    ls->menuCartAutoReset       = "挿入/取り出し後リセット";
    ls->menuCartNoRecentFiles   = "- 使用ファイルなし -";
    ls->menuCartFMPac         = "FMPAC+カートリッジ";
    ls->menuCartPac           = "PAC+カートリッジ";
    ls->menuCartSpecial         = "その他";
    
    ls->menuDiskInsert          = "挿入";
    ls->menuDiskEject           = "取り出し";
    ls->menuDiskAutoStart       = "挿入/取り出し後リセット";
    ls->menuDiskNoRecentFiles   = "- 使用ファイルなし -";
    
    ls->menuCasInsert           = "挿入";
    ls->menuCasEject            = "取り出し";
    ls->menuCasSetPosition      = "テープ位置セット";
    ls->menuCasRewind           = "巻き戻し";
    ls->menuCasNoRecentFiles   = "- 使用ファイルなし -";
    
    ls->menuZoomNormal          = "標準サイズ";
    ls->menuZoomDouble          = "2倍サイズ";
    ls->menuZoomFullscreen      = "フルスクリーン";
    

    ls->menuPropsEmulation      = "エミュレーション";
    ls->menuPropsVideo          = "ビデオ";
    ls->menuPropsSound          = "サウンド";
    ls->menuPropsControls       = "コントロール";
    ls->menuPropsPerformance    = "パフォーマンス";
    ls->menuPropsLanguage       = "言語";
    
    ls->menuHelpHelp            = "ヘルプ目次";
    ls->menuHelpAbout           = "blueMSXについて";

    ls->menuFileCart1           = "ROMスロット 1";
    ls->menuFileCart2           = "ROMスロット 2";
    ls->menuFileDiskA           = "ディスクドライブ A";
    ls->menuFileDiskB           = "ディスクドライブ B";
    ls->menuFileCas             = "カセットテープ";
    ls->menuFileLoadState       = "CPUステート 読み込み";
    ls->menuFileSaveState       = "CPUステート 保存";
    ls->menuFileQLoadState      = "クイックロード";
    ls->menuFileQSaveState      = "クイックセーブ";
    ls->menuFileCaptureAudio    = "録音";
    ls->menuFileScreenShot      = "スクリーンショット";
    ls->menuFileExit            = "終了";

    ls->menuRunRun              = "実行";
    ls->menuRunPause            = "一時停止";
    ls->menuRunStop             = "停止";
    ls->menuRunSoftReset        = "ソ\フトリセット";
    ls->menuRunHardReset        = "ハードリセット";
    ls->menuRunCleanReset       = "クリーンリセット";

    ls->menuFile                = "ファイル";
    ls->menuRun                 = "実行";
    ls->menuWindow              = "ウィンドウ";
    ls->menuOptions             = "オプション";

    ls->menuHelp                = "ヘルプ";
    

    ls->errorTitle              = "blueMSX エラー";
    ls->errorEnterFullscreen    = "フルスクリーンモードにできません.           \n";
    ls->errorDirectXFailed      = "DirectX オブジェクトを作成できません.           \nGDIを代わりに使用します.\nグラフィックカードの設定を確認してください.";

    ls->errorNoRomInZip         = "zipファイルの中に.romファイルが見つかりません.";
    ls->errorNoDskInZip         = "zipファイルの中に.dskファイルが見つかりません.";
    ls->errorNoCasInZip         = "zipファイルの中に.casファイルが見つかりません.";

    ls->errorNoHelp             = "blueMSXのヘルプファイルが見つかりません.";
    ls->errorStartEmu           = "MSXエミュレータの開始に失敗しました.";

    ls->tooltipReset            = "MSXをリセットします";
    ls->tooltipCart1            = "スロット1にカートリッジを挿入します";
    ls->tooltipCart2            = "スロット2にカートリッジを挿入します";
    ls->tooltipDiskA            = "ドライブAにディスクを挿入します";
    ls->tooltipDiskB            = "ドライブBにディスクを挿入します";
    ls->tooltipCas              = "カセットテープを挿入します";
    ls->tooltipStart            = "エミュレーションを開始します";
    ls->tooltipResume           = "エミュレーションを続行します";
    ls->tooltipPause            = "エミュレーションを一時停止します";
    ls->tooltipWindowSize       = "ウィンドウのサイズを変更します";
    ls->tooltipProperties       = "設定ダイアログを開きます";
    ls->tooltipHelp             = "ヘルプを開きます";

    ls->dlgMainWindow           = "  blueMSX";
    ls->dlgLoadRom              = "blueMSX - romイメージを選択";
    ls->dlgLoadDsk              = "blueMSX - dskイメージを選択";
    ls->dlgLoadCas              = "blueMSX - casイメージを選択";
    ls->dlgLoadRomDskCas        = "blueMSX - rom, dsk, またはcasイメージを選択";
    ls->dlgLoadRomDesc          = "読み込むromイメージ:";
    ls->dlgLoadDskDesc          = "読み込むdskイメージ:";
    ls->dlgLoadCasDesc          = "読み込むcasイメージ:";
    ls->dlgLoadRomDskCasDesc    = "読み込むrom, dsk, casイメージ:";
    ls->dlgLoadState            = "CPUステート 読み込み";
    ls->dlgSaveState            = "CPUステート 保存";
    ls->dlgInsertRom1           = "ROMカートリッジをスロット1に挿入";
    ls->dlgInsertRom2           = "ROMカートリッジをスロット2に挿入";
    ls->dlgInsertDiskA          = "ディスクイメージをドライブAに挿入";
    ls->dlgInsertDiskB          = "ディスクイメージをドライブBに挿入";
    ls->dlgInsertCas            = "カセットテープを挿入";

    ls->dlgOK                   = "OK";
    ls->dlgCancel               = "キャンセル";

    ls->dlgTapeTitle            = "blueMSX - カセットテープ";
    ls->dlgTapeFrameText        = "テープ位置";
    ls->dlgTapeCurrentPos       = "現在位置";
    ls->dlgTapeTotalTime        = "トータルタイム";

    ls->dlgZipReset             = "挿入後リセット";

    ls->dlgAboutTitle           = "blueMSXについて";

    ls->dlgJoyTitle1            = "blueMSX - ジョイスティック セット A";
    ls->dlgJoyTitle2            = "blueMSX - ジョイスティック セット B";
    ls->dlgJoyUpText            = "上";
    ls->dlgJoyDownText          = "下";
    ls->dlgJoyLeftText          = "左";
    ls->dlgJoyRightText         = "右";
    ls->dlgJoyButton1Text       = "ボタン1";
    ls->dlgJoyButton2Text       = "ボタン2";
    ls->dlgJoyGB                = "キー設定";

    ls->dlgLangLangText         = "blueMSXで使用する言語を選択してください";
    ls->dlgLangLangTitle        = "blueMSX - 言語";

    ls->propTitle               = "blueMSX - 設定";
    ls->propEmulation           = "エミュレーション";
    ls->propVideo               = "ビデオ";
    ls->propSound               = "サウンド";
    ls->propControls            = "コントロール";
    ls->propPerformance         = "パフォーマンス";
    

    ls->propEmuGeneralGB        = "一般 ";
    ls->propEmuFamilyText       = "MSXの種類:";
    ls->propEmuMemoryGB         = "メモリ ";
    ls->propEmuRamSizeText      = "メインRAM:";
    ls->propEmuVramSizeText     = "VRAM:";
    ls->propEmuSpeedGB          = "スピード ";
    ls->propEmuSpeedText        = "スピード:";

    ls->propMonMonGB            = "モニター ";
    ls->propMonTypeText         = "モニターの種類:";
    ls->propMonEmuText          = "モニターエミュレーション:";
    ls->propVideoYypeText       = "映像方式:";
    ls->propWindowSizeText      = "ウィンドウサイズ:";

    ls->propPerfVideoDrvGB      = "ビデオドライバ ";
    ls->propPerfVideoDispDrvText= "ディスプレイドライバ:";
    ls->propPerfFrameSkipText   = "フレームスキップ:";
    ls->propPerfAudioDrvGB      = "サウンドドライバ ";
    ls->propPerfAudioDrvText    = "サウンドドライバ:";
    ls->propPerfAudioBufSzText  = "サウンドバッファ:";
    ls->propPerfEmuGB           = "エミュレーション ";
    ls->propPerfSyncModeText    = "SYNCモード:";

    ls->propSndChipEmuGB        = "サウンドのエミュレーション ";
    ls->propSndMixerGB          = "ミキサー ";
    ls->propSndMonoText         = "mono";
    ls->propSndStereoText       = "stereo";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "MASTER";

    ls->propJoyPort1GB          = "ジョイスティックポート 1 ";
    ls->propJoyPort2GB          = "ジョイスティックポート 2 ";
    ls->propJoyAutofireText     = "連射:";
    ls->propJoyKeysetGB         = "ジョイスティック設定 ";
    ls->propJoyKeyest1          = "セットAの設定 ";
    ls->propJoyKeyest2          = "セットBの設定 ";

    ls->enumVideoMonColor       = "カラー";
    ls->enumVideoMonGrey        = "モノクロ";
    ls->enumVideoMonGreen       = "グリーン";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "なし";
    ls->enumVideoEmuYc          = "Y/Cケーブル (鮮明)";
    ls->enumVideoEmuYcBlur      = "Y/Cケーブル＋ノイズ (鮮明)";
    ls->enumVideoEmuComp        = "コンポジット (不鮮明)";
    ls->enumVideoEmuCompBlur    = "コンポジット＋ノイズ (不鮮明)";
    ls->enumVideoEmuScale2x     = "Scale 2x";

    ls->enumVideoSize1x         = "標準サイズ - 320x200";
    ls->enumVideoSize2x         = "2倍サイズ - 640x400";
    ls->enumVideoSizeFullscreen = "フルスクリーン";

    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "なし";
    ls->enumVideoFrameskip1     = "1フレーム";
    ls->enumVideoFrameskip2     = "2フレーム";
    ls->enumVideoFrameskip3     = "3フレーム";
    ls->enumVideoFrameskip4     = "4フレーム";
    ls->enumVideoFrameskip5     = "5フレーム";

    ls->enumSoundDrvNone        = "サウンドなし";
    ls->enumSoundDrvWMM         = "WMMドライバ";
    ls->enumSoundDrvDirectX     = "DirectXドライバ";

    ls->enumEmuSync1ms          = "1ms (正確)";
    ls->enumEmuSyncAuto         = "自動 (推奨)";

    ls->enumControlsJoyNone     = "なし";
    ls->enumControlsJoyNumpad   = "テンキー";
    ls->enumControlsJoyKeysetA  = "セットA";
    ls->enumControlsJoyKeysetB  = "セットB";
    ls->enumControlsJoyPCjoy1   = "PCジョイスティック#1";
    ls->enumControlsJoyPCjoy2   = "PCジョイスティック#2";
    ls->enumControlsJoyMouse    = "マウス";

    ls->enumControlsAfOff       = "なし";
    ls->enumControlsAfSlow      = "低速";
    ls->enumControlsAfMedium    = "中";
    ls->enumControlsAfFast      = "高速";

    ls->dlgAboutAbout           = "このソ\フトについて\r\n==========";
    ls->dlgAboutVersion         = "バージョン:";
    ls->dlgAboutBuildNumber     = "ビルド:";
    ls->dlgAboutBuildDate       = "日付:";
    ls->dlgAboutCreat           = "製作 Daniel Vik";
    ls->dlgAboutThanks          = "ご協力いただいた方々\r\n============";
    ls->dlgAboutLisence         = "======\r\n\r\n"
                                  "このソ\フトウェアは現状をそのままの状態で配布するものであり, 明示的または"
                                  "黙示的を問わず一切の保証はありません. またこのソ\フトウェアの使用の結果生じた"
                                  "いかなる損害についても, 作者は責任を負いません.\r\n\r\n"
                                  "詳しい説明については, www.bluemsx.com をご覧ください. ";
    
    ls->dlgAboutDevel           = "開発者\r\n========";

    // New entries
    ls->menuTools                = "ツール";
    ls->menuToolsMachine         = "マシン構\成編集";
    ls->menuPropsSettings        = "その他";
    ls->menuCasRewindAfterInsert = "挿入後巻き戻す";
    ls->menuCasUseReadOnly       = "テープを読み込み専用にする";
    ls->lmenuCasSaveAs           = "テープを別名で保存...";

    ls->dlgSaveCassette          = "blueMSX - テープを保存";
    ls->dlgTapeCustom            = "カスタムファイルを表\示";
    ls->dlgTapeSetPosText        = "テープ位置:";
    ls->dlgTabPosition           = "位置";
    ls->dlgTabType               = "タイプ";
    ls->dlgTabFilename           = "ファイル名";

    ls->propSettings             = "その他";
    
    ls->propSetFileHistoryGB     = "ファイルヒストリ ";
    ls->propSetFileHistorySize   = "ファイルヒストリの個数:";
    ls->propSetFileHistoryClear  = "ヒストリの消去";
    ls->propSetScreenSaverGB     = "スクリーンセーバ ";
    ls->propSetScreenSaver       = " blueMSXの動作中はスクリーンセーバを無効にする";

    ls->confTitle                = "blueMSX - マシン構\成編集";
    ls->confSave                 = "保存";
    ls->confSaveAs               = "別名保存...";
    ls->confRun                  = "起動";
    ls->confClose                = "閉じる";
    ls->confConfigText           = "マシン構\成";
    ls->confSlotLayout           = "スロット構\成";
    ls->confMemory               = "メモリ";
    ls->confChipEmulation        = "チップ";

    ls->confSlotLayoutGB         = "スロット構\成 ";
    ls->confSlotExtSlotGB        = "拡張スロット ";
    ls->confSlotSlot0            = "スロット 0";
    ls->confSlotSlot1            = "スロット 1";
    ls->confSlotSlot2            = "スロット 2";
    ls->confSlotSlot3            = "スロット 3";
    ls->confSlotCart1            = "カートリッジ 1:";
    ls->confSlotCart2            = "カートリッジ 2:";
    ls->confSlotPrimary          = "基本";
    ls->confSlotExpanded         = "拡張 (4つの副スロット)";

    ls->confMemAdd               = "追加...";
    ls->confMemEdit              = "編集...";
    ls->confMemRemove            = "削除";
    ls->confMemSlot              = "スロット";
    ls->confMemAddresss          = "アドレス";
    ls->confMemType              = "タイプ";
    ls->confMemRomImage          = "ロム";
    
    ls->confChipVideoGB          = "ビデオ ";
    ls->confChipVideoChip        = "ビデオチップ:";
    ls->confChipVideoRam         = "ビデオRAM:";
    ls->confChipSoundGB          = "サウンド ";

    ls->slotEditMemTitle         = "blueMSX - マッパの編集";
    ls->slotEditMemGB            = "マッパの詳細 ";
    ls->slotEditMemType          = "タイプ:";
    ls->slotEditMemFile          = "ファイル:";
    ls->slotEditMemAddress       = "アドレス:";
    ls->slotEditMemSize          = "サイズ:";
    ls->slotEditMemSlot          = "スロット:";

    ls->confSaveAsTitle          = "blueMSX - マシン構\成を別名で保存...";
    ls->confSaveAsMachineName    = "構\成名:";

    ls->confSaveTitle            = "blueMSX - マシン構\成の保存";
    ls->confSaveText             = "マシン構\成を上書きしてよろしいですか?";

    ls->dlgOpen                  = "開く";
    ls->confEditMemInternalRoms  = "blueMSX - 内蔵ロム";

    ls->confSaveTitle            = "blueMSX - マシン構\成編集の終了";
    ls->confSaveText             = "現在の構\成が失われますが、よろしいですか?";
    
    ls->confExitSaveTitle        = "blueMSX - マシン構\成編集の終了";
    ls->confExitSaveText         = "現在の構\成が失われますが、よろしいですか?";

    ls->confDiscardTitle         = "blueMSX - マシン構\成編集";
    
    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypesGB          = "ファイル種類 ";
    ls->propFileTypes            = " blueMSXに関連付けるファイル種類 (.rom, .dsk, .cas, .sta)";
    ls->propDisableWinKeys       = " blueMSXを使用中に左右のWindowsキーを無効化する"; 
    ls->propWindowsEnvGB         = "ウィンドウズ環境 ";
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW accel."; 
    ls->enumVideoDrvDirectDrawHWSys = "DirectDraw mix."; 
    ls->propMonHorizStretch      = " 水平 ストレッチ";  
    ls->propClearHistory         = "ヒストリの消去を実行して、よろしいですか?"; 

    ls->propEmuFrontSwitchGB     = "パナソ\ニックスイッチ "; 
    ls->propEmuFrontSwitch       = " 前面スイッチ"; 
    ls->propEmuAudioSwitch       = " MSX-AUDIO カートリッジ スイッチ"; 
    ls->propMonVertStretch       = " 垂直 ストレッチ";

    ls->dlgCmosGB                = "CMOS "; 
    ls->dlgCmosEnable            = " CMOSを有効"; 
    ls->dlgCmosBattery           = " 内蔵バッテリーを有効化";
     
    ls->menuCartSnatcher         = "The Snatcher カートリッジ";
    ls->menuCartSdSnatcher       = "SD-Snatcher カートリッジ";
    ls->menuCartSCCMirrored      = "SCC Mirrored カートリッジ";
    ls->menuCartSCCExpanded      = "SCC Expanded カートリッジ";
    ls->menuCartSCCPlus          = "SCC+  カートリッジ";
    ls->menuCartSCC              = "SCC  カートリッジ";
    
    ls->warningTitle             = "blueMSX - Warning";
    ls->tooltipStop              = "エミュレーションを停止します";

    // New entries in 1.5.1
    ls->enumControlsJoyKeyset   = "キーセット";    
    ls->propJoyConfigKeyset     = "コンフィグ キーセット";
    ls->propJoyControlText      = "コントロール:";
    ls->propJoyButtonText       = "ボタン";
    ls->propJoyButtonAText      = "ボタン A:";
    ls->propJoyButtonBText      = "ボタン B:";

    ls->menuToolsShortcuts      = "ショートカット構\成編集";

    ls->shortcutSaveConfig      = "blueMSX - 構\成の保存";
    ls->shortcutOverwriteConfig = "ショートカット構\成を上書きしてよろしいですか?:";
    ls->shortcutExitConfig      = "blueMSX - ショートカット構\成編集の終了";
    ls->shortcutDiscardConfig   = "現在の構\成が失われますが、よろしいですか?";
    ls->shortcutSaveConfigAs    = "blueMSX - ショートカット構\成を別名で保存...";
    ls->shortcutConfigName      = "構\成名:";
    ls->shortcutNewProfile      = "< 新規 プロファイル >";
    ls->shortcutConfigTitle     = "blueMSX - ショートカット 構\成編集";
    ls->shortcutAssign          = "割り当て";
    ls->shortcutPressText       = "ショートカットキー入力欄:";
    ls->shortcutScheme          = "マッピングスキーム:";

    ls->shortcutCartInsert1     = "カートリッジ1 挿入";
    ls->shortcutCartRemove1     = "カートリッジ1 取り出し";
    ls->shortcutCartInsert2     = "カートリッジ2 挿入";
    ls->shortcutCartRemove2     = "カートリッジ2 取り出し";
    ls->shortcutCartAutoReset   = "カートリッジ 挿入/取り出し後リセット";
    ls->shortcutDiskInsertA     = "ディスクA 挿入";
    ls->shortcutDiskRemoveA     = "ディスクA 取り出し";
    ls->shortcutDiskChangeA     = "ディスクA 入れ替え(v-DRIVE)";
    ls->shortcutDiskAutoResetA  = "ディスクA 挿入/取り出し後リセット";
    ls->shortcutDiskInsertB     = "ディスクB 挿入";
    ls->shortcutDiskRemoveB     = "ディスクB 取り出し";
    ls->shortcutCasInsert       = "テープ 挿入";
    ls->shortcutCasEject        = "テープ 取り出し";
    ls->shortcutCasAutorewind   = "テープ 挿入後巻き戻す";
    ls->shortcutCasReadOnly     = "テープを読み込み専用にする";
    ls->shortcutCasSetPosition  = "テープ位置セット";
    ls->shortcutCasRewind       = "テープ巻き戻し";
    ls->shortcutCasSave         = "テープイメージ 保存";
    ls->shortcutCpuStateLoad    = "CPUステート読み込み";
    ls->shortcutCpuStateSave    = "CPUステート保存";
    ls->shortcutCpuStateQload   = "クイックロード";
    ls->shortcutCpuStateQsave   = "クリックセーブ";
    ls->shortcutAudioCapture    = "サウンド録音の実行/停止";
    ls->shortcutScreenshotOrig  = "スクリーンショット";
    ls->shortcutScreenshotSmall = "無フィルター標準サイズ スクリーンショット";
    ls->shortcutScreenshotLarge = "無フィルター2倍サイズ スクリーンショット";
    ls->shortcutQuit            = "blueMSXを終了する";
    ls->shortcutRunPause        = "エミュレーションの実行/ポーズ";
    ls->shortcutStop            = "停止";
    ls->shortcutResetHard       = "ハードリセット";
    ls->shortcutResetSoft       = "ソ\フトリセット";
    ls->shortcutResetClean      = "クリーンリセット";
    ls->shortcutSizeSmall       = "標準サイズ";
    ls->shortcutSizeNormal      = "2倍サイズ";
    ls->shortcutSizeFullscreen  = "フルスクリーン";
    ls->shortcutToggleFullscren = "フルスクリーン化";
    ls->shortcutVolumeIncrease  = "ボリュームを上げる";
    ls->shortcutVolumeDecrease  = "ボリュームを下げる";
    ls->shortcutVolumeMute      = "ミュート";
    ls->shortcutSwitchMsxAudio  = "MSX-AUDIOカートリッジスイッチ";
    ls->shortcutSwitchFront     = "前面スイッチ";
    ls->shortcutToggleMouseLock = "マウスロック";
    ls->shortcutEmuSpeedMax     = "エミュレーション実行速度を最速化";
    ls->shortcutEmuSpeedNormal  = "エミュレーション実行速度を標準化";
    ls->shortcutEmuSpeedInc     = "エミュレーション速度を加速";
    ls->shortcutEmuSpeedDec     = "エミュレーション速度の減速";
    ls->shortcutShowEmuProp     = "エミュレーション設定画面の表\示";
    ls->shortcutShowVideoProp   = "ビデオ設定画面の表\示";
    ls->shortcutShowAudioProp   = "サウンド設定画面の表\示";
    ls->shortcutShowCtrlProp    = "コントロール設定画面の表\示";
    ls->shortcutShowPerfProp    = "パフォーマンス設定画面の表\示";
    ls->shortcutShowSettProp    = "その他設定画面の表\示";
    ls->shortcutShowLanguage    = "言語ダイアログの表\示";
    ls->shortcutShowMachines    = "マシン構\成編集の表\示";
    ls->shortcutShowShortcuts   = "ショートカットエディターの表\示";
    ls->shortcutShowHelp        = "ヘルプダイアログの表\示";
    ls->shortcutShowAbout       = "blueMSXについての表\示";

    ls->shortcutSpecialMenu1    = "カートリッジ1のその他メニューの表\示";
    ls->shortcutSpecialMenu2    = "カートリッジ2のその他メニューの表\示";
    ls->shortcutVolumeStereo    = "モノ/ステレオの切り替え";
    ls->shortcutThemeSwitch     = "テーマの切り替え";
    ls->shortcutToggleSpriteEnable = "スプライトの表\示/無効";

    ls->shortcutShowApearProp   = "外観設定画面の表\示";
    ls->menuPropsApearance      = "外観";
    ls->propApearance           = "外観";
    ls->propThemeGB             = "テーマ ";
    ls->propTheme               = "テーマ";
    ls->propThemeClassic        = "クラシック";
    ls->propThemeBlue           = "DIGIblue";

    ls->propMonBrightness       = "明るさ:";
    ls->propMonContrast         = "コントラスト:";
    ls->propMonSaturation       = "彩度:";
    ls->propMonGamma            = "ガンマ:";
    ls->propMonScanlines        = "スキャンライン:";
    ls->dlgRomType              = "ロム種類:"; 
    ls->propOpenRomGB           = "ロムダイアログを開く"; 
    ls->propDefaultRomType      = "標準ロムタイプ:"; 
    ls->propGuessRomType        = "ロム種類を推測";

    ls->propFile                = "ファイル"; 
    ls->propSettDefSlotGB       = "ドラッグ＆ドロップ "; 
    ls->propSettDefSlots        = "ロムを挿入するスロット:"; 
    ls->propSettDefSlot1        = " スロット 1"; 
    ls->propSettDefSlot2        = " スロット 2"; 
    ls->propSettDefDrives       = "ディスクを挿入するドライブ:"; 
    ls->propSettDefDriveA       = " ドライブ A"; 
    ls->propSettDefDriveB       = " ドライブ B"; 
    ls->menuPropsFile           = "ファイル";
    ls->shortcutShowFiles       = "ファイルダイアログを表\示";

    // New entries in 1.6.1 
    ls->menuDiskDirInsert       = "ディレクトリ挿入"; 
    ls->shortcutDiskDirInsertA  = "ディレクトリをディスクAとして挿入"; 
    ls->shortcutDiskDirInsertB  = "ディレクトリをディスクBとして挿入";
    ls->propMonDeInterlace      = " デインターレース";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "パナソ\ニック系 ポーズスイッチ";
    ls->shortcutSizeMinimized   = "ウィンドウ 最小化";
    ls->shortcutEmuSpeedToggle  = "最速動作の有無";
    ls->shortcutToggleCpuTrace  = "CPUトレースの有無";

    ls->enumVideoEmuMonitor     = "モニター";

    ls->propEmuPauseSwitch      = " ポーズ スイッチ";
    ls->propVideoFreqText       = "ビデオ 周波数:";
    ls->propVideoFreqAuto       = "自動";
    ls->propSndOversampleText   = "サンプリング:";

    ls->confChipExtras          = "エキストラ";
    ls->confBoardGB             = "基盤 ";
    ls->confBoardText           = "基盤 タイプ:";
    ls->dlgCpuFreqGB            = "CPU 周波数 ";
    ls->dlgZ80FreqText          = "Z80 周波数:";
    ls->dlgR800FreqText         = "R800 周波数:";
    ls->dlgFdcGB                = "フロッピーディスクコントローラー ";
    ls->dlgCFdcNumDrivesText    = "ドライブの数:";

    ls->propPriorityBoost        = " blueMSXに割当てるプライオリティーのブースト";

    // New entries in 2.0.1
    ls->propEmuFdcTiming        = "FDDドライブのタイミングを無効化";
    ls->shortcutToggleFdcTiming = "FDDドライブのタイミング 有無";
    ls->propUseRegistry         = "レジストリに設定を保存する";

    // New entries in 2.2
    ls->menuCartHBI55           = "Sony HBI-55 カートリッジ";
    ls->propSndPcm              = " Turbo-R PCM";
    ls->propSndAY8910           = " AY8910 PSG";
    ls->propSndSN76489          = " SN76489 PSG";
    ls->enumVideoEmuHq2x        = "Hq2x";
    ls->propMonColorGhosting    = "RFモジュレータ";

    ls->keyconfigSelectedKey    = "選択キー:";
    ls->keyconfigMappedTo       = "対象キー:";
    ls->keyconfigMappingScheme  = "マッピングスキーム:";

    ls->discardChanges          = "構\成が失われますが、よろしいですか?";
    ls->overwriteConfig         = "構\成を上書きしてよろしいですか?";

    ls->confSaveAsTitle         = "別名で保存...";
    ls->confSaveAsName          = "名前:";

    ls->menuToolsKeyboard       = "キーボード構\成編集";
    ls->shortcutShowKeyboard    = "キーボード構\成編集の表\示";

    ls->menuVideoSource         = "ビデオソ\ース";
    ls->menuVideoSourceDefault  = "ビデオソ\ースの接続がありません";
    ls->menuVideoChipAutodetect = "ヒデオチップの自動認識";
    ls->propFullscreenResText   = "フルスクリーンの解像度:";
    ls->dlgSavePreview          = "プレビュー表\示";
    ls->dlgSaveDate             = "セーブ時刻:";
    
    ls->enumVideoMonAmber       = "アンバー";

    ls->menuPropsPorts          = "ポート";
    ls->propPortsLptGB          = "パラレルポート ";
    ls->propPortsComGB          = "シリアルポート ";
    ls->propPortsLptText        = "ポート:";
    ls->propPortsCom1Text       = "ポート 1:";

	ls->shortcutShowDebugger    = "デバッガー表\示";
    ls->shortcutShowTrainer     = "トレーナー表\示";
    ls->shortcutShowPorts       = "ポート構\成設定の表\示";
};


#endif

