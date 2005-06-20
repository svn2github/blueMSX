/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/BlueMSXToolInterface.h,v $
**
** $Revision: 1.14 $
**
** $Date: 2005-06-20 00:31:20 $
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
#ifndef BLUEMSX_TOOL_INTERFACE_H
#define BLUEMSX_TOOL_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BLUEMSX_TYPES
#define BLUEMSX_TYPES

#ifdef __GNUC__
#define __int64 long long
#endif

typedef unsigned char    UInt8;
typedef unsigned short   UInt16;
typedef unsigned long    UInt32;
typedef unsigned __int64 UInt64;
typedef signed   char    Int8;
typedef signed   short   Int16;
typedef signed   long    Int32;

#endif

typedef enum { EMULATOR_STOPPED, EMULATOR_PAUSED, EMULATOR_RUNNING } EmulatorState;

typedef struct Snapshot Snapshot;
typedef struct Device   Device;

typedef enum { 
    DEVTYPE_UNKNOWN,
    DEVTYPE_CPU, 
    DEVTYPE_CART, 
    DEVTYPE_BIOS, 
    DEVTYPE_RAM, 
    DEVTYPE_AUDIO,
    DEVTYPE_VIDEO,
    DEVTYPE_IOPORT
} DeviceType;

struct Device {
    char name[64];
    DeviceType type;
    int  deviceId;
};


typedef struct {
    int    deviceId;
    char   name[32];
    int    writeProtected;
    UInt32 startAddress;
    UInt32 size;
    UInt8  memory[1];
} MemoryBlock;

typedef struct {
    int    deviceId;
    char   name[32];
    UInt32 count;
    struct Register {
        char  name[7];
        UInt8 width;
        UInt32 value;
    } reg[1];
} RegisterBank;

typedef struct {
    int    deviceId;
    char   name[32];
    UInt32 size;
    UInt32 callstack[1];
} Callstack;

typedef struct {
    int    deviceId;
    char   name[32];
    UInt32 count;
    struct IoPort {
        UInt16 port;
        UInt8  value;
    } port[1];
} IoPorts;





/////////////////////////////////
/// DLL interface

typedef Snapshot*     (__stdcall *ToolSnapshotCreate)();
typedef void          (__stdcall *ToolSnapshotDestroy)(Snapshot* Snapshot);
typedef EmulatorState (__stdcall *ToolGetEmulatorState)();
typedef int           (__stdcall *ToolSnapshotGetDeviceCount)(Snapshot* Snapshot);
typedef Device*       (__stdcall *ToolSnapshotGetDevice)(Snapshot* Snapshot, int deviceIndex);

typedef int           (__stdcall *ToolDeviceGetMemoryBlockCount)(Device* device);
typedef MemoryBlock*  (__stdcall *ToolDeviceGetMemoryBlock)(Device* device, int memBlockIndex);
typedef int           (__stdcall *ToolDeviceWriteMemory)(MemoryBlock* memoryBlock, void* data, int startAddr, int size);
typedef int           (__stdcall *ToolDeviceGetRegisterBankCount)(Device* device);
typedef RegisterBank* (__stdcall *ToolDeviceGetRegisterBank)(Device* device, int regBankIndex);
typedef int           (__stdcall *ToolDeviceWriteRegister)(RegisterBank* regBank, int regIndex, UInt32 value);
typedef int           (__stdcall *ToolDeviceGetCallstackCount)(Device* device);
typedef Callstack*    (__stdcall *ToolDeviceGetCallstack)(Device* device, int callstackIndex);
typedef int           (__stdcall *ToolDeviceGetIoPortsCount)(Device* device);
typedef IoPorts*      (__stdcall *ToolDeviceGetIoPorts)(Device* device, int ioPortIndex);
typedef int           (__stdcall *ToolDeviceWriteIoPort)(IoPorts* ioPorts, int portIndex, UInt32 value);
typedef void          (__stdcall *ToolAction)();
typedef void          (__stdcall *ToolBreakpoint)(UInt16);
typedef char*         (__stdcall *ToolPath)();
typedef void          (__stdcall *ToolEmulatorVersion)(int* major, int* minor, int* buildNumber);
typedef struct {
    ToolSnapshotCreate              create;
    ToolSnapshotDestroy             destroy;
    ToolGetEmulatorState            getState;
    ToolSnapshotGetDeviceCount      getDeviceCount;
    ToolSnapshotGetDevice           getDevice;

    ToolDeviceGetMemoryBlockCount   getMemoryBlockCount;
    ToolDeviceGetMemoryBlock        getMemoryBlock;
    ToolDeviceWriteMemory           writeMemoryBlockSement;
    ToolDeviceGetRegisterBankCount  getRegisterBankCount;
    ToolDeviceGetRegisterBank       getRegisterBank;
    ToolDeviceWriteRegister         writeRegisterBankRegister;
    ToolDeviceGetCallstackCount     getCallstackCount;
    ToolDeviceGetCallstack          getCallstack;
    ToolDeviceGetIoPortsCount       getIoPortsCount;
    ToolDeviceGetIoPorts            getIoPorts;
    ToolDeviceWriteIoPort           writeIoPortsPort;

    ToolAction                      run;
    ToolAction                      stop;
    ToolAction                      pause;
    ToolAction                      step;

    ToolBreakpoint                  setBreakpoint;
    ToolBreakpoint                  clearBreakpoint;

    ToolPath                        getToolDirectory;
    ToolEmulatorVersion             getEmulatorVersion;
} Interface;

typedef int  (__stdcall *CreateFn)(Interface*, char*, int);
typedef void (__stdcall *NotifyFn)();
typedef void (__stdcall *TraceFn)(const char*);
typedef void (__stdcall *SetBpFn)(UInt16, UInt16, UInt16);

__declspec(dllexport) int  __stdcall Create10(Interface*, char* name, int length);
__declspec(dllexport) void __stdcall Show();
__declspec(dllexport) void __stdcall NotifyEmulatorStart();
__declspec(dllexport) void __stdcall NotifyEmulatorStop();
__declspec(dllexport) void __stdcall NotifyEmulatorPause();
__declspec(dllexport) void __stdcall NotifyEmulatorResume();
__declspec(dllexport) void __stdcall NotifyEmulatorReset();
__declspec(dllexport) void __stdcall EmulatorTrace(const char* message);
__declspec(dllexport) void __stdcall EmulatorSetBreakpoint(UInt16 address);

#ifdef __cplusplus
}
#endif

#endif
