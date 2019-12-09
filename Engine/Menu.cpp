#include "Menu.h"
#include "Game.h"

MenuHandler::MenuHandler(Graphics & gfx, Mouse & mouse) : gfx(gfx), mouse(mouse), text(gfx, "Letters2.bmp")
{
	spSubMenus.push(std::make_unique<IQuit>());
	spSubMenus.push(std::make_unique<MainMenu>(*this));
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
		spSubMenus.push(std::make_unique<KaeseMenu>(*this)); break;
	case _KaeseMenu:
		spSubMenus.push(std::make_unique<KaeseOptionsMenu>(*this)); break;
	case _Snake:
		spSubMenus.push(std::make_unique<SnakeMenu>(*this)); break;
	case _SnakeMenu:
		spSubMenus.push(std::make_unique<SnakeOptionsMenu>(*this)); break;
	case _Pong:
		spSubMenus.push(std::make_unique<PongMenu>(*this)); break;
	case _PongMenu:
		spSubMenus.push(std::make_unique<PongOptionsMenu>(*this)); break;
	case _DevMode:
		spSubMenus.push(std::make_unique<DevModeMenu>(*this)); break;
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

MenuHandler::Menu::Menu(MenuHandler& menuHandler) : mH(menuHandler) {}

MenuHandler::MainMenu::MainMenu(MenuHandler& menuHandler) : Menu(menuHandler) 
{
	//Welcome Label
	vpLabels.emplace_back(std::make_unique<Label>(
		mH.gfx, mH.text, "Willkommen zur Arcade", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, letterspacing, border, Color(0u, 0u, 185u), Colors::White));

	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 325, 200 }, Vec2<int>{ 150, 50 }, "Kaesekaestchen", 2, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 325, 260 }, Vec2<int>{ 150, 50 }, "Snake", 3, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 325, 320 }, Vec2<int>{ 150, 50 }, "Pong", 4, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//End
	vpButtons.emplace_back(std::make_unique<Button>( 
		mH.text, mH.gfx, Vec2<int>{ 350, 500 }, Vec2<int>{ 100, 50 }, "Beenden", 1, letterspacing, border, half_bordersize, Colors::Red, Colors::White));
#ifdef _DEBUG
	vpButtons.emplace_back(std::make_unique<Button>( 
		mH.text, mH.gfx, Vec2<int>{ 360, 550 }, Vec2<int>{ 80, 40 }, "DevMode", 1000000, letterspacing, border, half_bordersize, Colors::Cyan, Colors::Black));
#endif
}
int MenuHandler::MainMenu::Update()
{
	while (!mH.mouse.IsEmpty()) //brute force
	{
		const auto e = mH.mouse.Read();
		for (auto i = 0u; i < vpButtons.size(); i++) //for(auto& i : objects)
		{
			if (e.GetType() == Mouse::Event::Type::LPress)
				vpButtons[i]->DoHitDetection(mH.mouse.GetPosX(), mH.mouse.GetPosY(), true);
			else
				vpButtons[i]->DoHitDetection(mH.mouse.GetPosX(), mH.mouse.GetPosY(), false);
			switch (int temp = vpButtons[i]->Update())
			{
			case 0:
				break; //don't return 0 directly, or it will cancel on the first Button
			case 2:
				mH.FlushData();
				return _Kaese;
			case 3:
				mH.FlushData();
				return _Snake;
			case 4:
				mH.FlushData();
				return _Pong;
			default:
				return temp;
			}
		}
	}
	return 0;
}

/*******************************************************************************************************************************************/

