/*****************************************************************************
** $Source: /cvsroot/bluemsx/blueMSX/Src/Z80/Z80.c,v $
**
** $Revision: 1.31 $
**
** $Date: 2007/08/05 18:05:05 $
**
** Author: Daniel Vik
**
** Description: Emulation of the Z80/Z80 processor
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

#include "z80.h"
#include <stdlib.h>
#include <stdio.h>

typedef void (*Opcode)();
typedef void (*OpcodeNn)(UInt16);

static UInt8  ZSXYTable[256];
static UInt8  ZSPXYTable[256];
static UInt8  ZSPHTable[256];
static UInt16 DAATable[0x800];


static void cb();
static void dd();
static void ed();
static void fd();
static void dd_cb();
static void fd_cb();

#define INT_LOW   0
#define INT_EDGE  1
#define INT_HIGH  2



#define delayMem(z80)      z80.systemTime += 3
#define delayMemOp(z80)    z80.systemTime += 3
#define delayMemPage(z80)  z80.systemTime += 0
#define delayPreIo(z80)    z80.systemTime += 1
#define delayPostIo(z80)   z80.systemTime += 3
#define delayM1(z80)       z80.systemTime += 2
#define delayXD(z80)       z80.systemTime += 1
#define delayIm(z80)       z80.systemTime += 2
#define delayIm2(z80)      z80.systemTime += 19
#define delayNmi(z80)      z80.systemTime += 11
#define delayParallel(z80) z80.systemTime += 2
#define delayBlock(z80)    z80.systemTime += 5
#define delayAdd8(z80)     z80.systemTime += 5
#define delayAdd16(z80)    z80.systemTime += 7
#define delayBit(z80)      z80.systemTime += 1
#define delayCall(z80)     z80.systemTime += 1
#define delayDjnz(z80)     z80.systemTime += 1
#define delayExSpHl(z80)   z80.systemTime += 3
#define delayInc(z80)      z80.systemTime += 1
#define delayInc16(z80)    z80.systemTime += 2
#define delayInOut(z80)    z80.systemTime += 1
#define delayLd(z80)       z80.systemTime += 1
#define delayLdi(z80)      z80.systemTime += 2
#define delayMul8(z80)     z80.systemTime += 0
#define delayMul16(z80)    z80.systemTime += 0
#define delayPush(z80)     z80.systemTime += 1
#define delayRet(z80)      z80.systemTime += 1
#define delayRld(z80)      z80.systemTime += 4
#define delayT9769(z80)    z80.systemTime += 0
#define delayLdSpHl(z80)   z80.systemTime += 2
#define delayBitIx(z80)    z80.systemTime += 2


Z80 z80;


static UInt8 readPort(UInt16 port) {
    UInt8 value;

    z80.regs.SH.W = port + 1;
    delayPreIo(z80);

    value = readIoPort(port);
    delayPostIo(z80);

    return value;

}

static void writePort(UInt16 port, UInt8 value) {
    z80.regs.SH.W = port + 1;
    delayPreIo(z80);

    writeIoPort(port, value);
    delayPostIo(z80);

}

static UInt8 readMem(UInt16 address) {
    delayMem(z80);
    return readMemory(address);
}

static UInt8 readOpcode(UInt16 address) {
    delayMemOp(z80);
    return readMemory(address);
}

static void writeMem(UInt16 address, UInt8 value) {
    delayMem(z80);
    writeMemory(address, value);
}

static void INC(UInt8* reg) {
    UInt8 regVal = ++(*reg);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | ZSXYTable[regVal] |
        (regVal == 0x80 ? V_FLAG : 0) |
        (!(regVal & 0x0f) ? H_FLAG : 0);
}

static void DEC(UInt8* reg) {
    UInt8 regVal = --(*reg);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | ZSXYTable[regVal] | 
        N_FLAG | (regVal == 0x7f ? V_FLAG : 0) |
        ((regVal & 0x0f) == 0x0f ? H_FLAG : 0);
}

static void ADD(UInt8 reg) {
    int rv = z80.regs.AF.B.h + reg;
    z80.regs.AF.B.l = ZSXYTable[rv & 0xff] | ((rv >> 8) & C_FLAG) |
        ((z80.regs.AF.B.h ^ rv ^ reg) & H_FLAG) |
        ((((reg ^ z80.regs.AF.B.h ^ 0x80) & (reg ^ rv)) >> 5) & V_FLAG);
    z80.regs.AF.B.h = rv;
}

static void ADDW(UInt16* reg1, UInt16 reg2) { //DIFF

    int rv = *reg1 + reg2;

    z80.regs.SH.W   = *reg1 + 1;
    z80.regs.AF.B.l = (z80.regs.AF.B.l & (S_FLAG | Z_FLAG | V_FLAG)) |
        (((*reg1 ^ reg2 ^ rv) >> 8) & H_FLAG) |
        ((rv >> 16) & C_FLAG) |
        ((rv >> 8) & (X_FLAG | Y_FLAG));
    *reg1 = rv;
    delayAdd16(z80);
}

static void ADC(UInt8 reg) {
    int rv = z80.regs.AF.B.h + reg + (z80.regs.AF.B.l & C_FLAG);
    z80.regs.AF.B.l = ZSXYTable[rv & 0xff] | ((rv >> 8) & C_FLAG) |
        ((z80.regs.AF.B.h ^ rv ^ reg) & H_FLAG) |
        ((((reg ^ z80.regs.AF.B.h ^ 0x80) & (reg ^ rv)) >> 5) & V_FLAG);
    z80.regs.AF.B.h = rv;
}

static void ADCW(UInt16 reg) {
    int rv = z80.regs.HL.W + reg + (z80.regs.AF.B.l & C_FLAG);

    z80.regs.SH.W   = z80.regs.HL.W + 1;
    z80.regs.AF.B.l = (((z80.regs.HL.W ^ reg ^ rv) >> 8) & H_FLAG) | 
        ((rv >> 16) & C_FLAG) | ((rv & 0xffff) ? 0 : Z_FLAG) |
        ((((reg ^ z80.regs.HL.W ^ 0x8000) & (reg ^ rv)) >> 13) & V_FLAG) |
        ((rv >> 8) & (S_FLAG | X_FLAG | Y_FLAG));
    z80.regs.HL.W = rv;
    delayAdd16(z80);
}

static void SUB(UInt8 reg) {
    int regVal = z80.regs.AF.B.h;
    int rv = regVal - reg;
    z80.regs.AF.B.l = ZSXYTable[rv & 0xff] | ((rv >> 8) & C_FLAG) |
        ((regVal ^ rv ^ reg) & H_FLAG) | N_FLAG |
        ((((reg ^ regVal) & (rv ^ regVal)) >> 5) & V_FLAG);
    z80.regs.AF.B.h = rv;
} 

static void SBC(UInt8 reg) {
    int regVal = z80.regs.AF.B.h;
    int rv = regVal - reg - (z80.regs.AF.B.l & C_FLAG);
    z80.regs.AF.B.l = ZSXYTable[rv & 0xff] | ((rv >> 8) & C_FLAG) |
        ((regVal ^ rv ^ reg) & H_FLAG) | N_FLAG |
        ((((reg ^ regVal) & (rv ^ regVal)) >> 5) & V_FLAG);
    z80.regs.AF.B.h = rv;
}

static void SBCW(UInt16 reg) {
    int regVal = z80.regs.HL.W;
    int rv = regVal - reg - (z80.regs.AF.B.l & C_FLAG);
    z80.regs.SH.W   = regVal + 1;
    z80.regs.AF.B.l = (((regVal ^ reg ^ rv) >> 8) & H_FLAG) | N_FLAG |
        ((rv >> 16) & C_FLAG) | ((rv & 0xffff) ? 0 : Z_FLAG) | 
        ((((reg ^ regVal) & (regVal ^ rv)) >> 13) & V_FLAG) |
        ((rv >> 8) & (S_FLAG | X_FLAG | Y_FLAG));
    z80.regs.HL.W = rv;
    delayAdd16(z80);
}

static void CP(UInt8 reg) {
    int regVal = z80.regs.AF.B.h;
    int rv = regVal - reg;
    z80.regs.AF.B.l = (ZSPXYTable[rv & 0xff] & (Z_FLAG | S_FLAG)) | 
        ((rv >> 8) & C_FLAG) |
        ((regVal ^ rv ^ reg) & H_FLAG) | N_FLAG |
        ((((reg ^ regVal) & (rv ^ regVal)) >> 5) & V_FLAG) |
        (reg & (X_FLAG | Y_FLAG));
}

static void AND(UInt8 reg) {
    z80.regs.AF.B.h &= reg;
    z80.regs.AF.B.l = ZSPXYTable[z80.regs.AF.B.h] | H_FLAG;
} 

static void OR(UInt8 reg) {
    z80.regs.AF.B.h |= reg;
    z80.regs.AF.B.l = ZSPXYTable[z80.regs.AF.B.h];
} 

static void XOR(UInt8 reg) {
    z80.regs.AF.B.h ^= reg;
    z80.regs.AF.B.l = ZSPXYTable[z80.regs.AF.B.h];
}

static void MULU(UInt8 reg) { // Diff on mask // RuMSX: (S_FLAG & V_FLAG)
    z80.regs.HL.W = (Int16)z80.regs.AF.B.h * reg;
    z80.regs.AF.B.l = (z80.regs.AF.B.l & (N_FLAG | H_FLAG)) |
        (z80.regs.HL.W ? 0 : Z_FLAG) | ((z80.regs.HL.W >> 15) & C_FLAG);
    delayMul8(z80);
}

static void MULUW(UInt16 reg) { // Diff on mask // RuMSX: (S_FLAG & V_FLAG)
    UInt32 rv = (UInt32)z80.regs.HL.W * reg;
    z80.regs.DE.W = (UInt16)(rv >> 16);
    z80.regs.HL.W = (UInt16)(rv & 0xffff);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & (N_FLAG | H_FLAG)) |
        (rv ? 0 : Z_FLAG) | (UInt8)((rv >> 31) & C_FLAG);
    delayMul16(z80);
}

static void SLA(UInt8* reg) {
    UInt8 regVal = *reg;
    regVal = regVal << 1;
    z80.regs.AF.B.l = ZSPXYTable[regVal] | ((*reg >> 7) & C_FLAG);
    *reg = regVal;
}

static void SLL(UInt8* reg) {
    UInt8 regVal = *reg;
    regVal = (regVal << 1) | 1;
    z80.regs.AF.B.l = ZSPXYTable[regVal] | ((*reg >> 7) & C_FLAG);
    *reg = regVal;
}

static void SRA(UInt8* reg) {
    UInt8 regVal = *reg;
    regVal = (regVal >> 1) | (regVal & 0x80);
    z80.regs.AF.B.l = ZSPXYTable[regVal] | (*reg & C_FLAG);
    *reg = regVal;
}

static void SRL(UInt8* reg) {
    UInt8 regVal = *reg;
    regVal = regVal >> 1;
    z80.regs.AF.B.l = ZSPXYTable[regVal] | (*reg & C_FLAG);
    *reg = regVal;
}

static void RL(UInt8* reg) {
    UInt8 regVal = *reg;
    regVal = (regVal << 1) | (z80.regs.AF.B.l & 0x01);
    z80.regs.AF.B.l = ZSPXYTable[regVal] | ((*reg >> 7) & C_FLAG);
    *reg = regVal;
}

static void RLC(UInt8* reg) {
    UInt8 regVal = *reg;
    regVal= (regVal << 1) | (regVal >> 7);
    z80.regs.AF.B.l = ZSPXYTable[regVal] | (regVal & C_FLAG);
    *reg = regVal;
}

static void RR(UInt8* reg) {
    UInt8 regVal = *reg;
    regVal = (regVal >> 1) | (z80.regs.AF.B.l << 7);
    z80.regs.AF.B.l = ZSPXYTable[regVal] | (*reg & C_FLAG);
    *reg = regVal;
}

static void RRC(UInt8* reg) {
    UInt8 regVal = *reg;
    regVal= (regVal >> 1) | (regVal << 7);
    z80.regs.AF.B.l = ZSPXYTable[regVal] | ((regVal >> 7) & C_FLAG);
    *reg = regVal;
}

static void BIT(UInt8 bit, UInt8 reg) {
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) |
        (reg & (X_FLAG | Y_FLAG)) | ZSPHTable[reg & (1 << bit)];
}

static void RES(UInt8 bit, UInt8* reg) {
    *reg &= ~(1 << bit);
}

static void SET(UInt8 bit, UInt8* reg) {
    *reg |= 1 << bit;
}

static void JR() {
    RegisterPair addr;

    addr.W = z80.regs.PC.W + 1 + (Int8)readOpcode(z80.regs.PC.W);
    z80.regs.PC.W = addr.W;
    z80.regs.SH.W = addr.W;
    delayAdd8(z80);
}

static void SKIP_JR() {
    readOpcode(z80.regs.PC.W++);
}

static void JP() {
    RegisterPair addr;

    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    z80.regs.PC.W = addr.W;
    z80.regs.SH.W = addr.W;
}

static void SKIP_JP() {
    RegisterPair addr;

    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    z80.regs.SH.W = addr.W;
}

static void CALL() {
    RegisterPair addr;

    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    delayCall(z80);
#ifdef ENABLE_CALLSTACK
    z80.callstack[z80.callstackSize++ & 0xff] = z80.regs.PC.W;
#endif
    writeMem(--z80.regs.SP.W, z80.regs.PC.B.h);
    writeMem(--z80.regs.SP.W, z80.regs.PC.B.l);
    z80.regs.PC.W = addr.W;
    z80.regs.SH.W = addr.W;
}

static void SKIP_CALL() {
    RegisterPair addr;

    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    z80.regs.SH.W = addr.W;
}

static void RET() { 
    RegisterPair addr;
    addr.B.l = readMem(z80.regs.SP.W++);
    addr.B.h = readMem(z80.regs.SP.W++);
    z80.regs.PC.W = addr.W;
    z80.regs.SH.W = addr.W;
#ifdef ENABLE_CALLSTACK
    if (z80.callstack[(z80.callstackSize - 1) & 0xff] == addr.W) {
        z80.callstackSize--;
    }
#endif
}

static void PUSH(UInt16* reg) {
    RegisterPair* pair = (RegisterPair*)reg;
    delayPush(z80);
    writeMem(--z80.regs.SP.W, pair->B.h);
    writeMem(--z80.regs.SP.W, pair->B.l);
}

static void POP(UInt16* reg) {
    RegisterPair* pair = (RegisterPair*)reg;
    pair->B.l = readMem(z80.regs.SP.W++);
    pair->B.h = readMem(z80.regs.SP.W++);
}

static void RST(UInt16 vector) {
#ifdef ENABLE_CALLSTACK
    z80.callstack[z80.callstackSize++ & 0xff] = z80.regs.PC.W;
#endif
    PUSH(&z80.regs.PC.W);
    z80.regs.PC.W = vector;
    z80.regs.SH.W = vector;
}

static void EX_SP(UInt16* reg) {
    RegisterPair* pair = (RegisterPair*)reg;
    RegisterPair addr;

    addr.B.l = readMem(z80.regs.SP.W++);
    addr.B.h = readMem(z80.regs.SP.W);
    writeMem(z80.regs.SP.W--, pair->B.h);
    writeMem(z80.regs.SP.W,   pair->B.l);
    pair->W   = addr.W;
    z80.regs.SH.W = addr.W;
    delayExSpHl(z80);
}

static void M1() { 
    UInt8 value = z80.regs.R;
    z80.regs.R = (value & 0x80) | ((value + 1) & 0x7f); 
    delayM1(z80);
}


static void nop() {
}

static void ld_bc_word() {
    z80.regs.BC.B.l = readOpcode(z80.regs.PC.W++);
    z80.regs.BC.B.h = readOpcode(z80.regs.PC.W++);
}

static void ld_de_word() {
    z80.regs.DE.B.l = readOpcode(z80.regs.PC.W++);
    z80.regs.DE.B.h = readOpcode(z80.regs.PC.W++);
}

static void ld_hl_word() {
    z80.regs.HL.B.l = readOpcode(z80.regs.PC.W++);
    z80.regs.HL.B.h = readOpcode(z80.regs.PC.W++);
}

static void ld_ix_word() {
    z80.regs.IX.B.l = readOpcode(z80.regs.PC.W++);
    z80.regs.IX.B.h = readOpcode(z80.regs.PC.W++);
}

static void ld_iy_word() {
    z80.regs.IY.B.l = readOpcode(z80.regs.PC.W++);
    z80.regs.IY.B.h = readOpcode(z80.regs.PC.W++);
}

static void ld_sp_word() {
    z80.regs.SP.B.l = readOpcode(z80.regs.PC.W++);
    z80.regs.SP.B.h = readOpcode(z80.regs.PC.W++);
}

static void ld_sp_hl() { 
    delayLdSpHl(z80);                  // white cat append
    z80.regs.SP.W = z80.regs.HL.W; 
}

static void ld_sp_ix() { 
    delayLdSpHl(z80);                  // white cat append
    z80.regs.SP.W = z80.regs.IX.W; 
}

static void ld_sp_iy() { 
    delayLdSpHl(z80);                  // white cat append
    z80.regs.SP.W = z80.regs.IY.W; 
}

static void ld_xbc_a() {
    writeMem(z80.regs.BC.W, z80.regs.AF.B.h);
}

static void ld_xde_a() {
    writeMem(z80.regs.DE.W, z80.regs.AF.B.h);
}

static void ld_xhl_a() {
    writeMem(z80.regs.HL.W, z80.regs.AF.B.h);
}

static void ld_a_xbc() {
    z80.regs.AF.B.h = readMem(z80.regs.BC.W);
}

static void ld_a_xde() {
    z80.regs.AF.B.h = readMem(z80.regs.DE.W);
}

static void ld_xhl_byte() {
    writeMem(z80.regs.HL.W, readOpcode(z80.regs.PC.W++));
}

static void ld_i_a() {
    delayLd(z80);
    z80.regs.I = z80.regs.AF.B.h;
}

static void ld_r_a() {
    delayLd(z80);
    z80.regs.R = z80.regs.R2 = z80.regs.AF.B.h;
}

static void ld_a_i() {
    delayLd(z80);
    z80.regs.AF.B.h = z80.regs.I;
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        ZSXYTable[z80.regs.AF.B.h] | (z80.regs.iff2 << 2);
}

static void ld_a_r() {
    delayLd(z80);
    z80.regs.AF.B.h = (z80.regs.R & 0x7f) | (z80.regs.R2 & 0x80);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        ZSXYTable[z80.regs.AF.B.h] | (z80.regs.iff2 << 2);
}

static void inc_bc() {
    z80.regs.BC.W++; delayInc16(z80);
}

static void inc_de() {
    z80.regs.DE.W++; delayInc16(z80);
}

static void inc_hl() {
    z80.regs.HL.W++; delayInc16(z80);
}

static void inc_ix() {
    z80.regs.IX.W++; delayInc16(z80);
}

static void inc_iy() {
    z80.regs.IY.W++; delayInc16(z80);
}

static void inc_sp() {
    z80.regs.SP.W++; delayInc16(z80);
}

static void inc_a() {
    INC(&z80.regs.AF.B.h);
}

static void inc_b() {
    INC(&z80.regs.BC.B.h);
}

static void inc_c() {
    INC(&z80.regs.BC.B.l);
}

static void inc_d() {
    INC(&z80.regs.DE.B.h);
}

static void inc_e() {
    INC(&z80.regs.DE.B.l);
}

static void inc_h() {
    INC(&z80.regs.HL.B.h);
}

static void inc_l() {
    INC(&z80.regs.HL.B.l);
}

static void inc_ixh() { 
    INC(&z80.regs.IX.B.h); 
}

static void inc_ixl() { 
    INC(&z80.regs.IX.B.l); 
}

static void inc_iyh() { 
    INC(&z80.regs.IY.B.h); 
}


static void inc_iyl() { 
    INC(&z80.regs.IY.B.l); 
}

static void inc_xhl() {
    UInt8 value = readMem(z80.regs.HL.W);
    INC(&value);
    delayInc(z80);
    writeMem(z80.regs.HL.W, value);
}

static void inc_xix() {
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    UInt8 value;
    delayAdd8(z80);
    value = readMem(addr);
    INC(&value);
    delayInc(z80);
    writeMem(addr, value);
    z80.regs.SH.W = addr;
}

static void inc_xiy() {
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    UInt8 value;
    delayAdd8(z80);
    value = readMem(addr);
    INC(&value);
    delayInc(z80);
    writeMem(addr, value);
    z80.regs.SH.W = addr;
}

static void dec_bc() {
    z80.regs.BC.W--; delayInc16(z80);
}

static void dec_de() {
    z80.regs.DE.W--; delayInc16(z80);
}

static void dec_hl() {
    z80.regs.HL.W--; delayInc16(z80);
}

static void dec_ix() {
    z80.regs.IX.W--; delayInc16(z80);
}

static void dec_iy() {
    z80.regs.IY.W--; delayInc16(z80);
}

static void dec_sp() {
    z80.regs.SP.W--; delayInc16(z80);
}

static void dec_a() {
    DEC(&z80.regs.AF.B.h);
}

static void dec_b() {
    DEC(&z80.regs.BC.B.h);
}

static void dec_c() {
    DEC(&z80.regs.BC.B.l);
}

static void dec_d() {
    DEC(&z80.regs.DE.B.h);
}

static void dec_e() {
    DEC(&z80.regs.DE.B.l);
}

static void dec_h() {
    DEC(&z80.regs.HL.B.h);
}

static void dec_l() {
    DEC(&z80.regs.HL.B.l);
}

static void dec_ixh() { 
    DEC(&z80.regs.IX.B.h); 
}

static void dec_ixl() { 
    DEC(&z80.regs.IX.B.l); 
}

static void dec_iyh() { 
    DEC(&z80.regs.IY.B.h); 
}

static void dec_iyl() { 
    DEC(&z80.regs.IY.B.l); 
}

static void dec_xhl() {
    UInt8 value = readMem(z80.regs.HL.W);
    DEC(&value);
    delayInc(z80);
    writeMem(z80.regs.HL.W, value);
}

static void dec_xix() {
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    UInt8 value;
    delayAdd8(z80);
    value = readMem(addr);
    DEC(&value);
    delayInc(z80);
    writeMem(addr, value);
    z80.regs.SH.W = addr;
}

static void dec_xiy() {
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    UInt8 value;
    delayAdd8(z80);
    value = readMem(addr);
    DEC(&value);
    delayInc(z80);
    writeMem(addr, value);
    z80.regs.SH.W = addr;
}

static void ld_a_a() { 
}

static void ld_a_b() { 
    z80.regs.AF.B.h = z80.regs.BC.B.h; 
}

static void ld_a_c() { 
    z80.regs.AF.B.h = z80.regs.BC.B.l; 
}

static void ld_a_d() { 
    z80.regs.AF.B.h = z80.regs.DE.B.h; 
}

static void ld_a_e() { 
    z80.regs.AF.B.h = z80.regs.DE.B.l; 
}

static void ld_a_h() { 
    z80.regs.AF.B.h = z80.regs.HL.B.h; 
}

static void ld_a_l() { 
    z80.regs.AF.B.h = z80.regs.HL.B.l; 
}

static void ld_a_ixh() { 
    z80.regs.AF.B.h = z80.regs.IX.B.h; 
}

static void ld_a_ixl() { 
    z80.regs.AF.B.h = z80.regs.IX.B.l; 
}

static void ld_a_iyh() { 
    z80.regs.AF.B.h = z80.regs.IY.B.h; 
}

static void ld_a_iyl() { 
    z80.regs.AF.B.h = z80.regs.IY.B.l; 
}

static void ld_a_xhl() { 
    z80.regs.AF.B.h = readMem(z80.regs.HL.W); 
}

static void ld_a_xix() { 
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    z80.regs.AF.B.h = readMem(addr);
}

static void ld_a_xiy() { 
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    z80.regs.AF.B.h = readMem(addr);
}

static void ld_xiy_a() { 
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    writeMem(addr, z80.regs.AF.B.h);
}

static void ld_xix_a() { 
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    writeMem(addr, z80.regs.AF.B.h);
}

static void ld_b_a() { 
    z80.regs.BC.B.h = z80.regs.AF.B.h; 
}

static void ld_b_b() { 
#ifdef ENABLE_ASMSX_DEBUG_COMMANDS
#if 1
    char debugString[256];
    UInt16 addr = z80.regs.PC.W;
    UInt16 bpAddr = 0;
    UInt8  size;
    UInt16 page = 0xffff;
    UInt16 slot = 0xffff;

    if (readMemory(addr++) != 24) {
        return;
    }

    size = readMemory(addr++);
    switch (size) {
    case 0:
        bpAddr = addr;
        break;
    case 2:
        bpAddr = readMemory(addr++);
        bpAddr |= readMemory(addr++) << 8;
        break;
    case 3:
        slot = readMemory(addr++);
        bpAddr = readMemory(addr++);
        bpAddr |= readMemory(addr++) << 8;
        break;
    case 4:
        slot = readMemory(addr++);
        page = readMemory(addr++);
        bpAddr = readMemory(addr++);
        bpAddr |= readMemory(addr++) << 8;
        break;
    default:
        return;
    }

    sprintf(debugString, "%.4x %.4x %.4x", slot, page, bpAddr);
    z80.debugCb(z80.ref, ASDBG_SETBP, debugString);

#else
    char debugString[256];
    UInt16 addr = z80.regs.PC.W;
    UInt16 end;
    UInt16 bpAddr = 0;

    if (readMemory(addr++) != 24) {
        return;
    }
    end = addr + 1 + (Int8)readMemory(addr);
    if (end < addr + 6 || end - addr > 255) {
        return;
    }
    addr++;

    if (readMemory(addr + 0) != 100 || 
        readMemory(addr + 1) != 100 || 
        readMemory(addr + 2) != 0   || 
        readMemory(addr + 3) != 0) 
    {
        return;
    }
    addr += 4;
    
    bpAddr = readMemory(addr++);
    bpAddr |= readMemory(addr++) << 8;

    sprintf(debugString, "%.4x", bpAddr);

    z80.debugCb(z80.ref, ASDBG_SETBP, debugString);
#endif
#endif
}

static void ld_b_c() { 
    z80.regs.BC.B.h = z80.regs.BC.B.l; 
}

static void ld_b_d() { 
    z80.regs.BC.B.h = z80.regs.DE.B.h; 
}

static void ld_b_e() { 
    z80.regs.BC.B.h = z80.regs.DE.B.l; 
}

static void ld_b_h() { 
    z80.regs.BC.B.h = z80.regs.HL.B.h; 
}

static void ld_b_l() { 
    z80.regs.BC.B.h = z80.regs.HL.B.l; 
}

static void ld_b_ixh() { 
    z80.regs.BC.B.h = z80.regs.IX.B.h; 
}

static void ld_b_ixl() { 
    z80.regs.BC.B.h = z80.regs.IX.B.l; 
}

static void ld_b_iyh() { 
    z80.regs.BC.B.h = z80.regs.IY.B.h; 
}

static void ld_b_iyl() { 
    z80.regs.BC.B.h = z80.regs.IY.B.l; 
}

static void ld_b_xhl() { 
    z80.regs.BC.B.h = readMem(z80.regs.HL.W); 
}

static void ld_b_xix() { 
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    z80.regs.BC.B.h = readMem(addr);
}

static void ld_b_xiy() { 
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    z80.regs.BC.B.h = readMem(addr);
}

static void ld_xix_b() { 
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    writeMem(addr, z80.regs.BC.B.h);
}

static void ld_xiy_b() { 
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    writeMem(addr, z80.regs.BC.B.h);
}

static void ld_c_a() { 
    z80.regs.BC.B.l = z80.regs.AF.B.h; 
}

static void ld_c_b() { 
    z80.regs.BC.B.l = z80.regs.BC.B.h; 
}

static void ld_c_c() { 
}

static void ld_c_d() { 
    z80.regs.BC.B.l = z80.regs.DE.B.h; 
}

static void ld_c_e() {
    z80.regs.BC.B.l = z80.regs.DE.B.l;
}

static void ld_c_h() { 
    z80.regs.BC.B.l = z80.regs.HL.B.h; 
}

static void ld_c_l() { 
    z80.regs.BC.B.l = z80.regs.HL.B.l; 
}

static void ld_c_ixh() { 
    z80.regs.BC.B.l = z80.regs.IX.B.h; 
}

static void ld_c_ixl() { 
    z80.regs.BC.B.l = z80.regs.IX.B.l; 
}

static void ld_c_iyh() { 
    z80.regs.BC.B.l = z80.regs.IY.B.h; 
}

static void ld_c_iyl() { 
    z80.regs.BC.B.l = z80.regs.IY.B.l; 
}

static void ld_c_xhl() { 
    z80.regs.BC.B.l = readMem(z80.regs.HL.W); 
}

static void ld_c_xix() { 
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    z80.regs.BC.B.l = readMem(addr);
}

static void ld_c_xiy() { 
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    z80.regs.BC.B.l = readMem(addr);
}

static void ld_xix_c() { 
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    writeMem(addr, z80.regs.BC.B.l);
}

static void ld_xiy_c() { 
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    writeMem(addr, z80.regs.BC.B.l);
}

static void ld_d_a() { 
    z80.regs.DE.B.h = z80.regs.AF.B.h; 
}

static void ld_d_b() { 
    z80.regs.DE.B.h = z80.regs.BC.B.h; 
}

static void ld_d_c() { 
    z80.regs.DE.B.h = z80.regs.BC.B.l; 
}

static void ld_d_d() { 
#ifdef ENABLE_ASMSX_DEBUG_COMMANDS
    char debugString[256];
    UInt16 addr = z80.regs.PC.W;
    UInt16 end;
    char* ptr = debugString;

    if (readMemory(addr++) != 24) {
        return;
    }

    end = addr + 1 + (Int8)readMemory(addr);
    addr++;

    if (end - addr > 127) {
        return;
    }
    else if (end - addr > 4 &&
             readMemory(addr + 0) == 100 && 
             readMemory(addr + 1) == 100 && 
             readMemory(addr + 2) == 0   &&
             readMemory(addr + 3) == 0) 
    {
        addr += 4;
    }
    
    while (addr < end) {
        *ptr++ = (char)readMemory(addr++);
    }

    if (ptr > debugString && ptr[-1] != 'n') {
        *ptr++ = '\n';
    }

    *ptr = 0;

    z80.debugCb(z80.ref, ASDBG_TRACE, debugString);
#endif
}

static void ld_d_e() { 
    z80.regs.DE.B.h = z80.regs.DE.B.l; 
}

static void ld_d_h() { 
    z80.regs.DE.B.h = z80.regs.HL.B.h; 
}

static void ld_d_l() { 
    z80.regs.DE.B.h = z80.regs.HL.B.l; 
}

static void ld_d_ixh() { 
    z80.regs.DE.B.h = z80.regs.IX.B.h; 
}

static void ld_d_ixl() { 
    z80.regs.DE.B.h = z80.regs.IX.B.l; 
}

static void ld_d_iyh() { 
    z80.regs.DE.B.h = z80.regs.IY.B.h; 
}

static void ld_d_iyl() { 
    z80.regs.DE.B.h = z80.regs.IY.B.l; 
}

static void ld_d_xhl() { 
    z80.regs.DE.B.h = readMem(z80.regs.HL.W); 
}

static void ld_d_xix() { 
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    z80.regs.DE.B.h = readMem(addr);
}

static void ld_d_xiy() { 
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    z80.regs.DE.B.h = readMem(addr);
}

static void ld_xix_d() { 
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    writeMem(addr, z80.regs.DE.B.h);

}
static void ld_xiy_d() { 
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    writeMem(addr, z80.regs.DE.B.h);
}

static void ld_e_a() { 
    z80.regs.DE.B.l = z80.regs.AF.B.h; 
}

static void ld_e_b() { 
    z80.regs.DE.B.l = z80.regs.BC.B.h; 
}

static void ld_e_c() { 
    z80.regs.DE.B.l = z80.regs.BC.B.l; 
}

static void ld_e_d() {
    z80.regs.DE.B.l = z80.regs.DE.B.h; 
}

static void ld_e_e() { 
}

static void ld_e_h() {
    z80.regs.DE.B.l = z80.regs.HL.B.h; 
}

static void ld_e_l() { 
    z80.regs.DE.B.l = z80.regs.HL.B.l; 
}

static void ld_e_ixh() { 
    z80.regs.DE.B.l = z80.regs.IX.B.h; 
}

static void ld_e_ixl() { 
    z80.regs.DE.B.l = z80.regs.IX.B.l; 
}

static void ld_e_iyh() { 
    z80.regs.DE.B.l = z80.regs.IY.B.h; 
}

static void ld_e_iyl() { 
    z80.regs.DE.B.l = z80.regs.IY.B.l; 
}

static void ld_e_xhl() { 
    z80.regs.DE.B.l = readMem(z80.regs.HL.W); 
}

static void ld_e_xix() { 
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    z80.regs.DE.B.l = readMem(addr);
}

static void ld_e_xiy() { 
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    z80.regs.DE.B.l = readMem(addr);
}

static void ld_xix_e() { 
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    writeMem(addr, z80.regs.DE.B.l);
}

static void ld_xiy_e() { 
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    writeMem(addr, z80.regs.DE.B.l);
}

static void ld_h_a() { 
    z80.regs.HL.B.h = z80.regs.AF.B.h;
}

static void ld_h_b() { 
    z80.regs.HL.B.h = z80.regs.BC.B.h;
}

static void ld_h_c() { 
    z80.regs.HL.B.h = z80.regs.BC.B.l;
}

static void ld_h_d() {
    z80.regs.HL.B.h = z80.regs.DE.B.h;
}

static void ld_h_e() {
    z80.regs.HL.B.h = z80.regs.DE.B.l; 
}

static void ld_h_h() { 
    z80.regs.HL.B.h = z80.regs.HL.B.h; 
}

static void ld_h_l() { 
    z80.regs.HL.B.h = z80.regs.HL.B.l; 
}

static void ld_h_ixh() {
    z80.regs.HL.B.h = z80.regs.IX.B.h; 
}

static void ld_h_ixl() {
    z80.regs.HL.B.h = z80.regs.IX.B.l;
}

static void ld_h_iyh() {
    z80.regs.HL.B.h = z80.regs.IY.B.h; 
}

static void ld_h_iyl() {
    z80.regs.HL.B.h = z80.regs.IY.B.l; 
}

static void ld_h_xhl() {
    z80.regs.HL.B.h = readMem(z80.regs.HL.W); 
}

static void ld_h_xix() { 
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    z80.regs.HL.B.h = readMem(addr);
}

static void ld_h_xiy() { 
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    z80.regs.HL.B.h = readMem(addr);
}

static void ld_xix_h() { 
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    writeMem(addr, z80.regs.HL.B.h);
}

static void ld_xiy_h() { 
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    writeMem(addr, z80.regs.HL.B.h);
}

static void ld_l_a() { 
    z80.regs.HL.B.l = z80.regs.AF.B.h; 
}

static void ld_l_b() {
    z80.regs.HL.B.l = z80.regs.BC.B.h; 
}

static void ld_l_c() {
    z80.regs.HL.B.l = z80.regs.BC.B.l;
}

static void ld_l_d() {
    z80.regs.HL.B.l = z80.regs.DE.B.h;
}

static void ld_l_e() {
    z80.regs.HL.B.l = z80.regs.DE.B.l;
}

static void ld_l_h() {
    z80.regs.HL.B.l = z80.regs.HL.B.h;
}

static void ld_l_l() {
    z80.regs.HL.B.l = z80.regs.HL.B.l;
}

static void ld_l_ixh() {
    z80.regs.HL.B.l = z80.regs.IX.B.h;
}

static void ld_l_ixl() {
    z80.regs.HL.B.l = z80.regs.IX.B.l;
}

static void ld_l_iyh() {
    z80.regs.HL.B.l = z80.regs.IY.B.h;
}

static void ld_l_iyl() {
    z80.regs.HL.B.l = z80.regs.IY.B.l; 
}

static void ld_l_xhl() {
    z80.regs.HL.B.l = readMem(z80.regs.HL.W); 
}

static void ld_l_xix() { 
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    z80.regs.HL.B.l = readMem(addr);
}

static void ld_l_xiy() { 
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    z80.regs.HL.B.l = readMem(addr);
}

static void ld_xix_l() { 
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    writeMem(addr, z80.regs.HL.B.l);
}

static void ld_xiy_l()   { 
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80);
    z80.regs.SH.W = addr;
    writeMem(addr, z80.regs.HL.B.l);
}

static void ld_ixh_a() { 
    z80.regs.IX.B.h = z80.regs.AF.B.h;
}

static void ld_ixh_b() {
    z80.regs.IX.B.h = z80.regs.BC.B.h;
}

static void ld_ixh_c() {
    z80.regs.IX.B.h = z80.regs.BC.B.l;
}

static void ld_ixh_d() {
    z80.regs.IX.B.h = z80.regs.DE.B.h; 
}

static void ld_ixh_e() {
    z80.regs.IX.B.h = z80.regs.DE.B.l;
}

static void ld_ixh_ixh() {
}

static void ld_ixh_ixl() {
    z80.regs.IX.B.h = z80.regs.IX.B.l;
}

static void ld_ixl_a() { 
    z80.regs.IX.B.l = z80.regs.AF.B.h;
}

static void ld_ixl_b() {
    z80.regs.IX.B.l = z80.regs.BC.B.h;
}

static void ld_ixl_c() {
    z80.regs.IX.B.l = z80.regs.BC.B.l; 
}

static void ld_ixl_d() { 
    z80.regs.IX.B.l = z80.regs.DE.B.h;
}

static void ld_ixl_e() {
    z80.regs.IX.B.l = z80.regs.DE.B.l;
}

static void ld_ixl_ixh() {
    z80.regs.IX.B.l = z80.regs.IX.B.h;
}

static void ld_ixl_ixl() {
}

static void ld_iyh_a() {
    z80.regs.IY.B.h = z80.regs.AF.B.h;
}

static void ld_iyh_b() {
    z80.regs.IY.B.h = z80.regs.BC.B.h;
}

static void ld_iyh_c() { 
    z80.regs.IY.B.h = z80.regs.BC.B.l;
}

static void ld_iyh_d() {
    z80.regs.IY.B.h = z80.regs.DE.B.h; 
}

static void ld_iyh_e() {
    z80.regs.IY.B.h = z80.regs.DE.B.l; 
}

static void ld_iyh_iyh() {
}

static void ld_iyh_iyl() {
    z80.regs.IY.B.h = z80.regs.IY.B.l; 
}

static void ld_iyl_a() {
    z80.regs.IY.B.l = z80.regs.AF.B.h;
}

static void ld_iyl_b() { 
    z80.regs.IY.B.l = z80.regs.BC.B.h;
}

static void ld_iyl_c() { 
    z80.regs.IY.B.l = z80.regs.BC.B.l;
}

static void ld_iyl_d() { 
    z80.regs.IY.B.l = z80.regs.DE.B.h;
}

static void ld_iyl_e() { 
    z80.regs.IY.B.l = z80.regs.DE.B.l;
}

static void ld_iyl_iyh() { 
    z80.regs.IY.B.l = z80.regs.IY.B.h;
}

static void ld_iyl_iyl() {
}

static void ld_xhl_b() { 
    writeMem(z80.regs.HL.W, z80.regs.BC.B.h);
}

static void ld_xhl_c() { 
    writeMem(z80.regs.HL.W, z80.regs.BC.B.l); 
}

static void ld_xhl_d() { 
    writeMem(z80.regs.HL.W, z80.regs.DE.B.h);
}

static void ld_xhl_e() { 
    writeMem(z80.regs.HL.W, z80.regs.DE.B.l);
}

static void ld_xhl_h() { 
    writeMem(z80.regs.HL.W, z80.regs.HL.B.h);
}

static void ld_xhl_l() { 
    writeMem(z80.regs.HL.W, z80.regs.HL.B.l);
}

static void ld_a_byte() {
    z80.regs.AF.B.h = readOpcode(z80.regs.PC.W++);
}

static void ld_b_byte() {
    z80.regs.BC.B.h = readOpcode(z80.regs.PC.W++);
}

static void ld_c_byte() {
    z80.regs.BC.B.l = readOpcode(z80.regs.PC.W++);
}

static void ld_d_byte() {
    z80.regs.DE.B.h = readOpcode(z80.regs.PC.W++);
}

static void ld_e_byte() {
    z80.regs.DE.B.l = readOpcode(z80.regs.PC.W++);
}

static void ld_h_byte() {
    z80.regs.HL.B.h = readOpcode(z80.regs.PC.W++);
}

static void ld_l_byte() {
    z80.regs.HL.B.l = readOpcode(z80.regs.PC.W++);
}

static void ld_ixh_byte() {

    z80.regs.IX.B.h = readOpcode(z80.regs.PC.W++);

}

static void ld_ixl_byte() {
    z80.regs.IX.B.l = readOpcode(z80.regs.PC.W++);
}

static void ld_iyh_byte() { 
    z80.regs.IY.B.h = readOpcode(z80.regs.PC.W++);
}

static void ld_iyl_byte() { 
    z80.regs.IY.B.l = readOpcode(z80.regs.PC.W++);
}

static void ld_xbyte_a() {
    RegisterPair addr;
    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    z80.regs.SH.W = z80.regs.AF.B.h << 8;
    writeMem(addr.W, z80.regs.AF.B.h);
}

static void ld_a_xbyte() {
    RegisterPair addr;
    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    z80.regs.AF.B.h = readMem(addr.W);
    z80.regs.SH.W = addr.W + 1;
}


static void ld_xix_byte() {
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    UInt8 value = readOpcode(z80.regs.PC.W++);
    delayParallel(z80); 
    z80.regs.SH.W = addr;
    writeMem(addr, value);
}

static void ld_xiy_byte() {
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    UInt8 value = readOpcode(z80.regs.PC.W++);
    delayParallel(z80); 
    z80.regs.SH.W = addr;
    writeMem(addr, value);
}

static void ld_xword_bc() {
    RegisterPair addr;
    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    writeMem(addr.W++, z80.regs.BC.B.l);
    writeMem(addr.W,   z80.regs.BC.B.h);
    z80.regs.SH.W = addr.W;
}

static void ld_xword_de() {
    RegisterPair addr;
    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    writeMem(addr.W++, z80.regs.DE.B.l);
    writeMem(addr.W,   z80.regs.DE.B.h);
    z80.regs.SH.W = addr.W;
}

static void ld_xword_hl() {
    RegisterPair addr;
    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    writeMem(addr.W++, z80.regs.HL.B.l);
    writeMem(addr.W,   z80.regs.HL.B.h);
    z80.regs.SH.W = addr.W;
}

static void ld_xword_ix() {
    RegisterPair addr;
    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    writeMem(addr.W++, z80.regs.IX.B.l);
    writeMem(addr.W,   z80.regs.IX.B.h);
    z80.regs.SH.W = addr.W;
}

static void ld_xword_iy() {
    RegisterPair addr;
    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    writeMem(addr.W++, z80.regs.IY.B.l);
    writeMem(addr.W,   z80.regs.IY.B.h);
    z80.regs.SH.W = addr.W;
}

static void ld_xword_sp() {
    RegisterPair addr;
    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    writeMem(addr.W++, z80.regs.SP.B.l);
    writeMem(addr.W,   z80.regs.SP.B.h);
    z80.regs.SH.W = addr.W;
}

static void ld_bc_xword() {
    RegisterPair addr;
    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    z80.regs.BC.B.l = readMem(addr.W++);
    z80.regs.BC.B.h = readMem(addr.W);
    z80.regs.SH.W = addr.W;
}

static void ld_de_xword() {
    RegisterPair addr;
    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    z80.regs.DE.B.l = readMem(addr.W++);
    z80.regs.DE.B.h = readMem(addr.W);
    z80.regs.SH.W = addr.W;
}

static void ld_hl_xword() {
    RegisterPair addr;
    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    z80.regs.HL.B.l = readMem(addr.W++);
    z80.regs.HL.B.h = readMem(addr.W);
    z80.regs.SH.W = addr.W;
}

static void ld_ix_xword() {
    RegisterPair addr;
    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    z80.regs.IX.B.l = readMem(addr.W++);
    z80.regs.IX.B.h = readMem(addr.W);
    z80.regs.SH.W = addr.W;
}

static void ld_iy_xword() {
    RegisterPair addr;
    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    z80.regs.IY.B.l = readMem(addr.W++);
    z80.regs.IY.B.h = readMem(addr.W);
    z80.regs.SH.W = addr.W;
}

static void ld_sp_xword() {
    RegisterPair addr;
    addr.B.l = readOpcode(z80.regs.PC.W++);
    addr.B.h = readOpcode(z80.regs.PC.W++);
    z80.regs.SP.B.l = readMem(addr.W++);
    z80.regs.SP.B.h = readMem(addr.W);
    z80.regs.SH.W = addr.W;
}

static void add_a_a() {
    ADD(z80.regs.AF.B.h); 
}

static void add_a_b() {
    ADD(z80.regs.BC.B.h);
}

static void add_a_c() {
    ADD(z80.regs.BC.B.l);
}

static void add_a_d() {
    ADD(z80.regs.DE.B.h);
}

static void add_a_e() {
    ADD(z80.regs.DE.B.l);
}

static void add_a_h() {
    ADD(z80.regs.HL.B.h); 
}

static void add_a_l() { 
    ADD(z80.regs.HL.B.l);
}

static void add_a_ixl() {
    ADD(z80.regs.IX.B.l); 
}

static void add_a_ixh() {
    ADD(z80.regs.IX.B.h);
}

static void add_a_iyl() {
    ADD(z80.regs.IY.B.l);
}

static void add_a_iyh() {
    ADD(z80.regs.IY.B.h);
}

static void add_a_byte(){
    ADD(readOpcode(z80.regs.PC.W++));
}

static void add_a_xhl() { 
    ADD(readMem(z80.regs.HL.W)); 
}

static void add_a_xix() {
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80); 
    ADD(readMem(addr));
    z80.regs.SH.W = addr;
}

static void add_a_xiy() {
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80); 
    ADD(readMem(addr));
    z80.regs.SH.W = addr;
}

static void adc_a_a() {
    ADC(z80.regs.AF.B.h);
}

static void adc_a_b() {
    ADC(z80.regs.BC.B.h); 
}

static void adc_a_c() {
    ADC(z80.regs.BC.B.l); 
}

static void adc_a_d() {
    ADC(z80.regs.DE.B.h); 
}

static void adc_a_e() {
    ADC(z80.regs.DE.B.l);
}

static void adc_a_h() {
    ADC(z80.regs.HL.B.h);
}

static void adc_a_l() {
    ADC(z80.regs.HL.B.l);
}

static void adc_a_ixl() {
    ADC(z80.regs.IX.B.l);
}

static void adc_a_ixh() {
    ADC(z80.regs.IX.B.h);
}

static void adc_a_iyl() {
    ADC(z80.regs.IY.B.l);
}

static void adc_a_iyh() { 
    ADC(z80.regs.IY.B.h);
}

static void adc_a_byte() {
    ADC(readOpcode(z80.regs.PC.W++)); 
}

static void adc_a_xhl() {
    ADC(readMem(z80.regs.HL.W));
}

static void adc_a_xix() {
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80); 
    z80.regs.SH.W = addr;
    ADC(readMem(addr));
}

static void adc_a_xiy() {
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80); 
    z80.regs.SH.W = addr;
    ADC(readMem(addr));
}

static void adc_hl_bc() {
    ADCW(z80.regs.BC.W);
}

static void adc_hl_de() { 
    ADCW(z80.regs.DE.W);
}

static void adc_hl_hl() {
    ADCW(z80.regs.HL.W);
}

static void adc_hl_sp() {
    ADCW(z80.regs.SP.W);
}

static void sub_a() {
    SUB(z80.regs.AF.B.h);
}

static void sub_b() {
    SUB(z80.regs.BC.B.h); 
}

static void sub_c() { 
    SUB(z80.regs.BC.B.l); 
}

static void sub_d() {
    SUB(z80.regs.DE.B.h); 
}

static void sub_e() {
    SUB(z80.regs.DE.B.l); 
}

static void sub_h() {
    SUB(z80.regs.HL.B.h);
}

static void sub_l() {
    SUB(z80.regs.HL.B.l);
}

static void sub_ixl() {
    SUB(z80.regs.IX.B.l); 
}

static void sub_ixh() {
    SUB(z80.regs.IX.B.h);
}

static void sub_iyl() {
    SUB(z80.regs.IY.B.l);
}

static void sub_iyh() {
    SUB(z80.regs.IY.B.h);
}

static void sub_byte(){
    SUB(readOpcode(z80.regs.PC.W++)); 
}

static void sub_xhl() { 
    SUB(readMem(z80.regs.HL.W)); 
}

static void sub_xix() {
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80); 
    z80.regs.SH.W = addr;
    SUB(readMem(addr));
}

static void sub_xiy() {
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80); 
    z80.regs.SH.W = addr;
    SUB(readMem(addr));
}

static void neg() {
    UInt8 regVal = z80.regs.AF.B.h;
    z80.regs.AF.B.h = 0;
    SUB(regVal);
}

static void sbc_a_a() {
    SBC(z80.regs.AF.B.h); 
}

static void sbc_a_b() {
    SBC(z80.regs.BC.B.h); 
}

static void sbc_a_c() {
    SBC(z80.regs.BC.B.l); 
}

static void sbc_a_d() {
    SBC(z80.regs.DE.B.h);
}

static void sbc_a_e() {
    SBC(z80.regs.DE.B.l);
}

static void sbc_a_h() {
    SBC(z80.regs.HL.B.h);
}

static void sbc_a_l() {
    SBC(z80.regs.HL.B.l);
}

static void sbc_a_ixl() {
    SBC(z80.regs.IX.B.l);
}

static void sbc_a_ixh() {
    SBC(z80.regs.IX.B.h);
}

static void sbc_a_iyl() {
    SBC(z80.regs.IY.B.l);
}

static void sbc_a_iyh() { 
    SBC(z80.regs.IY.B.h);
}

static void sbc_a_byte(){ 
    SBC(readOpcode(z80.regs.PC.W++));
}

static void sbc_a_xhl() { 
    SBC(readMem(z80.regs.HL.W)); 
}

static void sbc_a_xix() {
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80); 
    SBC(readMem(addr));
    z80.regs.SH.W = addr;
}

static void sbc_a_xiy() {
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80); 
    SBC(readMem(addr));
    z80.regs.SH.W = addr;
}

static void sbc_hl_bc() { SBCW(z80.regs.BC.W);
}

static void sbc_hl_de() { SBCW(z80.regs.DE.W); 
}

static void sbc_hl_hl() { SBCW(z80.regs.HL.W);
}

static void sbc_hl_sp() { SBCW(z80.regs.SP.W);
}

static void cp_a() {
    CP(z80.regs.AF.B.h);
}

static void cp_b() {
    CP(z80.regs.BC.B.h);
}

static void cp_c() {
    CP(z80.regs.BC.B.l);
}

static void cp_d() {
    CP(z80.regs.DE.B.h);
}

static void cp_e() {
    CP(z80.regs.DE.B.l);
}

static void cp_h() {
    CP(z80.regs.HL.B.h);
}

static void cp_l() {
    CP(z80.regs.HL.B.l);
}

static void cp_ixl() {
    CP(z80.regs.IX.B.l);
}

static void cp_ixh() {
    CP(z80.regs.IX.B.h);
}

static void cp_iyl() { 
    CP(z80.regs.IY.B.l);
}

static void cp_iyh() {
    CP(z80.regs.IY.B.h);
}

static void cp_byte(){
    CP(readOpcode(z80.regs.PC.W++)); 
}

static void cp_xhl() { 
    CP(readMem(z80.regs.HL.W)); 
}

static void cp_xix() {
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80); 
    CP(readMem(addr));
    z80.regs.SH.W = addr;
}

static void cp_xiy() {
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80); 
    CP(readMem(addr));
    z80.regs.SH.W = addr;
}

static void and_a() {
    AND(z80.regs.AF.B.h); 
}

static void and_b() {
    AND(z80.regs.BC.B.h); 
}

static void and_c() {
    AND(z80.regs.BC.B.l);
}

static void and_d() {
    AND(z80.regs.DE.B.h);
}

static void and_e() {
    AND(z80.regs.DE.B.l); 
}

static void and_h() {
    AND(z80.regs.HL.B.h);
}

static void and_l() { 
    AND(z80.regs.HL.B.l); 
}

static void and_ixl() {
    AND(z80.regs.IX.B.l);
}

static void and_ixh() {
    AND(z80.regs.IX.B.h); 
}

static void and_iyl() {
    AND(z80.regs.IY.B.l); 
}

static void and_iyh() {
    AND(z80.regs.IY.B.h); 
}

static void and_byte(){
    AND(readOpcode(z80.regs.PC.W++)); 
}

static void and_xhl() { 
    AND(readMem(z80.regs.HL.W));
}

static void and_xix() {
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80); 
    AND(readMem(addr));
    z80.regs.SH.W = addr;
}

static void and_xiy() {
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80); 
    AND(readMem(addr));
    z80.regs.SH.W = addr;
}

static void or_a() {
    OR(z80.regs.AF.B.h);
}

static void or_b() {
    OR(z80.regs.BC.B.h);
}

static void or_c() {
    OR(z80.regs.BC.B.l);
}

static void or_d() {
    OR(z80.regs.DE.B.h);
}

static void or_e() {
    OR(z80.regs.DE.B.l);
}

static void or_h() {
    OR(z80.regs.HL.B.h); 
}

static void or_l() {
    OR(z80.regs.HL.B.l); 
}

static void or_ixl() {
    OR(z80.regs.IX.B.l); 
}

static void or_ixh() {
    OR(z80.regs.IX.B.h);
}

static void or_iyl() {
    OR(z80.regs.IY.B.l); 
}

static void or_iyh() {
    OR(z80.regs.IY.B.h); 
}

static void or_byte(){
    OR(readOpcode(z80.regs.PC.W++)); 
}

static void or_xhl() { 
    OR(readMem(z80.regs.HL.W));
}

static void or_xix() {
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80); 
    OR(readMem(addr));
    z80.regs.SH.W = addr;
}

static void or_xiy() {
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80); 
    OR(readMem(addr));
    z80.regs.SH.W = addr;
}

static void xor_a() { 
    XOR(z80.regs.AF.B.h); 
}

static void xor_b() {
    XOR(z80.regs.BC.B.h); 
}

static void xor_c() { 
    XOR(z80.regs.BC.B.l); 
}

static void xor_d() { 
    XOR(z80.regs.DE.B.h);
}

static void xor_e() {
    XOR(z80.regs.DE.B.l);
}

static void xor_h() {
    XOR(z80.regs.HL.B.h);
}

static void xor_l() {
    XOR(z80.regs.HL.B.l);
}

static void xor_ixl() {
    XOR(z80.regs.IX.B.l); 
}

static void xor_ixh() { 
    XOR(z80.regs.IX.B.h); 
}

static void xor_iyl() {
    XOR(z80.regs.IY.B.l); 
}

static void xor_iyh() { 
    XOR(z80.regs.IY.B.h);
}

static void xor_byte(){
    XOR(readOpcode(z80.regs.PC.W++));
}

static void xor_xhl() {
    XOR(readMem(z80.regs.HL.W));
}

static void xor_xix() {
    UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80); 
    XOR(readMem(addr));
    z80.regs.SH.W = addr;
}

static void xor_xiy() {
    UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    delayAdd8(z80); 
    XOR(readMem(addr));
    z80.regs.SH.W = addr;
}

static void add_hl_bc() {
    ADDW(&z80.regs.HL.W, z80.regs.BC.W);
}

static void add_hl_de() {
    ADDW(&z80.regs.HL.W, z80.regs.DE.W);
}

static void add_hl_hl() {
    ADDW(&z80.regs.HL.W, z80.regs.HL.W);
}

static void add_hl_sp() {
    ADDW(&z80.regs.HL.W, z80.regs.SP.W);
}

static void add_ix_bc() {
    ADDW(&z80.regs.IX.W, z80.regs.BC.W);
}

static void add_ix_de() {
    ADDW(&z80.regs.IX.W, z80.regs.DE.W);
}

static void add_ix_ix() {
    ADDW(&z80.regs.IX.W, z80.regs.IX.W);
}

static void add_ix_sp() {
    ADDW(&z80.regs.IX.W, z80.regs.SP.W);
}

static void add_iy_bc() {
    ADDW(&z80.regs.IY.W, z80.regs.BC.W);
}

static void add_iy_de() {
    ADDW(&z80.regs.IY.W, z80.regs.DE.W);
}

static void add_iy_iy() {
    ADDW(&z80.regs.IY.W, z80.regs.IY.W);
}

static void add_iy_sp() {
    ADDW(&z80.regs.IY.W, z80.regs.SP.W);
}

static void mulu_xhl() { 
}

static void mulu_a() { 
}

static void mulu_b() { 
}

static void mulu_c() {
}

static void mulu_d() {
}

static void mulu_e() {
}

static void mulu_h() { 
}

static void mulu_l() { 
}

static void muluw_bc() { 
}

static void muluw_de() {
}

static void muluw_hl() {
}

static void muluw_sp() {
}

static void sla_a() { 
    SLA(&z80.regs.AF.B.h); 
}

static void sla_b() { 
    SLA(&z80.regs.BC.B.h); 
}

static void sla_c() {
    SLA(&z80.regs.BC.B.l); 
}

static void sla_d() {
    SLA(&z80.regs.DE.B.h);
}

static void sla_e() { 
    SLA(&z80.regs.DE.B.l); 
}

static void sla_h() {
    SLA(&z80.regs.HL.B.h);
}

static void sla_l() {
    SLA(&z80.regs.HL.B.l); 
}

static void sla_xhl() { 
    UInt8 val = readMem(z80.regs.HL.W);
    SLA(&val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 SLA_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    SLA(&val);
    delayBit(z80);                 // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void sla_xnn  (UInt16 addr) {
    SLA_XNN(addr);
}

static void sla_xnn_a(UInt16 addr) { 
    z80.regs.AF.B.h = SLA_XNN(addr);
}

static void sla_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = SLA_XNN(addr);
}

static void sla_xnn_c(UInt16 addr) { 
    z80.regs.BC.B.l = SLA_XNN(addr);
}

static void sla_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = SLA_XNN(addr);
}

static void sla_xnn_e(UInt16 addr) {
    z80.regs.DE.B.l = SLA_XNN(addr);
}

static void sla_xnn_h(UInt16 addr) {
    z80.regs.HL.B.h = SLA_XNN(addr);
}

static void sla_xnn_l(UInt16 addr) {
    z80.regs.HL.B.l = SLA_XNN(addr);
}

static void sll_a() {
    SLL(&z80.regs.AF.B.h); 
}

static void sll_b() {
    SLL(&z80.regs.BC.B.h); 
}

static void sll_c() {
    SLL(&z80.regs.BC.B.l);
}

static void sll_d() {
    SLL(&z80.regs.DE.B.h);
}

static void sll_e() {
    SLL(&z80.regs.DE.B.l);
}

static void sll_h() {
    SLL(&z80.regs.HL.B.h);
}

static void sll_l() {
    SLL(&z80.regs.HL.B.l); 
}

static void sll_xhl() { 
    UInt8 val = readMem(z80.regs.HL.W);
    SLL(&val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 SLL_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    SLL(&val);
    delayBit(z80);                 // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void sll_xnn  (UInt16 addr) { 
    SLL_XNN(addr);
}

static void sll_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = SLL_XNN(addr);
}

static void sll_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = SLL_XNN(addr);
}

static void sll_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = SLL_XNN(addr);
}

static void sll_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = SLL_XNN(addr);
}

static void sll_xnn_e(UInt16 addr) {
    z80.regs.DE.B.l = SLL_XNN(addr);
}

static void sll_xnn_h(UInt16 addr) {
    z80.regs.HL.B.h = SLL_XNN(addr);
}

static void sll_xnn_l(UInt16 addr) { 
    z80.regs.HL.B.l = SLL_XNN(addr); 
}

static void sra_a() {    
    SRA(&z80.regs.AF.B.h);
}

static void sra_b() { 
    SRA(&z80.regs.BC.B.h);
}

static void sra_c() { 
    SRA(&z80.regs.BC.B.l);
}

static void sra_d() { 
    SRA(&z80.regs.DE.B.h);
}

static void sra_e() { 
    SRA(&z80.regs.DE.B.l); 
}

static void sra_h() {
    SRA(&z80.regs.HL.B.h);
}

static void sra_l() {
    SRA(&z80.regs.HL.B.l); 
}

static void sra_xhl() { 
    UInt8 val = readMem(z80.regs.HL.W);
    SRA(&val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 SRA_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    SRA(&val);
    delayBit(z80);                 // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void sra_xnn  (UInt16 addr) {
    SRA_XNN(addr); 
}

static void sra_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = SRA_XNN(addr); 
}

static void sra_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = SRA_XNN(addr); 
}

static void sra_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = SRA_XNN(addr); 
}

static void sra_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = SRA_XNN(addr); 
}

static void sra_xnn_e(UInt16 addr) { 
    z80.regs.DE.B.l = SRA_XNN(addr); 
}

static void sra_xnn_h(UInt16 addr) {
    z80.regs.HL.B.h = SRA_XNN(addr); 
}

static void sra_xnn_l(UInt16 addr) {
    z80.regs.HL.B.l = SRA_XNN(addr);
}

static void srl_a() { 
    SRL(&z80.regs.AF.B.h); 
}

static void srl_b() {
    SRL(&z80.regs.BC.B.h); 
}

static void srl_c() { 
    SRL(&z80.regs.BC.B.l); 
}

static void srl_d() {
    SRL(&z80.regs.DE.B.h);
}

static void srl_e() {
    SRL(&z80.regs.DE.B.l); 
}

static void srl_h() {
    SRL(&z80.regs.HL.B.h); 
}

static void srl_l() {
    SRL(&z80.regs.HL.B.l); 
}

static void srl_xhl() { 
    UInt8 val = readMem(z80.regs.HL.W);
    SRL(&val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 SRL_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    SRL(&val);
    delayBit(z80);                 // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void srl_xnn  (UInt16 addr) {
    SRL_XNN(addr);
}

static void srl_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = SRL_XNN(addr);
}

static void srl_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = SRL_XNN(addr); 
}

static void srl_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = SRL_XNN(addr); 
}

static void srl_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = SRL_XNN(addr);
}

static void srl_xnn_e(UInt16 addr) { 
    z80.regs.DE.B.l = SRL_XNN(addr); 
}

static void srl_xnn_h(UInt16 addr) {
    z80.regs.HL.B.h = SRL_XNN(addr);
}

static void srl_xnn_l(UInt16 addr) {
    z80.regs.HL.B.l = SRL_XNN(addr);
}

static void rl_a() {
    RL(&z80.regs.AF.B.h);
}

static void rl_b() {
    RL(&z80.regs.BC.B.h);
}

static void rl_c() { 
    RL(&z80.regs.BC.B.l); 
}

static void rl_d() {
    RL(&z80.regs.DE.B.h);
}

static void rl_e() { 
    RL(&z80.regs.DE.B.l);
}

static void rl_h() {
    RL(&z80.regs.HL.B.h);
}

static void rl_l() { 
    RL(&z80.regs.HL.B.l);
}

static void rl_xhl() { 
    UInt8 val = readMem(z80.regs.HL.W);
    RL(&val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 RL_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    RL(&val);
    delayBit(z80);                 // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void rl_xnn  (UInt16 addr) {
    RL_XNN(addr);
}

static void rl_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = RL_XNN(addr);
}

static void rl_xnn_b(UInt16 addr) { 
    z80.regs.BC.B.h = RL_XNN(addr); 
}

static void rl_xnn_c(UInt16 addr) { 
    z80.regs.BC.B.l = RL_XNN(addr); 
}

static void rl_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = RL_XNN(addr);
}

static void rl_xnn_e(UInt16 addr) { 
    z80.regs.DE.B.l = RL_XNN(addr);
}

static void rl_xnn_h(UInt16 addr) {
    z80.regs.HL.B.h = RL_XNN(addr);
}

static void rl_xnn_l(UInt16 addr) {
    z80.regs.HL.B.l = RL_XNN(addr);
}

static void rlc_a() {
    RLC(&z80.regs.AF.B.h);
}

static void rlc_b() {
    RLC(&z80.regs.BC.B.h);
}

static void rlc_c() { 
    RLC(&z80.regs.BC.B.l);
}

static void rlc_d() {
    RLC(&z80.regs.DE.B.h);
}

static void rlc_e() { 
    RLC(&z80.regs.DE.B.l);
}

static void rlc_h() {
    RLC(&z80.regs.HL.B.h);
}

static void rlc_l() { 
    RLC(&z80.regs.HL.B.l);
}

static void rlc_xhl() { 
    UInt8 val = readMem(z80.regs.HL.W);
    RLC(&val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 RLC_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    RLC(&val);
    delayBit(z80);                 // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void rlc_xnn  (UInt16 addr) { 
    RLC_XNN(addr);
}

static void rlc_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = RLC_XNN(addr);
}

static void rlc_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = RLC_XNN(addr);
}

static void rlc_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = RLC_XNN(addr); 
}

static void rlc_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = RLC_XNN(addr); 
}

static void rlc_xnn_e(UInt16 addr) {
    z80.regs.DE.B.l = RLC_XNN(addr); 
}

static void rlc_xnn_h(UInt16 addr) {
    z80.regs.HL.B.h = RLC_XNN(addr);
}

static void rlc_xnn_l(UInt16 addr) {
    z80.regs.HL.B.l = RLC_XNN(addr); 
}

static void rr_a() {
    RR(&z80.regs.AF.B.h);
}

static void rr_b() {
    RR(&z80.regs.BC.B.h); 
}

static void rr_c() {
    RR(&z80.regs.BC.B.l);
}

static void rr_d() {
    RR(&z80.regs.DE.B.h);
}

static void rr_e() {
    RR(&z80.regs.DE.B.l);
}

static void rr_h() {
    RR(&z80.regs.HL.B.h);
}

static void rr_l() { 
    RR(&z80.regs.HL.B.l);
}

static void rr_xhl() { 
    UInt8 val = readMem(z80.regs.HL.W);
    RR(&val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 RR_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    RR(&val);
    delayBit(z80);                 // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void rr_xnn  (UInt16 addr) {
    RR_XNN(addr);
}

static void rr_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = RR_XNN(addr);
}

static void rr_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = RR_XNN(addr);
}

static void rr_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = RR_XNN(addr);
}

static void rr_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = RR_XNN(addr);
}

static void rr_xnn_e(UInt16 addr) {
    z80.regs.DE.B.l = RR_XNN(addr); 
}

static void rr_xnn_h(UInt16 addr) {
    z80.regs.HL.B.h = RR_XNN(addr);
}

static void rr_xnn_l(UInt16 addr) {
    z80.regs.HL.B.l = RR_XNN(addr);
}

static void rrc_a() {
    RRC(&z80.regs.AF.B.h);
}

static void rrc_b() {
    RRC(&z80.regs.BC.B.h);
}

static void rrc_c() {
    RRC(&z80.regs.BC.B.l);
}

static void rrc_d() {
    RRC(&z80.regs.DE.B.h);
}

static void rrc_e() {
    RRC(&z80.regs.DE.B.l);
}

static void rrc_h() { 
    RRC(&z80.regs.HL.B.h);
}

static void rrc_l() { 
    RRC(&z80.regs.HL.B.l); 
}

static void rrc_xhl() { 
    UInt8 val = readMem(z80.regs.HL.W);
    RRC(&val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 RRC_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    RRC(&val);
    delayBit(z80);                 // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void rrc_xnn  (UInt16 addr) {
    RRC_XNN(addr);
}

static void rrc_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = RRC_XNN(addr); 
}

static void rrc_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = RRC_XNN(addr);
}

static void rrc_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = RRC_XNN(addr);
}

static void rrc_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = RRC_XNN(addr);
}

static void rrc_xnn_e(UInt16 addr) {
    z80.regs.DE.B.l = RRC_XNN(addr);
}

static void rrc_xnn_h(UInt16 addr) {
    z80.regs.HL.B.h = RRC_XNN(addr);
}

static void rrc_xnn_l(UInt16 addr) { 
    z80.regs.HL.B.l = RRC_XNN(addr);
}

static void bit_0_a() { 
    BIT(0, z80.regs.AF.B.h);
}

static void bit_0_b() {
    BIT(0, z80.regs.BC.B.h);
}

static void bit_0_c() {
    BIT(0, z80.regs.BC.B.l);
}

static void bit_0_d() {
    BIT(0, z80.regs.DE.B.h); 
}

static void bit_0_e() {
    BIT(0, z80.regs.DE.B.l);
}

static void bit_0_h() { 
    BIT(0, z80.regs.HL.B.h);
}

static void bit_0_l() {
    BIT(0, z80.regs.HL.B.l); 
}

static void bit_0_xhl() {
    delayBit(z80);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        (z80.regs.SH.B.h & (X_FLAG | Y_FLAG)) | 
        ZSPHTable[readMem(z80.regs.HL.W) & (1 << 0)];
}

static void bit_0_xnn(UInt16 addr) { 
    delayBitIx(z80);           // white cat append
    z80.regs.SH.W   = addr;
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        (z80.regs.SH.B.h & (X_FLAG | Y_FLAG)) |
        ZSPHTable[readMem(addr) & (1 << 0)];
}

static void bit_1_a() {
    BIT(1, z80.regs.AF.B.h);
}

static void bit_1_b() {
    BIT(1, z80.regs.BC.B.h);
}

static void bit_1_c() {
    BIT(1, z80.regs.BC.B.l);
}

static void bit_1_d() {
    BIT(1, z80.regs.DE.B.h);
}

static void bit_1_e() {
    BIT(1, z80.regs.DE.B.l);
}

static void bit_1_h() {
    BIT(1, z80.regs.HL.B.h);
}

static void bit_1_l() {
    BIT(1, z80.regs.HL.B.l);
}

static void bit_1_xhl() {
    delayBit(z80);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        (z80.regs.SH.B.h & (X_FLAG | Y_FLAG)) | 
        ZSPHTable[readMem(z80.regs.HL.W) & (1 << 1)];
}

static void bit_1_xnn(UInt16 addr) { 
    delayBitIx(z80);           // white cat append
    z80.regs.SH.W   = addr;
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        (z80.regs.SH.B.h & (X_FLAG | Y_FLAG)) |
        ZSPHTable[readMem(addr) & (1 << 1)];
}

static void bit_2_a() {
    BIT(2, z80.regs.AF.B.h); 
}

static void bit_2_b() {
    BIT(2, z80.regs.BC.B.h);
}

static void bit_2_c() {
    BIT(2, z80.regs.BC.B.l);
}

static void bit_2_d() {
    BIT(2, z80.regs.DE.B.h);
}

static void bit_2_e() {
    BIT(2, z80.regs.DE.B.l);
}

static void bit_2_h() {
    BIT(2, z80.regs.HL.B.h);
}

static void bit_2_l() { 
    BIT(2, z80.regs.HL.B.l);
}

static void bit_2_xhl() {
    delayBit(z80);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        (z80.regs.SH.B.h & (X_FLAG | Y_FLAG)) | 
        ZSPHTable[readMem(z80.regs.HL.W) & (1 << 2)];
}

static void bit_2_xnn(UInt16 addr) { 
    delayBitIx(z80);           // white cat append
    z80.regs.SH.W   = addr;
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        (z80.regs.SH.B.h & (X_FLAG | Y_FLAG)) |
        ZSPHTable[readMem(addr) & (1 << 2)];
}

static void bit_3_a() {
    BIT(3, z80.regs.AF.B.h);
}

static void bit_3_b() {
    BIT(3, z80.regs.BC.B.h);
}

static void bit_3_c() { 
    BIT(3, z80.regs.BC.B.l);
}

static void bit_3_d() {
    BIT(3, z80.regs.DE.B.h); 
}

static void bit_3_e() {
    BIT(3, z80.regs.DE.B.l);
}

static void bit_3_h() { 
    BIT(3, z80.regs.HL.B.h);
}

static void bit_3_l() { 
    BIT(3, z80.regs.HL.B.l);
}

static void bit_3_xhl() {
    delayBit(z80);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        (z80.regs.SH.B.h & (X_FLAG | Y_FLAG)) | 
        ZSPHTable[readMem(z80.regs.HL.W) & (1 << 3)];
}

static void bit_3_xnn(UInt16 addr) { 
    delayBitIx(z80);           // white cat append
    z80.regs.SH.W   = addr;
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        (z80.regs.SH.B.h & (X_FLAG | Y_FLAG)) |
        ZSPHTable[readMem(addr) & (1 << 3)];
}

static void bit_4_a() {
    BIT(4, z80.regs.AF.B.h);
}

static void bit_4_b() { 
    BIT(4, z80.regs.BC.B.h);
}

static void bit_4_c() { 
    BIT(4, z80.regs.BC.B.l);
}

static void bit_4_d() {
    BIT(4, z80.regs.DE.B.h);
}

static void bit_4_e() {
    BIT(4, z80.regs.DE.B.l);
}

static void bit_4_h() {
    BIT(4, z80.regs.HL.B.h);
}

static void bit_4_l() { 
    BIT(4, z80.regs.HL.B.l);
}

static void bit_4_xhl() {
    delayBit(z80);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        (z80.regs.SH.B.h & (X_FLAG | Y_FLAG)) | 
        ZSPHTable[readMem(z80.regs.HL.W) & (1 << 4)];
}

static void bit_4_xnn(UInt16 addr) { 
    delayBitIx(z80);           // white cat append
    z80.regs.SH.W   = addr;
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        (z80.regs.SH.B.h & (X_FLAG | Y_FLAG)) |
        ZSPHTable[readMem(addr) & (1 << 4)];
}

static void bit_5_a() {
    BIT(5, z80.regs.AF.B.h); 
}

static void bit_5_b() {
    BIT(5, z80.regs.BC.B.h); 
}

static void bit_5_c() { 
    BIT(5, z80.regs.BC.B.l); 
}

static void bit_5_d() {
    BIT(5, z80.regs.DE.B.h); 
}

static void bit_5_e() {
    BIT(5, z80.regs.DE.B.l); 
}

static void bit_5_h() {
    BIT(5, z80.regs.HL.B.h);
}

static void bit_5_l() { 
    BIT(5, z80.regs.HL.B.l); 
}

static void bit_5_xhl() {
    delayBit(z80);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        (z80.regs.SH.B.h & (X_FLAG | Y_FLAG)) | 
        ZSPHTable[readMem(z80.regs.HL.W) & (1 << 5)];
}

static void bit_5_xnn(UInt16 addr) { 
    delayBitIx(z80);           // white cat append
    z80.regs.SH.W   = addr;
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        (z80.regs.SH.B.h & (X_FLAG | Y_FLAG)) |
        ZSPHTable[readMem(addr) & (1 << 5)];
}

static void bit_6_a() { 
    BIT(6, z80.regs.AF.B.h);
}

static void bit_6_b() {
    BIT(6, z80.regs.BC.B.h);
}

static void bit_6_c() {
    BIT(6, z80.regs.BC.B.l); 
}

static void bit_6_d() { 
    BIT(6, z80.regs.DE.B.h);
}

static void bit_6_e() {
    BIT(6, z80.regs.DE.B.l);
}

static void bit_6_h() {
    BIT(6, z80.regs.HL.B.h);
}

static void bit_6_l() {
    BIT(6, z80.regs.HL.B.l);
}

static void bit_6_xhl() {
    delayBit(z80);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        (z80.regs.SH.B.h & (X_FLAG | Y_FLAG)) | 
        ZSPHTable[readMem(z80.regs.HL.W) & (1 << 6)];
}

static void bit_6_xnn(UInt16 addr) { 
    delayBitIx(z80);           // white cat append
    z80.regs.SH.W   = addr;
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        (z80.regs.SH.B.h & (X_FLAG | Y_FLAG)) |
        ZSPHTable[readMem(addr) & (1 << 6)];
}

static void bit_7_a() { 
    BIT(7, z80.regs.AF.B.h); 
}

static void bit_7_b() { 
    BIT(7, z80.regs.BC.B.h);
}

static void bit_7_c() {
    BIT(7, z80.regs.BC.B.l);
}

static void bit_7_d() {
    BIT(7, z80.regs.DE.B.h);
}

static void bit_7_e() {
    BIT(7, z80.regs.DE.B.l); 
}

static void bit_7_h() {
    BIT(7, z80.regs.HL.B.h);
}

static void bit_7_l() {
    BIT(7, z80.regs.HL.B.l); 
}

static void bit_7_xhl() {
    delayBit(z80);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        (z80.regs.SH.B.h & (X_FLAG | Y_FLAG)) | 
        ZSPHTable[readMem(z80.regs.HL.W) & (1 << 7)];
}

static void bit_7_xnn(UInt16 addr) { 
    delayBitIx(z80);           // white cat append
    z80.regs.SH.W   = addr;
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        (z80.regs.SH.B.h & (X_FLAG | Y_FLAG)) |
        ZSPHTable[readMem(addr) & (1 << 7)];
}

static void res_0_a() {
    RES(0, &z80.regs.AF.B.h);
}

static void res_0_b() {
    RES(0, &z80.regs.BC.B.h);
}

static void res_0_c() {
    RES(0, &z80.regs.BC.B.l);
}

static void res_0_d() {
    RES(0, &z80.regs.DE.B.h);
}

static void res_0_e() {
    RES(0, &z80.regs.DE.B.l);
}

static void res_0_h() {
    RES(0, &z80.regs.HL.B.h);
}

static void res_0_l() {
    RES(0, &z80.regs.HL.B.l);
}

static void res_0_xhl() {
    UInt8 val = readMem(z80.regs.HL.W);
    RES(0, &val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 RES_0_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    RES(0, &val);
    delayBit(z80);             // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void res_0_xnn  (UInt16 addr) {
    RES_0_XNN(addr);
}

static void res_0_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = RES_0_XNN(addr);
}

static void res_0_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = RES_0_XNN(addr);
}

static void res_0_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = RES_0_XNN(addr);
}

static void res_0_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = RES_0_XNN(addr);
}

static void res_0_xnn_e(UInt16 addr) {
    z80.regs.DE.B.l = RES_0_XNN(addr);
}

static void res_0_xnn_h(UInt16 addr) {
    z80.regs.HL.B.h = RES_0_XNN(addr);
}

static void res_0_xnn_l(UInt16 addr) { 
    z80.regs.HL.B.l = RES_0_XNN(addr); 
}

static void res_1_a() { 
    RES(1, &z80.regs.AF.B.h);
}

static void res_1_b() {
    RES(1, &z80.regs.BC.B.h);
}

static void res_1_c() {
    RES(1, &z80.regs.BC.B.l); 
}

static void res_1_d() {
    RES(1, &z80.regs.DE.B.h); 
}

static void res_1_e() {
    RES(1, &z80.regs.DE.B.l); 
}

static void res_1_h() {
    RES(1, &z80.regs.HL.B.h);
}

static void res_1_l() {
    RES(1, &z80.regs.HL.B.l); 
}

static void res_1_xhl() {
    UInt8 val = readMem(z80.regs.HL.W);
    RES(1, &val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 RES_1_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    RES(1, &val);
    delayBit(z80);             // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void res_1_xnn  (UInt16 addr) {
    RES_1_XNN(addr); 
}

static void res_1_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = RES_1_XNN(addr);
}

static void res_1_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = RES_1_XNN(addr);
}

static void res_1_xnn_c(UInt16 addr) { 
    z80.regs.BC.B.l = RES_1_XNN(addr); 
}

static void res_1_xnn_d(UInt16 addr) { 
    z80.regs.DE.B.h = RES_1_XNN(addr);
}

static void res_1_xnn_e(UInt16 addr) { 
    z80.regs.DE.B.l = RES_1_XNN(addr);
}

static void res_1_xnn_h(UInt16 addr) { 
    z80.regs.HL.B.h = RES_1_XNN(addr);
}

static void res_1_xnn_l(UInt16 addr) { 
    z80.regs.HL.B.l = RES_1_XNN(addr);
}

static void res_2_a() {
    RES(2, &z80.regs.AF.B.h);
}

static void res_2_b() {
    RES(2, &z80.regs.BC.B.h);
}

static void res_2_c() {
    RES(2, &z80.regs.BC.B.l);
}

static void res_2_d() {
    RES(2, &z80.regs.DE.B.h);
}

static void res_2_e() { 
    RES(2, &z80.regs.DE.B.l); 
}

static void res_2_h() {
    RES(2, &z80.regs.HL.B.h); 
}

static void res_2_l() {
    RES(2, &z80.regs.HL.B.l);
}

static void res_2_xhl() {
    UInt8 val = readMem(z80.regs.HL.W);
    RES(2, &val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 RES_2_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    RES(2, &val);
    delayBit(z80);             // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void res_2_xnn  (UInt16 addr) {
    RES_2_XNN(addr); 
}

static void res_2_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = RES_2_XNN(addr);
}

static void res_2_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = RES_2_XNN(addr);
}

static void res_2_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = RES_2_XNN(addr);
}

static void res_2_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = RES_2_XNN(addr);
}

static void res_2_xnn_e(UInt16 addr) {
    z80.regs.DE.B.l = RES_2_XNN(addr);
}

static void res_2_xnn_h(UInt16 addr) {
    z80.regs.HL.B.h = RES_2_XNN(addr); 
}

static void res_2_xnn_l(UInt16 addr) {
    z80.regs.HL.B.l = RES_2_XNN(addr);
}

static void res_3_a() {
    RES(3, &z80.regs.AF.B.h);
}

static void res_3_b() {
    RES(3, &z80.regs.BC.B.h);
}

static void res_3_c() { 
    RES(3, &z80.regs.BC.B.l);
}

static void res_3_d() {
    RES(3, &z80.regs.DE.B.h);
}

static void res_3_e() {
    RES(3, &z80.regs.DE.B.l);
}

static void res_3_h() {
    RES(3, &z80.regs.HL.B.h);
}

static void res_3_l() {
    RES(3, &z80.regs.HL.B.l);
}

static void res_3_xhl() {
    UInt8 val = readMem(z80.regs.HL.W);
    RES(3, &val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 RES_3_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    RES(3, &val);
    delayBit(z80);             // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void res_3_xnn  (UInt16 addr) {
    RES_3_XNN(addr);
}

static void res_3_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = RES_3_XNN(addr); 
}

static void res_3_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = RES_3_XNN(addr);
}

static void res_3_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = RES_3_XNN(addr); 
}

static void res_3_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = RES_3_XNN(addr);
}

static void res_3_xnn_e(UInt16 addr) {
    z80.regs.DE.B.l = RES_3_XNN(addr);
}

static void res_3_xnn_h(UInt16 addr) { 
    z80.regs.HL.B.h = RES_3_XNN(addr); 
}

static void res_3_xnn_l(UInt16 addr) {
    z80.regs.HL.B.l = RES_3_XNN(addr);
}

static void res_4_a() {
    RES(4, &z80.regs.AF.B.h);
}

static void res_4_b() {
    RES(4, &z80.regs.BC.B.h);
}

static void res_4_c() { 
    RES(4, &z80.regs.BC.B.l);
}

static void res_4_d() {
    RES(4, &z80.regs.DE.B.h);
}

static void res_4_e() {
    RES(4, &z80.regs.DE.B.l);
}

static void res_4_h() {
    RES(4, &z80.regs.HL.B.h);
}

static void res_4_l() {
    RES(4, &z80.regs.HL.B.l); 
}

static void res_4_xhl() {
    UInt8 val = readMem(z80.regs.HL.W);
    RES(4, &val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 RES_4_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    RES(4, &val);
    delayBit(z80);             // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void res_4_xnn  (UInt16 addr) {
    RES_4_XNN(addr); 
}

static void res_4_xnn_a(UInt16 addr) { 
    z80.regs.AF.B.h = RES_4_XNN(addr); 
}

static void res_4_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = RES_4_XNN(addr);
}

static void res_4_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = RES_4_XNN(addr);
}

static void res_4_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = RES_4_XNN(addr);
}

static void res_4_xnn_e(UInt16 addr) {
    z80.regs.DE.B.l = RES_4_XNN(addr);
}

static void res_4_xnn_h(UInt16 addr) {
    z80.regs.HL.B.h = RES_4_XNN(addr);
}

static void res_4_xnn_l(UInt16 addr) {
    z80.regs.HL.B.l = RES_4_XNN(addr);
}

static void res_5_a() {
    RES(5, &z80.regs.AF.B.h);
}

static void res_5_b() {
    RES(5, &z80.regs.BC.B.h);
}

static void res_5_c() {
    RES(5, &z80.regs.BC.B.l);
}

static void res_5_d() {
    RES(5, &z80.regs.DE.B.h);
}

static void res_5_e() {
    RES(5, &z80.regs.DE.B.l);
}

static void res_5_h() {
    RES(5, &z80.regs.HL.B.h);
}

static void res_5_l() {
    RES(5, &z80.regs.HL.B.l);
}

static void res_5_xhl() {
    UInt8 val = readMem(z80.regs.HL.W);
    RES(5, &val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 RES_5_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    RES(5, &val);
    delayBit(z80);             // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void res_5_xnn  (UInt16 addr) {
    RES_5_XNN(addr);
}

static void res_5_xnn_a(UInt16 addr) { 
    z80.regs.AF.B.h = RES_5_XNN(addr);
}

static void res_5_xnn_b(UInt16 addr) { 
    z80.regs.BC.B.h = RES_5_XNN(addr);
}

static void res_5_xnn_c(UInt16 addr) { 
    z80.regs.BC.B.l = RES_5_XNN(addr);
}

static void res_5_xnn_d(UInt16 addr) { 
    z80.regs.DE.B.h = RES_5_XNN(addr);
}

static void res_5_xnn_e(UInt16 addr) { 
    z80.regs.DE.B.l = RES_5_XNN(addr);
}

static void res_5_xnn_h(UInt16 addr) { 
    z80.regs.HL.B.h = RES_5_XNN(addr);
}

static void res_5_xnn_l(UInt16 addr) { 
    z80.regs.HL.B.l = RES_5_XNN(addr);
}

static void res_6_a() {
    RES(6, &z80.regs.AF.B.h);
}

static void res_6_b() {
    RES(6, &z80.regs.BC.B.h);
}

static void res_6_c() {
    RES(6, &z80.regs.BC.B.l); 
}

static void res_6_d() { 
    RES(6, &z80.regs.DE.B.h);
}

static void res_6_e() { 
    RES(6, &z80.regs.DE.B.l);
}

static void res_6_h() { 
    RES(6, &z80.regs.HL.B.h);
}

static void res_6_l() { 
    RES(6, &z80.regs.HL.B.l);
}

static void res_6_xhl() {
    UInt8 val = readMem(z80.regs.HL.W);
    RES(6, &val); 
    delayBit(z80);             // white cat append
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 RES_6_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    RES(6, &val);
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void res_6_xnn  (UInt16 addr) {
    RES_6_XNN(addr);
}

static void res_6_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = RES_6_XNN(addr);
}

static void res_6_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = RES_6_XNN(addr);
}

static void res_6_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = RES_6_XNN(addr); 
}

static void res_6_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = RES_6_XNN(addr);
}

static void res_6_xnn_e(UInt16 addr) {
    z80.regs.DE.B.l = RES_6_XNN(addr);
}

static void res_6_xnn_h(UInt16 addr) {
    z80.regs.HL.B.h = RES_6_XNN(addr);
}

static void res_6_xnn_l(UInt16 addr) {
    z80.regs.HL.B.l = RES_6_XNN(addr);
}

static void res_7_a() {
    RES(7, &z80.regs.AF.B.h);
}

static void res_7_b() {
    RES(7, &z80.regs.BC.B.h);
}

static void res_7_c() {
    RES(7, &z80.regs.BC.B.l);
}

static void res_7_d() { 
    RES(7, &z80.regs.DE.B.h);
}

static void res_7_e() {
    RES(7, &z80.regs.DE.B.l);
}

static void res_7_h() {
    RES(7, &z80.regs.HL.B.h);
}

static void res_7_l() {
    RES(7, &z80.regs.HL.B.l); 
}

static void res_7_xhl() {
    UInt8 val = readMem(z80.regs.HL.W);
    RES(7, &val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 RES_7_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    RES(7, &val);
    delayBit(z80);             // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void res_7_xnn  (UInt16 addr) {
    RES_7_XNN(addr); 
}

static void res_7_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = RES_7_XNN(addr);
}

static void res_7_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = RES_7_XNN(addr); 
}

static void res_7_xnn_c(UInt16 addr) { 
    z80.regs.BC.B.l = RES_7_XNN(addr); 
}

static void res_7_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = RES_7_XNN(addr);
}

static void res_7_xnn_e(UInt16 addr) { 
    z80.regs.DE.B.l = RES_7_XNN(addr); 
}

static void res_7_xnn_h(UInt16 addr) { 
    z80.regs.HL.B.h = RES_7_XNN(addr); 
}

static void res_7_xnn_l(UInt16 addr) { 
    z80.regs.HL.B.l = RES_7_XNN(addr); 
}

static void set_0_a() {
    SET(0, &z80.regs.AF.B.h); 
}

static void set_0_b() {
    SET(0, &z80.regs.BC.B.h);
}

static void set_0_c() {
    SET(0, &z80.regs.BC.B.l);
}

static void set_0_d() {
    SET(0, &z80.regs.DE.B.h);
}

static void set_0_e() { 
    SET(0, &z80.regs.DE.B.l);
}

static void set_0_h() { 
    SET(0, &z80.regs.HL.B.h);
}

static void set_0_l() {
    SET(0, &z80.regs.HL.B.l);
}

static void set_0_xhl() {
    UInt8 val = readMem(z80.regs.HL.W);
    SET(0, &val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 SET_0_XNN(UInt16 addr) {

    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;

    SET(0, &val);
    delayBit(z80);             // white cat append
    delayInc(z80);

    writeMem(addr, val);
    return val;
}

static void set_0_xnn  (UInt16 addr) { 
    SET_0_XNN(addr);
}

static void set_0_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = SET_0_XNN(addr);
}

static void set_0_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = SET_0_XNN(addr);
}

static void set_0_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = SET_0_XNN(addr);
}

static void set_0_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = SET_0_XNN(addr);
}

static void set_0_xnn_e(UInt16 addr) {
    z80.regs.DE.B.l = SET_0_XNN(addr);
}

static void set_0_xnn_h(UInt16 addr) { 
    z80.regs.HL.B.h = SET_0_XNN(addr); 
}

static void set_0_xnn_l(UInt16 addr) { 
    z80.regs.HL.B.l = SET_0_XNN(addr);
}

static void set_1_a() {
    SET(1, &z80.regs.AF.B.h);
}

static void set_1_b() {
    SET(1, &z80.regs.BC.B.h);
}

static void set_1_c() {
    SET(1, &z80.regs.BC.B.l);
}

static void set_1_d() {
    SET(1, &z80.regs.DE.B.h);
}

static void set_1_e() {
    SET(1, &z80.regs.DE.B.l);
}

static void set_1_h() {
    SET(1, &z80.regs.HL.B.h);
}

static void set_1_l() { 
    SET(1, &z80.regs.HL.B.l);
}

static void set_1_xhl() {
    UInt8 val = readMem(z80.regs.HL.W);
    SET(1, &val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 SET_1_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    SET(1, &val);
    delayBit(z80);             // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void set_1_xnn  (UInt16 addr) { 
    SET_1_XNN(addr);
}

static void set_1_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = SET_1_XNN(addr); 
}

static void set_1_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = SET_1_XNN(addr);
}

static void set_1_xnn_c(UInt16 addr) { 
    z80.regs.BC.B.l = SET_1_XNN(addr);
}

static void set_1_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = SET_1_XNN(addr);
}

static void set_1_xnn_e(UInt16 addr) { 
    z80.regs.DE.B.l = SET_1_XNN(addr);
}

static void set_1_xnn_h(UInt16 addr) { 
    z80.regs.HL.B.h = SET_1_XNN(addr);
}

static void set_1_xnn_l(UInt16 addr) {
    z80.regs.HL.B.l = SET_1_XNN(addr);
}

static void set_2_a() { 
    SET(2, &z80.regs.AF.B.h);
}

static void set_2_b() {
    SET(2, &z80.regs.BC.B.h); 
}

static void set_2_c() {
    SET(2, &z80.regs.BC.B.l); 
}

static void set_2_d() { 
    SET(2, &z80.regs.DE.B.h);
}

static void set_2_e() { 
    SET(2, &z80.regs.DE.B.l);
}

static void set_2_h() {
    SET(2, &z80.regs.HL.B.h);
}

static void set_2_l() {
    SET(2, &z80.regs.HL.B.l);
}

static void set_2_xhl() {
    UInt8 val = readMem(z80.regs.HL.W);
    SET(2, &val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 SET_2_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    SET(2, &val);
    delayBit(z80);             // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void set_2_xnn  (UInt16 addr) {
    SET_2_XNN(addr);
}

static void set_2_xnn_a(UInt16 addr) { 
    z80.regs.AF.B.h = SET_2_XNN(addr); 
}

static void set_2_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = SET_2_XNN(addr); 
}

static void set_2_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = SET_2_XNN(addr);
}

static void set_2_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = SET_2_XNN(addr);
}

static void set_2_xnn_e(UInt16 addr) { 
    z80.regs.DE.B.l = SET_2_XNN(addr);
}

static void set_2_xnn_h(UInt16 addr) { 
    z80.regs.HL.B.h = SET_2_XNN(addr); 
}

static void set_2_xnn_l(UInt16 addr) { 
    z80.regs.HL.B.l = SET_2_XNN(addr); 
}

static void set_3_a() {
    SET(3, &z80.regs.AF.B.h);
}

static void set_3_b() {
    SET(3, &z80.regs.BC.B.h);
}

static void set_3_c() {
    SET(3, &z80.regs.BC.B.l);
}

static void set_3_d() { 
    SET(3, &z80.regs.DE.B.h);
}

static void set_3_e() { 
    SET(3, &z80.regs.DE.B.l);
}

static void set_3_h() { 
    SET(3, &z80.regs.HL.B.h);
}

static void set_3_l() { 
    SET(3, &z80.regs.HL.B.l);
}

static void set_3_xhl() {
    UInt8 val = readMem(z80.regs.HL.W);
    SET(3, &val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 SET_3_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    SET(3, &val);
    delayBit(z80);             // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void set_3_xnn  (UInt16 addr) {
    SET_3_XNN(addr);
}

static void set_3_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = SET_3_XNN(addr); 
}

static void set_3_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = SET_3_XNN(addr);
}

static void set_3_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = SET_3_XNN(addr);
}

static void set_3_xnn_d(UInt16 addr) { 
    z80.regs.DE.B.h = SET_3_XNN(addr);
}

static void set_3_xnn_e(UInt16 addr) {
    z80.regs.DE.B.l = SET_3_XNN(addr);
}

static void set_3_xnn_h(UInt16 addr) { 
    z80.regs.HL.B.h = SET_3_XNN(addr);
}

static void set_3_xnn_l(UInt16 addr) { 
    z80.regs.HL.B.l = SET_3_XNN(addr);
}

static void set_4_a() {
    SET(4, &z80.regs.AF.B.h);
}

static void set_4_b() {
    SET(4, &z80.regs.BC.B.h);
}

static void set_4_c() {
    SET(4, &z80.regs.BC.B.l);
}

static void set_4_d() {
    SET(4, &z80.regs.DE.B.h);
}

static void set_4_e() {
    SET(4, &z80.regs.DE.B.l);
}

static void set_4_h() {
    SET(4, &z80.regs.HL.B.h); 
}

static void set_4_l() {
    SET(4, &z80.regs.HL.B.l); 
}

static void set_4_xhl() {
    UInt8 val = readMem(z80.regs.HL.W);
    SET(4, &val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 SET_4_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    SET(4, &val);
    delayBit(z80);             // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void set_4_xnn  (UInt16 addr) {
    SET_4_XNN(addr);
}

static void set_4_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = SET_4_XNN(addr);
}

static void set_4_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = SET_4_XNN(addr);
}

static void set_4_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = SET_4_XNN(addr);
}

static void set_4_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = SET_4_XNN(addr);
}

static void set_4_xnn_e(UInt16 addr) {
    z80.regs.DE.B.l = SET_4_XNN(addr);
}

static void set_4_xnn_h(UInt16 addr) {
    z80.regs.HL.B.h = SET_4_XNN(addr);
}

static void set_4_xnn_l(UInt16 addr) {
    z80.regs.HL.B.l = SET_4_XNN(addr);
}

static void set_5_a() { 
    SET(5, &z80.regs.AF.B.h); 
}

static void set_5_b() {
    SET(5, &z80.regs.BC.B.h);
}

static void set_5_c() {
    SET(5, &z80.regs.BC.B.l);
}

static void set_5_d() { 
    SET(5, &z80.regs.DE.B.h);
}

static void set_5_e() { 
    SET(5, &z80.regs.DE.B.l); 
}

static void set_5_h() { 
    SET(5, &z80.regs.HL.B.h); 
}

static void set_5_l() { 
    SET(5, &z80.regs.HL.B.l);
}

static void set_5_xhl() {
    UInt8 val = readMem(z80.regs.HL.W);
    SET(5, &val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 SET_5_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    SET(5, &val);
    delayBit(z80);             // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void set_5_xnn  (UInt16 addr) {
    SET_5_XNN(addr);
}

static void set_5_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = SET_5_XNN(addr);
}

static void set_5_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = SET_5_XNN(addr);
}

static void set_5_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = SET_5_XNN(addr);
}

static void set_5_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = SET_5_XNN(addr);
}

static void set_5_xnn_e(UInt16 addr) { 
    z80.regs.DE.B.l = SET_5_XNN(addr);
}

static void set_5_xnn_h(UInt16 addr) {
    z80.regs.HL.B.h = SET_5_XNN(addr);
}

static void set_5_xnn_l(UInt16 addr) { 
    z80.regs.HL.B.l = SET_5_XNN(addr);
}

static void set_6_a() {
    SET(6, &z80.regs.AF.B.h);
}

static void set_6_b() {
    SET(6, &z80.regs.BC.B.h);
}

static void set_6_c() {
    SET(6, &z80.regs.BC.B.l);
}

static void set_6_d() {
    SET(6, &z80.regs.DE.B.h);
}

static void set_6_e() {
    SET(6, &z80.regs.DE.B.l); 
}

static void set_6_h() {
    SET(6, &z80.regs.HL.B.h);
}

static void set_6_l() { 
    SET(6, &z80.regs.HL.B.l); 
}

static void set_6_xhl() {
    UInt8 val = readMem(z80.regs.HL.W);
    SET(6, &val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 SET_6_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    SET(6, &val);
    delayBit(z80);             // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void set_6_xnn  (UInt16 addr) {
    SET_6_XNN(addr); 
}

static void set_6_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = SET_6_XNN(addr); 
}

static void set_6_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = SET_6_XNN(addr);
}

static void set_6_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = SET_6_XNN(addr);
}

static void set_6_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = SET_6_XNN(addr);
}

static void set_6_xnn_e(UInt16 addr) {
    z80.regs.DE.B.l = SET_6_XNN(addr); 
}

static void set_6_xnn_h(UInt16 addr) {
    z80.regs.HL.B.h = SET_6_XNN(addr);
}

static void set_6_xnn_l(UInt16 addr) { 
    z80.regs.HL.B.l = SET_6_XNN(addr);
}

static void set_7_a() {
    SET(7, &z80.regs.AF.B.h); 
}

static void set_7_b() {
    SET(7, &z80.regs.BC.B.h); 
}

static void set_7_c() {
    SET(7, &z80.regs.BC.B.l); 
}

static void set_7_d() {
    SET(7, &z80.regs.DE.B.h); 
}

static void set_7_e() {
    SET(7, &z80.regs.DE.B.l);
}

static void set_7_h() {
    SET(7, &z80.regs.HL.B.h);
}

static void set_7_l() {
    SET(7, &z80.regs.HL.B.l); 
}

static void set_7_xhl() {
    UInt8 val = readMem(z80.regs.HL.W);
    SET(7, &val); 
    delayInc(z80);
    writeMem(z80.regs.HL.W, val);
}

static UInt8 SET_7_XNN(UInt16 addr) {
    UInt8 val = readMem(addr);
    z80.regs.SH.W = addr;
    SET(7, &val);
    delayBit(z80);             // white cat append
    delayInc(z80);
    writeMem(addr, val);
    return val;
}

static void set_7_xnn  (UInt16 addr) {
    SET_7_XNN(addr);
}

static void set_7_xnn_a(UInt16 addr) {
    z80.regs.AF.B.h = SET_7_XNN(addr);
}

static void set_7_xnn_b(UInt16 addr) {
    z80.regs.BC.B.h = SET_7_XNN(addr);
}

static void set_7_xnn_c(UInt16 addr) {
    z80.regs.BC.B.l = SET_7_XNN(addr);
}

static void set_7_xnn_d(UInt16 addr) {
    z80.regs.DE.B.h = SET_7_XNN(addr);
}

static void set_7_xnn_e(UInt16 addr) {
    z80.regs.DE.B.l = SET_7_XNN(addr); 
}

static void set_7_xnn_h(UInt16 addr) {
    z80.regs.HL.B.h = SET_7_XNN(addr);
}

static void set_7_xnn_l(UInt16 addr) {
    z80.regs.HL.B.l = SET_7_XNN(addr);
}

static void ex_af_af() {
    UInt16 regVal = z80.regs.AF.W;
    z80.regs.AF.W = z80.regs.AF1.W;
    z80.regs.AF1.W = regVal;
}

static void djnz() {
    delayDjnz(z80);
    z80.regs.BC.B.h--;
    if (z80.regs.BC.B.h != 0) {
        JR(z80);
    }
    else {
        SKIP_JR(z80);
    }
}

static void jr() {
    JR(z80);
}

static void jr_z() {
    if (z80.regs.AF.B.l & Z_FLAG) {
        JR(z80);
    }
    else {
        SKIP_JR(z80);
    }
}

static void jr_nz() {
    if (z80.regs.AF.B.l & Z_FLAG) {
        SKIP_JR(z80);
    }
    else {
        JR(z80);
    }
}

static void jr_c() {
    if (z80.regs.AF.B.l & C_FLAG) {
        JR(z80);
    }
    else {
        SKIP_JR(z80);
    }
}

static void jr_nc() {
    if (z80.regs.AF.B.l & C_FLAG) {
        SKIP_JR(z80);
    }
    else {
        JR(z80);
    }
}

static void jp() {
    JP(z80);
}

static void jp_hl() { 
    z80.regs.PC.W = z80.regs.HL.W; 
}

static void jp_ix() { 
    z80.regs.PC.W = z80.regs.IX.W; 
}

static void jp_iy() { 
    z80.regs.PC.W = z80.regs.IY.W; 
}

static void jp_z() {
    if (z80.regs.AF.B.l & Z_FLAG) {
        JP(z80);
    }
    else {
        SKIP_JP(z80);
    }
}

static void jp_nz() {
    if (z80.regs.AF.B.l & Z_FLAG) {
        SKIP_JP(z80);
    }
    else {
        JP(z80);
    }
}

static void jp_c() {
    if (z80.regs.AF.B.l & C_FLAG) {
        JP(z80);
    }
    else {
        SKIP_JP(z80);
    }
}

static void jp_nc() {
    if (z80.regs.AF.B.l & C_FLAG) {
        SKIP_JP(z80);
    }
    else {
        JP(z80);
    }
}

static void jp_m() {
    if (z80.regs.AF.B.l & S_FLAG) {
        JP(z80);
    }
    else {
        SKIP_JP(z80);
    }
}

static void jp_p() {
    if (z80.regs.AF.B.l & S_FLAG) {
        SKIP_JP(z80);
    }
    else {
        JP(z80);
    }
}

static void jp_pe() {
    if (z80.regs.AF.B.l & V_FLAG) {
        JP(z80);
    }
    else {
        SKIP_JP(z80);
    }
}

static void jp_po() {
    if (z80.regs.AF.B.l & V_FLAG) {
        SKIP_JP(z80);
    }
    else {
        JP(z80);
    }
}

static void call() {
    CALL(z80);
}

static void call_z() {
    if (z80.regs.AF.B.l & Z_FLAG) {
        CALL(z80);
    }
    else {
        SKIP_CALL(z80);
    }
}

static void call_nz() {
    if (z80.regs.AF.B.l & Z_FLAG) {
        SKIP_CALL(z80);
    }
    else {
        CALL(z80);
    }
}

static void call_c() {
    if (z80.regs.AF.B.l & C_FLAG) {
        CALL(z80);
    }
    else {
        SKIP_CALL(z80);
    }
}

static void call_nc() {
    if (z80.regs.AF.B.l & C_FLAG) {
        SKIP_CALL(z80);
    }
    else {
        CALL(z80);
    }
}

static void call_m() {
    if (z80.regs.AF.B.l & S_FLAG) {
        CALL(z80);
    }
    else {
        SKIP_CALL(z80);
    }
}

static void call_p() {
    if (z80.regs.AF.B.l & S_FLAG) {
        SKIP_CALL(z80);
    }
    else {
        CALL(z80);
    }
}

static void call_pe() {
    if (z80.regs.AF.B.l & V_FLAG) {
        CALL(z80);
    }
    else {
        SKIP_CALL(z80);
    }
}

static void call_po() {
    if (z80.regs.AF.B.l & V_FLAG) {
        SKIP_CALL(z80);
    }
    else {
        CALL(z80);
    }
}

static void ret() {
    RET(z80);
}

static void ret_c() {
    delayRet(z80);
    if (z80.regs.AF.B.l & C_FLAG) {
        RET(z80);
    }
}

static void ret_nc() {
    delayRet(z80);
    if (!(z80.regs.AF.B.l & C_FLAG)) {
        RET(z80);
    }
}

static void ret_z() {
    delayRet(z80);
    if (z80.regs.AF.B.l & Z_FLAG) {
        RET(z80);
    }
}

static void ret_nz() {
    delayRet(z80);
    if (!(z80.regs.AF.B.l & Z_FLAG)) {
        RET(z80);
    }
}

static void ret_m() {
    delayRet(z80);
    if (z80.regs.AF.B.l & S_FLAG) {
        RET(z80);
    }
}

static void ret_p() {
    delayRet(z80);
    if (!(z80.regs.AF.B.l & S_FLAG)) {
        RET(z80);
    }
}

static void ret_pe() {
    delayRet(z80);
    if (z80.regs.AF.B.l & V_FLAG) {
        RET(z80);
    }
}

static void ret_po() {
    delayRet(z80);
    if (!(z80.regs.AF.B.l & V_FLAG)) {
        RET(z80);
    }
}

static void reti() {
    z80.regs.iff1 = z80.regs.iff2;
    RET(z80);
}

static void retn() {
    z80.regs.iff1 = z80.regs.iff2;
    RET(z80); 
}

static void ex_xsp_hl() { 
    EX_SP(&z80.regs.HL.W);
}

static void ex_xsp_ix() { 
    EX_SP(&z80.regs.IX.W); 
}

static void ex_xsp_iy() { 

    EX_SP(&z80.regs.IY.W); 

}

static void ex_de_hl() {
    UInt16 tmp = z80.regs.DE.W;
    z80.regs.DE.W  = z80.regs.HL.W;
    z80.regs.HL.W  = tmp;
}


static void rlca() {
    UInt8 regVal = z80.regs.AF.B.h;
    z80.regs.AF.B.h = (regVal << 1) | (regVal >> 7);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & (S_FLAG | Z_FLAG | P_FLAG)) |
        (z80.regs.AF.B.h & (Y_FLAG | X_FLAG | C_FLAG));
}

static void rrca() {

    UInt8 regVal = z80.regs.AF.B.h;
    z80.regs.AF.B.h = (regVal >> 1) | (regVal << 7);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & (S_FLAG | Z_FLAG | P_FLAG)) | 
        (regVal &  C_FLAG) | (z80.regs.AF.B.h & (X_FLAG | Y_FLAG));
}

static void rla() {
    UInt8 regVal = z80.regs.AF.B.h;
    z80.regs.AF.B.h = (regVal << 1) | (z80.regs.AF.B.l & C_FLAG);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & (S_FLAG | Z_FLAG | P_FLAG)) |
        ((regVal >> 7) & C_FLAG) | (z80.regs.AF.B.h & (X_FLAG | Y_FLAG));
}

static void rra() {
    UInt8 regVal = z80.regs.AF.B.h;
    z80.regs.AF.B.h = (regVal >> 1) | ((z80.regs.AF.B.l & C_FLAG) << 7);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & (S_FLAG | Z_FLAG | P_FLAG)) |
        (regVal & C_FLAG) | (z80.regs.AF.B.h & (X_FLAG | Y_FLAG));
}

static void daa() {
    int regVal = z80.regs.AF.B.l;
    z80.regs.AF.W = DAATable[(int)z80.regs.AF.B.h | ((regVal & 3) << 8) | 
        ((regVal & 0x10) << 6)];
}

static void cpl() {
    z80.regs.AF.B.h ^= 0xff;
    z80.regs.AF.B.l = 
        (z80.regs.AF.B.l & (S_FLAG | Z_FLAG | P_FLAG | C_FLAG)) |
        H_FLAG | N_FLAG | (z80.regs.AF.B.h & (X_FLAG | Y_FLAG));
}

static void scf() {
    z80.regs.AF.B.l = (z80.regs.AF.B.l & (S_FLAG | Z_FLAG | P_FLAG)) |
        C_FLAG | (z80.regs.AF.B.h & (X_FLAG | Y_FLAG));
}

static void ccf() { //DIFF
    z80.regs.AF.B.l = 
        ((z80.regs.AF.B.l & (S_FLAG | Z_FLAG | P_FLAG | C_FLAG)) |
        ((z80.regs.AF.B.l & C_FLAG) << 4) |
        (z80.regs.AF.B.h & (X_FLAG | Y_FLAG))) ^ C_FLAG;
}

static void halt() {
    if ((z80.intState == INT_LOW && z80.regs.iff1) || (z80.nmiState == INT_EDGE)) {
		z80.regs.halt=0;
    }
	else {
		z80.regs.PC.W--;
		z80.regs.halt=1;
	}
}

static void push_af() {
    PUSH(&z80.regs.AF.W);
}

static void push_bc() {
    PUSH(&z80.regs.BC.W); 
}

static void push_de() {
    PUSH(&z80.regs.DE.W);
}

static void push_hl() {
    PUSH(&z80.regs.HL.W);
}

static void push_ix() {
    PUSH(&z80.regs.IX.W);
}

static void push_iy() { 
    PUSH(&z80.regs.IY.W);
}

static void pop_af() {
    POP(&z80.regs.AF.W);
}

static void pop_bc() {
    POP(&z80.regs.BC.W);
}

static void pop_de() {
    POP(&z80.regs.DE.W);
}

static void pop_hl() {
    POP(&z80.regs.HL.W); 
}

static void pop_ix() {
    POP(&z80.regs.IX.W); 
}

static void pop_iy() {
    POP(&z80.regs.IY.W);
}

static void rst_00() {
    RST(0x00);
}
static void rst_08() {
    RST(0x08);
}
static void rst_10() {
    RST(0x10);
}
static void rst_18() {
    RST(0x18);
}
static void rst_20() {
    RST(0x20);
}
static void rst_28() {
    RST(0x28);
}
static void rst_30() {
    RST(0x30);
}
static void rst_38() {
    RST(0x38);
}

static void out_byte_a() {
    RegisterPair port;
    port.B.l = readOpcode(z80.regs.PC.W++);
    port.B.h = z80.regs.AF.B.h;
    writePort(port.W, z80.regs.AF.B.h);
}

static void in_a_byte() {
    RegisterPair port;
    port.B.l = readOpcode(z80.regs.PC.W++);
    port.B.h = z80.regs.AF.B.h;
    z80.regs.AF.B.h = readPort(port.W);
}

static void exx() {
    UInt16 tmp;
    tmp        = z80.regs.BC.W; 
    z80.regs.BC.W  = z80.regs.BC1.W; 
    z80.regs.BC1.W = tmp;
    tmp        = z80.regs.DE.W; 
    z80.regs.DE.W  = z80.regs.DE1.W; 
    z80.regs.DE1.W = tmp;
    tmp        = z80.regs.HL.W; 
    z80.regs.HL.W  = z80.regs.HL1.W; 
    z80.regs.HL1.W = tmp;
}

static void rld() {
    UInt8 val = readMem(z80.regs.HL.W);
    z80.regs.SH.W = z80.regs.HL.W + 1;
    delayRld(z80);
    writeMem(z80.regs.HL.W, (val << 4) | (z80.regs.AF.B.h & 0x0f));
    z80.regs.AF.B.h = (z80.regs.AF.B.h & 0xf0) | (val >> 4);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        ZSPXYTable[z80.regs.AF.B.h];
}

static void rrd() {
    UInt8 val = readMem(z80.regs.HL.W);
    z80.regs.SH.W = z80.regs.HL.W + 1;
    delayRld(z80);
    writeMem(z80.regs.HL.W, (val >> 4) | (z80.regs.AF.B.h << 4));
    z80.regs.AF.B.h = (z80.regs.AF.B.h & 0xf0) | (val & 0x0f);
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        ZSPXYTable[z80.regs.AF.B.h];
}

static void di() {
    z80.regs.iff1 = 0;
    z80.regs.iff2 = 0;
}

static void ei() {
/*    if (!z80.regs.iff1) {
        z80.regs.iff2 = 1;
        z80.regs.iff1 = 2;
    }*/
        z80.regs.iff2 = 1;
        z80.regs.iff1 = 1;
		z80.regs.ei_mode=1;
}

