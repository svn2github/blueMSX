/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32.c,v $
**
** $Revision: 1.31 $
**
** $Date: 2005-01-16 06:48:17 $
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
#define DIRECTINPUT_VERSION     0x0700

#include <windows.h>
#include <tchar.h>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <CommCtrl.h>

#include "Win32FileTypes.h"
#include "Win32ThemeClassic.h"
#include "Board.h"
#include "Led.h"
#include "Switches.h"
#include "audioMixer.h"
#include "videoRender.h"
#include "CommandLine.h"
#include "Language.h"   
#include "resource.h"
#include "Casette.h"
#include "JoystickIO.h"
#include "RomLoader.h"
#include "build_number.h"

#include "Win32Sound.h"
#include "Win32Properties.h"
#include "Win32joystick.h"
#include "Win32keyboard.h"
#include "Win32directx.h"
#include "FileHistory.h"
#include "Win32Dir.h"
#include "Win32Help.h"
#include "Win32Menu.h"
#include "Win32ScreenShot.h"
#include "Win32MouseEmu.h"
#include "Win32machineConfig.h"
#include "Win32ShortcutsConfig.h"
#include "Actions.h"
#include "LaunchFile.h"
#include "TokenExtract.h"
#include "Emulator.h"
#include "Keyboard.h"
#include "Theme.h"
#include "ThemeLoader.h"
#include "Win32ThemeClassic.h"
#include "ArchNotifications.h"

void vdpSetDisplayEnable(int enable);

void centerDialog(HWND hwnd, int noActivate) {
    RECT r1;
    RECT r2;
    int x;
    int y;

    GetWindowRect(GetParent(hwnd), &r1);
    GetWindowRect(hwnd, &r2);

    x = r1.left + (r1.right - r1.left - r2.right + r2.left) / 2;
    y = r1.top  + (r1.bottom - r1.top - r2.bottom + r2.top) / 2;
    SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | (noActivate ? SWP_NOACTIVATE : 0));
}

void updateDialogPos(HWND hwnd, int dialogID, int noMove, int noSize) 
{
    Properties* pProperties = propGetGlobalProperties();

    int screenWidth  = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    RECT r;
    int x;
    int y;
    int w;
    int h;

    if (pProperties->video.size == P_VIDEO_SIZEFULLSCREEN) {
        noMove = 1;
        noSize = 1;
    }

    r.left   = pProperties->settings.windowPos[dialogID].left; 
    r.top    = pProperties->settings.windowPos[dialogID].top; 
    r.right  = pProperties->settings.windowPos[dialogID].right; 
    r.bottom = pProperties->settings.windowPos[dialogID].bottom; 

    x = r.left;
    y = r.top;
    w = r.right - r.left;
    h = r.bottom - r.top;

    if (noMove || (x == 0 && y == 0)) {
        RECT r1;
        RECT r2;

        GetWindowRect(GetParent(hwnd), &r1);
        GetWindowRect(hwnd, &r2);

        x = r1.left + (r1.right - r1.left - r2.right + r2.left) / 2;
        y  = r1.top  + (r1.bottom - r1.top - r2.bottom + r2.top) / 2;
    }
    
    if (r.right == 0 || r.bottom == 0) {
        RECT r1;
        GetWindowRect(hwnd, &r1);
        w = r1.right - r1.left;
        h = r1.bottom - r1.top;
    }

    if (x + w > screenWidth) {
        x = screenWidth - w;
    }

    if (y + h > screenHeight) {
        y = screenHeight - h;
    }

    if (y < 0) {
        y = 0;
    }

    SetWindowPos(hwnd, NULL, x, y, w, h, SWP_NOZORDER | (noSize ? SWP_NOSIZE : 0));
}

void saveDialogPos(HWND hwnd, int dialogID)
{
    Properties* pProperties = propGetGlobalProperties();
    RECT r;

    if (pProperties->video.size != P_VIDEO_SIZEFULLSCREEN) {
        GetWindowRect(hwnd, &r);

        pProperties->settings.windowPos[dialogID].left   = r.left;
        pProperties->settings.windowPos[dialogID].top    = r.top;
        pProperties->settings.windowPos[dialogID].right  = r.right;
        pProperties->settings.windowPos[dialogID].bottom = r.bottom;
    }
}

///////////////////////////////////////////////////////////////////////////

#define WM_SHOWDSKWIN        (WM_USER + 1248)

#define TIMER_DSKDIALOGSHOW 20

static BOOL CALLBACK dskProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    static int show = 0;

    switch (iMsg) {
    case WM_INITDIALOG:
        centerDialog(hDlg, 0);
        return FALSE;

    case WM_SHOWDSKWIN:
        {
            Properties* pProperties = propGetGlobalProperties();
            RECT r1;
            RECT r2;
            int x;
            int y;

            GetWindowRect(GetParent(hDlg), &r1);
            GetWindowRect(hDlg, &r2);

            x = r1.left + (r1.right - r1.left - r2.right + r2.left) / 2;
            y = r1.top  + (r1.bottom - r1.top - r2.bottom + r2.top) / 2;

            SetWindowText(GetDlgItem(hDlg, IDC_DISKIMAGE), 
                          stripPath(*pProperties->diskdrive.slotAZip ? 
                          pProperties->diskdrive.slotAZip : pProperties->diskdrive.slotA));
            if (!show) {
                enterDialogShow();
                SetWindowPos(hDlg, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
                show = 1;
            }
            SetTimer(hDlg, TIMER_DSKDIALOGSHOW, 1000, NULL);
            
            centerDialog(hDlg, 1);
        }
        return TRUE;

    case WM_TIMER:
        ShowWindow(hDlg, SW_HIDE);
        KillTimer(hDlg, TIMER_DSKDIALOGSHOW);
    
        show = 0;
        exitDialogShow();
        return TRUE;
    }
    return FALSE;
}

typedef void* DiskQuickviewWindow;

DiskQuickviewWindow* diskQuickviewWindowCreate(HWND parent) {
    return (DiskQuickviewWindow*)CreateDialog(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DISKIMAGE), parent, dskProc);
}

void diskQuickviewWindowDestroy(DiskQuickviewWindow* dqw)
{
    DestroyWindow((HWND)dqw);
}

void diskQuickviewWindowShow(DiskQuickviewWindow* dqw)
{
    SendMessage((HWND)dqw, WM_SHOWDSKWIN, 0, 0);
}

///////////////////////////////////////////////////////////////////////////

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
    ROM_MOONSOUND,
    ROM_DISKPATCH,
    ROM_CASPATCH,
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
    ROM_UNKNOWN,
};

static void updateRomTypeList(HWND hDlg, ZipFileDlgInfo* dlgInfo) {
    char fileName[MAX_PATH];
    int size;
    char* buf = NULL;
    int index;

    index = SendDlgItemMessage(hDlg, IDC_DSKLIST, LB_GETCURSEL, 0, 0);
    SendDlgItemMessage(hDlg, IDC_DSKLIST, LB_GETTEXT, index, (LPARAM)fileName);
    
    if (isFileExtension(fileName, ".rom") || isFileExtension(fileName, ".mx1") || isFileExtension(fileName, ".mx2")) {
        buf = romLoad(dlgInfo->zipFileName, fileName, &size);
    }

    if (buf != NULL) {
        RomType romType = romMapperGuessRom(buf, size, 0, NULL);
        int idx = 0;

        while (romTypeList[idx] != romType) {
            idx++;
        }

        SendMessage(GetDlgItem(hDlg, IDC_OPEN_ROMTYPE), CB_SETCURSEL, idx, 0);

        free(buf);

        dlgInfo->openRomType = romType;

        EnableWindow(GetDlgItem(hDlg, IDC_OPEN_ROMTYPE), 1);
        EnableWindow(GetDlgItem(hDlg, IDC_OPEN_ROMTEXT), 1);
    }    
    else {
        dlgInfo->openRomType = ROM_UNKNOWN;
        EnableWindow(GetDlgItem(hDlg, IDC_OPEN_ROMTYPE), 0);
        EnableWindow(GetDlgItem(hDlg, IDC_OPEN_ROMTEXT), 0);
        SendMessage(GetDlgItem(hDlg, IDC_OPEN_ROMTYPE), CB_SETCURSEL, -1, 0);
    }
}

static BOOL CALLBACK dskZipDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    static ZipFileDlgInfo* dlgInfo;

    switch (iMsg) {
    case WM_DESTROY:
        saveDialogPos(hDlg, DLG_ID_ZIPOPEN);
        return 0;

    case WM_INITDIALOG:
        {
            char* fileList;
            int sel = 0;
            int i;
            
            updateDialogPos(hDlg, DLG_ID_ZIPOPEN, 0, 1);

            dlgInfo = (ZipFileDlgInfo*)lParam;

            dlgInfo->openRomType = ROM_UNKNOWN;

            SetWindowText(hDlg, dlgInfo->title);

            SendMessage(GetDlgItem(hDlg, IDC_DSKLOADTXT), WM_SETTEXT, 0, (LPARAM)dlgInfo->description);
            SetWindowText(GetDlgItem(hDlg, IDC_DSKRESET), langDlgZipReset());
            SetWindowText(GetDlgItem(hDlg, IDOK), langDlgOK());
            SetWindowText(GetDlgItem(hDlg, IDCANCEL), langDlgCancel());
            SetWindowText(GetDlgItem(hDlg, IDC_OPEN_ROMTEXT), langDlgRomType());

            fileList = dlgInfo->fileList;

            for (i = 0; romTypeList[i] != ROM_UNKNOWN; i++) {
                SendDlgItemMessage(hDlg, IDC_OPEN_ROMTYPE, CB_ADDSTRING, 0, (LPARAM)romTypeToString(romTypeList[i]));
                SendDlgItemMessage(hDlg, IDC_ROMTYPE, CB_SETCURSEL, i, 0);
            }
            SendDlgItemMessage(hDlg, IDC_OPEN_ROMTYPE, CB_ADDSTRING, 0, (LPARAM)romTypeToString(ROM_UNKNOWN));
            EnableWindow(GetDlgItem(hDlg, IDC_OPEN_ROMTYPE), 0);
            EnableWindow(GetDlgItem(hDlg, IDC_OPEN_ROMTEXT), 0);

            if (dlgInfo->selectFileIndex != -1) {
                sel = dlgInfo->selectFileIndex;
            }

            for (i = 0; i < dlgInfo->fileListCount; i++) {
                if (dlgInfo->selectFileIndex != -1 && 0 == strcmp(dlgInfo->selectFile, fileList)) {
                    sel = i;
                }
                SendMessage(GetDlgItem(hDlg, IDC_DSKLIST), LB_ADDSTRING, 0, (LPARAM)fileList);
                fileList += strlen(fileList) + 1;
            }

            if (dlgInfo->autoReset == -1) {
                ShowWindow(GetDlgItem(hDlg, IDC_DSKRESET), SW_HIDE);
            }
            else {
                SendMessage(GetDlgItem(hDlg, IDC_DSKRESET), BM_SETCHECK, dlgInfo->autoReset ? BST_CHECKED : BST_UNCHECKED, 0);
            }
            SendDlgItemMessage(hDlg, IDC_DSKLIST, LB_SETCURSEL, sel, 0);
        
            updateRomTypeList(hDlg, dlgInfo);

            return FALSE;
        }

    case WM_COMMAND:
        switch(LOWORD(wParam)) {
        case IDC_OPEN_ROMTYPE:
            if (HIWORD(wParam) == 1 || HIWORD(wParam) == 2) {
                int idx = SendMessage(GetDlgItem(hDlg, IDC_OPEN_ROMTYPE), CB_GETCURSEL, 0, 0);

                dlgInfo->openRomType = idx == CB_ERR ? -1 : romTypeList[idx];
            }
            return 0;
        case IDC_DSKRESET:
            if (dlgInfo->autoReset == 1) {
                SendMessage(GetDlgItem(hDlg, IDC_DSKRESET), BM_SETCHECK, BST_UNCHECKED, 0);
                dlgInfo->autoReset = 0;
            }
            else if (dlgInfo->autoReset == 0) {
                SendMessage(GetDlgItem(hDlg, IDC_DSKRESET), BM_SETCHECK, BST_CHECKED, 1);
                dlgInfo->autoReset = 1;
            }
            break;
        case IDC_DSKLIST:
            switch (HIWORD(wParam)) {
            case LBN_SELCHANGE:
                updateRomTypeList(hDlg, dlgInfo);
                break;
            }

            if (HIWORD(wParam) != LBN_DBLCLK) {
                break;
            }
            // else, fall through
        case IDOK:
            dlgInfo->selectFileIndex = SendMessage(GetDlgItem(hDlg, IDC_DSKLIST), LB_GETCURSEL, 0, 0);
            SendMessage(GetDlgItem(hDlg, IDC_DSKLIST), LB_GETTEXT, dlgInfo->selectFileIndex, (LPARAM)dlgInfo->selectFile);
            EndDialog(hDlg, TRUE);
            return TRUE;
        case IDCANCEL:
            dlgInfo->selectFileIndex = -1;
            dlgInfo->selectFile[0] = '\0';
            EndDialog(hDlg, FALSE);
            return TRUE;
        }
        break;
    case WM_CLOSE:
        dlgInfo->selectFileIndex = -1;
        dlgInfo->selectFile[0] = '\0';
        EndDialog(hDlg, FALSE);
        return TRUE;
    }

    return FALSE;
}

