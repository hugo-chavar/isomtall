#include <sstream> 
#include "Sprite.h"
#include "AnimatedEntity.h"
#include "DirList.h"

Sprite::Sprite(EntityObject *entity)
{
	this->inicializar(entity->pixelRefX(),entity->pixelRefY(),entity->baseWidth(),entity->baseHeight());
	cargarFrame(entity);//->imagePath());
}

void Sprite::inicializar(int refX,int refY,int baseWidth,int baseHeight)
{
	estado = 0;
	relx = refX;
	rely = refY;
	_baseWidth = baseWidth;
	_baseHeight = baseHeight;
}

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
	for(unsigned i=0;i<frames.size();i++)
	{
		frames[i]->liberar();
		delete frames[i];
	}
}

void Sprite::cargarFrame(EntityObject * entity)
{
	frames.push_back(new Frame());
	frames[0]->cargar(entity->imagePath());
}


void Sprite::actualizarFrame()
{
}

Frame* Sprite::getFrameActual()
{
	return frames[estado];
}

int Sprite::relatx()
{
	return relx;
}

int Sprite::relaty()
{
	return rely;
}

int Sprite::baseWidth()
{
	return _baseWidth;
}

int Sprite::baseHeight()
{
	return _baseHeight;
}

unsigned Sprite::getCurrentState() {
	return estado;
}

Frame* Sprite::getFrameAt(int state) {
	if (state < 0) {
		return this->getFrameActual();
	}
	return frames[static_cast<int>(state)];
}