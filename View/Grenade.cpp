#include "GameView.h"
#include "Grenade.h"
#include "Logger.h"
#include "../Common/StringUtilities.h"

Grenade::Grenade() {
	this->setName("Grenade");
	this->setAmmunitionType(HAND_GRENADE);
	this->setStatus(EXPLOSIVE_INACTIVE);
	this->setSprite(this->getSpriteWithName(this->getName()));
	explosionSprite = (SpriteAnimado*)this->getSpriteWithName("redexplosion");
}

Grenade::~Grenade() {
}

bool Grenade::isAlive() {
	return (this->getStatus() != EXPLOSIVE_DUST_IN_THE_WIND);
}

void Grenade::update() {
	switch (this->getStatus()){
		case EXPLOSIVE_FLYING: {
			Movable::verify();
			if ((!this->isTargetReached())&&(this->couldContinue()))
				Movable::update();
			else {
				this->setTargetTile(this->getLastTile());
				this->setStatus(EXPLOSIVE_BOUNCING);
				this->setTargetReached(false);
				this->setCouldContinue(true);
				this->changeToOppositeDirection();
				//this->setStatus(EXPLOSIVE_EXPLOSION_COUNTDOWN);
				//this->startCountDown(5); //tarda 5 segundos en exlotar
			}
			break;
		}
		
		case EXPLOSIVE_BOUNCING: {
			int x, y;
			this->setCurrentTile(this->getCurrentTile() + this->getDirection());
			x = this->getTileWidth()*(this->getCurrentTile().first - this->getCurrentTile().second)/2 - this->getSprite()->relatx();
			y = this->getTileHeight()*(this->getCurrentTile().first + this->getCurrentTile().second)/2 - this->getSprite()->relaty();
			this->setPosition(std::make_pair(x, y));
			//this->setRectangle(this->getInitialTile(),this->getSprite());
			//this->updateRectanglePosition(,)
			//this->setBouncing(true);
			//if ((!this->isTargetReached())&&(this->couldContinue())) {
			//	Movable::update();
			//	Movable::verify();
			//}
			//else {
				this->setStatus(EXPLOSIVE_EXPLOSION_COUNTDOWN);
				this->startCountDown(5); //tarda 5 segundos en exlotar
			//}
		}
		break;
		case EXPLOSIVE_EXPLOSION_COUNTDOWN: {
			this->decreaseEndStatusTime();
			//common::Logger::instance().log("this->endStatusTime: " + stringUtilities::unsignedToString(static_cast<unsigned>(this->endStatusTime)));
			if (this->endStatusTime == 0)
				this->setStatus(EXPLOSIVE_EXPLOSION);
			break;
		}
		case EXPLOSIVE_EXPLOSION: {
			this->setStatus(EXPLOSIVE_BURNING);
			break;
		}
		case EXPLOSIVE_BURNING: {
				this->decreaseEndStatusTime();
				if (this->endStatusTime == 0) // EN REALIDAD HAY QUE PREGUNTAR SI MOSTRO TODA LA ANIMACION DEL SPRITE
					this->setStatus(EXPLOSIVE_DUST_IN_THE_WIND);
				break;
		}
	}

	//if (this->getStatus() == EXPLOSIVE_FLYING) {
	//	Movable::verify();
	//	if ((!this->isTargetReached())&&(this->couldContinue()))
	//		Movable::update();
	//	else {
	//		this->setTargetTile(this->getLastTile());
	//		this->setStatus(EXPLOSIVE_BOUNCING);
	//		this->setTargetReached(false);
	//		this->setCouldContinue(true);
	//		this->changeToOppositeDirection();
	//		//this->setStatus(EXPLOSIVE_EXPLOSION_COUNTDOWN);
	//		//this->startCountDown(5); //tarda 5 segundos en exlotar
	//	}
	//} else {

	//	if (this->getStatus() == EXPLOSIVE_EXPLOSION_COUNTDOWN) {
	//		this->decreaseEndStatusTime();
	//		//common::Logger::instance().log("this->endStatusTime: " + stringUtilities::unsignedToString(static_cast<unsigned>(this->endStatusTime)));
	//		if (this->endStatusTime == 0) {
	//			this->setStatus(EXPLOSIVE_EXPLOSION);
	//			

	//		}
	//	} else {
	//		if (this->getStatus() == EXPLOSIVE_EXPLOSION) {
	//			//MANEJAR EXPLOSION
	//			this->setStatus(EXPLOSIVE_BURNING);
	//			//CAMBIAR A SPRITE DE FUEGO
	//			this->startCountDown(2); //tarda 2 segundos en mostrar sprite de explosion

	//		} else 	if (this->getStatus() == EXPLOSIVE_BURNING) {
	//			this->decreaseEndStatusTime();
	//			if (this->endStatusTime == 0) // EN REALIDAD HAY QUE PREGUNTAR SI MOSTRO TODA LA ANIMACION DEL SPRITE
	//				this->setStatus(EXPLOSIVE_DUST_IN_THE_WIND);
	//		}
	//	}
	//}
}
		
void Grenade::startCountDown(float seconds) {
	
	this->setEndStatusTime(seconds);
}