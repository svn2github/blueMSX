/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Theme/ThemeLoader.cpp,v $
**
** $Revision: 1.10 $
**
** $Date: 2005-01-11 03:02:49 $
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
#include "TinyXml.h"
#include "ThemeLoader.h"
extern "C" {
#include "StrcmpNoCase.h"
#include "ArchBitmap.h"
#include "ArchText.h"
#include "Keyboard.h"
}

#define MAX_CLIP_POINTS 512

struct ThemeDefaultInfo {
    char* mode;
    int width;
    int height;
} themeDefaultInfo[] = {
    { "small",           320, 240 },
    { "normal",          640, 480 },
    { "smallfullscreen", 320, 240 },
    { "fullscreen",      640, 480 }
};

enum ThemeInfo { THEME_SMALL = 0, THEME_NORMAL = 1, THEME_SMALLFULLSCREEN = 2, THEME_FULLSCREEN = 3 };

static ButtonEvent getAction(TiXmlElement* el, const char* actionTag, const char* arg1Tag, const char* arg2Tag, int* arg1, int* arg2)
{
    *arg1 = 1;
    *arg2 = 1;

    el->QueryIntAttribute(arg1Tag, arg1);
    el->QueryIntAttribute(arg2Tag, arg2);

    const char* action = el->Attribute(actionTag);
    if (action == NULL) {
        return NULL;
    }

    if (0 == strcmp(action, "switch-togglefdctiming"))  return (ButtonEvent)actionToggleFdcTiming;

    if (0 == strcmp(action, "switch-audioswitch"))      return (ButtonEvent)actionToggleMsxAudioSwitch;
    if (0 == strcmp(action, "switch-frontswitch"))      return (ButtonEvent)actionToggleFrontSwitch;
    if (0 == strcmp(action, "switch-pauseswitch"))      return (ButtonEvent)actionTogglePauseSwitch;
    
    if (0 == strcmp(action, "menu-specialcart1"))       return (ButtonEvent)actionMenuSpecialCart1;
    if (0 == strcmp(action, "menu-specialcart2"))       return (ButtonEvent)actionMenuSpecialCart2;
    if (0 == strcmp(action, "menu-reset"))              return (ButtonEvent)actionMenuReset;
    if (0 == strcmp(action, "menu-run"))                return (ButtonEvent)actionMenuRun;
    if (0 == strcmp(action, "menu-file"))               return (ButtonEvent)actionMenuFile;
    if (0 == strcmp(action, "menu-cart1"))              return (ButtonEvent)actionMenuCart1;
    if (0 == strcmp(action, "menu-cart2"))              return (ButtonEvent)actionMenuCart2;
    if (0 == strcmp(action, "menu-diska"))              return (ButtonEvent)actionMenuDiskA;
    if (0 == strcmp(action, "menu-diskb"))              return (ButtonEvent)actionMenuDiskB;
    if (0 == strcmp(action, "menu-cassette"))           return (ButtonEvent)actionMenuCassette;
    if (0 == strcmp(action, "menu-windowsize"))         return (ButtonEvent)actionMenuZoom;
    if (0 == strcmp(action, "menu-options"))            return (ButtonEvent)actionMenuOptions;
    if (0 == strcmp(action, "menu-help"))               return (ButtonEvent)actionMenuHelp;
    if (0 == strcmp(action, "menu-tools"))              return (ButtonEvent)actionMenuTools;
    
    if (0 == strcmp(action, "dlg-emulation"))           return (ButtonEvent)actionPropShowEmulation;
    if (0 == strcmp(action, "dlg-video"))               return (ButtonEvent)actionPropShowVideo;
    if (0 == strcmp(action, "dlg-audio"))               return (ButtonEvent)actionPropShowAudio;
    if (0 == strcmp(action, "dlg-controls"))            return (ButtonEvent)actionPropShowControls;
    if (0 == strcmp(action, "dlg-performance"))         return (ButtonEvent)actionPropShowPerformance;
    if (0 == strcmp(action, "dlg-settings"))            return (ButtonEvent)actionPropShowSettings;
    if (0 == strcmp(action, "dlg-apearance"))           return (ButtonEvent)actionPropShowApearance;
    if (0 == strcmp(action, "dlg-language"))            return (ButtonEvent)actionOptionsShowLanguage;
    if (0 == strcmp(action, "dlg-machineeditor"))       return (ButtonEvent)actionToolsShowMachineEditor;
    if (0 == strcmp(action, "dlg-shortcuteditor"))      return (ButtonEvent)actionToolsShowShorcutEditor;
    if (0 == strcmp(action, "dlg-help"))                return (ButtonEvent)actionHelpShowHelp;
    if (0 == strcmp(action, "dlg-about"))               return (ButtonEvent)actionHelpShowAbout;
    
    if (0 == strcmp(action, "state-load"))              return (ButtonEvent)actionLoadState;
    if (0 == strcmp(action, "state-save"))              return (ButtonEvent)actionSaveState;
    if (0 == strcmp(action, "state-quickload"))         return (ButtonEvent)actionQuickLoadState;
    if (0 == strcmp(action, "state-quicksave"))         return (ButtonEvent)actionQuickSaveState;

    if (0 == strcmp(action, "cart1-insert"))            return (ButtonEvent)actionCartInsert1;
    if (0 == strcmp(action, "cart1-remove"))            return (ButtonEvent)actionCartRemove1;
    if (0 == strcmp(action, "cart1-toggleautoreset"))   return (ButtonEvent)actionToggleCartAutoReset;
    if (0 == strcmp(action, "cart2-insert"))            return (ButtonEvent)actionCartInsert2;
    if (0 == strcmp(action, "cart2-remove"))            return (ButtonEvent)actionCartRemove2;
    
    if (0 == strcmp(action, "diska-insert"))            return (ButtonEvent)actionDiskInsertA;
    if (0 == strcmp(action, "diska-insertdir"))         return (ButtonEvent)actionDiskDirInsertA;
    if (0 == strcmp(action, "diska-remove"))            return (ButtonEvent)actionDiskRemoveA;
    if (0 == strcmp(action, "diska-quickchange"))       return (ButtonEvent)actionDiskQuickChange;
    if (0 == strcmp(action, "diska-toggleautoreset"))   return (ButtonEvent)actionToggleDiskAutoResetA;
    if (0 == strcmp(action, "diskb-insert"))            return (ButtonEvent)actionDiskInsertB;
    if (0 == strcmp(action, "diskb-insertdir"))         return (ButtonEvent)actionDiskDirInsertB;
    if (0 == strcmp(action, "diskb-remove"))            return (ButtonEvent)actionDiskRemoveB;
    
    if (0 == strcmp(action, "cas-insert"))              return (ButtonEvent)actionCasInsert;
    if (0 == strcmp(action, "cas-remove"))              return (ButtonEvent)actionCasRemove;
    if (0 == strcmp(action, "cas-rewind"))              return (ButtonEvent)actionCasRewind;
    if (0 == strcmp(action, "cas-setposition"))         return (ButtonEvent)actionCasSetPosition;
    if (0 == strcmp(action, "cas-togglereadonly"))      return (ButtonEvent)actionCasToggleReadonly;
    if (0 == strcmp(action, "cas-toggleautorewind"))    return (ButtonEvent)actionToggleCasAutoRewind;
    if (0 == strcmp(action, "cas-save"))                return (ButtonEvent)actionCasSave;
    
    if (0 == strcmp(action, "window-small"))            return (ButtonEvent)actionWindowSizeSmall;
    if (0 == strcmp(action, "window-normal"))           return (ButtonEvent)actionWindowSizeNormal;
    if (0 == strcmp(action, "window-minimized"))        return (ButtonEvent)actionWindowSizeMinimized;
    if (0 == strcmp(action, "window-fullscreen"))       return (ButtonEvent)actionWindowSizeFullscreen;
    if (0 == strcmp(action, "window-togglefullscreen")) return (ButtonEvent)actionFullscreenToggle;
    
    if (0 == strcmp(action, "screenshot-normal"))       return (ButtonEvent)actionScreenCapture;
    if (0 == strcmp(action, "screenshot-small"))        return (ButtonEvent)actionScreenCaptureUnfilteredSmall;
    if (0 == strcmp(action, "screenshot-large"))        return (ButtonEvent)actionScreenCaptureUnfilteredLarge;
    
    if (0 == strcmp(action, "emu-quit"))                return (ButtonEvent)actionQuit;
    if (0 == strcmp(action, "emu-resetsoft"))           return (ButtonEvent)actionEmuResetSoft;
    if (0 == strcmp(action, "emu-resethard"))           return (ButtonEvent)actionEmuResetHard;
    if (0 == strcmp(action, "emu-resetclean"))          return (ButtonEvent)actionEmuResetClean;
    if (0 == strcmp(action, "emu-togglepause"))         return (ButtonEvent)actionEmuTogglePause;
    if (0 == strcmp(action, "emu-stop"))                return (ButtonEvent)actionEmuStop;
    if (0 == strcmp(action, "emu-togglemousecapture"))  return (ButtonEvent)actionToggleMouseCapture;
    if (0 == strcmp(action, "emu-togglecputrace"))      return (ButtonEvent)actionCpuTraceToggle;
    
    if (0 == strcmp(action, "emu-setmaxspeed"))         return (ButtonEvent)actionMaxSpeedSet;
    if (0 == strcmp(action, "emu-releasemaxspeed"))     return (ButtonEvent)actionMaxSpeedRelease;
    if (0 == strcmp(action, "emu-togglemaxspeed"))      return (ButtonEvent)actionMaxSpeedToggle;
    if (0 == strcmp(action, "emu-normalspeed"))         return (ButtonEvent)actionEmuSpeedNormal;
    if (0 == strcmp(action, "emu-increasespeed"))       return (ButtonEvent)actionEmuSpeedDecrease;
    if (0 == strcmp(action, "emu-decreasespeed"))       return (ButtonEvent)actionEmuSpeedDecrease;
    
    if (0 == strcmp(action, "audio-togglerecord"))      return (ButtonEvent)actionToggleWaveCapture;
    if (0 == strcmp(action, "audio-increasevolume"))    return (ButtonEvent)actionVolumeIncrease;
    if (0 == strcmp(action, "audio-decreasevolume"))    return (ButtonEvent)actionVolumeDecrease;
    if (0 == strcmp(action, "audio-togglestereo"))      return (ButtonEvent)actionVolumeToggleStereo;
    if (0 == strcmp(action, "audio-togglemute"))        return (ButtonEvent)actionMuteToggleMaster;

    if (0 == strcmp(action, "audio-togglemutemaster"))    return (ButtonEvent)actionMuteToggleMaster;
    if (0 == strcmp(action, "audio-togglemutepsg"))       return (ButtonEvent)actionMuteTogglePsg;
    if (0 == strcmp(action, "audio-togglemutepcm"))       return (ButtonEvent)actionMuteTogglePcm;
    if (0 == strcmp(action, "audio-togglemutescc"))       return (ButtonEvent)actionMuteToggleScc;
    if (0 == strcmp(action, "audio-togglemutekeyboard"))  return (ButtonEvent)actionMuteToggleKeyboard;
    if (0 == strcmp(action, "audio-togglemutemsxmusic"))  return (ButtonEvent)actionMuteToggleMsxMusic;
    if (0 == strcmp(action, "audio-togglemutemsxaudio"))  return (ButtonEvent)actionMuteToggleMsxAudio;
    if (0 == strcmp(action, "audio-togglemutemoonsound")) return (ButtonEvent)actionMuteToggleMoonsound;

    if (0 == strcmp(action, "port1-setnone"))           return (ButtonEvent)actionPort1SetNone;
    if (0 == strcmp(action, "port1-setmouse"))          return (ButtonEvent)actionPort1SetMouse;
    if (0 == strcmp(action, "port1-setnumpad"))         return (ButtonEvent)actionPort1SetNumpad;
    if (0 == strcmp(action, "port1-setkeyset"))         return (ButtonEvent)actionPort1SetKeyset;
    if (0 == strcmp(action, "port1-setjoystick"))       return (ButtonEvent)actionPort1SetJoystick;
    if (0 == strcmp(action, "port2-setnone"))           return (ButtonEvent)actionPort2SetNone;
    if (0 == strcmp(action, "port2-setmouse"))          return (ButtonEvent)actionPort2SetMouse;
    if (0 == strcmp(action, "port2-setnumpad"))         return (ButtonEvent)actionPort2SetNumpad;
    if (0 == strcmp(action, "port2-setkeyset"))         return (ButtonEvent)actionPort2SetKeyset;
    if (0 == strcmp(action, "port2-setjoystick"))       return (ButtonEvent)actionPort2SetJoystick;

    if (0 == strcmp(action, "level-master"))      return (ButtonEvent)actionVolumeSetMaster;
    if (0 == strcmp(action, "level-psg"))         return (ButtonEvent)actionVolumeSetPsg;
    if (0 == strcmp(action, "level-pcm"))         return (ButtonEvent)actionVolumeSetPcm;
    if (0 == strcmp(action, "level-scc"))         return (ButtonEvent)actionVolumeSetScc;
    if (0 == strcmp(action, "level-keyboard"))    return (ButtonEvent)actionVolumeSetKeyboard;
    if (0 == strcmp(action, "level-msxmusic"))    return (ButtonEvent)actionVolumeSetMsxMusic;
    if (0 == strcmp(action, "level-msxaudio"))    return (ButtonEvent)actionVolumeSetMsxAudio;
    if (0 == strcmp(action, "level-moonsound"))   return (ButtonEvent)actionVolumeSetMoonsound;
    if (0 == strcmp(action, "pan-psg"))           return (ButtonEvent)actionPanSetPsg;
    if (0 == strcmp(action, "pan-pcm"))           return (ButtonEvent)actionPanSetPcm;
    if (0 == strcmp(action, "pan-scc"))           return (ButtonEvent)actionPanSetScc;
    if (0 == strcmp(action, "pan-keyboard"))      return (ButtonEvent)actionPanSetKeyboard;
    if (0 == strcmp(action, "pan-msxmusic"))      return (ButtonEvent)actionPanSetMsxMusic;
    if (0 == strcmp(action, "pan-msxaudio"))      return (ButtonEvent)actionPanSetMsxAudio;
    if (0 == strcmp(action, "pan-moonsound"))     return (ButtonEvent)actionPanSetMoonsound;

    if (0 == strcmp(action, "slider-rensha"))       return (ButtonEvent)actionRenshaSetLevel;

    if (0 == strcmp(action, "slider-emuspeed"))     return (ButtonEvent)actionEmuSpeedSet;
    
    if (0 == strcmp(action, "cart1-setautoreset"))   return (ButtonEvent)actionSetCartAutoReset;
    if (0 == strcmp(action, "diska-setautoreset"))   return (ButtonEvent)actionSetDiskAutoResetA;
    if (0 == strcmp(action, "cas-setautorewind"))    return (ButtonEvent)actionSetCasAutoRewind;
    if (0 == strcmp(action, "sprite-setenable"))     return (ButtonEvent)actionSetSpriteEnable;
    if (0 == strcmp(action, "switch-setfdctiming"))  return (ButtonEvent)actionSetFdcTiming;
    if (0 == strcmp(action, "switch-setmsxaudio"))   return (ButtonEvent)actionSetMsxAudioSwitch;
    if (0 == strcmp(action, "switch-setfront"))      return (ButtonEvent)actionSetFrontSwitch;
    if (0 == strcmp(action, "switch-setpause"))      return (ButtonEvent)actionSetPauseSwitch;
    if (0 == strcmp(action, "audio-setrecord"))      return (ButtonEvent)actionSetWaveCapture;
    if (0 == strcmp(action, "mouse-setcapture"))     return (ButtonEvent)actionSetMouseCapture;
    if (0 == strcmp(action, "window-setfullscreen")) return (ButtonEvent)actionSetFullscreen;
    if (0 == strcmp(action, "cas-setreadonly"))      return (ButtonEvent)actionSetCasReadonly;
    if (0 == strcmp(action, "audio-setmute"))        return (ButtonEvent)actionSetVolumeMute;
    if (0 == strcmp(action, "audio-setstereo"))      return (ButtonEvent)actionSetVolumeStereo;
    
	return NULL;
}