static void im_0()  {
    z80.regs.im = 0;
}

static void im_1()  {
    z80.regs.im = 1;
}

static void im_2()  {
    z80.regs.im = 2;
}

static void in_a_c() { 
    z80.regs.AF.B.h = readPort(z80.regs.BC.W); 
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        ZSPXYTable[z80.regs.AF.B.h]; 
}

static void in_b_c() { 
    z80.regs.BC.B.h = readPort(z80.regs.BC.W); 
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        ZSPXYTable[z80.regs.BC.B.h]; 
}

static void in_c_c() { 
    z80.regs.BC.B.l = readPort(z80.regs.BC.W); 
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        ZSPXYTable[z80.regs.BC.B.l]; 
}

static void in_d_c() { 
    z80.regs.DE.B.h = readPort(z80.regs.BC.W); 
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        ZSPXYTable[z80.regs.DE.B.h]; 
}

static void in_e_c() { 
    z80.regs.DE.B.l = readPort(z80.regs.BC.W); 
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        ZSPXYTable[z80.regs.DE.B.l]; 
}

static void out_c_a()   {
    writePort(z80.regs.BC.W, z80.regs.AF.B.h); 
}

static void out_c_b()   {
    writePort(z80.regs.BC.W, z80.regs.BC.B.h);
}

