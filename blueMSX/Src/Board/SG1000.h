/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/SG1000.h,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-08-30 04:57:22 $
**
** More info: http://www.bluemsx.com
**
** Author: Ricardo Bittencourt
** Copyright (C) 2003-2004 Daniel Vik, Ricardo Bittencourt
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
#ifndef SG1000_H
#define SG1000_H
 
#include "MSXTypes.h"
#include "Board.h"
#include "Machine.h"
#include "audioMixer.h"
#include <stdio.h>

int sg1000Create(Machine* machine, 
                 DeviceInfo* deviceInfo,
                 int loadState);
void sg1000Destroy();

void sg1000Run();
void sg1000Stop();

void sg1000Reset();

void sg1000InitStatistics(Machine* machine);

void sg1000SaveState();

UInt32 sg1000SystemTime();

int  sg1000GetRefreshRate();

void sg1000SetInt(UInt32 irq);
void sg1000ClearInt(UInt32 irq);
UInt32 sg1000GetInt();

void sg1000SetCpuTimeout(UInt32 time);

void sg1000TraceEnable(const char* fileName);
void sg1000TraceDisable();
int  sg1000TraceGetEnable();

void sg1000SetBreakpoint(UInt16 address);
void sg1000ClearBreakpoint(UInt16 address);

UInt8* sg1000GetRamPage(int page);
UInt32 sg1000GetRamSize();
UInt32 sg1000GetVramSize();

int sg1000UseRom();
int sg1000UseMegaRom();
int sg1000UseMegaRam();
int sg1000UseFmPac();

void sg1000ChangeCartridge(int cartNo, RomType romType, char* cart, char* cartZip);
void sg1000ChangeDiskette(int driveId, char* fileName, const char* fileInZipFile);
int  sg1000ChangeCassette(char* name, const char* fileInZipFile);

#endif /* SG1000_H */

