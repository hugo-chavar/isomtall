#include "AmmunitionPool.h"
#include "StringUtilities.h"
#include "GameView.h"
#include "Logger.h"


AmmunitionPool::AmmunitionPool() {
	Arrow* arrow = NULL;
	Grenade* grenade = NULL;
	IceIncantation* iceIncantation = NULL;
	Bomb* bomb = NULL;
	IceBomb* iceBomb = NULL;
	for (unsigned int i = 0; i < NUMBERAMMUNITIONS; i++) {
		arrow = new Arrow();
		arrow->setVelocity(0);
		arrow->setAvailable(true);
		this->arrows.push_back(arrow);
		grenade = new Grenade();
		grenade->setVelocity(0);
		grenade->setAvailable(true);
		this->grenades.push_back(grenade);
		iceIncantation = new IceIncantation();
		iceIncantation->setVelocity(0);
		iceIncantation->setAvailable(true);
		this->iceIncantations.push_back(iceIncantation);
		bomb = new Bomb();
		bomb->setAvailable(true);
		this->bombs.push_back(bomb);
		iceBomb = new IceBomb();
		iceBomb->setAvailable(true);
		this->iceBombs.push_back(iceBomb);
	}
	this->setNextArrowIndex(0);
	this->setNextGrenadeIndex(0);
	this->setNextIceIncantationIndex(0);
	this->setNextBombIndex(0);
	this->setNextIceBombIndex(0);
}