static void out_c_c()   { 
    writePort(z80.regs.BC.W, z80.regs.BC.B.l);
}

static void out_c_d()   {
    writePort(z80.regs.BC.W, z80.regs.DE.B.h);
}

static void out_c_e()   {
    writePort(z80.regs.BC.W, z80.regs.DE.B.l);
}

static void out_c_h()   {
    writePort(z80.regs.BC.W, z80.regs.HL.B.h);
}

static void out_c_l()   {
    writePort(z80.regs.BC.W, z80.regs.HL.B.l);
}

static void out_c_0()   { 
    writePort(z80.regs.BC.W, 0); 
}

static void in_h_c() { 
    z80.regs.HL.B.h = readPort(z80.regs.BC.W); 
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        ZSPXYTable[z80.regs.HL.B.h]; 
}

static void in_l_c() { 
    z80.regs.HL.B.l = readPort(z80.regs.BC.W); 
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        ZSPXYTable[z80.regs.HL.B.l];
}

static void in_0_c() { 
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        ZSPXYTable[readPort(z80.regs.BC.W)]; 
}

static void cpi() { 
    UInt8 val = readMem(z80.regs.HL.W++);
    UInt8 rv = z80.regs.AF.B.h - val;
    delayBlock(z80);

    z80.regs.BC.W--;
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        ((z80.regs.AF.B.h ^ val ^ rv) & H_FLAG) | 
        (ZSPXYTable[rv & 0xff] & (Z_FLAG | S_FLAG)) | N_FLAG;
    rv -= (z80.regs.AF.B.l & H_FLAG) >> 4;
    z80.regs.AF.B.l |= ((rv << 4) & Y_FLAG) | (rv & X_FLAG) | 
        (z80.regs.BC.W ? P_FLAG : 0);
}

