/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Theme/Theme.c,v $
**
** $Revision: 1.12 $
**
** $Date: 2005-01-14 09:33:49 $
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
#include "Theme.h"
#include "Actions.h"
#include "ArchNotifications.h"

typedef enum { ITEM_IMAGE, ITEM_TEXT, ITEM_BUTTON, ITEM_DUALBUTTON, ITEM_TOGGLEBUTTON, ITEM_METER, ITEM_SLIDER, ITEM_OBJECT } ItemType;

struct ThemeItem {
    ThemeItem*   next;
    ItemType     type;
    void*        object;
    ThemeTrigger trigger;
    ThemeTrigger visible;
    ThemeTrigger pressed;
};

#define TEST(a, x) ((a & THEME_TRIGGER_NOT) ? !(x) : (x))

static int actionTypeToInt(ThemeTrigger actionType)
{
    int key;
    int idx = -1;
    switch (actionType & THEME_TRIGGER_MASK) {
    case THEME_TRIGGER_IMG_DISKA:       idx = TEST(actionType, themeTriggerLedDiskA()); break;
    case THEME_TRIGGER_IMG_DISKB:       idx = TEST(actionType, themeTriggerLedDiskB()); break;
    case THEME_TRIGGER_IMG_CAS:         idx = TEST(actionType, themeTriggerLedCas()); break;
    case THEME_TRIGGER_IMG_AS:          idx = TEST(actionType, themeTriggerLedAudioSwitch()); break;
    case THEME_TRIGGER_IMG_TRACE:       idx = TEST(actionType, themeTriggerCpuTraceEnable()); break;
    case THEME_TRIGGER_IMG_FS:          idx = TEST(actionType, themeTriggerLedFrontSwitch()); break;
    case THEME_TRIGGER_IMG_PS:          idx = TEST(actionType, themeTriggerLedPauseSwitch()); break;
    case THEME_TRIGGER_IMG_CAPS:        idx = TEST(actionType, themeTriggerLedCaps()); break;
    case THEME_TRIGGER_IMG_KANA:        idx = TEST(actionType, themeTriggerLedKana()); break;
    case THEME_TRIGGER_IMG_TURBOR:      idx = TEST(actionType, themeTriggerLedTurboR()); break;
    case THEME_TRIGGER_IMG_PAUSE:       idx = TEST(actionType, themeTriggerLedPause()); break;
    case THEME_TRIGGER_IMG_REC:         idx = TEST(actionType, themeTriggerLedRecord()); break;
    case THEME_TRIGGER_IMG_STOPPED:     idx = TEST(actionType, themeTriggerEmuStopped()); break;
    case THEME_TRIGGER_IMG_PAUSED:      idx = TEST(actionType, themeTriggerEmuPaused()); break;
    case THEME_TRIGGER_IMG_RUNNING:     idx = TEST(actionType, themeTriggerEmuRunning()); break;

    case THEME_TRIGGER_IMG_FDCTIMING:   idx = TEST(actionType, themeTriggerFdcTiming()); break;
    case THEME_TRIGGER_IMG_KBD:         idx = TEST(actionType, themeTriggerAudioKbd()); break;
    case THEME_TRIGGER_IMG_MOON:        idx = TEST(actionType, themeTriggerAudioMoonsound()); break;
    case THEME_TRIGGER_IMG_MSXA:        idx = TEST(actionType, themeTriggerAudioMsxAudio()); break;
    case THEME_TRIGGER_IMG_MSXM:        idx = TEST(actionType, themeTriggerAudioMsxMusic()); break;
    case THEME_TRIGGER_IMG_PSG:         idx = TEST(actionType, themeTriggerAudioPsg()); break;
    case THEME_TRIGGER_IMG_SCC:         idx = TEST(actionType, themeTriggerAudioScc()); break;
    case THEME_TRIGGER_IMG_PCM:         idx = TEST(actionType, themeTriggerAudioPcm()); break;
    case THEME_TRIGGER_IMG_MASTER:      idx = TEST(actionType, themeTriggerAudioMaster()); break;
    case THEME_TRIGGER_IMG_STEREO:      idx = TEST(actionType, themeTriggerAudioStereo()); break;
    case THEME_TRIGGER_IMG_L_KBD:       idx = themeTriggerVolKbdLeft(); break;
    case THEME_TRIGGER_IMG_R_KBD:       idx = themeTriggerVolKbdRight(); break;
    case THEME_TRIGGER_IMG_L_MOON:      idx = themeTriggerVolMoonsoundLeft(); break;
    case THEME_TRIGGER_IMG_R_MOON:      idx = themeTriggerVolMoonsoundRight(); break;
    case THEME_TRIGGER_IMG_L_MSXA:      idx = themeTriggerVolMsxAudioLeft(); break;
    case THEME_TRIGGER_IMG_R_MSXA:      idx = themeTriggerVolMsxAudioRight(); break;
    case THEME_TRIGGER_IMG_L_MSXM:      idx = themeTriggerVolMsxMusicLeft(); break;
    case THEME_TRIGGER_IMG_R_MSXM:      idx = themeTriggerVolMsxMusicRight(); break;
    case THEME_TRIGGER_IMG_L_PSG:       idx = themeTriggerVolPsgLeft(); break;
    case THEME_TRIGGER_IMG_R_PSG:       idx = themeTriggerVolPsgRight(); break;
    case THEME_TRIGGER_IMG_L_SCC:       idx = themeTriggerVolSccLeft(); break;
    case THEME_TRIGGER_IMG_R_SCC:       idx = themeTriggerVolSccRight(); break;
    case THEME_TRIGGER_IMG_L_PCM:       idx = themeTriggerVolPcmLeft(); break;
    case THEME_TRIGGER_IMG_R_PCM:       idx = themeTriggerVolPcmRight(); break;
    case THEME_TRIGGER_IMG_L_MASTER:    idx = themeTriggerVolMasterLeft(); break;
    case THEME_TRIGGER_IMG_R_MASTER:    idx = themeTriggerVolMasterRight(); break;

    case THEME_TRIGGER_LEVEL_MASTER:    idx = themeTriggerLevelMaster(); break;
    case THEME_TRIGGER_LEVEL_PSG:       idx = themeTriggerLevelPsg(); break;
    case THEME_TRIGGER_LEVEL_PCM:       idx = themeTriggerLevelPcm(); break;
    case THEME_TRIGGER_LEVEL_SCC:       idx = themeTriggerLevelScc(); break;
    case THEME_TRIGGER_LEVEL_KEYBOARD:  idx = themeTriggerLevelKeyboard(); break;
    case THEME_TRIGGER_LEVEL_MSXMUSIC:  idx = themeTriggerLevelMsxMusic(); break;
    case THEME_TRIGGER_LEVEL_MSXAUDIO:  idx = themeTriggerLevelMsxAudio(); break;
    case THEME_TRIGGER_LEVEL_MOONSOUND: idx = themeTriggerLevelMoonsound(); break;
    case THEME_TRIGGER_PAN_PSG:         idx = themeTriggerPanPsg(); break;
    case THEME_TRIGGER_PAN_PCM:         idx = themeTriggerPanPcm(); break;
    case THEME_TRIGGER_PAN_SCC:         idx = themeTriggerPanScc(); break;
    case THEME_TRIGGER_PAN_KEYBOARD:    idx = themeTriggerPanKeyboard(); break;
    case THEME_TRIGGER_PAN_MSXMUSIC:    idx = themeTriggerPanMsxMusic(); break;
    case THEME_TRIGGER_PAN_MSXAUDIO:    idx = themeTriggerPanMsxAudio(); break;
    case THEME_TRIGGER_PAN_MOONSOUND:   idx = themeTriggerPanMoonsound(); break;

    case THEME_TRIGGER_EMUSPEED:        idx = themeTriggerLevelEmuSpeed(); break;

    case THEME_TRIGGER_RENSHA:          idx = themeTriggerLevelRensha(); break;
    case THEME_TRIGGER_RENSHALED:       idx = TEST(actionType, themeTriggerLedRensha()); break;

    case THEME_TRIGGER_IMG_PORT1_EN:    idx = TEST(actionType, themeTriggerPort1None() ^ 0xffff); break;
    case THEME_TRIGGER_IMG_PORT1_NONE:  idx = TEST(actionType, themeTriggerPort1None()); break;
    case THEME_TRIGGER_IMG_PORT1_MOUSE: idx = TEST(actionType, themeTriggerPort1Mouse()); break;
    case THEME_TRIGGER_IMG_PORT1_NUM:   idx = TEST(actionType, themeTriggerPort1Num()); break;
    case THEME_TRIGGER_IMG_PORT1_KBD:   idx = TEST(actionType, themeTriggerPort1Kbd()); break;
    case THEME_TRIGGER_IMG_PORT1_JOY:   idx = TEST(actionType, themeTriggerPort1Joy()); break;
    case THEME_TRIGGER_IMG_PORT2_EN:    idx = TEST(actionType, themeTriggerPort2None() ^ 0xffff); break;
    case THEME_TRIGGER_IMG_PORT2_NONE:  idx = TEST(actionType, themeTriggerPort2None()); break;
    case THEME_TRIGGER_IMG_PORT2_MOUSE: idx = TEST(actionType, themeTriggerPort2Mouse()); break;
    case THEME_TRIGGER_IMG_PORT2_NUM:   idx = TEST(actionType, themeTriggerPort2Num()); break;
    case THEME_TRIGGER_IMG_PORT2_KBD:   idx = TEST(actionType, themeTriggerPort2Kbd()); break;
    case THEME_TRIGGER_IMG_PORT2_JOY:   idx = TEST(actionType, themeTriggerPort2Joy()); break;
    case THEME_TRIGGER_IMG_M_MOON:      idx = TEST(actionType, themeTriggerMachineMoonsound()); break;
    case THEME_TRIGGER_IMG_M_MSXM:      idx = TEST(actionType, themeTriggerMachineMsxMusic()); break;
    case THEME_TRIGGER_IMG_M_MSXA:      idx = TEST(actionType, themeTriggerMachineMsxAudio()); break;
    case THEME_TRIGGER_IMG_M_SCC:       idx = TEST(actionType, themeTriggerMachineScc()); break;
    case THEME_TRIGGER_IMG_M_ROM:       idx = TEST(actionType, themeTriggerMachineRom()); break;
    case THEME_TRIGGER_IMG_M_MEGAROM:   idx = TEST(actionType, themeTriggerMachineMegaRom()); break;
    case THEME_TRIGGER_IMG_M_MEGARAM:   idx = TEST(actionType, themeTriggerMachineMegaRam()); break;
    case THEME_TRIGGER_IMG_M_FMPAC:     idx = TEST(actionType, themeTriggerMachineFmPac()); break;
    case THEME_TRIGGER_IMG_DISK_RI:     idx = TEST(actionType, themeTriggerConfDiskRI()); break;
    case THEME_TRIGGER_IMG_CART_RI:     idx = TEST(actionType, themeTriggerConfCartRI()); break;
    case THEME_TRIGGER_IMG_CAS_RO:      idx = TEST(actionType, themeTriggerConfCasRO()); break;
    case THEME_TRIGGER_IMG_SCANLINES:   idx = TEST(actionType, themeTriggerVideoScanlines()); break;
    case THEME_TRIGGER_IMG_HSTRETCH:    idx = TEST(actionType, themeTriggerVideoHstretch()); break;
    case THEME_TRIGGER_IMG_VSTRETCH:    idx = TEST(actionType, themeTriggerVideoVstretch()); break;
    }

    key = (actionType & THEME_TRIGGER_MASK) - THEME_TRIGGER_FIRST_KEY_PRESSED;
    if (key >= 0 && key <= THEME_TRIGGER_LAST_KEY_PRESSED - THEME_TRIGGER_FIRST_KEY_PRESSED) {
        idx = TEST(actionType, themeTriggerKeyPressed(key));
    }

    key = (actionType & THEME_TRIGGER_MASK) - THEME_TRIGGER_FIRST_KEY_CONFIG;
    if (key >= 0 && key <= THEME_TRIGGER_LAST_KEY_CONFIG - THEME_TRIGGER_FIRST_KEY_CONFIG) {
        idx = TEST(actionType, themeTriggerKeyConfigured(key));
    }

    return idx;
}

