#include "Snake.h"
#include <assert.h>


SnakeGame::SnakeGame(Graphics& gfx, Keyboard& keyboard, void* data)
	:
	gfx(gfx),
	keyboard(keyboard),
	cellcount(GetCellCount(data)),
	cellsize(CalculateCellSize(cellcount, data)),
	cellborderwidth(CalculateCellBorderWidth(cellsize, static_cast<double*>(data)[1])),
	topleft(CalculateTopLeft(cellcount, cellsize)),
	keys{ static_cast<char*>(data)[16], static_cast<char*>(data)[17], static_cast<char*>(data)[18], static_cast<char*>(data)[19] },
	snake(*this, static_cast<short*>(data)[3]),
	gamespeed(static_cast<float*>(data)[5]),
	colors{ static_cast<Color*>(data)[6], static_cast<Color*>(data)[7], static_cast<Color*>(data)[8],
	static_cast<Color*>(data)[9], static_cast<Color*>(data)[10], } //damn this feels shaky as fuck
{
	//reserve Cell space to avoid reallocating
	cells.reserve(cellcount.x*cellcount.y);
	//make Cells
	for (int y = 0; y < cellcount.y; y++)
	{
		for (int x = 0; x < cellcount.x; x++)
		{
			cells.emplace_back(*this, Vec2<int>{ topleft.x + x * cellsize, topleft.y + y * cellsize});
		}
	}
	//place Apple
	PlaceApple();

	//set up keyboard
	if (keyboard.AutorepeatIsEnabled())
		keyboard.DisableAutorepeat();
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

Vec2<int> SnakeGame::GetCellCount(void* data)
{
	return Vec2<int>(int(static_cast<short*>(data)[0]), int(static_cast<short*>(data)[1]));
}

int SnakeGame::CalculateCellBorderWidth(const int cellsize, const double borderthicknessratio)
{
	assert(borderthicknessratio > 0.0);
	assert(borderthicknessratio < 1.0);
	return static_cast<int>((double)cellsize * borderthicknessratio);
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

Vec2<int> SnakeGame::MakeSnakeHead(SnakeGame& sg)
{
	std::mt19937 rng(sg.rd());
	std::uniform_int_distribution<int> dice(0, sg.cellcount.x*sg.cellcount.y - 1);
	return Vec2<int>(dice(rng), dice(rng));
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
		if (cells[snake.head.x + snake.head.y * cellcount.x].cc == Cell::Apple)
			snake.Update(true);
		else
			snake.Update(false);
	}
}

void SnakeGame::PlaceApple()
{
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> dice(0, cellcount.x*cellcount.y - 1);
	int x = dice(rng); int y = dice(rng);
	while (!(cells[x + y * cellcount.x].cc == Cell::Empty)) {
		x = dice(rng); y = dice(rng);
	}
	cells[x + y * cellcount.x].cc = Cell::Apple;
}

void SnakeGame::Snake::Update(bool apple)
{
	body.push(head);
	sg.cells[head.x + head.y * sg.cellcount.x].cc = Cell::Snake;
	if (!apple) {
		body.pop();
		sg.cells[body.back().x + body.back().y * sg.cellcount.x].cc = Cell::Empty;
	}
	else
		length++;
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
	sg.cells[head.x + head.y * sg.cellcount.x].cc = Cell::Snakehead;
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
			sg.cellsize - sg.cellborderwidth, sg.cellsize - sg.cellborderwidth, sg.colors[1]);
		break;
	case Apple:
		sg.gfx.DrawRectangleDim(pos.x + sg.cellborderwidth, pos.y + sg.cellborderwidth,
			sg.cellsize - sg.cellborderwidth, sg.cellsize - sg.cellborderwidth, sg.colors[2]);
		break;
	case Snake:
		sg.gfx.DrawRectangleDim(pos.x + sg.cellborderwidth, pos.y + sg.cellborderwidth,
			sg.cellsize - sg.cellborderwidth, sg.cellsize - sg.cellborderwidth, sg.colors[3]);
		break;
	case Snakehead:
		sg.gfx.DrawRectangleDim(pos.x + sg.cellborderwidth, pos.y + sg.cellborderwidth,
			sg.cellsize - sg.cellborderwidth, sg.cellsize - sg.cellborderwidth, sg.colors[4]);
		break;
	}
}
