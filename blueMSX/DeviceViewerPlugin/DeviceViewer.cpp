#include <windows.h>
#include "ToolInterface.h"
#include "Resource.h"
#include "resrc1.h"
#include <string>
#include <commctrl.h>
#include <sstream>
#include <iomanip>

using namespace std;

static HWND deviceViewerHwnd = NULL;

#define WM_STATUS (WM_USER + 0)

HTREEITEM addChild ( HWND hwnd, HTREEITEM parent, char *pszText, int imageIndex )
{
	tagTVINSERTSTRUCTA insertStruct;
	tagTVITEMA treeItem;
 
	treeItem.mask = TVIF_TEXT | TVIF_IMAGE;
	treeItem.cchTextMax			= strlen ( pszText );
	treeItem.pszText			= strdup ( pszText );
	treeItem.iImage				= imageIndex;
	treeItem.iSelectedImage		= imageIndex;	 

	insertStruct.hParent		= parent;
	insertStruct.hInsertAfter	= 0;
	insertStruct.item			= treeItem;
	
	// insert the item
	return TreeView_InsertItem ( hwnd, &insertStruct );
}


void SetDeviceInfoString2 ( HWND hDlg )
{
	
	HTREEITEM nodeDeviceName;

	HWND Tree;
	
	Tree = GetDlgItem ( hDlg, IDC_DEVICETREE );
	TreeView_DeleteAllItems ( Tree );

	HTREEITEM nodeCpu = NULL;
	HTREEITEM nodeRam = NULL;
	HTREEITEM nodeBios = NULL;
	HTREEITEM nodeCart = NULL;
	HTREEITEM nodeVideo = NULL;
	HTREEITEM nodeAudio = NULL;
	HTREEITEM nodeIoPort = NULL;
	HTREEITEM nodeOther = NULL;
	
	Snapshot* snapshot = SnapshotCreate();
    if (snapshot != NULL) {
        int deviceCount = SnapshotGetDeviceCount(snapshot);

		for (int i = 0; i < deviceCount; i++) {
            Device* device = SnapshotGetDevice(snapshot, i);
            int j;

            HTREEITEM treeItem = NULL;

            switch (device->type) {
            default:
            case DEVTYPE_UNKNOWN:
		        if (nodeOther  == NULL) nodeOther  = addChild ( Tree, 0, "Other", 0 );
                treeItem = nodeOther;
                break;
            case DEVTYPE_CPU:
		        if (nodeCpu    == NULL) nodeCpu    = addChild ( Tree, 0, "CPU", 0 );
                treeItem = nodeCpu;
                break;
            case DEVTYPE_CART: 
		        if (nodeCart   == NULL) nodeCart   = addChild ( Tree, 0, "Cartridges", 0 );
                treeItem = nodeCart;
                break;
            case DEVTYPE_BIOS: 
		        if (nodeBios   == NULL) nodeBios   = addChild ( Tree, 0, "BIOS", 0 );
                treeItem = nodeBios;
                break;
            case DEVTYPE_RAM:
		        if (nodeRam    == NULL) nodeRam    = addChild ( Tree, 0, "RAM Memory", 0 );
                treeItem = nodeRam;
                break;
            case DEVTYPE_AUDIO:
		        if (nodeAudio  == NULL) nodeAudio  = addChild ( Tree, 0, "Audio Devices", 0 );
                treeItem = nodeAudio;
                break;
            case DEVTYPE_VIDEO:
		        if (nodeVideo  == NULL) nodeVideo  = addChild ( Tree, 0, "Video Devices", 0 );
                treeItem = nodeVideo;
                break;
            case DEVTYPE_IOPORT:
		        if (nodeIoPort == NULL) nodeIoPort = addChild ( Tree, 0, "I/O Ports", 0 );
                treeItem = nodeIoPort;
                break;
            }
			
			nodeDeviceName = addChild ( Tree, treeItem, device->name, 0 );

            int memCount = DeviceGetMemoryBlockCount(device);

            for (j = 0; j < memCount; j++) {
				
                MemoryBlock* mem = DeviceGetMemoryBlock(device, j);
			
				char buffer [50];
				
				HTREEITEM nodeMemoryItem = addChild ( Tree, nodeDeviceName, mem->name, 0 );
				sprintf ( buffer, "Size: 0x%X", mem->size );
				HTREEITEM nodeMemorySize = addChild ( Tree, nodeMemoryItem, buffer, 0 );
				sprintf ( buffer, "Start: 0x%X", mem->startAddress );
				HTREEITEM nodeMemoryAddress = addChild ( Tree, nodeMemoryItem, buffer, 0 );
				
            }
            
            int regBankCount = DeviceGetRegisterBankCount(device);

            for (j = 0; j < regBankCount; j++) {
                RegisterBank* regBank = DeviceGetRegisterBank(device, j);
                
				HTREEITEM nodeRegsItem = addChild ( Tree, nodeDeviceName, regBank->name, 0 );

                for (UInt32 k = 0; k < regBank->count; k++) {
				    char buffer [50];
                    if (regBank->reg[k].width == 8) 
				        sprintf ( buffer, "%s: 0x%.2X", regBank->reg[k].name, regBank->reg[k].value );
                    else if (regBank->reg[k].width == 16)
				        sprintf ( buffer, "%s: 0x%.4X", regBank->reg[k].name, regBank->reg[k].value );
                    else
				        sprintf ( buffer, "%s: 0x%.8X", regBank->reg[k].name, regBank->reg[k].value );

				    HTREEITEM nodeMemorySize = addChild ( Tree, nodeRegsItem, buffer, 0 );
                }
            }
            
            int ioPortsCount = DeviceGetIoPortsCount(device);
            
            for (j = 0; j < ioPortsCount; j++) {
                IoPorts* ioPorts = DeviceGetIoPorts(device, j);
                
				HTREEITEM nodeRegsItem = addChild ( Tree, nodeDeviceName, ioPorts->name, 0 );

                for (UInt32 k = 0; k < ioPorts->count; k++) {
				    char buffer [50];
				    sprintf ( buffer, "Port %0X%2X: 0x%.2x", k, ioPorts->port[k].value );

				    HTREEITEM nodeMemorySize = addChild ( Tree, nodeRegsItem, buffer, 0 );
                }
            }
        }

        SnapshotDestroy(snapshot);
    }

}

