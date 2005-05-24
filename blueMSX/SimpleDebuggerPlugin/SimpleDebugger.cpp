#include <windows.h>
#include "ToolInterface.h"
#include "Resource.h"
#include "StatusBar.h"
#include "Toolbar.h"
#include "Disassembly.h"
#include "Callstack.h"
#include "Stack.h"
#include "CpuRegisters.h"
#include "SymbolInfo.h"
#include "Memory.h"
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
static StackWindow* stack = NULL;
static CallstackWindow* callstack = NULL;
static CpuRegisters* cpuRegisters = NULL;
static SymbolInfo* symbolInfo = NULL;
static Memory* memory = NULL;

#define WM_STATUS (WM_USER + 1797)

#define TB_RESUME   37000
#define TB_PAUSE    37001
#define TB_STOP     37002
#define TB_RUN      37003
#define TB_SHOWNEXT 37004
#define TB_STEPIN   37005
#define TB_RUNTO    37006
#define TB_BPTOGGLE 37007
#define TB_BPENABLE 37008
#define TB_BPENALL  37009
#define TB_BPDISALL 37010
#define TB_BPREMALL 37011

static void updateTooltip(int id, char* str)
{
    switch (id) {
    case TB_RESUME:   sprintf(str, "Start/Continue");            break;
    case TB_PAUSE:    sprintf(str, "Break All");                 break;
    case TB_STOP:     sprintf(str, "Stop Debugging");            break;
    case TB_RUN:      sprintf(str, "Restart");                   break;
    case TB_SHOWNEXT: sprintf(str, "Show Next Statement");       break;
    case TB_STEPIN:   sprintf(str, "Step Into");                 break;
    case TB_RUNTO:    sprintf(str, "Run To Cursor");             break;
    case TB_BPTOGGLE: sprintf(str, "Set/Remove Breakpoint");     break;
    case TB_BPENABLE: sprintf(str, "Enable/Disable Breakpoint"); break;
    case TB_BPENALL:  sprintf(str, "Enable All Breakpoints");    break;
    case TB_BPDISALL: sprintf(str, "Disable All Breakpoints");   break;
    case TB_BPREMALL: sprintf(str, "Remove All Breakpoints");    break;
    }
}

