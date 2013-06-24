#include "GameView.h"
#include "IceBombDropper.h"

IceBombDropper::IceBombDropper() {
	this->setAmmo(5);//TODO: quitar harcodeo
	IceBomb* bomb = NULL;
	for (unsigned int i = 0; i < BOMB_POOL_SIZE; i++) {
		bomb = new IceBomb();
		this->getBombs().push_back(bomb);
	}
	this->setNextBombIndex(0);
}

IceBombDropper::~IceBombDropper() {
	for (unsigned int i = 0; i < BOMB_POOL_SIZE; i++) {
		delete this->getBombs()[i];
	}
}

void IceBombDropper::strike(Daniable*) {
	IceBomb* bomb = NULL;

	if (this->getAmmo() > 0) {
		bomb = this->getAvailableBomb();
		if (bomb != NULL) {
			this->ammo--;
			bomb->setStatus(EXPLOSIVE_EXPLOSION_COUNTDOWN);
			bomb->setOwner(this->getOwner());
			bomb->setPosition(this->getPosition());
			bomb->setDamage(this->getDamage());
			//bomb->setRectangle(bomb->getPosition(), bomb->getSprite() );
			bomb->setDamage(this->getDamage());
			bomb->startCountDown(0);
			GameView::instance().getWorldView()->addAmmunition(bomb);
		}
	}
}

IceBomb* IceBombDropper::getAvailableBomb() {
	IceBomb* bomb = NULL;
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

unsigned IceBombDropper::getNextBombIndex() {
	return this->nextBombIndex;
}

void IceBombDropper::setNextBombIndex(unsigned value) {
	this->nextBombIndex = value;
}

std::vector<IceBomb*>& IceBombDropper::getBombs() {
	return this->bombs;
}

bool IceBombDropper::sameDirection(std::pair<int, int> ) {
	return true;
}

bool IceBombDropper::isInsideRange(std::pair<int, int> ) {
	return true;
}

bool IceBombDropper::needsToReposition(std::pair<int, int> ) {
	return false;
}

bool IceBombDropper::readyToStrike(std::pair<int, int> ) {
	return true;
}