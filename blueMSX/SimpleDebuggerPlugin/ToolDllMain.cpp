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
static ToolDeviceWriteMemory           toolDeviceWriteMemory;
static ToolDeviceGetRegisterBankCount  toolDeviceGetRegisterBankCount;
static ToolDeviceGetRegisterBank       toolDeviceGetRegisterBank;
static ToolDeviceWriteRegister         toolDeviceWriteRegister;
static ToolDeviceGetIoPortsCount       toolDeviceGetIoPortsCount;
static ToolDeviceGetIoPorts            toolDeviceGetIoPorts;
static ToolDeviceWriteIoPort           toolDeviceWriteIoPort;
static ToolAction                      toolDeviceRun;
static ToolAction                      toolDeviceStop;
static ToolAction                      toolDevicePause;
static ToolAction                      toolDeviceStep;
static ToolBreakpoint                  toolSetBreakpoint;
static ToolBreakpoint                  toolClearBreakpoint;

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

void DeviceWriteMemoryBlockMemory(MemoryBlock* memoryBlock, void* data, int startAddr, int size) {
    toolDeviceWriteMemory(memoryBlock, data, startAddr, size);
}

int DeviceGetRegisterBankCount(Device* device) {
    return toolDeviceGetRegisterBankCount(device);
}

RegisterBank* DeviceGetRegisterBank(Device* device, int index) {
    return toolDeviceGetRegisterBank(device, index);
}

void DeviceWriteRegisterBankRegister(RegisterBank* regBank, int regIndex, UInt32 value) {
    toolDeviceWriteRegister(regBank, regIndex, value);
}

int DeviceGetIoPortsCount(Device* device) {
    return toolDeviceGetIoPortsCount(device);
}

IoPorts* DeviceGetIoPorts(Device* device, int index) {
    return toolDeviceGetIoPorts(device, index);
}

void DeviceWriteIoPortsPort(IoPorts* ioPorts, int portIndex, UInt32 value) {
    toolDeviceWriteIoPort(ioPorts, portIndex, value);
}

void EmulatorRun() {
    toolDeviceRun();
}

void EmulatorStop() {
    toolDeviceStop();
}

void EmulatorPause() {
    toolDevicePause();
}

void EmulatorStep() {
    toolDeviceStep();
}

void SetBreakpoint(UInt16 address) {
    toolSetBreakpoint(address);
}

void ClearBreakpoint(UInt16 address) {
    toolClearBreakpoint(address);
}

HINSTANCE GetDllHinstance()
{
    return hInstance;
}

extern "C" __declspec(dllexport) int __stdcall Create10(Interface* toolInterface, char* name, int length)
{
    strcpy(name, OnGetName());
    
    toolSnapshotCreate              = toolInterface->create;
    toolSnapshotDestroy             = toolInterface->destroy;
    toolGetState                    = toolInterface->getState;
    toolSnapshotGetDeviceCount      = toolInterface->getDeviceCount;
    toolSnapshotGetDevice           = toolInterface->getDevice;
    toolDeviceGetMemoryBlockCount   = toolInterface->getMemoryBlockCount;
    toolDeviceGetMemoryBlock        = toolInterface->getMemoryBlock;
    toolDeviceWriteMemory           = toolInterface->writeMemoryBlockSement;
    toolDeviceGetRegisterBankCount  = toolInterface->getRegisterBankCount;
    toolDeviceGetRegisterBank       = toolInterface->getRegisterBank;
    toolDeviceWriteRegister         = toolInterface->writeRegisterBankRegister;
    toolDeviceGetIoPortsCount       = toolInterface->getIoPortsCount;
    toolDeviceGetIoPorts            = toolInterface->getIoPorts;
    toolDeviceWriteIoPort           = toolInterface->writeIoPortsPort;
    toolDeviceRun                   = toolInterface->run;
    toolDeviceStop                  = toolInterface->stop;
    toolDevicePause                 = toolInterface->pause;
    toolDeviceStep                  = toolInterface->step;
    toolSetBreakpoint               = toolInterface->setBreakpoint;
    toolClearBreakpoint             = toolInterface->clearBreakpoint;

    OnCreateTool();

    return 1;
}

extern "C"__declspec(dllexport) void __stdcall Destroy()
{
    OnDestroyTool();
}

extern "C"__declspec(dllexport) void __stdcall Show()
{
    OnShowTool();
}

extern "C"__declspec(dllexport) void __stdcall NotifyEmulatorStart()
{
    OnEmulatorStart();
}

extern "C"__declspec(dllexport) void __stdcall NotifyEmulatorStop()
{
    OnEmulatorStop();
}

extern "C"__declspec(dllexport) void __stdcall NotifyEmulatorPause()
{
    OnEmulatorPause();
}

extern "C"__declspec(dllexport) void __stdcall NotifyEmulatorResume()
{
    OnEmulatorResume();
}
extern "C" int APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID /*lpvReserved*/)
{
    if(fdwReason == DLL_PROCESS_ATTACH) {
        hInstance = hinstDLL;
    }

    return TRUE;
}
