/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Theme/Theme.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2004-12-06 08:04:33 $
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

typedef enum { ITEM_IMAGE, ITEM_TEXT, ITEM_BUTTON, ITEM_DUALBUTTON, ITEM_METER, ITEM_SLIDER } ItemType;

struct ThemeItem {
    ThemeItem*   next;
    ItemType     type;
    void*        object;
    ThemeTrigger trigger;
    ThemeTrigger visible;
};

#define TEST(a, x) ((a & THEME_TRIGGER_NOT) ? !(x) : (x))

static int actionTypeToInt(ThemeTrigger actionType, StatusInfo* statusInfo)
{
    int idx = -1;
    switch (actionType & THEME_TRIGGER_MASK) {
    case THEME_TRIGGER_IMG_DISKA:   idx = TEST(actionType, statusInfo->ledDiskA); break;
    case THEME_TRIGGER_IMG_DISKB:   idx = TEST(actionType, statusInfo->ledDiskB); break;
    case THEME_TRIGGER_IMG_CAS:     idx = TEST(actionType, statusInfo->ledCas); break;
    case THEME_TRIGGER_IMG_AS:      idx = TEST(actionType, statusInfo->ledAudioSwitch); break;
    case THEME_TRIGGER_IMG_TRACE:   idx = TEST(actionType, statusInfo->cpuTraceEnable); break;
    case THEME_TRIGGER_IMG_FS:      idx = TEST(actionType, statusInfo->ledFrontSwitch); break;
    case THEME_TRIGGER_IMG_PS:      idx = TEST(actionType, statusInfo->ledPauseSwitch); break;
    case THEME_TRIGGER_IMG_CAPS:    idx = TEST(actionType, statusInfo->ledCaps); break;
    case THEME_TRIGGER_IMG_KANA:    idx = TEST(actionType, statusInfo->ledKana); break;
    case THEME_TRIGGER_IMG_TURBOR:  idx = TEST(actionType, statusInfo->ledTurboR); break;
    case THEME_TRIGGER_IMG_PAUSE:   idx = TEST(actionType, statusInfo->ledPause); break;
    case THEME_TRIGGER_IMG_REC:     idx = TEST(actionType, statusInfo->ledRecord); break;
    case THEME_TRIGGER_IMG_STOPPED: idx = TEST(actionType, statusInfo->emuStopped); break;
    case THEME_TRIGGER_IMG_PAUSED:  idx = TEST(actionType, statusInfo->emuPaused); break;
    case THEME_TRIGGER_IMG_RUNNING: idx = TEST(actionType, statusInfo->emuRunning); break;
    case THEME_TRIGGER_IMG_KBD:     idx = TEST(actionType, statusInfo->audioKbd); break;
    case THEME_TRIGGER_IMG_MOON:    idx = TEST(actionType, statusInfo->audioMoonsound); break;
    case THEME_TRIGGER_IMG_MSXA:    idx = TEST(actionType, statusInfo->audioMsxAudio); break;
    case THEME_TRIGGER_IMG_MSXM:    idx = TEST(actionType, statusInfo->audioMsxMusic); break;
    case THEME_TRIGGER_IMG_PSG:     idx = TEST(actionType, statusInfo->audioPsg); break;
    case THEME_TRIGGER_IMG_SCC:     idx = TEST(actionType, statusInfo->audioScc); break;
    case THEME_TRIGGER_IMG_PCM:     idx = TEST(actionType, statusInfo->audioPcm); break;
    case THEME_TRIGGER_IMG_MASTER:  idx = TEST(actionType, statusInfo->audioMaster); break;
    case THEME_TRIGGER_IMG_STEREO:  idx = TEST(actionType, statusInfo->audioStereo); break;
    case THEME_TRIGGER_IMG_L_KBD:    idx = statusInfo->volKbdLeft; break;
    case THEME_TRIGGER_IMG_R_KBD:    idx = statusInfo->volKbdRight; break;
    case THEME_TRIGGER_IMG_L_MOON:   idx = statusInfo->volMoonsoundLeft; break;
    case THEME_TRIGGER_IMG_R_MOON:   idx = statusInfo->volMoonsoundRight; break;
    case THEME_TRIGGER_IMG_L_MSXA:   idx = statusInfo->volMsxAudioLeft; break;
    case THEME_TRIGGER_IMG_R_MSXA:   idx = statusInfo->volMsxAudioRight; break;
    case THEME_TRIGGER_IMG_L_MSXM:   idx = statusInfo->volMsxMusicLeft; break;
    case THEME_TRIGGER_IMG_R_MSXM:   idx = statusInfo->volMsxMusicRight; break;
    case THEME_TRIGGER_IMG_L_PSG:    idx = statusInfo->volPsgLeft; break;
    case THEME_TRIGGER_IMG_R_PSG:    idx = statusInfo->volPsgRight; break;
    case THEME_TRIGGER_IMG_L_SCC:    idx = statusInfo->volSccLeft; break;
    case THEME_TRIGGER_IMG_R_SCC:    idx = statusInfo->volSccRight; break;
    case THEME_TRIGGER_IMG_L_PCM:    idx = statusInfo->volPcmLeft; break;
    case THEME_TRIGGER_IMG_R_PCM:    idx = statusInfo->volPcmRight; break;
    case THEME_TRIGGER_IMG_L_MASTER: idx = statusInfo->volMasterLeft; break;
    case THEME_TRIGGER_IMG_R_MASTER: idx = statusInfo->volMasterRight; break;

    case THEME_TRIGGER_LEVEL_MASTER:    idx = statusInfo->levelMaster; break;
    case THEME_TRIGGER_LEVEL_PSG:       idx = statusInfo->levelPsg; break;
    case THEME_TRIGGER_LEVEL_PCM:       idx = statusInfo->levelPcm; break;
    case THEME_TRIGGER_LEVEL_SCC:       idx = statusInfo->levelScc; break;
    case THEME_TRIGGER_LEVEL_KEYBOARD:  idx = statusInfo->levelKeyboard; break;
    case THEME_TRIGGER_LEVEL_MSXMUSIC:  idx = statusInfo->levelMsxMusic; break;
    case THEME_TRIGGER_LEVEL_MSXAUDIO:  idx = statusInfo->levelMsxAudio; break;
    case THEME_TRIGGER_LEVEL_MOONSOUND: idx = statusInfo->levelMoonsound; break;
    case THEME_TRIGGER_PAN_PSG:         idx = statusInfo->panPsg; break;
    case THEME_TRIGGER_PAN_PCM:         idx = statusInfo->panPcm; break;
    case THEME_TRIGGER_PAN_SCC:         idx = statusInfo->panScc; break;
    case THEME_TRIGGER_PAN_KEYBOARD:    idx = statusInfo->panKeyboard; break;
    case THEME_TRIGGER_PAN_MSXMUSIC:    idx = statusInfo->panMsxMusic; break;
    case THEME_TRIGGER_PAN_MSXAUDIO:    idx = statusInfo->panMsxAudio; break;
    case THEME_TRIGGER_PAN_MOONSOUND:   idx = statusInfo->panMoonsound; break;

    case THEME_TRIGGER_EMUSPEED:        idx = statusInfo->emuSpeed; break;

    case THEME_TRIGGER_RENSHA:          idx = statusInfo->renshaLevel; break;
    case THEME_TRIGGER_RENSHALED:       idx = statusInfo->renshaLed; break;

    case THEME_TRIGGER_IMG_PORT1_EN:    idx = TEST(actionType, statusInfo->port1None ^ 0xffff); break;
    case THEME_TRIGGER_IMG_PORT1_NONE:  idx = TEST(actionType, statusInfo->port1None); break;
    case THEME_TRIGGER_IMG_PORT1_MOUSE: idx = TEST(actionType, statusInfo->port1Mouse); break;
    case THEME_TRIGGER_IMG_PORT1_NUM:   idx = TEST(actionType, statusInfo->port1Num); break;
    case THEME_TRIGGER_IMG_PORT1_KBD:   idx = TEST(actionType, statusInfo->port1Kbd); break;
    case THEME_TRIGGER_IMG_PORT1_JOY:   idx = TEST(actionType, statusInfo->port1Joy); break;
    case THEME_TRIGGER_IMG_PORT2_EN:    idx = TEST(actionType, statusInfo->port2None ^ 0xffff); break;
    case THEME_TRIGGER_IMG_PORT2_NONE:  idx = TEST(actionType, statusInfo->port2None); break;
    case THEME_TRIGGER_IMG_PORT2_MOUSE: idx = TEST(actionType, statusInfo->port2Mouse); break;
    case THEME_TRIGGER_IMG_PORT2_NUM:   idx = TEST(actionType, statusInfo->port2Num); break;
    case THEME_TRIGGER_IMG_PORT2_KBD:   idx = TEST(actionType, statusInfo->port2Kbd); break;
    case THEME_TRIGGER_IMG_PORT2_JOY:   idx = TEST(actionType, statusInfo->port2Joy); break;
    case THEME_TRIGGER_IMG_M_MOON:      idx = TEST(actionType, statusInfo->machineMoonsound); break;
    case THEME_TRIGGER_IMG_M_MSXM:      idx = TEST(actionType, statusInfo->machineMsxMusic); break;
    case THEME_TRIGGER_IMG_M_MSXA:      idx = TEST(actionType, statusInfo->machineMsxAudio); break;
    case THEME_TRIGGER_IMG_M_SCC:       idx = TEST(actionType, statusInfo->machineScc); break;
    case THEME_TRIGGER_IMG_M_ROM:       idx = TEST(actionType, statusInfo->machineRom); break;
    case THEME_TRIGGER_IMG_M_MEGAROM:   idx = TEST(actionType, statusInfo->machineMegaRom); break;
    case THEME_TRIGGER_IMG_M_MEGARAM:   idx = TEST(actionType, statusInfo->machineMegaRam); break;
    case THEME_TRIGGER_IMG_M_FMPAC:     idx = TEST(actionType, statusInfo->machineFmPac); break;
    case THEME_TRIGGER_IMG_DISK_RI:     idx = TEST(actionType, statusInfo->confDiskRI); break;
    case THEME_TRIGGER_IMG_CART_RI:     idx = TEST(actionType, statusInfo->confCartRI); break;
    case THEME_TRIGGER_IMG_CAS_RO:      idx = TEST(actionType, statusInfo->confCasRO); break;
    case THEME_TRIGGER_IMG_SCANLINES:   idx = TEST(actionType, statusInfo->videoScanlines); break;
    case THEME_TRIGGER_IMG_HSTRETCH:    idx = TEST(actionType, statusInfo->videoHstretch); break;
    case THEME_TRIGGER_IMG_VSTRETCH:    idx = TEST(actionType, statusInfo->videoVstretch); break;
    }
    return idx;
}