////////////////////////////////////////////////////////////////////

static char* convertTapePos(int tapePos)
{
    static char str[64];
    int pos = tapePos / 128;

    _stprintf(str, "%dh %02dm %02ds", pos / 3600, (pos / 60) % 60, pos % 60);
    return str;
}

static void tapeDlgUpdate(HWND hwnd, TapeContent* tc, int tcCount, int showCustomFiles) 
{
    static char* typeNames[] = { "ASCII", "BIN", "BAS", "Custom" };
    int curPos;
    int i;
    int idx = 0;

    ListView_DeleteAllItems(hwnd);

    curPos = tapeGetCurrentPos();

    for (i = 0; i < tcCount; i++) {
        char buffer[64] = {0};
        LV_ITEM lvi = {0};

        if (showCustomFiles || tc[i].type != TAPE_CUSTOM) {
            lvi.mask       = LVIF_TEXT;
            lvi.iItem      = idx;
            lvi.pszText    = buffer;
	        lvi.cchTextMax = 64;
            
            sprintf(buffer, convertTapePos(tc[i].pos));
            ListView_InsertItem(hwnd, &lvi);
            lvi.iSubItem++;
            
            sprintf(buffer, typeNames[tc[i].type]);
            ListView_SetItem(hwnd, &lvi);
            lvi.iSubItem++;
            
            sprintf(buffer, tc[i].fileName);
            ListView_SetItem(hwnd, &lvi);

            if (tc[i].pos <= curPos) {
                SetFocus(hwnd);
                ListView_SetItemState(hwnd, idx, LVIS_SELECTED, LVIS_SELECTED);
            }
            idx++;
        }
    }
}


static BOOL CALLBACK tapePosDlg(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    static int currIndex;
    static HWND hwnd;
    static TapeContent* tc;
    static int* showCustomFiles;
    static int tcCount;

    switch (iMsg) {
    case WM_DESTROY:
        saveDialogPos(hDlg, DLG_ID_TAPEPOS);
        return 0;

    case WM_INITDIALOG:
        {
            char buffer[32];
            LV_COLUMN lvc = {0};

            showCustomFiles = (int*)lParam;
         
            updateDialogPos(hDlg, DLG_ID_TAPEPOS, 0, 1);

            currIndex = -1;

            SetWindowText(hDlg, langDlgTapeTitle());

            SendMessage(GetDlgItem(hDlg, IDC_SETTAPEPOSTXT), WM_SETTEXT, 0, (LPARAM)langDlgTapeSetPosText());
            SetWindowText(GetDlgItem(hDlg, IDC_SETTAPECUSTOM), langDlgTapeCustom());
            SetWindowText(GetDlgItem(hDlg, IDOK), langDlgOK());
            SetWindowText(GetDlgItem(hDlg, IDCANCEL), langDlgCancel());

            SendMessage(GetDlgItem(hDlg, IDC_SETTAPECUSTOM), BM_SETCHECK, *showCustomFiles ? BST_CHECKED : BST_UNCHECKED, 0);

            tc = tapeGetContent(&tcCount);
    
            hwnd = GetDlgItem(hDlg, IDC_SETTAPELIST);

            EnableWindow(GetDlgItem(hDlg, IDOK), FALSE);

            ListView_SetExtendedListViewStyle(hwnd, LVS_EX_FULLROWSELECT);

            lvc.mask       = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
            lvc.fmt        = LVCFMT_LEFT;
            lvc.cx         = 100;
            lvc.pszText    = buffer;
	        lvc.cchTextMax = 32;

            sprintf(buffer, langDlgTabPosition());
            lvc.cx = 95;
            ListView_InsertColumn(hwnd, 0, &lvc);
            sprintf(buffer, langDlgTabType());
            lvc.cx = 65;
            ListView_InsertColumn(hwnd, 1, &lvc);
            sprintf(buffer, langDlgTabFilename());
            lvc.cx = 105;
            ListView_InsertColumn(hwnd, 2, &lvc);
        }

        tapeDlgUpdate(hwnd, tc, tcCount, *showCustomFiles);
        return FALSE;

    case WM_NOTIFY:
        switch (wParam) {
        case IDC_SETTAPELIST:
            if ((((NMHDR FAR *)lParam)->code) == LVN_ITEMCHANGED) {
                if (ListView_GetSelectedCount(hwnd)) {
                    int index = ListView_GetNextItem(hwnd, -1, LVNI_SELECTED);

                    if (currIndex == -1 && index != -1) {
                        EnableWindow(GetDlgItem(hDlg, IDOK), TRUE);
                    }
                    currIndex = index;
                }
                else {
                    if (currIndex != -1) {
                        EnableWindow(GetDlgItem(hDlg, IDOK), FALSE);
                    }
                    currIndex = -1;
                }
            }
            if ((((NMHDR FAR *)lParam)->code) == LVN_ITEMACTIVATE) {
                if (ListView_GetSelectedCount(hwnd)) {
                    int index = ListView_GetNextItem(hwnd, -1, LVNI_SELECTED);
                    SendMessage(hDlg, WM_COMMAND, IDOK, 0);
                }
                return TRUE;
            }
        }
        break;

    case WM_COMMAND:
        switch(LOWORD(wParam)) {
        case IDC_SETTAPECUSTOM:
            {
                *showCustomFiles = BST_CHECKED == SendMessage(GetDlgItem(hDlg, IDC_SETTAPECUSTOM), BM_GETCHECK, 0, 0);
                tapeDlgUpdate(GetDlgItem(hDlg, IDC_SETTAPELIST), tc, tcCount, *showCustomFiles);
            }
            return TRUE;

        case IDCANCEL:
            EndDialog(hDlg, FALSE);
            return TRUE;

        case IDOK:
            {
                int index = 0;
                int i;

                if (ListView_GetSelectedCount(hwnd)) {
                    currIndex = ListView_GetNextItem(hwnd, -1, LVNI_SELECTED);
                }

                for (i = 0; i < tcCount; i++) {
                    if (*showCustomFiles || tc[i].type != TAPE_CUSTOM) {
                        if (currIndex == index) {
                            tapeSetCurrentPos(tc[i].pos);
                        }
                        index++;
                    }
                }
             
                EndDialog(hDlg, TRUE);
            }
            return TRUE;
        }
        return FALSE;

    case WM_CLOSE:
        EndDialog(hDlg, FALSE);
        return TRUE;
    }

    return FALSE;
}

void setTapePosition(HWND parent, Properties* pProperties) {
    if (emulatorGetState() != EMU_STOPPED) {
        emulatorSuspend();
    }
    else {
        tapeSetReadOnly(1);
        boardChangeCassette(strlen(pProperties->cassette.tape) ? pProperties->cassette.tape : NULL, 
                            strlen(pProperties->cassette.tapeZip) ? pProperties->cassette.tapeZip : NULL);
    }

    DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SETTAPEPOS), parent, tapePosDlg, (LPARAM)&pProperties->cassette.showCustomFiles);

    if (emulatorGetState() != EMU_STOPPED) {
        emulatorResume();
    }
    else {
        boardChangeCassette(NULL, NULL);
        tapeSetReadOnly(pProperties->cassette.readOnly);
    }
}

///////////////////////////////////////////////////////////////////////////

#define hotkeyEq(hotkey1, hotkey2) (*(DWORD*)&hotkey1 == *(DWORD*)&hotkey2)

static int maxSpeedIsSet = 0;

static void checkKeyDown(Shortcuts* s, ShotcutHotkey key) {
    if (hotkeyEq(key, s->emuSpeedFull)) {
        actionMaxSpeedSet();
        maxSpeedIsSet = 1;

    }
}

