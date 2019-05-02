#include "Menu.h"
#include "Game.h"

MenuHandler::MenuHandler(Graphics & gfx, Mouse & mouse) : gfx(gfx), mouse(mouse), text(gfx, "Letters2.bmp")
{
	spSubMenus.push(std::make_unique<IQuit>());
	spSubMenus.push(std::make_unique<MainMenu>(gfx, mouse, text));
}

int MenuHandler::Update() // 1 is reserved for going back/ending, 0 is do nothing
{
	if (spSubMenus.empty()) return 1;
	switch (int temp = spSubMenus.top()->Update())
	{
	case _Nothing:
		break;
	case _Quit:
		spSubMenus.pop(); break;
	case _Kaese:
		spSubMenus.push(std::make_unique<KaeseMenu>(gfx, mouse, text)); break;
	case _KaeseMenu:
		spSubMenus.push(std::make_unique<KaeseOptionsMenu>(gfx, mouse, text)); break;
	case _Snake:
		spSubMenus.push(std::make_unique<SnakeMenu>(gfx, mouse, text)); break;
	case _SnakeMenu:
		spSubMenus.push(std::make_unique<SnakeOptionsMenu>(gfx, mouse, text)); break;
	default:
		return temp;
	}
	return 0;
}

void MenuHandler::Draw()
{
	if (spSubMenus.size() > 1) {
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
}

/****************  Menu  *******************/

MenuHandler::Menu::Menu(Graphics& gfx, Mouse& mouse, Text& text) : mouse(mouse), gfx(gfx), text(text) {}

MenuHandler::MainMenu::MainMenu(Graphics & gfx, Mouse & mouse, Text & text) : Menu(gfx, mouse, text) 
{
	//Welcome Label
	vpLabels.emplace_back(std::make_unique<Label>(
		gfx, text, "Willkommen zur Arcade", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, letterspacing, border, Color(0u, 0u, 185u), Colors::White));

	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 325, 200 }, Vec2<int>{ 150, 50 }, "Kaesekaestchen", 2, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 325, 260 }, Vec2<int>{ 150, 50 }, "Snake", 3, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//End
	vpButtons.emplace_back(std::make_unique<Button>( 
		text, gfx, Vec2<int>{ 350, 500 }, Vec2<int>{ 100, 50 }, "Beenden", 1, letterspacing, border, half_bordersize, Colors::Red, Colors::White));
}
int MenuHandler::MainMenu::Update()
{
	while (!mouse.IsEmpty()) //brute force
	{
		const auto e = mouse.Read();
		for (auto i = 0u; i < vpButtons.size(); i++) //for(auto& i : objects)
		{
			if (e.GetType() == Mouse::Event::Type::LPress)
				vpButtons[i]->DoHitDetection(mouse.GetPosX(), mouse.GetPosY(), true);
			else
				vpButtons[i]->DoHitDetection(mouse.GetPosX(), mouse.GetPosY(), false);
			switch (int temp = vpButtons[i]->Update())
			{
			case 0:
				break; //don't return 0 directly, or it will cancel on the first Button
			case 2:
				return _Kaese;
			case 3:
				return _Snake;
			default:
				return temp;
			}
		}
	}
	return 0;
}

/*******************************************************************************************************************************************/

