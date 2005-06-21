/*****************************************************************************
** File:        Language.c
**
** Author:      Daniel Vik
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
#include <stdlib.h>

class LanguageEnglish : public Language
{
public:
    LanguageEnglish() {
        genericOk                   = "OK";
        genericCancel               = "Cancel";

        toolbarResume               = "Start/Continue";
        toolbarPause                = "Break All";
        toolbarStop                 = "Stop Debugging";
        toolbarRun                  = "Restart";
        toolbarShowNext             = "Show Next Statement";
        toolbarStepIn               = "Step Into";
        toolbarStepOver             = "Step Over";
        toolbarStepOut              = "Step Out";
        toolbarRunTo                = "Run To Cursor";
        toolbarBpToggle             = "Set/Remove Breakpoint";
        toolbarBpEnable             = "Enable/Disable Breakpoint";
        toolbarBpEnableAll          = "Enable All Breakpoints";
        toolbarBpDisableAll         = "Disable All Breakpoints";
        toolbarBpRemoveAll          = "Remove All Breakpoints";

        menuFile                    = "File";
        menuFileLoadSymbolFile      = "Load Symbol File";
        menuFileExit                = "Exit";

        menuDebug                   = "Debug";
        menuDebugStart              = "Start";
        menuDebugContinue           = "Continue";
        menuDebugBreakAll           = "Break All";
        menuDebugStop               = "Stop Debugging";
        menuDebugRestart            = "Restart";
        menuDebugStepIn             = "Step Into";
        menuDebugStepOver           = "Step Over";
        menuDebugStepOut            = "Step Out";
        menuDebugRunTo              = "Run To Cursor";
        menuDebugShowSymbols        = "Show Symbol Information";
        menuDebugGoto               = "Go To";
        menuDebugBpAdd              = "Add New Breakpoint";
        menuDebugBpToggle           = "Set/Remove Breakpoint";
        menuDebugEnable             = "Enable/Disable Breakpoint";
        menuDebugRemoveAll          = "Remove All Breakpoints";
        menuDebugEnableAll          = "Enable All Breakpoints";
        menuDebugDisableAll         = "Disable All Breakpoints";
        menuDebugShowAssemblyFlags  = "Show Assembly Flags";

        menuWindow                  = "Window";

        menuHelp                    = "Help";
        menuHelpAbout               = "About";

        windowDebugger              = "blueMSX - Debugger";
        windowDisassembly           = "Disassembly";
        windowDisassemblyUnavail    = "Disassembly unavailable.";
        windowCpuRegisters          = "CPU Registers";
        windowStack                 = "Stack";
        windowStackUnavail          = "Stack unavailable.";
        windowCallstack             = "Callstack";
        windowCallstackUnavail      = "Callstack unavailable.";
        windowMemory                = "Memory";

        memWindowMemory             = "Memory:";
        memWindowAddress            = "Address:";

        setBpWindowCaption          = "Add New Breakpoint";
        gotoWindowCaption           = "Go To Address";
        gotoWindowText              = "Address or Label:";

        symbolWindowCaption         = "Open Symbol File";
        symbolWindowText            = "Replace old symbols";
        
        aboutBuilt                  = "Built:";
        aboutVisit                  = "Visit http://www.bluemsx.com for details";
    }
};


class LanguageJapanese : public Language
{
public:
    LanguageJapanese() {
        genericOk                   = "OK";
        genericCancel               = "�L�����Z��";

        toolbarResume               = "�J�n/���s";
        toolbarPause                = "�S�Ē�~";
        toolbarStop                 = "�f�o�b�O���~";
        toolbarRun                  = "���X�^�[�g";
        toolbarShowNext             = "���̃X�e�[�g�����g�\\��";
        toolbarStepIn               = "�X�e�b�v �C��";
        toolbarStepOver             = "�X�e�b�v �I�[�o�[";
        toolbarStepOut              = "�X�e�b�v �A�E�g";
        toolbarRunTo                = "�J�[�\\���Ŏ��s";
        toolbarBpToggle             = "�u���C�N�|�C���g/����";
        toolbarBpEnable             = "�u���C�N�|�C���g�L/��";
        toolbarBpEnableAll          = "�u���C�N�|�C���g�S�L����";
        toolbarBpDisableAll         = "�u���C�N�|�C���g�S������";
        toolbarBpRemoveAll          = "�u���C�N�|�C���g�S����";

        menuFile                    = "�t�@�C��";
        menuFileLoadSymbolFile      = "�V���{���t�@�C���̃��[�h";
        menuFileExit                = "�I��";

        menuDebug                   = "�f�o�b�O";
        menuDebugStart              = "�J�n";
        menuDebugContinue           = "���s";
        menuDebugBreakAll           = "�S�Ē�~";
        menuDebugStop               = "�f�o�b�O���~";
        menuDebugRestart            = "���X�^�[�g";
        menuDebugStepIn             = "�X�e�b�v �C��";
        menuDebugStepOver           = "�X�e�b�v �I�[�o�[";
        menuDebugStepOut            = "�X�e�b�v �A�E�g";
        menuDebugRunTo              = "�J�[�\\���Ŏ��s";
        menuDebugShowSymbols        = "�V���{�����\\��";
        menuDebugGoto               = "�ړ�";
        menuDebugBpAdd              = "Add New Breakpoint";
        menuDebugBpToggle           = "�u���C�N�|�C���g�̃Z�b�g/����";
        menuDebugEnable             = "�u���C�N�|�C���g�L/��";
        menuDebugRemoveAll          = "�u���C�N�|�C���g�S����";
        menuDebugEnableAll          = "�u���C�N�|�C���g�S�L����";
        menuDebugDisableAll         = "�u���C�N�|�C���g�S������";
        menuDebugShowAssemblyFlags  = "Show Assembly Flags";

        menuWindow                  = "�E�B���h�E";

        menuHelp                    = "�w���v";
        menuHelpAbout               = "�f�o�b�K�[�ɂ���";

        windowDebugger              = "blueMSX - Debugger";
        windowDisassembly           = "�t�A�Z���u��";
        windowDisassemblyUnavail    = "Disassembly unavailable.";
        windowCpuRegisters          = "CPU ���W�X�^";
        windowStack                 = "�X�^�b�N";
        windowStackUnavail          = "Stack unavailable.";
        windowCallstack             = "�R�[���X�^�b�N";
        windowCallstackUnavail      = "Callstack unavailable.";
        windowMemory                = "������";

        memWindowMemory             = "������:";
        memWindowAddress            = "�A�h���X:";

        setBpWindowCaption          = "Add New Breakpoint";
        gotoWindowCaption           = "�A�h���X�Ɉړ�";
        gotoWindowText              = "�A�h���X�܂��̓��x��:";

        symbolWindowCaption         = "Open Symbol File";
        symbolWindowText            = "�V���{���̓���ւ�";
        
        aboutBuilt                  = "Built:";
        aboutVisit                  = "Visit http://www.bluemsx.com for details";
    }
};




namespace {
    Language* ls = new LanguageEnglish;
}


void Language::SetLanguage(LanguageId langId) 
{
    delete ls;
    switch (langId) {
    case LID_JAPANESE:
        ls = new LanguageJapanese;
        break;
    case LID_ENGLISH:
    default:
        ls = new LanguageEnglish;
        break;
    }
}

const char* Language::genericOk;
const char* Language::genericCancel;

const char* Language::toolbarResume;
const char* Language::toolbarPause;
const char* Language::toolbarStop;
const char* Language::toolbarRun;
const char* Language::toolbarShowNext;
const char* Language::toolbarStepIn;
const char* Language::toolbarStepOver;
const char* Language::toolbarStepOut;
const char* Language::toolbarRunTo;
const char* Language::toolbarBpToggle;
const char* Language::toolbarBpEnable;
const char* Language::toolbarBpEnableAll;
const char* Language::toolbarBpDisableAll;
const char* Language::toolbarBpRemoveAll;

const char* Language::menuFile;
const char* Language::menuFileLoadSymbolFile;
const char* Language::menuFileExit;

const char* Language::menuDebug;
const char* Language::menuDebugStart;
const char* Language::menuDebugContinue;
const char* Language::menuDebugBreakAll;
const char* Language::menuDebugStop;
const char* Language::menuDebugRestart;
const char* Language::menuDebugStepIn;
const char* Language::menuDebugStepOver;
const char* Language::menuDebugStepOut;
const char* Language::menuDebugRunTo;
const char* Language::menuDebugShowSymbols;
const char* Language::menuDebugGoto;
const char* Language::menuDebugBpAdd;
const char* Language::menuDebugBpToggle;
const char* Language::menuDebugEnable;
const char* Language::menuDebugRemoveAll;
const char* Language::menuDebugEnableAll;
const char* Language::menuDebugDisableAll;
const char* Language::menuDebugShowAssemblyFlags;

const char* Language::menuWindow;
const char* Language::menuHelp;
const char* Language::menuHelpAbout;

const char* Language::windowDebugger;
const char* Language::windowDisassembly;
const char* Language::windowDisassemblyUnavail;
const char* Language::windowCpuRegisters;
const char* Language::windowStack;
const char* Language::windowStackUnavail;
const char* Language::windowCallstack;
const char* Language::windowCallstackUnavail;
const char* Language::windowMemory;

const char* Language::memWindowMemory;
const char* Language::memWindowAddress;

const char* Language::setBpWindowCaption;
const char* Language::gotoWindowCaption;
const char* Language::gotoWindowText;

const char* Language::symbolWindowCaption;
const char* Language::symbolWindowText;

const char* Language::aboutBuilt;
const char* Language::aboutVisit;
