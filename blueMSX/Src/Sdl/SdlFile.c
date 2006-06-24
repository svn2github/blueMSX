/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Sdl/SdlFile.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2006-06-24 02:27:08 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2006 Daniel Vik
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
#include "ArchFile.h"

#include <stdlib.h>

#ifdef WINDOWS_HOST

#include <windows.h>
#include <direct.h>
#include <shlobj.h> 
#include <shlwapi.h>

const char* archGetCurrentDirectory()
{
    static char pathname[512];
    GetCurrentDirectory(512, pathname);
    return pathname;
}

int archCreateDirectory(const char* pathname)
{
    return mkdir(pathname);
}

void archSetCurrentDirectory(const char* pathname)
{
    SetCurrentDirectory(pathname);
}

int archFileExists(const char* fileName)
{
    return PathFileExists(fileName);
}

#else

#include <sys/stat.h>
#include <unistd.h>


int archCreateDirectory(const char* pathname)
{
    return mkdir(pathname, 0777);
}

const char* archGetCurrentDirectory()
{
    static char buf[512];
    return getcwd(buf, sizeof(buf));
}

void archSetCurrentDirectory(const char* pathname)
{
    chdir(pathname);
}

int archFileExists(const char* fileName)
{
    struct stat s;
    return stat(fileName, &s) == 0;
}
#endif

/* File dialogs: */
char* archFilenameGetOpenRom(Properties* properties, int cartSlot, RomType* romType) { return NULL; }
char* archFilenameGetOpenDisk(Properties* properties, int drive, int allowCreate) { return NULL; }
char* archFilenameGetOpenHarddisk(Properties* properties, int drive, int allowCreate) { return NULL; }
char* archFilenameGetOpenCas(Properties* properties) { return NULL; }
char* archFilenameGetSaveCas(Properties* properties, int* type) { return NULL; }
char* archFilenameGetOpenState(Properties* properties) { return NULL; }
char* archFilenameGetSaveState(Properties* properties) { return NULL; }
char* archDirnameGetOpenDisk(Properties* properties, int drive) { return NULL; }
char* archFilenameGetOpenRomZip(Properties* properties, int cartSlot, const char* fname, const char* fileList, int count, int* autostart, int* romType) { return NULL; }
char* archFilenameGetOpenDiskZip(Properties* properties, int drive, const char* fname, const char* fileList, int count, int* autostart) { return NULL; }
char* archFilenameGetOpenCasZip(Properties* properties, const char* fname, const char* fileList, int count, int* autostart) { return NULL; }
char* archFilenameGetOpenAnyZip(Properties* properties, const char* fname, const char* fileList, int count, int* autostart, int* romType) { return NULL; }

