#include "Brain.h"
#include <stdlib.h>
#include <math.h>
#include <time.h> 
#include <random>

using namespace std;

Brain::Brain(int s) : size(s)
{
	dirX = new float[size];
	dirY = new float[size];

	random_device rd;
	srand(rd());

	for (int i = 0; i < size; i++)
	{
		float angle = ((float)rand() / (float)RAND_MAX) * 2*3.1416;
		dirX[i] = cos(angle);
		dirY[i] = sin(angle);
	}
}

Brain::~Brain()
{
	delete[] dirX;
	delete[] dirY;
}

float Brain::GetDirectionX(int index)
{
	return dirX[index];
}

float Brain::GetDirectionY(int index)
{
	return dirY[index];
}

