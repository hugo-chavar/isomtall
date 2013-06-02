#pragma once
#include "Sprite.h"

class SpriteAnimado: public Sprite {

private:
	float delay;
	float fps;
	int comienzo_frame;
	void avanzarFrames();
	bool tiempoFrameCumplido(float delta);
	
	void loadSurfaces();
public:
	void initialize();
	void actualizarFrame();
	void getNextFrame();
	SpriteAnimado(AnimatedEntity* entity);
	bool ultimoFrame();
	~SpriteAnimado();
};

