/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Emulator/CommandLine.c,v $
**
** $Revision: 1.10 $
**
** $Date: 2005-07-05 22:41:17 $
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
#include "CommandLine.h"
#include "TokenExtract.h"
#include "IsFileExtension.h"
#include "MediaDb.h"
#include "ziphelper.h"
#include "Machine.h"
#include "Casette.h"
#include "FileHistory.h"
#include "LaunchFile.h"
#include "Emulator.h"


static RomType romNameToType(char* name) {
    RomType romType = ROM_UNKNOWN;

    if (name == NULL) {
        return ROM_UNKNOWN;
    }

    romType = mediaDbOldStringToType(name);

    if (romType == ROM_UNKNOWN) {
        romType = atoi(name);
        if (romType < ROM_STANDARD || romType > ROM_MAXROMID) {
            romType = ROM_UNKNOWN;
        }
    }

    return romType;
}

static int isRomFileType(char* filename, char* inZip) {
    inZip[0] = 0;

    if (isFileExtension(filename, ".zip")) {
        int count;
        char* fileList;
        
        fileList = zipGetFileList(filename, ".rom", &count);
        if (fileList) {
            strcpy(inZip, fileList);
            free(fileList);
            return 1;
        }
        
        fileList = zipGetFileList(filename, ".ri", &count);
        if (fileList) {
            strcpy(inZip, fileList);
            free(fileList);
            return 1;
        }
        
        fileList = zipGetFileList(filename, ".mx1", &count);
        if (fileList) {
            strcpy(inZip, fileList);
            free(fileList);
            return 1;
        }
        
        fileList = zipGetFileList(filename, ".mx2", &count);
        if (fileList) {
            strcpy(inZip, fileList);
            free(fileList);
            return 1;
        }
        
        fileList = zipGetFileList(filename, ".col", &count);
        if (fileList) {
            strcpy(inZip, fileList);
            free(fileList);
            return 1;
        }

        return 0;
    }

    return isFileExtension(filename, ".rom") ||
           isFileExtension(filename, ".ri")  ||
           isFileExtension(filename, ".mx1") ||
           isFileExtension(filename, ".mx2") ||
           isFileExtension(filename, ".col");
}

static int isDskFileType(char* filename, char* inZip) {
    inZip[0] = 0;

    if (isFileExtension(filename, ".zip")) {
        int count;
        char* fileList;
        
        fileList = zipGetFileList(filename, ".dsk", &count);
        if (fileList) {
            strcpy(inZip, fileList);
            free(fileList);
            return 1;
        }
        
        fileList = zipGetFileList(filename, ".di1", &count);
        if (fileList) {
            strcpy(inZip, fileList);
            free(fileList);
            return 1;
        }
        
        fileList = zipGetFileList(filename, ".di2", &count);
        if (fileList) {
            strcpy(inZip, fileList);
            free(fileList);
            return 1;
        }
        
        fileList = zipGetFileList(filename, ".360", &count);
        if (fileList) {
            strcpy(inZip, fileList);
            free(fileList);
            return 1;
        }
        
        fileList = zipGetFileList(filename, ".720", &count);
        if (fileList) {
            strcpy(inZip, fileList);
            free(fileList);
            return 1;
        }

        return 0;
    }

    return isFileExtension(filename, ".dsk") ||
           isFileExtension(filename, ".di1") ||
           isFileExtension(filename, ".di2") ||
           isFileExtension(filename, ".360") ||
           isFileExtension(filename, ".720");
}

static int isCasFileType(char* filename, char* inZip) {
    inZip[0] = 0;

    if (isFileExtension(filename, ".zip")) {
        int count;
        char* fileList;
        
        fileList = zipGetFileList(filename, ".cas", &count);
        if (fileList) {
            strcpy(inZip, fileList);
            free(fileList);
            return 1;
        }
        return 0;
    }

    return isFileExtension(filename, ".cas");
}

int emuCheckResetArgument(char* cmdLine) {
    int i;
    char*   argument;
    
    for (i = 0; argument = extractToken(cmdLine, i); i++) {
        if (strcmp(argument, "/reset") == 0) {
            return 1;
        }
        if (strcmp(argument, "/resetregs") == 0) {
            return 2;
        }
    }

    return 0;
}