static Toolbar* initializeToolbar(HWND owner)
{
    Toolbar* toolBar = new Toolbar(GetDllHinstance(), owner, IDB_TOOLBAR, RGB(239, 237, 222));

    toolBar->addSeparator();
    toolBar->addButton(0,  TB_RESUME);
    toolBar->addButton(1,  TB_PAUSE);
    toolBar->addButton(2,  TB_STOP);
    toolBar->addButton(3,  TB_RUN);
    toolBar->addSeparator();
    toolBar->addButton(4,  TB_SHOWNEXT);
    toolBar->addButton(5,  TB_STEPIN);
    toolBar->addButton(6,  TB_RUNTO);
    toolBar->addSeparator();
    toolBar->addButton(10, TB_BPTOGGLE);
    toolBar->addButton(11, TB_BPENABLE);
    toolBar->addButton(9,  TB_BPENALL);
    toolBar->addButton(8,  TB_BPDISALL);
    toolBar->addButton(7,  TB_BPREMALL);

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
    toolBar->enableItem(8, state == EMULATOR_PAUSED && disassembly->isCursorPresent());

    toolBar->enableItem(10, state != EMULATOR_STOPPED && disassembly->isCursorPresent());
    toolBar->enableItem(11, state != EMULATOR_STOPPED && disassembly->isBpOnCcursor());
    toolBar->enableItem(12, disassembly->getDisabledBpCount() > 0);
    toolBar->enableItem(13, disassembly->getEnabledBpCount() > 0);
    toolBar->enableItem(14, disassembly->getEnabledBpCount() || disassembly->getDisabledBpCount());
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

#define MENU_FILE_EXIT              37100
#define MENU_FILE_LOADSYM           37101

#define MENU_DEBUG_CONTINUE         37200
#define MENU_DEBUG_BREAKALL         37201
#define MENU_DEBUG_STOP             37202
#define MENU_DEBUG_RESTART          37203
#define MENU_DEBUG_STEP             37204
#define MENU_DEBUG_RUNTO            37205
#define MENU_DEBUG_SHOWSYMBOLS      37206
#define MENU_DEBUG_GOTO             37207
#define MENU_DEBUG_BPTOGGLE         37208
#define MENU_DEBUG_BPENABLE         37209
#define MENU_DEBUG_BPREMOVEALL      37210
#define MENU_DEBUG_BPENABLEALL      37211
#define MENU_DEBUG_BPDISABLEALL     37212

#define MENU_WINDOW_DISASSEMBLY     37300
#define MENU_WINDOW_CPUREGISTERS    37301
#define MENU_WINDOW_STACK           37302
#define MENU_WINDOW_CALLSTACK       37303
#define MENU_WINDOW_MEMORY          37304

#define MENU_HELP_ABOUT             37400

static void updateWindowMenu() 
{
    EmulatorState state = GetEmulatorState();

    HMENU hMenuFile = CreatePopupMenu();
    AppendMenu(hMenuFile, MF_STRING, MENU_FILE_LOADSYM, "Load Symbol File");
    AppendMenu(hMenuFile, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenuFile, MF_STRING, MENU_FILE_EXIT, "Exit");
    
    HMENU hMenuDebug = CreatePopupMenu();
    if (state == EMULATOR_STOPPED) {
        AppendMenu(hMenuDebug, MF_STRING, MENU_DEBUG_CONTINUE, "Start\tF5");
    }
    else {
        AppendMenu(hMenuDebug, MF_STRING | (state != EMULATOR_RUNNING ? 0 : MF_GRAYED), MENU_DEBUG_CONTINUE, "Continue\tF5");
        AppendMenu(hMenuDebug, MF_STRING | (state == EMULATOR_RUNNING ? 0 : MF_GRAYED), MENU_DEBUG_BREAKALL, "Break All\tCtrl+Alt+Break");
        AppendMenu(hMenuDebug, MF_STRING                                              , MENU_DEBUG_STOP,     "Stop Debugging\tShift+F5");
        AppendMenu(hMenuDebug, MF_STRING                                              , MENU_DEBUG_RESTART,  "Restart\tCtrl+Shift+F5");
    }
    AppendMenu(hMenuDebug, MF_STRING | (state == EMULATOR_PAUSED                  ? 0 : MF_GRAYED), MENU_DEBUG_STEP, "Step Into\tF10");
    AppendMenu(hMenuDebug, MF_STRING | (state == EMULATOR_PAUSED && disassembly->isCursorPresent() ? 0 : MF_GRAYED), MENU_DEBUG_RUNTO, "Run To Cursor\tShift+F10");
    AppendMenu(hMenuDebug, MF_SEPARATOR, 0, NULL);

    AppendMenu(hMenuDebug, MF_STRING | (symbolInfo->getShowStatus() ? MF_CHECKED : 0), MENU_DEBUG_SHOWSYMBOLS, "Show Symbol Information\tF8");
    AppendMenu(hMenuDebug, MF_SEPARATOR, 0, NULL);

    AppendMenu(hMenuDebug, MF_STRING | (1 ? 0 : MF_GRAYED), MENU_DEBUG_GOTO, "Go To\tCtrl+G");
    AppendMenu(hMenuDebug, MF_SEPARATOR, 0, NULL);
    
    AppendMenu(hMenuDebug, MF_STRING | (state != EMULATOR_STOPPED && disassembly->isCursorPresent() ? 0 : MF_GRAYED), MENU_DEBUG_BPTOGGLE, "Set/Remove Breakpoint\tF9");
    AppendMenu(hMenuDebug, MF_STRING | (state != EMULATOR_STOPPED && disassembly->isBpOnCcursor() ? 0 : MF_GRAYED), MENU_DEBUG_BPENABLE, "Enable/Disable Breakpoint\tShift+F9");
    AppendMenu(hMenuDebug, MF_STRING | (disassembly->getEnabledBpCount() || disassembly->getDisabledBpCount() ? 0 : MF_GRAYED), MENU_DEBUG_BPREMOVEALL, "Remove All Breakpoints\tCtrl+Shift+F9");

    AppendMenu(hMenuDebug, MF_STRING | (disassembly->getDisabledBpCount() ? 0 : MF_GRAYED), MENU_DEBUG_BPENABLEALL, "Enable All Breakpoints");
    AppendMenu(hMenuDebug, MF_STRING | (disassembly->getEnabledBpCount() ? 0 : MF_GRAYED), MENU_DEBUG_BPDISABLEALL, "Disable All Breakpoints");

    HMENU hMenuWindow = CreatePopupMenu();
    AppendMenu(hMenuWindow, MF_STRING | (disassembly  && disassembly->isVisible()  ? MFS_CHECKED : 0), MENU_WINDOW_DISASSEMBLY, "Disassembly");
    AppendMenu(hMenuWindow, MF_STRING | (cpuRegisters && cpuRegisters->isVisible() ? MFS_CHECKED : 0), MENU_WINDOW_CPUREGISTERS, "CPU Registers");
    AppendMenu(hMenuWindow, MF_STRING | (stack        && stack->isVisible()        ? MFS_CHECKED : 0), MENU_WINDOW_STACK, "Stack");
    AppendMenu(hMenuWindow, MF_STRING | (callstack    && callstack->isVisible()    ? MFS_CHECKED : 0), MENU_WINDOW_CALLSTACK, "Callstack");
    AppendMenu(hMenuWindow, MF_STRING | (memory       && memory->isVisible()       ? MFS_CHECKED : 0), MENU_WINDOW_MEMORY, "Memory Viewer");

    HMENU hMenuHelp = CreatePopupMenu();
    AppendMenu(hMenuHelp, MF_STRING, MENU_HELP_ABOUT, "About");

    static HMENU hMenu = NULL;
    if (hMenu != NULL) {
        DestroyMenu(hMenu);
    }

    hMenu = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuFile, "File");
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuDebug, "Debug");
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuWindow, "Window");
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuHelp, "Help");
    
    SetMenu(dbgHwnd, hMenu);
}


