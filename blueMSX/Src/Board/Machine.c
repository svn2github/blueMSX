/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/Machine.c,v $
**
** $Revision: 1.14 $
**
** $Date: 2005-09-24 00:50:00 $
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
#define USE_ARCH_GLOB
#include "Machine.h"
#include "SaveState.h"
#include "IniFileParser.h"
#ifdef USE_ARCH_GLOB
#include "ArchGlob.h"
#include <string.h>
#include <ctype.h>
#else
#include <windows.h>
#endif
#include <stdlib.h>
#include "ArchFile.h"

#include "TokenExtract.h"

int toint(char* buffer) 
{
    int i;

    if (buffer == NULL) {
        return -1;
    }

    for (i = 0; buffer[i]; i++) {
        if (!isdigit(buffer[i])) return -1;
    }

    return atoi(buffer);
}

static int readMachine(Machine* machine, const char* machineName, const char* file)
{
    static char buffer[10000];
    char* slotBuf;
    int value;
    int i = 0;

    strcpy(machine->name, machineName);

    iniFileOpen(file);

    // Read board info
    iniFileGetString("Board", "type", "none", buffer, 10000);
    if      (0 == strcmp(buffer, "MSX"))          machine->board.type = BOARD_MSX;
    else if (0 == strcmp(buffer, "SVI"))          machine->board.type = BOARD_SVI;
    else if (0 == strcmp(buffer, "ColecoVision")) machine->board.type = BOARD_COLECO;
    else if (0 == strcmp(buffer, "SG-1000"))      machine->board.type = BOARD_SG1000;
    else                                          machine->board.type = BOARD_MSX;

    // Read video info
    iniFileGetString("Video", "version", "none", buffer, 10000);
    if      (0 == strcmp(buffer, "V9938"))    machine->video.vdpVersion = VDP_V9938;
    else if (0 == strcmp(buffer, "V9958"))    machine->video.vdpVersion = VDP_V9958;
    else if (0 == strcmp(buffer, "TMS9929A")) machine->video.vdpVersion = VDP_TMS9929A;
    else if (0 == strcmp(buffer, "TMS99x8A")) machine->video.vdpVersion = VDP_TMS99x8A;
    else { iniFileClose(); return 0; }

    iniFileGetString("Video", "vram size", "none", buffer, 10000);
    if (0 == strcmp(buffer, "16kB")) machine->video.vramSize = 16 * 1024;
    else if (0 == strcmp(buffer, "64kB")) machine->video.vramSize = 64 * 1024;
    else if (0 == strcmp(buffer, "128kB")) machine->video.vramSize = 128 * 1024;
    else if (0 == strcmp(buffer, "192kB")) machine->video.vramSize = 192 * 1024;
    else { iniFileClose(); return 0; }

    // Read CMOS info
    iniFileGetString("CMOS", "Enable CMOS", "none", buffer, 10000);
    if (0 == strcmp(buffer, "none")) machine->cmos.enable = 1;
    else if (0 == strcmp(buffer, "0")) machine->cmos.enable = 0;
    else if (0 == strcmp(buffer, "1")) machine->cmos.enable = 1;
    else { iniFileClose(); return 0; }

    // Read CPU info
    iniFileGetString("CPU", "Z80 Frequency", "none", buffer, 10000);
    if (0 == sscanf(buffer, "%dHz", &value)) {
        value = 3579545;
    }
    machine->cpu.freqZ80 = value;

    // Read CPU info
    iniFileGetString("CPU", "R800 Frequency", "none", buffer, 10000);
    if (0 == sscanf(buffer, "%dHz", &value)) {
        value = 7159090;
    }
    machine->cpu.freqR800 = value;

    // Read FDC info
    iniFileGetString("FDC", "Count", "none", buffer, 10000);
    if (0 == strcmp(buffer, "none")) machine->fdc.count = 2;
    else if (0 == strcmp(buffer, "0")) machine->fdc.count = 0;
    else if (0 == strcmp(buffer, "1")) machine->fdc.count = 1;
    else if (0 == strcmp(buffer, "2")) machine->fdc.count = 2;
    else if (0 == strcmp(buffer, "3")) machine->fdc.count = 3;
    else if (0 == strcmp(buffer, "4")) machine->fdc.count = 4;
    else { iniFileClose(); return 0; }
    
    iniFileGetString("CMOS", "Battery Backed", "none", buffer, 10000);
    if (0 == strcmp(buffer, "none")) machine->cmos.batteryBacked = 1;
    else if (0 == strcmp(buffer, "0")) machine->cmos.batteryBacked = 0;
    else if (0 == strcmp(buffer, "1")) machine->cmos.batteryBacked = 1;
    else { iniFileClose(); return 0; }

    // Read subslot info
    iniFileGetString("Subslotted Slots", "slot 0", "none", buffer, 10000);
    if (0 == strcmp(buffer, "0")) machine->slot[0].subslotted = 0;
    else if (0 == strcmp(buffer, "1")) machine->slot[0].subslotted = 1;
    else { iniFileClose(); return 0; }
    
    iniFileGetString("Subslotted Slots", "slot 1", "none", buffer, 10000);
    if (0 == strcmp(buffer, "0")) machine->slot[1].subslotted = 0;
    else if (0 == strcmp(buffer, "1")) machine->slot[1].subslotted = 1;
    else { iniFileClose(); return 0; }
    
    iniFileGetString("Subslotted Slots", "slot 2", "none", buffer, 10000);
    if (0 == strcmp(buffer, "0")) machine->slot[2].subslotted = 0;
    else if (0 == strcmp(buffer, "1")) machine->slot[2].subslotted = 1;
    else { iniFileClose(); return 0; }
    
    iniFileGetString("Subslotted Slots", "slot 3", "none", buffer, 10000);
    if (0 == strcmp(buffer, "0")) machine->slot[3].subslotted = 0;
    else if (0 == strcmp(buffer, "1")) machine->slot[3].subslotted = 1;
    else { iniFileClose(); return 0; }

    // Read external slot info
    iniFileGetString("External Slots", "slot A", "none", buffer, 10000);
    machine->cart[0].slot = toint(extractToken(buffer, 0));        
    machine->cart[0].subslot = toint(extractToken(buffer, 1));    
    if (machine->cart[0].slot < 0 || machine->cart[0].slot >= 4) { iniFileClose(); return 0; }
    if (machine->cart[0].subslot < 0 || machine->cart[0].subslot >= 4) { iniFileClose(); return 0; }  

    iniFileGetString("External Slots", "slot B", "none", buffer, 10000);
    machine->cart[1].slot = toint(extractToken(buffer, 0));        
    machine->cart[1].subslot = toint(extractToken(buffer, 1));    
    if (machine->cart[1].slot < 0 || machine->cart[1].slot >= 4) { iniFileClose(); return 0; }
    if (machine->cart[1].subslot < 0 || machine->cart[1].subslot >= 4) { iniFileClose(); return 0; }   

    // Read slots
    iniFileGetSection("Slots", buffer, 10000);

    slotBuf = buffer;
    machine->cpu.hasR800 = 0;
    machine->fdc.enabled = 0;
    for (i = 0; i < sizeof(machine->slotInfo) / sizeof(SlotInfo) && *slotBuf; i++) {
        char* arg;

        machine->slotInfo[i].slot = toint(extractToken(slotBuf, 0));    
        machine->slotInfo[i].subslot = toint(extractToken(slotBuf, 1));
        machine->slotInfo[i].startPage = toint(extractToken(slotBuf, 2));
        machine->slotInfo[i].pageCount = toint(extractToken(slotBuf, 3));
        machine->slotInfo[i].romType = toint(extractToken(slotBuf, 4));
        machine->cpu.hasR800 |= machine->slotInfo[i].romType == ROM_S1990;
        machine->fdc.enabled |= machine->slotInfo[i].romType == ROM_DISKPATCH   ||
                                machine->slotInfo[i].romType == ROM_TC8566AF    ||
                                machine->slotInfo[i].romType == ROM_MICROSOL    ||
                                machine->slotInfo[i].romType == ROM_NATIONALFDC ||
                                machine->slotInfo[i].romType == ROM_PHILIPSFDC  ||
                                machine->slotInfo[i].romType == ROM_SVI328FDC   ||
                                machine->slotInfo[i].romType == ROM_SVI738FDC;
        arg = extractToken(slotBuf, 5);
        strcpy(machine->slotInfo[i].name, arg ? arg : "");
        arg = extractToken(slotBuf, 6);
        strcpy(machine->slotInfo[i].inZipName, arg ? arg : "");

        if (machine->slotInfo[i].slot < 0 || machine->slotInfo[i].slot >= 4) { iniFileClose(); return 0; }
        if (machine->slotInfo[i].subslot < 0 || machine->slotInfo[i].subslot >= 4) { iniFileClose(); return 0; }
        if (machine->slotInfo[i].startPage < 0 || machine->slotInfo[i].startPage >= 8) { iniFileClose(); return 0; }
        if (machine->slotInfo[i].pageCount == -1) { iniFileClose(); return 0; }
        if (machine->slotInfo[i].romType < 1 || machine->slotInfo[i].romType > ROM_MAXROMID) { iniFileClose(); return 0; }

        slotBuf += strlen(slotBuf) + 1;
    }

    machine->slotInfoCount = i;
 
    iniFileClose();

    return 1;
}

