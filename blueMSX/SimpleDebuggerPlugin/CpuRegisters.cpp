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
#include "CpuRegisters.h"
#include "Resource.h"
#include <stdio.h>

namespace {

const char regName[15][8] = {
    "AF ",
    "BC ",
    "DE ",
    "HL ",
    "AF'",
    "BC'",
    "DE'",
    "HL'",
    "IX ",
    "IY ",
    "SP ",
    "PC ",
    "I  ",
    "R  ",
    "IFF"
};

}

static CpuRegisters* cpuRegisters = NULL;

static LRESULT CALLBACK regsWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    return cpuRegisters->wndProc(hwnd, iMsg, wParam, lParam);
}

LRESULT CpuRegisters::wndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    HDC hdc;

    switch (iMsg) {
    case WM_CREATE:
        hdc = GetDC(hwnd);
        hMemdc = CreateCompatibleDC(hdc);
        ReleaseDC(hwnd, hdc);
        colorBlack = RGB(0, 0, 0);
        colorGray  = RGB(64, 64, 64);
        colorRed   = RGB(255, 0, 0);
        SetBkMode(hMemdc, TRANSPARENT);
        hFont = CreateFont(-MulDiv(10, GetDeviceCaps(hMemdc, LOGPIXELSY), 72), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New");
        hFontBold = CreateFont(-MulDiv(10, GetDeviceCaps(hMemdc, LOGPIXELSY), 72), 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New");

        hBrushWhite  = CreateSolidBrush(RGB(255, 255, 255));
        hBrushLtGray = CreateSolidBrush(RGB(239, 237, 222));
        hBrushDkGray = CreateSolidBrush(RGB(128, 128, 128));

        SelectObject(hMemdc, hFont); 
        TEXTMETRIC tm;
        if (GetTextMetrics(hMemdc, &tm)) {
            textHeight = tm.tmHeight;
            textWidth = tm.tmMaxCharWidth;
        }
        return 0;

    case WM_ERASEBKGND:
        return 1;

    case WM_LBUTTONDOWN:
        SetFocus(hwnd);
        return 0;

    case WM_SIZE:
        updateScroll();
        break;

    case WM_VSCROLL:
        scrollWindow(LOWORD(wParam));
         return 0;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            RECT r;
            GetClientRect(hwnd, &r);
            int top    = ps.rcPaint.top;
            int height = ps.rcPaint.bottom - ps.rcPaint.top;

            HBITMAP hBitmap = CreateCompatibleBitmap(GetWindowDC(NULL), r.right, r.bottom);
            HBITMAP hBitmapOrig = (HBITMAP)SelectObject(hMemdc, hBitmap);
            
            SelectObject(hMemdc, hBrushWhite); 
            PatBlt(hMemdc, 0, top, r.right, height, PATCOPY);

            drawText(ps.rcPaint.top, ps.rcPaint.bottom);

            BitBlt(hdc, 0, top, r.right, height, hMemdc, 0, top, SRCCOPY);

            DeleteObject(SelectObject(hMemdc, hBitmapOrig));
            EndPaint(hwnd, &ps);
        }
        return TRUE;

    case WM_DESTROY:
        DeleteObject(hBrushWhite);
        DeleteObject(hBrushLtGray);
        DeleteObject(hBrushDkGray);
        DeleteDC(hMemdc);
        break;
    }

    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}


CpuRegisters::CpuRegisters(HINSTANCE hInstance, HWND owner) : 
    lineCount(0)
{
    cpuRegisters = this;

    static WNDCLASSEX wndClass;

    wndClass.cbSize         = sizeof(wndClass);
    wndClass.style          = CS_VREDRAW;
    wndClass.lpfnWndProc    = regsWndProc;
    wndClass.cbClsExtra     = 0;
    wndClass.cbWndExtra     = 0;
    wndClass.hInstance      = hInstance;
    wndClass.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BLUEMSX));
    wndClass.hIconSm        = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BLUEMSX));
    wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground  = NULL;
    wndClass.lpszMenuName   = NULL;
    wndClass.lpszClassName  = "msxregs";

    RegisterClassEx(&wndClass);

    for (int i = 0; i < 15; i++) {
        regValue[i] = -1;
    }

    hwnd = CreateWindowEx(WS_EX_TOOLWINDOW, "msxregs", "CPU Registers", 
                          WS_OVERLAPPED | WS_CLIPSIBLINGS | WS_CHILD | WS_BORDER | WS_THICKFRAME | WS_DLGFRAME, 
                          CW_USEDEFAULT, CW_USEDEFAULT, 100, 100, owner, NULL, hInstance, NULL);
    invalidateContent();
}

CpuRegisters::~CpuRegisters()
{
}

