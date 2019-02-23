#pragma once
#include "TwoPlayer.h"
#include "AI.h"
#include "Mouse.h"

enum Kaesekaestchenmode
{
	running,
	Player1Victory,
	Player2Victory,
	Undecided
};

class Kaesekaestchen
{
public:
	Kaesekaestchen(BoardInit brdinit, Graphics& gfx, Mouse& mouse, int flag);
	Kaesekaestchen(Graphics& gfx, Mouse& mouse, void* data, int flag);
	~Kaesekaestchen();
	int Update();
	void Draw();

private:
	Graphics& gfx;
	Mouse& mouse;
	Board* brd;
	Kaesekaestchenmode kkm;
};
