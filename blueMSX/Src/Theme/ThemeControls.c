/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Theme/ThemeControls.c,v $
**
** $Revision: 1.13 $
**
** $Date: 2005-07-23 06:10:50 $
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
#include "ThemeControls.h"
#include "ArchBitmap.h"
#include "ArchNotifications.h"
#include "ArchText.h"
#include "MsxTypes.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct ActiveImage {
    ArchBitmap* bitmap;
    int width;
    int height;
    int count;
    int index;
    int show;
    int x;
    int y;
    int cols;
};

ActiveImage* activeImageCreate(int x, int y, int cols, ArchBitmap* bitmap, int count)
{
    ActiveImage* activeImage = malloc(sizeof(ActiveImage));

    activeImage->bitmap  = bitmap;
    activeImage->x       = x;
    activeImage->y       = y;
    activeImage->cols    = cols;
    activeImage->count   = count;
    activeImage->index   = 0;
    activeImage->width   = archBitmapGetWidth(activeImage->bitmap) / (count < cols ? count : cols);
    activeImage->height  = archBitmapGetHeight(activeImage->bitmap) / (1 + (count - 1) / cols);
    activeImage->show    = 1;

    return activeImage;
}

void activeImageDestroy(ActiveImage* activeImage)
{
    archBitmapDestroy(activeImage->bitmap);
    free(activeImage);
}

void activeImageSetPosition(ActiveImage* activeImage, int x, int y)
{
    activeImage->x = x;
    activeImage->y = y;
}

int activeImageGetWidth(ActiveImage* activeImage)
{
    return activeImage->width;
}

int activeImageIsVisible(ActiveImage* activeImage)
{
    return activeImage->show;
}

int activeImageGetHeight(ActiveImage* activeImage)
{
    return activeImage->height;
}

int activeImageSetImage(ActiveImage* activeImage, int index)
{
    int indexModified;
    
    if (index < 0 || index >= activeImage->count) {
        return 0;
    }

    indexModified = index != activeImage->index;

    activeImage->index = index;

    return indexModified && activeImage->show;
}

int activeImageGetImage(ActiveImage* activeImage)
{
    return activeImage->index;
}

int activeImageShow(ActiveImage* activeImage, int show)
{
    if (!show == !activeImage->show) {
        return 0;
    }

    activeImage->show = show;

    return 1;
}

void activeImageDraw(ActiveImage* activeImage, void* dc)
{
    if (activeImage->show && activeImage->count > 0) {
        archBitmapDraw(activeImage->bitmap, dc, 
                     activeImage->x, activeImage->y, 
                     (activeImage->index % activeImage->cols) * activeImage->width, 
                     (activeImage->index / activeImage->cols) * activeImage->height, 
                     activeImage->width, activeImage->height);
    }
}

typedef enum { AB_NORMAL = 0, AB_HOOVER = 1, AB_PUSHED = 2 } ButtonState;

struct ActiveButton {
    ActiveImage* bitmap;
    int state;
    int pushed;
    int x;
    int y;
    UInt32 width;
    UInt32 height;
    ButtonEvent event;
    int arg1;
    int arg2;
};

ActiveButton* activeButtonCreate(int x, int y, int cols, ArchBitmap* bitmap, ButtonEvent event, int arg1, int arg2)
{
    ActiveButton* activeButton = malloc(sizeof(ActiveButton));

    activeButton->bitmap  = activeImageCreate(x, y, cols, bitmap, 3);
    activeButton->x       = x;
    activeButton->y       = y;
    activeButton->width   = activeImageGetWidth(activeButton->bitmap);
    activeButton->height  = activeImageGetHeight(activeButton->bitmap);
    activeButton->state   = AB_NORMAL;
    activeButton->pushed  = 0;
    activeButton->event   = event;
    activeButton->arg1    = arg1;
    activeButton->arg2    = arg2;

    return activeButton;
}

