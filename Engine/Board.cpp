#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx, const BoardColors brdclr, const Vec2<int> cellcount, const double borderthicknessratio)
	:
	gfx(gfx),
	brdclr(brdclr),
	cellcount(cellcount),
	cellsize(CalculateCellSize(cellcount, cellborderwidth)),
	topleft(CalculateTopLeft(cellcount, cellsize)),
	cellborderwidth(CalculateCellBorderWidth1(cellcount, borderthicknessratio))
{
	Init(*this);
}

Board::Board(Graphics & gfx, const BoardColors brdclr, const Vec2<int> cellcount, const Vec2<int> cellsize, const double borderthicknessratio)
	:
	gfx(gfx),
	brdclr(brdclr),
	cellcount(cellcount),
	cellsize(CheckCellSize(cellcount, cellsize, cellborderwidth)),
	topleft(CalculateTopLeft(cellcount, cellsize)),
	cellborderwidth(CalculateCellBorderWidth2(cellsize, borderthicknessratio))
{
	Init(*this);
}

const Vec2<int> Board::CheckCellSize(const Vec2<int> cellcount, const Vec2<int> cellsize, int cellborderwidth)
{
	assert(Graphics::ScreenWidth > cellcount.x * cellsize.x + cellborderwidth);
	assert(Graphics::ScreenHeight < cellcount.y * cellsize.y + cellborderwidth);
	return cellsize;
}

Vec2<int> Board::CalculateCellSize(const Vec2<int> cellcount, int cellborderwidth)
{
	return Vec2<int>((Graphics::ScreenWidth - cellcount.x * cellborderwidth) / cellcount.x, 
		(Graphics::ScreenHeight - cellcount.y * cellborderwidth) / cellcount.y);
}

Vec2<int> Board::CalculateTopLeft(const Vec2<int> cellcount, const Vec2<int> cellsize)
{
	return Vec2<int>((Graphics::ScreenWidth - cellcount.x * cellsize.x) / 2, (Graphics::ScreenHeight - cellcount.y * cellsize.y) / 2);
}

int Board::CalculateCellBorderWidth1(const Vec2<int> cellcount, const double borderthicknessratio)
{
	assert(borderthicknessratio > 0.0);
	assert(borderthicknessratio < 1.0);
	auto x = Graphics::ScreenWidth * borderthicknessratio / (cellcount.x + 1);
	auto y = Graphics::ScreenHeight * borderthicknessratio / (cellcount.y + 1);
	if (x > y)
		return static_cast<int>(y);
	else
		return static_cast<int>(x);
}

int Board::CalculateCellBorderWidth2(const Vec2<int> cellsize, const double borderthicknessratio)
{

	if (cellsize.x > cellsize.y)
		return static_cast<int>((double)cellsize.y * borderthicknessratio);
	else
		return static_cast<int>((double)cellsize.x * borderthicknessratio);
}

void Board::Init(Board& brd)
{
	//reserve Cell space to avoid reallocating
	brd.cells.reserve(brd.cellcount.x*brd.cellcount.y);
	//make Cells
	for (int y = 0; y < brd.cellcount.y; y++)
	{
		for (int x = 0; x < brd.cellcount.x; x++)
		{
			brd.cells.emplace_back(brd, Vec2<int>{ brd.topleft.x + x * brd.cellsize.x, brd.topleft.y + y * brd.cellsize.y}, x + y * brd.cellcount.x);
		}
	}
	//Fill Cells at border of Board
	for (int i = 0; i < brd.cellcount.x; i++)
	{
		brd.cells[i].top = true;
	}
	for (int i = 0; i < brd.cellcount.x*brd.cellcount.y; i += brd.cellcount.x)
	{
		brd.cells[i].left = true;
	}
}

void Board::Draw() const
{
	//Draw Cell Background
	gfx.DrawRectangle(topleft.x, topleft.y, 
		cells[cellcount.x * cellcount.y - 1].pos.x + cellsize.x, cells[cellcount.x * cellcount.y - 1].pos.y + cellsize.y, 
		brdclr.background);	
	//make Right and bottom look filled
	int x = cells[cellcount.x*cellcount.y - 1].pos.x;
	int y = cells[cellcount.x*cellcount.y - 1].pos.y;
	gfx.DrawRectangle(x + cellsize.x, topleft.y, x + cellsize.x + cellborderwidth, y + cellsize.y + cellborderwidth, brdclr.clicked);
	gfx.DrawRectangle(topleft.x, y + cellsize.y, x + cellsize.x + cellborderwidth, y + cellsize.y + cellborderwidth, brdclr.clicked);
	//Draw Cells on Top
	for (auto i = 0u; i < cells.size(); i++)
	{
		cells[i].Draw();
	}
	//Draw lastClicked on Top
	if (lastclickedCell.first > -1)
		cells[lastclickedCell.first].Draw(lastclickedCell.second);
}