static BOOL replaceSymbols = TRUE;

UINT_PTR CALLBACK hookProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    switch (iMsg) {
    case WM_INITDIALOG:
        SendDlgItemMessage(hDlg, IDC_SYMBOLSAPPEND, BM_SETCHECK, replaceSymbols ? BST_CHECKED : BST_UNCHECKED, 0);
        return 0;

    case WM_SIZE:
        {
            RECT r;
            int height;
            int width;
            HWND hwnd;

            GetClientRect(GetParent(hDlg), &r);
            
            height = r.bottom - r.top;
            width  = r.right - r.left;

            hwnd = GetDlgItem(hDlg, IDC_SYMBOLSAPPEND);
            SetWindowPos(hwnd, NULL, 81, height - 26, 0, 0, SWP_NOSIZE | SWP_NOZORDER);            
        }
        return 0;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_SYMBOLSAPPEND) {
            int newChecked = BST_CHECKED == SendDlgItemMessage(hDlg, IDC_SYMBOLSAPPEND, BM_GETCHECK, 0, 0);
            if (newChecked != replaceSymbols) {
                replaceSymbols = newChecked;
                InvalidateRect(hDlg, NULL, TRUE);
            }
        }
        return 0;

        
    }
    return 0;
}

void loadSymbolFile(HWND hwndOwner)
{
    OPENFILENAME ofn; 
    static char pFileName[MAX_PATH];
    static char buffer[0x20000];

    pFileName[0] = 0; 

    char  curDir[MAX_PATH];

    GetCurrentDirectory(MAX_PATH, curDir);

    ofn.lStructSize = sizeof(OPENFILENAME); 
    ofn.hwndOwner = hwndOwner; 
    ofn.hInstance = GetDllHinstance();
    ofn.lpstrFilter = "*.SYM\0*.*\0\0"; 
    ofn.lpstrCustomFilter = NULL; 
    ofn.nMaxCustFilter = 0;
    ofn.nFilterIndex = 0; 
    ofn.lpstrFile = pFileName; 
    ofn.nMaxFile = 1024; 
    ofn.lpstrFileTitle = NULL; 
    ofn.nMaxFileTitle = 0; 
    ofn.lpstrInitialDir = NULL; 
    ofn.lpstrTitle = "Open Symbol File"; 
    ofn.Flags = OFN_EXPLORER | OFN_ENABLESIZING | OFN_ENABLETEMPLATE | OFN_HIDEREADONLY | OFN_ENABLEHOOK | OFN_FILEMUSTEXIST; 
    ofn.nFileOffset = 0; 
    ofn.nFileExtension = 0; 
    ofn.lpstrDefExt = NULL; 
    ofn.lCustData = 0; 
    ofn.lpfnHook = hookProc; 
    ofn.lpTemplateName = MAKEINTRESOURCE(IDD_OPEN_SYMBOLSDIALOG); 

    BOOL rv = GetOpenFileName(&ofn); 

    SetCurrentDirectory(curDir);

    if (!rv) {
        return; 
    }

    FILE* file = fopen(pFileName, "r");
    if (file == NULL) {
        return;
    }

    fread(buffer, 1, sizeof(buffer), file);
    buffer[sizeof(buffer) - 1] = 0;
    if (replaceSymbols) {
        symbolInfo->clear();
    }
    symbolInfo->append(std::string(buffer));
    symbolInfo->show();
    disassembly->refresh();
    callstack->refresh();
    stack->refresh();
    fclose(file);
}


