#include "GameView.h"
#include "Grenade.h"
#include "Logger.h"
#include "Daniable.h"
#include "../Common/StringUtilities.h"

Grenade::Grenade() {
	this->setName("Grenade");
	this->setAmmunitionType(HAND_GRENADE);
	this->setStatus(EXPLOSIVE_INACTIVE);
	this->setSprite(this->getSpriteWithName(this->getName()));
	explosionSprite = (SpriteAnimado*)this->getSpriteWithName("redexplosion");
}

Grenade::~Grenade() {
}

bool Grenade::isAlive() {
	return (this->getStatus() != EXPLOSIVE_DUST_IN_THE_WIND);
}

void Grenade::update() {
	switch (this->getStatus()){
		case EXPLOSIVE_FLYING: {
			Movable::verify();
			if ((!this->isTargetReached())&&(this->couldContinue()))
				Movable::update();
			else {
				this->setTargetTile(this->getLastTile());
				this->setStatus(EXPLOSIVE_BOUNCING);
				this->setTargetReached(false);
				this->setCouldContinue(true);
				this->changeToOppositeDirection();
			}
			break;
		}
		
		case EXPLOSIVE_BOUNCING: {
			int x, y;
			this->setCurrentTile(this->getCurrentTile() + this->getDirection());
			x = this->getTileWidth()*(this->getCurrentTile().first - this->getCurrentTile().second)/2 - this->getSprite()->relatx();
			y = this->getTileHeight()*(this->getCurrentTile().first + this->getCurrentTile().second)/2 - this->getSprite()->relaty();
			this->setPosition(std::make_pair(x, y));
			this->setStatus(EXPLOSIVE_EXPLOSION_COUNTDOWN);
			this->startCountDown(5); //tarda 5 segundos en exlotar
		}
		break;
		case EXPLOSIVE_EXPLOSION_COUNTDOWN: {
			this->decreaseEndStatusTime();
			//common::Logger::instance().log("this->endStatusTime: " + stringUtilities::unsignedToString(static_cast<unsigned>(this->endStatusTime)));
			if (this->endStatusTime == 0)
				this->setStatus(EXPLOSIVE_EXPLOSION);
			break;
		}
		case EXPLOSIVE_EXPLOSION: {
			GameView::instance().getGameSounds().playSoundEffect(SOUND_INDEX_EXPLOSION);
			this->setStatus(EXPLOSIVE_BURNING);
			explosionSprite->setAccumulatedTime(0.0);
			explosionSprite->restart();
			this->setCenter(this->getCurrentTile());
			this->setRange(3);
			this->activate();
			this->range.fill();
			std::pair<int, int > aux;
			while (this->range.hasNext()) {
				aux = this->range.next();
				Daniable* daniable = GameView::instance().getDaniableInTile(aux);
				if (daniable) {
					daniable->recibirDano(this->getDamage());
					if (!(daniable->isAlive()))
						GameView::instance().getMission()->missionUpdate(daniable, this->getOwner());
				}
			}
			break;
		}
		case EXPLOSIVE_BURNING: {
			explosionSprite->updateFrame();
			this->decreaseEndStatusTime();
			if ((this->endStatusTime == 0)&&(explosionSprite->lastFrame())) {
				this->setStatus(EXPLOSIVE_DUST_IN_THE_WIND);
				this->setAvailable(true);
			}
			break;
		}
	}
}
		
void Grenade::startCountDown(float seconds) {
	this->setEndStatusTime(seconds);
}

void Grenade::render(Camera& camera) {
		if (this->getStatus() != EXPLOSIVE_BURNING)
			Movable::render(camera);
		else {
			this->setRectangle(this->getCurrentTile(),explosionSprite);
			camera.render(this->spriteRect,explosionSprite->getSurfaceAt(-1)->getSurfaceToShow(false));
		}

}