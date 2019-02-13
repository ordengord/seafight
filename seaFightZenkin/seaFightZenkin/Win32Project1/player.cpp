#include "Player.h"

Player::Player()
{
	shipList = new ShipList();
}

Player::~Player()
{
	delete shipList;
}

bool Player::Init()
{
	return true;
}

bool Player::AttackCell(CellData &c)
{
	return true;
}

bool Player::IsHit(CellData c)
{
	return false;
}
	
void Player::ProcessResult(CellData c, bool isHit)
{
}

void Player::Win()
{
}

void Player::Lose()
{
}

bool Player::hasShip()
{
	return !shipList->Empty();
}