/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Theme/ThemeControls.h,v $
**
** $Revision: 1.4 $
**
** $Date: 2005-01-09 09:04:57 $
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
#ifndef THEME_CONTROLS_H
#define THEME_CONTROLS_H

#include "ArchBitmap.h"

typedef void (*ButtonEvent)(int, int);

typedef struct ActiveImage ActiveImage;

ActiveImage* activeImageCreate(int x, int y, int cols, ArchBitmap* bitmap, int count);
void activeImageDestroy(ActiveImage* activeImage);
void activeImageSetPosition(ActiveImage* activeImage, int x, int y);
int activeImageGetWidth(ActiveImage* activeImage);
int activeImageGetHeight(ActiveImage* activeImage);
int activeImageSetImage(ActiveImage* activeImage, int index);
int activeImageShow(ActiveImage* activeImage, int show);
void activeImageDraw(ActiveImage* activeImage, void* dc);


typedef struct ActiveButton ActiveButton;

ActiveButton* activeButtonCreate(int x, int y, int cols, ArchBitmap* bitmap, ButtonEvent event, int arg1, int arg2);
void activeButtonDestroy(ActiveButton* activeButton);
int activeButtonEnable(ActiveButton* activeButton, int enable);
int activeButtonMouseMove(ActiveButton* activeButton, int x, int y);
int activeButtonDown(ActiveButton* activeButton, int x, int y);
int activeButtonUp(ActiveButton* activeButton, int x, int y);
int activeButtonShow(ActiveButton* activeButton, int show);
void activeButtonDraw(ActiveButton* activeButton, void* dc);
int activeButtonForcePushed(ActiveButton* activeButton, int pushed);


typedef struct ActiveDualButton ActiveDualButton;

ActiveDualButton* activeDualButtonCreate(int x, int y, int cols, ArchBitmap* bitmap, 
                                          ButtonEvent eventA, int argA1, int argA2, 
                                          ButtonEvent eventB, int argB1, int argB2, int vertical);
void activeDualButtonDestroy(ActiveDualButton* activeButton);
int activeDualButtonEnable(ActiveDualButton* activeButton, int enable);
int activeDualButtonMouseMove(ActiveDualButton* activeButton, int x, int y);
int activeDualButtonDown(ActiveDualButton* activeButton, int x, int y);
int activeDualButtonUp(ActiveDualButton* activeButton, int x, int y);
void activeDualButtonDraw(ActiveDualButton* activeButton, void* dc);
int activeDualButtonShow(ActiveDualButton* activeButton, int show);
int activeDualButtonForcePushed(ActiveDualButton* activeButton, int pushed);


typedef struct ActiveText ActiveText;

ActiveText* activeTextCreate(int x, int y, int cols, ArchBitmap* bitmap, int width, int type, int color, int rightAligned);
void activeTextDestroy(ActiveText* activeText);
int activeTextSetText(ActiveText* activeText, char* string);
void activeTextDraw(ActiveText* activeText, void* dc);
int activeTextShow(ActiveText* activeText, int show);


typedef struct ActiveMeter ActiveMeter;

ActiveMeter* activeMeterCreate(int x, int y, int cols, ArchBitmap* bitmap, int count);
void activeMeterDestroy(ActiveMeter* activeMeter);
int activeMeterSetImage(ActiveMeter* activeMeter, int index);
void activeMeterDraw(ActiveMeter* activeMeter, void* dc);
int activeMeterShow(ActiveMeter* activeMeter, int show);


typedef void (*SliderEvent)(int);
typedef struct ActiveSlider ActiveSlider;
typedef enum { AS_HORIZONTAL, AS_VERTICAL, AS_BOTH } AsDirection;

ActiveSlider* activeSliderCreate(int x, int y, int cols, ArchBitmap* bitmap, SliderEvent event, int count,
                                 AsDirection direction, int sensitivity);
void activeSliderDestroy(ActiveSlider* activeSlider);
void activeSliderDraw(ActiveSlider* activeSlider, void* dc);
int activeSliderShow(ActiveSlider* activeSlider, int show);
int activeSliderSetImage(ActiveSlider* activeSlider, int index);
int activeSliderDown(ActiveSlider* activeSlider, int x, int y);
int activeSliderUp(ActiveSlider* activeSlider, int x, int y);
int activeSliderMouseMove(ActiveSlider* activeSlider, int x, int y);

typedef struct ActiveObject ActiveObject;

ActiveObject* activeObjectCreate(int x, int y, int width, int height, const char* id);
void activeObjectDestroy(ActiveObject* activeObject);
void activeObjectActivate(ActiveObject* activeObject, void* window);

#endif
