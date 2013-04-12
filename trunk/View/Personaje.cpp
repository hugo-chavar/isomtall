#include "Personaje.h"
#include "../Model/PersonajeConstantes.h"


Personaje::Personaje() {
}

void Personaje::update(){
	std::pair<int, int> tile;
	tile.first = 0;
	tile.second = 0;
	int animacion = 0;
	if (((delta.first) == 0)&&((delta.second) == 0)) {
		modelo.getCurrent(tileActual);
		animacion = modelo.mover(tile, velocidad);
		estado = procesarAnimacion(animacion);
		modelo.setCurrent(tile.first, tile.second);
	}
	if (estado != ERROR) {
		sprites[estado]->actualizarFrame();
		if ((delta.first) < 0) {
			
			delta.first = delta.first + velocidad;
		} else {
			if ((delta.first) > 0) {

				delta.first = delta.first - velocidad;
			}
		}
		if ((delta.second) < 0) {

			delta.second = delta.second + velocidad;
		} else {
			if ((delta.second) > 0) {

				delta.second = delta.second - velocidad;
			}
		}
	}
}

void Personaje::render(Camera& camera) {
	camera.render(this->spriteRect, sprites[estado]->getFrameActual()->getSuperficie());
}


void Personaje::setDestino(int xTile, int yTile){
	modelo.setDestino(xTile, yTile);
}

void Personaje::agregarSprite(Sprite* sprite) {
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
	case PARADO_SE: return STOP_S;
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
	return ERROR;
}

Personaje::~Personaje(){
}