#pragma once

//#include <string>
//#include <map>
//#include "Graphics.h"
//#include "Label.h"
//#include <memory>
#include "Button.h"
#include "Bitmap.h"
#include "Interface.h"
#include "Mouse.h"
#include "Graphics.h"

class MenuHandler : public Interface
{
public:
	MenuHandler(Graphics& gfx, Mouse& mouse);
	int Update();
	void Draw();

private:
	Graphics& gfx;
	Mouse& mouse;
	Text text;
	std::stack<std::unique_ptr<Interface>> spSubMenus;

private:
	class IQuit : public Interface
	{
	public:
		int Update() { return 1; }
	};
	class Menu : public Interface
	{
	public:
		Menu(Graphics& gfx, Mouse& mouse, Text& text);
		Menu(const Menu&) = delete;
		Menu& operator=(const Menu&) = delete;
		//Menu(const Menu&&) = delete;
		//Menu& operator=(const Menu&&) = delete;
		virtual ~Menu(){}

		virtual int Update() = 0;
		//virtual void Draw() = 0;

	protected:
	public:
		Graphics& gfx;
		Mouse& mouse;
		Text& text;
		std::vector<std::unique_ptr<Label>> vpLabels;
		std::vector<std::unique_ptr<Button>> vpButtons;

		static constexpr int letterspacing = 3;
		static constexpr int border = 6;
		static constexpr int half_bordersize = 2;
	};
	enum Options
	{
		_StartHard = -5,
		_StartMedium = -4,
		_StartEasy = -3,
		_StartTP = -2,
		_StartSnake = -1,
		_Nothing = 0,
		_Quit = 1,
		_MainMenu,
		_Kaese,
		_KaeseMenu,
		_Snake,
		_SnakeMenu
	};

	class MainMenu : public Menu
	{
	public:
		MainMenu(Graphics& gfx, Mouse& mouse, Text& text);
		int Update();
	};

	class KaeseMenu : public Menu
	{
	public:
		KaeseMenu(Graphics& gfx, Mouse& mouse, Text& text);
		int Update();
	};

	class KaeseOptionsMenu : public Menu
	{
	public:
		KaeseOptionsMenu(Graphics& gfx, Mouse& mouse, Text& text);
		int Update();
	};

	class SnakeMenu: public Menu
	{
	public:
		SnakeMenu(Graphics& gfx, Mouse& mouse, Text& text);
		int Update();
	};

	class SnakeOptionsMenu : public Menu
	{
	public:
		SnakeOptionsMenu(Graphics& gfx, Mouse& mouse, Text& text);
		int Update();
	};
};
//It aint pretty, but typedef won't work with the cast
#define _TopMenu (dynamic_cast<Menu*>(spSubMenus.top().get()))