/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Board/MSX.c,v $
**
** $Revision: 1.32 $
**
** $Date: 2005-02-28 00:53:35 $
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

#include "MSX.h"

#include "R800.h"
#include "R800Dasm.h"
#include "R800SaveState.h"

#include "SaveState.h"
#include "MsxPPI.h"
#include "Board.h"
#include "RTC.h"
#include "Led.h"
#include "Switches.h"
#include "sramLoader.h"
#include "JoystickIO.h"
#include "AudioMixer.h"
#include "AY8910.h"
#include "KeyClick.h"
#include "audioMixer.h"
#include "Keyboard.h"
#include "MediaDb.h"
#include "VDP.h"
#include "V9938.h"
#include "VideoManager.h"
#include "MediaDb.h"
#include "Casette.h"
#include "Disk.h"
#include "MegaromCartridge.h"
#include "IoPort.h"
#include "SlotManager.h"
#include "DeviceManager.h"
#include "DebugDeviceManager.h"
#include "RomLoader.h"
#include "ramMapper.h"
#include "ramMapperIo.h"
#include "ramNormal.h"
#include "romMapperNormal.h"
#include "romMapperKanji.h"
#include "romMapperKanji12.h"
#include "romMapperBasic.h"
#include "romMapperCasette.h"
#include "romMapperStandard.h"
#include "romMapperMsxDos2.h"
#include "romMapperKonami5.h"
#include "romMapperKonami4.h"
#include "romMapperKoei.h"
#include "romMapperHolyQuran.h"
#include "romMapperMegaRam.h"
#include "romMapperASCII8.h"
#include "romMapperASCII16.h"
#include "romMapperDisk.h"
#include "romMapperTC8566AF.h"
#include "romMapperMicrosol.h"
#include "romMapperNationalFdc.h"
#include "romMapperPhilipsFdc.h"
#include "romMapperSvi738Fdc.h"
#include "romMapperGameMaster2.h"
#include "romMapperASCII8sram.h"
#include "romMapperASCII16sram.h"
#include "romMapperASCII16nf.h"
#include "romMapperKonami4nf.h"
#include "romMapperPlain.h"
#include "romMapperHarryFox.h"
#include "romMapperHalnote.h"
#include "romMapperMsxAudio.h"
#include "romMapperRType.h"
#include "romMapperCrossBlaim.h"
#include "romMapperKorean80.h"
#include "romMapperKorean90.h"
#include "romMapperKorean126.h"
#include "romMapperPAC.h"
#include "romMapperFMPAC.h"
#include "romMapperLodeRunner.h"
#include "romMapperSCCplus.h"
#include "romMapperPanasonic.h"
#include "romMapperNational.h"
#include "sramMapperMatsuchita.h"
#include "romMapperKonamiSynth.h"
#include "romMapperMajutsushi.h"
#include "sramMapperS1985.h"
#include "romMapperS1990.h"
#include "romMapperF4device.h"
#include "romMapperBunsetu.h"
#include "romMapperTurboRTimer.h"
#include "romMapperTurboRPCM.h"
#include "romMapperSonyHBI55.h"
#include "romMapperMsxMusic.h"
#include "romMapperMsxPrn.h"
#include "romMapperMoonsound.h"

void PatchZ80(void* ref, CpuRegs* cpuRegs);

void msxLoadState();

// Hardware
static Machine*        msxMachine;
static DeviceInfo*     msxDevInfo;
static AY8910*         ay8910;
static R800*           r800;
static RTC*            rtc;
static JoystickIO*     joyIO;
static UInt8*          msxRam;
static UInt32          msxRamSize;
static UInt32          msxVramSize;
static int             useRom;
static int             useMegaRom;
static int             useMegaRam;
static int             useFmPac;
static RomType         currentRomType[2];
static int			   pendingInt;
static UInt32          z80Frequency;
static int             traceEnabled;
static int             debugHandle;

void msxTraceEnable(const char* fileName) {
    traceEnabled = r800OpenTrace(fileName);
}

void msxTraceDisable() {
    r800CloseTrace();
    traceEnabled = 0;
}

int msxTraceGetEnable() {
    return traceEnabled;
}

void msxSetBreakpoint(UInt16 address) {
    if (r800) {
        r800SetBreakpoint(r800, address);
    }
}
void msxClearBreakpoint(UInt16 address) {
    if (r800) {
        r800ClearBreakpoint(r800, address);
    }
}

UInt32 msxGetRamSize()
{ 
    return msxRamSize / 1024;
}

UInt32 msxGetVramSize()
{
    return msxVramSize / 1024;
}

int msxUseRom()
{
    return useRom;
}

int msxUseMegaRom()
{
    return useMegaRom;
}

