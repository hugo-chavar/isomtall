#pragma once

#include <string>
#include "Sprite.h"
#include "Camera.h"

using namespace view;

class Entity
{
private:
	SDL_Rect spriteRect;
	Sprite * sprite;
	SDL_Rect posicionIsometricaPorTiles(int tileX,int tileY,Sprite* sprite);

public:

	Entity(int tileX,int tileY,Sprite* spriteCargado);//(int tileX,int tileY,std::string path,std::string nombre,int nroFrames, int relx,int rely);
	void update();
	void render(Camera& camera);
	~Entity(void);
};

