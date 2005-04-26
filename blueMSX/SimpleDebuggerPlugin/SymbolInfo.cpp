/*****************************************************************************
** File:        Win32Toolbar.c
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
#include "SymbolInfo.h"
#include <stdio.h>



void SymbolInfo::clear()
{
    symbolMap.erase(symbolMap.begin(), symbolMap.end());
}

const char* SymbolInfo::find(WORD address, WORD& offset)
{
    offset = 0; // Not implemented yet
    std::map<DWORD, Symbol>::const_iterator i = symbolMap.find(address);
    if (i == symbolMap.end()) {
        return NULL;
    }

    return (i->second).name;
}

void SymbolInfo::update(std::string& buffer)
{
    clear();

    int index = 0;
    bool lastLine = false;
    while (!lastLine) {
        int nextIndex = buffer.find('\n', index);

        lastLine = nextIndex == std::string::npos;

        std::string line = lastLine ? buffer.substr(index) : buffer.substr(index, nextIndex - index);

        if (line.length() > 0) {
            char lineBuffer[512];
            strcpy(lineBuffer, line.c_str());
            char* label = strtok(lineBuffer, "\r\n\t ");
            char* addr  = strtok(NULL, "\r\n\t ");
            if (addr && 0 == strcmp(addr, "equ")) {
                addr  = strtok(NULL, "\r\n\t ");
            }
            if (label && addr) {
                int labelLen = strlen(label);
                if (label[labelLen - 1] == ':') {
                    label[labelLen - 1] = 0;
                }
                DWORD address;
                int count = sscanf(addr, "%xh", &address);
                if (count == 1 && labelLen) {
                    symbolMap[address] = Symbol(label);
//                    printf("%.4x: %s\n", address, label);
                }
            }
        }

        index = nextIndex + 1;
    }
}


SymbolInfo::SymbolInfo() : showSymbols(false)
{
}

SymbolInfo::~SymbolInfo()
{
}

void SymbolInfo::show()
{
    showSymbols = true;
}

void SymbolInfo::hide()
{
    showSymbols = false;
}


bool SymbolInfo::getShowStatus()
{
    return showSymbols;
}
