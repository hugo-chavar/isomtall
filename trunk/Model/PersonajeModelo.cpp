#include <cstdlib>
#include "Logger.h"
#include "PersonajeModelo.h"
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

using namespace common;


PersonajeModelo::PersonajeModelo() {
	current.first = DEFAULT_MAIN_CHARACTER_X;
	current.second = DEFAULT_MAIN_CHARACTER_Y;
	target.first = current.first;
	target.second = current.second;
	targetParcial.first = current.first;
	targetParcial.second = current.second;
	xPath = NULL;
	yPath = NULL;
	posMov = 0;
	caminoSize = 0;
	estado = PARADO_S;
	velocidad = DEFAULT_MAIN_CHARACTER_SPEED;
}

PersonajeModelo::PersonajeModelo(int ActualX, int ActualY) {
	current.first = ActualX;
	current.second = ActualY;
	target.first = current.first;
	target.second = current.second;
	targetParcial.first = current.first;
	targetParcial.second = current.second;
	xPath = NULL;
	yPath = NULL;
	posMov = 0;
	caminoSize = 0;
	this->estado = PARADO_S;
	//this->velocidad = velocidad;
}


void PersonajeModelo::setCurrent(int x, int y) {
	current.first = x;
	current.second = y;
}

void PersonajeModelo::animation(AnimatedEntity* ae) {
	_animation = ae;
}

void PersonajeModelo::animar() {
	this->setDestino(5,5);
}

bool PersonajeModelo::hasDirectoryRemaining(){
	return _animation->hasNextDir();
}

AnimatedEntity* PersonajeModelo::animation() {
	return _animation;
}

string PersonajeModelo::nextDirectory() {
	return _animation->nextDirectory();
}

int PersonajeModelo::fps()
{
	return _animation->fps();
}

int PersonajeModelo::delay()
{
	return _animation->delay();
}

void PersonajeModelo::setDestino(int x, int y) {
	target.first = x;
	target.second = y;
	targetParcial.first = x;
	targetParcial.second = y;
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

int PersonajeModelo::getEstado() {
	return estado;
}

float PersonajeModelo::getVelocidad() {
	return velocidad;
}

int PersonajeModelo::siCaminaDetenerse() {
	int cambio = SIN_CAMBIO;
	
	if ((estado<10) || (estado>19)) { //si esta caminando
		cambio = ESTADO_MOVIMIENTO; //que se quede quieto
	}
	return cambio;
}

int PersonajeModelo::mover(std::pair<int, int>& destino, float& velocidad) {
	Pathfinder pathF;
	int cambio = SIN_CAMBIO;
	double coste;
	float costeF = 0;

	if (target == current) {
		cambio = this->siCaminaDetenerse();
		estado = cambiarEstado(current.first, current.second, cambio);
		velocidad = 0;
		return estado;
	}
	if (((xPath == NULL)&&(yPath == NULL))||((xPath[caminoSize-1]!=targetParcial.first)||(yPath[caminoSize-1]!=targetParcial.second))||((posMov==caminoSize)&&((target.first!=targetParcial.first)||(target.second!=targetParcial.second)))) {
		posMov = 0;
		caminoSize = 0;
		if (xPath != NULL) {
			delete [] xPath;
			xPath = NULL;
		}
		if (yPath != NULL) {
			delete [] yPath;
			yPath = NULL;
		}
		targetParcial.first = target.first;
		targetParcial.second = target.second;
		caminoSize = pathF.getPath(current.first, current.second, targetParcial.first, targetParcial.second, xPath, yPath);
		if (caminoSize == 0) {
			target.first = targetParcial.first;
			target.second = targetParcial.second;
		}
		if (caminoSize <  0) {
			cambio = this->siCaminaDetenerse();
			estado = cambiarEstado(current.first, current.second, cambio);
			velocidad = 0;
			return estado;
		}
	}
	if (posMov < caminoSize) {
		destino.first = xPath[posMov];
		destino.second = yPath[posMov];
		coste = (Game::instance().world())->cost(xPath[posMov], yPath[posMov]);
		costeF = (float) coste;
		velocidad = ((this->velocidad)*costeF);
		posMov++;
	} else {
		cambio = this->siCaminaDetenerse();
		estado = cambiarEstado(targetParcial.first, targetParcial.second, cambio);
		velocidad = 0;
		return estado;
	}
	cambio = ESTADO_MOVIMIENTO;
	estado = cambiarEstado(destino.first, destino.second, cambio);
	return estado;
}

int PersonajeModelo::cambiarEstado(int x, int y, int cambio) {
	if (cambio == SIN_CAMBIO) {
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
