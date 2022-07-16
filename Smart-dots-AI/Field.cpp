#include "Field.h"
#include <SDL2/SDL.h>

Field::Field(int iGoalposX, int iGoalposY)
{
	ppObstacles = nullptr;

	pGoal = new Goal;
	pGoal->iPosX = iGoalposX;
	pGoal->iPosY = iGoalposY;
    pGoal->iRadius = 10;

    ppObstacles = new SDL_Rect * [MAX_OBSTACLES];
}

Field::~Field()
{
    for (int i = 0; i < iObsSize; i++)
    {
        delete ppObstacles[i];
    }
    delete[] ppObstacles;
}

void Field::AddObstacle(int iObsPosX, int iObsPosY, int iObsHeigth, int iObsWidth)
{
    if (iObsSize < MAX_OBSTACLES)
    {
        ppObstacles[iObsSize] = new SDL_Rect;

        ppObstacles[iObsSize]->x = iObsPosX;
        ppObstacles[iObsSize]->y = iObsPosY;
        ppObstacles[iObsSize]->h = iObsHeigth;
        ppObstacles[iObsSize]->w = iObsWidth;

        iObsSize++;
    }
}

bool Field::GetCollision()
{
	return true;
}

void Field::Update(SDL_Renderer* renderer)
{
	DrawObstacles(renderer);
	DrawGoal(renderer);
}

void Field::DrawObstacles(SDL_Renderer* renderer)
{
    for (int i = 0; i < iObsSize; i++)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, ppObstacles[i]);
    }
}

void Field::DrawGoal(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);

    // Drawing circle
    for (float x = pGoal->iPosX - pGoal->iRadius; x <= pGoal->iPosX + pGoal->iRadius; x++)
    {
        for (float y = pGoal->iPosY - pGoal->iRadius; y <= pGoal->iPosY + pGoal->iRadius; y++)
        {
            if ((pow(pGoal->iPosY - y, 2) + pow(pGoal->iPosX - x, 2)) <= pow(pGoal->iRadius, 2))
            {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }

}
