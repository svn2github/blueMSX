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
#include "Memory.h"
#include "Resource.h"
#include <stdio.h>
#include <string>


static Memory* memory = NULL;

static LRESULT CALLBACK memoryWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    return memory->wndProc(hwnd, iMsg, wParam, lParam);
}

static LRESULT CALLBACK memViewWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    return memory->memWndProc(hwnd, iMsg, wParam, lParam);
}

static BOOL CALLBACK wndToolProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    return memory->toolDlgProc(hwnd, iMsg, wParam, lParam);
}

void Memory::updateDropdown()
{
    while (CB_ERR != SendDlgItemMessage(toolHwnd, IDC_MEMORY, CB_DELETESTRING, 0, 0));

    int index = 0;
    MemList::iterator it;
    for (it = memList.begin(); it != memList.end(); ++it) {
        MemoryItem* mi = *it;
        SendDlgItemMessage(toolHwnd, IDC_MEMORY, CB_ADDSTRING, 0, (LPARAM)mi->title.c_str());
        if (index == 0 || (currentMemory && currentMemory->title == mi->title)) {
            SendDlgItemMessage(toolHwnd, IDC_MEMORY, CB_SETCURSEL, index, 0);
        }
    }
}

void Memory::setNewMemory(const std::string& title)
{
    MemList::iterator it;
    for (it = memList.begin(); it != memList.end(); ++it) {
        MemoryItem* mi = *it;
        if (mi->title == title) {
            currentMemory = mi;
            updateScroll();
            InvalidateRect(memHwnd, NULL, TRUE);
            return;
        }
    }
}

BOOL Memory::toolDlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (iMsg) {
    case WM_INITDIALOG:
        addressInput = new HexInputDialog(hwnd, 300,3,75,22,6);
        return FALSE;

    case WM_LBUTTONDOWN:
        SetFocus(hwnd);
        return 0;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_MEMORY:
            if (HIWORD(wParam) == CBN_SELCHANGE) {
                char buffer[128];
                int idx = SendDlgItemMessage(hwnd, IDC_MEMORY, CB_GETCURSEL, 0, 0);
                int rv = SendDlgItemMessage(hwnd, IDC_MEMORY, CB_GETLBTEXT, idx, (LPARAM)buffer);
                if (rv != CB_ERR) {
                    setNewMemory(buffer);
                }
            }
            break;
        }
        return TRUE;

    case WM_CLOSE:
        delete addressInput;
        return FALSE;

    case HexInputDialog::EC_NEWVALUE:
        if (addressInput == (HexInputDialog*)wParam) {
            showAddress(lParam);
        }
        return FALSE;
    }
    return FALSE;
}

void Memory::updateWindowPositions()
{
    RECT r;
    GetWindowRect(toolHwnd, &r);
    int toolHeight = toolHwnd ? r.bottom - r.top : 0;
    GetClientRect(hwnd, &r);
    SetWindowPos(toolHwnd, NULL, 0, 0, r.right - r.left, toolHeight, SWP_NOZORDER);

    SetWindowPos(memHwnd, NULL, 0, toolHeight, r.right - r.left, r.bottom - r.top - toolHeight, SWP_NOZORDER);
}

LRESULT Memory::wndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (iMsg) {
    case WM_CREATE:
        return 0;

    case WM_LBUTTONDOWN:
        SetFocus(hwnd);
        return 0;

    case WM_SIZE:
        updateWindowPositions();
        break;

    case WM_DESTROY:
        DeleteObject(hBrushWhite);
        DeleteObject(hBrushLtGray);
        DeleteObject(hBrushDkGray);
        DeleteDC(hMemdc);
        break;
    }

    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

