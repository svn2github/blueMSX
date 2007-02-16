/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/ft245.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2007-02-16 22:24:21 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003-2006 Daniel Vik
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
******************************************************************************
*/
#include "ft245.h"
#include "Board.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>

typedef struct FT245
{
    int dummy;
};


void ft245SaveState(FT245* ft)
{
}

void ft245LoadState(FT245* ft)
{
}

FT245* ft245Create()
{
    FT245* ft = malloc(sizeof(FT245));

    return ft;
}

void ft245Destroy(FT245* ft)
{
    free(ft);
}

void ft245Reset(FT245* ft)
{
}

UInt8 ft245Read(FT245* ft)
{
    return 0xff;
}

UInt8 ft245Peek(FT245* ft)
{
    return 0xff;
}

UInt8 ft245GetTxe(FT245* ft)
{
    return 0;
}

UInt8 ft245GetRxf(FT245* ft)
{
    return 0;
}

void ft245Write(FT245* ft, UInt8 value)
{
}
