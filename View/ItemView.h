#pragma once
#include "Entity.h"

class ItemView: public Entity
{

private:

	bool hidden;
	bool alive;
	SDL_Rect hiddenSpriteRect;
	Sprite * hiddenSprite;
	void setHiddenRectangle(std::pair<int, int> pos, Sprite* sprite );

public:

	ItemView(int tileX,int tileY,Sprite* spriteCargado,Sprite * _hiddenSprite,std::string state);
	~ItemView();
	void update();
	void render(Camera& camera);
	void changeState();
};

