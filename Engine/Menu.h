#pragma once

#include <string>
#include <map>
#include "Graphics.h"
#include "Bitmap.h"
#include "WorldObject.h"
#include <memory>

enum Gamestate
{
	GsError = -1,
	GsMenu,
	GsKaese,
	GsSnake,

	GstwoPlayer,
	GsAILevel1,
	GsAILevel2,
	GsAILevel3,
	GsPlayer1Victory,
	GsPlayer2Victory,
	GsUndecided
};

class Game;
class Menu
{
private:
	enum Menustate
	{
		MsMain,

		MsSnakeInit, MsSnake, MsSnakeOptionen,

		MsKaeseInit, MsKaese, MsKaeseOptionen, MsSmall, MsMedium, MsDefault, MsBig, MsSquare, MsFree, MsThickBorder, MsSlimBorder
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
			Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor, Gamestate gs,
			//Label
			std::string s, Color background = Colors::Magenta, Color textcolor = Colors::White);
		void Update() override;

	private:
		Gamestate gs = GsError;
	};
	class MenuButton : public Button
	{
	public:
		MenuButton(Menu& menu, Graphics* gfx,
			//Button
			Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor, Menustate ms,
			//Label
			std::string s, Color background = Colors::Magenta, Color textcolor = Colors::White);
		void Update() override;

	private:
		Menustate ms;
	};
public:
	Menu(Game* game);
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;
	//Menu(const Menu&&) = delete;
	//Menu& operator=(const Menu&&) = delete;
	~Menu();

	Gamestate Update(int mouse_x, int mouse_y, bool buttondown);
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
	Gamestate gs = GsMenu;
	Menustate ms;
	Menustate prevms;
	static constexpr int letterspacing = 3;
	static constexpr int border = 6;
};