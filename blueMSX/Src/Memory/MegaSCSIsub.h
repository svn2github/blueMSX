/*
 * $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Memory/MegaSCSIsub.h,v $
 *
 * $Revision: 1.5 $
 *
 * $Date: 2007-03-24 05:20:37 $
 *
 * Copyright (C) 2007 white cat
 *
 */
#ifndef MEGASCSISUB_H
#define MEGASCSISUB_H

#include "MsxTypes.h"
#include "MB89352.h"

#define REG_DREG 10

// CD_UPDATE: Dynnamically create parameter table and select correct
//            parameters based on inserted disk
const SCSICREATE* getMegaSCSIparm(int hdId);
int EseRamSize(int size);

#endif