static char* actionTypeToStr(ThemeTrigger actionType)
{
    char* str = NULL;

    switch (actionType & THEME_TRIGGER_MASK) {
    case THEME_TRIGGER_TEXT_FREQ:            str = themeTriggerEmuFrequency(); break;
    case THEME_TRIGGER_TEXT_CPU:             str = themeTriggerCpuString(); break;
    case THEME_TRIGGER_TEXT_FPS:             str = themeTriggerFpsString(); break;
    case THEME_TRIGGER_TEXT_RAM:             str = themeTriggerMemoryRam(); break;
    case THEME_TRIGGER_TEXT_VRAM:            str = themeTriggerMemoryVram(); break;
    case THEME_TRIGGER_TEXT_SCREEN:          str = themeTriggerScreenMode(); break;
    case THEME_TRIGGER_TEXT_SCREENSHORT:     str = themeTriggerScreenModeShort(); break;
    case THEME_TRIGGER_TEXT_ROMMAPPER1:      str = themeTriggerRomMapper1(); break;
    case THEME_TRIGGER_TEXT_ROMMAPPER2:      str = themeTriggerRomMapper2(); break;
    case THEME_TRIGGER_TEXT_ROMMAPPER1SHORT: str = themeTriggerRomMapper1Short(); break;
    case THEME_TRIGGER_TEXT_ROMMAPPER2SHORT: str = themeTriggerRomMapper2Short(); break;
    case THEME_TRIGGER_TEXT_RUNNAME:         str = themeTriggerRunningName(); break;
    case THEME_TRIGGER_TEXT_MACHINENAME:     str = themeTriggerMachineName(); break;
    case THEME_TRIGGER_TEXT_SCANLINESPCT:    str = themeTriggerVideoScanlinePct(); break;
    case THEME_TRIGGER_TEXT_VERSION:         str = themeTriggerVersion(); break;
    case THEME_TRIGGER_TEXT_BUILDNUMBER:     str = themeTriggerBuildNumber(); break;
    case THEME_TRIGGER_TEXT_BUILDANDVER:     str = themeTriggerBuildAndVersion(); break;
    case THEME_TRIGGER_TEXT_SELECTEDKEY:     str = themeTriggerSelectedKey(); break;
    case THEME_TRIGGER_TEXT_MAPPEDKEY:       str = themeTriggerMappedKey(); break;
        
    case THEME_TRIGGER_LANG_KBD_SELKEY:      str = themeTriggerLangKbdSelKey(); break;
    case THEME_TRIGGER_LANG_KBD_MAPPEDTO:    str = themeTriggerLangKbdMappedTo(); break;
    case THEME_TRIGGER_LANG_KBD_MAPSCHEME:   str = themeTriggerLangKbdMapSCheme(); break;
    }
    return str;
}

