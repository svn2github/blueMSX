/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Printer.c,v $
**
** $Revision: 1.6 $
**
** $Date: 2005-05-09 20:58:31 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vikl, Tomas Karlsson
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
#include "Properties.h"



#ifdef __GNUC__ // FIXME: Include is not available in gnu c
#include <string.h>
static HRESULT StringCchCopy(LPTSTR d, size_t l, LPCTSTR s) { strncpy(d, s, l); d[l-1]=0; return S_OK; }
static HRESULT StringCchLength(LPCTSTR s, size_t m, size_t *l) { *l = strlen(s); if (*l > m) *l = m; return S_OK; }
#else
#define STRSAFE_NO_DEPRECATE
#include <strsafe.h>
#endif

#include "Win32Printer.h"
#include "ArchPrinter.h"

static HDC hdcPrn;
static TEXTMETRIC tm;
static BOOL bPrinterInitialized = FALSE;
static TCHAR szLineBuffer[81];
static BYTE nLinePos;
static UINT nRow;

typedef enum {PRINT_US=0, PRINT_FR=1, PRINT_DE=2, PRINT_UK=3, PRINT_DK=4, PRINT_SE=5, PRINT_IT=6, PRINT_SP=7} printerCharMaps;
/*
     US  FR  DE  UK  DK  SE  IT  SP
0x23 "#","#","#","£","#","#","#","#"
0x24 "$","$","$","$","$","¤","$","$"
0x40 "@","à","§","@","@","É","@","@"
0x5B "[","°","Ä","[","Æ","Ä","°","í"
0x5C "\","ç","Ö","\","Ø","Ö","\","Ñ"
0x5D "]","§","Ü","]","Å","Å","é","¿"
0x5E "^","^","^","^","^","Ü","^","^"
0x60 "´","´","´","´","´","é","ù","´"
0x7B "{","é","ä","{","æ","ä","à","¨"
0x7C "|","ù","ö","|","ø","ö","ò","ñ"
0x7D "}","è","ü","}","å","å","è","}"
0x7E "~","¨","ß","~","~","ü","ì","~"
*/
static const UInt8 prnCharMapNumber[8] = {0x23,0x23,0x23,0xA3,0x23,0x23,0x23,0x23};
static const UInt8 prnCharMapDollar[8] = {0x24,0x24,0x24,0x24,0x24,0xA4,0x24,0x24};
static const UInt8 prnCharMapAt[8] = {0x40,0xE0,0xA7,0x40,0x40,0xC9,0x40,0x40};
static const UInt8 prnCharMapLeftSquareBracket[8] = {0x5B,0xB0,0xC4,0x5B,0xC6,0xC4,0xB0,0xED};
static const UInt8 prnCharMapReverseSolidus[8] = {0x5C,0xE7,0xD6,0x5C,0xD8,0xD6,0x5C,0xD1};
static const UInt8 prnCharMapRightSquareBracket[8] = {0x5D,0xA7,0xDC,0x5D,0xC5,0xC5,0xE9,0xBF};
static const UInt8 prnCharMapCircumflexAccent[8] = {0x5E,0x5E,0x5E,0x5E,0x5E,0xDC,0x5E,0x5E};
static const UInt8 prnCharMapAcuteAccent[8] = {0xB4,0xB4,0xB4,0xB4,0xB4,0xE9,0xF9,0xB4};
static const UInt8 prnCharMapLeftCurlyBracket[8] = {0x7B,0xE9,0xE4,0x7B,0xE6,0xE4,0xE0,0xA8};
static const UInt8 prnCharMapVerticalLine[8] = {0x7C,0xF9,0xF6,0x7C,0xF8,0xF6,0xF2,0xF1};
static const UInt8 prnCharMapRightCurlyBracket[8] = {0x7D,0xE8,0xFC,0x7D,0xE5,0xE5,0xE8,0x7D};
static const UInt8 prnCharTilde[8] = {0x7E,0xA8,0xDF,0x7E,0x7E,0xFC,0xEC,0x7E};

static void printerDestroy(void)
{
    if (EndPage(hdcPrn) > 0)
        EndDoc(hdcPrn);

    DeleteObject(SelectObject(hdcPrn, GetStockObject(SYSTEM_FONT)));
    DeleteDC(hdcPrn);
    bPrinterInitialized = FALSE;
    nLinePos = 0;
}

