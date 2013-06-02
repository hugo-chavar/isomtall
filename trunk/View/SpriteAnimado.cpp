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
	estado = 0;
	relx = spriteEntity->pixelRefX();
	rely = spriteEntity->pixelRefY();
	_baseWidth = spriteEntity->baseWidth();
	_baseHeight = spriteEntity->baseHeight();
	this->loadSurfaces();
}

void SpriteAnimado::actualizarFrame() {
	float deltaTime = 0.0;
	if (estado == 0)
		deltaTime = delay;
	if ( tiempoFrameCumplido(deltaTime))
		this->avanzarFrames();
}

void SpriteAnimado::getNextFrame() {
	this->avanzarFrames();
}

bool SpriteAnimado::ultimoFrame() {
	if (estado >= surfaces.size()-1) {
		return true;
	} else {
		return false;
	}
}

void SpriteAnimado::reiniciar() {
	estado = 0;
}

void SpriteAnimado::avanzarFrames() {
	comienzo_frame = SDL_GetTicks();
	if ( this->ultimoFrame() )
		estado = 0;
	else
		estado = estado++;
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

void SpriteAnimado::setCurrentState(unsigned state) {
	estado = state;
}