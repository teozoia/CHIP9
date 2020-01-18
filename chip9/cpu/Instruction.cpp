//
//  Instruction.cpp
//  CHIP9
//
//  Created by Matteo Zoia on 03/01/2020.
//  Copyright © 2020 Matteo Zoia. All rights reserved.
//

#include <iostream>
#include "Reg.cpp"
#include "DoubleReg.cpp"
#include "Memory.cpp"
#include "Screen.cpp"
#pragma once

class Instruction{
    
private:
    uint8_t opcode;
    Reg<uint8_t> *r1;
    Reg<uint8_t> *r2;
    DoubleReg<uint8_t> *rr1;
    DoubleReg<uint8_t> *rr2;
    DoubleReg<uint8_t> *rr3;
    Reg<uint8_t> *flag;
    uint8_t immediate8_0;
    uint8_t immediate8_1;
    
    Memory *mem;
    Screen *scr;
    
public:
    char name[10];
    
    Instruction() = default;
    
    void clear(){
        strncpy(this->name, "NONE", 5);
        this->opcode = 0;
        this->r1 = NULL;
        this->r2 = NULL;
        this->rr1 = NULL;
        this->rr2 = NULL;
        this->rr3 = NULL;
        this->immediate8_0 = 0;
        this->immediate8_1 = 0;
    }
    
    char *get_name(){
        return name;
    }
    
    uint8_t get_opcode(){
        return this->opcode;
    }
    
    Reg<uint8_t> *get_r1(){
        return this->r1;
    }
    
    Reg<uint8_t> *get_r2(){
        return this->r2;
    }
    
    DoubleReg<uint8_t> *get_rr1(){
        return this->rr1;
    }
    
    DoubleReg<uint8_t> *get_rr2(){
        return this->rr2;
    }
    
    DoubleReg<uint8_t> *get_rr3(){
        return this->rr3;
    }
    
    Reg<uint8_t> *get_flag(){
        return this->flag;
    }
    
    uint8_t get_imm8_0(){
        return this->immediate8_0;
    }
    
    uint8_t get_imm8_1(){
        return this->immediate8_1;
    }
    
    Memory *get_mem(){
        return mem;
    }
    
    Screen *get_scr(){
        return scr;
    }
    
    void set_opcode(uint8_t o){
        this->opcode = o;
    }
    
    void set_r1(Reg<uint8_t> *r){
        this->r1 = r;
    }
    
    void set_r2(Reg<uint8_t> *r){
        this->r2 = r;
    }
    
    void set_rr1(DoubleReg<uint8_t> *r){
        this->rr1 = r;
    }
    
    void set_rr2(DoubleReg<uint8_t> *r){
        this->rr2 = r;
    }
    
    void set_rr3(DoubleReg<uint8_t> *r){
        this->rr3 = r;
    }
    
    void set_flag(Reg<uint8_t> *r){
        this->flag = r;
    }
    
    void set_imm8_0(uint8_t i){
        this->immediate8_0 = i;
    }
    
    void set_imm8_1(uint8_t i){
        this->immediate8_1 = i;
    }
    
    void set_mem(Memory *m){
        this->mem = m;
    }
    
    void set_scr(Screen *s){
        this->scr = s;
    }
    
    void print(){
        printf(">>> %s OP: 0x%02x, R1: %s, R2: %s, RR1: %s, RR2: %s, RR3: %s, FLAG: 0x%02x Imm: 0x%02x-%02x\n",
               this->name,
               this->opcode,
               this->r1->getName(),
               this->r2->getName(),
               this->rr1->getName(),
               this->rr2->getName(),
               this->rr3->getName(),
               this->flag->getValue(),
               this->immediate8_1,
               this->immediate8_0);
    }

    void disass(){
        printf("(%02x %02x%02x) %s 0x%02x-%02x\n",
                this->opcode,
                this->immediate8_0,
                this->immediate8_1,
                this->name,
                this->immediate8_1,
                this->immediate8_0);
    }
};

