/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/Casette.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2004-12-21 21:35:03 $
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
#include "Casette.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "SaveState.h"
#include <io.h>
#include "ziphelper.h"


static UInt8 hdrSVICAS[17] = { 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x7F};
static UInt8 hdrFMSX98[17] = { 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x48, 0x65, 0x61, 0x64, 0x65, 0x72, 0x5f };
static UInt8 hdrFMSXDOS[8] = { 0x1f,0xa6,0xde,0xba,0xcc,0x13,0x7d,0x74 };
static UInt8 hdrASCII[10]  = { 0xea,0xea,0xea,0xea,0xea,0xea,0xea,0xea,0xea,0xea };
static UInt8 hdrBINARY[10] = { 0xd0,0xd0,0xd0,0xd0,0xd0,0xd0,0xd0,0xd0,0xd0,0xd0 };
static UInt8 hdrBASIC[10]  = { 0xd3,0xd3,0xd3,0xd3,0xd3,0xd3,0xd3,0xd3,0xd3,0xd3 };
static char   tapeBaseDir[512];
static char   tapePosName[512];
static char   tapeName[512];
static int    tapeRdWr;
static TapeFormat tapeFormat;
static UInt8* tapeHeader;
static int    tapeHeaderSize;
static char*  ramImageBuffer = NULL;
static int    ramImageSize = 0;
static int    ramImagePos = 0;
static int    casBusy;
static int    autoRewind = 0;

static char* stripPath(char* filename) {
    char* ptr = filename + strlen(filename) - 1;

    while (--ptr >= filename) {
        if (*ptr == '/' || *ptr == '\\') {
            return ptr + 1;
        }
    }

    return filename;
}

static int ramread(void* buf, int size, int* ramPos) {
    if (*ramPos > ramImageSize) {
        return 0;
    }
    if (*ramPos + size > ramImageSize) {
        size = ramImageSize - *ramPos;
    }

    memcpy(buf, ramImageBuffer + *ramPos, size);
    *ramPos += size;

    return size;
}

void tapeLoadState() {
    SaveState* state = saveStateOpenForRead("tape");

    ramImagePos = saveStateGet(state, "ramImagePos",  0);

    if (ramImagePos >= ramImageSize) {
        ramImagePos = 0;
    }
    saveStateClose(state);
}

void tapeSaveState() {
    SaveState* state = saveStateOpenForWrite("tape");

    saveStateSet(state, "ramImagePos",  ramImagePos);

    saveStateClose(state);
}

UInt8 tapeRead(UInt8* value) 
{
    if (ramImageBuffer != NULL) {
        if (autoRewind && ramImagePos == ramImageSize) {
            ramImagePos = 0;
        }

        if (ramImagePos < ramImageSize) {
            *value = ramImageBuffer[ramImagePos++];
            casBusy = 1;
            return 1;
        }
        return 0;
    }

    return 0;
}

UInt8 tapeWrite(UInt8 value) 
{
    if (ramImageBuffer != NULL) {
        if (ramImagePos >= ramImageSize) {
            char* newBuf = realloc(ramImageBuffer, ramImageSize + 1024);
            if (newBuf) {
                ramImageBuffer = newBuf;
                memset(ramImageBuffer + ramImageSize, 0, 1024);
                ramImageSize += 1024;
            }
        }

        if (ramImagePos < ramImageSize) {
            ramImageBuffer[ramImagePos++] = value;
            casBusy = 1;
            return 1;
        }
        return 0;
    }

    return 0;
}

UInt8 tapeReadHeader() 
{    
    if (ramImageBuffer != NULL) {
        UInt8 buf[32];
        int i;
        for (i = 0; i < tapeHeaderSize; i++) {
            if (!tapeRead(buf + i)) {
                return 0;
            }
        }
        
        while (memcmp(buf, tapeHeader, tapeHeaderSize)) {
            memmove(buf, buf + 1, tapeHeaderSize - 1);
            if (!tapeRead(buf + tapeHeaderSize - 1)) {
                return 0;
            }
        }
        return 1;
    }

    return 0;
}

