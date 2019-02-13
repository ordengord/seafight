#include "battleFieldUI.h"

class UI
{
private:
	BattleFieldUI *myField, *enemyField;
public:
	UI();
	~UI();

	void DisplayGreeting();
	void DisplayMessage(char *m);
	bool GetNewShipData(ShipData &s);
	bool GetCellToAttack(CellData &c);
	void DisplayNewShip(ShipData s);
	void DisplayEnemyFieldHit(CellData c);
	void DisplayEnemyFieldMiss(CellData c);
	void DisplayMyFieldHit(CellData c);
	void DisplayMyFieldMiss(CellData c);
	void DisplayFields();
};