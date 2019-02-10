#pragma once

#include "Board.h"
#include <random>

class AI : public Board
{
public:
	//Fill Screen
	AI(Graphics& gfx, const BoardColors brdclr, const Vec2<int> cellcount, const double borderthicknessratio);
	//Borders
	AI(Graphics& gfx, const BoardColors brdclr, const Vec2<int> cellcount, const Vec2<int> cellsize, const double borderthicknessratio);
	AI(const AI& brd) = delete;
	AI& operator=(const AI& brd) = delete;
	virtual ~AI() = default;

public:
	int Update(int mouse_x, int mouse_y);

private:
	static void Init(AI& ai);

protected:
	int FindCellWith3();
	bool CheckRight(int index);
	bool CheckBottom(int index);
	void ManageCellState();
	int TopClick(int index);
	int LeftClick(int index);
	std::pair<bool, int> IsValid(int index); //bool: valid at all //int: top 1, left 2, both 3
	virtual void AIstuff() = 0;

protected: //AI specific
	const Vec2<int> topclick  = {cellsize.x / 2, cellborderwidth / 2};
	const Vec2<int> leftclick = {cellborderwidth / 2, cellsize.y / 2};
	std::vector<int8_t> cellstate;
	bool AIset = false;
	std::random_device rd;
};

class EasyAI : public AI
{
public:
	//Fill Screen
	EasyAI(Graphics& gfx, const BoardColors brdclr, const Vec2<int> cellcount, const double borderthicknessratio);
	//Borders
	EasyAI(Graphics& gfx, const BoardColors brdclr, const Vec2<int> cellcount, const Vec2<int> cellsize, const double borderthicknessratio);
	EasyAI(const EasyAI& brd) = delete;
	EasyAI& operator=(const EasyAI& brd) = delete;
	~EasyAI() = default;

private:
	void AIstuff() override;
};

class MediumAI : public AI
{
public:
	//Fill Screen
	MediumAI(Graphics& gfx, const BoardColors brdclr, const Vec2<int> cellcount, const double borderthicknessratio);
	//Borders
	MediumAI(Graphics& gfx, const BoardColors brdclr, const Vec2<int> cellcount, const Vec2<int> cellsize, const double borderthicknessratio);
	MediumAI(const MediumAI& brd) = delete;
	MediumAI& operator=(const MediumAI& brd) = delete;
	~MediumAI() = default;

private:
	void AIstuff() override;
};

class HardAI : public AI
{
public:
	//Fill Screen
	HardAI(Graphics& gfx, const BoardColors brdclr, const Vec2<int> cellcount, const double borderthicknessratio);
	//Borders
	HardAI(Graphics& gfx, const BoardColors brdclr, const Vec2<int> cellcount, const Vec2<int> cellsize, const double borderthicknessratio);
	HardAI(const HardAI& brd) = delete;
	HardAI& operator=(const HardAI& brd) = delete;
	~HardAI() = default;

private:
	void AIstuff() override;
};