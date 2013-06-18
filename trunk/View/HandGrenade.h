#ifndef _HANDGRENADE_H_
#define _HANDGRENADE_H_

#ifndef HANDGRENADE_POOL_SIZE
#define HANDGRENADE_POOL_SIZE 5
#endif//HANDGRENADE_POOL_SIZE

#include "Grenade.h"
#include "Weapon.h"


class HandGrenade: public Weapon {

public:
	HandGrenade();
	~HandGrenade();
	void strike(Daniable* target);
	std::vector<Grenade*>& getGrenades();
	Grenade* getAvailableGrenade();
	unsigned getAmmo();
	void setAmmo(unsigned ammo);

private:
	std::vector<Grenade*> grenades;
	unsigned ammo;
	unsigned nextGrenadeIndex;
	unsigned getNextGrenadeIndex();
	void setNextGrenadeIndex(unsigned value);
};


#endif // _HANDGRENADE_H_