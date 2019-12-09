#pragma once
#include "Interface.h"
#include "Bitmap.h"
#include "Label.h"
#include "Frametimer.h"
#include "Vec2.h"

class DevMode : public Interface
{
public:
	DevMode(Graphics& gfx, Keyboard& kbd, Mouse& mouse) 
		: gfx(gfx), kbd(kbd), mouse(mouse), text(gfx, "Letters2.bmp"), 
		label(gfx, text, "Test", Vec2<int>{10, 10}, Vec2<int>{780,30}, 3, 6, Colors::Cyan, Colors::Black) {}
	int Update() override 
	{ 
		deltatime += ft.Mark();
		if (kbd.KeyIsPressed('A') && deltatime > steptime) {
			point.x -= speed; deltatime = 0.f;
		}
		if (kbd.KeyIsPressed('D') && deltatime > steptime) {
			point.x += speed; deltatime = 0.f;
		}

		if (Vec2Math::isColliding(point, circ))
			label.SetText("POINT ! CIRC Collision detected!");
		else if(Vec2Math::isColliding(point, line))
			label.SetText("POINT ! LINE Collision detected!");
		else if (Vec2Math::isColliding(point, tri))
			label.SetText("POINT ! TRI Collision detected!");
		//if (Vec2Math::isColliding(line, circ))
		//	label.SetText("LINE ! CIRC Collision detected!");
		//else if (Vec2Math::isColliding(tri, circ))
		//	label.SetText("TRI ! CIRC Collision detected!");
		//else if (Vec2Math::isColliding(tri, line))
		//	label.SetText("TRI ! LINE Collision detected!");
		else
			label.SetText("Peace and Harmony");
		return 0;
	}
	void Draw() override 
	{ 
		//Draw Corners of Triangle
		gfx.PutPixel(tri.p1.x, tri.p1.y, Colors::Cyan);
		gfx.PutPixel(tri.p2.x, tri.p2.y, Colors::Cyan);
		gfx.PutPixel(tri.p3.x, tri.p3.y, Colors::Cyan);

		//Draw Middle of Circle
		gfx.PutPixel(circ.pos.x, circ.pos.y, Colors::Red);

		//Draw End points of Line
		gfx.PutPixel(line.p1.x, line.p1.y, Colors::Blue);
		gfx.PutPixel(line.p2.x, line.p2.y, Colors::Blue);

		//Draw Point
		gfx.PutPixel(point.x, point.y, Colors::Green);

		//Draw label
		label.Draw();
	}

private:
	///Setup
	Graphics& gfx;
	Keyboard& kbd;
	Mouse& mouse;
	Text text;
	Label label;
	FrameTimer ft;
	float deltatime = 0.0f;
	const float steptime = 0.1f;
	const float speed = 1.f;

	///Custom
	Vec2Math::Triangle<float> tri = { { 100.f,100.f },{ 23.f,170.f },{ 300.f,143.f }};
	Vec2Math::Circle<float> circ = { {80.f,110.f}, 5.f };
	Vec2Math::Line<float> line = { { 200.f, 50.f },{ 200.f, 200.f } };//{ {30.f, 240.f},{ 230.f, 50.f } };
	Vec2<float> point = { 110.f, 110.f };
};