#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <vector>
#include "Sprite.h"
#include "PersonajeModelo.h"
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
	model::PersonajeModelo* personajeModelo();
	void loadSprites();
	void clearSprites() ;
	void addNextSprite(AnimatedEntity*);
	void addFirstSprite(AnimatedEntity*);
	
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
	std::pair<float, float> delta;
	std::pair<float, float> ePot;
	int serr;
};
#endif