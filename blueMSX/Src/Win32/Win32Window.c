/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Window.c,v $
**
** $Revision: 1.3 $
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
#include "MsxTypes.h"
#include "Win32Common.h"
#include "Win32File.h"
#include "Win32Keyboard.h"
#include "Theme.h"
#include "Machine.h"
#include "ArchNotifications.h"
#include "Language.h"
#include "Resource.h"

// Timer ID's
#define TIMER_STATUSBAR_UPDATE              10
#define TIMER_POLL_INPUT                    11
#define TIMER_THEME                         17
#define TIMER_CLIP_REGION                   19


// Custom Window Control Messages

#define WM_UPDATE                   (WM_USER + 1245)

#define WM_OBJECT_BASE              (WM_USER + 1300)

#define WM_DROPDOWN_KEYBOARDCONFIG  (WM_OBJECT_BASE + 31)
#define WM_DROPDOWN_THEMEPAGES      (WM_OBJECT_BASE + 32)
#define WM_DROPDOWN_MACHINECONFIG   (WM_OBJECT_BASE + 33)

#define WM_BUTTON_OK                (WM_OBJECT_BASE + 1)
#define WM_BUTTON_CANCEL            (WM_OBJECT_BASE + 2)
#define WM_BUTTON_SAVE              (WM_OBJECT_BASE + 3)
#define WM_BUTTON_SAVEAS            (WM_OBJECT_BASE + 4)
#define WM_BUTTON_CLOSE             (WM_OBJECT_BASE + 5)

#define WM_CLOSE_RESULT_OK      0xefdf0012
#define WM_CLOSE_RESULT_CANCEL  0xefdf0013

#define WM_OBJECT_CONTOL_BASE       (WM_USER + 1400)

#define WM_OBJECT_UPDATE            (WM_OBJECT_CONTOL_BASE + 1)
#define WM_OBJECT_SHOW              (WM_OBJECT_CONTOL_BASE + 2)
#define WM_OBJECT_ENABLE            (WM_OBJECT_CONTOL_BASE + 3)


static void objectShow(HWND parent, int notifyId, int show);
static void objectEnable(HWND parent, int notifyId, int enable);
static void objectUpdate(HWND parent, int notifyId, int arg);


//////////////////////////////////////////////////////////////////////////
// Methods to manage object window data
//
typedef struct {
    HWND  hwnd;
    int   id;
    void* data;
} WindowData;

#define WINDOW_DATA_NO 1024

WindowData windowData[WINDOW_DATA_NO];


