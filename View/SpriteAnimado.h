#pragma once
#include "Sprite.h"

class SpriteAnimado:public Sprite
{

private:
	float delay;
	float fps;
	int comienzo_frame;
	void cargarFrames(AnimatedEntity * entity);

public:
	void actualizarFrame();
	SpriteAnimado(AnimatedEntity* entity);
	~SpriteAnimado();
};

