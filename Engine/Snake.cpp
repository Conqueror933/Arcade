#include "Snake.h"



Snake::Snake(Graphics& gfx, Keyboard& keyboard, void* data, int flag)
	:
	gfx(gfx),
	keyboard(keyboard)
{
}


Snake::~Snake()
{
}

int Snake::Update()
{
	switch (sm)
	{
	case running:
		//code
		return 0;
	case Victory:
		//code
		return 1;
	default:
		return -1;
	}
}

void Snake::Draw()
{
	switch (sm)
	{
	case running:
		//draw
		break;
	case Victory:
		//draw
		break;
	}
}