UInt8 tapeWriteHeader() 
{
    if (ramImageBuffer != NULL) {
        int i;
        
        for (i = 0; i < tapeHeaderSize; i++) {
            if (!tapeWrite(tapeHeader[i])) {
                return 0;
            }
        }
        return 1;
    }

    return 0;
}

void tapeSetDirectory(char* baseDir, char* prefix) {
    strcpy(tapeBaseDir, baseDir);
}

void tapeSetReadOnly(int readOnly)
{
    tapeRdWr = !readOnly;
}

int tapeInsert(char *name, const char *fileInZipFile) 
{
    FILE* file;

    if (ramImageBuffer != NULL) {
        file = fopen(tapePosName, "w");
        if (file != NULL) {
            char buffer[32];
            sprintf(buffer, "POS:%d", ramImagePos);
            fwrite(buffer, 1, 32, file);
            fclose(file);
        }

        if (*tapeName && tapeRdWr) {
            tapeSave(tapeName, tapeFormat);
        }

        free(ramImageBuffer);
        ramImageBuffer = NULL;
    }

    *tapeName = 0;

    if(!name) {
        return 1;
    }

    // Create filename for tape position file
    sprintf(tapePosName, "%s\\%s", tapeBaseDir, stripPath(name));
    if (fileInZipFile == NULL) {
        strcpy(tapeName, name);
    }
    else {
        strcat(tapePosName, stripPath((char*)fileInZipFile));
    }
    strcat(tapePosName, ".pos");

    ramImagePos = 0;

    // Load and verify tape position
    file = fopen(tapePosName, "rb");
    if (file != NULL) {
        char buffer[32] = { 0 };
        fread(buffer, 1, 31, file);
        sscanf(buffer, "POS:%d", &ramImagePos);
        fclose(file);
    }

    if (fileInZipFile != NULL) {
        ramImageBuffer = zipLoadFile(name, fileInZipFile, &ramImageSize);
        if (ramImagePos > ramImageSize) {
            ramImagePos = ramImageSize;
        }
    }
    else {
        file = fopen(name,"rb");
        if (file != NULL) {
            // Load file into RAM buffer
            fseek(file, 0, SEEK_END);
            ramImageSize = ftell(file);
            fseek(file, 0, SEEK_SET);
            ramImageBuffer = malloc(ramImageSize);
            if (ramImageBuffer != NULL) {
                if (ramImageSize != fread(ramImageBuffer, 1, ramImageSize, file)) {
                    free(ramImageBuffer);
                    ramImageBuffer = NULL;
                }
            }
            fclose(file);
        }
    }

    if (ramImageBuffer != NULL) {
        UInt8* ptr = ramImageBuffer + ramImageSize - 17;
        int cntFMSXDOS = 0;
        int cntFMSX98  = 0;
        int cntSVICAS  = 0;

        while (ptr >= ramImageBuffer) {
            if (!memcmp(ptr, hdrFMSXDOS, sizeof(hdrFMSXDOS))) {
                cntFMSXDOS++;
            }
            if (!memcmp(ptr, hdrFMSX98, sizeof(hdrFMSX98))) {
                cntFMSX98++;
            }
            if (!memcmp(ptr, hdrSVICAS, sizeof(hdrSVICAS))) {
                cntSVICAS++;
            }
            ptr--;
        }

        if (cntSVICAS > cntFMSXDOS && cntSVICAS > cntFMSX98) {
            tapeFormat     = TAPE_SVICAS;
            tapeHeader     = hdrSVICAS;
            tapeHeaderSize = sizeof(hdrSVICAS);
        }
        else if (cntFMSXDOS >= cntFMSX98) {
            tapeFormat     = TAPE_FMSXDOS;
            tapeHeader     = hdrFMSXDOS;
            tapeHeaderSize = sizeof(hdrFMSXDOS);
        }
        else {
            tapeFormat     = TAPE_FMSX98AT;
            tapeHeader     = hdrFMSX98;
            tapeHeaderSize = sizeof(hdrFMSX98);
        }
    }

    if (ramImagePos > ramImageSize) {
        ramImagePos = ramImageSize;
    }

    return ramImageBuffer != NULL;
}