//////////////////////////////////////////////////////////////////////////
/// Function:
///     windowDataSet
///
/// Description:
///     Associates a pointer with a windows handle. If the data pointer
///     is NULL, the association for the window handle is removed.
//////////////////////////////////////////////////////////////////////////
static void windowDataSet(HWND hwnd, int id, void* data)
{
    if (id != 0) {
        int i;
        for (i = 0; i < WINDOW_DATA_NO - 1; i++) {
            if (windowData[i].hwnd == hwnd || windowData[i].hwnd == NULL) {
                windowData[i].hwnd = hwnd;
                windowData[i].id   = id;
                windowData[i].data = data;
                return;
            }
        }
    }
    else {
        int i;
        for (i = 0; windowData[i].hwnd != NULL; i++) {
            if (windowData[i].hwnd == hwnd) {
                while (windowData[i + 1].hwnd != NULL) {
                    windowData[i] = windowData[i + 1];
                    i++;
                }
                return;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////
/// Function:
///     windowDataGet
///
/// Description:
///     Gets a pointer associated with a window handle. If no association
///     exist for the handle, NULL is returned.
//////////////////////////////////////////////////////////////////////////
static void* windowDataGet(HWND hwnd)
{
    int i;
    for (i = 0; windowData[i].hwnd != NULL; i++) {
        if (windowData[i].hwnd == hwnd) {
            return windowData[i].data;
        }
    }
    return NULL;
}


//////////////////////////////////////////////////////////////////////////
/// Struct:
///     WindowInfo
///
/// Description:
///     Contains window specific data
//////////////////////////////////////////////////////////////////////////
typedef struct WindowInfo {
    HWND hwnd;
    int  captionHeight;
    int  isMinimized;
    int  isMoving;
    Theme* theme;
    
    HBITMAP hBitmap;
    
    HRGN     hrgn;
    int      rgnSize;
    RGNDATA* rgnData;
    int      rgnEnable;
} WindowInfo;


//////////////////////////////////////////////////////////////////////////
/// Function:
///     windowSetClipRegion
///
/// Description:
///     Enables/disables the clip region for a window
//////////////////////////////////////////////////////////////////////////
static void windowSetClipRegion(WindowInfo* wi, int enable) 
{
    if (wi->rgnEnable == enable) {
        return;
    }
    if (!enable || wi->rgnData == NULL || wi->isMoving) {
        SetWindowRgn(wi->hwnd, NULL, TRUE);
        wi->rgnEnable = 0;
    }
    else {
        HRGN hrgn = ExtCreateRegion(NULL, wi->rgnSize, wi->rgnData);
        SetWindowRgn(wi->hwnd, hrgn, TRUE);
        wi->rgnEnable = 1;
    }
}


//////////////////////////////////////////////////////////////////////////
/// Function:
///     windowUpdateClipRegion
///
/// Description:
///     Updates the clip region
//////////////////////////////////////////////////////////////////////////
static void windowUpdateClipRegion(WindowInfo* wi) 
{
    if (wi->rgnData != NULL && wi->hrgn != NULL) {
        POINT pt;
        RECT r;

        GetCursorPos(&pt);
        GetWindowRect(wi->hwnd, &r);
        windowSetClipRegion(wi, !PtInRegion(wi->hrgn, pt.x - r.left, pt.y - r.top));
    }
}


//////////////////////////////////////////////////////////////////////////
/// Function:
///     windowCheckClipRegion
///
/// Description:
///     Checks the mouse position relative to the clip region and updates
///     the clip region timer if necessary
//////////////////////////////////////////////////////////////////////////
static void windowCheckClipRegion(WindowInfo* wi) 
{
    if (wi->rgnData != NULL && wi->hrgn != NULL) {
        POINT pt;
        RECT r;

        GetCursorPos(&pt);
        GetWindowRect(wi->hwnd, &r);
        if (wi->rgnEnable == !PtInRegion(wi->hrgn, pt.x - r.left, pt.y - r.top)) {
            SetTimer(wi->hwnd, TIMER_CLIP_REGION, 500, NULL);
        }
    }
}


//////////////////////////////////////////////////////////////////////////
/// Function:
///     windowCreateClipRegion
///
/// Description:
///     Creates a clip region for a window based on the theme config
//////////////////////////////////////////////////////////////////////////
static void windowCreateClipRegion(WindowInfo* wi)
{
    ThemePage* themePage = themeGetCurrentPage(wi->theme);

    if (themePage->clipPoint.count > 0) {
        int i;
        HRGN hrgn;
        POINT pt[512];
        int dx = GetSystemMetrics(SM_CXFIXEDFRAME);
        int dy = GetSystemMetrics(SM_CYFIXEDFRAME) + wi->captionHeight;

        for (i = 0; i < themePage->clipPoint.count; i++) {
            ClipPoint cp = themePage->clipPoint.list[i];
            pt[i].x = cp.x + dx;
            pt[i].y = cp.y + dy;
        }

        hrgn = CreatePolygonRgn(pt, themePage->clipPoint.count, WINDING);
        wi->rgnSize = 0;
        if (hrgn != NULL) {
            wi->rgnSize = GetRegionData(hrgn, 0, NULL);
            if (wi->rgnSize > 0) {
                wi->rgnData = malloc(wi->rgnSize);
                wi->rgnSize = GetRegionData(hrgn, wi->rgnSize, wi->rgnData);
                if (wi->rgnSize == 0) {
                    free(wi->rgnData);
                    wi->rgnData = NULL;
                }
            }
            if (wi->rgnSize == 0) {
                wi->rgnData = NULL;
            }
            else {
                int width  = themePage->width  + 2 * GetSystemMetrics(SM_CXFIXEDFRAME);
                int height = themePage->height + 2 * GetSystemMetrics(SM_CYFIXEDFRAME) + wi->captionHeight;

                wi->hrgn = CreateRectRgn(0, 0, width, height);
                CombineRgn(wi->hrgn, wi->hrgn, hrgn, RGN_XOR);
            }
            DeleteObject(hrgn);
        }
    }

    windowSetClipRegion(wi, themePage->clipPoint.count > 0);

    if (wi->rgnData == NULL) {
        KillTimer(wi->hwnd, TIMER_CLIP_REGION);
    }
    else {
        SetTimer(wi->hwnd, TIMER_CLIP_REGION, 500, NULL);
    }
}


//////////////////////////////////////////////////////////////////////////
/// Function:
///     keyboardDlgProc
///
/// Description:
///     Specialized window handler for keyboard configuration windows
//////////////////////////////////////////////////////////////////////////
static LRESULT CALLBACK keyboardDlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    WindowInfo* wi = windowDataGet(hwnd);

    switch (iMsg) {
    case WM_CREATE:
        keyboardStartConfig();
        objectUpdate(hwnd, WM_DROPDOWN_KEYBOARDCONFIG, (int)keyboardGetCurrentConfig());
        SetTimer(hwnd, TIMER_POLL_INPUT, 500, NULL);
        return 0;

    case WM_TIMER:
        switch(wParam) {
        case TIMER_POLL_INPUT:
            objectEnable(hwnd, WM_BUTTON_SAVE, keyboardConfigIsModified());
            break;
        }
        break;

    case WM_BUTTON_CLOSE:
        SendMessage(hwnd, WM_CLOSE, 0, 0);
        break;

    case WM_BUTTON_SAVE:
        if (keyboardConfigIsModified()) {
            if (IDYES == MessageBox(hwnd, langOverwriteConfig(), langWarningTitle(), MB_ICONWARNING | MB_YESNO)) {
                keyboardSaveConfig(keyboardGetCurrentConfig());
            }
        }
        break;

    case WM_BUTTON_SAVEAS:
        {
            char* name = openConfigFile(hwnd, langConfSaveAsTitle(), langConfSaveAsName(), keyboardGetConfigs(), keyboardGetCurrentConfig());
            if (name != NULL) {
                if (0 == strcmp(name, keyboardGetCurrentConfig())) {
                    if (IDYES == MessageBox(hwnd, langOverwriteConfig(), langWarningTitle(), MB_ICONWARNING | MB_YESNO)) {
                        keyboardSaveConfig(keyboardGetCurrentConfig());
                    }
                }
                else {
                    keyboardSaveConfig(name);
                    objectUpdate(hwnd, WM_DROPDOWN_KEYBOARDCONFIG, (int)keyboardGetCurrentConfig());
                }
            }
        }
        break;

    case WM_ACTIVATE:
        keybardEnableEdit(wParam != WA_INACTIVE);
        break;

    case WM_CLOSE:
        if (keyboardConfigIsModified()) {
            if (IDNO == MessageBox(hwnd, langDiscardChanges(), langWarningTitle(), MB_ICONWARNING | MB_YESNO)) {
                return WM_CLOSE_RESULT_CANCEL;
            }
        }
        KillTimer(hwnd, TIMER_POLL_INPUT);
        keyboardCancelConfig();
        keybardEnableEdit(0);
        return WM_CLOSE_RESULT_OK;
    }

    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}


//////////////////////////////////////////////////////////////////////////
/// Function:
///     windowProc
///
/// Description:
///     Generic window handler for a themed window
//////////////////////////////////////////////////////////////////////////
static LRESULT CALLBACK windowProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    WindowInfo* wi = windowDataGet(hwnd);
    LRESULT rv = 0;

    switch (iMsg) {
    case WM_CREATE:
        {
            ThemePage* themePage;
            CREATESTRUCT* cs = (CREATESTRUCT*)lParam;

            wi = (WindowInfo*)cs->lpCreateParams;
            windowDataSet(hwnd, 1, wi);

            wi->hwnd = hwnd;
            wi->captionHeight = GetSystemMetrics((GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_TOOLWINDOW) ? SM_CYSMCAPTION : SM_CYCAPTION);
            
            themePage = themeGetCurrentPage(wi->theme);
            SendMessage(hwnd, WM_UPDATE, 0, 0);

            ShowWindow(hwnd, TRUE); 
            
            SetTimer(hwnd, TIMER_STATUSBAR_UPDATE, 100, NULL);
        }
        break;

    case WM_DROPDOWN_THEMEPAGES:
        themeSetPageFromHash(wi->theme, themeGetNameHash((char*)lParam));
        SendMessage(hwnd, WM_UPDATE, 0, 0);
        return 0;

    case WM_CLOSE:
        // Special handling at the end
        break;

    case WM_ENTERSIZEMOVE:
        wi->isMoving = 1;
        break;

    case WM_EXITSIZEMOVE:
        wi->isMoving = 0;
        windowUpdateClipRegion(wi);
        break;

    case WM_TIMER:
        switch(wParam) {
        case TIMER_STATUSBAR_UPDATE:
            themePageUpdate(themeGetCurrentPage(wi->theme), GetDC(hwnd));
            break;
        case TIMER_CLIP_REGION:
            windowUpdateClipRegion(wi);
            break;
        case TIMER_THEME:
            if (!wi->isMinimized) {
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
                themePageMouseMove(themeGetCurrentPage(wi->theme), hdc, pt.x, pt.y);
                ReleaseDC(hwnd, hdc);
            }
            break;
        }
        break;

    case WM_UPDATE:
        {
            ThemePage* themePage = themeGetCurrentPage(wi->theme);
            int width;
            int height;

            width  = themePage->width  + 2 * GetSystemMetrics(SM_CXFIXEDFRAME);
            height = themePage->height + 2 * GetSystemMetrics(SM_CYFIXEDFRAME) + wi->captionHeight;
            
            if (wi->hBitmap) {
                DeleteObject(wi->hBitmap);
            }
            wi->hBitmap = CreateCompatibleBitmap(GetDC(hwnd), width, height);
            themePageActivate(themePage, NULL);

            SetWindowPos(hwnd, NULL, 0, 0, width, height, 
                         SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);

            themePageActivate(themePage, hwnd);
            windowCreateClipRegion(wi);

            InvalidateRect(hwnd, NULL, TRUE);
        }
        return 0;

    case WM_NCMOUSEMOVE:
        windowCheckClipRegion(wi);
        break;
        
    case WM_MOUSEMOVE:
        {
            ThemePage* themePage = themeGetCurrentPage(wi->theme);
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);
            themePageMouseMove(themePage, GetDC(hwnd), pt.x, pt.y);
            windowCheckClipRegion(wi);
        }
        SetTimer(hwnd, TIMER_THEME, 250, NULL);

        break;

    case WM_LBUTTONDOWN:
        {
            ThemePage* themePage = themeGetCurrentPage(wi->theme);
            POINT pt;
            SetCapture(hwnd);
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);
            themePageMouseButtonDown(themePage, GetDC(hwnd), pt.x, pt.y);
        }
        break;

    case WM_LBUTTONUP:
        {
            ThemePage* themePage = themeGetCurrentPage(wi->theme);
            POINT pt;
            
            ReleaseCapture();
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);
            themePageMouseButtonUp(themePage, GetDC(hwnd), pt.x, pt.y);
        }

    case WM_ERASEBKGND:
        return 1;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps); 
            HDC hMemDC = CreateCompatibleDC(hdc);
            HBITMAP hBitmap = (HBITMAP)SelectObject(hMemDC, wi->hBitmap);
            ThemePage* themePage = themeGetCurrentPage(wi->theme);
            
            themePageUpdate(themePage, hMemDC); //OWN DC
            themePageDraw(themePage, hMemDC);

            BitBlt(hdc, 0, 0, themePage->width, themePage->height, hMemDC, 0, 0, SRCCOPY);

            SelectObject(hMemDC, hBitmap);
            DeleteDC(hMemDC);                

            EndPaint(hwnd, &ps);
        }
        return 0;
    }

    if (wi && wi->theme->themeHandler == TH_KBDCONFIG) {
        rv = keyboardDlgProc(hwnd, iMsg, wParam, lParam);
    }
    else {
        rv = iMsg == WM_CLOSE ? 0 : DefWindowProc(hwnd, iMsg, wParam, lParam);
    }

    if (iMsg == WM_CLOSE) {
        if (rv != WM_CLOSE_RESULT_CANCEL) {
            KillTimer(hwnd, TIMER_STATUSBAR_UPDATE);
            windowDataSet(hwnd, 0, NULL);
            themePageActivate(themeGetCurrentPage(wi->theme), NULL);
            wi->theme->reference = NULL;
            free(wi);
            wi = NULL;
            DestroyWindow(hwnd);
        }
        rv = 0;
    }

    return iMsg == WM_CREATE ? 0 : rv;
}


