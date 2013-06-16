#include "Ammunition.h"

Ammunition::Ammunition() {
	this->owner = "";
	this->ammo_id = "";
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

float Ammunition::getDamage() {
	return this->damage;
}

void Ammunition::setDamage(float value) {
	this->damage = value;
}

std::string Ammunition::getAmmoId() {
	return this->ammo_id;
}

void Ammunition::setAmmoID(std::string value) {
	this->ammo_id = value;
}

bool Ammunition::isAvailable() {
	return this->available;
}

void Ammunition::setAvailable(bool available) {
	this->available = available;
}