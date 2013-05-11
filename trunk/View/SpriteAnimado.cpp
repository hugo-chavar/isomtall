#include "SpriteAnimado.h"


SpriteAnimado::SpriteAnimado(AnimatedEntity* entity) {
	this->inicializar(entity->pixelRefX(),entity->pixelRefY(),entity->baseWidth(),entity->baseHeight());
	comienzo_frame = SDL_GetTicks();
	delay = static_cast<float>(entity->delay()); 
	fps = static_cast<float>(entity->fps());
	cargarFrames(entity);
}

SpriteAnimado::~SpriteAnimado() {
}

void SpriteAnimado::actualizarFrame() {
	float deltaTime = 0.0;
	if(estado == 0)
		deltaTime = delay;
	if ( tiempoFrameCumplido(deltaTime))
		this->avanzarFrames();
}

void SpriteAnimado::cargarFrames(AnimatedEntity * entity) {
	unsigned i = 0;
	entity->imagesPaths()->restartCurrentPosition();
	while (entity->imagesPaths()->hasNext()) {
		frames.push_back(new Frame());	
		frames[i]->cargar(entity->imagesPaths()->nextFullPath());
		i++;
	}
}

bool SpriteAnimado::ultimoFrame() {
	if (estado >= frames.size()-1) {
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