int msxUseMegaRam()
{
    return useMegaRam;
}

int msxUseFmPac()
{
    return useFmPac;
}

UInt32 msxSystemTime() 
{
    if (r800) {
        return r800GetSystemTime(r800);
    }
    return 0;
}

void msxSetCpu(int mode)
{
    switch (mode) {
    default:
    case 0:
        r800SetMode(r800, CPU_Z80);
        break;
    case 1:
        r800SetMode(r800, CPU_R800);
        break;
    }
}

void msxEnableCpuFreq_1_5(int enable) {
    if (enable) {
        r800SetFrequency(r800, CPU_Z80, 3 * z80Frequency / 2);
    }
    else {
        r800SetFrequency(r800, CPU_Z80, z80Frequency);
    }
}

void msxSetInt(UInt32 irq)
{
	pendingInt |= irq;
    r800SetInt(r800);
}


UInt32 msxGetInt(UInt32 irq)
{
    return pendingInt & irq;
}

void msxClearInt(UInt32 irq)
{
	pendingInt &= ~irq;
	if (pendingInt == 0) {
        r800ClearInt(r800);
	}
}

static void writeMisc(void* ref, UInt16 ioPort, UInt8 value)
{
    switch (ioPort & 0xff) {
    case 0xa7:
		ledSetPause(value & 0x01);
		ledSetTurboR(value & 0x80);
		break;
	}
}

static UInt8 readMisc(void* ref, UInt16 ioPort)
{
    switch (ioPort & 0xff) {
    case 0x04: 
        return 2;

    case 0x05: 
        return 0;

    case 0x90:
        return 0xfd;

    case 0xa7:
        return switchGetPause() ? 1 : 0;

    case 0xe8:
    case 0xe9:
    case 0xea:
    case 0xeb:
    case 0xec:
    case 0xed:
    case 0xee:
    case 0xef:
        return 0;
    }

    return 0xff;
}

void msxInitStatistics(Machine* machine)
{
    int i;

    msxVramSize = machine->video.vramSize;

    for (i = 0; i < machine->slotInfoCount; i++) {
        if (machine->slotInfo[i].romType == RAM_NORMAL || machine->slotInfo[i].romType == RAM_MAPPER) {
            msxRamSize = 0x2000 * machine->slotInfo[i].pageCount;
        }
    }
}


