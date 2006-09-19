/*****************************************************************************
** File:        msxTypes.h
**
** Author:      Daniel Vik
**
** Description: Type definitions
**
** More info:   www.bluemsx.com
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
#ifndef BLUEMSX_TYPES
#define BLUEMSX_TYPES

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __GNUC__
#define __int64 long long
#endif

#ifdef _WIN32
#define DIR_SEPARATOR "\\"
#else
#define DIR_SEPARATOR "/"
#endif

/* So far, only support for MSVC types
 */
typedef unsigned char    UInt8;
typedef unsigned short   UInt16;
typedef unsigned long    UInt32;
typedef unsigned __int64 UInt64;
typedef signed   char    Int8;
typedef signed   short   Int16;
typedef signed   long    Int32;


// Debug replacement for malloc and free to easier find memory leaks.
#if 0

#define malloc dbgMalloc
#define calloc dbgCalloc
#define free   dbgFree

#include <stdlib.h>

void* dbgMalloc(size_t size);
void* dbgCalloc(size_t size, size_t count);
void dbgFree(void* ptr);
void dbgEnable();
void dbgDisable();
void dbgPrint();

#else

#define dbgEnable()
#define dbgDisable()
#define dbgPrint()

#endif

#ifdef __cplusplus
}
#endif


#endif
