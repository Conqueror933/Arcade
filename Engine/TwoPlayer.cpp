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

/****************************************************************************************************/
/*												Logic												*/
/****************************************************************************************************/
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

//int TwoPlayer::Cell::Update(int mouse_x, int mouse_y)
//{
//	if (playerflag == -1)
//	{
//		if (mouse_x > TPbrd.cellborderwidth && mouse_x < TPbrd.cellsize.x &&
//			mouse_y > 0 && mouse_y < TPbrd.cellborderwidth)
//			if (!top) {
//				top = true; TPbrd.set = true;
//				TPbrd.lastclickedCell = { pos.x + pos.y * TPbrd.cellcount.x, true };
//			}
//		if (mouse_x > 0 && mouse_x < TPbrd.cellborderwidth &&
//			mouse_y > TPbrd.cellborderwidth && mouse_y < TPbrd.cellsize.y)
//			if (!left) {
//				left = true; TPbrd.set = true;
//				TPbrd.lastclickedCell = { pos.x + pos.y * TPbrd.cellcount.x, false };
//			}
//		return 5;// Update();
//	}
//	return 0;
//}
//
//int TwoPlayer::Cell::Update()
//{
//	int b = 0;
//	if (playerflag == -1)
//	{
//		int x = pos.x;
//		int y = pos.y;
//
//		//error- and checking for right and bottom
//		if (left && top) {
//			bool right = (x == brd.size.x - 1 ? true : brd.cells[brd.size.x * y + x + 1].left);
//			bool bottom = (y == brd.size.y - 1 ? true : brd.cells[x + brd.size.x * (y + 1)].top);
//			if (right && bottom && top && left) {
//				if (brd.turncounter % 2 == 0) {
//					brd.players[0].SetCounter();
//					playerflag = 0;
//				}
//				else {
//					brd.players[1].SetCounter();
//					playerflag = 1;
//				}
//				b++;
//			}
//		}
//		if (top && y > 0)
//			if (brd.cells[x + brd.size.x * (y - 1)].left && brd.cells[x + brd.size.x * (y - 1)].top)
//				b += brd.cells[x + brd.size.x * (y - 1)].Update();
//		if (left && x > 0)
//			if (brd.cells[brd.size.x * y + x - 1].left && brd.cells[brd.size.x * y + x - 1].top)
//				b += brd.cells[brd.size.x * y + x - 1].Update();
//	}
//	return b;
//}
