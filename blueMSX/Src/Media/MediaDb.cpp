/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Media/MediaDb.cpp,v $
**
** $Revision: 1.23 $
**
** $Date: 2005-08-31 06:51:52 $
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
#include <windows.h>
extern "C" {
#include "MsxTypes.h"
#include "MediaDb.h"
#include "Crc32.h"
#include "TokenExtract.h"
#include "StrcmpNoCase.h"
#include "Language.h"
}

#include "TinyXml.h"
#include "Sha1.h"
#include <string>
#include <map>

using namespace std;

typedef map<UInt32, MediaType*> CrcMap;
typedef map<string, MediaType*> Sha1Map;


struct MediaDb {
    Sha1Map sha1Map;
    CrcMap crcMap;
};

struct MediaType {
    MediaType(RomType rt, const string t, const string c = "", const string y = "", const string ct = "", const string r = "", string s = "") :
        romType(rt), title(t), company(c), year(y), country(ct), remark(r), start(s) {}

    MediaType(const MediaType& mt) :
        romType(mt.romType), title(mt.title), company(mt.company), year(mt.year), 
        country(mt.country), remark(mt.remark), start(mt.start) {}

    string title;
    string company;
    string year;
    string country;
    string remark;
    RomType romType;
    string start;
};

static MediaDb* romdb;
static MediaDb* diskdb;
static MediaDb* casdb;
static RomType  romdbDefaultType = ROM_UNKNOWN;


static string parseCountryCode(const string& code)
{
    if (code == "SE" || code == "se") return "Sweden";
    if (code == "JP" || code == "jp") return "Japan";
    if (code == "KR" || code == "kr") return "Korea";
    if (code == "NL" || code == "nl") return "The Netherlands";
    if (code == "GB" || code == "gb") return "England";
    if (code == "FR" || code == "fr") return "France";
    if (code == "ES" || code == "es") return "Spain";
    if (code == "BR" || code == "br") return "Brazil";
    if (code == "MA" || code == "ma") return "Arabic";

    return code;
}

