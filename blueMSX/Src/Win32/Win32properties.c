/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32properties.c,v $
**
** $Revision: 1.18 $
**
** $Date: 2005-01-29 00:28:52 $
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
#include <windows.h>
#include <tchar.h>
#include <math.h>
#include <commctrl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define STRSAFE_NO_DEPRECATE
#include <strsafe.h>

#include "Win32Properties.h"
#include "Win32DirectX.h"
#include "ThemeLoader.h"
#include "Win32keyboard.h"
#include "resource.h"
#include "Language.h"
#include "Machine.h"
#include "Board.h"

static HWND hDlgSound = NULL;
static int propModified = 0;
static Mixer* theMixer;
static Video* theVideo;
static int centered = 0;
extern void emulatorRestartSound();

static int canUseRegistry = 0;
static int useRegistry = 0;
static char* keyPath = NULL;
static char* keyFile = NULL;
static char registryKey[] = "blueMSX";

static char virtualKeys[256][32] = {
    "",
    "", //"LBUTTON", 
    "", //"RBUTTON",
    "CANCEL",
    "", //"MBUTTON",
    "", //"XBUTTON1",
    "", //"XBUTTON2",
    "",
    "BACKSPACE",
    "", //"TAB",
    "",
    "",
    "CLEAR",
    "ENTER",
    "",
    "",
    "SHIFT",
    "CTRL",
    "ALT",
    "PAUSE",
    "CAPS LOCK",
    "KANA",
    "",
    "JUNJA",
    "FINAL",
    "KANJI",
    "",
    "ESC",
    "CONVERT",
    "NONCONVERT",
    "ACCEPT",
    "MODECHANGE",
    "SPACE",
    "PAGE UP",
    "PAGE DOWN",
    "END",
    "HOME",
    "LEFT ARROW",
    "UP ARROW",
    "RIGHT ARROW",
    "DOWN ARROW",
    "SELECT",
    "PRINT",
    "EXECUTE",
    "PRINT SCREEN",
    "INS",
    "DEL",
    "HELP",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "LEFT WIN",
    "RIGHT WIN",
    "APPS",
    "",
    "SLEEP",
    "NUMPAD 0",
    "NUMPAD 1",
    "NUMPAD 2",
    "NUMPAD 3",
    "NUMPAD 4",
    "NUMPAD 5",
    "NUMPAD 6",
    "NUMPAD 7",
    "NUMPAD 8",
    "NUMPAD 9",
    "NUMPAD *",
    "NUMPAD +",
    "NUMPAD ,",
    "NUMPAD -",
    "NUMPAD .",
    "NUMPAD /",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "F13",
    "F14",
    "F15",
    "F16",
    "F17",
    "F18",
    "F19",
    "F20",
    "F21",
    "F22",
    "F23",
    "F24",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "NUM LOCK",
    "SCROLL LOCK",
    "OEM 1",
    "OEM 2",
    "OEM 3",
    "OEM 4",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "LEFT SHIFT",
    "RIGHT SHIFT",
    "LEFT CONTROL",
    "RIGHT CONTROL",
    "LEFT ALT",
    "RIGHT ALT",
    "BROWSER BACK",
    "BROWSER FORWARD",
    "BROWSER REFRESH",
    "BROWSER STOP",
    "BROWSER SEARCH",
    "BROWSER FAVORITES",
    "BROWSER HOME",
    "VOLUME MUTE",
    "VOLUME DOWN",
    "VOLUME UP",
    "NEXT TRACK",
    "PREV TRACK",
    "MEDIA STOP",
    "MEDIA PLAY",
    "LAUNCH MAIL",
    "LAUNCH MEDIA SELECT",
    "LAUNCH APP 1",
    "LAUNCH APP 2",
    "",
    "",
    ";",
    "+",
    ",",
    "-",
    ".",
    "?",
    "~",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "[",
    "\\",
    "]",
    "\"",
    "OEM 5",
    "",
    "OEM 6",
    "OEM 7",
    "OEM 8",
    "OEM 9",
    "PROCESS",
    "OEM 10",
    "",
    "",
    "OEM 11",
    "OEM 12",
    "OEM 13",
    "OEM 14",
    "OEM 15",
    "OEM 16",
    "OEM 17",
    "OEM 18",
    "OEM 19",
    "OEM 20",
    "OEM 21",
    "OEM 22",
    "OEM 23",
    "ATTN",
    "CRSEL",
    "EXSEL",
    "EREOF",
    "PLAY",
    "ZOOM",
    "",
    "PA1",
    "CLEAR",
    ""
};

static _TCHAR* pEmuFamily[] = {
    "MSX, Basic 1.0",
    "MSX, Basic 1.0 - Brazilian",
    "MSX, Basic 1.0 - Japanese",
    "MSX, Basic 1.0 - Korean",
    "MSX 2, Basic 2.1",
    "MSX 2, Basic 2.0 - Japanese", 
    "MSX 2, Basic 2.0 - Korean", 
    "MSX 2+, Basic 3.0",
    NULL
};

static _TCHAR* pEmuRAM[] = {
    "16 kBytes",
    "32 kBytes",
    "64 kBytes",
    "128 kBytes",
    "256 kBytes",
    "512 kBytes",
    "1 MBytes",
    "2 MBytes",
    "4 MBytes",
    NULL
};

static _TCHAR* pEmuVRAM[] = {
    "16 kBytes",
    "32 kBytes",
    "64 kBytes",
    "128 kBytes",
    NULL
};

static _TCHAR pVideoMonData[4][64];
static _TCHAR* pVideoMon[] = {
    pVideoMonData[0],
    pVideoMonData[1],
    pVideoMonData[2],
    pVideoMonData[3],
    NULL
};

static _TCHAR pVideoTypeData[2][64];
static _TCHAR* pVideoVideoType[] = {
    pVideoTypeData[0], 
    pVideoTypeData[1],
    NULL
};

static _TCHAR pVideoEmuData[9][64];
static _TCHAR* pVideoPalEmu[] = {
    pVideoEmuData[0],
    pVideoEmuData[1],
    pVideoEmuData[2],
    pVideoEmuData[3],
    pVideoEmuData[4],
    pVideoEmuData[5],
    pVideoEmuData[6],
    pVideoEmuData[7],
    NULL
};

static _TCHAR pVideoSizeData[6][64];
static _TCHAR* pVideoMonSize[] = {
    pVideoSizeData[0],
    pVideoSizeData[1],
    pVideoSizeData[2],
    NULL
};

static _TCHAR pVideoDriverData[3][64];
static _TCHAR* pVideoDriver[] = {
    pVideoDriverData[0],
    pVideoDriverData[1],
    pVideoDriverData[2],
    NULL
};

static _TCHAR pVideoFrameSkipData[6][64];
static _TCHAR* pVideoFrameSkip[] = {
    pVideoFrameSkipData[0],
    pVideoFrameSkipData[1],
    pVideoFrameSkipData[2],
    pVideoFrameSkipData[3],
    pVideoFrameSkipData[4],
    pVideoFrameSkipData[5],
    NULL
};

static _TCHAR pSoundDriverData[3][64];
static _TCHAR* pSoundDriver[] = {
    pSoundDriverData[0],
    pSoundDriverData[1],
    pSoundDriverData[2],
    NULL
};

static _TCHAR pEmuSyncData[2][64];
static _TCHAR* pEmuSync[] = {
    pEmuSyncData[0],
    pEmuSyncData[1],
    NULL
};

static int soundBufSizes[] = { 10, 20, 50, 100, 150, 200, 250, 300, 350 };

static _TCHAR* pSoundBufferSize[] = {
    "10 ms",
    "20 ms",
    "50 ms",
    "100 ms",
    "150 ms",
    "200 ms",
    "250 ms",
    "300 ms",
    "350 ms",
    NULL
};


static void setButtonCheck(HWND hDlg, int id, int check, int enable) {
    HWND hwnd = GetDlgItem(hDlg, id);

    if (check) {
        SendMessage(hwnd, BM_SETCHECK, BST_CHECKED, 0);
    }
    else {
        SendMessage(hwnd, BM_SETCHECK, BST_UNCHECKED, 0);
    }
    if (!enable) {
        SendMessage(hwnd, BM_SETCHECK, BST_INDETERMINATE, 0);
    }
}

static int getButtonCheck(HWND hDlg, int id) {
    HWND hwnd = GetDlgItem(hDlg, id);

    return BST_CHECKED == SendMessage(hwnd, BM_GETCHECK, 0, 0) ? 1 : 0;
}

static void initDropList(HWND hDlg, int id, _TCHAR** pList, int index) {
    while (*pList != NULL && **pList != 0) {
        SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)*pList);
        pList++;
    }

    SendDlgItemMessage(hDlg, id, CB_SETCURSEL, index, 0);
}

static int getDropListIndex(HWND hDlg, int id, _TCHAR** pList) {
    int index = 0;
    _TCHAR s[64];

    GetDlgItemText(hDlg, id, s, 63);
    
    while (*pList != NULL) {
        if (0 == _tcscmp(s, *pList)) {
            return index;
        }
        index++;
        pList++;
    }

    return -1;
}

static char* strEmuSpeed(int logFrequency) {
    UInt32 frequency = (UInt32)(3579545 * pow(2.0, (logFrequency - 50) / 15.0515));
    static char buffer[32];

    sprintf(buffer, "%d.%03dMHz (%d%%)", frequency / 1000000, (frequency / 1000) % 1000, frequency * 10 / 357954);
    return buffer;

}

static BOOL CALLBACK emulationDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    static Properties* pProperties;
    static int curSpeed;
    static char machineName[64];

    switch (iMsg) {
    case WM_INITDIALOG:    
        if (!centered) {
            updateDialogPos(GetParent(hDlg), DLG_ID_PROPERTIES, 0, 1);
            centered = 1;
        }
        pProperties = (Properties*)((PROPSHEETPAGE*)lParam)->lParam;

        SendMessage(GetDlgItem(hDlg, IDC_EMUGENERALGROUPBOX), WM_SETTEXT, 0, (LPARAM)langPropEmuGeneralGB());
        SendMessage(GetDlgItem(hDlg, IDC_EMUFAMILYTEXT), WM_SETTEXT, 0, (LPARAM)langPropEmuFamilyText());
        SendMessage(GetDlgItem(hDlg, IDC_VDPFREQTEXT), WM_SETTEXT, 0, (LPARAM)langPropVideoFreqText());
        SendMessage(GetDlgItem(hDlg, IDC_EMUSPEEDTEXT), WM_SETTEXT, 0, (LPARAM)langPropEmuSpeedText());
        SendMessage(GetDlgItem(hDlg, IDC_EMUSPEEDGROUPBOX), WM_SETTEXT, 0, (LPARAM)langPropEmuSpeedGB());
        SendMessage(GetDlgItem(hDlg, IDC_EMUFRONTSWITCHGROUPBOX), WM_SETTEXT, 0, (LPARAM)langPropEmuFrontSwitchGB());
        
        SetWindowText(GetDlgItem(hDlg, IDC_EMUFDCTIMING),   langPropEmuFdcTiming());
        SetWindowText(GetDlgItem(hDlg, IDC_EMUFRONTSWITCH), langPropEmuFrontSwitch());
        SetWindowText(GetDlgItem(hDlg, IDC_EMUPAUSESWITCH), langPropEmuPauseSwitch());
        SetWindowText(GetDlgItem(hDlg, IDC_EMUAUDIOSWITCH), langPropEmuAudioSwitch());

        setButtonCheck(hDlg, IDC_EMUFDCTIMING,   !pProperties->emulation.enableFdcTiming, 1);
        setButtonCheck(hDlg, IDC_EMUFRONTSWITCH, pProperties->emulation.frontSwitch, 1);
        setButtonCheck(hDlg, IDC_EMUPAUSESWITCH, pProperties->emulation.pauseSwitch, 1);
        setButtonCheck(hDlg, IDC_EMUAUDIOSWITCH, pProperties->emulation.audioSwitch, 1);

        curSpeed = pProperties->emulation.speed;

        SendDlgItemMessage(hDlg, IDC_VDPFREQ, CB_ADDSTRING, 0, (LPARAM)langPropVideoFreqAuto());
        SendDlgItemMessage(hDlg, IDC_VDPFREQ, CB_ADDSTRING, 0, (LPARAM)"50 Hz");
        SendDlgItemMessage(hDlg, IDC_VDPFREQ, CB_ADDSTRING, 0, (LPARAM)"60 Hz");

        SendDlgItemMessage(hDlg, IDC_VDPFREQ, CB_SETCURSEL, pProperties->emulation.vdpSyncMode, 0);

        machineName[0] = 0;

        {
            char** machineNames = machineGetAvailable(1);
            int index = 0;
            while (*machineNames != NULL) {
                _TCHAR buffer[128];

                _stprintf(buffer, "%s", *machineNames);

                SendDlgItemMessage(hDlg, IDC_EMUFAMILY, CB_ADDSTRING, 0, (LPARAM)buffer);

                if (index == 0 || 0 == strcmp(*machineNames, pProperties->emulation.machineName)) {
                    SendDlgItemMessage(hDlg, IDC_EMUFAMILY, CB_SETCURSEL, index, 0);
                    strcpy(machineName, *machineNames);
                }
                machineNames++;
                index++;
            }
        }

        SendMessage(GetDlgItem(hDlg, IDC_EMUSPEEDCUR), WM_SETTEXT, 0, (LPARAM)strEmuSpeed(curSpeed));

        SendMessage(GetDlgItem(hDlg, IDC_EMUSPEED), TBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 100));
        SendMessage(GetDlgItem(hDlg, IDC_EMUSPEED), TBM_SETPOS,   1, (LPARAM)curSpeed);

        return FALSE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_EMUFAMILY) {
            char buffer[64];
            int idx = SendMessage(GetDlgItem(hDlg, IDC_EMUFAMILY), CB_GETCURSEL, 0, 0);
            int rv = SendMessage(GetDlgItem(hDlg, IDC_EMUFAMILY), CB_GETLBTEXT, idx, (LPARAM)buffer);

            if (rv != CB_ERR) {
                if (strcmp(machineName, buffer)) {
                    strcpy(machineName, buffer);
                }
            }
            return TRUE;
        }
        return TRUE;

    case WM_NOTIFY:
        if (((NMHDR FAR*)lParam)->code == PSN_APPLY || ((NMHDR FAR*)lParam)->code == PSN_QUERYCANCEL) {
            saveDialogPos(GetParent(hDlg), DLG_ID_PROPERTIES);
        }

        if (wParam == IDC_EMUSPEED) {
            curSpeed = SendMessage(GetDlgItem(hDlg, IDC_EMUSPEED), TBM_GETPOS, 0, 0);
            SendMessage(GetDlgItem(hDlg, IDC_EMUSPEEDCUR), WM_SETTEXT, 0, (LPARAM)strEmuSpeed(curSpeed));
            return TRUE;
        }

        if ((((NMHDR FAR *)lParam)->code) != PSN_APPLY) {
            return FALSE;
        }
            
        {
            char** machineNames = machineGetAvailable(1);
            int index = 0;
            char buffer[64];

            pProperties->emulation.enableFdcTiming = !getButtonCheck(hDlg, IDC_EMUFDCTIMING);
            pProperties->emulation.frontSwitch = getButtonCheck(hDlg, IDC_EMUFRONTSWITCH);
            pProperties->emulation.pauseSwitch = getButtonCheck(hDlg, IDC_EMUPAUSESWITCH);
            pProperties->emulation.audioSwitch = getButtonCheck(hDlg, IDC_EMUAUDIOSWITCH);

            pProperties->emulation.vdpSyncMode = SendMessage(GetDlgItem(hDlg, IDC_VDPFREQ), CB_GETCURSEL, 0, 0);

            GetDlgItemText(hDlg, IDC_EMUFAMILY, buffer, 63);
            
            while (*machineNames != NULL) {
                if (0 == strcmp(buffer, *machineNames)) {
                    strcpy(pProperties->emulation.machineName, buffer);
                    break;
                }
                machineNames++;
                index++;
            }
        }

        pProperties->emulation.speed        = curSpeed;

        propModified = 1;
        
        return TRUE;
    }

    return FALSE;
}

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
    ROM_KONAMISYNTH,
    ROM_MAJUTSUSHI,
    ROM_HALNOTE,
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
    ROM_MSXMUSIC,
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
    ROM_SONYHBI55,
    ROM_MSXAUDIODEV,
    ROM_TURBORPCM,
    ROM_UNKNOWN,
};

