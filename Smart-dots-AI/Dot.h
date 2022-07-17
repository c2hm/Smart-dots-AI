#pragma once
#include <SDL2/SDL.h>
#include "Brain.h"
#include "Field.h"

using namespace std;

class Dot
{
public:
    Dot(Field *pF, int x, int y);
    Dot(Field* pF, int x, int y, Brain* pB);
    ~Dot();
    void Update(SDL_Renderer* renderer);
    float GetFitness();
    Dot* CloneDot();
    bool IsDead();
    void Mutate();
    void SetBest();
    

private:
    Field* pField;
    int iStep = 0;
    Brain *pBrain;
    float fPosX = 0;
    float fPosY = 0;
    float fVelX = 0;
    float fVelY = 0;
    float fAccX = 0;
    float fAccY = 0;
    bool bDead = false;
    bool bGoal = false;
    float fFitness = 0;
    int iStartPosX = 0;
    int iStartPosY = 0;
    int fClosestDistToGoal = INT_MAX;
    bool bIsBest = false;

    void Move();
    void Draw(SDL_Renderer* renderer);
    void CalculateFitness();
};




