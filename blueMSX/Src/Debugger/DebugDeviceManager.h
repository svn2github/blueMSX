/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Debugger/DebugDeviceManager.h,v $
**
** $Revision: 1.4 $
**
** $Date: 2005-02-13 11:14:58 $
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
#ifndef DEBUG_DEVICE_MANAGER_H
#define DEBUG_DEVICE_MANAGER_H

#include "MsxTypes.h"
#include "Debugger.h"

typedef void (*SetDebugInfo)(void* ref, DbgDevice*);

void debugDeviceManagerReset();

int debugDeviceRegister(const char* name, SetDebugInfo setDebugInfo, void* ref);
void debugDeviceUnregister(int handle);

DbgMemoryBlock* dbgDeviceAddMemoryBlock(DbgDevice* dbgDevice,
                                        const char* name,
                                        UInt32 startAddress,
                                        UInt32 size,
                                        UInt8* memory);

DbgRegisterBank* dbgDeviceAddRegisterBank(DbgDevice* dbgDevice,
                                          const char* name,
                                          UInt32 registerCount);
void dbgRegisterBankAddRegister(DbgRegisterBank* regBank,
                                int index,
                                const char* name,
                                UInt8 width,
                                UInt32 value);

DbgIoPorts* dbgDeviceAddIoPorts(DbgDevice* dbgDevice,
                                const char* name,
                                UInt32 ioPortsCount);
void dbgIoPortsAddPort(DbgIoPorts* ioPorts,
                       int index,
                       UInt16 port,
                       UInt8 value);

void debugDeviceGetSnapshot(DbgDevice** dbgDeviceList, int* count);

#endif /*DEBUG_DEVICE_MANAGER_H*/