//////////////////////////////////////////////////////////////////////////
/// Function:
///     archWindowCreate
///
/// Description:
///     Creates a window based on the theme configuration
//////////////////////////////////////////////////////////////////////////
void* archWindowCreate(Theme* theme, int childWindow) 
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    WindowInfo* wi;

    static int initialized = 0;
    if (!initialized) {
        static WNDCLASSEX wndClass;
        wndClass.cbSize         = sizeof(wndClass);
        wndClass.style          = CS_OWNDC;
        wndClass.lpfnWndProc    = windowProc;
        wndClass.cbClsExtra     = 0;
        wndClass.cbWndExtra     = 0;
        wndClass.hInstance      = hInstance;
        wndClass.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BLUEMSX));
        wndClass.hIconSm        = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BLUEMSX));
        wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wndClass.hbrBackground  = NULL;
        wndClass.lpszMenuName   = NULL;
        wndClass.lpszClassName  = "blueMSX Popup";

        RegisterClassEx(&wndClass);

        initialized = 1;
    }

    wi = calloc(1, sizeof(WindowInfo));
    wi->theme = theme;

    if (childWindow) {
        return CreateWindowEx(WS_EX_TOOLWINDOW, "blueMSX Popup", theme->name, 
                            WS_OVERLAPPED | WS_CLIPCHILDREN | WS_BORDER | WS_DLGFRAME | 
                            WS_SYSMENU | WS_MINIMIZEBOX, 
                            CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, getMainHwnd(), NULL, 
                            hInstance, wi);
    }
    else {
        return CreateWindow("blueMSX Popup", theme->name, 
                            WS_OVERLAPPED | WS_CLIPCHILDREN | WS_BORDER | WS_DLGFRAME | 
                            WS_SYSMENU | WS_MINIMIZEBOX, 
                            CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, NULL, NULL, 
                            hInstance, wi);
    }
}


