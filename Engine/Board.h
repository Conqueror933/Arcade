#pragma once

#include "Graphics.h"
#include <vector>
#include "Vec2.h"
#include "Player.h"

//enum Direction
//{
//	Dirtop,
//	Dirleft
//};

struct BoardColors
{
	Color foreground = Colors::LightGray;
	Color background = Colors::Gray;

	Color clicked = Colors::White;
	Color lastclicked = Colors::Green;

	Color player1 = Colors::Blue;
	Color player2 = Colors::Red;
};

class Board
{
private:
	class Cell
	{
	public:
		Cell(Board& brd, Vec2<int> position);
		~Cell();
		Cell(const Cell& other);
		Cell& operator=(const Cell& other);

		int Update();
		int Update(int mouse_x, int mouse_y);
		void Draw() const;

	private:
		Board& brd;
	public:
		Vec2<int> position; //arrayspace
		bool top = false;
		bool left = false;
		int playerflag = -1; //player[0] = 0, player[1] = 1
	};

public:
	Board(Graphics& gfx, const BoardColors brdclr, 
		const Vec2<int> topleft, const Vec2<int> bottomright, const Vec2<int> size, const unsigned int borderthicknessratio = 4);
	Board(const Board& brd) = delete;
	Board& operator=(const Board& brd) = delete;

	int Update(int x, int y);
	void Draw() const;

//private:
//	Direction DetectMouseInput(int i, Vec2<int> loc);
//	int FindCell(int x, int y);
//	Vec2<int> FindClickPos(int x, int y);
//	void UpdateAdjacent(int i, int offset, Direction e, Player& plr);
//	const bool Collision(const int x0, const int y0, const int x1, const int y1, Vec2<int> to_check);

private:
	Graphics& gfx;
	const BoardColors brdclr;
	const Vec2<int> topleft;
	const Vec2<int> bottomright;
	const Vec2<int> size;
	const int borderwidth; //of the cell
	const Vec2<int> cellsize;


	std::vector<Cell> cells;
	int cellsfilled = 0;
	int lastclickedCell = -1;
	bool set;
	//Direction lastclickedDirection;

	std::vector<Player> players;
	int turncounter = 0;
};



/*if (!static_cast<Board*>(curInterface)->GameEnded())
{
GameRunning();
}
else
{
if (players[0].GetCounter() > players[1].GetCounter())
{
//players[0] wins
gfx.DrawRectangle(0, 0, 700, 500, players[0].GetColor());
}
else if (players[0].GetCounter() < players[1].GetCounter())
{
// players[1] wins
gfx.DrawRectangle(0, 0, 700, 500, players[1].GetColor());
}
else
{
//Unentschieden || smth went very wrong
gfx.DrawRectangle(0, 0, 700, 500, Colors::Green);
}
}*/

//void Game::GameRunning()
//{
//	auto brd = static_cast<Board*>(curInterface);
//	while (!wnd.mouse.IsEmpty())
//	{
//		const auto e = wnd.mouse.Read();
//		if (e.GetType() == Mouse::Event::Type::LPress)
//		{
//			int x = wnd.mouse.GetPosX();
//			int y = wnd.mouse.GetPosY();
//
//
//			int old = brd->Cellsfilled();
//			if (timmyturner % 2 == 0)
//			{
//				timmyturner += brd->Update(x, y, players[0]);	//successful click == +1 == next player		//confirmed
//			}												//if click missed == +0 == same player		//confirmed
//			else if (timmyturner % 2 == 1)
//			{
//				timmyturner += brd->Update(x, y, players[1]);
//			}
//			else
//			{
//				//smth went wrong
//				gfx.DrawRectangle(0, 0, 700, 500, Colors::Cyan);
//			}
//			//filled out a cell, so you can go again
//			if (old + 1 <= brd->Cellsfilled())					//has filled cell == -1 == same player
//				timmyturner--;								//if click missed == didnt fill cell == false == -0
//		}
//	}
//}