#pragma once

#include "Graphics.h"
#include <vector>
#include "Vec2.h"

struct BoardColors
{
	Color foreground = Colors::LightGray;
	Color background = Colors::Gray;

	Color clicked = Colors::White;
	Color lastclicked = Colors::Green;

	Color player1 = Colors::Blue;
	Color player2 = Colors::Red;
};

struct BoardInit
{
	BoardColors brdclr;
	Vec2<int> boardcellcounts;// = Vec2<int>(10, 10);
	Vec2<int> boardcellsize;// = Vec2<int>(0, 0);
	double boardborderthickness;// = 0.25;
};

class Board
{
protected:
	enum Playerflag { None, Player1, Player2 };
private:
	class Cell
	{
	public:
		Cell(Board& brd, Vec2<int> screenposition, unsigned int index);
		virtual ~Cell();
		//Cell(const Cell& other);
		//Cell& operator=(const Cell& other);

	public:
		int Update(int mouse_x, int mouse_y, Playerflag plr); //return number of cells assigned to a player
		void Draw() const;
		void Draw(bool b) const;

	private:
		Board& brd;

	public:
		Vec2<int> pos; //screenposition
		int index;
		bool top = false;
		bool left = false;
		Playerflag playerflag = None;
	};

public:
	//Fill Screen
	Board(Graphics& gfx, const BoardColors brdclr, const Vec2<int> cellcount, const double borderthicknessratio);
	//Borders
	Board(Graphics& gfx, const BoardColors brdclr, const Vec2<int> cellcount, const Vec2<int> cellsize, const double borderthicknessratio);
	Board(const Board& brd) = delete;
	Board& operator=(const Board& brd) = delete;
	virtual ~Board() = default;

private: //statics
	static int CalculateCellBorderWidth1(const Vec2<int> cellcount, const double borderthicknessratio);
	static int CalculateCellBorderWidth2(const Vec2<int> cellsize, const double borderthicknessratio);
	static Vec2<int> CalculateCellSize(const Vec2<int> cellcount, int borderwidth);
	static const Vec2<int> CheckCellSize(const Vec2<int> cellcount, const Vec2<int> cellsize, int cellborderwidth);
	static Vec2<int> CalculateTopLeft(const Vec2<int> cellcount, const Vec2<int> cellsize, int cellborderwidth);
	static void Init(Board& brd);

public:
	virtual int Update(int mouse_x, int mouse_y) = 0;
	void Draw() const;

protected:
	Graphics& gfx;
	const BoardColors brdclr;

	const Vec2<int> cellcount;
	const int cellborderwidth;	//in Board cause it is basically static for the Cell but not actually static
	const Vec2<int> cellsize;	//in Board cause it is basically static for the Cell but not actually static
	const Vec2<int> topleft;

	std::vector<Cell> cells;
	int cellsfilled = 0;
	std::pair<int, bool> lastclickedCell = { -1, false }; //int = index, bool: true = top, false = left
	bool set;

	int player1counter = 0;
	int player2counter = 0;
};

/*
#define SquareBoard			0x0001i16 //0000 0000 0000 0001
#define SquareCells			0x0002i16 //0000 0000 0000 0010
#define FillScreen			0x0004i16 //0000 0000 0000 0100
#define FavorSquareBoard	0x0008i16 //0000 0000 0000 1000
#define FavorSquareCells	0x0010i16 //0000 0000 0001 0000

Square Board ? Cellcount.x == Cellcount.y : Cellcount.x != Cellcount.y || Cellcount.x == Cellcount.y
Square Cells ? Cellsize.x == Cellsize.y : Cellsize.x != Cellsize.y || Cellsize.x == Cellsize.y
Fill Screen  ? Cellsize * Cellcount == Graphics::Screen : borders
FavorSquareBoard = Cellsize * Cellcount > Graphics::Screen ? Cellcount(x==y) = Graphics::Screen / Cellsize : Cellcount.x != Cellcount.y
FavorSquareCells = Cellsize * Cellcount > Graphics::Screen ? Cellsize(x==y) = Graphics::Screen / Cellcount : Cellcount.x != Cellcount.y
*/