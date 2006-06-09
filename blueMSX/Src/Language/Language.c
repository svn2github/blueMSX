/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Language/Language.c,v $
**
** $Revision: 1.56 $
**
** $Date: 2006-06-09 20:30:01 $
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
#include "Language.h"
#include "LanguageStrings.h"
#include <stdlib.h>
#include <stdio.h>
#include <commctrl.h>
#include "Resource.h"

#include "LanguageEnglish.h"
#include "LanguageSwedish.h"
#include "LanguageSpannish.h"
#include "LanguageJapanese.h"
#include "LanguageKorean.h"
#include "LanguagePortuguese.h"
#include "LanguageFrench.h"
#include "LanguageDutch.h"
#include "LanguageItalian.h"
#include "LanguageFinnish.h"
#include "LanguageGerman.h"
#include "LanguagePolish.h"
#include "LanguageChineseSimplified.h"
#include "LanguageChineseTraditional.h"
 
static LanguageStrings langEnglish;
static LanguageStrings langSwedish;
static LanguageStrings langSpanish;
static LanguageStrings langJapanese;
static LanguageStrings langKorean;
static LanguageStrings langPortuguese;
static LanguageStrings langFrench;
static LanguageStrings langDutch;
static LanguageStrings langItalian;
static LanguageStrings langFinnish;
static LanguageStrings langGerman;
static LanguageStrings langPolish;
static LanguageStrings langChineseSimplified;
static LanguageStrings langChineseTraditional;

static LanguageStrings* ls;

typedef struct {
    EmuLanguageType type;
    _TCHAR          name[32];
} LanguageInfo;

static LanguageInfo languageInfo[] = {
    { EMU_LANG_CHINESESIMP, "Chinese Simplified" },
    { EMU_LANG_CHINESETRAD, "Chinese Traditional" },
    { EMU_LANG_DUTCH,       "Dutch" },
    { EMU_LANG_ENGLISH,     "English" },
    { EMU_LANG_FINNISH,     "Finnish" },
    { EMU_LANG_FRENCH,      "French" },
    { EMU_LANG_GERMAN,      "German" },
    { EMU_LANG_ITALIAN,     "Italian" },
    { EMU_LANG_JAPANESE,    "Japanese" },
    { EMU_LANG_KOREAN,      "Korean" },
    { EMU_LANG_POLISH,      "Polish" },
    { EMU_LANG_PORTUGUESE,  "Portuguese" },
    { EMU_LANG_SPANISH,     "Spanish" },
    { EMU_LANG_SWEDISH,     "Swedish" },
    { EMU_LANG_UNKNOWN,     "" }
};

EmuLanguageType langFromName(_TCHAR* name) {
    int i;
    for (i = 0; languageInfo[i].type != EMU_LANG_UNKNOWN; i++) {
        if (0 == _tcscmp(name, languageInfo[i].name)) {
            break;
        }
    }
    return languageInfo[i].type;
}

static BOOL CALLBACK langDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    static int* lang = NULL;

    switch (iMsg) {
    case WM_INITDIALOG:
        {
            char buffer[64];
            HIMAGELIST himlSmall;
            LV_COLUMN lvc = {0};
            LV_ITEM lvi = { 0 };
            int i;

            lang = (int*)lParam;

            SetWindowText(hDlg, langDlgLangTitle());
            SendMessage(GetDlgItem(hDlg, IDC_LANGTXT), WM_SETTEXT, 0, (LPARAM)langDlgLangLangText());
            SetWindowText(GetDlgItem(hDlg, IDOK), langDlgOK());
            SetWindowText(GetDlgItem(hDlg, IDCANCEL), langDlgCancel());

            ListView_SetExtendedListViewStyle(GetDlgItem(hDlg, IDC_LANGLIST), LVS_EX_FULLROWSELECT);

            himlSmall = ImageList_Create(GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), TRUE, 1, 1); 

            ImageList_AddIcon(himlSmall, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FLAG_CHINASIMP))); 
            ImageList_AddIcon(himlSmall, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FLAG_CHINATRAD))); 
            ImageList_AddIcon(himlSmall, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FLAG_NETHERLANDS))); 
            ImageList_AddIcon(himlSmall, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FLAG_USA))); 
            ImageList_AddIcon(himlSmall, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FLAG_FINLAND))); 
            ImageList_AddIcon(himlSmall, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FLAG_FRANCE))); 
            ImageList_AddIcon(himlSmall, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FLAG_GERMANY))); 
            ImageList_AddIcon(himlSmall, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FLAG_ITALY))); 
            ImageList_AddIcon(himlSmall, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FLAG_JAPAN))); 
            ImageList_AddIcon(himlSmall, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FLAG_KOREA))); 
            ImageList_AddIcon(himlSmall, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FLAG_POLAND))); 
            ImageList_AddIcon(himlSmall, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FLAG_BRAZIL))); 
            ImageList_AddIcon(himlSmall, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FLAG_SPAIN))); 
            ImageList_AddIcon(himlSmall, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FLAG_SWEDEN))); 
            
            ListView_SetImageList(GetDlgItem(hDlg, IDC_LANGLIST), himlSmall, LVSIL_SMALL);

            SetFocus(GetDlgItem(hDlg, IDC_LANGLIST));

            lvc.mask       = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
            lvc.fmt        = LVCFMT_LEFT;
            lvc.cx         = 185;
            lvc.pszText    = buffer;
	        lvc.cchTextMax = sizeof(buffer);
            sprintf(buffer, "       %s", langMenuPropsLanguage());

            ListView_InsertColumn(GetDlgItem(hDlg, IDC_LANGLIST), 0, &lvc);

            for (i = 0; languageInfo[i].type != EMU_LANG_UNKNOWN; i++) {
                lvi.mask       = LVIF_IMAGE | LVIF_TEXT;
                lvi.iItem      = i;
                lvi.pszText    = buffer;
	            lvi.cchTextMax = sizeof(buffer);
                lvi.iImage     = i;

                sprintf(buffer, "   %s", languageInfo[i].name);

                ListView_InsertItem(GetDlgItem(hDlg, IDC_LANGLIST), &lvi);
 
                if (languageInfo[i].type == *lang) {
                    ListView_SetItemState(GetDlgItem(hDlg, IDC_LANGLIST), i, LVIS_SELECTED, LVIS_SELECTED);
                }
           }

            return FALSE;
        }

    case WM_NOTIFY:
        switch (wParam) {
        case IDC_LANGLIST:
            if ((((NMHDR FAR *)lParam)->code) == LVN_ITEMACTIVATE) {
                if (ListView_GetSelectedCount(GetDlgItem(hDlg, IDC_LANGLIST))) {
                    int index = ListView_GetNextItem(GetDlgItem(hDlg, IDC_LANGLIST), -1, LVNI_SELECTED);
                    if (index != -1) {
                        SendMessage(hDlg, WM_COMMAND, IDOK, 0);
                    }
                }
            }
            return TRUE;
        }
        break;

    case WM_COMMAND:
        switch(LOWORD(wParam)) {
        case IDOK:
            {
                if (ListView_GetSelectedCount(GetDlgItem(hDlg, IDC_LANGLIST))) {
                    int index = ListView_GetNextItem(GetDlgItem(hDlg, IDC_LANGLIST), -1, LVNI_SELECTED);
                    if (index != -1) {
                        *lang = languageInfo[index].type;
                    }
                }
                EndDialog(hDlg, TRUE);
            }
            return TRUE;
        case IDCANCEL:
            EndDialog(hDlg, FALSE);
            return TRUE;
        }
        break;
    case WM_CLOSE:
        EndDialog(hDlg, FALSE);
        return TRUE;
    }

    return FALSE;
}

