#pragma once
#include "PongGame.h"

class PongAI : public PongGame 
{ 
public: 
	virtual int Update() override { return 0; }
	virtual void Draw() override {} 
};

class PongAIEasy : public PongAI 
{};

class PongAIMedium : public PongAI 
{};

class PongAIHard : public PongAI 
{};