/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Media/MediaDb.cpp,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-02-11 04:38:27 $
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
extern "C" {
#include "MsxTypes.h"
#include "MediaDb.h"
#include "Crc32.h"
#include "TokenExtract.h"
}

#include "TinyXml.h"
#include <string>
#include <map>

using namespace std;

typedef map<UInt32, MediaType*> CrcMap;
typedef map<string, MediaType*> Sha1Map;


struct MediaDb {
    Sha1Map sha1Map;
    CrcMap crcMap;
};

static MediaDb* romdb;
static MediaDb* diskdb;
static MediaDb* casdb;
static RomType  romdbDefaultType = ROM_UNKNOWN;

extern "C" RomType mediaDbOldStringToType(const char* romName)
{
    string name(romName);

    if (name == "standard")     return ROM_STANDARD;
    if (name == "mirrored")     return ROM_PLAIN;
    if (name == "msxdos2")      return ROM_MSXDOS2;
    if (name == "konami5")      return ROM_KONAMI5;
    if (name == "konami4")      return ROM_KONAMI4;
    if (name == "ascii8")       return ROM_ASCII8;
    if (name == "halnote")      return ROM_HALNOTE;
    if (name == "basic")        return ROM_BASIC;
    if (name == "0x4000")       return ROM_0x4000;
    if (name == "konamisynth")  return ROM_KONAMISYNTH;
    if (name == "majutsushi")   return ROM_MAJUTSUSHI;
    if (name == "ascii16")      return ROM_ASCII16;
    if (name == "gamemaster2")  return ROM_GAMEMASTER2;
    if (name == "ascii8sram")   return ROM_ASCII8SRAM;
    if (name == "koei")         return ROM_KOEI;
    if (name == "ascii16sram")  return ROM_ASCII16SRAM;
    if (name == "konami4nf")    return ROM_KONAMI4NF;
    if (name == "ascii16nf")    return ROM_ASCII16NF;
    if (name == "snatcher")     return ROM_SNATCHER;
    if (name == "sdsnatcher")   return ROM_SDSNATCHER;
    if (name == "sccmirrored")  return ROM_SCCMIRRORED;
    if (name == "sccexpanded")  return ROM_SCCEXTENDED;
    if (name == "scc")          return ROM_SCC;
    if (name == "sccplus")      return ROM_SCCPLUS;
    if (name == "scc+")         return ROM_SCCPLUS;
    if (name == "pac")          return ROM_PAC;
    if (name == "fmpac")        return ROM_FMPAC;
    if (name == "msxaudio")     return ROM_MSXAUDIO;
    if (name == "msxmusic")     return ROM_MSXMUSIC;
    if (name == "moonsound")    return ROM_MOONSOUND;
    if (name == "tc8566af")     return ROM_TC8566AF;
    if (name == "mb8877a")      return ROM_NATIONALFDC;
    if (name == "diskpatch")    return ROM_DISKPATCH;
    if (name == "caspatch")     return ROM_CASPATCH;
    if (name == "wd2793")       return ROM_PHILIPSFDC;
    if (name == "svi738fdc")    return ROM_SVI738FDC;
    if (name == "microsol")     return ROM_MICROSOL;
    if (name == "rtype")        return ROM_RTYPE;
    if (name == "crossblaim")   return ROM_CROSSBLAIM;
    if (name == "harryfox")     return ROM_HARRYFOX;
    if (name == "loderunner")   return ROM_LODERUNNER;
    if (name == "korean80")     return ROM_KOREAN80;
    if (name == "korean90")     return ROM_KOREAN90;
    if (name == "korean126")    return ROM_KOREAN126;
    if (name == "holyquran")    return ROM_HOLYQURAN;  
    if (name == "kanji")        return ROM_KANJI;      
    if (name == "kanji12")      return ROM_KANJI12;    
    if (name == "jisyo")        return ROM_JISYO;    
    if (name == "bunsetsu")     return ROM_BUNSETU;
    if (name == "coleco")       return ROM_COLECO;
    if (name == "svi328")       return ROM_SVI328;

    return ROM_UNKNOWN;
}