void DebuggerUpdate()
{
    updateToolBar();
    updateWindowMenu();
}


static Snapshot* currentSnapshot = NULL;

void updateDeviceState()
{
    bool disassemblyUpdated = false;

    if (GetEmulatorState() == EMULATOR_RUNNING) {
        return;
    }

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
                UInt16 sp = 0;

                RegisterBank* regBank = DeviceGetRegisterBank(device, 0);
                for (UInt32 k = 0; k < regBank->count; k++) {
                    if (0 == strcmp("PC", regBank->reg[k].name)) {
                        pc = (UInt16)regBank->reg[k].value;
                    }
                    if (0 == strcmp("SP", regBank->reg[k].name)) {
                        sp = (UInt16)regBank->reg[k].value;
                    }
                }

                cpuRegisters->updateContent(regBank);

                MemoryBlock* mem = DeviceGetMemoryBlock(device, 0);
                if (mem->size == 0x10000) {
                    disassembly->updateContent(mem->memory, pc);
                    stack->updateContent(mem->memory, sp);
                    disassemblyUpdated = true;
                }

                Callstack* stack = DeviceGetCallstack(device, 0);
                if (stack != NULL) {
                    callstack->updateContent(stack->callstack, stack->size);
                }
            }
        }

        memory->updateContent(snapshot);
    }

    if (currentSnapshot != NULL) {
        SnapshotDestroy(currentSnapshot);
    }

    currentSnapshot = snapshot;

    if (!disassemblyUpdated) {
        disassembly->invalidateContent();
        cpuRegisters->invalidateContent();
        callstack->invalidateContent();
        stack->invalidateContent();
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


static BOOL CALLBACK gotoProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    static HexInputDialog* addressInput = NULL;
    static WORD* address = NULL;

    switch (iMsg) {        
    case WM_INITDIALOG:
        if (addressInput) {
            delete addressInput;
        }
        addressInput = new HexInputDialog(hDlg, 10,30,249,22,6, symbolInfo);
        addressInput->setFocus();
        address = (WORD*)lParam;
        return FALSE;

    case WM_COMMAND:
        switch (wParam) {
        case IDOK:
            *address = (WORD)addressInput->getValue();
            EndDialog(hDlg, TRUE);
            return TRUE;
        case IDCANCEL:
            EndDialog(hDlg, FALSE);
            return TRUE;
        }
        break;
        
    case HexInputDialog::EC_NEWVALUE:
        *address = (WORD)addressInput->getValue();
        EndDialog(hDlg, TRUE);
        return FALSE;

    case WM_CLOSE:
        EndDialog(hDlg, FALSE);
        return TRUE;
    }

    return FALSE;
}

