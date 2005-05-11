/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Printer.c,v $
**
** $Revision: 1.15 $
**
** $Date: 2005-05-11 23:55:46 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Rudolf Lechleitner, Daniel Vik, Tomas Karlsson
**
** This code is ported from RuMSX and modified to fit into the blueMSX
** framework.
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
#include "Win32Printer.h"
#include "ArchPrinter.h"



static PropLptEmulation printerType = P_LPT_MSXPRN;

static void ResetEmulatedPrinter(void);

//////////////////////////////////////////////////////////////////////////////////
/// Raw printer emulation
//////////////////////////////////////////////////////////////////////////////////

static HANDLE hFile = INVALID_HANDLE_VALUE;

static void printerRawDestroy(void)
{
    if (hFile != INVALID_HANDLE_VALUE) {
        CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;
    }
}

static void printerRawWrite(BYTE value)
{
    if (hFile != INVALID_HANDLE_VALUE) {
        DWORD dwWritten;
        WriteFile(hFile, &value, 1, &dwWritten, NULL);
    }
}

static int printerRawCreate(void)
{
    Properties* pProperties = propGetGlobalProperties();

    hFile = CreateFile(pProperties->ports.Lpt.portName, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH, NULL);

    return hFile != INVALID_HANDLE_VALUE;
}


///////////////////////////////////////////////////////////////
/// Emulated printer, from RuMSX
///////////////////////////////////////////////////////////////

//#define USE_REAL_FONT

