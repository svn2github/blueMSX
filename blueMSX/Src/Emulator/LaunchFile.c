/*****************************************************************************
** File:        LaunchFile.c
**
** Author:      Daniel Vik
**
** Description: Methods to insert disks/roms/cassettes
**
** More info:   www.bluemsx.com
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
#include "LaunchFile.h"
#include "IsFileExtension.h"
#include "ziphelper.h"
#include "RomLoader.h"
#include "FileHistory.h"
#include "Emulator.h"
#include "Board.h"
#include <stdio.h>

#include "ArchDialog.h"

void archUpdateMenu(int show);

int insertCartridge(Properties* properties, int drive, char* fname, char* inZipFile, RomType romType, int forceAutostart) {
    int autostart = forceAutostart == 1 || properties->cartridge.autoReset;
    int noautostart = forceAutostart == -1;
    char romName[512] = "";
    char filename[512] = "";
    int isZip = isFileExtension(fname, ".zip");

    if (fname) strcpy(filename, fname);
    
    emulatorResetMixer();

    if (isZip) {
        if (inZipFile != NULL) {
            strcpy(romName, inZipFile);
        }
        else {
            // This is really ugly and should be done nicer...
            // The idea is to get files of three types and merge them into
            // one list. Maybe it should be done in zipGetFileList?
            int i;
            char* fileList;
            int countRom;
            int countMx1;
            int countMx2;
            char* fileListRom = zipGetFileList(filename, ".rom", &countRom);
            char* fileListMx1 = zipGetFileList(filename, ".mx1", &countMx1);
            char* fileListMx2 = zipGetFileList(filename, ".mx2", &countMx2);
            int count = countRom + countMx1 + countMx2;
            int sizeRom = 0;
            int sizeMx1 = 0;
            int sizeMx2 = 0;

            for (i = 0; i < countRom; i++) {
                sizeRom += strlen(fileListRom + sizeRom) + 1;
            }
            for (i = 0; i < countMx1; i++) {
                sizeMx1 += strlen(fileListMx1 + sizeMx1) + 1;
            }
            for (i = 0; i < countMx2; i++) {
                sizeMx2 += strlen(fileListMx2 + sizeMx2) + 1;
            }

            fileList = malloc(sizeRom + sizeMx1 + sizeMx2);
            memcpy(fileList, fileListRom, sizeRom);
            memcpy(fileList + sizeRom, fileListMx1, sizeMx1);
            memcpy(fileList + sizeRom + sizeMx1, fileListMx2, sizeMx2);

            if (count == 0) {
                MessageBox(NULL, langErrorNoRomInZip(), langErrorTitle(), MB_OK);
                return 0;
            }

            if (count == 1) {
                strcpy(romName, fileList);
            }
            else {
                ZipFileDlgInfo dlgInfo;

                _stprintf(dlgInfo.title, "%s", langDlgLoadRom());
                _stprintf(dlgInfo.description, "%s", langDlgLoadRomDesc());
                strcpy(dlgInfo.zipFileName, fname);
                dlgInfo.fileList = fileList;
                dlgInfo.fileListCount = count;
                dlgInfo.autoReset = autostart;

                dlgInfo.selectFileIndex = -1;
                strcpy(dlgInfo.selectFile, drive == 0 ? properties->cartridge.slotAZip : properties->cartridge.slotBZip);

                archFileFromZipDialog(&dlgInfo);

                romType = dlgInfo.openRomType;

                if (dlgInfo.selectFile[0] == '\0') {
                    free(fileList);
                    return 0;
                }
                autostart = dlgInfo.autoReset;
                strcpy(romName, dlgInfo.selectFile);
            }

            if(fileListRom) free(fileListRom);
            if(fileListMx1) free(fileListMx1);
            if(fileListMx2) free(fileListMx2);
            free(fileList);
        }
    }
    {
        int size;
        char* buf = romLoad(filename, isZip ? romName : NULL, &size);
        char prettyRomName[256];

        if (buf != NULL) {
            RomType chkRomType = romMapperGuessRom(buf, size, 1, prettyRomName);
            free(buf);
            
            if (prettyRomName[0] != 0) {
                setExtendedRomName(drive, prettyRomName);
            }
            else {
                setExtendedRomName(drive, stripPathExt(isZip ? romName : filename));
            }

            if (romType == ROM_UNKNOWN) {
                romType = chkRomType;
            }
        }
    }

    romType = 0 == strcmp(CARTNAME_SNATCHER,    filename) ? ROM_SNATCHER :
              0 == strcmp(CARTNAME_SDSNATCHER,  filename) ? ROM_SDSNATCHER :
              0 == strcmp(CARTNAME_SCCMIRRORED, filename) ? ROM_SCCMIRRORED :
              0 == strcmp(CARTNAME_SCCEXPANDED, filename) ? ROM_SCCEXTENDED :
              0 == strcmp(CARTNAME_SCC,         filename) ? ROM_SCC :
              0 == strcmp(CARTNAME_SCCPLUS,     filename) ? ROM_SCCPLUS :
              0 == strcmp(CARTNAME_FMPAC,       filename) ? ROM_FMPAC :
              0 == strcmp(CARTNAME_PAC,         filename) ? ROM_PAC :
              0 == strcmp(CARTNAME_EXTRAM512KB, filename) ? ROM_EXTRAM512KB :
              0 == strcmp(CARTNAME_EXTRAM1MB,   filename) ? ROM_EXTRAM1MB :
              0 == strcmp(CARTNAME_EXTRAM2MB,   filename) ? ROM_EXTRAM2MB :
              0 == strcmp(CARTNAME_EXTRAM4MB,   filename) ? ROM_EXTRAM4MB :
              0 == strcmp(CARTNAME_MEGARAM128,  filename) ? ROM_MEGARAM128 :
              0 == strcmp(CARTNAME_MEGARAM256,  filename) ? ROM_MEGARAM256 :
              0 == strcmp(CARTNAME_MEGARAM512,  filename) ? ROM_MEGARAM512 :
              0 == strcmp(CARTNAME_MEGARAM768,  filename) ? ROM_MEGARAM768 :
              0 == strcmp(CARTNAME_MEGARAM2M,   filename) ? ROM_MEGARAM2M  :
              romType;

    if (drive == 0) {
        strcpy(properties->cartridge.slotA, filename);
        strcpy(properties->cartridge.slotAZip, romName);
        properties->cartridge.slotAType = romType;
        updateFileHistory(*properties->filehistory.cartridgeA, 
                          properties->filehistory.cartridgeTypeA, 
                          filename, romType);
    }
    else {
        strcpy(properties->cartridge.slotB, filename);
        strcpy(properties->cartridge.slotBZip, romName);
        properties->cartridge.slotBType = romType;
        updateFileHistory(*properties->filehistory.cartridgeB, 
                          properties->filehistory.cartridgeTypeB, 
                          filename, romType);
    }

    if (autostart && !noautostart) {
        emulatorStop();
        emulatorStart(NULL);
    }
    else if (emulatorGetState() != EMU_STOPPED) {
        emulatorSuspend();
        boardChangeCartridge(drive, romType, filename, isZip ? romName : NULL);
        emulatorResume();
    }

    return 1;
}

int insertDiskette(Properties* properties, int drive, char* fname, char* inZipFile, int forceAutostart) {
    char diskName[512] = "";
    char filename[512] = "";
    int autostart = forceAutostart == 1 || (drive == 0 ? properties->diskdrive.autostartA : 0);
    int noautostart = forceAutostart == -1;
    int isZip = isFileExtension(fname, ".zip");

    if (fname) strcpy(filename, fname);

    emulatorResetMixer();

    if (isZip) {
        if (inZipFile != NULL) {
            strcpy(diskName, inZipFile);
        }
        else {
            // This is really ugly and should be done nicer...
            // The idea is to get files of three types and merge them into
            // one list. Maybe it should be done in zipGetFileList?
            int i;
            char* fileList;
            int countDsk;
            int countDi1;
            int countDi2;
            char* fileListDsk = zipGetFileList(filename, ".dsk", &countDsk);
            char* fileListDi1 = zipGetFileList(filename, ".di1", &countDi1);
            char* fileListDi2 = zipGetFileList(filename, ".di2", &countDi2);
            int count = countDsk + countDi1 + countDi2;
            int sizeDsk = 0;
            int sizeDi1 = 0;
            int sizeDi2 = 0;

            for (i = 0; i < countDsk; i++) {
                sizeDsk += strlen(fileListDsk + sizeDsk) + 1;
            }
            for (i = 0; i < countDi1; i++) {
                sizeDi1 += strlen(fileListDi1 + sizeDi1) + 1;
            }
            for (i = 0; i < countDi2; i++) {
                sizeDi2 += strlen(fileListDi2 + sizeDi2) + 1;
            }

            fileList = malloc(sizeDsk + sizeDi1 + sizeDi2);
            memcpy(fileList, fileListDsk, sizeDsk);
            memcpy(fileList + sizeDsk, fileListDi1, sizeDi1);
            memcpy(fileList + sizeDsk + sizeDi1, fileListDi2, sizeDi2);

            if (count == 0) {
                MessageBox(NULL, langErrorNoDskInZip(), langErrorTitle(), MB_OK);
                return 0;
            }

            if (count == 1) {
                strcpy(diskName, fileList);
            }
            else {
                ZipFileDlgInfo dlgInfo;

                _stprintf(dlgInfo.title, "%s", langDlgLoadDsk());
                _stprintf(dlgInfo.description, "%s", langDlgLoadDskDesc());
                strcpy(dlgInfo.zipFileName, fname);
                dlgInfo.fileList = fileList;
                dlgInfo.fileListCount = count;
                dlgInfo.autoReset = autostart;

                dlgInfo.selectFileIndex = -1;
                strcpy(dlgInfo.selectFile, drive == 0 ? properties->diskdrive.slotAZip : properties->diskdrive.slotBZip);

                archFileFromZipDialog(&dlgInfo);

                if (dlgInfo.selectFile[0] == '\0') {
                    free(fileList);
                    return 0;
                }
                strcpy(diskName, dlgInfo.selectFile);
                autostart = dlgInfo.autoReset;
            }
            if(fileListDsk) free(fileListDsk);
            if(fileListDi1) free(fileListDi1);
            if(fileListDi2) free(fileListDi2);
            free(fileList);
        }
    }

    if (drive == 0) {
        strcpy(properties->diskdrive.slotA, filename);
        strcpy(properties->diskdrive.slotAZip, diskName);
        updateExtendedDiskName(0, properties->diskdrive.slotA, properties->diskdrive.slotAZip);
        updateFileHistory(*properties->filehistory.diskdriveA, NULL, filename, 0);
    }
    else {
        strcpy(properties->diskdrive.slotB, filename);
        strcpy(properties->diskdrive.slotBZip, diskName);
        updateExtendedDiskName(1, properties->diskdrive.slotB, properties->diskdrive.slotBZip);
        updateFileHistory(*properties->filehistory.diskdriveB, NULL, filename, 0);
    }

    if (autostart && !noautostart) {
        emulatorStop();
        emulatorStart(NULL);
    }
    else if (emulatorGetState() != EMU_STOPPED) {
        emulatorSuspend();
        boardChangeDiskette(drive, filename, isZip ? diskName : NULL);
        emulatorResume();
    }

    return 1;
}

int insertCassette(Properties* properties, char* fname, char* inZipFile, int forceAutostart) {
    int autostart = forceAutostart == 1;
    int noautostart = forceAutostart == -1;
    char tapeName[512] = "";
    char filename[512] = "";
    int isZip = isFileExtension(fname, ".zip");

    if (fname) strcpy(filename, fname);

    if (isZip) {
        if (inZipFile != NULL) {
            strcpy(tapeName, inZipFile);
        }
        else {
            int count;
            char* fileList = zipGetFileList(filename, ".cas", &count);

            if (fileList == NULL) {
                MessageBox(NULL, langErrorNoCasInZip(), langErrorTitle(), MB_OK);
                return 0;
            }

            if (count == 1) {
                strcpy(tapeName, fileList);
            }
            else {
                ZipFileDlgInfo dlgInfo;

                _stprintf(dlgInfo.title, "%s", langDlgLoadCas());
                _stprintf(dlgInfo.description, "%s", langDlgLoadCasDesc());
                strcpy(dlgInfo.zipFileName, fname);
                dlgInfo.fileList = fileList;
                dlgInfo.fileListCount = count;
                dlgInfo.autoReset = autostart;

                dlgInfo.selectFileIndex = -1;
                strcpy(dlgInfo.selectFile, properties->cassette.tapeZip);

                archFileFromZipDialog(&dlgInfo);

                autostart = dlgInfo.autoReset;
                if (dlgInfo.selectFile[0] == '\0') {
                    free(fileList);
                    return 0;
                }
                strcpy(tapeName, dlgInfo.selectFile);
            }
            free(fileList);
        }
    }

    strcpy(properties->cassette.tape, filename);
    strcpy(properties->cassette.tapeZip, tapeName);
    updateExtendedCasName(properties->cassette.tape, properties->cassette.tapeZip);
    updateFileHistory(*properties->filehistory.cassette, NULL, filename, 0);

    if (autostart && !noautostart) {
        emulatorStart(NULL);
    }
    else if (emulatorGetState() != EMU_STOPPED) {
        emulatorSuspend();
        boardChangeCassette(filename, isZip ? tapeName : NULL);
        emulatorResume();
    }

    return 1;
}

static int insertDisketteOrCartridge(Properties* properties, int drive, char* filename, int forceAutostart) {
    ZipFileDlgInfo dlgInfo;
    int countDsx;
    int countDi1;
    int countDi2;
    int countRox;
    int countMx1;
    int countMx2;
    int countCas;
    char* fileListDsk = NULL;
    char* fileListRom = NULL;
    char* fileListDsx = zipGetFileList(filename, ".dsk", &countDsx);
    char* fileListDi1 = zipGetFileList(filename, ".di1", &countDi1);
    char* fileListDi2 = zipGetFileList(filename, ".di2", &countDi2);
    char* fileListRox = zipGetFileList(filename, ".rom", &countRox);
    char* fileListMx1 = zipGetFileList(filename, ".mx1", &countMx1);
    char* fileListMx2 = zipGetFileList(filename, ".mx2", &countMx2);
    char* fileListCas = zipGetFileList(filename, ".cas", &countCas);
    int countRom = countRox + countMx1 + countMx2;
    int countDsk = countDsx + countDi1 + countDi2;
    char* fileList;
    int sizeDsk = 0;
    int sizeDsx = 0;
    int sizeDi1 = 0;
    int sizeDi2 = 0;
    int sizeRox = 0;
    int sizeRom = 0;
    int sizeMx1 = 0;
    int sizeMx2 = 0;
    int sizeCas = 0;
    int success = 0;
    int i;

    // First merge different dsk formats into one list
    for (i = 0; i < countDsx; i++) {
        sizeDsx += strlen(fileListDsx + sizeDsx) + 1;
    }
    for (i = 0; i < countDi1; i++) {
        sizeDi1 += strlen(fileListDi1 + sizeDi1) + 1;
    }
    for (i = 0; i < countDi2; i++) {
        sizeDi2 += strlen(fileListDi2 + sizeDi2) + 1;
    }

    if (countDsk > 0) {
        fileListDsk = malloc(sizeDsx + sizeDi1 + sizeDi2);
        memcpy(fileListDsk, fileListDsx, sizeDsx);
        memcpy(fileListDsk + sizeDsx, fileListDi1, sizeDi1);
        memcpy(fileListDsk + sizeDsx + sizeDi1, fileListDi2, sizeDi2);
    }

    // Then merge different dsk formats into one list
    for (i = 0; i < countRox; i++) {
        sizeRox += strlen(fileListRox + sizeRox) + 1;
    }
    for (i = 0; i < countMx1; i++) {
        sizeMx1 += strlen(fileListMx1 + sizeMx1) + 1;
    }
    for (i = 0; i < countMx2; i++) {
        sizeMx2 += strlen(fileListMx2 + sizeMx2) + 1;
    }

    if (countRom > 0) {
        fileListRom = malloc(sizeRox + sizeMx1 + sizeMx2);
        memcpy(fileListRom, fileListRox, sizeRox);
        memcpy(fileListRom + sizeRox, fileListMx1, sizeMx1);
        memcpy(fileListRom + sizeRox + sizeMx1, fileListMx2, sizeMx2);
    }

    // Finally check different types...
    if (fileListDsk == NULL && fileListRom == NULL && fileListCas == NULL) {
        return 0;
    }

    if (fileListDsk == NULL && fileListCas == NULL) {
        free(fileListRom);
        return insertCartridge(properties, drive, filename, NULL, ROM_UNKNOWN, 0);
    }

    if (fileListRom == NULL && fileListCas == NULL) {
        free(fileListDsk);
        return insertDiskette(properties, drive, filename, NULL, 0);
    }

    if (fileListRom == NULL && fileListDsk == NULL) {
        free(fileListCas);
        return insertCassette(properties, filename, NULL, 0);
    }

    for (i = 0; i < countRom; i++) {
        sizeRom += strlen(fileListRom + sizeRom) + 1;
    }

    for (i = 0; i < countDsk; i++) {
        sizeDsk += strlen(fileListDsk + sizeDsk) + 1;
    }

    for (i = 0; i < countCas; i++) {
        sizeCas += strlen(fileListCas + sizeCas) + 1;
    }

    fileList = malloc(sizeDsk + sizeRom + sizeCas);
    memcpy(fileList, fileListRom, sizeRom);
    memcpy(fileList + sizeRom, fileListDsk, sizeDsk);
    memcpy(fileList + sizeRom + sizeDsk, fileListCas, sizeCas);

    _stprintf(dlgInfo.title, "%s", langDlgLoadRomDskCas());
    _stprintf(dlgInfo.description, "%s", langDlgLoadRomDskCasDesc());
    strcpy(dlgInfo.zipFileName, filename);
    dlgInfo.fileList = fileList;
    dlgInfo.fileListCount = countDsk + countRom + countCas;
    dlgInfo.autoReset = properties->diskdrive.autostartA || properties->cartridge.autoReset || forceAutostart;
    dlgInfo.selectFileIndex = -1;
    dlgInfo.selectFile[0] = 0;

    archFileFromZipDialog(&dlgInfo);

    if (isFileExtension(dlgInfo.selectFile, ".rom") || isFileExtension(dlgInfo.selectFile, ".mx1") || isFileExtension(dlgInfo.selectFile, ".mx2")) {
        success = insertCartridge(properties, drive, filename, dlgInfo.selectFile, dlgInfo.openRomType, dlgInfo.autoReset);
    }
    else if (isFileExtension(dlgInfo.selectFile, ".dsk") || isFileExtension(dlgInfo.selectFile, ".di1") || isFileExtension(dlgInfo.selectFile, ".di2")) {
        success = insertDiskette(properties, drive, filename, dlgInfo.selectFile, dlgInfo.autoReset);
    }
    else if (isFileExtension(dlgInfo.selectFile, ".cas")) {
        success = insertCassette(properties, filename, dlgInfo.selectFile, dlgInfo.autoReset);
    }

    if(fileListDsk) free(fileListDsk);
    if(fileListDi1) free(fileListDi1);
    if(fileListDi2) free(fileListDi2);
    if(fileListRom) free(fileListRom);
    if(fileListMx1) free(fileListMx1);
    if(fileListMx2) free(fileListMx2);
    if(fileListCas) free(fileListCas);
    if(fileList) free(fileList);

    return success;
}

int tryLaunchUnknownFile(Properties* properties, char* fileName, int forceAutostart) 
{
    int rv = 0;

    if (isFileExtension(fileName, ".sta")) {
        emulatorStart(fileName);
        return 1;
    }

    if (isFileExtension(fileName, ".rom") || isFileExtension(fileName, ".mx1") || isFileExtension(fileName, ".mx2")) {
        rv = insertCartridge(properties, properties->cartridge.quickStartDrive, fileName, NULL, ROM_UNKNOWN, forceAutostart);
    }
    else if (isFileExtension(fileName, ".dsk") || isFileExtension(fileName, ".di1") || isFileExtension(fileName, ".di2")) {
        rv = insertDiskette(properties, properties->diskdrive.quickStartDrive, fileName, NULL, forceAutostart);
    }
    else if (isFileExtension(fileName, ".cas")) {
        rv = insertCassette(properties, fileName, NULL, forceAutostart);
    }
    else if (isFileExtension(fileName, ".zip")) {
        rv = insertDisketteOrCartridge(properties, properties->cartridge.quickStartDrive, fileName, forceAutostart);
    }
    
    archUpdateMenu(0);

    return rv;
}

