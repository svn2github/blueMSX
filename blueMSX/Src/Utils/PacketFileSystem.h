/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Utils/PacketFileSystem.h,v $
**
** $Revision: 1.1 $
**
** $Date: 2008-03-30 06:54:01 $
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
#ifndef PACKET_FILESYSTEM_H
#define PACKET_FILESYSTEM_H

// The Packet File System redefines the file io routines.
// An fopen call first looks for the file to open in the
// current package. If not found in the package, regular
// fopen is called.
// A file opened that was found in the package will cause
// consecutive calls to file methods to access the package.

// The PacketFileSystem.h should be included after all
// standard include files in order to correctly redefine
// the file io methods.



int pkg_load(const char* filename, char* key, int keyLen);
void pkg_unload();

#ifdef USE_PACKET_FS

#define fopen   pkg_fopen
#define fclose  pkg_fclose
#define fread   pkg_fread
#define fwrite  pkg_fwrite
#define fseek   pkg_fseek
#define ftell   pkg_ftell
#define fgets   pkg_fgets

#endif

#endif
