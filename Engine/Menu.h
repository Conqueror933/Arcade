#pragma once

//#include <string>
//#include <map>
//#include "Graphics.h"
//#include "Label.h"
#include "Button.h"
#include "Bitmap.h"
#include "WorldObject.h"
#include <memory>

enum Gamestate //power to change the game
{
	GsError = -1,
	GsMenu,
	GsKaese,
	GsSnake,
	GsQuit
};

class Game;
class Menu
{
private:
	enum Menustate //power to change the Menuwindow
	{
		MsMain,

		MsSnakeInit, MsSnake, MsSnakeOptionen, 

		MsKaeseInit, MsKaese, MsKaeseOptionen
	};
	//enum Option //power to change the void*data for game options
	//{
	//	Small, Medium, Default, Big, 
	//	Square, Free, 
	//	ThickBorder, SlimBorder,
	//	Doublespeed, Normalspeed, 
	//	up, left, right, down, 
	//	Color1, Color2, Color3, Color4, Color5, Color6,
	//	Undefined1, Undefined2, Undefined3, Undefined4
	//};

public:
	Menu(Game* game);
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;
	//Menu(const Menu&&) = delete;
	//Menu& operator=(const Menu&&) = delete;
	~Menu();

	std::pair<Gamestate, int> Update(int mouse_x, int mouse_y, bool buttondown);
	void Draw();

private:
	void CreateMainMenu();

	void CreateSnakeMenu();
	void CreateSnakeOptionsMenu();

	void CreateKaeseMenu();
	void CreateKaeseOptionsMenu();

private:
	Game* game;
	Text text;
	std::vector<std::unique_ptr<WorldObject>> objects;
	std::pair<Gamestate, int> gs = std::make_pair(GsMenu, -1);
	Menustate ms;
	Menustate prevms;
	static constexpr int letterspacing = 3;
	static constexpr int border = 6;


//namespace MB //MenuButton
//{
	//template<class T>
public:
	class ButtonOwner
	{
	public:
		ButtonOwner(Menu* m) : Owner(m){}
		virtual void operator()() = 0;
	protected:
		int GetMenustate()
		{
			return Owner->ms;
		}
		void SetMenustate(Menustate m)
		{
			Owner->ms = m;
		}
		std::pair<Gamestate, int> GetGamestate()
		{
			return Owner->gs;
		}
		void SetGamestate(std::pair<Gamestate, int> g)
		{
			Owner->gs = g;
		}
		void* GetDataPointer()
		{
			return Owner->game->data;
		}
	protected:
		Menu* Owner;
	};
};

struct Back : public Menu::ButtonOwner//<T>
{
	Back(Menu* m) : ButtonOwner(m) {}
	void operator()()
	{
		{
			short* ptr = static_cast<short*>(GetDataPointer());
			ptr[12] = 10;
			ptr[13] = 10;
			ptr[14] = 0;
			ptr[15] = 0;
		}
		{
			double* ptr = static_cast<double*>(GetDataPointer());
			ptr[4] = 0.25;
		}
		DBOUT("Back functor.");
		/*GetMenustate(Owner);*/
		SetGamestate(std::make_pair(GsKaese, 0));
		//Owner.gs = std::make_pair(GsKaese, 0);
	}
};
struct Option1
{
	void operator()()
	{
		;
	}
};
//namespace MB //MenuButton
//{
//	//template<class T>
//	class ButtonOwner
//	{
//	public:
//		virtual void operator()() = 0;
//	protected:
//		static int GetMenustate(Menu* m)
//		{
//			return m->ms;
//		}
//		//protected:
//		//	T * Owner;
//	};
//	template<class T>
//	struct Back : public ButtonOwner<T>
//	{
//		void operator()()
//		{
//			DBOUT("Back functor.");
//			GetMenustate(Owner);
//			ms = MsKaese;
//		}
//	};
//	struct Option1
//	{
//		void operator()()
//		{
//			;
//		}
//	};
//}