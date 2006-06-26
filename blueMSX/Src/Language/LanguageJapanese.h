/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/LanguageJapanese.h,v $
**
** $Revision: 1.35 $
**
** $Date: 2006-06-26 00:27:58 $
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
    // Language lines
    //----------------------

    ls->langChineseSimplified   = "Chinese Simplified";
    ls->langChineseTraditional  = "Chinese Traditional";
    ls->langDutch               = "Dutch";
    ls->langEnglish             = "English";
    ls->langFinnish             = "Finnish";
    ls->langFrench              = "French";
    ls->langGerman              = "German";
    ls->langItalian             = "Italian";
    ls->langJapanese            = "Japanese";
    ls->langKorean              = "Korean";
    ls->langPolish              = "Polish";
    ls->langPortuguese          = "Portuguese";
    ls->langSpanish             = "Spanish";
    ls->langSwedish             = "Swedish";


    //----------------------
    // Generic lines
    //----------------------

    ls->textDevice              = "デバイス:"; 
    ls->textFilename            = "ファイル名:"; 
    ls->textFile                = "ファイル"; 
    ls->textNone                = "無し"; 
    ls->textUnknown             = "Unknown";                            // New in 2.5


    //----------------------
    // Warning and Error lines
    //----------------------

    ls->warningTitle            = "blueMSX - Warning";
    ls->warningDiscardChanges   = "構\成が失われますが、よろしいですか?";
    ls->warningOverwriteFile    = "Do you want to overwrite the file:"; // New in 2.5
    ls->errorTitle              = "blueMSX エラー";
    ls->errorEnterFullscreen    = "フルスクリーンモードにできません.           \n";
    ls->errorDirectXFailed      = "DirectX オブジェクトを作成できません.           \nGDIを代わりに使用します.\nグラフィックカードの設定を確認してください.";
    ls->errorNoRomInZip         = "zipファイルの中に.romファイルが見つかりません.";
    ls->errorNoDskInZip         = "zipファイルの中に.dskファイルが見つかりません.";
    ls->errorNoCasInZip         = "zipファイルの中に.casファイルが見つかりません.";
    ls->errorNoHelp             = "blueMSXのヘルプファイルが見つかりません.";
    ls->errorStartEmu           = "MSXエミュレータの開始に失敗しました.";
    ls->errorPortableReadonly   = "Portable device is readonly";        // New in 2.5


    //----------------------
    // File related lines
    //----------------------

    ls->fileRom                 = "ロム イメージ"; 
    ls->fileAll                 = "全てのファイル"; 
    ls->fileCpuState            = "CPU ステート"; 
    ls->fileDisk                = "ディスク イメージ"; 
    ls->fileCas                 = "テープ イメージ"; 


    //----------------------
    // Menu related lines
    //----------------------

    ls->menuNoRecentFiles       = "- 使用ファイルなし -";
    ls->menuInsert              = "挿入";
    ls->menuEject               = "取り出し";

    ls->menuCartGameReader      = "Game Reader";                        // New in 2.5
    ls->menuCartIde             = "IDE";                                // New in 2.5
    ls->menuCartBeerIde         = "Beer";                               // New in 2.5
    ls->menuCartGIde            = "GIDE";                               // New in 2.5
    ls->menuCartSunriseIde      = "Sunrise";                            // New in 2.5
    ls->menuCartSCC              = "SCC  カートリッジ";
    ls->menuCartSCCPlus          = "SCC+  カートリッジ";
    ls->menuCartFMPac           = "FMPAC+カートリッジ";
    ls->menuCartPac             = "PAC+カートリッジ";
    ls->menuCartHBI55           = "Sony HBI-55 カートリッジ";
    ls->menuCartInsertSpecial   = "Insert Special";                     // New in 2.5
    ls->menuCartMegaRam         = "MegaRAM";                            // New in 2.5
    ls->menuCartExternalRam     = "外部 ラム"; 

    ls->menuDiskInsertNew       = "Insert New Disk Image";              // New in 2.5
    ls->menuDiskDirInsert       = "ディレクトリ挿入"; 
    ls->menuDiskAutoStart       = "挿入/取り出し後リセット";
    ls->menuCartAutoReset       = "挿入/取り出し後リセット";

    ls->menuCasRewindAfterInsert = "挿入後巻き戻す";
    ls->menuCasUseReadOnly       = "テープを読み込み専用にする";
    ls->lmenuCasSaveAs           = "テープを別名で保存...";
    ls->menuCasSetPosition      = "テープ位置セット";
    ls->menuCasRewind           = "巻き戻し";
    
    ls->menuPrnFormfeed         = "フォームフィード"; 

    ls->menuZoomNormal          = "標準サイズ";
    ls->menuZoomDouble          = "2倍サイズ";
    ls->menuZoomFullscreen      = "フルスクリーン";
    
    ls->menuPropsEmulation      = "エミュレーション";
    ls->menuPropsVideo          = "ビデオ";
    ls->menuPropsSound          = "サウンド";
    ls->menuPropsControls       = "コントロール";
    ls->menuPropsPerformance    = "パフォーマンス";
    ls->menuPropsSettings        = "その他";
    ls->menuPropsFile           = "ファイル";
    ls->menuPropsLanguage       = "言語";
    ls->menuPropsPorts          = "ポート";
    
    ls->menuVideoChipAutodetect = "ヒデオチップの自動認識";
    ls->menuVideoSource         = "Video Out Source";                   // New in 2.5
    ls->menuVideoSourceDefault  = "No Video Out Source Connected";      // New in 2.5    
    ls->menuVideoInSource       = "Video In Source";                    // New in 2.5
    ls->menuVideoInBitmap       = "Bitmap File";                        // New in 2.5

    ls->menuHelpHelp            = "ヘルプ目次";
    ls->menuHelpAbout           = "blueMSXについて";

    ls->menuFileCart            = "ROMスロット";
    ls->menuFileDisk            = "ディスクドライブ";
    ls->menuFileCas             = "カセットテープ";
    ls->menuFilePrn             = "プリンター"; 
    ls->menuFileLoadState       = "CPUステート 読み込み";
    ls->menuFileSaveState       = "CPUステート 保存";
    ls->menuFileQLoadState      = "クイックロード";
    ls->menuFileQSaveState      = "クイックセーブ";
    ls->menuFileCaptureAudio    = "録音";
    ls->menuFileScreenShot      = "スクリーンショット";
    ls->menuFileExit            = "終了";

    ls->menuFileHarddisk        = "Hard Disk";                          // New in 2.5
    ls->menuFileHarddiskNoPesent= "No Controllers Present";             // New in 2.5

    ls->menuRunRun              = "実行";
    ls->menuRunPause            = "一時停止";
    ls->menuRunStop             = "停止";
    ls->menuRunSoftReset        = "ソ\フトリセット";
    ls->menuRunHardReset        = "ハードリセット";
    ls->menuRunCleanReset       = "クリーンリセット";

    ls->menuToolsMachine         = "マシン構\成編集";
    ls->menuToolsShortcuts      = "ショートカット構\成編集";
    ls->menuToolsKeyboard       = "キーボード構\成編集";
    ls->menuToolsMixer          = "ミキサー"; 
    ls->menuToolsDebugger       = "Debugger";               // New in 2.5
    ls->menuToolsTrainer        = "Trainer";                // New in 2.5
    ls->menuToolsTraceLogger    = "Trace Logger";           // New in 2.5

    ls->menuFile                = "ファイル";
    ls->menuRun                 = "実行";
    ls->menuWindow              = "ウィンドウ";
    ls->menuOptions             = "オプション";
    ls->menuTools                = "ツール";
    ls->menuHelp                = "ヘルプ";


    //----------------------
    // Dialog related lines
    //----------------------

    ls->dlgOK                   = "OK";
    ls->dlgOpen                  = "開く";
    ls->dlgCancel               = "キャンセル";
    ls->dlgSave                 = "保存";
    ls->dlgSaveAs               = "別名保存...";
    ls->dlgRun                  = "起動";
    ls->dlgClose                = "閉じる";

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
    ls->dlgSaveCassette          = "blueMSX - テープを保存";
    ls->dlgInsertRom1           = "ROMカートリッジをスロット1に挿入";
    ls->dlgInsertRom2           = "ROMカートリッジをスロット2に挿入";
    ls->dlgInsertDiskA          = "ディスクイメージをドライブAに挿入";
    ls->dlgInsertDiskB          = "ディスクイメージをドライブBに挿入";
    ls->dlgInsertHarddisk       = "Insert Hard Disk";                   // New in 2.5
    ls->dlgInsertCas            = "カセットテープを挿入";
    ls->dlgRomType              = "ロム種類:"; 

    ls->dlgTapeTitle            = "blueMSX - カセットテープ";
    ls->dlgTapeFrameText        = "テープ位置";
    ls->dlgTapeCurrentPos       = "現在位置";
    ls->dlgTapeTotalTime        = "トータルタイム";
    ls->dlgTapeSetPosText        = "テープ位置:";
    ls->dlgTapeCustom            = "カスタムファイルを表\示";
    ls->dlgTabPosition           = "位置";
    ls->dlgTabType               = "タイプ";
    ls->dlgTabFilename           = "ファイル名";
    ls->dlgZipReset             = "挿入後リセット";

    ls->dlgAboutTitle           = "blueMSXについて";

    ls->dlgLangLangText         = "blueMSXで使用する言語を選択してください";
    ls->dlgLangLangTitle        = "blueMSX - 言語";

    ls->dlgAboutAbout           = "このソ\フトについて\r\n==========";
    ls->dlgAboutVersion         = "バージョン:";
    ls->dlgAboutBuildNumber     = "ビルド:";
    ls->dlgAboutBuildDate       = "日付:";
    ls->dlgAboutCreat           = "製作 Daniel Vik";
    ls->dlgAboutDevel           = "開発者\r\n========";
    ls->dlgAboutThanks          = "ご協力いただいた方々\r\n============";
    ls->dlgAboutLisence         = "LICENSE\r\n"
                                  "======\r\n\r\n"
                                  "このソ\フトウェアは現状をそのままの状態で配布するものであり, 明示的または"
                                  "黙示的を問わず一切の保証はありません. またこのソ\フトウェアの使用の結果生じた"
                                  "いかなる損害についても, 作者は責任を負いません.\r\n\r\n"
                                  "詳しい説明については, www.bluemsx.com をご覧ください. ";

    ls->dlgSavePreview          = "プレビュー表\示";
    ls->dlgSaveDate             = "セーブ時刻:";


    //----------------------
    // Properties related lines
    //----------------------

    ls->propTitle               = "blueMSX - 設定";
    ls->propEmulation           = "エミュレーション";
    ls->propVideo               = "ビデオ";
    ls->propSound               = "サウンド";
    ls->propControls            = "コントロール";
    ls->propPerformance         = "パフォーマンス";
    ls->propSettings             = "その他";
    ls->propFile                = "ファイル"; 
    ls->propPorts               = "ポート";
    
    ls->propEmuGeneralGB        = "一般 ";
    ls->propEmuFamilyText       = "MSXの種類:";
    ls->propEmuMemoryGB         = "メモリ ";
    ls->propEmuRamSizeText      = "メインRAM:";
    ls->propEmuVramSizeText     = "VRAM:";
    ls->propEmuSpeedGB          = "スピード ";
    ls->propEmuSpeedText        = "スピード:";
    ls->propEmuFrontSwitchGB     = "パナソ\ニックスイッチ "; 
    ls->propEmuFrontSwitch       = " 前面スイッチ"; 
    ls->propEmuFdcTiming        = "FDDドライブのタイミングを無効化";
    ls->propEmuPauseSwitch      = " ポーズ スイッチ";
    ls->propEmuAudioSwitch       = " MSX-AUDIO カートリッジ スイッチ"; 
    ls->propVideoFreqText       = "ビデオ 周波数:";
    ls->propVideoFreqAuto       = "自動";
    ls->propSndOversampleText   = "サンプリング:";
    ls->propSndYkInGB           = "YK-01/YK-10/YK-20 In ";                // New in 2.5
    ls->propSndMidiInGB         = "MIDI イン "; 
    ls->propSndMidiOutGB        = "MIDI アウト "; 
    ls->propSndMidiChannel      = "MIDI Channel:";                      // New in 2.5
    ls->propSndMidiAll          = "All";                                // New in 2.5

    ls->propMonMonGB            = "モニター ";
    ls->propMonTypeText         = "モニターの種類:";
    ls->propMonEmuText          = "モニターエミュレーション:";
    ls->propVideoTypeText       = "映像方式:";
    ls->propWindowSizeText      = "ウィンドウサイズ:";
    ls->propMonHorizStretch      = " 水平 ストレッチ";  
    ls->propMonVertStretch       = " 垂直 ストレッチ";
    ls->propMonDeInterlace      = " デインターレース";
    ls->propBlendFrames         = " Blend consecutive frames";           // New in 2.5
    ls->propMonBrightness       = "明るさ:";
    ls->propMonContrast         = "コントラスト:";
    ls->propMonSaturation       = "彩度:";
    ls->propMonGamma            = "ガンマ:";
    ls->propMonScanlines        = "スキャンライン:";
    ls->propMonColorGhosting    = "RFモジュレータ";
    ls->propMonEffectsGB        = "エフェクト "; 

    ls->propPerfVideoDrvGB      = "ビデオドライバ ";
    ls->propPerfVideoDispDrvText= "ディスプレイドライバ:";
    ls->propPerfFrameSkipText   = "フレームスキップ:";
    ls->propPerfAudioDrvGB      = "サウンドドライバ ";
    ls->propPerfAudioDrvText    = "サウンドドライバ:";
    ls->propPerfAudioBufSzText  = "サウンドバッファ:";
    ls->propPerfEmuGB           = "エミュレーション ";
    ls->propPerfSyncModeText    = "SYNCモード:";
    ls->propFullscreenResText   = "フルスクリーンの解像度:";

    ls->propSndChipEmuGB        = "サウンドのエミュレーション ";
    ls->propSndMsxMusic         = " MSX-MUSIC";
    ls->propSndMsxAudio         = " MSX-AUDIO";
    ls->propSndMoonsound         = " Moonsound";
    ls->propSndMt32ToGm         = " MT-32 楽器をジェネラルMIDIにマッピング"; 

    ls->propPortsLptGB          = "パラレルポート ";
    ls->propPortsComGB          = "シリアルポート ";
    ls->propPortsLptText        = "ポート:";
    ls->propPortsCom1Text       = "ポート 1:";
    ls->propPortsNone           = "なし";
    ls->propPortsSimplCovox     = "SiMPL / Covox DAC";
    ls->propPortsFile           = "ファイルへプリント"; 
    ls->propPortsComFile        = "ファイルへ送る"; 
    ls->propPortsOpenLogFile    = "ログファイルを開く"; 
    ls->propPortsEmulateMsxPrn  = "エミュレーション:"; 

    ls->propSetFileHistoryGB     = "ファイルヒストリ ";
    ls->propSetFileHistorySize   = "ファイルヒストリの個数:";
    ls->propSetFileHistoryClear  = "ヒストリの消去";
    ls->propFileTypes            = " blueMSXに関連付けるファイル種類 (.rom, .dsk, .cas, .sta)";
    ls->propWindowsEnvGB         = "ウィンドウズ環境 ";
    ls->propSetScreenSaver       = " blueMSXの動作中はスクリーンセーバを無効にする";
    ls->propDisableWinKeys       = " blueMSXを使用中に左右のWindowsキーを無効化する"; 
    ls->propPriorityBoost        = " blueMSXに割当てるプライオリティーのブースト";
    ls->propScreenshotPng       = " Use Portable Network Graphics (.png) screenshots";  // New in 2.5
    ls->propClearHistory         = "ヒストリの消去を実行して、よろしいですか?"; 
    ls->propOpenRomGB           = "ロムダイアログを開く"; 
    ls->propDefaultRomType      = "標準ロムタイプ:"; 
    ls->propGuessRomType        = "ロム種類を推測";

    ls->propSettDefSlotGB       = "ドラッグ＆ドロップ "; 
    ls->propSettDefSlots        = "ロムを挿入するスロット:"; 
    ls->propSettDefSlot         = " スロット"; 
    ls->propSettDefDrives       = "ディスクを挿入するドライブ:"; 
    ls->propSettDefDrive        = " ドライブ"; 

    ls->propThemeGB             = "テーマ ";
    ls->propTheme               = "テーマ";


    //----------------------
    // Dropdown related lines
    //----------------------

    ls->enumVideoMonColor       = "カラー";
    ls->enumVideoMonGrey        = "モノクロ";
    ls->enumVideoMonGreen       = "グリーン";
    ls->enumVideoMonAmber       = "アンバー";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "なし";
    ls->enumVideoEmuYc          = "Y/Cケーブル (鮮明)";
    ls->enumVideoEmuMonitor     = "モニター";
    ls->enumVideoEmuYcBlur      = "Y/Cケーブル＋ノイズ (鮮明)";
    ls->enumVideoEmuComp        = "コンポジット (不鮮明)";
    ls->enumVideoEmuCompBlur    = "コンポジット＋ノイズ (不鮮明)";
    ls->enumVideoEmuScale2x     = "Scale 2x";
    ls->enumVideoEmuHq2x        = "Hq2x";

    ls->enumVideoSize1x         = "標準サイズ - 320x200";
    ls->enumVideoSize2x         = "2倍サイズ - 640x400";
    ls->enumVideoSizeFullscreen = "フルスクリーン";

    ls->enumVideoDrvDirectDrawHW= "DirectDraw HW accel."; 
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
    
    ls->enumEmuSync1ms          = "MSXの速度に同期"; 
    ls->enumEmuSyncAuto         = "オート (高速)"; 
    ls->enumEmuSyncNone         = "無し"; 
    ls->enumEmuSyncVblank       = "PCの書換えに同期"; 
    ls->enumEmuAsyncVblank      = "Asynchronous PC Vblank";             // New in 2.5

    ls->enumControlsJoyNone     = "なし";
    ls->enumControlsJoyMouse    = "マウス";
    ls->enumControlsJoyTetris2Dongle = "テトリス 2 ドングル"; 
    ls->enumControlsJoyTMagicKeyDongle = "MagicKey Dongle";             // New in 2.5
    ls->enumControlsJoy2Button = "2-button Joystick";                   // New in 2.5
    ls->enumControlsJoyGunstick  = "Gun Stick";                         // New in 2.5
    ls->enumControlsJoyAsciiLaser="ASCII Plus-X Terminator Laser";      // New in 2.5
    ls->enumControlsJoyColeco = "ColecoVision Joystick";                // New in 2.5

    ls->enumDiskMsx35Dbl9Sect    = "MSX 3.5 Double Sided, 9 Sectors";     // New in 2.5
    ls->enumDiskMsx35Dbl8Sect    = "MSX 3.5 Double Sided, 8 Sectors";     // New in 2.5
    ls->enumDiskMsx35Sgl9Sect    = "MSX 3.5 Single Sided, 9 Sectors";     // New in 2.5
    ls->enumDiskMsx35Sgl8Sect    = "MSX 3.5 Single Sided, 8 Sectors";     // New in 2.5
    ls->enumDiskSvi525Dbl        = "SVI-328 5.25 Double Sided";           // New in 2.5
    ls->enumDiskSvi525Sgl        = "SVI-328 5.25 Single Sided";           // New in 2.5


    //----------------------
    // Configuration related lines
    //----------------------

    ls->confTitle                = "blueMSX - マシン構\成編集";
    ls->confConfigText           = "マシン構\成";
    ls->confSlotLayout           = "スロット構\成";
    ls->confMemory               = "メモリ";
    ls->confChipEmulation        = "チップ";
    ls->confChipExtras          = "エキストラ";

    ls->confOpenRom             = "ロム イメージを開く"; 
    ls->confSaveTitle            = "blueMSX - マシン構\成編集の終了";
    ls->confSaveText             = "現在の構\成が失われますが、よろしいですか?";    
    ls->confSaveAsTitle         = "別名で保存...";
    ls->confSaveAsMachineName    = "構\成名:";
    ls->confDiscardTitle         = "blueMSX - マシン構\成編集";
    ls->confExitSaveTitle        = "blueMSX - マシン構\成編集の終了";
    ls->confExitSaveText         = "現在の構\成が失われますが、よろしいですか?";

    ls->confSlotLayoutGB         = "スロット構\成 ";
    ls->confSlotExtSlotGB        = "拡張スロット ";
    ls->confBoardGB             = "基盤 ";
    ls->confBoardText           = "基盤 タイプ:";
    ls->confSlotPrimary          = "基本";
    ls->confSlotExpanded         = "拡張 (4つの副スロット)";

    ls->confSlotCart             = "カートリッジ";
    ls->confSlot                = "スロット"; 
    ls->confSubslot             = "サブスロット"; 

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

    ls->confCmosGB                = "CMOS "; 
    ls->confCmosEnable            = " CMOSを有効"; 
    ls->confCmosBattery           = " 内蔵バッテリーを有効化";

    ls->confCpuFreqGB            = "CPU 周波数 ";
    ls->confZ80FreqText          = "Z80 周波数:";
    ls->confR800FreqText         = "R800 周波数:";
    ls->confFdcGB                = "フロッピーディスクコントローラー ";
    ls->confCFdcNumDrivesText    = "ドライブの数:";

    ls->confEditMemTitle         = "blueMSX - マッパの編集";
    ls->confEditMemGB            = "マッパの詳細 ";
    ls->confEditMemType          = "タイプ:";
    ls->confEditMemFile          = "ファイル:";
    ls->confEditMemAddress       = "アドレス:";
    ls->confEditMemSize          = "サイズ:";
    ls->confEditMemSlot          = "スロット:";


    //----------------------
    // Shortcut lines
    //----------------------

    ls->shortcutKey             = "ホットキー"; 
    ls->shortcutDescription     = "ショートカット"; 

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
    ls->shortcutSpecialMenu1    = "カートリッジ1のその他メニューの表\示";
    ls->shortcutSpecialMenu2    = "カートリッジ2のその他メニューの表\示";
    ls->shortcutCartAutoReset   = "カートリッジ 挿入/取り出し後リセット";
    ls->shortcutDiskInsertA     = "ディスクA 挿入";
    ls->shortcutDiskDirInsertA  = "ディレクトリをディスクAとして挿入"; 
    ls->shortcutDiskRemoveA     = "ディスクA 取り出し";
    ls->shortcutDiskChangeA     = "ディスクA 入れ替え(v-DRIVE)";
    ls->shortcutDiskAutoResetA  = "ディスクA 挿入/取り出し後リセット";
    ls->shortcutDiskInsertB     = "ディスクB 挿入";
    ls->shortcutDiskDirInsertB  = "ディレクトリをディスクBとして挿入";
    ls->shortcutDiskRemoveB     = "ディスクB 取り出し";
    ls->shortcutCasInsert       = "テープ 挿入";
    ls->shortcutCasEject        = "テープ 取り出し";
    ls->shortcutCasAutorewind   = "テープ 挿入後巻き戻す";
    ls->shortcutCasReadOnly     = "テープを読み込み専用にする";
    ls->shortcutCasSetPosition  = "テープ位置セット";
    ls->shortcutCasRewind       = "テープ巻き戻し";
    ls->shortcutCasSave         = "テープイメージ 保存";
    ls->shortcutPrnFormFeed     = "フォームフィード"; 
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
    ls->shortcutSizeMinimized   = "ウィンドウ 最小化";
    ls->shortcutToggleFullscren = "フルスクリーン化";
    ls->shortcutVolumeIncrease  = "ボリュームを上げる";
    ls->shortcutVolumeDecrease  = "ボリュームを下げる";
    ls->shortcutVolumeMute      = "ミュート";
    ls->shortcutVolumeStereo    = "モノ/ステレオの切り替え";
    ls->shortcutSwitchMsxAudio  = "MSX-AUDIOカートリッジスイッチ";
    ls->shortcutSwitchFront     = "前面スイッチ";
    ls->shortcutSwitchPause     = "パナソ\ニック系 ポーズスイッチ";
    ls->shortcutToggleMouseLock = "マウスロック";
    ls->shortcutEmuSpeedMax     = "エミュレーション実行速度を最速化";
    ls->shortcutEmuSpeedToggle  = "最速動作の有無";
    ls->shortcutEmuSpeedNormal  = "エミュレーション実行速度を標準化";
    ls->shortcutEmuSpeedInc     = "エミュレーション速度を加速";
    ls->shortcutEmuSpeedDec     = "エミュレーション速度の減速";
    ls->shortcutThemeSwitch     = "テーマの切り替え";
    ls->shortcutShowEmuProp     = "エミュレーション設定画面の表\示";
    ls->shortcutShowVideoProp   = "ビデオ設定画面の表\示";
    ls->shortcutShowAudioProp   = "サウンド設定画面の表\示";
    ls->shortcutShowCtrlProp    = "コントロール設定画面の表\示";
    ls->shortcutShowPerfProp    = "パフォーマンス設定画面の表\示";
    ls->shortcutShowSettProp    = "その他設定画面の表\示";
    ls->shortcutShowPorts       = "ポート構\成設定の表\示";
    ls->shortcutShowLanguage    = "言語ダイアログの表\示";
    ls->shortcutShowMachines    = "マシン構\成編集の表\示";
    ls->shortcutShowShortcuts   = "ショートカットエディターの表\示";
    ls->shortcutShowKeyboard    = "キーボード構\成編集の表\示";
    ls->shortcutShowMixer       = "ミキサーの表\示"; 
	ls->shortcutShowDebugger    = "デバッガー表\示";
    ls->shortcutShowTrainer     = "トレーナー表\示";
    ls->shortcutShowHelp        = "ヘルプダイアログの表\示";
    ls->shortcutShowAbout       = "blueMSXについての表\示";
    ls->shortcutShowFiles       = "ファイルダイアログを表\示";
    ls->shortcutToggleSpriteEnable = "スプライトの表\示/無効";
    ls->shortcutToggleFdcTiming = "FDDドライブのタイミング 有無";
    ls->shortcutToggleCpuTrace  = "CPUトレースの有無";


    //----------------------
    // Keyboard config lines
    //----------------------
    
    ls->keyconfigSelectedKey    = "選択キー:";
    ls->keyconfigMappedTo       = "対象キー:";
    ls->keyconfigMappingScheme  = "マッピングスキーム:";

    
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
    ls->romTypeSfg05            = "Yamaha SFG-05";
    
    
    //----------------------
    // Debug type lines
    // Note: Only needs translation if debugger is translated
    //----------------------

    ls->dbgMemVisible           = "Visible Memory";
    ls->dbgMemRamNormal         = "Normal";
    ls->dbgMemRamMapped         = "Mapped";
    ls->dbgMemVram              = "VRAM";
    ls->dbgMemYmf278            = "YMF278 Sample RAM";
    ls->dbgMemAy8950            = "AY8950 Sample RAM";
    ls->dbgMemScc               = "Memory";

    ls->dbgCallstack            = "Callstack";

    ls->dbgRegs                 = "Registers";
    ls->dbgRegsCpu              = "CPU Registers";
    ls->dbgRegsYmf262           = "YMF262 Registers";
    ls->dbgRegsYmf278           = "YMF278 Registers";
    ls->dbgRegsAy8950           = "AY8950 Registers";
    ls->dbgRegsYm2413           = "YM2413 Registers";

    ls->dbgDevRamMapper         = "RAM Mapper";
    ls->dbgDevRam               = "RAM";
    ls->dbgDevIdeBeer           = "Beer IDE";
    ls->dbgDevIdeGide           = "GIDE";
    ls->dbgDevF4Device          = "F4 Device";
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
    ls->dbgDevMsxAudio          = "MSX Audio";
    ls->dbgDevMsxAudioMidi      = "MSX Audio MIDI";
    ls->dbgDevMsxMusic          = "MSX Music";
    ls->dbgDevPrinter           = "Printer";
    ls->dbgDevRs232             = "RS232";
    ls->dbgDevS1990             = "S1990";
    ls->dbgDevSfg05             = "Yamaha SFG-05";
    ls->dbgDevHbi55             = "Sony HBI-55";
    ls->dbgDevSviFdc            = "SVI FDC";
    ls->dbgDevSviPrn            = "SVI Printer";
    ls->dbgDevSvi80Col          = "SVI 80 Column";
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
    ls->dbgDevTrPause           = "TR Pause";
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
