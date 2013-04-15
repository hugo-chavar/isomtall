#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <vector>
#include "Sprite.h"
#include "../Model/PersonajeModelo.h"
#include "Entity.h"

class Personaje : public Entity {
public:
	Personaje(model::PersonajeModelo* pj);
	void agregarSprite(Sprite* sprite);
	void update();
	void render(Camera& camera);
	void setDestino(int xTile, int yTile);
	~Personaje();
	std::pair<int,int> posicion();
	model::PersonajeModelo* Personaje::personajeModelo();

private:
	int procesarAnimacion(int animacion);
	int estadoModelo(int estado);
	void velocidadRelativa(std::pair<float, float>& factor);
	void resolverSerrucho();

	std::pair<int, int> tileActual;
	model::PersonajeModelo* modelo;
	std::vector<Sprite*> sprites;
	float velocidad;
	int estado;
	std::pair<int, int> delta;
	std::pair<float, float> ePot;
	int serr;
};
#endif