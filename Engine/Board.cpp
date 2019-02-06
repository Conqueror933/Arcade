#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx, const BoardColors brdclr,
	const Vec2<int> topleft, const Vec2<int> bottomright, const Vec2<int> size, const unsigned int borderthicknessratio)
	:
	gfx(gfx),
	brdclr(brdclr),
	topleft(topleft),
	bottomright(bottomright),
	size(size),
	//calculate borderwidth
	borderwidth(Vec2<int>::pickLowest(Vec2<int>::constminus(bottomright, topleft) / borderthicknessratio / (size + 1))),
	//calculate cellsize
	cellsize(Vec2<int>(Vec2<int>::constminus(bottomright - borderwidth, topleft) / size ))
{
	//Set Background
	gfx.DrawRectangle(0, 0, gfx.ScreenWidth - 1, gfx.ScreenHeight - 1, Color(0u, 205u, 0u));
	//reserve Cell space to avoid reallocating
	cells.reserve(size.x*size.y);
	//make Cells
	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			cells.emplace_back(*this, Vec2<int>{ x, y});
		}
	}
	//make Players
	players.emplace_back(brdclr.player1);
	players.emplace_back(brdclr.player2);
	//Fill Cells at border of Board
	for (int i = 0; i < size.x; i++)
	{
		cells[i].top = true;
	}
	for (int i = 0; i < size.y*size.y; i += size.y)
	{
		cells[i].left = true;
	}
	//make Right and bottom look filled
	int x = cells[size.x*size.y - 1].position.x * cellsize.x + topleft.x;
	int y = cells[size.x*size.y - 1].position.y * cellsize.y + topleft.y;
	gfx.DrawRectangle(x + cellsize.x, 
		topleft.y,
		x + cellsize.x + borderwidth, 
		y + cellsize.y + borderwidth, 
		brdclr.clicked);
	gfx.DrawRectangle(topleft.x,
		y + cellsize.y,
		x + cellsize.x + borderwidth,
		y + cellsize.y + borderwidth,
		brdclr.clicked);
}

/****************************************************************************************************/
/*												Logic												*/
/****************************************************************************************************/
int Board::Update(int mouse_x, int mouse_y)
{
	set = false;
	int x = (mouse_x - topleft.x) / cellsize.x;
	int y = (mouse_y - topleft.y) / cellsize.y;
	if (x >= 0 && x < size.x && y >= 0 && y < size.y)
		//if(cells[x + size.x * y].Update(mouse_x, mouse_y))
		if(auto temp = cells[x + size.x * y].Update((mouse_x - topleft.x) % cellsize.x, (mouse_y - topleft.y) % cellsize.y))
		{
			cellsfilled += temp;
			//check who won
			if (cellsfilled == size.x * size.y)
			{
				if (players[0].GetCounter() > players[1].GetCounter())
					return 1;
				else if (players[0].GetCounter() < players[1].GetCounter())
					return 2;
				else
					return -1;
			}
			//}
		}
		else
			if(set)
				turncounter++;
	return 0;
}

/****************************************************************************************************/
/*												Draw												*/
/****************************************************************************************************/
void Board::Draw() const
{
	for (auto i = 0u; i < cells.size(); i++)
	{
		cells[i].Draw();
	}
	if (lastclickedCell.first > -1)
		cells[lastclickedCell.first].Draw();
}


/****************************************************************************************************/
/****************************************************************************************************/
/*											Cell Subclass											*/
/****************************************************************************************************/
/****************************************************************************************************/

Board::Cell::Cell(Board& brd, Vec2<int> position)
	:
	brd(brd),
	position(position)
{
	brd.gfx.DrawRectangleDim(position.x * brd.cellsize.x + brd.topleft.x, position.y * brd.cellsize.y + brd.topleft.y,
		brd.cellsize.x, brd.cellsize.y, brd.brdclr.background);
}

Board::Cell::~Cell()
{
}

Board::Cell::Cell(const Cell & other)
	:
	brd(other.brd),
	position(other.position)
{
}

Board::Cell& Board::Cell::operator=(const Cell& other)
{
	return *this;
}

/****************************************************************************************************/
/*												Logic												*/
/****************************************************************************************************/

int Board::Cell::Update(int mouse_x, int mouse_y)
{
	if (playerflag == -1)
	{
		if (mouse_x > brd.borderwidth && mouse_x < brd.cellsize.x &&
			mouse_y > 0 && mouse_y < brd.borderwidth)
			if (!top) {
				top = true; brd.set = true; 
				brd.lastclickedCell = { position.x + position.y * brd.size.x, true };
			}
		if (mouse_x > 0 && mouse_x < brd.borderwidth &&
			mouse_y > brd.borderwidth && mouse_y < brd.cellsize.y)
			if (!left) { 
				left = true; brd.set = true; 
				brd.lastclickedCell = { position.x + position.y * brd.size.x, false };
			}
		return Update();
	}
	return 0;
}

int Board::Cell::Update()
{
	int b = 0;
	if (playerflag == -1)
	{
		int x = position.x;
		int y = position.y;

		//error- and checking for right and bottom
		if (left && top) {
			bool right; x == brd.size.x - 1 ? right = true : right = brd.cells[brd.size.x * y + x + 1].left;
			bool bottom; y == brd.size.y - 1 ? bottom = true : bottom = brd.cells[x + brd.size.x * (y + 1)].top;
			if (right && bottom && top && left) {
				if (brd.turncounter % 2 == 0) {
					brd.players[0].SetCounter();
					playerflag = 0;
				}
				else {
					brd.players[1].SetCounter();
					playerflag = 1;
				}
				b++;
			}
		}
		if (top && y > 0)
			if (brd.cells[x + brd.size.x * (y - 1)].left && brd.cells[x + brd.size.x * (y - 1)].top)
				b += brd.cells[x + brd.size.x * (y - 1)].Update();
		if (left && x > 0)
			if (brd.cells[brd.size.x * y + x - 1].left && brd.cells[brd.size.x * y + x - 1].top)
				b += brd.cells[brd.size.x * y + x - 1].Update();
	}
	return b;
}

/****************************************************************************************************/
/*												Draw												*/
/****************************************************************************************************/
void Board::Cell::Draw() const
{
	Color c;
	int x = position.x * brd.cellsize.x + brd.topleft.x;
	int y = position.y * brd.cellsize.y + brd.topleft.y;
	switch (playerflag)
	{
	case -1:
		c = brd.brdclr.foreground; break;
	case 0:
		c = brd.brdclr.player1; break;
	case 1:
		c = brd.brdclr.player2; break;
	}
	brd.gfx.DrawRectangleDim(x + brd.borderwidth, y + brd.borderwidth,
		brd.cellsize.x - brd.borderwidth, brd.cellsize.y - brd.borderwidth, c);
	if ((position.x + position.y * brd.size.x) == brd.lastclickedCell.first)
		if (brd.lastclickedCell.second)
			brd.gfx.DrawRectangle(x, y, x + brd.borderwidth + brd.cellsize.x, y + brd.borderwidth, brd.brdclr.lastclicked);
		else
			brd.gfx.DrawRectangle(x, y, x + brd.borderwidth, y + brd.borderwidth + brd.cellsize.y, brd.brdclr.lastclicked);
	else {
		if (top)
			brd.gfx.DrawRectangle(x, y, x + brd.borderwidth + brd.cellsize.x, y + brd.borderwidth, brd.brdclr.clicked);
		if (left)
			brd.gfx.DrawRectangle(x, y, x + brd.borderwidth, y + brd.borderwidth + brd.cellsize.y, brd.brdclr.clicked);
	}
}