static void cpir() { 
    cpi(z80);
    if (z80.regs.BC.W && !(z80.regs.AF.B.l & Z_FLAG)) {
        delayBlock(z80); 
        z80.regs.PC.W -= 2;
    }
}

static void cpd() { 
    UInt8 val = readMem(z80.regs.HL.W--);
    UInt8 rv = z80.regs.AF.B.h - val;
    delayBlock(z80);

    z80.regs.BC.W--;
    z80.regs.AF.B.l = (z80.regs.AF.B.l & C_FLAG) | 
        ((z80.regs.AF.B.h ^ val ^ rv) & H_FLAG) | 
        (ZSPXYTable[rv & 0xff] & (Z_FLAG | S_FLAG)) | N_FLAG;
    rv -= (z80.regs.AF.B.l & H_FLAG) >> 4;
    z80.regs.AF.B.l |= ((rv << 4) & Y_FLAG) | (rv & X_FLAG) |
        (z80.regs.BC.W ? P_FLAG : 0);
}

static void cpdr() { 
    cpd(z80);
    if (z80.regs.BC.W && !(z80.regs.AF.B.l & Z_FLAG)) {
        delayBlock(z80); 
        z80.regs.PC.W -= 2;
    }
}

static void ldi() { 
    UInt8 val = readMem(z80.regs.HL.W++);
    writeMem(z80.regs.DE.W++, val);
    delayLdi(z80);

    z80.regs.BC.W--;
    z80.regs.AF.B.l = (z80.regs.AF.B.l & (S_FLAG | Z_FLAG | C_FLAG)) |
        (((z80.regs.AF.B.h + val) << 4) & Y_FLAG) | 
        ((z80.regs.AF.B.h + val) & X_FLAG) | (z80.regs.BC.W ? P_FLAG : 0);
}

