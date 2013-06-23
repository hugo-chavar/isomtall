#include "Game.h"
#include "GameView.h"
#include "Sword.h"

Sword::Sword() {
	this->setAmmo(1);
}

Sword::~Sword() {
}

void Sword::strike(Daniable* target) {
	float precision = Game::instance().getRandom();
	if (precision >= this->getPrecision()) {
		target->recibirDano(this->getDamage());
		if(target->isWood())
			GameView::instance().getGameSounds().playSoundEffect(SOUND_INDEX_ATTACK_ON_WOOD);
		else
			GameView::instance().getGameSounds().playSoundEffect(SOUND_INDEX_ATTACK_ON_SHIELD);
		if (!(target->isAlive()))
			GameView::instance().getMission()->missionUpdate(target, this->getOwner());
	}
	
}
