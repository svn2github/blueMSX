/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Debugger/Debugger.h,v $
**
** $Revision: 1.3 $
**
** $Date: 2005-02-12 09:30:07 $
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
#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "MsxTypes.h"

typedef void (*DebuggerEvent)();

typedef struct Debugger    Debugger;
typedef struct DbgSnapshot DbgSnapshot;
typedef struct DbgDevice   DbgDevice;

typedef struct {
    char   name[32];
    UInt32 startAddress;
    UInt32 size;
    UInt8  memory[1];
} DbgMemoryBlock;

typedef struct {
    char   name[32];
    UInt32 count;
    struct DbgRegister {
        char  name[7];
        UInt8 value;
    } reg[1];
} DbgRegisterBank;

typedef struct {
    char name[32];
    UInt32 count;
    struct DbgIoPort {
        UInt16 port;
        UInt8  value;
    } port[1];
} DbgIoPorts;

Debugger* debuggerCreate(DebuggerEvent onEmulatorStart,
                         DebuggerEvent onEmulatorStop,
                         DebuggerEvent onEmulatorPause,
                         DebuggerEvent onEmulatorResume);

void debuggerDestroy(Debugger* debugger);

DbgSnapshot*     dbgSnapshotCreate(Debugger* debugger);
void             dbgSnapshotDestroy(DbgSnapshot* dbgSnapshot);
int              dbgSnapshotGetDeviceCount(DbgSnapshot* dbgSnapshot);
const DbgDevice* dbgSnapshotGetDevice(DbgSnapshot* dbgSnapshot, int deviceIndex);

int                    dbgDeviceGetMemoryBlockCount(DbgDevice* dbgDevice);
const DbgMemoryBlock*  dbgDeviceGetMemoryBlock(DbgDevice* dbgDevice, int memBlockIndex);
int                    dbgDeviceGetRegisterBankCount(DbgDevice* dbgDevice);
const DbgRegisterBank* dbgDeviceGetRegisterBank(DbgDevice* dbgDevice, int regBankIndex);
int                    dbgDeviceGetIoPortsCount(DbgDevice* dbgDevice);
const DbgIoPorts*      dbgDeviceGetIoPorts(DbgDevice* dbgDevice, int ioPortIndex);


// Internal structure

struct DbgDevice {
    char name[64];
    DbgMemoryBlock*  memoryBlock[4];
    DbgRegisterBank* registerBank[4];
    DbgIoPorts*      ioPorts[4];
    int              deviceHandle;
};


#endif /*DEBUGGER_H*/
