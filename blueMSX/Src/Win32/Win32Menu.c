/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Menu.c,v $
**
** $Revision: 1.17 $
**
** $Date: 2005-05-17 04:50:31 $
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
#include <tchar.h>
#include <stdio.h>
#include "Win32Menu.h"
#include "Win32ToolLoader.h"
#include "FileHistory.h"
#include "LaunchFile.h"
#include "Resource.h"
#include "Language.h"
#include "Board.h"
#include "archMenu.h"
#include "Actions.h"
#include "Casette.h"
#include "VideoManager.h"
#include "ArchControls.h"
#include "ArchNotifications.h"


#define ID_FILE                         40010
#define ID_FILE_LOAD                    40011
#define ID_FILE_SAVE                    40012
#define ID_FILE_QLOAD                   40013
#define ID_FILE_QSAVE                   40014
#define ID_LOG_WAV                      40015
#define ID_PRT_SCR                      40016
#define ID_FILE_EXIT                    40017

#define ID_FILE_INSERT_CARTRIDGEA       40018
#define ID_FILE_INSERT_CARTRIDGEB       40019
#define ID_FILE_REMOVE_CARTRIDGEA       40020
#define ID_FILE_REMOVE_CARTRIDGEB       40021
#define ID_FILE_CARTRIDGE_AUTORESET     40022
#define ID_FILE_INSERT_DISKETTEA        40023
#define ID_FILE_INSERT_DISKETTEDIRA     40024
#define ID_FILE_INSERT_DISKETTEA_RESET  40025
#define ID_FILE_INSERT_DISKETTEB        40026
#define ID_FILE_INSERT_DISKETTEDIRB     40027
#define ID_FILE_REMOVE_DISKETTEA        40028
#define ID_FILE_REMOVE_DISKETTEB        40029
#define ID_FILE_INSERT_CASSETTE         40030
#define ID_FILE_REMOVE_CASSETTE         40031
#define ID_FILE_REWIND_CASSETTE         40032
#define ID_FILE_POSITION_CASSETTE       40033
#define ID_FILE_SAVE_CASSETTE           40034
#define ID_FILE_READONLY_CASSETTE       40035
#define ID_FILE_AUTOREWNIND_CASSETTE    40036
#define ID_FILE_CARTA_FMPAC             40037
#define ID_FILE_CARTB_FMPAC             40038
#define ID_FILE_CARTA_PAC               40039
#define ID_FILE_CARTB_PAC               40040
#define ID_FILE_CARTA_MEGARAM128        40041
#define ID_FILE_CARTB_MEGARAM128        40042
#define ID_FILE_CARTA_MEGARAM256        40043
#define ID_FILE_CARTB_MEGARAM256        40044
#define ID_FILE_CARTA_MEGARAM512        40045
#define ID_FILE_CARTB_MEGARAM512        40046
#define ID_FILE_CARTA_MEGARAM768        40047
#define ID_FILE_CARTB_MEGARAM768        40048
#define ID_FILE_CARTA_MEGARAM2M         40049
#define ID_FILE_CARTB_MEGARAM2M         40050
#define ID_FILE_CARTA_SNATCHER          40051
#define ID_FILE_CARTB_SNATCHER          40052
#define ID_FILE_CARTA_SDSNATCHER        40053
#define ID_FILE_CARTB_SDSNATCHER        40054
#define ID_FILE_CARTA_SCCMIRRORED       40055
#define ID_FILE_CARTB_SCCMIRRORED       40056
#define ID_FILE_CARTA_SCCEXPANDED       40057
#define ID_FILE_CARTB_SCCEXPANDED       40058
#define ID_FILE_CARTA_SCC               40059
#define ID_FILE_CARTB_SCC               40060
#define ID_FILE_CARTA_SCCPLUS           40061
#define ID_FILE_CARTB_SCCPLUS           40062
#define ID_FILE_CARTA_EXTRAM512KB       40063
#define ID_FILE_CARTB_EXTRAM512KB       40064
#define ID_FILE_CARTA_EXTRAM1MB         40065
#define ID_FILE_CARTB_EXTRAM1MB         40066
#define ID_FILE_CARTA_EXTRAM2MB         40067
#define ID_FILE_CARTB_EXTRAM2MB         40068
#define ID_FILE_CARTA_EXTRAM4MB         40069
#define ID_FILE_CARTB_EXTRAM4MB         40070
#define ID_FILE_CARTA_SONYHBI55         40071
#define ID_FILE_CARTB_SONYHBI55         40072
#define ID_VIDEO_AUTODETECT             40073
#define ID_FILE_PRINTER_FORMFEED        40074

#define ID_CARTRIDGEA_HISTORY           30000
#define ID_CARTRIDGEB_HISTORY           30050
#define ID_DISKDRIVEA_HISTORY           30100
#define ID_DISKDRIVEB_HISTORY           30150
#define ID_CASSETTE_HISTORY             30200
#define ID_VIDEO_CONNECTORS             30250
#define ID_CTRLPORT1_BASE               30300
#define ID_CTRLPORT2_BASE               30350
#define ID_TOOLPLUGINS                  30400

#define ID_RUN_RUN                      40081
#define ID_RUN_PAUSE                    40082
#define ID_RUN_STOP                     40083
#define ID_RUN_RESET                    40084
#define ID_RUN_SOFTRESET                40085
#define ID_RUN_CLEANRESET               40086

#define ID_SIZE_NORMAL                  40157
#define ID_SIZE_X2                      40158
#define ID_SIZE_FULLSCREEN              40159
#define ID_SIZE_MINIMIZED               40160

#define ID_OPTIONS_EMULATION            40121
#define ID_OPTIONS_AUDIO                40122
#define ID_OPTIONS_VIDEO                40123
#define ID_OPTIONS_CONTROLS             40124
#define ID_OPTIONS_PERFORMANCE          40125
#define ID_OPTIONS_SETTINGS             40126
#define ID_OPTIONS_LANGUAGE             40127
#define ID_OPTIONS_APEARANCE            40128
#define ID_OPTIONS_PORTS                40129

#define ID_HELP_HELP                    40151
#define ID_HELP_ABOUT                   40152

#define ID_TOOLS_MACHINEEDITOR          40154
#define ID_TOOLS_SHORTCUTSEDITOR        40155
#define ID_TOOLS_KEYBOARDEDITOR         40156




#ifndef MIM_BACKGROUND
#define MIM_BACKGROUND              0x00000002
#endif

typedef struct {
    int focused;
    unsigned int x;
    unsigned int y;
    unsigned int w;
    unsigned int h;
    char* text;
    void (*action)(int, int);
} MenuInfo;


static HWND     menuHwnd       = NULL;
static HWND     parentHwnd     = NULL;
static HBRUSH   menuBrush      = NULL;
static COLORREF menuText       = 0;
static HBRUSH   menuFocusBrush = NULL;
static int      menuItemCount  = 0;
static int      menuX          = 0;
static int      menuY          = 0;
static int      menuDown       = -1;
static int      menuPending    = 0;
static MenuInfo menuInfo[10];

static HMENU hMenuReset = NULL;
static HMENU hMenuCartSpecialA = NULL;
static HMENU hMenuCartSpecialB = NULL;
static HMENU hMenuVideoConnect = NULL;
static HMENU hMenuCartA = NULL;
static HMENU hMenuCartB = NULL;
static HMENU hMenuRun = NULL;
static HMENU hMenuDiskA = NULL;
static HMENU hMenuDiskB = NULL;
static HMENU hMenuCasette = NULL;
static HMENU hMenuPrinter = NULL;
static HMENU hMenuControlsPort1 = NULL;
static HMENU hMenuControlsPort2 = NULL;
static HMENU hMenuZoom = NULL;
static HMENU hMenuOptions = NULL;
static HMENU hMenuHelp = NULL;
static HMENU hMenuFile = NULL;
static HMENU hMenuTools = NULL;


HMENU menuCreateOptions(Properties* pProperties, Shortcuts* shortcuts);
HMENU menuCreateHelp(Properties* pProperties, Shortcuts* shortcuts);
HMENU menuCreateFile(Properties* pProperties, Shortcuts* shortcuts, int isStopped, int logSound, int tempStateExits, int enableSpecial);
HMENU menuCreateTools(Properties* pProperties, Shortcuts* shortcuts);