extern "C" const char* romTypeToString(RomType romType)
{
    switch (romType) {    
    case ROM_STANDARD:    return "Standard";
    case ROM_MSXDOS2:     return "MSXDOS 2";
    case ROM_KONAMI5:     return "Konami 5";
    case ROM_KONAMI4:     return "Konami 4";
    case ROM_ASCII8:      return "ASCII 8";
    case ROM_ASCII16:     return "ASCII 16";
    case ROM_GAMEMASTER2: return "Game Master 2 (SRAM)";
    case ROM_ASCII8SRAM:  return "ASCII 8 (SRAM)";
    case ROM_ASCII16SRAM: return "ASCII 16 (SRAM)";
    case ROM_RTYPE:       return "R-Type";
    case ROM_CROSSBLAIM:  return "Cross Blaim";
    case ROM_HARRYFOX:    return "Harry Fox";
    case ROM_MAJUTSUSHI:  return "Konami Majutsushi";
    case ROM_KOREAN80:    return "Korean 80 in 1";
    case ROM_KOREAN126:   return "Korean 126 in 1";
    case ROM_SCC:         return "SCC";
    case ROM_SCCPLUS:     return "SCC+";
    case ROM_SNATCHER:    return "The Snatcher";
    case ROM_SDSNATCHER:  return "SD Snatcher";
    case ROM_SCCMIRRORED: return "SCC mirrored";
    case ROM_SCCEXTENDED: return "SCC extended";
    case ROM_FMPAC:       return "FMPAC (SRAM)";
    case ROM_KONAMI4NF:   return "Konami4 alt.";
    case ROM_ASCII16NF:   return "ASCII 16 alt.";
    case ROM_PLAIN:       return "Mirrored ROM";
    case ROM_NORMAL:      return "Normal ROM";
    case ROM_DISKPATCH:   return "Normal + Disk Patch";
    case ROM_CASPATCH:    return "Normal + Cassette Patch";
    case ROM_TC8566AF:    return "TC8566AF Disk Controller";
    case ROM_MICROSOL:    return "Microsol Disk Controller";
    case ROM_NATIONALFDC: return "National Disk Controller";
    case ROM_PHILIPSFDC:  return "Philips Disk Controller";
    case ROM_SVI738FDC:   return "SVI-738 Disk Controller";
    case RAM_MAPPER:      return "Mapped RAM";
    case RAM_NORMAL:      return "Normal RAM";
    case ROM_KANJI:       return "Kanji";
    case ROM_HOLYQURAN:   return "Holy Quran";
    case SRAM_MATSUCHITA: return "Matsushita SRAM";
    case ROM_PANASONIC16: return "Panasonic 16kB SRAM";
    case ROM_PANASONIC32: return "Panasonic 32kB SRAM";
    case ROM_BUNSETU:     return "Bunsetsu";
    case ROM_JISYO:       return "Jisyo";
    case ROM_KANJI12:     return "Kanji12";
    case ROM_NATIONAL:    return "National (SRAM)";
    case SRAM_S1985:      return "S1985";
    case ROM_S1990:       return "S1990";
    case ROM_F4DEVICE:    return "F4 Device Normal";
    case ROM_F4INVERTED:  return "F4 Device Inverted";
    case ROM_TURBORTIMER: return "Turbo-R Timer";
    case AUDIO_MOONSOUND: return "Moonsound Audio";
    case AUDIO_Y8950:     return "Y8950 Audio";
    case AUDIO_YM2413:    return "YM2413 Audio";
    case ROM_KOEI:        return "Koei (SRAM)";
    case ROM_BASIC:       return "Basic ROM";
    case ROM_HALNOTE:     return "Halnote";
    case ROM_LODERUNNER:  return "Lode Runner";
    case ROM_0x4000:      return "Normal 0x4000";
    case ROM_KONAMISYNTH: return "Konami Synthesizer";
    case ROM_PAC:         return "PAC (SRAM)";
    case ROM_MEGARAM:     return "MegaRAM";
    case ROM_MEGARAM128:  return "128kB MegaRAM";
    case ROM_MEGARAM256:  return "256kB MegaRAM";
    case ROM_MEGARAM512:  return "512kB MegaRAM";
    case ROM_MEGARAM768:  return "768kB MegaRAM";
    case ROM_MEGARAM2M:   return "2MB MegaRAM";
    case ROM_EXTRAM:      return "External RAM";
    case ROM_EXTRAM512KB: return "512kB External RAM";
    case ROM_EXTRAM1MB:   return "1MB External RAM";
    case ROM_EXTRAM2MB:   return "2MB External RAM";
    case ROM_EXTRAM4MB:   return "4MB External RAM";
    case ROM_MSXMUSIC:    return "MSX Music";
    case ROM_MSXAUDIO:    return "MSX Audio";
    case ROM_MOONSOUND:   return "Moonsound";
    case ROM_KOREAN90:    return "Korean 90 in 1";
    case ROM_SVI328:      return "SVI-328 Cartridge";
    case ROM_SVI328FDC:   return "SVI-328 Disk Controller";
    case ROM_SVI328PRN:   return "SVI-328 Printer";
    case ROM_SVI328RS232: return "SVI-328 Serial Port";
    case ROM_SVI80COL:    return "SVI 80 Column Card";
    case ROM_COLECO:      return "Coleco Cartridge";
    case ROM_SONYHBI55:   return "Sony HBI-55";
    case ROM_MSXAUDIODEV: return "MSX Audio Chip";
    case ROM_MSXPRN:      return "MSX Printer";
    case ROM_TURBORPCM:   return "Turbo-R PCM Chip";

    case ROM_UNKNOWN:     return "Unknown";
    }

    return "unknown";
}

