#include <windows.h>
#include "ToolInterface.h"
#include "Resource.h"
#include <string>
#include <commctrl.h>
#include <sstream>
#include <iomanip>

using namespace std;

static HWND dbgHwnd = NULL;

#define MENU_FILE_EXIT              37100
#define MENU_HELP_ABOUT             37400

static void updateWindowMenu() 
{
    HMENU hMenuFile = CreatePopupMenu();
    AppendMenu(hMenuFile, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenuFile, MF_STRING, MENU_FILE_EXIT, "Exit");
    
    HMENU hMenuHelp = CreatePopupMenu();
    AppendMenu(hMenuHelp, MF_STRING, MENU_HELP_ABOUT, "About");

    static HMENU hMenu = NULL;
    if (hMenu != NULL) {
        DestroyMenu(hMenu);
    }

    hMenu = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuFile, "File");
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuHelp, "Help");
    
    SetMenu(dbgHwnd, hMenu);
}

static LRESULT CALLBACK wndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (iMsg) {
    case WM_CREATE:
        return 0;


    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case MENU_FILE_EXIT:
            SendMessage(hwnd, WM_CLOSE, 0, 0);
            return 0;

        case MENU_HELP_ABOUT:
            MessageBox(NULL, "blueMSX debugger\r\n\r\nBuilt: " __DATE__ "\r\n\r\nVisit http://www.bluemsx.com for details    \r\n\r\n\r\n",
                       "blueMSX - Debugger", MB_ICONINFORMATION | MB_OK);
            return 0;
        }
        break;

    case WM_SIZE:
        break;
        
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
        }
        return 0;

    case WM_CLOSE:
        dbgHwnd = NULL;
		break;
    }

    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void OnCreateTool() {
    WNDCLASSEX wndClass;

    wndClass.cbSize         = sizeof(wndClass);
    wndClass.style          = 0;
    wndClass.lpfnWndProc    = wndProc;
    wndClass.cbClsExtra     = 0;
    wndClass.cbWndExtra     = 0;
    wndClass.hInstance      = GetDllHinstance();
    wndClass.hIcon          = NULL;
    wndClass.hIconSm        = NULL;
    wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground  = NULL;
    wndClass.lpszMenuName   = NULL;
    wndClass.lpszClassName  = "TraceWindow";

    RegisterClassEx(&wndClass);
    }

void OnDestroyTool() {
    if (dbgHwnd != NULL) {
        CloseWindow(dbgHwnd);
    }
}

void OnShowTool() {
    if (dbgHwnd != NULL) {
        return;
    }

    dbgHwnd = CreateWindow("TraceWindow", "blueMSX - Trace", 
                           WS_OVERLAPPEDWINDOW, 
                           CW_USEDEFAULT, CW_USEDEFAULT, 600, 440, NULL, NULL, GetDllHinstance(), NULL);

    ShowWindow(dbgHwnd, TRUE);

    updateWindowMenu();
}

void OnEmulatorStart() {
}

void OnEmulatorStop() {
}

void OnEmulatorPause() {
}

void OnEmulatorResume() {
}

void OnEmulatorReset() {
}

void OnEmulatorTrace(const char* message)
{
}

const char* OnGetName() {
    return "Trace Window";
}