/*****************   Cell   ********************/

Board::Cell::Cell(Board& brd, Vec2<int> screenposition, unsigned int index)
	:
	brd(brd),
	pos(screenposition),
	index(index)
{
}

Board::Cell::~Cell()
{
}

int Board::Cell::Update(int mouse_x, int mouse_y, Playerflag plr)
{
	if (playerflag == None)
	{
		int r = 0;
		if (mouse_x > brd.cellborderwidth && mouse_x < brd.cellsize.x &&
			mouse_y > 0 && mouse_y < brd.cellborderwidth)
			if (!top) {
				top = true; brd.set = true;
				brd.lastclickedCell = { index, true };
				if (left)
				{
					bool right  = (index / brd.cellcount.y == brd.cellcount.x - 1 ? true : brd.cells[index + 1].left);
					bool bottom = (index / brd.cellcount.x == brd.cellcount.y - 1 ? true : brd.cells[index + brd.cellcount.x].top);
					if (right && bottom) {
						playerflag = plr; r++;
					}
				}
				if (brd.cells[index - brd.cellcount.x].top && brd.cells[index - brd.cellcount.x].left)
					if (brd.cells[index - brd.cellcount.x + 1].left) {
						brd.cells[index - brd.cellcount.x].playerflag = plr; r++;
					}
			}
		if (mouse_x > 0 && mouse_x < brd.cellborderwidth &&
			mouse_y > brd.cellborderwidth && mouse_y < brd.cellsize.y)
			if (!left) {
				left = true; brd.set = true;
				brd.lastclickedCell = { index, false };
				if (top)
				{
					bool right = (index / brd.cellcount.y == brd.cellcount.x - 1 ? true : brd.cells[index + 1].left);
					bool bottom = (index / brd.cellcount.x == brd.cellcount.y - 1 ? true : brd.cells[index + brd.cellcount.x].top);
					if (right && bottom) {
						playerflag = plr; r++;
					}
				}
				if (brd.cells[index - 1].top && brd.cells[index - 1].left)
					if (brd.cells[index - 1 + brd.cellcount.x].top) {
						brd.cells[index - 1].playerflag = plr; r++;
					}
			}
		return r;
	}
	return 0;
}

void Board::Cell::Draw() const
{
	//decide on Color
	Color c;
	switch (playerflag)
	{
	case None:
		c = brd.brdclr.foreground; break;
	case Player1:
		c = brd.brdclr.player1; break;
	case Player2:
		c = brd.brdclr.player2; break;
	}
	//Draw inner Cell
	brd.gfx.DrawRectangleDim(pos.x + brd.cellborderwidth, pos.y + brd.cellborderwidth,
		brd.cellsize.x - brd.cellborderwidth, brd.cellsize.y - brd.cellborderwidth, c);
	//Draw Edges
	if (top)
		brd.gfx.DrawRectangle(pos.x, pos.y, pos.x + brd.cellborderwidth + brd.cellsize.x, pos.y + brd.cellborderwidth, brd.brdclr.clicked);
	if (left)
		brd.gfx.DrawRectangle(pos.x, pos.y, pos.x + brd.cellborderwidth, pos.y + brd.cellborderwidth + brd.cellsize.y, brd.brdclr.clicked);
}

void Board::Cell::Draw(bool b) const
{
	if(b)
		//top
		brd.gfx.DrawRectangle(pos.x, pos.y, pos.x + brd.cellborderwidth + brd.cellsize.x, pos.y + brd.cellborderwidth, brd.brdclr.lastclicked);
	else
		//left
		brd.gfx.DrawRectangle(pos.x, pos.y, pos.x + brd.cellborderwidth, pos.y + brd.cellborderwidth + brd.cellsize.y, brd.brdclr.lastclicked);
}
