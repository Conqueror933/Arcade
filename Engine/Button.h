#pragma once

//#include "Bitmap.h"
//#include "WorldObject.h"
#include "Label.h"

class Button : public WorldObject
{
public:
	Button(Menu& menu, Graphics* gfx,
		//Button
		Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor,
		//Label
		std::string s, Color background = Colors::Magenta, Color textcolor = Colors::White);
	virtual ~Button() = default;

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
		Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor, std::pair<Gamestate, int> gs,
		//Label
		std::string s, Color background = Colors::Magenta, Color textcolor = Colors::White);
	void Update() override;

private:
	std::pair<Gamestate, int> gs;
};
class MenuButton : public Button
{
public:
	MenuButton(Menu& menu, Graphics* gfx,
		//Button
		Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor, Menustate ms,
		//Label
		std::string s, Color background = Colors::Magenta, Color textcolor = Colors::White);
	virtual ~MenuButton() = default;
	virtual void Update() override;

protected:
	Menustate ms;
};
class OptionButton : public MenuButton
{
public:
	OptionButton(Menu& menu, Graphics* gfx,
		//Button
		Vec2<int> position, Vec2<int> size, int half_bordersize, Color backgroundcolor, Color foregroundcolor, Menustate ms, Option opt,
		//Label
		std::string s, Color background = Colors::Magenta, Color textcolor = Colors::White);
	void Update() override;

private:
	Option opt;
};