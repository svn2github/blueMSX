/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/Disk.c,v $
**
** $Revision: 1.7 $
**
** $Date: 2004-12-20 21:03:50 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vik, Tomas Karlsson
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
#include "Disk.h"
#include "DirAsDisk.h"
#include "Board.h"
#include "ziphelper.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

#define MAXSECTOR (2 * 9 * 81)

static int   drivesEnabled[2] = { 1, 1 };
static FILE* drives[2];
static int   RdOnly[2];
static char* ramImageBuffer[2];
static int   ramImageSize[2];
static int   sectorsPerTrack[2];
static int   fileSize[2];
static int   sides[2];
static int   tracks[2];
static int   changed[2];


UInt8 diskEnabled(int driveId)
{
    return driveId >= 0 && driveId < MAXDRIVES && drivesEnabled[driveId];
}

void  diskEnable(int driveId, int enable)
{
    if (driveId >= 0 && driveId < MAXDRIVES)
        drivesEnabled[driveId] = enable;
}

UInt8 diskPresent(int driveId)
{
    return driveId >= 0 && driveId < MAXDRIVES && 
        (drives[driveId] != NULL || ramImageBuffer[driveId] != NULL);
}

int diskGetSectorsPerTrack(int driveId)
{
    if (driveId < MAXDRIVES)
        return sectorsPerTrack[driveId];

    return 0;
}

int diskGetSides(int driveId)
{
    if (driveId < MAXDRIVES)
        return sides[driveId];

    return 0;
}

int diskGetSectorSize(int driveId, int side, int track, int density)
{
    int secSize;

    if (driveId >= MAXDRIVES)
        return 0;

    if (boardGetType() == BOARD_SVI) {
        secSize = (track==0 && side==0 && density==1) ? 128 : 256;
    }
    else {
        secSize = 512;
    }

    return secSize;
}

static int diskGetSectorOffset(int driveId, int sector, int side, int track, int density)
{
    int offset;
    int secSize;

    if (driveId >= MAXDRIVES)
        return 0;

    secSize = diskGetSectorSize(driveId, side, track, density);

    if (boardGetType() == BOARD_SVI) {
        if (track==0 && side==0 && density==1)
            offset = (sector-1)*128; 
        else
            offset = ((track*sides[driveId]+side)*17+sector-1)*256-2048;
    }
    else {
        offset =  sector - 1 + diskGetSectorsPerTrack(driveId) * (track * diskGetSides(driveId) + side);
        offset *= secSize;
    }
    return offset;
}

int diskChanged(int driveId)
{
    if (driveId < MAXDRIVES) {
        int isChanged = changed[driveId];
        changed[driveId] = 0;

        return isChanged;
    }

    return 0;
}

UInt8 diskRead(int driveId, UInt8* buffer, int sector)
{
    if (driveId >= MAXDRIVES)
        return 0;

    if (ramImageBuffer[driveId] != NULL) {
        int offset = sector * 512;

        if (ramImageSize[driveId] < offset + 512) {
            return 0;
        }

        memcpy(buffer, ramImageBuffer[driveId] + offset, 512);
        return 1;
    }
    else {
        if ((drives[driveId] != NULL)) {
            if (0 == fseek(drives[driveId], sector * 512, SEEK_SET)) {
                UInt8 success = fread(buffer, 1, 512, drives[driveId]) == 512;
                return success;
            }
        }
    }
    return 0;
}

UInt8 diskReadSector(int driveId, UInt8* buffer, int sector, int side, int track, int density, int *sectorSize)
{
    int secSize;
    int offset;

    if (driveId >= MAXDRIVES)
        return 0;

    offset = diskGetSectorOffset(driveId, sector, side, track, density);
    secSize = diskGetSectorSize(driveId, side, track, density);

    *sectorSize = secSize;

    if (ramImageBuffer[driveId] != NULL) {
        if (ramImageSize[driveId] < offset + secSize) {
            return 0;
        }

        memcpy(buffer, ramImageBuffer[driveId] + offset, secSize);
        return 1;
    }
    else {
        if ((drives[driveId] != NULL)) {
            if (0 == fseek(drives[driveId], offset, SEEK_SET)) {
                UInt8 success = fread(buffer, 1, secSize, drives[driveId]) == secSize;
                return success;
            }
        }
    }

    return 0;
}

