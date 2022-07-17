#pragma once
#include <SDL2/SDL.h>

const int HEIGTH = 800;
const int WIDTH = 800;
const int MAX_OBSTACLES = 10;

class Field
{
public:
	Field(int iGoalposX, int iGoalposY);
	~Field();
	void AddObstacle(int iObsPosX, int iObsPosY, int iObsHeigth, int iObsWidth);
	bool GetCollision(int iDotPosX, int iDotPosY, bool *bIsGoal);
	void Update(SDL_Renderer* renderer);
	float GetGoalDistance(int iDotPosX, int iDotPosY);

private:
	typedef struct
	{
		int iPosX;
		int iPosY;
		int iRadius;
	}Goal;

	SDL_Rect** ppObstacles;
	SDL_Rect* pGoal;
	int iObsSize = 0;

	void DrawObstacles(SDL_Renderer* renderer);
	void DrawGoal(SDL_Renderer* renderer);
};



