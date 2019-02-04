#pragma once
#include "Colors.h"

class Player
{
public:
	Player(Color c) : c(c) {}
	//Getter
	const Color GetColor() { return c; }
	const int GetCounter() { return counter; }
	//Setter
	void SetCounter(){ counter++; }

private:
	Color c;
	int counter = 0;
};