void langInit() {
    langInitEnglish(&langEnglish);

    langInitEnglish(&langSwedish);
    langInitSwedish(&langSwedish);
    
    langInitEnglish(&langSpanish);
    langInitSpanish(&langSpanish);
    
    langInitEnglish(&langJapanese);
    langInitJapanese(&langJapanese);
    
    langInitEnglish(&langKorean);
    langInitKorean(&langKorean);
    
    langInitEnglish(&langPortuguese);
    langInitPortuguese(&langPortuguese);
    
    langInitEnglish(&langFrench);
    langInitFrench(&langFrench);
    
    langInitEnglish(&langDutch);
    langInitDutch(&langDutch);
    
    langInitEnglish(&langItalian);
    langInitItalian(&langItalian);
    
    langInitEnglish(&langFinnish);
    langInitFinnish(&langFinnish);
    
    langInitEnglish(&langGerman);
    langInitGerman(&langGerman);

    langInitEnglish(&langPolish);
    langInitPolish(&langPolish);

    langInitEnglish(&langChineseSimplified);
    langInitChineseSimplified(&langChineseSimplified);

    langInitEnglish(&langChineseTraditional);
    langInitChineseTraditional(&langChineseTraditional);
    
    ls = &langEnglish;
}

int langSetLanguage(EmuLanguageType languageType) {
    switch (languageType) {
    case EMU_LANG_ENGLISH:
        ls = &langEnglish;
        break;
    case EMU_LANG_SWEDISH:
        ls = &langSwedish;
        break;
    case EMU_LANG_SPANISH:
        ls = &langSpanish;
        break;
    case EMU_LANG_JAPANESE:
        ls = &langJapanese;
        break;
    case EMU_LANG_KOREAN:
        ls = &langKorean;
        break;
    case EMU_LANG_PORTUGUESE:
        ls = &langPortuguese;
        break;
    case EMU_LANG_FRENCH:
        ls = &langFrench;
        break;
    case EMU_LANG_DUTCH:
        ls = &langDutch;
        break;
    case EMU_LANG_ITALIAN:
        ls = &langItalian;
        break;
    case EMU_LANG_FINNISH:
        ls = &langFinnish;
        break;
    case EMU_LANG_GERMAN:
        ls = &langGerman;
        break;

    case EMU_LANG_POLISH:
        ls = &langPolish;
        break;

    case EMU_LANG_CHINESESIMP:
        ls = &langChineseSimplified;
        break;

    case EMU_LANG_CHINESETRAD:
        ls = &langChineseTraditional;
        break;
    default:
        return 0;
    }

    return 1;
}

int langShowDlg(HWND hwnd, int oldLanguage) {
    int lang = oldLanguage;
    DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LANGUAGE), hwnd, langDlgProc, (LPARAM)&lang);
    return lang;
}


//----------------------
// Generic lines
//----------------------

_TCHAR* langTextDevice() { return ls->textDevice; }
_TCHAR* langTextFilename() { return ls->textFilename; }
_TCHAR* langTextFile() { return ls->textFile; }
_TCHAR* langTextNone() { return ls->textNone; }
_TCHAR* langTextUnknown() { return ls->textUnknown; }


//----------------------
// Warning and Error lines
//----------------------

_TCHAR* langWarningTitle() { return ls->warningTitle; }
_TCHAR* langWarningDiscardChanges()  {return ls->warningDiscardChanges; }
_TCHAR* langWarningOverwriteFile() { return ls->warningOverwriteFile; }
_TCHAR* langErrorTitle() { return ls->errorTitle; }
_TCHAR* langErrorEnterFullscreen() { return ls->errorEnterFullscreen; }
_TCHAR* langErrorDirectXFailed() { return ls->errorDirectXFailed; }
_TCHAR* langErrorNoRomInZip() { return ls->errorNoRomInZip; }
_TCHAR* langErrorNoDskInZip() { return ls->errorNoDskInZip; }
_TCHAR* langErrorNoCasInZip() { return ls->errorNoCasInZip; }
_TCHAR* langErrorNoHelp() { return ls->errorNoHelp; }
_TCHAR* langErrorStartEmu() { return ls->errorStartEmu; }
_TCHAR* langErrorPortableReadonly()  {return ls->errorPortableReadonly; }


