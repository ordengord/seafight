#include "game.h"

Game::Game()
{
}

Game::Game(Player *a, Player *b) : p1(a), p2(b) 
{
	if (Init())
	{
		Play();
	}
}

Game::~Game()
{
}

bool Game::Init()
{
	if (!p1->Init())
	{
		return false;
	}

	return p2->Init();
}

void Game::Play()
{
	Player *activePlayer = p1, *standByPlayer = p2;
	CellData c;
	bool isHit = false;

	do
	{
		if (!isHit)
		{
			activePlayer = standByPlayer;
			standByPlayer = (activePlayer == p1) ? p2 : p1;
		}

		if (!activePlayer->AttackCell(c))
		{
			return;
		}

		isHit = standByPlayer->IsHit(c);
		activePlayer->ProcessResult(c, isHit);
	}
	while(standByPlayer->hasShip());

	activePlayer->Win();
	standByPlayer->Lose();
}