#pragma once

enum Gamestate
{
	GsError = -1,
	GsMenu,
	GstwoPlayer,
	GsAILevel1,
	GsAILevel2,
	GsAILevel3,
	GsPlayer1Victory,
	GsPlayer2Victory
};

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
	Vec2<int> boardcellcounts = Vec2<int>(10, 10);
	Vec2<int> boardcellsize = Vec2<int>(30, 30);
	double boardborderthickness = 0.25;
};