void CpuRegisters::show()
{
    ShowWindow(hwnd, true);
}

void CpuRegisters::hide()
{
    ShowWindow(hwnd, false);
}

void CpuRegisters::updatePosition(RECT& rect)
{
    SetWindowPos(hwnd, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
}

void CpuRegisters::invalidateContent()
{
    for (int i = 0; i < 15; i++) {
        regModified[i] = 0;
        regValue[i] = -1;
    }
    
    InvalidateRect(hwnd, NULL, TRUE);
}

void CpuRegisters::updateContent(RegisterBank* regBank)
{
    for (int i = 0; i < 15; i++) {
        int val = regBank->reg[i].value;
        regModified[i] = regValue[i] != val;
        regValue[i] = val;
    }
    
    InvalidateRect(hwnd, NULL, TRUE);
}

void CpuRegisters::updateScroll() 
{
    RECT r;
    GetClientRect(hwnd, &r);
    int visibleLines = r.bottom / textHeight;

    r.right -= 10 + 8 * textWidth;
 
    registersPerRow = 1;

    while (r.right > 11 * textWidth) {
        registersPerRow++;
        r.right -= 11 * textWidth;
    }

    lineCount = (14 + registersPerRow) / registersPerRow;

    SCROLLINFO si;
    si.cbSize    = sizeof(SCROLLINFO);
    
    GetScrollInfo(hwnd, SB_VERT, &si);
    int oldFirstLine = si.nPos;

    si.fMask     = SIF_PAGE | SIF_POS | SIF_RANGE;
    si.nMin      = 0;
    si.nMax      = lineCount;
    si.nPage     = visibleLines;
    si.nPos      = 0;

    SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
    
    InvalidateRect(hwnd, NULL, TRUE);
}

void CpuRegisters::scrollWindow(int sbAction)
{
    int yPos;
    SCROLLINFO si;

    si.cbSize = sizeof (si);
    si.fMask  = SIF_ALL;
    GetScrollInfo (hwnd, SB_VERT, &si);
    yPos = si.nPos;
    switch (sbAction) {
    case SB_TOP:
        si.nPos = si.nMin;
        break;
    case SB_BOTTOM:
        si.nPos = si.nMax;
        break;
    case SB_LINEUP:
        si.nPos -= 1;
        break;
    case SB_LINEDOWN:
        si.nPos += 1;
        break;
    case SB_PAGEUP:
        si.nPos -= si.nPage;
        break;
    case SB_PAGEDOWN:
        si.nPos += si.nPage;
        break;
    case SB_THUMBTRACK:
        si.nPos = si.nTrackPos;
        break;              
    default:
        break; 
    }

    si.fMask = SIF_POS;
    SetScrollInfo (hwnd, SB_VERT, &si, TRUE);
    GetScrollInfo (hwnd, SB_VERT, &si);
    if (si.nPos != yPos) {                    
        ScrollWindow(hwnd, 0, textHeight * (yPos - si.nPos), NULL, NULL);
        UpdateWindow (hwnd);
    }
}

void CpuRegisters::drawText(int top, int bottom)
{
    SCROLLINFO si;

    si.cbSize = sizeof (si);
    si.fMask  = SIF_POS;
    GetScrollInfo (hwnd, SB_VERT, &si);
    int yPos = si.nPos;
    int FirstLine = max (0, yPos + top / textHeight);
    int LastLine = min (lineCount - 1, yPos + bottom / textHeight);

    for (int i = FirstLine; i <= LastLine; i++) {
        RECT r = { 10, textHeight * (i - yPos), 100, textHeight * (i + 1 - yPos) };
        for (int j = 0; j < registersPerRow; j++) {
            int reg = j * lineCount + i; //i * registersPerRow + j;

            if (reg >= 15) {
                continue;
            }

            SetTextColor(hMemdc, colorBlack);
            SelectObject(hMemdc, hFontBold); 
            DrawText(hMemdc, regName[reg], strlen(regName[reg]), &r, DT_LEFT);
            SelectObject(hMemdc, hFont); 
            r.left  += 4 * textWidth;
            r.right += 4 * textWidth;
            
            char text[5];
            if (regValue[reg] < 0) {
                SetTextColor(hMemdc, colorGray);
                sprintf(text, "???");
            }
            else {
                SetTextColor(hMemdc, regModified[reg] ? colorRed : colorGray);
                if (reg < 12) {
                    sprintf(text, "%.4X", regValue[reg]);
                }
                else {
                    sprintf(text, "%.2X", regValue[reg]);
                }
            }
            DrawText(hMemdc, text, strlen(text), &r, DT_LEFT);
            r.left  += 6 * textWidth;
            r.right += 6 * textWidth;
        }
    }
}