MenuHandler::KaeseMenu::KaeseMenu(MenuHandler& menuHandler) : Menu(menuHandler)
{
	//Welcome Label
	vpLabels.emplace_back(std::make_unique<Label>(
		mH.gfx, mH.text, "Willkommen zum Kaesekaestchen", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, letterspacing, border, Color(0u, 0u, 185u), Colors::White));
	//2 Player
	vpButtons.emplace_back(std::make_unique<Button>(
			mH.text, mH.gfx, Vec2<int>{ 325, 200 }, Vec2<int>{ 150, 50 }, "Zwei Spieler", 2, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//AI Level 1
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 325, 260 }, Vec2<int>{ 150, 50 }, "Einfach", 3, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//AI Level 2
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 325, 320 }, Vec2<int>{ 150, 50 }, "Mittel", 4, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//AI Level 3
	/*vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 325, 380 }, Vec2<int>{ 150, 50 }, "Schwer", 5, letterspacing, border, half_bordersize, Colors::White, Colors::Black));*/
	//Optionen
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 325, 460 }, Vec2<int>{ 150, 50 }, "Optionen", 6, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Back
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 25, Graphics::ScreenHeight - 65 }, Vec2<int>{ 75, 40 }, "Back", 1, letterspacing, border, half_bordersize, Colors::Red, Colors::White));

	//Set Default Values
	mH.data.AddEntry("Size", 10);
	mH.data.AddEntry("Square", 40);
	mH.data.AddEntry("Border", 0.25);
}
int MenuHandler::KaeseMenu::Update()
{
	while (!mH.mouse.IsEmpty()) //brute force
	{
		const auto e = mH.mouse.Read();
		for (auto i = 0u; i < vpButtons.size(); i++) //for(auto& i : objects)
		{
			if (e.GetType() == Mouse::Event::Type::LPress)
				vpButtons[i]->DoHitDetection(mH.mouse.GetPosX(), mH.mouse.GetPosY(), true);
			else
				vpButtons[i]->DoHitDetection(mH.mouse.GetPosX(), mH.mouse.GetPosY(), false);
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

MenuHandler::KaeseOptionsMenu::KaeseOptionsMenu(MenuHandler& menuHandler) : Menu(menuHandler)
{
	//Optionen
	vpLabels.emplace_back(std::make_unique<Label>(
		mH.gfx, mH.text, "Optionen", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, letterspacing, border, Color(0u, 0u, 185u), Colors::White));
	//Small size is 4x4  -  would be nice if this was a slider
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 200, 200 }, Vec2<int>{ 150, 50 }, "Small", 2, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Medium size is 8x8
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 200, 260 }, Vec2<int>{ 150, 50 }, "Medium", 3, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Default size is 10x10
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 200, 320 }, Vec2<int>{ 150, 50 }, "Default", 4, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Big size is 12x12
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 200, 380 }, Vec2<int>{ 150, 50 }, "Big", 5, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Square ensures Square Cells (and Board)  -  would be nice if this was a checkbox
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 450, 200 }, Vec2<int>{ 150, 50 }, "Square", 6, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//makes Board fill the entire screen
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 450, 260 }, Vec2<int>{ 150, 50 }, "Full Screen", 7, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Extra thick borders
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 450, 320 }, Vec2<int>{ 150, 50 }, "Thick Borders", 8, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Reset Thick borders
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 450, 380 }, Vec2<int>{ 150, 50 }, "Slim Borders", 9, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Back
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 25, Graphics::ScreenHeight - 65 }, Vec2<int>{ 75, 40 }, "Back", 1, letterspacing, border, half_bordersize, Colors::Red, Colors::White));
}
int MenuHandler::KaeseOptionsMenu::Update()
{
	while (!mH.mouse.IsEmpty()) //brute force
	{
		const auto e = mH.mouse.Read();
		for (auto i = 0u; i < vpButtons.size(); i++) //for(auto& i : objects)
		{
			if (e.GetType() == Mouse::Event::Type::LPress)
				vpButtons[i]->DoHitDetection(mH.mouse.GetPosX(), mH.mouse.GetPosY(), true);
			else
				vpButtons[i]->DoHitDetection(mH.mouse.GetPosX(), mH.mouse.GetPosY(), false);
			switch (int temp = vpButtons[i]->Update())
			{
			case 0:
				break; //don't return 0 directly, or it will cancel on the first Button
			case 2:
				mH.data.ChangeEntry("Size", 4); break; //Small
			case 3:
				mH.data.ChangeEntry("Size", 8); break; //Medium
			case 4:
				mH.data.ChangeEntry("Size", 10); break; //Default
			case 5:
				mH.data.ChangeEntry("Size", 12); break; //Big
			case 6:
				mH.data.ChangeEntry("Square", 40); break; //Square
			case 7:
				mH.data.ChangeEntry("Square", 0); break; //Free
			case 8:
				mH.data.ChangeEntry("Border", 0.35); break; //ThickBorder
			case 9:
				mH.data.ChangeEntry("Border", 0.25); break; //SlimBorder
			default:
				return temp;
			}
		}
	}
	return 0;
}

