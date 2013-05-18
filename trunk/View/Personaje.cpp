#include "Personaje.h"
#include "../Model/PersonajeConstantes.h"
#include "SDL_ttf.h"
#include "Logger.h"
#include "StringUtilities.h"

#include "Game.h"


Personaje::Personaje(PersonajeModelo* pj) {
	modelo = pj;
	tileActual = pj->getPosition();
	this->setCurrentSpritePosition(this->calculateSpritePosition(pj->getEstado()));
	velocidad = pj->getVelocidad();
	delta.first = 0;
	delta.second = 0;
	ePot.first = 0;
	ePot.second = 0;
	serr = 0;
	crearNombre(modelo->getName());

	//this->modelo->getAnimation()->fps(static_cast<int>(this->modelo->getAnimation()->fps() * (this->modelo->getVelocidad()/2)));

	this->setFreezed(false);
	this->resetSpriteState();
}

void Personaje::crearNombre(string textoNombre) {
	TTF_Font *font = NULL;
	SDL_Rect cuadroMensaje;

	cuadroMensaje.x = spriteRect.x + 25;
	cuadroMensaje.y = spriteRect.y;
	SDL_Color textColor = { 255, 255, 255 };
	font = TTF_OpenFont( FUENTE, 12 );
	nombre = TTF_RenderText_Blended( font, textoNombre.c_str(), textColor );
	SDL_SetClipRect(nombre, (&cuadroMensaje));
	TTF_CloseFont( font );
}

void Personaje::loadSprites() {
	AnimatedEntity* animatedEntity;
	animatedEntity = new AnimatedEntity();
	animatedEntity->copy(modelo->getAnimation());
	animatedEntity->loadImages(modelo->nextDirectory());
	this->addFirstSprite(animatedEntity);

	while (modelo->hasDirectoryRemaining()) {
		animatedEntity->loadImages(modelo->nextDirectory());
		this->addNextSprite(animatedEntity);
		animatedEntity->clearImages();
	}

	delete animatedEntity;
	animatedEntity = NULL;
}

void Personaje::clearSprites() {
	vector<SpriteAnimado*>::iterator it;
	for (it = sprites.begin(); it != sprites.end(); it++){
		delete *it;
	}
	sprites.clear();
}

void Personaje::addNextSprite(AnimatedEntity* entity) {
	SpriteAnimado* newSprite = new SpriteAnimado(entity);
	sprites.push_back(newSprite);
}

void Personaje::addFirstSprite(AnimatedEntity* entity) {
	SpriteAnimado* newSprite = new SpriteAnimado(entity);
	sprites.push_back(newSprite);
	this->setRectangle(modelo->getPosition(), newSprite);
}

bool Personaje::isCenteredInTile() {
	return ((delta.first == 0) && (delta.second == 0));
}

void Personaje::setFreezed(bool value) {
	Entity::setFreezed(value);
	//if (this->freezed == value)
	//	return;
	//this->freezed = value;
	//if (!this->isFreezed())
	//	this->freezedSpriteState = -1;
}
//
//void Personaje::resetSpriteState() {
//	this->freezedSpriteState = -1;
//}


void Personaje::detenerAnimacion() {
	modelo->terminarAnimacion();
	int currentAnimationNumber = modelo->getEstado();
	this->setCurrentSpritePosition(this->calculateSpritePosition(currentAnimationNumber));
}

void Personaje::animar() {
//	float deltaTime = Game::instance().time()->getDeltaTime();
	//this->modelo->getAnimation()->fps();
	if (!this->modelo->estaAnimandose())
		return;
	int currentAnimationNumber = modelo->getEstado();
	if (this->calculateSpritePosition(currentAnimationNumber) != this->getCurrentSpritePosition()) {
		sprites[this->getCurrentSpritePosition()]->reiniciar();
		sprites[this->calculateSpritePosition(currentAnimationNumber)]->reiniciar();
	}
	this->setCurrentSpritePosition(this->calculateSpritePosition(currentAnimationNumber));
	if (sprites[this->getCurrentSpritePosition()]->ultimoFrame()) {
		this->detenerAnimacion();
	}
}