static char* actionTypeToStr(ThemeTrigger actionType, StatusInfo* statusInfo)
{
    char* str = NULL;

    switch (actionType & THEME_TRIGGER_MASK) {
    case THEME_TRIGGER_TEXT_FREQ:   str = statusInfo->emuFrequency; break;
    case THEME_TRIGGER_TEXT_CPU:    str = statusInfo->cpuString; break;
    case THEME_TRIGGER_TEXT_FPS:    str = statusInfo->fpsString; break;
    case THEME_TRIGGER_TEXT_RAM:    str = statusInfo->memoryRam; break;
    case THEME_TRIGGER_TEXT_VRAM:   str = statusInfo->memoryVram; break;
    case THEME_TRIGGER_TEXT_SCREEN: str = statusInfo->screenMode; break;
    case THEME_TRIGGER_TEXT_SCREENSHORT: str = statusInfo->screenModeShort; break;
    case THEME_TRIGGER_TEXT_ROMMAPPER1: str = statusInfo->romMapper1; break;
    case THEME_TRIGGER_TEXT_ROMMAPPER2: str = statusInfo->romMapper2; break;
    case THEME_TRIGGER_TEXT_ROMMAPPER1SHORT: str = statusInfo->romMapper1Short; break;
    case THEME_TRIGGER_TEXT_ROMMAPPER2SHORT: str = statusInfo->romMapper2Short; break;
    case THEME_TRIGGER_TEXT_RUNNAME:str = statusInfo->runningName; break;
    case THEME_TRIGGER_TEXT_MACHINENAME: str = statusInfo->machineName; break;
    case THEME_TRIGGER_TEXT_SCANLINESPCT: str = statusInfo->videoScanlinePct; break;
    case THEME_TRIGGER_TEXT_VERSION: str = statusInfo->version; break;
    case THEME_TRIGGER_TEXT_BUILDNUMBER: str = statusInfo->buildNumber; break;
    case THEME_TRIGGER_TEXT_BUILDANDVER: str = statusInfo->buildAndVersion; break;
    }
    return str;
}

