#include "playerAI.h"

PlayerAI::PlayerAI()
{
	ai = new AI();
}

PlayerAI::~PlayerAI()
{
	delete ai;
}

bool PlayerAI::Init()
{
	ShipData s;

	for (int i = SHIP_TYPE_COUNT; i > 0; --i)
	{
		while (shipList->isNewShipLengthValid(i))
		{
			s.length = i;
			ai->GenerateShip(s);

			if (shipList->isNewShipLocationValid(s))
			{
				shipList->PushNewShip(s);
				ai->UpdateField(s);
			}
		}
	}

	ai->ResetField();

	return true;
}

bool PlayerAI::AttackCell(CellData &c)
{
	ai->GetCellToAttack(c);
	return true;
}

bool PlayerAI::IsHit(CellData c)
{
	return shipList->Hit(c);
}

void PlayerAI::ProcessResult(CellData c, bool isHit)
{
	if (isHit)
	{
		ai->ProcessHit(c);
	}
	else
	{
		ai->ProcessMiss(c);
	}
}