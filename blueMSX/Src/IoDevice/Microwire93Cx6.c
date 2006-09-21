/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/IoDevice/Microwire93Cx6.c,v $
**
** $Revision: 1.1 $
**
** $Date: 2006-09-21 20:20:46 $
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
#include "Microwire93Cx6.h"
#include "Board.h"
#include "SaveState.h"
#include <stdlib.h>
#include <string.h>

typedef struct Microwire93Cx6
{
    int dummy;
};


void microwire93Cx6SaveState(Microwire93Cx6* mw)
{
}

void microwire93Cx6LoadState(Microwire93Cx6* mw)
{
}

Microwire93Cx6* microwire93Cx6Create(int size, int mode, void* romData, int romSize, char* sramFilename)
{
    Microwire93Cx6* mw = malloc(sizeof(Microwire93Cx6));

    return mw;
}

void microwire93Cx6Destroy(Microwire93Cx6* mw)
{
    free(mw);
}

void microwire93Cx6Reset(Microwire93Cx6* mw)
{
}


void microwire93Cx6SetCs(Microwire93Cx6* rtl, int value)
{
}

void microwire93Cx6SetClk(Microwire93Cx6* rtl, int value)
{
}

void microwire93Cx6SetDo(Microwire93Cx6* rtl, int value)
{
}

int microwire93Cx6GetDi(Microwire93Cx6* rtl)
{
    return 0;
}