static void printerWrite(BYTE value)
{
    DWORD dwWritten = 0;
    DWORD dwLength = 0;

    switch (value) {
    case 0x23:
        value = prnCharMapNumber[PRINT_US];
        break;
    case 0x24:
        value = prnCharMapDollar[PRINT_US];
        break;
    case 0x40:
        value = prnCharMapAt[PRINT_US];
        break;
    case 0x5b:
        value = prnCharMapLeftSquareBracket[PRINT_US];
        break;
    case 0x5c:
        value = prnCharMapReverseSolidus[PRINT_US];
        break;
    case 0x5d:
        value = prnCharMapRightSquareBracket[PRINT_US];
        break;
    case 0x5e:
        value = prnCharMapCircumflexAccent[PRINT_US];
        break;
    case 0x60:
        value = prnCharMapAcuteAccent[PRINT_US];
        break;
    case 0x7b:
        value = prnCharMapLeftCurlyBracket[PRINT_US];
        break;
    case 0x7c:
        value = prnCharMapVerticalLine[PRINT_US];
        break;
    case 0x7d:
        value = prnCharMapRightCurlyBracket[PRINT_US];
        break;
    case 0x7e:
        value = prnCharTilde[PRINT_US];
        break;
    case 0x0d:
        nLinePos = 0;
        return;
    case 0x0a:
        dwLength = strlen(szLineBuffer);
        TextOut(hdcPrn, 0, tm.tmHeight*nRow, szLineBuffer, dwLength);
        memset(szLineBuffer, 0, sizeof(szLineBuffer));
        nRow++;
        nLinePos = 0;
        if (nRow == 70) { // Fix correct row number
            EndPage(hdcPrn);
            nRow = 0;
            if (!(StartPage(hdcPrn) > 0))
                printerDestroy();
        }
        return;
    case 0x0c:  // Form feed
        dwLength = strlen(szLineBuffer);
        if (dwLength > 0) {
            TextOut(hdcPrn, 0, tm.tmHeight*nRow, szLineBuffer, dwLength);
            memset(szLineBuffer, 0, sizeof(szLineBuffer));
        }
        EndPage(hdcPrn);
        nRow = 0;
        nLinePos = 0;
        if (!(StartPage(hdcPrn) > 0))
            printerDestroy();
        return;
    }

    szLineBuffer[nLinePos] = value;
    nLinePos++;
    if (nLinePos == 80) {
        dwLength = strlen(szLineBuffer);
        TextOut(hdcPrn, 0, tm.tmHeight*nRow, szLineBuffer, dwLength);
        memset(szLineBuffer, 0, sizeof(szLineBuffer));
        nRow++;
        nLinePos = 0;
        if (nRow == 70) { // Fix correct row number
            EndPage(hdcPrn);
            nRow = 0;
            if (!(StartPage(hdcPrn) > 0))
                printerDestroy();
        }
    }
}

static int printerCreate(void)
{
    LOGFONT lf;
    DOCINFO dc;

    Properties* pProperties = propGetGlobalProperties();

    if (bPrinterInitialized)
        return TRUE;

    if ((hdcPrn = CreateDC(NULL, TEXT(pProperties->ports.Lpt.name), NULL, NULL)) == NULL)
        return FALSE;

    ZeroMemory(&lf, sizeof(LOGFONT));
    lf.lfHeight = -MulDiv(10, GetDeviceCaps(hdcPrn, LOGPIXELSY), 72);
    lf.lfPitchAndFamily = FIXED_PITCH | FF_DONTCARE;
    memcpy((void*)lf.lfFaceName, "DotMatrix", strlen("DotMatrix") + 1);
    SelectObject(hdcPrn, CreateFontIndirect(&lf)); 

    GetTextMetrics(hdcPrn, &tm);

    ZeroMemory(&dc, sizeof(DOCINFO));
    dc.cbSize = sizeof(DOCINFO);
    dc.lpszDocName = TEXT("blueMSX");

    if ((!StartDoc(hdcPrn, &dc) > 0) && (!StartPage(hdcPrn) > 0))
    {
        if (EndPage(hdcPrn) > 0)
            EndDoc(hdcPrn);
        DeleteDC(hdcPrn);
        return FALSE;
    }
    bPrinterInitialized = TRUE;
    nLinePos = 0;
    nRow = 0;
    return TRUE;
}

void archPrinterWrite(BYTE value)
{
    if (bPrinterInitialized)
        printerWrite(value);
}

int archPrinterCreate(void)
{
    return printerCreate();
}

void archPrinterDestroy(void)
{
    printerDestroy();
}
