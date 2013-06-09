#ifndef DANIABLE_H
#define DANIABLE_H

#include <utility>

class Daniable
{
public:
	Daniable(void);
	~Daniable(void);
	virtual void recibirDano(float dano);
	std::pair<int, int> getPosicionActualEnTiles();
	bool isAlive();

protected:
	std::pair<int, int> tileActual;
	float vidaActual;
};

#endif

