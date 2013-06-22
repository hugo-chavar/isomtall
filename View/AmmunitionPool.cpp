#include "AmmunitionPool.h"
#include "StringUtilities.h"
#include "GameView.h"


AmmunitionPool::AmmunitionPool() {
	Arrow* arrow = NULL;
	Grenade* grenade = NULL;
	for (unsigned int i = 0; i < NUMBERAMMUNITIONS; i++) {
		arrow = new Arrow();
		this->arrows.push_back(arrow);
		grenade = new Grenade();
		this->grenades.push_back(grenade);
	}
	this->setNextArrowIndex(0);
	this->setNextGrenadeIndex(0);
}

AmmunitionPool::~AmmunitionPool() {
	for (unsigned int i = 0; i < NUMBERAMMUNITIONS; i++) {
		delete this->arrows[i];
		delete this->grenades[i];
	}
}

Arrow* AmmunitionPool::getAvailableArrow() {
	Arrow* arrow = NULL;
	bool found = false;
	unsigned int i = this->getNextArrowIndex();

	do {
		arrow = this->arrows[i];
		if (arrow->isAvailable()) {
			found = true;
			arrow->setAvailable(false);
		}

		if (i < (this->arrows.size() - 1))
			i++;
		else
			i = 0;
	} while (!found && i != this->getNextArrowIndex());

	if (!found)
		arrow = NULL; //TODO: LOG SOME WARNING.

	this->setNextArrowIndex(i);

	return arrow;
}

Grenade* AmmunitionPool::getAvailableGrenade() {
	Grenade* grenade = NULL;
	bool found = false;
	unsigned int i = this->getNextGrenadeIndex();

	do {
		grenade = this->grenades[i];
		if (grenade->isAvailable()) {
			found = true;
			grenade->setAvailable(false);
		}

		if (i < (this->grenades.size() - 1))
			i++;
		else
			i = 0;
	} while (!found && i != this->getNextGrenadeIndex());

	if (!found)
		grenade = NULL; //TODO: LOG SOME WARNING.

	this->setNextGrenadeIndex(i);

	return grenade;
}

unsigned AmmunitionPool::getNextArrowIndex() {
	return this->nextArrowIndex;
}

void AmmunitionPool::setNextArrowIndex(unsigned value) {
	this->nextArrowIndex = value;
}

unsigned AmmunitionPool::getNextGrenadeIndex() {
	return this->nextGrenadeIndex;
}

void AmmunitionPool::setNextGrenadeIndex(unsigned value) {
	this->nextGrenadeIndex = value;
}

void AmmunitionPool::deserialize(string argument) {
	bool found = false;
	std::vector <std::string> data;
	stringUtilities::splitString(argument, data, '?');

	if (data[0] == "Arrow") {
		for (unsigned int i=0; i<this->arrows.size(); i++) {
			if ((this->arrows[i]->getAmmoId() == data[1]) && (!this->arrows[i]->isAvailable())) {
				this->arrows[i]->positionFromString(data[2]);
				this->arrows[i]->directionFromString(data[3]);
				this->arrows[i]->setCouldContinue(data[4] == "A");
				found = true;
			}
		}
		if (!found) {
			Arrow *arrow = NULL;
			arrow = this->getAvailableArrow();
			if (arrow) {
				arrow->setName(data[0]);
				arrow->setAmmoID(data[1]);
				arrow->positionFromString(data[2]);
				arrow->directionFromString(data[3]);
				arrow->setCouldContinue(data[4] == "A");
				GameView::instance().getWorldView()->addAmmunition(arrow);
			}
		}
	}

	else {
		if (data[0] == "Grenade") {
			for (unsigned int i=0; i<this->grenades.size(); i++) {
				if ((this->grenades[i]->getAmmoId() == data[1]) && (!this->grenades[i]->isAvailable())) {
					this->grenades[i]->positionFromString(data[2]);
					this->grenades[i]->setCouldContinue(data[3] == "A");
					found = true;
				}
			}
			if (!found) {
				Grenade *grenade = NULL;
				grenade = this->getAvailableGrenade();
				if (grenade) {
					grenade->setName(data[0]);
					grenade->setAmmoID(data[1]);
					grenade->positionFromString(data[2]);
					grenade->setCouldContinue(data[3] == "A");
					GameView::instance().getWorldView()->addAmmunition(grenade);
				}
			}
		}
	}
}

bool AmmunitionPool::ammoIDIsInPlay(string name, string id) {
	if (name == "Arrow") {
		for (unsigned int i=0; i<this->arrows.size(); i++) {
			if ((this->arrows[i]->getAmmoId() == id) && (this->arrows[i]->isAvailable()))
				return true;
		}
	}
	return false;
}