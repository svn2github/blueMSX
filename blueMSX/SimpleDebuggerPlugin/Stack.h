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
#ifndef STACK_H
#define STACK_H

#include <windows.h>

class StackWindow {
public:
    StackWindow(HINSTANCE hInstance, HWND owner);
    ~StackWindow();

    void show();
    void hide();
    bool isVisible();

    void enableEdit();
    void disableEdit();
    
    void updatePosition(RECT& rect);

    void refresh();

    void updateContent(BYTE* memory, WORD sp);
    void invalidateContent();
    void updateScroll();

    LRESULT wndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

private:

    enum { MAX_LINES = 1024 };

    void scrollWindow(int sbAction);
    void drawText(int top, int bottom);

    bool     editEnabled;

    HWND   hwnd;
    HDC    hMemdc;
    HFONT  hFont;
    HBRUSH hBrushWhite;
    HBRUSH hBrushLtGray;
    HBRUSH hBrushDkGray;
    
    COLORREF colorBlack;
    COLORREF colorRed;
    COLORREF colorGray;

    int    textHeight;
    int    textWidth;

    struct LineInfo {
        WORD address;
        char text[48];
        int  textLength;
        char dataText[48];
        int  dataTextLength;
        bool modified;
    };

    int      lineCount;
    int      currentLine;
    LineInfo lineInfo[MAX_LINES];
    int      linePos;
    
    BYTE backupMemory[0x10000];
    WORD backupSP;
};

#endif //STACK_H