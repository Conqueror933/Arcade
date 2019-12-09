/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include <assert.h>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	spInterface.push(std::make_unique<IQuit>());
	spInterface.push(std::make_unique<MenuHandler>(gfx, wnd.mouse));
}

Game::~Game()
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

#define _GetData dynamic_cast<MenuHandler*>(spInterface.top().get())->GetData()
void Game::UpdateModel()
{
	DBOUT(60.0f/ft.Mark() << '\n'); //fps
	if (spInterface.empty()) {
		wnd.Kill(); return;
	}
	int r = spInterface.top()->Update(); //sanity check for games not to create other games on top //debatable
	assert(!(spInterface.size() > 2u && (r > 1 || r < 0)));
		//return;
	switch (r)
	{
	case 0:
		break;
	case 1:
		spInterface.pop(); break;
	case -1:
		spInterface.push(std::make_unique<SnakeGame>	 (gfx, wnd.kbd, _GetData));		 break;
	case -2:
		spInterface.push(std::make_unique<Kaesekaestchen>(gfx, wnd.mouse, _GetData, 0)); break;
	case -3:
		spInterface.push(std::make_unique<Kaesekaestchen>(gfx, wnd.mouse, _GetData, 1)); break;
	case -4:
		spInterface.push(std::make_unique<Kaesekaestchen>(gfx, wnd.mouse, _GetData, 2)); break;
	case -5:
		spInterface.push(std::make_unique<Kaesekaestchen>(gfx, wnd.mouse, _GetData, 3)); break;
	case -6:
		spInterface.push(std::make_unique<Pong>(gfx, wnd.kbd, _GetData)); break;
	case 1000000:
		spInterface.push(std::make_unique<DevMode>(gfx, wnd.kbd, wnd.mouse)); break;
	default:
		throw std::exception("Bad Update return");
	}
}

void Game::ComposeFrame()
{
	if (spInterface.size() > 1)
		spInterface.top()->Draw();
}