//////////////////////////////////////////////////////////////////////////
/// Function:
///     objectUpdate
///
/// Description:
///     Updates the child windows of parent with type notifyId 
//////////////////////////////////////////////////////////////////////////
static void objectUpdate(HWND parent, int notifyId, int arg)
{
    int i;
    for (i = 0; windowData[i].hwnd != NULL; i++) {
        if (GetParent(windowData[i].hwnd) == parent && windowData[i].id == notifyId) {
            SendMessage(windowData[i].hwnd, WM_OBJECT_UPDATE, 0, (LPARAM)arg);
        }
    }
}


//////////////////////////////////////////////////////////////////////////
/// Function:
///     objectShow
///
/// Description:
///     Shows/hides the child windows of parent with type notifyId 
//////////////////////////////////////////////////////////////////////////
static void objectShow(HWND parent, int notifyId, int show)
{
    int i;
    for (i = 0; windowData[i].hwnd != NULL; i++) {
        if (GetParent(windowData[i].hwnd) == parent && windowData[i].id == notifyId) {
            SendMessage(windowData[i].hwnd, WM_OBJECT_SHOW, 0, show);
        }
    }
}


//////////////////////////////////////////////////////////////////////////
/// Function:
///     objectEnable
///
/// Description:
///     Enables/disables the child windows of parent with type notifyId 
//////////////////////////////////////////////////////////////////////////
static void objectEnable(HWND parent, int notifyId, int enable)
{
    int i;
    for (i = 0; windowData[i].hwnd != NULL; i++) {
        if (GetParent(windowData[i].hwnd) == parent && windowData[i].id == notifyId) {
            SendMessage(windowData[i].hwnd, WM_OBJECT_ENABLE, 0, enable);
        }
    }
}