//----------------------
// File related lines
//----------------------

_TCHAR* langFileRom() { return ls->fileRom; }
_TCHAR* langFileAll() { return ls->fileAll; }
_TCHAR* langFileCpuState() { return ls->fileCpuState; }
_TCHAR* langFileDisk() { return ls->fileDisk; }
_TCHAR* langFileCas() { return ls->fileCas; }


//----------------------
// Menu related lines
//----------------------

_TCHAR* langMenuNoRecentFiles() { return ls->menuNoRecentFiles; }
_TCHAR* langMenuInsert() { return ls->menuInsert; }
_TCHAR* langMenuEject() { return ls->menuEject; }

_TCHAR* langMenuCartGameReader() { return ls->menuCartGameReader; }
_TCHAR* langMenuCartIde() { return ls->menuCartIde; }
_TCHAR* langMenuCartBeerIde() { return ls->menuCartBeerIde; }
_TCHAR* langMenuCartGIde() { return ls->menuCartGIde; }
_TCHAR* langMenuCartSunriseIde() { return ls->menuCartSunriseIde; }
_TCHAR* langMenuCartSCC() { return ls->menuCartSCC; }
_TCHAR* langMenuCartSCCPlus() { return ls->menuCartSCCPlus; }
_TCHAR* langMenuCartFMPac()  { return ls->menuCartFMPac; }
_TCHAR* langMenuCartPac()  { return ls->menuCartPac; }
_TCHAR* langMenuCartHBI55() { return ls->menuCartHBI55; }
_TCHAR* langMenuCartInsertSpecial() { return ls->menuCartInsertSpecial; }
_TCHAR* langMenuCartMegaRam() { return ls->menuCartMegaRam; }
_TCHAR* langMenuCartExternalRam() { return ls->menuCartExternalRam; }

_TCHAR* langMenuDiskInsertNew() { return ls->menuDiskInsertNew; }
_TCHAR* langMenuDiskDirInsert() { return ls->menuDiskDirInsert; }
_TCHAR* langMenuDiskAutoStart() { return ls->menuDiskAutoStart; }
_TCHAR* langMenuCartAutoReset() { return ls->menuCartAutoReset; }

_TCHAR* langMenuCasRewindAfterInsert() { return ls->menuCasRewindAfterInsert; }
_TCHAR* langMenuCasUseReadOnly() { return ls->menuCasUseReadOnly; }
_TCHAR* langMenuCasSaveAs() { return ls->lmenuCasSaveAs; }
_TCHAR* langMenuCasSetPosition() { return ls->menuCasSetPosition; }
_TCHAR* langMenuCasRewind() { return ls->menuCasRewind; }

_TCHAR* langMenuPrnFormfeed() { return ls->menuPrnFormfeed; }

_TCHAR* langMenuZoomNormal() { return ls->menuZoomNormal; }
_TCHAR* langMenuZoomDouble() { return ls->menuZoomDouble; }
_TCHAR* langMenuZoomFullscreen() { return ls->menuZoomFullscreen; }

_TCHAR* langMenuPropsEmulation() { return ls->menuPropsEmulation; }
_TCHAR* langMenuPropsVideo() { return ls->menuPropsVideo; }
_TCHAR* langMenuPropsSound() { return ls->menuPropsSound; }
_TCHAR* langMenuPropsControls() { return ls->menuPropsControls; }
_TCHAR* langMenuPropsPerformance() { return ls->menuPropsPerformance; }
_TCHAR* langMenuPropsSettings() { return ls->menuPropsSettings; }
_TCHAR* langMenuPropsFile() { return ls->menuPropsFile; }
_TCHAR* langMenuPropsLanguage() { return ls->menuPropsLanguage; }
_TCHAR* langMenuPropsPorts() { return ls->menuPropsPorts; }

_TCHAR* langMenuVideoSource()        { return ls->menuVideoSource; }
_TCHAR* langMenuVideoSourceDefault() { return ls->menuVideoSourceDefault; }
_TCHAR* langMenuVideoChipAutodetect() { return ls->menuVideoChipAutodetect; }
_TCHAR* langMenuVideoInSource() { return ls->menuVideoInSource; }
_TCHAR* langMenuVideoInBitmap() { return ls->menuVideoInBitmap; }

_TCHAR* langMenuHelpHelp() { return ls->menuHelpHelp; }
_TCHAR* langMenuHelpAbout() { return ls->menuHelpAbout; }

_TCHAR* langMenuFileCart() { return ls->menuFileCart; }
_TCHAR* langMenuFileDisk() { return ls->menuFileDisk; }
_TCHAR* langMenuFileCas() { return ls->menuFileCas; }
_TCHAR* langMenuFilePrn() { return ls->menuFilePrn; }
_TCHAR* langMenuFileLoadState() { return ls->menuFileLoadState; }
_TCHAR* langMenuFileSaveState() { return ls->menuFileSaveState; }
_TCHAR* langMenuFileQLoadState() { return ls->menuFileQLoadState; }
_TCHAR* langMenuFileQSaveState() { return ls->menuFileQSaveState; }
_TCHAR* langMenuFileCaptureAudio() { return ls->menuFileCaptureAudio; }
_TCHAR* langMenuFileScreenShot() { return ls->menuFileScreenShot; }
_TCHAR* langMenuFileExit() { return ls->menuFileExit; }
_TCHAR* langMenuFileHarddisk() { return ls->menuFileHarddisk; }
_TCHAR* langMenuFileHarddiskNoPresent() { return ls->menuFileHarddiskNoPesent; }

_TCHAR* langMenuRunRun() { return ls->menuRunRun; }
_TCHAR* langMenuRunPause() { return ls->menuRunPause; }
_TCHAR* langMenuRunStop() { return ls->menuRunStop; }
_TCHAR* langMenuRunSoftReset() { return ls->menuRunSoftReset; }
_TCHAR* langMenuRunHardReset() { return ls->menuRunHardReset; }
_TCHAR* langMenuRunCleanReset() { return ls->menuRunCleanReset; }

