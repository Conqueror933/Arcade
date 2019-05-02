#include "Menu.h"
#include "Game.h"

MenuHandler::MenuHandler(Graphics & gfx, Mouse & mouse) : gfx(gfx), mouse(mouse), text(gfx, "Letters2.bmp")
{
	spSubMenus.push(std::make_unique<IQuit>());
	spSubMenus.push(std::make_unique<MainMenu>(gfx, mouse, text));
}

//void Menu::CreateMainMenu()
//{
//	//Welcome Label
//	objects.emplace_back(std::make_unique<Label>(
//		&game->gfx, &text, "Willkommen zur Arcade", Vec2<int>{ 200, 50 }, letterspacing, border, Vec2<int>{ 400, 100 }, Color(0u, 0u, 185u), Colors::White));
//	//objects.emplace_back(std::make_unique<MenuButton>(
//	//	*this, &game->gfx, Vec2<int>{ 325, 200 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsKaeseInit,
//	//	"Kaesekaestchen", Colors::White, Colors::Black));
//	//objects.emplace_back(std::make_unique<MenuButton>(
//	//	*this, &game->gfx, Vec2<int>{ 325, 260 }, Vec2<int>{ 150, 50 }, 2, Colors::Gray, Colors::LightGray, MsSnakeInit,
//	//	"Snake", Colors::White, Colors::Black));
//
//	//End
//	objects.emplace_back(std::make_unique<Button<Back>>( &text,
//		/**this, */&game->gfx, *this, Vec2<int>{ 350, 500 }, Vec2<int>{ 100, 50 }, 2, Color(145u, 0u, 0u), Color(200u, 0u, 0u), /*std::make_pair(GsQuit, 0),*/
//		"Beenden", letterspacing, border, Color(255u, 0u, 0u), Colors::White));
//}
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

int MenuHandler::Update() //int mouse_x, int mouse_y, bool buttondown
{
	switch (spSubMenus.top()->Update())
	{
	case 0:
		break;
	case 1:
		break;
	default:
		break;
	}
	return 0; //just to compile
}

void MenuHandler::Draw()
{
	//Set Background
	gfx.DrawRectangle(0, 0, gfx.ScreenWidth, gfx.ScreenHeight, Color(0u, 0u, 205u));
	for (auto i = 0u; i < _TopMenu->vpLabels.size(); i++)
	{
		_TopMenu->vpLabels[i]->Draw();
	}
	for (auto i = 0u; i < _TopMenu->vpButtons.size(); i++)
	{
		_TopMenu->vpButtons[i]->Draw();
	}
}

/****************  Menu  *******************/

MenuHandler::Menu::Menu(Graphics& gfx, Mouse& mouse, Text& text) : mouse(mouse), gfx(gfx), text(text) {}

MenuHandler::MainMenu::MainMenu(Graphics & gfx, Mouse & mouse, Text & text) : Menu(gfx, mouse, text) 
{
	//Welcome Label
	vpLabels.emplace_back(std::make_unique<Label>(
		gfx, text, "Willkommen zur Arcade", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, letterspacing, border, Color(0u, 0u, 185u), Colors::White));

	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 325, 200 }, Vec2<int>{ 150, 50 }, "Kaesekaestchen", (int)Option2, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 325, 260 }, Vec2<int>{ 150, 50 }, "Snake", (int)Option3, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//End
	vpButtons.emplace_back(std::make_unique<Button>( 
		text, gfx, Vec2<int>{ 350, 500 }, Vec2<int>{ 100, 50 }, "Beenden", (int)Quit, letterspacing, border, half_bordersize, Colors::Red, Colors::White));
}

int MenuHandler::MainMenu::Update()
{
	for (auto i = 0u; i < vpButtons.size(); i++) //for(auto& i : objects)
	{
		vpButtons[i]->DoHitDetection(mouse.GetPosX(), mouse.GetPosY(), mouse.LeftIsPressed()); //brute force
		switch (vpButtons[i]->Update())
		{
		case 0:
			break; //don't return 0 directly, or it will cancel on the first Button
		case 1:
			return 1;
		case 2:
			return 2;
		case 3:
			return 3;
		default:
			throw std::exception("Bad Button return value.");
		}
	}
	return 0;
}


MenuHandler::SnakeMenu::SnakeMenu(Graphics & gfx, Mouse & mouse, Text & text) : Menu(gfx, mouse, text) {
}
int MenuHandler::SnakeMenu::Update()
{
	return 0; //just to compile
}
MenuHandler::SnakeOptionsMenu::SnakeOptionsMenu(Graphics & gfx, Mouse & mouse, Text & text) : Menu(gfx, mouse, text) {
}
int MenuHandler::SnakeOptionsMenu::Update()
{
	return 0; //just to compile
}


MenuHandler::KaeseMenu::KaeseMenu(Graphics & gfx, Mouse & mouse, Text & text) : Menu(gfx, mouse, text) {
}
int MenuHandler::KaeseMenu::Update()
{
	return 0; //just to compile
}
MenuHandler::KaeseOptionsMenu::KaeseOptionsMenu(Graphics & gfx, Mouse & mouse, Text & text) : Menu(gfx, mouse, text) {
}
int MenuHandler::KaeseOptionsMenu::Update()
{
	return 0; //just to compile
}
