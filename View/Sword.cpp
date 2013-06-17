#include "Sword.h"
#include "Game.h"

Sword::Sword() {
}

Sword::~Sword() {
}

void Sword::strike(Daniable* target) {
	float precision = Game::instance().getRandom();
	if (precision >= this->getPrecision()) {
		target->recibirDano(this->getDamage());
	}
	
}