static void ldir() { 
    ldi(z80);
    if (z80.regs.BC.W != 0) {
        delayBlock(z80); 
        z80.regs.PC.W -= 2; 
    }
}

static void ldd() { 
    UInt8 val = readMem(z80.regs.HL.W--);
    writeMem(z80.regs.DE.W--, val);
    delayLdi(z80);

    z80.regs.BC.W--;
    z80.regs.AF.B.l = (z80.regs.AF.B.l & (S_FLAG | Z_FLAG | C_FLAG)) |
        (((z80.regs.AF.B.h + val) << 4) & Y_FLAG) | 
        ((z80.regs.AF.B.h + val) & X_FLAG) | (z80.regs.BC.W ? P_FLAG : 0);
}

static void lddr() { 
    ldd(z80);
    if (z80.regs.BC.W != 0) {
        delayBlock(z80); 
        z80.regs.PC.W -= 2; 
    }
}

static void ini() {  // Diff on flags
    UInt8  val;
    UInt16 tmp;
    delayInOut(z80);
    z80.regs.BC.B.h--;
    val = readPort(z80.regs.BC.W);
    writeMem(z80.regs.HL.W++, val);
    z80.regs.AF.B.l = (ZSPXYTable[z80.regs.BC.B.h] & (Z_FLAG | S_FLAG)) |
        ((val >> 6) & N_FLAG);
    tmp = val + ((z80.regs.BC.B.l + 1) & 0xFF);
    z80.regs.AF.B.l |= (tmp >> 8) * (H_FLAG | C_FLAG) |
        (ZSPXYTable[(tmp & 0x07) ^ z80.regs.BC.B.h] & P_FLAG);
}

