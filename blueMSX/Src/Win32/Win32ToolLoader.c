/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32ToolLoader.c,v $
**
** $Revision: 1.7 $
**
** $Date: 2005-02-26 08:02:34 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vikl, Tomas Karlsson
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
#include <windows.h>
#include <tchar.h>
#include "Win32ToolLoader.h"
#include "BlueMSXToolInterface.h"
#include "Debugger.h"
#include "Actions.h"

#define MAX_TOOLS 16

struct ToolInfo {
    char description[32];
    HINSTANCE library;
    Debugger* debugger;

    struct {
        NotifyFn show;
        NotifyFn destroy;
        NotifyFn onEmulatorStart;
        NotifyFn onEmulatorStop;
        NotifyFn onEmulatorPause;
        NotifyFn onEmulatorResume;
    } callbacks;
};

static ToolInfo* toolList[MAX_TOOLS];
static int       toolListCount = 0;
static volatile int isUpdating = 0;

static void onEmulatorStart(ToolInfo* toolInfo) {
    if (!isUpdating && toolInfo->callbacks.onEmulatorStart != NULL) {
        toolInfo->callbacks.onEmulatorStart();
    }
}

static void onEmulatorStop(ToolInfo* toolInfo) {
    if (!isUpdating && toolInfo->callbacks.onEmulatorStop != NULL) {
        toolInfo->callbacks.onEmulatorStop();
    }
}

static void onEmulatorPause(ToolInfo* toolInfo) {
    if (!isUpdating && toolInfo->callbacks.onEmulatorPause != NULL) {
        toolInfo->callbacks.onEmulatorPause();
    }
}

static void onEmulatorResume(ToolInfo* toolInfo) {
    if (!isUpdating && toolInfo->callbacks.onEmulatorResume != NULL) {
        toolInfo->callbacks.onEmulatorResume();
    }
}

Snapshot* __stdcall toolSnapshotCreate() {
    if (dbgGetState() == DBG_RUNNING) {
        Snapshot* snapshot;
        isUpdating = 1;
        actionEmuTogglePause();
        snapshot = (Snapshot*)dbgSnapshotCreate(NULL);
        actionEmuTogglePause();
        isUpdating = 0;
        return snapshot;
    }
    return (Snapshot*)dbgSnapshotCreate(NULL);
}

void __stdcall toolSnapshotDestroy(Snapshot* s) {
    dbgSnapshotDestroy((DbgSnapshot*)s);
}

EmulatorState __stdcall toolGetState() {
    return dbgGetState();
}

int __stdcall toolSnapshotGetDeviceCount(Snapshot* s)
{
    return dbgSnapshotGetDeviceCount((DbgSnapshot*)s);
}

Device* __stdcall toolSnapshotGetDevice(Snapshot* s, int d)
{
    return (Device*)dbgSnapshotGetDevice((DbgSnapshot*)s, d);
}

int __stdcall toolDeviceGetMemoryBlockCount(Device* d)
{
    return dbgDeviceGetMemoryBlockCount((DbgDevice*)d);
}

MemoryBlock* __stdcall toolDeviceGetMemoryBlock(Device* d, int m)
{
    return (MemoryBlock*)dbgDeviceGetMemoryBlock((DbgDevice*)d, m);
}

int __stdcall toolDeviceGetRegisterBankCount(Device* d)
{
    return dbgDeviceGetRegisterBankCount((DbgDevice*)d);
}

RegisterBank* __stdcall toolDeviceGetRegisterBank(Device* d, int r)
{
    return (RegisterBank*)dbgDeviceGetRegisterBank((DbgDevice*)d, r);
}

int __stdcall toolDeviceGetIoPortsCount(Device* d)
{
    return dbgDeviceGetIoPortsCount((DbgDevice*)d);
}

IoPorts* __stdcall toolDeviceGetIoPorts(Device* d, int p)
{
    return (IoPorts*)dbgDeviceGetIoPorts((DbgDevice*)d, p);
}

void __stdcall toolRun()
{
    dbgRun();
}

void __stdcall toolStop()
{
    dbgStop();
}

void __stdcall toolPause()
{
    dbgPause();
}

void __stdcall toolStep()
{
    dbgStep();
}

void __stdcall toolSetBreakpoint(UInt16 address)
{
    dbgSetBreakpoint(address);
}

void __stdcall toolClearBreakpoint(UInt16 address)
{
    dbgClearBreakpoint(address);
}

int __stdcall toolWriteMemory(MemoryBlock* memoryBlock, void* data, int startAddr, int size)
{
    return dbgDeviceWriteMemory((DbgMemoryBlock*)memoryBlock, data, startAddr, size);
}