static void showPopupMenu(HMENU hMenu, int x, int y)
{
    int flags = 0;
    if (x == -1 && y == -1) {
        RECT r;
        GetWindowRect(parentHwnd, &r);
        x = (r.left + r.right) / 2;
        y =  (r.top + r.bottom) / 2;
        flags = TPM_CENTERALIGN;
    }
    else {
        POINT pt = {x, y};
        ClientToScreen(parentHwnd, &pt);
        x = pt.x;
        y = pt.y;
    }

    enterDialogShow();
    TrackPopupMenu(hMenu, 0, x, y, flags, parentHwnd, NULL);
    exitDialogShow();
}

static void setMenuColor(HMENU hMenu) 
{
    MENUINFO mi;

    mi.cbSize = sizeof(mi);
    mi.fMask = MIM_BACKGROUND;
    mi.hbrBack = menuBrush;
//    SetMenuInfo(hMenu, &mi);
}

static HMENU menuCreateReset(Properties* pProperties, Shortcuts* shortcuts) {
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();
    
    setMenuColor(hMenu);

    _stprintf(langBuffer, "%s        \t%hs", langMenuRunHardReset(), shortcutsToString(shortcuts->resetHard));
    AppendMenu(hMenu, MF_STRING, ID_RUN_RESET, langBuffer);
//    ModifyMenu(hMenu, 0, MF_BYPOSITION | MF_OWNERDRAW, 0, NULL);
    _stprintf(langBuffer, "%s        \t%hs", langMenuRunSoftReset(), shortcutsToString(shortcuts->resetSoft));
    AppendMenu(hMenu, MF_STRING, ID_RUN_SOFTRESET, langBuffer);
    _stprintf(langBuffer, "%s        \t%hs", langMenuRunCleanReset(), shortcutsToString(shortcuts->resetClean));
    AppendMenu(hMenu, MF_STRING, ID_RUN_CLEANRESET, langBuffer);

    return hMenu;
}

static HMENU menuCreateVideoConnect(Properties* pProperties, Shortcuts* shortcuts) 
{
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();

    int count = videoManagerGetCount();
    int i;

    if (count == 0) {
        _stprintf(langBuffer, "%s", langMenuVideoSourceDefault());
        AppendMenu(hMenu, MF_STRING | MF_GRAYED, ID_VIDEO_CONNECTORS + 0, langBuffer);
    }

    for (i = 0; i < count; i++) {
        _stprintf(langBuffer, "%s        ", videoManagerGetName(i));
        AppendMenu(hMenu, MF_STRING | (videoManagerIsActive(i) ? MFS_CHECKED : 0), ID_VIDEO_CONNECTORS + i, langBuffer);
    }
    
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    
    _stprintf(langBuffer, "%s", langMenuVideoChipAutodetect());
    AppendMenu(hMenu, MF_STRING | (count > 1 ? (pProperties->video.chipAutodetect ? MFS_CHECKED : 0) : MF_GRAYED), ID_VIDEO_AUTODETECT, langBuffer);

    return hMenu;
}

static HMENU menuCreateCartSpecialA(Properties* pProperties, Shortcuts* shortcuts) {
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();

    setMenuColor(hMenu);

#if 0
    _stprintf(langBuffer, "%s", langMenuCartSnatcher());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_SNATCHER, langBuffer);

    _stprintf(langBuffer, "%s", langMenuCartSdSnatcher());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_SDSNATCHER, langBuffer);

    _stprintf(langBuffer, "%s", langMenuCartSCCMirrored());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_SCCMIRRORED, langBuffer);

    _stprintf(langBuffer, "%s", langMenuCartSCCExpanded());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_SCCEXPANDED, langBuffer);
