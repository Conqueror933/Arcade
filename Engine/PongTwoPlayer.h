#pragma once
#include "PongGame.h"

class PongTwoPlayer : public PongGame 
{ 
public:
	PongTwoPlayer(Graphics& gfx, Keyboard& keyboard, StringSwitch<DataPass>& data) : PongGame(gfx, keyboard, data) {}
	int Update() override { return 0; }
	void Draw() override { gfx.PutPixel(100, 100, 255, 255, 255); }
};