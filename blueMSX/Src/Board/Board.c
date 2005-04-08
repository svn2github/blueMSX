/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/Board.c,v $
**
** $Revision: 1.28 $
**
** $Date: 2005-04-08 05:58:46 $
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
#include "Board.h"
#include "MSX.h"
#include "SVI.h"
#include "Coleco.h"
#include "AudioMixer.h"
#include "YM2413.h"
#include "Y8950.h"
#include "Moonsound.h"
#include "SaveState.h"
#include "ziphelper.h"
#include "ArchNotifications.h"
#include "VideoManager.h"
#include "DebugDeviceManager.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

extern void PatchReset(BoardType boardType);

static int boardType;
static int cassetteInserted = 0;
static Mixer* boardMixer = NULL;
static int (*syncToRealClock)(int, int) = NULL;
UInt32* boardSysTime;
static UInt64 boardSysTime64;
static UInt32 oldTime;
static UInt32 boardFreq = boardFrequency();
static int fdcTimingEnable = 1;
static int fdcActive       = 0;
static BoardTimer* fdcTimer;
static BoardTimer* syncTimer;

static char saveStateVersion[32] = "blueMSX - state  v 7";

static void   (*initStatistics)(Machine*)                     = msxInitStatistics;
static void   (*softReset)()                                  = msxReset;
static int    (*create)(Machine*, DeviceInfo*, int)           = msxCreate;
static void   (*destroy)()                                    = msxDestroy;
static void   (*run)()                                        = msxRun;
static void   (*stop)()                                       = msxStop;
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
static int    (*changeCassette)(char*, const char*)           = msxChangeCassette;
static void   (*setCpuTimeout)(UInt32)                        = msxSetCpuTimeout;
static void   (*setBreakpoint)(UInt16)                        = msxSetBreakpoint;
static void   (*clearBreakpoint)(UInt16)                      = msxClearBreakpoint;

static void boardSetType(BoardType type)
{
    boardType = type;
    switch (type) {
    default:
    case BOARD_MSX:
        initStatistics  = msxInitStatistics;
        softReset       = msxReset;
        create          = msxCreate;
        destroy         = msxDestroy;
        run             = msxRun;
        stop            = msxStop;
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
        setCpuTimeout   = msxSetCpuTimeout;
        setBreakpoint   = msxSetBreakpoint;
        clearBreakpoint = msxClearBreakpoint;
        break;

    case BOARD_SVI:
        initStatistics  = sviInitStatistics;
        softReset       = sviReset;
        create          = sviCreate;
        destroy         = sviDestroy;
        run             = sviRun;
        stop            = sviStop;
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
        setCpuTimeout   = sviSetCpuTimeout;
        setBreakpoint   = sviSetBreakpoint;
        clearBreakpoint = sviClearBreakpoint;
        break;

    case BOARD_COLECO:
        initStatistics  = colecoInitStatistics;
        softReset       = colecoReset;
        create          = colecoCreate;
        destroy         = colecoDestroy;
        run             = colecoRun;
        stop            = colecoStop;
        saveState       = colecoSaveState;
        getRefreshRate  = colecoGetRefreshRate;
        setInt          = colecoSetInt;
        clearInt        = colecoClearInt;
        getInt          = colecoGetInt;
        traceEnable     = colecoTraceEnable;
        traceDisable    = colecoTraceDisable;
        traceGetEnable  = colecoTraceGetEnable;
        getRamPage      = colecoGetRamPage;
        getRamSize      = colecoGetRamSize;
        getVramSize     = colecoGetVramSize;
        useRom          = colecoUseRom;
        useMegaRom      = colecoUseMegaRom;
        useMegaRam      = colecoUseMegaRam;
        useFmPac        = colecoUseFmPac;
        changeCartridge = colecoChangeCartridge;
        changeDiskette  = colecoChangeDiskette;
        changeCassette  = colecoChangeCassette;
        setCpuTimeout   = colecoSetCpuTimeout;
        setBreakpoint   = colecoSetBreakpoint;
        clearBreakpoint = colecoClearBreakpoint;
        break;
    }
    
    PatchReset(boardType);
}

int boardGetFdcTimingEnable() {
    return fdcTimingEnable;
}

void boardSetFdcTimingEnable(int enable) {
    fdcTimingEnable = enable;
}

void boardSetFdcActive() {
    if (!fdcTimingEnable) {
        boardTimerAdd(fdcTimer, boardSystemTime() + (UInt32)((UInt64)500 * boardFrequency() / 1000));
        fdcActive = 1;
    }
}

void boardSetBreakpoint(UInt16 address) {
    setBreakpoint(address);
}

void boardClearBreakpoint(UInt16 address) {
    clearBreakpoint(address);
}

static void onFdcDone(void* ref, UInt32 time)
{
    fdcActive = 0;
}

