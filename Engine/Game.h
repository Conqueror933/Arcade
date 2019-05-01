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
#include "Snake.h"
#include <stack>

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
	void ClearData();
	void SetData(DataPass data);
	/********************************/
private:
	MainWindow & wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	std::pair<Gamestate, int> gamestate = std::make_pair(GsMenu, -1);
	Gamestate prevgamestate = GsError; /*because DEBUG-mode auto initializes every variable, 
									   it sets this to 0 which is GsMenu which on the very first call of Update makes it so that it doesn't get initialized, since gamestate == prevgamestate (0 == 0)*/

	//Should be totally legimit RAII, right? no memory leaking happening
	void* curInterface = nullptr;

	std::stack<std::unique_ptr<Interface>> sInterface;

	static constexpr unsigned int databuffermemblocksize = 64u;
	void* data = ::operator new (databuffermemblocksize); //basically malloc, but not quite
	/********************************/

	class IQuit : public Interface
	{
	public:
		IQuit(Game* game) : pgame(game) {}
		int Update() { pgame->wnd.Kill(); }
		void Draw(){}

	private:
		Game * pgame;
	};
};
