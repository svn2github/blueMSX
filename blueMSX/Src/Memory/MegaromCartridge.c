/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/MegaromCartridge.c,v $
**
** $Revision: 1.41 $
**
** $Date: 2006-09-01 19:29:54 $
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
#include "MegaromCartridge.h"
#include "MediaDb.h"
#include "RomLoader.h"
#include "SlotManager.h"

#include "ramMapper.h"
#include "romMapperStandard.h"
#include "romMapperMsxDos2.h"
#include "romMapperKonami5.h"
#include "romMapperNormal.h"
#include "romMapperKonami4.h"
#include "romMapperASCII8.h"
#include "romMapperASCII16.h"
#include "romMapperGameMaster2.h"
#include "romMapperASCII8sram.h"
#include "romMapperASCII16sram.h"
#include "romMapperKoei.h"
#include "romMapperASCII16nf.h"
#include "romMapperKonami4nf.h"
#include "romMapperKanji.h"
#include "romMapperKanji12.h"
#include "romMapperHolyQuran.h"
#include "romMapperMegaRAM.h"
#include "romMapperMsxAudio.h"
#include "romMapperPlain.h"
#include "romMapperBasic.h"
#include "romMapperHarryFox.h"
#include "romMapperHalnote.h"
#include "romMapperRType.h"
#include "romMapperCrossBlaim.h"
#include "romMapperLodeRunner.h"
#include "romMapperKorean80.h"
#include "romMapperKorean90.h"
#include "romMapperKorean126.h"
#include "romMapperKonamiSynth.h"
#include "romMapperKonamiKeyboardMaster.h"
#include "romMapperKonamiWordPro.h"
#include "romMapperMajutsushi.h"
#include "romMapperPAC.h"
#include "romMapperFMPAC.h"
#include "romMapperFMPAK.h"
#include "romMapperSCCplus.h"
#include "romMapperDisk.h"
#include "romMapperTC8566AF.h"
#include "romMapperMicrosol.h"
#include "romMapperNationalFdc.h"
#include "romMapperPhilipsFdc.h"
#include "romMapperSvi738Fdc.h"
#include "romMapperSonyHBI55.h"
#include "romMapperMoonsound.h"
#ifdef WIN32
#include "romMapperGameReader.h"
#endif
#include "romMapperSunriseIDE.h"
#include "romMapperBeerIDE.h"
#include "romMapperGIDE.h"
#include "romMapperSg1000Castle.h"
#include "romMapperMicrosolVmx80.h"
#include "romMapperSvi727.h"
#include "romMapperSonyHBIV1.h"
#include "romMapperFmDas.h"
#include "romMapperSfg05.h"
#include "romMapperSf7000Ipl.h"
#include "romMapperPlayBall.h"
#include "romMapperObsonet.h"
#include "romMapperSg1000.h"
#include "romMapperSegaBasic.h"
#include "romMapperCvMegaCart.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
    struct {
        int slot;
        int sslot;
    } cart[2];
} CartridgeInfo;


CartridgeInfo cartridgeInfo;


void cartridgeSetSlotInfo(int cartNo, int slot, int sslot) 
{
    cartridgeInfo.cart[cartNo].slot  = slot;
    cartridgeInfo.cart[cartNo].sslot = sslot;
}