void machineSave(Machine* machine)
{
    char dir[512];
    char file[512];
    char buffer[10000];
    int size = 0;
    int i;

    sprintf(dir, "Machines/%s", machine->name);
    archCreateDirectory(dir);

    sprintf(file, "Machines/%s/config.ini", machine->name);

    iniFileOpen(file);

    // Write CMOS info
    iniFileWriteString("CMOS", "Enable CMOS", machine->cmos.enable ? "1" : "0");
    iniFileWriteString("CMOS", "Battery Backed", machine->cmos.batteryBacked ? "1" : "0");

    // Write FDC info
    sprintf(buffer, "%d", machine->fdc.count);
    iniFileWriteString("FDC", "Count", buffer);

    // Write CPU info
    sprintf(buffer, "%dHz", machine->cpu.freqZ80);
    iniFileWriteString("CPU", "Z80 Frequency", buffer);
    if (machine->cpu.hasR800) {
        sprintf(buffer, "%dHz", machine->cpu.freqR800);
        iniFileWriteString("CPU", "R800 Frequency", buffer);
    }

    // Write Board info
    switch (machine->board.type) {
    case BOARD_MSX:     iniFileWriteString("Board", "type", "MSX"); break;
    case BOARD_SVI:     iniFileWriteString("Board", "type", "SVI"); break;
    case BOARD_COLECO:  iniFileWriteString("Board", "type", "ColecoVision"); break;
    case BOARD_SG1000:  iniFileWriteString("Board", "type", "SG-1000"); break;
    }

    // Write video info
    switch (machine->video.vdpVersion) {
        case VDP_V9958:     iniFileWriteString("Video", "version", "V9958"); break;
        case VDP_V9938:     iniFileWriteString("Video", "version", "V9938"); break;
        case VDP_TMS9929A:  iniFileWriteString("Video", "version", "TMS9929A"); break;
        case VDP_TMS99x8A:  iniFileWriteString("Video", "version", "TMS99x8A"); break;
    }

    sprintf(buffer, "%dkB", machine->video.vramSize / 0x400);
    iniFileWriteString("Video", "vram size", buffer);

    // Write subslot info
    iniFileWriteString("Subslotted Slots", "slot 0", machine->slot[0].subslotted ? "1" : "0");
    iniFileWriteString("Subslotted Slots", "slot 1", machine->slot[1].subslotted ? "1" : "0");
    iniFileWriteString("Subslotted Slots", "slot 2", machine->slot[2].subslotted ? "1" : "0");
    iniFileWriteString("Subslotted Slots", "slot 3", machine->slot[3].subslotted ? "1" : "0");

    // Write external slot info
    sprintf(buffer, "%d %d", machine->cart[0].slot, machine->cart[0].subslot);
    iniFileWriteString("External Slots", "slot A", buffer);
    sprintf(buffer, "%d %d", machine->cart[1].slot, machine->cart[1].subslot);
    iniFileWriteString("External Slots", "slot B", buffer);

    // Write slots
    for (i = 0; i < machine->slotInfoCount; i++) {
        size += sprintf(buffer + size, "%d %d %d %d %d \"%s\" \"%s\"",
                        machine->slotInfo[i].slot,
                        machine->slotInfo[i].subslot,
                        machine->slotInfo[i].startPage,
                        machine->slotInfo[i].pageCount,
                        machine->slotInfo[i].romType,
                        machine->slotInfo[i].name,
                        machine->slotInfo[i].inZipName);
        buffer[size++] = 0;
    }

    buffer[size++] = 0;
    buffer[size++] = 0;

//    iniFileWriteString("Slots", NULL, NULL);
    iniFileWriteSection("Slots", buffer);

    iniFileClose();
}

