#include "Dot.h"
#include <SDL2/SDL.h>
#include <cmath>
using namespace std;

Dot::Dot(int x, int y)
{
    posX = x;
    posY = y;

    pBrain = new Brain(1000);
}

Dot::~Dot() 
{
    delete pBrain;
}

void Dot::Update(SDL_Renderer* renderer)
{
    Move();
    Draw(renderer);
}

void Dot::Move()
{
    if (step < size)
    {
       posX += pBrain->GetDirectionX(step);
       posY += pBrain->GetDirectionY(step);
       step++;
    }
}

void Dot::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);

    // Drawing circle
    for (float x = posX - radius; x <= posX + radius; x++)
    {
        for (float y = posY - radius; y <= posY + radius; y++)
        {
            if ((pow(posY - y, 2) + pow(posX - x, 2)) <= pow(radius, 2))
            {
                x = (int)x;
                y = (int)y;
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}



