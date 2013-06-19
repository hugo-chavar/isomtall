#include "GameView.h"
#include "Grenade.h"
#include "Logger.h"
#include "../Common/StringUtilities.h"

Grenade::Grenade() {
	this->setName("Grenade");
	this->setAmmunitionType(HAND_GRENADE);
	this->setStatus(EXPLOSIVE_INACTIVE);
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
		if ((!this->isTargetReached())&&(this->couldContinue()))
			Movable::update();
		else {
			this->setStatus(EXPLOSIVE_EXPLOSION_COUNTDOWN);
			this->startCountDown(5); //tarda 5 segundos en exlotar
		}
	} else {

		if (this->getStatus() == EXPLOSIVE_EXPLOSION_COUNTDOWN) {
			this->decreaseEndStatusTime();
			common::Logger::instance().log("this->endStatusTime: " + stringUtilities::unsignedToString(static_cast<unsigned>(this->endStatusTime)));
			if (this->endStatusTime == 0) {
				this->setStatus(EXPLOSIVE_EXPLOSION);
				//this->startCountDown(2); //tarda 2 segundos en mostrar sprite de explosion

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
		
void Grenade::startCountDown(float seconds) {
	
	this->setEndStatusTime(seconds);
}