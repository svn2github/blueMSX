/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Emulator/FileHistory.c,v $
**
** $Revision: 1.7 $
**
** $Date: 2005-01-30 23:17:29 $
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
#include "FileHistory.h"
#include "Properties.h"
#include "ziphelper.h"
#include "RomLoader.h"
#include <stdio.h>
#include <sys/stat.h>
#include <direct.h>

static char extendedName[2][256];
static char extendedDiskName[2][256];
static char extendedCasName[256];

char* stripPathExt(char* filename) {
    static char buffer[128];
    
    strcpy(buffer, stripPath(filename));

    if (buffer[strlen(buffer) - 4] == '.') {
        buffer[strlen(buffer) - 4] = 0;
    }

    return buffer;
}

char* stripPath(char* filename) {
    char* ptr = filename + strlen(filename) - 1;

    while (--ptr >= filename) {
        if (*ptr == '/' || *ptr == '\\') {
            return ptr + 1;
        }
    }

    return filename;
}

void updateFileHistory(char* history, RomType* historyType, char* filename, RomType romType) {
    char fname[MAX_PATH];
    int i = 0;

    strcpy(fname, filename);

    for (i = 0; i < MAX_HISTORY - 1; i++) {
        if (*(history + MAX_PATH * i) == 0 || 0 == strcmp(history + MAX_PATH * i, fname)) {
            break;
        }
    }
    while (i > 0) {
        strcpy(history + MAX_PATH * i, history + MAX_PATH * (i - 1));
        if (historyType) historyType[i] = historyType[i - 1];
        i--;
    }
    strcpy(history, fname);
    if (historyType) historyType[0] = romType;
}

void verifyFileHistory(char* history, RomType* historyType) {
    int i, j;

    for (i = 0; i < MAX_HISTORY; i++) {
        char *fname = history + MAX_PATH * i;
        if (fname[0] != '\0' && 
            strcmp(fname, CARTNAME_SNATCHER)    && 
            strcmp(fname, CARTNAME_SDSNATCHER)  && 
            strcmp(fname, CARTNAME_SCCMIRRORED) && 
            strcmp(fname, CARTNAME_SCCEXPANDED) && 
            strcmp(fname, CARTNAME_SCC)         && 
            strcmp(fname, CARTNAME_SCCPLUS)     && 
            strcmp(fname, CARTNAME_FMPAC)       && 
            strcmp(fname, CARTNAME_PAC)         && 
            strcmp(fname, CARTNAME_SONYHBI55)   && 
            strcmp(fname, CARTNAME_EXTRAM512KB) && 
            strcmp(fname, CARTNAME_EXTRAM1MB)   &&
            strcmp(fname, CARTNAME_EXTRAM2MB)   &&
            strcmp(fname, CARTNAME_EXTRAM4MB)   &&
            strcmp(fname, CARTNAME_MEGARAM128)  && 
            strcmp(fname, CARTNAME_MEGARAM256)  && 
            strcmp(fname, CARTNAME_MEGARAM512)  && 
            strcmp(fname, CARTNAME_MEGARAM768)  && 
            strcmp(fname, CARTNAME_MEGARAM2M)) 
        {
            struct stat s;
            int rv = stat(fname, &s);
            if (rv == 0 && (s.st_mode & S_IFDIR)) {
            }
            else {
                FILE* file = fopen(fname, "r");
                if (file != NULL) {
                    fclose(file);
                }
                else {
                    if (i == MAX_HISTORY - 1) {
                        *(history + MAX_PATH * i) = 0;
                    }
                    else {
                        for (j = i + 1; j < MAX_HISTORY; j++) {
                            strcpy(history + MAX_PATH * (j - 1), history + MAX_PATH * j);
                            if (historyType) historyType[j - 1] = historyType[j];
                            *(history + MAX_PATH * j) = 0;
                        }
                        i--;
                    }
                }
            }
        }
    }
}