void activeButtonDestroy(ActiveButton* activeButton)
{
    activeImageDestroy(activeButton->bitmap);
    free(activeButton);
}

void activeButtonDraw(ActiveButton* activeButton, void* dc)
{
    activeImageDraw(activeButton->bitmap, dc);
}

static int activeButtonSetImage(ActiveButton* activeButton)
{
    int index = activeButton->state;
    int rv;

    if (activeButton->pushed) {
        index = AB_PUSHED;
    }

    rv = index != activeImageGetImage(activeButton->bitmap);

    activeImageSetImage(activeButton->bitmap, index);

    return rv;
}

int activeButtonForcePushed(ActiveButton* activeButton, int pushed)
{
    activeButton->pushed = pushed;
    return activeButtonSetImage(activeButton);
}

int activeButtonShow(ActiveButton* activeButton, int show)
{
    return activeImageShow(activeButton->bitmap, show);
}

int activeButtonMouseMove(ActiveButton* activeButton, int x, int y)
{
    int oldState = activeButton->state;

    if (!activeImageIsVisible(activeButton->bitmap)) {
        return 0;
    }

    if ((UInt32)(x - activeButton->x) < activeButton->width &&
        (UInt32)(y - activeButton->y) < activeButton->height)
    {
        activeButton->state = AB_HOOVER;
    }
    else {
        activeButton->state = AB_NORMAL;
    }

    return activeButtonSetImage(activeButton);
}

int activeButtonDown(ActiveButton* activeButton, int x, int y)
{
    int oldState = activeButton->state;

    if (!activeImageIsVisible(activeButton->bitmap)) {
        return 0;
    }

    if ((UInt32)(x - activeButton->x) < activeButton->width &&
        (UInt32)(y - activeButton->y) < activeButton->height)
    {
        if (activeButton->event != NULL && activeButton->arg2 == -1) {
            activeButton->event(activeButton->arg1, 1);
        }
        activeButton->state = AB_PUSHED;
    }
    else {
        activeButton->state = AB_NORMAL;
    }

    return activeButtonSetImage(activeButton) || activeButton->state != oldState;
}

int activeButtonUp(ActiveButton* activeButton, int x, int y)
{
    int oldState = activeButton->state;

    if (!activeImageIsVisible(activeButton->bitmap)) {
        return 0;
    }

    if ((UInt32)(x - activeButton->x) < activeButton->width &&
        (UInt32)(y - activeButton->y) < activeButton->height)
    {
        if (activeButton->event != NULL) {
            if (activeButton->arg2 == -1) {
                activeButton->event(activeButton->arg1, 0);
            }
            else {
                activeButton->event(activeButton->arg1, activeButton->arg2);
            }
        }
        activeButton->state = AB_HOOVER;
    }
    else {
        if (activeButton->arg2 == -1) {
            activeButton->event(activeButton->arg1, 0);
        }
        activeButton->state = AB_NORMAL;
    }

    return activeButtonSetImage(activeButton) || activeButton->state != oldState;
}


typedef enum { ADB_NORMAL = 0, ADB_HOOVER = 1, ADB_PUSHEDA = 2, ADB_PUSHEDB = 3 } DualButtonState;

struct ActiveDualButton {
    ActiveImage* bitmap;
    int state;
    int pushed;
    int x;
    int y;
    UInt32 width;
    UInt32 height;
    UInt32 widthB;
    UInt32 heightB;
    ButtonEvent eventA;
    int argA1;
    int argA2;
    ButtonEvent eventB;
    int argB1;
    int argB2;
    int vertical;
};