Machine* machineCreate(const char* machineName)
{
    char fileName[512];
    Machine* machine;
    int success;

    machine = malloc(sizeof(Machine));

    sprintf(fileName, "Machines/%s/config.ini", machineName);
    success = readMachine(machine, machineName, fileName);
    if (!success) {
        free(machine);
        return NULL;
    }

    machineUpdate(machine);

    return machine;
}

void machineDestroy(Machine* machine)
{
    free(machine);
}


int machineIsValid(const char* machineName, int checkRoms)
{
    Machine* machine = machineCreate(machineName);
    int i;
    int success = 1;

    if (machine == NULL) {
        return 0;
    }

    if (!checkRoms) {
        return 1;
    }

    for (i = 0; i < machine->slotInfoCount; i++) {
        if (strlen(machine->slotInfo[i].name) || 
            strlen(machine->slotInfo[i].inZipName))
        {        
            FILE* file = fopen(machine->slotInfo[i].name, "r");
            if (file == NULL) {
                if (success) {
//                    printf("\n%s: Cant find rom:\n", machineName);
                }
//                printf("     %s\n", machine->slotInfo[i].name);
                success = 0;
                continue;
            }
            fclose(file);
        }
    }

    free(machine);

    return success;
}

#ifdef USE_ARCH_GLOB
char** machineGetAvailable(int checkRoms)
{
    static char* machineNames[256];
    static char  names[256][64];
    ArchGlob* glob = archGlob("Machines/*", ARCH_GLOB_DIRS);
    int index = 0;
    int i;

    if (glob == NULL) {
        machineNames[0] = NULL;
        return machineNames;
    }

    for (i = 0; i < glob->count; i++) {
        char fileName[512];
        FILE* file;
		sprintf(fileName, "%s/config.ini", glob->pathVector[i]);
        file = fopen(fileName, "rb");
        if (file != NULL) {
            const char* name = strrchr(glob->pathVector[i], '/');
            if (name == NULL) {
                name = strrchr(glob->pathVector[i], '\\');
            }
            if (name == NULL) {
                name = glob->pathVector[i] - 1;
            }
            name++;
            if (machineIsValid(name, checkRoms)) {
                strcpy(names[index], name);
                machineNames[index] = names[index];
                index++;
            }
            fclose(file);
        }
    }

    archGlobFree(glob);
    
    machineNames[index] = NULL;

    return machineNames;
}
#else

