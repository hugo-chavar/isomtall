#ifndef DANIABLE_H
#define DANIABLE_H

//#include <utility>
#include "Positionable.h"

class Daniable: public Positionable
{
public:
	Daniable(void);
	~Daniable(void);
	virtual void recibirDano(float dano);
	//std::pair<int, int> getPosicionActualEnTiles();
	bool isAlive();

protected:
	//std::pair<int, int> tileActual;
	float vidaActual;
};

#endif

