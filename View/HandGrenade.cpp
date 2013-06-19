#include "GameView.h"
#include "HandGrenade.h"

HandGrenade::HandGrenade() {
	this->setAmmo(5);//TODO: quitar harcodeo
	Grenade* grenade = NULL;
	for (unsigned int i = 0; i < HANDGRENADE_POOL_SIZE; i++) {
		grenade = new Grenade();
		this->getGrenades().push_back(grenade);
	}
	this->setNextGrenadeIndex(0);
}

HandGrenade::~HandGrenade() {
	for (unsigned int i = 0; i < HANDGRENADE_POOL_SIZE; i++) {
		delete this->getGrenades()[i];
	}
}

void HandGrenade::strike(Daniable* target) {
	Grenade* grenade = NULL;

	if (this->getAmmo() > 0) {
		grenade = this->getAvailableGrenade();
		if (grenade != NULL) {
			this->ammo--;
			grenade->setStatus(EXPLOSIVE_FLYING);
			grenade->setCouldContinue(true);
			grenade->setTargetReached(false);
			grenade->setOwner(this->getOwner());
			grenade->setTargetTile(target->getPosition());
			grenade->setInitialTile(this->getPosition());
			grenade->setDamage(this->getDamage());
			grenade->setDirection(this->getDirection());
			grenade->setVelocity(150.0);//TODO: sacar harcodeo
			grenade->initialize();
			GameView::instance().getWorldView()->addAmmunition(grenade);
			//TODO: put projectile into simulation entities list.
		}
	}
}

Grenade* HandGrenade::getAvailableGrenade() {
	Grenade* grenade = NULL;
	bool found = false;
	unsigned int i = this->getNextGrenadeIndex();

	do {
		grenade = this->getGrenades()[i];
		if (grenade->isAvailable()) {
			found = true;
			grenade->setAvailable(false);
		}

		if (i < (this->getGrenades().size() - 1))
			i++;
		else
			i = 0;
	} while (!found && i != this->getNextGrenadeIndex());

	if (!found)
		grenade = NULL; //TODO: LOG SOME WARNING.

	this->setNextGrenadeIndex(i);

	return grenade;
}

unsigned HandGrenade::getAmmo() {
	return this->ammo;
}

void HandGrenade::setAmmo(unsigned ammo) {
	this->ammo = ammo;
}

unsigned HandGrenade::getNextGrenadeIndex() {
	return this->nextGrenadeIndex;
}

void HandGrenade::setNextGrenadeIndex(unsigned value) {
	this->nextGrenadeIndex = value;
}

std::vector<Grenade*>& HandGrenade::getGrenades() {
	return this->grenades;
}