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
#ifndef EDIT_CONTROLS_H
#define EDIT_CONTROLS_H

#include <windows.h>
#include <string>
#include <list>
#include <map>

class HexInputDialog {
public:
    enum { WM_NEWVALUE = WM_USER + 7029 };

    HexInputDialog(HWND parent, int x, int y, int width, int height, int numChars);
    ~HexInputDialog();

    void setValue(int value);
    void show();
    void hide();
private:
    int wx;
    int wy;
    int wwidth;
    int wheight;
    int chars;
    HWND hwnd;

    static std::map<HWND, HexInputDialog*> dialogMap;
    static int  richeditVersion;

    static void initRichEditControlDll();
    static BOOL CALLBACK dlgStaticProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

    BOOL dlgProc(UINT iMsg, WPARAM wParam, LPARAM lParam);
};


#endif //EDIT_CONTROLS_H
