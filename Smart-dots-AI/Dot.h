#pragma once
#include <SDL2/SDL.h>
#include "Brain.h"
#include "Field.h"



using namespace std;

class Dot
{
public:
    Dot(Field *pF, int x, int y);
    ~Dot();
    void Update(SDL_Renderer* renderer);

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

    void Move();
    void Draw(SDL_Renderer* renderer);
};