void Personaje::update() {
	this->setFreezed(!modelo->getIsActivo());
	this->mover();
	if (this->isCenteredInTile()) {
		this->animar();
	}
	modelo->update();
	sprites[this->getCurrentSpritePosition()]->actualizarFrame();
}

void Personaje::mover() {
	if (this->isCenteredInTile() && (this->isFreezed() || this->modelo->estaAnimandose()))
		return;

	std::pair<float, float> factor;	//Cuantos pixels se mueve por ciclo
	factor.first = 0;
	factor.second = 0;
	
	calcularSigTileAMover();
	calcularvelocidadRelativa(factor);
	if (this->getCurrentSpritePosition() != ESTADO_ERROR) {
		moverSprite(factor);
	}
}


void Personaje::calcularSigTileAMover(){
	int currentAnimationNumber = 0;	//animacion del personaje en el sistema de PersonajeModelo
	std::pair<int, int> tile;	//Un tile
	int previousSpritePosition = this->getCurrentSpritePosition();

	if (this->isCenteredInTile()) {
		serr = 0;
		tileActual = modelo->getPosition();
		currentAnimationNumber = modelo->mover(tile, velocidad);
		this->setCurrentSpritePosition(this->calculateSpritePosition(currentAnimationNumber));
		if (previousSpritePosition != this->getCurrentSpritePosition()) {
			ePot.first = 0;
			ePot.second = 0;
		} 
		//std::string aux = stringUtilities::floatToString(velocidad);
		//common::Logger::instance().log("Velocidad: "+ aux);
		if (velocidad != 0) {
			//modelo->setIsInCenterTile(false);
			modelo->setCurrent(tile.first, tile.second);
		}
	}
}

void Personaje::moverSprite(std::pair<float, float>& factor){
	
	if (delta.first != 0) { //Hay movimieto en x
		ePot.first = ePot.first + factor.first;	//Aumento la cantidad de movimiento, cuantos pixels se va a mover
		moverSpriteEnX(); //Mueve en x
	}
	if (delta.second != 0) { //Si hay movimiento en y, y no esta activada la corrección en diagonal
		ePot.second = ePot.second + factor.second;									//O si esta activada la corrección pero se completo el movimineto en x
		moverSpriteEnY();															//Caso en que la velocidad no es entera
	}
}

void Personaje::moverSpriteEnX() {
	float factorT = 0;	//El truncamiento de la variable factor
	if (ePot.first >= 1) {	//Si la cantidad de movimiento es mayor a un pixel o mas
		if (delta.second != 0) { //Si también hay movimiento en y seteo el control del movimiento diagonal
			serr++;
		}
		//TODO: mejorar el codigo repetido:, notar que dice: if(negativo) sumar else restar..
		factorT = std::floor(ePot.first);	//Trunco para obtener una cantidad entera
		ePot.first -= factorT;	//Saco la cantidad entera de la cantidad de movimiento
		if (delta.first < 0) {	//Si me muevo hacia las x negativas
			delta.first += factorT;
			if (delta.first > 0) {	//Si me paso, por los decimales
				spriteRect.x -= (Sint16) (factorT - delta.first); //Muevo el sprite en x
				ePot.first += delta.first;
				delta.first = 0;	//Termino el movimietno en x
			} else {				//Mientras siga pudiendo moverse
				spriteRect.x -= (Sint16) factorT;
			}
		} else {
			delta.first -= factorT;
			if (delta.first < 0) {
				spriteRect.x += (Sint16)(factorT + delta.first);
				ePot.first -= delta.first;
				delta.first = 0;
			} else {
				spriteRect.x += (Sint16)factorT;
			}
		}
	}
}

void Personaje::moverSpriteEnY() {
	float factorT = 0;	//El truncamiento de la variable factor
	//TODO: mejorar el codigo repetido:, notar que dice: if(negativo) sumar else restar..
	if (((ePot.second >= 1)/*&&(serr != 1))||((serr == 1)&&(delta.first == 0)&&(ePot.second >= 1)*/)) {
		serr = 0;
		factorT = std::floor(ePot.second);
		ePot.second -= factorT;
		if (delta.second < 0) {
			delta.second += factorT;
			if (delta.second > 0) {
				spriteRect.y -= (Sint16)(factorT - delta.second);
				ePot.second += delta.second;
				delta.second = 0;
			} else {
				spriteRect.y -= (Sint16)factorT;
			}
		} else {
			delta.second -= factorT;
			if (delta.second < 0) {
				spriteRect.y += (Sint16)(factorT + delta.second);
				ePot.second -= delta.second;
				delta.second = 0;
			} else {
				spriteRect.y += (Sint16)factorT;
			}
		}
	}
}