static void checkKeyUp(Shortcuts* s, ShotcutHotkey key) 
{
    if (maxSpeedIsSet) {
        actionMaxSpeedRelease();
        maxSpeedIsSet = 0;
    }

    if (hotkeyEq(key, s->spritesEnable))                actionToggleSpriteEnable();
    if (hotkeyEq(key, s->fdcTiming))                    actionToggleFdcTiming();
    if (hotkeyEq(key, s->msxAudioSwitch))               actionToggleMsxAudioSwitch();
    if (hotkeyEq(key, s->frontSwitch))                  actionToggleFrontSwitch();
    if (hotkeyEq(key, s->pauseSwitch))                  actionTogglePauseSwitch();
    if (hotkeyEq(key, s->quit))                         actionQuit();
    if (hotkeyEq(key, s->wavCapture))                   actionToggleWaveCapture();
    if (hotkeyEq(key, s->screenCapture))                actionScreenCapture();
    if (hotkeyEq(key, s->screenCaptureUnfilteredSmall)) actionScreenCaptureUnfilteredSmall();
    if (hotkeyEq(key, s->screenCaptureUnfilteredLarge)) actionScreenCaptureUnfilteredLarge();
    if (hotkeyEq(key, s->cpuStateLoad))                 actionLoadState();
    if (hotkeyEq(key, s->cpuStateSave))                 actionSaveState();
    if (hotkeyEq(key, s->cpuStateQuickLoad))            actionQuickLoadState();
    if (hotkeyEq(key, s->cpuStateQuickSave))            actionQuickSaveState();
    if (hotkeyEq(key, s->cartInsert1))                  actionCartInsert1();
    if (hotkeyEq(key, s->cartInsert2))                  actionCartInsert2();
    if (hotkeyEq(key, s->cartSpecialMenu1))             actionMenuSpecialCart1(-1, -1);
    if (hotkeyEq(key, s->cartSpecialMenu2))             actionMenuSpecialCart2(-1, -1);
    if (hotkeyEq(key, s->diskInsertA))                  actionDiskInsertA();
    if (hotkeyEq(key, s->diskInsertB))                  actionDiskInsertB();
    if (hotkeyEq(key, s->diskDirInsertA))               actionDiskDirInsertA();
    if (hotkeyEq(key, s->diskDirInsertB))               actionDiskDirInsertB();
    if (hotkeyEq(key, s->diskChangeA))                  actionDiskQuickChange();
    if (hotkeyEq(key, s->casInsert))                    actionCasInsert();
    if (hotkeyEq(key, s->casRewind))                    actionCasRewind();
    if (hotkeyEq(key, s->casSetPos))                    actionCasSetPosition();
    if (hotkeyEq(key, s->mouseLockToggle))              actionToggleMouseCapture();
    if (hotkeyEq(key, s->emulationRunPause))            actionEmuTogglePause();
    if (hotkeyEq(key, s->emulationStop))                actionEmuStop();
    if (hotkeyEq(key, s->emuSpeedNormal))               actionEmuSpeedNormal();
    if (hotkeyEq(key, s->emuSpeedInc))                  actionEmuSpeedDecrease();
    if (hotkeyEq(key, s->emuSpeedToggle))               actionMaxSpeedToggle();
    if (hotkeyEq(key, s->emuSpeedDec))                  actionEmuSpeedIncrease();
    if (hotkeyEq(key, s->windowSizeSmall))              actionWindowSizeSmall();
    if (hotkeyEq(key, s->windowSizeNormal))             actionWindowSizeNormal();
    if (hotkeyEq(key, s->windowSizeMinimized))          actionWindowSizeMinimized();
    if (hotkeyEq(key, s->windowSizeFullscreen))         actionWindowSizeFullscreen();
    if (hotkeyEq(key, s->windowSizeFullscreenToggle))   actionFullscreenToggle();
    if (hotkeyEq(key, s->resetSoft))                    actionEmuResetSoft();
    if (hotkeyEq(key, s->resetHard))                    actionEmuResetHard();
    if (hotkeyEq(key, s->resetClean))                   actionEmuResetClean();
    if (hotkeyEq(key, s->volumeIncrease))               actionVolumeIncrease();
    if (hotkeyEq(key, s->volumeDecrease))               actionVolumeDecrease();
    if (hotkeyEq(key, s->volumeMute))                   actionMuteToggleMaster();
    if (hotkeyEq(key, s->volumeStereo))                 actionVolumeToggleStereo();
    if (hotkeyEq(key, s->cpuTrace))                     actionCpuTraceToggle();
    if (hotkeyEq(key, s->themeSwitch))                  actionNextTheme();
    if (hotkeyEq(key, s->casRemove))                    actionCasRemove();
    if (hotkeyEq(key, s->diskRemoveA))                  actionDiskRemoveA();
    if (hotkeyEq(key, s->diskRemoveB))                  actionDiskRemoveB();
    if (hotkeyEq(key, s->cartRemove1))                  actionCartRemove1();
    if (hotkeyEq(key, s->cartRemove2))                  actionCartRemove2();
    if (hotkeyEq(key, s->cartAutoReset))                actionToggleCartAutoReset();
    if (hotkeyEq(key, s->diskAutoResetA))               actionToggleDiskAutoResetA();
    if (hotkeyEq(key, s->casToggleReadonly))            actionCasToggleReadonly();
    if (hotkeyEq(key, s->casAutoRewind))                actionToggleCasAutoRewind();
    if (hotkeyEq(key, s->casSave))                      actionCasSave();
    if (hotkeyEq(key, s->propShowEmulation))            actionPropShowEmulation();
    if (hotkeyEq(key, s->propShowVideo))                actionPropShowVideo();
    if (hotkeyEq(key, s->propShowAudio))                actionPropShowAudio();
    if (hotkeyEq(key, s->propShowControls))             actionPropShowControls();
    if (hotkeyEq(key, s->propShowPerformance))          actionPropShowPerformance();
    if (hotkeyEq(key, s->propShowSettings))             actionPropShowSettings();
    if (hotkeyEq(key, s->propShowApearance))            actionPropShowApearance();
    if (hotkeyEq(key, s->optionsShowLanguage))          actionOptionsShowLanguage();
    if (hotkeyEq(key, s->toolsShowMachineEditor))       actionToolsShowMachineEditor();
    if (hotkeyEq(key, s->toolsShowShorcutEditor))       actionToolsShowShorcutEditor();
    if (hotkeyEq(key, s->helpShowHelp))                 actionHelpShowHelp();
    if (hotkeyEq(key, s->helpShowAbout))                actionHelpShowAbout();
}

static void updateVideoRender(Video* pVideo, Properties* pProperties) {
    videoSetDeInterlace(pVideo, pProperties->video.deInterlace);

    switch (pProperties->video.monType) {
    case P_VIDEO_COLOR:
        videoSetColorMode(pVideo, VIDEO_COLOR);
        break;
    case P_VIDEO_BW:
        videoSetColorMode(pVideo, VIDEO_BLACKWHITE);
        break;
    case P_VIDEO_GREEN:
        videoSetColorMode(pVideo, VIDEO_GREEN);
        break;
    }

    switch (pProperties->video.palEmu) {
    case P_VIDEO_PALNONE:
        videoSetPalMode(pVideo, VIDEO_PAL_FAST);
        break;
    case P_VIDEO_PALMON:
        videoSetPalMode(pVideo, VIDEO_PAL_MONITOR);
        break;
    case P_VIDEO_PALYC:
        videoSetPalMode(pVideo, VIDEO_PAL_SHARP);
        break;
    case P_VIDEO_PALNYC:
        videoSetPalMode(pVideo, VIDEO_PAL_SHARP_NOISE);
        break;
    case P_VIDEO_PALCOMP:
        videoSetPalMode(pVideo, VIDEO_PAL_BLUR);
        break;
    case P_VIDEO_PALNCOMP:
        videoSetPalMode(pVideo, VIDEO_PAL_BLUR_NOISE);
        break;
	case P_VIDEO_PALSCALE2X:
		videoSetPalMode(pVideo, VIDEO_PAL_SCALE2X);
		break;
	case P_VIDEO_PALHQ2X:
		videoSetPalMode(pVideo, VIDEO_PAL_HQ2X);
		break;
	case P_VIDEO_PAL_STRETCHED:
		videoSetPalMode(pVideo, VIDEO_PAL_STRETCHED);
		break;
    }

    videoSetFrameSkip(pVideo, pProperties->video.frameSkip);
}

