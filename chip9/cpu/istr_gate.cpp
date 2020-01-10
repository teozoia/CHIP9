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
    i->set_rr1(&dregs[3]); // SP
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
    i->set_r2(&regs[0]); // A
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

/* TODO */

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