static int getKeyCode(TiXmlElement* el, char* triggerName)
{
    const char* keycode = el->Attribute(triggerName);
    if (keycode == NULL) {
        return -1;
    }
    
    return keyboardStringToKeyCode(keycode);
}


static int getIndexedTrigger(TiXmlElement* el, char* triggerName, int idx)
{
    const char* trigger = el->Attribute(triggerName);
    if (trigger == NULL) {
        return THEME_TRIGGER_NONE;
    }

    int inverted = (strlen(trigger) > 4 && 0 == memcmp(trigger, "not ", 4));

    const char* s = inverted ? trigger + 4 : trigger;
    int         t = inverted ? THEME_TRIGGER_NOT : 0;
    
    if (0 == strcmp(s, "key-pressed"))    return t | (THEME_TRIGGER_FIRST_KEY_PRESSED + idx);
    if (0 == strcmp(s, "key-configured")) return t | (THEME_TRIGGER_FIRST_KEY_CONFIG + idx);

    return -1;
}

static int getTrigger(TiXmlElement* el, char* triggerName)
{
    const char* trigger = el->Attribute(triggerName);
    if (trigger == NULL) {
        return THEME_TRIGGER_NONE;
    }

    int inverted = (strlen(trigger) > 4 && 0 == memcmp(trigger, "not ", 4));

    const char* s = inverted ? trigger + 4 : trigger;
    int         t = inverted ? THEME_TRIGGER_NOT : 0;
    
    if (0 == strcmp(s, "emu-stopped"))              return t | THEME_TRIGGER_IMG_STOPPED;
    if (0 == strcmp(s, "emu-paused"))               return t | THEME_TRIGGER_IMG_PAUSED;
    if (0 == strcmp(s, "emu-running"))              return t | THEME_TRIGGER_IMG_RUNNING;
    
    if (0 == strcmp(s, "cpu-trace"))                return t | THEME_TRIGGER_IMG_TRACE;

    if (0 == strcmp(s, "led-diska"))                return t | THEME_TRIGGER_IMG_DISKA;
    if (0 == strcmp(s, "led-diskb"))                return t | THEME_TRIGGER_IMG_DISKB;
    if (0 == strcmp(s, "led-cassette"))             return t | THEME_TRIGGER_IMG_CAS;
    if (0 == strcmp(s, "led-audioswitch"))          return t | THEME_TRIGGER_IMG_AS;
    if (0 == strcmp(s, "led-frontswitch"))          return t | THEME_TRIGGER_IMG_FS;
    if (0 == strcmp(s, "led-pauseswitch"))          return t | THEME_TRIGGER_IMG_PS;
    if (0 == strcmp(s, "led-caps"))                 return t | THEME_TRIGGER_IMG_CAPS;
    if (0 == strcmp(s, "led-kana"))                 return t | THEME_TRIGGER_IMG_KANA;
    if (0 == strcmp(s, "led-turbor"))               return t | THEME_TRIGGER_IMG_TURBOR;
    if (0 == strcmp(s, "led-pause"))                return t | THEME_TRIGGER_IMG_PAUSE;
    
    if (0 == strcmp(s, "enable-fdctiming"))         return t | THEME_TRIGGER_IMG_FDCTIMING;

    if (0 == strcmp(s, "enable-keyboard"))          return t | THEME_TRIGGER_IMG_KBD;
    if (0 == strcmp(s, "enable-moonsound"))         return t | THEME_TRIGGER_IMG_MOON;
    if (0 == strcmp(s, "enable-msxaudio"))          return t | THEME_TRIGGER_IMG_MSXA;
    if (0 == strcmp(s, "enable-msxmusic"))          return t | THEME_TRIGGER_IMG_MSXM;
    if (0 == strcmp(s, "enable-psg"))               return t | THEME_TRIGGER_IMG_PSG;
    if (0 == strcmp(s, "enable-scc"))               return t | THEME_TRIGGER_IMG_SCC;
    if (0 == strcmp(s, "enable-pcm"))               return t | THEME_TRIGGER_IMG_PCM;
    if (0 == strcmp(s, "enable-master"))            return t | THEME_TRIGGER_IMG_MASTER;
    if (0 == strcmp(s, "enable-stereo"))            return t | THEME_TRIGGER_IMG_STEREO;
    
    if (0 == strcmp(s, "volume-keyboard-left"))     return t | THEME_TRIGGER_IMG_L_KBD;
    if (0 == strcmp(s, "volume-keyboard-right"))    return t | THEME_TRIGGER_IMG_R_KBD;
    if (0 == strcmp(s, "volume-moonsound-left"))    return t | THEME_TRIGGER_IMG_L_MOON;
    if (0 == strcmp(s, "volume-moonsound-right"))   return t | THEME_TRIGGER_IMG_R_MOON;
    if (0 == strcmp(s, "volume-msxaudio-left"))     return t | THEME_TRIGGER_IMG_L_MSXA;
    if (0 == strcmp(s, "volume-msxaudio-right"))    return t | THEME_TRIGGER_IMG_R_MSXA;
    if (0 == strcmp(s, "volume-msxmusic-left"))     return t | THEME_TRIGGER_IMG_L_MSXM;
    if (0 == strcmp(s, "volume-msxmusic-right"))    return t | THEME_TRIGGER_IMG_R_MSXM;
    if (0 == strcmp(s, "volume-psg-left"))          return t | THEME_TRIGGER_IMG_L_PSG;
    if (0 == strcmp(s, "volume-psg-right"))         return t | THEME_TRIGGER_IMG_R_PSG;
    if (0 == strcmp(s, "volume-scc-left"))          return t | THEME_TRIGGER_IMG_L_SCC;
    if (0 == strcmp(s, "volume-scc-right"))         return t | THEME_TRIGGER_IMG_R_SCC;
    if (0 == strcmp(s, "volume-pcm-left"))          return t | THEME_TRIGGER_IMG_L_PCM;
    if (0 == strcmp(s, "volume-pcm-right"))         return t | THEME_TRIGGER_IMG_R_PCM;
    if (0 == strcmp(s, "volume-master-left"))       return t | THEME_TRIGGER_IMG_L_MASTER;
    if (0 == strcmp(s, "volume-master-right"))      return t | THEME_TRIGGER_IMG_R_MASTER;

    if (0 == strcmp(s, "slider-rensha"))            return t | THEME_TRIGGER_RENSHA;
    if (0 == strcmp(s, "led-rensha"))               return t | THEME_TRIGGER_RENSHALED;
    
    if (0 == strcmp(s, "slider-emuspeed"))          return t | THEME_TRIGGER_EMUSPEED;

    if (0 == strcmp(s, "level-master"))            return t | THEME_TRIGGER_LEVEL_MASTER;
    if (0 == strcmp(s, "level-psg"))               return t | THEME_TRIGGER_LEVEL_PSG;
    if (0 == strcmp(s, "level-pcm"))               return t | THEME_TRIGGER_LEVEL_PCM;
    if (0 == strcmp(s, "level-scc"))               return t | THEME_TRIGGER_LEVEL_SCC;
    if (0 == strcmp(s, "level-keyboard"))          return t | THEME_TRIGGER_LEVEL_KEYBOARD;
    if (0 == strcmp(s, "level-msxmusic"))          return t | THEME_TRIGGER_LEVEL_MSXMUSIC;
    if (0 == strcmp(s, "level-msxaudio"))          return t | THEME_TRIGGER_LEVEL_MSXAUDIO;
    if (0 == strcmp(s, "level-moonsound"))         return t | THEME_TRIGGER_LEVEL_MOONSOUND;
    if (0 == strcmp(s, "pan-psg"))                 return t | THEME_TRIGGER_PAN_PSG;
    if (0 == strcmp(s, "pan-pcm"))                 return t | THEME_TRIGGER_PAN_PCM;
    if (0 == strcmp(s, "pan-scc"))                 return t | THEME_TRIGGER_PAN_SCC;
    if (0 == strcmp(s, "pan-keyboard"))            return t | THEME_TRIGGER_PAN_KEYBOARD;
    if (0 == strcmp(s, "pan-msxmusic"))            return t | THEME_TRIGGER_PAN_MSXMUSIC;
    if (0 == strcmp(s, "pan-msxaudio"))            return t | THEME_TRIGGER_PAN_MSXAUDIO;
    if (0 == strcmp(s, "pan-moonsound"))           return t | THEME_TRIGGER_PAN_MOONSOUND;

    if (0 == strcmp(s, "port1-enable"))             return t | THEME_TRIGGER_IMG_PORT1_EN;
    if (0 == strcmp(s, "port1-none"))               return t | THEME_TRIGGER_IMG_PORT1_NONE;
    if (0 == strcmp(s, "port1-mouse"))              return t | THEME_TRIGGER_IMG_PORT1_MOUSE;
    if (0 == strcmp(s, "port1-numpad"))             return t | THEME_TRIGGER_IMG_PORT1_NUM;
    if (0 == strcmp(s, "port1-keyboard"))           return t | THEME_TRIGGER_IMG_PORT1_KBD;
    if (0 == strcmp(s, "port1-joystick"))           return t | THEME_TRIGGER_IMG_PORT1_JOY;
    if (0 == strcmp(s, "port2-enable"))             return t | THEME_TRIGGER_IMG_PORT2_EN;
    if (0 == strcmp(s, "port2-none"))               return t | THEME_TRIGGER_IMG_PORT2_NONE;
    if (0 == strcmp(s, "port2-mouse"))              return t | THEME_TRIGGER_IMG_PORT2_MOUSE;
    if (0 == strcmp(s, "port2-numpad"))             return t | THEME_TRIGGER_IMG_PORT2_NUM;
    if (0 == strcmp(s, "port2-keyboard"))           return t | THEME_TRIGGER_IMG_PORT2_KBD;
    if (0 == strcmp(s, "port2-joystick"))           return t | THEME_TRIGGER_IMG_PORT2_JOY;

    if (0 == strcmp(s, "using-moonsound"))          return t | THEME_TRIGGER_IMG_M_MOON;
    if (0 == strcmp(s, "using-msxmusic"))           return t | THEME_TRIGGER_IMG_M_MSXM;
    if (0 == strcmp(s, "using-msxaudio"))           return t | THEME_TRIGGER_IMG_M_MSXA;
    if (0 == strcmp(s, "using-scc"))                return t | THEME_TRIGGER_IMG_M_SCC;
    if (0 == strcmp(s, "using-rom"))                return t | THEME_TRIGGER_IMG_M_ROM;
    if (0 == strcmp(s, "using-megaram"))            return t | THEME_TRIGGER_IMG_M_MEGARAM;
    if (0 == strcmp(s, "using-megarom"))            return t | THEME_TRIGGER_IMG_M_MEGAROM;
    if (0 == strcmp(s, "using-fmpac"))              return t | THEME_TRIGGER_IMG_M_FMPAC;

    if (0 == strcmp(s, "status-record"))            return t | THEME_TRIGGER_IMG_REC;
    if (0 == strcmp(s, "status-diskreset"))         return t | THEME_TRIGGER_IMG_DISK_RI;
    if (0 == strcmp(s, "status-cartreset"))         return t | THEME_TRIGGER_IMG_CART_RI;
    if (0 == strcmp(s, "status-casreadonly"))       return t | THEME_TRIGGER_IMG_CAS_RO;
    if (0 == strcmp(s, "status-scanlines"))         return t | THEME_TRIGGER_IMG_SCANLINES;
    if (0 == strcmp(s, "status-hstretch"))          return t | THEME_TRIGGER_IMG_HSTRETCH;
    if (0 == strcmp(s, "status-vstretch"))          return t | THEME_TRIGGER_IMG_VSTRETCH;
    
    if (0 == strcmp(s, "text-scanlinespct"))        return t | THEME_TRIGGER_TEXT_SCANLINESPCT;
    if (0 == strcmp(s, "text-emufrequency"))        return t | THEME_TRIGGER_TEXT_FREQ;
    if (0 == strcmp(s, "text-cpuusage"))            return t | THEME_TRIGGER_TEXT_CPU;
    if (0 == strcmp(s, "text-framespersecond"))     return t | THEME_TRIGGER_TEXT_FPS;
    if (0 == strcmp(s, "text-ramsize"))             return t | THEME_TRIGGER_TEXT_RAM;
    if (0 == strcmp(s, "text-vramsize"))            return t | THEME_TRIGGER_TEXT_VRAM;
    if (0 == strcmp(s, "text-screentype"))          return t | THEME_TRIGGER_TEXT_SCREEN;
    if (0 == strcmp(s, "text-screentypeshort"))     return t | THEME_TRIGGER_TEXT_SCREENSHORT;
    if (0 == strcmp(s, "text-rommapper1"))          return t | THEME_TRIGGER_TEXT_ROMMAPPER1;
    if (0 == strcmp(s, "text-rommapper2"))          return t | THEME_TRIGGER_TEXT_ROMMAPPER2;
    if (0 == strcmp(s, "text-rommapper1short"))     return t | THEME_TRIGGER_TEXT_ROMMAPPER1SHORT;
    if (0 == strcmp(s, "text-rommapper2short"))     return t | THEME_TRIGGER_TEXT_ROMMAPPER2SHORT;
    if (0 == strcmp(s, "text-machinename"))         return t | THEME_TRIGGER_TEXT_MACHINENAME;
    if (0 == strcmp(s, "text-runningname"))         return t | THEME_TRIGGER_TEXT_RUNNAME;
    if (0 == strcmp(s, "text-version"))             return t | THEME_TRIGGER_TEXT_VERSION;
    if (0 == strcmp(s, "text-buildnumber"))         return t | THEME_TRIGGER_TEXT_BUILDNUMBER;
    if (0 == strcmp(s, "text-buildandversion"))     return t | THEME_TRIGGER_TEXT_BUILDANDVER;
    if (0 == strcmp(s, "text-selectedkey"))         return t | THEME_TRIGGER_TEXT_SELECTEDKEY;
    if (0 == strcmp(s, "text-mappedkey"))           return t | THEME_TRIGGER_TEXT_MAPPEDKEY;
    
    if (0 == strcmp(s, "lang-kbd-selkey"))          return t | THEME_TRIGGER_LANG_KBD_SELKEY;
    if (0 == strcmp(s, "lang-kbd-mappedto"))        return t | THEME_TRIGGER_LANG_KBD_MAPPEDTO;
    if (0 == strcmp(s, "lang-kbd-mapscheme"))       return t | THEME_TRIGGER_LANG_KBD_MAPSCHEME;

    return -1;
}

