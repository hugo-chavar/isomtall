#include "SpriteAnimado.h"
#include "GameView.h"

SpriteAnimado::SpriteAnimado(AnimatedEntity* entity) {
	spriteEntity = entity;
	comienzo_frame = SDL_GetTicks();
	delay = static_cast<float>(entity->delay()); 
	fps = static_cast<float>(entity->fps());
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

void SpriteAnimado::actualizarFrame() {
	float deltaTime = 0.0;
	if (this->getCurrentSurfaceNumber() == 0)
		deltaTime = delay;
	if ( tiempoFrameCumplido(deltaTime))
		this->avanzarFrames();
}

void SpriteAnimado::getNextFrame() {
	this->avanzarFrames();
}

bool SpriteAnimado::ultimoFrame() {
	if (this->getCurrentSurfaceNumber() >= (this->surfaces.size() - 1)) {
		return true;
	} else {
		return false;
	}
}

void SpriteAnimado::avanzarFrames() {
	comienzo_frame = SDL_GetTicks();
	if ( this->ultimoFrame() )
		this->restart();
	else
		this->currentSurfaceNumber++;
}

bool SpriteAnimado::tiempoFrameCumplido(float delta) {
	return ((SDL_GetTicks() - comienzo_frame) >= ((1000/fps) + delta));
}

void SpriteAnimado::loadSurfaces() {
	AnimatedEntity* auxEntity = (AnimatedEntity*)spriteEntity;
	auxEntity->imagesPaths()->restartCurrentPosition();
	while (auxEntity->imagesPaths()->hasNext()) {
		this->addSurface(auxEntity->imagesPaths()->nextFullPath());
	}
}
