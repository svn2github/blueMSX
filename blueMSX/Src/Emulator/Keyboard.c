/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Emulator/Keyboard.c,v $
**
** $Revision: 1.3 $
**
** $Date: 2005-01-07 06:38:28 $
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
#include "Keyboard.h"


static UInt16 keyMap[128];

static void initKeyMapMSX()
{
    memset(keyMap, 0, sizeof(keyMap));

    keyMap[EK_0      ] = 0x001;
    keyMap[EK_1      ] = 0x002;
    keyMap[EK_2      ] = 0x004;
    keyMap[EK_3      ] = 0x008;
    keyMap[EK_4      ] = 0x010;
    keyMap[EK_5      ] = 0x020;
    keyMap[EK_6      ] = 0x040;
    keyMap[EK_7      ] = 0x080;

    keyMap[EK_8      ] = 0x101;
    keyMap[EK_9      ] = 0x102;
    keyMap[EK_NEG    ] = 0x104;
    keyMap[EK_CIRCFLX] = 0x108;
    keyMap[EK_BKSLASH] = 0x110;
    keyMap[EK_AT     ] = 0x120;
    keyMap[EK_LBRACK ] = 0x140;
    keyMap[EK_SEMICOL] = 0x180;

    keyMap[EK_COLON  ] = 0x201;
    keyMap[EK_RBRACK ] = 0x202;
    keyMap[EK_COMMA  ] = 0x204;
    keyMap[EK_PERIOD ] = 0x208;
    keyMap[EK_DIV    ] = 0x210;
    keyMap[EK_UNDSCRE] = 0x220;
    keyMap[EK_A      ] = 0x240;
    keyMap[EK_B      ] = 0x280;

    keyMap[EK_C      ] = 0x301;
    keyMap[EK_D      ] = 0x302;
    keyMap[EK_E      ] = 0x304;
    keyMap[EK_F      ] = 0x308;
    keyMap[EK_G      ] = 0x310;
    keyMap[EK_H      ] = 0x320;
    keyMap[EK_I      ] = 0x340;
    keyMap[EK_J      ] = 0x380;

    keyMap[EK_K      ] = 0x401;
    keyMap[EK_L      ] = 0x402;
    keyMap[EK_M      ] = 0x404;
    keyMap[EK_N      ] = 0x408;
    keyMap[EK_O      ] = 0x410;
    keyMap[EK_P      ] = 0x420;
    keyMap[EK_Q      ] = 0x440;
    keyMap[EK_R      ] = 0x480;

    keyMap[EK_S      ] = 0x501;
    keyMap[EK_T      ] = 0x502;
    keyMap[EK_U      ] = 0x504;
    keyMap[EK_V      ] = 0x508;
    keyMap[EK_W      ] = 0x510;
    keyMap[EK_X      ] = 0x520;
    keyMap[EK_Y      ] = 0x540;
    keyMap[EK_Z      ] = 0x580;

    keyMap[EK_LSHIFT ] = 0x601;
    keyMap[EK_RSHIFT ] = 0x601;
    keyMap[EK_CTRL   ] = 0x602;
    keyMap[EK_GRAPH  ] = 0x604;
    keyMap[EK_CAPS   ] = 0x608;
    keyMap[EK_CODE   ] = 0x610;
    keyMap[EK_F1     ] = 0x620;
    keyMap[EK_F2     ] = 0x640;
    keyMap[EK_F3     ] = 0x680;

    keyMap[EK_F4     ] = 0x701;
    keyMap[EK_F5     ] = 0x702;
    keyMap[EK_ESC    ] = 0x704;
    keyMap[EK_TAB    ] = 0x708;
    keyMap[EK_STOP   ] = 0x710;
    keyMap[EK_BKSPACE] = 0x720;
    keyMap[EK_SELECT ] = 0x740;
    keyMap[EK_RETURN ] = 0x780;

    keyMap[EK_SPACE  ] = 0x801;
    keyMap[EK_CLS    ] = 0x802;
    keyMap[EK_INS    ] = 0x804;
    keyMap[EK_DEL    ] = 0x808;
    keyMap[EK_LEFT   ] = 0x810;
    keyMap[EK_UP     ] = 0x820;
    keyMap[EK_DOWN   ] = 0x840;
    keyMap[EK_RIGHT  ] = 0x880;

    keyMap[EK_NUMMUL ] = 0x901;
    keyMap[EK_NUMADD ] = 0x902;
    keyMap[EK_NUMDIV ] = 0x904;
    keyMap[EK_NUM0   ] = 0x908;
    keyMap[EK_NUM1   ] = 0x910;
    keyMap[EK_NUM2   ] = 0x920;
    keyMap[EK_NUM3   ] = 0x940;
    keyMap[EK_NUM4   ] = 0x980;

    keyMap[EK_NUM5   ] = 0xa01;
    keyMap[EK_NUM6   ] = 0xa02;
    keyMap[EK_NUM7   ] = 0xa04;
    keyMap[EK_NUM8   ] = 0xa08;
    keyMap[EK_NUM9   ] = 0xa10;
    keyMap[EK_NUMSUB ] = 0xa20;
    keyMap[EK_NUMCOM ] = 0xa40;
    keyMap[EK_NUMPER ] = 0xa80;

    keyMap[EK_JIKKOU ] = 0xb02;
    keyMap[EK_TORIKE ] = 0xb08;
//    keyMap[EK_PAUSE  ] = 0x780;
}

