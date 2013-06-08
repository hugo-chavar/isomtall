#include "SpriteAnimado.h"
#include "Game.h"

SpriteAnimado::SpriteAnimado(AnimatedEntity* entity) {
	spriteEntity = entity;
	//comienzo_frame = SDL_GetTicks();
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
	if (this->getCurrentSurfaceNumber() == 0)
		deltaTime -= delay;
	//comienzo_frame = SDL_GetTicks();
	this->addSticks(deltaTime); //TODO: traer del timer
	if ( this->timeIsOver())
		this->advance();
}
//
//void SpriteAnimado::getNextFrame() {
//	this->avanzarFrames();
//}

bool SpriteAnimado::lastFrame() {
	if (this->getCurrentSurfaceNumber() >= (this->surfaces.size() - 1)) {
		return true;
	} else {
		return false;
	}
}

void SpriteAnimado::advance() {
	if ( this->lastFrame() )
		this->restart();
	else
		this->currentSurfaceNumber++;
	this->accumulatedTime -= (1000/fps);
}

bool SpriteAnimado::timeIsOver() {
	return (this->accumulatedTime >= (1000/fps));
}

void SpriteAnimado::loadSurfaces() {
	AnimatedEntity* auxEntity = (AnimatedEntity*)spriteEntity;
	auxEntity->imagesPaths()->restartCurrentPosition();
	while (auxEntity->imagesPaths()->hasNext()) {
		this->addSurface(auxEntity->imagesPaths()->nextFullPath());
	}
}


void SpriteAnimado::addSticks(float ticks) {
	this->accumulatedTime += ticks;
}
