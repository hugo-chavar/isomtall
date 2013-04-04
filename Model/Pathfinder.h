// Algoritmo de Pathfinder A*

#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "Nodo.h"
#include "Foo.h"		//Este vendría a ser el mapa ver en el .cpp los dos casos en los que se usa
#include "ListaPath.h"
#include "Par.h"
#include <map>

class Pathfinder {

public:
	int getPath (int OrigenX, int OrigenY, int DestinoX, int DestinoY, Foo &Tiles, int* &XPath, int* &YPath);

private:
	void agregarVecinos(Nodo& actual, int DestinoX, int DestinoY, std::map<Par, Nodo>& closeList, ListaPath& openList, Foo& Tiles);
	unsigned int calcularGCost (unsigned int padre, int posX, int posY, double coste);
	unsigned int calcularHeuristica(int posX, int posY, int DestinoX, int DestinoY); //Con metodo Manhattan
};

#endif