static ArchBitmap* loadBitmap(TiXmlElement* el, int* x, int* y, int* columns)
{
    *x = 0;
    *y = 0;
    *columns = 999;

    el->QueryIntAttribute("srcColumns", columns);
    el->QueryIntAttribute("x", x);
    el->QueryIntAttribute("y", y);

    const char* src = el->Attribute("src");
    if (src == NULL) {
        return NULL;
    }
    
    return archBitmapCreateFromFile(src);
}


static void addImage(Theme* theme, TiXmlElement* el)
{
    int x, y, cols;
    ArchBitmap* bitmap = loadBitmap(el, &x, &y, &cols);
    if (bitmap == NULL) {
        return;
    }

    ThemeTrigger visible = (ThemeTrigger)getTrigger(el, "visible");
    if (visible == -1) {
        visible = THEME_TRIGGER_NONE;
    }

    themeAddImage(theme, activeImageCreate(x, y, cols, bitmap, 1), THEME_TRIGGER_NONE, visible);
}

static void addLed(Theme* theme, TiXmlElement* el)
{
    int x, y, cols;
    ArchBitmap* bitmap = loadBitmap(el, &x, &y, &cols);
    if (bitmap == NULL) {
        return;
    }

    ThemeTrigger trigger = (ThemeTrigger)getTrigger(el, "trigger");
    if (trigger == -1) {
        return;
    }

    ThemeTrigger visible = (ThemeTrigger)getTrigger(el, "visible");
    if (visible == -1) {
        visible = THEME_TRIGGER_NONE;
    }

    themeAddImage(theme, activeImageCreate(x, y, cols, bitmap, 2), trigger, visible);
}

