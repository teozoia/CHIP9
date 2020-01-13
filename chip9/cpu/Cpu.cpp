//
//  Cpu.cpp
//  CHIP9
//
//  Created by Matteo Zoia on 30/12/2019.
//  Copyright © 2019 Matteo Zoia. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Memory.cpp"
#include "exec_gate.cpp"
#include "istr_gate.cpp"
#pragma once

static const int N_REGS = 12;
static const int N_DREGS = 5;

static const uint8_t GPR_DEFAULT = 0xAA;
static const uint8_t FLAG_DEFAULT = 0x00;
static const uint8_t I_DEFAULT = 0x00; // I (P)
static const uint8_t X_DEFAULT = 0x00; // X (C)
static char REG_NAME[12][5] = {"F","A","B","C","D","E","H","L","S","P","I","X"};

class Cpu{
    
private:
    char name[10];
    
    Reg<uint8_t> gpregs[N_REGS]; /* [ F, A, B, C, D, E, H, L, S, P, I, X ] */
    DoubleReg<uint8_t> dregs[N_DREGS]; /* [ BC, DE, HL, SP, IX(PC) ] */
    Memory memory;
    Instruction istr;
    
    DoubleReg<uint8_t> *pc; /* Alias to PC */
    DoubleReg<uint8_t> *sp; /* Alias to SP */
    Reg<uint8_t> *flag; /* Alias to FLAG */
    
    void (*ISTRGATE[0x100])(Instruction *i, Reg<uint8_t> *r, DoubleReg<uint8_t> *dr);
    void (*EXECGATE[0x100])(Instruction *i);

    
    void fetch_param(uint8_t *p, Memory *m, DoubleReg<uint8_t> *pc){
        uint8_t tmp = m->readw(getD(pc));
        memcpy(p, &tmp, sizeof(uint8_t));
        setD(pc, getD(pc) + 1);
    }
        
public:
    Cpu(){
        strncpy(name, "CHIP9-CPU", 10);
        
        gpregs[0] = Reg<uint8_t>(FLAG_DEFAULT, REG_NAME[0]); /* F */
        gpregs[1] = Reg<uint8_t>(GPR_DEFAULT, REG_NAME[1]); /* A */
        gpregs[2] = Reg<uint8_t>(GPR_DEFAULT, REG_NAME[2]); /* B */
        gpregs[3] = Reg<uint8_t>(GPR_DEFAULT, REG_NAME[3]); /* C */
        gpregs[4] = Reg<uint8_t>(GPR_DEFAULT, REG_NAME[4]); /* D */
        gpregs[5] = Reg<uint8_t>(GPR_DEFAULT, REG_NAME[5]); /* E */
        gpregs[6] = Reg<uint8_t>(GPR_DEFAULT, REG_NAME[6]); /* H */
        gpregs[7] = Reg<uint8_t>(GPR_DEFAULT, REG_NAME[7]); /* L */
        gpregs[8] = Reg<uint8_t>(GPR_DEFAULT, REG_NAME[8]); /* S */
        gpregs[9] = Reg<uint8_t>(GPR_DEFAULT, REG_NAME[9]); /* P */
        gpregs[10] = Reg<uint8_t>(I_DEFAULT, REG_NAME[10]); /* I */
        gpregs[11] = Reg<uint8_t>(X_DEFAULT, REG_NAME[11]); /* X */
        
        dregs[0] = DoubleReg<uint8_t>(&gpregs[2], &gpregs[3]); /* BC */
        dregs[1] = DoubleReg<uint8_t>(&gpregs[4], &gpregs[5]); /* DE */
        dregs[2] = DoubleReg<uint8_t>(&gpregs[6], &gpregs[7]); /* HL */
        dregs[3] = DoubleReg<uint8_t>(&gpregs[8], &gpregs[9]); /* SP */
        dregs[4] = DoubleReg<uint8_t>(&gpregs[10], &gpregs[11]); /* IX(PC) */
        
        // Set aliases
        pc = &dregs[4];
        sp = &dregs[3];
        flag = &gpregs[0];
        
        memory = Memory();
        
        istr.set_flag(flag);
        istr.set_mem(&memory);
        
        init_d(ISTRGATE);
        init_e(EXECGATE);
        
    }
    
    void status(){
        
        printf("CPU Regs:\n");
        printf("%s: 0x%02x (%d), %s: 0x%02x (%d), %s: 0x%02x (%d), %s: 0x%02x (%d)\n", gpregs[0].getName(), gpregs[0].getValue(), gpregs[0].getValue(), gpregs[1].getName(), gpregs[1].getValue(), gpregs[1].getValue(), gpregs[2].getName(), gpregs[2].getValue(), gpregs[2].getValue(), gpregs[3].getName(), gpregs[3].getValue(), gpregs[3].getValue());
        printf("%s: 0x%02x (%d), %s: 0x%02x (%d), %s: 0x%02x (%d), %s: 0x%02x (%d)\n", gpregs[4].getName(), gpregs[4].getValue(), gpregs[4].getValue(), gpregs[5].getName(), gpregs[5].getValue(), gpregs[5].getValue(), gpregs[6].getName(), gpregs[6].getValue(), gpregs[6].getValue(), gpregs[7].getName(), gpregs[7].getValue(), gpregs[7].getValue());
        
        dregs[0].print();
        printf(", ");
        dregs[1].print();
        printf(", ");
        dregs[2].print();
        printf("\n");
        
        dregs[3].print();
        printf(" | ");
        dregs[4].print();
        printf("\n\n");
            
    }
    
    void show_memory(int offset, int size){
        /* Wrapper to function show */
        this->memory.show(offset, size);
    }
    
    void loadrom(char filename[], int bsize, int addr){
        /* Wrapper to loadrom furnction of Memory class */
        this->memory.loadrom(filename, bsize, addr);
    }
    
    /* Need refactoring */
    void fetch(){
        uint8_t opcode = 0x00;
        uint8_t param = 0x00;
        
        this->istr.clear();
        opcode = this->memory.readb(getD(pc));
        this->istr.set_opcode(opcode);
        setD(pc, getD(pc) + 1);
        
        switch(opcode){
            case 0x20: case 0x30: case 0x40: case 0x50:
            case 0x60: case 0x80: case 0x90:
            case 0x9F: case 0xAF: case 0xBF: case 0xCF:
            case 0xDF: case 0xEF: case 0xFF: case 0xEE:
            case 0xFE:
            case 0xE7: case 0xF7: case 0xA7: case 0xB7:
            case 0xC7: case 0xD7:
                fetch_param(&param, &this->memory, pc);
                this->istr.set_imm8_0(param);
                break;
            
            case 0x21: case 0x31: case 0x41: case 0x22:
            case 0x0F: case 0x1F: case 0x2F: case 0x3F:
            case 0x4F: case 0x5F: case 0x6F: case 0x7F:
            case 0x8F: case 0x1E:
                fetch_param(&param, &this->memory, pc);
                this->istr.set_imm8_0(param);
                fetch_param(&param, &this->memory, pc);
                this->istr.set_imm8_1(param);
                break;
        }
        //this->istr.print();
    }
    
    void decode(){
        /* Wrapper to specifical decode function based on opcode */
        ISTRGATE[istr.get_opcode()](&istr, gpregs, dregs);
        //this->istr.print();
        printf("IX(PC): 0x%04x\n",getD(pc));
    }
    
    void execute(){
        /* Wrapper to real instruction (jump table) */
        EXECGATE[istr.get_opcode()](&istr);
    }
    
};
