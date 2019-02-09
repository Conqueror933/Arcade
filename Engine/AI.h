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
	virtual int Update(int mouse_x, int mouse_y) = 0;

private:
	static void Init(AI& ai);

protected:
	int FindCellWith3();
	bool CheckRight(int index);
	bool CheckBottom(int index);
	void ManageCellState();

protected: //AI specific
	const Vec2<int> topclick  = {cellsize.x / 2, cellborderwidth / 2};
	const Vec2<int> leftclick = {cellborderwidth / 2, cellsize.y / 2};
	std::vector<int8_t> cellstate;
	bool AIset = false;
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

public:
	int Update(int mouse_x, int mouse_y);

private:
	void AIstuff();

private:
	std::random_device rd;
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

public:
	int Update(int mouse_x, int mouse_y);
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

public:
	int Update(int mouse_x, int mouse_y);
};