ActiveDualButton* activeDualButtonCreate(int x, int y, int cols, ArchBitmap* bitmap, 
                                          ButtonEvent eventA, int argA1, int argA2, 
                                          ButtonEvent eventB, int argB1, int argB2, int vertical)
{
    ActiveDualButton* activeButton = malloc(sizeof(ActiveDualButton));

    activeButton->bitmap   = activeImageCreate(x, y, cols, bitmap, 4);
    activeButton->x        = x;
    activeButton->y        = y;
    activeButton->width    = activeImageGetWidth(activeButton->bitmap);
    activeButton->height   = activeImageGetHeight(activeButton->bitmap);
    activeButton->widthB   = activeButton->width / 3;
    activeButton->heightB  = activeButton->height / 3;
    activeButton->state    = ADB_NORMAL;
    activeButton->pushed   = 0;
    activeButton->eventA   = eventA;
    activeButton->argA1    = argA1;
    activeButton->argA2    = argA2;
    activeButton->eventB   = eventB;
    activeButton->argB1    = argB1;
    activeButton->argB2    = argB2;
    activeButton->vertical = vertical;

    return activeButton;
}

void activeDualButtonDestroy(ActiveDualButton* activeButton)
{
    activeImageDestroy(activeButton->bitmap);
    free(activeButton);
}

void activeDualButtonDraw(ActiveDualButton* activeButton, void* dc)
{
    activeImageDraw(activeButton->bitmap, dc);
}

static int activeDualButtonSetImage(ActiveDualButton* activeButton)
{
    int index = activeButton->state;
    int rv;

    if (activeButton->pushed) {
        index = AB_PUSHED;
    }

    rv = index != activeImageGetImage(activeButton->bitmap);

    activeImageSetImage(activeButton->bitmap, index);

    return rv;
}

int activeDualButtonForcePushed(ActiveDualButton* activeButton, int pushed)
{
    activeButton->pushed = pushed;
    return activeDualButtonSetImage(activeButton);
}

int activeDualButtonShow(ActiveDualButton* activeButton, int show)
{
    return activeImageShow(activeButton->bitmap, show);
}

int activeDualButtonMouseMove(ActiveDualButton* activeButton, int x, int y)
{
    int oldState = activeButton->state;

    if (!activeImageIsVisible(activeButton->bitmap)) {
        return 0;
    }

    if ((UInt32)(x - activeButton->x) < activeButton->width &&
        (UInt32)(y - activeButton->y) < activeButton->height)
    {
        activeButton->state = ADB_HOOVER;
    }
    else {
        activeButton->state = ADB_NORMAL;
    }

    return activeDualButtonSetImage(activeButton);
}

int activeDualButtonDown(ActiveDualButton* activeButton, int x, int y)
{
    int oldState = activeButton->state;

    if (!activeImageIsVisible(activeButton->bitmap)) {
        return 0;
    }

    if ((UInt32)(x - activeButton->x) < activeButton->width &&
        (UInt32)(y - activeButton->y) < activeButton->height)
    {
        if ((activeButton->vertical && (UInt32)(y - activeButton->y) < activeButton->height - activeButton->heightB) ||
            (!activeButton->vertical && (UInt32)(x - activeButton->x) < activeButton->width - activeButton->widthB))
        {
            activeButton->state = ADB_PUSHEDA;
        }
        else {
            activeButton->state = ADB_PUSHEDB;
        }
    }
    else {
        activeButton->state = ADB_NORMAL;
    }

    return activeDualButtonSetImage(activeButton) || activeButton->state != oldState;
}

