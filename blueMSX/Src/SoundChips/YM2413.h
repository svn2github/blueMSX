/*****************************************************************************
** File:        ym2413.c
**
** Author:      Daniel Vik
**
** Description: Emulation of the YM2413 sound chip
**
** More info:   www.bluemsx.com
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
#ifndef YM2413_H
#define YM2413_H

#ifdef __cplusplus
extern "C" {
#endif

#include "msxTypes.h"
#include "audioMixer.h"

/* Type definitions */
typedef struct YM_2413 YM_2413;

/* Constructor and destructor */
int ym2413Create(Mixer* mixer);

void ym2413SetOversampling(int Oversampling);

#ifdef __cplusplus
}
#endif

#endif
