#include "AI.h"



AI::AI(Board& brd, int Playernumber, Color c)
	:
	Player(Playernumber, c),
	brd(brd)
{
	auto s = brd.GetBoardSize();
	cellstate.resize(s*s, 0);
}


AI::~AI()
{
}
