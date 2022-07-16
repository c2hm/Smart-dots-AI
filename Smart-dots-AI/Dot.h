#pragma once
#include <SDL2/SDL.h>
#include "Brain.h"

static const int size = 1000;
static const int radius = 5;

using namespace std;

class Dot
{
public:
    Dot(int x, int y);
    ~Dot();
    void Update(SDL_Renderer* renderer);

private:
    int step = 0;
    Brain *pBrain;
    float posX;
    float posY;

    void Move();
    void Draw(SDL_Renderer* renderer);
};




