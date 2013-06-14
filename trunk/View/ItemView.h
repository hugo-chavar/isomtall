#pragma once
#include "Entity.h"


class ItemView: public Entity
{

private:

	//unsigned state;
	//bool hidden;
	//bool alive;
	SDL_Rect hiddenSpriteRect;
	Sprite * hiddenSprite;
	void setHiddenRectangle(std::pair<int, int> pos, Sprite* sprite );
	//string name;

public:
	//string getName();
	ItemView(int tileX,int tileY,Sprite* spriteCargado,Sprite * _hiddenSprite,unsigned _state,string _name);
	~ItemView();
	void update();
	void render(Camera& camera);
	bool isHidden();
	void uncover();
	void revive(unsigned _state,pair <int,int> pos);
	bool isAlive();
	void kill();
};