char** machineGetAvailable(int checkRoms)
{
    static char* machineNames[256];
    static char  names[256][64];
	HANDLE          handle;
	WIN32_FIND_DATA wfd;
    int index = 0;
    BOOL cont = TRUE;

    handle = FindFirstFile("Machines/*", &wfd);

    if (handle == INVALID_HANDLE_VALUE) {
        machineNames[0] = NULL;
        return machineNames;
    }

    while (cont) {
        char fileName[512];

		DWORD fa = GetFileAttributes(wfd.cFileName);
        if (fa & FILE_ATTRIBUTE_DIRECTORY) {
            FILE* file;
		    sprintf(fileName, "Machines/%s/config.ini", wfd.cFileName);
            file = fopen(fileName, "rb");
            if (file != NULL) {
                if (machineIsValid(wfd.cFileName, checkRoms)) {
                    strcpy(names[index], wfd.cFileName);
                    machineNames[index] = names[index];
                    index++;
                }
                fclose(file);
            }
            
        }
        cont = FindNextFile(handle, &wfd);
    }

	FindClose(handle);
    
    machineNames[index] = NULL;

    return machineNames;
}
#endif

void machineUpdate(Machine* machine)
{
    int entry;
    int i;

    for (entry = 0; entry < machine->slotInfoCount; entry++) {
        machine->slotInfo[entry].error = 0;
        if (machine->slotInfo[entry].subslot && !machine->slot[machine->slotInfo[entry].slot].subslotted) {
            machine->slotInfo[entry].error = 1;
        }
        if (machine->slotInfo[entry].pageCount > 0) {
            for (i = 0; i < entry; i++) {
                if (machine->slotInfo[i].slot    == machine->slotInfo[entry].slot &&
                    machine->slotInfo[i].subslot == machine->slotInfo[entry].subslot &&
                    machine->slotInfo[i].pageCount > 0)
                {
                    int tstStart = machine->slotInfo[entry].startPage;
                    int tstEnd   = tstStart + machine->slotInfo[entry].pageCount;
                    int start    = machine->slotInfo[i].startPage;
                    int end      = start + machine->slotInfo[i].pageCount;
                    if (tstStart >= start && tstStart < end) {
                        machine->slotInfo[entry].error = 1;
                    }
                    if (tstEnd > start && tstEnd <= end) {
                        machine->slotInfo[entry].error = 1;
                    }
                }
            }
        }
    }

    for (i = 0; i < machine->slotInfoCount; i++) {
        for (entry = 0; entry < machine->slotInfoCount - 1; entry++) {
            SlotInfo* si1 = &machine->slotInfo[entry];
            SlotInfo* si2 = &machine->slotInfo[entry + 1];
            int tst1 = (si1->slot << 24) + (si1->subslot << 20) + 
                       (si1->startPage << 12) + si1->pageCount;
            int tst2 = (si2->slot << 24) + (si2->subslot << 20) + 
                       (si2->startPage << 12) + si2->pageCount;

            if (tst2 < tst1) {
                SlotInfo tmp;
                memcpy(&tmp, si1, sizeof(SlotInfo));
                memcpy(si1, si2, sizeof(SlotInfo));
                memcpy(si2, &tmp, sizeof(SlotInfo));
            }
        }
    }

    // Check R800 and FDC enable
    machine->cpu.hasR800 = 0;
    machine->fdc.enabled = 0;
    for (i = 0; i < machine->slotInfoCount; i++) {
        machine->cpu.hasR800 |= machine->slotInfo[i].romType == ROM_S1990;
        machine->fdc.enabled |= machine->slotInfo[i].romType == ROM_DISKPATCH     ||
                                machine->slotInfo[i].romType == ROM_TC8566AF      ||
                                machine->slotInfo[i].romType == ROM_MICROSOL      ||
                                machine->slotInfo[i].romType == ROM_NATIONALFDC   ||
                                machine->slotInfo[i].romType == ROM_PHILIPSFDC    ||
                                machine->slotInfo[i].romType == ROM_SVI328FDC     ||
                                machine->slotInfo[i].romType == ROM_SVI738FDC;
    }

    // Check VRAM size
    if (machine->video.vdpVersion == VDP_V9938) {
        if (machine->video.vramSize >= 128 * 1024) {
            machine->video.vramSize = 128 * 1024;
        }
        else if (machine->video.vramSize >= 64 * 1024) {
            machine->video.vramSize = 64 * 1024;
        }
        else if (machine->video.vramSize >= 32 * 1024) {
            machine->video.vramSize = 32 * 1024;
        }
        else {
            machine->video.vramSize = 16 * 1024;
        }
    }
    else if (machine->video.vdpVersion == VDP_V9958) {
        if (machine->video.vramSize >= 192 * 1024) {
            machine->video.vramSize = 192 * 1024;
        }
        else {
            machine->video.vramSize = 128 * 1024;
        }
    }
    else {
        machine->video.vramSize = 16 * 1024;
    }
}


