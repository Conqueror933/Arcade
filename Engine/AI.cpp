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
	int index = 0;
	for (; index < cellstate.size(); index++)
		if (cellstate[index] == 3)
			break;
	if (index != cellstate.size())
	{
		int temp = 0;
		if (cells[index].top)
			if (cells[index].left)
				if (!CheckRight(index)) //NOT LeftClick, its + not -
					temp += cells[index + 1].Update(leftclick.x, leftclick.y, Player2); //set right
				else
					temp += cells[index + cellcount.x].Update(topclick.x, topclick.y, Player2); //set bottom
			else
				temp += LeftClick(index); //set left
		else
			temp += TopClick(index); //set top
		return temp;
	}
	return -1;
}

bool AI::CheckRight(int index)
{
	if ((index + 1) % cellcount.x != 0) //not on the right side
		if (!cells[index + 1].left) //check rights left
			return false;
	return true;
}

bool AI::CheckBottom(int index)
{
	if (index / cellcount.x != cellcount.y - 1) //not at the bottom
		if (!cells[index + cellcount.x].top) //check bottoms top
			return false;
	return true;
}

void AI::ManageCellState()
{//int = index, bool: true = top, false = left
	cellstate[lastclickedCell.first] += 1;
	if (lastclickedCell.second) {
		if (lastclickedCell.first >= cellcount.x)
			cellstate[lastclickedCell.first - cellcount.x] += 1;
	}
	else
		if (lastclickedCell.first % cellcount.x > 0)
			cellstate[lastclickedCell.first - 1] += 1;
}

inline int AI::TopClick(int index)
{//actually useless now
	return cells[index].Update(topclick.x, topclick.y, Player2);
}

inline int AI::LeftClick(int index)
{//actually useless now
	return cells[index].Update(leftclick.x, leftclick.y, Player2);
}

std::pair<bool, int> AI::IsValid(int i) //bool: valid at all //int: top 1, left 2, both 3
{
	if (cellstate[i] > 1) //check self
		return {false, 0};
	else
	{
		//index = 10 % 10 = 0 -> left -> left cant be set
		bool left = (i % cellcount.x == 0 ? false : cellstate[i - 1] < 2);
		//index = 10 < 10 -> top -> top cant be set
		bool top = (i < cellcount.x ? false : cellstate[i - cellcount.x] < 2);
		if (cells[i].top) //if my top is set, check validity of my left side
			if (left) //check left validity 
				return { true, 2 };
			else
				return { false, 0 };
		else if (cells[i].left) //if my left is set, check validity of above
			if (top) //check top
				return { true, 1 };
			else
				return { false, 0 };
		else //so my top and my left AREN'T set
			if (left && top)
				return { true, 3 };
			else if (left)
				return { true, 2 };
			else if (top)
				return { true, 1 };
			else
				return { false, 0 };
	}
}

int AI::Update(int mouse_x, int mouse_y)
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
					return 3;
			}
			ManageCellState(); //playerclick
		}
		else
			if (set) {
				ManageCellState(); //playerclick
				AIstuff();
				if (cellsfilled == cellcount.x * cellcount.y)
				{
					if (player1counter > player2counter)
						return 1;
					else if (player1counter < player2counter)
						return 2;
					else
						return 3;
				}
			}
	return 0;
}

EasyAI::EasyAI(Graphics & gfx, const BoardColors brdclr, const Vec2<int> cellcount, const double borderthicknessratio)
	:
	AI(gfx,brdclr, cellcount, borderthicknessratio)
{
}

EasyAI::EasyAI(Graphics & gfx, const BoardColors brdclr, const Vec2<int> cellcount, const Vec2<int> cellsize, const double borderthicknessratio)
	:
	AI(gfx, brdclr, cellcount, cellsize, borderthicknessratio)
{
}