static void doSync(UInt32 time, int breakpointHit)
{
    int execTime = syncToRealClock(fdcActive, breakpointHit);
    if (execTime < 0) {
        stop();
        return;
    }

    mixerSync(boardMixer);

    if (execTime == 0) {
        boardTimerAdd(syncTimer, boardSystemTime() + 1);
    }
    else {
        boardTimerAdd(syncTimer, time + (UInt32)((UInt64)execTime * boardFreq / 1000));
    }
}

static void onSync(void* ref, UInt32 time)
{
    doSync(time, 0);
}

void boardOnBreakpoint(UInt16 pc)
{
    doSync(boardSystemTime(), 1);
}

int boardRun(Machine* machine, 
             DeviceInfo* deviceInfo,
             Mixer* mixer,
             char* stateFile,
             int frequency,
             int (*syncCallback)(int, int))
{
    int loadState = 0;
    int success;
    boardSetType(machine->board.type);

    syncToRealClock = syncCallback;

    videoManagerReset();
    debugDeviceManagerReset();

    boardMixer = mixer;

    if (stateFile != NULL) {
        char* version;
        int   size;
    
        saveStateCreate(stateFile);
        version = zipLoadFile(stateFile, "version", &size);
        if (version != NULL) {
            if (0 == strncmp(version, saveStateVersion, sizeof(saveStateVersion) - 1)) {
                SaveState* state = saveStateOpenForRead("board");
                BoardType boardType = saveStateGet(state, "boardType", BOARD_MSX);
                boardSysTime64  = (UInt64)saveStateGet(state, "boardSysTime64Hi", 0) << 32 |
                                  (UInt64)saveStateGet(state, "boardSysTime64Lo", 0);
                oldTime = saveStateGet(state, "oldTime", 0);
                saveStateClose(state);

                boardSetType(boardType);

                loadState = 1;
            }
            free(version);
        }
    }

    boardSetFrequency(frequency);

    success = create(machine, deviceInfo, loadState);
    if (success) {
        syncTimer = boardTimerCreate(onSync, NULL);
        fdcTimer = boardTimerCreate(onFdcDone, NULL);
        
        boardTimerAdd(syncTimer, boardSystemTime() + 1);

        run();

        destroy();

        boardTimerDestroy(fdcTimer);
        boardTimerDestroy(syncTimer);
    }

    return success;
}

BoardType boardGetType()
{
    return boardType;
}

Mixer* boardGetMixer()
{
    return boardMixer;
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
    char buf[128];
    time_t ltime;
    SaveState* state;
    int size;
    void* bitmap;
    int rv;

    saveStateCreate(stateFile);
    
    rv = zipSaveFile(stateFile, "version", 0, saveStateVersion, strlen(saveStateVersion) + 1);
    if (!rv) {
        return;
    }
    
    state = saveStateOpenForWrite("board");

    saveStateSet(state, "boardType", boardType);
    saveStateSet(state, "boardSysTime64Hi", (UInt32)(boardSysTime64 >> 32));
    saveStateSet(state, "boardSysTime64Lo", (UInt32)boardSysTime64);
    saveStateSet(state, "oldTime", oldTime);

    saveStateClose(state);

    saveState(stateFile);

    bitmap = archScreenCapture(SC_SMALL, &size);
    if (size > 0) {
        zipSaveFile(stateFile, "screenshot.bmp", 1, bitmap, size);
    }
    free(bitmap);

    memset(buf, 0, 128);
    time(&ltime);
    strftime(buf, 128, "%X   %A, %B %d, %Y", localtime(&ltime));
    zipSaveFile(stateFile, "date.txt", 1, buf, strlen(buf) + 1);
}


void boardSetFrequency(int frequency)
{
    boardFreq = frequency * (boardFrequency() / 3579545);
    
	mixerSetBoardFrequency(frequency);
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
    cassetteInserted = changeCassette(name, fileInZipFile);
}

int boardGetCassetteInserted()
{
    return cassetteInserted;
}

#define HIRES_CYCLES_PER_LORES_CYCLE (UInt64)100000
#define boardFrequency64() (HIRES_CYCLES_PER_LORES_CYCLE * boardFrequency())

UInt32 boardCalcRelativeTimeout(UInt32 timerFrequency, UInt32 nextTimeout)
{
    UInt64 currentTime = boardSystemTime64();
    UInt64 frequency   = boardFrequency64() / timerFrequency;

    currentTime = frequency * (currentTime / frequency);

    return (UInt32)((currentTime + nextTimeout * frequency) / HIRES_CYCLES_PER_LORES_CYCLE);
}

/////////////////////////////////////////////////////////////
// Board timer

typedef struct BoardTimer {
    BoardTimer*  next;
    BoardTimer*  prev;
    BoardTimerCb callback;
    void*        ref;
    UInt32       timeout;
};

static BoardTimer* timerList = NULL;
static UInt32 timeAnchor;

