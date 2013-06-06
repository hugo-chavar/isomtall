#include "Entity.h"
#include "Game.h"
#include "TimeManager.h"

Entity::Entity() {
}

Entity::Entity(int tileX,int tileY,Sprite* spriteCargado) {
	this->setFogged(true);
	this->setStatus(ENTITY_NORMAL);
	this->resetSpriteState();
	sprite = spriteCargado;
	this->setRectangle(std::make_pair(tileX, tileY), spriteCargado);
}

Entity::~Entity() {
}

void Entity::setRectangle(std::pair<int, int> pos, Sprite* sprite ) {
	spriteRect = posicionIsometricaPorTiles(pos.first, pos.second, sprite);
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
	if (this->isImmobilized() && (this->freezedSpriteState < 0)) {
		freezedSpriteState = sprite->getCurrentSurfaceNumber();
		return;
	}
	if (!this->isImmobilized()) {
		this->resetSpriteState();
		return;
	}
	if (this->getStatus() == ENTITY_FROZEN) {
		this->decreaseEndStatusTime(Game::instance().time()->getDeltaTime());
		if (this->endStatusTime == 0)
			this->setStatus(ENTITY_NORMAL);
	}
}

void Entity::render(Camera& camera) {
	
	this->renderEntitySprite(this->spriteRect,this->sprite,camera);
	/*if (this->isImmobilized()) {
		if (this->isFogged())
			camera.render(spriteRect,sprite->getSurfaceAt(freezedSpriteState)->getBlackShadow());
		else
			camera.render(spriteRect,sprite->getSurfaceAt(freezedSpriteState)->getWhiteShadow());
	}
	camera.render(spriteRect,sprite->getSurfaceAt(freezedSpriteState)->getSurfaceToShow(this->isImmobilized()));*/
}

void Entity::renderEntitySprite(SDL_Rect rect,Sprite * _sprite,Camera& camera)
{
	if (this->isImmobilized()) {
		if (this->isFogged())
			camera.render(rect,_sprite->getSurfaceAt(freezedSpriteState)->getBlackShadow());
		else
			camera.render(rect,_sprite->getSurfaceAt(freezedSpriteState)->getWhiteShadow());
	}
	camera.render(rect,_sprite->getSurfaceAt(freezedSpriteState)->getSurfaceToShow(this->isImmobilized()));
}

void Entity::setFogged(bool value) {
	this->fogged = value;
}

void Entity::resetSpriteState() {
	this->freezedSpriteState = -1;
}

bool Entity::isFogged() {
	return this->fogged;
}

void Entity::setStatus(entityStatus_t status) {
	this->status = status;
}

entityStatus_t Entity::getStatus() {
	return this->status;
}

bool Entity::isImmobilized() {
	return ((this->isFogged() )||(this->getStatus() == ENTITY_FROZEN));
}

void Entity::iceUp(unsigned seconds) {
	this->setStatus(ENTITY_FROZEN);
	this->setEndStatusTime(static_cast<Uint32>(seconds*1000));
}

void Entity::decreaseEndStatusTime(float timeToDecrease) {
	Uint32 aux = static_cast<Uint32>(timeToDecrease);
	if (aux < this->endStatusTime)
		this->endStatusTime -= aux;
	else
		this->setEndStatusTime(0);
}

void Entity::setEndStatusTime(Uint32 endTime) {
	this->endStatusTime = endTime;
}