int fileExist(char* fileName, char* zipFile) {
    if (fileName == NULL || *fileName == 0) {
        return 0;
    }

    if (zipFile == NULL || *zipFile == 0) {
        FILE* file = fopen(fileName, "r");
        if (file != NULL) {
            fclose(file);
            return 1;
        }
        return 0;
    }
    else {
        int size;
        char* buf = zipLoadFile(zipFile, fileName, &size);
        if (buf != NULL) {
            free(buf);
            return 1;
        }
        return 0;
    }

    return 0;
}

char* fileGetNext(char* filename, char* zipFile) {
    static char name[512];
    static int pos = -1;
    int c;
    int j;

    strcpy(name, filename);

    pos = strlen(name) - 5;

    if (pos < 0) {
        return name;
    }

    while (pos >= 0) {
        c = name[pos];
    
        if (c >= '0' && c <= '9') {
            if (c < '9') {
                name[pos] = c + 1;
                if (fileExist(name, zipFile)) {
                    return name;
                }
            }

            for (j = 0; j < c; j++) {
                name[pos] = j;
                if (fileExist(name, zipFile)) {
                    return name;
                }
            }
            name[pos] = c;
        }
        pos--;
    }

    pos = strlen(name) - 5;
    c = name[pos];

    if (c >= 'A' && c <= 'Z') {
        if (c < 'Z') {
            name[pos] = c + 1;
            if (fileExist(name, zipFile)) {
                pos = -1;
                return name;
            }
        }

        for (j = 'A'; j <= c; j++) {
            name[pos] = j;
            if (fileExist(name, zipFile)) {
                pos = -1;
                return name;
            }
        }
    }

    if (c >= 'a' && c <= 'z') {
        if (c < 'z') {
            name[pos] = c + 1;
            if (fileExist(name, zipFile)) {
                pos = -1;
                return name;
            }
        }

        for (j = 'a'; j <= c; j++) {
            name[pos] = j;
            if (fileExist(name, zipFile)) {
                pos = -1;
                return name;
            }
        }
    }

    return name;
}

void updateExtendedRomName(int drive, char* filename, char* zipFile) {
    int size;
    char* buf = romLoad(filename, zipFile[0] ? zipFile : NULL, &size);

    if (buf != NULL) {
        romMapperGuessRom(buf, size, 1, extendedName[drive]);
        free(buf);
        if (extendedName[drive][0] == 0) {
            strcpy(extendedName[drive], stripPathExt(zipFile[0] ? zipFile : filename));
        }
    }
}

void updateExtendedDiskName(int drive, char* filename, char* zipFile) {
    int size;
    char* buf = romLoad(filename, zipFile[0] ? zipFile : NULL, &size);

    extendedDiskName[drive][0] = 0;
    if (buf != NULL) {
        romMapperGetDiskInfo(buf, size, extendedDiskName[drive]);
        free(buf);
        if (extendedDiskName[drive][0] == 0) {
            strcpy(extendedDiskName[drive], stripPathExt(zipFile[0] ? zipFile : filename));
        }
    }
}

void updateExtendedCasName(char* filename, char* zipFile) {
    int size;
    char* buf = romLoad(filename, zipFile[0] ? zipFile : NULL, &size);

    extendedCasName[0] = 0;
    if (buf != NULL) {
        romMapperGetCasInfo(buf, size, extendedCasName);
        free(buf);
        if (extendedCasName[0] == 0) {
            strcpy(extendedCasName, stripPathExt(zipFile[0] ? zipFile : filename));
        }
    }
}

void setExtendedRomName(int drive, char* name) {
    strcpy(extendedName[drive], name);
}

