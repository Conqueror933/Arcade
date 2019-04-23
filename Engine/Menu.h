#pragma once

//#include <string>
//#include <map>
//#include "Graphics.h"
//#include "Label.h"
#include "Button.h"
#include "Bitmap.h"
#include "WorldObject.h"
#include <memory>

enum Gamestate //power to change the game
{
	GsError = -1,
	GsMenu,
	GsKaese,
	GsSnake,
	GsQuit
};

class Game;
class Menu
{
private:
	enum Menustate //power to change the Menuwindow
	{
		MsMain,

		MsSnakeInit, MsSnake, MsSnakeOptionen, 

		MsKaeseInit, MsKaese, MsKaeseOptionen
	};
	//enum Option //power to change the void*data for game options
	//{
	//	Small, Medium, Default, Big, 
	//	Square, Free, 
	//	ThickBorder, SlimBorder,
	//	Doublespeed, Normalspeed, 
	//	up, left, right, down, 
	//	Color1, Color2, Color3, Color4, Color5, Color6,
	//	Undefined1, Undefined2, Undefined3, Undefined4
	//};

public:
	Menu(Game* game);
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;
	//Menu(const Menu&&) = delete;
	//Menu& operator=(const Menu&&) = delete;
	~Menu();

	std::pair<Gamestate, int> Update(int mouse_x, int mouse_y, bool buttondown);
	void Draw();

private:
	void CreateMainMenu();

	void CreateSnakeMenu();
	void CreateSnakeOptionsMenu();

	void CreateKaeseMenu();
	void CreateKaeseOptionsMenu();

private:
	Game* game;
	Text text;
	std::vector<std::unique_ptr<WorldObject>> objects;
	std::pair<Gamestate, int> gs = std::make_pair(GsMenu, -1);
	Menustate ms;
	Menustate prevms;
	static constexpr int letterspacing = 3;
	static constexpr int border = 6;
};

struct Back
{
	void operator()()
	{
		DBOUT("Back functor.");
	}
};