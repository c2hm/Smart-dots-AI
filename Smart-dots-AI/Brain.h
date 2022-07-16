#pragma once

class Brain
{
public:
	Brain(int s);
	~Brain();
	float GetDirectionX(int index);
	float GetDirectionY(int index);

private:
	int size;
	float* dirX;
	float* dirY;
};

