#ifndef DANIABLE_H
#define DANIABLE_H

#include "Positionable.h"

class Daniable: public Positionable
{
public:
	Daniable(void);
	~Daniable(void);
	virtual void recibirDano(float dano);
	bool isAlive();
	virtual bool isWood();

protected:
	float vidaActual;
};

#endif

