#include "Memory.hpp"

uint8_t Memory::readb(int offset){
    return this->memory[offset];
}

uint16_t Memory::readw(int offset){
    // Little-endian
    return ((uint16_t)readb(offset + 1) << 8) | (uint16_t)readb(offset);
}

void Memory::writeb(int offset, uint8_t data){
    this->memory[offset] = data;
}

void Memory::writew(int offset, uint16_t data){
    // Little-endian
    writeb(offset, (uint8_t)data);
    writeb(offset + 1, (uint8_t)(data >> 8));
}

void Memory::show(int offset, int size){
    for(int i = offset + (offset % 2); i < offset + size; i = i + 2)
        printf("0x%04x: %02x %02x\n", i, readb(i), readb(i + 1));
}

void Memory::loadrom(char filename[], uint16_t bsize, uint16_t addr){

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
