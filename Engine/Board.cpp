#include "Board.h"
#include "Graphics.h"
#include "Player.h"
#include "Enum.h"
#include <assert.h>

Board::Board(Graphics & gfx)
	:
	gfx(gfx),
	size(0)
{
}

Board::Board(Graphics & gfx, const int size, const int cellsize)
	:
	gfx(gfx),
	size(size)
{
	cells.reserve(size*size);
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			cells.emplace_back( *this, gfx, Vec2<int>{ x,y }, boardColor, cellsize );
		}
	}

	for (int i = 0; i < size; i++)
	{
		cells[i].UpdateBorders(eleft);
	}
	for (int i = size * (size - 1); i < size*size; i++)
	{
		cells[i].UpdateBorders(eright);
	}
	for (int i = 0; i < size*size; i += size)
	{
		cells[i].UpdateBorders(etop);
	}
	for (int i = size - 1; i < size*size; i += size)
	{
		cells[i].UpdateBorders(ebottom);
	}
}

Board::Board(Graphics & gfx, Player& plr, const int size, const int cellsize)
	:
	gfx(gfx),
	size(size)
{
	cells.reserve(size*size);
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			cells.emplace_back(*this, gfx, Vec2<int>{ x, y }, boardColor, cellsize);
		}
	}

	for (int i = 0; i < size; i++)
	{
		cells[i].UpdateBorders(eleft);
		plr.Update(i);
	}
	for (int i = size * (size - 1); i < size*size; i++)
	{
		cells[i].UpdateBorders(eright);
		plr.Update(i);
	}
	for (int i = 0; i < size*size; i += size)
	{
		cells[i].UpdateBorders(etop);
		plr.Update(i);
	}
	for (int i = size - 1; i < size*size; i += size)
	{
		cells[i].UpdateBorders(ebottom);
		plr.Update(i);
	}
}

Board::Board(const Board & brd)
	:
	gfx(brd.gfx),
	size(brd.size)
{
}

Board & Board::operator=(const Board & brd)
{
	return *this;
}

/****************************************************************************************************/
/*												Logic												*/
/****************************************************************************************************/
int Board::Update(int x, int y, Player& plr)
{
	int r;
	int i = FindCell(x, y);
	Vec2<int> loc = FindClickPos(x, y);
	if (i >= 0 && i <= size * size)
	{
		Direction e = DetectMouseInput(i, loc);
		//clicked cell
		r = cells[i].Update(e, plr); // == UpdateAdjacent(i, 0, e, plr);
		plr.Update(i);
		if (r == 1)//last clicked color change stuff
		{
			lastclickedCell = i;
			lastclickedDirection = e;
		}
		// adjacent cells
		switch (e) {
		case etop:
			e = ebottom;
			UpdateAdjacent(i, -1, e, plr);
			break;
		case ebottom:
			e = etop;
			UpdateAdjacent(i, 1, e, plr);
			break;
		case eleft:
			e = eright;
			UpdateAdjacent(i, -size, e, plr);
			break;
		case eright:
			e = eleft;
			UpdateAdjacent(i, size, e, plr);
			break;
		}
	}
	else
	{
		r = 0;
	}
	return r;
}

bool Board::GameEnded()
{
	bool filled = true;
	for (int i = 0; i < size*size; i++)
	{
		filled = filled && cells[i].GetBorderfilled();
	}
	return filled;
}

int Board::Cellsfilled()
{
	cellsfilled = 0;
	for (int i = 0; i < size*size; i++)
	{
		if (cells[i].GetBorderfilled())
			cellsfilled++;
	}
	return cellsfilled;
}

void Board::UpdateAdjacent(int i, int offset, Direction e, Player& plr)
{
	i += offset;
	if (i <= size * size && i >= 0)
		cells[i].Update(e, plr);
}

Direction Board::DetectMouseInput(int i, Vec2<int> loc)
{
	//assert(FindCell());
	//assert(FindClickPos());
	int max = GetCellSize();
	int min = 0;
	int tlcut = GetCellBorderwidth();	//topleftcut
	int brcut = max - tlcut;			//bottomrightcut

	if (Collision(tlcut, min, brcut, tlcut, loc))
	{
		return etop;
	}
	if (Collision(tlcut, brcut, brcut, max, loc))
	{
		return ebottom;
	}
	if (Collision(min, tlcut, tlcut, brcut, loc))
	{
		return eleft;
	}
	if (Collision(brcut, tlcut, max, brcut, loc))
	{
		return eright;
	}
	return error;
}

int Board::FindCell(int x, int y)
{
	int s = GetCellSize();
	if (x > 0 && x < s * size + boardborder &&
		y > 0 && y < s * size + boardborder)
	{
		Vec2<int> loc{ (x - boardborder) / s, (y - boardborder) / s };
		int i = loc.y + loc.x*size;			//i = Position of Cell in Array
		return i;
	}
	return -1;
}

Vec2<int> Board::FindClickPos(int x, int y)
{
	int s = GetCellSize();
	if (x > 0 && x < s * size + boardborder &&
		y > 0 && y < s * size + boardborder)
	{
		Vec2<int> loc{ (x - boardborder) % s, (y - boardborder) % s };
		return loc;
	}
	return { -1,-1 };
}