static RomType mediaDbStringToType(const std::string name)
{
    // Megaroms
    if (name == "ASCII16")          return ROM_ASCII16;
    if (name == "ASCII16SRAM2")     return ROM_ASCII16SRAM;
    if (name == "ASCII8")           return ROM_ASCII8;
    if (name == "ASCII8SRAM8")      return ROM_ASCII8SRAM;
    if (name == "KoeiSRAM8")        return ROM_KOEI;
    if (name == "KoeiSRAM32")       return ROM_KOEI;
    if (name == "Konami")           return ROM_KONAMI4;
    if (name == "KonamiSCC")        return ROM_KONAMI5;
    if (name == "Halnote")          return ROM_HALNOTE;
    if (name == "HarryFox")         return ROM_HARRYFOX;
    if (name == "HolyQuran")        return ROM_HOLYQURAN;
    if (name == "CrossBlaim")       return ROM_CROSSBLAIM;
    if (name == "Zemina80in1")      return ROM_KOREAN80;
    if (name == "Zemina90in1")      return ROM_KOREAN90;
    if (name == "Zemina126in1")     return ROM_KOREAN126;
    if (name == "Wizardry")         return ROM_ASCII8SRAM;
    if (name == "GameMaster2")      return ROM_GAMEMASTER2;
    if (name == "SuperLodeRunner")  return ROM_LODERUNNER;
    if (name == "R-Type")           return ROM_RTYPE;
    if (name == "Majutsushi")       return ROM_MAJUTSUSHI;
    if (name == "Synthesizer")      return ROM_KONAMISYNTH;
    if (name == "KeyboardMaster")   return ROM_KONAMKBDMAS;
    if (name == "GenericKonami")    return ROM_KONAMI4NF;
    if (name == "SuperPierrot")     return ROM_ASCII16NF;

    if (name == "Normal")           return ROM_STANDARD;

    // System roms
    if (name == "Bunsetsu")     return ROM_BUNSETU;
    if (name == "CasPatch")     return ROM_CASPATCH;
    if (name == "Coleco")       return ROM_COLECO;
    if (name == "FMPAC")        return ROM_FMPAC;
    if (name == "FMPAK")        return ROM_FMPAK;
    if (name == "DiskPatch")    return ROM_DISKPATCH;
    if (name == "fsa1fm1")      return ROM_UNKNOWN;
    if (name == "fsa1fm2")      return ROM_UNKNOWN;
    if (name == "Jisyo")        return ROM_JISYO;
    if (name == "Kanji1")       return ROM_KANJI;
    if (name == "Kanji12")      return ROM_KANJI12;
    if (name == "MB8877A")      return ROM_NATIONALFDC;
    if (name == "SVI738FDC")    return ROM_SVI738FDC;
    if (name == "TC8566AF")     return ROM_TC8566AF;
    if (name == "WD2793")       return ROM_PHILIPSFDC;
    if (name == "Microsol")     return ROM_MICROSOL;
    if (name == "MoonSound")    return ROM_MOONSOUND;

    if (name == "Panasonic16")  return ROM_PANASONIC16;
    if (name == "Panasonic32")  return ROM_PANASONIC32;
    if (name == "Standard16K")  return ROM_MSXDOS2;
    if (name == "SVI328CART")   return ROM_SVI328;
    if (name == "SVI80COL")     return ROM_SVI80COL;
    if (name == "SVI738FDC")    return ROM_SVI738FDC;
    if (name == "MSX-AUDIO")    return ROM_MSXAUDIO;
    if (name == "MSX-MUSIC")    return ROM_MSXMUSIC;
    if (name == "National")     return ROM_NATIONAL;
    if (name == "CX5M-MUSIC")   return ROM_UNKNOWN; // not implemented
    if (name == "FSA1FM1")      return ROM_UNKNOWN; // not implemented
    if (name == "FSA1FM2")      return ROM_UNKNOWN; // not implemented

    // Roms not supproted in this format in the db
    if (name == "0x4000")       return ROM_0x4000;
    if (name == "0xC000")       return ROM_0xC000;
    if (name == "auto")         return ROM_PLAIN;
    if (name == "basic")        return ROM_BASIC;

    return ROM_UNKNOWN;
}


static string mediaDbGetRemarks(TiXmlElement* dmp)
{
    string remark;

    for (TiXmlElement* it = dmp->FirstChildElement(); it != NULL; it = it->NextSiblingElement()) {
        if (strcmp(it->Value(), "remark") == 0) {
            for (TiXmlElement* i = it->FirstChildElement(); i != NULL; i = i->NextSiblingElement()) {
                if (strcmp(i->Value(), "text") == 0) {
                    TiXmlNode* name = i->FirstChild();
                    if (name != NULL) {
                        if (remark.length()) {
                            remark += "\n";
                        }
                        remark += name->Value();
                    }
                }
            }
        }
    }

    return remark;
}

static string mediaDbGetStart(TiXmlElement* dmp)
{
    string start;

    for (TiXmlElement* it = dmp->FirstChildElement(); it != NULL; it = it->NextSiblingElement()) {
        if (strcmp(it->Value(), "start") == 0) {
            for (TiXmlElement* i = it->FirstChildElement(); i != NULL; i = i->NextSiblingElement()) {
                if (strcmp(i->Value(), "text") == 0) {
                    TiXmlNode* name = i->FirstChild();
                    if (name != NULL) {
                        if (start.length()) {
                            start += "\n";
                        }
                        start += name->Value();
                    }
                }
            }
        }
    }
    return start;
}

