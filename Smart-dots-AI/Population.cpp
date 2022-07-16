#include "Population.h"
#include <iostream>


using namespace std;

Population::Population(Field *pF, int s, int start_x, int start_y)
{
	pField = pF;
	iSize = s;
	ppDot = new Dot * [iSize];
	for (int i = 0; i < iSize; i++)
	{
		ppDot[i] = new Dot(pF, start_x, start_y);
	}
}

Population::~Population()
{
	for (int i = 0; i < iSize; i++)
	{
		delete ppDot[i];
	}
	delete[] ppDot;
}

void Population::Update(SDL_Renderer* renderer)
{
	for (int i = 0; i < iSize; i++)
	{
		ppDot[i]->Update(renderer);
	}
}

