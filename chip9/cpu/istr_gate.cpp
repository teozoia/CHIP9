//
//  istr_gate.cpp
//  CHIP9
//
//  Created by Matteo Zoia on 08/01/2020.
//  Copyright © 2020 Matteo Zoia. All rights reserved.
//

#include <stdio.h>
#include "Instruction.cpp"
#pragma once

/*
 * NOTES: this cpp file is very very boring; for every instruction in the ISA it takes
 * the opcode and compose a structure for the execute function.
 * At this time is implemented with a jump table, so there are about 256 function very
 * similar each oher, the next step is take all the opcodes and push them in Z3 SAT solver
 * (from Microsfot) and try to extract a better way to divide the opcode.
 * The goal is to have less function in this jump table.
 */

/* regs: [ F, A, B, C, D, E, H, L, S, P, I, X ] */
/* dregs: [ BC, DE, HL, SP, IX(PC) ] */

static void d_dummy(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    return;
}

// ----[ LDI R ]------------------------------------------------------------------

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

// 50 LDI E, xx
static void d_ldie(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "LDI");
    i->set_r1(&regs[5]); // E
}

// 60 LDI H, xx
static void d_ldih(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "LDI");
    i->set_r1(&regs[6]); // H
}

// 70 LDI E, xx
static void d_ldil(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "LDI");
    i->set_r1(&regs[7]); // L
}

// 80 LDI (HL), xx
static void d_ldiHL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "LDI");
    i->set_rr1(&dregs[2]); // HL
}

// 90 LDI A, xx
static void d_ldia(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "LDI");
    i->set_r1(&regs[1]); // A
}

// ----[ LDX RR ]------------------------------------------------------------------

// 21 LDX BC, yy xx
static void d_ldxbc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "LDX");
    i->set_rr1(&dregs[0]); // BC
}

// 31 LDX DE, yy xx
static void d_ldxde(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "LDX");
    i->set_rr1(&dregs[1]); // DE
}

// 41 LDX HL, yy xx
static void d_ldxhl(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "LDX");
    i->set_rr1(&dregs[2]); // HL
}

// 22 LDX SP, yy xx
static void d_ldxsp(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "LDX");
    i->set_rr1(&dregs[3]); // SP
}

// ----[ PUSH R ]------------------------------------------------------------------

// 81 PUSH B
static void d_pushb(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "PUSH");
    i->set_r1(&regs[2]); // B
    i->set_rr1(&dregs[3]); // SP
}

// 91 PUSH C
static void d_pushc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "PUSH");
    i->set_r1(&regs[3]); // C
    i->set_rr1(&dregs[3]); // SP
}

// A1 PUSH D
static void d_pushd(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "PUSH");
    i->set_r1(&regs[4]); // D
    i->set_rr1(&dregs[3]); // SP
}

// B1 PUSH E
static void d_pushe(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "PUSH");
    i->set_r1(&regs[4]); // E
    i->set_rr1(&dregs[3]); // SP
}

// C1 PUSH H
static void d_pushh(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "PUSH");
    i->set_r1(&regs[5]); // H
    i->set_rr1(&dregs[3]); // SP
}

// D1 PUSH L
static void d_pushl(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "PUSH");
    i->set_r1(&regs[6]); // L
    i->set_rr1(&dregs[3]); // SP
}

// C0 PUSH (HL)
static void d_pushHL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "PUSH");
    i->set_rr1(&dregs[2]); // HL
    i->set_rr2(&dregs[3]); // SP
}

// D0 PUSH S
static void d_pusha(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "PUSH");
    i->set_r1(&regs[1]); // A
    i->set_rr1(&dregs[3]); // SP
}

// ----[ PUSH RR ]-----------------------------------------------------------------

// 51 PUSH BC
static void d_pushbc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "PUSH");
    i->set_rr1(&dregs[0]); // BC
    i->set_rr2(&dregs[3]); // SP
}

// 61 PUSH BC
static void d_pushde(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "PUSH");
    i->set_rr1(&dregs[1]); // BC
    i->set_rr2(&dregs[3]); // SP
}

// 71 PUSH HL
static void d_pushhl(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "PUSH");
    i->set_rr1(&dregs[2]); // HL
    i->set_rr2(&dregs[3]); // SP
}

// ----[ POP R ]------------------------------------------------------------------

// 82 POP B
static void d_popb(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "POP");
    i->set_r1(&regs[2]); // B
    i->set_rr1(&dregs[3]); // SP
}

// 92 POP C
static void d_popc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "POP");
    i->set_r1(&regs[3]); // C
    i->set_rr1(&dregs[3]); // SP
}

// A2 POP D
static void d_popd(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "POP");
    i->set_r1(&regs[4]); // D
    i->set_rr1(&dregs[3]); // SP
}

// B2 POP E
static void d_pope(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "POP");
    i->set_r1(&regs[5]); // E
    i->set_rr1(&dregs[3]); // SP
}

// C2 POP H
static void d_poph(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "POP");
    i->set_r1(&regs[6]); // H
    i->set_rr1(&dregs[3]); // SP
}

// D2 POP L
static void d_popl(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "POP");
    i->set_r1(&regs[7]); // L
    i->set_rr1(&dregs[3]); // SP
}

// C3 POP (HL)
static void d_popHL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "POP");
    i->set_rr1(&dregs[2]); // HL
    i->set_rr2(&dregs[3]); // SP
}

