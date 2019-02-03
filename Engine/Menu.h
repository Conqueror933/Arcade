#pragma once

#include <string>
#include <map>
#include "Graphics.h"
#include "Bitmap.h"
#include "WorldObject.h"
#include "Effect.h"
#include <memory>
#include "MainWindow.h"

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
	//template<class E>
	class Button : public WorldObject
	{
	public:
		Button(Graphics* gfx, Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor,// E effect
			Text* text, std::string s, Color background = Colors::Magenta, Color textcolor = Colors::White)
			:
			WorldObject(gfx, position, size, backgroundcolor, foregroundcolor),
			half_bordersize(half_bordersize),
			//effect(effect),
			label(gfx, text, s, 
				Vec2<int>(position.x + half_bordersize*2, position.y + half_bordersize*2),
				Vec2<int>(size.x - half_bordersize*4, size.y - half_bordersize*4),
				background, textcolor)
		{
			if (size == Vec2<int>{0, 0}) throw std::exception("Button can't have 0 size.");
			if (label.size.x < 0) throw std::exception("Labelsize of Button can't be less than 0. bordersize might be to big.");
			if (label.size.y < 0) throw std::exception("Labelsize of Button can't be less than 0. bordersize might be to big.");
		}

	public:
		void Update() override
		{
			if (clicked)
			{
				//this is the moment for the effect to take place. ...?

				//effect();

				// 2 Player
				//AI level 1
				//AI level 2
				//AI level 3
				//Optionen
			}
		}
		void Draw() override
		{
			if (highlighted)
			{
				Color b = backgroundcolor; b.Shade(0.5f);
				Color f = foregroundcolor; f.Shade(0.5f);
				if(clicked) label.backgroundcolor.Shade(0.75f);
				gfx->DrawRectangleDim(position.x, position.y, size.x, size.y, b);
				gfx->DrawRectangleDim(position.x + half_bordersize, position.y + half_bordersize,
					size.x - half_bordersize * 2, size.y - half_bordersize * 2, f);
				label.Draw();
				if(clicked) label.backgroundcolor.Tint(0.75f);
			}
			else
			{
				gfx->DrawRectangleDim(position.x, position.y, size.x, size.y, backgroundcolor);
				gfx->DrawRectangleDim(position.x + half_bordersize, position.y + half_bordersize, 
					size.x - half_bordersize*2, size.y - half_bordersize*2, foregroundcolor);
				label.Draw();
			}
		}
		void SetHighlight(bool b) { highlighted = b; }
		void SetClicked(bool b) { clicked = b; }

	private:
		Label label;
		int half_bordersize;
		//E effect;
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

	void Update(int mouse_x, int mouse_y, bool buttondown);
	void Draw();

private:
	Graphics& gfx;
	Text text;
	std::vector<std::unique_ptr<WorldObject>> objects;

	static constexpr int letterspacing = 3;
	static constexpr int border = 6;
};