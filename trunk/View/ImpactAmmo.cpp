#include "ImpactAmmo.h"
#include "GameView.h"
#include "Logger.h"
#include "../Common/StringUtilities.h"

ImpactAmmo::ImpactAmmo():Ammunition() {
}

ImpactAmmo::~ImpactAmmo(){
}

void ImpactAmmo::verify() {
	Movable::verify();
	//common::Logger::instance().log("Ammo pos tile: " + stringUtilities::pairIntToString(this->getCurrentTile()));
	//common::Logger::instance().log("Ammo pos pixel: " + this->positionToString());
	this->impact(GameView::instance().getDaniableInTile(this->getCurrentTile()));
	if (!this->isAlive())
		this->setAvailable(true);
}

void ImpactAmmo::deserialize(std::string in) {
	std::vector<std::string> splittedIn;
	stringUtilities::splitString(in,splittedIn,';');

	this->setName(splittedIn[0]);
	this->setAmmoID(splittedIn[1]);
	this->positionFromString(splittedIn[2]);
}

std::string ImpactAmmo::serialize() {
	std::string out = this->getName();
	out.append(";");
	out.append(this->getAmmoId());
	out.append(";");
	out.append(this->positionToString());
	return out;
}