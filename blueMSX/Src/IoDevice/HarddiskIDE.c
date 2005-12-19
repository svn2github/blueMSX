/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/HarddiskIDE.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2005-12-19 21:50:47 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2004 Daniel Vik
**
**  This software is provhdd 'as-is', without any express or implied
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
#include "HarddiskIde.h"
#include "Board.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define STATUS_ERR  0x01
#define STATUS_DRQ  0x08
#define STATUS_DSC  0x10
#define STATUS_DRDY 0x40


static const UInt8 defaultIdentifyBlock[512] = {
    0x5a,0x0c,0xba,0x09,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x3f,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x31,0x20,0x00,0x00,0x00,0x01,0x04,0x00,0x31,0x56,
    0x30,0x2e,0x20,0x20,0x20,0x20,0x50,0x4f,0x4e,0x45,0x4d,0x20,0x58,0x53,0x48,0x20,
    0x52,0x41,0x20,0x44,0x49,0x44,0x4b,0x53,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x10,0x80,
    0x00,0x00,0x00,0x0b,0x00,0x00,0x00,0x02,0x00,0x02,0x03,0x00,0xba,0x09,0x10,0x00,
    0x3f,0x00,0x60,0x4c,0x26,0x00,0x00,0x00,0xe0,0x53,0x26,0x00,0x07,0x00,0x07,0x04,
    0x03,0x00,0x78,0x00,0x78,0x00,0xf0,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

struct HarddiskIde {
    UInt8 errorReg;
    UInt8 sectorCountReg;
    UInt8 sectorNumReg;
    UInt8 cylinderLowReg;
    UInt8 cylinderHighReg;
    UInt8 devHeadReg;
    UInt8 statusReg;
    UInt8 featureReg;
    
    int totalSectors;
    int transferRead;
    int transferWrite;
    UInt32 transferCount;
    UInt32 transferSectorNumber;

    int   sectorDataOffset;
    UInt8 identifyBlock[512];
    UInt8 sectorData[512 * 256];

    FILE* file;
};


static void setTransferRead(HarddiskIde* hd, int status)
{
    if (status != hd->transferRead) {
        hd->transferRead = status;
    }
}

static void setTransferWrite(HarddiskIde* hd, int status)
{
    if (status != hd->transferWrite) {
        hd->transferWrite = status;
    }
}

static UInt32 getSectorNumber(HarddiskIde* hd)
{
    return hd->sectorNumReg | (hd->cylinderLowReg << 8) |
        (hd->cylinderHighReg << 16) | ((hd->devHeadReg & 0x0f) << 24);
}

static void setError(HarddiskIde* hd, UInt8 error)
{
    hd->errorReg = error;
    hd->statusReg |= STATUS_ERR;
    hd->statusReg &= ~STATUS_DRQ;
    setTransferWrite(hd, 0);
    setTransferRead(hd, 0);
}

static UInt32 getNumSectors(HarddiskIde* hd)
{
    return hd->sectorCountReg == 0 ? 256 : hd->sectorCountReg;
}

static int readLogicalSector(HarddiskIde* hd, UInt32 sector, UInt8* buf)
{
    if (fseek(hd->file, 512 * sector, SEEK_SET) != 0) {
        return 0;
    }
    return fread(buf, 1, 512, hd->file) == 512;
}

static int writeLogicalSector(HarddiskIde* hd, UInt32 sector, const UInt8* buf)
{
    if (fseek(hd->file, 512 * sector, SEEK_SET) != 0) {
        return 0;
    }
    return fwrite(buf, 1, 512, hd->file) == 512;
}

static void executeCommand(HarddiskIde* hd, UInt8 cmd)
{
    hd->statusReg &= ~(STATUS_DRQ | STATUS_ERR);
    setTransferRead(hd, 0);
    setTransferWrite(hd, 0);
    switch (cmd) {
    case 0xef: // Set Feature
        if (hd->featureReg != 0x03) {
            setError(hd, 0x04);
        }
        break;

    case 0xec: // ATA Identify Device
        hd->transferCount = 512/2;
        hd->sectorDataOffset = -512;
        setTransferRead(hd, 1);
        hd->statusReg |= STATUS_DRQ;
        break;

    case 0x91:
        break;

    case 0x30: { // Write Sector
        int sectorNumber = getSectorNumber(hd);
        int numSectors = getNumSectors(hd);
        if ((sectorNumber + numSectors) > hd->totalSectors) {
            setError(hd, 0x14);
            break;
        }
        hd->transferSectorNumber = sectorNumber;
        hd->transferCount = 512/2 * numSectors;
        hd->sectorDataOffset = 0;
        setTransferWrite(hd, 1);
        hd->statusReg |= STATUS_DRQ;
        break;
    }
    case 0x20: { // Read Sector
        int sectorNumber = getSectorNumber(hd);
        int numSectors = getNumSectors(hd);
        int i;

        if ((sectorNumber + numSectors) > hd->totalSectors) {
            setError(hd, 0x14);
            break;
        }
          
        for (i = 0; i < numSectors; i++) {
            if (!readLogicalSector(hd, sectorNumber + i, hd->sectorData + i * 512 + 512)) {
                break;
            }
        }
        if (i != numSectors) {
            setError(hd, 0x44);
            break;
        }

        hd->transferCount = 512/2 * numSectors;
        hd->sectorDataOffset = 0;
        setTransferRead(hd, 1);
        hd->statusReg |= STATUS_DRQ;
        break;
    }
    default: // all others
        setError(hd, 0x04);
    }
}

void harddiskIdeReset(HarddiskIde* hd)
{
    hd->errorReg = 0x01;
    hd->sectorCountReg = 0x01;
    hd->sectorNumReg = 0x01;
    hd->cylinderLowReg = 0x00;
    hd->cylinderHighReg = 0x00;
    hd->devHeadReg = 0x00;
    hd->statusReg = STATUS_DSC | STATUS_DRDY;
    hd->featureReg = 0x00;
    setTransferRead(hd, 0);
    setTransferWrite(hd, 0);
}

UInt16 harddiskIdeRead(HarddiskIde* hd)
{
    UInt16 value;

    if (!hd->transferRead) {
        return 0x7f7f;
    }

    value  = hd->sectorData[hd->sectorDataOffset++];
    value |= hd->sectorData[hd->sectorDataOffset++] << 8;
    if (--hd->transferCount == 0) {
        setTransferRead(hd, 0);
        hd->statusReg &= ~STATUS_DRQ;
    }
    return value;
}

void harddiskIdeWrite(HarddiskIde* hd, UInt16 value)
{
    if (!hd->transferWrite) {
        return;
    }

    hd->sectorData[hd->sectorDataOffset++] = value & 0xff;
    hd->sectorData[hd->sectorDataOffset++] = value >> 8;
    hd->transferCount--;
    if ((hd->transferCount & 255) == 0) {
        if (!writeLogicalSector(hd, hd->transferSectorNumber, hd->sectorData + 512)) {
            setError(hd, 0x44);
            setTransferWrite(hd, 0);
            return;
        }
        hd->transferSectorNumber++;
        hd->sectorDataOffset = 0;
    }
    if (hd->transferCount == 0) {
        setTransferWrite(hd, 0);
        hd->statusReg &= ~STATUS_DRQ;
    }
}

UInt8 harddiskIdeReadRegister(HarddiskIde* hd, UInt8 reg)
{
    switch (reg) {
    case 1:
        return hd->errorReg;
    case 2: 
        return hd->sectorCountReg;
    case 3: 
        return hd->sectorNumReg;
    case 4: 
        return hd->cylinderLowReg;
    case 5: 
        return hd->cylinderHighReg;
    case 6: 
        return hd->devHeadReg;
    case 7: 
        return hd->statusReg;
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 15:
        return 0x7f;
    }

    return 0x7f;
}

void harddiskIdeWriteRegister(HarddiskIde* hd, UInt8 reg, UInt8 value)
{
    switch (reg) {
    case 1:
        hd->featureReg = value;
        break;
    case 2:
        hd->sectorCountReg = value;
        break;
    case 3:
        hd->sectorNumReg = value;
        break;
    case 4:
        hd->cylinderLowReg = value;
        break;
    case 5:
        hd->cylinderHighReg = value;
        break;
    case 6:
        hd->devHeadReg = value;
        break;
    case 7:
        executeCommand(hd, value);
        break;
    }
}

void harddiskIdeLoadState(HarddiskIde* hd)
{
    SaveState* state = saveStateOpenForRead("harddiskIde");

    saveStateClose(state);
}

void harddiskIdeSaveState(HarddiskIde* hd)
{
    SaveState* state = saveStateOpenForWrite("harddiskIde");

    saveStateClose(state);
}

HarddiskIde* harddiskIdeCreate(const char* fileName)
{
    UInt32 fileSize;

    FILE* file = fopen(fileName, "w+");
    if (file == NULL) {
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    if (fileSize < 1024 * 1024) {
        fclose(file);
        return NULL;
    }
    else {
        HarddiskIde* hd = malloc(sizeof(HarddiskIde));

        UInt16 totalSectors = (UInt16)(fileSize / 512);
        UInt16 heads = 16;
        UInt16 sectors = 32;
        UInt16 cylinders = totalSectors / (heads * sectors);
        
        memcpy(hd->identifyBlock, defaultIdentifyBlock, 512);

        hd->identifyBlock[0x02] = cylinders & 0xff;
        hd->identifyBlock[0x03] = cylinders >> 8;
        hd->identifyBlock[0x06] = heads & 0xff;
        hd->identifyBlock[0x07] = heads >> 8;
        hd->identifyBlock[0x0c] = sectors & 0xff;
        hd->identifyBlock[0x0d] = sectors >> 8;

        hd->identifyBlock[0x78] = (totalSectors & 0x000000ff) >>  0;
        hd->identifyBlock[0x79] = (totalSectors & 0x0000ff00) >>  8;
        hd->identifyBlock[0x7a] = (totalSectors & 0x00ff0000) >> 16;
        hd->identifyBlock[0x7b] = (totalSectors & 0xff000000) >> 24;

        hd->totalSectors = totalSectors;
        hd->transferRead = 0;
        hd->transferWrite = 0;

        harddiskIdeReset(hd);

        return hd;
    }
}

void harddiskIdeDestroy(HarddiskIde* hd)
{
    fclose(hd->file);
    free(hd);
}
