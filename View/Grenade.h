#ifndef _GRENADE_H_
#define _GRENADE_H_

#include "Movable.h"
#include "Daniable.h"
#include "Explosive.h"

class Grenade: public Movable, public Explosive {

protected:

public:
	Grenade();
	~Grenade();
	bool isAlive();
	void update();
};


#endif // _GRENADE_H_