#include <windows.h>
#include "ToolInterface.h"
#include "Resource.h"
#include "resrc1.h"
#include "Language.h"
#include <string>
#include <commctrl.h>
#include <list>
#include <sstream>
#include <iomanip>

enum CompareType
{
    CMP_EQUAL,
    CMP_NOTEQUAL,
    CMP_LESSTHAN,
    CMP_LESSOREQUAL,
    CMP_GRATERTHAN,
    CMP_GREATEROREQUAL,
};

enum DisplayType
{
    DPY_DECIMAL,
    DPY_HEXADECIMAL,
};

enum DataSize
{
    DATASIZE_8BIT,
    DATASIZE_16BIT,
};

enum CompareValue
{
    CMP_OLDVALUE,
    CMP_CHANGE,
    CMP_SPECIFIC,
};


using namespace std;

static HWND dbgHwnd = NULL;
static HWND hDlgSearch = NULL;
static HWND hDlgCheats = NULL;
static LanguageId langId = LID_ENGLISH;

static HBRUSH hBrush = NULL;

static CompareType  compareType    = CMP_EQUAL;
static DisplayType  displayType    = DPY_DECIMAL;
static DataSize     dataSize       = DATASIZE_8BIT;
static CompareValue compareValue   = CMP_SPECIFIC;
static Int32        cmpChangeVal   = 0;
static Int32        cmpSpecificVal = 0;

static bool canSearch   = false;
static bool canUndo     = false;
static bool canAddCheat = false;
static bool hasSnapshot = false;

static Int32 DataMask[]  = { 0xff, 0xffff };
static char* DpyFormat[] = { "%d", "%X" }; 
static char* DpySizeFormat[2][2]  = { { "%d", "%.2X" }, { "%d", "%.4X" } };

static UInt16 getData(DataSize dataSize, UInt8* mem, Int32 offset)
{
    if (dataSize == DATASIZE_16BIT) {
        return mem[offset] + 256 * mem[(offset + 1) & 0xffff];
    }
    return mem[offset];
}

static void setBtCheck(HWND hDlg, int id, bool check, bool enable = true) {
    HWND hwnd = GetDlgItem(hDlg, id);

    if (check) {
        SendMessage(hwnd, BM_SETCHECK, BST_CHECKED, 0);
    }
    else {
        SendMessage(hwnd, BM_SETCHECK, BST_UNCHECKED, 0);
    }
    if (!enable) {
        SendMessage(hwnd, BM_SETCHECK, BST_INDETERMINATE, 0);
    }
}

static int getBtCheck(HWND hDlg, int id) {
    HWND hwnd = GetDlgItem(hDlg, id);

    return BST_CHECKED == SendMessage(hwnd, BM_GETCHECK, 0, 0) ? 1 : 0;
}


struct SnapshotData
{
    UInt8 dataNew[0x10000];
    UInt8 dataOld[0x10000];
    UInt8 mask[0x10000];
    UInt8 maskRef[0x10000];
};

SnapshotData snapshotData;



#if 0
#define IDEDITCTL           100

#define MENU_FILE_EXIT              37100
#define MENU_FILE_LOG               37101
#define MENU_EDIT_SELECTALL         37200
#define MENU_EDIT_COPY              37201
#define MENU_EDIT_CLEAR             37202
#define MENU_HELP_ABOUT             37400

static void updateWindowMenu() 
{
    HMENU hMenuFile = CreatePopupMenu();
    
    AppendMenu(hMenuFile, MF_STRING, MENU_FILE_LOG, logFile == NULL ? Language::menuFileLogToFile : Language::menuFileStopLogToFile);
    AppendMenu(hMenuFile, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenuFile, MF_STRING, MENU_FILE_EXIT, Language::menuFileExit);
    
    HMENU hMenuEdit = CreatePopupMenu();
    AppendMenu(hMenuEdit, MF_STRING, MENU_EDIT_SELECTALL, Language::menuEditSelectAll);
    AppendMenu(hMenuEdit, MF_STRING, MENU_EDIT_COPY, Language::menuEditCopy);
    AppendMenu(hMenuEdit, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenuEdit, MF_STRING, MENU_EDIT_CLEAR, Language::menuEditClearWindow);

    HMENU hMenuHelp = CreatePopupMenu();
    AppendMenu(hMenuHelp, MF_STRING, MENU_HELP_ABOUT, Language::menuHelpAbout);

    static HMENU hMenu = NULL;
    if (hMenu != NULL) {
        DestroyMenu(hMenu);
    }

    hMenu = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuFile, Language::menuFile);
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuEdit, Language::menuEdit);
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuHelp, Language::menuHelp);
    
    SetMenu(dbgHwnd, hMenu);
}
#endif

