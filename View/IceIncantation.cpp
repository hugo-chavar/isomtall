#include "GameView.h"
#include "IceIncantation.h"

IceIncantation::IceIncantation():ImpactAmmo() {
	this->setName("IceIncantation");
	this->setAmmunitionType(IMPACT_AMMO);
	//this->setDamage(50.0);
	this->setSprite(this->getSpriteWithName(this->getName()));
}

IceIncantation::~IceIncantation() {
}

void IceIncantation::impact(Daniable* daniable) {
	if (daniable) {
		//this->impact(static_cast<Personaje>daniable);
		this->setTargetReached(true);
		this->setAvailable(true);
	}
}

void IceIncantation::impact(Entity* entity) {
	if (entity) {
		entity->iceUp(5);
		this->setTargetReached(true);
		this->setAvailable(true);
	}
}