static void addMeter(Theme* theme, TiXmlElement* el)
{
    int x, y, cols;
    ArchBitmap* bitmap = loadBitmap(el, &x, &y, &cols);
    if (bitmap == NULL) {
        return;
    }

    ThemeTrigger trigger = (ThemeTrigger)getTrigger(el, "trigger");
    if (trigger == -1) {
        return;
    }

    ThemeTrigger visible = (ThemeTrigger)getTrigger(el, "visible");
    if (visible == -1) {
        visible = THEME_TRIGGER_NONE;
    }

    int max = 1;
    el->QueryIntAttribute("max", &max);

    themeAddMeter(theme, activeMeterCreate(x, y, cols, bitmap, max), trigger, visible);
}

static void addSlider(Theme* theme, TiXmlElement* el)
{
    int x, y, cols;
    ArchBitmap* bitmap = loadBitmap(el, &x, &y, &cols);
    if (bitmap == NULL) {
        return;
    }

    ThemeTrigger trigger = (ThemeTrigger)getTrigger(el, "trigger");
    if (trigger == -1) {
        return;
    }

    ThemeTrigger visible = (ThemeTrigger)getTrigger(el, "visible");
    if (visible == -1) {
        visible = THEME_TRIGGER_NONE;
    }

    int arga, argb;
    SliderEvent action = (SliderEvent)getAction(el, "action", "arga", "argb", &arga, &argb);

    int max = 1;
    el->QueryIntAttribute("max", &max);

    AsDirection direction = AS_BOTH;
    const char* align = el->Attribute("direction");
    if (align != 0 && strcmp(align, "vertical") == 0) {
        direction = AS_VERTICAL;
    }
    if (align != 0 && strcmp(align, "horizontal") == 0) {
        direction = AS_HORIZONTAL;
    }
    
    int sensitivity = 1;
    el->QueryIntAttribute("sensitivity", &sensitivity);

    themeAddSlider(theme, activeSliderCreate(x, y, cols, bitmap, action, max, direction, sensitivity), trigger, visible);
}

