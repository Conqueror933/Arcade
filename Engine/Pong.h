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
		case '2': pong = new PongTwoPlayer(gfx, keyboard, data); break;
		case 'E': pong = new PongAIEasy(gfx, keyboard, data); break;
		case 'M': pong = new PongAIMedium(gfx, keyboard, data); break;
		case 'H': pong = new PongAIHard(gfx, keyboard, data); break;
		}
	}
	~Pong() { delete pong; }
	virtual int Update() override { return pong->Update(); /*return 1 to end program*/ }
	virtual void Draw() override { pong->Draw(); }

private:
	PongGame* pong;
};