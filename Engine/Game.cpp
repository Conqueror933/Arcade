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
#include "TwoPlayer.h"
#include "AI.h"
#include <assert.h>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	ClearData();
}

Game::~Game()
{
	if (curInterface != nullptr)
	{
		delete curInterface;
		curInterface = nullptr;
	}
	/*if (data != nullptr)
	{
		::operator delete(data);
		data = nullptr;
	}*/
}

void Game::ClearData()
{
	for (auto i = 0u; i < databufferarraysize; i++)
	{
		data[i].ll = 0;
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
	switch (gamestate)
	{
	case GsMenu:
		//<init>
		if (prevgamestate != GsMenu)
			if (curInterface != nullptr)
			{
				delete curInterface;
				curInterface = new Menu(this); 
			}
			else
				curInterface = new Menu(this); //first call
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
				curInterface = new Kaesekaestchen(3);
			}
		//</init>
		//<code>
		if (static_cast<Kaesekaestchen*>(curInterface)->Update()) //if running return 0 else return 1
			gamestate = GsMenu;
		//</code>
		prevgamestate = GsKaese;
		break;
	case GstwoPlayer:
		if (prevgamestate != GstwoPlayer)
			InitBoard<TwoPlayer>();
		DoBoardUpdate();
		prevgamestate = GstwoPlayer;
		break;
	case GsAILevel1:
		if (prevgamestate != GsAILevel1)
			InitBoard<EasyAI>();
		DoBoardUpdate();
		prevgamestate = GsAILevel1;
		break;
	case GsAILevel2:
		if (prevgamestate != GsAILevel2)
			if (curInterface != nullptr)
				InitBoard<MediumAI>();
		DoBoardUpdate();
		prevgamestate = GsAILevel2;
		break;
	case GsAILevel3:
		if (prevgamestate != GsAILevel3)
			if (curInterface != nullptr)
				InitBoard<HardAI>();
		DoBoardUpdate();
		prevgamestate = GsAILevel3;
		break;
	case GsPlayer1Victory:
		while (!wnd.mouse.IsEmpty())
		{
			const auto e = wnd.mouse.Read();
			if (e.GetType() == Mouse::Event::Type::LPress)
				gamestate = GsMenu;
		}
		prevgamestate = GsPlayer1Victory;
		break;
	case GsPlayer2Victory:
		while (!wnd.mouse.IsEmpty())
		{
			const auto e = wnd.mouse.Read();
			if (e.GetType() == Mouse::Event::Type::LPress)
				gamestate = GsMenu;
		}
		prevgamestate = GsPlayer2Victory;
		break;
	case GsUndecided:
		while (!wnd.mouse.IsEmpty())
		{
			const auto e = wnd.mouse.Read();
			if (e.GetType() == Mouse::Event::Type::LPress)
				gamestate = GsMenu;
		}
		prevgamestate = GsUndecided;
		break;
	default:
		gamestate = GsError;
	}
}

inline  /*__declspec(noinline)*/ BoardInit Game::GetBoardInit()
{
	BoardInit bi;
	bi.boardcellcounts = Vec2<int>(data[6].i, data[7].i);
	bi.boardcellsize = Vec2<int>(data[8].i, data[9].i);
	bi.boardborderthickness = data[10].d;
	return bi;
}

void Game::DoBoardUpdate()
{
	while (!wnd.mouse.IsEmpty())
	{
		const auto e = wnd.mouse.Read();
		if (e.GetType() == Mouse::Event::Type::LPress) {
			auto temp = static_cast<Board*>(curInterface)->Update(wnd.mouse.GetPosX(), wnd.mouse.GetPosY());
			if (temp == 1)
				gamestate = GsPlayer1Victory;
			else if (temp == 2)
				gamestate = GsPlayer2Victory;
			else if (temp == 3)
				gamestate = GsUndecided;
		}
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
	case GstwoPlayer:
	case GsAILevel1:
	case GsAILevel2:
	case GsAILevel3:
		static_cast<Board*>(curInterface)->Draw();
		break;
	case GsPlayer1Victory:
		gfx.DrawRectangle(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Blue);
		static_cast<Board*>(curInterface)->Draw();
		break;
	case GsPlayer2Victory:
		gfx.DrawRectangle(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Red);
		static_cast<Board*>(curInterface)->Draw();
		break;
	case GsUndecided:
		gfx.DrawRectangle(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Cyan);
		static_cast<Board*>(curInterface)->Draw();
		break;
	default:
		throw std::exception("Bad Gamestate.");
	}
}
