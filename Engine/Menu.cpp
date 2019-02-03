#include "Menu.h"



Menu::Menu(Graphics& gfx)
	: 
	gfx(gfx),
	text(gfx, "Letters2.bmp")
{
	//Set Background
	gfx.DrawRectangle(0, 0, gfx.ScreenWidth-1, gfx.ScreenHeight-1, Color(0u, 0u, 205u));
	//Welcome Label
	objects.emplace_back(std::make_unique<Label>(
		&gfx, &text, "Willkommen zum Kaesekaestchen", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, Color(0u, 0u, 185u), Colors::White));
	//2 Player
	objects.emplace_back(std::make_unique<Button>(
		&gfx, Vec2<int>{ 325, 200 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, 
		&text, "Zwei Spieler", Colors::White, Colors::Black));
	//AI Level 1
	objects.emplace_back(std::make_unique<Button>(
		&gfx, Vec2<int>{ 325, 260 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray,
		&text, "KI Level Eins", Colors::White, Colors::Black));
	//AI Level 2
	objects.emplace_back(std::make_unique<Button>(
		&gfx, Vec2<int>{ 325, 320 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray,
		&text, "KI Level Zwei", Colors::White, Colors::Black));
	//AI Level 3
	objects.emplace_back(std::make_unique<Button>(
		&gfx, Vec2<int>{ 325, 380 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray,
		&text, "KI Level Drei", Colors::White, Colors::Black));
	//Optionen
	objects.emplace_back(std::make_unique<Button>(
		&gfx, Vec2<int>{ 325, 460 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray,
		&text, "Optionen", Colors::White, Colors::Black));
}

Menu::~Menu()
{
}

void Menu::Update(int mouse_x, int mouse_y, bool buttondown)
{
	for (auto i = 0u; i < objects.size(); i++)
	{
		if (auto temp = dynamic_cast<Button*>(objects[i].get()))
		{
			if (temp->position.x <= mouse_x && (temp->position.x + temp->size.x) >= mouse_x &&
				temp->position.y <= mouse_y && (temp->position.y + temp->size.y) >= mouse_y)
			{
				temp->SetHighlight(true);
				if (buttondown)
					temp->SetClicked(true);
				else
					temp->SetClicked(false);
			}
			else
				temp->SetHighlight(false);
		}
	}
}

void Menu::Draw()
{
	for (auto i = 0u; i < objects.size(); i++)
	{
		objects[i]->Draw();
	}
}

Menu::Label::Label(Graphics* gfx, Text* text, std::string s, Vec2<int> position, Vec2<int> size, Color background, Color textcolor)
	:
	WorldObject(gfx, position, size, background, textcolor),
	text(text), 
	s(s)
{
}

Menu::Label::Label(const Label& other) 
	: 
	WorldObject(other.gfx, other.position, other.size, other.backgroundcolor, other.foregroundcolor),
	text(other.text),
	s(other.s)
{
}

void Menu::Label::Draw()
{
	//check if label background is desired
	if(backgroundcolor != Colors::Magenta)
		gfx->DrawRectangleDim(position.x, position.y, size.x, size.y, backgroundcolor);

	//get the width & height of the text
	const char* str = s.c_str();
	int width = 0;
	for (auto i = 0;str[i] != 0; i++)
	{
		width += text->GetLetterWidth(str[i]);
		width += letterspacing;
	}
	width -= letterspacing; //remove spacing past the last
	int height = text->GetLetterHeight();

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
		text->Draw(s, vec, letterspacing, foregroundcolor);
	}
}