extern "C" const char* romTypeToShortString(RomType romType) 
{
    switch (romType) {    
    case ROM_STANDARD:    return "STANDARD";
    case ROM_MSXDOS2:     return "MSXDOS2";
    case ROM_KONAMI5:     return "KONAMI5";
    case ROM_KONAMI4:     return "KONAMI4";
    case ROM_ASCII8:      return "ASCII8";
    case ROM_ASCII16:     return "ASCII16";
    case ROM_GAMEMASTER2: return "GMASTER2";
    case ROM_ASCII8SRAM:  return "ASCII8SRAM";
    case ROM_ASCII16SRAM: return "ASCII16SRAM";
    case ROM_RTYPE:       return "R-TYPE";
    case ROM_CROSSBLAIM:  return "CROSSBLAIM";
    case ROM_HARRYFOX:    return "HARRYFOX";
    case ROM_KOREAN80:    return "80IN1";
    case ROM_KOREAN126:   return "126IN1";
    case ROM_SCC:         return "SCC";
    case ROM_SCCPLUS:     return "SCC+";
    case ROM_SNATCHER:    return "SNATCHER";
    case ROM_SDSNATCHER:  return "SDSNATCHER";
    case ROM_SCCMIRRORED: return "SCCMIRRORED";
    case ROM_SCCEXTENDED: return "SCCEXTENDED";
    case ROM_FMPAC:       return "FMPAC";
    case ROM_KONAMI4NF:   return "KONAMI4ALT";
    case ROM_ASCII16NF:   return "ASCII16ALT";
    case ROM_PLAIN:       return "MIRRORED";
    case ROM_NORMAL:      return "NORMAL";
    case ROM_DISKPATCH:   return "DISKPATCH";
    case ROM_CASPATCH:    return "CASPATCH";
    case ROM_TC8566AF:    return "TC8566AF";
    case ROM_MICROSOL:    return "MICROSOL";
    case ROM_NATIONALFDC: return "NATNL FDC";
    case ROM_PHILIPSFDC:  return "PHILIPSFDC";
    case ROM_SVI738FDC:   return "SVI738 FDC";
    case RAM_MAPPER:      return "MAPPED RAM";
    case RAM_NORMAL:      return "NORMAL RAM";
    case ROM_KANJI:       return "KANJI";
    case ROM_HOLYQURAN:   return "HOLYQURAN";
    case SRAM_MATSUCHITA: return "MATSUSHITA";
    case ROM_PANASONIC16: return "PANASON 16";
    case ROM_PANASONIC32: return "PANASON 32";
    case ROM_BUNSETU:     return "BUNSETSU";
    case ROM_JISYO:       return "JISYO";
    case ROM_KANJI12:     return "KANJI12";
    case ROM_NATIONAL:    return "NATIONAL";
    case SRAM_S1985:      return "S1985";
    case ROM_S1990:       return "S1990";
    case ROM_F4DEVICE:    return "F4NORMAL";
    case ROM_F4INVERTED:  return "F4INV";
    case ROM_TURBORTIMER: return "TURBORTMR";
    case AUDIO_MOONSOUND: return "MOONSOUND";
    case AUDIO_Y8950:     return "Y8950";
    case AUDIO_YM2413:    return "YM2413";
    case ROM_KOEI:        return "KOEI";
    case ROM_BASIC:       return "BASIC";
    case ROM_HALNOTE:     return "HALNOTE";
    case ROM_LODERUNNER:  return "LODERUNNER";
    case ROM_0x4000:      return "0x4000";
    case ROM_KONAMISYNTH: return "KONSYNTH";
    case ROM_MAJUTSUSHI:  return "MAJUTSUSHI";
    case ROM_PAC:         return "PAC";
    case ROM_MEGARAM:     return "MEGARAM";
    case ROM_MEGARAM128:  return "MEGARAM128";
    case ROM_MEGARAM256:  return "MEGARAM256";
    case ROM_MEGARAM512:  return "MEGARAM512";
    case ROM_MEGARAM768:  return "MEGARAM768";
    case ROM_MEGARAM2M:   return "MEGARAM2MB";
    case ROM_EXTRAM:      return "EXTERN RAM";
    case ROM_EXTRAM512KB: return "EXTRAM 512";
    case ROM_EXTRAM1MB:   return "EXTRAM 2MB";
    case ROM_EXTRAM2MB:   return "EXTRAM 1MB";
    case ROM_EXTRAM4MB:   return "EXTRAM 4MB";
    case ROM_MSXMUSIC:    return "MSXMUSIC";
    case ROM_MSXAUDIO:    return "MSXAUDIO";
    case ROM_MOONSOUND:   return "MOONSOUND";
    case ROM_KOREAN90:    return "90IN1";
    case ROM_SVI328:      return "SVI328";
    case ROM_SVI328FDC:   return "SVI328FDC";
    case ROM_SVI328PRN:   return "SVI328PRN";
    case ROM_SVI328RS232: return "SVI328RS232";
    case ROM_SVI80COL:    return "SVI80COL";
    case ROM_COLECO:      return "COLECO";
    case ROM_SONYHBI55:   return "HBI-55";
    case ROM_MSXAUDIODEV: return "MSXAUDIO";
    case ROM_MSXPRN:      return "MSXPRN";
    case ROM_TURBORPCM:   return "TURBOR PCM";

    case ROM_UNKNOWN:     return "UNKNOWN";
    }

    return "UNKNOWN";
}

