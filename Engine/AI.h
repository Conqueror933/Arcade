#pragma once

#include "Board.h"
#include "Player.h"

class AI : public Player
{
public:
	AI(Board& brd, int Playernumber, Color c);
	~AI();

private:
	Board& brd;
	std::vector<int8_t> cellstate;
};