static void inir() { 
    ini(z80);
    if (z80.regs.BC.B.h != 0) {
        delayBlock(z80); 
        z80.regs.PC.W -= 2; 
    }
}


static void ind() {
    UInt8 val;
    UInt16 tmp;
    delayInOut(z80);
    z80.regs.BC.B.h--;
    val = readPort(z80.regs.BC.W);
    writeMem(z80.regs.HL.W--, val);
    z80.regs.AF.B.l = (ZSPXYTable[z80.regs.BC.B.h] & (Z_FLAG | S_FLAG)) | 
        ((val >> 6) & N_FLAG);
    tmp = val + ((z80.regs.BC.B.l - 1) & 0xFF);
    z80.regs.AF.B.l |= (tmp >> 8) * (H_FLAG | C_FLAG) |
        (ZSPXYTable[(tmp & 0x07) ^ z80.regs.BC.B.h] & P_FLAG);
}

static void indr() { 
    ind(z80);
    if (z80.regs.BC.B.h != 0) {
        delayBlock(z80); 
        z80.regs.PC.W -= 2; 
    }
}

static void outi() {
    UInt8  val;
    UInt16 tmp;
    delayInOut(z80);
    val = readMem(z80.regs.HL.W++);
    writePort(z80.regs.BC.W, val);
    z80.regs.BC.B.h--;
    z80.regs.AF.B.l = (ZSXYTable[z80.regs.BC.B.h]) |
        ((val >> 6) & N_FLAG);
    tmp = val + z80.regs.HL.B.l;
    z80.regs.AF.B.l |= (tmp >> 8) * (H_FLAG | C_FLAG) |
        (ZSPXYTable[(tmp & 0x07) ^ z80.regs.BC.B.h] & P_FLAG);
}

