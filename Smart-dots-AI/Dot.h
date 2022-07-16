#pragma once
#include <SDL2/SDL.h>
#include "Brain.h"
#include "Field.h"

static const int SIZE = 1000;
static const int RADIUS = 3;

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
    float fPosX;
    float fPosY;
    bool bDead = false;
    bool bGoal = false;

    void Move();
    void Draw(SDL_Renderer* renderer);
};




