#include "ListaPath.h"

using namespace model;

ListaPath::ListaPath() {
}

void ListaPath::agregar(Nodo* nuevo) {
	std::map<Par, Nodo>::iterator it;
	int xValue = 0;
	int yValue = 0;
	Par* pos = NULL;
	bool insert = true;

	it = nodeList.begin();
	while(it!=nodeList.end()) {
		if((*nuevo)<(it->second)) {
			nuevo->getPos(xValue, yValue);
			pos = new Par(xValue, yValue);
			nodeList.insert(it, std::pair<Par, Nodo>(*pos, *nuevo));
			insert = false;
			break;
		}
		it++;
	}
	if ((it==nodeList.end())&&(insert)) {
		nuevo->getPos(xValue, yValue);
		pos = new Par(xValue, yValue);
		nodeList.insert(it, std::pair<Par, Nodo>(*pos, *nuevo));
	}
}

Nodo* ListaPath::getNodo(int X, int Y) {
	std::map<Par, Nodo>::iterator it;
	Par* pos = NULL;
	Nodo* nodoDevuelto = NULL;

	it = nodeList.begin();
	pos = new Par(X, Y);
	it = nodeList.find(*pos);
	if (it == nodeList.end()) {
		return nodoDevuelto;
	}
	nodoDevuelto = new Nodo(0,0);
	*nodoDevuelto = it->second;
	nodeList.erase(it);
	return nodoDevuelto;
}

Nodo* ListaPath::getNodo() {
	Nodo* nodoDevuelto = NULL;
	Nodo* nodo = NULL;
	std::map<Par, Nodo>::iterator it;
	int size = 0;
	int count = 0;

	it = nodeList.begin();
	if (nodeList.empty()) {
		return nodoDevuelto;
	}
	size = nodeList.size();
	nodo = &(it->second);
	for (int i = 0; i < (size); ++i) {
		if (*nodo > it->second) {
			nodo = &(it->second);
			count = i;
		}
		it++;
	}
	nodoDevuelto = new Nodo(0,0);
	*nodoDevuelto = *nodo;
	it = nodeList.begin();
	for (int i=0; i < (count); ++i) {
		it++;
	}
	nodeList.erase(it);
	return nodoDevuelto;
}

bool ListaPath::empty() {
	return nodeList.empty();
}

ListaPath::~ListaPath() {
}