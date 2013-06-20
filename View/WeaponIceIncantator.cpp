#include "GameView.h"
#include "WeaponIceIncantator.h"
#include "IceIncantation.h"

WeaponIceIncantator::WeaponIceIncantator() {
	this->setAmmo(500);//TODO: quitar harcodeo
	IceIncantation* iceIncantation = NULL;
	for (unsigned int i = 0; i < ICE_INCANTATOR_POOL_SIZE; i++) {
		iceIncantation = new IceIncantation();
		this->getIceIncantations().push_back(iceIncantation);
	}
	this->setNextIceIncantationIndex(0);
}

WeaponIceIncantator::~WeaponIceIncantator() {
	for (unsigned int i = 0; i < ICE_INCANTATOR_POOL_SIZE; i++) {
		delete this->getIceIncantations()[i];
	}
}

void WeaponIceIncantator::strike(Daniable* target) {
	IceIncantation* iceIncantation = NULL;

	if (this->getAmmo() > 0) {
		iceIncantation = this->getAvailableIceIncantation();
		if (iceIncantation != NULL) {
			this->ammo--;
			iceIncantation->setCouldContinue(true);
			iceIncantation->setTargetReached(false);
			iceIncantation->setOwner(this->getOwner());
			iceIncantation->setTargetTile(target->getPosition());
			iceIncantation->setInitialTile(this->getPosition());
			iceIncantation->setDamage(this->getDamage());
			iceIncantation->setDirection(this->getDirection());
			iceIncantation->setVelocity(150.0);//TODO: sacar harcodeo
			iceIncantation->initialize();
			GameView::instance().getWorldView()->addAmmunition(iceIncantation);
		}
	}
}

IceIncantation* WeaponIceIncantator::getAvailableIceIncantation() {
	IceIncantation* iceIncantation = NULL;
	bool found = false;
	unsigned int i = this->getNextIceIncantationIndex();

	do {
		iceIncantation = this->getIceIncantations()[i];
		if (iceIncantation->isAvailable()) {
			found = true;
			iceIncantation->setAvailable(false);
		}

		if (i < (this->getIceIncantations().size() - 1))
			i++;
		else
			i = 0;
	} while (!found && i != this->getNextIceIncantationIndex());

	if (!found)
		iceIncantation = NULL; //TODO: LOG SOME WARNING.

	this->setNextIceIncantationIndex(i);

	return iceIncantation;
}

unsigned WeaponIceIncantator::getAmmo() {
	return this->ammo;
}

void WeaponIceIncantator::setAmmo(unsigned ammo) {
	this->ammo = ammo;
}

unsigned WeaponIceIncantator::getNextIceIncantationIndex() {
	return this->nextIceIncantationIndex;
}

void WeaponIceIncantator::setNextIceIncantationIndex(unsigned value) {
	this->nextIceIncantationIndex = value;
}

std::vector<IceIncantation*>& WeaponIceIncantator::getIceIncantations() {
	return this->iceIncantations;
}