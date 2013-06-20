#include <cstdlib>
#include "Logger.h"
#include "PersonajeModelo.h"
#include "Pathfinder.h"
#include "PersonajeConstantes.h"
#include "../Common/stringUtilities.h"
#include "OpcionesJuego.h"
#include "Game.h"
#include "../View/GameView.h"

using namespace common;

PersonajeModelo::PersonajeModelo() {
	this->xPath = NULL;
	this->yPath = NULL;
	this->vision = NULL;
	this->initialize(DEFAULT_MAIN_CHARACTER_X, DEFAULT_MAIN_CHARACTER_Y);
}

PersonajeModelo::PersonajeModelo(int ActualX, int ActualY) {
	this->xPath = NULL;
	this->yPath = NULL;
	this->vision = NULL;
	this->initialize(ActualX, ActualY);
}

PersonajeModelo& PersonajeModelo::operator=(const PersonajeModelo &source){
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
	precisionMinima = source.precisionMinima;
	danoMaximo = source.danoMaximo;
	vidaMaxima = source.vidaMaxima;
	magiaMaxima = source.magiaMaxima;
	return *this;
	this->vidaMaxima = source.vidaMaxima;
}

void PersonajeModelo::initialize(int pos_x, int pos_y) {
	this->startPosition = std::make_pair(pos_x, pos_y);
	//velocidad = DEFAULT_MAIN_CHARACTER_SPEED;
	this->resetChar();
}


void PersonajeModelo::resetChar() {
	this->setPosition(this->startPosition);
	this->limpiarPath();
	this->setNoTarget();
	posMov = 0;
	caminoSize = 0;
	estado = PARADO;
	velocidad = Game::instance().configuration()->mainCharacterSpeed();
	orientacion = SUR;
	this->setAnimating(false);
	animacionActual = SIN_CAMBIO;
	following = false;
	isReseting = true;
	this->setActive(true);
}

//---------Getters/setters ------------------------------

void PersonajeModelo::setAnimation(AnimatedEntity* ae) {
	animation = ae;
}

float PersonajeModelo::getDanoMaximo() {
	return this->danoMaximo;
}

