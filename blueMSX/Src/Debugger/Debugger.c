/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Debugger/Debugger.c,v $
**
** $Revision: 1.11 $
**
** $Date: 2005-03-09 21:43:55 $
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

#include "Debugger.h"
#include "DebugDeviceManager.h"
#include "Emulator.h"
#include "Actions.h"
#include "Board.h"
#include <stdlib.h>

struct Debugger {
    DebuggerEvent onEmulatorStart;
    DebuggerEvent onEmulatorStop;
    DebuggerEvent onEmulatorPause;
    DebuggerEvent onEmulatorResume;
    DebuggerEvent onEmulatorReset;
    void* ref;
};

#define MAX_DEVICES 64
#define MAX_DEBUGGERS 64

struct DbgSnapshot {
    int count;
    DbgDevice* dbgDevice[MAX_DEVICES];
};

static Debugger* debuggerList[MAX_DEBUGGERS];
static DbgState  dbgState = DBG_STOPPED;

static void onDefault() {
}

Debugger* debuggerCreate(DebuggerEvent onEmulatorStart,
                         DebuggerEvent onEmulatorStop,
                         DebuggerEvent onEmulatorPause,
                         DebuggerEvent onEmulatorResume,
                         DebuggerEvent onEmulatorReset,
                         void* ref)
{
    Debugger* debugger = malloc(sizeof(Debugger));
    int i;

    debugger->onEmulatorStart  = onEmulatorStart  ? onEmulatorStart  : onDefault;
    debugger->onEmulatorStop   = onEmulatorStop   ? onEmulatorStop   : onDefault;
    debugger->onEmulatorPause  = onEmulatorPause  ? onEmulatorPause  : onDefault;
    debugger->onEmulatorResume = onEmulatorResume ? onEmulatorResume : onDefault;
    debugger->onEmulatorReset  = onEmulatorReset  ? onEmulatorReset  : onDefault;
    debugger->ref = ref;

    for (i = 0; i < MAX_DEBUGGERS; i++) {
        if (debuggerList[i] == NULL) {
            debuggerList[i] = debugger;
            break;
        }
    }

    return debugger;
}


void debuggerDestroy(Debugger* debugger)
{
    int i;

    for (i = 0; i < MAX_DEBUGGERS; i++) {
        if (debuggerList[i] == debugger) {
            debuggerList[i] = NULL;
            break;
        }
    }

    free(debugger);
}

void debuggerNotifyEmulatorStart()
{
    int i;
    
    dbgState = DBG_RUNNING;

    for (i = 0; i < MAX_DEBUGGERS; i++) {
        if (debuggerList[i] != NULL) {
            debuggerList[i]->onEmulatorStart(debuggerList[i]->ref);
        }
    }
}

void debuggerNotifyEmulatorStop()
{
    int i;

    dbgState = DBG_STOPPED;

    for (i = 0; i < MAX_DEBUGGERS; i++) {
        if (debuggerList[i] != NULL) {
            debuggerList[i]->onEmulatorStop(debuggerList[i]->ref);
        }
    }
}

void debuggerNotifyEmulatorPause()
{
    int i;
    
    dbgState = DBG_PAUSED;

    for (i = 0; i < MAX_DEBUGGERS; i++) {
        if (debuggerList[i] != NULL) {
            debuggerList[i]->onEmulatorPause(debuggerList[i]->ref);
        }
    }
}

void debuggerNotifyEmulatorResume()
{
    int i;
    
    dbgState = DBG_RUNNING;

    for (i = 0; i < MAX_DEBUGGERS; i++) {
        if (debuggerList[i] != NULL) {
            debuggerList[i]->onEmulatorResume(debuggerList[i]->ref);
        }
    }
}

void debuggerNotifyEmulatorReset()
{
    int i;
    
    dbgState = DBG_RUNNING;

    for (i = 0; i < MAX_DEBUGGERS; i++) {
        if (debuggerList[i] != NULL) {
            debuggerList[i]->onEmulatorReset(debuggerList[i]->ref);
        }
    }
}

DbgSnapshot* dbgSnapshotCreate() 
{
    DbgSnapshot* dbgSnapshot;
    
    if (dbgState != DBG_PAUSED) {
        return NULL;
    }

    dbgSnapshot = malloc(sizeof(DbgSnapshot));

    debugDeviceGetSnapshot(dbgSnapshot->dbgDevice, &dbgSnapshot->count);

    return dbgSnapshot;
}

