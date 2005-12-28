/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Menu.c,v $
**
** $Revision: 1.38 $
**
** $Date: 2005-12-28 06:50:18 $
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
#include "Disk.h"
#include "VideoManager.h"
#include "ArchNotifications.h"
#include "ArchInput.h"
#include "JoystickPort.h"



#define ID_VIDEO_CONNECTORS             30250
#define ID_CTRLPORT1_BASE               30300
#define ID_CTRLPORT2_BASE               30350
#define ID_TOOLPLUGINS                  30400

#define ID_FILE                         40011
#define ID_FILE_LOAD                    40012
#define ID_FILE_SAVE                    40013
#define ID_FILE_QLOAD                   40014
#define ID_FILE_QSAVE                   40015
#define ID_FILE_LOGWAV                  40016
#define ID_FILE_PTRSCR                  40017
#define ID_FILE_EXIT                    40018
#define ID_FILE_PRINTER_FORMFEED        40019

#define ID_RUN_RUN                      40021
#define ID_RUN_PAUSE                    40022
#define ID_RUN_STOP                     40023
#define ID_RUN_RESET                    40024
#define ID_RUN_SOFTRESET                40025
#define ID_RUN_CLEANRESET               40026

#define ID_VIDEO_AUTODETECT             40031
#define ID_SIZE_NORMAL                  40032
#define ID_SIZE_X2                      40033
#define ID_SIZE_FULLSCREEN              40034
#define ID_SIZE_MINIMIZED               40035

#define ID_OPTIONS_EMULATION            40041
#define ID_OPTIONS_AUDIO                40042
#define ID_OPTIONS_VIDEO                40043
#define ID_OPTIONS_PERFORMANCE          40044
#define ID_OPTIONS_SETTINGS             40045
#define ID_OPTIONS_LANGUAGE             40046
#define ID_OPTIONS_APEARANCE            40047
#define ID_OPTIONS_PORTS                40048

#define ID_HELP_HELP                    40051
#define ID_HELP_ABOUT                   40052

#define ID_TOOLS_MACHINEEDITOR          40064
#define ID_TOOLS_SHORTCUTSEDITOR        40065
#define ID_TOOLS_KEYBOARDEDITOR         40066
#define ID_TOOLS_MIXER                  40061


#define ID_FILE_CART_OFFSET               100

#define ID_FILE_CART_INSERT             41000
#define ID_FILE_CART_REMOVE             41001
#define ID_FILE_CART_AUTORESET          41002
#define ID_FILE_CART_HISTORY            41003

#define ID_FILE_CART_FMPAC              41070
#define ID_FILE_CART_PAC                41071
#define ID_FILE_CART_MEGARAM128         41072
#define ID_FILE_CART_MEGARAM256         41073
#define ID_FILE_CART_MEGARAM512         41074
#define ID_FILE_CART_MEGARAM768         41075
#define ID_FILE_CART_MEGARAM2M          41076
#define ID_FILE_CART_SNATCHER           41077
#define ID_FILE_CART_SDSNATCHER         41078
#define ID_FILE_CART_SCCMIRRORED        41079
#define ID_FILE_CART_SCCEXPANDED        41080
#define ID_FILE_CART_SCC                41081
#define ID_FILE_CART_SCCPLUS            41082
#define ID_FILE_CART_EXTRAM512KB        41083
#define ID_FILE_CART_EXTRAM1MB          41084
#define ID_FILE_CART_EXTRAM2MB          41085
#define ID_FILE_CART_EXTRAM4MB          41086
#define ID_FILE_CART_SONYHBI55          41087
#define ID_FILE_CART_GAMEREADER         41088
#define ID_FILE_CART_SUNRISEIDE         41089
#define ID_FILE_CART_BEERIDE            41090
#define ID_FILE_CART_GIDE               41091

#define ID_FILE_DISK_OFFSET               100

#define ID_FILE_DISK_INSERT             41200
#define ID_FILE_DISK_INSERTDIR          41201
#define ID_FILE_DISK_REMOVE             41202
#define ID_FILE_DISK_AUTOSTART          41203
#define ID_FILE_DISK_HISTORY            41204

#define ID_FILE_TAPE_INSERT             41400
#define ID_FILE_TAPE_REMOVE             41401
#define ID_FILE_TAPE_REWIND             41402
#define ID_FILE_TAPE_POSITION           41403
#define ID_FILE_TAPE_SAVE               41404
#define ID_FILE_TAPE_READONLY           41405
#define ID_FILE_TAPE_AUTOREWNIND        41406
#define ID_FILE_TAPE_HISTORY            41407


#define ID_HARDDISK_OFFSET                 50
#define ID_HARDDISK_COUNT                  30

