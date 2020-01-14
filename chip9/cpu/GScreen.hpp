//
//  GScreen.hpp
//  CHIP9
//
//  Created by Matteo Zoia on 14/01/2020.
//  Copyright © 2020 Matteo Zoia. All rights reserved.
//

#ifndef GScreen_hpp
#define GScreen_hpp

#include "Screen.cpp"
#include <SDL2/SDL.h>
#include <iostream>

static const int XPOS = SDL_WINDOWPOS_CENTERED;
static const int YPOS = SDL_WINDOWPOS_CENTERED;

class GScreen{

private:
    int width;
    int height;
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Mirroring of legacy screen
    SDL_Rect rects[Y][X];
    Screen *screen;

public:
    GScreen();
    ~GScreen();
    
    void init(const char *title, Screen *s);
    
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running();
    void cycle();
};

#endif /* GScreen_hpp */
