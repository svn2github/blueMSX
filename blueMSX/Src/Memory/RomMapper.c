/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/RomMapper.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2004-12-23 16:48:50 $
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
#include "romMapper.h"
#include "msxTypes.h"
#include "TokenExtract.h"
#include <stdio.h>
#include <string.h>

static char romdbFilename[512]  = "romdb.dat";
static RomType romdbDefaultType = ROM_UNKNOWN;
static char diskdbFilename[512] = "diskdb.dat";
static char casdbFilename[512]  = "casdb.dat";

// Static CRC table
static UInt32 crc32Table[256] = {
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
	0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
	0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
	0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
	0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
	0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
	0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,

	0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
	0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
	0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
	0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
	0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
	0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
	0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
	0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
	0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
	0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
	0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,

	0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
	0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
	0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
	0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
	0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
	0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
	0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
	0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
	0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
	0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
	0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,

	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
	0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
	0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
	0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
	0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
	0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
	0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
	0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
	0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
	0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
	0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d,
};

static UInt32 crc32(const void* buffer, int size) {
    const UInt8* ptr = (const UInt8*)buffer;
    UInt32 crc = 0xffffffff;

    while (size--) {
    	crc = (crc >> 8) ^ crc32Table[*ptr++ ^ (crc & 0xff)];
    }

    return ~crc;
}

int strcmpnocase(const char* str1, const char* str2);

RomType romMapperTypeFromString(const char* name)
{
    if (0 == strcmpnocase(name, "standard"))     return ROM_STANDARD;
    if (0 == strcmpnocase(name, "mirrored"))     return ROM_PLAIN;
    if (0 == strcmpnocase(name, "msxdos2"))      return ROM_MSXDOS2;
    if (0 == strcmpnocase(name, "konami5"))      return ROM_KONAMI5;
    if (0 == strcmpnocase(name, "konami4"))      return ROM_KONAMI4;
    if (0 == strcmpnocase(name, "ascii8"))       return ROM_ASCII8;
    if (0 == strcmpnocase(name, "halnote"))      return ROM_HALNOTE;
    if (0 == strcmpnocase(name, "coleco"))       return ROM_BASIC;
    if (0 == strcmpnocase(name, "basic"))        return ROM_BASIC;
    if (0 == strcmpnocase(name, "0x4000"))       return ROM_0x4000;
    if (0 == strcmpnocase(name, "konamisynth"))  return ROM_KONAMISYNTH;
    if (0 == strcmpnocase(name, "majutsushi"))   return ROM_MAJUTSUSHI;
    if (0 == strcmpnocase(name, "ascii16"))      return ROM_ASCII16;
    if (0 == strcmpnocase(name, "gamemaster2"))  return ROM_GAMEMASTER2;
    if (0 == strcmpnocase(name, "ascii8sram"))   return ROM_ASCII8SRAM;
    if (0 == strcmpnocase(name, "koei"))         return ROM_KOEI;
    if (0 == strcmpnocase(name, "ascii16sram"))  return ROM_ASCII16SRAM;
    if (0 == strcmpnocase(name, "konami4nf"))    return ROM_KONAMI4NF;
    if (0 == strcmpnocase(name, "ascii16nf"))    return ROM_ASCII16NF;
    if (0 == strcmpnocase(name, "snatcher"))     return ROM_SNATCHER;
    if (0 == strcmpnocase(name, "sdsnatcher"))   return ROM_SDSNATCHER;
    if (0 == strcmpnocase(name, "sccmirrored"))  return ROM_SCCMIRRORED;
    if (0 == strcmpnocase(name, "sccexpanded"))  return ROM_SCCEXTENDED;
    if (0 == strcmpnocase(name, "scc"))          return ROM_SCC;
    if (0 == strcmpnocase(name, "sccplus"))      return ROM_SCCPLUS;
    if (0 == strcmpnocase(name, "scc+"))         return ROM_SCCPLUS;
    if (0 == strcmpnocase(name, "pac"))          return ROM_PAC;
    if (0 == strcmpnocase(name, "fmpac"))        return ROM_FMPAC;
    if (0 == strcmpnocase(name, "msxaudio"))     return ROM_MSXAUDIO;
    if (0 == strcmpnocase(name, "tc8566af"))     return ROM_TC8566AF;
    if (0 == strcmpnocase(name, "mb8877a"))      return ROM_NATIONALFDC;
    if (0 == strcmpnocase(name, "diskpatch"))    return ROM_DISKPATCH;
    if (0 == strcmpnocase(name, "caspatch"))     return ROM_CASPATCH;
    if (0 == strcmpnocase(name, "wd2793"))       return ROM_PHILIPSFDC;
    if (0 == strcmpnocase(name, "svi738fdc"))    return ROM_SVI738FDC;
    if (0 == strcmpnocase(name, "microsol"))     return ROM_MICROSOL;
    if (0 == strcmpnocase(name, "rtype"))        return ROM_RTYPE;
    if (0 == strcmpnocase(name, "crossblaim"))   return ROM_CROSSBLAIM;
    if (0 == strcmpnocase(name, "harryfox"))     return ROM_HARRYFOX;
    if (0 == strcmpnocase(name, "loderunner"))   return ROM_LODERUNNER;
    if (0 == strcmpnocase(name, "korean80"))     return ROM_KOREAN80;
    if (0 == strcmpnocase(name, "korean90"))     return ROM_KOREAN90;
    if (0 == strcmpnocase(name, "korean126"))    return ROM_KOREAN126;
    if (0 == strcmpnocase(name, "holyquran"))    return ROM_HOLYQURAN;  
    if (0 == strcmpnocase(name, "kanji"))        return ROM_KANJI;      
    if (0 == strcmpnocase(name, "kanji12"))      return ROM_KANJI12;    
    if (0 == strcmpnocase(name, "jisyo"))        return ROM_JISYO;    
    if (0 == strcmpnocase(name, "bunsetsu"))     return ROM_BUNSETU;

    return ROM_UNKNOWN;
}    