static void addButton(Theme* theme, TiXmlElement* el)
{
    int x, y, cols;
    ArchBitmap* bitmap = loadBitmap(el, &x, &y, &cols);
    if (bitmap == NULL) {
        return;
    }

    ThemeTrigger trigger = (ThemeTrigger)getTrigger(el, "trigger");
    if (trigger == -1) {
        return;
    }

    ThemeTrigger visible = (ThemeTrigger)getTrigger(el, "visible");
    if (visible == -1) {
        visible = THEME_TRIGGER_NONE;
    }

    int arga, argb;
    ButtonEvent action = getAction(el, "action", "arga", "argb", &arga, &argb);

    themeAddButton(theme, activeButtonCreate(x, y, cols, bitmap, action, arga, argb), trigger, visible, THEME_TRIGGER_NONE);
}

static void addToggleButton(Theme* theme, TiXmlElement* el)
{
    int x, y, cols;
    ArchBitmap* bitmap = loadBitmap(el, &x, &y, &cols);
    if (bitmap == NULL) {
        return;
    }

    ThemeTrigger trigger = (ThemeTrigger)getTrigger(el, "trigger");
    if (trigger == -1) {
        return;
    }

    ThemeTrigger visible = (ThemeTrigger)getTrigger(el, "visible");
    if (visible == -1) {
        visible = THEME_TRIGGER_NONE;
    }

    int arga, argb;
    ButtonEvent action = getAction(el, "action", "arga", "argb", &arga, &argb);

    themeAddToggleButton(theme, activeToggleButtonCreate(x, y, cols, bitmap, action, arga, argb), 
                         trigger, visible, THEME_TRIGGER_NONE);
}

