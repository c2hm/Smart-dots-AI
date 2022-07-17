#pragma once

class Brain
{
public:
	Brain(int s);
	Brain(int s, float* x, float* y);
	~Brain();
	float GetDirectionX(int index);
	float GetDirectionY(int index);
	Brain* CloneBrain();
	void Mutate();

private:
	int iSize;
	float* fDirX;
	float* fDirY;
};