static void otir() { 
    outi(z80);
    if (z80.regs.BC.B.h != 0) {
        delayBlock(z80); 
        z80.regs.PC.W -= 2; 
    }
}

static void outd() {
    UInt8 val;
    UInt16 tmp;
    delayInOut(z80);
    val = readMem(z80.regs.HL.W--);
    writePort(z80.regs.BC.W, val);
    z80.regs.BC.B.h--;
    z80.regs.AF.B.l = (ZSXYTable[z80.regs.BC.B.h]) |
        ((val >> 6) & N_FLAG);
    tmp = val + z80.regs.HL.B.l;
    z80.regs.AF.B.l |= (tmp >> 8) * (H_FLAG | C_FLAG) |
        (ZSPXYTable[(tmp & 0x07) ^ z80.regs.BC.B.h] & P_FLAG);
}

static void otdr() { 
    outd(z80);
    if (z80.regs.BC.B.h != 0) {
        delayBlock(z80); 
        z80.regs.PC.W -= 2; 
    }
}

static Opcode opcodeMain[256] = {
    nop,         ld_bc_word,  ld_xbc_a,    inc_bc,      inc_b,       dec_b,       ld_b_byte,   rlca,
    ex_af_af,    add_hl_bc,   ld_a_xbc,    dec_bc,      inc_c,       dec_c,       ld_c_byte,   rrca,
    djnz,        ld_de_word,  ld_xde_a,    inc_de,      inc_d,       dec_d,       ld_d_byte,   rla,
    jr,          add_hl_de,   ld_a_xde,    dec_de,      inc_e,       dec_e,       ld_e_byte,   rra,
    jr_nz,       ld_hl_word,  ld_xword_hl, inc_hl,      inc_h,       dec_h,       ld_h_byte,   daa,
    jr_z,        add_hl_hl,   ld_hl_xword, dec_hl,      inc_l,       dec_l,       ld_l_byte,   cpl,
    jr_nc,       ld_sp_word,  ld_xbyte_a,  inc_sp,      inc_xhl,     dec_xhl,     ld_xhl_byte, scf,
    jr_c,        add_hl_sp,   ld_a_xbyte,  dec_sp,      inc_a,       dec_a,       ld_a_byte,   ccf,
    ld_b_b,      ld_b_c,      ld_b_d,      ld_b_e,      ld_b_h,      ld_b_l,      ld_b_xhl,    ld_b_a,
    ld_c_b,      ld_c_c,      ld_c_d,      ld_c_e,      ld_c_h,      ld_c_l,      ld_c_xhl,    ld_c_a,
    ld_d_b,      ld_d_c,      ld_d_d,      ld_d_e,      ld_d_h,      ld_d_l,      ld_d_xhl,    ld_d_a,
    ld_e_b,      ld_e_c,      ld_e_d,      ld_e_e,      ld_e_h,      ld_e_l,      ld_e_xhl,    ld_e_a,
    ld_h_b,      ld_h_c,      ld_h_d,      ld_h_e,      ld_h_h,      ld_h_l,      ld_h_xhl,    ld_h_a,
    ld_l_b,      ld_l_c,      ld_l_d,      ld_l_e,      ld_l_h,      ld_l_l,      ld_l_xhl,    ld_l_a,
    ld_xhl_b,    ld_xhl_c,    ld_xhl_d,    ld_xhl_e,    ld_xhl_h,    ld_xhl_l,    halt,        ld_xhl_a,
    ld_a_b,      ld_a_c,      ld_a_d,      ld_a_e,      ld_a_h,      ld_a_l,      ld_a_xhl,    ld_a_a,
    add_a_b,     add_a_c,     add_a_d,     add_a_e,     add_a_h,     add_a_l,     add_a_xhl,   add_a_a,
    adc_a_b,     adc_a_c,     adc_a_d,     adc_a_e,     adc_a_h,     adc_a_l,     adc_a_xhl,   adc_a_a,
    sub_b,       sub_c,       sub_d,       sub_e,       sub_h,       sub_l,       sub_xhl,     sub_a,
    sbc_a_b,     sbc_a_c,     sbc_a_d,     sbc_a_e,     sbc_a_h,     sbc_a_l,     sbc_a_xhl,   sbc_a_a,
    and_b,       and_c,       and_d,       and_e,       and_h,       and_l,       and_xhl,     and_a,
    xor_b,       xor_c,       xor_d,       xor_e,       xor_h,       xor_l,       xor_xhl,     xor_a,
    or_b,        or_c,        or_d,        or_e,        or_h,        or_l,        or_xhl,      or_a,
    cp_b,        cp_c,        cp_d,        cp_e,        cp_h,        cp_l,        cp_xhl,      cp_a,
    ret_nz,      pop_bc,      jp_nz,       jp,          call_nz,     push_bc,     add_a_byte,  rst_00,
    ret_z,       ret,         jp_z,        cb,          call_z,      call,        adc_a_byte,  rst_08,
    ret_nc,      pop_de,      jp_nc,       out_byte_a,  call_nc,     push_de,     sub_byte,    rst_10,
    ret_c,       exx,         jp_c,        in_a_byte,   call_c,      dd,          sbc_a_byte,  rst_18,
    ret_po,      pop_hl,      jp_po,       ex_xsp_hl,   call_po,     push_hl,     and_byte,    rst_20,
    ret_pe,      jp_hl,       jp_pe,       ex_de_hl,    call_pe,     ed,          xor_byte,    rst_28,
    ret_p,       pop_af,      jp_p,        di,          call_p,      push_af,     or_byte,     rst_30,
    ret_m,       ld_sp_hl,    jp_m,        ei,          call_m,      fd,          cp_byte,     rst_38
};

static Opcode opcodeCb[256] = {
    rlc_b,       rlc_c,       rlc_d,       rlc_e,       rlc_h,       rlc_l,       rlc_xhl,     rlc_a,
    rrc_b,       rrc_c,       rrc_d,       rrc_e,       rrc_h,       rrc_l,       rrc_xhl,     rrc_a,
    rl_b,        rl_c,        rl_d,        rl_e,        rl_h,        rl_l,        rl_xhl,      rl_a ,
    rr_b,        rr_c,        rr_d,        rr_e,        rr_h,        rr_l,        rr_xhl,      rr_a ,
    sla_b,       sla_c,       sla_d,       sla_e,       sla_h,       sla_l,       sla_xhl,     sla_a,
    sra_b,       sra_c,       sra_d,       sra_e,       sra_h,       sra_l,       sra_xhl,     sra_a,
    sll_b,       sll_c,       sll_d,       sll_e,       sll_h,       sll_l,       sll_xhl,     sll_a,
    srl_b,       srl_c,       srl_d,       srl_e,       srl_h,       srl_l,       srl_xhl,     srl_a,
    bit_0_b,     bit_0_c,     bit_0_d,     bit_0_e,     bit_0_h,     bit_0_l,     bit_0_xhl,   bit_0_a,
    bit_1_b,     bit_1_c,     bit_1_d,     bit_1_e,     bit_1_h,     bit_1_l,     bit_1_xhl,   bit_1_a,
    bit_2_b,     bit_2_c,     bit_2_d,     bit_2_e,     bit_2_h,     bit_2_l,     bit_2_xhl,   bit_2_a,
    bit_3_b,     bit_3_c,     bit_3_d,     bit_3_e,     bit_3_h,     bit_3_l,     bit_3_xhl,   bit_3_a,
    bit_4_b,     bit_4_c,     bit_4_d,     bit_4_e,     bit_4_h,     bit_4_l,     bit_4_xhl,   bit_4_a,
    bit_5_b,     bit_5_c,     bit_5_d,     bit_5_e,     bit_5_h,     bit_5_l,     bit_5_xhl,   bit_5_a,
    bit_6_b,     bit_6_c,     bit_6_d,     bit_6_e,     bit_6_h,     bit_6_l,     bit_6_xhl,   bit_6_a,
    bit_7_b,     bit_7_c,     bit_7_d,     bit_7_e,     bit_7_h,     bit_7_l,     bit_7_xhl,   bit_7_a,
    res_0_b,     res_0_c,     res_0_d,     res_0_e,     res_0_h,     res_0_l,     res_0_xhl,   res_0_a,
    res_1_b,     res_1_c,     res_1_d,     res_1_e,     res_1_h,     res_1_l,     res_1_xhl,   res_1_a,
    res_2_b,     res_2_c,     res_2_d,     res_2_e,     res_2_h,     res_2_l,     res_2_xhl,   res_2_a,
    res_3_b,     res_3_c,     res_3_d,     res_3_e,     res_3_h,     res_3_l,     res_3_xhl,   res_3_a,
    res_4_b,     res_4_c,     res_4_d,     res_4_e,     res_4_h,     res_4_l,     res_4_xhl,   res_4_a,
    res_5_b,     res_5_c,     res_5_d,     res_5_e,     res_5_h,     res_5_l,     res_5_xhl,   res_5_a,
    res_6_b,     res_6_c,     res_6_d,     res_6_e,     res_6_h,     res_6_l,     res_6_xhl,   res_6_a,
    res_7_b,     res_7_c,     res_7_d,     res_7_e,     res_7_h,     res_7_l,     res_7_xhl,   res_7_a,
    set_0_b,     set_0_c,     set_0_d,     set_0_e,     set_0_h,     set_0_l,     set_0_xhl,   set_0_a,
    set_1_b,     set_1_c,     set_1_d,     set_1_e,     set_1_h,     set_1_l,     set_1_xhl,   set_1_a,
    set_2_b,     set_2_c,     set_2_d,     set_2_e,     set_2_h,     set_2_l,     set_2_xhl,   set_2_a,
    set_3_b,     set_3_c,     set_3_d,     set_3_e,     set_3_h,     set_3_l,     set_3_xhl,   set_3_a,
    set_4_b,     set_4_c,     set_4_d,     set_4_e,     set_4_h,     set_4_l,     set_4_xhl,   set_4_a,
    set_5_b,     set_5_c,     set_5_d,     set_5_e,     set_5_h,     set_5_l,     set_5_xhl,   set_5_a,
    set_6_b,     set_6_c,     set_6_d,     set_6_e,     set_6_h,     set_6_l,     set_6_xhl,   set_6_a,
    set_7_b,     set_7_c,     set_7_d,     set_7_e,     set_7_h,     set_7_l,     set_7_xhl,   set_7_a
};

static Opcode opcodeDd[256] = {
    nop,         ld_bc_word,  ld_xbc_a,    inc_bc,      inc_b,       dec_b,       ld_b_byte,   rlca,
    ex_af_af,    add_ix_bc,   ld_a_xbc,    dec_bc,      inc_c,       dec_c,       ld_c_byte,   rrca,
    djnz,        ld_de_word,  ld_xde_a,    inc_de,      inc_d,       dec_d,       ld_d_byte,   rla,
    jr,          add_ix_de,   ld_a_xde,    dec_de,      inc_e,       dec_e,       ld_e_byte,   rra,
    jr_nz,       ld_ix_word,  ld_xword_ix, inc_ix,      inc_ixh,     dec_ixh,     ld_ixh_byte, daa,
    jr_z,        add_ix_ix,   ld_ix_xword, dec_ix,      inc_ixl,     dec_ixl,     ld_ixl_byte, cpl,
    jr_nc,       ld_sp_word,  ld_xbyte_a,  inc_sp,      inc_xix,     dec_xix,     ld_xix_byte, scf,
    jr_c,        add_ix_sp,   ld_a_xbyte,  dec_sp,      inc_a,       dec_a,       ld_a_byte,   ccf,
    ld_b_b,      ld_b_c,      ld_b_d,      ld_b_e,      ld_b_ixh,    ld_b_ixl,    ld_b_xix,    ld_b_a,
    ld_c_b,      ld_c_c,      ld_c_d,      ld_c_e,      ld_c_ixh,    ld_c_ixl,    ld_c_xix,    ld_c_a,
    ld_d_b,      ld_d_c,      ld_d_d,      ld_d_e,      ld_d_ixh,    ld_d_ixl,    ld_d_xix,    ld_d_a,
    ld_e_b,      ld_e_c,      ld_e_d,      ld_e_e,      ld_e_ixh,    ld_e_ixl,    ld_e_xix,    ld_e_a,
    ld_ixh_b,    ld_ixh_c,    ld_ixh_d,    ld_ixh_e,    ld_ixh_ixh,  ld_ixh_ixl,  ld_h_xix,    ld_ixh_a,
    ld_ixl_b,    ld_ixl_c,    ld_ixl_d,    ld_ixl_e,    ld_ixl_ixh,  ld_ixl_ixl,  ld_l_xix,    ld_ixl_a,
    ld_xix_b,    ld_xix_c,    ld_xix_d,    ld_xix_e,    ld_xix_h,    ld_xix_l,    halt,        ld_xix_a,
    ld_a_b,      ld_a_c,      ld_a_d,      ld_a_e,      ld_a_ixh,    ld_a_ixl,    ld_a_xix,    ld_a_a,
    add_a_b,     add_a_c,     add_a_d,     add_a_e,     add_a_ixh,   add_a_ixl,   add_a_xix,   add_a_a,
    adc_a_b,     adc_a_c,     adc_a_d,     adc_a_e,     adc_a_ixh,   adc_a_ixl,   adc_a_xix,   adc_a_a,
    sub_b,       sub_c,       sub_d,       sub_e,       sub_ixh,     sub_ixl,     sub_xix,     sub_a,
    sbc_a_b,     sbc_a_c,     sbc_a_d,     sbc_a_e,     sbc_a_ixh,   sbc_a_ixl,   sbc_a_xix,   sbc_a_a,
    and_b,       and_c,       and_d,       and_e,       and_ixh,     and_ixl,     and_xix,     and_a,
    xor_b,       xor_c,       xor_d,       xor_e,       xor_ixh,     xor_ixl,     xor_xix,     xor_a,
    or_b,        or_c,        or_d,        or_e,        or_ixh,      or_ixl,      or_xix,      or_a,
    cp_b,        cp_c,        cp_d,        cp_e,        cp_ixh,      cp_ixl,      cp_xix,      cp_a,
    ret_nz,      pop_bc,      jp_nz,       jp,          call_nz,     push_bc,     add_a_byte,  rst_00,
    ret_z,       ret,         jp_z,        dd_cb,       call_z,      call,        adc_a_byte,  rst_08,
    ret_nc,      pop_de,      jp_nc,       out_byte_a,  call_nc,     push_de,     sub_byte,    rst_10,
    ret_c,       exx,         jp_c,        in_a_byte,   call_c,      dd,          sbc_a_byte,  rst_18,
    ret_po,      pop_ix,      jp_po,       ex_xsp_ix,   call_po,     push_ix,     and_byte,    rst_20,
    ret_pe,      jp_ix,       jp_pe,       ex_de_hl,    call_pe,     ed,          xor_byte,    rst_28,
    ret_p,       pop_af,      jp_p,        di,          call_p,      push_af,     or_byte,     rst_30,
    ret_m,       ld_sp_ix,    jp_m,        ei,          call_m,      fd,          cp_byte,     rst_38  
};