void updateJoystick(Properties* pProperties) {    
    switch (pProperties->joy1.type) {
    case P_JOY_NONE:
    case P_JOY_MOUSE:
        JoystickSetType(0, JOY_NONE, 0);
        break;
    case P_JOY_NUMPAD:
        JoystickSetType(0, JOY_NUMPAD, 0);
        break;
    case P_JOY_KEYSET:
        JoystickSetType(0, JOY_KEYSET, 0);
        break;
    case P_JOY_HW:
        JoystickSetType(0, JOY_HW, pProperties->joy1.hwType);
        JoystickSetHwButtons(0, pProperties->joy1.hwButtonA, pProperties->joy1.hwButtonB);
        break;
    }

    switchSetRensha(pProperties->joy1.autofire);

    switch (pProperties->joy2.type) {
    case P_JOY_NONE:
    case P_JOY_MOUSE:
        JoystickSetType(1, JOY_NONE, 0);
        break;
    case P_JOY_NUMPAD:
        JoystickSetType(1, JOY_NUMPAD, 0);
        break;
    case P_JOY_KEYSET:
        JoystickSetType(1, JOY_KEYSET, 1);
        break;
    case P_JOY_HW:
        JoystickSetType(1, JOY_HW, pProperties->joy2.hwType);
        JoystickSetHwButtons(1, pProperties->joy1.hwButtonA, pProperties->joy1.hwButtonB);
        break;
    }

    JoystickSetKeyStateKey(1, JOY_UP,    pProperties->joy1.keyUp);
    JoystickSetKeyStateKey(1, JOY_DOWN,  pProperties->joy1.keyDown);
    JoystickSetKeyStateKey(1, JOY_LEFT,  pProperties->joy1.keyLeft);
    JoystickSetKeyStateKey(1, JOY_RIGHT, pProperties->joy1.keyRight);
    JoystickSetKeyStateKey(1, JOY_BT1,   pProperties->joy1.button1);
    JoystickSetKeyStateKey(1, JOY_BT2,   pProperties->joy1.button2);

    JoystickSetKeyStateKey(2, JOY_UP,    pProperties->joy2.keyUp);
    JoystickSetKeyStateKey(2, JOY_DOWN,  pProperties->joy2.keyDown);
    JoystickSetKeyStateKey(2, JOY_LEFT,  pProperties->joy2.keyLeft);
    JoystickSetKeyStateKey(2, JOY_RIGHT, pProperties->joy2.keyRight);
    JoystickSetKeyStateKey(2, JOY_BT1,   pProperties->joy2.button1);
    JoystickSetKeyStateKey(2, JOY_BT2,   pProperties->joy2.button2);
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


#define WM_UPDATE            (WM_USER + 1245)
#define WM_LAUNCHFILE        (WM_USER + 1249)

#define TIMER_STATUSBAR_UPDATE              10
#define TIMER_POLL_INPUT                    11
#define TIMER_POLL_FRAMECOUNT               12
#define TIMER_SCREENUPDATE                  13
#define TIMER_SCREENSHOT                    14
#define TIMER_SCREENSHOT_UNFILTERED_LARGE   15
#define TIMER_SCREENSHOT_UNFILTERED_SMALL   16
#define TIMER_THEME                         17
#define TIMER_MENUUPDATE                    18
#define TIMER_CLIP_REGION                   19

void  PatchDiskSetBusy(int driveId, int busy);

static void updateMenu(int show);

typedef void (*KbdLockFun)(); 

KbdLockFun kbdLockEnable = NULL;
KbdLockFun kbdLockDisable = NULL;

static Properties* pProperties;

typedef struct {
    HWND emuHwnd;
    HWND hwnd;
    HRGN hrgn;
    int      rgnSize;
    RGNDATA* rgnData;
    int      rgnSizeOrig;
    RGNDATA* rgnDataOrig;
    int      rgnEnable;
    HMENU hMenu;
    int showMenu;
    int trackMenu;
    int showDialog;
    BITMAPINFO bmInfo;
    DiskQuickviewWindow dskWnd;
    
    //
    void* bmBitsGDI;
    int frameCount;
    int framesPerSecond;
    char pCurDir[MAX_PATH];
    Video* pVideo;
    int minimized;
    Mixer* mixer;
    int enteringFullscreen;
    int evenOdd;
    int interlace;
    Shortcuts* shortcuts;
    DWORD buttonState;
    int normalViedoSize;

    HANDLE ddrawEvent;
    HANDLE ddrawAckEvent;

    HBITMAP hBitmap;
    ThemePage* themePageActive;
    ThemeCollection** themeList;
    int themeIndex;
    int X;
    int Y;
} WinState;



#define WIDTH  320
#define HEIGHT 240

#define LAUNCH_TEMP_FILE "launch.tmp"

static WinState st;


static void registerFileTypes() {
    registerFileType(".dsk", "blueMSXdsk", "DSK Image", 1);
    registerFileType(".di1", "blueMSXdsk", "DSK Image", 1);
    registerFileType(".di2", "blueMSXdsk", "DSK Image", 1);
    registerFileType(".rom", "blueMSXrom", "ROM Image", 2);
    registerFileType(".mx1", "blueMSXrom", "ROM Image", 2);
    registerFileType(".mx2", "blueMSXrom", "ROM Image", 2);
    registerFileType(".cas", "blueMSXcas", "CAS Image", 3);
    registerFileType(".sta", "blueMSXsta", "blueMSX State", 4);
}

static void unregisterFileTypes() {
    unregisterFileType(".dsk", "blueMSXdsk", "DSK Image", 1);
    unregisterFileType(".di1", "blueMSXdsk", "DSK Image", 1);
    unregisterFileType(".di2", "blueMSXdsk", "DSK Image", 1);
    unregisterFileType(".rom", "blueMSXrom", "ROM Image", 2);
    unregisterFileType(".mx1", "blueMSXrom", "ROM Image", 2);
    unregisterFileType(".mx2", "blueMSXrom", "ROM Image", 2);
    unregisterFileType(".cas", "blueMSXcas", "CAS Image", 3);
    unregisterFileType(".sta", "blueMSXsta", "blueMSX State", 4);
}

HWND getMainHwnd()
{
    return st.hwnd;
}

void archShowPropertiesDialog(PropPage  startPane) {
    Properties oldProp = *pProperties;
    int restart = 0;
    int changed;
    int i;

    emulatorSetFrequency(50, NULL);
    enterDialogShow();
    propUpdateJoyinfo(pProperties);
    changed = showProperties(pProperties, st.hwnd, startPane, st.mixer, st.pVideo);
    exitDialogShow();
    emulatorSetFrequency(pProperties->emulation.speed, NULL);
    if (!changed) {
        return;
    }

    /* Save properties */
    propSave(pProperties);

    /* Always update video render */
    updateVideoRender(st.pVideo, pProperties);

    /* Always update joystick controls */
    updateJoystick(pProperties);

    /* Update window size only if changed */
    if (pProperties->video.driver != oldProp.video.driver ||
        pProperties->video.fullRes != oldProp.video.fullRes ||
        pProperties->video.size != oldProp.video.size ||
        pProperties->video.horizontalStretch != oldProp.video.horizontalStretch ||
        pProperties->video.verticalStretch != oldProp.video.verticalStretch ||
        strcmp(pProperties->settings.themeName, oldProp.settings.themeName))
    {
        archUpdateWindow();
    }

    joystickIoSetType(0, pProperties->joy1.type == P_JOY_NONE  ? 0 : pProperties->joy1.type == P_JOY_MOUSE ? 2 : 1, pProperties->joy1.type);
    joystickIoSetType(1, pProperties->joy2.type == P_JOY_NONE  ? 0 : pProperties->joy2.type == P_JOY_MOUSE ? 2 : 1, pProperties->joy2.type);

    mouseEmuEnable(pProperties->joy1.type == P_JOY_MOUSE || pProperties->joy2.type == P_JOY_MOUSE);

    /* Must restart MSX if Machine configuration changed */
    if (strcmp(oldProp.emulation.machineName, pProperties->emulation.machineName) ||
        oldProp.emulation.syncMethod != pProperties->emulation.syncMethod ||
        oldProp.emulation.vdpSyncMode != pProperties->emulation.vdpSyncMode)
    {
        restart = 1;
    }

    /* Update switches */
    switchSetAudio(pProperties->emulation.audioSwitch);
    switchSetFront(pProperties->emulation.frontSwitch);
    switchSetPause(pProperties->emulation.pauseSwitch);
    emulatorSetFrequency(pProperties->emulation.speed, NULL);

    /* Update sound only if changed, Must restart if changed */
    if (oldProp.sound.bufSize              != pProperties->sound.bufSize ||
        oldProp.sound.driver               != pProperties->sound.driver  ||
        oldProp.sound.frequency            != pProperties->sound.frequency ||
        oldProp.sound.chip.enableY8950     != pProperties->sound.chip.enableY8950 ||
        oldProp.sound.chip.enableYM2413    != pProperties->sound.chip.enableYM2413 ||
        oldProp.sound.chip.enableMoonsound != pProperties->sound.chip.enableMoonsound ||
        oldProp.sound.stereo               != pProperties->sound.stereo) 
    {
        soundDriverConfig(st.hwnd, pProperties->sound.driver);
        emulatorRestartSound();
    }

    if (oldProp.sound.chip.enableY8950     != pProperties->sound.chip.enableY8950 ||
        oldProp.sound.chip.enableYM2413    != pProperties->sound.chip.enableYM2413 ||
        oldProp.sound.chip.enableMoonsound != pProperties->sound.chip.enableMoonsound)
    {
        boardSetY8950Enable(pProperties->sound.chip.enableY8950);
        boardSetYm2413Enable(pProperties->sound.chip.enableYM2413);
        boardSetMoonsoundEnable(pProperties->sound.chip.enableMoonsound);
        restart = 1;
    }

    for (i = 0; i < MIXER_CHANNEL_TYPE_COUNT; i++) {
        mixerSetChannelTypeVolume(st.mixer, i, pProperties->sound.mixerChannel[i].volume);
        mixerSetChannelTypePan(st.mixer, i, pProperties->sound.mixerChannel[i].pan);
        mixerEnableChannelType(st.mixer, i, pProperties->sound.mixerChannel[i].enable);
    }
    
    if (pProperties->emulation.registerFileTypes && !oldProp.emulation.registerFileTypes) {
        registerFileTypes();
    }
    else {
        unregisterFileTypes();
    }
    
    if (pProperties->emulation.disableWinKeys && !oldProp.emulation.disableWinKeys) {
        if (kbdLockEnable && emulatorGetState() == EMU_RUNNING && pProperties->emulation.disableWinKeys) {
            kbdLockEnable();
        }
        else if (kbdLockDisable) {
            kbdLockDisable();
        }
    }
    
    if (pProperties->emulation.priorityBoost && !oldProp.emulation.priorityBoost) {
        if (pProperties->emulation.priorityBoost) {
            SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
        }
        else {
            SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
        }
    }

    mixerSetMasterVolume(st.mixer, pProperties->sound.masterVolume);
    mixerEnableMaster(st.mixer, pProperties->sound.masterEnable);

    if (restart) {
        emulatorRestart();
    }

    if (oldProp.settings.disableScreensaver != pProperties->settings.disableScreensaver) {
        POINT pt;
        SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, !pProperties->settings.disableScreensaver, 0, SPIF_SENDWININICHANGE); 
        GetCursorPos(&pt);
        SetCursorPos(pt.x + 1, pt.y);
    }

    updateMenu(0);

    InvalidateRect(st.hwnd, NULL, TRUE);
}


void enterDialogShow() {
    if (pProperties->video.driver != P_VIDEO_DRVGDI) {
        emulatorSuspend();
        DirectXSetGDISurface();
        emulatorResume();
    }
    st.showDialog++;
    if (st.showDialog == 1) {
        emuEnableSynchronousUpdate(0);
        SetTimer(st.hwnd, TIMER_SCREENUPDATE, 100, NULL);
    }
}

void exitDialogShow() {
    st.showDialog--;
    if (st.showDialog == 0) {
        emuEnableSynchronousUpdate(1);
        KillTimer(st.hwnd, TIMER_SCREENUPDATE);
        SetEvent(st.ddrawAckEvent);
    }
}

static void updateMenu(int show) {
    int doDelay = show;
    int enableSpecial = 1;

    if (pProperties->video.size != P_VIDEO_SIZEFULLSCREEN) {
        show = 1;
    }

    emulatorSuspend();

    if (pProperties->video.driver != P_VIDEO_DRVGDI) {
         if (doDelay) { 
             DirectXSetGDISurface();
         }
    }

    if (boardGetType() != BOARD_MSX) {
        enableSpecial = 0;
    }

    menuUpdate(pProperties, 
               st.shortcuts,
               emulatorGetState() == EMU_RUNNING, 
               emulatorGetState() == EMU_STOPPED, 
               mixerIsLogging(st.mixer),
               fileExist(pProperties->filehistory.quicksave, NULL),
               enableSpecial);

    st.showMenu = menuShow(show);

    emulatorResume();

    if (pProperties->video.size == P_VIDEO_SIZEFULLSCREEN) {
        mouseEmuActivate(!show);
    }
}

static void setClipRegion(int enable) {
    if (st.rgnEnable == enable) {
        return;
    }
    if (!enable || st.rgnData == NULL || st.showDialog) {
        SetWindowRgn(st.hwnd, NULL, TRUE);
        st.rgnEnable = 0;
    }
    else {
        HRGN hrgn = ExtCreateRegion(NULL, st.rgnSize, st.rgnData);
        SetWindowRgn(st.hwnd, hrgn, TRUE);
        st.rgnEnable = 1;
    }
}

static void updateClipRegion() {
    if (st.rgnData != NULL && st.hrgn != NULL) {
        POINT pt;
        RECT r;

        GetCursorPos(&pt);
        GetWindowRect(st.hwnd, &r);
        setClipRegion(!PtInRegion(st.hrgn, pt.x - r.left, pt.y - r.top));
    }
}

static void checkClipRegion() {
    if (st.rgnData != NULL && st.hrgn != NULL) {
        POINT pt;
        RECT r;

        GetCursorPos(&pt);
        GetWindowRect(st.hwnd, &r);
        if (st.rgnEnable == !PtInRegion(st.hrgn, pt.x - r.left, pt.y - r.top)) {
            SetTimer(st.hwnd, TIMER_CLIP_REGION, 500, NULL);
        }
    }
}

static int getZoom() {
    switch (pProperties->video.size) {
    case P_VIDEO_SIZEX1:
        return 1;
    case P_VIDEO_SIZEX2:
        return 2;
    case P_VIDEO_SIZEFULLSCREEN:
        switch (pProperties->video.fullRes) {
        case P_VIDEO_FRES320X240_16:
        case P_VIDEO_FRES320X240_32:
            return 1;
        case P_VIDEO_FRES640X480_16:
        case P_VIDEO_FRES640X480_32:
            return 2;
        }
    }
    return 1;
}


void themeSet(char* themeName, int forceMatch) {
    int x  = 0;
    int y  = 0;
    int w  = GetSystemMetrics(SM_CXSCREEN);
    int h  = GetSystemMetrics(SM_CYSCREEN);
    int ex = 0;
    int ey = 0;
    int index;

    if (themeName == NULL) {
        themeName = "";
    }
    
    index = getThemeListIndex(st.themeList, themeName, forceMatch);
    if (index == -1) {
        return;
    }

    if (st.themePageActive) {
        themePageActivate(st.themePageActive, NULL);
    }

    setClipRegion(0);
    st.themeIndex = index;
    strcpy(pProperties->settings.themeName, themeName);
    strcpy(pProperties->settings.themeName, st.themeList[st.themeIndex]->name);

    switch (pProperties->video.size) {
    case P_VIDEO_SIZEX1:
        st.themePageActive = themeGetCurrentPage(st.themeList[st.themeIndex]->little);
        break;
    case P_VIDEO_SIZEX2:
        st.themePageActive = themeGetCurrentPage(st.themeList[st.themeIndex]->normal);
        break;
    case P_VIDEO_SIZEFULLSCREEN:
        switch (pProperties->video.fullRes) {
        case P_VIDEO_FRES320X240_16:
        case P_VIDEO_FRES320X240_32:
            st.themePageActive = themeGetCurrentPage(st.themeList[st.themeIndex]->smallfullscreen);
            break;
        case P_VIDEO_FRES640X480_16:
        case P_VIDEO_FRES640X480_32:
            st.themePageActive = themeGetCurrentPage(st.themeList[st.themeIndex]->fullscreen);
            break;
        }
        break;
    }

    if (st.themePageActive) {
        themePageActivate(st.themePageActive, st.hwnd);
    }

    if (st.hBitmap) {
        DeleteObject(st.hBitmap);
    }

    menuSetInfo(st.themePageActive->menu.color, st.themePageActive->menu.focusColor, 
                st.themePageActive->menu.textColor, 
                st.themePageActive->menu.x, st.themePageActive->menu.y,
                st.themePageActive->menu.width, 32);

    if (pProperties->video.size != P_VIDEO_SIZEFULLSCREEN) {
        x = st.X;
        y = st.Y;
        w = st.themePageActive->width + 2 * GetSystemMetrics(SM_CXFIXEDFRAME);
        h = st.themePageActive->height + 2 * GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION);
        ex = st.themePageActive->emuWinX;
        ey = st.themePageActive->emuWinY;
    }

    st.hBitmap = CreateCompatibleBitmap(GetDC(st.hwnd), w, h);
    SetWindowPos(st.hwnd, HWND_NOTOPMOST, x, y, w, h, SWP_SHOWWINDOW);
    SetWindowPos(st.emuHwnd, NULL, ex, ey, getZoom() * WIDTH, getZoom() * HEIGHT, SWP_NOZORDER);

    if (st.rgnData != NULL) {
        SetWindowRgn(st.hwnd, NULL, TRUE);
        free(st.rgnData);
        st.rgnData = NULL;
    }

    if (st.hrgn != NULL) {
        DeleteObject(st.hrgn);
        st.hrgn = NULL;
    }

    if (st.themePageActive->clipPoint.count > 0) {
        int i;
        HRGN hrgn;
        POINT pt[512];
        int dx = GetSystemMetrics(SM_CXFIXEDFRAME);
        int dy = GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION);

        for (i = 0; i < st.themePageActive->clipPoint.count; i++) {
            ClipPoint cp = st.themePageActive->clipPoint.list[i];
            pt[i].x = cp.x + dx;
            pt[i].y = cp.y + dy;
        }

        hrgn = CreatePolygonRgn(pt, st.themePageActive->clipPoint.count, WINDING);
        st.rgnSize = 0;
        if (hrgn != NULL) {
            st.rgnSize = GetRegionData(hrgn, 0, NULL);
            if (st.rgnSize > 0) {
                st.rgnData = malloc(st.rgnSize);
                st.rgnSize = GetRegionData(hrgn, st.rgnSize, st.rgnData);
                if (st.rgnSize == 0) {
                    free(st.rgnData);
                    st.rgnData = NULL;
                }
            }
            if (st.rgnSize == 0) {
                st.rgnData = NULL;
            }
            else {
                st.hrgn = CreateRectRgn(0, 0, w, h);
                CombineRgn(st.hrgn, st.hrgn, hrgn, RGN_XOR);
            }
            DeleteObject(hrgn);
        }
    }

    setClipRegion(st.themePageActive->clipPoint.count > 0);

    if (st.rgnData == NULL) {
        KillTimer(st.hwnd, TIMER_CLIP_REGION);
    }
    else {
        SetTimer(st.hwnd, TIMER_CLIP_REGION, 500, NULL);
    }

    InvalidateRect(st.hwnd, NULL, FALSE);
}