_TCHAR* langMenuToolsMachine() { return ls->menuToolsMachine; }
_TCHAR* langMenuToolsShortcuts() { return ls->menuToolsShortcuts; }
_TCHAR* langMenuToolsKeyboard() { return ls->menuToolsKeyboard; }
_TCHAR* langMenuToolsMixer() { return ls->menuToolsMixer; }

_TCHAR* langMenuFile() { return ls->menuFile; }
_TCHAR* langMenuRun() { return ls->menuRun; }
_TCHAR* langMenuWindow() { return ls->menuWindow; }
_TCHAR* langMenuOptions() { return ls->menuOptions; }
_TCHAR* langMenuTools() { return ls->menuTools; }
_TCHAR* langMenuHelp() { return ls->menuHelp; }


//----------------------
// Dialog related lines
//----------------------

_TCHAR* langDlgOK() { return ls->dlgOK; }
_TCHAR* langDlgOpen() { return ls->dlgOpen; }
_TCHAR* langDlgCancel() { return ls->dlgCancel; }
_TCHAR* langDlgSave() { return ls->dlgSave; }
_TCHAR* langDlgSaveAs() { return ls->dlgSaveAs; }
_TCHAR* langDlgRun() { return ls->dlgRun; }
_TCHAR* langDlgClose() { return ls->dlgClose; }

_TCHAR* langDlgLoadRom() { return ls->dlgLoadRom; }
_TCHAR* langDlgLoadDsk() { return ls->dlgLoadDsk; }
_TCHAR* langDlgLoadCas() { return ls->dlgLoadCas; }
_TCHAR* langDlgLoadRomDskCas() { return ls->dlgLoadRomDskCas; }
_TCHAR* langDlgLoadRomDesc() { return ls->dlgLoadRomDesc; }
_TCHAR* langDlgLoadDskDesc() { return ls->dlgLoadDskDesc; }
_TCHAR* langDlgLoadCasDesc() { return ls->dlgLoadCasDesc; }
_TCHAR* langDlgLoadRomDskCasDesc() { return ls->dlgLoadRomDskCasDesc; }
_TCHAR* langDlgLoadState() { return ls->dlgLoadState; }
_TCHAR* langDlgSaveState() { return ls->dlgSaveState; }
_TCHAR* langDlgSaveCassette() { return ls->dlgSaveCassette; }
_TCHAR* langDlgInsertRom1() { return ls->dlgInsertRom1; }
_TCHAR* langDlgInsertRom2() { return ls->dlgInsertRom2; }
_TCHAR* langDlgInsertDiskA() { return ls->dlgInsertDiskA; }
_TCHAR* langDlgInsertDiskB() { return ls->dlgInsertDiskB; }
_TCHAR* langDlgInsertHarddisk() { return ls->dlgInsertHarddisk; }
_TCHAR* langDlgInsertCas() { return ls->dlgInsertCas; }
_TCHAR* langDlgRomType() { return ls->dlgRomType; }

_TCHAR* langDlgTapeTitle() { return ls->dlgTapeTitle; }
_TCHAR* langDlgTapeFrameText() { return ls->dlgTapeFrameText; }
_TCHAR* langDlgTapeCurrentPos() { return ls->dlgTapeCurrentPos; }
_TCHAR* langDlgTapeTotalTime() { return ls->dlgTapeTotalTime; }
_TCHAR* langDlgTapeSetPosText() { return ls->dlgTapeSetPosText; }
_TCHAR* langDlgTapeCustom() { return ls->dlgTapeCustom; }
_TCHAR* langDlgTabPosition() { return ls->dlgTabPosition; }
_TCHAR* langDlgTabType() { return ls->dlgTabType; }
_TCHAR* langDlgTabFilename() { return ls->dlgTabFilename; }
_TCHAR* langDlgZipReset() { return ls->dlgZipReset; }

_TCHAR* langDlgAboutTitle() { return ls->dlgAboutTitle; }

_TCHAR* langDlgLangLangText() { return ls->dlgLangLangText; }
_TCHAR* langDlgLangTitle() { return ls->dlgLangLangTitle; }

_TCHAR* langDlgAboutAbout() { return ls->dlgAboutAbout; }
_TCHAR* langDlgAboutVersion() { return ls->dlgAboutVersion; }
_TCHAR* langDlgAboutBuildNumber() { return ls->dlgAboutBuildNumber; }
_TCHAR* langDlgAboutBuildDate() { return ls->dlgAboutBuildDate; }
_TCHAR* langDlgAboutCreat() { return ls->dlgAboutCreat; }
_TCHAR* langDlgAboutDevel() { return ls->dlgAboutDevel; }
_TCHAR* langDlgAboutThanks() { return ls->dlgAboutThanks; }
_TCHAR* langDlgAboutLisence() { return ls->dlgAboutLisence; }


//----------------------
// Properties related lines
//----------------------

_TCHAR* langPropTitle() { return ls->propTitle; }
_TCHAR* langPropEmulation() { return ls->propEmulation; }
_TCHAR* langPropVideo() { return ls->propVideo; }
_TCHAR* langPropSound() { return ls->propSound; }
_TCHAR* langPropControls() { return ls->propControls; }
_TCHAR* langPropPerformance() { return ls->propPerformance; }
_TCHAR* langPropSettings() { return ls->propSettings; }
_TCHAR* langPropFile()  { return ls->propFile; }
_TCHAR* langPropPorts() { return ls->propPorts; }

