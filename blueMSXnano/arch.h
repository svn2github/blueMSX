/*****************************************************************************
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
#ifndef ARCH_H
#define ARCH_H

#ifdef WIN32

typedef unsigned char    UInt8;
typedef   signed char    Int8;
typedef unsigned short   UInt16;
typedef   signed short   Int16;
typedef unsigned long    UInt32;
typedef   signed long    Int32;
typedef unsigned __int64 UInt64;
typedef   signed __int64 Int64;
#else
typedef unsigned char      UInt8;
typedef   signed char      Int8;
typedef unsigned short     UInt16;
typedef   signed short     Int16;
typedef unsigned int       UInt32;
typedef   signed int       Int32;
typedef unsigned long long UInt64;
typedef   signed long long Int64;
#endif


// Set cursor location in console
void setpos(int x, int y);

// Return pressed key or 0 if no key is pressed
char pollkbd(void);

// Get system time in microseconds
unsigned long gettime(void);

// Delay ms milliseconds
void delay(unsigned long ms);

// Clears console screen
void clearscreen(void);

#endif