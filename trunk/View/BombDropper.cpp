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

void BombDropper::strike(Daniable*) {
	Bomb* bomb = NULL;

	if (this->getAmmo() > 0) {
		bomb = this->getAvailableBomb();
		if (bomb != NULL) {
			this->ammo--;
			bomb->setStatus(EXPLOSIVE_EXPLOSION_COUNTDOWN);
			bomb->setOwner(this->getOwner());
			bomb->setPosition(this->getPosition());
			bomb->setDamage(this->getDamage());
			bomb->setRectangle(bomb->getPosition(), bomb->getSprite() );
			bomb->setDamage(this->getDamage());
			bomb->startCountDown(5);
			GameView::instance().getWorldView()->addAmmunition(bomb);
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

bool BombDropper::sameDirection(std::pair<int, int> ) {
	return true;
}

bool BombDropper::isInsideRange(std::pair<int, int> ) {
	return true;
}

bool BombDropper::needsToReposition(std::pair<int, int> ) {
	return false;
}

bool BombDropper::readyToStrike(std::pair<int, int> ) {
	return true;
}