/*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Src/Win32/Win32keyboard.c,v $
**
** $Revision: 1.2 $
**
** $Date: 2004-12-06 07:32:02 $
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
#define DIRECTINPUT_VERSION     0x0500
#include "Win32keyboard.h"
#include <windows.h>
#include <stdio.h>
#include <winioctl.h>
#include <dinput.h>
 

#ifndef DIK_WEBFORWARD
#define DIK_WEBFORWARD      0xE9
#define DIK_WEBBACK         0xEA
#endif

static BYTE msxKeyMap[16];

typedef struct { 
    DWORD Code; 
    WORD  VirtKey;
    DWORD DCode;
    byte Pos; 
    byte Mask; 
    char* Name;
} KeyMapEntry;

/* Key mapping table */
static KeyMapEntry keyMapSvi[] = {
    { 0x0B, 0,           DIK_0,          0,  0x01, "0"         }, /* 0          */
    { 0x02, 0,           DIK_1,          0,  0x02, "1"         }, /* 1          */
    { 0x03, 0,           DIK_2,          0,  0x04, "2"         }, /* 2          */
    { 0x04, 0,           DIK_3,          0,  0x08, "3"         }, /* 3          */
    { 0x05, 0,           DIK_4,          0,  0x10, "4"         }, /* 4          */
    { 0x06, 0,           DIK_5,          0,  0x20, "5"         }, /* 5          */
    { 0x07, 0,           DIK_6,          0,  0x40, "6"         }, /* 6          */
    { 0x08, 0,           DIK_7,          0,  0x80, "7"         }, /* 7          */
	{ 0x09, 0,           DIK_8,          1,  0x01, "8"         }, /* 8          */
    { 0x0A, 0,           DIK_9,          1,  0x02, "9"         }, /* 9          */
    { 0x27, 0,           DIK_SEMICOLON,  1,  0x04, ";"         }, /* ;          */
    { 0x28, 0,           DIK_APOSTROPHE, 1,  0x08, "'"         }, /* '          */
    { 0x33, 0,           DIK_COMMA,      1,  0x10, ","         }, /* ,         */
	{ 0x0D, 0,           DIK_EQUALS,     1,  0x20, "="         }, /* =          */
    { 0x34, 0,           DIK_PERIOD,     1,  0x40, "."         }, /* .          */
    { 0x35, 0,           DIK_SLASH,      1,  0x80, "/"         }, /* /          */
	{ 0x0C, 0,           DIK_MINUS,      2,  0x01, "-"         }, /* -          */
    { 0x1E, 0,           DIK_A,          2,  0x02, "A"         }, /* A          */
    { 0x30, 0,           DIK_B,          2,  0x04, "B"         }, /* B          */
    { 0x2E, 0,           DIK_C,          2,  0x08, "C"         }, /* C          */
    { 0x20, 0,           DIK_D,          2,  0x10, "D"         }, /* D          */
    { 0x12, 0,           DIK_E,          2,  0x20, "E"         }, /* E          */
    { 0x21, 0,           DIK_F,          2,  0x40, "F"         }, /* F          */
    { 0x22, 0,           DIK_G,          2,  0x80, "G"         }, /* G          */
    { 0x23, 0,           DIK_H,          3,  0x01, "H"         }, /* H          */
    { 0x17, 0,           DIK_I,          3,  0x02, "I"         }, /* I          */
    { 0x24, 0,           DIK_J,          3,  0x04, "J"         }, /* J          */
    { 0x25, 0,           DIK_K,          3,  0x08, "K"         }, /* K          */
    { 0x26, 0,           DIK_L,          3,  0x10, "L"         }, /* L          */
    { 0x32, 0,           DIK_M,          3,  0x20, "M"         }, /* M          */
    { 0x31, 0,           DIK_N,          3,  0x40, "N"         }, /* N          */
    { 0x18, 0,           DIK_O,          3,  0x80, "O"         }, /* O          */
    { 0x19, 0,           DIK_P,          4,  0x01, "P"         }, /* P          */
    { 0x10, 0,           DIK_Q,          4,  0x02, "Q"         }, /* Q          */
    { 0x13, 0,           DIK_R,          4,  0x04, "R"         }, /* R          */
    { 0x1F, 0,           DIK_S,          4,  0x08, "S"         }, /* S          */
    { 0x14, 0,           DIK_T,          4,  0x10, "T"         }, /* T          */
    { 0x16, 0,           DIK_U,          4,  0x20, "U"         }, /* U          */
    { 0x2f, 0,           DIK_V,          4,  0x40, "V"         }, /* V          */
    { 0x11, 0,           DIK_W,          4,  0x80, "W"         }, /* W          */
	{ 0x2D, 0,           DIK_X,          5,  0x01, "X"         }, /* X          */
    { 0x15, 0,           DIK_Y,          5,  0x02, "Y"         }, /* Y          */
    { 0x2C, 0,           DIK_Z,          5,  0x04, "Z"         }, /* Z          */
    { 0x1A, 0,           DIK_LBRACKET,   5,  0x08, "["         }, /* [          */
	{ 0x2B, 0,           DIK_BACKSLASH,  5,  0x10, "\\"        }, /* \          */
    { 0x1B, 0,           DIK_RBRACKET,   5,  0x20, "]"         }, /* ]          */
    { 0x0E, 0,           DIK_BACK,       5,  0x40, "BACK"      }, /* BACKSPACE  */
    { 0x48, 0,           DIK_UP,         5,  0x80, "UP"        }, /* UP ARROW   */
    { 0x00, VK_LSHIFT,   DIK_LSHIFT,     6,  0x01, "SHIFT"     }, /* SHIFT      */
    { 0x00, VK_RSHIFT,   DIK_RSHIFT,     6,  0x01, "SHIFT"     }, /* SHIFT      */
    { 0x00, VK_LCONTROL, DIK_LCONTROL,   6,  0x02, "CTRL"      }, /* CONTROL    */
    { 0x00, VK_RCONTROL, DIK_RCONTROL,   6,  0x02, "CTRL"      }, /* CONTROL    */
    { 0x00, VK_LMENU,    DIK_LMENU,      6,  0x04, "LGRAP"     }, /* LGRAP      */
    { 0x00, VK_RMENU,    DIK_RMENU,      6,  0x08, "RGRAP"     }, /* RGRAP      */
    { 0x01, 0,           DIK_ESCAPE,     6,  0x10, "ESC"       }, /* ESCAPE     */
    { 0x49, 0,           DIK_PRIOR,      6,  0x20, "STOP"      }, /* STOP/BREAK */ //VK 69 - PAGE UP key
    { 0x1C, 0,           DIK_RETURN,     6,  0x40, "ENTER"     }, /* ENTER     */
    { 0x9C, 0,           DIK_NUMPADENTER,6,  0x40, "ENTER"     }, /* Enter on numeric keypad */
	{ 0x4B, 0,           DIK_LEFT,       6,  0x80, "LEFT"      }, /* LEFT ARROW */
    { 0x3B, 0,           DIK_F1,         7,  0x01, "F1"        }, /* F1         */
    { 0x3C, 0,           DIK_F2,         7,  0x02, "F2"        }, /* F2         */
    { 0x3D, 0,           DIK_F3,         7,  0x04, "F3"        }, /* F3         */
    { 0x3E, 0,           DIK_F4,         7,  0x08, "F4"        }, /* F4         */
    { 0x3F, 0,           DIK_F5,         7,  0x10, "F5"        }, /* F5         */
    { 0x47, 0,           DIK_HOME,       7,  0x20, "HOME"      }, /* HOME/CLS   */ //VK 67 - HOME key
    { 0x52, 0,           DIK_INSERT,     7,  0x40, "INS"       }, /* INSERT     */ //VK 2d - INS key
    { 0x50, 0,           DIK_DOWN,       7,  0x80, "DOWN"      }, /* DOWN ARROW */
    { 0x39, 0,           DIK_SPACE,      8,  0x01, "SPACE"     }, /* SPACE      */
    { 0x0F, 0,           DIK_TAB,        8,  0x02, "TAB"       }, /* TAB        */
    { 0x53, 0,           DIK_DELETE,     8,  0x04, "DEL"       }, /* DELETE     */ //VK 6e - DEL key
    { 0x00, VK_CAPITAL,  DIK_CAPITAL,    8,  0x08, "CAPS"      }, /* CAPSLOCK   */
//  { 0x4F, 0,           DIK_END,        7,  0x40, "SELECT"    }, /* SELECT     */ //VK 23 - END key
    { 0x4F, 0,           DIK_SCROLL,     8,  0x10, "SELECT"    }, /* SELECT     */
    { 0x4F, 0,           DIK_SYSRQ,      8,  0x20, "PRINT"     }, /* PRINT      */
    { 0x00, 0,           0,              8,  0x40, ""          },
    { 0x4D, 0,           DIK_RIGHT,      8,  0x80, "RIGHT"     }, /* RIGHT ARROW */
    { 0x00, VK_NUMPAD0,  DIK_NUMPAD0,    9,  0x01, "NUM0"       }, /* NUMPAD 0   */
    { 0x00, VK_NUMPAD1,  DIK_NUMPAD1,    9,  0x02, "NUM1"       }, /* NUMPAD 1   */
    { 0x00, VK_NUMPAD2,  DIK_NUMPAD2,    9,  0x04, "NUM2"       }, /* NUMPAD 2   */
    { 0x00, VK_NUMPAD3,  DIK_NUMPAD3,    9,  0x08, "NUM3"       }, /* NUMPAD 3   */
    { 0x00, VK_NUMPAD4,  DIK_NUMPAD4,    9,  0x10, "NUM4"       }, /* NUMPAD 4   */
    { 0x00, VK_NUMPAD5,  DIK_NUMPAD5,    9,  0x20, "NUM5"       }, /* NUMPAD 5   */
    { 0x00, VK_NUMPAD6,  DIK_NUMPAD6,    9,  0x40, "NUM6"       }, /* NUMPAD 6   */
    { 0x00, VK_NUMPAD7,  DIK_NUMPAD7,    9,  0x80, "NUM7"       }, /* NUMPAD 7   */
    { 0x00, VK_NUMPAD8,  DIK_NUMPAD8,    10, 0x01, "NUM8"       }, /* NUMPAD 8   */
    { 0x00, VK_NUMPAD9,  DIK_NUMPAD9,    10, 0x02, "NUM9"       }, /* NUMPAD 9   */
    { 0x4E, VK_ADD,      DIK_ADD,        10, 0x04, "NUM+"       }, /* NUMPAD +   */
    { 0x4A, VK_SUBTRACT, DIK_SUBTRACT,   10, 0x08, "NUM-"       }, /* NUMPAD -   */
    { 0x37, VK_MULTIPLY, DIK_MULTIPLY,   10, 0x10, "NUM*"       }, /* NUMPAD *   */
    { 0x35, VK_DIVIDE,   DIK_DIVIDE,     10, 0x20, "NUM/"       }, /* NUMPAD /   */
    { 0x45, VK_DECIMAL,  DIK_DECIMAL,    10, 0x40, "NUM."       }, /* NUMPAD .   */
    { 0x00, VK_NEXT,     DIK_NEXT,       10, 0x80, "NUM,"       }, /* NUMPAD ,   */ //VK 22 - PAGE DOWN key
    { 0x00, 0, 0, 0,  0x00 }  /** The End. **/
};

