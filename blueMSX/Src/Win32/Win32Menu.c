/*****************************************************************************
** File:        Win32Menu.c
**
** Author:      Daniel Vik
**
** Description: Methods to show create menus.
**
** More info:   www.bluemsx.com
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
#include "FileHistory.h"
#include "Language.h"
#include "Resource.h"
#include "archMenu.h"

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
static HMENU hMenuCartA = NULL;
static HMENU hMenuCartB = NULL;
static HMENU hMenuRun = NULL;
static HMENU hMenuDiskA = NULL;
static HMENU hMenuDiskB = NULL;
static HMENU hMenuCasette = NULL;
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

    setMenuColor(hMenu);

    _stprintf(langBuffer, "%s", langMenuToolsMachine());
    AppendMenu(hMenu, MF_STRING, ID_TOOLS_MACHINEEDITOR, langBuffer);
    
    _stprintf(langBuffer, "%s", langMenuToolsShortcuts());
    AppendMenu(hMenu, MF_STRING, ID_TOOLS_SHORTCUTSEDITOR, langBuffer);
   
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
    if (hMenuCartA) DestroyMenu(hMenuCartA);
    if (hMenuCartB) DestroyMenu(hMenuCartB);
    if (hMenuRun) DestroyMenu(hMenuRun);
    if (hMenuDiskA) DestroyMenu(hMenuDiskA);
    if (hMenuDiskB) DestroyMenu(hMenuDiskB);
    if (hMenuCasette) DestroyMenu(hMenuCasette);
    if (hMenuZoom) DestroyMenu(hMenuZoom);
    if (hMenuOptions) DestroyMenu(hMenuOptions);
    if (hMenuHelp) DestroyMenu(hMenuHelp);
    if (hMenuFile) DestroyMenu(hMenuFile);
    if (hMenuTools) DestroyMenu(hMenuTools);

    hMenuReset        = menuCreateReset(pProperties, shortcuts);
    hMenuCartSpecialA = menuCreateCartSpecialA(pProperties, shortcuts);
    hMenuCartSpecialB = menuCreateCartSpecialB(pProperties, shortcuts);
    hMenuCartA        = menuCreateCartA(pProperties, shortcuts, enableSpecial);
    hMenuCartB        = menuCreateCartB(pProperties, shortcuts, enableSpecial);
    hMenuRun          = menuCreateRun(pProperties, shortcuts, isRunning, isStopped);
    hMenuDiskA        = menuCreateDiskA(pProperties, shortcuts);
    hMenuDiskB        = menuCreateDiskB(pProperties, shortcuts);
    hMenuCasette      = menuCreateCassette(pProperties, shortcuts);
    hMenuZoom         = menuCreateZoom(pProperties, shortcuts);
    hMenuOptions      = menuCreateOptions(pProperties, shortcuts);
    hMenuHelp         = menuCreateHelp(pProperties, shortcuts);
    hMenuFile         = menuCreateFile(pProperties, shortcuts, isStopped, logSound, tempStateExits, enableSpecial);
    hMenuTools        = menuCreateTools(pProperties, shortcuts);

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

void archShowMenuZoom(int x, int y) {
    showPopupMenu(hMenuZoom, x, y);
}

void archShowMenuOptions(int x, int y) {
    showPopupMenu(hMenuOptions, x, y);
}

void archShowMenuTools(int x, int y) {
    showPopupMenu(hMenuTools, x, y);
}

