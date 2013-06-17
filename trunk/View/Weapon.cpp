#include "Weapon.h"

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

bool Weapon::readyToStrike(std::pair<int, int> tile) {
	if (!this->sameDirection(tile))
		return false;
	if (!this->isInsideRange(tile))
		return false;
	return true;
}