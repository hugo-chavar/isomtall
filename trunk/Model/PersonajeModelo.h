//Representación del personaje en el modelo


#ifndef PERSONAJEMODELO_H
#define PERSONAJEMODELO_H

#include <utility>

class PersonajeModelo {

public:
	PersonajeModelo();
	PersonajeModelo(int ActualX, int ActualY);
	void setCurrent(int x, int y);
	void setDestino(int x, int y);
	int mover(std::pair<int, int>& destino);	//Falta agregar velocidad y orientaciones, y el mapa
	~PersonajeModelo();
private:
	std::pair<int, int> current;
	std::pair<int, int> target;
	int* xPath;
	int* yPath;
	int posMov;
	int caminoSize;
};

#endif