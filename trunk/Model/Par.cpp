#include "Par.h"

Par::Par() {
	X = 0;
	Y = 0;
}

Par::Par(int posX, int posY) {
	X = posX;
	Y = posY;
}

Par::Par(const Par& par) {
	par.getPos(X, Y);
}

void Par::getPos(int& posX, int& posY) const {
	posX = X;
	posY = Y;
}

void Par::setPos(int posX, int posY) {
	X = posX;
	Y = posY;
}

const Par &Par::operator=(const Par &par) {
	if(par != *this) {
		par.getPos(X, Y);
	}
	return *this;
}

bool Par::operator==(const Par &par) const {
	int xPos = 0;
	int yPos = 0;

	par.getPos(xPos, yPos);
	if ((xPos==X)&&(yPos==Y)) {
		return true;
	}
	return false;
}

bool Par::operator!=(const Par &par) const {
	if (*this == par) {
		return false;
	}
	return true;
}

bool Par::operator<(const Par &par) const {
	int posX;
	int posY;

	par.getPos(posX, posY);
	if ((X+Y) < (posX+posY)) {
		return true;
	}
	if ((X < posX)&&((X+Y) == (posX+posY))) {
		return true;
	}
	return false;
}

bool Par::operator>(const Par &par) const {
	int posX;
	int posY;

	par.getPos(posX, posY);
	if ((X+Y) > (posX+posY)) {
		return true;
	}
	if ((X > posX)&&((X+Y) == (posX+posY))) {
		return true;
	}
	return false;
}

Par::~Par(){
}