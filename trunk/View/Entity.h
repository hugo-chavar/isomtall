#pragma once

#include <string>
#include "Sprite.h"
#include "Camera.h"
#include "Surface.h"

enum entityStatus_t {
	//ENTITY_FOGGED,
	ENTITY_FROZEN,
	ENTITY_BLINKING,
	ENTITY_NORMAL
};

using namespace view;

class Entity
{
protected:
	SDL_Rect spriteRect;
	Sprite * sprite;
	//Surface shadow;
	SDL_Rect posicionIsometricaPorTiles(int tileX,int tileY,Sprite* sprite);
	bool fogged;
	int freezedSpriteState;
	entityStatus_t status;

public:
	Entity();
	Entity(int tileX,int tileY,Sprite* spriteCargado);
	virtual void update();
	virtual void render(Camera& camera);
	~Entity(void);
	void setFogged(bool);
	bool isFogged();
	void setRectangle(std::pair<int, int> pos, Sprite* sprite );
	void resetSpriteState();
	void setStatus(entityStatus_t status);
	entityStatus_t getStatus();
	bool isImmobilized();
};

