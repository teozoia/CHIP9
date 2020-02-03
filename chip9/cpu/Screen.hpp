#include <iostream>

#ifndef CHIP9_SCREEN_HPP
#define CHIP9_SCREEN_HPP

/*
 * From Section 1: "System feature", subsection 1.1: "Specification"
 * Screen resolution 128x64 1-bit pixels, @60Hz
 */

static const int X = 128;
static const int Y = 64;

/* Pixel class has been created for optimization by setting every uint8_t pixel to size 1-bit */
class Pixel{
private:
    uint8_t pixel:1;
public:
    Pixel(){ pixel = 0; }
    void setPixel(uint8_t v){ pixel = v; }
    uint8_t getPixel(){ return pixel; }
};


class Screen{
    
private:
    Pixel screen[Y][X];

public:
    Screen();
    
    void clear();
    void setSegment(uint8_t val, uint8_t x, uint8_t y);
    uint8_t getPixel(int y, int x);

};

#endif //CHIP9_SCREEN_HPP
