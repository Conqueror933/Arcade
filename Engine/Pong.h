#pragma once
#include "Interface.h"
#include "PongGame.h"
#include "PongTwoPlayer.h"
#include "PongAI.h"

class Pong : public Interface
{
public:
	Pong(Graphics& gfx, Keyboard& keyboard, StringSwitch<DataPass>& data)
	{
		switch (data.GetValue("Gamemode").c)
		{
		case '2': pong = new PongTwoPlayer(); break;
		case 'E': pong = new PongAIEasy(); break;
		case 'M': pong = new PongAIMedium(); break;
		case 'H': pong = new PongAIHard(); break;
		}
	}
	~Pong() { delete pong; }
	virtual int Update() override { return pong->Update(); /*return 1 to end program*/ }
	virtual void Draw() override { pong->Draw(); }

private:
	PongGame* pong;
};