int activeDualButtonUp(ActiveDualButton* activeButton, int x, int y)
{
    int oldState = activeButton->state;

    if (!activeImageIsVisible(activeButton->bitmap)) {
        return 0;
    }

    if ((UInt32)(x - activeButton->x) < activeButton->width &&
        (UInt32)(y - activeButton->y) < activeButton->height)
    {
        if (activeButton->state == ADB_PUSHEDA && 
            ((activeButton->vertical && (UInt32)(y - activeButton->y) < activeButton->height - activeButton->heightB) ||
             (!activeButton->vertical && (UInt32)(x - activeButton->x) < activeButton->width - activeButton->widthB)))
        {
            if (activeButton->eventA != NULL) {
                activeButton->eventA(activeButton->argA1, activeButton->argA2);
            }
        }
        else if (activeButton->state == ADB_PUSHEDB && 
            ((activeButton->vertical && (UInt32)(y - activeButton->y) >= activeButton->height - activeButton->heightB) ||
             (!activeButton->vertical && (UInt32)(x - activeButton->x) >= activeButton->width - activeButton->widthB)))
        {
            if (activeButton->eventB != NULL) {
                activeButton->eventB(activeButton->argB1, activeButton->argB2);
            }
        }

        activeButton->state = ADB_HOOVER;
    }
    else {
        activeButton->state = ADB_NORMAL;
    }

    return activeDualButtonSetImage(activeButton) || activeButton->state != oldState;
}



typedef enum { ATB_NORMAL = 0, ATB_HOOVER = 1, ATB_PUSHED = 2 } ToggleButtonState;

struct ActiveToggleButton {
    ActiveImage* bitmap;
    int state;
    int pushed;
    int toggled;
    int x;
    int y;
    UInt32 width;
    UInt32 height;
    ButtonEvent event;
    int arg1;
    int arg2;
};

ActiveToggleButton* activeToggleButtonCreate(int x, int y, int cols, ArchBitmap* bitmap, ButtonEvent event, int arg1, int arg2)
{
    ActiveToggleButton* activeButton = malloc(sizeof(ActiveToggleButton));

    activeButton->bitmap  = activeImageCreate(x, y, cols, bitmap, 6);
    activeButton->x       = x;
    activeButton->y       = y;
    activeButton->width   = activeImageGetWidth(activeButton->bitmap);
    activeButton->height  = activeImageGetHeight(activeButton->bitmap);
    activeButton->state   = ATB_NORMAL;
    activeButton->pushed  = 0;
    activeButton->toggled = 0;
    activeButton->event   = event;
    activeButton->arg1    = arg1;
    activeButton->arg2    = arg2;

    return activeButton;
}

void activeToggleButtonDestroy(ActiveToggleButton* activeButton)
{
    activeImageDestroy(activeButton->bitmap);
    free(activeButton);
}

void activeToggleButtonDraw(ActiveToggleButton* activeButton, void* dc)
{
    activeImageDraw(activeButton->bitmap, dc);
}

static int activeToggleButtonSetImage(ActiveToggleButton* activeButton)
{
    int index = activeButton->state;
    int rv;

    if (activeButton->pushed) {
        index = ATB_PUSHED;
    }

    if (activeButton->toggled) {
        index += 3;
    }

    rv = index != activeImageGetImage(activeButton->bitmap);

    activeImageSetImage(activeButton->bitmap, index);

    return rv;
}

int activeToggleButtonForcePushed(ActiveToggleButton* activeButton, int pushed)
{
    activeButton->pushed = pushed;
    return activeToggleButtonSetImage(activeButton);
}

int activeToggleButtonSetToggled(ActiveToggleButton* activeButton, int toggled)
{
    activeButton->toggled = toggled;
    return activeToggleButtonSetImage(activeButton);
}

int activeToggleButtonShow(ActiveToggleButton* activeButton, int show)
{
    return activeImageShow(activeButton->bitmap, show);
}

int activeToggleButtonMouseMove(ActiveToggleButton* activeButton, int x, int y)
{
    int oldState = activeButton->state;

    if (!activeImageIsVisible(activeButton->bitmap)) {
        return 0;
    }

    if ((UInt32)(x - activeButton->x) < activeButton->width &&
        (UInt32)(y - activeButton->y) < activeButton->height)
    {
        activeButton->state = ATB_HOOVER;
    }
    else {
        activeButton->state = ATB_NORMAL;
    }

    return activeToggleButtonSetImage(activeButton);
}

