#pragma once
#include "PongGame.h"

class PongAI : public PongGame 
{ 
public:
	PongAI(Graphics& gfx, Keyboard& keyboard, StringSwitch<DataPass>& data) : PongGame(gfx, keyboard, data) {}
	virtual int Update() override { return 0; }
	virtual void Draw() override {} 
};

class PongAIEasy : public PongAI 
{
public:
	PongAIEasy(Graphics& gfx, Keyboard& keyboard, StringSwitch<DataPass>& data) : PongAI(gfx, keyboard, data) {}
};

class PongAIMedium : public PongAI 
{
public:
	PongAIMedium(Graphics& gfx, Keyboard& keyboard, StringSwitch<DataPass>& data) : PongAI(gfx, keyboard, data) {}
};

class PongAIHard : public PongAI 
{
public:
	PongAIHard(Graphics& gfx, Keyboard& keyboard, StringSwitch<DataPass>& data) : PongAI(gfx, keyboard, data) {}
};