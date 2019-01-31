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
	virtual void Update(int i) {}
private:
	Color c;
	int counter;
	int playernumber;
};