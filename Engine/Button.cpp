#include "Menu.h"
#include "Game.h"

/****************  BaseButton  *******************/
inline Menu::Button::Button(
	Menu& menu, Graphics* gfx, Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor,
	std::string s, Color background, Color textcolor)
	:
	WorldObject(gfx, position, size, backgroundcolor, foregroundcolor),
	half_bordersize(half_bordersize),
	menu(menu),
	label(gfx, &menu.text, s,
		Vec2<int>(position.x + half_bordersize * 2, position.y + half_bordersize * 2),
		Vec2<int>(size.x - half_bordersize * 4, size.y - half_bordersize * 4),
		background, textcolor)
{
	if (size == Vec2<int>{0, 0}) throw std::exception("Button can't have 0 size.");
	if (label.size.x < 0) throw std::exception("Labelsize of Button can't be less than 0. bordersize might be to big.");
	if (label.size.y < 0) throw std::exception("Labelsize of Button can't be less than 0. bordersize might be to big.");
}

inline void Menu::Button::Draw()
{
	if (highlighted)
	{
		Color b = backgroundcolor; b.Shade(0.5f);
		Color f = foregroundcolor; f.Shade(0.5f);
		if (clicked) label.backgroundcolor.Shade(0.75f);
		gfx->DrawRectangleDim(position.x, position.y, size.x, size.y, b);
		gfx->DrawRectangleDim(position.x + half_bordersize, position.y + half_bordersize,
			size.x - half_bordersize * 2, size.y - half_bordersize * 2, f);
		label.Draw();
		if (clicked) label.backgroundcolor.Tint(0.75f);
	}
	else
	{
		gfx->DrawRectangleDim(position.x, position.y, size.x, size.y, backgroundcolor);
		gfx->DrawRectangleDim(position.x + half_bordersize, position.y + half_bordersize,
			size.x - half_bordersize * 2, size.y - half_bordersize * 2, foregroundcolor);
		label.Draw();
	}
}

/****************  GameButton  *******************/
Menu::GameButton::GameButton(Menu & menu, Graphics * gfx, 
	Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor, std::pair<Gamestate, int> gs,
	std::string s, Color background, Color textcolor)
	:
	Button(menu, gfx, position, size, half_bordersize, backgroundcolor, foregroundcolor, s, background, textcolor),
	gs(gs)
{
}

inline void Menu::GameButton::Update()
{
	if (clicked)
	{
		menu.gs = gs;
	}
}

/****************  MenuButton  *******************/
Menu::MenuButton::MenuButton(Menu & menu, Graphics * gfx, 
	Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor, Menustate ms, 
	std::string s, Color background, Color textcolor)
	:
	Button(menu, gfx, position, size, half_bordersize, backgroundcolor, foregroundcolor, s, background, textcolor),
	ms(ms)
{
}

inline void Menu::MenuButton::Update()
{
	if (clicked)
	{
		switch (ms)
		{
		case MsMain:
			menu.game->ClearData();
		case MsKaese:
		case MsKaeseOptionen:
		case MsSnake:
		case MsSnakeOptionen:
			menu.ms = ms;
			return;
		case MsKaeseInit:
			menu.game->data[6].i = 10;
			menu.game->data[7].i = 10;
			menu.game->data[8].i = 0;
			menu.game->data[9].i = 0;
			menu.game->data[10].d = 0.25;
			menu.ms = MsKaese;
			break;
		case MsSnakeInit:
			menu.ms = MsSnake;
			break;
		case MsSmall:
			menu.game->data[6].i = 4;
			menu.game->data[7].i = 4;
			break;
		case MsMedium:
			menu.game->data[6].i = 8;
			menu.game->data[7].i = 8;
			break;
		case MsDefault:
			menu.game->data[6].i = 10;
			menu.game->data[7].i = 10;
			break;
		case MsBig:
			menu.game->data[6].i = 12;
			menu.game->data[7].i = 12;
			break;
		case MsSquare:
			menu.game->data[8].i = 40;
			menu.game->data[9].i = 40;
			break;
		case MsFree:
			menu.game->data[8].i = 0;
			menu.game->data[9].i = 0;
			break;
		case MsThickBorder:
			menu.game->data[10].d = 0.35;
			break;
		case MsSlimBorder:
			menu.game->data[10].d = 0.25;
			break;
		}
	}
}
/*
BoardInit
00:	int		:	Color
01: int		:	Color
02: int		:	Color
03: int		:	Color
04: int		:	Color
05: int		:	Color
06: short	:	boardcellcounts.x
07: short	:	boardcellcounts.y
08: short	:	boardcellsize.x
09: short	:	boardcellsize.y
10: double	:	boardborderthickness
*/