char* createSaveFileBaseName(Properties* properties, int useExtendedName)
{
    static char fileBase[128] = { 0 };
    int done = 0;

    if (*properties->cartridge.slotA) {
        if (useExtendedName && extendedName[0][0]) {
            strcpy(fileBase, extendedName[0]);
        }
        else if (*properties->cartridge.slotAZip) {
            strcpy(fileBase, stripPathExt(properties->cartridge.slotAZip));
        }
        else {
            strcpy(fileBase, stripPathExt(properties->cartridge.slotA));
        }

        if (strcmp(properties->cartridge.slotA, CARTNAME_SNATCHER)     &&
            strcmp(properties->cartridge.slotA, CARTNAME_SDSNATCHER)   &&
            strcmp(properties->cartridge.slotA, CARTNAME_SCCMIRRORED)  &&
            strcmp(properties->cartridge.slotA, CARTNAME_SCCEXPANDED)  &&
            strcmp(properties->cartridge.slotA, CARTNAME_SCC)          &&
            strcmp(properties->cartridge.slotA, CARTNAME_SCCPLUS)      &&
            strcmp(properties->cartridge.slotA, CARTNAME_FMPAC)        &&
            strcmp(properties->cartridge.slotA, CARTNAME_PAC)          &&
            strcmp(properties->cartridge.slotA, CARTNAME_EXTRAM512KB)  &&
            strcmp(properties->cartridge.slotA, CARTNAME_EXTRAM1MB)    &&
            strcmp(properties->cartridge.slotA, CARTNAME_EXTRAM2MB)    &&
            strcmp(properties->cartridge.slotA, CARTNAME_EXTRAM4MB)    &&
            strcmp(properties->cartridge.slotA, CARTNAME_MEGARAM128)   &&
            strcmp(properties->cartridge.slotA, CARTNAME_MEGARAM256)   &&
            strcmp(properties->cartridge.slotA, CARTNAME_MEGARAM512)   &&
            strcmp(properties->cartridge.slotA, CARTNAME_MEGARAM768)   &&
            strcmp(properties->cartridge.slotA, CARTNAME_MEGARAM2M)    &&
            properties->cartridge.slotAType != ROM_FMPAC               &&
            properties->cartridge.slotAType != ROM_PAC                 &&
            properties->cartridge.slotAType != ROM_MSXAUDIO            &&
            properties->cartridge.slotAType != ROM_MOONSOUND           &&
            properties->cartridge.slotAType != ROM_SNATCHER            &&
            properties->cartridge.slotAType != ROM_SDSNATCHER          &&
            properties->cartridge.slotAType != ROM_SCCMIRRORED         &&
            properties->cartridge.slotAType != ROM_SCC                 &&
            properties->cartridge.slotAType != ROM_SCCPLUS             &&
            properties->cartridge.slotAType != ROM_SONYHBI55)
        {
            done = 1;
        }
    }

    if (!done && *properties->cartridge.slotB) {
        if (useExtendedName && extendedName[1][0]) {
            strcpy(fileBase, extendedName[1]);
        }
        else if (*properties->cartridge.slotBZip) {
            strcpy(fileBase, stripPathExt(properties->cartridge.slotBZip));
        }
        else {
            strcpy(fileBase, stripPathExt(properties->cartridge.slotB));
        }

        if (strcmp(properties->cartridge.slotB, CARTNAME_SNATCHER)     &&
            strcmp(properties->cartridge.slotB, CARTNAME_SDSNATCHER)   &&
            strcmp(properties->cartridge.slotB, CARTNAME_SCCMIRRORED)  &&
            strcmp(properties->cartridge.slotB, CARTNAME_SCCEXPANDED)  &&
            strcmp(properties->cartridge.slotB, CARTNAME_SCC)          &&
            strcmp(properties->cartridge.slotB, CARTNAME_SCCPLUS)      &&
            strcmp(properties->cartridge.slotB, CARTNAME_FMPAC)        &&
            strcmp(properties->cartridge.slotB, CARTNAME_PAC)          &&
            strcmp(properties->cartridge.slotB, CARTNAME_SONYHBI55)    &&
            strcmp(properties->cartridge.slotB, CARTNAME_EXTRAM512KB)  &&
            strcmp(properties->cartridge.slotB, CARTNAME_EXTRAM1MB)    &&
            strcmp(properties->cartridge.slotB, CARTNAME_EXTRAM2MB)    &&
            strcmp(properties->cartridge.slotB, CARTNAME_EXTRAM4MB)    &&
            strcmp(properties->cartridge.slotB, CARTNAME_MEGARAM128)   &&
            strcmp(properties->cartridge.slotB, CARTNAME_MEGARAM256)   &&
            strcmp(properties->cartridge.slotB, CARTNAME_MEGARAM512)   &&
            strcmp(properties->cartridge.slotB, CARTNAME_MEGARAM768)   &&
            strcmp(properties->cartridge.slotB, CARTNAME_MEGARAM2M)    &&
            properties->cartridge.slotBType != ROM_FMPAC               &&
            properties->cartridge.slotBType != ROM_PAC                 &&
            properties->cartridge.slotBType != ROM_MSXAUDIO            &&
            properties->cartridge.slotBType != ROM_MOONSOUND           &&
            properties->cartridge.slotBType != ROM_SNATCHER            &&
            properties->cartridge.slotBType != ROM_SDSNATCHER          &&
            properties->cartridge.slotBType != ROM_SCCMIRRORED         &&
            properties->cartridge.slotBType != ROM_SCC                 &&
            properties->cartridge.slotBType != ROM_SCCPLUS             &&
            properties->cartridge.slotBType != ROM_SONYHBI55) 
        {
            done = 1;
        }
    }
    
    if (!done && *properties->diskdrive.slotA) {
        if (useExtendedName && extendedDiskName[0][0]) {
            strcpy(fileBase, extendedDiskName[0]);
        }
        else if (*properties->diskdrive.slotAZip) {
            strcpy(fileBase, stripPathExt(properties->diskdrive.slotAZip));
        }
        else {
            strcpy(fileBase, stripPathExt(properties->diskdrive.slotA));
        }
        done = 1;
    }
    
    if (!done && *properties->diskdrive.slotB) {
        if (useExtendedName && extendedDiskName[1][0]) {
            strcpy(fileBase, extendedDiskName[1]);
        }
        else if (*properties->diskdrive.slotBZip) {
            strcpy(fileBase, stripPathExt(properties->diskdrive.slotBZip));
        }
        else {
            strcpy(fileBase, stripPathExt(properties->diskdrive.slotB));
        }
        done = 1;
    }
    
    if (!done && *properties->cassette.tape) {
        if (useExtendedName && extendedCasName[0]) {
            strcpy(fileBase, extendedCasName);
        }
        else if (*properties->cassette.tapeZip) {
            strcpy(fileBase, stripPathExt(properties->cassette.tapeZip));
        }
        else {
            strcpy(fileBase, stripPathExt(properties->cassette.tape));
        }
        done = 1;
    }

    if (fileBase[0] == 0) {
        strcpy(fileBase, "unknown");
    }

    return fileBase;
}



