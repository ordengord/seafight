#include "player.h"
#include "ui.h"

class PlayerHuman : public Player
{
private:
    UI *ui;
public:
	PlayerHuman();
	~PlayerHuman();

	bool Init();

	bool AttackCell(CellData &c);
	bool IsHit(CellData c);
	void ProcessResult(CellData c, bool isHit);

	void Win();
	void Lose();
};