#include "Menu.h"
#include "Game.h"

/****************  Menu  *******************/

Menu::Menu(Game* game)
	: 
	game(game),
	text(game->gfx, "Letters2.bmp")
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
		&game->gfx, &text, "Willkommen zur Arcade", Vec2<int>{ 200, 50 }, letterspacing, border, Vec2<int>{ 400, 100 }, Color(0u, 0u, 185u), Colors::White));
	//objects.emplace_back(std::make_unique<MenuButton>(
	//	*this, &game->gfx, Vec2<int>{ 325, 200 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsKaeseInit,
	//	"Kaesekaestchen", Colors::White, Colors::Black));
	//objects.emplace_back(std::make_unique<MenuButton>(
	//	*this, &game->gfx, Vec2<int>{ 325, 260 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsSnakeInit,
	//	"Snake", Colors::White, Colors::Black));

	//End
	objects.emplace_back(std::make_unique<Button<Back>>( &text,
		/**this, */&game->gfx, *this, Vec2<int>{ 350, 500 }, Vec2<int>{ 100, 50 }, 2, Color(145u, 0u, 0u), Color(200u, 0u, 0u), /*std::make_pair(GsQuit, 0),*/
		"Beenden", letterspacing, border, Color(255u, 0u, 0u), Colors::White));
}
//
//void Menu::CreateSnakeMenu()
//{
//	//Welcome Label
//	objects.emplace_back(std::make_unique<Label>(
//		&game->gfx, &text, "Welcome to Snake", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, Color(0u, 0u, 185u), Colors::White));
//	//Start
//	objects.emplace_back(std::make_unique<GameButton>(
//		*this, &game->gfx, Vec2<int>{ 325, 200 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, std::make_pair(GsSnake, 0),
//		"Start", Colors::White, Colors::Black));
//	//Optionen
//	objects.emplace_back(std::make_unique<MenuButton>(
//		*this, &game->gfx, Vec2<int>{ 325, 460 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsSnakeOptionen,
//		"Optionen", Colors::White, Colors::Black));
//	//Back
//	objects.emplace_back(std::make_unique<MenuButton>(
//		*this, &game->gfx, Vec2<int>{ 25, Graphics::ScreenHeight - 65 }, Vec2<int>{ 75, 40 }, 2, Colors::Gray, Colors::LightGray, MsMain,
//		"Back", Colors::White, Colors::Black));
//}
//
//void Menu::CreateSnakeOptionsMenu()
//{
//	//Optionen
//	objects.emplace_back(std::make_unique<Label>(
//		&game->gfx, &text, "Optionen", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, Color(0u, 0u, 185u), Colors::White));
//
//	objects.emplace_back(std::make_unique<OptionButton>(
//		*this, &game->gfx, Vec2<int>{ 200, 200 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsSnake, Small,
//		"Small", Colors::White, Colors::Black));
//	objects.emplace_back(std::make_unique<OptionButton>(
//		*this, &game->gfx, Vec2<int>{ 200, 260 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsSnake, Medium,
//		"Medium", Colors::White, Colors::Black));
//	objects.emplace_back(std::make_unique<OptionButton>(
//		*this, &game->gfx, Vec2<int>{ 200, 320 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsSnake, Default,
//		"Default", Colors::White, Colors::Black));
//	objects.emplace_back(std::make_unique<OptionButton>(
//		*this, &game->gfx, Vec2<int>{ 200, 380 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsSnake, Big,
//		"Big", Colors::White, Colors::Black));
//	objects.emplace_back(std::make_unique<OptionButton>(
//		*this, &game->gfx, Vec2<int>{ 450, 200 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsSnake, Doublespeed,
//		"Doublespeed", Colors::White, Colors::Black));
//	objects.emplace_back(std::make_unique<OptionButton>(
//		*this, &game->gfx, Vec2<int>{ 450, 260 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsSnake, Normalspeed,
//		"Normalspeed", Colors::White, Colors::Black));
//	objects.emplace_back(std::make_unique<OptionButton>(
//		*this, &game->gfx, Vec2<int>{ 450, 320 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsSnake, ThickBorder,
//		"Thick borders", Colors::White, Colors::Black));
//	objects.emplace_back(std::make_unique<OptionButton>(
//		*this, &game->gfx, Vec2<int>{ 450, 380 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsSnake, SlimBorder,
//		"Slim borders", Colors::White, Colors::Black));
//	//Back
//	objects.emplace_back(std::make_unique<MenuButton>(
//		*this, &game->gfx, Vec2<int>{ 325, 460 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsSnake,
//		"Back", Colors::White, Colors::Black));
//}
//
//void Menu::CreateKaeseMenu()
//{
//	//Welcome Label
//	objects.emplace_back(std::make_unique<Label>(
//		&game->gfx, &text, "Willkommen zum Kaesekaestchen", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, Color(0u, 0u, 185u), Colors::White));
//	//2 Player
//	objects.emplace_back(std::make_unique<GameButton>(
//		*this, &game->gfx, Vec2<int>{ 325, 200 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, std::make_pair(GsKaese, 0),
//		"Zwei Spieler", Colors::White, Colors::Black));
//	//AI Level 1
//	objects.emplace_back(std::make_unique<GameButton>(
//		*this, &game->gfx, Vec2<int>{ 325, 260 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, std::make_pair(GsKaese, 1),
//		"Einfach", Colors::White, Colors::Black));
//	//AI Level 2
//	objects.emplace_back(std::make_unique<GameButton>(
//		*this, &game->gfx, Vec2<int>{ 325, 320 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, std::make_pair(GsKaese, 2),
//		"Mittel", Colors::White, Colors::Black));
//	//AI Level 3
//	/*objects.emplace_back(std::make_unique<GameButton>(
//		*this, &game->gfx, Vec2<int>{ 325, 380 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, std::make_pair(GsKaese, 3),
//		"Schwer", Colors::White, Colors::Black));*/
//	//Optionen
//	objects.emplace_back(std::make_unique<MenuButton>(
//		*this, &game->gfx, Vec2<int>{ 325, 460 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsKaeseOptionen,
//		"Optionen", Colors::White, Colors::Black));
//	//Back
//	objects.emplace_back(std::make_unique<MenuButton>(
//		*this, &game->gfx, Vec2<int>{ 25, Graphics::ScreenHeight - 65 }, Vec2<int>{ 75, 40 }, 2, Colors::Gray, Colors::LightGray, MsMain,
//		"Back", Colors::White, Colors::Black));
//}
//
//void Menu::CreateKaeseOptionsMenu()
//{
//	//Optionen
//	objects.emplace_back(std::make_unique<Label>(
//		&game->gfx, &text, "Optionen", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, Color(0u, 0u, 185u), Colors::White));
//	//Small size is 4x4  -  would be nice if this was a slider
//	objects.emplace_back(std::make_unique<OptionButton>(
//		*this, &game->gfx, Vec2<int>{ 200, 200 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsKaese, Small,
//		"Small", Colors::White, Colors::Black));
//	//Medium size is 8x8
//	objects.emplace_back(std::make_unique<OptionButton>(
//		*this, &game->gfx, Vec2<int>{ 200, 260 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsKaese, Medium,
//		"Medium", Colors::White, Colors::Black));
//	//Default size is 10x10
//	objects.emplace_back(std::make_unique<OptionButton>(
//		*this, &game->gfx, Vec2<int>{ 200, 320 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsKaese, Default,
//		"Default", Colors::White, Colors::Black));
//	//Big size is 12x12
//	objects.emplace_back(std::make_unique<OptionButton>(
//		*this, &game->gfx, Vec2<int>{ 200, 380 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsKaese, Big,
//		"Big", Colors::White, Colors::Black));
//	//Square ensures Square Cells (and Board)  -  would be nice if this was a checkbox
//	objects.emplace_back(std::make_unique<OptionButton>(
//		*this, &game->gfx, Vec2<int>{ 450, 200 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsKaese, Square,
//		"Square", Colors::White, Colors::Black));
//	//makes Board fill the entire screen
//	objects.emplace_back(std::make_unique<OptionButton>(
//		*this, &game->gfx, Vec2<int>{ 450, 260 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsKaese, Free,
//		"Full Screen", Colors::White, Colors::Black));
//	//Extra thick borders
//	objects.emplace_back(std::make_unique<OptionButton>(
//		*this, &game->gfx, Vec2<int>{ 450, 320 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsKaese, ThickBorder,
//		"Thick borders", Colors::White, Colors::Black));
//	//Reset Thick borders
//	objects.emplace_back(std::make_unique<OptionButton>(
//		*this, &game->gfx, Vec2<int>{ 450, 380 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsKaese, SlimBorder,
//		"Slim borders", Colors::White, Colors::Black));
//	//Back
//	objects.emplace_back(std::make_unique<MenuButton>(
//		*this, &game->gfx, Vec2<int>{ 325, 460 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsKaese,
//		"Back", Colors::White, Colors::Black));
//}