static char* cheatFileDialog(HWND hwndOwner, bool openForSave)
{
    OPENFILENAME ofn; 
    static char fileName[MAX_PATH];

    fileName[0] = 0; 

    char  curDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, curDir);

    ofn.lStructSize = sizeof(OPENFILENAME); 
    ofn.hwndOwner = hwndOwner; 
    ofn.hInstance = GetDllHinstance();
    ofn.lpstrFilter = "*.MCF\0*.*\0\0"; 
    ofn.lpstrCustomFilter = NULL; 
    ofn.nMaxCustFilter = 0;
    ofn.nFilterIndex = 0; 
    ofn.lpstrFile = fileName; 
    ofn.nMaxFile = 1024; 
    ofn.lpstrFileTitle = NULL; 
    ofn.nMaxFileTitle = 0; 
    ofn.lpstrInitialDir = NULL; 
    ofn.nFileOffset = 0; 
    ofn.nFileExtension = 0; 
    ofn.lpstrDefExt = NULL; 
    ofn.lCustData = 0; 
    ofn.lpfnHook = NULL; 
    ofn.lpTemplateName = NULL; 

    BOOL rv = FALSE;
    if (openForSave) {
        ofn.lpstrTitle = Language::saveCheatCaption; 
        ofn.Flags = OFN_EXPLORER | OFN_ENABLESIZING | OFN_OVERWRITEPROMPT; 

        rv = GetSaveFileName(&ofn); 
    }
    else {
        ofn.lpstrTitle = Language::loadCheatCaption; 
        ofn.Flags = OFN_EXPLORER | OFN_ENABLESIZING | OFN_FILEMUSTEXIST; 

        rv = GetOpenFileName(&ofn); 
    }

    SetCurrentDirectory(curDir);

    if (!rv) {
        return NULL; 
    }

    return fileName;
}

void updateSnapshot(bool reset = false)
{
    if ((!hasSnapshot && !reset) || GetEmulatorState() == EMULATOR_RUNNING) {
        return;
    }

    Snapshot* snapshot = SnapshotCreate();
    if (snapshot != NULL) {
        int deviceCount = SnapshotGetDeviceCount(snapshot);

        for (int i = 0; i < deviceCount; i++) {
            Device* device = SnapshotGetDevice(snapshot, i);
            int memCount = DeviceGetMemoryBlockCount(device);

            if (device->type == DEVTYPE_CPU && memCount > 0) {
                MemoryBlock* mem = DeviceGetMemoryBlock(device, 0);
                if (mem->size == 0x10000) {
                    if (reset) {
                        memcpy(snapshotData.dataOld, mem->memory, 0x10000);
                        memset(snapshotData.mask,    1,           0x10000);
                        memset(snapshotData.maskRef, 1,           0x10000);
                    }
                    else {
                        memcpy(snapshotData.dataOld, snapshotData.dataNew, 0x10000);
                        memcpy(snapshotData.maskRef, snapshotData.mask,    0x10000);
                    }
                    memcpy(snapshotData.dataNew, mem->memory, 0x10000);
                    hasSnapshot = true;
                }
            }
        }
    }
    SnapshotDestroy(snapshot);
}


