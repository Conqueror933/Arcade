#include "Snake.h"
#include <assert.h>


SnakeGame::SnakeGame(Graphics& gfx, Keyboard& keyboard, StringSwitch<DataPass>& data)
	:
	gfx(gfx),
	keyboard(keyboard),
	cellcount(GetCellCount(data)),
	cellsize(CalculateCellSize(cellcount, data)),
	cellborderwidth(CalculateCellBorderWidth(cellsize, data.GetValue("Border").d)),
	topleft(CalculateTopLeft(cellcount, cellsize)),
	snake(*this, 3),
	gamespeed((float)data.GetValue("Speed").d)
{
	//reserve Cell space to avoid reallocating/
	cells.reserve(cellcount.x*cellcount.y);
	//make Cells
	for (int y = 0; y < cellcount.y; y++)
	{
		for (int x = 0; x < cellcount.x; x++)
		{
			cells.emplace_back(*this, Vec2<int>{ topleft.x + x * cellsize, topleft.y + y * cellsize});
		}
	}
	//make snake longer
	snake.Init();

	//place Apple
	PlaceApple();

	//set up keyboard
	if (keyboard.AutorepeatIsEnabled())
		keyboard.DisableAutorepeat();
}

SnakeGame::~SnakeGame()
{
}

Vec2<int> SnakeGame::GetCellCount(StringSwitch<DataPass>& data)
{
	return Vec2<int>(data.GetValue("Size").i, data.GetValue("Size").i);
}

int SnakeGame::CalculateCellBorderWidth(const int cellsize, const double borderthicknessratio)
{
	assert(borderthicknessratio > 0.0);
	assert(borderthicknessratio < 1.0);
	return static_cast<int>((double)cellsize * borderthicknessratio);
}

int SnakeGame::CalculateCellSize(const Vec2<int> cellcount, StringSwitch<DataPass>& data)
{
	int x = Graphics::ScreenWidth / cellcount.x;
	int y = Graphics::ScreenHeight / cellcount.y;
	//if (static_cast<short*>(data)[2] == 0)
	//{
		if (x < y)
			return x;
		else
			return y;
	//}
	//else
	//{
	//	int w = static_cast<short*>(data)[2];
	//	assert(w * x < Graphics::ScreenWidth);
	//	assert(w * y < Graphics::ScreenHeight);
	//	return w;
	//}
}

Vec2<int> SnakeGame::CalculateTopLeft(const Vec2<int> cellcount, const int cellsize)
{
	return Vec2<int>((Graphics::ScreenWidth - cellcount.x * cellsize) / 2,
		(Graphics::ScreenHeight - cellcount.y * cellsize) / 2);
}

Vec2<int> SnakeGame::MakeSnakeHead(SnakeGame& sg)
{
	std::mt19937 rng(sg.rd());
	std::uniform_int_distribution<int> dice(0, sg.cellcount.x*sg.cellcount.y - 1);
	return Vec2<int>(dice(rng), dice(rng));
}

int SnakeGame::Update()
{
	switch (sm)
	{
	case running:
		//code
		if (snake.length == cellcount.x * cellcount.y)
			sm = Victory;
		Run();
		return 0;
	default:
		//code
		if (keyboard.KeyIsPressed(VK_SPACE))
			return 1;
		else
			return 0;
	}
}

void SnakeGame::Draw()
{
	switch (sm)
	{
	case running:
		//draw
		for (auto i = 0u; i < cells.size(); i++)
			cells[i].Draw();
		break;
	case Defeat:
		//draw
		gfx.DrawRectangle(0, 0, 100, 100, Colors::Red);
		break;
	case Victory:
		//draw
		gfx.DrawRectangle(0, 0, 100, 100, Colors::Blue);
		break;
	}
}

inline void SnakeGame::Run()
{
	if (keyboard.KeyIsPressed(keys[0]))
		snake.dir = Snake::up;
	if (keyboard.KeyIsPressed(keys[1]))
		snake.dir = Snake::left;
	if (keyboard.KeyIsPressed(keys[2]))
		snake.dir = Snake::right;
	if (keyboard.KeyIsPressed(keys[3]))
		snake.dir = Snake::down;

	time_passed += ft.Mark();
	if (time_passed > gamespeed)
	{
		time_passed -= gamespeed;
		snake.Update();
	}
}

void SnakeGame::PlaceApple()
{
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> dice(0, cellcount.x*cellcount.y - 1);
	int apple = dice(rng);
	while (!(cells[apple].cc == Cell::Empty))
		apple = dice(rng);
	cells[apple].cc = Cell::Apple;
}

void SnakeGame::Snake::Update()
{
	if (sg.cells[head.x + head.y * sg.cellcount.x].cc == Cell::Empty) {
		if (!body.empty()) {
			sg.cells[body.front().x + body.front().y * sg.cellcount.x].cc = Cell::Empty;
			body.pop();
		}
	}
	else if (sg.cells[head.x + head.y * sg.cellcount.x].cc == Cell::Apple)
	{
		length++;
		sg.PlaceApple();
	}
	else
		sg.sm = Defeat;
	sg.cells[head.x + head.y * sg.cellcount.x].cc = Cell::Snakehead;
	if(!body.empty())
		sg.cells[body.back().x + body.back().y * sg.cellcount.x].cc = Cell::Snake;
	body.push(head);
	switch (dir)
	{
	case up:
		head.y--;
		if (head.y < 0) {
			sg.sm = Defeat;
			head.y++;
		}
		break;
	case left:
		head.x--;
		if (head.x < 0) {
			sg.sm = Defeat;
			head.x++;
		}
		break;
	case right:
		head.x++;
		if (head.x > sg.cellcount.x) {
			sg.sm = Defeat;
			head.x--;
		}
		break;
	case down:
		head.y++;
		if (head.y > sg.cellcount.y) {
			sg.sm = Defeat;
			head.y--;
		}
		break;
	}
	sg.cells[body.back().x + body.back().y * sg.cellcount.x].cc = Cell::Snakehead;
}

SnakeGame::Cell::Cell(SnakeGame& sg, Vec2<int> screenposition)
	:
	sg(sg),
	pos(screenposition)
{
}

void SnakeGame::Cell::Draw() const
{
	sg.gfx.DrawRectangleDim(pos.x, pos.y, sg.cellsize, sg.cellsize, sg.colors[0]);
	switch (cc)
	{
	case Empty:
		sg.gfx.DrawRectangleDim(pos.x + sg.cellborderwidth, pos.y + sg.cellborderwidth, 
			sg.cellsize - sg.cellborderwidth * 2, sg.cellsize - sg.cellborderwidth * 2, sg.colors[1]);
		break;
	case Apple:
		sg.gfx.DrawRectangleDim(pos.x + sg.cellborderwidth, pos.y + sg.cellborderwidth,
			sg.cellsize - sg.cellborderwidth * 2, sg.cellsize - sg.cellborderwidth * 2, sg.colors[2]);
		break;
	case Snake:
		sg.gfx.DrawRectangleDim(pos.x + sg.cellborderwidth, pos.y + sg.cellborderwidth,
			sg.cellsize - sg.cellborderwidth * 2, sg.cellsize - sg.cellborderwidth * 2, sg.colors[3]);
		break;
	case Snakehead:
		sg.gfx.DrawRectangleDim(pos.x + sg.cellborderwidth, pos.y + sg.cellborderwidth,
			sg.cellsize - sg.cellborderwidth * 2, sg.cellsize - sg.cellborderwidth * 2, sg.colors[4]);
		break;
	}
}
