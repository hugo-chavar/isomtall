#pragma once
#include "Sprite.h"

class SpriteAnimado:public Sprite
{

private:
	float delay;
	float fps;
	int comienzo_frame;
	void cargarFrames(AnimatedEntity * entity);
	void avanzarFrames();
	bool tiempoFrameCumplido(float delta);

public:
	void actualizarFrame();
	SpriteAnimado(AnimatedEntity* entity);
	~SpriteAnimado();
};