_TCHAR* langPropEmuGeneralGB() { return ls->propEmuGeneralGB; }
_TCHAR* langPropEmuFamilyText() { return ls->propEmuFamilyText; }
_TCHAR* langPropEmuMemoryGB() { return ls->propEmuMemoryGB; }
_TCHAR* langPropEmuRamSizeText() { return ls->propEmuRamSizeText; }
_TCHAR* langPropEmuVramSizeText() { return ls->propEmuVramSizeText; }
_TCHAR* langPropEmuSpeedGB() { return ls->propEmuSpeedGB; }
_TCHAR* langPropEmuSpeedText() { return ls->propEmuSpeedText; }
_TCHAR* langPropEmuFrontSwitchGB() { return ls->propEmuFrontSwitchGB; }
_TCHAR* langPropEmuFrontSwitch() { return ls->propEmuFrontSwitch; }
_TCHAR* langPropEmuFdcTiming() { return ls->propEmuFdcTiming; }
_TCHAR* langPropEmuPauseSwitch() { return ls->propEmuPauseSwitch; }
_TCHAR* langPropEmuAudioSwitch() { return ls->propEmuAudioSwitch; }
_TCHAR* langPropVideoFreqText() { return ls->propVideoFreqText; }
_TCHAR* langPropVideoFreqAuto() { return ls->propVideoFreqAuto; }
_TCHAR* langPropSndOversampleText() { return ls->propSndOversampleText; }
_TCHAR* langPropSndYkInGB() { return ls->propSndYkInGB; }
_TCHAR* langPropSndMidiInGB() { return ls->propSndMidiInGB; }
_TCHAR* langPropSndMidiOutGB() { return ls->propSndMidiOutGB; }
_TCHAR* langPropSndMidiChannel() { return ls->propSndMidiChannel; }
_TCHAR* langPropSndMidiAll() { return ls->propSndMidiAll; }

_TCHAR* langPropMonMonGB() { return ls->propMonMonGB; }
_TCHAR* langPropMonTypeText() { return ls->propMonTypeText; }
_TCHAR* langPropMonEmuText() { return ls->propMonEmuText; }
_TCHAR* langPropVideoTypeText() { return ls->propVideoTypeText; }
_TCHAR* langPropWindowSizeText() { return ls->propWindowSizeText; }
_TCHAR* langPropMonHorizStretch() { return ls->propMonHorizStretch; }
_TCHAR* langPropMonVertStretch() { return ls->propMonVertStretch; }
_TCHAR* langPropMonDeInterlace() { return ls->propMonDeInterlace; }
_TCHAR* langPropMonBrightness() { return ls->propMonBrightness; }
_TCHAR* langPropMonContrast() { return ls->propMonContrast; }
_TCHAR* langPropMonSaturation() { return ls->propMonSaturation; }
_TCHAR* langPropMonGamma() { return ls->propMonGamma; }
_TCHAR* langPropMonScanlines() { return ls->propMonScanlines; }
_TCHAR* langPropMonColorGhosting() { return ls->propMonColorGhosting; }
_TCHAR* langPropMonEffectsGB() { return ls->propMonEffectsGB; }

_TCHAR* langPropPerfVideoDrvGB() { return ls->propPerfVideoDrvGB; }
_TCHAR* langPropPerfVideoDispDrvText() { return ls->propPerfVideoDispDrvText; }
_TCHAR* langPropPerfFrameSkipText() { return ls->propPerfFrameSkipText; }
_TCHAR* langPropPerfAudioDrvGB() { return ls->propPerfAudioDrvGB; }
_TCHAR* langPropPerfAudioDrvText() { return ls->propPerfAudioDrvText; }
_TCHAR* langPropPerfAudioBufSzText() { return ls->propPerfAudioBufSzText; }
_TCHAR* langPropPerfEmuGB() { return ls->propPerfEmuGB; }
_TCHAR* langPropPerfSyncModeText() { return ls->propPerfSyncModeText; }
_TCHAR* langPropFullscreenResText() { return ls->propFullscreenResText; }

_TCHAR* langPropSndChipEmuGB() { return ls->propSndChipEmuGB; }
_TCHAR* langPropSndMsxMusic() { return ls->propSndMsxMusic; }
_TCHAR* langPropSndMsxAudio() { return ls->propSndMsxAudio; }
_TCHAR* langPropSndMoonsound() { return ls->propSndMoonsound; }
_TCHAR* langPropSndMt32ToGm() { return ls->propSndMt32ToGm; }

_TCHAR* langPropPortsLptGB() { return ls->propPortsLptGB; }
_TCHAR* langPropPortsComGB() { return ls->propPortsComGB; }
_TCHAR* langPropPortsLptText() { return ls->propPortsLptText; }
_TCHAR* langPropPortsCom1Text() { return ls->propPortsCom1Text; }
_TCHAR* langPropPortsNone() { return ls->propPortsNone; }
_TCHAR* langPropPortsSimplCovox() { return ls->propPortsSimplCovox; }
_TCHAR* langPropPortsFile() { return ls->propPortsFile; }
_TCHAR* langPropPortsComFile()  { return ls->propPortsComFile; }
_TCHAR* langPropPortsOpenLogFile() { return ls->propPortsOpenLogFile; }
_TCHAR* langPropPortsEmulateMsxPrn() { return ls->propPortsEmulateMsxPrn; }

_TCHAR* langPropSetFileHistoryGB() { return ls->propSetFileHistoryGB; }
_TCHAR* langPropSetFileHistorySize() { return ls->propSetFileHistorySize; }
_TCHAR* langPropSetFileHistoryClear() { return ls->propSetFileHistoryClear; }
_TCHAR* langPropFileTypes() { return ls->propFileTypes; }
_TCHAR* langPropWindowsEnvGB() { return ls->propWindowsEnvGB; }
_TCHAR* langPropScreenSaver() { return ls->propSetScreenSaver; }
_TCHAR* langPropDisableWinKeys() { return ls->propDisableWinKeys; }
_TCHAR* langPropPriorityBoost() { return ls->propPriorityBoost; }
_TCHAR* langPropScreenshotPng() { return ls->propScreenshotPng; }
_TCHAR* langPropClearFileHistory() { return ls->propClearHistory; }
_TCHAR* langPropOpenRomGB() { return ls->propOpenRomGB; }
_TCHAR* langPropDefaultRomType() { return ls->propDefaultRomType; }
_TCHAR* langPropGuessRomType() { return ls->propGuessRomType; }