void EasyAI::AIstuff()
{
	std::mt19937 rng(rd());
	std::uniform_int_distribution<unsigned int> dice(0u, cellcount.x*cellcount.y - 1);
	std::uniform_int_distribution<unsigned int> coin(0u, 1u);
	AIset = false;
	while (!AIset && (cellsfilled != cellcount.x * cellcount.y)) //if ai fills a cell, go again
	{
		ManageCellState();
		int cftemp = 0; //cellsfilledtemp ... cause cellsfilled already exists
						//if there is a cell with 3 sides closed, capture it
		int temp = FindCellWith3();
		if (temp > 0)
			cftemp += temp;
		//else click on a random cell with less than 3 set
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
				cftemp += LeftClick(calc);
			else if (y == cellcount.x*cellcount.y) //all left are filled -> click on a top
				cftemp += TopClick(calc);
			else //all left nor all top are filled -> throw a coin
			{
				if (coin(rng) == 0)
					cftemp += TopClick(calc);
				else
					cftemp += LeftClick(calc);
			}
		}
		if (cftemp > 0)
			AIset = false;
		else
			AIset = true;
		cellsfilled += cftemp;
		player2counter += cftemp;
	}
}

MediumAI::MediumAI(Graphics & gfx, const BoardColors brdclr, const Vec2<int> cellcount, const double borderthicknessratio)
	:
	AI(gfx, brdclr, cellcount, borderthicknessratio)
{
}

MediumAI::MediumAI(Graphics & gfx, const BoardColors brdclr, const Vec2<int> cellcount, const Vec2<int> cellsize, const double borderthicknessratio)
	:
	AI(gfx, brdclr, cellcount, cellsize, borderthicknessratio)
{
}

void MediumAI::AIstuff()
{
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> dice(0, cellcount.x*cellcount.y - 1);
	std::uniform_int_distribution<int> coin(0, 1);
	AIset = false;
	while (!AIset && (cellsfilled != cellcount.x * cellcount.y)) //if ai fills a cell, go again
	{
		int cftemp = 0; //cellsfilledtemp ... cause cellsfilled already exists
		//if there is a cell with 3 sides closed, capture it
		int temp = FindCellWith3();
		if (temp > 0)
			cftemp += temp;
		//else click on a random cell with less than 3 set
		else
		{
			int calc = dice(rng);
			//find all possible valid to set cells
			std::vector<std::pair<int, int>> allcells1; // all cells with 1 or 0 set
			for (int i = 0; i < (int)cellstate.size(); i++) //find all 1 set cells
			{//check all 4 sides and put only in when actually valid
				std::pair<bool, int> valid = IsValid(i);
				if (valid.first)
					allcells1.emplace_back(std::pair<int, int>{ i, valid.second }); //bool: valid at all //int: top 1, left 2, both 3
			}
			if (allcells1.empty()) { //empty == there are no good cells to pick
				//check top and left, maybe toss a coin
				set = false;
				while (!set) {
					if (cells[calc].top)
						if (cells[calc].left)
							calc = dice(rng);
						else
							cftemp += LeftClick(calc);
					else
						if (cells[calc].left)
							cftemp += TopClick(calc);
						else
							if (coin(rng) == 0)
								cftemp += LeftClick(calc);
							else
								cftemp += TopClick(calc);
				}
			}
			else //there are still good cells to pick from
			{
				std::uniform_int_distribution<int> dice1(0, allcells1.size()-1);
				calc = dice1(rng);
				//at this point it is guaranteed that either top or left are settable
				if (allcells1[calc].second == 3)
					if (coin(rng) == 0)
						cftemp += LeftClick(allcells1[calc].first);
					else
						cftemp += TopClick(allcells1[calc].first);
				else if (allcells1[calc].second == 2)
					cftemp += LeftClick(allcells1[calc].first);
				else if (allcells1[calc].second == 1)
					cftemp += TopClick(allcells1[calc].first);
			}
		}
		if (cftemp > 0)
			AIset = false;
		else
			AIset = true;
		cellsfilled += cftemp;
		player2counter += cftemp;
		ManageCellState(); //AIclick
	}
}