static void addAddress(HWND hwnd, int entry, UInt32 address, Int32 oldData, Int32 newData, Int32 diff) {
    char buffer[512] = {0};
    LV_ITEM lvi = {0};
    
    lvi.mask       = LVIF_TEXT;
    lvi.iItem      = entry;
    lvi.pszText    = buffer;
	lvi.cchTextMax = 512;

    sprintf(buffer, "%.4X", address);

    ListView_InsertItem(hwnd, &lvi);
    
    lvi.iSubItem++;
    sprintf(buffer, DpySizeFormat[dataSize][displayType], oldData);
    ListView_SetItem(hwnd, &lvi);
    
    lvi.iSubItem++;
    sprintf(buffer, DpySizeFormat[dataSize][displayType], newData);
    ListView_SetItem(hwnd, &lvi);
    
    lvi.iSubItem++;
    sprintf(buffer, DpySizeFormat[dataSize][displayType], diff);
    ListView_SetItem(hwnd, &lvi);
}

void updateListView()
{
    HWND hwnd = GetDlgItem(hDlgSearch, IDC_MEMLIST);
    ListView_DeleteAllItems(hwnd);

    if (!hasSnapshot) {
        return;
    }

    int idx = 0;

    for (int i = 0; i < 0x10000; i++) {
        if (snapshotData.mask[i]) {
            Int32 oldData = getData(dataSize, snapshotData.dataOld, i);
            Int32 newData = getData(dataSize, snapshotData.dataNew, i);
            if (displayType == DPY_DECIMAL) {
                addAddress(hwnd, idx++, i, oldData, newData, newData - oldData);
            }
            else {
                addAddress(hwnd, idx++, i, oldData, newData, (newData - oldData) & DataMask[dataSize]);
            }
        }
    }
}

struct SearchInfo
{
    CompareType  compareType;
    DataSize     dataSize;
    CompareValue compareValue;
    Int32        cmpChangeVal;
    Int32        cmpSpecificVal;

    SearchInfo(CompareType ct, DataSize ds, CompareValue cv, Int32 ccv, Int32 csv)
    : compareType(ct), dataSize(ds), compareValue(cv), cmpChangeVal(ccv), cmpSpecificVal(csv) {}

    bool operator==(const SearchInfo& si) {
        return si.compareType    == compareType  &&
               si.dataSize       == dataSize     &&
               si.compareValue   == compareValue &&
               si.cmpChangeVal   == cmpChangeVal &&
               si.cmpSpecificVal == cmpSpecificVal;
    }
};

typedef std::list<SearchInfo> SearchInfoList;
SearchInfoList searchInfoList;

void clearSearch()
{
    while(!searchInfoList.empty()) {
        searchInfoList.pop_front();
    }
    canUndo = false;
}

bool doSearch(CompareType  compareType, 
              DataSize     dataSize,
              CompareValue compareValue,
              Int32        cmpChangeVal,
              Int32        cmpSpecificVal,
              bool         addToUndoList = true)
{
    SearchInfo searchInfo(compareType, dataSize, compareValue, cmpChangeVal, cmpSpecificVal);

    if (addToUndoList) {
        if (!searchInfoList.empty()) {
            SearchInfo lastSearch = searchInfoList.back();
            if (searchInfo == lastSearch) {
                return false;
            }
        }
    }

    bool modified = false;

    for (Int32 i = 0; i < 0x10000; i++) {
        if (snapshotData.mask[i] == 0) {
            continue;
        }
        Int32 cmp1 = 0;
        Int32 cmp2 = 0;
        switch (compareValue) {
        case CMP_OLDVALUE:
            cmp1 = getData(dataSize, snapshotData.dataOld, i);
            cmp2 = getData(dataSize, snapshotData.dataNew, i);
            break;
        case CMP_CHANGE:
            cmp1 = cmpChangeVal;
            cmp2 = getData(dataSize, snapshotData.dataNew, i) - getData(dataSize, snapshotData.dataOld, i);
            break;
        case CMP_SPECIFIC:
            cmp1 = cmpSpecificVal;
            cmp2 = getData(dataSize, snapshotData.dataNew, i);
            break;
        }

        UInt8 oldMask = snapshotData.mask[i];
        switch (compareType) {
        case CMP_EQUAL:
            snapshotData.mask[i] = (cmp2 == cmp1);
            break;
        case CMP_NOTEQUAL:
            snapshotData.mask[i] = (cmp2 != cmp1);
            break;
        case CMP_LESSTHAN:
            snapshotData.mask[i] = (cmp2 < cmp1);
            break;
        case CMP_LESSOREQUAL:
            snapshotData.mask[i] = (cmp2 <= cmp1);
            break;
        case CMP_GRATERTHAN:
            snapshotData.mask[i] = (cmp2 > cmp1);
            break;
        case CMP_GREATEROREQUAL:
            snapshotData.mask[i] = (cmp2 >= cmp1);
            break;
        }

        modified |= snapshotData.mask[i] != oldMask;
    }

    if (addToUndoList) {
        if (modified) {        
            searchInfoList.push_back(searchInfo);
            canUndo = true;
        }
    }
    return modified;
}

