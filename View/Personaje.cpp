#include "Personaje.h"
#include "../Model/PersonajeConstantes.h"


Personaje::Personaje(model::PersonajeModelo* pj) {
	//MainCharacter* m_char = NULL;
	
	modelo = pj;
	pj->getCurrent(tileActual);
	estado = procesarAnimacion(pj->getEstado());
	velocidad = pj->getVelocidad();
	delta.first = 0;
	delta.second = 0;
	
	ePot.first = 0;
	ePot.second = 0;
	serr = 0;
}

void Personaje::update(){
	std::pair<int, int> tile;
	tile.first = 0;
	tile.second = 0;
	int animacion = 0;
	std::pair<float, float> factor;
	factor.first = 0;
	factor.second = 0;
	float factorT = 0;
	int estadoAc = estado;

	if (((delta.first) == 0)&&((delta.second) == 0)) {
		serr = 0;
		modelo->getCurrent(tileActual);
		animacion = modelo->mover(tile, velocidad);
		estado = procesarAnimacion(animacion);
		if (estadoAc != estado) {
			ePot.first = 0;
			ePot.second = 0;
		} 
		if (velocidad != 0) {
			modelo->setCurrent(tile.first, tile.second);
		}
	}
	velocidadRelativa(factor);
	if (estado != ERROR) {
		sprites[estado]->actualizarFrame();
		if (delta.first != 0) {
			if (delta.second != 0) {
				serr++;
			}
			ePot.first = ePot.first + factor.first;
			if (ePot.first >= 1) {
				factorT = std::floor(ePot.first);
				ePot.first -= factorT;
				if (delta.first < 0) {
					delta.first += factorT;
					if (delta.first > 0) {
						spriteRect.x -= (Sint16) (factorT - delta.first);
						ePot.first += delta.first;
						delta.first = 0;
					} else {
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
		if (((delta.second != 0)&&(serr != 1))||((serr == 1)&&(delta.first == 0))) {
			serr = 0;
			ePot.second = ePot.second + factor.second;
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
	}
}


void Personaje::render(Camera& camera) {
	camera.render(this->spriteRect, sprites[estado]->getFrameActual()->getSuperficie());
}


void Personaje::setDestino(int xTile, int yTile){
	modelo->setDestino(xTile, yTile);
}

void Personaje::velocidadRelativa(std::pair<float, float>& factor) {
	//Velocidad Relativa Hacia el Norte
	if ((delta.second < 0)&&(delta.first == 0)) {
		factor.second = velocidad/2;
	}
	//Velocidad Relativa Hacia el Sur
	if ((delta.second > 0)&&(delta.first == 0)) {
		factor.second = velocidad*2;
	}
	//Velocidad Relativa Hacia el Este y el Oeste
	if ((delta.first != 0)&&(delta.second == 0)) {
		factor.first = velocidad;
	}
	//Velocidades Relativas Hacia el NorOeste y NorEste
	if ((delta.first != 0)&&(delta.second < 0)) {
		factor.first = (float)(velocidad/(1.5));
		factor.second = (float)(velocidad/(1.5));
	}
	//Velocidades Relativas Hacia el SudOeste y SudEste
	if ((delta.first != 0)&&(delta.second > 0)) {
		factor.first = (float)(velocidad*(1.5));
		factor.second = (float)(velocidad*(1.5));
	}
	//Velocidad Cuando No se Mueve
	if ((delta.first == 0)&&(delta.second == 0)){
		factor.first = 0;
		factor.second = 0;
	}
}

void Personaje::agregarSprite(Sprite* sprite) {
	if (sprites.empty()) {
		spriteRect=posicionIsometricaPorTiles(tileActual.first, tileActual.second,sprite);
		spriteRect.w=(Uint16)(sprite->getFrameActual()->getSuperficie()->w);
		spriteRect.h=(Uint16)(sprite->getFrameActual()->getSuperficie()->h);
	}
	sprites.push_back(sprite);
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
	default: return ERROR;
	}
	//return ERROR;
}

int Personaje::estadoModelo(int estado) {
	switch(estado) {
	case STOP_N: return PARADO_N;
	case STOP_NE: return PARADO_NE;
	case STOP_NOE: return PARADO_NOE;
	case STOP_S: return PARADO_S;
	case STOP_SE: return PARADO_SE;
	case STOP_SOE: return PARADO_SOE;
	case STOP_E: return PARADO_E;
	case STOP_O: return PARADO_O;
	case WALK_N: return CAMINANDO_N;
	case WALK_NE: return CAMINANDO_NE;
	case WALK_NOE: return CAMINANDO_NOE;
	case WALK_S: return CAMINANDO_S;
	case WALK_SE: return CAMINANDO_SE;
	case WALK_SOE: return CAMINANDO_SOE;
	case WALK_E: return CAMINANDO_E;
	case WALK_O: return CAMINANDO_O;
	default: return ERROR;
	}
	//return ERROR;
}

Personaje::~Personaje(){
}

model::PersonajeModelo* Personaje::personajeModelo()
{return modelo;}

std::pair<int,int> Personaje::posicion()
{
	std::pair<int,int> pos;
	pos.first=spriteRect.x;
	pos.second=spriteRect.y;
	return pos;
}