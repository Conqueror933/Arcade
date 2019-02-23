#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "Vec2.h"

class Snake
{
private:
	enum Snakemode
	{
		running,
		Victory
	};
public:
	Snake(Graphics& gfx, Keyboard& keyboard, void* data, int flag);
	~Snake();
	int Update();
	void Draw();

private:
	Graphics& gfx;
	Keyboard& keyboard;
	Snakemode sm;
};
