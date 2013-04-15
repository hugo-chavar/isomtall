#include "Entity.h"





Entity::Entity() {}

Entity::Entity(int tileX,int tileY,Sprite* spriteCargado)//(int tileX,int tileY,std::string path,std::string nombre,int nroFrames, int relx,int rely)
{
	sprite= spriteCargado;
	spriteRect=posicionIsometricaPorTiles(tileX, tileY,sprite);
	spriteRect.w=(Uint16)(sprite->getFrameActual()->getSuperficie()->w);
	spriteRect.h=(Uint16)(sprite->getFrameActual()->getSuperficie()->h);
}

SDL_Rect Entity::posicionIsometricaPorTiles(int tileX,int tileY,Sprite* sprite)
{
	SDL_Rect rectangulo;
	rectangulo.x= (Sint16)(pptx*tileX/2-pptx*tileY/2-sprite->relatx());
	rectangulo.y= (Sint16)(ppty*tileX/2+ppty*tileY/2-sprite->relaty());
	return rectangulo;
}

void Entity::update()
{
	sprite->actualizarFrame();
	//Aca deberia actualizarse tambien la entidad del modelo
}
void Entity::render(Camera& camera)
{
camera.render(spriteRect,sprite->getFrameActual()->getSuperficie());
}

Entity::~Entity(void)
{
}
