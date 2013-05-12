#include <cstdlib>
#include "Logger.h"
#include "PersonajeModelo.h"
#include "Pathfinder.h"
#include "PersonajeConstantes.h"
#include "Game.h"

using namespace common;

PersonajeModelo::PersonajeModelo() {
	this->initialize(DEFAULT_MAIN_CHARACTER_X, DEFAULT_MAIN_CHARACTER_Y);
}

PersonajeModelo::PersonajeModelo(int ActualX, int ActualY) {
	this->initialize(ActualX, ActualY);
}

void PersonajeModelo::initialize(int pos_x, int pos_y) {
	current.first = pos_x;
	current.second = pos_y;
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
	this->setIsActivo(true);
	orientacion = SUR;
	this->setAnimating(false);
	animacionActual = SIN_CAMBIO;
}


void PersonajeModelo::setCurrent(int x, int y) {
	current.first = x;
	current.second = y;
}

void PersonajeModelo::setAnimation(AnimatedEntity* ae) {
	animation = ae;
}

void PersonajeModelo::atacar() {
	animacionActual = ATACAR;
	targetParcial = target = current;
	if (estado >= MOVIMIENTO) {
		estado = estado + ATACAR - MOVIMIENTO;
	} else {
		estado = estado + ATACAR - PARADO;
	}
}

bool PersonajeModelo::estaAnimandose() {
	return this->isAnimating;
}

void PersonajeModelo::animar(char opcion) {
	if ((isActivo)&&(animacionActual == SIN_CAMBIO)) {
		
		switch (opcion) {
		case 'a': {
			this->setAnimating(true);
			this->atacar();
				  }
		default:;
		}
	}
}

void PersonajeModelo::terminarAnimacion() {
	this->setAnimating(false);
	estado = estado - animacionActual + PARADO;
	animacionActual = SIN_CAMBIO;
}


bool PersonajeModelo::hasDirectoryRemaining(){
	return animation->hasNextDir();
}

AnimatedEntity* PersonajeModelo::getAnimation() {
	return animation;
}

string PersonajeModelo::nextDirectory() {
	return animation->nextDirectory();
}

int PersonajeModelo::fps() {
	return animation->fps();
}

int PersonajeModelo::delay() {
	return animation->delay();
}

void PersonajeModelo::setDestino(int x, int y) {
	if ((isActivo)&&(!this->estaAnimandose())) {
		target.first = x;
		target.second = y;
		targetParcial.first = x;
		targetParcial.second = y;
	}
}

void PersonajeModelo::setEstado(int state) {
	estado = state;
}

void PersonajeModelo::setIsActivo(bool active) {
		isActivo = active;
}

//void PersonajeModelo::setIsActivo() {
//	activarDesactivar();
//	if (isActivo) {
//		isActivo = false;
//	} else {
//		isActivo = true;
//	}
//}
//
//void PersonajeModelo::activarDesactivar() {
//	if ((this->estaAnimando())) {
//		this->terminarAnimacion();
//	}
//	if (isActivo) {
//		if (estado >= MOVIMIENTO) {
//			estado = estado + FREEZAR - MOVIMIENTO;
//		} else {
//			estado = estado + FREEZAR - PARADO;
//		}
//		targetParcial = target = current;
//	} else {
//		estado = estado - FREEZAR + PARADO;
//	}
//}


bool PersonajeModelo::getIsActivo() {
	return isActivo;
}

void PersonajeModelo::setVelocidad(float vel) {
	velocidad = vel;
}

//void PersonajeModelo::getCurrent(std::pair<int, int>& actual) {
//	actual.first = current.first;
//	actual.second = current.second;
//}

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

int PersonajeModelo::mover(std::pair<int, int>& destino, float& velocidadAni) {
	Pathfinder pathF;
	int cambio = SIN_CAMBIO;
	double coste = 0;
	float costeF = 0;

	if (target == current) {
		return (this->quedarseQuieto(velocidadAni));
	}
	if (esNecesarioCalcularNuevoPath()) {
		posMov = 0;
		caminoSize = 0;
		limpiarPath();
		targetParcial.first = target.first;
		targetParcial.second = target.second;
		caminoSize = pathF.getPath(current.first, current.second, targetParcial.first, targetParcial.second, xPath, yPath);
		if (caminoSize == 0) { //Si no se tiene que mover, seteo el destino en los parciales
			target.first = targetParcial.first;
			target.second = targetParcial.second;
		}
		if (caminoSize <  0) {
			return (this->quedarseQuieto(velocidadAni));
		}
	}
	if (posMov < caminoSize) {
		this->moverse(destino, velocidadAni);
	} else {
		return (this->quedarseQuieto(velocidadAni));
	}
	cambio = ESTADO_MOVIMIENTO;
	estado = cambiarEstado(destino.first, destino.second, cambio);
	return estado;
}

bool PersonajeModelo::esNecesarioCalcularNuevoPath(){
	if ((xPath == NULL)&&(yPath == NULL)) { //Si no hay camino seteado
		return true;
	}
	if ((xPath[caminoSize-1]!=targetParcial.first)||(yPath[caminoSize-1]!=targetParcial.second)) { //Si cambio de destino durante el movimiento
		return true;
	}
	if ((posMov==caminoSize)&&((target.first!=targetParcial.first)||(target.second!=targetParcial.second))) { //Si completo el primer pedazo del camino
		return true;
	}
	return false;
}

