/****************************************************************************
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *****************************************************************************
*/
#include <stdio.h>
#include <conio.h>
#include "arch.h"

void setpos(Int8 x, Int8 y)
{
    _asm {
        mov ah, 2
        xor bh, bh
        mov dh, y
        mov dl, x
        int 10h
    };
}

void clearscreen(void)
{
    _asm {
        mov ax, 1
        int 10h
        mov ah, 1
        mov cx, 201fh
        int 10h
    };
}

void display(const char *buffer)
{
    // this code works only with near pointers
    _asm {
        push bp
        mov bx, 0007h
        mov cx, 0001h
        mov dh, 0ffh
        mov si, buffer
    arch_display_row:
        xor dl, dl
        inc dh
    arch_display_char:
        mov ah, 02h
        int 10h
        lodsb
        or al, al
        jz arch_display_exit
        cmp al, 0ah
        je arch_display_row
        mov ah, 0ah
        int 10h
        inc dl
        jmp short arch_display_char
    arch_display_exit:
        pop bp
    };
}

void delay(UInt32 ms)
{
    volatile UInt32 __far *const tick_counter = 0x0040 :> 0x006c;
    if ((ms /= 55)) {
        for (ms += *tick_counter; ms != *tick_counter; );
    }
}

UInt8 pollkbd(void)
{
    if (_kbhit()) {
        int ch = getch();
        if (ch) {
            return ch;
        }
        // Handling of special characters.
        // Map Cursor keys to 'ascii codes' 28-31
        switch (getch()) {
            case 'H': return 28;
            case 'P': return 29;
            case 'K': return 30;
            case 'M': return 31;
            default:
                break;
        }
    }
    return 0;
}

UInt32 gettime(void)
{
    UInt16 low = 0, high = 0;
    // use int 1a instead of 0040:006c here to ensure atomic fetch operation
    _asm {
        xor ah, ah
        int 1ah
        mov high, cx
        mov low, dx
    };
    return (((UInt32)high << 16) | low) * 54945;
}