/* Key mapping table */
static KeyMapEntry keyMapEnglish[] = {
    { 0x0B, 0,           DIK_0,          0,  0x01, "0"         }, /* 0          */
    { 0x02, 0,           DIK_1,          0,  0x02, "1"         }, /* 1          */
    { 0x03, 0,           DIK_2,          0,  0x04, "2"         }, /* 2          */
    { 0x04, 0,           DIK_3,          0,  0x08, "3"         }, /* 3          */
    { 0x05, 0,           DIK_4,          0,  0x10, "4"         }, /* 4          */
    { 0x06, 0,           DIK_5,          0,  0x20, "5"         }, /* 5          */
    { 0x07, 0,           DIK_6,          0,  0x40, "6"         }, /* 6          */
    { 0x08, 0,           DIK_7,          0,  0x80, "7"         }, /* 7          */
    { 0x09, 0,           DIK_8,          1,  0x01, "8"         }, /* 8          */
    { 0x0A, 0,           DIK_9,          1,  0x02, "9"         }, /* 9          */
    { 0x0C, 0,           DIK_MINUS,      1,  0x04, "-"         }, /* -          */
    { 0x0D, 0,           DIK_EQUALS,     1,  0x08, "="         }, /* =          */
    { 0x2B, 0,           DIK_BACKSLASH,  1,  0x10, "\\"        }, /* \          */
    { 0x1A, 0,           DIK_LBRACKET,   1,  0x20, "["         }, /* [          */
    { 0x1B, 0,           DIK_RBRACKET,   1,  0x40, "]"         }, /* ]          */
    { 0x27, 0,           DIK_SEMICOLON,  1,  0x80, ";"         }, /* ;          */
    { 0x28, 0,           DIK_APOSTROPHE, 2,  0x01, "'"         }, /* '          */
    { 0x29, 0,           DIK_GRAVE,      2,  0x02, "`"         }, /* `          */
    { 0x33, 0,           DIK_COMMA,      2,  0x04, ","         }, /* ,          */
    { 0x34, 0,           DIK_PERIOD,     2,  0x08, "."         }, /* .          */
    { 0x35, 0,           DIK_SLASH,      2,  0x10, "/"         }, /* /          */
    { 0x1E, 0,           DIK_A,          2,  0x40, "A"         }, /* A          */
    { 0x30, 0,           DIK_B,          2,  0x80, "B"         }, /* B          */
    { 0x2E, 0,           DIK_C,          3,  0x01, "C"         }, /* C          */
    { 0x20, 0,           DIK_D,          3,  0x02, "D"         }, /* D          */
    { 0x12, 0,           DIK_E,          3,  0x04, "E"         }, /* E          */
    { 0x21, 0,           DIK_F,          3,  0x08, "F"         }, /* F          */
    { 0x22, 0,           DIK_G,          3,  0x10, "G"         }, /* G          */
    { 0x23, 0,           DIK_H,          3,  0x20, "H"         }, /* H          */
    { 0x17, 0,           DIK_I,          3,  0x40, "I"         }, /* I          */
    { 0x24, 0,           DIK_J,          3,  0x80, "J"         }, /* J          */
    { 0x25, 0,           DIK_K,          4,  0x01, "K"         }, /* K          */
    { 0x26, 0,           DIK_L,          4,  0x02, "L"         }, /* L          */
    { 0x32, 0,           DIK_M,          4,  0x04, "M"         }, /* M          */
    { 0x31, 0,           DIK_N,          4,  0x08, "N"         }, /* N          */
    { 0x18, 0,           DIK_O,          4,  0x10, "O"         }, /* O          */
    { 0x19, 0,           DIK_P,          4,  0x20, "P"         }, /* P          */
    { 0x10, 0,           DIK_Q,          4,  0x40, "Q"         }, /* Q          */
    { 0x13, 0,           DIK_R,          4,  0x80, "R"         }, /* R          */
    { 0x1F, 0,           DIK_S,          5,  0x01, "S"         }, /* S          */
    { 0x14, 0,           DIK_T,          5,  0x02, "T"         }, /* T          */
    { 0x16, 0,           DIK_U,          5,  0x04, "U"         }, /* U          */
    { 0x2f, 0,           DIK_V,          5,  0x08, "V"         }, /* V          */
    { 0x11, 0,           DIK_W,          5,  0x10, "W"         }, /* W          */
    { 0x2D, 0,           DIK_X,          5,  0x20, "X"         }, /* X          */
    { 0x15, 0,           DIK_Y,          5,  0x40, "Y"         }, /* Y          */
    { 0x2C, 0,           DIK_Z,          5,  0x80, "Z"         }, /* Z          */
    { 0x3B, 0,           DIK_F1,         6,  0x20, "F1"        }, /* F1         */
    { 0x3C, 0,           DIK_F2,         6,  0x40, "F2"        }, /* F2         */
    { 0x3D, 0,           DIK_F3,         6,  0x80, "F3"        }, /* F3         */
    { 0x3E, 0,           DIK_F4,         7,  0x01, "F4"        }, /* F4         */
    { 0x3F, 0,           DIK_F5,         7,  0x02, "F5"        }, /* F5         */
    { 0x01, 0,           DIK_ESCAPE,     7,  0x04, "ESC"       }, /* ESCAPE     */
    { 0x0F, 0,           DIK_TAB,        7,  0x08, "TAB"       }, /* TAB        */
    { 0x49, 0,           DIK_PRIOR,      7,  0x10, "STOP"      }, /* STOP/BREAK */ //VK 69 - PAGE UP key
    { 0x0E, 0,           DIK_BACK,       7,  0x20, "BACK"      }, /* BACKSPACE  */
    { 0x4F, 0,           DIK_END,        7,  0x40, "SELECT"    }, /* SELECT     */ //VK 23 - END key
    { 0x1C, 0,           DIK_RETURN,     7,  0x80, "RETURN"    }, /* RETURN     */
    { 0x9C, 0,           DIK_NUMPADENTER,7,  0x80, "ENTER"     }, /* Enter on numeric keypad */
    { 0x39, 0,           DIK_SPACE,      8,  0x01, "SPACE"     }, /* SPACE      */
    { 0x47, 0,           DIK_HOME,       8,  0x02, "HOME"      }, /* HOME/CLS   */ //VK 67 - HOME key
    { 0x52, 0,           DIK_INSERT,     8,  0x04, "INS"       }, /* INSERT     */ //VK 2d - INS key
    { 0x53, 0,           DIK_DELETE,     8,  0x08, "DEL"       }, /* DELETE     */ //VK 6e - DEL key
    { 0x4B, 0,           DIK_LEFT,       8,  0x10, "LEFT"      }, /* LEFT ARROW */
    { 0x48, 0,           DIK_UP,         8,  0x20, "UP"        }, /* UP ARROW   */
    { 0x4D, 0,           DIK_RIGHT,      8,  0x80, "RIGHT"     }, /* RIGHT ARROW */
    { 0x50, 0,           DIK_DOWN,       8,  0x40, "DOWN"      }, /* DOWN ARROW */
    { 0x37, VK_MULTIPLY, DIK_MULTIPLY,   9,  0x01, "NUM*"      }, /* NUMPAD *   */
    { 0x4E, VK_ADD,      DIK_ADD,        9,  0x02, "NUM+"      }, /* NUMPAD +   */
    { 0x35, VK_DIVIDE,   DIK_DIVIDE,     9,  0x04, "NUM/"       }, /* NUMPAD /   */
    { 0x00, VK_NUMPAD0,  DIK_NUMPAD0,    9,  0x08, "NUM0"       }, /* NUMPAD 0   */
    { 0x00, VK_NUMPAD1,  DIK_NUMPAD1,    9,  0x10, "NUM1"       }, /* NUMPAD 1   */
    { 0x00, VK_NUMPAD2,  DIK_NUMPAD2,    9,  0x20, "NUM2"       }, /* NUMPAD 2   */
    { 0x00, VK_NUMPAD3,  DIK_NUMPAD3,    9,  0x40, "NUM3"       }, /* NUMPAD 3   */
    { 0x00, VK_NUMPAD4,  DIK_NUMPAD4,    9,  0x80, "NUM4"       }, /* NUMPAD 4   */
    { 0x00, VK_NUMPAD5,  DIK_NUMPAD5,    10, 0x01, "NUM5"       }, /* NUMPAD 5   */
    { 0x00, VK_NUMPAD6,  DIK_NUMPAD6,    10, 0x02, "NUM6"       }, /* NUMPAD 6   */
    { 0x00, VK_NUMPAD7,  DIK_NUMPAD7,    10, 0x04, "NUM7"       }, /* NUMPAD 7   */
    { 0x00, VK_NUMPAD8,  DIK_NUMPAD8,    10, 0x08, "NUM8"       }, /* NUMPAD 8   */
    { 0x00, VK_NUMPAD9,  DIK_NUMPAD9,    10, 0x10, "NUM9"       }, /* NUMPAD 9   */
    { 0x4A, VK_SUBTRACT, DIK_SUBTRACT,   10, 0x20, "NUM-"       }, /* NUMPAD -   */
    { 0x00, VK_NEXT,     DIK_NEXT,       10, 0x40, "NUM,"       }, /* NUMPAD ,   */ //VK 22 - PAGE DOWN key
    { 0x45, VK_DECIMAL,  DIK_DECIMAL,    10, 0x80, "NUM."       }, /* NUMPAD .   */
    { 0x00, 0,           0,              11, 0x01, ""           },
    { 0x00, 0,           DIK_RWIN,       11, 0x02, "JIKKOU"     },
    { 0x00, 0,           DIK_WEBBACK,    11, 0x02, "JIKKOU"     },
    { 0x00, 0,           0,              11, 0x04, ""           },
    { 0x00, 0,           DIK_LWIN,       11, 0x08, "TORIKESHI"  },
    { 0x00, 0,           DIK_WEBFORWARD, 11, 0x08, "TORIKESHI"  },
    { 0x00, 0,           0,              11, 0x10, ""           },
    { 0x00, 0,           0,              11, 0x20, ""           },
    { 0x00, 0,           0,              11, 0x40, ""           },
    { 0x00, 0,           0,              11, 0x80, ""           },
    { 0x00, VK_LSHIFT,   DIK_LSHIFT,     6,  0x01, "SHIFT"      }, /* SHIFT      */
    { 0x00, VK_RSHIFT,   DIK_RSHIFT,     6,  0x01, "SHIFT"      }, /* SHIFT      */
    { 0x00, VK_LCONTROL, DIK_LCONTROL,   6,  0x02, "CTRL"       }, /* CONTROL    */
    { 0x00, VK_RCONTROL, DIK_RCONTROL,   2,  0x20, "CTRL"       }, /* ACC        */
    { 0x00, VK_LMENU,    DIK_LMENU,      6,  0x04, "GRAPH"      }, /* GRAPH      */
    { 0x00, VK_RMENU,    DIK_RMENU,      6,  0x10, "CODE"       }, /* CODE       */
    { 0x00, VK_CAPITAL,  DIK_CAPITAL,    6,  0x08, "CAPS"       }, /* CAPSLOCK   */
    { 0x00, 0, 0, 0,  0x00 }  /** The End. **/
};