static BOOL CALLBACK filesDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    static Properties* pProperties;
    int i;

    switch (iMsg) {
    case WM_INITDIALOG:  
        if (!centered) {
            updateDialogPos(GetParent(hDlg), DLG_ID_PROPERTIES, 0, 1);
            centered = 1;
        }
        pProperties = (Properties*)((PROPSHEETPAGE*)lParam)->lParam;
  
        SendMessage(GetDlgItem(hDlg, IDC_SETINGSFILEHISTORYGOUPBOX), WM_SETTEXT, 0, (LPARAM)langPropSetFileHistoryGB());
        SendMessage(GetDlgItem(hDlg, IDC_SETINGSHISTORYSIZETEXT), WM_SETTEXT, 0, (LPARAM)langPropSetFileHistorySize());
        SetWindowText(GetDlgItem(hDlg, IDC_SETTINGSHISTORYCLEAR), langPropSetFileHistoryClear());

        {
            _TCHAR buffer[32];
            _stprintf(buffer, "%d", pProperties->filehistory.count);
            SetWindowText(GetDlgItem(hDlg, IDC_SETINGSHISTORYSIZE), buffer);
        }

        for (i = 0; romTypeList[i] != ROM_UNKNOWN; i++) {
            SendDlgItemMessage(hDlg, IDC_SETTINGSROMTYPE, CB_ADDSTRING, 0, (LPARAM)romTypeToString(romTypeList[i]));
            if (pProperties->cartridge.defaultType == romTypeList[i]) {
                SendDlgItemMessage(hDlg, IDC_SETTINGSROMTYPE, CB_SETCURSEL, i, 0);
            }
        }

        SetWindowText(GetDlgItem(hDlg, IDC_SETTINGSROMTYPEGB), langPropOpenRomGB());
        SetWindowText(GetDlgItem(hDlg, IDC_SETTINGSROMTYPETEXT), langPropDefaultRomType());

        SendDlgItemMessage(hDlg, IDC_SETTINGSROMTYPE, CB_ADDSTRING, 0, (LPARAM)langPropGuessRomType());
        if (pProperties->cartridge.defaultType == romTypeList[i]) {
            SendDlgItemMessage(hDlg, IDC_SETTINGSROMTYPE, CB_SETCURSEL, i, 0);
        }

        SetWindowText(GetDlgItem(hDlg, IDC_SETTINGSDEFSLOTSGB), langPropSettDefSlotGB());
        SetWindowText(GetDlgItem(hDlg, IDC_SETTINGSSLOTS), langPropSettDefSlots());
        SetWindowText(GetDlgItem(hDlg, IDC_SETTINGSSLOT1), langPropSettDefSlot1());
        SetWindowText(GetDlgItem(hDlg, IDC_SETTINGSSLOT2), langPropSettDefSlot2());
        SetWindowText(GetDlgItem(hDlg, IDC_SETTINGSDRIVES), langPropSettDefDrives());
        SetWindowText(GetDlgItem(hDlg, IDC_SETTINGSDRIVEA), langPropSettDefDriveA());
        SetWindowText(GetDlgItem(hDlg, IDC_SETTINGSDRIVEB), langPropSettDefDriveB());


        setButtonCheck(hDlg, IDC_SETTINGSSLOT1, pProperties->cartridge.quickStartDrive == 0, 1);
        setButtonCheck(hDlg, IDC_SETTINGSSLOT2, pProperties->cartridge.quickStartDrive == 1, 1);
        setButtonCheck(hDlg, IDC_SETTINGSDRIVEA, pProperties->diskdrive.quickStartDrive == 0, 1);
        setButtonCheck(hDlg, IDC_SETTINGSDRIVEB, pProperties->diskdrive.quickStartDrive == 1, 1);

        return FALSE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_SETTINGSHISTORYCLEAR:
            {
                int rv = MessageBox(NULL, langPropClearFileHistory(), langWarningTitle(), MB_ICONWARNING | MB_OKCANCEL);
                if (rv == IDOK) {
                    int i;

                    for (i = 0; i < MAX_HISTORY; i++) {
                        pProperties->filehistory.cartridgeA[i][0] = 0;
                        pProperties->filehistory.cartridgeB[i][0] = 0;
                        pProperties->filehistory.diskdriveA[i][0] = 0;
                        pProperties->filehistory.diskdriveB[i][0] = 0;
                        pProperties->filehistory.cassette[i][0] = 0;
                    }

                    pProperties->filehistory.quicksave[0] = 0;

                    EnableWindow(GetDlgItem(hDlg, IDC_SETTINGSHISTORYCLEAR), FALSE);
                }
            }
            break;

        case IDC_SETTINGSSLOT1:
            setButtonCheck(hDlg, IDC_SETTINGSSLOT1, 1, 1);
            setButtonCheck(hDlg, IDC_SETTINGSSLOT2, 0, 1);
            break;

        case IDC_SETTINGSSLOT2:
            setButtonCheck(hDlg, IDC_SETTINGSSLOT1, 0, 1);
            setButtonCheck(hDlg, IDC_SETTINGSSLOT2, 1, 1);
            break;

        case IDC_SETTINGSDRIVEA:
            setButtonCheck(hDlg, IDC_SETTINGSDRIVEA, 1, 1);
            setButtonCheck(hDlg, IDC_SETTINGSDRIVEB, 0, 1);
            break;

        case IDC_SETTINGSDRIVEB:
            setButtonCheck(hDlg, IDC_SETTINGSDRIVEA, 0, 1);
            setButtonCheck(hDlg, IDC_SETTINGSDRIVEB, 1, 1);
            break;
        }
        return TRUE;

    case WM_NOTIFY:
        if (((NMHDR FAR*)lParam)->code == PSN_APPLY || ((NMHDR FAR*)lParam)->code == PSN_QUERYCANCEL) {
            saveDialogPos(GetParent(hDlg), DLG_ID_PROPERTIES);
        }

        if ((((NMHDR FAR *)lParam)->code) != PSN_APPLY) {
            return FALSE;
        }
        
        i = SendMessage(GetDlgItem(hDlg, IDC_SETTINGSROMTYPE), CB_GETCURSEL, 0, 0);
        if (i != CB_ERR) {
            pProperties->cartridge.defaultType = romTypeList[i];
        }

        {
            char buffer[64];

            GetDlgItemText(hDlg, IDC_SETINGSHISTORYSIZE, buffer, 63);

            if (isdigit(*buffer)) {
                int count = atoi(buffer);
                if (count < 0)  count = 0;
                if (count > 30) count = 30;

                pProperties->filehistory.count = count;
            }
        }

        pProperties->cartridge.quickStartDrive = getButtonCheck(hDlg, IDC_SETTINGSSLOT2) ? 1 : 0;
        pProperties->diskdrive.quickStartDrive = getButtonCheck(hDlg, IDC_SETTINGSDRIVEB) ? 1 : 0;

        propModified = 1;
        
        return TRUE;
    }

    return FALSE;
}

extern void archUpdateWindow();

static BOOL CALLBACK settingsDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    static Properties* pProperties;
    static char oldTheme[128];

    switch (iMsg) {
    case WM_INITDIALOG:
        if (!centered) {
            updateDialogPos(GetParent(hDlg), DLG_ID_PROPERTIES, 0, 1);
            centered = 1;
        }
        pProperties = (Properties*)((PROPSHEETPAGE*)lParam)->lParam;
        strcpy(oldTheme, pProperties->settings.themeName);

        SetWindowText(GetDlgItem(hDlg, IDC_APEARANCETHEMEGB), langPropThemeGB());
        SetWindowText(GetDlgItem(hDlg, IDC_APEARANCETHEMETEXT), langPropTheme());

        {
            ThemeCollection** themeNames = themeGetAvailable();
            int index = 0;
            while (*themeNames != NULL) {
                SendDlgItemMessage(hDlg, IDC_APEARANCETHEME, CB_ADDSTRING, 0, (LPARAM)*themeNames);

                if (index == 0 || 0 == strcmp((*themeNames)->name, pProperties->settings.themeName)) {
                    SendDlgItemMessage(hDlg, IDC_APEARANCETHEME, CB_SETCURSEL, index, 0);
                }
                themeNames++;
                index++;
            }
        }

        SetWindowText(GetDlgItem(hDlg, IDC_SETTINGSWINDOWSENV), langPropWindowsEnvGB());
        SetWindowText(GetDlgItem(hDlg, IDC_SETTINGSSCREENSAVER), langPropScreenSaver());
        SetWindowText(GetDlgItem(hDlg, IDC_SETTINGSFILETYPES), langPropFileTypes());
        SetWindowText(GetDlgItem(hDlg, IDC_SETTINGSDISABLEWINKEYS), langPropDisableWinKeys());
        SetWindowText(GetDlgItem(hDlg, IDC_SETTINGSPRIORITYBOOST), langPropPriorityBoost());
        SetWindowText(GetDlgItem(hDlg, IDC_SETTINGSUSEREGISTRY), langPropUseRegistry());

        setButtonCheck(hDlg, IDC_SETTINGSFILETYPES, pProperties->emulation.registerFileTypes, 1);
        setButtonCheck(hDlg, IDC_SETTINGSDISABLEWINKEYS, pProperties->emulation.disableWinKeys, 1);
        setButtonCheck(hDlg, IDC_SETTINGSPRIORITYBOOST, pProperties->emulation.priorityBoost, 1);
        setButtonCheck(hDlg, IDC_SETTINGSSCREENSAVER, pProperties->settings.disableScreensaver, 1);
        setButtonCheck(hDlg, IDC_SETTINGSUSEREGISTRY, useRegistry && canUseRegistry, 1);
        EnableWindow(GetDlgItem(hDlg, IDC_SETTINGSUSEREGISTRY), canUseRegistry);

        return FALSE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_APEARANCETHEME:
            if (HIWORD(wParam) == CBN_SELCHANGE) {
                char buffer[128];
                int idx = SendMessage(GetDlgItem(hDlg, IDC_APEARANCETHEME), CB_GETCURSEL, 0, 0);
                int rv = SendMessage(GetDlgItem(hDlg, IDC_APEARANCETHEME), CB_GETLBTEXT, idx, (LPARAM)buffer);

                if (rv != CB_ERR) {
                    strcpy(pProperties->settings.themeName, buffer);
                    archUpdateWindow();
                    SetFocus(GetParent(hDlg));
                }
            }
            break;
        }
        return 0;

    case WM_NOTIFY:
        if (((NMHDR FAR*)lParam)->code == PSN_APPLY || ((NMHDR FAR*)lParam)->code == PSN_QUERYCANCEL) {
            saveDialogPos(GetParent(hDlg), DLG_ID_PROPERTIES);
        }

        if ((((NMHDR FAR *)lParam)->code) == PSN_QUERYCANCEL) {
            strcpy(pProperties->settings.themeName, oldTheme);
            archUpdateWindow();
            return FALSE;
        }
        if ((((NMHDR FAR *)lParam)->code) == PSN_APPLY) {
            return FALSE;
        }

        pProperties->emulation.registerFileTypes = getButtonCheck(hDlg, IDC_SETTINGSFILETYPES);
        pProperties->emulation.disableWinKeys    = getButtonCheck(hDlg, IDC_SETTINGSDISABLEWINKEYS);
        pProperties->settings.disableScreensaver = getButtonCheck(hDlg, IDC_SETTINGSSCREENSAVER);
        pProperties->emulation.priorityBoost     = getButtonCheck(hDlg, IDC_SETTINGSPRIORITYBOOST);
        if (canUseRegistry) {
            useRegistry = getButtonCheck(hDlg, IDC_SETTINGSUSEREGISTRY);
        }

        propModified = 1;
        
        return TRUE;
    }

    return FALSE;
}