AmmunitionPool::~AmmunitionPool() {
	for (unsigned int i = 0; i < NUMBERAMMUNITIONS; i++) {
		delete this->arrows[i];
		delete this->grenades[i];
		this->iceIncantations[i];
		this->bombs[i];
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


IceIncantation* AmmunitionPool::getAvailableIceIncantation() {
	IceIncantation* iceIncantation = NULL;
	bool found = false;
	unsigned int i = this->getNextIceIncantationIndex();

	do {
		iceIncantation = this->iceIncantations[i];
		if (iceIncantation->isAvailable()) {
			found = true;
			iceIncantation->setAvailable(false);
		}

		if (i < (this->iceIncantations.size() - 1))
			i++;
		else
			i = 0;
	} while (!found && i != this->getNextIceIncantationIndex());

	if (!found)
		iceIncantation = NULL; //TODO: LOG SOME WARNING.

	this->setNextIceIncantationIndex(i);

	return iceIncantation;
}

Bomb* AmmunitionPool::getAvailableBomb() {
	Bomb* bomb = NULL;
	bool found = false;
	unsigned int i = this->getNextBombIndex();

	do {
		bomb = this->bombs[i];
		if (bomb->isAvailable()) {
			found = true;
			bomb->setAvailable(false);
		}

		if (i < (this->bombs.size() - 1))
			i++;
		else
			i = 0;
	} while (!found && i != this->getNextBombIndex());

	if (!found)
		bomb = NULL; //TODO: LOG SOME WARNING.

	this->setNextBombIndex(i);

	return bomb;
}

IceBomb* AmmunitionPool::getAvailableIceBomb() {
	IceBomb* iceBomb = NULL;
	bool found = false;
	unsigned int i = this->getNextIceBombIndex();

	do {
		iceBomb = this->iceBombs[i];
		if (iceBomb->isAvailable()) {
			found = true;
			iceBomb->setAvailable(false);
		}

		if (i < (this->iceBombs.size() - 1))
			i++;
		else
			i = 0;
	} while (!found && i != this->getNextIceBombIndex());

	if (!found)
		iceBomb = NULL; //TODO: LOG SOME WARNING.

	this->setNextIceBombIndex(i);

	return iceBomb;
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

unsigned AmmunitionPool::getNextIceIncantationIndex() {
	return this->nextIceIncantationIndex;
}

void AmmunitionPool::setNextIceIncantationIndex(unsigned value) {
	this->nextIceIncantationIndex = value;
}

unsigned AmmunitionPool::getNextBombIndex() {
	return this->nextBombIndex;
}

void AmmunitionPool::setNextBombIndex(unsigned value) {
	this->nextBombIndex = value;
}

unsigned AmmunitionPool::getNextIceBombIndex()
{
	return this->nextIceBombIndex;
}

void AmmunitionPool::setNextIceBombIndex(unsigned value) {
	this->nextIceBombIndex = value;
}

void AmmunitionPool::deserialize(string argument) {
	bool found = false;
	std::vector <std::string> data;
	stringUtilities::splitString(argument, data, '?');

	if (data[0] == "Arrow") {
		for (unsigned int i=0; i<this->arrows.size(); i++) {
			if ((!this->arrows[i]->isAlive()) && (!this->arrows[i]->isAvailable())) {
				this->arrows[i]->setAvailable(true);
			}
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
				if ((!this->grenades[i]->isAlive()) && (!this->grenades[i]->isAvailable())) {
					this->grenades[i]->setAvailable(true);
				}
				if ((this->grenades[i]->getAmmoId() == data[1]) && (!this->grenades[i]->isAvailable())) {
					this->grenades[i]->positionFromString(data[2]);
					this->grenades[i]->directionFromString(data[3]);
					//this->grenades[i]->setCouldContinue(data[4] == "A");
					this->grenades[i]->setStatusFromString(data[4]);
					this->grenades[i]->setTargetTile(stringUtilities::stringToPairInt(data[5]));
					if (this->grenades[i]->getStatus() == EXPLOSIVE_BURNING) {
						this->grenades[i]->setEndStatusTime(0);
						this->grenades[i]->setStatus(EXPLOSIVE_EXPLOSION);
						
					}
					this->grenades[i]->setCurrentTile(stringUtilities::stringToPairInt(data[6]));
					this->grenades[i]->setInitialTile(stringUtilities::stringToPairInt(data[7]));
					this->grenades[i]->setVelocity(stringUtilities::stringToFloat(data[8]));
					this->grenades[i]->setLastTile(stringUtilities::stringToPairInt(data[9]));
					this->grenades[i]->setCouldContinue(data[10]=="T");
					this->grenades[i]->setTargetReached(data[11]=="T");
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
					grenade->directionFromString(data[3]);
					//grenade->setCouldContinue(data[4] == "A");
					grenade->setStatusFromString(data[4]);
					grenade->setTargetTile(stringUtilities::stringToPairInt(data[5]));
					grenade->setCurrentTile(stringUtilities::stringToPairInt(data[6]));
					grenade->setInitialTile(stringUtilities::stringToPairInt(data[7]));
					grenade->setVelocity(stringUtilities::stringToFloat(data[8]));
					grenade->setLastTile(stringUtilities::stringToPairInt(data[9]));
					grenade->setCouldContinue(data[10]=="T");
					grenade->setTargetReached(data[11]=="T");
					GameView::instance().getWorldView()->addAmmunition(grenade);
				}
			}
		} else if (data[0] == "IceIncantation") {
			for (unsigned int i=0; i<this->iceIncantations.size(); i++) {
				if ((!this->iceIncantations[i]->isAlive()) && (!this->iceIncantations[i]->isAvailable())) {
					this->iceIncantations[i]->setAvailable(true);
				}
				if ((this->iceIncantations[i]->getAmmoId() == data[1]) && (!this->iceIncantations[i]->isAvailable())) {
					this->iceIncantations[i]->positionFromString(data[2]);
					this->iceIncantations[i]->directionFromString(data[3]);
					this->iceIncantations[i]->setCouldContinue(data[4] == "A");
					found = true;
				}
			}
			if (!found) {
				IceIncantation *iceIncantation = NULL;
				iceIncantation = this->getAvailableIceIncantation();
				if (iceIncantation) {
					iceIncantation->setName(data[0]);
					iceIncantation->setAmmoID(data[1]);
					iceIncantation->positionFromString(data[2]);
					iceIncantation->directionFromString(data[3]);
					iceIncantation->setCouldContinue(data[4] == "A");
					GameView::instance().getWorldView()->addAmmunition(iceIncantation);
				}
			}
		} else if (data[0] == "Bomb") {
			for (unsigned int i=0; i<this->bombs.size(); i++) {
				if ((!this->bombs[i]->isAlive()) && (!this->bombs[i]->isAvailable())) {
					this->bombs[i]->setAvailable(true);
				}
				if ((this->bombs[i]->getAmmoId() == data[1]) && (!this->bombs[i]->isAvailable())) {
					this->bombs[i]->positionFromString(data[2]);
					this->bombs[i]->setEndStatusTime(5000);
					//bomb->directionFromString(data[3]);
					//bomb->setCouldContinue(data[3] == "A");
					this->bombs[i]->setStatusFromString(data[3]);
					if (this->bombs[i]->getStatus() == EXPLOSIVE_BURNING) {
						this->bombs[i]->setEndStatusTime(0);
						this->bombs[i]->setStatus(EXPLOSIVE_EXPLOSION);
					}
					found = true;
				}
			}
			if (!found) {
				Bomb * bomb = NULL;
				bomb = this->getAvailableBomb();
				if (bomb) {
					bomb->setName(data[0]);
					bomb->setAmmoID(data[1]);
					bomb->positionFromString(data[2]);
					//bomb->directionFromString(data[3]);
					//bomb->setCouldContinue(data[3] == "A");
					bomb->setStatusFromString(data[3]);
					if (bomb->getStatus() == EXPLOSIVE_EXPLOSION_COUNTDOWN)
						bomb->setEndStatusTime(5000);
					GameView::instance().getWorldView()->addAmmunition(bomb);
				}
			}
		}else if (data[0] == "IceBomb") {
			for (unsigned int i=0; i<this->iceBombs.size(); i++) {
				if ((!this->iceBombs[i]->isAlive()) && (!this->iceBombs[i]->isAvailable())) {
					this->iceBombs[i]->setAvailable(true);
				}
				if ((this->iceBombs[i]->getAmmoId() == data[1]) && (!this->iceBombs[i]->isAvailable())) {
					this->iceBombs[i]->positionFromString(data[2]);
					this->iceBombs[i]->setEndStatusTime(5000);
					this->iceBombs[i]->setStatusFromString(data[3]);
					if (this->iceBombs[i]->getStatus() == EXPLOSIVE_BURNING) {
						this->iceBombs[i]->setEndStatusTime(0);
						this->iceBombs[i]->setStatus(EXPLOSIVE_EXPLOSION);
					}
					found = true;
				}
			}
		if (!found) {
				IceBomb * iceBomb = NULL;
				iceBomb = this->getAvailableIceBomb();
				if (iceBomb) {
					iceBomb->setName(data[0]);
					iceBomb->setAmmoID(data[1]);
					iceBomb->positionFromString(data[2]);
					//bomb->directionFromString(data[3]);
					//bomb->setCouldContinue(data[3] == "A");
					iceBomb->setStatusFromString(data[3]);
					if (iceBomb->getStatus() == EXPLOSIVE_EXPLOSION_COUNTDOWN)
						iceBomb->setEndStatusTime(5000);
					GameView::instance().getWorldView()->addAmmunition(iceBomb);
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