MenuHandler::KaeseMenu::KaeseMenu(Graphics & gfx, Mouse & mouse, Text & text) : Menu(gfx, mouse, text)
{
	//Welcome Label
	vpLabels.emplace_back(std::make_unique<Label>(
		gfx, text, "Willkommen zum Kaesekaestchen", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, letterspacing, border, Color(0u, 0u, 185u), Colors::White));
	//2 Player
	vpButtons.emplace_back(std::make_unique<Button>(
			text, gfx, Vec2<int>{ 325, 200 }, Vec2<int>{ 150, 50 }, "Zwei Spieler", 2, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//AI Level 1
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 325, 260 }, Vec2<int>{ 150, 50 }, "Einfach", 3, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//AI Level 2
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 325, 320 }, Vec2<int>{ 150, 50 }, "Mittel", 4, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//AI Level 3
	/*vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 325, 380 }, Vec2<int>{ 150, 50 }, "Schwer", 5, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));*/
	//Optionen
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 325, 460 }, Vec2<int>{ 150, 50 }, "Optionen", 6, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Back
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 25, Graphics::ScreenHeight - 65 }, Vec2<int>{ 75, 40 }, "Back", 1, letterspacing, border, half_bordersize, Colors::Red, Colors::White));
}
int MenuHandler::KaeseMenu::Update()
{
	while (!mouse.IsEmpty()) //brute force
	{
		const auto e = mouse.Read();
		for (auto i = 0u; i < vpButtons.size(); i++) //for(auto& i : objects)
		{
			if (e.GetType() == Mouse::Event::Type::LPress)
				vpButtons[i]->DoHitDetection(mouse.GetPosX(), mouse.GetPosY(), true);
			else
				vpButtons[i]->DoHitDetection(mouse.GetPosX(), mouse.GetPosY(), false);
			switch (int temp = vpButtons[i]->Update())
			{
			case 0:
				break; //don't return 0 directly, or it will cancel on the first Button
			case 2:
				return _StartTP;
			case 3:
				return _StartEasy;
			case 4:
				return _StartMedium;
			case 5:
				return _StartHard;
			case 6:
				return _KaeseMenu;
			default:
				return temp;
			}
		}
	}
	return 0;
}

MenuHandler::KaeseOptionsMenu::KaeseOptionsMenu(Graphics & gfx, Mouse & mouse, Text & text) : Menu(gfx, mouse, text)
{
	//Optionen
	vpLabels.emplace_back(std::make_unique<Label>(
		gfx, text, "Optionen", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, letterspacing, border, Color(0u, 0u, 185u), Colors::White));
	//Small size is 4x4  -  would be nice if this was a slider
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 200, 200 }, Vec2<int>{ 150, 50 }, "Small", 2, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Medium size is 8x8
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 200, 260 }, Vec2<int>{ 150, 50 }, "Medium", 3, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Default size is 10x10
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 200, 320 }, Vec2<int>{ 150, 50 }, "Default", 4, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Big size is 12x12
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 200, 380 }, Vec2<int>{ 150, 50 }, "Big", 5, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Square ensures Square Cells (and Board)  -  would be nice if this was a checkbox
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 450, 200 }, Vec2<int>{ 150, 50 }, "Square", 6, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//makes Board fill the entire screen
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 450, 260 }, Vec2<int>{ 150, 50 }, "Full Screen", 7, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Extra thick borders
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 450, 320 }, Vec2<int>{ 150, 50 }, "Thick Borders", 8, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Reset Thick borders
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 450, 380 }, Vec2<int>{ 150, 50 }, "Slim Borders", 9, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Back
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 25, Graphics::ScreenHeight - 65 }, Vec2<int>{ 75, 40 }, "Back", 1, letterspacing, border, half_bordersize, Colors::Red, Colors::White));
}
int MenuHandler::KaeseOptionsMenu::Update()
{
	while (!mouse.IsEmpty()) //brute force
	{
		const auto e = mouse.Read();
		for (auto i = 0u; i < vpButtons.size(); i++) //for(auto& i : objects)
		{
			if (e.GetType() == Mouse::Event::Type::LPress)
				vpButtons[i]->DoHitDetection(mouse.GetPosX(), mouse.GetPosY(), true);
			else
				vpButtons[i]->DoHitDetection(mouse.GetPosX(), mouse.GetPosY(), false);
			switch (int temp = vpButtons[i]->Update())
			{
			case 0:
				break; //don't return 0 directly, or it will cancel on the first Button
			default:
				return temp;
			}
		}
	}
	return 0;
}

/*******************************************************************************************************************************************/