static void themeAddLast(Theme* theme, ItemType itemType, void* object, ThemeTrigger trigger, ThemeTrigger visible)
{
    ThemeItem* item = malloc(sizeof(ThemeItem));
    ThemeItem** pItem = &theme->itemList;

    while (*pItem != NULL) {
        pItem = &((*pItem)->next);
    }

    *pItem = item;
    
    item->type = itemType;
    item->object = object;
    item->trigger = trigger;
    item->visible = visible;
    item->next = NULL;
}

Theme* themeCreate(int width,
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
    Theme* theme = calloc(1, sizeof(Theme));

    theme->width           = width;
    theme->height          = height;
    theme->emuWinX         = emuPosX;
    theme->emuWinY         = emuPosY;
    theme->emuWinW         = emuWidth;
    theme->emuWinH         = emuHeight;
    theme->menu.x          = menuPosX;
    theme->menu.y          = menuPosY;
    theme->menu.width      = menuWidth;
    theme->menu.color      = menuColor;
    theme->menu.focusColor = menuFocusColor;
    theme->menu.textColor  = menuTextColor;
    theme->clipPoint.count = clipPointCount;

    if (clipPointCount > 0) {
        int size = clipPointCount * sizeof(ClipPoint);
        theme->clipPoint.list = malloc(size);
        memcpy(theme->clipPoint.list, clipPointList, size);
    }

    return theme;
}

