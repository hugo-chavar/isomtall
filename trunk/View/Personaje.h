#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <vector>
#include "Sprite.h"
#include "SpriteAnimado.h"
#include "PersonajeModelo.h"
#include "Entity.h"

class Personaje : public Entity {
public:
	Personaje(PersonajeModelo* pj);
	void agregarSprite(Sprite* sprite);
	void update();
	
	void render(Camera& camera);
	void setDestino(int xTile, int yTile);
	~Personaje();
	std::pair<int,int> posicion();
	PersonajeModelo* personajeModelo();
	void loadSprites();
	void clearSprites() ;
	void addNextSprite(AnimatedEntity*);
	void addFirstSprite(AnimatedEntity*);
	
private:
	int procesarAnimacion(int animacion);
	void velocidadRelativa(std::pair<float, float>& factor);
	void mover();
	void calcularSigTileAMover();
	void moverSprite(std::pair<float, float>& factor);
	bool isCenteredInTile();
	std::pair<int, int> tileActual;
	PersonajeModelo* modelo;
	std::vector<SpriteAnimado*> sprites;
	float velocidad;
	int estado;
	int gralStatus; //0 MOVIMIENTO, 1 ANIMACION
	std::pair<float, float> delta;
	std::pair<float, float> ePot;
	int serr;
};
#endif