void romMapperSetRomdbFilename(const char* filename)
{
    strcpy(romdbFilename, filename);
}

void romMapperSetDiskdbFilename(const char* filename)
{
    strcpy(diskdbFilename, filename);
}

void romMapperSetCasdbFilename(const char* filename)
{
    strcpy(casdbFilename, filename);
}

RomType romMapperRomFromFile(const void *romData, int size, char* extendedName)
{
    UInt32 crc = crc32(romData, size);
    char buffer[128];
    RomType romType = ROM_UNKNOWN;
    FILE* file = fopen(romdbFilename, "r");

    if (file == NULL) {
        return ROM_UNKNOWN;
    }

    while (romType == ROM_UNKNOWN && fgets(buffer, 128, file)) {
        char* crcBuf  = extractToken(buffer, 0);

        if (crcBuf) {
            int c = 0;

            sscanf(crcBuf, "%x", &c);

            if (c == crc) {
                romType = romMapperTypeFromString(extractToken(buffer, 1));

                // Handle some duplicate CRCs
                if (crc == 0x0e84505d) {
                    romType = crc32(romData, 128) == 0xb8a8e218 ? ROM_FMPAC : ROM_KOREAN126;
                }
                if (crc == 0xe0e72736) {
                    romType = crc32(romData, 128) == 0x4cae8359 ? ROM_KONAMI5 : ROM_KOREAN80;
                }
                
                if (extendedName != NULL) {
                    int index = 2;
                    char* buf = extractToken(buffer, index++);
                    int length;

                    while (buf != NULL) {
                        strcat(extendedName, buf);
                        buf = extractToken(buffer, index++);
                        strcat(extendedName, buf != NULL ? " " : "");
                    }

                    length = strlen(extendedName);
                    if (length > 10 && extendedName[length - 1] == ']' && extendedName[length - 10] == '[') {
                        extendedName[length - 10] = 0;
                    }
                }
            }
        }
    }

    fclose(file);

    return romType;
}

void romMapperSetDefaultType(RomType romType)
{
    romdbDefaultType = romType;
}


