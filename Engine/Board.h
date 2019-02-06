#pragma once

#include "Graphics.h"
#include <vector>
#include "Vec2.h"
#include "Player.h"

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
	std::pair<int, bool> lastclickedCell = { -1, false }; //int = index, bool: true = top, false = left
	bool set;

	std::vector<Player> players;
	int turncounter = 0;
};