PropVideoSize archGetWindowedSize() {
    return st.normalViedoSize;
}

void archUpdateWindow() {
    int zoom = getZoom();

    st.enteringFullscreen = 1;
    emulatorSuspend();

    DirectXExitFullscreenMode();

    if (st.bmBitsGDI != NULL) {
        free(st.bmBitsGDI);
        st.bmBitsGDI = NULL;
    }

    if (pProperties->video.size == P_VIDEO_SIZEFULLSCREEN) {
        if (pProperties->video.driver == P_VIDEO_DRVGDI) {
            pProperties->video.size = P_VIDEO_SIZEX2;
        }
        else {
            int rv;
            int depth = pProperties->video.fullRes == P_VIDEO_FRES320X240_16 ||
                        pProperties->video.fullRes == P_VIDEO_FRES640X480_16 ? 16 : 32;

            SetWindowLong(st.hwnd, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_VISIBLE);

            rv = DirectXEnterFullscreenMode(st.emuHwnd, zoom * WIDTH, zoom * HEIGHT, depth, 
                                            pProperties->video.driver == P_VIDEO_DRVDIRECTX_VIDEO, 
                                            pProperties->video.driver == P_VIDEO_DRVDIRECTX_VIDEO);
            if (rv != DXE_OK) {
                DirectXExitFullscreenMode();
                zoom = 2;
                rv = DirectXEnterFullscreenMode(st.emuHwnd, zoom * WIDTH, zoom * HEIGHT, 16, 
                                            pProperties->video.driver == P_VIDEO_DRVDIRECTX_VIDEO, 
                                            pProperties->video.driver == P_VIDEO_DRVDIRECTX_VIDEO);
            }
            if (rv != DXE_OK) {
                MessageBox(NULL, langErrorEnterFullscreen(), langErrorTitle(), MB_OK);
                DirectXExitFullscreenMode();
                pProperties->video.size = P_VIDEO_SIZEX2;
            }
        }
    }

    if (pProperties->video.size != P_VIDEO_SIZEFULLSCREEN) {
        st.normalViedoSize = pProperties->video.size;

        if (GetWindowLong(st.hwnd, GWL_STYLE) & WS_POPUP) {
            mouseEmuActivate(1);
            SetWindowLong(st.hwnd, GWL_STYLE, WS_OVERLAPPED | WS_CLIPCHILDREN | WS_BORDER | WS_DLGFRAME | 
                                WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
        }

        if (pProperties->video.driver != P_VIDEO_DRVGDI) {
            int rv = DirectXEnterWindowedMode(st.emuHwnd, zoom * WIDTH, zoom * HEIGHT, 
                                              pProperties->video.driver == P_VIDEO_DRVDIRECTX_VIDEO, 
                                              pProperties->video.driver == P_VIDEO_DRVDIRECTX_VIDEO);
            if (rv != DXE_OK) {
                MessageBox(NULL, langErrorDirectXFailed(), langErrorTitle(), MB_OK);
                pProperties->video.driver = P_VIDEO_DRVGDI;
            }
        }
    }

    if (st.rgnData != NULL) {
        SetWindowRgn(st.hwnd, NULL, TRUE);
        free(st.rgnData);
        st.rgnData = NULL;
    }
    setClipRegion(0);
    themeSet(pProperties->settings.themeName, 1);
    updateMenu(0);

    {
        RECT r = { 0, 0, zoom * WIDTH, zoom * HEIGHT };
        mouseEmuSetCaptureInfo(&r);
    }

    emulatorResume();

    st.enteringFullscreen = 0;

    if (emulatorGetState() != EMU_RUNNING) {
        InvalidateRect(st.hwnd, NULL, TRUE);
    }
}



static void emuWindowDraw()
{         
    if (!st.enteringFullscreen && 
        (pProperties->video.driver == P_VIDEO_DRVDIRECTX_VIDEO || 
        pProperties->video.driver == P_VIDEO_DRVDIRECTX))
    {
        DirectXUpdateSurface(st.pVideo, emulatorGetFrameBuffer(), WIDTH, HEIGHT, emulatorGetScrLineWidth(), 
                             st.showMenu | st.showDialog || emulatorGetState() != EMU_RUNNING, 
                             0, 0, getZoom(), 
                             pProperties->video.horizontalStretch, pProperties->video.verticalStretch, 
                             st.evenOdd, st.interlace);
        st.frameCount++;
    }
}

static LRESULT CALLBACK emuWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (iMsg) {
    case WM_CREATE:
        return 0;

    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
        return SendMessage(GetParent(hwnd), iMsg, wParam, lParam);

    case WM_PAINT:
        if (pProperties->video.driver == P_VIDEO_DRVGDI && emulatorGetState() != EMU_STOPPED) {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);   
            DWORD* bmBitsSrc;
            int zoom = getZoom();
            int width;
            int height;
            RECT r;

            GetClientRect(hwnd, &r);

            width = r.right - r.left;
            height = r.bottom - r.top;
            bmBitsSrc = (DWORD*)emulatorGetFrameBuffer() +  WIDTH * (HEIGHT - 1) * 2;
            
            if (st.bmBitsGDI == 0) {
                st.bmBitsGDI = malloc(4096 * 4096 * sizeof(UInt32));
            }
            videoRender(st.pVideo, 32, zoom, st.evenOdd, st.interlace, bmBitsSrc, WIDTH, HEIGHT, 
                        emulatorGetScrLineWidth(), st.bmBitsGDI, 
                        -1 * (int)sizeof(DWORD) * WIDTH, zoom * WIDTH * sizeof(DWORD));
            st.bmInfo.bmiHeader.biWidth    = zoom * WIDTH;
            st.bmInfo.bmiHeader.biHeight   = zoom * HEIGHT;
            st.bmInfo.bmiHeader.biBitCount = 32;
            StretchDIBits(hdc, 0, 0,  width, height, 0, 0, zoom * WIDTH, zoom * HEIGHT, st.bmBitsGDI, 
                            &st.bmInfo, DIB_RGB_COLORS, SRCCOPY);
            EndPaint(hwnd, &ps);
            st.frameCount++;
        }
        else if (pProperties->video.driver != P_VIDEO_DRVGDI  && emulatorGetState() == EMU_PAUSED) {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
            SetEvent(st.ddrawEvent);
        }
        else {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
        }
        return 0;
    }

    return DefWindowProc(hwnd, iMsg, wParam, lParam);    
}

