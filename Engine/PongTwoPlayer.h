#pragma once
#include "PongGame.h"
#include "Frametimer.h"
#include "Vec2.h"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class PongTwoPlayer : public PongGame 
{ 
public:
	PongTwoPlayer(Graphics& gfx, Keyboard& keyboard, StringSwitch<DataPass>& data) : PongGame(gfx, keyboard, data) {}
	int Update() override 
	{ 
		player1.Update();
		player2.Update();
		ball.Update();
		return 0;
	}

	void Draw() override 
	{ 
		player1.Draw();
		player2.Draw();
		ball.Draw();
	}

private:
	class Player
	{
	public:
		Player(PongTwoPlayer& PTP, int x, int y,const char up, const char down)
			: 
			PTP(PTP), pos(x,y), up(up), down(down)
		{
		}
		void Update()
		{
			deltatime += ft.Mark();

			if (PTP.kbd.KeyIsPressed(up) && deltatime > steptime) 
			{
				if (pos.y > 0) 
				{
					pos.y -= speed; deltatime = 0.f;
				}
			}

			if (PTP.kbd.KeyIsPressed(down) && deltatime > steptime)
			{
				if (pos.y < Graphics::ScreenHeight - 100)
				{
					pos.y += speed; deltatime = 0.f;
				}
			}
		}
		void Draw()
		{
			PTP.gfx.DrawRectangleDim(pos.x-3, pos.y-50, 6, 100, Colors::White);
		}
		const int GetX() const { return pos.x; }
		const int GetY() const { return pos.y; }

	private:
		PongTwoPlayer& PTP;
		Vec2<float> pos;
		const char up;
		const char down;
		FrameTimer ft;
		float deltatime = 0.0f;
		const float steptime = 0.01f;
		const float speed = 5.f;
	};
	Player player1{ *this, 25, Graphics::ScreenHeight / 2, 'W', 'S' };
	Player player2{ *this, Graphics::ScreenWidth - 25, Graphics::ScreenHeight / 2, 'O', 'L' };

	class Ball
	{	
	public:
		Ball(PongTwoPlayer& PTP)
			:
			PTP(PTP)
		{
		}
		void Update()
		{
			deltatime += ft.Mark();			
			if (rl && deltatime > steptime) // Bool für Richtungsänderung
			{
				x -= speed; deltatime = 0.f;
			}
			if (!rl && deltatime > steptime)
			{
				x += speed; deltatime = 0.f;
			}

			if (x - 10 <= PTP.player1.GetX() + 3) 
			{
				if (y + 10 > PTP.player1.GetY() - 50 && y - 10 < PTP.player1.GetY() + 50) 
				{
					rl = false;
				}
			}
			if (x + 10 >= PTP.player2.GetX() - 3)
			{
				if (y + 10 > PTP.player2.GetY() - 50 && y - 10 < PTP.player2.GetY() + 50)
				{
					rl = true;
				}
			}
		}
		void Draw()
		{
			PTP.gfx.DrawRectangleDim(x-10, y-10, 20, 20, Colors::Red);
		}
		const int GetX() const { return x; }
		const int GetY() const { return y; }
	private:
		PongTwoPlayer & PTP;
		int y = Graphics::ScreenHeight / 2;
		int	x = Graphics::ScreenWidth / 2;
		bool rl = true;
		FrameTimer ft;
		float deltatime = 0.0f;
		const float steptime = 0.01f;
		const float speed = 3.f;
	};	
	Ball ball{*this};

private:
};