static void addDualButton(Theme* theme, TiXmlElement* el)
{
    int x, y, cols;
    ArchBitmap* bitmap = loadBitmap(el, &x, &y, &cols);
    if (bitmap == NULL) {
        return;
    }

    ThemeTrigger trigger = (ThemeTrigger)getTrigger(el, "trigger");
    if (trigger == -1) {
        return;
    }

    ThemeTrigger visible = (ThemeTrigger)getTrigger(el, "visible");
    if (visible == -1) {
        visible = THEME_TRIGGER_NONE;
    }

    int arg1x, arg1y;
    ButtonEvent action1 = getAction(el, "action1", "arg1x", "arg1y", &arg1x, &arg1y);
    
    int arg2x, arg2y;
    ButtonEvent action2 = getAction(el, "action2", "arg2x", "arg2y", &arg2x, &arg2y);

    int vertical = 0;
    const char* align = el->Attribute("direction");
    if (align != 0 && strcmp(align, "vertical") == 0) {
        vertical = 1;
    }

    themeAddDualButton(theme, activeDualButtonCreate(x, y, cols, bitmap, action1, arg1x, arg1y,
                                                      action2, arg2x, arg2y, vertical), 
                       trigger, visible, THEME_TRIGGER_NONE);
}

static void addKeyButton(Theme* theme, TiXmlElement* el)
{
    int x, y, cols;
    ArchBitmap* bitmap = loadBitmap(el, &x, &y, &cols);
    if (bitmap == NULL) {
        return;
    }

    int keycode = getKeyCode(el, "keycode");
    if (keycode < 0) {
        return;
    }

    ThemeTrigger visible = (ThemeTrigger)getTrigger(el, "visible");
    if (visible == -1) {
        visible = (ThemeTrigger)getIndexedTrigger(el, "visible", keycode);
        if (visible == -1) {
            visible = THEME_TRIGGER_NONE;
        }
    }

    ThemeTrigger trigger = (ThemeTrigger)(THEME_TRIGGER_FIRST_KEY_CONFIG + keycode);
    ThemeTrigger pressed = (ThemeTrigger)(THEME_TRIGGER_FIRST_KEY_PRESSED + keycode);
    ButtonEvent action = (ButtonEvent)actionKeyPress;

    themeAddToggleButton(theme, activeToggleButtonCreate(x, y, cols, bitmap, action, keycode, -1), 
                         trigger, visible, pressed);
}