// D3 POP A
static void d_popa(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "POP");
    i->set_r1(&regs[1]); // A
    i->set_rr1(&dregs[3]); // SP
}

// ----[ POP RR ]-----------------------------------------------------------------

// 52 POP BC
static void d_popbc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "POP");
    i->set_rr1(&dregs[0]); // BC
    i->set_rr2(&dregs[3]); // SP
}

// 62 POP DE
static void d_popde(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "POP");
    i->set_rr1(&dregs[1]); // DE
    i->set_rr2(&dregs[3]); // SP
}

// 72 POP HL
static void d_pophl(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "POP");
    i->set_rr1(&dregs[2]); // HL
    i->set_rr2(&dregs[3]); // SP
}

// ----[ MOV R1(B), R2 ]------------------------------------------------------------

// 09 MOV B, B
static void d_movb_b(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[2]); // B
    i->set_r2(&regs[2]); // B
}

// 19 MOV B, C
static void d_movb_c(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[2]); // B
    i->set_r2(&regs[3]); // C
}

// 29 MOV B, D
static void d_movb_d(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[2]); // B
    i->set_r2(&regs[4]); // D
}

// 39 MOV B, E
static void d_movb_e(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[2]); // B
    i->set_r2(&regs[5]); // E
}

// 49 MOV B, H
static void d_movb_h(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[2]); // B
    i->set_r2(&regs[6]); // H
}

// 59 MOV B, L
static void d_movb_l(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[2]); // B
    i->set_r2(&regs[7]); // L
}

// 69 MOV B, (HL)
static void d_movb_HL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[2]); // B
    i->set_rr1(&dregs[2]); // HL
}

// 79 MOV B, A
static void d_movb_a(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[2]); // B
    i->set_r2(&regs[1]); // A
}

// ----[ MOV R1(C), R2 ]------------------------------------------------------------

// 89 MOV C, B
static void d_movc_b(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[3]); // C
    i->set_r2(&regs[2]); // B
}

// 99 MOV C, C
static void d_movc_c(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[3]); // C
    i->set_r2(&regs[3]); // C
}

// A9 MOV C, D
static void d_movc_d(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[3]); // C
    i->set_r2(&regs[4]); // D
}

// B9 MOV C, E
static void d_movc_e(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[3]); // C
    i->set_r2(&regs[5]); // E
}

// C9 MOV C, H
static void d_movc_h(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[3]); // C
    i->set_r2(&regs[6]); // H
}

// D9 MOV C, L
static void d_movc_l(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[3]); // C
    i->set_r2(&regs[7]); // L
}

// E9 MOV C, (HL)
static void d_movc_HL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[3]); // C
    i->set_rr1(&dregs[2]); // HL
}

// F9 MOV C, A
static void d_movc_a(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[3]); // C
    i->set_r2(&regs[0]); // A
}

// ----[ MOV R1(D), R2 ]------------------------------------------------------------

// 0A MOV D, B
static void d_movd_b(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[4]); // D
    i->set_r2(&regs[2]); // B
}

// 1A MOV D, C
static void d_movd_c(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[4]); // D
    i->set_r2(&regs[3]); // C
}

// 2A MOV D, D
static void d_movd_d(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[4]); // D
    i->set_r2(&regs[4]); // D
}

// 3A MOV D, E
static void d_movd_e(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[4]); // D
    i->set_r2(&regs[5]); // E
}

// 4A MOV D, H
static void d_movd_h(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[4]); // D
    i->set_r2(&regs[6]); // H
}

// 5A MOV D, L
static void d_movd_l(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[4]); // D
    i->set_r2(&regs[7]); // L
}

// 6A MOV D, (HL)
static void d_movd_HL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[4]); // D
    i->set_rr1(&dregs[2]); // HL
}

// 7A MOV D, A
static void d_movd_a(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[4]); // D
    i->set_r2(&regs[0]); // A
}

// ----[ MOV R1(E), R2 ]------------------------------------------------------------

// 8A MOV E, B
static void d_move_b(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[5]); // E
    i->set_r2(&regs[2]); // B
}

// 9A MOV E, C
static void d_move_c(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[5]); // E
    i->set_r2(&regs[3]); // C
}

// AA MOV E, D
static void d_move_d(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[5]); // E
    i->set_r2(&regs[4]); // D
}

// BA MOV E, E
static void d_move_e(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[5]); // E
    i->set_r2(&regs[5]); // E
}

// CA MOV E, H
static void d_move_h(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[5]); // E
    i->set_r2(&regs[6]); // H
}

// DA MOV E, L
static void d_move_l(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[5]); // E
    i->set_r2(&regs[7]); // L
}

// EA MOV E, (HL)
static void d_move_HL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[5]); // E
    i->set_rr1(&dregs[2]); // HL
}

// FA MOV E, A
static void d_move_a(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[5]); // E
    i->set_r2(&regs[0]); // A
}

// ----[ MOV R1(H), R2 ]------------------------------------------------------------

// 0B MOV H, B
static void d_movh_b(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[6]); // H
    i->set_r2(&regs[2]); // B
}

// 1B MOV H, C
static void d_movh_c(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[6]); // H
    i->set_r2(&regs[3]); // C
}

// 2B MOV H, D
static void d_movh_d(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[6]); // H
    i->set_r2(&regs[4]); // D
}

// 3B MOV H, E
static void d_movh_e(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[6]); // H
    i->set_r2(&regs[5]); // E
}

