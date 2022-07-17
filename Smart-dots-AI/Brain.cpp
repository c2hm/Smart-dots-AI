#include "Brain.h"
#include <stdlib.h>
#include <math.h>
#include <time.h> 
#include <random>

using namespace std;

const int MUTATION_PERCENTAGE_LIMIT = 1;

Brain::Brain(int s) : iSize(s)
{
	fDirX = new float[iSize];
	fDirY = new float[iSize];

	random_device rd;
	srand(rd());

	for (int i = 0; i < iSize; i++)
	{
		float angle = ((float)rand() / (float)RAND_MAX) * 2*3.1416;
		fDirX[i] = cos(angle);
		fDirY[i] = sin(angle);
	}
}

Brain::Brain(int s, float *x, float *y) : iSize(s)
{
	fDirX = new float[iSize];
	fDirY = new float[iSize];

	for (int i = 0; i < iSize; i++)
	{
		fDirX[i] = x[i];
		fDirY[i] = y[i];
	}
}

Brain::~Brain()
{
	delete[] fDirX;
	delete[] fDirY;
}

float Brain::GetDirectionX(int index)
{
	return fDirX[index];
}

float Brain::GetDirectionY(int index)
{
	return fDirY[index];
}

Brain* Brain::CloneBrain()
{
	Brain* clone = new Brain(iSize, fDirX, fDirY);

	if (clone == NULL)
	{
		return NULL;
	}
	return clone;
}

void Brain::Mutate()
{
	random_device rd;
	srand(rd());

	for (int i = 0; i < iSize; i++)
	{
		float iMutationChance = rand() % 100;

		if (iMutationChance <= MUTATION_PERCENTAGE_LIMIT && iMutationChance > 0)
		{
			float iMutationPercentage = 0.1;
			fDirX[i] += fDirX[i] * iMutationPercentage;
			fDirY[i] += fDirY[i] * iMutationPercentage;
		}
	}
}