static LRESULT CALLBACK wndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (iMsg) {
    case WM_CREATE:
        SetTimer(hwnd, TIMER_STATUSBAR_UPDATE, 100, NULL);
        SetTimer(hwnd, TIMER_POLL_INPUT, 20, NULL);
        SetTimer(hwnd, TIMER_POLL_FRAMECOUNT, 1000, NULL);
        DragAcceptFiles(hwnd, TRUE);
        return 0;

    case WM_DROPFILES:
        {
            char fname[MAX_PATH];
            HDROP hDrop;
            hDrop = (HDROP)wParam;
            DragQueryFile(hDrop, 0, fname, 512);
            DragFinish(hDrop);

            tryLaunchUnknownFile(pProperties, fname, 0);
        }
        return 0;

    case WM_LAUNCHFILE:
        {
            char fileName[512];
            FILE* file = fopen(LAUNCH_TEMP_FILE, "r");
            if (file != NULL) {
                int size = fread(fileName, 1, 512, file);
                fclose(file);
                if (size > 0) {
                    char* argument;

                    fileName[size] = 0;                    

                    argument = extractToken(fileName, 0);
                    if (*argument) {
                        emulatorStop();
                        // Clear cartridge info
                        pProperties->cartridge.slotA[0] = 0;
                        pProperties->cartridge.slotAZip[0] = 0;
                        pProperties->cartridge.slotB[0] = 0;
                        pProperties->cartridge.slotBZip[0] = 0;
                        pProperties->cartridge.slotAType = ROM_UNKNOWN;
                        pProperties->cartridge.slotBType = ROM_UNKNOWN;
                        updateExtendedRomName(0, pProperties->cartridge.slotA, pProperties->cartridge.slotAZip);
                        updateExtendedRomName(1, pProperties->cartridge.slotB, pProperties->cartridge.slotBZip);

                        pProperties->diskdrive.slotA[0] = 0;
                        pProperties->diskdrive.slotAZip[0] = 0;
                        pProperties->diskdrive.slotB[0] = 0;
                        pProperties->diskdrive.slotBZip[0] = 0;
                        updateExtendedDiskName(0, pProperties->diskdrive.slotA, pProperties->diskdrive.slotAZip);
                        updateExtendedDiskName(1, pProperties->diskdrive.slotB, pProperties->diskdrive.slotBZip);
                    
                        updateExtendedCasName(pProperties->cassette.tape, pProperties->cassette.tapeZip);

                        tryLaunchUnknownFile(pProperties, argument, 1);
                    }

                    SetActiveWindow(hwnd);
                }
            }
        }
        return 0;

    case WM_COMMAND:
        if ( menuCommand(pProperties, LOWORD(wParam))) {
            updateMenu(0);
        }
        break;

    case WM_SYSKEYDOWN:
    case WM_KEYDOWN:
        {
            ShotcutHotkey key;
            key.type = HOTKEY_TYPE_KEYBOARD;
            key.mods = keyboardGetModifiers();
            key.key  = wParam & 0xff;
            checkKeyDown(st.shortcuts, key);
        }
        return 0;

    case WM_SYSKEYUP:
    case WM_KEYUP:
        {
            ShotcutHotkey key;
            key.type = HOTKEY_TYPE_KEYBOARD;
            key.mods = keyboardGetModifiers();
            key.key  = wParam & 0xff;
            checkKeyUp(st.shortcuts, key);
        }
        return 0;

    case WM_CHAR:
    case WM_SYSCHAR:
        return 0;

    case WM_SYSCOMMAND:
        switch(wParam) {
        case SC_MAXIMIZE:
            vdpSetDisplayEnable(1);
            st.minimized = 0;
            if (pProperties->video.size != P_VIDEO_SIZEFULLSCREEN) {
                pProperties->video.size = P_VIDEO_SIZEFULLSCREEN;
                archUpdateWindow();
            }
            return 0;
        case SC_MINIMIZE:
            vdpSetDisplayEnable(0);
            st.minimized = 1;
//            emulatorSuspend();
            break;
        case SC_RESTORE:
            vdpSetDisplayEnable(1);
            st.minimized = 0;
//            emulatorResume();
            break;
        }
        break;

    case WM_NCLBUTTONDBLCLK:
        if (wParam == HTCAPTION) {
            if (pProperties->video.size != P_VIDEO_SIZEFULLSCREEN) {
                pProperties->video.size = P_VIDEO_SIZEFULLSCREEN;
                archUpdateWindow();
            }
            return 0;
        }
        break;

    case WM_ENTERSIZEMOVE:
        emulatorSuspend();
        mouseEmuActivate(0);
        st.showDialog++;
        break;

    case WM_EXITSIZEMOVE:
        st.showDialog--;
        emulatorResume();
        mouseEmuActivate(1);
        break;

    case WM_ENTERMENULOOP:
        emulatorSuspend();
        st.trackMenu = 1;
        SetTimer(st.hwnd, TIMER_MENUUPDATE, 250, NULL);
        mouseEmuActivate(0);
        return 0;

    case WM_EXITMENULOOP:
        {
            int moreMenu;
            
            if (!st.minimized) {
                emuWindowDraw();
            }
            moreMenu = menuExitMenuLoop();
            if (!moreMenu) {
                mouseEmuActivate(1);
                //KillTimer(st.hwnd, TIMER_MENUUPDATE);
                emulatorResume();
                updateMenu(0);
                if (pProperties->video.size == P_VIDEO_SIZEFULLSCREEN) {
                    PostMessage(hwnd, WM_LBUTTONDOWN, 0, 0);
                    PostMessage(hwnd, WM_LBUTTONUP, 0, 0);
                }
                st.trackMenu = 0;
            }
        }
        return 0;

    case WM_MOVE:
        if (!st.enteringFullscreen && pProperties->video.size != P_VIDEO_SIZEFULLSCREEN) {
            RECT r;
            GetWindowRect(hwnd, &r);
            st.X = r.left;
            st.Y = r.top;
        }

    case WM_DISPLAYCHANGE:
        if (pProperties->video.driver != P_VIDEO_DRVGDI) {
            int zoom = getZoom();
            if (st.enteringFullscreen) {
                DirectXUpdateWindowedMode(st.emuHwnd, zoom * WIDTH, zoom * HEIGHT,
                                          pProperties->video.driver == P_VIDEO_DRVDIRECTX_VIDEO, 
                                          pProperties->video.driver == P_VIDEO_DRVDIRECTX_VIDEO);
            }
        }
        break;

    case WM_GETMINMAXINFO:
        {
            LRESULT rv = DefWindowProc(hwnd, iMsg, wParam, lParam);
            MINMAXINFO* mmi = (MINMAXINFO*)lParam;
            mmi->ptMaxSize.x      = 2048;
            mmi->ptMaxSize.y      = 2048;
            mmi->ptMaxTrackSize.x = 2048;
            mmi->ptMaxTrackSize.y = 2048;
            return 0;
        }

    case WM_SIZE:
        InvalidateRect(hwnd, NULL, FALSE);
        break;
        
    case WM_ACTIVATE:
        if (wParam == WA_INACTIVE) {
            if (kbdLockDisable != NULL) {
                kbdLockDisable(0);
            }
            mouseEmuActivate(0);
            actionMaxSpeedRelease();
        }
        else {
            if (kbdLockEnable != NULL && emulatorGetState() == EMU_RUNNING && pProperties->emulation.disableWinKeys) {
                kbdLockEnable();
            }
            mouseEmuActivate(1);
        }
        break;

    case WM_NCMOUSEMOVE:
        if (st.themePageActive) {
            checkClipRegion();
        }
        break;

    case WM_MOUSEMOVE:
        if (st.themePageActive) {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);
            themePageMouseMove(st.themePageActive, GetDC(hwnd), pt.x, pt.y);
            checkClipRegion();
        }
        if (pProperties->video.size == P_VIDEO_SIZEFULLSCREEN) {
            if (HIWORD(lParam) < 2) {
                if (!st.showMenu) {
                    updateMenu(1);
                }
            }
        }
        SetTimer(hwnd, TIMER_THEME, 250, NULL);

        break;

    case WM_LBUTTONDOWN:
        SetCapture(hwnd);
    
        if (st.themePageActive) {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);
            themePageMouseButtonDown(st.themePageActive, GetDC(hwnd), pt.x, pt.y);
        }
        if (st.showMenu && pProperties->video.size == P_VIDEO_SIZEFULLSCREEN) {
            updateMenu(0);
        }
        break;

    case WM_LBUTTONUP:
        ReleaseCapture();
        if (st.themePageActive) {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);
            themePageMouseButtonUp(st.themePageActive, GetDC(hwnd), pt.x, pt.y);
        }

    case WM_ERASEBKGND:
        return 1;

    case WM_TIMER:
        switch (wParam) {
        case TIMER_CLIP_REGION:
            updateClipRegion();
            break;

        case TIMER_STATUSBAR_UPDATE:
            if (!st.minimized) {
                static UInt32 resetCnt = 0;

                if (emulatorGetState() == EMU_RUNNING) {
                    if ((resetCnt++ & 0x3f) == 0) {
                        mixerIsChannelTypeActive(st.mixer, MIXER_CHANNEL_MOONSOUND, 1);
                        mixerIsChannelTypeActive(st.mixer, MIXER_CHANNEL_MSXAUDIO, 1);
                        mixerIsChannelTypeActive(st.mixer, MIXER_CHANNEL_MSXMUSIC, 1);
                        mixerIsChannelTypeActive(st.mixer, MIXER_CHANNEL_SCC, 1);
                    }
                }

                PatchDiskSetBusy(0, 0);
                PatchDiskSetBusy(1, 0);
                tapeSetBusy(0);

                themePageUpdate(st.themePageActive, GetDC(hwnd));
            }
            break;

        case TIMER_POLL_INPUT:
            {
                DWORD buttonState = joystickUpdate();
                DWORD buttons     = buttonState & ~st.buttonState;
                ShotcutHotkey key;
                int i;

                for (i = 1; buttons != 0; i++, buttons >>= 1) {
                    if (buttons & 1) {
                        key.type = HOTKEY_TYPE_JOYSTICK;
                        key.mods = 0;
                        key.key  = i;
                        checkKeyDown(st.shortcuts, key);
                    }
                }
                
                buttons = ~buttonState & st.buttonState;
                for (i = 1; buttons != 0; i++, buttons >>= 1) {
                    if (buttons & 1) {
                        key.type = HOTKEY_TYPE_JOYSTICK;
                        key.mods = 0;
                        key.key  = i;
                        checkKeyUp(st.shortcuts, key);
                    }
                }

                st.buttonState = buttonState;

                keyboardUpdate();

                mouseEmuSetRunState(emulatorGetState() == EMU_RUNNING);
            }
            break;

        case TIMER_POLL_FRAMECOUNT:
            st.framesPerSecond = st.frameCount;
            st.frameCount = 0;
            break;

        case TIMER_MENUUPDATE:
            if (!st.minimized) {
                emuWindowDraw();
            }
            if (!st.trackMenu) {
                KillTimer(st.hwnd, TIMER_MENUUPDATE);
            }
            break;

        case TIMER_SCREENUPDATE:
            {
                DWORD rv = WaitForSingleObject(st.ddrawEvent, 0);
                if (rv == WAIT_OBJECT_0) {
                    if (!st.minimized) {
                        emuWindowDraw();
                    }
                    SetEvent(st.ddrawAckEvent);
                }
            }
            break;

        case TIMER_SCREENSHOT:
            KillTimer(hwnd, TIMER_SCREENSHOT);
			ScreenShot(pProperties, st.emuHwnd, WIDTH * getZoom(), HEIGHT * getZoom(), 0, 0);
            break;

        case TIMER_SCREENSHOT_UNFILTERED_LARGE:
            KillTimer(hwnd, TIMER_SCREENSHOT_UNFILTERED_LARGE);

            {
                int zoom = 2;
                DWORD* bmBitsSrc = (DWORD*)emulatorGetFrameBuffer() + WIDTH * (HEIGHT - 1) * 2;
                DWORD* bmBitsDst = malloc(zoom * zoom * WIDTH * HEIGHT * sizeof(UInt32));
                VideoPalMode palMode      = st.pVideo->palMode;
                int scanLinesEnable       = st.pVideo->scanLinesEnable;
                int colorSaturationEnable = st.pVideo->colorSaturationEnable;

                st.pVideo->palMode = VIDEO_PAL_FAST;
                st.pVideo->scanLinesEnable = 0;
                st.pVideo->colorSaturationEnable = 0;
                videoRender(st.pVideo, 32, zoom, st.evenOdd, st.interlace, bmBitsSrc, WIDTH, HEIGHT, 
                            emulatorGetScrLineWidth(), bmBitsDst, 
                            -1 * (int)sizeof(DWORD) * WIDTH, zoom * WIDTH * sizeof(DWORD));

                st.pVideo->palMode               = palMode;
                st.pVideo->scanLinesEnable       = scanLinesEnable;
                st.pVideo->colorSaturationEnable = colorSaturationEnable;

                ScreenShot3(pProperties, bmBitsDst + zoom * 24, 320 * zoom, (320 - 48) * zoom, 240 * zoom);

                free(bmBitsDst);
            }
            break;

        case TIMER_SCREENSHOT_UNFILTERED_SMALL:
            KillTimer(hwnd, TIMER_SCREENSHOT_UNFILTERED_SMALL);

            {
                int zoom = 1;
                DWORD* bmBitsSrc = (DWORD*)emulatorGetFrameBuffer() + WIDTH * (HEIGHT - 1) * 2;
                DWORD* bmBitsDst = malloc(zoom * zoom * WIDTH * HEIGHT * sizeof(UInt32));
                VideoPalMode palMode      = st.pVideo->palMode;
                int scanLinesEnable       = st.pVideo->scanLinesEnable;
                int colorSaturationEnable = st.pVideo->colorSaturationEnable;

                st.pVideo->palMode = VIDEO_PAL_FAST;
                st.pVideo->scanLinesEnable = 0;
                st.pVideo->colorSaturationEnable = 0;
                videoRender(st.pVideo, 32, zoom, st.evenOdd, st.interlace, bmBitsSrc, WIDTH, HEIGHT, 
                            emulatorGetScrLineWidth(), bmBitsDst, 
                            -1 * (int)sizeof(DWORD) * WIDTH, zoom * WIDTH * sizeof(DWORD));

                st.pVideo->palMode               = palMode;
                st.pVideo->scanLinesEnable       = scanLinesEnable;
                st.pVideo->colorSaturationEnable = colorSaturationEnable;

                ScreenShot3(pProperties, bmBitsDst + zoom * 24, 320 * zoom, (320 - 48) * zoom, 240 * zoom);

                free(bmBitsDst);
            }
            break;
            
        case TIMER_THEME:        
            if (!st.minimized) {
                POINT pt;
                RECT r;
                HDC hdc;

                GetCursorPos(&pt);
                GetWindowRect(hwnd, &r);

                if (!PtInRect(&r, pt)) {
                    KillTimer(hwnd, TIMER_THEME);
                }

                ScreenToClient(hwnd, &pt);

                hdc = GetDC(hwnd);
                themePageMouseMove(st.themePageActive, hdc, pt.x, pt.y);
                ReleaseDC(hwnd, hdc);
            }
            break;
        }
        return 0;

    case WM_UPDATE:
        InvalidateRect(st.emuHwnd, NULL, FALSE);
        return 0;

    case WM_INPUTLANGCHANGE:
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            if (!st.minimized) {
                HDC hMemDC = CreateCompatibleDC(hdc);
                HBITMAP hBitmap = (HBITMAP)SelectObject(hMemDC, st.hBitmap);

                themePageDraw(st.themePageActive, hMemDC);

                BitBlt(hdc, 0, 0, st.themePageActive->width, st.themePageActive->height, hMemDC, 0, 0, SRCCOPY);

                SelectObject(hMemDC, hBitmap);
                DeleteDC(hMemDC);                
            }
            EndPaint(hwnd, &ps);
        }
        return 0;
        
    case WM_DESTROY:         
        emulatorStop();
        if (pProperties->video.size != P_VIDEO_SIZEFULLSCREEN) {
            RECT r;
            
            GetWindowRect(hwnd, &r);
            st.X = r.left;
            st.Y = r.top;
        }
        st.enteringFullscreen = 1;
        DirectXExitFullscreenMode();
        PostQuitMessage(0);
        inputDestroy();
        return 0;
    }

    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