bool undoSearch()
{
    if (searchInfoList.empty()) {
        return false;
    }
    searchInfoList.pop_back();

    memcpy(snapshotData.mask, snapshotData.maskRef, 0x10000);

    for (SearchInfoList::iterator i = searchInfoList.begin(); i != searchInfoList.end(); ++i) {
        doSearch(i->compareType, i->dataSize, i->compareValue, i->cmpChangeVal, i->cmpSpecificVal, false);
    }

    canUndo = !searchInfoList.empty();
    return true;
}


void updateButtons(HWND hDlg)
{
    EnableWindow(GetDlgItem(hDlgSearch, IDC_MEMLIST),  GetEmulatorState() == EMULATOR_PAUSED);
    EnableWindow(GetDlgItem(hDlgSearch, IDC_SNAPSHOT), GetEmulatorState() == EMULATOR_PAUSED);
    EnableWindow(GetDlgItem(hDlgSearch, IDC_SEARCH),   GetEmulatorState() == EMULATOR_PAUSED && hasSnapshot);
    EnableWindow(GetDlgItem(hDlgSearch, IDC_UNDO),     GetEmulatorState() == EMULATOR_PAUSED && canUndo);
    EnableWindow(GetDlgItem(hDlgSearch, IDC_ADDCHEAT), GetEmulatorState() == EMULATOR_PAUSED && canAddCheat);
}

void updateSearchFields(HWND hDlg)
{
    setBtCheck(hDlg, IDC_CMP_EQUAL,          compareType == CMP_EQUAL);
    setBtCheck(hDlg, IDC_CMP_NOTEQUAL,       compareType == CMP_NOTEQUAL);
    setBtCheck(hDlg, IDC_CMP_LESSTHAN,       compareType == CMP_LESSTHAN);
    setBtCheck(hDlg, IDC_CMP_LESSOREQUAL,    compareType == CMP_LESSOREQUAL);
    setBtCheck(hDlg, IDC_CMP_GREATERTHAN,    compareType == CMP_GRATERTHAN);
    setBtCheck(hDlg, IDC_CMP_GREATEROREQUAL, compareType == CMP_GREATEROREQUAL);
    
    setBtCheck(hDlg, IDC_VAL_DEC, displayType == DPY_DECIMAL);
    setBtCheck(hDlg, IDC_VAL_HEX, displayType == DPY_HEXADECIMAL);
    
    setBtCheck(hDlg, IDC_VAL_8BIT,  dataSize == DATASIZE_8BIT);
    setBtCheck(hDlg, IDC_VAL_16BIT, dataSize == DATASIZE_16BIT);
    
    setBtCheck(hDlg, IDC_CMP_OLDVAL,    compareValue == CMP_OLDVALUE);
    setBtCheck(hDlg, IDC_CMP_CHANGE,    compareValue == CMP_CHANGE);
    setBtCheck(hDlg, IDC_CMP_SPECIFIC,  compareValue == CMP_SPECIFIC);

    EnableWindow(GetDlgItem(hDlg, IDC_CMP_VALCHANGE),   compareValue == CMP_CHANGE);
    EnableWindow(GetDlgItem(hDlg, IDC_CMP_VALSPECIFIC), compareValue == CMP_SPECIFIC);

    char buffer[32];
    
    sprintf(buffer, DpyFormat[displayType], cmpChangeVal & DataMask[dataSize]);
    SetWindowText(GetDlgItem(hDlg, IDC_CMP_VALCHANGE), buffer);

    sprintf(buffer, DpyFormat[displayType], cmpSpecificVal & DataMask[dataSize]);
    SetWindowText(GetDlgItem(hDlg, IDC_CMP_VALSPECIFIC), buffer);
}

