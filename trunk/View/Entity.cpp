#include "Entity.h"
#include "Game.h"

Entity::Entity() {
}

Entity::Entity(int tileX,int tileY,Sprite* spriteCargado) {
	this->setFreezed(true);
	this->resetSpriteState();
	sprite = spriteCargado;
	this->setRectangle(std::make_pair(tileX, tileY), spriteCargado);
}

Entity::~Entity() {
	//this->shadow.free();
	//delete this->shadow;
}

void Entity::setRectangle(std::pair<int, int> pos, Sprite* sprite ) {
	spriteRect = posicionIsometricaPorTiles(pos.first, pos.second, sprite);
	/*spriteRect.w = (Uint16)(sprite->getFrameActual()->getSuperficie()->w);
	spriteRect.h = (Uint16)(sprite->getFrameActual()->getSuperficie()->h);*/
	spriteRect.w = (Uint16)(sprite->getCurrentSurface()->getSurface()->w);
	spriteRect.h = (Uint16)(sprite->getCurrentSurface()->getSurface()->h);
}

SDL_Rect Entity::posicionIsometricaPorTiles(int tileX,int tileY,Sprite* sprite) {
	SDL_Rect rectangulo;
	unsigned pptx = Game::instance().world()->tileWidth();
	unsigned ppty = Game::instance().world()->tileHeight();
	rectangulo.x = (Sint16)(pptx*tileX/2-pptx*tileY/2-sprite->relatx());
	rectangulo.y = (Sint16)(ppty*tileX/2+ppty*tileY/2-sprite->relaty());
	return rectangulo;
}

void Entity::update() {
	if (this->isFreezed() && (this->freezedSpriteState < 0)) {
		freezedSpriteState = sprite->getCurrentState();
	}
	//sprite->actualizarFrame();
	//Aca deberia actualizarse tambien la entidad del modelo
}

void Entity::render(Camera& camera) {

	//if (this->freezed)
	//	camera.render(spriteRect,this->shadow.getSdlSurface());
	//camera.render(spriteRect,sprite->getFrameAt(freezedSpriteState)->getSuperficie(this->freezed));

	//camera.render(spriteRect,sprite->getFrameActual()->getSuperficie(false));

	if (this->freezed)
		camera.render(spriteRect,sprite->getSurfaceAt(freezedSpriteState)->getShadow());
	camera.render(spriteRect,sprite->getSurfaceAt(freezedSpriteState)->getSurfaceToShow(this->freezed));
}

void Entity::setFreezed(bool value) {
	if (this->freezed == value)
		return;
	this->freezed = value;
	if (!this->isFreezed())
		this->resetSpriteState();
}

void Entity::resetSpriteState() {
	this->freezedSpriteState = -1;
}

bool Entity::isFreezed() {
	return this->freezed;
}
//
//SDL_Rect Entity::getSdlRect() {
//	return this->spriteRect;
//}