#endif

    _stprintf(langBuffer, "%s", langMenuCartSCC());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_SCC, langBuffer);

    _stprintf(langBuffer, "%s", langMenuCartSCCPlus());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_SCCPLUS, langBuffer);
    
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s", langMenuCartFMPac());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_FMPAC, langBuffer);

    _stprintf(langBuffer, "%s", langMenuCartPac());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_PAC, langBuffer);
    
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s", langMenuCartHBI55());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_SONYHBI55, langBuffer);
    
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s", "External RAM 512 kB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_EXTRAM512KB, langBuffer);

    _stprintf(langBuffer, "%s", "External RAM 1 MB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_EXTRAM1MB, langBuffer);

    _stprintf(langBuffer, "%s", "External RAM 2 MB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_EXTRAM2MB, langBuffer);

    _stprintf(langBuffer, "%s", "External RAM 4 MB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_EXTRAM4MB, langBuffer);
    
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s", "MegaRAM 128 kB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_MEGARAM128, langBuffer);

    _stprintf(langBuffer, "%s", "MegaRAM 256 kB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_MEGARAM256, langBuffer);

    _stprintf(langBuffer, "%s", "MegaRAM 512 kB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_MEGARAM512, langBuffer);

    _stprintf(langBuffer, "%s", "MegaRAM 768 kB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_MEGARAM768, langBuffer);

    _stprintf(langBuffer, "%s", "MegaRAM 2 MB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTA_MEGARAM2M, langBuffer);

    return hMenu;
}

static HMENU menuCreateCartA(Properties* pProperties, Shortcuts* shortcuts, int enableSpecial) {
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();
    int i;

    setMenuColor(hMenu);

    _stprintf(langBuffer, "%s      \t%hs", langMenuCartInsert(), shortcutsToString(shortcuts->cartInsert1));
    AppendMenu(hMenu, MF_STRING, ID_FILE_INSERT_CARTRIDGEA, langBuffer);

    _stprintf(langBuffer, "%s%hs%hs", langMenuCartRemove(), (*pProperties->cartridge.slotA ? ": " : ""), stripPath(pProperties->cartridge.slotA));
    AppendMenu(hMenu, MF_STRING | (*pProperties->cartridge.slotA ? 0 : MF_GRAYED), ID_FILE_REMOVE_CARTRIDGEA, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s", langMenuCartAutoReset());
    AppendMenu(hMenu, MF_STRING | (pProperties->cartridge.autoReset ? MFS_CHECKED : 0), ID_FILE_CARTRIDGE_AUTORESET, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    if (*pProperties->filehistory.cartridgeA[0] == 0) {
        _stprintf(langBuffer, "%s", langMenuCartNoRecentFiles());
        AppendMenu(hMenu, MF_STRING | MF_GRAYED,  0, langBuffer);
    }

    verifyFileHistory(*pProperties->filehistory.cartridgeA,
                      pProperties->filehistory.cartridgeTypeA);

    for (i = 0; i < pProperties->filehistory.count && *pProperties->filehistory.cartridgeA[i]; i++) {
        _stprintf(langBuffer, "%hs", stripPath(pProperties->filehistory.cartridgeA[i]));
        AppendMenu(hMenu, MF_STRING, ID_CARTRIDGEA_HISTORY + i, langBuffer);
    }

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s", langMenuCartSpecial());
    if (enableSpecial) {
        AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreateCartSpecialA(pProperties, shortcuts), langBuffer);
    }
    else {
        AppendMenu(hMenu, MF_STRING | MF_GRAYED,  0, langBuffer);
    }

    return hMenu;
}

static HMENU menuCreateCartSpecialB(Properties* pProperties, Shortcuts* shortcuts) {
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();

    setMenuColor(hMenu);

#if 0
    _stprintf(langBuffer, "%s", langMenuCartSnatcher());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_SNATCHER, langBuffer);

    _stprintf(langBuffer, "%s", langMenuCartSdSnatcher());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_SDSNATCHER, langBuffer);

    _stprintf(langBuffer, "%s", langMenuCartSCCMirrored());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_SCCMIRRORED, langBuffer);

    _stprintf(langBuffer, "%s", langMenuCartSCCExpanded());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_SCCEXPANDED, langBuffer);
#endif

    _stprintf(langBuffer, "%s", langMenuCartSCC());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_SCC, langBuffer);

    _stprintf(langBuffer, "%s", langMenuCartSCCPlus());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_SCCPLUS, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s", langMenuCartFMPac());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_FMPAC, langBuffer);

    _stprintf(langBuffer, "%s", langMenuCartPac());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_PAC, langBuffer);
    
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s", langMenuCartHBI55());
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_SONYHBI55, langBuffer);
    
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s", "External RAM 512 kB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_EXTRAM512KB, langBuffer);

    _stprintf(langBuffer, "%s", "External RAM 1 MB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_EXTRAM1MB, langBuffer);

    _stprintf(langBuffer, "%s", "External RAM 2 MB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_EXTRAM2MB, langBuffer);

    _stprintf(langBuffer, "%s", "External RAM 4 MB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_EXTRAM4MB, langBuffer);
    
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s", "MegaRAM 128 kB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_MEGARAM128, langBuffer);

    _stprintf(langBuffer, "%s", "MegaRAM 256 kB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_MEGARAM256, langBuffer);

    _stprintf(langBuffer, "%s", "MegaRAM 512 kB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_MEGARAM512, langBuffer);

    _stprintf(langBuffer, "%s", "MegaRAM 768 kB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_MEGARAM768, langBuffer);

    _stprintf(langBuffer, "%s", "MegaRAM 2 MB");
    AppendMenu(hMenu, MF_STRING, ID_FILE_CARTB_MEGARAM2M, langBuffer);

    return hMenu;
}

static HMENU menuCreateCartB(Properties* pProperties, Shortcuts* shortcuts, int enableSpecial) {
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();
    int i;

    setMenuColor(hMenu);

    _stprintf(langBuffer, "%s      \t%hs", langMenuCartInsert(), shortcutsToString(shortcuts->cartInsert2));
    AppendMenu(hMenu, MF_STRING, ID_FILE_INSERT_CARTRIDGEB, langBuffer);

    _stprintf(langBuffer, "%s%hs%hs", langMenuCartRemove(), (*pProperties->cartridge.slotB ? ": " : ""), stripPath(pProperties->cartridge.slotB));
    AppendMenu(hMenu, MF_STRING | (*pProperties->cartridge.slotB ? 0 : MF_GRAYED), ID_FILE_REMOVE_CARTRIDGEB, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s", langMenuCartAutoReset());
    AppendMenu(hMenu, MF_STRING | (pProperties->cartridge.autoReset ? MFS_CHECKED : 0), ID_FILE_CARTRIDGE_AUTORESET, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    if (*pProperties->filehistory.cartridgeB[0] == 0) {
        _stprintf(langBuffer, "%s", langMenuCartNoRecentFiles());
        AppendMenu(hMenu, MF_STRING | MF_GRAYED,  0, langBuffer);
    }

    verifyFileHistory(*pProperties->filehistory.cartridgeB,
                      pProperties->filehistory.cartridgeTypeB);

    for (i = 0; i < pProperties->filehistory.count && *pProperties->filehistory.cartridgeB[i]; i++) {
        _stprintf(langBuffer, "%hs", stripPath(pProperties->filehistory.cartridgeB[i]));
        AppendMenu(hMenu, MF_STRING, ID_CARTRIDGEB_HISTORY + i, langBuffer);
    }

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s", langMenuCartSpecial());
    if (enableSpecial) {
        AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreateCartSpecialB(pProperties, shortcuts), langBuffer);
    }
    else {
        AppendMenu(hMenu, MF_STRING | MF_GRAYED,  0, langBuffer);
    }

    return hMenu;
}

static HMENU menuCreateDiskA(Properties* pProperties, Shortcuts* shortcuts) {
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();
    int i;

    setMenuColor(hMenu);

    _stprintf(langBuffer, "%s      \t%hs", langMenuDiskInsert(), shortcutsToString(shortcuts->diskInsertA));
    AppendMenu(hMenu, MF_STRING, ID_FILE_INSERT_DISKETTEA, langBuffer);

    _stprintf(langBuffer, "%s      \t%hs", langMenuDiskDirInsert(), shortcutsToString(shortcuts->diskDirInsertA));
    AppendMenu(hMenu, MF_STRING, ID_FILE_INSERT_DISKETTEDIRA, langBuffer);

    _stprintf(langBuffer, "%s%hs%hs", langMenuDiskEject(), (*pProperties->diskdrive.slotA ? ": " : ""), stripPath(pProperties->diskdrive.slotA));
    AppendMenu(hMenu, MF_STRING | (*pProperties->diskdrive.slotA ? 0 : MF_GRAYED), ID_FILE_REMOVE_DISKETTEA, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s", langMenuDiskAutoStart());
    AppendMenu(hMenu, MF_STRING | (pProperties->diskdrive.autostartA ? MFS_CHECKED : 0), ID_FILE_INSERT_DISKETTEA_RESET, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    if (*pProperties->filehistory.diskdriveA[0] == 0) {
        _stprintf(langBuffer, "%s", langMenuDiskNoRecentFiles());
        AppendMenu(hMenu, MF_STRING | MF_GRAYED,  0, langBuffer);
    }

    verifyFileHistory(*pProperties->filehistory.diskdriveA, NULL);

    for (i = 0; i < pProperties->filehistory.count && *pProperties->filehistory.diskdriveA[i]; i++) {
        _stprintf(langBuffer, "%hs", stripPath(pProperties->filehistory.diskdriveA[i]));
        AppendMenu(hMenu, MF_STRING, ID_DISKDRIVEA_HISTORY + i, langBuffer);
    }

    return hMenu;
}

static HMENU menuCreateDiskB(Properties* pProperties, Shortcuts* shortcuts) {
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();
    int i;

    setMenuColor(hMenu);

    _stprintf(langBuffer, "%s      \t%hs", langMenuDiskInsert(), shortcutsToString(shortcuts->diskInsertB));
    AppendMenu(hMenu, MF_STRING, ID_FILE_INSERT_DISKETTEB, langBuffer);

    _stprintf(langBuffer, "%s      \t%hs", langMenuDiskDirInsert(), shortcutsToString(shortcuts->diskDirInsertB));
    AppendMenu(hMenu, MF_STRING, ID_FILE_INSERT_DISKETTEDIRB, langBuffer);

    _stprintf(langBuffer, "%s%hs%hs", langMenuDiskEject(), (*pProperties->diskdrive.slotB ? ": " : ""), stripPath(pProperties->diskdrive.slotB));
    AppendMenu(hMenu, MF_STRING | (*pProperties->diskdrive.slotB ? 0 : MF_GRAYED), ID_FILE_REMOVE_DISKETTEB, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    if (*pProperties->filehistory.diskdriveB[0] == 0) {
        _stprintf(langBuffer, "%s", langMenuDiskNoRecentFiles());
        AppendMenu(hMenu, MF_STRING | MF_GRAYED,  0, langBuffer);
    }

    verifyFileHistory(*pProperties->filehistory.diskdriveB, NULL);
    
    for (i = 0; i < pProperties->filehistory.count && *pProperties->filehistory.diskdriveB[i]; i++) {
        _stprintf(langBuffer, "%hs", stripPath(pProperties->filehistory.diskdriveB[i]));
        AppendMenu(hMenu, MF_STRING, ID_DISKDRIVEB_HISTORY + i, langBuffer);
    }

    return hMenu;
}

static HMENU menuCreatePrinter(Properties* pProperties, Shortcuts* shortcuts) {
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();

    setMenuColor(hMenu);

    _stprintf(langBuffer, "%s      \t%hs", langMenuPrnFormfeed(), shortcutsToString(shortcuts->prnFormFeed));
    AppendMenu(hMenu, MF_STRING, ID_FILE_PRINTER_FORMFEED, langBuffer);

    return hMenu;
}

static HMENU menuCreateCassette(Properties* pProperties, Shortcuts* shortcuts) {
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();
    int i;

    setMenuColor(hMenu);

    _stprintf(langBuffer, "%s      \t%hs", langMenuCasInsert(), shortcutsToString(shortcuts->casInsert));
    AppendMenu(hMenu, MF_STRING, ID_FILE_INSERT_CASSETTE, langBuffer);

    _stprintf(langBuffer, "%s%hs%hs", langMenuCasEject(), (*pProperties->cassette.tape ? ": " : ""), stripPath(pProperties->cassette.tape));
    AppendMenu(hMenu, MF_STRING | (*pProperties->cassette.tape ? 0 : MF_GRAYED), ID_FILE_REMOVE_CASSETTE, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, langMenuCasRewindAfterInsert());
    AppendMenu(hMenu, MF_STRING | (pProperties->cassette.autoRewind ? MFS_CHECKED : 0), ID_FILE_AUTOREWNIND_CASSETTE, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, langMenuCasUseReadOnly());
    AppendMenu(hMenu, MF_STRING | (pProperties->cassette.readOnly ? MFS_CHECKED : 0), ID_FILE_READONLY_CASSETTE, langBuffer);

    _stprintf(langBuffer, "%s", langMenuCasSaveAs());
    AppendMenu(hMenu, MF_STRING | (*pProperties->cassette.tape ? 0 : MF_GRAYED), ID_FILE_SAVE_CASSETTE, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s      \t%hs", langMenuCasSetPosition(), shortcutsToString(shortcuts->casSetPos));
    AppendMenu(hMenu, MF_STRING | (*pProperties->cassette.tape ? 0 : MF_GRAYED), ID_FILE_POSITION_CASSETTE, langBuffer);

    _stprintf(langBuffer, "%s      \t%hs", langMenuCasRewind(), shortcutsToString(shortcuts->casRewind));
    AppendMenu(hMenu, MF_STRING | (*pProperties->cassette.tape ? 0 : MF_GRAYED), ID_FILE_REWIND_CASSETTE, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    if (*pProperties->filehistory.cassette[0] == 0) {
        _stprintf(langBuffer, "%s", langMenuCasNoRecentFiles());
        AppendMenu(hMenu, MF_STRING | MF_GRAYED,  0, langBuffer);
    }

    verifyFileHistory(*pProperties->filehistory.cassette, NULL);

    for (i = 0; i < pProperties->filehistory.count && *pProperties->filehistory.cassette[i]; i++) {
        _stprintf(langBuffer, "%hs", stripPath(pProperties->filehistory.cassette[i]));
        AppendMenu(hMenu, MF_STRING, ID_CASSETTE_HISTORY + i, langBuffer);
    }

    return hMenu;
}

static HMENU menuCreateControlsPort1(Properties* pProperties, Shortcuts* shortcuts) {
    HMENU           hMenu = CreatePopupMenu();
    PropControlsJoy joyType = pProperties->joy1.type;
    int             hwType  = joyType == P_JOY_HW ? pProperties->joy1.hwType : -1;
    int i;

    setMenuColor(hMenu);

    AppendMenu(hMenu, MF_STRING | (joyType == P_JOY_NONE ? MFS_CHECKED : 0), 
               ID_CTRLPORT1_BASE + 0, langEnumControlsJoyNone());
    AppendMenu(hMenu, MF_STRING | (joyType == P_JOY_MOUSE ? MFS_CHECKED : 0), 
               ID_CTRLPORT1_BASE + 1, langEnumControlsJoyMouse());
    AppendMenu(hMenu, MF_STRING | (joyType == P_JOY_NUMPAD ? MFS_CHECKED : 0), 
               ID_CTRLPORT1_BASE + 2, langEnumControlsJoyNumpad());
    AppendMenu(hMenu, MF_STRING | (joyType == P_JOY_KEYSET ? MFS_CHECKED : 0), 
               ID_CTRLPORT1_BASE + 3, langEnumControlsJoyKeyset());
    AppendMenu(hMenu, MF_STRING | (joyType == P_JOY_TETRISDONGLE ? MFS_CHECKED : 0), 
               ID_CTRLPORT1_BASE + 4, langEnumControlsJoyTetrisDongle());
    
    for (i = 0; i < archJoystickGetCount(); i++) {
        AppendMenu(hMenu, MF_STRING | (hwType == i ? MFS_CHECKED : 0), 
                ID_CTRLPORT1_BASE + 5 + i, archJoystickGetName(i));
    }
    
    return hMenu;
}

static HMENU menuCreateControlsPort2(Properties* pProperties, Shortcuts* shortcuts) {
    HMENU           hMenu = CreatePopupMenu();
    PropControlsJoy joyType = pProperties->joy2.type;
    int             hwType  = joyType == P_JOY_HW ? pProperties->joy2.hwType : -1;
    int i;

    setMenuColor(hMenu);

    AppendMenu(hMenu, MF_STRING | (joyType == P_JOY_NONE ? MFS_CHECKED : 0), 
               ID_CTRLPORT2_BASE + 0, langEnumControlsJoyNone());
    AppendMenu(hMenu, MF_STRING | (joyType == P_JOY_MOUSE ? MFS_CHECKED : 0), 
               ID_CTRLPORT2_BASE + 1, langEnumControlsJoyMouse());
    AppendMenu(hMenu, MF_STRING | (joyType == P_JOY_NUMPAD ? MFS_CHECKED : 0), 
               ID_CTRLPORT2_BASE + 2, langEnumControlsJoyNumpad());
    AppendMenu(hMenu, MF_STRING | (joyType == P_JOY_KEYSET ? MFS_CHECKED : 0), 
               ID_CTRLPORT2_BASE + 3, langEnumControlsJoyKeyset());
    AppendMenu(hMenu, MF_STRING | (joyType == P_JOY_TETRISDONGLE ? MFS_CHECKED : 0), 
               ID_CTRLPORT2_BASE + 4, langEnumControlsJoyTetrisDongle());

    for (i = 0; i < archJoystickGetCount(); i++) {
        AppendMenu(hMenu, MF_STRING | (hwType == i ? MFS_CHECKED : 0), 
                ID_CTRLPORT2_BASE + 5 + i, archJoystickGetName(i));
    }
    
    return hMenu;
}

static HMENU menuCreateZoom(Properties* pProperties, Shortcuts* shortcuts) {
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();

    setMenuColor(hMenu);

    _stprintf(langBuffer, "%s      \t%hs", langMenuZoomNormal(), shortcutsToString(shortcuts->windowSizeSmall));
    AppendMenu(hMenu, MF_STRING | (pProperties->video.size == P_VIDEO_SIZEX1 ? MFS_CHECKED : 0), ID_SIZE_NORMAL, langBuffer);

    _stprintf(langBuffer, "%s      \t%hs", langMenuZoomDouble(), shortcutsToString(shortcuts->windowSizeNormal));
    AppendMenu(hMenu, MF_STRING | (pProperties->video.size == P_VIDEO_SIZEX2 ? MFS_CHECKED : 0), ID_SIZE_X2, langBuffer);

    _stprintf(langBuffer, "%s      \t%hs", langMenuZoomFullscreen(), shortcutsToString(shortcuts->windowSizeFullscreen));
    AppendMenu(hMenu, MF_STRING | (pProperties->video.size == P_VIDEO_SIZEFULLSCREEN ? MFS_CHECKED : 0), ID_SIZE_FULLSCREEN, langBuffer);

    return hMenu;
}

static HMENU menuCreateOptions(Properties* pProperties, Shortcuts* shortcuts) {
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();

    setMenuColor(hMenu);

    _stprintf(langBuffer, "%s", langMenuVideoSource());
    AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreateVideoConnect(pProperties, shortcuts), langBuffer);
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s", langMenuPropsEmulation());
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_EMULATION, langBuffer);

    _stprintf(langBuffer, "%s", langMenuPropsVideo());
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_VIDEO, langBuffer);

    _stprintf(langBuffer, "%s", langMenuPropsSound());
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_AUDIO, langBuffer);

    _stprintf(langBuffer, "%s", langMenuPropsControls());
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_CONTROLS, langBuffer);

    _stprintf(langBuffer, "%s", langMenuPropsPerformance());
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_PERFORMANCE, langBuffer);

    _stprintf(langBuffer, "%s", langMenuPropsFile());
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_SETTINGS, langBuffer);

    _stprintf(langBuffer, "%s", langMenuPropsSettings());
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_APEARANCE, langBuffer);

    _stprintf(langBuffer, "%s", langMenuPropsPorts());
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_PORTS, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s", langMenuPropsLanguage());
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_LANGUAGE, langBuffer);

    return hMenu;
}

static HMENU menuCreateHelp(Properties* pProperties, Shortcuts* shortcuts) {
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();

    setMenuColor(hMenu);

    _stprintf(langBuffer, "%s", langMenuHelpHelp());
    AppendMenu(hMenu, MF_STRING, ID_HELP_HELP, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s", langMenuHelpAbout());
    AppendMenu(hMenu, MF_STRING, ID_HELP_ABOUT, langBuffer);

    return hMenu;
}

static HMENU menuCreateTools(Properties* pProperties, Shortcuts* shortcuts) {
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();
    int count;

    setMenuColor(hMenu);

    _stprintf(langBuffer, "%s", langMenuToolsMachine());
    AppendMenu(hMenu, MF_STRING, ID_TOOLS_MACHINEEDITOR, langBuffer);
    
    _stprintf(langBuffer, "%s", langMenuToolsShortcuts());
    AppendMenu(hMenu, MF_STRING, ID_TOOLS_SHORTCUTSEDITOR, langBuffer);

    _stprintf(langBuffer, "%s", langMenuToolsKeyboard());
    AppendMenu(hMenu, MF_STRING, ID_TOOLS_KEYBOARDEDITOR, langBuffer);

    count = toolGetCount();

    if (count > 0) {
        int i;

        AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

        for (i = 0; i < count; i++) {
            _stprintf(langBuffer, "%s", toolInfoGetName(toolInfoGet(i)));
            AppendMenu(hMenu, MF_STRING, ID_TOOLPLUGINS + i, langBuffer);
        }
    }
    
    return hMenu;
}

static HMENU menuCreateFile(Properties* pProperties, Shortcuts* shortcuts, int isStopped, int logSound, int tempStateExits, int enableSpecial) {
    HMENU hMenu = CreatePopupMenu();
    _TCHAR menuBuffer[512];

    setMenuColor(hMenu);

    _stprintf(menuBuffer, "%s", langMenuFileCart1());
    AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreateCartA(pProperties, shortcuts, enableSpecial), menuBuffer);

    _stprintf(menuBuffer, "%s", langMenuFileCart2());
    AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreateCartB(pProperties, shortcuts, enableSpecial), menuBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(menuBuffer, "%s", langMenuFileDiskA());
    AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreateDiskA(pProperties, shortcuts), menuBuffer);

    _stprintf(menuBuffer, "%s", langMenuFileDiskB());
    AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreateDiskB(pProperties, shortcuts), menuBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(menuBuffer, "%s", langMenuFileCas());
    AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreateCassette(pProperties, shortcuts), menuBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(menuBuffer, "%s", langMenuFilePrn());
    AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreatePrinter(pProperties, shortcuts), menuBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(menuBuffer, "%s        \t%hs", langMenuFileLoadState(), shortcutsToString(shortcuts->cpuStateLoad));
    AppendMenu(hMenu, MF_STRING, ID_FILE_LOAD, menuBuffer);

    _stprintf(menuBuffer, "%s        \t%hs", langMenuFileSaveState(), shortcutsToString(shortcuts->cpuStateSave));
    AppendMenu(hMenu, MF_STRING | (!isStopped ? 0 : MF_GRAYED), ID_FILE_SAVE, menuBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(menuBuffer, "%s        \t%hs", langMenuFileQLoadState(), shortcutsToString(shortcuts->cpuStateQuickLoad));
    AppendMenu(hMenu, MF_STRING | (tempStateExits ? 0 : MF_GRAYED), ID_FILE_QLOAD, menuBuffer);

    _stprintf(menuBuffer, "%s        \t%hs", langMenuFileQSaveState(), shortcutsToString(shortcuts->cpuStateQuickSave));
    AppendMenu(hMenu, MF_STRING | (!isStopped ? 0 : MF_GRAYED), ID_FILE_QSAVE, menuBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(menuBuffer, "%s        \t%hs", langMenuFileCaptureAudio(), shortcutsToString(shortcuts->wavCapture));
    AppendMenu(hMenu, MF_STRING | (logSound ? MFS_CHECKED : 0), ID_LOG_WAV, menuBuffer);

    _stprintf(menuBuffer, "%s        \t%hs", langMenuFileScreenShot(), shortcutsToString(shortcuts->screenCapture));
    AppendMenu(hMenu, MF_STRING, ID_PRT_SCR, menuBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);  

    _stprintf(menuBuffer, "%s        \t%hs", langMenuFileExit(), shortcutsToString(shortcuts->quit));
    AppendMenu(hMenu, MF_STRING, ID_FILE_EXIT, menuBuffer);

    return hMenu;
}

static HMENU menuCreateRun(Properties* pProperties, Shortcuts* shortcuts, int isRunning, int isStopped) {
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();

    setMenuColor(hMenu);

    if (isRunning) {
        _stprintf(langBuffer, "%s        \t%hs", langMenuRunPause(), shortcutsToString(shortcuts->emulationRunPause));
        AppendMenu(hMenu, MF_STRING, ID_RUN_RUN, langBuffer);
    }
    else {
        _stprintf(langBuffer, "%s        \t%hs", langMenuRunRun(), shortcutsToString(shortcuts->emulationRunPause));
        AppendMenu(hMenu, MF_STRING, ID_RUN_RUN, langBuffer);
    }

    _stprintf(langBuffer, "%s        \t%hs", langMenuRunStop(), shortcutsToString(shortcuts->emulationStop));
    AppendMenu(hMenu, MF_STRING | (!isStopped ? 0 : MF_GRAYED), ID_RUN_STOP, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s        \t%hs", langMenuRunHardReset(), shortcutsToString(shortcuts->resetHard));
    AppendMenu(hMenu, MF_STRING, ID_RUN_RESET, langBuffer);

    _stprintf(langBuffer, "%s        \t%hs", langMenuRunSoftReset(), shortcutsToString(shortcuts->resetSoft));
    AppendMenu(hMenu, MF_STRING, ID_RUN_SOFTRESET, langBuffer);

    _stprintf(langBuffer, "%s        \t%hs", langMenuRunCleanReset(), shortcutsToString(shortcuts->resetClean));
    AppendMenu(hMenu, MF_STRING, ID_RUN_CLEANRESET, langBuffer);

    return hMenu;
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////


static void menuDrawItem(HDC hdc, MenuInfo* mi, int focused) 
{
    HBRUSH hBrush = (HBRUSH)SelectObject(hdc, focused ? menuFocusBrush : menuBrush);

    Rectangle(hdc, mi->x, mi->y, mi->x + mi->w, mi->y + mi->h); 

    TextOut(hdc, mi->x + 8, mi->y + 2, mi->text, strlen(mi->text));
    SelectObject(hdc, hBrush);
}

static void menuButtonDown(HWND hwnd, unsigned int x, unsigned int y)
{
    MenuInfo* mi = menuInfo;
    int i;

    for (i = 0; i < menuItemCount; i++) {
        MenuInfo* mi = menuInfo + i;
        int hit = ((x - mi->x) < mi->w) && ((y - mi->y) < mi->h);
        if (hit) {
            menuDown = i;
            InvalidateRect(hwnd, NULL, TRUE);
            mi->action(mi->x + menuX, mi->y + mi->h + menuY);
            return;
        }
    }
}

static void menuMouseMove(HWND hwnd, unsigned int x, unsigned int y, int forceUpdate)
{
    MenuInfo* mi = menuInfo;
    int i;

    for (i = 0; i < menuItemCount; i++) {
        MenuInfo* mi = menuInfo + i;
        int focused = ((x - mi->x) < mi->w) && ((y - mi->y) < mi->h);
        if (focused != mi->focused || forceUpdate) {
            menuDrawItem(GetDC(hwnd), mi, focused || menuDown == i);
        }
        if (focused && menuDown != -1 && menuDown != i) {
            menuDown = -1;
            menuPending = 1;
            EndMenu();
        }
        mi->focused = focused;
    }
}


static LRESULT CALLBACK menuProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (iMsg) {
    case WM_CREATE:
        return 0;

    case WM_MOUSEMOVE:
        {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);
            menuMouseMove(hwnd, pt.x, pt.y, 0);
            SetTimer(hwnd, 1, 250, NULL);
        }
        return 0;

    case WM_TIMER:
        {
            POINT pt;
            RECT r;

            GetCursorPos(&pt);
            GetWindowRect(hwnd, &r);

            ScreenToClient(hwnd, &pt);

            if (wParam == 1) {
                menuMouseMove(hwnd, pt.x, pt.y, 0);
            }
            else {
                KillTimer(hwnd, 2);
                menuPending = 0;
                menuButtonDown(menuHwnd, pt.x, pt.y);
            }
        }
        return 0;

    case WM_LBUTTONDOWN:
        {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);
            menuButtonDown(hwnd, pt.x, pt.y);
        }
        return 0;

    case WM_PAINT:
         {
            PAINTSTRUCT ps;
            HDC hdc;
            RECT r;
            HBRUSH hBrush;
            POINT pt;

            hdc = BeginPaint(hwnd, &ps); 

            GetClientRect(hwnd, &r);

            hBrush = (HBRUSH)SelectObject(hdc, menuBrush);

            Rectangle(hdc, r.left - 1, r.top - 1, r.right + 1, r.bottom + 1); 

            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);
            menuMouseMove(hwnd, pt.x, pt.y, 1);

            SelectObject(hdc, hBrush);

            EndPaint(hwnd, &ps);
        }
        return 0;
    }

    return DefWindowProc(hwnd, iMsg, wParam, lParam);  
}


