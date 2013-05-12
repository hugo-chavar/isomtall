#pragma once

#include <string>
#include "Sprite.h"
#include "Camera.h"
#include "Surface.h"

using namespace view;

class Entity
{
protected:
	SDL_Rect spriteRect;
	Sprite * sprite;
	Surface shadow;
	SDL_Rect posicionIsometricaPorTiles(int tileX,int tileY,Sprite* sprite);
	bool freezed;
	int freezedSpriteState;

public:
	Entity();
	Entity(int tileX,int tileY,Sprite* spriteCargado);
	virtual void update();
	virtual void render(Camera& camera);
	~Entity(void);
	void setFreezed(bool);
	bool isFreezed();
	SDL_Rect getSdlRect();
};

