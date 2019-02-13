#include "BattleFieldAI.h"
#include "common.h"

class AI
{
private:
	BattleFieldAI *aiField;

	ShipData damagedShip;

	int enemyShips[SHIP_TYPE_COUNT];
	int enemyShipMaxRemainingLength;
public:
	AI();
	~AI();

	void ResetField();
	void GenerateShip(ShipData &s);
	void UpdateField(ShipData s);

	bool IsShipDamaged();
	void DestroyDamagedShip();
	void UpdateEnemyShipMaxRemainingLength();

	bool GetDamagedShipOption(CellData &c);
	void GetCellToAttack(CellData &c);
	void ProcessHit(CellData c);
	void ProcessMiss(CellData c);
};