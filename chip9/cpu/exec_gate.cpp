//
//  instr_exec.cpp
//  CHIP9
//
//  Created by Matteo Zoia on 07/01/2020.
//  Copyright © 2020 Matteo Zoia. All rights reserved.
//

#include <stdio.h>
#include "Instruction.cpp"
#pragma once

static void hcf(Instruction *i){
    printf("PANIC!!! Your machine is catching fire.\n");
    exit(0);
}

static void ldi(Instruction *i){
    i->get_r1()->set(i->get_imm8_0());
}

static void ldiHL(Instruction *i){
    uint16_t addr = getD(i->get_rr1());
    i->get_mem()->writeb(addr, i->get_imm8_0());
}

static void ldx(Instruction *i){
    i->get_rr1()->set(i->get_imm8_1(), i->get_imm8_0());
}

static void pushr(Instruction *i){
    uint8_t byte = i->get_r1()->getValue();
    uint16_t sp_v = getD(i->get_rr1());
    i->get_mem()->writeb(sp_v, byte);
    setD(i->get_rr1(), sp_v - 2);
}

static void pushHL(Instruction *i){
    uint8_t byte = i->get_mem()->readb(getD(i->get_rr1()));
    uint16_t sp_v = getD(i->get_rr2());
    i->get_mem()->writeb(sp_v, byte);
    setD(i->get_rr2(), sp_v - 2);
}

static void pushrr(Instruction *i){
    uint16_t word = getD(i->get_rr1());
    uint16_t sp_v = getD(i->get_rr2());
    i->get_mem()->writew(sp_v, word);
    setD(i->get_rr2(), sp_v - 2);
}

static void popr(Instruction *i){
    uint16_t sp_v = getD(i->get_rr1()) + 2;
    setD(i->get_rr1(), sp_v);
    i->get_r1()->set(i->get_mem()->readb(sp_v));
}

static void popHL(Instruction *i){
    uint16_t sp_v = getD(i->get_rr2()) + 2;
    uint16_t hl_v = getD(i->get_rr1());
    setD(i->get_rr2(), sp_v);
    i->get_mem()->writeb(hl_v, i->get_mem()->readb(sp_v));
}

static void poprr(Instruction *i){
    uint16_t sp_v = getD(i->get_rr2()) + 2;
    setD(i->get_rr2(), sp_v);
    setD(i->get_rr1(), i->get_mem()->readw(sp_v));
}

static void mov(Instruction *i){
    i->get_r1()->set(i->get_r2()->getValue());
}

static void mov_HL(Instruction *i){
    uint8_t v = i->get_mem()->readb(getD(i->get_rr1()));
    i->get_r1()->set(v);
}

static void movHL_(Instruction *i){
    uint16_t addrHL = getD(i->get_rr1());
    i->get_mem()->writeb(addrHL, i->get_r1()->getValue());
}

static void movrr(Instruction *i){
    i->get_rr1()->set(i->get_rr2()->getHigh(), i->get_rr2()->getLow());
}

static void clrflag(Instruction *i){
    i->get_flag()->set(0);
}

static void setflag_z1(Instruction *i){
    uint8_t mask = 0x80; // 1000 0000
    i->get_flag()->set(i->get_flag()->getValue() | mask);
}

static void setflag_z0(Instruction *i){
    uint8_t mask = 0x7F; // 0111 1111
    i->get_flag()->set(i->get_flag()->getValue() & mask);
}

static void setflag_n1(Instruction *i){
    uint8_t mask = 0x40; // 0100 0000
    i->get_flag()->set(i->get_flag()->getValue() | mask);
}

static void setflag_n0(Instruction *i){
    uint8_t mask = 0xBF; // 1011 1111
    i->get_flag()->set(i->get_flag()->getValue() & mask);
}

static void setflag_h1(Instruction *i){
    uint8_t mask = 0x20; // 0010 0000
    i->get_flag()->set(i->get_flag()->getValue() | mask);
}

static void setflag_h0(Instruction *i){
    uint8_t mask = 0xDF; // 1101 1111
    i->get_flag()->set(i->get_flag()->getValue() & mask);
}

static void setflag_c1(Instruction *i){
    uint8_t mask = 0x10; // 0001 0000
    i->get_flag()->set(i->get_flag()->getValue() | mask);
}

