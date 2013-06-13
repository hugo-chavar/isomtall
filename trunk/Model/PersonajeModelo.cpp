#include <cstdlib>
#include "Logger.h"
#include "PersonajeModelo.h"
#include "Pathfinder.h"
#include "PersonajeConstantes.h"
#include "../Common/stringUtilities.h"
#include "OpcionesJuego.h"
#include "Game.h"

using namespace common;

PersonajeModelo::PersonajeModelo() {
	this->initialize(DEFAULT_MAIN_CHARACTER_X, DEFAULT_MAIN_CHARACTER_Y);
}

PersonajeModelo::PersonajeModelo(int ActualX, int ActualY) {
	this->initialize(ActualX, ActualY);
}

PersonajeModelo& PersonajeModelo::operator=(const PersonajeModelo &source){
	//this->current = source.current;
	this->setPosition(source.position);
	this->target = source.target;
	this->targetParcial = source.targetParcial;
	this->xPath = source.xPath;
	this->yPath = source.yPath;
	this->posMov = source.posMov;
	this->caminoSize = source.caminoSize;
	this->velocidad = source.velocidad;
	this->orientacion = source.orientacion;
	this->animacionActual = source.animacionActual;
	this->estado = source.estado;
	this->animation = source.animation;
	this->isActivo = source.isActivo;
	this->isAnimating = source.isAnimating;
	this->vision = NULL;
	return *this;
	this->vidaMaxima = source.vidaMaxima;
}

void PersonajeModelo::initialize(int pos_x, int pos_y) {
	this->setPosition(std::make_pair(pos_x, pos_y));
	this->target = this->getPosition();
	this->targetParcial = this->target;
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
	this->vision = NULL;
	vidaMaxima = DEFAULT_CHARACTER_MAX_LIFE;
	magiaMaxima = DEFAULT_CHARACTER_MAX_MAGIC;
	/*mapKeyPressedToAnimation['a'] = ATACAR;
	mapKeyPressedToAnimation['s'] = DEFENDER;*/
}

void PersonajeModelo::setAnimation(AnimatedEntity* ae) {
	animation = ae;
}

void PersonajeModelo::changeToAnimation(int animationNumber) {
	this->targetParcial = this->getPosition();
	this->target = this->targetParcial;
	if (estado >= MOVIMIENTO) {
		this->changeToState(animationNumber - MOVIMIENTO);
	} else {
		this->changeToState(animationNumber - PARADO);
	}
}

void PersonajeModelo::changeToState(int addedState) {
	this->estado += addedState;
}

void PersonajeModelo::animar(char opcion) {
	if ((isActivo )&& (animacionActual == SIN_CAMBIO)) {
		
		switch (opcion) {
		case (OPCION_ATACAR): {
			this->setAnimating(true);
			this->changeToAnimation(ATACAR);
			break;
				  }
		case (OPCION_DEFENDER): {
			this->setAnimating(true);
			this->changeToAnimation(DEFENDER);
			break;
				  }
		default:;
		}
	}
}


bool PersonajeModelo::estaAnimandose() {
	return this->isAnimating;
}

void PersonajeModelo::terminarAnimacion() {
	this->setAnimating(false);
	this->changeToState(PARADO - animacionActual);
	animacionActual = SIN_CAMBIO;
}


bool PersonajeModelo::hasDirectoryRemaining(){
	return animation->hasNextDir();
}

AnimatedEntity* PersonajeModelo::getAnimation() {
	return animation;
}

float PersonajeModelo::getVidaMaxima() {
	return vidaMaxima;
}

void PersonajeModelo::setVidaMaxima(float vida) {
	vidaMaxima = vida;
}

float PersonajeModelo::getMagiaMaxima() {
	return magiaMaxima;
}

void PersonajeModelo::setMagiaMaxima(float magia) {
	magiaMaxima = magia;
}

string PersonajeModelo::nextDirectory() {
	return this->animation->nextDirectory();
}

int PersonajeModelo::fps() {
	return this->animation->fps();
}

int PersonajeModelo::delay() {
	return this->animation->delay();
}

void PersonajeModelo::setDestino(int x, int y) {
	if ((isActivo) && (!this->estaAnimandose())) {
		target.first = x;
		target.second = y;
		targetParcial.first = x;
		targetParcial.second = y;
	}
}

void PersonajeModelo::setEstado(int state) {
	this->estado = state;
}