static void themePageAddLast(ThemePage* themePage, ItemType itemType, void* object, ThemeTrigger trigger, ThemeTrigger visible, ThemeTrigger pressed)
{
    ThemeItem* item = malloc(sizeof(ThemeItem));
    ThemeItem** pItem = &themePage->itemList;

    while (*pItem != NULL) {
        pItem = &((*pItem)->next);
    }

    *pItem = item;
    
    item->type = itemType;
    item->object = object;
    item->trigger = trigger;
    item->visible = visible;
    item->pressed = pressed;
    item->next = NULL;
}

ThemePage* themePageCreate(const char* name,
                           int width,
                           int height,
                           int emuPosX,
                           int emuPosY,
                           int emuWidth,
                           int emuHeight,
                           int menuPosX,
                           int menuPosY,
                           int menuWidth,
                           COLORREF menuColor,
                           COLORREF menuFocusColor,
                           COLORREF menuTextColor,
                           int        clipPointCount,
                           ClipPoint* clipPointList)
{
    ThemePage* themePage = calloc(1, sizeof(ThemePage));

    strcpy(themePage->name, name);

    themePage->width           = width;
    themePage->height          = height;
    themePage->emuWinX         = emuPosX;
    themePage->emuWinY         = emuPosY;
    themePage->emuWinW         = emuWidth;
    themePage->emuWinH         = emuHeight;
    themePage->menu.x          = menuPosX;
    themePage->menu.y          = menuPosY;
    themePage->menu.width      = menuWidth;
    themePage->menu.color      = menuColor;
    themePage->menu.focusColor = menuFocusColor;
    themePage->menu.textColor  = menuTextColor;
    themePage->clipPoint.count = clipPointCount;

    if (clipPointCount > 0) {
        int size = clipPointCount * sizeof(ClipPoint);
        themePage->clipPoint.list = malloc(size);
        memcpy(themePage->clipPoint.list, clipPointList, size);
    }

    return themePage;
}

