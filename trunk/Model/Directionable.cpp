#include "Directionable.h"
#include "StringUtilities.h"
#include "DataTypes.h"


const std::pair<int, int> Directionable::DIRECTION_N = std::make_pair<int, int>(-1,-1);
const std::pair<int, int> Directionable::DIRECTION_S = std::make_pair<int, int>(1,1);
const std::pair<int, int> Directionable::DIRECTION_NE = std::make_pair<int, int>(0,-1);
const std::pair<int, int> Directionable::DIRECTION_E = std::make_pair<int, int>(1,-1);
const std::pair<int, int> Directionable::DIRECTION_SE = std::make_pair<int, int>(1,0);
const std::pair<int, int> Directionable::DIRECTION_O = std::make_pair<int, int>(-1,1);
const std::pair<int, int> Directionable::DIRECTION_NO = std::make_pair<int, int>(-1,0);
const std::pair<int, int> Directionable::DIRECTION_SO = std::make_pair<int, int>(0,1);
const std::pair<int, int> Directionable::DIRECTION_Q = std::make_pair<int, int>(0,0);

const std::map<std::pair<int, int>, std::pair<int, int> > Directionable::TRANSFORM_TILE_TO_PIXEL_DIRECTION  =  Directionable::create_map();

Directionable::Directionable() {
	this->direction = Directionable::DIRECTION_Q;
}

Directionable::~Directionable() {
}

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

void Directionable::setDirection(std::pair<int, int> from, std::pair<int, int> to) {
	this->setDirection(this->calculateDirection(from, to));
}

int Directionable::getOrientation() {
	unsigned result;
	if (this->direction == Directionable::DIRECTION_N)
		result = NORTH;
	else if (this->direction == Directionable::DIRECTION_S)
		result = SOUTH;
	else if (this->direction == Directionable::DIRECTION_SO)
		result = SOUTHWEST;
	else if (this->direction == Directionable::DIRECTION_SE)
		result = SOUTHEAST;
	else if (this->direction == Directionable::DIRECTION_NE)
		result = NORTHEAST;
	else if (this->direction == Directionable::DIRECTION_NO)
		result = NORTHWEST;
	else if (this->direction == Directionable::DIRECTION_O)
		result = WEST;
	else if (this->direction == Directionable::DIRECTION_E)
		result = EAST;
	else
		return -1;
	return static_cast<int>(result);
}


std::pair<int, int> Directionable::getPixelDirection() {
	return TRANSFORM_TILE_TO_PIXEL_DIRECTION.at(this->direction);
}

std::pair<int, int> Directionable::calculateDirection(std::pair<int, int> from, std::pair<int, int> to) {
	std::pair<int, int> aux = to + (from*(-1));
	aux.first = (aux.first == 0) ? 0 : ((aux.first > 0)? 1: -1);
	aux.second = (aux.second == 0) ? 0 : ((aux.second > 0)? 1: -1);
	return aux;
}

std::pair<int, int> Directionable::calculateDistance(std::pair<int, int> from, std::pair<int, int> to) {
	std::pair<int, int> aux = to + (from*(-1));
	return aux;
}


void Directionable::changeToOppositeDirection() {
	this->setDirection((this->getDirection()*(-1)));
}
