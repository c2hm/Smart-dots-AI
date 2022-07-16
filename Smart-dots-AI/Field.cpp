#include "Field.h"
#include <SDL2/SDL.h>

const int DEAD_MARGIN_DIST = 2;
const int GOAL_LENGTH = 25;

Field::Field(int iGoalposX, int iGoalposY)
{
    ppObstacles = nullptr;

    pGoal = new SDL_Rect;
    pGoal->x = iGoalposX;
    pGoal->y = iGoalposY;
    pGoal->h = GOAL_LENGTH;
    pGoal->w = GOAL_LENGTH;

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

bool Field::GetCollision(int iDotPosX, int iDotPosY, bool* bIsGoal)
{
    if (iDotPosX < DEAD_MARGIN_DIST || iDotPosX > WIDTH - DEAD_MARGIN_DIST)
    {
        return true;
    }
    else if (iDotPosY < DEAD_MARGIN_DIST || iDotPosY > HEIGTH - DEAD_MARGIN_DIST)
    {
        return true;
    }

    for (int i = 0; i < iObsSize; i++)
    {
        int iLeftLimit = ppObstacles[i]->x - DEAD_MARGIN_DIST;
        int iRightLimit = ppObstacles[i]->x + ppObstacles[i]->w + DEAD_MARGIN_DIST;
        int iTopLimit = ppObstacles[i]->y - DEAD_MARGIN_DIST;
        int iBottomLimit = ppObstacles[i]->y + ppObstacles[i]->h + DEAD_MARGIN_DIST;

        if (iDotPosX > iLeftLimit && iDotPosX < iRightLimit && iDotPosY > iTopLimit && iDotPosY < iBottomLimit)
        {
            return true;
        }
    }

    int iLeftLimit = pGoal->x - DEAD_MARGIN_DIST;
    int iRightLimit = pGoal->x + pGoal->w + DEAD_MARGIN_DIST;
    int iTopLimit = pGoal->y - DEAD_MARGIN_DIST;
    int iBottomLimit = pGoal->y + pGoal->h + DEAD_MARGIN_DIST;

    if (iDotPosX > iLeftLimit && iDotPosX < iRightLimit && iDotPosY > iTopLimit && iDotPosY < iBottomLimit)
    {
        *bIsGoal = true;
        return true;
    }




	return false;
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
    SDL_RenderDrawRect(renderer, pGoal);
    SDL_RenderFillRect(renderer, pGoal);
}
