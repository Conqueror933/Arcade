#pragma once

#include <string>
#include <map>
#include "Graphics.h"
#include "Bitmap.h"
#include "WorldObject.h"
#include <memory>

enum Gamestate //power to change the game
{
	GsError = -1,
	GsMenu,
	GsKaese,
	GsSnake,
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
	enum Option //power to change the void*data for game options
	{
		Small, Medium, Default, Big, 
		Square, Free, 
		ThickBorder, SlimBorder,
		Doublespeed, Normalspeed, 
		up, left, right, down, 
		Color1, Color2, Color3, Color4, Color5, Color6,
		Undefined1, Undefined2, Undefined3, Undefined4
	};

	class Label : public WorldObject
	{
	public:
		//helper thing to display text on screen
		Label(Graphics* gfx, Text* text, std::string s, Vec2<int> position,
			Vec2<int> size = { 0,0 }, Color background = Colors::Magenta, Color textcolor = Colors::White);
			//add a "Style" Object for rounded corners and all that fancy stuff
		Label(const Label& other);
		Label& operator=(const Label& other) { return *this = Label(other); }
		void Update() override { /*if (!permanent) timercountdown;*/ }
		void Draw() override;
	private:
		Text* text;
		const std::string s;
		/*bool permanent;*/
	};

	class Button : public WorldObject
	{
	public:
		Button(Menu& menu, Graphics* gfx, 
			//Button
			Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor,
			//Label
			std::string s, Color background = Colors::Magenta, Color textcolor = Colors::White);
		virtual ~Button() = default;

	public:
		virtual void Update() = 0;
		virtual void Draw();
		void SetHighlight(bool b) { highlighted = b; }
		void SetClicked(bool b) { clicked = b; }

	protected:
		Menu & menu;
		Label label;
		const int half_bordersize;
		bool highlighted = false;
		bool clicked = false;
	};
	class GameButton : public Button
	{
	public:
		GameButton(Menu& menu, Graphics* gfx,
			//Button
			Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor, std::pair<Gamestate, int> gs,
			//Label
			std::string s, Color background = Colors::Magenta, Color textcolor = Colors::White);
		void Update() override;

	private:
		std::pair<Gamestate, int> gs;
	};
	class MenuButton : public Button
	{
	public:
		MenuButton(Menu& menu, Graphics* gfx,
			//Button
			Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor, Menustate ms,
			//Label
			std::string s, Color background = Colors::Magenta, Color textcolor = Colors::White);
		virtual ~MenuButton() = default;
		virtual void Update() override;

	protected:
		Menustate ms;
	};
	class OptionButton : public MenuButton
	{
	public:
		OptionButton(Menu& menu, Graphics* gfx,
			//Button
			Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor, Menustate ms, Option opt,
			//Label
			std::string s, Color background = Colors::Magenta, Color textcolor = Colors::White);
		void Update() override;

	private:
		Option opt;
	};

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