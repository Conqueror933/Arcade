#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "Vec2.h"
#include "Frametimer.h"
#include <vector>
#include <queue>
#include <array>
#include <random>

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
		Cell(SnakeGame& sg, Vec2<int> screenposition);
		~Cell() = default;

	public:
		void Draw() const;

	public:
		Vec2<int> pos; //screenposition
		CellContents cc = Empty;

	private:
		SnakeGame& sg;
	};

	struct Snake
	{
		Snake(SnakeGame& sg, int bodyparts) : sg(sg), length(bodyparts + 1) {}
		void Init()
		{//limited by the size of the field, if bodyparts > cellcounts.x = insta lose
			/*for (int i = 0; i < length; i++)
				body.push(Vec2<int>{ 0, 0});*/
		}
		enum Direction { up, left, right, down } dir = right;
		void Update();
		Vec2<int> head = { 0, 0 };
		std::queue<Vec2<int>> body;
		int length;

	private:
		SnakeGame& sg;
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
	static int CalculateCellBorderWidth(const int cellsize, const double borderthicknessratio);
	static int CalculateCellSize(const Vec2<int> cellcount, void* data);
	static Vec2<int> CalculateTopLeft(const Vec2<int> cellcount, const int cellsize);
	static Vec2<int> MakeSnakeHead(SnakeGame& sg);

private:
	inline void Run();
	void PlaceApple();

private:
	Graphics& gfx;
	Keyboard& keyboard;
	Snakemode sm = running;
	std::random_device rd;
	FrameTimer ft;

	const Vec2<int> cellcount;
	const int cellsize;
	const int cellborderwidth; //for drawing purposes
	const Vec2<int> topleft;
	const std::array<char, 4> keys;
	const float gamespeed;
	const std::array<Color, 5> colors; //Border, Cell, Apple, Snake, Snakehead

	std::vector<Cell> cells;
	Snake snake;
	float time_passed = 0.0f;
};
/*
SnakeInit
00:	short	:	Cellcount.x
02:	short	:	Cellcount.y
04:	short	:	Cellsize
06:	short	:	Snakebodyparts
08:	double	:	cellborderthicknessratio
16:	char	:	up		- Key
17:	char	:	left	- Key
18:	char	:	right	- Key
19:	char	:	down	- Key
20:	float	:	gamespeed
24:	int		:	Color - Border
28:	int		:	Color - Cell
32:	int		:	Color - Apple
36:	int		:	Color - Snake
40:	int		:	Color - Snakehead
44:	int		:	Color
48:	int		:	Color
52:	int		:	Color
56:	int		:	Color
60:	int		:	Color
64: end
*/