/* Key mapping table */
KeyMapEntry keyMapJapanese[] = {
    { 0x0B, 0,           DIK_0,          0,  0x01, "0"          }, /* 0          */
    { 0x02, 0,           DIK_1,          0,  0x02, "1"          }, /* 1          */
    { 0x03, 0,           DIK_2,          0,  0x04, "2"          }, /* 2          */
    { 0x04, 0,           DIK_3,          0,  0x08, "3"          }, /* 3          */
    { 0x05, 0,           DIK_4,          0,  0x10, "4"          }, /* 4          */
    { 0x06, 0,           DIK_5,          0,  0x20, "5"          }, /* 5          */
    { 0x07, 0,           DIK_6,          0,  0x40, "6"          }, /* 6          */
    { 0x08, 0,           DIK_7,          0,  0x80, "7"          }, /* 7          */
    { 0x09, 0,           DIK_8,          1,  0x01, "8"          }, /* 8          */
    { 0x0A, 0,           DIK_9,          1,  0x02, "9"          }, /* 9          */
    { 0x0C, 0,           DIK_MINUS,      1,  0x04, "-"          }, /* -          */
    { 0x0D, 0,           DIK_CIRCUMFLEX, 1,  0x08, "^"          }, /* ^          */
    { 0x7D, 0,           DIK_YEN,		 1,  0x10, "\\"         }, /* \          */
    { 0x1A, 0,           DIK_AT,	     1,  0x20, "@"          }, /* @          */
    { 0x1B, 0,           DIK_LBRACKET,   1,  0x40, "["          }, /* [          */
    { 0x27, 0,           DIK_SEMICOLON,  1,  0x80, ";"          }, /* ;          */
    { 0x28, 0,           DIK_COLON, 	 2,  0x01, ":"          }, /* :          */
    { 0x2B, 0,           DIK_RBRACKET,   2,  0x02, "]"          }, /* ]          */
    { 0x33, 0,           DIK_COMMA,      2,  0x04, ","          }, /* ,          */
    { 0x34, 0,           DIK_PERIOD,     2,  0x08, "."          }, /* .          */
    { 0x35, 0,           DIK_SLASH,      2,  0x10, "/"          }, /* /          */
    { 0x73, 0,           DIK_BACKSLASH,  2,  0x20, "\\"         }, /* \          */
    { 0x1E, 0,           DIK_A,          2,  0x40, "A"          }, /* A          */
    { 0x30, 0,           DIK_B,          2,  0x80, "B"          }, /* B          */
    { 0x2E, 0,           DIK_C,          3,  0x01, "C"          }, /* C          */
    { 0x20, 0,           DIK_D,          3,  0x02, "D"          }, /* D          */
    { 0x12, 0,           DIK_E,          3,  0x04, "E"          }, /* E          */
    { 0x21, 0,           DIK_F,          3,  0x08, "F"          }, /* F          */
    { 0x22, 0,           DIK_G,          3,  0x10, "G"          }, /* G          */
    { 0x23, 0,           DIK_H,          3,  0x20, "H"          }, /* H          */
    { 0x17, 0,           DIK_I,          3,  0x40, "I"          }, /* I          */
    { 0x24, 0,           DIK_J,          3,  0x80, "J"          }, /* J          */
    { 0x25, 0,           DIK_K,          4,  0x01, "K"          }, /* K          */
    { 0x26, 0,           DIK_L,          4,  0x02, "L"          }, /* L          */
    { 0x32, 0,           DIK_M,          4,  0x04, "M"          }, /* M          */
    { 0x31, 0,           DIK_N,          4,  0x08, "N"          }, /* N          */
    { 0x18, 0,           DIK_O,          4,  0x10, "O"          }, /* O          */
    { 0x19, 0,           DIK_P,          4,  0x20, "P"          }, /* P          */
    { 0x10, 0,           DIK_Q,          4,  0x40, "Q"          }, /* Q          */
    { 0x13, 0,           DIK_R,          4,  0x80, "R"          }, /* R          */
    { 0x1F, 0,           DIK_S,          5,  0x01, "S"          }, /* S          */
    { 0x14, 0,           DIK_T,          5,  0x02, "T"          }, /* T          */
    { 0x16, 0,           DIK_U,          5,  0x04, "U"          }, /* U          */
    { 0x2f, 0,           DIK_V,          5,  0x08, "V"          }, /* V          */
    { 0x11, 0,           DIK_W,          5,  0x10, "W"          }, /* W          */
    { 0x2D, 0,           DIK_X,          5,  0x20, "X"          }, /* X          */
    { 0x15, 0,           DIK_Y,          5,  0x40, "Y"          }, /* Y          */
    { 0x2C, 0,           DIK_Z,          5,  0x80, "Z"          }, /* Z          */
    { 0x3B, 0,           DIK_F1,         6,  0x20, "F1"         }, /* F1         */
    { 0x3C, 0,           DIK_F2,         6,  0x40, "F2"         }, /* F2         */
    { 0x3D, 0,           DIK_F3,         6,  0x80, "F3"         }, /* F3         */
    { 0x3E, 0,           DIK_F4,         7,  0x01, "F4"         }, /* F4         */
    { 0x3F, 0,           DIK_F5,         7,  0x02, "F5"         }, /* F5         */
    { 0x01, 0,           DIK_ESCAPE,     7,  0x04, "ESC"        }, /* ESCAPE     */
    { 0x0F, 0,           DIK_TAB,        7,  0x08, "TAB"        }, /* TAB        */
    { 0x49, 0,           DIK_PRIOR,      7,  0x10, "STOP"       }, /* STOP/BREAK */ //VK 69 - PAGE UP key
    { 0x0E, 0,           DIK_BACK,       7,  0x20, "BACK"       }, /* BACKSPACE  */
    { 0x4F, 0,           DIK_END,        7,  0x40, "SELECT"     }, /* SELECT     */ //VK 23 - END key
    { 0x1C, 0,           DIK_RETURN,     7,  0x80, "RETURN"     }, /* RETURN     */
    { 0x9C, 0,           DIK_NUMPADENTER,7,  0x80, "ENTER"      }, /* Enter on numeric keypad */
    { 0x39, 0,           DIK_SPACE,      8,  0x01, "SPACE"      }, /* SPACE      */
    { 0x47, 0,           DIK_HOME,       8,  0x02, "HOME"       }, /* HOME/CLS   */ //VK 67 - HOME key
    { 0x52, 0,           DIK_INSERT,     8,  0x04, "INS"        }, /* INSERT     */ //VK 2d - INS key
    { 0x53, 0,           DIK_DELETE,     8,  0x08, "DEL"        }, /* DELETE     */ //VK 6e - DEL key
    { 0x4B, 0,           DIK_LEFT,       8,  0x10, "LEFT"       }, /* LEFT ARROW */
    { 0x48, 0,           DIK_UP,         8,  0x20, "UP"         }, /* UP ARROW   */
    { 0x4D, 0,           DIK_RIGHT,      8,  0x80, "RIGHT"      }, /* RIGHT ARROW */
    { 0x50, 0,           DIK_DOWN,       8,  0x40, "DOWN"       }, /* DOWN ARROW */
    { 0x37, VK_MULTIPLY, DIK_MULTIPLY,   9,  0x01, "NUM*"       }, /* NUMPAD *   */
    { 0x4E, VK_ADD,      DIK_ADD,        9,  0x02, "NUM+"       }, /* NUMPAD +   */
    { 0x35, VK_DIVIDE,   DIK_DIVIDE,     9,  0x04, "NUM/"       }, /* NUMPAD /   */
    { 0x00, VK_NUMPAD0,  DIK_NUMPAD0,    9,  0x08, "NUM0"       }, /* NUMPAD 0   */
    { 0x00, VK_NUMPAD1,  DIK_NUMPAD1,    9,  0x10, "NUM1"       }, /* NUMPAD 1   */
    { 0x00, VK_NUMPAD2,  DIK_NUMPAD2,    9,  0x20, "NUM2"       }, /* NUMPAD 2   */
    { 0x00, VK_NUMPAD3,  DIK_NUMPAD3,    9,  0x40, "NUM3"       }, /* NUMPAD 3   */
    { 0x00, VK_NUMPAD4,  DIK_NUMPAD4,    9,  0x80, "NUM4"       }, /* NUMPAD 4   */
    { 0x00, VK_NUMPAD5,  DIK_NUMPAD5,    10, 0x01, "NUM5"       }, /* NUMPAD 5   */
    { 0x00, VK_NUMPAD6,  DIK_NUMPAD6,    10, 0x02, "NUM6"       }, /* NUMPAD 6   */
    { 0x00, VK_NUMPAD7,  DIK_NUMPAD7,    10, 0x04, "NUM7"       }, /* NUMPAD 7   */
    { 0x00, VK_NUMPAD8,  DIK_NUMPAD8,    10, 0x08, "NUM8"       }, /* NUMPAD 8   */
    { 0x00, VK_NUMPAD9,  DIK_NUMPAD9,    10, 0x10, "NUM9"       }, /* NUMPAD 9   */
    { 0x4A, VK_SUBTRACT, DIK_SUBTRACT,   10, 0x20, "NUM-"       }, /* NUMPAD -   */
    { 0x00, VK_NEXT,     DIK_NEXT,       10, 0x40, "NUM,"       }, /* NUMPAD ,   */ //VK 22 - PAGE DOWN key
    { 0x45, VK_DECIMAL,  DIK_DECIMAL,    10, 0x80, "NUM."       }, /* NUMPAD .   */
    { 0x00, 0,           0,              11, 0x01 },
    { 0x00, 0,           DIK_RWIN,       11, 0x02, "JIKKOU"     },
    { 0x00, 0,           DIK_LWIN,       11, 0x08, "TORIKESHI"  },
    { 0x00, 0,           0,              11, 0x04 },
    { 0x00, 0,           DIK_WEBBACK,    11, 0x02, "JIKKOU"     },
    { 0x00, 0,           DIK_CONVERT,    11, 0x02, "JIKKOU"     }, /* Jikkou     */ 
    { 0x00, 0,           DIK_WEBFORWARD, 11, 0x08, "TORIKESHI"  },
    { 0x00, 0,           DIK_NOCONVERT,  11, 0x08, "TORIKESHI"  }, /* Torikeshi  */
    { 0x00, 0,           0,              11, 0x10 },
    { 0x00, 0,           0,              11, 0x20 },
    { 0x00, 0,           0,              11, 0x40 },
    { 0x00, 0,           0,              11, 0x80 },
    { 0x00, VK_LSHIFT,   DIK_LSHIFT,     6,  0x01 }, /* SHIFT      */
    { 0x00, VK_RSHIFT,   DIK_RSHIFT,     6,  0x01 }, /* SHIFT      */
    { 0x00, VK_LCONTROL, DIK_LCONTROL,   6,  0x02 }, /* CONTROL    */
    { 0x00, VK_RCONTROL, DIK_RCONTROL,   6,  0x02 }, /* CONTROL    */
    { 0x00, VK_LMENU,    DIK_LMENU,      6,  0x04 }, /* GRAPH      */
    { 0x00, VK_RMENU,    DIK_RMENU,      6,  0x10 }, /* CODE       */
    { 0x00, VK_CAPITAL,  DIK_CAPITAL,    6,  0x08 }, /* CAPSLOCK   */
    { 0x00, 0, 0, 0,  0x00 }  /** The End. **/
};

