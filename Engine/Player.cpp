#include "Player.h"

Player::Player(int Playernumber, Color in_c)
{
	c = in_c;
	playernumber = Playernumber;
}

const Color Player::GetColor()
{
	return c;
}

const int Player::GetCounter()
{
	return counter;
}

void Player::SetCounter()
{
	counter++;
}