void themePageDestroy(ThemePage* themePage)
{
    ThemeItem* item;
    
    if (themePage == NULL) {
        return;
    }

    item = themePage->itemList;

    while (item != NULL) {
        ThemeItem* next = item->next;

        switch (item->type) {
        case ITEM_IMAGE:
            activeImageDestroy(item->object);
            break;
        case ITEM_TEXT:
            activeTextDestroy(item->object);
            break;
        case ITEM_BUTTON:
            activeButtonDestroy(item->object);
            break;
        case ITEM_DUALBUTTON:
            activeDualButtonDestroy(item->object);
            break;
        case ITEM_TOGGLEBUTTON:
            activeToggleButtonDestroy(item->object);
            break;
        case ITEM_METER:
            activeMeterDestroy(item->object);
            break;
        case ITEM_SLIDER:
            activeSliderDestroy(item->object);
            break;
        case ITEM_OBJECT:
            activeObjectDestroy(item->object);
            break;
        }

        item = next;
    }

    free(themePage);
}

void themePageAddImage(ThemePage* themePage, void* object, ThemeTrigger trigger, ThemeTrigger visible)
{
    themePageAddLast(themePage, ITEM_IMAGE, object, trigger, visible, THEME_TRIGGER_NONE);
}

void themePageAddMeter(ThemePage* themePage, void* object, ThemeTrigger trigger, ThemeTrigger visible)
{
    themePageAddLast(themePage, ITEM_METER, object, trigger, visible, THEME_TRIGGER_NONE);
}

