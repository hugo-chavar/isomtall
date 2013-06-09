#include "SpriteAnimado.h"
#include "Game.h"
#include "StringUtilities.h"

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
	this->accumulatedTime -= ((1000/fps) + this->getDelay());
	if ( this->lastFrame() )
		this->restart();
	else
		this->currentSurfaceNumber++;
	
}

bool SpriteAnimado::timeIsOver() {
	common::Logger::instance().log("Acumulated: " + stringUtilities::floatToString(this->accumulatedTime));
	common::Logger::instance().log("100/fps: " + stringUtilities::floatToString((1000/fps)));
	common::Logger::instance().log("Delay: " + stringUtilities::floatToString(this->getDelay()));
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
