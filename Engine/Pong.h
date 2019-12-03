#pragma once
#include "Interface.h"

class Pong : public Interface
{
public:
	Pong(Graphics& gfx, Keyboard& keyboard, StringSwitch<DataPass>& data) {}
	virtual int Update() override { return 0; /*return 1 to end program*/ }
	virtual void Draw() override {}
};