_TCHAR* langPropSettDefSlotGB() { return ls->propSettDefSlotGB; }
_TCHAR* langPropSettDefSlots() { return ls->propSettDefSlots; }
_TCHAR* langPropSettDefSlot() { return ls->propSettDefSlot; }
_TCHAR* langPropSettDefDrives() { return ls->propSettDefDrives; }
_TCHAR* langPropSettDefDrive() { return ls->propSettDefDrive; }

_TCHAR* langPropThemeGB() { return ls->propThemeGB; }
_TCHAR* langPropTheme() { return ls->propTheme; }


//----------------------
// Dropdown related lines
//----------------------

_TCHAR* langEnumVideoMonColor() { return ls->enumVideoMonColor; }
_TCHAR* langEnumVideoMonGrey() { return ls->enumVideoMonGrey; }
_TCHAR* langEnumVideoMonGreen() { return ls->enumVideoMonGreen; }
_TCHAR* langEnumVideoMonAmber() { return ls->enumVideoMonAmber; }

_TCHAR* langEnumVideoTypePAL() { return ls->enumVideoTypePAL; }
_TCHAR* langEnumVideoTypeNTSC() { return ls->enumVideoTypeNTSC; }

_TCHAR* langEnumVideoEmuNone() { return ls->enumVideoEmuNone; }
_TCHAR* langEnumVideoEmuYc() { return ls->enumVideoEmuYc; }
_TCHAR* langEnumVideoEmuMonitor() { return ls->enumVideoEmuMonitor; }
_TCHAR* langEnumVideoEmuYcBlur() { return ls->enumVideoEmuYcBlur; }
_TCHAR* langEnumVideoEmuComp() { return ls->enumVideoEmuComp; }
_TCHAR* langEnumVideoEmuCompBlur() { return ls->enumVideoEmuCompBlur; }
_TCHAR* langEnumVideoEmuScale2x() { return ls->enumVideoEmuScale2x; }
_TCHAR* langEnumVideoEmuHq2x() { return ls->enumVideoEmuHq2x; }

_TCHAR* langEnumVideoSize1x() { return ls->enumVideoSize1x; }
_TCHAR* langEnumVideoSize2x() { return ls->enumVideoSize2x; }
_TCHAR* langEnumVideoSizeFullscreen() { return ls->enumVideoSizeFullscreen; }

_TCHAR* langEnumVideoDrvDirectDrawHW() { return ls->enumVideoDrvDirectDrawHW; }
_TCHAR* langEnumVideoDrvDirectDraw() { return ls->enumVideoDrvDirectDraw; }
_TCHAR* langEnumVideoDrvGDI() { return ls->enumVideoDrvGDI; }

_TCHAR* langEnumVideoFrameskip0() { return ls->enumVideoFrameskip0; }
_TCHAR* langEnumVideoFrameskip1() { return ls->enumVideoFrameskip1; }
_TCHAR* langEnumVideoFrameskip2() { return ls->enumVideoFrameskip2; }
_TCHAR* langEnumVideoFrameskip3() { return ls->enumVideoFrameskip3; }
_TCHAR* langEnumVideoFrameskip4() { return ls->enumVideoFrameskip4; }
_TCHAR* langEnumVideoFrameskip5() { return ls->enumVideoFrameskip5; }

_TCHAR* langEnumSoundDrvNone() { return ls->enumSoundDrvNone; }
_TCHAR* langEnumSoundDrvWMM() { return ls->enumSoundDrvWMM; }
_TCHAR* langEnumSoundDrvDirectX() { return ls->enumSoundDrvDirectX; }

_TCHAR* langEnumEmuSync1ms() { return ls->enumEmuSync1ms; }
_TCHAR* langEnumEmuSyncAuto() { return ls->enumEmuSyncAuto; }
_TCHAR* langEnumEmuSyncNone() { return ls->enumEmuSyncNone; }
_TCHAR* langEnumEmuSyncVblank() { return ls->enumEmuSyncVblank; }
_TCHAR* langEnumEmuAsyncVblank() { return ls->enumEmuAsyncVblank; }

_TCHAR* langEnumControlsJoyNone() { return ls->enumControlsJoyNone; }
_TCHAR* langEnumControlsJoyMouse() { return ls->enumControlsJoyMouse; }
_TCHAR* langEnumControlsJoyTetrisDongle() { return ls->enumControlsJoyTetris2Dongle; }
_TCHAR* langEnumControlsJoyMagicKeyDongle() { return ls->enumControlsJoyTMagicKeyDongle; }
_TCHAR* langEnumControlsJoy2Button() { return ls->enumControlsJoy2Button; }
_TCHAR* langEnumControlsJoyLightGun() { return ls->enumControlsJoyLightGun; }
_TCHAR* langEnumControlsJoyColeco() { return ls->enumControlsJoyColeco; }


//----------------------
// Configuration related lines
//----------------------

_TCHAR* langDlgSavePreview() { return ls->dlgSavePreview; }
_TCHAR* langDlgSaveDate() { return ls->dlgSaveDate; }

_TCHAR* langConfTitle() { return ls->confTitle; }
_TCHAR* langConfConfigText() { return ls->confConfigText; }
_TCHAR* langConfSlotLayout() { return ls->confSlotLayout; }
_TCHAR* langConfMemory() { return ls->confMemory; }
_TCHAR* langConfChipEmulation() { return ls->confChipEmulation; }
_TCHAR* langConfChipExtras() { return ls->confChipExtras; }

_TCHAR* langConfOpenRom() { return ls->confOpenRom; }
_TCHAR* langConfSaveTitle() { return ls->confSaveTitle; }
_TCHAR* langConfSaveText() { return ls->confSaveText; }
_TCHAR* langConfSaveAsTitle() { return ls->confSaveAsTitle; }
_TCHAR* langConfSaveAsMachineName() { return ls->confSaveAsMachineName; }
_TCHAR* langConfDiscardTitle() { return ls->confDiscardTitle; }
_TCHAR* langConfExitSaveTitle() { return ls->confExitSaveTitle; }
_TCHAR* langConfExitSaveText() { return ls->confExitSaveText; }

