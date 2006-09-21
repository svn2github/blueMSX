/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/wd33c93.h,v $
**
** $Revision: 1.4 $
**
** $Date: 2006-09-21 04:28:06 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2006 Daniel Vik, Ricardo Bittencourt
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
#ifndef WD33C93_H
#define WD33C93_H

#include "MsxTypes.h"

typedef struct WD33C93 WD33C93;

typedef struct {
    UInt32 (*execCommand)(void*, UInt8, UInt8);
    void   (*read)(void*, void*, UInt32);
    void   (*write)(void*, void*, UInt32);
} IoDeviceCallbacks;

WD33C93* wd33c93Create();
void     wd33c93Destroy(WD33C93* wd33c93);

void     wd33c93ReadData(WD33C93* wd33c93, int bytes, UInt8* data);
void     wd33c93WriteData(WD33C93* wd33c93, int bytes, UInt8* data);
void*    wd33c93GetDevice(WD33C93* wd33c93, int id);
int      wd33c93SetDevice(WD33C93* wd33c93, int id, IoDeviceCallbacks* cb, void* ref);
void     wd33c93ClearDma(WD33C93* wd33c93);
int      wd33c93GetDmaCount(WD33C93* wd33c93);
UInt8    wd33c93Read(WD33C93* wd33c93, int offset);
void     wd33c93Write(WD33C93* wd33c93, int offset, unsigned char data);

void     wd33c93LoadState(WD33C93* wd33c93);
void     wd33c93SaveState(WD33C93* wd33c93);

#endif