void checkNumberInput(HWND hDlg, int id, DisplayType displayType, DataSize dataSize, Int32* value)
{
    static bool isUpdating = false;

    if (isUpdating) {
        return;
    }

    isUpdating = true;
    char buffer[16];
    GetWindowText(GetDlgItem(hDlg, id), buffer, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = 0;

    bool isEmpty = strlen(buffer) == 0;
    bool negOnly = strcmp(buffer, "-") == 0 || strcmp(buffer, "0-") == 0;

    if (negOnly) {
        strcpy(buffer, "-");
        *value = 0;
    }
    else if (isEmpty) {
        *value = 0;
    }
    else {
        bool valid = true;
        for (UInt32 i = 0; i < strlen(buffer); i++) {
            if (displayType == DPY_DECIMAL) {
                valid &= (buffer[i] >= '0' && buffer[i] <= '9') || 
                          buffer[0] == '-';
            }
            else {
                valid &= (buffer[i] >= '0' && buffer[i] <= '9') ||
                        (buffer[i] >= 'A' && buffer[i] <= 'F') ||
                        (buffer[i] >= 'a' && buffer[i] <= 'f');
            }
        }

        if (valid) {
            Int32 val;
            if (buffer[0] == '-') {
                sscanf(buffer + 1, DpyFormat[displayType], &val);
                if (val <= DataMask[dataSize]) {
                    *value = -val;
                }
            }
            else {
                sscanf(buffer, DpyFormat[displayType], &val);
                if (val <= DataMask[dataSize]) {
                    *value = val;
                }
            }
        }

        UInt32 selStart = 0;
        UInt32 selEnd = 0;
        SendDlgItemMessage(hDlg, id, EM_GETSEL, (WPARAM)&selStart, (LPARAM)&selEnd);
        if (*value < 0) {
            sprintf(buffer, DpyFormat[displayType], -1 * (-1 * *value & DataMask[dataSize]));
        }
        else {
            sprintf(buffer, DpyFormat[displayType], *value & DataMask[dataSize]);
        }
    }
    SetWindowText(GetDlgItem(hDlg, id), buffer);
    SendDlgItemMessage(hDlg, id, EM_SETSEL, 8, 8);
    isUpdating = false;
}

static BOOL CALLBACK searchProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    static int currIndex;

    switch (iMsg) {
    case WM_INITDIALOG:
        {
            char buffer[32];
            LV_COLUMN lvc = {0};
            
            currIndex = -1;
    
            HWND hwnd = GetDlgItem(hDlg, IDC_MEMLIST);

            ListView_SetExtendedListViewStyle(hwnd, LVS_EX_FULLROWSELECT);

            lvc.mask       = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
            lvc.fmt        = LVCFMT_LEFT;
            lvc.cx         = 100;
            lvc.pszText    = buffer;
	        lvc.cchTextMax = 32;

            sprintf(buffer, "Address");
            lvc.cx = 108;
            ListView_InsertColumn(hwnd, 0, &lvc);
            sprintf(buffer, "Old Value");
            lvc.cx = 75;
            ListView_InsertColumn(hwnd, 1, &lvc);
            sprintf(buffer, "New Value");
            lvc.cx = 75;
            ListView_InsertColumn(hwnd, 2, &lvc);
            sprintf(buffer, "Change");
            lvc.cx = 75;
            ListView_InsertColumn(hwnd, 3, &lvc);
        }

        updateSearchFields(hDlg);

        return FALSE;

    case WM_COMMAND:
        {
            DisplayType  oldDisplayType = displayType;
            DataSize     oldDataSize    = dataSize;

            switch (LOWORD(wParam)) {
            case IDC_CMP_EQUAL:          compareType  = CMP_EQUAL;          break;
            case IDC_CMP_NOTEQUAL:       compareType  = CMP_NOTEQUAL;       break;
            case IDC_CMP_LESSTHAN:       compareType  = CMP_LESSTHAN;       break;
            case IDC_CMP_LESSOREQUAL:    compareType  = CMP_LESSOREQUAL;    break;
            case IDC_CMP_GREATERTHAN:    compareType  = CMP_GRATERTHAN;     break;
            case IDC_CMP_GREATEROREQUAL: compareType  = CMP_GREATEROREQUAL; break;
            case IDC_VAL_DEC:            displayType  = DPY_DECIMAL;        break;
            case IDC_VAL_HEX:            displayType  = DPY_HEXADECIMAL;    break;
            case IDC_VAL_8BIT:           dataSize     = DATASIZE_8BIT;      break;
            case IDC_VAL_16BIT:          dataSize     = DATASIZE_16BIT;     break;
            case IDC_CMP_OLDVAL:         compareValue = CMP_OLDVALUE;       break;
            case IDC_CMP_CHANGE:         compareValue = CMP_CHANGE;         break;
            case IDC_CMP_SPECIFIC:       compareValue = CMP_SPECIFIC;       break;
            case IDC_CMP_VALCHANGE:
                checkNumberInput(hDlg, IDC_CMP_VALCHANGE, displayType, dataSize, &cmpChangeVal);
                break;

            case IDC_CMP_VALSPECIFIC:
                checkNumberInput(hDlg, IDC_CMP_VALSPECIFIC, displayType, dataSize, &cmpSpecificVal);
                break;
            }

            if (oldDisplayType != displayType || oldDataSize != dataSize) {
                updateListView();
            }
        }

        switch (LOWORD(wParam)) {
        case IDC_VAL_DEC:
        case IDC_VAL_HEX:
        case IDC_VAL_8BIT:
        case IDC_VAL_16BIT:
        case IDC_CMP_OLDVAL:
        case IDC_CMP_CHANGE:
        case IDC_CMP_SPECIFIC:
            {
                EnableWindow(GetDlgItem(hDlg, IDC_CMP_VALCHANGE),   compareValue == CMP_CHANGE);
                EnableWindow(GetDlgItem(hDlg, IDC_CMP_VALSPECIFIC), compareValue == CMP_SPECIFIC);

                char buffer[32];
                
                sprintf(buffer, DpyFormat[displayType], cmpChangeVal & DataMask[dataSize]);
                SetWindowText(GetDlgItem(hDlg, IDC_CMP_VALCHANGE), buffer);

                sprintf(buffer, DpyFormat[displayType], cmpSpecificVal & DataMask[dataSize]);
                SetWindowText(GetDlgItem(hDlg, IDC_CMP_VALSPECIFIC), buffer);
            }
            break;

        case IDC_SNAPSHOT:
            updateSnapshot(true);
            clearSearch();
            updateListView();
            updateButtons(dbgHwnd);
            break;

        case IDC_SEARCH:
            if (doSearch(compareType, dataSize, compareValue, cmpChangeVal, cmpSpecificVal)) {
                updateListView();
            }
            updateButtons(dbgHwnd);
            break;

        case IDC_UNDO:
            if (undoSearch()) {
                updateListView();
            }
            updateButtons(dbgHwnd);
            break;

        case IDC_ADDCHEAT:
            break;
        }
        return TRUE;

    case WM_NOTIFY:
        switch (wParam) {
        case IDC_MEMLIST:
            if ((((NMHDR FAR *)lParam)->code) == LVN_ITEMCHANGED) {
                HWND hwnd = GetDlgItem(hDlg, IDC_MEMLIST);

                if (ListView_GetSelectedCount(hwnd)) {
                    int index = ListView_GetNextItem(hwnd, -1, LVNI_SELECTED);

                    if (currIndex == -1 && index != -1) {
                        canAddCheat = true;
                        updateButtons(hDlg);
                    }
                    currIndex = index;
                }
                else {
                    if (currIndex != -1) {
                        canAddCheat = false;
                        updateButtons(hDlg);
                    }
                    currIndex = -1;
                }
            }

            if ((((NMHDR FAR *)lParam)->code) == LVN_ITEMACTIVATE) {
                HWND hwnd = GetDlgItem(hDlg, IDC_MEMLIST);

                if (ListView_GetSelectedCount(hwnd)) {
                    int index = ListView_GetNextItem(hwnd, -1, LVNI_SELECTED);
                    // Add cheat here
                }
                return TRUE;
            }
        }
        break;

    case WM_CTLCOLORBTN:
    case WM_CTLCOLORSTATIC:
        SetBkColor((HDC)wParam, GetSysColor(COLOR_3DLIGHT));
        return (BOOL)hBrush;

    case WM_ERASEBKGND:
        return TRUE;
    }
    return FALSE;
}

