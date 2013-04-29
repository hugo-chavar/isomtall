#include "Nodo.h"


Nodo::Nodo() {
	posX = 0;
	posY = 0;
	posXP = 0; posYP = 0;
	GScore = 0; HScore = 0;
}

Nodo::Nodo (int X, int Y) {
	posX = X;
	posY = Y;
	posXP = 0; posYP = 0;
	GScore = 0; HScore = 0;
}

Nodo::Nodo(const Nodo& nodo) {
	nodo.getPos(posX, posY);
	nodo.getPosP(posXP, posYP);
	GScore = nodo.getGScore();
	HScore = nodo.getHScore();
}

void Nodo::getPos (int &X, int &Y) const {
	X = posX;
	Y = posY;
}

void Nodo::setPos (int X, int Y) {
	posX = X;
	posY = Y;
}

void Nodo::getPosP (int &X, int&Y) const {
	X = posXP;
	Y = posYP;
}

void Nodo::setPosP (int X, int Y) {
	posXP = X;
	posYP = Y;
}

void Nodo::setGScore (unsigned int Score) {
	GScore = Score;
}

void Nodo::setHScore (unsigned int Score) {
	HScore = Score;
}

unsigned int Nodo::getGScore () const {
	return GScore;
}

unsigned int Nodo::getHScore () const {
	return HScore;
}

const Nodo &Nodo::operator=(const Nodo &nodo) {
	if (nodo != *this) {
		nodo.getPos(posX, posY);
		nodo.getPosP(posXP, posYP);
		GScore = nodo.getGScore();
		HScore = nodo.getHScore();
	}
	return *this;
}

bool Nodo::operator==(const Nodo &nodo) const {
	int x;
	int y;
	nodo.getPos(x, y);
	if ((x == posX)&&(y == posY)) {
			return true;
	}
	return false;
}

bool Nodo::operator!=(const Nodo &nodo) const {
	if (*this == nodo) {
		return false;
	}
	return true;
}

bool Nodo::operator<(const Nodo &nodo) const {
	unsigned int Score = 0;
	unsigned int hScore = 0;
	Score = nodo.getGScore() + nodo.getHScore();
	if ((HScore + GScore) < Score) {
		return true;
	} else {
		Score = nodo.getHScore();
		if ((HScore < Score)&&(Score==(GScore+HScore))) {
			return true;
		}
	}
	return false;
}

bool Nodo::operator>(const Nodo &nodo) const {
	unsigned int Score = 0;
	unsigned int hScore = 0;
	Score = nodo.getGScore() + nodo.getHScore();
	if ((HScore + GScore) > Score) {
		return true;
	} else {
		hScore = nodo.getHScore();
		if ((HScore > hScore)&&(Score==(GScore+HScore))) {
			return true;
		}
	}
	return false;
}

Nodo::~Nodo() {
}