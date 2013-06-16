#include "ProjectileWeapon.h"

ProjectileWeapon::ProjectileWeapon() {
	this->ammo = 0;
	this->nextProjectileIndex = 0;

}

std::vector<ImpactAmmo*>& ProjectileWeapon::getProjectiles() {
	return this->projectiles;
}

unsigned int ProjectileWeapon::getNextProjectileIndex() {
	return this->nextProjectileIndex;
}

void ProjectileWeapon::setNextProjectileIndex(unsigned int availableProjectileIndex) {
	this->nextProjectileIndex = availableProjectileIndex;
}

ImpactAmmo* ProjectileWeapon::getAvailableProjectile() {
	ImpactAmmo* projectile = NULL;
	bool found = false;
	unsigned int i = this->getNextProjectileIndex();

	do {
		projectile = this->getProjectiles()[i];

		if (projectile->isAvailable()) {
			found = true;
			projectile->setAvailable(false);
		}

		if (i < PROJECTILE_POOL_SIZE)
			i++;
		else
			i = 0;
	} while (!found && i != this->getNextProjectileIndex());

	if (!found)
		projectile = NULL; //TODO: LOG SOME WARNING.

	this->setNextProjectileIndex(i);

	return projectile;
}

unsigned int ProjectileWeapon::getAmmo() {
	return this->ammo;
}

void ProjectileWeapon::setAmmo(unsigned int ammo) {
	this->ammo = ammo;
}

ProjectileWeapon::~ProjectileWeapon() {
	for (unsigned int i = 0; i < PROJECTILE_POOL_SIZE; i++) {
		delete this->getProjectiles()[i];
	}
}