#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>
#include "BlueMSXToolInterface.h"
#include "ToolInterface.h"

static ToolSnapshotCreate              toolSnapshotCreate;
static ToolSnapshotDestroy             toolSnapshotDestroy;
static ToolGetEmulatorState            toolGetState;
static ToolSnapshotGetDeviceCount      toolSnapshotGetDeviceCount;
static ToolSnapshotGetDevice           toolSnapshotGetDevice;

static ToolDeviceGetMemoryBlockCount   toolDeviceGetMemoryBlockCount;
static ToolDeviceGetMemoryBlock        toolDeviceGetMemoryBlock;
static ToolDeviceGetRegisterBankCount  toolDeviceGetRegisterBankCount;
static ToolDeviceGetRegisterBank       toolDeviceGetRegisterBank;
static ToolDeviceGetIoPortsCount       toolDeviceGetIoPortsCount;
static ToolDeviceGetIoPorts            toolDeviceGetIoPorts;

static HINSTANCE hInstance;


Snapshot* SnapshotCreate() {
    return toolSnapshotCreate();
}

EmulatorState GetEmulatorState()
{
    return toolGetState();
}

void SnapshotDestroy(Snapshot* snapshot) {
    toolSnapshotDestroy(snapshot);
}

int SnapshotGetDeviceCount(Snapshot* snapshot) {
    return toolSnapshotGetDeviceCount(snapshot);
}

Device* SnapshotGetDevice(Snapshot* snapshot, int index) {
    return toolSnapshotGetDevice(snapshot, index);
}

int DeviceGetMemoryBlockCount(Device* device) {
    return toolDeviceGetMemoryBlockCount(device);
}

MemoryBlock* DeviceGetMemoryBlock(Device* device, int index) {
    return toolDeviceGetMemoryBlock(device, index);
}

int DeviceGetRegisterBankCount(Device* device) {
    return toolDeviceGetRegisterBankCount(device);
}

RegisterBank* DeviceGetRegisterBank(Device* device, int index) {
    return toolDeviceGetRegisterBank(device, index);
}

int DeviceGetIoPortsCount(Device* device) {
    return toolDeviceGetIoPortsCount(device);
}

IoPorts* DeviceGetIoPorts(Device* device, int index) {
    return toolDeviceGetIoPorts(device, index);
}

HINSTANCE GetDllHinstance()
{
    return hInstance;
}

extern "C" __declspec(dllexport) int __stdcall Create10(Interface* toolInterface, char* name, int length)
{
    strcpy(name, GetName());
    
    toolSnapshotCreate              = toolInterface->create;
    toolSnapshotDestroy             = toolInterface->destroy;
    toolGetState                    = toolInterface->getState;
    toolSnapshotGetDeviceCount      = toolInterface->getDeviceCount;
    toolSnapshotGetDevice           = toolInterface->getDevice;
    toolDeviceGetMemoryBlockCount   = toolInterface->getMemoryBlockCount;
    toolDeviceGetMemoryBlock        = toolInterface->getMemoryBlock;
    toolDeviceGetRegisterBankCount  = toolInterface->getRegisterBankCount;
    toolDeviceGetRegisterBank       = toolInterface->getRegisterBank;
    toolDeviceGetIoPortsCount       = toolInterface->getIoPortsCount;
    toolDeviceGetIoPorts            = toolInterface->getIoPorts;

    return 1;
}

extern "C"__declspec(dllexport) void __stdcall Destroy()
{
    DestroyTool();
}

extern "C"__declspec(dllexport) void __stdcall Show()
{
    ShowTool();
}

extern "C"__declspec(dllexport) void __stdcall OnEmulatorStart()
{
    EmulatorStart();
}

extern "C"__declspec(dllexport) void __stdcall OnEmulatorStop()
{
    EmulatorStop();
}

extern "C"__declspec(dllexport) void __stdcall OnEmulatorPause()
{
    EmulatorPause();
}

extern "C"__declspec(dllexport) void __stdcall OnEmulatorResume()
{
    EmulatorResume();
}
extern "C" int APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID /*lpvReserved*/)
{
    if(fdwReason == DLL_PROCESS_ATTACH) {
        hInstance = hinstDLL;
    }

    return TRUE;
}
