/*****************************************************************************
** File:
**      Board.h
**
** Author:
**      Daniel Vik
**
** More info:   
**      www.bluemsx.com
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
#ifndef BOARD_H
#define BOARD_H
 
#include "MSXTypes.h"
#include "RomMapper.h"
#include "Machine.h"
#include "VDP.h"
#include "audioMixer.h"
#include <stdio.h>

typedef struct {
    struct {
        int     inserted;
        RomType type;
        char    name[512];
        char    inZipName[512];
    } cartridge[2];
    struct {
        int  inserted;
        char name[512];
        char inZipName[512];
    } diskette[2];
    struct {
        int  inserted;
        char name[512];
        char inZipName[512];
    } cassette;
    struct {
        int enableYM2413;
        int enableY8950;
        int enableMoonsound;
        int moonsoundSRAM;
    } audio;
    struct {
        VdpSyncMode vdpSyncMode;
    } video;
} DeviceInfo;

int boardRun(Machine* machine, 
             DeviceInfo* deviceInfo,
             Mixer* mixer,
             char* stateFile,
             int frequency);

BoardType boardGetType();

void boardSetMachine(Machine* machine);
void boardReset();

UInt32 msxSystemTime();

void boardSaveState(const char* stateFile);

void boardSetFrequency(int frequency);
int  boardGetRefreshRate();

void   boardSetInt(UInt32 irq);
void   boardClearInt(UInt32 irq);
UInt32 boardGetInt(UInt32 irq);

void boardTraceEnable(const char* fileName);
void boardTraceDisable();
int  boardTraceGetEnable();

UInt8* boardGetRamPage(int page);
UInt32 boardGetRamSize();
UInt32 boardGetVramSize();

int boardUseRom();
int boardUseMegaRom();
int boardUseMegaRam();
int boardUseFmPac();

char* boardGetBaseDirectory();

void boardChangeCartridge(int cartNo, RomType romType, char* cart, char* cartZip);
void boardChangeDiskette(int driveId, char* fileName, const char* fileInZipFile);
void boardChangeCassette(char* name, const char* fileInZipFile);
void boardSetDirectory(char* dir);
void boardSetYm2413Oversampling(int value);
void boardSetY8950Oversampling(int value);
void boardSetMoonsoundOversampling(int value);

#define boardFrequency() (6 * 3579545)

unsigned long boardSystemTime();

#endif /* BOARD_H */

