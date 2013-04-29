//Lista especial usada para la Open List

#ifndef LISTAPATH_H
#define LISTAPATH_H

#include "Par.h"
#include <vector>
#include <map>
#include "Nodo.h"


class ListaPath {
public:
	ListaPath();
	void agregar(Nodo* nuevo);
	bool empty();
	Nodo* getNodo();
	Nodo* getNodo(int X, int Y);
	~ListaPath();
private:
	std::map<Par, Nodo> nodeList;
};

#endif