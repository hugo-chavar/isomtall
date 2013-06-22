#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <vector>
#include "Sprite.h"
#include "SpriteAnimado.h"
#include "PersonajeModelo.h"
#include "Entity.h"
#include "Daniable.h"
#include "Constants.h"
#include "SDL_ttf.h"
#include "Weapon.h"
#include "Hechizo.h"

class Personaje : public Daniable {
public:
	Personaje(PersonajeModelo*,std::string char_id);
	~Personaje();
	
	//----- Getters/Setters methods -----
	PersonajeModelo* personajeModelo();
	void setAnimating(bool value);
	void setActive(bool value);
	bool isActive();
	void setPixelPosition(std::pair<int, int> pixel);
	std::pair<int, int> getPixelPosition();
	std::pair<int,int> getRealPixelPosition();
	int getCurrentSpritePosition();
	void setCurrentSpritePosition(int pos);
	void setPlayerName(std::string name);
	std::string getPlayerName();
	void setFont(TTF_Font* font);
	float getShieldResistance();
	std::string getCharacterId();
	std::pair<int,int> getPosicionActualEnTiles();
	void setCurrentEnemy(int tileX, int tileY);
	void setDestino(int xTile, int yTile);
	std::vector<unsigned int>& getAnimationFxRelation();
	std::string getSpellActual();
	std::vector<Weapon*>& getWeapons();
	void setCenteredInTile(bool centroTile);
	bool isCenteredInTile();
	void setSelectedWeapon(unsigned value);
	unsigned getSelectedWeapon();
	void setHechizo(Hechizo* hechizo);
	void setProtTime(float time);
	void setProtCost(float cost);
	void setInvulnerable(bool inv);
	bool hasIceSpell();
	void setIceSpell(bool value);

	//----- Simulation methods -----
	void update();
	void updateSinglePlayer();
	void render(Camera& camera);

	//----- Server updating methods -----
	std::string updateToString();
	void updateFromString(std::string data);
	std::string initToString();
	void initFromString(std::string data);
	std::string idToString();
	//----- Sprite loading methods -----
	void loadSprites();
	void clearSprites() ;
	void addNextSprite(AnimatedEntity*);
	void addFirstSprite(AnimatedEntity*);
	//----- Functional methods -----
	
	bool hasValidSprite();
	bool isThisSpriteValid(int currentAnimationNumber);
	bool repositionToStrike();
	void increaseSpeed(float factor);
	void heal();
	void rechargeMagic();
	void recibirDano(float dano);
	bool isItem();
	void eatIfItem(std::pair<int, int> destino);
	void setShield(float resistance,float absortion);
	bool hasShield();
	bool useMagic(float usedMagic); //Devuelve si pudo usar esa cantidad de magia
	void loadWeapons();
	bool isValidWeapon();
	bool isWood();
	void processKeyCommand(char animation);
	void invocarMagia();
	void detenerMagia();

	
private:
	//----- Private methods -----
	int calculateSpritePosition(int currentAnimationNumber);
	void calcularSigTileAMover();
	void animar();
	void atacar();
	void detenerAnimacion();
	void createLabelName();
	void createStatsBar();
	void updateStatsBar();
	void renderStatsBars(Camera& camera);
	void calcularvelocidadRelativa(std::pair<float, float>& factor);
	void mover();
	void moverSprite(std::pair<float, float>& factor);
	void moverSpriteEnX();
	void moverSpriteEnY();
	void perseguirEnemigo();
	bool isCenteredInTileInSinglePlayer();
	void createOnPJInfo();
	void renderProtHalo(Camera& camera);
	void rendertShield(Camera& camera);
	void manejarDano(float dano);
	void stopProtectionSpell();
	void updateProtectionSpell();
	void reset();
	void changeWeapon();

	//----- Attributes -----
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
	float shieldResistance;
	int currentSpritePosition;
	std::pair<float, float> delta; //Cuanto recorrio en x y en y del movimiento
	std::pair<float, float> ePot; //Cuanto se mueve por ciclo en x y en y
	int serr; //variable usada para coordinar el movimiento en x y en y en la diagonal
	bool centeredInTile;
	std::string playerName;
	bool active;
	TTF_Font* font;
	std::vector<unsigned int> animationFxRelation;
	Daniable* currentEnemy;
	float shieldAbsortion;
	SDL_Surface* ProtectionHalo;
	SDL_Surface* tShield;
	bool invulnerable;
	Hechizo* hechizoActual;
	float protTime;
	float protCost;
	std::string hechizoActualMulti;
	std::string character_id;
	unsigned selectedWeapon;
	std::vector<Weapon*> weapons;
	bool iceSpell;
	bool wandSpell;

};
#endif