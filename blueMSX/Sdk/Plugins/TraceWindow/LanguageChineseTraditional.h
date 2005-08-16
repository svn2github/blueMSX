/*****************************************************************************
** File:
**      LanguageChineseTraditional.h
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
#ifndef LANGUAGE_CHINESE_TRADITIONAL_H
#define LANGUAGE_CHINESE_TRADITIONAL_H

#include "LanguageEnglish.h"

class LanguageChineseTraditional : public LanguageEnglish
{
public:
    LanguageChineseTraditional() {
        traceWindowName         = "Trace Logger";
        traceWindowCaption      = "blueMSX - Trace Logger";
        openWindowCaption       = "Open Log File";

        menuFile                = "檔案";
        menuFileLogToFile       = "Log to File";
        menuFileExit            = "結束";
        
        menuEdit                = "Edit";
        menuEditSelectAll       = "Select All";
        menuEditCopy            = "Copy";
        menuEditClearWindow     = "Clear Window";

        menuHelp                = "說明";
        menuHelpAbout           = "關於";

        aboutBuilt              = "組建:";
        aboutVisit              = "請訪問 http://www.bluemsx.com 取得更多細節";
    }
};

#endif //LANGUAGE_CHINESE_TRADITIONAL_H
