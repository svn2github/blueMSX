/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Theme/Theme.h,v $
**
** $Revision: 1.8 $
**
** $Date: 2005-01-13 06:16:02 $
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
typedef struct ThemePage ThemePage;
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

struct ThemePage {
// public:
    char name[64];
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

#define THEME_MAX_PAGES 64

struct Theme {
    int currentPage;
    int pageCount;
    ThemePage* pages[THEME_MAX_PAGES];
};

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
                           unsigned long menuColor,
                           unsigned long menuFocusColor,
                           unsigned long menuTextColor,
                           int        clipPointCount,
                           ClipPoint* clipPointList);

Theme*     themeCreate();
void       themeDestroy(Theme* theme);
void       themeAddPage(Theme* theme, ThemePage* page);
ThemePage* themeGetCurrentPage(Theme* theme);
int        themeGetCurrentPageIndex(Theme* theme);
int        themeGetPageCount(Theme* theme);
void       themeSetPageFromHash(Theme* theme, unsigned long hash);
unsigned long themeGetNameHash(const char* name);


void themePageDestroy(ThemePage* theme);

void themePageAddImage(ThemePage* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible);

void themePageAddText(ThemePage* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible);

void themePageAddButton(ThemePage* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible, ThemeTrigger pressed);

void themePageAddDualButton(ThemePage* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible, ThemeTrigger pressed);

void themePageAddToggleButton(ThemePage* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible, ThemeTrigger pressed);

void themePageAddMeter(ThemePage* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible);

void themePageAddSlider(ThemePage* theme, void* object, ThemeTrigger trigger, ThemeTrigger visible);

void themePageAddObject(ThemePage* theme, void* object, ThemeTrigger visible);

void themePageActivate(ThemePage* theme, void* window);
void themePageUpdate(ThemePage* theme, void* dc);
void themePageDraw(ThemePage* theme, void* dc);
void themePageMouseMove(ThemePage* theme, void* dc, int x, int y);
void themePageMouseButtonUp(ThemePage* theme, void* dc, int x, int y);
void themePageMouseButtonDown(ThemePage* theme, void* dc, int x, int y);

#endif //WIN32_THEME_CLASSIC_H
