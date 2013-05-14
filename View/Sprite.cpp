#include <sstream> 
#include "Sprite.h"
#include "AnimatedEntity.h"
#include "DirList.h"

Sprite::Sprite(EntityObject *entity) {
	spriteEntity = entity;
	this->initialize();
}

void Sprite::initialize() {
	estado = 0;
	relx = spriteEntity->pixelRefX();
	rely = spriteEntity->pixelRefY();
	_baseWidth = spriteEntity->baseWidth();
	_baseHeight = spriteEntity->baseHeight();
	this->loadSurfaces();
}

Sprite::Sprite() {
}

Sprite::~Sprite() {
	for( unsigned i=0; i < surfaces.size(); i++) {
		surfaces[i]->free();
		delete surfaces[i];
	}
}

void Sprite::actualizarFrame() {
}

int Sprite::relatx() {
	return relx;
}

int Sprite::relaty() {
	return rely;
}

int Sprite::baseWidth() {
	return _baseWidth;
}

int Sprite::baseHeight() {
	return _baseHeight;
}

unsigned Sprite::getCurrentState() {
	return estado;
}

void Sprite::loadSurfaces() {
	this->addSurface(spriteEntity->imagePath());
}

void Sprite::addSurface(std::string path) {
	view::Surface* auxSurface = new view::Surface();
	auxSurface->load(path);
	auxSurface->createShadow();
	surfaces.push_back(auxSurface);
}

view::Surface* Sprite::getSurfaceAt(int state) {
	if (state < 0) {
		return this->getCurrentSurface();
	}
	return surfaces[static_cast<int>(state)];
}


view::Surface* Sprite::getCurrentSurface() {
	return surfaces[estado];
}