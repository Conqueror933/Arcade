#pragma once
#include "Board.h"

class TwoPlayer : public Board
{
public:
	//Fill Screen
	TwoPlayer(Graphics& gfx, const BoardColors brdclr, const Vec2<int> cellcount, const double borderthicknessratio);
	//Borders
	TwoPlayer(Graphics& gfx, const BoardColors brdclr, const Vec2<int> cellcount, const Vec2<int> cellsize, const double borderthicknessratio);
	TwoPlayer(const TwoPlayer& brd) = delete;
	TwoPlayer& operator=(const TwoPlayer& brd) = delete;
	~TwoPlayer() = default;

public:
	int Update(int x, int y) override;

private:
	int player1counter = 0;
	int player2counter = 0;
	int turncounter = 0;
};
