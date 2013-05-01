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
	//determina en que posicion del vector de sprites esta el sprite del estado actual
	int procesarAnimacion(int animacion);
	void calcularvelocidadRelativa(std::pair<float, float>& factor);
	void mover();
	void calcularSigTileAMover();
	//realiza el desplazamiento en x y en y del sprite, de un tile a otro
	void moverSprite(std::pair<float, float>& factor);
	void moverSpriteEnX(std::pair<float, float>& factor);
	void moverSpriteEnY(std::pair<float, float>& factor);
	bool isCenteredInTile();

	std::pair<int, int> tileActual;
	PersonajeModelo* modelo;
	std::vector<SpriteAnimado*> sprites;
	float velocidad; //velocidad actual
	int estado; //estado actual, si se mueve y en que direcci�n
	int gralStatus; //0 MOVIMIENTO, 1 ANIMACION
	std::pair<float, float> delta; //Cuanto recorrio en x y en y del movimiento
	std::pair<float, float> ePot; //Cuanto se mueve por ciclo en x y en y
	int serr; //variable usada para coordinar el movimiento en x y en y en la diagonal
};
#endif