#define ID_HARDDISK_INSERT              41500
#define ID_HARDDISK_INSERTNEW           41501
#define ID_HARDDISK_INSERTDIR           41502
#define ID_HARDDISK_REMOVE              41503
#define ID_HARDDISK_HISTORY             41504




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
static HMENU hMenuHarddisk = NULL;
static HMENU hMenuRun = NULL;
static HMENU hMenuDiskA = NULL;
static HMENU hMenuDiskB = NULL;
static HMENU hMenuCasette = NULL;
static HMENU hMenuPrinter = NULL;
static HMENU hMenuJoyPort1 = NULL;
static HMENU hMenuJoyPort2 = NULL;
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
    HWND hwnd = GetForegroundWindow();
    int flags = 0;
    if (x == -1 && y == -1) {
        RECT r;
        if (GetParent(hwnd) == parentHwnd) {
            hwnd = parentHwnd;
        }
        GetWindowRect(hwnd, &r);
        x = (r.left + r.right) / 2;
        y =  (r.top + r.bottom) / 2;
        flags = TPM_CENTERALIGN;
    }
    else {
        POINT pt = {x, y};
        ClientToScreen(hwnd, &pt);
        x = pt.x;
        y = pt.y;
    }

    enterDialogShow();
    TrackPopupMenu(hMenu, 0, x, y, flags, hwnd, NULL);
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

static HMENU menuCreateCartSpecial(int cartNo, Properties* pProperties, Shortcuts* shortcuts) 
{
    int idOffset = cartNo * ID_FILE_CART_OFFSET;

    HMENU hMenu = CreatePopupMenu();
    HMENU hMenuExtRam = CreatePopupMenu();
    HMENU hMenuMegaRam = CreatePopupMenu();
    HMENU hMenuIde = CreatePopupMenu();

    setMenuColor(hMenu);
    setMenuColor(hMenuExtRam);
    setMenuColor(hMenuMegaRam);

    AppendMenu(hMenuExtRam, MF_STRING, idOffset + ID_FILE_CART_EXTRAM512KB, "512 kB");
    AppendMenu(hMenuExtRam, MF_STRING, idOffset + ID_FILE_CART_EXTRAM1MB, "1 MB");
    AppendMenu(hMenuExtRam, MF_STRING, idOffset + ID_FILE_CART_EXTRAM2MB, "2 MB");
    AppendMenu(hMenuExtRam, MF_STRING, idOffset + ID_FILE_CART_EXTRAM4MB, "4 MB");

    AppendMenu(hMenuMegaRam, MF_STRING, idOffset + ID_FILE_CART_MEGARAM128, "128 kB");
    AppendMenu(hMenuMegaRam, MF_STRING, idOffset + ID_FILE_CART_MEGARAM256, "256 kB");
    AppendMenu(hMenuMegaRam, MF_STRING, idOffset + ID_FILE_CART_MEGARAM512, "512 kB");
    AppendMenu(hMenuMegaRam, MF_STRING, idOffset + ID_FILE_CART_MEGARAM768, "768 kB");
    AppendMenu(hMenuMegaRam, MF_STRING, idOffset + ID_FILE_CART_MEGARAM2M, "2 MB");

    AppendMenu(hMenuIde, MF_STRING, idOffset + ID_FILE_CART_SUNRISEIDE, langMenuCartSunriseIde());
    AppendMenu(hMenuIde, MF_STRING, idOffset + ID_FILE_CART_BEERIDE, langMenuCartBeerIde());
    AppendMenu(hMenuIde, MF_STRING, idOffset + ID_FILE_CART_GIDE, langMenuCartGIde());

    AppendMenu(hMenu, MF_STRING, idOffset + ID_FILE_CART_GAMEREADER, langMenuCartGameReader());
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_STRING, idOffset + ID_FILE_CART_SCC, langMenuCartSCC());
    AppendMenu(hMenu, MF_STRING, idOffset + ID_FILE_CART_SCCPLUS, langMenuCartSCCPlus());
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuIde, langMenuCartIde());
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_STRING, idOffset + ID_FILE_CART_FMPAC, langMenuCartFMPac());
    AppendMenu(hMenu, MF_STRING, idOffset + ID_FILE_CART_PAC, langMenuCartPac());
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_STRING, idOffset + ID_FILE_CART_SONYHBI55, langMenuCartHBI55());
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuExtRam, langMenuCartExternalRam());
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_POPUP, (UINT)hMenuMegaRam, langMenuCartMegaRam());

    return hMenu;
}


