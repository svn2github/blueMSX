/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Theme/Theme.h,v $
**
** $Revision: 1.6 $
**
** $Date: 2005-01-10 16:07:11 $
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
#include "ThemeTriggers.h"

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

void themeAddToggleButton(Theme* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible);

void themeAddMeter(Theme* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible);

void themeAddSlider(Theme* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible);

void themeAddObject(Theme* theme, void* object, ThemeTrigger visible);

void themeActivate(Theme* theme, void* window);
void themeUpdate(Theme* theme, void* dc);
void themeDraw(Theme* theme, void* dc);
void themeMouseMove(Theme* theme, void* dc, int x, int y);
void themeMouseButtonUp(Theme* theme, void* dc, int x, int y);
void themeMouseButtonDown(Theme* theme, void* dc, int x, int y);

#endif //WIN32_THEME_CLASSIC_H
