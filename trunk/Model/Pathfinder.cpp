#include "Pathfinder.h"
#include <cstdlib>
#include <map>
#include <vector>
#include <math.h>
#include "Game.h"

using namespace model;

#define MOV_PENALTY 10


int Pathfinder::getPath (int OrigenX, int OrigenY, int DestinoX, int DestinoY, int* &XPath, int* &YPath) { //, Foo &Tiles
	int actualX = OrigenX;
	int actualY = OrigenY;
	bool found = false;
	Par* posActual = NULL;
	Nodo* actual = NULL;
	std::map<Par, Nodo> closeList;
	ListaPath openList;
	std::vector<Par> camino;
	int tamano;

	if ((OrigenX == DestinoX) && (OrigenY == DestinoY)) {
		*XPath = NULL;
		*YPath = NULL;
		return 0;
	}
	actual = new Nodo(OrigenX, OrigenY);
	posActual = new Par(actualX, actualY);
	openList.agregar(actual);
	delete actual;
	while (!(openList.empty())) {
		actual = openList.getNodo();
		actual->getPos(actualX, actualY);
		if ((actualX==DestinoX)&&(actualY==DestinoY)) {
			found = true;
			break;
		}
		agregarVecinos(*actual, DestinoX, DestinoY, closeList, openList); //, Tiles
		posActual->setPos(actualX, actualY);
		closeList.insert(std::pair<Par, Nodo>(*posActual, *actual));
	}
	if (!(found)) {
		XPath = NULL;
		YPath = NULL;
		delete posActual;
		return -1;
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
	return tamano;
}

void Pathfinder::agregarVecinos(Nodo& actual, int DestinoX, int DestinoY, std::map<Par, Nodo>& closeList, ListaPath& openList) { //, Foo& Tiles
	Par* posExplorar = NULL;
	Nodo* nuevoNodo = NULL;
	int alto = 0;
	int ancho = 0;
	int actualX = 0;
	int actualY = 0;
	int explorarX = -2;
	int explorarY = 1;
	double coste = 0;
	int closeFound = 0;
	unsigned int GCost = 0;
	unsigned int HCost = 0;

	alto = Game::instance().world().height();
	ancho = Game::instance().world().width();
	actual.getPos(actualX, actualY);
	explorarX = explorarX + actualX;
	explorarY = actualY + explorarY;
	posExplorar = new Par(actualX, actualY);
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
		posExplorar->setPos(explorarX, explorarY);
		if (((explorarX < 0)||(explorarX > ancho))||((explorarY < 0)||(explorarY > alto))) {
			continue;
		}
		coste = Game::instance().world().cost(explorarX, explorarY);
		if (coste == 0) {
			continue;
		}
		closeFound = closeList.count(*posExplorar);
		if (closeFound != 0) {
			continue;
		}
		GCost = calcularGCost (actual.getGScore(), explorarX, explorarY, coste);
		nuevoNodo = openList.getNodo(explorarX, explorarY);
		if (nuevoNodo != NULL) {
			if (nuevoNodo->getGScore() > GCost) {
				nuevoNodo->setGScore(GCost);
				nuevoNodo->setPosP(actualX, actualY);
			}
			openList.agregar(nuevoNodo);
			delete nuevoNodo;
			continue;
		}
		HCost = calcularHeuristica(explorarX, explorarY, DestinoX, DestinoY);
		nuevoNodo = new Nodo(explorarX, explorarY);
		nuevoNodo->setPosP(actualX, actualY);
		nuevoNodo->setGScore(GCost);
		nuevoNodo->setHScore(HCost);
		openList.agregar(nuevoNodo);
		delete nuevoNodo;
	}

	delete posExplorar;
}


unsigned int Pathfinder::calcularGCost (unsigned int padre, int posX, int posY, double coste) {
	unsigned int costeRed = 0;

	coste = MOV_PENALTY/coste;
	costeRed = (unsigned)std::floor(coste);
	return (costeRed + padre); 
}

unsigned int Pathfinder::calcularHeuristica(int posX, int posY, int DestinoX, int DestinoY) {
	
	posX = std::abs(posX-DestinoX);
	posY = std::abs(posY-DestinoY);
	return ((posX+posY)*MOV_PENALTY);
}