void addMenuItem(char* text, void (*action)(int, int), int append)
{
    SIZE size;
    int i;
    int offset = 0;

    if (!append) {
        menuItemCount = 0;
    }

    for (i = 0; i < menuItemCount; i++) {
        offset += menuInfo[i].w;
    }

    GetTextExtentPoint32(GetDC(menuHwnd), text, strlen(text), &size);
    menuInfo[menuItemCount].x = offset;
    menuInfo[menuItemCount].y = 0;
    menuInfo[menuItemCount].w = size.cx + 17;
    menuInfo[menuItemCount].h = 20;
    menuInfo[menuItemCount].text = text;
    menuInfo[menuItemCount].focused = 0;
    menuInfo[menuItemCount].action = action;

    menuItemCount++;
}

int menuExitMenuLoop() {
    menuDown = -1;
    if (menuPending) {
        SetTimer(menuHwnd, 2, 10, NULL);
        return 1;
    }
    return 0;
}

int menuShow(int show) 
{
    ShowWindow(menuHwnd, (show || menuDown != -1 || menuPending) ? SW_NORMAL : SW_HIDE);

    return show;
}

void menuSetInfo(COLORREF color, COLORREF focusColor, COLORREF textColor, int x, int y, int width, int height)
{
    DeleteObject(menuBrush);
    menuBrush = CreateSolidBrush(color);
    menuText = textColor;
    DeleteObject(menuFocusBrush);
    menuFocusBrush = CreateSolidBrush(focusColor);
    menuX = x;
    menuY = y;

    SetWindowPos(menuHwnd, HWND_TOP, x, y, width, 20, 0);

    SetTextColor(GetDC(menuHwnd), textColor);
}

