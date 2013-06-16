#ifndef _PROJECTILE_WEAPON_H_
#define _PROJECTILE_WEAPON_H_

#ifndef PROJECTILE_POOL_SIZE
#define PROJECTILE_POOL_SIZE 5
#endif//PROJECTILE_POOL_SIZE

#include "Weapon.h"
#include <vector>
#include "ImpactAmmo.h"


class ProjectileWeapon : public Weapon {
private:
	unsigned int ammo;
	std::vector<ImpactAmmo*> projectiles;
	unsigned int nextProjectileIndex;
	
	unsigned int getNextProjectileIndex();
	void setNextProjectileIndex(unsigned int nextProjectileIndex);

protected:
	ImpactAmmo* getAvailableProjectile();

public:
	ProjectileWeapon();
	virtual ~ProjectileWeapon();
	unsigned int getAmmo();
	void setAmmo(unsigned int ammo);
	virtual void strike(Daniable* target) = 0;
	std::vector<ImpactAmmo*>& getProjectiles();

};



#endif // _PROJECTILE_WEAPON_H_