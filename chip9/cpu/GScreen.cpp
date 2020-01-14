//
//  GScreen.cpp
//  CHIP9
//
//  Created by Matteo Zoia on 14/01/2020.
//  Copyright © 2020 Matteo Zoia. All rights reserved.
//

#include "GScreen.hpp"

GScreen::GScreen(){
    width = 512;
    height = 256;
}

GScreen::~GScreen(){}

void GScreen::init(const char *title, Screen *s){

    // Setting model
    screen = s;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){

        std::cout << "Subsystem initialized" << std::endl;

        window = SDL_CreateWindow(title, XPOS, YPOS, width, height, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);

        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // RGB-Alpha
        }

        for(int i = 0; i < Y; i++){
            for(int j = 0; j < X; j++){
                rects[i][j] = {(4 * j), (4 * i), 4, 4};
                SDL_RenderFillRect(renderer, &rects[i][j]);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
        }

        SDL_RenderPresent(renderer);

        isRunning = true;
    }else{
        isRunning = false;
    }
}

void GScreen::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void GScreen::update(){
    SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
    SDL_RenderFillRect(renderer, &rects[50][20]);
    
}

bool GScreen::running() {
    return isRunning;
}

void GScreen::render(){
    //SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void GScreen::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void GScreen::cycle() {

    while(running()){
        handleEvents();
        update();
        render();
    }
}