static LRESULT CALLBACK wndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    static BOOL isActive = FALSE;

    switch (iMsg) {
    case WM_CREATE:
        return 0;

    case WM_HOTKEY:
        if (isActive) {
            switch (wParam) {
            case 1:
                SendMessage(hwnd, WM_COMMAND, MENU_DEBUG_CONTINUE, 0);
                break;
            case 2:
                if (GetEmulatorState() == EMULATOR_RUNNING)
                    SendMessage(hwnd, WM_COMMAND, MENU_DEBUG_BREAKALL, 0);
                break;
            case 3:
                if (GetEmulatorState() != EMULATOR_STOPPED)
                    SendMessage(hwnd, WM_COMMAND, MENU_DEBUG_STOP, 0);
                break;
            case 4:
                if (GetEmulatorState() == EMULATOR_PAUSED)
                    SendMessage(hwnd, WM_COMMAND, MENU_DEBUG_RESTART, 0);
                break;
            case 5:
                if (GetEmulatorState() == EMULATOR_PAUSED)
                    SendMessage(hwnd, WM_COMMAND, MENU_DEBUG_STEP, 0);
                break;
            case 6:
                if (GetEmulatorState() == EMULATOR_PAUSED && disassembly->isCursorPresent())
                    SendMessage(hwnd, WM_COMMAND, MENU_DEBUG_RUNTO, 0);
                break;
            case 7:
                if (GetEmulatorState() != EMULATOR_STOPPED && disassembly->isCursorPresent())
                    SendMessage(hwnd, WM_COMMAND, MENU_DEBUG_BPTOGGLE, 0);
                break;
            case 8:
                if (GetEmulatorState() != EMULATOR_STOPPED && disassembly->isBpOnCcursor())
                    SendMessage(hwnd, WM_COMMAND, MENU_DEBUG_BPENABLE, 0);
                break;
            case 9:
                if (disassembly->getEnabledBpCount() || disassembly->getDisabledBpCount())
                    SendMessage(hwnd, WM_COMMAND, MENU_DEBUG_BPREMOVEALL, 0);
                break;
            case 10:
                SendMessage(hwnd, WM_COMMAND, MENU_DEBUG_SHOWSYMBOLS, 0);
                break;
            case 11:
                SendMessage(hwnd, WM_COMMAND, MENU_DEBUG_GOTO, 0);
                break;
            }
        }
        return 0;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case MENU_FILE_EXIT:
            SendMessage(hwnd, WM_CLOSE, 0, 0);
            return 0;

        case MENU_FILE_LOADSYM:
            loadSymbolFile(hwnd);
            return 0;

        case MENU_HELP_ABOUT:
            MessageBox(NULL, "blueMSX debugger\r\n\r\nBuilt: " __DATE__ "\r\n\r\nVisit http://www.bluemsx.com for details    \r\n\r\n\r\n",
                       "blueMSX - Debugger", MB_ICONINFORMATION | MB_OK);
            return 0;

        case MENU_WINDOW_DISASSEMBLY:
            if (disassembly->isVisible()) {
                disassembly->hide(); 
            }
            else {
                disassembly->show();
            }
            updateWindowMenu();
            return 0;

        case MENU_WINDOW_CPUREGISTERS:
            if (cpuRegisters->isVisible()) {
                cpuRegisters->hide(); 
            }
            else {
                cpuRegisters->show();
            }
            updateWindowMenu();
            return 0;

        case MENU_WINDOW_STACK:
            if (stack->isVisible()) {
                stack->hide(); 
            }
            else {
                stack->show();
            }
            updateWindowMenu();
            return 0;

        case MENU_WINDOW_CALLSTACK:
            if (callstack->isVisible()) {
                callstack->hide(); 
            }
            else {
                callstack->show();
            }
            updateWindowMenu();
            return 0;

        case MENU_WINDOW_MEMORY:
            if (memory->isVisible()) {
                memory->hide(); 
            }
            else {
                memory->show();
            }
            updateWindowMenu();
            return 0;

        case MENU_DEBUG_CONTINUE:
        case TB_RESUME:
            EmulatorRun();
            return 0;
            
        case MENU_DEBUG_BREAKALL:
        case TB_PAUSE:
            EmulatorPause();
            return 0;
            
        case MENU_DEBUG_STOP:
        case TB_STOP:
            EmulatorStop();
            return 0;
            
        case MENU_DEBUG_RESTART:
        case TB_RUN:
            EmulatorStop();
            EmulatorRun();
            return 0;
            
        case TB_SHOWNEXT:
            disassembly->updateScroll();
            return 0;
            
        case MENU_DEBUG_STEP:
        case TB_STEPIN:
            EmulatorStep();
            return 0;
            
        case MENU_DEBUG_RUNTO:
        case TB_RUNTO:
            disassembly->setRuntoBreakpoint();
            EmulatorRun();
            return 0;

        case MENU_DEBUG_GOTO:
             {
                WORD address = 0;
                BOOL rv = DialogBoxParam(GetDllHinstance(), MAKEINTRESOURCE(IDD_GOTO), hwnd, gotoProc, (LPARAM)&address);
                if (rv) {
                    disassembly->setCursor(address);
                }
            }
            return 0;

        case MENU_DEBUG_SHOWSYMBOLS:
            if (symbolInfo->getShowStatus()) {
                symbolInfo->hide();
            }
            else {
                symbolInfo->show();
            }
            disassembly->refresh();
            callstack->refresh();
            stack->refresh();
            updateWindowMenu();
            return 0;
            
        case MENU_DEBUG_BPTOGGLE:
        case TB_BPTOGGLE:
            disassembly->toggleBreakpoint();
            return 0;
            
        case MENU_DEBUG_BPENABLE:
        case TB_BPENABLE:
            disassembly->toggleBreakpointEnable();
            return 0;
            
        case MENU_DEBUG_BPREMOVEALL:
        case TB_BPREMALL:
            disassembly->clearAllBreakpoints();
            return 0;

        case MENU_DEBUG_BPENABLEALL:
        case TB_BPENALL:
            disassembly->enableAllBreakpoints();
            return 0;

        case MENU_DEBUG_BPDISABLEALL:
        case TB_BPDISALL:
            disassembly->disableAllBreakpoints();
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
        updateWindowMenu();
        updateDeviceState();
        return 0;

    case WM_ACTIVATE:
        isActive = wParam != WA_INACTIVE;
        if (isActive) {
#if 1
            RegisterHotKey(hwnd, 1,  0, VK_F5);
            RegisterHotKey(hwnd, 2,  MOD_CONTROL | MOD_ALT, VK_CANCEL);
            RegisterHotKey(hwnd, 3,  MOD_SHIFT, VK_F5);
            RegisterHotKey(hwnd, 4,  MOD_CONTROL | MOD_SHIFT, VK_F5);
            RegisterHotKey(hwnd, 5,  0, VK_F10);
            RegisterHotKey(hwnd, 6,  MOD_SHIFT, VK_F10);
            RegisterHotKey(hwnd, 7,  0, VK_F9);
            RegisterHotKey(hwnd, 8,  MOD_SHIFT, VK_F9);
            RegisterHotKey(hwnd, 9,  MOD_CONTROL | MOD_SHIFT, VK_F9);        
            RegisterHotKey(hwnd, 10, 0, VK_F8);     
            RegisterHotKey(hwnd, 11, MOD_CONTROL, 'G');
        }
        else {
            int i;
            for (i = 1; i <= 11; i++) {
                UnregisterHotKey(hwnd, i);
            }
        }
#endif
        break;

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
        disassembly->clearAllBreakpoints();
        dbgHwnd = NULL;
        delete statusBar;
        statusBar = NULL;
        delete toolBar;
        toolBar = NULL;
        viewHwnd = NULL;
        DestroyWindow(hwnd);
        delete disassembly;
        disassembly = NULL;
        delete cpuRegisters;
        cpuRegisters = NULL;
        delete callstack;
        callstack = NULL;
        delete stack;
        stack = NULL;
        delete memory;
        memory = NULL;
        delete symbolInfo;
        symbolInfo = NULL;
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
    if (dbgHwnd != NULL) {
        CloseWindow(dbgHwnd);
    }
}