std::pair<Gamestate, int> Menu::Update(int mouse_x, int mouse_y, bool buttondown)
{
	for (auto i = 0u; i < objects.size(); i++)
	{
		//if (auto temp = dynamic_cast<Button*>(objects[i].get()))
		//{
		auto temp = objects[i].get();
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
		//}
		objects[i]->Update();
	}
	if (ms == prevms)	//turned the ms != prevms around for ease of reading
		return gs;
	switch (ms)
	{
	//case MsKaese:
	//	objects.clear();
	//	CreateKaeseMenu();
	//	break;
	//case MsKaeseOptionen:
	//	objects.clear();
	//	CreateKaeseOptionsMenu();
	//	break;
	//case MsSnake:
	//	objects.clear();
	//	CreateSnakeMenu();
	//	break;
	//case MsSnakeOptionen:
	//	objects.clear();
	//	CreateSnakeOptionsMenu();
	//	break;
	//case MsMain:
	//	objects.clear();
	//	CreateMainMenu();
	//	break;
	}
	return gs;
}

void Menu::Draw()
{
	//Set Background
	game->gfx.DrawRectangle(0, 0, game->gfx.ScreenWidth, game->gfx.ScreenHeight, Color(0u, 0u, 205u));
	for (auto i = 0u; i < objects.size(); i++)
	{
		objects[i]->Draw();
	}
}
