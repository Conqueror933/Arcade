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
	spInterface.push(std::make_unique<IQuit>(this));
	spInterface.push(std::make_unique<Menu>(this));
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

void Game::UpdateModel()
{
	switch (spInterface.top->Update()) //could use a sanity check if its not the menu returning, since a Game shouldn't create another game
	{
	case 0:
		break;
	case 1:
		spInterface.pop(); break;
	case 2:
	{ void* data; int flag;
		spInterface.push(std::make_unique<Kaesekaestchen>(gfx, wnd.mouse, data, flag)); /*Constructor is still fucked, but this way it will compile, won't work, but compile*/ }
	case 3:
	{ void* data; int flag;
		spInterface.push(std::make_unique<SnakeGame>(gfx, wnd.mouse, data, flag)); /*Constructor is still fucked, but this way it will compile, won't work, but compile*/ }
	default:
		throw std::exception("Bad Update return");
	}
}

void Game::ComposeFrame()
{
	spInterface.top->Draw();
}
