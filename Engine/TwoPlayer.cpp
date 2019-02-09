#include "TwoPlayer.h"
#include <assert.h>

TwoPlayer::TwoPlayer(Graphics & gfx, const BoardColors brdclr, const Vec2<int> cellcount, const double borderthicknessratio)
	:
	Board(gfx, brdclr, cellcount, borderthicknessratio)
{
}

TwoPlayer::TwoPlayer(Graphics & gfx, const BoardColors brdclr, const Vec2<int> cellcount, const Vec2<int> cellsize, const double borderthicknessratio)
	:
	Board(gfx, brdclr, cellcount, cellsize, borderthicknessratio)
{
}

int TwoPlayer::Update(int mouse_x, int mouse_y)
{
	set = false;
	int x = (mouse_x - topleft.x) / cellsize.x;
	int y = (mouse_y - topleft.y) / cellsize.y;
	if (x >= 0 && x < cellcount.x && y >= 0 && y < cellcount.y)
		//if(cells[x + cellcount.x * y].Update(mouse_x, mouse_y))
		if (turncounter % 2 == 0) {
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
			}
			else
				if (set)
					turncounter++;
		}
		else
		{
			if (auto temp = cells[x + cellcount.x * y].Update((mouse_x - topleft.x) % cellsize.x, (mouse_y - topleft.y) % cellsize.y, Player2))
			{
				cellsfilled += temp;
				player2counter += temp;
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
			}
			else
				if (set)
					turncounter++;
		}
	return 0;
}