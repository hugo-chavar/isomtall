#ifndef _WEAPON_ICE_INCANTATOR_H_
#define _WEAPON_ICE_INCANTATOR_H_

#ifndef ICE_INCANTATOR_POOL_SIZE
#define ICE_INCANTATOR_POOL_SIZE 5
#endif//ICE_INCANTATOR_POOL_SIZE

#include "IceIncantation.h"
#include "Weapon.h"

class WeaponIceIncantator: public Weapon {

public:
	WeaponIceIncantator();
	~WeaponIceIncantator();
	void strike(Daniable* target);
	std::vector<IceIncantation*>& getIceIncantations();
	IceIncantation* getAvailableIceIncantation();
	unsigned getAmmo();
	void setAmmo(unsigned ammo);
private:
	std::vector<IceIncantation*> iceIncantations;
	unsigned ammo;
	unsigned nextIceIncantationIndex;
	unsigned getNextIceIncantationIndex();
	void setNextIceIncantationIndex(unsigned value);
};

#endif // _WEAPON_ICE_INCANTATOR_H_