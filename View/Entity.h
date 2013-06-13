#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>
#include "Sprite.h"
#include "Camera.h"
#include "Surface.h"

enum entityStatus_t {
	HIDDEN_ITEM,
	UNCOVER_ITEM,
	DEATH_ITEM,
	REVIVE_UNCOVER_ITEM,
	REVIVE_HIDDEN_ITEM,
	ENTITY_FROZEN,
	ENTITY_BLINKING,
	ENTITY_NORMAL,
	EXPLOSIVE_AVAILABLE,
	EXPLOSIVE_EXPLOSION_COUNTDOWN,
	EXPLOSIVE_EXPLOSION,
	EXPLOSIVE_DUST_IN_THE_WIND,
	ITEM_WAITING_REGENERATION

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
	unsigned status;
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
	void setStatus(unsigned status);
	unsigned getStatus();
	bool isImmobilized();
	void setEndStatusTime(Uint32 endTime);
	void decreaseEndStatusTime();
	void iceUp(unsigned seconds);
	virtual bool isItem();
	bool needsCountDown();
	bool needsToBeCleaned();
	void setSprite(Sprite* sprite);
	Sprite* getSprite();
	float getDeltaTime();
	unsigned getTileWidth();
	unsigned getTileHeight();
};

#endif // _ENTITY_H_