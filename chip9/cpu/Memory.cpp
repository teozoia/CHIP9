//
//  Memory.cpp
//  chip9
//
//  Created by Matteo Zoia on 30/12/2019.
//  Copyright © 2019 Matteo Zoia. All rights reserved.
//

#include <iostream>
#pragma once

const static int SIZE = 0x10000;

class Memory{
private:
    uint8_t memory[SIZE];

public:
    Memory() = default;
    
    uint8_t readb(int offset){
        return this->memory[offset];
    }
    
    uint16_t readw(int offset){
        // Little-endian
        return ((uint16_t)readb(offset + 1) << 8) | (uint16_t)readb(offset);
    }
    
    void writeb(int offset, uint8_t data){
        this->memory[offset] = data;
    }
    
    void writew(int offset, uint16_t data){
        // Little-endian
        writeb(offset, (uint8_t)data);
        writeb(offset + 1, (uint8_t)(data >> 8));
    }
    
    void show(int offset, int size){
        for(int i = offset + (offset % 2); i < size; i = i + 2)
            printf("0x%04x: %02x %02x\n", i, readb(i), readb(i + 1));
    }
    
    /* Read ROM from filename and loads bsize bytes of it in memory ad address addr */
    void loadrom(char filename[], uint16_t bsize, uint16_t addr){

        FILE *file = fopen(filename, "r");
        uint8_t b;
        uint16_t i = 0;
        
        if(file == NULL)
            printf("Can't open ROM! Check the path dude\n");
        else
            do{
                b = (uint8_t)fgetc(file);
                writeb(addr + i, b);
                i++;
            } while(i < bsize);

    }
    
};
