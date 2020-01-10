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
    // Different exec(), but immediate8_0 = 0/1
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
    // B -> X
    // C -> y
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
