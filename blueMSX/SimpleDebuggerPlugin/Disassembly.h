/*****************************************************************************
** File:
**      Win32ToolBar.h
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
#ifndef DISASSEMBLY_H
#define DISASSEMBLY_H

#include <windows.h>

class Disassembly {
public:
    Disassembly(HINSTANCE hInstance, HWND owner);
    ~Disassembly();

    void show();
    void hide();
    
    void updatePosition(RECT& rect);

    void updateContent(BYTE* memory, WORD pc);
    void invalidateContent();
    void updateScroll();

    BOOL dlgProc(UINT iMsg, WPARAM wParam, LPARAM lParam);

private:

    int dasm(BYTE* memory, WORD PC, char* dest);
    void scrollWindow(int sbAction);
    void drawText(int top, int bottom);

    HWND   hwnd;
    HDC    hMemdc;
    HFONT  hFont;
    int    textHeight;
    
    struct LineInfo {
        WORD address;
        bool breakpoint;
        bool haspc;
        char text[48];
        int  textLength;
    };

    int      programCounter;
    int      firstVisibleLine;
    int      lineCount;
    LineInfo lineInfo[0x10000];
    int      linePos;
};

#endif //DISASSEMBLY_H
