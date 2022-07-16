#pragma once
#include "Dot.h"
#include <vector>

using namespace std;

class Population
{
public:
	Population(int s, int start_x, int start_y);
	~Population();
	void Update(SDL_Renderer* renderer);

private:
	int size;
	Dot **ppDot;
};
