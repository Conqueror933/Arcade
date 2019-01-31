#pragma once

#include <string>
#include <map>
#include "Graphics.h"
#include "Bitmap.h"

class Menu
{
private:
	class Button
	{
		//hit detection
			//possible animation
		//invokes smth when pressed
	};
	class Label
	{
		//helper thing to display text on screen
		friend class Button;
		std::string s;

		static std::map<char, std::pair<int,int>> letters; 
		//char = letter, int = x position of letter in bitmapint = width of letter in bitmap

	};
public:
	Menu(Graphics& gfx);
	~Menu();

	void Update() { 
		text.Draw("LOOK MA AUTOMATISCHES SCHREIBEN", { 100,100 }, Colors::Yellow);
		//text.Draw('H', { 100,100 }, Colors::Cyan);
		//text.Draw('E', { 110,100 }, Colors::Cyan);
		//text.Draw('L', { 120,100 }, Colors::Cyan);
		//text.Draw('L', { 130,100 }, Colors::Cyan);
		//text.Draw('O', { 140,100 }, Colors::Cyan);
		//text.Draw('W', { 155,100 }, Colors::Cyan);
		//text.Draw('O', { 170,100 }, Colors::Cyan);
		//text.Draw('R', { 180,100 }, Colors::Cyan);
		//text.Draw('L', { 190,100 }, Colors::Cyan);
		//text.Draw('D', { 200,100 }, Colors::Cyan);
	}
	void Draw(){}

private:
	Graphics& gfx;
	Text text;
};

