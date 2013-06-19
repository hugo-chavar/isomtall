#include "GameView.h"
#include "Bomb.h"

Bomb::Bomb() {
	this->setName("Bomb");
	this->setAmmunitionType(HAND_GRENADE);
	this->setStatus(EXPLOSIVE_INACTIVE);
	this->setSprite(this->getSpriteWithName(this->getName()));
	explosionSprite = static_cast<SpriteAnimado*>(this->getSpriteWithName("redexplosion"));
}

Bomb::~Bomb() {
}

bool Bomb::isAlive() {
	return (this->getStatus() != EXPLOSIVE_DUST_IN_THE_WIND);
}

void Bomb::update() {

}
		
void Bomb::startCountDown(float seconds) {
	this->setStatus(EXPLOSIVE_EXPLOSION_COUNTDOWN);
	this->setEndStatusTime(seconds);
}