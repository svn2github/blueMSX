/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Theme/Theme.h,v $
**
** $Revision: 1.3 $
**
** $Date: 2004-12-13 02:04:48 $
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
#ifndef THEME_H
#define THEME_H

#include "ThemeControls.h"

typedef struct Theme Theme;
typedef struct ThemeItem ThemeItem;

typedef struct {
    int x;
    int y;
} ClipPoint;

typedef struct {
    char   name[32];
    Theme* little;
    Theme* normal;
    Theme* smallfullscreen;
    Theme* fullscreen;
} ThemeCollection;

typedef enum {
    THEME_TRIGGER_NONE,
    THEME_TRIGGER_IMG_STOPPED,
    THEME_TRIGGER_IMG_PAUSED,
    THEME_TRIGGER_IMG_RUNNING,
    THEME_TRIGGER_IMG_TRACE,
    THEME_TRIGGER_IMG_DISKA,
    THEME_TRIGGER_IMG_DISKB,
    THEME_TRIGGER_IMG_CAS,
    THEME_TRIGGER_IMG_AS,
    THEME_TRIGGER_IMG_FS,
    THEME_TRIGGER_IMG_PS,
    THEME_TRIGGER_IMG_CAPS,
    THEME_TRIGGER_IMG_KANA,
	THEME_TRIGGER_IMG_TURBOR,
	THEME_TRIGGER_IMG_PAUSE,
    THEME_TRIGGER_IMG_FDCTIMING,
    THEME_TRIGGER_IMG_KBD,
    THEME_TRIGGER_IMG_MOON,
    THEME_TRIGGER_IMG_MSXA,
    THEME_TRIGGER_IMG_MSXM,
    THEME_TRIGGER_IMG_MASTER,
    THEME_TRIGGER_IMG_STEREO,
    THEME_TRIGGER_IMG_PSG,
    THEME_TRIGGER_IMG_SCC,
    THEME_TRIGGER_IMG_PCM,
    THEME_TRIGGER_IMG_L_KBD,
    THEME_TRIGGER_IMG_R_KBD,
    THEME_TRIGGER_IMG_L_MOON,
    THEME_TRIGGER_IMG_R_MOON,
    THEME_TRIGGER_IMG_L_MSXA,
    THEME_TRIGGER_IMG_R_MSXA,
    THEME_TRIGGER_IMG_L_MSXM,
    THEME_TRIGGER_IMG_R_MSXM,
    THEME_TRIGGER_IMG_L_PSG,
    THEME_TRIGGER_IMG_R_PSG,
    THEME_TRIGGER_IMG_L_SCC,
    THEME_TRIGGER_IMG_R_SCC,
    THEME_TRIGGER_IMG_L_PCM,
    THEME_TRIGGER_IMG_R_PCM,
    THEME_TRIGGER_IMG_L_MASTER,
    THEME_TRIGGER_IMG_R_MASTER,
    THEME_TRIGGER_IMG_PORT1_EN,
	THEME_TRIGGER_IMG_PORT1_NONE,
    THEME_TRIGGER_IMG_PORT1_MOUSE,
    THEME_TRIGGER_IMG_PORT1_NUM,
    THEME_TRIGGER_IMG_PORT1_KBD,
    THEME_TRIGGER_IMG_PORT1_JOY,
    THEME_TRIGGER_IMG_PORT2_EN,
    THEME_TRIGGER_IMG_PORT2_NONE,
    THEME_TRIGGER_IMG_PORT2_MOUSE,
    THEME_TRIGGER_IMG_PORT2_NUM,
    THEME_TRIGGER_IMG_PORT2_KBD,
    THEME_TRIGGER_IMG_PORT2_JOY,
    THEME_TRIGGER_IMG_M_MOON,
    THEME_TRIGGER_IMG_M_MSXM,
    THEME_TRIGGER_IMG_M_MSXA,
    THEME_TRIGGER_IMG_M_SCC,
    THEME_TRIGGER_IMG_M_ROM,
    THEME_TRIGGER_IMG_M_MEGARAM,
    THEME_TRIGGER_IMG_M_MEGAROM,
    THEME_TRIGGER_IMG_M_FMPAC,
    THEME_TRIGGER_IMG_REC,
    THEME_TRIGGER_IMG_DISK_RI,
    THEME_TRIGGER_IMG_CART_RI,
    THEME_TRIGGER_IMG_CAS_RO,
    THEME_TRIGGER_IMG_SCANLINES,
    THEME_TRIGGER_IMG_HSTRETCH,
    THEME_TRIGGER_IMG_VSTRETCH,
    THEME_TRIGGER_TEXT_SCANLINESPCT,
    THEME_TRIGGER_TEXT_FREQ,
    THEME_TRIGGER_TEXT_CPU,
    THEME_TRIGGER_TEXT_FPS,
    THEME_TRIGGER_TEXT_RAM,
    THEME_TRIGGER_TEXT_VRAM,
    THEME_TRIGGER_TEXT_SCREEN,
    THEME_TRIGGER_TEXT_SCREENSHORT,
    THEME_TRIGGER_TEXT_ROMMAPPER1,
    THEME_TRIGGER_TEXT_ROMMAPPER2,
    THEME_TRIGGER_TEXT_ROMMAPPER1SHORT,
    THEME_TRIGGER_TEXT_ROMMAPPER2SHORT,
    THEME_TRIGGER_TEXT_MACHINENAME,
    THEME_TRIGGER_TEXT_RUNNAME,
    THEME_TRIGGER_TEXT_VERSION,
    THEME_TRIGGER_TEXT_BUILDNUMBER,
    THEME_TRIGGER_TEXT_BUILDANDVER,

    THEME_TRIGGER_LEVEL_MASTER,
    THEME_TRIGGER_LEVEL_PSG,
    THEME_TRIGGER_LEVEL_PCM,
    THEME_TRIGGER_LEVEL_SCC,
    THEME_TRIGGER_LEVEL_KEYBOARD,
    THEME_TRIGGER_LEVEL_MSXMUSIC,
    THEME_TRIGGER_LEVEL_MSXAUDIO,
    THEME_TRIGGER_LEVEL_MOONSOUND,
    THEME_TRIGGER_PAN_PSG,
    THEME_TRIGGER_PAN_PCM,
    THEME_TRIGGER_PAN_SCC,
    THEME_TRIGGER_PAN_KEYBOARD,
    THEME_TRIGGER_PAN_MSXMUSIC,
    THEME_TRIGGER_PAN_MSXAUDIO,
    THEME_TRIGGER_PAN_MOONSOUND,
    
    THEME_TRIGGER_RENSHA,
    THEME_TRIGGER_RENSHALED,

    THEME_TRIGGER_EMUSPEED,

    THEME_TRIGGER_MASK = 0x3fffffff,
    
    THEME_TRIGGER_NOT  = 0x80000000,

    THEME_TRIGGER_IMG_NOT_STOPPED = THEME_TRIGGER_NOT | THEME_TRIGGER_IMG_STOPPED,
    THEME_TRIGGER_IMG_NOT_PAUSED  = THEME_TRIGGER_NOT | THEME_TRIGGER_IMG_PAUSED,
    THEME_TRIGGER_IMG_NOT_RUNNING = THEME_TRIGGER_NOT | THEME_TRIGGER_IMG_RUNNING
} ThemeTrigger;


