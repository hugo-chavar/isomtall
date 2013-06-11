#include "Directionable.h"
#include "StringUtilities.h"

Directionable::Directionable() {
	this->direction = std::make_pair(0, 0);
}

Directionable::~Directionable() {
}

const std::pair<int, int> Directionable::DIRECTION_N = std::make_pair<int, int>(0,1);

std::pair<int, int> Directionable::getDirection() {
	return this->direction;
}

void Directionable::setDirection(std::pair<int, int> dir) {
	this->direction = dir;
}

std::string Directionable::directionToString() {
	return stringUtilities::pairIntToString(this->getDirection());
}

void Directionable::directionFromString(std::string stringPosition) {
	this->setDirection(stringUtilities::stringToPairInt(stringPosition));
}