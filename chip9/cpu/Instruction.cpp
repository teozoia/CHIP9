#include "Instruction.hpp"

void Instruction::clear(){
    strncpy(this->name, "NONE", 5);
    this->opcode = 0;
    this->r1 = NULL;
    this->r2 = NULL;
    this->rr1 = NULL;
    this->rr2 = NULL;
    this->immediate8_0 = 0;
    this->immediate8_1 = 0;
}

uint8_t Instruction::get_opcode(){
    return this->opcode;
}

Reg<uint8_t> *Instruction::get_r1(){
    return this->r1;
}

Reg<uint8_t> *Instruction::get_r2(){
    return this->r2;
}

DoubleReg<uint8_t> *Instruction::get_rr1(){
    return this->rr1;
}

DoubleReg<uint8_t> *Instruction::get_rr2(){
    return this->rr2;
}

Reg<uint8_t> *Instruction::get_flag(){
    return this->flag;
}

uint8_t Instruction::get_imm8_0(){
    return this->immediate8_0;
}

uint8_t Instruction::get_imm8_1(){
    return this->immediate8_1;
}

Memory *Instruction::get_mem(){
    return mem;
}

Screen *Instruction::get_scr(){
    return scr;
}

void Instruction::set_opcode(uint8_t o){
    this->opcode = o;
}

void Instruction::set_r1(Reg<uint8_t> *r){
    this->r1 = r;
}

void Instruction::set_r2(Reg<uint8_t> *r){
    this->r2 = r;
}

void Instruction::set_rr1(DoubleReg<uint8_t> *r){
    this->rr1 = r;
}

void Instruction::set_rr2(DoubleReg<uint8_t> *r){
    this->rr2 = r;
}

void Instruction::set_flag(Reg<uint8_t> *r){
    this->flag = r;
}

void Instruction::set_imm8_0(uint8_t i){
    this->immediate8_0 = i;
}

void Instruction::set_imm8_1(uint8_t i){
    this->immediate8_1 = i;
}

void Instruction::set_mem(Memory *m){
    this->mem = m;
}

void Instruction::set_scr(Screen *s){
    this->scr = s;
}

void Instruction::print(){
    printf(">>> %s OP: 0x%02x, R1: %s, R2: %s, RR1: %s, RR2: %s, FLAG: 0x%02x Imm: 0x%02x-%02x\n",
            this->name,
            this->opcode,
            this->r1->getName(),
            this->r2->getName(),
            this->rr1->getName(),
            this->rr2->getName(),
            this->flag->getValue(),
            this->immediate8_1,
            this->immediate8_0);
}
