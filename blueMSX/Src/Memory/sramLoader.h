/*****************************************************************************
** File:
**      sramLoader.h
**
** Author:
**      Daniel Vik
**
** Description:
**      SRAM helper methods.
**
** More info:   
**      www.bluemsx.com
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
#ifndef SRAM_LOADER_H
#define SRAM_LOADER_H
 
#include "MSXTypes.h"

char* sramCreateFilename(char* romFilename);
char* sramCreateFilenameWithSuffix(char* romFilename, char* suffix);
void sramLoad(char* filename, UInt8* sram, int length, void* header, int headerLength);
void sramSave(char* filename, UInt8* sram, int length, void* header, int headerLength);

#endif
