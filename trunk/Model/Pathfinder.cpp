#include "Pathfinder.h"
#include <cstdlib>
#include <map>
#include <vector>
#include <math.h>
#include "Game.h"


#define MOV_PENALTY 10
#define MOV_PENALTY_DIAG 14


int Pathfinder::getPath (int OrigenX, int OrigenY, int& DestinoX, int& DestinoY, int* &XPath, int* &YPath) { //, Foo &Tiles
	int actualX = OrigenX;
	int actualY = OrigenY;
	bool found = false;
	Par* posActual = NULL;
	Nodo* actual = NULL;
	std::map<Par, Nodo> closeList;
	ListaPath openList;
	std::vector<Par> camino;
	int controlTamano = 0;
	int tamanoMax = 100;
	int tamano;

	if ((OrigenX == DestinoX) && (OrigenY == DestinoY)) {
		*XPath = NULL;
		*YPath = NULL;
		return 0;
	}
	actual = new Nodo(OrigenX, OrigenY);
	actual->setHScore(calcularHeuristica(OrigenX, OrigenY, DestinoX, DestinoY));
	posActual = new Par(actualX, actualY);
	openList.agregar(actual);
	while (!(openList.empty())&&(controlTamano < tamanoMax)) {
		actual->getPos(actualX, actualY);
		if ((actualX==DestinoX)&&(actualY==DestinoY)) {
			found = true;
			break;
		}
		agregarVecinos(*actual, DestinoX, DestinoY, closeList, openList); //, Tiles
		posActual->setPos(actualX, actualY);
		closeList.insert(std::pair<Par, Nodo>(*posActual, *actual));
		openList.getNodo(*actual);
		controlTamano++;
	}
	if (!(found)) {
		if (!tileProximo(OrigenX, OrigenY, DestinoX, DestinoY)) {
			getNodoMasCercano(closeList, actual, actualX, actualY);
			DestinoX = actualX;
			DestinoY = actualY;
		} else {
			DestinoX=OrigenX;
			DestinoY=OrigenY;
			actualX=OrigenX;
			actualY=OrigenY;
		}
	}
	if ((actualX == OrigenX)&&(actualY == OrigenY)) {
		tamano = 0;
		delete posActual;
		delete actual;
		return tamano;
	}
	while (true) {
		posActual->setPos(actualX, actualY);
		camino.push_back(*posActual);
		actual->getPosP(actualX, actualY);
		posActual->setPos(actualX, actualY);
		*actual = closeList[*posActual];
		if ((actualX == OrigenX)&&(actualY==OrigenY)) {
			break;
		}
	}
	tamano = (int) camino.size();
	XPath = new int [tamano];
	YPath = new int [tamano];
	for (int i = 0; i < tamano; ++i) {
		*posActual = camino.back();
		camino.pop_back();
		posActual->getPos(actualX, actualY);
		XPath[i] = actualX;
		YPath[i] = actualY;
	}
	delete posActual;
	delete actual;
	return tamano;
}

bool Pathfinder::tileProximo(int OrigenX, int OrigenY, int DestinoX, int DestinoY) {
	int distanciaX = std::abs(OrigenX-DestinoX);
	int distanciaY = std::abs(OrigenY-DestinoY);
	if ((distanciaX<=1)&&(distanciaY<=1)) {
		return true;
	}
	return false;
}

void Pathfinder::getNodoMasCercano(std::map<Par, Nodo>& closeList, Nodo* &actual, int& actualX, int& actualY) {
	std::map<Par, Nodo>::iterator it;
	actual = new Nodo(-1,-1);
	it = closeList.begin();
	*actual = it->second;

	for (it = closeList.begin(); it != closeList.end(); it++) {
		if (((it->second.getHScore()) <= (actual->getHScore()))&&((it->second.getHScore()) > 0)) {
			if ((it->second.getHScore()) == (actual->getHScore())) {
				if ((it->second.getGScore()) < (actual->getGScore())) {
					*actual = it->second;
				}
			} else {
				*actual = it->second;
			}
		}
	}
	actual->getPos(actualX, actualY);
}

