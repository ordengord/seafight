#include "battleFieldAI.h"

BattleFieldAI::BattleFieldAI()
{
	Reset();
}

BattleFieldAI::~BattleFieldAI()
{
}

void BattleFieldAI::Reset()
{
	for (int i = 0; i < FIELD_SIZE; ++i)
	{
		for (int j = 0; j < FIELD_SIZE; ++j)
		{
			field[i][j] = true;
		}
	}

	availableCellsCount = FIELD_SIZE * FIELD_SIZE;
}


int BattleFieldAI::GetAvailableCellsCount()
{
	return availableCellsCount;
}

void BattleFieldAI::GetAvailableCellByPosition(int position, CellData &c)
{
	int count = 0;

	for (int i = 0; i < FIELD_SIZE; ++i)
	{
		for (int j = 0; j < FIELD_SIZE; ++j)
		{
			if (field[i][j])
			{
				if ( count == position )
				{
					c.row = i;
					c.column = j;
					return;
				}

				++count;
			}
		}
	}
}

void BattleFieldAI::UpdateCell(CellData c)
{
	int value = field[c.row][c.column];
	field[c.row][c.column] = false;
	availableCellsCount -= value;
}

bool BattleFieldAI::GetCellValue(CellData c)
{
	return field[c.row][c.column];
}

void BattleFieldAI::UpdateField(ShipData s)
{
	int value;
	if (s.direction != VERTICAL)
	{
		// update cells above
		if (s.topLeftRow > 0)
		{
			// upper left corner
			if (s.topLeftColumn > 0)
			{
				UpdateCell(CellData(s.topLeftRow - 1, s.topLeftColumn - 1));
			}

			// upper right corner
			if ((s.topLeftColumn + s.length) < FIELD_SIZE)
			{
				UpdateCell(CellData(s.topLeftRow - 1, s.topLeftColumn + s.length));
			}

			// cells above
			for (int i = 0; i < s.length; ++i)
			{
				UpdateCell(CellData(s.topLeftRow - 1, s.topLeftColumn + i));
			}
		}

		// update cells below
		if (s.topLeftRow < (FIELD_SIZE - 1) )
		{
			// lower left corner
			if (s.topLeftColumn > 0)
			{
				UpdateCell(CellData(s.topLeftRow + 1, s.topLeftColumn - 1));
			}

			// lower right corner
			if ((s.topLeftColumn + s.length) < FIELD_SIZE)
			{
				UpdateCell(CellData(s.topLeftRow + 1, s.topLeftColumn + s.length));
			}

			// cells below
			for (int i = 0; i < s.length; ++i)
			{
				UpdateCell(CellData(s.topLeftRow + 1, s.topLeftColumn + i));
			}
		}

		// the middle at the left
		if (s.topLeftColumn > 0)
		{
			UpdateCell(CellData(s.topLeftRow, s.topLeftColumn - 1));
		}

		// the middle at the right
		if ((s.topLeftColumn + s.length) < FIELD_SIZE)
		{
			UpdateCell(CellData(s.topLeftRow, s.topLeftColumn + s.length));
		}

		// the ship itself
		for (int i = 0; i < s.length; ++i)
		{
			UpdateCell(CellData(s.topLeftRow, s.topLeftColumn + i));
		}
	}
	else
	{
		// update cells to the left
		if (s.topLeftColumn > 0)
		{
			// left upper corner
			if (s.topLeftRow > 0)
			{
				UpdateCell(CellData(s.topLeftRow - 1, s.topLeftColumn - 1));
			}

			// left lower corner
			if ((s.topLeftRow + s.length) < FIELD_SIZE)
			{
				UpdateCell(CellData(s.topLeftRow + s.length, s.topLeftColumn - 1));
			}

			// cells to the left
			for (int i = 0; i < s.length; ++i)
			{
				UpdateCell(CellData(s.topLeftRow + i, s.topLeftColumn - 1));
			}
		}

		// update cells to the right
		if (s.topLeftColumn < (FIELD_SIZE - 1) )
		{
			// right upper corner
			if (s.topLeftRow > 0)
			{
				UpdateCell(CellData(s.topLeftRow - 1, s.topLeftColumn + 1));
			}

			// right lower corner
			if ((s.topLeftRow + s.length) < FIELD_SIZE)
			{
				UpdateCell(CellData(s.topLeftRow + s.length, s.topLeftColumn + 1));
			}

			// cells to the right
			for (int i = 0; i < s.length; ++i)
			{
				UpdateCell(CellData(s.topLeftRow + i, s.topLeftColumn + 1));
			}
		}

		// the middle above
		if (s.topLeftRow > 0)
		{
			UpdateCell(CellData(s.topLeftRow - 1, s.topLeftColumn));
		}

		// the middle below
		if ((s.topLeftRow + s.length) < FIELD_SIZE)
		{
			UpdateCell(CellData(s.topLeftRow + s.length, s.topLeftColumn));
		}

		// the ship itself
		for (int i = 0; i < s.length; ++i)
		{
			UpdateCell(CellData(s.topLeftRow + i, s.topLeftColumn));
		}
	}
}