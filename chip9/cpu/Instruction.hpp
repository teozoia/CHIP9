#include <iostream>
#include "Reg.hpp"
#include "DoubleReg.hpp"
#include "Memory.hpp"
#include "Screen.hpp"

#ifndef CHIP9_INSTRUCTION_HPP
#define CHIP9_INSTRUCTION_HPP

class Instruction{
    
private:
    uint8_t opcode;
    Reg<uint8_t> *r1;
    Reg<uint8_t> *r2;
    DoubleReg<uint8_t> *rr1;
    DoubleReg<uint8_t> *rr2;
    Reg<uint8_t> *flag;
    uint8_t immediate8_0;
    uint8_t immediate8_1;
    
    Memory *mem;
    Screen *scr;
    
public:
    char name[10];
    
    Instruction() = default;
    void clear();

    uint8_t get_opcode();
    Reg<uint8_t> *get_r1();
    Reg<uint8_t> *get_r2();
    DoubleReg<uint8_t> *get_rr1();
    DoubleReg<uint8_t> *get_rr2();
    Reg<uint8_t> *get_flag();
    uint8_t get_imm8_0();
    uint8_t get_imm8_1();

    Memory *get_mem();
    Screen *get_scr();
    
    void set_opcode(uint8_t o);
    void set_r1(Reg<uint8_t> *r);
    void set_r2(Reg<uint8_t> *r);
    void set_rr1(DoubleReg<uint8_t> *r);
    void set_rr2(DoubleReg<uint8_t> *r);
    void set_flag(Reg<uint8_t> *r);
    void set_imm8_0(uint8_t i);
    void set_imm8_1(uint8_t i);

    void set_mem(Memory *m);
    void set_scr(Screen *s);
    
    void print();
};


#endif //CHIP9_INSTRUCTION_HPP