void menuUpdate(Properties* pProperties, 
                Shortcuts* shortcuts, 
                int isRunning, 
                int isStopped, 
                int logSound,
                int tempStateExits,
                int enableSpecial)
{
    if (hMenuReset) DestroyMenu(hMenuReset);
    if (hMenuCartSpecialA) DestroyMenu(hMenuCartSpecialA);
    if (hMenuCartSpecialB) DestroyMenu(hMenuCartSpecialB);
    if (hMenuVideoConnect) DestroyMenu(hMenuVideoConnect);
    if (hMenuCartA) DestroyMenu(hMenuCartA);
    if (hMenuCartB) DestroyMenu(hMenuCartB);
    if (hMenuRun) DestroyMenu(hMenuRun);
    if (hMenuDiskA) DestroyMenu(hMenuDiskA);
    if (hMenuDiskB) DestroyMenu(hMenuDiskB);
    if (hMenuCasette) DestroyMenu(hMenuCasette);
    if (hMenuPrinter) DestroyMenu(hMenuPrinter);
    if (hMenuControlsPort1) DestroyMenu(hMenuControlsPort1);
    if (hMenuControlsPort2) DestroyMenu(hMenuControlsPort2);
    if (hMenuZoom) DestroyMenu(hMenuZoom);
    if (hMenuOptions) DestroyMenu(hMenuOptions);
    if (hMenuHelp) DestroyMenu(hMenuHelp);
    if (hMenuFile) DestroyMenu(hMenuFile);
    if (hMenuTools) DestroyMenu(hMenuTools);

    hMenuReset         = menuCreateReset(pProperties, shortcuts);
    hMenuCartSpecialA  = menuCreateCartSpecialA(pProperties, shortcuts);
    hMenuCartSpecialB  = menuCreateCartSpecialB(pProperties, shortcuts);
    hMenuVideoConnect  = menuCreateVideoConnect(pProperties, shortcuts);
    hMenuCartA         = menuCreateCartA(pProperties, shortcuts, enableSpecial);
    hMenuCartB         = menuCreateCartB(pProperties, shortcuts, enableSpecial);
    hMenuRun           = menuCreateRun(pProperties, shortcuts, isRunning, isStopped);
    hMenuDiskA         = menuCreateDiskA(pProperties, shortcuts);
    hMenuDiskB         = menuCreateDiskB(pProperties, shortcuts);
    hMenuCasette       = menuCreateCassette(pProperties, shortcuts);
    hMenuPrinter       = menuCreatePrinter(pProperties, shortcuts);
    hMenuControlsPort1 = menuCreateControlsPort1(pProperties, shortcuts);
    hMenuControlsPort2 = menuCreateControlsPort2(pProperties, shortcuts);
    hMenuZoom          = menuCreateZoom(pProperties, shortcuts);
    hMenuOptions       = menuCreateOptions(pProperties, shortcuts);
    hMenuHelp          = menuCreateHelp(pProperties, shortcuts);
    hMenuFile          = menuCreateFile(pProperties, shortcuts, isStopped, logSound, tempStateExits, enableSpecial);
    hMenuTools         = menuCreateTools(pProperties, shortcuts);
 
    InvalidateRect(menuHwnd, NULL, TRUE);
}