char* generateSaveFilename(Properties* properties, char* directory, char* prefix, char* extension, int digits)
{
	WIN32_FIND_DATA fileData;
    FILETIME writeTime;
    HANDLE hFile;
	char lastfile[512];
    static char filename[512];
    char baseName[128];
    int fileIndex = 0;
    int extensionLen = strlen(extension);
    int i;
    int numMod = 1;
    char filenameFormat[32] = "%s\\%s%s_";
    char destfileFormat[32];

    for (i = 0; i < digits; i++) {
        strcat(filenameFormat, "?");
        numMod *= 10;
    }
    strcat(filenameFormat, "%s");
    sprintf(destfileFormat, "%%s\\%%s%%s_%%0%di%%s", digits);
    
    strcpy(baseName, createSaveFileBaseName(properties, 0));

	mkdir(directory);

    sprintf(filename, filenameFormat, directory, prefix, baseName, extension);

    hFile = FindFirstFile(filename,&fileData);
    if (hFile != INVALID_HANDLE_VALUE) {
        int filenameLen;

        writeTime = fileData.ftLastWriteTime;
		strcpy(lastfile, fileData.cFileName);

	    while (FindNextFile(hFile, &fileData ) != 0) {
            if (CompareFileTime(&fileData.ftLastWriteTime, &writeTime) < 0) {
                break;
            }
            writeTime = fileData.ftLastWriteTime;
            strcpy(lastfile, fileData.cFileName);
		}

        filenameLen = strlen(lastfile);

        if (filenameLen > extensionLen + digits) {
            lastfile[filenameLen - extensionLen] = 0;
            fileIndex = (atoi(&lastfile[filenameLen - extensionLen - digits]) + 1) % numMod;
        }
    }

    FindClose(hFile);

    sprintf(filename, destfileFormat, directory, prefix, baseName, fileIndex, extension);

    return filename;
}
