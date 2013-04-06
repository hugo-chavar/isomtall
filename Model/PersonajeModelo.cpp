#include "PersonajeModelo.h"
#include <cstdlib>
#include "Pathfinder.h"
#include "PersonajeConstantes.h"

using namespace model;

PersonajeModelo::PersonajeModelo() {
	current.first = 0;
	current.second = 0;
	target.first = current.first;
	target.second = current.second;
	xPath = NULL;
	yPath = NULL;
	posMov = 0;
	caminoSize = 0;
	estado = PARADO_S;
	mundo = NULL;
}

PersonajeModelo::PersonajeModelo(int ActualX, int ActualY, int estado, Stage* worldModel) {
	current.first = ActualX;
	current.second = ActualY;
	target.first = current.first;
	target.second = current.second;
	xPath = NULL;
	yPath = NULL;
	posMov = 0;
	caminoSize = 0;
	this->estado = estado;
	mundo = worldModel;
}

void PersonajeModelo::setCurrent(int x, int y) {
	current.first = x;
	current.second = y;
}

void PersonajeModelo::setDestino(int x, int y) {
	target.first = x;
	target.second = y;
}

void PersonajeModelo::setEstado(int state) {
	estado = state;
}

void PersonajeModelo::setStage(Stage* worldModel) {
	mundo = worldModel;
}

int PersonajeModelo::mover(std::pair<int, int>& destino) {
	Pathfinder pathF;

	if (target == current) {
		return 0;
	}
	if (((xPath == NULL)&&(yPath == NULL))||((xPath[caminoSize-1]!=target.first)&&(yPath[caminoSize-1]!=target.second))) {
		posMov = 0;
		caminoSize = 0;
		if ((xPath != NULL)&&(yPath != NULL)) {
			delete [] xPath;
			delete [] yPath;
			xPath = NULL;
			yPath = NULL;
		}
		caminoSize = pathF.getPath(current.first, current.second, target.first, target.second, mundo, xPath, yPath);
		if (caminoSize <  0) {
			return 0;
		}
	}
	if (posMov < caminoSize) {
		destino.first = xPath[posMov];
		destino.second = yPath[posMov];
		posMov++;
	} else {
		return 0;
	}
	return 1;
}

PersonajeModelo::~PersonajeModelo(){
	if (xPath != NULL) {
		delete [] xPath;
		xPath = NULL;
	}
	if (yPath != NULL) {
		delete [] yPath;
		yPath = NULL;
	}
}