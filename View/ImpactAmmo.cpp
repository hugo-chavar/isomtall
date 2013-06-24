#include "ImpactAmmo.h"
#include "GameView.h"
#include "Logger.h"
#include "../Common/StringUtilities.h"

#define TOLERANCE 0.35

ImpactAmmo::ImpactAmmo():Ammunition() {
}

ImpactAmmo::~ImpactAmmo(){
}

void ImpactAmmo::verify() {
	Movable::verify();
	this->impact(GameView::instance().getDaniableInTile(this->getCurrentTile()));
	if (!this->isAlive())
		this->setAvailable(true);
}

void ImpactAmmo::setRange(int range) {
	this->range = range;
}

void ImpactAmmo::setPrecision(float precision) {
	this->precision = precision;
}

int ImpactAmmo::getRange() {
	return (this->range);
}

float ImpactAmmo::getPrecision() {
	return (this->precision);
}

bool ImpactAmmo::canHit(){
	float precision = Game::instance().getRandom();
	float recorrido = (float)this->getTileCount()*100/(float)this->getRange();
	this->resetTileCount();
	precision = (precision*((float)TOLERANCE)*(100-recorrido)/100) + precision*(1-((float)TOLERANCE));
	if (precision >= this->getPrecision()) {
		return true;
	}
	return false;
}

void ImpactAmmo::deserialize(std::string in) {
	std::vector<std::string> splittedIn;
	stringUtilities::splitString(in,splittedIn,'?');

	this->setName(splittedIn[0]);
	this->setAmmoID(splittedIn[1]);
	this->positionFromString(splittedIn[2]);
	this->directionFromString(splittedIn[3]);
	this->setCouldContinue(splittedIn[4] == "A");
}

std::string ImpactAmmo::serialize() {
	std::string out = this->getName();
	out.append("?");
	out.append(this->getAmmoId());
	out.append("?");
	out.append(this->positionToString());
	out.append("?");
	out.append(this->directionToString());
	out.append("?");
	if (this->isAlive())
		out.append("A");
	else
		out.append("D");
	return out;
}