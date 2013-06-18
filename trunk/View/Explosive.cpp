#include "Explosive.h"
#include "GameView.h"
#include "Logger.h"
#include "../Common/StringUtilities.h"

Explosive::Explosive():Ammunition() {
}

Explosive::~Explosive(){
}

//void Explosive::verify() {
//	//common::Logger::instance().log("Ammo pos tile: " + stringUtilities::pairIntToString(this->getCurrentTile()));
//	//common::Logger::instance().log("Ammo pos pixel: " + this->positionToString());
//	this->impact(GameView::instance().getDaniableInTile(this->getCurrentTile()));
//	if (!this->isAlive())
//		this->setAvailable(true);
//}