MenuHandler::SnakeMenu::SnakeMenu(Graphics & gfx, Mouse & mouse, Text & text) : Menu(gfx, mouse, text) 
{
	//Welcome Label
	vpLabels.emplace_back(std::make_unique<Label>(
		gfx, text, "Welcome to Snake", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, letterspacing, border, Color(0u, 0u, 185u), Colors::White));
	//Start
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 325, 200 }, Vec2<int>{ 150, 50 }, "Start", 2, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Optionen
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 325, 460 }, Vec2<int>{ 150, 50 }, "Optionen", 3, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Back
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 25, Graphics::ScreenHeight - 65 }, Vec2<int>{ 75, 40 }, "Back", 1, letterspacing, border, half_bordersize, Colors::Red, Colors::White));
}
int MenuHandler::SnakeMenu::Update()
{
	while (!mouse.IsEmpty()) //brute force
	{
		const auto e = mouse.Read();
		for (auto i = 0u; i < vpButtons.size(); i++) //for(auto& i : objects)
		{
			if (e.GetType() == Mouse::Event::Type::LPress)
				vpButtons[i]->DoHitDetection(mouse.GetPosX(), mouse.GetPosY(), true);
			else
				vpButtons[i]->DoHitDetection(mouse.GetPosX(), mouse.GetPosY(), false);
			switch (int temp = vpButtons[i]->Update())
			{
			case 0:
				break; //don't return 0 directly, or it will cancel on the first Button
			case 2:
				return _StartSnake;
			case 3:
				return _SnakeMenu;
			default:
				return temp;
			}
		}
	}
	return 0;
}

MenuHandler::SnakeOptionsMenu::SnakeOptionsMenu(Graphics & gfx, Mouse & mouse, Text & text) : Menu(gfx, mouse, text)
{
	//Optionen
	vpLabels.emplace_back(std::make_unique<Label>(
		gfx, text, "Optionen", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, letterspacing, border, Color(0u, 0u, 185u), Colors::White));
	//Small size is 4x4  -  would be nice if this was a slider
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 200, 200 }, Vec2<int>{ 150, 50 }, "Small", 2, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Medium size is 8x8
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 200, 260 }, Vec2<int>{ 150, 50 }, "Medium", 3, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Default size is 10x10
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 200, 320 }, Vec2<int>{ 150, 50 }, "Default", 4, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Big size is 12x12
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 200, 380 }, Vec2<int>{ 150, 50 }, "Big", 5, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Doublespeed
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 450, 200 }, Vec2<int>{ 150, 50 }, "Doublespeed", 6, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Normalspeed
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 450, 260 }, Vec2<int>{ 150, 50 }, "Normalspeed", 7, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Extra thick borders
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 450, 320 }, Vec2<int>{ 150, 50 }, "Thick Borders", 8, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Reset Thick borders
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 450, 380 }, Vec2<int>{ 150, 50 }, "Slim Borders", 9, letterspacing, border, half_bordersize, Colors::Gray, Colors::Black));
	//Back
	vpButtons.emplace_back(std::make_unique<Button>(
		text, gfx, Vec2<int>{ 25, Graphics::ScreenHeight - 65 }, Vec2<int>{ 75, 40 }, "Back", 1, letterspacing, border, half_bordersize, Colors::Red, Colors::White));
}
int MenuHandler::SnakeOptionsMenu::Update()
{
	while (!mouse.IsEmpty()) //brute force
	{
		const auto e = mouse.Read();
		for (auto i = 0u; i < vpButtons.size(); i++) //for(auto& i : objects)
		{
			if (e.GetType() == Mouse::Event::Type::LPress)
				vpButtons[i]->DoHitDetection(mouse.GetPosX(), mouse.GetPosY(), true);
			else
				vpButtons[i]->DoHitDetection(mouse.GetPosX(), mouse.GetPosY(), false);
			switch (int temp = vpButtons[i]->Update())
			{
			case 0:
				break; //don't return 0 directly, or it will cancel on the first Button
			default:
				return temp;
			}
		}
	}
	return 0;
}
