#include "Personaje.h"
#include "../Model/PersonajeConstantes.h"
#include "SDL_ttf.h"

#include "Game.h"


Personaje::Personaje(PersonajeModelo* pj) {
	modelo = pj;
	pj->getCurrent(tileActual);
	estado = procesarAnimacion(pj->getEstado());
	velocidad = pj->getVelocidad();
	delta.first = 0;
	delta.second = 0;
	ePot.first = 0;
	ePot.second = 0;
	serr = 0;
	crearNombre();

	this->modelo->animation()->fps(static_cast<int>(this->modelo->animation()->fps() * (this->modelo->getVelocidad()/2)));
}

/*void Personaje::crearNombre() {
	TTF_Font *font = NULL;
	SDL_Color textColor = { 0, 0, 0 };
	font = TTF_OpenFont( "../Fonts/Arial.ttf", 8 );
	nombre = TTF_RenderText_Solid( font, "The quick brown fox jumps over the lazy dog", textColor );
	TTF_CloseFont( font );
}*/

void Personaje::loadSprites() {
	AnimatedEntity* animatedEntity;
	animatedEntity = new AnimatedEntity();
	animatedEntity->copy(modelo->animation());
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
	spriteRect = posicionIsometricaPorTiles(tileActual.first, tileActual.second,newSprite);
	spriteRect.w = static_cast<Uint16>(newSprite->getFrameActual()->getSuperficie()->w);
	spriteRect.h = static_cast<Uint16>(newSprite->getFrameActual()->getSuperficie()->h);
}

bool Personaje::isCenteredInTile(){
	return ((delta.first == 0) && (delta.second == 0));
}

void Personaje::freezar() {
	int animacion = modelo->getEstado();
	estado = procesarAnimacion(animacion);
	sprites[estado]->actualizarFrame();
}

void Personaje::detenerAnimacion() {
	sprites[estado]->actualizarFrame();
	modelo->terminarAnimacion();
	int animacion = modelo->getEstado();
	estado = procesarAnimacion(animacion);
}

void Personaje::animar() {
	int animacion = modelo->getEstado();
	if (procesarAnimacion(animacion) != estado) {
		sprites[estado]->reiniciar();
	}
	estado = procesarAnimacion(animacion);
	if (sprites[estado]->ultimoFrame()) {
		this->detenerAnimacion();
	}
	sprites[estado]->actualizarFrame();
}

void Personaje::update(){
	
	if ((modelo->getIsActivo())||(!(this->isCenteredInTile()))) {
		if ((modelo->estaAnimando())&&(this->isCenteredInTile())) {
			this->animar();
		} else {
			this->mover();
		}
	} else {
		this->freezar();
	}
}

void Personaje::mover(){
	std::pair<float, float> factor;	//Cuantos pixels se mueve por ciclo
	factor.first = 0;
	factor.second = 0;
	

	calcularSigTileAMover();
	calcularvelocidadRelativa(factor);
	if (estado != ERROR) {
		sprites[estado]->actualizarFrame();
		moverSprite(factor);
	}
}


void Personaje::calcularSigTileAMover(){
	int animacion = 0;	//animacion del personaje en el sistema de PersonajeModelo
	std::pair<int, int> tile;	//Un tile
	int estadoAnterior = estado;

	if (this->isCenteredInTile()) {
		serr = 0;
		modelo->getCurrent(tileActual);
		animacion = modelo->mover(tile, velocidad);
		estado = procesarAnimacion(animacion);
		if (estadoAnterior != estado) {
			ePot.first = 0;
			ePot.second = 0;
		} 
		if (velocidad != 0) {
			modelo->setCurrent(tile.first, tile.second);
		}
	}
}

void Personaje::moverSprite(std::pair<float, float>& factor){
	
	if (delta.first != 0) { //Hay movimieto en x
		if (delta.second != 0) { //Si también hay movimiento en y seteo el control del movimiento diagonal
			serr++;
		}
		ePot.first = ePot.first + factor.first;	//Aumento la cantidad de movimiento, cuantos pixels se va a mover
		moverSpriteEnX(); //Mueve en x
	}
	if (((delta.second != 0)&&(serr != 1))||((serr == 1)&&(delta.first == 0))) { //Si hay movimiento en y, y no esta activada la corrección en diagonal
		serr = 0;																	//O si esta activada la corrección pero se completo el movimineto en x
		ePot.second = ePot.second + factor.second;									//Caso en que la velocidad no es entera
		moverSpriteEnY();
	}
}

void Personaje::moverSpriteEnX() {
	float factorT = 0;	//El truncamiento de la variable factor
	if (ePot.first >= 1) {	//Si la cantidad de movimiento es mayor a un pixel o mas
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
	if (ePot.second >= 1) {
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
	camera.render(this->spriteRect, sprites[estado]->getFrameActual()->getSuperficie());
}


void Personaje::setDestino(int xTile, int yTile){
	modelo->setDestino(xTile, yTile);
}

void Personaje::calcularvelocidadRelativa(std::pair<float, float>& factor) {
	if (delta.first != 0){ //Hay movimiento en x
		if (delta.second != 0) { //Diagonal
			factor.first = static_cast<float>(velocidad *0.707);
			factor.second = static_cast<float>(velocidad *0.707);
		} else { //Horizontal
			factor.first = velocidad;
		}
	} else { //No hay movimiento en x
		if (delta.second != 0){ //Vertical
			factor.second = (velocidad/2);
		} else {//Quieto
			factor.first = 0;
			factor.second = 0;
		}

	}
}


int Personaje::procesarAnimacion(int animacion) {
	if ((animacion < MOVIMIENTO)||(animacion >= (MOVIMIENTO + FACTOR_ORIENTACION))) {
		delta.first = 0;
		delta.second = 0;
	}
	switch (animacion) {
		//Parado
	case PARADO_N: return STOP_N;
	case PARADO_NE: return STOP_NE;
	case PARADO_NOE: return STOP_NOE;
	case PARADO_S: return STOP_S;
	case PARADO_SE: return STOP_SE;
	case PARADO_SOE: return STOP_SOE;
	case PARADO_E: return STOP_E;
	case PARADO_O: return STOP_O;
		//Caminando
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
	default: return ERROR;
	}
}

Personaje::~Personaje(){
	if (sprites.size() > 0) {
		clearSprites();
	}
	/*SDL_FreeSurface( nombre );*/
}

PersonajeModelo* Personaje::personajeModelo(){
	return modelo;
}

std::pair<int,int> Personaje::posicion(){
	std::pair<int,int> pos;
	pos.first = spriteRect.x;
	pos.second = spriteRect.y;
	return pos;
}

std::pair<int,int> Personaje::getPosicionEnTiles(){
	float deltaAbsX = std::abs(delta.first);
	float deltaAbsY = std::abs(delta.second);

	if ((deltaAbsX <= 32) && (deltaAbsY == 0)) {
		return modelo->getPosition();
	}
	if ((deltaAbsX == 0) && (deltaAbsY <= 16)) {
		return modelo->getPosition();
	}
	if ((deltaAbsX <= 16) && (deltaAbsY <= 8)) {
		return modelo->getPosition();
	}
	return tileActual;
}