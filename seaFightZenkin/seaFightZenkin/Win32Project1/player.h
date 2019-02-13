#pragma once
#include "shipList.h"

class Player
{
protected:
	ShipList *shipList;
public:
	Player();
	~Player();

	virtual bool Init();
	virtual bool AttackCell(CellData &c);
	virtual bool IsHit(CellData c);
	virtual void ProcessResult(CellData c, bool isHit);

	virtual void Win();
	virtual void Lose();

	bool hasShip();
};