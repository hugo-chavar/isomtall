#include <sstream> 
#include "Sprite.h"
#include "AnimatedEntity.h"
#include "DirList.h"

Sprite::Sprite(EntityObject *entity) {
	this->spriteEntity = entity;
	this->initialize();
}

void Sprite::initialize() {
	this->restart();
	this->relx = this->spriteEntity->pixelRefX();
	this->rely = this->spriteEntity->pixelRefY();
	this->_baseWidth = this->spriteEntity->baseWidth();
	this->_baseHeight = this->spriteEntity->baseHeight();
	this->loadSurfaces();
}

Sprite::Sprite() {
}

Sprite::~Sprite() {
	for ( unsigned i = 0; i < this->surfaces.size(); i++) {
		this->surfaces[i]->free();
		delete this->surfaces[i];
	}
}

void Sprite::updateFrame() {
}

int Sprite::relatx() {
	return this->relx;
}

int Sprite::relaty() {
	return this->rely;
}

int Sprite::baseWidth() {
	return this->_baseWidth;
}

int Sprite::baseHeight() {
	return this->_baseHeight;
}

unsigned Sprite::getCurrentSurfaceNumber() {
	return this->currentSurfaceNumber;
}

void Sprite::loadSurfaces() {
	this->addSurface(this->spriteEntity->imagePath());
}

void Sprite::addSurface(std::string path) {
	view::Surface* auxSurface = new view::Surface();
	auxSurface->load(path);
	//auxSurface->createShadows();
	auxSurface->createBlackShadow();
	this->surfaces.push_back(auxSurface);
}

view::Surface* Sprite::getSurfaceAt(int state) {
	if (state < 0) {
		return this->getCurrentSurface();
	}
	return surfaces[static_cast<unsigned>(state)];
}

view::Surface* Sprite::getCurrentSurface() {
	return surfaces[this->getCurrentSurfaceNumber()];
}

void Sprite::restart() {
	this->setCurrentSurfaceNumber(0);
}

void Sprite::setCurrentSurfaceNumber(unsigned surfaceNumber) {
	this->currentSurfaceNumber = surfaceNumber;
}

void Sprite::initWhiteShadows() {
	for ( unsigned i = 0; i < this->surfaces.size(); i++) {
		if (!this->surfaces[i]->hasWhiteShadow()) {
			this->surfaces[i]->createWhiteShadow();
		}
	}
}