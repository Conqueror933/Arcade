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
		{
			short* ptr = static_cast<short*>(menu.game->data);
			ptr[12] = 10;
			ptr[13] = 10;
			ptr[14] = 0;
			ptr[15] = 0;
		}
		{
			double* ptr = static_cast<double*>(menu.game->data);
			ptr[4] = 0.25;
		}
			menu.ms = MsKaese;
			break;
		case MsSnakeInit:
			menu.ms = MsSnake;
			break;
		case MsSmall:
		{
			short* ptr = static_cast<short*>(menu.game->data);
			ptr[12] = 4;
			ptr[13] = 4;
		}
			break;
		case MsMedium:
		{
			short* ptr = static_cast<short*>(menu.game->data);
			ptr[12] = 8;
			ptr[13] = 8;
		}
			break;
		case MsDefault:
		{
			short* ptr = static_cast<short*>(menu.game->data);
			ptr[12] = 10;
			ptr[13] = 10;
		}
			break;
		case MsBig:
		{
			short* ptr = static_cast<short*>(menu.game->data);
			ptr[12] = 12;
			ptr[13] = 12;
		}
			break;
		case MsSquare:
		{
			short* ptr = static_cast<short*>(menu.game->data);
			ptr[14] = 40;
			ptr[15] = 40;
		}
			break;
		case MsFree:
		{
			short* ptr = static_cast<short*>(menu.game->data);
			ptr[14] = 0;
			ptr[15] = 0;
		}
			break;
		case MsThickBorder:
		{
			double* ptr = static_cast<double*>(menu.game->data);
			ptr[4] = 0.35;
		}
			break;
		case MsSlimBorder:
		{
			double* ptr = static_cast<double*>(menu.game->data);
			ptr[4] = 0.25;
		}
			break;
		}
	}
}
/*
BoardInit
00:	int		:	Color
04: int		:	Color
08: int		:	Color
12: int		:	Color
16: int		:	Color
20: int		:	Color
24: short	:	boardcellcounts.x
26: short	:	boardcellcounts.y
28: short	:	boardcellsize.x
30: short	:	boardcellsize.y
32: double	:	boardborderthickness
40: end
*/