int dbgDeviceWriteMemory(DbgMemoryBlock* memoryBlock, void* data, int startAddr, int size)
{
    return debugDeviceWriteMemory(memoryBlock, data, startAddr, size);
}

int dbgDeviceWriteRegister(DbgRegisterBank* regBank, int regIndex, UInt32 value)
{
    return debugDeviceWriteRegister(regBank, regIndex, value);
}

int dbgDeviceWriteIoPort(DbgIoPorts* ioPorts, int portIndex, UInt32 value)
{
    return debugDeviceWriteIoPort(ioPorts, portIndex, value);
}

void dbgSnapshotDestroy(DbgSnapshot* dbgSnapshot)
{
    int i;

    for (i = 0; i < dbgSnapshot->count; i++) {
        DbgDevice* dbgDevice = dbgSnapshot->dbgDevice[i];
        int j;
        for (j = 0; j < MAX_DBG_COMPONENTS; j++) {
            if (dbgDevice->memoryBlock[j] != NULL) {
                free(dbgDevice->memoryBlock[j]);
            }
            if (dbgDevice->registerBank[j] != NULL) {
                free(dbgDevice->registerBank[j]);
            }
            if (dbgDevice->ioPorts[j] != NULL) {
                free(dbgDevice->ioPorts[j]);
            }
        }

        free(dbgDevice);
    }
    free(dbgSnapshot);
}

DbgState dbgGetState()
{
    return dbgState;
}

int dbgSnapshotGetDeviceCount(DbgSnapshot* dbgSnapshot)
{
    return dbgSnapshot->count;
}

const DbgDevice* dbgSnapshotGetDevice(DbgSnapshot* dbgSnapshot, int index)
{
    if (index >= dbgSnapshot->count) {
        return NULL;
    }
    return dbgSnapshot->dbgDevice[index];
}

int dbgDeviceGetMemoryBlockCount(DbgDevice* dbgDevice)
{
    return dbgDevice->memoryBlockCount;
}

const DbgMemoryBlock* dbgDeviceGetMemoryBlock(DbgDevice* dbgDevice, int index)
{
    if (index >= dbgDevice->memoryBlockCount) {
        return NULL;
    }
    return dbgDevice->memoryBlock[index];
}

int dbgDeviceGetRegisterBankCount(DbgDevice* dbgDevice)
{
    return dbgDevice->registerBankCount;
}

const DbgRegisterBank* dbgDeviceGetRegisterBank(DbgDevice* dbgDevice, int index)
{
    if (index >= dbgDevice->registerBankCount) {
        return NULL;
    }
    return dbgDevice->registerBank[index];
}

int dbgDeviceGetCallstackCount(DbgDevice* dbgDevice)
{
    return dbgDevice->callstack != NULL ? 1 : 0;
}

const DbgCallstack* dbgDeviceGetCallstack(DbgDevice* dbgDevice, int index)
{
    if (index >= dbgDeviceGetCallstackCount(dbgDevice)) {
        return NULL;
    }
    return dbgDevice->callstack;
}

int dbgDeviceGetIoPortsCount(DbgDevice* dbgDevice)
{
    return dbgDevice->ioPortsCount;
}

const DbgIoPorts* dbgDeviceGetIoPorts(DbgDevice* dbgDevice, int index)
{
    if (index >= dbgDevice->ioPortsCount) {
        return NULL;
    }
    return dbgDevice->ioPorts[index];
}

void dbgRun()
{
    if (emulatorGetState() != EMU_RUNNING) {
        actionEmuTogglePause();
    }
}

void dbgStop()
{
    emulatorStop();
}

void dbgPause()
{
    if (emulatorGetState() == EMU_RUNNING) {
        actionEmuTogglePause();
    }
}

void dbgStep()
{
    if (emulatorGetState() == EMU_PAUSED) {
        actionEmuStep();
    }
}

void dbgSetBreakpoint(UInt16 address)
{
    boardSetBreakpoint(address);
}

void dbgClearBreakpoint(UInt16 address)
{
    boardClearBreakpoint(address);
}

