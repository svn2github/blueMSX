/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/Board.h,v $
**
** $Revision: 1.14 $
**
** $Date: 2005-02-06 23:38:57 $
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
        VdpSyncMode vdpSyncMode;
    } video;
} DeviceInfo;

void boardInit(UInt32* systemTime);

int boardRun(Machine* machine, 
             DeviceInfo* deviceInfo,
             Mixer* mixer,
             char* stateFile,
             int frequency,
             int (*videoSync)(int));

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

Mixer* boardGetMixer();

void boardChangeCartridge(int cartNo, RomType romType, char* cart, char* cartZip);
void boardChangeDiskette(int driveId, char* fileName, const char* fileInZipFile);
void boardChangeCassette(char* name, const char* fileInZipFile);

int  boardGetCassetteInserted();

#define boardFrequency() (6 * 3579545)

static UInt32 boardSystemTime() {
    extern UInt32* boardSysTime;
    return *boardSysTime;
}

typedef void (*BoardTimerCb)(void* ref, UInt32 time);

typedef struct BoardTimer BoardTimer;

BoardTimer* boardTimerCreate(BoardTimerCb callback, void* ref);
void boardTimerDestroy(BoardTimer* timer);
void boardTimerAdd(BoardTimer* timer, UInt32 timeout);
void boardTimerRemove(BoardTimer* timer);
UInt32 boardTimerCheckTimeout();
UInt32 boardCalcRelativeTimeout(UInt32 timerFrequency, UInt32 nextTimeout);

// The following methods are more generic config than board specific
// They should be moved from board.
void boardSetDirectory(char* dir);

void boardSetFdcTimingEnable(int enable);
int  boardGetFdcTimingEnable();
void boardSetFdcActive();

void boardSetYm2413Oversampling(int value);
int  boardGetYm2413Oversampling();
void boardSetY8950Oversampling(int value);
int  boardGetY8950Oversampling();
void boardSetMoonsoundOversampling(int value);
int  boardGetMoonsoundOversampling();

void boardSetYm2413Enable(int value);
int  boardGetYm2413Enable();
void boardSetY8950Enable(int value);
int  boardGetY8950Enable();
void boardSetMoonsoundEnable(int value);
int  boardGetMoonsoundEnable();

#endif /* BOARD_H */

