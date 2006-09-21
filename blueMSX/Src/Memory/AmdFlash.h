/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/AmdFlash.h,v $
**
** $Revision: 1.1 $
**
** $Date: 2006-09-21 20:20:49 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2006 Daniel Vik
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
******************************************************************************
*/
#ifndef AMD_FLASH_H
#define AMD_FLASH_H
 
#include "MsxTypes.h"

typedef struct AmdFlash AmdFlash;


AmdFlash* amdFlashCreate(int flashSize, int sectorSize, void* romData, int size, char* sramFilename);
void amdFlashDestroy(AmdFlash* rm);

void amdFlashWrite(AmdFlash* rm, UInt32 address, UInt8 value);
UInt8* amdFlashGetPage(AmdFlash* rm, UInt32 address);
void amdFlashReset(AmdFlash* rm);
void amdFlashSaveState(AmdFlash* rm);
void amdFlashLoadState(AmdFlash* rm);

#endif
