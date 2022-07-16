#include "Dot.h"
#include <SDL2/SDL.h>
#include <cmath>

using namespace std;

static const int MAX_VELOCITY = 6;
static const int SIZE = 350;
static const int RADIUS = 3;

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
    fAccX += pBrain->GetDirectionX(iStep);
    fAccY += pBrain->GetDirectionY(iStep);
    iStep++;  

    fVelX += fAccX;
    fVelY += fAccY;

    float fVelNorme = sqrt(fVelX*fVelX + fVelY*fVelY);

    if (fVelNorme >= MAX_VELOCITY)
    {
        fVelX = fVelX / fVelNorme * MAX_VELOCITY;
        fVelY = fVelY / fVelNorme * MAX_VELOCITY;
    }



    fPosX += fVelX;
    fPosY += fVelY;

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




