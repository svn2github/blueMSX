/*****************************************************************************
** File:
**      Win32ShortcutsConfig.h
**
** More info:   www.bluemsx.com
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
#ifndef WIN32_SHORTCUTSCONFIG_H
#define WIN32_SHORTCUTSCONFIG_H

#include <windows.h>
#include "Win32Properties.h"


#define HOTKEY_TYPE_NONE     0
#define HOTKEY_TYPE_KEYBOARD 1
#define HOTKEY_TYPE_JOYSTICK 2

typedef struct {
    unsigned type : 8;
    unsigned mods : 8;
    unsigned key  : 16;
} ShotcutHotkey;



typedef struct {
    ShotcutHotkey spritesEnable;
    ShotcutHotkey msxAudioSwitch;
    ShotcutHotkey frontSwitch;
    ShotcutHotkey pauseSwitch;
    ShotcutHotkey quit;
    ShotcutHotkey wavCapture;
    ShotcutHotkey screenCapture;
    ShotcutHotkey screenCaptureUnfilteredSmall;
    ShotcutHotkey screenCaptureUnfilteredLarge;
    ShotcutHotkey cpuStateLoad;
    ShotcutHotkey cpuStateSave;
    ShotcutHotkey cpuStateQuickLoad;
    ShotcutHotkey cpuStateQuickSave;
    ShotcutHotkey cartInsert1;
    ShotcutHotkey cartInsert2;
    ShotcutHotkey cartSpecialMenu1;
    ShotcutHotkey cartSpecialMenu2;
    ShotcutHotkey diskInsertA;
    ShotcutHotkey diskInsertB;
    ShotcutHotkey diskDirInsertA;
    ShotcutHotkey diskDirInsertB;
    ShotcutHotkey diskChangeA;
    ShotcutHotkey casInsert;
    ShotcutHotkey casRewind;
    ShotcutHotkey casSetPos;
    ShotcutHotkey mouseLockToggle;
    ShotcutHotkey emulationRunPause;
    ShotcutHotkey emulationStop;
    ShotcutHotkey emuSpeedFull;
    ShotcutHotkey emuSpeedNormal;
    ShotcutHotkey emuSpeedInc;
    ShotcutHotkey emuSpeedDec;
    ShotcutHotkey emuSpeedToggle;
    ShotcutHotkey windowSizeSmall;
    ShotcutHotkey windowSizeNormal;
    ShotcutHotkey windowSizeMinimized;
    ShotcutHotkey windowSizeFullscreen;
    ShotcutHotkey windowSizeFullscreenToggle;
    ShotcutHotkey resetSoft;
    ShotcutHotkey resetHard;
    ShotcutHotkey resetClean;
    ShotcutHotkey volumeIncrease;
    ShotcutHotkey volumeDecrease;
    ShotcutHotkey volumeMute;
    ShotcutHotkey volumeStereo;
    ShotcutHotkey cpuTrace;
    ShotcutHotkey themeSwitch;
    ShotcutHotkey casRemove;
    ShotcutHotkey diskRemoveA;
    ShotcutHotkey diskRemoveB;
    ShotcutHotkey cartRemove1;
    ShotcutHotkey cartRemove2;
    ShotcutHotkey cartAutoReset;
    ShotcutHotkey diskAutoResetA;
    ShotcutHotkey casToggleReadonly;
    ShotcutHotkey casAutoRewind;
    ShotcutHotkey casSave;
    ShotcutHotkey propShowEmulation;
    ShotcutHotkey propShowVideo;
    ShotcutHotkey propShowAudio;
    ShotcutHotkey propShowControls;
    ShotcutHotkey propShowPerformance;
    ShotcutHotkey propShowSettings;
    ShotcutHotkey propShowApearance;
    ShotcutHotkey optionsShowLanguage;
    ShotcutHotkey toolsShowMachineEditor;
    ShotcutHotkey toolsShowShorcutEditor;
    ShotcutHotkey helpShowHelp;
    ShotcutHotkey helpShowAbout;
} Shortcuts;


Shortcuts* shortcutsCreateProfile(char* profileName);
void shortcutsDestroyProfile(Shortcuts* shortcuts);
int shortcutsShowDialog(HWND hwnd, Properties* pProperties);
char* shortcutsToString(ShotcutHotkey hotkey);
void shortcutsSetDirectory(char* profileDir);
int shortcutsIsProfileValid(char* profileName);
int shortcutsGetAnyProfile(char* profileName);

#endif //WIN32_STATUSBAR_H