static void updateFullscreenResList(HWND hDlg) {
    int count = DirectDrawGetAvailableDisplayModeCount();
    DxDisplayMode* curDdm = DirectDrawGetDisplayMode();
    int i;

    while (CB_ERR != SendDlgItemMessage(hDlg, IDC_PERFFULLSCREEN, CB_DELETESTRING, 0, 0));

    for (i = 0; i < count; i++) {
        char text[32];
        DxDisplayMode* ddm = DirectDrawGetAvailableDisplayMode(i);
        sprintf(text, "%d x %d - %d bit", ddm->width, ddm->height, ddm->bitCount);
        SendDlgItemMessage(hDlg, IDC_PERFFULLSCREEN, CB_ADDSTRING, 0, (LPARAM)text);
        if (ddm->width == curDdm->width && ddm->height == curDdm->height && ddm->bitCount == curDdm->bitCount) {
            SendDlgItemMessage(hDlg, IDC_PERFFULLSCREEN, CB_SETCURSEL, i, 0);
        }
    }
}

static void getFullscreenResList(HWND hDlg, int* width, int* height, int* bitCount) 
{
    DxDisplayMode* ddm = NULL;
    int index = SendDlgItemMessage(hDlg, IDC_PERFFULLSCREEN, CB_GETCURSEL, 0, 0);

    if (index >= 0) {
        ddm = DirectDrawGetAvailableDisplayMode(index);
    }
    if (ddm == NULL) {
        ddm = DirectDrawGetDisplayMode();
    }
    *width    = ddm->width;
    *height   = ddm->height;
    *bitCount = ddm->bitCount;
}


static BOOL CALLBACK performanceDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    static Properties* pProperties;

    switch (iMsg) {
    case WM_INITDIALOG:
        if (!centered) {
            updateDialogPos(GetParent(hDlg), DLG_ID_PROPERTIES, 0, 1);
            centered = 1;
        }
        pProperties = (Properties*)((PROPSHEETPAGE*)lParam)->lParam;

        /* Init language specific dropdown list data */
        _stprintf(pVideoDriver[0], "%s", langEnumVideoDrvDirectDrawHW());
        _stprintf(pVideoDriver[1], "%s", langEnumVideoDrvDirectDraw());
        _stprintf(pVideoDriver[2], "%s", langEnumVideoDrvGDI());

        _stprintf(pVideoFrameSkip[0], "%s", langEnumVideoFrameskip0());
        _stprintf(pVideoFrameSkip[1], "%s", langEnumVideoFrameskip1());
        _stprintf(pVideoFrameSkip[2], "%s", langEnumVideoFrameskip2());
        _stprintf(pVideoFrameSkip[3], "%s", langEnumVideoFrameskip3());
        _stprintf(pVideoFrameSkip[4], "%s", langEnumVideoFrameskip4());
        _stprintf(pVideoFrameSkip[5], "%s", langEnumVideoFrameskip5());

        _stprintf(pSoundDriver[0], "%s", langEnumSoundDrvNone());
        _stprintf(pSoundDriver[1], "%s", langEnumSoundDrvWMM());
        _stprintf(pSoundDriver[2], "%s", langEnumSoundDrvDirectX());

        _stprintf(pEmuSync[0], "%s", langEnumEmuSync1ms());
        _stprintf(pEmuSync[1], "%s", langEnumEmuSyncAuto());

        /* Init language specific dialog items */
        SendDlgItemMessage(hDlg, IDC_PERFVIDEODRVGROUPBOX, WM_SETTEXT, 0, (LPARAM)langPropPerfVideoDrvGB());
        SendDlgItemMessage(hDlg, IDC_PERFDISPDRVTEXT, WM_SETTEXT, 0, (LPARAM)langPropPerfVideoDispDrvText());
        SendDlgItemMessage(hDlg, IDC_PERFFRAMESKIPTEXT, WM_SETTEXT, 0, (LPARAM)langPropPerfFrameSkipText());
        SendDlgItemMessage(hDlg, IDC_AUDIODRVGROUPBOX, WM_SETTEXT, 0, (LPARAM)langPropPerfAudioDrvGB());
        SendDlgItemMessage(hDlg, IDC_PERFSNDDRVTEXT, WM_SETTEXT, 0, (LPARAM)langPropPerfAudioDrvText());
        SendDlgItemMessage(hDlg, IDC_PERFSNDBUFSZTEXT, WM_SETTEXT, 0, (LPARAM)langPropPerfAudioBufSzText());
        SendDlgItemMessage(hDlg, IDC_PERFEMUGROUPBOX, WM_SETTEXT, 0, (LPARAM)langPropPerfEmuGB());
        SendDlgItemMessage(hDlg, IDC_PERFSYNCMODETEXT, WM_SETTEXT, 0, (LPARAM)langPropPerfSyncModeText());
        SendDlgItemMessage(hDlg, IDC_PERFFULLSCREEN, WM_SETTEXT, 0, (LPARAM)langPropFullscreenResText());
        

        initDropList(hDlg, IDC_SNDDRIVER, pSoundDriver, pProperties->sound.driver);
        {
            int index = 0;
            while (pProperties->sound.bufSize > soundBufSizes[index]) {
                if (soundBufSizes[index] == 350) {
                    break;
                }
                index++;
            }
            initDropList(hDlg, IDC_SNDBUFSZ, pSoundBufferSize, index);
        }
        initDropList(hDlg, IDC_VIDEODRV, pVideoDriver, pProperties->video.driver);
        initDropList(hDlg, IDC_FRAMESKIP, pVideoFrameSkip, pProperties->video.frameSkip);
        initDropList(hDlg, IDC_EMUSYNC, pEmuSync, pProperties->emulation.syncMethod);

        updateFullscreenResList(hDlg);

        return FALSE;

    case WM_NOTIFY:
        if (((NMHDR FAR*)lParam)->code == PSN_APPLY || ((NMHDR FAR*)lParam)->code == PSN_QUERYCANCEL) {
            saveDialogPos(GetParent(hDlg), DLG_ID_PROPERTIES);
        }

        if ((((NMHDR FAR *)lParam)->code) != PSN_APPLY) {
            return FALSE;
        }
            
        getFullscreenResList(hDlg, 
                             &pProperties->video.fullscreen.width,
                             &pProperties->video.fullscreen.height,
                             &pProperties->video.fullscreen.bitDepth);
                                
        pProperties->sound.driver           = getDropListIndex(hDlg, IDC_SNDDRIVER, pSoundDriver);
        pProperties->sound.bufSize          = soundBufSizes[getDropListIndex(hDlg, IDC_SNDBUFSZ, pSoundBufferSize)];
        pProperties->video.driver           = getDropListIndex(hDlg, IDC_VIDEODRV, pVideoDriver);
        pProperties->video.frameSkip        = getDropListIndex(hDlg, IDC_FRAMESKIP, pVideoFrameSkip);
        pProperties->emulation.syncMethod   = getDropListIndex(hDlg, IDC_EMUSYNC, pEmuSync);

        DirectDrawSetDisplayMode(pProperties->video.fullscreen.width,
                                pProperties->video.fullscreen.height,
                                pProperties->video.fullscreen.bitDepth);

        propModified = 1;
        
        return TRUE;
    }

    return FALSE;
}

extern void updateEmuWindow();

static char* strPct(int value) {
    static char buffer[32];
    sprintf(buffer, "%d%%", value);
    return buffer;
}

static char* strDec(int value) {
    static char buffer[32];
    sprintf(buffer, "%d.%.2d", value / 100, value % 100);
    return buffer;
}

static char* strPt(int value) {
    static char buffer[32];
    sprintf(buffer, "%d.%d", value / 2, 5 * (value & 1));
    return buffer;
}