void Pathfinder::agregarVecinos(Nodo& actual, int DestinoX, int DestinoY, std::map<Par, Nodo>& closeList, ListaPath& openList) { //, Foo& Tiles
	Par posExplorar;
	Nodo* nuevoNodo = NULL;
	Nodo nodoAgregar;
	int alto = 0;
	int ancho = 0;
	int actualX = 0;
	int actualY = 0;
	int explorarX = -2;
	int explorarY = 1;
	double coste = 0;
	int closeFound = 0;
	bool obstaculosAdyacentes [4];
	unsigned int GCost = 0;
	unsigned int HCost = 0;

	alto = (Game::instance().world())->height();
	ancho = (Game::instance().world())->width();
	actual.getPos(actualX, actualY);
	explorarX = explorarX + actualX;
	explorarY = actualY + explorarY;
	posExplorar.setPos(actualX, actualY);
	explorarObstaculos(actualX, actualY, obstaculosAdyacentes);
	for(int i = 0; i < 9; ++i) {
		if (explorarX == (actualX+1)) {
			explorarX = -2 + actualX;
		}
		if ((i == 3)||(i == 6)) {
			explorarY--;
		}
		explorarX++;
		if ((explorarX == actualX)&&(explorarY == actualY)) {
			continue;
		}
		posExplorar.setPos(explorarX, explorarY);
		if (((explorarX < 0)||(explorarX > ancho-1))||((explorarY < 0)||(explorarY > alto-1))) {
			continue;
		}
		coste = (Game::instance().world())->cost(explorarX, explorarY);
		if (coste == 0) {
			continue;
		}
		if (hayObstaculosAdyacentes(explorarX, explorarY, actualX, actualY, obstaculosAdyacentes)) {
			continue;
		}
		closeFound = closeList.count(posExplorar);
		if (closeFound != 0) {
			continue;
		}
		GCost = calcularGCost (actual.getGScore(), explorarX, explorarY, actualX, actualY, coste);
		nuevoNodo = openList.getNodo(explorarX, explorarY);
		if (nuevoNodo != NULL) {
			if (nuevoNodo->getGScore() > GCost) {
				nuevoNodo->setGScore(GCost);
				nuevoNodo->setPosP(actualX, actualY);
			}
			continue;
		}
		HCost = calcularHeuristica(explorarX, explorarY, DestinoX, DestinoY);
		nodoAgregar.setPos(explorarX, explorarY);
		nodoAgregar.setPosP(actualX, actualY);
		nodoAgregar.setGScore(GCost);
		nodoAgregar.setHScore(HCost);
		openList.agregar(&nodoAgregar);
		delete nuevoNodo;
	}
}

void Pathfinder::explorarObstaculos(int actualX, int actualY, bool* obstaculosAdyacentes) {
	int explorarX = actualX + 1;
	int explorarY = actualY;
	int alto = (Game::instance().world())->height();
	int ancho = (Game::instance().world())->width();

	if (((explorarX < 0)||(explorarX > ancho-1))||((explorarY < 0)||(explorarY > alto-1))) {
			obstaculosAdyacentes[0] = true;
	} else {
		if ((Game::instance().world())->cost(explorarX, explorarY) == 0) {
			obstaculosAdyacentes[0] = true;
		} else {
			obstaculosAdyacentes[0] = false;
		}
	}
	explorarX = explorarX - 1;
	explorarY = explorarY - 1;
	if (((explorarX < 0)||(explorarX > ancho-1))||((explorarY < 0)||(explorarY > alto-1))) {
			obstaculosAdyacentes[1] = true;
	} else {
		if ((Game::instance().world())->cost(explorarX, explorarY) == 0) {
			obstaculosAdyacentes[1] = true;
		} else {
			obstaculosAdyacentes[1] = false;
		}
	}
	explorarX = explorarX - 1;
	explorarY = explorarY + 1;
	if (((explorarX < 0)||(explorarX > ancho-1))||((explorarY < 0)||(explorarY > alto-1))) {
			obstaculosAdyacentes[2] = true;
	} else {
		if ((Game::instance().world())->cost(explorarX, explorarY) == 0) {
			obstaculosAdyacentes[2] = true;
		} else {
			obstaculosAdyacentes[2] = false;
		}
	}
	explorarX = explorarX + 1;
	explorarY = explorarY + 1;
	if (((explorarX < 0)||(explorarX > ancho-1))||((explorarY < 0)||(explorarY > alto-1))) {
			obstaculosAdyacentes[3] = true;
	} else {
		if ((Game::instance().world())->cost(explorarX, explorarY) == 0) {
			obstaculosAdyacentes[3] = true;
		} else {
			obstaculosAdyacentes[3] = false;
		}
	}
}

bool Pathfinder::hayObstaculosAdyacentes(int explorarX, int explorarY, int actualX, int actualY, bool* obstaculosAdyacentes) {
	if ((explorarX > actualX) && (explorarY < actualY)) {
		return ((obstaculosAdyacentes[0])||(obstaculosAdyacentes[1]));
	}
	if ((explorarX < actualX) && (explorarY < actualY)) {
		return ((obstaculosAdyacentes[1])||(obstaculosAdyacentes[2]));
	}
	if ((explorarX < actualX) && (explorarY > actualY)) {
		return ((obstaculosAdyacentes[2])||(obstaculosAdyacentes[3]));
	}
	if ((explorarX > actualX) && (explorarY > actualY)) {
		return ((obstaculosAdyacentes[0])||(obstaculosAdyacentes[3]));
	}
	return false;
}


unsigned int Pathfinder::calcularGCost (unsigned int padre, int posX, int posY, int padreX, int padreY, double coste) {
	unsigned int costeRed = 0;

	if (diagonal(posX, posY, padreX, padreY)) {
		coste = MOV_PENALTY_DIAG/coste;
	} else {
		coste = MOV_PENALTY/coste;
	}
	costeRed = (unsigned)std::floor(coste);
	return (costeRed + padre); 
}

bool Pathfinder::diagonal(int posX, int posY, int padreX, int padreY){
	if ((posX!=padreX)&&(posY!=padreY)) {
		return true;
	}
	return false;
}

unsigned int Pathfinder::calcularHeuristica(int posX, int posY, int DestinoX, int DestinoY) {
	
	posX = std::abs(posX-DestinoX);
	posY = std::abs(posY-DestinoY);
	return ((posX+posY)*MOV_PENALTY);
}