#ifndef CHIP9_GSCREEN_HPP
#define CHIP9_GSCREEN_HPP

#include <iostream>
#include "Screen.hpp"
#include <SDL2/SDL.h>

static const int XPOS = SDL_WINDOWPOS_CENTERED;
static const int YPOS = SDL_WINDOWPOS_CENTERED;

class GScreen{

private:
    int width;
    int height;
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Rect rects[Y][X];
    Screen *screen;

public:
    GScreen();
    
    void init(const char *title, Screen *s);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running();
};

#endif // CHIP9_GSCREEN_HPP