int tapeSave(char *name, TapeFormat format)
{
    FILE* file;
    int offset   = 0;
    int writePos = 0;
    UInt8* hdrData;
    int    hdrSize;

    if (ramImageBuffer == NULL) {
        return 0;
    }

    if (format != TAPE_FMSX98AT && format != TAPE_FMSXDOS && format != TAPE_SVICAS) {
        return 0;
    }

    file = fopen(name, "wb");
    if (file == NULL) {
        return 0;
    }

    while (offset < ramImageSize) {
        if (ramImageSize - offset >= tapeHeaderSize && !memcmp(ramImageBuffer + offset, tapeHeader, tapeHeaderSize)) {
            switch (format) {
                case TAPE_FMSXDOS:
                    hdrData = hdrFMSXDOS;
                    hdrSize = sizeof(hdrFMSXDOS);
                    break;
                case TAPE_FMSX98AT:
                    hdrData = hdrFMSX98;
                    hdrSize = sizeof(hdrFMSX98);
                    break;
                case TAPE_SVICAS:
                    hdrData = hdrSVICAS;
                    hdrSize = sizeof(hdrSVICAS);
                    break;
            }

            if (format == TAPE_FMSXDOS) {
                while (writePos & 7) {
                    UInt8 zero = 0;
                    fwrite(&zero, 1, 1, file);
                    writePos ++;
                }
            }

            fwrite(hdrData, 1, hdrSize, file);
            writePos += hdrSize;
            offset += tapeHeaderSize;
        }
        else {
            fwrite(ramImageBuffer + offset, 1, 1, file);
            writePos++;
            offset++;
        }
    }

    fclose(file);

    return 1;
}

TapeFormat tapeGetFormat()
{
    return tapeFormat;
}

UInt32 tapeGetLength()
{
    return ramImageSize;
}

TapeContent* tapeGetContent(int* count)
{
    static TapeContent tapeContent[1024];
    int  index = 0;
    char buffer[32];
    int  ramPos = 0;
    int  position = 0;
    int  skipNext = 0;

    memset(tapeContent, 0, sizeof(tapeContent));

    *count = 0;

    if (ramImageBuffer == NULL) {
        return tapeContent;
    }

    while (ramread(buffer, tapeHeaderSize, &ramPos) == tapeHeaderSize) {
        if (!memcmp(buffer, tapeHeader, tapeHeaderSize)) {
            if (skipNext) {
                skipNext = 0;
            }
            else if (ramread(buffer, 10, &ramPos) == 10) {
                if (!memcmp(buffer, hdrASCII, 10)) {
                    ramread(tapeContent[index].fileName, 6, &ramPos);
                    tapeContent[index].type = TAPE_ASCII;
                    tapeContent[index++].pos = ramPos - 16 - tapeHeaderSize;

                    while (ramPos < ramImageSize && ramImageBuffer[ramPos] != 0x1a) {
                        ramPos++;
                    }

                    position = ramPos - 1;
                } 
                else if (!memcmp(buffer, hdrBINARY, 10)) {
                    ramread(tapeContent[index].fileName, 6, &ramPos); 
                    tapeContent[index].type = TAPE_BINARY;
                    tapeContent[index++].pos = ramPos - 16 - tapeHeaderSize;
                    skipNext = 1;
                }
                else if (!memcmp(buffer, hdrBASIC, 10)) {
                    ramread(tapeContent[index].fileName, 6, &ramPos); 
                    tapeContent[index].type = TAPE_BASIC;
                    tapeContent[index++].pos = ramPos - 16 - tapeHeaderSize;
                    skipNext = 1;
                }
                else {
                    strcpy(tapeContent[index].fileName, "");
                    tapeContent[index].type = TAPE_CUSTOM;
                    tapeContent[index++].pos = ramPos - 10 - tapeHeaderSize;
                }
            }
        }
        ramPos = ++position;
    }

    *count = index;

    return tapeContent;
}

UInt32 tapeGetCurrentPos()
{
    return ramImagePos;
}

void tapeSetCurrentPos(int pos)
{
    if (pos < ramImageSize) {
        ramImagePos = pos;
    }
}

int tapeIsBusy()
{
    return casBusy;
}

void tapeSetBusy(int busy)
{
    casBusy = busy;
}
