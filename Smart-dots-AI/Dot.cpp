#include "Dot.h"
#include <SDL2/SDL.h>
#include <cmath>

using namespace std;

Dot::Dot(Field* pF, int x, int y)
{
    fPosX = x;
    fPosY = y;

    pField = pF;
    pBrain = new Brain(1000);
}

Dot::~Dot() 
{
    delete pBrain;
}

void Dot::Update(SDL_Renderer* renderer)
{
    if (!bDead)
    {
        Move();
    }

    Draw(renderer);
}

void Dot::Move()
{
    fPosX += pBrain->GetDirectionX(iStep);
    fPosY += pBrain->GetDirectionY(iStep);
    iStep++;    

    if (iStep >= SIZE || pField->GetCollision((int)fPosX, (int)fPosY, &bGoal))
    {
        bDead = true;
    }
}


void Dot::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);

    // Drawing circle
    for (float x = fPosX - RADIUS; x <= fPosX + RADIUS; x++)
    {
        for (float y = fPosY - RADIUS; y <= fPosY + RADIUS; y++)
        {
            if ((pow(fPosY - y, 2) + pow(fPosX - x, 2)) <= pow(RADIUS, 2))
            {
                SDL_RenderDrawPoint(renderer, (int)x, (int)y);
            }
        }
    }
}