// 4B MOV H, H
static void d_movh_h(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[6]); // H
    i->set_r2(&regs[6]); // H
}

// 5B MOV H, L
static void d_movh_l(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[6]); // H
    i->set_r2(&regs[7]); // L
}

// 6B MOV H, (HL)
static void d_movh_HL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[6]); // H
    i->set_rr1(&dregs[2]); // HL
}

// 7B MOV H, A
static void d_movh_a(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[6]); // H
    i->set_r2(&regs[0]); // A
}

// ----[ MOV R1(L), R2 ]------------------------------------------------------------

// 8B MOV L, B
static void d_movl_b(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[7]); // L
    i->set_r2(&regs[2]); // B
}

// 9B MOV L, C
static void d_movl_c(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[7]); // L
    i->set_r2(&regs[3]); // C
}

// AB MOV L, D
static void d_movl_d(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[7]); // L
    i->set_r2(&regs[4]); // D
}

// BB MOV L, E
static void d_movl_e(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[7]); // L
    i->set_r2(&regs[5]); // E
}

// CB MOV L, H
static void d_movl_h(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[7]); // L
    i->set_r2(&regs[6]); // H
}

// DB MOV L, L
static void d_movl_l(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[7]); // L
    i->set_r2(&regs[7]); // L
}

// EB MOV L, (HL)
static void d_movl_HL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[7]); // L
    i->set_rr1(&dregs[2]); // HL
}

// FB MOV L, A
static void d_movl_a(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[7]); // L
    i->set_r2(&regs[0]); // A
}

// ----[ MOV R1(HL), R2 ]------------------------------------------------------------

// 0C MOV (HL), B
static void d_movHL_b(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_rr1(&dregs[2]); // (HL)
    i->set_r1(&regs[2]); // B
}

// 1C MOV (HL), C
static void d_movHL_c(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_rr1(&dregs[2]); // (HL)
    i->set_r1(&regs[3]); // C
}

// 2C MOV (HL), D
static void d_movHL_d(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_rr1(&dregs[2]); // (HL)
    i->set_r1(&regs[4]); // D
}

// 3C MOV (HL), E
static void d_movHL_e(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_rr1(&dregs[2]); // (HL)
    i->set_r1(&regs[5]); // E
}

// 4C MOV (HL), H
static void d_movHL_h(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_rr1(&dregs[2]); // (HL)
    i->set_r1(&regs[6]); // H
}

// 5C MOV (HL), L
static void d_movHL_l(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_rr1(&dregs[2]); // (HL)
    i->set_r1(&regs[7]); // L
}

// 6C HCF
static void d_hcf(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "HCF");
}

// 7C MOV (HL), A
static void d_movHL_a(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_rr1(&dregs[2]); // (HL)
    i->set_r1(&regs[1]); // A
}

// ----[ MOV R1(A), R2 ]------------------------------------------------------------

// 8C MOV A, B
static void d_mova_b(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[2]); // B
}

// 9C MOV A, C
static void d_mova_c(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[3]); // C
}

// AC MOV A, D
static void d_mova_d(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[4]); // D
}

// BC MOV A, E
static void d_mova_e(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[5]); // E
}

// CC MOV A, H
static void d_mova_h(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[6]); // H
}

// DC MOV A, L
static void d_mova_l(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[7]); // L
}

// EC MOV A, (HL)
static void d_mova_HL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[1]); // A
    i->set_rr1(&dregs[2]); // HL
}

// FC MOV A, A
static void d_mova_a(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[0]); // A
}

// ----[ MOV RR1, RR2 ]-------------------------------------------------------------

// ED MOV HL, BC
static void d_movhl_bc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_rr1(&dregs[2]); // HL
    i->set_rr2(&dregs[0]); // BC
}

// FD MOV HL, DE
static void d_movhl_de(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "MOV");
    i->set_rr1(&dregs[2]); // HL
    i->set_rr2(&dregs[1]); // DE
}

// ----[ CLRFLAG ]--------------------------------------------------------------------

// 08 CLRFLAG
static void d_clrflag(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CLRFLAG");
}

// ----[ SETFLAG f, x ]---------------------------------------------------------------

// 18-28-38-48-58-68-78-88 SETFLAG Z, x
static void d_setflag(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "SETFLAG");
}

// ----[ ADD R ]--------------------------------------------------------------------

// 04 ADD B
static void d_addb(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "ADD");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[2]); // B
}

// 14 ADD C
static void d_addc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "ADD");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[3]); // C
}

// 24 ADD D
static void d_addd(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "ADD");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[4]); // D
}

// 34 ADD E
static void d_adde(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "ADD");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[5]); // E
}

// 44 ADD H
static void d_addh(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "ADD");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[6]); // H
}

// 54 ADD L
static void d_addl(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "ADD");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[7]); // L
}

// 64 ADD (HL)
static void d_addHL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "ADD");
    i->set_r1(&regs[1]); // A
    i->set_rr1(&dregs[2]); // HL
}

// 74 ADD A
static void d_adda(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "ADD");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[1]); // A
}

// ----[ ADDI xx ]----------------------------------------------------------------

// A7 ADDI xx
static void d_addi(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "ADD");
    i->set_r1(&regs[1]); // A
}

// ----[ ADDX RR ]----------------------------------------------------------------