void SetDeviceInfoString(HWND hDlg)
{
    stringstream devInfo;
    
    Snapshot* snapshot = SnapshotCreate();
    if (snapshot != NULL) {
        int deviceCount = SnapshotGetDeviceCount(snapshot);

        for (int i = 0; i < deviceCount; i++) {
            Device* device = SnapshotGetDevice(snapshot, i);
            int j;

            devInfo << device->name << "\r\n";

            int memCount = DeviceGetMemoryBlockCount(device);
            for (j = 0; j < memCount; j++) {
                MemoryBlock* mem = DeviceGetMemoryBlock(device, j);
                devInfo << "   Memory: " << mem->name << " Size: 0x" << hex << mem->size << "\r\n";
            }

            int regBankCount = DeviceGetRegisterBankCount(device);
            for (j = 0; j < regBankCount; j++) {
                RegisterBank* regBank = DeviceGetRegisterBank(device, j);
                devInfo << "   Registers: " << regBank->name << "\r\n";

                for (UInt32 k = 0; k < regBank->count; k++) {
                    devInfo << "      " << regBank->reg[k].name << "  " << hex << setw(regBank->reg[k].width / 4) << setfill('0') << regBank->reg[k].value << "\r\n";
                }
            }

            int ioPortsCount = DeviceGetIoPortsCount(device);
            for (j = 0; j < ioPortsCount; j++) {
                IoPorts* ioPorts = DeviceGetIoPorts(device, j);
                devInfo << "   IO Ports: " << ioPorts->name << "\r\n";

                for (UInt32 k = 0; k < ioPorts->count; k++) {
                    devInfo << "      Port 0x" << hex << ioPorts->port[k].port << "  0x" << ioPorts->port[k].value << "\r\n";
                }
            }
        }

        SnapshotDestroy(snapshot);
    }

    SendDlgItemMessage(hDlg, ID_DEVICEINFO, WM_SETTEXT, 0, (LPARAM)devInfo.str().c_str());
}

