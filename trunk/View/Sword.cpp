#include "Game.h"
#include "GameView.h"
#include "Sword.h"

Sword::Sword() {
}

Sword::~Sword() {
}

void Sword::strike(Daniable* target) {
	float precision = Game::instance().getRandom();
	if (precision >= this->getPrecision()) {
		target->recibirDano(this->getDamage());
		if (!(target->isAlive()))
			GameView::instance().getMission()->missionUpdate(target, this->getOwner());
	}
	
}

unsigned Sword::getAmmo() {
	return 1;
}

