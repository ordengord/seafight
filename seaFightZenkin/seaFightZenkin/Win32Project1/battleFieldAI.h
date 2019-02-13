#include "common.h"

class BattleFieldAI
{
private:
	bool field[FIELD_SIZE][FIELD_SIZE];
	int availableCellsCount;
public:
	BattleFieldAI();
	~BattleFieldAI();

	void Reset();
	int GetAvailableCellsCount();
	void GetAvailableCellByPosition(int position, CellData &c);

	bool GetCellValue(CellData c);
	void UpdateCell(CellData c);
	void UpdateField(ShipData s);
};