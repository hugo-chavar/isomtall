#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>
#include "GameDependent.h"
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
	EXPLOSIVE_INACTIVE,
	EXPLOSIVE_FLYING,
	EXPLOSIVE_EXPLOSION_COUNTDOWN,
	EXPLOSIVE_BOUNCING,
	EXPLOSIVE_BURNING,
	EXPLOSIVE_EXPLOSION,
	EXPLOSIVE_DUST_IN_THE_WIND,
	ITEM_WAITING_REGENERATION

};

using namespace view;

class Entity: public GameDependent {
protected:
	SDL_Rect spriteRect;
	Sprite * sprite;
	SDL_Rect posicionIsometricaPorTiles(int tileX,int tileY,Sprite* sprite);
	bool fogged;
	float endStatusTime;
	int freezedSpriteState;
	unsigned status;
	std::string name;
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
	void setEndStatusTime(float endTime);
	void decreaseEndStatusTime();
	void iceUp(float seconds);
	virtual bool isItem();
	bool needsCountDown();
	bool needsToBeCleaned();
	std::string statusToString();
	void setSprite(Sprite* sprite);
	Sprite* getSprite();
	unsigned getTileWidth();
	unsigned getTileHeight();
	void updateRectanglePosition(int x, int y);
	virtual bool isAlive();
	std::string getName();
	void setName(std::string value);
};

#endif // _ENTITY_H_