void Personaje::render(Camera& camera) {
	SDL_Rect cuadroMensaje;

	cuadroMensaje.x = spriteRect.x + 25;
	cuadroMensaje.y = spriteRect.y;
	//TODO: mejorar siguientes 3 lineas..
	if (this->freezed)
		camera.render(spriteRect,sprites[this->getCurrentSpritePosition()]->getSurfaceAt(freezedSpriteState)->getShadow());
	camera.render(this->spriteRect, sprites[this->getCurrentSpritePosition()]->getSurfaceAt(freezedSpriteState)->getSurfaceToShow(this->freezed));
	SDL_SetClipRect(nombre, (&cuadroMensaje));
	camera.render(cuadroMensaje, this->nombre);
}

void Personaje::setDestino(int xTile, int yTile){
	modelo->setDestino(xTile, yTile);
}

void Personaje::calcularvelocidadRelativa(std::pair<float, float>& factor) {
	float deltaTime = Game::instance().time()->getDeltaTime();

	if (delta.first != 0){ //Hay movimiento en x
		if (delta.second != 0) { //Diagonal
			factor.first = static_cast<float>((velocidad*deltaTime) *0.707);
			factor.second = static_cast<float>((velocidad*deltaTime) *0.707/2);
		} else { //Horizontal
			factor.first = (velocidad*deltaTime);
		}
	} else { //No hay movimiento en x
		if (delta.second != 0){ //Vertical
			factor.second = ((velocidad*deltaTime)/2);
		} else {//Quieto
			factor.first = 0;
			factor.second = 0;
		}

	}
}


int Personaje::calculateSpritePosition(int currentAnimationNumber) {
	if ((currentAnimationNumber < MOVIMIENTO)||(currentAnimationNumber >= (MOVIMIENTO + FACTOR_ORIENTACION))) {
		delta.first = 0;
		delta.second = 0;
	}
	switch (currentAnimationNumber) {
	case PARADO_N: return STOP_N;
	case PARADO_NE: return STOP_NE;
	case PARADO_NOE: return STOP_NOE;
	case PARADO_S: return STOP_S;
	case PARADO_SE: return STOP_SE;
	case PARADO_SOE: return STOP_SOE;
	case PARADO_E: return STOP_E;
	case PARADO_O: return STOP_O;
	case CAMINANDO_N: { 
		delta.first = 0;
		delta.second = -32;
		return WALK_N;
					  }
	case CAMINANDO_NE: {
		delta.first = 32;
		delta.second = -16;
		return WALK_NE;
					   }
	case CAMINANDO_NOE: {
		delta.first = -32;
		delta.second = -16;
		return WALK_NOE;
						}
	case CAMINANDO_S: {
		delta.first = 0;
		delta.second = 32;
		return WALK_S;
					  }
	case CAMINANDO_SE: {
		delta.first = 32;
		delta.second = 16;
		return WALK_SE;
					   }
	case CAMINANDO_SOE: {
		delta.first = -32;
		delta.second = 16;
		return WALK_SOE;
						}
	case CAMINANDO_O: {
		delta.first = -64;
		delta.second = 0;
		return WALK_O;
					  }
	case CAMINANDO_E: {
		delta.first = 64;
		delta.second = 0;
		return WALK_E;
					  }
	case FREEZAR_N: return FREEZE_N;
	case FREEZAR_NE: return FREEZE_NE;
	case FREEZAR_NOE: return FREEZE_NOE;
	case FREEZAR_S: return FREEZE_S;
	case FREEZAR_SE: return FREEZE_SE;
	case FREEZAR_SOE: return FREEZE_SOE;
	case FREEZAR_E: return FREEZE_E;
	case FREEZAR_O: return FREEZE_O;
	case ATACAR_N: return ATTACK_N;
	case ATACAR_NE: return ATTACK_NE;
	case ATACAR_NOE: return ATTACK_NOE;
	case ATACAR_S: return ATTACK_S;
	case ATACAR_SE: return ATTACK_SE;
	case ATACAR_SOE: return ATTACK_SOE;
	case ATACAR_E: return ATTACK_E;
	case ATACAR_O: return ATTACK_O;
	case DEFENDER_N: return DEFEND_N;
	case DEFENDER_NE: return DEFEND_NE;
	case DEFENDER_NOE: return DEFEND_NOE;
	case DEFENDER_S: return DEFEND_S;
	case DEFENDER_SE: return DEFEND_SE;
	case DEFENDER_SOE: return DEFEND_SOE;
	case DEFENDER_E: return DEFEND_E;
	case DEFENDER_O: return DEFEND_O;
	default: return ESTADO_ERROR;
	}
}

