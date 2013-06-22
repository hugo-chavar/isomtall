#include "GameView.h"
#include "Arrow.h"

Arrow::Arrow():ImpactAmmo() {
	this->setName("Arrow");
	this->setAmmunitionType(IMPACT_AMMO);
	//this->setDamage(50.0);
	this->setSprite(this->getSpriteWithName(this->getName()));
}

Arrow::~Arrow() {
}

void Arrow::impact(Daniable* daniable) {
	if (daniable) {
		if(daniable->isWood())
			GameView::instance().getGameSounds().playSoundEffect(SOUND_INDEX_ATTACK_ON_WOOD);
		else
			GameView::instance().getGameSounds().playSoundEffect(SOUND_INDEX_ATTACK_ON_SHIELD);
		daniable->recibirDano(this->getDamage());
		this->setTargetReached(true);
		this->setAvailable(true);
		if (!(daniable->isAlive()))
			GameView::instance().getMission()->missionUpdate(daniable, this->getOwner());
	}
}
//
//void Arrow::deserialize(std::string in) {
//	std::vector<std::string> splittedIn;
//	stringUtilities::splitString(in,splittedIn,';');
//
//	this->setName(splittedIn[0]);
//	this->setAmmoID(splittedIn[1]);
//	this->positionFromString(splittedIn[2]);
//}
//
//std::string Arrow::serialize() {
//	std::string out = this->getName();
//	out.append(";");
//	out.append(this->getAmmoId());
//	out.append(";");
//	out.append(this->positionToString());
//	return out;
//}