static BOOL CALLBACK dummyProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    return FALSE;
}

void menuCreate(HWND parent)
{
    static WNDCLASSEX wndClass;
    HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);

    wndClass.cbSize         = sizeof(wndClass);
    wndClass.style          = CS_OWNDC;
    wndClass.lpfnWndProc    = menuProc;
    wndClass.cbClsExtra     = 0;
    wndClass.cbWndExtra     = 0;
    wndClass.hInstance      = hInstance;
    wndClass.hIcon          = NULL;
    wndClass.hIconSm        = NULL;
    wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground  = NULL;
    wndClass.lpszMenuName   = NULL;
    wndClass.lpszClassName  = "blueMSXmenuWindow";

    RegisterClassEx(&wndClass);

    menuBrush      = CreateSolidBrush(RGB(219, 221, 224));
    menuFocusBrush = CreateSolidBrush(RGB(200, 50, 50));
    parentHwnd     = parent;

    menuHwnd = CreateWindow(wndClass.lpszClassName, NULL, WS_CHILD | WS_CLIPSIBLINGS, 
                            0, 0, 0, 0, parent, 0, hInstance, NULL);
    SelectObject(GetDC(menuHwnd), CreatePen(PS_NULL, 0, 0));
    SelectObject(GetDC(menuHwnd), (HFONT)SendMessage(CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DISKIMAGE), menuHwnd, dummyProc), WM_GETFONT, 0, 0));
    SetBkMode (GetDC(menuHwnd), TRANSPARENT);
    SetTextColor(GetDC(menuHwnd), 0);
}

void archShowMenuSpecialCart1(int x, int y) {
    showPopupMenu(hMenuCartSpecialA, x, y);
}

void archShowMenuSpecialCart2(int x, int y) {
    showPopupMenu(hMenuCartSpecialB, x, y);
}

void archShowMenuReset(int x, int y) {
    showPopupMenu(hMenuReset, x, y);
}

void archShowMenuHelp(int x, int y) {
    showPopupMenu(hMenuHelp, x, y);
}


