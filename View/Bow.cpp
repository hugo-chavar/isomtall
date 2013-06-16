#include "Bow.h"
#include "Arrow.h"

Bow::Bow() {
	
	Arrow* arrow = NULL;
	for (unsigned int i = 0; i < PROJECTILE_POOL_SIZE; i++) {
		arrow = new Arrow();
		this->getProjectiles().push_back(arrow);
	}
}

Bow::~Bow() {
}

void Bow::strike(Daniable* target) {
	Arrow* arrow = NULL;

	if (this->getAmmo() > 0) {
		arrow = (Arrow *)this->getAvailableProjectile();
		if (arrow != NULL) {
			arrow->setTargetTile(target->getPosition());
			arrow->setDamage(this->getDamage());
			//put projectile into simulation entities list.
		}
	}
}