void themePageAddSlider(ThemePage* themePage, void* object, ThemeTrigger trigger, ThemeTrigger visible)
{
    themePageAddLast(themePage, ITEM_SLIDER, object, trigger, visible, THEME_TRIGGER_NONE);
}

void themePageAddText(ThemePage* themePage, void* object, ThemeTrigger trigger, ThemeTrigger visible)
{
    themePageAddLast(themePage, ITEM_TEXT, object, trigger, visible, THEME_TRIGGER_NONE);
}

void themePageAddButton(ThemePage* themePage, void* object, ThemeTrigger trigger, ThemeTrigger visible, ThemeTrigger pressed)
{
    themePageAddLast(themePage, ITEM_BUTTON, object, trigger, visible, pressed);
}

void themePageAddDualButton(ThemePage* themePage, void* object, ThemeTrigger trigger, ThemeTrigger visible, ThemeTrigger pressed)
{
    themePageAddLast(themePage, ITEM_DUALBUTTON, object, trigger, visible, pressed);
}

void themePageAddToggleButton(ThemePage* themePage, void* object, ThemeTrigger trigger, ThemeTrigger visible, ThemeTrigger pressed)
{
    themePageAddLast(themePage, ITEM_TOGGLEBUTTON, object, trigger, visible, pressed);
}

void themePageAddObject(ThemePage* themePage, void* object, ThemeTrigger visible)
{
    themePageAddLast(themePage, ITEM_OBJECT, object, THEME_TRIGGER_NONE, visible, THEME_TRIGGER_NONE);
}