void archShowMenuRun(int x, int y) {
    showPopupMenu(hMenuRun, x, y);
}

void archShowMenuFile(int x, int y) {
    showPopupMenu(hMenuFile, x, y);
}

void archShowMenuCart1(int x, int y) {
    showPopupMenu(hMenuCartA, x, y);
}

void archShowMenuCart2(int x, int y) {
    showPopupMenu(hMenuCartB, x, y);
}

void archShowMenuDiskA(int x, int y) {
    showPopupMenu(hMenuDiskA, x, y);
}

void archShowMenuDiskB(int x, int y) {
    showPopupMenu(hMenuDiskB, x, y);
}

void archShowMenuCassette(int x, int y) {
    showPopupMenu(hMenuCasette, x, y);
}

void archShowMenuPrinter(int x, int y) {
    showPopupMenu(hMenuPrinter, x, y);
}

void archShowMenuControlsPort1(int x, int y) {
    archUpdateMenu(0);
    showPopupMenu(hMenuControlsPort1, x, y);
}

void archShowMenuControlsPort2(int x, int y) {
    archUpdateMenu(0);
    showPopupMenu(hMenuControlsPort2, x, y);
}

void archShowMenuZoom(int x, int y) {
    showPopupMenu(hMenuZoom, x, y);
}

void archShowMenuOptions(int x, int y) {
    archUpdateMenu(0);
    showPopupMenu(hMenuOptions, x, y);
}

void archShowMenuTools(int x, int y) {
    showPopupMenu(hMenuTools, x, y);
}

