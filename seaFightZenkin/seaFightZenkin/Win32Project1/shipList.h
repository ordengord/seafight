#include "ship.h"
#include <list>

using namespace std;

class ShipList
{
private:
	list<Ship> shipList;
public:
	ShipList();
	~ShipList();

	bool isNewShipLengthValid(int length);
	bool isNewShipLocationValid(ShipData s);

	void PushNewShip(ShipData s);

	bool Full();
	bool Empty();

	bool Hit(CellData c);
};