static void addObject(Theme* theme, TiXmlElement* el)
{
    int x = 0;
    int y = 0;
    int width = -1;
    int height = -1;

    el->QueryIntAttribute("x", &x);
    el->QueryIntAttribute("y", &y);
    el->QueryIntAttribute("width", &width);
    el->QueryIntAttribute("height", &height);
    
    const char* id = el->Attribute("id");
    if (id == NULL) {
        return;
    }

    ThemeTrigger visible = (ThemeTrigger)getTrigger(el, "visible");
    if (visible == -1) {
        visible = THEME_TRIGGER_NONE;
    }

    themeAddObject(theme, activeObjectCreate(x, y, width, height, id), visible);
}

static void addText(Theme* theme, TiXmlElement* el)
{
    int x, y, cols;
    ArchBitmap* bitmap = loadBitmap(el, &x, &y, &cols);
    if (bitmap == NULL) {
        return;
    }

    ThemeTrigger trigger = (ThemeTrigger)getTrigger(el, "trigger");
    if (trigger == -1) {
        return;
    }
    
    int width = 10;
    el->QueryIntAttribute("width", &width);
    
    int type = 0;
    const char* typeStr = el->Attribute("type");
    if (typeStr != NULL && 0 == strcmp(typeStr, "native")) {
        type = 1;
    }

    int color = 0xffffff;
    const char* colStr = el->Attribute("fgcolor");
    if (colStr != NULL) {
        sscanf(colStr, "%x", &color);
        color = RGB((color>>16), ((color>>8)&0xff), (color&0xff));
    }    

    int rightAlign = 0;
    const char* align = el->Attribute("align");
    if (align != 0 && strcmp(align, "right") == 0) {
        rightAlign = 1;
    }

    ThemeTrigger visible = (ThemeTrigger)getTrigger(el, "visible");
    if (visible == -1) {
        visible = THEME_TRIGGER_NONE;
    }
    
    themeAddText(theme, activeTextCreate(x, y, cols, bitmap, width, type, color, rightAlign), trigger, visible);
}

