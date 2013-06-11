#include "Positionable.h"
#include "StringUtilities.h"

Positionable::Positionable() {
	this->position = std::make_pair(0, 0);
}

Positionable::~Positionable() {
}

std::pair<int, int> Positionable::getPosition() {
	return this->position;
}

void Positionable::setPosition(std::pair<int, int> pos) {
	this->position = pos;
}

std::string Positionable::positionToString() {
	return stringUtilities::pairIntToString(this->getPosition());
}

void Positionable::positionFromString(std::string stringPosition) {
	this->setPosition(stringUtilities::stringToPairInt(stringPosition));
}