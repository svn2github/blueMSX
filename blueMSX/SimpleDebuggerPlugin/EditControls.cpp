/*****************************************************************************
** File:        Win32Toolbar.c
**
** Author:      Daniel Vik
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
#include "EditControls.h"
#include "Resource.h"
#include "ToolInterface.h"
#include <stdio.h>
#include <CommCtrl.h>
#include <RichEdit.h>


HexInputDialog::HexInputDialog(HWND parent, int x, int y, int width, int height, int numChars) :
    wx(x), wy(y), wwidth(width), wheight(height), chars(numChars)
{
    initRichEditControlDll();

    if (richeditVersion == 1) {
        hwnd = CreateDialogParam(GetDllHinstance(), MAKEINTRESOURCE(IDD_RICHEDITCTRL1), parent, dlgStaticProc, (LPARAM)this);
    }
    else if (richeditVersion == 2) {
        hwnd = CreateDialogParam(GetDllHinstance(), MAKEINTRESOURCE(IDD_RICHEDITCTRL2), parent, dlgStaticProc, (LPARAM)this);
    }
    show();
}

HexInputDialog::~HexInputDialog() 
{
    
    std::map<HWND, HexInputDialog*>::iterator iter = dialogMap.find(hwnd);
    if (iter != dialogMap.end()) {
        dialogMap.erase(iter);
    }
    DestroyWindow(hwnd);
}

void HexInputDialog::setValue(int value)
{
    char text[16];
    sprintf(text, "%X", value);
    text[chars] = 0;
    SETTEXTEX t = { GT_DEFAULT, CP_ACP };
    SendDlgItemMessage(hwnd, IDC_ADDRESS, EM_SETTEXTEX, (WPARAM)&t, (LPARAM)text);
}

void HexInputDialog::show() 
{
    ShowWindow(hwnd, TRUE);
}

void HexInputDialog::hide() 
{
    ShowWindow(hwnd, FALSE);
}

void HexInputDialog::initRichEditControlDll()
{
    static bool richeditinitialized = false;
    if (richeditinitialized) {
        InitCommonControls();
        return;
    }

    std::string richeditLibrary;

    OSVERSIONINFO osInfo;
    memset( &osInfo, 0, sizeof(OSVERSIONINFO) );
    osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    if ( GetVersionEx( &osInfo ) ) {
        if ( osInfo.dwPlatformId == VER_PLATFORM_WIN32_NT ) {
            richeditLibrary = "RICHED20.Dll";
            richeditVersion = 2;
        }
        else if ( osInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS ) { //Windows 9.x
            richeditLibrary = "RICHED32.DLL";
            richeditVersion = 1;
        }
    }       

    if  (NULL == LoadLibrary(richeditLibrary.c_str())) {
        richeditVersion = 0;
    }
}

BOOL CALLBACK HexInputDialog::dlgStaticProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    if (iMsg == WM_INITDIALOG) {
        dialogMap[hwnd] = (HexInputDialog*)lParam;
        dialogMap[hwnd]->hwnd = hwnd;
    }
    if (dialogMap.find(hwnd) == dialogMap.end()) {
        return FALSE;
    }
    return dialogMap[hwnd]->dlgProc(iMsg, wParam, lParam);
}

BOOL HexInputDialog::dlgProc(UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (iMsg) {
    case WM_INITDIALOG:
        SetWindowPos(hwnd, NULL, wx, wy, wwidth, wheight, SWP_NOZORDER);
        RECT r;
        GetClientRect(hwnd, &r);
        SetWindowPos(GetDlgItem(hwnd, IDC_ADDRESS), NULL, 0, 0, r.right, r.bottom, SWP_NOZORDER);
        SendDlgItemMessage(hwnd, IDC_ADDRESS, EM_SETEVENTMASK, 0, 
                            SendDlgItemMessage(hwnd, IDC_ADDRESS, EM_GETEVENTMASK, 0, 0) | ENM_KEYEVENTS); 
        return FALSE;

    case WM_NOTIFY:  
        switch (LOWORD(wParam)) { 
        case IDC_ADDRESS: 
            {
                MSGFILTER *keyfilter = (MSGFILTER *)lParam; 
                int keyCode;
                switch(keyfilter->nmhdr.code) { 
                case EN_MSGFILTER: 
                    switch(keyfilter->msg) { 
                    case WM_CHAR: 
                        GETTEXTLENGTHEX tl = {GTL_DEFAULT, CP_ACP};
                        int len = SendDlgItemMessage(hwnd, IDC_ADDRESS, EM_GETTEXTLENGTHEX, (WPARAM)&tl, 0);
                        if (len == E_INVALIDARG) {
                            len = 0;
                        }
                        keyCode = keyfilter->wParam;
                        if (len < chars) {
                            if ((keyCode >= '0' && keyCode <= '9') ||
                                (keyCode >= 'a' && keyCode <= 'f') ||
                                (keyCode >= 'A' && keyCode <= 'F'))
                            {
                                if (keyCode >= 'a' && keyCode <= 'f') {
                                    keyfilter->wParam -= 'a' - 'A';
                                }
                                SetWindowLong(hwnd, DWL_MSGRESULT, 0);
                                return TRUE;
                            }
                        }
                        if (keyCode == '\r' || keyCode == '\n') {
                            GETTEXTEX t = {15, GT_DEFAULT, CP_ACP, NULL, NULL};
                            char text[16];
                            int len = SendDlgItemMessage(hwnd, IDC_ADDRESS, EM_GETTEXTEX, (WPARAM)&t, (LPARAM)text);
                            text[len] = 0;
                            int addr = 0;
                            sscanf(text, "%X", &addr);

                            SendMessage(GetParent(hwnd), WM_NEWVALUE, addr, 0);
                        }

                        SetWindowLong(hwnd, DWL_MSGRESULT, 1);
                        return TRUE;
                    }
                }
            }
        }
        return FALSE;
    }
    return FALSE;
}

std::map<HWND, HexInputDialog*> HexInputDialog::dialogMap;
int HexInputDialog::richeditVersion = 0;
