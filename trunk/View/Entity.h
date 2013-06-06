#pragma once

#include <string>
#include "Sprite.h"
#include "Camera.h"
#include "Surface.h"


enum entityStatus_t {
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
	SDL_Rect posicionIsometricaPorTiles(int tileX,int tileY,Sprite* sprite);
	bool fogged;
	Uint32 endStatusTime;
	int freezedSpriteState;
	entityStatus_t status;
	void renderEntitySprite(SDL_Rect rect,Sprite * _sprite,Camera& camera);

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
	void setEndStatusTime(Uint32 endTime);
	void decreaseEndStatusTime(float timeToDecrease);
	void iceUp(unsigned seconds);
};