struct Theme {
// public:
    int width;
    int height;
    int emuWinX;
    int emuWinY;
    int emuWinW;
    int emuWinH;
    struct {
        unsigned long color;
        unsigned long focusColor;
        unsigned long textColor;
        int x;
        int y;
        int width;
    } menu;

    struct {
        int count;
        ClipPoint* list;
    } clipPoint;

// private:
    ThemeItem*        itemList;
    ThemeItem*        activeItem;
    ActiveButton*     btDown;
    ActiveDualButton* btDualDown;
    int               btPressed;
};

typedef struct {
    int emuStopped;
    int emuPaused;
    int emuRunning;
    int fdcTiming;
    int cpuTraceEnable;
    int ledDiskA;
    int ledDiskB;
    int ledCas;
    int ledAudioSwitch;
    int ledFrontSwitch;
    int ledPauseSwitch;
    int ledCaps;
    int ledKana;
	int ledTurboR;
	int ledPause;
    int ledRecord;

    int audioStereo;
    int audioMaster;
    int audioKbd;
    int audioMoonsound;
    int audioMsxAudio;
    int audioMsxMusic;
    int audioPsg;
    int audioScc;
    int audioPcm;

    int volKbdLeft;
    int volKbdRight;
    int volMoonsoundLeft;
    int volMoonsoundRight;
    int volMsxAudioLeft;
    int volMsxAudioRight;
    int volMsxMusicLeft;
    int volMsxMusicRight;
    int volPsgLeft;
    int volPsgRight;
    int volSccLeft;
    int volSccRight;
    int volPcmLeft;
    int volPcmRight;
    int volMasterLeft;
    int volMasterRight;

    int levelMaster;
    int levelPsg;
    int levelPcm;
    int levelScc;
    int levelKeyboard;
    int levelMsxMusic;
    int levelMsxAudio;
    int levelMoonsound;
    int panPsg;
    int panPcm;
    int panScc;
    int panKeyboard;
    int panMsxMusic;
    int panMsxAudio;
    int panMoonsound;

    int renshaLevel;
    int renshaLed;

    int emuSpeed;

    int port1None;
    int port1Mouse;
    int port1Num;
    int port1Kbd;
    int port1Joy;
    int port2None;
    int port2Mouse;
    int port2Num;
    int port2Kbd;
    int port2Joy;

    int machineMoonsound;
    int machineMsxAudio;
    int machineMsxMusic;
    int machineScc;
    int machineRom;
    int machineMegaRom;
    int machineMegaRam;
    int machineFmPac;

    int confDiskRI;
    int confCartRI;
    int confCasRO;

    int videoScanlines;
    int videoHstretch;
    int videoVstretch;
    char videoScanlinePct[16];

    char screenMode[16];
    char screenModeShort[16];
    char memoryRam[16];
    char memoryVram[16];
    char emuFrequency[16];
    char fpsString[16];
    char cpuString[16];
    char romMapper1[16];
    char romMapper2[16];
    char romMapper1Short[16];
    char romMapper2Short[16];
    char machineName[128];
    char runningName[128];
    char buildNumber[16];
    char version[16];
    char buildAndVersion[32];
} StatusInfo;


Theme* themeCreate(int width,
                   int height,
                   int emuPosX,
                   int emuPosY,
                   int emuWidth,
                   int emuHeight,
                   int menuPosX,
                   int menuPosY,
                   int menuWidth,
                   unsigned long menuColor,
                   unsigned long menuFocusColor,
                   unsigned long menuTextColor,
                   int        clipPointCount,
                   ClipPoint* clipPointList);

void themeDestroy(Theme* theme);

void themeAddImage(Theme* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible);

void themeAddText(Theme* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible);

void themeAddButton(Theme* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible);

void themeAddDualButton(Theme* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible);

void themeAddMeter(Theme* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible);

void themeAddSlider(Theme* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible);

void themeUpdate(Theme* theme, void* dc, StatusInfo* statusInfo);
void themeDraw(Theme* theme, void* dc);
void themeMouseMove(Theme* theme, void* dc, int x, int y);
void themeMouseButtonUp(Theme* theme, void* dc, int x, int y);
void themeMouseButtonDown(Theme* theme, void* dc, int x, int y);

#endif //WIN32_THEME_CLASSIC_H
