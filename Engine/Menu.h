#pragma once

#include <string>
#include <map>
#include "Graphics.h"
#include "Bitmap.h"
#include "WorldObject.h"

class Menu
{
private:
	class Button : public WorldObject
	{
		//hit detection
			//possible animation
		//invokes smth when pressed
	};
	struct Label : public WorldObject
	{
		//helper thing to display text on screen
		Label(Text& text, std::string s, Vec2<int> position, 
			Vec2<int> size = { 0,0 }, Color background = Colors::Magenta, Color textcolor = Colors::White);
		//add a "Style" Object for rounded corners and all that fancy stuff
		void Draw();
		Text& text;
		std::string s;
	};
public:
	Menu(Graphics& gfx);
	~Menu();

	void Update();
	void Draw();

private:
	Graphics& gfx;
	Text text;
	std::vector<Label> labels;
	std::vector<Button> buttons;

	static constexpr int letterspacing = 3;
	static constexpr int border = 6;
};

