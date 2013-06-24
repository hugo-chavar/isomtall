#ifndef _AMMUNITION_POOL_H_
#define _AMMUNITION_POOL_H_

#include "Ammunition.h"
#include <vector>
#include "Arrow.h"
#include "Grenade.h"
#include "Bomb.h"
#include "IceIncantation.h"
#include "IceBomb.h"

#define NUMBERAMMUNITIONS 5


class AmmunitionPool {

public:
	AmmunitionPool();
	~AmmunitionPool();
	Arrow* getAvailableArrow();
	Grenade* getAvailableGrenade();
	IceIncantation* getAvailableIceIncantation();
	Bomb* getAvailableBomb();
	IceBomb* getAvailableIceBomb();
	void deserialize(string argument);
	bool ammoIDIsInPlay(string name, string id);

private:
	std::vector<Arrow*> arrows;
	std::vector<Grenade*> grenades;
	std::vector<IceIncantation*> iceIncantations;
	std::vector<Bomb*> bombs;
	std::vector<IceBomb*> iceBombs;

	unsigned nextArrowIndex;
	unsigned getNextArrowIndex();
	void setNextArrowIndex(unsigned value);

	unsigned nextGrenadeIndex;
	unsigned getNextGrenadeIndex();
	void setNextGrenadeIndex(unsigned value);

	unsigned nextIceIncantationIndex;
	unsigned getNextIceIncantationIndex();
	void setNextIceIncantationIndex(unsigned value);

	unsigned nextBombIndex;
	unsigned getNextBombIndex();
	void setNextBombIndex(unsigned value);

	unsigned nextIceBombIndex;
	unsigned getNextIceBombIndex();
	void setNextIceBombIndex(unsigned value);

};


#endif // _AMMUNITION_POOL_H_