float PersonajeModelo::getPrecisionMinima() {
	return this->precisionMinima;
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

void PersonajeModelo::setDanoMaximo(float dano) {
	danoMaximo = dano;
}

void PersonajeModelo::setPrecisionMinima(float precision) {
	precisionMinima = precision;
}

bool PersonajeModelo::estaAnimandose() {
	return this->isAnimating;
}

bool PersonajeModelo::getIsReseting(){
	return isReseting;
}

void PersonajeModelo::setIsReseting(){
	isReseting = false;
}

void PersonajeModelo::setEstado(int state) {
	this->estado = state;
}

int PersonajeModelo::getEstado() {
	return this->estado;
}

void PersonajeModelo::setActive(bool value) {
		this->active = value;
}

bool PersonajeModelo::isActive() {
	return this->active;
}

void PersonajeModelo::setVelocidad(float vel) {
	this->velocidad = vel;
}

float PersonajeModelo::getVelocidad() {
	return this->velocidad;
}

int PersonajeModelo::getOrientacion() {
	return this->orientacion;
}

bool PersonajeModelo::followingEnemy() {
	return following;
}

void PersonajeModelo::setFollowingEnemy(bool enemy) {
	following = enemy;
}

std::pair<int, int> PersonajeModelo::getTarget() {
	return target;
}

void PersonajeModelo::setName(string nombreJugador) {
	this->name = nombreJugador;
}

string PersonajeModelo::getName() {
	return this->name;
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

//-----------------Functional methods -----------------------

void PersonajeModelo::herir() {
	animacionActual = HERIR;
	this->changeToAnimation(animacionActual);
}

void PersonajeModelo::morir() {
	animacionActual = MORIR;
	this->changeToAnimation(animacionActual);
}


void PersonajeModelo::atacar() {
		animacionActual = ATACAR;
		this->changeToAnimation(animacionActual);
}

void PersonajeModelo::defender() {
	animacionActual = DEFENDER;
	this->changeToAnimation(animacionActual);
}

void PersonajeModelo::hacerMagia() {
	animacionActual = MAGIA;
	this->changeToAnimation(animacionActual);
}

void PersonajeModelo::changeToAnimation(int animationNumber) {
	this->setAnimating(true);
	this->setNoTarget();
	if (estado >= MOVIMIENTO) {
		this->changeToState(animationNumber - MOVIMIENTO);
	} else {
		this->changeToState(animationNumber - PARADO);
	}
}

void PersonajeModelo::changeToState(int addedState) {
	this->estado += addedState;
}

void PersonajeModelo::terminarAnimacion() {
	this->setAnimating(false);
	if (animacionActual == MORIR) {
		this->resetChar();
	} else {
		this->changeToState(PARADO - animacionActual);
		animacionActual = SIN_CAMBIO;
	}
}

bool PersonajeModelo::hasDirectoryRemaining(){
	return animation->hasNextDir();
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

bool PersonajeModelo::isThereAnEnemy(int tileX, int tileY) {
	std::pair<int, int> tileDestino(tileX, tileY);

	if ((!this->isActive())||(this->estaAnimandose())) {
		return false;
	}
	if ((vision != NULL) && (vision->isInsideVision(tileDestino)) && (GameView::instance().getDaniableInTile(tileDestino) != NULL)) {
		return true;
	}
	return false;
}

void PersonajeModelo::setDestino(int x, int y) {
	if ((isActivo) && (!this->estaAnimandose())) {
		target.first = x;
		target.second = y;
		targetParcial.first = x;
		targetParcial.second = y;
	}
}




int PersonajeModelo::siCaminaDetenerse() {
	int cambio = SIN_CAMBIO;
	
	if (estado == MOVIMIENTO) { //si esta caminando
		cambio = ESTADO_MOVIMIENTO; //que se quede quieto
	}
	return cambio;
}

int PersonajeModelo::mover(std::pair<int, int>& destino, float& velocidadAni) {
	Pathfinder pathF;
	int cambio = SIN_CAMBIO;
	double coste = 0;
	float costeF = 0;
	

	if (this->target == this->getPosition()) {
		return (this->quedarseQuieto(velocidadAni));
	}
	if (esNecesarioCalcularNuevoPath()) {
		posMov = 0;
		caminoSize = 0;
		limpiarPath();
		targetParcial.first = target.first;
		targetParcial.second = target.second;
		caminoSize = pathF.getPath(this->getPosition().first, this->getPosition().second, targetParcial.first, targetParcial.second, xPath, yPath);
		if (caminoSize == 0) { //Si no se tiene que mover, seteo el destino en los parciales
			this->orientar(target);
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


//int PersonajeModelo::mover(std::pair<int, int>& destino, float& velocidadAni) {
//	int cambio = SIN_CAMBIO;
//	double coste = 0;
//	float costeF = 0;
//
//	if (this->target == this->getPosition()) {
//		return (this->quedarseQuieto(velocidadAni));
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


void PersonajeModelo::orientar(std::pair<int, int> destino) {
	this->setDirection(this->getPosition(), destino);
	int cambio = ESTADO_MOVIMIENTO;
	estado = cambiarEstado(destino.first, destino.second, cambio);
}


bool PersonajeModelo::esNecesarioCalcularNuevoPath(){
	if ((xPath == NULL)&&(yPath == NULL)) { //Si no hay camino seteado
		return true;
	}
	if ((xPath[caminoSize-1]!=targetParcial.first)||(yPath[caminoSize-1]!=targetParcial.second)) { //Si cambio de destino durante el movimiento
		return true;
	}
	if (posMov >= 5/*this->getVision()->getRangeVision()*/) { //Si se movio el maximo antes de recalcular
		return true;
	}
	if ((posMov==caminoSize)&&((target.first!=targetParcial.first)||(target.second!=targetParcial.second))) { //Si completo el primer pedazo del camino
		return true;
	}
	if (followingEnemy()) {
		return true;
	}
	if ((Game::instance().world())->cost(xPath[posMov], yPath[posMov]) == 0) { //Hay un pj en el tile al que se va a mover
		return true;
	}
	return false;
}

bool PersonajeModelo::canSee(std::pair<int, int> tile) {
	return vision->isInsideVision(tile);
}

void PersonajeModelo::moverse(std::pair<int, int>& destino, float &velocidad){
	double coste = 0;
	float costeF = 0;

	destino.first = xPath[posMov];
	destino.second = yPath[posMov];
	this->setDirection(this->getPosition(), destino);
	coste = (Game::instance().world())->cost(xPath[posMov], yPath[posMov]);
	costeF = (float) coste;
	velocidad = ((this->velocidad)*costeF);
	posMov++;
	//this->eatIfItem(destino);
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
		return PARADO;
	}
	orientacion = obtenerOrientacionRespectoAUnTile(x, y);
	if ((orientacion >= 0)&&(orientacion <= 7)) {
		return MOVIMIENTO;
	} else {
		return ESTADO_ERROR;
	}
}

int PersonajeModelo::obtenerOrientacionRespectoAUnTile(int x, int y) {
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

void PersonajeModelo::restartDirectories() {
	this->animation->imagesPaths()->restartCurrentPosition();
}

void PersonajeModelo::increaseSpeed(float factor)
{
	this->velocidad=this->velocidad*factor;
	if(this->velocidad>MAX_MAIN_CHARACTER_SPEED)
	{
		this->velocidad=MAX_MAIN_CHARACTER_SPEED;
	}
}

void PersonajeModelo::setNoTarget() {
	this->target = this->getPosition();
	this->targetParcial = this->target;
}