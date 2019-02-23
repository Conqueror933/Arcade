#include "Kaesekaestchen.h"
#include "Game.h"

Kaesekaestchen::Kaesekaestchen(Graphics& gfx, Mouse& mouse, void* data, int flag)
	:
	gfx(gfx),
	mouse(mouse)
{
	Board::BoardInit brdinit; 
	short* ptr = static_cast<short*>(data);
	brdinit.boardcellcounts = Vec2<int>(int(ptr[12]), int(ptr[13]));
	brdinit.boardcellsize = Vec2<int>(int(ptr[14]), int(ptr[15])); 
	brdinit.boardborderthickness = static_cast<double*>(data)[4];
	switch (flag)
	{
	case 0://twoPlayer;
		if (brdinit.boardcellsize == Vec2<int>{0, 0})
			brd = new TwoPlayer(gfx, brdinit.brdclr, brdinit.boardcellcounts, brdinit.boardborderthickness);
		else
			brd = new TwoPlayer(gfx, brdinit.brdclr, brdinit.boardcellcounts, brdinit.boardcellsize, brdinit.boardborderthickness);
		break;
	case 1://AILevel1;
		if (brdinit.boardcellsize == Vec2<int>{0, 0})
			brd = new EasyAI(gfx, brdinit.brdclr, brdinit.boardcellcounts, brdinit.boardborderthickness);
		else
			brd = new EasyAI(gfx, brdinit.brdclr, brdinit.boardcellcounts, brdinit.boardcellsize, brdinit.boardborderthickness);
		break;
	case 2://AILevel2;
		if (brdinit.boardcellsize == Vec2<int>{0, 0})
			brd = new MediumAI(gfx, brdinit.brdclr, brdinit.boardcellcounts, brdinit.boardborderthickness);
		else
			brd = new MediumAI(gfx, brdinit.brdclr, brdinit.boardcellcounts, brdinit.boardcellsize, brdinit.boardborderthickness);
		break;
	case 3://AILevel3;
		if (brdinit.boardcellsize == Vec2<int>{0, 0})
			brd = new HardAI(gfx, brdinit.brdclr, brdinit.boardcellcounts, brdinit.boardborderthickness);
		else
			brd = new HardAI(gfx, brdinit.brdclr, brdinit.boardcellcounts, brdinit.boardcellsize, brdinit.boardborderthickness);
		break;
	}
	kkm = running;
}


Kaesekaestchen::~Kaesekaestchen()
{
	if (brd != nullptr)
	{
		delete brd;
		brd = nullptr;
	}
}

int Kaesekaestchen::Update()
{
	switch (kkm)
	{
	case running:
		while (!mouse.IsEmpty())
		{
			const auto e = mouse.Read();
			if (e.GetType() == Mouse::Event::Type::LPress) {
				auto temp = brd->Update(mouse.GetPosX(), mouse.GetPosY());
				if (temp == 1)
					kkm = Player1Victory;
				else if (temp == 2)
					kkm = Player2Victory;
				else if (temp == 3)
					kkm = Undecided;
			}
		}
	default:
		while (!mouse.IsEmpty())
		{
			const auto e = mouse.Read();
			if (e.GetType() == Mouse::Event::Type::LPress)
				return 1;
		}
	}
	return 0;
}

void Kaesekaestchen::Draw()
{
	switch (kkm)
	{
	case running:
		brd->Draw();
		break;
	case Player1Victory:
		gfx.DrawRectangle(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Blue);
		brd->Draw();
		break;
	case Player2Victory:
		gfx.DrawRectangle(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Red);
		brd->Draw();
		break;
	case Undecided:
		gfx.DrawRectangle(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Cyan);
		brd->Draw();
		break;
	default:
		throw std::exception("Bad Gamestate.");
	}
}
