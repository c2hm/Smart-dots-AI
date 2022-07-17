#include "Dot.h"
#include <SDL2/SDL.h>
#include <cmath>

using namespace std;

static const int MAX_VELOCITY = 20;
static const int SIZE = 350;
static const int RADIUS = 4;

Dot::Dot(Field* pF, int x, int y)
{
    iStartPosX = x;
    iStartPosY = y;
    fPosX = iStartPosX;
    fPosY = iStartPosY;

    pField = pF;
    pBrain = new Brain(1000);
}

Dot::Dot(Field* pF, int x, int y, Brain *pB)
{
    iStartPosX = x;
    iStartPosY = y;
    fPosX = iStartPosX;
    fPosY = iStartPosY;

    pField = pF;
    pBrain = pB;
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

    float fDist = pField->GetGoalDistance((int)fPosX, (int)fPosY);

    if (fClosestDistToGoal > fDist)
    {
        fClosestDistToGoal = fDist;
    }

    if (iStep >= SIZE || pField->GetCollision((int)fPosX, (int)fPosY, &bGoal))
    {
        bDead = true;
        CalculateFitness();
    }
}

void Dot::Draw(SDL_Renderer* renderer)
{
    if (bIsBest)
    {
        SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
    }
    

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

void Dot::CalculateFitness()
{
    if (bGoal)
    {
        fFitness = 1000.0f/(float)(iStep*iStep);
    }
    else
    {
        fFitness = 1.0f / (fClosestDistToGoal * fClosestDistToGoal);
    } 
}

float Dot::GetFitness()
{
    return fFitness;
}

bool Dot::IsDead()
{
    return bDead;
}

void Dot::Mutate()
{
    pBrain->Mutate();
}

Dot* Dot::CloneDot()
{
    if (pBrain == NULL)
    {
        return NULL;
    }
    return new Dot(pField, iStartPosX, iStartPosY, pBrain->CloneBrain());
}

void Dot::SetBest()
{
    bIsBest = true;
}




