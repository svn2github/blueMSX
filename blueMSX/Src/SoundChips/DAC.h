/*****************************************************************************
** File:
**      dac.h
**
** Author:
**      Daniel Vik
**
** Description:
**      Emulation of the Konami DAC sound chip.
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
#ifndef DAC_H
#define DAC_H

#include <stdio.h>

#include "msxTypes.h"
#include "audioMixer.h"

/* Type definitions */
typedef struct DAC DAC;

/* Constructor and destructor */
DAC* dacCreate(Mixer* mixer);
void dacDestroy(DAC* dac);
void dacReset(DAC* dac);

/* Register read/write methods */
void dacWrite(DAC* dac, UInt8 value);

#endif

