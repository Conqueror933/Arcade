#pragma once
#include "TwoPlayer.h"
#include "AI.h"
#include "Mouse.h"
#include "Interface.h"
#include "StringSwitch.h"

class Kaesekaestchen : public Interface
{
private:
	enum Kaesekaestchenmode
	{
		running,
		Player1Victory,
		Player2Victory,
		Undecided
	};
public:
	Kaesekaestchen(Graphics& gfx, Mouse& mouse, StringSwitch<DataPass>& data, int flag);
	~Kaesekaestchen();
	int Update();
	void Draw();

private:
	Graphics& gfx;
	Mouse& mouse;
	Board* brd;
	Kaesekaestchenmode kkm;
};
