/*****************************************************************************
** File:
**      ramMapperIo.h
**
** Author:
**      Daniel Vik
**
** Description:
**      I/O for Ram mapper
**
** More info:   
**      www.bluemsx.com
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
#ifndef RAM_MAPPER_IO_H
#define RAM_MAPPER_IO_H

#include "MSXTypes.h"

typedef void  (*MemIoWrite)(void*, UInt16, UInt8);

int ramMapperIoCreate();

int ramMapperIoAdd(int size, MemIoWrite write, void* ref);
void ramMapperIoRemove(int handle);

int ramMapperIoGetPortValue(int ioPort);

#endif