////////////////////////////////////////////////////////////////////

static int videoTimeAverage = 0;
static int videoTimeTotal = 0;
static int videoTimeIdle = 1;

UInt32 videoGetCpuUsage() {
    videoTimeAverage = 1000 * (videoTimeTotal - videoTimeIdle) / videoTimeTotal;

    if (videoTimeAverage >= 1000) {
        videoTimeAverage = 0;
    }

    videoTimeIdle  = 0;
    videoTimeTotal = 1;

    return videoTimeAverage;
}

void updateEmuWindow() {
    if (emulatorGetState() != EMU_STOPPED) {
        SetEvent(st.ddrawEvent);
    }
}

void setDefaultPath() {   
    char buffer[512];
    char rootDir[512];
    FILE* file;
    char* ptr;

    // Set current directory to where the exe is located
    GetModuleFileName((HINSTANCE)GetModuleHandle(NULL), buffer, 512);
    ptr = stripPath(buffer);
    *ptr = 0;
    chdir(buffer);

    GetCurrentDirectory(MAX_PATH - 1, st.pCurDir);

    // Get Root directory
    file = fopen("wrtest", "w");
    if (file != NULL) {
        GetCurrentDirectory(MAX_PATH - 1, rootDir); 
        fclose(file);
    }
    else {
        chdir("C:\\");
        mkdir("C:\\blueMSX Temporary Files");
        chdir("C:\\blueMSX Temporary Files");

        GetCurrentDirectory(MAX_PATH - 1, rootDir); 
        SetCurrentDirectory(st.pCurDir);
    }

    // Set up temp directories
    sprintf(buffer, "%s\\Audio Capture", rootDir);
    mkdir(buffer);
    actionSetAudioCaptureSetDirectory(buffer, "");

    sprintf(buffer, "%s\\QuickSave", rootDir);
    mkdir(buffer);
    actionSetQuickSaveSetDirectory(buffer, "");

    sprintf(buffer, "%s\\SRAM", rootDir);
    mkdir(buffer);
    boardSetDirectory(buffer);

    sprintf(buffer, "%s\\Shortcut Profiles", rootDir);
    mkdir(buffer);
    shortcutsSetDirectory(buffer);

    sprintf(buffer, "%s\\Keyboard Config", rootDir);
    mkdir(buffer);
    keyboardSetDirectory(buffer);

    sprintf(buffer, "%s\\Screenshots", rootDir);
    mkdir(buffer);
    screenshotSetDirectory(buffer, "");

    sprintf(buffer, "%s\\Casinfo", rootDir);
    mkdir(buffer);
    tapeSetDirectory(buffer, "");

    sprintf(buffer, "%s\\romdb.dat", rootDir);
    romMapperSetRomdbFilename(buffer);

    sprintf(buffer, "%s\\diskdb.dat", rootDir);
    romMapperSetDiskdbFilename(buffer);
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

#ifdef _CONSOLE
int main(int argc, char **argv)
#else
WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PSTR szLine, int iShow)
#endif
{
#ifdef _CONSOLE
    char szLine[8192] = "";
#endif
    static WNDCLASSEX wndClass;
    HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
    BOOL screensaverActive;
    int  resetRegistry;
    HWND hwnd;
    int doExit = 0;
    RECT wr;
    MSG msg;
    int i;
    HINSTANCE kbdLockInst;

#ifdef _CONSOLE
    for (i = 1; i < argc; i++) {
        strcat(szLine, argv[i]);
        strcat(szLine, " ");
    }
#endif

    hwnd = FindWindow("blueMSX", "  blueMSX");
    if (hwnd != NULL && *szLine) {
        char args[2048];
        char* cmdLine = args;

        if (0 == strncmp(szLine, "/onearg ", 8)) {
            char* ptr;
            sprintf(args, "\"%s", szLine + 8);
            ptr = args + strlen(args);
            while(*--ptr == ' ') {
                *ptr = 0; 
            }
            strcat(args, "\"");
        }
        else {
            cmdLine = szLine;
        }
        if (!extractToken(cmdLine, 1)) {
            FILE* file = fopen(LAUNCH_TEMP_FILE, "w");
            if (file != NULL) {
                fwrite(cmdLine, 1, strlen(cmdLine) + 1, file);
                fclose(file);
                SendMessage(hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
                SetForegroundWindow(hwnd);
                PostMessage(hwnd, WM_LAUNCHFILE, 0, 0);
            }
            return 0;
        }
    }

    kbdLockInst = LoadLibrary("kbdlock.dll");

    if (kbdLockInst != NULL) {
        kbdLockEnable  = (KbdLockFun)GetProcAddress(kbdLockInst, (LPCSTR)2);
        kbdLockDisable = (KbdLockFun)GetProcAddress(kbdLockInst, (LPCSTR)3);
    }

    InitCommonControls(); 

    wndClass.cbSize         = sizeof(wndClass);
    wndClass.style          = CS_OWNDC;
    wndClass.lpfnWndProc    = wndProc;
    wndClass.cbClsExtra     = 0;
    wndClass.cbWndExtra     = 0;
    wndClass.hInstance      = hInstance;
    wndClass.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BLUEMSX));
    wndClass.hIconSm        = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BLUEMSX));
    wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground  = NULL;
    wndClass.lpszMenuName   = NULL;
    wndClass.lpszClassName  = "blueMSX";

    RegisterClassEx(&wndClass);

    wndClass.lpfnWndProc    = emuWndProc;
    wndClass.lpszClassName  = "blueMSXemuWindow";
    wndClass.hIcon          = NULL;
    wndClass.hIconSm        = NULL;
    RegisterClassEx(&wndClass);

    resetRegistry = emuCheckResetArgument(szLine);
    propertiesInit(emuCheckIniFileArgument(szLine));
    pProperties = propCreate(resetRegistry);
    pProperties->language = emuCheckLanguageArgument(szLine, pProperties->language);
       
    if (resetRegistry == 2) {
        propDestroy(pProperties);
        FreeLibrary(kbdLockInst);

        exit(0);
        return 0;
    }

    setDefaultPath();

    st.normalViedoSize = P_VIDEO_SIZEX2;
    st.buttonState = 0;
    st.showDialog = 0;
    st.enteringFullscreen = 1;
    st.frameCount = 0;
    st.framesPerSecond = 0;
    st.minimized = 0;
    st.bmBitsGDI     = NULL;
    st.bmInfo.bmiHeader.biSize           = sizeof(BITMAPINFOHEADER);
    st.bmInfo.bmiHeader.biWidth          = WIDTH;
    st.bmInfo.bmiHeader.biHeight         = HEIGHT;
    st.bmInfo.bmiHeader.biPlanes         = 1;
    st.bmInfo.bmiHeader.biBitCount       = 32;
    st.bmInfo.bmiHeader.biCompression    = BI_RGB;
    st.bmInfo.bmiHeader.biClrUsed        = 0;
    st.bmInfo.bmiHeader.biClrImportant   = 0;
    st.ddrawEvent    = CreateEvent(NULL, FALSE, FALSE, NULL);
    st.ddrawAckEvent = CreateEvent(NULL, FALSE, FALSE, NULL);    

    st.pVideo = videoCreate();
    videoSetColors(st.pVideo, pProperties->video.saturation, pProperties->video.brightness, 
                  pProperties->video.contrast, pProperties->video.gamma);
    videoSetScanLines(st.pVideo, pProperties->video.scanlinesEnable, pProperties->video.scanlinesPct);
    videoSetColorSaturation(st.pVideo, pProperties->video.colorSaturationEnable, pProperties->video.colorSaturationWidth);

    st.mixer  = mixerCreate();

    emulatorInit(pProperties, st.mixer);
    actionInit(pProperties, st.mixer);
    langInit();
    tapeSetReadOnly(pProperties->cassette.readOnly);
    
    // Initialize shortcuts profile
    if (!shortcutsIsProfileValid(pProperties->emulation.shortcutProfile)) {
        shortcutsGetAnyProfile(pProperties->emulation.shortcutProfile);
    }

    st.shortcuts = shortcutsCreateProfile(pProperties->emulation.shortcutProfile);

    SystemParametersInfo(SPI_GETSCREENSAVEACTIVE, 0, &screensaverActive, SPIF_SENDWININICHANGE); 
    SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, !pProperties->settings.disableScreensaver, 0, SPIF_SENDWININICHANGE); 

    if (pProperties->emulation.registerFileTypes) {
        registerFileTypes();
    }
    else {
        unregisterFileTypes();
    }

    pProperties->language = emuCheckLanguageArgument(szLine, pProperties->language);
    langSetLanguage(pProperties->language);

    st.hwnd = CreateWindow("blueMSX", "  blueMSX", 
                            WS_OVERLAPPED | WS_CLIPCHILDREN | WS_BORDER | WS_DLGFRAME | 
                            WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, 
                            CW_USEDEFAULT, CW_USEDEFAULT, 800, 200, NULL, NULL, hInstance, NULL);

    menuCreate(st.hwnd);

    addMenuItem(langMenuFile(), actionMenuFile, 0);
    addMenuItem(langMenuRun(), actionMenuRun, 1);
    addMenuItem(langMenuWindow(), actionMenuZoom, 1);
    addMenuItem(langMenuOptions(), actionMenuOptions, 1);
    addMenuItem(langMenuTools(), actionMenuTools, 1);
    addMenuItem(langMenuHelp(), actionMenuHelp, 1);

    st.emuHwnd = CreateWindow("blueMSXemuWindow", "", WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, 0, 0, 0, 0, st.hwnd, NULL, hInstance, NULL);
    ShowWindow(st.emuHwnd, SW_HIDE);

    inputInit();
    inputReset(st.hwnd);
    keyboardLoadConfig(pProperties->keyboard.configFile);
    sprintf(pProperties->keyboard.configFile, keyboardGetCurrentConfig());

    propUpdateJoyinfo(pProperties);
    joystickIoSetType(0, pProperties->joy1.type == P_JOY_NONE  ? 0 : pProperties->joy1.type == P_JOY_MOUSE ? 2 : 1, pProperties->joy1.type);
    joystickIoSetType(1, pProperties->joy2.type == P_JOY_NONE  ? 0 : pProperties->joy2.type == P_JOY_MOUSE ? 2 : 1, pProperties->joy2.type);
    mouseEmuInit(st.emuHwnd, 1);
    mouseEmuEnable(pProperties->joy1.type == P_JOY_MOUSE || pProperties->joy2.type == P_JOY_MOUSE);

    st.dskWnd = diskQuickviewWindowCreate(st.hwnd);

    GetWindowRect(st.hwnd, &wr);
    st.X  = wr.left;
    st.Y  = wr.top;

    SetWindowPos(st.hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOZORDER);

    st.enteringFullscreen = 0;

    soundDriverConfig(st.hwnd, pProperties->sound.driver);
    emulatorRestartSound();

    for (i = 0; i < MIXER_CHANNEL_TYPE_COUNT; i++) {
        mixerSetChannelTypeVolume(st.mixer, i, pProperties->sound.mixerChannel[i].volume);
        mixerSetChannelTypePan(st.mixer, i, pProperties->sound.mixerChannel[i].pan);
        mixerEnableChannelType(st.mixer, i, pProperties->sound.mixerChannel[i].enable);
    }
    
    mixerSetMasterVolume(st.mixer, pProperties->sound.masterVolume);
    mixerEnableMaster(st.mixer, pProperties->sound.masterEnable);

    updateVideoRender(st.pVideo, pProperties);
    updateJoystick(pProperties);
    
    romMapperSetDefaultType(pProperties->cartridge.defaultType);

    if (pProperties->cartridge.slotA[0]) insertCartridge(pProperties, 0, pProperties->cartridge.slotA, pProperties->cartridge.slotAZip, pProperties->cartridge.slotAType, -1);
    if (pProperties->cartridge.slotB[0]) insertCartridge(pProperties, 1, pProperties->cartridge.slotB, pProperties->cartridge.slotBZip, pProperties->cartridge.slotBType, -1);
    if (pProperties->diskdrive.slotA[0]) insertDiskette(pProperties, 0, pProperties->diskdrive.slotA, pProperties->diskdrive.slotAZip, -1);
    if (pProperties->diskdrive.slotB[0]) insertDiskette(pProperties, 1, pProperties->diskdrive.slotB, pProperties->diskdrive.slotBZip, -1);

    updateExtendedRomName(0, pProperties->cartridge.slotA, pProperties->cartridge.slotAZip);
    updateExtendedRomName(1, pProperties->cartridge.slotB, pProperties->cartridge.slotBZip);
    updateExtendedDiskName(0, pProperties->diskdrive.slotA, pProperties->diskdrive.slotAZip);
    updateExtendedDiskName(1, pProperties->diskdrive.slotB, pProperties->diskdrive.slotBZip);
    updateExtendedCasName(pProperties->cassette.tape, pProperties->cassette.tapeZip);

    // Call initStatistics to get correct ram size and vram size for status bars
    {
        Machine* machine = machineCreate(pProperties->emulation.machineName);
        if (machine != NULL) {
            boardSetMachine(machine);
            machineDestroy(machine);
        }
    }
    boardSetFdcTimingEnable(pProperties->emulation.enableFdcTiming);
    boardSetY8950Enable(pProperties->sound.chip.enableY8950);
    boardSetYm2413Enable(pProperties->sound.chip.enableYM2413);
    boardSetMoonsoundEnable(pProperties->sound.chip.enableMoonsound);

    updateMenu(0);

    if (emuTryStartWithArguments(pProperties, szLine) < 0) {           
        exit(0);
        return 0;
    }

    st.themePageActive = NULL;
    st.themeList = createThemeList(themeClassicCreate());
    themeSet(emuCheckThemeArgument(szLine), 0);

    archUpdateWindow();
    ShowWindow(st.hwnd, SW_NORMAL);
    UpdateWindow(st.hwnd);

    if (pProperties->emulation.priorityBoost) {
        SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
    }

    while (!doExit) {
        DWORD rv = MsgWaitForMultipleObjects(1, &st.ddrawEvent, FALSE, INFINITE, QS_ALLINPUT);    
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                doExit = 1;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (rv == WAIT_OBJECT_0) {
            if (!st.minimized) {
                emuWindowDraw();
            }
            SetEvent(st.ddrawAckEvent);
        }
    }

    sprintf(pProperties->keyboard.configFile, keyboardGetCurrentConfig());
    shortcutsDestroyProfile(st.shortcuts);
    videoDestroy(st.pVideo);
    propDestroy(pProperties);

    archSoundDestroy();
    Sleep(300);
    mixerDestroy(st.mixer);

    SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, screensaverActive, 0, SPIF_SENDWININICHANGE); 

    if (kbdLockDisable) {
        kbdLockDisable();
    }
    FreeLibrary(kbdLockInst);

    exit(0);

    return 0;
}



