#pragma once

//#include "Bitmap.h"
//#include "WorldObject.h"
#include "Label.h"

template<typename B>
class Button : public WorldObject
{
public:
	Button(/*Menu& menu, */Text* text, Graphics* gfx,
		//Button
		Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor,
		//Label
		std::string s, const int letterspacing, const int border, Color background = Colors::Magenta, Color textcolor = Colors::White)
		:
		WorldObject(gfx, position, size, backgroundcolor, foregroundcolor),
		half_bordersize(half_bordersize),
		/*menu(menu),*/
		label(gfx, /*&menu.*/text, s,
			Vec2<int>(position.x + half_bordersize * 2, position.y + half_bordersize * 2),
			letterspacing,
			border,
			Vec2<int>(size.x - half_bordersize * 4, size.y - half_bordersize * 4),
			background, textcolor)
	{
#ifdef _DEBUG
		if (size == Vec2<int>{0, 0}) throw std::exception("Button can't have 0 size.");
		if (label.size.x < 0) throw std::exception("Labelsize of Button can't be less than 0. bordersize might be to big.");
		if (label.size.y < 0) throw std::exception("Labelsize of Button can't be less than 0. bordersize might be to big.");
#endif
	}
	~Button() = default;

public:
	void Update() { if(clicked) behaviour(); }
	//virtual void Update() = 0;
	void Draw()
	{
		if (highlighted)
		{
			Color b = backgroundcolor; b.Shade(0.5f);
			Color f = foregroundcolor; f.Shade(0.5f);
			if (clicked) label.backgroundcolor.Shade(0.75f);
			gfx->DrawRectangleDim(position.x, position.y, size.x, size.y, b);
			gfx->DrawRectangleDim(position.x + half_bordersize, position.y + half_bordersize,
				size.x - half_bordersize * 2, size.y - half_bordersize * 2, f);
			label.Draw();
			if (clicked) label.backgroundcolor.Tint(0.75f);
		}
		else
		{
			gfx->DrawRectangleDim(position.x, position.y, size.x, size.y, backgroundcolor);
			gfx->DrawRectangleDim(position.x + half_bordersize, position.y + half_bordersize,
				size.x - half_bordersize * 2, size.y - half_bordersize * 2, foregroundcolor);
			label.Draw();
		}
	}
	void SetHighlight(bool b) { highlighted = b; }
	void SetClicked(bool b) { clicked = b; }

protected:
	/*Menu & menu;*/
	Label label;
	B behaviour;
	const int half_bordersize;
	bool highlighted = false;
	bool clicked = false;
};
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