#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Population.h"
#include "Field.h"
#include <time.h> 

using namespace std;

const int STATE_UPDATE = 0;
const int STATE_UPDATED = 1;
const int STATE_PRESENT = 3;
const int FRAME_RATE = 50;

SDL_Event event;
SDL_Renderer* r = NULL;
SDL_Window* window = NULL; 
Field field(400, 100);
Population pop(&field, 2000, 375, 700);
uint32_t frameTimer;
int state = STATE_UPDATE;

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGTH, 0, &window, &r);

    field.AddObstacle(150, 150, 50, 200);
    field.AddObstacle(400, 500, 200, 50);
    field.AddObstacle(300, 600, 50, 300);

    frameTimer = SDL_GetTicks();

    while (!(event.type == SDL_QUIT)) {

        if (state == STATE_UPDATE)
        {
            SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
            SDL_RenderClear(r);
            field.Update(r);
            pop.Update(r);
            state = STATE_UPDATED;
        }
        else if (state == STATE_UPDATED)
        {
            if (SDL_GetTicks() - frameTimer > FRAME_RATE)
            {
                state = STATE_PRESENT;
            }
        }
        else if (state == STATE_PRESENT)
        {
            SDL_RenderPresent(r);
            frameTimer = SDL_GetTicks();
            state = STATE_UPDATE;

        }

        SDL_PollEvent(&event);
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