void machineLoadState(Machine* machine)
{
    SaveState* state = saveStateOpenForRead("machine");
    int hasR800 = 0;
    int i;

    saveStateGetBuffer(state, "name", machine->name, sizeof(machine->name));

    machine->board.type = saveStateGet(state, "boardType", BOARD_MSX);

    machine->slot[0].subslotted    = saveStateGet(state, "subslotted00",      0);
    machine->slot[1].subslotted    = saveStateGet(state, "subslotted01",      0);
    machine->slot[2].subslotted    = saveStateGet(state, "subslotted02",      0);
    machine->slot[3].subslotted    = saveStateGet(state, "subslotted03",      0);

    machine->cart[0].slot          = saveStateGet(state, "cartSlot00",        0);
    machine->cart[0].subslot       = saveStateGet(state, "cartSubslot00",     0);
    machine->cart[1].slot          = saveStateGet(state, "cartSlot01",        0);
    machine->cart[1].subslot       = saveStateGet(state, "cartSubslot01",     0);
    
    machine->video.vdpVersion      = saveStateGet(state, "videoVersion",      0);
    machine->video.vramSize        = saveStateGet(state, "videoVramSize",     0x10000);
    
    machine->cmos.enable           = saveStateGet(state, "cmosEnable",        0);
    machine->cmos.batteryBacked    = saveStateGet(state, "cmosBatteryBacked", 0);
    
    machine->fdc.count             = saveStateGet(state, "fdcCount",          2);
    machine->cpu.freqZ80           = saveStateGet(state, "cpuFreqZ80",        3579545);
    machine->cpu.freqR800          = saveStateGet(state, "cpuFreqR800",       7159090);
    
    machine->slotInfoCount         = saveStateGet(state, "slotInfoCount",     0);

    for (i = 0; i < sizeof(machine->slotInfo) / sizeof(machine->slotInfo[0]); i++) {
        char tag[32];
        
        sprintf(tag, "slotRomType%.2d", i);
        machine->slotInfo[i].romType = saveStateGet(state, tag, 0);
        
        hasR800 |= machine->slotInfo[i].romType == ROM_S1990;

        sprintf(tag, "slot%.2d", i);
        machine->slotInfo[i].slot = saveStateGet(state, tag, 0);
        
        sprintf(tag, "subslot%.2d", i);
        machine->slotInfo[i].subslot = saveStateGet(state, tag, 0);
        
        sprintf(tag, "slotStartPage%.2d", i);
        machine->slotInfo[i].startPage = saveStateGet(state, tag, 0);
        
        sprintf(tag, "slotPageCount%.2d", i);
        machine->slotInfo[i].pageCount = saveStateGet(state, tag, 0);
        
        sprintf(tag, "slotError%.2d", i);
        machine->slotInfo[i].error = saveStateGet(state, tag, 0);
        
        sprintf(tag, "slotName%.2d", i);
        saveStateGetBuffer(state, tag, machine->slotInfo[i].name, 512);
        
        sprintf(tag, "slotInZipName%.2d", i);
        saveStateGetBuffer(state, tag, machine->slotInfo[i].inZipName, 128);
    }
    
    machine->cpu.hasR800 = hasR800;

    saveStateClose(state);

    machineUpdate(machine);
}

