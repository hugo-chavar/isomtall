#include "Ammunition.h"

Ammunition::Ammunition( ) {
	this->owner = "";
}

Ammunition::~Ammunition() {
}


std::string Ammunition::getOwner() {
	return this->owner;
}

void Ammunition::setOwner(std::string value) {
	this->owner = value;
}

unsigned Ammunition::getAmmunitionType() {
	return this->ammunitionType;
}

void Ammunition::setAmmunitionType(unsigned value) {
	this->ammunitionType = value;
}