void OnShowTool() {
    if (dbgHwnd != NULL) {
        return;
    }

    dbgHwnd = CreateWindow("msxdebugger", "blueMSX - Debugger", 
                           WS_OVERLAPPEDWINDOW, 
                           CW_USEDEFAULT, CW_USEDEFAULT, 800, 740, NULL, NULL, GetDllHinstance(), NULL);

    viewHwnd = CreateWindow("msxdebuggerview", "", 
                            WS_OVERLAPPED | WS_CHILD | WS_CLIPCHILDREN, CW_USEDEFAULT, CW_USEDEFAULT, 600, 500, dbgHwnd, NULL, GetDllHinstance(), NULL);

    ShowWindow(dbgHwnd, TRUE);
    ShowWindow(viewHwnd, TRUE);

    symbolInfo = new SymbolInfo;

    std::vector<int> fieldVector;
    fieldVector.push_back(0);
    fieldVector.push_back(70);
    fieldVector.push_back(20);
    statusBar = new StatusBar(GetDllHinstance(), dbgHwnd, fieldVector);
    updateStatusBar();
    statusBar->show();
    toolBar = initializeToolbar(dbgHwnd);
    toolBar->show();

    disassembly = new Disassembly(GetDllHinstance(), viewHwnd, symbolInfo);
    RECT r = { 3, 3, 437, 420 };
    disassembly->updatePosition(r);
    disassembly->show();

    cpuRegisters = new CpuRegisters(GetDllHinstance(), viewHwnd);
    RECT r2 = { 440, 3, 650, 190 };
    cpuRegisters->updatePosition(r2);
    cpuRegisters->show();

    callstack = new CallstackWindow(GetDllHinstance(), viewHwnd, disassembly);
    RECT r5 = { 440, 193, 650, 420 };
    callstack->updatePosition(r5);
    callstack->show();

    stack = new StackWindow(GetDllHinstance(), viewHwnd);
    RECT r6 = { 653, 3, 790, 420 };
    stack->updatePosition(r6);
    stack->show();

    memory = new Memory(GetDllHinstance(), viewHwnd, symbolInfo);
    RECT r3 = { 3, 423, 710, 630 };
    memory->updatePosition(r3);
    memory->show();
    updateWindowPositions();
    
    if (GetEmulatorState() == EMULATOR_PAUSED) {
        OnEmulatorPause();
    }

    updateToolBar();
    updateWindowMenu();
}