void machineSaveState(Machine* machine)
{
    SaveState* state = saveStateOpenForWrite("machine");
    int i;

    saveStateSetBuffer(state, "name", machine->name, sizeof(machine->name));

    saveStateSet(state, "boardType",         machine->board.type);

    saveStateSet(state, "subslotted00",      machine->slot[0].subslotted);
    saveStateSet(state, "subslotted01",      machine->slot[1].subslotted);
    saveStateSet(state, "subslotted02",      machine->slot[2].subslotted);
    saveStateSet(state, "subslotted03",      machine->slot[3].subslotted);

    saveStateSet(state, "cartSlot00",        machine->cart[0].slot);
    saveStateSet(state, "cartSubslot00",     machine->cart[0].subslot);
    saveStateSet(state, "cartSlot01",        machine->cart[1].slot);
    saveStateSet(state, "cartSubslot01",     machine->cart[1].subslot);
    
    saveStateSet(state, "videoVersion",      machine->video.vdpVersion);
    saveStateSet(state, "videoVramSize",     machine->video.vramSize);
    

    saveStateSet(state, "cmosEnable",        machine->cmos.enable);
    saveStateSet(state, "cmosBatteryBacked", machine->cmos.batteryBacked);
    
    saveStateSet(state, "fdcCount",          machine->fdc.count);
    saveStateSet(state, "cpuFreqZ80",        machine->cpu.freqZ80);
    saveStateSet(state, "cpuFreqR800",       machine->cpu.freqR800);
    
    saveStateSet(state, "slotInfoCount",     machine->slotInfoCount);

    for (i = 0; i < sizeof(machine->slotInfo) / sizeof(machine->slotInfo[0]); i++) {
        char tag[32];
        
        sprintf(tag, "slotRomType%.2d", i);
        saveStateSet(state, tag, machine->slotInfo[i].romType);
        
        sprintf(tag, "slot%.2d", i);
        saveStateSet(state, tag, machine->slotInfo[i].slot);
        
        sprintf(tag, "subslot%.2d", i);
        saveStateSet(state, tag, machine->slotInfo[i].subslot);
        
        sprintf(tag, "slotStartPage%.2d", i);
        saveStateSet(state, tag, machine->slotInfo[i].startPage);
        
        sprintf(tag, "slotPageCount%.2d", i);
        saveStateSet(state, tag, machine->slotInfo[i].pageCount);
        
        sprintf(tag, "slotError%.2d", i);
        saveStateSet(state, tag, machine->slotInfo[i].error);
        
        sprintf(tag, "slotName%.2d", i);
        saveStateSetBuffer(state, tag, machine->slotInfo[i].name, 512);
        
        sprintf(tag, "slotInZipName%.2d", i);
        saveStateSetBuffer(state, tag, machine->slotInfo[i].inZipName, 128);
    }

    saveStateClose(state);
}
