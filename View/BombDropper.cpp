#include "GameView.h"
#include "BombDropper.h"

BombDropper::BombDropper() {
	this->setAmmo(5);//TODO: quitar harcodeo
	Bomb* bomb = NULL;
	for (unsigned int i = 0; i < BOMB_POOL_SIZE; i++) {
		bomb = new Bomb();
		this->getBombs().push_back(bomb);
	}
	this->setNextBombIndex(0);
}

BombDropper::~BombDropper() {
	for (unsigned int i = 0; i < BOMB_POOL_SIZE; i++) {
		delete this->getBombs()[i];
	}
}

void BombDropper::strike(Daniable* target) {
	Bomb* bomb = NULL;

	if (this->getAmmo() > 0) {
		bomb = this->getAvailableBomb();
		if (bomb != NULL) {
			this->ammo--;
			bomb->setStatus(EXPLOSIVE_FLYING);
			bomb->setOwner(this->getOwner());
			bomb->setPosition(this->getPosition());
			bomb->setDamage(this->getDamage());
			bomb->setRectangle(bomb->getPosition(), bomb->getSprite() );
			//bomb->setDirection(this->getDirection());
			//bomb->setVelocity(150.0);//TODO: sacar harcodeo
			//bomb->initialize();
			GameView::instance().getWorldView()->addAmmunition(bomb);
			//TODO: put projectile into simulation entities list.
		}
	}
}

Bomb* BombDropper::getAvailableBomb() {
	Bomb* bomb = NULL;
	bool found = false;
	unsigned int i = this->getNextBombIndex();

	do {
		bomb = this->getBombs()[i];
		if (bomb->isAvailable()) {
			found = true;
			bomb->setAvailable(false);
		}

		if (i < (this->getBombs().size() - 1))
			i++;
		else
			i = 0;
	} while (!found && i != this->getNextBombIndex());

	if (!found)
		bomb = NULL; //TODO: LOG SOME WARNING.

	this->setNextBombIndex(i);

	return bomb;
}

unsigned BombDropper::getAmmo() {
	return this->ammo;
}

void BombDropper::setAmmo(unsigned ammo) {
	this->ammo = ammo;
}

unsigned BombDropper::getNextBombIndex() {
	return this->nextBombIndex;
}

void BombDropper::setNextBombIndex(unsigned value) {
	this->nextBombIndex = value;
}

std::vector<Bomb*>& BombDropper::getBombs() {
	return this->bombs;
}