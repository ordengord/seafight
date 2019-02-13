#include "shipList.h"
#include <iterator>

using namespace std;

ShipList::ShipList()
{
}

ShipList::~ShipList()
{
	shipList.clear();
}

bool ShipList::isNewShipLengthValid(int length)
{
	int maxCountForTheLength = MAX_LENGTH - length + 1;
	int currentCount = 0;

	for (list<Ship>::iterator it = shipList.begin(); it != shipList.end(); ++it)
	{
		if (it->Length() == length)
		{
			++currentCount;
		}
	}

	return (currentCount < maxCountForTheLength);
}

bool ShipList::isNewShipLocationValid(ShipData s)
{
	for (list<Ship>::iterator it = shipList.begin(); it != shipList.end(); ++it)
	{
		// both ships are horizontal
		if ((s.direction == HORIZONTAL) && (it->Direction() != VERTICAL) ||
			(it->Direction() == HORIZONTAL) && (s.direction != VERTICAL))
		{
			// new ship is above or below more than one row from current, ok
			if ((s.topLeftRow > (it->TopLeftRow() + 1)) || (s.topLeftRow < (it->TopLeftRow() - 1)))
			{
				continue;
			}

			// the row of the new ship is adjacent or the same with the current one
			// but the new ship is enough to the left, ok
			if ((s.topLeftColumn < it->TopLeftColumn()) && ((it->TopLeftColumn() - s.topLeftColumn) > s.length))
			{
				continue;
			}

			// the row of the new ship is adjacent or the same with the current one
			// but the new ship is enough to the right, ok
			if ((s.topLeftColumn > it->TopLeftColumn()) && ((s.topLeftColumn - it->TopLeftColumn()) > it->Length()))
			{
				continue;
			}

			// otherwise
			return false;
		}

		// both ships are vertical
		if ((s.direction == VERTICAL) && (it->Direction() != HORIZONTAL) ||
			(it->Direction() == VERTICAL) && (s.direction != HORIZONTAL))
		{
			// the new ship is more than one column to the left or to the right of the current, ok
			if ((s.topLeftColumn < (it->TopLeftColumn() - 1)) || (s.topLeftColumn > (it->TopLeftColumn() + 1)))
			{
				continue;
			}

			// the column is the same or they are adjacent
			// but the new ship is safe above the current, ok
			if ((s.topLeftRow < it->TopLeftRow()) && ((it->TopLeftRow() - s.topLeftRow) > s.length))
			{
				continue;
			}

			// the column is the same or they are adjacent
			// but the new ship is safe below the current, ok
			if ((s.topLeftRow > it->TopLeftRow()) && ((s.topLeftRow - it->TopLeftRow()) > it->Length()))
			{
				continue;
			}

			// otherwise
			return false;
		}

		// new ship is horizontal, current ship is vertical
		if ((s.direction != VERTICAL) && (it->Direction() != HORIZONTAL))
		{
			// new ship is more than one row above the start of the current ship
			// or is more than one row below its end, ok
			if ((s.topLeftRow < (it->TopLeftRow() - 1)) || (s.topLeftRow > (it->TopLeftRow() + it->Length())))
			{
				continue;
			}

			// current ship is more than one column to the left from the start of the new ship
			// or is more than one column to the right of its end, ok
			if ((it->TopLeftColumn() < (s.topLeftColumn - 1)) || (it->TopLeftColumn() > (s.topLeftColumn + s.length)))
			{
				continue;
			}

			// otherwise
			return false;
		}

		// new ship is vertical and current ship is horizontal
		if ((s.direction != HORIZONTAL) && (it->Direction() != VERTICAL))
		{
			// new ship is more than one column to the left from the start of the current ship
			// or is more than one column to the right of its end, ok
			if ((s.topLeftColumn < (it->TopLeftColumn() - 1)) || (s.topLeftColumn > (it->TopLeftColumn() + it->Length())))
			{
				continue;
			}

			// current ship is more than one row above the start of the new ship
			// or is more than one row below its end, ok
			if ((it->TopLeftRow() < (s.topLeftRow - 1)) || (it->TopLeftRow() > (s.topLeftRow + s.length)))
			{
				continue;
			}

			//otherwise
			return false;
		}
	}

	return true;
}

void ShipList::PushNewShip(ShipData s)
{
	shipList.push_back(Ship(s));
}

bool ShipList::Full()
{
	return (shipList.size() >= MAX_SHIP_COUNT);
}

bool ShipList::Empty()
{
	return shipList.empty();
}

bool ShipList::Hit(CellData c)
{
	for (list<Ship>::iterator it = shipList.begin(); it != shipList.end(); ++it)
	{
		if (it->Hit(c))
		{
			if (it->IsRuined())
			{
				shipList.erase(it);
			}
			return true;
		}
	}

	return false;
}