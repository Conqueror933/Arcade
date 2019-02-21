/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Game.h																				  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Menu.h"
#include "Kaesekaestchen.h"
#include "Board.h"

class Game
{
	friend class Menu;
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	~Game();
	void Go();

private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	inline /* __declspec(noinline)*/ BoardInit GetBoardInit();
	void DoBoardUpdate();
	template<class T> void InitBoard();
	void ClearData();
	/********************************/
private:
	MainWindow & wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Gamestate gamestate = GsMenu;
	Gamestate prevgamestate;

	//Should be totally legimit RAII, right? no memory learking happening
	void* curInterface = nullptr;

	union Data
	{
		char ca[sizeof(double)];
		char c;
		int i;
		unsigned int ui;
		long long ll;
		float f;
		double d;
	};
	//void* data = ::operator new (64u); //basically malloc, but not quite
	static constexpr unsigned int databufferarraysize = 16u;
	std::array<Data, databufferarraysize> data{};
	/********************************/
};

template<class T>
inline void Game::InitBoard()
{
	if (curInterface != nullptr)
	{
		delete curInterface;
		BoardInit brdinit = GetBoardInit();
		if (brdinit.boardcellsize == Vec2<int>{0, 0})
			curInterface = new T(gfx, brdinit.brdclr, brdinit.boardcellcounts, brdinit.boardborderthickness);
		else
			curInterface = new T(gfx, brdinit.brdclr, brdinit.boardcellcounts, brdinit.boardcellsize, brdinit.boardborderthickness);
	}
}
