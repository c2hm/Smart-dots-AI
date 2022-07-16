#include "Population.h"
#include <iostream>

using namespace std;

Population::Population(int s, int start_x, int start_y)
{
	size = s;
	ppDot = new Dot * [size];
	for (int i = 0; i < size; i++)
	{
		ppDot[i] = new Dot(start_x, start_y);
	}
}

Population::~Population()
{
	for (int i = 0; i < size; i++)
	{
		delete ppDot[i];
	}
	delete[] ppDot;
}

void Population::Update(SDL_Renderer* renderer)
{
	for (int i = 0; i < size; i++)
	{
		ppDot[i]->Update(renderer);
	}
}