static HMENU menuCreateCart(int cartNo, Properties* pProperties, Shortcuts* shortcuts, int enableSpecial)
{
    int idOffset = cartNo * ID_FILE_CART_OFFSET;
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();
    int i;

    setMenuColor(hMenu);

    verifyFileHistory(*pProperties->filehistory.cartridge[cartNo],
                      pProperties->filehistory.cartridgeType[cartNo]);

    _stprintf(langBuffer, "%s      \t%hs", langMenuCartInsert(), shortcutsToString(shortcuts->cartInsert[cartNo]));
    AppendMenu(hMenu, MF_STRING, idOffset + ID_FILE_CART_INSERT, langBuffer);

    if (enableSpecial) {
        AppendMenu(hMenu, MF_POPUP, (UINT)menuCreateCartSpecial(cartNo, pProperties, shortcuts), langMenuCartInsertSpecial());
    }

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s%hs%hs", langMenuCartRemove(), (*pProperties->media.carts[cartNo].fileName ? ": " : ""), stripPath(pProperties->media.carts[cartNo].fileName));
    AppendMenu(hMenu, MF_STRING | (*pProperties->media.carts[cartNo].fileName ? 0 : MF_GRAYED), idOffset + ID_FILE_CART_REMOVE, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    if (cartNo == 0) {
        AppendMenu(hMenu, MF_STRING | (pProperties->cartridge.autoReset ? MFS_CHECKED : 0), idOffset + ID_FILE_CART_AUTORESET, langMenuCartAutoReset());
    }

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    if (*pProperties->filehistory.cartridge[cartNo][0] == 0) {
        AppendMenu(hMenu, MF_STRING | MF_GRAYED,  0, langMenuCartNoRecentFiles());
    }

    for (i = 0; i < pProperties->filehistory.count && *pProperties->filehistory.cartridge[cartNo][i]; i++) {
        _stprintf(langBuffer, "%hs", stripPath(pProperties->filehistory.cartridge[cartNo][i]));
        AppendMenu(hMenu, MF_STRING, idOffset + ID_FILE_CART_HISTORY + i, langBuffer);
    }

    return hMenu;
}


static HMENU menuCreateDisk(int diskNo, Properties* pProperties, Shortcuts* shortcuts) 
{
    int idOffset = diskNo * ID_FILE_CART_OFFSET;
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();
    int i;

    verifyFileHistory(*pProperties->filehistory.diskdrive[diskNo], NULL);

    setMenuColor(hMenu);

    _stprintf(langBuffer, "%s      \t%hs", langMenuDiskInsert(), shortcutsToString(shortcuts->diskInsert[diskNo]));
    AppendMenu(hMenu, MF_STRING, idOffset + ID_FILE_DISK_INSERT, langBuffer);

    _stprintf(langBuffer, "%s      \t%hs", langMenuDiskDirInsert(), shortcutsToString(shortcuts->diskDirInsert[diskNo]));
    AppendMenu(hMenu, MF_STRING, idOffset + ID_FILE_DISK_INSERTDIR, langBuffer);

    _stprintf(langBuffer, "%s%hs%hs", langMenuDiskEject(), (*pProperties->media.disks[diskNo].fileName ? ": " : ""), stripPath(pProperties->media.disks[diskNo].fileName));
    AppendMenu(hMenu, MF_STRING | (*pProperties->media.disks[diskNo].fileName ? 0 : MF_GRAYED), idOffset + ID_FILE_DISK_REMOVE, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    if (diskNo == 0) {
        AppendMenu(hMenu, MF_STRING | (pProperties->diskdrive.autostartA ? MFS_CHECKED : 0), idOffset + ID_FILE_DISK_AUTOSTART, langMenuDiskAutoStart());
    }

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    if (*pProperties->filehistory.diskdrive[diskNo][0] == 0) {
        AppendMenu(hMenu, MF_STRING | MF_GRAYED,  0, langMenuDiskNoRecentFiles());
    }

    for (i = 0; i < pProperties->filehistory.count && *pProperties->filehistory.diskdrive[diskNo][i]; i++) {
        _stprintf(langBuffer, "%hs", stripPath(pProperties->filehistory.diskdrive[diskNo][i]));
        AppendMenu(hMenu, MF_STRING, idOffset + ID_FILE_DISK_HISTORY + i, langBuffer);
    }

    return hMenu;
}

static HMENU menuCreateIdeHd(int diskNo, Properties* pProperties, Shortcuts* shortcuts)
{
    int idOffset = diskNo * ID_HARDDISK_OFFSET;
    HMENU hMenu = CreatePopupMenu();
    _TCHAR langBuffer[560];

    setMenuColor(hMenu);

    AppendMenu(hMenu, MF_STRING, idOffset + ID_HARDDISK_INSERT, langMenuDiskInsert());
    AppendMenu(hMenu, MF_STRING, idOffset + ID_HARDDISK_INSERTNEW, langMenuDiskInsertNew());
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    _stprintf(langBuffer, "%s%hs%hs", langMenuDiskEject(), (*pProperties->media.disks[diskNo].fileName ? ": " : ""), stripPath(pProperties->media.disks[diskNo].fileName));
    AppendMenu(hMenu, MF_STRING | (*pProperties->media.disks[diskNo].fileName ? 0 : MF_GRAYED), idOffset + ID_HARDDISK_REMOVE, langBuffer);

    return hMenu;
}

static HMENU menuCreateHarddisk(Properties* pProperties, Shortcuts* shortcuts)
{
    HMENU hMenu = CreatePopupMenu();
    _TCHAR langBuffer[560];
    int hasHd = 0;
    int i;

    setMenuColor(hMenu);

    for (i = 0; i < MAX_HD_COUNT; i++) {
        switch (boardGetHdType(i)) {
        case HD_SUNRISEIDE:
            hasHd = 1;
            _stprintf(langBuffer, "IDE%d  - Sunrise Primary", i);
            AppendMenu(hMenu, MF_POPUP, (UINT)menuCreateIdeHd(diskGetHdDriveId(i, 0), pProperties, shortcuts), langBuffer);
            _stprintf(langBuffer, "IDE%d  - Sunrise Secondary", i);
            AppendMenu(hMenu, MF_POPUP, (UINT)menuCreateIdeHd(diskGetHdDriveId(i, 1), pProperties, shortcuts), langBuffer);
            break;
        case HD_BEERIDE:
            hasHd = 1;
            _stprintf(langBuffer, "IDE%d Beer", i);
            AppendMenu(hMenu, MF_POPUP, (UINT)menuCreateIdeHd(diskGetHdDriveId(i, 0), pProperties, shortcuts), langBuffer);
            break;
        case HD_GIDE:
            hasHd = 1;
            _stprintf(langBuffer, "IDE%d GIDE", i);
            AppendMenu(hMenu, MF_POPUP, (UINT)menuCreateIdeHd(diskGetHdDriveId(i, 0), pProperties, shortcuts), langBuffer);
            break;
        }
    }

    if (!hasHd) {
        AppendMenu(hMenu, MF_STRING | MF_GRAYED, 0, langMenuFileHarddiskNoPresent());
    }

    return hMenu;
}

static HMENU menuCreateCassette(Properties* pProperties, Shortcuts* shortcuts)
{
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();
    int i;

    verifyFileHistory(*pProperties->filehistory.cassette[0], NULL);

    setMenuColor(hMenu);

    _stprintf(langBuffer, "%s      \t%hs", langMenuCasInsert(), shortcutsToString(shortcuts->casInsert));
    AppendMenu(hMenu, MF_STRING, ID_FILE_TAPE_INSERT, langBuffer);

    _stprintf(langBuffer, "%s%hs%hs", langMenuCasEject(), (*pProperties->media.tapes[0].fileName ? ": " : ""), stripPath(pProperties->media.tapes[0].fileName));
    AppendMenu(hMenu, MF_STRING | (*pProperties->media.tapes[0].fileName ? 0 : MF_GRAYED), ID_FILE_TAPE_REMOVE, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    AppendMenu(hMenu, MF_STRING | (pProperties->cassette.autoRewind ? MFS_CHECKED : 0), ID_FILE_TAPE_AUTOREWNIND, langMenuCasRewindAfterInsert());

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    AppendMenu(hMenu, MF_STRING | (pProperties->cassette.readOnly ? MFS_CHECKED : 0), ID_FILE_TAPE_READONLY, langMenuCasUseReadOnly());

    AppendMenu(hMenu, MF_STRING | (*pProperties->media.tapes[0].fileName ? 0 : MF_GRAYED), ID_FILE_TAPE_SAVE, langMenuCasSaveAs());

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    _stprintf(langBuffer, "%s      \t%hs", langMenuCasSetPosition(), shortcutsToString(shortcuts->casSetPos));
    AppendMenu(hMenu, MF_STRING | (*pProperties->media.tapes[0].fileName ? 0 : MF_GRAYED), ID_FILE_TAPE_POSITION, langBuffer);

    _stprintf(langBuffer, "%s      \t%hs", langMenuCasRewind(), shortcutsToString(shortcuts->casRewind));
    AppendMenu(hMenu, MF_STRING | (*pProperties->media.tapes[0].fileName ? 0 : MF_GRAYED), ID_FILE_TAPE_REWIND, langBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

    if (*pProperties->filehistory.cassette[0][0] == 0) {
        AppendMenu(hMenu, MF_STRING | MF_GRAYED,  0, langMenuCasNoRecentFiles());
    }

    for (i = 0; i < pProperties->filehistory.count && *pProperties->filehistory.cassette[0][i]; i++) {
        _stprintf(langBuffer, "%hs", stripPath(pProperties->filehistory.cassette[0][i]));
        AppendMenu(hMenu, MF_STRING, ID_FILE_TAPE_HISTORY + i, langBuffer);
    }

    return hMenu;
}

static HMENU menuCreatePrinter(Properties* pProperties, Shortcuts* shortcuts) 
{
    _TCHAR langBuffer[560];
    HMENU hMenu = CreatePopupMenu();

    setMenuColor(hMenu);

    _stprintf(langBuffer, "%s      \t%hs", langMenuPrnFormfeed(), shortcutsToString(shortcuts->prnFormFeed));
    AppendMenu(hMenu, MF_STRING, ID_FILE_PRINTER_FORMFEED, langBuffer);

    return hMenu;
}

static HMENU menuCreateJoyPort1(Properties* pProperties, Shortcuts* shortcuts)
{
    HMENU            hMenu = CreatePopupMenu();
    JoystickPortType joyType = joystickPortGetType(0);

    setMenuColor(hMenu);

    AppendMenu(hMenu, MF_STRING | (joyType == JOYSTICK_PORT_NONE ? MFS_CHECKED : 0), 
               ID_CTRLPORT1_BASE + 0, langEnumControlsJoyNone());
    AppendMenu(hMenu, MF_STRING | (joyType == JOYSTICK_PORT_JOYSTICK ? MFS_CHECKED : 0), 
               ID_CTRLPORT1_BASE + 1, "2-button Joystick");
    AppendMenu(hMenu, MF_STRING | (joyType == JOYSTICK_PORT_MOUSE ? MFS_CHECKED : 0), 
               ID_CTRLPORT1_BASE + 2, langEnumControlsJoyMouse());
    AppendMenu(hMenu, MF_STRING | (joyType == JOYSTICK_PORT_TETRIS2DONGLE ? MFS_CHECKED : 0), 
               ID_CTRLPORT1_BASE + 3, langEnumControlsJoyTetrisDongle());
    AppendMenu(hMenu, MF_STRING | (joyType == JOYSTICK_PORT_LIGHTGUN ? MFS_CHECKED : 0), 
               ID_CTRLPORT1_BASE + 4, "Light Gun");
    AppendMenu(hMenu, MF_STRING | (joyType == JOYSTICK_PORT_COLECOJOYSTICK ? MFS_CHECKED : 0), 
               ID_CTRLPORT1_BASE + 5, "ColecoVision Joystick");
    
    return hMenu;
}

static HMENU menuCreateJoyPort2(Properties* pProperties, Shortcuts* shortcuts) 
{
    HMENU            hMenu = CreatePopupMenu();
    JoystickPortType joyType = joystickPortGetType(1);

    setMenuColor(hMenu);

    AppendMenu(hMenu, MF_STRING | (joyType == JOYSTICK_PORT_NONE ? MFS_CHECKED : 0), 
               ID_CTRLPORT2_BASE + 0, langEnumControlsJoyNone());
    AppendMenu(hMenu, MF_STRING | (joyType == JOYSTICK_PORT_JOYSTICK ? MFS_CHECKED : 0), 
               ID_CTRLPORT2_BASE + 1, "2-button Joystick");
    AppendMenu(hMenu, MF_STRING | (joyType == JOYSTICK_PORT_MOUSE ? MFS_CHECKED : 0), 
               ID_CTRLPORT2_BASE + 2, langEnumControlsJoyMouse());
    AppendMenu(hMenu, MF_STRING | (joyType == JOYSTICK_PORT_TETRIS2DONGLE ? MFS_CHECKED : 0), 
               ID_CTRLPORT2_BASE + 3, langEnumControlsJoyTetrisDongle());
    AppendMenu(hMenu, MF_STRING | (joyType == JOYSTICK_PORT_LIGHTGUN ? MFS_CHECKED : 0), 
               ID_CTRLPORT2_BASE + 4, "Light Gun");
    AppendMenu(hMenu, MF_STRING | (joyType == JOYSTICK_PORT_COLECOJOYSTICK ? MFS_CHECKED : 0), 
               ID_CTRLPORT2_BASE + 5, "ColecoVision Joystick");
    
    return hMenu;
}

static HMENU menuCreateZoom(Properties* pProperties, Shortcuts* shortcuts)
{
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

static HMENU menuCreateOptions(Properties* pProperties, Shortcuts* shortcuts)
{
    HMENU hMenu = CreatePopupMenu();

    setMenuColor(hMenu);

    AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreateVideoConnect(pProperties, shortcuts), langMenuVideoSource());
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_EMULATION, langMenuPropsEmulation());
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_VIDEO, langMenuPropsVideo());
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_AUDIO, langMenuPropsSound());
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_PERFORMANCE, langMenuPropsPerformance());
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_SETTINGS, langMenuPropsFile());
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_APEARANCE, langMenuPropsSettings());
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_PORTS, langMenuPropsPorts());
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_STRING, ID_OPTIONS_LANGUAGE, langMenuPropsLanguage());

    return hMenu;
}

