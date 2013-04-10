//Representación del personaje en el modelo


#ifndef PERSONAJEMODELO_H
#define PERSONAJEMODELO_H

#include <utility>
#include "Stage.h"
#include "Constants.h"

namespace model {
class PersonajeModelo {

public:
	PersonajeModelo();
	PersonajeModelo(int ActualX, int ActualY, int estado, Stage* worldModel, MainCharacter *datosPersonaje);
	void setStage(Stage* worldModel);
	void setEstado(int state);
	void setCurrent(int x, int y);
	void setDestino(int x, int y);
	void setVelocidad(int vel);
	int mover(std::pair<int, int>& destino, int &velocidad);	//Devuelve el estado, que son las orientaciones. Devuelve la velocidad
	~PersonajeModelo();											//del movimiento, la corrección de la vista no se la hace
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
	int velocidad;
	Stage* mundo;
	MainCharacter *_datosPersonaje;
};
}

#endif