/*******************************************************************************************************************************************/

MenuHandler::SnakeMenu::SnakeMenu(MenuHandler& menuHandler) : Menu(menuHandler) 
{
	//Welcome Label
	vpLabels.emplace_back(std::make_unique<Label>(
		mH.gfx, mH.text, "Welcome to Snake", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, letterspacing, border, Color(0u, 0u, 185u), Colors::White));
	//Start
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 325, 200 }, Vec2<int>{ 150, 50 }, "Start", 2, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Optionen
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 325, 460 }, Vec2<int>{ 150, 50 }, "Optionen", 3, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Back
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 25, Graphics::ScreenHeight - 65 }, Vec2<int>{ 75, 40 }, "Back", 1, letterspacing, border, half_bordersize, Colors::Red, Colors::White));

	//Set Default Values
	mH.data.AddEntry("Size", 20);
	mH.data.AddEntry("Speed", 0.3f);
	mH.data.AddEntry("Border", 0.05);
}
int MenuHandler::SnakeMenu::Update()
{
	while (!mH.mouse.IsEmpty()) //brute force
	{
		const auto e = mH.mouse.Read();
		for (auto i = 0u; i < vpButtons.size(); i++) //for(auto& i : objects)
		{
			if (e.GetType() == Mouse::Event::Type::LPress)
				vpButtons[i]->DoHitDetection(mH.mouse.GetPosX(), mH.mouse.GetPosY(), true);
			else
				vpButtons[i]->DoHitDetection(mH.mouse.GetPosX(), mH.mouse.GetPosY(), false);
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

MenuHandler::SnakeOptionsMenu::SnakeOptionsMenu(MenuHandler& menuHandler) : Menu(menuHandler)
{
	//Optionen
	vpLabels.emplace_back(std::make_unique<Label>(
		mH.gfx, mH.text, "Optionen", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, letterspacing, border, Color(0u, 0u, 185u), Colors::White));
	//Small size is 4x4  -  would be nice if this was a slider
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 200, 200 }, Vec2<int>{ 150, 50 }, "Small", 2, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Medium size is 8x8
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 200, 260 }, Vec2<int>{ 150, 50 }, "Medium", 3, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Default size is 10x10
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 200, 320 }, Vec2<int>{ 150, 50 }, "Default", 4, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Big size is 12x12
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 200, 380 }, Vec2<int>{ 150, 50 }, "Big", 5, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Doublespeed
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 450, 200 }, Vec2<int>{ 150, 50 }, "Doublespeed", 6, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Normalspeed
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 450, 260 }, Vec2<int>{ 150, 50 }, "Normalspeed", 7, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Extra thick borders
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 450, 320 }, Vec2<int>{ 150, 50 }, "Thick Borders", 8, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Reset Thick borders
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 450, 380 }, Vec2<int>{ 150, 50 }, "Slim Borders", 9, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Back
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 25, Graphics::ScreenHeight - 65 }, Vec2<int>{ 75, 40 }, "Back", 1, letterspacing, border, half_bordersize, Colors::Red, Colors::White));
}
int MenuHandler::SnakeOptionsMenu::Update()
{
	while (!mH.mouse.IsEmpty()) //brute force
	{
		const auto e = mH.mouse.Read();
		for (auto i = 0u; i < vpButtons.size(); i++) //for(auto& i : objects)
		{
			if (e.GetType() == Mouse::Event::Type::LPress)
				vpButtons[i]->DoHitDetection(mH.mouse.GetPosX(), mH.mouse.GetPosY(), true);
			else
				vpButtons[i]->DoHitDetection(mH.mouse.GetPosX(), mH.mouse.GetPosY(), false);
			switch (int temp = vpButtons[i]->Update())
			{
			case 0:
				break; //don't return 0 directly, or it will cancel on the first Button
			case 2:
				mH.data.ChangeEntry("Size", 06); break; //Small
			case 3:
				mH.data.ChangeEntry("Size", 15); break; //Medium
			case 4:
				mH.data.ChangeEntry("Size", 20); break; //Default
			case 5:
				mH.data.ChangeEntry("Size", 30); break; //Big
			case 6:
				mH.data.ChangeEntry("Speed", 0.15f); break; //Doublespeed
			case 7:
				mH.data.ChangeEntry("Speed", 0.30f); break; //Normalspeed
			case 8:
				mH.data.ChangeEntry("Border", 0.30); break; //ThickBorder
			case 9:
				mH.data.ChangeEntry("Border", 0.05); break; //SlimBorder
			default:
				return temp;
			}
		}
	}
	return 0;
}

