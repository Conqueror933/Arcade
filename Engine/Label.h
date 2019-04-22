#pragma once

#include "Bitmap.h"
#include "WorldObject.h"

class Label : public WorldObject
{
public:
	//helper thing to display text on screen
	Label(Graphics* gfx, Text* text, std::string s, Vec2<int> position, const int letterspacing, const int border,
		Vec2<int> size = { 0,0 }, Color background = Colors::Magenta, Color textcolor = Colors::White);
	//add a "Style" Object for rounded corners and all that fancy stuff
	Label(const Label& other);
	Label& operator=(const Label& other) { return *this = Label(other); }
	void Update() override { /*if (!permanent) timercountdown;*/ }
	void Draw() override;
private:
	Text * text;
	const std::string s;
	const int letterspacing;
	const int border;
	/*bool permanent;*/
};