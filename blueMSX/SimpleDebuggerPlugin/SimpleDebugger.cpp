#include <windows.h>
#include "ToolInterface.h"
#include "Resource.h"
#include "StatusBar.h"
#include "Toolbar.h"
#include "Disassembly.h"
#include "resrc1.h"
#include <string>
#include <commctrl.h>
#include <sstream>
#include <iomanip>

using namespace std;

static HWND dbgHwnd = NULL;
static HWND viewHwnd = NULL;
static StatusBar* statusBar = NULL;
static Toolbar* toolBar = NULL;
static Disassembly* disassembly = NULL;

#define WM_STATUS (WM_USER + 1797)

#define TB_RESUME   37000
#define TB_PAUSE    37001
#define TB_STOP     37002
#define TB_RUN      37003
#define TB_SHOWNEXT 37004
#define TB_STEPIN   37005
#define TB_RUNTO    37006

static void updateTooltip(int id, char* str)
{
    switch (id) {
    case TB_RESUME:   sprintf(str, "Resume");               break;
    case TB_PAUSE:    sprintf(str, "Break All");            break;
    case TB_STOP:     sprintf(str, "Stop Debugging");       break;
    case TB_RUN:      sprintf(str, "Restart");              break;
    case TB_SHOWNEXT: sprintf(str, "Show Next Statement");  break;
    case TB_STEPIN:   sprintf(str, "Step Into");            break;
    case TB_RUNTO:    sprintf(str, "Run To Cursor");        break;
    }
}

static Toolbar* initializeToolbar(HWND owner)
{
    Toolbar* toolBar = new Toolbar(GetDllHinstance(), owner, IDB_TOOLBAR, RGB(239, 237, 222), IDB_TOOLBARBG);

    toolBar->addSeparator();
    toolBar->addButton(0, TB_RESUME);
    toolBar->addButton(1, TB_PAUSE);
    toolBar->addButton(2, TB_STOP);
    toolBar->addButton(3, TB_RUN);
    toolBar->addSeparator();
    toolBar->addButton(4, TB_SHOWNEXT);
    toolBar->addButton(5, TB_STEPIN);
    toolBar->addButton(6, TB_RUNTO);
    toolBar->addSeparator();

    return toolBar;
}

static void updateToolBar()
{
    if (toolBar == NULL) {
        return;
    }

    EmulatorState state = GetEmulatorState();
    
    toolBar->enableItem(1, state != EMULATOR_RUNNING);
    toolBar->enableItem(2, state == EMULATOR_RUNNING);
    toolBar->enableItem(3, state != EMULATOR_STOPPED);
    toolBar->enableItem(4, true);
    
    toolBar->enableItem(6, state == EMULATOR_PAUSED);
    toolBar->enableItem(7, state == EMULATOR_PAUSED);
    toolBar->enableItem(8, state == EMULATOR_PAUSED);
}

static void updateStatusBar()
{
    if (statusBar == NULL) {
        return;
    }

    switch (GetEmulatorState()) {
    case EMULATOR_RUNNING:
        statusBar->setField(1, "Running");
        break;
    case EMULATOR_PAUSED:
        statusBar->setField(1, "Paused");
        break;
    case EMULATOR_STOPPED:
        statusBar->setField(1, "Stopped");
        break;
    }
}

void updateDeviceState()
{
    bool disassemblyUpdated = false;

    Snapshot* snapshot = SnapshotCreate();
    if (snapshot != NULL) {
        int deviceCount = SnapshotGetDeviceCount(snapshot);

        for (int i = 0; i < deviceCount; i++) {
            Device* device = SnapshotGetDevice(snapshot, i);
            int j;

            int memCount = DeviceGetMemoryBlockCount(device);

            for (j = 0; j < memCount; j++) {
                MemoryBlock* mem = DeviceGetMemoryBlock(device, j);
            }

            int regBankCount = DeviceGetRegisterBankCount(device);
            for (j = 0; j < regBankCount; j++) {
                RegisterBank* regBank = DeviceGetRegisterBank(device, j);
            }

            int ioPortsCount = DeviceGetIoPortsCount(device);
            for (j = 0; j < ioPortsCount; j++) {
                IoPorts* ioPorts = DeviceGetIoPorts(device, j);
            }

            if (device->type == DEVTYPE_CPU && memCount > 0) {
                UInt16 pc = 0;

                for (j = 0; j < regBankCount; j++) {
                    RegisterBank* regBank = DeviceGetRegisterBank(device, j);
                    for (UInt32 k = 0; k < regBank->count; k++) {
                        if (0 == strcmp("PC", regBank->reg[k].name)) {
                            pc = (UInt16)regBank->reg[k].value;
                        }
                    }
                }

                MemoryBlock* mem = DeviceGetMemoryBlock(device, 0);
                if (mem->size == 0x10000) {
                    disassembly->updateContent(mem->memory, pc);
                    disassemblyUpdated = true;
                }
            }

        }

        SnapshotDestroy(snapshot);
    }

    if (!disassemblyUpdated) {
        disassembly->invalidateContent();
    }
}