int cartridgeInsert(int cartNo, RomType romType, char* cart, char* cartZip) 
{
    char* romName = cartZip != NULL ? cartZip : cart;
    int success = 1;
    UInt8* buf;
    int size;
    int slot  = cartridgeInfo.cart[cartNo].slot;
    int sslot = cartridgeInfo.cart[cartNo].sslot;

    // Delete old cartridge
    slotRemove(slot, sslot);

    if (cart == NULL) {
        return 0;
    }

    switch (romType) {
    case ROM_EXTRAM512KB:
        success &= ramMapperCreate(0x80000, slot, sslot, 0, NULL, NULL);
        break;
        
    case ROM_EXTRAM1MB:
        success &= ramMapperCreate(0x100000, slot, sslot, 0, NULL, NULL);
        break;
        
    case ROM_EXTRAM2MB:
        success &= ramMapperCreate(0x200000, slot, sslot, 0, NULL, NULL);
        break;
        
    case ROM_EXTRAM4MB:
        success &= ramMapperCreate(0x400000, slot, sslot, 0, NULL, NULL);
        break;

    case ROM_MEGARAM128:
        success &= romMapperMegaRAMCreate(0x20000, slot, sslot, 0);
        break;

    case ROM_MEGARAM256:
        success &= romMapperMegaRAMCreate(0x40000, slot, sslot, 0);
        break;

    case ROM_MEGARAM512:
        success &= romMapperMegaRAMCreate(0x80000, slot, sslot, 0);
        break;

    case ROM_MEGARAM768:
        success &= romMapperMegaRAMCreate(0xc0000, slot, sslot, 0);
        break;

    case ROM_MEGARAM2M:
        success &= romMapperMegaRAMCreate(0x200000, slot, sslot, 0);
        break;

    case ROM_PAC:
        success &= romMapperPACCreate("PacA.rom", NULL, 0, slot, sslot, 2);
        break;

#ifdef WIN32
    case ROM_GAMEREADER:
        success &= romMapperGameReaderCreate(cartNo, slot, sslot);
        break;
#endif

    case ROM_GIDE:
        success &= romMapperGIdeCreate(cartNo);
        break;

    case ROM_FMPAC:
        if (cart[strlen(cart) - 4] != '.') {
            buf = romLoad("Machines/Shared Roms/FMPAC.rom", "", &size);
            if (buf != NULL) {
                success &= romMapperFMPACCreate("FmPacA.rom", buf, size, slot, sslot, 2);
                free(buf);
            }
            else {
                static UInt8 romFMPAC[0x10000] = {
                    0x41, 0x42, 0x00, 0x00, 0x82, 0x40, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x50, 0x41, 0x43, 0x32, 0x4f, 0x50, 0x4c, 0x4c
                };
                success &= romMapperFMPACCreate("FmPacA.rom", romFMPAC, 0x10000, slot, sslot, 2);
            }
            break;
        }
        // Fall through.. 
    default:
        // Load roms for Special Carts
        if (strcmp(cart, "Sunrise IDE") == 0) {
            buf = romLoad("Machines/Shared Roms/sunriseide.rom", cartZip, &size);
            if (buf == 0) {
                success &= romMapperSunriseIdeCreate(cartNo, romName, NULL, 0, slot, sslot, 0);
                break;
            }
        }
        // Load roms for Special Carts
        else if (strcmp(cart, "Beer IDE") == 0) {
            buf = romLoad("Machines/Shared Roms/beeride.rom", cartZip, &size);
            if (buf == 0) {
                success &= romMapperBeerIdeCreate(cartNo, romName, NULL, 0, slot, sslot, 0);
                break;
            }
        }
        else {
            buf = romLoad(cart, cartZip, &size);
        }
        if (buf == NULL) {
            switch (romType) {
            case ROM_SNATCHER:
                success &= romMapperSCCplusCreate(NULL, NULL, 0, slot, sslot, 2, SCC_SNATCHER);
                break;

            case ROM_SDSNATCHER:
                success &= romMapperSCCplusCreate(NULL, NULL, 0, slot, sslot, 2, SCC_SDSNATCHER);
                break;

            case ROM_SCCMIRRORED:
                success &= romMapperSCCplusCreate(NULL, NULL, 0, slot, sslot, 2, SCC_MIRRORED);
                break;

            case ROM_SCCEXTENDED:
                success &= romMapperSCCplusCreate(NULL, NULL, 0, slot, sslot, 2, SCC_EXTENDED);
                break;

            case ROM_SCC:
                success &= romMapperSCCplusCreate(romName, NULL, 0, slot, sslot, 2, SCC_EXTENDED);
                break;

            case ROM_SCCPLUS:
                success &= romMapperSCCplusCreate(romName, NULL, 0, slot, sslot, 2, SCCP_EXTENDED);
                break;

            case ROM_SONYHBI55:
                success &= romMapperSonyHBI55Create();
                break;
            }
            break;
        }
        
        if (romType == ROM_UNKNOWN) {
            MediaType* mediaType = mediaDbGuessRom(buf, size);
            romType =  mediaDbGetRomType(mediaType);
        }

        switch (romType) {
        case ROM_0x4000:
            success &= romMapperNormalCreate(romName, buf, size, slot, sslot, 2);
            break;
            
        case ROM_0xC000:
            success &= romMapperNormalCreate(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_BASIC:
            success &= romMapperBasicCreate(romName, buf, size, slot, sslot, 4);
            break;

        case ROM_FMDAS:
            success &= romMapperFmDasCreate(romName, buf, size, slot, sslot, 0);
            break;

        case ROM_PLAIN:
            success &= romMapperPlainCreate(romName, buf, size, slot, sslot, 0);
            break;

        case ROM_FMPAK:
            success &= romMapperFMPAKCreate(romName, buf, size, slot, sslot, 0);
            break;

        case ROM_STANDARD:
            success &= romMapperStandardCreate(romName, buf, size, slot, sslot, 2);
            break;
            
        case ROM_MSXDOS2:
            success &= romMapperMsxDos2Create(romName, buf, size, slot, sslot, 2);
            break;
            
        case ROM_KONAMI5:
            success &= romMapperKonami5Create(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_OBSONET:
            success &= romMapperObsonetCreate(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_SNATCHER:
            success &= romMapperSCCplusCreate(NULL, buf, size, slot, sslot, 2, SCC_SNATCHER);
            break;

        case ROM_SDSNATCHER:
            success &= romMapperSCCplusCreate(NULL, buf, size, slot, sslot, 2, SCC_SDSNATCHER);
            break;

        case ROM_SCCMIRRORED:
            success &= romMapperSCCplusCreate(NULL, buf, size, slot, sslot, 2, SCC_MIRRORED);
            break;

        case ROM_SCCEXTENDED:
            success &= romMapperSCCplusCreate(NULL, buf, size, slot, sslot, 2, SCC_EXTENDED);
            break;

        case ROM_SCC:
            success &= romMapperSCCplusCreate(romName, buf, size, slot, sslot, 2, SCC_EXTENDED);
            break;

        case ROM_SCCPLUS:
            success &= romMapperSCCplusCreate(romName, buf, size, slot, sslot, 2, SCCP_EXTENDED);
            break;

        case ROM_MOONSOUND:
            success &= romMapperMoonsoundCreate(romName, buf, size, 640);
            break;
            
        case ROM_KONAMI4:
            success &= romMapperKonami4Create(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_MAJUTSUSHI:
            success &= romMapperMajutsushiCreate(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_HOLYQURAN:
            success &= romMapperHolyQuranCreate(romName, buf, size, slot, sslot, 2);
            break;

		case ROM_KONAMISYNTH:
            success &= romMapperKonamiSynthCreate(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_KONWORDPRO:
            success &= romMapperKonamiWordProCreate(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_KONAMKBDMAS:
            {
                // Try to load voice rom before creating the rom mapper
                char voiceName[512];
                int voiceSize = 0;
                UInt8* voiceData;
                int i;

                strcpy(voiceName, cart);
                for (i = strlen(voiceName); i > 0 && voiceName[i] != '.'; i--);
                voiceName[i] = 0;
                strcat(voiceName, "_voice.rom");
                    
                voiceData = romLoad(voiceName, NULL, &voiceSize);
                success &= romMapperKonamiKeyboardMasterCreate(romName, buf, size, slot, sslot, 2, voiceData, voiceSize);
                if (voiceData != NULL) {
                    free(voiceData);
                }
            }
            break;
            
        case ROM_ASCII8:
            success &= romMapperASCII8Create(romName, buf, size, slot, sslot, 2);
            break;
            
        case ROM_ASCII16:
            success &= romMapperASCII16Create(romName, buf, size, slot, sslot, 2);
            break;
            
        case ROM_ASCII8SRAM:
            success &= romMapperASCII8sramCreate(romName, buf, size, slot, sslot, 2);
            break;
            
        case ROM_ASCII16SRAM:
            success &= romMapperASCII16sramCreate(romName, buf, size, slot, sslot, 2);
            break;
            
        case ROM_KOEI:
            success &= romMapperKoeiCreate(romName, buf, size, slot, sslot, 2);
            break;
            
        case ROM_KONAMI4NF:
            success &= romMapperKonami4nfCreate(romName, buf, size, slot, sslot, 2);
            break;
            
        case ROM_ASCII16NF:
            success &= romMapperASCII16nfCreate(romName, buf, size, slot, sslot, 2);
            break;
            
        case ROM_GAMEMASTER2:
            success &= romMapperGameMaster2Create(romName, buf, size, slot, sslot, 2);
            break;
            
        case ROM_HARRYFOX:
            success &= romMapperHarryFoxCreate(romName, buf, size, slot, sslot, 2);
            break;
            
        case ROM_HALNOTE:
            success &= romMapperHalnoteCreate(romName, buf, size, slot, sslot, 2);
            break;
            
        case ROM_RTYPE:
            success &= romMapperRTypeCreate(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_LODERUNNER:
            success &= romMapperLodeRunnerCreate(romName, buf, size, slot, sslot, 4);
            break;
            
        case ROM_CROSSBLAIM:
            success &= romMapperCrossBlaimCreate(romName, buf, size, slot, sslot, 2);
            break;
            
        case ROM_KOREAN80:
            success &= romMapperKorean80Create(romName, buf, size, slot, sslot, 2);
            break;
            
        case ROM_KOREAN90:
            success &= romMapperKorean90Create(romName, buf, size, slot, sslot, 2);
            break;
            
        case ROM_KOREAN126:
            success &= romMapperKorean126Create(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_MSXAUDIO:
            success &= romMapperMsxAudioCreate(romName, buf, size, slot, sslot, 0);
            break;

        case ROM_YAMAHASFG01:
            success &= romMapperSfg05Create(romName, buf, size, slot, sslot, 0);
            break;

        case ROM_YAMAHASFG05:
            success &= romMapperSfg05Create(romName, buf, size, slot, sslot, 0);
            break;

        case ROM_SF7000IPL:
            success &= romMapperSf7000IplCreate(romName, buf, size, slot, sslot, 0);
            break;

        case ROM_DISKPATCH:
            success &= romMapperDiskCreate(romName, buf, size, slot, sslot, 2);
           break;

        case ROM_TC8566AF:
            success &= romMapperTC8566AFCreate(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_MICROSOL:
            success &= romMapperMicrosolCreate(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_NATIONALFDC:
            success &= romMapperNationalFdcCreate(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_PHILIPSFDC:
            success &= romMapperPhilipsFdcCreate(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_SVI738FDC:
            success &= romMapperSvi738FdcCreate(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_SVI328:
            success &= romMapperNormalCreate(romName, buf, size, 1, 0, 0);
            break;

        case ROM_COLECO:
            success &= romMapperNormalCreate(romName, buf, size, 0, 0, 4);
            break;

        case ROM_CVMEGACART:
            success &= romMapperCvMegaCartCreate(romName, buf, size, 0, 0, 4);
            break;

        case ROM_SG1000:
        case ROM_SC3000:
            success &= romMapperSg1000Create(romName, buf, size, slot, sslot, 0);
            break;

        case ROM_SG1000CASTLE:
            success &= romMapperSg1000CastleCreate(romName, buf, size, slot, sslot, 0);
            break;

        case ROM_SEGABASIC:
            success &= romMapperSegaBasicCreate(romName, buf, size, slot, sslot, 0);
            break;

        case ROM_KANJI:
            success &= romMapperKanjiCreate(buf, size);
            break;

        case ROM_KANJI12:
            success &= romMapperKanji12Create(buf, size);
            break;
            
        case ROM_FMPAC:
            success &= romMapperFMPACCreate(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_SUNRISEIDE:
            success &= romMapperSunriseIdeCreate(cartNo, romName, buf, size, slot, sslot, 0);
            break;

        case ROM_BEERIDE:
            success &= romMapperBeerIdeCreate(cartNo, romName, buf, size, slot, sslot, 2);
            break;

        case ROM_SONYHBIV1:
            success &= romMapperSonyHbiV1Create(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_PLAYBALL:
            success &= romMapperPlayBallCreate(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_SVI727:
            success &= romMapperSvi727Create(romName, buf, size, slot, sslot, 2);
            break;

        case ROM_MICROSOL80:
            {
                // Try to load character rom before creating the rom mapper
                char charName[512];
                int charSize = 0;
                UInt8* charData;
                int i;

                strcpy(charName, cart);
                for (i = strlen(charName); i > 0 && charName[i] != '.'; i--);
                charName[i] = 0;
                strcat(charName, "_char.rom");
                    
                charData = romLoad(charName, NULL, &charSize);
                success &= romMapperMicrosolVmx80Create(romName, buf, size, slot, sslot, 2, charData, charSize);
                if (charData != NULL) {
                    free(charData);
                }
            }
            break;

        default:
            success = 0;
            break;
        }

        free(buf);
    }

    return success;
}

