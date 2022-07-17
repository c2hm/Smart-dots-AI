#include "Population.h"
#include <random>


using namespace std;

Population::Population(Field *pF, int s, int start_x, int start_y)
{
	pField = pF;
	iSize = s;
	ppDots = new Dot * [iSize];
	for (int i = 0; i < iSize; i++)
	{
		ppDots[i] = new Dot(pF, start_x, start_y);
	}
}

Population::~Population()
{
	for (int i = 0; i < iSize; i++)
	{
		delete ppDots[i];
	}
	delete[] ppDots;
}

void Population::Update(SDL_Renderer* renderer)
{
	if (AllDotsDead())
	{
		NaturalSelection();
	}

	for (int i = 1; i < iSize; i++)
	{
		ppDots[i]->Update(renderer);
	}

	ppDots[0]->Update(renderer);
}

bool Population::AllDotsDead()
{
	for (int i = 0; i < iSize; i++)
	{
		if (!ppDots[i]->IsDead())
		{
			return false;
		}
	}
	return true;
}

void Population::NaturalSelection()
{
	Dot** ppNewDots = new Dot * [iSize];

	Dot* pBestDot = GetBestDot();

	ppNewDots[0] = pBestDot->CloneDot();
	ppNewDots[0]->SetBest();

	for (int i = 1; i < iSize; i++)
	{
		Dot* pDotParent = GetParent();
		ppNewDots[i] = pDotParent->CloneDot();
		ppNewDots[i]->Mutate();
	}

	for (int i = 0; i < iSize; i++)
	{
		delete ppDots[i];
	}
	delete[] ppDots;

	ppDots = ppNewDots;
	iGen++;	
}

Dot* Population::GetParent()
{
	CalculateFitnessSum();

	random_device rd;
	srand(rd());

	float fRandomNbr = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / fFitnessSum));
	float runningSum = 0;

	for (int i = 0; i < iSize; i++) {
		runningSum += ppDots[i]->GetFitness();
		if (runningSum > fRandomNbr) {
			return ppDots[i];
		}
	}

	return ppDots[iSize-1];
}


void Population::CalculateFitnessSum() {
	fFitnessSum = 0;
	for (int i = 0; i < iSize; i++) {
		fFitnessSum += ppDots[i]->GetFitness();
	}
}

Dot* Population::GetBestDot()
{
	int iBestDotIndex = 0;
	for (int i = 0; i < iSize; i++) {
		if (ppDots[i]->GetFitness() > ppDots[iBestDotIndex]->GetFitness())
		{
			iBestDotIndex = i;
		}
	}
	return ppDots[iBestDotIndex];
}

int Population::GetGeneration()
{
	return iGen;
}





