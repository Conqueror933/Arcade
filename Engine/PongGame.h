#pragma once

class PongGame
{ 
public:
	virtual ~PongGame() = 0 {}
	virtual int Update() = 0; 
	virtual void Draw() = 0; 
};