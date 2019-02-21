#include "Kaesekaestchen.h"



Kaesekaestchen::Kaesekaestchen(int flag)
{
	
}


Kaesekaestchen::~Kaesekaestchen()
{
}

int Kaesekaestchen::Update()
{
	switch (flag)
	{
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
	}
}