static int initMachine(Machine* machine, 
                       VdpSyncMode vdpSyncMode)
{
    char cmosName[128];
    void* jisyoRom = NULL;
    int jisyoRomSize = 0;
    int success = 1;
    UInt8* buf;
    int size;
    int i;

    sprintf(cmosName, "%s\\%s.cmos", boardGetBaseDirectory(), machine->name);
    rtc = rtcCreate(machine->cmos.enable, machine->cmos.batteryBacked ? cmosName : 0);

    msxRam = NULL;

    msxVramSize = machine->video.vramSize;

    vdpCreate(VDP_MSX, machine->video.vdpVersion, vdpSyncMode, machine->video.vramSize / 0x4000);

    for (i = 0; i < 4; i++) {
        slotSetSubslotted(i, machine->slot[i].subslotted);
    }

    /* Map megarom cartridges */
    for (i = 0; i < 2; i++) {
        cartridgeSetSlotInfo(i, machine->cart[i].slot, machine->cart[i].subslot);
    }

    /* Initialize RAM */
    for (i = 0; i < machine->slotInfoCount; i++) {
        int slot;
        int subslot;
        int startPage;
        char* romName;
        
        // Don't map slots with error
        if (machine->slotInfo[i].error) {
            continue;
        }

        romName   = strlen(machine->slotInfo[i].inZipName) ? machine->slotInfo[i].inZipName : machine->slotInfo[i].name;
        slot      = machine->slotInfo[i].slot;
        subslot   = machine->slotInfo[i].subslot;
        startPage = machine->slotInfo[i].startPage;
        size      = 0x2000 * machine->slotInfo[i].pageCount;

        if (machine->slotInfo[i].romType == RAM_NORMAL) {
            success &= ramNormalCreate(size, slot, subslot, startPage, &msxRam, &msxRamSize);
            continue;
        }

        if (machine->slotInfo[i].romType == RAM_MAPPER) {
            success &= ramMapperCreate(size, slot, subslot, startPage, &msxRam, &msxRamSize);
            continue;
        }
    }

    if (msxRam == NULL) {
        return 0;
    }

    for (i = 0; i < machine->slotInfoCount; i++) {
        int slot;
        int subslot;
        int startPage;
        char* romName;
        
        // Don't map slots with error
        if (machine->slotInfo[i].error) {
            continue;
        }

        romName   = strlen(machine->slotInfo[i].inZipName) ? machine->slotInfo[i].inZipName : machine->slotInfo[i].name;
        slot      = machine->slotInfo[i].slot;
        subslot   = machine->slotInfo[i].subslot;
        startPage = machine->slotInfo[i].startPage;
        size      = 0x2000 * machine->slotInfo[i].pageCount;
        
        if (machine->slotInfo[i].romType == RAM_NORMAL) {
            continue;
        }
        
        if (machine->slotInfo[i].romType == RAM_MAPPER) {
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_SNATCHER) {
            success &= romMapperSCCplusCreate(NULL, NULL, 0, slot, subslot, startPage, SCC_SNATCHER);
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_SDSNATCHER) {
            success &= romMapperSCCplusCreate(NULL, NULL, 0, slot, subslot, startPage, SCC_SDSNATCHER);
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_SCCMIRRORED) {
            success &= romMapperSCCplusCreate(NULL, NULL, 0, slot, subslot, startPage, SCC_MIRRORED);
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_SCCEXTENDED) {
            success &= romMapperSCCplusCreate(NULL, NULL, 0, slot, subslot, startPage, SCC_EXTENDED);
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_PAC) {
            success &= romMapperPACCreate("Pac.rom", NULL, 0, slot, subslot, startPage);
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_EXTRAM) {
            success &= ramMapperCreate(size, slot, subslot, startPage, NULL, NULL);
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_MEGARAM) {
            success &= romMapperMegaRAMCreate(size, slot, subslot, startPage);
            continue;
        }

        if (machine->slotInfo[i].romType == SRAM_MATSUCHITA) {
            success &= sramMapperMatsushitaCreate();
            continue;
        }

        if (machine->slotInfo[i].romType == SRAM_S1985) {
            success &= sramMapperS1985Create();
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_S1990) {
            success &= romMapperS1990Create();
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_TURBORTIMER) {
            success &= romMapperTurboRTimerCreate(0);
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_F4DEVICE) {
            success &= romMapperF4deviceCreate(0);
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_F4INVERTED) {
            success &= romMapperF4deviceCreate(1);
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_SONYHBI55) {
            success &= romMapperSonyHBI55Create();
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_MSXAUDIODEV) {
            success &= romMapperMsxAudioCreate(NULL, NULL, 0, 0, 0, 0);
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_TURBORPCM) {
            success &= romMapperTurboRPcmCreate();
            continue;
        }

        if (machine->slotInfo[i].romType == ROM_MSXPRN) {
            success &= romMapperMsxPrnCreate();
            continue;
        }
        
        buf = romLoad(machine->slotInfo[i].name, machine->slotInfo[i].inZipName, &size);

        if (buf == NULL) {
            success = 0;
            continue;
        }

        switch (machine->slotInfo[i].romType) {
        case ROM_0x4000:
            success &= romMapperNormalCreate(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_BASIC:
            success &= romMapperBasicCreate(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_PLAIN:
            success &= romMapperPlainCreate(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_STANDARD:
            success &= romMapperStandardCreate(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_MSXDOS2:
            success &= romMapperMsxDos2Create(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_KONAMI5:
            success &= romMapperKonami5Create(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_MOONSOUND:
            success &= romMapperMoonsoundCreate(romName, buf, size, 640);
            break;

        case ROM_SCC:
            success &= romMapperSCCplusCreate(romName, buf, size, slot, subslot, startPage, SCC_EXTENDED);
            break;

        case ROM_SCCPLUS:
            success &= romMapperSCCplusCreate(romName, buf, size, slot, subslot, startPage, SCCP_EXTENDED);
            break;
            
        case ROM_KONAMI4:
            success &= romMapperKonami4Create(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_MAJUTSUSHI:
            success &= romMapperMajutsushiCreate(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_HOLYQURAN:
            success &= romMapperHolyQuranCreate(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_KONAMISYNTH:
            success &= romMapperKonamiSynthCreate(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_ASCII8:
            success &= romMapperASCII8Create(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_ASCII16:
            success &= romMapperASCII16Create(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_PANASONIC16:
            success &= romMapperPanasonicCreate(romName, buf, size, slot, subslot, startPage, 0x4000);
            break;

        case ROM_PANASONIC32:
            success &= romMapperPanasonicCreate(romName, buf, size, slot, subslot, startPage, 0x8000);
            break;
            
        case ROM_ASCII8SRAM:
            success &= romMapperASCII8sramCreate(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_ASCII16SRAM:
            success &= romMapperASCII16sramCreate(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_MSXAUDIO:
            success &= romMapperMsxAudioCreate(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_KOEI:
            success &= romMapperKoeiCreate(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_NATIONAL:
            success &= romMapperNationalCreate(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_KONAMI4NF:
            success &= romMapperKonami4nfCreate(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_ASCII16NF:
            success &= romMapperASCII16nfCreate(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_GAMEMASTER2:
            success &= romMapperGameMaster2Create(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_HARRYFOX:
            success &= romMapperHarryFoxCreate(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_HALNOTE:
            success &= romMapperHalnoteCreate(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_RTYPE:
            success &= romMapperRTypeCreate(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_CROSSBLAIM:
            success &= romMapperCrossBlaimCreate(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_LODERUNNER:
            success &= romMapperLodeRunnerCreate(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_KOREAN80:
            success &= romMapperKorean80Create(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_KOREAN90:
            success &= romMapperKorean90Create(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_KOREAN126:
            success &= romMapperKorean126Create(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_FMPAC:
            useFmPac++;
            success &= romMapperFMPACCreate(romName, buf, size, slot, subslot, startPage);
            break;
            
        case ROM_MSXMUSIC:
            success &= romMapperMsxMusicCreate(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_NORMAL:
            success &= romMapperNormalCreate(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_CASPATCH:
            success &= romMapperCasetteCreate(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_DISKPATCH:
            success &= romMapperDiskCreate(romName, buf, size, slot, subslot, startPage);
           break;

        case ROM_TC8566AF:
            success &= romMapperTC8566AFCreate(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_MICROSOL:
            success &= romMapperMicrosolCreate(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_NATIONALFDC:
            success &= romMapperNationalFdcCreate(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_PHILIPSFDC:
            success &= romMapperPhilipsFdcCreate(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_SVI738FDC:
            success &= romMapperSvi738FdcCreate(romName, buf, size, slot, subslot, startPage);
            break;

        case ROM_KANJI:
            success &= romMapperKanjiCreate(buf, size);
            break;

        case ROM_KANJI12:
            success &= romMapperKanji12Create(buf, size);
            break;

        case ROM_JISYO:
            if (jisyoRom == NULL) {
                jisyoRom = malloc(size);
                memcpy(jisyoRom, buf, size);
                jisyoRomSize = size;
            }
            break;

        case ROM_BUNSETU:
            success &= romMapperBunsetuCreate(romName, buf, size, slot, subslot, startPage, jisyoRom, jisyoRomSize);
            break;
        }
        free(buf);
    }

    if (jisyoRom != NULL) {
        free(jisyoRom);
    }

    ay8910 = ay8910Create(boardGetMixer(), AY8910_MSX);
    joyIO = joystickIoCreate(ay8910);

    for (i = 0; i < 8; i++) {
        slotMapRamPage(0, 0, i);
    }

    /* Register misc io ports */
    ioPortRegister(0x04, readMisc, NULL, NULL);
    ioPortRegister(0x05, readMisc, NULL, NULL);
    ioPortRegister(0x90, readMisc, NULL, NULL);
    ioPortRegister(0xa7, readMisc, writeMisc, NULL); // FIXME - Turbo R pause
    ioPortRegister(0xe8, readMisc, NULL, NULL);
    ioPortRegister(0xe9, readMisc, NULL, NULL);
    ioPortRegister(0xea, readMisc, NULL, NULL);
    ioPortRegister(0xeb, readMisc, NULL, NULL);
    ioPortRegister(0xec, readMisc, NULL, NULL);
    ioPortRegister(0xed, readMisc, NULL, NULL);
    ioPortRegister(0xee, readMisc, NULL, NULL);
    ioPortRegister(0xef, readMisc, NULL, NULL);

    return success;
}

void msxReset()
{
    UInt32 systemTime = boardSystemTime();

    slotManagerReset();

    if (r800 != NULL) {
        r800Reset(r800, systemTime);
    }
    
    if (ay8910 != NULL) {
        ay8910Reset(ay8910);
    }
    
    deviceManagerReset();
}

void msxSetCpuTimeout(UInt32 time)
{
    r800SetTimeoutAt(r800, time);
}

static void cpuTimeout(void* ref)
{
    boardTimerCheckTimeout();
}

static void breakpointCb(void* ref, UInt16 pc)
{
    boardOnBreakpoint(pc);
}

void msxRun() {
    r800Execute(r800);
}

void msxStop() {
    r800StopExecution(r800);
}

static void getDebugInfo(void* dummy, DbgDevice* dbgDevice)
{
    static UInt8 mappedRAM[0x10000];
    DbgRegisterBank* regBank;
    int i;

    for (i = 0; i < 0x10000; i++) {
        mappedRAM[i] = slotPeek(NULL, i);
    }

    dbgDeviceAddMemoryBlock(dbgDevice, "Visible Memory", 1, 0, 0x10000, mappedRAM);

    if (r800->callstackSize > 255) {
        static UInt16 callstack[0x100];
        int beginning = r800->callstackSize & 0xff;
        int reminder = 256 - beginning;
        memcpy(callstack, r800->callstack + beginning, reminder * sizeof(UInt16));
        memcpy(callstack + reminder, r800->callstack, beginning * sizeof(UInt16));
        dbgDeviceAddCallstack(dbgDevice, "Callstack", callstack, 256);
    }
    else {
        dbgDeviceAddCallstack(dbgDevice, "Callstack", r800->callstack, r800->callstackSize);
    }

    regBank = dbgDeviceAddRegisterBank(dbgDevice, "CPU Registers", 14);

    dbgRegisterBankAddRegister(regBank,  0, "AF",  16, r800->regs.AF.W);
    dbgRegisterBankAddRegister(regBank,  1, "BC",  16, r800->regs.BC.W);
    dbgRegisterBankAddRegister(regBank,  2, "DE",  16, r800->regs.DE.W);
    dbgRegisterBankAddRegister(regBank,  3, "HL",  16, r800->regs.HL.W);
    dbgRegisterBankAddRegister(regBank,  4, "AF1", 16, r800->regs.AF1.W);
    dbgRegisterBankAddRegister(regBank,  5, "BC1", 16, r800->regs.BC1.W);
    dbgRegisterBankAddRegister(regBank,  6, "DE1", 16, r800->regs.DE1.W);
    dbgRegisterBankAddRegister(regBank,  7, "HL1", 16, r800->regs.HL1.W);
    dbgRegisterBankAddRegister(regBank,  8, "IX",  16, r800->regs.IX.W);
    dbgRegisterBankAddRegister(regBank,  9, "IY",  16, r800->regs.IY.W);
    dbgRegisterBankAddRegister(regBank, 10, "SP",  16, r800->regs.SP.W);
    dbgRegisterBankAddRegister(regBank, 11, "PC",  16, r800->regs.PC.W);
    dbgRegisterBankAddRegister(regBank, 12, "I",   8,  r800->regs.I);
    dbgRegisterBankAddRegister(regBank, 13, "R",   8,  r800->regs.R);
//    dbgRegisterBankAddRegister(regBank, 14, "IFF", 8,  (r800->regs.iff1 != 0 ? 1 : 0)  + 2 * (r800->regs.iff2 != 0 ? 1 : 0));
    dbgRegisterBankAddRegister(regBank, 14, "IFF", 8,  (r800->regs.iff1 & 1) && (~r800->regs.iff1 & 2) ?1 : 0);
}

static int dbgWriteRegister(void* dummy, char* name, int regIndex, UInt32 value)
{
    switch (regIndex) {
    case  0: r800->regs.AF.W = (UInt16)value; break;
    case  1: r800->regs.BC.W = (UInt16)value; break;
    case  2: r800->regs.DE.W = (UInt16)value; break;
    case  3: r800->regs.HL.W = (UInt16)value; break;
    case  4: r800->regs.AF1.W = (UInt16)value; break;
    case  5: r800->regs.BC1.W = (UInt16)value; break;
    case  6: r800->regs.DE1.W = (UInt16)value; break;
    case  7: r800->regs.HL1.W = (UInt16)value; break;
    case  8: r800->regs.IX.W = (UInt16)value; break;
    case  9: r800->regs.IY.W = (UInt16)value; break;
    case 10: r800->regs.SP.W = (UInt16)value; break;
    case 11: r800->regs.PC.W = (UInt16)value; break;
    case 12: r800->regs.I = (UInt8)value; break;
    case 13: r800->regs.R = (UInt8)value; break;
    case 14: 
        r800->regs.iff1 = 2;//(UInt8)(value & 1); 
        r800->regs.iff2 = 1;//(UInt8)((value >> 1) & 1); 
        break;
    }

    return 1;
}

int msxCreate(Machine* machine, 
              DeviceInfo* devInfo,
              int loadState)
{
    DebugCallbacks dbgCallbacks = { getDebugInfo, NULL, dbgWriteRegister, NULL };
    int success;
    int i;

    msxMachine   = machine;
    msxDevInfo   = devInfo;

	pendingInt	  = 0;

    // If we're running from a state file, use its machine
    // and user configuration
    if (loadState) {
        msxLoadState();
        machineLoadState(msxMachine);
    }

    deviceManagerCreate();

    r800 = r800Create(slotRead, slotWrite, ioPortRead, ioPortWrite, PatchZ80, cpuTimeout, breakpointCb, NULL);

    boardInit(&r800->systemTime);

    ioPortReset();
    ramMapperIoCreate();

    r800Reset(r800, 0);
    mixerReset(boardGetMixer());

    currentRomType[0] = ROM_UNKNOWN;
    currentRomType[1] = ROM_UNKNOWN;

    msxPPICreate();
    slotManagerCreate();
    
    debugHandle = debugDeviceRegister(DBGTYPE_CPU, "Z80", &dbgCallbacks, NULL);

    success = initMachine(machine, devInfo->video.vdpSyncMode);

    for (i = 0; i < 2; i++) {
        if (devInfo->cartridge[i].inserted) {
            msxChangeCartridge(i, devInfo->cartridge[i].type, 
                                  devInfo->cartridge[i].name,
                                  devInfo->cartridge[i].inZipName);
        }
    }

    for (i = 0; i < 2; i++) {
        if (devInfo->diskette[i].inserted) {
            msxChangeDiskette(i, devInfo->diskette[i].name,
                                 devInfo->diskette[i].inZipName);
        }
    }

    if (devInfo->cassette.inserted) {
        msxChangeCassette(devInfo->cassette.name,
                          devInfo->cassette.inZipName);
    }

    z80Frequency = machine->cpu.freqZ80;
    r800SetFrequency(r800, CPU_Z80,  machine->cpu.freqZ80);
    r800SetFrequency(r800, CPU_R800, machine->cpu.freqR800);

    diskEnable(0, machine->fdc.count > 0);
    diskEnable(1, machine->fdc.count > 1);

    if (loadState) {
        r800LoadState(r800);
        boardInit(&r800->systemTime);

        deviceManagerLoadState();
        slotLoadState();
        if (joyIO != NULL) {
            joystickIoLoadState(joyIO);
        }
        rtcLoadState(rtc);
        if (ay8910 != NULL) {
            ay8910LoadState(ay8910);
        }
        tapeLoadState();
        videoManagerLoadState();
        keyboardLoadState();
    }

    if (!success) {
        msxDestroy();
    }

    return success;
}

void msxDestroy() {        
    msxTraceDisable();

    rtcDestroy(rtc);

    if (joyIO != NULL) {
        joystickIoDestroy(joyIO);
        joyIO = NULL;
    }    
    if (ay8910 != NULL) {
        ay8910Destroy(ay8910);
        ay8910 = NULL;
    }

    msxChangeDiskette(0, NULL, NULL);
    msxChangeDiskette(1, NULL, NULL);

    msxChangeCassette(0, 0);
    
    debugDeviceUnregister(debugHandle);

    slotManagerDestroy();

    deviceManagerDestroy();

    r800Destroy(r800);

    msxMachine = NULL;
    msxDevInfo = NULL;

    useRom     = 0;
    useMegaRom = 0;
    useMegaRam = 0;
    useFmPac   = 0;
}

int msxGetRefreshRate()
{
    return vdpGetRefreshRate();
}

UInt8* msxGetRamPage(int page) {
    static UInt8 emptyRam[0x2000];

    if (msxRam == NULL) {
        return emptyRam;
    }

	return msxRam + ((page * 0x2000) & (msxRamSize - 1));
}

int msxChangeCassette(char *name, const char *fileInZipFile)
{
    if (name && strlen(name) == 0) {
        name = NULL;
    }

    if (fileInZipFile && strlen(fileInZipFile) == 0) {
        fileInZipFile = NULL;
    }

    if (msxDevInfo != NULL) {
        msxDevInfo->cassette.inserted = name != NULL;

        strcpy(msxDevInfo->cassette.name, name ? name : "");
        strcpy(msxDevInfo->cassette.inZipName, fileInZipFile ? fileInZipFile : "");
    }

    tapeInsert(name, fileInZipFile);

    return msxDevInfo ? msxDevInfo->cassette.inserted : 0;
}

static int romTypeIsRom(RomType romType) {
    switch (romType) {
    case ROM_SCC:         return 1;
    case ROM_SCCPLUS:     return 1;
    case ROM_MOONSOUND:   return 1;
    case ROM_SNATCHER:    return 1;
    case ROM_SDSNATCHER:  return 1;
    case ROM_SCCMIRRORED: return 1;
    case ROM_SCCEXTENDED: return 1;
    case ROM_PLAIN:       return 1;
    case ROM_NORMAL:      return 1;
    case ROM_DISKPATCH:   return 1;
    case ROM_CASPATCH:    return 1;
    case ROM_MICROSOL:    return 1;
    case ROM_NATIONALFDC: return 1;
    case ROM_PHILIPSFDC:  return 1;
    case ROM_SVI738FDC:   return 1;
    case ROM_HOLYQURAN:   return 1;
    case SRAM_MATSUCHITA: return 1;
    case ROM_BASIC:       return 1;
    case ROM_0x4000:      return 1;
	case ROM_KONAMISYNTH: return 1;
    }
    return 0;
}

static int romTypeIsMegaRom(RomType romType) {
    switch (romType) {
    case ROM_STANDARD:    return 1;
    case ROM_MSXDOS2:     return 1;
    case ROM_KONAMI5:     return 1;
    case ROM_KONAMI4:     return 1;
    case ROM_ASCII8:      return 1;
    case ROM_ASCII16:     return 1;
    case ROM_GAMEMASTER2: return 1;
    case ROM_ASCII8SRAM:  return 1;
    case ROM_TC8566AF:    return 1;
    case ROM_ASCII16SRAM: return 1;
    case ROM_RTYPE:       return 1;
    case ROM_CROSSBLAIM:  return 1;
    case ROM_HARRYFOX:    return 1;
    case ROM_KOREAN80:    return 1;
    case ROM_KOREAN126:   return 1;
    case ROM_KONAMI4NF:   return 1;
    case ROM_ASCII16NF:   return 1;
    case ROM_HOLYQURAN:   return 1;
    case ROM_MAJUTSUSHI:  return 1;
    case ROM_KOEI:        return 1;
    case ROM_HALNOTE:     return 1;
    case ROM_LODERUNNER:  return 1;
    case ROM_MSXAUDIO:    return 1;
    case ROM_KOREAN90:    return 1;
    case ROM_SONYHBI55:   return 1;
    case ROM_EXTRAM512KB: return 1;
    case ROM_EXTRAM1MB:   return 1;
    case ROM_EXTRAM2MB:   return 1;
    case ROM_EXTRAM4MB:   return 1;
    }
    return 0;
}

static int romTypeIsMegaRam(RomType romType) {
    switch (romType) {
    case ROM_MEGARAM:     return 1;
    case ROM_MEGARAM128:  return 1;
    case ROM_MEGARAM256:  return 1;
    case ROM_MEGARAM512:  return 1;
    case ROM_MEGARAM768:  return 1;
    case ROM_MEGARAM2M:   return 1;
    }
    return 0;
}

static int romTypeIsFmPac(RomType romType) {
    switch (romType) {
    case ROM_FMPAC:       return 1;
    }
    return 0;
}

void msxChangeCartridge(int cartNo, RomType romType, char* cart, char* cartZip)
{
    if (cart && strlen(cart) == 0) {
        cart = NULL;
    }

    if (cartZip && strlen(cartZip) == 0) {
        cartZip = NULL;
    }

    if (msxDevInfo != NULL) {
        msxDevInfo->cartridge[cartNo].inserted = cart != NULL;
        msxDevInfo->cartridge[cartNo].type = romType;

        strcpy(msxDevInfo->cartridge[cartNo].name, cart ? cart : "");
        strcpy(msxDevInfo->cartridge[cartNo].inZipName, cartZip ? cartZip : "");
    }

    if (cart == NULL) {
        romType = currentRomType[cartNo];
        currentRomType[cartNo] = ROM_UNKNOWN;
        useRom     -= romTypeIsRom(romType);
        useMegaRom -= romTypeIsMegaRom(romType);
        useMegaRam -= romTypeIsMegaRam(romType);
        useFmPac   -= romTypeIsFmPac(romType);
    }
    else {
        currentRomType[cartNo] = romType;
        useRom     += romTypeIsRom(romType);
        useMegaRom += romTypeIsMegaRom(romType);
        useMegaRam += romTypeIsMegaRam(romType);
        useFmPac   += romTypeIsFmPac(romType);
    }

    cartridgeInsert(cartNo, romType, cart, cartZip);
}

void msxChangeDiskette(int driveId, char* fileName, const char* fileInZipFile)
{
    if (fileName && strlen(fileName) == 0) {
        fileName = NULL;
    }

    if (fileInZipFile && strlen(fileInZipFile) == 0) {
        fileInZipFile = NULL;
    }

    if (msxDevInfo != NULL) {
        msxDevInfo->diskette[driveId].inserted = fileName != NULL;

        strcpy(msxDevInfo->diskette[driveId].name, fileName ? fileName : "");
        strcpy(msxDevInfo->diskette[driveId].inZipName, fileInZipFile ? fileInZipFile : "");
    }

    diskChange(driveId ,fileName, fileInZipFile);
}
    
void msxSaveState()
{   
    SaveState* state = saveStateOpenForWrite("msx");
    DeviceInfo* di = msxDevInfo;

    saveStateSet(state, "pendingInt",      pendingInt);
    saveStateSet(state, "z80Frequency",    z80Frequency);
    
    saveStateSet(state, "cartInserted00", di->cartridge[0].inserted);
    saveStateSet(state, "cartType00",     di->cartridge[0].type);
    saveStateSetBuffer(state, "cartName00",  di->cartridge[0].name, strlen(di->cartridge[0].name) + 1);
    saveStateSetBuffer(state, "cartInZip00", di->cartridge[0].inZipName, strlen(di->cartridge[0].inZipName) + 1);
    saveStateSet(state, "cartInserted01", di->cartridge[1].inserted);
    saveStateSet(state, "cartType01",     di->cartridge[1].type);
    saveStateSetBuffer(state, "cartName01",  di->cartridge[1].name, strlen(di->cartridge[1].name) + 1);
    saveStateSetBuffer(state, "cartInZip01", di->cartridge[1].inZipName, strlen(di->cartridge[1].inZipName) + 1);

    saveStateSet(state, "diskInserted00", di->diskette[0].inserted);
    saveStateSetBuffer(state, "diskName00",  di->diskette[0].name, strlen(di->diskette[0].name) + 1);
    saveStateSetBuffer(state, "diskInZip00", di->diskette[0].inZipName, strlen(di->diskette[0].inZipName) + 1);
    saveStateSet(state, "diskInserted01", di->diskette[1].inserted);
    saveStateSetBuffer(state, "diskName01",  di->diskette[1].name, strlen(di->diskette[1].name) + 1);
    saveStateSetBuffer(state, "diskInZip01", di->diskette[1].inZipName, strlen(di->diskette[1].inZipName) + 1);

    saveStateSet(state, "casInserted", di->cassette.inserted);
    saveStateSetBuffer(state, "casName",  di->cassette.name, strlen(di->cassette.name) + 1);
    saveStateSetBuffer(state, "casInZip", di->cassette.inZipName, strlen(di->cassette.inZipName) + 1);

    saveStateSet(state, "vdpSyncMode",   di->video.vdpSyncMode);

    saveStateClose(state);

    machineSaveState(msxMachine);
    r800SaveState(r800);
    if (joyIO != NULL) {
        joystickIoSaveState(joyIO);
    }
    deviceManagerSaveState();
    slotSaveState();
    rtcSaveState(rtc);
    if (ay8910 != NULL) {
        ay8910SaveState(ay8910);
    }
    tapeSaveState();
    videoManagerSaveState();
    keyboardSaveState();
}

void msxLoadState()
{
    SaveState* state = saveStateOpenForRead("msx");
    DeviceInfo* di = msxDevInfo;

    pendingInt          = saveStateGet(state, "pendingInt",      0);
    z80Frequency        = saveStateGet(state, "z80Frequency",    0);

    di->cartridge[0].inserted = saveStateGet(state, "cartInserted00", 0);
    di->cartridge[0].type = saveStateGet(state, "cartType00",     0);
    saveStateGetBuffer(state, "cartName00",  di->cartridge[0].name, sizeof(di->cartridge[0].name));
    saveStateGetBuffer(state, "cartInZip00", di->cartridge[0].inZipName, sizeof(di->cartridge[0].inZipName));
    di->cartridge[1].inserted = saveStateGet(state, "cartInserted01", 0);
    di->cartridge[1].type = saveStateGet(state, "cartType01",     0);
    saveStateGetBuffer(state, "cartName01",  di->cartridge[1].name, sizeof(di->cartridge[1].name));
    saveStateGetBuffer(state, "cartInZip01", di->cartridge[1].inZipName, sizeof(di->cartridge[1].inZipName));

    di->diskette[0].inserted = saveStateGet(state, "diskInserted00", 0);
    saveStateGetBuffer(state, "diskName00",  di->diskette[0].name, sizeof(di->diskette[0].name));
    saveStateGetBuffer(state, "diskInZip00", di->diskette[0].inZipName, sizeof(di->diskette[0].inZipName));
    di->diskette[1].inserted = saveStateGet(state, "diskInserted01", 0);
    saveStateGetBuffer(state, "diskName01",  di->diskette[1].name, sizeof(di->diskette[1].name));
    saveStateGetBuffer(state, "diskInZip01", di->diskette[1].inZipName, sizeof(di->diskette[1].inZipName));

    di->cassette.inserted = saveStateGet(state, "casInserted", 0);
    saveStateGetBuffer(state, "casName",  di->cassette.name, sizeof(di->cassette.name));
    saveStateGetBuffer(state, "casInZip", di->cassette.inZipName, sizeof(di->cassette.inZipName));

    di->video.vdpSyncMode = saveStateGet(state, "vdpSyncMode", 0);

    saveStateClose(state);
}