static BYTE FontBitmaps[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3c, 0x42, 0xa5, 0x81, 0xa5, 0x99, 0x42, 0x3c,
    0x3c, 0x7e, 0xdb, 0xff, 0xff, 0xdb, 0x66, 0x3c,
    0x6c, 0xfe, 0xfe, 0xfe, 0x7c, 0x38, 0x10, 0x00,
    0x10, 0x38, 0x7c, 0xfe, 0x7c, 0x38, 0x10, 0x00,
    0x10, 0x38, 0x54, 0xfe, 0x54, 0x10, 0x38, 0x00,
    0x10, 0x38, 0x7c, 0xfe, 0xfe, 0x10, 0x38, 0x00,
    0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xe7, 0xe7, 0xff, 0xff, 0xff,
    0x38, 0x44, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00,
    0xc7, 0xbb, 0x7d, 0x7d, 0x7d, 0xbb, 0xc7, 0xff,
    0x0f, 0x03, 0x05, 0x79, 0x88, 0x88, 0x88, 0x70,
    0x38, 0x44, 0x44, 0x44, 0x38, 0x10, 0x7c, 0x10,
    0x30, 0x28, 0x24, 0x24, 0x28, 0x20, 0xe0, 0xc0,
    0x3c, 0x24, 0x3c, 0x24, 0x24, 0xe4, 0xdc, 0x18,
    0x10, 0x54, 0x38, 0xee, 0x38, 0x54, 0x10, 0x00,
    0x10, 0x10, 0x10, 0x7c, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0xff, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xff, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0xf0, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x1f, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0xff, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x1f, 0x10, 0x10, 0x10, 0x10,
    0x00, 0x00, 0x00, 0xf0, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x1f, 0x00, 0x00, 0x00, 0x00,
    0x10, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00,
    0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81,
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
    0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01,
    0x00, 0x10, 0x10, 0xff, 0x10, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x20, 0x00,
    0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x50, 0x50, 0xf8, 0x50, 0xf8, 0x50, 0x50, 0x00,
    0x20, 0x78, 0xa0, 0x70, 0x28, 0xf0, 0x20, 0x00,
    0xc0, 0xc8, 0x10, 0x20, 0x40, 0x98, 0x18, 0x00,
    0x40, 0xa0, 0x40, 0xa8, 0x90, 0x98, 0x60, 0x00,
    0x10, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x10, 0x20, 0x40, 0x40, 0x40, 0x20, 0x10, 0x00,
    0x40, 0x20, 0x10, 0x10, 0x10, 0x20, 0x40, 0x00,
    0x20, 0xa8, 0x70, 0x20, 0x70, 0xa8, 0x20, 0x00,
    0x00, 0x20, 0x20, 0xf8, 0x20, 0x20, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x40,
    0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00,
    0x00, 0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00,
    0x70, 0x88, 0x98, 0xa8, 0xc8, 0x88, 0x70, 0x00,
    0x20, 0x60, 0xa0, 0x20, 0x20, 0x20, 0xf8, 0x00,
    0x70, 0x88, 0x08, 0x10, 0x60, 0x80, 0xf8, 0x00,
    0x70, 0x88, 0x08, 0x30, 0x08, 0x88, 0x70, 0x00,
    0x10, 0x30, 0x50, 0x90, 0xf8, 0x10, 0x10, 0x00,
    0xf8, 0x80, 0xe0, 0x10, 0x08, 0x10, 0xe0, 0x00,
    0x30, 0x40, 0x80, 0xf0, 0x88, 0x88, 0x70, 0x00,
    0xf8, 0x88, 0x10, 0x20, 0x20, 0x20, 0x20, 0x00,
    0x70, 0x88, 0x88, 0x70, 0x88, 0x88, 0x70, 0x00,
    0x70, 0x88, 0x88, 0x78, 0x08, 0x10, 0x60, 0x00,
    0x00, 0x00, 0x20, 0x00, 0x00, 0x20, 0x00, 0x00,
    0x00, 0x00, 0x20, 0x00, 0x00, 0x20, 0x20, 0x40,
    0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x00,
    0x00, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0x00, 0x00,
    0xc0, 0x60, 0x30, 0x18, 0x30, 0x60, 0xc0, 0x00,
    0x70, 0x88, 0x08, 0x10, 0x20, 0x00, 0x20, 0x00,
    0x70, 0x88, 0x08, 0x68, 0xa8, 0xa8, 0x70, 0x00,
    0x20, 0x50, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x00,
    0xf0, 0x48, 0x48, 0x70, 0x48, 0x48, 0xf0, 0x00,
    0x30, 0x48, 0x80, 0x80, 0x80, 0x48, 0x30, 0x00,
    0xe0, 0x50, 0x48, 0x48, 0x48, 0x50, 0xe0, 0x00,
    0xf8, 0x80, 0x80, 0xf0, 0x80, 0x80, 0xf8, 0x00,
    0xf8, 0x80, 0x80, 0xf0, 0x80, 0x80, 0x80, 0x00,
    0x70, 0x88, 0x80, 0xb8, 0x88, 0x88, 0x70, 0x00,
    0x88, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x88, 0x00,
    0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00,
    0x38, 0x10, 0x10, 0x10, 0x90, 0x90, 0x60, 0x00,
    0x88, 0x90, 0xa0, 0xc0, 0xa0, 0x90, 0x88, 0x00,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xf8, 0x00,
    0x88, 0xd8, 0xa8, 0xa8, 0x88, 0x88, 0x88, 0x00,
    0x88, 0xc8, 0xc8, 0xa8, 0x98, 0x98, 0x88, 0x00,
    0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00,
    0xf0, 0x88, 0x88, 0xf0, 0x80, 0x80, 0x80, 0x00,
    0x70, 0x88, 0x88, 0x88, 0xa8, 0x90, 0x68, 0x00,
    0xf0, 0x88, 0x88, 0xf0, 0xa0, 0x90, 0x88, 0x00,
    0x70, 0x88, 0x80, 0x70, 0x08, 0x88, 0x70, 0x00,
    0xf8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00,
    0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00,
    0x88, 0x88, 0x88, 0x88, 0x50, 0x50, 0x20, 0x00,
    0x88, 0x88, 0x88, 0xa8, 0xa8, 0xd8, 0x88, 0x00,
    0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88, 0x00,
    0x88, 0x88, 0x88, 0x70, 0x20, 0x20, 0x20, 0x00,
    0xf8, 0x08, 0x10, 0x20, 0x40, 0x80, 0xf8, 0x00,
    0x70, 0x40, 0x40, 0x40, 0x40, 0x40, 0x70, 0x00,
    0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x00,
    0x70, 0x10, 0x10, 0x10, 0x10, 0x10, 0x70, 0x00,
    0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00,
    0x40, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00,
    0x80, 0x80, 0xb0, 0xc8, 0x88, 0xc8, 0xb0, 0x00,
    0x00, 0x00, 0x70, 0x88, 0x80, 0x88, 0x70, 0x00,
    0x08, 0x08, 0x68, 0x98, 0x88, 0x98, 0x68, 0x00,
    0x00, 0x00, 0x70, 0x88, 0xf8, 0x80, 0x70, 0x00,
    0x10, 0x28, 0x20, 0xf8, 0x20, 0x20, 0x20, 0x00,
    0x00, 0x00, 0x68, 0x98, 0x98, 0x68, 0x08, 0x70,
    0x80, 0x80, 0xf0, 0x88, 0x88, 0x88, 0x88, 0x00,
    0x20, 0x00, 0x60, 0x20, 0x20, 0x20, 0x70, 0x00,
    0x10, 0x00, 0x30, 0x10, 0x10, 0x10, 0x90, 0x60,
    0x40, 0x40, 0x48, 0x50, 0x60, 0x50, 0x48, 0x00,
    0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00,
    0x00, 0x00, 0xd0, 0xa8, 0xa8, 0xa8, 0xa8, 0x00,
    0x00, 0x00, 0xb0, 0xc8, 0x88, 0x88, 0x88, 0x00,
    0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, 0x00,
    0x00, 0x00, 0xb0, 0xc8, 0xc8, 0xb0, 0x80, 0x80,
    0x00, 0x00, 0x68, 0x98, 0x98, 0x68, 0x08, 0x08,
    0x00, 0x00, 0xb0, 0xc8, 0x80, 0x80, 0x80, 0x00,
    0x00, 0x00, 0x78, 0x80, 0xf0, 0x08, 0xf0, 0x00,
    0x40, 0x40, 0xf0, 0x40, 0x40, 0x48, 0x30, 0x00,
    0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x68, 0x00,
    0x00, 0x00, 0x88, 0x88, 0x88, 0x50, 0x20, 0x00,
    0x00, 0x00, 0x88, 0xa8, 0xa8, 0xa8, 0x50, 0x00,
    0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88, 0x00,
    0x00, 0x00, 0x88, 0x88, 0x98, 0x68, 0x08, 0x70,
    0x00, 0x00, 0xf8, 0x10, 0x20, 0x40, 0xf8, 0x00,
    0x18, 0x20, 0x20, 0x40, 0x20, 0x20, 0x18, 0x00,
    0x20, 0x20, 0x20, 0x00, 0x20, 0x20, 0x20, 0x00,
    0xc0, 0x20, 0x20, 0x10, 0x20, 0x20, 0xc0, 0x00,
    0x40, 0xa8, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x20, 0x50, 0xf8, 0x00, 0x00, 0x00,
    0x70, 0x88, 0x80, 0x80, 0x88, 0x70, 0x20, 0x60,
    0x90, 0x00, 0x00, 0x90, 0x90, 0x90, 0x68, 0x00,
    0x10, 0x20, 0x70, 0x88, 0xf8, 0x80, 0x70, 0x00,
    0x20, 0x50, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00,
    0x48, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00,
    0x20, 0x10, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00,
    0x20, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00,
    0x00, 0x70, 0x80, 0x80, 0x80, 0x70, 0x10, 0x60,
    0x20, 0x50, 0x70, 0x88, 0xf8, 0x80, 0x70, 0x00,
    0x50, 0x00, 0x70, 0x88, 0xf8, 0x80, 0x70, 0x00,
    0x20, 0x10, 0x70, 0x88, 0xf8, 0x80, 0x70, 0x00,
    0x50, 0x00, 0x00, 0x60, 0x20, 0x20, 0x70, 0x00,
    0x20, 0x50, 0x00, 0x60, 0x20, 0x20, 0x70, 0x00,
    0x40, 0x20, 0x00, 0x60, 0x20, 0x20, 0x70, 0x00,
    0x50, 0x00, 0x20, 0x50, 0x88, 0xf8, 0x88, 0x00,
    0x20, 0x00, 0x20, 0x50, 0x88, 0xf8, 0x88, 0x00,
    0x10, 0x20, 0xf8, 0x80, 0xf0, 0x80, 0xf8, 0x00,
    0x00, 0x00, 0x6c, 0x12, 0x7e, 0x90, 0x6e, 0x00,
    0x3e, 0x50, 0x90, 0x9c, 0xf0, 0x90, 0x9e, 0x00,
    0x60, 0x90, 0x00, 0x60, 0x90, 0x90, 0x60, 0x00,
    0x90, 0x00, 0x00, 0x60, 0x90, 0x90, 0x60, 0x00,
    0x40, 0x20, 0x00, 0x60, 0x90, 0x90, 0x60, 0x00,
    0x40, 0xa0, 0x00, 0xa0, 0xa0, 0xa0, 0x50, 0x00,
    0x40, 0x20, 0x00, 0xa0, 0xa0, 0xa0, 0x50, 0x00,
    0x90, 0x00, 0x90, 0x90, 0xb0, 0x50, 0x10, 0xe0,
    0x50, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, 0x00,
    0x50, 0x00, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00,
    0x20, 0x20, 0x78, 0x80, 0x80, 0x78, 0x20, 0x20,
    0x18, 0x24, 0x20, 0xf8, 0x20, 0xe2, 0x5c, 0x00,
    0x88, 0x50, 0x20, 0xf8, 0x20, 0xf8, 0x20, 0x00,
    0xc0, 0xa0, 0xa0, 0xc8, 0x9c, 0x88, 0x88, 0x8c,
    0x18, 0x20, 0x20, 0xf8, 0x20, 0x20, 0x20, 0x40,
    0x10, 0x20, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00,
    0x10, 0x20, 0x00, 0x60, 0x20, 0x20, 0x70, 0x00,
    0x20, 0x40, 0x00, 0x60, 0x90, 0x90, 0x60, 0x00,
    0x20, 0x40, 0x00, 0x90, 0x90, 0x90, 0x68, 0x00,
    0x50, 0xa0, 0x00, 0xa0, 0xd0, 0x90, 0x90, 0x00,
    0x28, 0x50, 0x00, 0xc8, 0xa8, 0x98, 0x88, 0x00,
    0x00, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00, 0xf8,
    0x00, 0x60, 0x90, 0x90, 0x90, 0x60, 0x00, 0xf0,
    0x20, 0x00, 0x20, 0x40, 0x80, 0x88, 0x70, 0x00,
    0x00, 0x00, 0x00, 0xf8, 0x80, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xf8, 0x08, 0x08, 0x00, 0x00,
    0x84, 0x88, 0x90, 0xa8, 0x54, 0x84, 0x08, 0x1c,
    0x84, 0x88, 0x90, 0xa8, 0x58, 0xa8, 0x3c, 0x08,
    0x20, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x00,
    0x00, 0x00, 0x24, 0x48, 0x90, 0x48, 0x24, 0x00,
    0x00, 0x00, 0x90, 0x48, 0x24, 0x48, 0x90, 0x00,
    0x28, 0x50, 0x20, 0x50, 0x88, 0xf8, 0x88, 0x00,
    0x28, 0x50, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00,
    0x28, 0x50, 0x00, 0x70, 0x20, 0x20, 0x70, 0x00,
    0x28, 0x50, 0x00, 0x20, 0x20, 0x20, 0x70, 0x00,
    0x28, 0x50, 0x00, 0x70, 0x88, 0x88, 0x70, 0x00,
    0x50, 0xa0, 0x00, 0x60, 0x90, 0x90, 0x60, 0x00,
    0x28, 0x50, 0x00, 0x88, 0x88, 0x88, 0x70, 0x00,
    0x50, 0xa0, 0x00, 0xa0, 0xa0, 0xa0, 0x50, 0x00,
    0xfc, 0x48, 0x48, 0x48, 0xe8, 0x08, 0x50, 0x20,
    0x00, 0x50, 0x00, 0x50, 0x50, 0x50, 0x10, 0x20,
    0xc0, 0x44, 0xc8, 0x54, 0xec, 0x54, 0x9e, 0x04,
    0x10, 0xa8, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x20, 0x50, 0x88, 0x50, 0x20, 0x00, 0x00,
    0x88, 0x10, 0x20, 0x40, 0x80, 0x28, 0x00, 0x00,
    0x7c, 0xa8, 0xa8, 0x68, 0x28, 0x28, 0x28, 0x00,
    0x38, 0x40, 0x30, 0x48, 0x48, 0x30, 0x08, 0x70,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
    0xf0, 0xf0, 0xf0, 0xf0, 0x0f, 0x0f, 0x0f, 0x0f,
    0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x3c, 0x3c, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0x0f, 0x0f, 0x0f, 0x0f, 0xf0, 0xf0, 0xf0, 0xf0,
    0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
    0x11, 0x22, 0x44, 0x88, 0x11, 0x22, 0x44, 0x88,
    0x88, 0x44, 0x22, 0x11, 0x88, 0x44, 0x22, 0x11,
    0xfe, 0x7c, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x7c, 0xfe,
    0x80, 0xc0, 0xe0, 0xf0, 0xe0, 0xc0, 0x80, 0x00,
    0x01, 0x03, 0x07, 0x0f, 0x07, 0x03, 0x01, 0x00,
    0xff, 0x7e, 0x3c, 0x18, 0x18, 0x3c, 0x7e, 0xff,
    0x81, 0xc3, 0xe7, 0xff, 0xff, 0xe7, 0xc3, 0x81,
    0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f,
    0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0,
    0x33, 0x33, 0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc,
    0x00, 0x20, 0x20, 0x50, 0x50, 0x88, 0xf8, 0x00,
    0x20, 0x20, 0x70, 0x20, 0x70, 0x20, 0x20, 0x00,
    0x00, 0x00, 0x00, 0x50, 0x88, 0xa8, 0x50, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
    0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x68, 0x90, 0x90, 0x90, 0x68, 0x00,
    0x30, 0x48, 0x48, 0x70, 0x48, 0x48, 0x70, 0xc0,
    0xf8, 0x88, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00,
    0xf8, 0x50, 0x50, 0x50, 0x50, 0x50, 0x98, 0x00,
    0xf8, 0x88, 0x40, 0x20, 0x40, 0x88, 0xf8, 0x00,
    0x00, 0x00, 0x78, 0x90, 0x90, 0x90, 0x60, 0x00,
    0x00, 0x50, 0x50, 0x50, 0x50, 0x68, 0x80, 0x80,
    0x00, 0x50, 0xa0, 0x20, 0x20, 0x20, 0x20, 0x00,
    0xf8, 0x20, 0x70, 0xa8, 0xa8, 0x70, 0x20, 0xf8,
    0x20, 0x50, 0x88, 0xf8, 0x88, 0x50, 0x20, 0x00,
    0x70, 0x88, 0x88, 0x88, 0x50, 0x50, 0xd8, 0x00,
    0x30, 0x40, 0x40, 0x20, 0x50, 0x50, 0x50, 0x20,
    0x00, 0x00, 0x00, 0x50, 0xa8, 0xa8, 0x50, 0x00,
    0x08, 0x70, 0xa8, 0xa8, 0xa8, 0x70, 0x80, 0x00,
    0x38, 0x40, 0x80, 0xf8, 0x80, 0x40, 0x38, 0x00,
    0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x00,
    0x00, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0x00,
    0x20, 0x20, 0xf8, 0x20, 0x20, 0x00, 0xf8, 0x00,
    0xc0, 0x30, 0x08, 0x30, 0xc0, 0x00, 0xf8, 0x00,
    0x18, 0x60, 0x80, 0x60, 0x18, 0x00, 0xf8, 0x00,
    0x10, 0x28, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xa0, 0x40,
    0x00, 0x20, 0x00, 0xf8, 0x00, 0x20, 0x00, 0x00,
    0x00, 0x50, 0xa0, 0x00, 0x50, 0xa0, 0x00, 0x00,
    0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x30, 0x78, 0x78, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x3e, 0x20, 0x20, 0x20, 0xa0, 0x60, 0x20, 0x00,
    0xa0, 0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00,
    0x40, 0xa0, 0x20, 0x40, 0xe0, 0x00, 0x00, 0x00,
    0x00, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


#define MAX_ESC_CMDSIZE      8      // Maximum size of ESC-command

#define PRTFONT_PICA         0      // Courier 1/10" (Pica)
#define PRTFONT_ELITE        1      // Courier 1/12" (Elite)
#define PRTFONT_CONDENSED    2      // Courier 1/17" (Condensed)
#define PRTFONT_PROPORTIONAL 3      // Proportional

typedef struct {
    int     iFont;
    BOOL    fLetterQuality;
    BOOL    fBold;
    BOOL    fItalic;
    BOOL    fSuperscript;
    BOOL    fSubscript;
    BOOL    fDoubleWidth;
    BOOL    fUnderline;
    BOOL    fDoubleStrike;
    BOOL    fEscSequence;
    BOOL    fAlternateChar;
    BOOL    fDetectPaperOut;
    BOOL    fJapanese;
    BOOL    fNinePinGraphics;
    BOOL    fLeftToRight;
    BOOL    fGraphicsHiLo;
    UINT    uiEightBit;
    UINT    uiPerforationSkip;
    UINT    uiLeftBorder;
    UINT    uiRightBorder;
    UINT    uiTotalWidth;
    UINT    uiTotalHeight;
    UINT    uiFontWidth;
    UINT    uiRemainingCommandBytes;
    size_t  sizeEscPos;
    BYTE    abEscSeq[MAX_ESC_CMDSIZE];
    size_t  sizeRemainingDataBytes;
    UINT    uiDensity;
    double  uiHpos;
    UINT    uiVpos;
    UINT    uiPageTop;
    UINT    uiLines;
    UINT    uiLineFeed;
    UINT    uiPageHeight;
    double  uiPixelSizeX;
    double  uiPixelSizeY;
} PRINTERRAM, *PPRINTERRAM;

PRINTERRAM   stPrtRam;
BOOL         fPrintDataOnPage;
ULONG        ulPrintPage = 1;
HDC          hdcPrinter = NULL;

static char  printDir[MAX_PATH];
static BYTE  abFontImage[256 * 8];
static int   aiCharStart[256];
static int   aiCharWidth[256];
static BYTE  abGrphImage[sizeof(DWORD) * 8];
static TCHAR szDocTitle[MAX_PATH];
static TEXTMETRIC tm;

static struct {
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD bmiColors[2];
} bmiFont, bmiGrph;

void UpdateFont(void)
{
    int fontSize[] = { 10, 12, 17, 10 };
    LOGFONT lf;

    ZeroMemory(&lf, sizeof(LOGFONT));
    lf.lfHeight = -MulDiv(fontSize[stPrtRam.iFont] / (stPrtRam.fSuperscript || stPrtRam.fSubscript ? 2 : 1), 
                          GetDeviceCaps(hdcPrinter, LOGPIXELSY), 72);
    lf.lfPitchAndFamily = FIXED_PITCH | FF_DONTCARE;

    lf.lfItalic = stPrtRam.fItalic;
    lf.lfStrikeOut = stPrtRam.fDoubleStrike;
    lf.lfUnderline = stPrtRam.fUnderline;
    lf.lfWeight = stPrtRam.fBold ? FW_BOLD : FW_NORMAL;

    strcpy(lf.lfFaceName, "DotMatrix");
    DeleteObject(SelectObject(hdcPrinter, CreateFontIndirect(&lf))); 
    
    GetTextMetrics(hdcPrinter, &tm);
}

void FlushEmulatedPrinter(void)
{
    if (hdcPrinter) {
        if (fPrintDataOnPage) {
            EndPage( hdcPrinter );
            EndDoc( hdcPrinter );
            ulPrintPage++;
        }
        else
            AbortDoc( hdcPrinter );
    }

    stPrtRam.uiHpos = stPrtRam.uiLeftBorder;
    stPrtRam.uiVpos = stPrtRam.uiPageTop;

    fPrintDataOnPage=FALSE;
}

static void SeekPrinterHeadRelative(double iOffset)
{
    stPrtRam.uiHpos += iOffset;

    if ((UINT)stPrtRam.uiHpos > stPrtRam.uiRightBorder) {
        stPrtRam.uiHpos = stPrtRam.uiLeftBorder;

        stPrtRam.uiVpos += stPrtRam.uiLineFeed;
        if (stPrtRam.uiVpos >= stPrtRam.uiPageHeight)
            FlushEmulatedPrinter();
    }
}

void SetPrintTitle(LPTSTR lpszDocTitle)
{
    if (lpszDocTitle)
        lstrcpy( szDocTitle, lpszDocTitle );
    else
        ZeroMemory( szDocTitle, sizeof(szDocTitle) );

    return;
}

void SetPrinterFont(LPBYTE lpCharacters, size_t sizeBytes)
{
    LPBYTE lpCurByte;
    int    iChar;
    int    iByte;
    BYTE   bCharMask;
    BYTE   bCurrBit;
    int    iBit;
    BOOL   fFound;

    // Reset previous settings
    ZeroMemory( aiCharStart, sizeof(aiCharStart) );
    ZeroMemory( aiCharWidth, sizeof(aiCharWidth) );
    ZeroMemory( abFontImage, sizeof(abFontImage) );

    // Apply new settings...
    if (lpCharacters)
    {
        lpCurByte=lpCharacters;
        for (iChar=0; iChar<256; iChar++)
        {
            bCharMask=0;
            for (iByte=0; iByte<8; iByte++)
            {
                bCharMask |= *lpCurByte;
                abFontImage[((7*256)-(iByte<<8)) | iChar] = *lpCurByte;

                lpCurByte++;
            }

            // Calculate start-position of proportional characters
            bCurrBit=0x80;
            fFound=FALSE;
            for (iBit=0; iBit<8 && !fFound; iBit++)
            {
                if (bCharMask & bCurrBit)
                {
                    fFound=TRUE;

                    // Characters without pixels (like SPACE) are starting
                    // at position 0, which is the already initialized value.
                    aiCharStart[iChar]=iBit;
                }

                bCurrBit>>=1;
            }

            // Calculate width of proportional characters
            //
            // (if the right seven bits are 0 we assume a character-size
            // of 1 pixel on the left, which is also valid for the
            // SPACE character)
            aiCharWidth[iChar]=1;

            bCurrBit=0x01;
            fFound=FALSE;
            for (iBit=8; iBit>0 && !fFound; iBit--)
            {
                if (bCharMask & bCurrBit)
                {
                    fFound=TRUE;
                    aiCharWidth[iChar] = iBit - aiCharStart[iChar];
                }

                bCurrBit<<=1;
            }
        } // next character

        ZeroMemory( &bmiFont, sizeof(bmiFont) );
        bmiFont.bmiHeader.biSize          = sizeof(bmiFont.bmiHeader);
        bmiFont.bmiHeader.biWidth         = 256*8;
        bmiFont.bmiHeader.biHeight        = 8;
        bmiFont.bmiHeader.biPlanes        = 1;
        bmiFont.bmiHeader.biBitCount      = 1;
        bmiFont.bmiHeader.biCompression   = BI_RGB;
        //  bmiFont.bmiHeader.biSizeImage     = 0; //sizeof(abFontImage)
        //  bmiFont.bmiHeader.biXPelsPerMeter = 0;
        //  bmiFont.bmiHeader.biYPelsPerMeter = 0;
        //  bmiFont.bmiHeader.biClrUsed       = 0;
        //  bmiFont.bmiHeader.biClrImportant  = 0;
        bmiFont.bmiColors[0].rgbBlue     = 0xFF;
        bmiFont.bmiColors[0].rgbGreen    = 0xFF;
        bmiFont.bmiColors[0].rgbRed      = 0xFF;
        bmiFont.bmiColors[0].rgbReserved = 0x00;
        bmiFont.bmiColors[1].rgbBlue     = 0x00;
        bmiFont.bmiColors[1].rgbGreen    = 0x00;
        bmiFont.bmiColors[1].rgbRed      = 0x00;
        bmiFont.bmiColors[1].rgbReserved = 0x00;
    } // endif lpCharacters

    ZeroMemory( &bmiGrph, sizeof(bmiGrph) );
    bmiGrph.bmiHeader.biSize         = sizeof(bmiGrph.bmiHeader);
    bmiGrph.bmiHeader.biWidth        = 1;
    bmiGrph.bmiHeader.biHeight       = 8;
    bmiGrph.bmiHeader.biPlanes       = 1;
    bmiGrph.bmiHeader.biBitCount     = 1;
    bmiGrph.bmiHeader.biCompression  = BI_RGB;
    bmiGrph.bmiColors[0].rgbBlue     = 0xFF;
    bmiGrph.bmiColors[0].rgbGreen    = 0xFF;
    bmiGrph.bmiColors[0].rgbRed      = 0xFF;
    bmiGrph.bmiColors[0].rgbReserved = 0x00;
    bmiGrph.bmiColors[1].rgbBlue     = 0x00;
    bmiGrph.bmiColors[1].rgbGreen    = 0x00;
    bmiGrph.bmiColors[1].rgbRed      = 0x00;
    bmiGrph.bmiColors[1].rgbReserved = 0x00;
}

void EnsurePrintPage(void)
{
    DOCINFO di;
    TCHAR   szDocName[MAX_PATH];

    if (!fPrintDataOnPage) {
        if (hdcPrinter) {
            char originalDir[MAX_PATH];

            ZeroMemory( &di, sizeof(di) );
            di.cbSize = sizeof(di);
            di.lpszDocName = szDocName;

            wsprintf( szDocName, TEXT("%s (%lu)"),
                szDocTitle, ulPrintPage );

            // We need to restore the current directory after
            // StartDoc is called in case we use a virtual
            // printer that writes to file and open a dialog
            // box. Also set current dir to the dir of last
            // access to this method before calling StartPage

            GetCurrentDirectory(MAX_PATH - 1, originalDir);
            if (*printDir) {
                SetCurrentDirectory(printDir);
            }
            StartDoc( hdcPrinter, &di );
            StartPage( hdcPrinter );
            
            GetCurrentDirectory(MAX_PATH - 1, printDir);
            SetCurrentDirectory(originalDir);
        }

        fPrintDataOnPage=TRUE;
    }
}

void PrintVisibleCharacter(BYTE bChar)
{
    EnsurePrintPage();

    if (hdcPrinter)
    {
        double iYPos = 0;
        double iHeight = stPrtRam.uiPixelSizeY;

        if (stPrtRam.fSubscript)
        {
            iHeight /= 2;
            iYPos = iHeight;
        }
        else if (stPrtRam.fSuperscript)
        {
            iHeight /= 2;
        }
        
#ifdef USE_REAL_FONT
        TextOut(hdcPrinter, 
                (UINT)(stPrtRam.uiHpos * stPrtRam.uiPixelSizeX), stPrtRam.uiVpos * stPrtRam.uiPixelSizeY + iYPos,
                &bChar, 1);
#else
        // Print character
        StretchDIBits( hdcPrinter,
            (UINT)(stPrtRam.uiHpos*stPrtRam.uiPixelSizeX), 
            (UINT)(stPrtRam.uiVpos*stPrtRam.uiPixelSizeY+iYPos),
            (UINT)(stPrtRam.uiPixelSizeX*stPrtRam.uiFontWidth), (UINT)(iHeight*8),
            8*(int)bChar, 0, stPrtRam.uiFontWidth, 8,
            abFontImage, (LPBITMAPINFO)&bmiFont,
            DIB_RGB_COLORS, SRCAND );
#endif
        // Move print-position...
        SeekPrinterHeadRelative(stPrtRam.uiFontWidth);
    }
}

void PrintGraphicByte(BYTE bByte, BOOL fMsxPrinter)
{
    int  iPixel;
    BYTE bMask;

    EnsurePrintPage();

    if (hdcPrinter)
    {
        ZeroMemory( abGrphImage, sizeof(abGrphImage) );

        if (fMsxPrinter)
            bMask = 0x80;
        else
            bMask = 0x01;

        for (iPixel=0; iPixel<8; iPixel++)
        {
            if (bByte & bMask)
                abGrphImage[iPixel<<2] = 0x80;

            if (fMsxPrinter)
                bMask >>= 1;
            else
                bMask <<= 1;
        }

        // Print bit-mask
        StretchDIBits(hdcPrinter,
            (UINT)(stPrtRam.uiHpos*stPrtRam.uiPixelSizeX), 
            (UINT)(stPrtRam.uiVpos*stPrtRam.uiPixelSizeY),
            (UINT)(stPrtRam.uiPixelSizeX), (UINT)(stPrtRam.uiPixelSizeY*8),
            0, 0, 1, 8,
            abGrphImage, (LPBITMAPINFO)&bmiGrph,
            DIB_RGB_COLORS, SRCAND );

        // Move print-position...
        SeekPrinterHeadRelative(100./stPrtRam.uiDensity);
    }

    return;
}

////////////////////////////////////////////////////
// MSX Printer specific methods
////////////////////////////////////////////////////

static void MsxPrnResetSettings(void)
{
    stPrtRam.uiLineFeed     = 11;
    stPrtRam.uiLeftBorder   = 48;
    stPrtRam.uiRightBorder  = 800;
    stPrtRam.uiDensity      = 100;
    stPrtRam.uiPageTop      = 48;
    stPrtRam.uiLines        = 72;
    stPrtRam.uiTotalWidth   = 825;
    stPrtRam.uiTotalHeight  = 825;
    stPrtRam.uiFontWidth    = 8;
    stPrtRam.fGraphicsHiLo  = TRUE;
}

static UINT MsxPrnParseNumber(size_t sizeStart, size_t sizeChars)
{
    UINT uiValue = 0;
    BYTE bChar;

    while (sizeChars--) {
        uiValue=uiValue*10;
        bChar=stPrtRam.abEscSeq[sizeStart++];
        if (bChar>='0' && bChar<='9')
            uiValue+=(UINT)(bChar-'0');
    }

    return uiValue;
}

static size_t MsxPrnCalcEscSequenceLength(BYTE character) 
{
    switch (character) {
    case 'A':
    case 'C':
        return 1;
    case 'T':
    case 'Z':
        return 2;
    case 'O':
    case '\\':
    case 'L':
        return 3;
    case 'S':
        return 4;
    case 'G':
        return 7;
    }

    return 0;
}

static void MsxPrnProcessEscSequence(void)
{
    switch (stPrtRam.abEscSeq[0]) {
    case 13:
        // (ESC, CR) Move printer-head to end-position
        break;

    case '!':
        stPrtRam.fLetterQuality=TRUE;
        break;

    case '&':
    case '$':
        stPrtRam.fJapanese=!stPrtRam.fJapanese;
        break;

    case '(':
        // ???: Set a horizontal tab position
        break;

    case ')':
        // ???: Partially delete a horizontal tab position
        break;

    case '\"':
        stPrtRam.fLetterQuality=FALSE;
        break;

    case '\\':
        stPrtRam.uiRightBorder=MsxPrnParseNumber( 1, 3 );
        break;

    case '@':
        ResetEmulatedPrinter();
        break;

    case 'A':
      // ???: Line-feed 1/6"
        stPrtRam.uiLineFeed=12;
        break;

    case 'B':
        // ???: Line-feed 1/9"
        stPrtRam.uiLineFeed=8;
        break;

    case 'C':
        switch (stPrtRam.abEscSeq[1])
        {
        case 'D':
            stPrtRam.fDoubleStrike=TRUE;
            break;

        case 'd':
            stPrtRam.fDoubleStrike=FALSE;
            break;

        case 'I':
            stPrtRam.fItalic=TRUE;
            break;

        case 'i':
            stPrtRam.fItalic=FALSE;
            break;

        case 'S':
            stPrtRam.fSuperscript=TRUE;
            break;

        case 's':
            stPrtRam.fSuperscript=FALSE;
            break;

        case 'U':
            stPrtRam.fSubscript=TRUE;
            break;

        case 'u':
            stPrtRam.fSubscript=FALSE;
            break;
        }
        UpdateFont();
        break;

    case 'E':
        stPrtRam.iFont=PRTFONT_ELITE;
        UpdateFont();
        break;

    case 'G':
        stPrtRam.uiDensity=MsxPrnParseNumber( 1, 3 );
        if (stPrtRam.uiDensity == 0) {
            stPrtRam.uiDensity = 1;
        }
        stPrtRam.sizeRemainingDataBytes=MsxPrnParseNumber( 4, 4 );
        break;

    case 'L':
        stPrtRam.uiLeftBorder=MsxPrnParseNumber( 1, 3 );
        break;

    case 'N':
        stPrtRam.iFont=PRTFONT_PICA;
        UpdateFont();
        break;

    case 'O':
        switch (stPrtRam.abEscSeq[1])
        {
        case 'S':
            stPrtRam.uiPerforationSkip=MsxPrnParseNumber( 2, 2 );
            break;

        case 'I':
            // ???: Set page-height(inches)
            break;

        default:
            // ???: Set page-height (lines)
            break;
        }
        break;

    case 'Q':
        stPrtRam.iFont=PRTFONT_CONDENSED;
        UpdateFont();
        break;

    case 'S':
        // Print graphics, density depending on font
        stPrtRam.sizeRemainingDataBytes=MsxPrnParseNumber( 1, 3 );
        break;

    case 'T':
        // ???: Line-feed nn/144"
        stPrtRam.uiLineFeed=(UINT)(MsxPrnParseNumber( 1, 2 )/4.875);
        break;

    case 'X':
        stPrtRam.fUnderline=TRUE;
        break;

    case 'Y':
        stPrtRam.fUnderline=FALSE;
        break;

    case 'Z':
        // ???: Line-feed nn/216"
        stPrtRam.uiLineFeed=(UINT)(MsxPrnParseNumber( 1, 2 )/3.25);
        break;

    case '[':
        // ???: Uni-directional printing
        break;

    case ']':
        // ???: Bi-directional printing
        break;

    case 'f':
        // ???: Scroll paper forward
        break;

    case 'p':
        stPrtRam.fDetectPaperOut=TRUE;
        break;

    case 'q':
        stPrtRam.fDetectPaperOut=FALSE;
        break;

    case 'r':
        // ???: Scroll paper back
        break;
    }
}

static void MsxPrnProcessCharacter(BYTE bChar)
{
    if (stPrtRam.fAlternateChar)
    {
        // Print SOH-preceded character
        PrintVisibleCharacter( (BYTE)(bChar & 0x1F) );
        stPrtRam.fAlternateChar=FALSE;
    }
    else {
        switch (bChar) {
        case 1:                                 // SOH: A symbolcode preceding code
            stPrtRam.fAlternateChar=TRUE;
            break;

        case 7:                                 // BEL: Audible beep (buzzer, 0.3s)
            break;

        case 8:                                 // BS: Backstep (1 Character)
            // ToDo: fix for other font-sizes ***
            stPrtRam.uiHpos -= 8;
            if (stPrtRam.uiHpos < stPrtRam.uiLeftBorder)
                stPrtRam.uiHpos=stPrtRam.uiLeftBorder;
            break;

        case 9:                                 // HAT: Horizontal tabulator
            {
                // ToDo: fix for other font-sizes ***
                UINT            uiNewPos;
                uiNewPos = ((UINT)stPrtRam.uiHpos + 64
                    - stPrtRam.uiLeftBorder) & ~63;
                uiNewPos += stPrtRam.uiLeftBorder;

                if (uiNewPos >= stPrtRam.uiHpos)
                    break;
                // else fall thru: CR/LF
            }

        case 10:                                // LF: Carriage return + Line feed
        case 11:                                // VT: Vertical tabulator (like LF)
//            stPrtRam.uiHpos = stPrtRam.uiLeftBorder;
            stPrtRam.uiVpos += stPrtRam.uiLineFeed;
            if (stPrtRam.uiVpos >= stPrtRam.uiPageHeight)
                FlushEmulatedPrinter();
            break;

        case 12:                                // FF: Form feed
            EnsurePrintPage();
            FlushEmulatedPrinter();
            break;

        case 13:                                // CR: Carriage return
            stPrtRam.uiHpos = stPrtRam.uiLeftBorder;
            break;

        case 14:                                // SO: Double character-width on
            stPrtRam.fDoubleWidth=TRUE;
            break;

        case 15:                                // SI: Double character-width off
            stPrtRam.fDoubleWidth=FALSE;
            break;

        case 27:
            stPrtRam.fEscSequence=TRUE;
            break;

        default:
            if (bChar<0 || bChar>=32)
            {
                // Yes, we can print it!
                PrintVisibleCharacter( bChar );
            }
            break;
        }
    }
}

////////////////////////////////////////////////////
// Epson FX80 specific methods
////////////////////////////////////////////////////

static UINT EpsonFx80ParseNumber(size_t sizeStart, size_t sizeChars)
{
    UINT uiValue = 0;

    sizeStart += sizeChars;

    while (sizeChars--) {
        uiValue = uiValue * 256;
        uiValue += stPrtRam.abEscSeq[--sizeStart];
    }

    return uiValue;
}

static void EpsonFx80ResetSettings(void)
{
    stPrtRam.uiLineFeed     = 12;
    stPrtRam.uiLeftBorder   = 48;
    stPrtRam.uiRightBorder  = stPrtRam.uiLeftBorder + 480;
    stPrtRam.uiDensity      = 100;
    stPrtRam.uiPageTop      = 48;
    stPrtRam.uiLines        = 72;
    stPrtRam.uiTotalWidth   = 610;
    stPrtRam.uiTotalHeight  = 825;
    stPrtRam.uiFontWidth    = 6;
    stPrtRam.fGraphicsHiLo  = FALSE;
}

static size_t EpsonFx80CalcEscSequenceLength(BYTE character) 
{
    character &= 127;

    switch (character) {
    case '!':
    case '-':
    case '/':
    case '3':
    case 'A':
    case 'J':
    case 'N':
    case 'Q':
    case 'R':
    case 'S':
    case 'U':
    case 'W':
    case 'b':
    case 'i':
    case 'j':
    case 'l':
    case 'p':
    case 's':
        return 1;
    case '%':
    case '?':
    case 'K':
    case 'L':
    case 'Z':
    case '^':
        return 2;
    case '*':
    case ':':
        return 3;

    case '&': // Custom character set, variable length
        return 0;
    case 'B': // Set tabs, variable length (up to 16 tabs)
        return 0;
    case 'C': // Set form length, variable length (2 or 3)
        return 0;
    case 'D': // Set tabs, variable length (up to 32 tabs)
        return 0;
    }
    return 0;
}

static void EpsonFx80ProcessEscSequence(void)
{
    BYTE character = stPrtRam.abEscSeq[0] & 127;

    switch (character) {
    case '!':  // Master Print Mode Select
        break;

    case '#':  // Accept Eight Bit as-is
        break;

    case '%':  // Activates Character Set
        break;

    case '&': // Custom character set, variable length
        break;

    case '*':  // Turn Graphics Mode ON
        stPrtRam.fNinePinGraphics = FALSE;
        switch(EpsonFx80ParseNumber(1, 1)) {
        default:
        case 0:
            stPrtRam.uiDensity = 100;
            break;
        case 1:
        case 2:
            stPrtRam.uiDensity = 200;
            break;
        case 3:
            stPrtRam.uiDensity = 400;
            break;
        case 4:
            stPrtRam.uiDensity = 133;
            break;
        case 5:
            stPrtRam.uiDensity = 120;
            break;
        case 6:
            stPrtRam.uiDensity = 150;
            break;
        }
        stPrtRam.sizeRemainingDataBytes = EpsonFx80ParseNumber(2, 2);
        break;

    case '-':  // Turn Underline Mode ON/OFF
        stPrtRam.fUnderline = EpsonFx80ParseNumber(1, 1);
        break;

    case '/':  // Selects Vertical Tab Channel
        break;

    case '0':  // Sets Line Spacing to 1/8 inch
        stPrtRam.uiLineFeed = 9;
        break;

    case '1':  // Sets Line Spacing to 7/72 inch
        stPrtRam.uiLineFeed = 7;
        break;

    case '2':  // Sets Line Spacing to 1/6 inch
        stPrtRam.uiLineFeed = 12;
        break;

    case '3':  // Sets Line Spacing to n/216 inch
        stPrtRam.uiLineFeed = (EpsonFx80ParseNumber(1, 1) & 127) / 4; //FIXME!!
        break;

    case '4':  // Turn Italic Mode ON
        stPrtRam.fItalic = TRUE;
        break;

    case '5':  // Turn Italic Mode OFF
        stPrtRam.fItalic = FALSE;
        break;

    case '6':  // Turn Printing of International Italic characters ON
        break;

    case '7':  // Turn Printing of International Italic characters OFF
        break;

    case '8':  // Turn Paper Out Sensor ON
        stPrtRam.fDetectPaperOut = TRUE;
        break;

    case '9':  // Turn Paper Out Sensor OFF
        stPrtRam.fDetectPaperOut = FALSE;
        break;

    case ':':  // Copies Rom Character set to RAM
        break;

    case '<':  // Turn Uni-directional printing ON (left to right)
        stPrtRam.fLeftToRight = TRUE;
        break;

    case '=':  // Sets eight bit to 0
        stPrtRam.uiEightBit = 0;
        break;

    case '>':  // Sets eight bit to 1
        stPrtRam.uiEightBit = 1;
        break;

    case '?':  // Redefines Graphics Codes
        break;

    case '@':  // Reset
        FlushEmulatedPrinter();
        ResetEmulatedPrinter();
        break;

    case 'A':  // Sets Line Spacing to n/72 inch
        stPrtRam.uiLineFeed = EpsonFx80ParseNumber(1, 1) & 127;
        break;

    case 'B':  // Set tabs, variable length (up to 16 tabs)
        break;

    case 'C': // Set form length, variable length (2 or 3)
        break;

    case 'D': // Set tabs, variable length (up to 32 tabs)
        break;

    case 'E':  // Turn Emphasized Mode ON
        break;

    case 'F':  // Turn Emphasized Mode OFF
        break;

    case 'G':  // Turn Double Strike Mode ON
        break;

    case 'H':  // Turn Double Strike Mode OFF
        break;

    case 'I':  // Enables printing of chars 1-31
        break;

    case 'J':  // Forces Line Feed with n/216 inch
        stPrtRam.uiVpos += (EpsonFx80ParseNumber(1, 1) & 127) / 4; // FIXME!!
        if (stPrtRam.uiVpos >= stPrtRam.uiPageHeight)
            FlushEmulatedPrinter();
        break;

    case 'K':  // Turn Single Density Graphics on (480 dot mode)
        stPrtRam.uiDensity = 100;
        stPrtRam.fNinePinGraphics = FALSE;
        stPrtRam.sizeRemainingDataBytes = EpsonFx80ParseNumber(1, 2);
        break;

    case 'L':  // Turn Double Density Graphics on (960 dot mode)
        stPrtRam.uiDensity = 200;
        stPrtRam.fNinePinGraphics = FALSE;
        stPrtRam.sizeRemainingDataBytes = EpsonFx80ParseNumber(1, 2);
        break;

    case 'M':  // Turn Elite mode ON
        break;

    case 'N':  // Turn Skip Over Perforation ON
        break;

    case 'O':  // Turn Skip Over Perforation OFF
        break;

    case 'P':  // Turn Elite mode OFF
        break;

    case 'Q':  // Set Right Margin
        {
            int width = EpsonFx80ParseNumber(1, 2);
            if (width > 78) width = 78; // FIXME Font dependent !!
            stPrtRam.uiRightBorder = 6 * width;
        }
        break;

    case 'R':  // Select International Character Set
        break;

    case 'S':  // Turn Script Mode ON
        {
            int script = EpsonFx80ParseNumber(1, 1);
            stPrtRam.fSuperscript = script == 0;
            stPrtRam.fSubscript   = script == 1;
        }
        break;

    case 'T':  // Turn Script Mode OFF
        stPrtRam.fSubscript =   FALSE;
        stPrtRam.fSuperscript = FALSE;
        break;

    case 'U':  // Turn Uni-directional mode ON/OFF
        stPrtRam.fLeftToRight = EpsonFx80ParseNumber(1, 1);
        break;

    case 'W':  // Turn Expanded Mode ON/OFF
        break;

    case 'Y':  // Turn High Speed Double Density Graphics ON
        break;

    case 'Z':  // Turns Quadruple Density Graphics ON
        stPrtRam.uiDensity = 400;
        stPrtRam.fNinePinGraphics = FALSE;
        stPrtRam.sizeRemainingDataBytes = EpsonFx80ParseNumber(1, 2);
        break;

    case '^':  // Turn Nine Pin Graphics Mode ON
        stPrtRam.uiDensity = EpsonFx80ParseNumber(1, 1) ? 200 : 100;
        stPrtRam.fNinePinGraphics = TRUE;
        stPrtRam.sizeRemainingDataBytes = 2 * EpsonFx80ParseNumber(2, 2);
        break;

    case 'b':  // Set Vertical Tab
        break;

    case 'i':  // Turn Immediate Mode ON/OFF
        break;

    case 'j':  // Immediate Reverse Line Feed
        stPrtRam.uiVpos -= (EpsonFx80ParseNumber(1, 1) & 127) / 4; // FIXME!!
        if (stPrtRam.uiVpos < stPrtRam.uiPageTop)
            stPrtRam.uiVpos = stPrtRam.uiPageTop;
        break;

    case 'l':  // Set Left Margin
        break;

    case 'p':  // Turn Proportional Mode ON/OFF
        break;

    case 's':  // Set Print Speed
        break;

    case 127: // Deletes Last Character in Buffer
        break;
    }
}

static void EpsonFx80ProcessCharacter(BYTE bChar)
{
    switch (bChar) {
    case 0:  // Terminates horizontal and vertical TAB setting
        break;
    case 7:  // Sound beeper
        break;
    case 8:  // Backspace
        // ToDo: fix for other font-sizes ***
        stPrtRam.uiHpos -= 8;
        if (stPrtRam.uiHpos < stPrtRam.uiLeftBorder)
            stPrtRam.uiHpos=stPrtRam.uiLeftBorder;
        break;
    case 9:  // Horizontal TAB
        {
            // ToDo: fix for other font-sizes ***
            UINT            uiNewPos;
            uiNewPos = ((UINT)stPrtRam.uiHpos + 64 - stPrtRam.uiLeftBorder) & ~63;
            uiNewPos += stPrtRam.uiLeftBorder;

            if (uiNewPos >= stPrtRam.uiHpos)
                break;
            // else fall thru: CR/LF
        }
        break;
    case 10: // Line Feed
    case 11: // Vertical TAB
        stPrtRam.uiVpos += stPrtRam.uiLineFeed;
        if (stPrtRam.uiVpos >= stPrtRam.uiPageHeight)
            FlushEmulatedPrinter();
        break;
    case 12: // Form Feed
        EnsurePrintPage();
        FlushEmulatedPrinter();
        break;
    case 13: // Carrige return
        stPrtRam.uiHpos = stPrtRam.uiLeftBorder;
        break;
    case 14: // Turns expanded mode ON
        break;
    case 15: // Shift in. Emties buffer, turns compressed mode ON (17.16 cpi)
        stPrtRam.fDoubleWidth = TRUE;
        break;
    case 17: // Device Control 1: 
        break;
    case 18: // Device Control 2: turns compressed mode OFF
        stPrtRam.fDoubleWidth = FALSE;
        break;
    case 19: // Device Control 3: 
        break;
    case 20: // Device Control 4: Turns expanded mode OFF
        break;
    case 24: // Cancels all text in the print buffer
        break;
    case 27: // Escape
        stPrtRam.fEscSequence = TRUE;
        break;
    default:
        if (bChar >= 32) {
            PrintVisibleCharacter(bChar);
        }
        break;
    }
}

////////////////////////////////////////////////////
// Generic Character processing
////////////////////////////////////////////////////

static void ResetEmulatedPrinter(void)
{
    ZeroMemory(&stPrtRam, sizeof(stPrtRam));

    switch (printerType) {
    case P_LPT_MSXPRN:
        MsxPrnResetSettings();
        break;
    case P_LPT_EPSONFX80:
        EpsonFx80ResetSettings();
        break;
    }

    stPrtRam.uiPageHeight   = stPrtRam.uiPageTop + stPrtRam.uiLines * stPrtRam.uiLineFeed;
    stPrtRam.uiHpos         = stPrtRam.uiLeftBorder;
    stPrtRam.uiVpos         = stPrtRam.uiPageTop;

    fPrintDataOnPage = FALSE;

    if (hdcPrinter != NULL) {
        stPrtRam.uiPixelSizeX = GetDeviceCaps(hdcPrinter, PHYSICALWIDTH) / stPrtRam.uiTotalWidth;
        stPrtRam.uiPixelSizeY = GetDeviceCaps(hdcPrinter, PHYSICALHEIGHT) / stPrtRam.uiTotalHeight;
    }

    return;
}

static size_t CalcEscSequenceLength(BYTE character) 
{
    size_t rv = 0;

    switch (printerType) {
    case P_LPT_MSXPRN:
        rv = MsxPrnCalcEscSequenceLength( character );
        break;
    case P_LPT_EPSONFX80:
        rv = EpsonFx80CalcEscSequenceLength( character );
        break;
    }
    return rv;
}

static void ProcessCharacter(BYTE bChar)
{
    switch (printerType) {
    case P_LPT_MSXPRN:
        MsxPrnProcessCharacter( bChar );
        break;
    case P_LPT_EPSONFX80:
        EpsonFx80ProcessCharacter( bChar );
        break;
    }
}

static void ProcessEscSequence(void)
{
    switch (printerType) {
    case P_LPT_MSXPRN:
        MsxPrnProcessEscSequence();
        break;
    case P_LPT_EPSONFX80:
        EpsonFx80ProcessEscSequence();
        break;
    }
}

void PrintToMSX(BYTE bData)
{
    if (stPrtRam.sizeRemainingDataBytes) {
        PrintGraphicByte( bData, stPrtRam.fGraphicsHiLo );
        stPrtRam.sizeRemainingDataBytes--;
    }
    else if (stPrtRam.fEscSequence) {
        stPrtRam.fEscSequence=FALSE;

        memset( &(stPrtRam.abEscSeq), 0, sizeof(stPrtRam.abEscSeq) );
        *(stPrtRam.abEscSeq)=bData;
        stPrtRam.sizeEscPos=1;

        stPrtRam.uiRemainingCommandBytes=CalcEscSequenceLength(bData);

        if (!stPrtRam.uiRemainingCommandBytes) {
            ProcessEscSequence();
        }
    }
    else if (stPrtRam.uiRemainingCommandBytes) {
        stPrtRam.abEscSeq[stPrtRam.sizeEscPos++]=bData;

        if (!--stPrtRam.uiRemainingCommandBytes) {
            ProcessEscSequence();
        }
    }
    else {
        ProcessCharacter( bData );
    }
}

static int printerCreate(void)
{
    Properties* pProperties = propGetGlobalProperties();

    SetPrintTitle("blueMSX");

    SetPrinterFont(FontBitmaps, sizeof(FontBitmaps));

    hdcPrinter = CreateDC(NULL, TEXT(pProperties->ports.Lpt.name), NULL, NULL);

    SetBkMode(hdcPrinter, TRANSPARENT);

    UpdateFont();

    ResetEmulatedPrinter();

    return hdcPrinter != NULL;
}

static void printerDestroy(void)
{
    if (hdcPrinter != NULL) {
        FlushEmulatedPrinter();
        ResetEmulatedPrinter();

        DeleteObject(SelectObject(hdcPrinter, GetStockObject(SYSTEM_FONT)));

        DeleteDC(hdcPrinter);
        hdcPrinter = NULL;
    }
}

static void printerWrite(BYTE value)
{
    if (hdcPrinter != NULL) {
        PrintToMSX(value);
    }
}

/////////////////////////////////////////////////////////////////////
/// Generic Printer methods
/////////////////////////////////////////////////////////////////////

void archPrinterWrite(BYTE value)
{
    if (printerType == P_LPT_RAW) {
        printerRawWrite(value);
    }
    else {
        printerWrite(value);
    }
}

int archPrinterCreate(void)
{
    Properties* pProperties = propGetGlobalProperties();
    printerType = pProperties->ports.Lpt.emulation;

    if (printerType == P_LPT_RAW) {
        return printerRawCreate();
    }
    else {
        return printerCreate();
    }
}

void archPrinterDestroy(void)
{
    if (printerType == P_LPT_RAW) {
        printerRawDestroy();
    }
    else {
        printerDestroy();
    }
}

void archForceFormFeed(void)
{
    if (printerType == P_LPT_RAW) {
    }
    else {
        FlushEmulatedPrinter();
    }
}
