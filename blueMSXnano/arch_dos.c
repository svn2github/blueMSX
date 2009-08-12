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

static UInt8 mono = 0;

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
    /* perform semi-intelligent display type detection.
     * mda, hercules and mono ega/vga will use 80x25 mono text screen mode.
     * others will use 40x25 color text screen mode.
     * hides cursor.
     */
    _asm {
        mov bx, 1
        push es
        mov ax, 0040h
        mov es, ax
        mov al, byte ptr es:[00049h]
        pop es
        cmp al, 7
        jne not_mono
        int 11h
        and al, 30h
        cmp al, 30h
        jne not_mono
        mov mono, 1
        mov bl, 7
    not_mono:
        mov ax, bx
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
        push es
        cmp mono, 0
        je display_color
        mov ax, 0b000h
        mov cx, 80 *2
        mov dl, 07h
        jmp short display_setup
    display_color:
        mov ax, 0b800h
        mov cx, 40 * 2
        mov dl, 1fh
    display_setup:
        mov es, ax
        xor bx, bx
        mov si, buffer
        cld
    display_row:
        mov di, bx
        add bx, cx
    display_char:
        lodsb
        or al, al
        jz display_exit
        cmp al, 0ah
        je display_row
        mov ah, dl
        stosw
        jmp short display_char
    display_exit:
        pop es
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
    volatile UInt32 __far *const tick_counter = 0x0040 :> 0x006c;
    UInt32 time;
    _asm {
        pushf
        cli
    };
    time = *tick_counter * 54945;
    _asm {
        popf
    };
    return time;
}

