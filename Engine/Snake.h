#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "Vec2.h"
#include <vector>

class SnakeGame
{
private:
	enum Snakemode
	{
		running,
		Defeat,
		Victory
	};
	class Cell
	{
	public:
		enum CellContents
		{
			Empty,
			Snakehead,
			Snake,
			Apple
		};
	public:
		Cell(Vec2<int> screenposition);
		~Cell();

	public:
		int Update();
		void Draw() const;

	public:
		Vec2<int> pos; //screenposition
		CellContents cc = Empty;
	};

	class Snake 
	{
		int Update();
		void Draw() = delete;
		class Head
		{};
		class Body
		{
			//Vec2<int> pos;
			//Vec2<int> prevpos; || Body/Head* next;
		};
		Head head;
		std::vector<Body> body;
		//needs a head -> controlled by player
		//needs body parts, in some sort of vector, part 0 follows head, part 1 follows 0, 2 -> 1, ...
	};
	/*
	Game calls SnakeGame::Update
	SnakeGame::Update calls SnakeGame::Run
	SnakeGame::Run calls Snake::Update
	Snake::Update ???
	??? calls Cell::Update
	Cell::Update now knows there is a Snake on it and Draws accordingly
	call update on the snake,
	snake moves
	call update on cells
	*/
public:
	SnakeGame(Graphics& gfx, Keyboard& keyboard, void* data);
	~SnakeGame();
	int Update();
	void Draw();

private:
	static Vec2<int> GetCellCount(void* data);
	static int CalculateCellSize(const Vec2<int> cellcount, void* data);
	static Vec2<int> CalculateTopLeft(const Vec2<int> cellcount, const int cellsize);

private:
	Graphics& gfx;
	Keyboard& keyboard;
	Snakemode sm;

	const Vec2<int> cellcount;
	const int cellsize;
	const Vec2<int> topleft;

	std::vector<Cell> cells;
};
/*
SnakeInit
00:	short	:	Cellcount.x
02:	short	:	Cellcount.y
04:	short	:	Cellsize
06:	short	:	
08:	int		:	Color
12:	int		:	Color
16:	int		:	Color
20:	int		:	Color
24:	int		:	Color
28:	int		:	Color
32:	int		:	Color
36:	int		:	Color
40:	int		:	Color
44:	int		:	Color
48:	int		:	Color
52:	int		:	Color
56:	int		:	Color
60:	int		:	Color
64: end
*/