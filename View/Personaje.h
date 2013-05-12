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
	~Personaje();
	void update();
	void render(Camera& camera);
	void setDestino(int xTile, int yTile);
	
	std::pair<int,int> posicion();
	PersonajeModelo* personajeModelo();
	void loadSprites();
	void clearSprites() ;
	void addNextSprite(AnimatedEntity*);
	void addFirstSprite(AnimatedEntity*);
	std::pair<int,int> getPosicionEnTiles();
	std::pair<int,int> getPosicionAnteriorEnTiles();
	void setFreezed(bool value);
	void setAnimating(bool value);
	//void resetSpriteState(); poner en virtual en entity para activar esto
private:
	//determina en que posicion del vector de sprites esta el sprite del estado actual
	int procesarAnimacion(int animacion);
	void calcularvelocidadRelativa(std::pair<float, float>& factor);
	void mover();
	void calcularSigTileAMover();
	//realiza el desplazamiento en x y en y del sprite, de un tile a otro
	void moverSprite(std::pair<float, float>& factor);
	void moverSpriteEnX();
	void moverSpriteEnY();
	bool isCenteredInTile();
	//void freezar();
	void animar();
	void detenerAnimacion();
	void crearNombre(string textoNombre);
	

	std::pair<int, int> tileActual;
	SDL_Surface *nombre;
	PersonajeModelo* modelo;
	std::vector<SpriteAnimado*> sprites;
	float velocidad; //velocidad actual
	int estado; //estado actual, si se mueve y en que dirección
	std::pair<float, float> delta; //Cuanto recorrio en x y en y del movimiento
	std::pair<float, float> ePot; //Cuanto se mueve por ciclo en x y en y
	int serr; //variable usada para coordinar el movimiento en x y en y en la diagonal
	//bool isAnimating;
};
#endif