#define MAX_JOYSTICKS 8

static LPDIRECTINPUT        dinput;
static int                  dinputVersion;
static LPDIRECTINPUTDEVICE  kbdDevice = NULL;
static LPDIRECTINPUTDEVICE2 kbdDevice2 = NULL;
static HWND                 dinputWindow;
static KeyMapEntry*         keyMap;
static int                  kbdModifiers;
struct JoyInfo {
    LPDIRECTINPUTDEVICE  diDevice;
    LPDIRECTINPUTDEVICE2 diDevice2;
    char                 name[128];
    int                  numButtons;
    int                  buttonA;
    int                  buttonB;
    int                  state;  
};
static struct JoyInfo joyInfo[MAX_JOYSTICKS];

static int joyCount;



#define STRUCTSIZE(x) ((dinputVersion == 0x0300) ? sizeof(x##_DX3) : sizeof(x))


static void modifyKeyMapVirtKey(WORD oldKey, WORD newKey) {
    int i;
    for (i = 0; keyMap[i].Mask != 0; i++) {
        if (keyMap[i].VirtKey == oldKey) {
            keyMap[i].VirtKey = newKey;
        }
    }
}

void archKeyboardSetKeymap(KeyboardKeymap keymap) 
{    
    int i;
    BOOL success;
    char klId[KL_NAMELENGTH];
    OSVERSIONINFO ovi;

    switch (keymap) {
    case KEYMAP_MSX:
        keyMap = keyMapEnglish;
        memset(klId, 0, sizeof(klId));

        /* Modify scan code map if nessecary */
        success = GetKeyboardLayoutName(klId) ;
        if (success) {
            if (0 == strcmp(klId + 4, "0411")) {
                keyMap = keyMapJapanese;
            }
        }
        break;

    case KEYMAP_SVI:
        keyMap = keyMapSvi;
        break;

    case KEYMAP_COLECO:
        keyMap = keyMapEnglish;
        break;
    }

    ovi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&ovi);
    if (ovi.dwMajorVersion <= 4) {
        modifyKeyMapVirtKey(VK_NEXT,     0);
        modifyKeyMapVirtKey(VK_LSHIFT,   VK_SHIFT);
        modifyKeyMapVirtKey(VK_RSHIFT,   VK_SHIFT);
        modifyKeyMapVirtKey(VK_LCONTROL, VK_CONTROL);
        modifyKeyMapVirtKey(VK_RCONTROL, VK_CONTROL);
        modifyKeyMapVirtKey(VK_LMENU,    VK_MENU);
        modifyKeyMapVirtKey(VK_RMENU,    VK_NEXT);
    } 

    for (i = 0; keyMap[i].Mask != 0; i++) {
        if (keyMap[i].Code != 0) {
            keyMap[i].VirtKey = MapVirtualKey(keyMap[i].Code, 1);
        }
    }
}