extern "C" MediaDb* mediaDbCreate()
{
    return new MediaDb;
}

extern "C" void mediaDbDestroy(MediaDb* mediaDb)
{
}

extern "C" void mediaDbAddFromOldFile(MediaDb* mediaDb, 
                                      const char* fileName, OldFormat format) 
{
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        return;
    }

    char buffer[128];
    while (fgets(buffer, 128, file)) {
        char* tokenStr     = extractToken(buffer, 1);
        if (tokenStr == NULL) {
            continue;
        }

        RomType romType    = format == FORMAT_ROM ? mediaDbOldStringToType(tokenStr) : ROM_UNKNOWN;
        std::string title  = extractTokens(buffer, format == FORMAT_ROM ? 2 : 1);
        
        std::string crcStr = extractToken(buffer, 0);
        UInt32 crc32;
        
        if (sscanf(crcStr.c_str(), "%x", &crc32) != 1) {
            continue;
        }

        if (title.length() == 0 || crc32 == 0) {
            continue;
        }

        MediaType* mediaType = new MediaType;
        mediaType->company[0] = 0;
        mediaType->remark[0] = 0;
        mediaType->year[0] = 0;
        mediaType->romType = romType;
        strcpy(mediaType->title, title.substr(0, sizeof(mediaType->title) - 1).c_str());

        mediaDb->crcMap[crc32] = mediaType;
    }
}