char* emuCheckIniFileArgument(char* cmdLine){
    static char iniFile[MAX_PATH];
    int i;
    char* argument;
    
    iniFile[0] = 0;

    for (i = 0; argument = extractToken(cmdLine, i); i++) {
        if (strcmp(argument, "/inifile") == 0) {
            argument = extractToken(cmdLine, i + 1);
            if (argument != NULL && argument[0] != '/') {
                strcat(iniFile, argument);
            }
            return iniFile;
        }
    }

    return NULL;
}

char* emuCheckThemeArgument(char* cmdLine){
    static char themeName[MAX_PATH];
    int i;
    char* argument;
    
    themeName[0] = 0;

    for (i = 0; argument = extractToken(cmdLine, i); i++) {
        if (strcmp(argument, "/theme") == 0) {
            argument = extractToken(cmdLine, i + 1);
            if (argument != NULL && argument[0] != '/') {
                strcat(themeName, argument);
            }
            return themeName;
        }
    }

    return NULL;
}

int emuCheckLanguageArgument(char* cmdLine, int defaultLang){
    int i;
    int lang;
    char* argument;
    
    for (i = 0; argument = extractToken(cmdLine, i); i++) {
        if (strcmp(argument, "/language") == 0) {
            argument = extractToken(cmdLine, ++i);
            if (argument == NULL) return defaultLang;
            lang = langFromName(argument);
            return lang == EMU_LANG_UNKNOWN ? defaultLang : lang;
        }
    }

    return defaultLang;
}

void emuCheckFullscreenArgument(Properties* properties, char* cmdLine){
    int i;
    char* argument;

    if (NULL == extractToken(cmdLine, 0)) {
        return;
    }

    properties->video.size = P_VIDEO_SIZEX2;

    for (i = 0; argument = extractToken(cmdLine, i); i++) {
        if (strcmp(argument, "/fullscreen") == 0) {
            properties->video.size = P_VIDEO_SIZEFULLSCREEN;
        }
    }
}