/*******************************************************************************************************************************************/

MenuHandler::PongMenu::PongMenu(MenuHandler& menuHandler) : Menu(menuHandler)
{
	//Welcome Label
	vpLabels.emplace_back(std::make_unique<Label>(
		mH.gfx, mH.text, "Welcome to Pong", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, letterspacing, border, Color(0u, 0u, 185u), Colors::White));
	//2 Player
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 325, 200 }, Vec2<int>{ 150, 50 }, "Zwei Spieler", 2, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//AI Level 1
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 325, 260 }, Vec2<int>{ 150, 50 }, "Einfache KI", 3, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//AI Level 2
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 325, 320 }, Vec2<int>{ 150, 50 }, "Mittlere KI", 4, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//AI Level 3
	vpButtons.emplace_back(std::make_unique<Button>(
	mH.text, mH.gfx, Vec2<int>{ 325, 380 }, Vec2<int>{ 150, 50 }, "Schwere KI", 5, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Optionen
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 325, 460 }, Vec2<int>{ 150, 50 }, "Optionen", 6, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Back
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 25, Graphics::ScreenHeight - 65 }, Vec2<int>{ 75, 40 }, "Back", 1, letterspacing, border, half_bordersize, Colors::Red, Colors::White));

	//Set Default Values
	mH.data.AddEntry("Gamemode", '2');
}
int MenuHandler::PongMenu::Update()
{
	while (!mH.mouse.IsEmpty()) //brute force
	{
		const auto e = mH.mouse.Read();
		for (auto i = 0u; i < vpButtons.size(); i++) //for(auto& i : objects)
		{
			if (e.GetType() == Mouse::Event::Type::LPress)
				vpButtons[i]->DoHitDetection(mH.mouse.GetPosX(), mH.mouse.GetPosY(), true);
			else
				vpButtons[i]->DoHitDetection(mH.mouse.GetPosX(), mH.mouse.GetPosY(), false);
			switch (int temp = vpButtons[i]->Update())
			{
			case 0:
				break; //don't return 0 directly, or it will cancel on the first Button
			case 2:
				mH.data.ChangeEntry("Gamemode", '2');
				return _StartPong;
			case 3:
				mH.data.ChangeEntry("Gamemode", 'E');
				return _StartPong;
			case 4:
				mH.data.ChangeEntry("Gamemode", 'M');
				return _StartPong;
			case 5:
				mH.data.ChangeEntry("Gamemode", 'H');
				return _StartPong;
			case 6:
				return _PongMenu;
			default:
				return temp;
			}
		}
	}
	return 0;
}

