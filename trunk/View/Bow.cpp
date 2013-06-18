#include "GameView.h"
#include "Bow.h"
#include "Arrow.h"

Bow::Bow() {
	this->setAmmo(5);//TODO: quitar harcodeo
	Arrow* arrow = NULL;
	for (unsigned int i = 0; i < ARROW_POOL_SIZE; i++) {
		arrow = new Arrow();
		this->getArrows().push_back(arrow);
	}
	this->setNextArrowIndex(0);
}

Bow::~Bow() {
	for (unsigned int i = 0; i < ARROW_POOL_SIZE; i++) {
		delete this->getArrows()[i];
	}
}

void Bow::strike(Daniable* target) {
	Arrow* arrow = NULL;

	if (this->getAmmo() > 0) {
		arrow = this->getAvailableArrow();
		if (arrow != NULL) {
			this->ammo--;
			arrow->setCouldContinue(true);
			arrow->setTargetReached(false);
			arrow->setOwner(this->getOwner());
			arrow->setTargetTile(target->getPosition());
			arrow->setInitialTile(this->getPosition());
			arrow->setDamage(this->getDamage());
			arrow->setDirection(this->getDirection());
			arrow->setVelocity(150.0);//TODO: sacar harcodeo
			arrow->initialize();
			GameView::instance().getWorldView()->addAmmunition(arrow);
			//TODO: put projectile into simulation entities list.
		}
	}
}

Arrow* Bow::getAvailableArrow() {
	Arrow* arrow = NULL;
	bool found = false;
	unsigned int i = this->getNextArrowIndex();

	do {
		arrow = this->getArrows()[i];
		if (arrow->isAvailable()) {
			found = true;
			arrow->setAvailable(false);
		}

		if (i < (this->getArrows().size() - 1))
			i++;
		else
			i = 0;
	} while (!found && i != this->getNextArrowIndex());

	if (!found)
		arrow = NULL; //TODO: LOG SOME WARNING.

	this->setNextArrowIndex(i);

	return arrow;
}

unsigned Bow::getAmmo() {
	return this->ammo;
}

void Bow::setAmmo(unsigned ammo) {
	this->ammo = ammo;
}

unsigned Bow::getNextArrowIndex() {
	return this->nextArrowIndex;
}

void Bow::setNextArrowIndex(unsigned value) {
	this->nextArrowIndex = value;
}

std::vector<Arrow*>& Bow::getArrows() {
	return this->arrows;
}