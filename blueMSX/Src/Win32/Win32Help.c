/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Help.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2004-12-06 07:32:02 $
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
#include "Win32Help.h"
#include "Win32Common.h"
#include "Language.h"
#include "build_number.h"
#include "Resource.h"
#include <stdio.h>
 

void createAboutInfo(char* buffer, int length, unsigned int clk)
{
    static char text[4096];
    static int  len = 0;

    if (len == 0) {
        sprintf(text, 
                "                                 "
                "Special thanks to: "
                "Ricardo Bittencourt,  "
                "Rudolf Lechleitner,  "
                "MkII,  "
                "Shimanuki Koshi,  "
                "Roger Filipe,  "
                "Kobayashi Michiko,  "
                "Ulver,  "
                "Nicolas Beyaert,  "
                "SLotman,  "
                "Laurent Halter,  "
                "Fabio Albergaria Dias,  "
                "Glafouk,  "
                "Martijn van Tienen,  "
                "Víctor Fernández Sánchez,  "
                "William Ouwehand,  "
                "Miikka \"MP83\" Poikela,  "
                "Davide Platania a.k.a. Kruznak,  "
                "Wouter Vermaelen,  "
                "Manuel Bilderbeek,  "
                "Maarten ter Huurne,  "
                "Jussi Pitkänen,  "
                "Tobias Keizer,  "
                "Atarulum,  "
                "Sandy Pleyte,  "
                "Amer Dugmag,  "
                "Alex Wulms,  "
                "BouKiCHi,  "
                "Marat Fayzullin,  "
                "Jarek Burczynski,  "
                "R. Belmont,  "
                "O. Galibert,  "
                "Tatsuyuki Satoh,  "
                "Gilles Vollant"
                "......          ......"
                "and YOU !!!!"
                "                                     ");

        len = strlen(text);
    }

    {
#define SHOW_VERSION_TIME 100
        int pos = clk % (len + SHOW_VERSION_TIME - length);
        if (pos < SHOW_VERSION_TIME) {
            sprintf(buffer, "version %s  build %d", BLUE_MSX_VERSION, BUILD_NUMBER);
        }
        else {
            strncpy(buffer, text + pos - SHOW_VERSION_TIME, length);
        }
    }
    buffer[length] = 0;
}


static BOOL CALLBACK aboutDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (iMsg) {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            EndDialog(hDlg, TRUE);
            return TRUE;
        }
        break;

    case WM_CLOSE:
        EndDialog(hDlg, TRUE);
        return TRUE;

    case WM_DESTROY:
        saveDialogPos(hDlg, DLG_ID_ABOUT);
        return 0;

    case WM_INITDIALOG:
        {
            _TCHAR aboutText[4096];
                _stprintf(aboutText, "%s\r\n\r\n"
                                     "%s%\t%s\r\n"
                                     "%s%\t%d\r\n"
                                     "%s%\t%s\r\n\r\n"
                                     "%s\r\n\r\n\r\n"
                                     "%s\r\n\r\n"
                              
                                     "Daniel Vik\r\n"
                                     "Benoît Delvaux\r\n"
                                     "Tomas Karlsson\r\n"
                                     "Ray Zero\r\n\r\n\r\n"
   
                                     "%s\r\n\r\n"

                                     "Shimanuki Koshi\r\n"
                                     "Roger Filipe\r\n"
                                     "Ricardo Bittencourt\r\n"
                                     "Rudolf Lechleitner\r\n"
                                     "MkII\r\n"
                                     "Kobayashi Michiko\r\n"
                                     "Ulver\r\n"
                                     "Nicolas Beyaert\r\n"
                                     "SLotman\r\n"
                                     "Laurent Halter\r\n"
                                     "Fabio Albergaria Dias\r\n"
                                     "Glafouk\r\n"
                                     "Martijn van Tienen\r\n"
                                     "Víctor Fernández Sánchez\r\n"
                                     "William Ouwehand\r\n"
                                     "Miikka \"MP83\" Poikela\r\n"
                                     "Davide Platania a.k.a. Kruznak\r\n"
                                     "Wouter Vermaelen\r\n"
                                     "Manuel Bilderbeek\r\n"
                                     "Maarten ter Huurne\r\n"
                                     "Tobias Keizer\r\n"
                                     "Atarulum\r\n"
                                     "Sandy Pleyte\r\n"
                                     "Amer Dugmag\r\n"
                                     "Alex Wulms\r\n"
                                     "BouKiCHi\r\n"
                                     "Marat Fayzullin\r\n"
                                     "Jarek Burczynski\r\n"
                                     "R. Belmont\r\n"
                                     "O. Galibert\r\n"
                                     "Tatsuyuki Satoh\r\n"
                                     "Gilles Vollant\r\n\r\n\r\n"
            
                                     "%s",
                          langDlgAboutAbout(),
                          langDlgAboutVersion(),
                          BLUE_MSX_VERSION,
                          langDlgAboutBuildNumber(),
                          BUILD_NUMBER,
                          langDlgAboutBuildDate(),
                          BUILD_DATE,
                          langDlgAboutCreat(),
                          langDlgAboutDevel(),
                          langDlgAboutThanks(),
                          langDlgAboutLisence());

            updateDialogPos(hDlg, DLG_ID_ABOUT, 0, 1);
            SetWindowText(hDlg, langDlgAboutTitle());
            SetWindowText(GetDlgItem(hDlg, IDOK), langDlgOK());

            SendMessage(GetDlgItem(hDlg, IDC_ABOUTTEXT), WM_SETTEXT, 0, (LPARAM)aboutText);
        }
        return FALSE;
    }

    return FALSE;
}

void helpShowAbout(HWND hwnd) {
    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, aboutDlgProc);
}

