#pragma once

class PongGame
{ 
public:
	PongGame(Graphics& gfx, Keyboard& keyboard, StringSwitch<DataPass>& data)
		: gfx(gfx), kbd(keyboard), data(data) {}
	virtual ~PongGame() = 0 {}
	virtual int Update() = 0; 
	virtual void Draw() = 0;

protected:
	Graphics& gfx;
	Keyboard& kbd;
	StringSwitch<DataPass>& data;
};