static void diskUpdateInfo(int driveId) 
{
	UInt8 buf[512];
    int sectorSize;
    int rv;

    sectorsPerTrack[driveId] = 9;
    sides[driveId]           = 2;
    tracks[driveId]          = 80;
    changed[driveId]         = 1;

    if (fileSize[driveId] / 512 == 1440) {
        return;
    }

    rv = diskReadSector(driveId, buf, 1, 0, 0, 512, &sectorSize);
    if (!rv) {
        return;
    }

    if (buf[0] ==0xeb) {
        switch (buf[0x15]) {
        case 0xf8:
	        sides[driveId]           = 1;
            tracks[driveId]          = 80;
	        sectorsPerTrack[driveId] = 9;
            return;
        case 0xf9:
	        sides[driveId]           = 2;
            tracks[driveId]          = 80;
	        sectorsPerTrack[driveId] = 9;
            // This check is needed to get the SVI dos disks to work
            // Maybe it should be applied to other cases as well
            rv = diskReadSector(driveId, buf, 2, 0, 0, 512, &sectorSize);
            if (rv && buf[0] == 0xf8) {
	            sides[driveId] = 1;
            }
            return;
        case 0xfa:
	        sides[driveId]           = 1;
            tracks[driveId]          = 80;
	        sectorsPerTrack[driveId] = 8;
            return;
        case 0xfb:
	        sides[driveId]           = 2;
            tracks[driveId]          = 80;
	        sectorsPerTrack[driveId] = 8;
            return;
        case 0xfc:
	        sides[driveId]           = 1;
            tracks[driveId]          = 40;
	        sectorsPerTrack[driveId] = 9;
            return;
        case 0xfd:
	        sides[driveId]           = 2;
            tracks[driveId]          = 40;
	        sectorsPerTrack[driveId] = 9;
            return;
        case 0xfe:
	        sides[driveId]           = 1;
            tracks[driveId]          = 40;
	        sectorsPerTrack[driveId] = 8;
            return;
        case 0xff:
	        sides[driveId]           = 2;
            tracks[driveId]          = 40;
	        sectorsPerTrack[driveId] = 8;
            return;
        }
    }
    
    if ((buf[0] == 0xe9) || (buf[0] ==0xeb)) {
	    sectorsPerTrack[driveId] = buf[0x18] + 256 * buf[0x19];
	    sides[driveId]           = buf[0x1a] + 256 * buf[0x1b];
    }
    else {
        rv = diskReadSector(driveId, buf, 2, 0, 0, 512, &sectorSize);
        if (!rv) {
            return;
        }
		if (buf[0] >= 0xF8) {
			sectorsPerTrack[driveId] = (buf[0] & 2) ? 8 : 9;
			sides[driveId]           = (buf[0] & 1) ? 2 : 1;
		}
    }

    if (sectorsPerTrack[driveId] == 0  || sides[driveId] == 0 || 
        sectorsPerTrack[driveId] > 255 || sides[driveId] > 2) 
    {
    	switch (fileSize[driveId]) {
        case 327680:  /* 80 tracks, 1 side, 8 sectors/track */
	        sectorsPerTrack[driveId] = 8;
	        sides[driveId] = 1;
            break;
        case 368640:  /* 80 tracks, 1 side, 9 sectors/track */
	        sectorsPerTrack[driveId] = 9;
	        sides[driveId] = 1;
            break;
        case 655360:  /* 80 tracks, 2 side, 8 sectors/track */
	        sectorsPerTrack[driveId] = 8;
	        sides[driveId] = 2;
            break;
        default:
            sectorsPerTrack[driveId] = 9;
            sides[driveId]           = 2;
        }
    }
}