static LRESULT CALLBACK wndProcView(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (iMsg) {
    case WM_CREATE:
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT r;
            GetClientRect(hwnd, &r);
            HBRUSH hBrush = (HBRUSH)SelectObject(hdc, GetStockObject(GRAY_BRUSH)); 
            PatBlt(hdc, 0, 0, r.right, r.bottom, PATCOPY);
            SelectObject(hdc, hBrush);
            EndPaint(hwnd, &ps);
        }
        return 0;
    }

    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

static void updateWindowPositions()
{    
    if (statusBar != NULL) {
        statusBar->updatePosition();
    }
    if (toolBar != NULL) {
        toolBar->updatePosition();
    }
    if (viewHwnd != NULL) {
        RECT r;
        GetClientRect(dbgHwnd, &r);

        if (statusBar != NULL) {
            r.bottom -= statusBar->getHeight();
        }
        if (toolBar != NULL) {
            r.top    += toolBar->getHeight();
            r.bottom -= toolBar->getHeight();
        }

        SetWindowPos(viewHwnd, NULL, r.left, r.top, r.right, r.bottom, SWP_NOZORDER);
    }
}

static LRESULT CALLBACK wndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (iMsg) {
    case WM_CREATE:
        return 0;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case TB_RESUME:
            EmulatorRun();
            return 0;
        case TB_PAUSE:
            EmulatorPause();
            return 0;
        case TB_STOP:
            EmulatorStop();
            return 0;
        case TB_RUN:
            EmulatorStop();
            EmulatorRun();
            return 0;
        case TB_SHOWNEXT:
            disassembly->updateScroll();
            return 0;
        case TB_STEPIN:
            EmulatorStep();
            return 0;
        case TB_RUNTO:
            return 0;
        }
        break;

    case WM_STATUS:
        if (statusBar != NULL) {
            updateStatusBar();
        }
        if (toolBar != NULL) {
            updateToolBar();
        }
        updateDeviceState();
        return 0;

    case WM_SIZE:
        updateWindowPositions();
        break;
        
    case WM_NOTIFY:
        switch(((LPNMHDR)lParam)->code){
        case NM_CUSTOMDRAW:
            if (toolBar != NULL) {
                toolBar->onWmNotify(lParam);
            }
            return 0;

        case TTN_GETDISPINFO: 
            { 
                LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam; 
                lpttt->hinst = GetDllHinstance(); 
                updateTooltip(lpttt->hdr.idFrom, lpttt->szText);
            }
        }
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
        delete statusBar;
        statusBar = NULL;
        delete toolBar;
        toolBar = NULL;
        viewHwnd = NULL;
        DestroyWindow(hwnd);
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
    wndClass.lpszClassName  = "msxdebugger";

    RegisterClassEx(&wndClass);
    
    wndClass.lpfnWndProc    = wndProcView;
    wndClass.lpszClassName  = "msxdebuggerview";
    wndClass.style          = 0;
    wndClass.lpszMenuName   = NULL;

    RegisterClassEx(&wndClass);
}

void OnDestroyTool() {
}

void OnShowTool() {
    if (dbgHwnd != NULL) {
        return;
    }

    dbgHwnd = CreateWindow("msxdebugger", "blueMSX - Debugger", 
                           WS_OVERLAPPEDWINDOW, 
                           CW_USEDEFAULT, CW_USEDEFAULT, 600, 600, NULL, NULL, GetDllHinstance(), NULL);

    viewHwnd = CreateWindow("msxdebuggerview", "", 
                            WS_OVERLAPPED | WS_CHILD, CW_USEDEFAULT, CW_USEDEFAULT, 600, 500, dbgHwnd, NULL, GetDllHinstance(), NULL);

    ShowWindow(dbgHwnd, TRUE);
    ShowWindow(viewHwnd, TRUE);

    std::vector<int> fieldVector;
    fieldVector.push_back(0);
    fieldVector.push_back(70);
    fieldVector.push_back(20);
    statusBar = new StatusBar(GetDllHinstance(), dbgHwnd, fieldVector);
    updateStatusBar();
    statusBar->show();
    toolBar = initializeToolbar(dbgHwnd);
    toolBar->show();
    updateToolBar();

    disassembly = new Disassembly(GetDllHinstance(), viewHwnd);
    RECT r = { 0, 32, 400, 500 };
    disassembly->updatePosition(r);
    disassembly->show();

    updateWindowPositions();
}

void OnEmulatorStart() {
    if (dbgHwnd != NULL) {
        disassembly->updateBreakpoints();
        SendMessage(dbgHwnd, WM_STATUS, 0, 0);
    }
}

void OnEmulatorStop() {
    if (dbgHwnd != NULL) {
        SendMessage(dbgHwnd, WM_STATUS, 0, 0);
    }
}

void OnEmulatorPause() {
    if (dbgHwnd != NULL) {
        SendMessage(dbgHwnd, WM_STATUS, 0, 0);
    }
}

void OnEmulatorResume() {
    if (dbgHwnd != NULL) {
        SendMessage(dbgHwnd, WM_STATUS, 0, 0);
    }
}

const char* OnGetName() {
    return "Debugger";
}
