#include "GameView.h"
#include "Bomb.h"

Bomb::Bomb() {
	this->setName("Bomb");
	this->setAmmunitionType(BOMB);
	this->setStatus(EXPLOSIVE_INACTIVE);
	this->setSprite(this->getSpriteWithName(this->getName()));
	explosionSprite = (SpriteAnimado*)(this->getSpriteWithName("redexplosion"));
}

Bomb::~Bomb() {
}

bool Bomb::isAlive() {
	return (this->getStatus() != EXPLOSIVE_DUST_IN_THE_WIND);
}

void Bomb::update() {
	switch (this->getStatus()){
		case EXPLOSIVE_EXPLOSION_COUNTDOWN: {
			this->decreaseEndStatusTime();
			//common::Logger::instance().log("this->endStatusTime: " + stringUtilities::unsignedToString(static_cast<unsigned>(this->endStatusTime)));
			if (this->endStatusTime == 0)
				this->setStatus(EXPLOSIVE_EXPLOSION);
			break;
		}
		case EXPLOSIVE_EXPLOSION: {
			this->setStatus(EXPLOSIVE_BURNING);
			explosionSprite->setAccumulatedTime(0.0);
			explosionSprite->restart();
			this->setCenter(this->getPosition());
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

			//this->setSprite(explosionSprite);
			//this->setRectangle(this->getPosition(),explosionSprite);
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
		
void Bomb::startCountDown(float seconds) {
	this->setEndStatusTime(seconds);
}

void Bomb::render(Camera& camera) {
	
		if ((this->getStatus() != EXPLOSIVE_BURNING) && (this->getStatus() != EXPLOSIVE_DUST_IN_THE_WIND))
			Entity::render(camera);
		else { // if (this->getStatus() == EXPLOSIVE_FLYING)
			this->setRectangle(this->getPosition(),explosionSprite);
			camera.render(this->spriteRect,explosionSprite->getSurfaceAt(-1)->getSurfaceToShow(false));
		}

}

void Bomb::deserialize(std::string in) {
	std::vector<std::string> splittedIn;
	stringUtilities::splitString(in,splittedIn,';');

	this->setName(splittedIn[0]);
	this->setAmmoID(splittedIn[1]);
	this->positionFromString(splittedIn[2]);
}

std::string Bomb::serialize() {
	std::string out = this->getName();
	out.append(";");
	out.append(this->getAmmoId());
	out.append(";");
	out.append(this->positionToString());
	return out;
}