static void setflag_c0(Instruction *i){
    uint8_t mask = 0xEF; // 1110 1111
    i->get_flag()->set(i->get_flag()->getValue() & mask);
}

// Util fuction
static void setflag_math(Instruction *i, uint16_t res){

    if(res == 0) // res == 0
        setflag_z1(i);
    else
        setflag_z0(i);

    if(((res >> 7) & 0x01FF) != 0) {
        setflag_n1(i);
    }else {
        setflag_n0(i);
    }

    if(((res >> 4) & 0x0FFF) != 0)
        setflag_h1(i);
    else
        setflag_h0(i);

    if(((res >> 8) & 0xFF) != 0)
        setflag_c1(i);
    else
        setflag_c0(i);
}

static void add(Instruction *i){
    uint16_t res = ((uint16_t)i->get_r2()->getValue()) + i->get_r1()->getValue();
    i->get_r2()->set((uint8_t)res);
    
    setflag_math(i, res);
}

static void addHL(Instruction *i){
    uint16_t addr = getD(i->get_rr1());
    uint16_t res = i->get_r1()->getValue() + i->get_mem()->readb(addr);
    i->get_r1()->set((uint8_t)res);

    setflag_math(i, res);
}

static void addi(Instruction *i){
    uint16_t res = i->get_r1()->getValue() + i->get_imm8_0();
    i->get_r1()->set((uint8_t)res);

    setflag_math(i, res);
}

static void addx(Instruction *i){
    uint16_t res = getD(i->get_rr1()) + i->get_r1()->getValue();

    if(res == 0)
        setflag_z1(i);
    else
        setflag_z0(i);

    if((res >> 7) == 1) {
        setflag_n1(i);
    }else {
        setflag_n0(i);
    }

    if(((res >> 8) & 0x007F) != 0)
        setflag_h1(i);
    else
        setflag_h0(i);

    if( ((uint16_t)(res - getD(i->get_rr1()))) != i->get_r1()->getValue())
        setflag_c1(i);
    else
        setflag_c0(i);


    setD(i->get_rr1(), res);
}

static void sub(Instruction *i){
    uint16_t res = ((uint16_t)i->get_r2()->getValue()) - i->get_r1()->getValue();
    i->get_r2()->set((uint8_t)res);

    setflag_math(i, res);
}

static void subHL(Instruction *i){
    uint16_t addr = getD(i->get_rr1());
    uint16_t res = ((uint16_t)i->get_mem()->readb(addr)) - i->get_r1()->getValue();
    i->get_mem()->writeb(addr, res);

    setflag_math(i, res);
}

static void subi(Instruction *i){
    uint16_t res = ((uint16_t)i->get_r1()->getValue()) - i->get_imm8_0();
    i->get_r1()->set(res);

    setflag_math(i, res);
}

static void inc(Instruction *i){
    uint16_t res = ((uint16_t)i->get_r1()->getValue()) + 1;
    i->get_r1()->set((uint8_t)res);

    setflag_math(i, res);
}

static void incHL(Instruction *i){
    uint16_t addr = getD(i->get_rr1());
    uint16_t res = ((uint16_t)i->get_mem()->readb(addr)) + 0x1;
    i->get_mem()->writeb(addr, (uint8_t)res);

    setflag_math(i, res);
}

static void inx(Instruction *i){
    setD(i->get_rr1(), getD(i->get_rr1()) + 1);
    // Flags not affected
}

static void dec(Instruction *i){
    uint16_t res = ((uint16_t)i->get_r1()->getValue()) - 1;
    i->get_r1()->set((uint8_t) res);

    setflag_math(i, res);
}

static void decHL(Instruction *i){
    uint16_t addr = getD(i->get_rr1());
    uint16_t res = ((uint16_t)i->get_mem()->readb(addr)) - 1;
    i->get_mem()->writeb(addr, (uint8_t)res);

    setflag_math(i, res);
}

static void and_(Instruction *i){
    Reg<uint8_t> *a = i->get_r1();
    Reg<uint8_t> *r = i->get_r2();
    uint16_t res = ((uint16_t)a->getValue()) & r->getValue();
    r->set((uint8_t)res);

    setflag_math(i, res);
    i->get_flag()->set(i->get_flag()->getValue() & 0xC0); // Clear H and C flags
}

