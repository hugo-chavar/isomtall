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