const bool Board::Collision(const int x0, const int y0, const int x1, const int y1, Vec2<int> to_check)
{
	if (to_check.x >= x0 && to_check.y >= y0 &&
		to_check.x <= x1 && to_check.y <= y1)
		return true;
	else
		return false;
}


/****************************************************************************************************/
/*												Draw												*/
/****************************************************************************************************/
const void Board::Draw()
{
	for (int i = 0; i < size*size; i++)
	{
		cells[i].Draw(cells[i].GetColor());
	}
	for (int i = 0; i < size*size; i++)
	{
		cells[i].DrawEdges();
	}
	if (lastclickedCell > -1)
		cells[lastclickedCell].DrawEdges(Colors::Green, lastclickedDirection);
}

/****************************************************************************************************/
/*												Getter												*/
/****************************************************************************************************/
const int Board::GetBoardSize()
{
	return 5;
}

const int Board::GetCellSize()
{
	return cells[0].GetSize();
}

const int Board::GetCellBorderwidth()
{
	return cells[0].GetBorderwidth();
}

const int Board::GetBoardBorder()
{
	return boardborder;
}


/****************************************************************************************************/
/****************************************************************************************************/
/*											Cell Subclass											*/
/****************************************************************************************************/
/****************************************************************************************************/

Board::Cell::Cell(Board& brd, Graphics & gfx, Vec2<int> loc, Color c, const int size)
	:
	gfx(gfx),
	brd(brd),
	loc(loc),
	c(c),
	size(size)
{
}

Board::Cell::~Cell()
{
}

Board::Cell::Cell(const Cell & other)
	:
	gfx(other.gfx),
	brd(other.brd),
	loc(other.loc),
	c(other.c),
	size(other.size)
{
}

Board::Cell& Board::Cell::operator=(Cell other)
{
	return *this;
}

/****************************************************************************************************/
/*												Logic												*/
/****************************************************************************************************/

int Board::Cell::Update(Direction e, Player& plr)
{
	int r = UpdateBorders(e);
	if (top && bottom && left && right)
		borderfilled = true;
	if (borderfilled && !set)
	{
		SetColor(plr.GetColor());
		plr.SetCounter();
		set = true;
	}
	return r;
}

int Board::Cell::UpdateBorders(Direction e)
{
	switch (e)
	{
	case etop:
		if (!top)
		{
			top = true;
			return 1;
		}
		else
			return 0;
	case ebottom:
		if (!bottom)
		{
			bottom = true;
			return 1;
		}
		else
			return 0;
	case eleft:
		if (!left)
		{
			left = true;
			return 1;
		}
		else
			return 0;
	case eright:
		if (!right)
		{
			right = true;
			return 1;
		}
		else
			return 0;
	}
	return 0;
}

/****************************************************************************************************/
/*												Draw												*/
/****************************************************************************************************/
const void Board::Cell::Draw(Color c)
{
	gfx.DrawRectangle(x, y, x + size, y + size, brd.borderColor);
	gfx.DrawRectangle(x + borderwidth, y + borderwidth, x + size - borderwidth, y + size - borderwidth, c);
}

const void Board::Cell::DrawEdges()
{
	if (top)
		gfx.DrawRectangle(x - borderwidth, y - borderwidth, x + size + borderwidth, y + borderwidth, brd.clickedColor);
	if (bottom)
		gfx.DrawRectangle(x - borderwidth, y + size - borderwidth, x + size + borderwidth, y + size + borderwidth, brd.clickedColor);
	if (left)
		gfx.DrawRectangle(x - borderwidth, y - borderwidth, x + borderwidth, y + size + borderwidth, brd.clickedColor);
	if (right)
		gfx.DrawRectangle(x + size - borderwidth, y - borderwidth, x + size + borderwidth, y + size + borderwidth, brd.clickedColor);
}

const void Board::Cell::DrawEdges(Color c, Direction lc)
{
	switch (lc) {
	case etop:
		if (top)
			gfx.DrawRectangle(x - borderwidth, y - borderwidth, x + size + borderwidth, y + borderwidth, c);
		break;
	case ebottom:
		if (bottom)
			gfx.DrawRectangle(x - borderwidth, y + size - borderwidth, x + size + borderwidth, y + size + borderwidth, c);
		break;
	case eleft:
		if (left)
			gfx.DrawRectangle(x - borderwidth, y - borderwidth, x + borderwidth, y + size + borderwidth, c);
		break;
	case eright:
		if (right)
			gfx.DrawRectangle(x + size - borderwidth, y - borderwidth, x + size + borderwidth, y + size + borderwidth, c);
		break;
	}
}

/****************************************************************************************************/
/*												Setter												*/
/****************************************************************************************************/
void Board::Cell::SetColor(Color in_c)
{
	c = in_c;
}

/****************************************************************************************************/
/*												Getter												*/
/****************************************************************************************************/

const Color Board::Cell::GetColor()
{
	return c;
}

const int Board::Cell::GetBorderfilled()
{
	return borderfilled;
}

const int Board::Cell::GetSize()
{
	return size;
}

const int Board::Cell::GetBorderwidth()
{
	return borderwidth;
}

