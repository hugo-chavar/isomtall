#ifndef _AMMUNITION_POOL_H_
#define _AMMUNITION_POOL_H_

#include "Ammunition.h"
#include <vector>
#include "Arrow.h"
#include "Grenade.h"

#define NUMBERAMMUNITIONS 5


class AmmunitionPool {

public:
	AmmunitionPool();
	~AmmunitionPool();
	Arrow* getAvailableArrow();
	Grenade* getAvailableGrenade();
	void deserialize(string argument);
	bool ammoIDIsInPlay(string name, string id);

private:
	std::vector<Arrow*> arrows;
	std::vector<Grenade*> grenades;

	unsigned nextArrowIndex;
	unsigned getNextArrowIndex();
	void setNextArrowIndex(unsigned value);

	unsigned nextGrenadeIndex;
	unsigned getNextGrenadeIndex();
	void setNextGrenadeIndex(unsigned value);

};


#endif // _AMMUNITION_POOL_H_