/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Debugger/DebugDeviceManager.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2005-02-12 20:18:34 $
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
#include "DebugDeviceManager.h"
#include <stdlib.h>
#include <string.h>

#define MAX_DEVICES 64

typedef struct {
    int handle;
    SetDebugInfo setDebugInfo;
    void* ref;
    char  name[32];
} DebugDeviceInfo;

typedef struct {
    DebugDeviceInfo di[MAX_DEVICES];
    int count;
    int lastHandle;
} DebugDeviceManager;

static DebugDeviceManager devManager;

void debugDeviceManagerReset() 
{
    devManager.count = 0;
    devManager.lastHandle = 0;
}

int debugDeviceRegister(const char* name, SetDebugInfo setDebugInfo, void* ref)
{
    if (devManager.count >= MAX_DEVICES) {
        return 0;
    }

    devManager.di[devManager.count].handle       = ++devManager.lastHandle;
    devManager.di[devManager.count].setDebugInfo = setDebugInfo;
    devManager.di[devManager.count].ref          = ref;

    strcpy(devManager.di[devManager.count].name, name);

    devManager.count++;

    return devManager.lastHandle - 1;
}

void debugDeviceUnregister(int handle)
{
    int i;

    if (devManager.count == 0) {
        return;
    }

    for (i = 0; i < devManager.count; i++) {
        if (devManager.di[i].handle == handle + 1) {
            break;
        }
    }

    if (i == devManager.count) {
        return;
    }

    devManager.count--;
    while (i < devManager.count) {
        devManager.di[i] = devManager.di[i + 1];
        i++;
    }
}

void debugDeviceGetSnapshot(DbgDevice** dbgDeviceList, int* count)
{
    int index = 0;
    int i;

    for (i = 0; i < devManager.count; i++) {
        if (devManager.di[i].handle != 0) {
            dbgDeviceList[index] = calloc(1, sizeof(DbgDevice));
            strcpy(dbgDeviceList[index]->name, devManager.di[i].name);
            dbgDeviceList[index]->deviceHandle = devManager.di[i].handle;
            devManager.di[i].setDebugInfo(devManager.di[i].ref, dbgDeviceList[index++]);
        }
    }

    *count = index;
}


DbgDevice* dbgDeviceCreate(int handle)
{
    DbgDevice* device = calloc(1, sizeof(DbgDevice));

    strcpy(device->name, devManager.di[handle].name);
    device->deviceHandle = devManager.di[handle].handle;

    return device;
}

DbgMemoryBlock* dbgDeviceAddMemoryBlock(DbgDevice* dbgDevice,
                                        const char* name,
                                        UInt32 startAddress,
                                        UInt32 size,
                                        UInt8* memory)
{
    DbgMemoryBlock* mem;
    int i;
    for (i = 0; i < MAX_DBG_COMPONENTS; i++) {
        if (dbgDevice->memoryBlock[i] == NULL) {
            break;
        }
    }

    if (i == MAX_DBG_COMPONENTS) {
        return NULL;
    }

    mem = malloc(sizeof(DbgMemoryBlock) + size);
    strcpy(mem->name, name);
    mem->startAddress = startAddress;
    mem->size = size;
    memcpy(mem->memory, memory, size);

    dbgDevice->memoryBlock[i] = mem;

    return mem;
}


DbgRegisterBank* dbgDeviceAddRegisterBank(DbgDevice* dbgDevice,
                                          const char* name,
                                          UInt32 registerCount)
{
    DbgRegisterBank* regBank;
    int i;
    for (i = 0; i < MAX_DBG_COMPONENTS; i++) {
        if (dbgDevice->registerBank[i] == NULL) {
            break;
        }
    }

    if (i == MAX_DBG_COMPONENTS) {
        return NULL;
    }

    regBank = calloc(1, sizeof(DbgRegisterBank) + registerCount * sizeof(struct DbgRegister));
    strcpy(regBank->name, name);
    regBank->count = registerCount;

    dbgDevice->registerBank[i] = regBank;

    return regBank;
}

void dbgRegisterBankAddRegister(DbgRegisterBank* regBank,
                                int index,
                                const char* name,
                                UInt8 value)
{
    strcpy(regBank->reg[index].name, name);
    regBank->reg[index].value = value;
}

DbgIoPorts* dbgDeviceAddIoPorts(DbgDevice* dbgDevice,
                                const char* name,
                                UInt32 ioPortsCount)
{
    DbgIoPorts* ioPorts;
    int i;
    for (i = 0; i < MAX_DBG_COMPONENTS; i++) {
        if (dbgDevice->ioPorts[i] == NULL) {
            break;
        }
    }

    if (i == MAX_DBG_COMPONENTS) {
        return NULL;
    }

    ioPorts = calloc(1, sizeof(DbgIoPorts) + ioPortsCount * sizeof(struct DbgIoPort));
    strcpy(ioPorts->name, name);
    ioPorts->count = ioPortsCount;

    dbgDevice->ioPorts[i] = ioPorts;

    return ioPorts;
}

void dbgIoPortsAddPort(DbgIoPorts* ioPorts,
                       int index,
                       UInt16 port,
                       UInt8 value)
{
    ioPorts->port[index].port = port;    
    ioPorts->port[index].value = value;
}

