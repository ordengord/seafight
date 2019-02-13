#include "playerHuman.h"
#include "playerAI.h"

class Game
{
private:
    Player *p1, *p2;
public:
	Game();
	Game(Player *a, Player *b);
	~Game();

	bool Init();
	void Play();
};