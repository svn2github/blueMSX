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

#include "SymbolInfo.h"
#include <windows.h>
#include <map>

class Disassembly {
public:
    Disassembly(HINSTANCE hInstance, HWND owner, SymbolInfo* symInfo);
    ~Disassembly();

    void show();
    void hide();
    bool isVisible();
    
    void refresh();

    void enableEdit();
    void disableEdit();

    WORD dasm(WORD PC, char* dest);
    
    void updatePosition(RECT& rect);

    void onWmKeyUp(int keyCode);

    void updateContent(BYTE* memory, WORD pc);
    void invalidateContent();
    void updateScroll(int address = -1);
    void updateBreakpoints();
    void setRuntoBreakpoint();
    void clearRuntoBreakpoint();
    void setCursor(WORD address);

    void toggleBreakpoint(int address = -1, bool setAlways = false);
    void toggleBreakpointEnable();
    void clearAllBreakpoints();

    LRESULT wndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

private:

    int dasm(BYTE* memory, WORD PC, char* dest);
    void scrollWindow(int sbAction);
    void drawText(int top, int bottom);

    bool     editEnabled;

    HWND   hwnd;
    HDC    hMemdc;
    HFONT  hFont;
    HBRUSH hBrushWhite;
    HBRUSH hBrushLtGray;
    HBRUSH hBrushDkGray;
    HBRUSH hBrushBlack;
    
    COLORREF colorBlack;
    COLORREF colorGray;
    COLORREF colorWhite;

    int    textHeight;
    int    textWidth;

    enum BpState { BP_NONE = 0, BP_SET = 1, BP_DISABLED = 2 };
    
    struct LineInfo {
        WORD address;
        bool isLabel;
        bool haspc;
        char text[48];
        int  textLength;
        char addr[48];
        int  addrLength;
        char dataText[48];
        int  dataTextLength;
    };

    int      runtoBreakpoint;
    int      programCounter;
    int      firstVisibleLine;
    int      lineCount;
    int      currentLine;
    LineInfo lineInfo[0x20000];
    int      breakpointCount;
    BpState  breakpoint[0x10000];
    int      linePos;
    bool     hasKeyboardFocus;

    BYTE backupMemory[0x10000];
    WORD backupPc;

    SymbolInfo* symbolInfo;
};


#endif //DISASSEMBLY_H
