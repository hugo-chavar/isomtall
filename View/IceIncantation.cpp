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
		daniable->iceUp(5);
		this->setTargetReached(true);
		this->setAvailable(true);
	}
}
//
//void IceIncantation::deserialize(std::string in) {
//	std::vector<std::string> splittedIn;
//	stringUtilities::splitString(in,splittedIn,';');
//
//	this->setName(splittedIn[0]);
//	this->setAmmoID(splittedIn[1]);
//	this->positionFromString(splittedIn[2]);
//}
//
//std::string IceIncantation::serialize() {
//	std::string out = this->getName();
//	out.append(";");
//	out.append(this->getAmmoId());
//	out.append(";");
//	out.append(this->positionToString());
//	return out;
//}
