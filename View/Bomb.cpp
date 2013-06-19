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

//void Grenade::impact(Daniable* daniable) {
//	if (daniable) {
//		daniable->recibirDano(this->getDamage());
//		this->setTargetReached(true);
//		this->setAvailable(true);
//		if (!(daniable->isAlive()))
//			GameView::instance().getMission()->missionUpdate(daniable, this->getOwner());
//	}
//}