//////////////////////////////////////////////////////////////////////////
/// Struct:
///     DropdownInfo
///
/// Description:
///     Contains dropdown menu specific data
//////////////////////////////////////////////////////////////////////////
typedef struct {
    int x;
    int y;
    int width;
    int height;
    int notifyId;
    Theme* theme;
    char text[64];
} DropdownInfo;


//////////////////////////////////////////////////////////////////////////
/// Function:
///     dropdownProc
///
/// Description:
///     Window handler for a dropdown menu controls
//////////////////////////////////////////////////////////////////////////
static BOOL CALLBACK dropdownProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    DropdownInfo* oi;

    switch (iMsg) {
    case WM_INITDIALOG:
        oi = (DropdownInfo*)malloc(sizeof(DropdownInfo));
        *oi = *(DropdownInfo*)lParam;
        SetWindowPos(hwnd, NULL, oi->x, oi->y, oi->width, oi->height, SWP_NOZORDER | SWP_SHOWWINDOW);
        SetWindowPos(GetDlgItem(hwnd, IDC_CONTROL), NULL, 0, 0, oi->width, 96, SWP_NOZORDER);
        windowDataSet(hwnd, oi->notifyId, oi);
        SendMessage(hwnd, WM_OBJECT_UPDATE, 0, 0);
        return FALSE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_CONTROL) {
            static int isChanging = 0;
            if (isChanging == 0 && HIWORD(wParam) == CBN_SELCHANGE) {
                char sel[64];
                int idx;
                int rv;

                isChanging = 1;

                idx = SendMessage(GetDlgItem(hwnd, IDC_CONTROL), CB_GETCURSEL, 0, 0);
                rv = SendMessage(GetDlgItem(hwnd, IDC_CONTROL), CB_GETLBTEXT, idx, (LPARAM)sel);
                if (rv != CB_ERR) {
                    oi = (DropdownInfo*)windowDataGet(hwnd);
                    SendMessage(GetParent(hwnd), (UINT)oi->notifyId, 0, (LPARAM)sel);
                }
                isChanging = 0;
            }
        }
        return TRUE;
    case WM_CLOSE:
        oi = (DropdownInfo*)windowDataGet(hwnd);
        windowDataSet(hwnd, 0, NULL);
        free(oi);
        break;
    case WM_OBJECT_UPDATE:
        while (CB_ERR != SendDlgItemMessage(hwnd, IDC_CONTROL, CB_DELETESTRING, 0, 0));

        oi = (DropdownInfo*)windowDataGet(hwnd);
        if (lParam != 0) {
            strcpy(oi->text, (char*)lParam);
        }
        {
            char** items = { NULL };
            int index = 0;

            switch (oi->notifyId) {
            case WM_DROPDOWN_MACHINECONFIG:
                items = machineGetAvailable(0);
                break;
            case WM_DROPDOWN_KEYBOARDCONFIG:
                items = keyboardGetConfigs();
                break;
            case WM_DROPDOWN_THEMEPAGES:
                items = themeGetPageNames((Theme*)oi->theme);
                break;
            }

            while (*items != NULL) {
                SendDlgItemMessage(hwnd, IDC_CONTROL, CB_ADDSTRING, 0, (LPARAM)*items);

                if (index == 0 || 0 == strcmp(*items, oi->text)) {
                    SendDlgItemMessage(hwnd, IDC_CONTROL, CB_SETCURSEL, index, 0);
                }
                items++;
                index++;
            }
        }
        break;
    case WM_OBJECT_SHOW:
        ShowWindow(hwnd, lParam);
        break;
    case WM_OBJECT_ENABLE:
        EnableWindow(hwnd, lParam);
        break;
    }
    return FALSE;
}


