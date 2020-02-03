#include "Screen.hpp"

Screen::Screen(){

    for(int i = 0; i < Y; i++)
        for(int j = 0; j < X; j++)
            screen[i][j] = Pixel();
}

void Screen::clear(){

    for(int i = 0; i < Y; i++)
        for(int j = 0; j < X; j++)
            screen[i][j].setPixel(0x00);
}

void Screen::setSegment(uint8_t val, uint8_t x, uint8_t y){

    int8_t sx = (int8_t)x;
    int8_t sy = (int8_t)y;

    for(int i = 0; i < 8; i++)
        if(((val >> (7 - i)) & 0x01) == 1)
            screen[sy][sx + i].setPixel(0xFF);
        else
            screen[sy][sx + i].setPixel(0x00);
}

uint8_t Screen::getPixel(int y, int x){
    return screen[y][x].getPixel();
}