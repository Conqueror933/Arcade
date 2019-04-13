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
		case MsKaeseInit:
			menu.game->ClearData();
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
			menu.game->ClearData();
			{
				short* ptr = static_cast<short*>(menu.game->data);
				ptr[0] = 20;
				ptr[1] = 20;
				ptr[2] = 0;
				ptr[3] = 3;
			}
			{
				char* ptr = static_cast<char*>(menu.game->data);
				ptr[16] = 'W';
				ptr[17] = 'A';
				ptr[18] = 'D';
				ptr[19] = 'S';
			}
			{
				Color* ptr = static_cast<Color*>(menu.game->data);
				ptr[6] = Colors::Gray;
				ptr[7] = Colors::LightGray;
				ptr[8] = Colors::Red;
				ptr[9] = Colors::Green;
				ptr[10] = Colors::Cyan;
			}
			{
				static_cast<double*>(menu.game->data)[1] = 0.05;
				static_cast<float*>(menu.game->data)[5] = 0.4f;
			}
			menu.ms = MsSnake;
			break;
		default:
			menu.ms = ms;
		}
	}
}

Menu::OptionButton::OptionButton(Menu & menu, Graphics * gfx,
	Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor, Menustate ms, Option opt,
	std::string s, Color background, Color textcolor)
	:
	MenuButton(menu, gfx, position, size, half_bordersize, backgroundcolor, foregroundcolor, ms, s, background, textcolor),
	opt(opt)
{
}
void Menu::OptionButton::Update()
{
	if (clicked)
	{
		switch (ms)
		{
		case MsKaese:
			switch (opt)
			{
			case Small:
			{
				short* ptr = static_cast<short*>(menu.game->data);
				ptr[12] = 4;
				ptr[13] = 4;
			}
			break;
			case Medium:
			{
				short* ptr = static_cast<short*>(menu.game->data);
				ptr[12] = 8;
				ptr[13] = 8;
			}
			break;
			case Default:
			{
				short* ptr = static_cast<short*>(menu.game->data);
				ptr[12] = 10;
				ptr[13] = 10;
			}
			break;
			case Big:
			{
				short* ptr = static_cast<short*>(menu.game->data);
				ptr[12] = 12;
				ptr[13] = 12;
			}
			break;
			case Square:
			{
				short* ptr = static_cast<short*>(menu.game->data);
				ptr[14] = 40;
				ptr[15] = 40;
			}
			break;
			case Free:
			{
				short* ptr = static_cast<short*>(menu.game->data);
				ptr[14] = 0;
				ptr[15] = 0;
			}
			break;
			case ThickBorder:
			{
				double* ptr = static_cast<double*>(menu.game->data);
				ptr[4] = 0.35;
			}
			break;
			case SlimBorder:
			{
				double* ptr = static_cast<double*>(menu.game->data);
				ptr[4] = 0.25;
			}
			break;
			default:
				throw std::exception("OptionsButton::Update::Kaese.default reached");
			}
			break;
		case MsSnake:
			switch (opt)
			{
			case Small:
			{
				short* ptr = static_cast<short*>(menu.game->data);
				ptr[0] = 6;
				ptr[1] = 6;
			}
				break;
			case Medium:
			{
				short* ptr = static_cast<short*>(menu.game->data);
				ptr[0] = 15;
				ptr[1] = 15;
			}
				break;
			case Default:
			{
				short* ptr = static_cast<short*>(menu.game->data);
				ptr[0] = 20;
				ptr[1] = 20;
			}
				break;
			case Big:
			{
				short* ptr = static_cast<short*>(menu.game->data);
				ptr[0] = 30;
				ptr[1] = 30;
			}
				break;
			case ThickBorder:
				static_cast<double*>(menu.game->data)[1] = 0.3;
				break;
			case SlimBorder:
				static_cast<double*>(menu.game->data)[1] = 0.05;
				break;
			case Doublespeed:
				static_cast<float*>(menu.game->data)[5] = 0.2f;
				break;
			case Normalspeed:
				static_cast<float*>(menu.game->data)[5] = 0.4f;
				break;
			default:
				throw std::exception("OptionsButton::Update::Snake.default reached");
			}
			break;
		//default:
		//	throw std::exception("OptionsButton::Update::NoOptionfound");
		}
	}
}
/*
Init
00: int		:	Color
04:	int		:	Color
08:	int		:	Color
12:	int		:	Color
16:	int		:	Color
20:	int		:	Color
24:	int		:	Color
28:	int		:	Color
32:	int		:	Color
36:	int		:	Color
40:	int		:	Color
44:	int		:	Color
48:	int		:	Color
52:	int		:	Color
56:	int		:	Color
60:	int		:	Color
64: end
*/