static void mediaDbAddItem(MediaDb* mediaDb, TiXmlElement* dmp, const MediaType& mediaType)
{
    for (TiXmlElement* it = dmp->FirstChildElement(); it != NULL; it = it->NextSiblingElement()) {
        if (strcmp(it->Value(), "hash") == 0) {
            const char* type = it->Attribute("algo");
            if (type != NULL) {
                if (strcmp(type, "sha1") == 0) {
                    TiXmlNode* hash = it->FirstChild();
                    string sha1(hash->Value());
                    mediaDb->sha1Map[sha1] = new MediaType(mediaType);
//                    if (mediaDb == casdb) printf("Adding: %s: %s\n", mediaType.title.c_str(), sha1.c_str());
                }
                if (strcmp(type, "crc32") == 0) {
                    UInt32 crc32;
                    TiXmlNode* hash = it->FirstChild();
                    if (sscanf(hash->Value(), "%x", &crc32) == 1) {
                        mediaDb->crcMap[crc32] = new MediaType(mediaType);
                    }
                }
            }
        }
    }
}

static void mediaDbAddDump(TiXmlElement* dmp, 
                           string& title,
                           string& company,
                           string& country,
                           string& year,
                           string& system)
{
    if (strcmp(dmp->Value(), "megarom") == 0 || strcmp(dmp->Value(), "systemrom") == 0 || strcmp(dmp->Value(), "rom") == 0) {
        RomType romType = strcmp(dmp->Value(), "rom") == 0 ? ROM_PLAIN : ROM_UNKNOWN;

        for (TiXmlElement* it = dmp->FirstChildElement(); it != NULL; it = it->NextSiblingElement()) {
            if (strcmp(it->Value(), "type") == 0) {
                TiXmlNode* name = it->FirstChild();
                if (name != NULL) {
                    romType = mediaDbStringToType(name->Value());
                }
            }
        }

        if (strcmpnocase(system.c_str(), "coleco") == 0) {
            romType = ROM_COLECO;
        }

        if (strcmpnocase(system.c_str(), "svi") == 0) {
            romType = ROM_SVI328;
        }

        // For standard roms, a start tag is used to specify start address
        if (romType == ROM_STANDARD) {
            for (TiXmlElement* it = dmp->FirstChildElement(); it != NULL; it = it->NextSiblingElement()) {
                if (strcmp(it->Value(), "start") == 0) {
                    TiXmlNode* name = it->FirstChild();
                    if (name != NULL) {
                        if (strcmp(name->Value(), "0x0000") == 0) {
                            romType = ROM_STANDARD;
                        }
                        if (strcmp(name->Value(), "0x4000") == 0) {
                            romType = ROM_0x4000;
                        }
                        if (strcmp(name->Value(), "0x8000") == 0) {
                            romType = ROM_BASIC;
                        }
                        if (strcmp(name->Value(), "0xC000") == 0) {
                            romType = ROM_0xC000;
                        }
                    }
                }
            }
        }

        string remark = mediaDbGetRemarks(dmp);

        mediaDbAddItem(romdb, dmp, MediaType(romType, title, company, year, country, remark));
    }

    if (strcmp(dmp->Value(), "sccpluscart") == 0) {
        RomType romType = ROM_SCC;
        

        for (TiXmlElement* it = dmp->FirstChildElement(); it != NULL; it = it->NextSiblingElement()) {
            if (strcmp(it->Value(), "boot") == 0) {
                TiXmlNode* name = it->FirstChild();
                if (name != NULL && strcmp(name->Value(), "scc+") == 0) {
                    romType = ROM_SCCPLUS;
                }
            }
        }

        string remark = mediaDbGetRemarks(dmp);

        mediaDbAddItem(romdb, dmp, MediaType(romType, title, company, year, country, remark));
    }

    if (strcmp(dmp->Value(), "cas") == 0) {
        string start = mediaDbGetStart(dmp);
        string remark = mediaDbGetRemarks(dmp);

        for (TiXmlElement* itt = dmp->FirstChildElement(); itt != NULL; itt = itt->NextSiblingElement()) {
            if (strcmp(itt->Value(), "format") == 0) {
                const char* type = itt->Attribute("type");
                if (type != NULL && strcmp(type, "cas") == 0) {
                    mediaDbAddItem(casdb, itt, MediaType(ROM_UNKNOWN, title, company, year, country, remark, start));
                }
            }
        }
    }

    if (strcmp(dmp->Value(), "dsk") == 0) {
        string start = mediaDbGetStart(dmp);
        string remark = mediaDbGetRemarks(dmp);

        for (TiXmlElement* itt = dmp->FirstChildElement(); itt != NULL; itt = itt->NextSiblingElement()) {
            if (strcmp(itt->Value(), "format") == 0) {
                const char* type = itt->Attribute("type");
                if (type != NULL && strcmp(type, "dsk") == 0) {
                    mediaDbAddItem(diskdb, itt, MediaType(ROM_UNKNOWN, title, company, year, country, remark, start));
                }
            }
        }
    }
}

