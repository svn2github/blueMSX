/*****************************************************************************
** File:        Win32Toolbar.c
**
** Author:      Daniel Vik
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
#include "Disassembly.h"
#include "ToolInterface.h"
#include "Resource.h"
#include <stdio.h>

extern void NotifyCursorPresent(bool isPresent, bool bpState, bool hasBp);

static const char* mnemonicXxCb[256] =
{
	"#","#","#","#","#","#","rlc Y"  ,"#",
	"#","#","#","#","#","#","rrc Y"  ,"#",
	"#","#","#","#","#","#","rl Y"   ,"#",
	"#","#","#","#","#","#","rr Y"   ,"#",
	"#","#","#","#","#","#","sla Y"  ,"#",
	"#","#","#","#","#","#","sra Y"  ,"#",
	"#","#","#","#","#","#","sll Y"  ,"#",
	"#","#","#","#","#","#","srl Y"  ,"#",
	"#","#","#","#","#","#","bit 0,Y","#",
	"#","#","#","#","#","#","bit 1,Y","#",
	"#","#","#","#","#","#","bit 2,Y","#",
	"#","#","#","#","#","#","bit 3,Y","#",
	"#","#","#","#","#","#","bit 4,Y","#",
	"#","#","#","#","#","#","bit 5,Y","#",
	"#","#","#","#","#","#","bit 6,Y","#",
	"#","#","#","#","#","#","bit 7,Y","#",
	"#","#","#","#","#","#","res 0,Y","#",
	"#","#","#","#","#","#","res 1,Y","#",
	"#","#","#","#","#","#","res 2,Y","#",
	"#","#","#","#","#","#","res 3,Y","#",
	"#","#","#","#","#","#","res 4,Y","#",
	"#","#","#","#","#","#","res 5,Y","#",
	"#","#","#","#","#","#","res 6,Y","#",
	"#","#","#","#","#","#","res 7,Y","#",
	"#","#","#","#","#","#","set 0,Y","#",
	"#","#","#","#","#","#","set 1,Y","#",
	"#","#","#","#","#","#","set 2,Y","#",
	"#","#","#","#","#","#","set 3,Y","#",
	"#","#","#","#","#","#","set 4,Y","#",
	"#","#","#","#","#","#","set 5,Y","#",
	"#","#","#","#","#","#","set 6,Y","#",
	"#","#","#","#","#","#","set 7,Y","#"
};

static const char* mnemonicCb[256] =
{
	"rlc b"  ,"rlc c"  ,"rlc d"  ,"rlc e"  ,"rlc h"  ,"rlc l"  ,"rlc (hl)"  ,"rlc a"  ,
	"rrc b"  ,"rrc c"  ,"rrc d"  ,"rrc e"  ,"rrc h"  ,"rrc l"  ,"rrc (hl)"  ,"rrc a"  ,
	"rl b"   ,"rl c"   ,"rl d"   ,"rl e"   ,"rl h"   ,"rl l"   ,"rl (hl)"   ,"rl a"   ,
	"rr b"   ,"rr c"   ,"rr d"   ,"rr e"   ,"rr h"   ,"rr l"   ,"rr (hl)"   ,"rr a"   ,
	"sla b"  ,"sla c"  ,"sla d"  ,"sla e"  ,"sla h"  ,"sla l"  ,"sla (hl)"  ,"sla a"  ,
	"sra b"  ,"sra c"  ,"sra d"  ,"sra e"  ,"sra h"  ,"sra l"  ,"sra (hl)"  ,"sra a"  ,
	"sll b"  ,"sll c"  ,"sll d"  ,"sll e"  ,"sll h"  ,"sll l"  ,"sll (hl)"  ,"sll a"  ,
	"srl b"  ,"srl c"  ,"srl d"  ,"srl e"  ,"srl h"  ,"srl l"  ,"srl (hl)"  ,"srl a"  ,
	"bit 0,b","bit 0,c","bit 0,d","bit 0,e","bit 0,h","bit 0,l","bit 0,(hl)","bit 0,a",
	"bit 1,b","bit 1,c","bit 1,d","bit 1,e","bit 1,h","bit 1,l","bit 1,(hl)","bit 1,a",
	"bit 2,b","bit 2,c","bit 2,d","bit 2,e","bit 2,h","bit 2,l","bit 2,(hl)","bit 2,a",
	"bit 3,b","bit 3,c","bit 3,d","bit 3,e","bit 3,h","bit 3,l","bit 3,(hl)","bit 3,a",
	"bit 4,b","bit 4,c","bit 4,d","bit 4,e","bit 4,h","bit 4,l","bit 4,(hl)","bit 4,a",
	"bit 5,b","bit 5,c","bit 5,d","bit 5,e","bit 5,h","bit 5,l","bit 5,(hl)","bit 5,a",
	"bit 6,b","bit 6,c","bit 6,d","bit 6,e","bit 6,h","bit 6,l","bit 6,(hl)","bit 6,a",
	"bit 7,b","bit 7,c","bit 7,d","bit 7,e","bit 7,h","bit 7,l","bit 7,(hl)","bit 7,a",
	"res 0,b","res 0,c","res 0,d","res 0,e","res 0,h","res 0,l","res 0,(hl)","res 0,a",
	"res 1,b","res 1,c","res 1,d","res 1,e","res 1,h","res 1,l","res 1,(hl)","res 1,a",
	"res 2,b","res 2,c","res 2,d","res 2,e","res 2,h","res 2,l","res 2,(hl)","res 2,a",
	"res 3,b","res 3,c","res 3,d","res 3,e","res 3,h","res 3,l","res 3,(hl)","res 3,a",
	"res 4,b","res 4,c","res 4,d","res 4,e","res 4,h","res 4,l","res 4,(hl)","res 4,a",
	"res 5,b","res 5,c","res 5,d","res 5,e","res 5,h","res 5,l","res 5,(hl)","res 5,a",
	"res 6,b","res 6,c","res 6,d","res 6,e","res 6,h","res 6,l","res 6,(hl)","res 6,a",
	"res 7,b","res 7,c","res 7,d","res 7,e","res 7,h","res 7,l","res 7,(hl)","res 7,a",
	"set 0,b","set 0,c","set 0,d","set 0,e","set 0,h","set 0,l","set 0,(hl)","set 0,a",
	"set 1,b","set 1,c","set 1,d","set 1,e","set 1,h","set 1,l","set 1,(hl)","set 1,a",
	"set 2,b","set 2,c","set 2,d","set 2,e","set 2,h","set 2,l","set 2,(hl)","set 2,a",
	"set 3,b","set 3,c","set 3,d","set 3,e","set 3,h","set 3,l","set 3,(hl)","set 3,a",
	"set 4,b","set 4,c","set 4,d","set 4,e","set 4,h","set 4,l","set 4,(hl)","set 4,a",
	"set 5,b","set 5,c","set 5,d","set 5,e","set 5,h","set 5,l","set 5,(hl)","set 5,a",
	"set 6,b","set 6,c","set 6,d","set 6,e","set 6,h","set 6,l","set 6,(hl)","set 6,a",
	"set 7,b","set 7,c","set 7,d","set 7,e","set 7,h","set 7,l","set 7,(hl)","set 7,a"
};

static const char* mnemonicEd[256] =
{
	"!"       ,"!"        ,"!"        ,"!"        ,"!"  ,"!"   ,"!"   ,"!"     ,
	"!"       ,"!"        ,"!"        ,"!"        ,"!"  ,"!"   ,"!"   ,"!"     ,
	"!"       ,"!"        ,"!"        ,"!"        ,"!"  ,"!"   ,"!"   ,"!"     ,
	"!"       ,"!"        ,"!"        ,"!"        ,"!"  ,"!"   ,"!"   ,"!"     ,
	"!"       ,"!"        ,"!"        ,"!"        ,"!"  ,"!"   ,"!"   ,"!"     ,
	"!"       ,"!"        ,"!"        ,"!"        ,"!"  ,"!"   ,"!"   ,"!"     ,
	"!"       ,"!"        ,"!"        ,"!"        ,"!"  ,"!"   ,"!"   ,"!"     ,
	"!"       ,"!"        ,"!"        ,"!"        ,"!"  ,"!"   ,"!"   ,"!"     ,
	"in b,(c)","out (c),b","sbc hl,bc","ld (W),bc","neg","retn","im 0","ld i,a",
	"in c,(c)","out (c),c","adc hl,bc","ld bc,(W)","!"  ,"reti","!"   ,"ld r,a",
	"in d,(c)","out (c),d","sbc hl,de","ld (W),de","!"  ,"!"   ,"im 1","ld a,i",
	"in e,(c)","out (c),e","adc hl,de","ld de,(W)","!"  ,"!"   ,"im 2","ld a,r",
	"in h,(c)","out (c),h","sbc hl,hl","ld (W),hl","!"  ,"!"   ,"!"   ,"rrd"   ,
	"in l,(c)","out (c),l","adc hl,hl","ld hl,(W)","!"  ,"!"   ,"!"   ,"rld"   ,
	"in 0,(c)","out (c),0","sbc hl,sp","ld (W),sp","!"  ,"!"   ,"!"   ,"!"     ,
	"in a,(c)","out (c),a","adc hl,sp","ld sp,(W)","!"  ,"!"   ,"!"   ,"!"     ,
	"!"       ,"!"        ,"!"        ,"!"        ,"!"  ,"!"   ,"!"   ,"!"     ,
	"!"       ,"!"        ,"!"        ,"!"        ,"!"  ,"!"   ,"!"   ,"!"     ,
	"!"       ,"!"        ,"!"        ,"!"        ,"!"  ,"!"   ,"!"   ,"!"     ,
	"!"       ,"!"        ,"!"        ,"!"        ,"!"  ,"!"   ,"!"   ,"!"     ,
	"ldi"     ,"cpi"      ,"ini"      ,"outi"     ,"!"  ,"!"   ,"!"   ,"!"     ,
	"ldd"     ,"cpd"      ,"ind"      ,"outd"     ,"!"  ,"!"   ,"!"   ,"!"     ,
	"ldir"    ,"cpir"     ,"inir"     ,"otir"     ,"!"  ,"!"   ,"!"   ,"!"     ,
	"lddr"    ,"cpdr"     ,"indr"     ,"otdr"     ,"!"  ,"!"   ,"!"   ,"!"     ,
	"!"       ,"mulub a,b","!"        ,"muluw hl,bc","!","!"   ,"!"   ,"!"     ,
	"!"       ,"mulub a,c","!"        ,"!"        ,"!",  "!"   ,"!"   ,"!"     ,
	"!"       ,"mulub a,d","!"        ,"muluw hl,de","!","!"   ,"!"   ,"!"     ,
	"!"       ,"mulub a,e","!"        ,"!"        ,"!",  "!"   ,"!"   ,"!"     ,
	"!"       ,"mulub a,h","!"        ,"muluw hl,hl","!","!"   ,"!"   ,"!"     ,
	"!"       ,"mulub a,l","!"        ,"!"        ,"!",  "!"   ,"!"   ,"!"     ,
	"!"       ,"mulub a,(hl)","!"     ,"muluw hl,sp","!","!"   ,"!"   ,"!"     ,
	"!"       ,"mulub a,a","!"        ,"!"        ,"!",  "!"   ,"!"   ,"!"
};

static const char* mnemonicXx[256] =
{
	"@"      ,"@"       ,"@"       ,"@"        ,"@"       ,"@"       ,"@"      ,"@"      ,
	"@"      ,"add I,bc","@"       ,"@"        ,"@"       ,"@"       ,"@"      ,"@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"@"       ,"@"       ,"@"      ,"@"      ,
	"@"      ,"add I,de","@"       ,"@"        ,"@"       ,"@"       ,"@"      ,"@"      ,
	"@"      ,"ld I,W"  ,"ld (W),I","inc I"    ,"inc Ih"  ,"dec Ih"  ,"ld Ih,B","@"      ,
	"@"      ,"add I,I" ,"ld I,(W)","dec I"    ,"inc Il"  ,"dec Il"  ,"ld Il,B","@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"inc X"   ,"dec X"   ,"ld X,B" ,"@"      ,
	"@"      ,"add I,sp","@"       ,"@"        ,"@"       ,"@"       ,"@"      ,"@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"ld b,Ih" ,"ld b,Il" ,"ld b,X" ,"@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"ld c,Ih" ,"ld c,Il" ,"ld c,X" ,"@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"ld d,Ih" ,"ld d,Il" ,"ld d,X" ,"@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"ld e,Ih" ,"ld e,Il" ,"ld e,X" ,"@"      ,
	"ld Ih,b","ld Ih,c" ,"ld Ih,d" ,"ld Ih,e"  ,"ld Ih,h" ,"ld Ih,l" ,"ld h,X" ,"ld Ih,a",
	"ld Il,b","ld Il,c" ,"ld Il,d" ,"ld Il,e"  ,"ld Il,h" ,"ld Il,l" ,"ld l,X" ,"ld Il,a",
	"ld X,b" ,"ld X,c"  ,"ld X,d"  ,"ld X,e"   ,"ld X,h"  ,"ld X,l"  ,"@"      ,"ld X,a" ,
	"@"      ,"@"       ,"@"       ,"@"        ,"ld a,Ih" ,"ld a,Il" ,"ld a,X" ,"@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"add a,Ih","add a,Il","add a,X","@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"adc a,Ih","adc a,Il","adc a,X","@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"sub Ih"  ,"sub Il"  ,"sub X"  ,"@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"sbc a,Ih","sbc a,Il","sbc a,X","@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"and Ih"  ,"and Il"  ,"and X"  ,"@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"xor Ih"  ,"xor Il"  ,"xor X"  ,"@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"or Ih"   ,"or Il"   ,"or X"   ,"@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"cp Ih"   ,"cp Il"   ,"cp X"   ,"@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"@"       ,"@"       ,"@"      ,"@"      ,
	"@"      ,"@"       ,"@"       ,"fd cb"    ,"@"       ,"@"       ,"@"      ,"@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"@"       ,"@"       ,"@"      ,"@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"@"       ,"@"       ,"@"      ,"@"      ,
	"@"      ,"pop I"   ,"@"       ,"ex (sp),I","@"       ,"push I"  ,"@"      ,"@"      ,
	"@"      ,"jp (I)"  ,"@"       ,"@"        ,"@"       ,"@"       ,"@"      ,"@"      ,
	"@"      ,"@"       ,"@"       ,"@"        ,"@"       ,"@"       ,"@"      ,"@"      ,
	"@"      ,"ld sp,I" ,"@"       ,"@"        ,"@"       ,"@"       ,"@"      ,"@"
};

static const char* mnemonicMain[256] =
{
	"nop"      ,"ld bc,W"  ,"ld (bc),a","inc bc"    ,"inc b"    ,"dec b"    ,"ld b,B"    ,"rlca"     ,
	"ex af,af'","add hl,bc","ld a,(bc)","dec bc"    ,"inc c"    ,"dec c"    ,"ld c,B"    ,"rrca"     ,
	"djnz R"   ,"ld de,W"  ,"ld (de),a","inc de"    ,"inc d"    ,"dec d"    ,"ld d,B"    ,"rla"      ,
	"jr R"     ,"add hl,de","ld a,(de)","dec de"    ,"inc e"    ,"dec e"    ,"ld e,B"    ,"rra"      ,
	"jr nz,R"  ,"ld hl,W"  ,"ld (W),hl","inc hl"    ,"inc h"    ,"dec h"    ,"ld h,B"    ,"daa"      ,
	"jr z,R"   ,"add hl,hl","ld hl,(W)","dec hl"    ,"inc l"    ,"dec l"    ,"ld l,B"    ,"cpl"      ,
	"jr nc,R"  ,"ld sp,W"  ,"ld (W),a" ,"inc sp"    ,"inc (hl)" ,"dec (hl)" ,"ld (hl),B" ,"scf"      ,
	"jr c,R"   ,"add hl,sp","ld a,(W)" ,"dec sp"    ,"inc a"    ,"dec a"    ,"ld a,B"    ,"ccf"      ,
	"ld b,b"   ,"ld b,c"   ,"ld b,d"   ,"ld b,e"    ,"ld b,h"   ,"ld b,l"   ,"ld b,(hl)" ,"ld b,a"   ,
	"ld c,b"   ,"ld c,c"   ,"ld c,d"   ,"ld c,e"    ,"ld c,h"   ,"ld c,l"   ,"ld c,(hl)" ,"ld c,a"   ,
	"ld d,b"   ,"ld d,c"   ,"ld d,d"   ,"ld d,e"    ,"ld d,h"   ,"ld d,l"   ,"ld d,(hl)" ,"ld d,a"   ,
	"ld e,b"   ,"ld e,c"   ,"ld e,d"   ,"ld e,e"    ,"ld e,h"   ,"ld e,l"   ,"ld e,(hl)" ,"ld e,a"   ,
	"ld h,b"   ,"ld h,c"   ,"ld h,d"   ,"ld h,e"    ,"ld h,h"   ,"ld h,l"   ,"ld h,(hl)" ,"ld h,a"   ,
	"ld l,b"   ,"ld l,c"   ,"ld l,d"   ,"ld l,e"    ,"ld l,h"   ,"ld l,l"   ,"ld l,(hl)" ,"ld l,a"   ,
	"ld (hl),b","ld (hl),c","ld (hl),d","ld (hl),e" ,"ld (hl),h","ld (hl),l","halt"      ,"ld (hl),a",
	"ld a,b"   ,"ld a,c"   ,"ld a,d"   ,"ld a,e"    ,"ld a,h"   ,"ld a,l"   ,"ld a,(hl)" ,"ld a,a"   ,
	"add a,b"  ,"add a,c"  ,"add a,d"  ,"add a,e"   ,"add a,h"  ,"add a,l"  ,"add a,(hl)","add a,a"  ,
	"adc a,b"  ,"adc a,c"  ,"adc a,d"  ,"adc a,e"   ,"adc a,h"  ,"adc a,l"  ,"adc a,(hl)","adc a,a"  ,
	"sub b"    ,"sub c"    ,"sub d"    ,"sub e"     ,"sub h"    ,"sub l"    ,"sub (hl)"  ,"sub a"    ,
	"sbc a,b"  ,"sbc a,c"  ,"sbc a,d"  ,"sbc a,e"   ,"sbc a,h"  ,"sbc a,l"  ,"sbc a,(hl)","sbc a,a"  ,
	"and b"    ,"and c"    ,"and d"    ,"and e"     ,"and h"    ,"and l"    ,"and (hl)"  ,"and a"    ,
	"xor b"    ,"xor c"    ,"xor d"    ,"xor e"     ,"xor h"    ,"xor l"    ,"xor (hl)"  ,"xor a"    ,
	"or b"     ,"or c"     ,"or d"     ,"or e"      ,"or h"     ,"or l"     ,"or (hl)"   ,"or a"     ,
	"cp b"     ,"cp c"     ,"cp d"     ,"cp e"      ,"cp h"     ,"cp l"     ,"cp (hl)"   ,"cp a"     ,
	"ret nz"   ,"pop bc"   ,"jp nz,W"  ,"jp W"      ,"call nz,W","push bc"  ,"add a,B"   ,"rst 00h"  ,
	"ret z"    ,"ret"      ,"jp z,W"   ,"cb"        ,"call z,W" ,"call W"   ,"adc a,B"   ,"rst 08h"  ,
	"ret nc"   ,"pop de"   ,"jp nc,W"  ,"out (B),a" ,"call nc,W","push de"  ,"sub B"     ,"rst 10h"  ,
	"ret c"    ,"exx"      ,"jp c,W"   ,"in a,(B)"  ,"call c,W" ,"dd"       ,"sbc a,B"   ,"rst 18h"  ,
	"ret po"   ,"pop hl"   ,"jp po,W"  ,"ex (sp),hl","call po,W","push hl"  ,"and B"     ,"rst 20h"  ,
	"ret pe"   ,"jp (hl)"  ,"jp pe,W"  ,"ex de,hl"  ,"call pe,W","ed"       ,"xor B"     ,"rst 28h"  ,
	"ret p"    ,"pop af"   ,"jp p,W"   ,"di"        ,"call p,W" ,"push af"  ,"or B"      ,"rst 30h"  ,
	"ret m"    ,"ld sp,hl" ,"jp m,W"   ,"ei"        ,"call m,W" ,"fd"       ,"cp B"      ,"rst 38h"
};

#define SIGN(val) (((val) & 128) ? '-' : '+')
#define ABS(val)  (((val) & 128) ? 256 - (val) : val)


int Disassembly::dasm(BYTE* memory, WORD PC, char* dest)
{
	const char* r = "INTERNAL PROGRAM ERROR";
	char offset = 0;
	const char* S;
	char buf[32];
	int pc = PC;
    int j;
    int k;
    BYTE val0;
    BYTE val1;
    BYTE val2;
    BYTE val;

	dest[0] = '\0';

    val0 = memory[pc++];

	switch (val0) {
	case 0xcb:
        val1 = memory[pc++];
		S = mnemonicCb[val1];
		break;
	case 0xed:
        val1 = memory[pc++];
		S = mnemonicEd[val1];
		break;
	case 0xdd:
		r = "ix";
        val1 = memory[pc++];
		switch (val1) {
		case 0xcb:
            val2 = memory[pc++];
			offset = val2;
			S = mnemonicXxCb[memory[pc++]];
			break;
		default:
			S = mnemonicXx[val1];
			break;
		}
		break;
	case 0xfd:
		r = "iy";
        val1 = memory[pc++];
		switch (val1) {
		case 0xcb:
            val2 = memory[pc++];
			offset = val2;
			S = mnemonicXxCb[memory[pc++]];
			break;
		default:
			S = mnemonicXx[val1];
			break;
		}
		break;
	default:
		S = mnemonicMain[val0];
		break;
    }

	for (j = 0; S[j]; j++) {
		switch (S[j]) {
		case 'B':
			sprintf(buf, "#%02x", memory[pc++]);
			strcat(dest, buf);
			break;
		case 'R':
			sprintf (buf, "#%04x", (PC + 2 + (char)memory[pc++]) & 0xFFFF);
			strcat(dest, buf);
			break;
		case 'W':
            val = memory[pc++];
			sprintf(buf, "#%04x", val + memory[pc++] * 256);
			strcat(dest, buf);
			break;
		case 'X':
            val = memory[pc++];
			sprintf(buf, "(%s%c#%02x)", r, SIGN(val), ABS(val));
			strcat(dest, buf);
			break;
		case 'Y':
			sprintf(buf, "(%s%c#%02x)", r, SIGN(offset), ABS(offset));
			strcat(dest, buf);
			break;
		case 'I':
			strcat(dest, r);
			break;
		case '!':
			sprintf(dest,"db     #ED, #%02x", val1);
			return 2;
		case '@':
			sprintf(dest,"db     #%02x", val0);
			return 1;
		case '#':
			sprintf(dest, "db     #%02x,#CB,#%02x", val0, val2);
			return 2;
		case ' ': {
			int k = strlen(dest);
            if (k < 6) {
                k = 7 - k;
            }
            else {
                k = 1;
            }

			memset(buf, ' ', k);
			buf[k] = '\0';
			strcat(dest, buf);
			break;
		}
		default:
			buf[0] = S[j];
			buf[1] = '\0';
			strcat(dest, buf);
			break;
		}
	}
	
    k = strlen(dest);
    if (k < 17) {
        k = 18 - k;
    }
    else {
        k = 1;
    }

	memset (buf, ' ', k);
	buf[k] = '\0';
	strcat(dest, buf);

	return pc - PC;
}



namespace {

class BitmapIcons 
{
public:
    BitmapIcons(HINSTANCE hInstance, int id, int count) {
        HBITMAP hBitmap = (HBITMAP)LoadBitmap(hInstance, MAKEINTRESOURCE(id));
        hMemDC  = CreateCompatibleDC(GetWindowDC(NULL));
        SelectObject(hMemDC, hBitmap);
        
        BITMAP bmp; 
        GetObject(hBitmap, sizeof(BITMAP), (PSTR)&bmp);
        width  = bmp.bmWidth / count;
        height = bmp.bmHeight;
    }

    ~BitmapIcons() {
        DeleteDC(hMemDC);
    }

    void drawIcon(HDC hdc, int x, int y, int index) {
        BitBlt(hdc, x, y, width, height, hMemDC, width * index, 0, SRCCOPY);
    }

private:
    HDC hMemDC;
    int width;
    int height;
};

}

static Disassembly* disassembly = NULL;
static BitmapIcons* bitmapIcons = NULL;

static LRESULT CALLBACK dasmWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    return disassembly->wndProc(hwnd, iMsg, wParam, lParam);
}

LRESULT Disassembly::wndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    HDC hdc;

    switch (iMsg) {
    case WM_CREATE:
        hdc = GetDC(hwnd);
        hMemdc = CreateCompatibleDC(hdc);
        ReleaseDC(hwnd, hdc);
        SetBkMode(hMemdc, TRANSPARENT);
        hFont = CreateFont(-MulDiv(10, GetDeviceCaps(hMemdc, LOGPIXELSY), 72), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New");

        hBrushWhite  = CreateSolidBrush(RGB(255, 255, 255));
        hBrushLtGray = CreateSolidBrush(RGB(239, 237, 222));
        hBrushDkGray = CreateSolidBrush(RGB(222, 222, 255));
        
        colorBlack = RGB(0, 0, 0);
        colorGray  = RGB(160, 160, 160);

        SelectObject(hMemdc, hFont); 
        TEXTMETRIC tm;
        if (GetTextMetrics(hMemdc, &tm)) {
            textHeight = tm.tmHeight;
            textWidth = tm.tmMaxCharWidth;
        }
        return 0;

    case WM_ERASEBKGND:
        return 1;

    case WM_SIZE:
        updateScroll();
        break;

    case WM_VSCROLL:
        scrollWindow(LOWORD(wParam));
         return 0;

    case WM_LBUTTONDOWN:
        SetFocus(hwnd);
        return 0;

    case WM_LBUTTONUP:
        if (lineCount > 10) {
            SCROLLINFO si;
            si.cbSize = sizeof (si);
            si.fMask  = SIF_POS;
            GetScrollInfo (hwnd, SB_VERT, &si);
            int row = si.nPos + HIWORD(lParam) / textHeight;
            if (LOWORD(lParam) < 25) {
                toggleBreakpoint(lineInfo[row].address);
            }
            else {
                currentLine = row;
            }
            NotifyCursorPresent(true, (currentLine >= 0 && breakpoint[lineInfo[currentLine].address] != BP_NONE), breakpointCount > 0);
            InvalidateRect(hwnd, NULL, TRUE);
        }
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            RECT r;
            GetClientRect(hwnd, &r);
            int top    = ps.rcPaint.top;
            int height = ps.rcPaint.bottom - ps.rcPaint.top;

            HBITMAP hBitmap = CreateCompatibleBitmap(GetWindowDC(NULL), r.right, r.bottom);
            HBITMAP hBitmapOrig = (HBITMAP)SelectObject(hMemdc, hBitmap);

            SelectObject(hMemdc, hBrushLtGray);  
            PatBlt(hMemdc, 0, top, 21, height, PATCOPY);
            
            SelectObject(hMemdc, hBrushWhite); 
            PatBlt(hMemdc, 21, top, r.right - 21, height, PATCOPY);

            drawText(ps.rcPaint.top, ps.rcPaint.bottom);

            BitBlt(hdc, 0, top, r.right, height, hMemdc, 0, top, SRCCOPY);

            DeleteObject(SelectObject(hMemdc, hBitmapOrig));
            EndPaint(hwnd, &ps);
        }
        return TRUE;

    case WM_DESTROY:
        DeleteObject(hBrushWhite);
        DeleteObject(hBrushLtGray);
        DeleteObject(hBrushDkGray);
        DeleteDC(hMemdc);
        break;
    }

    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}


Disassembly::Disassembly(HINSTANCE hInstance, HWND owner) : 
    linePos(0), lineCount(0), currentLine(-1), programCounter(0), 
    firstVisibleLine(0), editEnabled(false), runtoBreakpoint(-1), breakpointCount(0)
{
    disassembly = this;

    static WNDCLASSEX wndClass;

    wndClass.cbSize         = sizeof(wndClass);
    wndClass.style          = CS_VREDRAW;
    wndClass.lpfnWndProc    = dasmWndProc;
    wndClass.cbClsExtra     = 0;
    wndClass.cbWndExtra     = 0;
    wndClass.hInstance      = hInstance;
    wndClass.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BLUEMSX));
    wndClass.hIconSm        = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BLUEMSX));
    wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground  = NULL;
    wndClass.lpszMenuName   = NULL;
    wndClass.lpszClassName  = "msxdasm";

    RegisterClassEx(&wndClass);

    if (bitmapIcons == NULL) {
        bitmapIcons = new BitmapIcons(hInstance, IDB_DASMICONS, 5);
    }

    for (int i = 0; i < 0x10000; i++) {
        breakpoint[i] = BP_NONE;
    }

    hwnd = CreateWindowEx(WS_EX_TOOLWINDOW, "msxdasm", "Disassembly", 
                          WS_OVERLAPPED | WS_CLIPSIBLINGS | WS_CHILD | WS_BORDER | WS_THICKFRAME | WS_DLGFRAME, 
                          CW_USEDEFAULT, CW_USEDEFAULT, 100, 100, owner, NULL, hInstance, NULL);
    invalidateContent();
}

Disassembly::~Disassembly()
{
}

void Disassembly::show()
{
    ShowWindow(hwnd, true);
}

void Disassembly::hide()
{
    ShowWindow(hwnd, false);
}

void Disassembly::enableEdit()
{
    editEnabled = true;
}

void Disassembly::disableEdit()
{
    editEnabled = false;
}

void Disassembly::updatePosition(RECT& rect)
{
    SetWindowPos(hwnd, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
}

void Disassembly::toggleBreakpoint(int address) 
{
    if (address == -1) {
        if (currentLine == -1) {
            return;
        }
        address = lineInfo[currentLine].address;
    }
    if (breakpoint[address] == BP_NONE) {
        breakpointCount++;
        breakpoint[address] = BP_SET;
        SetBreakpoint(address);
    }
    else {
        breakpointCount--;
        breakpoint[address] = BP_NONE;
        ClearBreakpoint(address);
    }
    NotifyCursorPresent(true, breakpoint[address] != BP_NONE, breakpointCount > 0);
    InvalidateRect(hwnd, NULL, TRUE);
}

void Disassembly::toggleBreakpointEnable()
{
    if (currentLine == -1) {
        return;
    }
    int address = lineInfo[currentLine].address;

    if (breakpoint[address] == BP_DISABLED) {
        breakpointCount--;
        breakpoint[address] = BP_SET;
        SetBreakpoint(address);
    }
    else if (breakpoint[address] == BP_SET) {
        breakpointCount++;
        breakpoint[address] = BP_DISABLED;
        ClearBreakpoint(address);
    }
    NotifyCursorPresent(true, breakpoint[address] != BP_NONE, breakpointCount > 0);
    InvalidateRect(hwnd, NULL, TRUE);
}

void Disassembly::clearAllBreakpoints()
{
    for (int address = 0; address < 0x10000; address++) {
        if (breakpoint[address] == BP_SET) {
            ClearBreakpoint(address);
        }
        breakpoint[address] = BP_NONE;
    }
    breakpointCount = 0;
    NotifyCursorPresent(true, breakpoint[address] != BP_NONE, breakpointCount > 0);
    InvalidateRect(hwnd, NULL, TRUE);
}

void Disassembly::updateBreakpoints()
{
    for (int addr = 0; addr < 0x10000; addr++) {
        if (breakpoint[addr] == BP_SET) {
            SetBreakpoint(addr);
        }
    }
    InvalidateRect(hwnd, NULL, TRUE);
}

void Disassembly::setRuntoBreakpoint()
{
    if (currentLine >= 0) {
        runtoBreakpoint = lineInfo[currentLine].address;
        SetBreakpoint(runtoBreakpoint);
    }
}

void Disassembly::clearRuntoBreakpoint()
{
    if (runtoBreakpoint >= 0) {
        if (breakpoint[runtoBreakpoint] != BP_SET) {
            ClearBreakpoint(runtoBreakpoint);
        }
    }
}


void Disassembly::invalidateContent()
{
    clearRuntoBreakpoint();
    NotifyCursorPresent(false, false, breakpointCount > 0);
    currentLine = -1;
    lineCount = 0;
    updateScroll();

    sprintf(lineInfo[lineCount].text, "Disassembly unavailable.");
    lineInfo[lineCount].textLength = strlen(lineInfo[lineCount].text);
    lineInfo[lineCount].haspc = 0;
    lineInfo[lineCount].dataText[0] = 0;
    lineInfo[lineCount].dataTextLength = 0;
    lineCount++;
    
    InvalidateRect(hwnd, NULL, TRUE);
}

void Disassembly::updateContent(BYTE* memory, WORD pc)
{
    clearRuntoBreakpoint();

    lineCount = 0;
    programCounter = 0;

    for (int addr = 0; addr < 0x10000; ) {
        sprintf(lineInfo[lineCount].text, "%.4X:               ", addr);
        int len = dasm(memory, addr, lineInfo[lineCount].text + 18);
        lineInfo[lineCount].textLength = strlen(lineInfo[lineCount].text);
        lineInfo[lineCount].address = addr;
        lineInfo[lineCount].haspc = addr == pc;

        lineInfo[lineCount].dataText[0] = 0;
        lineInfo[lineCount].dataTextLength = 0;

        if (addr == pc) {
            programCounter = lineCount;
        }
        int i = min(3, len);
        while (i--) {
            char text[16];
            sprintf(text, "%.2x ", memory[addr]);
            strcat(lineInfo[lineCount].dataText, text);
            lineInfo[lineCount].dataTextLength += 3;
            len--;
            addr++;
        }
        addr += len;
        lineCount++;
    }
    updateScroll();
    InvalidateRect(hwnd, NULL, TRUE);
}

void Disassembly::updateScroll() 
{
    RECT r;
    GetClientRect(hwnd, &r);
    int visibleLines = r.bottom / textHeight;

    if (programCounter < firstVisibleLine + visibleLines / 4) {
        firstVisibleLine = programCounter - visibleLines / 2;
    }

    if (programCounter >= firstVisibleLine + visibleLines - 1) {
        firstVisibleLine = programCounter - visibleLines / 2;
    }

    if (firstVisibleLine >= lineCount) {
        firstVisibleLine = lineCount - visibleLines;
    }

    firstVisibleLine = max(0, firstVisibleLine);

    SCROLLINFO si;
    si.cbSize    = sizeof(SCROLLINFO);
    
    GetScrollInfo(hwnd, SB_VERT, &si);
    int oldFirstLine = si.nPos;

    si.fMask     = SIF_PAGE | SIF_POS | SIF_RANGE | (visibleLines >= lineCount ? 0 : 0);
    si.nMin      = 0;
    si.nMax      = lineCount;
    si.nPage     = visibleLines;
    si.nPos      = firstVisibleLine;

    SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
    
    GetScrollInfo(hwnd, SB_VERT, &si);
    
    if (si.nPos != oldFirstLine) {
        InvalidateRect(hwnd, NULL, TRUE);
    }
}

void Disassembly::scrollWindow(int sbAction)
{
    int yPos;
    SCROLLINFO si;

    si.cbSize = sizeof (si);
    si.fMask  = SIF_ALL;
    GetScrollInfo (hwnd, SB_VERT, &si);
    yPos = si.nPos;
    switch (sbAction) {
    case SB_TOP:
        si.nPos = si.nMin;
        break;
    case SB_BOTTOM:
        si.nPos = si.nMax;
        break;
    case SB_LINEUP:
        si.nPos -= 1;
        break;
    case SB_LINEDOWN:
        si.nPos += 1;
        break;
    case SB_PAGEUP:
        si.nPos -= si.nPage;
        break;
    case SB_PAGEDOWN:
        si.nPos += si.nPage;
        break;
    case SB_THUMBTRACK:
        si.nPos = si.nTrackPos;
        break;              
    default:
        break; 
    }

    si.fMask = SIF_POS;
    SetScrollInfo (hwnd, SB_VERT, &si, TRUE);
    GetScrollInfo (hwnd, SB_VERT, &si);
    if (si.nPos != yPos) {                    
        ScrollWindow(hwnd, 0, textHeight * (yPos - si.nPos), NULL, NULL);
        UpdateWindow (hwnd);
    }
}

void Disassembly::drawText(int top, int bottom)
{
    SCROLLINFO si;

    si.cbSize = sizeof (si);
    si.fMask  = SIF_POS;
    GetScrollInfo (hwnd, SB_VERT, &si);
    int yPos = si.nPos;
    int FirstLine = max (0, yPos + top / textHeight);
    int LastLine = min (lineCount - 1, yPos + bottom / textHeight);

    RECT r = { 30, textHeight * (FirstLine - yPos), 300, textHeight };

    r.bottom += r.top;

    for (int i = FirstLine; i <= LastLine; i++) {
        if (i == currentLine) {
            RECT rc;
            GetClientRect(hwnd, &rc);
            SelectObject(hMemdc, hBrushDkGray); 
            PatBlt(hMemdc, 21, r.top, rc.right - 21, r.bottom - r.top, PATCOPY);
        }

        int address = lineInfo[i].address;
        if (lineInfo[i].haspc) {
            if (breakpoint[address] == BP_SET) {
                bitmapIcons->drawIcon(hMemdc, 4, r.top, 3);
            }
            else if (breakpoint[address] == BP_DISABLED) {
                bitmapIcons->drawIcon(hMemdc, 4, r.top, 3);
            }
            else {
                bitmapIcons->drawIcon(hMemdc, 4, r.top, 0);
            }
        }
        else {
            if (breakpoint[address] == BP_SET) {
                bitmapIcons->drawIcon(hMemdc, 4, r.top, 1);
            }
            else if (breakpoint[address] == BP_DISABLED) {
                bitmapIcons->drawIcon(hMemdc, 4, r.top, 2);
            }
        }

        SetTextColor(hMemdc, colorGray);
        r.left += 6 * textWidth;
        DrawText(hMemdc, lineInfo[i].dataText, lineInfo[i].dataTextLength, &r, DT_LEFT);
        r.left -= 6 * textWidth;
        SetTextColor(hMemdc, colorBlack);

        DrawText(hMemdc, lineInfo[i].text, lineInfo[i].textLength, &r, DT_LEFT);
        r.top += textHeight;
        r.bottom += textHeight;
    }
}