static void andHL(Instruction *i){
    Reg<uint8_t> *a = i->get_r1();
    uint16_t addr = getD(i->get_rr1());
    uint16_t res = ((uint16_t)a->getValue()) & i->get_mem()->readb(addr);
    i->get_mem()->writeb(addr, (uint8_t)res);

    setflag_math(i, res);
    i->get_flag()->set(i->get_flag()->getValue() & 0xC0); // Clear H and C flags
}

static void andi(Instruction *i){
    Reg<uint8_t> *a = i->get_r1();
    uint16_t res = ((uint16_t)a->getValue()) & i->get_imm8_0();
    a->set((uint8_t)res);

    setflag_math(i, res);
    i->get_flag()->set(i->get_flag()->getValue() & 0xC0); // Clear H and C flags
}

static void or_(Instruction *i){
    Reg<uint8_t> *a = i->get_r1();
    Reg<uint8_t> *r = i->get_r2();
    uint16_t res = ((uint16_t)a->getValue()) | r->getValue();
    r->set((uint8_t)res);

    setflag_math(i, res);
    i->get_flag()->set(i->get_flag()->getValue() & 0xC0); // Clear H and C flags
}

static void orHL(Instruction *i){
    Reg<uint8_t> *a = i->get_r1();
    uint16_t addr = getD(i->get_rr1());
    uint16_t res = ((uint16_t)a->getValue()) | i->get_mem()->readb(addr);
    i->get_mem()->writeb(addr, (uint8_t)res);

    setflag_math(i, res);
    i->get_flag()->set(i->get_flag()->getValue() & 0xC0); // Clear H and C flags
}

static void ori(Instruction *i){
    Reg<uint8_t> *a = i->get_r1();
    uint16_t res = ((uint8_t)a->getValue()) | i->get_imm8_0();
    a->set((uint8_t)res);

    setflag_math(i, res);
    i->get_flag()->set(i->get_flag()->getValue() & 0xC0); // Clear H and C flags
}

static void xor_(Instruction *i){
    Reg<uint8_t> *a = i->get_r1();
    Reg<uint8_t> *r = i->get_r2();
    uint16_t res = ((uint8_t)a->getValue()) ^ r->getValue();
    r->set((uint8_t)res);

    setflag_math(i, res);
    i->get_flag()->set(i->get_flag()->getValue() & 0xC0); // Clear H and C flags
}

static void xorHL(Instruction *i){
    Reg<uint8_t> *a = i->get_r1();
    uint16_t addr = getD(i->get_rr1());
    uint16_t res = ((uint16_t)a->getValue()) ^ i->get_mem()->readb(addr);
    i->get_mem()->writeb(addr, (uint8_t)res);

    setflag_math(i, res);
    i->get_flag()->set(i->get_flag()->getValue() & 0xC0); // Clear H and C flags
}

static void xori(Instruction *i){
    Reg<uint8_t> *a = i->get_r1();
    uint16_t res = ((uint8_t)a->getValue()) ^ i->get_imm8_0();
    a->set((uint8_t)res);

    setflag_math(i, res);
    i->get_flag()->set(i->get_flag()->getValue() & 0xC0); // Clear H and C flags
}

static void cmp(Instruction *i){
    Reg<uint8_t> *a = i->get_r1();
    Reg<uint8_t> *r = i->get_r2();
    
    if(a->getValue() == r->getValue())
        i->get_flag()->set(i->get_flag()->getValue() | 0x80);
    else if(r->getValue() < a->getValue())
        i->get_flag()->set(i->get_flag()->getValue() | 0x40);
}

static void cmpHL(Instruction *i){
    Reg<uint8_t> *a = i->get_r1();
    uint8_t r = i->get_mem()->readb(getD(i->get_rr1()));
    
    if(a->getValue() == r)
        i->get_flag()->set(i->get_flag()->getValue() | 0x80);
    else if(r < a->getValue())
        i->get_flag()->set(i->get_flag()->getValue() | 0x40);
}

static void cmpi(Instruction *i){
    Reg<uint8_t> *a = i->get_r1();
    
    if(a->getValue() == i->get_imm8_0())
        i->get_flag()->set(i->get_flag()->getValue() | 0x80);
    else if(i->get_imm8_0() < a->getValue())
        i->get_flag()->set(i->get_flag()->getValue() | 0x40);
}

