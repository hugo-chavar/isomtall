#include "Weapon.h"
#include "DataTypes.h"
#include "Game.h"
#include <vector>

Weapon::Weapon() {
	this->active = false;
	this->damage = 0;
	this->precision = 0;
}

Weapon::~Weapon() {
}

void Weapon::setActive(bool active) {
	this->active = active;
}

void Weapon::setRange(int value) {
	this->range.setRadius(value);
}

void Weapon::setDamage(float damage) {
	this->damage = damage;
}

void Weapon::setPrecision(float precision) {
	this->precision = precision;
}

void Weapon::initialize(bool active, unsigned int range, float damage, float precision) {
	this->setActive(active);
	this->setRange(range);
	this->setDamage(damage);
	this->setPrecision(precision);
}

bool Weapon::getActive() {
	return this->active;
}

int Weapon::getRange() {
	return this->range.getRadius();
}

float Weapon::getDamage() {
	return this->damage;
}

float Weapon::getPrecision() {
	return this->precision;
}

std::string Weapon::getOwner() {
	return this->owner;
}

void Weapon::setOwner(std::string value) {
	this->owner = value;
}

bool Weapon::sameDirection(std::pair<int, int> tile) {
	std::pair<int, int> aux = this->calculateDirection(this->getPosition(), tile);
	return (aux == this->getDirection());
}

bool Weapon::isInsideRange(std::pair<int, int> tile) {
	this->range.setCenter(this->getPosition());
	return (this->range.inside(tile));
}

bool Weapon::needsToReposition(std::pair<int, int> tile) {
	std::pair<int, int> distance = this->calculateDistance(this->getPosition(), tile);
	if ((distance.first == 0) || (distance.second == 0))
		return false;
	if (distance.first == distance.second)
		return false;
	if (distance.first == (distance.second*(-1)))
		return false;
	if ((distance.first < distance.second) || (distance.first > distance.second))
		return true;
	return true;
}

bool Weapon::readyToStrike(std::pair<int, int> tile) {
	if (!this->sameDirection(tile))
		return false;
	if (!this->isInsideRange(tile))
		return false;
	return true;
}

std::pair<int, int> Weapon::calculateRepositionToStrike(std::pair<int, int> tile) {
	vector<std::pair<int,int>> posiblePositions;
	for (int i=-1; i<=1; i++) {
		for (int j=-1; j<=1; j++) {
			this->position = this->position + make_pair(i,j);
			if (this->isInsideRange(tile) && (!this->needsToReposition(tile)) && (Game::instance().world()->cost(this->position.first, this->position.second) == 1))
				posiblePositions.push_back(this->position);
			this->position = this->position + make_pair(i,j)*(-1);
		}
	}
	std::pair<int, int> distance;
	std::pair<int, int> reposition = this->position;
	int mod = 100000;
	for (unsigned int i=0; i<posiblePositions.size(); i++) {
		distance = this->calculateDistance(posiblePositions[i], tile);
		int new_mod = (distance.first * distance.first) + (distance.second * distance.second);
		if (new_mod < mod) {
			reposition = posiblePositions[i];
			mod = new_mod;
		}
	}
	return reposition;
}