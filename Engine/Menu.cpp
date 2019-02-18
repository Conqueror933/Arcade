#include "Menu.h"

/****************  Menu  *******************/

Menu::Menu(Graphics& gfx)
	: 
	gfx(gfx),
	text(gfx, "Letters2.bmp")
{
	CreateMainMenu();
}

Menu::Menu(Graphics & gfx, BoardInit brdinit)
	:
	gfx(gfx),
	text(gfx, "Letters2.bmp"),
	brdinit(brdinit)
{
	CreateMainMenu();
}

Menu::~Menu()
{
}

void Menu::CreateMainMenu()
{
	//Welcome Label
	objects.emplace_back(std::make_unique<Label>(
		&gfx, &text, "Willkommen zur Arcade", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, Color(0u, 0u, 185u), Colors::White));
	objects.emplace_back(std::make_unique<MenuButton>(
		*this, &gfx, Vec2<int>{ 325, 200 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsKaese,
		"Kaesekaestchen", Colors::White, Colors::Black));
	objects.emplace_back(std::make_unique<MenuButton>(
		*this, &gfx, Vec2<int>{ 325, 260 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsSnake,
		"Snake", Colors::White, Colors::Black));
}

void Menu::CreateSnakeMenu()
{
	//Back
	objects.emplace_back(std::make_unique<MenuButton>(
		*this, &gfx, Vec2<int>{ 25, Graphics::ScreenHeight - 65 }, Vec2<int>{ 75, 40 }, 2, Colors::Gray, Colors::LightGray, MsMain,
		"Back", Colors::White, Colors::Black));
}

void Menu::CreateSnakeOptionsMenu()
{
	//Back
	objects.emplace_back(std::make_unique<MenuButton>(
		*this, &gfx, Vec2<int>{ 325, 460 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsKaese,
		"Back", Colors::White, Colors::Black));
}

void Menu::CreateKaeseMenu()
{
	//Welcome Label
	objects.emplace_back(std::make_unique<Label>(
		&gfx, &text, "Willkommen zum Kaesekaestchen", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, Color(0u, 0u, 185u), Colors::White));
	//2 Player
	objects.emplace_back(std::make_unique<GameButton>(
		*this, &gfx, Vec2<int>{ 325, 200 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, GstwoPlayer,
		"Zwei Spieler", Colors::White, Colors::Black));
	//AI Level 1
	objects.emplace_back(std::make_unique<GameButton>(
		*this, &gfx, Vec2<int>{ 325, 260 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, GsAILevel1,
		"Einfach", Colors::White, Colors::Black));
	//AI Level 2
	objects.emplace_back(std::make_unique<GameButton>(
		*this, &gfx, Vec2<int>{ 325, 320 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, GsAILevel2,
		"Mittel", Colors::White, Colors::Black));
	//AI Level 3
	objects.emplace_back(std::make_unique<GameButton>(
		*this, &gfx, Vec2<int>{ 325, 380 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, GsAILevel3,
		"Schwer", Colors::White, Colors::Black));
	//Optionen
	objects.emplace_back(std::make_unique<MenuButton>(
		*this, &gfx, Vec2<int>{ 325, 460 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsKaeseOptionen,
		"Optionen", Colors::White, Colors::Black));
	//Back
	objects.emplace_back(std::make_unique<MenuButton>(
		*this, &gfx, Vec2<int>{ 25, Graphics::ScreenHeight - 65 }, Vec2<int>{ 75, 40 }, 2, Colors::Gray, Colors::LightGray, MsMain,
		"Back", Colors::White, Colors::Black));
}

void Menu::CreateKaeseOptionsMenu()
{
	//Optionen
	objects.emplace_back(std::make_unique<Label>(
		&gfx, &text, "Optionen", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, Color(0u, 0u, 185u), Colors::White));
	//Small size is 4x4  -  would be nice if this was a slider
	objects.emplace_back(std::make_unique<MenuButton>(
		*this, &gfx, Vec2<int>{ 200, 200 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsSmall,
		"Small", Colors::White, Colors::Black));
	//Medium size is 8x8
	objects.emplace_back(std::make_unique<MenuButton>(
		*this, &gfx, Vec2<int>{ 200, 260 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsMedium,
		"Medium", Colors::White, Colors::Black));
	//Default size is 10x10
	objects.emplace_back(std::make_unique<MenuButton>(
		*this, &gfx, Vec2<int>{ 200, 320 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsDefault,
		"Default", Colors::White, Colors::Black));
	//Big size is 12x12
	objects.emplace_back(std::make_unique<MenuButton>(
		*this, &gfx, Vec2<int>{ 200, 380 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsBig,
		"Big", Colors::White, Colors::Black));
	//Square ensures Square Cells (and Board)  -  would be nice if this was a checkbox
	objects.emplace_back(std::make_unique<MenuButton>(
		*this, &gfx, Vec2<int>{ 450, 200 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsSquare,
		"Square", Colors::White, Colors::Black));
	//makes Board fill the entire screen
	objects.emplace_back(std::make_unique<MenuButton>(
		*this, &gfx, Vec2<int>{ 450, 260 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsFree,
		"Full Screen", Colors::White, Colors::Black));
	//Extra thick borders
	objects.emplace_back(std::make_unique<MenuButton>(
		*this, &gfx, Vec2<int>{ 450, 320 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsThickBorder,
		"Thick borders", Colors::White, Colors::Black));
	//Reset Thick borders
	objects.emplace_back(std::make_unique<MenuButton>(
		*this, &gfx, Vec2<int>{ 450, 380 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsSlimBorder,
		"Slim borders", Colors::White, Colors::Black));
	//Back
	objects.emplace_back(std::make_unique<MenuButton>(
		*this, &gfx, Vec2<int>{ 325, 460 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsKaese,
		"Back", Colors::White, Colors::Black));
}

Gamestate Menu::Update(int mouse_x, int mouse_y, bool buttondown)
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
				prevms = ms;
			}
			else
				temp->SetHighlight(false);
		}
		objects[i]->Update();
	}
	if (ms == prevms)	//turned the ms != prevms around for ease of reading
		return gs;
	switch (ms)
	{
	case MsKaese:
		objects.clear();
		CreateKaeseMenu();
		break;
	case MsKaeseOptionen:
		objects.clear();
		CreateKaeseOptionsMenu();
		break;
	case MsSnake:
		objects.clear();
		CreateSnakeMenu();
		break;
	case MsSnakeOptionen:
		objects.clear();
		CreateSnakeOptionsMenu();
		break;
	case MsMain:
		objects.clear();
		CreateMainMenu();
		break;
	}
	return gs;
}

void Menu::Draw()
{
	//Set Background
	gfx.DrawRectangle(0, 0, gfx.ScreenWidth, gfx.ScreenHeight, Color(0u, 0u, 205u));
	for (auto i = 0u; i < objects.size(); i++)
	{
		objects[i]->Draw();
	}
}

/****************  Label  *******************/

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