static HMENU menuCreateHelp(Properties* pProperties, Shortcuts* shortcuts) 
{
    HMENU hMenu = CreatePopupMenu();

    setMenuColor(hMenu);

    AppendMenu(hMenu, MF_STRING, ID_HELP_HELP, langMenuHelpHelp());
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_STRING, ID_HELP_ABOUT, langMenuHelpAbout());

    return hMenu;
}

static HMENU menuCreateTools(Properties* pProperties, Shortcuts* shortcuts)
{
    HMENU hMenu = CreatePopupMenu();
    int count;

    setMenuColor(hMenu);

    AppendMenu(hMenu, MF_STRING, ID_TOOLS_MACHINEEDITOR, langMenuToolsMachine());
    AppendMenu(hMenu, MF_STRING, ID_TOOLS_SHORTCUTSEDITOR, langMenuToolsShortcuts());
    AppendMenu(hMenu, MF_STRING, ID_TOOLS_KEYBOARDEDITOR, langMenuToolsKeyboard());
    AppendMenu(hMenu, MF_STRING, ID_TOOLS_MIXER, langMenuToolsMixer());

    count = toolGetCount();
    if (count > 0) {
        int i;

        AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

        for (i = 0; i < count; i++) {
            AppendMenu(hMenu, MF_STRING, ID_TOOLPLUGINS + i, toolInfoGetName(toolInfoGet(i)));
        }
    }
    
    return hMenu;
}

