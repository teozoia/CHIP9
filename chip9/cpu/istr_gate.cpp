//
//  istr_gate.cpp
//  chip9
//
//  Created by Matteo Zoia on 08/01/2020.
//  Copyright © 2020 Matteo Zoia. All rights reserved.
//

#include <stdio.h>
#include "Instruction.cpp"
#pragma once

/* regs: [ F, A, B, C, D, E, H, L, S, P, I, X ] */
/* dregs: [ BC, DE, HL, SP, IX(PC) ] */

static void d_dummy(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    return;
}

// 20 LDI B, xx
static void d_ldib(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "LDI");
    i->set_r1(&regs[2]); // B
}

// 30 LDI C, xx
static void d_ldic(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "LDI");
    i->set_r1(&regs[3]); // C
}

// 40 LDI D, xx
static void d_ldid(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "LDI");
    i->set_r1(&regs[4]); // D
}

// 22 LDX SP, yy xx
static void d_ldxsp(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "LDX");
    i->set_rr1(&dregs[3]); // SP
}

// 76 XOR A
static void d_xora(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "XOR");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[1]); // A
}

// 0F JMP yy xx
static void d_jmp(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "JMP");
    i->set_rr1(&dregs[4]); // PC
}