static BOOL CALLBACK videoDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    static Properties* pProperties;
    static int palEmu;
    static int monType;
    static int oldScanlinesEnable;
    static int oldScanlinesPct;
    static int oldColorGhostingEnable;
    static int oldColorGhostingWidth;
    static int oldHoriz;
    static int oldVert;
    static int oldDeinterlace;
    static int brightness;
    static int saturation;
    static int contrast;
    static int gamma;
    int value;

    switch (iMsg) {
    case WM_INITDIALOG:
        if (!centered) {
            updateDialogPos(GetParent(hDlg), DLG_ID_PROPERTIES, 0, 1);
            centered = 1;
        }
        pProperties = (Properties*)((PROPSHEETPAGE*)lParam)->lParam;

        /* Init language specific dropdown list data */
        _stprintf(pVideoMon[0], "%s", langEnumVideoMonColor());
        _stprintf(pVideoMon[1], "%s", langEnumVideoMonGrey());
        _stprintf(pVideoMon[2], "%s", langEnumVideoMonGreen());
        _stprintf(pVideoMon[3], "%s", langEnumVideoMonAmber());

        _stprintf(pVideoVideoType[0], "%s", langEnumVideoTypePAL());
        _stprintf(pVideoVideoType[1], "%s", langEnumVideoTypeNTSC());

        _stprintf(pVideoPalEmu[0], "%s", langEnumVideoEmuNone());
        _stprintf(pVideoPalEmu[1], "%s", langEnumVideoEmuMonitor());
        _stprintf(pVideoPalEmu[2], "%s", langEnumVideoEmuYc());
        _stprintf(pVideoPalEmu[3], "%s", langEnumVideoEmuYcBlur());
        _stprintf(pVideoPalEmu[4], "%s", langEnumVideoEmuComp());
        _stprintf(pVideoPalEmu[5], "%s", langEnumVideoEmuCompBlur());
        _stprintf(pVideoPalEmu[6], "%s", langEnumVideoEmuScale2x());
        _stprintf(pVideoPalEmu[7], "%s", langEnumVideoEmuHq2x());

        _stprintf(pVideoMonSize[0], "%s", langEnumVideoSize1x());
        _stprintf(pVideoMonSize[1], "%s", langEnumVideoSize2x());
        _stprintf(pVideoMonSize[2], "%s", langEnumVideoSizeFullscreen());

        /* Init language specific dialog items */
        SendMessage(GetDlgItem(hDlg, IDC_MONGROUPBOX), WM_SETTEXT, 0, (LPARAM)langPropMonMonGB());
        SendMessage(GetDlgItem(hDlg, IDC_MONTYPETEXT), WM_SETTEXT, 0, (LPARAM)langPropMonTypeText());
        SendMessage(GetDlgItem(hDlg, IDC_MONEMUTEXT), WM_SETTEXT, 0, (LPARAM)langPropMonEmuText());
        SendMessage(GetDlgItem(hDlg, IDC_MONVIDEOTYPETEXT), WM_SETTEXT, 0, (LPARAM)langPropVideoYypeText());
        SendMessage(GetDlgItem(hDlg, IDC_MONWINDOWSIZETEXT), WM_SETTEXT, 0, (LPARAM)langPropWindowSizeText());
        SendMessage(GetDlgItem(hDlg, IDC_MONHORIZSTRETCH), WM_SETTEXT, 0, (LPARAM)langPropMonHorizStretch());
        SendMessage(GetDlgItem(hDlg, IDC_MONVERTSTRETCH), WM_SETTEXT, 0, (LPARAM)langPropMonVertStretch());
        SendMessage(GetDlgItem(hDlg, IDC_MONDEINTERLACE), WM_SETTEXT, 0, (LPARAM)langPropMonDeInterlace());

        setButtonCheck(hDlg, IDC_MONHORIZSTRETCH, pProperties->video.horizontalStretch, 1);
        setButtonCheck(hDlg, IDC_MONVERTSTRETCH, pProperties->video.verticalStretch, 1);
        setButtonCheck(hDlg, IDC_MONDEINTERLACE, pProperties->video.deInterlace, 1);

        /* Init dropdown lists */
        initDropList(hDlg, IDC_MONTYPE, pVideoMon, pProperties->video.monType);
        initDropList(hDlg, IDC_PALEMU, pVideoPalEmu, pProperties->video.palEmu);
        initDropList(hDlg, IDC_MONSIZE, pVideoMonSize, pProperties->video.size);

        palEmu             = pProperties->video.palEmu;
        monType            = pProperties->video.monType;

        oldScanlinesEnable     = pProperties->video.scanlinesEnable;
        oldScanlinesPct        = pProperties->video.scanlinesPct;
        oldColorGhostingEnable = pProperties->video.colorSaturationEnable;
        oldColorGhostingWidth  = pProperties->video.colorSaturationWidth;
        oldHoriz               = pProperties->video.horizontalStretch;
        oldVert                = pProperties->video.verticalStretch;
        oldDeinterlace         = pProperties->video.deInterlace;

        SendMessage(GetDlgItem(hDlg, IDC_MONBRIGHTNESSTEXT), WM_SETTEXT, 0, (LPARAM)langPropMonBrightness());
        SendMessage(GetDlgItem(hDlg, IDC_MONCONTRASTTEXT), WM_SETTEXT, 0, (LPARAM)langPropMonContrast());
        SendMessage(GetDlgItem(hDlg, IDC_MONSATURATIONTEXT), WM_SETTEXT, 0, (LPARAM)langPropMonSaturation());
        SendMessage(GetDlgItem(hDlg, IDC_MONGAMMATEXT), WM_SETTEXT, 0, (LPARAM)langPropMonGamma());
        SendMessage(GetDlgItem(hDlg, IDC_SCANLINESENABLE), WM_SETTEXT, 0, (LPARAM)langPropMonScanlines());
        SendMessage(GetDlgItem(hDlg, IDC_COLORGHOSTINGENABLE), WM_SETTEXT, 0, (LPARAM)langPropMonColorGhosting());
        

        contrast   = pProperties->video.contrast;
        brightness = pProperties->video.brightness;
        saturation = pProperties->video.saturation;
        gamma      = pProperties->video.gamma;

        setButtonCheck(hDlg, IDC_SCANLINESENABLE, pProperties->video.scanlinesEnable, 1);
        setButtonCheck(hDlg, IDC_COLORGHOSTINGENABLE, pProperties->video.colorSaturationEnable, 1);

        EnableWindow(GetDlgItem(hDlg, IDC_SCANLINESSLIDEBAR), oldScanlinesEnable);
        EnableWindow(GetDlgItem(hDlg, IDC_SCANLINESVALUE), oldScanlinesEnable);
        
        EnableWindow(GetDlgItem(hDlg, IDC_COLORGHOSTINGSLIDEBAR), oldColorGhostingEnable);
        EnableWindow(GetDlgItem(hDlg, IDC_COLORGHOSTINGVALUE), oldColorGhostingEnable);

        SendMessage(GetDlgItem(hDlg, IDC_SCANLINESSLIDEBAR), TBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 100));
        SendMessage(GetDlgItem(hDlg, IDC_SCANLINESSLIDEBAR), TBM_SETPOS,   1, (LPARAM)(100 - oldScanlinesPct));
        SendMessage(GetDlgItem(hDlg, IDC_SCANLINESVALUE), WM_SETTEXT, 0, (LPARAM)strPct(100 - oldScanlinesPct));

        SendMessage(GetDlgItem(hDlg, IDC_COLORGHOSTINGSLIDEBAR), TBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 4));
        SendMessage(GetDlgItem(hDlg, IDC_COLORGHOSTINGSLIDEBAR), TBM_SETPOS,   1, (LPARAM)oldColorGhostingWidth);
        SendMessage(GetDlgItem(hDlg, IDC_COLORGHOSTINGVALUE), WM_SETTEXT, 0, (LPARAM)strPt(oldColorGhostingWidth));

        SendMessage(GetDlgItem(hDlg, IDC_MONSATURATIONSLIDE), TBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 200));
        SendMessage(GetDlgItem(hDlg, IDC_MONSATURATIONSLIDE), TBM_SETPOS,   1, (LPARAM)saturation);
        SendMessage(GetDlgItem(hDlg, IDC_MONSATURATIONVALUE), WM_SETTEXT, 0, (LPARAM)strDec(saturation));

        SendMessage(GetDlgItem(hDlg, IDC_MONBRIGHTNESSSLIDE), TBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 200));
        SendMessage(GetDlgItem(hDlg, IDC_MONBRIGHTNESSSLIDE), TBM_SETPOS,   1, (LPARAM)brightness);
        SendMessage(GetDlgItem(hDlg, IDC_MONBRIGHTNESSVALUE), WM_SETTEXT, 0, (LPARAM)strDec(brightness));

        SendMessage(GetDlgItem(hDlg, IDC_MONCONTRASTSLIDE), TBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 200));
        SendMessage(GetDlgItem(hDlg, IDC_MONCONTRASTSLIDE), TBM_SETPOS,   1, (LPARAM)contrast);
        SendMessage(GetDlgItem(hDlg, IDC_MONCONTRASTVALUE), WM_SETTEXT, 0, (LPARAM)strDec(contrast));

        SendMessage(GetDlgItem(hDlg, IDC_MONGAMMASLIDE), TBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 200));
        SendMessage(GetDlgItem(hDlg, IDC_MONGAMMASLIDE), TBM_SETPOS,   1, (LPARAM)gamma);
        SendMessage(GetDlgItem(hDlg, IDC_MONGAMMAVALUE), WM_SETTEXT, 0, (LPARAM)strDec(gamma));

        EnableWindow(GetDlgItem(hDlg, IDC_MONSATURATIONSLIDE), monType == P_VIDEO_COLOR);
        EnableWindow(GetDlgItem(hDlg, IDC_MONSATURATIONVALUE), monType == P_VIDEO_COLOR);
        EnableWindow(GetDlgItem(hDlg, IDC_MONSATURATIONTEXT), monType == P_VIDEO_COLOR);

        return FALSE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_SCANLINESENABLE:
            pProperties->video.scanlinesEnable = getButtonCheck(hDlg, IDC_SCANLINESENABLE);
            EnableWindow(GetDlgItem(hDlg, IDC_SCANLINESSLIDEBAR), pProperties->video.scanlinesEnable);
            EnableWindow(GetDlgItem(hDlg, IDC_SCANLINESVALUE), pProperties->video.scanlinesEnable);
            
            videoSetScanLines(theVideo, pProperties->video.scanlinesEnable, pProperties->video.scanlinesPct);
            updateEmuWindow();
            break;

        case IDC_COLORGHOSTINGENABLE:
            pProperties->video.colorSaturationEnable = getButtonCheck(hDlg, IDC_COLORGHOSTINGENABLE);
            EnableWindow(GetDlgItem(hDlg, IDC_COLORGHOSTINGSLIDEBAR), pProperties->video.colorSaturationEnable);
            EnableWindow(GetDlgItem(hDlg, IDC_COLORGHOSTINGVALUE), pProperties->video.colorSaturationEnable);



            videoSetColorSaturation(theVideo, pProperties->video.colorSaturationEnable, pProperties->video.colorSaturationWidth);
            updateEmuWindow();
            break;

        case IDC_PALEMU:
            palEmu = getDropListIndex(hDlg, IDC_PALEMU, pVideoPalEmu);
            videoSetPalMode(theVideo, palEmu);
            updateEmuWindow();
            break;

        case IDC_MONTYPE:
            monType = getDropListIndex(hDlg, IDC_MONTYPE, pVideoMon);
            switch (monType) {
            case P_VIDEO_COLOR:
                videoSetColorMode(theVideo, VIDEO_COLOR);
                break;
            case P_VIDEO_BW:
                videoSetColorMode(theVideo, VIDEO_BLACKWHITE);
                break;
            case P_VIDEO_GREEN:
                videoSetColorMode(theVideo, VIDEO_GREEN);
                break;
            case P_VIDEO_AMBER:
                videoSetColorMode(theVideo, VIDEO_AMBER);
                break;
            }
            EnableWindow(GetDlgItem(hDlg, IDC_MONSATURATIONSLIDE), monType == P_VIDEO_COLOR);
            EnableWindow(GetDlgItem(hDlg, IDC_MONSATURATIONVALUE), monType == P_VIDEO_COLOR);
            EnableWindow(GetDlgItem(hDlg, IDC_MONSATURATIONTEXT), monType == P_VIDEO_COLOR);
            updateEmuWindow();
            break;

        case IDC_MONHORIZSTRETCH:
            pProperties->video.horizontalStretch = getButtonCheck(hDlg, IDC_MONHORIZSTRETCH);
            updateEmuWindow();
            break;

        case IDC_MONVERTSTRETCH:
            pProperties->video.verticalStretch   = getButtonCheck(hDlg, IDC_MONVERTSTRETCH);
            updateEmuWindow();
            break;
        case IDC_MONDEINTERLACE:
            pProperties->video.deInterlace   = getButtonCheck(hDlg, IDC_MONDEINTERLACE);
            videoSetDeInterlace(theVideo, pProperties->video.deInterlace);
            updateEmuWindow();
        }
        break;

    case WM_NOTIFY:
        if (((NMHDR FAR*)lParam)->code == PSN_APPLY || ((NMHDR FAR*)lParam)->code == PSN_QUERYCANCEL) {
            saveDialogPos(GetParent(hDlg), DLG_ID_PROPERTIES);
        }

        switch (wParam) {
        case IDC_SCANLINESSLIDEBAR:
            pProperties->video.scanlinesPct = 100 - SendMessage(GetDlgItem(hDlg, IDC_SCANLINESSLIDEBAR), TBM_GETPOS, 0, 0);
            SendMessage(GetDlgItem(hDlg, IDC_SCANLINESVALUE), WM_SETTEXT, 0, (LPARAM)strPct(100 - pProperties->video.scanlinesPct));

            videoSetScanLines(theVideo, pProperties->video.scanlinesEnable, pProperties->video.scanlinesPct);

            updateEmuWindow();
            return 0;
            
        case IDC_COLORGHOSTINGSLIDEBAR:
            pProperties->video.colorSaturationWidth = SendMessage(GetDlgItem(hDlg, IDC_COLORGHOSTINGSLIDEBAR), TBM_GETPOS, 0, 0);
            SendMessage(GetDlgItem(hDlg, IDC_COLORGHOSTINGVALUE), WM_SETTEXT, 0, (LPARAM)strPt(pProperties->video.colorSaturationWidth));

            videoSetColorSaturation(theVideo, pProperties->video.colorSaturationEnable, pProperties->video.colorSaturationWidth);
            updateEmuWindow();
            return 0;

        case IDC_MONSATURATIONSLIDE:
            value = SendMessage(GetDlgItem(hDlg, IDC_MONSATURATIONSLIDE), TBM_GETPOS, 0, 0);
            if (value != saturation) {
                saturation = value;
                SendMessage(GetDlgItem(hDlg, IDC_MONSATURATIONVALUE), WM_SETTEXT, 0, (LPARAM)strDec(saturation));
                videoSetColors(theVideo, saturation, brightness, contrast, gamma);
                updateEmuWindow();
            }
            return 0;

        case IDC_MONBRIGHTNESSSLIDE:
            value = SendMessage(GetDlgItem(hDlg, IDC_MONBRIGHTNESSSLIDE), TBM_GETPOS, 0, 0);
            if (value != brightness) {
                brightness = value;
                SendMessage(GetDlgItem(hDlg, IDC_MONBRIGHTNESSVALUE), WM_SETTEXT, 0, (LPARAM)strDec(brightness));
                videoSetColors(theVideo, saturation, brightness, contrast, gamma);
                updateEmuWindow();
            }
            return 0;

        case IDC_MONCONTRASTSLIDE:
            value = SendMessage(GetDlgItem(hDlg, IDC_MONCONTRASTSLIDE), TBM_GETPOS, 0, 0);
            if (value != contrast) {
                contrast = value;
                SendMessage(GetDlgItem(hDlg, IDC_MONCONTRASTVALUE), WM_SETTEXT, 0, (LPARAM)strDec(contrast));
                videoSetColors(theVideo, saturation, brightness, contrast, gamma);
                updateEmuWindow();
            }

        case IDC_MONGAMMASLIDE:
            value = SendMessage(GetDlgItem(hDlg, IDC_MONGAMMASLIDE), TBM_GETPOS, 0, 0);
            if (value != gamma) {
                gamma = value;
                SendMessage(GetDlgItem(hDlg, IDC_MONGAMMAVALUE), WM_SETTEXT, 0, (LPARAM)strDec(gamma));
                videoSetColors(theVideo, saturation, brightness, contrast, gamma);
                updateEmuWindow();
            }
            return 0;
        }

        if ((((NMHDR FAR *)lParam)->code) == PSN_QUERYCANCEL) {
            videoSetScanLines(theVideo, pProperties->video.scanlinesEnable, pProperties->video.scanlinesPct);

            videoSetColorSaturation(theVideo, pProperties->video.colorSaturationEnable, pProperties->video.colorSaturationWidth);
            videoSetPalMode(theVideo, pProperties->video.palEmu);
            videoSetColors(theVideo, pProperties->video.saturation, pProperties->video.brightness, 
                           pProperties->video.contrast, pProperties->video.gamma);
            switch (pProperties->video.monType) {
            case P_VIDEO_COLOR:
                videoSetColorMode(theVideo, VIDEO_COLOR);
                break;
            case P_VIDEO_BW:
                videoSetColorMode(theVideo, VIDEO_BLACKWHITE);
                break;
            case P_VIDEO_GREEN:
                videoSetColorMode(theVideo, VIDEO_GREEN);
                break;
            case P_VIDEO_AMBER:
                videoSetColorMode(theVideo, VIDEO_AMBER);
                break;
            }
            pProperties->video.horizontalStretch     = oldHoriz;
            pProperties->video.verticalStretch       = oldVert;
            pProperties->video.deInterlace           = oldDeinterlace;
            pProperties->video.scanlinesEnable       = oldScanlinesEnable;
            pProperties->video.scanlinesPct          = oldScanlinesPct;
            pProperties->video.colorSaturationEnable = oldColorGhostingEnable;
            pProperties->video.colorSaturationWidth  = oldColorGhostingWidth;
            updateEmuWindow();
            return FALSE;
        }
        else if ((((NMHDR FAR *)lParam)->code) != PSN_APPLY) {
            return FALSE;
        }

        pProperties->video.monType           = monType;
        pProperties->video.palEmu            = palEmu;
//        pProperties->video.size              = getDropListIndex(hDlg, IDC_MONSIZE, pVideoMonSize);
        pProperties->video.contrast          = contrast;
        pProperties->video.brightness        = brightness;
        pProperties->video.saturation        = saturation;
        pProperties->video.gamma             = gamma;
        propModified = 1;
        
        return TRUE;
    }

    return FALSE;
}