#define MAX_TIME  (2 * 1368 * 313)
#define TEST_TIME 0x7fffffff

BoardTimer* boardTimerCreate(BoardTimerCb callback, void* ref)
{
    BoardTimer* timer = malloc(sizeof(BoardTimer));

    timer->next     = timer;
    timer->prev     = timer;
    timer->callback = callback;
    timer->ref      = ref ? ref : timer;
    timer->timeout  = 0;

    return timer;
}

void boardTimerDestroy(BoardTimer* timer)
{
    boardTimerRemove(timer);

    free(timer);
}

void boardTimerAdd(BoardTimer* timer, UInt32 timeout)
{
    UInt32 currentTime = boardSystemTime();
    BoardTimer* refTimer;
    BoardTimer* next = timer->next;
    BoardTimer* prev = timer->prev;

    // Remove current timer
    next->prev = prev;
    prev->next = next;

    timerList->timeout = currentTime + TEST_TIME;

    refTimer = timerList->next;

    if (timeout - timeAnchor - TEST_TIME < currentTime - timeAnchor - TEST_TIME) {
        timer->next = timer;
        timer->prev = timer;
        
        // Time has already expired
        return;
    }

    while (timeout - timeAnchor > refTimer->timeout - timeAnchor) {
        refTimer = refTimer->next;
    }

    timer->timeout       = timeout;
    timer->next          = refTimer;
    timer->prev          = refTimer->prev;
    refTimer->prev->next = timer;
    refTimer->prev       = timer;

    setCpuTimeout(timerList->next->timeout);
}

void boardTimerRemove(BoardTimer* timer)
{
    BoardTimer* next = timer->next;
    BoardTimer* prev = timer->prev;

    next->prev = prev;
    prev->next = next;

    timer->next = timer;
    timer->prev = timer;
}

UInt32 boardTimerCheckTimeout()
{
    UInt32 currentTime = boardSystemTime();
    timerList->timeout = currentTime + MAX_TIME;

    for (;;) {
        BoardTimer* timer = timerList->next;
        if (timer == timerList) {
            return currentTime + 1000;
        }
        if (timer->timeout - timeAnchor > currentTime - timeAnchor) {
            break;
        }

        boardTimerRemove(timer);
        timer->callback(timer->ref, timer->timeout);
    }

    timeAnchor = currentTime;    

    setCpuTimeout(timerList->next->timeout);

    return timerList->next->timeout - currentTime;
}

UInt64 boardSystemTime64() {
    UInt32 currentTime = boardSystemTime();
    boardSysTime64 += HIRES_CYCLES_PER_LORES_CYCLE * (currentTime - oldTime);
    oldTime = currentTime;
    return boardSysTime64;
}

void boardInit(UInt32* systemTime)
{
    boardSysTime = systemTime;
    oldTime = *systemTime;
    boardSysTime64 = oldTime * HIRES_CYCLES_PER_LORES_CYCLE;

    timeAnchor = *systemTime;
    if (timerList != NULL) {
        for (;;) {
            BoardTimer* timer = timerList->next;
            if (timer == timerList) {
                break;
            }
            boardTimerRemove(timer);
        }

        free(timerList);
    }
    timerList = boardTimerCreate(NULL, NULL);
}


/////////////////////////////////////////////////////////////
// Not board specific stuff....

static char baseDirectory[512];
static int oversamplingYM2413    = 1;
static int oversamplingY8950     = 1;
static int oversamplingMoonsound = 1;
static int enableYM2413          = 1;
static int enableY8950           = 1;
static int enableMoonsound       = 1;
static int videoAutodetect       = 1;

char* boardGetBaseDirectory() {
    return baseDirectory;
}

void boardSetDirectory(char* dir) {
    strcpy(baseDirectory, dir);
}

void boardSetYm2413Oversampling(int value) {
    oversamplingYM2413 = value;
}

int boardGetYm2413Oversampling() {
    return oversamplingYM2413;
}

void boardSetY8950Oversampling(int value) {
    oversamplingY8950 = value;
}

int boardGetY8950Oversampling() {
    return oversamplingY8950;
}

void boardSetMoonsoundOversampling(int value) {
    oversamplingMoonsound = value;
}

int boardGetMoonsoundOversampling() {
    return oversamplingMoonsound;
}

void boardSetYm2413Enable(int value) {
    enableYM2413 = value;
}

int boardGetYm2413Enable() {
    return enableYM2413;
}

void boardSetY8950Enable(int value) {
    enableY8950 = value;
}

int boardGetY8950Enable() {
    return enableY8950;
}

void boardSetMoonsoundEnable(int value) {
    enableMoonsound = value;
}

int boardGetMoonsoundEnable() {
    return enableMoonsound;
}

void boardSetVideoAutodetect(int value) {
    videoAutodetect = value;
}

int  boardGetVideoAutodetect() {
    return videoAutodetect;
}
