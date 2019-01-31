#include "Menu.h"



Menu::Menu(Graphics& gfx)
	: 
	gfx(gfx),
	text(gfx, "Letters2.bmp")
{
	labels.emplace_back(Label(text, "Hello World", Vec2<int>{ 100, 100 }));
	labels.emplace_back(Label(text, "Continue", Vec2<int>{ 100, 200 }));
	labels.emplace_back(Label(text, "End", Vec2<int>{ 100, 300 }));
	labels.emplace_back(Label(text, "Play", Vec2<int>{ 100, 400 }));
}

Menu::~Menu()
{
}

void Menu::Update()
{
	
}

void Menu::Draw()
{
	for (auto i = 0; i < 4; i++)
	{
		labels[i].Draw();
	}
	//text.Draw("Hello World!", { 100,100 }, letterspacing, Colors::Yellow);
}

Menu::Label::Label(Text& text, std::string s, Vec2<int> position, Vec2<int> size, Color background, Color textcolor)
	:
	WorldObject(position, size, background, textcolor),
	text(text), 
	s(s)
{
}

void Menu::Label::Draw()
{
	//check if label background is desired
	if(backgroundcolor != Colors::Magenta)
		text.DrawRectangleDim(position.x, position.y, size.x, size.y, backgroundcolor);

	//get the width & height of the text
	const char* str = s.c_str();
	int width = 0;
	for (auto i = 0;str[i] != 0; i++)
	{
		width += text.GetLetterWidth(str[i]);
		width += letterspacing;
	}
	width -= letterspacing; //remove spacing past the last
	int height = text.GetLetterHeight();

	//if default settings are enabled, make default background
	if (size == Vec2<int>{0, 0})
	{
		size.x = width + border;
		size.y = height + border;
	}

	//if text fits in background draw text
	if (width < size.x && height < size.y)
	{
		auto x = size.x - width;
		auto y = size.y - height;
		Vec2<int> vec = { position.x + x / 2, position.y + y / 2 };
		text.Draw(s, vec, letterspacing, foregroundcolor);
	}
}
