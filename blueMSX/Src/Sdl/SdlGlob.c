/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Sdl/SdlGlob.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2006-06-19 18:53:36 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vikl, Tomas Karlsson
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
#ifdef WINDOWS_HOST

#include "ArchGlob.h"
#include <windows.h>
#include <stdlib.h>

// This glob only support very basic globbing, dirs in the patterns are only 
// supported without any wildcards

ArchGlob* archGlob(const char* pattern, int flags)
{
    char oldPath[MAX_PATH];
    const char* filePattern;
    ArchGlob* glob;
    WIN32_FIND_DATA wfd;
    HANDLE handle;

    GetCurrentDirectory(MAX_PATH, oldPath);

    filePattern = strrchr(pattern, '/');
    if (filePattern == NULL) {
        filePattern = pattern;
    }
    else {
        char relPath[MAX_PATH];
        strcpy(relPath, pattern);
        relPath[filePattern - pattern] = '\0';
        pattern = filePattern + 1;
        SetCurrentDirectory(relPath);
    }

    handle = FindFirstFile(pattern, &wfd);
    if (handle == INVALID_HANDLE_VALUE) {
        SetCurrentDirectory(oldPath);
        return NULL;
    }

    glob = (ArchGlob*)calloc(1, sizeof(ArchGlob));

    do {
        DWORD fa;
        if (0 == strcmp(wfd.cFileName, ".") || 0 == strcmp(wfd.cFileName, "..")) {
            continue;
        }
		fa = GetFileAttributes(wfd.cFileName);
        if (((flags & ARCH_GLOB_DIRS) && (fa & FILE_ATTRIBUTE_DIRECTORY) != 0) ||
            ((flags & ARCH_GLOB_FILES) && (fa & FILE_ATTRIBUTE_DIRECTORY) == 0))
        {
            char* path = (char*)malloc(MAX_PATH);
            GetCurrentDirectory(MAX_PATH, path);
            strcat(path, "\\");
            strcat(path, wfd.cFileName);

            glob->count++;
            glob->pathVector = realloc(glob->pathVector, sizeof(char*) * glob->count);
            glob->pathVector[glob->count - 1] = path;
        }
    } while (FindNextFile(handle, &wfd));

    FindClose(handle);

    SetCurrentDirectory(oldPath);

    return glob;
}

void archGlobFree(ArchGlob* globHandle)
{
    int i;

    if (globHandle == NULL) {
        return;
    }
    
    for (i = 0; i < globHandle->count; i++) {
        free(globHandle->pathVector[i]);
    }
    free(globHandle->pathVector);
    free(globHandle);
}

#else

#include "ArchGlob.h"
#include <glob.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ArchGlob* archGlob(const char* pattern, int flags)
{
    ArchGlob* globHandle;
    glob_t g;
    int rv;
    int i;

    rv = glob(pattern, GLOB_MARK, NULL, &g);
    if (rv != 0) {
        return NULL;
    }
    
    globHandle = (ArchGlob*)calloc(1, sizeof(ArchGlob));

    for (i = 0; i < g.gl_pathc; i++) {
        char* path = g.gl_pathv[i];
        int len = strlen(path);

        if ((flags & ARCH_GLOB_DIRS) && path[len - 1] == '/') {
            char* storePath = calloc(1, len);
            memcpy(storePath, path, len - 1);
            globHandle->count++;
            globHandle->pathVector = realloc(globHandle->pathVector, sizeof(char*) * globHandle->count);
            globHandle->pathVector[globHandle->count - 1] = storePath;
        }

        if ((flags & ARCH_GLOB_FILES) && path[len - 1] != '/') {
            char* storePath = calloc(1, len + 1);
            memcpy(storePath, path, len);
            globHandle->count++;
            globHandle->pathVector = realloc(globHandle->pathVector, sizeof(char*) * globHandle->count);
            globHandle->pathVector[globHandle->count - 1] = storePath;
        }
    }

    globfree(&g);

    return globHandle;
}

void archGlobFree(ArchGlob* globHandle)
{
    int i;

    if (globHandle == NULL) {
        return;
    }
    
    for (i = 0; i < globHandle->count; i++) {
        free(globHandle->pathVector[i]);
    }
    if (globHandle->pathVector != NULL) {
        free(globHandle->pathVector);
    }
    free(globHandle);
}

#endif