static void mediaDbAddFromXmlFile(const char* fileName) 
{
    static const char* rootTag = "softwaredb";

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
    
    for (TiXmlElement* sw = root->FirstChildElement(); sw != NULL; sw = sw->NextSiblingElement()) {
        if (strcmp(sw->Value(), "software") != 0) {
            continue;
        }

        string  title;
        string  company;
        string country;
        string  year;
        string  system;
        
        TiXmlElement* item;

        for (item = sw->FirstChildElement(); item != NULL; item = item->NextSiblingElement()) {
            if (strcmp(item->Value(), "system") == 0) {
                TiXmlNode* name = item->FirstChild();
                if (name != NULL) {
                    system = name->Value();
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
            if (strcmp(item->Value(), "country") == 0) {
                TiXmlNode* name = item->FirstChild();
                if (name != NULL) {
                    country = parseCountryCode(name->Value());
                }
            }
            if (strcmp(item->Value(), "year") == 0) {
                TiXmlNode* name = item->FirstChild();
                if (name != NULL) {
                    year = name->Value();
                }
            }
        }

        for (item = sw->FirstChildElement(); item != NULL; item = item->NextSiblingElement()) {
            if (strcmp(item->Value(), "dump") != 0) {
                continue;
            }
            
            string start;

            for (TiXmlElement* dmp = item->FirstChildElement(); dmp != NULL; dmp = dmp->NextSiblingElement()) {
                if (strcmp(dmp->Value(), "group") == 0) {
                    for (TiXmlElement* it = dmp->FirstChildElement(); it != NULL; it = it->NextSiblingElement()) {
                        mediaDbAddDump(it, title, company, country, year, system);
                    }
                    continue;
                }
                mediaDbAddDump(dmp, title, company, country, year, system);
            }
        }
    }
}

extern MediaType* mediaDbLookup(MediaDb* mediaDb, const void *buffer, int size)
{
	SHA1 sha1;
	sha1.update((const UInt8*)buffer, size);
    
//    printf("Lookup: %s\n", sha1.hex_digest().c_str());
    Sha1Map::iterator iterSha1 = mediaDb->sha1Map.find(sha1.hex_digest());
    if (iterSha1 != mediaDb->sha1Map.end()) {
        return iterSha1->second;
    }

    UInt32 crc = crc32(buffer, size);

    CrcMap::iterator iterCrc = mediaDb->crcMap.find(crc);
    if (iterCrc != mediaDb->crcMap.end()) {
        return iterCrc->second;
    }
    
    return NULL;
}

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
    if (name == "0xC000")       return ROM_0xC000;
    if (name == "konamisynth")  return ROM_KONAMISYNTH;
    if (name == "kbdmaster")    return ROM_KONAMKBDMAS;
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
    if (name == "fmpak")        return ROM_FMPAK;
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
    case ROM_KONAMI5:     return "Konami SCC";
    case ROM_KONAMI4:     return "Konami";
    case ROM_ASCII8:      return "ASCII 8";
    case ROM_ASCII16:     return "ASCII 16";
    case ROM_GAMEMASTER2: return "Game Master 2 (SRAM)";
    case ROM_ASCII8SRAM:  return "ASCII 8 (SRAM)";
    case ROM_ASCII16SRAM: return "ASCII 16 (SRAM)";
    case ROM_RTYPE:       return "R-Type";
    case ROM_CROSSBLAIM:  return "Cross Blaim";
    case ROM_HARRYFOX:    return "Harry Fox";
    case ROM_MAJUTSUSHI:  return "Konami Majutsushi";
    case ROM_KOREAN80:    return "Zemina 80 in 1";
    case ROM_KOREAN90:    return "Zemina 90 in 1";
    case ROM_KOREAN126:   return "Zemina 126 in 1";
    case ROM_SCC:         return "SCC";
    case ROM_SCCPLUS:     return "SCC+";
    case ROM_SNATCHER:    return "The Snatcher";
    case ROM_SDSNATCHER:  return "SD Snatcher";
    case ROM_SCCMIRRORED: return "SCC mirrored";
    case ROM_SCCEXTENDED: return "SCC extended";
    case ROM_FMPAC:       return "FMPAC (SRAM)";
    case ROM_FMPAK:       return "FMPAK";
    case ROM_KONAMI4NF:   return "Konami Generic";
    case ROM_ASCII16NF:   return "Super Pierrot";
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
    case ROM_TURBORIO:    return "Turbo-R Pause";
    case ROM_F4DEVICE:    return "F4 Device Normal";
    case ROM_F4INVERTED:  return "F4 Device Inverted";
    case ROM_MSXMIDI:     return "MSX-MIDI";
    case ROM_TURBORTIMER: return "Turbo-R Timer";
    case AUDIO_MOONSOUND: return "Moonsound Audio";
    case AUDIO_Y8950:     return "Y8950 Audio";
    case AUDIO_YM2413:    return "YM2413 Audio";
    case ROM_KOEI:        return "Koei (SRAM)";
    case ROM_BASIC:       return "Basic ROM";
    case ROM_HALNOTE:     return "Halnote";
    case ROM_LODERUNNER:  return "Lode Runner";
    case ROM_0x4000:      return "Normal 0x4000";
    case ROM_0xC000:      return "Normal 0xC000";
    case ROM_KONAMISYNTH: return "Konami Synthesizer";
    case ROM_KONAMKBDMAS: return "Konami Keyboard Master";
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

    case ROM_UNKNOWN:     return langUnknown();
    }

    return langUnknown();
}

