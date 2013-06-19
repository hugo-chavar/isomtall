#ifndef DANIABLE_H
#define DANIABLE_H

#include "Positionable.h"
#include "Entity.h"
#include "Sprite.h"

class Daniable: public Positionable, public Entity
{
public:
	Daniable(void);
	~Daniable(void);
	Daniable(int tileX,int tileY,Sprite* spriteCargado);
	virtual void recibirDano(float dano);
	bool isAlive();
	virtual bool isWood();

protected:
	float vidaActual;
};

#endif

