/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Sdl/SdlMouse.c,v $
**
** $Revision: 1.4 $
**
** $Date: 2006-06-24 07:25:10 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2006 Daniel Vik
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
#include "SdlMouse.h"
#include <SDL/SDL.h>
#include "MsxTypes.h"
#include "ArchInput.h"


typedef struct SdlMouse {
    SDL_Cursor* cursorArrow;
    SDL_Cursor* cursorCross;
    AmEnableMode mode;
    int hasFocus;
    struct {
        int top;
        int left;
        int bottom;
        int right;
    } captRgn;
    int buttonState;
    int defX;
    int defY;
    int lockDx;
    int lockDy;
    int dx;
    int dy;
} SdlMouse;

SdlMouse mouse;

static int sdlMouseInRect(int x, int y)
{
    return x > mouse.captRgn.left && x < mouse.captRgn.right &&
           y > mouse.captRgn.top  && y < mouse.captRgn.bottom;
}
#if 0
  "X                               ",
  "XX                              ",
  "X.X                             ",
  "X..X                            ",
  "X...X                           ",
  "X....X                          ",
  "X.....X                         ",
  "X......X                        ",
  "X.......X                       ",
  "X........X                      ",
  "X.....XXXXX                     ",
  "X..X..X                         ",
  "X.X X..X                        ",
  "XX  X..X                        ",
  "X    X..X                       ",
  "     X..X                       ",
  "      X..X                      ",
  "      X..X                      ",
  "       XX                       ",

  "        XXXXX                   ",
  "        X   X                   ",
  "        X   X                   ",
  "         X X                    ",
  "         X X                    ",
  "         X X                    ",
  "          X                     ",
  "XXX       X       XXX           ",
  "X  XXX         XXX  X           ",
  "X     XX  X  XX     X           ",
  "X  XXX         XXX  X           ",
  "XXX       X       XXX           ",
  "          X                     ",
  "         X X                    ",
  "         X X                    ",
  "         X X                    ",
  "        X   X                   ",
  "        X   X                   ",
  "        XXXXX                   ",
#endif
static UInt8 crossData[] = {
    0x00,0xf8,0x00,0x00,
    0x00,0x88,0x00,0x00,
    0x00,0x88,0x00,0x00,
    0x00,0x50,0x00,0x00,
    0x00,0x50,0x00,0x00,
    0x00,0x50,0x00,0x00,
    0x00,0x20,0x00,0x00,
    0x70,0x20,0x38,0x00,
    0x9c,0x01,0xc8,0x00,
    0x83,0x26,0x08,0x00,
    0x9c,0x01,0xc8,0x00,
    0x70,0x20,0x38,0x00,
    0x00,0x20,0x00,0x00,
    0x00,0x50,0x00,0x00,
    0x00,0x50,0x00,0x00,
    0x00,0x50,0x00,0x00,
    0x00,0x88,0x00,0x00,
    0x00,0x88,0x00,0x00,
    0x00,0xf8,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00
};

static UInt8 crossMask[] = {
    0x00,0xf8,0x00,0x00,
    0x00,0xf8,0x00,0x00,
    0x00,0xf8,0x00,0x00,
    0x00,0x70,0x00,0x00,
    0x00,0x70,0x00,0x00,
    0x00,0x70,0x00,0x00,
    0x00,0x20,0x00,0x00,
    0x70,0x20,0x38,0x00,
    0xfc,0x01,0xf8,0x00,
    0xff,0x27,0xf8,0x00,
    0xfc,0x01,0xf8,0x00,
    0x70,0x20,0x38,0x00,
    0x00,0x20,0x00,0x00,
    0x00,0x70,0x00,0x00,
    0x00,0x70,0x00,0x00,
    0x00,0x70,0x00,0x00,
    0x00,0xf8,0x00,0x00,
    0x00,0xf8,0x00,0x00,
    0x00,0xf8,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00
};