void themePageMouseMove(ThemePage* themePage, void*  dc, int x, int y)
{
    ThemeItem* item;

    if (themePage->btPressed) {
        for (item = themePage->itemList; item != NULL; item = item->next) {
            switch (item->type) {
            case ITEM_SLIDER:
                if (activeSliderMouseMove(item->object, x, y)) {
                    activeSliderDraw(item->object, dc);
                }
                break;
            }
        }
        return;
    }

    for (item = themePage->itemList; item != NULL; item = item->next) {
        switch (item->type) {
        case ITEM_IMAGE:
            break;
        case ITEM_METER:
            break;
        case ITEM_TEXT:
            break;
        case ITEM_BUTTON:
            if (activeButtonMouseMove(item->object, x, y)) {
                activeButtonDraw(item->object, dc);
            }
            break;
        case ITEM_DUALBUTTON:
            if (activeDualButtonMouseMove(item->object, x, y)) {
                activeDualButtonDraw(item->object, dc);
            }
            break;
        case ITEM_TOGGLEBUTTON:
            if (activeToggleButtonMouseMove(item->object, x, y)) {
                activeToggleButtonDraw(item->object, dc);
            }
            break;
        }
    }
}

void themePageMouseButtonDown(ThemePage* themePage, void*  dc, int x, int y)
{
    ThemeItem* item;

    themePageMouseButtonUp(themePage, dc, x, y);
    if (themePage == NULL) {
        return;
    }

    themePage->btPressed  = 1;

    for (item = themePage->itemList; item != NULL; item = item->next) {
        switch (item->type) {
        case ITEM_IMAGE:
            break;
        case ITEM_METER:
            break;
        case ITEM_SLIDER:
            if (activeSliderDown(item->object, x, y)) {
                themePage->activeItem = item;
                activeSliderDraw(item->object, dc);
            }
            break;
        case ITEM_TEXT:
            break;
        case ITEM_BUTTON:
            if (activeButtonDown(item->object, x, y)) {
                themePage->activeItem = item;
                activeButtonDraw(item->object, dc);
            }
            break;
        case ITEM_DUALBUTTON:
            if (activeDualButtonDown(item->object, x, y)) {
                themePage->activeItem = item;
                activeDualButtonDraw(item->object, dc);
            }
            break;
        case ITEM_TOGGLEBUTTON:
            if (activeToggleButtonDown(item->object, x, y)) {
                themePage->activeItem = item;
                activeToggleButtonDraw(item->object, dc);
            }
            break;
        }
    }
}

void themePageMouseButtonUp(ThemePage* themePage, void*  dc, int x, int y)
{
    themePage->btPressed = 0;

    if (themePage == NULL) {
        return;
    }

    if (!themePage->activeItem) {
        return;
    }

    switch (themePage->activeItem->type) {
    case ITEM_IMAGE:
        break;
    case ITEM_METER:
        break;
    case ITEM_SLIDER:
        activeSliderUp(themePage->activeItem->object, x, y);
        activeSliderDraw(themePage->activeItem->object, dc);
        break;
    case ITEM_TEXT:
        break;
    case ITEM_BUTTON:
        activeButtonUp(themePage->activeItem->object, x, y);
        activeButtonDraw(themePage->activeItem->object, dc);
        break;
    case ITEM_DUALBUTTON:
        activeDualButtonUp(themePage->activeItem->object, x, y);
        activeDualButtonDraw(themePage->activeItem->object,  dc);
        break;
    case ITEM_TOGGLEBUTTON:
        activeToggleButtonUp(themePage->activeItem->object, x, y);
        activeToggleButtonDraw(themePage->activeItem->object, dc);
        break;
    }
    themePage->activeItem = NULL;
}

void themePageDraw(ThemePage* themePage, void*  dc)
{
    ThemeItem* item;

    if (themePage == NULL) {
        return;
    }

    for (item = themePage->itemList; item != NULL; item = item->next) {
        switch (item->type) {
        case ITEM_IMAGE:
            activeImageDraw(item->object, dc);
            break;
        case ITEM_METER:
            activeMeterDraw(item->object, dc);
            break;
        case ITEM_SLIDER:
            activeSliderDraw(item->object, dc);
            break;
        case ITEM_TEXT:
            activeTextDraw(item->object, dc);
            break;
        case ITEM_BUTTON:
            activeButtonDraw(item->object, dc);
            break;
        case ITEM_DUALBUTTON:
            activeDualButtonDraw(item->object, dc);
            break;
        case ITEM_TOGGLEBUTTON:
            activeToggleButtonDraw(item->object, dc);
            break;
        }
    }
}