static BOOL CALLBACK enumKeyboards(LPCDIDEVICEINSTANCE devInst, LPVOID ref)
{
    DIDEVCAPS kbdCaps;
    HRESULT rv;

    if (kbdDevice != NULL) {
        return DIENUM_CONTINUE;
    }

    rv = IDirectInput_CreateDevice(dinput, &devInst->guidInstance, &kbdDevice, NULL);
    if (rv != DI_OK) {
        return DIENUM_CONTINUE;
    }

    IDirectInputDevice_QueryInterface(kbdDevice, &IID_IDirectInputDevice2, (void **)&kbdDevice2);

    kbdCaps.dwSize = STRUCTSIZE(DIDEVCAPS);
    rv = IDirectInputDevice_GetCapabilities(kbdDevice, &kbdCaps);
    if (rv == DI_OK) {
        rv = IDirectInputDevice_SetDataFormat(kbdDevice, &c_dfDIKeyboard);
        if (rv == DI_OK) {
            rv = IDirectInputDevice_SetCooperativeLevel(kbdDevice, dinputWindow,
                DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
            if (rv != DI_OK) {
                if (kbdDevice2 != NULL) {
                    IDirectInputDevice_Release(kbdDevice2);
                }
                IDirectInputDevice_Release(kbdDevice);
                kbdDevice = NULL;
                kbdDevice2 = NULL;
            }
        }
    }

    return DIENUM_CONTINUE;
}

static BOOL CALLBACK enumAxesCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, void* pContext)
{
    DIPROPRANGE diprg;
    HRESULT rv;

    diprg.diph.dwSize       = sizeof(DIPROPRANGE);
    diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    diprg.diph.dwHow        = DIPH_BYOFFSET;
    diprg.diph.dwObj        = pdidoi->dwOfs;
    diprg.lMin              = -100;
    diprg.lMax              = +100;
    
    rv = IDirectInputDevice_SetProperty(joyInfo[joyCount].diDevice, DIPROP_RANGE, &diprg.diph);
    
    if (rv != DI_OK) {
        return DIENUM_STOP;
    }

    return DIENUM_CONTINUE;
}