void SetDeviceStatus(HWND hDlg) 
{
    string statusString = "Status: ";
    switch (GetEmulatorState()) {
    case EMULATOR_STOPPED: statusString += "STOPPED"; break;
    case EMULATOR_PAUSED:  statusString += "PAUSED";  break;
    case EMULATOR_RUNNING: statusString += "RUNNING"; break;
    }

    SetWindowText(GetDlgItem(hDlg, IDC_APEARANCETHEMETEXT), statusString.c_str());
}

static void SizeDialogItems(HWND hDlg)
{
    RECT r;
    int height;
    int width;
    HWND hwnd;

    GetClientRect(hDlg, &r);
    
    height = r.bottom - r.top;
    width  = r.right - r.left;

    hwnd = GetDlgItem(hDlg, IDC_DEVICETREE);
    SetWindowPos(hwnd, NULL, 0, 32, width, height - 32, SWP_NOZORDER);

    hwnd = GetDlgItem(hDlg, IDC_APEARANCETHEMETEXT);
    SetWindowPos(hwnd, NULL, width - 100, 7, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    hwnd = GetDlgItem(hDlg, ID_REFRESH);
    SetWindowPos(hwnd, NULL, 10, 5, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

static BOOL CALLBACK dlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (iMsg) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_REFRESH:
            //SetDeviceInfoString(hDlg);
			SetDeviceInfoString2 ( hDlg );
            return TRUE;
        }
        break;

    case WM_STATUS:
        SetDeviceStatus(hDlg);
		SetDeviceInfoString2 ( hDlg );
        //SetDeviceInfoString(hDlg);

        return 0;

    case WM_SIZE:
        SizeDialogItems(hDlg);
        return TRUE;

    case WM_CLOSE:
        deviceViewerHwnd = NULL;
        EndDialog(hDlg, TRUE);
		
        return TRUE;

    case WM_INITDIALOG:

		SetDeviceInfoString2 ( hDlg );
        //SetDeviceInfoString(hDlg);
        SetDeviceStatus(hDlg);
        SizeDialogItems(hDlg);
        ShowWindow(hDlg, SW_SHOW);
        return FALSE;
    }

    return FALSE;
}

void CreateTool() {
}

void DestroyTool() {
}

static void ShowError() {
    LPVOID lpMsgBuf;
    if (!FormatMessage( 
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM | 
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPTSTR) &lpMsgBuf,
        0,
        NULL ))
    {
        // Handle the error.
        return;
    }

    // Process any inserts in lpMsgBuf.
    // ...

    // Display the string.
    MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );

    // Free the buffer.
    LocalFree( lpMsgBuf );
}

void ShowTool() {
    if (deviceViewerHwnd != NULL) {
        return;
    }

    deviceViewerHwnd = CreateDialog(GetDllHinstance(), MAKEINTRESOURCE(IDD_DEVICEVIEWER), NULL, dlgProc);
}

void EmulatorStart() {    
    if (deviceViewerHwnd != NULL) {
        SendMessage(deviceViewerHwnd, WM_STATUS, 0, 0);
    }
}

void EmulatorStop() {
    if (deviceViewerHwnd != NULL) {
        SendMessage(deviceViewerHwnd, WM_STATUS, 0, 0);
    }
}

void EmulatorPause() {
    if (deviceViewerHwnd != NULL) {
        SendMessage(deviceViewerHwnd, WM_STATUS, 0, 0);
    }
}

void EmulatorResume() {
    if (deviceViewerHwnd != NULL) {
        SendMessage(deviceViewerHwnd, WM_STATUS, 0, 0);
    }
}

const char* GetName() {
    return "Device Viewer";
}