LRESULT Memory::memWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    HDC hdc;

    switch (iMsg) {
    case WM_CREATE:
        hdc = GetDC(hwnd);
        hMemdc = CreateCompatibleDC(hdc);
        ReleaseDC(hwnd, hdc);
        colorBlack = RGB(0, 0, 0);
        colorGray  = RGB(128, 128, 128);
        colorRed   = RGB(255, 0, 0);
        SetBkMode(hMemdc, TRANSPARENT);
        hFont = CreateFont(-MulDiv(10, GetDeviceCaps(hMemdc, LOGPIXELSY), 72), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New");

        hBrushWhite  = CreateSolidBrush(RGB(255, 255, 255));
        hBrushLtGray = CreateSolidBrush(RGB(239, 237, 222));
        hBrushDkGray = CreateSolidBrush(RGB(128, 128, 128));

        SelectObject(hMemdc, hFont); 
        TEXTMETRIC tm;
        if (GetTextMetrics(hMemdc, &tm)) {
            textHeight = tm.tmHeight;
            textWidth = tm.tmMaxCharWidth;
        }
        
        dataInput1 = new HexInputDialog(hwnd, -100,0,23,22,1);
        dataInput2 = new HexInputDialog(hwnd, -100,0,23,22,2);
        dataInput1->hide();
        dataInput2->hide();
        return 0;

    case WM_LBUTTONDOWN:
        {
            SetFocus(hwnd);
            if (currentMemory == NULL || !editEnabled) {
                return 0;
            }

            SCROLLINFO si;

            si.cbSize = sizeof (si);
            si.fMask  = SIF_POS;
            GetScrollInfo (memHwnd, SB_VERT, &si);

            int x = (LOWORD(lParam) - 10) / textWidth - 8;
            int col;
            int row = HIWORD(lParam) / textHeight;

            if (x >= 0 && x < 3 * memPerRow && x % 3 != 2) {
                col = x / 3;
                int addr = (row + si.nPos) * memPerRow + col;
                if (addr < currentMemory->size) {
                    currentEditAddress = addr;
                    dataInput2->setPosition(10 + (3 * col + 8) * textWidth, row * textHeight - 2);
                    dataInput2->setValue(currentMemory->memory[addr]);
                    dataInput2->show();
                }
            }
        }
        return 0;

    case HexInputDialog::EC_KILLFOCUS:
    case HexInputDialog::EC_NEWVALUE:
        if (currentMemory != 0 && currentEditAddress >= 0 && currentEditAddress < currentMemory->size) {
            UInt8 value = (UInt8)lParam;
            bool success = false;
            if (currentMemory->memory[currentEditAddress] != value) {
                success = DeviceWriteMemoryBlockMemory(currentMemory->memBlock, &value, currentEditAddress, 1);
            }
            if (success) {
                currentMemory->memory[currentEditAddress] = value;
            }
            InvalidateRect(memHwnd, NULL, TRUE);
        }
        currentEditAddress = -1;
        dataInput1->hide();
        dataInput2->hide();
        return FALSE;

    case WM_ERASEBKGND:
        return 1;

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
        delete dataInput1;
        delete dataInput2;
        DeleteDC(hMemdc);
        break;
    }

    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

Memory::Memory(HINSTANCE hInstance, HWND owner) : 
    lineCount(0), currentAddress(0), currentMemory(NULL), currentEditAddress(-1), editEnabled(false)
{
    memory = this;

    static WNDCLASSEX wndClass;

    wndClass.cbSize         = sizeof(wndClass);
    wndClass.style          = CS_VREDRAW;
    wndClass.lpfnWndProc    = memoryWndProc;
    wndClass.cbClsExtra     = 0;
    wndClass.cbWndExtra     = 0;
    wndClass.hInstance      = hInstance;
    wndClass.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BLUEMSX));
    wndClass.hIconSm        = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BLUEMSX));
    wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground  = NULL;
    wndClass.lpszMenuName   = NULL;
    wndClass.lpszClassName  = "msxmemory";

    RegisterClassEx(&wndClass);

    wndClass.lpfnWndProc    = memViewWndProc;
    wndClass.lpszClassName  = "msxmemoryview";
    wndClass.style          = 0;
    wndClass.lpszMenuName   = NULL;

    RegisterClassEx(&wndClass);

    hwnd = CreateWindowEx(WS_EX_TOOLWINDOW, "msxmemory", "Memory", 
                          WS_OVERLAPPED | WS_CLIPSIBLINGS | WS_CHILD | WS_BORDER | WS_THICKFRAME | WS_DLGFRAME, 
                          CW_USEDEFAULT, CW_USEDEFAULT, 100, 100, owner, NULL, hInstance, NULL);

    memHwnd = CreateWindow("msxmemoryview", "", 
                             WS_OVERLAPPED | WS_CLIPSIBLINGS | WS_CHILD, 
                             CW_USEDEFAULT, CW_USEDEFAULT, 100, 100, hwnd, NULL, hInstance, NULL);

    toolHwnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MEMORYTOOLBAR), hwnd, wndToolProc);

    ShowWindow(memHwnd, TRUE);
    ShowWindow(toolHwnd, TRUE);

    updateWindowPositions();
    invalidateContent();
}

