#include "romMapperMatraINK.h"
#include "AmdFlash.h"
#include "MediaDb.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>


typedef struct {
    int deviceHandle;
    AmdFlash* flash;
    int slot;
    int sslot;
    int startPage;
} RomMapperMatraINK;

static void saveState(RomMapperMatraINK* rm)
{
    amdFlashSaveState(rm->flash);
}

static void loadState(RomMapperMatraINK* rm)
{ 
    amdFlashLoadState(rm->flash);
}

static void destroy(RomMapperMatraINK* rm)
{
    amdFlashDestroy(rm->flash);
    slotUnregister(rm->slot, rm->sslot, rm->startPage);
    deviceManagerUnregister(rm->deviceHandle);

    free(rm);
}


static UInt8 read(RomMapperMatraINK* rm, UInt16 address) 
{
    return amdFlashRead(rm->flash, address);
}

static UInt8 peek(RomMapperMatraINK* rm, UInt16 address) 
{
    return amdFlashRead(rm->flash, address);
}

static void write(RomMapperMatraINK* rm, UInt16 address, UInt8 value) 
{
    amdFlashWrite(rm->flash, address, value);
}

int romMapperMatraINKCreate(char* filename, UInt8* romData, 
                             int size, int slot, int sslot, int startPage) 
{
    DeviceCallbacks callbacks = { destroy, NULL, saveState, loadState };
    RomMapperMatraINK* rm;
    int i;

    rm = calloc(1, sizeof(RomMapperMatraINK));

    rm->deviceHandle = deviceManagerRegister(ROM_MEGAFLSHSCC, &callbacks, rm);
    slotRegister(slot, sslot, startPage, 8, read, peek, write, destroy, rm);

    rm->slot  = slot;
    rm->sslot = sslot;
    rm->startPage  = startPage;

    rm->flash = amdFlashCreate(AMD_TYPE_2, 0x10000, 0x10000, 0xff, romData, size, NULL, 0);

    for (i = 0; i < 8; i++) {
        slotMapPage(slot, sslot, startPage + i, NULL, 0, 0);
    }

    return 1;
}
