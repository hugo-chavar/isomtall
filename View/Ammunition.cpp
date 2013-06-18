#include "Ammunition.h"
#include "StringUtilities.h"

unsigned Ammunition::ammo_id_counter = 0;

Ammunition::Ammunition() {
	this->owner = "";
	this->ammo_id = stringUtilities::unsignedToString(ammo_id_counter++);
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