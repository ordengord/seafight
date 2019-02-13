#include "playerHuman.h"

PlayerHuman::PlayerHuman()
{
	ui = new UI();
}

PlayerHuman::~PlayerHuman()
{
	delete ui;
}

bool PlayerHuman::Init()
{
	ShipData s;

	ui->DisplayGreeting();

	do
	{
		if (!ui->GetNewShipData(s))
		{
			return false;
		}

		if (!shipList->isNewShipLengthValid(s.length))
		{
			ui->DisplayMessage("There are enough ships of this length. Please try again!");
			continue;
		}

		if (!shipList->isNewShipLocationValid(s))
		{
			ui->DisplayMessage("The ship is too close to another ship. Please try again!");
			continue;
		}

		shipList->PushNewShip(s);
		ui->DisplayNewShip(s);
	}
	while(!shipList->Full()); 

/*
	s = ShipData(3,4,4,HORIZONTAL);
	shipList->PushNewShip(s);
	ui->DisplayNewShip(s);

	s = ShipData(0,6,2,VERTICAL);
	shipList->PushNewShip(s);
	ui->DisplayNewShip(s);

	s = ShipData(2,2,3,VERTICAL);
	shipList->PushNewShip(s);
	ui->DisplayNewShip(s);

	s = ShipData(1,8,1,NONE);
	shipList->PushNewShip(s);
	ui->DisplayNewShip(s);

	s = ShipData(6,0,3,HORIZONTAL);
	shipList->PushNewShip(s);
	ui->DisplayNewShip(s);

	s = ShipData(5,4,1,NONE);
	shipList->PushNewShip(s);
	ui->DisplayNewShip(s);

	s = ShipData(5,6,2,VERTICAL);
	shipList->PushNewShip(s);
	ui->DisplayNewShip(s);

	s = ShipData(9,8,1,NONE);
	shipList->PushNewShip(s);
	ui->DisplayNewShip(s);

	s = ShipData(5,8,2,HORIZONTAL);
	shipList->PushNewShip(s);
	ui->DisplayNewShip(s);

	s = ShipData(3,9,1,NONE);
	shipList->PushNewShip(s);
	ui->DisplayNewShip(s);
*/

	return true;
}

bool PlayerHuman::AttackCell(CellData &c)
{
	return ui->GetCellToAttack(c);
}

bool PlayerHuman::IsHit(CellData c)
{
	if (shipList->Hit(c))
	{
		ui->DisplayMyFieldHit(c);
		return true;
	}

	ui->DisplayMyFieldMiss(c);
	return false;
}

void PlayerHuman::ProcessResult(CellData c, bool isHit)
{
	if (isHit)
	{
		ui->DisplayEnemyFieldHit(c);
	}
	else
	{
		ui->DisplayEnemyFieldMiss(c);
	}
}

void PlayerHuman::Win()
{
	ui->DisplayFields();
	ui->DisplayMessage("Congratulations! You won!");
}

void PlayerHuman::Lose()
{
	ui->DisplayFields();
	ui->DisplayMessage("You were unfortunate this time. Would you like to play once more?");
}