_TCHAR* langConfSlotLayoutGB() { return ls->confSlotLayoutGB; }
_TCHAR* langConfSlotExtSlotGB() { return ls->confSlotExtSlotGB; }
_TCHAR* langConfBoardGB() { return ls->confBoardGB; }
_TCHAR* langConfBoardText() { return ls->confBoardText; }
_TCHAR* langConfSlotPrimary() { return ls->confSlotPrimary; }
_TCHAR* langConfSlotExpanded() { return ls->confSlotExpanded; }

_TCHAR* langConfCartridge() { return ls->confSlotCart; }
_TCHAR* langConfSlot() { return ls->confSlot; }
_TCHAR* langConfSubslot() { return ls->confSubslot; }

_TCHAR* langConfMemAdd() { return ls->confMemAdd; }
_TCHAR* langConfMemEdit() { return ls->confMemEdit; }
_TCHAR* langConfMemRemove() { return ls->confMemRemove; }
_TCHAR* langConfMemSlot() { return ls->confMemSlot; }
_TCHAR* langConfMemAddress() { return ls->confMemAddresss; }
_TCHAR* langConfMemType() { return ls->confMemType; }
_TCHAR* langConfMemRomImage() { return ls->confMemRomImage; }

_TCHAR* langConfChipVideoGB() { return ls->confChipVideoGB; }
_TCHAR* langConfChipVideoChip() { return ls->confChipVideoChip; }
_TCHAR* langConfChipVideoRam() { return ls->confChipVideoRam; }
_TCHAR* langConfChipSoundGB() { return ls->confChipSoundGB; }

_TCHAR* langConfCmosGB() { return ls->confCmosGB; }
_TCHAR* langConfCmosEnableText() { return ls->confCmosEnable; }
_TCHAR* langConfCmosBatteryText() { return ls->confCmosBattery; }

_TCHAR* langConfChipCpuFreqGB() { return ls->confCpuFreqGB; }
_TCHAR* langConfChipZ80FreqText() { return ls->confZ80FreqText; }
_TCHAR* langConfChipR800FreqText() { return ls->confR800FreqText; }
_TCHAR* langConfChipFdcGB() { return ls->confFdcGB; }
_TCHAR* langConfChipFdcNumDrivesText() { return ls->confCFdcNumDrivesText; }

_TCHAR* langConfEditMemTitle() { return ls->confEditMemTitle; }
_TCHAR* langConfEditMemGB() { return ls->confEditMemGB; }
_TCHAR* langConfEditMemType() { return ls->confEditMemType; }
_TCHAR* langConfEditMemFile() { return ls->confEditMemFile; }
_TCHAR* langConfEditMemAddress() { return ls->confEditMemAddress; }
_TCHAR* langConfEditMemSize() { return ls->confEditMemSize; }
_TCHAR* langConfEditMemSlot() { return ls->confEditMemSlot; }


//----------------------
// Shortcut lines
//----------------------

_TCHAR* langShortcutKey() { return ls->shortcutKey; }
_TCHAR* langShortcutDescription() { return ls->shortcutDescription; }