void PersonajeModelo::moverse(std::pair<int, int>& destino, float &velocidad){
	double coste = 0;
	float costeF = 0;

	destino.first = xPath[posMov];
	destino.second = yPath[posMov];
	coste = (Game::instance().world())->cost(xPath[posMov], yPath[posMov]);
	costeF = (float) coste;
	velocidad = ((this->velocidad)*costeF);
	posMov++;
}

int PersonajeModelo::quedarseQuieto(float &velocidad){
	int cambio = SIN_CAMBIO;
	cambio = this->siCaminaDetenerse();
	estado = cambiarEstado(targetParcial.first, targetParcial.second, cambio);
	velocidad = 0;
	return estado;
}

void PersonajeModelo::limpiarPath() {
	if (xPath != NULL) {
		delete [] xPath;
		xPath = NULL;
	}
	if (yPath != NULL) {
		delete [] yPath;
		yPath = NULL;
	}
}

int PersonajeModelo::cambiarEstado(int x, int y, int cambio) {
	if (cambio == SIN_CAMBIO) {
		return estado;
	}
	if((x==current.first)&&(y==current.second)&&(cambio==ESTADO_MOVIMIENTO)){
		return (estado-FACTOR_ORIENTACION);
	}
	orientacion = obtenerOrientacion(x, y);
	switch (orientacion) {
	case NORTE: return CAMINANDO_N;
	case NORESTE: return CAMINANDO_NE;
	case NOROESTE: return CAMINANDO_NOE;
	case SUR: return CAMINANDO_S;
	case SUDESTE: return CAMINANDO_SE;
	case SUDOESTE: return CAMINANDO_SOE;
	case ESTE: return CAMINANDO_E;
	case OESTE: return CAMINANDO_O;
	default: return ESTADO_ERROR;
	}
}

int PersonajeModelo::obtenerOrientacion(int x, int y) {
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
	return ESTADO_ERROR;
}

PersonajeModelo::~PersonajeModelo(){
	//if (xPath != NULL) {
	//	delete [] xPath;
	//	xPath = NULL;
	//}
	//if (yPath != NULL) {
	//	delete [] yPath;
	//	yPath = NULL;
	//}
	this->limpiarPath();
	if (this->vision)
		delete this->vision;
}

void PersonajeModelo::setName(string nombreJugador) {
	this->name = nombreJugador;
}

string PersonajeModelo::getName() {
	return this->name;
}

std::pair<int, int> PersonajeModelo::getPosition() {
	return this->current;
}

void PersonajeModelo::createVision(int range) {
	this->vision = new CharacterVision();
	this->vision->setRangeVision(range);
	this->vision->setPosition(this->getPosition());
	this->vision->initialize();
}

CharacterVision* PersonajeModelo::getVision() {
	return this->vision;
}

void PersonajeModelo::update() {
	this->vision->updatePosition(this->getPosition());
}

std::pair<int, int> PersonajeModelo::obtenerFrentePersonaje() {
	std::pair <int, int> posicionSig = current;

	if ((orientacion == NORTE) || (orientacion == NORESTE) || (orientacion == ESTE))
		posicionSig.second--;
	else if ((orientacion == SUDOESTE) || (orientacion == OESTE) || (orientacion == SUR))
		posicionSig.second++;

	if ((orientacion == NORTE) || (orientacion == NOROESTE) || (orientacion == OESTE))
		posicionSig.first--;
	else if ((orientacion == ESTE) || (orientacion == SUDESTE) || (orientacion == SUR))
		posicionSig.first++;
	
	return posicionSig;

	//if (orientacion == NORTE) {
	//	posicionSig.first = current.first - 1;
	//	posicionSig.second = current.second - 1;
	//	return posicionSig;
	//}
	//if (orientacion == NORESTE) {
	//	posicionSig.first = current.first;
	//	posicionSig.second = current.second - 1;
	//	return posicionSig;
	//}
	//if (orientacion == ESTE) {
	//	posicionSig.first = current.first + 1;
	//	posicionSig.second = current.second - 1;
	//	return posicionSig;
	//}
	//if (orientacion == NOROESTE) {
	//	posicionSig.first = current.first - 1;
	//	posicionSig.second = current.second;
	//	return posicionSig;
	//}
	//if (orientacion == SUDESTE) {
	//	posicionSig.first = current.first + 1;
	//	posicionSig.second = current.second;
	//	return posicionSig;
	//}
	//if (orientacion == OESTE) {
	//	posicionSig.first = current.first - 1;
	//	posicionSig.second = current.second + 1;
	//	return posicionSig;
	//}
	//if (orientacion == SUDOESTE) {
	//	posicionSig.first = current.first;
	//	posicionSig.second = current.second + 1;
	//	return posicionSig;
	//}
	//if (orientacion == SUR) {
	//	posicionSig.first = current.first + 1;
	//	posicionSig.second = current.second + 1;
	//	return posicionSig;
	//}
}

void PersonajeModelo::setAnimating(bool value) {
	this->isAnimating = value;
}