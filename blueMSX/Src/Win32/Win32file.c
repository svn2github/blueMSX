/*****************************************************************************
** File:        Win32file.c
**
** Author:      Daniel Vik
**
** Description: File open and save dialog boxes.
**
** More info:   www.bluemsx.com
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
#include <windows.h> 
#include <tchar.h>
#include "Win32file.h"
#include <stdlib.h>
#include <stdio.h>
#include "Resource.h"
#include "RomMapper.h"
#include "RomLoader.h"
#include "zipHelper.h"
#include "Win32Common.h"

static RomType romTypeList[] = {
    ROM_ASCII8,
    ROM_ASCII8SRAM,
    ROM_ASCII16,
    ROM_ASCII16SRAM,
    ROM_KONAMI4,
    ROM_KONAMI5,
    ROM_PLAIN,
    ROM_BASIC,
    ROM_0x4000,
    ROM_KOEI,
    ROM_RTYPE,
    ROM_CROSSBLAIM,
    ROM_HARRYFOX,
    ROM_LODERUNNER,
    ROM_HALNOTE,
	ROM_KONAMISYNTH,
    ROM_MAJUTSUSHI,
    ROM_SCC,
    ROM_SCCPLUS,
    ROM_KONAMI4NF, 
    ROM_ASCII16NF,
    ROM_GAMEMASTER2,
    ROM_KOREAN80,
    ROM_KOREAN90,
    ROM_KOREAN126,
    ROM_HOLYQURAN,
    ROM_FMPAC,
    ROM_MSXAUDIO,
    ROM_DISKPATCH,
    ROM_TC8566AF,
    ROM_MICROSOL,
    ROM_NATIONALFDC,
    ROM_PHILIPSFDC,
    ROM_SVI738FDC,
    ROM_KANJI,
    ROM_KANJI12,
    ROM_JISYO,
    ROM_BUNSETU,
    ROM_MSXDOS2,
    ROM_NATIONAL,
    ROM_PANASONIC16,
    ROM_PANASONIC32,
    ROM_SVI328,
    ROM_UNKNOWN,
};

static RomType openRomType;

UINT_PTR CALLBACK hookRomProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    switch (iMsg) {
    case WM_TIMER:
        if (wParam == 13) {
            updateDialogPos(GetParent(hDlg), DLG_ID_OPEN, 0, 0);
            ShowWindow(GetParent(hDlg), SW_NORMAL);
            KillTimer(hDlg, 13);
        }
        return 0;
        
    case WM_INITDIALOG:
        {
            int i;

            ShowWindow(GetParent(hDlg), SW_HIDE);
            updateDialogPos(GetParent(hDlg), DLG_ID_OPEN, 0, 1);
            SetTimer(hDlg, 13, 250, 0);

            for (i = 0; romTypeList[i] != ROM_UNKNOWN; i++) {
                SendDlgItemMessage(hDlg, IDC_OPEN_ROMTYPE, CB_ADDSTRING, 0, (LPARAM)romTypeToString(romTypeList[i]));
//                SendDlgItemMessage(hDlg, IDC_ROMTYPE, CB_SETCURSEL, i, 0);
            }
            SendDlgItemMessage(hDlg, IDC_OPEN_ROMTYPE, CB_ADDSTRING, 0, (LPARAM)romTypeToString(ROM_UNKNOWN));
            EnableWindow(GetDlgItem(hDlg, IDC_OPEN_ROMTYPE), 0);
        }
        return 0;

    case WM_SIZE:
        {
            RECT r;
            int height;
            int width;
            HWND hwnd;

            GetClientRect(GetParent(hDlg), &r);
            
            height = r.bottom - r.top;
            width  = r.right - r.left;

            hwnd = GetDlgItem(hDlg, IDC_OPEN_ROMTEXT);
            SetWindowPos(hwnd, NULL, 8, height - 29, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

            hwnd = GetDlgItem(hDlg, IDC_OPEN_ROMTYPE);
            SetWindowPos(hwnd, NULL, 81, height - 32, width - 187, 12, SWP_NOZORDER);
        }
        return 0;
        
    case WM_COMMAND:
        switch(LOWORD(wParam)) {
        case IDC_OPEN_ROMTYPE:
            if (HIWORD(wParam) == 1 || HIWORD(wParam) == 2) {
                int idx = SendMessage(GetDlgItem(hDlg, IDC_OPEN_ROMTYPE), CB_GETCURSEL, 0, 0);

                openRomType = idx == CB_ERR ? -1 : romTypeList[idx];
            }
            return 0;
        }

        return 0;

    case WM_DESTROY:
        saveDialogPos(GetParent(hDlg), DLG_ID_OPEN);
        return 0;
        
    case WM_NOTIFY:
        {
            OFNOTIFY* ofn = (OFNOTIFY*)lParam;
            switch (ofn->hdr.code) {
            case CDN_SELCHANGE:
                {
                    char fileName[MAX_PATH];
                    int fileSize = SendMessage(GetParent(hDlg), CDM_GETFILEPATH, MAX_PATH, (LPARAM)fileName);
                    int size;
                    char* buf = NULL;

                    if (isFileExtension(fileName, ".zip")) {
                        int countRom;
                        int countMx1;
                        int countMx2;
                        char* fileListRom = zipGetFileList(fileName, ".rom", &countRom);
                        char* fileListMx1 = zipGetFileList(fileName, ".mx1", &countMx1);
                        char* fileListMx2 = zipGetFileList(fileName, ".mx2", &countMx2);
                        int count = countRom + countMx1 + countMx2;

                        if (count == 1) {
                            if (countRom == 1) {
                                buf = romLoad(fileName, fileListRom, &size);
                            }
                            if (countMx1 == 1) {
                                buf = romLoad(fileName, fileListMx1, &size);
                            }
                            if (countMx2 == 1) {
                                buf = romLoad(fileName, fileListMx2, &size);
                            }
                        }

                        if (fileListRom) free(fileListRom);
                        if (fileListMx1) free(fileListMx1);
                        if (fileListMx2) free(fileListMx2);
                    }
                    else {
                        buf = romLoad(fileName, NULL, &size);
                    }
            
                    if (buf != NULL) {
                        RomType romType = romMapperGuessRom(buf, size, 0, NULL);
                        int idx = 0;

                        while (romTypeList[idx] != romType) {
                            idx++;
                        }

                        SendMessage(GetDlgItem(hDlg, IDC_OPEN_ROMTYPE), CB_SETCURSEL, idx, 0);

                        free(buf);

                        openRomType = romType;

                        EnableWindow(GetDlgItem(hDlg, IDC_OPEN_ROMTYPE), 1);
                    }    
                    else {
                        openRomType = ROM_UNKNOWN;
                        EnableWindow(GetDlgItem(hDlg, IDC_OPEN_ROMTYPE), 0);
                        SendMessage(GetDlgItem(hDlg, IDC_OPEN_ROMTYPE), CB_SETCURSEL, -1, 0);
                    }
                }
                break;
            }
        }
        return 0;
    }

    return 0;
}

char* openRomFile(HWND hwndOwner, _TCHAR* pTitle, char* pFilter, char* pDir, int mustExist, 
                  char* defExt, int* filterIndex, RomType* romType)
{ 
    OPENFILENAME ofn; 
    BOOL rv; 
    static char pFileName[MAX_PATH];
    FILE* file;

    pFileName[0] = 0; 
    *romType = ROM_UNKNOWN;

    ofn.lStructSize = sizeof(OPENFILENAME); 
    ofn.hwndOwner = hwndOwner; 
    ofn.hInstance = (HINSTANCE)GetModuleHandle(NULL); 
    ofn.lpstrFilter = pFilter ? pFilter : "*.*\0\0"; 
    ofn.lpstrCustomFilter = NULL; 
    ofn.nMaxCustFilter = 0; 
    ofn.nFilterIndex = filterIndex ? *filterIndex : 0; 
    ofn.lpstrFile = pFileName; 
    ofn.nMaxFile = 1024; 
    ofn.lpstrFileTitle = NULL; 
    ofn.nMaxFileTitle = 0; 
    ofn.lpstrInitialDir = pDir; 
    ofn.lpstrTitle = pTitle; 
    ofn.Flags = OFN_EXPLORER | OFN_ENABLESIZING | OFN_ENABLETEMPLATE | OFN_ENABLEHOOK | OFN_HIDEREADONLY | (mustExist ? OFN_FILEMUSTEXIST : 0); 
    ofn.nFileOffset = 0; 
    ofn.nFileExtension = 0; 
    ofn.lpstrDefExt = NULL; 
    ofn.lCustData = 0; 
    ofn.lpfnHook = hookRomProc; 
    ofn.lpTemplateName = MAKEINTRESOURCE(IDD_OPEN_ROMDROPDOWN); 

    rv = GetOpenFileName(&ofn); 

    if (!rv) {
        return NULL; 
    }

    if (filterIndex) {
        *filterIndex = ofn.nFilterIndex;
    }

    if (pDir != NULL) {
        GetCurrentDirectory(MAX_PATH - 1, pDir);
    }

    file = fopen(pFileName, "r");
    if (file != NULL) {
        fclose(file);
    }
    else {
        if (defExt) {
            if (strlen(pFileName) <= strlen(defExt)) {
                strcat(pFileName, defExt);
            }
            else {
                char* pos = pFileName + strlen(pFileName) - strlen(defExt);
                int  len  = strlen(defExt);
                while (len--) {
                    if (toupper(pos[len]) != toupper(defExt[len])) {
                        break;
                    }
                }
                if (len >= 0) {
                    strcat(pFileName, defExt);
                }
            }
        }
        file = fopen(pFileName, "a+");
        if (file != NULL) {
            fclose(file);
        }
    }

    *romType = openRomType;

    return pFileName; 
} 

UINT_PTR CALLBACK hookProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    switch (iMsg) {
    case WM_TIMER:
        if (wParam == 13) {
            updateDialogPos(GetParent(hDlg), DLG_ID_OPEN, 0, 0);
            KillTimer(hDlg, 13);
            ShowWindow(GetParent(hDlg), SW_NORMAL);
        }
        return 0;

    case WM_INITDIALOG:
        ShowWindow(GetParent(hDlg), SW_HIDE);
        updateDialogPos(hDlg, DLG_ID_OPEN, 0, 1);
        SetTimer(hDlg, 13, 250, 0);
        return 0;

    case WM_DESTROY:
        saveDialogPos(GetParent(hDlg), DLG_ID_OPEN);
        return 0;
    }

    return 0;
}

char* openFile(HWND hwndOwner, _TCHAR* pTitle, char* pFilter, char* pDir, int mustExist, 
               char* defExt, int* filterIndex)
{ 
    OPENFILENAME ofn; 
    BOOL rv; 
    static char pFileName[MAX_PATH];
    FILE* file;

    pFileName[0] = 0; 

    ofn.lStructSize = sizeof(OPENFILENAME); 
    ofn.hwndOwner = hwndOwner; 
    ofn.hInstance = (HINSTANCE)GetModuleHandle(NULL); 
    ofn.lpstrFilter = pFilter ? pFilter : "*.*\0\0"; 
    ofn.lpstrCustomFilter = NULL; 
    ofn.nMaxCustFilter = 0; 
    ofn.nFilterIndex = filterIndex ? *filterIndex : 0; 
    ofn.lpstrFile = pFileName; 
    ofn.nMaxFile = 1024; 
    ofn.lpstrFileTitle = NULL; 
    ofn.nMaxFileTitle = 0; 
    ofn.lpstrInitialDir = pDir; 
    ofn.lpstrTitle = pTitle; 
    ofn.Flags = OFN_EXPLORER | OFN_ENABLESIZING | OFN_ENABLEHOOK | OFN_HIDEREADONLY | (mustExist ? OFN_FILEMUSTEXIST : 0); 
    ofn.nFileOffset = 0; 
    ofn.nFileExtension = 0; 
    ofn.lpstrDefExt = NULL; 
    ofn.lCustData = 0; 
    ofn.lpfnHook = hookProc; 
    ofn.lpTemplateName = NULL; 

    rv = GetOpenFileName(&ofn); 

    if (!rv) {
        return NULL; 
    }

    if (filterIndex) {
        *filterIndex = ofn.nFilterIndex;
    }

    if (pDir != NULL) {
        GetCurrentDirectory(MAX_PATH - 1, pDir);
    }

    file = fopen(pFileName, "r");
    if (file != NULL) {
        fclose(file);
    }
    else {
        if (defExt) {
            if (strlen(pFileName) <= strlen(defExt)) {
                strcat(pFileName, defExt);
            }
            else {
                char* pos = pFileName + strlen(pFileName) - strlen(defExt);
                int  len  = strlen(defExt);
                while (len--) {
                    if (toupper(pos[len]) != toupper(defExt[len])) {
                        break;
                    }
                }
                if (len >= 0) {
                    strcat(pFileName, defExt);
                }
            }
        }
        file = fopen(pFileName, "a+");
        if (file != NULL) {
            char data[1024];
            int i;
            memset(data, 0, 1024);
            for (i = 0; i < 720; i++) {
                fwrite(data, 1, 1024, file);
            }
            fclose(file);
        }
    }

    return pFileName; 
} 

char* saveFile(HWND hwndOwner, _TCHAR* pTitle, char* pFilter, int* pFilterIndex, char* pDir) { 
    OPENFILENAME ofn; 
    BOOL rv; 
    static char pFileName[MAX_PATH]; 
    pFileName[0] = 0; 

    ofn.lStructSize = sizeof(OPENFILENAME); 
    ofn.hwndOwner = hwndOwner; 
    ofn.hInstance = (HINSTANCE)GetModuleHandle(NULL); 
    ofn.lpstrFilter = pFilter ? pFilter : "*.*\0\0"; 
    ofn.lpstrCustomFilter = NULL; 
    ofn.nMaxCustFilter = 0; 
    ofn.nFilterIndex = pFilterIndex ? *pFilterIndex : 0; 
    ofn.lpstrFile = pFileName; 
    ofn.nMaxFile = 1024; 
    ofn.lpstrFileTitle = NULL; 
    ofn.nMaxFileTitle = 0; 
    ofn.lpstrInitialDir = pDir; 
    ofn.lpstrTitle = pTitle; 
    ofn.Flags = OFN_EXPLORER | OFN_ENABLESIZING | OFN_HIDEREADONLY | OFN_ENABLEHOOK; 
    ofn.nFileOffset = 0; 
    ofn.nFileExtension = 0; 
    ofn.lpstrDefExt = NULL; 
    ofn.lCustData = 0; 
    ofn.lpfnHook = hookProc; 
    ofn.lpTemplateName = NULL; 

    rv = GetSaveFileName(&ofn); 

    if (!rv) { 
        return NULL; 
    } 

    if (pFilterIndex) {
        *pFilterIndex = ofn.nFilterIndex;
    }

    if (pDir != NULL) {
        GetCurrentDirectory(MAX_PATH - 1, pDir);
    }

    return pFileName; 
} 


