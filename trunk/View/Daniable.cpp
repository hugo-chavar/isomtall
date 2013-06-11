#include "Daniable.h"

Daniable::Daniable()
{
	vidaActual = 0;
}

Daniable::~Daniable()
{

}

void Daniable::recibirDano(float dano)
{
	//Metodo Abstracto
}
//
//std::pair<int, int> Daniable::getPosicionActualEnTiles() {
//	return tileActual;
//}

bool Daniable::isAlive() {
	if (vidaActual > 0) {
		return true;
	}
	return false;
}