//////////////////////////////////////////////////////////////////////////
/// Function:
///     objectDropdownCreate
///
/// Description:
///     Function to create dropdown menu controls (from within themes)
//////////////////////////////////////////////////////////////////////////
static void* objectDropdownCreate(HWND hwnd, char* id, int x, int y, int width, int height, int arg1, int arg2)
{
    DropdownInfo oi = { x, y, width, height, 0, 0 };

    if (0 == strcmp(id, "dropdown-keyconfigs")) {
        oi.text[0] = 0;
        oi.notifyId = WM_DROPDOWN_KEYBOARDCONFIG;
    }
    
    if (0 == strcmp(id, "dropdown-machineconfigs")) {
        oi.text[0] = 0;
        oi.notifyId = WM_DROPDOWN_MACHINECONFIG;
    }

    if (0 == strcmp(id, "dropdown-themepages")) {
        Theme* theme = (Theme*)arg1;
        strcpy(oi.text, themeGetPageName(theme, themeGetCurrentPageIndex(theme)));
        oi.notifyId = WM_DROPDOWN_THEMEPAGES;
        oi.theme    = (Theme*)arg1;
    }
    
    if (oi.notifyId == 0) {
        return NULL;
    }

    return CreateDialogParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DROPDOWN), hwnd, dropdownProc, (LPARAM)&oi);
}


//////////////////////////////////////////////////////////////////////////
/// Function:
///     objectDropdownDestroy
///
/// Description:
///     Function to destroy dropdown menu controls
//////////////////////////////////////////////////////////////////////////
static void objectDropdownDestroy(void* object) 
{
    DestroyWindow((HWND)object);
}



//////////////////////////////////////////////////////////////////////////
/// Struct:
///     ButtonInfo
///
/// Description:
///     Contains button control specific data
//////////////////////////////////////////////////////////////////////////
typedef struct {
    int x;
    int y;
    int width;
    int height;
    char* text;
    int notifyId;
} ButtonInfo;