static void CreateToolTip(HWND hwndCtrl, HWND* hwndTT, TOOLINFO* ti)
{
    *hwndTT = CreateWindow(TOOLTIPS_CLASS, TEXT(""), WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL, (HMENU)NULL, GetModuleHandle(NULL), NULL);

    ti->cbSize = sizeof(TOOLINFO);
    ti->uFlags = TTF_IDISHWND | TTF_CENTERTIP | TTF_ABSOLUTE;
    ti->hwnd   = hwndCtrl;
    ti->uId    = (UINT)hwndCtrl;
    ti->hinst  = GetModuleHandle(NULL);
    ti->lpszText  = "";
    ti->rect.left = ti->rect.top = ti->rect.bottom = ti->rect.right = 60; 

    SendMessage(*hwndTT, TTM_ADDTOOL, 0, (LPARAM)ti);
    SendMessage(*hwndTT, TTM_TRACKACTIVATE, (WPARAM)TRUE, (LPARAM)ti);
    SendMessage(hwndCtrl, TBM_SETTOOLTIPS, (WPARAM)*hwndTT, 0);
}

static void UpdateVolumeToolTip(HWND hCtrl, HWND hwndTT, TOOLINFO* ti)
{
    static char str[32];
    int val = SendMessage(hCtrl, TBM_GETPOS,   0, 0);
    if (val == 100) {
        sprintf(str, "-inf.");
    }
    else {
        sprintf(str, "%.1f dB", -30. * val / 100);
    }
    ti->lpszText  = str;
    SendMessage(hwndTT, TTM_UPDATETIPTEXT, 0, (LPARAM)ti);  
}

static void UpdatePanToolTip(HWND hCtrl, HWND hwndTT, TOOLINFO* ti)
{
    static char str[32];
    int val = SendMessage(hCtrl, TBM_GETPOS,   0, 0);
    if (val == 50) {
        sprintf(str, "    C    ");
    }
    else if (val < 50) {
        sprintf(str, "L: %d", 2 * (50 - val));
    }
    else {
        sprintf(str, "R: %d", 2 * (val - 50));
    }
    ti->lpszText  = str;
    SendMessage(hwndTT, TTM_UPDATETIPTEXT, 0, (LPARAM)ti);  
}

static BOOL CALLBACK soundDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hwndVolTT[MIXER_CHANNEL_TYPE_COUNT];
    static TOOLINFO tiVol[MIXER_CHANNEL_TYPE_COUNT];
    static HWND hwndPanTT[MIXER_CHANNEL_TYPE_COUNT];
    static TOOLINFO tiPan[MIXER_CHANNEL_TYPE_COUNT];
    static int oldEnable[MIXER_CHANNEL_TYPE_COUNT];
    static int oldMasterEnable;
    static HWND hwndMasterTT[2];
    static TOOLINFO tiMaster[2];
    static Properties* pProperties;
    static int stereo;
    int updateAudio = FALSE;
    int index;
    int i;

    switch (iMsg) {
    case WM_INITDIALOG:
        if (!centered) {
            updateDialogPos(GetParent(hDlg), DLG_ID_PROPERTIES, 0, 1);
            centered = 1;
        }
        hDlgSound = hDlg;

        pProperties = (Properties*)((PROPSHEETPAGE*)lParam)->lParam;

        SendMessage(GetDlgItem(hDlg, IDC_SNDMIXERMASTERTEXT), WM_SETTEXT, 0, (LPARAM)langPropSndMasterText());

        SendMessage(GetDlgItem(hDlg, IDC_SNDCHIPEMUGROUPBOX), WM_SETTEXT, 0, (LPARAM)langPropSndChipEmuGB());
        SendMessage(GetDlgItem(hDlg, IDC_SNDMIXERGROUPBOX), WM_SETTEXT, 0, (LPARAM)langPropSndMixerGB());
        SendMessage(GetDlgItem(hDlg, IDC_OVERSAMPLETEXT1), WM_SETTEXT, 0, (LPARAM)langPropSndOversampleText());
        SendMessage(GetDlgItem(hDlg, IDC_OVERSAMPLETEXT2), WM_SETTEXT, 0, (LPARAM)langPropSndOversampleText());
        SendMessage(GetDlgItem(hDlg, IDC_OVERSAMPLETEXT3), WM_SETTEXT, 0, (LPARAM)langPropSndOversampleText());
        SetWindowText(GetDlgItem(hDlg, IDC_ENABLEMSXMUSIC), langPropSndMsxMusicText());
        SetWindowText(GetDlgItem(hDlg, IDC_ENABLEMSXAUDIO), langPropSndMsxAudioText());
        SetWindowText(GetDlgItem(hDlg, IDC_ENABLEMOONSOUND), langPropSndMoonsound());

        {
            int index = 0;
            int oversampling = 1;
            for (; index < 4; index++, oversampling <<= 1) {
                const char* modes[] = { "1 x", "2 x", "4 x", "8 x"} ;
                SendDlgItemMessage(hDlg, IDC_OVERSAMPLEMSXMUSIC, CB_ADDSTRING, 0, (LPARAM)modes[index]);
                if (oversampling <= pProperties->sound.chip.ym2413Oversampling) {
                    SendDlgItemMessage(hDlg, IDC_OVERSAMPLEMSXMUSIC, CB_SETCURSEL, index, 0);
                }
                
                SendDlgItemMessage(hDlg, IDC_OVERSAMPLEMSXAUDIO, CB_ADDSTRING, 0, (LPARAM)modes[index]);
                if (oversampling <= pProperties->sound.chip.y8950Oversampling) {
                    SendDlgItemMessage(hDlg, IDC_OVERSAMPLEMSXAUDIO, CB_SETCURSEL, index, 0);
                }
                
                SendDlgItemMessage(hDlg, IDC_OVERSAMPLEMOONSOUND, CB_ADDSTRING, 0, (LPARAM)modes[index]);
                if (oversampling <= pProperties->sound.chip.moonsoundOversampling) {
                    SendDlgItemMessage(hDlg, IDC_OVERSAMPLEMOONSOUND, CB_SETCURSEL, index, 0);
                }
            }
        }

        for (i = 0; i < MIXER_CHANNEL_TYPE_COUNT; i++) {
            CreateToolTip(GetDlgItem(hDlg, IDC_VOLUME1 + i), &hwndVolTT[i], &tiVol[i]);
            CreateToolTip(GetDlgItem(hDlg, IDC_PAN1 + i), &hwndPanTT[i], &tiPan[i]);

            SendMessage(GetDlgItem(hDlg, IDC_VOLUME1 + i),    TBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 100));
            SendMessage(GetDlgItem(hDlg, IDC_VOLUME1 + i),    TBM_SETPOS,   1, (LPARAM)(100 - pProperties->sound.mixerChannel[i].volume));
            SendMessage(GetDlgItem(hDlg, IDC_PAN1 + i),       TBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 100));
            SendMessage(GetDlgItem(hDlg, IDC_PAN1 + i),       TBM_SETPOS,   1, (LPARAM)pProperties->sound.mixerChannel[i].pan);
            SendMessage(GetDlgItem(hDlg, IDC_VOLENABLE1 + i), BM_SETCHECK, pProperties->sound.mixerChannel[i].enable ? BST_CHECKED : BST_UNCHECKED, 0);
            oldEnable[i] = pProperties->sound.mixerChannel[i].enable;
        }

        oldMasterEnable = pProperties->sound.masterEnable;

        SendMessage(GetDlgItem(hDlg, IDC_VOLENABLEMASTER), BM_SETCHECK, pProperties->sound.masterEnable ? BST_CHECKED : BST_UNCHECKED, 0);
        
        CreateToolTip(GetDlgItem(hDlg, IDC_MASTERL), &hwndMasterTT[0], &tiMaster[0]);
        CreateToolTip(GetDlgItem(hDlg, IDC_MASTERR), &hwndMasterTT[1], &tiMaster[1]);

        SendMessage(GetDlgItem(hDlg, IDC_MASTERL), TBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 100));
        SendMessage(GetDlgItem(hDlg, IDC_MASTERL), TBM_SETPOS,   1, (LPARAM)(100 - pProperties->sound.masterVolume));
        SendMessage(GetDlgItem(hDlg, IDC_MASTERR), TBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 100));
        SendMessage(GetDlgItem(hDlg, IDC_MASTERR), TBM_SETPOS,   1, (LPARAM)(100 - pProperties->sound.masterVolume));

        setButtonCheck(hDlg, IDC_ENABLEMSXMUSIC,  pProperties->sound.chip.enableYM2413, 1);
        setButtonCheck(hDlg, IDC_ENABLEMSXAUDIO,  pProperties->sound.chip.enableY8950, 1);
        setButtonCheck(hDlg, IDC_ENABLEMOONSOUND, pProperties->sound.chip.enableMoonsound, 1);

        stereo = pProperties->sound.stereo;
        SetWindowText(GetDlgItem(hDlg, IDC_STEREO), stereo ? langPropSndStereoText() : langPropSndMonoText());

        return FALSE;

    case WM_COMMAND:
        if (LOWORD(wParam) >= IDC_VOLENABLE1 && LOWORD(wParam) < IDC_VOLENABLE1 + MIXER_CHANNEL_TYPE_COUNT) {
            updateAudio = TRUE;
        }

        switch(LOWORD(wParam)) {
        case IDC_STEREO:
            stereo = !stereo;
            SetWindowText(GetDlgItem(hDlg, IDC_STEREO), stereo ? langPropSndStereoText() : langPropSndMonoText());
            emulatorRestartSound();
            updateAudio = TRUE;
            break;
        case IDC_MASTERL:
            SendMessage(GetDlgItem(hDlg, IDC_MASTERR), TBM_SETPOS,   1, (LPARAM)SendMessage(GetDlgItem(hDlg, IDC_MASTERL), TBM_GETPOS,   0, 0));
            updateAudio = TRUE;
            break;
        case IDC_MASTERR:
            SendMessage(GetDlgItem(hDlg, IDC_MASTERL), TBM_SETPOS,   1, (LPARAM)SendMessage(GetDlgItem(hDlg, IDC_MASTERR), TBM_GETPOS,   0, 0));
            updateAudio = TRUE;
            break;
        case IDC_VOLENABLEMASTER:
            updateAudio = TRUE;
            break;
        case IDC_OVERSAMPLEMSXMUSIC:
            index = SendDlgItemMessage(hDlg, IDC_OVERSAMPLEMSXMUSIC, CB_GETCURSEL, 0, 0);
            boardSetYm2413Oversampling(1 << index);
            break;
        case IDC_OVERSAMPLEMSXAUDIO:
            index = SendDlgItemMessage(hDlg, IDC_OVERSAMPLEMSXAUDIO, CB_GETCURSEL, 0, 0);
            boardSetY8950Oversampling(1 << index);
            break;
        case IDC_OVERSAMPLEMOONSOUND:
            index = SendDlgItemMessage(hDlg, IDC_OVERSAMPLEMOONSOUND, CB_GETCURSEL, 0, 0);
            boardSetMoonsoundOversampling(1 << index);
            break;
        }
        break;

    case WM_NOTIFY:
        if (((NMHDR FAR*)lParam)->code == PSN_APPLY || ((NMHDR FAR*)lParam)->code == PSN_QUERYCANCEL) {
            saveDialogPos(GetParent(hDlg), DLG_ID_PROPERTIES);
        }

        switch (((NMHDR FAR *)lParam)->code) {
        case PSN_APPLY:
            pProperties->sound.chip.enableYM2413 = getButtonCheck(hDlg, IDC_ENABLEMSXMUSIC);
            pProperties->sound.chip.enableY8950 = getButtonCheck(hDlg, IDC_ENABLEMSXAUDIO);
            pProperties->sound.chip.enableMoonsound = getButtonCheck(hDlg, IDC_ENABLEMOONSOUND);
            index = SendDlgItemMessage(hDlg, IDC_OVERSAMPLEMSXMUSIC, CB_GETCURSEL, 0, 0);
            pProperties->sound.chip.ym2413Oversampling = 1 << index;
            index = SendDlgItemMessage(hDlg, IDC_OVERSAMPLEMSXAUDIO, CB_GETCURSEL, 0, 0);
            pProperties->sound.chip.y8950Oversampling = 1 << index;
            index = SendDlgItemMessage(hDlg, IDC_OVERSAMPLEMOONSOUND, CB_GETCURSEL, 0, 0);
            pProperties->sound.chip.moonsoundOversampling = 1 << index;

            for (i = 0; i < MIXER_CHANNEL_TYPE_COUNT; i++) {
                pProperties->sound.mixerChannel[i].volume = 100 - SendMessage(GetDlgItem(hDlg, IDC_VOLUME1 + i),    TBM_GETPOS,   0, 0);
                pProperties->sound.mixerChannel[i].pan    = SendMessage(GetDlgItem(hDlg, IDC_PAN1 + i),       TBM_GETPOS,   0, 0);
                pProperties->sound.mixerChannel[i].enable = SendMessage(GetDlgItem(hDlg, IDC_VOLENABLE1 + i), BM_GETCHECK, 0, 0) == BST_CHECKED;
            }

            pProperties->sound.masterVolume = 100 - SendMessage(GetDlgItem(hDlg, IDC_MASTERL), TBM_GETPOS,   0, 0);
            pProperties->sound.masterEnable = SendMessage(GetDlgItem(hDlg, IDC_VOLENABLEMASTER), BM_GETCHECK, 0, 0) == BST_CHECKED;
            pProperties->sound.stereo = stereo;

            for (i = 0; i < MIXER_CHANNEL_TYPE_COUNT; i++) {
                DestroyWindow(hwndVolTT[i]);
                DestroyWindow(hwndPanTT[i]);
            }
            DestroyWindow(hwndMasterTT[0]);
            DestroyWindow(hwndMasterTT[1]);

            propModified = 1;
            return TRUE;

        case PSN_QUERYCANCEL:
            emulatorRestartSound();

            boardSetYm2413Oversampling(pProperties->sound.chip.ym2413Oversampling);
            boardSetY8950Oversampling(pProperties->sound.chip.y8950Oversampling);
            boardSetMoonsoundOversampling(pProperties->sound.chip.moonsoundOversampling);

            pProperties->sound.masterEnable = oldMasterEnable;
            for (i = 0; i < MIXER_CHANNEL_TYPE_COUNT; i++) {
                pProperties->sound.mixerChannel[i].enable = oldEnable[i];
                mixerSetChannelTypeVolume(theMixer, i, pProperties->sound.mixerChannel[i].volume);
                mixerSetChannelTypePan(theMixer, i, pProperties->sound.mixerChannel[i].pan);
                mixerEnableChannelType(theMixer, i, pProperties->sound.mixerChannel[i].enable);
            }
            mixerSetMasterVolume(theMixer, pProperties->sound.masterVolume);
            mixerEnableMaster(theMixer, pProperties->sound.masterEnable);

            for (i = 0; i < MIXER_CHANNEL_TYPE_COUNT; i++) {
                DestroyWindow(hwndVolTT[i]);
                DestroyWindow(hwndPanTT[i]);
            }
            DestroyWindow(hwndMasterTT[0]);
            DestroyWindow(hwndMasterTT[1]);

            return FALSE;

        default:
            if (wParam == IDC_MASTERL) {
                SendMessage(GetDlgItem(hDlg, IDC_MASTERR), TBM_SETPOS,   1, (LPARAM)SendMessage(GetDlgItem(hDlg, IDC_MASTERL), TBM_GETPOS,   0, 0));
                UpdateVolumeToolTip(GetDlgItem(hDlg, IDC_MASTERL), hwndMasterTT[0], &tiMaster[0]);
                updateAudio = TRUE;
            }
            if (wParam == IDC_MASTERR) {
                SendMessage(GetDlgItem(hDlg, IDC_MASTERL), TBM_SETPOS,   1, (LPARAM)SendMessage(GetDlgItem(hDlg, IDC_MASTERR), TBM_GETPOS,   0, 0));
                UpdateVolumeToolTip(GetDlgItem(hDlg, IDC_MASTERR), hwndMasterTT[1], &tiMaster[1]);
                updateAudio = TRUE;
            }

            if (wParam >= IDC_VOLUME1 && wParam < IDC_VOLUME1 + MIXER_CHANNEL_TYPE_COUNT) {  
                UpdateVolumeToolTip(GetDlgItem(hDlg, wParam), hwndVolTT[wParam - IDC_VOLUME1], &tiVol[wParam - IDC_VOLUME1]);
                updateAudio = TRUE;
            }

            if (wParam >= IDC_PAN1 && wParam < IDC_PAN1 + MIXER_CHANNEL_TYPE_COUNT) {    
                UpdatePanToolTip(GetDlgItem(hDlg, wParam), hwndPanTT[wParam - IDC_PAN1], &tiPan[wParam - IDC_PAN1]);
                updateAudio = TRUE;
            }

            break;
        }

        break;
    }

    if (updateAudio) {
        for (i = 0; i < MIXER_CHANNEL_TYPE_COUNT; i++) {
            mixerSetChannelTypeVolume(theMixer, i, 100 - SendMessage(GetDlgItem(hDlg, IDC_VOLUME1 + i), TBM_GETPOS,   0, 0));
            mixerSetChannelTypePan(theMixer, i, SendMessage(GetDlgItem(hDlg, IDC_PAN1 + i), TBM_GETPOS,   0, 0));
            pProperties->sound.mixerChannel[i].enable = SendMessage(GetDlgItem(hDlg, IDC_VOLENABLE1 + i), BM_GETCHECK, 0, 0) == BST_CHECKED;
            mixerEnableChannelType(theMixer, i, pProperties->sound.mixerChannel[i].enable);
        }
        mixerSetMasterVolume(theMixer, 100 - SendMessage(GetDlgItem(hDlg, IDC_MASTERL), TBM_GETPOS,   0, 0));
        pProperties->sound.masterEnable = SendMessage(GetDlgItem(hDlg, IDC_VOLENABLEMASTER), BM_GETCHECK, 0, 0) == BST_CHECKED;
        mixerEnableMaster(theMixer, pProperties->sound.masterEnable);
    }

    return FALSE;
}