static UInt8 arrowMask[] = {
    0x80,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xe0,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,
    0xf8,0x00,0x00,0x00,0xfc,0x00,0x00,0x00,0xfe,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
    0xff,0x80,0x00,0x00,0xff,0xc0,0x00,0x00,0xff,0xe0,0x00,0x00,0xfe,0x00,0x00,0x00,
    0xef,0x00,0x00,0x00,0xcf,0x00,0x00,0x00,0x87,0x80,0x00,0x00,0x07,0x80,0x00,0x00,
    0x03,0xc0,0x00,0x00,0x03,0xc0,0x00,0x00,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

static UInt8 arrowData[] = {
    0x80,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xa0,0x00,0x00,0x00,0x90,0x00,0x00,0x00,
    0x88,0x00,0x00,0x00,0x84,0x00,0x00,0x00,0x82,0x00,0x00,0x00,0x81,0x00,0x00,0x00,
    0x80,0x80,0x00,0x00,0x80,0x40,0x00,0x00,0x83,0xe0,0x00,0x00,0x92,0x00,0x00,0x00,
    0xa9,0x00,0x00,0x00,0xc9,0x00,0x00,0x00,0x84,0x80,0x00,0x00,0x04,0x80,0x00,0x00,
    0x02,0x40,0x00,0x00,0x02,0x40,0x00,0x00,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};


void sdlMouseSetCaptureRect(int x, int y, int width, int height)
{
    if (mouse.cursorArrow == NULL) {
        mouse.cursorArrow = SDL_CreateCursor(arrowData, arrowMask, 32, 32, 0, 0);
    }

    if (mouse.cursorCross == NULL) {
        mouse.cursorCross = SDL_CreateCursor(crossData, crossMask, 32, 32, 10, 10);
    }

    mouse.captRgn.top    = y;
    mouse.captRgn.left   = x;
    mouse.captRgn.bottom = y + height - 1;
    mouse.captRgn.right  = x + width - 1;
    mouse.defX           = x + 100;
    mouse.defY           = y + 100;

    SDL_SetCursor(mouse.cursorArrow);
}

void sdlMouseSetFocus(int focus)
{
    if (focus) {
        if (mouse.mode == AM_DISABLE) {
            SDL_ShowCursor(SDL_DISABLE);
        }
        if (mouse.mode == AM_ENABLE_MOUSE) {
            SDL_WarpMouse(mouse.defX, mouse.defY);
        }
    }
    else {
        mouse.hasFocus = 0;
        SDL_ShowCursor(SDL_ENABLE);
    }
}

void sdlMouseButton(int button, int pressed)
{
    if (mouse.mode == AM_DISABLE) {
        return;
    }
    if (pressed) {
        if (button == SDL_BUTTON_LEFT)   mouse.buttonState |= 1;
        if (button == SDL_BUTTON_MIDDLE) mouse.buttonState |= 2;
        if (button == SDL_BUTTON_RIGHT)  mouse.buttonState |= 2;
    }
    else {
        if (button == SDL_BUTTON_LEFT)   mouse.buttonState &= ~1;
        if (button == SDL_BUTTON_MIDDLE) mouse.buttonState &= ~2;
        if (button == SDL_BUTTON_RIGHT)  mouse.buttonState &= ~2;
    }
}

void sdlMouseMove(int x, int y)
{
    if (mouse.mode == AM_ENABLE_LASER) {
        mouse.hasFocus = sdlMouseInRect(x, y);
        mouse.dx = 0x10000 * (x - mouse.captRgn.left) / (mouse.captRgn.right  - mouse.captRgn.left);
        mouse.dy = 0x10000 * (y - mouse.captRgn.top)  / (mouse.captRgn.bottom - mouse.captRgn.top);
    }
 
    if (mouse.mode == AM_ENABLE_MOUSE) {
        if (x == mouse.captRgn.left || x == mouse.captRgn.right ||
            y == mouse.captRgn.top  || y == mouse.captRgn.bottom) 
        {
            mouse.hasFocus = 0;
            SDL_ShowCursor(SDL_ENABLE);
        }

        if (x == mouse.defX && y == mouse.defY) {
            if (!mouse.hasFocus) {
                mouse.buttonState = 0;
                mouse.lockDy      = 0;
                mouse.lockDx      = 0;
                mouse.dx          = 0;
                mouse.dy          = 0;
                mouse.hasFocus    = 1;
                SDL_ShowCursor(SDL_DISABLE);
            }
        }
        else {
            if (mouse.hasFocus) {
                int dx = x - mouse.defX;
                int dy = y - mouse.defY;
                int mx = mouse.defX;
                int my = mouse.defY;

                mouse.lockDx += dx;
                mouse.lockDy += dy;
                mouse.dx     += dx;
                mouse.dy     += dy;
                
                if (mouse.lockDx < -500) mx = mouse.captRgn.left;
                if (mouse.lockDx >  500) mx = mouse.captRgn.right;
                if (mouse.lockDy < -500) my = mouse.captRgn.top;
                if (mouse.lockDy >  500) my = mouse.captRgn.bottom;

                SDL_WarpMouse(mx, my);
            }
            else if (sdlMouseInRect(x, y)) {
                SDL_WarpMouse(mouse.defX, mouse.defY);
            }
        }
    }
}

void archMouseGetState(int* dx, int* dy) 
{ 
    *dx = 0;
    *dy = 0;

    if (mouse.hasFocus) {
        if (mouse.mode == AM_ENABLE_LASER) {
            *dx = mouse.dx;
            *dy = mouse.dy;
        }

        if (mouse.mode == AM_ENABLE_MOUSE) {
            *dx = -mouse.dx;
            *dy = -mouse.dy;
            mouse.dx = 0;
            mouse.dy = 0;
        }
    }
}

int  archMouseGetButtonState(int checkAlways) 
{ 
    if (mouse.hasFocus) {
        return mouse.buttonState; 
    }
    else {
        return 0;
    }
}

void  archMouseEmuEnable(AmEnableMode mode) 
{ 
   mouse.mode = mode;
}
