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

	//	//calculate cellsize
	//cellsize(Vec2<int>(Vec2<float>{
	//	Vec2<float>::constminus((Vec2<float>(bottomright) - (float)borderwidth), Vec2<float>(topleft)) /
	//	Vec2<float>(size) + Vec2<float>{0.5f, 0.5f}
	//})) //dis is not good...
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
			//errorchecking for right and bottom
			//bool right; x == size.x - 1 ? right = true : right = cells[size.x * y + x + 1].left;
			//bool bottom; y == size.y - 1 ? bottom = true : bottom = cells[x + size.x * (y + 1)].top;
			//if (right && bottom && cells[x + size.x * y].top && cells[x + size.x * y].left)
			//{
				//cellsfilled++;
				//if (turncounter % 2 == 0) {
				//	players[0].SetCounter();
				//	cells[x + size.x * y].playerflag = 0;
				//}
				//else {
				//	players[1].SetCounter();
				//	cells[x + size.x * y].playerflag = 1;
				//}

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
	//int r;
	//int i = FindCell(x, y);
	//Vec2<int> loc = FindClickPos(x, y);
	//if (i >= 0 && i <= size * size)
	//{
	//	Direction e = DetectMouseInput(i, loc);
	//	//clicked cell
	//	r = cells[i].Update(e, plr); // == UpdateAdjacent(i, 0, e, plr);
	//	plr.Update(i);
	//	if (r == 1)//last clicked color change stuff
	//	{
	//		lastclickedCell = i;
	//		lastclickedDirection = e;
	//	}
	//	// adjacent cells
	//	switch (e) {
	//	case etop:
	//		e = ebottom;
	//		UpdateAdjacent(i, -1, e, plr);
	//		break;
	//	case ebottom:
	//		e = etop;
	//		UpdateAdjacent(i, 1, e, plr);
	//		break;
	//	case eleft:
	//		e = eright;
	//		UpdateAdjacent(i, -size, e, plr);
	//		break;
	//	case eright:
	//		e = eleft;
	//		UpdateAdjacent(i, size, e, plr);
	//		break;
	//	}
	//}
	//else
	//{
	//	r = 0;
	//}
	//return r;
}

//bool Board::GameEnded()
//{
//	int filled = 0;
//	for (int i = 0; i < size.x*size.y; i++)
//	{
//		filled = filled && cells[i].GetBorderfilled();
//	}
//	return filled;
//}
//
//int Board::Cellsfilled()
//{
//	cellsfilled = 0;
//	for (int i = 0; i < size*size; i++)
//	{
//		if (cells[i].GetBorderfilled())
//			cellsfilled++;
//	}
//	return cellsfilled;
//}
//
//void Board::UpdateAdjacent(int i, int offset, Direction e, Player& plr)
//{
//	i += offset;
//	if (i <= size * size && i >= 0)
//		cells[i].Update(e, plr);
//}
//
//Direction Board::DetectMouseInput(int i, Vec2<int> loc)
//{
//	//assert(FindCell());
//	//assert(FindClickPos());
//	int max = GetCellSize();
//	int min = 0;
//	int tlcut = GetCellBorderwidth();	//topleftcut
//	int brcut = max - tlcut;			//bottomrightcut
//
//	if (Collision(tlcut, min, brcut, tlcut, loc))
//	{
//		return etop;
//	}
//	if (Collision(tlcut, brcut, brcut, max, loc))
//	{
//		return ebottom;
//	}
//	if (Collision(min, tlcut, tlcut, brcut, loc))
//	{
//		return eleft;
//	}
//	if (Collision(brcut, tlcut, max, brcut, loc))
//	{
//		return eright;
//	}
//	return error;
//}
//
//int Board::FindCell(int x, int y)
//{
//	int s = GetCellSize();
//	if (x > 0 && x < s * size + boardborder &&
//		y > 0 && y < s * size + boardborder)
//	{
//		Vec2<int> loc{ (x - boardborder) / s, (y - boardborder) / s };
//		int i = loc.y + loc.x*size;			//i = Position of Cell in Array
//		return i;
//	}
//	return -1;
//}
//
//Vec2<int> Board::FindClickPos(int x, int y)
//{
//	int s = GetCellSize();
//	if (x > 0 && x < s * size + boardborder &&
//		y > 0 && y < s * size + boardborder)
//	{
//		Vec2<int> loc{ (x - boardborder) % s, (y - boardborder) % s };
//		return loc;
//	}
//	return { -1,-1 };
//}
//
//const bool Board::Collision(const int x0, const int y0, const int x1, const int y1, Vec2<int> to_check)
//{
//	if (to_check.x >= x0 && to_check.y >= y0 &&
//		to_check.x <= x1 && to_check.y <= y1)
//		return true;
//	else
//		return false;
//}


