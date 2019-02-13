#include "battleFieldUI.h"
#include <iostream>

using namespace std;

BattleFieldUI::BattleFieldUI()
{
	for (int i = 0; i < FIELD_SIZE; ++i)
	{
		for (int j = 0; j < FIELD_SIZE; ++j)
		{
			field[i][j] = DEFAULT_CHAR;
		}
	}
}

BattleFieldUI::~BattleFieldUI()
{
}

void BattleFieldUI::Display()
{
	char letter = 'A';

	cout << "    0 1 2 3 4 5 6 7 8 9" << endl;
	cout << "  -----------------------\n";
	for (int i = 0; i < FIELD_SIZE; ++i) 
	{
		cout << letter++ << " " << "| ";

		for (int j = 0; j < FIELD_SIZE; ++j) 
		{
			cout << field[i][j] << " ";
		}
		cout << "|";
		cout << endl;
	}
	cout << "  -----------------------" << endl;
}

void BattleFieldUI::DisplayNewShip(ShipData s)
{
	switch (s.direction)
	{
		case NONE:
		{
			field[s.topLeftRow][s.topLeftColumn] = SHIP_CHAR;
			return;
		}
		case HORIZONTAL:
		{
			for (int i = 0; i < s.length; ++i)
			{
				field[s.topLeftRow][s.topLeftColumn + i] = SHIP_CHAR;
			}
			return;
		}
		case VERTICAL:
		{
			for (int i = 0; i < s.length; ++i)
			{
				field[s.topLeftRow + i][s.topLeftColumn] = SHIP_CHAR;
			}
			return;
		}
	}
}

void BattleFieldUI::DisplayHit(CellData c)
{
	field[c.row][c.column] = HIT_CHAR;
}

void BattleFieldUI::DisplayMiss(CellData c)
{
	field[c.row][c.column] = MISS_CHAR;
}