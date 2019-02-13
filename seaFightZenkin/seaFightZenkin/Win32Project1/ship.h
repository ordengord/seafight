#include "common.h"

class Ship
{
private:
	ShipData data;
	bool ship[MAX_LENGTH];
public:
	Ship();
	Ship(ShipData d);
	~Ship();

	int Length();
	int TopLeftRow();
	int TopLeftColumn();
	E_DIRECTION Direction();

	bool Hit(CellData c);
	bool IsRuined();
};