////////////////////////////////////////////////////////////////////////

static void addCheat(HWND hwnd, int entry, char* description, bool enable, UInt32 address, 
                     Int32 value, DataSize dataSize, DisplayType displayType)
{
    char buffer[512] = {0};
    LV_ITEM lvi = {0};
    
    lvi.mask       = LVIF_TEXT;
    lvi.iItem      = entry;
    lvi.pszText    = description;
	lvi.cchTextMax = 512;

    ListView_InsertItem(hwnd, &lvi);
    
    lvi.mask       = LVIF_TEXT;
    lvi.pszText    = buffer;

    lvi.iSubItem++;
    sprintf(buffer, "%.4x", address);
    ListView_SetItem(hwnd, &lvi);
    
    lvi.iSubItem++;
    sprintf(buffer, DpySizeFormat[dataSize][displayType], value);
    ListView_SetItem(hwnd, &lvi);

    ListView_SetCheckState(hwnd, entry, enable);
}


static BOOL CALLBACK cheatsProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    static int currIndex;

    switch (iMsg) {
    case WM_INITDIALOG:
        {
//            HBITMAP hIcon = LoadBitmap(GetDllHinstance(), MAKEINTRESOURCE(IDB_TRAINER));
//            SendDlgItemMessage(hDlg, IDC_OPEN, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hIcon);
            HICON hIcon = LoadIcon(GetDllHinstance(), MAKEINTRESOURCE(IDI_OPEN));
            SendDlgItemMessage(hDlg, IDC_OPEN, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);

            hIcon = LoadIcon(GetDllHinstance(), MAKEINTRESOURCE(IDI_SAVE));
            SendDlgItemMessage(hDlg, IDC_SAVE, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
                        char buffer[32];
            LV_COLUMN lvc = {0};
            

            HWND hwnd = GetDlgItem(hDlg, IDC_CHEATLIST);

            ListView_SetExtendedListViewStyle(hwnd, LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);

            lvc.mask       = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
            lvc.fmt        = LVCFMT_LEFT;
            lvc.pszText    = buffer;
	        lvc.cchTextMax = 32;

            sprintf(buffer, "Description");
            lvc.cx = 225;
            ListView_InsertColumn(hwnd, 0, &lvc);
            sprintf(buffer, "Address");
            lvc.cx = 65;
            ListView_InsertColumn(hwnd, 1, &lvc);
            sprintf(buffer, "Value");
            lvc.cx = 60;
            ListView_InsertColumn(hwnd, 2, &lvc);

            addCheat(hwnd, 0, "Cheat Number one", true, 0x1234, 156, DATASIZE_8BIT, DPY_HEXADECIMAL);
            addCheat(hwnd, 1, "Another cheat", false, 0x8423, 33, DATASIZE_8BIT, DPY_HEXADECIMAL);
        }

        return FALSE;

    case WM_CTLCOLORBTN:
    case WM_CTLCOLORSTATIC:
        SetBkColor((HDC)wParam, GetSysColor(COLOR_3DLIGHT));
        return (BOOL)hBrush;

    case WM_ERASEBKGND:
        return TRUE;
    }
    return FALSE;
}

