#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Population.h"

using namespace std;

SDL_Event event;
SDL_Renderer* r = NULL;
SDL_Window* window = NULL; 
Population pop(10, 200, 200);

#define HEIGTH 800
#define WIDTH 800

int main(int argc, char* argv[]) {


    SDL_Init(SDL_INIT_VIDEO);       // Initializing SDL as Video
    SDL_CreateWindowAndRenderer(WIDTH, HEIGTH, 0, &window, &r);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 0);      // setting draw color
    SDL_RenderClear(r);
    pop.Update(r);
    SDL_RenderPresent(r);    // Reflects the changes done in the window.

    

    while (!(event.type == SDL_QUIT)) {

        SDL_RenderClear(r);
        SDL_SetRenderDrawColor(r, 0, 0, 0, 0);      // setting draw color
        SDL_RenderClear(r);
        pop.Update(r);
        SDL_RenderPresent(r);    // Reflects the changes done in the window.

        SDL_Delay(10);
        SDL_PollEvent(&event);
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
