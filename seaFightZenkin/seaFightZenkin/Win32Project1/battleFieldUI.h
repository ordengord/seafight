#include "common.h"

const char DEFAULT_CHAR = '0';
const char SHIP_CHAR = '+';
const char HIT_CHAR = 'x';
const char MISS_CHAR = '-';

class BattleFieldUI
{
private:
	char field[FIELD_SIZE][FIELD_SIZE];
public:
	BattleFieldUI();
	~BattleFieldUI();

	void Display();
	void DisplayNewShip(ShipData s);
	void DisplayHit(CellData c);
	void DisplayMiss(CellData c);
};