//////////////////////////////////////////////////////////////////////////
/// Function:
///     dropdownProc
///
/// Description:
///     Window handler for a button controls
//////////////////////////////////////////////////////////////////////////
static BOOL CALLBACK buttonProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    static ButtonInfo* oi;

    switch (iMsg) {
    case WM_INITDIALOG:
        oi = (ButtonInfo*)lParam;
        SetWindowPos(hwnd, NULL, oi->x, oi->y, oi->width, oi->height, SWP_NOZORDER | SWP_SHOWWINDOW);
        SetWindowPos(GetDlgItem(hwnd, IDC_CONTROL), NULL, 0, 0, oi->width, oi->height, SWP_NOZORDER);
        SetWindowText(GetDlgItem(hwnd, IDC_CONTROL), oi->text);
        windowDataSet(hwnd, oi->notifyId, (void*)oi->notifyId);
        return FALSE;
    case WM_COMMAND:
        if (wParam == IDC_CONTROL) {
            SendMessage(GetParent(hwnd), (UINT)windowDataGet(hwnd), 0, 0);
        }
        return TRUE;
    case WM_CLOSE:
        windowDataSet(hwnd, 0, NULL);
        break;
    case WM_OBJECT_SHOW:
        ShowWindow(hwnd, lParam);
        break;
    case WM_OBJECT_ENABLE:
        EnableWindow(GetDlgItem(hwnd, IDC_CONTROL), lParam);
        break;
    }
    return FALSE;
}


//////////////////////////////////////////////////////////////////////////
/// Function:
///     objectButtonCreate
///
/// Description:
///     Function to create button controls (from within themes)
//////////////////////////////////////////////////////////////////////////
static void* objectButtonCreate(HWND hwnd, char* id, int x, int y, int width, int height)
{
    ButtonInfo oi = { x, y, width, height, NULL, 0};
    
    if (0 == strcmp(id, "button-close")) {
        oi.text     = langDlgClose();
        oi.notifyId = WM_BUTTON_CLOSE;
    }
    if (0 == strcmp(id, "button-ok")) {
        oi.text     = langDlgOK();
        oi.notifyId = WM_BUTTON_OK;
    }
    if (0 == strcmp(id, "button-cancel")) {
        oi.text = langDlgCancel();
        oi.notifyId = WM_BUTTON_CANCEL;
    }
    if (0 == strcmp(id, "button-save")) {
        oi.text = langDlgSave();
        oi.notifyId = WM_BUTTON_SAVE;
    }
    if (0 == strcmp(id, "button-saveas")) {
        oi.text = langDlgSaveAs();
        oi.notifyId = WM_BUTTON_SAVEAS;
    }
    
    if (oi.notifyId == 0) {
        return NULL;
    }

    return CreateDialogParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_BUTTON), hwnd, buttonProc, (LPARAM)&oi);
}


//////////////////////////////////////////////////////////////////////////
/// Function:
///     objectButtonDestroy
///
/// Description:
///     Function to destroy button controls
//////////////////////////////////////////////////////////////////////////
static void objectButtonDestroy(void* object) 
{
    DestroyWindow((HWND)object);
}


//////////////////////////////////////////////////////////////////////////
/// Function:
///     archObjectCreate
///
/// Description:
///     Creates a control based on the id string. The method is used to
///     create host specific controls from the themes.
//////////////////////////////////////////////////////////////////////////
void* archObjectCreate(char* id, void* window, int x, int y, int width, int height, int arg1, int arg2)
{
    if (0 == strncmp(id, "button-", 7)) {
        return objectButtonCreate(window, id, x, y, width, height);
    }
    if (0 == strncmp(id, "dropdown-", 9)) {
        return objectDropdownCreate(window, id, x, y, width, height, arg1, arg2);
    }
    return NULL;
}


//////////////////////////////////////////////////////////////////////////
/// Function:
///     archObjectDestroy
///
/// Description:
///     Destroys a control based on the id string.
//////////////////////////////////////////////////////////////////////////
void archObjectDestroy(char* id, void* object)
{
    if (0 == strncmp(id, "button-", 7)) {
        objectButtonDestroy(object);
    }
    if (0 == strncmp(id, "dropdown-", 9)) {
        objectDropdownDestroy(object);
    }
}
