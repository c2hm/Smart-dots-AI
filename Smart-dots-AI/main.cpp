#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Population.h"
#include "Field.h"

using namespace std;

SDL_Event event;
SDL_Renderer* r = NULL;
SDL_Window* window = NULL; 
Field field(400, 100);
Population pop(&field, 100, 375, 700);

int main(int argc, char* argv[]) {


    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGTH, 0, &window, &r);

    field.AddObstacle(150, 150, 50, 50);
    field.AddObstacle(400, 600, 50, 50);
    field.AddObstacle(300, 700, 50, 50);

    while (!(event.type == SDL_QUIT)) {

        SDL_SetRenderDrawColor(r, 0, 0, 0, 0); 
        SDL_RenderClear(r);
        field.Update(r);
        pop.Update(r);
        SDL_RenderPresent(r);  

        SDL_Delay(50);
        SDL_PollEvent(&event);
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
