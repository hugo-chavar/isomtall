#include "Arrow.h"

Arrow::Arrow():ImpactAmmo() {
	this->setName("Arrow");
	this->setAmmunitionType(ARROW);
	this->setDamage(50.0);
}

Arrow::~Arrow() {
}

void Arrow::impact(Daniable* daniable) {
	if (daniable) {
		daniable->recibirDano(this->getDamage());
		this->setTargetReached(true);
	}
}