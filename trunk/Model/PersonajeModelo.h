#ifndef PERSONAJEMODELO_H
#define PERSONAJEMODELO_H

#include <utility>
#include "Constants.h"
#include "DirList.h"
#include "AnimatedEntity.h"


class PersonajeModelo {

public:
	PersonajeModelo();
	PersonajeModelo(int ActualX, int ActualY);
	void setEstado(int state);
	void setCurrent(int x, int y);
	void setDestino(int x, int y);
	void setVelocidad(float vel);
	void getCurrent(std::pair<int, int>& actual);
	int getEstado();
	float getVelocidad();
	int mover(std::pair<int, int>& destino, float &velocidad);	//Devuelve el estado, que son las orientaciones. Devuelve la velocidad
	~PersonajeModelo();											//del movimiento, la corrección de la vista no se la hace
	string nextDirectory();
	bool hasDirectoryRemaining();
	void animation(AnimatedEntity*);
	AnimatedEntity* animation();
	int fps();
	int delay();

	void animar();
private:

	int siCaminaDetenerse();
	int cambiarEstado(int x, int y, int cambio);
	int comparadorOctario(int x, int y);	//Obtiene el sentido según el signo de x e y
	
	std::pair<int, int> current;
	std::pair<int, int> target;
	int* xPath;
	int* yPath;
	int posMov;
	int caminoSize;
	int estado;
	float velocidad;
	AnimatedEntity * _animation;
};


#endif