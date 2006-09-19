/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32Eth.h,v $
**
** $Revision: 1.4 $
**
** $Date: 2006-09-19 06:00:37 $
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
#ifndef WIN32_ETH_H
#define WIN32_ETH_H

#include "Properties.h"

void ethIfInitialize(Properties* properties);
void ethIfCleanup(Properties* properties);

int ethIfGetCount();
char* ethIfGetName(int index);
int ethIfIsActive(int index);
void ethIfSetActive(int index);


#endif
