#pragma once

#include <string>
#include "Sprite.h"
#include "Camera.h"

#define ppty 32 //pixels por tile en y
#define pptx 64 //pixels por tile en x

using namespace view;

class Entity
{
protected:
	SDL_Rect spriteRect;
	Sprite * sprite;
	SDL_Rect posicionIsometricaPorTiles(int tileX,int tileY,Sprite* sprite);
	int orden;

public:

	Entity();
	Entity(int tileX,int tileY,Sprite* spriteCargado);
	//Entity(int tileX,int tileY,Sprite* spriteCargado,int orden);//(int tileX,int tileY,std::string path,std::string nombre,int nroFrames, int relx,int rely);
	virtual void update();
	virtual void render(Camera& camera);
	int order();
	~Entity(void);
};