MenuHandler::PongOptionsMenu::PongOptionsMenu(MenuHandler& menuHandler) : Menu(menuHandler)
{
	//Optionen
	vpLabels.emplace_back(std::make_unique<Label>(
		mH.gfx, mH.text, "Optionen", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, letterspacing, border, Color(0u, 0u, 185u), Colors::White));
	//Small size is 4x4  -  would be nice if this was a slider
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 200, 200 }, Vec2<int>{ 150, 50 }, "Option1", 2, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Medium size is 8x8
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 200, 260 }, Vec2<int>{ 150, 50 }, "Option", 3, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Default size is 10x10
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 200, 320 }, Vec2<int>{ 150, 50 }, "Option", 4, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Big size is 12x12
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 200, 380 }, Vec2<int>{ 150, 50 }, "Option", 5, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Doublespeed
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 450, 200 }, Vec2<int>{ 150, 50 }, "Option", 6, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Normalspeed
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 450, 260 }, Vec2<int>{ 150, 50 }, "Option", 7, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Extra thick borders
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 450, 320 }, Vec2<int>{ 150, 50 }, "Option", 8, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Reset Thick borders
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 450, 380 }, Vec2<int>{ 150, 50 }, "Option1", 9, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Back
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 25, Graphics::ScreenHeight - 65 }, Vec2<int>{ 75, 40 }, "Back", 1, letterspacing, border, half_bordersize, Colors::Red, Colors::White));
}
int MenuHandler::PongOptionsMenu::Update()
{
	while (!mH.mouse.IsEmpty()) //brute force
	{
		const auto e = mH.mouse.Read();
		for (auto i = 0u; i < vpButtons.size(); i++) //for(auto& i : objects)
		{
			if (e.GetType() == Mouse::Event::Type::LPress)
				vpButtons[i]->DoHitDetection(mH.mouse.GetPosX(), mH.mouse.GetPosY(), true);
			else
				vpButtons[i]->DoHitDetection(mH.mouse.GetPosX(), mH.mouse.GetPosY(), false);
			switch (int temp = vpButtons[i]->Update())
			{
			case 0:
				break; //don't return 0 directly, or it will cancel on the first Button
			case 2:
				break; //Option-Button 1
			case 3:
				break; //Option-Button 2
			case 4:
				break; //Option-Button 3
			case 5:
				break; //Option-Button 4
			case 6:
				break; //Option-Button 5
			case 7:
				break; //Option-Button 6
			case 8:
				break; //Option-Button 7
			case 9:
				break; //Option-Button 8
			default:
				return temp;
			}
		}
	}
	return 0;
}

/*******************************************************************************************************************************************/

MenuHandler::DevModeMenu::DevModeMenu(MenuHandler& menuHandler) : Menu(menuHandler)
{
	//Welcome Label
	vpLabels.emplace_back(std::make_unique<Label>(
		mH.gfx, mH.text, "DevMode", Vec2<int>{ 200, 50 }, Vec2<int>{ 400, 100 }, letterspacing, border, Color(0u, 0u, 185u), Colors::White));
	//Start
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 325, 200 }, Vec2<int>{ 150, 50 }, "Start", 2, letterspacing, border, half_bordersize, Colors::White, Colors::Black));
	//Back
	vpButtons.emplace_back(std::make_unique<Button>(
		mH.text, mH.gfx, Vec2<int>{ 25, Graphics::ScreenHeight - 65 }, Vec2<int>{ 75, 40 }, "Back", 1, letterspacing, border, half_bordersize, Colors::Red, Colors::White));
}

int MenuHandler::DevModeMenu::Update()
{
	while (!mH.mouse.IsEmpty()) //brute force
	{
		const auto e = mH.mouse.Read();
		for (auto i = 0u; i < vpButtons.size(); i++) //for(auto& i : objects)
		{
			if (e.GetType() == Mouse::Event::Type::LPress)
				vpButtons[i]->DoHitDetection(mH.mouse.GetPosX(), mH.mouse.GetPosY(), true);
			else
				vpButtons[i]->DoHitDetection(mH.mouse.GetPosX(), mH.mouse.GetPosY(), false);
			switch (int temp = vpButtons[i]->Update())
			{
			case 0:
				break; //don't return 0 directly, or it will cancel on the first Button
			case 2:
				return _StartDevMode;
			default:
				return temp;
			}
		}
	}
	return 0;
}