/****************************************************************************************************/
/*												Draw												*/
/****************************************************************************************************/
void Board::Draw() const
{
	for (auto i = 0u; i < cells.size(); i++)
	{
		cells[i].Draw();
	}
	/*if (lastclickedCell > -1)
		cells[lastclickedCell].DrawEdges(Colors::Green, lastclickedDirection);*/
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
			if (!top) { top = true; brd.set = true; }
		if (mouse_x > 0 && mouse_x < brd.borderwidth &&
			mouse_y > brd.borderwidth && mouse_y < brd.cellsize.y)
			if (!left) { left = true; brd.set = true; }
		return Update();
	}
	return 0;
	//int r = UpdateBorders(e);
	//if (top && bottom && left && right)
	//	borderfilled = true;
	//if (borderfilled && !set)
	//{
	//	SetColor(plr.GetColor());
	//	plr.SetCounter();
	//	set = true;
	//}
	//return r;
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

//int Board::Cell::UpdateBorders(Direction e)
//{
//	switch (e)
//	{
//	case etop:
//		if (!top)
//		{
//			top = true;
//			return 1;
//		}
//		else
//			return 0;
//	case ebottom:
//		if (!bottom)
//		{
//			bottom = true;
//			return 1;
//		}
//		else
//			return 0;
//	case eleft:
//		if (!left)
//		{
//			left = true;
//			return 1;
//		}
//		else
//			return 0;
//	case eright:
//		if (!right)
//		{
//			right = true;
//			return 1;
//		}
//		else
//			return 0;
//	}
//	return 0;
//}

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
	if (top)
		brd.gfx.DrawRectangle(x, y, x + brd.borderwidth + brd.cellsize.x, y + brd.borderwidth, brd.brdclr.clicked);
	if(left)
		brd.gfx.DrawRectangle(x, y, x + brd.borderwidth, y + brd.borderwidth + brd.cellsize.y, brd.brdclr.clicked);

	//gfx.DrawRectangle(x, y, x + size, y + size, brd.borderColor);
	//gfx.DrawRectangle(x + borderwidth, y + borderwidth, x + size - borderwidth, y + size - borderwidth, c);
}

//const void Board::Cell::DrawEdges()
//{
//	if (top)
//		gfx.DrawRectangle(x - borderwidth, y - borderwidth, x + size + borderwidth, y + borderwidth, brd.clickedColor);
//	if (bottom)
//		gfx.DrawRectangle(x - borderwidth, y + size - borderwidth, x + size + borderwidth, y + size + borderwidth, brd.clickedColor);
//	if (left)
//		gfx.DrawRectangle(x - borderwidth, y - borderwidth, x + borderwidth, y + size + borderwidth, brd.clickedColor);
//	if (right)
//		gfx.DrawRectangle(x + size - borderwidth, y - borderwidth, x + size + borderwidth, y + size + borderwidth, brd.clickedColor);
//}
//
//const void Board::Cell::DrawEdges(Color c, Direction lc)
//{
//	switch (lc) {
//	case etop:
//		if (top)
//			gfx.DrawRectangle(x - borderwidth, y - borderwidth, x + size + borderwidth, y + borderwidth, c);
//		break;
//	case ebottom:
//		if (bottom)
//			gfx.DrawRectangle(x - borderwidth, y + size - borderwidth, x + size + borderwidth, y + size + borderwidth, c);
//		break;
//	case eleft:
//		if (left)
//			gfx.DrawRectangle(x - borderwidth, y - borderwidth, x + borderwidth, y + size + borderwidth, c);
//		break;
//	case eright:
//		if (right)
//			gfx.DrawRectangle(x + size - borderwidth, y - borderwidth, x + size + borderwidth, y + size + borderwidth, c);
//		break;
//	}
//}