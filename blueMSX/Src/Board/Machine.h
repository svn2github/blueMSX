/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/Machine.h,v $
**
** $Revision: 1.3 $
**
** $Date: 2004-12-30 22:53:25 $
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
#ifndef MACHINE_H
#define MACHINE_H
 
#include "MSXTypes.h"
#include "RomMapper.h"
#include "VDP.h"
#include <stdio.h>


typedef enum { BOARD_MSX, BOARD_SVI, BOARD_COLECO } BoardType;

typedef struct {
    RomType romType;
    char name[512];
    char inZipName[128];
    int slot;
    int subslot;
    int startPage;
    int pageCount;
    int error;
} SlotInfo;

typedef struct {
    char name[64];
    struct {
        BoardType type;
    } board;
    struct {
        int subslotted;
    } slot[4];
    struct {
        int slot;
        int subslot;
    } cart[2];
    struct {
        VdpVersion vdpVersion;
        int vramSize;
    } video;
    struct {
        int enableAY8910;
        int enableSN76489;
        int enableYM2413;
        int enableY8950;
        int enableMoonsound;
        int enablePCM;
        int moonsoundSRAM;
    } audio;
    struct {
        int enable;
        int batteryBacked;
    } cmos;
    struct {
        int    hasR800;
        UInt32 freqZ80;
        UInt32 freqR800;
    } cpu;
    struct {
        int enabled;
        int count;
    } fdc;
    int slotInfoCount;
    SlotInfo slotInfo[32];
} Machine;


Machine* machineCreate(char* machineName);
void machineDestroy(Machine* machine);

char** machineGetAvailable(int checkRoms);

int machineIsValid(char* machineName, int checkRoms);

void machineUpdate(Machine* machine);

void machineSave(Machine* machine);

void machineLoadState(Machine* machine);
void machineSaveState(Machine* machine);

#endif

