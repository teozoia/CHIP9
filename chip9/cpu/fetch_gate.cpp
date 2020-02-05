#include <stdio.h>
#include "Instruction.hpp"
#pragma once

static void noparam(DoubleReg<uint8_t> *pc, Instruction *i){
    return;
}

static void param_single(DoubleReg<uint8_t> *pc, Instruction *i){
    i->set_imm8_0(i->get_mem()->readw(getD(pc)));
    setD(pc, getD(pc) + 1);
}

static void param_double(DoubleReg<uint8_t> *pc, Instruction *i){
    param_single(pc, i);

    i->set_imm8_1(i->get_mem()->readw(getD(pc)));
    setD(pc, getD(pc) + 1);
}

static void init_f( void (*GATE[])(DoubleReg<uint8_t> *pc, Instruction *i) ) {

    std::fill_n(GATE, 0x100, &noparam);

    GATE[0x20] = param_single;
    GATE[0x30] = param_single;
    GATE[0x40] = param_single;
    GATE[0x50] = param_single;
    GATE[0x60] = param_single;
    GATE[0x80] = param_single;
    GATE[0x90] = param_single;
    GATE[0x9F] = param_single;
    GATE[0xAF] = param_single;
    GATE[0xBF] = param_single;
    GATE[0xCF] = param_single;
    GATE[0xDF] = param_single;
    GATE[0xEF] = param_single;
    GATE[0xFF] = param_single;
    GATE[0xEE] = param_single;
    GATE[0xFE] = param_single;
    GATE[0xE7] = param_single;
    GATE[0xF7] = param_single;
    GATE[0xA7] = param_single;
    GATE[0xB7] = param_single;
    GATE[0xC7] = param_single;
    GATE[0xD7] = param_single;

    GATE[0x21] = param_double;
    GATE[0x31] = param_double;
    GATE[0x41] = param_double;
    GATE[0x22] = param_double;
    GATE[0x0F] = param_double;
    GATE[0x1F] = param_double;
    GATE[0x2F] = param_double;
    GATE[0x3F] = param_double;
    GATE[0x4F] = param_double;
    GATE[0x5F] = param_double;
    GATE[0x6F] = param_double;
    GATE[0x7F] = param_double;
    GATE[0x8F] = param_double;
    GATE[0x1E] = param_double;

}

