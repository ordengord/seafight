#include "ship.h"

Ship::Ship()
{
	for (int i = 0; i < MAX_LENGTH; ++i)
	{
		ship[i] = true;
	}
}

Ship::Ship(ShipData d) : data(d)
{
	Ship();
}

Ship::~Ship()
{
}

int Ship::Length()
{
	return data.length;
}

int Ship::TopLeftRow()
{
	return data.topLeftRow;
}

int Ship::TopLeftColumn()
{
	return data.topLeftColumn;
}

E_DIRECTION Ship::Direction()
{
	return data.direction;
}

bool Ship::Hit(CellData c)
{
	bool success = true;

	// one deck ship or a head of the ship
	if (c.row == TopLeftRow() && c.column == TopLeftColumn())
	{
		success = ship[0];
		ship[0] = false;
		return success;
	}

	if (c.row == TopLeftRow())
	{
		switch (Direction())
		{
			case HORIZONTAL:
			{
				if ( (TopLeftColumn() < c.column) && (c.column < (TopLeftColumn() + Length())) )
				{
					success = ship[c.column - TopLeftColumn()];
					ship[c.column - TopLeftColumn()] = false;
					return success;
				}
			}
			case VERTICAL:
			{
				return false;
			}
		}
	}

	if (c.column == TopLeftColumn())
	{
		switch (Direction())
		{
			case HORIZONTAL:
			{
				return false;
			}
			case VERTICAL:
			{
				if ( (TopLeftRow() < c.row) && (c.row < TopLeftRow() + Length()) )
				{
					success = ship[c.row - TopLeftRow()];
					ship[c.row - TopLeftRow()] = false;
					return success;
				}
			}
		}
	}

	return false;
}

bool Ship::IsRuined()
{
	bool ruined = true;

	for (int i = 0; i < Length(); ++i)
	{
		ruined = (ruined && !ship[i]);
	}

	return ruined;
}