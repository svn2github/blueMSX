/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/SimpleDebuggerPlugin/ToolInterface.h,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-02-23 08:48:31 $
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
#ifndef TOOL_INTERFACE_H
#define TOOL_INTERFACE_H

//
// See the include file below for the datastructures used in the interface
//
#include "BlueMSXToolInterface.h"

Snapshot* SnapshotCreate();
void SnapshotDestroy(Snapshot* snapshot);
EmulatorState GetEmulatorState();
int SnapshotGetDeviceCount(Snapshot* snapshot);
Device* SnapshotGetDevice(Snapshot* snapshot, int index);
int DeviceGetMemoryBlockCount(Device* device);
MemoryBlock* DeviceGetMemoryBlock(Device* device, int index);
int DeviceGetRegisterBankCount(Device* device);
RegisterBank* DeviceGetRegisterBank(Device* device, int index);
int DeviceGetIoPortsCount(Device* device);
IoPorts* DeviceGetIoPorts(Device* device, int index);

void EmulatorRun();
void EmulatorStop();
void EmulatorPause();
void EmulatorStep();

void SetBreakpoint(UInt16 address);
void ClearBreakpoint(UInt16 address);

HINSTANCE GetDllHinstance();

//
// To be implemented by the user....
//
void OnCreateTool();
void OnDestroyTool();
void OnShowTool();
void OnEmulatorStart();
void OnEmulatorStop();
void OnEmulatorPause();
void OnEmulatorResume();

const char* OnGetName();

#endif
