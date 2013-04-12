#include "PersonajeModelo.h"
#include <cstdlib>
#include "Pathfinder.h"
#include "PersonajeConstantes.h"
#include "Game.h"

#define NORTE 0
#define NORESTE 1
#define NOROESTE 2
#define SUR 3
#define SUDESTE 4
#define SUDOESTE 5
#define ESTE 6
#define OESTE 7

using namespace model;

PersonajeModelo::PersonajeModelo() {
	current.first = DEFAULT_MAIN_CHARACTER_X;
	current.second = DEFAULT_MAIN_CHARACTER_Y;
	target.first = current.first;
	target.second = current.second;
	xPath = NULL;
	yPath = NULL;
	posMov = 0;
	caminoSize = 0;
	estado = PARADO_S;
	velocidad = DEFAULT_MAIN_CHARACTER_SPEED;
}

PersonajeModelo::PersonajeModelo(int ActualX, int ActualY, int estado, MainCharacter *datosPersonaje) {
	current.first = ActualX;
	current.second = ActualY;
	target.first = current.first;
	target.second = current.second;
	xPath = NULL;
	yPath = NULL;
	posMov = 0;
	caminoSize = 0;
	_datosPersonaje = datosPersonaje;
	this->estado = estado;
	this->velocidad = datosPersonaje->speed();
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


void PersonajeModelo::setVelocidad(float vel) {
	velocidad = vel;
}

void PersonajeModelo::getCurrent(std::pair<int, int>& actual) {
	actual.first = current.first;
	actual.second = current.second;
}

int PersonajeModelo::mover(std::pair<int, int>& destino, float& velocidad) {
	Pathfinder pathF;
	int cambio = SIN_CAMBIO;
	double coste;

	if ((estado<10) || (estado>19)) {
		cambio = ESTADO_MOVIMIENTO;
		estado = cambiarEstado(current.first, current.second, cambio);
		velocidad = 0;
		return estado;
	}
	if (target == current) {
		if ((estado<10) || (estado>19)) {
			cambio = ESTADO_MOVIMIENTO;
		}
		estado = cambiarEstado(current.first, current.second, cambio);
		velocidad = 0;
		return estado;
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
		caminoSize = pathF.getPath(current.first, current.second, target.first, target.second, xPath, yPath);
		if (caminoSize <  0) {
			if ((estado<10) || (estado>19)) {
				cambio = ESTADO_MOVIMIENTO;
			}
			estado = cambiarEstado(current.first, current.second, cambio);
			velocidad = 0;
			return estado;
		}
	}
	if (posMov < caminoSize) {
		destino.first = xPath[posMov];
		destino.second = yPath[posMov];
		coste = Game::instance().world().cost(xPath[posMov], yPath[posMov]);
		coste = std::floor((this->velocidad)*coste);
		velocidad = (float) coste;
		posMov++;
	} else {
		if ((estado<10) || (estado>19)) {
			cambio = ESTADO_MOVIMIENTO;
		}
		estado = cambiarEstado(target.first, target.second, cambio);
		velocidad = 0;
		return estado;
	}
	cambio = ESTADO_MOVIMIENTO;
	estado = cambiarEstado(destino.first, destino.second, cambio);
	return estado;
}

int PersonajeModelo::cambiarEstado(int x, int y, int cambio) {
	if (cambio==SIN_CAMBIO) {
		return estado;
	}
	if((x==current.first)&&(y==current.second)&&(cambio==ESTADO_MOVIMIENTO)){
		return (estado-FACTOR_ORIENTACION);
	}
	switch (comparadorOctario(x, y)) {
	case NORTE: return CAMINANDO_N;
	case NORESTE: return CAMINANDO_NE;
	case NOROESTE: return CAMINANDO_NOE;
	case SUR: return CAMINANDO_S;
	case SUDESTE: return CAMINANDO_SE;
	case SUDOESTE: return CAMINANDO_SOE;
	case ESTE: return CAMINANDO_E;
	case OESTE: return CAMINANDO_O;
	default: return ERROR;
	}
}

int PersonajeModelo::comparadorOctario(int x, int y) {
	int xCurr = current.first;
	int yCurr = current.second;
	
	if ((x < xCurr)&&(y < yCurr)) {
		return NORTE;
	}
	if ((x == xCurr)&&(y < yCurr)) {
		return NORESTE;
	}
	if ((x > xCurr)&&(y < yCurr)) {
		return ESTE;
	}
	if ((x < xCurr)&&(y == yCurr)) {
		return NOROESTE;
	}
	if ((x > xCurr)&&(y == yCurr)) {
		return SUDESTE;
	}
	if ((x < xCurr)&&(y > yCurr)) {
		return OESTE;
	}
	if ((x == xCurr)&&(y > yCurr)) {
		return SUDOESTE;
	}
	if ((x > xCurr)&&(y > yCurr)) {
		return SUR;
	}
	return ERROR;
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