extern "C" void mediaDbAddFromXmlFile(MediaDb* mediaDb, const char* fileName, 
                                      const char* rootTag, const char* elemTag) 
{
    if (fileName == NULL) {
        return;
    }

    TiXmlDocument doc(fileName);

    doc.LoadFile();
    if (doc.Error()) {
        return;
    }
    
    TiXmlElement* root = doc.RootElement();
    if (root == NULL || strcmp(root->Value(), rootTag) != 0) {
        return;
    }
    
    for (TiXmlElement* el = root->FirstChildElement(); el != NULL; el = el->NextSiblingElement()) {
        if (strcmp(el->Value(), elemTag) != 0) {
            continue;
        }

        RomType romType = ROM_UNKNOWN;
        string  title;
        string  company;
        string  year;
        string  remark;
        
        for (TiXmlElement* item = el->FirstChildElement(); item != NULL; item = item->NextSiblingElement()) {
            if (strcmp(item->Value(), "romtype") == 0) {
                TiXmlNode* name = item->FirstChild();
                if (name != NULL) {
                    romType = mediaDbOldStringToType(name->Value());
                }
            }
            if (strcmp(item->Value(), "title") == 0) {
                TiXmlNode* name = item->FirstChild();
                if (name != NULL) {
                    title = name->Value();
                }
            }
            if (strcmp(item->Value(), "company") == 0) {
                TiXmlNode* name = item->FirstChild();
                if (name != NULL) {
                    company = name->Value();
                }
            }
            if (strcmp(item->Value(), "year") == 0) {
                TiXmlNode* name = item->FirstChild();
                if (name != NULL) {
                    year = name->Value();
                }
            }
            if (strcmp(item->Value(), "remark") == 0) {
                TiXmlNode* name = item->FirstChild();
                if (name != NULL) {
                    remark = name->Value();
                }
            }
        }
        
        for (TiXmlElement* item = el->FirstChildElement(); item != NULL; item = item->NextSiblingElement()) {
            if (strcmp(item->Value(), "crc") == 0) {
                TiXmlNode* name = item->FirstChild();
                if (name != NULL) {
                    UInt32 crc32;
                    if (sscanf(name->Value(), "%x", &crc32) == 1) {
                        MediaType* mediaType = new MediaType;
                        strcpy(mediaType->title, title.substr(0, sizeof(mediaType->title) - 1).c_str());
                        strcpy(mediaType->company, company.substr(0, sizeof(mediaType->company) - 1).c_str());
                        strcpy(mediaType->remark, remark.substr(0, sizeof(mediaType->remark) - 1).c_str());
                        strcpy(mediaType->year, year.substr(0, sizeof(mediaType->year) - 1).c_str());
                        mediaType->romType = romType;

                        mediaDb->crcMap[crc32] = mediaType;
                    }
                }
            }
        }
    }
}

extern "C" MediaType* mediaDbLookup(MediaDb* mediaDb, const void *buffer, int size)
{
    UInt32 crc = crc32(buffer, size);

    CrcMap::iterator iter = mediaDb->crcMap.find(crc);

    if (iter == mediaDb->crcMap.end()) {
        return NULL;
    }
    return iter->second;
}

extern "C" void mediaDbCreateRomdb(const char* oldFileName, const char* xmlFileName)
{
    if (romdb == NULL) {
        romdb = mediaDbCreate();
    }

    mediaDbAddFromOldFile(romdb, oldFileName, FORMAT_ROM);
    mediaDbAddFromXmlFile(romdb, xmlFileName, "romdb", "rom");
}

extern "C" void mediaDbCreateDiskdb(const char* oldFileName, const char* xmlFileName)
{
    if (diskdb == NULL) {
        diskdb = mediaDbCreate();
    }

    mediaDbAddFromOldFile(diskdb, oldFileName, FORMAT_DISK);
    mediaDbAddFromXmlFile(diskdb, xmlFileName, "diskdb", "disk");
}

