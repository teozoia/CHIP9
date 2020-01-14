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


class Screen{
    
private:
    char screen[Y][X];
    
public:
    Screen(){ clear(); }
    
    void clear(){
        for(int i = 0; i < Y; i++)
            for(int j = 0; j < X; j++)
                screen[i][j] = ' ';
    }
    
    void setSegment(uint8_t val, uint8_t x, uint8_t y){
        
        int8_t sx = (int8_t)x;
        int8_t sy = (int8_t)y;
        
        for(int i = 0; i < 8; i++)
            if((val >> (8 - i)) == 1)
                screen[sy][sx + i] = '*';
            else
                screen[sy][sx + i] = ' ';
        
        printf("Setting segemnt of screen\n");
    }
    
    void show(){
        for(int i = 0; i < Y; i++){
            for(int j = 0; j < X; j++)
                printf("%c", screen[i][j]);
            printf("\n");
        }
    }
};
