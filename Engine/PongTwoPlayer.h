#pragma once
#include "PongGame.h"

class PongTwoPlayer : public PongGame 
{ 
public: 
	int Update() override { return 0; }
	void Draw() override {} 
};