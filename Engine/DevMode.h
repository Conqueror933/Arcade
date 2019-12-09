#pragma once
#include "Interface.h"
#include "Vec2.h"
#include "Bitmap.h"
#include "Label.h"

class DevMode : public Interface
{
public:
	DevMode(Graphics& gfx, Keyboard& kbd, Mouse& mouse) 
		: gfx(gfx), kbd(kbd), mouse(mouse), text(gfx, "Letters2.bmp"), 
		label(gfx, text, "Test", Vec2<int>{10, 10}, Vec2<int>{780,30}, 3, 6, Colors::Cyan, Colors::Black) {}
	int Update() override { return 0; }
	void Draw() override { label.Draw(); }

private:
	Graphics& gfx;
	Keyboard& kbd;
	Mouse& mouse;
	Text text;
	Label label;
};