static void cmps(Instruction *i){
    int8_t a = (int8_t) (i->get_r1()->getValue());
    int8_t r = (int8_t) (i->get_r2()->getValue());
    
    if(a == r)
        i->get_flag()->set(i->get_flag()->getValue() | 0x80);
    else if(r < a)
        i->get_flag()->set(i->get_flag()->getValue() | 0x40);
}

static void cmpsHL(Instruction *i){
    int8_t a = (int8_t) (i->get_r1()->getValue());
    int8_t r = (int8_t) i->get_mem()->readb(getD(i->get_rr1()));
    
    if(a == r)
        i->get_flag()->set(i->get_flag()->getValue() | 0x80);
    else if(r < a)
        i->get_flag()->set(i->get_flag()->getValue() | 0x40);
}

static void sin(Instruction *i){
    printf("sin function not implemented for now\n");
}

static void sout(Instruction *i){
    printf("%c", i->get_r1()->getValue());
}

static void clrscr(Instruction *i){
    i->get_scr()->clear();
}

static void draw(Instruction *i){
    i->get_scr()->setSegment(i->get_r1()->getValue(), i->get_imm8_0(), i->get_imm8_1());
    //i->get_scr()->show();
}

static void jmp(Instruction *i){
    i->get_rr1()->set(i->get_imm8_1(), i->get_imm8_0());
}

static void jmpz(Instruction *i){
    
    uint8_t mask = 0x80; // 1000 0000
    if((i->get_flag()->getValue() & mask) != 0)
        i->get_rr1()->set(i->get_imm8_1(), i->get_imm8_0());
}

static void jmpnz(Instruction *i){
    
    uint8_t mask = 0x80; // 1000 0000
    if((i->get_flag()->getValue() & mask) == 0)
    if((i->get_flag()->getValue() & mask) == 0)
        i->get_rr1()->set(i->get_imm8_1(), i->get_imm8_0());
}

static void jmpn(Instruction *i){
    
    uint8_t mask = 0x40; // 0100 0000
    if((i->get_flag()->getValue() & mask) != 0)
        i->get_rr1()->set(i->get_imm8_1(), i->get_imm8_0());
}

static void jmpnn(Instruction *i){
    
    uint8_t mask = 0x40; // 0100 0000
    if((i->get_flag()->getValue() & mask) == 0)
        i->get_rr1()->set(i->get_imm8_1(), i->get_imm8_0());
}

static void jmph(Instruction *i){
    
    uint8_t mask = 0x20; // 0010 0000
    if((i->get_flag()->getValue() & mask) != 0)
        i->get_rr1()->set(i->get_imm8_1(), i->get_imm8_0());
}

static void jmpnh(Instruction *i){
    
    uint8_t mask = 0x20; // 0010 0000
    if((i->get_flag()->getValue() & mask) == 0)
        i->get_rr1()->set(i->get_imm8_1(), i->get_imm8_0());
}

static void jmpc(Instruction *i){
    
    uint8_t mask = 0x10; // 0001 0000
    if((i->get_flag()->getValue() & mask) != 0)
        i->get_rr1()->set(i->get_imm8_1(), i->get_imm8_0());
}

static void jmpnc(Instruction *i){
    
    uint8_t mask = 0x10; // 0001 0000
    if((i->get_flag()->getValue() & mask) == 0)
        i->get_rr1()->set(i->get_imm8_1(), i->get_imm8_0());
}

/* NEVVVVVVV */
static void njmp(Instruction *i){
    int8_t sig_jmp_offset = (int8_t) i->get_imm8_0();
    setD(i->get_rr1(), getD(i->get_rr1()) + sig_jmp_offset);
}

static void njmpz(Instruction *i){

    uint8_t mask = 0x80; // 1000 0000
    int8_t sig_jmp_offset = (int8_t) i->get_imm8_0();
    if((i->get_flag()->getValue() & mask) != 0)
        setD(i->get_rr1(), getD(i->get_rr1()) + sig_jmp_offset);
}

static void njmpnz(Instruction *i){

    uint8_t mask = 0x80; // 1000 0000
    int8_t sig_jmp_offset = (int8_t) i->get_imm8_0();
    if((i->get_flag()->getValue() & mask) == 0)
        setD(i->get_rr1(), getD(i->get_rr1()) + sig_jmp_offset);
}