RomType romMapperGuessRom(const void *buffer, int size, int guess, char* extendedName)
{
    const UInt8* romData = buffer;
    int i;
    int mapper;
    int counters[6] = { 0, 0, 0, 0, 0, 0 };
    RomType romType;

    if (extendedName) {
        extendedName[0] = 0;
    }

    if (size < 128) {
        return romdbDefaultType;
    }

    romType = romMapperRomFromFile(romData, size, extendedName);

    if (romType == ROM_UNKNOWN &&
        size < 0x8001 && romData[0] == 0xF3 && romData[1] == 0x31) {
            romType = ROM_SVI328;
    }

    if (romType == ROM_STANDARD &&
        (size < 0x10000 || (size == 0x10000 && romData[0x4000] == 'A' && romData[0x4001] == 'B'))) {
        romType = ROM_PLAIN;
    }

    if (romType != ROM_UNKNOWN) {
        return romType;
    }

    if (!guess || romdbDefaultType != ROM_UNKNOWN) {
        return romdbDefaultType;
    }

	if (size <= 0x10000) {
		if (size == 0x10000) {
			return ROM_ASCII16;
		} 
        
        if (size <= 0x4000 && romData[0] == 'A' && romData[1] == 'B') {
			UInt16 init = romData[2] + 256 * romData[3];
			UInt16 text = romData[8] + 256 * romData[9];
			if (init == 0 && (text & 0xc000) == 0x8000) {
				return ROM_BASIC;
			}
		}
		return ROM_PLAIN;
	}

    counters[0]++; /* Mapper #0 is default */
    counters[4]--; /* #5 preferred over #4 */

    /* Count occurences of characteristic addresses */
    for (i = 0; i < size - 2; i++) {
        UInt8 value = romData[i] + ((int)romData[i + 1] << 8) + ((int)romData[i + 2] << 16);

        switch(value) {
        case 0x400032: 
            counters[3]++;
            break;

        case 0x500032: 
            counters[2]++;
            break;

        case 0x600032: 
            counters[3]++;
            counters[4]++;
            counters[5]++;
            break;

        case 0x680032: 
            counters[4]++;
            break;

        case 0x700032: 
            counters[2]++;
            counters[4]++;
            counters[5]++;
            break;

        case 0x780032: 
            counters[4]++;
            break;

        case 0x77ff32: 
            counters[5]++;
            break;

        case 0x800032: 
            counters[3]++;
            break;

        case 0x900032: 
            counters[2]++;
            break;

        case 0xa00032: 
            counters[3]++;
            break;

        case 0xb00032: 
            counters[2]++;
            break;
        }
    }

    /* Find which mapper type got more hits */
    mapper = 0;

    for (i = 0; i < 6; i++) {
        if (counters[i] > counters[mapper]) {
            mapper = i;
        }
    }

    switch (mapper) {
    default:
    case 0: return ROM_STANDARD;
    case 1: return ROM_MSXDOS2;
    case 2: return ROM_KONAMI5;
    case 3: return ROM_KONAMI4;
    case 4: return ROM_ASCII8;
    case 5: return ROM_ASCII16;
    case 6: return ROM_GAMEMASTER2;
    }
}


void romMapperGetDiskInfo(const void *data, int size, char* extendedName)
{
    if (extendedName) {
        UInt32 crc = crc32(data, size);
        char buffer[128];
        RomType romType = ROM_UNKNOWN;
        FILE* file;

        extendedName[0] = 0;
        
        if (size == 0) {
            return;
        }

        file = fopen(diskdbFilename, "r");
        if (file == NULL) {
            return;
        }

        while (fgets(buffer, 128, file)) {
            char* crcBuf  = extractToken(buffer, 0);

            if (crcBuf) {
                int c = 0;

                sscanf(crcBuf, "%x", &c);

                if (c == crc) {
                    int index = 1;
                    char* buf = extractToken(buffer, index++);
                    int length;

                    while (buf != NULL) {
                        strcat(extendedName, buf);
                        buf = extractToken(buffer, index++);
                        strcat(extendedName, buf != NULL ? " " : "");
                    }

                    length = strlen(extendedName);
                    if (length > 10 && extendedName[length - 1] == ']' && extendedName[length - 10] == '[') {
                        extendedName[length - 10] = 0;
                    }
                }
            }
        }

        fclose(file);
    }
}

void romMapperGetCasInfo(const void *data, int size, char* extendedName)
{
    if (extendedName) {
        UInt32 crc = crc32(data, size);
        char buffer[128];
        RomType romType = ROM_UNKNOWN;
        FILE* file;

        extendedName[0] = 0;
        
        if (size == 0) {
            return;
        }

        file = fopen(casdbFilename, "r");
        if (file == NULL) {
            return;
        }

        while (fgets(buffer, 128, file)) {
            char* crcBuf  = extractToken(buffer, 0);

            if (crcBuf) {
                int c = 0;

                sscanf(crcBuf, "%x", &c);

                if (c == crc) {
                    int index = 1;
                    char* buf = extractToken(buffer, index++);
                    int length;

                    while (buf != NULL) {
                        strcat(extendedName, buf);
                        buf = extractToken(buffer, index++);
                        strcat(extendedName, buf != NULL ? " " : "");
                    }

                    length = strlen(extendedName);
                    if (length > 10 && extendedName[length - 1] == ']' && extendedName[length - 10] == '[') {
                        extendedName[length - 10] = 0;
                    }
                }
            }
        }

        fclose(file);
    }
}