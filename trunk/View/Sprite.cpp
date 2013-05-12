#include <sstream> 
#include "Sprite.h"
#include "AnimatedEntity.h"
#include "DirList.h"

Sprite::Sprite(EntityObject *entity) {
	//this->inicializar(entity->pixelRefX(),entity->pixelRefY(),entity->baseWidth(),entity->baseHeight());
	
	//cargarFrame(entity);
	spriteEntity = entity;
	this->initialize();
	//loadSurfaces(entity);
}
//
//void Sprite::inicializar(int refX,int refY,int baseWidth,int baseHeight) {
//	estado = 0;
//	relx = refX;
//	rely = refY;
//	_baseWidth = baseWidth;
//	_baseHeight = baseHeight;
//}

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
	//for(unsigned i=0;i<frames.size();i++) 	{
	//	frames[i]->liberar();
	//	delete frames[i];
	//}

	for( unsigned i=0; i < surfaces.size(); i++) {
		surfaces[i]->free();
		delete surfaces[i];
	}
}
//
//void Sprite::cargarFrame(EntityObject * entity) {
//	frames.push_back(new Frame());
//	frames[0]->cargar(entity->imagePath());
//}


void Sprite::actualizarFrame() {
}

//Frame* Sprite::getFrameActual() {
//	return frames[estado];
//}

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
//
//Frame* Sprite::getFrameAt(int state) {
//	if (state < 0) {
//		return this->getFrameActual();
//	}
//	return frames[static_cast<int>(state)];
//}
//
//void Sprite::loadSurfaces(EntityObject * entity) {
//	view::Surface* auxSurface = new view::Surface();
//	auxSurface->load(entity->imagePath());
//	surfaces.push_back(auxSurface);
//}

void Sprite::loadSurfaces() {
	this->addSurface(spriteEntity->imagePath());
	//view::Surface* auxSurface = new view::Surface();
	//auxSurface->load(spriteEntity->imagePath());
	//surfaces.push_back(auxSurface);
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