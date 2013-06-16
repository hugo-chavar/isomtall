#include "Weapon.h"

Weapon::Weapon() {
	this->active = false;
	this->range = 0;
	this->damage = 0;
	this->precision = 0;
}

Weapon::~Weapon() {
}

void Weapon::setActive(bool active) {
	this->active = active;
}

void Weapon::setRange(unsigned int range) {
	this->range = range;
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

unsigned int Weapon::getRange() {
	return this->range;
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