int activeToggleButtonDown(ActiveToggleButton* activeButton, int x, int y)
{
    int oldState = activeButton->state;

    if (!activeImageIsVisible(activeButton->bitmap)) {
        return 0;
    }

    if ((UInt32)(x - activeButton->x) < activeButton->width &&
        (UInt32)(y - activeButton->y) < activeButton->height)
    {
        if (activeButton->event != NULL && activeButton->arg2 == -1) {
            activeButton->event(activeButton->arg1, 1);
        }
        activeButton->state = ATB_PUSHED;
    }
    else {
        activeButton->state = ATB_NORMAL;
    }

    return activeToggleButtonSetImage(activeButton) || activeButton->state != oldState;
}

int activeToggleButtonUp(ActiveToggleButton* activeButton, int x, int y)
{
    int oldState = activeButton->state;

    if (!activeImageIsVisible(activeButton->bitmap)) {
        return 0;
    }

    if ((UInt32)(x - activeButton->x) < activeButton->width &&
        (UInt32)(y - activeButton->y) < activeButton->height)
    {
        if (activeButton->event != NULL) {
            if (activeButton->arg2 == -1) {
                activeButton->event(activeButton->arg1, 0);
            }
            else {
                activeButton->event(activeButton->arg1, activeButton->arg2);
            }
        }
        activeButton->state = ATB_HOOVER;
    }
    else {
        if (activeButton->arg2 == -1) {
            activeButton->event(activeButton->arg1, 0);
        }
        activeButton->state = ATB_NORMAL;
    }

    return activeToggleButtonSetImage(activeButton) || activeButton->state != oldState;
}




typedef struct ActiveNativeText {
    ActiveImage* background;
    int width;
    int height;
    int x;
    int y;
    ArchText* archText;
    char string[128];
} ActiveNativeText;

ActiveNativeText* activeNativeTextCreate(int x, int y, ArchBitmap* bitmap, int color, int rightAligned)
{
    ActiveNativeText* activeText = malloc(sizeof(ActiveNativeText));

    activeText->background = activeImageCreate(x, y, 1, bitmap, 1);
    activeText->string[0]  = 0;
    activeText->width      = activeImageGetWidth(activeText->background);
    activeText->height     = activeImageGetHeight(activeText->background);
    activeText->x          = x + 2;
    activeText->y          = y - 1;

    activeText->archText = archTextCreate(activeText->height, color, rightAligned);

    return activeText;
}

void activeNativeTextDestroy(ActiveNativeText* activeText)
{
    activeImageDestroy(activeText->background);
    archTextDestroy(activeText->archText);
    free(activeText);
}

int activeNativeTextSetText(ActiveNativeText* activeText, const char* string)
{
    int diff = strcmp(string, activeText->string);
    strcpy(activeText->string, string);
    return diff;
}

void activeNativeTextDraw(ActiveNativeText* activeText, void* dc)
{
    activeImageDraw(activeText->background, dc);

    archTextDraw(activeText->archText, dc, activeText->x, activeText->y, 
                 activeText->width - 4, activeText->height, activeText->string); 
}

int activeNativeTextShow(ActiveNativeText* activeText, int show)
{
    return activeImageShow(activeText->background, show);
}

struct ActiveText{
    ActiveImage* font;
    int startChar;
    int charCount;
    char* string;
    int size;
    int x;
    int y;
    int width;
    int right;
    ActiveNativeText* nativeText;
};

ActiveText* activeTextCreate(int x, int y, int cols, ArchBitmap* bitmap, int startChar, int charCount, int width, int type, int color, int rightAligned)
{
    ActiveText* activeText = malloc(sizeof(ActiveText));

    if (type == 1) {
        activeText->nativeText = activeNativeTextCreate(x, y, bitmap, color, rightAligned);
        return activeText;
    }
    activeText->nativeText = NULL;
    activeText->font       = activeImageCreate(x, y, cols, bitmap, charCount);
    activeText->startChar  = startChar;
    activeText->charCount  = charCount;
    activeText->string     = calloc(1, width);
    activeText->size       = width;
    activeText->x          = x;
    activeText->y          = y;
    activeText->width      = activeImageGetWidth(activeText->font);
    activeText->right      = rightAligned;

    return activeText;
}

