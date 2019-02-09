#pragma once

#include "Board.h"

class AI : public Board
{
public:
	AI(Board& brd, Color c);
	~AI();
	void Update(int i);

private:
	Board& brd;
	std::vector<int8_t> cellstate;
};

