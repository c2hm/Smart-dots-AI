#include "Dot.h"
#include <SDL2/SDL.h>
#include <cmath>
using namespace std;

Dot::Dot(int x, int y, int wh, int ww)
{
    fPosX = x;
    fPosY = y;
    iWindowHeigth = wh;
    iWindowWidth = ww;

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
        VerifyDead();
    }

    Draw(renderer);

    if (bKill)
    {
        bDead = true;
    }
}

void Dot::Move()
{
       fPosX += pBrain->GetDirectionX(iStep);
       fPosY += pBrain->GetDirectionY(iStep);
       iStep++;     
}

void Dot::VerifyDead()
{
    if (fPosX < 0)
    {
        fPosX = 2;
        bKill = true;
    }
    else if (fPosX > iWindowHeigth)
    {
        fPosX = iWindowHeigth - 2;
        bKill = true;
    }
    if (fPosY < 0)
    {
        fPosY = 2;
        bKill = true;
    }
    else if (fPosY > iWindowWidth)
    {
        fPosY = iWindowWidth - 2;
        bKill = true;
    }

    if (iStep >= SIZE)
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



