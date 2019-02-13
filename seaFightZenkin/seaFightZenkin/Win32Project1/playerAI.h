#include "player.h"
#include "ai.h"

class PlayerAI : public Player
{
private:
	AI *ai;
public:
	PlayerAI();
	~PlayerAI();

	bool Init();

	bool AttackCell(CellData &c);
	bool IsHit(CellData c);
	void ProcessResult(CellData c, bool isHit);
};