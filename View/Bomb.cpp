#include "GameView.h"
#include "Bomb.h"

Bomb::Bomb() {
	this->setName("Bomb");
	this->setAmmunitionType(HAND_GRENADE);
	this->setStatus(EXPLOSIVE_INACTIVE);
	//this->setDamage(50.0);
	this->setSprite(this->getSpriteWithName(this->getName()));
}

Bomb::~Bomb() {
}

bool Bomb::isAlive() {
	return (this->getStatus() != EXPLOSIVE_DUST_IN_THE_WIND);
}

void Bomb::update() {

}