void activeTextDestroy(ActiveText* activeText)
{
    if (activeText->nativeText) {
        activeNativeTextDestroy(activeText->nativeText);
    }
    else {
        activeImageDestroy(activeText->font);
        free(activeText->string);
    }
    free(activeText);
}

int activeTextSetText(ActiveText* activeText, const char* string)
{
    char tmpString[128];
    int count;

    if (activeText->nativeText) {
        return activeNativeTextSetText(activeText->nativeText, string);
    }
    
    count = strlen(string);
    if (count > activeText->size) {
        count = activeText->size;
    }

    memset(tmpString, 32, activeText->size);
    if (activeText->right) {
        memcpy(tmpString + activeText->size - count, string, count);
    }
    else {
        memcpy(tmpString, string, count);
    }

    if (memcmp(activeText->string, tmpString, activeText->size)) {
        memcpy(activeText->string, tmpString, activeText->size);
        return 1;
    }
    return 0;
}

void activeTextDraw(ActiveText* activeText, void* dc)
{
    int i;

    if (activeText->nativeText) {
        activeNativeTextDraw(activeText->nativeText, dc);
        return;
    }

    for (i = 0; i < activeText->size; i++) {
        activeImageSetImage(activeText->font, ((UInt8)activeText->string[i]) - activeText->startChar);
        activeImageSetPosition(activeText->font, activeText->x + i * activeText->width, activeText->y);
        activeImageDraw(activeText->font, dc);
    }
}

int activeTextShow(ActiveText* activeText, int show)
{
    if (activeText->nativeText) {
        return activeNativeTextShow(activeText->nativeText, show);
    }

    return activeImageShow(activeText->font, show);
}

struct ActiveMeter {
    ActiveImage* bitmap;
    int x;
    int y;
    UInt32 width;
    UInt32 height;
    int index;
    int count;
};

ActiveMeter* activeMeterCreate(int x, int y, int cols, ArchBitmap* bitmap, int count)
{
    ActiveMeter* activeMeter = malloc(sizeof(ActiveMeter));

    activeMeter->bitmap = activeImageCreate(x, y, cols, bitmap, count);
    activeMeter->x      = x;
    activeMeter->y      = y;
    activeMeter->count  = count;
    activeMeter->index  = 0;
    activeMeter->width  = activeImageGetWidth(activeMeter->bitmap);
    activeMeter->height = activeImageGetHeight(activeMeter->bitmap);
    
    return activeMeter;
}

void activeMeterDestroy(ActiveMeter* activeMeter)
{
    activeImageDestroy(activeMeter->bitmap);
}

int activeMeterSetImage(ActiveMeter* activeMeter, int index)
{
    if (index > 0) {
        index = 1 + (activeMeter->count - 1) * index / 100;
    }
    if (index != activeMeter->index) {
        activeMeter->index = index;
        activeImageSetImage(activeMeter->bitmap, index);
    }
    return 1;
}

int activeMeterShow(ActiveMeter* activeMeter, int show)
{
    return activeImageShow(activeMeter->bitmap, show);
}

void activeMeterDraw(ActiveMeter* activeMeter, void* dc)
{
    activeImageDraw(activeMeter->bitmap, dc);
}

struct ActiveSlider {
    ActiveImage* bitmap;
    int x;
    int y;
    UInt32 width;
    UInt32 height;
    ButtonEvent upEvent;
    int arg1;
    int arg2;
    SliderEvent event;
    int index;
    int count;
    AsDirection ctrl;
    int sens;
    int downX;
    int downY;
    int downI;
};