Memory::~Memory()
{
}

void Memory::show()
{
    ShowWindow(hwnd, true);
}

void Memory::hide()
{
    ShowWindow(hwnd, false);
}

void Memory::enableEdit()
{
    editEnabled = true;
}

void Memory::disableEdit()
{
    editEnabled = false;
    dataInput1->hide();
    dataInput2->hide();
}

void Memory::updatePosition(RECT& rect)
{
    dataInput1->hide();
    dataInput2->hide();

    SetWindowPos(hwnd, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
}

void Memory::invalidateContent()
{
    dataInput1->hide();
    dataInput2->hide();

    MemList::iterator it;
    while(!memList.empty()) {
        delete memList.front();
        memList.pop_front();
    }

    currentMemory = NULL;
    updateScroll();

    updateDropdown();

    InvalidateRect(memHwnd, NULL, TRUE);
}

void Memory::updateContent(Snapshot* snapshot)
{
    dataInput1->hide();
    dataInput2->hide();

    bool devicesChanged = false;

    std::string currentMemoryTitle;

    if (currentMemory != NULL) {
        currentMemoryTitle = currentMemory->title;
    }

    MemList::iterator it;
    for (it = memList.begin(); it != memList.end(); ++it) {
        MemoryItem* mi = *it;
        memcpy(mi->ref, mi->memory, mi->size);
        mi->flag = false;
    }

    int deviceCount = SnapshotGetDeviceCount(snapshot);

    for (int i = 0; i < deviceCount; i++) {
        Device* device = SnapshotGetDevice(snapshot, i);
        int j;

        int memCount = DeviceGetMemoryBlockCount(device);

        for (j = 0; j < memCount; j++) {
            MemoryBlock* mem = DeviceGetMemoryBlock(device, j);

            char memName[64];

            sprintf(memName, "%d: %s - %s", device->deviceId, device->name, mem->name);

            for (it = memList.begin(); it != memList.end(); ++it) {
                MemoryItem* mi = *it;
                if (mi->title == memName && mi->size == mem->size) {
                    memcpy(mi->memory, mem->memory, mi->size);
                    mi->flag = true;
                    break;
                }
            }
            if (it == memList.end()) {
                memList.push_back(new MemoryItem(memName, mem));
                devicesChanged = true;
            }
        }
    }

    for (it = memList.begin(); it != memList.end(); ++it) {
        MemoryItem* mi = *it;
        if (!mi->flag) {
            devicesChanged = true;
            delete mi;
            it = memList.erase(it);
        }
    }

    for (it = memList.begin(); it != memList.end(); ++it) {
        MemoryItem* mi = *it;
        if (mi->title == currentMemoryTitle) {
            currentMemory = mi;
            break;
        }
    }

    if (currentMemory == NULL && memList.size() > 0) {
        currentMemory = memList.front();
        updateScroll();
    }

    if (devicesChanged) {
        updateDropdown();
    }

    InvalidateRect(memHwnd, NULL, TRUE);
}

void Memory::showAddress(int addr)
{
    RECT r;
    GetClientRect(memHwnd, &r);
    int visibleLines = r.bottom / textHeight;

    int memSize = currentMemory != NULL ? currentMemory->size : 0;

    int maxAddr = memSize - visibleLines * memPerRow;

    if (addr > maxAddr) {
        addr = maxAddr;
    }
    if (addr < 0) {
        addr = 0;
    }

    currentAddress = addr;
    updateScroll();
}

void Memory::updateScroll() 
{
    RECT r;
    GetClientRect(memHwnd, &r);
    int visibleLines = r.bottom / textHeight;

    r.right -= 20 + 13 * textWidth;
 
    memPerRow = 1;

    while (r.right > 4 * textWidth) {
        memPerRow++;
        r.right -= 4 * textWidth;
    }

    int memSize = currentMemory != NULL ? currentMemory->size : 0;
    lineCount = (memSize + memPerRow - 1) / memPerRow;

    SCROLLINFO si;
    si.cbSize    = sizeof(SCROLLINFO);
    
    GetScrollInfo(memHwnd, SB_VERT, &si);
    int oldFirstLine = si.nPos;

    si.fMask     = SIF_PAGE | SIF_POS | SIF_RANGE;
    si.nMin      = 0;
    si.nMax      = lineCount;
    si.nPage     = visibleLines;
    si.nPos      = currentAddress / memPerRow;

    SetScrollInfo(memHwnd, SB_VERT, &si, TRUE);
    
    InvalidateRect(memHwnd, NULL, TRUE);
}

void Memory::scrollWindow(int sbAction)
{
    SCROLLINFO si;

    si.cbSize = sizeof (si);
    si.fMask  = SIF_ALL;
    GetScrollInfo (memHwnd, SB_VERT, &si);
    int yPos = si.nPos;
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
    SetScrollInfo (memHwnd, SB_VERT, &si, TRUE);
    GetScrollInfo (memHwnd, SB_VERT, &si);
    if (si.nPos != yPos) {                    
        ScrollWindow(memHwnd, 0, textHeight * (yPos - si.nPos), NULL, NULL);
        UpdateWindow (memHwnd);
    }
}

void Memory::drawText(int top, int bottom)
{
    SCROLLINFO si;

    si.cbSize = sizeof (si);
    si.fMask  = SIF_POS;
    GetScrollInfo (memHwnd, SB_VERT, &si);
    int yPos = si.nPos;
    int FirstLine = max (0, yPos + top / textHeight);
    int LastLine = min (lineCount - 1, yPos + bottom / textHeight);

    if (currentMemory == NULL) {
        return;
    }
    int memSize = currentMemory != NULL ? currentMemory->size : 0;

    for (int i = FirstLine; i <= LastLine; i++) {
        RECT r = { 10, textHeight * (i - yPos), 100, textHeight * (i + 1 - yPos) };
        
        int addr = i * memPerRow;

        char addrText[16];
        sprintf(addrText, "%.6X", addr);

        SetTextColor(hMemdc, colorGray);
        DrawText(hMemdc, addrText, strlen(addrText), &r, DT_LEFT);

        r.left  += textWidth * 8;
        r.right += textWidth * 8;

        int j;
        for (j = 0; j < memPerRow; j++) {
            if (addr + j >= memSize) {
                continue;
            }
            
            UInt32 val = currentMemory->memory[addr + j];
            UInt32 ref = currentMemory->ref[addr + j];

            if (val == ref) {
                SetTextColor(hMemdc, colorBlack);
            }
            else {
                SetTextColor(hMemdc, colorRed);
            }
            
            sprintf(addrText, "%.2x", val);
            DrawText(hMemdc, addrText, strlen(addrText), &r, DT_LEFT);
            
            r.left  += textWidth * 3;
            r.right += textWidth * 3;
        }
        
        r.left  += textWidth * 1;
        r.right += textWidth * 1;

        for (j = 0; j < memPerRow; j++) {
            if (addr >= memSize) {
                continue;
            }
            
            UInt32 val = currentMemory->memory[addr + j];
            UInt32 ref = currentMemory->ref[addr + j];

            if (val == ref) {
                SetTextColor(hMemdc, colorBlack);
            }
            else {
                SetTextColor(hMemdc, colorRed);
            }

            sprintf(addrText, "%c", val);
            
            DrawText(hMemdc, addrText, strlen(addrText), &r, DT_LEFT);
            
            r.left  += textWidth * 1;
            r.right += textWidth * 1;
        }
    }
}
