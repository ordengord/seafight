#include "ai.h"
#include <stdlib.h>
#include <time.h>

AI::AI()
{
	aiField = new BattleFieldAI();
	srand(time(NULL));
	//srand(25);

	for (int i = 0; i < SHIP_TYPE_COUNT; ++i)
	{
		enemyShips[i] = SHIP_TYPE_COUNT - i;
	}

	damagedShip.length = 0;
	damagedShip.direction = NONE;
	damagedShip.topLeftRow = 0;
	damagedShip.topLeftRow = 0;

	enemyShipMaxRemainingLength = SHIP_TYPE_COUNT;
}

AI::~AI()
{
	delete aiField;
}

void AI::ResetField()
{
	aiField->Reset();
}

void AI::GenerateShip(ShipData &s)
{
	CellData c;

	do
	{
		int availableCount = aiField->GetAvailableCellsCount();
		int position = rand() % availableCount;

		aiField->GetAvailableCellByPosition(position, c);

		s.topLeftRow = c.row;
		s.topLeftColumn = c.column;
	
		if (s.length == 1)
		{
			s.direction = NONE;
			break;
		}
		
		s.direction = (rand() % 2) ? HORIZONTAL : VERTICAL;

		if ((s.direction == HORIZONTAL) && ((s.topLeftColumn + s.length) > FIELD_SIZE))
		{
			continue;
		}

		if ((s.direction == VERTICAL) && ((s.topLeftRow + s.length) > FIELD_SIZE))
		{
			continue;
		}

		break;
	}
	while(true);
}

void AI::UpdateField(ShipData s)
{
	aiField->UpdateField(s);
}

void AI::ProcessMiss(CellData c)
{
	aiField->UpdateCell(c);
}

bool AI::IsShipDamaged()
{
	return (damagedShip.length > 0);
}

void AI::DestroyDamagedShip()
{
	--enemyShips[damagedShip.length - 1];
	aiField->UpdateField(damagedShip);
	damagedShip.length = 0;
}

void AI::UpdateEnemyShipMaxRemainingLength()
{
	for (int i = enemyShipMaxRemainingLength - 1; i >= 0; --i)
	{
		if (enemyShips[i] > 0)
		{
			enemyShipMaxRemainingLength = i + 1;
			break;
		}
	}
}

bool AI::GetDamagedShipOption(CellData &option)
{
	int count = 0;
	CellData options[MAX_LENGTH];
	CellData c;

	switch (damagedShip.direction)
	{
		case NONE:
		{
			// above cell
			if (damagedShip.topLeftRow > 0)
			{
				c.row = damagedShip.topLeftRow - 1;
				c.column = damagedShip.topLeftColumn;

				if (aiField->GetCellValue(c))
				{
					options[count++] = c;
				}
			}

			// below cell
			if (damagedShip.topLeftRow < (FIELD_SIZE - 1))
			{
				c.row = damagedShip.topLeftRow + 1;
				c.column = damagedShip.topLeftColumn;

				if (aiField->GetCellValue(c))
				{
					options[count++] = c;
				}
			}
			
			// left cell
			if (damagedShip.topLeftColumn > 0)
			{
				c.row = damagedShip.topLeftRow;
				c.column = damagedShip.topLeftColumn - 1;

				if (aiField->GetCellValue(c))
				{
					options[count++] = c;
				}
			}

			// right cell
			if (damagedShip.topLeftColumn < (FIELD_SIZE - 1))
			{
				c.row = damagedShip.topLeftRow;
				c.column = damagedShip.topLeftColumn + 1;

				if (aiField->GetCellValue(c))
				{
					options[count++] = c;
				}
			}
			break;
		}
		case HORIZONTAL:
		{
			// left cell
			if (damagedShip.topLeftColumn > 0)
			{
				c.row = damagedShip.topLeftRow;
				c.column = damagedShip.topLeftColumn - 1;

				if (aiField->GetCellValue(c))
				{
					options[count++] = c;
				}
			}

			// right cell
			if ((damagedShip.topLeftColumn + damagedShip.length) < FIELD_SIZE )
			{
				c.row = damagedShip.topLeftRow;
				c.column = damagedShip.topLeftColumn + damagedShip.length;

				if (aiField->GetCellValue(c))
				{
					options[count++] = c;
				}
			}
			break;
		}
		case VERTICAL:
		{
			// above cell
			if (damagedShip.topLeftRow > 0)
			{
				c.row = damagedShip.topLeftRow - 1;
				c.column = damagedShip.topLeftColumn;

				if (aiField->GetCellValue(c))
				{
					options[count++] = c;
				}
			}

			// below cell
			if ((damagedShip.topLeftRow + damagedShip.length) < FIELD_SIZE )
			{
				c.row = damagedShip.topLeftRow + damagedShip.length;
				c.column = damagedShip.topLeftColumn;

				if (aiField->GetCellValue(c))
				{
					options[count++] = c;
				}
			}
			break;
		}
	}

	if (count == 0)
	{
		return false;
	}

	int index = rand() % count;
	option = options[index];

	return true;
}

void AI::GetCellToAttack(CellData &c)
{

	if (damagedShip.length == enemyShipMaxRemainingLength)
	{
		DestroyDamagedShip();
		UpdateEnemyShipMaxRemainingLength();
	}

	if (IsShipDamaged())
	{
		if (GetDamagedShipOption(c))
		{
			return;
		}
		DestroyDamagedShip();
	}

	int availableCount = aiField->GetAvailableCellsCount();
	int position = rand() % availableCount;

	aiField->GetAvailableCellByPosition(position, c);
}

void AI::ProcessHit(CellData c)
{
	if (damagedShip.length == 0)
	{
		damagedShip.length = 1;
		damagedShip.topLeftRow = c.row;
		damagedShip.topLeftColumn = c.column;
		damagedShip.direction = NONE;
	}
	else
	{
		++damagedShip.length;

		if (damagedShip.topLeftRow == c.row)
		{
			damagedShip.direction = HORIZONTAL;
			damagedShip.topLeftColumn = (damagedShip.topLeftColumn < c.column) ?
				damagedShip.topLeftColumn : c.column;
		}
		else if (damagedShip.topLeftColumn == c.column)
		{
			damagedShip.direction = VERTICAL;
			damagedShip.topLeftRow = (damagedShip.topLeftRow < c.row) ?
				damagedShip.topLeftRow : c.row;
		}
		else
		{
			//error
		}
	}
}
