/*****************************************************************************
** File:
**      Board.c
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
#include "Board.h"
#include "MSX.h"
#include "SVI.h"
#include "AudioMixer.h"
#include "YM2413.h"
#include "Y8950.h"
#include "Moonsound.h"
#include "SaveState.h"
#include "ziphelper.h"
#include <string.h>
#include <stdlib.h>

extern void PatchReset(BoardType boardType);

static int boardType;
static char baseDirectory[512];

static char saveStateVersion[32] = "blueMSX - state  v 7";

static void   (*initStatistics)(Machine*)                     = msxInitStatistics;
static void   (*softReset)()                                  = msxReset;
static int    (*run)(Machine*, DeviceInfo*, Mixer*, int, int) = msxRun;
static void   (*setFrequency)(UInt32)                         = msxSetFrequency;
static UInt32 (*systemTime)()                                 = msxSystemTime;
static void   (*saveState)()                                  = msxSaveState;
static int    (*getRefreshRate)()                             = msxGetRefreshRate;
static void   (*setInt)(UInt32)                               = msxSetInt;
static void   (*clearInt)(UInt32)                             = msxClearInt;
static UInt32 (*getInt)()                                     = msxGetInt;
static void   (*traceEnable)(const char*)                     = msxTraceEnable;
static void   (*traceDisable)()                               = msxTraceDisable;
static int    (*traceGetEnable)()                             = msxTraceGetEnable;
static UInt8* (*getRamPage)(page)                             = msxGetRamPage;
static UInt32 (*getRamSize)()                                 = msxGetRamSize;
static UInt32 (*getVramSize)()                                = msxGetVramSize;
static int    (*useRom)()                                     = msxUseRom;
static int    (*useMegaRom)()                                 = msxUseMegaRom;
static int    (*useMegaRam)()                                 = msxUseMegaRam;
static int    (*useFmPac)()                                   = msxUseFmPac;
static void   (*changeCartridge)(int, RomType, char*, char*)  = msxChangeCartridge;
static void   (*changeDiskette)(int, char*, const char*)      = msxChangeDiskette;
static void   (*changeCassette)(char*, const char*)           = msxChangeCassette;

static void boardSetType(BoardType type)
{
    boardType = type;
    switch (type) {
    default:
    case BOARD_MSX:
        initStatistics  = msxInitStatistics;
        softReset       = msxReset;
        run             = msxRun;
        setFrequency    = msxSetFrequency;
        systemTime      = msxSystemTime;
        saveState       = msxSaveState;
        getRefreshRate  = msxGetRefreshRate;
        setInt          = msxSetInt;
        clearInt        = msxClearInt;
        getInt          = msxGetInt;
        traceEnable     = msxTraceEnable;
        traceDisable    = msxTraceDisable;
        traceGetEnable  = msxTraceGetEnable;
        getRamPage      = msxGetRamPage;
        getRamSize      = msxGetRamSize;
        getVramSize     = msxGetVramSize;
        useRom          = msxUseRom;
        useMegaRom      = msxUseMegaRom;
        useMegaRam      = msxUseMegaRam;
        useFmPac        = msxUseFmPac;
        changeCartridge = msxChangeCartridge;
        changeDiskette  = msxChangeDiskette;
        changeCassette  = msxChangeCassette;
        break;

    case BOARD_SVI:
        initStatistics  = sviInitStatistics;
        softReset       = sviReset;
        run             = sviRun;
        setFrequency    = sviSetFrequency;
        systemTime      = sviSystemTime;
        saveState       = sviSaveState;
        getRefreshRate  = sviGetRefreshRate;
        setInt          = sviSetInt;
        clearInt        = sviClearInt;
        getInt          = sviGetInt;
        traceEnable     = sviTraceEnable;
        traceDisable    = sviTraceDisable;
        traceGetEnable  = sviTraceGetEnable;
        getRamPage      = sviGetRamPage;
        getRamSize      = sviGetRamSize;
        getVramSize     = sviGetVramSize;
        useRom          = sviUseRom;
        useMegaRom      = sviUseMegaRom;
        useMegaRam      = sviUseMegaRam;
        useFmPac        = sviUseFmPac;
        changeCartridge = sviChangeCartridge;
        changeDiskette  = sviChangeDiskette;
        changeCassette  = sviChangeCassette;
        break;
    }
    
    PatchReset(boardType);
}

int boardRun(Machine* machine, 
             DeviceInfo* deviceInfo,
             Mixer* mixer,
             char* stateFile,
             int frequency)
{
    int loadState = 0;
    boardSetType(machine->board.type);

    if (stateFile != NULL) {
        char* version;
        int   size;
    
        saveStateCreate(stateFile);
        version = zipLoadFile(stateFile, "version", &size);
        if (version != NULL) {
            if (0 == strncmp(version, saveStateVersion, sizeof(saveStateVersion) - 1)) {
                SaveState* state = saveStateOpenForRead("board");
                BoardType boardType = saveStateGet(state, "boardType", BOARD_MSX);
                saveStateClose(state);

                boardSetType(boardType);

                loadState = 1;
            }
            free(version);
        }
    }

    return run(machine, deviceInfo, mixer, loadState, frequency);
}

BoardType boardGetType()
{
    return boardType;
}

void boardSetMachine(Machine* machine)
{
    boardSetType(machine->board.type);

    initStatistics(machine);
}

void boardReset()
{
    softReset();
}

void boardSaveState(const char* stateFile)
{
    SaveState* state;
    int rv;

    saveStateCreate(stateFile);
    
    rv = zipSaveFile(stateFile, "version", 0, saveStateVersion, strlen(saveStateVersion) + 1);
    if (!rv) {
        return;
    }
    
    state = saveStateOpenForWrite("board");

    saveStateSet(state, "boardType", boardType);

    saveStateClose(state);

    saveState(stateFile);
}

void boardSetFrequency(int frequency)
{
    setFrequency(frequency);
    
	mixerSetBoardFrequency(frequency);
}

UInt32 boardSystemTime()
{
    return systemTime();
}

int  boardGetRefreshRate()
{
    return getRefreshRate();
}

void   boardSetInt(UInt32 irq)
{
    setInt(irq);
}

void   boardClearInt(UInt32 irq)
{
    clearInt(irq);
}

UInt32 boardGetInt(UInt32 irq)
{
    return getInt(irq);
}

void boardTraceEnable(const char* fileName)
{
    traceEnable(fileName);
}

void boardTraceDisable()
{
    traceDisable();
}

int  boardTraceGetEnable()
{
    return traceGetEnable();
}

UInt8* boardGetRamPage(int page)
{
    return getRamPage(page);
}

UInt32 boardGetRamSize()
{
    return getRamSize();
}

UInt32 boardGetVramSize()
{
    return getVramSize();
}

int boardUseRom()
{
    return useRom();
}

int boardUseMegaRom()
{
    return useMegaRom();
}

int boardUseMegaRam()
{
    return useMegaRam();
}

int boardUseFmPac()
{
    return useFmPac();
}

void boardChangeCartridge(int cartNo, RomType romType, char* cart, char* cartZip)
{
    changeCartridge(cartNo, romType, cart, cartZip);
}

void boardChangeDiskette(int driveId, char* fileName, const char* fileInZipFile)
{
    changeDiskette(driveId, fileName, fileInZipFile);
}

void boardChangeCassette(char* name, const char* fileInZipFile)
{
    changeCassette(name, fileInZipFile);
}

char* boardGetBaseDirectory() {
    return baseDirectory;
}

void boardSetDirectory(char* dir)
{
    strcpy(baseDirectory, dir);
}

void boardSetYm2413Oversampling(int value)
{
    ym2413SetOversampling(value);
}

void boardSetY8950Oversampling(int value) 
{
#ifdef USE_OPENMSX_MSXAUDIO
    msxaudioSetOversampling(value);
#else
    y8950SetOversampling(value);
#endif
}
void boardSetMoonsoundOversampling(int value)
{
    moonsoundSetOversampling(value);
}