void themeDestroy(Theme* theme)
{
    ThemeItem* item;
    
    if (theme == NULL) {
        return;
    }

    item = theme->itemList;

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
        case ITEM_METER:
            activeMeterDestroy(item->object);
            break;
        case ITEM_SLIDER:
            activeSliderDestroy(item->object);
            break;
        }

        item = next;
    }

    free(theme);
}

void themeAddImage(Theme* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible)
{
    themeAddLast(theme, ITEM_IMAGE, object, trigger, visible);
}

void themeAddMeter(Theme* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible)
{
    themeAddLast(theme, ITEM_METER, object, trigger, visible);
}

void themeAddSlider(Theme* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible)
{
    themeAddLast(theme, ITEM_SLIDER, object, trigger, visible);
}

void themeAddText(Theme* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible)
{
    themeAddLast(theme, ITEM_TEXT, object, trigger, visible);
}

void themeAddButton(Theme* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible)
{
    themeAddLast(theme, ITEM_BUTTON, object, trigger, visible);
}

void themeAddDualButton(Theme* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible)
{
    themeAddLast(theme, ITEM_DUALBUTTON, object, trigger, visible);
}

void themeMouseMove(Theme* theme, void*  dc, int x, int y)
{
    ThemeItem* item;

    if (theme->btPressed) {
        for (item = theme->itemList; item != NULL; item = item->next) {
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

    for (item = theme->itemList; item != NULL; item = item->next) {
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
        }
    }
}

void themeMouseButtonDown(Theme* theme, void*  dc, int x, int y)
{
    ThemeItem* item;

    themeMouseButtonUp(theme, dc, x, y);
    if (theme == NULL) {
        return;
    }

    theme->btPressed  = 1;
    theme->activeItem = NULL;

    for (item = theme->itemList; item != NULL; item = item->next) {
        switch (item->type) {
        case ITEM_IMAGE:
            break;
        case ITEM_METER:
            break;
        case ITEM_SLIDER:
            if (activeSliderDown(item->object, x, y)) {
                theme->activeItem = item;
                activeSliderDraw(item->object, dc);
                return;
            }
            break;
        case ITEM_TEXT:
            break;
        case ITEM_BUTTON:
            if (activeButtonDown(item->object, x, y)) {
                theme->activeItem = item;
                activeButtonDraw(item->object, dc);
                return;
            }
            break;
        case ITEM_DUALBUTTON:
            if (activeDualButtonDown(item->object, x, y)) {
                theme->activeItem = item;
                activeDualButtonDraw(item->object, dc);
                return;
            }
            break;
        }
    }
}

void themeMouseButtonUp(Theme* theme, void*  dc, int x, int y)
{
    theme->btPressed = 0;

    if (theme == NULL) {
        return;
    }

    if (!theme->activeItem) {
        return;
    }

    switch (theme->activeItem->type) {
    case ITEM_IMAGE:
        break;
    case ITEM_METER:
        break;
    case ITEM_SLIDER:
        activeSliderUp(theme->activeItem->object, x, y);
        activeSliderDraw(theme->activeItem->object, dc);
        break;
    case ITEM_TEXT:
        break;
    case ITEM_BUTTON:
        activeButtonUp(theme->activeItem->object, x, y);
        activeButtonDraw(theme->activeItem->object, dc);
        break;
    case ITEM_DUALBUTTON:
        activeDualButtonUp(theme->activeItem->object, x, y);
        activeDualButtonDraw(theme->activeItem->object,  dc);
        break;
    }
}

void themeDraw(Theme* theme, void*  dc)
{
    ThemeItem* item;

    if (theme == NULL) {
        return;
    }

    for (item = theme->itemList; item != NULL; item = item->next) {
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
        }
    }
}