static BOOL CALLBACK enumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, void* pContext)
{
    DIDEVCAPS diDevCaps;
    HRESULT rv;

    strcpy(joyInfo[joyCount].name, pdidInstance->tszInstanceName);

    rv = IDirectInput_CreateDevice(dinput, &pdidInstance->guidInstance, &joyInfo[joyCount].diDevice, NULL);
    if (rv != DI_OK) {
        return DIENUM_CONTINUE;
    }
  
    joyInfo[joyCount].diDevice2 = NULL;
    rv = IDirectInputDevice_QueryInterface(joyInfo[joyCount].diDevice, &IID_IDirectInputDevice2, (void **)&joyInfo[joyCount].diDevice2);

	rv = IDirectInputDevice_SetDataFormat(joyInfo[joyCount].diDevice, &c_dfDIJoystick);
    if (rv != DI_OK) {
        IDirectInputDevice_Release(joyInfo[joyCount].diDevice);
        return DIENUM_CONTINUE;
    }
    
    rv = IDirectInputDevice_SetCooperativeLevel(joyInfo[joyCount].diDevice, dinputWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (rv != DI_OK) {
        IDirectInputDevice_Release(joyInfo[joyCount].diDevice);
        return DIENUM_CONTINUE;
    }

	rv = IDirectInputDevice_EnumObjects(joyInfo[joyCount].diDevice, enumAxesCallback, (void*)dinputWindow, DIDFT_AXIS);
    if (rv != DI_OK) {
        IDirectInputDevice_Release(joyInfo[joyCount].diDevice);
        return DIENUM_CONTINUE;
    }

    diDevCaps.dwSize = sizeof(diDevCaps);
    rv = IDirectInputDevice_GetCapabilities(joyInfo[joyCount].diDevice, &diDevCaps);
    if (rv != DI_OK) {
        IDirectInputDevice_Release(joyInfo[joyCount].diDevice);
        return DIENUM_CONTINUE;
    }
    joyInfo[joyCount].numButtons = diDevCaps.dwButtons;

    if (++joyCount == MAX_JOYSTICKS) {
        return DIENUM_STOP;
    }

    return DIENUM_CONTINUE;
}

int inputInit(HWND hwnd)
{
    HRESULT rv   = 234;
    joyCount     = 0;
    kbdModifiers = 0;
    
    memset(msxKeyMap, 0xff, 16);

    dinputWindow = hwnd;
    dinputVersion = DIRECTINPUT_VERSION;
	rv = DirectInputCreate(GetModuleHandle(NULL), dinputVersion, &dinput, NULL);
    if (rv != DI_OK) {
        dinputVersion = 0x0300;
    	rv = DirectInputCreate(GetModuleHandle(NULL), dinputVersion, &dinput, NULL);
        if (rv != DI_OK) {
            printf("Failed to initialize DirectInput\n");
            return 0;
        }
    }

	rv = IDirectInput_EnumDevices(dinput, DIDEVTYPE_KEYBOARD, enumKeyboards, 0, DIEDFL_ATTACHEDONLY);
    if (rv != DI_OK) {
        IDirectInput_Release(dinput);
        printf("Failed to find DirectInput device\n");
        return 0;
    }

    if (kbdDevice == NULL) {
        printf("Failed to create DirectInput device\n");
        return 0;
    }

    rv = IDirectInput_EnumDevices(dinput, DIDEVTYPE_JOYSTICK, enumJoysticksCallback, 0, DIEDFL_ATTACHEDONLY);

    return 1;
}

void inputDestroy(void)
{
    if (kbdDevice) {
        IDirectInputDevice_Release(kbdDevice);
        kbdDevice = NULL;
    }
    
    if (kbdDevice2) {
        IDirectInputDevice_Release(kbdDevice2);
        kbdDevice2 = NULL;
    }

    while (--joyCount >= 0) {
        if (joyInfo[joyCount].diDevice) {
    	    IDirectInputDevice_Unacquire(joyInfo[joyCount].diDevice);
            IDirectInputDevice_Release(joyInfo[joyCount].diDevice);
        }
        joyInfo[joyCount].diDevice = NULL;
        if (joyInfo[joyCount].diDevice2) {
            IDirectInputDevice_Release(joyInfo[joyCount].diDevice2);
            joyInfo[joyCount].diDevice2 = NULL;
        }
    }

    if (dinput) {
        IDirectInput_Release(dinput);
    }

    dinput = NULL;
}

static int joystickUpdateState(int index,  DWORD* buttonMask) {
    DIJOYSTATE js;
    HRESULT rv;
    int state = 0;
    DWORD bMask = 0;
    int i;

    *buttonMask = 0;
    if (index >= joyCount) {
        return 0;
    }

    if (joyInfo[index].diDevice2) {
        IDirectInputDevice2_Poll(joyInfo[index].diDevice2);
    }

    rv = IDirectInputDevice_GetDeviceState(joyInfo[index].diDevice, sizeof(DIJOYSTATE), &js);
    if (rv == DIERR_INPUTLOST || rv == DIERR_NOTACQUIRED) {
    	rv = IDirectInputDevice_Acquire(joyInfo[index].diDevice);
    }

    if (rv != DI_OK) {
        return 0;
    }

    if (js.lX < -50) state |= 0x04; 
    if (js.lX >  50) state |= 0x08;
    if (js.lY < -50) state |= 0x01; 
    if (js.lY >  50) state |= 0x02; 
    if (js.rgbButtons[joyInfo[index].buttonA]) state |= 0x10;
    if (js.rgbButtons[joyInfo[index].buttonB]) state |= 0x20;

    for (i = 0; i < joyInfo[index].numButtons; i++) {
        if (js.rgbButtons[i]) bMask |= 1 << i;
    }

    *buttonMask = bMask;

    return state;
}

int archJoystickGetCount() {
    return joyCount;
}

char* joystickGetName(int index) {
    return joyInfo[index].name;
}


int joystickGetState(int index) {
    return joyInfo[index].state;
}

int joystickNumButtons(int index) {
    return joyInfo[index].numButtons;
}

void joystickSetButtons(int index, int buttonA, int buttonB)
{
    joyInfo[index].buttonA = buttonA;
    joyInfo[index].buttonB = buttonB;
}

DWORD joystickUpdate()
{
    int i;
    DWORD buttonMask = 0;

    for (i = 0; i < joyCount; i++) {
        DWORD mask;
        joyInfo[i].state = joystickUpdateState(i, &mask);
        buttonMask |= mask;
    }

    return buttonMask;
}

void keyboardEnable(int enable)
{
    if (kbdDevice != NULL) {
        if (enable) {
            IDirectInputDevice_Acquire(kbdDevice);
        }
        else {
            IDirectInputDevice_Unacquire(kbdDevice);
        }
    }
}

int keyboardGetModifiers()
{
    return kbdModifiers;
}

void archKeyboardGetState(unsigned char* keyboardState) {
    memcpy(keyboardState, msxKeyMap, 16);
}

void keyboardUpdate() 
{ 
    int i;
    
    memset(msxKeyMap, 0xff, 16);

    if (!GetFocus()) {
        return;
    }

    if (kbdDevice != NULL) {
        char buffer[256]; 
        HRESULT  rv; 
        
        if (kbdDevice2) {
			IDirectInputDevice2_Poll(kbdDevice2);
        }

        rv = IDirectInputDevice_GetDeviceState(kbdDevice, sizeof(buffer), (LPVOID)&buffer); 
        if (rv == DIERR_INPUTLOST || rv == DIERR_NOTACQUIRED) {
            rv = IDirectInputDevice_Acquire(kbdDevice);
            if (rv == DI_OK) {
                rv = IDirectInputDevice_GetDeviceState(kbdDevice, sizeof(buffer), (LPVOID)&buffer); 
            }
        }

        if (rv >= 0) { 
            kbdModifiers = ((buffer[DIK_LSHIFT]   & 0x80) >> 7) | ((buffer[DIK_RSHIFT]   & 0x80) >> 6) | 
                           ((buffer[DIK_LCONTROL] & 0x80) >> 5) | ((buffer[DIK_RCONTROL] & 0x80) >> 4) | 
                           ((buffer[DIK_LALT]     & 0x80) >> 3) | ((buffer[DIK_RALT]     & 0x80) >> 2) | 
                           ((buffer[DIK_LWIN]     & 0x80) >> 1) | ((buffer[DIK_RWIN]     & 0x80) >> 0);

            if (!(kbdModifiers &&
                  ((buffer[DIK_F6]  | buffer[DIK_F7]  | buffer[DIK_F8]  | buffer[DIK_F9]  | 
                    buffer[DIK_F10] | buffer[DIK_F11] | buffer[DIK_F12]) >> 7)))
            {
                for (i = 0; keyMap[i].Mask != 0; i++) {
                    if (buffer[keyMap[i].DCode] >> 7) {
//                  if ((buffer[keyMap[i].DCode] >> 7) || customKeys[keyMap[i].VirtKey] > 0) {
                        msxKeyMap[keyMap[i].Pos] &= ~keyMap[i].Mask;
                    }
                }
            }

            return;
        }
    }

    kbdModifiers = (GetAsyncKeyState(VK_LMENU)   > 1UL ? KBD_LALT     : 0) |
                   (GetAsyncKeyState(VK_MENU)    > 1UL ? KBD_LALT     : 0) |
                   (GetAsyncKeyState(VK_SHIFT)   > 1UL ? KBD_LSHIFT   : 0) |
                   (GetAsyncKeyState(VK_CONTROL) > 1UL ? KBD_LCTRL    : 0) |
                   (GetAsyncKeyState(VK_LWIN)    > 1UL ? KBD_LWIN     : 0) |
                   (GetAsyncKeyState(VK_RWIN)    > 1UL ? KBD_RWIN     : 0);

    // If we got here, DirectInput failed. Use old input mechanism
    for (i = 0; keyMap[i].Mask != 0; i++) {
        if (keyMap[i].VirtKey != 0 && GetAsyncKeyState(keyMap[i].VirtKey) > 1UL) {
            msxKeyMap[keyMap[i].Pos] &= ~keyMap[i].Mask;
        }
    }
} 
