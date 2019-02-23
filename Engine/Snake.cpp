#include "Snake.h"
#include <assert.h>


SnakeGame::SnakeGame(Graphics& gfx, Keyboard& keyboard, void* data)
	:
	gfx(gfx),
	keyboard(keyboard),
	cellcount(GetCellCount(data)),
	cellsize(CalculateCellSize(cellcount, data)),
	topleft(CalculateTopLeft(cellcount, cellsize))
{
	//reserve Cell space to avoid reallocating
	cells.reserve(cellcount.x*cellcount.y);
	//make Cells
	for (int y = 0; y < cellcount.y; y++)
	{
		for (int x = 0; x < cellcount.x; x++)
		{
			cells.emplace_back(Vec2<int>{ topleft.x + x * cellsize, topleft.y + y * cellsize});
		}
	}
	//make and place Snake

	//place Apple
}


SnakeGame::~SnakeGame()
{
}

int SnakeGame::Update()
{
	switch (sm)
	{
	case running:
		//code
		return 0;
	default:
		//code
		return 1;
	}
}

void SnakeGame::Draw()
{
	switch (sm)
	{
	case running:
		//draw
		break;
	case Defeat:
		//draw
		break;
	case Victory:
		//draw
		break;
	}
}

Vec2<int> SnakeGame::GetCellCount(void* data)
{
	return Vec2<int>(int(static_cast<short*>(data)[0]), int(static_cast<short*>(data)[1]));
}

int SnakeGame::CalculateCellSize(const Vec2<int> cellcount, void* data)
{
	int x = Graphics::ScreenWidth / cellcount.x;
	int y = Graphics::ScreenHeight / cellcount.y;
	if (static_cast<short*>(data)[2] == 0)
	{
		if (x < y)
			return x;
		else
			return y;
	}
	else
	{
		int w = static_cast<short*>(data)[2];
		assert(w * x < Graphics::ScreenWidth);
		assert(w * y < Graphics::ScreenHeight);
		return w;
	}
}

Vec2<int> SnakeGame::CalculateTopLeft(const Vec2<int> cellcount, const int cellsize)
{
	return Vec2<int>((Graphics::ScreenWidth - cellcount.x * cellsize) / 2,
		(Graphics::ScreenHeight - cellcount.y * cellsize) / 2);
}

SnakeGame::Cell::Cell(Vec2<int> screenposition)
	:
	pos(screenposition)
{
}