// 83 ADDX BC
static void d_addxbc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "ADDX");
    i->set_r1(&regs[1]); // A
    i->set_rr1(&dregs[0]); // BC
}

// 93 ADDX BC
static void d_addxde(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "ADDX");
    i->set_r1(&regs[1]); // A
    i->set_rr1(&dregs[1]); // DE
}

// A3 ADDX BC
static void d_addxhl(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "ADDX");
    i->set_r1(&regs[1]); // A
    i->set_rr1(&dregs[2]); // HL
}

// ----[ SUB R ]--------------------------------------------------------------------

// 84 ADD B
static void d_subb(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "SUB");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[2]); // B
}

// 94 SUB C
static void d_subc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "SUB");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[3]); // C
}

// A4 SUB D
static void d_subd(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "SUB");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[4]); // D
}

// B4 SUB E
static void d_sube(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "SUB");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[5]); // E
}

// C4 SUB H
static void d_subh(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "SUB");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[6]); // H
}

// D4 SUB L
static void d_subl(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "SUB");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[7]); // L
}

// E4 SUB (HL)
static void d_subHL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "SUB");
    i->set_r1(&regs[1]); // A
    i->set_rr1(&dregs[2]); // HL
}

// F4 SUB A
static void d_suba(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "SUB");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[1]); // A
}

// ----[ SUBI xx ]----------------------------------------------------------------

// B7 SUBI
static void d_subi(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "SUBI");
    i->set_r1(&regs[1]); // A
}

// ----[ INC R ]------------------------------------------------------------------

// 03 INC B
static void d_incb(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "INC");
    i->set_r1(&regs[2]); // B
}

// 13 INC C
static void d_incc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "INC");
    i->set_r1(&regs[3]); // C
}

// 23 INC D
static void d_incd(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "INC");
    i->set_r1(&regs[4]); // D
}

// 33 INC E
static void d_ince(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "INC");
    i->set_r1(&regs[5]); // E
}

// 43 INC H
static void d_inch(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "INC");
    i->set_r1(&regs[6]); // H
}

// 53 INC L
static void d_incl(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "INC");
    i->set_r1(&regs[7]); // L
}

// 63 INC (HL)
static void d_incHL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "INC");
    i->set_rr1(&dregs[2]); // HL
}

// 73 INC A
static void d_inca(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "INC");
    i->set_r1(&regs[1]); // A
}

// ----[ INX RR ]----------------------------------------------------------------

// A8 INX BC
static void d_inxbc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "INX");
    i->set_rr1(&dregs[0]); // BC
}

// B8 INX DE
static void d_inxde(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "INX");
    i->set_rr1(&dregs[1]); // DE
}

// C8 INX HL
static void d_inxhl(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "INX");
    i->set_rr1(&dregs[2]); //HL
}

// ----[ DEC R ]------------------------------------------------------------------

// 07 DEC B
static void d_decb(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "DEC");
    i->set_r1(&regs[2]); // B
}

// 17 DEC C
static void d_decc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "DEC");
    i->set_r1(&regs[3]); // C
}

// 27 DEC D
static void d_decd(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "DEC");
    i->set_r1(&regs[4]); // D
}

// 37 DEC E
static void d_dece(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "DEC");
    i->set_r1(&regs[5]); // E
}

// 47 DEC H
static void d_dech(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "DEC");
    i->set_r1(&regs[6]); // H
}

// 57 DEC L
static void d_decl(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "DEC");
    i->set_r1(&regs[7]); // L
}

// 67 DEC (HL)
static void d_decHL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "DEC");
    i->set_rr1(&dregs[2]); // HL
}

// 77 DEC A
static void d_deca(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "DEC");
    i->set_r1(&regs[1]); // A
}

// ----[ AND R ]------------------------------------------------------------------

// 05 AND B
static void d_andb(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "AND");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[2]); // B
}

// 15 AND C
static void d_andc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "AND");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[3]); // C
}

// 25 AND D
static void d_andd(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "AND");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[4]); // D
}

// 35 AND E
static void d_ande(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "AND");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[5]); // E
}

// 45 AND H
static void d_andh(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "AND");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[6]); // H
}

// 55 AND L
static void d_andl(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "AND");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[7]); // L
}

// 65 AND HL
static void d_andHL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "AND");
    i->set_r1(&regs[1]); // A
    i->set_rr1(&dregs[2]); // HL
}

// 75 AND A
static void d_anda(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "AND");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[1]); // A
}

// ----[ ANDI xx ]----------------------------------------------------------------

// C7 ANDI xx
static void d_andi(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "ANDI");
    i->set_r1(&regs[1]); // A
}

// ----[ OR R ]-------------------------------------------------------------------

// 85 OR B
static void d_orb(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "OR");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[2]); // B
}

// 95 OR C
static void d_orc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "OR");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[3]); // C
}

// A5 OR D
static void d_ord(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "OR");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[4]); // D
}

// B5 OR E
static void d_ore(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "OR");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[5]); // E
}

// C5 OR H
static void d_orh(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "OR");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[6]); // H
}

// D5 OR L
static void d_orl(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "OR");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[7]); // L
}

// E5 OR HL
static void d_orHL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "OR");
    i->set_r1(&regs[1]); // A
    i->set_rr1(&dregs[2]); // HL
}

// F5 OR A
static void d_ora(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "OR");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[1]); // A
}

// ----[ ORI xx ]----------------------------------------------------------------