_TCHAR* langShortcutSaveConfig() { return ls->shortcutSaveConfig; }
_TCHAR* langShortcutOverwriteConfig() { return ls->shortcutOverwriteConfig; }
_TCHAR* langShortcutExitConfig() { return ls->shortcutExitConfig; }
_TCHAR* langShortcutDiscardConfig() { return ls->shortcutDiscardConfig; }
_TCHAR* langShortcutSaveConfigAs() { return ls->shortcutSaveConfigAs; }
_TCHAR* langShortcutConfigName() { return ls->shortcutConfigName; }
_TCHAR* langShortcutNewProfile() { return ls->shortcutNewProfile; }
_TCHAR* langShortcutConfigTitle() { return ls->shortcutConfigTitle; }
_TCHAR* langShortcutAssign() { return ls->shortcutAssign; }
_TCHAR* langShortcutPressText() { return ls->shortcutPressText; }
_TCHAR* langShortcutScheme() { return ls->shortcutScheme; }
_TCHAR* langShortcutCartInsert1() { return ls->shortcutCartInsert1; }
_TCHAR* langShortcutCartRemove1() { return ls->shortcutCartRemove1; }
_TCHAR* langShortcutCartInsert2() { return ls->shortcutCartInsert2; }
_TCHAR* langShortcutCartRemove2() { return ls->shortcutCartRemove2; }
_TCHAR* langShortcutCartSpecialMenu1() { return ls->shortcutSpecialMenu1; }
_TCHAR* langShortcutCartSpecialMenu2() { return ls->shortcutSpecialMenu2; }
_TCHAR* langShortcutCartAutoReset() { return ls->shortcutCartAutoReset; }
_TCHAR* langShortcutDiskInsertA() { return ls->shortcutDiskInsertA; }
_TCHAR* langShortcutDiskDirInsertA() { return ls->shortcutDiskDirInsertA; }
_TCHAR* langShortcutDiskRemoveA() { return ls->shortcutDiskRemoveA; }
_TCHAR* langShortcutDiskChangeA() { return ls->shortcutDiskChangeA; }
_TCHAR* langShortcutDiskAutoResetA() { return ls->shortcutDiskAutoResetA; }
_TCHAR* langShortcutDiskInsertB() { return ls->shortcutDiskInsertB; }
_TCHAR* langShortcutDiskDirInsertB() { return ls->shortcutDiskDirInsertB; }
_TCHAR* langShortcutDiskRemoveB() { return ls->shortcutDiskRemoveB; }
_TCHAR* langShortcutCasInsert() { return ls->shortcutCasInsert; }
_TCHAR* langShortcutCasEject() { return ls->shortcutCasEject; }
_TCHAR* langShortcutCasAutorewind() { return ls->shortcutCasAutorewind; }
_TCHAR* langShortcutCasReadOnly() { return ls->shortcutCasReadOnly; }
_TCHAR* langShortcutCasSetPosition() { return ls->shortcutCasSetPosition; }
_TCHAR* langShortcutCasRewind() { return ls->shortcutCasRewind; }
_TCHAR* langShortcutCasSave() { return ls->shortcutCasSave; }
_TCHAR* langShortcutPrnFormFeed() { return ls->shortcutPrnFormFeed; }
_TCHAR* langShortcutCpuStateLoad() { return ls->shortcutCpuStateLoad; }
_TCHAR* langShortcutCpuStateSave() { return ls->shortcutCpuStateSave; }
_TCHAR* langShortcutCpuStateQload() { return ls->shortcutCpuStateQload; }
_TCHAR* langShortcutCpuStateQsave() { return ls->shortcutCpuStateQsave; }
_TCHAR* langShortcutAudioCapture() { return ls->shortcutAudioCapture; }
_TCHAR* langShortcutScreenshotOrig() { return ls->shortcutScreenshotOrig; }
_TCHAR* langShortcutScreenshotSmall() { return ls->shortcutScreenshotSmall; }
_TCHAR* langShortcutScreenshotLarge() { return ls->shortcutScreenshotLarge; }
_TCHAR* langShortcutQuit() { return ls->shortcutQuit; }
_TCHAR* langShortcutRunPause() { return ls->shortcutRunPause; }
_TCHAR* langShortcutStop() { return ls->shortcutStop; }
_TCHAR* langShortcutResetHard() { return ls->shortcutResetHard; }
_TCHAR* langShortcutResetSoft() { return ls->shortcutResetSoft; }
_TCHAR* langShortcutResetClean() { return ls->shortcutResetClean; }
_TCHAR* langShortcutSizeSmall() { return ls->shortcutSizeSmall; }
_TCHAR* langShortcutSizeNormal() { return ls->shortcutSizeNormal; }
_TCHAR* langShortcutSizeFullscreen() { return ls->shortcutSizeFullscreen; }
_TCHAR* langShortcutSizeMinimized() { return ls->shortcutSizeMinimized; }
_TCHAR* langShortcutToggleFullscren() { return ls->shortcutToggleFullscren; }
_TCHAR* langShortcutVolumeIncrease() { return ls->shortcutVolumeIncrease; }
_TCHAR* langShortcutVolumeDecrease() { return ls->shortcutVolumeDecrease; }
_TCHAR* langShortcutVolumeMute() { return ls->shortcutVolumeMute; }
_TCHAR* langShortcutVolumeStereo() { return ls->shortcutVolumeStereo; }
_TCHAR* langShortcutSwitchMsxAudio() { return ls->shortcutSwitchMsxAudio; }
_TCHAR* langShortcutSwitchFront() { return ls->shortcutSwitchFront; }
_TCHAR* langShortcutSwitchPause() { return ls->shortcutSwitchPause; }
_TCHAR* langShortcutToggleMouseLock() { return ls->shortcutToggleMouseLock; }
_TCHAR* langShortcutEmuSpeedMax() { return ls->shortcutEmuSpeedMax; }
_TCHAR* langShortcutEmuSpeedMaxToggle() { return ls->shortcutEmuSpeedToggle; }
_TCHAR* langShortcutEmuSpeedNormal() { return ls->shortcutEmuSpeedNormal; }
_TCHAR* langShortcutEmuSpeedInc() { return ls->shortcutEmuSpeedInc; }
_TCHAR* langShortcutEmuSpeedDec() { return ls->shortcutEmuSpeedDec; }
_TCHAR* langShortcutThemeSwitch() { return ls->shortcutThemeSwitch; }
_TCHAR* langShortcutShowEmuProp() { return ls->shortcutShowEmuProp; }
_TCHAR* langShortcutShowVideoProp() { return ls->shortcutShowVideoProp; }
_TCHAR* langShortcutShowAudioProp() { return ls->shortcutShowAudioProp; }
_TCHAR* langShortcutShowCtrlProp() { return ls->shortcutShowCtrlProp; }
_TCHAR* langShortcutShowPerfProp() { return ls->shortcutShowPerfProp; }
_TCHAR* langShortcutShowSettProp() { return ls->shortcutShowSettProp; }
_TCHAR* langShortcutShowPorts() { return ls->shortcutShowPorts; }
_TCHAR* langShortcutShowLanguage() { return ls->shortcutShowLanguage; }
_TCHAR* langShortcutShowMachines() { return ls->shortcutShowMachines; }
_TCHAR* langShortcutShowShortcuts() { return ls->shortcutShowShortcuts; }
_TCHAR* langShortcutShowKeyboard() { return ls->shortcutShowKeyboard; }
_TCHAR* langShortcutShowMixer() { return ls->shortcutShowMixer; }
_TCHAR* langShortcutShowDebugger() { return ls->shortcutShowDebugger; }
_TCHAR* langShortcutShowTrainer() { return ls->shortcutShowTrainer; }
_TCHAR* langShortcutShowHelp() { return ls->shortcutShowHelp; }
_TCHAR* langShortcutShowAbout() { return ls->shortcutShowAbout; }
_TCHAR* langShortcutShowFiles() { return ls->shortcutShowFiles; }
_TCHAR* langShortcutToggleSpriteEnable() { return ls->shortcutToggleSpriteEnable; }
_TCHAR* langShortcutToggleFdcTiming() { return ls->shortcutToggleFdcTiming; }
_TCHAR* langShortcutToggleCpuTrace() { return ls->shortcutToggleCpuTrace; }


//----------------------
// Keyboard config lines
//----------------------

_TCHAR* langKeyconfigSelectedKey() { return ls->keyconfigSelectedKey; }
_TCHAR* langKeyconfigMappedTo() { return ls->keyconfigMappedTo; }
_TCHAR* langKeyconfigMappingScheme() { return ls->keyconfigMappingScheme; }