void OnEmulatorStart() {
    if (dbgHwnd != NULL) {
        disassembly->updateBreakpoints();
        disassembly->disableEdit();
        cpuRegisters->disableEdit();
        callstack->disableEdit();
        stack->disableEdit();
        memory->disableEdit();
        SendMessage(dbgHwnd, WM_STATUS, 0, 0);
    }
}

void OnEmulatorStop() {
    if (dbgHwnd != NULL) {
        disassembly->disableEdit();
        cpuRegisters->disableEdit();
        callstack->disableEdit();
        stack->disableEdit();
        memory->disableEdit();
        SendMessage(dbgHwnd, WM_STATUS, 0, 0);
    }
}

void OnEmulatorPause() {
    if (dbgHwnd != NULL) {
        disassembly->enableEdit();
        cpuRegisters->enableEdit();
        callstack->enableEdit();
        stack->enableEdit();
        memory->enableEdit();
        SendMessage(dbgHwnd, WM_STATUS, 0, 0);
    }
}

void OnEmulatorResume() {
    if (dbgHwnd != NULL) {
        disassembly->disableEdit();
        cpuRegisters->disableEdit();
        callstack->disableEdit();
        stack->disableEdit();
        memory->disableEdit();
        SendMessage(dbgHwnd, WM_STATUS, 0, 0);
    }
}

void OnEmulatorReset() {
}

void OnEmulatorTrace(const char* message)
{
}

void OnEmulatorSetBreakpoint(UInt16 address)
{
    if (disassembly != NULL) {
        disassembly->toggleBreakpoint(address, true);
    }
}

const char* OnGetName() {
    return "Debugger";
}