static void initKeyMapSVI()
{
    memset(keyMap, 0, sizeof(keyMap));

    keyMap[EK_0      ] = 0x001;
    keyMap[EK_1      ] = 0x002;
    keyMap[EK_2      ] = 0x004;
    keyMap[EK_3      ] = 0x008;
    keyMap[EK_4      ] = 0x010;
    keyMap[EK_5      ] = 0x020;
    keyMap[EK_6      ] = 0x040;
    keyMap[EK_7      ] = 0x080;

    keyMap[EK_8      ] = 0x101;
    keyMap[EK_9      ] = 0x102;
    keyMap[EK_SEMICOL] = 0x104;
    keyMap[EK_COLON  ] = 0x108;
    keyMap[EK_COMMA  ] = 0x110;
    keyMap[EK_CIRCFLX] = 0x120;
    keyMap[EK_PERIOD ] = 0x140;
    keyMap[EK_DIV    ] = 0x180;

    keyMap[EK_NEG    ] = 0x201;
    keyMap[EK_A      ] = 0x202;
    keyMap[EK_B      ] = 0x204;
    keyMap[EK_C      ] = 0x208;
    keyMap[EK_D      ] = 0x210;
    keyMap[EK_E      ] = 0x220;
    keyMap[EK_F      ] = 0x240;
    keyMap[EK_G      ] = 0x280;

    keyMap[EK_H      ] = 0x301;
    keyMap[EK_I      ] = 0x302;
    keyMap[EK_J      ] = 0x304;
    keyMap[EK_K      ] = 0x308;
    keyMap[EK_L      ] = 0x310;
    keyMap[EK_M      ] = 0x320;
    keyMap[EK_N      ] = 0x340;
    keyMap[EK_O      ] = 0x380;

    keyMap[EK_P      ] = 0x401;
    keyMap[EK_Q      ] = 0x402;
    keyMap[EK_R      ] = 0x404;
    keyMap[EK_S      ] = 0x408;
    keyMap[EK_T      ] = 0x410;
    keyMap[EK_U      ] = 0x420;
    keyMap[EK_V      ] = 0x440;
    keyMap[EK_W      ] = 0x480;

    keyMap[EK_X      ] = 0x501;
    keyMap[EK_Y      ] = 0x502;
    keyMap[EK_Z      ] = 0x504;
    keyMap[EK_AT     ] = 0x508;
    keyMap[EK_BKSLASH] = 0x510;
    keyMap[EK_LBRACK ] = 0x520;
    keyMap[EK_BKSPACE] = 0x540;
    keyMap[EK_UP     ] = 0x580;

    keyMap[EK_LSHIFT ] = 0x601;
    keyMap[EK_RSHIFT ] = 0x601;
    keyMap[EK_CTRL   ] = 0x602;
    keyMap[EK_GRAPH  ] = 0x604;
    keyMap[EK_CODE   ] = 0x608;
    keyMap[EK_ESC    ] = 0x610;
    keyMap[EK_STOP   ] = 0x620;
    keyMap[EK_RETURN ] = 0x640;
    keyMap[EK_LEFT   ] = 0x680;

    keyMap[EK_F1     ] = 0x701;
    keyMap[EK_F2     ] = 0x702;
    keyMap[EK_F3     ] = 0x704;
    keyMap[EK_F4     ] = 0x708;
    keyMap[EK_F5     ] = 0x710;
    keyMap[EK_CLS    ] = 0x720;
    keyMap[EK_INS    ] = 0x740;
    keyMap[EK_DOWN   ] = 0x780;

    keyMap[EK_SPACE  ] = 0x801;
    keyMap[EK_TAB    ] = 0x802;
    keyMap[EK_DEL    ] = 0x804;
    keyMap[EK_CAPS   ] = 0x808;
    keyMap[EK_SELECT ] = 0x810;
    keyMap[EK_PRINT  ] = 0x820;
    keyMap[EK_RIGHT  ] = 0x880;

    keyMap[EK_NUM0   ] = 0x901;
    keyMap[EK_NUM1   ] = 0x902;
    keyMap[EK_NUM2   ] = 0x904;
    keyMap[EK_NUM3   ] = 0x908;
    keyMap[EK_NUM4   ] = 0x910;
    keyMap[EK_NUM5   ] = 0x920;
    keyMap[EK_NUM6   ] = 0x940;
    keyMap[EK_NUM7   ] = 0x980;

    keyMap[EK_NUM8   ] = 0xa01;
    keyMap[EK_NUM9   ] = 0xa02;
    keyMap[EK_NUMADD ] = 0xa04;
    keyMap[EK_NUMSUB ] = 0xa08;
    keyMap[EK_NUMMUL ] = 0xa10;
    keyMap[EK_NUMDIV ] = 0xa20;
    keyMap[EK_NUMPER ] = 0xa40;
    keyMap[EK_NUMCOM ] = 0xa80;
}

static UInt8 keyboardState[16];

void keyboardKeyDown(int keyCode)
{
    int kbdCode = keyMap[keyCode];
    keyboardState[kbdCode >> 8] &= ~(kbdCode & 0xff);
}

void keyboardKeyUp(int keyCode)
{
    int kbdCode = keyMap[keyCode];
    keyboardState[kbdCode >> 8] |= (kbdCode & 0xff);
}

int keyboardGetKeyState(int keyCode)
{
    int kbdCode = keyMap[keyCode];
    return (keyboardState[kbdCode >> 8] & (kbdCode & 0xff)) == 0;
}
    
void keyboardReset() 
{
    keyboardSetKeymap(KEYMAP_MSX);

    memset(keyboardState, 0xff, 16);
}

void keyboardSetKeymap(KeyboardKeymap keymap) 
{    
    switch (keymap) {
    case KEYMAP_MSX:
        initKeyMapMSX();
        break;

    case KEYMAP_SVI:
        initKeyMapSVI();
        break;

    case KEYMAP_COLECO:
        initKeyMapMSX();
        break;
    }
}

UInt8* keyboardGetState() {
    return keyboardState;
}

