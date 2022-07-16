#pragma once
#include <SDL2/SDL.h>
#include "Brain.h"

static const int SIZE = 1000;
static const int RADIUS = 5;

using namespace std;

class Dot
{
public:
    Dot(int x, int y, int wh, int ww);
    ~Dot();
    void Update(SDL_Renderer* renderer);

private:
    int iStep = 0;
    Brain *pBrain;
    float fPosX;
    float fPosY;
    int iWindowHeigth;
    int iWindowWidth;
    bool bDead = false;
    bool bKill = false;

    void Move();
    void Draw(SDL_Renderer* renderer);
    void VerifyDead();
};