//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

static BOOL CALLBACK joykeyDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    static JoystickProperties* joyCtrl;
    static JoystickProperties tmpJoyCtrl;
    static int id = 0;

    switch (iMsg) {
    case WM_COMMAND:
        switch(LOWORD(wParam)) {
        case IDOK:
            KillTimer(hDlg, 0);
            *joyCtrl = tmpJoyCtrl;
            EndDialog(hDlg, TRUE);
            return TRUE;
        case IDCANCEL:
            KillTimer(hDlg, 0);
            EndDialog(hDlg, FALSE);
            return TRUE;
        case IDC_KEYUP:
            break;
        }
        switch (HIWORD(wParam)) {
        case EN_KILLFOCUS:
            id = 0;
            break;
        case EN_SETFOCUS:
            id = LOWORD(wParam);
            break;
        }
        break;

    case WM_TIMER:
        if (id != 0) {
            int i;
            for (i = 0; i < 256; i++) {
                if (virtualKeys[i][0]) {
                    SHORT state = GetAsyncKeyState(i);
                    if (state & 1) {
                        SendMessage(GetDlgItem(hDlg, id), WM_SETTEXT, 0, (LPARAM)virtualKeys[i]);
                        switch (id) {
                        case IDC_KEYUP:      tmpJoyCtrl.keyUp    = i; break;
                        case IDC_KEYDOWN:    tmpJoyCtrl.keyDown  = i; break;
                        case IDC_KEYLEFT:    tmpJoyCtrl.keyLeft  = i; break;
                        case IDC_KEYRIGHT:   tmpJoyCtrl.keyRight = i; break;
                        case IDC_KEYBUTTON1: tmpJoyCtrl.button1  = i; break;
                        case IDC_KEYBUTTON2: tmpJoyCtrl.button2  = i; break;
                        }
                    }
                }
            }
        }
        break;

    case WM_INITDIALOG:
        updateDialogPos(hDlg, DLG_ID_JOYKEYS, 0, 1);
        joyCtrl = (JoystickProperties*)lParam;

        SetWindowText(GetDlgItem(hDlg, IDOK), langDlgOK());
        SetWindowText(GetDlgItem(hDlg, IDCANCEL), langDlgCancel());

        SendMessage(GetDlgItem(hDlg, IDC_JOYUPTEXT), WM_SETTEXT, 0, (LPARAM)langDlgJoyUpText());
        SendMessage(GetDlgItem(hDlg, IDC_JOYDOWNTEXT), WM_SETTEXT, 0, (LPARAM)langDlgJoyDownText());
        SendMessage(GetDlgItem(hDlg, IDC_JOYLEFTTEXT), WM_SETTEXT, 0, (LPARAM)langDlgJoyLeftText());
        SendMessage(GetDlgItem(hDlg, IDC_JOYRIGHTTEXT), WM_SETTEXT, 0, (LPARAM)langDlgJoyRightText());
        SendMessage(GetDlgItem(hDlg, IDC_JOYBUTTON1TEXT), WM_SETTEXT, 0, (LPARAM)langDlgJoyButton1Text());
        SendMessage(GetDlgItem(hDlg, IDC_JOYBUTTON2TEXT), WM_SETTEXT, 0, (LPARAM)langDlgJoyButton2Text());
        SendMessage(GetDlgItem(hDlg, IDC_JOYGROUPBOX), WM_SETTEXT, 0, (LPARAM)langDlgJoyGB());

        SetWindowText(hDlg, joyCtrl->id == 1 ? langDlgJoyTitle1() : langDlgJoyTitle2());

        tmpJoyCtrl = *joyCtrl;
        SendMessage(GetDlgItem(hDlg, IDC_KEYUP),      WM_SETTEXT, 0, (LPARAM)virtualKeys[tmpJoyCtrl.keyUp]);
        SendMessage(GetDlgItem(hDlg, IDC_KEYDOWN),    WM_SETTEXT, 0, (LPARAM)virtualKeys[tmpJoyCtrl.keyDown]);
        SendMessage(GetDlgItem(hDlg, IDC_KEYLEFT),    WM_SETTEXT, 0, (LPARAM)virtualKeys[tmpJoyCtrl.keyLeft]);
        SendMessage(GetDlgItem(hDlg, IDC_KEYRIGHT),   WM_SETTEXT, 0, (LPARAM)virtualKeys[tmpJoyCtrl.keyRight]);
        SendMessage(GetDlgItem(hDlg, IDC_KEYBUTTON1), WM_SETTEXT, 0, (LPARAM)virtualKeys[tmpJoyCtrl.button1]);
        SendMessage(GetDlgItem(hDlg, IDC_KEYBUTTON2), WM_SETTEXT, 0, (LPARAM)virtualKeys[tmpJoyCtrl.button2]);

        SetTimer(hDlg, 0, 1, NULL);
        return FALSE;

    case WM_DESTROY:
        saveDialogPos(hDlg, DLG_ID_JOYKEYS);
        return 0;
    }

    return FALSE;
}

static updateJoystickList(HWND hDlg, int id, int type, int hwType) {
    int i;

    while (CB_ERR != SendDlgItemMessage(hDlg, id, CB_DELETESTRING, 0, 0));

    // Add static members
    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)langEnumControlsJoyNone());
    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)langEnumControlsJoyMouse());
    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)langEnumControlsJoyNumpad());
    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)langEnumControlsJoyKeyset());

    for (i = 0; i < archJoystickGetCount(); i++) {
        SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)archJoystickGetName(i));
    }

    if (type == P_JOY_HW) {
        type += hwType;
    }
    
    SendDlgItemMessage(hDlg, id, CB_SETCURSEL, type, 0);
}

static int getJoystickList(HWND hDlg, int id, int* hwType, char* hwName, int* hwIndex) 
{
    char selection[128];
    int index = SendMessage(GetDlgItem(hDlg, id), CB_GETCURSEL, 0, 0);
    int rv = SendMessage(GetDlgItem(hDlg, id), CB_GETLBTEXT, index, (LPARAM)selection);

    if (rv == CB_ERR || index < 0) {
        return P_JOY_NONE;
    }

    *hwType = 0;
    switch (index) {
    case 0: return P_JOY_NONE;
    case 1: return P_JOY_MOUSE;
    case 2: return P_JOY_NUMPAD;
    case 3: return P_JOY_KEYSET;
    default:
        break;
    }
    
    *hwType = index - 4;

    if (hwName != NULL && hwIndex != NULL) {
        int i;

        strcpy(hwName, selection);
        *hwIndex = 0;

        for (i = 0; i < *hwType; i++) {
            if (0 == strcpy(selection, archJoystickGetName(i))) {
                *hwIndex++;
            }
        }
    }

    return P_JOY_HW;
}

static updateJoystickButtonList(HWND hDlg, int id, int joyIndex, int button) 
{
    int buttons;
    int i;

    while (CB_ERR != SendDlgItemMessage(hDlg, id, CB_DELETESTRING, 0, 0));

    buttons = joystickNumButtons(joyIndex);

    if (buttons < 2) {
        buttons = 2;
    }

    for (i = 0; i < buttons; i++) {
        _TCHAR buffer[32];
        _stprintf(buffer, "%s %d", langPropJoyButtonText(), i + 1);

        SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)buffer);
    }

    SendDlgItemMessage(hDlg, id, CB_SETCURSEL, button, 0);
}

static int getJoystickButtonList(HWND hDlg, int id) 
{
    return SendMessage(GetDlgItem(hDlg, id), CB_GETCURSEL, 0, 0);
}

static updateJoystickAutofireList(HWND hDlg, int id, int autofire) 
{
    while (CB_ERR != SendDlgItemMessage(hDlg, id, CB_DELETESTRING, 0, 0));

    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)langEnumControlsAfOff());
    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)"1");
    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)"2");
    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)"3");
    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)"4");
    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)"5");
    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)"6");
    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)"7");
    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)"8");
    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)"9");
    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)"10");

    SendDlgItemMessage(hDlg, id, CB_SETCURSEL, autofire, 0);
}

static int getJoystickAutofireList(HWND hDlg, int id) 
{
    return SendMessage(GetDlgItem(hDlg, id), CB_GETCURSEL, 0, 0);
}

void propUpdateJoyinfo(Properties* pProperties)
{
    int joyCount = archJoystickGetCount();

    if (pProperties->joy1.type == P_JOY_HW) {
        int subindex = 0;
        int i;

        for (i = 0; i < joyCount; i++) {
            if (0 == strcmp(pProperties->joy1.hwName, archJoystickGetName(i))) {
                if (subindex == pProperties->joy1.hwIndex) {
                    pProperties->joy1.hwType = i;
                    return;
                }
                subindex++;
            }
        }
        // If joystick was not found, set it to none
        pProperties->joy1.type = P_JOY_NONE;
    }

    if (pProperties->joy2.type == P_JOY_HW) {
        int subindex = 0;
        int i;

        for (i = 0; i < joyCount; i++) {
            if (0 == strcmp(pProperties->joy2.hwName, archJoystickGetName(i))) {
                if (subindex == pProperties->joy2.hwIndex) {
                    pProperties->joy2.hwType = i;
                    return;
                }
                subindex++;
            }
        }
        // If joystick was not found, set it to none
        pProperties->joy2.type = P_JOY_NONE;
    }
}

