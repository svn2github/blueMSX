/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Debugger/Debugger.h,v $
**
** $Revision: 1.2 $
**
** $Date: 2005-02-11 16:49:43 $
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

typedef void (*EmulatorStartCb)();
typedef void (*EmulatorStopCb)();
typedef void (*EmulatorPauseCb)();
typedef void (*EmulatorResumeCb)();

typedef struct Debugger Debugger;

typedef struct {
    char   name[32];
    UInt32 startAddress;
    UInt32 size;
    UInt8  memory[1];
} DbgMemoryBlock;

typedef struct {
    char   name[32];
    UInt32 count;
    struct {
        char name[8];
        UInt8  bitCount;
        UInt32 value;
    } regs[1];
} DbgRegisterBank;

typedef struct {
    UInt32 count;
    struct {
        char name[8];
        UInt8  bitCount;
        UInt32 value;
    } regs[1];
} DbgIoPorts;

typedef struct {
    char name[64];
    int  memoryBblocks;
    int  registerBanks;
    int  ioPortBanks;
} DbgDevice;

Debugger* debuggerCreate(EmulatorStartCb*  startCb,
                         EmulatorStopCb*   stopCb,
                         EmulatorPauseCb*  pauseCb,
                         EmulatorResumeCb* resumeCb);

int debuggerGetDeviceCount();

DbgDevice* debuggerGetDevice(int index);

DbgMemoryBlock*  dbgDeviceGetMemoryBlock(DbgDevice* dbgDevice, int index);
DbgRegisterBank* dbgDeviceGetRegisterBank(DbgDevice* dbgDevice, int index);
DbgIoPorts*      dbgDeviceGetIoPorts(DbgDevice* dbgDevice, int index);

#endif /*DEBUGGER_H*/
