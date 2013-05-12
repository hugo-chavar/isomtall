#pragma once
#include "Sprite.h"

class SpriteAnimado: public Sprite {

private:
	float delay;
	float fps;
	int comienzo_frame;
	//void cargarFrames(AnimatedEntity * entity);
	void avanzarFrames();
	bool tiempoFrameCumplido(float delta);
	//void loadSurfaces(EntityObject * entity);
	
	void loadSurfaces();
public:
	void initialize();
	void actualizarFrame();
	SpriteAnimado(AnimatedEntity* entity);
	//Dice si el sprite esta en el ultimo frame
	bool ultimoFrame();
	void reiniciar();
	~SpriteAnimado();
};