static BOOL CALLBACK controlsDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    static Properties* pProperties;
    static int oldHwIndex1;
    static int oldHwIndex2;

    switch (iMsg) {
    case WM_INITDIALOG:  
        if (!centered) {
            updateDialogPos(GetParent(hDlg), DLG_ID_PROPERTIES, 0, 1);
            centered = 1;
        }

        SendMessage(GetDlgItem(hDlg, IDC_JOYPORT1GROUPBOX), WM_SETTEXT, 0, (LPARAM)langPropJoyPort1GB());
        SendMessage(GetDlgItem(hDlg, IDC_JOYPORT2GROUPBOX), WM_SETTEXT, 0, (LPARAM)langPropJoyPort2GB());
        SendMessage(GetDlgItem(hDlg, IDC_JOYAUTOFIRETEXT1), WM_SETTEXT, 0, (LPARAM)langPropJoyAutofireText());
//        SendMessage(GetDlgItem(hDlg, IDC_JOYAUTOFIRETEXT2), WM_SETTEXT, 0, (LPARAM)langPropJoyAutofireText());
        
        SendMessage(GetDlgItem(hDlg, IDC_JOYCONTROLTEXT1), WM_SETTEXT, 0, (LPARAM)langPropJoyControlText());
        SendMessage(GetDlgItem(hDlg, IDC_JOYCONTROLTEXT2), WM_SETTEXT, 0, (LPARAM)langPropJoyControlText());

        SetWindowText(GetDlgItem(hDlg, IDC_JOYKEYSET1), langPropJoyConfigKeyset());
        SetWindowText(GetDlgItem(hDlg, IDC_JOYKEYSET2), langPropJoyConfigKeyset());

        SetWindowText(GetDlgItem(hDlg, IDC_JOYBUTTONATEXT1), langPropJoyButtonAText());
        SetWindowText(GetDlgItem(hDlg, IDC_JOYBUTTONBTEXT1), langPropJoyButtonBText());
        SetWindowText(GetDlgItem(hDlg, IDC_JOYBUTTONATEXT2), langPropJoyButtonAText());
        SetWindowText(GetDlgItem(hDlg, IDC_JOYBUTTONBTEXT2), langPropJoyButtonBText());

        SetWindowText(GetDlgItem(GetParent(hDlg), IDOK), langDlgOK());
        SetWindowText(GetDlgItem(GetParent(hDlg), IDCANCEL), langDlgCancel());

        pProperties = (Properties*)((PROPSHEETPAGE*)lParam)->lParam;

        updateJoystickList(hDlg, IDC_JOY1, pProperties->joy1.type, pProperties->joy1.hwType);
        updateJoystickList(hDlg, IDC_JOY2, pProperties->joy2.type, pProperties->joy2.hwType);

        updateJoystickAutofireList(hDlg, IDC_AUTOFIRE1, pProperties->joy1.autofire);
//        updateJoystickAutofireList(hDlg, IDC_AUTOFIRE2, pProperties->joy2.autofire);

        EnableWindow(GetDlgItem(hDlg, IDC_JOYKEYSET1), pProperties->joy1.type == P_JOY_KEYSET);
        EnableWindow(GetDlgItem(hDlg, IDC_JOYKEYSET2), pProperties->joy2.type == P_JOY_KEYSET);
        
        EnableWindow(GetDlgItem(hDlg, IDC_JOYBUTTONA1), pProperties->joy1.type == P_JOY_HW);
        EnableWindow(GetDlgItem(hDlg, IDC_JOYBUTTONB1), pProperties->joy1.type == P_JOY_HW);
        
        EnableWindow(GetDlgItem(hDlg, IDC_JOYBUTTONA2), pProperties->joy2.type == P_JOY_HW);
        EnableWindow(GetDlgItem(hDlg, IDC_JOYBUTTONB2), pProperties->joy2.type == P_JOY_HW);

        oldHwIndex1 = -1;
        oldHwIndex2 = -1;

        if (pProperties->joy1.type == P_JOY_HW) {
            oldHwIndex1 = pProperties->joy1.hwType;
            updateJoystickButtonList(hDlg, IDC_JOYBUTTONA1, pProperties->joy1.hwType, pProperties->joy1.hwButtonA);
            updateJoystickButtonList(hDlg, IDC_JOYBUTTONB1, pProperties->joy1.hwType, pProperties->joy1.hwButtonB);
        }

        if (pProperties->joy2.hwType == P_JOY_HW) {
            oldHwIndex2 = pProperties->joy2.hwType;
            updateJoystickButtonList(hDlg, IDC_JOYBUTTONA1, pProperties->joy2.hwType, pProperties->joy2.hwButtonA);
            updateJoystickButtonList(hDlg, IDC_JOYBUTTONB1, pProperties->joy2.hwType, pProperties->joy2.hwButtonB);
        }

        return FALSE;
        
    case WM_COMMAND:
        switch(LOWORD(wParam)) {
        case IDC_JOYKEYSET1:
            DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_JOYKEYS), hDlg, joykeyDlgProc, (LPARAM)&pProperties->joy1);
            return TRUE;

        case IDC_JOYKEYSET2:
            DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_JOYKEYS), hDlg, joykeyDlgProc, (LPARAM)&pProperties->joy2);
            return TRUE;

        case IDC_JOY1:
            {
                int index;
                int type = getJoystickList(hDlg, IDC_JOY1, &index, NULL, NULL);
                
                EnableWindow(GetDlgItem(hDlg, IDC_JOYKEYSET1), type == P_JOY_KEYSET);
                EnableWindow(GetDlgItem(hDlg, IDC_JOYBUTTONA1), type == P_JOY_HW);
                EnableWindow(GetDlgItem(hDlg, IDC_JOYBUTTONB1), type == P_JOY_HW);

                if (type == P_JOY_HW && oldHwIndex1 != index) {
                    updateJoystickButtonList(hDlg, IDC_JOYBUTTONA1, index, 0);
                    updateJoystickButtonList(hDlg, IDC_JOYBUTTONB1, index, 1);
                }
                else {
                    SetWindowText(GetDlgItem(hDlg, IDC_JOYBUTTONA1), "");
                    SetWindowText(GetDlgItem(hDlg, IDC_JOYBUTTONB1), "");
                }
                oldHwIndex1 = type == P_JOY_HW ? index : -1;
            }
            return TRUE;

        case IDC_JOY2:
            {
                int index;
                int type = getJoystickList(hDlg, IDC_JOY2, &index, NULL, NULL);
                
                EnableWindow(GetDlgItem(hDlg, IDC_JOYKEYSET2), type == P_JOY_KEYSET);
                EnableWindow(GetDlgItem(hDlg, IDC_JOYBUTTONA2), type == P_JOY_HW);
                EnableWindow(GetDlgItem(hDlg, IDC_JOYBUTTONB2), type == P_JOY_HW);

                if (type == P_JOY_HW && oldHwIndex2 != index) {
                    updateJoystickButtonList(hDlg, IDC_JOYBUTTONA2, index, 0);
                    updateJoystickButtonList(hDlg, IDC_JOYBUTTONB2, index, 1);
                }
                else {
                    SetWindowText(GetDlgItem(hDlg, IDC_JOYBUTTONA2), "");
                    SetWindowText(GetDlgItem(hDlg, IDC_JOYBUTTONB2), "");
                }
                oldHwIndex2 = type == P_JOY_HW ? index : -1;
            }
            return TRUE;
        }
        return FALSE;

    case WM_NOTIFY:
        if (((NMHDR FAR*)lParam)->code == PSN_APPLY || ((NMHDR FAR*)lParam)->code == PSN_QUERYCANCEL) {
            saveDialogPos(GetParent(hDlg), DLG_ID_PROPERTIES);
        }

        if ((((NMHDR FAR *)lParam)->code) != PSN_APPLY) {
            return FALSE;
        }
        pProperties->joy1.autofire = getJoystickAutofireList(hDlg, IDC_AUTOFIRE1);
//        pProperties->joy2.autofire = getJoystickAutofireList(hDlg, IDC_AUTOFIRE2);

        pProperties->joy1.type = getJoystickList(hDlg, IDC_JOY1, 
                                                 &pProperties->joy1.hwType, 
                                                 pProperties->joy1.hwName, 
                                                 &pProperties->joy1.hwIndex);
        pProperties->joy2.type = getJoystickList(hDlg, IDC_JOY2, 
                                                 &pProperties->joy2.hwType, 
                                                 pProperties->joy2.hwName, 
                                                 &pProperties->joy2.hwIndex);

        pProperties->joy1.hwButtonA = getJoystickButtonList(hDlg, IDC_JOYBUTTONA1);
        pProperties->joy1.hwButtonB = getJoystickButtonList(hDlg, IDC_JOYBUTTONB1);

        pProperties->joy2.hwButtonA = getJoystickButtonList(hDlg, IDC_JOYBUTTONA2);
        pProperties->joy2.hwButtonB = getJoystickButtonList(hDlg, IDC_JOYBUTTONB2);

        propModified = 1;
        
        return TRUE;
    }

    return FALSE;
}

static BOOL updatePortsLptList(HWND hDlg, int id)
{
    LPPRINTER_INFO_2 lpPrinterInfo = NULL;
    TCHAR sBuf[MAX_PATH];
    DWORD dwNeeded;
    DWORD dwReturned;
    DWORD dwItem;

    while (CB_ERR != SendDlgItemMessage(hDlg, id, CB_DELETESTRING, 0, 0));

    // Get buffer size
    EnumPrinters(PRINTER_ENUM_LOCAL|PRINTER_ENUM_CONNECTIONS, NULL, 2, NULL, 0, &dwNeeded, &dwReturned);

    // Allocate memory
    lpPrinterInfo = (LPPRINTER_INFO_2)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwNeeded);
    if (lpPrinterInfo == NULL)
        return FALSE;

    if (!EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 2, (LPBYTE)lpPrinterInfo, dwNeeded, &dwNeeded, &dwReturned))
        return FALSE;

    // Add static members
//    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)langEnumPortsLptNone());
    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)"None");

    // Add printers 
    for (dwItem = 0; dwItem < dwReturned; dwItem++) {
        if SUCCEEDED(StringCchPrintf(sBuf, MAX_PATH-1, _T("%s - %s"), lpPrinterInfo[dwItem].pPortName, lpPrinterInfo[dwItem].pPrinterName))
            SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)sBuf);
    }

    SendDlgItemMessage(hDlg, id, CB_SETCURSEL, 0, 0);

    // Free memory
    HeapFree(GetProcessHeap(), 0, lpPrinterInfo);

    return TRUE;
}

static BOOL IsNumeric(LPCTSTR pszString, BOOL bIgnoreColon)
{
    BOOL bNumeric = TRUE;
    size_t cch;
    unsigned int i;

    if (!SUCCEEDED(StringCchLength(pszString, MAX_PATH-1, &cch)))
        return FALSE;
    if (cch == 0)
        return FALSE;

    for (i=0; i<cch && bNumeric; i++) {
        bNumeric = (_istdigit(pszString[i]) != 0);
        if (bIgnoreColon && (pszString[i] == _T(':')))
            bNumeric = TRUE;
    }
    return bNumeric;
}

static BOOL updatePortsComList(HWND hDlg, int id)
{
    PORT_INFO_2 *lpPortInfo = NULL;
    TCHAR sBuf[MAX_PATH];
    DWORD dwNeeded;
    DWORD dwReturned;
    DWORD dwItem;

    while (CB_ERR != SendDlgItemMessage(hDlg, id, CB_DELETESTRING, 0, 0));

    // Get buffer size
    EnumPorts(NULL, 2, NULL, 0, &dwNeeded, &dwReturned);

    // Allocate memory
    lpPortInfo = (PORT_INFO_2*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwNeeded);
    if (lpPortInfo == NULL)
        return FALSE;

    if (!EnumPorts(NULL, 2, (LPBYTE)lpPortInfo, dwNeeded, &dwNeeded, &dwReturned))
        return FALSE;

    // Add static members
//    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)langEnumPortsComNone());
    SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)"None");

    // Add COM ports 
    for (dwItem = 0; dwItem < dwReturned; dwItem++) {
        size_t cch;
        if SUCCEEDED(StringCchLength(lpPortInfo[dwItem].pPortName, MAX_PATH-1, &cch))
            if (cch > 3)
                if ((_tcsnicmp(lpPortInfo[dwItem].pPortName, _T("COM"), 3) == 0) && IsNumeric(&lpPortInfo[dwItem].pPortName[3], TRUE))
                    if SUCCEEDED(StringCchPrintf(sBuf, MAX_PATH-1, _T("%s - %s"), lpPortInfo[dwItem].pPortName, lpPortInfo[dwItem].pDescription))
                        SendDlgItemMessage(hDlg, id, CB_ADDSTRING, 0, (LPARAM)sBuf);
    }

    SendDlgItemMessage(hDlg, id, CB_SETCURSEL, 0, 0);

    // Free memory
    HeapFree(GetProcessHeap(), 0, lpPortInfo);

    return TRUE;
}