void themeUpdate(Theme* theme, void*  dc, StatusInfo* statusInfo)
{
    ThemeItem* item;
    int redraw = 0;

    if (theme == NULL) {
        return;
    }

    // Update visibility

    for (item = theme->itemList; item != NULL; item = item->next) {
        int   visible = actionTypeToInt(item->visible, statusInfo);

        if (visible == -1) {
            continue;
        }

        switch (item->type) {
        case ITEM_IMAGE:
            redraw |= activeImageShow(item->object, visible);
            break;
        case ITEM_METER:
            redraw |= activeMeterShow(item->object, visible);
            break;
        case ITEM_SLIDER:
            redraw |= activeSliderShow(item->object, visible);
            break;
        case ITEM_TEXT:
            redraw |= activeTextShow(item->object, visible);
            break;
        case ITEM_BUTTON:
            redraw |= activeButtonShow(item->object, visible);
            break;
        case ITEM_DUALBUTTON:
            redraw |= activeDualButtonShow(item->object, visible);
            break;
        }
    }

    // Update items

    for (item = theme->itemList; item != NULL; item = item->next) {
        int   idx = actionTypeToInt(item->trigger, statusInfo);
        char* str = actionTypeToStr(item->trigger, statusInfo);

        switch (item->type) {
        case ITEM_IMAGE:
            if (idx != -1) redraw |= activeImageSetImage(item->object, idx);
            if (redraw) activeImageDraw(item->object, dc);
            break;
        case ITEM_METER:
            if (idx != -1) redraw |= activeMeterSetImage(item->object, idx);
            if (redraw) activeMeterDraw(item->object, dc);
            break;
        case ITEM_SLIDER:
            if (idx != -1) redraw |= activeSliderSetImage(item->object, idx);
            if (redraw) activeSliderDraw(item->object, dc);
            break;
        case ITEM_TEXT:
            if (str != NULL) redraw |= activeTextSetText(item->object, str);
            if (redraw) activeTextDraw(item->object, dc);
            break;
        case ITEM_BUTTON:
            if (idx != -1) redraw |= activeButtonEnable(item->object, idx);
            if (redraw) activeButtonDraw(item->object, dc);
            break;
        case ITEM_DUALBUTTON:
            if (idx != -1) redraw |= activeDualButtonEnable(item->object, idx);
            if (redraw) activeDualButtonDraw(item->object, dc);
            break;
        }
    }
}


