#ifndef PLAYER_H
#define PLAYER_H

#include <MDGFW/Entity.h>

class Player : public Entity
{
public:
	Player();
	virtual ~Player();
	void Update();
private:

};

#endif // !PLAYER_H
