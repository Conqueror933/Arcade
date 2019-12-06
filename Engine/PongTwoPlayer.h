#pragma once
#include "PongGame.h"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class PongTwoPlayer : public PongGame 
{ 
public:
	PongTwoPlayer(Graphics& gfx, Keyboard& keyboard, StringSwitch<DataPass>& data) : PongGame(gfx, keyboard, data) {}
	int Update() override { 
		
		p1();
		p2();

	return 0; 
	}

	void Draw() override { 

		gfx.DrawRectangleDim(25, y1, 5, 100, Colors::White);
		gfx.DrawRectangleDim(Graphics::ScreenWidth-25, y2, 5, 100, Colors::White);

	}

	void p1() {

		if (kbd.KeyIsPressed('W')) {
			if (y1 >= 1) {
				y1 = y1 - 2;
			}
		}

		if (kbd.KeyIsPressed('S')) {
			if (y1 < Graphics::ScreenHeight - 100) {
				y1 = y1 + 2;
			}
		}

	}

	void p2() {

		if (kbd.KeyIsPressed('O')) {
			if (y2 >= 1) {
				y2 = y2 - 2;
			}
		}

		if (kbd.KeyIsPressed('L')) {
			if (y2 < Graphics::ScreenHeight - 100) {
				y2 = y2 + 2;
			}
		}
	}

	private:
		int y1 = 200;
		int y2 = 200;
		

};