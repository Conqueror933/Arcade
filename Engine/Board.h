#pragma once

#include "Graphics.h"
#include <vector>
#include "Vec2.h"
#include "Enum.h"
#include "Player.h"

class Board
{
private:
	class Cell
	{
	public:
		Cell(Board& brd, Graphics& gfx, Vec2<int> loc, Color c, const int size = 30);
		~Cell();
		Cell(const Cell& other);
		Cell& operator=(Cell other);
		int Update(Direction e, Player& plr);
		int UpdateBorders(Direction e);
		const void Draw(Color c);
		const void DrawEdges();
		const void DrawEdges(Color c, Direction lc);
		//Setter:
		void SetColor(Color in_c);
		//Getters:
		const Color GetColor();
		const int GetBorderfilled();
		const int GetSize();
		const int GetBorderwidth();

	private:
		Graphics& gfx;
		Board& brd;
		Vec2<int> loc;
		Color c;
		const int size;//make static again, only need 1 copy, not 64
		const int borderwidth = 5;
		int x = loc.x*size + brd.GetBoardBorder();
		int y = loc.y*size + brd.GetBoardBorder();
		bool set = false;
		bool top = false;
		bool bottom = false;
		bool left = false;
		bool right = false;
		bool borderfilled = false;
	};

public:
	Board(Graphics& gfx);
	Board(Graphics& gfx, const int size, const int cellsize = 30);
	Board(Graphics& gfx, Player& plr, const int size = 8, const int cellsize = 30);
	Board(const Board& brd);
	Board& operator=(const Board& brd);
	int Update(int x, int y, Player& plr);
	bool GameEnded();
	int Cellsfilled();
	const void Draw();
	const int GetBoardSize();
	const int GetCellSize();
	const int GetCellBorderwidth();
	const int GetBoardBorder();

private:
	Direction DetectMouseInput(int i, Vec2<int> loc);
	int FindCell(int x, int y);
	Vec2<int> FindClickPos(int x, int y);
	void UpdateAdjacent(int i, int offset, Direction e, Player& plr);
	const bool Collision(const int x0, const int y0, const int x1, const int y1, Vec2<int> to_check);

private:
	Graphics& gfx;
	Vec2<int> loc;
	const int boardborder = 50;
	const int size;
	std::vector<Cell> cells;
	const Color boardColor = Colors::LightGray;
	const Color borderColor = Colors::Gray;
	const Color clickedColor = Colors::White;
	int cellsfilled = 0;
	int lastclickedCell = -1;
	Direction lastclickedDirection;
};