////////////////////////////////////////////////////////////////////////////////////////

#include "Win32file.h"


void archShowCassettePosDialog()
{
    enterDialogShow();
    setTapePosition(getMainHwnd(), pProperties);
    exitDialogShow();
}

void archShowHelpDialog()
{
    HINSTANCE rv = 0;
    if (pProperties->language == EMU_LANG_JAPANESE) {
         rv = ShellExecute(getMainHwnd(), "open", "blueMSXjp.chm", NULL, NULL, SW_SHOWNORMAL);
    }
    if (rv <= (HINSTANCE)32) {
        rv = ShellExecute(getMainHwnd(), "open", "blueMSX.chm", NULL, NULL, SW_SHOWNORMAL);
    }
    if (rv <= (HINSTANCE)32) {
        MessageBox(NULL, langErrorNoHelp(), langErrorTitle(), MB_OK);
    }
}

void archShowAboutDialog()
{
    enterDialogShow();
    helpShowAbout(getMainHwnd());
    exitDialogShow();
}

void archShowLanguageDialog()
{
    int lang;
    int success;
    enterDialogShow();
    lang = langShowDlg(getMainHwnd(), pProperties->language);
    exitDialogShow();
    success = langSetLanguage(lang);
    if (success) {
        pProperties->language = lang;
        addMenuItem(langMenuFile(), actionMenuFile, 0);
        addMenuItem(langMenuRun(), actionMenuRun, 1);
        addMenuItem(langMenuWindow(), actionMenuZoom, 1);
        addMenuItem(langMenuOptions(), actionMenuOptions, 1);
        addMenuItem(langMenuTools(), actionMenuTools, 1);
        addMenuItem(langMenuHelp(), actionMenuHelp, 1);
    }
    updateMenu(0);
}
void archShowShortcutsEditor() 
{
    int apply;
    enterDialogShow();
    apply = shortcutsShowDialog(getMainHwnd(), pProperties);
    shortcutsDestroyProfile(st.shortcuts);
    st.shortcuts = shortcutsCreateProfile(pProperties->emulation.shortcutProfile);
    updateMenu(0);
    exitDialogShow();
}

void archShowMachineEditor()
{
    int apply;
    enterDialogShow();
    apply = confShowDialog(getMainHwnd(), pProperties->emulation.machineName);
    exitDialogShow();
    if (apply) {
        actionEmuResetHard();
    }
    updateMenu(0);
}

void archScreenCapture(ScreenCaptureType type)
{
    switch (type) {
    case SC_NORMAL:
        SetTimer(getMainHwnd(), TIMER_SCREENSHOT, 50, NULL);
        break;
    case SC_SMALL:
        SetTimer(getMainHwnd(), TIMER_SCREENSHOT_UNFILTERED_SMALL, 50, NULL);
        break;
    case SC_LARGE:
        SetTimer(getMainHwnd(), TIMER_SCREENSHOT_UNFILTERED_LARGE, 50, NULL);
        break;
    }
}

void archMinimizeWindow() {
    ShowWindow(getMainHwnd(), SW_MINIMIZE);
    updateMenu(0);
}

void archDiskQuickChangeNotify() 
{
    diskQuickviewWindowShow(st.dskWnd);
}

char* archDirOpen(char* title, char* defaultDir)
{
    char* filename;

    enterDialogShow();
    filename = openDir(getMainHwnd(), title, defaultDir);
    exitDialogShow();
    SetCurrentDirectory(st.pCurDir);

    return filename;
}

char* archFileOpen(char* title, char* extensionList, char* defaultDir, char* extensions, int* selectedExtension, char* defautExtension, int createFileSize)
{
    char* fileName;

    enterDialogShow();
    fileName = openFile(getMainHwnd(), title, extensionList, defaultDir, createFileSize, defautExtension, selectedExtension);
    exitDialogShow();
    SetCurrentDirectory(st.pCurDir);

    return fileName;
}

char* archFileRomOpen(char* title, char* extensionList, char* defaultDir, char* extensions, int* selectedExtension, char* defautExtension, RomType* romType) 
{
    char* fileName;

    enterDialogShow();
    fileName = openRomFile(getMainHwnd(), title, extensionList, defaultDir, 1, defautExtension, selectedExtension, romType);
    exitDialogShow();
    SetCurrentDirectory(st.pCurDir);

    return fileName;
}

char* archFileSave(char* title, char* extensionList, char* defaultDir, char* extensions, int* selectedExtension)
{
    char* fileName;

    enterDialogShow();
    fileName = saveFile(getMainHwnd(), title, extensionList, selectedExtension, defaultDir);
    exitDialogShow();
    SetCurrentDirectory(st.pCurDir);

    return fileName;
}

void archUpdateMenu(int show) {
    updateMenu(show);
}

void archQuit() {
    DestroyWindow(getMainHwnd());
}

void archFileFromZipDialog(ZipFileDlgInfo* dlgInfo) {
    enterDialogShow();
    DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ZIPDSK), getMainHwnd(), dskZipDlgProc, (LPARAM)dlgInfo);
    exitDialogShow();
}

void archEmulationStartNotification() {
    ShowWindow(st.emuHwnd, SW_NORMAL);

    if (kbdLockEnable != NULL && pProperties->emulation.disableWinKeys) {
        kbdLockEnable();
    }
}

void archEmulationStopNotification()
{
    DirectXSetGDISurface();
    ShowWindow(st.emuHwnd, SW_HIDE);

    if (kbdLockDisable != NULL) {
        kbdLockDisable();
    }
}

void archUpdateEmuDisplay(int synchronous, int evenOdd, int interlace) {
    st.evenOdd    = evenOdd;
    st.interlace  = interlace;

    if (pProperties->video.driver == P_VIDEO_DRVGDI) {
        if (!synchronous) {
            PostMessage(getMainHwnd(), WM_UPDATE, 0, 0);
        }
    }
    else {
        SetEvent(st.ddrawEvent);
        if (synchronous) {
            WaitForSingleObject(st.ddrawAckEvent, 500);
        }
    }
}

void archThemeSetNext() {
    st.themeIndex++;
    if (st.themeList[st.themeIndex] == NULL) {
        st.themeIndex = 0;
    }
    
    strcpy(pProperties->settings.themeName, st.themeList[st.themeIndex]->name);

    archUpdateWindow();
}

void archKeyboardSetSelectedKey(int keyCode) {
    keyboardSetSelectedKey(keyCode);
}

void archThemeUpdate(Theme* theme) {
    if (theme->reference == NULL) {
        themeSet(pProperties->settings.themeName, 0);
    }
    else {
        SendMessage(theme->reference, WM_UPDATE, 0, 0);
    }
}

int archGetFramesPerSecond() {
    return st.framesPerSecond;
}

void archEmulationStartFailure() {
     MessageBox(NULL, langErrorStartEmu(), langErrorTitle(), MB_ICONHAND | MB_OK);
}
