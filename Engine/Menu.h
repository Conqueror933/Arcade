#pragma once

#include <string>
#include <map>
#include "Graphics.h"
#include "Bitmap.h"
#include "WorldObject.h"
#include <memory>
#include "MainWindow.h"

enum Gamestate
{
	GsError = -1,
	GsMenu,
	GstwoPlayer,
	GsAILevel1,
	GsAILevel2,
	GsAILevel3,
	GsOptionen,
	GsVictory
};

class Menu
{
private:
	struct Label : public WorldObject
	{
		Label() = default;
		//helper thing to display text on screen
		Label(Graphics* gfx, Text* text, std::string s, Vec2<int> position,
			Vec2<int> size = { 0,0 }, Color background = Colors::Magenta, Color textcolor = Colors::White);
			//add a "Style" Object for rounded corners and all that fancy stuff
		Label(const Label& other);
		Label& operator=(const Label& other) { return *this = Label(other); }
		virtual void Update() {}
		virtual void Draw();
		Text* text;
		std::string s;
	};
	class Button : public WorldObject
	{
	public:
		Button(Menu& menu, Graphics* gfx, Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor, Gamestate gs,
			std::string s, Color background = Colors::Magenta, Color textcolor = Colors::White);

	public:
		void Update() override;
		void Draw() override;
		void SetHighlight(bool b) { highlighted = b; }
		void SetClicked(bool b) { clicked = b; }

	private:
		Menu & menu;
		Label label;
		int half_bordersize;
		Gamestate gs = GsError;
		bool highlighted = false;
		bool clicked = false;
	};
public:
	Menu(Graphics& gfx);
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;
	//Menu(const Menu&&) = delete;
	//Menu& operator=(const Menu&&) = delete;
	~Menu();

	Gamestate Update(int mouse_x, int mouse_y, bool buttondown);
	void Draw();

private:
	Text text;
	std::vector<std::unique_ptr<WorldObject>> objects;

	Gamestate gs = GsMenu;
	static constexpr int letterspacing = 3;
	static constexpr int border = 6;
};