// D7 ORI xx
static void d_ori(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "ORI");
    i->set_r1(&regs[1]); // A
}

// ----[ XOR R ]-------------------------------------------------------------------

// 06 XOR B
static void d_xorb(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "XOR");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[2]); // B
}

// 16 XOR C
static void d_xorc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "XOR");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[3]); // C
}

// 26 XOR D
static void d_xord(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "XOR");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[4]); // D
}

// 36 XOR E
static void d_xore(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "XOR");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[5]); // E
}

// 46 XOR H
static void d_xorh(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "XOR");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[6]); // H
}

// 56 XOR L
static void d_xorl(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "XOR");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[7]); // L
}

// 66 XOR HL
static void d_xorHL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "XOR");
    i->set_r1(&regs[1]); // A
    i->set_rr1(&dregs[2]); // HL
}

// 76 XOR A
static void d_xora(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "XOR");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[1]); // A
}

// ----[ XORI xx ]----------------------------------------------------------------

// E7 XORI xx
static void d_xori(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "XORI");
    i->set_r1(&regs[1]); // A
}

// ----[ CMP R ]-------------------------------------------------------------------

// 86 CMP B
static void d_cmpb(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMP");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[2]); // B
}

// 96 CMP C
static void d_cmpc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMP");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[3]); // C
}

// A6 CMP D
static void d_cmpd(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMP");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[4]); // D
}

// B6 CMP E
static void d_cmpe(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMP");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[5]); // E
}

// C6 CMP H
static void d_cmph(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMP");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[6]); // H
}

// D6 CMP L
static void d_cmpl(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMP");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[7]); // L
}

// E6 CMP HL
static void d_cmpHL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMP");
    i->set_r1(&regs[1]); // A
    i->set_rr1(&dregs[2]); // HL
}

// F6 CMP A
static void d_cmpa(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMP");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[1]); // A
}

// ----[ CMPI xx ]----------------------------------------------------------------

// F7 CMPI xx
static void d_cmpi(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMPI");
    i->set_r1(&regs[1]); // A
}

// ----[ CMPS R ]-----------------------------------------------------------------

// 0D CMPS B
static void d_cmpsb(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMPS");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[2]); // B
}

// 1D CMPS C
static void d_cmpsc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMPS");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[3]); // C
}

// 2D CMPS D
static void d_cmpsd(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMPS");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[4]); // D
}

// 3D CMPS E
static void d_cmpse(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMPS");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[5]); // E
}

// 4D CMPS H
static void d_cmpsh(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMPS");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[6]); // H
}

// 5D CMP L
static void d_cmpsl(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMPS");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[7]); // L
}

// 6D CMPS HL
static void d_cmpsHL(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMPS");
    i->set_r1(&regs[1]); // A
    i->set_rr1(&dregs[2]); // HL
}

// 7D CMPS A
static void d_cmpsa(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CMPS");
    i->set_r1(&regs[1]); // A
    i->set_r2(&regs[1]); // A
}

// ----[ I/O ]-------------------------------------------------------------------

// E0 SIN
static void d_sin(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "SIN");
    i->set_r1(&regs[1]); // A
}

// E1 SOUT
static void d_sout(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "SOUT");
    i->set_r1(&regs[1]); // A
}

// F0 CLRSCR
static void d_clrscr(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CLRSCR");
}

// F1 DRAW
static void d_draw(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "DRAW");
    i->set_r1(&regs[1]); // A
    i->set_imm8_0(regs[3].getValue()); // C -> X
    i->set_imm8_1(regs[2].getValue()); // B -> Y
}

/*
 * NOTES: I use only JMP and JMPCC for map near-jump instruction.
 * NJMP 54 --> remapped to JMP 00 54
 */

// ----[ JMP xxyy ]---------------------------------------------------------------

// 0F JMP yy xx
static void d_jmp(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "JMP");
    i->set_rr1(&dregs[4]); // PC
}

// ----[ JMPCC xxyy ]------------------------------------------------------------

// 1F-2F-3F-4F-5F-6F-7F-8F JMPCC
static void d_jmpcc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "JMPCC");
    i->set_rr1(&dregs[4]); // PC
    // Different exec()
}

// ----[ NJMP xx ]---------------------------------------------------------------

// 9F NJMP xx
static void d_njmp(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "NJMP");
    i->set_rr1(&dregs[4]); // PC
    i->set_imm8_1(0);
}

// ----[ NJMPCC xx ]------------------------------------------------------------

// AF-BF-CF-DF-EF-FF-EE-FE NJMPCC
static void d_njmpcc(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "NJMPCC");
    i->set_rr1(&dregs[4]); // PC
    i->set_imm8_1(0);
    // Different exec()
}

// ----[ CALL xxyy ]-------------------------------------------------------------

// 1E CALL yy xx
static void d_call(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "CALL");
    i->set_rr1(&dregs[4]); // PC
    i->set_rr2(&dregs[3]); // SP
}

// ----[ RET ]-------------------------------------------------------------------

// 0E RET
static void d_ret(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "RET");
    i->set_rr1(&dregs[4]); // PC
    i->set_rr2(&dregs[3]); // SP
}

// ----[ NOP ]-------------------------------------------------------------------

// 00 NOP
static void d_nop(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs){
    strcpy(i->name, "NOP");
}

