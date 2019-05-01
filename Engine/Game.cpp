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
	sInterface.push(std::make_unique<IQuit>(this));
	sInterface.push(std::make_unique<Menu>(this));
	ClearData();
}

Game::~Game()
{
	if (curInterface != nullptr)
	{
		delete curInterface;
		curInterface = nullptr;
	}
	if (data != nullptr)
	{
		delete data;
		data = nullptr;
	}
}

void Game::ClearData()
{
	char* ptr = static_cast<char*>(data);
	for (auto i = 0u; i < databuffermemblocksize; i++)
	{
		ptr[i] = '\0';
	}
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
	/*****************************************/
	int returnvalue = sInterface.top->Update();
	if (returnvalue == 1)
		sInterface.pop();
	/***********    same shit    *************/
	if(sInterface.top->Update())
		sInterface.pop();
	/*****************************************/


	switch (gamestate.first)
	{
	case GsMenu:
		//<init>
		if (prevgamestate != GsMenu)
			if (curInterface != nullptr)
			{
				delete curInterface;
				curInterface = new Menu(this);
				wnd.mouse.Flush();
			}
			else {
				curInterface = new Menu(this); //first call
				wnd.mouse.Flush();
			}
		//</init>
		//<code>
		while (!wnd.mouse.IsEmpty())
		{
			const auto e = wnd.mouse.Read();
			if (e.GetType() == Mouse::Event::Type::LPress)
				gamestate = static_cast<Menu*>(curInterface)->Update(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), true);
			else
				gamestate = static_cast<Menu*>(curInterface)->Update(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), false);
		}
		//</code>
		prevgamestate = GsMenu;
		break;
	case GsKaese:
		//<init>
		if (prevgamestate != GsKaese)
			if (curInterface != nullptr)
			{
				delete curInterface;
				curInterface = new Kaesekaestchen(gfx, wnd.mouse, data, gamestate.second);
				wnd.mouse.Flush();
			}
		//</init>
		//<code>
		wnd.mouse;
		if (static_cast<Kaesekaestchen*>(curInterface)->Update()) //if running return 0 else return 1
			gamestate = std::make_pair(GsMenu, -1);
		//</code>
		prevgamestate = GsKaese;
		break;
	case GsSnake:
		//<init>
		if (prevgamestate != GsSnake)
			if (curInterface != nullptr)
			{
				delete curInterface;
				curInterface = new SnakeGame(gfx, wnd.kbd, data);
				wnd.kbd.Flush();
				wnd.mouse.Flush();
			}
		//</init>
		//<code>
		if (static_cast<SnakeGame*>(curInterface)->Update()) //if running return 0 else return 1
			gamestate = std::make_pair(GsMenu, -1);
		//</code>
		prevgamestate = GsSnake;
		break;
	case GsQuit:
		wnd.Kill();
	default:
		gamestate = std::make_pair(GsError, -1);
	}
}

void Game::ComposeFrame()
{
	switch (prevgamestate)
	{
	case GsMenu:
		static_cast<Menu*>(curInterface)->Draw();
		break;
	case GsKaese:
		static_cast<Kaesekaestchen*>(curInterface)->Draw();
		break;
	case GsSnake:
		static_cast<SnakeGame*>(curInterface)->Draw();
		break;
	default:
		throw std::exception("Bad Gamestate.");
	}
}
