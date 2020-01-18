//
//  Screen.cpp
//  chip9
//
//  Created by Matteo Zoia on 13/01/2020.
//  Copyright © 2020 Matteo Zoia. All rights reserved.
//

#include <iostream>
#pragma once

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
    Screen(){
        for(int i = 0; i < Y; i++)
            for(int j = 0; j < X; j++)
                screen[i][j] = Pixel();
    }
    
    void clear(){
        for(int i = 0; i < Y; i++)
            for(int j = 0; j < X; j++)
                screen[i][j].setPixel(0x00);
    }
    
    void setSegment(uint8_t val, uint8_t x, uint8_t y){
        
        int8_t sx = (int8_t)x;
        int8_t sy = (int8_t)y;
        
        for(int i = 0; i < 8; i++)
            if(((val >> (7 - i)) & 0x01) == 1)
                screen[sy][sx + i].setPixel(0xFF);
            else
                screen[sy][sx + i].setPixel(0x00);
    }

    uint8_t getPixel(int y, int x){
        return screen[y][x].getPixel();
    }
};
