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
    ls->statusBarStopped        = "  중지";
    ls->statusBarPaused         = "  일시 정지";
    ls->statusBarRunning        = "  실행중";
    
    ls->menuHardReset           = "하드 리셋";
    ls->menuSoftReset           = "소프트 리셋";
    
    ls->menuCartInsert          = "삽입";
    ls->menuCartRemove          = "제거";
    ls->menuCartAutoReset       = "삽입/제거 후에 재시작";
    ls->menuCartNoRecentFiles   = "- 열어본 파일 없음 -";
    ls->menuCartFMPac           = "FM-PAC 카트리지";
    ls->menuCartPac             = "PAC 카트리지";
    ls->menuCartSpecial         = "사용자 지정 카트리지";

    ls->menuDiskInsert          = "삽입";
    ls->menuDiskEject           = "꺼내기";
    ls->menuDiskAutoStart       = "삽입후에 재시작";
    ls->menuDiskNoRecentFiles   = "- 열어본 파일 없음 -";
    
    ls->menuCasInsert           = "삽입";
    ls->menuCasEject            = "꺼내기";
    ls->menuCasSetPosition      = "위치 설정";
    ls->menuCasRewind           = "되감기";
    ls->menuCasNoRecentFiles    = "- 열어본 파일 없음 -";

    ls->menuZoomNormal          = "보통 크기";
    ls->menuZoomDouble          = "두배 크기";
    ls->menuZoomFullscreen      = "전체 화면";
    
    ls->menuPropsEmulation      = "에뮬레이션";
    ls->menuPropsVideo          = "비디오";
    ls->menuPropsSound          = "사운드";
    ls->menuPropsControls       = "콘트롤";
    ls->menuPropsPerformance    = "성능";
    ls->menuPropsLanguage       = "언어";
    
    ls->menuHelpHelp            = "도움말 항목";
    ls->menuHelpAbout           = "blueMSX에 대하여";

    ls->menuFileCart1           = "카트리지 슬롯 1";
    ls->menuFileCart2           = "카트리지 슬롯 2";
    ls->menuFileDiskA           = "디스크 드라이브 A";
    ls->menuFileDiskB           = "디스크 드라이브 B";
    ls->menuFileCas             = "카세트";
    ls->menuFileLoadState       = "CPU 상태 불러오기";
    ls->menuFileSaveState       = "CPU 상태 저장";
    ls->menuFileQLoadState      = "상태 바로 불러오기";
    ls->menuFileQSaveState      = "상태 바로 저장";
    ls->menuFileCaptureAudio    = "소리 저장";
    ls->menuFileScreenShot      = "화면 저장";
    ls->menuFileExit            = "끝내기";

    ls->menuRunRun              = "실행";
    ls->menuRunPause            = "일시 정지";
    ls->menuRunStop             = "중지";
    ls->menuRunSoftReset        = "소프트 리셋";
    ls->menuRunHardReset        = "하드 리셋";
    ls->menuRunCleanReset       = "전체 리셋";

    ls->menuFile                = "파일";
    ls->menuRun                 = "실행";
    ls->menuWindow              = "윈도우";
    ls->menuOptions             = "옵션";
    ls->menuHelp                = "도움말";
    
    ls->errorTitle              = "blueMSX - 에러";
    ls->errorEnterFullscreen    = "전체 화면모드 진입 실패.           \n";
    ls->errorDirectXFailed      = "DirectX 오브젝트 만들기 실패.           \nGDI로 대체해서 사용합니다.\n그래픽카드 등록정보을 확인하세요.";
    ls->errorNoRomInZip         = "zip파일 안에 .rom을 찾을 수 없습니다.";
    ls->errorNoDskInZip         = "zip파일 안에 .dsk를 찾을 수 없습니다.";
    ls->errorNoCasInZip         = "zip파일 안에 .cas를 찾을 수 없습니다.";
    ls->errorNoHelp             = "blueMSX 도움말을 찾을 수 없습니다.";
    ls->errorStartEmu           = "MSX 에뮬레이터를 시작할 수 없습니다.";

    ls->tooltipReset            = "MSX 리셋";
    ls->tooltipCart1            = "슬롯 1에 카트리지 삽입";
    ls->tooltipCart2            = "슬롯 2에 카트리지 삽입";
    ls->tooltipDiskA            = "드라이브 A에 디스크 삽입";
    ls->tooltipDiskB            = "드라이브 B에 디스크 삽입";
    ls->tooltipCas              = "카세트 플레이어에 테잎 삽입";
    ls->tooltipStart            = "에뮬레이션 시작";
    ls->tooltipResume           = "에뮬레이션 다시 시작";
    ls->tooltipPause            = "에뮬레이션 일시 정지";
    ls->tooltipWindowSize       = "윈도우 크기 설정";
    ls->tooltipProperties       = "옵션 보기";
    ls->tooltipHelp             = "도움말 보기";

    ls->dlgMainWindow           = "  blueMSX";
    ls->dlgLoadRom              = "blueMSX - 카트리지에 삽입할 rom 이미지 선택";
    ls->dlgLoadDsk              = "blueMSX - 드라이브에 삽입할 dsk 이미지 선택";
    ls->dlgLoadCas              = "blueMSX - 카세트 플레이어에 넣을 cas 이미지 선택";
    ls->dlgLoadRomDskCas        = "blueMSX - 읽어 들일 rom, dsk, cas 이미지 선택";
    ls->dlgLoadRomDesc          = "카트리지에 삽입할 롬 이미지를 선택해 주세요:";
    ls->dlgLoadDskDesc          = "드라이브에 삽입할 첫번째 장 디스크 또는 디스크 이미지를 선택해 주세요(교환은 ALT+F9. 파일명과 숫자가 일정해야 됩니다):";
    ls->dlgLoadCasDesc          = "카세트 플레이어에 넣을 테잎 이미지를 선택해 주세요:";
    ls->dlgLoadRomDskCasDesc    = "읽어 들일 롬,디스크,또는 테잎 이미지를 선택해 주세요:";
    ls->dlgLoadState            = "CPU 상태 불러오기";
    ls->dlgSaveState            = "CPU 상태 저장";
    ls->dlgInsertRom1           = "슬롯 1에 ROM 카트리지 삽입";
    ls->dlgInsertRom2           = "슬롯 2에 ROM 카트리지 삽입";
    ls->dlgInsertDiskA          = "드라이브 A에 디스크 삽입";
    ls->dlgInsertDiskB          = "드라이브 B에 디스크 삽입";
    ls->dlgInsertCas            = "카세트 테잎 삽입";

    ls->dlgOK                   = "확인";
    ls->dlgOpen                 = "열기";
    ls->dlgCancel               = "취소";

    ls->dlgTapeTitle            = "blueMSX - 테잎 위치";
    ls->dlgTapeFrameText        = "테잎 위치";
    ls->dlgTapeCurrentPos       = "현재 위치";
    ls->dlgTapeTotalTime        = "총 시간";

    ls->dlgZipReset             = "삽입후 재시작";

    ls->dlgAboutTitle           = "blueMSX에 대하여";

    ls->dlgJoyTitle1            = "blueMSX - 죠이스틱A 키설정";
    ls->dlgJoyTitle2            = "blueMSX - 죠이스틱B 키설정";
    ls->dlgJoyUpText            = "위";
    ls->dlgJoyDownText          = "아래";
    ls->dlgJoyLeftText          = "왼쪽";
    ls->dlgJoyRightText         = "오른쪽";
    ls->dlgJoyButton1Text       = "버튼 1";
    ls->dlgJoyButton2Text       = "버튼 2";
    ls->dlgJoyGB                = "키설정 ";

    ls->dlgLangLangText         = "blueMSX에 사용할 언어 선택";
    ls->dlgLangLangTitle        = "blueMSX - 언어";

    ls->propTitle               = "blueMSX - 속성";
    ls->propEmulation           = "에뮬레이션";
    ls->propVideo               = "비디오";
    ls->propSound               = "사운드";
    ls->propControls            = "콘트롤";
    ls->propPerformance         = "성능";
    
    ls->propEmuGeneralGB        = "일반 ";
    ls->propEmuFamilyText       = "MSX 머신:";
    ls->propEmuMemoryGB         = "메모리 ";
    ls->propEmuRamSizeText      = "램 크기:";
    ls->propEmuVramSizeText     = "비디오램 크기:";
    ls->propEmuSpeedGB          = "에뮬레이션 속도 ";
    ls->propEmuSpeedText        = "에뮬레이션 속도:";

    ls->propMonMonGB            = "모니터 ";
    ls->propMonTypeText         = "모니터 유형:";
    ls->propMonEmuText          = "모니터 에뮬레이션:";
    ls->propVideoYypeText       = "비디오 유형:";
    ls->propWindowSizeText      = "윈도우 크기:";

    ls->propPerfVideoDrvGB      = "비디오 드라이버 ";
    ls->propPerfVideoDispDrvText= "화면 드라이버:";
    ls->propPerfFrameSkipText   = "프레임 건너띄기:";
    ls->propPerfAudioDrvGB      = "오디오 드라이버 ";
    ls->propPerfAudioDrvText    = "사운드 드라이버:";
    ls->propPerfAudioBufSzText  = "사운드 버퍼 사이즈:";
    ls->propPerfEmuGB           = "클럭 에뮬레이션 ";
    ls->propPerfSyncModeText    = "동기화 모드:";

    ls->propSndChipEmuGB        = "사운드 칩 에뮬레이션 ";
    ls->propSndMixerGB          = "오디오 믹서 ";
    ls->propSndMonoText         = "모노";
    ls->propSndStereoText       = "스테레오";
    ls->propSndMsxMusicText     = " MSX-MUSIC";
    ls->propSndMsxAudioText     = " MSX-AUDIO";
    ls->propSndMsxMasterText    = "마스터";

    ls->propJoyPort1GB          = "포트 #1 ";
    ls->propJoyPort2GB          = "포트 #2 ";
    ls->propJoyAutofireText     = "자동발사:";
    ls->propJoyKeysetGB         = "죠이스틱 키설정 ";
    ls->propJoyKeyest1          = "A 키설정";
    ls->propJoyKeyest2          = "B 키설정";

    ls->enumVideoMonColor       = "컬러";
    ls->enumVideoMonGrey        = "검정과 흰색";
    ls->enumVideoMonGreen       = "녹색";

    ls->enumVideoTypePAL        = "PAL";
    ls->enumVideoTypeNTSC       = "NTSC";

    ls->enumVideoEmuNone        = "없음";
    ls->enumVideoEmuYc          = "Y/C 케이블 (선명)";
    ls->enumVideoEmuYcBlur      = "잡음있는 Y/C 케이블 (선명)";
    ls->enumVideoEmuComp        = "컴포지트 (흐릿)";
    ls->enumVideoEmuCompBlur    = "잡음있는 컴포지트 (흐릿)";
    ls->enumVideoEmuScale2x     = "2x 스케일";

    ls->enumVideoSize1x         = "보통 - 320x200";
    ls->enumVideoSize2x         = "두배 - 640x400";
    ls->enumVideoSizeFullscreen = "전체 화면";

    ls->enumVideoDrvDirectDraw  = "DirectDraw";
    ls->enumVideoDrvGDI         = "GDI";

    ls->enumVideoFrameskip0     = "없음";
    ls->enumVideoFrameskip1     = "1 프레임";
    ls->enumVideoFrameskip2     = "2 프레임";
    ls->enumVideoFrameskip3     = "3 프레임";
    ls->enumVideoFrameskip4     = "4 프레임";
    ls->enumVideoFrameskip5     = "5 프레임";

    ls->enumSoundDrvNone        = "소리없음";
    ls->enumSoundDrvWMM         = "WMM 드라이버";
    ls->enumSoundDrvDirectX     = "DirectX 드라이버";

    ls->enumEmuSync1ms          = "1ms (오리지널)";
    ls->enumEmuSyncAuto         = "자동 (빠름)";

    ls->enumControlsJoyNone     = "없음";
    ls->enumControlsJoyNumpad   = "숫자키";
    ls->enumControlsJoyKeysetA  = "키 A";
    ls->enumControlsJoyKeysetB  = "키 B";
    ls->enumControlsJoyPCjoy1   = "PC 죠이스틱 #1";
    ls->enumControlsJoyPCjoy2   = "PC 죠이스틱 #2";
    ls->enumControlsJoyMouse    = "마우스";

    ls->enumControlsAfOff       = "끔";
    ls->enumControlsAfSlow      = "느리게";
    ls->enumControlsAfMedium    = "중간";
    ls->enumControlsAfFast      = "빠르게";

    ls->dlgAboutAbout           = "대하여\r\n=====";
    ls->dlgAboutVersion         = "버전:";
    ls->dlgAboutBuildNumber     = "빌드:";
    ls->dlgAboutBuildDate       = "날짜:";
    ls->dlgAboutCreat           = "제작자: Daniel Vik";
    ls->dlgAboutDevel           = "개발자 분들\r\n========";
    ls->dlgAboutThanks          = "도움을 주신 분들\r\n===========";
    ls->dlgAboutLisence         = "라이센스\r\n"
                                  "======\r\n\r\n"
				  "이 소프트웨어는 원본 그대로 배포되어야 하며, 명시적이건 내포적이건 "
				  "어떤 종류의 보증도 하지 않습니다.\r\n이 소프트웨어의 사용으로 일어나는 "
				  "어떠한 문제에도 제작자에게는 책임이 없습니다.\r\n\r\n"
                                  "더 자세한 것은 www.bluemsx.com을 방문해 주세요.";

    // New entries
    ls->menuTools                = "도구";
    ls->menuToolsMachine         = "머신 편집기";
    ls->menuPropsSettings        = "외부 설정";
    ls->menuCasRewindAfterInsert = "삽입후에 되감기";
    ls->menuCasUseReadOnly       = "읽기전용";
    ls->lmenuCasSaveAs           = "다른 이름으로 저장...";

    ls->dlgSaveCassette          = "blueMSX - 테잎 이미지 저장";
    ls->dlgTapeCustom            = "사용자 지정 파일 보기";
    ls->dlgTapeSetPosText        = "테잎 위치:";
    ls->dlgTabPosition           = "위치";
    ls->dlgTabType               = "형식";
    ls->dlgTabFilename           = "파일 이름";

    ls->propSettings             = "외부 설정";
    
    ls->propSetFileHistoryGB     = "열어본 파일 목록 ";
    ls->propSetFileHistorySize   = "파일 보관 크기:";
    ls->propSetFileHistoryClear  = "목록 지우기";
    ls->propSetScreenSaverGB     = "화면 보호기 ";
    ls->propSetScreenSaver       = " blueMSX 실행중에는 화면 보호기 기능 중지";

    ls->confTitle                = "blueMSX - 머신 설정 편집기";
    ls->confSave                 = "저장";
    ls->confSaveAs               = "다른 이름으로...";
    ls->confRun                  = "실행";
    ls->confClose                = "닫기";
    ls->confConfigText           = "머신 설정";
    ls->confSlotLayout           = "슬롯 배치";
    ls->confMemory               = "메모리";
    ls->confChipEmulation        = "칩 에뮬레이션";

    ls->confSlotLayoutGB         = "슬롯 배치 ";
    ls->confSlotExtSlotGB        = "외부 슬롯 ";
    ls->confSlotSlot0            = "슬롯 0";
    ls->confSlotSlot1            = "슬롯 1";
    ls->confSlotSlot2            = "슬롯 2";
    ls->confSlotSlot3            = "슬롯 3";
    ls->confSlotCart1            = "카트리지 1:";
    ls->confSlotCart2            = "카트리지 2:";
    ls->confSlotPrimary          = "기본";
    ls->confSlotExpanded         = "확장 (4개의 서브슬롯)";

    ls->confMemAdd               = "추가...";
    ls->confMemEdit              = "편집...";
    ls->confMemRemove            = "제거";
    ls->confMemSlot              = "슬롯";
    ls->confMemAddresss          = "주소";
    ls->confMemType              = "형식";
    ls->confMemRomImage          = "롬 이미지";
    
    ls->confSaveTitle            = "blueMSX - 설정 저장";
    ls->confSaveText             = "이미 파일이 있습니다. 기존 파일을 이 파일로 바꾸시겠습니까?";

    ls->confChipVideoGB          = "비디오 ";
    ls->confChipVideoChip        = "비디오 칩:";
    ls->confChipVideoRam         = "비디오 램:";
    ls->confChipSoundGB          = "사운드 ";

    ls->slotEditMemTitle         = "blueMSX - 맵퍼 편집";
    ls->slotEditMemGB            = "맵퍼 항목 ";
    ls->slotEditMemType          = "형식:";
    ls->slotEditMemFile          = "파일:";
    ls->slotEditMemAddress       = "주소";
    ls->slotEditMemSize          = "크기";
    ls->slotEditMemSlot          = "슬롯";
    ls->confDiscardTitle         = "blueMSX - 설정";
    ls->confExitSaveTitle        = "blueMSX - 머신 설정 편집기 나가기";
    ls->confExitSaveText         = "변경한 설정이 적용되기 위해선 저장을 하셔야 합니다만 현재 설정에는 아무런 영향도 주지않고 그냥 나가겠습니까?";

    ls->confSaveAsMachineTitle   = "blueMSX - 다른 이름으로 머신 설정 저장...";
    ls->confSaveAsMachineName    = "머신 이름:";

    ls->confEditMemInternalRoms  = "blueMSX - 내부 ROM";
    ls->propSndMoonsound         = " Moonsound";

    ls->propFileTypesGB          = "파일 형식 ";
    ls->propFileTypes            = " blueMSX에 파일형식(.rom .dsk .cas .sta) 연결";
    ls->propDisableWinKeys       = " blueMSX 실행중에는 왼/오른쪽 윈도우 키 사용 않함"; 
    ls->propWindowsEnvGB         = "윈도우즈 환경 "; 
    ls->enumVideoDrvDirectDrawHW = "DirectDraw HW accel."; 
    ls->enumVideoDrvDirectDrawHWSys = "DirectDraw mix."; 
    ls->propMonHorizStretch      = " 수평 스크래치";
    ls->propMonVertStretch       = " 수직 스크래치";
    ls->propClearHistory         = "열어본 파일 목록을 지울까요?";
    ls->propEmuFrontSwitchGB     = "파나소닉 스위치 ";
    ls->propEmuFrontSwitch       = " 프론트 스위치";
    ls->propEmuAudioSwitch       = " MSX-AUDIO 카트리지 스위치";


    ls->dlgCmosGB                = "CMOS ";
    ls->dlgCmosEnable            = " CMOS 사용";
    ls->dlgCmosBattery           = " 충전지 사용";

    ls->menuCartSnatcher        = "The Snatcher 카트리지";
    ls->menuCartSdSnatcher      = "SD-Snatcher 카트리지";
    ls->menuCartSCCMirrored     = "SCC Mirrored 카트리지";
    ls->menuCartSCCExpanded     = "SCC Expanded 카트리지";
    ls->warningTitle             = "blueMSX - 경고";
    ls->tooltipStop             = "에뮬레이션 ";


        // New entries in 1.5.1
    ls->enumControlsJoyKeyset   = "키보드";    
    ls->propJoyConfigKeyset     = "키설정";
    ls->propJoyControlText      = "콘트롤:";
    ls->propJoyButtonText       = "버튼";
    ls->propJoyButtonAText      = "버튼 A:";
    ls->propJoyButtonBText      = "버튼 B:";

    ls->menuToolsShortcuts      = "단축키 편집기";

    ls->shortcutSaveConfig      = "blueMSX - 설정 저장";
    ls->shortcutOverwriteConfig = "이미 파일이 있습니다. 기존 파일을 이 파일로 바꾸시겠습니까?";
    ls->shortcutExitConfig      = "blueMSX - 단축키 편집기 나가기";
    ls->shortcutDiscardConfig   = "변경한 설정이 적용되기 위해선 저장을 하셔야 합니다만 현재 설정에는 아무런 영향도 주지않고 그냥 나가겠습니까?";
    ls->shortcutSaveConfigAs    = "blueMSX - 다른이름으로 단축키 설정 저장...";
    ls->shortcutConfigName      = "설정 이름:";
    ls->shortcutNewProfile      = "< 새로운 프로필 >";
    ls->shortcutConfigTitle     = "blueMSX - 단축키 매핑 편집기";
    ls->shortcutAssign          = "적용";
    ls->shortcutPressText       = "단축키 새로 설정:";
    ls->shortcutScheme          = "단축키 스타일:";

    ls->shortcutCartInsert1     = "카트리지 1 삽입";
    ls->shortcutCartRemove1     = "카트리지 1 제거";
    ls->shortcutCartInsert2     = "카트리지 2 삽입";
    ls->shortcutCartRemove2     = "카트리지 2 제거";
    ls->shortcutCartAutoReset   = "카트리지 삽입후 에뮬레이터 재시작";
    ls->shortcutDiskInsertA     = "디스켓 A 삽입";
    ls->shortcutDiskRemoveA     = "디스켓 A 꺼내기";
    ls->shortcutDiskChangeA     = "디스켓 A 빠른 교환(zip압축 파일)";
    ls->shortcutDiskAutoResetA  = "디스켓 A 삽입후 에뮬레이터 재시작";
    ls->shortcutDiskInsertB     = "디스켓 B 삽입";
    ls->shortcutDiskRemoveB     = "디스켓 B 꺼내기";
    ls->shortcutCasInsert       = "카세트 삽입";
    ls->shortcutCasEject        = "카세트 꺼내기";
    ls->shortcutCasAutorewind   = "카세트 자동 되감기 기능 변환";
    ls->shortcutCasReadOnly     = "카세트 읽기전용 변환";
    ls->shortcutCasSetPosition  = "테잎 위치 설정";
    ls->shortcutCasRewind       = "카세트 되감기";
    ls->shortcutCasSave         = "카세트 이미지 저장";
    ls->shortcutCpuStateLoad    = "CPU 상태 불러오기";
    ls->shortcutCpuStateSave    = "CPU 상태 저장";
    ls->shortcutCpuStateQload   = "상태 바로 불러오기";
    ls->shortcutCpuStateQsave   = "상태 바로 저장";
    ls->shortcutAudioCapture    = "소리 저장 시작/중지";
    ls->shortcutScreenshotOrig  = "화면 저장";
    ls->shortcutScreenshotSmall = "작은 크기로 화면 저장(원본)";
    ls->shortcutScreenshotLarge = "큰 크기로 화면 저장(원본)";
    ls->shortcutQuit            = "blueMSX 끝내기";
    ls->shortcutRunPause        = "에뮬레이션 시작/일시 정지";
    ls->shortcutStop            = "에뮬레이션 중지";
    ls->shortcutResetHard       = "하드 리셋";
    ls->shortcutResetSoft       = "소프트 리셋";
    ls->shortcutResetClean      = "전체 리셋";
    ls->shortcutSizeSmall       = "작은 윈도우 크기로 설정";
    ls->shortcutSizeNormal      = "보통 윈도우 크기로 설정";
    ls->shortcutSizeFullscreen  = "전체 화면으로 설정";
    ls->shortcutToggleFullscren = "전체 화면 변환";
    ls->shortcutVolumeIncrease  = "볼륨 증가";
    ls->shortcutVolumeDecrease  = "볼륨 감소";
    ls->shortcutVolumeMute      = "음소거";
    ls->shortcutSwitchMsxAudio  = "MSX-AUDIO 스위치 변환";
    ls->shortcutSwitchFront     = "파나소닉 프론트 스위치 변환";
    ls->shortcutToggleMouseLock = "마우스 고정 변환";
    ls->shortcutEmuSpeedMax     = "최대 에뮬레이션 속도";
    ls->shortcutEmuSpeedNormal  = "보통 에뮬레이션 속도";
    ls->shortcutEmuSpeedInc     = "에뮬레이션 속도 증가";
    ls->shortcutEmuSpeedDec     = "에뮬레이션 속도 감소";
    ls->shortcutShowEmuProp     = "에뮬레이션 속성 보기";
    ls->shortcutShowVideoProp   = "비디오 속성 보기";
    ls->shortcutShowAudioProp   = "오디오 속성 보기";
    ls->shortcutShowCtrlProp    = "콘트롤 속성 보기";
    ls->shortcutShowPerfProp    = "성능 속성 보기";
    ls->shortcutShowSettProp    = "외부 설정 속성 보기";
    ls->shortcutShowLanguage    = "언어 보기";
    ls->shortcutShowMachines    = "머신 편집기 보기";
    ls->shortcutShowShortcuts   = "단축키 편집기 보기";
    ls->shortcutShowHelp        = "도움말 보기";
    ls->shortcutShowAbout       = "blueMSX에 대하여 보기";
    
    ls->shortcutSpecialMenu1    = "카트리지 1 - 사용자 지정 카트리지";
    ls->shortcutSpecialMenu2    = "카트리지 2 - 사용자 지정 카트리지";
    ls->shortcutVolumeStereo    = "모노/스테레오 변환";
    ls->shortcutThemeSwitch     = "테마 변환";
    ls->shortcutToggleSpriteEnable = "스프라이트 보이기/숨기기 변환";
    
    ls->shortcutShowApearProp   = "외부 속성 보기";
    ls->menuPropsApearance      = "외부";
    ls->propApearance           = "외부";
    ls->propThemeGB             = "테마 ";
    ls->propTheme               = "기본 테마:";
    ls->propThemeClassic        = "고전";
    ls->propThemeBlue           = "DIGIDIGI파랑";

    ls->propMonBrightness       = "밝기:";
    ls->propMonContrast         = "선명도:";
    ls->propMonSaturation       = "채도:";
    ls->propMonGamma            = "감마:";
    ls->propMonScanlines        = " 스캔라인:";

    ls->dlgRomType              = "롬 형식:";
    ls->propOpenRomGB           = "열때 항상 현재 설정 사용 ";
    ls->propDefaultRomType      = "기본 롬 형식:";
    ls->propGuessRomType        = "자동 판단";

    ls->propFile                = "파일";
    ls->propSettDefSlotGB       = "마우스로 끌어서 놓을때 ";
    ls->propSettDefSlots        = "현재 슬롯에 롬 삽입:";
    ls->propSettDefSlot1        = " 슬롯 1";
    ls->propSettDefSlot2        = " 슬롯 2";
    ls->propSettDefDrives       = "현재 드라이브에 디스켓 삽입:";
    ls->propSettDefDriveA       = " 드라이브 A";
    ls->propSettDefDriveB       = " 드라이브 B";
    ls->menuPropsFile           = "파일";
    ls->shortcutShowFiles       = "파일 속성 보기";

    // New entries in 1.6.1
    ls->menuDiskDirInsert       = "디렉토리 삽입";
    ls->shortcutDiskDirInsertA  = "디스켓 A로 디렉토리 삽입";
    ls->shortcutDiskDirInsertB  = "디스켓 B로 디렉토리 삽입";

    ls->propMonDeInterlace      = " 디인터레이스";

    // New entries in 2.0
    ls->shortcutSwitchPause     = "일시 정지 스위치";
    ls->shortcutSizeMinimized   = "윈도우 최소화";
    ls->shortcutEmuSpeedToggle  = "에뮬레이션 속도 최대화 변환";
    ls->shortcutToggleCpuTrace  = "CPU 트레이스 변환";

    ls->enumVideoEmuMonitor     = "모니터";

    ls->propEmuPauseSwitch      = " 일시 정지 스위치";
    ls->propVideoFreqText       = "비디오 주파수:";
    ls->propVideoFreqAuto       = "자동";
    ls->propSndOversampleText   = "오버샘플:";

    ls->confChipExtras          = "기타";
    ls->confBoardGB             = "시스템 ";
    ls->confBoardText           = "시스템 형식:";
    ls->dlgCpuFreqGB            = "CPU 주파수 ";
    ls->dlgZ80FreqText          = "Z80 주파수:";
    ls->dlgR800FreqText         = "R800 주파수:";
    ls->dlgFdcGB                = "플로피 디스크 컨트롤러 ";
    ls->dlgCFdcNumDrivesText    = "드라이브의 갯수:";

    ls->propPriorityBoost        = " blueMSX에 작업 우선권 주기";

    // New entries in 2.1
    ls->propEmuFdcTiming        = "플로피 드라이브 타이밍 사용 않함";
    ls->shortcutToggleFdcTiming = "플로피 드라이브 타이밍 사용/않함 변환";
    ls->propUseRegistry         = "레지스트리에 설정 저장";

    // New entries in 2.2
    ls->menuCartHBI55           = "Sony HBI-55 카트리지";
    ls->propSndPcm              = " Turbo-R PCM";
    ls->propSndAY8910           = " AY8910 PSG";
    ls->propSndSN76489          = " SN76489 PSG";
    ls->enumVideoEmuHq2x        = "Hq2x";
    ls->propMonColorGhosting    = "RF-모듈레이터";

    ls->keyconfigSelectedKey    = "선택된 키:";
    ls->keyconfigMappedTo       = "대응된 키:";
    ls->keyconfigMappingScheme  = "매핑 스타일:";

    ls->discardChanges          = "변경한 설정이 적용되기 위해선 저장을 하셔야 합니다만 현재 설정에는 아무런 영향도 주지않고 그냥 나가겠습니까?";
    ls->overwriteConfig         = "이미 파일이 있습니다. 기존 파일을 이 파일로 바꾸시겠습니까?";

    ls->confSaveAsTitle         = "다른 이름으로 설정 저장...";
    ls->confSaveAsName          = "이름:";

    ls->menuToolsKeyboard       = "키보드 편집기";
    ls->shortcutShowKeyboard    = "키보드 편집기 보기";

    ls->menuVideoSource         = "비디오 소스";
    ls->menuVideoSourceDefault  = "비디오 소스 연결 않됨";
    ls->menuVideoChipAutodetect = "비디오 칩 자동감지";
    ls->propFullscreenResText   = "전체 화면 해상도:";
    ls->dlgSavePreview          = "미리 보기";
    ls->dlgSaveDate             = "시간 저장됨:";

    ls->enumVideoMonAmber       = "호박색"; 

    ls->menuPropsPorts          = "포트"; 
    ls->propPortsLptGB          = "패러럴 포트 "; 
    ls->propPortsComGB          = "시리얼 포트 "; 
    ls->propPortsLptText        = "포트:"; 
    ls->propPortsCom1Text       = "포트 1:";

    ls->shortcutShowDebugger    = "디버거 보기"; 
    ls->shortcutShowTrainer     = "트레이너 보기"; 
    ls->shortcutShowPorts       = "포트 속성 보기";
};

#endif
