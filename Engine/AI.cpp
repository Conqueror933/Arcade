#include "AI.h"

AI::AI(Graphics & gfx, const BoardColors brdclr, const Vec2<int> cellcount, const double borderthicknessratio)
	:
	Board(gfx, brdclr, cellcount, borderthicknessratio)
{
	Init(*this);	
}

AI::AI(Graphics & gfx, const BoardColors brdclr, const Vec2<int> cellcount, const Vec2<int> cellsize, const double borderthicknessratio)
	: 
	Board(gfx, brdclr, cellcount, cellsize, borderthicknessratio)
{
	Init(*this);
}

void AI::Init(AI & ai)
{
	//reserve Cell space to avoid reallocating
	ai.cellstate.resize(ai.cellcount.x*ai.cellcount.y, 0);
	//Set cellstate TOP
	for (int i = 0; i < ai.cellcount.x; i++)
	{
		ai.cellstate[i] += 1; //ai.totalnumberofcellbordersset++;
	}
	//Set cellstate LEFT
	for (int i = 0; i < ai.cellcount.x*ai.cellcount.y; i += ai.cellcount.x)
	{
		ai.cellstate[i] += 1; //ai.totalnumberofcellbordersset++;
	}
	//Set cellstate BOTTOM
	for (int i = (ai.cellcount.y - 1) * ai.cellcount.x; i < ai.cellcount.x * ai.cellcount.y; i++)
	{
		ai.cellstate[i] += 1; //ai.totalnumberofcellbordersset++;
	}
	//Set cellstate RIGHT
	for (int i = ai.cellcount.x - 1; i < ai.cellcount.x*ai.cellcount.y; i += ai.cellcount.x)
	{
		ai.cellstate[i] += 1; //ai.totalnumberofcellbordersset++;
	}
}

int AI::FindCellWith3()
{
	for (auto i = 0u; i < cellstate.size(); i++)
		if (cellstate[i] == 3)
			return i;
	return -1;
}

bool AI::CheckRight(int index)
{
	if ((index + 1) % cellcount.y != 0) //not on the right side
		if (!cells[index + 1].left) { //check rights left
			cellstate[index + 1] += 1;
			return true;
		}
	return false;
}

bool AI::CheckBottom(int index)
{
	if (index / cellcount.x != cellcount.y - 1) //not at the bottom
		if (!cells[index + cellcount.x].top) {//check bottoms top
			cellstate[index + cellcount.x] += 1;
			return true;
		}
	return false;
}

void AI::ManageCellState()
{
	cellstate[lastclickedCell.first] += 1;
	if (lastclickedCell.second) {
		if (lastclickedCell.first >= cellcount.x)
			cellstate[lastclickedCell.first - cellcount.x] += 1;
	}
	else
		if (lastclickedCell.first % cellcount.x > 0)
			cellstate[lastclickedCell.first - 1] += 1;
}

EasyAI::EasyAI(Graphics & gfx, const BoardColors brdclr, const Vec2<int> cellcount, const double borderthicknessratio)
	:
	AI(gfx,brdclr, cellcount, borderthicknessratio)
{
}

EasyAI::EasyAI(Graphics & gfx, const BoardColors brdclr, const Vec2<int> cellcount, const Vec2<int> cellsize, const double borderthicknessratio)
	:
	AI(gfx,brdclr,cellcount,cellsize,borderthicknessratio)
{
}

int EasyAI::Update(int mouse_x, int mouse_y)
{
	set = false;
	int x = (mouse_x - topleft.x) / cellsize.x;
	int y = (mouse_y - topleft.y) / cellsize.y;
	if (x >= 0 && x < cellcount.x && y >= 0 && y < cellcount.y)
			if (auto temp = cells[x + cellcount.x * y].Update((mouse_x - topleft.x) % cellsize.x, (mouse_y - topleft.y) % cellsize.y, Player1))
			{
				cellsfilled += temp;
				player1counter += temp;
				//check who won
				if (cellsfilled == cellcount.x * cellcount.y)
				{
					if (player1counter > player2counter)
						return 1;
					else if (player1counter < player2counter)
						return 2;
					else
						return -1;
				}
				ManageCellState();
			}
			else
				if (set) {
					ManageCellState();
					AIstuff();
					if (cellsfilled == cellcount.x * cellcount.y)
					{
						if (player1counter > player2counter)
							return 1;
						else if (player1counter < player2counter)
							return 2;
						else
							return -1;
					}
				}
	return 0;
}

void EasyAI::AIstuff()
{
	std::mt19937 rng(rd());
	std::uniform_int_distribution<unsigned int> dice(0u, cellcount.x*cellcount.y - 1);
	std::uniform_int_distribution<unsigned int> coin(0u, 1u);
	AIset = false;
	while (!AIset && (cellsfilled != cellcount.x * cellcount.y)) //if ai fills a cell, go again
	{
		int temp = 0;
		//if there is a cell with 3 sides closed, capture it
		int index = FindCellWith3();
		if (index != -1)
		{
			if (cells[index].top) {
				if (cells[index].left) {
					if (CheckRight(index))
						temp = cells[index + 1].Update(leftclick.x, leftclick.y, Player2);
					if (CheckBottom(index))
						temp = cells[index + cellcount.x].Update(topclick.x, topclick.y, Player2);
				}
				else {
					temp = cells[index].Update(leftclick.x, leftclick.y, Player2);
					cellstate[index - 1] += 1;
				}
			}
			else if (cells[index].left) {
				temp = cells[index].Update(topclick.x, topclick.y, Player2);
				cellstate[index - cellcount.x] += 1;
			}
			cellstate[index] += 1;
		}
		//else click on a random cell
		else
		{
			int calc = dice(rng);
			int x = 0;
			int y = 0;
			for (auto i = 0; i < cellstate.size(); i++) {
				if (cells[i].top)
					x++;
				if (cells[i].left)
					y++;
			}
			if (x == cellcount.x*cellcount.y) //all top are filled -> click on a left
			{
				//leftclick
				while (cells[calc].left) calc = dice(rng); //find a cell whose left isnt set
				temp = cells[calc].Update(leftclick.x, leftclick.y, Player2);
				cellstate[calc - 1] += 1;
			}
			else if (y == cellcount.x*cellcount.y) //all left are filled -> click on a top
			{
				//topclick
				while (cells[calc].top) calc = dice(rng); //find a cell whose top isnt set
				temp = cells[calc].Update(topclick.x, topclick.y, Player2);
				cellstate[calc - cellcount.x] += 1;
			}
			else //all left nor all top are filled -> throw a coin
			{
				if (coin(rng) == 0)
				{
					//topclick
					while (cells[calc].top) calc = dice(rng); //find a cell whose top isnt set
					temp = cells[calc].Update(topclick.x, topclick.y, Player2);
					cellstate[calc - cellcount.x] += 1;
				}
				else
				{
					//leftclick
					while (cells[calc].left) calc = dice(rng); //find a cell whose left isnt set
					temp = cells[calc].Update(leftclick.x, leftclick.y, Player2);
					cellstate[calc - 1] += 1;
				}
			}
			cellstate[calc] += 1;
		}
		if (temp > 0)
			AIset = false;
		else
			AIset = true;
		cellsfilled += temp;
		player2counter += temp;
	}
}