HardAI::HardAI(Graphics & gfx, const BoardColors brdclr, const Vec2<int> cellcount, const double borderthicknessratio)
	:
	AI(gfx, brdclr, cellcount, borderthicknessratio)
{
}

HardAI::HardAI(Graphics & gfx, const BoardColors brdclr, const Vec2<int> cellcount, const Vec2<int> cellsize, const double borderthicknessratio)
	:
	AI(gfx, brdclr, cellcount, cellsize, borderthicknessratio)
{
}

void HardAI::FindAllCellsWith1()
{
	for (int i = 0; i < (int)cellstate.size(); i++) //find all 1 set cells
	{//check all 4 sides and put only in when actually valid
		std::pair<bool, int> valid = IsValid(i);
		if (valid.first)
			allcells1.emplace_back(std::pair<int, int>{ i, valid.second }); //bool: valid at all //int: top 1, left 2, both 3
	}
}

void HardAI::FindAllCellsWith3()
{
	for (int index = 0; index < cellstate.size(); index++)
		if (cellstate[index] == 3) 
			if (cells[index].top)
				if (cells[index].left)
					if (!CheckRight(index)) //NOT LeftClick, its + not -
						allcells3.emplace_back(std::pair<int, Direction>{index, dright}); //set right
					else
						allcells3.emplace_back(std::pair<int, Direction>{index, dbottom}); //set bottom
				else
					allcells3.emplace_back(std::pair<int, Direction>{index, dleft}); //set left
			else
				allcells3.emplace_back(std::pair<int, Direction>{index, dtop}); //set top
}

void HardAI::AIstuff() //MediumAI in disguise for now :)
{
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> dice(0, cellcount.x*cellcount.y - 1);
	std::uniform_int_distribution<int> coin(0, 1);
	AIset = false;
	while (!AIset && (cellsfilled != cellcount.x * cellcount.y)) //if ai fills a cell, go again
	{
		int cftemp = 0; //cellsfilledtemp ... cause cellsfilled already exists
						//if there is a cell with 3 sides closed, capture it			
		/*
			1. check cells for for 3s, dont take them yet tho
			1.1 if there are cells with 3, calculate how many it gives, make a vector of vectors or a map(maybe) to keep track
			1.2 decide on whats best for me, pick that
			2. if there are no 3s,
			2.1 look for cells with 0 or 1, do same thing as medium
			2.2 if allcells1.isempty() do step 1.1&1.2
			2.3 if there are 0s or 1s, random?

			3s and 1s check have to be parallel, if there are 3s check if there are 1s, if there are 1s, just take it, if there are no 1s, calculate boardstate and find the lowest give away and 2nd lowest, cause thats what he will give me, to decide im gonna be an asshole
		*/
		int calc = dice(rng);
		FindAllCellsWith3();
		FindAllCellsWith1();
		if (allcells3.empty())
		{
			if (allcells1.empty())
			{
				//calculate the best giveaway
			}
			else
			{
				//random?
				std::uniform_int_distribution<int> dice1(0, allcells1.size() - 1);
				calc = dice1(rng);
				//at this point it is guaranteed that either top or left are settable
				if (allcells1[calc].second == 3)
					if (coin(rng) == 0)
						cftemp += LeftClick(allcells1[calc].first);
					else
						cftemp += TopClick(allcells1[calc].first);
				else if (allcells1[calc].second == 2)
					cftemp += LeftClick(allcells1[calc].first);
				else if (allcells1[calc].second == 1)
					cftemp += TopClick(allcells1[calc].first);
			}
		}
		else
		{
			if (allcells1.empty())
			{
				//calculate if its worth taking ALL 3s that are connected
				//calculate best giveaway
			}
			else
			{
				//Takethe3
				//random?
			}
		}
		if (cftemp > 0)
			AIset = false;
		else
			AIset = true;
		cellsfilled += cftemp;
		player2counter += cftemp;
		ManageCellState(); //AIclick
	}
}
