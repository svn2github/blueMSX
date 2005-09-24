/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Arch/ArchFile.h,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-09-24 00:10:49 $
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
#ifndef ARCH_FILE_H
#define ARCH_FILE_H

#include "Properties.h"


typedef struct {
    char        title[128];
    char        description[128];
    const char* fileList;
    int         fileListCount;
    int         autoReset;
    char        selectFile[512];
    char        zipFileName[512];
    int         selectFileIndex;
    RomType     openRomType;
} ZipFileDlgInfo;


char* archFilenameGetOpenRom(Properties* properties, int cartSlot, RomType* romType);

char* archFilenameGetOpenDisk(Properties* properties, int drive);

char* archFilenameGetOpenCas(Properties* properties);

char* archFilenameGetSaveCas(Properties* properties, int* type);

char* archFilenameGetOpenState(Properties* properties);

char* archFilenameGetSaveState(Properties* properties);

char* archDirnameGetOpenDisk(Properties* properties, int drive);

char* archFilenameGetOpenRomZip(Properties* properties, int cartSlot, const char* fname, const char* fileList, int count, int* autostart, int* romType);

char* archFilenameGetOpenDiskZip(Properties* properties, int drive, const char* fname, const char* fileList, int count, int* autostart);

char* archFilenameGetOpenCasZip(Properties* properties, const char* fname, const char* fileList, int count, int* autostart);

char* archFilenameGetOpenAnyZip(Properties* properties, const char* fname, const char* fileList, int count, int* autostart, int* romType);

const char* archGetCurrentDirectory();
void archSetCurrentDirectory(const char* pathname);

#endif