static void init_d( void (*GATE[])(Instruction *i, Reg<uint8_t> *regs, DoubleReg<uint8_t> *dregs) ){
    
    std::fill_n(GATE, 0x100, &d_dummy);
    
    // LDI
    GATE[0x20] = d_ldib;       // 20 LDI B, xx
    GATE[0x30] = d_ldic;       // 30 LDI C, xx
    GATE[0x40] = d_ldid;       // 40 LDI D, xx
    GATE[0x50] = d_ldie;       // 50 LDI E, xx
    GATE[0x60] = d_ldih;       // 60 LDI H, xx
    GATE[0x70] = d_ldil;       // 70 LDI L, xx
    GATE[0x80] = d_ldiHL;      // 80 LDI (HL), xx
    GATE[0x90] = d_ldia;       // 90 LDI A, xx
    
    GATE[0x21] = d_ldxbc;      // 21 LDX BC, xxyy
    GATE[0x31] = d_ldxde;      // 31 LDX DE, xxyy
    GATE[0x41] = d_ldxhl;      // 41 LDX HL, xxyy
    GATE[0x22] = d_ldxsp;      // 22 LDX SP, xxyy
    
    // PUSH
    GATE[0x81] = d_pushb;       // 81 PUSH B
    GATE[0x91] = d_pushc;       // 91 PUSH C
    GATE[0xA1] = d_pushd;       // A1 PUSH D
    GATE[0xB1] = d_pushe;       // B1 PUSH E
    GATE[0xC1] = d_pushh;       // C1 PUSH H
    GATE[0xD1] = d_pushl;       // D1 PUSH L
    GATE[0xE1] = d_pushHL;      // E1 PUSH (HL)
    GATE[0xF1] = d_pusha;       // F1 PUSH A
    
    GATE[0x51] = d_pushbc;      // 51 PUSH BC
    GATE[0x61] = d_pushde;      // 61 PUSH DE
    GATE[0x71] = d_pushhl;      // 71 PUSH HL
    
    // POP
    GATE[0x82] = d_popb;       // 82 POP B
    GATE[0x92] = d_popc;       // 92 POP C
    GATE[0xA2] = d_popd;       // A2 POP D
    GATE[0xB2] = d_pope;       // B2 POP E
    GATE[0xC2] = d_poph;       // C2 POP H
    GATE[0xD2] = d_popl;       // D2 POP L
    GATE[0xC3] = d_popHL;      // C3 POP (HL)
    GATE[0xD3] = d_popa;       // D3 POP A
    
    GATE[0x52] = d_popbc;      // 52 POP BC
    GATE[0x62] = d_popde;      // 62 POP DE
    GATE[0x72] = d_pophl;      // 72 POP HL
    
    // MOV
    GATE[0x09] = d_movb_b;       // 09 MOV B, B
    GATE[0x19] = d_movb_c;       // 19 MOV B, C
    GATE[0x29] = d_movb_d;       // 29 MOV B, D
    GATE[0x39] = d_movb_e;       // 39 MOV B, E
    GATE[0x49] = d_movb_h;       // 49 MOV B, H
    GATE[0x59] = d_movb_l;       // 59 MOV B, L
    GATE[0x69] = d_movb_HL;      // 69 MOV B, (HL)
    GATE[0x79] = d_movb_a;       // 79 MOV B, A
    
    GATE[0x89] = d_movc_b;       // 89 MOV C, B
    GATE[0x99] = d_movc_c;       // 99 MOV C, C
    GATE[0xA9] = d_movc_d;       // A9 MOV C, D
    GATE[0xB9] = d_movc_e;       // B9 MOV C, E
    GATE[0xC9] = d_movc_h;       // C9 MOV C, H
    GATE[0xD9] = d_movc_l;       // D9 MOV C, L
    GATE[0xE9] = d_movc_HL;      // E9 MOV C, (HL)
    GATE[0xF9] = d_movc_a;       // F9 MOV C, A
    
    GATE[0x0A] = d_movd_b;       // 0A MOV D, B
    GATE[0x1A] = d_movd_c;       // 1A MOV D, C
    GATE[0x2A] = d_movd_d;       // 2A MOV D, D
    GATE[0x3A] = d_movd_e;       // 3A MOV D, E
    GATE[0x4A] = d_movd_h;       // 4A MOV D, H
    GATE[0x5A] = d_movd_l;       // 5A MOV D, L
    GATE[0x6A] = d_movd_HL;      // 6A MOV D, (HL)
    GATE[0x7A] = d_movd_a;       // 7A MOV D, A
    
    GATE[0x8A] = d_move_b;       // 8A MOV E, B
    GATE[0x9A] = d_move_c;       // 9A MOV E, C
    GATE[0xAA] = d_move_d;       // AA MOV E, D
    GATE[0xBA] = d_move_e;       // BA MOV E, E
    GATE[0xCA] = d_move_h;       // CA MOV E, H
    GATE[0xDA] = d_move_l;       // DA MOV E, L
    GATE[0xEA] = d_move_HL;      // EA MOV E, (HL)
    GATE[0xFA] = d_move_a;       // FA MOV E, A
    
    GATE[0x0B] = d_movh_b;       // 0B MOV H, B
    GATE[0x1B] = d_movh_c;       // 1B MOV H, C
    GATE[0x2B] = d_movh_d;       // 2B MOV H, D
    GATE[0x3B] = d_movh_e;       // 3B MOV H, E
    GATE[0x4B] = d_movh_h;       // 4B MOV H, H
    GATE[0x5B] = d_movh_l;       // 5B MOV H, L
    GATE[0x6B] = d_movh_HL;      // 6B MOV H, (HL)
    GATE[0x7B] = d_movh_a;       // 7B MOV H, A
    
    GATE[0x8B] = d_movl_b;       // 8B MOV L, B
    GATE[0x9B] = d_movl_c;       // 9B MOV L, C
    GATE[0xAB] = d_movl_d;       // AB MOV L, D
    GATE[0xBB] = d_movl_e;       // BB MOV L, E
    GATE[0xCB] = d_movl_h;       // CB MOV L, H
    GATE[0xDB] = d_movl_l;       // DB MOV L, L
    GATE[0xEB] = d_movl_HL;      // EB MOV L, (HL)
    GATE[0xFB] = d_movl_a;       // FB MOV L, A
    
    GATE[0x0C] = d_movHL_b;       // 0C MOV (HL), B
    GATE[0x1C] = d_movHL_c;       // 1C MOV (HL), C
    GATE[0x2C] = d_movHL_d;       // 2C MOV (HL), D
    GATE[0x3C] = d_movHL_e;       // 3C MOV (HL), E
    GATE[0x4C] = d_movHL_h;       // 4C MOV (HL), H
    GATE[0x5C] = d_movHL_l;       // 5C MOV (HL), L
    GATE[0x6C] = d_hcf;           // 6C HCF
    GATE[0x7C] = d_movHL_a;       // 7C MOV (HL), A
    
    GATE[0x8C] = d_mova_b;       // 8C MOV A, B
    GATE[0x9C] = d_mova_c;       // 9C MOV A, C
    GATE[0xAC] = d_mova_d;       // AC MOV A, D
    GATE[0xBC] = d_mova_e;       // BC MOV A, E
    GATE[0xCC] = d_mova_h;       // CC MOV A, H
    GATE[0xDC] = d_mova_l;       // DC MOV A, L
    GATE[0xEC] = d_mova_HL;      // EC MOV A, (HL)
    GATE[0xFC] = d_mova_a;       // FC MOV A, A
    
    GATE[0xED] = d_movhl_bc;       // ED MOV HL, BC
    GATE[0xFD] = d_movhl_de;       // FD MOV HL, DE
    
    // FLAG
    GATE[0x08] = d_clrflag;       // 08 CLRFLAG
    
    GATE[0x18] = d_setflag;       // 18 SETFLAG Z, 1
    GATE[0x28] = d_setflag;       // 28 SETFLAG Z, 0
    GATE[0x38] = d_setflag;       // 38 SETFLAG N, 1
    GATE[0x48] = d_setflag;       // 48 SETFLAG N, 0
    GATE[0x58] = d_setflag;       // 58 SETFLAG H, 1
    GATE[0x68] = d_setflag;       // 68 SETFLAG H, 0
    GATE[0x78] = d_setflag;       // 78 SETFLAG C, 1
    GATE[0x88] = d_setflag;       // 88 SETFLAG C, 0
    
    // ADD
    GATE[0x04] = d_addb;       // 04 ADD B
    GATE[0x14] = d_addc;       // 14 ADD C
    GATE[0x24] = d_addd;       // 24 ADD D
    GATE[0x34] = d_adde;       // 34 ADD E
    GATE[0x44] = d_addh;       // 44 ADD H
    GATE[0x54] = d_addl;       // 54 ADD L
    GATE[0x64] = d_addHL;      // 64 ADD (HL)
    GATE[0x74] = d_adda;       // 74 ADD A
    
    GATE[0xA7] = d_addi;       // A7 ADDI xx
    
    GATE[0x83] = d_addxbc;       // 83 ADDX BC
    GATE[0x93] = d_addxde;       // 93 ADDX DE
    GATE[0xA3] = d_addxhl;       // A3 ADDX HL
    
    // SUB
    GATE[0x84] = d_subb;       // 84 SUB B
    GATE[0x94] = d_subc;       // 94 SUB C
    GATE[0xA4] = d_subd;       // A4 SUB D
    GATE[0xB4] = d_sube;       // B4 SUB E
    GATE[0xC4] = d_subh;       // C4 SUB H
    GATE[0xD4] = d_subl;       // D4 SUB L
    GATE[0xE4] = d_subHL;      // E4 SUB (HL)
    GATE[0xF4] = d_suba;       // F4 SUB A
    
    GATE[0xB7] = d_subi;       // B7 SUBI xx
    
    // INC
    GATE[0x03] = d_incb;       // 03 INC B
    GATE[0x13] = d_incc;       // 13 INC C
    GATE[0x23] = d_incd;       // 23 INC D
    GATE[0x33] = d_ince;       // 33 INC E
    GATE[0x43] = d_inch;       // 43 INC H
    GATE[0x53] = d_incl;       // 53 INC L
    GATE[0x63] = d_incHL;      // 63 INC (HL)
    GATE[0x73] = d_inca;       // 73 INC A
    
    GATE[0xA8] = d_inxbc;      // A8 INX BC
    GATE[0xB8] = d_inxde;      // B8 INX DE
    GATE[0xC8] = d_inxhl;      // C8 INX HL
    
    // DEC
    GATE[0x07] = d_decb;       // 07 DEC B
    GATE[0x17] = d_decc;       // 17 DEC C
    GATE[0x27] = d_decd;       // 27 DEC D
    GATE[0x37] = d_dece;       // 37 DEC E
    GATE[0x47] = d_dech;       // 47 DEC H
    GATE[0x57] = d_decl;       // 57 DEC L
    GATE[0x67] = d_decHL;      // 67 DEC (HL)
    GATE[0x77] = d_deca;       // 77 DEC A
    
    // AND
    GATE[0x05] = d_andb;       // 05 AND B
    GATE[0x15] = d_andc;       // 15 AND C
    GATE[0x25] = d_andd;       // 25 AND D
    GATE[0x35] = d_ande;       // 35 AND E
    GATE[0x45] = d_andh;       // 45 AND H
    GATE[0x55] = d_andl;       // 55 AND L
    GATE[0x65] = d_andHL;      // 65 AND (HL)
    GATE[0x75] = d_anda;       // 75 AND A
    
    GATE[0xC7] = d_andi;       // C7 ANDI xx
    
    // OR
    GATE[0x85] = d_orb;       // 85 OR B
    GATE[0x95] = d_orc;       // 95 OR C
    GATE[0xA5] = d_ord;       // A5 OR D
    GATE[0xB5] = d_ore;       // B5 OR E
    GATE[0xC5] = d_orh;       // C5 OR H
    GATE[0xD5] = d_orl;       // D5 OR L
    GATE[0xE5] = d_orHL;      // E5 OR (HL)
    GATE[0xF5] = d_ora;       // F5 OR A
    
    GATE[0xD7] = d_ori;       // D7 ORI xx
    
    // XOR
    GATE[0x06] = d_xorb;       // 06 XOR B
    GATE[0x16] = d_xorc;       // 16 XOR C
    GATE[0x26] = d_xord;       // 26 XOR D
    GATE[0x36] = d_xore;       // 36 XOR E
    GATE[0x46] = d_xorh;       // 46 XOR H
    GATE[0x56] = d_xorl;       // 56 XOR L
    GATE[0x66] = d_xorHL;      // 66 XOR (HL)
    GATE[0x76] = d_xora;       // 76 XOR A
    
    GATE[0xE7] = d_xori;       // E7 XORI xx
    
    // CMP
    GATE[0x86] = d_cmpb;       // 86 CMP B
    GATE[0x96] = d_cmpc;       // 96 CMP C
    GATE[0xA6] = d_cmpd;       // A6 CMP D
    GATE[0xB6] = d_cmpe;       // B6 CMP E
    GATE[0xC6] = d_cmph;       // C6 CMP H
    GATE[0xD6] = d_cmpl;       // D6 CMP L
    GATE[0xE6] = d_cmpHL;      // E6 CMP (HL)
    GATE[0xF6] = d_cmpa;       // F6 CMP A
    
    GATE[0xF7] = d_cmpi;       // F7 CMPI xx
    
    // CMPS
    GATE[0x0D] = d_cmpsb;       // 0D CMPS B
    GATE[0x1D] = d_cmpsc;       // 1D CMPS C
    GATE[0x2D] = d_cmpsd;       // 2D CMPS D
    GATE[0x3D] = d_cmpse;       // 3D CMPS E
    GATE[0x4D] = d_cmpsh;       // 4D CMPS H
    GATE[0x5D] = d_cmpsl;       // 5D CMPS L
    GATE[0x6D] = d_cmpsHL;      // 6D CMPS (HL)
    GATE[0x7D] = d_cmpsa;       // 7D CMPS A
    
    // I/O
    GATE[0xE0] = d_sin;          // E0 SIN
    GATE[0xE1] = d_sout;         // E1 SOUT
    GATE[0xF0] = d_clrscr;       // F0 CLRSCR
    GATE[0xF1] = d_draw;         // F1 DRAW
    
    // JMP
    GATE[0x0F] = d_jmp;         // 0F JMP yy xx
    
    GATE[0x1F] = d_jmpcc;         // 1F JMPCC yy xx
    GATE[0x2F] = d_jmpcc;         // 2F JMPCC yy xx
    GATE[0x3F] = d_jmpcc;         // 3F JMPCC yy xx
    GATE[0x4F] = d_jmpcc;         // 4F JMPCC yy xx
    GATE[0x5F] = d_jmpcc;         // 5F JMPCC yy xx
    GATE[0x6F] = d_jmpcc;         // 6F JMPCC yy xx
    GATE[0x7F] = d_jmpcc;         // 7F JMPCC yy xx
    GATE[0x8F] = d_jmpcc;         // 8F JMPCC yy xx
    
    GATE[0x9F] = d_njmp;         // 9F NJMP xx
    
    GATE[0xAF] = d_njmpcc;         // AF NJMPCC xx
    GATE[0xBF] = d_njmpcc;         // BF NJMPCC xx
    GATE[0xCF] = d_njmpcc;         // CF NJMPCC xx
    GATE[0xDF] = d_njmpcc;         // DF NJMPCC xx
    GATE[0xEF] = d_njmpcc;         // EF NJMPCC xx
    GATE[0xFF] = d_njmpcc;         // FF NJMPCC xx
    GATE[0xEE] = d_njmpcc;         // EE NJMPCC xx
    GATE[0xFE] = d_njmpcc;         // FE NJMPCC xx
    
    // Func handling
    GATE[0x1E] = d_call;         // 1E CALL yy xx
    
    GATE[0x0E] = d_ret;            // 0E RET
    
    GATE[0x00] = d_nop;         // 00 NOP
    
}
