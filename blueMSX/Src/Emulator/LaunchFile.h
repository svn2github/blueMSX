/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Emulator/LaunchFile.h,v $
**
** $Revision: 1.2 $
**
** $Date: 2004-12-06 08:02:49 $
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
#ifndef LAUNCH_FILE_H
#define LAUNCH_FILE_H

#include "RomMapper.h"
#include "Properties.h"

typedef struct {
    char    title[128];
    char    description[128];
    char*   fileList;
    int     fileListCount;
    int     autoReset;
    char    selectFile[512];
    char    zipFileName[512];
    int     selectFileIndex;
    RomType openRomType;
} ZipFileDlgInfo;

int tryLaunchUnknownFile(Properties* properties, char* fileName, int forceAutostart);
int insertCartridge(Properties* properties, int drive, char* fname, char* inZipFile, RomType romType, int forceAutostart);
int insertDiskette(Properties* properties, int drive, char* fname, char* inZipFile, int forceAutostart);
int insertCassette(Properties* properties, char* fname, char* inZipFile, int forceAutostart);

#endif


