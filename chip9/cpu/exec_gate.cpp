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

static void ldxsp(Instruction *i){
    i->get_rr1()->set(i->get_imm8_1(), i->get_imm8_0());
}

static void xor_(Instruction *i){
    Reg<uint8_t> *a = i->get_r1();
    Reg<uint8_t> *r = i->get_r2();
    a->set(a->getValue() xor r->getValue());
}

static void jmp(Instruction *i){
    i->get_rr1()->set(i->get_imm8_1(), i->get_imm8_0());
}
