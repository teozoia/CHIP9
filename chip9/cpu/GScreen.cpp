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

        window = SDL_CreateWindow(title, XPOS, YPOS, width, height, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // RGB-Alpha
            SDL_RenderClear(renderer);
        }


        for(int i = 0; i < Y; i++){
            for(int j = 0; j < X; j++){
                rects[i][j] = {(4 * j), (4 * i), 4, 4};
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rects[i][j]);
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

    SDL_RenderClear(renderer);
}

void GScreen::update(){


    for(int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            if (screen->getPixel(i, j) == 1)
                SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
            else
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rects[i][j]);
        }
    }
}

bool GScreen::running() {
    return isRunning;
}

void GScreen::render(){
    SDL_RenderPresent(renderer);
}

void GScreen::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}


