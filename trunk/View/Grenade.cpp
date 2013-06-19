#include "GameView.h"
#include "Grenade.h"

Grenade::Grenade() {
	this->setName("Grenade");
	this->setAmmunitionType(HAND_GRENADE);
	this->setStatus(EXPLOSIVE_INACTIVE);
	//this->setDamage(50.0);
	this->setSprite(this->getSpriteWithName(this->getName()));
}

Grenade::~Grenade() {
}

bool Grenade::isAlive() {
	return (this->getStatus() != EXPLOSIVE_DUST_IN_THE_WIND);
}

void Grenade::update() {
	if (this->getStatus() == EXPLOSIVE_FLYING) {
		Movable::verify();
		if (!this->isTargetReached())
			Movable::update();
		else {
			this->setStatus(EXPLOSIVE_EXPLOSION_COUNTDOWN);
			this->startCountDown(5); //tarda 5 segundos en exlotar
		}
	} else {

		if (this->getStatus() == EXPLOSIVE_EXPLOSION_COUNTDOWN) {
			//tic tac tic tac
			//TODO: decrease time and manage bomb blast
			this->decreaseEndStatusTime();
			if (this->endStatusTime == 0) {
				this->setStatus(EXPLOSIVE_EXPLOSION);
				this->startCountDown(2); //tarda 2 segundos en mostrar sprite de explosion

			}
		} else {
			if (this->getStatus() == EXPLOSIVE_EXPLOSION) {
				this->decreaseEndStatusTime();
				if (this->endStatusTime == 0)
					this->setStatus(EXPLOSIVE_DUST_IN_THE_WIND);
			}
		}
	}
}
		
void Grenade::startCountDown(unsigned seconds) {
	
	this->setEndStatusTime(static_cast<Uint32>(seconds*1000));
}