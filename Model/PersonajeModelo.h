//Representación del personaje en el modelo


#ifndef PERSONAJEMODELO_H
#define PERSONAJEMODELO_H

#include <utility>
#include "Constants.h"
#include "DirList.h"
#include "AnimatedEntity.h"

namespace model {
class PersonajeModelo {

public:
	PersonajeModelo();
	//PersonajeModelo(MainCharacter& datosPersonaje);
	PersonajeModelo(int ActualX, int ActualY);//, int estado, float velocidad, MainCharacter *datosPersonaje
	void setEstado(int state);
	void setCurrent(int x, int y);
	void setDestino(int x, int y);
	void setVelocidad(float vel);
	void getCurrent(std::pair<int, int>& actual);
	int getEstado();
	float getVelocidad();
	int mover(std::pair<int, int>& destino, float &velocidad);	//Devuelve el estado, que son las orientaciones. Devuelve la velocidad
	~PersonajeModelo();											//del movimiento, la corrección de la vista no se la hace
	void loadSpritesDir();
	void addRefToSprite(string);
	void setDirectory(string);
	void animation(AnimatedEntity*);
	AnimatedEntity* animation();
	int fps();
	int delay();
private:
	int cambiarEstado(int x, int y, int cambio);
	int comparadorOctario(int x, int y);
	std::pair<int, int> current;
	std::pair<int, int> target;
	int* xPath;
	int* yPath;
	int posMov;
	int caminoSize;
	int estado;
	float velocidad;

	DirList spritesMainDir;
	list <DirList*> spritesRefs ;
	AnimatedEntity * _animation;

};
}

#endif