////////////////////////////////////////////////////////////////////////

static BOOL CALLBACK trainerProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (iMsg) {
    case WM_INITDIALOG:
        if (hBrush == NULL) {
            hBrush = CreateSolidBrush(GetSysColor(COLOR_3DLIGHT));
        }

        hDlgSearch  = CreateDialog(GetDllHinstance(), MAKEINTRESOURCE(IDD_SEARCH),  GetDlgItem(hDlg, IDC_TAB), searchProc);
        SetWindowPos(hDlgSearch,  NULL, 3, 24, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

        hDlgCheats  = CreateDialog(GetDllHinstance(), MAKEINTRESOURCE(IDD_CHEATS),  GetDlgItem(hDlg, IDC_TAB), cheatsProc);
        SetWindowPos(hDlgCheats,  NULL, 3, 24, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

        ShowWindow(hDlgCheats, SW_NORMAL);

        {
            TCITEM tcItem = { TCIF_TEXT, 0, 0, 0, 0, -1, 0 };

            tcItem.pszText = "Active Cheats ";
            TabCtrl_InsertItem(GetDlgItem(hDlg, IDC_TAB), 0, &tcItem);
            
            tcItem.pszText = "Find Cheats ";
            TabCtrl_InsertItem(GetDlgItem(hDlg, IDC_TAB), 1, &tcItem);
        }
        return FALSE;

    case WM_NOTIFY:
        switch (wParam) {
        case IDC_TAB:
            if ((((NMHDR FAR *)lParam)->code) == TCN_SELCHANGE) {
                ShowWindow(hDlgSearch,  SW_HIDE);
                ShowWindow(hDlgCheats,  SW_HIDE);
                switch(TabCtrl_GetCurSel(GetDlgItem(hDlg, IDC_TAB))) {
                case 0:
                default:
                    ShowWindow(hDlgCheats, SW_NORMAL);
                    break;
                case 1:
                    ShowWindow(hDlgSearch, SW_NORMAL);
                    break;
                }
            }
            break;
        }
        break;
        
    case WM_CLOSE:
        hasSnapshot = false;
        ShowWindow(dbgHwnd, SW_HIDE); 
        return TRUE;
    }
    return FALSE;
}


void OnCreateTool() {
}

void OnDestroyTool() {
    if (dbgHwnd != NULL) {
        DestroyWindow(dbgHwnd);
    }
}

void OnShowTool() {
    if (dbgHwnd == NULL) {
        dbgHwnd = CreateDialog(GetDllHinstance(), MAKEINTRESOURCE(IDD_TRAINER), NULL, trainerProc); 
        DWORD dw = GetLastError();
        dw = dw;
    }

    ShowWindow(dbgHwnd, SW_SHOW); 

    canAddCheat = false;
    
    updateListView();
    updateButtons(dbgHwnd);

    Language::SetLanguage(langId);
}

void OnEmulatorStart() {
    updateButtons(dbgHwnd);
}

void OnEmulatorStop() {
    updateButtons(dbgHwnd);
}

void OnEmulatorPause() {
    updateSnapshot();
    clearSearch();
    updateListView();
    updateButtons(dbgHwnd);
}

void OnEmulatorResume() {
    updateButtons(dbgHwnd);
}

void OnEmulatorReset() {
}

void OnEmulatorTrace(const char* message)
{
}

void OnEmulatorSetBreakpoint(UInt16 address) {
}

void OnEmulatorSetBreakpoint(UInt16 slot, UInt16 address) {
}

void OnEmulatorSetBreakpoint(UInt16 slot, UInt16 page, UInt16 address) {
}

const char* OnGetName() {
    return Language::trainerName;
}

void OnSetLanguage(LanguageId languageId)
{
    langId = languageId;
    Language::SetLanguage(langId);
}