void themePageActivate(ThemePage* themePage, void* window)
{
    ThemeItem* item;
    for (item = themePage->itemList; item != NULL; item = item->next) {
        if (item->type == ITEM_OBJECT) {
            activeObjectActivate(item->object, window);
        }
    }
}

void themePageUpdate(ThemePage* themePage, void* dc)
{
    ThemeItem* item;
    int redrawAll = 0;

    if (themePage == NULL) {
        return;
    }

    // Update visibility
    for (item = themePage->itemList; item != NULL; item = item->next) {
        int   visible = actionTypeToInt(item->visible);
        if (visible == -1) {
            continue;
        }

        switch (item->type) {
        case ITEM_IMAGE:
            redrawAll |= activeImageShow(item->object, visible);
            break;
        case ITEM_METER:
            redrawAll |= activeMeterShow(item->object, visible);
            break;
        case ITEM_SLIDER:
            redrawAll |= activeSliderShow(item->object, visible);
            break;
        case ITEM_TEXT:
            redrawAll |= activeTextShow(item->object, visible);
            break;
        case ITEM_BUTTON:
            redrawAll |= activeButtonShow(item->object, visible);
            break;
        case ITEM_DUALBUTTON:
            redrawAll |= activeDualButtonShow(item->object, visible);
            break;
        case ITEM_TOGGLEBUTTON:
            redrawAll |= activeToggleButtonShow(item->object, visible);
            break;
        case ITEM_OBJECT:
//            redrawAll |= activeObjectShow(item->object, visible);
            break;
        }
    }

    // Update items
    for (item = themePage->itemList; item != NULL; item = item->next) {
        int   pressed = actionTypeToInt(item->pressed);
        int   trigger = actionTypeToInt(item->trigger);
        char* str     = actionTypeToStr(item->trigger);
        int   redraw  = redrawAll;

        switch (item->type) {
        case ITEM_IMAGE:
            if (trigger != -1) redraw |= activeImageSetImage(item->object, trigger);
            if (redraw) activeImageDraw(item->object, dc);
            break;
        case ITEM_METER:
            if (trigger != -1) redraw |= activeMeterSetImage(item->object, trigger);
            if (redraw) activeMeterDraw(item->object, dc);
            break;
        case ITEM_SLIDER:
            if (trigger != -1) redraw |= activeSliderSetImage(item->object, trigger);
            if (redraw) activeSliderDraw(item->object, dc);
            break;
        case ITEM_TEXT:
            if (str != NULL) redraw |= activeTextSetText(item->object, str);
            if (redraw) activeTextDraw(item->object, dc);
            break;
        case ITEM_BUTTON:
            if (pressed != -1) redraw |= activeButtonForcePushed(item->object, pressed);
            if (redraw) activeButtonDraw(item->object, dc);
            break;
        case ITEM_DUALBUTTON:
            if (pressed != -1) redraw |= activeDualButtonForcePushed(item->object, pressed);
            if (redraw) activeDualButtonDraw(item->object, dc);
            break;
        case ITEM_TOGGLEBUTTON:
            if (pressed != -1) redraw |= activeToggleButtonForcePushed(item->object, pressed);
            if (trigger != -1) redraw |= activeToggleButtonSetToggled(item->object, trigger);
            if (redraw) activeButtonDraw(item->object, dc);
            break;
        }
    }
}

///////////////////////////////////////////////////////////////

Theme* themeCreate(const char* name) 
{
    Theme* theme = malloc(sizeof(Theme));
    strcpy(theme->name, name);
    theme->reference = NULL;
    theme->currentPage = 0;
    theme->pageCount = 0;
    theme->pages[0] = NULL;
    return theme;
}

