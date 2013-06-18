#ifndef _GRENADE_H_
#define _GRENADE_H_

#include "ImpactAmmo.h"
#include "Daniable.h"


class Grenade: public ImpactAmmo {

protected:

public:
	Grenade();
	~Grenade();
	void impact(Daniable* daniable);
};


#endif // _GRENADE_H_