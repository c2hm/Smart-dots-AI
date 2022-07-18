#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Population.h"
#include "Field.h"
#include <time.h> 
#include <string>

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


    TTF_Init();
    TTF_Font* pFont = TTF_OpenFont("H:/Code perso/Smart-dots-AI/ressources/font.ttf", 24);
    SDL_Color White = { 255, 255, 255 };
    SDL_Rect Message_rect;
    Message_rect.x = 25;
    Message_rect.y = 25; 
    Message_rect.w = 100;
    Message_rect.h = 25; 

    //field.AddObstacle(200, 150, 200, 400);
    field.AddObstacle(300, 100, 200, 50);
    field.AddObstacle(500, 100, 200, 50);
    field.AddObstacle(400, 450, 200, 50);
    field.AddObstacle(300, 550, 50, 300);

    frameTimer = SDL_GetTicks();

    while (!(event.type == SDL_QUIT)) {

        if (state == STATE_UPDATE)
        {
            SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
            SDL_RenderClear(r);

            field.Update(r);
            pop.Update(r);

            string text = "Gen : ";
            text += to_string(pop.GetGeneration());
            SDL_Surface*  surfaceMessage = TTF_RenderText_Solid(pFont, text.c_str(), White);
            SDL_Texture* Message = SDL_CreateTextureFromSurface(r, surfaceMessage);
            SDL_RenderCopy(r, Message, NULL, &Message_rect);
            SDL_FreeSurface(surfaceMessage);
            SDL_DestroyTexture(Message);

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