static Theme* loadTheme(TiXmlElement* root, ThemeInfo themeInfo) 
{
    TiXmlElement* modeEl;

    Theme* theme = NULL;

    for (modeEl = root->FirstChildElement(); modeEl != NULL; modeEl = modeEl->NextSiblingElement()) {
        if (strcmp(modeEl->Value(), "theme") != 0) {
            continue;
        }

        const char* mode = modeEl->Attribute("mode");
        if (strcmp(mode, themeDefaultInfo[themeInfo].mode) != 0) {
            continue;
        }

        // Get width and height of main window
        int width  = themeDefaultInfo[themeInfo].width;
        int height = themeDefaultInfo[themeInfo].height;
    
        if (themeInfo == THEME_SMALL || themeInfo == THEME_NORMAL) {
            modeEl->QueryIntAttribute("width", &width);
            modeEl->QueryIntAttribute("height", &height);
        }

        TiXmlElement* infoEl;
        ClipPoint clipPointList[MAX_CLIP_POINTS];  
        int clipPointCount = 0;      
        int emuX           = 0;
        int emuY           = 0;
        int menuX          = 0;
        int menuY          = -100;
        int menuWidth      = 357;
        int menuColor      = RGB(219, 221, 224);
        int menuFocusColor = RGB(128, 128, 255);
        int menuTextColor  = RGB(0, 0, 0);
        int color;

        // First, get info about emu window and menu
        for (infoEl = modeEl->FirstChildElement(); infoEl != NULL; infoEl = infoEl->NextSiblingElement()) {
            if (strcmp(infoEl->Value(), "emuwindow") == 0) {
                infoEl->QueryIntAttribute("x", &emuX);
                infoEl->QueryIntAttribute("y", &emuY);
            }
            
            if (strcmp(infoEl->Value(), "menu") == 0) {
                if (themeInfo == THEME_SMALL || themeInfo == THEME_NORMAL) {
                    infoEl->QueryIntAttribute("x", &menuX);
                    infoEl->QueryIntAttribute("y", &menuY);
                    infoEl->QueryIntAttribute("width", &menuWidth);
                }
                else {
                    menuX = 0;
                    menuY = 0;
                }
                const char* colStr = infoEl->Attribute("bgcolor");
                if (colStr != NULL) {
                    sscanf(colStr, "%x", &color);
                    menuColor = RGB((color>>16), ((color>>8)&0xff), (color&0xff));
                }
                
                colStr = infoEl->Attribute("fgcolor");
                if (colStr != NULL) {
                    sscanf(colStr, "%x", &color);
                    menuTextColor = RGB((color>>16), ((color>>8)&0xff), (color&0xff));
                }
               
                colStr = infoEl->Attribute("focuscolor");
                if (colStr != NULL) {
                    sscanf(colStr, "%x", &color);
                    menuFocusColor = RGB((color>>16), ((color>>8)&0xff), (color&0xff));
                }
            }

            if (strcmp(infoEl->Value(), "clipregion") == 0) {
                clipPointCount = 0;
                TiXmlElement* ptEl;
                for (ptEl = infoEl->FirstChildElement(); ptEl != NULL; ptEl = ptEl->NextSiblingElement()) {
                    if (strcmp(ptEl->Value(), "point") == 0) {
                        int x = -1;
                        int y = -1;
                        ptEl->QueryIntAttribute("x", &x);
                        ptEl->QueryIntAttribute("y", &y);
                        if (x >= 0 && y >= 0 && clipPointCount < MAX_CLIP_POINTS) {
                            ClipPoint clipPoint = { x, y };
                            clipPointList[clipPointCount++] = clipPoint;
                        }
                    }
                }
            }
        }

        theme = themeCreate(width,
                            height,
                            emuX,
                            emuY,
                            themeDefaultInfo[themeInfo].width,
                            themeDefaultInfo[themeInfo].height,
                            menuX, 
                            menuY, 
                            menuWidth,
                            menuColor,
                            menuFocusColor,
                            menuTextColor,
                            clipPointCount,
                            clipPointList);
        
        for (infoEl = modeEl->FirstChildElement(); infoEl != NULL; infoEl = infoEl->NextSiblingElement()) {
            if (strcmp(infoEl->Value(), "image") == 0) {
                addImage(theme, infoEl);
            }
            if (strcmp(infoEl->Value(), "led") == 0) {
                addLed(theme, infoEl);
            }
            if (strcmp(infoEl->Value(), "text") == 0) {
                addText(theme, infoEl);
            }
            if (strcmp(infoEl->Value(), "button") == 0) {
                addButton(theme, infoEl);
            }
            if (strcmp(infoEl->Value(), "dualbutton") == 0) {
                addDualButton(theme, infoEl);
            }
            if (strcmp(infoEl->Value(), "togglebutton") == 0) {
                addToggleButton(theme, infoEl);
            }
            if (strcmp(infoEl->Value(), "keybutton") == 0) {
                addKeyButton(theme, infoEl);
            }
            if (strcmp(infoEl->Value(), "meter") == 0) {
                addMeter(theme, infoEl);
            }
            if (strcmp(infoEl->Value(), "slider") == 0) {
                addSlider(theme, infoEl);
            }
            if (strcmp(infoEl->Value(), "object") == 0) {
                addObject(theme, infoEl);
            }
        }
    }

    return theme;
}

extern "C" ThemeCollection* themeLoad(char* themeName) 
{
    char dirName[512];
    char oldDirName[512];

    GetCurrentDirectory(512, oldDirName);

    sprintf(dirName, "%s\\Themes\\%s", oldDirName, themeName);

    SetCurrentDirectory(dirName);

    TiXmlDocument doc("Theme.xml");

    doc.LoadFile();

    if (doc.Error()) {
        SetCurrentDirectory(oldDirName);
        return NULL;
    }

    TiXmlElement* root = doc.RootElement();

    if (root == NULL || strcmp(root->Value(), "bluemsxtheme") != 0) {
        SetCurrentDirectory(oldDirName);
        return NULL;
    }

    const char* name = root->Attribute( "name" );
    if (name == NULL) {
        name = themeName;
    }

    ThemeCollection* theme = (ThemeCollection*)calloc(1, sizeof(ThemeCollection));

    strcpy(theme->name, name);

    theme->little          = loadTheme(root, THEME_SMALL);
    theme->normal          = loadTheme(root, THEME_NORMAL);
    theme->fullscreen      = loadTheme(root, THEME_FULLSCREEN);
    theme->smallfullscreen = loadTheme(root, THEME_SMALLFULLSCREEN);

    if (theme->little == NULL && theme->normal == NULL &&
        theme->fullscreen == NULL && theme->smallfullscreen == NULL) 
    {
        free(theme);
        theme = NULL;
    }

    SetCurrentDirectory(oldDirName);
    return theme;
}

static ThemeCollection** currentWin32Theme = NULL;

extern "C" ThemeCollection** createThemeList(ThemeCollection* defaultTheme)
{
    ThemeCollection** themeList = (ThemeCollection**)calloc(1, 128 * sizeof(ThemeCollection*));
    int index = 0;

    // Set default theme
    if (defaultTheme != NULL) {
        themeList[index++] = defaultTheme;
    }

    // Load custom made themes
    WIN32_FIND_DATA wfd;
    HANDLE handle = FindFirstFile("Themes/*", &wfd);

    if (handle != INVALID_HANDLE_VALUE) {
        do {
		    DWORD fa = GetFileAttributes(wfd.cFileName);
            if (fa & FILE_ATTRIBUTE_DIRECTORY) {
                ThemeCollection* theme = themeLoad(wfd.cFileName);
                if (theme != NULL) {
                    if (theme->little == NULL)          theme->little =          themeList[0]->little;
                    if (theme->normal == NULL)          theme->normal =          themeList[0]->normal;
                    if (theme->fullscreen == NULL)      theme->fullscreen =      themeList[0]->fullscreen;
                    if (theme->smallfullscreen == NULL) theme->smallfullscreen = themeList[0]->smallfullscreen;
                    themeList[index++] = theme;
                }
            }
        } while (FindNextFile(handle, &wfd));

    	FindClose(handle);
    }

    themeList[index] = NULL;

    currentWin32Theme = themeList;

    return themeList;
}

extern "C" ThemeCollection** themeGetAvailable()
{
    return currentWin32Theme;
}

extern "C" int getThemeListIndex(ThemeCollection** themeList, const char* name, int forceMatch)
{
    int index = 0;
    while (*themeList) {
        if (strcmpnocase(name, (*themeList)->name) == 0) {
            return index;
        }
        index++;
        themeList++;
    }

    if (forceMatch) {
        return 0;
    }

    return -1;
}