int menuCommand(Properties* pProperties, int command) 
{
    int i;

    i = command - ID_TOOLPLUGINS;
    if (i >= 0 && i < 50) {
        toolInfoShowTool(toolInfoGet(i));
    }

    
    i = command - ID_VIDEO_CONNECTORS;
    if (i >= 0 && i < 16) {
        if (videoManagerGetActive() == i) {
            videoManagerSetActive(-1);
        }
        else {
            videoManagerSetActive(i);
        }
        return 1;
    }
    
    i = command - ID_CTRLPORT1_BASE;
    if (i >= 0 && i < 16) {
        if (i >= 5) {
            pProperties->joy1.hwType = i - 5;
            strcpy(pProperties->joy1.hwName, archJoystickGetName(pProperties->joy1.hwType));
            i = 5;
        }
        pProperties->joy1.type = i;

        archUpdateJoystick();
        return 1;
    }

    i = command - ID_CTRLPORT2_BASE;
    if (i >= 0 && i < 16) {
        if (i >= 5) {
            pProperties->joy2.hwType = i - 5;
            strcpy(pProperties->joy2.hwName, archJoystickGetName(pProperties->joy2.hwType));
            i = 5;
        }
        pProperties->joy2.type = i;
        
        archUpdateJoystick();
        return 1;
    }

    i = command - ID_CARTRIDGEA_HISTORY;
    if (i >= 0 && i < MAX_HISTORY) {
        insertCartridge(pProperties, 0, pProperties->filehistory.cartridgeA[i], NULL, pProperties->filehistory.cartridgeTypeA[i], 0);
        return 1;
    }
    i = command - ID_CARTRIDGEB_HISTORY;
    if (i >= 0 && i < MAX_HISTORY) {
        insertCartridge(pProperties, 1, pProperties->filehistory.cartridgeB[i], NULL, pProperties->filehistory.cartridgeTypeB[i], 0);
        return 1;
    }
    i = command - ID_DISKDRIVEA_HISTORY;
    if (i >= 0 && i < MAX_HISTORY) {
        insertDiskette(pProperties, 0, pProperties->filehistory.diskdriveA[i], NULL, 0);
        return 1;
    }
    i = command - ID_DISKDRIVEB_HISTORY;
    if (i >= 0 && i < MAX_HISTORY) {
        insertDiskette(pProperties, 1, pProperties->filehistory.diskdriveB[i], NULL, 0);
        return 1;
    }
    i = command - ID_CASSETTE_HISTORY;
    if (i >= 0 && i < MAX_HISTORY) {
        insertCassette(pProperties, pProperties->filehistory.cassette[i], NULL, 0);
        if (pProperties->cassette.autoRewind) {
            tapeSetCurrentPos(0);
        }
        return 1;
    }
    
    switch (command) {
    case ID_FILE_CARTA_EXTRAM512KB:
        insertCartridge(pProperties, 0, CARTNAME_EXTRAM512KB, NULL, ROM_EXTRAM512KB, 0);
        return 1;
    case ID_FILE_CARTB_EXTRAM512KB:
        insertCartridge(pProperties, 1, CARTNAME_EXTRAM512KB, NULL, ROM_EXTRAM512KB, 0);
        return 1;
    case ID_FILE_CARTA_EXTRAM1MB:
        insertCartridge(pProperties, 0, CARTNAME_EXTRAM1MB, NULL, ROM_EXTRAM1MB, 0);
        return 1;
    case ID_FILE_CARTB_EXTRAM1MB:
        insertCartridge(pProperties, 1, CARTNAME_EXTRAM1MB, NULL, ROM_EXTRAM1MB, 0);
        return 1;
    case ID_FILE_CARTA_EXTRAM2MB:
        insertCartridge(pProperties, 0, CARTNAME_EXTRAM2MB, NULL, ROM_EXTRAM2MB, 0);
        return 1;
    case ID_FILE_CARTB_EXTRAM2MB:
        insertCartridge(pProperties, 1, CARTNAME_EXTRAM2MB, NULL, ROM_EXTRAM2MB, 0);
        return 1;
    case ID_FILE_CARTA_EXTRAM4MB:
        insertCartridge(pProperties, 0, CARTNAME_EXTRAM4MB, NULL, ROM_EXTRAM4MB, 0);
        return 1;
    case ID_FILE_CARTB_EXTRAM4MB:
        insertCartridge(pProperties, 1, CARTNAME_EXTRAM4MB, NULL, ROM_EXTRAM4MB, 0);
        return 1;
    case ID_FILE_CARTA_MEGARAM128:
        insertCartridge(pProperties, 0, CARTNAME_MEGARAM128, NULL, ROM_MEGARAM128, 0);
        return 1;
    case ID_FILE_CARTB_MEGARAM128:
        insertCartridge(pProperties, 1, CARTNAME_MEGARAM128, NULL, ROM_MEGARAM128, 0);
        return 1;
    case ID_FILE_CARTA_MEGARAM256:
        insertCartridge(pProperties, 0, CARTNAME_MEGARAM256, NULL, ROM_MEGARAM256, 0);
        return 1;
    case ID_FILE_CARTB_MEGARAM256:
        insertCartridge(pProperties, 1, CARTNAME_MEGARAM256, NULL, ROM_MEGARAM256, 0);
        return 1;
    case ID_FILE_CARTA_MEGARAM512:
        insertCartridge(pProperties, 0, CARTNAME_MEGARAM512, NULL, ROM_MEGARAM512, 0);
        return 1;
    case ID_FILE_CARTB_MEGARAM512:
        insertCartridge(pProperties, 1, CARTNAME_MEGARAM512, NULL, ROM_MEGARAM512, 0);
        return 1;
    case ID_FILE_CARTA_MEGARAM768:
        insertCartridge(pProperties, 0, CARTNAME_MEGARAM768, NULL, ROM_MEGARAM768, 0);
        return 1;
    case ID_FILE_CARTB_MEGARAM768:
        insertCartridge(pProperties, 1, CARTNAME_MEGARAM768, NULL, ROM_MEGARAM768, 0);
        return 1;
    case ID_FILE_CARTA_MEGARAM2M:
        insertCartridge(pProperties, 0, CARTNAME_MEGARAM2M, NULL, ROM_MEGARAM2M, 0);
        return 1;
    case ID_FILE_CARTB_MEGARAM2M:
        insertCartridge(pProperties, 1, CARTNAME_MEGARAM2M, NULL, ROM_MEGARAM2M, 0);
        return 1;
    case ID_FILE_CARTA_SNATCHER:
        insertCartridge(pProperties, 0, CARTNAME_SNATCHER, NULL, ROM_SNATCHER, 0);
        return 1;
    case ID_FILE_CARTA_SDSNATCHER:
        insertCartridge(pProperties, 0, CARTNAME_SDSNATCHER, NULL, ROM_SDSNATCHER, 0);
        return 1;
    case ID_FILE_CARTA_SCCMIRRORED:
        insertCartridge(pProperties, 0, CARTNAME_SCCMIRRORED, NULL, ROM_SCCMIRRORED, 0);
        return 1;
    case ID_FILE_CARTA_SCCEXPANDED:
        insertCartridge(pProperties, 0, CARTNAME_SCCEXPANDED, NULL, ROM_SCCEXTENDED, 0);
        return 1;
    case ID_FILE_CARTA_SCC:
        insertCartridge(pProperties, 0, CARTNAME_SCC, NULL, ROM_SCC, 0);
        return 1;
    case ID_FILE_CARTA_SCCPLUS:
        insertCartridge(pProperties, 0, CARTNAME_SCCPLUS, NULL, ROM_SCCPLUS, 0);
        return 1;
    case ID_FILE_CARTB_SNATCHER:
        insertCartridge(pProperties, 1, CARTNAME_SNATCHER, NULL, ROM_SNATCHER, 0);
        return 1;
    case ID_FILE_CARTB_SDSNATCHER:
        insertCartridge(pProperties, 1, CARTNAME_SDSNATCHER, NULL, ROM_SDSNATCHER, 0);
        return 1;
    case ID_FILE_CARTB_SCCMIRRORED:
        insertCartridge(pProperties, 1, CARTNAME_SCCMIRRORED, NULL, ROM_SCCMIRRORED, 0);
        return 1;
    case ID_FILE_CARTB_SCCEXPANDED:
        insertCartridge(pProperties, 1, CARTNAME_SCCEXPANDED, NULL, ROM_SCCEXTENDED, 0);
        return 1;
    case ID_FILE_CARTB_SCC:
        insertCartridge(pProperties, 1, CARTNAME_SCC, NULL, ROM_SCC, 0);
        return 1;
    case ID_FILE_CARTB_SCCPLUS:
        insertCartridge(pProperties, 1, CARTNAME_SCCPLUS, NULL, ROM_SCCPLUS, 0);
        return 1;
    case ID_FILE_CARTA_FMPAC:
        insertCartridge(pProperties, 0, CARTNAME_FMPAC, NULL, ROM_FMPAC, 0);
        return 1;
    case ID_FILE_CARTA_PAC:
        insertCartridge(pProperties, 0, CARTNAME_PAC, NULL, ROM_PAC, 0);
        return 1;
    case ID_FILE_CARTB_FMPAC:
        insertCartridge(pProperties, 1, CARTNAME_FMPAC, NULL, ROM_FMPAC, 0);
        return 1;
    case ID_FILE_CARTB_PAC:            
        insertCartridge(pProperties, 1, CARTNAME_PAC, NULL, ROM_PAC, 0);
        return 1;
    case ID_FILE_CARTA_SONYHBI55:            
        insertCartridge(pProperties, 0, CARTNAME_SONYHBI55, NULL, ROM_SONYHBI55, 0);
        return 1;
    case ID_FILE_CARTB_SONYHBI55:            
        insertCartridge(pProperties, 1, CARTNAME_SONYHBI55, NULL, ROM_SONYHBI55, 0);
        return 1;

    case ID_VIDEO_AUTODETECT:
        pProperties->video.chipAutodetect = !pProperties->video.chipAutodetect;
        boardSetVideoAutodetect(pProperties->video.chipAutodetect);
        return 0;

    case ID_PRT_SCR:                        actionScreenCapture();          return 0;
    case ID_FILE_POSITION_CASSETTE:         actionCasSetPosition();         return 0;
    case ID_FILE_REWIND_CASSETTE:           actionCasRewind();              return 0;
    case ID_FILE_INSERT_DISKETTEA:          actionDiskInsertA();            return 0;
    case ID_FILE_INSERT_DISKETTEB:          actionDiskInsertB();            return 0;
    case ID_FILE_INSERT_DISKETTEDIRA:       actionDiskDirInsertA();         return 0;
    case ID_FILE_INSERT_DISKETTEDIRB:       actionDiskDirInsertB();         return 0;
    case ID_FILE_INSERT_CASSETTE:           actionCasInsert();              return 0;
    case ID_FILE_SAVE:                      actionSaveState();              return 0;
    case ID_FILE_LOAD:                      actionLoadState();              return 0;
    case ID_FILE_QSAVE:                     actionQuickSaveState();         return 0;
    case ID_FILE_QLOAD:                     actionQuickLoadState();         return 0;
    case ID_FILE_INSERT_CARTRIDGEA:         actionCartInsert1();            return 0;
    case ID_FILE_INSERT_CARTRIDGEB:         actionCartInsert2();            return 0;
    case ID_LOG_WAV:                        actionToggleWaveCapture();      return 0;
    case ID_FILE_EXIT:                      actionQuit();                   return 0;
    case ID_SIZE_NORMAL:                    actionWindowSizeSmall();        return 0;
    case ID_SIZE_X2:                        actionWindowSizeNormal();       return 0;
    case ID_SIZE_MINIMIZED:                 actionWindowSizeMinimized();    return 0;
    case ID_SIZE_FULLSCREEN:                actionWindowSizeFullscreen();   return 0;
    case ID_RUN_RUN:                        actionEmuTogglePause();         return 0;
    case ID_RUN_STOP:                       actionEmuStop();                return 0;
    case ID_RUN_RESET:                      actionEmuResetHard();           return 0;
    case ID_RUN_SOFTRESET:                  actionEmuResetSoft();           return 0;
    case ID_RUN_CLEANRESET:                 actionEmuResetClean();          return 0;
    case ID_FILE_READONLY_CASSETTE:         actionCasToggleReadonly();      return 0;
    case ID_FILE_AUTOREWNIND_CASSETTE:      actionToggleCasAutoRewind();    return 0;
    case ID_FILE_SAVE_CASSETTE:             actionCasSave();                return 0;
    case ID_FILE_CARTRIDGE_AUTORESET:       actionToggleCartAutoReset();    return 0;
    case ID_FILE_INSERT_DISKETTEA_RESET:    actionToggleDiskAutoResetA();   return 0;
    case ID_FILE_REMOVE_CARTRIDGEA:         actionCartRemove1();            return 0;
    case ID_FILE_REMOVE_CARTRIDGEB:         actionCartRemove2();            return 0;
    case ID_FILE_REMOVE_DISKETTEA:          actionDiskRemoveA();            return 0;
    case ID_FILE_REMOVE_DISKETTEB:          actionDiskRemoveB();            return 0;
    case ID_FILE_REMOVE_CASSETTE:           actionCasRemove();              return 0;
    case ID_FILE_PRINTER_FORMFEED:          actionPrinterForceFormFeed();   return 0;
    case ID_OPTIONS_EMULATION:              actionPropShowEmulation();      return 0;
    case ID_OPTIONS_VIDEO:                  actionPropShowVideo();          return 0;
    case ID_OPTIONS_AUDIO:                  actionPropShowAudio();          return 0;
    case ID_OPTIONS_CONTROLS:               actionPropShowControls();       return 0;
    case ID_OPTIONS_PERFORMANCE:            actionPropShowPerformance();    return 0;
    case ID_OPTIONS_SETTINGS:               actionPropShowSettings();       return 0;
    case ID_OPTIONS_APEARANCE:              actionPropShowApearance();      return 0;
    case ID_OPTIONS_PORTS:                  actionPropShowPorts();          return 0;
    case ID_OPTIONS_LANGUAGE:               actionOptionsShowLanguage();    return 0;
    case ID_TOOLS_MACHINEEDITOR:            actionToolsShowMachineEditor(); return 0;
    case ID_TOOLS_SHORTCUTSEDITOR:          actionToolsShowShorcutEditor(); return 0;
    case ID_TOOLS_KEYBOARDEDITOR:           actionToolsShowKeyboardEditor();return 0;
    case ID_HELP_HELP:                      actionHelpShowHelp();           return 0;
    case ID_HELP_ABOUT:                     actionHelpShowAbout();          return 0;
    }
    return 0;
}