static Opcode opcodeEd[256] = {
    nop,         nop,         nop,         nop,         nop,         nop,         nop,         nop,
    nop,         nop,         nop,         nop,         nop,         nop,         nop,         nop,
    nop,         nop,         nop,         nop,         nop,         nop,         nop,         nop,
    nop,         nop,         nop,         nop,         nop,         nop,         nop,         nop,
    nop,         nop,         nop,         nop,         nop,         nop,         nop,         nop,
    nop,         nop,         nop,         nop,         nop,         nop,         nop,         nop,
    nop,         nop,         nop,         nop,         nop,         nop,         nop,         nop,
    nop,         nop,         nop,         nop,         nop,         nop,         nop,         nop,
    in_b_c,      out_c_b,     sbc_hl_bc,   ld_xword_bc, neg,         retn,        im_0,        ld_i_a,
    in_c_c,      out_c_c,     adc_hl_bc,   ld_bc_xword, neg,         reti,        im_0,        ld_r_a,
    in_d_c,      out_c_d,     sbc_hl_de,   ld_xword_de, neg,         retn,        im_1,        ld_a_i,
    in_e_c,      out_c_e,     adc_hl_de,   ld_de_xword, neg,         retn,        im_2,        ld_a_r,
    in_h_c,      out_c_h,     sbc_hl_hl,   ld_xword_hl, neg,         retn,        im_0,        rrd,
    in_l_c,      out_c_l,     adc_hl_hl,   ld_hl_xword, neg,         retn,        im_0,        rld,
    in_0_c,      out_c_0,     sbc_hl_sp,   ld_xword_sp, neg,         retn,        im_1,        nop,
    in_a_c,      out_c_a,     adc_hl_sp,   ld_sp_xword, neg,         retn,        im_2,        nop,
    nop,         nop,         nop,         nop,         nop,         nop,         nop,         nop,
    nop,         nop,         nop,         nop,         nop,         nop,         nop,         nop,
    nop,         nop,         nop,         nop,         nop,         nop,         nop,         nop,
    nop,         nop,         nop,         nop,         nop,         nop,         nop,         nop,
    ldi,         cpi,         ini,         outi,        nop,         nop,         nop,         nop,
    ldd,         cpd,         ind,         outd,        nop,         nop,         nop,         nop,
    ldir,        cpir,        inir,        otir,        nop,         nop,         nop,         nop,
    lddr,        cpdr,        indr,        otdr,        nop,         nop,         nop,         nop,
    nop,         mulu_b,      nop,         muluw_bc,    nop,         nop,         nop,         nop,
    nop,         mulu_c,      nop,         nop,         nop,         nop,         nop,         nop,
    nop,         mulu_d,      nop,         muluw_de,    nop,         nop,         nop,         nop,
    nop,         mulu_e,      nop,         nop,         nop,         nop,         nop,         nop,
    nop,         mulu_h,      nop,         muluw_hl,    nop,         nop,         nop,         nop,
    nop,         mulu_l,      nop,         nop,         nop,         nop,         nop,         nop,
    nop,         mulu_xhl,    nop,         muluw_sp,    nop,         nop,         nop,         nop,
    nop,         mulu_a,      nop,         nop,         nop,         nop,         patch,       nop
};

static Opcode opcodeFd[256] = {
    nop,         ld_bc_word,ld_xbc_a,      inc_bc,      inc_b,       dec_b,       ld_b_byte,   rlca,
    ex_af_af,    add_iy_bc,   ld_a_xbc,    dec_bc,      inc_c,       dec_c,       ld_c_byte,   rrca,
    djnz,        ld_de_word,  ld_xde_a,    inc_de,      inc_d,       dec_d,       ld_d_byte,   rla,
    jr,          add_iy_de,   ld_a_xde,    dec_de,      inc_e,       dec_e,       ld_e_byte,   rra,
    jr_nz,       ld_iy_word,  ld_xword_iy, inc_iy,      inc_iyh,     dec_iyh,     ld_iyh_byte, daa,
    jr_z,        add_iy_iy,   ld_iy_xword, dec_iy,      inc_iyl,     dec_iyl,     ld_iyl_byte, cpl,
    jr_nc,       ld_sp_word,  ld_xbyte_a,  inc_sp,      inc_xiy,     dec_xiy,     ld_xiy_byte, scf,
    jr_c,        add_iy_sp,   ld_a_xbyte,  dec_sp,      inc_a,       dec_a,       ld_a_byte,   ccf,
    ld_b_b,      ld_b_c,      ld_b_d,      ld_b_e,      ld_b_iyh,    ld_b_iyl,    ld_b_xiy,    ld_b_a,
    ld_c_b,      ld_c_c,      ld_c_d,      ld_c_e,      ld_c_iyh,    ld_c_iyl,    ld_c_xiy,    ld_c_a,
    ld_d_b,      ld_d_c,      ld_d_d,      ld_d_e,      ld_d_iyh,    ld_d_iyl,    ld_d_xiy,    ld_d_a,
    ld_e_b,      ld_e_c,      ld_e_d,      ld_e_e,      ld_e_iyh,    ld_e_iyl,    ld_e_xiy,    ld_e_a,
    ld_iyh_b,    ld_iyh_c,    ld_iyh_d,    ld_iyh_e,    ld_iyh_iyh,  ld_iyh_iyl,  ld_h_xiy,    ld_iyh_a,
    ld_iyl_b,    ld_iyl_c,    ld_iyl_d,    ld_iyl_e,    ld_iyl_iyh,  ld_iyl_iyl,  ld_l_xiy,    ld_iyl_a,
    ld_xiy_b,    ld_xiy_c,    ld_xiy_d,    ld_xiy_e,    ld_xiy_h,    ld_xiy_l,    halt,        ld_xiy_a,
    ld_a_b,      ld_a_c,      ld_a_d,      ld_a_e,      ld_a_iyh,    ld_a_iyl,    ld_a_xiy,    ld_a_a,
    add_a_b,     add_a_c,     add_a_d,     add_a_e,     add_a_iyh,   add_a_iyl,   add_a_xiy,   add_a_a,
    adc_a_b,     adc_a_c,     adc_a_d,     adc_a_e,     adc_a_iyh,   adc_a_iyl,   adc_a_xiy,   adc_a_a,
    sub_b,       sub_c,       sub_d,       sub_e,       sub_iyh,     sub_iyl,     sub_xiy,     sub_a,
    sbc_a_b,     sbc_a_c,     sbc_a_d,     sbc_a_e,     sbc_a_iyh,   sbc_a_iyl,   sbc_a_xiy,   sbc_a_a,
    and_b,       and_c,       and_d,       and_e,       and_iyh,     and_iyl,     and_xiy,     and_a,
    xor_b,       xor_c,       xor_d,       xor_e,       xor_iyh,     xor_iyl,     xor_xiy,     xor_a,
    or_b,        or_c,        or_d,        or_e,        or_iyh,      or_iyl,      or_xiy,      or_a,
    cp_b,        cp_c,        cp_d,        cp_e,        cp_iyh,      cp_iyl,      cp_xiy,      cp_a,
    ret_nz,      pop_bc,      jp_nz,       jp,          call_nz,     push_bc,     add_a_byte,  rst_00,
    ret_z,       ret,         jp_z,        fd_cb,       call_z,      call,        adc_a_byte,  rst_08,
    ret_nc,      pop_de,      jp_nc,       out_byte_a,  call_nc,     push_de,     sub_byte,    rst_10,
    ret_c,       exx,         jp_c,        in_a_byte,   call_c,      dd,          sbc_a_byte,  rst_18,
    ret_po,      pop_iy,      jp_po,       ex_xsp_iy,   call_po,     push_iy,     and_byte,    rst_20,
    ret_pe,      jp_iy,       jp_pe,       ex_de_hl,    call_pe,     ed,          xor_byte,    rst_28,
    ret_p,       pop_af,      jp_p,        di,          call_p,      push_af,     or_byte,     rst_30,
    ret_m,       ld_sp_iy,    jp_m,        ei,          call_m,      fd,          cp_byte,     rst_38  
};

static OpcodeNn opcodeNnCb[256] = {
    rlc_xnn_b,   rlc_xnn_c,   rlc_xnn_d,   rlc_xnn_e,   rlc_xnn_h,   rlc_xnn_l,   rlc_xnn,     rlc_xnn_a,
    rrc_xnn_b,   rrc_xnn_c,   rrc_xnn_d,   rrc_xnn_e,   rrc_xnn_h,   rrc_xnn_l,   rrc_xnn,     rrc_xnn_a,
    rl_xnn_b,    rl_xnn_c,    rl_xnn_d,    rl_xnn_e,    rl_xnn_h,    rl_xnn_l,    rl_xnn,      rl_xnn_a,
    rr_xnn_b,    rr_xnn_c,    rr_xnn_d,    rr_xnn_e,    rr_xnn_h,    rr_xnn_l,    rr_xnn,      rr_xnn_a,
    sla_xnn_b,   sla_xnn_c,   sla_xnn_d,   sla_xnn_e,   sla_xnn_h,   sla_xnn_l,   sla_xnn,     sla_xnn_a,   
    sra_xnn_b,   sra_xnn_c,   sra_xnn_d,   sra_xnn_e,   sra_xnn_h,   sra_xnn_l,   sra_xnn,     sra_xnn_a,
    sll_xnn_b,   sll_xnn_c,   sll_xnn_d,   sll_xnn_e,   sll_xnn_h,   sll_xnn_l,   sll_xnn,     sll_xnn_a,
    srl_xnn_b,   srl_xnn_c,   srl_xnn_d,   srl_xnn_e,   srl_xnn_h,   srl_xnn_l,   srl_xnn,     srl_xnn_a,
    bit_0_xnn,   bit_0_xnn,   bit_0_xnn,   bit_0_xnn,   bit_0_xnn,   bit_0_xnn,   bit_0_xnn,   bit_0_xnn,   
    bit_1_xnn,   bit_1_xnn,   bit_1_xnn,   bit_1_xnn,   bit_1_xnn,   bit_1_xnn,   bit_1_xnn,   bit_1_xnn,   
    bit_2_xnn,   bit_2_xnn,   bit_2_xnn,   bit_2_xnn,   bit_2_xnn,   bit_2_xnn,   bit_2_xnn,   bit_2_xnn,   
    bit_3_xnn,   bit_3_xnn,   bit_3_xnn,   bit_3_xnn,   bit_3_xnn,   bit_3_xnn,   bit_3_xnn,   bit_3_xnn,   
    bit_4_xnn,   bit_4_xnn,   bit_4_xnn,   bit_4_xnn,   bit_4_xnn,   bit_4_xnn,   bit_4_xnn,   bit_4_xnn,   
    bit_5_xnn,   bit_5_xnn,   bit_5_xnn,   bit_5_xnn,   bit_5_xnn,   bit_5_xnn,   bit_5_xnn,   bit_5_xnn,   
    bit_6_xnn,   bit_6_xnn,   bit_6_xnn,   bit_6_xnn,   bit_6_xnn,   bit_6_xnn,   bit_6_xnn,   bit_6_xnn,   
    bit_7_xnn,   bit_7_xnn,   bit_7_xnn,   bit_7_xnn,   bit_7_xnn,   bit_7_xnn,   bit_7_xnn,   bit_7_xnn,   
    res_0_xnn_b, res_0_xnn_c, res_0_xnn_d, res_0_xnn_e, res_0_xnn_h, res_0_xnn_l, res_0_xnn,   res_0_xnn_a,
    res_1_xnn_b, res_1_xnn_c, res_1_xnn_d, res_1_xnn_e, res_1_xnn_h, res_1_xnn_l, res_1_xnn,   res_1_xnn_a,
    res_2_xnn_b, res_2_xnn_c, res_2_xnn_d, res_2_xnn_e, res_2_xnn_h, res_2_xnn_l, res_2_xnn,   res_2_xnn_a,
    res_3_xnn_b, res_3_xnn_c, res_3_xnn_d, res_3_xnn_e, res_3_xnn_h, res_3_xnn_l, res_3_xnn,   res_3_xnn_a,
    res_4_xnn_b, res_4_xnn_c, res_4_xnn_d, res_4_xnn_e, res_4_xnn_h, res_4_xnn_l, res_4_xnn,   res_4_xnn_a,
    res_5_xnn_b, res_5_xnn_c, res_5_xnn_d, res_5_xnn_e, res_5_xnn_h, res_5_xnn_l, res_5_xnn,   res_5_xnn_a,
    res_6_xnn_b, res_6_xnn_c, res_6_xnn_d, res_6_xnn_e, res_6_xnn_h, res_6_xnn_l, res_6_xnn,   res_6_xnn_a,
    res_7_xnn_b, res_7_xnn_c, res_7_xnn_d, res_7_xnn_e, res_7_xnn_h, res_7_xnn_l, res_7_xnn,   res_7_xnn_a,
    set_0_xnn_b, set_0_xnn_c, set_0_xnn_d, set_0_xnn_e, set_0_xnn_h, set_0_xnn_l, set_0_xnn,   set_0_xnn_a,
    set_1_xnn_b, set_1_xnn_c, set_1_xnn_d, set_1_xnn_e, set_1_xnn_h, set_1_xnn_l, set_1_xnn,   set_1_xnn_a,
    set_2_xnn_b, set_2_xnn_c, set_2_xnn_d, set_2_xnn_e, set_2_xnn_h, set_2_xnn_l, set_2_xnn,   set_2_xnn_a,
    set_3_xnn_b, set_3_xnn_c, set_3_xnn_d, set_3_xnn_e, set_3_xnn_h, set_3_xnn_l, set_3_xnn,   set_3_xnn_a,
    set_4_xnn_b, set_4_xnn_c, set_4_xnn_d, set_4_xnn_e, set_4_xnn_h, set_4_xnn_l, set_4_xnn,   set_4_xnn_a,
    set_5_xnn_b, set_5_xnn_c, set_5_xnn_d, set_5_xnn_e, set_5_xnn_h, set_5_xnn_l, set_5_xnn,   set_5_xnn_a,
    set_6_xnn_b, set_6_xnn_c, set_6_xnn_d, set_6_xnn_e, set_6_xnn_h, set_6_xnn_l, set_6_xnn,   set_6_xnn_a,
    set_7_xnn_b, set_7_xnn_c, set_7_xnn_d, set_7_xnn_e, set_7_xnn_h, set_7_xnn_l, set_7_xnn,   set_7_xnn_a,
};

static void dd_cb() {
	UInt16 addr = z80.regs.IX.W + (Int8)readOpcode(z80.regs.PC.W++);
    int opcode = readOpcode(z80.regs.PC.W++);
	delayM1(z80);
    opcodeNnCb[opcode](addr);
}

static void fd_cb() {
	UInt16 addr = z80.regs.IY.W + (Int8)readOpcode(z80.regs.PC.W++);
    int opcode = readOpcode(z80.regs.PC.W++);
	delayM1(z80);
    opcodeNnCb[opcode](addr);
}

static void cb() {
    int opcode = readOpcode(z80.regs.PC.W++);
    M1(z80);
    opcodeCb[opcode](z80);
}

static void dd() {
    int opcode = readOpcode(z80.regs.PC.W++);
    M1(z80);
    opcodeDd[opcode](z80);
}

static void ed() {
    int opcode = readOpcode(z80.regs.PC.W++);
    M1(z80);
    opcodeEd[opcode](z80);
}

static void fd() {
    int opcode = readOpcode(z80.regs.PC.W++);
    M1(z80);
    opcodeFd[opcode](z80);
}

static void executeInstruction(UInt8 opcode) {
    M1(z80);
    opcodeMain[opcode](z80);
}


static void z80InitTables() {
    int i;

	for (i = 0; i < 256; ++i) {
        UInt8 flags = i ^ 1;
        flags = flags ^ (flags >> 4);
        flags = flags ^ (flags << 2);
        flags = flags ^ (flags >> 1);
        flags = (flags & V_FLAG) | H_FLAG | (i & (S_FLAG | X_FLAG | Y_FLAG)) |
                (i ? 0 : Z_FLAG);

        ZSXYTable[i]  = flags & (Z_FLAG | S_FLAG | X_FLAG | Y_FLAG);
		ZSPXYTable[i] = flags & (Z_FLAG | S_FLAG | X_FLAG | Y_FLAG | V_FLAG);
		ZSPHTable[i]  = flags & (Z_FLAG | S_FLAG | V_FLAG | H_FLAG);
	}

    for (i = 0; i < 0x800; ++i) {
		int flagC = i & 0x100;
		int flagN = i & 0x200;
		int flagH = i & 0x400;
		UInt8 a = i & 0xff;
		UInt8 hi = a / 16;
		UInt8 lo = a & 15;
		UInt8 diff;
        UInt8 regA;

		if (flagC) {
			diff = ((lo <= 9) && !flagH) ? 0x60 : 0x66;
		} 
        else {
			if (lo >= 10) {
				diff = (hi <= 8) ? 0x06 : 0x66;
			} 
            else {
				if (hi >= 10) {
					diff = flagH ? 0x66 : 0x60;
				} 
                else {
					diff = flagH ? 0x06 : 0x00;
				}
			}
		}
		regA = flagN ? a - diff : a + diff;
		DAATable[i] = (regA << 8) |
                      ZSPXYTable[regA] | 
                      (flagN ? N_FLAG : 0) |
                      (flagC || (lo <= 9 ? hi >= 10 : hi >= 9) ? C_FLAG : 0) |
                      ((flagN ? (flagH && lo <= 5) : lo >= 10) ? H_FLAG : 0);
	}
}

void z80Init()
{
    z80InitTables();

    z80.terminate   = 0;
    z80.systemTime  = 0;

    z80Reset(0);
}

UInt32 z80GetSystemTime() {
    return z80.systemTime;
}

void z80Reset(UInt32 cpuTime) {

    z80.regs.AF.W       = 0xffff;
	z80.regs.BC.W       = 0xffff;
	z80.regs.DE.W       = 0xffff;
	z80.regs.HL.W       = 0xffff;
	z80.regs.IX.W       = 0xffff;
	z80.regs.IY.W       = 0xffff;
	z80.regs.SP.W       = 0xffff;
	z80.regs.AF1.W      = 0xffff;
	z80.regs.BC1.W      = 0xffff;
	z80.regs.DE1.W      = 0xffff;
	z80.regs.HL1.W      = 0xffff;
    z80.regs.SH.W       = 0xffff;
	z80.regs.I          = 0x00;
	z80.regs.R          = 0x00;
	z80.regs.R2         = 0;
	z80.regs.PC.W       = 0x0000;

    z80.regs.iff1       = 0;
    z80.regs.iff2       = 0;
    z80.regs.im         = 0;
    z80.regs.halt       = 0;
    z80.regs.ei_mode    = 0;
    z80.dataBus         = 0xff;
    z80.defaultDatabus  = 0xff;
    z80.intState        = INT_HIGH;
    z80.nmiState        = INT_HIGH;
}

void z80SetDataBus(UInt8 value, UInt8 defaultValue, int setDefault) {
    z80.dataBus = value;
    if (setDefault) {
        z80.defaultDatabus = defaultValue;
    }
}

void z80SetInt() {
    z80.intState = INT_LOW;
}

void z80ClearInt() {
    z80.intState = INT_HIGH;
}

void z80SetNmi() {
    if (z80.nmiState == INT_HIGH) {
        z80.nmiState = INT_EDGE;
    }
}

void z80ClearNmi() {
    z80.nmiState = INT_HIGH;
}

void z80StopExecution() {
    z80.terminate = 1;
}

void z80SetTimeout(SystemTime time)
{
    z80.timeout = time;
}


void z80Execute() {
    while (!z80.terminate) {
        UInt16 address;
        int iff1 = 0;

        if ((Int32)(z80.timeout - z80.systemTime) <= 0) {
            timeout();
        }

        executeInstruction(readOpcode(z80.regs.PC.W++));

        if (z80.regs.halt) {
			continue;
        }

		if (z80.regs.ei_mode) {
			z80.regs.ei_mode=0;
			continue;
		}

        if (! ((z80.intState==INT_LOW && z80.regs.iff1)||(z80.nmiState==INT_EDGE)) ) {
			continue;
        }

        /* If it is NMI... */

        if (z80.nmiState == INT_EDGE) {
            z80.nmiState = INT_LOW;
	        writeMemory(--z80.regs.SP.W, z80.regs.PC.B.h);
	        writeMemory(--z80.regs.SP.W, z80.regs.PC.B.l);
            z80.regs.iff1 = 0;
            z80.regs.PC.W = 0x0066;
            M1(z80);
            delayNmi(z80);
            continue;
        }

        z80.regs.iff1 = 0;
        z80.regs.iff2 = 0;

        switch (z80.regs.im) {

        case 0:
            delayIm(z80);
            address = z80.dataBus;
            z80.dataBus = z80.defaultDatabus;
            executeInstruction((UInt8)address);
            break;

        case 1:
            delayIm(z80);
            executeInstruction(0xff);
            break;

        case 2:
            address = z80.dataBus | ((Int16)z80.regs.I << 8);
            z80.dataBus = z80.defaultDatabus;
	        writeMemory(--z80.regs.SP.W, z80.regs.PC.B.h);
	        writeMemory(--z80.regs.SP.W, z80.regs.PC.B.l);
            z80.regs.PC.B.l = readMemory(address++);
            z80.regs.PC.B.h = readMemory(address);
            M1(z80);
            delayIm2(z80);
            break;
        }
    }
}