static void njmpn(Instruction *i){

    uint8_t mask = 0x40; // 0100 0000
    int8_t sig_jmp_offset = (int8_t) i->get_imm8_0();
    if((i->get_flag()->getValue() & mask) != 0)
        setD(i->get_rr1(), getD(i->get_rr1()) + sig_jmp_offset);
}

static void njmpnn(Instruction *i){

    uint8_t mask = 0x40; // 0100 0000
    int8_t sig_jmp_offset = (int8_t) i->get_imm8_0();
    if((i->get_flag()->getValue() & mask) == 0)
        setD(i->get_rr1(), getD(i->get_rr1()) + sig_jmp_offset);
}

static void njmph(Instruction *i){

    uint8_t mask = 0x20; // 0010 0000
    int8_t sig_jmp_offset = (int8_t) i->get_imm8_0();
    if((i->get_flag()->getValue() & mask) != 0)
        setD(i->get_rr1(), getD(i->get_rr1()) + sig_jmp_offset);
}

static void njmpnh(Instruction *i){

    uint8_t mask = 0x20; // 0010 0000
    int8_t sig_jmp_offset = (int8_t) i->get_imm8_0();
    if((i->get_flag()->getValue() & mask) == 0)
        setD(i->get_rr1(), getD(i->get_rr1()) + sig_jmp_offset);
}

static void njmpc(Instruction *i){

    uint8_t mask = 0x10; // 0001 0000
    int8_t sig_jmp_offset = (int8_t) i->get_imm8_0();
    if((i->get_flag()->getValue() & mask) != 0)
        setD(i->get_rr1(), getD(i->get_rr1()) + sig_jmp_offset);
}

static void njmpnc(Instruction *i){

    uint8_t mask = 0x10; // 0001 0000
    int8_t sig_jmp_offset = (int8_t) i->get_imm8_0();
    if((i->get_flag()->getValue() & mask) == 0)
        setD(i->get_rr1(), getD(i->get_rr1()) + sig_jmp_offset);
}

static void call(Instruction *i){

    uint16_t pc_v = getD(i->get_rr1());
    uint16_t sp_v = getD(i->get_rr2());
    i->get_mem()->writew(sp_v, pc_v);
    setD(i->get_rr2(), sp_v - 2);
    i->get_rr1()->set(i->get_imm8_1(), i->get_imm8_0());
}

static void ret(Instruction *i){
    poprr(i);
}

static void nop(Instruction *i){}

