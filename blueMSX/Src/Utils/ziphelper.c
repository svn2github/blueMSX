/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Utils/ziphelper.c,v $
**
** $Revision: 1.7 $
**
** $Date: 2009-07-18 14:10:27 $
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
#include "zip.h"
#include "unzip.h"
#include "ctype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void toLower(char* str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}

/******************************************************************************
*** Description
***     Load a file in a zip file into memory.
***
*** Arguments
***     zipName     - Name of zip file
***     fileName    - Name of file insize zipfile to load
***     size        - Output of size of file
***
*** Return
***     Pointer to allocate memory buffer with file content or NULL on
***     failure.
***
*******************************************************************************
*/
void* _zipLoadFile(const char* zipName, const char* fileName, int* size, zlib_filefunc_def* filefunc)
{
    void* buf;
    char name[256];
    unzFile zip;
    unz_file_info info;

    *size = 0;

    if (fileName[0] == '*') {
        strcpy(name, zipName);
        name[strlen(zipName) - 3] = fileName[strlen(fileName) - 3];
        name[strlen(zipName) - 2] = fileName[strlen(fileName) - 2];
        name[strlen(zipName) - 1] = fileName[strlen(fileName) - 1];
    }
    else {
        strcpy(name, fileName);
    }

    zip = unzOpen2(zipName, filefunc);
    if (!zip) {
        return NULL;
    }

    if (unzLocateFile(zip, name, 1) == UNZ_END_OF_LIST_OF_FILE) {
        unzClose(zip);
        return NULL;
    }

    if (unzOpenCurrentFile(zip) != UNZ_OK) {
        return NULL;
    }

    unzGetCurrentFileInfo(zip,&info,NULL,0,NULL,0,NULL,0);

    buf = malloc(info.uncompressed_size);
    *size = info.uncompressed_size;

    if (!buf) {
        unzCloseCurrentFile(zip);
        unzClose(zip);
        return NULL;
    }

    unzReadCurrentFile(zip, buf, info.uncompressed_size);
    unzCloseCurrentFile(zip);
    unzClose(zip);

    return buf;
}


/******************************************************************************
*** Description
***     Read cache to speed-up reading multiple files from one zip.
***
******************************************************************************/

static unsigned long memfile_index;
static unsigned long memfile_size;

void *fopen_mem_func(void *opaque, const char *filename, int mode)
{
    memfile_index = 0;
    return (void *)filename;
}

unsigned long fread_mem_func(void *opaque, void *stream, void *buf, unsigned long size)
{
    if( memfile_index + size > memfile_size ) {
        size = memfile_size - memfile_index;
    }
    memcpy(buf, (char*)stream + memfile_index, size);
    memfile_index += size;
    return size;
}

unsigned long fwrite_mem_func(void *opaque, void *stream, const void *buf, unsigned long size)
{
    return -1;
}

long ftell_mem_func(void *opaque, void *stream)
{
    return memfile_index;
}

long fseek_mem_func(void *opaque, void *stream, unsigned long offset, int origin)
{
    switch (origin)
    {
    case ZLIB_FILEFUNC_SEEK_CUR :
        memfile_index += offset;
        break;
    case ZLIB_FILEFUNC_SEEK_END :
        memfile_index = memfile_size - offset;
        break;
    case ZLIB_FILEFUNC_SEEK_SET :
        memfile_index = offset;
        break;
    default: return -1;
    }
    if( memfile_index > memfile_size ) memfile_index = memfile_size;
    if( memfile_index < 0 ) memfile_index = 0;
    return 0;
}

int fclose_mem_func(void *opaque, void *stream)
{
    return 0;
}

int ferror_mem_func(void *opaque, void *stream)
{
    return 0;
}

void fill_fopen_memfunc(zlib_filefunc_def *pzlib_filefunc_def)
{
    pzlib_filefunc_def->zopen_file = fopen_mem_func;
    pzlib_filefunc_def->zread_file = fread_mem_func;
    pzlib_filefunc_def->zwrite_file = fwrite_mem_func;
    pzlib_filefunc_def->ztell_file = ftell_mem_func;
    pzlib_filefunc_def->zseek_file = fseek_mem_func;
    pzlib_filefunc_def->zclose_file = fclose_mem_func;
    pzlib_filefunc_def->zerror_file = ferror_mem_func;
    pzlib_filefunc_def->opaque = NULL;
}

static char *cacheData = NULL, cacheFile[512];
static zlib_filefunc_def cacheFilefunc;

void* zipLoadFile(const char* zipName, const char* fileName, int* size)
{
    if( cacheData != NULL && *cacheFile != '\0' && 0==strcmp(cacheFile, zipName) ) {
        return _zipLoadFile(cacheData, fileName, size, &cacheFilefunc);
    }else{
        return _zipLoadFile(zipName, fileName, size, NULL);
    }
}

void zipCacheReadOnlyZip(const char* zipName)
{
    *cacheFile = '\0';
    if( cacheData != NULL ) {
        free(cacheData);
        cacheData = NULL;
    }
    if( zipName != NULL ) {
        FILE *file;
        fill_fopen_memfunc(&cacheFilefunc);
        file = fopen(zipName, "rb");
        if( file != NULL ) {
            fseek(file, 0, SEEK_END);
            memfile_size = ftell(file);
            fseek(file, 0, SEEK_SET);
            cacheData = malloc(memfile_size);
            if( cacheData != NULL ) {
                size_t size = fread(cacheData, 1, memfile_size, file);
                if( size == memfile_size ) {
                    strcpy(cacheFile, zipName);
                }
            }
            fclose(file);
        }
    }
}



