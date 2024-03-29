#include "SpriteAnimado.h"
#include "Game.h"
#include "StringUtilities.h"

SpriteAnimado::SpriteAnimado(AnimatedEntity* entity) {
	spriteEntity = entity;
	delay = static_cast<float>(entity->delay()); 
	fps = static_cast<float>(entity->fps());
	this->accumulatedTime = 0;
	this->initialize();
}

SpriteAnimado::~SpriteAnimado() {
}

void SpriteAnimado::initialize() {
	this->restart();
	relx = spriteEntity->pixelRefX();
	rely = spriteEntity->pixelRefY();
	_baseWidth = spriteEntity->baseWidth();
	_baseHeight = spriteEntity->baseHeight();
	this->loadSurfaces();
}

void SpriteAnimado::updateFrame() {
	float deltaTime = Game::instance().getTimer()->getDeltaTime();
	this->addSticks(deltaTime);
	if ( this->timeIsOver())
		this->advance();
}

bool SpriteAnimado::lastFrame() {
	return (this->getCurrentSurfaceNumber() >= (this->surfaces.size() - 1));
}

void SpriteAnimado::advance() {
	this->accumulatedTime -= ((1000/fps) + this->getDelay());
	if ( this->lastFrame() )
		this->restart();
	else
		this->currentSurfaceNumber++;
}

bool SpriteAnimado::timeIsOver() {
	return (this->accumulatedTime >= (1000/fps) - this->getDelay());
}

void SpriteAnimado::loadSurfaces() {
	AnimatedEntity* auxEntity = (AnimatedEntity*)spriteEntity;
	auxEntity->imagesPaths()->restartCurrentPosition();
	while (auxEntity->imagesPaths()->hasNext()) {
		this->addSurface(auxEntity->imagesPaths()->nextFullPath());
	}
}

void SpriteAnimado::addSticks(float ticks) {
	this->accumulatedTime += ticks*1000;
}

float SpriteAnimado::getDelay() {
	if (this->getCurrentSurfaceNumber() == 0)
		return this->delay;
	return 0;
}

void SpriteAnimado::setAccumulatedTime(float ticks) {
	this->accumulatedTime = ticks;
}
