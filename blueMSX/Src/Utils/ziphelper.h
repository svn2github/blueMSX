/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Utils/ziphelper.h,v $
**
** $Revision: 1.3 $
**
** $Date: 2006-09-19 06:00:35 $
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
#ifndef ZIPHELPER_H
#define ZIPHELPER_H

void* zipLoadFile(const char* zipName, const char* fileName, int* size);
int zipSaveFile(const char* zipName, const char* fileName, int append, void* buffer, int size);
char* zipGetFileList(const char* zipName, const char* ext, int* count);
int zipHasFileType(char* zipName, char* ext);

void* zipCompress(void* buffer, int size, int* retSize);

#endif