static void init_e( void (*GATE[])(Instruction *i) ){
    
    std::fill_n(GATE, 0x100, &hcf);
    
    GATE[0x22] = ldx;         // LDX SP
    GATE[0x76] = xor_;          // XOR A
    GATE[0x0F] = jmp;           // JMP
    GATE[0x6C] = hcf;           // HCF (HALT Intel)
    
    // LDI
    GATE[0x20] = ldi;       // 20 LDI B, xx
    GATE[0x30] = ldi;       // 30 LDI C, xx
    GATE[0x40] = ldi;       // 40 LDI D, xx
    GATE[0x50] = ldi;       // 50 LDI E, xx
    GATE[0x60] = ldi;       // 60 LDI H, xx
    GATE[0x70] = ldi;       // 70 LDI L, xx
    GATE[0x80] = ldiHL;      // 80 LDI (HL), xx
    GATE[0x90] = ldi;       // 90 LDI A, xx
    
    GATE[0x21] = ldx;      // 21 LDX BC, xxyy
    GATE[0x31] = ldx;      // 31 LDX DE, xxyy
    GATE[0x41] = ldx;      // 41 LDX HL, xxyy
    GATE[0x22] = ldx;      // 22 LDX SP, xxyy
    
    // PUSH
    GATE[0x81] = pushr;       // 81 PUSH B
    GATE[0x91] = pushr;       // 91 PUSH C
    GATE[0xA1] = pushr;       // A1 PUSH D
    GATE[0xB1] = pushr;       // B1 PUSH E
    GATE[0xC1] = pushr;       // C1 PUSH H
    GATE[0xD1] = pushr;       // D1 PUSH L
    GATE[0xC0] = pushHL;      // E1 PUSH (HL)
    GATE[0xD0] = pushr;       // F1 PUSH A
    
    GATE[0x51] = pushrr;      // 51 PUSH BC
    GATE[0x61] = pushrr;      // 61 PUSH DE
    GATE[0x71] = pushrr;      // 71 PUSH HL
    
    // POP
    GATE[0x82] = popr;       // 82 POP B
    GATE[0x92] = popr;       // 92 POP C
    GATE[0xA2] = popr;       // A2 POP D
    GATE[0xB2] = popr;       // B2 POP E
    GATE[0xC2] = popr;       // C2 POP H
    GATE[0xD2] = popr;       // D2 POP L
    GATE[0xC3] = popHL;      // C3 POP (HL)
    GATE[0xD3] = popr;       // D3 POP A
    
    GATE[0x52] = poprr;      // 52 POP BC
    GATE[0x62] = poprr;      // 62 POP DE
    GATE[0x72] = poprr;      // 72 POP HL
    
    // MOV
    GATE[0x09] = mov;       // 09 MOV B, B
    GATE[0x19] = mov;       // 19 MOV B, C
    GATE[0x29] = mov;       // 29 MOV B, D
    GATE[0x39] = mov;       // 39 MOV B, E
    GATE[0x49] = mov;       // 49 MOV B, H
    GATE[0x59] = mov;       // 59 MOV B, L
    GATE[0x69] = mov_HL;      // 69 MOV B, (HL)
    GATE[0x79] = mov;       // 79 MOV B, A
    
    GATE[0x89] = mov;       // 89 MOV C, B
    GATE[0x99] = mov;       // 99 MOV C, C
    GATE[0xA9] = mov;       // A9 MOV C, D
    GATE[0xB9] = mov;       // B9 MOV C, E
    GATE[0xC9] = mov;       // C9 MOV C, H
    GATE[0xD9] = mov;       // D9 MOV C, L
    GATE[0xE9] = mov_HL;      // E9 MOV C, (HL)
    GATE[0xF9] = mov;       // F9 MOV C, A
    
    GATE[0x0A] = mov;       // 0A MOV D, B
    GATE[0x1A] = mov;       // 1A MOV D, C
    GATE[0x2A] = mov;       // 2A MOV D, D
    GATE[0x3A] = mov;       // 3A MOV D, E
    GATE[0x4A] = mov;       // 4A MOV D, H
    GATE[0x5A] = mov;       // 5A MOV D, L
    GATE[0x6A] = mov_HL;      // 6A MOV D, (HL)
    GATE[0x7A] = mov;       // 7A MOV D, A
    
    GATE[0x8A] = mov;       // 8A MOV E, B
    GATE[0x9A] = mov;       // 9A MOV E, C
    GATE[0xAA] = mov;       // AA MOV E, D
    GATE[0xBA] = mov;       // BA MOV E, E
    GATE[0xCA] = mov;       // CA MOV E, H
    GATE[0xDA] = mov;       // DA MOV E, L
    GATE[0xEA] = mov_HL;      // EA MOV E, (HL)
    GATE[0xFA] = mov;       // FA MOV E, A
    
    GATE[0x0B] = mov;               // 0B MOV H, B
    GATE[0x1B] = mov;               // 1B MOV H, C
    GATE[0x2B] = mov;               // 2B MOV H, D
    GATE[0x3B] = mov;               // 3B MOV H, E
    GATE[0x4B] = mov;               // 4B MOV H, H
    GATE[0x5B] = mov;               // 5B MOV H, L
    GATE[0x6B] = mov_HL;            // 6B MOV H, (HL)
    GATE[0x7B] = mov;               // 7B MOV H, A
    
    GATE[0x8B] = mov;               // 8B MOV L, B
    GATE[0x9B] = mov;               // 9B MOV L, C
    GATE[0xAB] = mov;               // AB MOV L, D
    GATE[0xBB] = mov;               // BB MOV L, E
    GATE[0xCB] = mov;               // CB MOV L, H
    GATE[0xDB] = mov;               // DB MOV L, L
    GATE[0xEB] = mov_HL;            // EB MOV L, (HL)
    GATE[0xFB] = mov;               // FB MOV L, A
    
    GATE[0x0C] = movHL_;            // 0C MOV (HL), B
    GATE[0x1C] = movHL_;            // 1C MOV (HL), C
    GATE[0x2C] = movHL_;            // 2C MOV (HL), D
    GATE[0x3C] = movHL_;            // 3C MOV (HL), E
    GATE[0x4C] = movHL_;            // 4C MOV (HL), H
    GATE[0x5C] = movHL_;            // 5C MOV (HL), L
    GATE[0x6C] = hcf;               // 6C HCF
    GATE[0x7C] = movHL_;            // 7C MOV (HL), A
    
    GATE[0x8C] = mov;               // 8C MOV A, B
    GATE[0x9C] = mov;               // 9C MOV A, C
    GATE[0xAC] = mov;               // AC MOV A, D
    GATE[0xBC] = mov;               // BC MOV A, E
    GATE[0xCC] = mov;               // CC MOV A, H
    GATE[0xDC] = mov;               // DC MOV A, L
    GATE[0xEC] = mov_HL;            // EC MOV A, (HL)
    GATE[0xFC] = mov;               // FC MOV A, A
    
    GATE[0xED] = movrr;             // ED MOV HL, BC
    GATE[0xFD] = movrr;             // FD MOV HL, DE
    
    // FLAG
    GATE[0x08] = clrflag;           // 08 CLRFLAG
    
    GATE[0x18] = setflag_z1;        // 18 SETFLAG Z, 1
    GATE[0x28] = setflag_z0;        // 28 SETFLAG Z, 0
    GATE[0x38] = setflag_n1;        // 38 SETFLAG N, 1
    GATE[0x48] = setflag_n0;        // 48 SETFLAG N, 0
    GATE[0x58] = setflag_h1;        // 58 SETFLAG H, 1
    GATE[0x68] = setflag_h0;        // 68 SETFLAG H, 0
    GATE[0x78] = setflag_c1;        // 78 SETFLAG C, 1
    GATE[0x88] = setflag_c0;        // 88 SETFLAG C, 0
    
    // ADD
    GATE[0x04] = add;       // 04 ADD B
    GATE[0x14] = add;       // 14 ADD C
    GATE[0x24] = add;       // 24 ADD D
    GATE[0x34] = add;       // 34 ADD E
    GATE[0x44] = add;       // 44 ADD H
    GATE[0x54] = add;       // 54 ADD L
    GATE[0x64] = addHL;      // 64 ADD (HL)
    GATE[0x74] = add;       // 74 ADD A
    
    GATE[0xA7] = addi;       // A7 ADDI xx
    
    GATE[0x83] = addx;       // 83 ADDX BC
    GATE[0x93] = addx;       // 93 ADDX DE
    GATE[0xA3] = addx;       // A3 ADDX HL
    
    // SUB
    GATE[0x84] = sub;       // 84 SUB B
    GATE[0x94] = sub;       // 94 SUB C
    GATE[0xA4] = sub;       // A4 SUB D
    GATE[0xB4] = sub;       // B4 SUB E
    GATE[0xC4] = sub;       // C4 SUB H
    GATE[0xD4] = sub;       // D4 SUB L
    GATE[0xE4] = subHL;      // E4 SUB (HL)
    GATE[0xF4] = sub;       // F4 SUB A
    
    GATE[0xB7] = subi;       // B7 SUBI xx
    
    // INC
    GATE[0x03] = inc;       // 03 INC B
    GATE[0x13] = inc;       // 13 INC C
    GATE[0x23] = inc;       // 23 INC D
    GATE[0x33] = inc;       // 33 INC E
    GATE[0x43] = inc;       // 43 INC H
    GATE[0x53] = inc;       // 53 INC L
    GATE[0x63] = incHL;      // 63 INC (HL)
    GATE[0x73] = inc;       // 73 INC A
    
    GATE[0xA8] = inx;      // A8 INX BC
    GATE[0xB8] = inx;      // B8 INX DE
    GATE[0xC8] = inx;      // C8 INX HL
    
    // DEC
    GATE[0x07] = dec;       // 07 DEC B
    GATE[0x17] = dec;       // 17 DEC C
    GATE[0x27] = dec;       // 27 DEC D
    GATE[0x37] = dec;       // 37 DEC E
    GATE[0x47] = dec;       // 47 DEC H
    GATE[0x57] = dec;       // 57 DEC L
    GATE[0x67] = decHL;      // 67 DEC (HL)
    GATE[0x77] = dec;       // 77 DEC A
    
    // AND
    GATE[0x05] = and_;       // 05 AND B
    GATE[0x15] = and_;       // 15 AND C
    GATE[0x25] = and_;       // 25 AND D
    GATE[0x35] = and_;       // 35 AND E
    GATE[0x45] = and_;       // 45 AND H
    GATE[0x55] = and_;       // 55 AND L
    GATE[0x65] = andHL;      // 65 AND (HL)
    GATE[0x75] = and_;       // 75 AND A
    
    GATE[0xC7] = andi;       // C7 ANDI xx
    
    // OR
    GATE[0x85] = or_;       // 85 OR B
    GATE[0x95] = or_;       // 95 OR C
    GATE[0xA5] = or_;       // A5 OR D
    GATE[0xB5] = or_;       // B5 OR E
    GATE[0xC5] = or_;       // C5 OR H
    GATE[0xD5] = or_;       // D5 OR L
    GATE[0xE5] = orHL;      // E5 OR (HL)
    GATE[0xF5] = or_;       // F5 OR A
    
    GATE[0xD7] = ori;       // D7 ORI xx
    
    // XOR
    GATE[0x06] = xor_;       // 06 XOR B
    GATE[0x16] = xor_;       // 16 XOR C
    GATE[0x26] = xor_;       // 26 XOR D
    GATE[0x36] = xor_;       // 36 XOR E
    GATE[0x46] = xor_;       // 46 XOR H
    GATE[0x56] = xor_;       // 56 XOR L
    GATE[0x66] = xorHL;      // 66 XOR (HL)
    GATE[0x76] = xor_;       // 76 XOR A
    
    GATE[0xE7] = xori;       // E7 XORI xx
    
    // CMP
    GATE[0x86] = cmp;       // 86 CMP B
    GATE[0x96] = cmp;       // 96 CMP C
    GATE[0xA6] = cmp;       // A6 CMP D
    GATE[0xB6] = cmp;       // B6 CMP E
    GATE[0xC6] = cmp;       // C6 CMP H
    GATE[0xD6] = cmp;       // D6 CMP L
    GATE[0xE6] = cmpHL;      // E6 CMP (HL)
    GATE[0xF6] = cmp;       // F6 CMP A
    
    GATE[0xF7] = cmpi;       // F7 CMPI xx
    
    // CMPS
    GATE[0x0D] = cmps;       // 0D CMPS B
    GATE[0x1D] = cmps;       // 1D CMPS C
    GATE[0x2D] = cmps;       // 2D CMPS D
    GATE[0x3D] = cmps;       // 3D CMPS E
    GATE[0x4D] = cmps;       // 4D CMPS H
    GATE[0x5D] = cmps;       // 5D CMPS L
    GATE[0x6D] = cmpsHL;      // 6D CMPS (HL)
    GATE[0x7D] = cmps;       // 7D CMPS A
    
    // I/O
    GATE[0xE0] = sin;          // E0 SIN
    GATE[0xE1] = sout;         // E1 SOUT
    GATE[0xF0] = clrscr;       // F0 CLRSCR
    GATE[0xF1] = draw;         // F1 DRAW
    
    // JMP
    GATE[0x0F] = jmp;         // 0F JMP yy xx
    
    GATE[0x1F] = jmpz;         // 1F JMPCC yy xx
    GATE[0x2F] = jmpnz;         // 2F JMPCC yy xx
    GATE[0x3F] = jmpn;         // 3F JMPCC yy xx
    GATE[0x4F] = jmpnn;         // 4F JMPCC yy xx
    GATE[0x5F] = jmph;         // 5F JMPCC yy xx
    GATE[0x6F] = jmpnh;         // 6F JMPCC yy xx
    GATE[0x7F] = jmpc;         // 7F JMPCC yy xx
    GATE[0x8F] = jmpnc;         // 8F JMPCC yy xx
    
    GATE[0x9F] = njmp;         // 9F NJMP xx
    
    GATE[0xAF] = njmpz;         // AF NJMPCC xx
    GATE[0xBF] = njmpnz;         // BF NJMPCC xx
    GATE[0xCF] = njmpn;         // CF NJMPCC xx
    GATE[0xDF] = njmpnn;         // DF NJMPCC xx
    GATE[0xEF] = njmph;         // EF NJMPCC xx
    GATE[0xFF] = njmpnh;         // FF NJMPCC xx
    GATE[0xEE] = njmpc;         // EE NJMPCC xx
    GATE[0xFE] = njmpnc;         // FE NJMPCC xx
    
    // Func handling
    GATE[0x1E] = call;         // 1E CALL yy xx
    
    GATE[0x0E] = ret;            // 0E RET
    
    GATE[0x00] = nop;         // 00 NOP
}