static int emuStartWithArguments(Properties* properties, char* commandLine) {
    int i;
    char    cmdLine[512] = "";
    char*   argument;
    char    rom1[512] = "";
    char    rom2[512] = "";
    char    rom1zip[256] = "";
    char    rom2zip[256] = "";
    RomType romType1  = ROM_UNKNOWN;
    RomType romType2  = ROM_UNKNOWN;
    char    machineName[64] = "";
    char    diskA[512] = "";
    char    diskB[512] = "";
    char    diskAzip[256] = "";
    char    diskBzip[256] = "";
    char    cas[512] = "";
    char    caszip[256] = "";
    int     fullscreen = 0;
    int     startEmu = 0;

    if (commandLine[0] != '/' && commandLine[1] == ':') {
        char* ptr;
        strcat(cmdLine, "\"");
        strcat(cmdLine, commandLine);
        ptr = cmdLine + strlen(commandLine);
        while (ptr > cmdLine && *ptr == ' ') {
            *ptr-- = '\0';
        }
        strcat(cmdLine, "\"");
    }
    else {
        strcat(cmdLine, commandLine);
    }

    // If one argument, assume it is a rom or disk to run
    if (!extractToken(cmdLine, 1)) {
        argument = extractToken(cmdLine, 0);
        
        if (*argument != '/') {
            if (*argument == '\"') argument++;

            if (*argument) {
                // Clear cartridge info
                properties->cartridge.slotA[0] = 0;
                properties->cartridge.slotAZip[0] = 0;
                properties->cartridge.slotB[0] = 0;
                properties->cartridge.slotBZip[0] = 0;
                properties->cartridge.slotAType = ROM_UNKNOWN;
                properties->cartridge.slotBType = ROM_UNKNOWN;
                updateExtendedRomName(0, properties->cartridge.slotA, properties->cartridge.slotAZip);
                updateExtendedRomName(1, properties->cartridge.slotB, properties->cartridge.slotBZip);

                properties->diskdrive.slotA[0] = 0;
                properties->diskdrive.slotAZip[0] = 0;
                properties->diskdrive.slotB[0] = 0;
                properties->diskdrive.slotBZip[0] = 0;
                updateExtendedDiskName(0, properties->diskdrive.slotA, properties->diskdrive.slotAZip);
                updateExtendedDiskName(1, properties->diskdrive.slotB, properties->diskdrive.slotBZip);
                updateExtendedCasName(properties->cassette.tape, properties->cassette.tapeZip);

                return tryLaunchUnknownFile(properties, argument, 1);
            }
            return 0;
        }
    }

    // If more than one argument, check arguments,
    // set configuration and then run

    for (i = 0; argument = extractToken(cmdLine, i); i++) {
        if (strcmp(argument, "/rom1") == 0) {
            argument = extractToken(cmdLine, ++i);
            if (argument == NULL || !isRomFileType(argument, rom1zip)) return 0; // Invaid argument
            strcpy(rom1, argument);
            startEmu = 1;
        }
        if (strcmp(argument, "/rom1zip") == 0) {
            argument = extractToken(cmdLine, ++i);
            if (argument == NULL) return 0;
            strcpy(rom1zip, argument);
        }
        if (strcmp(argument, "/romtype1") == 0) {
            argument = extractToken(cmdLine, ++i);
            if (argument == NULL) return 0; // Invaid argument
            romType1 = romNameToType(argument);
            startEmu = 1;
        }
        if (strcmp(argument, "/rom2") == 0) {
            argument = extractToken(cmdLine, ++i);
            if (argument == NULL || !isRomFileType(argument, rom2zip)) return 0; // Invaid argument
            strcpy(rom2, argument);
            startEmu = 1;
        }
        if (strcmp(argument, "/rom2zip") == 0) {
            argument = extractToken(cmdLine, ++i);
            if (argument == NULL) return 0;
            strcpy(rom2zip, argument);
        }
        if (strcmp(argument, "/romtype2") == 0) {
            argument = extractToken(cmdLine, ++i);
            if (argument == NULL) return 0; // Invaid argument
            romType2 = romNameToType(argument);
            startEmu = 1;
        }
        if (strcmp(argument, "/diskA") == 0) {
            argument = extractToken(cmdLine, ++i);
            if (argument == NULL || !isDskFileType(argument, diskAzip)) return 0; // Invaid argument
            strcpy(diskA, argument);
            startEmu = 1;
        }
        if (strcmp(argument, "/diskAzip") == 0) {
            argument = extractToken(cmdLine, ++i);
            if (argument == NULL) return 0;
            strcpy(diskAzip, argument);
        }
        if (strcmp(argument, "/diskB") == 0) {
            argument = extractToken(cmdLine, ++i);
            if (argument == NULL || !isDskFileType(argument, diskBzip)) return 0; // Invaid argument
            strcpy(diskB, argument);
            startEmu = 1;
        }
        if (strcmp(argument, "/diskBzip") == 0) {
            argument = extractToken(cmdLine, ++i);
            if (argument == NULL) return 0;
            strcpy(diskBzip, argument);
        }
        if (strcmp(argument, "/cas") == 0) {
            argument = extractToken(cmdLine, ++i);
            if (argument == NULL || !isCasFileType(argument, caszip)) return 0; // Invaid argument
            strcpy(cas, argument);
            startEmu = 1;
        }
        if (strcmp(argument, "/caszip") == 0) {
            argument = extractToken(cmdLine, ++i);
            if (argument == NULL) return 0;
            strcpy(caszip, argument);
        }
        if (strcmp(argument, "/family") == 0) {
            argument = extractToken(cmdLine, ++i);
            if (argument == NULL) return 0; // Invaid argument
            strcpy(machineName, argument); // FIXME verify arg
            if (!machineIsValid(machineName, 1)) return 0;
            startEmu = 1;
        }
        if (strcmp(argument, "/machine") == 0) {
            argument = extractToken(cmdLine, ++i);
            if (argument == NULL) return 0; // Invaid argument
            strcpy(machineName, argument);
            if (!machineIsValid(machineName, 1)) return 0;
            startEmu = 1;
        }
        if (strcmp(argument, "/fullscreen") == 0) {
            fullscreen = 1;
        }
    }

    if (!startEmu) {
        return 1;
    }

    properties->cartridge.slotA[0] = 0;
    properties->cartridge.slotAZip[0] = 0;
    properties->cartridge.slotB[0] = 0;
    properties->cartridge.slotBZip[0] = 0;
    properties->cartridge.slotAType = ROM_UNKNOWN;
    properties->cartridge.slotBType = ROM_UNKNOWN;
    updateExtendedRomName(0, properties->cartridge.slotA, properties->cartridge.slotAZip);
    updateExtendedRomName(1, properties->cartridge.slotB, properties->cartridge.slotBZip);

    properties->diskdrive.slotA[0] = 0;
    properties->diskdrive.slotAZip[0] = 0;
    properties->diskdrive.slotB[0] = 0;
    properties->diskdrive.slotBZip[0] = 0;
    updateExtendedDiskName(0, properties->diskdrive.slotA, properties->diskdrive.slotAZip);
    updateExtendedDiskName(1, properties->diskdrive.slotB, properties->diskdrive.slotBZip);
    updateExtendedCasName(properties->cassette.tape, properties->cassette.tapeZip);
    
    if (!strlen(rom1)) {
        switch (romType1) {
        case ROM_SCC:         strcat(rom1, CARTNAME_SCC); romType1 = ROM_SCC; break;
        case ROM_SCCPLUS:     strcat(rom1, CARTNAME_SCCPLUS); romType1 = ROM_SCCPLUS; break;
        case ROM_SNATCHER:    strcat(rom1, CARTNAME_SNATCHER); break;
        case ROM_SDSNATCHER:  strcat(rom1, CARTNAME_SDSNATCHER); break;
        case ROM_SCCMIRRORED: strcat(rom1, CARTNAME_SCCMIRRORED); break;
        case ROM_SCCEXTENDED: strcat(rom1, CARTNAME_SCCEXPANDED); break;
        case ROM_FMPAC:       strcat(rom1, CARTNAME_FMPAC); break;
        case ROM_PAC:         strcat(rom1, CARTNAME_PAC); break;
        case ROM_SONYHBI55:   strcat(rom1, CARTNAME_SONYHBI55); break;
        }
    }

    if (!strlen(rom2)) {
        switch (romType2) {
        case ROM_SCC:         strcat(rom2, CARTNAME_SCC); romType2 = ROM_SCC; break;
        case ROM_SCCPLUS:     strcat(rom2, CARTNAME_SCCPLUS); romType2 = ROM_SCCPLUS; break;
        case ROM_SNATCHER:    strcat(rom2, CARTNAME_SNATCHER); break;
        case ROM_SDSNATCHER:  strcat(rom2, CARTNAME_SDSNATCHER); break;
        case ROM_SCCMIRRORED: strcat(rom2, CARTNAME_SCCMIRRORED); break;
        case ROM_SCCEXTENDED: strcat(rom2, CARTNAME_SCCEXPANDED); break;
        case ROM_FMPAC:       strcat(rom2, CARTNAME_FMPAC); break;
        case ROM_PAC:         strcat(rom2, CARTNAME_PAC); break;
        case ROM_SONYHBI55:   strcat(rom2, CARTNAME_SONYHBI55); break;
        }
    }

    if (strlen(rom1)  && !insertCartridge(properties, 0, rom1, *rom1zip ? rom1zip : NULL, romType1, -1)) return 0;
    if (strlen(rom2)  && !insertCartridge(properties, 1, rom2, *rom2zip ? rom2zip : NULL, romType2, -1)) return 0;
    if (strlen(diskA) && !insertDiskette(properties, 0, diskA, *diskAzip ? diskAzip : NULL, -1)) return 0;
    if (strlen(diskB) && !insertDiskette(properties, 1, diskB, *diskBzip ? diskBzip : NULL, -1)) return 0;
    if (strlen(cas)   && !insertCassette(properties, cas, *caszip ? caszip : NULL, -1)) return 0;

    if (properties->cassette.autoRewind) {
        tapeSetCurrentPos(0);
    }

    if (strlen(machineName)) strcpy(properties->emulation.machineName, machineName);

    emulatorStop();
    emulatorStart(NULL);

    return 1;
}

int emuTryStartWithArguments(Properties* properties, char* cmdLine) {
    if (cmdLine == NULL || *cmdLine == 0) {
        return 0;
    }

    if (*cmdLine) {
        int success;
        if (0 == strncmp(cmdLine, "/onearg ", 8)) {
            char args[2048];
            char* ptr;
            sprintf(args, "\"%s", cmdLine + 8);
            ptr = args + strlen(args);
            while(*--ptr == ' ') {
                *ptr = 0; 
            }
            strcat(args, "\"");
            success = emuStartWithArguments(properties, args);
        }
        else {
            success = emuStartWithArguments(properties, cmdLine);
        }
        if (!success) {
            return -1;
        }
    }

    return 1;
}