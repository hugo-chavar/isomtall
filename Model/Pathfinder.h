// Algoritmo de Pathfinder A*

#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "Nodo.h"
#include "ListaPath.h"
#include "Par.h"
#include <map>

class Pathfinder {

public:
	int getPath (int OrigenX, int OrigenY, int& DestinoX, int& DestinoY, int* &XPath, int* &YPath); //Foo &Tiles,

private:
	void getNodoMasCercano(std::map<Par, Nodo>& closeList, Nodo* &actual, int &actualX, int &actualY);
	void agregarVecinos(Nodo& actual, int DestinoX, int DestinoY, std::map<Par, Nodo>& closeList, ListaPath& openList); //, Foo& Tiles
	unsigned int calcularGCost (unsigned int padre, int posX, int posY, double coste);
	unsigned int calcularHeuristica(int posX, int posY, int DestinoX, int DestinoY); //Con metodo Manhattan
};

#endif