static BOOL CALLBACK portsDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static Properties* pProperties;

    switch (iMsg) {
    case WM_INITDIALOG:  
        if (!centered) {
            updateDialogPos(GetParent(hDlg), DLG_ID_PROPERTIES, 0, 1);
            centered = 1;
        }

        SendMessage(GetDlgItem(hDlg, IDC_PORTSLPTGROUPBOX), WM_SETTEXT, 0, (LPARAM)langPropPortsLptGB());
        SendMessage(GetDlgItem(hDlg, IDC_PORTSCOMGROUPBOX), WM_SETTEXT, 0, (LPARAM)langPropPortsComGB());
        SendMessage(GetDlgItem(hDlg, IDC_PORTSLPTTEXT), WM_SETTEXT, 0, (LPARAM)langPropPortsLptText());
        SendMessage(GetDlgItem(hDlg, IDC_PORTSCOM1TEXT), WM_SETTEXT, 0, (LPARAM)langPropPortsCom1Text());
        SetWindowText(GetDlgItem(GetParent(hDlg), IDOK), langDlgOK());
        SetWindowText(GetDlgItem(GetParent(hDlg), IDCANCEL), langDlgCancel());

        updatePortsLptList(hDlg, IDC_PORTSLPT);
        updatePortsComList(hDlg, IDC_PORTSCOM1);

        pProperties = (Properties*)((PROPSHEETPAGE*)lParam)->lParam;

        return FALSE;
        
    case WM_COMMAND:
        switch(LOWORD(wParam)) {
        case IDC_PORTSLPT:
            return TRUE;

        case IDC_PORTSCOM1:
            return TRUE;
        }
        return FALSE;

    case WM_NOTIFY:
        if (((NMHDR FAR*)lParam)->code == PSN_APPLY || ((NMHDR FAR*)lParam)->code == PSN_QUERYCANCEL) {
            saveDialogPos(GetParent(hDlg), DLG_ID_PROPERTIES);
        }

        if ((((NMHDR FAR *)lParam)->code) != PSN_APPLY) {
            return FALSE;
        }

        return TRUE;
    }

    return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


int showProperties(Properties* pProperties, HWND hwndOwner, PropPage startPage, Mixer* mixer, Video* video) {
	HINSTANCE       hInst = (HINSTANCE)GetModuleHandle(NULL);
    PROPSHEETPAGE   psp[8];
    PROPSHEETHEADER psh;
    Properties oldProp = *pProperties;

    centered = 0;
    hDlgSound = NULL;
    theMixer = mixer;
    theVideo = video;

    psp[0].dwSize = sizeof(PROPSHEETPAGE);
    psp[0].dwFlags = PSP_USEICONID | PSP_USETITLE;
    psp[0].hInstance = hInst;
    psp[0].pszTemplate = MAKEINTRESOURCE(IDD_EMULATION);
    psp[0].pszIcon = NULL;
    psp[0].pfnDlgProc = emulationDlgProc;
    psp[0].pszTitle = langPropEmulation();
    psp[0].lParam = (LPARAM)pProperties;
    psp[0].pfnCallback = NULL;

    psp[1].dwSize = sizeof(PROPSHEETPAGE);
    psp[1].dwFlags = PSP_USEICONID | PSP_USETITLE;
    psp[1].hInstance = hInst;
    psp[1].pszTemplate = MAKEINTRESOURCE(IDD_VIDEO);
    psp[1].pszIcon = NULL;
    psp[1].pfnDlgProc = videoDlgProc;
    psp[1].pszTitle = langPropVideo();
    psp[1].lParam = (LPARAM)pProperties;
    psp[1].pfnCallback = NULL;

    psp[2].dwSize = sizeof(PROPSHEETPAGE);
    psp[2].dwFlags = PSP_USEICONID | PSP_USETITLE;
    psp[2].hInstance = hInst;
    psp[2].pszTemplate = MAKEINTRESOURCE(IDD_SOUND);
    psp[2].pszIcon = NULL;
    psp[2].pfnDlgProc = soundDlgProc;
    psp[2].pszTitle = langPropSound();
    psp[2].lParam = (LPARAM)pProperties;
    psp[2].pfnCallback = NULL;

    psp[3].dwSize = sizeof(PROPSHEETPAGE);
    psp[3].dwFlags = PSP_USEICONID | PSP_USETITLE;
    psp[3].hInstance = hInst;
    psp[3].pszTemplate = MAKEINTRESOURCE(IDD_CONTROLS);
    psp[3].pszIcon = NULL;
    psp[3].pfnDlgProc = controlsDlgProc;
    psp[3].pszTitle = langPropControls();
    psp[3].lParam = (LPARAM)pProperties;
    psp[3].pfnCallback = NULL;

    psp[4].dwSize = sizeof(PROPSHEETPAGE);
    psp[4].dwFlags = PSP_USEICONID | PSP_USETITLE;
    psp[4].hInstance = hInst;
    psp[4].pszTemplate = MAKEINTRESOURCE(IDD_PERFORMANCE);
    psp[4].pszIcon = NULL;
    psp[4].pfnDlgProc = performanceDlgProc;
    psp[4].pszTitle = langPropPerformance();
    psp[4].lParam = (LPARAM)pProperties;
    psp[4].pfnCallback = NULL;

    psp[5].dwSize = sizeof(PROPSHEETPAGE);
    psp[5].dwFlags = PSP_USEICONID | PSP_USETITLE;
    psp[5].hInstance = hInst;
    psp[5].pszTemplate = MAKEINTRESOURCE(IDD_SETTINGS);
    psp[5].pszIcon = NULL;
    psp[5].pfnDlgProc = filesDlgProc;
    psp[5].pszTitle = langPropFile();
    psp[5].lParam = (LPARAM)pProperties;
    psp[5].pfnCallback = NULL;

    psp[6].dwSize = sizeof(PROPSHEETPAGE);
    psp[6].dwFlags = PSP_USEICONID | PSP_USETITLE;
    psp[6].hInstance = hInst;
    psp[6].pszTemplate = MAKEINTRESOURCE(IDD_APEARANCE);
    psp[6].pszIcon = NULL;
    psp[6].pfnDlgProc = settingsDlgProc;
    psp[6].pszTitle = langPropSettings();
    psp[6].lParam = (LPARAM)pProperties;
    psp[6].pfnCallback = NULL;

    psp[7].dwSize = sizeof(PROPSHEETPAGE);
    psp[7].dwFlags = PSP_USEICONID | PSP_USETITLE;
    psp[7].hInstance = hInst;
    psp[7].pszTemplate = MAKEINTRESOURCE(IDD_PORTS);
    psp[7].pszIcon = NULL;
    psp[7].pfnDlgProc = portsDlgProc;
    psp[7].pszTitle = langPropPorts();
    psp[7].lParam = (LPARAM)pProperties;
    psp[7].pfnCallback = NULL;
    
    psh.dwSize = sizeof(PROPSHEETHEADER);
    psh.dwFlags = PSH_USEICONID | PSH_PROPSHEETPAGE | PSH_NOAPPLYNOW;
    psh.hwndParent = hwndOwner;
    psh.hInstance = hInst;
    psh.pszIcon = NULL;
    psh.pszCaption = langPropTitle();
    psh.nPages = sizeof(psp) / sizeof(PROPSHEETPAGE);
    psh.nStartPage = startPage;
    psh.ppsp = (LPCPROPSHEETPAGE) &psp;
    psh.pfnCallback = NULL;

    propModified = 0;

    PropertySheet(&psh);

    if (propModified) {
        propModified = memcmp(&oldProp, pProperties, sizeof(Properties));
    }

    return propModified;
}

//////////////////////////////////////////////////////////////////////////////
// Host dependent load/save methods, Can be moved to its own file

static void getRegStrValue(char* keyDir, char* keyStr, char* returnValue) {  
    char value[1024];
    LONG rv;
    HKEY hKey;
    DWORD length = 1024;
    DWORD type;
    char directory[64];

    sprintf(directory, "Software\\%s", keyDir);

    rv = RegOpenKeyEx(HKEY_CURRENT_USER, directory, 0, KEY_QUERY_VALUE, &hKey);    
    if (rv != ERROR_SUCCESS) {
        return;
    }

    length = sizeof(value);
    rv = RegQueryValueEx(hKey, keyStr, NULL, &type, (BYTE*)value, &length);
    RegCloseKey(hKey);
    if (rv != ERROR_SUCCESS) {
        return;
    }

    strcpy(returnValue, value);
}

static void getRegIntValue(char* keyDir, char* keyStr, DWORD* returnValue) {  
    LONG rv;
    HKEY hKey;
    DWORD length;
    DWORD type;
    DWORD value;
    char directory[32];

    sprintf(directory, "Software\\%s", keyDir);

    rv = RegOpenKeyEx(HKEY_CURRENT_USER, directory, 0, KEY_QUERY_VALUE, &hKey);  
    if (rv != ERROR_SUCCESS) {
        return;
    }

    length = sizeof(value);
    rv = RegQueryValueEx(hKey, keyStr, NULL, &type, (BYTE *)&value, &length);

    RegCloseKey(hKey);

    if (rv != ERROR_SUCCESS) {
        return;
    }

    *returnValue = value;
}

static BOOL setRegIntValue(char* keyDir, char* keyStr, DWORD value) {
    HKEY hKey;
    DWORD exist;
    DWORD rv;
    DWORD dwValue = (DWORD)value;
    char directory[64];

    sprintf(directory, "Software\\%s", keyDir);

    rv = RegCreateKeyEx(HKEY_CURRENT_USER, directory, 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &exist);
    if (rv != ERROR_SUCCESS) {
        return FALSE;
    }

    rv = RegSetValueEx(hKey, keyStr, 0, REG_DWORD, (BYTE *)&dwValue, sizeof(DWORD));

    RegCloseKey(hKey);

    return TRUE;
}

static BOOL setRegStrValue(char* keyDir, char* keyStr, char* value) {
    HKEY hKey;
    DWORD exist;
    DWORD rv;
    DWORD dwValue = (DWORD)value;
    char directory[64];

    sprintf(directory, "Software\\%s", keyDir);

    rv = RegCreateKeyEx(HKEY_CURRENT_USER, directory, 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &exist);
    if (rv != ERROR_SUCCESS) {
        return FALSE;
    }

    rv = RegSetValueEx(hKey, keyStr, 0, REG_SZ, (BYTE *)value, strlen(value) + 1);

    RegCloseKey(hKey);

    return TRUE;
}

static void getIniStrValue(char* keyDir, char* keyStr, char* returnValue) {  
    char file[1024];
    char defStr[512];

    if (keyFile != NULL)      sprintf(file, "%s", keyFile);
    else if (keyPath != NULL) sprintf(file, "%s\\%s.ini", keyPath, keyDir);
    else                      sprintf(file, "%s.ini", keyDir);

    strcpy(defStr, returnValue);

    GetPrivateProfileString("General", keyStr, defStr, returnValue, 512, file);      
}

static void getIniIntValue(char* keyDir, char* keyStr, DWORD* returnValue) {  
    char file[1024];
    DWORD def = *returnValue;

    if (keyFile != NULL)      sprintf(file, "%s", keyFile);
    else if (keyPath != NULL) sprintf(file, "%s\\%s.ini", keyPath, keyDir);
    else                      sprintf(file, "%s.ini", keyDir);

    *returnValue = GetPrivateProfileInt("General", keyStr, def, file);                           
}

static BOOL setIniIntValue(char* keyDir, char* keyStr, DWORD value) {
    char file[1024];
    char buf[30];

    sprintf(buf, "%d", value);

    if (keyFile != NULL)      sprintf(file, "%s", keyFile);
    else if (keyPath != NULL) sprintf(file, "%s\\%s.ini", keyPath, keyDir);
    else                      sprintf(file, "%s.ini", keyDir);

    return WritePrivateProfileString("General", keyStr, buf, file);
}

static BOOL setIniStrValue(char* keyDir, char* keyStr, char* value) {
    char file[1024];

    if (keyFile != NULL)      sprintf(file, "%s", keyFile);
    else if (keyPath != NULL) sprintf(file, "%s\\%s.ini", keyPath, keyDir);
    else                      sprintf(file, "%s.ini", keyDir);

    return WritePrivateProfileString("General", keyStr, value, file);
}
  
void getStrValue(char* keyStr, char* returnValue) {
    if (useRegistry) getRegStrValue(registryKey, keyStr, returnValue);
    else             getIniStrValue(registryKey, keyStr, returnValue);
}

void getIntValue(char* keyStr, long* returnValue) {
    if (useRegistry) getRegIntValue(registryKey, keyStr, returnValue);
    else             getIniIntValue(registryKey, keyStr, returnValue);
}   
    
int setStrValue(char* keyStr, char* value) {
    if (useRegistry) return setRegStrValue(registryKey, keyStr, value);
    else             return setIniStrValue(registryKey, keyStr, value);
}

int setIntValue(char* keyStr, long value) {
    if (useRegistry) return setRegIntValue(registryKey, keyStr, value);
    else             return setIniIntValue(registryKey, keyStr, value);
}

char* getLocalDirectory() {
    static char dir[1024];
    char* ptr;
    DWORD size;

    size = GetModuleFileName(NULL, dir, 1024);

    if (size == 0) {
        return NULL;
    }

    ptr = dir + size;

    while (ptr > dir && *ptr != '\\') {
        ptr--;
    }
    *ptr = 0;

    if (ptr == dir) {
        return NULL;
    }

    return dir;
}

void propertiesUseRegistry(int enable)
{
    useRegistry = enable && canUseRegistry;
}

void propertiesInit(char* iniFile) 
{
    DWORD test = 0;

    setRegIntValue(registryKey, "Test", 42);
    getRegIntValue(registryKey, "Test", &test);

    canUseRegistry = test == 42;
    useRegistry = 0;

    keyPath = getLocalDirectory();

    if (iniFile != NULL && *iniFile != 0) {
        canUseRegistry = 0;
        keyFile = malloc(MAX_PATH);
        strcpy(keyFile, iniFile);
    }

    if (canUseRegistry) {
        getRegIntValue(registryKey, "UseRegistry", &useRegistry);
    }
}