static HMENU menuCreateFile(Properties* pProperties, Shortcuts* shortcuts, int isStopped, int logSound, int tempStateExits, int enableSpecial) 
{
    HMENU hMenu = CreatePopupMenu();
    _TCHAR menuBuffer[512];

    setMenuColor(hMenu);

    AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreateCart(0, pProperties, shortcuts, enableSpecial), langMenuFileCart1());
    AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreateCart(1, pProperties, shortcuts, enableSpecial), langMenuFileCart2());
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreateDisk(0, pProperties, shortcuts), langMenuFileDiskA());
    AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreateDisk(1, pProperties, shortcuts), langMenuFileDiskB());
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreateCassette(pProperties, shortcuts), langMenuFileCas());
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreateHarddisk(pProperties, shortcuts), langMenuFileHarddisk());
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_POPUP,     (UINT)menuCreatePrinter(pProperties, shortcuts), langMenuFilePrn());
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
    AppendMenu(hMenu, MF_STRING | (logSound ? MFS_CHECKED : 0), ID_FILE_LOGWAV, menuBuffer);

    _stprintf(menuBuffer, "%s        \t%hs", langMenuFileScreenShot(), shortcutsToString(shortcuts->screenCapture));
    AppendMenu(hMenu, MF_STRING, ID_FILE_PTRSCR, menuBuffer);

    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);  

    _stprintf(menuBuffer, "%s        \t%hs", langMenuFileExit(), shortcutsToString(shortcuts->quit));
    AppendMenu(hMenu, MF_STRING, ID_FILE_EXIT, menuBuffer);

    return hMenu;
}

