/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/Coleco.h,v $
**
** $Revision: 1.6 $
**
** $Date: 2005-02-22 03:39:10 $
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
#ifndef COLECO_H
#define COLECO_H
 
#include "MSXTypes.h"
#include "Board.h"
#include "Machine.h"
#include "audioMixer.h"
#include <stdio.h>

int colecoCreate(Machine* machine, 
                 DeviceInfo* deviceInfo,
                 int loadState);
void colecoDestroy();

void colecoRun();
void colecoStop();

void colecoReset();

void colecoInitStatistics(Machine* machine);

void colecoSaveState();

UInt32 colecoSystemTime();

int  colecoGetRefreshRate();

void colecoSetInt(UInt32 irq);
void colecoClearInt(UInt32 irq);
UInt32 colecoGetInt();

void colecoSetCpuTimeout(UInt32 time);

void colecoTraceEnable(const char* fileName);
void colecoTraceDisable();
int  colecoTraceGetEnable();

void colecoSetBreakpoint(UInt16 address);
void colecoClearBreakpoint(UInt16 address);

UInt8* colecoGetRamPage(int page);
UInt32 colecoGetRamSize();
UInt32 colecoGetVramSize();

int colecoUseRom();
int colecoUseMegaRom();
int colecoUseMegaRam();
int colecoUseFmPac();

void colecoChangeCartridge(int cartNo, RomType romType, char* cart, char* cartZip);
void colecoChangeDiskette(int driveId, char* fileName, const char* fileInZipFile);
int  colecoChangeCassette(char* name, const char* fileInZipFile);

#endif /* SVI_H */