int __stdcall toolWriteRegister(RegisterBank* regBank, int regIndex, UInt32 value)
{
    return dbgDeviceWriteRegister((DbgRegisterBank*)regBank, regIndex, value);
}

int __stdcall toolDeviceWriteIoPort(IoPorts* ioPorts, int portIndex, UInt32 value)
{
    return dbgDeviceWriteIoPort((DbgIoPorts*)ioPorts, portIndex, value);
}

static Interface toolInterface = {
    toolSnapshotCreate,
    toolSnapshotDestroy,
    toolGetState,
    toolSnapshotGetDeviceCount,
    toolSnapshotGetDevice,
    toolDeviceGetMemoryBlockCount,
    toolDeviceGetMemoryBlock,
    toolWriteMemory,
    toolDeviceGetRegisterBankCount,
    toolDeviceGetRegisterBank,
    toolWriteRegister,
    toolDeviceGetIoPortsCount,
    toolDeviceGetIoPorts,
    toolDeviceWriteIoPort,
    toolRun,
    toolStop,
    toolPause,
    toolStep,
    toolSetBreakpoint,
    toolClearBreakpoint
};

void toolLoadAll(const char* path)
{
    WIN32_FIND_DATA wfd;
    char  curDir[MAX_PATH];
    char  toolDir[MAX_PATH] = "";
    HANDLE handle;

    GetCurrentDirectory(MAX_PATH, curDir);
    strcat(toolDir, curDir);
    strcat(toolDir, "\\Tools");

    if (!SetCurrentDirectory(toolDir)) {
        return;
    }

    handle = FindFirstFile("*.dll", &wfd);

    if (handle == INVALID_HANDLE_VALUE) {
        SetCurrentDirectory(curDir);
        return;
    }

    do {
        ToolInfo* toolInfo;
        HINSTANCE lib = LoadLibrary(wfd.cFileName);

        if (lib != NULL) {
            char description[32] = "Unknown";
            CreateFn create   = (CreateFn)GetProcAddress(lib, (LPCSTR)1);
            NotifyFn destroy  = (NotifyFn)GetProcAddress(lib, (LPCSTR)2);
            NotifyFn show     = (NotifyFn)GetProcAddress(lib, (LPCSTR)3);
            NotifyFn onStart  = (NotifyFn)GetProcAddress(lib, (LPCSTR)4);
            NotifyFn onStop   = (NotifyFn)GetProcAddress(lib, (LPCSTR)5);
            NotifyFn onPause  = (NotifyFn)GetProcAddress(lib, (LPCSTR)6);
            NotifyFn onResume = (NotifyFn)GetProcAddress(lib, (LPCSTR)7);

            if (create == NULL) {
                FreeLibrary(lib);
                continue;
            }

            if (create(&toolInterface, description, 31) == 0) {
                FreeLibrary(lib);
                continue;
            }

            toolInfo = malloc(sizeof(ToolInfo));
            toolInfo->callbacks.destroy          = destroy;
            toolInfo->callbacks.show             = show;
            toolInfo->callbacks.onEmulatorStart  = onStart;
            toolInfo->callbacks.onEmulatorStop   = onStop;
            toolInfo->callbacks.onEmulatorPause  = onPause;
            toolInfo->callbacks.onEmulatorResume = onResume;
            toolInfo->debugger = debuggerCreate(onEmulatorStart, onEmulatorStop, onEmulatorPause, onEmulatorResume, toolInfo);
            toolInfo->library = lib;
            strcpy(toolInfo->description, description);

            toolList[toolListCount++] = toolInfo;
        }
    } while (FindNextFile(handle, &wfd));

    SetCurrentDirectory(curDir);
}

void toolUnLoadAll()
{
    int i;

    for (i = 0; i < toolListCount; i++) {
        if (toolList[i]->callbacks.destroy != NULL) {
            toolList[i]->callbacks.destroy();
        }
        FreeLibrary((HMODULE)toolList[i]->library);
        free(toolList[i]);
    }
}

int toolGetCount() {
    return toolListCount;
}

ToolInfo* toolInfoGet(int index)
{
    if (index < 0 || index >= toolListCount) {
        return NULL;
    }

    return toolList[index];
}

const char* toolInfoGetName(ToolInfo* toolInfo)
{
    return toolInfo->description;
}

void toolInfoShowTool(ToolInfo* toolInfo)
{
    if (toolInfo->callbacks.show != NULL) {
        toolInfo->callbacks.show();
    }
}