static HMENU menuCreateRun(Properties* pProperties, Shortcuts* shortcuts, int isRunning, int isStopped)
{
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
    if (hMenuHarddisk) DestroyMenu(hMenuHarddisk);
    if (hMenuRun) DestroyMenu(hMenuRun);
    if (hMenuDiskA) DestroyMenu(hMenuDiskA);
    if (hMenuDiskB) DestroyMenu(hMenuDiskB);
    if (hMenuCasette) DestroyMenu(hMenuCasette);
    if (hMenuPrinter) DestroyMenu(hMenuPrinter);
    if (hMenuJoyPort1) DestroyMenu(hMenuJoyPort1);
    if (hMenuJoyPort2) DestroyMenu(hMenuJoyPort2);
    if (hMenuZoom) DestroyMenu(hMenuZoom);
    if (hMenuOptions) DestroyMenu(hMenuOptions);
    if (hMenuHelp) DestroyMenu(hMenuHelp);
    if (hMenuFile) DestroyMenu(hMenuFile);
    if (hMenuTools) DestroyMenu(hMenuTools);

    hMenuReset         = menuCreateReset(pProperties, shortcuts);
    hMenuCartSpecialA  = menuCreateCartSpecial(0, pProperties, shortcuts);
    hMenuCartSpecialB  = menuCreateCartSpecial(1, pProperties, shortcuts);
    hMenuVideoConnect  = menuCreateVideoConnect(pProperties, shortcuts);
    hMenuCartA         = menuCreateCart(0, pProperties, shortcuts, enableSpecial);
    hMenuCartB         = menuCreateCart(1, pProperties, shortcuts, enableSpecial);
    hMenuHarddisk      = menuCreateHarddisk(pProperties, shortcuts);
    hMenuRun           = menuCreateRun(pProperties, shortcuts, isRunning, isStopped);
    hMenuDiskA         = menuCreateDisk(0, pProperties, shortcuts);
    hMenuDiskB         = menuCreateDisk(1, pProperties, shortcuts);
    hMenuCasette       = menuCreateCassette(pProperties, shortcuts);
    hMenuPrinter       = menuCreatePrinter(pProperties, shortcuts);
    hMenuJoyPort1      = menuCreateJoyPort1(pProperties, shortcuts);
    hMenuJoyPort2      = menuCreateJoyPort2(pProperties, shortcuts);
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

void archShowMenuHarddisk(int x, int y) {
    showPopupMenu(hMenuHarddisk, x, y);
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

void archShowMenuJoyPort1(int x, int y) {
    archUpdateMenu(0);
    showPopupMenu(hMenuJoyPort1, x, y);
}

void archShowMenuJoyPort2(int x, int y) {
    archUpdateMenu(0);
    showPopupMenu(hMenuJoyPort2, x, y);
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
    int h;

    // Parse Cart Menu Items
    for (i = 0; i < 2; i++) {
        int cmd = command - i * ID_FILE_CART_OFFSET;
        
        h = cmd - ID_FILE_CART_HISTORY;
        if (h >= 0 && h < MAX_HISTORY) {
            insertCartridge(pProperties, i, pProperties->filehistory.cartridge[i][h], NULL, pProperties->filehistory.cartridgeType[i][h], 0);
            return 1;
        }

        switch (cmd) {
        case ID_FILE_CART_EXTRAM512KB:
            insertCartridge(pProperties, i, CARTNAME_EXTRAM512KB, NULL, ROM_EXTRAM512KB, 0);
            return 1;
        case ID_FILE_CART_EXTRAM1MB:
            insertCartridge(pProperties, i, CARTNAME_EXTRAM1MB, NULL, ROM_EXTRAM1MB, 0);
            return 1;
        case ID_FILE_CART_EXTRAM2MB:
            insertCartridge(pProperties, i, CARTNAME_EXTRAM2MB, NULL, ROM_EXTRAM2MB, 0);
            return 1;
        case ID_FILE_CART_EXTRAM4MB:
            insertCartridge(pProperties, i, CARTNAME_EXTRAM4MB, NULL, ROM_EXTRAM4MB, 0);
            return 1;
        case ID_FILE_CART_GAMEREADER:
            insertCartridge(pProperties, i, CARTNAME_GAMEREADER, NULL, ROM_GAMEREADER, 0);
            return 1;
        case ID_FILE_CART_SUNRISEIDE:
            insertCartridge(pProperties, i, CARTNAME_SUNRISEIDE, NULL, ROM_SUNRISEIDE, 0);
            return 1;
        case ID_FILE_CART_BEERIDE:
            insertCartridge(pProperties, i, CARTNAME_BEERIDE, NULL, ROM_BEERIDE, 0);
            return 1;
        case ID_FILE_CART_GIDE:
            insertCartridge(pProperties, i, CARTNAME_GIDE, NULL, ROM_GIDE, 0);
            return 1;
        case ID_FILE_CART_MEGARAM128:
            insertCartridge(pProperties, i, CARTNAME_MEGARAM128, NULL, ROM_MEGARAM128, 0);
            return 1;
        case ID_FILE_CART_MEGARAM256:
            insertCartridge(pProperties, i, CARTNAME_MEGARAM256, NULL, ROM_MEGARAM256, 0);
            return 1;
        case ID_FILE_CART_MEGARAM512:
            insertCartridge(pProperties, i, CARTNAME_MEGARAM512, NULL, ROM_MEGARAM512, 0);
            return 1;
        case ID_FILE_CART_MEGARAM768:
            insertCartridge(pProperties, i, CARTNAME_MEGARAM768, NULL, ROM_MEGARAM768, 0);
            return 1;
        case ID_FILE_CART_MEGARAM2M:
            insertCartridge(pProperties, i, CARTNAME_MEGARAM2M, NULL, ROM_MEGARAM2M, 0);
            return 1;
        case ID_FILE_CART_SNATCHER:
            insertCartridge(pProperties, i, CARTNAME_SNATCHER, NULL, ROM_SNATCHER, 0);
            return 1;
        case ID_FILE_CART_SDSNATCHER:
            insertCartridge(pProperties, i, CARTNAME_SDSNATCHER, NULL, ROM_SDSNATCHER, 0);
            return 1;
        case ID_FILE_CART_SCCMIRRORED:
            insertCartridge(pProperties, i, CARTNAME_SCCMIRRORED, NULL, ROM_SCCMIRRORED, 0);
            return 1;
        case ID_FILE_CART_SCCEXPANDED:
            insertCartridge(pProperties, i, CARTNAME_SCCEXPANDED, NULL, ROM_SCCEXTENDED, 0);
            return 1;
        case ID_FILE_CART_SCC:
            insertCartridge(pProperties, i, CARTNAME_SCC, NULL, ROM_SCC, 0);
            return 1;
        case ID_FILE_CART_SCCPLUS:
            insertCartridge(pProperties, i, CARTNAME_SCCPLUS, NULL, ROM_SCCPLUS, 0);
            return 1;
        case ID_FILE_CART_FMPAC:
            insertCartridge(pProperties, i, CARTNAME_FMPAC, NULL, ROM_FMPAC, 0);
            return 1;
        case ID_FILE_CART_PAC:            
            insertCartridge(pProperties, i, CARTNAME_PAC, NULL, ROM_PAC, 0);
            return 1;
        case ID_FILE_CART_SONYHBI55:            
            insertCartridge(pProperties, i, CARTNAME_SONYHBI55, NULL, ROM_SONYHBI55, 0);
            return 1;
        case ID_FILE_CART_INSERT:       
            actionCartInsert(i);            
            return 0;
        case ID_FILE_CART_REMOVE:   
            actionCartRemove(i);          
            return 0;
        case ID_FILE_CART_AUTORESET:    
            actionToggleCartAutoReset(i);   
            return 0;
        }
    }

    // Parse Disk Menu Items
    for (i = 0; i < 2; i++) {
        int cmd = command - i * ID_FILE_DISK_OFFSET;
        
        h = cmd - ID_FILE_DISK_HISTORY;
        if (h >= 0 && h < MAX_HISTORY) {
            insertDiskette(pProperties, i, pProperties->filehistory.diskdrive[i][h], NULL, 0);
            return 1;
        }

        switch (cmd) {
        case ID_FILE_DISK_INSERT: 
            actionDiskInsert(i);
            return 0;
        case ID_FILE_DISK_INSERTDIR:      
            actionDiskInsertDir(i); 
            return 0;
        case ID_FILE_DISK_REMOVE:  
            actionDiskRemove(i);
            return 0;
        case ID_FILE_DISK_AUTOSTART:
            actionToggleDiskAutoReset();
            return 0;
        }
    }
    
    // Parse Tape Menu Items
    h = command - ID_FILE_TAPE_HISTORY;
    if (h >= 0 && h < MAX_HISTORY) {
        insertCassette(pProperties, 0, pProperties->filehistory.cassette[0][h], NULL, 0);
        if (pProperties->cassette.autoRewind) {
            tapeSetCurrentPos(0);
        }
        return 1;
    }

    // Parse Harddisk Menu Items
    for (i = 0; i < ID_HARDDISK_COUNT; i++) {
        int cmd = command - i * ID_HARDDISK_OFFSET;
        
        h = command - ID_HARDDISK_HISTORY;
        if (h >= 0 && h < MAX_HISTORY) {
            return 1;   
        }

        switch (cmd) {
        case ID_HARDDISK_INSERT: 
            actionHarddiskInsert(i); 
            return 0;
        case ID_HARDDISK_INSERTNEW:
            actionHarddiskInsertNew(i); 
            return 0;
        case ID_HARDDISK_INSERTDIR:
            actionHarddiskInsertDir(i);
            return 0;
        case ID_HARDDISK_REMOVE:
            actionHarddiskRemove(i);
            return 0;
        }
        
    }

    switch (command) {
    case ID_FILE_TAPE_POSITION:             actionCasSetPosition();         return 0;
    case ID_FILE_TAPE_REWIND:               actionCasRewind();              return 0;
    case ID_FILE_TAPE_INSERT:               actionCasInsert();              return 0;
    case ID_FILE_TAPE_REMOVE:               actionCasRemove();              return 0;
    case ID_FILE_TAPE_READONLY:             actionCasToggleReadonly();      return 0;
    case ID_FILE_TAPE_AUTOREWNIND:          actionToggleCasAutoRewind();    return 0;
    case ID_FILE_TAPE_SAVE:                 actionCasSave();                return 0;
    }

    // Parse other Menu Items

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
        joystickPortSetType(0, i);
        return 1;
    }

    i = command - ID_CTRLPORT2_BASE;
    if (i >= 0 && i < 16) {
        joystickPortSetType(1, i);
        return 1;
    }

    switch (command) {
    case ID_VIDEO_AUTODETECT:
        pProperties->video.chipAutodetect = !pProperties->video.chipAutodetect;
        boardSetVideoAutodetect(pProperties->video.chipAutodetect);
        return 0;
    case ID_FILE_PTRSCR:                        actionScreenCapture();          return 0;
    case ID_FILE_SAVE:                      actionSaveState();              return 0;
    case ID_FILE_LOAD:                      actionLoadState();              return 0;
    case ID_FILE_QSAVE:                     actionQuickSaveState();         return 0;
    case ID_FILE_QLOAD:                     actionQuickLoadState();         return 0;
    case ID_FILE_LOGWAV:                        actionToggleWaveCapture();      return 0;
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
    case ID_FILE_PRINTER_FORMFEED:          actionPrinterForceFormFeed();   return 0;
    case ID_OPTIONS_EMULATION:              actionPropShowEmulation();      return 0;
    case ID_OPTIONS_VIDEO:                  actionPropShowVideo();          return 0;
    case ID_OPTIONS_AUDIO:                  actionPropShowAudio();          return 0;
    case ID_OPTIONS_PERFORMANCE:            actionPropShowPerformance();    return 0;
    case ID_OPTIONS_SETTINGS:               actionPropShowSettings();       return 0;
    case ID_OPTIONS_APEARANCE:              actionPropShowApearance();      return 0;
    case ID_OPTIONS_PORTS:                  actionPropShowPorts();          return 0;
    case ID_OPTIONS_LANGUAGE:               actionOptionsShowLanguage();    return 0;
    case ID_TOOLS_MACHINEEDITOR:            actionToolsShowMachineEditor(); return 0;
    case ID_TOOLS_SHORTCUTSEDITOR:          actionToolsShowShorcutEditor(); return 0;
    case ID_TOOLS_KEYBOARDEDITOR:           actionToolsShowKeyboardEditor();return 0;
    case ID_TOOLS_MIXER:                    actionToolsShowMixer();         return 0;
    case ID_HELP_HELP:                      actionHelpShowHelp();           return 0;
    case ID_HELP_ABOUT:                     actionHelpShowAbout();          return 0;
    }
    return 0;
}