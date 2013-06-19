#include "GameView.h"
#include "Grenade.h"

Grenade::Grenade() {
	this->setName("Grenade");
	this->setAmmunitionType(HAND_GRENADE);
	//this->setDamage(50.0);
	this->setSprite(this->getSpriteWithName(this->getName()));
}

Grenade::~Grenade() {
}

bool Grenade::isAlive() {
	return (!this->exploded);
}

void Grenade::update() {
	Movable::verify();
	if (!this->isTargetReached())
		Movable::update();
}