extern "C" void mediaDbCreateCasdb(const char* oldFileName, const char* xmlFileName)
{
    if (diskdb == NULL) {
        casdb = mediaDbCreate();
    }

    mediaDbAddFromOldFile(casdb, oldFileName, FORMAT_CAS);
    mediaDbAddFromXmlFile(casdb, xmlFileName, "casdb", "cas");
}

extern "C" MediaType* mediaDbLookupRom(const void *buffer, int size) 
{
    const char* romData = (const char*)buffer;
    static MediaType defaultColeco = { "Unknown Coleco rom", "", "", "", ROM_COLECO };
    static MediaType defaultSvi    = { "Unknown SVI rom", "", "", "", ROM_SVI328 };

    if (romdb == NULL) {
        return NULL;
    }
    MediaType* mediaType = mediaDbLookup(romdb, buffer, size);

    if (mediaType == NULL &&
        size <= 0x8000 && romData[0] == 0xF3 && romData[1] == 0x31)
    {
        mediaType = &defaultSvi;
    }

    if (mediaType == NULL &&
        size <= 0x8000 && romData[0] == 0x55 && romData[1] == 0xAA) 
    {
        mediaType = &defaultColeco;
    }

    return mediaType;
}

extern "C" MediaType* mediaDbLookupDisk(const void *buffer, int size)
{
    if (diskdb == NULL) {
        return NULL;
    }
    return mediaDbLookup(diskdb, buffer, size);
}

extern "C" MediaType* mediaDbLookupCas(const void *buffer, int size)
{
    if (casdb == NULL) {
        return NULL;
    }
    return mediaDbLookup(casdb, buffer, size);
}

extern "C" const char* mediaDbCreatePrettyString(MediaType* mediaType)
{
    static char prettyString[512];

    prettyString[0] = 0;

    if (mediaType != NULL) {
        strcat(prettyString, mediaType->title);
        if (mediaType->company[0] || mediaType->year[0]) {
            strcat(prettyString, " -");
        }
            
        if (mediaType->company[0]) {
            strcat(prettyString, " ");
            strcat(prettyString, mediaType->company);
        }

        if (mediaType->year[0]) {
            strcat(prettyString, " ");
            strcat(prettyString, mediaType->year);
        }
    }

    return prettyString;
}


extern "C" void mediaDbSetDefaultRomType(RomType romType)
{
    romdbDefaultType = romType;
}

extern "C" MediaType* mediaDbGuessRom(const void *buffer, int size) 
{
    static MediaType staticMediaType = { "Unknown MSX rom", "", "", "", ROM_UNKNOWN };

    const UInt8* romData = (const UInt8*)buffer;
    int i;
    int mapper;
    int counters[6] = { 0, 0, 0, 0, 0, 0 };

    staticMediaType.romType = romdbDefaultType;

    if (size < 128) {
        return &staticMediaType;
    }

    MediaType* mediaType = mediaDbLookupRom(buffer, size);
    if (mediaType == NULL) {
        mediaType = &staticMediaType;
    }

    if (mediaType->romType != ROM_UNKNOWN) {
        return mediaType;
    }

	if (size <= 0x10000) {
		if (size == 0x10000) {
            mediaType->romType = ROM_ASCII16;
			return mediaType;
		} 
        
        if (size <= 0x4000 && romData[0] == 'A' && romData[1] == 'B') {
			UInt16 init = romData[2] + 256 * romData[3];
			UInt16 text = romData[8] + 256 * romData[9];
			if (init == 0 && (text & 0xc000) == 0x8000) {
                mediaType->romType = ROM_BASIC;
			    return mediaType;
			}
		}
        mediaType->romType = ROM_PLAIN;
		return mediaType;
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
    case 0: mediaType->romType = ROM_STANDARD; break;
    case 1: mediaType->romType = ROM_MSXDOS2; break;
    case 2: mediaType->romType = ROM_KONAMI5; break;
    case 3: mediaType->romType = ROM_KONAMI4; break;
    case 4: mediaType->romType = ROM_ASCII8; break;
    case 5: mediaType->romType = ROM_ASCII16; break;
    case 6: mediaType->romType = ROM_GAMEMASTER2; break;
    }
    
    return mediaType;
}
