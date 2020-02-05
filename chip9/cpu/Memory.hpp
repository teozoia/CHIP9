#include <iostream>

#ifndef CHIP9_MEMORY_HPP
#define CHIP9_MEMORY_HPP

const static int SIZE = 0x10000;

class Memory{
private:
    uint8_t memory[SIZE];

public:
    Memory() = default;
    
    uint8_t readb(int offset);
    uint16_t readw(int offset);
    
    void writeb(int offset, uint8_t data);
    void writew(int offset, uint16_t data);
    
    void show(int offset, int size);
    
    /* Read ROM from filename and loads bsize bytes of it in memory ad address addr */
    void loadrom(char filename[], uint16_t bsize, uint16_t addr);
    
};

#endif //CHIP9_MEMORY_HPP
