#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <vector>
#include "Sprite.h"
#include "SpriteAnimado.h"
#include "PersonajeModelo.h"
#include "Entity.h"
#include "Daniable.h"
#include "Mutex.h"
#include "Constants.h"
#include "SDL_ttf.h"

class Personaje : public Entity, public Daniable {
public:
	Personaje(PersonajeModelo* pj);
	~Personaje();
	void update();
	void render(Camera& camera);
	PersonajeModelo* personajeModelo();
	void loadSprites();
	void clearSprites() ;
	void addNextSprite(AnimatedEntity*);
	void addFirstSprite(AnimatedEntity*);
	//std::pair<int,int> getPosicionEnTiles();
	//std::pair<int,int> getPosicionAnteriorEnTiles();
	//void setFreezed(bool value);
	void setAnimating(bool value);
	std::string updateToString();
	void updateFromString(std::string data);
	std::string initToString();
	void initFromString(std::string data);
	void setPixelPosition(std::pair<int, int> pixel);
	std::pair<int, int> getPixelPosition();
	int getCurrentSpritePosition();
	void setCurrentSpritePosition(int pos);
	void setPlayerName(std::string name);
	std::string getPlayerName();
	bool isCenteredInTile();
	std::string idToString();
	void setActive(bool value);
	bool isActive();
	//void setDestino(int xTile, int yTile);
	void setFont(TTF_Font* font);
	bool hasValidSprite();

private:
	int calculateSpritePosition(int currentAnimationNumber);
	//void calcularvelocidadRelativa(std::pair<float, float>& factor);
	void mover();
	void calcularSigTileAMover();
	//realiza el desplazamiento en x y en y del sprite, de un tile a otro
	//void moverSprite(std::pair<float, float>& factor);
	//void moverSpriteEnX();
	//void moverSpriteEnY();
	void setCenteredInTile(bool centroTile);
	void animar();
	void detenerAnimacion();
	void createLabelName();
	void createStatsBar();
	void updateStatsBar();
	void renderStatsBars(Camera& camera);
	//std::pair<int, int> tileActual;
	SDL_Surface* labelName;
	SDL_Surface* magicBarPos;
	SDL_Surface* magicBarNeg;
	SDL_Surface* lifeBarG;
	SDL_Surface* lifeBarR;
	int barWidth;
	PersonajeModelo* modelo;
	std::vector<SpriteAnimado*> sprites;
	float velocidad; //velocidad actual
	float magiaActual;
	int currentSpritePosition;
	std::pair<float, float> delta; //Cuanto recorrio en x y en y del movimiento
	std::pair<float, float> ePot; //Cuanto se mueve por ciclo en x y en y
	int serr; //variable usada para coordinar el movimiento en x y en y en la diagonal
	bool centeredInTile;
	std::string playerName;
	bool active;
	TTF_Font* font;
};
#endif