extern "C" const char* romTypeToShortString(RomType romType) 
{
    switch (romType) {
    case ROM_STANDARD:    return "STANDARD";
    case ROM_MSXDOS2:     return "MSXDOS2";
    case ROM_KONAMI5:     return "KONAMI SCC";
    case ROM_KONAMI4:     return "KONAMI";
    case ROM_ASCII8:      return "ASCII8";
    case ROM_ASCII16:     return "ASCII16";
    case ROM_GAMEMASTER2: return "GMASTER2";
    case ROM_ASCII8SRAM:  return "ASCII8SRAM";
    case ROM_ASCII16SRAM: return "ASCII16SRAM";
    case ROM_RTYPE:       return "R-TYPE";
    case ROM_CROSSBLAIM:  return "CROSSBLAIM";
    case ROM_HARRYFOX:    return "HARRYFOX";
    case ROM_KOREAN80:    return "ZEM 80IN1";
    case ROM_KOREAN126:   return "ZEM 126IN1";
    case ROM_KOREAN90:    return "ZEM 90IN1";
    case ROM_SCC:         return "SCC";
    case ROM_SCCPLUS:     return "SCC+";
    case ROM_SNATCHER:    return "SNATCHER";
    case ROM_SDSNATCHER:  return "SDSNATCHER";
    case ROM_SCCMIRRORED: return "SCCMIRRORED";
    case ROM_SCCEXTENDED: return "SCCEXTENDED";
    case ROM_FMPAC:       return "FMPAC";
    case ROM_FMPAK:       return "FMPAK";
    case ROM_KONAMI4NF:   return "KONAMI GEN";
    case ROM_ASCII16NF:   return "SUPERPIERR";
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
    case ROM_TURBORIO:    return "TR PAUSE";
    case ROM_F4DEVICE:    return "F4NORMAL";
    case ROM_F4INVERTED:  return "F4INV";
    case ROM_MSXMIDI:     return "MSX-MIDI";
    case ROM_TURBORTIMER: return "TURBORTMR";
    case AUDIO_MOONSOUND: return "MOONSOUND";
    case AUDIO_Y8950:     return "Y8950";
    case AUDIO_YM2413:    return "YM2413";
    case ROM_KOEI:        return "KOEI";
    case ROM_BASIC:       return "BASIC";
    case ROM_HALNOTE:     return "HALNOTE";
    case ROM_LODERUNNER:  return "LODERUNNER";
    case ROM_0x4000:      return "0x4000";
    case ROM_0xC000:      return "0xC000";
    case ROM_KONAMISYNTH: return "KONSYNTH";
    case ROM_KONAMKBDMAS: return "KBDMASTER";
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

extern "C" void mediaDbLoad(const char* directory)
{
    if (romdb == NULL) {
        romdb = new MediaDb;
    }
    if (diskdb == NULL) {
        diskdb = new MediaDb;
    }
    if (casdb == NULL) {
        casdb = new MediaDb;
    }

    string path = directory;
    path += "\\";

    string searchPath = path + "*.xml";
    WIN32_FIND_DATA wfd;
    HANDLE handle = FindFirstFile(searchPath.c_str(), &wfd);

    if (handle != INVALID_HANDLE_VALUE) {
        do {
            string filename = path + wfd.cFileName;
            mediaDbAddFromXmlFile(filename.c_str());
        } while (FindNextFile(handle, &wfd));

    	FindClose(handle);
    }
}

extern "C" MediaType* mediaDbLookupRom(const void *buffer, int size) 
{
    const char* romData = (const char*)buffer;
    static MediaType defaultColeco(ROM_COLECO, "Unknown Coleco rom");
    static MediaType defaultSvi(ROM_SVI328, "Unknown SVI rom");

    if (romdb == NULL) {
        return NULL;
    }
    MediaType* mediaType = mediaDbLookup(romdb, buffer, size);

    if (mediaType == NULL &&
        size <= 0x8000 && (unsigned char)romData[0] == 0xF3 && romData[1] == 0x31)
    {
        mediaType = &defaultSvi;
    }

    if (mediaType == NULL &&
        size <= 0x8000 && (unsigned char)romData[0] == 0x55 && (unsigned char)romData[1] == 0xAA) 
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

RomType mediaDbGetRomType(MediaType* mediaType)
{
    return mediaType->romType;
}

extern "C" const char* mediaDbGetTitle(MediaType* mediaType)
{
    return mediaType->title.c_str();
}

extern "C" const char* mediaDbGetYear(MediaType* mediaType)
{
    return mediaType->year.c_str();
}

extern "C" const char* mediaDbGetCompany(MediaType* mediaType)
{
    return mediaType->company.c_str();
}

extern "C" const char* mediaDbGetRemark(MediaType* mediaType)
{
    return mediaType->remark.c_str();
}

extern "C" const char* mediaDbGetPrettyString(MediaType* mediaType)
{
    static char prettyString[512];

    prettyString[0] = 0;

    if (mediaType != NULL) {
        strcat(prettyString, mediaType->title.c_str());
        if (mediaType->company.length() || mediaType->year.length() || mediaType->country.length()) {
            strcat(prettyString, " -");
        }
            
        if (mediaType->company.length()) {
            strcat(prettyString, " ");
            strcat(prettyString, mediaType->company.c_str());
        }

        if (mediaType->year.length()) {
            strcat(prettyString, " ");
            strcat(prettyString, mediaType->year.c_str());
        }

        if (mediaType->country.length()) {
            strcat(prettyString, " ");
            strcat(prettyString, mediaType->country.c_str());
        }

        if (mediaType->remark.length()) {
            std::string remark = " : ";
            for (int i = 0; mediaType->remark[i] != '\r' && mediaType->remark[i] != '\n' && mediaType->remark[i] != '\0'; i++) {
                remark += mediaType->remark[i];
            }
            int remarkLength = 35 - mediaType->start.length();
            if (remarkLength > 0) {
                if (remark.length() > 35) {
                    remark = remark.substr(0, 35) + "...";
                }
                strcat(prettyString, remark.c_str());
            }
        }
        
        if (mediaType->start.length()) {
            strcat(prettyString, " [ ");
            strcat(prettyString, mediaType->start.c_str());
            strcat(prettyString, " ]");
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
    static MediaType staticMediaType(ROM_UNKNOWN, "Unknown MSX rom");

    const UInt8* romData = (const UInt8*)buffer;
    int i;
    int mapper;
    UInt32 counters[6] = { 0, 0, 0, 0, 0, 0 };

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
//			if (init == 0 && (text & 0xc000) == 0x8000) {
			if ((text & 0xc000) == 0x8000) {
                mediaType->romType = ROM_BASIC;
			    return mediaType;
			}
		}
        mediaType->romType = ROM_PLAIN;
		return mediaType;
	}

    /* Count occurences of characteristic addresses */
    for (i = 0; i < size - 3; i++) {
        if (romData[i] == 0x32) {
            UInt32 value = romData[i + 1] + ((UInt32)romData[i + 2] << 8);

            switch(value) {
            case 0x4000: 
            case 0x8000: 
            case 0xa000: 
                counters[3]++;
                break;

            case 0x5000: 
            case 0x9000: 
            case 0xb000: 
                counters[2]++;
                break;

            case 0x6000: 
                counters[3]++;
                counters[4]++;
                counters[5]++;
                break;

            case 0x6800: 
            case 0x7800: 
                counters[4]++;
                break;

            case 0x7000: 
                counters[2]++;
                counters[4]++;
                counters[5]++;
                break;

            case 0x77ff: 
                counters[5]++;
                break;
            }
        }
    }

    /* Find which mapper type got more hits */
    mapper = 0;

    counters[4] -= counters[4] ? 1 : 0;

	for (i = 0; i <= 5; i++) {
		if (counters[i] > 0 && counters[i] >= counters[mapper]) {
			mapper = i;
		}
	}

    if (mapper == 5 && counters[0] == counters[5]) {
		mapper = 0;
	}

    switch (mapper) {
    default:
    case 0: mediaType->romType = ROM_STANDARD; break;
    case 1: mediaType->romType = ROM_MSXDOS2; break;
    case 2: mediaType->romType = ROM_KONAMI5; break;
    case 3: mediaType->romType = ROM_KONAMI4; break;
    case 4: mediaType->romType = ROM_ASCII8; break;
    case 5: mediaType->romType = ROM_ASCII16; break;
    }
    
    return mediaType;
}



















/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

void mediaDbAddFromOldFile(MediaDb* mediaDb, 
                           const char* fileName, OldFormat format) 
{
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        return;
    }

    char buffer[1024];
    while (fgets(buffer, 1024, file)) {
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
        
        if (title.length() > 10 && title[title.length() - 1] == ']' && title[title.length() - 10] == '[') {
            title = title.substr(0, title.length() - 10);
        }

        if (mediaDb->crcMap.find(crc32) == mediaDb->crcMap.end()) {
            mediaDb->crcMap[crc32] = new MediaType(romType, title);
        }
    }
}


extern "C" void mediaDbCreateRomdb(const char* oldFileName)
{
    if (romdb == NULL) {
        romdb = new MediaDb;
    }

    mediaDbAddFromOldFile(romdb, oldFileName, FORMAT_ROM);
}

extern "C" void mediaDbCreateDiskdb(const char* oldFileName)
{
    if (diskdb == NULL) {
        diskdb = new MediaDb;
    }

    mediaDbAddFromOldFile(diskdb, oldFileName, FORMAT_DISK);
}

extern "C" void mediaDbCreateCasdb(const char* oldFileName)
{
    if (casdb == NULL) {
        casdb = new MediaDb;
    }

    mediaDbAddFromOldFile(casdb, oldFileName, FORMAT_CAS);
}