/******************************************************************************
*** Description
***     Load a file in a zip file into memory.
***
*** Arguments
***     zipName     - Name of zip file
***     fileName    - Name of file insize zipfile to save
***     buffer      - Buffer to save
***     size        - Size of buffer to save
***
*******************************************************************************
*/
int zipSaveFile(const char* zipName, char* fileName, int append, void* buffer, int size)
{
    zipFile zip;
    zip_fileinfo zi;
    int err;

    zip = zipOpen(zipName, append ? 2 : 0);
    if (zip == NULL) {
        return 0;
    }

    memset(&zi, 0, sizeof(zi));

    err = zipOpenNewFileInZip(zip, fileName, &zi,
                              NULL, 0, NULL, 0, NULL,
                              Z_DEFLATED, Z_DEFAULT_COMPRESSION);
    if (err == ZIP_OK) {
        err = zipWriteInFileInZip(zip, buffer, size);
    }

    zipClose(zip, NULL);

    return err >= 0;
}

int zipHasFileType(char* zipName, char* ext) {
    char tempName[256];
    char extension[8];
    unzFile zip;
    unz_file_info info;
    int found = 0;
    int status;

    zip = unzOpen(zipName);
    if (!zip) {
        return 0;
    }

    strcpy(extension, ext);
    toLower(extension);

    status = unzGoToFirstFile(zip);
    unzGetCurrentFileInfo(zip,&info,tempName,256,NULL,0,NULL,0);

    while (status == UNZ_OK) {
        unzGetCurrentFileInfo(zip, &info, tempName, 256, NULL, 0, NULL, 0);

        toLower(tempName);
        if (strstr(tempName, extension) != NULL) {
            found = 1;
            break;
        }

        status = unzGoToNextFile(zip);
    }

    unzClose(zip);

    return found;
}

/******************************************************************************
*** Description
***     Checks if a file exists in a zip file.
***
*** Arguments
***     zipName     - Name of zip file
***     fileName    - Name of file insize zipfile to load
***
*** Return
***     1 = file exists, 0 = non existing zip or file in zip does not exists
***     failure.
***
*******************************************************************************
*/
int zipFileExists(const char* zipName, const char* fileName)
{
    char name[256];
    unzFile zip;

    if (fileName[0] == '*') {
        strcpy(name, zipName);
        name[strlen(zipName) - 3] = fileName[strlen(fileName) - 3];
        name[strlen(zipName) - 2] = fileName[strlen(fileName) - 2];
        name[strlen(zipName) - 1] = fileName[strlen(fileName) - 1];
    }
    else {
        strcpy(name, fileName);
    }

    zip = unzOpen(zipName);
    if (!zip) {
        return 0;
    }

    if (unzLocateFile(zip, name, 1) == UNZ_END_OF_LIST_OF_FILE) {
        unzClose(zip);
        return 0;
    }else{
        unzClose(zip);
        return 1;
    }
}

/******************************************************************************
*** Description
***     Creates a list of file names inside a zip that matches a given
***     extension.
***
*** Arguments
***     zipName     - Name of zip file
***     ext         - Extension to check
***     count       - Output for number of matching files in zip file.
***
*** Return
***     1 if files with the given extension exists in the zip file,
***     0 otherwise.
***
*******************************************************************************
*/
char* zipGetFileList(char* zipName, char* ext, int* count) {
    char tempName[256];
    char extension[8];
    unzFile zip;
    unz_file_info info;
    char* fileArray = NULL;
    int totalLen = 0;
    int status;

    *count = 0;

    zip = unzOpen(zipName);
    if (!zip) {
        return 0;
    }

    strcpy(extension, ext);
    toLower(extension);

    status = unzGoToFirstFile(zip);
    unzGetCurrentFileInfo(zip,&info,tempName,256,NULL,0,NULL,0);

    while (status == UNZ_OK) {
        char tmp[256];

        unzGetCurrentFileInfo(zip, &info, tempName, 256, NULL, 0, NULL, 0);

        strcpy(tmp, tempName);

        toLower(tmp);
        if (strstr(tmp, extension) != NULL) {
            int entryLen = strlen(tempName) + 1;
            fileArray = realloc(fileArray, totalLen +  entryLen + 1);
            strcpy(fileArray + totalLen, tempName);
            totalLen += entryLen;
            fileArray[totalLen] = '\0'; // double null termination at end

            *count = *count + 1;
        }

        status = unzGoToNextFile(zip);
    }

    unzClose(zip);

    return fileArray;
}

void* zipCompress(void* buffer, int size, unsigned long* retSize)
{
    void* retBuf;

    *retSize = (size * 1001) / 1000 + 12;
    retBuf = malloc(*retSize);

    if (compress(retBuf, retSize, buffer, size) != Z_OK) {
        free(retBuf);
        retBuf = NULL;
    }

    return retBuf;
}
