/*****************************************************************************
** $Source:
**
** $Revision:
**
** $Date:
**
** Author: white cat
** File  : sramMapperEseSCC.h
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2007 Daniel Vik, white cat
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
#ifndef SRAMMAPPER_ESESCC_H
#define SRAMMAPPER_ESESCC_H

#include "MsxTypes.h"

int sramMapperEseSCCCreate(char* filename, UInt8* buf, int size, int pSlot, int sSlot, int startPage, int hdId, int mode);

#endif
