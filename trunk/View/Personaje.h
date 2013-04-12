#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <vector>
#include "Sprite.h"
#include "./Model/PersonajeModelo.h"
#include "Entity.h"

class Personaje : public Entity {
public:
	Personaje();
	void agregarSprite(Sprite* sprite);
	void update();
	void render(Camera& camera);
	void setDestino(int xTile, int yTile);
	~Personaje();
private:
	int procesarAnimacion(int animacion);

	model::PersonajeModelo modelo;
	std::vector<Sprite*> sprites;
	float velocidad;
	int estado;
	std::pair<float, float> delta;
};
#endif