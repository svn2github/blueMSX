/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/rtl8019.h,v $
**
** $Revision: 1.1 $
**
** $Date: 2006-08-26 01:03:35 $
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
#ifndef RTL8019_H
#define RTL8019_H

#include "MsxTypes.h"

typedef struct RTL8019 RTL8019;

RTL8019* rtl8019Create();
void rtl8019Destroy(RTL8019* rtl);
void rtl8019Reset(RTL8019* rtl);

UInt8 rtl8019Read(RTL8019* rtl, UInt8 address);
void rtl8019Write(RTL8019* rtl, UInt8 address, UInt8 value);

void rtl8019SaveState(RTL8019* rtl);
void rtl8019LoadState(RTL8019* rtl);

#endif

