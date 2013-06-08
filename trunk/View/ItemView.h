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
	string name;

public:

	string getName();
	ItemView(int tileX,int tileY,Sprite* spriteCargado,Sprite * _hiddenSprite,std::string state,string _name);
	~ItemView();
	void update();
	void render(Camera& camera);
	void changeState();
	void uncover();
	void revive(char _hidden);
	bool isAlive();
	void kill();
};

