//Representación del personaje en el modelo


#ifndef PERSONAJEMODELO_H
#define PERSONAJEMODELO_H

#include <utility>
#include "Stage.h"

namespace model {
class PersonajeModelo {

public:
	PersonajeModelo();
	PersonajeModelo(int ActualX, int ActualY, int estado, Stage* worldModel);
	void setStage(Stage* worldModel);
	void setEstado(int state);
	void setCurrent(int x, int y);
	void setDestino(int x, int y);
	int mover(std::pair<int, int>& destino);	//Devuelve el estado, que son las orientaciones
	~PersonajeModelo();
private:
	std::pair<int, int> current;
	std::pair<int, int> target;
	int* xPath;
	int* yPath;
	int posMov;
	int caminoSize;
	int estado;
	Stage* mundo;
};
}

#endif