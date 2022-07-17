#pragma once
#include "Dot.h"
#include "Field.h"

using namespace std;

class Population
{
public:
	Population(Field* pF, int s, int start_x, int start_y);
	~Population();
	void Update(SDL_Renderer* renderer);

private:
	Field* pField;
	int iSize;
	Dot **ppDots;
	float fFitnessSum = 0;

	bool AllDotsDead();
	void CalculateFitnessSum();
	void NaturalSelection();
	Dot* GetParent();
	Dot* GetBestDot();
};