void themeDestroy(Theme* theme)
{
    while (theme->pageCount--) {
        themePageDestroy(theme->pages[theme->pageCount]);
    }
    free(theme);
}

void themeAddPage(Theme* theme, ThemePage* themePage) 
{
    if (theme->pageCount == THEME_MAX_PAGES) {
        return;
    }

    theme->pages[theme->pageCount++] = themePage;
}

ThemePage* themeGetCurrentPage(Theme* theme)
{
    return theme->pages[theme->currentPage];
}

int themeGetCurrentPageIndex(Theme* theme)
{
    return theme->currentPage;
}

int themeGetPageCount(Theme* theme)
{
    return theme->pageCount;
}

void themeSetPageFromHash(Theme* theme, unsigned long hash)
{
    int oldPage = theme->currentPage;
    int i;
    for (i = 0; i < theme->pageCount; i++) {
        if (themeGetNameHash(theme->pages[i]->name) == hash) {
            theme->currentPage = i;
        }
    }
    if (oldPage != theme->currentPage) {
        themePageActivate(theme->pages[oldPage], NULL);
    }
    archThemeUpdate(theme);
}

char* themeGetPageName(Theme* theme, int index)
{
    return theme->pages[index]->name;
}

char** themeGetPageNames(Theme* theme)
{
    static char* names[256];
    int i = 0;

    for (i = 0; i < theme->pageCount; i++) {
        names[i] = theme->pages[i]->name;
    }
    names[i] = NULL;

    return names;
}

ThemePage* themeGetPage(Theme* theme, int index)
{
    if (index < theme->pageCount) {
        theme->pages[index];
    }
    return NULL;
}

UInt32 themeGetNameHash(const char* name)
{
    UInt32 tag = 0;
    UInt32 mod = 1;

    while (*name) {
        mod *= 19219;
        tag += mod * *name++;
    }

    return tag;
}

////////////////////////

ThemeCollection* themeCollectionCreate() 
{
    ThemeCollection* tc = (ThemeCollection*)calloc(1, sizeof(ThemeCollection));
    return tc;
}

void themeCollectionDestroy(ThemeCollection* tc) 
{
    int i;

    if (tc->little)          themeDestroy(tc->little);
    if (tc->normal)          themeDestroy(tc->normal);
    if (tc->fullscreen)      themeDestroy(tc->fullscreen);
    if (tc->smallfullscreen) themeDestroy(tc->smallfullscreen);

    for (i = 0; i < THEME_MAX_WINDOWS; i++) {
        if (tc->theme[i] != NULL) {
            themeDestroy(tc->theme[i]);
            tc->theme[i] = NULL;
        }
    }
}


void themeCollectionAddWindow(ThemeCollection* tc, Theme* theme)
{
    int i;

    for (i = 0; i < THEME_MAX_WINDOWS; i++) {
        if (tc->theme[i] == NULL) {
            tc->theme[i] = theme;
        }
    }
}

void themeCollectionOpenWindow(ThemeCollection* tc, unsigned long hash)
{
    Theme* theme = NULL;

    int i;
    for (i = 0; i < THEME_MAX_WINDOWS; i++) {
        if (tc->theme[i] && themeGetNameHash(tc->theme[i]->name) == hash) {
            theme = tc->theme[i];
            break;
        }
    }
    if (theme == NULL || tc->theme[i]->reference != NULL) {
        return;
    }

    tc->theme[i]->reference = archWindowCreate(tc->theme[i], WH_NORMAL);
}

void themeCollectionOpenKbdWindow(ThemeCollection* tc, unsigned long hash)
{
    Theme* theme = NULL;

    int i;
    for (i = 0; i < THEME_MAX_WINDOWS; i++) {
        if (tc->theme[i] && themeGetNameHash(tc->theme[i]->name) == hash) {
            theme = tc->theme[i];
            break;
        }
    }
    if (theme == NULL || tc->theme[i]->reference != NULL) {
        return;
    }

    tc->theme[i]->reference = archWindowCreate(tc->theme[i], WH_KBDCONFIG);
}