ActiveSlider* activeSliderCreate(int x, int y, int cols, ArchBitmap* bitmap, SliderEvent event, int count,
                                 AsDirection direction, int sensitivity,
                                 ButtonEvent upEvent, int arg1, int arg2)
{
    ActiveSlider* activeSlider = malloc(sizeof(ActiveSlider));

    activeSlider->bitmap  = activeImageCreate(x, y, cols, bitmap, count);
    activeSlider->x       = x;
    activeSlider->y       = y;
    activeSlider->width   = activeImageGetWidth(activeSlider->bitmap);
    activeSlider->height  = activeImageGetHeight(activeSlider->bitmap);
    activeSlider->upEvent = upEvent;
    activeSlider->event   = event;
    activeSlider->arg1    = arg1;
    activeSlider->arg2    = arg2;
    activeSlider->count   = count;
    activeSlider->index   = 0;
    activeSlider->downX   = 0;
    activeSlider->downY   = 0;
    activeSlider->downI   = -1;
    activeSlider->ctrl    = direction;
    activeSlider->sens    = sensitivity;

    return activeSlider;
}

void activeSliderDestroy(ActiveSlider* activeSlider)
{
    activeImageDestroy(activeSlider->bitmap);
    free(activeSlider);
}

void activeSliderDraw(ActiveSlider* activeSlider, void* dc)
{
    activeImageDraw(activeSlider->bitmap, dc);
}

int activeSliderShow(ActiveSlider* activeSlider, int show)
{
    return activeImageShow(activeSlider->bitmap, show);
}

int activeSliderSetImage(ActiveSlider* activeSlider, int index)
{
    index = (int)ceil(index * (activeSlider->count - 1) / 100.0);

    if (index >= activeSlider->count) {
        index = activeSlider->count - 1;
    }

    if (index != activeSlider->index) {
        activeSlider->index = index;
        activeImageSetImage(activeSlider->bitmap, index);
    }
    return 1;
}

int activeSliderDown(ActiveSlider* activeSlider, int x, int y)
{
    if (!activeImageIsVisible(activeSlider->bitmap)) {
        return 0;
    }

    if ((UInt32)(x - activeSlider->x) >= activeSlider->width ||
        (UInt32)(y - activeSlider->y) >= activeSlider->height)
    {
        return 0;
    }
    
    activeSlider->downI = activeSlider->index;
    activeSlider->downX = x;
    activeSlider->downY = y;

    return 1;
}

int activeSliderUp(ActiveSlider* activeSlider, int x, int y)
{
    activeSlider->downI = -1;

    if (activeSlider->upEvent != NULL) {
        if (activeSlider->arg2 == -1) {
            activeSlider->upEvent(activeSlider->arg1, 0);
        }
        else {
            activeSlider->upEvent(activeSlider->arg1, activeSlider->arg2);
        }
    }    
    return 0;
}

int activeSliderMouseMove(ActiveSlider* activeSlider, int x, int y)
{
    int step;
    int stepX;
    int stepY;
    int index;

    if (activeSlider->downI == -1) {
        return 0;
    }

    stepX = x - activeSlider->downX;
    stepY = y - activeSlider->downY;

    if (activeSlider->ctrl == AS_HORIZONTAL) step = stepX / activeSlider->sens;
    if (activeSlider->ctrl == AS_VERTICAL)   step = -stepY / activeSlider->sens;
    if (activeSlider->ctrl == AS_BOTH)       step = (stepX - stepY) / activeSlider->sens;

    index = activeSlider->downI + step;
    if (index < 0) index = 0;
    if (index > activeSlider->count - 1) index = activeSlider->count - 1;

    if (index == activeSlider->index) {
        return 0;
    }

    index = 100 * index / (activeSlider->count - 1);
    activeSliderSetImage(activeSlider, index);

    if (activeSlider->event != NULL && activeSlider->count > 1) {
        activeSlider->event(index);
    }

    return 1;
}