Personaje::~Personaje(){
	if (sprites.size() > 0) {
		clearSprites();
	}
	SDL_FreeSurface( nombre );
}

PersonajeModelo* Personaje::personajeModelo(){
	return modelo;
}

std::pair<int,int> Personaje::getPosicionEnTiles(){
	return modelo->getPosition();
}

std::pair<int,int> Personaje::getPosicionAnteriorEnTiles(){
	float deltaAbsX = std::abs(delta.first);
	float deltaAbsY = std::abs(delta.second);

	if ((deltaAbsX <= 32) && (deltaAbsY == 0)) {
		return this->getPosicionEnTiles();
	}
	if ((deltaAbsX == 0) && (deltaAbsY <= 16)) {
		return this->getPosicionEnTiles();
	}
	if ((deltaAbsX <= 16) && (deltaAbsY <= 8)) {
		return this->getPosicionEnTiles();
	}
	return tileActual;
}

//tilex, tiley; pixelx, pixely; isFreezed; nro_status; nro_surface
std::string Personaje::updateToString() {
	std::string out;
	out = stringUtilities::pairIntToString(modelo->getPosition());
	out.append(";");
	out.append(stringUtilities::pairIntToString(this->getPixelPosition()));
	out.append(";");
	if (this->isFreezed()) {
		out.append("F");
	} else {
		out.append("N");
	}
	out.append(";");
	out.append(stringUtilities::intToString(this->getCurrentSpritePosition()));
	out.append(";");
	out.append(stringUtilities::intToString(sprites[this->getCurrentSpritePosition()]->getCurrentState()));
	return out;
}

//tilex, tiley; pixelx, pixely; isFreezed; nro_status; nro_surface
void Personaje::updateFromString(std::string data) {
	vector <std::string> splittedData;
	stringUtilities::splitString(data, splittedData, ';');
	std::pair<int,int> tilePosition = stringUtilities::stringToPairInt(splittedData[0]);
	std::pair<int,int> pixels = stringUtilities::stringToPairInt(splittedData[1]);
	this->setFreezed(splittedData[2] == "F");
	this->setCurrentSpritePosition(stringUtilities::stringToInt(splittedData[3]));
	sprites[this->getCurrentSpritePosition()]->setCurrentState(stringUtilities::stringToInt(splittedData[4]));
}

int Personaje::getCurrentSpritePosition() {
	return this->currentSpritePosition;
}

void Personaje::setCurrentSpritePosition(int pos) {
	this->currentSpritePosition = pos;
}

std::pair<int,int> Personaje::getPixelPosition() {
	return std::make_pair<int,int>(spriteRect.x, spriteRect.y);
}

void Personaje::setPixelPosition(std::pair<int,int> pixel) {
	spriteRect.x = static_cast<Sint16>(pixel.first);
	spriteRect.y = static_cast<Sint16>(pixel.second);
}

//tilex,tiley;pixelx,pixely;isFreezed;nro_status;nro_surface~datos_vision
std::string Personaje::initToString() {
	std::string out = this->updateToString();
	out.append("~");
	out.append(this->modelo->getVision()->toString());
	return out;
}

//tilex,tiley;pixelx,pixely;isFreezed;nro_status;nro_surface~datos_vision
void Personaje::initFromString(std::string data) {
	vector <std::string> splittedData;
	stringUtilities::splitString(data, splittedData, '~');
	this->updateFromString(splittedData[0]);
	this->modelo->getVision()->fromString(splittedData[1]);
}