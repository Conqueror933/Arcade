#pragma once

//#include "Bitmap.h"
#include "Label.h"

//struct ButtonConstructorParams
//{
//	//Button
//	Vec2<int> position;
//	Vec2<int> size;
//	int half_bordersize;
//	Color buttoncolor;
//	//Label
//	std::string text;
//	int letterspacing;
//	int border;
//	Color textcolor = Colors::White;
//};

class Button
{
public:
	Button(
		Text& text, Graphics& gfx, Vec2<int> position, Vec2<int> size, std::string s, int returnvalue, 
		const int letterspacing, const int border, int half_bordersize, Color backgroundcolor, Color textcolor = Colors::White)
		:
		//Button
		gfx(gfx), position(position), size(size), returnvalue(returnvalue),
		backgroundcolor(backgroundcolor), half_bordersize(half_bordersize),
		//Label
		label(gfx, text, s,
			Vec2<int>(position.x + half_bordersize * 2, position.y + half_bordersize * 2),
			Vec2<int>(size.x - half_bordersize * 4, size.y - half_bordersize * 4),
			letterspacing, border, Colors::Magenta, textcolor)
	{
#ifdef _DEBUG
		if (size == Vec2<int>{0, 0}) throw std::exception("Button can't have 0 size.");
		if (size.x < 0) throw std::exception("Labelsize of Button can't be less than 0. bordersize might be to big.");
		if (size.y < 0) throw std::exception("Labelsize of Button can't be less than 0. bordersize might be to big.");
#endif
	}
	~Button() = default;

public:
	void DoHitDetection(int x, int y, bool clicked)
	{
		if (x > position.x && x < position.x + size.x &&
			y > position.y && y < position.y + size.y)
		{
			SetHighlight(true);
			if (clicked)
				SetClicked(true);
			else
				SetClicked(false);
		}
		else {
			SetHighlight(false);
			SetClicked(false);
		}
	}
	int Update() { return (clicked ? returnvalue : 0); }
	void Draw()
	{
		Color Edge1 = backgroundcolor; Edge1.Shade(0.25f);
		Color Edge2 = backgroundcolor; Edge2.Shade(0.5f);
		Color Background = backgroundcolor;

		if (highlighted)
		{
			//Edge1.Shade(0.5f);
			Edge2.Shade(0.25f);
			Background.Shade(0.75f);
		}

		gfx.DrawRectangleDim(position.x, position.y, size.x, size.y, Edge1);
		gfx.DrawRectangleDim(position.x + half_bordersize, position.y + half_bordersize,
			size.x - half_bordersize * 2, size.y - half_bordersize * 2, Edge2);
		gfx.DrawRectangleDim(position.x + half_bordersize * 2, position.y + half_bordersize * 2,
			size.x - half_bordersize * 4, size.y - half_bordersize * 4, Background);
		label.Draw();
	}
	void SetHighlight(bool b) { highlighted = b; }
	void SetClicked(bool b) { clicked = b; }

private:
	Graphics& gfx;
	Vec2<int> position;
	Vec2<int> size;
	Color backgroundcolor;

	Label label;
	const int returnvalue;
	const int half_bordersize;
	bool highlighted = false;
	bool clicked = false;
};

//template<typename B>
//class Button : public WorldObject
//{
//public:
//	Button(/*Menu& menu, */Text* text, Graphics* gfx, B behaviour,
//		//Button
//		Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor,
//		//Label
//		std::string s, const int letterspacing, const int border, Color background = Colors::Magenta, Color textcolor = Colors::White)
//		:
//		WorldObject(gfx, position, size, backgroundcolor, foregroundcolor),
//		half_bordersize(half_bordersize),
//		behaviour(behaviour),
//		/*menu(menu),*/
//		label(gfx, /*&menu.*/text, s,
//			Vec2<int>(position.x + half_bordersize * 2, position.y + half_bordersize * 2),
//			letterspacing,
//			border,
//			Vec2<int>(size.x - half_bordersize * 4, size.y - half_bordersize * 4),
//			background, textcolor)
//	{
//#ifdef _DEBUG
//		if (size == Vec2<int>{0, 0}) throw std::exception("Button can't have 0 size.");
//		if (label.size.x < 0) throw std::exception("Labelsize of Button can't be less than 0. bordersize might be to big.");
//		if (label.size.y < 0) throw std::exception("Labelsize of Button can't be less than 0. bordersize might be to big.");
//#endif
//	}
//	~Button() = default;
//
//public:
//	int Update() { if(clicked) behaviour(); }
//	//virtual void Update() = 0;
//	void Draw()
//	{
//		if (highlighted)
//		{
//			Color b = backgroundcolor; b.Shade(0.5f);
//			Color f = foregroundcolor; f.Shade(0.5f);
//			if (clicked) label.backgroundcolor.Shade(0.75f);
//			gfx->DrawRectangleDim(position.x, position.y, size.x, size.y, b);
//			gfx->DrawRectangleDim(position.x + half_bordersize, position.y + half_bordersize,
//				size.x - half_bordersize * 2, size.y - half_bordersize * 2, f);
//			label.Draw();
//			if (clicked) label.backgroundcolor.Tint(0.75f);
//		}
//		else
//		{
//			gfx->DrawRectangleDim(position.x, position.y, size.x, size.y, backgroundcolor);
//			gfx->DrawRectangleDim(position.x + half_bordersize, position.y + half_bordersize,
//				size.x - half_bordersize * 2, size.y - half_bordersize * 2, foregroundcolor);
//			label.Draw();
//		}
//	}
//	void SetHighlight(bool b) { highlighted = b; }
//	void SetClicked(bool b) { clicked = b; }
//
//protected:
//	/*Menu & menu;*/
//	Label label;
//	B behaviour;
//	const int half_bordersize;
//	bool highlighted = false;
//	bool clicked = false;
//};
//class GameButton : public Button
//{
//public:
//	GameButton(Menu& menu, Graphics* gfx,
//		//Button
//		Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor, std::pair<Gamestate, int> gs,
//		//Label
//		std::string s, Color background = Colors::Magenta, Color textcolor = Colors::White);
//	void Update() override;
//
//private:
//	std::pair<Gamestate, int> gs;
//};
//class MenuButton : public Button
//{
//public:
//	MenuButton(Menu& menu, Graphics* gfx,
//		//Button
//		Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor, Menustate ms,
//		//Label
//		std::string s, Color background = Colors::Magenta, Color textcolor = Colors::White);
//	virtual ~MenuButton() = default;
//	virtual void Update() override;
//
//protected:
//	Menustate ms;
//};
//class OptionButton : public MenuButton
//{
//public:
//	OptionButton(Menu& menu, Graphics* gfx,
//		//Button
//		Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor, Menustate ms, Option opt,
//		//Label
//		std::string s, Color background = Colors::Magenta, Color textcolor = Colors::White);
//	void Update() override;
//
//private:
//	Option opt;
//};