struct ActiveGrabImage {
    ActiveImage* bitmap;
    int x;
    int y;
    UInt32 width;
    UInt32 height;
    int downX;
    int downY;
    int downI;
};

ActiveGrabImage* activeGrabImageCreate(int x, int y, int cols, ArchBitmap* bitmap, int count)
{
    ActiveGrabImage* activeImage = malloc(sizeof(ActiveImage));

    activeImage->bitmap  = activeImageCreate(x, y, cols, bitmap, count);

    activeImage->x       = x;
    activeImage->y       = y;
    activeImage->width   = activeImageGetWidth(activeImage->bitmap);
    activeImage->height  = activeImageGetHeight(activeImage->bitmap);
    activeImage->downX   = 0;
    activeImage->downY   = 0;
    activeImage->downI   = 0;
    return activeImage;
}

void activeGrabImageDestroy(ActiveGrabImage* activeImage)
{
    activeImageDestroy(activeImage->bitmap);
    free(activeImage);
}

int activeGrabImageSetImage(ActiveGrabImage* activeImage, int index)
{
    return activeImageSetImage(activeImage->bitmap, index);
}

int activeGrabImageShow(ActiveGrabImage* activeImage, int show)
{
    return activeImageShow(activeImage->bitmap, show);
}

void activeGrabImageDraw(ActiveGrabImage* activeImage, void* dc)
{
    activeImageDraw(activeImage->bitmap, dc);
}

int activeGrabImageMouseMove(ActiveGrabImage* activeImage, int x, int y)
{
    return 0;
}

int activeGrabImageDown(ActiveGrabImage* activeImage, int x, int y)
{
    if (!activeImageIsVisible(activeImage->bitmap)) {
        return 0;
    }

    if ((UInt32)(x - activeImage->x) >= activeImage->width ||
        (UInt32)(y - activeImage->y) >= activeImage->height)
    {
        return 0;
    }
    
    activeImage->downX = x;
    activeImage->downY = y;
    activeImage->downI = 1;

    archWindowStartMove();
    return 0;
}

int activeGrabImageUp(ActiveGrabImage* activeImage, int x, int y)
{
    if (!activeImage->downI) {
        return 0;
    }
    
    activeImage->downI = 0;

    archWindowEndMove();

    return 0;
}

struct ActiveObject 
{
    char id[64];
    void* handle;
    int x;
    int y;
    int width;
    int height;
    int arg1;
    int arg2;
    void* object;
};

void* archObjectCreate(char* id, void* window, int x, int y, int width, int height, int arg1, int arg2);
void archObjectDestroy(char* id, void* object);

ActiveObject* activeObjectCreate(int x, int y, int width, int height, const char* id, int arg1, int arg2)
{
    ActiveObject* activeObject = malloc(sizeof(ActiveObject));

    strcpy(activeObject->id, id);
    activeObject->arg1   = arg1;
    activeObject->arg2   = arg2;
    activeObject->x      = x;
    activeObject->y      = y;
    activeObject->width  = width;
    activeObject->height = height;
    activeObject->object = NULL;

    return activeObject;
}

void activeObjectDestroy(ActiveObject* activeObject)
{
    activeObjectActivate(activeObject, NULL);
    
    free(activeObject);
}

void activeObjectActivate(ActiveObject* activeObject, void* window)
{
    if (window != NULL && activeObject->object == NULL) {
        activeObject->object = archObjectCreate(activeObject->id,
                                                window, 
                                                activeObject->x, 
                                                activeObject->y, 
                                                activeObject->width, 
                                                activeObject->height,
                                                activeObject->arg1,
                                                activeObject->arg2);
    }

    if (window == NULL && activeObject->object != NULL) {
        archObjectDestroy(activeObject->id, activeObject->object);
        activeObject->object = NULL;
    }
}

