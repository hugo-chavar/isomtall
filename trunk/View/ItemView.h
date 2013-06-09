#pragma once
#include "Entity.h"

#ifndef item_state_t
#define item_state_t
enum item_state_t {
	HIDDEN_ITEM,
	UNCOVER_ITEM,
	DEATH_ITEM,
	REVIVE_UNCOVER_ITEM,
	REVIVE_HIDDEN_ITEM,
	REGENERATING

};
#endif

class ItemView: public Entity
{

private:

	unsigned state;
	//bool hidden;
	//bool alive;
	SDL_Rect hiddenSpriteRect;
	Sprite * hiddenSprite;
	void setHiddenRectangle(std::pair<int, int> pos, Sprite* sprite );
	string name;

public:

	string getName();
	ItemView(int tileX,int tileY,Sprite* spriteCargado,Sprite * _hiddenSprite,unsigned _state,string _name);
	~ItemView();
	void update();
	void render(Camera& camera);
	//void changeState();
	void uncover();
	void revive(unsigned _state,pair <int,int> pos);
	bool isAlive();
	void kill();
};