UInt8 diskWrite(int driveId, UInt8 *buffer, int sector)
{
    if (driveId >= MAXDRIVES) {
        return 0;
    }

    if (sector >= MAXSECTOR) {
        return 0;
    }

    if (ramImageBuffer[driveId] != NULL) {
        int offset = sector * 512;

        if (ramImageSize[driveId] < offset + 512) {
            return 0;
        }

        memcpy(ramImageBuffer[driveId] + offset, buffer, 512);
        return 1;
    }
    else {
        if (drives[driveId] != NULL && !RdOnly[driveId]) {
            if (0 == fseek(drives[driveId], sector * 512, SEEK_SET)) {
                UInt8 success = fwrite(buffer, 1, 512, drives[driveId]) == 512;
                if (success && sector == 0) {
                    diskUpdateInfo(driveId);
                }
                return success;
            }
        }
    }
    return 0;
}

UInt8 diskWriteSector(int driveId, UInt8 *buffer, int sector, int side, int track, int density)
{
    int secSize;
    int offset;

    if (driveId >= MAXDRIVES)
        return 0;

    if (sector >= MAXSECTOR)
        return 0;

    offset = diskGetSectorOffset(driveId, sector, side, track, density);
    secSize = diskGetSectorSize(driveId, side, track, density);

    if (ramImageBuffer[driveId] != NULL) {
        if (ramImageSize[driveId] < offset + secSize) {
            return 0;
        }

        memcpy(ramImageBuffer[driveId] + offset, buffer, secSize);
        return 1;
    }
    else {
        if (drives[driveId] != NULL && !RdOnly[driveId]) {
            if (0 == fseek(drives[driveId], offset, SEEK_SET)) {
                UInt8 success = fwrite(buffer, 1, secSize, drives[driveId]) == secSize;
                return success;
            }
        }
    }
    return 0;
}


static int diskCheckSize(int driveId, int dskImageSize)
{
    fileSize[driveId] = dskImageSize;

    if (boardGetType() == BOARD_SVI) {
        switch (dskImageSize) {
        case 172032:	/* Single sided */
            sides[driveId] = 1;
            return 1;
        case 346112:	/* Double sided */
            sides[driveId] = 2;
            return 1;
        default:
            return 0;
        }
	}
    else {
        diskUpdateInfo(driveId);
        return 1;
    }
}

UInt8 diskChange(int driveId, char* fileName, const char* fileInZipFile)
{
    struct stat s;
    int rv;

    if (driveId >= MAXDRIVES)
        return 0;

    /* Close previous disk image */
    if(drives[driveId] != NULL) { 
        fclose(drives[driveId]);
        drives[driveId] = NULL; 
    }

    if (ramImageBuffer[driveId] != NULL) {
        // Flush to file??
        free(ramImageBuffer[driveId]);
        ramImageBuffer[driveId] = NULL;
    }

    if(!fileName) {
        return 1;
    }

    rv = stat(fileName, &s);
    if (rv == 0) {
        if (s.st_mode & S_IFDIR) {
            if (boardGetType() == BOARD_SVI) {
                return 1;
            }
            else {
                ramImageBuffer[driveId] = dirLoadFile(fileName, &ramImageSize[driveId]);
                diskCheckSize(driveId, ramImageSize[driveId]);
                return ramImageBuffer[driveId] != NULL;
            }
        }
    }

    if (fileInZipFile != NULL) {
        ramImageBuffer[driveId] = zipLoadFile(fileName, fileInZipFile, &ramImageSize[driveId]);
        diskCheckSize(driveId, ramImageSize[driveId]);
        return ramImageBuffer[driveId] != NULL;
    }

    drives[driveId] = fopen(fileName, "r+b");
    RdOnly[driveId] = 0;

    if (drives[driveId] == NULL) {
        drives[driveId] = fopen(fileName, "rb");
        RdOnly[driveId] = 1;
    }

    if (drives[driveId] == NULL) {
        return 0;
    }

    fseek(drives[driveId],0,SEEK_END);
    if (!diskCheckSize(driveId, ftell(drives[driveId]))) {
        fclose(drives[driveId]);
        drives[driveId] = NULL;
    }

    diskUpdateInfo(driveId);

    return 1;
}
