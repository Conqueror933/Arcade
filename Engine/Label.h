#pragma once

#include "Bitmap.h"

class Label
{
public:
	//helper thing to display text on screen
	Label(Graphics& gfx, Text& text, std::string s, Vec2<int> position, Vec2<int> size = { 0,0 }, 
		const int letterspacing = 3, const int border = 6, Color backgroundcolor = Colors::Magenta, Color textcolor = Colors::White);
	//add a "Style" Object for rounded corners and all that fancy stuff
	Label(const Label& other);
	Label& operator=(const Label& other) { return *this = Label(other); }
	//int Update() { /*if (!permanent) timercountdown;*/ }
	void Draw();

	void SetText(std::string text) { s = text; }
	void SetBackground(Color c) { background = c; }
	void SetTextColor(Color c) { textcolor = c; }
private:
	Graphics& gfx;
	Text& text;
	Vec2<int> position;
	Vec2<int> size;
	Color background;
	Color textcolor;

	std::string s;
	const int letterspacing;
	const int border;
	/*bool permanent;*/
};