int PersonajeModelo::getEstado() {
	return this->estado;
}

void PersonajeModelo::setIsActivo(bool active) {
		this->isActivo = active;
}
bool PersonajeModelo::getIsActivo() {
	return isActivo;
}

void PersonajeModelo::setVelocidad(float vel) {
	this->velocidad = vel;
}

float PersonajeModelo::getVelocidad() {
	return this->velocidad;
}

int PersonajeModelo::siCaminaDetenerse() {
	int cambio = SIN_CAMBIO;
	
	if ((estado<10) || (estado>19)) { //si esta caminando
		cambio = ESTADO_MOVIMIENTO; //que se quede quieto
	}
	return cambio;
}

//int PersonajeModelo::mover(std::pair<int, int>& destino, float& velocidadAni) {
//	Pathfinder pathF;
//	int cambio = SIN_CAMBIO;
//	double coste = 0;
//	float costeF = 0;
//
//	if (target == current) {
//		return (this->quedarseQuieto(velocidadAni));
//	}
//	if (esNecesarioCalcularNuevoPath()) {
//		posMov = 0;
//		caminoSize = 0;
//		limpiarPath();
//		targetParcial.first = target.first;
//		targetParcial.second = target.second;
//		caminoSize = pathF.getPath(current.first, current.second, targetParcial.first, targetParcial.second, xPath, yPath);
//		if (caminoSize == 0) { //Si no se tiene que mover, seteo el destino en los parciales
//			target.first = targetParcial.first;
//			target.second = targetParcial.second;
//		}
//		if (caminoSize <  0) {
//			return (this->quedarseQuieto(velocidadAni));
//		}
//	}
//	if (posMov < caminoSize) {
//		this->moverse(destino, velocidadAni);
//	} else {
//		return (this->quedarseQuieto(velocidadAni));
//	}
//	cambio = ESTADO_MOVIMIENTO;
//	estado = cambiarEstado(destino.first, destino.second, cambio);
//	return estado;
//}

int PersonajeModelo::mover(std::pair<int, int>& destino, float& velocidadAni) {
	int cambio = SIN_CAMBIO;
	double coste = 0;
	float costeF = 0;

	if (this->target == this->getPosition()) {
		return (this->quedarseQuieto(velocidadAni));
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
	if ((posMov == caminoSize)&&( this->target != this->targetParcial)) { //Si completo el primer pedazo del camino
		return true;
	}
	return false;
}

void PersonajeModelo::moverse(std::pair<int, int>& destino, float &velocidad) {
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
	if((this->getPosition() == std::make_pair(x,y))&&(cambio==ESTADO_MOVIMIENTO)){
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
	int xCurr = this->getPosition().first;
	int yCurr = this->getPosition().second;
	
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
	this->limpiarPath();
	if (this->vision){
		delete this->vision;
	}
}

void PersonajeModelo::setName(string nombreJugador) {
	this->name = nombreJugador;
}

string PersonajeModelo::getName() {
	return this->name;
}
//
//std::pair<int, int> PersonajeModelo::getPosition() {
//	return this->current;
//}

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
	/*this->vision->updatePosition(this->getPosition());*/
}

std::pair<int, int> PersonajeModelo::obtenerFrentePersonaje() {
	std::pair <int, int> posicionSig = this->getPosition();

	if ((orientacion == NORTE) || (orientacion == NORESTE) || (orientacion == ESTE))
		posicionSig.second--;
	else if ((orientacion == SUDOESTE) || (orientacion == OESTE) || (orientacion == SUR))
		posicionSig.second++;

	if ((orientacion == NORTE) || (orientacion == NOROESTE) || (orientacion == OESTE))
		posicionSig.first--;
	else if ((orientacion == ESTE) || (orientacion == SUDESTE) || (orientacion == SUR))
		posicionSig.first++;
	
	return posicionSig;
}

void PersonajeModelo::setAnimating(bool value) {
	this->isAnimating = value;
}

int PersonajeModelo::getRefPixelX() {
	return this->animation->pixelRefX();
}

int PersonajeModelo::getRefPixelY() {
	return this->animation->pixelRefY();
}

void PersonajeModelo::restartDirectories() {
	this->animation->imagesPaths()->restartCurrentPosition();
}
//
//void PersonajeModelo::setPosition(std::pair<int, int> pos) {
//	this->current = pos;
//}