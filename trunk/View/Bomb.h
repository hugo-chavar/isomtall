#ifndef _BOMB_H_
#define _BOMB_H_

#include "Movable.h"
#include "Daniable.h"
#include "Explosive.h"

class Bomb: public Entity, public Explosive, public Positionable {

protected:

public:
	Bomb();
	~Bomb();
	bool isAlive();
	void update();
	void startCountDown(unsigned seconds);
};


#endif // _BOMB_H_