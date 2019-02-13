#include "ui.h"
#include <iostream>
#include <string>

using namespace std;

UI::UI()
{
	myField = new BattleFieldUI();
	enemyField = new BattleFieldUI();
}

UI::~UI()
{
	delete myField;
	delete enemyField;
}

void UI::DisplayGreeting()
{
	cout << "SeaFight Game by Sergey Zenkin\n\n";
}

bool isExit(string s)
{
	if ((s.length() > 0) && (s.compare(1, 1, "x", 1, 1) == 0))
	{
		cout << "You exited from the game. Good Buy! Looking forward to seeing you again!" << endl;
		return true;
	}

	return false;
}

bool isInputOk(string s, CellData &c)
{
	if ((s.length() == 0) || (s.length() > 2))
	{
		return false;
	}

	if ((s[0] >= 'A') && (s[0] <= 'J'))
	{
		c.row = s[0] - 'A';
	}
	else if ((s[0] >= 'a') && (s[0] <= 'j'))
	{
		c.row = s[0] - 'a';
	}
	else
	{
		return false;
	}

	if ((s[1] >= '0') && (s[1] <= '9'))
	{
		c.column = s[1] - '0';
	}
	else
	{
		return false;
	}

	return true;
}

void UI::DisplayMessage(char *m)
{
	string s;
	cout << m << endl;
	cout << "Press any key to continue..." << endl;

	getline(cin, s);
}

bool UI::GetNewShipData(ShipData &s)
{
	string startCellString, endCellString;
	CellData startCell, endCell;

	do
	{
		myField->Display();

		cout << "Please enter a new ship start and end cells" << endl;
		cout << "The cells should be between a0 and j9" << endl;
		cout << "For one-deck ship start cell and end cell should match" << endl;
		cout << "Use \'x\' for exit" << endl << endl;

		cout << "Start cell: ";

		getline(cin, startCellString);

		if (isExit(startCellString))
		{
			return false;
		}

		cout << "End cell: ";
	
		getline(cin, endCellString);

		if (isExit(endCellString))
		{
			return false;
		}

		cout << endl;

		cout << "You entered: " << startCellString << " " << endCellString << endl << endl;

		if (!isInputOk(startCellString, startCell) ||
			!isInputOk(endCellString, endCell))
		{
			DisplayMessage("The cell values should be between a0 and j9. Please try again!");
			continue;
		}

		if ((startCell.row != endCell.row) && (startCell.column != endCell.column))
		{
			DisplayMessage("The cells should be in a single row or in a single column. Please try again!");
			continue;
		}

		if (startCell.row == endCell.row)
		{
			s.topLeftRow = startCell.row;

			if (startCell.column > endCell.column)
			{
				s.length = startCell.column - endCell.column + 1;
				s.topLeftColumn = endCell.column;
			}
			else
			{
				s.length = endCell.column - startCell.column + 1;
				s.topLeftColumn = startCell.column;
			}

			s.direction = (s.length > 1) ? HORIZONTAL : NONE;

			if (s.length > MAX_LENGTH)
			{
				DisplayMessage("The ship is too long. Please try again!");
				continue;
			}
		}

		if (startCell.column == endCell.column)
		{
			s.topLeftColumn = startCell.column;

			if (startCell.row > endCell.row)
			{
				s.length = startCell.row - endCell.row + 1;
				s.topLeftRow = endCell.row;
			}
			else
			{
				s.length = endCell.row - startCell.row + 1;
				s.topLeftRow = startCell.row;
			}

			s.direction = (s.length > 1) ? VERTICAL : NONE;

			if (s.length > MAX_LENGTH)
			{
				DisplayMessage("The ship is too long. Please try again!");
				continue;
			}
		}

		return true;
	}
	while(true);
}

bool UI::GetCellToAttack(CellData &c)
{
	string input;

	do
	{
		DisplayFields();

		cout << "Cell to attack: ";

		getline(cin, input);

		if (isExit(input))
		{
			return false;
		}

		if (!isInputOk(input, c))
		{
			DisplayMessage("The value should be between a0 and j9. Please try again!");
			continue;
		}

		break;
	}
	while (true);
}

void UI::DisplayNewShip(ShipData s)
{
	myField->DisplayNewShip(s);
}

void UI::DisplayEnemyFieldHit(CellData c)
{
	enemyField->DisplayHit(c);
}

void UI::DisplayEnemyFieldMiss(CellData c)
{
	enemyField->DisplayMiss(c);
}

void UI::DisplayMyFieldHit(CellData c)
{
	cout << "Enemy hit: " << (char) ('a'+ c.row) << (char)('0' + c.column) << endl;
	myField->DisplayHit(c);
}

void UI::DisplayMyFieldMiss(CellData c)
{
	cout << "Enemy missed: " << char('a'+ c.row) << (char)('0' + c.column) << endl;
	myField->DisplayMiss(c);
}

void UI::DisplayFields()
{
	cout << "Your field: " << endl;
	myField->Display();
	cout << endl;

	cout << "Enemy field: " << endl;
	enemyField->Display();
	cout << endl;
}