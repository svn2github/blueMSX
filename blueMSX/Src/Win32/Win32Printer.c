/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Printer.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-01-23 22:06:49 $
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
**TRUE
******************************************************************************
*/
#include <windows.h>
#include <tchar.h>
#include "Win32Printer.h"
#include "ArchPrinter.h"

static HANDLE hPrinter = NULL; 
static BOOL bPrinterInitialized = FALSE;

static BOOL printerReady(void)
{
    DOC_INFO_1 pDocInfo;
    DWORD dwPrintJob;

    // Already initialized?
    if (bPrinterInitialized)
        return TRUE;

    // Get a handle to the printer
    if (!OpenPrinter(_T("hp photosmart 7700 series"), &hPrinter, NULL))
        return FALSE;

    // Fill in the structure with info
    ZeroMemory(&pDocInfo, sizeof(pDocInfo));
    pDocInfo.pDocName = _T("blueMSX");
    pDocInfo.pOutputFile = NULL;
    pDocInfo.pDatatype = "RAW";

    // Inform the spooler the document is beginning
    if ((dwPrintJob = StartDocPrinter(hPrinter, 1, (LPBYTE)&pDocInfo)) == 0) {
          ClosePrinter(hPrinter);
          return FALSE;
    }

    // Start a page
    if (!StartPagePrinter(hPrinter)) {
          EndDocPrinter( hPrinter );
          ClosePrinter( hPrinter );
          return FALSE;
    }

    bPrinterInitialized = TRUE;

    return TRUE;
}

static void printerClose(void)
{
    // Inform the spooler that the document is ending
    EndDocPrinter(hPrinter);
    ClosePrinter(hPrinter);

    bPrinterInitialized = FALSE;
}

static void printerWrite(BYTE value)
{
    DWORD dwWritten = 0;

    // Form feed?
    if (value == 12) {
        EndPagePrinter(hPrinter);
        if (!StartPagePrinter(hPrinter))
            printerClose();
    }
    else
//        if (!WritePrinter(hPrinter, _T("blueMSX"), _tcsclen(_T("blueMSX")), &dwWritten))
        if (!WritePrinter(hPrinter, &value, 1, &dwWritten))
            printerClose();
}

void archPrinterWrite(BYTE value)
{
    if (printerReady())
        printerWrite(value);
}

int archPrinterReady(void)
{
    return printerReady();
}
