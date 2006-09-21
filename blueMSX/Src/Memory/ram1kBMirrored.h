/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/ram1kBMirrored.h,v $
**
** $Revision: 1.4 $
**
** $Date: 2006-09-21 04:28:07 $
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
#ifndef RAM_1KB_MIRRORED_H
#define RAM_1KB_MIRRORED_H

#include "MsxTypes.h"

int ramMirroredCreate(int size, int slot, int sslot, int startPage, UInt32 ramBlockSize, 
                      UInt8** ramPtr, UInt32* ramSize);

#endif
