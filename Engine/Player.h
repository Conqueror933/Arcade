#pragma once
#include "Colors.h"

class Player
{
public:
	Player(int Playernumber, Color c);
	//Getter
	const Color GetColor();
	const int GetCounter();
	//Setter
	void SetCounter();
private:
	Color c;
	int counter;
	int playernumber;
};